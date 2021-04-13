/**
 * @file          bm.c
 *
 * \brief         Includes Buffer management API implementation.
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
 * @addtogroup BufferManagement
 * @{
 */

/*----------------------- Header Files Inclusions ---------------------------*/
#include "bm.h"
#include "debug.h"   /* logging */
#include "intr.h"    /* handler registration */
#include "ra.h"      /* buffer register access */
#include "hc_api.h"  /* host controller services */

/*-------------------------- Macro Definitions ------------------------------*/

/** @addtogroup BM_DEFINES BM_DEFINES
 * @{
 */

/* Debug prints definitions */
#ifdef __DEBUG
#define _BM_DBG_INFO(__format__, arg...)    \
    dz_print(_DZ_BUF, "[%4d]%s::" __format__"\n", __LINE__,    \
    __FUNCTION__,## arg )

#define _BM_DBG_ERR(__format__, arg...)    \
    dz_print(_DZ_CRTICAL, "[%4d]%s::" __format__"\n", __LINE__,    \
    __FUNCTION__,## arg )
#else
#define _BM_DBG_INFO(__format__, arg...)
#define _BM_DBG_ERR(__format__, arg...)
#endif

/* Helper Macros for checking internal buffer state */
#define IS_BUF_RD_READY(s) (hc_getPresentState(s) & 0x00000800) /* bit[11] */
#define IS_BUF_WR_READY(s) (hc_getPresentState(s) & 0x00000400) /* bit[10] */

#define _TABLE_SIZE         4096            /* ADMA2 descriptor table size */
#define _MAX_DESC_LINES     (_TABLE_SIZE/8) /* Max descriptor lines (512) */
#define _FILL_DESC_LINES  (_MAX_DESC_LINES-1) /* Max descriptor lines (511) */
#define _DMA_TRANS_SIZE   4096                /* Default transfer size for DMA*/
#define _ADMA2_DESC_ENTRY (511+512)           /* Max ADMA2 two table size */

#define _ADMA2_ATTRIB_LINK  0x30              /* Desc is link entry */
#define _ADMA2_ATTRIB_TRAN  0x20              /* Desc is transaction entry */
#define _ADMA2_ATTRIB_INTR  0x04              /* Desc raise the interrupt */
#define _ADMA2_ATTRIB_END   0x02              /* Desc transaction is End */
#define _ADMA2_ATTRIB_VALID 0x01              /* Valid descriptor line */

#define _FILL_BOTH_BUF      0x00
#define _FILL_SINGLE_BUF    0x01

/**@}*/ //end of BM_DEFINES

/*-------------------------- Enum Definitions -------------------------------*/

/** @addtogroup BM_Enums BM_Enums
 * @{
 */

/**
 * @brief ADMA2 Descriptor table indices
 *
 * These are used for double buffering concept
 * for ADMA2. After ADMA2 descriptor line processing, status will be notified
 * to host. This notification can be controlled by INT bit in every ADMA2
 * descriptor line. Descriptor table 512th entry interrupt can be used if user
 * requested transaction size is more than two table size(511+511 entries).
 * Note:
 * 1. 512 entries can be configured in single descriptor table
 * 2. 511+512 entries can be configured in two tables (512th entry in first
 * table is link entry to the next table)
 * 3. 511+511 entries can be configured if entries are more than 1022 entries.
 * (After processing 512th entry of the table, the interrupt will be raised,
 * in the handler same table descriptor lines will be updated)
 */
typedef enum tag_adma_tbl_e
{
    _ADMA_TBL_0     = 0x0,  /**< ADMA Table Index 0 */
    _ADMA_TBL_1     = 0x1,  /**< ADMA Table Index 1 */
    _ADMA_TBL_MAX   = 0x2,  /**< ADMA Maximum Table */
}adma_tbl_e;

/**@}*/ //end of BM_Enums

/*------------------ Data Structures & Custom Typedefs ----------------------*/

/** @defgroup BM_Structures BM_Structures
 * @{
 */

/**
 * @brief Structure for PIO data transfer
 */
typedef struct
{
    _ub8 *pucBuf;    /**< Host buffer pointer(Virtual) */
    _ub32 uiOffset;  /**< Running offset info */
    _ub32 uiSize;    /**< Total transfer size */
    _ub32 uiSlot;    /**< Slot number information */
}bm_pio_t;

/**
 * @brief Structure for SDMA data transfer
 */
typedef struct
{
    _ub8 *pucBuf;          /**< Host buffer pointer(Virtual) */
    _ub32 uiDAdr;          /**< DMA address */
    _ub32 uiOffset;        /**< Running size offset info */
    _ub32 uiSize;          /**< Total transfer size */
    _ub32 uiSlot;          /**< Slot number information */
    com_RWDir_e direction; /**< Read/Write direction */
    _ub32 uiRemSize;       /**< Remaining size */
}bm_sdma_t;

/**
 * @brief Structure for ADMA2 data transfer
 */
typedef struct
{
    _ub32 uiOffset;        /**< Running size offset info */
    _ub32 uiIndex;         /**< Running SG element index info */
    _ub32 uiRemSize;       /**< Remaining size for the transaction */
    _ub32 uiRemIndex;      /**< Remaining SG element index to be processed */
    adma_tbl_e eTabId;     /**< Active ADMA2 Descriptor table ID */
    com_sglist_t *pList;   /**< User pointer for scatter gather */
}bm_adma2sg_t;

/**
 * @brief ADMA2 descriptor structure
 */
typedef struct
{
    _ub16 usAttr;      /**< Descriptor table attributes */
    _ub16 usLen;       /**< Descriptor table length */
    _ub32 uiPhy;       /**< Descriptor table address */
}bm_adma2desc_t;

/**@}*/ // BM_Structures

/*------------------------------ Externs ------------------------------------*/

/*---------------------------- Prototypes -----------------------------------*/

/** @addtogroup BM_Prototypes BM_Prototypes
 * @{
 */

static bm_sts_e transferPIO(
    _ub32 uiSlot,
    _ub8 *pucBuf,
    _ub32 uiSize);

static bm_sts_e transferSDMA(
    _ub32 uiSlot,
    _ub8 *pucBuf,
    _ub32 uiSize,
    com_RWDir_e direction);

static bm_sts_e cleanupSDMA(
    _ub32 uiSlot,
    _ub8 *pucBuf,
    _ub32 uiSize,
    com_RWDir_e direction);

static bm_sts_e transferADMA2(
    _ub32 uiSlot,
    _ub8 *pucBuf,
    _ub32 uiSize,
    com_RWDir_e direction);

static bm_sts_e cleanupADMA2(
    _ub32 uiSlot,
    _ub8 *pucBuf,
    _ub32 uiSize,
    com_RWDir_e direction);

static void readPIO(void *pArg);
static void writePIO(void *pArg);
static void handleSDMA(void *pArg);
static void fillADMA2Desc(bm_adma2sg_t *admaSg, int flag);
static void handleADMA(void *pArg);
static int fillADMA2Table(
    bm_adma2sg_t *admaSg,
    com_sg_t *paSg,
    bm_adma2desc_t **ptr,
    int sgStartIndex,
    int sgEndIndex);

/**@}*/ // BM_Prototypes

/*------------- Data variable/Structure allocation (global) -----------------*/

/** @addtogroup BM_Globals BM_Globals
 * @{
 */

static bm_pio_t bm_pio;
static bm_sdma_t bm_sdma;
static bm_adma2sg_t bm_adma2sg;

/* Global variables for ADMA2 descriptor tables */
static void *pCpuAddrTbl[_ADMA_TBL_MAX]  = {NULL, NULL};
static _ub32 uiDmaAddrTbl[_ADMA_TBL_MAX] = {0,0};

/**@}*/ // BM_Globals

/*----------------------- Function Definitions ------------------------------*/

/** @addtogroup BM_Functions BM_Functions
 * @{
 */

/**
 * @brief Initialization routine for buffer management module.
 *
 * Initializes the data handling structure members and register the ISRs for
 * read and write routines.
 *
 * @param None
 *
 * @retval _BM_STS_OK If no error.
 * @retval _BM_INTR_ERR when interrupt registration fails
 */
bm_sts_e bm_init(void)
{
    intr_sts_e ret;
    os_sts_e sts = _OS_OK;
    adma_tbl_e tbl_idx;

/*--------------------------------- PIO --------------------------------------*/
    /* Initialize PIO structure */
    bm_pio.uiSlot = 0;
    bm_pio.pucBuf = NULL;
    bm_pio.uiSize = 0;
    bm_pio.uiOffset = 0;

    /* register read handler for PIO mode for slot-0 */
    ret = intr_registerHdlr(_NORM_INTR_RD_PIO, readPIO, (void *)&bm_pio, 0);
    if(_INTR_OK != ret)
    {
        return _BM_INTR_ERR;
    }

    /* register write handler for PIO mode for slot-0 */
    ret = intr_registerHdlr(_NORM_INTR_WR_PIO, writePIO, (void *)&bm_pio, 0);
    if(_INTR_OK != ret)
    {
        /* deregister read handler for PIO mode for slot-0 */
        intr_deregisterHdlr(_NORM_INTR_RD_PIO, 0);
        return _BM_INTR_ERR;
    }

/*-------------------------------- SDMA --------------------------------------*/

    /* Input args not verified in this function. */
    /* Initialize SDMA structure */
    bm_sdma.uiSlot = 0;
    bm_sdma.pucBuf = NULL;
    bm_sdma.uiDAdr = 0;
    bm_sdma.uiSize = 0;
    bm_sdma.uiOffset = 0;
    bm_sdma.direction = _COM_DIR_R;

    /* register read handler for DMA mode for slot-0 */
    ret = intr_registerHdlr(_NORM_INTR_DMA, handleSDMA, (void *)&bm_sdma, 0);
    if(_INTR_OK != ret)
    {
        /* deregister write handler for PIO mode for slot-0 */
        intr_deregisterHdlr(_NORM_INTR_WR_PIO, 0);

        /* deregister read handler for PIO mode for slot-0 */
        intr_deregisterHdlr(_NORM_INTR_RD_PIO, 0);

        return _BM_INTR_ERR;
    }

/*-------------------------------- ADMA2 -------------------------------------*/
    /*
     * Allocate memory for ADMA2 descriptor tables:
     * get the physical and virtual address of the table.
     */
    for(tbl_idx=_ADMA_TBL_0; tbl_idx<_ADMA_TBL_MAX; ++tbl_idx)
    {
        sts |= os_allocDmem(
            &pCpuAddrTbl[tbl_idx], &uiDmaAddrTbl[tbl_idx], _TABLE_SIZE);
    }

    if(_OS_OK != sts)
    {
        for(; tbl_idx>=_ADMA_TBL_0; --tbl_idx)
        {
            os_freeDmem(
              pCpuAddrTbl[tbl_idx], uiDmaAddrTbl[tbl_idx], _TABLE_SIZE);

            pCpuAddrTbl[tbl_idx]  = NULL;
            uiDmaAddrTbl[tbl_idx] = 0;
        }

        /* deregister DMA handler for SDMA mode for slot-0 */
        intr_deregisterHdlr(_NORM_INTR_DMA, 0);

        /* deregister read handler for PIO mode for slot-0 */
        intr_deregisterHdlr(_NORM_INTR_RD_PIO, 0);

        /* deregister write handler for PIO mode for slot-0 */
        intr_deregisterHdlr(_NORM_INTR_WR_PIO, 0);

        _BM_DBG_ERR("Memory allocate for dsc table failed!");
        return _BM_STS_NG;
    }

    return _BM_STS_OK;
}

/**
 * @brief Cleanup routine for buffer management module.
 *
 * @param None
 *
 * @retval _BM_STS_OK If no error.
 * @retval _BM_STS_NG when any error occurs in deallocation
 */
bm_sts_e bm_exit(void)
{
    bm_sts_e eSts = _BM_STS_OK;
    adma_tbl_e tbl_idx;
    os_sts_e eOsSts;

/*-------------------------------- ADMA2 -------------------------------------*/
    for(tbl_idx=_ADMA_TBL_0; tbl_idx<_ADMA_TBL_MAX; ++tbl_idx)
    {
        eOsSts = os_freeDmem(
            pCpuAddrTbl[tbl_idx], uiDmaAddrTbl[tbl_idx], _TABLE_SIZE);
        if(_OS_OK != eOsSts)
        {
            _BM_DBG_ERR("ADMA Table Mem De-allocate failed");
            eSts = _BM_STS_NG;
        }

        pCpuAddrTbl[tbl_idx]    = NULL;
        uiDmaAddrTbl[tbl_idx]   = 0;
    }

/*----------------------------- SDMA/ADMA2 -----------------------------------*/
    /* deregister DMA handler for SDMA/ADMA2 mode for slot-0 */
    intr_deregisterHdlr(_NORM_INTR_DMA, 0);

/*--------------------------------- PIO --------------------------------------*/
    /* deregister read handler for PIO mode for slot-0 */
    intr_deregisterHdlr(_NORM_INTR_RD_PIO, 0);

    /* deregister write handler for PIO mode for slot-0 */
    intr_deregisterHdlr(_NORM_INTR_WR_PIO, 0);

    return eSts;
}

/**
 * @brief Buffer module configuration API before data transfer.
 *
 * @param[in] uiSlot slot number for Host controller.
 * @param[in] pucBuf Address of input buffer.
 * @param[in] uiSize input buffer size
 * @param[in] direction read/write direction
 *
 * @retval _BM_STS_OK If no error.
 * @retval _BM_STS_NG when any error occurs in data transfer or when any of the
 *         input arguments are not valid.
 */
bm_sts_e bm_config(
    _ub32 uiSlot,
    _ub8 *pucBuf,
    _ub32 uiSize,
    com_RWDir_e direction)
{
    com_modes_e mode;
    bm_sts_e ret = _BM_STS_OK;

    /* Input parameter verification */
    if(NULL == pucBuf)
    {
        _BM_DBG_INFO("Input buffer address is NULL");
        return _BM_STS_NG;
    }

    /* rest of the input parameter check is not done! */

    /* getting the mode of operation */
    mode = hc_getOpMode(uiSlot);
    switch(mode)
    {
        case _COM_MODE_PIO:
            ret = transferPIO(uiSlot, pucBuf, uiSize);
        break;

        case _COM_MODE_SDMA:
            ret = transferSDMA(uiSlot, pucBuf, uiSize, direction);
        break;

        case _COM_MODE_ADMA2:
            ret = transferADMA2(uiSlot, pucBuf, uiSize, direction);
        break;

        default:
            _BM_DBG_INFO("Mode is invalid.");
            ret = _BM_STS_NG;
        break;
    }

    return ret;
}

/**
 * @brief Buffer module de-configuration API after data transfer.
 *
 * @param[in] uiSlot slot number for Host controller.
 * @param[in] pucBuf Address of input buffer.
 * @param[in] uiSize input buffer size
 * @param[in] direction read/write direction
 *
 * @retval _BM_STS_OK If no error.
 * @retval _BM_STS_NG when any error occurs in data transfer or when any of the
 *         input arguments are not valid.
 */
bm_sts_e bm_deconfig(
    _ub32 uiSlot,
    _ub8 *pucBuf,
    _ub32 uiSize,
    com_RWDir_e direction)
{
    com_modes_e mode;
    bm_sts_e ret = _BM_STS_OK;

    /* Input parameter verification */
    if(NULL == pucBuf)
    {
        _BM_DBG_INFO("Input buffer address is NULL");
        return _BM_STS_NG;
    }

    /* rest of the input parameter check is not done! */

    /* getting the mode of operation */
    mode = hc_getOpMode(uiSlot);
    switch(mode)
    {
        case _COM_MODE_PIO:
            /* None as of now! */
        break;

        case _COM_MODE_SDMA:
            ret = cleanupSDMA(uiSlot, pucBuf, uiSize, direction);
        break;

        case _COM_MODE_ADMA2:
            ret = cleanupADMA2(uiSlot, pucBuf, uiSize, direction);
        break;

        default:
            _BM_DBG_INFO("Mode is invalid.");
            ret = _BM_STS_NG;
        break;
    }

    return ret;
}

/*-------------------- Static Function Definitions ---------------------------*/
/**
 * @brief preparation routine for PIO data transfer.
 *
 * Assigns the pio structure members with the slot number and input buffer
 * details.
 *
 * @param[in] uiSlot slot number for Host controller.
 * @param[in] pucBuf Address of input buffer.
 * @param[in] uiSize input buffer size
 *
 * @retval _BM_STS_OK If no error.
 */
static bm_sts_e transferPIO(
    _ub32 uiSlot,
    _ub8 *pucBuf,
    _ub32 uiSize)
{
    /* Input args not verified in this function. */

    /* Initialize PIO structure */
    bm_pio.uiSlot = uiSlot;
    bm_pio.pucBuf = pucBuf;
    bm_pio.uiSize = uiSize;
    bm_pio.uiOffset = 0;

    _BM_DBG_INFO("Inside PIO function");

    return _BM_STS_OK;
}

/**
 * @brief preparation routine for SDMA data transfer.
 *
 * @param[in] uiSlot slot number for Host controller.
 * @param[in] pucBuf Address of input buffer.
 * @param[in] uiSize input buffer size
 * @param[in] direction read/write direction
 *
 * @retval _BM_STS_OK If no error.
 * @retval _BM_STS_NG when any error occurs in data transfer
 */
static bm_sts_e transferSDMA(
    _ub32 uiSlot,
    _ub8 *pucBuf,
    _ub32 uiSize,
    com_RWDir_e direction)
{
    os_sts_e eSts = _OS_OK;
    _ub32 size = _DMA_TRANS_SIZE; /* default translation size */

    /* Input args not verified in this function. */

    /* Initialize SDMA structure */
    bm_sdma.uiSlot = uiSlot;
    bm_sdma.uiSize = uiSize;
    bm_sdma.uiOffset = 0;
    bm_sdma.pucBuf = pucBuf;
    bm_sdma.direction = direction;
    bm_sdma.uiRemSize = uiSize;

    if(uiSize >= _DMA_TRANS_SIZE)
    {
        size = _DMA_TRANS_SIZE;
    }
    else /* Transfer request less than 4KB */
    {
        size = uiSize;
    }

    /* Translate the first transfer chunk */
    eSts  = os_mapPhyAddr(
        &bm_sdma.uiDAdr,
        (_ub8 *)pucBuf,
        size,
        direction);
    if(eSts != _OS_OK)
    {
        return _BM_STS_NG;
    }
    /* Write into SDMA Address Register */
    hc_setDMAAdr(bm_sdma.uiSlot, bm_sdma.uiDAdr);

    /* Update offset with block transfer size */
    bm_sdma.uiOffset += size;
    bm_sdma.uiRemSize -= size;

    return _BM_STS_OK;
}

/**
 * @brief cleanup routine after SDMA data transfer.
 *
 * @param[in] uiSlot slot number for Host controller.
 * @param[in] pucBuf Address of input buffer.
 * @param[in] uiSize input buffer size
 * @param[in] direction read/write direction
 *
 * @retval _BM_STS_OK If no error.
 * @retval _BM_STS_NG when any error occurs in data transfer
 */
static bm_sts_e cleanupSDMA(
    _ub32 uiSlot,
    _ub8 *pucBuf,
    _ub32 uiSize,
    com_RWDir_e direction)
{
    os_sts_e eSts = _OS_OK;
    _ub32 size = _DMA_TRANS_SIZE; /* default translation size */

    /* Input args not verified in this function. */

    if(uiSize >= _DMA_TRANS_SIZE)
    {
        size = _DMA_TRANS_SIZE;
    }
    else /* Transfer request less than 4KB */
    {
        size = uiSize;
    }

    /* unmap the physical memory */
    eSts  = os_unmapPhyAddr(bm_sdma.uiDAdr, size, direction);
    if(eSts != _OS_OK)
    {
        return _BM_STS_NG;
    }
    return _BM_STS_OK;
}

/**
 * @brief preparation routine for ADMA2 data transfer.
 *
 * @param[in] uiSlot slot number for Host controller.
 * @param[in] pucBuf Address points to scatter gather list.
 * @param[in] uiSize total input scatters size in bytes
 * @param[in] direction read/write direction
 *
 * @retval _BM_STS_OK If no error.
 * @retval _BM_STS_NG when any error occurs in data transfer.
 */
static bm_sts_e transferADMA2(
    _ub32 uiSlot,
    _ub8 *pucBuf,
    _ub32 uiSize,
    com_RWDir_e direction)
{
    com_sglist_t *sgList = NULL;

    /* Input args not verified in this function. */

    /* get sglist from pointer input */
    sgList = (com_sglist_t *)pucBuf;

    /*
     * Initialize ADMA2 global values before starting transactions
     * uiRemSize initially holds total size of transactions, this will be
     * decreased for every descriptor configuration until reaches 0.
     * uiRemIndex initially holds total SG index for the transaction, this
     * also reduced every descriptor configuration, end of the successful
     * transaction this will be zero
     * uiIndex denotes current index for SG element, initially zero, will be
     * incremented every successful descriptor line configuration
     * eTabId denotes current table ID, initially pointed to 0th descriptor
     * table, from handler this will be 0 or 1.
     * pList point to SG list received from higher layer
     */
    bm_adma2sg.uiOffset  = 0;
    bm_adma2sg.uiRemSize = uiSize;
    bm_adma2sg.uiIndex   = 0;
    bm_adma2sg.uiRemIndex = sgList->uiTotal;
    bm_adma2sg.eTabId     = _ADMA_TBL_0;
    bm_adma2sg.pList      = sgList;

    /*
     * If total descriptor entries are exceeded two tables size, Register ADMA2
     * table configuration handler for slot-0
     */
    if(sgList->uiTotal > _ADMA2_DESC_ENTRY)
    {
        if(_INTR_OK != \
           intr_registerHdlr(_NORM_INTR_DMA, handleADMA, (void *)&bm_adma2sg, 0))
        {
            return _BM_INTR_ERR;
        }
    }
    fillADMA2Desc(&bm_adma2sg, _FILL_BOTH_BUF);

    /* Set the first table in to the register */
    hc_setDMAAdr(uiSlot, uiDmaAddrTbl[_ADMA_TBL_0]);

    return _BM_STS_OK;
}

/**
 * @brief cleanup routine after ADMA2 data transfer.
 *
 * @param[in] uiSlot slot number for Host controller.
 * @param[in] pucBuf Address of input buffer.
 * @param[in] uiSize input buffer size
 * @param[in] direction read/write direction
 *
 * @retval _BM_STS_OK If no error.
 */
static bm_sts_e cleanupADMA2(
    _ub32 uiSlot,
    _ub8 *pucBuf,
    _ub32 uiSize,
    com_RWDir_e direction)
{
    com_sglist_t *sgList = NULL;

    /* Input args not verified in this function. */

    /* get sglist from pointer input */
    sgList = (com_sglist_t *)pucBuf;
    if(sgList->uiTotal > _ADMA2_DESC_ENTRY)
    {
        intr_deregisterHdlr(_NORM_INTR_DMA, 0);
    }
    return _BM_STS_OK;
}

/**
 * @brief ISR for Device read by PIO mode
 *
 * @param[in] *pArg bm_pio_t structure pointer
 *
 * @retval none.
 */
static void readPIO(void *pArg)
{
    bm_pio_t *ptr = (bm_pio_t *)pArg;
    _ub32 *offset; /* running offset */
    _ub32 i = 0;
#ifdef __32BIT
    _ub32 addr;    /* start address */
    addr = (_ub32)ptr->pucBuf;    /* copy the reference to local space */
#else /* !__32BIT */
    _ub64 addr;    /* start address */
    addr = (_ub64)ptr->pucBuf;    /* copy the reference to local space */
#endif /* __32BIT */

    /* Input arguments are not verified as it will be done by upper layer */
    offset = (_ub32 *)&ptr->uiOffset;

    /* read from the internal buffer */
    /* block_size/4 = 128 for 512byte block*/
    for(i = 0; ((IS_BUF_RD_READY(ptr->uiSlot)) && (i < _BLK_SIZE/4)); i++)
    {
        /* transfer data from the internal buffer to user buffer */
        *(unsigned int *)(addr + *offset) = hc_getBufDatPort(ptr->uiSlot);
        *offset += 4; /* 32bit=4bytes */
    }

    /* Information Purpose */
    if(*offset == ptr->uiSize)
    {
        _BM_DBG_INFO("user buffer is full!");
    }
    else
    {
        /* assuming block size if 512bytes */
        _BM_DBG_INFO("Block Count ---> %d", ptr->uiOffset/_BLK_SIZE);
    }
}

/**
 * @brief ISR for Device write by PIO mode
 *
 * @param[in] *pArg bm_pio_t structure pointer
 *
 * @retval none.
 */
static void writePIO(void *pArg)
{
    bm_pio_t *ptr = (bm_pio_t *)pArg;
    _ub32 *offset; /* running offset */
    _ub32 i = 0;
#ifdef __32BIT
    _ub32 addr;    /* start address */
    addr = (_ub32)ptr->pucBuf;    /* copy the reference to local space */
#else /* !__32BIT */
    _ub64 addr;    /* start address */
    addr = (_ub64)ptr->pucBuf;    /* copy the reference to local space */
#endif /* __32BIT */

    /* input argument is not verified */

    /* copy the reference to local space */
    offset = (_ub32 *)&ptr->uiOffset;

    /* read from the internal buffer */
    /* block_size/4 = 128 for 512byte block*/
    for(i = 0; ((IS_BUF_WR_READY(ptr->uiSlot)) && (i < _BLK_SIZE/4)); i++)
    {
        /* transfer data from the user buffer to internal buffer */
        hc_setBufDatPort(ptr->uiSlot , *(unsigned int *)(addr + *offset));
        *offset += 4; /* 32bit=4bytes */
    }

    /* Information Purpose */
    if(*offset == ptr->uiSize)
    {
        _BM_DBG_INFO("user buffer is empty!");
    }
    else
    {
        /* assuming block size if 512bytes */
        _BM_DBG_INFO("Block Count ---> %d", ptr->uiOffset/_BLK_SIZE);
    }
}

/**
 * @brief ISR for Device read/write by SDMA mode
 *
 * @param[in] *pArg bm_sdma_t structure pointer
 *
 * @retval none.
 */
static void handleSDMA(void *pArg)
{
    os_sts_e eSts = _OS_OK;
    bm_sdma_t *ptr = (bm_sdma_t *)pArg;
    _ub32 size = _DMA_TRANS_SIZE; /* default translation size */

    /* Input args not verified in this function. */

    if(ptr->uiOffset == ptr->uiSize)
    {
        _BM_DBG_INFO("------------>Transfer done!");
        return;
    }
    else
    {
        _BM_DBG_INFO("------------>Handle SDMA");
    }

    /* unmap the physical memory */
    eSts  = os_unmapPhyAddr(ptr->uiDAdr, _DMA_TRANS_SIZE, ptr->direction);
    if(eSts != _OS_OK)
    {
        _BM_DBG_ERR("Error: os_unmapPhyAddr() in interrupt!");
        return;
    }

    if(ptr->uiRemSize >= _DMA_TRANS_SIZE)
    {
        size = _DMA_TRANS_SIZE;
    }
    else /* Transfer request less than 4KB */
    {
        size = ptr->uiRemSize;
    }

    /* Translate the next transfer chunk */
    eSts  = os_mapPhyAddr(
        &(ptr->uiDAdr),
        (_ub8 *)(ptr->pucBuf + ptr->uiOffset),
        size,
        ptr->direction);
    if(eSts != _OS_OK)
    {
        _BM_DBG_ERR("Error: os_mapPhyAddr() in interrupt!");
        return;
    }
    /* Write into SDMA Address Register */
    hc_setDMAAdr(ptr->uiSlot, ptr->uiDAdr);

    /* Update offset with block transfer size */
    ptr->uiOffset += size;
    ptr->uiRemSize -= size;
}

/**
 * @brief ISR for Device read/write by ADMA mode
 *
 * @param[in] *pArg bm_adma2sg_t structure pointer
 *
 * @retval none.
 */
static void handleADMA(void *pArg)
{
    bm_adma2sg_t *padma2Sg = (bm_adma2sg_t *)pArg;

    fillADMA2Desc(padma2Sg, _FILL_SINGLE_BUF);

    _BM_DBG_INFO("handle ADMA Idx[%d] Off[%d] RemSize[%d]",
        padma2Sg->uiRemIndex, padma2Sg->uiOffset, padma2Sg->uiRemSize);
}

/**
 * @brief ADMA2 descriptor table configuration function for read/write
 *
 * @param[in] *padma2Sg pointer to adma scatter gather list
 * @param[in] flag 0: called initially (fill both the tables)
 * 1: called from service routine (fill alternative tables)
 *
 * @retval none.
 */
static void fillADMA2Desc(bm_adma2sg_t *admaSg, int flag)
{
    com_sglist_t *sgList = NULL;
    com_sg_t *paSg = NULL;
    bm_adma2desc_t *ptr = NULL;
    int sgIndex = 0;
    int sgEndIndex = 0;

    /* get sglist from pointer input */
    sgList = admaSg->pList;
    paSg   = sgList->paEle;

    /* Read end index for the Scatter Gather element */
    sgEndIndex = sgList->uiTotal;
    if((0 == sgEndIndex) || (0 == admaSg->uiRemSize))
    {
        _BM_DBG_INFO("fillADMA2Desc No action");
        return;
    }

    /* get current SG index in to local variable */
    sgIndex = admaSg->uiIndex;

    /* ptr is point to current table descriptor line */
    ptr = (bm_adma2desc_t *)pCpuAddrTbl[admaSg->eTabId];

    _BM_DBG_INFO("Tb[%d] sgIndex[%d] loop[%d]",
        admaSg->eTabId, sgIndex, sgEndIndex);

    /*
     * If SG elements are more than one table descriptors size (512)
     * fill the current table and set the link for other table descriptor memory
     * in the last descriptor line
     * Note that for more than 512 SG elements this code always
     * executed irrespective of call from handler or init routines
     */
    if(admaSg->uiRemIndex > _MAX_DESC_LINES)
    {
        /* prepare list only 511(blksize-1) descriptor entries */
        sgIndex = fillADMA2Table( admaSg, paSg, &ptr, sgIndex,
            (admaSg->uiIndex+_FILL_DESC_LINES));

        /*
         * Create a link to next descriptor table
         * Update descriptor attribute as link, address field point to
         * next table start address and length as zero
         */
        ptr->uiPhy  = uiDmaAddrTbl[admaSg->eTabId];
        ptr->usAttr = _ADMA2_ATTRIB_LINK | _ADMA2_ATTRIB_VALID;
        ptr->usLen  = 0;

        _BM_DBG_INFO("[%d %d] = adr[0x%08X] Sz[%d] atr[0x%02X]\n",
            sgIndex, admaSg->uiRemIndex,
            ptr->uiPhy, ptr->usLen, ptr->usAttr);

        /* Requested to fill single buffer just return (called from handler) */
        if(_FILL_SINGLE_BUF == flag)
        {
            return;
        }

        /*
         * If remaining indices are more than available table size, enable the
         * interrupt attribute and set end index as last descriptor line
         */
        if(admaSg->uiRemIndex >= _MAX_DESC_LINES)
        {
            sgEndIndex = admaSg->uiIndex + _FILL_DESC_LINES;
            ptr->usAttr |= _ADMA2_ATTRIB_INTR;
        }
        else
        {
            sgEndIndex = sgList->uiTotal;
        }

        /* pointer moved to next table for the updation */
        ptr = (bm_adma2desc_t *)pCpuAddrTbl[admaSg->eTabId];
    }

    sgIndex = fillADMA2Table( admaSg, paSg, &ptr, sgIndex, sgEndIndex);

    /* If still SG entries are available */
    if(admaSg->uiRemIndex)
    {
        /*
         * Create a link to next descriptor table
         * Update descriptor attribute as link, address field point to
         * next table start address and length as zero
         */
        ptr->uiPhy = uiDmaAddrTbl[admaSg->eTabId];
        ptr->usAttr = _ADMA2_ATTRIB_LINK | _ADMA2_ATTRIB_VALID;
        ptr->usLen  = 0;

        /*
         * Set interrupt request for next table if remaining size more than
         * a table descriptor size
         */
        if(admaSg->uiRemIndex > _MAX_DESC_LINES)
        {
            ptr->usAttr |= _ADMA2_ATTRIB_INTR;
        }
        _BM_DBG_INFO("[%d %d] = adr[0x%08X] Sz[%d] atr[0x%02X]\n",
            sgIndex, admaSg->uiRemIndex,
            ptr->uiPhy, ptr->usLen, ptr->usAttr);
    }

    _BM_DBG_INFO("Index Ends %d\n", admaSg->uiIndex);

    return;
}

/**
 * @brief Fill ADMA2 Table with DMA params
 *
 * @param[in] *admaSg pointer to adma SG list
 * @param[in] *paSg   SG Element Array
 * @param[in] **ptr   pointer to ADMA2 descriptor pointer
 * @param[in] sgStartIndex start index to fill SG element
 * @param[in] sgEndIndex  start index up to filled SG element
 * @param[out] index Successful SG index after fill
 */
static int fillADMA2Table(
    bm_adma2sg_t *admaSg,
    com_sg_t *paSg,
    bm_adma2desc_t **ptr,
    int sgStartIndex,
    int sgEndIndex)
{
    int sgIndex = 0;

    for(sgIndex = sgStartIndex; sgIndex < sgEndIndex; sgIndex++)
    {
        /* Update ADMA2 global values */
        admaSg->uiOffset  += paSg[sgIndex].uiSize;
        admaSg->uiRemSize -= paSg[sgIndex].uiSize;
        --admaSg->uiRemIndex;

        /* Update device descriptor lines */
        (*ptr)->uiPhy = paSg[sgIndex].dmaAddr;
        (*ptr)->usLen = paSg[sgIndex].uiSize;

        /* Update descriptor attributes */
        (*ptr)->usAttr = _ADMA2_ATTRIB_TRAN | _ADMA2_ATTRIB_VALID;

        /* if remaining size is zero set the end attribute */
        if(0 == admaSg->uiRemIndex)
        {
            (*ptr)->usAttr |= _ADMA2_ATTRIB_END;
        }

        _BM_DBG_INFO("[%d %d] = adr[0x%08X] Sz[%d] atr[0x%02X]\n",
            sgIndex, admaSg->uiRemIndex,
            (*ptr)->uiPhy, (*ptr)->usLen, (*ptr)->usAttr);

        /* Move to next entry */
        (*ptr)++;
    }

    /* In next iteration loop starts with new index and new table */
    admaSg->uiIndex = sgIndex;
    admaSg->eTabId = (admaSg->eTabId ^ 1);

    return sgIndex;
}

/**@}*/ // BM_Functions

/**@}*//* BufferManagement */

