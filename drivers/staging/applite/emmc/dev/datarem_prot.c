/**
 * @file          datarem_prot.c
 *
 * \brief         Source file of data removal and data protection.
 *
 * \b COPYRIGHT : TOSHIBA Corporation Semiconductor and Storage Company
 * 2010-2015 All rights reserved
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

#define _512KB                524288               /* The value of 512kb */

/**
 * @brief Masks for Write Protection/Lock-Unlock
 */
#define _WP_PERM_PASWD_DIS_MASK  0x80  /* Password protection disable/enable */
#define _WP_PERM_DIS_MASK        0x40  /* WP Permanent Disable/enable */
#define _WP_US_PERM_DIS_MASK     0x10  /* Userarea permanent WP disabl/enable */
#define _WP_US_PWR_DIS_MASK      0x08  /* Userarea poweron WP disable/enable */
#define _WP_US_PERM_EN_MASK      0x04  /* Permanent/temporary WP for CMD28 */
#define _WP_US_PWR_EN_MASK       0x01  /* Power on write protection for CMD28 */

/**
 * @brief Masks for Sanitize
 */
#define _SANITIZE_SUPRT_MASK     0x40  /* Mask for sanitize support */

/**
 * @brief Retry count for Sanitize timeout checking - 1s
 */
#define _SANITIZE_TIMEOUT    10

#define _CSD_PERM_WRT_PROT (0x1 << 13)
#define _CSD_TEMP_WRT_PROT (0x1 << 12)

/**@}*/ // Seq_DEFINES

/*---------------------------- Prototypes -----------------------------------*/

/** @addtogroup Seq_Prototypes Seq_Prototypes
 * @{
 */

/* Function to execute all command sequences */
extern dev_sts_e executeSequence(_ub32 uiSlot, seq_id_e eSeqID);

/**@}*/ // Seq_Prototypes

/*---------------------------- function definitions --------------------------*/

/** @addtogroup Seq_Functions Seq_Functions
 * @{
 */

/**
 * @brief Performs Data Removal - Erase/Trim/Discard.
 *
 * @param[in] uiSlot slot number
 * @param[in] ePartNum - partition number
 * @param[in] uiStartSectr- Startaddr for which action is reqd [in sector unit]
 * @param[in] uiEndSectr- Endaddr for which action is reqd [in sector unit]
 * @param[in] eRemType- rem_type choose from discard/erase/trim/sanitize
 *
 * @retval _DEV_PARTITION_NOT_CREATED Invalid argument sent
 * @retval _DEV_INPUT_ERR Slot is invalid
 * @retval _DEV_CMDSEND_ERR command send error
 * @retval _DEV_TIMEOUT_ERR timeout error
 * @retval _DEV_STS_OK The function is successful
 */
dev_sts_e dev_remData(
    _ub32 uiSlot,
    com_part_num_e ePartNum,
    _ub32 uiStartSectr,
    _ub32 uiEndSectr,
    com_rem_type_e eRemType)
{
    cmd_frm_t *pCmdSeq;
    dev_sts_e eSts = _DEV_STS_OK;

    _ub32 uiMaxDevSize = 0;
    _ub32 uiAlign = 0;
    _ub32 uiErsGrpSize;

    extcsdinfo_t *pExtCSD;
    com_csd_params_t *pCSDParams =  &seq_tCSDParams[uiSlot];

    /* Input arguments is not validated as it is done by caller */

    pExtCSD = &seq_tEXTCSDInfo[uiSlot];

    if(eRemType == _COM_SANITIZE)
    {
        _SEQ_DBG_ERR("In-Correct Data Removal Type");
        return _DEV_INPUT_ERR;
    }

    /*
     * For Sanitize addresses not required
     * for ERASE,DISCARD,TRIM start and end addr required
     */

    /** GPP area **/
    if((ePartNum > _COM_PARTITION_UDA) && (ePartNum < _COM_PARTITION_MAX))
    {
        com_gpp_attr_t gpp_part;

        eSts = pm_getGPPAttributes(uiSlot, ePartNum, &gpp_part);
        if(_DEV_STS_OK != eSts)
        {
            return eSts;
        }

        /* Get the partition size in sector units */
        uiMaxDevSize = gpp_part.uiPartSize;
    }
    else
    {
       /*
        * User Defined area:
        * getting the device capacity in sector count
        */
        uiMaxDevSize = seq_getSectCnt(uiSlot);
    }

   /*
    * Checking if address is beyond partition capacity - device also checks
    * this and reports error
    */
    if((uiEndSectr- uiStartSectr) > uiMaxDevSize)
    {
        _SEQ_DBG_ERR("addresses beyond partition capacity");
        return _DEV_INPUT_ERR;
    }

   /* The below if-else is for debug purpose. */
   /*
    * For erase - erase blk size is multiples of erase_unit_size
    * For discard,trim - erase blk size is multiples of write_blk_size
    */
    if(_COM_ERASE == eRemType)
    {
        /* Get the erase group size (in term of sectors) */
        uiErsGrpSize = seq_getErsGrpSize(uiSlot);

        uiAlign = uiErsGrpSize ;
        _SEQ_DBG_INFO("Erase align size = %x \n",uiAlign);

    }
    else
    {
        /*
         * Minimum blk size is Write Blk length for Trim and Discard CMDs
         * Read from CSD register
         */
        uiAlign = (1 << pCSDParams->ucWrBlkLen);
        _SEQ_DBG_INFO("non-erase align size = %x \n",uiAlign);
    }

    {
        _ub32 uiMemCont = pExtCSD->ucBuf[_EXTCSD_ERASE_MEM_CONT_OFST];
        _SEQ_DBG_INFO("on Erase mem content = %x \n",uiMemCont);
    }

   /*
    * Forming the command set/arguments
    * Execute the Erase sequence
    * Issue CMD35 start_addr;
    * Issue CMD36 end_addr;
    * Issue CMD38 type;
    */
    pCmdSeq = seq_tCmdSeqTbl[_SEQ_ID_ERASE];
    pCmdSeq[0].uiArg = uiStartSectr; /* CMD35 argument */
    pCmdSeq[1].uiArg = uiEndSectr;   /* CMD36 argument */
    /* rem_type [0 - erase,1- trim,3- discard] */
    pCmdSeq[2].uiArg = eRemType; /* CMD38 argument */

    /* Call the ERASE sequence */
    eSts = executeSequence(uiSlot, _SEQ_ID_ERASE);
    if(_DEV_STS_OK != eSts)
    {
        _SEQ_DBG_ERR("Erase Sequence failed");
    }

    return eSts;
}

/**
 * @brief Performs Data Removal - Sanitize
 *
 * @param[in] uiSlot slot number
 *
 * @retval _DEV_SANITIZE_UNSUPPORTED error
 * @retval _DEV_TIMEOUT_ERR timeout error
 * @retval _DEV_SWITCH_ERR Device switch error occured
 * @retval _DEV_STS_OK The function is successful
 */
dev_sts_e dev_sanitize(_ub32 uiSlot)
{
    dev_sts_e eSts = _DEV_STS_OK;
    _ub8 ucRetry = 0;
    extcsdinfo_t *pExtCSD;

    _ub32 uiSantzSup;

    /* Input arguments is not validated as it is done by caller */

    pExtCSD = &seq_tEXTCSDInfo[uiSlot];

   /*
    * For Sanitize addresses not required
    * for ERASE,DISCARD,TRIM start and end addr required
    */

    /* Checking if sanitize operation is supported by device */
    uiSantzSup = pExtCSD->ucBuf[_EXTCSD_SEC_FEAT_SUPPORT_OFST];
    uiSantzSup &= _SANITIZE_SUPRT_MASK;

    if(!uiSantzSup)
    {
        _SEQ_DBG_ERR("Sanitize un-supported");
        return _DEV_SANITIZE_UNSUPPORTED;
    }

    /* TBD: how to test sanitize */
    /* Start sanitize operation: Write to EXT_CSD[165] SANITIZE_START = 1 */
    eSts = seq_writeExtCSD(uiSlot,_EXTCSD_SANITIZE_START_OFST,1);
    if(_DEV_STS_OK != eSts)
    {
        _SEQ_DBG_ERR("Sanitize operation seq_writeExtCSD failed ");
        return eSts;
    }

    /*
     * Once sanitize is issued we need to check if sanitize is complete.
     * This is done by checking if device is busy
     *
     * Check DAT line inhibit status - 1s
     * cmd_checkInhibitSts retries for 100ms
     */
    while(_LINE_BUSY == cmd_checkInhibitSts(uiSlot, _DAT_LINE))
    {
        if(ucRetry > _SANITIZE_TIMEOUT)
        {
            eSts = _DEV_TIMEOUT_ERR;
            _SEQ_DBG_ERR("Sanitize timeout \n");
            break;
        }

        ucRetry++;
        _SEQ_DBG_ERR("DAT line busy\n");
    }

    return eSts;
}

/**
 * @brief Set Write protect device/segments.
 *
 * @param[in] uiSlot slot number
 * @param[in] ePartNum - partition number
 * @param[in] uiDevSeg - protect device/segments
 * @param[in] uiProtType - type of protection
 * @param[in] uiSectr - start sector
 * @param[in] piobuf - buffer for sending CSD data
 *
 * @retval _DEV_PARTITION_NOT_CREATED Invalid argument sent
 * @retval _DEV_INPUT_ERR Slot is invalid
 * @retval _DEV_CMDSEND_ERR command send error
 * @retval _DEV_TIMEOUT_ERR timeout error
 * @retval _DEV_STS_OK The function is successful
 */
dev_sts_e dev_setWriteProt(
    _ub32 uiSlot,
    com_part_num_e ePartNum,
    com_wp_e uiDevSeg,
    com_wp_type_e uiProtType,
    _ub32 uiSectr,
    _ub8 *piobuf)
{
    cmd_frm_t *pCmdSeq;
    dev_sts_e eSts = _DEV_STS_OK;
    extcsdinfo_t *pExtCSD;
    _ub32 uiUserWP;
    com_csd_params_t *pCSDParams;
    _ub32 uiVal;

    /* Input arguments is not validated as it is done by caller */

    pCSDParams =  &seq_tCSDParams[uiSlot];
    pExtCSD = &seq_tEXTCSDInfo[uiSlot];

    /* Read the user area WP enable/disable details */
    uiUserWP = pExtCSD->ucBuf[_EXTCSD_USER_WP_OFST];

    /* Device Protection */
    if(_COM_DEV == uiDevSeg)
    {
        /* Check for protection type as power-on */
        if(_COM_PWR == uiProtType)
        {
            _SEQ_DBG_ERR("Power-on WP for entire Device is not allowed");
            return _DEV_INPUT_ERR;
        }

        /* Check for protection type as permanent */
        if(_COM_PERM == uiProtType)
        {
            /*
             * Device Permanent Write Protection - OTP !!
             * checking if write potection is alowed
             */
            _ub32 uiPermWP = uiUserWP & _WP_PERM_DIS_MASK;
            if(!uiPermWP)
            {
                seq_writeCSD(uiSlot,_CSD_PERM_WRT_PROT,_COM_SET,piobuf);
            }
            else
            {
                _SEQ_DBG_ERR("Write Protection of Device Disabled");
                return _DEV_INPUT_ERR;
            }
        }
        else
        {
            /* Device Temporary Write Protection */
            seq_writeCSD(uiSlot,_CSD_TEMP_WRT_PROT,_COM_SET,piobuf);
        }
    }

    /* Segment Protection */
    if(_COM_SEG == uiDevSeg)
    {
        _ub32 uiMaxDevSize = 0;
        _ub32 uiPermWP;

        /* Calculating Partition size GPP area */
        if(!pCSDParams->ucWPEnable)
        {
            _SEQ_DBG_ERR("Write protect of groups not allowed");
        }

        if((ePartNum > _COM_PARTITION_UDA) &&
           (ePartNum < _COM_PARTITION_MAX))
        {
            com_gpp_attr_t tGppPart;

            eSts = pm_getGPPAttributes(uiSlot, ePartNum, &tGppPart);
            if(_DEV_STS_OK != eSts)
            {
                return eSts;
            }

            uiMaxDevSize = tGppPart.uiPartSize;
        }
        else
        {
            /*
             * User Defined area
             * getting the device capacity: sector count
             */
            uiMaxDevSize = seq_getSectCnt(uiSlot);
        }

        /* Calculating the min write protect Erase group size */
        {
            _ub32 uiWpSize;
            _ub32 uiSectAddr = uiSectr;

            /* Get the write protect group size (in term of sectors) */
            uiWpSize = seq_getWPGrpSize(uiSlot);

            /* checking if address is beyond partition capacity */
            if((uiSectAddr + uiWpSize) > uiMaxDevSize)
            {
                _SEQ_DBG_ERR("setting WP beyond partition capacity");
                return _DEV_INPUT_ERR;
            }
        }

        uiVal = uiUserWP;

        /* Power on Protection */
        if(_COM_PWR== uiProtType)
        {
            uiPermWP = uiUserWP & _WP_US_PWR_DIS_MASK;
            if(!uiPermWP)
            {
                uiVal |= _WP_US_PWR_EN_MASK;
            }
            else
            {
                _SEQ_DBG_ERR("PWR ON Write Protection of Segment Disabled");
                return _DEV_INPUT_ERR;
            }
        }

        /* Permanent Protection - OTP */
        if(_COM_PERM == uiProtType)
        {
            uiPermWP = uiUserWP & _WP_US_PERM_DIS_MASK;
            if(!uiPermWP)
            {
                uiVal |= _WP_US_PERM_EN_MASK;
            }
            else
            {
                _SEQ_DBG_ERR("Permanent Write Protection of Segment Disabled");
                return _DEV_INPUT_ERR;
            }
        }

        /* Temporary Protection */
        if(_COM_TEMP == uiProtType)
        {
            uiVal &=  ~(_WP_US_PERM_EN_MASK | _WP_US_PWR_EN_MASK);
        }

        /* Write to Extended CSD */
        eSts = seq_writeExtCSD(uiSlot,_EXTCSD_USER_WP_OFST,uiVal);
        if(_DEV_STS_OK != eSts)
        {
            _SEQ_DBG_ERR("Write ExtCSD failed");
        }

        pCmdSeq = seq_tCmdSeqTbl[_SEQ_ID_SETWP];
        pCmdSeq[0].uiArg = uiSectr; /* CMD28 argument */

        /* Sending CMD28 */
        eSts = executeSequence(uiSlot, _SEQ_ID_SETWP);
        if(_DEV_STS_OK != eSts)
        {
            _SEQ_DBG_ERR("Set Write Protect failed");
        }
    }

    return eSts;
}

/**
 * @brief Clear Write protect device/segments.
 *
 * @param[in] uiSlot slot number
 * @param[in] ePartNum - partition number
 * @param[in] uiDevSeg - protect device/segments
 * @param[in] uiProtType - type of protection
 * @param[in] uiSectr - start sector
 * @param[in] piobuf - buffer for sending CSD data
 *
 * @retval _DEV_PARTITION_NOT_CREATED Invalid argument sent
 * @retval _DEV_INPUT_ERR Slot is invalid
 * @retval _DEV_CMDSEND_ERR command send error
 * @retval _DEV_TIMEOUT_ERR timeout error
 * @retval _DEV_STS_OK The function is successful
 */
dev_sts_e dev_clrWriteProt(
    _ub32 uiSlot,
    com_part_num_e ePartNum,
    com_wp_e uiDevSeg,
    com_wp_type_e uiProtType,
    _ub32 uiSectr,
    _ub8 *piobuf)
{
    cmd_frm_t *pCmdSeq;
    dev_sts_e eSts = _DEV_STS_OK;
    extcsdinfo_t *pExtCSD;

    /* Input arguments is not validated as it is done by caller */

    pExtCSD = &seq_tEXTCSDInfo[uiSlot];

    /* Clear Write Protect of Device */
    if(_COM_DEV == uiDevSeg)
    {
        /* Check for protection type as power-on */
        if(_COM_PWR == uiProtType)
        {
            _SEQ_DBG_ERR("Clearing Poweron WP for entire Device not allowed");
            return _DEV_INPUT_ERR;
        }

        /* Check for protection type as permanent */
        if(_COM_PERM == uiProtType)
        {
            /*
             * This is Not possible as Setting Permanent WP of device is OTP
             * Hence Clearing Permanent WP is not Possible
             */
            seq_writeCSD(uiSlot,_CSD_PERM_WRT_PROT,_COM_CLR,piobuf);
        }
        else
        {
            /* Clearing Temporary Device WP */
            seq_writeCSD(uiSlot,_CSD_TEMP_WRT_PROT,_COM_CLR,piobuf);
        }
    }

    if(_COM_SEG == uiDevSeg)
    {
        _ub32 uiMaxDevSize = 0;

        /*
         * TBD - the portion of code calculating the Erase group size and
         * WP erase size can be made into a fucntion
         */
        if((ePartNum > _COM_PARTITION_UDA) && (ePartNum < _COM_PARTITION_MAX))
        {
            com_gpp_attr_t tGppPart;
            eSts = pm_getGPPAttributes(uiSlot, ePartNum, &tGppPart);
            if(_DEV_STS_OK != eSts)
            {
                return eSts;
            }
            uiMaxDevSize = tGppPart.uiPartSize;
        }
        else
        {
            /*
             * User Defined area
             * getting the device capacity: sector count * 512Bytes
             */
            uiMaxDevSize = seq_getSectCnt(uiSlot);
        }

        /* Calculating the min write protect group size */
        {
            _ub32 uiWpSize;
            _ub32 uiSectAddr = uiSectr;

            /* Get the write protect group size (in term of sectors) */
            uiWpSize = seq_getWPGrpSize(uiSlot);

            /* checking if address is beyond partition capacity */
            if((uiSectAddr + uiWpSize) > uiMaxDevSize)
            {
                _SEQ_DBG_ERR("clearing WP beyond partition capacity");
                return _DEV_INPUT_ERR;
            }
        }

        /*
         * TBD - Clear WP works only on Temporary WP regions
         * we might have to read the seg attributes and report error if
         * Permanent WP region is being accessed
         */
        pCmdSeq = seq_tCmdSeqTbl[_SEQ_ID_CLRWP];
        pCmdSeq[0].uiArg = uiSectr; /** CMD29 argument **/

        /* sending CMD29 - clear WP command */
        eSts = executeSequence(uiSlot, _SEQ_ID_CLRWP);
        if(_DEV_STS_OK != eSts)
        {
            _SEQ_DBG_ERR("Clear Write Protect failed");
        }
    }

    return eSts;
}

/**
 * @brief get Write Protect status and Type of Write Protection for segments
 *
 * @param[in] uiSlot - Host controller Slot no
 * @param[in] eWpStat - send either CMD30 or CMD31
 * @param[in] uiSect - sector for which Status is required
 *
 * @retval _DEV_STS_OK Sequence executed successfully
 * @retval _DEV_INPUT_ERR Input param error
 * @retval _DEV_CMDBUSY_ERR CMD sending failed as CMD/DAT line was busy
 * @retval _DEV_CMDSEND_ERR CMD sending failed: timeout/index/crc/endbit error
 * @retval _DEV_DEV_ILLEGAL_CMD_ERR Illegal command issued
 * @retval _DEV_DEV_CC_ERR Device undefined Error
 * @retval _DEV_DEV_ERR Device error related to last host cmd
 * @retval _DEV_DEV_SWITCH_ERR Switch command failed
 */
dev_sts_e dev_getWPStat(
    _ub32 uiSlot,
    com_wpstat_e eWpStat,
    _ub32 uiSect)
{
    dev_sts_e eSts = _DEV_STS_OK;
    cmd_frm_t *pCmdSeq;
    seq_id_e eSeqID;

    _SEQ_DBG_INFO("ENTRY");

    /* Input arguments is not validated as it is done by caller */

    eSeqID = (_COM_GET_WP_STATUS ==eWpStat)? \
        _SEQ_ID_GET_WP_STAT : _SEQ_ID_GET_WP_TYP;

    /* Retrieve the Switch sequence from the sequence table */
    pCmdSeq = seq_tCmdSeqTbl[eSeqID];

    /* Execute the switch sequence */
    eSts = executeSequence(uiSlot, eSeqID);

    _SEQ_DBG_INFO("EXIT");

    return eSts;
}

/**
 * @brief function to Lock/Unlock device,set/clr PWD ,force erase
 *
 * @param[in] uiSlot - Host controller Slot no
 * @param[in] uiSize - size of password
 *
 * @retval _DEV_STS_OK Sequence executed successfully
 * @retval _DEV_INPUT_ERR Input param error
 * @retval _DEV_CMDBUSY_ERR CMD sending failed as CMD/DAT line was busy
 * @retval _DEV_CMDSEND_ERR CMD sending failed: timeout/index/crc/endbit error
 * @retval _DEV_DEV_ILLEGAL_CMD_ERR Illegal command issued
 * @retval _DEV_DEV_CC_ERR Device undefined Error
 * @retval _DEV_DEV_ERR Device error related to last host cmd
 * @retval _DEV_DEV_SWITCH_ERR Switch command failed
 */
dev_sts_e dev_devLkUnlk(
    _ub32 uiSlot,
    _ub32 uiSize)
{
    dev_sts_e eSts = _DEV_STS_OK;
    cmd_frm_t *pCmdSeq;
    _ub32 uiUserWP = seq_tEXTCSDInfo[uiSlot].ucBuf[_EXTCSD_USER_WP_OFST];
    _ub32 uiPermWP = uiUserWP & _WP_PERM_PASWD_DIS_MASK;

    _SEQ_DBG_INFO("ENTRY");

    /* Input arguments is not validated as it is done by caller */

    _SEQ_DBG_INFO("passwd enable/diable %x \n",uiPermWP);

   /* Checking if Password setting is allowed */
    if(uiPermWP){
        _SEQ_DBG_ERR("passwd setting Disabled \n");
    return _DEV_INPUT_ERR;
    }

    pCmdSeq = seq_tCmdSeqTbl[_SEQ_ID_LKUNLK];
    pCmdSeq[0].uiArg = uiSize;

    /* Execute the CMD42 */
    eSts = executeSequence(uiSlot, _SEQ_ID_LKUNLK);

    _SEQ_DBG_INFO("EXIT");

    return eSts;
}

/**@}*/ // Seq_Functions

/**@}*//* Sequence */
/**@}*//* Device */

