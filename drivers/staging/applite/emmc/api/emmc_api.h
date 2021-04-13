/**
 * @file          emmc_api.h
 *
 * \brief         This is header file for API layer of the eMMC device
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
 * @addtogroup EMMCMemoryInterface
 * @{
 */

/**
 * @addtogroup EMMCAPIs
 * @{
 */

#ifndef _EMMC_API_H_
#define _EMMC_API_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*----------------------- Header Files Inclusions ---------------------------*/
#include "types.h"
#include "com.h"

/*-------------------------- Macro Definitions ------------------------------*/

/** @addtogroup API_DEFINES API_DEFINES
 * @{
 */

/* [MONTH:8 | YEAR:8 | MAJOR NO:8 | MINOR NO:8 */
/* MONTH = 08, YEAR = 13, MajorNO = 04 MinorNo = 00 */
#define _EMMC_DRV_VERSION   0x08130400 /* In BCD */

/* Maximum no. of GPPs that can be created are 4 */
#define _EMMC_MAX_GPPS      4

/**@}*/ // API_DEFINES

/*-------------------------- Enum Definitions -------------------------------*/

/** @addtogroup API_Enums API_Enums
 * @{
 */

/**
 * @brief Error codes from different modules
 *
 * Error codes are given different values based on which module returns these
 * errors. For ex: If OS layer returns error code 0x0007, value returned to
 * upper layer will be (_OS_ID | 0x0000007) = 0x00030007. This error code
 * indicates OS layer returned _OS_ERR_INTR_REG
 */

typedef enum tag_emmc_sts_e
{
    _EMMC_STS_OK                    = 0x00000000, /**< No error */
    _EMMC_STS_NG                    = 0x00000001, /**< Return status NG */
    _EMMC_INIT_INVALID              = 0x00000002, /**< emmc_init is invalid */
    _EMMC_ARG_INVALID               = 0x00000003, /**< Input arg is invalid */
    _EMMC_REQ_INVALID               = 0x00000004, /**< Entry is invalid */
    _EMMC_SLOT_INVALID              = 0x00000005, /**< Slot is invalid */
    _EMMC_HC_STS_ERR                = 0x00010001, /**< Wrong val read frm reg */
    _EMMC_HC_STS_TIMEOUT            = 0x00010002, /**< HC cfg is unsuccessful */
    _EMMC_HC_STS_NOTSUPPORTED       = 0x00010003, /**< Feature not supported  */
    _EMMC_OS_ERR_DRV_REG            = 0x00030001, /**< OS drv register err */
    _EMMC_OS_ERR_IRQ_RETRV          = 0x00030002, /**< Err in retrieving Irq */
    _EMMC_OS_ERR_TASK_CREATION      = 0x00030003, /**< createTsk err(Threads) */
    _EMMC_OS_ERR_TASK_DELETION      = 0x00030004, /**< delTask err(Threads) */
    _EMMC_OS_ERR_MEM_ALLOC_FAIL     = 0x00030005, /**< Err in allocating mem */
    _EMMC_OS_ERR_DMEM_ALLOC_FAIL    = 0x00030006, /**< Err allocating DMA mem */
    _EMMC_OS_ERR_INTR_REG           = 0x00030007, /**< Err registering intr */
    _EMMC_OS_ERR_CREATE_TIMER       = 0x00030008, /**< Err in creating timer */
    _EMMC_OS_ERR_DELETE_TIMER       = 0x00030009, /**< Err in deleting timer */
    _EMMC_OS_ERR_CREATE_LOCK        = 0x0003000A, /**< Err in creating lock */
    _EMMC_OS_ERR_DELETE_LOCK        = 0x0003000B, /**< Err in deleting lock */
    _EMMC_OS_ERR_WAIT_TIMEOUT       = 0x0003000C, /**< Err in synchronization */
    _EMMC_OS_ERR_INVALID_CB_FUNC    = 0x0003000D, /**< Err in call back func */
    _EMMC_OS_ERR_MOD_TIMER          = 0x0003000E, /**< Err in modifying timer */
    _EMMC_OS_ERR_PARAM              = 0x0003000F, /**< Error in function args */
    _EMMC_OS_ERR_SEMAPHORE          = 0x00030010, /**< Error taking semaphore */
    _EMMC_OS_ERR_RESOURCE           = 0x00030011, /**< Resource access error */
    _EMMC_OS_ERR_MEMCMP             = 0x00030012, /**< mem_cmp error */
    _EMMC_OS_ERR_OBTRES             = 0x00030013, /**< Error obtain resources */
    _EMMC_OS_ERR_MAP                = 0X00030014, /**< Err in mapping address */
    _EMMC_OS_ERR_PROBE_PLTDRV       = 0x00030015, /**< Platform resources err */
    _EMMC_OS_ERR_PROBE_PCIDRV       = 0x00030016, /**< Err Probing PCI device */
    _EMMC_OS_STS_INVALID            = 0x00030017, /**< Invalid error status */
    _EMMC_DEV_INPUT_ERR             = 0x00040001, /**< Input param error */
    _EMMC_DEV_TIMEOUT_ERR           = 0x00040002, /**< Seq timeout occurred */
    _EMMC_DEV_DATA_ERR              = 0x00040003, /**< Data error occured */
    _EMMC_DEV_ADMA_ERR              = 0x00040004, /**< ADMA error occured */
    _EMMC_DEV_TRANSTIMEOUT_ERR      = 0x00040005, /**< Data transfer timeout */
    _EMMC_DEV_CMDBUSY_ERR           = 0x00040006, /**< CMD fail-CMD line busy */
    _EMMC_DEV_DATBUSY_ERR           = 0x00040007, /**< CMD fail-DAT line busy */
    _EMMC_DEV_CMDSEND_ERR           = 0x00040008, /**< timout/indx/crc/endbit */
    _EMMC_DEV_ADDR_OUT_OF_RANGE     = 0x00040009, /**< Addr out of Range err */
    _EMMC_DEV_ADDR_MISALIGN         = 0x0004000A, /**< Addr misalign error */
    _EMMC_DEV_BLK_LEN_ERR           = 0x0004000B, /**< Block length error */
    _EMMC_DEV_ERASE_SEQ_ERR         = 0x0004000C, /**< Erase sequence error */
    _EMMC_DEV_ERASE_PARAM_ERR       = 0x0004000D, /**< Erase param error */
    _EMMC_DEV_WP_VIOLATION_ERR      = 0x0004000E, /**< WP violation occurred */
    _EMMC_DEV_LOCK_UNLOCK_FAIL      = 0x0004000F, /**< Lock/Unlock Failed */
    _EMMC_DEV_ILLEGAL_CMD_ERR       = 0x00040010, /**< Illegal command issued */
    _EMMC_DEV_ECC_FAIL              = 0x00040011, /**< Device ECC failed */
    _EMMC_DEV_CC_ERR                = 0x00040012, /**< Device undefined Error */
    _EMMC_DEV_ERR                   = 0x00040013, /**< Deverr for HC cmd */
    _EMMC_DEV_CIDCSD_OVRWRT_ERR     = 0x00040014, /**< CID/CSD overwrite err */
    _EMMC_DEV_WP_ERASE_SKIP_ERR     = 0x00040015, /**< WP Erase skip error */
    _EMMC_DEV_ERASE_RESET_ERR       = 0x00040016, /**< Erase reset error */
    _EMMC_DEV_SWITCH_ERR            = 0x00040017, /**< Switch command error */
    _EMMC_DEV_LOCKED                = 0x00040018, /**< Device is locked */
    _EMMC_DEV_EXCEPTION             = 0x00040019, /**< Exception evt occurred */
    _EMMC_DEV_DEVSTATE_ERR          = 0x0004001A, /**< Dev in incorrect state*/
    _EMMC_DEV_CMDLAYER_FAIL         = 0x0004001B, /**< CMD init/exit fail */
    _EMMC_DEV_INTR_FAIL             = 0x0004001C, /**< Int Hdl reg/dereg fail */
    _EMMC_DEV_ALREADY_DONE          = 0x0004001D, /**< Operation already done */
    _EMMC_DEV_PART_NOT_SUPPORTED    = 0x0004001E, /**< Partn not supported */
    _EMMC_DEV_PART_DONE_ERR         = 0x0004001F, /**< Partition already Done */
    _EMMC_DEV_PART_INVALID          = 0x00040020, /**< Partition not valid */
    _EMMC_DEV_PART_NOT_CREATED      = 0x00040021, /**< Partition not created */
    _EMMC_DEV_MAX_PARTS_EXCEEDED    = 0x00040022, /**< max 4 partns possible */
    _EMMC_DEV_PART_SIZE_ERR         = 0x00040023, /**< partn size not aligned */
    _EMMC_DEV_MAX_ENH_SIZE_ERR      = 0x00040024, /**< Enhanced size exceeded */
    _EMMC_DEV_EUDAADDR_ALIGN_ERR    = 0x00040025, /**< euda adr not wpg align */
    _EMMC_DEV_ENH_ATTRIB_NOT_SUPTD  = 0x00040026, /**< Enh attrib not suptd. */
    _EMMC_DEV_EXT_ATTRIB_NOT_SUPTD  = 0x00040027, /**< Ext attrib not suptd. */
    _EMMC_DEV_PART_SIZE_EXCEEDED    = 0x00040028, /**< part. size exceeded */
    _EMMC_DEV_SANITIZE_UNSUPPORTED  = 0x00040029, /**< Sanitize not supported */
    _EMMC_DEV_STS_INVALID           = 0x0004002A, /**< Invalid status */
    _EMMC_BM_INTR_ERR               = 0x00050001, /**< Intr err occured in BM */
    _EMMC_BM_STS_NG                 = 0x00050002, /**< BM status NG */
    _EMMC_INTR_INVALID_PARAM        = 0x00060001, /**< Invald parm in intr */
    _EMMC_INTR_ERR_MOD_TIMER        = 0x00060002, /**< Err in modifying timer */
    _EMMC_INTR_ERR_INIT             = 0x00060003, /**< Error in init function */
    _EMMC_INTR_ERR_EXIT             = 0x00060004, /**< Error in exit function */
    _EMMC_INTR_ERR_POLL             = 0x00060005, /**< Error in polling init*/
    _EMMC_INTR_STS_INVALID          = 0x00060006, /**< Intr status invalid */
}emmc_sts_e;

/**@}*/ //end of API_Enums

/*------------------ Data Structures & Custom Typedefs ----------------------*/

/*------------------------------ Externs ------------------------------------*/

/*---------------------------- Prototypes -----------------------------------*/

/** @addtogroup API_Prototypes API_Prototypes
 * @{
 */

/* initialization */
emmc_sts_e emmc_init(void);

/* exit */
emmc_sts_e emmc_exit(void);

/* read/write */
emmc_sts_e emmc_read(
    _ub32 uiSlot,
    _ub8 *pucBuf,
    _ub32 uiSize,
    _ub32 uiDevAdr);

emmc_sts_e emmc_write(
    _ub32 uiSlot,
    _ub8 *pucBuf,
    _ub32 uiSize,
    _ub32 uiDevAdr);

/* APIs to set HC config params */

/*
 * Config params applicable to HC and device side will be set to data base.
 * Every time these APIs are called,emmc_setConfig() should be called which will
 * actually update the HC
 */

/* Updates the bus width in the database */
emmc_sts_e emmc_setBusWidth(_ub32 uiSlot, com_busWidth_e width);

/* Updates the op mode in the database */
emmc_sts_e emmc_setOpMode(_ub32 uiSlot, com_modes_e mode);

/* Updates the clock frequency in the database */
emmc_sts_e emmc_setClock(_ub32 uiSlot, _ub32 uiVal);

/* This API will flush the data from the internal data base to HC */
emmc_sts_e emmc_setConfig(_ub32 uiSlot);

/* API to get the sector count from the device */
emmc_sts_e emmc_getDevMaxSect(_ub32 uiSlot, _ub32 *uiSectCnt);

/* API to get card specific information CSD from the device */
emmc_sts_e emmc_getDevInfo_CSD(
    _ub32 uiSlot,
    com_csd_params_t *pCSDParams);

/* API to get card specific information CID from the device */
emmc_sts_e emmc_getDevInfo_CID(
    _ub32 uiSlot,
    com_cid_params_t *pCIDParams);

/* Get the version */
emmc_sts_e emmc_getVersion(_ub32 *puiVersion);

/* API to get the attributes of the GPPs */
emmc_sts_e emmc_getGPPAttributes(
    _ub32 uiSlot,
    com_part_num_e ePartNum,
    com_gpp_attr_t *pPartAttr);

/* API to get the attributes of the EUDA */
emmc_sts_e emmc_getEUDAAttributes(
    _ub32 uiSlot,
    com_euda_attr_t *pPartAttr);

emmc_sts_e emmc_disableEmulationMode(
    _ub32 uiSlot);

/* API to get the access to GPPs and EUDA */
emmc_sts_e emmc_accessPartitions(
    _ub32 uiSlot,
    com_part_num_e ePartNum);

/* API to get the current accessed partition */
emmc_sts_e emmc_getCurrPartition(_ub32 uiSlot, _ub32 *puiPartNum);

/* API to cretae the GPPs and EUDA*/
emmc_sts_e emmc_createPartition(
    _ub32 uiSlot,
    _ub32 uiNumGpps,
    com_part_attr_t *pAttr);

/* API to get the write protect group size( in terms of bytes) */
emmc_sts_e emmc_getHCWPGrpSize(_ub32 uiSlot, _ub32 *puiSize);

/* API to get the maximum enhanced size of the memory */
emmc_sts_e emmc_getMaxEnhSize(_ub32 uiSlot, _ub32 *puiMaxEnhSize);

/* API to remove data - Erase/Trim/Discard/Sanitize */
 emmc_sts_e emmc_remData(_ub32 uiSlot,
     com_part_num_e ePartNum,
     _ub32 uiStartSectr,
     _ub32 uiEndSectr,
     com_rem_type_e eRemType);

/* API to remove data - Sanitize */
 emmc_sts_e emmc_sanitize(_ub32 uiSlot);

/* API to set Write Protection */
emmc_sts_e emmc_setWriteProt(
    _ub32 uiSlot,
    com_part_num_e ePartNum,
    com_wp_e uiDevSeg,
    com_wp_type_e uiProtType,
    _ub32 uiSectr);

/* API to Clear Write Protection */
emmc_sts_e emmc_clrWriteProt(
    _ub32 uiSlot,
    com_part_num_e ePartNum,
    com_wp_e uiDevSeg,
    com_wp_type_e uiProtType,
    _ub32 uiSectr);

/* API to get Write Protect Status */
emmc_sts_e emmc_getWPStat(
    _ub32 uiSlot,
    _ub32 uisectr,
    _ub32 *uiWpStat,
    _ub64 *ullWpType);

/* API to Lock/Unlock/Set PWD/Clear PWD/Force Erase */
emmc_sts_e emmc_devLkUnlk(
    _ub32 uiSlot,
    com_lkunlk_e eLkUnlk,
    _ub32 uiPwdLen,
    _ub8 *pucPwdBuf);

/* API to get the write protect group size( in terms of bytes) */
emmc_sts_e emmc_getWPGrpSize(_ub32 uiSlot, _ub32 *pullSize);

/* API to get the write protect Erase group size( in terms of bytes) */
emmc_sts_e emmc_getErsGrpSize(_ub32 uiSlot, _ub32 *pullSize);

/* API to get the Erase Memory content */
emmc_sts_e emmc_getErsMemContent(_ub32 uiSlot, _ub8 *pucErsMemCont);

/**@}*//* API_Prototypes */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _EMMC_API_H_ */

/**@} *//* EMMCAPIs */
/**@} *//* EMMCMemoryInterface */

