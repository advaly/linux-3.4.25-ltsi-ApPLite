/*
 * Copyright (C) 2010 Toshiba Corporation
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

#include <linux/suspend.h>
#include <linux/module.h>
#include <linux/io.h>
#include <linux/syscore_ops.h>
#include <asm/cacheflush.h>
#include <asm/suspend.h>
#include <mach/hardware.h>
#include <mach/platform.h>
#include <mach/regs/cpu_memmap_def.h>
#include <mach/regs/pmu_reg_def.h>

static int tz2000_suspend_finish(unsigned long val)
{
	flush_cache_all();
	if (readl(__io_address(TZ2000_SCOMM_BASE + 0x63c)) & 0x100) {
		tz2000_enter_suspend();
		cpu_do_idle();
	}
	return 0;
}

static void __iomem *wconf_base;
struct tz2000_saved_regs {
	u32 gconf_pinshare0;
	u32 gconf_pinshare1;
	u32 wconf_emmc0_cfg_cap;
	u32 wconf_emmc1_cfg_cap;
	u32 wconf_usb2phy_config0;
	u32 wconf_usb2phy_config1;
	u32 wconf_usb2hd_mux_ctl;
	u32 wconf_usb2hd_refclk;
	u32 pmu_cgoff_peri1;
	u32 pmu_cgoff_peri3;
	u32 pmu_cgoff_peri4;
	u32 pmu_cgoff_ether;
	u32 pmu_cgoff_emmc;
	u32 pmu_cgoff_telomere;
	u32 pmu_cgoff_usb2hd;
	u32 pmu_sroff_peri1;
	u32 pmu_sroff_peri3;
	u32 pmu_sroff_peri4;
	u32 pmu_sroff_ether;
	u32 pmu_sroff_emmc;
	u32 pmu_sroff_telomere;
	u32 pmu_sroff_usb2hd;
	u32 pmu_poren;
};

static void writel_rb(u32 val, void __iomem *reg)
{
	writel(val, reg);
	(void)readl(reg);
}

static void tz2000_save_regs(struct tz2000_saved_regs *regs)
{
	void __iomem *reg;
	unsigned long val;
	int internal_nand_mode;

	regs->gconf_pinshare0 = readl(__io_address(TZ2000_GCONF_PINSHARE0));
	regs->gconf_pinshare1 = readl(__io_address(TZ2000_GCONF_PINSHARE1));

	regs->wconf_emmc0_cfg_cap =
		readl(wconf_base +
		      (TZ2000_WCONF_EMMC_BASE(0) - TZ2000_WCONF_BASE));
	regs->wconf_emmc1_cfg_cap =
		readl(wconf_base +
		      (TZ2000_WCONF_EMMC_BASE(1) - TZ2000_WCONF_BASE));
	internal_nand_mode = (regs->wconf_emmc1_cfg_cap & 0x00040000) != 0;
	regs->wconf_usb2hd_mux_ctl = readl(wconf_base + 0x700);
	regs->wconf_usb2hd_refclk = readl(wconf_base + 0x704);
	regs->wconf_usb2phy_config1 = readl(wconf_base + 0x610);
	regs->wconf_usb2phy_config0 = readl(wconf_base + 0x600);

	regs->pmu_cgoff_peri1 = readl(__io_address(TZ2000_PMU_CGOFF_PERI1));
	regs->pmu_cgoff_peri3 = readl(__io_address(TZ2000_PMU_CGOFF_PERI3));
	regs->pmu_cgoff_peri4 = readl(__io_address(TZ2000_PMU_CGOFF_PERI4));
	regs->pmu_cgoff_ether = readl(__io_address(TZ2000_PMU_CGOFF_ETHER));
	regs->pmu_cgoff_emmc = readl(__io_address(TZ2000_PMU_CGOFF_EMMC));
	regs->pmu_cgoff_telomere =
		readl(__io_address(TZ2000_PMU_CGOFF_TELOMERE));
	regs->pmu_cgoff_usb2hd = readl(__io_address(TZ2000_PMU_CGOFF_USB2HD));

	regs->pmu_sroff_peri1 = readl(__io_address(TZ2000_PMU_SROFF_PERI1));
	regs->pmu_sroff_peri3 = readl(__io_address(TZ2000_PMU_SROFF_PERI3));
	regs->pmu_sroff_peri4 = readl(__io_address(TZ2000_PMU_SROFF_PERI4));
	regs->pmu_sroff_ether = readl(__io_address(TZ2000_PMU_SROFF_ETHER));
	regs->pmu_sroff_emmc = readl(__io_address(TZ2000_PMU_SROFF_EMMC));
	regs->pmu_sroff_telomere =
		readl(__io_address(TZ2000_PMU_SROFF_TELOMERE));
	regs->pmu_sroff_usb2hd = readl(__io_address(TZ2000_PMU_SROFF_USB2HD));

	/* stop clock before soft reset */
	writel_rb(0x03, __io_address(TZ2000_PMU_CGON_EMMC));
	if (internal_nand_mode)
		writel_rb(0x030111, __io_address(TZ2000_PMU_CGON_TELOMERE));
	else
		writel_rb(0x030000, __io_address(TZ2000_PMU_CGON_TELOMERE));
	udelay(1);

	/* soft reset */
	writel_rb(0x00005511, __io_address(TZ2000_PMU_SRON_USB2HD));
	writel_rb(0x00000011, __io_address(TZ2000_PMU_SRON_ETHER));
	writel_rb(0x00000001, __io_address(TZ2000_PMU_SRON_EMMC));
	if (internal_nand_mode)
		writel_rb(0x00030303, __io_address(TZ2000_PMU_SRON_TELOMERE));
	else
		writel_rb(0x00010000, __io_address(TZ2000_PMU_SRON_TELOMERE));
	/* SoftResetOn_periSS_1 (i2c,gpio) */
	writel_rb(0x01110000, __io_address(TZ2000_PMU_SRON_PERI1));
	/* SoftResetOn_periSS_3 (spib,spims) */
	writel_rb(0x01000111, __io_address(TZ2000_PMU_SRON_PERI3));
	/* SoftResetOn_periSS_4 (uart) */
	writel_rb(0x00111101, __io_address(TZ2000_PMU_SRON_PERI4));
	udelay(1);

	/* start clock again */
	writel_rb(regs->pmu_cgoff_emmc, __io_address(TZ2000_PMU_CGOFF_EMMC));
	writel_rb(regs->pmu_cgoff_telomere,
		  __io_address(TZ2000_PMU_CGOFF_TELOMERE));
	udelay(1 + 10 * 16); /* 1us + at least 16 hck cycle (at min. 100KHz) */

	/* Isolation On */
	regs->pmu_poren = readl(__io_address(TZ2000_PMU_POREN));
	val = regs->pmu_poren;
	val &= ~0x80;	/* emmc4sd */
	val &= ~0x40;	/* USB */
	val &= ~0x20;	/* ADC */
	val &= ~(internal_nand_mode ? 0x10 : 0x100);
	writel(val, __io_address(TZ2000_PMU_POREN));
	udelay(internal_nand_mode ? 80 : 1);

	reg = __io_address(TZ2000_PMU_USB_CONTROL); /* VDD33_USB Enable */
	writel(0x00000000, reg);
	udelay(1);
	writel(0x00000004, reg);	/* Set SHUNT_VDD33_USB */
	udelay(1000);

	/* clock off */
	writel(0x00001111, __io_address(TZ2000_PMU_CGON_USB2HD));
	writel(0x00000001, __io_address(TZ2000_PMU_CGON_ETHER));
	writel(0x00000003, __io_address(TZ2000_PMU_CGON_EMMC));
	writel(0x00030000, __io_address(TZ2000_PMU_CGON_TELOMERE));
	/* ClockGatingOff_periSS_1 (i2c,gpio) */
	writel(0x01110000, __io_address(TZ2000_PMU_CGON_PERI1));
	/* ClockGatingOff_periSS_3 (spib,spims) */
	writel(0x01000111, __io_address(TZ2000_PMU_CGON_PERI3));
	/* ClockGatingOff_periSS_4 (uart) */
	writel(0x00111101, __io_address(TZ2000_PMU_CGON_PERI4));
}

static void tz2000_restore_regs(struct tz2000_saved_regs *regs)
{
	void __iomem *reg;

	writel(regs->pmu_cgoff_peri1, __io_address(TZ2000_PMU_CGOFF_PERI1));
	writel(regs->pmu_cgoff_peri3, __io_address(TZ2000_PMU_CGOFF_PERI3));
	writel(regs->pmu_cgoff_peri4, __io_address(TZ2000_PMU_CGOFF_PERI4));
	writel(regs->pmu_cgoff_ether, __io_address(TZ2000_PMU_CGOFF_ETHER));
	writel(regs->pmu_cgoff_emmc, __io_address(TZ2000_PMU_CGOFF_EMMC));
	writel(regs->pmu_cgoff_telomere,
	       __io_address(TZ2000_PMU_CGOFF_TELOMERE));

	writel(regs->gconf_pinshare0, __io_address(TZ2000_GCONF_PINSHARE0));
	writel(regs->gconf_pinshare1, __io_address(TZ2000_GCONF_PINSHARE1));

	writel(regs->wconf_emmc0_cfg_cap,
	       wconf_base + (TZ2000_WCONF_EMMC_BASE(0) - TZ2000_WCONF_BASE));
	writel(regs->wconf_emmc1_cfg_cap,
	       wconf_base + (TZ2000_WCONF_EMMC_BASE(1) - TZ2000_WCONF_BASE));

	writel(regs->pmu_cgoff_usb2hd, __io_address(TZ2000_PMU_CGOFF_USB2HD));

	writel(regs->wconf_usb2phy_config0, wconf_base + 0x600);
	writel(regs->wconf_usb2phy_config1, wconf_base + 0x610);
	writel(regs->wconf_usb2hd_refclk, wconf_base + 0x704);
	writel(regs->wconf_usb2hd_mux_ctl, wconf_base + 0x700);

	/* Isolation Off */
	writel(regs->pmu_poren, __io_address(TZ2000_PMU_POREN));
	udelay(1);

	writel(regs->pmu_sroff_peri1, __io_address(TZ2000_PMU_SROFF_PERI1));
	writel(regs->pmu_sroff_peri3, __io_address(TZ2000_PMU_SROFF_PERI3));
	writel(regs->pmu_sroff_peri4, __io_address(TZ2000_PMU_SROFF_PERI4));
	writel(regs->pmu_sroff_ether, __io_address(TZ2000_PMU_SROFF_ETHER));
	writel(regs->pmu_sroff_emmc, __io_address(TZ2000_PMU_SROFF_EMMC));
	writel(regs->pmu_sroff_telomere,
	       __io_address(TZ2000_PMU_SROFF_TELOMERE));

	reg = __io_address(TZ2000_PMU_USB_CONTROL); /* VDD33_USB Enable */
	udelay(1);
	writel(0x00000000, reg);
	udelay(1);
	writel(0x00000001, reg);	/* Set VDD33_USB weak */
	udelay(100);
	writel(0x00000003, reg);	/* Set VDD33_USB strong */
	udelay(1000);
	reg = __io_address(TZ2000_PMU_SROFF_USB2HD);
	writel(regs->pmu_sroff_usb2hd & 0x00000001, reg);
	udelay(225);
	writel(regs->pmu_sroff_usb2hd & 0x00004401, reg);
	udelay(1);
	writel(regs->pmu_sroff_usb2hd & 0x00005511, reg);
}

static struct tz2000_saved_regs saved_regs;

static int tz2000_suspend(void)
{
	tz2000_save_regs(&saved_regs);
	return 0;
}

static void tz2000_setup_gdmac(void)
{
	writel(BIT(8), __io_address(CPU_PMU_REG_BASE + PMU_CLOCKGATINGOFF_PERISS_0_OFS));
	writel(BIT(8), __io_address(CPU_PMU_REG_BASE + PMU_SOFTRESETOFF_PERISS_0_OFS));
}

static void tz2000_resume(void)
{
	tz2000_restore_regs(&saved_regs);
	tz2000_setup_gdmac();
}

static struct syscore_ops tz2000_pm_syscore_ops = {
	.resume = tz2000_resume,
	.suspend = tz2000_suspend,
};

static int __init tz2000_pm_syscore_init(void)
{
	register_syscore_ops(&tz2000_pm_syscore_ops);
	return 0;
}
postcore_initcall(tz2000_pm_syscore_init);

static int tz2000_pm_enter(suspend_state_t state)
{
#define TZ2000_SYS_FLAGSSET		(TZ2000_MBOOT_BASE + 0x70)
	writel(virt_to_phys(v7_cpu_resume), __io_address(TZ2000_SYS_FLAGSSET));

	/* Enter shut-down */
	cpu_suspend(0, tz2000_suspend_finish);
	cpu_init();
	return 0;
}

static const struct platform_suspend_ops tz2000_pm_ops = {
	.enter	= tz2000_pm_enter,
	.valid	= suspend_valid_only_mem,
};

static int __init tz2000_pm_init(void)
{
	wconf_base = ioremap(TZ2000_WCONF_BASE, SZ_4K);
	suspend_set_ops(&tz2000_pm_ops);
	return 0;
}
arch_initcall(tz2000_pm_init);
