/**
 * @file          hc_api.c
 *
 * \brief         This file includes host configuration APIs' implementation.
 *
 * \b COPYRIGHT : TOSHIBA Corporation Semiconductor and Storage Company
 * 2010-2015 All rights reserved.
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
 * @addtogroup HostController
 * @{
 */

/**
 * @addtogroup HCAPIs
 * @{
 */

/*----------------------- Header Files Inclusions ---------------------------*/
#include "types.h"  /* TO access the data types' typedefs */
#include "os.h"     /* Required to access os services */
#include "hc_api.h" /* To access all the HC data types */
#include "ra.h"     /* To make use of all the register access macros */
#include "debug.h"  /* To access the debug macros and functions */

/*-------------------------- Macro Definitions ------------------------------*/

/** @addtogroup HC_DEFINES HC_DEFINES
 * @{
 */

#ifndef _HC_DEBUG
#define _HC_DEBUG
#endif

#ifdef _HC_DEBUG

#define msgi(__format__, arg...)    \
       dz_print(_DZ_HC, "%s::" __format__"\n", __FUNCTION__, ## arg)

#define msgc(__format__, arg...)    \
       dz_print(_DZ_CRTICAL, "%s::" __format__"\n", __FUNCTION__, ## arg)

#else

#define msgi(__format__, arg...)    /* do nothing */
#define msgc(__format__, arg...)    /* do nothing */

#endif

#define _MAX_BLK_CNT    0xFFFF /* Maximum blk count possible */

#define _RETRYCNT       10 /* Retry count for reset and clock stabilisation */

/*
 * Maximum frequency supported is 100MHz.
 */
#define _MAX_FREQ       100000000

/*
 * Macros representing standard frequency values required for checking the
 * input frequency ranges and further for setting UHS bits or any other
 * frequency related bits
 */
#define _12MHZ          12000000U
#define _25MHZ          25000000U
#define _50MHZ          50000000U
#define _104MHZ         104000000U

/* Macros that include all the mask values of Capabilities Register */
#define _CLK_MULTI                0x00ff0000U  /* Bits 48-55 */
#define _RETUNE_MODES             0x0000C000U  /* Bits 46-47 */
#define _SDR50_TUNE               0x00002000U  /* Bit 45 */
#define _RETUNE_TIMER             0x00000f00U  /* Bits 40-43 */
#define _TYPED                    0x00000040U  /* Bit 38 */
#define _TYPEC                    0x00000020U  /* Bit 37 */
#define _TYPEA                    0x00000010U  /* Bit 36 */
#define _DDR50                    0x00000004U  /* Bit 34 */
#define _SDR104                   0x00000002U  /* Bit 33 */
#define _SDR50                    0x00000001U  /* Bit 32 */
#define _SLOT_TYPE                0xC0000000U  /* Bits 30-31 */
#define _ASYNC_INT                0x20000000U  /* Bit 29 */
#define _SYS_BUS64                0x10000000U  /* Bit 28 */
#define _VOLT1_8                  0x04000000U  /* Bit 26 */
#define _VOLT3_0                  0x02000000U  /* Bit 25 */
#define _VOLT3_3                  0x01000000U  /* Bit 24 */
#define _SUSP_RES                 0x00800000U  /* Bit 23 */
#define _SDMA                     0x00400000U  /* Bit 22 */
#define _HIGH_SPEED               0x00200000U  /* Bit 21 */
#define _ADMA2                    0x00080000U  /* Bit 19 */
#define _EMBED_DEV8               0x00040000U  /* Bit 18 */
#define _MAX_BLKLEN               0x00030000U  /* Bits 16-17 */
#define _BASE_CLKFREQ             0x0000ff00U  /* Bits 08-15 */
#define _TIMEOUT_CLK              0x00000080U  /* Bit 07 */
#define _TIMEOUT_CLKFREQ          0x0000003fU  /* Bits 00-05 */

/*
 * Transfer Mode Register is a 16bit register required for setting transfer
 * parameters
 */
#define _DMAEN                    0x0001U  /* Bit 0 */
#define _BLKCNT_EN                0x0002U  /* Bit 1 */
#define _AUTOCMD_EN               0x000CU  /* Bits 2-3 */
#define _DATA_TXDIR               0x0010U  /* Bit 4 */
#define _SING_MULTIBLK            0x0020U  /* Bit 5 */

/* Software Reset Register is a 8bit register required for resetting */
#define _ALLRST                   0x01U    /* Bit 0 */
#define _CMDRST                   0x02U    /* Bit 1 */
#define _DATRST                   0x04U    /* Bit 2 */

/* Preset value register is a 16bit register required for clock config */
#define _SD_CLKFREQ               0x03FFU  /* Bits 0-9 */
#define _CLKGEN_VAL               0x0400U  /* Bit 10 */
#define _DRV_STREN                0xC000U  /* Bits 14-15 */

/* Host control 1 register is a 8bit register required for features setting */
#define _LED_CTRL                 0x01U    /* Bit 0 */
#define _DATA_TXWIDTH             0x02U    /* Bit 1 */
#define _HSPEED_EN                0x04U    /* Bit 2 */
#define _DMA_SEL                  0x18U    /* Bits 3-4 */
#define _DMA_SDMA                 0x00U    /* value of DMASEL = 00 for SDMA */
#define _DMA_ADMA                 0x10U    /* value of DMASEL = 10 for ADMA */
#define _EDATA_TXWIDTH            0x20U    /* Bit 5 */
#define _CARD_DET_TEST            0x40U    /* Bit 6 */
#define _CARD_DET_SIGSEL          0x80U    /* Bit 7 */

/* Host control 2 register is a 16bit register for advanced features setting */
#define _UHS_MODE_SEL             0x0007U  /* Bits 0-2 */
#define _UHS_SDR12                0x0000U  /* Bits 0-2 : 000 for SDR12 */
#define _UHS_SDR25                0x0001U  /* Bits 0-2 : 001 for SDR25 */
#define _UHS_SDR50                0x0002U  /* Bits 0-2 : 010 for SDR50 */
#define _UHS_SDR104               0x0003U  /* Bits 0-2 : 011 for SDR104 */
#define _UHS_DDR50                0x0004U  /* Bits 0-2 : 100 for DDR50 */
#define _UHS_SDR200               0x0005U  /* Bits 0-2 : 101 for SDR200 */
#define _18V_SIGEN                0x0008U  /* Bit 3 */
#define _DRV_STREN_SEL            0x0030U  /* Bits 4-5 */
#define _EXECUTE_TUNING           0x0040U  /* Bit 6 */
#define _SAMPLING_CLK_SEL         0x0080U  /* Bit 7 */
#define _ASYNC_INTR_EN            0x4000U  /* Bit 14 */
#define _PRESET_VAL_EN            0x8000U  /* Bit 15 */

/*
 * Present State register is a 32 bit register accessed to know
 * the state of the host controller at any point of time
 */
#define _COMMAND_INHIBIT_CMD      0x00000001U   /* Bit 00 */
#define _COMMAND_INHIBIT_DAT      0x00000002U   /* Bit 01 */
#define _DATLINE_ACT              0x00000004U   /* Bit 02 */
#define _RE_TUNING_REQ            0x00000008U   /* Bit 03 */
#define _WTX_ACT                  0x00000100U   /* Bit 08 */
#define _RTX_ACT                  0x00000200U   /* Bit 09 */
#define _BUFW_EN                  0x00000400U   /* Bit 10 */
#define _BUFR_EN                  0x00000800U   /* Bit 11 */
#define _CARD_INSERTED            0x00010000U   /* Bit 16 */
#define _CARDSTATE_STABLE         0x00020000U   /* Bit 17 */
#define _CARDDET_PINLVL           0x00040000U   /* Bit 18 */
#define _WRITE_PROT_PINLVL        0x00080000U   /* Bit 19 */
#define _DATLINE_SIGLVL           0x00F00000U   /* Bits 20-23 */
#define _CMDLINE_SIGLVL           0x01000000U   /* Bit 24 */

/* Power control register is a 8bit register required to set the bus power */
#define _SDBUS_PWR                0x01U         /* Bit 0 */
#define _VBITS                    0x0EU         /* Bits 1-3 for voltage value */
#define _VOLT33                   0x0EU         /* Bits 1-3 for 3.3V */
#define _VOLT30                   0x0CU         /* Bits 1-3 for 3.0V */
#define _VOLT18                   0x0AU         /* Bits 1-3 for 1.8V */

/*
 * Normal Interrupt Status register is a 16bit register required to
 * check for interrupts
 */
#define _CMD_COMP                 0x0001U      /* Bit 0 */
#define _TX_COMP                  0x0002U      /* Bit 1 */
#define _BLKGAP_EVT               0x0004U      /* Bit 2 */
#define _DMA_INT                  0x0008U      /* Bit 3 */
#define _BUFW_READY               0x0010U      /* Bit 4 */
#define _BUFR_READY               0x0020U      /* Bit 5 */
#define _CARD_INSERT              0x0040U      /* Bit 6 */
#define _CARD_REMOVE              0x0080U      /* Bit 7 */
#define _CARD_INT                 0x0100U      /* Bit 8 */
#define _INT_ADET                 0x0200U      /* Bit 9 */
#define _INT_BDET                 0x0400U      /* Bit 10 */
#define _INT_CDET                 0x0800U      /* Bit 11 */
#define _RETUNING_EVT             0x1000U      /* Bit 12 */
#define _ERR_INTR                 0x8000U      /* Bit 15 */
#ifdef __GLEN
#define _ALL_INTR                 0x003BU      /* All relevant bits */
#else /* !__GLEN */
#define _ALL_INTR                 0xFFFFU      /* All bits */
#endif /* __GLEN */

/*
 * Error Interrupt Status register is a 16bit register required to check for
 * interrupts if any
 */
#define _CMD_TIMEOUTERR           0x0001U      /* Bit 0 */
#define _CMD_CRCERR               0x0002U      /* Bit 1 */
#define _CMD_ENDBITERR            0x0004U      /* Bit 2 */
#define _CMD_INDEXERR             0x0008U      /* Bit 3 */
#define _DAT_TIMEOUTERR           0x0010U      /* Bit 4 */
#define _DAT_CRCERR               0x0020U      /* Bit 5 */
#define _DAT_ENDBITERR            0x0040U      /* Bit 6 */
#define _CURR_LMTERR              0x0080U      /* Bit 7 */
#define _AUTO_CMDERR              0x0100U      /* Bit 8 */
#define _ADMA_ERR                 0x0200U      /* Bit 9 */
#define _TUNING_ERR               0x0400U      /* Bit 10 */
#define _VEND_SPECERR             0xF000U      /* Bits 12-15 */
/* All interrupts except command error interrupts for Prototype */
#define _ERRINTR_MASK             0xFFF0U
#define _ALLERR_INTR              0xFFFFU      /* All bits */

/* Clock control register is a 16bit register required for clock config */
#define _INTCLK_EN                0x0001U      /* Bit 0 */
#define _INTCLK_STABLE            0x0002U      /* Bit 1 */
#define _SDCLK_EN                 0x0004U      /* Bit 2 */
#define _CLKGEN_SEL               0x0020U      /* Bit 5 */
/* Upper 2 bits of the 10bit clock frequency */
#define _UBSDCLK_FREQSEL          0x00C0U      /* Bits 6-7 */
/* Lower 8bits of the 10bit SD clock frequency */
#define _SDCLK_FREQSEL            0xFF00U      /* Bit 8-15 */

/**@}*/ // HC_DEFINES

/*-------------------------- Enum Definitions -------------------------------*/

/*------------------ Data Structures & Custom Typedefs ----------------------*/
#ifdef __GLEN
static transVal_t hc_transVal[_MAX_SLOTS];
#endif /* __GLEN */

/*------------------------------ Externs ------------------------------------*/

/*---------------------------- Prototypes -----------------------------------*/

/** @addtogroup HC_Prototypes HC_Prototypes
 * @{
 */

static inline _ub32 checkCardInserted(_ub32 uiSlot);
static void stopClock(_ub32 uiSlot);
static hc_sts_e startClock(_ub32 uiSlot,_ub32 uifreq);
#ifdef __GLEN
/* Function to return the 16 bit value of Transfer mode register */
static _ub16 getTransVal(_ub32 uiSlot);
#endif /* __GLEN */

/**@}*/ // HC_Prototypes

/*------------- Data variable/Structure allocation (global) -----------------*/

/** @addtogroup HC_Globals HC_Globals
 * @{
 */

CapReg_params_t hc_cap_val[_MAX_SLOTS];
_addr hc_BaseAdr;

/**@}*/ // HC_Globals

/*----------------------- Function Definitions ------------------------------*/

/** @addtogroup HC_Functions HC_Functions
 * @{
 */

/**
 * @brief This stores the capabilities of the controller into a structure.
 *
 * @param[in] uiSlot slot number
 * @param[out] pCap pointer to structure t store the Capabilities of HC.
 *
 * @retval _HC_STS_OK Host controller config is successful
 * @retval _HC_STS_ERR Wrong values read/written from/to the register
 */

hc_sts_e hc_getCapabilities(_ub32 uiSlot, CapReg_params_t *pCap)
{
    volatile _ub32 reg = 0;

    msgi("ENTRY: slot number [%d]", uiSlot);

    /* Input argument Check */
    if(NULL == pCap)
    {
        msgc("pCap is a NULL pointer.");
        return _HC_STS_ERR;
    }

    /* Extract the information from the lower 32bits of Capabilities Register */
    reg = R32_CAPABLITY1(uiSlot);
    msgi("Initial 32 bits of capability register: 0x%08x.", reg);

    /* Time Out Clock Frequency(bits[0-5]) */
    pCap->ucTimeoutClkFreq = (_ub8)(reg & _TIMEOUT_CLKFREQ);

    /* Time out Clock Unit(bit[7]) */
    pCap->ucTimeoutClk = (_ub8)((reg & _TIMEOUT_CLK) >> 7);

    /* Base Clock Frequency(bits[8-15]) */
    pCap->ucBaseClkFreq = (_ub8)((reg & _BASE_CLKFREQ) >> 8);

    /* Maximum Block Length(bits[16-17]) */
    pCap->ucMaxBlkLen = (_ub8)((reg & _MAX_BLKLEN) >> 16);

    /* 8 bit support for Embedded Device(bit[18]) */
    pCap->ucEDev8 = (_ub8)((reg & _EMBED_DEV8) >> 18);

    /* ADMA2 mode support bit(bit[19]) */
    pCap->ucADMA2 = (_ub8)((reg & _ADMA2) >> 19);

    /* High Speed Support(bit[21]) */
    pCap->ucHSpeed = (_ub8)((reg & _HIGH_SPEED) >> 21);

    /* SDMA mode support bit(bit[22]) */
    pCap->ucSDMA = (_ub8)((reg & _SDMA) >> 22);

    /* Suspend Resume Support(bit[23]) */
    pCap->ucSuspRes = (_ub8)((reg & _SUSP_RES) >> 23);

    /* Voltage Support 3.3V(bit[24]) */
    pCap->ucV3_3 = (_ub8)((reg & _VOLT3_3) >> 24);

    /* Voltage support 3.0V(bit[25]) */
    pCap->ucV3_0 = (_ub8)((reg & _VOLT3_0) >> 25);

    /* Voltage support 1.8V(bit[26]) */
    pCap->ucV1_8 = (_ub8)((reg & _VOLT1_8) >> 26);

    /* 64 bit System Bus support(bit[28]) */
    pCap->ucSysBus64 = (_ub8)((reg & _SYS_BUS64) >> 28);

    /* Asynchronous Interrupt Support(bit[29]) */
    pCap->ucAsyncInt = (_ub8)((reg & _ASYNC_INT) >> 29);

    /* Slot Type of host controller(bits[30-31]) */
    pCap->ucSlotType = (_ub8)((reg & _SLOT_TYPE) >> 30);

    /* Extract the information from the upper 32bits of Capabilities Register */
    reg = R32_CAPABLITY2(uiSlot);
    msgi("Bits 32-63 of capability register: 0x%08x.", reg);

    /* SDR50 Support(bit[32]) */
    pCap->ucSDR50 = (_ub8)(reg & _SDR50);

    /* SDR104 Support(bit[33]) */
    pCap->ucSDR104 = (_ub8)((reg & _SDR104) >> 1);

    /* DDR50 Support(bit[34]) */
    pCap->ucDDR50 = (_ub8)((reg & _DDR50) >> 2);

    /* Driver Type A Support(bit[36]) */
    pCap->ucTypeA = (_ub8)((reg & _TYPEA) >> 4);

    /* Driver Type C Support(bit[37]) */
    pCap->ucTypeC = (_ub8)((reg & _TYPEC) >> 5);

    /* Driver Type D Support(bit[38]) */
    pCap->ucTypeD = (_ub8)((reg & _TYPED) >> 6);

    /* Timer Count for Re-Tuning(bits[40-43]) */
    pCap->ucReTuneTimer = (_ub8)((reg & _RETUNE_TIMER) >> 8);

    /* Use Tuning for SDR50(bit[45]) */
    pCap->ucSDR50Tune = (_ub8)((reg & _SDR50_TUNE) >> 13);

    /* Re-Tuning Modes(bits[46-47]) */
    pCap->ucReTuneMode = (_ub8)((reg & _RETUNE_MODES) >> 14);

    /* Clock Multiplier(bits[48-55]) */
    pCap->ucClkMulti = (_ub8)((reg & _CLK_MULTI) >> 16);

    /* Bits[55-63] are reserved in capability register */
    return _HC_STS_OK;
}

/**
 * @brief This resets a particular line based on the user input.
 *
 * @param[in] uiSlot slot number
 * @param[in] resetLine particular line to be reset
 *
 * @retval _HC_STS_OK Host controller config is successful
 * @retval _HC_STS_TIMEOUT Host controller config timed out
 */
hc_sts_e hc_reset(_ub32 uiSlot, com_swRst_e resetLine)
{
    volatile _ub8 wval = 0;
    volatile _ub8 rval = 0;
    _ub32 retrycnt = 0;

    msgi("ENTRY: slot number [%d]", uiSlot);

    /* Input arguments are not verified as it will be done by upper layer */

    /* check arg to reset the entire HC registers */
    if(_COM_RST_ALL == resetLine)
    {
        wval = _ALLRST;
    }
    else if(_COM_RST_CMD == resetLine)
    {
        /* data related circuit */
        wval = _CMDRST;
    }
    else if (_COM_RST_DAT == resetLine)
    {
        /* command related circuit */
        wval = _DATRST;
    }
    else
    {
        /* do nothing. [control never comes here] */
    }

    /* Read the initial value of software reset register */
    rval = R8_SOFTWARE_RST(uiSlot);
    msgi("Software reset reg initial: 0x%02x.", rval);

    /* Write the required value into the Software Reset Register */
    wval = (wval | rval);
    W8_SOFTWARE_RST(uiSlot, wval);

    /* Keep polling until the lines are reset : retry 10 times */
    while(retrycnt < _RETRYCNT)
    {
        rval= R8_SOFTWARE_RST(uiSlot);
        if (0 == (wval & rval))
        {
            /* break if the line is reset successfully */
            break;
        }

        /* small delay of 10us: TRIAL AND ERROR VALUE..! */
        os_delayUs(10);
        retrycnt++;
    }

    if(_RETRYCNT == retrycnt)
    {
        msgc("hc_reset timed out: _HC_STS_TIMEOUT");
        return _HC_STS_TIMEOUT;
    }

    msgi("Software reset reg updated: 0x%02x", R8_SOFTWARE_RST(uiSlot));

    return _HC_STS_OK;
}

/**
 * @brief This maps to the System physical address.
 *
 * NOTE: Please call hc_setOpMode() before calling this function.
 *
 * @param[in] uiSlot slot number
 * @param[in] uiaddr physical address of the system.
 *
 * @retval _HC_STS_OK Host controller config is successful
 * @retval _HC_STS_ERR Wrong values read/written from/to the register
 */
hc_sts_e hc_setDMAAdr(_ub32 uiSlot, _ub32 uiAddr)
{
    hc_sts_e hc_status = _HC_STS_OK;
    com_modes_e mode = _COM_MODE_PIO;

    /* Input arguments are not verified as it will be done by upper layer */

    msgi("ENTRY: address: 0x%08x", uiAddr);

    mode = hc_getOpMode(uiSlot);

    switch(mode)
    {
        case _COM_MODE_PIO:
            msgc("DMA is not enabled in Transfer mode reg");
            hc_status = _HC_STS_ERR;
        break;

        case _COM_MODE_SDMA:
            msgi("SDMA mode of operation selected");
            W32_SDMA_ADR(uiSlot, uiAddr);
        break;

        case _COM_MODE_ADMA2:
            msgi("ADMA mode of operation selected");
            W32_ADMASTART1(uiSlot, uiAddr);
        break;

        case _COM_MODE_RSV:
            msgc("Reserved mode selected");
            hc_status = _HC_STS_ERR;
        break;

        default: /*do nothing*/
        break;
    }

    return hc_status;
}

/**
 * @brief This returns back the SD clock frequency.
 *
 * @param[in] uiSlot slot number
 *
 * @retval The SD clock frequency value in Hz.
 */
_ub32 hc_getFreq(_ub32 uiSlot)
{
    volatile _ub16 reg = 0;
    _ub32 baseclk = 0;
    _ub32 divisor = 0;

    /* Input arguments are not verified as it will be done by upper layer */

    msgi("ENTRY: slot number [%d]", uiSlot);

    /* Read capabilities Register structure value */
    baseclk = (_ub32)hc_cap_val[uiSlot].ucBaseClkFreq;
    msgi("Base clock frequency: %u MHz", baseclk);

    /**
     * The freq value read is in MHz eg: 200 means 200MHz
     * Thus multiply with 1000000 to convert it in terms of Hz
     * 200MHz--> 200 * 1000000 = 200000000 Hz
     */
    baseclk = (baseclk * 1000000);

    reg = R16_CLK_CTRL(uiSlot);
    msgi("Clock control reg: 0x%04x", reg);

    /**
     * Get the upper two bits of the SD clock frequency and
     * shift those 2bits to 8th and 9th bit position
     */
    divisor = (_ub32)((reg & _UBSDCLK_FREQSEL) << 2);

    /* Get the lower 8bits of the SD clock frequency and add it the divisor */
    divisor = (divisor | (_ub32)((reg & _SDCLK_FREQSEL) >> 8));
    msgi(" Frequency divisor: %u", divisor);

    /* If divisor value is zero then base frequency is in use */
    if(0 == divisor)
    {
        return baseclk;
    }

    baseclk = (baseclk/(2 * divisor));
    msgi("Freq value to be returned: %u Hz", baseclk);

    return baseclk;
}

/**
 * @brief This sets the frequency of the clock for data transaction.
 *
 * NOTE This function should be called as the last function while setting
 * the host controller configurations like voltage, buswidth etc. This flow is
 * required to maintain the stability and reduce configuration errors.
 *
 * @param[in] uiSlot slot number
 * @param[in] uifreq different frequency values for the clock in unit Hz
 *
 * @retval _HC_STS_OK Host controller config is successful
 * @retval _HC_STS_ERR Wrong values read/written from/to the register
 * @retval _HC_STS_TIMEOUT Host controller config timed out
 */
hc_sts_e hc_setFreq(_ub32 uiSlot, _ub32 uiFreq)
{
    hc_sts_e hc_status = _HC_STS_OK;

    /* Input arguments are not verified as it will be done by upper layer */

    msgi("ENTRY: Frequency to be set: %u", uiFreq);

    /*
     * Host Controller Version 3.00 supports mandatory 10bit mode instead of
     * the 8-bit Divided Clock Mode.
     * Programmable Clock Mode is optionally supported.
     *
     * REF :SD Host Controller Specification Version 3.00 (section 2.2.14)
     *
     * As of now only 10bit divided clock mode is implemented in the driver
     */

    /* Stop the clock initially */
    stopClock(uiSlot);
    msgi("After stopClock");

    /* Start the Clock with the new frequency */
    hc_status = startClock(uiSlot, uiFreq);
    msgi("After startClock: %u", uiFreq);

    return hc_status;
}
/**
 * @brief   This sets the different data parameters before data transaction.
 *
 * @param[in] uiSlot slot number
 * @param[in] uiSize size of the data to be used for transaction
 * @param[in] ucdir direction of data transaction (read : 1 /write : 0);
 *
 * @retval _HC_STS_OK Host controller config is successful
 * @retval _HC_STS_ERR Wrong values read/written from/to the register
 */
hc_sts_e hc_setDataParams(_ub32 uiSlot, _ub32 uiSize, com_RWDir_e dir)
{
    volatile _ub16 reg = 0;
    _ub32 cnt = 1;

    msgi("ENTRY1: size is %u", uiSize);
    msgi("ENTRY2: direction is %d", dir);

#ifndef __GLEN
    reg = R16_TRANSMODE(uiSlot);
    msgi("Transfer mode reg initial: 0x%04x", reg);
#endif /* __GLEN */

    cnt = uiSize/_BLK_SIZE; /* Each Block size = 512B */

    if(cnt > (_ub32)_MAX_BLK_CNT)
    {
        /* The block count is more than the possible max value : 65535 */
        return _HC_STS_ERR;
    }
    else
    {
        /* if the count val is within the range */
        reg = (reg | _BLKCNT_EN); /* Enable the Block count bit */
    }

#ifdef __GLEN
    if(1 < cnt)
    {
        hc_transVal[uiSlot].ucSingMultiBlk = 0x01;/* Indicate as multi block */
    }
    else
    {
        hc_transVal[uiSlot].ucSingMultiBlk = 0x00;/* Indicate as single block */
    }

    if(_COM_DIR_R == dir)
    {
        hc_transVal[uiSlot].ucDatTxDir = 0x01;/* Set the direction as Read */
    }
    else
    {
        hc_transVal[uiSlot].ucDatTxDir = 0x00;/* Set the direction as Write */
    }
#else /* !__GLEN */
    if(1 < cnt)
    {
        reg = (reg | _SING_MULTIBLK); /* Indicate as multi block */
    }
    else
    {
        reg = (reg & (~_SING_MULTIBLK));/* Indicate as single block */
    }

    if(_COM_DIR_R == dir)
    {
        reg = (reg | _DATA_TXDIR); /* Set the direction as Read */
    }
    else
    {
        reg = (reg & (~_DATA_TXDIR)); /* Set the direction as Write */
    }
#endif /* __GLEN */

#ifndef __GLEN
    W16_TRANSMODE(uiSlot, reg);
    msgi("Transfer mode reg updated: 0x%04x", R16_TRANSMODE(uiSlot));
#endif /* __GLEN */

    W16_BLKCNT(uiSlot, cnt); /* write into the register */

    return _HC_STS_OK;
}

/**
 * @brief This gets the SD bus widths
 *
 * @param[in] uiSlot slot number
 * @param[in] mode Different values of the width of the SD bus
 *
 * @retval Bus widths (1/4/8 bit width)
 */
com_busWidth_e hc_getBusWidth(_ub32 uiSlot)
{
    volatile _ub8 reg = 0;
    _ub8 tempext = 0;
    _ub8 tempdat = 0;

    /* Input arguments are not verified as it will be done by upper layer */

    msgi("ENTRY: slot number [%d]", uiSlot);

    /* Read the Host control 1 register */
    reg = R8_HOST_CTRL1(uiSlot);
    msgi("Host control 1 reg: %x", reg);

    tempext = ((reg & _EDATA_TXWIDTH) >> 5);
    tempdat = ((reg & _DATA_TXWIDTH) >> 1);

    if(1 == tempext)
    {
        /* Extended data width bit is set */
        return _COM_BWIDTH_8;
    }
    else
    {
        if(1 == tempdat)
        {
            /* Extended data width bit is zero and data width bit is one */
            return _COM_BWIDTH_4;
        }
        else
        {
            /* Extended data width bit and data width bit both are zero */
            return _COM_BWIDTH_1;
        }
    }

}

/**
 * @brief This sets the SD bus widths.
 *
 * @param[in] uiSlot slot number
 * @param[in] mode Different values of the width of the SD bus
 *
 * @retval _HC_STS_OK Host controller config is successful
 * @retval _HC_STS_ERR Wrong values read/written from/to the register
 * @retval _HC_STS_NOTSUPPORTED unsupported feature is being set
 */
hc_sts_e hc_setBusWidth(_ub32 uiSlot, com_busWidth_e width)
{
    volatile _ub8 reg = 0;

    /* Input arguments are not verified as it will be done by upper layer */

    msgi("ENTRY: width: %d", width);

    /* Disable the card interrupt to mask the incorrect interrupts */
    hc_disableIntr(uiSlot, _CARD_INT);

    reg = R8_HOST_CTRL1(uiSlot);
    msgi("Host control 1 reg initial : 0x%02x", reg);
    /* set data transfer width in host control 1 register */
    if(_COM_BWIDTH_1 == width)
    {
        reg = (reg & (~_EDATA_TXWIDTH));/* mask if previously 8bit width */
        reg = (reg & (~_DATA_TXWIDTH));/* Data Tx width=0 for 1 bit */
    }
    else if(_COM_BWIDTH_4 == width)
    {
        reg = (reg & (~_EDATA_TXWIDTH));/* mask if previously 8bit width */
        reg = (reg | (_DATA_TXWIDTH));/* Data Tx width=1 for 4 bit */
    }
    else
    {
        if(1 == hc_cap_val[uiSlot].ucEDev8)
        {
            /* Extended Data Tx width=1 for 8bit */
            reg = (reg | (_EDATA_TXWIDTH));
        }
        else
        {
            msgc("8 bit bus width is not supported");

#ifndef __GLEN
            hc_enableIntr(uiSlot, _CARD_INT);
#endif /* __GLEN */
            return _HC_STS_NOTSUPPORTED;
        }
    }

    /* Write the required value into Host control 1 register */
    W8_HOST_CTRL1(uiSlot, reg);
    msgi("Host control 1 reg updated: 0x%02x", R8_HOST_CTRL1(uiSlot));

#ifndef __GLEN
    /* Enable the card interrupt */
    hc_enableIntr(uiSlot, _CARD_INT);
#endif /* __GLEN */

    return _HC_STS_OK;
}

/**
 * @brief This sets the values for bus voltage and bus power.
 *
 * @param[in] uiSlot slot number
 * @param[in] voltValue Different values of the voltage in unit volt
 *
 * @retval _HC_STS_OK Host controller config is successful
 * @retval _HC_STS_ERR Wrong values read/written from/to the register
 * @retval _HC_STS_NOTSUPPORTED unsupported feature is being set
 */
hc_sts_e hc_setBusPwr(_ub32 uiSlot, com_volt_e voltValue)
{
    hc_sts_e hc_status = _HC_STS_OK;
    volatile _ub8 reg = 0;
    volatile _ub16 reg2 = 0;

    /* Input arguments are not verified as it will be done by upper layer */

    msgi("ENTRY: slot number [%d]", uiSlot);

    reg= R8_PWR_CTRL(uiSlot);

    reg2 = R16_HOST_CTRL2(uiSlot);

    msgi("Power control reg initial: 0x%02x", reg);
    msgi("Host control 2 reg initial: 0x%04x", reg2);

    switch(voltValue)
    {
        case _COM_VOLT3_3:
            /* Read capabilities Register structure value for confirmation */
            if (1 == hc_cap_val[uiSlot].ucV3_3)
            {
                /* clear the previous voltage value */
                reg = (reg & (~_VBITS));

                /* set the voltage value to 3.3V */
                reg = (reg | _VOLT33);

                /* Enable the bus power */
                reg = (reg | _SDBUS_PWR);

                /* Disable the 1.8V signalling bit */
                reg2 = (reg2 & (~_18V_SIGEN));
            }
            else
            {
                msgc("3.3V voltage value is not supported");
                hc_status = _HC_STS_NOTSUPPORTED;
            }
        break;

        case _COM_VOLT3_0:
            /* Read capabilities Register structure value for confirmation */
            if (1 == hc_cap_val[uiSlot].ucV3_0)
            {
                /* clear the previous voltage value */
                reg = (reg & (~_VBITS));

                /* set the voltage value to 3.0V */
                reg = (reg | _VOLT30);

                /* Enable the bus power */
                reg = (reg | _SDBUS_PWR);

                /* Disable the 1.8V signalling bit */
                reg2 = (reg2 & (~_18V_SIGEN));
            }
            else
            {
                msgc("3.0V voltage value is not supported");
                hc_status = _HC_STS_NOTSUPPORTED;
            }
        break;

        case _COM_VOLT1_8:
            /* Read capabilities Register structure value for confirmation */
            if (1 == hc_cap_val[uiSlot].ucV1_8)
            {
                /* clear the previous voltage value */
                reg = (reg & (~_VBITS));

                /* set the voltage value to 3.0V */
                reg = (reg | _VOLT18);

                /* Enable the bus power */
                reg = (reg | _SDBUS_PWR);

                /* Enable the 1.8V signalling bit */
                reg2 = (reg2 | _18V_SIGEN);
            }
            else
            {
                msgc("1.8V voltage value is not supported");
                hc_status = _HC_STS_NOTSUPPORTED;
            }
        break;

        default: /* do nothing [control doesn't come here] */
        break;
    }

    /* Update the power control register */
    W8_PWR_CTRL(uiSlot, reg);

    /* Update the Host Control2 register */
    W16_HOST_CTRL2(uiSlot, reg2);

    /* Prints for verification */
    msgi("Power control reg updated: 0x%02x", R8_PWR_CTRL(uiSlot));
    msgi("Host control 2 reg updated: 0x%04x", R16_HOST_CTRL2(uiSlot));

    return hc_status;
}

/**
 * @brief This gives the information of the mode of data transfer selected.
 *
 * @param[in] uiSlot slot number
 *
 * @retval _HC_MODE_SDMA SDMA mode of operation is selected
 * @retval _HC_MODE_ADMA ADMA mode of operation is selected
 * @retval _HC_MODE_PIO PIO mode of operation is selected
 * @retval _HC_MODE_RSV some reserved mode of operation is selected
 */
com_modes_e hc_getOpMode(_ub32 uiSlot)
{
    volatile _ub16 reg1 = 0;
    volatile _ub8 reg2 = 0;

    /* Input arguments are not verified as it will be done by upper layer */

    msgi("ENTRY: slot number [%d]", uiSlot);
#ifndef __GLEN
    /* Read the transfer mode reg to know DMA is enabled or not */
    reg1 = R16_TRANSMODE(uiSlot);
#endif /* __GLEN */

    msgi("Transfer mode reg: 0x%04x", reg1);

    /* Check if DMA is enabled or not */
#ifdef __GLEN
    if(1 == (hc_transVal[uiSlot].ucDMAEn & 0x01))
#else /* !__GLEN */
    if(1 == (reg1 & _DMAEN))
#endif /* __GLEN */
    {
        /* Read the host control 1 reg to know the type of DMA enabled */
        reg2 = R8_HOST_CTRL1(uiSlot);
        msgi("Host control 1 reg: 0x%02x", reg2);

        reg2 = ((reg2 & _DMA_SEL) >> 3);

        if(0x00 == reg2)
        {
        /* The present mode is set to be SDMA */
            return _COM_MODE_SDMA;
        }
        else if(0x02 == reg2)
        {
        /* The present mode is set to be ADMA2 */
            return _COM_MODE_ADMA2;
        }
        else
        {
            return _COM_MODE_RSV;
        }
    }

    return _COM_MODE_PIO;
}

/**
 * @brief This sets the mode of operation for data transaction.
 *
 * @param[in] uiSlot slot number
 * @param[in] mode different modes possible for the Data transaction
 *
 * @retval _HC_STS_OK Host controller config is successful
 * @retval _HC_STS_ERR Wrong values read/written from/to the register
 * @retval _HC_STS_NOTSUPPORTED unsupported feature is being set
 */
hc_sts_e hc_setOpMode(_ub32 uiSlot, com_modes_e mode)
{
    hc_sts_e hc_status = _HC_STS_OK;
#ifndef __GLEN
    volatile _ub16 reg1 = 0;
#endif /* __GLEN */
    volatile _ub8 reg2 = 0;

    /* Input arguments are not verified as it will be done by upper layer */

    msgi("ENTRY: Mode to be set %d", mode);

#ifndef __GLEN
    /* Read the transfer mode register to access DMA enable bit */
    reg1 = R16_TRANSMODE(uiSlot);
    msgi("Transfer mode reg : 0x%04x", reg1);
#endif /* __GLEN */

    /* Read Host Control 1 register to set SDMA/ADMA bits */
    reg2 = R8_HOST_CTRL1(uiSlot);
    msgi("Host control 1 reg : 0x%02x", reg2);

    switch(mode)
    {
        case _COM_MODE_PIO:
#ifdef __GLEN
            /* DMA enable bit is reset (Disable DMA) */
            hc_transVal[uiSlot].ucDMAEn = 0x00;
            /* Enable the Block count bit */
            hc_transVal[uiSlot].ucBlkCntEn = 0x01;
#else /* !__GLEN */
            /* DMA enable bit is reset (Disable DMA) */
            reg1 = (reg1 & (~_DMAEN));
#endif /* __GLEN */
        break;

        case _COM_MODE_SDMA:
            /* check if SDMA is supported and enable the related bits */
            if(1 == hc_cap_val[uiSlot].ucSDMA)
            {
#ifdef __GLEN
                /* Enable DMA in transfer mode reg*/
                hc_transVal[uiSlot].ucDMAEn = 0x01;
                /* Enable the Block count bit */
                hc_transVal[uiSlot].ucBlkCntEn = 0x01;
#else /* !__GLEN */
                /* Enable DMA in transfer mode reg*/
                reg1 = (reg1 | (_DMAEN));
#endif /* __GLEN */

                /* clear the previous mode set in host control 1 reg*/
                reg2 = (reg2 & (~_DMA_SEL));

                /* Specify DMA type as SDMA */
                reg2 = (reg2 | (_DMA_SDMA));
            }
            else
            {
                msgc("SDMA is not supported(capability register)");
                hc_status = _HC_STS_NOTSUPPORTED;
            }
            break;

        case _COM_MODE_ADMA2:
            /* check if ADMA2 is supported and enable the related bits */
            if(1 == hc_cap_val[uiSlot].ucADMA2)
            {
                /*
                 * In this driver, block count is always disabled for ADMA mode
                 * of operation. Thus disable the block count bit in
                 * transfer mode register
                 */
#ifdef __GLEN
                hc_transVal[uiSlot].ucBlkCntEn = 0x00;
                /* Enable DMA in transfer mode reg*/
                hc_transVal[uiSlot].ucDMAEn = 0x01;
#else /* !__GLEN */
                reg1 = (reg1 & (~_BLKCNT_EN));
                /* Enable DMA in transfer mode reg*/
                reg1 = reg1 | (_DMAEN);
#endif /* __GLEN */

                /* clear the previous mode set in host control 1 reg*/
                reg2 = (reg2 & (~_DMA_SEL));

                /* Specify DMA type as ADMA */
                reg2 = reg2 | (_DMA_ADMA);
            }
            else
            {
                msgc("ADMA is not supported(capability register)");
                hc_status = _HC_STS_NOTSUPPORTED;
            }
        break;

        default:
            msgc("Some reserved mode selected");
            hc_status = _HC_STS_ERR;
        break;
    }

    /* Set the bits to specify DMA type = SDMA or ADMA2 */
    W8_HOST_CTRL1(uiSlot, reg2);
    msgi("Host control 1 reg updated: 0x%02x", R8_HOST_CTRL1(uiSlot));

#ifndef __GLEN
    /* Set the bit to enble or disable DMA */
    W16_TRANSMODE(uiSlot, reg1);
    msgi("Transfer mode reg updated: 0x%04x", R16_TRANSMODE(uiSlot));
#endif /* __GLEN */

    return hc_status;
}

/**
 * @brief This enables all the normal interrupts depending on the
 * input mask value.
 *
 * NOTE: This function will retain the previous interrupts enabled.
 *
 * @param[in] uiSlot slot number
 * @param[in] uiMaskVal all the normal interrupt bits (ORed together)
 * to be enabled.
 *
 * @retval NONE
 */
void hc_enableIntr(_ub32 uiSlot, _ub16 uiMaskVal)
{
    volatile _ub16 reg = 0;

    /* Input arguments are not verified as it will be done by upper layer */

    msgi("ENTRY: slot number [%d]", uiSlot);

    /* Read the Normal interrupt status enable register */
    reg = R16_NORMINT_STSEN(uiSlot);
    msgi("Normal intr status enable reg initial: 0x%04x", reg);

    /* Write 1 to the interrupt bits to be enabled */
    reg = (reg | uiMaskVal);
    W16_NORMINT_STSEN(uiSlot, reg);

    /* Read the Normal interrupt signal enable register */
    reg = R16_NORMINT_SIGEN(uiSlot);
    msgi("Normal intr signal enable reg initial: 0x%04x", reg);

    /* Write 1 to the interrupt bits to be enabled */
    reg = (reg | uiMaskVal);

    W16_NORMINT_SIGEN(uiSlot, reg);

    /* prints for verification */
    msgi("Normal intr status enable reg updated:0x%04x"\
        , R16_NORMINT_STSEN(uiSlot));

    msgi("Normal intr signal enable reg updated :0x%04x"\
        , R16_NORMINT_SIGEN(uiSlot));
}

/**
 * @brief This disables all the normal interrupts depending on the
 * input mask value.
 *
 * @param[in] uiSlot slot number
 * @param[in] uiMaskVal all the normal interrupt bits (ORed together)
 * to be disabled.
 *
 * @retval NONE
 */
void hc_disableIntr(_ub32 uiSlot, _ub16 uiMaskVal)
{
    volatile _ub16 reg = 0;

    /* Input arguments are not verified as it will be done by upper layer */

    msgi("ENTRY: slot number [%d]", uiSlot);

    /* Read the Normal interrupt signal enable register */
    reg = R16_NORMINT_SIGEN(uiSlot);
    msgi("Normal intr signal enable reg initial: 0x%04x", reg);

    /* Write 0 to all the interrupt bits to be masked */
    reg = (reg &(~uiMaskVal));
    W16_NORMINT_SIGEN(uiSlot, reg);

    /* Read the Normal interrupt status enable register */
    reg = R16_NORMINT_STSEN(uiSlot);
    msgi("Normal intr status enable reg initial: 0x%04x", reg);

    /* Write 0 to all the interrupt bits to be masked */
    reg = (reg &(~uiMaskVal));
    W16_NORMINT_STSEN(uiSlot, reg);

    /* prints for verification */
    msgi("Normal intr status enable reg updated:0x%04x"\
        , R16_NORMINT_STSEN(uiSlot));

    msgi("Normal intr signal enable reg updated :0x%04x"\
        , R16_NORMINT_SIGEN(uiSlot));
}

/**
 * @brief This enables all the error interrupts depending on the
 * input mask value.
 *
 * NOTE: This function will retain the previous interrupts enabled.
 *
 * @param[in] uiSlot slot number
 * @param[in] uiMaskVal all the error interrupt bits (ORed together)
 * to be enabled.
 *
 * @retval NONE
 */
void hc_enableErrIntr(_ub32 uiSlot, _ub16 uiMaskVal)
{
    volatile _ub16 reg = 0;

    /* Input arguments are not verified as it will be done by upper layer */

    msgi("ENTRY: slot number [%d]", uiSlot);

    /* Read the Error interrupt status enable register */
    reg = R16_ERRINT_STSEN(uiSlot);
    msgi("Error intr status enable reg initial: 0x%04x", reg);

    /* Write 1 to the interrupt bits to be enabled */
    reg= (reg | uiMaskVal);
    W16_ERRINT_STSEN(uiSlot, uiMaskVal);

    /* Read the Error interrupt signal enable register */
    reg = R16_ERRINT_SIGEN(uiSlot);
    msgi("Error intr signal enable reg initial: 0x%04x", reg);

    /* Write 1 to the interrupt bits to be enabled */
    reg = (reg | uiMaskVal);

    W16_ERRINT_SIGEN(uiSlot, reg);

    /* prints for verification */
    msgi("Error intr status enable reg updated:0x%04x"\
        , R16_ERRINT_STSEN(uiSlot));

    msgi("Error intr signal enable reg updated :0x%04x"\
        , R16_ERRINT_SIGEN(uiSlot));
}

/**
 * @brief This disables all the error interrupts depending on the
 * input mask value.
 *
 * @param[in] uiSlot slot number
 * @param[in] uiMaskVal all the error interrupt bits (ORed together)
 * to be disabled.
 *
 * @retval NONE
 */
void hc_disableErrIntr(_ub32 uiSlot, _ub16 uiMaskVal)
{
    volatile _ub16 reg = 0;

    /* Input arguments are not verified as it will be done by upper layer */

    msgi("ENTRY: slot number [%d]", uiSlot);

    /* Read the Error interrupt signal enable register */
    reg = R16_ERRINT_SIGEN(uiSlot);
    msgi("Error intr signal enable reg initial: 0x%04x", reg);

    /* Write 0 to all the interrupt bits to be masked */
    reg = (reg & (~uiMaskVal));
    W16_ERRINT_SIGEN(uiSlot, reg);

    /* Read the Error interrupt status enable register */
    reg = R16_ERRINT_STSEN(uiSlot);
    msgi("Error intr status enable reg initial: 0x%04x", reg);

    /* Write 0 to all the interrupt bits to be masked */
    reg = (reg &(~uiMaskVal));
    W16_ERRINT_STSEN(uiSlot, reg);

    /* prints for verification */
    msgi("Error intr status enable reg updated:0x%04x"\
        , R16_ERRINT_STSEN(uiSlot));

    msgi("Error intr signal enable reg updated :0x%04x"\
        , R16_ERRINT_SIGEN(uiSlot));
}

/**
 * @brief This gets the Error interrupt status at present.
 *
 * @param[in] uiSlot slot number.
 *
 * @retval Error interrupt status register value
 */
_ub16 hc_getErrIntrSts(_ub32 uiSlot)
{
    /* Input arguments are not verified as it will be done by upper layer */
   /* Read Error Interrupt status register */
    return (R16_ERRINT_STS(uiSlot));
}

/**
 * @brief This gets the normal interrupt status at present.
 *
 * @param[in] uiSlot slot number.
 *
 * @retval Normal interrupt status register value
 */
_ub16 hc_getIntrSts(_ub32 uiSlot)
{
    /* Input arguments are not verified as it will be done by upper layer */
    /* Read Normal Interrupt Status register */
    return (R16_NORMINT_STS(uiSlot));
}

/**
 * @brief This gets the Error interrupt signals enabled at present.
 *
 * @param[in] uiSlot slot number.
 *
 * @retval Error interrupt signal enable register value
 */
_ub16 hc_getErrIntrMask(_ub32 uiSlot)
{
    /* Input arguments are not verified as it will be done by upper layer */
    /* Read Error Interrupt signal enable register */
    return (R16_ERRINT_SIGEN(uiSlot));
}

/**
 * @brief This gets the normal interrupt signals enabled at present.
 *
 * @param[in] uiSlot slot number.
 *
 * @retval Normal interrupt signal enable register value
 */
_ub16 hc_getIntrMask(_ub32 uiSlot)
{
    /* Input arguments are not verified as it will be done by upper layer */
    /* Read Normal Interrupt signal enable register */
    return(R16_NORMINT_SIGEN(uiSlot));
}
/***************************!!!! Newly Defined APIs !!!!**********************/
/**
 * @brief This gets the slot interrupt status register value
 *
 * @param[in] uiSlot slot number
 *
 * @retval NONE
 */
void hc_dumpReg(_ub32 uiSlot)
{
    msgc("\n\n\n***** HC REGISTER DUMP for slot %d ****\n",uiSlot);
    msgc("    SDMA_SYS_ADDR: 0x%08x   | BLOCK SIZE: %d Bytes\n",\
                R32_SDMA_ADR(uiSlot), R16_BLKSIZE(uiSlot));
    msgc("    BLOCK COUNT: %04d     | ARGUMENT : 0x%08x\n",\
                R16_BLKCNT(uiSlot), R32_ARG1(uiSlot));
    msgc("    TRANSFER MODE: 0x%04x      | COMMAND : 0x%04x\n",\
                R16_TRANSMODE(uiSlot), R16_CMD(uiSlot));
    msgc("    RESP1 | RESP0 : 0x%08x\n", R32_RESP01(uiSlot));
    msgc("    RESP3 | RESP2 : 0x%08x\n", R32_RESP23(uiSlot));
    msgc("    RESP5 | RESP4 : 0x%08x\n", R32_RESP45(uiSlot));
    msgc("    RESP7 | RESP6 : 0x%08x\n", R32_RESP67(uiSlot));
    msgc("    PRES_STATE: 0x%08x    | HOST CTRL1 : 0x%02x\n",
                R32_PRESENT_STS(uiSlot), R8_HOST_CTRL1(uiSlot));
    msgc("    HOST CTRL2: 0x%04x\n", R16_HOST_CTRL2(uiSlot));
    msgc("    POWER CTRL: 0x%02x    | BLOCKGAP : 0x%02x\n",\
                R8_PWR_CTRL(uiSlot), R8_BLOCKGAP_CTRL(uiSlot));
    msgc("    WAKEUP: 0x%02x       | CLOCK CTRL : 0x%04x\n",\
                R8_WAKEUP_CTRL(uiSlot), R16_CLK_CTRL(uiSlot));
    msgc("    TIMEOUT: 0x%02x      | NORM INT STS : 0x%04x\n",\
                R8_TIMEOUT_CTRL(uiSlot), R16_NORMINT_STS(uiSlot));
    msgc("    ERR INT STS : 0x%04x\n", R16_ERRINT_STS(uiSlot));
    msgc("    NOR_INTR_STS_EN: 0x%04x | ERR_INTR_STS_EN : 0x%04x\n",\
                R16_NORMINT_STSEN(uiSlot), R16_ERRINT_STSEN(uiSlot));
    msgc("    NOR_INTR_SIGEN: 0x%04x  | ERR_INTR_SIGEN : 0x%04x\n",\
                R16_NORMINT_SIGEN(uiSlot), R16_ERRINT_SIGEN(uiSlot));
    msgc("    ACMD12 error: 0x%04x  | CAPABILITIES1 : 0x%08x\n", \
                R16_ACMD_ERRSTS(uiSlot), R32_CAPABLITY1(uiSlot));
    msgc("    CAPABILITIES2 : 0x%08x  | MAX CUR CAP : 0x%08x\n", \
                R32_CAPABLITY2(uiSlot), R32_MAXCUR_CAP(uiSlot));
    msgc("    SLOT INTR STS: 0x%04x | SD HOST VER : 0x%04x\n",\
                R16_SLOT_INTSTS(uiSlot), R16_CTRLR_VER(uiSlot));
    msgc("    SOFTWARE RST 0x%02x\n", R8_SOFTWARE_RST(uiSlot));
    msgc("    ADMA ERR STS 0x%04x\n", R8_ADMA_ERR(uiSlot));
    msgc("    FORCE EVENT CMD STS 0x%04x\n", R16_FRCEVT_ACMD(uiSlot));
    msgc("    FORCE EVENT ERRSTS 0x%04x\n", R16_FRCEVT_ERRINT(uiSlot));
    msgc("    ADMA SYS ADD1 0x%08x\n", R32_ADMASTART1(uiSlot));
    msgc("    ADMA SYS ADD1 is 0x%08x\n", R32_ADMASTART2(uiSlot));
    msgc("    PRESET VAL1 0x%08x\n", R32_PRESETVAL1(uiSlot));
    msgc("    PRESET VAL2 0x%08x\n", R32_PRESETVAL2(uiSlot));
    msgc("    PRESET VAL3  0x%08x\n", R32_PRESETVAL3(uiSlot));
    msgc("    PRESET VAL4 0x%08x\n", R32_PRESETVAL4(uiSlot));
    msgc("    SHARED BUS CTRL 0x%08x\n", R32_SHRDBUS_CTRL(uiSlot));
    msgc("*****DUMPING REGISTERS FINISHED *****\n\n\n");
}

/**
 * @brief This gets the slot interrupt status register value
 *
 * @param[in] uiSlot slot number
 *
 * @retval slot interrupt status register value
 */
_ub16 hc_getSlotIntrSts(_ub32 uiSlot)
{
    /* return the value Read from slot interrupt status register */
    return (R16_SLOT_INTSTS(uiSlot));
}

/**
 * @brief This gets the buffer data port register value
 *
 * @param[in] uiSlot slot number
 *
 * @retval buffer data port register value
 */
_ub32 hc_getBufDatPort(_ub32 uiSlot)
{
    /* return the value Read from Buffer data port register */
    return (R32_BUF_DAT_PORT(uiSlot));
}

/**
 * @brief This sets the buffer data port register value
 *
 * @param[in] uiSlot slot number
 * @param[in] uiVal value to be written to the buffer data port register
 *
 * @retval NONE
 */
void hc_setBufDatPort(_ub32 uiSlot, _ub32 uiVal)
{
    W32_BUF_DAT_PRT(uiSlot, uiVal);
}

/**
 * @brief This gets the Device response form the response registers
 *
 * @param[in] uiSlot slot number
 *
 * @retval Response register value
 */
_ub32 hc_getResponse(_ub32 uiSlot, com_resp_e resp)
{
    _ub32 reg = 0;

    /* return the value Read from Present State register */
    switch (resp)
    {
        case _COM_RESP_01:
            reg = R32_RESP01(uiSlot);
            break;

        case _COM_RESP_23:
            reg = R32_RESP23(uiSlot);
            break;

        case _COM_RESP_45:
            reg = R32_RESP45(uiSlot);
            break;

        case _COM_RESP_67:
            reg = R32_RESP67(uiSlot);
            break;

        default:
            msgc("Invalid response argument to access");
    }

    return reg;
}

/**
 * @brief This gets the present state register value
 *
 * @param[in] uiSlot slot number
 *
 * @retval Present state register value
 */
_ub32 hc_getPresentState(_ub32 uiSlot)
{
    /* return the value Read from Present State register */
    return (R32_PRESENT_STS(uiSlot));
}

/**
 * @brief This clears the error bits set in the Error Interrupt status register.
 *
 * @param[in] uiSlot slot number
 * @param[in] usErrVal Mask to reset the required error bits.
 *
 * @retval NONE
 */
void hc_clrErrIntrSts(_ub32 uiSlot, _ub16 usErrVal)
{
    /* Clear the error bits */
    W16_ERRINT_STS(uiSlot, usErrVal);
}

/**
 * @brief This clears the bits set in the Normal Interrupt status register.
 *
 * @param[in] uiSlot slot number
 * @param[in] usIntrVal Mask to reset the required error bits.
 *
 * @retval NONE
 */
void hc_clrNormIntrSts(_ub32 uiSlot, _ub16 usIntrVal)
{
    /* Clear the Normal interrupt status bits */
    W16_NORMINT_STS(uiSlot, usIntrVal);
}

/**
 * @brief This will set the block size register with required value.
 *
 * @param[in] uiSlot slot number
 * @param[in] usBlkSize Block size value.
 *
 * @retval NONE
 */
void hc_setBlockSize(_ub32 uiSlot, _ub16 usBlkSize)
{
    /* Clear the Normal interrupt status bits */
    W16_BLKSIZE(uiSlot, usBlkSize);
}

/**
 * @brief This sets the required value into the argument and command register.
 *
 * @param[in] uiSlot slot number
 *
 * @retval NONE
 */
void hc_setCmdReg(_ub32 uiSlot, _ub16 usCmdVal, _ub32 uiCmdArg)
{
    /* Write to the Argument1 register */
    W32_ARG1(uiSlot, uiCmdArg);

    /* Write to the Command register. This will send command to the device. */
    W16_CMD(uiSlot, usCmdVal);
}

#ifdef __GLEN
/**
 * @brief This sets the value of argument, command and transfer mode register.
 *
 * @param[in] uiSlot slot number.
 * @param[in] usCmdVal command index to be set into command register
 *
 * @retval NONE
 */
void hc_setCmdTransReg(_ub32 uiSlot, _ub16 usCmdVal, _ub32 uiCmdArg)
{

    volatile _ub32 reg_val = 0;
    _ub16 reg = 0;

    /* Get the transfer mode register value */
    reg = getTransVal(uiSlot);

    /* Get the command register value */
    reg_val = (_ub32)usCmdVal;

    /* Shift the command register value to upper 16 bits */
    reg_val = (reg_val << 16);

    /*
     * Bit-wise OR the command register value
     * with the transfer mode register value
     */
    reg_val = reg_val | (_ub32)reg;

    /* Write to the Argument1 register */
    W32_ARG1(uiSlot, uiCmdArg);

    /* Write to the Command register. This will send command to the device. */
    W32_CMD_TRANS(uiSlot, reg_val);
}
/**
 * @brief This gets the value of transfer mode register bits set.
 *
 * @param[in] uiSlot slot number.
 *
 * @retval Transfer mode register value
 */
static _ub16 getTransVal(_ub32 uiSlot)
{
    _ub16 transvalue =0x0000;
    transVal_t *ptr = NULL;

    /* input argument is not validated */

    ptr = (transVal_t *)(&hc_transVal[uiSlot]);
    transvalue = (ptr->ucDMAEn & 0x01);
    transvalue |= ((_ub16)((ptr->ucBlkCntEn & 0x01) << 1));
    transvalue |= ((_ub16)((ptr->ucAutoCmdEn & 0x03) << 2));
    transvalue |= ((_ub16)((ptr->ucDatTxDir & 0x01) << 4));
    transvalue |= ((_ub16)((ptr->ucSingMultiBlk & 0x01) << 5));

    return transvalue;
}
#endif /* __GLEN */

/**
 * @brief This starts the clock for data transaction.
 *
 * @param[in] uiSlot slot number
 * @param[in] freq_val different frequency values for the clock in Hz
 *
 * @retval _HC_STS_OK Host controller config is successful
 * @retval _HC_STS_ERR Wrong values read/written from/to the register
 * @retval _HC_STS_TIMEOUT Host controller config timed out
 */
static hc_sts_e startClock(_ub32 uiSlot, _ub32 uiFreq)
{
    volatile _ub32 regclk = 0;
    volatile _ub8 reghost1 = 0;
    volatile _ub16 reghost2 = 0;
    _ub32 baseclk = 0;
    _ub32 tempclk = 0;
    _ub32 divisor = 0;
    _ub32 retrycnt = 0;

    /* Input arguments are not verified as it will be done by upper layer */

    msgi("ENTRY: slot number [%d]", uiSlot);

    /* Read capabilities Register structure value */
    baseclk = (_ub32)hc_cap_val[uiSlot].ucBaseClkFreq;
    msgi("Base clock frequency: %u", baseclk);

    /**
     * The user can input any frequency value in unit Hz
     * The register gives us the value in MHz
     * example: if register reads 200, then it means 200 MHz
     * Thus, multiply it with 1000* 1000 = 1000000 to convert it in terms of Hz
     * 200MHz --> 200 *1000000 = 200000000 Hz
     */
    baseclk = baseclk * 1000000;
    tempclk = baseclk;

    msgi("base_clk in HZ: %u", baseclk);

    if (_MAX_FREQ < uiFreq)
    {
        msgc("clock_supply: input freq greater than 50MHz..!!");
        return _HC_STS_ERR;
    }

    if(0 == baseclk)
    {
        msgc("clock_supply: Base clock = 0..!!");
        return _HC_STS_ERR;
    }

    while(tempclk > uiFreq)
    {
        divisor++;
        tempclk= (baseclk/(2*divisor));
        /* msgi("base_clk in while: %d",base_clk); */
        /* msgi("tempclk in while: %d",tempclk); */
    }

    msgi("Divisor after while loop: %u", divisor);

    /* Read clock control register to set the divisor value */
     regclk = (_ub32)R16_CLK_CTRL(uiSlot);
    msgi("Clock control register initial: 0x%04x", regclk);

    /* Clear the initial freq divisor values */
    regclk = (regclk & (_ub32)(~_SDCLK_FREQSEL));
    regclk = (regclk & (_ub32)(~_UBSDCLK_FREQSEL));

    /* set new divisor value initial 8 bits(SDClkFreqSelect : 08-15 bits) */
    regclk = (regclk | ((divisor & 0x00FF)<<8));
    /* set new divisor value 9th and 10th bits(SDClkFreqSelect : 06-07 bits) */
    regclk = (regclk | ((divisor & 0x0300) >> 2));

    /* Read the host control 1 register to enable high speed bit */
    reghost1= R8_HOST_CTRL1(uiSlot);
    msgi("Host control 1 reg initial: 0x%02x", reghost1);

    if(uiFreq <= _25MHZ) /* if frequency is 25MHZ or lesser */
    {
        reghost1 = (reghost1 & (~_HSPEED_EN));
    }
    else
    {
        reghost1 = (reghost1 | _HSPEED_EN);
    }

    /* write into host control 1 register, the updated value */
    W8_HOST_CTRL1(uiSlot, reghost1);

    /*
     * Select the UHS mode bits and Driver strength accordingly
     * in Host control 2 register. Read the Host control 2 register.
     */
    reghost2 = R16_HOST_CTRL2(uiSlot);

    /* Check if 1.8V signalling is enabled */
    if(_18V_SIGEN == (reghost2 & _18V_SIGEN))
    {
        msgi("1.8V signalling is enabled");

        /* Reset the preset value enable bit */
        reghost2 = (reghost2 & (~_PRESET_VAL_EN));

        /* Check for the input frequency values and update the UHS bits */
        if(uiFreq <= _12MHZ)
        {
            /* Clear the initial UHS value set*/
            reghost2 = (reghost2 & (~_UHS_MODE_SEL));

            /* Set the UHS bits for freq less than or equal to 12MHz */
            reghost2 = (reghost2 | _UHS_SDR12);
        }
        else if(uiFreq <= _25MHZ)
        {
            /* Clear the initial UHS value set*/
            reghost2 = (reghost2 & (~_UHS_MODE_SEL));

            /* Set the UHS bits for freq less than or equal to 25MHz */
            reghost2 = (reghost2 | _UHS_SDR25);
        }
        else if((uiFreq <= _50MHZ))
        {
            /* Clear the initial UHS value set*/
            reghost2 = (reghost2 & (~_UHS_MODE_SEL));

            /* Set the UHS bits for freq less than or equal to 50MHz */
            reghost2 = (reghost2 | _UHS_SDR50);
        }
        else if(uiFreq <= _104MHZ)
        {
            /* Clear the initial UHS value set*/
            reghost2 = (reghost2 & (~_UHS_MODE_SEL));

            /* Set the UHS bits for freq less than or equal to 104MHz */
            reghost2 = (reghost2 | _UHS_SDR104);
        }
        else
        {
            /* Clear the initial UHS value set*/
            reghost2 = (reghost2 & (~_UHS_MODE_SEL));

            /* Set the UHS bits for freq less than or equal to 200MHz */
            reghost2 = (reghost2 | _UHS_SDR200);
        }

        /*
         * Driver strength should also be set in Host control 2 register.
         * It should be explored more and for prototype now, the default
         * Driver Type B is Selected.
         */

        /* Update the Host control 2 register with proper values */
         W16_HOST_CTRL2(uiSlot, reghost2);
     }

    /* Enableinternalclock(IntClkEnable) */
    regclk = (regclk | _INTCLK_EN);
    W16_CLK_CTRL(uiSlot, (_ub16)regclk);

    /**
     * Read Int Clk Stable in Clk Control register and wait till it is SET
     * Or check till LoopCount becomes 10
     */
    while(retrycnt < _RETRYCNT)
    {
        regclk = (_ub32)R16_CLK_CTRL(uiSlot);
        /* Discard all other bitfields except Internal Clock Stable: bit[1] */
        if (_INTCLK_STABLE == (regclk & (_ub32)_INTCLK_STABLE))
        {
            break;
        }

        os_delayUs(10); /* Trial and error value */
        retrycnt++;
    }
    if (_RETRYCNT == retrycnt)
    {
        msgc("timeout error occurred");
        return _HC_STS_TIMEOUT;
    }

    /* EnableSDclock: SDClkEnable bit */
    regclk = (_ub32)R16_CLK_CTRL(uiSlot);
    regclk = (regclk | (_ub32)_SDCLK_EN);
    W16_CLK_CTRL(uiSlot, (_ub16)regclk);

    msgi("Clock control reg updated: 0x%04x", R16_CLK_CTRL(uiSlot));
    msgi("Host control 1 reg updated: 0x%02x", R8_HOST_CTRL1(uiSlot));

    return _HC_STS_OK;
}

/**
 * @brief This stops the clock for data transaction.
 *
 * @param[in] uiSlot slot number
 *
 * @retval NONE
 */
static void stopClock(_ub32 uiSlot)
{
    volatile _ub16 reg = 0;

    /* Input arguments are not verified as it will be done by upper layer */

    msgi("ENTRY: slot number [%d]", uiSlot);

    /* Read the clock control register */
    reg = R16_CLK_CTRL(uiSlot);
    msgi("Clock control reg initial: 0x%04x", reg);

    /* write 0 to SD clk and internal clk enable bits in clock control reg */
    reg = (reg & (~_SDCLK_EN));
    reg = (reg & (~_INTCLK_EN));
    W16_CLK_CTRL(uiSlot, reg);

    msgi("Clock control reg updated: 0x%04x", R16_CLK_CTRL(uiSlot));
}

/**
 * @brief This verifies whether the card is inserted already or not.
 *
 * @param[in] uiSlot slot number
 *
 * @retval value 1 or 0 indicating card present or not present respectively
 */
static inline _ub32 checkCardInserted(_ub32 uiSlot)
{
    return ((R32_PRESENT_STS(uiSlot) & _CARD_INSERTED) >> 16);
 }
/*------------------------Host Controller Initialiasation--------------------*/
/**
 * @brief Initializes the Host controller with all the default values.
 *
 * @param[out] pValidSlot pointer to an array of slots (valid or invalid)
 *
 * @retval _HC_STS_OK Host controller config is successful
 * @retval _HC_STS_ERR Wrong values read/written from/to the register
 * @retval _HC_STS_TIMEOUT Host controller config timed out
 */
hc_sts_e hc_init(_ub32 *pValidSlot)
{
    hc_sts_e hc_status = _HC_STS_OK;

    /* Default values */
    com_swRst_e resetline = _COM_RST_ALL; /* Rest all lines */
    com_volt_e voltval = _COM_VOLT1_8; /* Default voltage of 1.8V */
    _ub32 intrmask = _ALL_INTR; /* Enable all the normal interrupts */
    _ub32 errintrmask = _ALLERR_INTR; /* Enable all the error interrupts */
    _ub32 freq = 400000; /* Initial clock should be set to 400KHZ */
    _ub32 Scnt = 0;
    _ub32 cardinsert = 0;
    _ub32 badSlot_cnt = 0;

#ifdef __GLEN
    if (machine_is_tz2000rb3())
        voltval = _COM_VOLT3_3; /* Default voltage of 3.3V */

#endif /* __GLEN */
    msgi("ENTRY");

    /* Argument Check */
    if(NULL == pValidSlot)
    {
        msgc("Slot array pointer is NULL");
        return _HC_STS_ERR;
    }

    /* Get the HC base address to access the registers*/
    hc_BaseAdr = os_getBase();

#ifdef __GLEN
    /* Clear the hc global structure */
    os_setMem(hc_transVal, 0, sizeof(hc_transVal));
#endif /* __GLEN */

    for(Scnt = 0; Scnt < _MAX_SLOTS; Scnt++)
    {
        /* Check if the card is inserted or not */
        cardinsert = checkCardInserted(Scnt);
        msgi("After check_card_Inserted");

        if(0 == cardinsert)
        {
            /* Card is not inserted for this particular slot */
            badSlot_cnt = badSlot_cnt + 1;
            continue;
        }

        /* Reset the Host Controller */
        hc_status = hc_reset(Scnt,resetline);
        msgi("After hc_software_reset");

        /* Check the status returned */
        if(_HC_STS_OK != hc_status)
        {
            /* Host controller couldnt be reset for this particular slot */
            badSlot_cnt = badSlot_cnt + 1;
            continue;
        }

        /* Get the capabilities of the Host Controller */
        hc_getCapabilities(Scnt,&hc_cap_val[Scnt]);
        msgi("After hc_get_capabilities");

        /* Set the HC bus power to dafault voltage: 1.8V */
        hc_status = hc_setBusPwr(Scnt,voltval);
        msgi("After hc_set_buspowercontrol");

        /* Check the status returned */
        if(_HC_STS_OK != hc_status)
        {
            /* Host controller bus power values could not be set properly */
            badSlot_cnt = badSlot_cnt + 1;
            continue;
        }

        /* Enable all the normal interrupts */
        hc_enableIntr(Scnt,intrmask);
        msgi("After hc_enable_interrupts");

        /* Enable all the error interrupts */
        hc_enableErrIntr(Scnt,errintrmask);
        msgi("After hc_enable_errinterrupts");

        /* Set the SD bus frequency to 400kHz */
        hc_status = hc_setFreq(Scnt,freq);
        msgi("After hc_set_frequency");

        /* Check the status returned */
        if(_HC_STS_OK != hc_status)
        {
            /* Host controller frequency could not be set properly */
            badSlot_cnt = badSlot_cnt + 1;
            continue;
        }

        /* Write block size to the register */
        W16_BLKSIZE(Scnt, _BLK_SIZE);

        /* Get the frequency value for cross verification */
        freq= hc_getFreq(Scnt);
        msgi("After hc_getFrequency %u", freq);

        /* Timeout value is set to 0xE maximum value possible */
        W8_TIMEOUT_CTRL(Scnt, 0xE);

        /*
         * card is present and Host controller is also set successfully
         * for this particular slot with all the required values. Thus set
         * the respective value of the array as Valid.
         */
        pValidSlot[Scnt] = _SLOT_VALID;

    }

    if (_MAX_SLOTS == badSlot_cnt)
    {
        /* Return Error if all the slots are not good */
        return _HC_STS_ERR;
    }
    else
    {
        return _HC_STS_OK;
    }
}

/**
 * @brief Disables all the interrupts and Resets all the device slots
 * of a Host controller.
 *
 * @param NONE
 *
 * @retval NONE
 */
void hc_exit(void)
{
    _ub16 Scnt = 0;

    /* Reset all the slots */
    for(Scnt = 0; Scnt < _MAX_SLOTS; Scnt++)
    {
        /* Disable all the normal interrupts */
        hc_disableIntr(Scnt, _ALL_INTR);

        /* Disable all the error interrupts */
        hc_disableErrIntr(Scnt, _ALLERR_INTR);

        /* Reset all the device slots */
        hc_reset(Scnt, _COM_RST_ALL);
    }
}

/**@}*/ // HC_Functions

/**@} *//* HCAPIs */
/**@} *//* HostController */

