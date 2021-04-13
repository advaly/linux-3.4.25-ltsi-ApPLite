/**
 * @file          dev_com.h
 *
 * \brief         Header file for CMD sequences & Partition Management layer.
 *
 * \b COPYRIGHT : TOSHIBA Corporation Semiconductor and Storage Company
 * 2010-2015 All rights reserved
 *
 * \b Project   : Glenfiddich
 *
 * \b Version   : 0.2
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

#ifndef _DEV_H_
#define _DEV_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*----------------------- Header Files Inclusions ---------------------------*/
#include "types.h"          /* To use the data type typedefs */
#include "config.h"          /* To use _MAX_SLOTS */
#include "cmd_api.h"          /* To use the data type typedefs */

/*-------------------------- Macro Definitions ------------------------------*/

/** @addtogroup Seq_DEFINES Seq_DEFINES
 * @{
 */

/* Debug prints definitions */
#ifdef __DEBUG
#define _SEQ_DBG_INFO(__format__, arg...)    \
    dz_print(_DZ_DEV, "[%4d]%s::" __format__"\n", __LINE__,    \
    __FUNCTION__,## arg )

#define _SEQ_DBG_ERR(__format__, arg...)    \
    dz_print(_DZ_CRTICAL, "[%4d]%s::" __format__"\n", __LINE__,    \
    __FUNCTION__,## arg )
#else /* !__DEBUG */
#define _SEQ_DBG_INFO(__format__, arg...)
#define _SEQ_DBG_ERR(__format__, arg...)
#endif /* __DEBUG */

/**
 * @brief For sequence table: Max no of CMDs in any sequence
 */
#define _NUM_CMD_MAX         6

/**
 * @brief Ext CSD Register size in bytes
 */
#define _EXTCSD_SIZE        512

/**
 * @brief Offsets for EXT CSD fields.
 */
#define _EXTCSD_EXT_PART_ATTR1_OFST    52  /* ofst for ext_attr 1 */
#define _EXTCSD_EXT_PART_ATTR2_OFST    53  /* ofst for ext_attr 2 */
#define _EXTCSD_EXT_USE_NTV_SEC_OFST   62  /* ofst for USE_NATIVE_SECTOR */
#define _EXTCSD_ENH_START_ADR_0_OFST   136  /* ofst for EUDA start addr byte0 */
#define _EXTCSD_ENH_START_ADR_1_OFST   137  /* ofst for EUDA start addr byte1 */
#define _EXTCSD_ENH_START_ADR_2_OFST   138  /* ofst for EUDA start addr byte2 */
#define _EXTCSD_ENH_START_ADR_3_OFST   139  /* ofst for EUDA start addr byte3 */
#define _EXTCSD_ENH_SIZE_0_OFST        140  /* ofst for EUDA size byte0 */
#define _EXTCSD_ENH_SIZE_1_OFST        141  /* ofst for EUDA size byte1 */
#define _EXTCSD_ENH_SIZE_2_OFST        142  /* ofst for EUDA size byte2 */
#define _EXTCSD_GP_SIZE_1_0_OFST       143  /* ofst for GPP1 size byte0 */
#define _EXTCSD_GP_SIZE_1_1_OFST       144  /* ofst for GPP1 size byte1 */
#define _EXTCSD_GP_SIZE_1_2_OFST       145  /* ofst for GPP1 size byte2 */
#define _EXTCSD_GP_SIZE_2_0_OFST       146  /* ofst for GPP2 size byte0 */
#define _EXTCSD_GP_SIZE_2_1_OFST       147  /* ofst for GPP2 size byte1 */
#define _EXTCSD_GP_SIZE_2_2_OFST       148  /* ofst for GPP2 size byte2 */
#define _EXTCSD_GP_SIZE_3_0_OFST       149  /* ofst for GPP3 size byte0 */
#define _EXTCSD_GP_SIZE_3_1_OFST       150  /* ofst for GPP3 size byte1 */
#define _EXTCSD_GP_SIZE_3_2_OFST       151  /* ofst for GPP3 size byte2 */
#define _EXTCSD_GP_SIZE_4_0_OFST       152  /* ofst for GPP4 size byte0 */
#define _EXTCSD_GP_SIZE_4_1_OFST       153  /* ofst for GPP4 size byte1 */
#define _EXTCSD_GP_SIZE_4_2_OFST       154  /* ofst for GPP4 size byte2 */
#define _EXTCSD_PART_COMPLETED_OFST    155  /* ofst for partition complete */
#define _EXTCSD_PART_ATTRIBUTE_OFST    156  /* ofst for partition attr */
#define _EXTCSD_MAX_ENH_SIZE_0_OFST    157  /* ofst for max enh size byte 0 */
#define _EXTCSD_MAX_ENH_SIZE_1_OFST    158  /* ofst for max enh size byte 1 */
#define _EXTCSD_MAX_ENH_SIZE_2_OFST    159  /* ofst for max enh size byte 2 */
#define _EXTCSD_PART_SUPPORT_OFST      160  /* ofst for partition support */
#define _EXTCSD_SANITIZE_START_OFST    165  /* ofst for sanitize start */
#define _EXTCSD_USER_WP_OFST           171  /* ofst for Write Protection */
#define _EXTCSD_ERASE_GROUP_DEF_OFST   175  /* ofst for erase group def bit */
#define _EXTCSD_PART_CONFIG_OFST       179  /* ofst for partition config */
#define _EXTCSD_ERASE_MEM_CONT_OFST    181  /* ofst for sanitize start */
#define _EXTCSD_SECTCNT_OFST           212  /* ofst for sector count */
#define _EXTCSD_HCWPGRP_OFST           221  /* ofst for HC WP Group Size */
#define _EXTCSD_HCERSGRP_OFST          224  /* ofst for HC Erase Group Size */
#define _EXTCSD_SEC_FEAT_SUPPORT_OFST  231  /* ofst for secure featur support */

/**
 * Masks for Partition Management ERASE GRP DEF bit
 */
#define _ERASE_GRP_DEF_MASK    0x01  /* Mask for Erase Group Def Bit */

/**
 * @brief Mask values for CSD register fields in R2 response register.
 */
#define _CSD_STRUCT_MASK        0x00C00000U /* Bits 119-118 in resp reg */
#define _SPEC_VERS_MASK         0x003C0000U /* Bits 117-114 in resp reg */
#define _TAAC_MASK              0x0000FF00U /* Bits 111-104 in resp reg */
#define _NSAC_MASK              0x000000FFU /* Bits 103-96 in resp reg */

#define _TRANS_SPEED_MASK       0xFF000000U /* Bits 95-88 in resp reg */
#define _DEV_CCC_MASK           0x00FFF000U /* Bits 87-76 in resp reg */
#define _RDBLKLEN_MASK          0x00000F00U /* Bits 75-72 in resp reg */
#define _RDPARTBLK_MASK         0x00000080U /* Bits 71-71 in resp reg */
#define _WRBLKMISALIGN_MASK     0x00000040U /* Bits 70-70 in resp reg */
#define _RDBLKMISALIGN_MASK     0x00000020U /* Bits 69-69 in resp reg */
#define _DSRIMPL_MASK           0x00000010U /* Bits 68-68 in resp reg */
#define _DEVSIZE_OFST1_MASK     0x00000003U /* Bits 65-64 in resp reg */
#define _DEVSIZE_OFST2_MASK     0xFFC00000U /* Bits 63-54 in resp reg */

#define _RDMINCURR_MASK         0x00380000U /* Bits 53-51 in resp reg */
#define _RDMAXCURR_MASK         0x00070000U /* Bits 50-48 in resp reg */
#define _WRMINCURR_MASK         0x0000E000U /* Bits 47-45 in resp reg */
#define _WRMAXCURR_MASK         0x00001C00U /* Bits 44-42 in resp reg */
#define _CSIZEMULT_MASK         0x00000380U /* Bits 41-39 in resp reg */
#define _ERASEGRPSIZE_MASK      0x0000007CU /* Bits 38-34 in resp reg */
#define _ERASEGRPMUL_OFST1_MASK 0x00000003U /* Bits 33-32 in resp reg */
#define _ERASEGRPMUL_OFST2_MASK 0xE0000000U /* Bits 31-29 in resp reg */

#define _WPGRPSIZE_MASK         0x1F000000U /* Bits 28-24 in resp reg */
#define _WPGRPENABLE_MASK       0x00800000U /* Bits 23-23 in resp reg */
#define _DEFAULTECC_MASK        0x00600000U /* Bits 22-21 in resp reg */
#define _R2WFACTOR_MASK         0x001C0000U /* Bits 20-18 in resp reg */
#define _WRBLKLEN_MASK          0x0003C000U /* Bits 17-14 in resp reg */
#define _WRBLPART_MASK          0x00002000U /* Bits 13-13 in resp reg */
#define _CONTPROTAPP_MASK       0x00000100U /* Bits 8-8 in resp reg */
#define _FILEFORMATGRP_MASK     0x00000080U /* Bits 7-7 in resp reg */
#define _COPY_MASK              0x00000040U /* Bits 6-6 in resp reg */
#define _PERMWRPROT_MASK        0x00000020U /* Bits 5-5 in resp reg */
#define _TEMPWRPROT_MASK        0x00000010U /* Bits 4-4 in resp reg */
#define _FILEFORMAT_MASK        0x0000000CU /* Bits 3-2 in resp reg */
#define _ECC_MASK               0x00000003U /* Bits 1-0 in resp reg */

/**
 * @brief For Clearing/setting CSD bits
 */
#define _COM_SET 1
#define _COM_CLR 0

/**
 * @brief For switching endianness
 */
#define _SWITCH_ENDIANNESS(uiTemp)                 \
                ((uiTemp >> 24) & 0xFF) |           \
                ((uiTemp >> 8) & 0xFF00) |          \
                ((uiTemp << 8) & 0xFF0000) |        \
                ((uiTemp << 24) & 0xFF000000);

/**@}*/ // Seq_DEFINES

/*-------------------------- Enum Definitions -------------------------------*/

/** @addtogroup Seq_Enums Seq_Enums
 * @{
 */

/**
 * @brief Device layer error/status codes
 */
typedef enum tag_dev_sts_e
{
    _DEV_STS_OK                   = 0x0000, /**< Sequence status OK */
    _DEV_INPUT_ERR                = 0x0001, /**< Input param error */
    _DEV_TIMEOUT_ERR              = 0x0002, /**< Sequence timeout occurred */
    _DEV_DATA_ERR                 = 0x0003, /**< Data error occured */
    _DEV_ADMA_ERR                 = 0x0004, /**< ADMA error occured */
    _DEV_TRANSTIMEOUT_ERR         = 0x0005, /**< Data transfer timeout */
    _DEV_CMDBUSY_ERR              = 0x0006, /**< CMD failed-CMD line busy */
    _DEV_DATBUSY_ERR              = 0x0007, /**< CMD failed-DAT line busy */
    _DEV_CMDSEND_ERR              = 0x0008, /**< CMD-timout/indx/crc/endbit */
    _DEV_ADDR_OUT_OF_RANGE        = 0x0009, /**< Addr out of Range err occur */
    _DEV_ADDR_MISALIGN            = 0x000A, /**< Addr misalign error occurred */
    _DEV_BLK_LEN_ERR              = 0x000B, /**< Block length error occurred */
    _DEV_ERASE_SEQ_ERR            = 0x000C, /**< Erase sequence err occurred */
    _DEV_ERASE_PARAM_ERR          = 0x000D, /**< Erase param error occurred */
    _DEV_WP_VIOLATION_ERR         = 0x000E, /**< WP violation occurred */
    _DEV_LOCK_UNLOCK_FAIL         = 0x000F, /**< Lock/Unlock Failed */
    _DEV_ILLEGAL_CMD_ERR          = 0x0010, /**< Illegal command issued */
    _DEV_ECC_FAIL                 = 0x0011, /**< Device ECC failed */
    _DEV_CC_ERR                   = 0x0012, /**< Device undefined Error */
    _DEV_ERR                      = 0x0013, /**< Deverr related to host cmd */
    _DEV_CIDCSD_OVERWRITE_ERR     = 0x0014, /**< CID/CSD overwrite error */
    _DEV_WP_ERASE_SKIP_ERR        = 0x0015, /**< WP Erase skip error */
    _DEV_ERASE_RESET_ERR          = 0x0016, /**< Erase reset error */
    _DEV_SWITCH_ERR               = 0x0017, /**< Switch command error */
    _DEV_LOCKED                   = 0x0018, /**< Device is locked */
    _DEV_EXCEPTION                = 0x0019, /**< Exception event occurred */
    _DEV_DEVSTATE_ERR             = 0x001A, /**< Device is not in right state */
    _DEV_CMDLAYER_FAIL            = 0x001B, /**< CMD layer init/exit failed */
    _DEV_INTR_FAIL                = 0x001C, /**< Int Hdlr reg/dereg failed */
    _DEV_ALREADY_DONE             = 0x001D, /**< operation is aldready done */
    _DEV_PARTITION_NOT_SUPPORTED  = 0x001E, /**< Partitionnig not supported */
    _DEV_PARTITION_DONE_ERR       = 0x001F, /**< Partition is already Done */
    _DEV_PARTITION_INVALID        = 0x0020, /**< Partition not valid */
    _DEV_PARTITION_NOT_CREATED    = 0x0021, /**< Partition not created */
    _DEV_MAX_PARTITONS_EXCEEDED   = 0x0022, /**< max 4 partitions possible */
    _DEV_PARTITION_SIZE_ERR       = 0x0023, /**< partition size not aligned */
    _DEV_MAX_ENHANCED_SIZE_ERR    = 0x0024, /**< device enhanced size max */
    _DEV_EUDAADDR_ALIGN_ERR       = 0x0025, /**< euda addr not aligned to wpg */
    _DEV_ENH_ATTRIB_NOT_SUPPORTED = 0x0026, /**< Enhanced attr not supported */
    _DEV_EXT_ATTRIB_NOT_SUPPORTED = 0x0027, /**< Extended attr not supported */
    _DEV_PARTITION_SIZE_EXCEEDED  = 0x0028, /**< partition size exceeded */
    _DEV_SANITIZE_UNSUPPORTED     = 0x0029, /**< Sanitize feature unsupported */
    _DEV_STS_INVALID              = 0x002A, /**< Invalid status */
}dev_sts_e;

/**
 * @brief Sequence IDs for each command sequence
 */
typedef enum tag_seq_id_e
{
    _SEQ_ID_INIT,           /**< ID for init sequence */
    _SEQ_ID_CONFIG,         /**< ID for config sequence */
    _SEQ_ID_SWITCH,         /**< ID for switch sequence */
    _SEQ_ID_READ,           /**< ID for read sequence */
    _SEQ_ID_WRITE,          /**< ID for write sequence */
    _SEQ_ID_EXTCSD,         /**< ID for write extcsd sequence */
    _SEQ_ID_ERASE,          /**< ID for erase sequence */
    _SEQ_ID_WRCSD,          /**< ID for write csd sequence */
    _SEQ_ID_RDCSD,          /**< ID for read csd sequence */
    _SEQ_ID_WRONGERASE,     /**< ID for Illegal Erase sequence: Testing only */
    _SEQ_ID_NONERASE,       /**< ID for Nonerase cmd in Erase seq: Testing */
    _SEQ_ID_INACTIVE,       /**< ID to send device to inactive state: Testing */
    _SEQ_ID_DESELECT,       /**< ID to deselect device: For testing only */
    _SEQ_ID_SELECT,         /**< ID to select device: For testing only */
    _SEQ_ID_SETWP,          /**< ID to set password device */
    _SEQ_ID_CLRWP,          /**< ID to clear password device */
    _SEQ_ID_GET_WP_STAT,    /**< ID to get status of write protection */
    _SEQ_ID_GET_WP_TYP,     /**< ID to get type of write protection */
    _SEQ_ID_LKUNLK,         /**< ID to Lock/Unlock device */
    _SEQ_ID_MAX,            /**< Invalid ID */
}seq_id_e;

/**@}*/ //end of Seq_Enums

/*------------------ Data Structures & Custom Typedefs ----------------------*/

/** @defgroup Seq_Structures Seq_Structures
 * @{
 */

/**
 * @brief Struct to store OCR details of eMMC device. Values in little endian
 */
typedef struct tag_ocr_params_t
{
    _ub8 ucVolt1_95;   /**< VDD voltage window 1.70-1.95V */
    _ub8 ucVolt2_6;    /**< VDD voltage window 2.0-2.6V */
    _ub8 ucVolt3_6;    /**< VDD voltage window 2.7-3.6V */
    _ub8 ucAccessMode; /**< Byte mode: 00'b, Sector mode: 10'b */
}ocr_params_t;

/**
 * @brief Struct to maintain buffer for ext csd storage, & slot num
 */
typedef struct tag_extcsdinfo_t
{
    _ub8 ucBuf[512];   /**< extcsd has 512 bytes */
    _ub32 uiSlot;      /**< slot no. associated with the structure */
}extcsdinfo_t;

/**
 * @brief Struct to maintain the command and argument info.
 *
 * To be considered: A delay parameter might have to be added to
 * consider the delay to be maintained between 2 commands.
 */
typedef struct tag_cmd_frm_t
{
    cmd_index_e eIndex;     /**< Command index */
    _ub32 uiArg;            /**< Argument to the command */
}cmd_frm_t;

/**@}*/ // Seq_Structures

/*---------------------------- Externs --------------------------------------*/

/** @defgroup Seq_Externs Seq_Externs
 * @{
 */

/* Struct variable which holds the EXTCSD register value */
extern extcsdinfo_t seq_tEXTCSDInfo[_MAX_SLOTS];

/* Struct variable to store CSD register details */
extern com_csd_params_t seq_tCSDParams[_MAX_SLOTS];

/* Table to maintain all sequences. executeSequence() reads from this table */
extern cmd_frm_t seq_tCmdSeqTbl[_SEQ_ID_MAX][(_NUM_CMD_MAX+1)];

/**@}*/ // Seq_Externs

/*---------------------------- Prototypes -----------------------------------*/

/** @addtogroup Seq_Prototypes Seq_Prototypes
 * @{
 */

/* API for CMD sequences layer and eMMC device init */
dev_sts_e seq_init(_ub32 *pValidSlot);

/* API for eMMC device config: Standby state -> Transfer state */
dev_sts_e seq_configDevice(_ub32 uiSlot);

/* API for data read cmd sequence */
dev_sts_e seq_readData(_ub32 uiSlot, _ub32 uiDevAddr, _ub32 uiSize);

/* API for data write cmd sequence */
dev_sts_e seq_writeData(_ub32 uiSlot, _ub32 uiDevAddr, _ub32 uiSize);

/* API to set the bus width */
dev_sts_e seq_setBuswidth(_ub32 uiSlot, com_busWidth_e eBusWidth);

/* API to set the bus speed */
dev_sts_e seq_setSpeed(_ub32 uiSlot, com_busSpeed_e eBusSpeed);

/* API to write to EXT CSD register of device */
dev_sts_e seq_writeExtCSD(_ub32 uiSlot, _ub32 uiOfst, _ub32 uiValue);

/* API to write to CSD register of device */
dev_sts_e seq_writeCSD(
    _ub32 uiSlot,
    _ub32 uiMask,
    _ub32 uisetclr,
    _ub8 *piobuf);

/* API to exit the CMD sequences layer after bringing device to idle state */
dev_sts_e seq_exit(_ub32 *pValidSlot);

/* API to get the device status */
dev_sts_e seq_getDevSts(_ub32 uiSlot, _ub32 *puiDevState);

/* API to get sector count */
_ub32 seq_getSectCnt(_ub32 uiSlot);

/* API to read the CID param struct */
com_cid_params_t* seq_getCID(_ub32 uiSlot);

/* API to read the CSD param struct */
com_csd_params_t* seq_getCSD(_ub32 uiSlot);

/* API to disable Emulation mode */
dev_sts_e seq_disableEmulationMode(_ub32 uiSlot);

/* API to get the attributes of the GPPs */
dev_sts_e pm_getGPPAttributes(
    _ub32 uiSlot,
    com_part_num_e ePartNumber,
    com_gpp_attr_t *pPartAttr);

/* API to get the attributes of the EUDA */
dev_sts_e pm_getEUDAAttributes(
    _ub32 uiSlot,
    com_euda_attr_t *pPartAttr);

/* API to get the access to GPPs and EUDA */
dev_sts_e pm_accessPartitions(
    _ub32 uiSlot,
    com_part_num_e ePartNum);

/* API to get the current accessed partition */
com_part_num_e pm_getCurrPartition(_ub32 uiSlot);

/* API to get the write protect group size( in terms of bytes) */
_ub32 pm_getHCWPGrpSize(_ub32 uiSlot);

/* API to get the maximum enhanced size of the memory */
_ub32 pm_getMaxEnhSize(_ub32 uiSlot);

/* API to create the Partitions in the device */
dev_sts_e pm_createPartition(
    _ub32 uiSlot,
    _ub32 uiNumGpps,
    com_part_attr_t *pAttr);

/* API to Erase/Trim/Discard */
dev_sts_e dev_remData(_ub32 uiSlot,
    com_part_num_e ePartNum,
    _ub32 uiStartSectr,
    _ub32 uiEndSectr,
    com_rem_type_e eRemType);

/* API to Sanitize */
dev_sts_e dev_sanitize(_ub32 uiSlot);


/* API to set Write Protection */
dev_sts_e dev_setWriteProt(
    _ub32 uiSlot,
    com_part_num_e ePartNum,
    com_wp_e uiDevSeg,
    com_wp_type_e uiProtType,
    _ub32 uiSectr,
    _ub8 *piobuf);

/* API to clear Write Protect function */
dev_sts_e dev_clrWriteProt(_ub32 uiSlot,
    com_part_num_e ePartNum,
    com_wp_e uiDevSeg,
    com_wp_type_e uiProtType,
    _ub32 uiSectr,
    _ub8 *piobuf);

/* API to Get Write Protect Status */
dev_sts_e dev_getWPStat(
    _ub32 uiSlot,
    com_wpstat_e eWpStat,
    _ub32 uiSect);

/* API to Lock/Unlock Device,Set/Clear PWD,Force Erase */
dev_sts_e dev_devLkUnlk(_ub32 uiSlot,_ub32 uiSize);

/* API to get the write protect group size( in sector units) */
_ub32 seq_getWPGrpSize(_ub32 uiSlot);

/* API to get the erase group size( in terms of sector units) */
_ub32 seq_getErsGrpSize(_ub32 uiSlot);

/* API to get the erase memory content */
_ub8 seq_getErsMemContent(_ub32 uiSlot);

/**@}*/ // Seq_Prototypes

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DEV_H_ */

/**@}*//* Sequence */
/**@}*//* Device */

