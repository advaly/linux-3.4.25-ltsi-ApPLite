/**
 * @file          config.h
 *
 * \brief         This file contains vendor specific config of HC and device
 *
 * \b COPYRIGHT : TOSHIBA Corporation Semiconductor and Storage Company
 *                2010-2015 All rights reserved
 *
 * \b Project   : Glenfiddich
 *
 * \b Version   : 0.1
 *
 * \b Release   : None
 *
 * \b Date      : 28-Mar-2013
 */

/**
 * @addtogroup Common
 * @{
 */

/**
 * @addtogroup VendorConfig
 * @{
 */

#ifndef _CONFIG_H_
#define _CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*----------------------- Header Files Inclusions ---------------------------*/

/*-------------------------- Macro Definitions ------------------------------*/

/** @addtogroup VendorConfig_DEFINES VendorConfig_DEFINES
 * @{
 */

#define _BLK_SIZE  512        /* size fixed to 512 as of now */
#define _MAX_SLOTS 1          /* MAX_SLOTS = 8 in actual */

/**
 * Below macros can be used for verifying the supported version obtained
 * from HC and device
 */
#define _CARD_VERSION 0x0100   /* eMMC device version, JEDEC spec, sec 7.3.2 */
/*
 * Ex; CARD_VERSION
 * 0 - Allocated by MMCA
 * 1 - Allocated by MMCA
 * 2 - Allocated by MMCA
 * 3 - Allocated by MMCA
 * 4 - Version 4.1.2.3
 * 55 - Reserved
 *
 * Actual value read from register will be 0x0100 --> 4 (Version 4.1.2.3)
 */

#define _HOST_VERSION 0x0002   /* HC version - ref: SD spec 3.0, sec 2.2.34 */
/*
 * Ex: HOST_VERSION
 * 00h - SD Host Specification Version 1.00
 * 01h - SD Host Specification Version 2.00
 * 02h - SD Host Specification Version 3.00
 */

/**@}*/ //end of VendorConfig_DEFINES

/*-------------------------- Enum Definitions -------------------------------*/

/*------------------ Data Structures & Custom Typedefs ----------------------*/

/*------------------------------ Externs ------------------------------------*/

/*---------------------------- Prototypes -----------------------------------*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CONFIG_H_ */

/**@}*//* VendorConfig */
/**@}*//* Common */

