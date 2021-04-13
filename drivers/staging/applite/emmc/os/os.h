/**
 * @file          os.h
 *
 * \brief         Header file for OS Abstraction Layer.
 *
 * \b COPYRIGHT : TOSHIBA Corporation Semiconductor and Storage Company
 *                2010-2015 All rights reserved
 *
 * \b Project   : Glenfiddich
 *
 * \b Version   : 0.3
 *
 * \b Release   : None
 *
 * \b Date      : 28-Jun-2013
 */


/**
 * @addtogroup AbstractionLayer
 * @{
 */

/**
 * @addtogroup OSServices
 * @{
 */

#ifndef _OS_H_
#define _OS_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*----------------------- Header Files Inclusions ----------------------------*/
#include "os_specific_func.h"    /* For OS specific functions */
#include "types.h"               /* Custom type defs */
#include "com.h"                 /* Common definitions */
/*-------------------------- Macro Definitions -------------------------------*/

/** @addtogroup OS_DEFINES OS_DEFINES
 * @{
 */

/* Macros for debugging */
#ifdef __DEBUG
#define _OS_DBG_INFO(__format__, arg...)    \
       dz_print(_DZ_CRTICAL, " OS: %s::" __format__,__FUNCTION__,## arg )
#define _OS_DBG_ERR(__format__, arg...)    \
       dz_print(_DZ_CRTICAL, " OS: %s::" __format__,__FUNCTION__,## arg )
#else
#define _OS_DBG_INFO(__format__, arg...)    /*  */
#define _OS_DBG_ERR(__format__, arg...)    /*  */
#endif

/**@}*/ // OS_DEFINES

/*-------------------------- Enum Definitions --------------------------------*/

/** @addtogroup OS_Enums OS_Enums
 * @{
 */

/**
 * @brief Enums for OS function call status
 */
typedef enum tag_os_sts_e
{
    _OS_OK                  = 0x0000,  /**< OS call successful */
    _OS_ERR_DRV_REG         = 0x0001,  /**< Driver registration error */
    _OS_ERR_IRQ_RETRV       = 0x0002,  /**< Error in retrieving Irq*/
    _OS_ERR_TASK_CREATION   = 0x0003,  /**< Err in creating tasks Ex Threads */
    _OS_ERR_TASK_DELETION   = 0x0004,  /**< Err in deleting tasks  Ex Threads */
    _OS_ERR_MEM_ALLOC_FAIL  = 0x0005,  /**< Error in allocating memory */
    _OS_ERR_DMEM_ALLOC_FAIL = 0x0006,  /**< Error in allocating DMA memory */
    _OS_ERR_INTR_REG        = 0x0007,  /**< Error in registering interrupt */
    _OS_ERR_CREATE_TIMER    = 0x0008,  /**< Error in creating timer */
    _OS_ERR_DELETE_TIMER    = 0x0009,  /**< Error in deleting timer */
    _OS_ERR_CREATE_LOCK     = 0x000A,  /**< Error in creating lock */
    _OS_ERR_DELETE_LOCK     = 0x000B,  /**< Error in deleting lock */
    _OS_ERR_WAIT_TIMEOUT    = 0x000C,  /**< Error in synchronization */
    _OS_ERR_INVALID_CALLBACK_FUNCTION = 0x000D, /**< Error in call back func */
    _OS_ERR_MOD_TIMER       = 0x000E,  /**< Error in modifying timer */
    _OS_ERR_PARAM           = 0x000F,  /**< Error in function arguments */
    _OS_ERR_SEMAPHORE       = 0x0010,  /**< Error in taking semaphore */
    _OS_ERR_RESOURCE        = 0x0011,  /**< Resource access error */
    _OS_ERR_MEMCMP          = 0x0012,  /**< Error in memory comparison*/
    _OS_ERR_OBTRES          = 0x0013,  /**< Error in obtaining OS resources */
    _OS_ERR_MAP             = 0X0014,  /**< Error in mapping address */
    _OS_ERR_PROBE_PLTDRV    = 0x0015,  /**< Err in getting platform resources */
    _OS_ERR_PROBE_PCIDRV    = 0x0016,  /**< Error in Probing PCI device */
    _OS_STS_INVALID         = 0x0017,  /**< Invalid error status */
} os_sts_e;

/**@}*/ //end of OS_Enums

/*------------------ Data Structures & Custom Typedefs -----------------------*/

/** @addtogroup OS_Typedef OS_Typedef
 * @{
 */

/* Typedef for function pointer */
typedef void (*FUNC_PTR)(void *pArg);
typedef unsigned long _UL;

/**@}*/ //end of OS_Typedef

/*------------------------------ Externs -------------------------------------*/

/*---------------------------- Prototypes ------------------------------------*/

/*----------------------------Initialization ---------------------------------*/

/** @addtogroup OS_Prototypes OS_Prototypes
 * @{
 */

/* Function for OS initialization */
os_sts_e os_init(void);

/* Function for OS exit*/
os_sts_e os_exit(void);

/*------------------------base for register set ------------------------------*/
/* Function for getting the base address */
_addr os_getBase(void);

/*----------------------------delays -----------------------------------------*/
/* Function for delaying task in ms */
void os_delayMs(_ub32 uiMsec);

/* Function for delaying task in us */
void os_delayUs(_ub32 uiUsec);

/*------------------------------ timers --------------------------------------*/
/* Function for creating timer */
os_sts_e os_createTimer(
    os_timer_t **pTimer,
    FUNC_PTR pfnHandler,
    _ub32 uiMode);

/* Function for deleting timer */
os_sts_e os_deleteTimer(os_timer_t **pTimer);

/* Function for adding timer */
os_sts_e os_addTimer(os_timer_t *pTimer, _ub32 uiMsec);

/*------------------------------- memory -------------------------------------*/
/* Function for memory allocation */
os_sts_e os_allocMem(void **pAddr, _ub32 uiSize);

/* Function for memory deallocation */
void os_freeMem(void *pAddr);

/* Function for DMA memory allocation */
os_sts_e os_allocDmem(void **pAddr, _ub32 *puiDAdr, _ub32 uiSize);

/* Function for DMA memory de allocation */
os_sts_e os_freeDmem(void *pAddr, _ub32 uiDaddr, _ub32 uiSize);

/* Function for setting memory location */
os_sts_e os_setMem(void *pDest, _ub8 ucVal, _ub32 uiSize);

/* Function for mapping physical address */
os_sts_e os_mapPhyAddr(
    _ub32 *pPhyAddr,
    void *pVAddr,
    _ub32 uiSize,
    com_RWDir_e direction);

/* Function for unmapping physical address */
os_sts_e os_unmapPhyAddr(
    _ub32 PhyAddr,
    _ub32 uiSize,
    com_RWDir_e direction);
/*-----------------------------interrupts ------------------------------------*/
/* Function for getting the Irq number */
_ub32 os_getIRQ(void);

/* Function for registering Interrupts */
os_sts_e os_registerIntr(_ub32 uiIrq, IFPTR pfnHandler, void *pArg);

/* Function for de registering Interrupts */
void os_deregisterIntr(_ub32 uiIrq);

/*---------------------- critical section & atomicity ------------------------*/
/* Function for creating lock */
os_sts_e os_createLock(os_lock_t **pLock);

/* Function for deleting lock */
os_sts_e os_deleteLock(os_lock_t **pLock);

/*-------------------------register access------------------------------------*/
/* Function for 32 bit read register access */
_ub32 os_read32(_addr ulAddr);

/* Function for 16 bit read register access */
_ub16 os_read16(_addr ulAddr);

/* Function for 8bit read register access */
_ub8 os_read8(_addr ulAddr);

/* Function for 32 bit write register access */
void os_write32(_ub32 ulValue, _addr ulAddr);

/* Function for 16 bit write register access */
void os_write16(_ub16 usValue, _addr ulAddr);

/* Function for 8 bit write register access */
void os_write8(_ub8 ucValue, _addr ulAddr);

/* Function to initialize the completions */
void os_initWakeupSignal(COMPLETION *cmplt);

/* Function to wakeup the thread which is waiting on the completion structure */
void os_wakeup(COMPLETION *cmplt);

/* Function to wait for completion of specific task */
os_sts_e os_waitForSignal(COMPLETION *cmplt, _ub32 timeout);

/**@}*/ // OS_Prototypes

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _OS_H_ */

/**@}*//* OSServices */
/**@}*//* AbstractionLayer */

