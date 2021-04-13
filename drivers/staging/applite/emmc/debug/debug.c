/**
 * @file         debug.c
 *
 * \brief        This file has interfaces' implementation of debug support.
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
 * @addtogroup Debug
 * @{
 */

/*----------------------- Header Files Inclusions ---------------------------*/
#include "debug.h"

/*-------------------------- Macro Definitions ------------------------------*/

/*-------------------------- Enum Definitions -------------------------------*/

/*------------------ Data Structures & Custom Typedefs ----------------------*/

/*------------------------------ Externs ------------------------------------*/

/*---------------------------- Prototypes -----------------------------------*/

/*------------- Data variable/Structure allocation (global) -----------------*/

/** @addtogroup Debug_Globals Debug_Globals
 * @{
 */

/* This static global is 32-bit and its each bit represents one zone */
static unsigned long debug_zone = 0x00000001;

/**@}*/ // Debug_Globals

/*----------------------- Function Definitions ------------------------------*/

/** @addtogroup Debug_Functions Debug_Functions
 * @{
 */

/**
 * @brief API to get debug zone information.
 *
 * @param[in] None
 *
 * @retval debug zone information.
 */
unsigned long debug_getZone(void)
{
    return debug_zone;
}

/**
 * @brief API to enable specific debug zone(s).
 *
 * @param[in] Zone: zone(s) to enable
 *
 * @retval None
 *
 * Recommendation: it is better to get the zone information before calling
 * this API at runtime.
 */
void debug_setZone(unsigned long zone)
{
    debug_zone = zone; /* intentionally no ORing done. */
}

/**@}*/ // Debug_Functions

/**@}*//* Debug */

