/*
 * linux/drivers/video/applite/applitefb_tz2000fb.c
 *
 * (C) Copyright TOSHIBA Corporation
 * Semiconductor & Storage Products Company 2013
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
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/fb.h>
#include <linux/init.h>
#include <linux/pci.h>

#include <linux/pm_runtime.h>
#include <linux/clk.h>

#include <linux/videodev2.h>
#include <mach/regs/pmu_offs_def.h>
#include <mach/regs/pmu_reg_def.h>
#include <mach/regs/lcdc_offs_def.h>
#include <mach/regs/lcdc_reg_def.h>
#include <linux/uaccess.h>
#include <linux/i2c.h>
#include <linux/gpio.h>

#include "applitefb.h"
#include "applitefb_tz2000.h"
#include "tz2000gfx_internal.h"


u_long gfx_size = CONFIG_APPLITEFB_DEFAULT_GFX_SIZE * 1024 * 1024;
module_param(gfx_size, ulong, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(gfx_size, "Set gfx_size value [MB]");

enum regist {
	GDCDSR_L,	/* start address for display */
	GDCDIMR_L,	/* size of display */
	GDCHSR_L,	/* parameter of horizon */
	GDCVSR_L,	/* parameter of vertical */
	MAX_REG_PARAM
};


/* default start position */
static __u16 tz2000_def_pos[][2] = {
	{ 0x006A, 0x004C },		/* 480x272 */
	{ 0x00C0, 0x005F }		/* 800x480 */
};


/* LCDC Setting Table */
static struct reg_param tz2000_reg_param[][MAX_REG_PARAM] = {
	{/* 480x272 */
		{0, LCDC_GDCDSR_L_OFFS, 0x006a004c},		/* GDCDSR  */
		{0, LCDC_GDCDIMR_L_OFFS, 0x01e00110},		/* GDCDIMR */
		{0, LCDC_GDCHSR_L_OFFS, 0x0029020D},		/* GDCHSR  */
		{0, LCDC_GDCVSR_L_OFFS, 0x000a011e}		/* GDCVSR  */
	},
	{/* 800x480 */
		{0, LCDC_GDCDSR_L_OFFS, 0x00c0005f},		/* GDCDSR  */
		{0, LCDC_GDCDIMR_L_OFFS, 0x032001e0},		/* GDCDIMR */
		{0, LCDC_GDCHSR_L_OFFS, 0x00170420},		/* GDCHSR  */
		{0, LCDC_GDCVSR_L_OFFS, 0x0002020d}		/* GDCVSR  */
	}
};

struct debug_reg_param debug_regist[] = {
	{ "GDCDCR_L"		, 0x0000},
	{ "GDCDCR_U"		, 0x0004},
	{ "GDCLARA0_L"		, 0x0010},
	{ "GDCLARA1_L"		, 0x0018},
	{ "GDCWARA_L"		, 0x0020},
	{ "GDCBGCR_L"		, 0x0028},
	{ "GDCLARB0_L"		, 0x0030},
	{ "GDCLARB1_L"		, 0x0038},
	{ "GDCWARB_L"		, 0x0040},
	{ "GDCLARC0_L"		, 0x0048},
	{ "GDCLARC1_L"		, 0x0050},
	{ "GDCLARD0_L"		, 0x0058},
	{ "GDCLARD1_L"		, 0x0060},
	{ "GDCMWRA_L"		, 0x0068},
	{ "GDCMWRB_L"		, 0x0070},
	{ "GDCMWRC_L"		, 0x0078},
	{ "GDCMWRD_L"		, 0x0080},
	{ "GDCMWRE_L"		, 0x0088},
	{ "GDCLSRA_L"		, 0x0090},
	{ "GDCLSRB_L"		, 0x0098},
	{ "GDCLSRC_L"		, 0x00A0},
	{ "GDCLSRD_L"		, 0x00A8},
	{ "GDCLSRE_L"		, 0x00B0},
	{ "GDCLDRA_L"		, 0x00B8},
	{ "GDCLDRB_L"		, 0x00C0},
	{ "GDCLDRC_L"		, 0x00C8},
	{ "GDCLDRD_L"		, 0x00D0},
	{ "GDCLDRE_L"		, 0x00D8},
	{ "GDCWSRA_L"		, 0x00E0},
	{ "GDCWSRB_L"		, 0x00E8},
	{ "GDCWIMRA_L"		, 0x00F0},
	{ "GDCWIMRB_L"		, 0x00F8},
	{ "GDCCAVRA_L"		, 0x0100},
	{ "GDCCAVRA_U"		, 0x0104},
	{ "GDCCAVRB_L"		, 0x0108},
	{ "GDCHSR_L"		, 0x0110},
	{ "GDCVSR_L"		, 0x0118},
	{ "GDCDCPR_L"		, 0x0120},
	{ "GDCDCPR_U"		, 0x0124},
	{ "GDCCBAR0_L"		, 0x0128},
	{ "GDCCBAR1_L"		, 0x0130},
	{ "GDCCBAR2_L"		, 0x0138},
	{ "GDCINTR_L"		, 0x0140},
	{ "GDCINTR_U"		, 0x0144},
	{ "GDCLARE0_L"		, 0x0230},
	{ "GDCLARE1_L"		, 0x0238},
	{ "GDCWARC_L"		, 0x0240},
	{ "GDCWARD_L"		, 0x0248},
	{ "GDCWARE_L"		, 0x0250},
	{ "GDCWSRC_L"		, 0x0258},
	{ "GDCWSRD_L"		, 0x0260},
	{ "GDCWSRE_L"		, 0x0268},
	{ "GDCWIMRC_L"		, 0x0270},
	{ "GDCWIMRD_L"		, 0x0278},
	{ "GDCWIMRE_L"		, 0x0280},
	{ "GDCDSR_L"		, 0x02B0},
	{ "GDCDIMR_L"		, 0x02B8},
};

static inline void plane_a_set(void);
static inline void plane_b_set(void);
static inline void plane_c_set(void);
static inline void plane_d_set(void);
static inline void plane_e_set(void);

static inline void plane_a_pan(void);
static inline void plane_b_pan(void);
static inline void plane_c_pan(void);
static inline void plane_d_pan(void);
static inline void plane_e_pan(void);


static void applitefb_reg_write(u32 mode, u32 regist)
{
	lcdc_write(&priv,
		tz2000_reg_param[mode][regist].reg_offset,
		tz2000_reg_param[mode][regist].val);
}

/* waits till the vsync interruption. */
int applitefb_wait_for_frame_end(unsigned int fconv)
{
	int ret;
	u32 gdcintr_l;

	mutex_lock(&applitefb_lock);
	gdcintr_l = lcdc_read(&priv, LCDC_GDCINTR_L_OFFS);
	gdcintr_l |= (HSYNC_IRQ_IS_256 | VSYNC_IRQ_MASK); /* unmask VSYNCMSK */
	lcdc_write(&priv, LCDC_GDCINTR_L_OFFS, gdcintr_l);

	/* Waiting for vsync */
	ret = wait_for_completion_interruptible_timeout(
		&priv.vsync_completion, msecs_to_jiffies(100));

	mutex_unlock(&applitefb_lock);
	if (!ret) {
		_ERR_LOG("tz2000fb_pan_display() timeout\n");
		return -ETIMEDOUT;
	} else if (ret < 0) {
		_ERR_LOG("err[%d]\n", ret);
		return ret;
	}
	return ret;
}
/* Pan the display */
int pan_display(struct fb_var_screeninfo *var, struct fb_info *info)
{
	int ret;
	u32 offset;
	struct applitefb_layer *layer = (struct applitefb_layer *)(info->par);

	_FNC_START("\n");

	offset = (var->yoffset * info->var.xres_virtual) *
		info->var.bits_per_pixel / 8 +
		var->xoffset * info->var.bits_per_pixel / 8;

	layer->addr[0] =
		info->fix.smem_start + offset;

	ret = applitefb_wait_for_frame_end(layer->layer);

	if (!ret) {
		_ERR_LOG("pan_display() timeout\n");
		return -ETIMEDOUT;
	} else if (ret < 0) {
		_ERR_LOG("pan_display() err\n");
		return ret;
	}

	_FNC_END("\n");
	return ret;
}

/* Registration interrupt handler */
void regist_irq(struct platform_device *pdev)
{
	int retval, irq[2];

	_FNC_START("\n");
	/* Registration interrupt handler of APC */
	irq[0] = platform_get_irq(pdev, 0);
	retval = request_irq(irq[0], handle_irq,
		IRQF_SHARED, "applitefb", &priv);

	if (retval) {
		_ERR_LOG("request_irq[%d] failed\n", irq[0]);
		retval = -EBUSY;
		goto fail_1;
	}
	/* Registration interrupt handler of GDC */
	irq[1] = platform_get_irq(pdev, 1);
	retval = request_irq(irq[1], handle_irq,
		IRQF_SHARED, "applitefb", &priv);

	if (retval) {
		_ERR_LOG("request_irq[%d] failed\n", irq[1]);
		retval = -EBUSY;
		goto fail_2;
	}
	_FNC_END("\n");
	return;
fail_2:
	/* Release of interruption */
	free_irq(irq[0], &priv);
fail_1:
	_FNC_END("FAILED\n");
	return;
}

/* Release of interruption */
void _free_irq(struct platform_device *pdev)
{
	int irq[2];

	_FNC_START("\n");
	irq[0] = platform_get_irq(pdev, 0);
	irq[1] = platform_get_irq(pdev, 1);
	free_irq(irq[1], &priv);
	free_irq(irq[0], &priv);
	_FNC_END("\n");
	return;
}

#if IS_ENABLED(CONFIG_FB_APPLITE_PANEL_ILI6480G2_59) ||\
	IS_ENABLED(CONFIG_FB_APPLITE_PANEL_ILI6480G2_29)

#if IS_ENABLED(CONFIG_APPLITE_PWM)
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/pwm.h>

struct pwm_device {
	struct list_head	node;
	struct platform_device *pdev;
	struct clk	*clk;

	const char	*label;

	void __iomem	*mmio_base;
	void __iomem	*pmu_base;

	unsigned int	use_count;
	unsigned int	pwm_id;

	unsigned int	iteration;

	unsigned int	div;
	unsigned int	pol;
	unsigned int	lvs;
	unsigned int	enbsel;

	unsigned int	genb_set;
};
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

#endif	/* CONFIG_APPLITE_PWM */
#endif	/* ONFIG_FB_APPLITE_PANEL_ILI6480G2_59 || CONFIG_FB_APPLITE_PANEL_ILI6480G2_29 */

/* register setting of PMU */
static void pmu_initialize(struct fb_var_screeninfo *var)
{
	_FNC_START("\n");
	/* setting of PMU */
	pmu_write(&priv, PMU_SoftResetOff_lcdcSS_0_OFFS, SOFTRESETON);
	pmu_write(&priv, PMU_PANEL_CLOCK_0_OFFS, PANELCLOCK_VAL);
	pmu_write(&priv, PMU_PLLConfig_PLLLCD_0_OFFS, PLLCONFIG0_VAL);
	pmu_write(&priv, PMU_PLLConfig_PLLLCD_1_OFFS, PLLCONFIG1_VAL);
	_FNC_END("\n");
}


/* setting of display control */
static void lcdc_control_set(void)
{
	__u32 config_u, config_l;


	_FNC_START("%d/%d/%d/%d/%d\n",
		g_fb_layer[0].format, g_fb_layer[1].format,
		g_fb_layer[2].format, g_fb_layer[3].format,
		g_fb_layer[4].format);

	/* setting of display control */
	config_l = (HDISP_MODE | DOTCLOCK_SELECT | DOTCLOCK_POLARITY |
			LAYER_A_EN | LAYER_B_EN | LAYER_C_EN |
			LAYER_D_EN);
	config_u = (GDC_ON | LAYER_E_EN);

	if (g_fb_layer[0].format == RGB565)
		config_l |= LAYER_A_FORMAT_IS_16BIT;
	if (g_fb_layer[1].format == RGB565)
		config_l |= LAYER_B_FORMAT_IS_16BIT;
	if (g_fb_layer[2].format == RGB565)
		config_l |= LAYER_C_FORMAT_IS_16BIT;
	if (g_fb_layer[3].format == RGB565)
		config_l |= LAYER_D_FORMAT_IS_16BIT;
	if (g_fb_layer[4].format == RGB565)
		config_u |= LAYER_E_FORMAT_IS_16BIT;
	if (priv.is_rgba == false) {
		/* ARGB8888*/
		_DBG_LOG("format is ARGB8888\n");
		config_u |= (BIT_FORMAT_IS_32);
	}

	lcdc_write(&priv, LCDC_GDCDCR_L_OFFS, config_l);
	lcdc_write(&priv, LCDC_GDCDCR_U_OFFS, config_u);

	/* setting of alpha parameter */
	lcdc_write(&priv, LCDC_GDCCAVRA_L_OFFS, ((a_alpha) | (b_alpha << 16)));
	lcdc_write(&priv, LCDC_GDCCAVRA_U_OFFS, ((c_alpha) | (d_alpha << 16)));
	lcdc_write(&priv, LCDC_GDCCAVRB_L_OFFS, e_alpha);

	_FNC_END("\n");
}

static void format_set(void)
{
	__u32 config_u;

	_FNC_START("%d/%d/%d/%d/%d\n",
		g_fb_layer[0].format, g_fb_layer[1].format,
		g_fb_layer[2].format, g_fb_layer[3].format,
		g_fb_layer[4].format);

	config_u = lcdc_read(&priv, LCDC_GDCDCR_U_OFFS);
	if (priv.is_rgba == false) {
		/* ARGB8888*/
		_DBG_LOG("format is ARGB8888\n");
		config_u |= (BIT_FORMAT_IS_32);
	} else {
		/* RGBA8888*/
		_DBG_LOG("format is RGBA8888\n");
		config_u &= ~(BIT_FORMAT_IS_32);
	}
	lcdc_write(&priv, LCDC_GDCDCR_U_OFFS, config_u);

	_FNC_END("\n");
}

void format_adjustment(void)
{
	__u32 i;
	struct fb_bitfield rgba8888_red		= {24, 8, 0};
	struct fb_bitfield rgba8888_green	= {16, 8, 0};
	struct fb_bitfield rgba8888_blue	= { 8, 8, 0};
	struct fb_bitfield rgba8888_transp	= { 0, 8, 0};
	struct fb_bitfield argb8888_red		= {16, 8, 0};
	struct fb_bitfield argb8888_green	= { 8, 8, 0};
	struct fb_bitfield argb8888_blue	= { 0, 8, 0};
	struct fb_bitfield argb8888_transp	= {24, 8, 0};

	_FNC_START("\n");
	for (i = 1; i < CONFIG_APPLITEFB_ENABLE_LAYER; i++) {
		if ((g_fb_layer[i].format == RGBA8888) && (priv.is_rgba == false)) {
			/* ARGB8888*/
			_DBG_LOG("adjust to ARGB8888\n");
			priv.info[i]->var.red		= argb8888_red;
			priv.info[i]->var.green		= argb8888_green;
			priv.info[i]->var.blue		= argb8888_blue;
			priv.info[i]->var.transp	= argb8888_transp;
			g_fb_layer[i].format = ARGB8888;
			/* call function of framework */
		} else if ((g_fb_layer[i].format == ARGB8888) && (priv.is_rgba == true)) {
			_DBG_LOG("adjust to RGBA8888\n");
			priv.info[i]->var.red		= rgba8888_red;
			priv.info[i]->var.green		= rgba8888_green;
			priv.info[i]->var.blue		= rgba8888_blue;
			priv.info[i]->var.transp	= rgba8888_transp;
			g_fb_layer[i].format = RGBA8888;
		}
	}
	format_set();

	_FNC_END("\n");
}

static inline void plane_a_display_position(void)
{
	lcdc_write(&priv, LCDC_GDCLSRA_L_OFFS,
		_MK_GDCLSRx_L((g_fb_layer[0].xpos + tz2000_def_pos[DISPLAY_MODE][0]),
			 (g_fb_layer[0].ypos + tz2000_def_pos[DISPLAY_MODE][1])));
	lcdc_write(&priv, LCDC_GDCLDRA_L_OFFS, (g_fb_layer[0].dxres << 16 | g_fb_layer[0].dyres));

	g_fb_layer[0].xpos_old = g_fb_layer[0].xpos;
	g_fb_layer[0].ypos_old = g_fb_layer[0].ypos;
}

static inline void plane_b_display_position(void)
{
	lcdc_write(&priv, LCDC_GDCLSRB_L_OFFS,
		_MK_GDCLSRx_L((g_fb_layer[1].xpos + tz2000_def_pos[DISPLAY_MODE][0]),
			 (g_fb_layer[1].ypos + tz2000_def_pos[DISPLAY_MODE][1])));
	lcdc_write(&priv, LCDC_GDCLDRB_L_OFFS, (g_fb_layer[1].dxres << 16 | g_fb_layer[1].dyres));

	g_fb_layer[1].xpos_old = g_fb_layer[1].xpos;
	g_fb_layer[1].ypos_old = g_fb_layer[1].ypos;
}

static inline void plane_c_display_position(void)
{
	lcdc_write(&priv, LCDC_GDCLSRC_L_OFFS,
		_MK_GDCLSRx_L((g_fb_layer[2].xpos + tz2000_def_pos[DISPLAY_MODE][0]),
			 (g_fb_layer[2].ypos + tz2000_def_pos[DISPLAY_MODE][1])));
	lcdc_write(&priv, LCDC_GDCLDRC_L_OFFS, (g_fb_layer[2].dxres << 16 | g_fb_layer[2].dyres));

	g_fb_layer[2].xpos_old = g_fb_layer[2].xpos;
	g_fb_layer[2].ypos_old = g_fb_layer[2].ypos;
}

static inline void plane_d_display_position(void)
{
	lcdc_write(&priv, LCDC_GDCLSRD_L_OFFS,
		_MK_GDCLSRx_L((g_fb_layer[3].xpos + tz2000_def_pos[DISPLAY_MODE][0]),
			 (g_fb_layer[3].ypos + tz2000_def_pos[DISPLAY_MODE][1])));
	lcdc_write(&priv, LCDC_GDCLDRD_L_OFFS, (g_fb_layer[3].dxres << 16 | g_fb_layer[3].dyres));

	g_fb_layer[3].xpos_old = g_fb_layer[3].xpos;
	g_fb_layer[3].ypos_old = g_fb_layer[3].ypos;
}

static inline void plane_e_display_position(void)
{
	lcdc_write(&priv, LCDC_GDCLSRE_L_OFFS,
		_MK_GDCLSRx_L((g_fb_layer[4].xpos + tz2000_def_pos[DISPLAY_MODE][0]),
			 (g_fb_layer[4].ypos + tz2000_def_pos[DISPLAY_MODE][1])));
	lcdc_write(&priv, LCDC_GDCLDRE_L_OFFS, (g_fb_layer[4].dxres << 16 | g_fb_layer[4].dyres));

	g_fb_layer[4].xpos_old = g_fb_layer[4].xpos;
	g_fb_layer[4].ypos_old = g_fb_layer[4].ypos;
}

static inline void plane_a_pan(void)
{
#if 0
	lcdc_write(&priv, LCDC_GDCLARA0_L_OFFS, (u32)g_fb_layer[0].addr[0]);
#else
	if (g_fb_layer[0].addr[0] != g_fb_layer[0].addr_old[0]) {
		lcdc_write(&priv, LCDC_GDCLARA0_L_OFFS, (u32)g_fb_layer[0].addr[0]);
		g_fb_layer[0].addr_old[0] = g_fb_layer[0].addr[0];
	}
#endif

	if ((g_fb_layer[0].xpos != g_fb_layer[0].xpos_old) ||
		(g_fb_layer[0].ypos != g_fb_layer[0].ypos_old)) {
		plane_a_display_position();
	}
}

static inline void plane_b_pan(void)
{
#if 0
	lcdc_write(&priv, LCDC_GDCLARB0_L_OFFS, (__u32)g_fb_layer[1].addr[0]);
#else
	if (g_fb_layer[1].addr[0] != g_fb_layer[1].addr_old[0]) {
		lcdc_write(&priv, LCDC_GDCLARB0_L_OFFS, (u32)g_fb_layer[1].addr[0]);
		g_fb_layer[1].addr_old[0] = g_fb_layer[1].addr[0];
	}
#endif

	if ((g_fb_layer[1].xpos != g_fb_layer[1].xpos_old) ||
		(g_fb_layer[1].ypos != g_fb_layer[1].ypos_old)) {
		plane_b_display_position();
	}
}

static inline void plane_c_pan(void)
{
#if 0
	lcdc_write(&priv, LCDC_GDCLARC0_L_OFFS, (__u32)g_fb_layer[2].addr[0]);
#else
	if (g_fb_layer[2].addr[0] != g_fb_layer[2].addr_old[0]) {
		lcdc_write(&priv, LCDC_GDCLARC0_L_OFFS, (__u32)g_fb_layer[2].addr[0]);
		g_fb_layer[2].addr_old[0] = g_fb_layer[2].addr[0];
	}
#endif
	if ((g_fb_layer[2].xpos != g_fb_layer[2].xpos_old) ||
		(g_fb_layer[2].ypos != g_fb_layer[2].ypos_old)) {
		plane_c_display_position();
	}
}

static inline void plane_d_pan(void)
{
#if 0
	lcdc_write(&priv, LCDC_GDCLARD0_L_OFFS, (__u32)g_fb_layer[3].addr[0]);
#else
	if (g_fb_layer[3].addr[0] != g_fb_layer[3].addr_old[0]) {
		lcdc_write(&priv, LCDC_GDCLARD0_L_OFFS, (__u32)g_fb_layer[3].addr[0]);
		g_fb_layer[3].addr_old[0] = g_fb_layer[3].addr[0];
	}
#endif
	if ((g_fb_layer[3].xpos != g_fb_layer[3].xpos_old) ||
		(g_fb_layer[3].ypos != g_fb_layer[3].ypos_old)) {
		plane_d_display_position();
	}
}

static inline void plane_e_pan(void)
{
#if 0
	lcdc_write(&priv, LCDC_GDCLARE0_L_OFFS, (__u32)g_fb_layer[4].addr[0]);
#else
	if (g_fb_layer[4].addr[0] != g_fb_layer[4].addr_old[0]) {
		lcdc_write(&priv, LCDC_GDCLARE0_L_OFFS, (__u32)g_fb_layer[4].addr[0]);
		g_fb_layer[4].addr_old[0] = g_fb_layer[4].addr[0];
	}
#endif
	if ((g_fb_layer[4].xpos != g_fb_layer[4].xpos_old) ||
		(g_fb_layer[4].ypos != g_fb_layer[4].ypos_old)) {
		plane_e_display_position();
	}
}

void plane_pan(int node)
{
	_FNC_START("node[%d]\n", node);

	switch (node) {
	case 0:
		plane_a_pan();
		break;
	case 1:
		plane_b_pan();
		break;
	case 2:
		plane_c_pan();
		break;
	case 3:
		plane_d_pan();
		break;
	case 4:
		plane_e_pan();
		break;
	default:
		_ERR_LOG("invalid node(%d)\n", node);
	}

	_FNC_END("\n");
}

/* register setting of Layer A */
static inline void plane_a_set(void)
{
	_FNC_START("\n");

	/* setting of Layer A */
	lcdc_write(&priv, LCDC_GDCMWRA_L_OFFS, priv.info[0]->var.xres_virtual);
	plane_a_display_position();

	/* setting of start address */
	lcdc_write(&priv, LCDC_GDCLARA0_L_OFFS, (u32)g_fb_layer[0].addr[0]);

	g_fb_layer[0].addr_old[0] = g_fb_layer[0].addr[0];
	_FNC_END("\n");
}

/* register setting of Layer B */
static inline void plane_b_set(void)
{
	_FNC_START("\n");

	/* setting of Layer B */
	lcdc_write(&priv, LCDC_GDCMWRB_L_OFFS, priv.info[1]->var.xres_virtual);
	plane_b_display_position();

	/* setting of start address */
	lcdc_write(&priv, LCDC_GDCLARB0_L_OFFS, (__u32)g_fb_layer[1].addr[0]);

	g_fb_layer[1].addr_old[0] = g_fb_layer[1].addr[0];
	_FNC_END("\n");
}

/* register setting of Layer C */
static inline void plane_c_set(void)
{
	_FNC_START("\n");

	/* setting of Layer C */
	lcdc_write(&priv, LCDC_GDCMWRC_L_OFFS, priv.info[2]->var.xres_virtual);
	plane_c_display_position();

	/* setting of start address */
	lcdc_write(&priv, LCDC_GDCLARC0_L_OFFS, (__u32)g_fb_layer[2].addr[0]);

	g_fb_layer[2].addr_old[0] = g_fb_layer[2].addr[0];
	_FNC_END("\n");
}

/* register setting of Layer D */
static inline void plane_d_set(void)
{
	_FNC_START("\n");

	/* setting of Layer D */
	lcdc_write(&priv, LCDC_GDCMWRD_L_OFFS, priv.info[3]->var.xres_virtual);
	plane_d_display_position();

	/* setting of start address */
	lcdc_write(&priv, LCDC_GDCLARD0_L_OFFS, (__u32)g_fb_layer[3].addr[0]);

	g_fb_layer[3].addr_old[0] = g_fb_layer[3].addr[0];
	_FNC_END("\n");
}

/* register setting of Layer E */
static inline void plane_e_set(void)
{
	_FNC_START("\n");

	/* setting of Layer E */
	lcdc_write(&priv, LCDC_GDCMWRE_L_OFFS, priv.info[4]->var.xres_virtual);
	plane_e_display_position();

	/* setting of start address */
	lcdc_write(&priv, LCDC_GDCLARE0_L_OFFS, (__u32)g_fb_layer[4].addr[0]);

	g_fb_layer[4].addr_old[0] = g_fb_layer[4].addr[0];
	_FNC_END("\n");
}

void plane_set(int node)
{
	_FNC_START("node[%d]\n", node);

	switch (node) {
	case 0:
		plane_a_set();
		break;
#if (CONFIG_APPLITEFB_ENABLE_LAYER > 1)
	case 1:
		plane_b_set();
		break;
#if (CONFIG_APPLITEFB_ENABLE_LAYER > 2)
	case 2:
		plane_c_set();
		break;
#if (CONFIG_APPLITEFB_ENABLE_LAYER > 3)
	case 3:
		plane_d_set();
		break;
#if (CONFIG_APPLITEFB_ENABLE_LAYER > 4)
	case 4:
		plane_e_set();
		break;
#endif	/* > 4 */
#endif	/* > 3 */
#endif	/* > 2 */
#endif	/* > 1 */
	default:
		_ERR_LOG("invalid node(%d)\n", node);
	}
	lcdc_control_set();

	_FNC_END("\n");
}


/* register setting when framebuffer is initialized */
void applitefb_lcdc_initialize(struct fb_var_screeninfo *var)
{
	u32 config_u;

	_FNC_START("\n");

#if IS_ENABLED(CONFIG_FB_APPLITE_PANEL_ILI6480G2_59) ||\
	IS_ENABLED(CONFIG_FB_APPLITE_PANEL_ILI6480G2_29)
	/* setting of PWM */
	pwm_start();
#endif

	/* setting of PMU */
	pmu_initialize(var);
	mdelay(1);

	/* setting of LayerA registers LAD=1->0 */
	config_u = lcdc_read(&priv, LCDC_GDCDCR_U_OFFS);
	config_u &= ~LAD;
	lcdc_write(&priv, LCDC_GDCDCR_U_OFFS, config_u);

	/* setting of LayerA */
	plane_a_set();

#if (CONFIG_APPLITEFB_ENABLE_LAYER > 1)
	/* setting of LayerB */
	plane_b_set();

#if (CONFIG_APPLITEFB_ENABLE_LAYER > 2)
	/* setting of LayerC */
	plane_c_set();

#if (CONFIG_APPLITEFB_ENABLE_LAYER > 3)
	/* setting of LayerD */
	plane_d_set();

#if (CONFIG_APPLITEFB_ENABLE_LAYER > 4)
	/* setting of LayerE */
	plane_e_set();
#endif	/* > 4 */
#endif	/* > 3 */
#endif	/* > 2 */
#endif	/* > 1 */

	lcdc_control_set();

	/* setting of LCDC */
	applitefb_reg_write(DISPLAY_MODE, GDCDSR_L);
	applitefb_reg_write(DISPLAY_MODE, GDCDIMR_L);
	applitefb_reg_write(DISPLAY_MODE, GDCHSR_L);
	applitefb_reg_write(DISPLAY_MODE, GDCVSR_L);

	_FNC_END("\n");
}

/* register setting when framebuffer is finalized */
void applitefb_lcdc_finalize(void)
{
	_FNC_START("\n");

	/* setting of interruption status */
	lcdc_write(&priv, LCDC_GDCINTR_L_OFFS, IRQ_FLAG);
	lcdc_write(&priv, LCDC_GDCINTR_U_OFFS,
		(PIXELCHECK_ERR_IRQ_FLAG | PIXELCHECK_EVENT_IRQ_FLAG));

	/* setting of display control */
	lcdc_write(&priv, LCDC_GDCDCR_U_OFFS, GDCDCR_U_CLEAR);
	lcdc_write(&priv, LCDC_GDCDCR_L_OFFS, GDCDCR_L_CLEAR);

	/* setting of soft reset on */
	pmu_write(&priv, PMU_SoftResetOn_lcdcSS_0_OFFS, SOFTRESETON);

#if IS_ENABLED(CONFIG_FB_APPLITE_PANEL_ILI6480G2_59) ||\
	IS_ENABLED(CONFIG_FB_APPLITE_PANEL_ILI6480G2_29)
	/* setting of PWM */
	pwm_stop();
#endif
	_FNC_END("\n");
}

static void lcdc_control_restart(void)
{
	__u32 config_u, config_l;

	_FNC_START("%d/%d/%d/%d/%d\n",
		g_fb_layer[0].format, g_fb_layer[1].format,
		g_fb_layer[2].format, g_fb_layer[3].format,
		g_fb_layer[4].format);

	/* setting of display control */
	config_l = (HDISP_MODE | DOTCLOCK_SELECT | DOTCLOCK_POLARITY |
			LAYER_A_EN | LAYER_B_EN | LAYER_C_EN |
			LAYER_D_EN);
	config_u = (GDC_ON | LAYER_E_EN);

	if (g_fb_layer[0].format == RGB565)
		config_l |= LAYER_A_FORMAT_IS_16BIT;
	if (g_fb_layer[1].format == RGB565)
		config_l |= LAYER_B_FORMAT_IS_16BIT;
	if (g_fb_layer[2].format == RGB565)
		config_l |= LAYER_C_FORMAT_IS_16BIT;
	if (g_fb_layer[3].format == RGB565)
		config_l |= LAYER_D_FORMAT_IS_16BIT;
	if (g_fb_layer[4].format == RGB565)
		config_u |= LAYER_E_FORMAT_IS_16BIT;
	if (priv.is_rgba == false) {
		/* ARGB8888*/
		_DBG_LOG("format is ARGB8888\n");
		config_u |= (BIT_FORMAT_IS_32);
	}

	lcdc_write(&priv, LCDC_GDCDCR_L_OFFS, config_l);
	lcdc_write(&priv, LCDC_GDCDCR_U_OFFS, config_u);

	_FNC_END("\n");
}

void applitefb_lcdc_enable(struct fb_var_screeninfo *var)
{
	_FNC_START("\n");

	/* setting of LayerA */
	plane_a_set();

#if (CONFIG_APPLITEFB_ENABLE_LAYER > 1)
	/* setting of LayerB */
	plane_b_set();

#if (CONFIG_APPLITEFB_ENABLE_LAYER > 2)
	/* setting of LayerC */
	plane_c_set();

#if (CONFIG_APPLITEFB_ENABLE_LAYER > 3)
	/* setting of LayerD */
	plane_d_set();

#if (CONFIG_APPLITEFB_ENABLE_LAYER > 4)
	/* setting of LayerE */
	plane_e_set();
#endif	/* > 4 */
#endif	/* > 3 */
#endif	/* > 2 */
#endif	/* > 1 */

	lcdc_control_restart();

	/* setting of interruption status */
	lcdc_write(&priv, LCDC_GDCINTR_L_OFFS,
			INPUT_FIFO_IRQ_MASK | GAPIF_IRQ_MASK);
	lcdc_write(&priv, LCDC_GDCINTR_U_OFFS,
		(PIXELCHECK_ERR_IRQ_FLAG | PIXELCHECK_EVENT_IRQ_FLAG));

	_FNC_END("\n");
}

void applitefb_lcdc_disable(void)
{
	u32 config_u;

	_FNC_START("\n");

	/* setting of interruption status */
	lcdc_write(&priv, LCDC_GDCINTR_L_OFFS, IRQ_FLAG);
	lcdc_write(&priv, LCDC_GDCINTR_U_OFFS,
		(PIXELCHECK_ERR_IRQ_FLAG | PIXELCHECK_EVENT_IRQ_FLAG));

	/* setting of GDC OFF */
	config_u = lcdc_read(&priv, LCDC_GDCDCR_U_OFFS);
	config_u &= ~GDC_ON;
	lcdc_write(&priv, LCDC_GDCDCR_U_OFFS, config_u);

	_FNC_END("\n");
}

/* Interrupt handler */
irqreturn_t handle_irq(int irq, void *data)
{
	unsigned long flag;
	u32 gdcintr_l, gdcintr_u;
	u32 config_u;

	/* read interruption status */
	gdcintr_l = lcdc_read(&priv, LCDC_GDCINTR_L_OFFS);
	gdcintr_u = lcdc_read(&priv, LCDC_GDCINTR_U_OFFS);

	spin_lock_irqsave(&priv.lcdc_slock, flag);

	lcdc_write(&priv, LCDC_GDCINTR_L_OFFS, gdcintr_l);
	lcdc_write(&priv, LCDC_GDCINTR_U_OFFS, gdcintr_u);

	if (gdcintr_l & VSYNC_IRQ_FLAG) {
		dprint("lcdc: wake up\n");

		gdcintr_l &= ~(VSYNC_IRQ_MASK); /* mask VSYNCMSK */
		lcdc_write(&priv, LCDC_GDCINTR_L_OFFS, gdcintr_l);

		/* setting of GDC OFF */
		config_u = lcdc_read(&priv, LCDC_GDCDCR_U_OFFS);
		config_u &= ~GDC_ON;
		lcdc_write(&priv, LCDC_GDCDCR_U_OFFS, config_u);

		/* setting of start address */
		plane_a_pan();
#if (CONFIG_APPLITEFB_ENABLE_LAYER > 1)
		plane_b_pan();
#if (CONFIG_APPLITEFB_ENABLE_LAYER > 2)
		plane_c_pan();
#if (CONFIG_APPLITEFB_ENABLE_LAYER > 3)
		plane_d_pan();
#if (CONFIG_APPLITEFB_ENABLE_LAYER > 4)
		plane_e_pan();
#endif	/* > 4 */
#endif	/* > 3 */
#endif	/* > 2 */
#endif	/* > 1 */

		/* setting of GDC ON */
		config_u = lcdc_read(&priv, LCDC_GDCDCR_U_OFFS);
		config_u |= GDC_ON;
		lcdc_write(&priv, LCDC_GDCDCR_U_OFFS, config_u);

		complete(&priv.vsync_completion); /* wake up */
	}

	if (gdcintr_l) {
		if (gdcintr_l & GAPIF_IRQ_FLAG)
			_ERR_LOG("lcdc: GAPINT\n");
		if (gdcintr_l & GBUS_ERR_IRQ_FLAG)
			_ERR_LOG("lcdc: GBERINT\n");
		if (gdcintr_l & INPUT_FIFO_IRQ_FLAG)
			_ERR_LOG("lcdc: IFURINT\n");
		if (gdcintr_l & OUTPUT_FIFO_IRQ_FLAG)
			_ERR_LOG("lcdc: OFURINT\n");
		if (gdcintr_l & VSYNCROCK_IRQ_FLAG)
			_ERR_LOG("lcdc: VSLINT\n");
		if (gdcintr_l & GDC_ERR_IRQ_FLAG)
			_ERR_LOG("lcdc: GPEINT\n");
		if (gdcintr_u & PIXELCHECK_EVENT_IRQ_FLAG)
			_ERR_LOG("lcdc: APEINT\n");
		if (gdcintr_u & PIXELCHECK_ERR_IRQ_FLAG)
			_ERR_LOG("lcdc: APCINT\n");
	}

	spin_unlock_irqrestore(&priv.lcdc_slock, flag);
	return IRQ_HANDLED;
}

int applitefb_wait_for_vsync(struct fb_info *info)
{
	int ret;
	u32 gdcintr_l;

	_FNC_START("\n");

	mutex_lock(&applitefb_lock);

	gdcintr_l = lcdc_read(&priv, LCDC_GDCINTR_L_OFFS);

	/* Enable vsync end interrupt and be careful not to acknowledge any
	 * pending interrupt.
	 */
	gdcintr_l |= (HSYNC_IRQ_IS_256 | VSYNC_IRQ_MASK); /* unmask VSYNCMSK */
	lcdc_write(&priv, LCDC_GDCINTR_L_OFFS, gdcintr_l);

	ret = wait_for_completion_interruptible_timeout(
		&priv.vsync_completion, msecs_to_jiffies(100));

	mutex_unlock(&applitefb_lock);
	if (!ret) {
		dprint("%s : wait for vsync timeout\n", FB_DEVICE_NAME);
		return -ETIMEDOUT;
	}
	_FNC_END("\n");
	return 0;
}

int applitefb_local_ioctl(struct fb_info *info, unsigned int cmd,
			  unsigned long arg)
{
	_FNC_START("cmd(%08x)\n", cmd);
	return tz2000gfx_ioctl(info, cmd, arg);
}

int applitefb_hw_start(void)
{
	__u32 val;

	_FNC_START("\n");
	/* start clock */
	clk_prepare_enable(priv.clk_dispif);

	/* VDD33_TOP */
	val = pmu_read(&priv, PMU_POREN_OFS);
	val &= ~PMU_POREN_POREN_TOP_MASK;

	pmu_write(&priv, PMU_POREN_OFS, (val | PMU_POREN_POREN_TOP_MASK));
	/* 100ns wait */
	ndelay(100);

	/* gfx resume */
	tz2000gfx_resume();

	_FNC_END("\n");
	return 0;
}

int applitefb_hw_stop(void)
{
	__u32 val;

	_FNC_START("\n");
	/* check status */
	val = lcdc_read(&priv, LCDC_GDCDCR_U_OFS);
	if (val & LCDC_GDCDCR_U_DISPIFON_MASK) {
		_ERR_LOG("GDCDCR_U(%08x) display interface enabled\n", val);
		/*return -EBUSY;*/
	}

	/* stop clock */
	clk_disable_unprepare(priv.clk_dispif);

	/* gfx suspend */
	val = tz2000gfx_suspend();

	_FNC_END("\n");
	return val;
}

int applitefb_runtime_suspend(struct device *dev)
{
	__u32 val;

	_FNC_START("\n");
	val = lcdc_read(&priv, LCDC_GDCDCR_U_OFS);
	lcdc_write(&priv, LCDC_GDCDCR_U_OFS, (val & 0x7FFFFFFF));
	mdelay(100);
	/* check status */
	val = lcdc_read(&priv, LCDC_GDCDCR_U_OFS);
	if (val & LCDC_GDCDCR_U_DISPIFON_MASK) {
		_ERR_LOG("GDCDCR_U(%08x) display interface enabled\n", val);
		/*return -EBUSY;*/
	}

	/* stop clock */
	clk_disable_unprepare(priv.clk_dispif);

	/* gfx suspend */
	val = tz2000gfx_suspend();

	_FNC_END("(%d)\n", val);
	return val;
}

int applitefb_runtime_resume(struct device *dev)
{
	_FNC_START("\n");
	/* start clock */
	clk_prepare_enable(priv.clk_dispif);

	/* gfx resume */
	tz2000gfx_resume();

	_FNC_END("\n");
	return 0;
}


#if IS_ENABLED(CONFIG_FB_APPLITE_PANEL_F07A_0102)
#elif IS_ENABLED(CONFIG_FB_APPLITE_PANEL_NHD4_3)
#elif IS_ENABLED(CONFIG_FB_APPLITE_PANEL_NHD4_3_59)
#elif IS_ENABLED(CONFIG_FB_APPLITE_PANEL_NHD4_3_29)
#elif IS_ENABLED(CONFIG_FB_APPLITE_PANEL_ILI6480G2_59)
#elif IS_ENABLED(CONFIG_FB_APPLITE_PANEL_ILI6480G2_29)
#endif	/* CONFIG_FB_APPLITE_PANEL_xxx */
