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
#include <linux/io.h>
#include <linux/syscore_ops.h>
#include <asm/cacheflush.h>
#include <asm/smp_scu.h>
#include <asm/suspend.h>
#include <mach/platform.h>
#include <mach/hardware.h>
#include <mach/smp.h>

#define EMULATE_SUSPEND /* for test */

static int tz3000_suspend_finish(unsigned long val)
{
	flush_cache_all();
	outer_flush_all();
	if (readl(__io_address(TZ3000_SCOMM_BASE + 0x63c)) & 0x100) {
		tz3000_enter_suspend();
		cpu_do_idle();
	}
	return 0;
}

static void __iomem *econf_base;
struct tz3000_saved_regs {
	u32 gconf_pinshare0;
	u32 gconf_pinshare1;
	u32 gconf_pinshare3;
	u32 econf_emmca_cfg_cap0;
	u32 econf_emmca_cfg_cap1;
	u32 econf_usb2phy_config0;
	u32 econf_usb2phy_config1;
	u32 econf_hsio_mux_ctl;
	u32 pmu_plleth0;
	u32 pmu_cgoff_peri1;
	u32 pmu_cgoff_peri3;
	u32 pmu_cgoff_peri4;
	u32 pmu_cgoff_ether;
	u32 pmu_cgoff_emmc;
	u32 pmu_cgoff_nandc;
	u32 pmu_cgoff_hsio;
	u32 pmu_sroff_cpu0;
	u32 pmu_sroff_cpu1;
	u32 pmu_sroff_peri1;
	u32 pmu_sroff_peri3;
	u32 pmu_sroff_peri4;
	u32 pmu_sroff_ether;
	u32 pmu_sroff_emmc;
	u32 pmu_sroff_nandc;
	u32 pmu_sroff_hsio;
};

static void writel_rb(u32 val, void __iomem *reg)
{
	writel(val, reg);
	(void)readl(reg);
}

static void tz3000_save_regs(struct tz3000_saved_regs *regs)
{
	regs->gconf_pinshare0 = readl(__io_address(TZ3000_GCONF_PINSHARE0));
	regs->gconf_pinshare1 = readl(__io_address(TZ3000_GCONF_PINSHARE1));
	regs->gconf_pinshare3 = readl(__io_address(TZ3000_GCONF_PINSHARE3));

	regs->econf_emmca_cfg_cap0 =
		readl(econf_base +
		      (TZ3000_ECONF_EMMC_BASE(0) - TZ3000_ECONF_BASE));
	regs->econf_emmca_cfg_cap1 =
		readl(econf_base +
		      (TZ3000_ECONF_EMMC_BASE(0) - TZ3000_ECONF_BASE) + 8);
	regs->econf_hsio_mux_ctl = readl(econf_base + 0x700);
	regs->econf_usb2phy_config1 = readl(econf_base + 0x610);
	regs->econf_usb2phy_config0 = readl(econf_base + 0x600);

	regs->pmu_plleth0 = readl(__io_address(TZ3000_PMU_PLLETHR_REG));

	regs->pmu_cgoff_peri1 = readl(__io_address(TZ3000_PMU_CGOFF_PERI1));
	regs->pmu_cgoff_peri3 = readl(__io_address(TZ3000_PMU_CGOFF_PERI3));
	regs->pmu_cgoff_peri4 = readl(__io_address(TZ3000_PMU_CGOFF_PERI4));
	regs->pmu_cgoff_ether = readl(__io_address(TZ3000_PMU_CGOFF_ETHER));
	regs->pmu_cgoff_emmc = readl(__io_address(TZ3000_PMU_CGOFF_EMMC));
	regs->pmu_cgoff_nandc = readl(__io_address(TZ3000_PMU_CGOFF_NANDC));
	regs->pmu_cgoff_hsio = readl(__io_address(TZ3000_PMU_CGOFF_HSIO));

	regs->pmu_sroff_cpu0 = readl(__io_address(TZ3000_PMU_SROFF_CPU0));
	regs->pmu_sroff_cpu1 = readl(__io_address(TZ3000_PMU_SROFF_CPU1));
	regs->pmu_sroff_peri1 = readl(__io_address(TZ3000_PMU_SROFF_PERI1));
	regs->pmu_sroff_peri3 = readl(__io_address(TZ3000_PMU_SROFF_PERI3));
	regs->pmu_sroff_peri4 = readl(__io_address(TZ3000_PMU_SROFF_PERI4));
	regs->pmu_sroff_ether = readl(__io_address(TZ3000_PMU_SROFF_ETHER));
	regs->pmu_sroff_emmc = readl(__io_address(TZ3000_PMU_SROFF_EMMC));
	regs->pmu_sroff_nandc = readl(__io_address(TZ3000_PMU_SROFF_NANDC));
	regs->pmu_sroff_hsio = readl(__io_address(TZ3000_PMU_SROFF_HSIO));

	/* stop clock before soft reset */
	writel_rb(0x03, __io_address(TZ3000_PMU_CGON_EMMC));
	udelay(1);

	/* soft reset */
	writel_rb(0x03030311, __io_address(TZ3000_PMU_SRON_HSIO));
	writel_rb(0x00000011, __io_address(TZ3000_PMU_SRON_ETHER));
	writel_rb(0x00000001, __io_address(TZ3000_PMU_SRON_EMMC));
	writel_rb(0x00000101, __io_address(TZ3000_PMU_SRON_NANDC));
	/* SoftResetOn_periSS_1 (i2c,gpio) */
	writel_rb(0x01110000, __io_address(TZ3000_PMU_SRON_PERI1));
	/* SoftResetOn_periSS_3 (spib,spims) */
	writel_rb(0x01000111, __io_address(TZ3000_PMU_SRON_PERI3));
	/* SoftResetOn_periSS_4 (uart) */
	writel_rb(0x00111101, __io_address(TZ3000_PMU_SRON_PERI4));
	udelay(1);

	/* start clock again */
	writel_rb(regs->pmu_cgoff_emmc, __io_address(TZ3000_PMU_CGOFF_EMMC));
	udelay(1 + 10 * 16); /* 1us + at least 16 hck cycle (at min. 100KHz) */

	/* clock off */
	writel(0x03030311, __io_address(TZ3000_PMU_CGON_HSIO));
	writel(0x00000001, __io_address(TZ3000_PMU_CGON_ETHER));
	writel(0x00000003, __io_address(TZ3000_PMU_CGON_EMMC));
	writel(0x00000101, __io_address(TZ3000_PMU_CGON_NANDC));
	/* ClockGatingOff_periSS_1 (i2c,gpio) */
	writel(0x01110000, __io_address(TZ3000_PMU_CGON_PERI1));
	/* ClockGatingOff_periSS_3 (spib,spims) */
	writel(0x01000111, __io_address(TZ3000_PMU_CGON_PERI3));
	/* ClockGatingOff_periSS_4 (uart) */
	writel(0x00111101, __io_address(TZ3000_PMU_CGON_PERI4));
}

static void tz3000_restore_regs(struct tz3000_saved_regs *regs)
{
	void __iomem *reg;

	writel(regs->pmu_cgoff_peri1, __io_address(TZ3000_PMU_CGOFF_PERI1));
	writel(regs->pmu_cgoff_peri3, __io_address(TZ3000_PMU_CGOFF_PERI3));
	writel(regs->pmu_cgoff_peri4, __io_address(TZ3000_PMU_CGOFF_PERI4));
	writel(regs->pmu_cgoff_ether, __io_address(TZ3000_PMU_CGOFF_ETHER));
	writel(regs->pmu_cgoff_emmc, __io_address(TZ3000_PMU_CGOFF_EMMC));
	writel(regs->pmu_cgoff_nandc, __io_address(TZ3000_PMU_CGOFF_NANDC));

	writel(regs->gconf_pinshare0, __io_address(TZ3000_GCONF_PINSHARE0));
	writel(regs->gconf_pinshare1, __io_address(TZ3000_GCONF_PINSHARE1));
	writel(regs->gconf_pinshare3, __io_address(TZ3000_GCONF_PINSHARE3));

	writel(regs->econf_emmca_cfg_cap0,
	       econf_base + (TZ3000_ECONF_EMMC_BASE(0) - TZ3000_ECONF_BASE));
	writel(regs->econf_emmca_cfg_cap1,
	       econf_base + (TZ3000_ECONF_EMMC_BASE(0) - TZ3000_ECONF_BASE)
	       + 8);

	writel(regs->pmu_cgoff_hsio, __io_address(TZ3000_PMU_CGOFF_HSIO));

	writel(regs->econf_usb2phy_config0, econf_base + 0x600);
	writel(regs->econf_usb2phy_config1, econf_base + 0x610);
	writel(regs->econf_hsio_mux_ctl, econf_base + 0x700);

	writel(regs->pmu_sroff_cpu0, __io_address(TZ3000_PMU_SROFF_CPU0));
	writel(regs->pmu_sroff_cpu1, __io_address(TZ3000_PMU_SROFF_CPU1));
	writel(regs->pmu_sroff_peri1, __io_address(TZ3000_PMU_SROFF_PERI1));
	writel(regs->pmu_sroff_peri3, __io_address(TZ3000_PMU_SROFF_PERI3));
	writel(regs->pmu_sroff_peri4, __io_address(TZ3000_PMU_SROFF_PERI4));
	writel(regs->pmu_sroff_ether, __io_address(TZ3000_PMU_SROFF_ETHER));
	writel(regs->pmu_sroff_emmc, __io_address(TZ3000_PMU_SROFF_EMMC));
	writel(regs->pmu_sroff_nandc, __io_address(TZ3000_PMU_SROFF_NANDC));

	reg = __io_address(TZ3000_PMU_SROFF_HSIO);
	writel(regs->pmu_sroff_hsio & 0x00000200, reg);
	udelay(1);
	writel(regs->pmu_sroff_hsio & 0x03030201, reg);
	udelay(225);
	writel(regs->pmu_sroff_hsio & 0x03030211, reg);
	udelay(1);
	writel(regs->pmu_sroff_hsio & 0x03030311, reg);

	/* restore RESET/PD/BP */
	writel(regs->pmu_plleth0 & 0x7, __io_address(TZ3000_PMU_PLLETHR_REG));
}

static struct tz3000_saved_regs saved_regs;

static int tz3000_suspend(void)
{
	tz3000_save_regs(&saved_regs);
	return 0;
}

static void tz3000_resume(void)
{
#ifdef CONFIG_SMP
	scu_enable(__io_address(TZ3000_CPU_BASE));
#endif
#ifdef CONFIG_CACHE_L2X0
	tz3000_pl310_init();
#endif
	tz3000_restore_regs(&saved_regs);
#if IS_ENABLED(CONFIG_APPLITE_IRECOG)
	init_irecog();
#endif
	tz3000_setup_gdmac();
}

static struct syscore_ops tz3000_pm_syscore_ops = {
	.resume = tz3000_resume,
	.suspend = tz3000_suspend,
};

static int __init tz3000_pm_syscore_init(void)
{
	register_syscore_ops(&tz3000_pm_syscore_ops);
	return 0;
}
postcore_initcall(tz3000_pm_syscore_init);

static int tz3000_pm_enter(suspend_state_t state)
{
	int i;

	/* set resume entry point for secondary cpus */
	/* do not use CONFIG_NR_CPUS, etc. for non-SMP build */
	for (i = 1; i < 4; i++)
		__raw_writel(virt_to_phys(tz3000_secondary_resume),
			     __io_address(TZ3000_SYS_FLAGSSET + (0x4 * i)));
	/* boot_secondary() will overwrite the entry point */
	writel(virt_to_phys(v7_cpu_resume), __io_address(TZ3000_SYS_FLAGSSET));

	/* Enter shut-down */
	cpu_suspend(0, tz3000_suspend_finish);
	cpu_init();
	return 0;
}

static const struct platform_suspend_ops tz3000_pm_ops = {
	.enter	= tz3000_pm_enter,
	.valid	= suspend_valid_only_mem,
};

static int __init tz3000_pm_init(void)
{
	econf_base = ioremap(TZ3000_ECONF_BASE, SZ_4K);
	suspend_set_ops(&tz3000_pm_ops);
	return 0;
}
arch_initcall(tz3000_pm_init);
