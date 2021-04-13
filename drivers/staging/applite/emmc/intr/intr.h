/**
 * @file          intr.h
 *
 * \brief         Header file for Interrupt Layer.
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

#ifndef _INTR_H_
#define _INTR_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*----------------------------- Headers --------------------------------------*/
#include "os.h"    /* To use OS service APIs */

/*--------------------------- Macro Definitions ------------------------------*/

/*----------------------------- Enumerations --------------------------------*/

/*--------------------- Data Structures & Custom typedefs------------------- */

/** @addtogroup Intr_Enums Intr_Enums
 * @{
 */

/**
 * @brief HC Interrupt indices
 */
typedef enum tag_events_e{
    _NORM_INTR_CMD_COMP = 0,       /**< Command complete interrupt */
    _NORM_INTR_TX_COMP,            /**< Transfer complete interrupt */
    _NORM_INTR_DMA,                /**< DMA interrupt for both SDMA/ADMA */
    _NORM_INTR_WR_PIO,             /**< Buffer write interrupt for PIO*/
    _NORM_INTR_RD_PIO,             /**< Buffer Read interrupt for PIO */
    _NORM_INTR_OTHERS,             /**< All other normal interrupts */
    _ERR_INTR_CMD,                 /**< Error interrupts related to cmds */
    _ERR_INTR_DATA,                /**< Error interrupts related to data */
    _ERR_INTR_ADMA,                /**< Error related to ADMA */
    _ERR_INTR_OTHERS,              /**< All other error interrupts */
    _MAX_NUM_EVENTS                /**< Invalid event */
}events_e;

/**
 * @brief Interrupt related status
 */
typedef enum tag_intr_sts_e{
    _INTR_OK             = 0x0000,  /**< Interrupt function call successful */
    _INTR_INVALID_PARAM  = 0x0001,  /**< Invalid param in interrupt func call */
    _INTR_ERR_MOD_TIMER  = 0x0002,  /**< Error in modifying timer*/
    _INTR_ERR_INIT       = 0x0003,  /**< Error in init function */
    _INTR_ERR_EXIT       = 0x0004,  /**< Error in exit function */
    _INTR_ERR_POLL       = 0x0005,  /**< Error in polling init*/
    _INTR_STS_INVALID    = 0x0006,  /**< Intr status invalid */
} intr_sts_e;

/**@}*/ //end of Intr_Enums


/** @defgroup Intr_Structures Intr_Structures
 * @{
 */

/**
 * @brief Interrupt call back function structure
 */
typedef struct tag_intr_cb_t
{
    FUNC_PTR cb; /**< Function pointer for the call back functions in ISR*/
    void *pData; /**< Data argument for the call back function */
}intr_cb_t;

/**@}*/ // Intr_Structures

/*------------------------------ Prototypes --------------------------------*/

/** @addtogroup Intr_Prototypes Intr_Prototypes
 * @{
 */

/* Function to initialize interrupt resources*/
intr_sts_e intr_init(void );

/* Function to de-initialize interrupt resources*/
intr_sts_e intr_exit(void );

/* Function for polling events */
intr_sts_e intr_pollEvtInit(_ub32 uiPollTime);

/* Function for polling events */
intr_sts_e intr_pollEvtExit(void);

/* Function to handle interrupts */
IRQRET intr_irqHandler(_b32 iIrq, void *pArg);

/* Function to dump interrupt registers */
intr_sts_e intr_dumpReg(_ub32 uiSlot);

/* Function to register handler for different events */
intr_sts_e intr_registerHdlr(
    events_e event,
    FUNC_PTR pfnHandler,
    void *pArg,
    _ub32 uiSlot);

/* Function to deregister handler for different events */
intr_sts_e intr_deregisterHdlr(events_e event, _ub32 uiSlot);

/* Function for checking interrupts in polling fashion */
void intr_pollHdlr(void *pArg);

/**@}*/ // Intr_Prototypes

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _INTR_H_ */

/**@}*//* Handlers */
/**@}*//* InterruptController */

