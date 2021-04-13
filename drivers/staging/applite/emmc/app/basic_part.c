/**
 * @file          basic_part.c
 *
 * \brief         eMMC partition functions test program.
 *
 * \b COPYRIGHT : TOSHIBA Corporation Semiconductor and Storage Company
 *                2010-2015 All rights reserved.
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
 * @addtogroup TestApplication
 * @{
 */

/**
 * @addtogroup UnitTesting
 * @{
 */

/*----------------------- Header Files Inclusions ---------------------------*/
#include "debug.h"
#include "emmc_api.h"
#include "os.h"
#include "config.h"

/*-------------------------- Macro Definitions ------------------------------*/


/** @addtogroup UT_DEFINES UT_DEFINES
 * @{
 */

#define DRIVER_DESCRIPTION   "eMMC partition driver"
#define COMPANY_NAME         "TSIP"
#define EMMC_NUM_OF_PARTITION   4

/**@}*/ // UT_DEFINES

/*-------------------------- Enum Definitions --------------------------------*/

/*------------------ Data Structures & Custom Typedefs -----------------------*/

/*------------------------------ Externs -------------------------------------*/

/*---------------------------- Prototypes ------------------------------------*/

/*------------- Data variable/Structure allocation (global) -----------------*/

/** @addtogroup UT_Globals UT_Globals
 * @{
 */

static unsigned int gpp_num = 1;

static unsigned int gpp1_type = _COM_PART_TYPE_DEFAULT;
static unsigned int gpp2_type = _COM_PART_TYPE_DEFAULT;
static unsigned int gpp3_type = _COM_PART_TYPE_DEFAULT;
static unsigned int gpp4_type = _COM_PART_TYPE_DEFAULT;

static unsigned int gppext1_type = _COM_EXT_PART_TYPE_DEFAULT;
static unsigned int gppext2_type = _COM_EXT_PART_TYPE_DEFAULT;
static unsigned int gppext3_type = _COM_EXT_PART_TYPE_DEFAULT;
static unsigned int gppext4_type = _COM_EXT_PART_TYPE_DEFAULT;

static unsigned int gpp1_size = 0x400000; /* Min value = 1*WPG = 4MB */
static unsigned int gpp2_size = 0x400000; /* Min value = 1*WPG = 4MB */
static unsigned int gpp3_size = 0x400000; /* Min value = 1*WPG = 4MB */
static unsigned int gpp4_size = 0x400000; /* Min value = 1*WPG = 4MB */

static unsigned int euda_addr = 0;
static unsigned int euda_size = 0;

/**@}*/ // UT_Globals

/** @addtogroup UT_Macros UT_Macros
 * @{
 */

/* Partition related Module params */
module_param(gpp_num, int, 0);
MODULE_PARM_DESC(gpp_num, "Number of GPPs to be created [Max:4]");

/* Partition Types from Module Params */
module_param(gpp1_type, int, 0);
MODULE_PARM_DESC(gpp1_type, "Partition type of GPP1 \
    (0:Default, 1:Enhanced, 2: Extended) ");

module_param(gpp2_type, int, 0);
MODULE_PARM_DESC(gpp2_type, "Partition type of GPP2 \
    (0:Default, 1:Enhanced, 2: Extended) ");

module_param(gpp3_type, int, 0);
MODULE_PARM_DESC(gpp3_type, "Partition type of GPP3 \
    (0:Default, 1:Enhanced, 2: Extended) ");

module_param(gpp4_type, int, 0);
MODULE_PARM_DESC(gpp4_type, "Partition type of GPP4 \
    (0:Default, 1:Enhanced, 2: Extended) ");

/* Extended Partition Types from Module Params */
module_param(gppext1_type, int, 0);
MODULE_PARM_DESC(gppext1_type, "Extended Partition type of GPP1 \
    (0:Default, 1:System Code, 2:Non persistent data) ");

module_param(gppext2_type, int, 0);
MODULE_PARM_DESC(gppext2_type, "Extended Partition type of GPP2 \
    (0:Default, 1:System Code, 2:Non persistent data) ");

module_param(gppext3_type, int, 0);
MODULE_PARM_DESC(gppext3_type, "Extended Partition type of GPP3 \
    (0:Default, 1:System Code, 2:Non persistent data) ");

module_param(gppext4_type, int, 0);
MODULE_PARM_DESC(gppext4_type, "Extended Partition type of GPP4 \
    (0:Default, 1:System Code, 2:Non persistent data) ");

/* Partition Sizes for Module Params */
module_param(gpp1_size, int, 0);
MODULE_PARM_DESC(gpp1_size, "Partition size of GPP1 in Bytes \
    (should be multiple of 4MB) ");

module_param(gpp2_size, int, 0);
MODULE_PARM_DESC(gpp2_size, "Partition size of GPP2 in Bytes \
    (should be multiple of 4MB) ");

module_param(gpp3_size, int, 0);
MODULE_PARM_DESC(gpp3_size,  "Partition size of GPP3 in Bytes \
    (should be multiple of 4MB) ");

module_param(gpp4_size, int, 0);
MODULE_PARM_DESC(gpp4_size, "Partition size of GPP4 in Bytes \
    (should be multiple of 4MB) ");

/* Enhanced user data partition configuration */
module_param(euda_addr, int, 0);
MODULE_PARM_DESC(euda_addr, "Enhanced user partition start address");

module_param(euda_size, int, 0);
MODULE_PARM_DESC(euda_size, "Enhanced user partition size \
    (should be multiple of 4MB)");

/**@}*/ // UT_Macros

/*----------------------- Function Definitions -------------------------------*/

/** @addtogroup UT_Functions UT_Functions
 * @{
 */

/**
 * @brief Partition driver initialization for eMMC device
 *
 * This will initialize the eMMC device with host controller
 * This should be invoked two times by user for the fresh
 * devices, first time this driver will disable the emulation mode
 * after restart the power cycle (means reset the device), in second time
 * driver creating the required partitions based on the module params
 *
 * @param none
 *
 * @retval NOERROR for successful initialization
 * @retval ERROR for failure
 */
static int __init driver_initialize(void)
{
    emmc_sts_e ret = _EMMC_STS_OK;
    unsigned int uiVersion;

    com_gpp_attr_t tGpp_attrib[EMMC_NUM_OF_PARTITION];
    com_gpp_attr_t tattrib;

    com_euda_attr_t tEuda_attrib;
    com_part_attr_t  tCreatePart;

    tGpp_attrib[0].eType       = gpp1_type;
    tGpp_attrib[0].eExtType    = gppext1_type;
    tGpp_attrib[0].uiPartSize = gpp1_size;

    tGpp_attrib[1].eType       = gpp2_type;
    tGpp_attrib[1].eExtType    = gppext2_type;
    tGpp_attrib[1].uiPartSize = gpp2_size;

    tGpp_attrib[2].eType       = gpp3_type;
    tGpp_attrib[2].eExtType    = gppext3_type;
    tGpp_attrib[2].uiPartSize = gpp3_size;

    tGpp_attrib[3].eType       = gpp4_type;
    tGpp_attrib[3].eExtType    = gppext4_type;
    tGpp_attrib[3].uiPartSize = gpp4_size;

    tEuda_attrib.uiStartAddr   = euda_addr;
    tEuda_attrib.uiSize       = euda_size;

    tCreatePart.pEattr = &tEuda_attrib;
    tCreatePart.pGattr = tGpp_attrib;

    /* Enable logging */
    debug_setZone(_DZ_LEVEL1);
    emmc_getVersion(&uiVersion);

    printk("\n");
    printk("*********************************************************\n");
    printk("               eMMC Partition Driver                     \n");
    printk("  TOSHIBA Corporation Semiconductor and Storage Company  \n");
    printk("            2010-2015 All rights reserved                \n");
    printk("           eMMC Driver Version 0x%08X\n",         uiVersion );
    printk("*********************************************************\n");

    /* Initialize the eMMC driver */
    ret = emmc_init();
    if(_EMMC_STS_OK != ret)
    {
        dz_print(_DZ_CRTICAL, "Error: emmc_init() failed code[0x%08x].\n", ret);
        return ret;
    }

    ret = emmc_getGPPAttributes(0, _COM_PARTITION_GPP1, &tattrib);
    if(_EMMC_DEV_PART_NOT_CREATED == ret)
    {
        ret = emmc_disableEmulationMode(0);
        if(_EMMC_STS_OK == ret)
        {
            printk("********************************************************\n");
            printk("INFO: Emulation mode is done, Please RESTART the target.\n");
            printk("********************************************************\n");
            emmc_exit();
            return ret;
        }

        /*
         * if enhanced user data size is zero,
         * pass NULL in to enhanced attrib for create partition
         */
        if(0 == euda_size)
        {
            tCreatePart.pEattr = NULL;
        }

        ret = emmc_createPartition(0, gpp_num, &tCreatePart);
        if(_EMMC_STS_OK != ret)
        {
            dz_print(_DZ_CRTICAL, \
                "Error: emmc_createPartition() failed code[0x%08x].\n", ret);
            emmc_exit();
            return ret;
        }
        printk("***********************************************************\n");
        printk("INFO: New Partitions are created, Please RESTART the target\n");
        printk("***********************************************************\n");
    }
    else
    {
        dz_print(_DZ_CRTICAL, "INFO: Partition is already Created\n");
    }

    return 0;
}

/**
 * @brief Unit test driver Deinitialization for eMMC device
 *
 * This will deinitialize the eMMC device and host controller
 * This function will be invoked while rmmod for the driver
 *
 * @param none
 *
 * @retval none
 */
static void __exit driver_exit(void)
{
    dz_print(_DZ_INFO, "... relaxing emmc partition driver!\n");

    emmc_exit();
}

/**@}*/ // UT_Functions

/** @addtogroup UT_Macros UT_Macros
 * @{
 */

module_init(driver_initialize);
module_exit(driver_exit);
MODULE_DESCRIPTION(DRIVER_DESCRIPTION);
MODULE_AUTHOR(COMPANY_NAME);
MODULE_LICENSE("GPL");

/**@}*/ // UT_Macros

/**@}*//* UnitTesting */
/**@}*//* TestApplication */

