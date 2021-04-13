/*
 * linux/drivers/video/applite/applitefb.h
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
#if !defined(__FRAMEBUFFER_MODULE_H__)
#define __FRAMEBUFFER_MODULE_H__

#include <linux/types.h>
#include "applitefb_tz2000.h"
#include "applitefb_tz3000.h"


/* for debug */
#undef APPLITE_DEBUG
#undef APPLITE_D2DP_DEBUG

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

#ifdef APPLITE_D2DP_DEBUG
	#define _D2DP_FNC_START(fmt, ...)	pr_info("+%s: "fmt, __func__, ##__VA_ARGS__)
	#define _D2DP_FNC_END(fmt, ...)		pr_info("-%s: "fmt, __func__, ##__VA_ARGS__)
	#define _D2DP_DBG_LOG(fmt, ...)		pr_info(" %s: "fmt, __func__, ##__VA_ARGS__)
	#define _D2DP_DEV_LOG(fmt, ...)		pr_info(" %s[fb%d]: "fmt, __func__, ##__VA_ARGS__)
#else
	#define _D2DP_FNC_START(fmt, ...)
	#define _D2DP_FNC_END(fmt, ...)
	#define _D2DP_DBG_LOG(fmt, ...)
	#define _D2DP_DEV_LOG(fmt, ...)
#endif

#define _WAR_LOG(fmt, ...)		pr_warning(" %s:"fmt, __func__, ##__VA_ARGS__)
#define _ERR_LOG(fmt, ...)		pr_err(" %s: --ERROR-- :"fmt, __func__, ##__VA_ARGS__)


#define DISPLAY_DRIVER_VERSION		"1.0"

#define MAX_PLANE			3

#define MAX_BPP				32
#define DEFAULT_BPP			32
#define FB_DEVICE_NAME			"fb"

#define DISPLAY_MODE_720_480_60P	1
#define DISPLAY_MODE_1280_720_60P	2
#define DISPLAY_MODE_1920_1080_30P	3

#define _1280x720_60HZ_			1

#define REGISTER_SIZE			20
#define BUFFER_SIZE			20

#define FB_SIZE_TWICE			2
#define FB_SIZE_THREE_TIMES		3

/* SIZE ALIGN MASK */
#define HSIZE_ALIGN_MASK		0x000007f0
#define VSIZE_ALIGN_MASK		0x000003f8


/* format of lcdc Structure */
struct applitefb_lcdc_format_info {
	u32 fourcc;
	unsigned int bpp;
	bool yuv;
};


/* FrameBuffer device Structure */
struct applitefb_layer {
	__u32	format;			/* input format */
	__u32	addr[MAX_PLANE];	/* input buffer phys address */
	__u32	line_length[MAX_PLANE];	/* buffer pitch */
	__u32	layer;			/* layer */
	void	*vram;			/* input buffer virtual address */
	int	xoffset;		/* pan x-offset */
	int	yoffset;		/* pan y-offset */
	__u16	xpos;			/* display left position */
	__u16	ypos;			/* display top position */
	__u16	xpos_old;		/* previous value of display left position */
	__u16	ypos_old;		/* previous value of display top position */
	u32	dxres;			/* display top position to HW */
	u32	dyres;			/* display top position to HW */
	__u32	addr_old[MAX_PLANE];	/* previous value of buffer address */
};

/* Register Management Structure */
struct reg_param {
	u32 reg_flag;		/* 0:LCDC 1:NONE */
	u16 reg_offset;
	u32 val;
};


/* Register Management Structure */
struct debug_reg_param {
	char regist_name[30];
	u32 reg_offset;
};


/* FrameBuffer common Structure */
struct applitefb_dev {
	void __iomem *pmu_regs;
	void __iomem *lcdc_regs;
	void __iomem *gfx_regs;
	struct completion vsync_completion;
	struct completion fconva_frame_end_completion;
	struct completion fconvb_frame_end_completion;
	struct device *dev;
	struct platform_device *pdev;
	struct clk *clk_dispif;
	struct clk *clk_gfx;
	struct fb_info *info[CONFIG_APPLITEFB_ENABLE_LAYER];
	spinlock_t lcdc_slock;
	u32 xres;
	u32 yres;
	unsigned int fail;
#if IS_ENABLED(CONFIG_FB_TZ2000)
	bool is_rgba;
#endif
};

/*===================================
Exported Functions prototypes
===================================*/
u32 get_display_mode(struct fb_var_screeninfo *);
u_long get_display_pixelformat(struct fb_var_screeninfo *var, __u32 *fmt);

void plane_pan(int node);
int pan_display(struct fb_var_screeninfo *, struct fb_info *);
void regist_irq(struct platform_device *pdev);
void _free_irq(struct platform_device *pdev);
void format_adjustment(void);
void applitefb_lcdc_initialize(struct fb_var_screeninfo *var);
void applitefb_lcdc_finalize(void);
void applitefb_lcdc_enable(struct fb_var_screeninfo *var);
void applitefb_lcdc_disable(void);
void plane_set(int node);
int applitefb_wait_for_vsync(struct fb_info *);
int applitefb_local_ioctl(struct fb_info *info, unsigned int cmd,
			  unsigned long arg);
int applitefb_runtime_suspend(struct device *dev);
int applitefb_runtime_resume(struct device *dev);
int applitefb_hw_start(void);
int applitefb_hw_stop(void);
int applitefb_wait_for_frame_end(unsigned int fconv);

void plane_output(int output);

void reg_dump(void);

irqreturn_t handle_irq(int , void *);
irqreturn_t handle_irq2(int , void *);


/* write to register */
static inline void lcdc_write(struct applitefb_dev *dev,
					const volatile u32 reg, u32 val)
{
	__raw_writel(val, dev->lcdc_regs + reg);
}

/* read from register */
static inline u32 lcdc_read(struct applitefb_dev *dev,
					const volatile u32 reg)
{
	return __raw_readl(dev->lcdc_regs + reg);
}

/* write to register */
static inline void pmu_write(struct applitefb_dev *dev,
					const volatile u32 reg, u32 val)
{
	__raw_writel(val, dev->pmu_regs + reg);
}

/* read from register */
static inline u32 pmu_read(struct applitefb_dev *dev,
					const volatile u32 reg)
{
	return __raw_readl(dev->pmu_regs + reg);
}

/* Function for get line_length */
static inline u32 get_line_length(int xres_virtual, int bpp)
{
	u32 length;
	_FNC_START("\n");

	length = ((xres_virtual * bpp) + 31) & ~31;
	length >>= 3;

	_FNC_END("xres_virtual[%d],bpp[%d],length[%u]\n",
		xres_virtual, bpp, length);

	return length;
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

/*===================================
Exported Variable prototypes
===================================*/
extern struct mutex applitefb_lock;
extern u_long magnification;
extern u_long xres;
extern u_long yres;
extern u_long gfx_size;
extern u_long a_alpha;
extern u_long b_alpha;
extern u_long c_alpha;
extern u_long d_alpha;
extern u_long e_alpha;
extern u_long sel_alpha;
extern u_long merge;
extern u_long is_colorbar;
extern u_long g_display_mode;
extern int probe_flag;
extern int plane_a_layer;
extern int plane_b_layer;

extern struct applitefb_dev priv;
extern struct applitefb_layer g_fb_layer[DEVICE_MAX];

extern u32 g_out_baseaddr;	/* output baseaddress */
extern u32 g_disp_xres;
extern u32 g_disp_yres;
extern u32 g_out_baseaddr_offset[DEVICE_MAX];

extern struct debug_reg_param debug_regist[];
#endif	/*__FRAMEBUFFER_MODULE_H__*/

