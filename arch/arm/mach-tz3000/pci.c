/*
 * routines for the Toshiba tz3000 pcie
 *
 * (C) Copyright TOSHIBA CORPORATION SEMICONDUCTOR COMPANY 2010
 * (C) Copyright TOSHIBA CORPORATION
 *      SEMICONDUCTOR & STORAGE PRODUCTS COMPANY 2013
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <linux/types.h>
#include <linux/pci.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/syscore_ops.h>
#include <asm/mach-types.h>
#include <mach/irqs.h>
#include <mach/platform.h>

#define TZ3000_PCI_REG_BASE		TZ3000_PCIE_BASE
#define TZ3000_PCI_REG_SIZE		0x00010000

#define TZ3000_PCI_MEM_RESOURCE_BASE	TZ3000_PCIE_EXMEM_BASE
#define TZ3000_PCI_MEM_RESOURCE_SIZE	0x10000000

#define TZ3000_PCI_RC_MEM_BASE		0x80000000
#define TZ3000_PCI_RC_MEM_SIZE		0x80000000

#define TZ3000_PCI_RC_MBOX_PCIE_BASE	TZ3000_MBOX_PCIE_BASE
#define TZ3000_PCI_RC_MBOX_PCIE_SIZE	0x00000400

#define TZ3000_PCI_VENDOR_ID		PCI_VENDOR_ID_TOSHIBA
#define TZ3000_PCI_DEVICE_ID		0x0421
#define TZ3000_PCI_REVISION_ID		0x00
#define TZ3000_PCI_CLASS_CODE		((PCI_CLASS_BRIDGE_PCI << 8) | 0x00)

#define PCFG_EXP_BASE			0x0040
#define PCFG_PM_BASE			0x0080
#define PCFG_AER_BASE			0x0100
#define PCFG_VC_BASE			0x0150

/*
 * Register Definitions
 */
enum pcie_mmap_regs {
	PCFG_PCIID			= PCI_VENDOR_ID,
	PCFG_STSCMD			= PCI_COMMAND,
	PCFG_PRIMARY_BUS		= PCI_PRIMARY_BUS,
	PCFG_PREF_MEMORY_BASE		= PCI_PREF_MEMORY_BASE,
	PCFG_PREF_BASE_UPPER32		= PCI_PREF_BASE_UPPER32,
	PCFG_PREF_LIMIT_UPPER32		= PCI_PREF_LIMIT_UPPER32,
	PCFG_BRDGCNTRL			= PCI_BRIDGE_CONTROL & ~0x3,
	PCFG_DEVCTLSTS			= (PCFG_EXP_BASE + PCI_EXP_DEVCTL),
	PCFG_RTCTL			= (PCFG_EXP_BASE + PCI_EXP_RTCTL),

	PBSC_VENDOR_ID			= 0x2000,
	PBSC_REVISION_ID		= 0x2008,
	PBSC_LINK_CAPA			= 0x204C,
	PBSC_FUNC_READY			= 0x2FC0,

	PTLC_RC_VBAR_RANGE_SET		= 0x300C,
	PTLC_RC_VBAR_0			= 0x3010,
	PTLC_RC_VBAR_1			= 0x3014,
	PTLC_RC_VBAR_2			= 0x3018,
	PTLC_RC_VBAR_3			= 0x301C,
	PTLC_RC_VBAR_4			= 0x3020,
	PTLC_RC_VBAR_5			= 0x3024,

	PTLC_RC_BS_VBAR_0		= 0x3030,
	PTLC_RC_BS_VBAR_1		= 0x3034,
	PTLC_RC_BS_VBAR_2		= 0x3038,
	PTLC_RC_BS_VBAR_3		= 0x303C,
	PTLC_RC_BS_VBAR_4		= 0x3040,
	PTLC_RC_BS_VBAR_5		= 0x3044,

	PMACC_PCLK_SYNC_RST		= 0x5000,
	PMACC_RATE_CHG_CTRL		= 0x5210,
	PMACC_LTSSM_MON			= 0x5400,

	IPC_PIPE_RESET_SH		= 0x6000,
	IPC_IP_MODE			= 0x6004,
	IPC_PHY_CFGOUT			= 0x6020,

	IPC_RANGE00_UP_OFFSET		= 0x6200,
	IPC_RANGE00_EN			= 0x6204,
	IPC_RANGE00_UP_RPLC		= 0x6208,
	IPC_RANGE00_WIDTH		= 0x620C,
	IPC_RANGE01_UP_OFFSET		= 0x6210,
	IPC_RANGE01_EN			= 0x6214,
	IPC_RANGE01_UP_RPLC		= 0x6218,
	IPC_RANGE01_WIDTH		= 0x621C,
	IPC_RANGE02_UP_OFFSET		= 0x6220,
	IPC_RANGE02_EN			= 0x6224,
	IPC_RANGE02_UP_RPLC		= 0x6228,
	IPC_RANGE02_WIDTH		= 0x622C,
	IPC_RANGE03_UP_OFFSET		= 0x6230,
	IPC_RANGE03_EN			= 0x6234,
	IPC_RANGE03_UP_RPLC		= 0x6238,
	IPC_RANGE03_WIDTH		= 0x623C,

	MACC_NFTS_SREF_CTRL		= 0x9004,
	MACC_NFTS_CREF_CTRL		= 0x9008,
	MACC_L1EXITLTCY_CTRL		= 0x900C,
	MACC_TXCOMMON_TO_CTRL		= 0x9080,
	MACC_PHYPIPE_INFO		= 0x9100,

	STMA_PINT0_INT			= 0xA000,
	STMA_PINT0_INT_MSK		= 0xA004,
	STMA_PORT_INT1			= 0xA010,
	STMA_PORT_INT1_MSK		= 0xA014,
	STMA_PORT_INT2			= 0xA020,
	STMA_PORT_INT2_MSK		= 0xA024,
	STMA_VC_VALID_INT		= 0xA100,
	STMA_VC_VALID_INT_MSK		= 0xA104,
	STMA_MAC_INFORM_INT		= 0xA108,
	STMA_MAC_INFORM_INT_MSK		= 0xA10C,
	STMA_RECEIVE_MSG		= 0xA110,
	STMA_RECEIVE_MSG_MSK		= 0xA114,
	STMA_RC_INTERNAL_INT		= 0xA120,
	STMA_RC_INTERNAL_INT_MSK	= 0xA124,
	STMA_POWER_INFORM_INT		= 0xA128,
	STMA_POWER_INFORM_INT_MSK	= 0xA12C,
	STMA_VC0_INTEGRITY_ERR		= 0xA200,
	STMA_VC0_TRN_ERR_MSK		= 0xA204,
	STMA_VC0_MAXI_ERR		= 0xA280,
	STMA_VC0_MAXI_ERR_MSK		= 0xA284,
	STMA_VC0_AXIW_ERR		= 0xA300,
	STMA_VC0_AXIW_ERR_MSK		= 0xA308,
	STMA_VC0_AXIR_ERR		= 0xA310,
	STMA_VC0_AXIR_ERR_MSK		= 0xA318,

	APCFG_ACC_KICK			= 0xB000,
	APCFG_ACC_BUSY			= 0xB004,
	APCFG_ACC_RDATA			= 0xB008,
	APCFG_TLP_HED0			= 0xB010,
	APCFG_TLP_HED1			= 0xB014,
	APCFG_TLP_HED2			= 0xB018,
	APCFG_TLP_DAT			= 0xB01C,
};

/*
 * Register Bit Field
 */
/* DEVCTL/DEVSTS */
#define DEVCTL_RE		(PCI_EXP_DEVCTL_URRE | PCI_EXP_DEVCTL_FERE | \
				 PCI_EXP_DEVCTL_NFERE | PCI_EXP_DEVCTL_CERE)

/* PBSC_VNDDEV_ID */
#define PBSC_BS_CFG_DEVICE_ID(x)	(((x) & 0xffff) << 16)
#define PBSC_BS_CFG_VENDOR_ID(x)	(x)

/* PBSC_REVISION_ID */
#define PBSC_BS_CFG_CLASS_CODE(x)	(((x) & 0xffffff) << 8)
#define PBSC_BS_CFG_REVID(x)		(x)

#define PBSC_BS_CFG_MAX_LNK_SPD		0x0000000f
#define PBSC_BS_CFG_MAX_LNK_SPD_2_5GT	0x00000001
#define PBSC_BS_CFG_MAX_LNK_SPD_5_0GT	0x00000002

/* PBSC_FUNC_READY */
#define PBSC_BS_FUNC_READY		0x00000001

/* PTLC_RC_VBAR_RANGE_SET */
#define PBSC_VBAR_P2_RPLC_EN		0x40000000
#define PBSC_VBAR_P2_OW(x)		(((x) & 0x3f) << 24)
#define PBSC_VBAR_P1_RPLC_EN		0x00400000
#define PBSC_VBAR_P1_OW(x)		(((x) & 0x3f) << 16)
#define PBSC_VBAR_P0_RPLC_EN		0x00004000
#define PBSC_VBAR_P0_OW(x)		(((x) & 0x3f) << 8)
#define PBSC_VBAR_PARTITION_EN(x)	(((x) & 0x7) << 2)
#define PBSC_VBAR_P2_EN			PBSC_VBAR_PARTITION_EN(4)
#define PBSC_VBAR_P1_EN			PBSC_VBAR_PARTITION_EN(2)
#define PBSC_VBAR_P0_EN			PBSC_VBAR_PARTITION_EN(1)
#define PBSC_RC_NOVBARMATCH_THR		0x00000002
#define PBSC_RC_BASE_LIM_EN		0x00000001

/* PMACC_PCLK_SYNC_RST */
#define PMACC_PCLK_SYNC_RST_RESET	0x00000001
#define PMACC_PCLK_SYNC_RST_ACTIVE	0x00000000

/* PMACC_RATE_CHG_CTRL */
#define PMACC_RG_PP_RATECHGENA	0x00000010

/* IPC_PIPE_RESET_SH */
#define IPC_PIPE_RESET_SH_LOW	0x00000000
#define IPC_PIPE_RESET_SH_HIGH	0x00000001

/* IPC_IP_MODE */
#define IP_MODE_EP		0x00000000
#define IP_MODE_RC		0x00000001

/* IPC_RANGE_UP_EN */
#define IPC_OFFSET_ADR_DW(x)	((x) & 0xfffff000)
#define IPC_OFFSET_PTYPE_IO	0x00000008
#define IPC_OFFSET_PTYPE_MEM	0x00000000
#define IPC_OFFSET_EN		0x00000001

/* IPC_RANGE_WIDTH */
#define IPC_OFFSET_OW(x)		((x) & 0x3f)
#define IPC_OFFSET_TC(x)		(((x) & 0x7) << 6)
#define IPC_OFFSET_REPLACE_DW(x)	((x) & 0xfffff000)

/* MACC_NFTS_SREF_CTRL */
#define MACC_NFTS_SREF_CTRL_WVAL	0x00002626

/* MACC_NFTS_CREF_CTRL */
#define MACC_NFTS_CREF_CTRL_WVAL	0x00002626

/* MACC_L1EXITLTCY_CTRL */
#define MACC_L1EXITLTCY_CTRL_WVAL	0x00120012

/* MACC_TXCOMMON_TO_CTRL */
#define MACC_TXCOMMON_TO_CTRL_WVAL	0x0000000A

/* MACC_PHYPIPE_INFO */
#define MACC_RG_PA_RXEIDLY(x)		(((x) & 0x3f) << 24)
#define MACC_RG_PA_TXSWING_FULL		0x00000000
#define MACC_RG_PA_TXSWING_LOW		0x00010000
#define MACC_RG_PA_CLKREQ_SUPPORT	0x00000100
#define MACC_RG_PA_PIPE30		0x00000002
#define MACC_RG_PA_GENERALPHY		0x00000001
#define MACC_PHYPIPE_INFO_WVAL		0x16000000

/* STMA_PINT0_INT */
#define STMA_LINK_STATE_MASK		0x00000600
#define STMA_LINK_STATE_L0		0x00000000
#define STMA_LINK_STATE_L1		0x00000200
#define STMA_LINK_STATE_L2		0x00000400
#define STMA_LINK_STATE_LINKDOWN	0x00000600
#define STMA_LINK_STATE_CHG		0x00000100

#define STMA_PCLK_VALID_CHG		0x00000002
#define STMA_PCLK_VALID			0x00000001

/* STMA_PORT_INT1 */
#define STMA_VC0_SAXI_ERR_DET_RES	0x01000000
#define STMA_VC0_MAXI_ERR_DET_RES	0x00010000
#define STMA_VC0_INTERNAL_ERR_DET_RES	0x00000100
#define STMA_POWER_INFORM_INT_RES	0x00000010
#define STMA_RC_INTERNAL_INT_RES	0x00000008
#define STMA_RECEIVE_MSG_INT_RES	0x00000004
#define STMA_MAC_INFORM_INT_RES		0x00000002
#define STMA_VC_VALID_INT_RES		0x00000001

/* STMA_PORT_INT2 */
#define STMA_TR_PND_CHG_INT_RES		0x00000008
#define STMA_PMCSR_CHANGE_INT_RES	0x00000004	/* for EP */
#define STMA_FLR_INT_RES		0x00000001	/* for EP */

/* STMA_VC_VALID_INT */
#define STMA_VC0_VALID_CHG		0x00000001
#define STMA_VC0_VALID			0x00000100

/* APCFG_ACC_KICK */
#define APCFG_TLP_KICK		0x00000001

/* APCFG_ACC_BUSY */
#define APCFG_ACC_BUSY_ERR	0x00000002
#define APCFG_ACC_BUSY_BUSY	0x00000001

/* APCFG_TLP_HED0 */
#define APCFG_TLP_FMT(x)	(((x) & 0x7) << 29)
#define APCFG_TLP_TYPE(x)	(((x) & 0x1f) << 24)
#define APCFG_TLP_TD		0x00008000
#define APCFG_TLP_HED0_3DW_ND	0x0
#define APCFG_TLP_HED0_3DW_WD	0x2
#define APCFG_TLP_HED0_CFGTYP0	0x04
#define APCFG_TLP_HED0_CFGRD0	(APCFG_TLP_FMT(APCFG_TLP_HED0_3DW_ND) | \
				 APCFG_TLP_TYPE(APCFG_TLP_HED0_CFGTYP0))
#define APCFG_TLP_HED0_CFGWR0	(APCFG_TLP_FMT(APCFG_TLP_HED0_3DW_WD) | \
				 APCFG_TLP_TYPE(APCFG_TLP_HED0_CFGTYP0))

/* APCFG_TLP_HED1 */
#define APCFG_TLP_REQID(x)	(((x) & 0xffff) << 16)
#define APCFG_TLP_FDWBE(x)	((x) & 0xf)

/* APCFG_TLP_HED2 */
#define APCFG_TLP_HED2_0(x)	(((x) & 0xff) << 24)
#define APCFG_TLP_HED2_1(x)	(((x) & 0xff) << 16)
#define APCFG_TLP_HED2_2(x)	((x) & 0xffff)
#define APCFG_TLP_HED2_D(b, d, r)	(APCFG_TLP_HED2_0(b) | \
					 APCFG_TLP_HED2_1(d) | \
					 APCFG_TLP_HED2_2(r))

/*
 * pcie register read/write functions
 */
static void __iomem *tz3000_pcie_reg_base;

static inline u32 pcie_reg_read(enum pcie_mmap_regs reg)
{
	return __raw_readl(tz3000_pcie_reg_base + reg);
}
static inline void pcie_reg_write(enum pcie_mmap_regs reg, u32 value)
{
	__raw_writel(value, tz3000_pcie_reg_base + reg);
}

/*
 * pcie misc functions
 */
static inline u32 pcie_get_ow(u32 size)
{
	return 64 - (get_bitmask_order(size) - 1);
}

/* Error reporting for debug
   0:none, 1:Correctable, 2:Non-Fatal, 4:Fatal, 7:all */
#define ERROR_REPORT_LEVEL	4

/* PERST signal is connected to GPIO. */
static int pci_reset_gpio = -1;

static void tz3000_pci_device_reset(int assert)
{
	if (pci_reset_gpio >= 0) {
		if (assert)
			gpio_set_value(pci_reset_gpio, 0);
		else
			gpio_set_value(pci_reset_gpio, 1);
	}
}

static int pcie_boot_phypll(void)
{
	u32 pint0int;
	int timeout;

	pr_info("PCIe: Phy pll boot...");

	/* SW_Set_Reg_EN */
	pcie_reg_write(IPC_PIPE_RESET_SH, IPC_PIPE_RESET_SH_HIGH);

	/* Check PCLK is stable */
	timeout = 1000;
	do {
		/* Check STMA_PINT0_INT */
		pint0int = pcie_reg_read(STMA_PINT0_INT);
		if (pint0int & STMA_PCLK_VALID)
			break;
		udelay(1);
	} while (--timeout);
	if (timeout == 0) {
		pr_cont("NG (phy pll time out, pint0int=0x%08x)\n", pint0int);
		return -1;
	}
	pr_cont("ok\n");

	/* clear STMA_PCLK_VALID_CHG */
	pcie_reg_write(STMA_PINT0_INT, 0xffffffff);
	return 0;
}

static int pcie_wait_vc_valid(void)
{
	u32 val;
	int timeout;

	/* SW_Set_Reg_PMAC_PSRST Task */
	pcie_reg_write(PMACC_PCLK_SYNC_RST, PMACC_PCLK_SYNC_RST_ACTIVE);

	/* check linkup status */
	pr_info("PCIe: Link up...");

	timeout = 100000;
	do {
		/* Wait Link UP */
		val = pcie_reg_read(STMA_VC_VALID_INT);
		if (val & STMA_VC0_VALID)
			break;
		udelay(1);
	} while (--timeout);
	if (timeout == 0) {
		pr_cont("NG (vc_valid_int=0x%08x)\n", val);
		return -1;
	}
	pr_cont("ok\n");

	/* clear STMA_VC0_VALID_CHG */
	pcie_reg_write(STMA_VC_VALID_INT, val);

	/* clear STMA_LINK_STATE_CHG */
	pcie_reg_write(STMA_PINT0_INT, 0xffffffff);
	return 0;
}

static void pcie_set_mapping(void)
{
	u32 val;

	/* Set Primary/Secondary/Subordinate Bus Number */
	val = (0xff << 16) | (1 << 8) | (0 << 0);
	pcie_reg_write(PCFG_PRIMARY_BUS, val);

	/* SW_Set_Reg_PTRAN_RC_VBAR Task */
	val = (PBSC_RC_BASE_LIM_EN | PBSC_VBAR_P0_EN | PBSC_VBAR_P1_EN |
	       PBSC_VBAR_P0_OW(pcie_get_ow(TZ3000_PCI_RC_MEM_SIZE)) |
	       PBSC_VBAR_P1_OW(pcie_get_ow(TZ3000_PCI_RC_MBOX_PCIE_SIZE)));
	pcie_reg_write(PTLC_RC_VBAR_RANGE_SET, val);

	/* set VBAR 0 */
	val = TZ3000_PCI_RC_MEM_BASE;
	val |= PCI_BASE_ADDRESS_MEM_TYPE_64 | PCI_BASE_ADDRESS_MEM_PREFETCH;
	pcie_reg_write(PTLC_RC_VBAR_0, val);
	pcie_reg_write(PTLC_RC_VBAR_1, 0x0);

	/* disable replace address function */
	pcie_reg_write(PTLC_RC_BS_VBAR_0, 0x0);
	pcie_reg_write(PTLC_RC_BS_VBAR_1, 0x0);

	/* set VBAR 1 */
	val = TZ3000_PCI_RC_MBOX_PCIE_BASE;
	val |= PCI_BASE_ADDRESS_MEM_TYPE_64;
	pcie_reg_write(PTLC_RC_VBAR_2, val);
	pcie_reg_write(PTLC_RC_VBAR_3, 0x0);

	/* disable replace address function */
	pcie_reg_write(PTLC_RC_BS_VBAR_2, 0x0);
	pcie_reg_write(PTLC_RC_BS_VBAR_3, 0x0);
}

static int pcie_start_pcieip(void)
{
	u32 addr;
	u32 rcctl, ecmd;

	/* Root error */
	addr = PCFG_EXP_BASE + PCI_EXP_RTCTL;
	rcctl = pcie_reg_read(addr);
	pcie_reg_write(addr, rcctl | (ERROR_REPORT_LEVEL & 0x7));

	addr = PCFG_AER_BASE + PCI_ERR_ROOT_COMMAND;
	ecmd = pcie_reg_read(addr);
	pcie_reg_write(addr, ecmd | (PCI_ERR_ROOT_CMD_COR_EN |
				     PCI_ERR_ROOT_CMD_NONFATAL_EN |
				     PCI_ERR_ROOT_CMD_FATAL_EN));
	return 0;
}

static void pcie_config_pcierc(void)
{
	u32 stscmd, dstatus, rtctl;

	pr_debug("PCIe: Config RC\n");

	/* Set busmaster enable */
	stscmd = pcie_reg_read(PCFG_STSCMD);
	pcie_reg_write(PCFG_STSCMD,
		       stscmd | PCI_COMMAND_MASTER | PCI_COMMAND_MEMORY);
	stscmd = pcie_reg_read(PCFG_STSCMD);
	pr_debug("PCIe: Status/Command (0x004) : 0x%08x\n", stscmd);

	/* Set CRS Software Visibility Enable */
	rtctl = pcie_reg_read(PCFG_RTCTL);
	pcie_reg_write(PCFG_RTCTL, rtctl | PCI_EXP_RTCTL_CRSSVE);
	rtctl = pcie_reg_read(PCFG_RTCTL);
	pr_debug("PCIe: Root Control (0x05c) : 0x%08x\n", rtctl);

	/* Enable error reporting */
	dstatus = pcie_reg_read(PCFG_DEVCTLSTS);
	dstatus = (dstatus & 0x0000ffff) | DEVCTL_RE;
	pcie_reg_write(PCFG_DEVCTLSTS, dstatus);
	dstatus = pcie_reg_read(PCFG_DEVCTLSTS);
	pr_debug("PCIe: Device status/control (0x048) : 0x%08x\n", dstatus);
}

/**
 * tz3000_pcie_portN_interrupt - PCIe interrupt handler
 * @irq: interrupt number
 * @dev_id: device data structure pointer(not used)
 *
 * This is the interrupt handler for PCIe interrupts
 */
static irqreturn_t tz3000_pcie_port0_interrupt(int irq, void *dev_id)
{
	u32 int_mask, int_status;
	u32 ltssm_mon;

	pr_debug("PCIe port0 Interrupt Handler called\n");

	/* Get interrupt status */
	int_status = pcie_reg_read(STMA_PINT0_INT);

	/* Mask interrupt */
	int_mask = pcie_reg_read(STMA_PINT0_INT_MSK);
	pcie_reg_write(STMA_PINT0_INT_MSK, 0xffffffff);

	pr_debug("PCIE port0 Interrupt (irq %d)\n", irq);
	pr_debug("PCIE port0 Interrupt status : 0x%08x\n", int_status);
	pr_debug("PCIE port0 Interrupt mask   : 0x%08x\n", int_mask);

	if (int_status & STMA_PCLK_VALID_CHG) {
		if (int_status & STMA_PCLK_VALID)
			pr_debug("PCIE PCLK is valid\n");
		else
			pr_debug("PCIE PCLK is invalid\n");
	}
	if (int_status & STMA_LINK_STATE_CHG) {
		u32 lstate = int_status & STMA_LINK_STATE_MASK;
		ltssm_mon = pcie_reg_read(PMACC_LTSSM_MON);
		pr_debug("                  ltssm_mon : 0x%08x\n", ltssm_mon);

		if (lstate == STMA_LINK_STATE_L0)
			pr_debug("PCIE LINK_STATE is L0\n");
		else if (lstate == STMA_LINK_STATE_L1)
			pr_debug("PCIE LINK_STATE is L1\n");
		else if (lstate == STMA_LINK_STATE_L2)
			pr_debug("PCIE LINK_STATE is L2\n");
		else
			/* not implemented yet */
			pr_debug("PCIE LINK_STATE is Link Down\n");
	}

	/* clear interrupt */
	pcie_reg_write(STMA_PINT0_INT, int_status);

	/* Enable interrupt */
	pcie_reg_write(STMA_PINT0_INT_MSK, int_mask);
	return IRQ_HANDLED;
}

static irqreturn_t tz3000_pcie_port1_interrupt(int irq, void *dev_id)
{
	u32 res_mask, res_status;
	u32 int_status;

	pr_debug("PCIe port1 Interrupt Handler called\n");

	/* Get interrupt status */
	res_status = pcie_reg_read(STMA_PORT_INT1);

	/* Mask interrupt */
	res_mask = pcie_reg_read(STMA_PORT_INT1_MSK);
	pcie_reg_write(STMA_PORT_INT1_MSK, 0xffffffff);

	pr_debug("PCIE port1 Interrupt (irq %d)\n", irq);
	pr_debug("PCIE port1 Interrupt status : 0x%08x\n", res_status);
	pr_debug("PCIE port1 Interrupt mask   : 0x%08x\n", res_mask);

	/* not implemented yet */

	if (res_status & STMA_RC_INTERNAL_INT_RES) {
		int_status = pcie_reg_read(STMA_RC_INTERNAL_INT);
		pcie_reg_write(STMA_RC_INTERNAL_INT, int_status);
		pr_debug("RC's Internal interrupt : 0x%08x\n", int_status);
	}
	if (res_status & STMA_MAC_INFORM_INT_RES) {
		int_status = pcie_reg_read(STMA_MAC_INFORM_INT);
		pcie_reg_write(STMA_MAC_INFORM_INT, int_status);
		pr_debug("MAC Interrupt Status : 0x%08x\n", int_status);
	}
	if (res_status & STMA_RECEIVE_MSG_INT_RES) {
		int_status = pcie_reg_read(STMA_RECEIVE_MSG);
		pcie_reg_write(STMA_RECEIVE_MSG, int_status);
		pr_debug("Inform Receiving Message : 0x%08x\n", int_status);
	}
	if (res_status & STMA_POWER_INFORM_INT_RES) {
		int_status = pcie_reg_read(STMA_POWER_INFORM_INT);
		pcie_reg_write(STMA_POWER_INFORM_INT, int_status);
		pr_debug("POWER Interrupt Status : 0x%08x\n", int_status);
	}
	if (res_status & STMA_VC_VALID_INT_RES) {
		int_status = pcie_reg_read(STMA_VC_VALID_INT);
		pcie_reg_write(STMA_VC_VALID_INT, int_status);
		pr_debug("Virtual Channel Valid : 0x%08x\n", int_status);
	}
	if (res_status & STMA_VC0_MAXI_ERR_DET_RES) {
		int_status = pcie_reg_read(STMA_VC0_MAXI_ERR);
		pcie_reg_write(STMA_VC0_MAXI_ERR, int_status);
		pr_debug("Error On AXI Master : 0x%08x\n", int_status);
	}
	if (res_status & STMA_VC0_SAXI_ERR_DET_RES) {
		int_status = pcie_reg_read(STMA_VC0_AXIW_ERR);
		pcie_reg_write(STMA_VC0_AXIW_ERR, int_status);
		if (int_status)
			pr_debug("Error On AXI Slave Write : 0x%08x\n",
				 int_status);

		int_status = pcie_reg_read(STMA_VC0_AXIR_ERR);
		pcie_reg_write(STMA_VC0_AXIR_ERR, int_status);
		if (int_status)
			pr_debug("Error On AXI Slave Read : 0x%08x\n",
				 int_status);
	}

	/* this function is not implemented in TZ3000 */
	if (res_status & STMA_VC0_INTERNAL_ERR_DET_RES) {
		int_status = pcie_reg_read(STMA_VC0_INTEGRITY_ERR);
		pcie_reg_write(STMA_VC0_INTEGRITY_ERR, int_status);
		pr_debug("Uncorrectable Error status : 0x%08x\n", int_status);
	}

	/* clear interrupt */
	pcie_reg_write(STMA_PORT_INT1, res_status);

	/* Enable interrupt */
	pcie_reg_write(STMA_PORT_INT1_MSK, res_mask);
	return IRQ_HANDLED;
}

static irqreturn_t tz3000_pcie_port2_interrupt(int irq, void *dev_id)
{
	u32 res_mask, res_status;

	pr_debug("PCIe port2 Interrupt Handler called\n");

	/* Get interrupt status */
	res_status = pcie_reg_read(STMA_PORT_INT2);

	/* Mask interrupt */
	res_mask = pcie_reg_read(STMA_PORT_INT2_MSK);
	pcie_reg_write(STMA_PORT_INT2_MSK, 0xffffffff);

	pr_debug("PCIE port2 Interrupt (irq %d)\n", irq);
	pr_debug("PCIE port2 Interrupt status : 0x%08x\n", res_status);
	pr_debug("PCIE port2 Interrupt mask   : 0x%08x\n", res_mask);

	/* clear interrupt */
	pcie_reg_write(STMA_PORT_INT2, res_status);

	/* Enable interrupt */
	pcie_reg_write(STMA_PORT_INT2_MSK, res_mask);
	return IRQ_HANDLED;
}

/**
 * tz3000_pcibios_init - pci setup routine
 */
static int tz3000_pcibios_init(bool first_init)
{
	u32 val;

	tz3000_pci_device_reset(0);

	if (first_init) {
		tz3000_pcie_reg_base =
			ioremap(TZ3000_PCI_REG_BASE, TZ3000_PCI_REG_SIZE);
		if (tz3000_pcie_reg_base == NULL) {
			release_mem_region(TZ3000_PCI_REG_BASE,
					   TZ3000_PCI_REG_SIZE);
			return -EBUSY;
		}
		pr_debug("PCIe: RegBase=%p\n", tz3000_pcie_reg_base);
	}

	/* Disable all interrupt */
	pcie_reg_write(STMA_PINT0_INT_MSK, ~0x0);
	pcie_reg_write(STMA_PORT_INT1_MSK, ~0x0);
	pcie_reg_write(STMA_PORT_INT2_MSK, ~0x0);

	/* SW_Set_Reg_PHY Task */
	pcie_reg_write(IPC_PHY_CFGOUT, 0x0);

	/* SW_Set_Reg_IPC_{RCMODE, VC_EXIST, FUNC_EXIST} Task */
	pcie_reg_write(IPC_IP_MODE, IP_MODE_RC);

	/* SW_Set_Reg_IPC_TAMAP Task */
	/* Set access window from system bus to pcie bus */

	/*  RANGE00 : target address map */
	pcie_reg_write(IPC_RANGE00_UP_OFFSET, 0x00000000);

	val = (IPC_OFFSET_ADR_DW(TZ3000_PCI_MEM_RESOURCE_BASE) | IPC_OFFSET_EN);
	pcie_reg_write(IPC_RANGE00_EN, val);

	pcie_reg_write(IPC_RANGE00_UP_RPLC, 0x00000000);

	val = (IPC_OFFSET_REPLACE_DW(TZ3000_PCI_MEM_RESOURCE_BASE) |
	       IPC_OFFSET_TC(0) |
	       IPC_OFFSET_OW(pcie_get_ow(TZ3000_PCI_MEM_RESOURCE_SIZE)));
	pcie_reg_write(IPC_RANGE00_WIDTH, val);

	/* SW_Set_Reg_AMAC Task */

	/* SW_Set_Reg_AMAC_NFTS_SeparateSource Task */
	pcie_reg_write(MACC_NFTS_SREF_CTRL, MACC_NFTS_SREF_CTRL_WVAL);

	/* SW_Set_Reg_AMAC_NFTS_CommonSource Task */
	pcie_reg_write(MACC_NFTS_CREF_CTRL, MACC_NFTS_CREF_CTRL_WVAL);

	/* SW_Set_Reg_AMAC_L1Exit_Latency Task */
	pcie_reg_write(MACC_L1EXITLTCY_CTRL, MACC_L1EXITLTCY_CTRL_WVAL);

	/* SW_Set_Reg_AMAC_TxCommon_Timeout Task */
	pcie_reg_write(MACC_TXCOMMON_TO_CTRL, MACC_TXCOMMON_TO_CTRL_WVAL);

	/* SW_Set_Reg_AMAC_PHY-PIPE_Operating_Mode & _EIDLY Task */
	pcie_reg_write(MACC_PHYPIPE_INFO, MACC_PHYPIPE_INFO_WVAL);

	/* wait 500msec for reset */
	if (!first_init)
		mdelay(500);

	/* Boot PHY PLL */
	if (pcie_boot_phypll())
		return -1;

	/* TZ3000 PCIeC workaround */
	pcie_reg_write(0x8200, 0x00120123);

	/* Errata : ASPM L0s Not Supported */
	val = pcie_reg_read(PBSC_LINK_CAPA);
	pcie_reg_write(PBSC_LINK_CAPA, val & ~0x00000400);

	/* Errata : mask Receiver Error to avoid false-detect */
	val = pcie_reg_read(PCFG_AER_BASE + PCI_ERR_COR_MASK);
	pcie_reg_write(PCFG_AER_BASE + PCI_ERR_COR_MASK,
		       val | PCI_ERR_COR_RCVR);

	/* SW_Set_Reg_PBSC Task */
	val = (PBSC_BS_CFG_VENDOR_ID(TZ3000_PCI_VENDOR_ID) |
	       PBSC_BS_CFG_DEVICE_ID(TZ3000_PCI_DEVICE_ID));
	pcie_reg_write(PBSC_VENDOR_ID, val);

	val = (PBSC_BS_CFG_CLASS_CODE(TZ3000_PCI_CLASS_CODE) |
	       PBSC_BS_CFG_REVID(TZ3000_PCI_REVISION_ID));
	pcie_reg_write(PBSC_REVISION_ID, val);

	/* SW_Set_Reg_PBSC_FUNC_READY Task */
	pcie_reg_write(PBSC_FUNC_READY, PBSC_BS_FUNC_READY);

	/* SW_Set_Reg_PMAC_RC_AutoChgGen Task */
	pcie_reg_write(PMACC_RATE_CHG_CTRL, PMACC_RG_PP_RATECHGENA);

	/* wait VC_VALID_INT (Link Up) */
	if (pcie_wait_vc_valid()) {
		pr_info("PCIe: change data rate to 2.5 GT/s\n");

		pcie_reg_write(PMACC_PCLK_SYNC_RST, PMACC_PCLK_SYNC_RST_RESET);

		val = pcie_reg_read(PBSC_LINK_CAPA) & ~PBSC_BS_CFG_MAX_LNK_SPD;
		val |= PBSC_BS_CFG_MAX_LNK_SPD_2_5GT;
		pcie_reg_write(PBSC_LINK_CAPA, val);

		if (pcie_wait_vc_valid()) {
			pcie_reg_write(PMACC_PCLK_SYNC_RST,
				       PMACC_PCLK_SYNC_RST_RESET);

			tz3000_pci_device_reset(1);
			mdelay(1);

			tz3000_pci_device_reset(0);
			mdelay(1);

			pr_info("PCIe: reset End Point\n");

			if (pcie_wait_vc_valid()) {
				pr_info("PCIe NG (link up time out)\n");
				return -1;
			}
		}
	}

	pr_debug("pciid: 0x%08x\n", pcie_reg_read(PCFG_PCIID));

	/* Setup PCI access mapping */
	pcie_set_mapping();

	/* Start pcieip */
	if (pcie_start_pcieip())
		return -1;

	/* Setup RC config */
	pcie_config_pcierc();

	if (first_init) {
		/* Setup IRQ */
		if (request_irq(IRQ_PCIEPORT(0), tz3000_pcie_port0_interrupt,
				IRQF_SHARED, "pcie port0", (void *)1))
			return -1;
		if (request_irq(IRQ_PCIEPORT(1), tz3000_pcie_port1_interrupt,
				IRQF_SHARED, "pcie port1", (void *)1))
			return -1;
		if (request_irq(IRQ_PCIEPORT(2), tz3000_pcie_port2_interrupt,
				IRQF_SHARED, "pcie port2", (void *)1))
			return -1;
	}

	/* port0 int : enable all */
	pcie_reg_write(STMA_PINT0_INT_MSK, 0x0);

	/* port1 int : enable all */
	pcie_reg_write(STMA_PORT_INT1_MSK, 0x0);

	/* port2 int : RC does not need to use port2 */
	pcie_reg_write(STMA_PORT_INT2_MSK, ~0x0);
	return 0;
}

static int pcie_write_rcconfig(unsigned int regno, int byte_enable, u32 val)
{
	u32 rdata, mask;
	const u32 mask_tbl[] = {	/* byte enable */
		0xffffffff,		/* 0000b */
		0xffffff00,		/* 0001b */
		0xffff00ff,		/* 0010b */
		0xffff0000,		/* 0011b */
		0xff00ffff,		/* 0100b */
		0xff00ff00,		/* 0101b */
		0xff0000ff,		/* 0110b */
		0xff000000,		/* 0111b */
		0x00ffffff,		/* 1000b */
		0x00ffff00,		/* 1001b */
		0x00ff00ff,		/* 1010b */
		0x00ff0000,		/* 1011b */
		0x0000ffff,		/* 1100b */
		0x0000ff00,		/* 1101b */
		0x000000ff,		/* 1110b */
		0x00000000		/* 1111b */
	};

	if (byte_enable == 0xf) {
		pcie_reg_write(regno, val);
	} else {
		/* need to do "read modify write" */
		/* APB I/F does not have Byte Enable Control Signal */
		mask = mask_tbl[byte_enable];

		/* need to unmask W1C register */
		if ((regno == (PCI_STATUS & ~0x3)) ||
		    (regno == (PCI_SEC_STATUS & ~0x3)) ||
		    (regno == ((PCFG_EXP_BASE + PCI_EXP_LNKSTA) & ~0x3))) {
			if (!(byte_enable & 0x8))
				mask &= 0x00ffffff;
		} else if ((regno ==
			    ((PCFG_EXP_BASE + PCI_EXP_DEVSTA) & ~0x3)) ||
			   (regno ==
			       ((PCFG_EXP_BASE + PCI_EXP_RTSTA) & ~0x3)) ||
			   (regno ==
			       ((PCFG_EXP_BASE + PCI_EXP_LNKCTL2) & ~0x3))) {
			if (!(byte_enable & 0x4))
				mask &= 0xff00ffff;
		} else if (regno ==
			   ((PCFG_AER_BASE + PCI_ERR_UNCOR_STATUS) & ~0x3)) {
			if (!(byte_enable & 0x1))
				mask &= 0xffffff00;
			if (!(byte_enable & 0x2))
				mask &= 0xffff00ff;
			if (!(byte_enable & 0x4))
				mask &= 0xff00ffff;
			if (!(byte_enable & 0x8))
				mask &= 0x00ffffff;
		} else if (regno ==
			   ((PCFG_AER_BASE + PCI_ERR_COR_STATUS) & ~0x3)) {
			if (!(byte_enable & 0x1))
				mask &= 0xffffff00;
			if (!(byte_enable & 0x2))
				mask &= 0xffff00ff;
		} else if (regno ==
			   ((PCFG_AER_BASE + PCI_ERR_ROOT_STATUS) & ~0x3)) {
			if (!(byte_enable & 0x1))
				mask &= 0xffffff00;
		}
		rdata = pcie_reg_read(regno);
		pcie_reg_write(regno, (rdata & mask) | val);
	}
	return 0;
}

static int pcie_read_rcconfig(unsigned int regno, u32 *val)
{
	*val = pcie_reg_read(regno);
	return 0;
}

static int pcie_read_epconfig(unsigned int busno, unsigned int devfn,
			      unsigned int regno, int byte_enable, u32 *val)
{
	int timeout;

	pcie_reg_write(APCFG_TLP_HED0, APCFG_TLP_HED0_CFGRD0);
	pcie_reg_write(APCFG_TLP_HED1,
		       (APCFG_TLP_REQID(0) | APCFG_TLP_FDWBE(byte_enable)));
	pcie_reg_write(APCFG_TLP_HED2, (APCFG_TLP_HED2_D(busno, devfn, regno)));
	pcie_reg_write(APCFG_ACC_KICK, APCFG_TLP_KICK);

	timeout = 1000000; /* 1 sec */
	while (--timeout) {
		if (!(pcie_reg_read(APCFG_ACC_BUSY) & APCFG_ACC_BUSY_BUSY))
			break;
		udelay(1);
	}
	if (!timeout) {
		pr_err("PCIE RC: Config Read Request Timeout\n");
		*val = 0xffffffff;
		return -1;
	}

	if (pcie_reg_read(APCFG_ACC_BUSY) & APCFG_ACC_BUSY_ERR) {
		pr_err("PCIE RC: Config Read Request Error\n");
		*val = 0xffffffff;
		return -1;
	}
	*val = __fswab32(pcie_reg_read(APCFG_ACC_RDATA));
	return 0;
}

static int pcie_write_epconfig(unsigned int busno, unsigned int devfn,
			       unsigned int regno, int byte_enable, u32 val)
{
	int timeout;

	pcie_reg_write(APCFG_TLP_HED0, APCFG_TLP_HED0_CFGWR0);
	pcie_reg_write(APCFG_TLP_HED1, (APCFG_TLP_REQID(0) |
					APCFG_TLP_FDWBE(byte_enable)));
	pcie_reg_write(APCFG_TLP_HED2, (APCFG_TLP_HED2_D(busno, devfn, regno)));
	pcie_reg_write(APCFG_TLP_DAT, __fswab32(val));
	pcie_reg_write(APCFG_ACC_KICK, APCFG_TLP_KICK);

	timeout = 1000000; /* 1 sec */
	while (--timeout) {
		if (!(pcie_reg_read(APCFG_ACC_BUSY) & APCFG_ACC_BUSY_BUSY))
			break;
		udelay(1);
	}
	if (!timeout) {
		pr_err("PCIE RC: Config Write Request Timeout\n");
		return -1;
	}

	if (pcie_reg_read(APCFG_ACC_BUSY) & APCFG_ACC_BUSY_ERR) {
		pr_info("PCIE RC: Config Write Request Error\n");
		return -1;
	}
	return 0;
}

static int check_restriction(unsigned int bus, unsigned int dev_fn)
{
	/* rc config access restriction */
	if ((bus == 0) && (dev_fn != 0))
		return -1;

	/* ep config access restriction */
	if ((bus == 0x1) && (PCI_SLOT(dev_fn) != 0))
		return -1;
	return 0;
}

/**
 * tz3000_pcibios_config_read - read function for PCI configuration register
 * @bus: PCI bus structure
 * @devfn: device & function index
 * @where: register number
 * @size: number of byte to read
 * @val: buffer of read data
 */
static int tz3000_pcibios_config_read(struct pci_bus *bus, unsigned int devfn,
				      int where, int size, u32 *val)
{
	int offset, byte_en;
	unsigned int busno, regno;
	int err;

	regno = where & ~0x3;
	offset = where & 0x3;

	/* check if the bus is top-level */
	if (bus->parent != NULL)
		busno = bus->number;
	else
		busno = 0;

	/* check config access restriction */
	if (check_restriction(busno, devfn)) {
		*val = 0xffffffff;
		return PCIBIOS_DEVICE_NOT_FOUND;
	}

	byte_en = ((1 << size) - 1) << offset;
	if (byte_en > 0xf || byte_en == 0) {
		pr_err("PCIE RC: Unexpected Config Read Request\n");
		*val = 0xffffffff;
		return -1;	/* error */
	}

	if (busno == 0)
		err = pcie_read_rcconfig(regno, val);
	else
		err = pcie_read_epconfig(busno, devfn, regno, byte_en, val);

	if (err) {
		*val = 0xffffffff;
		return PCIBIOS_DEVICE_NOT_FOUND;
	}

	*val >>= offset * 8;
	return PCIBIOS_SUCCESSFUL;
}

/**
 * tz3000_pcibios_config_write - write function for PCI configuration register
 * @bus: PCI bus structure
 * @devfn: device & function index
 * @where: register number
 * @size: number of byte to write
 * @val: write data
 */
static int tz3000_pcibios_config_write(struct pci_bus *bus, unsigned int devfn,
				       int where, int size, u32 val)
{
	int offset, byte_en;
	unsigned int busno, regno;
	int err;

	regno = where & ~0x3;
	offset = where & 0x3;

	/* check if the bus is top-level */
	if (bus->parent != NULL)
		busno = bus->number;
	else
		busno = 0;

	/* check config access restriction */
	if (check_restriction(busno, devfn))
		return PCIBIOS_DEVICE_NOT_FOUND;

	byte_en = ((1 << size) - 1) << offset;
	if (byte_en > 0xf || byte_en == 0) {
		pr_err("PCIE RC: Unexpected Config Write Request\n");
		return -1;	/* error */
	}

	val <<= offset * 8;

	if (busno == 0)
		err = pcie_write_rcconfig(regno, byte_en, val);
	else
		err = pcie_write_epconfig(busno, devfn, regno, byte_en, val);

	if (err)
		return PCIBIOS_DEVICE_NOT_FOUND;
	return PCIBIOS_SUCCESSFUL;
}

/**
 * tz3000_pci_map_irq - map suitable IRQ onto a slot and a pin
 * @dev: pci_bus device
 * @slot: slot number
 * @pin: pin number
 */
static int __init tz3000_pci_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	if (WARN_ON(pin == 0 || pin > 4))
		return -1;
	else if (dev->bus->parent)
		return IRQ_PCIEINTX(pin - 1);
	else
		return IRQ_PCIEPORT(1); /* for portdrv */
}

/* initialize in setup */
static struct pci_ops tz3000_pci_ops = {
	.read = tz3000_pcibios_config_read,
	.write = tz3000_pcibios_config_write
};

static struct resource tz3000_pci_mem_resource = {
	.name = "PCI MEM",
	.start = TZ3000_PCI_MEM_RESOURCE_BASE,
	.end = TZ3000_PCI_MEM_RESOURCE_BASE + TZ3000_PCI_MEM_RESOURCE_SIZE - 1,
	.flags = IORESOURCE_MEM,
};

static int __init tz3000_pci_setup(int nr, struct pci_sys_data *sys)
{
	int ret;

	ret = tz3000_pcibios_init(true);
	if (ret < 0)
		return ret;

	ret = request_resource(&iomem_resource, &tz3000_pci_mem_resource);
	if (ret) {
		pr_err("PCI: unable to allocate non-prefetchable memory region (%d)\n",
		       ret);
		return ret;
	}
	pci_add_resource_offset(&sys->resources,
				&tz3000_pci_mem_resource, sys->mem_offset);
	return 1;
}

static struct pci_bus * __devinit
tz3000_pci_scan_bus(int nr, struct pci_sys_data *sys)
{
	return pci_scan_root_bus(NULL, sys->busnr, &tz3000_pci_ops, sys,
				 &sys->resources);
}

static struct hw_pci tz3000_pci __initdata = {
	.swizzle		= pci_std_swizzle,
	.map_irq		= tz3000_pci_map_irq,
	.nr_controllers		= 1,
	.setup			= tz3000_pci_setup,
	.scan			= tz3000_pci_scan_bus,
};

#ifdef CONFIG_PM_SLEEP
static int tz3000_pci_suspend(void)
{
	pr_debug("%s\n", __func__);
	pr_debug("PCIe: assert reset\n");
	tz3000_pci_device_reset(1);
	return 0;
}

static void tz3000_pci_resume(void)
{
	pr_debug("%s\n", __func__);
	tz3000_pcibios_init(false);
}

static struct syscore_ops tz3000_pci_pm_syscore_ops = {
	.suspend = tz3000_pci_suspend,
	.resume = tz3000_pci_resume,
};
#endif

static int __init tz3000_pci_init(void)
{
	if (machine_is_tz3000eva()) {
		/* check hsio setting */
		if (gpio_get_value(7) == 0) {
			/* Disable or USB3H */
			pr_info("PCI: disabled\n");
			return -1;
		}
		/* PCIe + USB2D or PCIe + USB3H(HS) */
		pci_reset_gpio = 55;
	} else if (machine_is_tz3000rb()) {
		pci_reset_gpio = 55;
	} else {
		return -1;
	}

	pcibios_min_io = 0;
	pcibios_min_mem = TZ3000_PCI_MEM_RESOURCE_BASE;
#ifdef CONFIG_PCIEPORTBUS
	/* pcie_ports_auto should be disabled for non ACPI platform */
	pcie_ports_auto = false;
#endif

	pci_common_init(&tz3000_pci);
#ifdef CONFIG_PM_SLEEP
	if (!no_pci_devices())
		register_syscore_ops(&tz3000_pci_pm_syscore_ops);
#endif
	return 0;
}

subsys_initcall(tz3000_pci_init);
