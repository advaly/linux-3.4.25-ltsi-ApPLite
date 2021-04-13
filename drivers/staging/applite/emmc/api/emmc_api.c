/**
 * @file          emmc_api.c
 *
 * \brief         This file includes interfaces for API layer of the eMMC device
 *
 * \b COPYRIGHT : TOSHIBA Corporation Semiconductor and Storage Company
 * 2010-2015 All rights reserved
 *
 * \b Project   : Glenfiddich
 *
 * \b Version   : 0.5
 *
 * \b Release   : None
 *
 * \b Date      : 02-Aug-2013
 */

/**
 * @addtogroup EMMC Memory Interface
 * @{
 */

/**
 * @addtogroup EMMCAPIs
 * @{
 */

/*----------------------- Header Files Inclusions ---------------------------*/
#include "emmc_api.h"
#include "os.h"
#include "cmd_api.h"
#include "hc_api.h"
#include "bm.h"
#include "intr.h"
#include "dev_com.h"
#include "debug.h"
#include "config.h"

/*-------------------------- Macro Definitions ------------------------------*/

/** @addtogroup API_DEFINES API_DEFINES
 * @{
 */

#ifdef __DEBUG
#define EMMC_OPT_DBG(__format__, arg...)    \
    dz_print(_DZ_API, "[%4d]%s::" __format__"\n", __LINE__,    \
    __FUNCTION__,## arg )

#define EMMC_ERR_DBG(__format__, arg...)    \
    dz_print(_DZ_CRTICAL, "[%4d]%s::" __format__"\n", __LINE__,    \
    __FUNCTION__,## arg )
#else /* !__DEBUG */
#define EMMC_OPT_DBG(__format__, arg...)
#define EMMC_ERR_DBG(__format__, arg...)
#endif /* __DEBUG */

/*
 * Lower layer error codes will have 16bit values. This will be ORed with upper
 * 16 bits of the module id. This error code will be returned to the upper
 * layer. Ex: If OS layer returned 0x0007(= _OS_ERR_INTR_REG), error code
 * returned will be _OS_ID | _OS_ERR_INTR_REG = 0x00030007
 */
#define ERRRET(ID, status) ((emmc_sts_e)(ID | status))

/* Module id, used for returning appropriate error return code for all layers */
#define _API_ID  0x00000000
#define _HC_ID   0x00010000
#define _CMD_ID  0x00020000
#define _OS_ID   0x00030000
#define _DEV_ID  0x00040000
#define _BM_ID   0x00050000
#define _INTR_ID 0x00060000

/* emmc Init entry check values.*/
#define _EMMC_INITIALIZE   1
#define _EMMC_UNINITIALIZE 0

/* Default emmc specific params */
#define _DEF_CLK_FREQ      400000   /* Clock frequency */
#define _NUM_PARTITIONS    4        /* Max partitions supported by device */

/* Exit levels */
#define _EXIT_LVL_ALL     0
#define _EXIT_LVL_BM      1
#define _EXIT_LVL_DEV     2
#define _EXIT_LVL_HC      3
#define _EXIT_LVL_REGINTR 4
#define _EXIT_LVL_INTR    5

/* Maximum password LEN */
#define _EMMC_MAX_PWD_LEN 16

/* Lock/unlock structure header values */
#define _UNLOCK             0x0 /* To Unlock */
#define _LOCK               0x4 /* To Lock */
#define _SETPWD             0x1 /* To set password */
#define _CLRPWD             0x2 /* To clear password */
#define _FORCE_ERASE        0x8 /* To force erase */
#define _SETPWD_LOCK        0x5 /* To set password and lock */
#define _FORCE_ERASE_OTHER  0xC /* For testing only: set erase bit + other */

/* Macro to mention switching to/from PIO mode */
#define _SET        1 /* To restore from PIO to the old mode */
#define _CLR        0 /* To switch to PIO mode */

/**@}*/ // API_DEFINES

/*-------------------------- Enum Definitions -------------------------------*/

/*------------------ Data Structures & Custom Typedefs ----------------------*/

/** @defgroup API_Structures API_Structures
 * @{
 */

/**
 * @brief HC configuration database structure
 */
typedef struct tag_HCCfgParams_t
{
    _ub32 uiSlot;           /**< To which slot this config belongs */
    _ub32 uiMask;           /**< Interrupt mask value */
    _ub32 uiStatus;         /**< Normal/error status */
    _ub32 uiClkFreq;        /**< Clock frequency */
    _ub32 uiDirtyFlag;      /**< Flag to check for any updates in cfg param */
    _ub16 usBusSpeed;       /**< Bus transaction speed */
    _ub16 usPwrCtrl;        /**< Power control value */
    _ub16 usBusWidth;       /**< Data bus width */
    _ub16 usMode;           /**< Data transfer mode */
    _ub16 usHostVersion;    /**< Host controller version */
    _ub16 usBlksize;        /**< Block size used */
}hcCfgParams_t;

/**
 * @brief EMMC configuration database structure
 */
typedef struct tag_devParams_t
{
    _ub32 uiSlot;             /**< To which slot this config belongs */
    _ub32 uiDirtyFlag;        /**< Flag to check for any updates in cfg param */
    _ub16 usNumPartitions;    /**< Number of partitions card supports */
    _ub16 usCardVersion;      /**< eMMC device version */
    _ub16 usBusWidth;         /**< Data bus width */
    _ub16 usBlksize;          /**< Block size used */
}devCfgParams_t;

/**@}*/ // API_Structures

/*------------------------------ Externs ------------------------------------*/

/*---------------------------- Prototypes -----------------------------------*/

/** @addtogroup API_Prototypes API_Prototypes
 * @{
 */

/* init default params for HC and emmc */
static void initHCParams(_ub32 uiSlot, hcCfgParams_t *hcCfg);

static void initDevParams(_ub32 uiSlot, devCfgParams_t *devCfg);

/* Wrapper function to call the initHCParams and initDevParams functions */
static void initDB(void);

/* Function to cleanup the acquired resources incase of any error */
static emmc_sts_e cleanup(_ub32 uiLevel);

/* API to switch mode to PIO and restore back to original mode */
static emmc_sts_e switchMode(
    _ub32 uiSlot,
    _ub32 uiSize,
    com_RWDir_e eDirection,
    _ub8 ucSetClrMode);

/**@}*//* API_Prototypes */
/*------------- Data variable/Structure allocation (global) -----------------*/

/** @addtogroup API_Globals API_Globals
 * @{
 */

static _ub32 SlotValid[_MAX_SLOTS] = {_SLOT_INVALID}; /* updated in hc_init */

/* HC and eMMC device config param structure */
static hcCfgParams_t hcCfg[_MAX_SLOTS];
static devCfgParams_t devCfg[_MAX_SLOTS];

/* Global flag used for avoiding multiple calls to emmc_init() */
static _b32 initEntryFlag = _EMMC_UNINITIALIZE;

/* sem lock for global HC and eMMC structure */
static INIT_SEM(apiLock); /* To get a sem lock */

/* Static buffer of 512Bytes used for CMD30,31,42,27 */
static _ub8 pioBuf[_BLK_SIZE];

/**@}*//* API_Globals */

/*----------------------- Function Definitions ------------------------------*/

/** @addtogroup API_Functions API_Functions
 * @{
 */

/**
 * @brief API to initialize the HC, device and all other modules
 *
 * @param None
 *
 * @retval _EMMC_OS_ERR_SEMAPHORE Error taking semaphore
 * @retval _EMMC_INIT_INVALID Invalid entry to the emmc_init
 * @retval _EMMC_STS_OK No error and emmc_init successful
 * @retval Error code from lower layers
 *
 * Important Note: This function is not re-entrant.
 */
emmc_sts_e emmc_init(void)
{
    _ub32 irq = 0;
    _ub32 ret = 0;
    void *ptr = NULL;
    _b32 sts = 0;

    EMMC_OPT_DBG("Enter");

    ret = TAKE_SEM(&apiLock);
    if(0 != ret)
    {
        EMMC_ERR_DBG("emmc_init-TAKESEM: ERROR %d\n", ret);
        return _EMMC_OS_ERR_SEMAPHORE;
    }

    /* Validate the entry to emmc_init() */
    if(_EMMC_INITIALIZE == initEntryFlag)
    {
        EMMC_ERR_DBG("Trying to Reinitialize\n");
        REL_SEM(&apiLock);
        return _EMMC_INIT_INVALID;
    }

    /*
     * To save local variable space, sts is declared as _b32 even though it
     * will be used for comparison with status enums returned by other layers.
     * It will be typecasted whenever required. For ex: if sts is compared
     * with OS enum it will be typecasted with os_sts_e.
     */

    /* Initialize the hc and dev structures.*/
    initDB();

    /* initialize the required OS services */
    sts = (_b32)os_init();
    if(_OS_OK != (os_sts_e)sts)
    {
        EMMC_ERR_DBG("os_init: ERROR 0x%08x\n", ERRRET(_OS_ID, sts));
        REL_SEM(&apiLock);
        return ERRRET(_OS_ID, sts);
    }

    /*
     * Initialize the host controller
     * Base address is obtained in hc_init. call this before other mod init
     */
    sts = (_b32)hc_init(SlotValid);
    if(_HC_STS_OK != (hc_sts_e)sts)
    {
        EMMC_ERR_DBG("hc_init: ERROR 0x%08x\n", ERRRET(_HC_ID, sts));
        cleanup(_EXIT_LVL_HC); /* error return check not reqd */
        REL_SEM(&apiLock);
        return ERRRET(_HC_ID, sts);
    }

    /* initialize interrupt handler */
    sts = intr_init();
    if(_INTR_OK != (intr_sts_e)sts)
    {
        EMMC_ERR_DBG("intr_init: ERR 0x%08x\n", ERRRET(_INTR_ID, sts));
        cleanup(_EXIT_LVL_INTR); /* error return check not reqd */
        REL_SEM(&apiLock);
        return ERRRET(_INTR_ID, sts);
    }

    /* Get an irq number from OS */
    irq = os_getIRQ();

    /* Register the interrupt */
    sts = (_b32)os_registerIntr(irq, intr_irqHandler, ptr);
    if(_OS_OK != (os_sts_e)sts)
    {
        EMMC_ERR_DBG("os_register_intr 0x%08x\n", ERRRET(_OS_ID, sts));
        cleanup(_EXIT_LVL_REGINTR); /* error return check not reqd */
        REL_SEM(&apiLock);
        return ERRRET(_OS_ID, sts);
    }

    /* Initialize card for all available slots */
    sts = (_b32)seq_init(SlotValid);
    if(_DEV_STS_OK != (dev_sts_e)sts)
    {
        EMMC_ERR_DBG("seq_init-0x%08x\n", ERRRET(_DEV_ID, sts));
        cleanup(_EXIT_LVL_DEV); /* error return check not reqd */
        REL_SEM(&apiLock);
        return ERRRET(_DEV_ID, sts);
    }

    /* get the buffer handlers */
    sts = (_b32)bm_init();
    if(_BM_STS_OK != (bm_sts_e)sts)
    {
        EMMC_ERR_DBG("bm_init: ERROR 0x%08x\n", ERRRET(_BM_ID, sts));
        cleanup(_EXIT_LVL_BM); /* error return check not reqd */
        REL_SEM(&apiLock);
        return ERRRET(_BM_ID, sts);
    }
    EMMC_OPT_DBG("Exit");

    /* emmc_init is successful. Clear the flag */
    initEntryFlag = _EMMC_INITIALIZE;
    REL_SEM(&apiLock);

    return _EMMC_STS_OK;
}

/**
 * @brief API to de-initialize the HC, device and all other modules
 *
 * @param None
 *
 * @retval _EMMC_OS_ERR_SEMAPHORE Error taking semaphore
 * @retval _EMMC_INIT_INVALID emmc is not yet initialized
 * @retval _EMMC_STS_OK No error and emmc_exit successful
 * @retval err Error code from lower layer
 *
 * Important Note: This function is not re-entrant
 */
emmc_sts_e emmc_exit(void)
{
    emmc_sts_e err = _EMMC_STS_OK;
    _ub32 ret = 0;

    /* acquire lock */
    ret = TAKE_SEM(&apiLock);
    if(0 != ret)
    {
        EMMC_ERR_DBG("emmc_init-TAKESEM: ERROR %d\n", ret);
        return _EMMC_OS_ERR_SEMAPHORE;
    }

    /* Check if emmc is initialized */
    if(_EMMC_INITIALIZE != initEntryFlag)
    {
        EMMC_ERR_DBG("emmc_init is not yet done!!\n");
        REL_SEM(&apiLock);
        return _EMMC_INIT_INVALID;
    }

    /* call cleanup function to release all resources and reset HC and dev */
    err = cleanup(_EXIT_LVL_ALL);
    /* Warnings are given in cleanup, just return the error */

    /* clear the entry flag before returning */
    initEntryFlag = _EMMC_UNINITIALIZE;

    /* Release lock before return */
    REL_SEM(&apiLock);
    return err;
}

/**
 * @brief API to read from the eMMC device
 *
 * @param[in] uiSlot slot number to read from
 * @param[in] pucBuf buffer to store the read data;
 * for ADMA2 it is the scatter gather list com_sglist_t
 * @param[in] uiSize size of the data to be read
 * @param[in] uiDevAdr Sector address of the device to read the data
 *
 * @retval _EMMC_ARG_INVALID Invalid Argument sent
 * @retval _EMMC_SLOT_INVALID Slot is invalid
 * @retval _EMMC_REQ_INVALID invalid call to emmc_read
 * @retval _EMMC_OS_ERR_SEMAPHORE Error taking semaphore
 * @retval _EMMC_STS_OK No error and emmc_read successful
 * @retval Error code from lower layers
 */
emmc_sts_e emmc_read(
    _ub32 uiSlot,
    _ub8 *pucBuf,
    _ub32 uiSize,
    _ub32 uiDevAdr)
{
    _b32 sts = 0;
    _ub32 ret = 0;

    /* Validate the input arguments */
    if(uiSlot >= _MAX_SLOTS)
    {
        return _EMMC_ARG_INVALID;
    }

    if(NULL == pucBuf)
    {
        return _EMMC_ARG_INVALID;
    }
    /* uiSize can be checked for max card size */

    /* uiDevAdr called with value 0. no i/p arg check*/

    /* Acquire lock before read */
    ret = TAKE_SEM(&apiLock);
    if(0 != ret)
    {
        EMMC_ERR_DBG("emmc_read-TAKESEM: ERROR %d\n", ret);
        return _EMMC_OS_ERR_SEMAPHORE;
    }

    /* Check the validity of the slot */
    if(_SLOT_VALID != SlotValid[uiSlot])
    {
        REL_SEM(&apiLock);
        return _EMMC_SLOT_INVALID;
    }

    /* Check if emmc is initialized */
    if(_EMMC_INITIALIZE != initEntryFlag)
    {
        EMMC_ERR_DBG("emmc_init is not yet done!!\n");
        REL_SEM(&apiLock);
        return _EMMC_REQ_INVALID;
    }

    EMMC_OPT_DBG("\n\n******emmc_read*******\n");

#ifdef __PERFORMANCE_MEASUREMENT
    os_perf_start(_COM_DIR_R);
#endif /* __PERFORMANCE_MEASUREMENT */

    /* call the buffer management module to handle the buffers internally */
    sts = (_b32)bm_config(uiSlot, pucBuf, uiSize, _COM_DIR_R);
    if(_BM_STS_OK != (bm_sts_e)sts)
    {
        EMMC_ERR_DBG("bm_config: ERROR 0x%08x\n", ERRRET(_BM_ID, sts));
        REL_SEM(&apiLock); /* release lock before return */
        return ERRRET(_BM_ID, sts);
    }

    /* Set the all the config params required for read on HC side */
    sts = (_b32)hc_setDataParams(uiSlot, uiSize, _COM_DIR_R );
    if(_HC_STS_OK != (hc_sts_e)sts)
    {
        EMMC_ERR_DBG("hc_setDataParams:0x%08x\n", ERRRET(_HC_ID, sts));
        bm_deconfig(uiSlot, pucBuf, uiSize, _COM_DIR_R);
        REL_SEM(&apiLock); /* release lock before return */
        return ERRRET(_HC_ID, sts);
    }

    /* call the emmc cmd sequences for the read operation */
    sts = (_b32)seq_readData(uiSlot, uiDevAdr, uiSize);
    if(_DEV_STS_OK != (dev_sts_e)sts)
    {
        EMMC_ERR_DBG("seq_readData: ERROR 0x%08x\n", ERRRET(_DEV_ID, sts));
        bm_deconfig(uiSlot, pucBuf, uiSize, _COM_DIR_R);
        REL_SEM(&apiLock); /* release lock before return */
        return ERRRET(_DEV_ID, sts);
    }

    sts = (_b32)bm_deconfig(uiSlot, pucBuf, uiSize, _COM_DIR_R);
    if(_BM_STS_OK != (bm_sts_e)sts)
    {
        EMMC_ERR_DBG("bm_deconfig: ERROR 0x%08x\n", ERRRET(_BM_ID, sts));
        REL_SEM(&apiLock); /* release lock before return */
        return ERRRET(_BM_ID, sts);
    }

#ifdef __PERFORMANCE_MEASUREMENT
    os_perf_stop(_COM_DIR_R, uiSize);
#endif /* __PERFORMANCE_MEASUREMENT */

    REL_SEM(&apiLock); /* release lock afer read */

    return _EMMC_STS_OK;
}

/**
 * @brief API to write to the eMMC device
 *
 * @param[in] uiSlot slot number to write the data
 * @param[in] pucBuf buffer from which the data will be read
 * for ADMA2 it is the scatter gather list com_sglist_t
 * @param[in] uiSize size of the data to be written
 * @param[in] uiDevAdr sector address of the device to write the data
 *
 * @retval _EMMC_ARG_INVALID Invalid Argument sent
 * @retval _EMMC_SLOT_INVALID Slot is invalid
 * @retval _EMMC_REQ_INVALID invalid call to emmc_write
 * @retval _EMMC_OS_ERR_SEMAPHORE Error taking semaphore
 * @retval _EMMC_STS_OK No error and emmc_write successful
 * @retval Error code from lower layers
 */
emmc_sts_e emmc_write(
    _ub32 uiSlot,
    _ub8 *pucBuf,
    _ub32 uiSize,
    _ub32 uiDevAdr)
{
    _b32 sts = 0;
    _ub32 ret = 0;

    /* Validate the input arguments */
    if(uiSlot >= _MAX_SLOTS)
    {
        return _EMMC_ARG_INVALID;
    }

    if(NULL == pucBuf)
    {
        return _EMMC_ARG_INVALID;
    }

    /* uiSize can be checked for max card size */

    /* uiDevAdr called with value 0. no i/p arg check*/

    /* Acquire lock before write */
    ret = TAKE_SEM(&apiLock);
    if(0 != ret)
    {
        EMMC_ERR_DBG("emmc_write-TAKESEM: ERROR %d\n", ret);
        return _EMMC_OS_ERR_SEMAPHORE;
    }

    /* Check the validity of the slot */
    if(_SLOT_VALID != SlotValid[uiSlot])
    {
        REL_SEM(&apiLock);
        return _EMMC_SLOT_INVALID;
    }

    /* Check if emmc is initialized */
    if(_EMMC_INITIALIZE != initEntryFlag)
    {
        EMMC_ERR_DBG("emmc_init is not yet done!!\n");
        REL_SEM(&apiLock);
        return _EMMC_REQ_INVALID;
    }

    EMMC_OPT_DBG("\n\n*******emmc_write*****\n");

#ifdef __PERFORMANCE_MEASUREMENT
    os_perf_start(_COM_DIR_W);
#endif /* __PERFORMANCE_MEASUREMENT */

    /* call the buffer management module to handle the buffers internally */
    sts = (_b32)bm_config(uiSlot, pucBuf, uiSize, _COM_DIR_W);
    if(_BM_STS_OK != (bm_sts_e)sts)
    {
        EMMC_ERR_DBG("bm_config: ERROR 0x%08x\n", ERRRET(_BM_ID, sts));
        REL_SEM(&apiLock); /* release lock before return */
        return ERRRET(_BM_ID, sts);
    }

    /* Set the all the config params required for write on HC side */
    sts = (_b32)hc_setDataParams(uiSlot, uiSize, _COM_DIR_W);
    if(_HC_STS_OK != (hc_sts_e)sts)
    {
        EMMC_ERR_DBG("hc_setDataParams:0x%08x\n", ERRRET(_HC_ID, sts));
        bm_deconfig(uiSlot, pucBuf, uiSize, _COM_DIR_W);
        REL_SEM(&apiLock); /* release lock before return */
        return ERRRET(_HC_ID, sts);
    }

    /* call the emmc cmd sequences for the write operation */
    sts = (_b32)seq_writeData(uiSlot, uiDevAdr, uiSize);
    if(_DEV_STS_OK != (dev_sts_e)sts)
    {
        EMMC_ERR_DBG("seq_writeData:ERROR 0x%08x\n", ERRRET(_DEV_ID, sts));
        bm_deconfig(uiSlot, pucBuf, uiSize, _COM_DIR_W);
        REL_SEM(&apiLock); /* release lock before return */
        return ERRRET(_DEV_ID, sts);
    }

    sts = (_b32)bm_deconfig(uiSlot, pucBuf, uiSize, _COM_DIR_W);
    if(_BM_STS_OK != (bm_sts_e)sts)
    {
        EMMC_ERR_DBG("bm_deconfig: ERROR 0x%08x\n", ERRRET(_BM_ID, sts));
        REL_SEM(&apiLock); /* release lock before return */
        return ERRRET(_BM_ID, sts);
    }

#ifdef __PERFORMANCE_MEASUREMENT
    os_perf_stop(_COM_DIR_W, uiSize);
#endif /* __PERFORMANCE_MEASUREMENT */

    REL_SEM(&apiLock); /* release lock after write */

    return _EMMC_STS_OK;
}

/**
 * @brief API to set the bus width
 *
 * @param[in] uiSlot slot number to set the bus width
 * @param[in] width bus width to be set to HC and Device
 *
 * @retval _EMMC_ARG_INVALID Invalid Argument sent
 * @retval _EMMC_SLOT_INVALID Slot is invalid
 * @retval _EMMC_OS_ERR_SEMAPHORE Error taking semaphore
 * @retval _EMMC_REQ_INVALID invalid call to emmc_setBusWidth
 * @retval _EMMC_STS_OK No error and emmc_setBusWidth successful
 */
emmc_sts_e emmc_setBusWidth(_ub32 uiSlot, com_busWidth_e width)
{
    _ub32 ret=0;

    /* Validate the input argument */
    if(uiSlot >= _MAX_SLOTS)
    {
        return _EMMC_ARG_INVALID;
    }

    if((width <_COM_BWIDTH_8) || (width > _COM_BWIDTH_1))
    {
        return _EMMC_ARG_INVALID;
    }

    /* Update the internal data base, accessing global, so use sem lock */
    ret = TAKE_SEM(&apiLock);
    if(0 != ret)
    {
         EMMC_ERR_DBG("emmc_setBusWidth-TAKESEM: ERROR %d\n", ret);
        return _EMMC_OS_ERR_SEMAPHORE;
    }

    /* Check the validity of the slot */
    if(_SLOT_VALID != SlotValid[uiSlot])
    {
        REL_SEM(&apiLock);
        return _EMMC_SLOT_INVALID;
    }

    /* Check if emmc is initialized */
    if(_EMMC_INITIALIZE != initEntryFlag)
    {
        EMMC_ERR_DBG("emmc_init is not yet done!!\n");
        REL_SEM(&apiLock);
        return _EMMC_REQ_INVALID;
    }

    hcCfg[uiSlot].usBusWidth = width;
    devCfg[uiSlot].usBusWidth = width;
    hcCfg[uiSlot].uiDirtyFlag = 1;
    devCfg[uiSlot].uiDirtyFlag = 1;

    REL_SEM(&apiLock);

    return _EMMC_STS_OK;
}

/**
 * @brief API to get the operation mode
 *
 * @param[in] uiSlot slot number to set the operation mode
 * @param[in] mode operation mode to set
 *
 * @retval _EMMC_ARG_INVALID Invalid Argument sent
 * @retval _EMMC_SLOT_INVALID Slot is invalid
 * @retval _EMMC_OS_ERR_SEMAPHORE Error taking semaphore
 * @retval _EMMC_REQ_INVALID invalid call to emmc_setOpMode
 * @retval _EMMC_STS_OK No error and emmc_setOpMode successful
 */
emmc_sts_e emmc_setOpMode(_ub32 uiSlot, com_modes_e mode)
{
    _ub32 ret = 0;

    /* validate the input arguments */
    if(uiSlot >= _MAX_SLOTS)
    {
        return _EMMC_ARG_INVALID;
    }

    if((mode< _COM_MODE_PIO) || (mode > _COM_MODE_ADMA2))
    {
        return _EMMC_ARG_INVALID;
    }

    /* Update the internal data base, accessing global, so use sem lock */
    ret = TAKE_SEM(&apiLock);
    if(0 != ret)
    {
         EMMC_ERR_DBG("emmc_setOpMode-TAKESEM: ERROR %d\n", ret);
        return _EMMC_OS_ERR_SEMAPHORE;
    }

    /* Check the validity of the slot */
    if(_SLOT_VALID != SlotValid[uiSlot])
    {
        REL_SEM(&apiLock);
        return _EMMC_SLOT_INVALID;
    }

    /* Check if emmc is initialized */
    if(_EMMC_INITIALIZE != initEntryFlag)
    {
        EMMC_ERR_DBG("emmc_init is not yet done!!\n");
        REL_SEM(&apiLock);
        return _EMMC_REQ_INVALID;
    }

    hcCfg[uiSlot].usMode = mode;
    hcCfg[uiSlot].uiDirtyFlag = 1;

    REL_SEM(&apiLock);

    return _EMMC_STS_OK;
}

/**
 * @brief API to set the clock value to HC
 *
 * @param[in] uiSlot slot number to set the clock
 * @param[in] uiVal value to be set
 *
 * @retval _EMMC_ARG_INVALID Invalid Argument sent
 * @retval _EMMC_SLOT_INVALID Slot is invalid
 * @retval _EMMC_OS_ERR_SEMAPHORE Error taking semaphore
 * @retval _EMMC_REQ_INVALID invalid call to emmc_setClock
 * @retval _EMMC_STS_OK No error and emmc_setClock successful
 */
emmc_sts_e emmc_setClock(_ub32 uiSlot, _ub32 uiVal)
{
    _ub32 ret = 0;

    /* Validate input argument */
    if(uiSlot >= _MAX_SLOTS)
    {
        return _EMMC_ARG_INVALID;
    }
    if((0 == uiVal) || (uiVal < _DEF_CLK_FREQ))
    {
        /* Clock should not be 0 or less than _DEF_CLK_FREQ */
        return _EMMC_ARG_INVALID;
    }

    /* Update the internal data base, accessing global, so use sem lock */
    ret = TAKE_SEM(&apiLock);
    if(0 != ret)
    {
         EMMC_ERR_DBG("emmc_setClock-TAKESEM: ERROR %d\n", ret);
        return _EMMC_OS_ERR_SEMAPHORE;
    }

    /* Check the validity of the slot */
    if(_SLOT_VALID != SlotValid[uiSlot])
    {
        REL_SEM(&apiLock);
        return _EMMC_SLOT_INVALID;
    }

    /* Check if emmc is initialized */
    if(_EMMC_INITIALIZE != initEntryFlag)
    {
        EMMC_ERR_DBG("emmc_init is not yet done!!\n");
        REL_SEM(&apiLock);
        return _EMMC_REQ_INVALID;
    }

    hcCfg[uiSlot].uiClkFreq = uiVal;
    hcCfg[uiSlot].uiDirtyFlag = 1;
    devCfg[uiSlot].uiDirtyFlag = 1; /* seq_setSpeed to be called for HS modes */

    REL_SEM(&apiLock);

    return _EMMC_STS_OK;
}

/**
 * @brief API to update the HC and device from the internal database
 *
 * @param[in] uiSlot slot number to set the config
 *
 * @retval _EMMC_ARG_INVALID Invalid Argument sent
 * @retval _EMMC_SLOT_INVALID Slot is invalid
 * @retval _EMMC_OS_ERR_SEMAPHORE Error taking semaphore
 * @retval _EMMC_REQ_INVALID invalid call to emmc_setConfig
 * @retval _EMMC_STS_OK No error and emmc_setConfig successful
 * @retval Error code from lower layers
 *
 * Important: This API should be called after calling any other cfg APIs.
 * Only then the values will be updated in HC and device side
 */
emmc_sts_e emmc_setConfig(_ub32 uiSlot)
{
    _b32 sts = 0;
    _ub32 ret = 0;

    /* Validate input parameters */
    if(uiSlot >= _MAX_SLOTS)
    {
        return _EMMC_ARG_INVALID;
    }

    /*
     * bus width, op mode and freq will be updated when this API is called
     * Accessing global, so use sem lock
     */
    ret = TAKE_SEM(&apiLock);
    if(0 != ret)
    {
         EMMC_ERR_DBG("emmc_setConfig-TAKESEM: ERROR %d\n", ret);
        return _EMMC_OS_ERR_SEMAPHORE;
    }

    /* Check the validity of the slot */
    if(_SLOT_VALID != SlotValid[uiSlot])
    {
        REL_SEM(&apiLock);
        return _EMMC_SLOT_INVALID;
    }

    /* Check if emmc is initialized */
    if(_EMMC_INITIALIZE != initEntryFlag)
    {
        EMMC_ERR_DBG("emmc_init is not yet done!!\n");
        REL_SEM(&apiLock);
        return _EMMC_REQ_INVALID;
    }

    /* Update config params on device side if something is changed */
    if(0 != devCfg[uiSlot].uiDirtyFlag)
    {
        /* Debug prints */
        EMMC_OPT_DBG("BlkSize = %d\n",devCfg->usBlksize);
        EMMC_OPT_DBG("BusWidth = %d\n",devCfg->usBusWidth);
        EMMC_OPT_DBG("NumPartitions = %d\n",devCfg->usNumPartitions);
        /*
         * Bus width should be updated on both HC and device side
         * First update bus width in device side
         */
        sts = (_b32)seq_setBuswidth(uiSlot,devCfg[uiSlot].usBusWidth);
        if(_DEV_STS_OK != (dev_sts_e)sts)
        {
            EMMC_ERR_DBG("seq_setBuswidth:ERR 0x%08x\n", ERRRET(_DEV_ID, sts));
            REL_SEM(&apiLock);    /* Release sem lock before returning error */
            return ERRRET(_DEV_ID, sts);
        }

        /* If clock freq is > 25MHz set HS in device side */
        {
            com_busSpeed_e speed = _COM_SPEED_NORMAL;
            if(hcCfg[uiSlot].uiClkFreq > 25000000)
            {
                /* Set Device to high speed */
                speed = _COM_SPEED_HIGH;

            }
            sts = (_b32)seq_setSpeed(uiSlot, speed);
            if(_DEV_STS_OK != (dev_sts_e)sts)
            {
                EMMC_ERR_DBG("seq_setSpeed:ERR 0x%08x\n", ERRRET(_DEV_ID, sts));
                REL_SEM(&apiLock); /* Release sem lock before returning error */
                return ERRRET(_DEV_ID, sts);
            }
        }

        /* Clear the dirty flag */
        devCfg[uiSlot].uiDirtyFlag = 0;
    }

    /* Update config params on HC side if something is changed */
    if(0 != hcCfg[uiSlot].uiDirtyFlag)
    {
        /* Debug prints */
        EMMC_OPT_DBG("BlkSize = %d\n",hcCfg->usBlksize);
        EMMC_OPT_DBG("PwrCtrl = %d\n",hcCfg->usPwrCtrl);
        EMMC_OPT_DBG("BusSpeed = %d\n",hcCfg->usBusSpeed);
        EMMC_OPT_DBG("ClkFreq = %d\n",hcCfg->uiClkFreq);
        EMMC_OPT_DBG("BusWidth = %d\n",hcCfg->usBusWidth);
        EMMC_OPT_DBG("Mode = %d\n",hcCfg->usMode);

        /* Update bus width in HC */
        sts = (_b32)hc_setBusWidth(uiSlot, hcCfg[uiSlot].usBusWidth);
        if(_HC_STS_OK != (hc_sts_e)sts)
        {
            EMMC_ERR_DBG("hc_setBusWidth ERROR 0x%08x\n", ERRRET(_HC_ID, sts));
            REL_SEM(&apiLock);    /* Release sem lock before returning error */
            return ERRRET(_HC_ID, sts);
        }

        /* Update op mode in HC */
        sts = (_b32)hc_setOpMode(
            uiSlot,
            (com_modes_e)hcCfg[uiSlot].usMode);
        if(_HC_STS_OK != (hc_sts_e)sts)
        {
            EMMC_ERR_DBG("hc_setOpMode:ERROR 0x%08x\n", ERRRET(_HC_ID, sts));
            REL_SEM(&apiLock);    /* Release sem lock before returning error */
            return ERRRET(_HC_ID, sts);
        }

        /* Update clock frequency in HC */
        sts = (_b32)hc_setFreq(
            uiSlot,
            hcCfg[uiSlot].uiClkFreq);
        if(_HC_STS_OK != (hc_sts_e)sts)
        {
            EMMC_ERR_DBG("hc_setFreq:ERROR 0x%08x\n", ERRRET(_HC_ID, sts));
            REL_SEM(&apiLock);    /* Release sem lock before returning error */
            return ERRRET(_HC_ID, sts);
        }

        /* Everything is updated ! clear the dirty flag */
        hcCfg[uiSlot].uiDirtyFlag = 0;
    }

    REL_SEM(&apiLock);

    return _EMMC_STS_OK;
}

/**
 * @brief  Removes Data from Device via Erase/Discard/Trim mechanisms.
 *
 * @param[in] uiSlot slot number
 * @param[in] ePartNum - partition number
 * @param[in] uiStartSectr startaddr for which action is reqd [in sector unit]
 * @param[in] uiEndSectr endaddr for which action is reqd [in sector unit]
 * @param[in] eRemType choose from discard/erase/trim
 *
 * @retval _EMMC_ARG_INVALID Invalid argument sent
 * @retval _EMMC_SLOT_INVALID Slot is invalid
 * @retval _EMMC_OS_ERR_SEMAPHORE Error taking semaphore
 * @retval _EMMC_REQ_INVALID invalid call to emmc_remData
 * @retval _EMMC_STS_OK The function is successful
 */
 emmc_sts_e emmc_remData(
     _ub32 uiSlot,
     com_part_num_e ePartNum,
     _ub32 uiStartSectr,
     _ub32 uiEndSectr,
     com_rem_type_e eRemType)
{
    dev_sts_e eSts = _DEV_STS_OK;
    _ub32 uiRet = 0;

    /* Validating the input arguments */

    /*Validate slot number */
    if(uiSlot >= _MAX_SLOTS)
    {
        return _EMMC_ARG_INVALID;
    }

    /* Validate data removal type parameter */
    if(eRemType >= _COM_REM_TYP_INVALID)
    {
        return _EMMC_ARG_INVALID;
    }

    /* Check if partition exceeds the permitted number */
    if(ePartNum >= _COM_PARTITION_MAX)
    {
        return _EMMC_ARG_INVALID;
    }

    /* if start sector is greater end sect -Error. Valid only if not sanitize */
    if(uiStartSectr > uiEndSectr)
    {
        return _EMMC_ARG_INVALID;
    }

    EMMC_OPT_DBG("rem type %x\n", eRemType);
    EMMC_OPT_DBG("start sect %x  end sect %x \n",uiStartSectr,uiEndSectr);

    /* Acquire lock before calling dev_remData */
    uiRet = TAKE_SEM(&apiLock);
    if(0 != uiRet)
    {
        EMMC_ERR_DBG("emmc_remdata - TAKESEM: ERROR %d\n", uiRet);
        return _EMMC_OS_ERR_SEMAPHORE;
    }

    /* Check the validity of the slot */
    if(_SLOT_VALID != SlotValid[uiSlot])
    {
        REL_SEM(&apiLock);
        return _EMMC_SLOT_INVALID;
    }

    /* Check if emmc is initialized */
    if(_EMMC_INITIALIZE != initEntryFlag)
    {
        EMMC_ERR_DBG("emmc_init is not yet done!!\n");
        REL_SEM(&apiLock);
        return _EMMC_REQ_INVALID;
    }

    /* Calling the device layer function */
    eSts = dev_remData(uiSlot,ePartNum,uiStartSectr,uiEndSectr, eRemType);
    if(_DEV_STS_OK != eSts)
    {
        EMMC_ERR_DBG("dev_remData: Error 0x%08x\n", ERRRET(_DEV_ID, eSts));
        REL_SEM(&apiLock); /* release lock before return */
        return ERRRET(_DEV_ID, eSts);
    }
    REL_SEM(&apiLock);

    return _EMMC_STS_OK;
}

/**
 * @brief  Removes Data from Device via Sanitize mechanism.
 *
 * @param[in] uiSlot slot number
 *
 * @retval _EMMC_ARG_INVALID Invalid argument sent
 * @retval _EMMC_SLOT_INVALID Slot is invalid
 * @retval _EMMC_OS_ERR_SEMAPHORE Error taking semaphore
 * @retval _EMMC_REQ_INVALID invalid call to emmc_remData
 * @retval _EMMC_STS_OK The function is successful
 */
 emmc_sts_e emmc_sanitize(_ub32 uiSlot)
{
    dev_sts_e eSts = _DEV_STS_OK;
    _ub32 uiRet = 0;

    /* Validating the input arguments */

    /*Validate slot number */
    if(uiSlot >= _MAX_SLOTS)
    {
        return _EMMC_ARG_INVALID;
    }

    /* Acquire lock before calling dev_sanitize */
    uiRet = TAKE_SEM(&apiLock);
    if(0 != uiRet)
    {
        EMMC_ERR_DBG("emmc_sanitize - TAKESEM: ERROR %d\n", uiRet);
        return _EMMC_OS_ERR_SEMAPHORE;
    }

    /* Check the validity of the slot */
    if(_SLOT_VALID != SlotValid[uiSlot])
    {
        REL_SEM(&apiLock);
        return _EMMC_SLOT_INVALID;
    }

    /* Check if emmc is initialized */
    if(_EMMC_INITIALIZE != initEntryFlag)
    {
        EMMC_ERR_DBG("emmc_init is not yet done!!\n");
        REL_SEM(&apiLock);
        return _EMMC_REQ_INVALID;
    }

    /* Calling the device layer function */
    eSts = dev_sanitize(uiSlot);
    if(_DEV_STS_OK != eSts)
    {
        EMMC_ERR_DBG("dev_sanitize: Error 0x%08x\n", ERRRET(_DEV_ID, eSts));
        REL_SEM(&apiLock); /* release lock before return */
        return ERRRET(_DEV_ID, eSts);
    }

    REL_SEM(&apiLock);

    return _EMMC_STS_OK;
}


/**
 * @brief sets Write Protection - WP can be on device/segment
 *
 * WP can be of type Permanent/Temporary/Power On.
 * Permanent protection is OTP.
 *
 * @param[in] uiSlot slot number
 * @param[in] ePartNum - partition number
 * @param[in] uiDevSeg - protect device or segment/sectors
 * @param[in] uiProtType - type of protection [Permanent/Temporary/Power-on
 * @param[in] uiSectr - sector number
 *
 * @retval _EMMC_ARG_INVALID Invalid argument sent
 * @retval _EMMC_OS_ERR_SEMAPHORE semaphore error
 * @retval _EMMC_SLOT_INVALID Slot is invalid
 * @retval _EMMC_REQ_INVALID invalid call to emmc_setWriteProt
 * @retval _EMMC_STS_OK The function is successful
 */
emmc_sts_e emmc_setWriteProt(
    _ub32 uiSlot,
    com_part_num_e ePartNum,
    com_wp_e uiDevSeg,
    com_wp_type_e uiProtType,
    _ub32 uiSectr)
{
    dev_sts_e eSts = _DEV_STS_OK;
    _ub32 uiRet = 0;

    emmc_sts_e eRet;

    /* Validate the input arguments */
    /* Validate Slot numer */
    if(uiSlot >= _MAX_SLOTS)
    {
        return _EMMC_ARG_INVALID;
    }

    /* Validate Protection argument - device or segment */
    if(uiDevSeg >= _COM_WP_INVALID)
    {
        return _EMMC_ARG_INVALID;
    }

    /* Validate Protection type */
    if(uiProtType >= _COM_WP_TYPE_INVALID)
    {
        return _EMMC_ARG_INVALID;
    }

    /* Validate partition number */
    if(ePartNum >= _COM_PARTITION_MAX)
    {
        return _EMMC_ARG_INVALID;
    }

    /* Acquire lock before accessing partitions */
    uiRet = TAKE_SEM(&apiLock);
    if(0 != uiRet)
    {
        EMMC_ERR_DBG("emmc_setWriteProt - TAKESEM: ERROR %d\n", uiRet);
        return _EMMC_OS_ERR_SEMAPHORE;
    }

    /* Check the validity of the slot */
    if(_SLOT_VALID != SlotValid[uiSlot])
    {
        REL_SEM(&apiLock);
        return _EMMC_SLOT_INVALID;
    }

    /* Check if emmc is initialized */
    if(_EMMC_INITIALIZE != initEntryFlag)
    {
        EMMC_ERR_DBG("emmc_init is not yet done!!\n");
        REL_SEM(&apiLock);
        return _EMMC_REQ_INVALID;
    }

    if(_COM_DEV == uiDevSeg)
    {
        /*
         * Setting Operation mode to PIO
         * Write protect on device requires modifying CSD
         * CSD structure is sent over the DAT line in PIO mode
         */
        eRet = switchMode(
            uiSlot,
            _COM_CSD_SIZE,
            _COM_DIR_W,
            _CLR);
        if(_EMMC_STS_OK != eRet)
        {
            EMMC_ERR_DBG("switchMode:Error 0x%08x\n",eRet);
            REL_SEM(&apiLock); /* release lock before return */
            return eRet;
        }
    }

    /* Calling the device layer  function */
    eSts = dev_setWriteProt(
        uiSlot,
        ePartNum,
        uiDevSeg,
        uiProtType,
        uiSectr,
        pioBuf);
    if(_DEV_STS_OK != eSts)
    {
        EMMC_ERR_DBG("dev_setWriteProt: Error 0x%08x\n", ERRRET(_DEV_ID, eSts));
        REL_SEM(&apiLock); /* release lock before return */
        return ERRRET(_DEV_ID, eSts);
    }

    if(_COM_DEV == uiDevSeg)
    {
        /* Restoring the data transfer Context from PIO */
        eRet = switchMode(
            uiSlot,
            _BLK_SIZE,
            _COM_DIR_W,
            _SET);
        if(_EMMC_STS_OK != eRet)
        {
            EMMC_ERR_DBG("switchMode:Error 0x%08x\n",eRet);
            REL_SEM(&apiLock); /* release lock before return */
            return eRet;
        }
    }

    REL_SEM(&apiLock);

    return _EMMC_STS_OK;
}

/**
 * @brief Clears Write Protection - WP can be on device/segment
 *
 * WP can be of type Permanent/Temporary/Power On.
 * Permanent protection is OTP.
 *
 * @param[in]  uiSlot slot number
 * @param[in]  ePartNum - partition number
 * @param[in]  uiDevSeg - protect device or segment/sectors
 * @param[in]  uiProtType - type of protection [Permanent/Temporary/Power-on]
 * @param[in]  uiSectr - sector number
 *
 * @retval _EMMC_ARG_INVALID Invalid argument sent
 * @retval _EMMC_OS_ERR_SEMAPHORE semaphore error
 * @retval _EMMC_SLOT_INVALID Slot is invalid
 * @retval _EMMC_REQ_INVALID invalid call to emmc_clrWriteProt
 * @retval _EMMC_STS_OK The function is successful
 */
emmc_sts_e emmc_clrWriteProt(
    _ub32 uiSlot,
    com_part_num_e ePartNum,
    com_wp_e uiDevSeg,
    com_wp_type_e uiProtType,
    _ub32 uiSectr)
{
    dev_sts_e eSts = _DEV_STS_OK;
    _ub32 uiRet = 0;

    emmc_sts_e eRet;

    /* Validate the input arguments */
    /* Validate Slot numer */
    if(uiSlot >= _MAX_SLOTS)
    {
        return _EMMC_ARG_INVALID;
    }

    /* Validate Protection argument - device or segment */
    if(uiDevSeg >= _COM_WP_INVALID)
    {
        return _EMMC_ARG_INVALID;
    }

    /* Validate Protection type */
    if(uiProtType >= _COM_WP_TYPE_INVALID)
    {
        return _EMMC_ARG_INVALID;
    }

    /* Validate partition number */
    if(ePartNum >= _COM_PARTITION_MAX)
    {
        return _EMMC_ARG_INVALID;
    }

    /* Acquire lock before accessing partitions */
    uiRet = TAKE_SEM(&apiLock);
    if(0 != uiRet)
    {
        EMMC_ERR_DBG("emmc_clrWriteProt - TAKESEM: ERROR %d\n", uiRet);
        return _EMMC_OS_ERR_SEMAPHORE;
    }

    /* Check the validity of the slot */
    if(_SLOT_VALID != SlotValid[uiSlot])
    {
        REL_SEM(&apiLock);
        return _EMMC_SLOT_INVALID;
    }

    /* Check if emmc is initialized */
    if(_EMMC_INITIALIZE != initEntryFlag)
    {
        EMMC_ERR_DBG("emmc_init is not yet done!!\n");
        REL_SEM(&apiLock);
        return _EMMC_REQ_INVALID;
    }

    if(_COM_DEV == uiDevSeg)
    {
        /*
         * Setting Operation mode to PIO
         * Write protect on device requires modifying CSD
         * CSD structure is sent over the DAT line in PIO mode
         */
        eRet = switchMode(
            uiSlot,
            _COM_CSD_SIZE,
            _COM_DIR_W,
            _CLR);
        if(_EMMC_STS_OK != eRet)
        {
            EMMC_ERR_DBG("switchMode:Error 0x%08x\n", eRet);
            REL_SEM(&apiLock); /* release lock before return */
            return eRet;
        }
    }

    /* Calling the device layer function */
    eSts = dev_clrWriteProt(
            uiSlot,
            ePartNum,
            uiDevSeg,
            uiProtType,
            uiSectr,
            pioBuf);
    if(_DEV_STS_OK != eSts)
    {
        EMMC_ERR_DBG("dev_clrWriteProt: Error 0x%08x\n", ERRRET(_DEV_ID, eSts));
        REL_SEM(&apiLock); /* release lock before return */
        return ERRRET(_DEV_ID, eSts);
    }

    if(_COM_DEV == uiDevSeg)
    {
        /* Restoring the data transfer Context from PIO */
        eRet = switchMode(
            uiSlot,
            _BLK_SIZE,
            _COM_DIR_W,
            _SET);
        if(_EMMC_STS_OK != eRet)
        {
            EMMC_ERR_DBG("switchMode:Error 0x%08x\n",eRet);
            REL_SEM(&apiLock); /* release lock before return */
            return eRet;
        }
    }

    REL_SEM(&apiLock);

    return _EMMC_STS_OK;
}

/**
 * @brief  get Write Protection Status of segments
 *
 * WP can be of type Permanent/Temporary/Power On.
 * Permanent protection is OTP.
 *
 * @param[in]  uiSlot slot number
 * @param[in]  uiSectr - sector number
 * @param[out] uiWpStat - indicates whether segment is protected or not
 * @param[out] ullWpType - indicates type of protection on the segment
 *
 * @retval _EMMC_ARG_INVALID Invalid argument sent
 * @retval _EMMC_OS_ERR_SEMAPHORE semaphore error
 * @retval _EMMC_SLOT_INVALID Slot is invalid
 * @retval _EMMC_REQ_INVALID invalid call to emmc_getWPStat
 * @retval _EMMC_STS_OK The function is successful
 */
emmc_sts_e emmc_getWPStat(
    _ub32 uiSlot,
    _ub32 uiSectr,
    _ub32 *uiWpStat,
    _ub64 *ullWpType)
{
    dev_sts_e eSts = _DEV_STS_OK;

    _ub32 uiRet = 0;
    emmc_sts_e eRet;

    /* Validate the input arguments */
    if(uiSlot >= _MAX_SLOTS)
    {
        return _EMMC_ARG_INVALID;
    }

    /* Acquire lock before accessing partitions */
    uiRet = TAKE_SEM(&apiLock);
    if(0 != uiRet)
    {
        EMMC_ERR_DBG("emmc_getWPStat - TAKESEM: ERROR %d\n", uiRet);
        return _EMMC_OS_ERR_SEMAPHORE;
    }

    /* Check the validity of the slot */
    if(_SLOT_VALID != SlotValid[uiSlot])
    {
        REL_SEM(&apiLock);
        return _EMMC_SLOT_INVALID;
    }

    /* Check if emmc is initialized */
    if(_EMMC_INITIALIZE != initEntryFlag)
    {
        EMMC_ERR_DBG("emmc_init is not yet done!!\n");
        REL_SEM(&apiLock);
        return _EMMC_REQ_INVALID;
    }

    /*
     * Setting Operation mode to PIO
     * Write protect status is received over DAT line
     */
    eRet = switchMode(
        uiSlot,
        _COM_CMD30_RET_SIZE,
        _COM_DIR_R,
        _CLR);
    if(_EMMC_STS_OK != eRet)
    {
        EMMC_ERR_DBG("switchMode:Error 0x%08x\n", eRet);
        REL_SEM(&apiLock); /* release lock before return */
        return eRet;
    }

    /* Calling the device layer - CMD30 */
    eSts = dev_getWPStat(uiSlot,_COM_GET_WP_STATUS,uiSectr);
    if(_DEV_STS_OK != eSts)
    {
        EMMC_ERR_DBG("dev_getWPStat: Error 0x%08x\n", ERRRET(_DEV_ID, eSts));
        REL_SEM(&apiLock); /* release lock before return */
        return ERRRET(_DEV_ID, eSts);
    }

    /* collecting return value in a 32-bit variable */
    *uiWpStat = *((_ub32*)pioBuf);

    /*
     * Setting Operation mode to PIO
     * Write protect status is received over DAT line
     */
    eRet = switchMode(
        uiSlot,
        _COM_CMD31_RET_SIZE,
        _COM_DIR_R,
        _CLR);
    if(_EMMC_STS_OK != eRet)
    {
        EMMC_ERR_DBG("switchMode:Error 0x%08x\n", eRet);
        REL_SEM(&apiLock); /* release lock before return */
        return eRet;
    }

    /* Calling the device layer function - CMD31 */
    eSts = dev_getWPStat(uiSlot,_COM_GET_WP_TYP,uiSectr);
    if(_DEV_STS_OK != eSts)
    {
        EMMC_ERR_DBG("dev_getWPStat: Error 0x%08x\n", ERRRET(_DEV_ID, eSts));
        REL_SEM(&apiLock); /* release lock before return */
        return ERRRET(_DEV_ID, eSts);
    }

    /* collecting return value in a 64-bit variable */
    *ullWpType = *((_ub64*)pioBuf);

    /* Restoring the data transfer Context from PIO */
    eRet = switchMode(
        uiSlot,
        _BLK_SIZE,
        _COM_DIR_W,
        _SET);
    if(_EMMC_STS_OK != eRet)
    {
        EMMC_ERR_DBG("switchMode:Error 0x%08x\n",eRet);
        REL_SEM(&apiLock); /* release lock before return */
        return eRet;
    }

    REL_SEM(&apiLock);

    return _EMMC_STS_OK;
}

/**
 * @brief  API to Lock/Unlock device, Set/Clear Password & Force Erase
 *
 * @param[in] uiSlot slot number
 * @param[in] eLkUnlk - parameter to lock/unlock/set PWD/clr PWD
 * @param[in] uiPwdLen - Password length
 * @param[in] pucPwdBuf - Password Buffer Pointer
 *
 * @retval _EMMC_ARG_INVALID Invalid argument sent
 * @retval _EMMC_OS_ERR_SEMAPHORE semaphore error
 * @retval _EMMC_SLOT_INVALID Slot is invalid
 * @retval _EMMC_REQ_INVALID invalid call to emmc_devLkUnlk
 * @retval _EMMC_STS_OK The function is successful
 */
emmc_sts_e emmc_devLkUnlk(
    _ub32 uiSlot,
    com_lkunlk_e eLkUnlk,
    _ub32 uiPwdLen,
    _ub8 *pucPwdBuf)
{
    dev_sts_e eSts = _DEV_STS_OK;
    _ub32 uiRet = 0;
    _ub32 uiLen=0;
    emmc_sts_e eRet;

    /* Validate the input arguments */
    /* Validate Slots */
    if(uiSlot >= _MAX_SLOTS)
    {
        return _EMMC_ARG_INVALID;
    }

    /* Validate elkunlk variable */
    if(eLkUnlk >= _COM_LKUNLK_INVALID)
    {
        return _EMMC_ARG_INVALID;
    }

    /* Validate Password length */
    if((0 == uiPwdLen) || (uiPwdLen > _EMMC_MAX_PWD_LEN) )
    {
        return _EMMC_ARG_INVALID;
    }

    /* Acquire lock before accessing partitions */
    uiRet = TAKE_SEM(&apiLock);
    if(0 != uiRet)
    {
        EMMC_ERR_DBG("emmc_devLkUnlk - TAKESEM: ERROR %d\n", uiRet);
        return _EMMC_OS_ERR_SEMAPHORE;
    }

    /* Check the validity of the slot */
    if(_SLOT_VALID != SlotValid[uiSlot])
    {
        REL_SEM(&apiLock);
        return _EMMC_SLOT_INVALID;
    }

    /* Check if emmc is initialized */
    if(_EMMC_INITIALIZE != initEntryFlag)
    {
        EMMC_ERR_DBG("emmc_init is not yet done!!\n");
        REL_SEM(&apiLock);
        return _EMMC_REQ_INVALID;
    }

    /* Copying password from host buffer to internal buffer */
    /* the 1st 2 bytes contain Header and Password Length **/
    for(uiLen=0;uiLen < uiPwdLen;uiLen++)
    {
        pioBuf[2+uiLen] = pucPwdBuf[uiLen];
    }

    /*
     * Calculating Data to be sent = Password Length
     *                           + Header Length(1byte)
     *                           + PWD_LEN field (1 byte)
     */
    pioBuf[1] = uiPwdLen;
    uiLen = 2 + uiPwdLen;

    /* Based on elkunlk creating 1Byte Header*/
    if(_COM_UNLOCK == eLkUnlk)
    {
        pioBuf[0]=_UNLOCK;
    }
    else if(_COM_LOCK == eLkUnlk)
    {
        pioBuf[0]=_LOCK;
    }
    else if(_COM_SET_PWD == eLkUnlk)
    {
        pioBuf[0]=_SETPWD;
    }
    else if(_COM_CLR_PWD == eLkUnlk)
    {
        pioBuf[0]=_CLRPWD;
    }
    else if(_COM_SET_PWD_LOCK == eLkUnlk)
    {
        pioBuf[0]=_SETPWD_LOCK;
    }
    /*
     * _COM_FORCE_ERASE_OTHER is for testing purpose only:
     * Following code will set Force erase bit and lock/unlock bit in the
     * lock device data structure. Device responds with an error.
     */
    else if(_COM_FORCE_ERASE_OTHER == eLkUnlk)
    {
         pioBuf[0]=_FORCE_ERASE_OTHER;
        uiLen = 1;
        pioBuf[1] = 0;
    }
    else
    {
        /* _COM_FORCE_ERASE == elkunlk */
        pioBuf[0]=_FORCE_ERASE;
        uiLen = 1;
        pioBuf[1] = 0;
    }

    /*
     * Setting Operation mode to PIO
     * Write protect status is received over DAT line
     */
    eRet = switchMode(
        uiSlot,
        uiLen,
        _COM_DIR_W,
        _CLR);
    if(_EMMC_STS_OK != eRet)
    {
        EMMC_ERR_DBG("switchMode:Error 0x%08x\n", eRet);
        REL_SEM(&apiLock); /* release lock before return */
        return eRet;
    }

    /* Calling the device layer function */
    eSts = dev_devLkUnlk(uiSlot,uiLen);

    if(_DEV_STS_OK != eSts)
    {
        EMMC_ERR_DBG("dev_devLkUnlk: Error 0x%08x\n", ERRRET(_DEV_ID, eSts));
        REL_SEM(&apiLock); /* release lock before return */
        return ERRRET(_DEV_ID, eSts);
    }

    /* Restoring the data transfer Context from PIO */
    eRet = switchMode(
        uiSlot,
        _BLK_SIZE,
        _COM_DIR_W,
        _SET);
    if(_EMMC_STS_OK != eRet)
    {
       EMMC_ERR_DBG("switchMode:Error 0x%08x\n",eRet);
       REL_SEM(&apiLock); /* release lock before return */
       return eRet;
    }

    REL_SEM(&apiLock);

    return _EMMC_STS_OK;
}

/**
 * @brief get the maximum sector count of the device
 *
 * @param[in] uiSlot slot number of the device
 * @param[out] uiSectCnt Pointer to hold sector count of the device
 *
 * @retval _EMMC_ARG_INVALID Invalid Argument sent
 * @retval _EMMC_SLOT_INVALID Slot is invalid
 * @retval _EMMC_REQ_INVALID invalid call to emmc_getDevMaxSect
 * @retval _EMMC_STS_OK Sector count is updated successfully in uiSectCnt
 */
emmc_sts_e emmc_getDevMaxSect(_ub32 uiSlot, _ub32 *uiSectCnt)
{
    /* Validate input parameters */
    if(uiSlot >= _MAX_SLOTS)
    {
        return _EMMC_ARG_INVALID;
    }
    if(NULL == uiSectCnt)
    {
        return _EMMC_ARG_INVALID;
    }

    /* Check the validity of the slot */
    if(_SLOT_VALID != SlotValid[uiSlot])
    {
        return _EMMC_SLOT_INVALID;
    }

    /* Check if emmc is initialized */
    if(_EMMC_INITIALIZE != initEntryFlag)
    {
        EMMC_ERR_DBG("emmc_init is not yet done!!\n");
        return _EMMC_REQ_INVALID;
    }

    /* Get the sector count from device layer */
    *uiSectCnt = seq_getSectCnt(uiSlot);

    return _EMMC_STS_OK;
}

/**
 * @brief get the device specific info from CSD register
 *
 * @param[in] uiSlot slot number of the device
 * @param[out] CSDParams CSD register values are stored
 *
 * @retval _EMMC_ARG_INVALID Invalid Argument sent
 * @retval _EMMC_SLOT_INVALID Slot is invalid
 * @retval _EMMC_REQ_INVALID invalid call to emmc_getDevInfo_CSD
 * @retval _EMMC_STS_OK CSD register contents are retrived successfully
 */
emmc_sts_e emmc_getDevInfo_CSD(
    _ub32 uiSlot,
    com_csd_params_t *pCSDParams)
{
    com_csd_params_t *pCSD = NULL;

    /* Validate input parameters */
    if(uiSlot >= _MAX_SLOTS)
    {
        return _EMMC_ARG_INVALID;
    }

    /* Check the validity of the slot */
    if(_SLOT_VALID != SlotValid[uiSlot])
    {
        return _EMMC_SLOT_INVALID;
    }

    /* Check if emmc is initialized */
    if(_EMMC_INITIALIZE != initEntryFlag)
    {
        EMMC_ERR_DBG("emmc_init is not yet done!!\n");
        return _EMMC_REQ_INVALID;
    }

    /* Get the device specific data from CSD register from device layer */
    pCSD = seq_getCSD(uiSlot);

    *pCSDParams = *pCSD;

    return _EMMC_STS_OK;
}

/**
 * @brief get the device specific info from CID register
 *
 * @param[in] uiSlot slot number of the device
 * @param[out] CIDParams CID register values are stored
 *
 * @retval _EMMC_ARG_INVALID Invalid Argument sent
 * @retval _EMMC_SLOT_INVALID Slot is invalid
 * @retval _EMMC_REQ_INVALID invalid call to emmc_getDevInfo_CID
 * @retval _EMMC_STS_OK CID register contents are retrived successfully
 */
emmc_sts_e emmc_getDevInfo_CID(
    _ub32 uiSlot,
    com_cid_params_t *pCIDParams)
{
    com_cid_params_t *pCID = NULL;

    /* Validate input parameters */
    if(uiSlot >= _MAX_SLOTS)
    {
        return _EMMC_ARG_INVALID;
    }

    /* Check the validity of the slot */
    if(_SLOT_VALID != SlotValid[uiSlot])
    {
        return _EMMC_SLOT_INVALID;
    }

    /* Check if emmc is initialized */
    if(_EMMC_INITIALIZE != initEntryFlag)
    {
        EMMC_ERR_DBG("emmc_init is not yet done!!\n");
        return _EMMC_REQ_INVALID;
    }

    /* Get the device identification info from CID register from seq layer */
    pCID = seq_getCID(uiSlot);

    *pCIDParams = *pCID;

    return _EMMC_STS_OK;
}

/**
 * @brief get emmc driver version
 *
 * @param[out] puiVersion 32 bit pointer variable to hold version
 *
 * @retval _EMMC_ARG_INVALID Invalid Argument sent
 * @retval _EMMC_STS_OK No error and emmc_getVersion successful
 */
emmc_sts_e emmc_getVersion(_ub32 *puiVersion)
{
    /* Validate input parameters */
    if(NULL == puiVersion)
    {
        return _EMMC_ARG_INVALID;
    }

    /* Update the version information into the pointer */
    *puiVersion = (_ub32)_EMMC_DRV_VERSION;

    return _EMMC_STS_OK;
}

/**
 * @brief Gets the General Purpose Partition attributes of the device.
 *
 * @param[in]  uiSlot slot number
 * @param[in]  ePartNum the partition for which attributes is requested
 * @param[out] pPartAttr the pointer in which the attributes are returned
 *
 * @retval _EMMC_ARG_INVALID Invalid argument sent
 * @retval _EMMC_SLOT_INVALID Slot is invalid
 * @retval _EMMC_REQ_INVALID invalid call to emmc_getGPPAttributes
 * @retval _EMMC_DEV_PART_INVALID Invalid partition number given as i/p
 * @retval _EMMC_DEV_PART_NOT_CREATED Partition is not created
 * @retval _EMMC_STS_OK The function is successful
 */
emmc_sts_e emmc_getGPPAttributes(
    _ub32 uiSlot,
    com_part_num_e ePartNum,
    com_gpp_attr_t *pPartAttr)
{
    _b32 sts = 0;
    _ub32 ret = 0;

    /* Validate the input arguments */
    if(uiSlot >= _MAX_SLOTS)
    {
        return _EMMC_ARG_INVALID;
    }

    /* If partition number is invalid return error */
    if((_COM_PARTITION_UDA == ePartNum) || (ePartNum >= _COM_PARTITION_MAX))
    {
        return _EMMC_ARG_INVALID;
    }

    if(NULL == pPartAttr)
    {
        return _EMMC_ARG_INVALID;
    }

    /* Acquire lock before getting GPP attributes */
    ret = TAKE_SEM(&apiLock);
    if(0 != ret)
    {
        EMMC_ERR_DBG("emmc_getGPPAttributes-TAKESEM: ERROR %d\n", ret);
        return _EMMC_OS_ERR_SEMAPHORE;
    }

    /* Check the validity of the slot */
    if(_SLOT_VALID != SlotValid[uiSlot])
    {
        REL_SEM(&apiLock);
        return _EMMC_SLOT_INVALID;
    }

    /* Check if emmc is initialized */
    if(_EMMC_INITIALIZE != initEntryFlag)
    {
        EMMC_ERR_DBG("emmc_init is not yet done!!\n");
        REL_SEM(&apiLock);
        return _EMMC_REQ_INVALID;
    }

    /* Get the GPP Atrributes from the device */
    sts = pm_getGPPAttributes(uiSlot, ePartNum, pPartAttr);
    if(_DEV_STS_OK != (dev_sts_e)sts)
    {
        if(_DEV_PARTITION_NOT_CREATED == (dev_sts_e)sts)
        {
            EMMC_OPT_DBG("pm_getGPPAttributes: Partition not created.\n");
        }
        REL_SEM(&apiLock); /* release lock before return */
        return ERRRET(_DEV_ID, sts);
    }

    REL_SEM(&apiLock);
    return _EMMC_STS_OK;
}

/**
 * @brief Gets the Enhanced User Data Area attributes of the device.
 *
 * @param[in]  uiSlot slot number
 * @param[out] pPartAttr the pointer in which the attributes are returned
 *
 * @retval _EMMC_ARG_INVALID Invalid argument sent
 * @retval _EMMC_SLOT_INVALID Slot is invalid
 * @retval _EMMC_REQ_INVALID invalid call to emmc_getEUDAAttributes
 * @retval _EMMC_DEV_PART_NOT_CREATED Partition is not created
 * @retval _EMMC_STS_OK The function is successful
 */
emmc_sts_e emmc_getEUDAAttributes(
    _ub32 uiSlot,
    com_euda_attr_t *pPartAttr)
{
    _b32 sts = 0;
    _ub32 ret = 0;

    /* Validate the input arguments */
    if(uiSlot >= _MAX_SLOTS)
    {
        return _EMMC_ARG_INVALID;
    }

    if(NULL == pPartAttr)
    {
        return _EMMC_ARG_INVALID;
    }

    /* Acquire lock before getting EUDA attributes */
    ret = TAKE_SEM(&apiLock);
    if(0 != ret)
    {
        EMMC_ERR_DBG("emmc_getEUDAAttributes-TAKESEM: ERROR %d\n", ret);
        return _EMMC_OS_ERR_SEMAPHORE;
    }

    /* Check the validity of the slot */
    if(_SLOT_VALID != SlotValid[uiSlot])
    {
        REL_SEM(&apiLock);
        return _EMMC_SLOT_INVALID;
    }

    /* Check if emmc is initialized */
    if(_EMMC_INITIALIZE != initEntryFlag)
    {
        EMMC_ERR_DBG("emmc_init is not yet done!!\n");
        REL_SEM(&apiLock);
        return _EMMC_REQ_INVALID;
    }

    /* Get the EUDA Atrributes from the device */
    sts = pm_getEUDAAttributes(uiSlot, pPartAttr);
    if(_DEV_STS_OK != (dev_sts_e)sts)
    {
        EMMC_ERR_DBG("pm_getEUDAAttributes: Error 0x%08x\n",
            ERRRET(_DEV_ID, sts));
        REL_SEM(&apiLock); /* release lock before return */
        return ERRRET(_DEV_ID, sts);
    }

    REL_SEM(&apiLock); /* release lock before return */

    return _EMMC_STS_OK;
}

/**
 * @brief Sets the Access to the appropriate partition in the device.
 *
 * @param[in]  uiSlot slot number
 * @param[in]  ePartNum the partition number to be accessed
 *
 * @retval _EMMC_ARG_INVALID Invalid argument sent
 * @retval _EMMC_SLOT_INVALID Slot is invalid
 * @retval _EMMC_REQ_INVALID invalid call to emmc_accessPartitions
 * @retval _EMMC_DEV_PART_INVALID Invalid partition number given as i/p
 * @retval _EMMC_DEV_PART_NOT_CREATED Partition is not created
 * @retval _EMMC_STS_OK The function is successful
 */
emmc_sts_e emmc_accessPartitions(
    _ub32 uiSlot,
    com_part_num_e ePartNum)
{
    _b32 sts = 0;
    _ub32 ret = 0;

    /* Validate the input arguments */
    if(uiSlot >= _MAX_SLOTS)
    {
        return _EMMC_ARG_INVALID;
    }

    if(ePartNum >= _COM_PARTITION_MAX)
    {
        return _EMMC_ARG_INVALID;
    }

    /* Acquire lock before accessing partitions */
    ret = TAKE_SEM(&apiLock);
    if(0 != ret)
    {
        EMMC_ERR_DBG("emmc_accessPartitions-TAKESEM: ERROR %d\n", ret);
        return _EMMC_OS_ERR_SEMAPHORE;
    }

    /* Check the validity of the slot */
    if(_SLOT_VALID != SlotValid[uiSlot])
    {
        REL_SEM(&apiLock);
        return _EMMC_SLOT_INVALID;
    }

    /* Check if emmc is initialized */
    if(_EMMC_INITIALIZE != initEntryFlag)
    {
        EMMC_ERR_DBG("emmc_init is not yet done!!\n");
        REL_SEM(&apiLock);
        return _EMMC_REQ_INVALID;
    }

    /* Set the Access to the required partition */
    sts = pm_accessPartitions(uiSlot, ePartNum);
    if(_DEV_STS_OK != (dev_sts_e)sts)
    {
        EMMC_ERR_DBG("pm_accessPartitions: Error 0x%08x\n",
            ERRRET(_DEV_ID, sts));
        REL_SEM(&apiLock); /* release lock before return */
        return ERRRET(_DEV_ID, sts);
    }

    REL_SEM(&apiLock);

    return _EMMC_STS_OK;
}

/**
 * @brief gets the current accessed partition
 *
 * @param[in]  slot number
 * @param[out] uiPartNum The current accessed partition
 *
 * @retval _EMMC_ARG_INVALID Invalid Argument sent
 * @retval _EMMC_SLOT_INVALID Slot is invalid
 * @retval _EMMC_REQ_INVALID invalid call to emmc_getCurrPartition
 * @retval _EMMC_STS_OK The API is successful
 */
emmc_sts_e emmc_getCurrPartition(_ub32 uiSlot, _ub32 *puiPartNum)
{
    _ub32 ret = 0;

    /* Validate the input arguments */
    if(uiSlot >= _MAX_SLOTS)
    {
        return _EMMC_ARG_INVALID;
    }

    if(NULL == puiPartNum)
    {
        return _EMMC_ARG_INVALID;
    }

    /* Acquire lock before getting current partition acessed */
    ret = TAKE_SEM(&apiLock);
    if(0 != ret)
    {
        EMMC_ERR_DBG("emmc_getCurrPartition-TAKESEM: ERROR %d\n", ret);
        return _EMMC_OS_ERR_SEMAPHORE;
    }

    /* Check the validity of the slot */
    if(_SLOT_VALID != SlotValid[uiSlot])
    {
        REL_SEM(&apiLock);
        return _EMMC_SLOT_INVALID;
    }

    /* Check if emmc is initialized */
    if(_EMMC_INITIALIZE != initEntryFlag)
    {
        EMMC_ERR_DBG("emmc_init is not yet done!!\n");
        REL_SEM(&apiLock);
        return _EMMC_REQ_INVALID;
    }

    *puiPartNum = (_ub32)pm_getCurrPartition(uiSlot);

    REL_SEM(&apiLock);

    return _EMMC_STS_OK;
}

/**
 * @brief Gets the Maximum Enhance Size allowed in the device.
 *
 * @param[in]  uiSlot slot number
 * @param[out] puiMaxEnhSize Pointer to hold the Maximum Enhance Size in sectors
 *
 * @retval _EMMC_ARG_INVALID Invalid argument sent
 * @retval _EMMC_SLOT_INVALID Slot is invalid
 * @retval _EMMC_REQ_INVALID invalid call to emmc_getMaxEnhSize
 * @retval _EMMC_STS_OK The function executed successfully
 */
emmc_sts_e emmc_getMaxEnhSize(_ub32 uiSlot, _ub32 *puiMaxEnhSize)
{
    _ub32 ret = 0;

    /* Validate the input arguments */
    if(uiSlot >= _MAX_SLOTS)
    {
        return _EMMC_ARG_INVALID;
    }

    if(NULL == puiMaxEnhSize)
    {
        return _EMMC_ARG_INVALID;
    }

    /* Acquire lock before getting max. enhanced size */
    ret = TAKE_SEM(&apiLock);
    if(0 != ret)
    {
        EMMC_ERR_DBG("emmc_getMaxEnhSize-TAKESEM: ERROR %d\n", ret);
        return _EMMC_OS_ERR_SEMAPHORE;
    }

    /* Check the validity of the slot */
    if(_SLOT_VALID != SlotValid[uiSlot])
    {
        REL_SEM(&apiLock);
        return _EMMC_SLOT_INVALID;
    }

    /* Check if emmc is initialized */
    if(_EMMC_INITIALIZE != initEntryFlag)
    {
        EMMC_ERR_DBG("emmc_init is not yet done!!\n");
        REL_SEM(&apiLock);
        return _EMMC_REQ_INVALID;
    }

    /* Get the maximum enhanced size from device layer */
    *puiMaxEnhSize = pm_getMaxEnhSize(uiSlot);

    REL_SEM(&apiLock);

    return _EMMC_STS_OK;
}

/**
 * @brief Gets the High Capacity Write Protect Group Size of the device.
 *
 * @param[in]  uiSlot slot number
 * @param[out] puiSize Pointer to hold the HCWPG Size
 *
 * @retval _EMMC_ARG_INVALID Invalid argument sent
 * @retval _EMMC_SLOT_INVALID Slot is invalid
 * @retval _EMMC_REQ_INVALID invalid call to emmc_getHCWPGrpSize
 * @retval _EMMC_STS_OK The function executed successfully
 */
emmc_sts_e emmc_getHCWPGrpSize(_ub32 uiSlot, _ub32 *puiSize)
{
    _ub32 ret = 0;

    /* Validate the input arguments */
    if(uiSlot >= _MAX_SLOTS)
    {
        return _EMMC_ARG_INVALID;
    }

    if(NULL == puiSize)
    {
        return _EMMC_ARG_INVALID;
    }

    /* Acquire lock before getting High Capacity WPG Size */
    ret = TAKE_SEM(&apiLock);
    if(0 != ret)
    {
        EMMC_ERR_DBG("emmc_getHCWPGrpSize-TAKESEM: ERROR %d\n", ret);
        return _EMMC_OS_ERR_SEMAPHORE;
    }

    /* Check the validity of the slot */
    if(_SLOT_VALID != SlotValid[uiSlot])
    {
        REL_SEM(&apiLock);
        return _EMMC_SLOT_INVALID;
    }

    /* Check if emmc is initialized */
    if(_EMMC_INITIALIZE != initEntryFlag)
    {
        EMMC_ERR_DBG("emmc_init is not yet done!!\n");
        REL_SEM(&apiLock);
        return _EMMC_REQ_INVALID;
    }

    /* Get the high capacity write protect group size from device layer */
    *puiSize = pm_getHCWPGrpSize(uiSlot);

    REL_SEM(&apiLock);

    return _EMMC_STS_OK;
}

/**
 * @brief Gets the Write Protect Group Size of the device.
 *
 * @param[in]  uiSlot slot number
 * @param[out] puiSize Pointer to hold the HCWPG Size
 *
 * @retval _EMMC_ARG_INVALID Invalid argument sent
 * @retval _EMMC_SLOT_INVALID Slot is invalid
 * @retval _EMMC_REQ_INVALID invalid call to emmc_getWPGrpSize
 * @retval _EMMC_STS_OK The function executed successfully
 */
emmc_sts_e emmc_getWPGrpSize(_ub32 uiSlot, _ub32 *puiSize)
{
    _ub32 ret = 0;

    /* Validate the input arguments */
    if(uiSlot >= _MAX_SLOTS)
    {
        return _EMMC_ARG_INVALID;
    }

    if(NULL == puiSize)
    {
        return _EMMC_ARG_INVALID;
    }

    /* Acquire lock before getting WPG Size */
    ret = TAKE_SEM(&apiLock);
    if(0 != ret)
    {
        EMMC_ERR_DBG("emmc_getWPGrpSize-TAKESEM: ERROR %d\n", ret);
        return _EMMC_OS_ERR_SEMAPHORE;
    }

    /* Check the validity of the slot */
    if(_SLOT_VALID != SlotValid[uiSlot])
    {
        REL_SEM(&apiLock);
        return _EMMC_SLOT_INVALID;
    }

    /* Check if emmc is initialized */
    if(_EMMC_INITIALIZE != initEntryFlag)
    {
        EMMC_ERR_DBG("emmc_init is not yet done!!\n");
        REL_SEM(&apiLock);
        return _EMMC_REQ_INVALID;
    }

    /* Get the write protect group size from device layer */
    *puiSize = seq_getWPGrpSize(uiSlot);

    REL_SEM(&apiLock);

    return _EMMC_STS_OK;
}


/**
 * @brief Gets the Erase Group Size of the device.
 *
 * @param[in]  uiSlot slot number
 * @param[out] puiSize Pointer to hold the Erase Group Size
 *
 * @retval _EMMC_ARG_INVALID Invalid argument sent
 * @retval _EMMC_SLOT_INVALID Slot is invalid
 * @retval _EMMC_REQ_INVALID invalid call to emmc_getErsGrpSize
 * @retval _EMMC_STS_OK The function executed successfully
 */
emmc_sts_e emmc_getErsGrpSize(_ub32 uiSlot, _ub32 *puiSize)
{
    _ub32 ret = 0;

    /* Validate the input arguments */
    if(uiSlot >= _MAX_SLOTS)
    {
        return _EMMC_ARG_INVALID;
    }

    if(NULL == puiSize)
    {
        return _EMMC_ARG_INVALID;
    }

    /* Acquire lock before getting WP Erase Group Size */
    ret = TAKE_SEM(&apiLock);
    if(0 != ret)
    {
        EMMC_ERR_DBG("emmc_getWPErsGrpSize-TAKESEM: ERROR %d\n", ret);
        return _EMMC_OS_ERR_SEMAPHORE;
    }

    /* Check the validity of the slot */
    if(_SLOT_VALID != SlotValid[uiSlot])
    {
        REL_SEM(&apiLock);
        return _EMMC_SLOT_INVALID;
    }

    /* Check if emmc is initialized */
    if(_EMMC_INITIALIZE != initEntryFlag)
    {
        EMMC_ERR_DBG("emmc_init is not yet done!!\n");
        REL_SEM(&apiLock);
        return _EMMC_REQ_INVALID;
    }

    /* Get the erase group size from device layer */
    *puiSize = seq_getErsGrpSize(uiSlot);

    REL_SEM(&apiLock);

    return _EMMC_STS_OK;
}

/**
 * @brief Gets the Erase memory content of the device.
 *
 * @param[in]  uiSlot slot number
 * @param[out] pucErsMemCont Pointer to hold the erase memory content
 *
 * @retval _EMMC_ARG_INVALID Invalid argument sent
 * @retval _EMMC_SLOT_INVALID Slot is invalid
 * @retval _EMMC_REQ_INVALID invalid call to emmc_getErsMemContent
 * @retval _EMMC_STS_OK The function executed successfully
 */
emmc_sts_e emmc_getErsMemContent(_ub32 uiSlot, _ub8 *pucErsMemCont)
{
    _ub32 ret = 0;

    /* Validate the input arguments */
    if(uiSlot >= _MAX_SLOTS)
    {
        return _EMMC_ARG_INVALID;
    }

    if(NULL == pucErsMemCont)
    {
        return _EMMC_ARG_INVALID;
    }

    /* Acquire lock before getting Erase Memory Content Size */
    ret = TAKE_SEM(&apiLock);
    if(0 != ret)
    {
        EMMC_ERR_DBG("emmc_getErsMemContent-TAKESEM: ERROR %d\n", ret);
        return _EMMC_OS_ERR_SEMAPHORE;
    }

    /* Check the validity of the slot */
    if(_SLOT_VALID != SlotValid[uiSlot])
    {
        REL_SEM(&apiLock);
        return _EMMC_SLOT_INVALID;
    }

    /* Check if emmc is initialized */
    if(_EMMC_INITIALIZE != initEntryFlag)
    {
        EMMC_ERR_DBG("emmc_init is not yet done!!\n");
        REL_SEM(&apiLock);
        return _EMMC_REQ_INVALID;
    }

    /* Get the erase memory content from device layer */
    *pucErsMemCont = seq_getErsMemContent(uiSlot);

    REL_SEM(&apiLock);

    return _EMMC_STS_OK;

}

/**
 * @brief Creates the partition in the device.
 *
 * @param[in] uiSlot Slot number
 * @param[in] uiNumGpps Number of GPPs to be created
 * @param[in] pAttr Struct pointer pointing to GPP & EUDA attr.
 *
 * @retval _EMMC_ARG_INVALID Invalid argument sent
 * @retval _EMMC_SLOT_INVALID Slot is invalid
 * @retval _EMMC_OS_ERR_SEMAPHORE Error acquiring semaphore
 * @retval _EMMC_REQ_INVALID invalid call to emmc_createPartition
 * @retval _EMMC_STS_OK The function executed successfully
 * @retval Error code from lower layers
 *
 * Important Note: This function is not re-entrant.
 */
emmc_sts_e emmc_createPartition(
    _ub32 uiSlot,
    _ub32 uiNumGpps,
    com_part_attr_t *pAttr)
{
    _b32 sts = 0;
    _ub32 ret = 0;

    /* Validate the input arguments */
    if(uiSlot >= _MAX_SLOTS)
    {
        return _EMMC_ARG_INVALID;
    }

    /* if num of partns > 4 return error */
    if(uiNumGpps > _EMMC_MAX_GPPS)
    {
        return _EMMC_DEV_MAX_PARTS_EXCEEDED;
    }

    if(NULL == pAttr)
    {
        return _EMMC_ARG_INVALID;
    }

    /* Only if both are NULL, return error */
    if((NULL == pAttr->pEattr) && (NULL == pAttr->pGattr))
    {
        return _EMMC_ARG_INVALID;
    }

    /* Acquire lock before creating partition */
    ret = TAKE_SEM(&apiLock);
    if(0 != ret)
    {
        EMMC_ERR_DBG("emmc_createPartition-TAKESEM: ERROR %d\n", ret);
        return _EMMC_OS_ERR_SEMAPHORE;
    }

    /* Check the validity of the slot */
    if(_SLOT_VALID != SlotValid[uiSlot])
    {
        REL_SEM(&apiLock);
        return _EMMC_SLOT_INVALID;
    }

    /* Check if emmc is initialized */
    if(_EMMC_INITIALIZE != initEntryFlag)
    {
        EMMC_ERR_DBG("emmc_init is not yet done!!\n");
        REL_SEM(&apiLock);
        return _EMMC_REQ_INVALID;
    }

    /* Create the partition in the device */
    sts = pm_createPartition(uiSlot, uiNumGpps, pAttr);
    if(_DEV_STS_OK != (dev_sts_e)sts)
    {
        EMMC_ERR_DBG("pm_createPartition: Error 0x%08x\n",
            ERRRET(_DEV_ID, sts));
        REL_SEM(&apiLock); /* release lock before return */
        return ERRRET(_DEV_ID, sts);
    }

    REL_SEM(&apiLock); /* release lock before return */
    return _EMMC_STS_OK;
}

/**
 * @brief Disable emulation mode for the device.
 *
 * @param[in] uiSlot Slot Number
 *
 * @retval _EMMC_ARG_INVALID Invalid argument sent
 * @retval _EMMC_SLOT_INVALID Slot is invalid
 * @retval _EMMC_REQ_INVALID invalid call to emmc_disableEmulationMode
 * @retval _EMMC_STS_OK The function executed successfully
 * @retval _EMMC_OS_ERR_SEMAPHORE for semaphore fails
 * @retval _EMMC_DEV_ALREADY_DONE for operation done already
 */
emmc_sts_e emmc_disableEmulationMode(_ub32 uiSlot)
{
    _b32 sts = 0;
    _ub32 ret = 0;

    /* Validate the input arguments */
    if(uiSlot >= _MAX_SLOTS)
    {
        return _EMMC_ARG_INVALID;
    }

    /* Acquire lock before disabling emulation mode */
    ret = TAKE_SEM(&apiLock);
    if(0 != ret)
    {
        EMMC_ERR_DBG("emmc_read-TAKESEM: ERROR %d\n", ret);
        return _EMMC_OS_ERR_SEMAPHORE;
    }

    /* Check the validity of the slot */
    if(_SLOT_VALID != SlotValid[uiSlot])
    {
        REL_SEM(&apiLock);
        return _EMMC_SLOT_INVALID;
    }

    /* Check if emmc is initialized */
    if(_EMMC_INITIALIZE != initEntryFlag)
    {
        EMMC_ERR_DBG("emmc_init is not yet done!!\n");
        REL_SEM(&apiLock);
        return _EMMC_REQ_INVALID;
    }

    sts = seq_disableEmulationMode(uiSlot);
    if(_DEV_STS_OK != (dev_sts_e)sts)
    {
        EMMC_ERR_DBG("seq_disableEmulationMode: Emulation Mode already\
        Disabled\n");
        REL_SEM(&apiLock); /* release lock before return */
        return ERRRET(_DEV_ID, sts);
    }

    REL_SEM(&apiLock); /* release lock before return */
    return _EMMC_STS_OK;
}

/**
 * @brief API to cleanup the resources acquired during emmc init
 *
 * @param[in] uiLevel indicates from which level should exit happen
 *
 * @retval _EMMC_STS_OK No error and emmc_exit successful
 * @retval err Error code
 */
static emmc_sts_e cleanup(_ub32 uiLevel)
{
    _ub32 irq = 0;
    _b32 sts = 0;
    emmc_sts_e err = _EMMC_STS_OK;

    EMMC_OPT_DBG("\n\n******EMMC EXIT*******\n");

    /* Fall through is intended, so no break statement is used. */
    switch(uiLevel)
    {
        case _EXIT_LVL_ALL:
            /* De-allocate the buffer handlers */
            sts = (_b32)bm_exit();
            if(_BM_STS_OK != (bm_sts_e)sts)
            {
                err = ERRRET(_BM_ID, sts);
                EMMC_ERR_DBG("bm_exit: ERROR 0x%08x\n", err);
            }

        case _EXIT_LVL_BM:
            /* De-allocate the command sequences layer */
            sts = (_b32)seq_exit(SlotValid);
            if(_DEV_STS_OK != (dev_sts_e)sts)
            {
                err = ERRRET(_DEV_ID, sts);
                EMMC_ERR_DBG("seq_exit: ERROR 0x%08x\n", err);
            }

        case _EXIT_LVL_DEV:
            /* get the irq for de-registering interrupt */
            irq = os_getIRQ();

            /* De-register the interrupt */
            os_deregisterIntr(irq);

        case _EXIT_LVL_REGINTR:
            /* De-initialize interrupt resources */
            sts = (_b32)intr_exit();
            if(_INTR_OK != (intr_sts_e)sts)
            {
                err = ERRRET(_INTR_ID, sts);
                EMMC_ERR_DBG("intr_exit: ERROR 0x%08x\n", err);
            }

        case _EXIT_LVL_INTR:
            /* Reset the host controller */
            hc_exit();

        case _EXIT_LVL_HC:
             /* De-initialize the OS services */
            sts = os_exit();
            if(_OS_OK != (os_sts_e)sts)
            {
                err = ERRRET(_OS_ID, sts);
                EMMC_ERR_DBG("os_exit: ERROR 0x%08x\n", err);
            }
            break;
        default:
            EMMC_ERR_DBG("cleanup called with wrong param \n");
    }

    EMMC_OPT_DBG("\n***********************************************\n");

    /*
     * Currently returns the latest error status,
     * critical message will be given for all
     */
    return err;
}

/**
 * @brief Function to initialize the HC config params
 *
 * @param[in] uiSlot Slot number to update the params
 * @param[in] hcCfg HC config structure
 *
 * @retval None
 */
static void initHCParams(_ub32 uiSlot, hcCfgParams_t *hcCfg)
{
    /* static function, so no input arg check required */

    /* Initialize the structure with default values */
    hcCfg->usBlksize = _BLK_SIZE;
    hcCfg->usPwrCtrl = _COM_VOLT1_8;
    hcCfg->usBusSpeed = _COM_SPEED_NORMAL;
    hcCfg->uiClkFreq = _DEF_CLK_FREQ;
    hcCfg->usBusWidth = _COM_BWIDTH_1;
    hcCfg->usMode = _COM_MODE_SDMA;
    hcCfg->usHostVersion = _HOST_VERSION;
    hcCfg->uiSlot = uiSlot;
    hcCfg->uiDirtyFlag = 0;

    EMMC_OPT_DBG("TEST: initHCParams done.\n");
    EMMC_OPT_DBG("BlkSize = %d\n",hcCfg->usBlksize);
    EMMC_OPT_DBG("PwrCtrl = %d\n",hcCfg->usPwrCtrl);
    EMMC_OPT_DBG("BusSpeed = %d\n",hcCfg->usBusSpeed);
    EMMC_OPT_DBG("ClkFreq = %d\n",hcCfg->uiClkFreq);
    EMMC_OPT_DBG("BusWidth = %d\n",hcCfg->usBusWidth);
    EMMC_OPT_DBG("Mode = %d\n",hcCfg->usMode);

    return;
}

/**
 * @brief Function to initialize the eMMC config params
 *
 * @param[in] uiSlot Slot number to update the params
 * @param[in] devCfg eMMC config structure
 *
 * @retval None
 */
static void initDevParams(_ub32 uiSlot, devCfgParams_t *devCfg)
{

    /* static function, so no input arg check required */

    /* Initialize the strutcure with default values */
    devCfg->usBlksize = _BLK_SIZE;
    devCfg->usCardVersion = _CARD_VERSION;
    devCfg->usBusWidth = _COM_BWIDTH_1;
    devCfg->usNumPartitions = _NUM_PARTITIONS;
    devCfg->uiSlot = uiSlot;
    devCfg->uiDirtyFlag = 0;

    EMMC_OPT_DBG("TEST: initDevParams done. Values\n");
    EMMC_OPT_DBG("BlkSize = %d\n",devCfg->usBlksize);
    EMMC_OPT_DBG("BusWidth = %d\n",devCfg->usBusWidth);
    EMMC_OPT_DBG("NumPartitions = %d\n",devCfg->usNumPartitions);

    return;
}

/**
 * @brief Wrapper Function to call the HC and dev initialization functions
 *
 * @param None
 *
 * @retval None
 */
static void initDB(void)
{
    _ub32 i;

    /* static function, so no input arg check required */

    /* This is a wrapper function which calls hc and dev init functions */
    for(i = 0; i < _MAX_SLOTS; i++)
    {
        /* Initialize the hcCfgParams_t structure with default values */
        initHCParams(i, &hcCfg[i]);
        /* Initialize devCfgParams_t structure with default values */
        initDevParams(i, &devCfg[i]);
    }

    EMMC_OPT_DBG("TEST: initDB done\n");
    return;
}

/**
 * @brief Used to set mode to PIO when required and to restore it to old mode
 *
 * @param[in] uiSlot slot number
 * @param[in] uiSize - Input Buffer size
 * @param[in] eDirection - Read /Write direction
 * @param[in] ucSetClrMode - _CLR: Set to PIO mode, _SET: Restore the old mode
 *
 * @retval _EMMC_STS_OK The function is successful
 */
static emmc_sts_e switchMode(
    _ub32 uiSlot,
    _ub32 uiSize,
    com_RWDir_e eDirection,
    _ub8 ucSetClrMode)
{
    hc_sts_e eHcSts = _HC_STS_OK;
    bm_sts_e eBmSts = _BM_STS_OK;
    com_modes_e eMode;

    /* Set mode to PIO when requested */
    if(ucSetClrMode == _CLR)
    {
        eMode = _COM_MODE_PIO;
    }
    /* Restore to the old mode once operation using PIO mode is completed */
    else
    {
        eMode = (com_modes_e)hcCfg[uiSlot].usMode;
    }

    /* Call HC layer function to set the operation mode */
    eHcSts = hc_setOpMode(uiSlot, eMode);
    if(_HC_STS_OK != eHcSts)
    {
        EMMC_ERR_DBG("hc_setOpMode:Error 0x%08x\n", ERRRET(_HC_ID, eHcSts));
        return ERRRET(_HC_ID, eHcSts);
    }

    /* Perform the reqd config for PIO mode of operation */
    if(ucSetClrMode == _CLR)
    {
        /* configuring pio structure for PIO data transfer */
        eBmSts = bm_config(uiSlot, pioBuf, uiSize, eDirection);
        if(_BM_STS_OK != eBmSts)
        {
            EMMC_ERR_DBG("bm_config: Error 0x%08x\n", ERRRET(_BM_ID, eBmSts));
            return ERRRET(_BM_ID, eBmSts);
        }

        /* configuring Host Control 1 register for PIO */
        eHcSts = hc_setDataParams(uiSlot, uiSize, eDirection);
        if(_HC_STS_OK != eHcSts)
        {
            EMMC_ERR_DBG("hc_setDataParams: Error 0x%08x\n",
                ERRRET(_HC_ID, eHcSts));
            return ERRRET(_HC_ID, eHcSts);
        }
    }

    /* configuring Block_size to reqd value */
    hc_setBlockSize(uiSlot, uiSize);

    return _EMMC_STS_OK;
}

/**@} *//* API_Functions */

/**@} *//* EMMCAPIs */
/**@}*//* EMMC Memory Interface */

