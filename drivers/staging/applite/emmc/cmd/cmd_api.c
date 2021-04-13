/**
 * @file          cmd_api.c
 *
 * \brief         Source file of CMD API layer.
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
 * @addtogroup Device
 * @{
 */

/**
 * @addtogroup Command
 * @{
 */

/*----------------------- Header Files Inclusions ---------------------------*/
#include "os.h"             /* To use OS service APIs */
#include "ra.h"             /* To use register access macros */
#include "intr.h"           /* To use interrupt related APIs */
#include "cmd_api.h"        /* CMD layer header file */
#include "hc_api.h"         /* To use HC APIs */
#include "debug.h"          /* To use the debug zone prints */
#include "config.h"         /* To use vendor specific macros/enums */

/*-------------------------- Macro Definitions ------------------------------*/

/** @addtogroup CMD_DEFINES CMD_DEFINES
 * @{
 */

/* Debug prints definitions */
#ifdef __DEBUG
#define _CMD_DBG_INFO(__format__, arg...)    \
    dz_print(_DZ_CMD, "[%4d]%s::" __format__"\n", __LINE__,    \
    __FUNCTION__,## arg )

#define _CMD_DBG_ERR(__format__, arg...)    \
    dz_print(_DZ_CRTICAL, "[%4d]%s::" __format__"\n", __LINE__,    \
    __FUNCTION__,## arg )
#else
#define _CMD_DBG_INFO(__format__, arg...)
#define _CMD_DBG_ERR(__format__, arg...)
#endif


/* Retry count for CMD/DAT inhibit status checking - 100ms */
#define _RETRY_CNT   100000

/* Retry for command complete wait */
#define _MAX_RETRY   500

/* Command complete/error masks */
#define _CMD_COMPLETE        0x0001
#define _CMD_ERR_MASK        0x000F
#define _CMD_INDEX_ERROR     0x0008
#define _CMD_ENDBIT_ERROR    0x0004
#define _CMD_CRC_ERROR       0x0002
#define _CMD_TIMEOUT_ERROR   0x0001

/*
 * Timeout for transfer complete:
 * Timeout value = 900s, assuming 400kHz freq and 1-bit bus-width, for
 * a data size of up to 32MB, and considering system overheads.
 */
#define _TRANS_TIMEOUT       900000

/**@}*/ // CMD_DEFINES

/*---------------------------- Prototypes -----------------------------------*/

/** @addtogroup CMD_Prototypes CMD_Prototypes
 * @{
 */

/* Function for packing the value to be written to the command register */
static _ub16 packCommand(cmd_params_t *pCmdParams);

/* Intr handler function for command complete interrupts */
static void wakeCmdComplete(void *pArg);

/* Intr handler function for command error interrupts */
static void wakeCmdError(void *pArg);

/* Intr handler function for Transfer complete interrupt */
static void wakeTransComplete(void *);

/* Intr handler function for data error interrupt */
static void wakeDataError(void *pArg);

/* Intr handler function for ADMA error interrupt */
static void wakeADMAError(void *pArg);

/**@}*/ // CMD_Prototypes

/*------------- Data variable/Structure allocation (global) -----------------*/

/** @addtogroup CMD_Globals CMD_Globals
 * @{
 */

static _ub32 cmd_uiSlot[_MAX_SLOTS] = {0};

/* Completion variables for command and transfer complete events */
static COMPLETION cmd_complete[_MAX_SLOTS];
static COMPLETION cmd_transcomp[_MAX_SLOTS];

/*
 * This table will maintain the command register field values
 * for each response category. Refer Table 2-10 of SD HC spec ver3.00
 */
static _ub16 cmd_usRgstParamsTbl[_RESP_CTGY_MAX]=
{
    0x0000, /* RespCtgy0: RespTyp 0b00, IndxCheckEnable 0, CRC Check enable 0 */
    0x0009, /* RespCtgy1: RespTyp 0b01, IndxCheckEnable 0, CRC Check enable 1 */
    0x0002, /* RespCtgy2: RespTyp 0b10, IndxCheckEnable 0, CRC Check enable 0 */
    0x001A, /* RespCtgy3: RespTyp 0b10, IndxCheckEnable 1, CRC Check enable 1 */
    0x001B  /* RespCtgy4: RespTyp 0b11, IndxCheckEnable 1, CRC Check enable 1 */
};

/* Variable to update data error */
static _ub32 cmd_uiDatErr = 0;

/* Variable to update ADMA error */
static _ub32 cmd_uiADMAErr = 0;

/* Variable to update CMD error */
static _ub32 cmd_uiCmdErr = 0;

/**@}*/ // CMD_Globals

/*----------------------- Function Definitions ------------------------------*/

/** @addtogroup CMD_Functions CMD_Functions
 * @{
 */

/**
 * @brief Packs the value to be written to the command register.
 *
 * @param[in] pCmdParams The params to update appropriate values to cmd reg
 *
 * @retval usRegVal The value to be written to the command register
 */
static _ub16 packCommand(cmd_params_t *pCmdParams)
{
    _ub16 usRegVal = 0;

    /*
     * Pack parameters into usRegVal:
     *
     * Read the table value corresponding to the
     * Response category and OR it with the CMD index
     */
    usRegVal = (cmd_usRgstParamsTbl[pCmdParams->eRespCtgy]) |
    ((_ub16)(pCmdParams->eIndex) << 8);

    /* Based on input from upper layer, update "Data Present Select" bit5 */
    if(_DAT_USED_DATA  == pCmdParams->eDatUsage)
    {
        usRegVal |= 0x20;   /* Set "Data Present Select" bit */
    }

    /* SPCL CASE: If the cmd is CMD12, update "Abort" bits[7:6] as 0b11 */
    if(_CMD12 == pCmdParams->eIndex)
    {
        usRegVal |= 0xC0;   /* Command Type = Abort (0b11) */
    }

    return usRegVal;
}

/**
 * @brief Checks the inhibit status of CMD/DAT line.
 *
 * @param[in] uiSlot Slot number of host controller
 * @param[in] uiLine Line whose inhibit sts to be checked - _CMD_LINE/_DAT_LINE
 *
 * @retval ucRet Inhibit status - _LINE_BUSY/_LINE_FREE
 */
_ub8 cmd_checkInhibitSts(
    _ub32 uiSlot,
    _ub32 uiLine)
{
    _ub32 uiLoopCnt = 0;
    _ub8 ucRet = 0;

    while(uiLoopCnt < _RETRY_CNT)
    {
        /*
         * Check for the CMD Inhibit(CMD) or CMD inhibit(DAT) in Present State
         * Register based on uiLine input
         */
        if(_LINE_FREE == (hc_getPresentState(uiSlot)& uiLine))
        {
            break;
        }

        uiLoopCnt ++;

        /* Wait for finite time */
        os_delayUs(1); /* Wait time in units of ms */
    }
    /* If CMD Inhibit is set to 1 even after retrying 5 times, return busy */
    if(_RETRY_CNT == uiLoopCnt)
    {
        ucRet = _LINE_BUSY;
    }
    else
    {
        ucRet = _LINE_FREE;
    }
    return ucRet;
}

/**
 * @brief Initializes the CMD layer of eMMC driver
 *
 * @param[in] uiSlot Slot number of host controller
 *
 * @retval _CMD_STS_OK Cmd layer initialization successful
 * @retval _CMD_INIT_NG Cmd layer initialization failed
 */
cmd_sts_e cmd_init(_ub32 uiSlot)
{
    intr_sts_e eIntRet = _INTR_OK;

    _CMD_DBG_INFO("ENTRY");

    cmd_uiSlot[uiSlot] = uiSlot;

    /* Register interrupt handler for transfer complete interrupt */
    eIntRet = intr_registerHdlr(
        _NORM_INTR_TX_COMP,
        (FUNC_PTR)wakeTransComplete,
        &cmd_uiSlot[uiSlot],
        cmd_uiSlot[uiSlot]);
    if(_INTR_OK != eIntRet)
    {
        _CMD_DBG_ERR("CMD layer intr handler registration failed\n");
        return _CMD_INIT_NG;
    }

    /* Register interrupt handler for data error interrupt */
    eIntRet = intr_registerHdlr(
        _ERR_INTR_DATA,
        (FUNC_PTR)wakeDataError,
        &cmd_uiSlot[uiSlot],
        cmd_uiSlot[uiSlot]);
    if(_INTR_OK != eIntRet)
    {
        _CMD_DBG_ERR("CMD layer intr handler registration failed\n");
        return _CMD_INIT_NG;
    }

    /* Register interrupt handler for ADMA error interrupt */
    eIntRet = intr_registerHdlr(
        _ERR_INTR_ADMA,
        (FUNC_PTR)wakeADMAError,
        &cmd_uiSlot[uiSlot],
        cmd_uiSlot[uiSlot]);
    if(_INTR_OK != eIntRet)
    {
        _CMD_DBG_ERR("CMD layer intr handler registration failed\n");
        return _CMD_INIT_NG;
    }

    /* Initialize the wakeup signal (completions) */
    os_initWakeupSignal(&cmd_transcomp[uiSlot]);
    os_initWakeupSignal(&cmd_complete[uiSlot]);

    /* Intr handler registration for command complete interrupt */
    eIntRet = intr_registerHdlr(
        _NORM_INTR_CMD_COMP,
        (FUNC_PTR)wakeCmdComplete,
        &cmd_uiSlot[uiSlot],
        cmd_uiSlot[uiSlot]);
    if(_INTR_OK != eIntRet)
    {
        _CMD_DBG_ERR("CMD layer intr handler registration failed\n");
        return _CMD_INIT_NG;
    }

    /* Intr handler registration for command error interrupt */
    eIntRet = intr_registerHdlr(
        _ERR_INTR_CMD,
        (FUNC_PTR)wakeCmdError,
        &cmd_uiSlot[uiSlot],
        cmd_uiSlot[uiSlot]);
    if(_INTR_OK != eIntRet)
    {
        _CMD_DBG_ERR("CMD layer intr handler registration failed\n");
        return _CMD_INIT_NG;
    }

    /* Initialize error variables */
    cmd_uiDatErr = 0;
    cmd_uiADMAErr = 0;
    cmd_uiCmdErr = 0;

    _CMD_DBG_INFO("EXIT");

    return _CMD_STS_OK;
}

/**
 * @brief Deallocates and exits the CMD layer of eMMC driver
 *
 * @param[in] uiSlot Slot No of host controller
 *
 * @retval _CMD_STS_OK Cmd layer exit successful
 * @retval _CMD_EXIT_NG Cmd layer exit failed
 */
cmd_sts_e cmd_exit(_ub32 uiSlot)
{
    intr_sts_e eIntRet = _INTR_OK;
    cmd_sts_e eRet = _CMD_STS_OK;

    _CMD_DBG_INFO("ENTRY");

    /* De-register interrupt handler for command complete interrupt */
    eIntRet = intr_deregisterHdlr(_NORM_INTR_CMD_COMP, uiSlot);
    if(_INTR_OK != eIntRet)
    {
        _CMD_DBG_ERR("CMD layer intr handler deregistration failed\n");
        eRet = _CMD_EXIT_NG;
    }

    /* De-register interrupt handler for command error interrupt */
    eIntRet = intr_deregisterHdlr(_ERR_INTR_CMD, uiSlot);
    if(_INTR_OK != eIntRet)
    {
        _CMD_DBG_ERR("CMD layer intr handler deregistration failed\n");
        eRet = _CMD_EXIT_NG;
    }

    /* De-register interrupt handler for transfer complete interrupt */
    eIntRet = intr_deregisterHdlr(_NORM_INTR_TX_COMP, uiSlot);
    if(_INTR_OK != eIntRet)
    {
        _CMD_DBG_ERR("CMD layer intr handler deregistration failed\n");
        eRet = _CMD_EXIT_NG;
    }

    /* De-register interrupt handler for data error interrupt */
    eIntRet = intr_deregisterHdlr(_ERR_INTR_DATA, uiSlot);
    if(_INTR_OK != eIntRet)
    {
        _CMD_DBG_ERR("CMD layer intr handler deregistration failed\n");
        eRet = _CMD_EXIT_NG;
    }

    /* De-register interrupt handler for ADMA error interrupt */
    eIntRet = intr_deregisterHdlr(_ERR_INTR_ADMA, uiSlot);
    if(_INTR_OK != eIntRet)
    {
        _CMD_DBG_ERR("CMD layer intr handler deregistration failed\n");
        eRet = _CMD_EXIT_NG;
    }

    _CMD_DBG_INFO("EXIT");

    return eRet;
}

/**
 * @brief Sends commands to eMMC and gives response data back.
 *
 * @param[in] uiSlot Slot number of host controller
 * @param[in] pCmdParams Parameters for framing & updating command register
 * @param[out] pResponse The variable/array to write the response data.
 *
 * @retval _CMD_STS_OK Command sending successful
 * @retval _CMD_CMDLINE_BUSY Command line busy
 * @retval _CMD_DATLINE_BUSY DAT line busy
 * @retval _CMD_INPUT_PARAM_ERR An input param to the API was wrong
 */
cmd_sts_e cmd_sendCommand(
    _ub32 uiSlot,
    cmd_params_t *pCmdParams,
    _ub32 *pResponse)
{
    _ub8 ucRet = 0;
    _ub16 usCmdVal = 0;
    os_sts_e eOsSts = _OS_OK;
    hc_sts_e eHcSts = _HC_STS_OK;

    _CMD_DBG_INFO("ENTRY");

    /* Validate Input Arguments */
    if((NULL == pCmdParams) || (NULL == pResponse))
    {
        return _CMD_INPUT_PARAM_ERR;
    }

    if((pCmdParams->eIndex < _CMD0) ||
        (pCmdParams->eIndex > _CMD63))
    {
        return _CMD_INPUT_PARAM_ERR;
    }

    if((pCmdParams->eDatUsage < _DAT_UNUSED) ||
        (pCmdParams->eDatUsage >= _DAT_USED_INVALID))
    {
        return _CMD_INPUT_PARAM_ERR;
    }

    if((pCmdParams->eRespCtgy < _RESP_CTGY0) ||
        (pCmdParams->eRespCtgy >= _RESP_CTGY_MAX))
    {
        return _CMD_INPUT_PARAM_ERR;
    }

    /* Check CMD line inhibit status */
    ucRet = cmd_checkInhibitSts(uiSlot, _CMD_LINE);
    if(_LINE_BUSY == ucRet)
    {
        _CMD_DBG_INFO("CMD line busy\n");
        return _CMD_CMDLINE_BUSY;
    }

    /* Check if DAT line is required for the command */
    if(_DAT_UNUSED != pCmdParams->eDatUsage)
    {
        /* Check DAT line inhibit status */
        ucRet = cmd_checkInhibitSts(uiSlot, _DAT_LINE);
        if(_LINE_BUSY == ucRet)
        {
            _CMD_DBG_INFO("DAT line busy\n");
            return _CMD_DATLINE_BUSY;
        }
    }

    /* Frame the command register value */
    usCmdVal = packCommand(pCmdParams);

    _CMD_DBG_INFO("-------------- CMD No: %u, ARG: 0x%08x\n",
        pCmdParams->eIndex,
        pCmdParams->uiArg);


#ifdef __GLEN
    /* Write to the Command register. This will send command to the device. */
    hc_setCmdTransReg(uiSlot, usCmdVal, pCmdParams->uiArg);
#else /* !__GLEN */
    /* Write to the Command register. This will send command to the device. */
    hc_setCmdReg(uiSlot, usCmdVal, pCmdParams->uiArg);
#endif /* __GLEN */

    /* Wait for command complete */
    eOsSts = os_waitForSignal(&cmd_complete[uiSlot], 2000);
    if(_OS_OK != eOsSts) /* Timeout occured */
    {
        _CMD_DBG_ERR("Wait for completion timed out\n");
        return _CMD_TRANSTIMEOUT_ERR;
    }

    /* Check if command error occured */
    if(1 == cmd_uiCmdErr)
    {
        cmd_uiCmdErr = 0;
        _CMD_DBG_ERR("Command related Error occured\n");
        return _CMD_SEND_ERR;
    }

    /* If DAT line is used, wait until transfer complete is received */
    if(_DAT_UNUSED != pCmdParams->eDatUsage)
    {
        /* Wait for transfer complete */
        eOsSts = os_waitForSignal(&cmd_transcomp[uiSlot], _TRANS_TIMEOUT);
        if(_OS_OK != eOsSts) /* Timeout occured */
        {
            _CMD_DBG_ERR("Wait for completion timed out\n");
            return _CMD_TRANSTIMEOUT_ERR;
        }

        /* If any data error or ADMA error occurs, return error */
        if((0 != cmd_uiDatErr) || (0 != cmd_uiADMAErr))
        {
            /* Reset the CMD and DAT line and return error */
            eHcSts = hc_reset(uiSlot, _COM_RST_CMD);
            if(_HC_STS_OK != eHcSts)    /* CMD line reset failed */
            {
                _CMD_DBG_ERR("CMD line reset failed");
            }

            eHcSts = hc_reset(uiSlot, _COM_RST_DAT);
            if(_HC_STS_OK != eHcSts)    /* DAT line reset failed */
            {
                _CMD_DBG_ERR("DAT line reset failed");
            }

            /* If ADMA error occured, dump ADMA error status register  */
            if(0 != cmd_uiADMAErr)
            {
                cmd_uiADMAErr = 0;

                _CMD_DBG_ERR("ADMA related error occured");
                _CMD_DBG_ERR("ADMA error status reg value : 0x%02x",
                    R8_ADMA_ERR(uiSlot));
                return _CMD_ADMA_ERR;
            }

            /* Data error occured */
            cmd_uiDatErr = 0;
            _CMD_DBG_ERR("Data related error occured");
            return _CMD_DATA_ERR;
        }

    }

    /*
     * Read response data and store to the array pointed to by pResponse.
     * For R2 response, response registers R0-R7 should be read.
     * For all other responses read R0-R1 response registers.
     */
    switch(pCmdParams->eRespCtgy)
    {
        /* No response */
        case _RESP_CTGY0:
        break;

        /* R2 response */
        case _RESP_CTGY1:
            *pResponse = hc_getResponse(uiSlot, _COM_RESP_01);
            pResponse++;
            *pResponse = hc_getResponse(uiSlot, _COM_RESP_23);
            pResponse++;
            *pResponse = hc_getResponse(uiSlot, _COM_RESP_45);
            pResponse++;
            *pResponse = hc_getResponse(uiSlot, _COM_RESP_67);
        break;

        /* R1/R3/R5 responses */
        default:
            *pResponse = hc_getResponse(uiSlot, _COM_RESP_01);
        break;
    }

    _CMD_DBG_INFO("EXIT");

    return _CMD_STS_OK;

}

/**
 * @brief Reads the response registers
 *
 * @param[in] uiSlot Host Controller slot number
 * @param[out] pResponse The array to write the response data.
 *
 * @retval _CMD_STS_OK Get response successful
 * @retval _CMD_INPUT_PARAM_ERR Input parameter incorrect
 */
cmd_sts_e cmd_getResponse(
    _ub32 uiSlot,
    _ub32 *pResponse)
{
    _CMD_DBG_INFO("ENTRY");

    if(NULL == pResponse)
    {
        _CMD_DBG_ERR("Input argument error\n");
        return _CMD_INPUT_PARAM_ERR;
    }
    *pResponse = hc_getResponse(uiSlot, _COM_RESP_01);
    pResponse++;
    *pResponse = hc_getResponse(uiSlot, _COM_RESP_23);
    pResponse++;
    *pResponse = hc_getResponse(uiSlot, _COM_RESP_45);
    pResponse++;
    *pResponse = hc_getResponse(uiSlot, _COM_RESP_67);

    _CMD_DBG_INFO("EXIT");

    return _CMD_STS_OK;
}

/**
 * @brief Handler for transfer complete intr
 *
 * @param[in] pArg Pointer to slot number value arg
 *
 * @retval None
 */
static void wakeTransComplete(void *pArg)
{
    _ub32 uiSlot = *(_ub32 *)pArg;

    _CMD_DBG_INFO("ENTRY: Transfer complete interrupt received...");

    /* Send complete to wake up the sleeping thread */
    os_wakeup(&cmd_transcomp[uiSlot]);

    _CMD_DBG_INFO("EXIT");
}

/**
 * @brief Handler for data related errors
 *
 * @param[in] pArg Pointer to slot number value arg
 *
 * @retval None
 */
static void wakeDataError(void *pArg)
{
    _ub32 uiSlot = *(_ub32 *)pArg;

    _CMD_DBG_INFO("ENTRY: Data error interrupt received...");

    /* Update error */
    cmd_uiDatErr = 1;

    /* Send complete to wake up the sleeping thread */
    os_wakeup(&cmd_transcomp[uiSlot]);

    _CMD_DBG_INFO("EXIT");
}

/**
 * @brief Handler for ADMA related errors
 *
 * @param[in] pArg Pointer to slot number value arg
 *
 * @retval None
 */
static void wakeADMAError(void *pArg)
{
    _ub32 uiSlot = *(_ub32 *)pArg;

    _CMD_DBG_INFO("ENTRY: Data error interrupt received...");

    /* Update error */
    cmd_uiADMAErr = 1;

    /* Send complete to wake up the sleeping thread */
    os_wakeup(&cmd_transcomp[uiSlot]);

    _CMD_DBG_INFO("EXIT");
}

/**
 * @brief Handler for transfer complete intr
 *
 * @param[in] pArg Pointer to slot number value arg
 *
 * @retval None
 */
static void wakeCmdComplete(void *pArg)
{
    _ub32 uiSlot = *(_ub32 *)pArg;

    _CMD_DBG_INFO("ENTRY: Command complete interrupt received...");

    os_wakeup(&cmd_complete[uiSlot]);

    _CMD_DBG_INFO("EXIT");
}

/**
 * @brief Handler for transfer complete intr
 *
 * @param[in] pArg Pointer to slot number value arg
 *
 * @retval None
 */
static void wakeCmdError(void *pArg)
{
    _ub32 uiSlot = *(_ub32 *)pArg;

    _CMD_DBG_INFO("ENTRY: Command error interrupt received...");

    /* Set command error flag */
    cmd_uiCmdErr = 1;

    os_wakeup(&cmd_complete[uiSlot]);

    _CMD_DBG_INFO("EXIT");
}
/**@}*/ // CMD_Functions

/**@} *//* Command */
/**@} *//* Device */

