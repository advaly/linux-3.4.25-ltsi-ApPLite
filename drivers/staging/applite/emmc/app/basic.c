/**
 * @file          basic.c
 *
 * \brief         Unit level functional test program.
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
 * @addtogroup UnitTesting
 * @{
 */

/*----------------------- Header Files Inclusions ---------------------------*/
#include "debug.h"
#include "emmc_api.h"
#include "os.h"
#include "config.h"

/*-------------------------- Macro Definitions ------------------------------*/

/** @addtogroup UT_DEFINES UT_DEFINES
 * @{
 */

#define DRIVER_DESCRIPTION   "eMMC unittest driver"
#define COMPANY_NAME         "TSIP"
#ifdef __GLEN
#define TRANSFER_UNIT        (8 * _BLK_SIZE) /* 4096 */
#else /* !__GLEN */
#define TRANSFER_UNIT        (_BLK_SIZE)
#endif /* __GLEN */
#define MAX_SEGMENT_SIZE    32768
#define NO_OF_SCATTER       page_no
#define MAGIC_DATA          0x12

/**@}*/ // UT_DEFINES

/*-------------------------- Enum Definitions --------------------------------*/

/*------------------ Data Structures & Custom Typedefs -----------------------*/

/*------------------------------ Externs -------------------------------------*/

/*---------------------------- Prototypes ------------------------------------*/

/*------------- Data variable/Structure allocation (global) -----------------*/

/** @addtogroup UT_Globals UT_Globals
 * @{
 */

static int transfer = 1;    /* Data transfer is enabled by default */
static unsigned int freq = 100000000;
static unsigned int buswidth = _COM_BWIDTH_8;
static unsigned int trans_mode = _COM_MODE_ADMA2;
static unsigned int page_no = 1;
static unsigned int trans_size = TRANSFER_UNIT; /* Multiples of 512 */
/* Device address above 9MB */
static unsigned int dev_adr = 0;
static unsigned int perf_loop = 1;
static unsigned int part_no = 0;
static int dbg = _DZ_LEVEL1;           /* Enable debug zones */

/* Variables to be used in the driver code */
static struct dma_pool *dmaPool = NULL;
static void **cpu_ptr;
static com_sglist_t sgList;

/**@}*/ // UT_Globals

/** @addtogroup UT_Macros UT_Macros
 * @{
 */

module_param(transfer, int, 0);
MODULE_PARM_DESC(transfer, \
    "Device should transfer the data (1: YES, 0:NO)");

module_param(freq, int, 0);
MODULE_PARM_DESC(freq, \
    "eMMC operating frequency (400000Hz to 50000000Hz): Default is 400KHz");

module_param(buswidth, int, 0);
MODULE_PARM_DESC(buswidth, \
    "eMMC bus width (0: 8bit, 1:4bit, 2:1bit [default])");

module_param(trans_mode, int, 0);
MODULE_PARM_DESC(trans_mode, \
    "Data trans Mode (0:PIO [default], 1:SDMA, 2:ADMA2)");

module_param(trans_size, int, 0);
MODULE_PARM_DESC(trans_size, \
    "Data transfer size (in multiple of 4KB): Default is 4KB");

module_param(page_no, int, 0);
#ifdef __GLEN
MODULE_PARM_DESC(page_no, "Number of pages of size 4096 bytes");
#else /* !__GLEN */
MODULE_PARM_DESC(page_no, "Number of pages of size 512 bytes");
#endif /* __GLEN */

module_param(perf_loop, int, 0);
MODULE_PARM_DESC(perf_loop, "Check the performance using loop count");

module_param(part_no, int, 0);
MODULE_PARM_DESC(part_no, \
    "Select partition for data transaction (1 to 5)");

module_param(dbg, int, 0);
MODULE_PARM_DESC(dbg, "Debug Zone (def:1: L1, 3:L2, 7:L3 0xFFFFFFF:All)");

/**@}*/ // UT_Macros

/*----------------------- Function Definitions -------------------------------*/

/** @addtogroup UT_Functions UT_Functions
 * @{
 */

/**
 * @brief Function to create Scatter Gather list for the given segment size
 * and total Scatter Gather elements. This function applicable only for ADMA2
 *
 * @param[in] ulSegSize     size of the individual segment, multiples of 4K
 * @param[in] ulTotalSgEle  Number of element in the list
 *
 * @retval 0xFFFFFFFF If any memory error occurs
 * @retval others     number of allocated elements
 */
static _ub32 emmcunit_createScatterGatherList(
    unsigned long ulSegSize,
    unsigned long ulTotalSgEle)
{
    dma_addr_t dma_handle;
    unsigned char *pW = NULL;
    int i = 0;
    int j = 0;

    /* Calculate total transfer size */
    trans_size = ulSegSize * ulTotalSgEle;

    /* Allocate memory for SG element list */
    sgList.paEle = (com_sg_t *)kzalloc(
            ulTotalSgEle*sizeof(com_sg_t), GFP_KERNEL);
    if(NULL == sgList.paEle)
    {
        dz_print(_DZ_CRTICAL, "Memory sgList.paEle fails\n");
        return -1;
    }

    /* Allocate memory to maintain virtual addresses for DMA memory */
    cpu_ptr = (void **)kzalloc(
            ulTotalSgEle*sizeof(void*), GFP_KERNEL);
    if(NULL == cpu_ptr)
    {
        dz_print(_DZ_CRTICAL, "Memory cpu_ptr fails\n");
        return -1;
    }

    /* Reserve dma pool of memory to create SG data chunk list */
    dmaPool = dma_pool_create(
        "emmc_sg",          /* name of scatter gather pool */
        NULL,               /* device id is NULL */
        ulTotalSgEle,       /* Number element used in scatter gather list */
        ulSegSize,          /* single element size in bytes */
        0);                 /* 0: No boundary crossing in reserved buffer seg */

    if(NULL == dmaPool)
    {
        dz_print(_DZ_CRTICAL, "SG Memory Pool Error\n");
        kfree(sgList.paEle);
        return -1;
    }
    dz_print(_DZ_INFO, "Transaction Size is %d Bytes\n", trans_size);

    /* Create SG list using DMA pool */
    for(j=0; j<ulTotalSgEle; j++ )
    {
        /*
         * Allocate dma memory for SG data chunks from reserved dma pool
         * Maintain corresponding virtual addresses in to global array, this
         * is used while initializing and cleaning the memory
         */
        pW = cpu_ptr[j] = dma_pool_alloc(dmaPool, GFP_KERNEL, &dma_handle);
        if(pW)
        {
            /* Assign dma address and size in to driver SG array list */
            sgList.paEle[j].dmaAddr = dma_handle;
            sgList.paEle[j].uiSize  = ulSegSize;

            /* Initialize buffer with some valid data for integirty test */
            for(i = 0; i < ulSegSize; i++)
            {
                pW[i] = MAGIC_DATA;
            }
        }
        else
        {
            /*
             * If dmapool allocate fails, SG elements limited up to the
             * available size
             */
            trans_size = ulSegSize * j;
            dz_print(_DZ_INFO, "Modified Transaction Size is %d Bytes\n",
                    trans_size);
            break;
        }

        dz_print(_DZ_INFO, "%d cadr[0x%08lX] dadr[0x%08X] Sz[%d]\n",
                j, (unsigned long)cpu_ptr[j], sgList.paEle[j].dmaAddr,
                sgList.paEle[j].uiSize);
    }

    /* Store total created element in to driver SG struct */
    sgList.uiTotal = j;

    return j;
}

/**
 * @brief Function to delete Scatter Gather list for the given segment size
 * and total Scatter Gather elements moreover data integrity also validated
 * before delete the elements. This function applicable only for ADMA2
 *
 * @param[in] ulSegSize     size of the individual segment, multiples of 4K
 * @param[in] ulTotalSgEle  Number of element in the list
 *
 * @retval None
 */
static void emmcunit_deleteScatterGatherList(
    unsigned long ulSegSize,
    unsigned long ulTotalSgEle)
{
    unsigned char *pR = NULL;
    int i = 0;
    int j = 0;
    int errFlag = 0;

    /* Data comparison */
    for(j=0; j<sgList.uiTotal; j++ )
    {
        /* Get buffer pointer from global storage */
        pR = cpu_ptr[j];
        if(pR)
        {
            /* Initialize Read buffer with zero data */
            for(i = 0; i < ulSegSize; i++)
            {
                /* If read data is not same as written data */
                if(pR[i] != MAGIC_DATA)
                {
                    dz_print(_DZ_CRTICAL,
                        "Error: Data comparison failed at %d offset[0x%08x].\n",
                        j, i);

                    /* Update error flag */
                    errFlag = 1;

                    /* break inner and outer loops */
                    j = sgList.uiTotal;
                    break;
                }
            }
        }
        else
        {
            /* If pointer is NULL break the loop */
            break;
        }
    }

    /* If no error, print success */
    if(0 == errFlag)
    {
        dz_print(_DZ_CRTICAL, "Transaction successful\n");
    }

    /* Free DMA SG buffers */
    for(j=0; j<sgList.uiTotal; j++ )
    {
        dma_pool_free(dmaPool, cpu_ptr[j], sgList.paEle[j].dmaAddr);
        cpu_ptr[j] = NULL;
    }

    /* Free DMA reserved pool */
    dma_pool_destroy(dmaPool);
    dmaPool = NULL;

    /* Free virtual address memory */
    kfree(cpu_ptr);
    cpu_ptr = NULL;

    /* Free Driver SG element memory */
    kfree(sgList.paEle);
    sgList.paEle = NULL;
}

/**
 * @brief Function to clear the data in Scatter Gather list for the given
 * segment size and total Scatter Gather elements. This function applicable
 * only for ADMA2
 *
 * @param[in] ulSegSize     size of the individual segment, multiples of 4K
 * @param[in] ulTotalSgEle  Number of element in the list
 *
 * @retval None
 */
static void emmcunit_clearScatterGatherData(
    unsigned long ulSegSize,
    unsigned long ulTotalSgEle)
{
    unsigned char *pR = NULL;
    int i = 0;
    int j = 0;

    /* Traverse to all Scatter Gather elements */
    for(j=0; j<sgList.uiTotal; j++ )
    {
        /* Get virtual address for the element */
        pR = cpu_ptr[j];
        if(pR)
        {
            /* Initialize Read buffer with zero data */
            for(i = 0; i < ulSegSize; i++)
            {
                pR[i] = 0x0;
            }
        }
        else
        {
            /* break if memory is end */
            j++;
            break;
        }
    }
    dz_print(_DZ_INFO, "SG Entry is %d\n", j);
    return;
}

/**
 * @brief Function to return memory to kernel and exit from the emmc driver.
 * Applicable irrespective of mode
 *
 * @param[in] pWriteBuf Write buffer address
 * @param[in] pReadBuf  Read buffer address
 *
 * @retval None
 */
static void emmcunit_cleanup(
    void *pWriteBuf,
    void *pReadBuf)
{
    /* Return ADMA2 Memory to kernel */
    if(_COM_MODE_ADMA2 == trans_mode)
    {
        emmcunit_deleteScatterGatherList(MAX_SEGMENT_SIZE, NO_OF_SCATTER);
    }
    else
    {
        /* Return PIO and SDMA memory to kernel */
        kfree(pReadBuf);
        kfree(pWriteBuf);
    }

    /* Exit from emmc driver */
    emmc_exit();
}

/**
 * @brief Unit Test driver initialization for eMMC device
 * This is the entry function for eMMC functional unit test driver
 *
 * This will initialize the eMMC device with host controller
 * This function will be invoked while insmod for the driver
 * since unit testing data transaction also part of driver
 * initialization
 *
 * @param none
 *
 * @retval NOERROR for successful initialization
 * @retval ERROR for failure
 */
static int __init driver_initialize(void)
{
    emmc_sts_e ret = _EMMC_STS_OK;
    void *pWriteBuf = NULL;
    void *pReadBuf = NULL;
    unsigned int i = 0;
    unsigned int uiVersion;
    unsigned int uiSectCnt = 0;
    unsigned char *pR = NULL;
    unsigned char *pW = NULL;
    _ub32 uiPartNum = 0;
    com_csd_params_t CSDParams;
    com_cid_params_t CIDParams;

    /* Enable logging */
    debug_setZone(dbg);
    emmc_getVersion(&uiVersion);

    printk("\n");
    printk("*********************************************************\n");
    printk("             eMMC Driver Unit Testing                    \n");
    printk("  TOSHIBA Corporation Semiconductor and Storage Company  \n");
    printk("            2010-2015 All rights reserved                \n");
    printk("           eMMC Driver Version 0x%08X\n",         uiVersion );
    printk("*********************************************************\n");

    /*
     * If mode is ADMA2 allocate and frame the Scatter Gather List as per
     * driver interface. The same list is used for read and write operation.
     * Constant value "MAGIC_DATA" is written in to the device, after write
     * completes, buffer clears with 0 and read from the device from same offset
     */
    if(_COM_MODE_ADMA2 == trans_mode)
    {
        if(-1 == emmcunit_createScatterGatherList(
            MAX_SEGMENT_SIZE, NO_OF_SCATTER))
        {
            dz_print(_DZ_CRTICAL, "SG Creation Fails\n");
            return -1;
        }

        /* Write and read pointers points in to same Scatter Gather list */
        pWriteBuf = pReadBuf = (void *)&sgList;
    }
    else
    {
        /* Other than ADMA2 total size is calculated with page_no */
        trans_size = (page_no * TRANSFER_UNIT);

        /* Allocate write buffer with zero data */
        pWriteBuf = kzalloc(trans_size, GFP_KERNEL);
        if(NULL == pWriteBuf)
        {
            dz_print(_DZ_CRTICAL, "Error: Memory allocation failed (write)!\n");
            return ret;
        }

        /* Initialize Write buffer with non-zero data */
        pW = (unsigned char *)pWriteBuf;
        for(i = 0; i < trans_size; i++)
        {
            pW[i] = MAGIC_DATA;
        }

        /* Allocate read buffer with zero data */
        pReadBuf = kzalloc(trans_size, GFP_KERNEL);
        if(NULL == pReadBuf)
        {
            kfree(pWriteBuf);
            dz_print(_DZ_CRTICAL, "Error: Memory allocation failed (read)!\n");
            return ret;
        }
    }

    /* Initialize the eMMC driver */
    ret = emmc_init();
    if(_EMMC_STS_OK != ret)
    {
        dz_print(_DZ_CRTICAL, "Error: emmc_init() failed code[0x%08x].\n", ret);
        emmcunit_cleanup(pWriteBuf, pReadBuf);
        return ret;
    }

    dz_print(_DZ_CRTICAL, ".....emmc_unit driver inserted successfully..!!\n");

    /* Get UDA partition size */
    ret = emmc_getDevMaxSect(0, &uiSectCnt);
    if(_EMMC_STS_OK == ret)
    {
        dz_print(_DZ_CRTICAL, "Total Device size in sectors %d\n", uiSectCnt);

        dz_print(_DZ_CRTICAL, "Total Device size is %dMB\n",
                 (uiSectCnt/2048));
    }

    ret = emmc_getDevInfo_CSD(0, &CSDParams);
    if(_EMMC_STS_OK != ret)
    {
        dz_print(_DZ_CRTICAL, \
            "Error: emmc_getDevInfo_CSD() failed code[0x%08x].\n", ret);
    }

    ret = emmc_getDevInfo_CID(0, &CIDParams);
    if(_EMMC_STS_OK != ret)
    {
        dz_print(_DZ_CRTICAL, \
            "Error: emmc_getDevInfo_CID() failed code[0x%08x].\n", ret);
    }

    if(1 == transfer)
    {
        /* Configure the eMMC driver */
        ret = emmc_setBusWidth(0, (com_busWidth_e)buswidth);
        ret |= emmc_setOpMode(0, (com_modes_e)trans_mode);
        ret |= emmc_setClock(0, freq);
        ret |= emmc_setConfig(0);
        if(_EMMC_STS_OK != ret)
        {
            dz_print(_DZ_CRTICAL, \
                "Error: emmc_setConfig() failed code[0x%08x].\n", ret);
            emmcunit_cleanup(pWriteBuf, pReadBuf);
            return ret;
        }

        /* Set device focus to requested partition */
        ret = emmc_getCurrPartition(0, &uiPartNum);
        if(uiPartNum != part_no)
        {
            ret |= emmc_accessPartitions(0, part_no);
            if(_EMMC_STS_OK != ret)
            {
                dz_print(_DZ_CRTICAL, \
                    "Error: emmc_AccessPartitions() failed code[0x%08x].\n", ret);
                emmcunit_cleanup(pWriteBuf, pReadBuf);
                return ret;
            }
        }

        dz_print(_DZ_INFO, "eMMC write initiated\n");
        /* To check performance same data buffer writes multiple times */
        for(i = 0; i < perf_loop; i++)
        {
            /* Write operation for slot-0 */
            ret = emmc_write(0, (_ub8 *)pWriteBuf, trans_size, dev_adr);
            if(_EMMC_STS_OK != ret)
            {
                dz_print(_DZ_CRTICAL, \
                    "Error: emmc_write() failed code[0x%08x].\n", ret);
                emmcunit_cleanup(pWriteBuf, pReadBuf);
                return ret;
            }
        }
        dz_print(_DZ_INFO, "Measure Write Performance\n");

        /* Clear ReadBuffer */
        if(_COM_MODE_ADMA2 == trans_mode)
        {
            emmcunit_clearScatterGatherData(MAX_SEGMENT_SIZE, NO_OF_SCATTER);
        }

        dz_print(_DZ_INFO, "eMMC Read initiated\n");
        /* To check performance same data buffer reads multiple times */
        for(i = 0; i < perf_loop; i++)
        {
            /* Read operation for slot-0 */
            ret = emmc_read(0, (_ub8 *)pReadBuf, trans_size, dev_adr);
            if(_EMMC_STS_OK != ret)
            {
                dz_print(_DZ_CRTICAL, \
                    "Error: emmc_read() failed code[0x%08x].\n", ret);
                emmcunit_cleanup(pWriteBuf, pReadBuf);
                return ret;
            }
        }

        /* Data Compare and free up the memory */
        if(_COM_MODE_ADMA2 == trans_mode)
        {
            emmcunit_deleteScatterGatherList(MAX_SEGMENT_SIZE, NO_OF_SCATTER);
        }
        else
        {
            /* Data integrity check */
            pR = (unsigned char *)pReadBuf;
            pW = (unsigned char *)pWriteBuf;

            for(i = 0; i < trans_size; i++)
            {
                if(pR[i] != pW[i])
                {
                    dz_print(_DZ_CRTICAL,
                        "Error: Data comparison failed at offset[0x%08x].\n", i);
                    break;
                }
            }

            if(i == trans_size)
            {
                dz_print(_DZ_CRTICAL, \
                    "Data comparison Passed with size[0x%08x]\n", trans_size);

                dz_print(_DZ_CRTICAL, "Transaction successful\n");
            }

            /* Deallocate other than ADMA2 resources */
            kfree(pReadBuf);
            kfree(pWriteBuf);
        }
    }

    return 0;
}

/**
 * @brief Unit test driver Deinitialization for eMMC device
 *
 * This will deinitialize the eMMC device and host controller
 * This function will be invoked while rmmod for the driver
 *
 * @param none
 *
 * @retval none
 */
static void __exit driver_exit(void)
{
    dz_print(_DZ_INFO, "... relaxing emmc unittest driver!\n");

    emmc_exit();
}

/**@}*/ // UT_Functions

/** @addtogroup UT_Macros UT_Macros
 * @{
 */

module_init(driver_initialize);
module_exit(driver_exit);
MODULE_DESCRIPTION(DRIVER_DESCRIPTION);
MODULE_AUTHOR(COMPANY_NAME);
MODULE_LICENSE("GPL");

/**@}*/ // UT_Macros

/**@}*//* UnitTesting */
/**@}*//* TestApplication */

