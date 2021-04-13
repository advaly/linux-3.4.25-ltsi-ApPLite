/**
 * @file          debug.h
 *
 * \brief         This file includes interfaces and macros of debug support.
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
 * \b Date      : 28-Jun-2013
 */

/**
 * @addtogroup Debug
 * @{
 */

#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @addtogroup Debug_DEFINES Debug_DEFINES
 * @{
 */

/*----------------------- Header Files Inclusions ---------------------------*/

/*-------------------------- Macro Definitions ------------------------------*/


#define _DZ_CRTICAL    0x00000001 /* Bit0: [General] Critical Message */
#define _DZ_WARN       0x00000002 /* Bit1: [General] Warning Message */
#define _DZ_INFO       0x00000004 /* Bit2: [General] Information */
#define _DZ_INTR       0x00000008 /* Bit3: [Specific] Interrupt */
#define _DZ_CMD        0x00000010 /* Bit4: [Specific] Command API */
#define _DZ_DEV        0x00000020 /* Bit5: [Specific] Command Sequence */
#define _DZ_API        0x00000040 /* Bit6: [Specific] Top APIs */
#define _DZ_BUF        0x00000080 /* Bit7: [Specific] Buffer Management */
#define _DZ_HC         0x00000100 /* Bit8: [Specific] Host Controller */
#define _DZ_RSVD       0x00000200 /* Bit9: [?] Reserved */
/* Here, only 10bits (from LSB) are used, other are reserved for future use. */

/**
 * @brief Helper macros: Debug Levels
 *
 * These macros can be used while setting the enable bits of a group of zone
 * using debug_setZone() function.
 *
 * Additional customized debug level can be defined, where multiple zones
 * are grouped on need purpose.
 */
#define _DZ_LEVEL1     0x00000001 /* Critical messages only */
#define _DZ_LEVEL2     0x00000003 /* Critical & Warning messages */
#define _DZ_LEVEL3     0x00000007 /* All general messages */
#define _DZ_LEVEL_ALL  0xFFFFFFFF /* All type of messages */

/**@}*/ // Debug_DEFINES

/*-------------------------- Enum Definitions -------------------------------*/

/*------------------ Data Structures & Custom Typedefs ----------------------*/

/*------------------------------ Externs ------------------------------------*/

/*---------------------------- Prototypes -----------------------------------*/

/** @addtogroup Debug_Prototypes Debug_Prototypes
 * @{
 */

unsigned long debug_getZone(void);
void debug_setZone(unsigned long zone);

/**@}*/ // Debug_Prototypes

/** @addtogroup Debug_DEFINES Debug_DEFINES
 * @{
 */

/* This macro is moved down due to API dependency! */
#ifdef __DEBUG
#define dz_print(zone, args...)                   \
    do                                            \
    {                                             \
        if(debug_getZone() & (unsigned long)zone) \
        {                                         \
            printk(args); /* Linux API! */        \
        }                                         \
    }while(0)
#else /* !__DEBUG */
#define dz_print(zone, ...) /* resolves to nothing! */
#endif /* __DEBUG */

/**@}*/ // Debug_DEFINES

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DEBUG_H_ */

/**@}*//* Debug */

