/**
 * @file          intr.c
 *
 * \brief         Source file of Interrupt Layer.
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
 * @addtogroup InterruptController
 * @{
 */

/**
 * @addtogroup Handlers
 * @{
 */

/*--------------------------- Headers ----------------------------------------*/
#include "intr.h"         /* Interrupt related functions */
#include "cmd_api.h"      /* To use CMD layer APIs */
#include "ra.h"           /* To use register access APIs */
#include "os.h"           /* To use OS service APIs */
#include "debug.h"        /* To use the debug zone prints */
#include "config.h"       /* To use configuration params */
#include "hc_api.h"       /* To use HC APIs to access registers */

/*--------------------------- Macro Definitions ------------------------------*/

/** @addtogroup Intr_DEFINES Intr_DEFINES
 * @{
 */

/* Macros for debugging */
#ifdef __DEBUG
#define _INTR_DBG_INFO(__format__, arg...)    \
       dz_print(_DZ_INTR, " INTR: %s::" __format__,__FUNCTION__,## arg )
#define _INTR_DBG_ERR(__format__, arg...)    \
       dz_print(_DZ_CRTICAL, " INTR: %s::" __format__,__FUNCTION__,## arg )
#else
#define _INTR_DBG_INFO(__format__, arg...)    /*  */
#define _INTR_DBG_ERR(__format__, arg...)    /*  */
#endif

/* Normal Interrupt IRQ */
#define _ERROR_INTERRUPT_IRQ          0x8000
#define _RETUNING_EVENT_IRQ           0x1000
#define _INTC_IRQ                     0x0800
#define _INTB_IRQ                     0x0400
#define _INTA_IRQ                     0x0200
#define _CARD_INTERRUPT_IRQ           0x0100
#define _CARD_REMOVAL_IRQ             0x0080
#define _CARD_INSERTION_IRQ           0x0040
#define _BLOCK_GAP_EVENT_IRQ          0x0004

#define _BUFFER_READ_READY_IRQ        0x0020
#define _BUFFER_WRITE_READY_IRQ       0x0010
#define _DMA_INTERRUPT_IRQ            0x0008
#define _TRANSFER_COMPLETE_IRQ        0x0002
#define _COMMAND_COMPLETE_IRQ         0x0001

/* Macro for grouping general normal interrupts */
#define _NORM_INTR_LVL                0x9fc4

/* Error Interrupt IRQ */
/* Level 4 Interrupts */
#define _VENDOR_SPECIFIC_STS_ERR_IRQ     0xf000
#define _TUNING_ERR_IRQ                  0x0400
#define _AUTOCMD12_ERR_IRQ               0x0100
#define _CURRENT_LIMIT_ERR_IRQ           0x0080

/* Level 3 Interrupts */
#define _ADMA_ERR_IRQ                    0x0200

/* Level 2 Interrupts */
#define _DATA_ENDBIT_ERR_IRQ             0x0040
#define _DATA_CRC_ERR_IRQ                0x0020
#define _DATA_TIMEOUT_ERR_IRQ            0x0010

/* Level 1 Interrupts */
#define _COMMAND_INDEX_ERR_IRQ           0x0008
#define _COMMAND_ENDBIT_ERR_IRQ          0x0004
#define _COMMAND_CRC_ERR_IRQ             0x0002
#define _COMMAND_TIMEOUT_ERR_IRQ         0x0001

/* Macros for grouping error interrupts */
#define _ERR_INTR_LVL1      (_COMMAND_INDEX_ERR_IRQ | \
                             _COMMAND_ENDBIT_ERR_IRQ | \
                             _COMMAND_CRC_ERR_IRQ| \
                             _COMMAND_TIMEOUT_ERR_IRQ)/* All cmd related errs */
#define _ERR_INTR_LVL2      (_DATA_ENDBIT_ERR_IRQ | \
                             _DATA_CRC_ERR_IRQ | \
                             _DATA_TIMEOUT_ERR_IRQ)/* All Data related errs */
#define _ERR_INTR_LVL3       _ADMA_ERR_IRQ        /* ADMA related errors */
#define _ERR_INTR_LVL4      (_VENDOR_SPECIFIC_STS_ERR_IRQ | \
                             _TUNING_ERR_IRQ | \
                             _AUTOCMD12_ERR_IRQ | \
                             _CURRENT_LIMIT_ERR_IRQ)/* All other error intrs */

/* Maximum number of times Handler has to service the pending interrupts */
#define _MAX_INTR_COUNT    2

/* Macro for faux interrupts */
#define _NO_INTERRUPT 0

/**@}*/ // Intr_DEFINES

/*-------------------------- Prototypes --------------------------------------*/

/** @addtogroup Intr_Prototypes Intr_Prototypes
 * @{
 */

/* Function for default interrupt handler */
void intr_genericHdlr(void *pArg);

/**@}*/ // Intr_Prototypes

/*--------------------------- Globals ----------------------------------------*/

/** @addtogroup Intr_Globals Intr_Globals
 * @{
 */

/* Global structure for interrupt handler on all slots */
static intr_cb_t intr_hdlr[_MAX_SLOTS][_MAX_NUM_EVENTS];;

#ifdef __POLL_ENABLE
/* Timer for polling events */
static os_timer_t *intr_pTimer;

/* Poll time for the events */
static _ub32 intr_uiTime;
#endif /* __POLL_ENABLE */

/* Lock for protecting interrupt handler */
static os_lock_t *intr_pLock;

/**@}*/ // Intr_Globals
/*----------------------- Function definition --------------------------------*/

/** @addtogroup Intr_Functions Intr_Functions
 * @{
 */

#ifdef __POLL_ENABLE /* For enabling polling mode */
/**
 * @brief Actual Polling function which calls interrupt handler
 *
 * @param[in] pArg The function argument for poll handler.
 *
 * @retval None.
 */
void intr_pollHdlr(void *pArg)
{
     /*
      * Call Interrupt handler function here Irq number and argument is passed
      * as 0 as it is not used.
      */
    intr_irqHandler(0, NULL);

    /* Modify the timer for next event */
    os_addTimer(intr_pTimer, (_b32)(intr_uiTime));
    return;
}
/**
 * @brief Init function for polling events.
 *
 * @param[in] uiPollTime The poll time of the event.
 *
 * @retval _INTR_OK Initialization is successful.
 * @retval _INTR_ERR_POLL Initialization  is not successful.
 */
intr_sts_e intr_pollEvtInit(_ub32 uiPollTime)
{
    os_sts_e eOSSts = _OS_OK;

    /* Update the poll time in data base */
    intr_uiTime = uiPollTime;
    /* Create the timer with polltime */
    eOSSts = os_createTimer(&intr_pTimer, &intr_pollHdlr, 0);
    if(_OS_OK != eOSSts)
    {
        _INTR_DBG_ERR("Error in Polling init\n");
        return _INTR_ERR_POLL;
    }

    /* Start the timer here */
    os_addTimer(intr_pTimer, uiPollTime);
    return _INTR_OK;

}

/**
 * @brief Exit function for polling events.
 *
 * @param None.
 *
 * @retval _INTR_OK deregistration is successful.
 * @retval _INTR_ERR_POLL Deregistration is not successful.
 */
intr_sts_e intr_pollEvtExit(void)
{
    _ub32 uiRet = 0;
    /* Delete the timer */
    uiRet = os_deleteTimer(&intr_pTimer);
    if(uiRet != _OS_OK)
    {
       _INTR_DBG_ERR("Error in Polling exit\n");
       return _INTR_ERR_POLL;
    }
    return _INTR_OK;

}
#endif /* __POLL_ENABLE */

/**
 * @brief Interrupt handler initialization
 *
 * @param None.
 *
 * @retval _INTR_OK Initialization is successful.
 * @retval _INTR_ERR_INIT Initialization is not successful.
 */
intr_sts_e intr_init(void)
{
    _ub32 i = 0;
    _ub32 j = 0;
    _ub32 uiRet = 0;

    /*
     * Register Default handler for all interrupts and all slots
     * Must be called during initialization so that default handler is
     * assigned.
     */
    for(i = 0; i < _MAX_SLOTS;i++)
    {
        for(j=0; j < _MAX_NUM_EVENTS;j++)
        {
            uiRet = intr_deregisterHdlr(j, i);
            if(_INTR_OK != uiRet)
            {
                _INTR_DBG_ERR("Interrupt initialization problem\n");
                return _INTR_ERR_INIT;
            }
        }
    }

    /* Create the lock for interrupt handler */
    uiRet = os_createLock(&intr_pLock);
    if(_OS_OK != uiRet)
    {
        _INTR_DBG_ERR("Lock creation failed\n");
        return _INTR_ERR_INIT;
    }

    return _INTR_OK;
}

/**
 * @brief Interrupt handler initialization
 *
 * @param None.
 *
 * @retval _INTR_OK Exit is successful.
 * @retval _INTR_ERR_EXIT Exit is not successful.
 */
intr_sts_e intr_exit(void)
{
    _ub32 uiRet = 0;

    /* Delete the lock */
    uiRet = os_deleteLock(&intr_pLock);
    if(_OS_OK != uiRet)
    {
        _INTR_DBG_ERR("Lock creation failed\n");
        return _INTR_ERR_EXIT;
    }

    return _INTR_OK;
}
/**
 * @brief Register handler for the interrupt
 *
 * @param[in] event The bit number for the handler.
 * @param[in] pfnHandler The handler function to be called.
 * @param[in] pArg The arguments for the handler function.
 * @param[in] uiSlot The slot number of device.
 *
 * @retval _INTR_OK registration is successful.
 * @retval _INTR_INVALID_PARAM registration is not successful.
 */
intr_sts_e intr_registerHdlr(
    events_e event,
    FUNC_PTR pfnHandler,
    void *pArg,
   _ub32 uiSlot)
{
    _INTR_DBG_INFO("event is %d\n", event);
    _INTR_DBG_INFO("uiSlotNum is %d\n", uiSlot);
    _INTR_DBG_INFO("pfnHandler is %p\n", pfnHandler);

    /* Return here if the boundary conditions are not satisfied */
    if((event >= _MAX_NUM_EVENTS) || (uiSlot > _MAX_SLOTS)
        || (NULL == pfnHandler))
    {
        _INTR_DBG_ERR("Invalid param call back function\n");
        return _INTR_INVALID_PARAM;
    }

    /* Update the handler information to global structure */
    intr_hdlr[uiSlot][event].cb = pfnHandler;
    intr_hdlr[uiSlot][event].pData = pArg;

    return _INTR_OK;

}

/**
 * @brief Unregister handler for the interrupt
 *
 * @param[in] event  The bit number for the handler.
 * @param[in] uiSlot The slot number of the device.
 *
 * @retval _INTR_OK deregistration is successful.
 * @retval _INTR_INVALID_PARAM Deregistration is not successful.
 */
intr_sts_e intr_deregisterHdlr(events_e event,_ub32 uiSlot)
{
    /* Return here if the boundary conditions are not satisfied */
    if((event >= _MAX_NUM_EVENTS) || (uiSlot > _MAX_SLOTS) )
    {
        _INTR_DBG_ERR("Invalid param call back function\n");
        return _INTR_INVALID_PARAM;
    }

    /* Update default handler to global structure */
    intr_hdlr[uiSlot][event].cb = intr_genericHdlr;
    intr_hdlr[uiSlot][event].pData = NULL;
    return _INTR_OK;
}

/**
 * @brief Interrupt handler to take appropriate action when interrupt raises.
 *
 * @param[in] iIrq The Irq number.
 * @param[in] pArg The function argument for general handler.
 *
 * retval IRQ_HANDLED IRQ is serviced properly.
 * retval IRQ_NONE IRQ is not installed.
 */
IRQRET intr_irqHandler (_b32 iIrq, void *pArg)
{
    /* Variables to capture register status */
    volatile _ub16 usNormIntSts = 0;
    volatile _ub16 usErrIntSts = 0;
    volatile _ub16 usSlotIntSts = 0;

    /* Counter to keep track of fair usage of interrupt handler */
    volatile static _ub32 uiIntrCnt = 0;

    /* Local variables */
    _ub32 uiSlot = 0;
    _ub32 uiEvent = 0;
    _UL ulFlags = 0;
    intr_cb_t *pIntr = NULL;

    /* Initialize the slot interrupt status */
    usSlotIntSts = hc_getSlotIntrSts(uiSlot);
    /* Take the lock so that interrupt handler is protected */
    SPIN_IRQ_SAVE(&(intr_pLock->spin), ulFlags);

    /* Pointer to the call back function which user registers */
    pIntr = &intr_hdlr[uiSlot][uiEvent];

    /* Read the slot interrupt status and return if no interrupt is raised */
    if(0 == usSlotIntSts)
    {
        /* Release the spin lock and return */
        SPIN_IRQ_RESTORE(&(intr_pLock->spin), ulFlags);
        return IRQ_NONE;
    }

    /*
     * Scan through all the slots and service them one after another starting
     * from slot 0 to max slots.
     */
    for(uiSlot = 0; uiSlot < _MAX_SLOTS; uiSlot++)
    {
        /* Initialize the interrupt count for each slot */
        uiIntrCnt = 0;

        if((usSlotIntSts >> uiSlot ) & 0x1)
        {
            do
            {
                /*
                 * Increment the interrupt count to know how many interrupts
                 * are serviced in this call.
                 */
                uiIntrCnt++;
                /*
                 * Read Normal Interrupt status register and check for
                 * error interrupt status.
                 */
                usNormIntSts = hc_getIntrSts(uiSlot);
                /*
                 * Check Error Interrupt status in Normal Inr sts register and
                 * then handle error interrupts.
                 */
                if(usNormIntSts & _ERROR_INTERRUPT_IRQ)
                {
                    /*
                     * Read Error Interrupt status register and service the
                     * interrupts only if enabled by user.
                     */
                    _INTR_DBG_ERR("Error Interrupt occurred\n");
                    usErrIntSts = (hc_getErrIntrSts(uiSlot) &
                                   hc_getErrIntrMask(uiSlot));

                    /*
                     * All command related errors are grouped in to this level
                     * The handler of this function has to clear the status
                     * bits.
                     */
                    if(usErrIntSts & _ERR_INTR_LVL1)
                    {
                        _INTR_DBG_ERR("Command related errors\n");
                        hc_clrErrIntrSts(uiSlot,(usErrIntSts & _ERR_INTR_LVL1));
                        pIntr = &intr_hdlr[uiSlot][_ERR_INTR_CMD];
                        /* Call the handler */
                        (pIntr->cb)(pIntr->pData);
                    }

                    /*
                     * All Data related errors are grouped in to this level
                     * The handler of this function has to clear the status
                     * bits.
                     */
                    if(usErrIntSts & _ERR_INTR_LVL2)
                    {
                        _INTR_DBG_ERR("Data related errors %x\n",usErrIntSts);
                        hc_clrErrIntrSts(uiSlot,(usErrIntSts & _ERR_INTR_LVL2));
                        pIntr = &intr_hdlr[uiSlot][_ERR_INTR_DATA];
                        /* Call the handler */
                        (pIntr->cb)(pIntr->pData);
                    }

                    /* ADMA related errors */
                    if(usErrIntSts & _ERR_INTR_LVL3)
                    {
                        _INTR_DBG_ERR("ADMA related err\n");
                       hc_clrErrIntrSts(uiSlot, (usErrIntSts & _ERR_INTR_LVL3));
                        pIntr = &intr_hdlr[uiSlot][_ERR_INTR_ADMA];
                        /* Call the handler */
                        (pIntr->cb)(pIntr->pData);
                    }

                    /* Other Generic error interrupts */
                    if(usErrIntSts & _ERR_INTR_LVL4)
                    {
                        _INTR_DBG_ERR("Generic Error\n");
                       hc_clrErrIntrSts(uiSlot, (usErrIntSts & _ERR_INTR_LVL4));
                        pIntr = &intr_hdlr[uiSlot][_ERR_INTR_OTHERS];
                        /* Call the handler */
                        (pIntr->cb)(pIntr->pData);
                    }
                    /* Clear the status of error interrupt */
                    hc_clrNormIntrSts(uiSlot, _ERROR_INTERRUPT_IRQ);
                }
                /*
                 * Read Normal Interrupt status register and service the
                 * interrupts only if enabled by user.
                 */
                usNormIntSts &= hc_getIntrMask(uiSlot);
                if(usNormIntSts)
                {
                     /* command complete interrupt */
                    if(usNormIntSts & _COMMAND_COMPLETE_IRQ)
                    {
                        /*
                         * Command complete interrupt is handled using polling.
                         * No need to service here.
                         */
                        hc_clrNormIntrSts(uiSlot, _COMMAND_COMPLETE_IRQ);
                        /* Get the call back function for the event */
                        pIntr = &intr_hdlr[uiSlot][_NORM_INTR_CMD_COMP];
                        /* Call the handler */
                        (pIntr->cb)(pIntr->pData);
                    }
                    /* DMA interrupt */
                    if(usNormIntSts & _DMA_INTERRUPT_IRQ)
                    {
                        hc_clrNormIntrSts(uiSlot, _DMA_INTERRUPT_IRQ);
                        /* Get the call back function for the event */
                        pIntr = &intr_hdlr[uiSlot][_NORM_INTR_DMA];
                        /* Call the handler */
                        (pIntr->cb)(pIntr->pData);
                    }
                    /* Buffer Write Ready Interrupt */
                    else if(usNormIntSts & _BUFFER_WRITE_READY_IRQ)
                    {
                        hc_clrNormIntrSts(uiSlot, _BUFFER_WRITE_READY_IRQ);
                        /* Get the call back function for the event */
                        pIntr = &intr_hdlr[uiSlot][_NORM_INTR_WR_PIO];
                        /* Call the handler */
                        (pIntr->cb)(pIntr->pData);
                    }
                    /* Buffer Read Ready Interrupt */
                    else if(usNormIntSts & _BUFFER_READ_READY_IRQ)
                    {
                        hc_clrNormIntrSts(uiSlot, _BUFFER_READ_READY_IRQ);
                        /* Get the call back function for the event */
                        pIntr = &intr_hdlr[uiSlot][_NORM_INTR_RD_PIO];
                        /* Call the handler */
                        (pIntr->cb)(pIntr->pData);
                    }

                    /* Transfer complete interrupt */
                    if(usNormIntSts & _TRANSFER_COMPLETE_IRQ)
                    {
                        hc_clrNormIntrSts(uiSlot, _TRANSFER_COMPLETE_IRQ);
                        /* Get the call back function for the event */
                        pIntr = &intr_hdlr[uiSlot][_NORM_INTR_TX_COMP];
                        /* Call the handler */
                        (pIntr->cb)(pIntr->pData);
                    }

                    /* All other normal interrupts */
                    if(usNormIntSts & _NORM_INTR_LVL)
                    {
                        hc_clrNormIntrSts(uiSlot,
                            (usNormIntSts & _NORM_INTR_LVL));

                        /* Get the call back function for the event */
                        pIntr = &intr_hdlr[uiSlot][_NORM_INTR_OTHERS];
                        /* Call the handler */
                        (pIntr->cb)(pIntr->pData);
                    }
                }
                /*
                 * Check the interrupt status here again and serve the
                 * the interrupts here itself again to reduce the latency
                 * Check is done for minimum no of times possible to play fair.
                 */
                usNormIntSts = (hc_getIntrSts(uiSlot) &
                    hc_getIntrMask(uiSlot));
                usErrIntSts = (hc_getErrIntrSts(uiSlot) &
                    hc_getErrIntrMask(uiSlot));
           }while((usNormIntSts || usErrIntSts)
           && (uiIntrCnt < _MAX_INTR_COUNT) );
        }
    }

    SPIN_IRQ_RESTORE(&(intr_pLock->spin), ulFlags);
    return IRQ_HANDLED;
}

/**
 * @brief Dumps all the relevant HC registers.
 *
 * @param[in] uiSlot The slot number of the registers
 *
 * @retval _INTR_INVALID_PARAM Error in input param.
 * @retval _INTR_OK Dump is successful.
 */
intr_sts_e intr_dumpReg(_ub32 uiSlot)
{
    if(uiSlot > _MAX_SLOTS)
    {
        _INTR_DBG_ERR("Error in slot number\n");
        return _INTR_INVALID_PARAM;
    }

    hc_dumpReg(uiSlot);

    return _INTR_OK;
}

/**
 * @brief Generic ISR for eMMC events.
 *
 * @param[in] pArg The function argument for generic handler.
 *
 * retval None.
 */
void intr_genericHdlr(void *pArg)
{
    /* Dump the registers for debugging if handler is not installed */
    _ub32 i = 0;
    for(i = 0; i < _MAX_SLOTS; i++)
    {
        intr_dumpReg(i);
    }

    /* Generic ISR function handler */
    _INTR_DBG_ERR("Whoa Dude..Handler is not installed.\n");
}

/**@}*//* Handlers */
/**@}*//* InterruptController */

