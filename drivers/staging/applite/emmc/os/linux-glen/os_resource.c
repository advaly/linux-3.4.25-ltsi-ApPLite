/**
 * @file          os_resource.c
 *
 * \brief         Source file of OS Abstraction Layer functions.
 *
 * \b COPYRIGHT : TOSHIBA Corporation Semiconductor and Storage Company
 *                2010-2015 All rights reserved
 *
 * \b Project   : Glenfiddich
 *
 * \b Version   : 0.3
 *
 * \b Release   : None
 *
 * \b Date      : 28-Jun-2013
 */

/**
 * @addtogroup PlatformLayer
 * @{
 */

/**
 * @addtogroup PlatformResourcesandServices
 * @{
 */

/*------------------------ Header Files Inclusions ---------------------------*/
#include "debug.h"      /* To use debug zone prints */
#include "os.h"         /* To use OS service APIs */

/*-------------------------- Macro Definitions -------------------------------*/

/** @addtogroup PF_DEFINES PF_DEFINES
 * @{
 */

#define HC_BASE_ADDR    0x0A280000 /* Physical address from memory map */
#define HC_MMIO_SIZE    256
#define HC_IRQ_NUM      174
#define RESOURCE_NAME   "internal_emmc"

/**@}*/ // PF_DEFINES

/*--------------------------- Enum Definitions -------------------------------*/

/*------------------- Data Structures & Custom Typedefs ----------------------*/

/*-------------------------------- Externs -----------------------------------*/

/*------------------------------- Prototypes ---------------------------------*/

/*---------------- Data variable/Structure allocation (global) ---------------*/

/** @addtogroup PF_Globals PF_Globals
 * @{
 */

/* HC register base address */
static _addr pHcRegBase = NULL;

/**@}*/ // PF_Globals

#ifdef __PERFORMANCE_MEASUREMENT

/** @defgroup PF_Structures PF_Structures
 * @{
 */

/* Performance structure for size and Time */
typedef struct tag_os_performance_t{
    unsigned long ticksCount; /**< Linux jiffies to maintain start and end */
    unsigned long sizeDone;   /**< Accumulated size for the second */
    unsigned long timeTaken;  /**<
                               * Accumulated jiffies count taken per second
                               * This is equallent to millisecond per data
                               * transaction
                               */
}os_performance_t;

/**@}*/ // PF_Structures

/** @addtogroup PF_Globals PF_Globals
 * @{
 */

/* 0: Write Performance 1: Read Performance */
static os_performance_t emmc_perf[2];

/**@}*/ // PF_Globals

#endif /* __PERFORMANCE_MEASUREMENT */

/*-------------------------- Function Definitions ----------------------------*/

/*----------------------------------------------------------------------------*/

/** @addtogroup PF_Functions PF_Functions
 * @{
 */

/**
 * @brief Resource (host controller base and irq) allocation
 *
 * @param[in] pArg The pointer to OS resource handle.
 *
 * @retval _OS_OK creation of lock successful.
 * @retval _OS_ERR_PARAM Error in input argument.
 * @retval _OS_ERR_RESOURCE Error in resource access.
 * @retval _OS_ERR_MAP Error in translating address.
 */
_ub32 os_obtainResource(os_resource_t *pArg)
{
    /* Verify input argument */
    if(NULL == pArg)
    {
        return _OS_ERR_PARAM;
    }

    /* Reserve and translate MMIO address from physical to virtual */
    if(NULL == request_mem_region(HC_BASE_ADDR, HC_MMIO_SIZE, RESOURCE_NAME))
    {
        _OS_DBG_ERR("Error: request_mem_region\n");
        return _OS_ERR_RESOURCE;
    }

    pHcRegBase = (_addr __user __force)ioremap_nocache(HC_BASE_ADDR, \
            HC_MMIO_SIZE);
    if(NULL == pHcRegBase)
    {
        _OS_DBG_ERR("Error: ioremap_nocache\n");
        /* unreserve MMIO address space */
        release_mem_region(HC_BASE_ADDR, HC_MMIO_SIZE);
        return _OS_ERR_MAP;
    }

    /* Update the resources in input structures */
    pArg->uiIrq = HC_IRQ_NUM;
    pArg->uiBase = pHcRegBase;

    return _OS_OK;
}

/**
 * @brief Resource (host controller base and irq) de-allocation
 *
 * @param[in] pArg The pointer to OS resource handle.
 *
 * @retval None
 */
void os_releaseResource(os_resource_t *pArg)
{
    /* free MMIO address space translation */
    iounmap((void __iomem *)pHcRegBase);

    /* unreserve MMIO address space */
    release_mem_region(HC_BASE_ADDR, HC_MMIO_SIZE);
}

#ifdef __PERFORMANCE_MEASUREMENT
/**
 * @brief Capture current tick before operation starts
 *
 * @param[in] Direction for the transaction
 *
 * @retval None
 */
void os_perf_start(int iDir)
{
    if(iDir >= 2)
    {
        /* Error */
        printk("Never Happens in Perf Start\n");
        return;
    }

    /* 1: Read 0:Write */
    emmc_perf[iDir].ticksCount = CUR_TIME;
    return;
}

/**
 * @brief Calculate processing time between start and stop ticks
 *
 * @param[in] Direction for the transaction
 * @param[in] size used for the transaction
 *
 * @retval None
 */
void os_perf_stop(int iDir, unsigned long uiSize)
{
    unsigned long temp = CUR_TIME;

    if(iDir >= 2)
    {
        /* Error */
        printk("Never Happens in Perf Stop\n");
        return;
    }

    if(temp >= emmc_perf[iDir].ticksCount)
    {
        emmc_perf[iDir].timeTaken += (temp - emmc_perf[iDir].ticksCount);

        emmc_perf[iDir].sizeDone += uiSize;

        /*
         * To avoid frequent print for the data transaction speed,
         * printing the datarate is done for every second
         */
        if((emmc_perf[iDir].timeTaken / HZ)  != 0)
        {
            printk("Trans %ld Bps\n",
                ((emmc_perf[iDir].sizeDone / emmc_perf[iDir].timeTaken) * HZ));

            /* Reset accumulated time(ms) and size(Bytes) */
            emmc_perf[iDir].timeTaken = 0;
            emmc_perf[iDir].sizeDone  = 0;
            emmc_perf[iDir].ticksCount = 0xFFFFFFFF;
        }
    }
    else
    {
        /* if time differ is zero consider as error */
        printk("Timing Error Ticks wraparound\n");
    }
    return;
}
#endif /* __PERFORMANCE_MEASUREMENT */

/**@}*/ // PF_Functions

/**@}*//* PlatformResourcesandServices */
/**@}*//* PlatformLayer */

