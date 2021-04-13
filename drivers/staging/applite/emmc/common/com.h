/**
 * @file          com.h
 *
 * \brief         This file includes macros and enums used commonly
 * by different modules
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
 * \b Date      : 02-Aug-2013
 */

/**
 * @addtogroup Common
 * @{
 */

/**
 * @addtogroup MacrosEnums
 * @{
 */

#ifndef _COM_H_
#define _COM_H_


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*----------------------- Header Files Inclusions ---------------------------*/

/*-------------------------- Macro Definitions ------------------------------*/

/** @addtogroup COM_DEFINES COM_DEFINES
 * @{
 */

#define _SLOT_VALID     1
#define _SLOT_INVALID   0
#define _COM_CSD_SIZE 16
#define _COM_CMD30_RET_SIZE 4
#define _COM_CMD31_RET_SIZE 8

/**@}*/ //end of COM_DEFINES

/*-------------------------- Enum Definitions -------------------------------*/

/** @addtogroup COM_Enums COM_Enums
 * @{
 */

/**
 * Enum related to the lines need to be reset during software reset
 */
typedef enum tag_com_resp_e
{
    _COM_RESP_01 = 0x0000,    /**< To indicate the response registers 0 and 1 */
    _COM_RESP_23 = 0x0001,    /**< To indicate the response registers 2 and 3 */
    _COM_RESP_45 = 0x0002,    /**< To indicate the response registers 4 and 5 */
    _COM_RESP_67 = 0x0003,    /**< To indicate the response registers 6 and 7 */
}com_resp_e;

/**
 * Enum related to the lines need to be reset during software reset
 */
typedef enum tag_com_swRst_e
{
    _COM_RST_ALL,    /**< reset all */
    _COM_RST_CMD,    /**< reset the command line */
    _COM_RST_DAT,    /**< reset the data line */
}com_swRst_e;

/**
 * @brief Enum related to the modes of data transfers
 */
typedef enum tag_com_modes_e
{
    _COM_MODE_PIO,      /**< Programmed IO using CPU mode of data transaction */
    _COM_MODE_SDMA,     /**< Single Operation mode of DMA data transaction */
    _COM_MODE_ADMA2,    /**< Advanced mode of DMA data transaction */
    _COM_MODE_RSV,      /**< Reserved */
}com_modes_e;

/**
 * @brief Enum related to the SD bus widths for data transfer
 */
typedef enum tag_com_busWidth_e
{
    _COM_BWIDTH_MIN,                          /**< Buswidth enum min value */
    _COM_BWIDTH_8 = _COM_BWIDTH_MIN,          /**< 8bit data line usage opt */
    _COM_BWIDTH_4,                            /**< 4bit data line usage opt */
    _COM_BWIDTH_1,                            /**< 1bit data line usage opt */
    _COM_BWIDTH_INVALID,                      /**< Invalid bit selection */
}com_busWidth_e;

/**
 * @brief Enum related to the voltage values possible for the Host controller
 */
typedef enum tag_com_volt_e
{
    _COM_VOLT3_3,           /**< SD bus 3.3 voltage selection */
    _COM_VOLT3_0,           /**< SD bus 3.0 voltage selection */
    _COM_VOLT1_8,           /**< SD bus 1.8 voltage selection */
}com_volt_e;

/**
 * @brief Enum to specify the direction of data transfer
 */
typedef enum tag_com_RWDir_e
{
    _COM_DIR_W,         /**< Write direction*/
    _COM_DIR_R,         /**< Read direction*/
}com_RWDir_e;

/**
 * @brief Enum for bus speed mode selection
 */
typedef enum tag_com_busSpeed_e
{
    _COM_SPEED_NORMAL,  /**< Normal mode */
    _COM_SPEED_HIGH,    /**< HS mode */
    _COM_SPEED_HS200    /**< HS200 mode */
}com_busSpeed_e;

/**
 * @brief Enum to hold different partition types
 */
typedef enum tag_com_part_type_e
{
    _COM_PART_TYPE_DEFAULT   = 0x0000, /**< default partition type */
    _COM_PART_TYPE_ENHANCED  = 0x0001, /**< enhanced partition type */
    _COM_PART_TYPE_EXTENDED  = 0x0002, /**< extended partition type */
    _COM_PART_TYPE_MAX       = 0x0003, /**< invalid partition type */
}com_part_type_e;

/**
 * @brief Enum to hold extended partition types
 */
typedef enum tag_com_ext_part_type_e
{
    _COM_EXT_PART_TYPE_DEFAULT  = 0x0000, /**< default ext partition .*/
    _COM_EXT_PART_TYPE_SYSCODE  = 0x0001, /**< to store system files */
    _COM_EXT_PART_TYPE_NONPERS  = 0x0002, /**< to store temp files */
    _COM_EXT_PART_TYPE_MAX      = 0x0003, /**< invalid ext partition type */
}com_ext_part_type_e;

/**
 * @brief Enum to hold different partition numbers
 */
typedef enum tag_com_part_num_e
{
    _COM_PARTITION_UDA               = 0x0000, /**< User Data Area */
    _COM_PARTITION_GPP1              = 0x0001, /**< GPP type 1 */
    _COM_PARTITION_GPP2              = 0x0002, /**< GPP type 2 */
    _COM_PARTITION_GPP3              = 0x0003, /**< GPP type 3 */
    _COM_PARTITION_GPP4              = 0x0004, /**< GPP type 4 */
    _COM_PARTITION_MAX               = 0x0005, /**< invalid partition number */
}com_part_num_e;

/**
 * @brief Enum to hold data removal types
 */
typedef enum tag_com_rem_type_e
{
    _COM_ERASE = 0x0,           /**< Removal type: Erase */
    _COM_TRIM,                  /**< Removal type: Trim */
    _COM_SANITIZE,              /**< Removal type: Sanitize */
    _COM_DISCARD,               /**< Removal type: Discard */
    _COM_REM_TYP_INVALID,       /**< Invalid Removal type */
}com_rem_type_e;

/**
 * @brief Enum to hold write protect
 */
typedef enum tag_com_wp_e
{
    _COM_DEV = 0x0,             /**< Write protect entire device */
    _COM_SEG,                   /**< Write protect segments of device */
    _COM_WP_INVALID,            /**< Invalid type */
}com_wp_e;

/**
 * @brief Enum to hold write protect types
 */
typedef enum tag_com_wp_type_e
{
    _COM_PERM= 0x0,             /**< Permanent write protection */
    _COM_TEMP,                  /**< Temporary write protection */
    _COM_PWR,                   /**< Power-on write protection */
    _COM_WP_TYPE_INVALID,       /**< Invalid type */
}com_wp_type_e;

/**
 * @brief Get either WP status or WP type
 */
typedef enum tag_com_wpstat_e
{
    _COM_GET_WP_STATUS = 0x0,    /**< Get WP status */
    _COM_GET_WP_TYP,             /**< Get WP type */
}com_wpstat_e;

/**
 * @brief Enum to hold lock/unlock command types
 */
typedef enum tag_com_lkunlk_e
{
    _COM_UNLOCK = 0x0,       /**< Unlock device */
    _COM_LOCK,               /**< Lock device */
    _COM_SET_PWD,            /**< Set password */
    _COM_CLR_PWD,            /**< Clear password */
    _COM_SET_PWD_LOCK,       /**< Set password and Lock device */
    _COM_FORCE_ERASE,        /**< Force erase */
    _COM_FORCE_ERASE_OTHER,  /**< For testing only: set erase bit + other bit */
    _COM_LKUNLK_INVALID,     /**< Invalid type */
}com_lkunlk_e;

/**@}*/ //end of COM_Enums

/*------------------ Data Structures & Custom Typedefs ----------------------*/

/** @defgroup COM_Structures COM_Structures
 * @{
 */

/**
 * @brief Struct to hold the values of general purpose partitions
 */
typedef struct tag_com_gpp_attr_t
{
    com_part_type_e eType;         /**< partition type */
    com_ext_part_type_e eExtType;  /**< ext partition type */
    _ub32 uiPartSize;              /**< GPP size in sector units */
}com_gpp_attr_t;

/**
 * @brief Struct to hold the values of enhanced user data area attributes
 */
typedef struct tag_com_euda_attr_t
{
    _ub32 uiStartAddr;    /**< start address of the enhanced uda */
    _ub32 uiSize;         /**< size of the EUDA */
    _ub8 uiEnhbit;        /**< Partition attribute bit */
}com_euda_attr_t;

/**
 * @brief Struct to hold the GPP attr. as well as EUDA attr.
 */
typedef struct tag_com_part_attr_t
{
    com_gpp_attr_t *pGattr;         /**< GPP attribs structure */
    com_euda_attr_t *pEattr;        /**< EUDA attr. structure */
}com_part_attr_t;

/**
 * @brief Struct to hold Scatter Gather element physical address and size
 */
typedef struct tag_com_sg_t
{
    _ub32 dmaAddr;  /**< Physical address of SG element */
    _ub32 uiSize;   /**< Current SG element size */
}com_sg_t;

/**
 * @brief Struct to hold Scatter Gather element array pointer and total element
 */
typedef struct tag_com_sglist_t
{
    com_sg_t *paEle;      /**< Array of SG elements */
    _ub32    uiTotal;     /**< Number of valid SG elements */
}com_sglist_t;

/**
 * @brief Struct to store CID details of eMMC device.
 */
typedef struct tag_com_cid_params_t
{
    _ub8 ucManuID;     /**< Manufacturer ID */
    _ub8 ucRsvd1;      /**< Reserved field */
    _ub8 ucDevType;    /**< Device type: Removable/Embedded */
    _ub8 ucOID;        /**< OEM/Appln ID */

    _ub8 ucPdtName[6]; /**< Product Name */
    _ub8 ucAlignVar1;  /**< Inserted for memory alignment purpose */
    _ub8 ucAlignVar2;  /**< Inserted for memory alignment purpose */

    _ub8 ucPdtRev;     /**< Product Revision */
    _ub8 ucAlignVar3;  /**< Inserted for memory alignment purpose */
    _ub8 ucAlignVar4;  /**< Inserted for memory alignment purpose */
    _ub8 ucAlignVar5;  /**< Inserted for memory alignment purpose */

    _ub32 uiPdtSlNo;   /**< Product Serial Number */

    _ub8 ucManuDt;     /**< Manufacturing date */
    _ub8 ucCrc7;       /**< CRC7 checksum */
    _ub8 ucAlignVar6;  /**< Inserted for memory alignment purpose */
    _ub8 ucAlignVar7;  /**< Inserted for memory alignment purpose */
}com_cid_params_t;

/**
 * @brief Struct to store CSD details of eMMC device
 */
typedef struct tag_com_csd_params_t
{
    _ub8 ucCSDVer;     /**< CSD version */
    _ub8 ucSpecsVer;   /**< eMMC s/m spec version */
    _ub8 ucTAAC;       /**< TAAC: Async part of data access time */
    _ub8 ucRsvd1;      /**< Reserved field */

    _ub8 ucNSAC;       /**< NSAC: Data access time; Clock-depend factor*/
    _ub8 ucTrnsSpeed;  /**< Transfer speed */
    _ub16 usCCC;       /**< Device command classes supported */

    _ub8 ucRdBlkLen;   /**< Max. read data block length supported */
    _ub8 ucPartRdBlkEn;/**< Partial blocks for read allowed or not */
    _ub8 ucWrMisalign; /**< Write datablk can be spread ovr >1 phy blk */
    _ub8 ucRdMisalign; /**< Read datablk can be spread over >1 phy blk */

    _ub8 ucDSRImp;     /**< Driver Stage Reg(DSR) implemented or not */
    _ub8 ucRsvd2;      /**< Reserved field */
    _ub16 usCSize;     /**< Used to compute device capacity */

    _ub8 ucRdMinCurr;  /**< Max values of read current at min power ip */
    _ub8 ucWrMinCurr;  /**< Max values of write current at min power ip*/
    _ub8 ucRdMaxCurr;  /**< Max values of read current at max power ip */
    _ub8 ucWrMaxCurr;  /**< Max values of write current at max power ip*/

    _ub8 ucCsizeMult;  /**< Used to compute device capacity */
    _ub8 ucEraseGrpSiz;/**< Used to calculate size of erasable unit */
    _ub8 ucEraseGrpMul;/**< Used to calculate size of erasable unit */
    _ub8 ucWPGrpSize;  /**< Min size of write protected region */

    _ub8 ucWPEnable;   /**< Write protection is possible or not */
    _ub8 ucDefECC;     /**< Default ECC code set by manufacturer */
    _ub8 ucR2WFactor;  /**< Blk prgm time:multiple of read access time */
    _ub8 ucWrBlkLen;   /**< Max. write data block length supported */

    _ub8 ucPartWrBlkEn;/**< Partial blocks for write allowed or not */
    _ub8 ucRsvd3;      /**< Reserved field */
    _ub8 ucContProtEn; /**< Content Protection Enabled or not */
    _ub8 ucFileFormGrp;/**< Selected group of file formats */

    _ub8 ucCopy;       /**< Denotes if content is copy or original.OTP */
    _ub8 ucPermWP;     /**< Permanent Write Protect */
    _ub8 ucTempWP;     /**< Temporary Write Protect */
    _ub8 ucFileFormat; /**< File format on the device */

    _ub8 ucECC;        /**< ECC code used for storing data on device */
    _ub8 ucCRC;        /**< CRC Check sum for CSD contents */
    _ub8 ucAlignVar8;  /**< Inserted for memory alignment purpose */
    _ub8 ucAlignVar9;  /**< Inserted for memory alignment purpose */
}com_csd_params_t;

/**@}*/ // COM_Structures

/*------------------------------ Externs ------------------------------------*/

/*---------------------------- Prototypes -----------------------------------*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _COM_H_ */

/**@}*//* MacrosEnums */
/**@}*//* Common */

