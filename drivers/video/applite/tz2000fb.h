/*
 * linux/drivers/video/applite/tz2000fb.h
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
#if !defined(__TZ2000FB_H__)
#define __TZ2000FB_H__

#include <linux/types.h>


/* for debug */
#undef APPLITE_DEBUG

#ifdef APPLITE_DEBUG
	#define dprint			pr_info
	#define _FNC_START(fmt, ...)	pr_info("+%s: "fmt, __func__, ##__VA_ARGS__)
	#define _FNC_END(fmt, ...)	pr_info("-%s: "fmt, __func__, ##__VA_ARGS__)
	#define _DBG_LOG(fmt, ...)	pr_info(" %s: "fmt, __func__, ##__VA_ARGS__)
	#define _DEV_LOG(fmt, ...)	pr_info(" %s[fb%d]: "fmt, __func__, ##__VA_ARGS__)
#else
	#define dprint(x, ...) { \
	}
	#define _FNC_START(fmt, ...)
	#define _FNC_END(fmt, ...)
	#define _DBG_LOG(fmt, ...)
	#define _DEV_LOG(fmt, ...)
#endif

#define _ERR_LOG(fmt, ...)		pr_err(" %s: --ERROR-- :"fmt, __func__, ##__VA_ARGS__)


#define DISPLAY_DRIVER_VERSION		"1.0"

#define TZ2000_MAX_LAYER 5


enum tz2000_lcdc_format {
	RGB16_RGB565    = 0, /* 16 bpp */
	ARGB32_RGBA8888 = 1, /* 32 bpp */
	ARGB32_ARGB8888 = 2, /* 32 bpp */
};


struct tz2000fb_layer {
	int layer;
	unsigned long pixelformat;
	void *memory;
	u32 size;
	u32 addr;
	u32 xres;
	u32 yres;
	u32 vxres;
	u32 vyres;
	u32 xlstart;
	u32 ylstart;
	u32 dxres;
	u32 dyres;
	u32 gdclsra_l_bak;
};

struct tz2000fb_dev {
	struct device *dev;
	void __iomem *pmu_regs;
	void __iomem *lcdc_regs;
	void __iomem *gfx_regs;
	spinlock_t lock;		/* Protects video buffer lists */
	struct completion vsync_completion;
	struct clk *clk_lcdc;
	struct clk *clk_gfx;
	struct fb_info *info[TZ2000_MAX_LAYER];
	struct tz2000fb_layer layer[TZ2000_MAX_LAYER];
	int flip;
	bool is_argb;
	ulong use_pwm0;
	spinlock_t lcdc_slock;
};
extern struct tz2000fb_dev priv;

#if IS_ENABLED(CONFIG_APPLITE_PWM)
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

#endif /* IS_ENABLED(CONFIG_APPLITE_PWM) */
#endif	/*__TZ2000FB_H__*/
