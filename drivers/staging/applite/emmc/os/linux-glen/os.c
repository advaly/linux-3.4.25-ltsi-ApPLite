/**
 * @file          os.c
 *
 * \brief         Source file of OS Abstraction Layer.
 *
 * \b COPYRIGHT : TOSHIBA Corporation Semiconductor and Storage Company
 *                2010-2015 All rights reserved
 *
 * \b Project   : Glenfiddich
 *
 * \b Version   : 0.2
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
 * @addtogroup LinuxOSServices
 * @{
 */

/*------------------------ Header Files Inclusions ---------------------------*/
#include "os.h"         /* To use OS service APIs */
#include "cmd_api.h"    /* To use CMD layer APIs */
#include "hc_api.h"     /* To use HC layer APIs */
#include "debug.h"      /* To use the debug zone prints */

/*-------------------------- Macro Definitions -------------------------------*/

/** @addtogroup OS_DEFINES OS_DEFINES
 * @{
 */

/* OS Init entry check values.*/
#define _OS_INITIALIZE      1
#define _OS_UNINITIALIZE    0

/**@}*/ // OS_DEFINES

/*--------------------------- Enum Definitions -------------------------------*/

/*------------------- Data Structures & Custom Typedefs ----------------------*/

/** @addtogroup OS_Globals OS_Globals
 * @{
 */

/* Global Structure for managing locks */
static os_lock_t os_lk[_MAX_NUM_RES];

/* Global Structure for managing timers */
static os_timer_t os_tmr[_MAX_NUM_RES];

/**@}*/ // OS_Globals

/** @addtogroup OS_Prototypes OS_Prototypes
 * @{
 */

/*
 * Initialize the semaphore. This will be used for protecting
 * global structures like timers,locks etc.
 */
static INIT_SEM(os_sem);

/**@}*/ // OS_Prototypes

/** @addtogroup OS_Globals OS_Globals
 * @{
 */

/* Global variable to keep track of OS Initialization */
static _ub32 uiOsInitStatus = _OS_UNINITIALIZE;

/* Structure to hold the base address and interrupt number */
static os_resource_t os_resource;

/**@}*/ // OS_Globals

/** @addtogroup OS_Functions OS_Functions
 * @{
 */

/**
 * @brief OS initialization
 *
 * @param None
 *
 * @retval _OS_OK.Initialization successful.
 * @retval _OS_ERR_RESOURCE Error in resource allocation.
 */
os_sts_e os_init(void)
{
    _ub32 uiRet = _OS_OK;

    /* Check if OS abstraction layer is already initialized */
    if(_OS_INITIALIZE == uiOsInitStatus)
    {
        _OS_DBG_ERR("OS abstraction already init\n");
        return _OS_OK;
    }

    /* Obtain the base address and IRQ number here */
    uiRet = os_obtainResource(&os_resource);
    if(_OS_OK != uiRet)
    {
        _OS_DBG_ERR("get resource failed.\n");
        return _OS_ERR_RESOURCE;
    }

    /*
     * Set the Global variable so that initialization won't happen
     * until exit is done.
     */
    uiOsInitStatus = _OS_INITIALIZE;

    return _OS_OK;
}

/**
 * @brief OS deinitialization
 *
 * @param None
 *
 * @retval _OS_OK.Initialization successful.
 * @retval _OS_ERR_RESOURCE Error in resource de allocation.
 */
os_sts_e os_exit(void)
{
    _ub32 i= 0;
    /* Check if OS abstraction layer is already initialized */
    if(_OS_UNINITIALIZE == uiOsInitStatus)
    {
        _OS_DBG_ERR("OS abstraction not init\n");
        return _OS_ERR_RESOURCE;
    }
    /* Release the resources obtained during initiailzation */
    os_releaseResource(&os_resource);

    for(i = 0; i < _MAX_NUM_RES; i++)
    {
        /* Release all resources usage at OS exit */
        os_lk[i].uiLockAvailable = _NOT_IN_USE;
        os_tmr[i].uiTimerAvailable = _NOT_IN_USE;
    }

    /* Reset the global variable so that initialization can happen again */
    uiOsInitStatus = _OS_UNINITIALIZE;

    return _OS_OK;
}

/**
 * @brief  Get the device base address
 *
 * @param None.
 *
 * @retval Base address of the HC register set.
 */
_addr os_getBase(void)
{
    /* Return the base address of the register set */
    return os_resource.uiBase;
}

/**
 * @brief Read 32 bit value from address specified.
 *
 * @param[in] ulAddr The address from where data has to be read.
 *
 * @retval Data read.
 */
_ub32 os_read32(_addr ulAddr)
{
    return readl((const volatile void __iomem *)ulAddr);
}

/**
 * @brief Read 16 bit value from address specified.
 *
 * @param[in] ulAddr The address from where data has to be read.
 *
 * @retval Data read.
 */
_ub16 os_read16(_addr ulAddr)
{
#ifdef __32BIT
    _ub32 reg = 0;
    _ub16 value = 0;
    _ub32 aligned_addr = ((_ub32)ulAddr & 0xFFFFFFFC);

    reg = readl((const volatile void __iomem *)aligned_addr); /* read 32bit */

    if((_ub32)ulAddr & 0x00000003)
    {
        /* upper 16bits */
        value = (_ub16)(reg >> 16);
    }
    else
    {
        /* lower 16bits */
        value = (_ub16)(reg & 0x0000FFFF); /* clear upper 16bits */
    }

    return value;
#else /* !__32BIT */
    return readw(ulAddr);
#endif /* __32BIT */
}

/**
 * @brief Read 8 bit value from address specified.
 *
 * @param[in] ulAddr The address from where data has to be read.
 *
 * @retval Data read.
 */
_ub8 os_read8(_addr ulAddr)
{
#ifdef __32BIT
    _ub32 reg = 0;
    unsigned char value = 0;
    _ub32 aligned_addr = ((_ub32)ulAddr & 0xFFFFFFFC);
    _ub32 shift = ((_ub32)ulAddr & 0x00000003);

    shift = (shift * 8);
    reg = readl((const volatile void __iomem *)aligned_addr); /* read 32bit */
    reg = (reg >> shift);
    value = (unsigned char)(reg & 0x000000FF); /* BYTE_MASK = 0x000000FF */

    return value;
#else /* !__32BIT */
    return readb(ulAddr);
#endif /* __32BIT */
}

/**
 * @brief Write 32 bit value to address specified.
 *
 * @param[in] ulValue The value to be written to address.
 * @param[in] ulAddr The address to which data has to be written.
 *
 * @retval None.
 */
void os_write32(_ub32 ulValue, _addr ulAddr)
{
    writel(ulValue, (const volatile void __iomem *)ulAddr);
    return;
}

/**
 * @brief Write 16 bit value to address specified.
 *
 * @param[in] usValue The value to be written to address.
 * @param[in] ulAddr The address to which data has to be written.
 *
 * @retval None.
 */
void os_write16(_ub16 usValue, _addr ulAddr)
{
#ifdef __32BIT
    _ub32 reg = 0;
    _ub32 aligned_addr = ((_ub32)ulAddr & 0xFFFFFFFC);

    reg = readl((const volatile void __iomem *)aligned_addr); /* read 32bit */

    if((_ub32)ulAddr & 0x00000003)
    {
        /* upper 16bits */
        reg = (reg & 0x0000FFFF); /* clear upper 16bits */
        reg = (reg | (unsigned int)(usValue << 16));
    }
    else
    {
        /* lower 16bits */
        reg = (reg & 0xFFFF0000); /* clear lower 16bits */
        reg = (reg | (unsigned int)usValue);
    }

    writel(reg, (const volatile void __iomem *)aligned_addr); /* write 32bit */
#else /* !__32BIT */
    writew(usValue, ulAddr);
#endif /* __32BIT */
    return;
}

/**
 * @brief Write 8 bit value to address specified.
 *
 * @param[in] ucValue The value to be written to address.
 * @param[in] ulAddr The address to which data has to be written.
 *
 * @retval None.
 */
void os_write8(_ub8 ucValue, _addr ulAddr)
{
#ifdef __32BIT
    _ub32 reg = 0;
    _ub32 reg_temp = (_ub32)ucValue;
    _ub32 aligned_addr = ((_ub32)ulAddr & 0xFFFFFFFC);
    _ub32 shift = ((_ub32)ulAddr & 0x00000003);

    shift = (shift * 8);
    reg = readl((const volatile void __iomem *)aligned_addr); /* read 32bit */
    /* BYTE_MASK = 0x000000FF */
    reg = (reg & (~(0x000000FF << shift))); /* clear byte */
    reg = (reg | (reg_temp << shift));
    writel(reg, (const volatile void __iomem *)aligned_addr); /* write 32bit */
#else /* !__32BIT */
    writeb(ucValue, ulAddr);
#endif /* __32BIT */
    return;
}

/**
 * @brief Sets memory area pointed to by dest with the constant byte val.
 *
 * @param[in] pDest The pointer to address where data has to be written.
 * @param[in] ucVal The value to be written to address.
 * @param[in] uiSize Number of bytes to be written.
 *
 * @retval _OS_OK.Memset successful.
 * @retval _OS_ERR_PARAM Invalid parameters.
 */
os_sts_e os_setMem(void *pDest, _ub8 ucVal, _ub32 uiSize)
{
    /* Return here if memory address is NULL or size is zero */
    if((NULL == pDest) || (0 == uiSize))
    {
        _OS_DBG_ERR("Invalid param in set mem\n");
        return _OS_ERR_PARAM;
    }

    /*Set the memory location */
    memset(pDest, ucVal, uiSize);

    return _OS_OK;
}

/*------------------------------delays --------------------------------------*/
/**
 * @brief Delay a particular task for the amount of time in ms specified.
 *
 * @param[in] uiMsec The period for which task has to be delayed.
 *
 * @retval None.
 *
 * Important Note: This is blocking call and cannot be used in interrupt context
 */
void os_delayMs(_ub32 uiMsec)
{
    /*
     * Delay the task by the time specified and blocks the system
     *(or at least the active CPU) if running single-threaded.
     * This is not recommended to use in interrupt context.
     */
    mdelay(uiMsec);
    return;
}

/**
 * @brief Delay a particular task for the amount of time in us specified.
 *
 * @param[in] uiUsec The period for which task has to be delayed.
 *
 * @retval None.
 *
 * Important Note: This is blocking call and cannot be used in interrupt context
 */
void os_delayUs(_ub32 uiUsec)
{
    /*
     * Delay the task by the time specified and blocks the system
     *(or at least the active CPU) if running single-threaded.
     * This is not recommended to use in interrupt context.
     */
    udelay(uiUsec);
    return;
}

/*------------------------- critical section & atomicity ---------------------*/
/**
 * @brief Create the lock.
 *
 * @param[out] pLock The pointer to lock handle. Caller will get the address of
 * resource available in the passed handle.
 *
 * @retval _OS_OK creation of lock successful.
 * @retval _OS_ERR_CREATE_LOCK creation of lock unsuccessful.
 * @retval _OS_ERR_SEMAPHORE Error in semaphore
 */
os_sts_e os_createLock(os_lock_t **pLock)
{
    _ub32 i = 0;
    _ub32 uiLockFound = 0;
    _ub32 uiRet = 0;

    /* Take the semaphore as globals are being accessed */
    uiRet = TAKE_SEM(&os_sem);
    if(uiRet)
    {
        _OS_DBG_ERR("Error in taking semaphore\n");
        return _OS_ERR_SEMAPHORE;
    }

    /* Scan through the global resources to allocate a lock for the user */
    for(i = 0; i < _MAX_NUM_RES; i++)
    {
        /* Assign a resource to the caller */
        if(_NOT_IN_USE == os_lk[i].uiLockAvailable)
        {
            os_lk[i].uiLockAvailable = _IN_USE;
            *pLock = &os_lk[i];
            uiLockFound = 1;
            break;
        }
    }

    /* Lock not found. Now what?? Return error.*/
    if(0 == uiLockFound)
    {
        _OS_DBG_ERR("Lock not found\n");
        REL_SEM(&os_sem);
        return _OS_ERR_CREATE_LOCK;
    }

    /* Initialize the lock before caller uses */
    spin_lock_init(&(os_lk[i].spin));

    /* Release the semaphore after accessing globals */
    REL_SEM(&os_sem);
    return _OS_OK;
}

/**
 * @brief Delete the lock.
 *
 * @param[in] pLock  The pointer to lock handle.
 *
 * @retval _OS_OK deletion of lock successful.
 * @retval _OS_ERR_DELETE_LOCK deletion of lock unsuccessful.
 * @retval _OS_ERR_SEMAPHORE Error in Semaphore.
 */
os_sts_e os_deleteLock(os_lock_t **pLock)
{
    _ub32 i = 0;
    _ub32 uiLockFound = 0;
    _ub32 uiRet = 0;

    /* Return here if handle is NULL */
    if(NULL == pLock)
    {
        _OS_DBG_ERR("Invalid param in deleting lock\n");
        return _OS_ERR_PARAM;
    }

    /* Take the semaphore as globals are being accessed */
    uiRet = TAKE_SEM(&os_sem);
    if(uiRet)
    {
        _OS_DBG_ERR("Error in taking semaphore\n");
        return _OS_ERR_SEMAPHORE;
    }

    /* Scan through the global resources to deallocate the lock for the user */
    for(i = 0; i < _MAX_NUM_RES; i++)
    {
        /* Delete the usage of the resource so that caller can use again */
        if(*pLock == &os_lk[i])
        {
            os_lk[i].uiLockAvailable = _NOT_IN_USE;
            uiLockFound = 1;
            break;
        }
    }

    /* Lock not found. Now what?? Return error */
    if(0 == uiLockFound)
    {
         _OS_DBG_ERR("Lock not found");
         REL_SEM(&os_sem);
         return _OS_ERR_DELETE_LOCK;
    }

    /* Release the semaphore after accessing globals */
    REL_SEM(&os_sem);
    return _OS_OK;
}

/*-----------------------------interrupts ----------------------------------*/
/**
 * @brief Get the IRQ number.
 *
 * @param None.
 *
 * @retval The IRQ number assigned by the OS.
 */
_ub32 os_getIRQ(void)
{
    /* Return the IRQ number to the caller */
    return os_resource.uiIrq;
}

/**
 * @brief Register an interrupt for the device.
 *
 * @param[in] uiIrq The irq number to be assigned.
 * @param[in] pfnHandler The function handler for the interrupt raised.
 * @param[in] pArg The argument for the handler.
 *
 * @retval _OS_OK registration is successful.
 * @retval _OS_ERR_INTR_REG registration is not successful.
 * @retval _OS_ERR_PARAM Error in params.
 */
os_sts_e os_registerIntr(_ub32 uiIrq, IFPTR pfnHandler, void *pArg)
{
    _ub32 uiret = 0;

    /*
     * Check if OS abstraction layer is already initialized  If not
     * interrupt should not be registered.
     */
    if(_OS_UNINITIALIZE== uiOsInitStatus)
    {
        _OS_DBG_ERR("OS abstraction not initialized.Don't register intr\n");
        return _OS_ERR_INTR_REG;
    }

    /* If the function handler is Null. Return error */
    if(NULL == pfnHandler)
    {
        _OS_DBG_ERR("Error in params os_registerIntr\n");
        return _OS_ERR_PARAM;
    }

    /*
     * Argument for the function handler has to be non NULL.
     * This is kept as this is linux specific. Have to revisit in
     * future for other OS.
     */
    if(NULL == pArg)
    {
        pArg = (void *)1;
    }

    /*
     * Request the IRQ number from the OS The interrupt line is made shared
     * considering other tasks in the system.
     */
    uiret = request_irq(uiIrq,
        (irq_handler_t)pfnHandler,
        IRQF_SHARED,
        "eMMC Interrupt",
        (void *)pArg);

    /* Request for IRQ rejected */
    if(uiret)
    {
        _OS_DBG_ERR("Interrupt registration failed\n");
        return _OS_ERR_INTR_REG;
    }

    return _OS_OK;
}

/**
 * @brief Free a registered interrupt for the device.
 *
 * @param[in] uiIrq The irq number to be assigned.
 *
 * @retval None.
 */
void os_deregisterIntr(_ub32 uiIrq)
{
    /*
     * Free the requested IRQ number so that OS can allocate for other tasks
     * Second argument is dummy and required only for Linux specific
     * implementation. Have to revisit this.
     */
    free_irq(uiIrq, (void *)1);
    return;
}

/*------------------------------ timers -----------------------------------*/
/**
 * @brief Create the timer.
 *
 * @param[out] pTimer The pointer to timer handle.
 * @param[in] pfnHandler The function handler to be called when timer expires.
 * @param[in] uiMode The mode of the timer.
 *
 * @retval _OS_OK timer creation is successful.
 * @retval _OS_ERR_CREATE_TIMER timer creation is not successful.
 * @retval _OS_ERR_PARAM Error in params.
 * @retval _OS_ERR_SEMAPHORE Error in Semaphore.
 */
os_sts_e os_createTimer(
    os_timer_t **pTimer,
    FUNC_PTR pfnHandler,
    _ub32 uiMode)
{
    _ub32 i = 0;
    _ub32 uiRet, uiTimerFound = 0;

    /* If the function handler is Null. Return error */
    if(NULL == pfnHandler)
    {
        _OS_DBG_ERR("Error in param\n");
        return _OS_ERR_PARAM;
    }

    /* Take the semaphore as globals are being accessed */
    uiRet = TAKE_SEM(&os_sem);
    if(uiRet)
    {
        _OS_DBG_ERR("Error in taking semaphore\n");
        return _OS_ERR_SEMAPHORE;
    }

    /* Scan through the global resources to allocate a timer for the user */
    for(i = 0; i < _MAX_NUM_RES; i++)
    {
         /* Assign a resource to the caller if not in use */
         if(_NOT_IN_USE == os_tmr[i].uiTimerAvailable)
        {
            os_tmr[i].uiTimerAvailable = _IN_USE;
            *pTimer = &os_tmr[i];
            uiTimerFound=1;
            break;
        }
    }
    _OS_DBG_INFO("Initialize the timer\n");

    /* Timer not found.Now what?? Return error */
    if(0 == uiTimerFound)
    {
        _OS_DBG_ERR("Timer not found");
        REL_SEM(&os_sem);
        return _OS_ERR_CREATE_TIMER;
    }

    /* Initialize the timer before caller uses */
    init_timer(&os_tmr[i].tlist);

    /* Initialize the timer list variables and assign the expiry time */
    os_tmr[i].tlist.data = 0;
    os_tmr[i].tlist.function = (void (*)(_UL))pfnHandler;

    /* Release the semaphore so that globals can be accessed */
    REL_SEM(&os_sem);

    return _OS_OK;
}

/**
 * @brief Add the timer.
 *
 * @param[in] pTimer The pointer to timer handle.
 * @param[in] uiMsec  The period for which timer has to be run.
 *
 * @retval _OS_OK timer deletion is successful.
 * @retval _OS_ERR_PARAM Error in params.
 * @retval _OS_ERR_MOD_TIMER Error in adding timer.
 * @retval _OS_ERR_SEMAPHORE Error in taking semaphore.
 */
os_sts_e os_addTimer(os_timer_t *pTimer, _ub32 uiMsec)
{
    _ub32 i = 0;
    /* If the timer handle is Null. Return error */
    if(NULL == pTimer)
    {
        _OS_DBG_ERR( "Error in params\n");
        return _OS_ERR_PARAM;
    }

    os_tmr[i].tlist.expires = CUR_TIME + uiMsec;

    /* Add the timer to the global list */
    add_timer(&(pTimer->tlist));

    return _OS_OK;
}

/**
 * @brief Delete the timer.
 *
 * @param[in] pTimer The pointer to timer handle.
 *
 * @retval _OS_OK timer deletion is successful.
 * @retval _OS_ERR_DELETE_TIMER timer deletion is not successful.
 * @retval _OS_ERR_SEMAPHORE Error in Semaphore.
 */
os_sts_e os_deleteTimer(os_timer_t **pTimer)
{
    _ub32 i = 0;
    _ub32 uiTimerFound,uiRet = 0;

    /* If the timer handle is Null. Return error */
    if(NULL == pTimer)
    {
        _OS_DBG_ERR( "Error in params\n");
        return _OS_ERR_PARAM;
    }

    /* Take semaphore for accessing global resources */
    uiRet = TAKE_SEM(&os_sem);
    if(uiRet)
    {
        _OS_DBG_ERR( "Error in taking semaphore\n");
        return _OS_ERR_SEMAPHORE;
    }

    /* Scan through the global resources to deallocate the timer for the user */
    for(i = 0; i < _MAX_NUM_RES; i++)
    {
        /* Reassign the resource so that caller can use in future */
        if(*pTimer == &os_tmr[i])
        {
            os_tmr[i].uiTimerAvailable  = _NOT_IN_USE;
            uiTimerFound = 1;
            break;
        }
    }

    /* Timer not found. Now what?? Return error */
    if(0 == uiTimerFound)
    {
         _OS_DBG_ERR( "Timer not found");
         REL_SEM(&os_sem);
         return _OS_ERR_DELETE_TIMER;
    }

    /* Delete the timer so that kernel can use it for further use */
    if (timer_pending(&os_tmr[i].tlist))
    {
        _OS_DBG_ERR( "Timer is still pending to run\n");
    }
    del_timer(&os_tmr[i].tlist);

    /* Release the semaphore for accessing the globals */
    REL_SEM(&os_sem);
    return _OS_OK;
}

/*------------------------------- memory ----------------------------------*/
/**
 * @brief Allocate the memory.
 *
 * @param[out] pAddr The pointer to pointer of the virtual address
 * allocated.
 * @param[in]  uiSize The size of the data to allocate.
 *
 * @retval _OS_OK allocation of memory successful.
 * @retval _OS_MEM_ALLOC_FAIL allocation of memory is not successful.
 * @retval _OS_ERR_PARAM Error in params
 */
os_sts_e os_allocMem(void **pAddr, _ub32 uiSize)
{
    /* Size validation  User shouldn't pass 0 and Address shouldn't be NULL */
    if(0 == uiSize)
    {
        _OS_DBG_ERR( "Error in params\n");
        return _OS_ERR_PARAM;
    }

    /*
     * Allocate memory using kzalloc. Be aware, kernel cannot guaranteed huge
     * contiguous chunks of memory with this. This will return virtual address.
     * It's much rare for an allocation with GFP_KERNEL to fail. This
     * shouldn't be used in interrupt contexts as there is a possibility of
     * sleep while kernel is trying hard to find memory.
     */
    *pAddr = kzalloc(uiSize, GFP_KERNEL);

    /* Allocation failed.*/
    if(NULL == *pAddr)
    {
        _OS_DBG_ERR( "Memory allocation fail\n");
        return _OS_ERR_MEM_ALLOC_FAIL;
    }
    return _OS_OK;
}

/**
 * @brief Free the memory.
 *
 * @param[in] pAddr The pointer to memory allocation to be freed.
 *
 * @retval None.
 */
void os_freeMem(void *pAddr)
{
    /* Free the allocated memory using kzalloc */
     kfree(pAddr);
     return;
}

/**
 * @brief Allocate DMA memory. Note the user has to pass address in 2nd param.
 *
 * @param[out] pAddr The pointer to pointer of virtual address allocated.
 * @param[out] puiDAdr The DMA address to be allocated.
 * @param[in] uiSize The amount of data to be allocated.
 *
 * @retval _OS_OK allocation of DMA memory successful.
 * @retval _OS_DMEM_ALLOC_FAIL allocation of DMA memory is not successful.
 * @retval _OS_ERR_PARAM Error in params
 */
os_sts_e os_allocDmem(void **pAddr, _ub32 *puiDAdr, _ub32 uiSize)
{
    /* Parameter checking */
    if(0 == uiSize)
    {
        _OS_DBG_ERR( "Error in params\n");
        return _OS_ERR_PARAM;
    }

    /*
     * Allocate consistent memory. Be aware that kernel cannot guaranteed huge
     * contiguous chunks of memory with this. This will return virtual address.
     * and physical address.
     */
    *pAddr = pci_alloc_consistent(NULL, uiSize, (dma_addr_t *)puiDAdr);
    if(NULL == *pAddr)
    {
        _OS_DBG_ERR( "pci_alloc_consistent failed\n");
        return _OS_ERR_DMEM_ALLOC_FAIL;
    }

    return _OS_OK;
}

/**
 * @brief De-allocate DMA memory.
 *
 * @param[in] pAddr The pointer to virtual address to be freed.
 * @param[in] uiDAdr The DMA address to be deallocated.
 * @param[in] uiSize The amount of data to be deallocated.
 *
 * @retval _OS_OK allocation of DMA memory successful.
 * @retval _OS_ERR_PARAM Error in params.
 */
os_sts_e os_freeDmem(void *pAddr, _ub32 uiDAdr, _ub32 uiSize)
{
    /* Address/ Size is null so return error */
    if((NULL == pAddr) || (0 == uiDAdr) || (0 == uiSize))
    {
        _OS_DBG_ERR( "Error in params os_freeDmem\n");
        return _OS_ERR_PARAM;
    }

    /* Deallocate the memory  No return value for this */
    pci_free_consistent(NULL, uiSize, pAddr, (dma_addr_t)uiDAdr);

    return _OS_OK;
}

/**
 * @brief Map physical address.
 *
 * @param[out] pPhyAddr The pointer to mapped physical address.
 * @param[in] pVAddr The pointer to virtual address
 * @param[in] uiSize The size of memory to be mapped.
 * @param[in] direction The direction for RW.
 *
 * @retval _OS_OK Mapping successful.
 * @retval _OS_ERR_MAP Error in mapping memory.
 */
os_sts_e os_mapPhyAddr(
    _ub32 *pPhyAddr,
    void *pVAddr,
    _ub32 uiSize,
    com_RWDir_e direction)
{
    enum dma_data_direction dir;
    if(NULL == pVAddr)
    {
        _OS_DBG_ERR("Null addresses passed\n");
        return _OS_ERR_MAP;
    }
    /*
     * This functions maps a single memory region and gives corresponding
     * physical address. Currently device address is not used and passed as NULL
     * This function has to be used with unmap Physical address.
     */
    dir = ((_COM_DIR_R == direction)? DMA_FROM_DEVICE : DMA_TO_DEVICE);
    *pPhyAddr = (_ub32)dma_map_single(NULL, pVAddr, uiSize, dir);

    /* Mapping fails. Return error */
    if(0 == *pPhyAddr)
    {
        _OS_DBG_ERR("Error in mapping\n");
        return _OS_ERR_MAP;
    }

    return _OS_OK;
}

/**
 * @brief Unmap physical address.
 *
 * @param[in] pPhyAddr The pointer to physical address.
 * @param[in] uiSize The size of memory to be mapped.
 * @param[in] direction The direction for RW.
 *
 * @retval _OS_OK Mapping successful.
 * @retval _OS_ERR_MAP Error in unmapping memory.
 */
os_sts_e os_unmapPhyAddr(
    _ub32 PhyAddr,
    _ub32 uiSize,
    com_RWDir_e direction)
{
    enum dma_data_direction dir;

    /* Address/ Size is null so return error */
    if((0 == PhyAddr) || (0 == uiSize))
    {
        _OS_DBG_ERR( "Error in params os_unmapPhyAddr\n");
        return _OS_ERR_MAP;
    }

    /*
     * This functions unmaps a single memory region
     * Currently device address is not used and passed as NULL
     */
    dir = ((_COM_DIR_R == direction)? DMA_FROM_DEVICE : DMA_TO_DEVICE);
    dma_unmap_single(NULL, (dma_addr_t)PhyAddr, uiSize, dir);

    return _OS_OK;
}

/**
 * @brief Initialize the completion structure.
 *
 * @param[in] cmplt Completion structure to be initialized.
 *
 * @retval None.
 */
void os_initWakeupSignal(COMPLETION *cmplt)
{

    init_completion(cmplt);

    return;
}

/**
 * @brief Wakeup the thread waiting on this completion structure.
 *
 * @param[in] cmplt Completion structure on which the thread is waiting.
 *
 * @retval None.
 */
void os_wakeup(COMPLETION *cmplt)
{

    complete(cmplt);

    return;
}

/**
 * @brief Waits for the completion of the specific task to be signalled or for
 * specified timeout to expire.
 *
 * @param[in] cmplt Completion structure on which the thread should wait.
 * @param[in] timeout Timeout value in Jiffies
 *
 * @retval _OS_OK Wait for signal is successful and no timeout occurred.
 * @retval _OS_ERR_WAIT_TIMEOUT Timeout occurred while waiting for completion
 *
 * Important Note: This function is interruptible.
 */
os_sts_e os_waitForSignal(COMPLETION *cmplt, _ub32 timeout)
{
    _b32 ret = 0;

    ret = wait_for_completion_interruptible_timeout(cmplt, timeout);
    if(ret <= 0) /* Timeout occured */
    {
        return _OS_ERR_WAIT_TIMEOUT;
    }

    return _OS_OK;
}

/**@}*/ // OS_Functions

/**@}*//* LinuxOSServices */
/**@}*//* AbstractionLayer */

