/*
 * sdhci-tz3000.c Support for SDHCI on TZ3000
 * Based on sdhci-dove.c
 *
 * (C) Copyright TOSHIBA CORPORATION
 *      SEMICONDUCTOR & STORAGE PRODUCTS COMPANY 2013
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <linux/delay.h>
#include <linux/err.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/mmc/host.h>
#include <linux/mmc/card.h>
#include <linux/platform_data/sdhci-tz3000.h>

#include "sdhci-pltfm.h"

struct pltfm_tz3000_data {
	u16 clk_on_reset;
	u16 transfer_mode;
	void __iomem *econf_emmc_addr;
	struct platform_device *pdev;
	const struct sdhci_tz3000_ec_tune_param *manual_tune_param;
};

#define EMMC_CTRL_DLYCHG	0x50
#define EMMC_CTRL_INDLY		0x58
#define EMMC_CTRL_OUTDLY	0x60
#define EMMC_CTRL_DLL0		0x68
#define EMMC_CTRL_DLL1		0x70

static void econf_emmc_updatew(struct sdhci_host *host, u16 val, int reg)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct pltfm_tz3000_data *tz3000_data = pltfm_host->priv;
	unsigned long timeout = 1000;

	writel(val, tz3000_data->econf_emmc_addr + reg);
	while (readl(tz3000_data->econf_emmc_addr + reg) !=
	       ((val << 16) | val)) {
		if (timeout == 0) {
			pr_err("%s: %s reg %x val %x timeout.\n",
			       mmc_hostname(host->mmc), __func__, reg, val);
			return;
		}
		timeout--;
		udelay(1);
	}
}

/* use 32bit access for SDHC registers */
static u8 sdhci_tz3000_readb(struct sdhci_host *host, int reg)
{
	return readl(host->ioaddr + (reg & ~3)) >> (8 * (reg & 3));
}

static u16 sdhci_tz3000_readw(struct sdhci_host *host, int reg)
{
	return readl(host->ioaddr + (reg & ~3)) >> (8 * (reg & 3));
}

static void sdhci_tz3000_writeb(struct sdhci_host *host, u8 val, int reg)
{
	int reg32 = reg & ~3;
	u32 val32 = readl(host->ioaddr + reg32);
	unsigned int bitofs = 8 * (reg & 3);
	u32 mask = 0xff << bitofs;
	writel((val << bitofs) | (val32 & ~mask), host->ioaddr + reg32);
}

static void sdhci_tz3000_writew(struct sdhci_host *host, u16 val, int reg)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct pltfm_tz3000_data *tz3000_data = pltfm_host->priv;
	int reg32 = reg & ~3;
	u32 val32 = readl(host->ioaddr + reg32);
	unsigned int bitofs = 8 * (reg & 3);
	u32 mask = 0xffff << bitofs;

	switch (reg) {
	case SDHCI_HOST_CONTROL2:
		/* errata 9.1: do not use "preset value enable" */
		val &= ~SDHCI_CTRL_PRESET_VAL_ENABLE;
		break;
	case SDHCI_TRANSFER_MODE:
		tz3000_data->transfer_mode = val;
		return;
	case SDHCI_COMMAND:
		val32 = tz3000_data->transfer_mode;
		break;
	}
	writel((val << bitofs) | (val32 & ~mask), host->ioaddr + reg32);
	if (reg == SDHCI_CLOCK_CONTROL) {
		/* errata 9.11, 9.12 workaround */
		readl(host->ioaddr + reg32); /* dummy read */
		udelay(10 * 20); /* at least 20 cycle (at minimum 100KHz) */
	}
}

static void sdhci_tz3000_disable_manual_tuning(struct sdhci_host *host);
static void sdhci_tz3000_manual_tuning(struct sdhci_host *host,
				       int otap, int itap, bool usedll);

static void sdhci_tz3000_reset_enter(struct sdhci_host *host, u8 mask)
{
	/* errata 9.3: software reset limitation */
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct pltfm_tz3000_data *tz3000_data = pltfm_host->priv;
	u16 clk;

	if (host->clock == 0 || host->clock >= 25000000)
		return;
	clk = sdhci_readw(host, SDHCI_CLOCK_CONTROL);
	tz3000_data->clk_on_reset = clk;
	if (tz3000_data->manual_tune_param &&
	    (clk & SDHCI_CLOCK_CARD_EN) &&
	    (clk & SDHCI_CLOCK_INT_STABLE))
		sdhci_tz3000_disable_manual_tuning(host);
	if (clk & SDHCI_CLOCK_CARD_EN) {
		clk &= ~SDHCI_CLOCK_CARD_EN;
		sdhci_writew(host, clk, SDHCI_CLOCK_CONTROL);
	}
	if (clk & SDHCI_CLOCK_INT_EN) {
		clk &= ~SDHCI_CLOCK_INT_EN;
		sdhci_writew(host, clk, SDHCI_CLOCK_CONTROL);
	}
}

static void sdhci_tz3000_reset_exit(struct sdhci_host *host, u8 mask)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct pltfm_tz3000_data *tz3000_data = pltfm_host->priv;
	u16 clk;

	if (host->clock == 0 || host->clock >= 25000000)
		return;
	clk = sdhci_readw(host, SDHCI_CLOCK_CONTROL);
	if (tz3000_data->clk_on_reset & SDHCI_CLOCK_INT_EN) {
		unsigned long timeout;

		clk |= SDHCI_CLOCK_INT_EN;
		sdhci_writew(host, clk, SDHCI_CLOCK_CONTROL);
		timeout = 200;
		while (!((clk = sdhci_readw(host, SDHCI_CLOCK_CONTROL))
			 & SDHCI_CLOCK_INT_STABLE)) {
			if (timeout == 0) {
				pr_err("%s: Internal clock never stabilised.\n",
				       mmc_hostname(host->mmc));
				return;
			}
			timeout--;
			mdelay(1);
		}
	}
	if (tz3000_data->clk_on_reset & SDHCI_CLOCK_CARD_EN) {
		clk |= SDHCI_CLOCK_CARD_EN;
		sdhci_writew(host, clk, SDHCI_CLOCK_CONTROL);
	}
	if (tz3000_data->manual_tune_param &&
	    (clk & SDHCI_CLOCK_CARD_EN) &&
	    (clk & SDHCI_CLOCK_INT_STABLE)) {
		const struct sdhci_tz3000_ec_tune_param *param =
			tz3000_data->manual_tune_param;
		sdhci_tz3000_manual_tuning(host, param->otap, param->itap,
					   param->usedll);
	}
}

static void sdhci_tz3000_disable_manual_tuning(struct sdhci_host *host)
{
	dev_dbg(mmc_dev(host->mmc), "disable manual tuning\n");

	/* Set TAPCHGWIN = 1 */
	econf_emmc_updatew(host, 1, EMMC_CTRL_DLYCHG);
	/* Set DLLENABLE = 0 */
	econf_emmc_updatew(host, 0, EMMC_CTRL_DLL0);
	/* Update ITAPDLY */
	econf_emmc_updatew(host, 0, EMMC_CTRL_INDLY);
	/* Update OTAPDLY */
	econf_emmc_updatew(host, 0, EMMC_CTRL_OUTDLY);
	/* Set TAPCHGWIN = 0 */
	econf_emmc_updatew(host, 0, EMMC_CTRL_DLYCHG);
}

static void sdhci_tz3000_manual_tuning(struct sdhci_host *host,
				       int otap, int itap, bool usedll)
{
	u32 itapval = itap < 0 ? 0 : ((itap << 8) | 1);
	u32 otapval = otap < 0 ? 0 : ((otap << 8) | 1);

	dev_dbg(mmc_dev(host->mmc), "manual tuning otap = %x, itap = %x\n",
		otap, itap);

	/* Set TAPCHGWIN = 1 */
	econf_emmc_updatew(host, 1, EMMC_CTRL_DLYCHG);
	/* Set DLLENABLE = 0 */
	econf_emmc_updatew(host, 0, EMMC_CTRL_DLL0);
	/* Update DLLCLKSEL */
	econf_emmc_updatew(host, 0, EMMC_CTRL_DLL1);
	/* Set DLLENABLE = 1 */
	if (usedll)
		econf_emmc_updatew(host, 1, EMMC_CTRL_DLL0);
	/* Update ITAPDLY */
	econf_emmc_updatew(host, itapval, EMMC_CTRL_INDLY);
	/* Update OTAPDLY */
	econf_emmc_updatew(host, otapval, EMMC_CTRL_OUTDLY);
	/* Set TAPCHGWIN = 0 */
	econf_emmc_updatew(host, 0, EMMC_CTRL_DLYCHG);
}

static void sdhci_tz3000_auto_tuning(struct sdhci_host *host, int otap)
{
	u32 otapval = otap < 0 ? 0 : ((otap << 8) | 1);

	dev_dbg(mmc_dev(host->mmc), "auto tuning otap = %x\n", otap);

	/* Set TAPCHGWIN = 1 */
	econf_emmc_updatew(host, 1, EMMC_CTRL_DLYCHG);
	/* Set DLLENABLE = 0 */
	econf_emmc_updatew(host, 0, EMMC_CTRL_DLL0);
	/* Update DLLCLKSEL */
	econf_emmc_updatew(host, 1, EMMC_CTRL_DLL1);
	/* Set DLLENABLE = 1 */
	econf_emmc_updatew(host, 1, EMMC_CTRL_DLL0);
	/* Update ITAPDLY */
	econf_emmc_updatew(host, 0, EMMC_CTRL_INDLY);
	/* Update OTAPDLY */
	econf_emmc_updatew(host, otapval, EMMC_CTRL_OUTDLY);
	/* Set TAPCHGWIN = 0 */
	econf_emmc_updatew(host, 0, EMMC_CTRL_DLYCHG);
}

static void sdhci_tz3000_enable_tuning(struct sdhci_host *host,
				       struct mmc_ios *ios, int enable)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct pltfm_tz3000_data *tz3000_data = pltfm_host->priv;
	struct platform_device *pdev = tz3000_data->pdev;
	struct sdhci_tz3000_platform_data *platdata = pdev->dev.platform_data;
	u16 clk;
	enum sdhci_tz3000_ec_tune_mode mode;
	const struct sdhci_tz3000_ec_tune_param *param;

	if (!host->clock)
		return;

	clk = sdhci_readw(host, SDHCI_CLOCK_CONTROL);
	if (!(clk & SDHCI_CLOCK_CARD_EN) || !(clk & SDHCI_CLOCK_INT_STABLE)) {
		dev_dbg(mmc_dev(host->mmc), "%s clock not enabled (0x%x).\n",
			__func__, clk);
		return;
	}

	if (!enable) {
		tz3000_data->manual_tune_param = NULL;
		sdhci_tz3000_disable_manual_tuning(host);
		return;
	}

	switch (ios->timing) {
	case MMC_TIMING_MMC_HS:
		mode = EC_MMC_HS;
		break;
	case MMC_TIMING_MMC_HS200:
		mode = EC_MMC_HS200;
		break;
	case MMC_TIMING_SD_HS: /* == MMC_TIMING_UHS_SDR25 */
		/* how can we tell UHS_SDR25 from HS? */
		mode = EC_SD_HS; /* or EC_SD_SDR25 */
		break;
	case MMC_TIMING_UHS_SDR50:
		if ((host->flags & SDHCI_SDR50_NEEDS_TUNING) ||
		    (host->flags & SDHCI_HS200_NEEDS_TUNING)) {
			mode = EC_SD_SDR50_AUTO;
			break;
		}
		mode = EC_SD_SDR50;
		break;
	case MMC_TIMING_UHS_SDR12:
		mode = EC_SD_SDR12;
		break;
	case MMC_TIMING_UHS_DDR50:
		/* MMC_HSDDR is not supported. assume SD_DDR50 */
		mode = EC_SD_DDR50;
		break;
	case MMC_TIMING_UHS_SDR104:
		mode = EC_SD_SDR104;
		break;
	default:
		mode = EC_SD_DS;
		break;
	}
	dev_dbg(mmc_dev(host->mmc), "tuning for timing = %d, mode = %d\n",
		ios->timing, mode);

	param = &platdata->ec_tune_params[mode];
	if (param->autotune) {
		tz3000_data->manual_tune_param = NULL;
		sdhci_tz3000_auto_tuning(host, param->otap);
	} else {
		tz3000_data->manual_tune_param = param;
		sdhci_tz3000_manual_tuning(host, param->otap, param->itap,
					   param->usedll);
	}
}

static unsigned int sdhci_tz3000_get_min_clock(struct sdhci_host *host)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct pltfm_tz3000_data *tz3000_data = pltfm_host->priv;
	struct platform_device *pdev = tz3000_data->pdev;
	struct sdhci_tz3000_platform_data *platdata = pdev->dev.platform_data;
	struct mmc_host *mmc = host->mmc;

	/* there is no hook to adjust f_max.  use get_min_clock instead. */
	if (platdata->f_max && platdata->f_max < mmc->f_max)
		mmc->f_max = platdata->f_max;
	return host->max_clk / SDHCI_MAX_DIV_SPEC_300;
}

static struct sdhci_ops sdhci_tz3000_ops = {
	.read_w = sdhci_tz3000_readw,
	.read_b = sdhci_tz3000_readb,
	.write_w = sdhci_tz3000_writew,
	.write_b = sdhci_tz3000_writeb,
	.platform_reset_enter = sdhci_tz3000_reset_enter,
	.platform_reset_exit = sdhci_tz3000_reset_exit,
	.enable_tuning = sdhci_tz3000_enable_tuning,
	.get_min_clock = sdhci_tz3000_get_min_clock,
};

static struct sdhci_pltfm_data sdhci_tz3000_pdata = {
	.ops	= &sdhci_tz3000_ops,
	.quirks	= 0,
	.quirks2 = SDHCI_QUIRK2_RESET_BOTH_CMD_DATA |
		   SDHCI_QUIRK2_RESET_AFTER_AUTO_TUNING |
		   SDHCI_QUIRK2_CHECK_CLK_BEFORE_SEND_COMMAND |
		   SDHCI_QUIRK2_WAIT_CARD_DETECT_ON_RESUME |
		   SDHCI_QUIRK2_STOP_CLK_NONSIMULTANEOUOSLY |
		   SDHCI_QUIRK2_DELAY_BEFORE_RESET_ON_ERROR,
};

static int __devinit sdhci_tz3000_probe(struct platform_device *pdev)
{
	struct sdhci_host *host;
	struct sdhci_pltfm_host *pltfm_host;
	struct pltfm_tz3000_data *tz3000_data;
	struct sdhci_tz3000_platform_data *platdata = pdev->dev.platform_data;
	int ret = 0;

	host = sdhci_pltfm_init(pdev, &sdhci_tz3000_pdata);
	if (IS_ERR(host))
		return PTR_ERR(host);
	pltfm_host = sdhci_priv(host);
	tz3000_data = devm_kzalloc(&pdev->dev,
				   sizeof(struct pltfm_tz3000_data),
				   GFP_KERNEL);
	if (!tz3000_data) {
		ret = -ENOMEM;
		goto err;
	}
	pltfm_host->priv = tz3000_data;
	tz3000_data->pdev = pdev;
	tz3000_data->econf_emmc_addr =
		devm_ioremap(&pdev->dev, platdata->econf_emmc_base, 0x100);
	if (!tz3000_data->econf_emmc_addr) {
		ret = ENOMEM;
		goto err;
	}

	sdhci_get_of_property(pdev);

	if (sdhci_readl(host, SDHCI_CAPABILITIES) & SDHCI_CAN_DO_8BIT)
		host->mmc->caps |= MMC_CAP_8_BIT_DATA;
	/* set non-removable if slot type was Embedded */
	if (((sdhci_readl(host, SDHCI_CAPABILITIES) >> 30) & 3) == 1)
		host->mmc->caps |= MMC_CAP_NONREMOVABLE;
	host->mmc->caps2 |= platdata->mmc_caps2;

	ret = sdhci_add_host(host);
	if (ret)
		goto err;

	return ret;
err:
	sdhci_pltfm_free(pdev);
	return ret;
}

static int __devexit sdhci_tz3000_remove(struct platform_device *pdev)
{
	return sdhci_pltfm_unregister(pdev);
}

#ifdef CONFIG_PM
static int sdhci_tz3000_suspend(struct device *dev)
{
	struct sdhci_host *host = dev_get_drvdata(dev);

	return sdhci_suspend_host(host);
}

static int sdhci_tz3000_resume(struct device *dev)
{
	struct sdhci_host *host = dev_get_drvdata(dev);

	return sdhci_resume_host(host);
}

/* SDHCI_PLTFM_PMOPS does not set freeze/thaw.  Use my own pmops. */
static const struct dev_pm_ops sdhci_tz3000_pmops = {
	SET_SYSTEM_SLEEP_PM_OPS(sdhci_tz3000_suspend, sdhci_tz3000_resume)
};
#define SDHCI_TZ3000_PMOPS (&sdhci_tz3000_pmops)
#else
#define SDHCI_TZ3000_PMOPS NULL
#endif

static struct platform_driver sdhci_tz3000_driver = {
	.driver		= {
		.name	= "sdhci-tz3000",
		.owner	= THIS_MODULE,
		.pm	= SDHCI_TZ3000_PMOPS,
	},
	.probe		= sdhci_tz3000_probe,
	.remove		= __devexit_p(sdhci_tz3000_remove),
};

module_platform_driver(sdhci_tz3000_driver);

MODULE_DESCRIPTION("SDHCI driver for TZ3000");
MODULE_LICENSE("GPL v2");
