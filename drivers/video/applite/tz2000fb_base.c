/*
 * linux/drivers/video/applite/tz2000fb_base.c
 *
 * (C) Copyright TOSHIBA Corporation
 * Semiconductor & Storage Products Company 2012
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
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/vmalloc.h>
#include <linux/delay.h>
#include <linux/uaccess.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/i2c.h>
#include <linux/gpio.h>

#if IS_ENABLED(CONFIG_PM_RUNTIME)
#include <linux/pm_runtime.h>
#endif /* IS_ENABLED(CONFIG_PM_RUNTIME) */
#include <linux/clk.h>

#include <linux/fb.h>
#include <linux/init.h>
#include <asm/cacheflush.h>

#include <mach/regs/cpu_memmap_def.h>
#ifndef CPU_SRAM_REG_BASE
  #define CPU_SRAM_REG_BASE 0xC0000000
#endif
#ifndef CPU_SRAM_REG_SIZE
  #define CPU_SRAM_REG_SIZE 0x100000
#endif
#include <mach/regs/pmu_reg_def.h>
#include <mach/regs/lcdc_reg_def.h>

#if IS_ENABLED(CONFIG_APPLITE_PWM)
#include <linux/miscdevice.h>
#include <linux/pwm.h>
#endif /* IS_ENABLED(CONFIG_APPLITE_PWM) */
#include "tz2000fb.h"
#include "tz2000gfx_internal.h"

#define DEFAULT_FORMAT_IS_RGB16_RGB565
#undef DEFAULT_FORMAT_IS_ARGB32_ARGB8888
#undef DEFAULT_FORMAT_IS_ARGB32_RGBA8888

#define STRICT_COLOR_CHECK
#undef DISABLE_32BIT_COLOR

#if IS_ENABLED(CONFIG_FB_APPLITE_BASIC_RESOURCE_MINIMAL_SRAM)
__u32 tz2000fb_sram_vtop_reg_base;
EXPORT_SYMBOL(tz2000fb_sram_vtop_reg_base);
#endif

static inline void lcdc_write_reg(const volatile void __iomem *base, const volatile u32 reg, u32 val)
{
	__raw_writel(val, base + reg);
}

static inline u32 lcdc_read_reg(const volatile void __iomem *base, const volatile u32 reg)
{
	return __raw_readl(base + reg);
}

static inline void set_rgba(struct fb_var_screeninfo *var,
			    __u32 r_off, __u32 r_len,
			    __u32 g_off, __u32 g_len,
			    __u32 b_off, __u32 b_len,
			    __u32 a_off, __u32 a_len)
{
	var->red.offset       = r_off;
	var->red.length       = r_len;
	var->red.msb_right    = 0;
	var->green.offset     = g_off;
	var->green.length     = g_len;
	var->green.msb_right  = 0;
	var->blue.offset      = b_off;
	var->blue.length      = b_len;
	var->blue.msb_right   = 0;
	var->transp.offset    = a_off;
	var->transp.length    = a_len;
	var->transp.msb_right = 0;
}

    /*
     *  RAM we reserve for the frame buffer. This defines the maximum screen
     *  size
     *
     *  The default can be overridden if the driver is compiled as a module
     */

#define MAX_XRES		800
#define MAX_YRES		480
#if IS_ENABLED(CONFIG_FB_APPLITE_BASIC_RESOURCE_MINIMAL)
  #define MAX_FB_MAGNIFICATION	1
  #define MAX_BPP		16
#elif IS_ENABLED(CONFIG_FB_APPLITE_BASIC_RESOURCE_MINIMAL_SRAM)
  #define MAX_FB_MAGNIFICATION	3
  #define MAX_BPP		16
#else
  #define MAX_FB_MAGNIFICATION	3
  #define MAX_BPP		32
#endif
#define MAX_FRAME_SIZE		(MAX_XRES * MAX_YRES * MAX_BPP / 8)
#if IS_ENABLED(CONFIG_FB_APPLITE_BASIC_RESOURCE_MINIMAL_SRAM)
  #define MAX_FB_SIZE		CPU_SRAM_REG_SIZE
#else
  #define MAX_FB_SIZE		(MAX_FRAME_SIZE * MAX_FB_MAGNIFICATION)
#endif
#if \
	IS_ENABLED(CONFIG_FB_TZ2000_DISPLAY_NHD4_3_84) || \
	IS_ENABLED(CONFIG_FB_TZ2000_DISPLAY_NHD4_3_59) || \
	IS_ENABLED(CONFIG_FB_TZ2000_DISPLAY_NHD4_3_29) || \
	IS_ENABLED(CONFIG_FB_TZ2000_DISPLAY_ILI6480G2_59) || \
	IS_ENABLED(CONFIG_FB_TZ2000_DISPLAY_ILI6480G2_29)
  #define DEFAULT_XRES		480
  #define DEFAULT_YRES		272
#else
  #define DEFAULT_XRES		800
  #define DEFAULT_YRES		480
#endif
#if IS_ENABLED(CONFIG_FB_APPLITE_BASIC_RESOURCE_MINIMAL) || IS_ENABLED(CONFIG_FB_APPLITE_BASIC_RESOURCE_MINIMAL_SRAM)
  #undef DEFAULT_FORMAT_IS_RGB16_RGB565
  #undef DEFAULT_FORMAT_IS_ARGB32_ARGB8888
  #undef DEFAULT_FORMAT_IS_ARGB32_RGBA8888
  #undef DISABLE_32BIT_COLOR
  #define DEFAULT_FORMAT_IS_RGB16_RGB565
  #define DISABLE_32BIT_COLOR
#endif /* IS_ENABLED(CONFIG_FB_APPLITE_BASIC_RESOURCE_MINIMAL) || IS_ENABLED(CONFIG_FB_APPLITE_BASIC_RESOURCE_MINIMAL_SRAM) */
#if defined(DEFAULT_FORMAT_IS_RGB16_RGB565)
  #define DEFAULT_FORMAT	RGB16_RGB565
  #define DEFAULT_BPP		16
  #define DEFAULT_COLOR_R	{ 11, 5, 0 }
  #define DEFAULT_COLOR_G	{  5, 6, 0 }
  #define DEFAULT_COLOR_B	{  0, 5, 0 }
  #define DEFAULT_COLOR_A	{  0, 0, 0 }
#elif defined(DEFAULT_FORMAT_IS_ARGB32_ARGB8888) && !defined(DISABLE_32BIT_COLOR)
  #define DEFAULT_FORMAT	ARGB32_ARGB8888
  #define DEFAULT_BPP		32
  #define DEFAULT_COLOR_R	{ 16, 8, 0 }
  #define DEFAULT_COLOR_G	{  8, 8, 0 }
  #define DEFAULT_COLOR_B	{  0, 8, 0 }
  #define DEFAULT_COLOR_A	{ 24, 8, 0 }
#elif defined(DEFAULT_FORMAT_IS_ARGB32_RGBA8888) && !defined(DISABLE_32BIT_COLOR)
  #define DEFAULT_FORMAT	ARGB32_RGBA8888
  #define DEFAULT_BPP		32
  #define DEFAULT_COLOR_R	{ 24, 8, 0 }
  #define DEFAULT_COLOR_G	{ 16, 8, 0 }
  #define DEFAULT_COLOR_B	{  8, 8, 0 }
  #define DEFAULT_COLOR_A	{  0, 8, 0 }
#else /* defined(DEFAULT_FORMAT_IS_RGB16_RGB565) */
  #define DEFAULT_FORMAT	RGB16_RGB565
  #define DEFAULT_BPP		16
  #define DEFAULT_COLOR_R	{ 11, 5, 0 }
  #define DEFAULT_COLOR_G	{  5, 6, 0 }
  #define DEFAULT_COLOR_B	{  0, 5, 0 }
  #define DEFAULT_COLOR_A	{  0, 0, 0 }
#endif
#if IS_ENABLED(CONFIG_FB_TZ2000_DISPLAY_F07A_0102_58)
  #define DEFAULT_FB_MODE	1
#elif IS_ENABLED(CONFIG_FB_TZ2000_DISPLAY_NHD4_3_84)
  #define DEFAULT_FB_MODE	2
#elif IS_ENABLED(CONFIG_FB_TZ2000_DISPLAY_NHD4_3_59)
  #define DEFAULT_FB_MODE	3
#elif IS_ENABLED(CONFIG_FB_TZ2000_DISPLAY_NHD4_3_29)
  #define DEFAULT_FB_MODE	4
#elif IS_ENABLED(CONFIG_FB_TZ2000_DISPLAY_ILI6480G2_59)
  #define DEFAULT_FB_MODE	5
#else
  #define DEFAULT_FB_MODE	6
#endif
#if IS_ENABLED(CONFIG_FB_APPLITE_BASIC_RESOURCE_MINIMAL) || IS_ENABLED(CONFIG_FB_APPLITE_BASIC_RESOURCE_MINIMAL_SRAM)
  #define DEFAULT_FB_MAGNIFICATION	1
  #define GFX_WORK_SIZE			0
#else
  #define DEFAULT_FB_MAGNIFICATION	3
  #define GFX_WORK_SIZE			(16 * 1024 * 1024)
#endif
#define DEFAULT_FRAME_SIZE	(DEFAULT_XRES * DEFAULT_YRES * DEFAULT_BPP / 8)

static u_long magnification = DEFAULT_FB_MAGNIFICATION;
module_param(magnification, ulong, 0644);
MODULE_PARM_DESC(magnification, "Num of Framebuffer");

static u_long fb_mode = DEFAULT_FB_MODE;
module_param(fb_mode, ulong, 0444);

static u_long xlstart_a;
static int param_set_xlstart_a(const char *str, struct kernel_param *kp);
static int param_get_xlstart_a(char *buf, struct kernel_param *kp);
module_param_call(xlstart_a, param_set_xlstart_a, param_get_xlstart_a, NULL, 0644);
MODULE_PARM_DESC(xlstart_a, "Layer A Start Registers (horizontal)");

static u_long ylstart_a;
static int param_set_ylstart_a(const char *str, struct kernel_param *kp);
static int param_get_ylstart_a(char *buf, struct kernel_param *kp);
module_param_call(ylstart_a, param_set_ylstart_a, param_get_ylstart_a, NULL, 0644);
MODULE_PARM_DESC(ylstart_a, "Layer A Start Registers (vertical)");

struct tz2000fb_dev priv = {
#if IS_ENABLED(CONFIG_FB_TZ2000_USE_PWM0)
	.use_pwm0 = 1,
#else
	.use_pwm0 = 0,
#endif
};

module_param_named(use_pwm0, priv.use_pwm0, long, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(use_pwm0, "Use PWM[0]");

static const char tz2000fb_devname[] = "tz2000fb";

#if IS_ENABLED(CONFIG_APPLITE_PWM)
struct pwm_device *pwm0;

static int pwm_start(void)
{
	int ret = 0, duty = 0, period = 0;

	pwm0 = pwm_request(0, "pwm0");

	period = 0x20;
	duty = 0x10;
	pwm0->iteration = 0;

	ret = pwm_config(pwm0, duty, period);
	if (ret < 0)
		return ret;

	pwm0->pol = 1;
	pwm0->lvs = 0;
	pwm0->div = 0;
	pwm0->enbsel = 0;
	pwm0->genb_set = 0;

	ret = pwm_enable(pwm0);
	if (ret < 0)
		return ret;

	return 0;
}

static int pwm_stop(void)
{
	if (pwm0) {
		pwm_disable(pwm0);
		pwm_free(pwm0);
	}

	return 0;
}

#else
static int pwm_start(void) { return 0; }
static int pwm_stop(void) { return 0; }

#endif /* IS_ENABLED(CONFIG_APPLITE_PWM) */
static void update_layer_start(void)
{
	u32 gdclsra_l, gdcldra_l;

	gdclsra_l = priv.layer[0].gdclsra_l_bak;
	gdclsra_l += (priv.layer[0].xlstart << 16);
	gdclsra_l += priv.layer[0].ylstart;

	gdcldra_l = ((priv.layer[0].dxres << 16) | priv.layer[0].dyres);

	lcdc_write_reg(priv.lcdc_regs, 0x090, gdclsra_l);
	lcdc_write_reg(priv.lcdc_regs, 0x0b8, gdcldra_l);
}

static int param_get_xlstart_a(char *buf, struct kernel_param *kp)
{
	int ret;
	int len;

	sprintf(buf, "%lu", xlstart_a);
	len = strlen(buf);
	ret = len + 1;

	return ret;
}

static int param_set_xlstart_a(const char *str, struct kernel_param *kp)
{
	u_long par;
	if (get_option((char **)&str, (int *)&par)) {
		if ((par >= 0) && (par < MAX_XRES)) {
			priv.layer[0].xlstart = xlstart_a = par;
			if ((priv.layer[0].xlstart + priv.layer[0].xres) > MAX_XRES)
				priv.layer[0].dxres = MAX_XRES - priv.layer[0].xlstart;
			else
				priv.layer[0].dxres = priv.layer[0].xres;
			update_layer_start();
			return 0;
		}
	}
	return -EINVAL;
}

static int param_get_ylstart_a(char *buf, struct kernel_param *kp)
{
	int ret;
	int len;

	sprintf(buf, "%lu", ylstart_a);
	len = strlen(buf);
	ret = len + 1;

	return ret;
}

static int param_set_ylstart_a(const char *str, struct kernel_param *kp)
{
	u_long par;
	if (get_option((char **)&str, (int *)&par)) {
		if ((par >= 0) && (par < MAX_YRES)) {
			priv.layer[0].ylstart = ylstart_a = par;
			if ((priv.layer[0].ylstart + priv.layer[0].yres) > MAX_YRES)
				priv.layer[0].dyres = MAX_YRES - priv.layer[0].ylstart;
			else
				priv.layer[0].dyres = priv.layer[0].yres;
			update_layer_start();
			return 0;
		}
	}
	return -EINVAL;
}

static int lcdc_setup(void)
{
	u32 gdcmwra_l = priv.layer[0].vxres;
	u32 gdcldra_l = ((priv.layer[0].dxres << 16) | priv.layer[0].dyres);
	priv.flip = 0;

	if (priv.use_pwm0)
		pwm_start();

	switch (fb_mode) {
	case 1:
		/* 800x480@58.19 F07A-0102 */
		lcdc_write_reg(priv.pmu_regs, PMU_SOFTRESETOFF_LCDCSS_0_OFS, 0x00000001);
		lcdc_write_reg(priv.pmu_regs, PMU_PANEL_CLOCK_0_OFS, 0x00000002);
		break;
	case 2:
		/* 480x272@84.38 NHD4_3 */
		lcdc_write_reg(priv.pmu_regs, PMU_SOFTRESETOFF_LCDCSS_0_OFS, 0x00000001);
		lcdc_write_reg(priv.pmu_regs, PMU_PANEL_CLOCK_0_OFS, 0x00000001);
		lcdc_write_reg(priv.pmu_regs, PMU_PLLCONFIG_PLLLCD_0_OFS, 0xa7153000);
		lcdc_write_reg(priv.pmu_regs, PMU_PLLCONFIG_PLLLCD_1_OFS, 0x0001014a);
		break;
	case 3:
		/* 480x272@59.94 NHD4_3 */
		lcdc_write_reg(priv.pmu_regs, PMU_SOFTRESETOFF_LCDCSS_0_OFS, 0x00000001);
		lcdc_write_reg(priv.pmu_regs, PMU_PANEL_CLOCK_0_OFS, 0x00000003);
		lcdc_write_reg(priv.pmu_regs, PMU_PLLCONFIG_PLLLCD_0_OFS, 0xa70c3200);
		lcdc_write_reg(priv.pmu_regs, PMU_PLLCONFIG_PLLLCD_1_OFS, 0x000e0435);
		break;
	case 4:
		/* 480x272@29.97 NHD4_3 */
		lcdc_write_reg(priv.pmu_regs, PMU_SOFTRESETOFF_LCDCSS_0_OFS, 0x00000001);
		lcdc_write_reg(priv.pmu_regs, PMU_PANEL_CLOCK_0_OFS, 0x00000003);
		lcdc_write_reg(priv.pmu_regs, PMU_PLLCONFIG_PLLLCD_0_OFS, 0xa70c3200);
		lcdc_write_reg(priv.pmu_regs, PMU_PLLCONFIG_PLLLCD_1_OFS, 0x000e0423);
		break;
	case 5:
		/* 480x272@59.94 ILI6480G2 */
		lcdc_write_reg(priv.pmu_regs, PMU_SOFTRESETOFF_LCDCSS_0_OFS, 0x00000001);
		lcdc_write_reg(priv.pmu_regs, PMU_PANEL_CLOCK_0_OFS, 0x00000003);
		lcdc_write_reg(priv.pmu_regs, PMU_PLLCONFIG_PLLLCD_0_OFS, 0xa70c3200);
		lcdc_write_reg(priv.pmu_regs, PMU_PLLCONFIG_PLLLCD_1_OFS, 0x000e0435);
		break;
	case 6:
		/* 480x272@29.97 ILI6480G2 */
		lcdc_write_reg(priv.pmu_regs, PMU_SOFTRESETOFF_LCDCSS_0_OFS, 0x00000001);
		lcdc_write_reg(priv.pmu_regs, PMU_PANEL_CLOCK_0_OFS, 0x00000000);
		lcdc_write_reg(priv.pmu_regs, PMU_PLLCONFIG_PLLLCD_0_OFS, 0xa7153100);
		lcdc_write_reg(priv.pmu_regs, PMU_PLLCONFIG_PLLLCD_1_OFS, 0x0001033b);
		break;
	}
	mdelay(1);
	{
		lcdc_write_reg(priv.lcdc_regs, 0x140, 0x00000104);
		lcdc_write_reg(priv.lcdc_regs, 0x144, 0x00000010);
		lcdc_write_reg(priv.lcdc_regs, 0x010, priv.layer[0].addr);
	}
	switch (fb_mode) {
	case 1:
		/* 800x480@58.19 F07A-0102 */
		lcdc_write_reg(priv.lcdc_regs, 0x068, gdcmwra_l);
		lcdc_write_reg(priv.lcdc_regs, 0x090, 0x00c0005f); /* default */
		lcdc_write_reg(priv.lcdc_regs, 0x0b8, gdcldra_l);
#if 0
		lcdc_write_reg(priv.lcdc_regs, 0x0e0, 0x00c0005f); /* default */
#endif
		lcdc_write_reg(priv.lcdc_regs, 0x2b0, 0x00c0005f); /* default */
		lcdc_write_reg(priv.lcdc_regs, 0x2b8, 0x032001e0);
		lcdc_write_reg(priv.lcdc_regs, 0x110, 0x00170420);
		lcdc_write_reg(priv.lcdc_regs, 0x118, 0x0002020d);
		break;
	case 2:
		/* 480x272@84.38 NHD4_3 */
		lcdc_write_reg(priv.lcdc_regs, 0x068, gdcmwra_l);
		lcdc_write_reg(priv.lcdc_regs, 0x090, 0x006a004c);
		lcdc_write_reg(priv.lcdc_regs, 0x0b8, gdcldra_l);
#if 0
		lcdc_write_reg(priv.lcdc_regs, 0x0e0, 0x002b000c);
#endif
		lcdc_write_reg(priv.lcdc_regs, 0x2b0, 0x006a004c);
		lcdc_write_reg(priv.lcdc_regs, 0x2b8, 0x01e00110);
		lcdc_write_reg(priv.lcdc_regs, 0x110, 0x0029020d);
		lcdc_write_reg(priv.lcdc_regs, 0x118, 0x000a011e);
		break;
	case 3:
		/* 480x272@59.94 NHD4_3 */
		lcdc_write_reg(priv.lcdc_regs, 0x068, gdcmwra_l);
		lcdc_write_reg(priv.lcdc_regs, 0x090, 0x006a004c);
		lcdc_write_reg(priv.lcdc_regs, 0x0b8, gdcldra_l);
		lcdc_write_reg(priv.lcdc_regs, 0x2b0, 0x006a004c);
		lcdc_write_reg(priv.lcdc_regs, 0x2b8, 0x01e00110);
		lcdc_write_reg(priv.lcdc_regs, 0x110, 0x0029020d);
		lcdc_write_reg(priv.lcdc_regs, 0x118, 0x000a011e);
		break;
	case 4:
		/* 480x272@29.97 NHD4_3 */
		lcdc_write_reg(priv.lcdc_regs, 0x068, gdcmwra_l);
		lcdc_write_reg(priv.lcdc_regs, 0x090, 0x00e0004c);
		lcdc_write_reg(priv.lcdc_regs, 0x0b8, gdcldra_l);
		lcdc_write_reg(priv.lcdc_regs, 0x2b0, 0x00e0004c);
		lcdc_write_reg(priv.lcdc_regs, 0x2b8, 0x01e00110);
		lcdc_write_reg(priv.lcdc_regs, 0x110, 0x002902c0);
		lcdc_write_reg(priv.lcdc_regs, 0x118, 0x000a011e);
		break;
	case 5:
		/* 480x272@59.94 ILI6480G2 */
		lcdc_write_reg(priv.lcdc_regs, 0x068, gdcmwra_l);
		lcdc_write_reg(priv.lcdc_regs, 0x090, 0x00680048);
		lcdc_write_reg(priv.lcdc_regs, 0x0b8, gdcldra_l);
		lcdc_write_reg(priv.lcdc_regs, 0x2b0, 0x00680048);
		lcdc_write_reg(priv.lcdc_regs, 0x2b8, 0x01e00110);
		lcdc_write_reg(priv.lcdc_regs, 0x110, 0x0010020d);
		lcdc_write_reg(priv.lcdc_regs, 0x118, 0x00020120);
		break;
	case 6:
		/* 480x272@29.97 ILI6480G2 */
		lcdc_write_reg(priv.lcdc_regs, 0x068, gdcmwra_l);
		lcdc_write_reg(priv.lcdc_regs, 0x090, 0x00e00048);
		lcdc_write_reg(priv.lcdc_regs, 0x0b8, gdcldra_l);
		lcdc_write_reg(priv.lcdc_regs, 0x2b0, 0x00e00048);
		lcdc_write_reg(priv.lcdc_regs, 0x2b8, 0x01e00110);
		lcdc_write_reg(priv.lcdc_regs, 0x110, 0x001002c0);
		lcdc_write_reg(priv.lcdc_regs, 0x118, 0x00020120);
		break;
	}
	priv.layer[0].gdclsra_l_bak = lcdc_read_reg(priv.lcdc_regs, 0x090);
	{
		if (priv.layer[0].pixelformat == RGB16_RGB565)
			/* RGB16_RGB565 */
			lcdc_write_reg(priv.lcdc_regs, 0x000, 0x01103001);
		else
			/* ARGB32_ARGB8888 or ARGB32_RGBA8888 */
			lcdc_write_reg(priv.lcdc_regs, 0x000, 0x01003001);
		if (priv.is_argb)
			/* ARGB32_ARGB8888 or RGB16_RGB565 */
			lcdc_write_reg(priv.lcdc_regs, 0x004, 0x80100000);
		else
			/* ARGB32_RGBA8888 or RGB16_RGB565 */
			lcdc_write_reg(priv.lcdc_regs, 0x004, 0x80000000);
	}

	return 0;
}

static int lcdc_cleanup(void)
{
	lcdc_write_reg(priv.lcdc_regs, 0x140, 0x8000f0f0);
	lcdc_write_reg(priv.lcdc_regs, 0x144, 0x00000030);
	lcdc_write_reg(priv.lcdc_regs, 0x004, 0x00000000);
	lcdc_write_reg(priv.lcdc_regs, 0x000, 0x00000000);
	lcdc_write_reg(priv.pmu_regs, PMU_SOFTRESETON_LCDCSS_0_OFS, 0x00000001);
	if (priv.use_pwm0)
		pwm_stop();

	return 0;
}

static struct fb_var_screeninfo tz2000fb_default __devinitdata = {
	.xres =		DEFAULT_XRES,
	.yres =		DEFAULT_YRES,
	.xres_virtual =	DEFAULT_XRES,
	.yres_virtual =	DEFAULT_YRES * DEFAULT_FB_MAGNIFICATION,
	.bits_per_pixel = DEFAULT_BPP,
	.grayscale =	0,
	.red =		DEFAULT_COLOR_R,
	.green =	DEFAULT_COLOR_G,
	.blue =		DEFAULT_COLOR_B,
	.transp =	DEFAULT_COLOR_A,
	.activate =	FB_ACTIVATE_NOW,
	.height =	-1,
	.width =	-1,
	.pixclock =	0,
	.left_margin =	0,
	.right_margin =	0,
	.upper_margin =	0,
	.lower_margin =	0,
	.hsync_len =	0,
	.vsync_len =	0,
	.sync =		0,
	.vmode =	FB_VMODE_NONINTERLACED,
	.rotate =	0,
};

static struct fb_fix_screeninfo tz2000fb_fix __devinitdata = {
	.id =		"TZ2000 LCDC",
	.type =		FB_TYPE_PACKED_PIXELS,
	.visual =	FB_VISUAL_TRUECOLOR,
	.xpanstep =	1,
	.ypanstep =	(DEFAULT_FB_MAGNIFICATION > 1) ? 1 : 0,
	.ywrapstep =	0,
	.line_length =	(DEFAULT_XRES * (DEFAULT_BPP / 8)),
#if defined(_MERGE_FBDEV_)
	.accel =	FB_ACCEL_APPLITE_TZ2000,
#else
	.accel =	FB_ACCEL_NONE,
#endif /* defined(_MERGE_FBDEV_) */
	.capabilities = 0,
};

static int tz2000fb_check_var(struct fb_var_screeninfo *var,
			      struct fb_info *info);
static int tz2000fb_set_par(struct fb_info *info);
static int tz2000fb_setcolreg(u_int regno, u_int red, u_int green, u_int blue,
			      u_int transp, struct fb_info *info);
static int tz2000fb_pan_display(struct fb_var_screeninfo *var,
				struct fb_info *info);
static int tz2000fb_mmap(struct fb_info *info,
			 struct vm_area_struct *vma);
static int tz2000fb_ioctl(struct fb_info *info,
			  unsigned int cmd,
			  unsigned long arg);

static struct fb_ops tz2000fb_ops = {
	.owner		= THIS_MODULE,
	.fb_read        = fb_sys_read,
	.fb_write       = fb_sys_write,
	.fb_check_var	= tz2000fb_check_var,
	.fb_set_par	= tz2000fb_set_par,
	.fb_setcolreg	= tz2000fb_setcolreg,
	.fb_pan_display	= tz2000fb_pan_display,
	.fb_fillrect	= sys_fillrect,
	.fb_copyarea	= sys_copyarea,
	.fb_imageblit	= sys_imageblit,
	.fb_mmap	= tz2000fb_mmap,
	.fb_ioctl	= tz2000fb_ioctl,
};

    /*
     *  Internal routines
     */
static int tz2000fb_wait_for_vsync(void)
{
	int ret;
	u32 gdcintr_l = lcdc_read_reg(priv.lcdc_regs, 0x140);

	/* Enable VSync End interrupt and be careful not to acknowledge any
	 * pending interrupt.
	 */
	gdcintr_l |= 0x01000004; /* unmask VSYNCMSK */
	lcdc_write_reg(priv.lcdc_regs, 0x140, gdcintr_l);

	ret = wait_for_completion_interruptible_timeout(&priv.vsync_completion,
							msecs_to_jiffies(100));
	if (!ret)
		return -ETIMEDOUT;

	return 0;
}

static irqreturn_t tz2000fb_lcdc_intr(int irq, void *data)
{
	unsigned long flag;
	u32 gdcintr_l = lcdc_read_reg(priv.lcdc_regs, 0x140);
	u32 gdcintr_u = lcdc_read_reg(priv.lcdc_regs, 0x144);

	spin_lock_irqsave(&priv.lcdc_slock, flag);

	lcdc_write_reg(priv.lcdc_regs, 0x140, ((gdcintr_l & ~0x8000f0f0) | 0x8000f0f0));
	lcdc_write_reg(priv.lcdc_regs, 0x144, ((gdcintr_u & ~0x00000030) | 0x00000030));

	if (gdcintr_l & 0x00000010)
		pr_warn("lcdc: GAPINT\n");
#if 0
	if (gdcintr_l & 0x00000020)
		pr_debug("lcdc: HSYNCINT\n");
#endif
	if (gdcintr_l & 0x00000040) {
		if (priv.flip)
			priv.flip--;
		complete(&priv.vsync_completion);
	}
	if (gdcintr_l & 0x00000080)
		pr_err("lcdc: GBERINT\n");
	if (gdcintr_l & 0x00001000)
		pr_warn("lcdc: IFURINT\n");
	if (gdcintr_l & 0x00002000)
		pr_warn("lcdc: OFURINT\n");
	if (gdcintr_l & 0x00004000)
		pr_debug("lcdc: VSLINT\n");
	if (gdcintr_l & 0x00008000)
		pr_err("lcdc: GPEINT\n");
	if (gdcintr_u & 0x00000010)
		pr_err("lcdc: APEINT\n");
	if (gdcintr_u & 0x00000020)
		pr_debug("lcdc: APCINT\n");

	spin_unlock_irqrestore(&priv.lcdc_slock, flag);

	return IRQ_HANDLED;
}

static u_long get_line_length(int xres_virtual, int bpp)
{
	u_long length;

	length = xres_virtual * bpp;
	length = (length + 31) & ~31;
	length >>= 3;
	return length;
}

    /*
     *  Setting the video mode has been split into two parts.
     *  First part, xxxfb_check_var, must not write anything
     *  to hardware, it should only verify and adjust var.
     *  This means it doesn't alter par but it does use hardware
     *  data from it to check this var.
     */

static int tz2000fb_check_var(struct fb_var_screeninfo *var,
			      struct fb_info *info)
{
	struct tz2000fb_layer *layer = (struct tz2000fb_layer *)(info->par);
	u_long line_length;

	/*
	 *  FB_VMODE_CONUPDATE and FB_VMODE_SMOOTH_XPAN are equal!
	 *  as FB_VMODE_SMOOTH_XPAN is only used internally
	 */

	if (var->vmode & FB_VMODE_CONUPDATE) {
		var->vmode |= FB_VMODE_YWRAP;
		var->xoffset = info->var.xoffset;
		var->yoffset = info->var.yoffset;
	}

	/*
	 *  Some very basic checks
	 */
	if (!var->xres)
		var->xres = 1;
	if (!var->yres)
		var->yres = 1;
	if (var->xres > var->xres_virtual)
		var->xres_virtual = var->xres;
	if (var->yres > var->yres_virtual)
		var->yres_virtual = var->yres;
	if (var->bits_per_pixel <= 1)
		return -EINVAL;
	else if (var->bits_per_pixel <= 8)
		return -EINVAL;
	else if (var->bits_per_pixel <= 16)
		var->bits_per_pixel = 16;
#ifdef STRICT_COLOR_CHECK
	else if (var->bits_per_pixel <= 24)
		return -EINVAL;
#endif /* STRICT_COLOR_CHECK */
#ifndef DISABLE_32BIT_COLOR
	else if (var->bits_per_pixel <= 32)
		var->bits_per_pixel = 32;
#endif /* DISABLE_32BIT_COLOR */
	else
		return -EINVAL;

#if 0
	if (var->yres <= 272) {
		var->xres = 480;
		var->yres = 272;
		var->xres_virtual = 480;
		var->yres_virtual = 272 * magnification;
	} else if (var->yres <= 480) {
		var->xres = 800;
		var->yres = 480;
		var->xres_virtual = 800;
		var->yres_virtual = 480 * magnification;
	} else
		return -EINVAL;

	switch (fb_mode) {
	case 0:
		if (!(var->xres == DEFAULT_XRES && var->yres == DEFAULT_YRES))
			return -EINVAL;
		break;
	case 1:	/* 800x480@58.19 F07A-0102 */
		if (!(var->xres == 800 && var->yres == 480))
			return -EINVAL;
		break;
	case 2:	/* 480x272@84.38 NHD4_3 */
	case 3:	/* 480x272@59.94 NHD4_3 */
	case 4:	/* 480x272@29.97 NHD4_3 */
	case 5:	/* 480x272@59.94 ILI6480G2 */
	case 6:	/* 480x272@29.97 ILI6480G2 */
		if (!(var->xres == 480 && var->yres == 272))
			return -EINVAL;
		break;
	default:
		return -EINVAL;
		break;
	}

#else
	if ((var->xres > MAX_XRES) || (var->yres > MAX_YRES))
		return -EINVAL;
	var->xres_virtual = var->xres;
	if ((var->yres_virtual == var->yres) ||
	    (var->yres_virtual > (var->yres * magnification)))
		var->yres_virtual = var->yres * magnification;

#endif
	if (var->xres_virtual < var->xoffset + var->xres)
		var->xres_virtual = var->xoffset + var->xres;
	if (var->yres_virtual < var->yoffset + var->yres)
		var->yres_virtual = var->yoffset + var->yres;

	/*
	 *  Memory limit
	 */
	line_length =
	    get_line_length(var->xres_virtual, var->bits_per_pixel);
	if (line_length * var->yres_virtual > layer->size)
		return -ENOMEM;

	/*
	 * Now that we checked it we alter var. The reason being is that the video
	 * mode passed in might not work but slight changes to it might make it
	 * work. This way we let the user know what is acceptable.
	 */
	switch (var->bits_per_pixel) {
	case 16:
		/* RGB 565 */
#ifdef STRICT_COLOR_CHECK
		if (var->red.offset    != 11 || var->red.length    != 5 ||
		    var->green.offset  !=  5 || var->green.length  != 6 ||
		    var->blue.offset   !=  0 || var->blue.length   != 5 ||
						var->transp.length != 0)
			return -EINVAL;
#endif /* STRICT_COLOR_CHECK */
		set_rgba(var, 11, 5, 5, 6, 0, 5, 0, 0);
		break;
	case 32:
		if (var->blue.offset) {
			/* RGBA 8888 */
#ifdef STRICT_COLOR_CHECK
			if (var->red.offset    != 24 || var->red.length    != 8 ||
			    var->green.offset  != 16 || var->green.length  != 8 ||
			    var->blue.offset   !=  8 || var->blue.length   != 8)
				return -EINVAL;
			set_rgba(var, 24, 8, 16, 8, 8, 8, 0, 8);
#else
			if (var->transp.length)
				set_rgba(var, 24, 8, 16, 8, 8, 8, 0, 8);
			else
				set_rgba(var, 24, 8, 16, 8, 8, 8, 0, 0);
#endif /* STRICT_COLOR_CHECK */
		} else {
			/* ARGB 8888 */
#ifdef STRICT_COLOR_CHECK
			if (var->red.offset    != 16 || var->red.length    != 8 ||
			    var->green.offset  !=  8 || var->green.length  != 8 ||
			    var->blue.offset   !=  0 || var->blue.length   != 8)
				return -EINVAL;
			set_rgba(var, 16, 8, 8, 8, 0, 8, 24, 8);
#else
			if (var->transp.length)
				set_rgba(var, 16, 8, 8, 8, 0, 8, 24, 8);
			else
				set_rgba(var, 16, 8, 8, 8, 0, 8, 0, 0);
#endif /* STRICT_COLOR_CHECK */
		}
		break;
	}

#if 0
	var->pixclock =	0;
	var->left_margin =	0;
	var->right_margin =	0;
	var->upper_margin =	0;
	var->lower_margin =	0;
	var->hsync_len =	0;
	var->vsync_len =	0;

#endif
	return 0;
}

/* This routine actually sets the video mode. It's in here where we
 * the hardware state info->par and fix which can be affected by the
 * change in par. For this driver it doesn't do much.
 */
static int tz2000fb_set_par(struct fb_info *info)
{
	struct tz2000fb_layer *layer = (struct tz2000fb_layer *)(info->par);

	info->fix.line_length = get_line_length(info->var.xres_virtual,
						info->var.bits_per_pixel);

	lcdc_cleanup();

	layer->xres = layer->dxres = info->var.xres;
	layer->yres = layer->dyres = info->var.yres;
	layer->vxres = info->var.xres_virtual;
	layer->vyres = info->var.yres_virtual;
	if (info->var.bits_per_pixel == 16) {
		layer->pixelformat = RGB16_RGB565;
	} else if (info->var.bits_per_pixel == 32) {
		if (info->var.blue.offset) {
			priv.is_argb = false;
			layer->pixelformat = ARGB32_RGBA8888;
		} else {
			priv.is_argb = true;
			layer->pixelformat = ARGB32_ARGB8888;
		}
	}

	lcdc_setup();

	info->fix.ypanstep = (magnification > 1) ? 1 : 0;
	return 0;
}

    /*
     *  Set a single color register. The values supplied are already
     *  rounded down to the hardware's capabilities (according to the
     *  entries in the var structure). Return != 0 for invalid regno.
     */

static int tz2000fb_setcolreg(u_int regno, u_int red, u_int green, u_int blue,
			      u_int transp, struct fb_info *info)
{
	if (regno >= 256)	/* no. of hw registers */
		return 1;
	/*
	 * Program hardware... do anything you want with transp
	 */

	/* grayscale works only partially under directcolor */
	if (info->var.grayscale) {
		/* grayscale = 0.30*R + 0.59*G + 0.11*B */
		red = green = blue =
		    (red * 77 + green * 151 + blue * 28) >> 8;
	}

	/* Directcolor:
	 *   var->{color}.offset contains start of bitfield
	 *   var->{color}.length contains length of bitfield
	 *   {hardwarespecific} contains width of RAMDAC
	 *   cmap[X] is programmed to (X << red.offset) | (X << green.offset) | (X << blue.offset)
	 *   RAMDAC[X] is programmed to (red, green, blue)
	 *
	 * Pseudocolor:
	 *    var->{color}.offset is 0 unless the palette index takes less than
	 *                        bits_per_pixel bits and is stored in the upper
	 *                        bits of the pixel value
	 *    var->{color}.length is set so that 1 << length is the number of available
	 *                        palette entries
	 *    cmap is not used
	 *    RAMDAC[X] is programmed to (red, green, blue)
	 *
	 * Truecolor:
	 *    does not use DAC. Usually 3 are present.
	 *    var->{color}.offset contains start of bitfield
	 *    var->{color}.length contains length of bitfield
	 *    cmap is programmed to (red << red.offset) | (green << green.offset) |
	 *                      (blue << blue.offset) | (transp << transp.offset)
	 *    RAMDAC does not exist
	 */
#define CNVT_TOHW(val, width) ((((val)<<(width))+0x7FFF-(val))>>16)
	switch (info->fix.visual) {
	case FB_VISUAL_TRUECOLOR:
	case FB_VISUAL_PSEUDOCOLOR:
		red = CNVT_TOHW(red, info->var.red.length);
		green = CNVT_TOHW(green, info->var.green.length);
		blue = CNVT_TOHW(blue, info->var.blue.length);
		transp = CNVT_TOHW(transp, info->var.transp.length);
		break;
	case FB_VISUAL_DIRECTCOLOR:
		red = CNVT_TOHW(red, 8);	/* expect 8 bit DAC */
		green = CNVT_TOHW(green, 8);
		blue = CNVT_TOHW(blue, 8);
		/* hey, there is bug in transp handling... */
		transp = CNVT_TOHW(transp, 8);
		break;
	}
#undef CNVT_TOHW
	/* Truecolor has hardware independent palette */
	if (info->fix.visual == FB_VISUAL_TRUECOLOR) {
		u32 v;

		if (regno >= 16)
			return 1;

		v = (red << info->var.red.offset) |
		    (green << info->var.green.offset) |
		    (blue << info->var.blue.offset) |
		    (transp << info->var.transp.offset);
		switch (info->var.bits_per_pixel) {
		case 8:
			break;
		case 16:
			((u32 *) (info->pseudo_palette))[regno] = v;
			break;
		case 24:
		case 32:
			((u32 *) (info->pseudo_palette))[regno] = v;
			break;
		}
		return 0;
	}
	return 0;
}

    /*
     *  Pan or Wrap the Display
     *
     *  This call looks only at xoffset, yoffset and the FB_VMODE_YWRAP flag
     */

static int tz2000fb_pan_display(struct fb_var_screeninfo *var,
				struct fb_info *info)
{
	struct tz2000fb_layer *layer = (struct tz2000fb_layer *)(info->par);

	if (var->vmode & FB_VMODE_YWRAP) {
		if (var->yoffset < 0
		    || var->yoffset >= info->var.yres_virtual
		    || var->xoffset)
			return -EINVAL;
	} else {
		if (var->xoffset + info->var.xres > info->var.xres_virtual ||
		    var->yoffset + info->var.yres > info->var.yres_virtual)
			return -EINVAL;
	}
	info->var.xoffset = var->xoffset;
	info->var.yoffset = var->yoffset;

	{
		u32 baseaddr = layer->addr;
		u32 line_length = get_line_length(var->xres_virtual, var->bits_per_pixel);

		baseaddr += line_length * var->yoffset;

		while (priv.flip > ((info->var.yres_virtual / info->var.yres) - 1)) {
			int ret;
			ret = wait_for_completion_interruptible_timeout(&priv.vsync_completion,
						msecs_to_jiffies(100));
			if (!ret)
				pr_debug("tz2000fb_pan_display() timeout\n");
		}

		lcdc_write_reg(priv.lcdc_regs, 0x010, baseaddr);

		priv.flip++;
	}

	if (var->vmode & FB_VMODE_YWRAP)
		info->var.vmode |= FB_VMODE_YWRAP;
	else
		info->var.vmode &= ~FB_VMODE_YWRAP;
	return 0;
}

    /*
     *  Most drivers don't need their own mmap function
     */

static int tz2000fb_mmap(struct fb_info *info,
			 struct vm_area_struct *vma)
{
	unsigned long start = vma->vm_start;
	unsigned long size = vma->vm_end - vma->vm_start;
	unsigned long offset = vma->vm_pgoff << PAGE_SHIFT;
	unsigned long page, pos;

	if (offset + size > info->fix.smem_len)
		return -EINVAL;

	pos = (unsigned long)info->fix.smem_start + offset;

	while (size > 0) {
		page = vmalloc_to_pfn((void *)pos);
		vma->vm_flags |= VM_IO | VM_RESERVED;
		vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);
		if (remap_pfn_range(vma, start, page, PAGE_SIZE, vma->vm_page_prot))
			return -EAGAIN;
		start += PAGE_SIZE;
		pos += PAGE_SIZE;
		if (size > PAGE_SIZE)
			size -= PAGE_SIZE;
		else
			size = 0;
	}

	return 0;
}

static void tz2000fb_get_vblank(struct fb_vblank *vblank)
{
	memset(vblank, 0, sizeof(*vblank));
	vblank->flags = FB_VBLANK_HAVE_VSYNC;

	return;
}

static int tz2000fb_ioctl(struct fb_info *info, unsigned int cmd,
			  unsigned long arg)
{
	int retval = 0;
	void __user *argp = (void __user *)arg;
	struct fb_vblank vblank;

	switch (cmd) {
	case FBIOGET_VBLANK:
		tz2000fb_get_vblank(&vblank);

		if (copy_to_user(argp, &vblank, sizeof(vblank))) {
			pr_err("copy_to_user()\n");
			retval = -EFAULT;
		}
		break;
	case FBIO_WAITFORVSYNC:
		{
			retval = tz2000fb_wait_for_vsync();
			break;
		}
	default:
#if defined(_MERGE_FBDEV_)
		retval = tz2000gfx_ioctl(info, cmd, arg);
#else
		retval = -ENOIOCTLCMD;
#endif
		break;
	}
	return retval;
}

#ifdef CONFIG_PM
int tz2000fb_hw_start(void)
{
	__u32 val;

	/* start clock */
	clk_prepare_enable(priv.clk_lcdc);

	/* VDD33_TOP */
	val = lcdc_read_reg(priv.pmu_regs, PMU_POREN_OFS);
	val &= ~PMU_POREN_POREN_TOP_MASK;

	lcdc_write_reg(priv.pmu_regs, PMU_POREN_OFS, (val | PMU_POREN_POREN_TOP_MASK));
	/* 100ns wait */
	ndelay(100);

#if defined(_MERGE_FBDEV_)
	/* gfx resume */
	tz2000gfx_resume();

#endif /* defined(_MERGE_FBDEV_) */
	return 0;
}

int tz2000fb_hw_stop(void)
{
	__u32 val;

	/* check status */
	val = lcdc_read_reg(priv.lcdc_regs, LCDC_GDCDCR_U_OFS);
	if (val & LCDC_GDCDCR_U_DISPIFON_MASK) {
		pr_err("GDCDCR_U(%08x) display interface enabled\n", val);
		/*return -EBUSY;*/
	}

	/* stop clock */
	clk_disable_unprepare(priv.clk_lcdc);

#if defined(_MERGE_FBDEV_)
	/* gfx suspend */
	val = tz2000gfx_suspend();

#endif /* defined(_MERGE_FBDEV_) */
	return val;
}

static int tz2000fb_suspend(struct device *dev)
{
	if (module_refcount(dev->driver->owner->mkobj.mod) > 0)
		return -EBUSY;

	lcdc_cleanup();
	tz2000fb_hw_stop();

	return 0;
}

static int tz2000fb_resume(struct device *dev)
{
	tz2000fb_hw_start();
	/* setting of register */
	lcdc_cleanup();
	lcdc_setup();

	return 0;
}

#endif
int tz2000fb_runtime_suspend(struct device *dev)
{
	__u32 val;

	val = lcdc_read_reg(priv.lcdc_regs, LCDC_GDCDCR_U_OFS);
	lcdc_write_reg(priv.lcdc_regs, LCDC_GDCDCR_U_OFS, (val & 0x7FFFFFFF));
	mdelay(100);
	/* check status */
	val = lcdc_read_reg(priv.lcdc_regs, LCDC_GDCDCR_U_OFS);
	if (val & LCDC_GDCDCR_U_DISPIFON_MASK) {
		dev_err(dev, "GDCDCR_U(%08x) display interface enabled\n", val);
		/*return -EBUSY;*/
	}

	/* stop clock */
	clk_disable_unprepare(priv.clk_lcdc);

#if defined(_MERGE_FBDEV_)
	/* gfx suspend */
	val = tz2000gfx_suspend();

#endif /* defined(_MERGE_FBDEV_) */
	return val;
}

int tz2000fb_runtime_resume(struct device *dev)
{
	/* start clock */
	clk_prepare_enable(priv.clk_lcdc);

#if defined(_MERGE_FBDEV_)
	/* gfx resume */
	tz2000gfx_resume();

#endif /* defined(_MERGE_FBDEV_) */
	return 0;
}

#ifndef MODULE
/*
 * The virtual framebuffer driver is only enabled if explicitly
 * requested by passing 'video=tz2000fb:' (or any actual options).
 */
static int __init tz2000fb_setup(char *options)
{
	char *this_opt;

	if (!options)
		return 1;

	if (!*options)
		return 1;

	while ((this_opt = strsep(&options, ",")) != NULL) {
		if (!*this_opt)
			continue;
	}
	return 1;
}
#endif  /*  MODULE  */

    /*
     *  Initialisation
     */

static int __devinit tz2000fb_probe(struct platform_device *pdev)
{
	int retval = -ENOMEM;
	unsigned int ii;
	struct resource *lcdc, *pmu;
	struct resource *gfx;
	int irq[2];

#if 0
	memset(&priv, 0, sizeof(struct tz2000fb_dev));

#endif
	priv.dev = &pdev->dev;

	/* Mapping to PMU register */
	pmu = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!pmu) {
		pr_err("lcdc platform_get_resource() failed [pmu]\n");
		retval = -ENOENT;
		goto err0;
	}
	priv.pmu_regs = ioremap_nocache(pmu->start, resource_size(pmu));
	if (!priv.pmu_regs) {
		pr_err("lcdc ioremap_nocache failed [pmu]\n");
		goto err0;
	}

	/* Mapping to LCDC register */
	lcdc = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (!lcdc) {
		pr_err("lcdc platform_get_resource() failed [lcdc]\n");
		retval = -ENOENT;
		goto err0;
	}
	priv.lcdc_regs = ioremap_nocache(lcdc->start, resource_size(lcdc));
	if (!priv.lcdc_regs) {
		pr_err("lcdc ioremap_nocache failed [lcdc]\n");
		goto err0;
	}

	/* Mapping to GFX register */
	gfx = platform_get_resource(pdev, IORESOURCE_MEM, 2);
	if (!gfx) {
		pr_err("lcdc platform_get_resource() failed [gfx]\n");
		retval = -ENOENT;
		goto err0;
	}
	priv.gfx_regs = ioremap_nocache(gfx->start, resource_size(gfx));
	if (!priv.gfx_regs) {
		pr_err("lcdc ioremap_nocache failed [gfx]\n");
		goto err0;
	}

	if (magnification > MAX_FB_MAGNIFICATION) {
		dev_warn(&pdev->dev, "Illegal magnification %lu. Force set %u\n",
			 magnification, MAX_FB_MAGNIFICATION);
		magnification = MAX_FB_MAGNIFICATION;
	}

#if IS_ENABLED(CONFIG_FB_APPLITE_BASIC_RESOURCE_MINIMAL_SRAM)
	{
		__u32 cgoff, sroff;
		const __u32 CLOCKGATINGOFF_VAL =
			PMU_CLOCKGATINGOFF_TELOMERESS_0_CG_WCLKDIV2_EMMC8SD_X_MASK |
			PMU_CLOCKGATINGOFF_TELOMERESS_0_CG_WCLKDIV2_EMMC8SD_H_MASK |
			PMU_CLOCKGATINGOFF_TELOMERESS_0_CG_WCLKDIV2_TELOMERE_MASK |
			PMU_CLOCKGATINGOFF_TELOMERESS_0_CG_NCLK_MASK |
			PMU_CLOCKGATINGOFF_TELOMERESS_0_CG_NCLKDIV2_MASK;
		const __u32 SOFTRESETON_VAL =
			PMU_SOFTRESETON_TELOMERESS_0_SRST_ASYNCNRSTDIV2_N_MASK |
			PMU_SOFTRESETON_TELOMERESS_0_SRST_NRSTDIV2_N_MASK |
			PMU_SOFTRESETON_TELOMERESS_0_SRST_ASYNCWRSTDIV2_TELOMERE_N_MASK |
			PMU_SOFTRESETON_TELOMERESS_0_SRST_MIXEDWRSTDIV2_TELOMERE_N_MASK |
			PMU_SOFTRESETON_TELOMERESS_0_SRST_MIXEDWRSTDIV2_EMMC8SD_H_N_MASK |
			PMU_SOFTRESETON_TELOMERESS_0_SRST_ASYNCWRSTDIV2_EMMC8SD_X_N_MASK;
		const __u32 SOFTRESETOFF_VAL =
			PMU_SOFTRESETOFF_TELOMERESS_0_SRST_ASYNCNRSTDIV2_N_MASK |
			PMU_SOFTRESETOFF_TELOMERESS_0_SRST_ASYNCWRSTDIV2_TELOMERE_N_MASK |
			PMU_SOFTRESETOFF_TELOMERESS_0_SRST_MIXEDWRSTDIV2_TELOMERE_N_MASK |
			PMU_SOFTRESETOFF_TELOMERESS_0_SRST_MIXEDWRSTDIV2_EMMC8SD_H_N_MASK |
			PMU_SOFTRESETOFF_TELOMERESS_0_SRST_ASYNCWRSTDIV2_EMMC8SD_X_N_MASK;

		cgoff = lcdc_read_reg(priv.pmu_regs, PMU_CLOCKGATINGOFF_TELOMERESS_0_OFS);
		sroff = lcdc_read_reg(priv.pmu_regs, PMU_SOFTRESETOFF_TELOMERESS_0_OFS);

		if (((CLOCKGATINGOFF_VAL & cgoff) != CLOCKGATINGOFF_VAL) ||
		    ((SOFTRESETOFF_VAL & sroff) != SOFTRESETOFF_VAL)) {
			/* SoftResetOn SRAM */
			lcdc_write_reg(priv.pmu_regs, PMU_SOFTRESETON_TELOMERESS_0_OFS, SOFTRESETON_VAL);

			/* ClockGatingOff SRAM */
			lcdc_write_reg(priv.pmu_regs, PMU_CLOCKGATINGOFF_TELOMERESS_0_OFS, CLOCKGATINGOFF_VAL);

			/* SoftResetOff SRAM */
			lcdc_write_reg(priv.pmu_regs, PMU_SOFTRESETOFF_TELOMERESS_0_OFS, SOFTRESETOFF_VAL);
			/* 100ns wait */
			ndelay(100);
		}
	}

#endif
	for (ii = 0; ii < TZ2000_MAX_LAYER; ii++) {
		priv.layer[ii].layer = ii;
		priv.layer[ii].pixelformat = DEFAULT_FORMAT;

		if (ii == 0)
			priv.layer[ii].size = PAGE_ALIGN(MAX_FB_SIZE + GFX_WORK_SIZE);
		else
			priv.layer[ii].size = 0;

		if (priv.layer[ii].size > 0) {
#if IS_ENABLED(CONFIG_FB_APPLITE_BASIC_RESOURCE_MINIMAL_SRAM)
			priv.layer[ii].addr = CPU_SRAM_REG_BASE;
			if (!request_mem_region(priv.layer[ii].addr, priv.layer[ii].size, "TZ2000-SRAM")) {
				pr_err("request_mem_region failed.\n");
				goto err1;
			}
			priv.layer[ii].memory = ioremap_nocache(
					priv.layer[ii].addr,
					priv.layer[ii].size);
			tz2000fb_sram_vtop_reg_base = virt_to_phys(priv.layer[ii].memory);
#else
			priv.layer[ii].memory = dma_alloc_coherent(
					NULL,
					priv.layer[ii].size,
					(dma_addr_t *)&priv.layer[ii].addr,
					GFP_KERNEL);
#endif
			if (!priv.layer[ii].memory)
				goto err1;
		}
	}

	if (DEFAULT_FORMAT == ARGB32_ARGB8888)
		priv.is_argb = true;
	else
		priv.is_argb = false;

	/*
	 * VFB must clear memory to prevent kernel info
	 * leakage into userspace
	 * VGA-based drivers MUST NOT clear memory if
	 * they want to be able to take over vgacon
	 */
	for (ii = 0; ii < TZ2000_MAX_LAYER; ii++)
		if (priv.layer[ii].size > 0)
			memset(priv.layer[ii].memory, 0, priv.layer[ii].size);

	priv.info[0] = framebuffer_alloc(sizeof(struct fb_info), &pdev->dev);
	if (!priv.info[0])
		goto err1;

	priv.info[0]->screen_base = (char __iomem *)priv.layer[0].memory;
	priv.info[0]->fbops = &tz2000fb_ops;

	retval = fb_find_mode(&priv.info[0]->var, priv.info[0], NULL,
			      NULL, 0, NULL, 32);

	if (!retval || (retval == 4))
		priv.info[0]->var = tz2000fb_default;
	tz2000fb_fix.smem_start = (unsigned long)priv.layer[0].memory;
	tz2000fb_fix.smem_len = priv.layer[0].size;
	tz2000fb_fix.ypanstep =	(magnification > 1) ? 1 : 0,
	priv.info[0]->fix = tz2000fb_fix;
	priv.info[0]->pseudo_palette = priv.info[0]->par;
	priv.info[0]->par = &priv.layer[0];
	priv.info[0]->flags = FBINFO_FLAG_DEFAULT;
	switch (fb_mode) {
	case 0:
		priv.info[0]->var.xres = DEFAULT_XRES;
		priv.info[0]->var.yres = DEFAULT_YRES;
		break;
	case 1:	/* 800x480@58.19 F07A-0102 */
		priv.info[0]->var.xres = 800;
		priv.info[0]->var.yres = 480;
		break;
	case 2:	/* 480x272@84.38 NHD4_3 */
	case 3:	/* 480x272@59.94 NHD4_3 */
	case 4:	/* 480x272@29.97 NHD4_3 */
	case 5:	/* 480x272@59.94 ILI6480G2 */
	case 6:	/* 480x272@29.97 ILI6480G2 */
		priv.info[0]->var.xres = 480;
		priv.info[0]->var.yres = 272;
		break;
	}
	priv.info[0]->var.xres_virtual = priv.info[0]->var.xres;
	priv.info[0]->var.yres_virtual = priv.info[0]->var.yres * magnification;

	priv.layer[0].xres = priv.layer[0].dxres = priv.info[0]->var.xres;
	priv.layer[0].yres = priv.layer[0].dyres = priv.info[0]->var.yres;
	priv.layer[0].vxres = priv.info[0]->var.xres_virtual;
	priv.layer[0].vyres = priv.info[0]->var.yres_virtual;
	priv.layer[0].xlstart = 0;
	priv.layer[0].ylstart = 0;

	retval = fb_alloc_cmap(&priv.info[0]->cmap, 256, 0);
	if (retval < 0)
		goto err2;

	retval = register_framebuffer(priv.info[0]);
	if (retval < 0)
		goto err3;
	platform_set_drvdata(pdev, priv.info[0]);

	spin_lock_init(&priv.lcdc_slock);

	/* Registration interrupt handler of APC */
	irq[0] = platform_get_irq(pdev, 0);
	retval = request_irq(irq[0], tz2000fb_lcdc_intr,
			     IRQF_SHARED, tz2000fb_devname, &priv);
	if (retval) {
		dev_err(&pdev->dev, "Unable to register interrupt.\n");
		goto err4;
	}
	/* Registration interrupt handler of GDC */
	irq[1] = platform_get_irq(pdev, 1);
	retval = request_irq(irq[1], tz2000fb_lcdc_intr,
			     IRQF_SHARED, tz2000fb_devname, &priv);
	if (retval) {
		dev_err(&pdev->dev, "Unable to register interrupt.\n");
		goto err5;
	}

	init_completion(&priv.vsync_completion);

	priv.clk_lcdc = clk_get(&(pdev->dev), "lcdc");
	if (IS_ERR(priv.clk_lcdc)) {
		dev_err(&pdev->dev, "clk_get(%s, lcdc) failed\n",
					dev_name(&(pdev->dev)));
		retval = -EFAULT;
		goto err6;
	}
#if defined(_MERGE_FBDEV_)
	priv.clk_gfx = clk_get(&(pdev->dev), "gfx");
	if (IS_ERR(priv.clk_gfx)) {
		dev_err(&pdev->dev, "clk_get(%s, gfx) failed\n", dev_name(&(pdev->dev)));
		clk_put(priv.clk_lcdc);
		retval = -EFAULT;
		goto err6;
	}
#endif /* defined(_MERGE_FBDEV_) */

#if defined(_MERGE_FBDEV_)
	/* reset assert */
	lcdc_write_reg(priv.pmu_regs, PMU_SOFTRESETON_GFXSS_0_OFS, 0x00000001);

	tz2000gfx_init();

#endif /* defined(_MERGE_FBDEV_) */
#if IS_ENABLED(CONFIG_PM_RUNTIME)
	pm_runtime_enable(&(pdev->dev));

	/* call tz2000fb_runtime_resume() directly */
	pm_runtime_get_sync(&(pdev->dev));

#else
	tz2000fb_runtime_resume(&(pdev->dev));

#endif /* IS_ENABLED(CONFIG_PM_RUNTIME) */
	lcdc_cleanup();
	retval = lcdc_setup();
	if (retval < 0)
		goto err6;

	pr_info("fb%d: TZ2000 frame buffer device, using %dK of video memory\n",
		priv.info[0]->node, priv.layer[0].size >> 10);

	return 0;

	lcdc_cleanup();
err6:
	free_irq(irq[1], &priv);
err5:
	free_irq(irq[0], &priv);
err4:
	unregister_framebuffer(priv.info[0]);
err3:
	fb_dealloc_cmap(&priv.info[0]->cmap);
err2:
	framebuffer_release(priv.info[0]);
err1:
	for (ii = 0; ii < TZ2000_MAX_LAYER; ii++)
#if IS_ENABLED(CONFIG_FB_APPLITE_BASIC_RESOURCE_MINIMAL_SRAM)
		if (priv.layer[ii].size > 0) {
			iounmap(priv.layer[ii].memory);
			release_mem_region(priv.layer[ii].addr, priv.layer[ii].size);
		}
#else
		if (priv.layer[ii].size > 0)
			dma_free_coherent(NULL,
					  priv.layer[ii].size,
					  priv.layer[ii].memory,
					  (dma_addr_t)priv.layer[ii].addr);
#endif

err0:
	if (priv.gfx_regs)
		iounmap(priv.gfx_regs);
	if (priv.pmu_regs)
		iounmap(priv.pmu_regs);
	if (priv.lcdc_regs)
		iounmap(priv.lcdc_regs);

	return retval;
}

static int __devexit tz2000fb_remove(struct platform_device *pdev)
{
	unsigned int ii;
	int irq[2];

	if (priv.info[0]) {
		lcdc_cleanup();

#if defined(_MERGE_FBDEV_)
		tz2000gfx_exit();

#endif /* defined(_MERGE_FBDEV_) */
#if IS_ENABLED(CONFIG_PM_RUNTIME)
		/* call tz2000fb_runtime_suspend() directly */
		pm_runtime_put_sync(&(pdev->dev));

		pm_runtime_disable(&(pdev->dev));
#else
		tz2000fb_runtime_suspend(&(pdev->dev));
#endif /* IS_ENABLED(CONFIG_PM_RUNTIME) */
		clk_put(priv.clk_lcdc);
#if defined(_MERGE_FBDEV_)
		clk_put(priv.clk_gfx);
#endif /* defined(_MERGE_FBDEV_) */

		irq[0] = platform_get_irq(pdev, 0);
		irq[1] = platform_get_irq(pdev, 1);
		free_irq(irq[1], &priv);
		free_irq(irq[0], &priv);

		unregister_framebuffer(priv.info[0]);

		fb_dealloc_cmap(&priv.info[0]->cmap);
		framebuffer_release(priv.info[0]);

		for (ii = 0; ii < TZ2000_MAX_LAYER; ii++)
#if IS_ENABLED(CONFIG_FB_APPLITE_BASIC_RESOURCE_MINIMAL_SRAM)
			if (priv.layer[ii].size > 0) {
				iounmap(priv.layer[ii].memory);
				release_mem_region(priv.layer[ii].addr, priv.layer[ii].size);
			}
#else
			if (priv.layer[ii].size > 0)
				dma_free_coherent(NULL,
						  priv.layer[ii].size,
						  priv.layer[ii].memory,
						  (dma_addr_t)priv.layer[ii].addr);
#endif

		if (priv.gfx_regs)
			iounmap(priv.gfx_regs);
		if (priv.pmu_regs)
			iounmap(priv.pmu_regs);
		if (priv.lcdc_regs)
			iounmap(priv.lcdc_regs);
	}

	return 0;
}

#ifdef CONFIG_PM
static int tz2000fb_freeze(struct device *dev)
{
	lcdc_cleanup();
	tz2000fb_hw_stop();

	return 0;
}

static const struct dev_pm_ops tz2000fb_pm_ops = {
	.suspend = tz2000fb_suspend,
	.resume = tz2000fb_resume,
	.freeze = tz2000fb_freeze,
	.thaw = tz2000fb_resume,
	.restore = tz2000fb_resume,
#if IS_ENABLED(CONFIG_PM_RUNTIME)
	.runtime_suspend = tz2000fb_runtime_suspend,
	.runtime_resume = tz2000fb_runtime_resume,
#endif /* IS_ENABLED(CONFIG_PM_RUNTIME) */
};

#endif
static struct platform_driver tz2000fb_driver = {
	.probe	= tz2000fb_probe,
	.remove = tz2000fb_remove,
	.driver = {
		.name	= "tz2000fb",
		.owner = THIS_MODULE,
#ifdef CONFIG_PM
		.pm = &tz2000fb_pm_ops,
#endif
	},
};

static int __init tz2000fb_init(void)
{
	int ret = 0;
#ifndef MODULE
	char *option = NULL;

	if (fb_get_options("tz2000fb", &option))
		return -ENODEV;
	tz2000fb_setup(option);
#endif

	ret = platform_driver_register(&tz2000fb_driver);

	return ret;
}

module_init(tz2000fb_init);

#ifdef MODULE
static void __exit tz2000fb_exit(void)
{
	platform_driver_unregister(&tz2000fb_driver);
}

module_exit(tz2000fb_exit);

/* MODULE INFORMATION */
MODULE_AUTHOR("TOSHIBA Corporation");
MODULE_DESCRIPTION("Display Driver");
MODULE_VERSION(DISPLAY_DRIVER_VERSION);
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("display");
#endif				/* MODULE */
