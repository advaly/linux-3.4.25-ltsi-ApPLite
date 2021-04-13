/**
 * @file          hc_api.h
 *
 * \brief         This file includes host configuration macros and
 * APIs' prototypes.
 *
 * \b COPYRIGHT : TOSHIBA Corporation Semiconductor and Storage Company
 * 2010-2015 All rights reserved.
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
 * @addtogroup HostController
 * @{
 */

/**
 * @addtogroup HCAPIs
 * @{
 */

#ifndef _HC_API_H_
#define _HC_API_H_


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*----------------------- Header Files Inclusions ---------------------------*/

#include "com.h"    /* Required to access commonly used enums */
#include "config.h" /* To access vendor specific data */

/*-------------------------- Macro Definitions ------------------------------*/

/*-------------------------- Enum Definitions -------------------------------*/

/** @addtogroup HC_Enums HC_Enums
 * @{
 */

/**
 * @brief Enum containing status/return values for HC configuration functions
 */
typedef enum tag_hc_sts_e
{
    /**< Host controller config is successful */
    _HC_STS_OK              = 0x0000,
    /**< Wrong values read from the register */
    _HC_STS_ERR             = 0x0001,
    /**< Host controller config is timed out */
    _HC_STS_TIMEOUT         = 0x0002,
    /**< If feature is not supported by Host controller */
    _HC_STS_NOTSUPPORTED    = 0x0003,
}hc_sts_e;

/**@}*/ //end of HC_Enums

/*------------------ Data Structures & Custom Typedefs ----------------------*/

/** @defgroup HC_Structures HC_Structures
 * @{
 */

/**
 * @brief Structure for Capabilities Register
 */
typedef struct tag_CapReg_params_t
{
    _ub8 ucClkMulti;       /**< Clock Multiplier */
    _ub8 ucReTuneMode;     /**< Re-Tuning Modes */
    _ub8 ucSDR50Tune;      /**< Use Tuning for SDR50 */
    _ub8 ucReTuneTimer;    /**< Timer Count for Re-Tuning */
    _ub8 ucTypeD;          /**< Driver Type D Support */
    _ub8 ucTypeC;          /**< Driver Type C Support */
    _ub8 ucTypeA;          /**< Driver Type A Support */
    _ub8 ucDDR50;          /**< DDR50 Support */
    _ub8 ucSDR104;         /**< SDR104 Support */
    _ub8 ucSDR50;          /**< SDR50 Support */
    _ub8 ucSlotType;       /**< Slot Type of host controller */
    _ub8 ucAsyncInt;       /**< Asynchronous Interrupt Support */
    _ub8 ucSysBus64;       /**< 64 bit System Bus support */
    _ub8 ucV1_8;           /**< Voltage support 1.8V */
    _ub8 ucV3_0;           /**< Voltage support 3.0V */
    _ub8 ucV3_3;           /**< Voltage Support 3.3V */
    _ub8 ucSuspRes;        /**< Suspend Resume Support */
    _ub8 ucSDMA;           /**< SDMA mode support bit */
    _ub8 ucHSpeed;         /**< High Speed Support */
    _ub8 ucADMA2;          /**< ADMA2 mode support bit */
    _ub8 ucEDev8;          /**< 8 bit support for Embedded Device */
    _ub8 ucMaxBlkLen;      /**< Maximum Block Length */
    _ub8 ucBaseClkFreq;    /**< Base Clock Frequency */
    _ub8 ucTimeoutClk;     /**< Time out Clock Unit */
    _ub8 ucTimeoutClkFreq; /**< Time Out Clock Frequency */
}CapReg_params_t;

/**
 * @brief Structure for transfer mode reg value
 */
typedef struct tag_transVal_t
{
    _ub8 ucDMAEn;          /**< DMA enable/disable  */
    _ub8 ucBlkCntEn;       /**< Block count enable/disable */
    _ub8 ucAutoCmdEn;      /**< Autocmd enable/disable */
    _ub8 ucDatTxDir;       /**< Data transfer direction */
    _ub8 ucSingMultiBlk;   /**< Single/Multi block */
}transVal_t;

/**@}*/ // HC_Structures

/*------------------------------ Externs ------------------------------------*/

/** @addtogroup HC_Externs HC_Externs
 * @{
 */

extern CapReg_params_t hc_cap_val[_MAX_SLOTS];

/**@}*/ // HC_Externs

/*---------------------------- Prototypes -----------------------------------*/

/** @addtogroup HC_Prototypes HC_Prototypes
 * @{
 */

/* Function to get the host controller capabilities  */
hc_sts_e hc_getCapabilities(_ub32 uiSlot, CapReg_params_t *pCap);

/* Function to reset the Host controller */
hc_sts_e hc_reset(_ub32 uiSlot, com_swRst_e resetLine);

/* Function to set the physical address for DMA operations */
hc_sts_e hc_setDMAAdr(_ub32 uiSlot, _ub32 uiAddr);

/* Function to get the SD clock frequency */
_ub32 hc_getFreq(_ub32 uiSlot);

/* Function to set the frequency for the SD bus */
hc_sts_e hc_setFreq(_ub32 uiSlot, _ub32 uiFreq);

/* Function to set the data parameters before the data transactions begin */
hc_sts_e hc_setDataParams(_ub32 uiSlot, _ub32 uiSize, com_RWDir_e dir);

/* Function to get the SD bus width */
com_busWidth_e hc_getBusWidth(_ub32 uiSlot);

/* Function to set the SD bus width for a data transaction */
hc_sts_e hc_setBusWidth(_ub32 uiSlot, com_busWidth_e width);

/* Function to set the SD bus voltage */
hc_sts_e hc_setBusPwr(_ub32 uiSlot, com_volt_e voltValue);

/* Function to get the mode of operation (PIO/ SDMA/ ADMA) */
com_modes_e hc_getOpMode(_ub32 uiSlot);

/* Function to set the operation mode for data transaction */
hc_sts_e hc_setOpMode(_ub32 uiSlot, com_modes_e mode);

/* Function to enable the normal interrupts */
void hc_enableIntr(_ub32 uiSlot, _ub16 uiMaskVal);

/* Function to disable the normal interrupts */
void hc_disableIntr(_ub32 uiSlot, _ub16 uiMaskVal);

/* Function to enable the error interrupts */
void hc_enableErrIntr(_ub32 uiSlot, _ub16 uiMaskVal);

/* Function to disable the error interrupts */
void hc_disableErrIntr(_ub32 uiSlot, _ub16 uiMaskVal);

/* Function to get the information about the normal interrupts enbabled */
_ub16 hc_getIntrMask(_ub32 uiSlot);

/* Function to get the information about the error interrupts enbabled */
_ub16 hc_getErrIntrMask(_ub32 uiSlot);

/* Function to get the normal interrupts' status */
_ub16 hc_getIntrSts(_ub32 uiSlot);

/* Function to get the error interrupts' status */
_ub16 hc_getErrIntrSts(_ub32 uiSlot);

/* Function to get the HC register dump */
void hc_dumpReg(_ub32 uiSlot);

/* Function to get the slot interrupts' status */
_ub16 hc_getSlotIntrSts(_ub32 uiSlot);

/* Function to get the Buffer Data Port register value */
_ub32 hc_getBufDatPort(_ub32 uiSlot);

/* Function to set the Buffer Data Port register value */
void hc_setBufDatPort(_ub32 uiSlot, _ub32 uiVal);

/* Function to get the Response register value */
_ub32 hc_getResponse(_ub32 uiSlot, com_resp_e resp);

/* Function to get the Present state register value */
_ub32 hc_getPresentState(_ub32 uiSlot);

/* Function to clear the Error interrupt status register */
void hc_clrErrIntrSts(_ub32 uiSlot, _ub16 usErrVal);

/* Function to clear the Normal interrupt status register */
void hc_clrNormIntrSts(_ub32 uiSlot, _ub16 usIntrVal);

/* Function to set the block size register */
void hc_setBlockSize(_ub32 uiSlot, _ub16 usBlkSize);

/* Function to set the command register */
void hc_setCmdReg(_ub32 uiSlot, _ub16 usCmdVal, _ub32 uiCmdArg);

/* Function to write the command and Transfer mode register at once */
void hc_setCmdTransReg(_ub32 uiSlot, _ub16 usCmdVal, _ub32 uiCmdArg);

/* Function to initialize the host controller with default values */
hc_sts_e hc_init(_ub32 *pValidSlot);

/* Function to disable all the interrupts and reset all the slots */
void hc_exit(void);

/**@}*/ // HC_Prototypes

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _HC_API_H_ */

/**@} *//* HCAPIs */
/**@} *//* HostController */

