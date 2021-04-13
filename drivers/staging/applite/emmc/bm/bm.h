/**
 * @file          bm.h
 *
 * \brief         Includes Buffer management API interfaces.
 *
 * \b COPYRIGHT : TOSHIBA Corporation Semiconductor and Storage Company
 *                2010-2015 All rights reserved.
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
 * @addtogroup BufferManagement
 * @{
 */

#ifndef _BM_H_
#define _BM_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*----------------------- Header Files Inclusions ---------------------------*/
#include "types.h"
#include "com.h"

/*-------------------------- Macro Definitions ------------------------------*/

/*-------------------------- Enum Definitions -------------------------------*/

/** @addtogroup BM_Enums BM_Enums
 * @{
 */

/**
 * @brief BM layer error codes enum
 */
typedef enum tag_bm_sts_e
{
    _BM_STS_OK     = 0x0000, /**< Success */
    _BM_INTR_ERR   = 0x0001, /**< err related to intr registration or handling */
    _BM_STS_NG     = 0x0002, /**< Failure */
}bm_sts_e;

/**@}*/ //end of BM_Enums

/*------------------ Data Structures & Custom Typedefs ----------------------*/

/*------------------------------ Externs ------------------------------------*/

/*---------------------------- Prototypes -----------------------------------*/

/** @addtogroup BM_Prototypes BM_Prototypes
 * @{
 */

bm_sts_e bm_init(void);

bm_sts_e bm_exit(void);

bm_sts_e bm_config(
    _ub32 uiSlot,
    _ub8 *pucBuf,
    _ub32 uiSize,
    com_RWDir_e direction);

bm_sts_e bm_deconfig(
    _ub32 uiSlot,
    _ub8 *pucBuf,
    _ub32 uiSize,
    com_RWDir_e direction);

/**@}*/ //end of BM_Prototypes

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _BM_H_ */

/**@}*//* BufferManagement */
