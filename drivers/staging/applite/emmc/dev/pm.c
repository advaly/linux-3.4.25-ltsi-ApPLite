/**
 * @file          pm.c
 *
 * \brief         Source file of partiiton management.
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

/*----------------------- Header Files Inclusions ---------------------------*/
#include "os.h"       /* To use OS service APIs */
#include "com.h"      /* To use the common enums and macros */
#include "config.h"   /* To use vendor specific macros/enums */
#include "debug.h"    /* To use the debug zone prints */
#include "dev_com.h"  /* Common header file for sequence & PM */

/*-------------------------- Macro Definitions ------------------------------*/

/** @addtogroup Seq_DEFINES Seq_DEFINES
 * @{
 */

/* Debug prints definitions */
#ifdef __DEBUG
#define _PM_DBG_INFO(__format__, arg...)    \
    dz_print(_DZ_DEV, "[%4d]%s::" __format__"\n", __LINE__,    \
    __FUNCTION__,## arg )

#define _PM_DBG_ERR(__format__, arg...)    \
    dz_print(_DZ_CRTICAL, "[%4d]%s::" __format__"\n", __LINE__,    \
    __FUNCTION__,## arg )
#else /* !__DEBUG */
#define _PM_DBG_INFO(__format__, arg...)
#define _PM_DBG_ERR(__format__, arg...)
#endif /* __DEBUG */

/* Masks for Partition Management */
#define _PART_SUPPORT_MASK     0x07  /* Mask for partition en, enh ,ext bits */
#define _PART_COMPLETED_MASK   0x01  /* Mask for partition complete bit */
#define _PART_EUDA_MASK        0x01  /* Mask for EUDA attrib */
#define _PART_GPP1_MASK        0x02  /* Mask for GPP1 attrib */
#define _PART_GPP2_MASK        0x04  /* Mask for GPP2 attrib */
#define _PART_GPP3_MASK        0x08  /* Mask for GPP3 attrib */
#define _PART_GPP4_MASK        0x10  /* Mask for GPP4 attrib */
#define _PART_EXTATTR0_MASK    0x0F  /* Mask for Extended attrib low nibble */
#define _PART_EXTATTR1_MASK    0xF0  /* Mask for Extended attrib high nibble */
#define _PART_CONFIG_MASK      0x07  /* Mask for accessing different partns*/
#define _ERASE_GRP_DEF_MASK    0x01  /* Mask for Erase Group Def Bit */

/* Macros to access various Partitions */
#define _PART_ACCESS_UDA       0x00  /* Value to access UDA */
#define _PART_ACCESS_GPP1      0x04  /* Value to access GPP1 */
#define _PART_ACCESS_GPP2      0x05  /* Value to access GPP2 */
#define _PART_ACCESS_GPP3      0x06  /* Value to access GPP3 */
#define _PART_ACCESS_GPP4      0x07  /* Value to access GPP4 */

#define _1024B                1024                 /* The value of 1024 bytes */
#define _MAX_GPP_SIZE         4294967295U          /* Max.GPP size(sectors) */
#define _MAX_GPP_PARTITIONS   4                    /* Maximum 4 partns */
#define _MAX_GPP_BYTES        3                    /* 3 Bytes for each GPP */
#define _MAX_EUDA_ADR_BYTES   4                    /* 4 Bytes for EUDA Addr */
#define _MAX_EUDA_SIZE_BYTES  3                    /* 3 Bytes for EUDA Size */

/**@}*/ // Seq_DEFINES

/*-------------------------- Enum Definitions -------------------------------*/

/*------------------ Data Structures & Custom Typedefs ----------------------*/

/** @defgroup Seq_Structures Seq_Structures
 * @{
 */

/**
 * @brief Struct to hold the values for partition enable,
 * @brief enhanced attribute enable,
 * @brief extended attribute enable
 */
typedef struct tag_partitionflags_t
{
    _ub32 uiPartitionEn;       /**< flag for partition enable */
    _ub32 uiEnhAttrEn;         /**< flag for enhanced attr enable */
    _ub32 uiExtAttrEn;         /**< flag for extended attr enable */
}partitionflags_t;

/**@}*/ // Seq_Structures

/*---------------------------- Prototypes -----------------------------------*/

/** @addtogroup Seq_Prototypes Seq_Prototypes
 * @{
 */

/* Function to check whether partition feature is supported or not */
static dev_sts_e checkPartitionSupport(_ub32 uiSlot);

/* Function to check whether partitions has been created or not */
static __inline dev_sts_e checkPartitionDone(_ub32 uiSlot);

/* Function to calculate the size of the GPP */
static _ub32 calculateGPPSize(_ub32 uiSlot, _ub32 uiGppOfs);

/* Function to calculate the size bytes to be set for GPP and EUDA */
static dev_sts_e calcGPPSizeBytes(
    _ub32 uiSlot,
    _ub32 uiSize,
    _ub8 *puiBytes);

/**@}*/ // Seq_Prototypes

/*------------- Data variable/Structure allocation (global) -----------------*/

/** @addtogroup Seq_Globals Seq_Globals
 * @{
 */

/* Struct variable to hold the flags for partn support, enh & ext support */
static partitionflags_t pm_tPartFlags[_MAX_SLOTS];

/**@}*/ // Seq_Globals

/*----------------------- Function Definitions ------------------------------*/

/** @addtogroup Seq_Functions Seq_Functions
 * @{
 */

/**
 * @brief Func to check if the partition is supported by the device
 *
 * @param[in] uiSlot Host Controller slot number
 *
 * @retval _DEV_PARTITION_NOT_SUPPORTED Partitioning not supported
 * @retval _DEV_STS_OK Partitionitning supported
 */
 static dev_sts_e checkPartitionSupport(_ub32 uiSlot)
{
    _ub8 uiRegVal;
    extcsdinfo_t *pExtCSD;
    partitionflags_t *pPartFlags;

    pPartFlags = &pm_tPartFlags[uiSlot];

    pExtCSD = &seq_tEXTCSDInfo[uiSlot];

    /* Read the partition Support information */
    uiRegVal = pExtCSD->ucBuf[_EXTCSD_PART_SUPPORT_OFST];
    _PM_DBG_INFO("partition support bits: 0x%08x", uiRegVal);
    uiRegVal = (uiRegVal & _PART_SUPPORT_MASK);

    switch(uiRegVal)
    {
        /* All three are supported */
        case 0x7:
            pPartFlags->uiPartitionEn = 1;
            pPartFlags->uiEnhAttrEn = 1;
            pPartFlags->uiExtAttrEn = 1;
        break;

        /* Enhanced attribute is not supported */
        case 0x5:
            pPartFlags->uiPartitionEn = 1;
            pPartFlags->uiEnhAttrEn = 0;
            pPartFlags->uiExtAttrEn = 1;
        break;

        /* Extended attribute is not supported */
        case 0x3:
            pPartFlags->uiPartitionEn = 1;
            pPartFlags->uiEnhAttrEn = 1;
            pPartFlags->uiExtAttrEn = 0;
        break;

        /* Only partitioning is supported */
        case 0x1:
            pPartFlags->uiPartitionEn = 1;
            pPartFlags->uiEnhAttrEn = 0;
            pPartFlags->uiExtAttrEn = 0;
        break;

        /* Nothing is supported */
        default:
            pPartFlags->uiPartitionEn = 0;
            pPartFlags->uiEnhAttrEn = 0;
            pPartFlags->uiExtAttrEn = 0;
        return _DEV_PARTITION_NOT_SUPPORTED;
    }

    return _DEV_STS_OK;
}

/**
 * @brief Func to check if the partition is done in the device
 *
 * @param[in] uiSlot Host Controller slot number
 *
 * @retval _DEV_STS_OK Partition can be created
 * @retval _DEV_PARTITION_DONE_ERR Partition is already done in the device
 */
static __inline dev_sts_e checkPartitionDone(_ub32 uiSlot)
{
    _ub8 uiRegVal;
    extcsdinfo_t *pExtCSD;

    pExtCSD = &seq_tEXTCSDInfo[uiSlot];
    uiRegVal = pExtCSD->ucBuf[_EXTCSD_PART_COMPLETED_OFST];
    _PM_DBG_INFO("partition completed bits: 0x%08x", uiRegVal);
    uiRegVal = (uiRegVal & _PART_COMPLETED_MASK);

    if(uiRegVal == 0x1)
    {
        return _DEV_PARTITION_DONE_ERR;
    }
    else
    {
        return _DEV_STS_OK;
    }
}

/**
 * @brief Func to calculate the GPP size in sectors
 *
 * @param[in] uiSlot Host Controller slot number
 * @param[in] uiGppOfs offset in the EXTCSD Register
 *
 * @retval _ub32 The value from the device
 */
static _ub32 calculateGPPSize(_ub32 uiSlot, _ub32 uiGppOfs)
{
    _ub8 uiSize[3] = {0};
    _ub32 uiGppSize = 0;
    _ub8 uiHCWPGrpSize = 0;
    _ub8 uiHCErsGrpSize = 0;
    extcsdinfo_t *pExtCSD;

    pExtCSD = &seq_tEXTCSDInfo[uiSlot];

    uiHCWPGrpSize = pExtCSD->ucBuf[_EXTCSD_HCWPGRP_OFST];
    uiHCErsGrpSize = pExtCSD->ucBuf[_EXTCSD_HCERSGRP_OFST];

    /* Get the size bytes from the appropriate offset */
    uiSize[0] = pExtCSD->ucBuf[uiGppOfs];
    uiGppOfs += 1;
    uiSize[1] = pExtCSD->ucBuf[uiGppOfs];
    uiGppOfs += 1;
    uiSize[2] = pExtCSD->ucBuf[uiGppOfs];

    _PM_DBG_INFO("-----uiSize[2] = %d-----\n",uiSize[2]);
    _PM_DBG_INFO("-----uiSize[1] = %d-----\n",uiSize[1]);
    _PM_DBG_INFO("-----uiSize[0] = %d-----\n",uiSize[0]);
    _PM_DBG_INFO("-----uiHCWPGrpSize = %d-----\n",uiHCWPGrpSize);
    _PM_DBG_INFO("-----uiHCErsGrpSize = %d-----\n",uiHCErsGrpSize);

    /* Calculate the GPP size */
    uiGppSize = ((uiSize[2] << 16)+(uiSize[1] << 8)+(uiSize[0] << 0));
    /* Gpp size is returned in terms of sector count */
    uiGppSize = (uiGppSize * uiHCWPGrpSize * uiHCErsGrpSize * _1024B);
    _PM_DBG_INFO("-----ulGppSize = %d-----\n",uiGppSize);

    return uiGppSize;
}

/**
 * @brief Func to calculate the bytes to be set for GPP Size
 *
 * @param[in]  uiSlot Host Controller slot number
 * @param[in]  uiSize Size of the partition
 * @param[out] puiBytes Holds the resultant size bytes
 *
 * @retval _DEV_PARTITION_SIZE_EXCEEDED Size > Max GPP Size
 * @retval _DEV_STS_OK Function executed successfully
 */
static dev_sts_e calcGPPSizeBytes(
    _ub32 uiSlot,
    _ub32 uiSize,
    _ub8 *puiBytes)
{
    _ub32 uiSizeFact = 0;
    _ub32 uiTempVal = 0;
    _ub32 uiChkSize = 0;
    _ub8 uiHCWPGrpSize = 0;
    _ub8 uiHCErsGrpSize = 0;
    extcsdinfo_t *pExtCSD;
    pExtCSD = &seq_tEXTCSDInfo[uiSlot];

    if(uiSize > _MAX_GPP_SIZE)
    {
        return _DEV_PARTITION_SIZE_EXCEEDED;
    }

    uiHCWPGrpSize = pExtCSD->ucBuf[_EXTCSD_HCWPGRP_OFST];
    uiHCErsGrpSize = pExtCSD->ucBuf[_EXTCSD_HCERSGRP_OFST];

    /* Calcualte the size factor as per the device spec */
    uiSizeFact = uiSize / (uiHCWPGrpSize * uiHCErsGrpSize * _1024B);

    /* if uiSizeFact < 256 only first byte is enough */
    if(uiSizeFact < 256)
    {
        puiBytes[2] = 0;
        puiBytes[1] = 0;
        puiBytes[0] = uiSizeFact;
    }
    /* if uiSizeFact < 65536 two bytes are enough */
    else if(uiSizeFact < 65536)
    {
        puiBytes[2] = 0;
        uiTempVal = (uiSizeFact - 255);
        puiBytes[1] = (uiTempVal >> 8);
        puiBytes[0] = 0xFF;
    }
    /* all three bytes are required */
    else
    {
        uiTempVal = (uiSizeFact - 65535);
        puiBytes[2] = (uiTempVal >> 16);
        puiBytes[1] = 0xFF;
        puiBytes[0] = 0xFF;
    }

    /* Recalculate the Size and validate if the calculations are proper */
    uiChkSize = (uiHCWPGrpSize * uiHCErsGrpSize * _1024B) * \
        ((puiBytes[2] << 16) + (puiBytes[1] << 8) + puiBytes[0]);

    if(uiChkSize != uiSize)
    {
        _PM_DBG_ERR("calcGPPSizeBytes Error \n");
    }

    _PM_DBG_INFO("-----puiBytes[2] = %d-----\n",puiBytes[2]);
    _PM_DBG_INFO("-----puiBytes[1] = %d-----\n",puiBytes[1]);
    _PM_DBG_INFO("-----puiBytes[0] = %d-----\n",puiBytes[0]);
    _PM_DBG_INFO("-----uiChkSize = %d-----\n",uiChkSize);
    _PM_DBG_INFO("-----uiSize = %d-----\n",uiSize);

    return _DEV_STS_OK;
}

/**
 * @brief Gets the EUDA attributes of the device.
 *
 * @param[in]  uiSlot Host controller Slot no
 * @param[out] pPartAttr the pointer in which the attributes are returned
 *
 * @retval _DEV_PARTITION_NOT_CREATED Partition is not created
 * @retval _DEV_STS_OK The function is successful
 */
dev_sts_e pm_getEUDAAttributes(
    _ub32 uiSlot,
    com_euda_attr_t *pPartAttr)
{
    _ub32 uiStartAddr = 0;
    _ub32 uiEUDASize = 0;
    _ub8 uiHCWPGrpSize = 0;
    _ub8 uiHCErsGrpSize = 0;
    _ub8 uiSize[3] = {0};
    _ub8 uiPartbit = 0;
    com_euda_attr_t *pEUDAttr;
    _ub8 *puiBuf;

    /* input argument is not validated */

    puiBuf = &seq_tEXTCSDInfo[uiSlot].ucBuf[0];

    /* if partn. is not created return error */
    if(1 != (puiBuf[_EXTCSD_PART_COMPLETED_OFST] & 0x01))
    {
        return _DEV_PARTITION_NOT_CREATED;
    }

    /* Local pointer which points to the address of the argument */
    pEUDAttr = pPartAttr;

    /* Get the partition enhance bit form the EXTCSD Register */
    uiPartbit = puiBuf[_EXTCSD_PART_ATTRIBUTE_OFST];
    uiPartbit = (uiPartbit & _PART_EUDA_MASK);

    /* If partn. bit not set EUDA not created */
    if((0 == uiPartbit))
    {
        return _DEV_PARTITION_NOT_CREATED;
    }

    /* Get the start address of the EUDA from the appropriate offset */
    uiStartAddr = puiBuf[_EXTCSD_ENH_START_ADR_3_OFST];
    uiStartAddr = uiStartAddr << 24;
    uiStartAddr |= (puiBuf[_EXTCSD_ENH_START_ADR_2_OFST] << 16);
    uiStartAddr |= (puiBuf[_EXTCSD_ENH_START_ADR_1_OFST] << 8);
    uiStartAddr |= (puiBuf[_EXTCSD_ENH_START_ADR_0_OFST]);
    _PM_DBG_INFO("EUDA Addr : 0x%08x\n",uiStartAddr);

    /* Get the size bytes of the EUDA */
    uiSize[2] = puiBuf[_EXTCSD_ENH_SIZE_2_OFST];
    uiSize[1] = puiBuf[_EXTCSD_ENH_SIZE_1_OFST];
    uiSize[0] = puiBuf[_EXTCSD_ENH_SIZE_0_OFST];

    /* Calculate the EUDA size from the bytes above */
    uiEUDASize = ((uiSize[2] << 16)+(uiSize[1] << 8)+(uiSize[0] << 0));

    /* If EUDA size is zero then EUDA not created */
    if((0 == uiEUDASize))
    {
        return _DEV_PARTITION_NOT_CREATED;
    }

    uiHCWPGrpSize = puiBuf[_EXTCSD_HCWPGRP_OFST];
    uiHCErsGrpSize = puiBuf[_EXTCSD_HCERSGRP_OFST];
    /* EUDA size is returned in terms of sector counts */
    uiEUDASize = (uiEUDASize * uiHCWPGrpSize * uiHCErsGrpSize * _1024B);
    _PM_DBG_INFO("EUDA Size : %d\n",uiEUDASize);

    /* Fill the structure with the values obtained */
    pEUDAttr->uiStartAddr = uiStartAddr;
    pEUDAttr->uiSize = uiEUDASize;
    pEUDAttr->uiEnhbit = uiPartbit;

    return _DEV_STS_OK;
}

/**
 * @brief Gets the partition attributes of the device.
 *
 * @param[in]  uiSlot Host controller Slot no
 * @param[in]  ePartNumber the partition for which attributes is requested
 * @param[out] pPartAttr the pointer in which the attributes are returned
 *
 * @retval _DEV_PARTITION_INVALID Invalid partition number given as i/p
 * @retval _DEV_PARTITION_NOT_CREATED Partition is not created
 * @retval _DEV_STS_OK The function is successful
 */
dev_sts_e pm_getGPPAttributes(
    _ub32 uiSlot,
    com_part_num_e ePartNumber,
    com_gpp_attr_t *pPartAttr)
{
    _ub32 uiGppSize = 0;
    _ub32 uiGppOfs = 0;
    _ub8 uiPartbit = 0;
    _ub8 uiExtAttrbit = 0;
    com_gpp_attr_t *pGPPattrib;
    extcsdinfo_t *pExtCSD;

    /* input argument is not validated */

    pExtCSD = &seq_tEXTCSDInfo[uiSlot];

    /* Get the partition attribute bit from the EXTCSD register */
    uiPartbit = pExtCSD->ucBuf[_EXTCSD_PART_ATTRIBUTE_OFST];
    if(1 != (pExtCSD->ucBuf[_EXTCSD_PART_COMPLETED_OFST] & 0x01))
    {
        return _DEV_PARTITION_NOT_CREATED;
    }
    else
    {
        pGPPattrib = pPartAttr;
        switch(ePartNumber)
        {
            /* Get the partition attributes like enhanced or extended */
            case _COM_PARTITION_GPP1:
                uiGppOfs = _EXTCSD_GP_SIZE_1_0_OFST;
                uiPartbit = (uiPartbit & _PART_GPP1_MASK);
                uiExtAttrbit = pExtCSD->ucBuf[_EXTCSD_EXT_PART_ATTR1_OFST];
            break;

            case _COM_PARTITION_GPP2:
                uiGppOfs = _EXTCSD_GP_SIZE_2_0_OFST;
                uiPartbit = (uiPartbit & _PART_GPP2_MASK);
                uiExtAttrbit = pExtCSD->ucBuf[_EXTCSD_EXT_PART_ATTR1_OFST];
                uiExtAttrbit = uiExtAttrbit >> 4;
            break;

            case _COM_PARTITION_GPP3:
                uiGppOfs = _EXTCSD_GP_SIZE_3_0_OFST;
                uiPartbit = (uiPartbit & _PART_GPP3_MASK);
                uiExtAttrbit = pExtCSD->ucBuf[_EXTCSD_EXT_PART_ATTR2_OFST];
            break;

            case _COM_PARTITION_GPP4:
                uiGppOfs = _EXTCSD_GP_SIZE_4_0_OFST;
                uiPartbit = (uiPartbit & _PART_GPP4_MASK);
                uiExtAttrbit = pExtCSD->ucBuf[_EXTCSD_EXT_PART_ATTR2_OFST];
                uiExtAttrbit = uiExtAttrbit >> 4;
            break;

            default:
            return _DEV_PARTITION_INVALID;
        }

        /* Last 4 bits indicate the type of Extended Attribute */
        uiExtAttrbit = uiExtAttrbit & 0x0000000FU;

        /* Decide based on the attributes whether it is enhanced or extended */
        if(0 != uiPartbit)
        {
            pGPPattrib->eType = _COM_PART_TYPE_ENHANCED;
            pGPPattrib->eExtType = uiExtAttrbit;
        }
        else if(0 == uiExtAttrbit)
        {
            pGPPattrib->eType = _COM_PART_TYPE_DEFAULT;
            pGPPattrib->eExtType = uiExtAttrbit;
        }
        else
        {
            pGPPattrib->eType = _COM_PART_TYPE_EXTENDED;
            pGPPattrib->eExtType = uiExtAttrbit;
        }

        /* Calculate the size of the GPP */
        uiGppSize = calculateGPPSize(uiSlot, uiGppOfs);
        _PM_DBG_INFO("GPP Size : %d\n",uiGppSize);
        pGPPattrib->uiPartSize = uiGppSize;
    }

    if((0 == uiGppSize))
    {
        return _DEV_PARTITION_NOT_CREATED;
    }

    return _DEV_STS_OK;
}

/**
 * @brief Sets the access to a particular partition
 *
 * @param[in] uiSlot Host controller Slot no
 * @param[in] ePartNum Partition number to be accessed
 *
 * @retval _DEV_PARTITION_INVALID Invalid partition number given as i/p
 * @retval _DEV_PARTITION_NOT_CREATED Partition is not created
 * @retval _DEV_STS_OK The function is successful
 */
dev_sts_e pm_accessPartitions(
    _ub32 uiSlot,
    com_part_num_e ePartNum)
{
    _ub8 uiRegVal = 0;
    _ub32 uiVal = 0;
    _ub32 uiOffst = 0;
    dev_sts_e eSts = _DEV_STS_OK;
    extcsdinfo_t *pExtCSD;

    /* input argument is not validated */

    pExtCSD = &seq_tEXTCSDInfo[uiSlot];

    /* For UDA no need to check partition completed bit */
    if(_COM_PARTITION_UDA != ePartNum)
    {
        /* if partn. is not created return error */
        if(1 != (pExtCSD->ucBuf[_EXTCSD_PART_COMPLETED_OFST] & 0x01))
        {
            return _DEV_PARTITION_NOT_CREATED;
        }
    }

    /* Read the partition_config offset */
    uiOffst = _EXTCSD_PART_CONFIG_OFST;
    uiRegVal = pExtCSD->ucBuf[uiOffst];
    uiRegVal = (uiRegVal & (~(_PART_CONFIG_MASK)));
    _PM_DBG_INFO("uiRegVal = 0x%08x\n",uiRegVal);

    /* Based on the partn no. set the appropriate bits in partn. config */
    switch(ePartNum)
    {
        case _COM_PARTITION_UDA:
            uiRegVal |= _PART_ACCESS_UDA;
            uiVal = (_ub32)uiRegVal;
        break;

        case _COM_PARTITION_GPP1:
            uiRegVal |= _PART_ACCESS_GPP1;
            uiVal = (_ub32)uiRegVal;
        break;

        case _COM_PARTITION_GPP2:
            uiRegVal |= _PART_ACCESS_GPP2;
            uiVal = (_ub32)uiRegVal;
        break;

        case _COM_PARTITION_GPP3:
            uiRegVal |= _PART_ACCESS_GPP3;
            uiVal = (_ub32)uiRegVal;
        break;

        case _COM_PARTITION_GPP4:
            uiRegVal |= _PART_ACCESS_GPP4;
            uiVal = (_ub32)uiRegVal;
        break;

        /* Invalid Partition Error */
        default:
        return _DEV_PARTITION_INVALID;
    }

    _PM_DBG_INFO("uival = %d\n",uiVal);

    eSts = seq_writeExtCSD(uiSlot,uiOffst,uiVal);
    _PM_DBG_INFO("eSts = 0x%08x\n",eSts);
    if(_DEV_STS_OK != eSts)
    {
        /* If switch error occurs then partition not created */
        if(_DEV_SWITCH_ERR == eSts)
        {
            _PM_DBG_ERR("Partition not created");
            return _DEV_PARTITION_NOT_CREATED;
        }
        else
        {
            _PM_DBG_ERR("seq_writeExtCSD Failed");
            return eSts;
        }
    }

    /* Updating the global struct so that readEXTCSD can be avoided later */
    pExtCSD->ucBuf[uiOffst] = uiRegVal;

    return _DEV_STS_OK;
}

/**
 * @brief gets the current accessed partition
 *
 * @param[in] uiSlot Host controller Slot no
 *
 * @retval com_part_num_e The current accessed partition
 */
com_part_num_e pm_getCurrPartition(_ub32 uiSlot)
{
    _ub8 *puiBuf;
    _ub32 uiNum = 0;

    /* input argument is not validated */

    puiBuf = &seq_tEXTCSDInfo[uiSlot].ucBuf[0];

    /* Read the currently accessed partition from PARTITION_CONFIG field */
    uiNum = (puiBuf[_EXTCSD_PART_CONFIG_OFST] & _PART_CONFIG_MASK);
    switch(uiNum)
    {
        case 0x00:
            return _COM_PARTITION_UDA;

        case 0x04:
            return _COM_PARTITION_GPP1;

        case 0x05:
            return _COM_PARTITION_GPP2;

        case 0x06:
            return _COM_PARTITION_GPP3;

        case 0x07:
            return _COM_PARTITION_GPP4;

        default:
            return (com_part_num_e)uiNum;
    }
}

/**
 * @brief Gets the High Capacity Write Protect Grp Size from the device
 *
 * @param[in] uiSlot Host Controller slot number
 *
 * @retval _ub32 The value(in terms of sectors) from the device
 */
 _ub32 pm_getHCWPGrpSize(_ub32 uiSlot)
{
    _ub8 uihcwpgrpval;
    _ub32 uiHCWPGSize = 0;
    _ub8 uihcersgrpval = 0;
    extcsdinfo_t *pExtCSD;

    /* input argument is not validated */

    pExtCSD = &seq_tEXTCSDInfo[uiSlot];

    /* get the val. from the offsets and calculate size */
    uihcwpgrpval = pExtCSD->ucBuf[_EXTCSD_HCWPGRP_OFST];
    uihcersgrpval = pExtCSD->ucBuf[_EXTCSD_HCERSGRP_OFST];
    /* HCWPG is returned in terms of sector counts */
    uiHCWPGSize = ((_ub32)uihcwpgrpval * (_ub32)uihcersgrpval * _1024B);

    _PM_DBG_INFO("HCWriteProtectGrpSize = %d\n",uiHCWPGSize);

    return uiHCWPGSize;
}

/**
 * @brief Gets the max value of enhanced area possible in device (in sectors)
 *
 * @param[in]  uiSlot Host controller Slot no
 *
 * @retval _ub32 Returns the maximum enhance size(sectors) allowed in the device
 */
_ub32 pm_getMaxEnhSize(_ub32 uiSlot)
{
    _ub32 uiMaxEnhVal = 0;
    _ub32 uiOffst = 0;
    _ub32 uiRegVal[3] = {0};
    _ub8 uiHCWPGrpSize = 0;
    _ub8 uiHCErsGrpSize = 0;
    _ub8 *puiBuf;

    /* input argument is not validated */

    puiBuf = &seq_tEXTCSDInfo[uiSlot].ucBuf[0];

    uiHCWPGrpSize = puiBuf[_EXTCSD_HCWPGRP_OFST];
    uiHCErsGrpSize = puiBuf[_EXTCSD_HCERSGRP_OFST];

    /* Get the values from the offsets */
    uiOffst = _EXTCSD_MAX_ENH_SIZE_0_OFST;
    uiRegVal[0] = puiBuf[uiOffst];
    uiOffst = _EXTCSD_MAX_ENH_SIZE_1_OFST;
    uiRegVal[1] = puiBuf[uiOffst];
    uiOffst = _EXTCSD_MAX_ENH_SIZE_2_OFST;
    uiRegVal[2] = puiBuf[uiOffst];

    /* With the help of the values calculate the max. enh. value */
    uiMaxEnhVal = ((uiRegVal[2] << 16)|(uiRegVal[1] << 8)|(uiRegVal[0]));
    /* the size is returned in terms of sector count */
    uiMaxEnhVal = (uiMaxEnhVal * uiHCWPGrpSize * uiHCErsGrpSize * _1024B);

    _PM_DBG_INFO("MaxEnhSize = %d\n",uiMaxEnhVal);

    return uiMaxEnhVal;
}

/**
 * @brief Sets the attributes of Enhanced User Data Area
 *
 * @param[in] uiSlot Host controller Slot no
 * @param[in] uiNumGpps No. of GPPS to be created
 * @param[in] pAttr Structure pointer pointing to GPP & EUDA Attr.
 *
 * @retval _DEV_STS_OK The function is successful
 * @retval _DEV_PARTITION_NOT_SUPPORTED Partitioning is not supported
 * @retval _DEV_STS_OK Partitioning is already done
 * @retval _DEV_PARTITION_SIZE_ERR GPP size is not WPG aligned
 * @retval _DEV_PARTITION_SIZE_EXCEEDED Device size exceeded
 * @retval _DEV_MAX_ENHANCED_SIZE_ERR Maximum enhance size exceeded
 * @retval _DEV_EUDAADDR_ALIGN_ERR EUDA Address is not aligned
 * @retval _DEV_ENH_ATTRIB_NOT_SUPPORTED Enhanced Attrib is not supported
 * @retval _DEV_EXT_ATTRIB_NOT_SUPPORTED Extended Attrib is not supported
 * @retval _DEV_SWITCH_ERR Switch command error
 */
dev_sts_e pm_createPartition(
    _ub32 uiSlot,
    _ub32 uiNumGpps,
    com_part_attr_t *pAttr)
{
    dev_sts_e eSts = _DEV_STS_OK;
    _ub32 uiMaxDevSize = 0;     /* Maximum capacity of the device */
    _ub32 uiMaxConfigSize = 0;  /* Maximum Size that needs to be configured */
    _ub32 uiMaxDevEnhSize = 0;  /* Max. Enhance Size allowed by the device */
    _ub32 uiMaxConfEnhSize = 0; /* Max. enhance size that needs to be set */
    _ub32 uiHCWPGSize = 0;       /* High Capacity Write protect Group Size */
    _ub32 uiloop = 0;            /* local variables for looping */
    _ub32 uiloop1 = 0;            /* local variables for looping */
    _ub32 uiVal = 0;             /* Holds the value to be set to EXTCSD reg.*/
    _ub32 uiOffst = 0;           /* To hold the offset of the EXTCSD reg */
    _ub32 uiSzOfst = 0;          /* Holds the offset of GPP size */
    _ub32 uiExtOfst = 0;         /* Holds the offset of Extended attribute */
    _ub32 uiEudaOfst = 0;        /* Holds the offset of EUDA start Address */
    _ub32 uiEnhBit = 0;
    /* Array to hold extended attributes */
    _ub32 uiExtAttr[4] = {0};
    /* Mask for EUDA Start Address */
    _ub32 uiEudaAdrMask[4]={0x000000FF,0x0000FF00,0x00FF0000,0xFF000000};
    _ub8 uiRegVal = 0;
    /* Array to hold the GPP size bytes and EUDA bytes */
    _ub8 uiSz[3] = {0};
    /* Array to hold the EUDA address bytes */
    _ub32 uiEudabytes[4] = {0};
    _ub32 uiDevSts = 0;
    extcsdinfo_t *pExtCSD;
    com_gpp_attr_t *pGppAttr = NULL;
    com_euda_attr_t *pEudaAttr = NULL;
    partitionflags_t *pPartFlags;

    /* input argument is not validated */

    pPartFlags = &pm_tPartFlags[uiSlot];

    /* Check the partition support in the device */
    eSts = checkPartitionSupport(uiSlot);
    if(_DEV_STS_OK != eSts)
    {
        _PM_DBG_ERR("checkPartitionSupport Failed : Error 0x%08x\n",eSts);
        return eSts;
    }

    /* Check if partition is already created */
    eSts = checkPartitionDone(uiSlot);
    if(_DEV_STS_OK != eSts)
    {
        _PM_DBG_ERR("checkPartitionDone Failed : Error 0x%08x\n",eSts);
        return eSts;
    }

    /* get the EUDA attribs. from the parameter */
    pEudaAttr = pAttr->pEattr;

    /* Get the device capacity in terms of sectors */
    uiMaxDevSize = seq_getSectCnt(uiSlot);
    /* uiMaxDevSize = (uiMaxDevSize * _BLK_SIZE); */

    /* get the max. enhance size(in terms of sectors) allowed in the device */
    uiMaxDevEnhSize = pm_getMaxEnhSize(uiSlot);

    /* get the high capacity write protect group size(in terms of sectors) */
    uiHCWPGSize = pm_getHCWPGrpSize(uiSlot);

    /* Pointer to the GPP Attr structure */
    pGppAttr = pAttr->pGattr;

    /* Only if GPP attr. is not NULL then proceed */
    if(NULL != pGppAttr)
    {
        for(uiloop = 0; uiloop < uiNumGpps ; uiloop++)
        {
            /* If GPP size is not WPG aligned return error */
            if(((pGppAttr[uiloop].uiPartSize) % uiHCWPGSize) != 0)
            {
                _PM_DBG_INFO("hcwpg size = %d\n",uiHCWPGSize);
                return _DEV_PARTITION_SIZE_ERR;
            }
            uiMaxConfigSize = uiMaxConfigSize +
                pGppAttr[uiloop].uiPartSize;
            if(_COM_PART_TYPE_ENHANCED ==
                pGppAttr[uiloop].eType)
            {
                uiMaxConfEnhSize = uiMaxConfEnhSize +
                    pGppAttr[uiloop].uiPartSize;
            }
        }
    }

    /* if EUDA attr. is not NULL calculate enh. size */
    if(NULL != pEudaAttr)
    {
        uiMaxConfigSize = uiMaxConfigSize + pEudaAttr->uiSize;
        uiMaxConfEnhSize = uiMaxConfEnhSize + pEudaAttr->uiSize;
        /* if EUDA start addr is not WPG aligned return error */
        if(((pEudaAttr->uiStartAddr) % (uiHCWPGSize << 9)) !=0)
        {
            return _DEV_EUDAADDR_ALIGN_ERR;
        }
        /* if euda size is not aligned return error */
        if(((pEudaAttr->uiSize) % uiHCWPGSize) != 0)
        {
            _PM_DBG_INFO("hcwpg size = %d\n",uiHCWPGSize);
            return _DEV_PARTITION_SIZE_ERR;
        }
    }

    /* If device config size is > than device capacity return error */
    if(uiMaxDevSize < uiMaxConfigSize)
    {
        return _DEV_PARTITION_SIZE_EXCEEDED;
    }

    /* if enhance config. size is > than that allowed by the device */
    if(uiMaxDevEnhSize < uiMaxConfEnhSize)
    {
        return _DEV_MAX_ENHANCED_SIZE_ERR;
    }

    /* Set Erase Group Def Bit */
    pExtCSD = &seq_tEXTCSDInfo[uiSlot];
    uiOffst = _EXTCSD_ERASE_GROUP_DEF_OFST;
    uiRegVal = pExtCSD->ucBuf[uiOffst];
    uiRegVal = (uiRegVal & (~(_ERASE_GRP_DEF_MASK)));
    uiRegVal |= 1;
    uiVal = (_ub32)uiRegVal;

    eSts = seq_writeExtCSD(uiSlot,uiOffst,uiVal);
    if(_DEV_STS_OK != eSts)
    {
        _PM_DBG_ERR("Set ERASE GROUP DEF Bit Failed");
        return eSts;
    }

    uiSzOfst = _EXTCSD_GP_SIZE_1_0_OFST;
    /* Set the attributes of GPP */
    if(NULL != pGppAttr)
    {
        for(uiloop = 0; uiloop < uiNumGpps ; uiloop++)
        {
            /* if Part. type is enhanced set the enhance bit in a variable */
            if(pGppAttr[uiloop].eType == _COM_PART_TYPE_ENHANCED)
            {
                if(pPartFlags->uiEnhAttrEn != 1)
                {
                    return _DEV_ENH_ATTRIB_NOT_SUPPORTED;
                }
                uiEnhBit |= 1 << (uiloop + 1);
            }

            /* if the partn. type is extended set the attributes to device */
            else if(pGppAttr[uiloop].eType == _COM_PART_TYPE_EXTENDED)
            {
                if(pPartFlags->uiExtAttrEn != 1)
                {
                    return _DEV_EXT_ATTRIB_NOT_SUPPORTED;
                }
                uiExtAttr[uiloop] = (_ub32)pGppAttr[uiloop].eExtType;
                /* if partn. number is 1 or 3, set it to higher nibble */
                if((1 == uiloop) || (3 == uiloop))
                {
                    uiExtAttr[uiloop] = uiExtAttr[uiloop] << 4;
                }
            }
            else
            {
                /* Partiiton type is Default : Do Nothing */
            }

            /* Calculate and set the size bytes for GPP in dev EXTCSD reg */
            eSts = calcGPPSizeBytes(uiSlot,pGppAttr[uiloop].uiPartSize,uiSz);
            if(_DEV_STS_OK != eSts)
            {
                _PM_DBG_ERR("calcGPPSizeBytes Failed");
                return eSts;
            }
            for(uiloop1 = 0 ; uiloop1 < _MAX_GPP_BYTES ; uiloop1++)
            {
                uiVal = (_ub32)uiSz[uiloop1];
                _PM_DBG_INFO("GPPSize = %d\n",uiVal);
                eSts = seq_writeExtCSD(uiSlot,uiSzOfst,uiVal);
                if(_DEV_STS_OK != eSts)
                {
                    _PM_DBG_ERR("seq_writeExtCSD Failed");
                    return eSts;
                }
                uiSzOfst++;
            }
        }

        /* writing the first offset of extended attr. for GPP 1 and 2 */
        uiExtOfst = _EXTCSD_EXT_PART_ATTR1_OFST;
        uiExtAttr[0] = (uiExtAttr[0] | uiExtAttr[1]);
        if(uiExtAttr[0] != 0)
        {
            eSts = seq_writeExtCSD(uiSlot,uiExtOfst,uiExtAttr[0]);
            if(_DEV_STS_OK != eSts)
            {
                _PM_DBG_ERR("seq_writeExtCSD Failed");
                return eSts;
            }
        }
        /* writing the second offset of extended attr. for GPP 3 and 4 */
        uiExtAttr[2] = (uiExtAttr[2] | uiExtAttr[3]);
        if(uiExtAttr[2] != 0)
        {
            uiExtOfst++;
            eSts = seq_writeExtCSD(uiSlot,uiExtOfst,uiExtAttr[2]);
            if(_DEV_STS_OK != eSts)
            {
                _PM_DBG_ERR("seq_writeExtCSD Failed");
                return eSts;
            }
        }
    }

    uiEudaOfst = _EXTCSD_ENH_START_ADR_0_OFST;

    /* Set the attributes of EUDA */
    if(NULL != pEudaAttr)
    {
        uiEnhBit = (uiEnhBit | 0x1);

        /* Set the address bytes for EUDA in device EXTCSD register */
        for(uiloop = 0; uiloop < _MAX_EUDA_ADR_BYTES ; uiloop++)
        {
            uiEudabytes[uiloop] =
                pEudaAttr->uiStartAddr & uiEudaAdrMask[uiloop];
            uiEudabytes[uiloop] = (uiEudabytes[uiloop] >> (uiloop << 3));
            _PM_DBG_INFO("EUDA addr bytes = %d\n",
                uiEudabytes[uiloop]);
            eSts = seq_writeExtCSD(uiSlot,uiEudaOfst,uiEudabytes[uiloop]);
            if(_DEV_STS_OK != eSts)
            {
                _PM_DBG_ERR("seq_writeExtCSD Failed");
                return eSts;
            }
            uiEudaOfst++;
        }

        /* Calculate the size bytes for EUDA */
        eSts = calcGPPSizeBytes(uiSlot,pEudaAttr->uiSize,uiSz);
        if(_DEV_STS_OK != eSts)
        {
            _PM_DBG_ERR("calcGPPSizeBytes Failed");
            return eSts;
        }

        uiSzOfst = _EXTCSD_ENH_SIZE_0_OFST;

        /* Set the size bytes for EUDA in device EXTCSD register */
        for(uiloop1 = 0 ; uiloop1 < _MAX_GPP_BYTES ; uiloop1++)
        {
            uiVal = (_ub32)uiSz[uiloop1];
            _PM_DBG_INFO("EUDASize = %d\n",uiVal);
            eSts = seq_writeExtCSD(uiSlot,uiSzOfst,uiVal);
            if(_DEV_STS_OK != eSts)
            {
                _PM_DBG_ERR("seq_writeExtCSD Failed");
                return eSts;
            }
            uiSzOfst++;
        }
    }

    /* Set the Enhanced Partition Attribute Bit */
    uiOffst = _EXTCSD_PART_ATTRIBUTE_OFST;
    _PM_DBG_INFO("EnhAttrib = %d\n",uiEnhBit);

    eSts = seq_writeExtCSD(uiSlot,uiOffst,uiEnhBit);
    if(_DEV_STS_OK != eSts)
    {
        _PM_DBG_ERR("seq_writeExtCSD Failed");
        return eSts;
    }

    /* Set partition completed bit in the device EXTCSD register */
    uiOffst = _EXTCSD_PART_COMPLETED_OFST;
    uiVal = 0x1;
    _PM_DBG_INFO("Partn. Comp. Bit = %d\n",uiVal);

    eSts = seq_writeExtCSD(uiSlot,uiOffst,uiVal);
    if(_DEV_STS_OK != eSts)
    {
        _PM_DBG_ERR("seq_writeExtCSD Failed");
        return eSts;
    }

    /* Send CMD13 to check the device status */
    eSts = seq_getDevSts(uiSlot,&uiDevSts);
    if(_DEV_STS_OK != eSts)
    {
        _PM_DBG_INFO("uiDevSts = 0x%08x\n",uiDevSts);
        _PM_DBG_ERR("seq_getDevSts Failed");
        return eSts;
    }

    return _DEV_STS_OK;
}

/**@}*/ // Seq_Functions

/**@}*//* Sequence */
/**@}*//* Device */

