/**
 * @file          types.h
 *
 * \brief         This file includes common data type typedefs.
 *
 * \b COPYRIGHT : TOSHIBA Corporation Semiconductor and Storage Company
 * 2010-2015 All rights reserved
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
 * @addtogroup DataTypes
 * @{
 */

#ifndef _TYPES_H_
#define _TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*----------------------- Header Files Inclusions ---------------------------*/

/*-------------------------- Macro Definitions ------------------------------*/

/*-------------------------- Enum Definitions -------------------------------*/

/*------------------ Data Structures & Custom Typedefs ----------------------*/
#ifdef __USE_OS_TYPES
typedef s8 _b8;
typedef u8 _ub8;
typedef s16 _b16;
typedef u16 _ub16;
typedef s32 _b32;
typedef u32 _ub32;
typedef s64 _b64;
typedef u64 _ub64;
#else /* !__USE_OS_TYPES */
typedef signed char _b8;
typedef unsigned char _ub8;
typedef signed short _b16;
typedef unsigned short _ub16;
typedef signed int _b32;
typedef unsigned int _ub32;
typedef signed long long _b64;
typedef unsigned long long _ub64;
typedef volatile void *_addr;
#endif /* __USE_OS_TYPES */

/*------------------------------ Externs ------------------------------------*/

/*---------------------------- Prototypes -----------------------------------*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TYPES_H_ */

/**@}*//* DataTypes */
/**@}*//* Common */

