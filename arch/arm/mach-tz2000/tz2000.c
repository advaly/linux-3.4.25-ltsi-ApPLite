/*
 * linux/arch/arm/mach-tz2000/tz2000.c
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
#include <linux/module.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/io.h>

#include <linux/platform_data/txss_eth.h>
#include <linux/platform_data/sdhci-tz3000.h>
#include <linux/platform_data/spi-tc90431.h>
#include <linux/platform_data/tz3000-cpufreq.h>
#include <linux/platform_data/gpio-tz3000.h>
#include <linux/platform_device.h>
#include <linux/errno.h>
#include <linux/err.h>
#include <linux/dma-mapping.h>
#include <linux/gpio.h>
#include <linux/i2c.h>
#include <linux/i2c/at24.h>
#include <linux/leds.h>
#include <linux/usb/ohci_pdriver.h>
#include <linux/usb/ehci_pdriver.h>
#include <linux/spi/spi.h>
#include <linux/spi/eeprom.h>
#include <linux/clk-tz3000.h>
#include <linux/mmc/host.h>
#include <asm/pgtable.h>
#include <asm/localtimer.h>
#include <asm/mach-types.h>
#include <asm/hardware/gic.h>
#include <asm/mach/map.h>
#include <asm/mach/time.h>
#include <asm/mach/arch.h>
#include <asm/gtimer.h>
#include <mach/irqs.h>
#include <mach/hardware.h>
#include <mach/platform.h>
#include <mach/system.h>
#include <mach/regs/cpu_memmap_def.h>
#include <mach/regs/pmu_reg_def.h>
#include <mach/regs/gconf_reg_def.h>
#include <mach/regs/wconf_reg_def.h>
#include <asm/pmu.h>

#if defined(CONFIG_SERIAL_8250)
#include <linux/serial.h>
#include <linux/serial_8250.h>
#endif

#if defined(CONFIG_SPI_TC90431) || defined(CONFIG_SPI_TC90431_MODULE)
#include <linux/spi/flash.h>
#include <linux/spi/tc90431.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/partitions.h>
#endif

static struct map_desc tz2000_io_desc[] __initdata = {
	{
		.virtual	= IO_ADDRESS(TZ2000_CPU_BASE),
		.pfn		= __phys_to_pfn(TZ2000_CPU_BASE),
		.length		= TZ2000_CPU_SIZE,
		.type		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(TZ2000_GCONF_BASE),
		.pfn		= __phys_to_pfn(TZ2000_GCONF_BASE),
		.length		= TZ2000_GCONF_SIZE,
		.type		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(TZ2000_PERIPHERAL_BASE),
		.pfn		= __phys_to_pfn(TZ2000_PERIPHERAL_BASE),
		.length		= TZ2000_PERIPHERAL_SIZE,
		.type		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(TZ2000_PMU_BASE),
		.pfn		= __phys_to_pfn(TZ2000_PMU_BASE),
		.length		= TZ2000_PMU_SIZE,
		.type		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(TZ2000_SCOMM_BASE),
		.pfn		= __phys_to_pfn(TZ2000_SCOMM_BASE),
		.length		= TZ2000_SCOMM_SIZE,
		.type		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(TZ2000_MBOOT_BASE),
		.pfn		= __phys_to_pfn(TZ2000_MBOOT_BASE),
		.length		= TZ2000_MBOOT_SIZE,
		.type		= MT_DEVICE,
	}
};

static void __init tz2000_map_io(void)
{
	iotable_init(tz2000_io_desc, ARRAY_SIZE(tz2000_io_desc));
}

static void __init tz2000_init_irq(void)
{
	gic_init(0, IRQ_GLOBALTIMER,
		 __io_address(TZ2000_GIC_DIST_BASE),
		 __io_address(TZ2000_GIC_CPU_BASE));
}

#define tz2000_has_debug_board() (gpio_get_value(34) == 0)

/*
 * register platform resource
 *   device name: name + no.  ex. "foo0" if name="foo" & no=0.
 *   memory area: use parent if size equal 0.
 *   irq        : don't set if irq equal 0.
 */
static struct platform_device *__init
register_platform_resource(int no, char *name, int irq, unsigned long addr,
			   unsigned long size)
{
	struct resource r[2];
	int num = 0;
	memset(r, 0, sizeof(r));
	r[num].flags = IORESOURCE_MEM;
	if (size) {
		r[num].start = addr;
		r[num].end = addr + size - 1;
		num++;
	}
	if (irq) {
		r[num].start = irq;
		r[num].flags = IORESOURCE_IRQ;
		num++;
	}
	if (!num)
		return ERR_PTR(-EINVAL);
	return platform_device_register_simple(name, no, r, num);
}

#ifdef CONFIG_SERIAL_8250
#define TZ2000_UART_NUM		4
#define TZ2000_UART_CLK		18432000;

static struct plat_serial8250_port tz2000_serial_pdata[TZ2000_UART_NUM + 1];

static struct platform_device tz2000_serial_device = {
	.name	= "serial8250",
	.id	= PLAT8250_DEV_PLATFORM,
	.dev	= {
		.platform_data	= tz2000_serial_pdata,
	},
};

static void __init tz2000_setup_serial(void)
{
	int i;

	for (i = 0; i < TZ2000_UART_NUM; i++) {
		struct plat_serial8250_port *pp = &tz2000_serial_pdata[i];
		pp->mapbase = TZ2000_UART_BASE + 0x1000 * i;
		pp->irq = IRQ_UART(i);
		pp->flags = UPF_BOOT_AUTOCONF | UPF_SKIP_TEST | UPF_IOREMAP;
		pp->iotype = UPIO_MEM;
		pp->regshift = 2;
		pp->uartclk = TZ2000_UART_CLK;
	}
	platform_device_register(&tz2000_serial_device);
}
#endif /* CONFIG_SERIAL_8250 */

#if defined(CONFIG_TXSSETH) || defined(CONFIG_TXSSETH_MODULE)
static void __init tz2000_setup_ethermac(void)
{
	struct platform_device *pdev;
	static struct txss_eth_platform_data pdata;


	if ((machine_is_tz2000rb2() && !tz2000_has_debug_board()) ||
	    machine_is_tz2000rb3())
		return;
	pdata.system_clock = 100000000;
	pdata.emacdrr = 0x80000000;
	pdata.fifosizer = 0x0000070f;
	pdev = register_platform_resource(0, "txss-eth", IRQ_ETHER,
					  TZ2000_ETHERMAC_BASE, SZ_8K);
	if (pdev) {
		pdev->dev.dma_mask = &pdev->dev.coherent_dma_mask;
		pdev->dev.coherent_dma_mask = DMA_BIT_MASK(32);
		pdev->dev.platform_data = &pdata;
	}
}
#endif

#if defined(CONFIG_SPI_TC90431) || defined(CONFIG_SPI_TC90431_MODULE)
static struct tc90431_spi_controller_data tz2000_spi_data0 = {
	.deassert_time = TZ2000_SPIC_INITIAL_DEASSERT_TIME,
#if IS_ENABLED(CONFIG_MTD_M25P80)
	.dir_read_phys = 0x20000000,
	.dir_read_size = 0x04000000,
#endif
};

static struct tc90431_spi_controller_data tz2000_spi_data1 = {
	.deassert_time = TZ2000_SPIC_INITIAL_DEASSERT_TIME,
#if IS_ENABLED(CONFIG_MTD_M25P80)
	.dir_read_phys = 0x24000000,
	.dir_read_size = 0x04000000,
#endif
};

static struct mtd_partition tz2000_spi_parts0[] = {
	{
		.name = "TZ2000 SPI0",
		.size = MTDPART_SIZ_FULL,
		.offset = 0x0,
	},
};

static struct flash_platform_data tz2000_spi_flash0 = {
	.name = "spi_flash0",
	.parts = tz2000_spi_parts0,
	.nr_parts = ARRAY_SIZE(tz2000_spi_parts0),
	.tc90431_spi_data = &tz2000_spi_data0,
};

static struct mtd_partition tz2000_spi_parts1[] = {
	{
		.name = "TZ2000 SPI1",
		.size = MTDPART_SIZ_FULL,
		.offset = 0x0,
	},
};

static struct flash_platform_data tz2000_spi_flash1 = {
	.name = "spi_flash1",
	.parts = tz2000_spi_parts1,
	.nr_parts = ARRAY_SIZE(tz2000_spi_parts1),
	.tc90431_spi_data = &tz2000_spi_data1,
};

static struct spi_board_info tz2000_spi_board_info[] __initdata = {
	{
		.modalias = "m25p80",
		.platform_data = &tz2000_spi_flash0,
		.controller_data = &tz2000_spi_data0,
		.max_speed_hz = TZ2000_SPIC_INITIAL_SPEED_HZ,
		.bus_num = TZ2000_SPIC_ID,
		.chip_select = 0,
	},
	{
		.modalias = "m25p80",
		.platform_data = &tz2000_spi_flash1,
		.controller_data = &tz2000_spi_data1,
		.max_speed_hz = TZ2000_SPIC_INITIAL_SPEED_HZ,
		.bus_num = TZ2000_SPIC_ID,
		.chip_select = 1,
	},
};

static void __init tz2000_setup_spi(void)
{
	int n = ARRAY_SIZE(tz2000_spi_board_info);
	struct platform_device *pdev;
	static struct spi_tc90431_platform_data pdata = {
		.hbus_clock = 50000000,
		.baud_clock = 600000000,
		.max_hz = 50000000,
	};
	pdev = register_platform_resource(TZ2000_SPIC_ID, "tc90431_spi", 0,
					  TZ2000_SPI_BASE, SZ_2K);
	if (pdev)
		pdev->dev.platform_data = &pdata;
	if (machine_is_tz2000rb2() || machine_is_tz2000rb3())
		n = 1;
	spi_register_board_info(tz2000_spi_board_info, n);
}
#endif /* CONFIG_SPI_TC90431 */

#if IS_ENABLED(CONFIG_SPI_TZ_SPIMS)
/* ROHM BR25S320 */
static struct spi_eeprom tz2000_spims_eeprom = {
	.name		= "br25s320",
	.byte_len	= 4096,
	.page_size	= 32,
	.flags		= EE_ADDR2,
};

static struct spi_board_info tz2000_spims_board_info[] __initdata = {
	{
		.modalias = "at25",
		.platform_data = &tz2000_spims_eeprom,
		.max_speed_hz = 3000000,	/* for 1.8V */
		.bus_num = TZ2000_SPIMS_ID,
		.chip_select = 0,
	},
};

static void __init tz2000_setup_spims(void)
{
	int i;
	u32 pinshare0 = readl(__io_address(TZ2000_GCONF_PINSHARE0));
	for (i = 0; i < TZ2000_SPIMS_NUM; i++) {
		u8 clk_bit;
		const char *clkname;
		struct clk *clk;
		if (i == 0) {
			clkname = "periSS_spims0";
			clk_bit = 8;
		} else if (i == 1) {
			clkname = "periSS_spims1";
			clk_bit = 24;
		} else {
			continue;
		}

		writel(1 << clk_bit, __io_address(TZ2000_PMU_SROFF_PERI3));
		clk = clk_register_tz_gate(NULL, clkname, "pllsys_50", 0,
			__io_address(TZ2000_PMU_CGON_PERI3), clk_bit);
		clk_register_clkdev(clk, NULL,
				    "spi-tz-spims.%d", TZ2000_SPIMS_ID + i);
		if (i == 0 && (pinshare0 & 0x04)) /* GPIO_SPI2_SEL */
			continue;
		if (i == 1 && (pinshare0 & 0x08)) /* GPIO_SPI3_SEL */
			continue;
		register_platform_resource(TZ2000_SPIMS_ID + i, "spi-tz-spims",
					   IRQ_SPIM(i),
					   TZ2000_SPIMS_REG(i), SZ_4K);
	}
	if (machine_is_tz2000eva())
		spi_register_board_info(tz2000_spims_board_info,
					ARRAY_SIZE(tz2000_spims_board_info));
}
#endif

#if IS_ENABLED(CONFIG_I2C_DESIGNWARE_PLATFORM)
/* ROHM BR24T16 */
static struct at24_platform_data eeprom_info = {
	.byte_len = 2048,
	.page_size = 16,
};

/* SII S24CS04A */
static struct at24_platform_data eeprom_info_4kbit = {
	.byte_len = 512,
	.page_size = 16,
};

static struct i2c_board_info i2c_eeprom_board_info __initdata = {
	I2C_BOARD_INFO("at24", 0x50),
	.platform_data = &eeprom_info,
};

#if IS_ENABLED(CONFIG_SND_SOC_TLV320ADC3xxx)
static struct i2c_board_info i2c_adc3xxx_board_info __initdata = {
	I2C_BOARD_INFO("tlv320adc3xxx", 0x18)
};
#endif

#if IS_ENABLED(CONFIG_SND_SOC_TLV320AIC3110) || \
	IS_ENABLED(CONFIG_MACH_TZ2000RB3)
static struct i2c_board_info i2c_aic3110_board_info __initdata = {
	I2C_BOARD_INFO("tlv320aic3110", 0x18)
};
#endif

/* PJ_I2C1: 5-6,7-8 Short for i2c0 */
static int eeprom_i2c_busno = -1;
static int __init early_eeprom_i2c(char *p)
{
	if (!p)
		return 0;

	return kstrtoint(p, 10, &eeprom_i2c_busno);
}
early_param("eeprom_i2c", early_eeprom_i2c);

#if IS_ENABLED(CONFIG_TOUCHSCREEN_NHD)
static struct i2c_board_info i2c_touchscreen_nhd_board_info __initdata = {
		I2C_BOARD_INFO("nhd_tp", 0x38),
};
#endif
#if IS_ENABLED(CONFIG_TOUCHSCREEN_FUSION)
static struct i2c_board_info i2c_touchscreen_fusion_board_info __initdata = {
		I2C_BOARD_INFO("fusion7_tp", 0x10),
};
#endif
#if IS_ENABLED(CONFIG_TOUCHSCREEN_IT7260_STS) || \
    IS_ENABLED(CONFIG_TOUCHSCREEN_IT7260_MTS)
static struct i2c_board_info i2c_touchscreen_it7260_board_info __initdata = {
		I2C_BOARD_INFO("IT7260", 0x46),
};
#endif

static void __init tz2000_setup_i2c(void)
{
	int i;
	struct clk *clk;

	writel(0x01000000, __io_address(TZ2000_PMU_SROFF_PERI1));
	clk = clk_register_tz_gate(NULL, "periSS_i2c", "pllsys_50", 0,
				   __io_address(TZ2000_PMU_CGON_PERI1), 24);
	for (i = 0; i < I2C_TZ2000_CH_NUM; i++) {
		clk_register_clkdev(clk, NULL, "i2c_designware.%d", i);
		register_platform_resource(i, "i2c_designware", IRQ_I2C(i),
					   I2C_TZ2000_REG(i), SZ_4K);
	}
	if (machine_is_tz2000eva())
		i2c_eeprom_board_info.platform_data = &eeprom_info_4kbit;
	if (machine_is_tz2000rb())
		eeprom_i2c_busno = 0;
	if (eeprom_i2c_busno >= 0)
		i2c_register_board_info(eeprom_i2c_busno,
					&i2c_eeprom_board_info, 1);
#if IS_ENABLED(CONFIG_TOUCHSCREEN_NHD)
	i2c_register_board_info(2, &i2c_touchscreen_nhd_board_info, 1);
#endif
#if IS_ENABLED(CONFIG_TOUCHSCREEN_FUSION)
	i2c_register_board_info(2, &i2c_touchscreen_fusion_board_info, 1);
#endif
#if IS_ENABLED(CONFIG_TOUCHSCREEN_IT7260_STS) || \
    IS_ENABLED(CONFIG_TOUCHSCREEN_IT7260_MTS)
	i2c_register_board_info(2, &i2c_touchscreen_it7260_board_info, 1);
#endif
#if IS_ENABLED(CONFIG_SND_SOC_TLV320ADC3xxx)
	if (!machine_is_tz2000rb3())
		i2c_register_board_info(3, &i2c_adc3xxx_board_info, 1);
#endif
#if IS_ENABLED(CONFIG_SND_SOC_TLV320AIC3110) || \
	IS_ENABLED(CONFIG_MACH_TZ2000RB3)
	if (machine_is_tz2000rb3())
		i2c_register_board_info(3, &i2c_aic3110_board_info, 1);
#endif
}
#endif

#if IS_ENABLED(CONFIG_MMC_SDHCI_TZ3000)

static struct resource tz2000_emmca_resources[] = {
	{
		.start	= TZ2000_EMMC4SD_BASE,
		.end	= TZ2000_EMMC4SD_BASE + 0xff,
		.flags	= IORESOURCE_MEM,
	}, {
		.start	= IRQ_EMMCA,
		.end	= IRQ_EMMCA,
		.flags	= IORESOURCE_IRQ,
	},
};

static struct resource tz2000_emmcb_resources[] = {
	{
		.start	= TZ2000_EMMC8SD_BASE,
		.end	= TZ2000_EMMC8SD_BASE + 0xff,
		.flags	= IORESOURCE_MEM,
	}, {
		.start	= IRQ_EMMCB,
		.end	= IRQ_EMMCB,
		.flags	= IORESOURCE_IRQ,
	},
};

static struct sdhci_tz3000_platform_data tz2000_emmca_platdata = {
	.econf_emmc_base = TZ2000_WCONF_EMMC_BASE(0),
	.ec_tune_params = {
		[EC_SD_DS]		= { -1, -1, 0, 0 },
		[EC_SD_HS]		= {  5, -1, 1, 0 },
		[EC_SD_SDR12]		= {  0, -1, 1, 0 },
		[EC_SD_SDR25]		= {  0, -1, 1, 0 },
		[EC_SD_SDR50]		= {  0, -1, 1, 0 },
		[EC_SD_SDR50_AUTO]	= {  0, -1, 1, 1 },
		[EC_SD_SDR104]		= {  0, -1, 1, 1 },
		[EC_SD_DDR50]		= {  0, -1, 1, 0 },
		[EC_MMC_HS]		= {  5, -1, 1, 0 },
		[EC_MMC_HS200]		= {  0, -1, 1, 1 },
		[EC_MMC_HSDDR]		= {  6, -1, 1, 0 },
	},
	.f_max = 50000000,
};

static struct sdhci_tz3000_platform_data tz2000_emmcb_platdata = {
	.econf_emmc_base = TZ2000_WCONF_EMMC_BASE(1),
	.ec_tune_params = {
		[EC_SD_DS]		= { -1, -1, 0, 0 },
		[EC_SD_HS]		= {  5, -1, 1, 0 },
		[EC_SD_SDR12]		= {  0, -1, 1, 0 },
		[EC_SD_SDR25]		= {  0, -1, 1, 0 },
		[EC_SD_SDR50]		= {  0, -1, 1, 0 },
		[EC_SD_SDR50_AUTO]	= {  0, -1, 1, 1 },
		[EC_SD_SDR104]		= {  0, -1, 1, 1 },
		[EC_SD_DDR50]		= {  0, -1, 1, 0 },
		[EC_MMC_HS]		= {  5, -1, 1, 0 },
		[EC_MMC_HS200]		= {  0, -1, 1, 1 },
		[EC_MMC_HSDDR]		= {  5, -1, 1, 0 },
	},
	.f_max = 50000000,
};

static struct sdhci_tz3000_platform_data tz2000_emmcb_nand_platdata = {
	.econf_emmc_base = TZ2000_WCONF_EMMC_BASE(1),
	.ec_tune_params = {
		[EC_SD_DS]		= { -1, -1, 0, 0 },
		[EC_SD_HS]		= { -1, -1, 0, 0 },
		[EC_SD_SDR12]		= { -1, -1, 0, 0 },
		[EC_SD_SDR25]		= { -1, -1, 0, 0 },
		[EC_SD_SDR50]		= { -1, -1, 0, 0 },
		[EC_SD_SDR50_AUTO]	= { -1, -1, 0, 0 },
		[EC_SD_SDR104]		= { -1, -1, 0, 0 },
		[EC_SD_DDR50]		= { -1, -1, 0, 0 },
		[EC_MMC_HS]		= { -1, -1, 0, 0 },
		[EC_MMC_HS200]		= { -1, -1, 0, 0 },
		[EC_MMC_HSDDR]		= { -1, -1, 0, 0 },
	},
	.f_max = 100000000,
	.mmc_caps2 = MMC_CAP2_FIXED_CSD_VER4 | MMC_CAP2_IGN_CSD_MAXDTR,
};

static void __init tz2000_sdhc_init(void)
{
	static struct platform_device tz2000_emmc[2];
	int i;
	void __iomem *wconf;

	for (i = 0; i < ARRAY_SIZE(tz2000_emmc); i++) {
		tz2000_emmc[i].name = "sdhci-tz3000";
		tz2000_emmc[i].id = i;
		tz2000_emmc[i].dev.dma_mask =
			&tz2000_emmc[i].dev.coherent_dma_mask;
		tz2000_emmc[i].dev.coherent_dma_mask = DMA_BIT_MASK(32);
	}
	tz2000_emmc[0].resource = tz2000_emmca_resources;
	tz2000_emmc[0].num_resources = ARRAY_SIZE(tz2000_emmca_resources);
	tz2000_emmc[0].dev.platform_data = &tz2000_emmca_platdata;
	platform_device_register(&tz2000_emmc[0]);
	if (machine_is_tz2000rb() || machine_is_tz2000rb2())
		gpio_set_value(0, 1);
	if (machine_is_tz2000rb() || machine_is_tz2000rb2() || machine_is_tz2000rb3()) {
		gpio_set_value(35, 0);
		mdelay(1);
		gpio_set_value(35, 1);
	}
#if IS_ENABLED(CONFIG_APPLITE_EMMC)
#ifdef CONFIG_PM
    /* for internal emmc */
    register_platform_resource(0, "emmc_pm", IRQ_EMMCB, TZ2000_EMMC8SD_BASE, SZ_1K);
#endif /* CONFIG_PM */
#else /* !CONFIG_APPLITE_EMMC */
	tz2000_emmc[1].resource = tz2000_emmcb_resources;
	tz2000_emmc[1].num_resources = ARRAY_SIZE(tz2000_emmcb_resources);
	tz2000_emmc[1].dev.platform_data = &tz2000_emmcb_platdata;
	wconf = ioremap(TZ2000_WCONF_EMMC_BASE(1), 0x100);
	/* CFG_CAPABILITY0:8BITSUPPORT means internal NAND mode */
	if (readl(wconf) & 0x00040000)
		tz2000_emmc[1].dev.platform_data = &tz2000_emmcb_nand_platdata;
	iounmap(wconf);
	platform_device_register(&tz2000_emmc[1]);
#endif
}
#endif

#if IS_ENABLED(CONFIG_USB_OHCI_HCD_PLATFORM)
static struct resource tz2000_ohci_resources[] = {
	[0] = {
		.start	= TZ2000_USB2H_OHCI_BASE,
		.end	= TZ2000_USB2H_OHCI_BASE + SZ_4K - 1,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= IRQ_USB2H_OHCI,
		.end	= IRQ_USB2H_OHCI,
		.flags	= IORESOURCE_IRQ,
	},
};

static struct usb_ohci_pdata tz2000_ohci_pdata = {
};

static struct platform_device tz2000_ohci_device = {
	.name		= "ohci-platform",
	.id		= -1,
	.resource	= tz2000_ohci_resources,
	.num_resources	= ARRAY_SIZE(tz2000_ohci_resources),
	.dev = {
		.dma_mask		=
			&tz2000_ohci_device.dev.coherent_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platform_data		= &tz2000_ohci_pdata,
	},
};
#endif

#if IS_ENABLED(CONFIG_USB_EHCI_HCD_PLATFORM)
static struct resource tz2000_ehci_resources[] = {
	[0] = {
		.start	= TZ2000_USB2H_EHCI_BASE,
		.end	= TZ2000_USB2H_EHCI_BASE + SZ_4K - 1,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= IRQ_USB2H_EHCI,
		.end	= IRQ_USB2H_EHCI,
		.flags	= IORESOURCE_IRQ,
	},
};

static struct usb_ehci_pdata tz2000_ehci_pdata = {
};

static struct platform_device tz2000_ehci_device = {
	.name		= "ehci-platform",
	.id		= -1,
	.resource	= tz2000_ehci_resources,
	.num_resources	= ARRAY_SIZE(tz2000_ehci_resources),
	.dev = {
		.dma_mask		=
			&tz2000_ehci_device.dev.coherent_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platform_data		= &tz2000_ehci_pdata,
	},
};
#endif

static void __init tz2000_usb2h_init(void)
{
	if (machine_is_tz2000eva() && !gpio_get_value(47))
		return;
#if IS_ENABLED(CONFIG_USB_OHCI_HCD_PLATFORM)
	platform_device_register(&tz2000_ohci_device);
#endif
#if IS_ENABLED(CONFIG_USB_EHCI_HCD_PLATFORM)
	platform_device_register(&tz2000_ehci_device);
#endif
}

#if IS_ENABLED(CONFIG_FB_TZ2000)

#define IRQ_LCDC(x)		(179 + (x))/* 179 - 180 */

static void tz2000_setup_lcdc(void)
{
#if IS_ENABLED(CONFIG_FB_APPLITE_BASIC)
	struct platform_device *pdev;
	static u64 dmamask = DMA_BIT_MASK(32);
	static struct resource r[] = {
		[0] = DEFINE_RES_MEM(CPU_PMU_REG_BASE, CPU_PMU_REG_SIZE),
		[1] = DEFINE_RES_MEM(CPU_LCDC_REG_BASE, CPU_LCDC_REG_SIZE),
		[2] = DEFINE_RES_MEM(CPU_GFX_REG_BASE, CPU_GFX_REG_SIZE),
		[3] = DEFINE_RES_IRQ(IRQ_LCDC(0)),
		[4] = DEFINE_RES_IRQ(IRQ_LCDC(1)),
	};
	struct clk *clk;

	/* ClockGatingOn_lcdcSS_0 */
	clk = clk_register_tz_gate_m(NULL, "lcdcSS", "pllsys_50", 0,
			   __io_address(TZ2000_PMU_BASE + 0x1128), 0x00000101);
	clk_register_clkdev(clk, "lcdc", "tz2000fb.0");
#if IS_ENABLED(CONFIG_FB_APPLITE_BASIC_GFX_MERGED)
	clk = clk_register_tz_gate(NULL, "gfxSS_gfx", "pllsys_50", 0,
				   __io_address(TZ2000_PMU_BASE + 0x1178), 0);
	clk_register_clkdev(clk, "gfx", "tz2000fb.0");
#endif /* IS_ENABLED(CONFIG_FB_APPLITE_BASIC_GFX_MERGED) */

	pdev = platform_device_register_simple("tz2000fb", 0, r, 5);
	if (pdev) {
		pdev->dev.dma_mask = &dmamask;
		pdev->dev.coherent_dma_mask = dmamask;
	}
#if !IS_ENABLED(CONFIG_FB_APPLITE_BASIC_GFX_MERGED)
	pdev = platform_device_register_simple("tz2000gfx", 0, NULL, 0);
	if (pdev) {
		pdev->dev.dma_mask = &dmamask;
		pdev->dev.coherent_dma_mask = dmamask;
	}
#endif /* !IS_ENABLED(CONFIG_FB_APPLITE_BASIC_GFX_MERGED) */
#elif IS_ENABLED(CONFIG_FB_APPLITE_STANDARD)
	struct platform_device *pdev;
	static u64 dmamask = DMA_BIT_MASK(32);
	static struct resource r[] = {
		[0] = DEFINE_RES_MEM(CPU_PMU_REG_BASE, CPU_PMU_REG_SIZE),
		[1] = DEFINE_RES_MEM(CPU_LCDC_REG_BASE, CPU_LCDC_REG_SIZE),
		[2] = DEFINE_RES_MEM(CPU_GFX_REG_BASE, CPU_GFX_REG_SIZE),
		[3] = DEFINE_RES_IRQ(IRQ_LCDC(0)),
		[4] = DEFINE_RES_IRQ(IRQ_LCDC(1)),
	};
	struct clk *clk;

	/* ClockGatingOn_lcdcSS_0 */
	clk = clk_register_tz_gate_m(NULL, "lcdcSS", "pllsys_50", 0,
			   __io_address(TZ2000_PMU_BASE + 0x1128), 0x00000101);
	clk_register_clkdev(clk, "lcdc", "applitefb.0");
	clk = clk_register_tz_gate(NULL, "gfxSS_gfx", "pllsys_50", 0,
				   __io_address(TZ2000_PMU_BASE + 0x1178), 0);
	clk_register_clkdev(clk, "gfx", "applitefb.0");

	pdev = platform_device_register_simple("applitefb", 0, r, 5);
	if (pdev) {
		pdev->dev.dma_mask = &dmamask;
		pdev->dev.coherent_dma_mask = dmamask;
	}
#endif
}
#endif

#if IS_ENABLED(CONFIG_SND_APPLITE_SOC)
static struct resource al_i2s_resources0[] = {
	DEFINE_RES_MEM(CPU_I2SO_REG_BASE, 0x1000),
	DEFINE_RES_MEM(CPU_I2SI_REG_BASE, 0x1000),
	DEFINE_RES_MEM(CPU_I2SC_REG_BASE, 0x100),
	DEFINE_RES_MEM(CPU_GCONF_REG_BASE, 0x1000),
	DEFINE_RES_MEM(CPU_PMU_REG_BASE, 0x10000),
	DEFINE_RES_IRQ(IRQ_I2SO0_INT),
	DEFINE_RES_IRQ(IRQ_I2SO0_ERR),
	DEFINE_RES_IRQ(IRQ_I2SI0_INT),
	DEFINE_RES_IRQ(IRQ_I2SI0_ERR),
};

/* id 0:I2S0 */
static struct platform_device snd_soc_applite_device0 = {
	.name		= "applite-i2s",
	.id		= 0,
	.resource	= al_i2s_resources0,
	.num_resources	= ARRAY_SIZE(al_i2s_resources0),
};
static struct platform_device snd_soc_appilte_pcm_device = {
	.name		= "applite-pcm-audio",
	.resource	= NULL,
	.num_resources	= 0,
};
static struct platform_device snd_soc_applite_tzxxx_device = {
	.name		= "applite-tzxxx",
	.resource	= NULL,
	.num_resources	= 0,
};
#endif

#if IS_ENABLED(CONFIG_APPLITE_SYSCON)

#define CPU_SCOMM_REG_BASE	(0x00580000)
#define SCOMM_REG_SIZE		(0x1000)

#define IRQ_SCOMM(x)	(32+(x))	/* 32 - 35 */

static void tz2000_setup_syscon(void)
{
	struct platform_device *pdev;
	static u64 dmamask = DMA_BIT_MASK(32);
	static struct resource r[] = {
		[0] = DEFINE_RES_MEM(CPU_SCOMM_REG_BASE, SCOMM_REG_SIZE),
		[1] = DEFINE_RES_MEM(CPU_MBOX_REG_BASE, CPU_MBOX_REG_SIZE),
		[2] = DEFINE_RES_IRQ(IRQ_SCOMM(2)),
		[3] = DEFINE_RES_IRQ(IRQ_SCOMM(3)),
	};
	pdev = platform_device_register_simple("applite-syscon", 0, r, 4);
	if (pdev) {
		pdev->dev.dma_mask = &dmamask;
		pdev->dev.coherent_dma_mask = dmamask;
	}
}
#endif

#if IS_ENABLED(CONFIG_USB_APPLITE_UDC)

#define IRQ_USB2DC 168

static void __init tz2000_udc_init(void)
{
	struct platform_device *pdev;
	static u64 dmamask = DMA_BIT_MASK(32);
	void __iomem *wconf_reg_base;
	u32 rev0;

	wconf_reg_base = ioremap(CPU_WCONF_REG_BASE, CPU_WCONF_REG_SIZE);

	if (machine_is_tz2000eva()) {
		pr_info("TZ2000 USB2DC Selected\n");
		writel(0x5511, __io_address(CPU_PMU_REG_BASE + PMU_SOFTRESETON_USB2HDSS_0_OFS));
		/* 1.USB2D Clock on */
		writel(0x1001, __io_address(CPU_PMU_REG_BASE + PMU_CLOCKGATINGOFF_USB2HDSS_0_OFS));
		/* 2.USB2PHY Refference Clock change */
		writel(0x51, wconf_reg_base + WCONF_USB2HD_REFCLK_OFS);
		/* 3.USB2D Config change */
		writel(0x3, wconf_reg_base + WCONF_USB2HD_MUX_CTL_OFS);
		/* 4-5.USB POREN */
		rev0 = readl(__io_address(CPU_PMU_REG_BASE + PMU_POREN_OFS));
		writel((rev0 | 0x40), __io_address(CPU_PMU_REG_BASE + PMU_POREN_OFS));
		udelay(1);
		/* 7-8.USB Control Setting */
		rev0 = readl(__io_address(CPU_PMU_REG_BASE + PMU_USB_CONTROL_OFS));
		writel((rev0 & ~0x4), __io_address(CPU_PMU_REG_BASE + PMU_USB_CONTROL_OFS));
		udelay(200);
		/* 9-10.USB Control Setting */
		rev0 = readl(__io_address(CPU_PMU_REG_BASE + PMU_USB_CONTROL_OFS));
		writel((rev0 | 0x01), __io_address(CPU_PMU_REG_BASE + PMU_USB_CONTROL_OFS));
		udelay(200);
		/* 11-12.USB Control Setting */
		rev0 = readl(__io_address(CPU_PMU_REG_BASE + PMU_USB_CONTROL_OFS));
		writel((rev0 | 0x02), __io_address(CPU_PMU_REG_BASE + PMU_USB_CONTROL_OFS));
		udelay(2000);
		/* 13.USB2D reset off */
		writel(0x1, __io_address(CPU_PMU_REG_BASE + PMU_SOFTRESETOFF_USB2HDSS_0_OFS));
		udelay(1000);
		writel(0x4001, __io_address(CPU_PMU_REG_BASE + PMU_SOFTRESETOFF_USB2HDSS_0_OFS));
		udelay(1);
		writel(0x5001, __io_address(CPU_PMU_REG_BASE + PMU_SOFTRESETOFF_USB2HDSS_0_OFS));

		pdev = register_platform_resource(0, "applite-udc",
				IRQ_USB2DC,
				CPU_USB2DC_REG_BASE, CPU_USB2DC_REG_SIZE);
		if (pdev) {
			pdev->dev.dma_mask = &dmamask;
			pdev->dev.coherent_dma_mask = dmamask;
		}
	}
}

#endif

#if IS_ENABLED(CONFIG_APPLITE_SADC)
static void __init tz2000_sadc_init(void)
{
	struct platform_device *pdev;
	struct clk *clk;
	static struct resource r[] = {
		[0] = DEFINE_RES_MEM(CPU_SADC12_REG_BASE, CPU_SADC12_REG_SIZE),
		[1] = DEFINE_RES_MEM(CPU_PMU_REG_BASE, CPU_PMU_REG_SIZE),
	};

	/* ClockGatingOn_periSS_1 */
	clk = clk_register_tz_gate(NULL, "periSS_adc", "pllsys_50", 0,
				   __io_address(TZ2000_PMU_BASE + 0x1024), 8);
	clk_register_clkdev(clk, NULL, "applite-sadc.0");

	pdev = platform_device_register_simple("applite-sadc", 0, r, 2);

	pr_debug("TZ2000 Slow AD register resource = 0x%0x\n", CPU_SADC12_REG_BASE);
	return;
}
#endif

#if IS_ENABLED(CONFIG_APPLITE_PWM)
#define IRQ_PWM 99 
static void __init tz2000_pwm_init(void)
{
	struct platform_device *pdev;
	struct clk *clk;
	static struct resource r[] = {
		[0] = DEFINE_RES_MEM(CPU_PWM_REG_BASE, CPU_PWM_REG_SIZE),
		[1] = DEFINE_RES_MEM(CPU_PMU_REG_BASE, CPU_PMU_REG_SIZE),
		[2] = DEFINE_RES_IRQ(IRQ_PWM),
	};

	/* ClockGatingOn_periSS_1 */
	clk = clk_register_tz_gate(NULL, "periSS_pwm", "pllsys_50", 0,
				   __io_address(TZ2000_PMU_BASE + 0x1024), 0);
	clk_register_clkdev(clk, NULL, "applite-pwm.0");

	pdev = platform_device_register_simple("applite-pwm", 0, r, 3);
	pr_debug("TZ2000 PWM register resource = 0x%0x\n", CPU_PWM_REG_BASE);
	return;
}
#endif

#if IS_ENABLED(CONFIG_APPLITE_YUVC)
static struct resource applite_yuvc_res[] = {
	DEFINE_RES_MEM_NAMED(CPU_YUVC_REG_BASE, CPU_YUVC_REG_SIZE, "yuvc"),
	DEFINE_RES_MEM_NAMED(CPU_PMU_REG_BASE, CPU_PMU_REG_SIZE, "pmu"),
	DEFINE_RES_MEM_NAMED(CPU_GDMAC_REG_BASE, CPU_GDMAC_REG_SIZE, "dma"),
	DEFINE_RES_IRQ_NAMED(181, "int"),
};
static void __init tz2000_setup_yuvc(void)
{
	struct platform_device *pdev;
	struct clk *clk;

	/* ClockGatingOn_yuvcSS_0 */
	clk = clk_register_tz_gate(NULL, "yuvcSS_yuvc", "pllsys_50", 0,
				   __io_address(TZ2000_PMU_BASE + 0x1158), 0);
	clk_register_clkdev(clk, NULL, "applite-yuvc.0");

	pdev = platform_device_register_simple("applite-yuvc", 0,
					applite_yuvc_res, 4);
	pr_debug("TZ2000 YUVC register resource = 0x%0x\n", CPU_YUVC_REG_BASE);
}

#endif

#if IS_ENABLED(CONFIG_RTC_DRV_APPLITE)
#define IRQ_RTC 187 
static void __init tz2000_rtc_init(void)
{
	struct platform_device *pdev;
	static struct resource r[] = {
		[0] = DEFINE_RES_MEM(CPU_RTC_REG_BASE, CPU_RTC_REG_SIZE),
		[1] = DEFINE_RES_IRQ(IRQ_RTC),
	};

	pdev = platform_device_register_simple("applite-rtc", 0, r, 2);

	pr_debug("TZ2000 RTC register resource = 0x%0x\n", CPU_RTC_REG_BASE);
	return;
}
#endif

static void tz2000_setup_gdmac(void)
{
	writel(BIT(8), __io_address(CPU_PMU_REG_BASE + PMU_CLOCKGATINGOFF_PERISS_0_OFS));
	writel(BIT(8), __io_address(CPU_PMU_REG_BASE + PMU_SOFTRESETOFF_PERISS_0_OFS));
}

static void __init tz2000_show_revision(void)
{
	u32 rev0, rev1;
	rev0 = readl(__io_address(TZ2000_BOOTINFO_FWREV0));
	rev1 = readl(__io_address(TZ2000_BOOTINFO_FWREV1));
	pr_info("TOSHIBA TZ2000 botfw:%x.%x\n", rev0, rev1);
}

static void tz2000_setup_pmu(void)
{
	static struct resource pmu_resources[] = {
		[0] = {
			.start = IRQ_PMU_CPU(0),
			.flags = IORESOURCE_IRQ,
		},
	};
	static struct platform_device pmu_device = {
		.name = "arm-pmu",
		.id = ARM_PMU_DEVICE_CPU,
		.num_resources = ARRAY_SIZE(pmu_resources),
		.resource = pmu_resources,
	};
	platform_device_register(&pmu_device);
}

static int txss_periphclk = TXSS_PERIPHCLK;

/* Early initializations */
static void __init tz2000_init_early(void)
{
	gtmr_setup(__io_address(TZ2000_GLOBAL_TMR_BASE),
		   IRQ_GLOBALTIMER, txss_periphclk);
	gtmr_sched_clock_init();
}

static struct gpio tz2000_eva_gpios[] = {
	{ .gpio = 1, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 2, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 3, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 32, .flags = GPIOF_IN, },
	{ .gpio = 33, .flags = GPIOF_IN, },
	{ .gpio = 34, .flags = GPIOF_IN, },
	{ .gpio = 35, .flags = GPIOF_IN, },
	{ .gpio = 38, .flags = GPIOF_IN, },
	{ .gpio = 39, .flags = GPIOF_IN, },
	{ .gpio = 44, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 45, .flags = GPIOF_IN, },
	{ .gpio = 46, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 47, .flags = GPIOF_IN, },
};
static struct gpio_led tz2000_eva_gpio_leds[] = {
	{ .gpio = 36, },
	{ .gpio = 37, },
};

static struct gpio tz2000_rb_gpios[] = {
	{ .gpio = 0, .flags = GPIOF_OUT_INIT_LOW, },
	{ .gpio = 1, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 2, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 3, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 32, .flags = GPIOF_IN, },
	{ .gpio = 33, .flags = GPIOF_IN, },
	{ .gpio = 34, .flags = GPIOF_IN, },
	{ .gpio = 35, .flags = GPIOF_OUT_INIT_LOW, },
	{ .gpio = 42, .flags = GPIOF_IN, },
	{ .gpio = 43, .flags = GPIOF_IN, },
	{ .gpio = 44, .flags = GPIOF_IN, },
	{ .gpio = 45, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 46, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 47, .flags = GPIOF_OUT_INIT_LOW, },
};
static struct gpio_led tz2000_rb_gpio_leds[] = {
	{ .gpio = 40, },
	{ .gpio = 41, },
};

static struct gpio tz2000_rb2_gpios[] = {
	{ .gpio = 0, .flags = GPIOF_OUT_INIT_LOW, },
	{ .gpio = 1, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 2, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 3, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 32, .flags = GPIOF_IN, },
	{ .gpio = 33, .flags = GPIOF_IN, },
	{ .gpio = 34, .flags = GPIOF_IN, },
	{ .gpio = 35, .flags = GPIOF_OUT_INIT_LOW, },
	{ .gpio = 43, .flags = GPIOF_IN, },
	{ .gpio = 44, .flags = GPIOF_IN, },
	{ .gpio = 45, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 46, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 47, .flags = GPIOF_OUT_INIT_LOW, },
};
static struct gpio_led tz2000_rb2_gpio_leds[] = {
	{ .gpio = 40, },
	{ .gpio = 41, },
};

static struct gpio tz2000_rb3_gpios[] = {
	{ .gpio = 0, .flags = GPIOF_OUT_INIT_LOW, },
	{ .gpio = 1, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 32, .flags = GPIOF_IN, },
	{ .gpio = 33, .flags = GPIOF_IN, },
	{ .gpio = 34, .flags = GPIOF_IN, },
	{ .gpio = 35, .flags = GPIOF_OUT_INIT_LOW, },
	{ .gpio = 40, .flags = GPIOF_OUT_INIT_LOW, },
	{ .gpio = 41, .flags = GPIOF_OUT_INIT_LOW, },
	{ .gpio = 43, .flags = GPIOF_IN, },
	{ .gpio = 47, .flags = GPIOF_OUT_INIT_LOW, },
};
static struct gpio_led tz2000_rb3_gpio_leds[] = {
	{ .gpio = 40, },
	{ .gpio = 41, },
};

static u32 gp0_smp = 0xffffffff;
static int __init early_gp0_smp(char *p)
{
	return p ? kstrtouint(p, 0, &gp0_smp) : 0;
}
early_param("gp0_smp", early_gp0_smp);

static u32 gp1_smp = 0xffffffff;
static int __init early_gp1_smp(char *p)
{
	return p ? kstrtouint(p, 0, &gp1_smp) : 0;
}
early_param("gp1_smp", early_gp1_smp);

#if IS_ENABLED(CONFIG_LEDS_GPIO)
static int use_leds_gpio;
static int __init early_use_leds_gpio(char *p)
{
	use_leds_gpio = 1;
	return 0;
}
early_param("use_leds_gpio", early_use_leds_gpio);
#endif

static __init void tz2000_gpio_board_init(void)
{
	int ret;
	int i;
	struct gpio *gpios = NULL;
	int n = 0;
	struct gpio_led *leds = NULL;
	int num_leds = 0;

	if (machine_is_tz2000eva()) {
		gpios = tz2000_eva_gpios;
		n = ARRAY_SIZE(tz2000_eva_gpios);
		leds = tz2000_eva_gpio_leds;
		num_leds = ARRAY_SIZE(tz2000_eva_gpio_leds);
	}
	if (machine_is_tz2000rb()) {
		gpios = tz2000_rb_gpios;
		n = ARRAY_SIZE(tz2000_rb_gpios);
		leds = tz2000_rb_gpio_leds;
		num_leds = ARRAY_SIZE(tz2000_rb_gpio_leds);
	}
	if (machine_is_tz2000rb2()) {
		gpios = tz2000_rb2_gpios;
		n = ARRAY_SIZE(tz2000_rb2_gpios);
		leds = tz2000_rb2_gpio_leds;
		num_leds = ARRAY_SIZE(tz2000_rb2_gpio_leds);
	}
	if (machine_is_tz2000rb3()) {
		gpios = tz2000_rb3_gpios;
		n = ARRAY_SIZE(tz2000_rb3_gpios);
		leds = tz2000_rb3_gpio_leds;
		num_leds = ARRAY_SIZE(tz2000_rb3_gpio_leds);
	}
	if (machine_is_tz2000eva() || machine_is_tz2000rb() || machine_is_tz2000rb2()) {
		writel( readl(__io_address(CPU_GCONF_REG_BASE + GCONF_PINSHARE0_OFS)) | GCONF_PINSHARE0_GPIO_SPI3_SEL_MASK,
			__io_address(CPU_GCONF_REG_BASE + GCONF_PINSHARE0_OFS));
	}
	ret = gpio_request_array(gpios, n);
	if (ret)
		pr_err("%s: gpio_request_array failed: %d\n", __func__, ret);
	for (i = 0; i < n; i++)
		gpio_export(gpios[i].gpio, true);
#if IS_ENABLED(CONFIG_LEDS_GPIO)
	if (use_leds_gpio && num_leds) {
		struct gpio_led_platform_data led_pdata = {
			.num_leds = num_leds,
			.leds = leds,
		};
		for (i = 0; i < num_leds; i++) {
			leds[i].name = kasprintf(GFP_KERNEL,
						 "gpio%u", leds[i].gpio);
			leds[i].default_state = LEDS_GPIO_DEFSTATE_OFF;
		}
		platform_device_register_resndata(NULL, "leds-gpio", -1,
						  NULL, 0,
						  &led_pdata,
						  sizeof(led_pdata));
		num_leds = 0;
	}
#endif
	for (i = 0; i < num_leds; i++) {
		gpio_request_one(leds[i].gpio, GPIOF_OUT_INIT_LOW, NULL);
		gpio_export(leds[i].gpio, true);
	}
}

static void tz2000_gpio_init(unsigned int id,
			     unsigned int gpio_base, unsigned int nr_gpio,
			     unsigned long gpio_reg_base,
			     unsigned int parent_irq,
			     unsigned int irq_base)
{
	static struct tz3000_gpio_platform_data pdata;
	struct resource res[2];

	memset(&res, 0, sizeof(res));
	res[0].start = gpio_reg_base;
	res[0].end = gpio_reg_base + SZ_4K - 1;
	res[0].flags = IORESOURCE_MEM;
	res[1].start = parent_irq;
	res[1].flags = IORESOURCE_IRQ;
	pdata.gpio_base = gpio_base;
	pdata.nr_gpio = nr_gpio;
	pdata.irq_base = irq_base;
	platform_device_register_resndata(NULL, "tz3000-gpio", id,
					  res, ARRAY_SIZE(res),
					  &pdata, sizeof(pdata));
}

static void tz2000_setup_cpufreq(void)
{
#if IS_ENABLED(CONFIG_ARM_TZ3000_CPUFREQ)
	static struct tz3000_cpufreq_platform_data cpufreq_pdata;
	static struct platform_device cpufreq_device = {
		.name = "tz3000-cpufreq",
		.id = -1,
		.dev = {
			.platform_data = &cpufreq_pdata,
		},
	};
	cpufreq_pdata.pllclk = TZ2000_PLLCLK;
	cpufreq_pdata.clkdiv_reg = __io_address(TZ2000_PMU_BASE + 0x4404);
	platform_device_register(&cpufreq_device);
#endif
}

static void __iomem *mbox_base;
static void tz2000_poweroff(void)
{
	if (mbox_base)
		writel(0x80, mbox_base + 4);
}

static void tz2000_restart(char mode, const char *cmd)
{
	if (mbox_base)
		writel(0x90, mbox_base + 4);
}

void tz2000_enter_suspend(void)
{
	if (mbox_base)
		writel(0xa0, mbox_base + 4);
}
static void __init tz2000_init(void)
{
	int i;

	mbox_base = ioremap(TZ2000_MBOX_BASE, SZ_4K);
	tz2000_show_revision();
	clk_register_fixed_rate(NULL, "pllsys_50", NULL, CLK_IS_ROOT, 50000000);
	if (gp0_smp != 0xffffffff)
		writel(gp0_smp, __io_address(TZ2000_GP_SMP(0)));
	if (gp1_smp != 0xffffffff)
		writel(gp1_smp, __io_address(TZ2000_GP_SMP(1)));
	for (i = 0; i < 2; i++)
		tz2000_gpio_init(i, i * 32, 32,
				 TZ2000_GPIO_BASE + i * 0x1000,
				 IRQ_GPIO(i), IRQ_GPIO_START + i * 32);
	tz2000_gpio_board_init();

	/* serial setup */
#ifdef CONFIG_SERIAL_8250
	tz2000_setup_serial();
#endif
	/* tz2000 ethermac setup */
#if defined(CONFIG_TXSSETH) || defined(CONFIG_TXSSETH_MODULE)
	tz2000_setup_ethermac();
#endif
	/* tz2000 spi setup */
#if defined(CONFIG_SPI_TC90431) || defined(CONFIG_SPI_TC90431_MODULE)
	tz2000_setup_spi();
#endif
#if IS_ENABLED(CONFIG_SPI_TZ_SPIMS)
	tz2000_setup_spims();
#endif

#if IS_ENABLED(CONFIG_I2C_DESIGNWARE_PLATFORM)
	tz2000_setup_i2c();
#endif
#if IS_ENABLED(CONFIG_MMC_SDHCI_TZ3000)
	tz2000_sdhc_init();
#endif
	tz2000_usb2h_init();
	tz2000_setup_pmu();
	tz2000_setup_cpufreq();
	tz2000_setup_gdmac();
#if IS_ENABLED(CONFIG_APPLITE_PWM)
	tz2000_pwm_init();
#endif
#if IS_ENABLED(CONFIG_FB_TZ2000)
	tz2000_setup_lcdc();
#endif
#if IS_ENABLED(CONFIG_SND_APPLITE_SOC)
	{
		struct clk *clk;

		/* ClockGatingOn_periSS_2 */
		clk = clk_register_tz_gate_m(NULL, "periSS_i2s", "pllsys_50", 0,
				__io_address(TZ2000_PMU_BASE + 0x1028),
				0x11010101);
		clk_register_clkdev(clk, "i2s", "applite-tzxxx.0");
		clk_register_clkdev(clk, "i2s", "applite-i2s.0");
	}
	platform_device_register(&snd_soc_applite_device0);
	platform_device_register(&snd_soc_appilte_pcm_device);
	platform_device_register(&snd_soc_applite_tzxxx_device);
#endif
#if IS_ENABLED(CONFIG_USB_APPLITE_UDC)
	tz2000_udc_init();
#endif
#if IS_ENABLED(CONFIG_APPLITE_SYSCON)
	tz2000_setup_syscon();
#endif
#if IS_ENABLED(CONFIG_APPLITE_SADC)
	tz2000_sadc_init();
#endif
#if IS_ENABLED(CONFIG_APPLITE_YUVC)
	tz2000_setup_yuvc();
#endif
#if IS_ENABLED(CONFIG_RTC_DRV_APPLITE)
	tz2000_rtc_init();
#endif

	pm_power_off = tz2000_poweroff;
}

static void __init tz2000_timer_init(void)
{
	gtmr_clocksource_init();
	gtmr_tick_setup();
}

static struct sys_timer tz2000_timer = {
	.init = tz2000_timer_init,
};

static struct platform_device applitema_device = {
	.name = "applitema",
	.dev = {
		.coherent_dma_mask = 0xffffffff,
	},
};

static int __init applitema_pdev_init(void)
{
	int ret;
#ifndef CONFIG_CMA
	int dma;
#endif

	ret = platform_device_register(&applitema_device);
	if (ret) {
		printk("%s: platform_device_register failed\n",
		       __FUNCTION__);
		return ret;
	}

	return 0;
}
device_initcall(applitema_pdev_init);

#ifdef CONFIG_MACH_TZ2000RB3
MACHINE_START(TZ2000RB3, "TOSHIBA TZ2000 RB3")
	.atag_offset	= 0x100,
	.map_io		= tz2000_map_io,
	.init_early	= tz2000_init_early,
	.init_irq	= tz2000_init_irq,
	.timer		= &tz2000_timer,
	.handle_irq	= gic_handle_irq,
	.init_machine	= tz2000_init,
	.restart	= tz2000_restart,
MACHINE_END
#endif

#ifdef CONFIG_MACH_TZ2000RB2
MACHINE_START(TZ2000RB2, "TOSHIBA TZ2000 RB2")
	.atag_offset	= 0x100,
	.map_io		= tz2000_map_io,
	.init_early	= tz2000_init_early,
	.init_irq	= tz2000_init_irq,
	.timer		= &tz2000_timer,
	.handle_irq	= gic_handle_irq,
	.init_machine	= tz2000_init,
	.restart	= tz2000_restart,
MACHINE_END
#endif

#ifdef CONFIG_MACH_TZ2000RB
MACHINE_START(TZ2000RB, "TOSHIBA TZ2000 RB")
	.atag_offset	= 0x100,
	.map_io		= tz2000_map_io,
	.init_early	= tz2000_init_early,
	.init_irq	= tz2000_init_irq,
	.timer		= &tz2000_timer,
	.handle_irq	= gic_handle_irq,
	.init_machine	= tz2000_init,
	.restart	= tz2000_restart,
MACHINE_END
#endif

#ifdef CONFIG_MACH_TZ2000EVA
MACHINE_START(TZ2000EVA, "TOSHIBA TZ2000 EVA")
	.atag_offset	= 0x100,
	.map_io		= tz2000_map_io,
	.init_early	= tz2000_init_early,
	.init_irq	= tz2000_init_irq,
	.timer		= &tz2000_timer,
	.handle_irq	= gic_handle_irq,
	.init_machine	= tz2000_init,
	.restart	= tz2000_restart,
MACHINE_END
#endif
