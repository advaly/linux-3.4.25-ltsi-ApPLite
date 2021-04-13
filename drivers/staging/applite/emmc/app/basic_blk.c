/**
 * @file          basic_blk.c
 *
 * \brief         This file has emmc block driver implementation
 *
 * \b COPYRIGHT : TOSHIBA Corporation Semiconductor and Storage Company
 *                2010-2015 All rights reserved.
 *
 * \b Project   : Glenfiddich
 *
 * \b Version   : 0.4
 *
 * \b Release   : None
 *
 * \b Date      : 28-Jun-2013
 */

/**
 * @addtogroup TestApplication
 * @{
 */

/**
 * @addtogroup BlockDriver
 * @{
 */

/*----------------------- Header Files Inclusions ---------------------------*/
#include <linux/module.h>       /* Module Macros */
#include <linux/moduleparam.h>  /* load time Param Macros */
#include <linux/init.h>

#include <linux/kernel.h>       /* printk() */
#include <linux/fs.h>           /* everything... */
#include <linux/errno.h>        /* error codes */
#include <linux/genhd.h>        /* gen device */
#include <linux/blkdev.h>       /* Block device functions */
#include <linux/kthread.h>      /* kernel thread functions */
#include <linux/hdreg.h>        /* geometric data structure */
#include <linux/scatterlist.h>  /* scatter gather list support */
#include <linux/dma-mapping.h>  /* DMA related linux defines and enums */

#include "emmc_api.h"           /* Toshiba eMMC APIs */
#include "debug.h"              /* Debug macros and functions */
#ifdef CONFIG_PM
#include <linux/platform_device.h> /* platform_driver */
#include <linux/pm.h>              /* dev_pm_ops */
#endif /* CONFIG_PM */

/*-------------------------- Macro Definitions -------------------------------*/

/** @addtogroup BLK_DEFINES BLK_DEFINES
 * @{
 */

#ifdef _EMMCBLK_DEBUG
#define _EMMCBLK_ERROR_DEBUG_MSG(__format__, arg...)    \
       dz_print(_DZ_CRTICAL, "[%4d]%s::" __format__"\n", __LINE__, \
       __FUNCTION__,## arg )

#define _EMMCBLK_OPTIONAL_DEBUG_MSG(__format__, arg...)    \
       dz_print(_DZ_INFO, "[%4d]%s::" __format__"\n", __LINE__, \
       __FUNCTION__,## arg )
#else
#define _EMMCBLK_ERROR_DEBUG_MSG(__format__, arg...)    /* Nop */
#define _EMMCBLK_OPTIONAL_DEBUG_MSG(__format__, arg...) /* Nop */
#endif /* !_EMMCBLK_DEBUG */

#define EMMC_DEVICE_NAME        "emmc"
#define EMMCBLK_DRIVER_VERSION  "3.0"
#define EMMC_SLOT_ID            0
#define EMMC_MINOR_OFFSET       8

/*
 * We can tweak our hardware sector size, but the kernel talks to us
 * in terms of small sectors, always.
 */
#ifdef __GLEN
#define PHYSICAL_SECTOR_SIZE 4096
#endif /* __GLEN */

#define KERNEL_SECTOR_SIZE  512
#define NO_OF_SCATTER       1024
#define MAX_SEGMENT_SIZE    65536
#define GEO_HEADS           4
#define GEO_SECTORS         16

/**@}*/ // BLK_DEFINES

/*-------------------------- Enum Definitions --------------------------------*/

/*------------------ Data Structures & Custom Typedefs -----------------------*/

/** @defgroup BLK_Structures BLK_Structures
 * @{
 */

/**
 * @brief Structure for block driver registration
 */
typedef struct tag_emmc_BlockDevice_t {
    unsigned int uiPartIdx;         /**< eMMC harware Partition ID */
    struct gendisk *gen_disk;       /**< eMMC device generic kernel structure */

    struct request_queue *queue;    /**< kernel request Q */
    struct request *req;            /**< current request descriptor */
    spinlock_t *DevLock;            /**< Spin lock for request Q */

    struct task_struct *thread;     /**< request Q callback work distributor */
    struct semaphore thread_sem;    /**< sync sem for Request Q and thread */

    struct scatterlist *sg;         /**< block driver scatter gather pointer */
    com_sglist_t    sgList;         /**< eMMC Driver SG processing list */
    int size;                       /**< Device size in bytes */

}emmc_BlockDevice;

/**@}*/ // BLK_Structures

/** @addtogroup BLK_Globals BLK_Globals
 * @{
 */

static spinlock_t atomicQLock;      /* Spin lock for request Q */

/**@}*/ // BLK_Globals

/*------------------------------ Externs -------------------------------------*/

/*------------- Data variable/Structure allocation (global) ------------------*/

/** @addtogroup BLK_Globals BLK_Globals
 * @{
 */

/* Block device globals */
static emmc_BlockDevice *gl_emmcDevice[_COM_PARTITION_MAX];

/* Default Block driver command line parameters and values */
static int major_num = 0;       /* default major number */
static int freq = 100000000;            /* Device Operating frequency */
static int buswidth = _COM_BWIDTH_8;   /* Device operating bus width */
static int trans_mode = _COM_MODE_ADMA2; /* Device transfer mode */
#ifdef __GLEN
static int blk_size = PHYSICAL_SECTOR_SIZE; /* Device sector size */
#else /* !__GLEN */
static int blk_size = KERNEL_SECTOR_SIZE; /* Device sector size */
#endif /* __GLEN */
static int dbg = _DZ_LEVEL1;           /* Enable debug zones */

/**@}*/ // BLK_Globals

/*------------------------- Kernel Module Macros -----------------------------*/

/** @addtogroup BLK_Macros BLK_Macros
 * @{
 */

MODULE_LICENSE("Dual BSD/GPL");
MODULE_VERSION(EMMCBLK_DRIVER_VERSION);

module_param(major_num, int, 0);
MODULE_PARM_DESC(major_num, "configure eMMC major number");

module_param(blk_size, int, 0);
#ifdef __GLEN
MODULE_PARM_DESC(blk_size, "Device block size def:4096B");
#else /* !__GLEN */
MODULE_PARM_DESC(blk_size, "Device block size def:512B");
#endif /* __GLEN */

module_param(freq, int, 0);
MODULE_PARM_DESC(freq, "eMMC operating frequency");

module_param(buswidth, int, 0);
MODULE_PARM_DESC(buswidth, "eMMC bus width (0: 8bit, 1:4bit, def:2:1bit)");

module_param(trans_mode, int, 0);
MODULE_PARM_DESC(trans_mode, "Data trans Mode (def:0: PIO, 1:SDMA, 2:ADMA2)");

module_param(dbg, int, 0);
MODULE_PARM_DESC(dbg, "Debug Zone (def:1: L1, 3:L2, 7:L3 0xFFFFFFF:All)");

/**@}*/ // BLK_Macros

/*---------------------------- Prototypes ------------------------------------*/

/** @addtogroup BLK_Prototypes BLK_Prototypes
 * @{
 */

static int emmcblk_getgeo(
    struct block_device * block_device,
    struct hd_geometry * geo);

/* The device operations structure */
static struct block_device_operations emmcblk_ops = {
        .owner  = THIS_MODULE,
        .getgeo = emmcblk_getgeo
};

/* Functions for Scatter Gather List */
static _ub32 emmcblk_createScatterGatherList(
    emmc_BlockDevice *emmcDevice,
    struct request *pRequest,
    char r_w);

static void emmcblk_deleteScatterGatherList(
    emmc_BlockDevice *emmcDevice,
    char r_w);

static void emmcblk_cleanNode(emmc_BlockDevice *emmcDevice);

/**@}*/ // BLK_Prototypes

/*----------------------- Function Definitions -------------------------------*/

/** @addtogroup BLK_Functions BLK_Functions
 * @{
 */

/**
 * @brief get geometric for the eMMC device
 *
 * To support partition tools such as fdisk, we need to configure the device
 * geometric settings. For this getgeo callback is registered using
 * blockdevice operation structure. This callback is called while using the
 * tools
 *
 * @param[in] block_device *    Kernel data structure for block device
 * @param[in] hd_geometry *     Geometric data structure for block device
 *
 * @retval 0 for successful initialization
 */
static int emmcblk_getgeo(
    struct block_device * block_device,
    struct hd_geometry * geo)
{
#ifdef __GLEN
    /* We have no real geometry, of course, so make something up. */
    geo->heads     = GEO_HEADS;
    geo->sectors   = GEO_SECTORS;
    geo->cylinders = \
    get_capacity(block_device->bd_disk)/(geo->heads * geo->sectors);
#else /* !__GLEN */
    unsigned int uiPartIdx = 0;
    long size;

    /* We have no real geometry, of course, so make something up. */
    size = (gl_emmcDevice[uiPartIdx]->size) * (blk_size / KERNEL_SECTOR_SIZE);
    geo->cylinders = (size & ~0x3f) >> 6;
    geo->heads   = GEO_HEADS;
    geo->sectors = GEO_SECTORS;
#endif /* __GLEN */
    geo->start = 0;
    return 0;
}

/**
 * @brief Callback routine for request Q
 *
 * Signalling block driver request to associate thread
 *
 * @param[in] request_queue Q*  Block driver request Q pointer
 *
 * @retval none
 * @Note: Callback from block driver scheduler
 */
static void emmcBlkRequestHandler(struct request_queue *Rq)
{
    emmc_BlockDevice *emmcDevice;
    struct request *req;
    emmcDevice = Rq->queuedata;

    /* if dummy request are there in the Q before init */
    if(!emmcDevice)
    {
        while((req = blk_fetch_request(Rq)) != NULL)
        {
            req->cmd_flags |= REQ_QUIET;
            spin_lock_irq(emmcDevice->queue->queue_lock);
            __blk_end_request_all(req, -EIO);
            spin_unlock_irq(emmcDevice->queue->queue_lock);
        }
        return;
    }

    /* If no pending request */
    if(!emmcDevice->req)
    {
        wake_up_process(emmcDevice->thread);
    }
}

/**
 * @brief Supporting function to access eMMC device
 *
 * This function call is made from eMMC thread with following params
 *
 * @param[in] gendisk* global block device pointer
 * @param[in] request* Current request description
 * @param[in] r_w      Transaction type as read or write
 *
 * @retval none
 */
static int emmcBlkRequestTransfer(
    struct gendisk *gd,
    struct request *pRequest,
    char r_w)
{
    volatile unsigned int Offset;
    volatile int ret;
    volatile int totalbytes = 0, totalbytesInSg = 0;
    emmc_BlockDevice *emmcDevice = gd->private_data;
    unsigned int blocks = 0;
    _ub32 uiPartNum = 0;
    _ub8 *ptr;

    /* if request belongs to file system such as packet-mode */
    if(pRequest->cmd_type != REQ_TYPE_FS)
    {
        _EMMCBLK_ERROR_DEBUG_MSG("Req belongs to Packet Node");
        ret = -EIO;
        spin_lock_irq(emmcDevice->queue->queue_lock);
        blk_end_request_all(pRequest, ret);
        spin_unlock_irq(emmcDevice->queue->queue_lock);
        return ret;
    }

    /* get no of sectors are requested for entire request */
    blocks = blk_rq_sectors(pRequest);

    /* boundary validation with device size */
    if(blk_rq_pos(pRequest) + blocks > get_capacity(pRequest->rq_disk))
    {
        ret = -EIO;
        _EMMCBLK_ERROR_DEBUG_MSG("No space in Device");
        spin_lock_irq(emmcDevice->queue->queue_lock);
        blk_end_request_all(pRequest, ret);
        spin_unlock_irq(emmcDevice->queue->queue_lock);
        return ret;
    }

    do
    {
        /* get device sector offset for transaction */
        Offset = blk_rq_pos(pRequest);

        /* Total bytes in the segment for current request */
        totalbytes = blk_rq_cur_bytes(pRequest);

        _EMMCBLK_OPTIONAL_DEBUG_MSG("TBlks[%d] TSegBytes[%d] off[0x%08X] Dir[%c]\n", \
            blocks, totalbytes, Offset, r_w);

        /* Update transaction pointer as Request buffer */
        ptr = pRequest->buffer;

        /* Scatter gather is applicable only for ADMA2 */
        if(_COM_MODE_ADMA2 == trans_mode)
        {
            /* Convert Block driver scatter list in to device scatter list */
            totalbytesInSg = emmcblk_createScatterGatherList(
                emmcDevice, pRequest, r_w);

            /* Update transaction pointer in to Scatter Gather List */
            ptr = (_ub8*)&emmcDevice->sgList;

            /* get total transaction bytes for the whole request */
            totalbytes = blk_rq_bytes(pRequest);

            /*
             * If block driver request and scatter gather list collective size
             * are different, we need to process only the scatter gather size,
             * the remaining size will be processed in next iteration.
             * Anyway this scenario never expected
             */
            if(totalbytes != totalbytesInSg)
            {
                _EMMCBLK_ERROR_DEBUG_MSG("Not processed complete request %d != %d\n", \
                                totalbytes, totalbytesInSg);

                totalbytes = totalbytesInSg;
            }
        }

        /* Select Partition based on the partition ID */
        ret = emmc_getCurrPartition(EMMC_SLOT_ID, &uiPartNum);
        if(uiPartNum != (emmcDevice->uiPartIdx))
        {
            ret |= emmc_accessPartitions(EMMC_SLOT_ID, emmcDevice->uiPartIdx);
        }

        if(_EMMC_STS_OK == ret)
        {
            if('W' == r_w)
            {
                /* eMMC driver write call */
                ret = emmc_write(EMMC_SLOT_ID, ptr, totalbytes, Offset);
                if(_EMMC_STS_OK != ret)
                {
                    _EMMCBLK_ERROR_DEBUG_MSG( \
                        "emmc_write(Off[%d]=>%dBytes) failed", \
                        Offset, totalbytes);
                }
            }
            else
            {
                /* eMMC driver read call */
                ret = emmc_read(EMMC_SLOT_ID, ptr, totalbytes, Offset);
                if(_EMMC_STS_OK != ret)
                {
                    _EMMCBLK_ERROR_DEBUG_MSG( \
                        "emmc_read(Off[%d]=>%dBytes) failed", \
                        Offset, totalbytes);
                }
            }
        }

        /* Scatter Gather is applicable only for ADMA2 */
        if(_COM_MODE_ADMA2 == trans_mode)
        {
            /* free SG resource to kernel */
            emmcblk_deleteScatterGatherList(emmcDevice, r_w);
        }

        /*
         * __blk_end_request() this call will Update request descriptor
         * with processed segments/bytes, the return value will be decider
         * to be continue the same request with new segments or not
         */
        spin_lock_irq(emmcDevice->queue->queue_lock);
        ret = __blk_end_request(pRequest, ret, totalbytes);
        spin_unlock_irq(emmcDevice->queue->queue_lock);

    }while(ret);

    return ret;
}

/**
 * @brief Create Scatter gather list from block Request
 *
 * This routine is used convert block driver request in to
 * eMMC scatter gather request to driver
 *
 * @param[in] Partition specific block driver structure
 * @param[in] Current block driver request
 * @param[in] Read or Write flag
 * @param[out] Create driver specific SG list and update
 * in to partition specific structure
 *
 * @retval Total bytes used in the SG list
 */
static _ub32 emmcblk_createScatterGatherList(
    emmc_BlockDevice *emmcDevice,
    struct request *pRequest,
    char r_w)
{
    int nentries = 0, tempentries;
    struct scatterlist *sgentry;
    int i = 0;
    int sgTotalBytes = 0;
    enum dma_data_direction dir;
    com_sg_t *psg;

    nentries = blk_rq_map_sg(emmcDevice->queue, pRequest, emmcDevice->sg);

    dir = (('W' == r_w)? DMA_TO_DEVICE : DMA_FROM_DEVICE);
    tempentries = dma_map_sg(NULL, emmcDevice->sg, nentries, dir);

    /*
     * if requested SG elements and actual physical address mapped elements
     * are different, we need to process only mapped elements.
     * This error case NEVER occur
     */
    if(tempentries != nentries)
    {
        _EMMCBLK_ERROR_DEBUG_MSG("SG entries are different %d != %d\n", \
                    tempentries, nentries);

        nentries = tempentries;
    }

    /* Get SG element array in temp pointer */
    psg = (com_sg_t*)emmcDevice->sgList.paEle;

    /* Store translated address and segment size in to driver database */
    for_each_sg(emmcDevice->sg, sgentry, nentries, i)
    {
        psg[i].dmaAddr = sg_dma_address(sgentry);
        psg[i].uiSize = sg_dma_len(sgentry);
        sgTotalBytes += psg[i].uiSize;
    }

    /* Update total SG elements in global struct */
    emmcDevice->sgList.uiTotal = nentries;

    _EMMCBLK_OPTIONAL_DEBUG_MSG("%d SG entries for %d Bytes\n", \
        nentries, sgTotalBytes);

    return sgTotalBytes;
}

/**
 * @brief Delete Scatter gather list from block Request
 *
 * This routine is used remove the scatter gather resource
 *
 * @param[in] Partition specific block driver structure
 * @param[in] Read or Write flag
 * @param[out] Create driver specific SG list and update
 * in to partition specific structure
 *
 * @retval none
 */
static void emmcblk_deleteScatterGatherList(
    emmc_BlockDevice *emmcDevice,
    char r_w)
{
    enum dma_data_direction dir;

    dir = (('W' == r_w)? DMA_TO_DEVICE : DMA_FROM_DEVICE);

    /* unmap scatter gather list addresses */
    dma_unmap_sg(NULL, emmcDevice->sg, emmcDevice->sgList.uiTotal, dir);

    /* initialize scatter gather list as zero */
    emmcDevice->sgList.uiTotal = 0;

    return;
}

/**
 * @brief Handling Linux block driver requests
 *
 * This thread routine is managing kernel request Q scheduler callback
 * processing in device access from request Q handler. This will provide
 * kernel resource usage in efficient way
 *
 * @param[in] emmc_BlockDevice*  eMMC global device structure
 *
 * @retval none
 */
static int emmcDevice_queue_thread(void *d)
{
    emmc_BlockDevice *emmcDevice = d;
    struct request_queue *rq = emmcDevice->queue;
    struct request *req = NULL;
    struct gendisk *gd;
    char r_w;

    current->flags |= PF_MEMALLOC;

    /* Lock */
    down(&emmcDevice->thread_sem);
    do
    {
        req = (struct request *)NULL;
        spin_lock_irq(rq->queue_lock);
        set_current_state(TASK_INTERRUPTIBLE);

        /* if request is plugged in Q */
#ifndef __GLEN
        if(!blk_queue_plugged(rq))
#endif /* __GLEN */
        {
            /* fetch request from Q */
            req = blk_fetch_request(rq);
        }

        /* store request in to global for supporting function */
        emmcDevice->req = req;
        gd = emmcDevice->gen_disk;
        spin_unlock_irq(rq->queue_lock);

        /* if request is not available reschedule the thread */
        if(!req)
        {
            if(kthread_should_stop())
            {
                set_current_state(TASK_RUNNING);
                break;
            }
            up(&emmcDevice->thread_sem);
            schedule();
            down(&emmcDevice->thread_sem);
            continue;
        }
        set_current_state(TASK_RUNNING);

        /* Get request processing direction */
        r_w = (rq_data_dir(req) == 0) ? 'R' : 'W';

        /* Request processing */
        emmcBlkRequestTransfer(gd, req, r_w);

    } while(1);

    /* UnLock */
    up(&emmcDevice->thread_sem);
    return 0;
}

#ifdef CONFIG_PM
int emmc_suspend(struct device *dev);
int emmc_resume(struct device *dev);

int emmc_suspend(struct device *dev)
{
    /* do nothing */
    return 0;
}

int emmc_resume(struct device *dev)
{
    emmc_sts_e ret = _EMMC_STS_OK;

    /* eMMC host and device de-initialization */
    emmc_exit();

    /* eMMC host and device initialization */
    ret = emmc_init();
    if(_EMMC_STS_OK != ret)
    {
        _EMMCBLK_ERROR_DEBUG_MSG("emmc_init() failed");
        return -1;
    }

    /* Set configuration for the eMMC device setup */
    ret = emmc_setBusWidth(EMMC_SLOT_ID, buswidth);
    ret |= emmc_setOpMode(EMMC_SLOT_ID, trans_mode);
    ret |= emmc_setClock(EMMC_SLOT_ID, freq);
    ret |= emmc_setConfig(EMMC_SLOT_ID);
    if(_EMMC_STS_OK != ret)
    {
        _EMMCBLK_ERROR_DEBUG_MSG("emmc_setConfig() failed code[%d]", ret);
        emmc_exit();
        return -1;
    }

    return 0;
}

static struct dev_pm_ops emmc_pm_ops = {
    SET_SYSTEM_SLEEP_PM_OPS(emmc_suspend, emmc_resume)
};

static struct platform_driver mmctsip_driver = {
    .driver = {
        .name = "emmc_pm",
        .owner = THIS_MODULE,
        .pm = &emmc_pm_ops,
       },
};
#endif /* CONFIG_PM */

/**
 * @brief Initializing block driver, Request Q and eMMC device
 *
 * This routine is used in module_init to do the insmod
 *
 * @param none
 *
 * @retval nonzero to error/0 for success to kernel module
 */
static int __init emmcblk_init(void)
{
    emmc_sts_e ret = _EMMC_STS_OK;
    int blk_ret = 0;
    unsigned int uiVersion;
    unsigned int uiSectCnt;
    unsigned int uiPartIdx = _COM_PARTITION_UDA;
    com_gpp_attr_t gpp_part;

    char acDevId[20] = EMMC_DEVICE_NAME;

    debug_setZone(dbg);
    emmc_getVersion(&uiVersion);

    printk("\n");
    printk("*********************************************************\n");
    printk("                    eMMC Block driver                    \n");
    printk("  TOSHIBA Corporation Semiconductor and Storage Company  \n");
    printk("            2010-2015 All rights reserved                \n");
    printk("           eMMC Driver Version 0x%08X\n",         uiVersion );
    printk("*********************************************************\n");

#ifdef CONFIG_PM
    ret = platform_driver_register(&mmctsip_driver);
    if(0 != ret)
    {
        _EMMCBLK_ERROR_DEBUG_MSG("platform_driver_register() failed");
        return -1;
    }
#endif /* CONFIG_PM */

    /* eMMC host and device initialization */
    ret = emmc_init();
    if(_EMMC_STS_OK != ret)
    {
        _EMMCBLK_ERROR_DEBUG_MSG("emmc_init() failed");
#ifdef CONFIG_PM
        platform_driver_unregister(&mmctsip_driver);
#endif /* CONFIG_PM */
        return -1;
    }

    /* Set configuration for the eMMC device setup */
    ret = emmc_setBusWidth(EMMC_SLOT_ID, buswidth);
    ret |= emmc_setOpMode(EMMC_SLOT_ID, trans_mode);
    ret |= emmc_setClock(EMMC_SLOT_ID, freq);
    ret |= emmc_setConfig(EMMC_SLOT_ID);
    if(_EMMC_STS_OK != ret)
    {
        _EMMCBLK_ERROR_DEBUG_MSG("emmc_setConfig() failed code[%d]", ret);
        emmc_exit();
#ifdef CONFIG_PM
        platform_driver_unregister(&mmctsip_driver);
#endif /* CONFIG_PM */
        return -1;
    }

    /* Registering eMMC as block driver */
    major_num = register_blkdev(major_num, acDevId);
    if(major_num < 0)
    {
        _EMMCBLK_ERROR_DEBUG_MSG("emmc: unable to get major number");
        emmc_exit();
#ifdef CONFIG_PM
        platform_driver_unregister(&mmctsip_driver);
#endif /* CONFIG_PM */
        return -1;
    }

    /* Create common spinlock for the device */
    spin_lock_init(&atomicQLock);

    /* Create device nodes for all partition for the device */
    do
    {
        /* Check GPP partition availability for the device */
        if(uiPartIdx > _COM_PARTITION_UDA)
        {
            ret = emmc_getGPPAttributes(EMMC_SLOT_ID, uiPartIdx, &gpp_part);
            if(_EMMC_DEV_PART_NOT_CREATED == ret)
            {
                ++uiPartIdx;
                continue;
            }
            uiSectCnt = gpp_part.uiPartSize;
        }
        else
        {
            ret = emmc_getDevMaxSect(EMMC_SLOT_ID, &uiSectCnt);
        }

        /* If status is OK display the device size */
        if(_EMMC_STS_OK == ret)
        {
            dz_print(\
                _DZ_CRTICAL, "Total Device size in sectors %d\n", uiSectCnt);
            dz_print(_DZ_CRTICAL, "Total Device size in MB        %d\n",
                     (uiSectCnt/2048));
        }

        /* alloc kernel memory for global block driver structure */
        gl_emmcDevice[uiPartIdx] = \
            kzalloc(sizeof(emmc_BlockDevice), GFP_KERNEL);
        if(NULL == gl_emmcDevice[uiPartIdx])
        {
            _EMMCBLK_ERROR_DEBUG_MSG(\
                "Cannot Allocate Memory to partition %d", uiPartIdx);

            blk_ret = -ENOMEM;
            break;
        }

        /* allocate generic disk with maximum 16 partitions */
        gl_emmcDevice[uiPartIdx]->gen_disk = alloc_disk(EMMC_MINOR_OFFSET);
        if(NULL == gl_emmcDevice[uiPartIdx]->gen_disk)
        {
            kfree(gl_emmcDevice[uiPartIdx]);
            _EMMCBLK_ERROR_DEBUG_MSG(\
                "GENDISK Allocation Fails for partition %d", uiPartIdx);

            blk_ret = -ENOMEM;
            break;
        }

        /* update eMMC values in to generic disk */
        gl_emmcDevice[uiPartIdx]->gen_disk->major = major_num;

        gl_emmcDevice[uiPartIdx]->gen_disk->first_minor = \
            (uiPartIdx+1) * EMMC_MINOR_OFFSET;

        gl_emmcDevice[uiPartIdx]->gen_disk->fops = &emmcblk_ops;

        gl_emmcDevice[uiPartIdx]->gen_disk->private_data = \
            &gl_emmcDevice[uiPartIdx];

        if(uiPartIdx == _COM_PARTITION_UDA)
        {
            sprintf(acDevId, "%s%1d", EMMC_DEVICE_NAME, 0);
        }
        else
        {
            sprintf(acDevId, "%sgpp%1d", EMMC_DEVICE_NAME, uiPartIdx);
        }
        strcpy(gl_emmcDevice[uiPartIdx]->gen_disk->disk_name, acDevId);

#ifdef __GLEN
        gl_emmcDevice[uiPartIdx]->size = uiSectCnt * KERNEL_SECTOR_SIZE;
#else /* !__GLEN */
        gl_emmcDevice[uiPartIdx]->size = uiSectCnt * blk_size;
#endif /* __GLEN */

        /* Get a request Q for block driver */
        gl_emmcDevice[uiPartIdx]->DevLock = &atomicQLock;
        spin_lock_init(gl_emmcDevice[uiPartIdx]->DevLock);
        gl_emmcDevice[uiPartIdx]->queue = blk_init_queue(
            emmcBlkRequestHandler, gl_emmcDevice[uiPartIdx]->DevLock);

        /* Validation for Request Q */
        if (gl_emmcDevice[uiPartIdx]->queue == NULL)
        {
            put_disk(gl_emmcDevice[uiPartIdx]->gen_disk);
            kfree(gl_emmcDevice[uiPartIdx]);
            _EMMCBLK_ERROR_DEBUG_MSG(\
                "REQ Q Creation Fails partition %d", uiPartIdx);

            blk_ret = -ENODEV;
            break;
        }

#ifdef __GLEN
        blk_queue_physical_block_size(gl_emmcDevice[uiPartIdx]->queue, \
                blk_size);

        blk_queue_logical_block_size(gl_emmcDevice[uiPartIdx]->queue, \
                KERNEL_SECTOR_SIZE);

        blk_queue_dma_alignment(gl_emmcDevice[uiPartIdx]->queue, \
                blk_size-1);

        blk_queue_max_segments(gl_emmcDevice[uiPartIdx]->queue, NO_OF_SCATTER);

        blk_queue_max_hw_sectors(gl_emmcDevice[uiPartIdx]->queue, blk_size);

        blk_queue_max_segment_size(gl_emmcDevice[uiPartIdx]->queue, \
            MAX_SEGMENT_SIZE);
#endif /* __GLEN */

        /* Update Request Q info in to emmc global structure and vice versa */
        gl_emmcDevice[uiPartIdx]->queue->queuedata = gl_emmcDevice[uiPartIdx];

        gl_emmcDevice[uiPartIdx]->gen_disk->queue = \
                gl_emmcDevice[uiPartIdx]->queue;

        gl_emmcDevice[uiPartIdx]->gen_disk->flags |= GENHD_FL_REMOVABLE;

        gl_emmcDevice[uiPartIdx]->gen_disk->private_data = \
                gl_emmcDevice[uiPartIdx];

        /* set the emmc device capacity in to generic disk */
        set_capacity(gl_emmcDevice[uiPartIdx]->gen_disk, uiSectCnt);
        _EMMCBLK_OPTIONAL_DEBUG_MSG("device capacity is %d sectors", uiSectCnt);

        /* Scatter gather is applicable only for ADMA2 */
        if(_COM_MODE_ADMA2 == trans_mode)
        {
            /* Create scatter gather list memory */
            gl_emmcDevice[uiPartIdx]->sg = \
                kcalloc(NO_OF_SCATTER, sizeof(struct scatterlist), GFP_KERNEL);

            /* Create scatter gather list memory */
            gl_emmcDevice[uiPartIdx]->sgList.paEle = \
                kcalloc(NO_OF_SCATTER, sizeof(com_sg_t), GFP_KERNEL);

            /* Validation for scatter gather list */
            if((NULL == gl_emmcDevice[uiPartIdx]->sg) ||
               (NULL == gl_emmcDevice[uiPartIdx]->sgList.paEle))
            {
                blk_cleanup_queue(gl_emmcDevice[uiPartIdx]->queue);
                put_disk(gl_emmcDevice[uiPartIdx]->gen_disk);
                kfree(gl_emmcDevice[uiPartIdx]);
                _EMMCBLK_ERROR_DEBUG_MSG(\
                    "Scatter Gather table creation fails");

                blk_ret = -1;
                break;
            }

            /* Initialize block device scatter list */
            sg_init_table(gl_emmcDevice[uiPartIdx]->sg, NO_OF_SCATTER);
        }

        /* create supporting thread for request Q */
        sema_init(&gl_emmcDevice[uiPartIdx]->thread_sem, 1);

        gl_emmcDevice[uiPartIdx]->thread = kthread_run(
            emmcDevice_queue_thread, gl_emmcDevice[uiPartIdx],
            "emmcthrd");

        /* Validation for Kernel Thread */
        if(IS_ERR(gl_emmcDevice[uiPartIdx]->thread))
        {
            blk_cleanup_queue(gl_emmcDevice[uiPartIdx]->queue);
            put_disk(gl_emmcDevice[uiPartIdx]->gen_disk);
            /* Release Scatter Gather memory */
            if(_COM_MODE_ADMA2 == trans_mode)
            {
                kfree(gl_emmcDevice[uiPartIdx]->sg);
                kfree(gl_emmcDevice[uiPartIdx]->sgList.paEle);
            }
            kfree(gl_emmcDevice[uiPartIdx]);

            _EMMCBLK_ERROR_DEBUG_MSG(\
                "Block Driver Thread Fails for partition %d", uiPartIdx);

            blk_ret = -1;
            break;
        }

        /* update partition ID in to the device */
        gl_emmcDevice[uiPartIdx]->uiPartIdx = uiPartIdx;

        /* Create eMMC block IO device */
        add_disk(gl_emmcDevice[uiPartIdx]->gen_disk);

        /* Move to next partition */
        ++uiPartIdx;
    }while(uiPartIdx < _COM_PARTITION_MAX);

    if(blk_ret)
    {
        --uiPartIdx;
        while((int)uiPartIdx >= 0)
        {
            /* Clean block driver q and nodes */
            emmcblk_cleanNode(gl_emmcDevice[uiPartIdx]);
            --uiPartIdx;
        }

        unregister_blkdev(major_num, acDevId);
        emmc_exit();
        _EMMCBLK_OPTIONAL_DEBUG_MSG("Block driver fails");
#ifdef CONFIG_PM
        platform_driver_unregister(&mmctsip_driver);
#endif /* CONFIG_PM */
        return -1;
    }

    _EMMCBLK_OPTIONAL_DEBUG_MSG("emmc_init() success");

    return 0;
}

/**
 * @brief Deinitializing block driver, Request Q and eMMC device
 *
 * This routine is used in module_exit to do the rmmod
 *
 * @param none
 *
 * @retval none
 */
static void __exit emmcblk_exit(void)
{
    unsigned int uiPartIdx = 0;

    do
    {
        /* Clean block driver q and nodes */
        emmcblk_cleanNode(gl_emmcDevice[uiPartIdx]);
        ++uiPartIdx;

    } while(uiPartIdx < _COM_PARTITION_MAX);

    /* Un register block device */
    unregister_blkdev(major_num, EMMC_DEVICE_NAME);

    /* Deinitialize eMMC device */
    emmc_exit();
    _EMMCBLK_OPTIONAL_DEBUG_MSG("called");

#ifdef CONFIG_PM
    platform_driver_unregister(&mmctsip_driver);
#endif /* CONFIG_PM */

    return;
}

/**
 * @brief cleanup block nodes
 *
 * This routine is used in emmcblk_exit
 *
 * @param[in] Block device pointer
 *
 * @retval none
 */
static void emmcblk_cleanNode(emmc_BlockDevice *emmcDevice)
{
    /* Cleanup is taken care only for the created partition */
    if(emmcDevice)
    {
        /* cleans up any partitioning information */
        del_gendisk(emmcDevice->gen_disk);
        /* Releases our reference to the gendisk */
        put_disk(emmcDevice->gen_disk);

        /* Cleanup Request Q thread */
        kthread_stop(emmcDevice->thread);
        send_sig(SIGKILL, emmcDevice->thread, 1);
        wake_up_process(emmcDevice->thread);

        /* Release kernel Request Q resources */
        blk_cleanup_queue(emmcDevice->queue);

        /* Scatter gather is applicable only for ADMA2 */
        if(_COM_MODE_ADMA2 == trans_mode)
        {
            /* Release scatter gather memory */
            kfree(emmcDevice->sg);
            kfree(emmcDevice->sgList.paEle);
        }

        /* Release global memory */
        kfree(emmcDevice);
    }
    return;
}

/**@}*/ // BLK_Functions

/** @addtogroup BLK_Macros BLK_Macros
 * @{
 */

module_init(emmcblk_init);
module_exit(emmcblk_exit);

/**@}*/ // BLK_Macros

/**@}*//* BlockDriver */
/**@}*//* TestApplication */

