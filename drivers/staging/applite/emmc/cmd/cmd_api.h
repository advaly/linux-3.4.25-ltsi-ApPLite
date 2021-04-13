/**
 * @file          cmd_api.h
 *
 * \brief         Header file of CMD API layer.
 *
 * \b COPYRIGHT : TOSHIBA Corporation Semiconductor and Storage Company
 * 2010-2015 All rights reserved
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
 * @addtogroup Device
 * @{
 */

/**
 * @addtogroup Command
 * @{
 */

#ifndef _CMD_API_H_
#define _CMD_API_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*----------------------- Header Files Inclusions ---------------------------*/
#include "types.h"          /* To use the data type typedefs */

/** @addtogroup CMD_DEFINES CMD_DEFINES
 * @{
 */

/* CMD/DAT line busy/free */
#define _LINE_BUSY   1
#define _LINE_FREE   0

/* CMD/DAT line inhibit field masks in Present state register */
#define _CMD_LINE    0x00000001
#define _DAT_LINE    0x00000002

/**@}*/ // CMD_DEFINES

/*-------------------------- Enum Definitions -------------------------------*/

/** @addtogroup CMD_Enums CMD_Enums
 * @{
 */

/**
 * @brief eMMC CMD indices
 */
typedef enum tag_cmd_index_e
{
    _CMD0,         /**< CMD0 - Device Reset */
    _CMD1,         /**< CMD1 - Send OCR */
    _CMD2,         /**< CMD2 - All Send CID */
    _CMD3,         /**< CMD3 - Set RCA*/
    _CMD4,         /**< CMD4 - Set DSR */
    _CMD5,         /**< CMD5 - Sleep/Awake */
    _CMD6,         /**< CMD6 - Switch */
    _CMD7,         /**< CMD7 - Select/Deselect card */
    _CMD8,         /**< CMD8 - Send EXT CSD*/
    _CMD9,         /**< CMD9 - Send CSD */
    _CMD10,        /**< CMD10 - Send CID */
    _CMD11,        /**< CMD11 - Obsolete */
    _CMD12,        /**< CMD12 - Stop Transmission */
    _CMD13,        /**< CMD13 - Send Status */
    _CMD14,        /**< CMD14 - Bus Test Read */
    _CMD15,        /**< CMD15 - Go to Inactive State */
    _CMD16,        /**< CMD16 - Set Block length */
    _CMD17,        /**< CMD17 - Read single block */
    _CMD18,        /**< CMD18 - Read Multiple blocks */
    _CMD19,        /**< CMD19 - Bus Test Write */
    _CMD20,        /**< CMD20 - Obsolete */
    _CMD21,        /**< CMD21 - Send tuning block */
    _CMD22,        /**< CMD22 - Rsvd */
    _CMD23,        /**< CMD23 - Set block count */
    _CMD24,        /**< CMD24 - Write Single block */
    _CMD25,        /**< CMD25 - Write Multiple blocks */
    _CMD26,        /**< CMD26 - Program CID */
    _CMD27,        /**< CMD27 - Program CSD */
    _CMD28,        /**< CMD28 - Set Write Protection */
    _CMD29,        /**< CMD29 - Clear Write Protection*/
    _CMD30,        /**< CMD30 - Send Write Protection */
    _CMD31,        /**< CMD31 - Send Write Protect Type */
    _CMD32,        /**< CMD32 - Rsvd */
    _CMD33,        /**< CMD33 - Rsvd */
    _CMD34,        /**< CMD34 - Rsvd */
    _CMD35,        /**< CMD35 - Erase Group Start */
    _CMD36,        /**< CMD36 - Erase Group End */
    _CMD37,        /**< CMD37 - Rsvd */
    _CMD38,        /**< CMD38 - Erase */
    _CMD39,        /**< CMD39 - Fast I/O */
    _CMD40,        /**< CMD40 - Go IRQ State */
    _CMD41,        /**< CMD41 - Rsvd */
    _CMD42,        /**< CMD42 - Lock/Unlock */
    _CMD43,        /**< CMD43 - Rsvd */
    _CMD44,        /**< CMD44 - Rsvd */
    _CMD45,        /**< CMD45 - Rsvd */
    _CMD46,        /**< CMD46 - Rsvd */
    _CMD47,        /**< CMD47 - Rsvd */
    _CMD48,        /**< CMD48 - Rsvd */
    _CMD49,        /**< CMD49 - Set Time */
    _CMD50,        /**< CMD50 - Rsvd */
    _CMD51,        /**< CMD51 - Rsvd */
    _CMD52,        /**< CMD52 - Rsvd */
    _CMD53,        /**< CMD53 - Rsvd */
    _CMD54,        /**< CMD54 - Rsvd */
    _CMD55,        /**< CMD55 - App CMD */
    _CMD56,        /**< CMD56 - Gen CMD */
    _CMD57,        /**< CMD57 - Rsvd */
    _CMD58,        /**< CMD58 - Rsvd */
    _CMD59,        /**< CMD59 - Rsvd */
    _CMD60,        /**< CMD60 - Rsvd */
    _CMD61,        /**< CMD61 - Rsvd */
    _CMD62,        /**< CMD62 - Rsvd */
    _CMD63,        /**< CMD63 - Rsvd */
    _CMD_MAX
}cmd_index_e;

/**
 * @brief Response Categories Table 2-10 of SD HC spec ver3.00
 */
typedef enum tag_resp_ctgy_e
{
    _RESP_CTGY0,        /**< No response */
    _RESP_CTGY1,        /**< R2 response */
    _RESP_CTGY2,        /**< R3/R4 response */
    _RESP_CTGY3,        /**< R1/R5 response */
    _RESP_CTGY4,        /**< R1b response */
    _RESP_CTGY_MAX      /**< Invalid value */
}resp_ctgy_e;

/**
 * @brief DAT line usage for commands
 */
typedef enum tag_dat_usage_e
{
    _DAT_UNUSED,        /**< DAT line not used */
    _DAT_USED_BUSY,     /**< DAT line used for busy signalling */
    _DAT_USED_DATA,     /**< DAT line used for data transfer */
    _DAT_USED_INVALID   /**< Invalid value */
}dat_usage_e;

/**
 * @brief Command Send status
 */
typedef enum tag_cmd_sts_e
{
    _CMD_STS_OK,           /**< 0x0: Command is sent successfully */
    _CMD_INIT_NG,          /**< 0x1: CMD layer Init failed */
    _CMD_EXIT_NG,          /**< 0x2: CMD layer Exit failed */
    _CMD_DATA_ERR,         /**< 0x3: Data error occured */
    _CMD_ADMA_ERR,         /**< 0x4: ADMA error occured */
    _CMD_TRANSTIMEOUT_ERR, /**< 0x5: Transfer complete event timed out */
    _CMD_CMDLINE_BUSY,     /**< 0x6: CMD line is busy */
    _CMD_DATLINE_BUSY,     /**< 0x7: DAT line is busy */
    _CMD_SEND_ERR,         /**< 0x8: Command timeout/endbit/crc/index error */
    _CMD_INPUT_PARAM_ERR,  /**< 0x9: Wrong input parameters */
    _CMD_STS_INVALID       /**< 0xA: Invalid status */
}cmd_sts_e;

/**@}*/ //end of CMD_Enums

/*------------------ Data Structures & Custom Typedefs ----------------------*/

/** @defgroup CMD_Structures CMD_Structures
 * @{
 */

/**
 * @brief Structure for Command and Argument1 register value framing
 */
typedef struct tag_cmd_params_t
{
    cmd_index_e     eIndex;         /* CMD index 0, 1, 2 etc */
    resp_ctgy_e     eRespCtgy;      /* Response Category as per Table2-10 */
    _ub32           uiArg;          /* Command Argument */
    dat_usage_e     eDatUsage;      /* DAT line used or not */
}cmd_params_t;

/**@}*/ // CMD_Structures

/*---------------------------- Prototypes -----------------------------------*/

/** @addtogroup CMD_Prototypes CMD_Prototypes
 * @{
 */

/* Function to initialize Cmd layer */
cmd_sts_e cmd_init(_ub32 uiSlot);

/* Function to send the command to eMMC device */
cmd_sts_e cmd_sendCommand(
    _ub32 uiSlot,
    cmd_params_t *pCmdParams,
    _ub32 *pResponse);

/* Function to retrieve the response data from response register */
cmd_sts_e cmd_getResponse(
    _ub32 uiSlot,
    _ub32 *pResponse);

/* Function to check inhibit status of CMD/DAT line */
_ub8 cmd_checkInhibitSts(_ub32 uiSlot,_ub32 uiLine);

/* Function to exit Cmd layer */
cmd_sts_e cmd_exit(_ub32 uiSlot);

/**@}*/ // CMD_Prototypes

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CMD_API_H_ */

/**@}*//* Command */
/**@}*//* Device */

