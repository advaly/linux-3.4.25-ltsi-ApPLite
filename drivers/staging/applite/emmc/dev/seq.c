/**
 * @file          seq.c
 *
 * \brief         Source file of CMD sequence layer.
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
 * @addtogroup Sequence
 * @{
 */

/*----------------------- Header Files Inclusions ---------------------------*/
#include "os.h"       /* To use OS service APIs */
#include "ra.h"       /* To use register access macros */
#include "hc_api.h"   /* To use HC layer APIs */
#include "intr.h"     /* To use interrupt related APIs */
#include "com.h"      /* To use the common enums and macros */
#include "debug.h"    /* To use the debug zone prints */
#include "config.h"   /* To use vendor specific macros/enums */
#include "dev_com.h" /* Common header file for sequence & PM */

/*-------------------------- Macro Definitions ------------------------------*/

/** @addtogroup Seq_DEFINES Seq_DEFINES
 * @{
 */

/* Macros for buffer read/write ready checking */
#define IS_BUF_RD_READY(s) (hc_getPresentState(s) & 0x00000800) /* bit[11] */
#define IS_BUF_WR_READY(s) (hc_getPresentState(s) & 0x00000400) /* bit[10] */


/* Masks for device status fields */
#define _DEV_STS_E          0xFDF9A080U  /* Error bits' mask in device status */
#define _DEV_ERR_RMODE      0xF0D02000U  /* Resp mode error bits' mask */
#define _DEV_ERR_XMODE      0xCD298080U  /* Exec mode error bits' mask */
#define _DEV_ADDR_OUT       0x80000000U  /* Bit31 - Addr out of range */
#define _DEV_ADRMISALIGN    0x40000000U  /* Bit30 - Addr misaligned */
#define _DEV_BLKLEN_ERR     0x20000000U  /* Bit29 - Block length error */
#define _DEV_ERASESEQ_ERR   0x10000000U  /* Bit28 - Erase seq error */
#define _DEV_ERASEPAR_ERR   0x08000000U  /* Bit27 - Erase Param error */
#define _DEV_WP_VIOLATION   0x04000000U  /* Bit26 - Write Protect violation */
#define _DEV_LOCKED_ERROR   0x02000000U  /* Bit25 - Device is locked */
#define _DEV_LOCK_FAILED    0x01000000U  /* Bit24 - Device lock/unlock failed */
#define _DEV_COMCRC_ERR     0x00800000U  /* Bit23 - Command CRC error */
#define _DEV_ILLEGAL_CMD    0x00400000U  /* Bit22 - Illegal command */
#define _DEV_ECC_FAILED     0x00200000U  /* Bit21 - Device ECC failed */
#define _DEV_CC_ERROR       0x00100000U  /* Bit20 - Device undefined error */
#define _DEV_ERROR          0x00080000U  /* Bit19 - Dev error coz of host cmd */
#define _DEV_OVERWRITE      0x00010000U  /* Bit16 - CID/CSD overwrite error */
#define _DEV_WP_ERASESKIP   0x00008000U  /* Bit15 - Erase skip coz of WP */
#define _DEV_ERASE_RESET    0x00002000U  /* Bit13 - Erase reset error */
#define _DEV_STATE          0x00001E00U  /* Bits[12:9] - Current State*/
#define _DEV_READY_DATA     0x00000100U  /* Bit8 - Ready for Data */
#define _DEV_SWITCH_ERROR   0x00000080U  /* Bit7 - Device switch error */
#define _DEV_EXCEPTION_ERR  0x00000040U  /* Bit6 - Exception event */
#define _DEV_APPCMD         0x00000020U  /* Bit5 - Dev expect app-specific cmd*/

/* Macro to mark the end of a command sequence */
#define _CMD_END       0xFFFFU

/*
 * Retry count for CMD1.
 * This is done based on trial and error. During testing, we've seen that
 * up to 23 times retry is required for CMD1. Worst case is set as 100.
 */
#define _CMD1_RETRY_MAX     100

/* Retry count for command sending in case of error */
#define _ERR_RETRY_MAX      3

/* Retry count for device state checking - 5ms */
#define _STATE_RETRY_MAX    5000



/* Bit mask for OCR: Device Power up status bit[31] */
#define _POWER_UP_OK        0x80000000U

/* R2 response: Which register details to be stored */
#define _CID                1
#define _CSD                2

/* Used for CSD buffer seq_crcBuf */
#define _DEV_CSD_SIZ_BYTE (_COM_CSD_SIZE/4)

/* Mask values for CID Register fileld in R2 response register */
#define _MANUID_MASK            0x000000FFU /* Bits 119-112 in resp reg */
#define _DEVTYPE_MASK           0x00000300U /* Bits 105-104 in resp reg */
#define _OID_MASK               0x000000FFU /* Bits 103-96 in resp reg */

#define _PDTNAME_OFST0_MASK     0xFF000000U /* Bits 95-88 in resp reg */
#define _PDTNAME_OFST1_MASK     0x00FF0000U /* Bits 87-80 in resp reg */
#define _PDTNAME_OFST2_MASK     0x0000FF00U /* Bits 79-72 in resp reg */
#define _PDTNAME_OFST3_MASK     0x000000FFU /* Bits 71-64 in resp reg */

#define _PDTREV_MASK            0x0000FF00U /* Bits 47-40 in resp reg */
#define _PDTSINO_OFST1_MASK     0x000000FFU /* Bits 39-32 in resp reg */
#define _PDTSINO_OFST2_MASK     0xFFFFFF00U /* Bits 31-8 in resp reg */
#define _MANUDT_MASK            0x000000FFU /* Bits 7-0 in resp reg */

/*
 * No of bytes of Mode segment(device configuration) of EXT CSD register
 * Jedec JESD84-B45 spec Sect7.4
 */
#define _EXTCSD_NUMBYTES    192

/*
 * CMD6(SWITCH) argument values for bus-width & bus speed mode settings:
 *
 * Ref. Sect 6.6.1, 6.10.4, 7.4 of Jedec JESD84-B45 spec.
 *
 * Argument fields are as follows,
 * [25:24]Access: 0b11 to write Value to the specified byte EXT CSD
 * [23:16]Index : EXT CSD byte offset to write Value to.(0xB7 - Bus width,
 *                0xB9 for Bus speed setting)
 * [15:8]Value  : The value to be written to the specified byte of EXT CSD
 *                Bus width settings: 0x0 - 1-bit, 0x1 - 4-bit, 0x2 - 8bit
 *                Bus speed modes: 0x0 - Normal, 0x1 - HS, 0x2 - HS200
 * [2:0]Cmd Set : To be set to 0, while SWITCH is used to write to EXT CSD
 */
#define _BUS_WIDTH_1BIT     0x03B70000U  /* 1-bit Bus-width mode */
#define _BUS_WIDTH_4BIT     0x03B70100U  /* 4-bit Bus-width mode */
#define _BUS_WIDTH_8BIT     0x03B70200U  /* 8-bit Bus-width mode */

#define _BUS_SPEED_NORMAL   0x03B90000U  /* Normal bus-speed mode */
#define _BUS_SPEED_HIGH     0x03B90100U  /* High bus-speed mode */
#define _BUS_SPEED_HS200    0x03B90200U  /* HS200 bus-speed mode */


#define _CMD6_ACCS_MASK     0x03000000U  /* Mask for CMD6 arg, Access field */
#define _CMD6_OFST_MASK     0x00FF0000U  /* Mask for CMD6 arg, Index field */
#define _CMD6_VAL_MASK      0x0000FF00U  /* Mask for CMD6 arg, Value field */


/* Macros for device states */
#define _IDLE_STATE     0x00000001  /* Idle: [12:9] in devsts = 0 */
#define _READY_STATE    0x00000002  /* Ready: [12:9] in devsts = 1 */
#define _IDENT_STATE    0x00000004  /* Identification: [12:9] in devsts = 2 */
#define _STBY_STATE     0x00000008  /* Standby: [12:9] in devsts = 3 */
#define _TRANS_STATE    0x00000010  /* Transfer: [12:9] in devsts = 4 */
#define _SEND_STATE     0x00000020  /* Send data: [12:9] in devsts = 5 */
#define _RECV_STATE     0x00000040  /* Receive data: [12:9] in devsts = 6 */
#define _PROG_STATE     0x00000080  /* Programming: [12:9] in devsts = 7 */
#define _DISC_STATE     0x00000100  /* Disconnect: [12:9] in devsts = 8 */
#define _BTST_STATE     0x00000200  /* Bus Test: [12:9] in devsts = 9 */
#define _SLP_STATE      0x00000400  /* Sleep: [12:9] in devsts = 10 */

/**@}*/ // Seq_DEFINES

/*-------------------------- Enum Definitions -------------------------------*/

/*------------------ Data Structures & Custom Typedefs ----------------------*/

/** @addtogroup Seq_Enums Seq_Enums
 * @{
 */

/**
 * @brief Enum for Ext CSD field types
 */
typedef enum tag_extcsd_typ_e
{
    _R,      /**< Read only */
    _W,      /**< One Time Programmable & not readable */
    _RW,     /**< One Time Programmable & readable */
    _WE,     /**< Multiple write with val kept after any reset; not readable */
    _RWE,    /**< Multiple write with val kept after any reset and readable */
    _RWC_P,  /**< Writable after val cleared by pwr fail & HW reset; readable */
    _RWE_P,  /**< Multiple write with value reset after any reset & readable */
    _WE_P,   /**< Multiple write with val reset after any reset; not readable */
    _RSVD,   /**< Reserved field */
}extcsd_typ_e;

/**@}*/ //end of Seq_Enums

/** @defgroup Seq_Structures Seq_Structures
 * @{
 */

/**
 * @brief Struct to maintain command info of each command
 */
typedef struct tag_cmd_info_t
{
    resp_ctgy_e eRespCtgy;  /**< Response category */
    dat_usage_e eDatUsage;  /**< DAT line usage of command */
}cmd_info_t;

/**@}*/ // Seq_Structures


/*---------------------------- Prototypes -----------------------------------*/

/** @addtogroup Seq_Prototypes Seq_Prototypes
 * @{
 */

/* Function to execute all command sequences */
dev_sts_e executeSequence(_ub32 uiSlot, seq_id_e eSeqID);

/* Function to parse response data */
static dev_sts_e checkResponse(
    _ub32 uiSlot,
    cmd_index_e eIndex,
    _ub32 *puiRespData);

/* Function for R1 response parsing*/
static dev_sts_e parseR1Resp(cmd_index_e eIndex, _ub32 uiRespVal);

/* Function for R2 response parsing*/
static void parseR2Resp(
    _ub32 uiSlot,
    _ub32 *puiRespVal,
    _ub8 ucReg);

/* Function for R3 response parsing*/
static inline void parseR3Resp(
    _ub32 *puiRespVal,
    ocr_params_t *pOCRParams);

/* Intr handler func to read EXT CSD value from internal buffer */
static void readExtCSD(void *ptr);

/* Function to validate device state for a command */
static dev_sts_e checkDeviceState(
    _ub32 uiSlot,
    cmd_index_e eIndex);

#ifdef __DEVERR_HANDLING
/* Function for device error handling */
static void devErrHandling(_ub32 uiSlot);
#endif


/**@}*/ // Seq_Prototypes

#ifdef __CRC7

/* Function for calculating CRC7 - done on CSD contents*/
/** Currently unused */
static char crc7(unsigned char *buffer,int count);

#endif /* #ifdef __CRC7 */

/*------------- Data variable/Structure allocation (global) -----------------*/

/** @addtogroup Seq_Globals Seq_Globals
 * @{
 */

/* Struct variable to store OCR register details */
static ocr_params_t seq_tOCRParams[_MAX_SLOTS];

/* Struct variable to store CID register details */
static com_cid_params_t seq_tCIDParams[_MAX_SLOTS];

/* Struct variable to store CSD register details */
com_csd_params_t seq_tCSDParams[_MAX_SLOTS];

/* Struct variable to use in buffer ready intr handler to read EXTCSD value */
extcsdinfo_t seq_tEXTCSDInfo[_MAX_SLOTS];

/*
 * Table for retrieving params required to send commands
 * For CMD7 and CMD12, Params change if response is R1b. Default taken is R1.
 * R1 resp Mask values - Reference Table 52 in Jedec JESD84-B45 spec
 */
const static cmd_info_t seq_tCmdInfoTbl[_CMD_MAX] =
{
    {_RESP_CTGY0, _DAT_UNUSED},     /* CMD0 */
    {_RESP_CTGY2, _DAT_UNUSED},     /* CMD1 */
    {_RESP_CTGY1, _DAT_UNUSED},     /* CMD2 */
    {_RESP_CTGY3, _DAT_UNUSED},     /* CMD3 */
    {_RESP_CTGY0, _DAT_UNUSED},     /* CMD4 */
    {_RESP_CTGY4, _DAT_USED_BUSY},  /* CMD5 */
    {_RESP_CTGY4, _DAT_USED_BUSY},  /* CMD6 */
    {_RESP_CTGY3, _DAT_UNUSED},     /* CMD7 */
    {_RESP_CTGY3, _DAT_USED_DATA},  /* CMD8 */
    {_RESP_CTGY1, _DAT_UNUSED},     /* CMD9 */
    {_RESP_CTGY1, _DAT_UNUSED},     /* CMD10 */
    {},                             /* Obsolete */
    {_RESP_CTGY3, _DAT_UNUSED},     /* CMD12 */
    {_RESP_CTGY3, _DAT_UNUSED},     /* CMD13 */
    {_RESP_CTGY3, _DAT_USED_DATA},  /* CMD14 */
    {_RESP_CTGY0, _DAT_UNUSED},     /* CMD15 */
    {_RESP_CTGY3, _DAT_UNUSED},     /* CMD16 */
    {_RESP_CTGY3, _DAT_USED_DATA},  /* CMD17 */
    {_RESP_CTGY3, _DAT_USED_DATA},  /* CMD18 */
    {_RESP_CTGY3, _DAT_USED_DATA},  /* CMD19 */
    {},                             /* Obsolete */
    {_RESP_CTGY3, _DAT_USED_DATA},  /* CMD21 */
    {},                             /* Rsvd */
    {_RESP_CTGY3, _DAT_UNUSED},     /* CMD23 */
    {_RESP_CTGY3, _DAT_USED_DATA},  /* CMD24 */
    {_RESP_CTGY3, _DAT_USED_DATA},  /* CMD25 */
    {_RESP_CTGY3, _DAT_USED_DATA},  /* CMD26 */
    {_RESP_CTGY3, _DAT_USED_DATA},  /* CMD27 */
    {_RESP_CTGY4, _DAT_USED_BUSY},  /* CMD28 */
    {_RESP_CTGY4, _DAT_USED_BUSY},  /* CMD29 */
    {_RESP_CTGY3, _DAT_USED_DATA},  /* CMD30 */
    {_RESP_CTGY3, _DAT_USED_DATA},  /* CMD31 */
    {},                             /* Rsvd */
    {},                             /* Rsvd */
    {},                             /* Rsvd */
    {_RESP_CTGY3, _DAT_UNUSED},     /* CMD35 */
    {_RESP_CTGY3, _DAT_UNUSED},     /* CMD36 */
    {},                             /* Rsvd */
    {_RESP_CTGY4, _DAT_USED_BUSY},  /* CMD38 */
    {_RESP_CTGY2, _DAT_UNUSED},     /* CMD39 */
    {_RESP_CTGY3, _DAT_UNUSED},     /* CMD40 */
    {},                             /* Rsvd */
    {_RESP_CTGY3, _DAT_USED_DATA},  /* CMD42 */
    {},                             /* Rsvd */
    {},                             /* Rsvd */
    {},                             /* Rsvd */
    {},                             /* Rsvd */
    {},                             /* Rsvd */
    {},                             /* Rsvd */
    {_RESP_CTGY3, _DAT_USED_DATA},  /* CMD49 */
    {},                             /* Rsvd */
    {},                             /* Rsvd */
    {},                             /* Rsvd */
    {},                             /* Rsvd */
    {},                             /* Rsvd */
    {_RESP_CTGY3, _DAT_UNUSED},     /* CMD55 */
    {_RESP_CTGY3, _DAT_USED_DATA},  /* CMD56 */
    {},                             /* Rsvd */
    {},                             /* Rsvd */
    {},                             /* Rsvd */
    {},                             /* Rsvd */
    {},                             /* Rsvd */
    {},                             /* Rsvd */
    {},                             /* Rsvd */
};

/* Table to maintain all sequences. executeSequence() reads from this table */
cmd_frm_t seq_tCmdSeqTbl[_SEQ_ID_MAX][(_NUM_CMD_MAX+1)] =
{
    /* Card Initialization sequence: Brings device to Standby state */
    { /* _SEQ_ID_INIT */
        {_CMD0, 0x0},         /* Reset device */
        {_CMD1, 0x40000000},  /* Send OCR: Sector mode selected in arg */
        {_CMD2, 0x0},         /* All Send CID */
        {_CMD3, 0x00010000},  /* Set Relative Addr */
        {_CMD_END, 0}
    },
    /* Config sequence: Bring to Transfer state, Set block len to 512bytes */
    { /* _SEQ_ID_CONFIG */
        {_CMD9, 0x00010000},  /* Send CSD */
        {_CMD10, 0x00010000}, /* Send CID */
        {_CMD7, 0x00010000},  /* Bring to transfer state */
        {_CMD16, 0x00000200}, /* Set Block length to 512 */
        {_CMD_END, 0}
    },
    /* SWITCH sequence. Command set/Extended CSD */
    { /* _SEQ_ID_SWITCH */
        {_CMD6, 0x0},         /* Switch command. Arg modified run time */
        {_CMD_END, 0}
    },
    /* Read Sequence */
    { /* _SEQ_ID_READ */
        {_CMD23, 0x0},        /* Set block count. Arg modified run time */
        {_CMD18, 0x0},        /* Multi read cmd. Arg modified run time */
        {_CMD_END, 0}
    },
    /* Write Sequence */
    { /* _SEQ_ID_WRITE */
        {_CMD23, 0x0},        /* Set block count. Arg modified run time */
        {_CMD25, 0x0},        /* Multi write cmd. Arg modified run time */
        {_CMD_END, 0}
    },
    /* Read Ext CSD */
    { /* _SEQ_ID_EXTCSD */
        {_CMD8, 0x00000000},  /* Get EXT CSD */
        {_CMD_END, 0}
    },
     /* Trim/Erase/Discard Sequence */
    { /* _SEQ_ID_ERASE */
        {_CMD35, 0x0},        /* Set Erase Start Addr. Arg modified run time */
        {_CMD36, 0x0},        /* Set Erase End Addr. Arg modified run time */
        {_CMD38, 0x0},        /* Start erase/trim/discard Arg modified runtim */
        {_CMD_END, 0}
    },
    /* Write CSD */
    { /* _SEQ_ID_WRCSD */
        {_CMD16, _COM_CSD_SIZE},  /* Set Block Length.128 bits - 16 bytes*/
        {_CMD27, 0x0},            /* Write CSD. Arg modified run time */
        {_CMD16, _BLK_SIZE},      /* Set Block Length.64 bits - 8 bytes*/
        {_CMD_END, 0}
    },
    /* Read CSD */
    { /* _SEQ_ID_RDCSD */
        {_CMD7, 0x00000000},  /* Bring to standby state */
        {_CMD9, 0x00010000},  /* Read CSD.*/
        {_CMD7, 0x00010000},  /* Bring to transfer state */
        {_CMD_END, 0}
    },
    /* Wrong erase sequence: For testing only */
    { /* _SEQ_ID_WRONGERASE */
        {_CMD35, 0x0},        /* Set Erase Start Addr.Arg set to 0 for testing */
        {_CMD38, 0x0},        /* Start [erase/trim/discard] process. Arg set
                               * to 0 for testing */
        {_CMD36, 0x0},        /* Set Erase End Addr. Arg set to 0 for testing */
        {_CMD_END, 0}
    },
    /* Non Erase cmd in erase sequence: For testing only */
    { /* _SEQ_ID_NONERASE */
        {_CMD35, 0x0},        /* Set Erase Start Addr.Arg set to 0 for testing */
        {_CMD36, 0x0},        /* Set Erase End Addr. Arg set to 0 for testing */
        {_CMD16, 512},        /* non Erase command: for testin only */
        {_CMD38, 0x0},        /* Start [erase/trim/discard] process. Arg set
                               * to 0 for testing */
        {_CMD_END, 0}
    },
    /* Sequence for sending to Inactive state */
    { /* _SEQ_ID_INACTIVE */
        {_CMD15, 0x00020000},/* RCA=0x0002 for testing purpose. This can be
                              * changed if reqd */
        {_CMD_END, 0}
    },
    /* Sequence for deselect */
    { /* _SEQ_ID_DESELECT */
        {_CMD7, 0x00000000}, /* Arg=0x0 for deselecting device */
        {_CMD13, 0x00010000}, /* To check the device state */
        {_CMD_END, 0}
    },
    /* Sequence for select */
    { /* _SEQ_ID_SELECT */
        {_CMD7, 0x00010000}, /* RCA= 0x0001 for selecting device */
        {_CMD_END, 0}
    },
    /* Set Write Protect */
    { /* _SEQ_ID_SETWP */
        {_CMD28, 0x0},        /* Read CSD. Arg modified run time */
        {_CMD_END, 0}
    },
    /* Clear Write Protect */
    { /* _SEQ_ID_CLRWP */
        {_CMD29, 0x0},        /* Read CSD. Arg modified run time */
        {_CMD_END, 0}
    },
    /* Get Write Protect Status */
    { /* _SEQ_ID_GET_WP_STAT */
        {_CMD16, _COM_CMD30_RET_SIZE},/* Set Block Length - 32 bits [4 bytes] */
        {_CMD30, 0},        /* Get Write Potect Status. Arg modified run time */
        {_CMD16, _BLK_SIZE}, /* Resetting BLK LEN to 512Bytes */
        {_CMD_END, 0}
    },
    /* Get Write Protect Type*/
    { /* _SEQ_ID_GET_WP_TYP */
        {_CMD16, _COM_CMD31_RET_SIZE},  /* Set Block Length.64 bits - 8 bytes*/
        {_CMD31, 0x0},       /* Get Write Potect type. Arg modified run time */
        {_CMD16, _BLK_SIZE}, /* Resetting BLK LEN to 512Bytes */
        {_CMD_END, 0}
    },
      /* Dev Lock/Unlock, set/clr PWD,Force Erase */
    { /* _SEQ_ID_LKUNLK */
        {_CMD16, 0x0},        /* Set Block Len. Arg modified run time */
        {_CMD42, 0x0},        /* Dev Lock/Unlock CMD. Arg modified run time */
        {_CMD16, _BLK_SIZE},  /* Resetting BLK LEN to 512Bytes */
        {_CMD_END, 0}
    },
};

/*
 * Table to maintain the Ext CSD reg field types. The types are as follows.
 * _R    : Read only
 * _W    : One Time Programmable and not readable
 * _RW   : One Time Programmable and readable
 * _WE   : Multiple writable with value kept after power failure, H/W reset
 *         assertion and any CMD0 reset and not readable
 * _RWE  : Multiple writable with value kept after power failure, H/W reset
 *         assertion and any CMD0 reset and readable
 * _RWC_P: Writable after value cleared by power failure and H/w reset
 *         assertion(value not cleared by CMD0 reset) and readable
 * _RWE_P: Multiple writable with value reset after power failure, H/W reset
 *         assertion and any CMD0 reset and readable
 * _WE_P : Multiple writable with value reset after power failure, H/W reset
 *         assertion and any CMD0 reset and not readable
 * _RSVD : Reserved field
 *
 * NOTE: Even if one bit of a register field is OTP, the type is set as OTP.
 */
const static extcsd_typ_e seq_tExtCSDTbl[_EXTCSD_NUMBYTES] =
{
    _RSVD,  /* Byte-0 */
    _RSVD,  /* Byte-1 */
    _RSVD,  /* Byte-2 */
    _RSVD,  /* Byte-3 */
    _RSVD,  /* Byte-4 */
    _RSVD,  /* Byte-5 */
    _RSVD,  /* Byte-6 */
    _RSVD,  /* Byte-7 */
    _RSVD,  /* Byte-8 */
    _RSVD,  /* Byte-9 */
    _RSVD,  /* Byte-10 */
    _RSVD,  /* Byte-11 */
    _RSVD,  /* Byte-12 */
    _RSVD,  /* Byte-13 */
    _RSVD,  /* Byte-14 */
    _RSVD,  /* Byte-15 */
    _RSVD,  /* Byte-16 */
    _RSVD,  /* Byte-17 */
    _RSVD,  /* Byte-18 */
    _RSVD,  /* Byte-19 */
    _RSVD,  /* Byte-20 */
    _RSVD,  /* Byte-21 */
    _RSVD,  /* Byte-22 */
    _RSVD,  /* Byte-23 */
    _RSVD,  /* Byte-24 */
    _RSVD,  /* Byte-25 */
    _RSVD,  /* Byte-26 */
    _RSVD,  /* Byte-27 */
    _RSVD,  /* Byte-28 */
    _RSVD,  /* Byte-29 */
    _RSVD,  /* Byte-30 */
    _RSVD,  /* Byte-31 */
    _WE_P,  /* Byte-32 */
    _RWE_P, /* Byte-33 */
    _RWE_P, /* Byte-34 */
    _R,     /* Byte-35 */
    _R,     /* Byte-36 */
    _RWE_P, /* Byte-37 */
    _RWE_P, /* Byte-38 */
    _RWE_P, /* Byte-39 */
    _RWE_P, /* Byte-40 */
    _RWE_P, /* Byte-41 */
    _RWE_P, /* Byte-42 */
    _RWE_P, /* Byte-43 */
    _RWE_P, /* Byte-44 */
    _RWE_P, /* Byte-45 */
    _RWE_P, /* Byte-46 */
    _RWE_P, /* Byte-47 */
    _RWE_P, /* Byte-48 */
    _RWE_P, /* Byte-49 */
    _RWE_P, /* Byte-50 */
    _RWE_P, /* Byte-51 */
    _RW,    /* Byte-52 */
    _RW,    /* Byte-53 */
    _R,     /* Byte-54 */
    _R,     /* Byte-55 */
    _RWE_P, /* Byte-56 */
    _RWE_P, /* Byte-57 */
    _R,     /* Byte-58 */
    _RWE_P, /* Byte-59 */
    _R,     /* Byte-60 */
    _R,     /* Byte-61 */
    _RW,    /* Byte-62 */
    _R,     /* Byte-63 */
    _RSVD,  /* Byte-64 */
    _RSVD,  /* Byte-65 */
    _RSVD,  /* Byte-66 */
    _RSVD,  /* Byte-67 */
    _RSVD,  /* Byte-68 */
    _RSVD,  /* Byte-69 */
    _RSVD,  /* Byte-70 */
    _RSVD,  /* Byte-71 */
    _RSVD,  /* Byte-72 */
    _RSVD,  /* Byte-73 */
    _RSVD,  /* Byte-74 */
    _RSVD,  /* Byte-75 */
    _RSVD,  /* Byte-76 */
    _RSVD,  /* Byte-77 */
    _RSVD,  /* Byte-78 */
    _RSVD,  /* Byte-79 */
    _RSVD,  /* Byte-80 */
    _RSVD,  /* Byte-81 */
    _RSVD,  /* Byte-82 */
    _RSVD,  /* Byte-83 */
    _RSVD,  /* Byte-84 */
    _RSVD,  /* Byte-85 */
    _RSVD,  /* Byte-86 */
    _RSVD,  /* Byte-87 */
    _RSVD,  /* Byte-88 */
    _RSVD,  /* Byte-89 */
    _RSVD,  /* Byte-90 */
    _RSVD,  /* Byte-91 */
    _RSVD,  /* Byte-92 */
    _RSVD,  /* Byte-93 */
    _RSVD,  /* Byte-94 */
    _RSVD,  /* Byte-95 */
    _RSVD,  /* Byte-96 */
    _RSVD,  /* Byte-97 */
    _RSVD,  /* Byte-98 */
    _RSVD,  /* Byte-99 */
    _RSVD,  /* Byte-100 */
    _RSVD,  /* Byte-101 */
    _RSVD,  /* Byte-102 */
    _RSVD,  /* Byte-103 */
    _RSVD,  /* Byte-104 */
    _RSVD,  /* Byte-105 */
    _RSVD,  /* Byte-106 */
    _RSVD,  /* Byte-107 */
    _RSVD,  /* Byte-108 */
    _RSVD,  /* Byte-109 */
    _RSVD,  /* Byte-110 */
    _RSVD,  /* Byte-111 */
    _RSVD,  /* Byte-112 */
    _RSVD,  /* Byte-113 */
    _RSVD,  /* Byte-114 */
    _RSVD,  /* Byte-115 */
    _RSVD,  /* Byte-116 */
    _RSVD,  /* Byte-117 */
    _RSVD,  /* Byte-118 */
    _RSVD,  /* Byte-119 */
    _RSVD,  /* Byte-120 */
    _RSVD,  /* Byte-121 */
    _RSVD,  /* Byte-122 */
    _RSVD,  /* Byte-123 */
    _RSVD,  /* Byte-124 */
    _RSVD,  /* Byte-125 */
    _RSVD,  /* Byte-126 */
    _RSVD,  /* Byte-127 */
    _RSVD,  /* Byte-128 */
    _RSVD,  /* Byte-129 */
    _R,     /* Byte-130 */
    _RWE,   /* Byte-131 */
    _WE_P,  /* Byte-132 */
    _RSVD,  /* Byte-133 */
    _RW,    /* Byte-134 */
    _RSVD,  /* Byte-135 */
    _RW,    /* Byte-136 */
    _RW,    /* Byte-137 */
    _RW,    /* Byte-138 */
    _RW,    /* Byte-139 */
    _RW,    /* Byte-140 */
    _RW,    /* Byte-141 */
    _RW,    /* Byte-142 */
    _RW,    /* Byte-143 */
    _RW,    /* Byte-144 */
    _RW,    /* Byte-145 */
    _RW,    /* Byte-146 */
    _RW,    /* Byte-147 */
    _RW,    /* Byte-148 */
    _RW,    /* Byte-149 */
    _RW,    /* Byte-150 */
    _RW,    /* Byte-151 */
    _RW,    /* Byte-152 */
    _RW,    /* Byte-153 */
    _RW,    /* Byte-154 */
    _RW,    /* Byte-155 */
    _RW,    /* Byte-156 */
    _R,     /* Byte-157 */
    _R,     /* Byte-158 */
    _R,     /* Byte-159 */
    _R,     /* Byte-160 */
    _RWE_P, /* Byte-161 */
    _RW,    /* Byte-162 */
    _RW,    /* Byte-163 */
    _WE_P,  /* Byte-164 */
    _WE_P,  /* Byte-165 */
    _R,     /* Byte-166 */
    _RW,    /* Byte-167 */
    _R,     /* Byte-168 */
    _RW,    /* Byte-169 */
    _RSVD,  /* Byte-170 */
    _RW,    /* Byte-171 */
    _RSVD,  /* Byte-172 */
    _RW,    /* Byte-173 */
    _R,     /* Byte-174 */
    _RWE_P, /* Byte-175 */
    _RSVD,  /* Byte-176 */
    _RWE,   /* Byte-177 */
    _RW,    /* Byte-178 */
    _RWE,   /* Byte-179 */
    _RSVD,  /* Byte-180 */
    _R,     /* Byte-181 */
    _RSVD,  /* Byte-182 */
    _WE_P,  /* Byte-183 */
    _RSVD,  /* Byte-184 */
    _RWE_P, /* Byte-185 */
    _RSVD,  /* Byte-186 */
    _RWE_P, /* Byte-187 */
    _RSVD,  /* Byte-188 */
    _R,     /* Byte-189 */
    _RSVD,  /* Byte-190 */
    _RWE_P, /* Byte-191 */
};

/*
 * Table to maintain valid states for each command:
 * [1 indicates state is valid]
 * Bit0 - Idle State
 * Bit1 - Ready State
 * Bit2 - Identification State
 * Bit3 - Standby State
 * Bit4 - Transfer State
 * Bit5 - Send-data State
 * Bit6 - Recv- data State
 * Bit7 - Programming State
 * Bit8 - Disconnect State
 * Bit9 - Bus-test State
 * Bit10 - Sleep State
 */
const static _ub32 seq_tValidStates[_CMD_MAX] =
{
    0x000007FF,         /* CMD0 */
    0x00000001,         /* CMD1 */
    0x00000002,         /* CMD2 */
    0x00000004,         /* CMD3 */
    0x00000008,         /* CMD4 */
    0x00000408,         /* CMD5 */
    0x00000010,         /* CMD6 */
    0x000001B8,         /* CMD7 */
    0x00000010,         /* CMD8 */
    0x00000008,         /* CMD9 */
    0x00000008,         /* CMD10 */
    0x00000000,         /* CMD11 - Obsolete */
    0x000000E0,         /* CMD12 */
    0x000003F8,         /* CMD13 */
    0x00000200,         /* CMD14 */
    0x000003F8,         /* CMD15 */
    0x00000010,         /* CMD16 */
    0x00000010,         /* CMD17 */
    0x00000010,         /* CMD18 */
    0x00000010,         /* CMD19 */
    0x00000000,         /* CMD20 - Obsolete */
    0x00000010,         /* CMD21 */
    0x00000000,         /* CMD22 - Rsvd */
    0x00000010,         /* CMD23 */
    0x00000010,         /* CMD24 */
    0x00000010,         /* CMD25 */
    0x00000010,         /* CMD26 */
    0x00000010,         /* CMD27 */
    0x00000010,         /* CMD28 */
    0x00000010,         /* CMD29 */
    0x00000010,         /* CMD30 */
    0x00000010,         /* CMD31 */
    0x000007FF,         /* CMD32 - Rsvd */
    0x000007FF,         /* CMD33 - Rsvd */
    0x000007FF,         /* CMD34 - Rsvd */
    0x00000010,         /* CMD35 */
    0x00000010,         /* CMD36 */
    0x00000000,         /* CMD37 - Rsvd */
    0x00000010,         /* CMD38 */
    0x00000008,         /* CMD39 */
    0x00000008,         /* CMD40 */
    0x00000000,         /* CMD41 - Rsvd */
    0x00000010,         /* CMD42 */
    0x00000000,         /* CMD43 - Rsvd */
    0x00000000,         /* CMD44 - Rsvd */
    0x00000000,         /* CMD45 - Rsvd */
    0x00000000,         /* CMD46 - Rsvd */
    0x00000000,         /* CMD47 - Rsvd */
    0x00000000,         /* CMD48 - Rsvd */
    0x00000010,         /* CMD49 */
    0x00000000,         /* CMD50 - Rsvd */
    0x00000000,         /* CMD51 - Rsvd */
    0x00000000,         /* CMD52 - Rsvd */
    0x00000000,         /* CMD53 - Rsvd */
    0x00000000,         /* CMD54 - Rsvd */
    0x000003F8,         /* CMD55 */
    0x00000010,         /* CMD56 */
    0x00000000,         /* CMD57 - Rsvd */
    0x00000000,         /* CMD58 - Rsvd */
    0x00000000,         /* CMD59 - Rsvd */
    0x00000000,         /* CMD60 - Rsvd */
    0x00000000,         /* CMD61 - Rsvd */
    0x00000000,         /* CMD62 - Rsvd */
    0x00000000,         /* CMD63 - Rsvd */
};

/* used for calculating the CRC of CSD values */
static _ub32 seq_crcBuf[_DEV_CSD_SIZ_BYTE];

static _ub8 seq_ucLockState;

/**@}*/ // Seq_Globals

/*----------------------- Function Definitions ------------------------------*/

/** @addtogroup Seq_Functions Seq_Functions
 * @{
 */

/**
 * @brief Common function for any eMMC sequence execution.
 *
 * @param[in] eSeqID Sequence ID of the sequence
 * @param[in] uiSlot Host Controller slot number
 *
 * @retval dev_sts_e Sequence error code
 */
dev_sts_e executeSequence(_ub32 uiSlot, seq_id_e eSeqID)
{
    cmd_frm_t *pCmdSeq;
    cmd_params_t tCmdParams;
    _ub32 uiLoop = 0;
    cmd_sts_e eSts = _CMD_STS_OK;
    _ub32 uiRespData[4];
    _ub8 ucCmd1Retry = 0;
    _ub8 ucErrRetry = 0;
    dev_sts_e eRetVal = _DEV_STS_OK;
    const cmd_info_t *pCmdInfo;
    hc_sts_e eHcSts = _HC_STS_OK;
    _ub32 uiDevState = 0;

    _SEQ_DBG_INFO("ENTRY");

    /* slot argument is not verified as it will be done by caller */

    /* sequence ID verification */
    if((eSeqID < _SEQ_ID_INIT) || (eSeqID >= _SEQ_ID_MAX))
    {
        _SEQ_DBG_ERR("Input param error ");
        return _DEV_INPUT_ERR;
    }

    /* Get the sequence based on sequence ID */
    pCmdSeq = seq_tCmdSeqTbl[eSeqID];

    /* Initialize values to 0 */
    os_setMem(&tCmdParams, 0, sizeof(tCmdParams));
    os_setMem(uiRespData, 0, sizeof(uiRespData));

    /* Execute sequence by sending commands one by one until end of sequence. */
    for(uiLoop = 0; uiLoop < (_NUM_CMD_MAX + 1); uiLoop++)
    {
        ucErrRetry = 0;

        /* End of sequence reached */
        if(_CMD_END == pCmdSeq[uiLoop].eIndex)
        {
            _SEQ_DBG_INFO("Sequence End...!!!");
            break;
        }
        else
        {
            /* Frame the command parameters required by CMD APIs layer */
            tCmdParams.eIndex = pCmdSeq[uiLoop].eIndex;
            pCmdInfo = &seq_tCmdInfoTbl[tCmdParams.eIndex];
            tCmdParams.eRespCtgy = pCmdInfo->eRespCtgy;
            tCmdParams.eDatUsage = pCmdInfo->eDatUsage;
            tCmdParams.uiArg = pCmdSeq[uiLoop].uiArg;

            /*
             * IMPT: This is special handling for CMD7
             * If CMD7 is given for deselecting the device(ie., Arg is 0),
             * Response category should be set as "No Response" ie., _RESP_CTGY0
             */
            if((_CMD7 == pCmdSeq[uiLoop].eIndex) &&
               (0 == pCmdSeq[uiLoop].uiArg))
            {
                tCmdParams.eRespCtgy = _RESP_CTGY0;
            }
        }

        switch(tCmdParams.eIndex)
        {
            case _CMD0:
            case _CMD1:
            case _CMD2:
            case _CMD3:
            /*
             * CMD13 can be send only in Data transfer mode. So state cannot
             * be checked before CMD0/1/2/3 . Hence, break
             */
            break;

            /*
             * Note: Reserved & Obsolete commands not checked here as they won't
             * be used in the sequence table itself.
             */

            default:
                /* Check if device state is valid for the command */
                eRetVal = checkDeviceState(uiSlot,tCmdParams.eIndex);
                if(_DEV_STS_OK != eRetVal)
                {
                    return eRetVal;
                }
            break;
        }

        while(ucErrRetry < _ERR_RETRY_MAX)
        {
            /* Call the Send command API */
            eSts = cmd_sendCommand(uiSlot, &tCmdParams, uiRespData);
            if(_CMD_STS_OK != eSts)
            {
                /* If any CMD err occurs, reset CMD/DAT lines */
                if(eSts > _CMD_DATLINE_BUSY)
                {
                    /* Reset CMD line */
                    eHcSts = hc_reset(uiSlot, _COM_RST_CMD);
                    if(_HC_STS_OK != eHcSts)    /* CMD line reset failed */
                    {
                        _SEQ_DBG_ERR("CMD line reset failed");
                        eRetVal = _DEV_CMDSEND_ERR;
                        break;
                    }

                    /* Reset DAT line if cmd uses DAT line */
                    if(_DAT_UNUSED != tCmdParams.eDatUsage)
                    {
                        eHcSts = hc_reset(uiSlot, _COM_RST_DAT);
                        if(_HC_STS_OK != eHcSts)    /* DAT line reset failed */
                        {
                            _SEQ_DBG_ERR("DAT line reset failed");
                            eRetVal = _DEV_CMDSEND_ERR;
                            break;
                        }
                    }
                    /* If error occurs, retry should be 3 times max */
                    ucErrRetry++;
                    os_delayMs(1);
                }
                else
                {
                    /*
                     * For CMD/DAT line busy error, DAT errors and ADMA errors
                     * return error directly w/o retry.
                     */
                    eRetVal = (dev_sts_e)eSts;
                    break;
                }
            }
            /* Parse the response data */
            else
            {
                /* Reset error retry count to 0 */
                ucErrRetry = 0;

                /*
                 * For CMD1, up to 15 times retrial required for Device
                 * power up sequence to be completed. Bit31 of OCR gives
                 * the card power up status.
                 */
                if(_CMD1 == tCmdParams.eIndex)
                {
                    /*
                     * If power up is done, parse the response data
                     * and store OCR register details
                     */
                    if(_POWER_UP_OK == (uiRespData[0] & _POWER_UP_OK))
                    {
                        parseR3Resp(uiRespData, &seq_tOCRParams[uiSlot]);
                        ucCmd1Retry = 0;
                        break;
                    }
                    else
                    {
                        /* If power up not completed, retry for max 15 times */
                        ucCmd1Retry++;

                        /* 1ms wait based on trial & error */
                        os_delayMs(1);

                        /* resend OCR with sector mode selection */
                        tCmdParams.uiArg |= uiRespData[0];

                        /* If max retry reached, break out of loop */
                        if(ucCmd1Retry > _CMD1_RETRY_MAX)
                        {
                            eRetVal = _DEV_TIMEOUT_ERR;
                            ucCmd1Retry = 0;
                            break;
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
                /*
                 * For other commands, parse the response and
                 * check for errors in case of R1 response.
                 */
                else
                {
                    eRetVal = checkResponse(
                        uiSlot,
                        tCmdParams.eIndex,
                        uiRespData);

                    break;
                }
            }
        }
        if((ucErrRetry >= _ERR_RETRY_MAX) || (_DEV_STS_OK != eRetVal))
        {
            _SEQ_DBG_ERR("Sequence failed !!! %d %d", ucErrRetry, eRetVal);
            break;
        }

        /* Reset the retry count to 0 for the next command */
        ucErrRetry = 0;
    }

    /* CMD Error code and Seq return value mapping */
    if(eSts > _CMD_DATLINE_BUSY)
    {
        eRetVal = _DEV_CMDSEND_ERR;
    }

    if(_DEV_STS_OK == eRetVal)
    {
        eRetVal = seq_getDevSts(uiSlot, &uiDevState);
    }

#ifdef __DEVERR_HANDLING
    /* If a device related error has occured, do error handling */
    if((eRetVal >= _DEV_ADDR_OUT_OF_RANGE) &&
        (eRetVal <= _DEV_EXCEPTION))
    {
        /*
         * For init sequence there is no point doing error recovery
         * as device has not even been initialized
         */
        if(_SEQ_ID_INIT != eSeqID)
        {
            devErrHandling(uiSlot);
        }
    }
#endif /* __DEVERR_HANDLING */

    _SEQ_DBG_INFO("EXIT");

    return eRetVal;
}

/**
 * @brief Function that parses the response data.
 *
 * @param[in] uiSlot Slot Number
 * @param[in] eIndex Command Index
 * @param[in] puiRespData Pointer to response array
 *
 * @retval _DEV_STS_OK Return status ok
 * @retval _DEV_ADDR_OUT_OF_RANGE Address out of Range error occurred
 * @retval _DEV_ADDR_MISALIGN Address misalign error occurred
 * @retval _DEV_BLK_LEN_ERR Block length error occurred
 * @retval _DEV_ERASE_SEQ_ERR Erase sequence error occurred
 * @retval _DEV_ERASE_PARAM_ERR Erase param error occurred
 * @retval _DEV_WP_VIOLATION_ERR WP violation occurred
 * @retval _DEV_LOCK_UNLOCK_FAIL Lock/Unlock Failed
 * @retval _DEV_ILLEGAL_CMD_ERR Illegal command issued
 * @retval _DEV_ECC_FAIL Device ECC failed
 * @retval _DEV_CC_ERR Device undefined Error
 * @retval _DEV_ERR Device error related to last host cmd
 * @retval _DEV_CIDCSD_OVERWRITE_ERR CID/CSD overwrite error
 * @retval _DEV_WP_ERASE_SKIP_ERR WP Erase skip error
 * @retval _DEV_ERASE_RESET_ERR Erase reset error
 * @retval _DEV_SWITCH_ERR Switch command error
 */
static dev_sts_e checkResponse(
    _ub32 uiSlot,
    cmd_index_e eIndex,
    _ub32 *puiRespData)
{
    dev_sts_e eRet = _DEV_STS_OK;

    /* Input arguments are not verified as it will be done by caller */

    switch(eIndex)
    {
        /* Commands with R2 response: CID register info */
        case _CMD2:
        case _CMD10:
            parseR2Resp(uiSlot, puiRespData, _CID);
        break;

        /* Commands with R2 response: CSD register info */
        case _CMD9:
            parseR2Resp(uiSlot, puiRespData, _CSD);
        break;

        /*
         * Commands with R3 response:
         * R3 response is already taken care for CMD1 prior to this func
         * call. Control will not come here. This is added just for
         * future extensibility or completion of spec adherence.
         */
        case _CMD1:
            parseR3Resp(puiRespData, &seq_tOCRParams[uiSlot]);
        break;

        /* Commands with no response */
        case _CMD0:
        case _CMD4: /* Fall Thru */
            break;

        /* Obsolete/Rsvd/App-specific Commands*/
        case _CMD11: /* Fall Thru */
        case _CMD20:
        case _CMD22:
        case _CMD32:
        case _CMD33:
        case _CMD34:
        case _CMD37:
        case _CMD41:
        case _CMD43:
        case _CMD44:
        case _CMD45:
        case _CMD46:
        case _CMD47:
        case _CMD48:
        case _CMD50:
        case _CMD51:
        case _CMD52:
        case _CMD53:
        case _CMD54:
        case _CMD55:
        case _CMD56:
        case _CMD57:
        case _CMD58:
        case _CMD59:
        case _CMD60:
        case _CMD61:
        case _CMD62:
        case _CMD63:
        break;

        default:
            /* Commands with R1 response: */

            /* Parse the R1 response data and perform reqd error handling */
            eRet = parseR1Resp(eIndex, *puiRespData);
        break;
    }
    return eRet;
}

/**
 * @brief Function to parse R1 response.
 *
 * @param[in] eIndex Command index
 * @param[in] uiRespVal Response data masked with appropriate bits
 *
 * @retval _DEV_STS_OK Return status ok
 * @retval _DEV_LOCKED Device is locked
 * @retval _DEV_EXCEPTION Device exception event occurred
 * @retval _DEV_ADDR_OUT_OF_RANGE Address out of Range error occurred
 * @retval _DEV_ADDR_MISALIGN Address misalign error occurred
 * @retval _DEV_BLK_LEN_ERR Block length error occurred
 * @retval _DEV_ERASE_SEQ_ERR Erase sequence error occurred
 * @retval _DEV_ERASE_PARAM_ERR Erase param error occurred
 * @retval _DEV_WP_VIOLATION_ERR WP violation occurred
 * @retval _DEV_LOCK_UNLOCK_FAIL Lock/Unlock Failed
 * @retval _DEV_ILLEGAL_CMD_ERR Illegal command issued
 * @retval _DEV_ECC_FAIL Device ECC failed
 * @retval _DEV_CC_ERR Device undefined Error
 * @retval _DEV_ERR Device error related to last host cmd
 * @retval _DEV_CIDCSD_OVERWRITE_ERR CID/CSD overwrite error
 * @retval _DEV_WP_ERASE_SKIP_ERR WP Erase skip error
 * @retval _DEV_ERASE_RESET_ERR Erase reset error
 * @retval _DEV_SWITCH_ERR Switch command error
 */
static dev_sts_e parseR1Resp(cmd_index_e eIndex, _ub32 uiRespVal)
{
    dev_sts_e eSts = _DEV_STS_OK;
    _ub16 devState = 0;

    /* Input arguments are not verified as it will be done by caller */

    seq_ucLockState = 0;

    /* Check the device status bits(S fields) in the resp data */
    /*
     * Check if device is locked. Return status is set as OK, bcoz
     * this is not an error condition and initialization and lock/unlock
     * commands can be sent when device is locked.
     */
    if(uiRespVal & _DEV_LOCKED_ERROR)
    {
        _SEQ_DBG_ERR("Device is locked!");
        seq_ucLockState = 1;
    }

    /* Check if any exception event occurred. Return status to upper layer */
    if(uiRespVal & _DEV_EXCEPTION_ERR)
    {
        _SEQ_DBG_ERR("Device Exception event occurred!");
        return _DEV_EXCEPTION;
    }

    /* Get the device current state */
    devState = (_ub16)((uiRespVal & _DEV_STATE) >> 9);

    _SEQ_DBG_INFO("Device state: 0x%04x", devState);

    /* Get the device ready for data bit */
    _SEQ_DBG_INFO("Dev ready for dat: %d",
        ((uiRespVal & _DEV_READY_DATA) >> 8));

    /* Check for device errors */
    if(uiRespVal & _DEV_STS_E)
    {
        /* Response mode errors: To be checked for all commands */
        if(uiRespVal & _DEV_ERR_RMODE)
        {
            if(uiRespVal & _DEV_ADDR_OUT)
            {
                /*
                 * This error can occur in resp/exec mode.
                 * If reported as part of CMD13's response, it's exec mode err.
                 */
                _SEQ_DBG_ERR("DEV RESP/EXEC ERR: Addr out of range!");
                eSts = _DEV_ADDR_OUT_OF_RANGE;
            }

            if(uiRespVal & _DEV_ADRMISALIGN)
            {
                /*
                 * This error can occur in resp/exec mode.
                 * If reported as part of CMD13's response, it's exec mode err.
                 */
                _SEQ_DBG_ERR("DEV RESP/EXEC ERR: Addr misaligned!");
                eSts = _DEV_ADDR_MISALIGN;
            }

            if(uiRespVal & _DEV_BLKLEN_ERR)
            {
                _SEQ_DBG_ERR("DEV RESP ERR: Wrong Block length!");
                eSts = _DEV_BLK_LEN_ERR;
            }

            if(uiRespVal & _DEV_ERASESEQ_ERR)
            {
                _SEQ_DBG_ERR("DEV RESP ERR: Wrong seq of erase commands!");
                eSts = _DEV_ERASE_SEQ_ERR;
            }

            if(uiRespVal & _DEV_COMCRC_ERR)
            {
                /*
                 * This error will be checked by host controller itself, if CRC
                 * check is enabled. This is a double check here.
                 */
                _SEQ_DBG_ERR("DEV RESP ERR: CMD CRC error!");
                eSts = _DEV_CMDSEND_ERR;
            }

            if(uiRespVal & _DEV_ILLEGAL_CMD)
            {
                _SEQ_DBG_ERR("DEV RESP ERR: Illegal CMD error!");
                eSts = _DEV_ILLEGAL_CMD_ERR;
            }

            if(uiRespVal & _DEV_CC_ERROR)
            {
                _SEQ_DBG_ERR("DEV RESP ERR: An undefined error occurred!");
                eSts = _DEV_CC_ERR;
            }

            if(uiRespVal & _DEV_ERASE_RESET)
            {
                _SEQ_DBG_ERR("DEV RESP ERR: Erase seq was reset!");
                eSts = _DEV_ERASE_RESET_ERR;
            }
        }

        /* In case of CMD13, check for execution mode errors of prev cmd */
        if((_CMD13 == eIndex) && (uiRespVal & _DEV_ERR_XMODE))
        {
            if(uiRespVal & _DEV_ERASEPAR_ERR)
            {
                _SEQ_DBG_ERR("DEV EXEC ERR: Invalid selection of erase grps!");
                eSts = _DEV_ERASE_PARAM_ERR;
            }

            if(uiRespVal & _DEV_WP_VIOLATION)
            {
                _SEQ_DBG_ERR("DEV EXEC ERR: Write protect violation!");
                eSts = _DEV_WP_VIOLATION_ERR;
            }

            if(uiRespVal & _DEV_LOCK_FAILED)
            {
                _SEQ_DBG_ERR("DEV EXEC ERR: Lock/Unlock failed!");
                eSts = _DEV_LOCK_UNLOCK_FAIL;
            }

            if(uiRespVal & _DEV_ECC_FAILED)
            {
                _SEQ_DBG_ERR("DEV EXEC ERR: Dev ECC was applied but failed!");
                eSts = _DEV_ECC_FAIL;
            }

            if(uiRespVal & _DEV_ERROR)
            {
                _SEQ_DBG_ERR("DEV EXEC ERR: An undefined err related to cmd!");
                eSts = _DEV_ERR;
            }

            if(uiRespVal & _DEV_OVERWRITE)
            {
                _SEQ_DBG_ERR("DEV EXEC ERR: Overwrite error for CID/CSD!");
                eSts = _DEV_CIDCSD_OVERWRITE_ERR;
            }

            if(uiRespVal & _DEV_WP_ERASESKIP)
            {
                _SEQ_DBG_ERR("DEV EXEC ERR: Only partial erase coz of WP!");
                eSts = _DEV_WP_ERASE_SKIP_ERR;
            }

            if(uiRespVal & _DEV_SWITCH_ERROR)
            {
                _SEQ_DBG_ERR("DEV EXEC ERR: Switch command failed!");
                eSts = _DEV_SWITCH_ERR;
            }
        }
    }

    return eSts;
}

/**
 * @brief Function to parse R2 response.
 *
 * @param[in] uiSlot Slot Number
 * @param[in] puiRespVal Pointer to response data
 * @param[in] ucReg CID/CSD register to be updated
 *
 * @retval None
 */
static void parseR2Resp(_ub32 uiSlot, _ub32 *puiRespVal, _ub8 ucReg)
{
    com_cid_params_t *pCIDParams;
    com_csd_params_t *pCSDParams;
    _ub32 uiVal0 = 0;
    _ub32 uiVal1 = 0;
    _ub32 uiVal2 = 0;
    _ub32 uiVal3 = 0;
    _ub32 uiTempVar1 = 0;
    _ub32 uiTempVar2 = 0;
    _ub8 ucTempVar1 = 0;
    _ub8 ucTempVar2 = 0;

    /* Input arguments are not verified as it will be done by caller */

    /* Read the bits 31-0 of Response reg value for CSD/CID Register */
    uiVal0 = *(puiRespVal + 0);

    /* Read the bits 63-32 of Response reg value for CSD/CID Register */
    uiVal1 = *(puiRespVal + 1);

    /* Read the bits 95-64 of Response reg value for CSD/CID Register */
    uiVal2 = *(puiRespVal + 2);

    /* Read the bits 127-96 of Response reg value for CSD/CID Register */
    uiVal3 = *(puiRespVal + 3);

    _SEQ_DBG_INFO("uiVal3 = 0x%x",uiVal3);
    _SEQ_DBG_INFO("uiVal2 = 0x%x",uiVal2);
    _SEQ_DBG_INFO("uiVal1 = 0x%x",uiVal1);
    _SEQ_DBG_INFO("uiVal0 = 0x%x\n",uiVal0);

    switch(ucReg)
    {
        /* CMD2/CMD10 gives CID as R2 response */
        case _CID:
            /* Get the global CID structure address */
            pCIDParams = &seq_tCIDParams[uiSlot];

            /*
             * Manufacture ID (MID). Bits[127:120] in CID
             * This is mapped to bits [119:112] in the response register
             */
            pCIDParams->ucManuID = ((uiVal3 & _MANUID_MASK) >> 16);
            _SEQ_DBG_INFO("Manufacturer ID = 0x%x",pCIDParams->ucManuID);

            /*
             * Device Type (CBX). Bits[113:112] in CID
             * This is mapped to bits [106:104] in the response register
             */
            pCIDParams->ucDevType = ((uiVal3 & _DEVTYPE_MASK) >> 8);
            _SEQ_DBG_INFO("Device Type = 0x%x",pCIDParams->ucDevType);

            /*
             * OEM/Application ID (OID). Bits[111:104] in CID
             * This is mapped to bits [103:96] in the response register
             */
            pCIDParams->ucOID = (uiVal3 & _OID_MASK);
            _SEQ_DBG_INFO("OEM/Application ID = 0x%x",pCIDParams->ucOID);

            /*
             * Product Name (PNM). Bits[103:56] in CID
             * This is mapped to bits [95:48] in the response register
             */
            pCIDParams->ucPdtName[5]  = ((uiVal2 & _PDTNAME_OFST0_MASK) >> 24);
            pCIDParams->ucPdtName[4]  = ((uiVal2 & _PDTNAME_OFST1_MASK) >> 16);
            pCIDParams->ucPdtName[3]  = ((uiVal2 & _PDTNAME_OFST2_MASK) >> 8);
            pCIDParams->ucPdtName[2]  = ((uiVal2 & _PDTNAME_OFST3_MASK));
            pCIDParams->ucPdtName[1]  = ((uiVal1 & _PDTNAME_OFST0_MASK) >> 24);
            pCIDParams->ucPdtName[0]  = ((uiVal1 & _PDTNAME_OFST1_MASK) >> 16);
           _SEQ_DBG_INFO("Product Name[0] = 0x%x",pCIDParams->ucPdtName[0]);
           _SEQ_DBG_INFO("Product Name[1] = 0x%x",pCIDParams->ucPdtName[1]);
           _SEQ_DBG_INFO("Product Name[2] = 0x%x",pCIDParams->ucPdtName[2]);
           _SEQ_DBG_INFO("Product Name[3] = 0x%x",pCIDParams->ucPdtName[3]);
           _SEQ_DBG_INFO("Product Name[4] = 0x%x",pCIDParams->ucPdtName[4]);
           _SEQ_DBG_INFO("Product Name[5] = 0x%x",pCIDParams->ucPdtName[5]);

            /*
             * Product Revision (PRV). Bits[55:48] in CID
             * This is mapped to bits [47:40] in the response register
             */
            pCIDParams->ucPdtRev = ((uiVal1 & _PDTREV_MASK) >> 8);
            _SEQ_DBG_INFO("Product Revision = 0x%x",pCIDParams->ucPdtRev);

            /*
             * Product Serial Number (PSN). Bits[47:16] in CID
             * This is mapped to bits [39:8] in the response register
             */
            uiTempVar1 = ((uiVal1 & _PDTSINO_OFST1_MASK) << 24);
            uiTempVar2 = ((uiVal0 & _PDTSINO_OFST2_MASK) >> 8);
            pCIDParams->uiPdtSlNo = uiTempVar1 | uiTempVar2;
            _SEQ_DBG_INFO("Product Serial Number = 0x%x",pCIDParams->uiPdtSlNo);

            /*
             * Manufacturing Date (MDT). Bits[15:8] in CID
             * This is mapped to bits [7:0] in the response register
             */
            pCIDParams->ucManuDt = (uiVal0 & _MANUDT_MASK);
            _SEQ_DBG_INFO("Manufacturing Date = 0x%x",pCIDParams->ucManuDt);

        break;

        /* CMD9 gives CSD as R2 response */
        case _CSD:

           /* Get the global CSD structure address */
            pCSDParams = &seq_tCSDParams[uiSlot];

            /*
             * Read CSD Version (CSD_STRUCTURE). Bits[127:126] in CSD
             * This is mapped to bits [119:118] in the response register
             */
            pCSDParams->ucCSDVer = ((uiVal3 & _CSD_STRUCT_MASK) >> 22);
            _SEQ_DBG_INFO("CSD Version = 0x%x",pCSDParams->ucCSDVer);

           /*
            * Read System Spec Version (SPEC_VERS). Bits[125:122] in CSD
            * This is mapped to bits [117:114] in the response register
            */
             pCSDParams->ucSpecsVer = ((uiVal3 & _SPEC_VERS_MASK) >> 18);
            _SEQ_DBG_INFO("System Spec Version = 0x%x",pCSDParams->ucSpecsVer);

           /*
            * Data Read Access Time 1 (TAAC). Bits[119:112] in CSD
            * This is mapped to bits [111:104] in the response register
            */
            pCSDParams->ucTAAC= ((uiVal3 & _TAAC_MASK) >> 8);
            _SEQ_DBG_INFO("TAAC = 0x%x",pCSDParams->ucTAAC);

            /*
             * Data Read Access Time 2 for Clock (NSAC). Bits[111:104] in CSD
             * This is mapped to bits [103:96] in the response register
             */
            pCSDParams->ucNSAC = (uiVal3 & _NSAC_MASK);
            _SEQ_DBG_INFO("NSAC = 0x%x",pCSDParams->ucNSAC);

            /*
             * Read Transfer Speed (TRAN_SPEED). Bits[103:96] in CSD
             * This is mapped to bits [95:88] in the response register
             */
            pCSDParams->ucTrnsSpeed = ((uiVal2 & _TRANS_SPEED_MASK) >> 24);
            _SEQ_DBG_INFO("Transfer Speed = 0x%x",pCSDParams->ucTrnsSpeed);

            /*
             * Read Device Command (CCC). Bits[95:84] in CSD
             * This is mapped to bits [87:76] in the response register
             */
            pCSDParams->usCCC = ((uiVal2 & _DEV_CCC_MASK) >> 12);
            _SEQ_DBG_INFO("Device Command Class = 0x%x",pCSDParams->usCCC);

            /*
             * Max Read Data Block Length (READ_BL_LEN). Bits[83:80] in CSD
             * This is mapped to bits [75:72] in the response register
             */
            pCSDParams->ucRdBlkLen = ((uiVal2 & _RDBLKLEN_MASK) >> 8);
            _SEQ_DBG_INFO("Read Data BLK Lengths = 0x%x",pCSDParams->ucRdBlkLen);

            /*
             * Partial Blocks For Read Allowed (READ_BL_PARTIAL). Bits[79:79] in CSD
             * This is mapped to bits [71:71] in the response register
             */
            pCSDParams->ucPartRdBlkEn = ((uiVal2 & _RDPARTBLK_MASK) >> 7);
            _SEQ_DBG_INFO("Read BLK Partial = 0x%x",pCSDParams->ucPartRdBlkEn);

            /*
             * Write Block Misalignment (WRITE_BLK_MISALIGN). Bits[78:78] in CSD
             * This is mapped to bits [70:70] in the response register
             */
            pCSDParams->ucWrMisalign = ((uiVal2 & _WRBLKMISALIGN_MASK) >> 6);
            _SEQ_DBG_INFO("Write BLK Misalign = 0x%x",pCSDParams->ucWrMisalign);

            /*
             * Read Block Misalignment (READ_BLK_MISALIGN). Bits[77:77] in CSD
             * This is mapped to bits [69:69] in the response register
             */
            pCSDParams->ucRdMisalign = ((uiVal2 & _RDBLKMISALIGN_MASK) >> 5);
            _SEQ_DBG_INFO("Read BLK Misalign = 0x%x",pCSDParams->ucRdMisalign);

            /*
             * DSR Implemented (DSR_IMP). Bits[76:76] in CSD
             * This is mapped to bits [68:68] in the response register
             */
            pCSDParams->ucDSRImp = ((uiVal2 & _DSRIMPL_MASK) >> 4);
            _SEQ_DBG_INFO("DSR Implemented = 0x%x",pCSDParams->ucDSRImp);

            /*
             * Device Size (C_SIZE). Bits[73:62] in CSD
             * This is mapped to bits [65:54] in the response register
             */
            uiTempVar1 = ((uiVal2 & _DEVSIZE_OFST1_MASK) << 10);
            uiTempVar2 = ((uiVal1 & _DEVSIZE_OFST2_MASK) >> 22);

            pCSDParams->usCSize = uiTempVar2 | uiTempVar1;
            _SEQ_DBG_INFO("Device Size (C_SIZE) = 0x%x",pCSDParams->usCSize);

            /*
             * Read Min Current (VDD_R_CURR_MIN). Bits[61:59] in CSD
             * This is mapped to bits [53:51] in the response register
             */
            pCSDParams->ucRdMinCurr = ((uiVal1 & _RDMINCURR_MASK) >> 19);
            _SEQ_DBG_INFO("Read VDD Min Current = 0x%x",pCSDParams->ucRdMinCurr);

            /*
             * Read Max Current (VDD_R_CURR_MAX). Bits[58:56] in CSD
             * This is mapped to bits [50:48] in the response register
             */
            pCSDParams->ucRdMaxCurr = ((uiVal1 & _RDMAXCURR_MASK) >> 16);
            _SEQ_DBG_INFO("Read VDD Max Current = 0x%x",pCSDParams->ucRdMaxCurr);

            /*
             * Write Min Current (VDD_W_CURR_MIN). Bits[55:53] in CSD
             * This is mapped to bits [47:45] in the response register
             */
            pCSDParams->ucWrMinCurr = ((uiVal1 & _WRMINCURR_MASK) >> 13);
            _SEQ_DBG_INFO("Write VDD Min Current = 0x%x",pCSDParams->ucWrMinCurr);

            /*
             * Write Max Current (VDD_W_CURR_MAX). Bits[52:50] in CSD
             * This is mapped to bits [44:42] in the response register
             */
            pCSDParams->ucWrMaxCurr = ((uiVal1 & _WRMAXCURR_MASK) >> 10);
            _SEQ_DBG_INFO("Write VDD Max Current = 0x%x",pCSDParams->ucWrMaxCurr);

            /*
             * Device Size Multplier (C_SIZE_MULT). Bits[49:47] in CSD
             * This is mapped to bits [41:39] in the response register
             */
            pCSDParams->ucCsizeMult = ((uiVal1 & _CSIZEMULT_MASK) >> 7);
            _SEQ_DBG_INFO("Device Size Multiplier = 0x%x",pCSDParams->ucCsizeMult);

            /*
             * Erase Group Size (ERASE_GRP_SIZE). Bits[46:42] in CSD
             * This is mapped to bits [38:34] in the response register
             */
            pCSDParams->ucEraseGrpSiz = ((uiVal1 & _ERASEGRPSIZE_MASK) >> 2);
            _SEQ_DBG_INFO("Erase Group Size = 0x%x",pCSDParams->ucEraseGrpSiz);

            /*
             * Erase Group Size Multiplier (ERASE_GRP_MULT). Bits[41:37] in CSD
             * This is mapped to bits [33:29] in the response register
             */
            ucTempVar1 = ((uiVal1 & _ERASEGRPMUL_OFST1_MASK) << 3);
            ucTempVar2 = ((uiVal0 & _ERASEGRPMUL_OFST2_MASK) >> 29);
            pCSDParams->ucEraseGrpMul = ucTempVar1 | ucTempVar2;
            _SEQ_DBG_INFO("Erase Group Size Multiplier = 0x%x",pCSDParams->ucEraseGrpMul);

            /*
             * Write Group Protect Size (WP_GRP_SIZE). Bits[36:32] in CSD
             * This is mapped to bits [28:24] in the response register
             */
            pCSDParams->ucWPGrpSize = ((uiVal0 & _WPGRPSIZE_MASK) >> 24);
            _SEQ_DBG_INFO("Write Protect Group Size = 0x%x",pCSDParams->ucWPGrpSize);

            /*
             * Write Group Protect Enable (WP_GRP_ENABLE). Bits[31:31] in CSD
             * This is mapped to bits [23:23] in the response register
             */
            pCSDParams->ucWPEnable = ((uiVal0 & _WPGRPENABLE_MASK) >> 23);
            _SEQ_DBG_INFO("Write Protect Group Enable = 0x%x",pCSDParams->ucWPEnable);

            /*
             * Manufacturer default ECC (DEFAULT_ECC). Bits[30:29] in CSD
             * This is mapped to bits [22:21] in the response register
             */
            pCSDParams->ucDefECC = ((uiVal0 & _DEFAULTECC_MASK) >> 21);
            _SEQ_DBG_INFO("Default ECC = 0x%x",pCSDParams->ucDefECC);

            /*
             * Write Speed Factor (R2W_FACTOR). Bits[29:26] in CSD
             * This is mapped to bits [20:18] in the response register
             */
            pCSDParams->ucR2WFactor = ((uiVal0 & _R2WFACTOR_MASK) >> 18);
            _SEQ_DBG_INFO("Write Speed Factor (R2WFactor) = 0x%x",pCSDParams->ucR2WFactor);

            /*
             * Max Write Data Block Length (WRITE_BL_LEN). Bits[25:22] in CSD
             * This is mapped to bits [17:14] in the response register
             */
            pCSDParams->ucWrBlkLen = ((uiVal0 & _WRBLKLEN_MASK) >> 14);
            _SEQ_DBG_INFO("Max Write Data Block Length = 0x%x",pCSDParams->ucWrBlkLen);

            /*
             * Partial Block For Write Allowed (WRITE_BL_PARTIAL). Bits[21:21] in CSD
             * This is mapped to bits [13:13] in the response register
             */
            pCSDParams->ucPartWrBlkEn = ((uiVal0 & _WRBLPART_MASK) >> 13);
            _SEQ_DBG_INFO("Partial Blocks For Write Allowed = 0x%x",pCSDParams->ucPartWrBlkEn);

            /*
             * Contents Protection Application (CONTENT_PROT_APP). Bits[16:16] in CSD
             * This is mapped to bits [8:8] in the response register
             */
            pCSDParams->ucContProtEn = ((uiVal0 & _CONTPROTAPP_MASK) >> 8);
            _SEQ_DBG_INFO("Content Protection Application = 0x%x",pCSDParams->ucContProtEn);

            /*
             * File Format Group (FILE_FORMAT_GRP). Bits[15:15] in CSD
             * This is mapped to bits [7:7] in the response register
             */
            pCSDParams->ucFileFormGrp = ((uiVal0 & _FILEFORMATGRP_MASK) >> 7);
            _SEQ_DBG_INFO("File Format Group = 0x%x",pCSDParams->ucFileFormGrp);

            /*
             * Copy Flag(OTP) (COPY). Bits[14:14] in CSD
             * This is mapped to bits [6:6] in the response register
             */
            pCSDParams->ucCopy = ((uiVal0 & _COPY_MASK) >> 6);
            _SEQ_DBG_INFO("Copy Flag (OTP) = 0x%x",pCSDParams->ucCopy);

            /*
             * Permanent Write Protection (PERM_WRITE_PROTECT). Bits[13:13] in CSD
             * This is mapped to bits [5:5] in the response register
             */
            pCSDParams->ucPermWP = ((uiVal0 & _PERMWRPROT_MASK) >> 5);
            _SEQ_DBG_INFO("Permanent Write Protection = 0x%x",pCSDParams->ucPermWP);

            /*
             * Temporary Write Protection (TEMP_WRITE_PROTECT). Bits[12:12] in CSD
             * This is mapped to bits [4:4] in the response register
             */
            pCSDParams->ucTempWP = ((uiVal0 & _TEMPWRPROT_MASK) >> 4);
            _SEQ_DBG_INFO("Temporary Write Protection = 0x%x",pCSDParams->ucTempWP);

            /*
             * File Format (FILE_FORMAT). Bits[11:10] in CSD
             * This is mapped to bits [3:2] in the response register
             */
            pCSDParams->ucFileFormat = ((uiVal0 & _FILEFORMAT_MASK) >> 2);
            _SEQ_DBG_INFO("File Format = 0x%x\n",pCSDParams->ucFileFormat);

            /*
             * ECC Code (ECC). Bits[9:8] in CSD
             * This is mapped to bits [1:0] in the response register
             */
            pCSDParams->ucECC = (uiVal0 & _ECC_MASK);
            _SEQ_DBG_INFO("ECC Code = 0x%x",pCSDParams->ucECC);

            /*
             * Storing the contents of CSD - used for CRC calculation for
             * writing into CSD register
             */
            seq_crcBuf[3] = uiVal0 << 8;
            seq_crcBuf[2] = (uiVal1 << 8) | ((uiVal0 >> 24) & 0xFF);
            seq_crcBuf[1] = (uiVal2 << 8) | ((uiVal1 >> 24) & 0xFF);
            seq_crcBuf[0] = (uiVal3 << 8) | ((uiVal2 >> 24) & 0xFF );

            _SEQ_DBG_INFO("crc : 0x%x %x %x %x",
                seq_crcBuf[3],seq_crcBuf[2],
                seq_crcBuf[1],seq_crcBuf[0]);

        break;

        default:
        break;
    }

}

/**
 * @brief Function to parse R3 response and store OCR details
 *
 * @param[in] puiRespVal Pointer to response data
 * @param[out] pOCRParams Pointer to struct variable for OCR details.
 *
 * @retval None
 */
static inline void parseR3Resp(
    _ub32 *puiRespVal,
    ocr_params_t *pOCRParams)
{
    /* Input arguments are not verified as it will be done by caller */

    /* Store the OCR register fields in the structure */
    pOCRParams->ucVolt1_95 = ((*puiRespVal >> 7) & 0x0001U);
    pOCRParams->ucVolt2_6 = ((*puiRespVal >> 8) & 0x007FU);
    pOCRParams->ucVolt3_6 = ((*puiRespVal >> 15) & 0x07F8U);
    pOCRParams->ucAccessMode = ((*puiRespVal >> 29) & 0x0006U);
}

/**
 * @brief Func to read EXT CSD register value thru' buffer data port after CMD8
 *
 * @param[in] Intr Handler arg pointer. extcsdinfo_t struct in this case
 *
 * @retval None
 */
static void readExtCSD(void *ptr)
{
    _ub32 i = 0;
    extcsdinfo_t *pExtCSD;
    _ub32 uiSlot;
    _ub32 *pBuf;

    /* Input arguments are not verified as it will be done by caller */

    pExtCSD = (extcsdinfo_t *)ptr;
    uiSlot = pExtCSD->uiSlot;

    /* Get the buffer pointer */
    pBuf = (_ub32*)(pExtCSD->ucBuf);

    /* Copy 512 bytes from internal buffer */
    for(i = 0; ((IS_BUF_RD_READY(uiSlot)) && (i < _BLK_SIZE/4)); i++)
    {
        /* Transfer data from the internal buffer to user buffer */
        *pBuf = hc_getBufDatPort(uiSlot);
        pBuf++; /* 32bit = 4bytes */
    }
}

/**
 * @brief Func to validate the Device state for a command
 *
 * @param[in] uiSlot: Slot number
 * @param[in] eIndex: Command index
 *
 * @retval dev_sts_e Return OK if state if fine, else error
 */
static dev_sts_e checkDeviceState(
    _ub32 uiSlot,
    cmd_index_e eIndex)
{
    _ub32 uiDevState = 0;
    dev_sts_e eSts = _DEV_STS_OK;
    _ub32 ucSttRetry = 0;

    /* Get the current device state */
    eSts = seq_getDevSts(uiSlot,&uiDevState);
    if(eSts != _DEV_STS_OK)
    {
        return eSts;
    }

    if(seq_ucLockState == 1)
    {
        switch(eIndex)
        {
            /* Allow Class 0 Commands */
            case _CMD0:
            case _CMD1:
            case _CMD2:
            case _CMD3:
            case _CMD4:
            case _CMD5:
            case _CMD6:
            case _CMD7:
            case _CMD8:
            case _CMD9:
            case _CMD10:
            case _CMD12:
            case _CMD13:
            case _CMD14:
            case _CMD15:
            case _CMD19:
            /* Allow Lock/UnLock Commands */
            case _CMD42:
            case _CMD16:

            break;

            default:
                _SEQ_DBG_ERR("seq_getDevSts returned error iS : 0x%08x\n",eSts);
                return _DEV_LOCKED;
            break;

        }
    }

    /* Loop until the device state is valid for the command */
    while(0 == (uiDevState & seq_tValidStates[eIndex]))
    {
        /* Get the current device state */
        eSts = seq_getDevSts(uiSlot, &uiDevState);
        if(_DEV_STS_OK != eSts)
        {
            _SEQ_DBG_ERR("Seq terminated-->seq_getDevSts:ret[0x%08x]\n", eSts);
            return eSts;
        }

        /* Left shift to required bit position */
        uiDevState = (1 << uiDevState );

        /* If max retry is exceeded, break out */
        if(ucSttRetry > _STATE_RETRY_MAX)
        {
            break;
        }

        /* Increment retry count */
        ucSttRetry++;

        /* Wait for 1us */
        os_delayUs(1);
    }

    /* If device state isn't proper after 5ms retry, return error */
    if(ucSttRetry > _STATE_RETRY_MAX)
    {
        _SEQ_DBG_ERR("Device is not in proper state for the cmd");
        return _DEV_DEVSTATE_ERR;
    }

    return eSts;
}

#ifdef __DEVERR_HANDLING
/**
 * @brief Func for device error handling. Brings device to Transfer state.
 *
 * @param[in] uiSlot: Slot number
 *
 * @retval None
 */
static void devErrHandling(_ub32 uiSlot)
{
    _ub32 uiState = 0;
    cmd_params_t tCmdParams;
    const cmd_info_t *pCmdInfo;
    _ub32 uiResp = 0;

    /* Get the current device state.
     * Error return from below function is ignored as there might be previous
     * device error bits updated in the status. We will be using only the
     * current state of the device.
     */
    seq_getDevSts(uiSlot,&uiState);
    uiState = (1 << uiState );
    _SEQ_DBG_INFO("Device state before error handling: 0x%08x", uiState);

    switch(uiState)
    {
        /*
         * NOTE: Device initialization mode states aren't considered here
         * as the control won't come here when a device error occurs during
         * initialization.
         */

        case _SLP_STATE:
            /* Form the params for CMD5 */
            tCmdParams.eIndex = _CMD5;
            pCmdInfo = &seq_tCmdInfoTbl[_CMD5];
            tCmdParams.eRespCtgy = pCmdInfo->eRespCtgy;
            tCmdParams.eDatUsage = pCmdInfo->eDatUsage;
            tCmdParams.uiArg = 0x00010000; /* RCA= 0x0001; Bit15=0 for awake */

            /* Send CMD5 to bring device to Standby state */
            cmd_sendCommand(uiSlot,&tCmdParams, &uiResp);

        case _STBY_STATE:
            /* Form the params for CMD7 */
            tCmdParams.eIndex = _CMD7;
            pCmdInfo = &seq_tCmdInfoTbl[_CMD7];
            tCmdParams.eRespCtgy = pCmdInfo->eRespCtgy;
            tCmdParams.eDatUsage = pCmdInfo->eDatUsage;
            tCmdParams.uiArg = 0x00010000; /* RCA= 0x0001; Bit15=0 for awake */

            /* Send CMD7 to bring device to Transfer state */
            cmd_sendCommand(uiSlot,&tCmdParams, &uiResp);
        break;

        case _SEND_STATE:
            /* Form the params for CMD12 */
            tCmdParams.eIndex = _CMD12;
            pCmdInfo = &seq_tCmdInfoTbl[_CMD12];
            tCmdParams.eRespCtgy = pCmdInfo->eRespCtgy;
            tCmdParams.eDatUsage = pCmdInfo->eDatUsage;
            tCmdParams.uiArg = 0x0;

            /* Send CMD12 to bring device to Transfer state */
            cmd_sendCommand(uiSlot,&tCmdParams, &uiResp);
        break;

        case _RECV_STATE:
            /* Form the params for CMD12 */
            tCmdParams.eIndex = _CMD12;
            pCmdInfo = &seq_tCmdInfoTbl[_CMD12];
            tCmdParams.eRespCtgy = _RESP_CTGY4; /* R1b for write case */
            tCmdParams.eDatUsage = pCmdInfo->eDatUsage;
            tCmdParams.uiArg = 0x0;

            /* Send CMD12 to bring device to Transfer state */
            cmd_sendCommand(uiSlot,&tCmdParams, &uiResp);
        break;

        /*
         * Bus-test, Programming and disconnect states are not considered
         * since they are just intermediate states, and going to transfer
         * state is automatically done by device from these states and
         * cannot be initiated. In future, if this needs to be extended the
         * same can be considered here.
         */
        case _PROG_STATE:
        case _DISC_STATE:
        case _BTST_STATE:
        break;

        default:
        break;
    }

    /* Check if device has come to Transfer state */
    seq_getDevSts(uiSlot,&uiState);
    uiState = (1 << uiState );
    _SEQ_DBG_INFO("Device state after error handling: 0x%08x", uiState);

    /* If device has not reached Transfer state print error message */
    if(_TRANS_STATE != uiState)
    {
        _SEQ_DBG_ERR("Error recovery failed! Please hard reset device");
    }
    else
    {
        _SEQ_DBG_ERR("Device is brought to transfer state!");
    }

    return;
}
#endif /* __DEVERR_HANDLING */

#ifdef __CRC7

/**
 * @brief Calculates CRC7 - unused currently
 *
 * @param[in] buffer - buffer pointer on which CRC7 calculation needs to be done
 * @param[in] count no of valid bytes in the buffer
 *
 *
 * @retval crc is returned [7-bits in length]
 *
 */
static char crc7(unsigned char *buffer, int count)
{
    int i, c, crc;
    crc = 0;
    while (count-- > 0)
    {
    c = *buffer++;
        for (i = 0; i < 8; i++)
        {
        crc <<= 1;
        if ((c ^ crc) & 0x80) crc ^= 0x9;
        c <<= 1;
        }
    }
    return (char)(crc & 0x7f);
}
#endif /* #ifdef __CRC7 */

/**
 * @brief Initializes seq layer and initializes eMMC device to standby state
 *
 * @param[in] pValidSlot List of slots marked valid/invalid by HC layer
 * @param[out] pValidSlot List of slots marked valid/invalid by Seq layer
 *
 * @retval _DEV_STS_OK Sequence executed successfully
 * @retval _DEV_INPUT_ERR Input param error
 * @retval _DEV_CMDLAYER_FAIL CMD layer init failed
 * @retval _DEV_CMDBUSY_ERR CMD sending failed as CMD/DAT line was busy
 * @retval _DEV_CMDSEND_ERR CMD sending failed - timeout/index/crc/endbit error
 * @retval _DEV_ILLEGAL_CMD_ERR Illegal command issued
 * @retval _DEV_CC_ERR Device undefined Error
 * @retval _DEV_ERR Device error related to last host cmd
 */
dev_sts_e seq_init(_ub32 *pValidSlot)
{
    dev_sts_e eSts = _DEV_STS_OK;
    _ub32 slotNo = 0;
    _ub32 hcBadCnt = 0;
    _ub32 seqBadCnt = 0;
    _ub32 uiVal = 0;
    _ub32 uiOffst = 0;
    _ub8 uiRegVal = 0;
    _ub8 *puiBuf;

    cmd_sts_e eCmdSts = _CMD_STS_OK;

    _SEQ_DBG_INFO("ENTRY");

    /* Clear the global structures */
    os_setMem(seq_tOCRParams, 0, sizeof(seq_tOCRParams));
    os_setMem(seq_tCIDParams, 0, sizeof(seq_tCIDParams));
    os_setMem(seq_tCSDParams, 0, sizeof(seq_tCSDParams));

    for(slotNo = 0; slotNo < _MAX_SLOTS; slotNo++)
    {
        if(_SLOT_INVALID == pValidSlot[slotNo])
        {
            /* Increment the invalid slot cnt from HC */
            hcBadCnt++;
            eSts = _DEV_INPUT_ERR;

            /* Continue to next slot */
            continue;
        }

        /* Initialize the command layer */
        eCmdSts = cmd_init(slotNo);
        if(_CMD_STS_OK != eCmdSts)
        {
            _SEQ_DBG_ERR("cmd_init[Slot%d]: ERROR 0x%08x\n", slotNo, eCmdSts);
            pValidSlot[slotNo] = _SLOT_INVALID;
            eSts = _DEV_CMDLAYER_FAIL;
            seqBadCnt++;
            continue;
        }

        /* Initialize struct for EXTCSD buf */
        seq_tEXTCSDInfo[slotNo].uiSlot = slotNo;
        os_setMem(
            seq_tEXTCSDInfo[slotNo].ucBuf,
            0,
            sizeof(seq_tEXTCSDInfo[slotNo].ucBuf));


        /* Execute init sequence for card to bring the device to Standby state */
        eSts = executeSequence(slotNo, _SEQ_ID_INIT);
        if(_DEV_STS_OK != eSts)
        {
            pValidSlot[slotNo] = _SLOT_INVALID;
            seqBadCnt++;
            continue;
        }

        /* Execute config sequence for card to bring it to Transfer state */
        eSts = seq_configDevice(slotNo);
        if(_DEV_STS_OK != eSts)
        {
            pValidSlot[slotNo] = _SLOT_INVALID;
            seqBadCnt++;
            continue;
        }
        /* Set erase group def bit if partition is done */
        puiBuf = &seq_tEXTCSDInfo[slotNo].ucBuf[0];
        if(1 == (puiBuf[_EXTCSD_PART_COMPLETED_OFST] & 0x01))
        {
            uiOffst = _EXTCSD_ERASE_GROUP_DEF_OFST;
            uiRegVal = puiBuf[uiOffst];
            uiRegVal = (uiRegVal & (~(_ERASE_GRP_DEF_MASK)));
            uiRegVal |= 1;
            uiVal = (_ub32)uiRegVal;
            eSts = seq_writeExtCSD(slotNo,uiOffst,uiVal);
            if(_DEV_STS_OK != eSts)
            {
                _SEQ_DBG_ERR("seq_accessPartitions:Set ERASE GRP DEF Bit Fail");
                return eSts;
            }
        }
    }

    /* If at least one slot is valid, return status OK */
    if((hcBadCnt + seqBadCnt) < _MAX_SLOTS)
    {
        eSts = _DEV_STS_OK;
    }
    _SEQ_DBG_INFO("EXIT");

    return eSts;
}

/**
 * @brief Reads CSD, CID info and brings the eMMC device to Transfer state
 *
 * IMPT NOTE: This func should be called in PIO mode only as EXT CSD reading is
 * to be done in PIO mode. Changing of mode to SDMA/ADMA2 should be done after
 * this function is called.
 *
 * @param[in] uiSlot Host Controller slot number
 *
 * @retval _DEV_STS_OK Sequence executed successfully
 * @retval _DEV_INPUT_ERR Input param error
 * @retval _DEV_CMDBUSY_ERR CMD sending failed as CMD/DAT line was busy
 * @retval _DEV_CMDSEND_ERR CMD sending failed - timeout/index/crc/endbit error
 * @retval _DEV_BLK_LEN_ERR Block length error occurred
 * @retval _DEV_ILLEGAL_CMD_ERR Illegal command issued
 * @retval _DEV_CC_ERR Device undefined Error
 * @retval _DEV_ERR Device error related to last host cmd
 */
dev_sts_e seq_configDevice(_ub32 uiSlot)
{
    dev_sts_e eSts = _DEV_STS_OK;
    intr_sts_e eIntrSts = _INTR_OK;

    _SEQ_DBG_INFO("ENTRY");

    /*
     * Execute config sequence for card:
     * a. Read CSD, CID info and store in respective structures
     * b. Bring the device from Standby to Transfer state.
     */
    eSts = executeSequence(uiSlot, _SEQ_ID_CONFIG);
    if(_DEV_STS_OK != eSts)
    {
        _SEQ_DBG_ERR("Input slot invalid!");
        return eSts;
    }
    /*
     * HC setting to read EXT_CSD (512 bytes)
     *
     * Transfer direction: _COM_DIR_R(Read from card to host)
     * Data transfer size: 512 bytes
     */
    hc_setDataParams(uiSlot, _EXTCSD_SIZE, _COM_DIR_R);


    /* Register read handler for PIO mode for reading EXT CSD */
    eIntrSts = intr_registerHdlr(
        _NORM_INTR_RD_PIO,
        readExtCSD,
        (void *)&seq_tEXTCSDInfo[uiSlot],
        uiSlot);
    if(_INTR_OK != eIntrSts)
    {
        _SEQ_DBG_ERR("Seq layer interrupt handler registration failed");
        eSts = _DEV_INTR_FAIL;
    }
    else
    {
        /* Read EXT CSD from device using CMD8 */
        eSts = executeSequence(uiSlot, _SEQ_ID_EXTCSD);

        /* De-register interrupt handler for PIO mode for reading EXT CSD */
        eIntrSts = intr_deregisterHdlr(_NORM_INTR_RD_PIO, uiSlot);
        if(_INTR_OK != eIntrSts)
        {
            _SEQ_DBG_ERR("Seq layer interrupt handler de-registration failed");
            eSts = _DEV_INTR_FAIL;
        }
    }

    _SEQ_DBG_INFO("EXIT");

    return eSts;
}

/**
 * @brief Reads the specified size of data from device
 *
 * @param[in] uiSlot Host controller Slot no
 * @param[in] uiDevAddr Device address to read the data from
 * @param[in] uiSize 512-byte aligned size of data to be read
 *
 * @retval _DEV_STS_OK Sequence executed successfully
 * @retval _DEV_INPUT_ERR Input param error
 * @retval _DEV_CMDBUSY_ERR CMD sending failed as CMD/DAT line was busy
 * @retval _DEV_CMDSEND_ERR CMD sending failed - timeout/index/crc/endbit error
 * @retval _DEV_ADDR_OUT_OF_RANGE Address out of Range error occurred
 * @retval _DEV_ADDR_MISALIGN Address misalign error occurred
 * @retval _DEV_BLK_LEN_ERR Block length error occurred
 * @retval _DEV_ILLEGAL_CMD_ERR Illegal command issued
 * @retval _DEV_ECC_FAIL Device ECC failed
 * @retval _DEV_CC_ERR Device undefined Error
 * @retval _DEV_ERR Device error related to last host cmd
 * @retval _DEV_TIMEOUT_ERR Sequence timed out
 * @retval _DEV_WQ_FAIL Wait-queue event failed
 */
dev_sts_e seq_readData(_ub32 uiSlot, _ub32 uiDevAddr, _ub32 uiSize)
{
    _ub32 uiNumBlk = 1;
    cmd_frm_t *pCmdSeq;
    dev_sts_e eSts = _DEV_STS_OK;

    _SEQ_DBG_INFO("ENTRY");

    /* Input params not validated as it is done by upper layer */

    /* Calculate the number of blocks */
    uiNumBlk = (uiSize/_BLK_SIZE);

    /* Get the seq table row for Read sequence */
    pCmdSeq = seq_tCmdSeqTbl[_SEQ_ID_READ];

    _SEQ_DBG_INFO("block count dev: %d", uiNumBlk);

    /* Format the arguments for read commands. */
    /* Set num of blocks for CMD23(Set block count CMD) */
    pCmdSeq[0].uiArg |= (uiNumBlk & 0xFFFF);

    /* Set device address for CMD18(Multi block Read command) */
    pCmdSeq[1].uiArg |= uiDevAddr;

    /* Execute the read sequence */
    eSts = executeSequence(uiSlot, _SEQ_ID_READ);
    if(_DEV_STS_OK != eSts)
    {
        _SEQ_DBG_ERR("Read Sequence failed");
    }

    /* Restore default argument values in seq table to 0 */
    pCmdSeq[0].uiArg = 0;
    pCmdSeq[1].uiArg = 0;

    _SEQ_DBG_INFO("EXIT");

    return eSts;
}

/**
 * @brief Writes the specified size of data to the device
 *
 * @param[in] uiSlot Host controller Slot no
 * @param[in] uiDevAddr Device address to write the data to
 * @param[in] uiSize 512-byte aligned size of data to be written
 *
 * @retval _DEV_STS_OK Sequence executed successfully
 * @retval _DEV_INPUT_ERR Input param error
 * @retval _DEV_CMDBUSY_ERR CMD sending failed as CMD/DAT line was busy
 * @retval _DEV_CMDSEND_ERR CMD sending failed - timeout/index/crc/endbit error
 * @retval _DEV_ADDR_OUT_OF_RANGE Address out of Range error occurred
 * @retval _DEV_ADDR_MISALIGN Address misalign error occurred
 * @retval _DEV_BLK_LEN_ERR Block length error occurred
 * @retval _DEV_WP_VIOLATION_ERR WP violation occurred
 * @retval _DEV_ILLEGAL_CMD_ERR Illegal command issued
 * @retval _DEV_ECC_FAIL Device ECC failed
 * @retval _DEV_CC_ERR Device undefined Error
 * @retval _DEV_ERR Device error related to last host cmd
 */
dev_sts_e seq_writeData(_ub32 uiSlot, _ub32 uiDevAddr, _ub32 uiSize)
{
    _ub32 uiNumBlk = 1;
    cmd_frm_t *pCmdSeq;
    dev_sts_e eSts = _DEV_STS_OK;

    _SEQ_DBG_INFO("ENTRY");

    /* Input params not validated as it is done by upper layer */

    /* Calculate the number of blocks */
    uiNumBlk = (uiSize/_BLK_SIZE);

    /* Get the seq table row for Write sequence */
    pCmdSeq = seq_tCmdSeqTbl[_SEQ_ID_WRITE];

    _SEQ_DBG_INFO("block count dev: %d", uiNumBlk);

    /* Format the arguments for read commands. */
    /* Set num of blocks for CMD23(Set block count CMD) */
    pCmdSeq[0].uiArg |= (uiNumBlk & 0xFFFF);

    /* Set device address for CMD25(Multi block Write command) */
    pCmdSeq[1].uiArg |= uiDevAddr;

    /* Execute the write sequence */
    eSts = executeSequence(uiSlot, _SEQ_ID_WRITE);
    if(_DEV_STS_OK != eSts)
    {
        _SEQ_DBG_ERR("Write Sequence failed");
    }

    /* Restore default argument values to 0 */
    pCmdSeq[0].uiArg = 0;
    pCmdSeq[1].uiArg = 0;

    _SEQ_DBG_INFO("EXIT");

    return eSts;
}


/**
 * @brief Sets bus width on the device side
 *
 * @param[in] uiSlot Host controller Slot no
 * @param[in] eBusWidth Bus width mode to be set
 *
 * @retval _DEV_STS_OK Sequence executed successfully
 * @retval _DEV_INPUT_ERR Input param error
 * @retval _DEV_CMDBUSY_ERR CMD sending failed as CMD/DAT line was busy
 * @retval _DEV_CMDSEND_ERR CMD sending failed: timeout/index/crc/endbit error
 * @retval _DEV_ILLEGAL_CMD_ERR Illegal command issued
 * @retval _DEV_CC_ERR Device undefined Error
 * @retval _DEV_ERR Device error related to last host cmd
 * @retval _DEV_SWITCH_ERR Switch command failed
 */
dev_sts_e seq_setBuswidth(_ub32 uiSlot, com_busWidth_e eBusWidth)
{
    dev_sts_e eSts = _DEV_STS_OK;
    cmd_frm_t *pCmdSeq;

    _SEQ_DBG_INFO("ENTRY");

    /* If bus width is not valid, return error */
    if((eBusWidth < _COM_BWIDTH_MIN) || (eBusWidth >= _COM_BWIDTH_INVALID))
    {
        return _DEV_INPUT_ERR;
    }

    /* Retrieve the Switch sequence from the sequence table */
    pCmdSeq = seq_tCmdSeqTbl[_SEQ_ID_SWITCH];

    /* Form the argument for Switch command based on bus-width */
    switch(eBusWidth)
    {
        case _COM_BWIDTH_1:
            pCmdSeq[0].uiArg = _BUS_WIDTH_1BIT;
        break;

        case _COM_BWIDTH_4:
            pCmdSeq[0].uiArg = _BUS_WIDTH_4BIT;
        break;

        case _COM_BWIDTH_8:
            pCmdSeq[0].uiArg = _BUS_WIDTH_8BIT;
        break;

        default:
            pCmdSeq[0].uiArg = _BUS_WIDTH_1BIT;
        break;
    }

    /* Execute the switch sequence */
    eSts = executeSequence(uiSlot, _SEQ_ID_SWITCH);

    /* Restore default argument value in table to 0 */
    pCmdSeq[0].uiArg = 0;

    _SEQ_DBG_INFO("EXIT");

    return eSts;
}

/**
 * @brief Sets bus speed mode on the device side.
 *
 * IMPT NOTE: Before setting freq > 25MHz on host side, set speed to HS
 * on device side. Default speed is set to Normal
 *
 * @param[in] uiSlot Host controller Slot no
 * @param[in] eBusSpeed Bus speed mode to be set
 *
 * @retval _DEV_STS_OK Sequence executed successfully
 * @retval _DEV_INPUT_ERR Input param error
 * @retval _DEV_CMDBUSY_ERR CMD sending failed as CMD/DAT line was busy
 * @retval _DEV_CMDSEND_ERR CMD sending failed: timeout/index/crc/endbit error
 * @retval _DEV_ILLEGAL_CMD_ERR Illegal command issued
 * @retval _DEV_CC_ERR Device undefined Error
 * @retval _DEV_ERR Device error related to last host cmd
 * @retval _DEV_SWITCH_ERR Switch command failed
 */
dev_sts_e seq_setSpeed(_ub32 uiSlot, com_busSpeed_e eBusSpeed)
{
    dev_sts_e eSts = _DEV_STS_OK;
    cmd_frm_t *pCmdSeq;

    _SEQ_DBG_INFO("ENTRY");

    /* If bus speed is not valid, return error */
    if((eBusSpeed < _COM_SPEED_NORMAL) || (eBusSpeed > _COM_SPEED_HS200))
    {
        return _DEV_INPUT_ERR;
    }

    /* Retrieve the Switch sequence from the sequence table */
    pCmdSeq = seq_tCmdSeqTbl[_SEQ_ID_SWITCH];

    /* Form the argument for Switch command based on bus-speed mode */
    switch(eBusSpeed)
    {
        case _COM_SPEED_NORMAL:
            pCmdSeq[0].uiArg = _BUS_SPEED_NORMAL;
        break;

        case _COM_SPEED_HIGH:
            pCmdSeq[0].uiArg = _BUS_SPEED_HIGH;
        break;

        case _COM_SPEED_HS200:
            pCmdSeq[0].uiArg = _BUS_SPEED_HS200;
        break;

        default:
            pCmdSeq[0].uiArg = _BUS_SPEED_NORMAL;
        break;
    }

    /* Execute the switch sequence */
    eSts = executeSequence(uiSlot, _SEQ_ID_SWITCH);

    /* Restore default argument value in table to 0 */
    pCmdSeq[0].uiArg = 0;

    _SEQ_DBG_INFO("EXIT");

    return eSts;
}

/**
 * @brief Sets the reqd fields of extended CSD register of the device.
 *
 * @param[in] uiSlot Host controller Slot no
 * @param[in] uiOfst Offset of Ext CSD register field to be written
 * @param[in] uiValue Value to be written to the specified byte offset
 *
 * @retval _DEV_STS_OK Sequence executed successfully
 * @retval _DEV_INPUT_ERR Input param error
 * @retval _DEV_CMDBUSY_ERR CMD sending failed as CMD/DAT line was busy
 * @retval _DEV_CMDSEND_ERR CMD sending failed: timeout/index/crc/endbit error
 * @retval _DEV_ILLEGAL_CMD_ERR Illegal command issued
 * @retval _DEV_CC_ERR Device undefined Error
 * @retval _DEV_ERR Device error related to last host cmd
 * @retval _DEV_SWITCH_ERR Switch command failed
 */
dev_sts_e seq_writeExtCSD(_ub32 uiSlot, _ub32 uiOfst, _ub32 uiValue)
{
    dev_sts_e eSts = _DEV_STS_OK;
    cmd_frm_t *pCmdSeq;
    _ub32 val = 0;

    _SEQ_DBG_INFO("ENTRY");

    /* If ofst is out of Modes Segment(Bits[191:0]) of EXT CSD, return error */
    if(uiOfst >= _EXTCSD_NUMBYTES)
    {
        _SEQ_DBG_ERR("ERR: Field requested is out of Modes Segment of EXTCSD");
        return _DEV_INPUT_ERR;
    }

    /* If the offset requested is a read-only field, return error */
    if(_R == seq_tExtCSDTbl[uiOfst])
    {
        _SEQ_DBG_ERR("ERR: EXTCSD field requested is Read-only");
        return _DEV_INPUT_ERR;
    }

/* For partition creation OTP has to be relaxed */
#ifndef __OTP
    /* If the offset requested is an OTP field, return error */
    if((_W == seq_tExtCSDTbl[uiOfst]) || (_RW == seq_tExtCSDTbl[uiOfst]))
    {
        _SEQ_DBG_ERR("ERR: EXTCSD field requested is OTP");
        return _DEV_INPUT_ERR;
    }
#endif

    /* If reserved field return error */
    if(_RSVD == seq_tExtCSDTbl[uiOfst])
    {
        _SEQ_DBG_ERR("ERR: EXTCSD field requested is Reserved");
        return _DEV_INPUT_ERR;
    }

    /* Retrieve the Switch sequence from the sequence table */
    pCmdSeq = seq_tCmdSeqTbl[_SEQ_ID_SWITCH];

    /* Form the argument for Switch command based on the input */
    val = _CMD6_ACCS_MASK;
    val |= ((uiOfst << 16) & _CMD6_OFST_MASK);
    val |= ((uiValue << 8) & _CMD6_VAL_MASK);
    pCmdSeq[0].uiArg = val;

    /* Execute the switch sequence */
    eSts = executeSequence(uiSlot, _SEQ_ID_SWITCH);

    /*
     * If SWITCH command is successful, update the value to internal ExtCSD
     * buffer so that reading ExtCSD again can be avoided.
     */
    if(_DEV_STS_OK == eSts)
    {
        seq_tEXTCSDInfo[uiSlot].ucBuf[uiOfst] = uiValue;
    }

    /* Restore default argument value in table to 0 */
    pCmdSeq[0].uiArg = 0;

    _SEQ_DBG_INFO("EXIT");

    return eSts;
}

/**
 * @brief Writes into CSD area.
 *
 * @param[in] uiSlot Host controller Slot no
 * @param[in] uiMask - bit positions to be set/cleared
 * @param[in] uisetclr -set or clear the bit positions
 * @param[in] piobuf -buffer containing the CSD contents

 * @retval _DEV_STS_OK Sequence executed successfully
 * @retval _DEV_INPUT_ERR Input param error
 * @retval _DEV_CMDBUSY_ERR CMD sending failed as CMD/DAT line was busy
 * @retval _DEV_CMDSEND_ERR CMD sending failed: timeout/index/crc/endbit error
 * @retval _DEV_DEV_ILLEGAL_CMD_ERR Illegal command issued
 * @retval _DEV_DEV_CC_ERR Device undefined Error
 * @retval _DEV_DEV_ERR Device error related to last host cmd
 * @retval _DEV_CIDCSD_OVERWRITE_ERR CID/CSD overwrite error
 */
dev_sts_e seq_writeCSD(
    _ub32 uiSlot,
    _ub32 uiMask,
    _ub32 uisetclr,
    _ub8 *piobuf)
{
    dev_sts_e eSts = _DEV_STS_OK;
   _ub32 uiValue;

    _SEQ_DBG_INFO("ENTRY");

   /* Only bits 0 -15 can be modified - rest of the fields are Read Only */
   /* Obtaining the original content of CSD [bits 0-31] */
    uiValue = seq_crcBuf[3];

    _SEQ_DBG_INFO("uiVal bef %x \n",uiValue);

   /* Modifying the required bit fields of CSD */
    if(_COM_SET == uisetclr)
    {
        uiValue |= uiMask;
    }
    else
    {
        uiValue &= ~uiMask;
    }

    seq_crcBuf[3] = uiValue;

    _SEQ_DBG_INFO("uiVal aftr %x \n",uiValue);

    /* switching endianness */
    {
        _ub32 uiTemp;

        uiTemp = seq_crcBuf[3];
        seq_crcBuf[3] = _SWITCH_ENDIANNESS(uiTemp);

        uiTemp = seq_crcBuf[2];
        seq_crcBuf[2] = _SWITCH_ENDIANNESS(uiTemp);

        uiTemp = seq_crcBuf[1];
        seq_crcBuf[1] = _SWITCH_ENDIANNESS(uiTemp);

        uiTemp = seq_crcBuf[0];
        seq_crcBuf[0] = _SWITCH_ENDIANNESS(uiTemp);
    }

   /* Copying the CSD contents to the buffer being transmitted over DAT line */
    {
        _ub32 uiLoop=0;
        _ub8 *ucpBuf_crc = (_ub8*)seq_crcBuf;

        for(uiLoop=0;uiLoop<15;uiLoop++)
        {
            piobuf[uiLoop]=ucpBuf_crc[uiLoop];
            _SEQ_DBG_INFO("buf val %x cnt %x \n",piobuf[uiLoop],uiLoop);
        }

        /* CSD CRC filed being populated */
        piobuf[uiLoop]=0;
        _SEQ_DBG_INFO("buf val %x cnt %x \n",piobuf[uiLoop],uiLoop);
    }

    eSts = executeSequence(uiSlot, _SEQ_ID_WRCSD);

    if(_DEV_STS_OK != eSts)
    {
        _SEQ_DBG_ERR("ERR: Write CSD failed");
        return eSts;
    }

     /* since CSD is modified - update the CSD structure */
     eSts = executeSequence(uiSlot, _SEQ_ID_RDCSD);
    if(_DEV_STS_OK != eSts)
    {
        _SEQ_DBG_ERR("ERR: Read CSD failed");
    }

    _SEQ_DBG_INFO("EXIT");

    return eSts;
}

/**
 * @brief Reads the device status by sending CMD13
 *
 * @param[in] uiSlot Slot number
 * @param[out] puiDevState Device state
 *
 * @retval _DEV_STS_OK Sequence executed successfully
 * @retval _DEV_INPUT_ERR Input param error
 * @retval _DEV_CMDBUSY_ERR CMD sending failed as CMD line was busy
 * @retval _DEV_CMDSEND_ERR CMD sending failed: timeout/index/crc/endbit error
 * @retval _DEV_LOCKED Device is locked
 * @retval _DEV_EXCEPTION Device exception event occurred
 * @retval _DEV_ADDR_OUT_OF_RANGE Address out of Range error occurred
 * @retval _DEV_ADDR_MISALIGN Address misalign error occurred
 * @retval _DEV_BLK_LEN_ERR Block length error occurred
 * @retval _DEV_ERASE_SEQ_ERR Erase sequence error occurred
 * @retval _DEV_ERASE_PARAM_ERR Erase param error occurred
 * @retval _DEV_WP_VIOLATION_ERR WP violation occurred
 * @retval _DEV_LOCK_UNLOCK_FAIL Lock/Unlock Failed
 * @retval _DEV_ILLEGAL_CMD_ERR Illegal command issued
 * @retval _DEV_ECC_FAIL Device ECC failed
 * @retval _DEV_CC_ERR Device undefined Error
 * @retval _DEV_ERR Device error related to last host cmd
 * @retval _DEV_CIDCSD_OVERWRITE_ERR CID/CSD overwrite error
 * @retval _DEV_WP_ERASE_SKIP_ERR WP Erase skip error
 * @retval _DEV_ERASE_RESET_ERR Erase reset error
 * @retval _DEV_SWITCH_ERR Switch command error
 */
dev_sts_e seq_getDevSts(_ub32 uiSlot, _ub32 *puiDevState)
{
    dev_sts_e eSts = _DEV_STS_OK;
    cmd_sts_e eCmdSts = _CMD_STS_OK;
    cmd_params_t tCmdParams;
    const cmd_info_t *pCmdInfo;
    _ub32 uiResp = 0;

    _SEQ_DBG_INFO("ENTRY");

    /* Validate input argument */
    if(NULL == puiDevState)
    {
        return _DEV_INPUT_ERR;
    }

    /* Retrieve the cmd info table entry for CMD13 */
    pCmdInfo = &seq_tCmdInfoTbl[_CMD13];

    /* Frame params for CMD13 */
    tCmdParams.eIndex = _CMD13;
    tCmdParams.eDatUsage = pCmdInfo->eDatUsage;
    tCmdParams.eRespCtgy = pCmdInfo->eRespCtgy;
    tCmdParams.uiArg = 0x00010000;         /* RCA = 0x0001 */

    /* Send CMD13 and get the response */
    eCmdSts = cmd_sendCommand(uiSlot, &tCmdParams, &uiResp);
    if(_CMD_STS_OK != eCmdSts)
    {
        /* Error code mapping */
        switch(eCmdSts)
        {
            case _CMD_CMDLINE_BUSY: /* Fall thru */
            case _CMD_DATLINE_BUSY:
                eSts = _DEV_CMDBUSY_ERR;
            break;

            case _CMD_INPUT_PARAM_ERR:
                eSts = _DEV_CMDSEND_ERR;
            break;

            default:
                eSts = _DEV_CMDSEND_ERR;
            break;
        }
    }
    else /* Update the device status from the response data */
    {
        /* Parse the response for errors */
        eSts = parseR1Resp(_CMD13, uiResp);
        /* Get the device current state */
        *puiDevState = (_ub16)((uiResp & _DEV_STATE) >> 9);
    }
    _SEQ_DBG_INFO("EXIT");
    return eSts;
}

/**
 * @brief Deallocates the CMD sequences layer of eMMC driver
 *
 * @param[in] pValidSlot List of slots marked valid/invalid by HC & Seq layer
 *
 * @retval _DEV_STS_OK Sequence executed successfully
 * @retval _DEV_CMDLAYER_FAIL Cmd layer exit failed
 */
dev_sts_e seq_exit(_ub32 *pValidSlot)
{
    dev_sts_e eSts = _DEV_STS_OK;
    cmd_sts_e eCmdSts = _CMD_STS_OK;
    _ub32 slotNo = 0;

    _SEQ_DBG_INFO("ENTRY");

    for(slotNo = 0; slotNo < _MAX_SLOTS; slotNo++)
    {
        if(_SLOT_INVALID == pValidSlot[slotNo])
        {
            /* Continue to next slot */
            continue;
        }

        eCmdSts = cmd_exit(slotNo);
        if(_CMD_STS_OK != eCmdSts)
        {
            eSts = _DEV_CMDLAYER_FAIL;
        }
    }
    _SEQ_DBG_INFO("EXIT");

    return eSts;
}

/**
 * @brief Returns the sector count of the device.
 *
 * @param[in] uiSlot Host controller Slot no
 *
 * @retval Sector count: No of sectors available
 */
_ub32 seq_getSectCnt(_ub32 uiSlot)
{
    extcsdinfo_t *pExtCSD;
    _ub32 uiSectCnt = 0;

    pExtCSD = &seq_tEXTCSDInfo[uiSlot];

    _SEQ_DBG_INFO("ENTRY");

    /* Read the sector count from the EXTCSD reg details */
    uiSectCnt = *(_ub32 *)(pExtCSD->ucBuf + _EXTCSD_SECTCNT_OFST);

    _SEQ_DBG_INFO("Sector Count: 0x%08x", uiSectCnt);

    _SEQ_DBG_INFO("EXIT");

    return uiSectCnt;
}

/**
 * @brief Returns the pointer to the CSD Param struct.
 *
 * @param[in] uiSlot Host controller Slot no
 *
 * @retval Pointer to the CSD Param struct
 */
com_csd_params_t* seq_getCSD(_ub32 uiSlot)
{
    _SEQ_DBG_INFO("Returning CSD Register Pointer");

    return &seq_tCSDParams[uiSlot];
}

/**
 * @brief Returns the pointer to the CID Param struct.
 *
 * @param[in] uiSlot Host controller Slot no
 *
 * @retval Pointer to the CID Param struct
 */
com_cid_params_t* seq_getCID(_ub32 uiSlot)
{
    _SEQ_DBG_INFO("Returning CID Register Pointer");

    return &seq_tCIDParams[uiSlot];
}

/**
 * @brief Disable emulation mode to the device
 *
 * @param[in] uiSlot Slot number
 *
 * @retval _DEV_ALREADY_DONE If device already in emulation mode
 * @retval _DEV_STS_OK if function is successful
 */
dev_sts_e seq_disableEmulationMode(_ub32 uiSlot)
{
    dev_sts_e eSts = _DEV_STS_OK;

    /* input argument is not validated */

    if(seq_tEXTCSDInfo[uiSlot].ucBuf[_EXTCSD_EXT_USE_NTV_SEC_OFST] != 0x01)
    {
        eSts = seq_writeExtCSD(uiSlot, _EXTCSD_EXT_USE_NTV_SEC_OFST, 0x01);
        if(_DEV_STS_OK != eSts)
        {
            _SEQ_DBG_ERR("seq_writeExtCSD Failed");
            return eSts;
        }
        return _DEV_STS_OK;
    }

    return _DEV_ALREADY_DONE;
}

/**
 * @brief Gets the Write Protect Grp Size from the device (in sectors)
 *
 * @param[in] uiSlot Host Controller slot number
 *
 * @retval _ub64 The value from the device
 */
_ub32 seq_getWPGrpSize(_ub32 uiSlot)
{
    _ub8 uiWpgrp;
    _ub8 uiWpgrpval = 0;
    _ub32 uiErsgrpsize = 0;
    _ub32 uiWpgrpsize = 0;

    extcsdinfo_t *pExtCSDParams = &seq_tEXTCSDInfo[uiSlot];
    com_csd_params_t *pCSDParams =  &seq_tCSDParams[uiSlot];

    /* Input argument is not validated */

    /* Get the erase group size in bytes */
    uiErsgrpsize = seq_getErsGrpSize(uiSlot);

    uiWpgrp = pExtCSDParams->ucBuf[_EXTCSD_ERASE_GROUP_DEF_OFST];
    uiWpgrp &= _ERASE_GRP_DEF_MASK;

    if(uiWpgrp)
    {
        dz_print(_DZ_CRTICAL, "IF Condition in seq_getWPGrpSize \n");
        /* get the values. from the offsets and calculate size */
        uiWpgrpval = pExtCSDParams->ucBuf[_EXTCSD_HCWPGRP_OFST];

        uiWpgrpsize = ((_ub32)uiWpgrpval *uiErsgrpsize);
    }
    else
    {
        uiWpgrpsize = ((pCSDParams->ucWPGrpSize + 1) * uiErsgrpsize) ;
    }

     _SEQ_DBG_INFO("WPG Size : %d\n",uiWpgrpsize);

    return uiWpgrpsize;
}

/**
 * @brief Gets the Erase Group Size from the device (in sectors)
 *
 * @param[in] uiSlot Host Controller slot number
 *
 * @retval uiErsgrpsize The size of erasable unit
 */
_ub32 seq_getErsGrpSize(_ub32 uiSlot)
{
    _ub8 uiErsgrp;
    _ub32 uiErsgrpsize = 0;

    extcsdinfo_t *pExtCSDParams = &seq_tEXTCSDInfo[uiSlot];
    com_csd_params_t *pCSDParams =  &seq_tCSDParams[uiSlot];

    /* Input argument is not validated */

    uiErsgrp = pExtCSDParams->ucBuf[_EXTCSD_ERASE_GROUP_DEF_OFST];
    uiErsgrp &= _ERASE_GRP_DEF_MASK;

    /* If ERASE_GROUP_DEF is set, read from Ext CSD, else from CSD register */
    if(uiErsgrp)
    {
        /* get the values from ExtCSD offset and calculate size(sector units) */
        uiErsgrpsize = (_ub32)pExtCSDParams->ucBuf[_EXTCSD_HCERSGRP_OFST];
        uiErsgrpsize *= 1024; /* To get size in sector units */
    }
    else
    {
        /* get value from CSD register and calculate size in sector units */
        uiErsgrpsize = ((pCSDParams->ucEraseGrpSiz + 1) * \
            (pCSDParams->ucEraseGrpMul + 1));
    }

    _SEQ_DBG_INFO("Erase WPG Size : %d\n",uiErsgrpsize);

    return uiErsgrpsize;
}

/**
 * @brief Gets the Erase Memory Content from the device
 *
 * @param[in] uiSlot Host Controller slot number
 *
 * @retval ucErsMemCont The value of erased memory content of the device
 */
_ub8 seq_getErsMemContent(_ub32 uiSlot)
{
    _ub8 ucErsMemCont;

    extcsdinfo_t *pExtCSDParams = &seq_tEXTCSDInfo[uiSlot];

    /* Input argument is not validated */

    ucErsMemCont = pExtCSDParams->ucBuf[_EXTCSD_ERASE_MEM_CONT_OFST];

    _SEQ_DBG_INFO("Erase Memory Content : %c\n", ucErsMemCont);

    return ucErsMemCont;
}

/**@}*/ // Seq_Functions

/**@}*//* Sequence */
/**@}*//* Device */

