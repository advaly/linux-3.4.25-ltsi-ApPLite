/*
 * linux/arch/arm/mach-tz3000/tz3000.c
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
#include <linux/spi/spi.h>
#include <linux/spi/eeprom.h>
#include <linux/clk-tz3000.h>
#include <asm/pgtable.h>
#include <asm/localtimer.h>
#include <asm/mach-types.h>
#include <asm/hardware/gic.h>
#include <asm/hardware/cache-l2x0.h>
#include <asm/mach/map.h>
#include <asm/mach/time.h>
#include <asm/mach/arch.h>
#include <asm/smp_twd.h>
#include <asm/gtimer.h>
#include <mach/irqs.h>
#include <mach/hardware.h>
#include <mach/platform.h>
#include <mach/system.h>
#include <mach/regs/cpu_memmap_def.h>
#include <mach/regs/pmu_reg_def.h>
#include <mach/regs/gconf_reg_def.h>
#include <mach/regs/econf_reg_def.h>
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

#if (IS_ENABLED(CONFIG_APPLITE_VEU) || IS_ENABLED(CONFIG_APPLITE_VDU))
#include <linux/pm_domain.h>
#endif

#if IS_ENABLED(CONFIG_APPLITE_VEU)
#include <linux/memblock.h>
#include <linux/dma-contiguous.h>
#endif

#if IS_ENABLED(CONFIG_APPLITE_VDU)
#include <linux/memblock.h>
#include <linux/dma-contiguous.h>
#endif


static struct map_desc tz3000_io_desc[] __initdata = {
	{
		.virtual	= IO_ADDRESS(TZ3000_CPU_BASE),
		.pfn		= __phys_to_pfn(TZ3000_CPU_BASE),
		.length		= TZ3000_CPU_SIZE,
		.type		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(TZ3000_GCONF_BASE),
		.pfn		= __phys_to_pfn(TZ3000_GCONF_BASE),
		.length		= TZ3000_GCONF_SIZE,
		.type		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(TZ3000_PERIPHERAL_BASE),
		.pfn		= __phys_to_pfn(TZ3000_PERIPHERAL_BASE),
		.length		= TZ3000_PERIPHERAL_SIZE,
		.type		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(TZ3000_PMU_BASE),
		.pfn		= __phys_to_pfn(TZ3000_PMU_BASE),
		.length		= TZ3000_PMU_SIZE,
		.type		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(TZ3000_SCOMM_BASE),
		.pfn		= __phys_to_pfn(TZ3000_SCOMM_BASE),
		.length		= TZ3000_SCOMM_SIZE,
		.type		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(TZ3000_MBOOT_BASE),
		.pfn		= __phys_to_pfn(TZ3000_MBOOT_BASE),
		.length		= TZ3000_MBOOT_SIZE,
		.type		= MT_DEVICE,
	}
};

static void __init tz3000_map_io(void)
{
	iotable_init(tz3000_io_desc, ARRAY_SIZE(tz3000_io_desc));
}

#ifdef CONFIG_CACHE_L2X0
int tz3000_pl310_init(void)
{
	void __iomem *pl310_base =
	    (void __iomem *)__io_address(TZ3000_L2C_BASE);
#ifdef CONFIG_CACHE_L310_PREFETCH_ENABLE
	u32 pctrl;
#endif
	if (!(readl(pl310_base + L2X0_CTRL) & 1)) {
		/* set RAM latencies to 1 cycle */
		writel(0, pl310_base + L2X0_TAG_LATENCY_CTRL);
		writel(0, pl310_base + L2X0_DATA_LATENCY_CTRL);
	}

	/* 512KB (64KB/way), 8-way associativity, evmon/share enabled */
	/* Exclusive cache disabled */
#ifdef CONFIG_CACHE_L310_PREFETCH_ENABLE
	/* Instruction/Data prefetching enabled */
	/* Bits: ..11 ...0 0101 0110 0000 .... .... .... */
	l2x0_init(pl310_base, 0x30560000, 0xce000fff);

	pctrl = readl(pl310_base + L2X0_PREFETCH_CTRL);
	writel(pctrl | 0x30000000, pl310_base + L2X0_PREFETCH_CTRL);
#else
	/* Bits: .... ...0 0101 0110 0000 .... .... .... */
	l2x0_init(pl310_base, 0x00560000, 0xfe000fff);
#endif
	return 0;
}
#endif

static void __init tz3000_init_irq(void)
{
	gic_init(0, IRQ_GLOBALTIMER,
		 __io_address(TZ3000_GIC_DIST_BASE),
		 __io_address(TZ3000_GIC_CPU_BASE));
}

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
#define TZ3000_UART_NUM		5
#define TZ3000_UART_CLK		18432000;

static struct plat_serial8250_port tz3000_serial_pdata[TZ3000_UART_NUM + 1];

static struct platform_device tz3000_serial_device = {
	.name	= "serial8250",
	.id	= PLAT8250_DEV_PLATFORM,
	.dev	= {
		.platform_data	= tz3000_serial_pdata,
	},
};

static void __init tz3000_setup_serial(void)
{
	int i;

	for (i = 0; i < TZ3000_UART_NUM; i++) {
		struct plat_serial8250_port *pp = &tz3000_serial_pdata[i];
		pp->mapbase = TZ3000_UART_BASE + 0x1000 * i;
		pp->irq = IRQ_UART(i);
		pp->flags = UPF_BOOT_AUTOCONF | UPF_SKIP_TEST | UPF_IOREMAP;
		pp->iotype = UPIO_MEM;
		pp->regshift = 2;
		pp->uartclk = TZ3000_UART_CLK;
	}
	platform_device_register(&tz3000_serial_device);
}
#endif /* CONFIG_SERIAL_8250 */

#if defined(CONFIG_TXSSETH) || defined(CONFIG_TXSSETH_MODULE)
static void __init tz3000_txsseth_rgmii_setup(void)
{
	/* clear RESET/PD/BP */
	writel(0, __io_address(TZ3000_PMU_PLLETHR_REG));
	mb(); /* barrier */
}

static void __init tz3000_setup_ethermac(void)
{
	struct platform_device *pdev;
	static struct txss_eth_platform_data pdata;
	u32 cgo = readl(__io_address(TZ3000_PMU_CGOFF_ETHER));

	if (!(cgo & 0x1))
		return;
	if (!(machine_is_tz3000rb2() || machine_is_tz3000rb4())) {
		pdata.is_rgmii = 1;
		pdata.gbit_support = 1;
	}
	pdata.system_clock = 200000000;
	pdata.emacdrr = 0x0f01000;
	pdata.rx_buf_size = 4096; /* will be cliped to max value by txss_eth */
	pdev = register_platform_resource(0, "txss-eth", IRQ_ETHER,
					  TZ3000_ETHERMAC_BASE, SZ_8K);
	if (pdev) {
		pdev->dev.dma_mask = &pdev->dev.coherent_dma_mask;
		pdev->dev.coherent_dma_mask = DMA_BIT_MASK(32);
		pdev->dev.platform_data = &pdata;
	}
	if (pdata.is_rgmii)
		tz3000_txsseth_rgmii_setup();
}
#endif

static int is_emmc2_selected(void)
{
	/* EMMC2_SEL */
	return readl(__io_address(TZ3000_GCONF_PINSHARE3)) & 1;
}

static int is_nand_selected(void)
{
	return !is_emmc2_selected();
}

static int machine_is_tz3000rb_old(void)
{
	/* for backward compatibility with old TZ3000RB U-Boot */
	return machine_is_tz3000eva() && is_nand_selected();
}

#if defined(CONFIG_SPI_TC90431) || defined(CONFIG_SPI_TC90431_MODULE)
static struct tc90431_spi_controller_data tz3000_spi_data0 = {
	.deassert_time = TZ3000_SPIC_INITIAL_DEASSERT_TIME,
#if IS_ENABLED(CONFIG_MTD_M25P80)
	.dir_read_phys = 0x20000000,
	.dir_read_size = 0x04000000,
#endif
};

static struct tc90431_spi_controller_data tz3000_spi_data1 = {
	.deassert_time = TZ3000_SPIC_INITIAL_DEASSERT_TIME,
#if IS_ENABLED(CONFIG_MTD_M25P80)
	.dir_read_phys = 0x24000000,
	.dir_read_size = 0x04000000,
#endif
};

static struct mtd_partition tz3000_spi_parts0[] = {
	{
		.name = "TZ3000 SPI0",
		.size = MTDPART_SIZ_FULL,
		.offset = 0x0,
	},
};

static struct flash_platform_data tz3000_spi_flash0 = {
	.name = "spi_flash0",
	.parts = tz3000_spi_parts0,
	.nr_parts = ARRAY_SIZE(tz3000_spi_parts0),
	.tc90431_spi_data = &tz3000_spi_data0,
};

static struct mtd_partition tz3000_spi_parts1[] = {
	{
		.name = "TZ3000 SPI1",
		.size = MTDPART_SIZ_FULL,
		.offset = 0x0,
	},
};

static struct flash_platform_data tz3000_spi_flash1 = {
	.name = "spi_flash1",
	.parts = tz3000_spi_parts1,
	.nr_parts = ARRAY_SIZE(tz3000_spi_parts1),
	.tc90431_spi_data = &tz3000_spi_data1,
};

static struct spi_board_info tz3000_spi_board_info[] __initdata = {
	{
		.modalias = "m25p80",
		.platform_data = &tz3000_spi_flash0,
		.controller_data = &tz3000_spi_data0,
		.max_speed_hz = TZ3000_SPIC_INITIAL_SPEED_HZ,
		.bus_num = TZ3000_SPIC_ID,
		.chip_select = 0,
	},
	{
		.modalias = "m25p80",
		.platform_data = &tz3000_spi_flash1,
		.controller_data = &tz3000_spi_data1,
		.max_speed_hz = TZ3000_SPIC_INITIAL_SPEED_HZ,
		.bus_num = TZ3000_SPIC_ID,
		.chip_select = 1,
	},
};

static void __init tz3000_setup_spi(void)
{
	int i;
	int n = ARRAY_SIZE(tz3000_spi_board_info);
	struct platform_device *pdev;
	static struct spi_tc90431_platform_data pdata = {
		.hbus_clock = 100000000,
		.baud_clock = 600000000,
#if 1 /* REVISIT: limit to 35.29MHz */
		.max_hz = 600000000 / 0x11,
#else
		.max_hz = 100000000,
#endif
	};
#if IS_ENABLED(CONFIG_MTD_M25P80)
	if (machine_is_tz3000rb4()) {
		/* quad io is not supported. disable direct access */
		tz3000_spi_data0.dir_read_phys = 0;
		tz3000_spi_data1.dir_read_phys = 0;
	}
#endif
	for (i = 0; i < TZ3000_SPIC_NUM; i++) {
		pdev = register_platform_resource(i, "tc90431_spi", 0,
						  TZ3000_SPI_REG(i), SZ_2K);
		if (pdev)
			pdev->dev.platform_data = &pdata;
	}
	if (machine_is_tz3000rb2() || machine_is_tz3000rb3() ||
	    machine_is_tz3000rb4())
		n = 1;
	spi_register_board_info(tz3000_spi_board_info, n);
}
#endif /* CONFIG_SPI_TC90431 */

#if IS_ENABLED(CONFIG_SPI_TZ_SPIMS)
static int eeprom_spims_busno = -1;
static int __init early_eeprom_spims(char *p)
{
	if (!p)
		return 0;

	return kstrtoint(p, 10, &eeprom_spims_busno);
}
early_param("eeprom_spims", early_eeprom_spims);

/* ROHM BR25S320 */
static struct spi_eeprom tz3000_spims_eeprom = {
	.name		= "br25s320",
	.byte_len	= 4096,
	.page_size	= 32,
	.flags		= EE_ADDR2,
};

static struct spi_board_info tz3000_spims_board_info[] __initdata = {
	{
		.modalias = "at25",
		.platform_data = &tz3000_spims_eeprom,
		.max_speed_hz = 3000000,	/* for 1.8V */
		.chip_select = 0,
	},
};

static void __init tz3000_setup_spims(void)
{
	int i;
	for (i = 0; i < TZ3000_SPIMS_NUM; i++) {
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
		writel(1 << clk_bit, __io_address(TZ3000_PMU_SROFF_PERI3));
		clk = clk_register_tz_gate(NULL, clkname, "pllsys_100", 0,
			__io_address(TZ3000_PMU_CGON_PERI3), clk_bit);
		clk_register_clkdev(clk, NULL,
				    "spi-tz-spims.%d", TZ3000_SPIMS_ID + i);
		register_platform_resource(TZ3000_SPIMS_ID + i, "spi-tz-spims",
					   IRQ_SPIM(i),
					   TZ3000_SPIMS_REG(i), SZ_4K);
	}
	if (eeprom_spims_busno >= 0) {
		tz3000_spims_board_info[0].bus_num =
			TZ3000_SPIMS_ID + eeprom_spims_busno;
		spi_register_board_info(tz3000_spims_board_info,
					ARRAY_SIZE(tz3000_spims_board_info));
	}
}
#endif

#if defined(CONFIG_MTD_NAND_TC90431_HAMMING) || \
	defined(CONFIG_MTD_NAND_TC90431_HAMMING_MODULE)
#include <linux/mtd/nand.h>
#include <linux/mtd/partitions.h>
static struct resource tz3000_ham_nand_resources[] = {
	[0] = {
		.start	= TZ3000_HAM_NAND_BASE,
		.end	= TZ3000_HAM_NAND_BASE + SZ_4K - 1,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= TZ3000_HAM_NANDC_BASE,
		.end	= TZ3000_HAM_NANDC_BASE + SZ_16M - 1,
		.flags	= IORESOURCE_MEM,
	},
	[2] = {
		.start	= 0,
		.end	= 0,
		.flags	= IORESOURCE_IRQ,
	},
};

static struct platform_nand_chip tz3000_ham_nand_data = {
	.nr_chips	= 1,
	.chip_delay	= 50,
	.options	= 0,
};

static struct platform_device tz3000_ham_nand_device = {
	.name = "tc90431_nand2",
	.id = -1,
	.dev = {
		.platform_data = &tz3000_ham_nand_data,
	},
	.num_resources = ARRAY_SIZE(tz3000_ham_nand_resources),
	.resource = tz3000_ham_nand_resources,
};

static void __init tz3000_ham_setup_nand(void)
{
	if (is_nand_selected()) {
		struct clk *clk;
		void __iomem *reg = __io_address(TZ3000_PMU_CGON_NANDC);
		clk_register_tz_gate(NULL, "nandcSS", "pllsys_100", 0, reg, 0);
		clk = clk_register_tz_gate(NULL, "nandcSS_m0", "nandcSS", 0,
					   reg, 8);
		clk_register_clkdev(clk, NULL, "tc90431_nand2");
		platform_device_register(&tz3000_ham_nand_device);
	}
}
#endif

#if IS_ENABLED(CONFIG_I2C_DESIGNWARE_PLATFORM)
/* ROHM BR24T16 */
static struct at24_platform_data eeprom_info = {
	.byte_len = 2048,
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

/* default i2c0 (PJ_I2C1: 9-10,11-12 Short, PJ_I2C2: 1-2,3-4 Short) */
static int eeprom_i2c_busno = -1;
static int __init early_eeprom_i2c(char *p)
{
	if (!p)
		return 0;

	return kstrtoint(p, 10, &eeprom_i2c_busno);
}
early_param("eeprom_i2c", early_eeprom_i2c);

static u32 tz3000_rb4_i2c_modify(u32 bus_id, u32 addr)
{
	int gpio6_val, gpio7_val;
	u32 new_addr;

	switch (addr) {
	case 0x07:
	case 0x21:
	case 0x3c:
		gpio6_val = 0;
		gpio7_val = 0;
		new_addr = addr;
		break;
	case 0x08:
	case 0x22:
	case 0x3d:
		gpio6_val = 1;
		gpio7_val = 0;
		new_addr = addr - 1;
		break;
	case 0x09:
	case 0x23:
	case 0x3e:
		gpio6_val = 0;
		gpio7_val = 1;
		new_addr = addr - 2;
		break;
	case 0x0a:
	case 0x24:
	case 0x3f:
		gpio6_val = 1;
		gpio7_val = 1;
		new_addr = addr - 3;
		break;
	default:
		return addr;
	}

	gpio_set_value(6, gpio6_val);
	gpio_set_value(7, gpio7_val);
	return new_addr;
}

static void __init tz3000_setup_i2c(void)
{
	int i;
	struct clk *clk;
	struct platform_device *pdev;

	writel(0x01000000, __io_address(TZ3000_PMU_SROFF_PERI1));
	clk = clk_register_tz_gate(NULL, "periSS_i2c", "pllsys_50", 0,
				   __io_address(TZ3000_PMU_CGON_PERI1), 24);
	for (i = 0; i < I2C_TZ3000_CH_NUM; i++) {
		clk_register_clkdev(clk, NULL, "i2c_designware.%d", i);
		pdev = register_platform_resource(i, "i2c_designware",
					IRQ_I2C(i), I2C_TZ3000_REG(i), SZ_4K);
		if (machine_is_tz3000rb4() && i == 1 && pdev)
			pdev->dev.platform_data = tz3000_rb4_i2c_modify;
	}
	if (eeprom_i2c_busno >= 0)
		i2c_register_board_info(eeprom_i2c_busno,
					&i2c_eeprom_board_info, 1);
#if IS_ENABLED(CONFIG_SND_SOC_TLV320ADC3xxx)
	if (!machine_is_tz3000rb4())
		i2c_register_board_info(3, &i2c_adc3xxx_board_info, 1);
#endif
}
#endif

#if IS_ENABLED(CONFIG_MMC_SDHCI_TZ3000)

static struct resource tz3000_emmca_resources[] = {
	{
		.start	= TZ3000_EMMCA_BASE,
		.end	= TZ3000_EMMCA_BASE + 0xff,
		.flags	= IORESOURCE_MEM,
	}, {
		.start	= IRQ_EMMCA,
		.end	= IRQ_EMMCA,
		.flags	= IORESOURCE_IRQ,
	},
};

static struct resource tz3000_emmcb_resources[] = {
	{
		.start	= TZ3000_EMMCB_BASE,
		.end	= TZ3000_EMMCB_BASE + 0xff,
		.flags	= IORESOURCE_MEM,
	}, {
		.start	= IRQ_EMMCB,
		.end	= IRQ_EMMCB,
		.flags	= IORESOURCE_IRQ,
	},
};

static struct resource tz3000_emmcc_resources[] = {
	{
		.start	= TZ3000_EMMCC_BASE,
		.end	= TZ3000_EMMCC_BASE + 0xff,
		.flags	= IORESOURCE_MEM,
	}, {
		.start	= IRQ_EMMCC,
		.end	= IRQ_EMMCC,
		.flags	= IORESOURCE_IRQ,
	},
};

static struct sdhci_tz3000_platform_data tz3000_emmca_platdata = {
	.econf_emmc_base = TZ3000_ECONF_EMMC_BASE(0),
	.ec_tune_params = {
		[EC_SD_DS]		= { -1, -1, 1, 0 },
		[EC_SD_HS]		= { 15, -1, 1, 0 },
		[EC_SD_SDR12]		= {  9, -1, 1, 0 },
		[EC_SD_SDR25]		= {  9, -1, 1, 0 },
		[EC_SD_SDR50]		= {  9, -1, 1, 0 },
		[EC_SD_SDR50_AUTO]	= {  5, -1, 1, 1 },
		[EC_SD_SDR104]		= {  3, -1, 1, 1 },
		[EC_SD_DDR50]		= {  7, -1, 1, 0 },
		[EC_MMC_HS]		= { 15, -1, 1, 0 },
		[EC_MMC_HS200]		= {  3, -1, 1, 1 },
		[EC_MMC_HSDDR]		= { -1, -1, 1, 0 },
	},
};

static struct sdhci_tz3000_platform_data tz3000_emmcb_platdata = {
	.econf_emmc_base = TZ3000_ECONF_EMMC_BASE(1),
	.ec_tune_params = {
		[EC_SD_DS]		= { -1, -1, 1, 0 },
		[EC_SD_HS]		= { 15, -1, 1, 0 },
		[EC_SD_SDR12]		= { 10, -1, 1, 0 },
		[EC_SD_SDR25]		= { 10, -1, 1, 0 },
		[EC_SD_SDR50]		= { 10, -1, 1, 0 },
		[EC_SD_SDR50_AUTO]	= {  5, -1, 1, 1 },
		[EC_SD_SDR104]		= {  4, -1, 1, 1 },
		[EC_SD_DDR50]		= {  9, -1, 1, 0 },
		[EC_MMC_HS]		= { 15, -1, 1, 0 },
		[EC_MMC_HS200]		= {  4, -1, 1, 1 },
		[EC_MMC_HSDDR]		= { -1, -1, 1, 0 },
	},
};

static struct sdhci_tz3000_platform_data tz3000_emmcc_platdata = {
	.econf_emmc_base = TZ3000_ECONF_EMMC_BASE(2),
	.ec_tune_params = {
		[EC_SD_DS]		= { -1, -1, 1, 0 },
		[EC_SD_HS]		= { 15, -1, 1, 0 },
		[EC_SD_SDR12]		= {  7, -1, 1, 0 },
		[EC_SD_SDR25]		= {  7, -1, 1, 0 },
		[EC_SD_SDR50]		= {  7, -1, 1, 0 },
		[EC_SD_SDR50_AUTO]	= {  4, -1, 1, 1 },
		[EC_SD_SDR104]		= {  2, -1, 1, 1 },
		[EC_SD_DDR50]		= {  6, -1, 1, 0 },
		[EC_MMC_HS]		= { 15, -1, 1, 0 },
		[EC_MMC_HS200]		= {  2, -1, 1, 1 },
		[EC_MMC_HSDDR]		= { -1, -1, 1, 0 },
	},
};

static void __init tz3000_sdhc_init(void)
{
	static struct platform_device tz3000_emmc[3];
	int i;
	u32 cgo = readl(__io_address(TZ3000_PMU_CGOFF_EMMC));

	for (i = 0; i < ARRAY_SIZE(tz3000_emmc); i++) {
		tz3000_emmc[i].name = "sdhci-tz3000";
		tz3000_emmc[i].id = i;
		tz3000_emmc[i].dev.dma_mask =
			&tz3000_emmc[i].dev.coherent_dma_mask;
		tz3000_emmc[i].dev.coherent_dma_mask = DMA_BIT_MASK(32);
	}
	if (cgo & 0x000003) {
		tz3000_emmc[0].resource = tz3000_emmca_resources;
		tz3000_emmc[0].num_resources =
			ARRAY_SIZE(tz3000_emmca_resources);
		tz3000_emmc[0].dev.platform_data = &tz3000_emmca_platdata;
		platform_device_register(&tz3000_emmc[0]);
	}
	if (cgo & 0x000300) {
		tz3000_emmc[1].resource = tz3000_emmcb_resources;
		tz3000_emmc[1].num_resources =
			ARRAY_SIZE(tz3000_emmcb_resources);
		tz3000_emmc[1].dev.platform_data = &tz3000_emmcb_platdata;
		platform_device_register(&tz3000_emmc[1]);
	}
	if ((cgo & 0x030000) && is_emmc2_selected()) {
		tz3000_emmc[2].resource = tz3000_emmcc_resources;
		tz3000_emmc[2].num_resources =
			ARRAY_SIZE(tz3000_emmcc_resources);
		tz3000_emmc[2].dev.platform_data = &tz3000_emmcc_platdata;
		platform_device_register(&tz3000_emmc[2]);
	}
}
#endif

#if IS_ENABLED(CONFIG_USB_XHCI_HCD)

static void __init tz3000_usb_init(void)
{
	struct platform_device *pdev;
	int have_usbh = 0;

	if (machine_is_tz3000eva()) {
		switch (readl(__io_address(TZ3000_GP_DR(0))) & 0xc0) {
		case 0x00: /* Disable */
			break;
		case 0x80: /* PCIe + USB2D */
			break;
		case 0x40: /* USB3H */
		case 0xc0: /* PCIe + USB3H(HS) */
			have_usbh = 1;
		}
	}
	if (machine_is_tz3000rb() || machine_is_tz3000rb_old() ||
	    machine_is_tz3000rb3() || machine_is_tz3000rb4())
		have_usbh = 1;
	if (have_usbh) {
		pdev = register_platform_resource(0, "xhci-hcd", IRQ_USB3HC,
						  TZ3000_USB3HC_BASE, SZ_1M);
		if (pdev) {
			pdev->dev.dma_mask = &pdev->dev.coherent_dma_mask;
			pdev->dev.coherent_dma_mask = DMA_BIT_MASK(32);
		}
	}
}

#endif

#if IS_ENABLED(CONFIG_VIDEO_APPLITE_CAMIF)

#include <media/soc_camera.h>
#include <media/applite-camera.h>

#if IS_ENABLED(CONFIG_SOC_CAMERA_T4K08)
/* T4K08 camera module */
static int tz3000_camera_power(struct device *dev, int on)
{
	gpio_set_value(2, on ? 1 : 0);
	return 0;
}

static struct i2c_board_info t4k08_info = {
	I2C_BOARD_INFO("t4k08", 0x3c),
};

static struct soc_camera_link t4k08_link = {
	.bus_id		= 0,
	.i2c_adapter_id	= 1,
	.board_info	= &t4k08_info,
	.power		= tz3000_camera_power,
};

static struct platform_device t4k08_camera = {
	.name   = "soc-camera-pdrv",
	.id     = 0,
	.dev    = {
		.platform_data = &t4k08_link,
	},
};
#endif

#if IS_ENABLED(CONFIG_SOC_CAMERA_TC358743)
/* TC358743 camera module */
static struct i2c_board_info tc358743_info = {
	I2C_BOARD_INFO("tc358743", 0x0F),
};

static struct soc_camera_link tc358743_link = {
	.bus_id		= 0,
	.i2c_adapter_id	= 1,
	.board_info	= &tc358743_info,
};

static struct platform_device tc358743_camera = {
	.name   = "soc-camera-pdrv",
	.id     = 0,
	.dev    = {
		.platform_data = &tc358743_link,
	},
};

static struct applite_camera_platform_data cam_tc358743_pdata = {
	.csirx_unused = false,
	.lane_config = LANE_CONFIG_4LANEx1,
};
#endif

#if IS_ENABLED(CONFIG_SOC_CAMERA_OV7725_MPD)
/* Reference board 4 camera module */
static int tz3000_rb4_camera_power(struct device *dev, int on)
{
	static int use_count = 0;

	if (on) {
		if (!use_count++) {
			gpio_direction_input(1);	/* Hi-Z */
			gpio_direction_input(12);	/* Hi-Z */
			msleep(100);
		}
	} else {
		if (!--use_count) {
			gpio_direction_output(12, 0);	/* Low */
			gpio_direction_output(1, 0);	/* Low */
			msleep(1);
		}
	}
	return 0;
}

#define RB4_CAMERA_NAME		"ov7725_mpd"
#define RB4_CAMERA_SLAVE	0x21

static struct i2c_board_info rb4_camera_info0 = {
	I2C_BOARD_INFO(RB4_CAMERA_NAME, RB4_CAMERA_SLAVE),
};
static struct i2c_board_info rb4_camera_info1 = {
	I2C_BOARD_INFO(RB4_CAMERA_NAME, RB4_CAMERA_SLAVE + 1),
};
static struct i2c_board_info rb4_camera_info2 = {
	I2C_BOARD_INFO(RB4_CAMERA_NAME, RB4_CAMERA_SLAVE + 2),
};
static struct i2c_board_info rb4_camera_info3 = {
	I2C_BOARD_INFO(RB4_CAMERA_NAME, RB4_CAMERA_SLAVE + 3),
};

static struct soc_camera_link rb4_camera_link0 = {
	.bus_id		= 0,
	.i2c_adapter_id	= 1,
	.board_info	= &rb4_camera_info0,
	.power		= tz3000_rb4_camera_power,
};
static struct soc_camera_link rb4_camera_link1 = {
	.bus_id		= 1,
	.i2c_adapter_id	= 1,
	.board_info	= &rb4_camera_info1,
	.power		= tz3000_rb4_camera_power,
};
static struct soc_camera_link rb4_camera_link2 = {
	.bus_id		= 2,
	.i2c_adapter_id	= 1,
	.board_info	= &rb4_camera_info2,
	.power		= tz3000_rb4_camera_power,
};
static struct soc_camera_link rb4_camera_link3 = {
	.bus_id		= 3,
	.i2c_adapter_id	= 1,
	.board_info	= &rb4_camera_info3,
	.power		= tz3000_rb4_camera_power,
};

static struct platform_device rb4_camera0 = {
	.name   = "soc-camera-pdrv",
	.id     = 0,
	.dev    = {
		.platform_data = &rb4_camera_link0,
	},
};
static struct platform_device rb4_camera1 = {
	.name   = "soc-camera-pdrv",
	.id     = 1,
	.dev    = {
		.platform_data = &rb4_camera_link1,
	},
};
static struct platform_device rb4_camera2 = {
	.name   = "soc-camera-pdrv",
	.id     = 2,
	.dev    = {
		.platform_data = &rb4_camera_link2,
	},
};
static struct platform_device rb4_camera3 = {
	.name   = "soc-camera-pdrv",
	.id     = 3,
	.dev    = {
		.platform_data = &rb4_camera_link3,
	},
};
#endif

#if IS_ENABLED(CONFIG_VIDEO_APPLITE_CAMIF_T4K28)
static int tz3000_rb4_t4k28_camera_power(struct device *dev, int on)
{
	static int use_count = 0;

	if (on) {
		if (!use_count++) {
			gpio_direction_input(1);	/* Hi-Z */
			gpio_direction_input(12);	/* Hi-Z */
			msleep(100);
		}
	} else {
		if (!--use_count) {
			gpio_direction_output(12, 0);	/* Low */
			gpio_direction_output(1, 0);	/* Low */
			msleep(1);
		}
	}
	return 0;
}
#define T4K28_CAMERA_NAME		"t4k28"
#define T4K28_CAMERA_SLAVE	0x3c

static struct i2c_board_info t4k28_camera_info0 = {
	I2C_BOARD_INFO(T4K28_CAMERA_NAME, T4K28_CAMERA_SLAVE),
};
static struct i2c_board_info t4k28_camera_info1 = {
	I2C_BOARD_INFO(T4K28_CAMERA_NAME, T4K28_CAMERA_SLAVE + 1),
};
static struct i2c_board_info t4k28_camera_info2 = {
	I2C_BOARD_INFO(T4K28_CAMERA_NAME, T4K28_CAMERA_SLAVE + 2),
};
static struct i2c_board_info t4k28_camera_info3 = {
	I2C_BOARD_INFO(T4K28_CAMERA_NAME, T4K28_CAMERA_SLAVE + 3),
};

static struct soc_camera_link t4k28_camera_link0 = {
	.bus_id		= 0,
	.i2c_adapter_id	= 1,
	.board_info	= &t4k28_camera_info0,
	.power		= tz3000_rb4_t4k28_camera_power,
};
static struct soc_camera_link t4k28_camera_link1 = {
	.bus_id		= 1,
	.i2c_adapter_id	= 1,
	.board_info	= &t4k28_camera_info1,
	.power		= tz3000_rb4_t4k28_camera_power,
};
static struct soc_camera_link t4k28_camera_link2 = {
	.bus_id		= 2,
	.i2c_adapter_id	= 1,
	.board_info	= &t4k28_camera_info2,
	.power		= tz3000_rb4_t4k28_camera_power,
};
static struct soc_camera_link t4k28_camera_link3 = {
	.bus_id		= 3,
	.i2c_adapter_id	= 1,
	.board_info	= &t4k28_camera_info3,
	.power		= tz3000_rb4_t4k28_camera_power,
};

static struct platform_device t4k28_camera0 = {
	.name   = "soc-camera-pdrv",
	.id     = 0,
	.dev    = {
		.platform_data = &t4k28_camera_link0,
	},
};
static struct platform_device t4k28_camera1 = {
	.name   = "soc-camera-pdrv",
	.id     = 1,
	.dev    = {
		.platform_data = &t4k28_camera_link1,
	},
};
static struct platform_device t4k28_camera2 = {
	.name   = "soc-camera-pdrv",
	.id     = 2,
	.dev    = {
		.platform_data = &t4k28_camera_link2,
	},
};
static struct platform_device t4k28_camera3 = {
	.name   = "soc-camera-pdrv",
	.id     = 3,
	.dev    = {
		.platform_data = &t4k28_camera_link3,
	},
};

/* T4K28 on Andes */
static int tz3000_t4k28_camera_power(struct device *dev, int on)
{
	gpio_set_value(2, on ? 1 : 0);
	return 0;
}

static struct i2c_board_info t4k28_info = {
	I2C_BOARD_INFO("t4k28", 0x3c),
};

static struct soc_camera_link t4k28_link = {
	.bus_id		= 0,
	.i2c_adapter_id	= 1,
	.board_info	= &t4k28_info,
	.power		= tz3000_t4k28_camera_power,
};

static struct platform_device t4k28_camera = {
	.name   = "soc-camera-pdrv",
	.id     = 0,
	.dev    = {
		.platform_data = &t4k28_link,
	},
};

#endif


static struct applite_camera_platform_data cam_dummy_pdata = {
	.csirx_unused = true,
};

static struct resource applite_camif_res[] = {
	DEFINE_RES_MEM_NAMED(CPU_CAMIF_REG_BASE, SZ_16K, "camif"),
	DEFINE_RES_MEM_NAMED(CPU_PMU_REG_BASE, CPU_PMU_REG_SIZE, "pmu"),
	DEFINE_RES_IRQ(170),
};

static void __init tz3000_setup_camera(void)
{
	int i, num_camera;
	struct platform_device *pdev;
	struct clk *clk, *clk2;
	int dummy[4] = {0, 0, 0, 0};

	num_camera = 0;
#if IS_ENABLED(CONFIG_VIDEO_APPLITE_CAMIF_AUTO_RB)
	pr_debug("%s: auto select\n", __func__);
	if (machine_is_tz3000rb4()) {
		num_camera = 4;
		platform_device_register(&rb4_camera0);
		platform_device_register(&rb4_camera1);
		platform_device_register(&rb4_camera2);
		platform_device_register(&rb4_camera3);
	} else {
		num_camera = 2;
		platform_device_register(&t4k08_camera);
		dummy[1] = 1;
	}
#endif
#if IS_ENABLED(CONFIG_VIDEO_APPLITE_CAMIF_OV7725_MPD)
	pr_debug("%s: ov7725\n", __func__);
	num_camera = 4;
	platform_device_register(&rb4_camera0);
	platform_device_register(&rb4_camera1);
	platform_device_register(&rb4_camera2);
	platform_device_register(&rb4_camera3);
#endif
#if IS_ENABLED(CONFIG_VIDEO_APPLITE_CAMIF_T4K08)
	pr_debug("%s: T4K08\n", __func__);
	num_camera = 2;
	platform_device_register(&t4k08_camera);
	dummy[1] = 1;
#endif
#if IS_ENABLED(CONFIG_VIDEO_APPLITE_CAMIF_TC358743)
	pr_debug("%s: TC358743\n", __func__);
	num_camera = 1;
	platform_device_register(&tc358743_camera);
#endif

#if IS_ENABLED(CONFIG_VIDEO_APPLITE_CAMIF_T4K28)
	if (machine_is_tz3000rb4()) {
		pr_debug("%s: t4k28 four cameras\n", __func__);
		num_camera = 4;
		platform_device_register(&t4k28_camera0);
		platform_device_register(&t4k28_camera1);
		platform_device_register(&t4k28_camera2);
		platform_device_register(&t4k28_camera3);
	} else {
		num_camera = 2;
		platform_device_register(&t4k28_camera);
		dummy[1] = 1;
	}
#endif

	/* ClockGatingOn_camifSS_0 */
	clk = clk_register_tz_gate_m(NULL, "camifSS_cmn", "pllsys_100", 0,
		__io_address(TZ3000_PMU_BASE + 0x1130), 0x100);

	for (i = 0; i < num_camera; i++) {
		/* ClockGatingOn_camifSS_0 */
		clk_register_clkdev(clk, "camif_common", "applite_cam.%d", i);

		/* ClockGatingOn_camifSS_0 */
		clk2 = clk_register_tz_gate_m(NULL, "camifSS_csr", "pllsys_100", 0,
			__io_address(TZ3000_PMU_BASE + 0x1130), 1<<i);
		clk_register_clkdev(clk2, "camif_csirx", "applite_cam.%d", i);

		pdev = platform_device_register_simple("applite_cam", i,
						applite_camif_res, 3);
		if (pdev) {
			pdev->dev.coherent_dma_mask = DMA_BIT_MASK(32);
#if IS_ENABLED(CONFIG_SOC_CAMERA_TC358743)
			pdev->dev.platform_data = &cam_tc358743_pdata;
#endif
			if (!dummy[i])
				continue;
			pdev->dev.platform_data = &cam_dummy_pdata;
			platform_device_register_simple(
					"applite_dummy_camera", i, NULL, 0);
		}
	}
}
#endif /* IS_ENABLED(CONFIG_VIDEO_APPLITE_CAMIF) */

#if (IS_ENABLED(CONFIG_APPLITE_VEU) || IS_ENABLED(CONFIG_APPLITE_VDU))

static __u32 vcodec_power_refcount = 0;
static int vcodec_power_down(void)
{
	void __iomem *pmu = __io_address(TZ3000_PMU_BASE);
	__u32 reg;

	pr_debug("%s: start(%d)\n", __func__, vcodec_power_refcount);
	if (vcodec_power_refcount == 1) {
		/* Mask Interrupt */
		writel(0x00000001, (pmu + PMU_MASK_INTERRUPT_OFS));
		/* SoftResetOn_vcodecSS_0 */
		writel(0x01010101, (pmu + PMU_SOFTRESETON_VCODECSS_0_OFS));
		/* SoftResetOn_eastpierSS_0 */
		writel(0x03000008, (pmu + PMU_SOFTRESETON_EASTPIERSS_0_OFS));
		/* SeqStatus_PowerOff_VIDEO */
		writel(0x00000001, (pmu + PMU_SEQSTATUS_POWEROFF_VIDEO_OFS));
		/* status inerrupt */
		do {
			reg = readl(pmu + PMU_SEQSTATUS_POWEROFF_VIDEO_OFS);
		} while (reg & 0x1);
		/* clear status */
		writel(0x00000001, (pmu + PMU_STATUS_INTERRUPT_OFS));
	}
	if (vcodec_power_refcount >= 1)
		vcodec_power_refcount--;

	return 0;
}
EXPORT_SYMBOL(vcodec_power_down);

static int vcodec_power_up(void)
{
	void __iomem *pmu = __io_address(TZ3000_PMU_BASE);

	pr_debug("%s: start(%d)\n", __func__, vcodec_power_refcount);
	if (vcodec_power_refcount == 0) {
		/* PowerSwitchOn_VIDEO */
		writel(1, (pmu + PMU_POWERSWITCHON_VIDEO_OFS));
		/* wait 7us */
		udelay(7);
		/* ClockGatingOffForPower_VIDEO */
		writel(1, (pmu + PMU_CLOCKGATINGOFFFORPOWER_VIDEO_OFS));
		/* ClockGatingOff_eastpierSS_0 */
		writel(0x01000000, (pmu + PMU_CLOCKGATINGOFF_EASTPIERSS_0_OFS));
		/* ClockGatingOff_vcodecSS_0 */
		writel(0x01030303, (pmu + PMU_CLOCKGATINGOFF_VCODECSS_0_OFS));
		/* wait 1us */
		udelay(1);
		/* InIsoOff_VIDEO */
		writel(0x00000001, (pmu + PMU_INISOOFF_VIDEO_OFS));
		/* OutIsoOff_VIDEO */
		writel(0x00000001, (pmu + PMU_OUTISOOFF_VIDEO_OFS));
		/* ClockGatingOn_vcodecSS_0 */
		writel(0x01030303, (pmu + PMU_CLOCKGATINGON_VCODECSS_0_OFS));
		/* SoftResetOff_eastpierSS_0 */
		writel(0x03000008, (pmu + PMU_SOFTRESETOFF_EASTPIERSS_0_OFS));
	}
	vcodec_power_refcount++;
	return 0;
}
EXPORT_SYMBOL(vcodec_power_up);


#endif


#if IS_ENABLED(CONFIG_APPLITE_VEU)

#define APPLITE_VEU_RESERVED_ALIGN   SZ_16M
#define APPLITE_VEU_RESERVED_SIZE    SZ_1M

static struct platform_device applite_veu_device = {
	.name = "appliteveu",
	.id   = -1,
	.dev  = {
		.coherent_dma_mask = DMA_BIT_MASK(32),
	},
	.resource      = NULL,
	.num_resources = 0,
};

int __init applite_veu_reserve_memblock(void)
{
	phys_addr_t begin;

	begin = memblock_find_in_range(
		0, MEMBLOCK_ALLOC_ACCESSIBLE,
		APPLITE_VEU_RESERVED_SIZE, APPLITE_VEU_RESERVED_ALIGN);
	if (!begin) {
		printk("%s: memblock_find_in_range failed\n",
                       __FUNCTION__);
		return -ENOMEM;
	}
	if (dma_declare_contiguous(&applite_veu_device.dev,
				APPLITE_VEU_RESERVED_SIZE, begin, 0)) {
		printk("%s: dma_declare_contiguous failed\n",
                       __FUNCTION__);
		return -ENOMEM;
	}
	printk("%s: reserved mem begin = 0x%0x size = 0x%x\n",
                       __FUNCTION__, begin, APPLITE_VEU_RESERVED_SIZE);
	return 0;
}

static void tz3000_setup_veu(void)
{
	struct clk *clk;

	/* setup clock domain */
	/* ClockGatingOn_vcodecSS_0 */
	clk = clk_register_tz_gate_m(NULL, "vcodecSS_veu", "pllsys_100", 0,
			__io_address(TZ3000_PMU_BASE + 0x1140), 0x00030000);
	clk_register_clkdev(clk, "veu", "appliteveu");

	platform_device_register(&applite_veu_device);
}
#endif

#if IS_ENABLED(CONFIG_APPLITE_VDU)

#define APPLITE_VDU_RESERVED_ALIGN   SZ_16M
#define APPLITE_VDU_RESERVED_SIZE    SZ_1M

static struct platform_device applite_vdu_device = {
	.name = "applitevdu",
	.id   = -1,
	.dev  = {
		.coherent_dma_mask = DMA_BIT_MASK(32),
	},
	.resource      = NULL,
	.num_resources = 0,
};

int __init applite_vdu_reserve_memblock(void)
{
	phys_addr_t begin;

	begin = memblock_find_in_range(
		0, MEMBLOCK_ALLOC_ACCESSIBLE,
		APPLITE_VDU_RESERVED_SIZE, APPLITE_VDU_RESERVED_ALIGN);
	if (!begin) {
		printk("%s: memblock_find_in_range failed\n",
			__FUNCTION__);
		return -ENOMEM;
	}
	if (dma_declare_contiguous(&applite_vdu_device.dev,
		APPLITE_VDU_RESERVED_SIZE, begin, 0)) {
		printk("%s: dma_declare_contiguous failed\n",
			__FUNCTION__);
		return -ENOMEM;
	}
	printk("%s: reserved mem begin = 0x%0x size = 0x%x\n",
		__FUNCTION__, begin, APPLITE_VDU_RESERVED_SIZE);
	return 0;
}

static void tz3000_setup_vdu(void)
{
	struct clk *clk;

	/* setup clock domain */
	/* ClockGatingOn_vcodecSS_0 */
	clk = clk_register_tz_gate_m(NULL, "vcodecSS_vdu", "pllsys_100", 0,
			__io_address(TZ3000_PMU_BASE + 0x1140), 0x00000303);
	clk_register_clkdev(clk, "vdu", "applitevdu");

	platform_device_register(&applite_vdu_device);
}

#endif

#if IS_ENABLED(CONFIG_APPLITE_VCONV)

static struct resource applite_vconv_res[] = {
	DEFINE_RES_MEM_NAMED(CPU_VCONV_REG_BASE, CPU_VCONV_REG_SIZE, "vconv"),
	DEFINE_RES_MEM_NAMED(CPU_PMU_REG_BASE, CPU_PMU_REG_SIZE, "pmu"),
	DEFINE_RES_MEM_NAMED(CPU_FDRAMC_REG_BASE, CPU_FDRAMC_REG_SIZE, "fdramc"),
	DEFINE_RES_MEM_NAMED(CPU_ECONF_REG_BASE, CPU_ECONF_REG_SIZE, "econf"),
	DEFINE_RES_IRQ_NAMED(168, "int"),
	DEFINE_RES_IRQ_NAMED(169, "err"),
};
static void tz3000_setup_vconv(void)
{
	struct platform_device *pdev;
	struct clk *clk;
	static u64 dmamask = DMA_BIT_MASK(32);

	/* ClockGatingOn_vconvSS_0 */
	clk = clk_register_tz_gate(NULL, "vconvSS_vconv", "pllsys_100", 0,
			__io_address(TZ3000_PMU_BASE + 0x1150), 0);
	clk_register_clkdev(clk, NULL, "vconv.0");
	pdev = platform_device_register_simple("vconv", 0,
						applite_vconv_res, 6);
	if (pdev) {
		pdev->dev.dma_mask = &dmamask;
		pdev->dev.coherent_dma_mask = dmamask;
	}
}
#endif

#if IS_ENABLED(CONFIG_APPLITE_MIRAGELITE)

static struct resource applite_miragelite_res[] = {
	DEFINE_RES_MEM_NAMED(CPU_PMU_REG_BASE, CPU_PMU_REG_SIZE,  "pmu"),
	DEFINE_RES_MEM_NAMED(CPU_ECONF_REG_BASE, CPU_ECONF_REG_SIZE,  "econf"),
	DEFINE_RES_MEM_NAMED(CPU_GPU_REG_BASE, CPU_GPU_REG_SIZE, "gpu"),
};
static void tz3000_setup_miragelite(void)
{
	struct clk *clk;

	/* ClockGatingOn_gpuSS_0 */
	clk = clk_register_tz_gate(NULL, "gpuSS_gpu", "pllsys_100", 0,
			__io_address(TZ3000_PMU_BASE + 0x1170), 0);
	clk_register_clkdev(clk, "gpu0", "miragelite.0");

	/* ClockGatingOn_eastpierSS_0 */
	clk = clk_register_tz_gate(NULL, "eastpierSS_gpu", "pllsys_100", 0,
			__io_address(TZ3000_PMU_BASE + 0x1100), 8);
	clk_register_clkdev(clk, "gpu1", "miragelite.0");

	platform_device_register_simple("miragelite", 0,
					applite_miragelite_res, 3);
}
#endif


#if IS_ENABLED(CONFIG_APPLITE_IRECOG)

#include <linux/platform_data/applite_irecog.h>
static DEFINE_SPINLOCK(irecog_spinlock);

static inline void irecog_set_clock_bits(int enable,
					 unsigned int *gate_on,
					 unsigned int *gate_off,
					 unsigned int *rst_on,
					 unsigned int *rst_off,
					 int *cnt,
					 unsigned int flag_gate[],
					 unsigned int flag_rst[])
{
	if(enable == APPLITE_IRECOG_CLOCK_ENABLE) {
		if(!(*cnt)++) {
			*gate_off |= flag_gate[1];
			*rst_on   |= flag_rst[0];
			*rst_off  |= flag_rst[1];
		}
	} else {
		if(!--(*cnt)) {
			*gate_on |= flag_gate[0];
			*rst_on  |= flag_rst[0];
			*rst_off |= flag_rst[1];
		}
	}

	if(*cnt < 0) *cnt = 0;
}

static void irecog_clock_enable(unsigned int type, int enable)
{
	static int pyramid_cnt = 0;
	static int hog_cnt     = 0;
	static int filter_cnt  = 0;
	static int affine_cnt  = 0;
	static int hist_cnt    = 0;

	static unsigned int affine_gate[] = {
		PMU_CLOCKGATINGON_IRECOGSS_0_CG_RCLK_AFFINE_MASK |
		PMU_CLOCKGATINGON_IRECOGSS_0_CG_RCLKDIV2_AFFINE_MASK,
		PMU_CLOCKGATINGOFF_IRECOGSS_0_CG_RCLK_AFFINE_MASK |
		PMU_CLOCKGATINGOFF_IRECOGSS_0_CG_RCLKDIV2_AFFINE_MASK
	};
	static unsigned int affine_rst[] = {
		PMU_SOFTRESETON_IRECOGSS_0_SRST_ASYNCRRST_AFFINE_N_MASK,
		PMU_SOFTRESETOFF_IRECOGSS_0_SRST_ASYNCRRST_AFFINE_N_MASK
	};
	static unsigned int filter_gate[] = {
		PMU_CLOCKGATINGON_IRECOGSS_0_CG_FCLK_MASK |
		PMU_CLOCKGATINGON_IRECOGSS_0_CG_ECLK_IRECOG_MASK,
		PMU_CLOCKGATINGOFF_IRECOGSS_0_CG_FCLK_MASK |
		PMU_CLOCKGATINGOFF_IRECOGSS_0_CG_ECLK_IRECOG_MASK
	};
	static unsigned int filter_rst[] = {
		PMU_SOFTRESETON_IRECOGSS_0_SRST_ASYNCFRST_N_MASK,
		PMU_SOFTRESETOFF_IRECOGSS_0_SRST_ASYNCFRST_N_MASK
	};
	static unsigned int hog_gate[] = {
		PMU_CLOCKGATINGON_IRECOGSS_0_CG_RCLK_COHOG0_MASK |
		PMU_CLOCKGATINGON_IRECOGSS_0_CG_RCLK_COHOG1_MASK |
		PMU_CLOCKGATINGON_IRECOGSS_0_CG_RCLKDIV2_COHOG0_MASK |
		PMU_CLOCKGATINGON_IRECOGSS_0_CG_RCLKDIV2_COHOG1_MASK,
		PMU_CLOCKGATINGOFF_IRECOGSS_0_CG_RCLK_COHOG0_MASK |
		PMU_CLOCKGATINGOFF_IRECOGSS_0_CG_RCLK_COHOG1_MASK |
		PMU_CLOCKGATINGOFF_IRECOGSS_0_CG_RCLKDIV2_COHOG0_MASK |
		PMU_CLOCKGATINGOFF_IRECOGSS_0_CG_RCLKDIV2_COHOG1_MASK,
	};
	static unsigned int hog_rst[] = {
		PMU_SOFTRESETON_IRECOGSS_0_SRST_ASYNCRRST_COHOG0_N_MASK |
		PMU_SOFTRESETON_IRECOGSS_0_SRST_ASYNCRRST_COHOG1_N_MASK,
		PMU_SOFTRESETOFF_IRECOGSS_0_SRST_ASYNCRRST_COHOG0_N_MASK |
		PMU_SOFTRESETOFF_IRECOGSS_0_SRST_ASYNCRRST_COHOG1_N_MASK
	};

	static unsigned int pyramid_gate[] = {
		PMU_CLOCKGATINGON_IRECOGSS_0_CG_RCLK_PYM_CNT_MASK |
		PMU_CLOCKGATINGON_IRECOGSS_0_CG_RCLK_PYM_VDM_MASK |
		PMU_CLOCKGATINGON_IRECOGSS_0_CG_RCLK_PYM_Y1_MASK |
		PMU_CLOCKGATINGON_IRECOGSS_0_CG_RCLK_PYM_Y2_MASK |
		PMU_CLOCKGATINGON_IRECOGSS_0_CG_RCLK_PYM_Y3_MASK |
		PMU_CLOCKGATINGON_IRECOGSS_0_CG_RCLK_PYM_Y4_MASK |
		PMU_CLOCKGATINGON_IRECOGSS_0_CG_RCLK_PYM_C1_MASK |
		PMU_CLOCKGATINGON_IRECOGSS_0_CG_RCLK_PYM_C2_MASK |
		PMU_CLOCKGATINGON_IRECOGSS_0_CG_RCLK_PYM_C3_MASK |
		PMU_CLOCKGATINGON_IRECOGSS_0_CG_RCLK_PYM_C4_MASK,
		PMU_CLOCKGATINGOFF_IRECOGSS_0_CG_RCLK_PYM_CNT_MASK |
		PMU_CLOCKGATINGOFF_IRECOGSS_0_CG_RCLK_PYM_VDM_MASK |
		PMU_CLOCKGATINGOFF_IRECOGSS_0_CG_RCLK_PYM_Y1_MASK |
		PMU_CLOCKGATINGOFF_IRECOGSS_0_CG_RCLK_PYM_Y2_MASK |
		PMU_CLOCKGATINGOFF_IRECOGSS_0_CG_RCLK_PYM_Y3_MASK |
		PMU_CLOCKGATINGOFF_IRECOGSS_0_CG_RCLK_PYM_Y4_MASK |
		PMU_CLOCKGATINGOFF_IRECOGSS_0_CG_RCLK_PYM_C1_MASK |
		PMU_CLOCKGATINGOFF_IRECOGSS_0_CG_RCLK_PYM_C2_MASK |
		PMU_CLOCKGATINGOFF_IRECOGSS_0_CG_RCLK_PYM_C3_MASK |
		PMU_CLOCKGATINGOFF_IRECOGSS_0_CG_RCLK_PYM_C4_MASK
	};
	static unsigned int pyramid_rst[] = {
		PMU_SOFTRESETON_IRECOGSS_0_SRST_RRST_PYM_CNT_N_MASK |
		PMU_SOFTRESETON_IRECOGSS_0_SRST_RRST_PYM_VDM_N_MASK |
		PMU_SOFTRESETON_IRECOGSS_0_SRST_RRST_PYM_Y1_N_MASK |
		PMU_SOFTRESETON_IRECOGSS_0_SRST_RRST_PYM_Y2_N_MASK |
		PMU_SOFTRESETON_IRECOGSS_0_SRST_RRST_PYM_Y3_N_MASK |
		PMU_SOFTRESETON_IRECOGSS_0_SRST_RRST_PYM_Y4_N_MASK |
		PMU_SOFTRESETON_IRECOGSS_0_SRST_RRST_PYM_C1_N_MASK |
		PMU_SOFTRESETON_IRECOGSS_0_SRST_RRST_PYM_C2_N_MASK |
		PMU_SOFTRESETON_IRECOGSS_0_SRST_RRST_PYM_C3_N_MASK |
		PMU_SOFTRESETON_IRECOGSS_0_SRST_RRST_PYM_C4_N_MASK,
		PMU_SOFTRESETOFF_IRECOGSS_0_SRST_RRST_PYM_CNT_N_MASK |
		PMU_SOFTRESETOFF_IRECOGSS_0_SRST_RRST_PYM_VDM_N_MASK |
		PMU_SOFTRESETOFF_IRECOGSS_0_SRST_RRST_PYM_Y1_N_MASK |
		PMU_SOFTRESETOFF_IRECOGSS_0_SRST_RRST_PYM_Y2_N_MASK |
		PMU_SOFTRESETOFF_IRECOGSS_0_SRST_RRST_PYM_Y3_N_MASK |
		PMU_SOFTRESETOFF_IRECOGSS_0_SRST_RRST_PYM_Y4_N_MASK |
		PMU_SOFTRESETOFF_IRECOGSS_0_SRST_RRST_PYM_C1_N_MASK |
		PMU_SOFTRESETOFF_IRECOGSS_0_SRST_RRST_PYM_C2_N_MASK |
		PMU_SOFTRESETOFF_IRECOGSS_0_SRST_RRST_PYM_C3_N_MASK |
		PMU_SOFTRESETOFF_IRECOGSS_0_SRST_RRST_PYM_C4_N_MASK
	};

	static unsigned int hist_gate[] = {
		PMU_CLOCKGATINGON_IRECOGSS_0_CG_RCLK_HISTGRAM_MASK |
		PMU_CLOCKGATINGON_IRECOGSS_0_CG_RCLKDIV2_HISTGRAM_MASK,
		PMU_CLOCKGATINGOFF_IRECOGSS_0_CG_RCLK_HISTGRAM_MASK |
		PMU_CLOCKGATINGOFF_IRECOGSS_0_CG_RCLKDIV2_HISTGRAM_MASK
	};
	static unsigned int hist_rst[] = {
		PMU_SOFTRESETON_IRECOGSS_0_SRST_ASYNCRRST_HISTGRAM_N_MASK,
		PMU_SOFTRESETOFF_IRECOGSS_0_SRST_ASYNCRRST_HISTGRAM_N_MASK
	};

	unsigned int gate_on, gate_off, rst_on, rst_off;
	int current_cnt, next_cnt;

	pr_debug("[%s]\n", __func__);

	spin_lock(&irecog_spinlock);

	gate_on  = 0x00000000;
	gate_off = 0x00000000;
	rst_on   = 0x00000000;
	rst_off  = 0x00000000;

	current_cnt = pyramid_cnt + hog_cnt + filter_cnt + affine_cnt;

	if(type & APPLITE_IRECOG_PYRAMID) {
		irecog_set_clock_bits(enable, &gate_on, &gate_off, &rst_on, &rst_off, &pyramid_cnt, pyramid_gate, pyramid_rst);
	}
	if(type & APPLITE_IRECOG_HOG) {
		irecog_set_clock_bits(enable, &gate_on, &gate_off, &rst_on, &rst_off, &hog_cnt, hog_gate, hog_rst);
	}
	if(type & APPLITE_IRECOG_FILTER) {
		irecog_set_clock_bits(enable, &gate_on, &gate_off, &rst_on, &rst_off, &filter_cnt, filter_gate, filter_rst);
	}
	if(type & APPLITE_IRECOG_AFFINE) {
		irecog_set_clock_bits(enable, &gate_on, &gate_off, &rst_on, &rst_off, &affine_cnt, affine_gate, affine_rst);
	}
	if(type & APPLITE_IRECOG_HIST) {
		irecog_set_clock_bits(enable, &gate_on, &gate_off, &rst_on, &rst_off, &hist_cnt, hist_gate, hist_rst);
	}

	next_cnt = pyramid_cnt + hog_cnt + filter_cnt + affine_cnt + hist_cnt;

	/* shread bus */
	if(gate_off  && (current_cnt == 0)) {
		gate_off |= PMU_CLOCKGATINGOFF_IRECOGSS_0_CG_RCLK_SHAREDBUS_MASK;
		rst_on   |= PMU_SOFTRESETON_IRECOGSS_0_SRST_RRST_SHAREDBUS_N_MASK;
		rst_off  |= PMU_SOFTRESETOFF_IRECOGSS_0_SRST_RRST_SHAREDBUS_N_MASK;
	}
	if(gate_on && (next_cnt == 0)) {
		gate_on |= PMU_CLOCKGATINGOFF_IRECOGSS_0_CG_RCLK_SHAREDBUS_MASK;
		rst_on  |= PMU_SOFTRESETON_IRECOGSS_0_SRST_RRST_SHAREDBUS_N_MASK;
		rst_off |= PMU_SOFTRESETOFF_IRECOGSS_0_SRST_RRST_SHAREDBUS_N_MASK;
	}

	spin_unlock(&irecog_spinlock);

	if(gate_off) {
		 writel(rst_on  , __io_address(CPU_PMU_REG_BASE + PMU_SOFTRESETON_IRECOGSS_0_OFS));
		 writel(gate_off, __io_address(CPU_PMU_REG_BASE + PMU_CLOCKGATINGOFF_IRECOGSS_0_OFS));
		 writel(rst_off , __io_address(CPU_PMU_REG_BASE + PMU_SOFTRESETOFF_IRECOGSS_0_OFS));
		 pr_debug(" enable:%d clk_on:0x%x\n", enable, gate_off);
	}
	if(gate_on) {
		writel(rst_on , __io_address(CPU_PMU_REG_BASE + PMU_SOFTRESETON_IRECOGSS_0_OFS));
		writel(gate_on, __io_address(CPU_PMU_REG_BASE + PMU_CLOCKGATINGON_IRECOGSS_0_OFS));
		pr_debug(" enable:%d clk_off:0x%x\n", enable, gate_on);
	}

	pr_debug(" ref_cnt pyramid:%d hog:%d filter:%d affine:%d hist:%d\n", pyramid_cnt, hog_cnt, filter_cnt, affine_cnt, hist_cnt);

	pr_debug(" pmu_clk_gating_on_reg :0x%08x\n",
			 readl(__io_address(CPU_PMU_REG_BASE + PMU_CLOCKGATINGON_IRECOGSS_0_OFS)));
	pr_debug(" pmu_clk_gating_off_reg:0x%08x\n",
			 readl(__io_address(CPU_PMU_REG_BASE + PMU_CLOCKGATINGOFF_IRECOGSS_0_OFS)));

}

static struct applite_irecog_platform_data irecog_platform_data = {
  .clock_enable = irecog_clock_enable,
};

static struct platform_device irecog_pyramid_device = {
	.name = "irecog_pyramid",
	.resource      = NULL,
	.num_resources = 0,
	.dev= {
    		.platform_data= &irecog_platform_data,
  	},
};
static struct platform_device irecog_hog_device = {
	.name = "irecog_hog",
	.resource      = NULL,
	.num_resources = 0,
	.dev= {
    		.platform_data= &irecog_platform_data,
  	},
};
static struct platform_device irecog_filter_device = {
	.name = "irecog_filter",
	.resource      = NULL,
	.num_resources = 0,
	.dev= {
    		.platform_data= &irecog_platform_data,
  	},
};
static struct platform_device irecog_affine_device = {
	.name = "irecog_affine",
	.resource      = NULL,
	.num_resources = 0,
	.dev= {
    		.platform_data= &irecog_platform_data,
  	},
};
static struct platform_device irecog_gdmac_pyramid_device = {
	.name = "irecog_gdmac_pyramid",
	.resource      = NULL,
	.num_resources = 0,
	.dev= {
    		.platform_data= &irecog_platform_data,
  	},
};
static struct platform_device irecog_gdmac_hand_detect_isolate_device = {
	.name = "irecog_gdmac_hand_detect_isolate",
	.resource      = NULL,
	.num_resources = 0,
	.dev= {
		.platform_data= &irecog_platform_data,
	},
};
static struct platform_device irecog_hist_device = {
	.name = "irecog_hist",
	.resource      = NULL,
	.num_resources = 0,
	.dev= {
		.platform_data= &irecog_platform_data,
	},
};

#define IRECOG_TIMEOUT 1000
void init_irecog(void)
{
	unsigned long speed_setting = 0x01;
	unsigned int ret;
	unsigned long deadline;

	/* eastwing setup */
	writel(0x00030004, __io_address(CPU_PMU_REG_BASE + PMU_SOFTRESETON_EASTPIERSS_0_OFS));
	writel(0x0003000f, __io_address(CPU_PMU_REG_BASE + PMU_CLOCKGATINGOFF_EASTPIERSS_0_OFS));
	writel(0x0003000f, __io_address(CPU_PMU_REG_BASE + PMU_SOFTRESETOFF_EASTPIERSS_0_OFS));

	/* irecog setup  */
	writel(0x0001ffff, __io_address(CPU_PMU_REG_BASE + PMU_SOFTRESETON_IRECOGSS_0_OFS));
	/* clock setting */
	writel(speed_setting, __io_address(CPU_PMU_REG_BASE + PMU_FREQUENCY_IRECOGSS_OFS));
	writel(0x1, __io_address(CPU_PMU_REG_BASE + PMU_SEQSTATUS_DFS_IRECOGSS_OFS));

	/* dfs setting */
	ret = readl(__io_address(CPU_PMU_REG_BASE + PMU_SEQSTATUS_DFS_IRECOGSS_OFS));
	deadline = jiffies + msecs_to_jiffies(IRECOG_TIMEOUT);

	while((ret & PMU_SEQSTATUS_DFS_IRECOGSS_SEQSTATUS_DFS_IRECOGSS_MASK) != 0x0
		  && time_before(jiffies, deadline)) {
		ret = readl(__io_address(CPU_PMU_REG_BASE + PMU_SEQSTATUS_DFS_IRECOGSS_OFS));
	}
	if(ret != 0x00) {
	  pr_warning(" %s irecog dfs setting fail.\n", __func__);
	}

	/* clock gating on */
	writel(0x007fffff, __io_address(CPU_PMU_REG_BASE + PMU_CLOCKGATINGON_IRECOGSS_0_OFS));
}


static void tz3000_setup_irecog(void)
{
	init_irecog();

	platform_device_register(&irecog_pyramid_device);
	platform_device_register(&irecog_hog_device);
	platform_device_register(&irecog_filter_device);
	platform_device_register(&irecog_affine_device);
	platform_device_register(&irecog_gdmac_pyramid_device);
	platform_device_register(&irecog_gdmac_hand_detect_isolate_device);
	platform_device_register(&irecog_hist_device);
}
#endif

#if IS_ENABLED(CONFIG_FB_TZ3000)
/*Interruption number*/
#define IRQ_DISPIF1(x)		(176 + (x))/* 176 - 183 */
#define IRQ_DISPIF2(x)		(248 + (x))/* 248 - 249 */

static void tz3000_setup_dispif(void)
{
#if IS_ENABLED(CONFIG_FB_APPLITE_BASIC)
	struct platform_device *pdev;
	static u64 dmamask = DMA_BIT_MASK(32);
	static struct resource r[] = {
		[0] = DEFINE_RES_MEM(CPU_PMU_REG_BASE, CPU_PMU_REG_SIZE),
		[1] = DEFINE_RES_MEM(CPU_DISPIF_REG_BASE, CPU_DISPIF_REG_SIZE),
		[2] = DEFINE_RES_IRQ(IRQ_DISPIF1(0)),
		[3] = DEFINE_RES_IRQ(IRQ_DISPIF1(1)),
		[4] = DEFINE_RES_IRQ(IRQ_DISPIF1(2)),
		[5] = DEFINE_RES_IRQ(IRQ_DISPIF1(3)),
		[6] = DEFINE_RES_IRQ(IRQ_DISPIF1(4)),
		[7] = DEFINE_RES_IRQ(IRQ_DISPIF1(5)),
		[8] = DEFINE_RES_IRQ(IRQ_DISPIF1(6)),
		[9] = DEFINE_RES_IRQ(IRQ_DISPIF1(7)),
		[10] = DEFINE_RES_IRQ(IRQ_DISPIF2(0)),
		[11] = DEFINE_RES_IRQ(IRQ_DISPIF2(1)),
	};
	struct clk *clk;

	/* ClockGatingOn_dispifSS_0 */
	clk = clk_register_tz_gate_m(NULL, "dispifSS", "pllsys_100", 0,
			__io_address(TZ3000_PMU_BASE + 0x1120), 0x00000101);
	clk_register_clkdev(clk, "dispif", "tz3000fb.0");
	pdev = platform_device_register_simple("tz3000fb", 0, r, 12);
	if (pdev) {
		pdev->dev.dma_mask = &dmamask;
		pdev->dev.coherent_dma_mask = dmamask;
	}
#elif IS_ENABLED(CONFIG_FB_APPLITE_STANDARD)
	struct platform_device *pdev;
	static u64 dmamask = DMA_BIT_MASK(32);
	static struct resource r[] = {
		[0] = DEFINE_RES_MEM(CPU_PMU_REG_BASE, CPU_PMU_REG_SIZE),
		[1] = DEFINE_RES_MEM(CPU_DISPIF_REG_BASE, CPU_DISPIF_REG_SIZE),
		[2] = DEFINE_RES_IRQ(IRQ_DISPIF1(0)),
		[3] = DEFINE_RES_IRQ(IRQ_DISPIF1(1)),
		[4] = DEFINE_RES_IRQ(IRQ_DISPIF1(2)),
		[5] = DEFINE_RES_IRQ(IRQ_DISPIF1(3)),
		[6] = DEFINE_RES_IRQ(IRQ_DISPIF1(4)),
		[7] = DEFINE_RES_IRQ(IRQ_DISPIF1(5)),
		[8] = DEFINE_RES_IRQ(IRQ_DISPIF1(6)),
		[9] = DEFINE_RES_IRQ(IRQ_DISPIF1(7)),
		[10] = DEFINE_RES_IRQ(IRQ_DISPIF2(0)),
		[11] = DEFINE_RES_IRQ(IRQ_DISPIF2(1)),
	};
	struct clk *clk;

	/* ClockGatingOn_dispifSS_0 */
	clk = clk_register_tz_gate_m(NULL, "dispifSS", "pllsys_100", 0,
			__io_address(TZ3000_PMU_BASE + 0x1120), 0x00000101);
	clk_register_clkdev(clk, "lcdc", "applitefb.0");
	pdev = platform_device_register_simple("applitefb", 0, r, 12);
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
static struct resource al_i2s_resources1[] = {
	DEFINE_RES_MEM(CPU_I2SO_REG_BASE + 0x1000, 0x1000),
	DEFINE_RES_MEM(CPU_I2SI_REG_BASE + 0x1000, 0x1000),
	DEFINE_RES_MEM(CPU_I2SC_REG_BASE, 0x100),
	DEFINE_RES_MEM(CPU_GCONF_REG_BASE, 0x1000),
	DEFINE_RES_MEM(CPU_PMU_REG_BASE, 0x10000),
	DEFINE_RES_IRQ(IRQ_I2SO1_INT),
	DEFINE_RES_IRQ(IRQ_I2SO1_ERR),
	DEFINE_RES_IRQ(IRQ_I2SI1_INT),
	DEFINE_RES_IRQ(IRQ_I2SI1_ERR),
};

/* id 0:I2S0 */
static struct platform_device snd_soc_applite_device0 = {
	.name		= "applite-i2s",
	.id		= 0,
	.resource	= al_i2s_resources0,
	.num_resources	= ARRAY_SIZE(al_i2s_resources0),
};
/* id 1:I2S1 */
static struct platform_device snd_soc_applite_device1 = {
	.name		= "applite-i2s",
	.id		= 1,
	.resource	= al_i2s_resources1,
	.num_resources	= ARRAY_SIZE(al_i2s_resources1),
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

#define SCOMM_REG_SIZE	(0x1000)
#define IRQ_SCOMM(x)	(32+(x))	/* 32 - 35 */

static void tz3000_setup_syscon(void)
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

#define IRQ_USB2DC 208

static void __init tz3000_udc_init(void)
{
	struct platform_device *pdev;
	static u64 dmamask = DMA_BIT_MASK(32);
	void __iomem *econf_reg_base;

	econf_reg_base = ioremap(TZ3000_ECONF_BASE, SZ_64K);

	if (machine_is_tz3000eva()) {
		switch (readl(__io_address(TZ3000_GP_DR(0))) & 0xc0) {
		case 0x00: /* Disable */
			break;
		case 0x80: /* PCIe + USB2D */
			pr_info("TZ3000 USB2DC Selected\n");
			/* 3.USB2D Clock on */
			writel(0x11, __io_address(CPU_PMU_REG_BASE + PMU_CLOCKGATINGOFF_HSIOSS_0_OFS));
			/* 6.USB2PHY Setting */
			writel(0x49082e08, econf_reg_base + ECONF_USB2PHY_CONFIG0_OFS);
			writel(0x1, econf_reg_base + ECONF_USB2PHY_CONFIG1_OFS);
			/* 7.MUX Select USB2D not USB2H */
			writel(0x10003, econf_reg_base + ECONF_HSIO_MUX_CTL_OFS);
			/* 8.USB2D Reset release */
			writel(0x1, __io_address(CPU_PMU_REG_BASE + PMU_SOFTRESETOFF_HSIOSS_0_OFS));
			udelay(500);
			writel(0x11, __io_address(CPU_PMU_REG_BASE + PMU_SOFTRESETOFF_HSIOSS_0_OFS));
			udelay(100);
			writel(0x111, __io_address(CPU_PMU_REG_BASE + PMU_SOFTRESETOFF_HSIOSS_0_OFS));

			pdev = register_platform_resource(0, "applite-udc",
						IRQ_USB2DC,
						CPU_USB2DC_REG_BASE, SZ_4K);
			if (pdev) {
				pdev->dev.dma_mask = &dmamask;
				pdev->dev.coherent_dma_mask = dmamask;
			}
			break;
		case 0x40: /* USB3H */
		case 0xc0: /* PCIe + USB3H(HS) */
			break;
		}
	}

	if (machine_is_tz3000rb() ||
	    machine_is_tz3000rb2()) {
		pr_info("TZ3000 USB2DC Selected\n");
		/* 3.USB2D Clock on */
		writel(0x11, __io_address(CPU_PMU_REG_BASE + PMU_CLOCKGATINGOFF_HSIOSS_0_OFS));
		/* 6.USB2PHY Setting */
		writel(0x49082e08, econf_reg_base + ECONF_USB2PHY_CONFIG0_OFS);
		writel(0x1, econf_reg_base + ECONF_USB2PHY_CONFIG1_OFS);
		/* 7.MUX Select USB2D not USB2H */
		writel(0x10003, econf_reg_base + ECONF_HSIO_MUX_CTL_OFS);
		/* 8.USB2D Reset release */
		writel(0x1, __io_address(CPU_PMU_REG_BASE + PMU_SOFTRESETOFF_HSIOSS_0_OFS));
		udelay(500);
		writel(0x11, __io_address(CPU_PMU_REG_BASE + PMU_SOFTRESETOFF_HSIOSS_0_OFS));
		udelay(100);
		writel(0x111, __io_address(CPU_PMU_REG_BASE + PMU_SOFTRESETOFF_HSIOSS_0_OFS));

		pdev = register_platform_resource(0, "applite-udc",
						IRQ_USB2DC,
						CPU_USB2DC_REG_BASE, SZ_4K);
		if (pdev) {
			pdev->dev.dma_mask = &dmamask;
			pdev->dev.coherent_dma_mask = dmamask;
		}
	}
}

#endif

#if IS_ENABLED(CONFIG_APPLITE_SADC)
static void __init tz3000_sadc_init(void)
{
	struct platform_device *pdev;
        struct clk *clk;
	static struct resource r[] = {
		[0] = DEFINE_RES_MEM(CPU_SADC_REG_BASE, CPU_SADC_REG_SIZE),
		[1] = DEFINE_RES_MEM(CPU_PMU_REG_BASE, CPU_PMU_REG_SIZE),
	};

	/* ClockGatingOn_periSS_1 */
	clk = clk_register_tz_gate(NULL, "periSS_adc", "pllsys_100", 0,
				__io_address(TZ3000_PMU_BASE + 0x1024), 8);
	clk_register_clkdev(clk, NULL, "applite-sadc.0");

	pdev = platform_device_register_simple("applite-sadc", 0, r, 2);
	pr_debug("TZ3000 Slow AD register resource = 0x%0x\n", CPU_SADC_REG_BASE);
	return;
}
#endif

#if IS_ENABLED(CONFIG_APPLITE_PWM)
#define IRQ_PWM	99
static void __init tz3000_pwm_init(void)
{
	struct platform_device *pdev;
        struct clk *clk;
	static struct resource r[] = {
		[0] = DEFINE_RES_MEM(CPU_PWM_REG_BASE, CPU_PWM_REG_SIZE),
		[1] = DEFINE_RES_MEM(CPU_PMU_REG_BASE, CPU_PMU_REG_SIZE),
		[2] = DEFINE_RES_IRQ(IRQ_PWM),
	};

	/* ClockGatingOn_periSS_1 */
	clk = clk_register_tz_gate(NULL, "periSS_pwm", "pllsys_100", 0,
				__io_address(TZ3000_PMU_BASE + 0x1024), 0);
	clk_register_clkdev(clk, NULL, "applite-pwm.0");

	pdev = platform_device_register_simple("applite-pwm", 0, r, 3);
	pr_debug("TZ3000 PWM register resource = 0x%0x\n", CPU_PWM_REG_BASE);
	return;
}
#endif

void tz3000_setup_gdmac(void)
{
	writel(BIT(8), __io_address(CPU_PMU_REG_BASE + PMU_SOFTRESETON_PERISS_0_OFS));
	writel(BIT(8), __io_address(CPU_PMU_REG_BASE + PMU_CLOCKGATINGOFF_PERISS_0_OFS));

	writel(BIT(0), __io_address(CPU_GCONF_REG_BASE + GCONF_GDMAC_CTRL0_OFS));
	writel(0, __io_address(CPU_GCONF_REG_BASE + GCONF_GDMAC_CTRL1_OFS));
	writel(0, __io_address(CPU_GCONF_REG_BASE + GCONF_GDMAC_CTRL2_OFS));
	writel(0, __io_address(CPU_GCONF_REG_BASE + GCONF_GDMAC_CTRL3_OFS));
	writel(0, __io_address(CPU_GCONF_REG_BASE + GCONF_GDMAC_CTRL4_OFS));
	writel(0, __io_address(CPU_GCONF_REG_BASE + GCONF_GDMAC_CTRL5_OFS));

	writel(BIT(8), __io_address(CPU_PMU_REG_BASE + PMU_SOFTRESETOFF_PERISS_0_OFS));
}

static void __init tz3000_show_revision(void)
{
	u32 rev0, rev1;
	rev0 = readl(__io_address(TZ3000_BOOTINFO_FWREV0));
	rev1 = readl(__io_address(TZ3000_BOOTINFO_FWREV1));
	pr_info("TOSHIBA TZ3000 botfw:%x.%x\n", rev0, rev1);
}

static void tz3000_setup_pmu(void)
{
	static struct resource pmu_resources[] = {
		[0] = {
			.start = IRQ_PMU_CPU(0),
			.flags = IORESOURCE_IRQ,
		},
		[1] = {
			.start = IRQ_PMU_CPU(1),
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

static int tz3000_pllclk = TZ3000_PLLCLK;
static int txss_periphclk = TXSS_PERIPHCLK;
static void __init tz3000_detect_clock(void)
{
	static struct {
		int pllclk;
		unsigned int conf0, conf1;
	} pllconfigs[] = {
		{ 1000000000, 0x27183000, 0x00000027 },
		{  800000000, 0x27133000, 0x0000001f },
		{  600000000, 0x270e3000, 0x00000017 },
		{  400000000, 0x27133000, 0x1000001f },
		{  200000000, 0x27133000, 0x1001001f },
		{  100000000, 0x27133000, 0x1003001f },
	};
	unsigned int conf0, conf1;
	int i;

	/* delect pll*/
	conf0 = readl(__io_address(TZ3000_PMU_PLLCONFIG_PLLCPU_0));
	conf1 = readl(__io_address(TZ3000_PMU_PLLCONFIG_PLLCPU_1));
	for (i = 0; i < ARRAY_SIZE(pllconfigs); i++) {
		if (pllconfigs[i].conf0 == conf0 &&
		    pllconfigs[i].conf1 == conf1) {
			tz3000_pllclk = pllconfigs[i].pllclk;
			txss_periphclk = pllconfigs[i].pllclk / 16;
			pr_info("TOSHIBA TZ3000 PLLCLK %dHz\n",
				pllconfigs[i].pllclk);
			break;
		}
	}
}

/* Early initializations */
static void __init tz3000_init_early(void)
{
	tz3000_detect_clock();
	gtmr_setup(__io_address(TZ3000_GLOBAL_TMR_BASE),
		   IRQ_GLOBALTIMER, txss_periphclk);
	gtmr_sched_clock_init();
}

static struct gpio tz3000_eva_gpios[] = {
	{ .gpio = 0, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 1, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 2, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 3, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 4, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 5, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 6, .flags = GPIOF_IN, },
	{ .gpio = 7, .flags = GPIOF_IN, },
	{ .gpio = 54, .flags = GPIOF_IN, },
	{ .gpio = 55, .flags = GPIOF_OUT_INIT_LOW, },
	{ .gpio = 56, .flags = GPIOF_IN, },
	{ .gpio = 57, .flags = GPIOF_IN, },
	{ .gpio = 58, .flags = GPIOF_IN, },
	{ .gpio = 59, .flags = GPIOF_IN, },
};
static struct gpio_led tz3000_eva_gpio_leds[] = {
	{ .gpio = 14, },
	{ .gpio = 15, },
	{ .gpio = 21, },
	{ .gpio = 28, },
	{ .gpio = 45, },
	{ .gpio = 46, },
	{ .gpio = 47, },
	{ .gpio = 48, },
};

static struct gpio tz3000_rb_gpios[] = {
	{ .gpio = 0, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 1, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 2, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 3, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 4, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 5, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 6, .flags = GPIOF_OUT_INIT_LOW, },
	{ .gpio = 7, .flags = GPIOF_IN, },
	{ .gpio = 21, .flags = GPIOF_IN, },
	{ .gpio = 54, .flags = GPIOF_IN, },
	{ .gpio = 55, .flags = GPIOF_OUT_INIT_LOW, },
};
static struct gpio_led tz3000_rb_gpio_leds[] = {
	{ .gpio = 14, },
	{ .gpio = 15, },
	{ .gpio = 28, },
	{ .gpio = 45, },
	{ .gpio = 56, },
	{ .gpio = 57, },
	{ .gpio = 58, },
	{ .gpio = 59, },
};

static struct gpio tz3000_rb2_gpios[] = {
	{ .gpio = 2, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 4, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 16, .flags = GPIOF_IN, },
	{ .gpio = 17, .flags = GPIOF_OUT_INIT_LOW, },
	{ .gpio = 62, .flags = GPIOF_OUT_INIT_HIGH, },
};
static struct gpio_led tz3000_rb2_gpio_leds[] = {
	{ .gpio = 14, },
	{ .gpio = 56, },
};

static struct gpio tz3000_rb3_gpios[] = {
	{ .gpio = 0, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 2, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 4, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 5, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 7, .flags = GPIOF_IN, },
	{ .gpio = 54, .flags = GPIOF_IN, },
};
static struct gpio_led tz3000_rb3_gpio_leds[] = {
	{ .gpio = 14, },
	{ .gpio = 56, },
};

static struct gpio tz3000_rb4_gpios[] = {
	{ .gpio = 0, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 1, .flags = GPIOF_IN, },
	{ .gpio = 2, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 3, .flags = GPIOF_IN, },
	{ .gpio = 4, .flags = GPIOF_IN, },
	{ .gpio = 6, .flags = GPIOF_OUT_INIT_LOW, },
	{ .gpio = 7, .flags = GPIOF_OUT_INIT_LOW, },
	{ .gpio = 8, .flags = GPIOF_IN, },
	{ .gpio = 9, .flags = GPIOF_IN, },
	{ .gpio = 10, .flags = GPIOF_IN, },
	{ .gpio = 11, .flags = GPIOF_OUT_INIT_HIGH, },
	{ .gpio = 12, .flags = GPIOF_OUT_INIT_LOW, },
	{ .gpio = 13, .flags = GPIOF_IN, },
	{ .gpio = 14, .flags = GPIOF_IN, },
	{ .gpio = 15, .flags = GPIOF_IN, },
	{ .gpio = 16, .flags = GPIOF_IN, },
	{ .gpio = 17, .flags = GPIOF_IN, },
	{ .gpio = 18, .flags = GPIOF_IN, },
	{ .gpio = 19, .flags = GPIOF_IN, },
	{ .gpio = 20, .flags = GPIOF_IN, },
	{ .gpio = 22, .flags = GPIOF_IN, },
	{ .gpio = 23, .flags = GPIOF_IN, },
	{ .gpio = 24, .flags = GPIOF_IN, },
	{ .gpio = 25, .flags = GPIOF_IN, },
	{ .gpio = 26, .flags = GPIOF_IN, },
	{ .gpio = 27, .flags = GPIOF_IN, },
	{ .gpio = 28, .flags = GPIOF_IN, },
	{ .gpio = 46, .flags = GPIOF_IN, },
	{ .gpio = 47, .flags = GPIOF_IN, },
	{ .gpio = 48, .flags = GPIOF_IN, },
};
static struct gpio_led tz3000_rb4_gpio_leds[] = {
	{ .gpio = 5, },
	{ .gpio = 21, },
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

#ifdef CONFIG_TZ3000_SGPIO
static u32 gp2_smp = 0xffffffff;
static int __init early_gp2_smp(char *p)
{
	return p ? kstrtouint(p, 0, &gp2_smp) : 0;
}
early_param("gp2_smp", early_gp2_smp);
#endif

#if IS_ENABLED(CONFIG_LEDS_GPIO)
static int use_leds_gpio;
static int __init early_use_leds_gpio(char *p)
{
	use_leds_gpio = 1;
	return 0;
}
early_param("use_leds_gpio", early_use_leds_gpio);
#endif

static __init void tz3000_gpio_board_init(void)
{
	int ret;
	int i;
	struct gpio *gpios = NULL;
	int n = 0;
	struct gpio_led *leds = NULL;
	int num_leds = 0;

#ifdef CONFIG_TZ3000_SGPIO
	void __iomem *sgpio;
	sgpio = ioremap(TZ3000_SGPIO_BASE, 0x1000);
	if (gp2_smp != 0xffffffff)
		writel(gp2_smp, sgpio + 0x30); /* SMP */
	writel(0x000000ff, sgpio + 0x58); /* IMPEN */
	iounmap(sgpio);
	for (i = 0; i < 8; i++) {
		gpio_request_one(64 + i, GPIOF_IN, NULL);
		gpio_export(64 + i, true);
	}
#endif
	if (machine_is_tz3000eva()) {
		gpios = tz3000_eva_gpios;
		n = ARRAY_SIZE(tz3000_eva_gpios);
		leds = tz3000_eva_gpio_leds;
		num_leds = ARRAY_SIZE(tz3000_eva_gpio_leds);
	}
	if (machine_is_tz3000rb() || machine_is_tz3000rb_old()) {
		gpios = tz3000_rb_gpios;
		n = ARRAY_SIZE(tz3000_rb_gpios);
		leds = tz3000_rb_gpio_leds;
		num_leds = ARRAY_SIZE(tz3000_rb_gpio_leds);
	}
	if (machine_is_tz3000rb2()) {
		gpios = tz3000_rb2_gpios;
		n = ARRAY_SIZE(tz3000_rb2_gpios);
		leds = tz3000_rb2_gpio_leds;
		num_leds = ARRAY_SIZE(tz3000_rb2_gpio_leds);
	}
	if (machine_is_tz3000rb3()) {
		gpios = tz3000_rb3_gpios;
		n = ARRAY_SIZE(tz3000_rb3_gpios);
		leds = tz3000_rb3_gpio_leds;
		num_leds = ARRAY_SIZE(tz3000_rb3_gpio_leds);
	}
	if (machine_is_tz3000rb4()) {
		gpios = tz3000_rb4_gpios;
		n = ARRAY_SIZE(tz3000_rb4_gpios);
		leds = tz3000_rb4_gpio_leds;
		num_leds = ARRAY_SIZE(tz3000_rb4_gpio_leds);
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

static void tz3000_gpio_init(unsigned int id,
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

static void tz3000_setup_cpufreq(void)
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
	cpufreq_pdata.pllclk = tz3000_pllclk;
	cpufreq_pdata.clkdiv_reg = __io_address(TZ3000_PMU_BASE + 0x4404);
	platform_device_register(&cpufreq_device);
#endif
}

static void __iomem *mbox_base;
static void tz3000_poweroff(void)
{
	if (mbox_base)
		writel(0x80, mbox_base + 4);
}

static void tz3000_restart(char mode, const char *cmd)
{
	if (mbox_base)
		writel(0x90, mbox_base + 4);
}

void tz3000_enter_suspend(void)
{
	if (mbox_base)
		writel(0xa0, mbox_base + 4);
}
static void __init tz3000_init(void)
{
	int i;

	mbox_base = ioremap(TZ3000_MBOX_BASE, SZ_4K);
	tz3000_show_revision();
	clk_register_fixed_rate(NULL, "pllsys_50", NULL, CLK_IS_ROOT, 50000000);
	clk_register_fixed_rate(NULL, "pllsys_100", NULL, CLK_IS_ROOT,
				100000000);
	if (gp0_smp != 0xffffffff)
		writel(gp0_smp, __io_address(TZ3000_GP_SMP(0)));
	if (gp1_smp != 0xffffffff)
		writel(gp1_smp, __io_address(TZ3000_GP_SMP(1)));
	for (i = 0; i < 2; i++)
		tz3000_gpio_init(i, i * 32, 32,
				 TZ3000_GPIO_BASE + i * 0x1000,
				 IRQ_GPIO(i), IRQ_GPIO_START + i * 32);
#ifdef CONFIG_TZ3000_SGPIO
	tz3000_gpio_init(2, 2 * 32, 8,
			 TZ3000_SGPIO_BASE, IRQ_SGPIO, IRQ_GPIO_START + 2 * 32);
#endif
	tz3000_gpio_board_init();

	/* L2 cache init */
#ifdef CONFIG_CACHE_L2X0
	tz3000_pl310_init();
#endif
	/* serial setup */
#ifdef CONFIG_SERIAL_8250
	tz3000_setup_serial();
#endif
	/* tz3000 ethermac setup */
#if defined(CONFIG_TXSSETH) || defined(CONFIG_TXSSETH_MODULE)
	tz3000_setup_ethermac();
#endif
	/* tz3000 spi setup */
#if defined(CONFIG_SPI_TC90431) || defined(CONFIG_SPI_TC90431_MODULE)
	tz3000_setup_spi();
#endif
#if IS_ENABLED(CONFIG_SPI_TZ_SPIMS)
	tz3000_setup_spims();
#endif

#if defined(CONFIG_MTD_NAND_TC90431_HAMMING) || \
	 defined(CONFIG_MTD_NAND_TC90431_HAMMING_MODULE)
	/* tz3000 hamming nand setup */
	tz3000_ham_setup_nand();
#endif

#if IS_ENABLED(CONFIG_I2C_DESIGNWARE_PLATFORM)
	tz3000_setup_i2c();
#endif
#if IS_ENABLED(CONFIG_MMC_SDHCI_TZ3000)
	tz3000_sdhc_init();
#endif
#if IS_ENABLED(CONFIG_USB_XHCI_HCD)
	tz3000_usb_init();
#endif
	tz3000_setup_pmu();
	tz3000_setup_cpufreq();
	tz3000_setup_gdmac();
#if IS_ENABLED(CONFIG_VIDEO_APPLITE_CAMIF)
	tz3000_setup_camera();
#endif
#if IS_ENABLED(CONFIG_APPLITE_IRECOG)
	tz3000_setup_irecog();
#endif
#if IS_ENABLED(CONFIG_FB_TZ3000)
	tz3000_setup_dispif();
#endif
#if IS_ENABLED(CONFIG_APPLITE_VEU)
	tz3000_setup_veu();
#endif
#if IS_ENABLED(CONFIG_APPLITE_VDU)
	tz3000_setup_vdu();
#endif
#if IS_ENABLED(CONFIG_APPLITE_VCONV)
	tz3000_setup_vconv();
#endif
#if IS_ENABLED(CONFIG_APPLITE_MIRAGELITE)
	tz3000_setup_miragelite();
#endif
#if IS_ENABLED(CONFIG_SND_APPLITE_SOC)
{
	struct clk *clk;

	/* ClockGatingOn_periSS_2 */
	clk = clk_register_tz_gate_m(NULL, "periSS_i2si0", "pllsys_100", 0,
			__io_address(TZ3000_PMU_BASE + 0x1028), 0x11011111);
	clk_register_clkdev(clk, "i2s", "applite-i2s.0");
	clk_register_clkdev(clk, "i2s", "applite-i2s.1");
}

	platform_device_register(&snd_soc_applite_device0);
	platform_device_register(&snd_soc_applite_device1);
	platform_device_register(&snd_soc_appilte_pcm_device);
	platform_device_register(&snd_soc_applite_tzxxx_device);
#endif
#if IS_ENABLED(CONFIG_USB_APPLITE_UDC)
	tz3000_udc_init();
#endif
#if IS_ENABLED(CONFIG_APPLITE_SYSCON)
	tz3000_setup_syscon();
#endif
#if IS_ENABLED(CONFIG_APPLITE_SADC)
	tz3000_sadc_init();
#endif
#if IS_ENABLED(CONFIG_APPLITE_PWM)
	tz3000_pwm_init();
#endif

	pm_power_off = tz3000_poweroff;
}

#ifdef CONFIG_HAVE_ARM_TWD
static DEFINE_TWD_LOCAL_TIMER(twd_local_timer,
			      TZ3000_PRIVATE_TMR_BASE,
			      IRQ_LOCALTIMER);

static void __init tz3000_twd_init(void)
{
	int err = twd_local_timer_register(&twd_local_timer);
	if (err)
		pr_err("twd_local_timer_register failed %d\n", err);
}
#else
#define tz3000_twd_init()	do { } while (0)
#endif

static void __init tz3000_timer_init(void)
{
	gtmr_clocksource_init();
	gtmr_tick_setup();
	tz3000_twd_init();
}

static struct sys_timer tz3000_timer = {
	.init = tz3000_timer_init,
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

void __init tz3000_reserve(void)
{
#if IS_ENABLED(CONFIG_APPLITE_VEU)
	applite_veu_reserve_memblock();
#endif
#if IS_ENABLED(CONFIG_APPLITE_VDU)
	applite_vdu_reserve_memblock();
#endif
}

#ifdef CONFIG_MACH_TZ3000RB4
MACHINE_START(TZ3000RB4, "TOSHIBA TZ3000 RB4")
	.atag_offset	= 0x100,
	.reserve	= tz3000_reserve,
	.map_io		= tz3000_map_io,
	.init_early	= tz3000_init_early,
	.init_irq	= tz3000_init_irq,
	.timer		= &tz3000_timer,
	.handle_irq	= gic_handle_irq,
	.init_machine	= tz3000_init,
	.restart	= tz3000_restart,
MACHINE_END
#endif

#ifdef CONFIG_MACH_TZ3000RB3
MACHINE_START(TZ3000RB3, "TOSHIBA TZ3000 RB3")
	.atag_offset	= 0x100,
	.reserve	= tz3000_reserve,
	.map_io		= tz3000_map_io,
	.init_early	= tz3000_init_early,
	.init_irq	= tz3000_init_irq,
	.timer		= &tz3000_timer,
	.handle_irq	= gic_handle_irq,
	.init_machine	= tz3000_init,
	.restart	= tz3000_restart,
MACHINE_END
#endif

#ifdef CONFIG_MACH_TZ3000RB2
MACHINE_START(TZ3000RB2, "TOSHIBA TZ3000 RB2")
	.atag_offset	= 0x100,
	.reserve	= tz3000_reserve,
	.map_io		= tz3000_map_io,
	.init_early	= tz3000_init_early,
	.init_irq	= tz3000_init_irq,
	.timer		= &tz3000_timer,
	.handle_irq	= gic_handle_irq,
	.init_machine	= tz3000_init,
	.restart	= tz3000_restart,
MACHINE_END
#endif

#ifdef CONFIG_MACH_TZ3000RB
MACHINE_START(TZ3000RB, "TOSHIBA TZ3000 RB")
	.atag_offset	= 0x100,
	.reserve	= tz3000_reserve,
	.map_io		= tz3000_map_io,
	.init_early	= tz3000_init_early,
	.init_irq	= tz3000_init_irq,
	.timer		= &tz3000_timer,
	.handle_irq	= gic_handle_irq,
	.init_machine	= tz3000_init,
	.restart	= tz3000_restart,
MACHINE_END
#endif

#ifdef CONFIG_MACH_TZ3000EVA
MACHINE_START(TZ3000EVA, "TOSHIBA TZ3000 EVA")
	.atag_offset	= 0x100,
	.reserve	= tz3000_reserve,
	.map_io		= tz3000_map_io,
	.init_early	= tz3000_init_early,
	.init_irq	= tz3000_init_irq,
	.timer		= &tz3000_timer,
	.handle_irq	= gic_handle_irq,
	.init_machine	= tz3000_init,
	.restart	= tz3000_restart,
MACHINE_END
#endif
