/**
 * @file          os_resource.c
 *
 * \brief         Source file of OS Abstraction Layer functions.
 *
 * \b COPYRIGHT : TOSHIBA Corporation Semiconductor and Storage Company
 *                2010-2015 All rights reserved
 *
 * \b Project   : Orion
 *
 * \b Version   : 0.2
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

#define DRIVER_NAME        "emmcpci_sfc"

/*
 * Vendor Specification Reference: Orion_SFC_Specification.doc
 * Revision: 20120629A
 * Section: 3.1.1
 */
#define VENDOR_ID   0x1414
#define DEVICE_ID   0x0085
#define BAR0        0
#define OICSMM_IRQS (1 + 4 * 1)

/* Reference: Orion_MSIgen_Specification.docx [Revision 20112021A]; Table 2-1 */
#define SFC_INTERRUPT_PIN_NUMBER    3

/* Macros related to XIP in Orion */
#define XIP_CONTROL             0x0800U
#define XIP_TUNECNT             0x0898U

/**@}*/ // PF_DEFINES

/*--------------------------- Enum Definitions -------------------------------*/

/*------------------- Data Structures & Custom Typedefs ----------------------*/

/** @defgroup PF_Structures PF_Structures
 * @{
 */

/**
 * @brief Structure for holding platform driver data
 */
struct __attribute__ ((__packed__)) os_platform_data {
    _ub16 usVendorId;
    _ub16 usDeviceId;
    _ub16 usClassId;
    _ub16 usSubVendorId;
    _ub16 usSubDeviceId;
    _ub16 usCommandRo;
    _ub16 usStatus;
    _ub8 ubLine;
    _ub8 ubIrq[OICSMM_IRQS];
};

#ifdef __PERFORMANCE_MEASUREMENT
/**
 * @brief Performance structure for size and Time
 */
typedef struct tag_os_performance_t{
    unsigned long ticksCount; /**< Linux jiffies to maintain start and end */
    unsigned long sizeDone;   /**< Accumulated size for the second */
    unsigned long timeTaken;  /**<
                               * Accumulated jiffies count taken per second
                               * This is equallent to millisecond per data
                               * transaction
                               */
}os_performance_t;

#endif /* __PERFORMANCE_MEASUREMENT */
/**@}*/ // PF_Structures

/*-------------------------------- Externs -----------------------------------*/

/*------------------------------- Prototypes ---------------------------------*/

/* Function for platform driver probing */
static _b32 __devinit os_probePltDrv(struct platform_device *pDev);

/* Function for platform driver removal */
static _b32 __devexit os_removePltDrv(struct platform_device *pDev);

/* Function for probing PCI driver */
static _b32 os_probeDev(
    struct pci_dev *pDev,
    const struct pci_device_id *pId);

/* Function for removing PCI driver */
static void os_removeDev(struct pci_dev *pDev);

/*---------------- Data variable/Structure allocation (global) ---------------*/

/** @addtogroup PF_Globals PF_Globals
 * @{
 */

#ifdef __PERFORMANCE_MEASUREMENT
/* 0: Write Performance 1: Read Performance */
static os_performance_t emmc_perf[2];
#endif /* __PERFORMANCE_MEASUREMENT */

/* HC register base address */
static _addr pHcRegBase = NULL;

/*
 * Default value assigned based on Orion board. Can be changed to some other
 * value in future.
 */
static _ub32 uiSfcMsiIrq = 18;

/*
 * password to enter platform driver registration,
 * these should be same as used by SMM parent driver during IRQ allocation.
 * + name
 * + os_platform_data structure
 */

/* Name for platform driver */
static const _b8 os_pltDrvName[] = "oicsmm_sfc";

/**@}*/ // PF_Globals

/** @defgroup PF_Structures PF_Structures
 * @{
 */

/* Platform driver structure */
static struct platform_driver os_sfc_driver =
{
    .probe      = os_probePltDrv,
    .remove     = __devexit_p(os_removePltDrv),
    .driver     =
    {
        .name   = os_pltDrvName,
        .owner  = THIS_MODULE,
        .pm = NULL, /* platfrom driver is not used for PM purpose */
    },
};

/* PCI device id structure */
static const struct pci_device_id os_hcId[] =
{
    {
        .vendor = VENDOR_ID,
        .device = DEVICE_ID,
        .subvendor = PCI_ANY_ID,
        .subdevice = PCI_ANY_ID,
        .driver_data = (kernel_ulong_t)NULL,
    },
};

/* PCI driver structure */
static struct pci_driver os_pcie_emmc =
{
    .name = DRIVER_NAME,
    .id_table = os_hcId,
    .probe = os_probeDev,
    .remove = os_removeDev,
    .suspend = NULL,
    .resume = NULL,
};

/**@}*/ // PF_Structures

/*-------------------------- Function Definitions ----------------------------*/

/** @addtogroup PF_Functions PF_Functions
 * @{
 */

/**
 * @brief OS function which gets resources from platform driver
 *
 * @param[in] pDev The pointer to platform device
 *
 * @retval _OS_ERR_PROBE_PLTDRV Error in probing the platform driver.
 * @retval _OS_OK Success in platform driver probing
 */
static _b32 __devinit os_probePltDrv(struct platform_device *pDev)
{
    struct os_platform_data *pdata = pDev->dev.platform_data;
    struct resource *res_irq;
    _b32 irq_num = 0;
    _ub32 reg32;

    /* Platform driver data is NULL.Return here */
    if(!pdata)
    {
        _OS_DBG_ERR("Err: pdev->dev.platform_data null\n");
        return _OS_ERR_PROBE_PLTDRV;
    }

    /* Get the IRQ pin and number here */
    res_irq = platform_get_resource(pDev, IORESOURCE_IRQ, 0); /* pin line */
    irq_num = (_b32)resource_size(res_irq); /* how many? */

    /*
     * Interrupt pin number received is checked here. Currently Orion specific
     * checking is done here. Can be changed to other number in future
     */
    if(SFC_INTERRUPT_PIN_NUMBER != res_irq->start) /* Is this our line? */
    {
        /* This is not SFC PIN line */
        _OS_DBG_ERR("Err: invalid req/irq.\n");
        return _OS_ERR_PROBE_PLTDRV;
    }

    /* we are looking for one IRQ allocated for us, and IRQ should be valid */
    if((irq_num != 1) || ((_b32)pdata->ubIrq[0] <= 0))
    {
        _OS_DBG_ERR("Err: invalid req/irq.\n");
        return _OS_ERR_PROBE_PLTDRV;
    }

    /* Now, we are clear to get IRQ from linux database */
    uiSfcMsiIrq = (_b32)pdata->ubIrq[0];
    _OS_DBG_INFO("IRQ for SFC module --------------> %d\n", uiSfcMsiIrq);

    /*
     * Orion specific handling for getting interrupt to APIC.
     * This has to be changed in future.
     * XIP_CONTROL->INT_ROUTE = 1: to enable eMMC ctrl route to APIC
     */
    reg32 = os_read32(pHcRegBase + XIP_CONTROL);
    reg32 |= 0x00000004;
    os_write32(reg32,(pHcRegBase + XIP_CONTROL));

    /* XIP_TUNECNT verification: related to HS200 tuning process */
    reg32 = os_read32(pHcRegBase + XIP_TUNECNT);

    /* check if greater than valid range (max=0x20) */
    if(0x00000020 < reg32)
    {
        reg32 = 0x00000020;
        os_write32(reg32,(pHcRegBase + XIP_TUNECNT));
    }

    _OS_DBG_INFO("XIP config is done\n");
    return _OS_OK;
}

/**
 * @brief OS function which removes the platform driver
 *
 * @param[in] pDev The pointer to platform device
 *
 * @retval _OS_OK Success in platform driver probing
 */
static _b32 __devexit os_removePltDrv(struct platform_device *pDev)
{
    /* as of now, this is stub */
    return _OS_OK;
}

/**
 * @brief OS function which gets irq number
 *
 * @param None.
 *
 * @retval _OS_ERR_IRQ_RETRV Error in getting Irq number.
 * @retval _OS_OK Successfully got IRQ number
 */
static _b32 os_getIrq(void)
{
    _b32 ret = 0;
    /* Register ourselves with linux as platform driver, to get IRQ! */
    ret = platform_driver_register(&os_sfc_driver);
    if(0 != ret)
    {
        _OS_DBG_ERR("err: platform_driver_register() Failed [ret=%d]\n", ret);
        return _OS_ERR_IRQ_RETRV;
    }

    /* Job done for platform driver! */
    platform_driver_unregister(&os_sfc_driver);

    return _OS_OK;
}

/**
 * @brief OS function which probes the PCI device
 *
 * @param[in] pDev The pointer to PCI device.
 * @param[in] pId The pointer to PCI device ID
 *
 * @retval _OS_ERR_IRQ_RETRV Error in getting Irq number.
 * @retval _OS_OK Successfully got IRQ number
 */
static _b32 os_probeDev(
    struct pci_dev *pDev,
    const struct pci_device_id *pId)
{
    _b32 ret = _OS_OK;
    resource_size_t start_addr = 0;
    void __iomem *pReg = NULL;

    _ub32 size = 0;

    _OS_DBG_INFO("os_probeDev\n");

    /* Initialize device before it is used by the driver */
    ret = pci_enable_device(pDev);
    if(0 != ret)
    {
        _OS_DBG_ERR("pci_enable_device\n");
        return _OS_ERR_PROBE_PCIDRV;
    }

    /* PCI Device Control Register setting */
    if((pDev->vendor == VENDOR_ID) && (pDev->device == DEVICE_ID))
    {
        _ub16 reg16;
        _b32 pos;
        pos = pci_find_capability(pDev, PCI_CAP_ID_EXP);
        if(pos)
        {
            pci_read_config_word(pDev, pos + PCI_EXP_DEVCTL, &reg16);

            /* Enable Relax Ordering: cleared */
            reg16 &= ~PCI_EXP_DEVCTL_RELAX_EN;

            /* Enable No Snoop: cleared */
            reg16 &= ~PCI_EXP_DEVCTL_NOSNOOP_EN;
            pci_write_config_word(pDev, pos + PCI_EXP_DEVCTL, reg16);
        }
    }

    /* Enable bus mastering for the device */
    pci_set_master(pDev);

    /* Fetch BAR-0 info */
    start_addr = pci_resource_start(pDev, BAR0);
    _OS_DBG_INFO("start_addr = 0x%08x\n", (unsigned int)start_addr);
    size = pci_resource_len(pDev, BAR0);
    _OS_DBG_INFO("size = 0x%08x\n", (unsigned int)size);

    /* Reserve PCI I/O and memory resource by name 'funtush_bar0' */
    ret = pci_request_region(pDev, BAR0, "funtush_bar0");
    if(0 != ret)
    {
        _OS_DBG_ERR("Error: pci_request_region\n");

        /* Disable bus-mastering for the device */
        pci_clear_master(pDev);

        /* Disable PCI device after use */
        pci_disable_device(pDev);

        return _OS_ERR_PROBE_PCIDRV;
    }

    /* Get the virtual address mapping */
    pReg = (void __iomem *)ioremap_nocache(start_addr, size);
    pHcRegBase = (_addr)(unsigned long)pReg;
    if(NULL == pHcRegBase)
    {
        /* Release the PCI I/O and memory resources previously reserved */
        pci_release_region(pDev, BAR0);

        /* Disable bus-mastering for the device */
        pci_clear_master(pDev);

        /* Disable PCI device after use */
        pci_disable_device(pDev);

        _OS_DBG_ERR("Error: ioremap_nocache\n");

        return _OS_ERR_PROBE_PCIDRV;
    }

    _OS_DBG_INFO("emmc_reg_base = %p\n", pHcRegBase);

    return _OS_OK;
}


/**
 * @brief OS function which removes the PCI device
 *
 * @param[in] pDev The pointer to PCI device.
 *
 * @retval None.
 */
static void os_removeDev(struct pci_dev *pDev)
{
    /* release the virtual address mapping */
    iounmap((void __iomem *)pHcRegBase);

    /* Release the PCI I/O and memory resources previously reserved */
    pci_release_region(pDev, BAR0);

    /* Disable bus-mastering for the device */
    pci_clear_master(pDev);

    /* Disable PCI device after use */
    pci_disable_device(pDev);
}

/*----------------------------------------------------------------------------*/
/**
 * @brief Resource allocation for Linux PCI platform
 *
 * @param[in] pArg The pointer to OS resource handle.
 *
 * @retval _OS_OK creation of lock successful.
 * @retval _OS_ERR_OBTRES Error in obtaining resources.
 */
_ub32 os_obtainResource(os_resource_t *pArg)
{
    /* Get Base address of register set */
    if(0 != pci_register_driver(&os_pcie_emmc))
    {
        _OS_DBG_ERR("pci_register_driver() failed.\n");
        return _OS_ERR_OBTRES;
    }

    /*
     * Retreive allocated IRQ for SFC from linux, through platform driver
     * interface.
     */
    if(0 != os_getIrq())
    {
        _OS_DBG_ERR("IRQ get failed for eMMC controller.\n");
        return _OS_ERR_OBTRES;
    }

    /* Update the resources in global structures */
    pArg->uiIrq = uiSfcMsiIrq;
    pArg->uiBase = (_addr)pHcRegBase;

    return _OS_OK;
}

/**
 * @brief Release Linux PCI platform device
 *
 * @param[in] pArg The pointer to OS resource handle.
 *
 * @retval None
 */
void os_releaseResource(os_resource_t *pArg)
{
    /* De register the platform driver */
    pci_unregister_driver(&os_pcie_emmc);
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

