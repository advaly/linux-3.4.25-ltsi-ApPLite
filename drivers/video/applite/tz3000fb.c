/*
 * linux/drivers/video/applite/tz3000fb.c
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

#include <linux/videodev2.h>
#include <linux/fb.h>
#include <linux/init.h>
#include <asm/cacheflush.h>

#ifndef V4L2_PIX_FMT_YUV444P
#define V4L2_PIX_FMT_YUV444P v4l2_fourcc('4', '4', '4', 'P') /* 24  YVU444 planar */
#endif

#include <mach/regs/cpu_memmap_def.h>
#include <mach/regs/pmu_offs_def.h>
#include <mach/regs/dispif_offs_def.h>

#define DISPLAY_DRIVER_VERSION		"1.0"

#define TZ3000_IRQ_DISPIF_HBLANKININT		(176)
#define TZ3000_IRQ_DISPIF_VBLANKININT		(177)
#define TZ3000_IRQ_DISPIF_VBLANKOUTINT		(178)
#define TZ3000_IRQ_DISPIF_HBLANKININT2		(179)
#define TZ3000_IRQ_DISPIF_HBLANKININT3		(180)
#define TZ3000_IRQ_DISPIF_DSIINT		(181)
#define TZ3000_IRQ_DISPIF_INTFRAME		(182)
#define TZ3000_IRQ_DISPIF_INTERR		(183)
#define TZ3000_IRQRE_DISPIF_VBLANKINEDGEINT	(248)
#define TZ3000_IRQRE_DISPIF_VSYNC		(249)


enum tz3000_dispif_fconv {
	fconva = 0,
	fconvb = 1,
	fconvc = 2,
};

enum tz3000_dispif_irq_control {
	irq_disable_all    = 0,
	irq_enable_all     = 1,
	irq_stat_clear_all = 2,
};

enum tz3000_dispif_dtg_control {
	dtg_start      = 0,
	dtg_stop       = 1,
	dtg_force_stop = 2,
};

enum tz3000_dispif_dsi_control {
	dsi_reset     = 0,
	dsi_continue  = 1,
	dsi_pause     = 2,
	dsi_start     = 3,
	dsi_int_clear = 4,
};

enum tz3000_dispif_cgate_control {
	cgate_off = 0,
	cgate_on  = 1,
};

enum tz3000_dispif_sel_alpha {
	grobal_alpha = 0,
	pixel_alpha  = 1,
};

enum tz3000_dispif_colorformat {
	rgb       = 0,
	ycbcr444  = 1,
	ycbcr422  = 2,
	ycbcr420  = 3,
};

enum tz3000_dispif_plane {
	use_noplane = 0,
	use_1plane  = 1,
	use_2plane  = 2,
	use_3plane  = 3,
};

enum tz3000_dispif_format {
	RGB16_BGR565          = 0x00000010, /* 16 bpp */
	RGB16_RGB565          = 0x00010010, /* 16 bpp */
	ARGB16_ABGR1555       = 0x00020010, /* 16 bpp */
	ARGB16_ARGB1555       = 0x00030010, /* 16 bpp */
	ARGB32_ABGR8888       = 0x00040010, /* 32 bpp */
	ARGB32_ARGB8888       = 0x00050010, /* 32 bpp */
	RGB24_R8_G8_B8        = 0x00000030,
	YCbCr444_AYCbCr8888   = 0x00000011,
	YCbCr444_ACbCrY8888   = 0x00010011,
	YCbCr444_Y8_Cb8_Cr8   = 0x00000031,
	YCbCr422_Y8_Cb8_Cr8   = 0x00000032,
	YCbCr420_Y8_Cb8Cr8    = 0x00000023, /* GPU raster */
	YCbCr420_Y8_Cb8_Cr8   = 0x00000033, /* Venezia raster */
#if 0 /* All tile format is not supported. */
	RGB16_BGR565_T        = 0x00000110, /* 16 bpp tile */
	RGB16_RGB565_T        = 0x00010110, /* 16 bpp tile */
	ARGB16_ABGR1555_T     = 0x00020110, /* 16 bpp tile */
	ARGB16_ARGB1555_T     = 0x00030110, /* 16 bpp tile */
	ARGB32_ABGR8888_T     = 0x00040110, /* 32 bpp tile */
	ARGB32_ARGB8888_T     = 0x00050110, /* 32 bpp tile */
	RGB24_R8_G8_B8_T      = 0x00000130,
	YCbCr444_AYCbCr8888_T = 0x00000111,
	YCbCr444_ACbCrY8888_T = 0x00010111,
	YCbCr444_Y8_Cb8_Cr8_T = 0x00000131,
	YCbCr420_vdu_i_T      = 0x00000113, /* vdu interlace (input only) */
	YCbCr420_vdu_p_T      = 0x00010113, /* vdu progressive (input only) */
	YCbCr420_Y8_Cb8Cr8_T  = 0x00000123, /* GPU tile */
	YCbCr420_venezia_T    = 0x00010123, /* Venezia tile */
	YCbCr420_veu_T        = 0x00020123, /* veu tile (output only) */
#endif
};

#define DEFAULT_FORMAT_IS_RGB16_RGB565
#undef DEFAULT_FORMAT_IS_ARGB32_ARGB8888
#undef DEFAULT_FORMAT_IS_ARGB32_ABGR8888

#undef STRICT_COLOR_CHECK
#undef DISABLE_32BIT_COLOR

static inline void dispif_write_reg(const volatile void __iomem *base, const volatile u32 reg, u32 val)
{
	__raw_writel(val, base + reg);
}

static inline u32 dispif_read_reg(const volatile void __iomem *base, u32 reg)
{
	return __raw_readl(base + reg);
}

static inline void set_rgba(struct fb_var_screeninfo *var,
			    __u32 r_off, __u32 r_len,
			    __u32 g_off, __u32 g_len,
			    __u32 b_off, __u32 b_len,
			    __u32 a_off, __u32 a_len)
{
	var->nonstd           = 0;
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

/* #define DISPIF_800X600_60HZ_A */
/* #define DISPIF_800X600_60HZ_B */
#define DISPIF_800X600_60HZ_C

/* #define DISPIF_1280X720_50HZ */
#define DISPIF_1280X720_60HZ

#define CONFIG_FB_TZ3000_USE_D2DP
/* #define CONFIG_FB_TZ3000_USE_D2DPI */

/* #define D2DP_I2C_ADDR (0x68) */
#define D2DP_I2C_ADDR (0x0f)
#define D2DP_I2C_BUS (2)	/* /dev/i2c-2 */
#define D2DP_RESET_GPIO (3)

#define D2DPI_I2C_ADDR 0x0f
#define D2DPI_I2C_BUS (2)	/* /dev/i2c-2 */
#define D2DPI_RESET_GPIO (3)

    /*
     *  RAM we reserve for the frame buffer. This defines the maximum screen
     *  size
     *
     *  The default can be overridden if the driver is compiled as a module
     */

#define MAX_FB_MAGNIFICATION	3
#define MAX_XRES		1920
#define MAX_YRES		1080
#define MAX_BPP			32
#define MAX_FRAME_SIZE		(MAX_XRES * MAX_YRES * MAX_BPP / 8)
#define MAX_FB_SIZE		(MAX_FRAME_SIZE * MAX_FB_MAGNIFICATION)
#define DEFAULT_FB_MAGNIFICATION	3
#define DEFAULT_XRES			1280
#define DEFAULT_YRES			720
#if defined(DEFAULT_FORMAT_IS_RGB16_RGB565)
  #define DEFAULT_FORMAT	RGB16_RGB565
  #define DEFAULT_PIXELFORMAT	1
  #define DEFAULT_BPP		16
  #define DEFAULT_COLOR_R	{ 11, 5, 0 }
  #define DEFAULT_COLOR_G	{  5, 6, 0 }
  #define DEFAULT_COLOR_B	{  0, 5, 0 }
  #define DEFAULT_COLOR_A	{  0, 0, 0 }
#elif defined(DEFAULT_FORMAT_IS_ARGB32_ARGB8888) && !defined(DISABLE_32BIT_COLOR)
  #define DEFAULT_FORMAT	ARGB32_ARGB8888
  #define DEFAULT_PIXELFORMAT	0
  #define DEFAULT_BPP		32
  #define DEFAULT_COLOR_R	{ 16, 8, 0 }
  #define DEFAULT_COLOR_G	{  8, 8, 0 }
  #define DEFAULT_COLOR_B	{  0, 8, 0 }
  #define DEFAULT_COLOR_A	{ 24, 8, 0 }
#elif defined(DEFAULT_FORMAT_IS_ARGB32_ABGR8888) && !defined(DISABLE_32BIT_COLOR)
  #define DEFAULT_FORMAT	ARGB32_ABGR8888
  #define DEFAULT_PIXELFORMAT	9
  #define DEFAULT_BPP		32
  #define DEFAULT_COLOR_R	{  0, 8, 0 }
  #define DEFAULT_COLOR_G	{  8, 8, 0 }
  #define DEFAULT_COLOR_B	{ 16, 8, 0 }
  #define DEFAULT_COLOR_A	{ 24, 8, 0 }
#else /* defined(DEFAULT_FORMAT_IS_RGB16_RGB565) */
  #define DEFAULT_FORMAT	RGB16_RGB565
  #define DEFAULT_PIXELFORMAT	1
  #define DEFAULT_BPP		16
  #define DEFAULT_COLOR_R	{ 11, 5, 0 }
  #define DEFAULT_COLOR_G	{  5, 6, 0 }
  #define DEFAULT_COLOR_B	{  0, 5, 0 }
  #define DEFAULT_COLOR_A	{  0, 0, 0 }
#endif
#define DEFAULT_FRAME_SIZE	(DEFAULT_XRES * DEFAULT_YRES * DEFAULT_BPP / 8)
#define DEFAULT_FB_MODE		3

static u_long magnification = DEFAULT_FB_MAGNIFICATION;
module_param(magnification, ulong, 0644);
MODULE_PARM_DESC(magnification, "Num of Framebuffer");

static u_long is_colorbar;
module_param(is_colorbar, ulong, 0444);

static u_long fb_mode = DEFAULT_FB_MODE;
module_param(fb_mode, ulong, 0444);

static u_long xres = DEFAULT_XRES;
module_param(xres, ulong, 0444);

static u_long yres = DEFAULT_YRES;
module_param(yres, ulong, 0444);

static u_long pixelformat = DEFAULT_PIXELFORMAT;
module_param(pixelformat, ulong, 0444);

struct tz3000fb_dev {
	struct device *dev;
	void __iomem *pmu_regs;
	void __iomem *dispif_regs;
	spinlock_t lock;		/* Protects video buffer lists */
	void *fconva_memory;
	void *fconvb_memory;
	void *fconva_out_memory;
	void *fconvb_out_memory;
	unsigned long fconva_in_base;
	unsigned long fconvb_in_base;
	unsigned long fconva_out_base;
	unsigned long fconvb_out_base;
	unsigned long fconva_in_size;
	unsigned long fconvb_in_size;
	unsigned long fconva_out_size;
	unsigned long fconvb_out_size;
	unsigned long fconva_in_xres;
	unsigned long fconvb_in_xres;
	unsigned long fconva_out_xres;
	unsigned long fconvb_out_xres;
	unsigned long fconva_in_yres;
	unsigned long fconvb_in_yres;
	unsigned long fconva_out_yres;
	unsigned long fconvb_out_yres;
	unsigned long fconva_format;
	unsigned long fconvb_format;
	unsigned long fconva_bpp;
	unsigned long fconvb_bpp;
	u32 fconva_baseaddr[3];
	u32 fconvb_baseaddr[3];
	u32 fconva_line_length[3];
	u32 fconvb_line_length[3];
	u32 fconva_size[3];
	u32 fconvb_size[3];
	u32 fconva_size_virtual[3];
	u32 fconvb_size_virtual[3];
	u32 fconva_pan_offset[3];
	u32 fconvb_pan_offset[3];
	u32 fconva_channel;
	u32 fconvb_channel;
	int fconva_flip;
	int fconvb_flip;
	struct completion vsync_completion;
	struct completion fconva_frame_end_completion;
	struct completion fconvb_frame_end_completion;
	struct clk *clk_dispif;
	spinlock_t dispif_slock;
};
static struct tz3000fb_dev priv;

static const char tz3000fb_devname[] = "tz3000fb";

#ifdef CONFIG_FB_TZ3000_USE_D2DP
static DEFINE_MUTEX(d2dp_lock);

static inline int d2dp_i2c_read(struct i2c_adapter *adapter,
			 u16 addr, u16 count, u8 *buf)
{
	int ret, retries;
	u8 msg_buf[2];
	struct i2c_msg msgs[] = {
		{
			.addr   = D2DP_I2C_ADDR,
			.flags  = 0,
			.len    = 2,
			.buf    = (u8 *)&msg_buf[0],
		}, {
			.addr   = D2DP_I2C_ADDR,
			.flags  = I2C_M_RD,
			.len    = count,
			.buf    = (u8 *)buf,
		}
	};

	u8 *paddr = (u8 *)&addr;

	msg_buf[0] = paddr[1];
	msg_buf[1] = paddr[0];

	for (retries = 3; retries > 0; retries--) {
		ret = i2c_transfer(adapter, msgs, 2);
		if (ret == 2)
			return 0;

		if (ret != -EAGAIN)
			break;
	}
	if (ret != 2)
		pr_err("i2c_transfer addr=0x%04x read error %d\n", addr, ret);

	return ret < 0 ? ret : -EIO;
}

static inline int d2dp_i2c_write32(struct i2c_adapter *adapter,
			    u16 addr, u32 val)
{
	int ret, retries;
	unsigned int ii;
	u8 msg_buf[2 + sizeof(u32)];
	struct i2c_msg msgs[] = {
		{
			.addr   = D2DP_I2C_ADDR,
			.flags  = 0,
			.len    = 2 + sizeof(u32),
			.buf    = (u8 *)&msg_buf[0],
		}
	};

	u8 *paddr = (u8 *)&addr;
	u8 *pbuf = (u8 *)&val;

	msg_buf[0] = paddr[1];
	msg_buf[1] = paddr[0];
	for (ii = 0; ii < sizeof(u32); ii++)
		msg_buf[2 + ii] = pbuf[ii];

	for (retries = 3; retries > 0; retries--) {
		ret = i2c_transfer(adapter, msgs, 1);
		if (ret == 1)
			return 0;

		if (ret != -EAGAIN)
			break;
	}
	if (ret != 1)
		pr_err("i2c_transfer addr=0x%04x write error %d\n", addr, ret);

	return ret < 0 ? ret : -EIO;
}

static void d2dp_reset(void)
{
	int val;

	mutex_lock(&d2dp_lock);

	val = gpio_get_value(D2DP_RESET_GPIO);
	if (val == 0)
		pr_debug("gpio%d=low : D2DP reset\n", D2DP_RESET_GPIO);
	else
		pr_debug("gpio%d=High: D2DP unreset\n", D2DP_RESET_GPIO);
	if (val > 0) {
		gpio_set_value(D2DP_RESET_GPIO, 0);
		mdelay(10);
		val = gpio_get_value(D2DP_RESET_GPIO);
		if (val == 0)
			pr_debug("gpio%d=low : D2DP reset\n", D2DP_RESET_GPIO);
		else
			pr_debug("gpio%d=High: D2DP unreset\n", D2DP_RESET_GPIO);
	}
	gpio_set_value(D2DP_RESET_GPIO, 1);
	mdelay(10);
	val = gpio_get_value(D2DP_RESET_GPIO);
	if (val == 0)
		pr_debug("gpio%d=low : D2DP reset\n", D2DP_RESET_GPIO);
	else
		pr_debug("gpio%d=High: D2DP unreset\n", D2DP_RESET_GPIO);

	mdelay(10);

	mutex_unlock(&d2dp_lock);
}

static int d2dp_init(u32 mode)
{
	int ret;
	struct i2c_adapter *adapter;
	u32 val;
	u32 count;
	u32 dp_lane = 0;

	switch (mode) {
	case 1:		/*  720x 480@59.94P */
	case 2:		/*  800x 600@60P */
		dp_lane = 1;
		break;
	case 3:		/* 1280x 720@50/60P */
	case 4:		/* 1920x1080@30P */
	case 5:		/* 1920x1080@60P */
		dp_lane = 2;
		break;
	}

	mutex_lock(&d2dp_lock);

	adapter = i2c_get_adapter(D2DP_I2C_BUS);
	if (!adapter) {
		pr_err("Failed to get I2C adapter, bus %d\n", 2);
		goto err;
	}

	ret = d2dp_i2c_read(adapter, 0x0500, sizeof(u32), (u8 *)&val);
	pr_debug("d2dp addr=0x%04x 0x%08x\n", 0x0500, val);
	mdelay(10);
	if (mode == 1) {
		ret  = d2dp_i2c_write32(adapter, 0x06a0, 0x00003082);
		ret |= d2dp_i2c_write32(adapter, 0x07a0, 0x00000002);
	} else if (mode == 2) {
		ret  = d2dp_i2c_write32(adapter, 0x06a0, 0x00003080);
		ret |= d2dp_i2c_write32(adapter, 0x07a0, 0x00000000);
	} else if (mode == 3 || mode == 4 || mode == 5) {
		ret  = d2dp_i2c_write32(adapter, 0x06a0, 0x00003086);
		ret |= d2dp_i2c_write32(adapter, 0x07a0, 0x00000002);
	}
	ret |= d2dp_i2c_write32(adapter, 0x0918, 0x00000101);
	mdelay(10);
	if (dp_lane == 1)
		ret |= d2dp_i2c_write32(adapter, 0x0800, 0x03000003);
	else if (dp_lane == 2)
		ret |= d2dp_i2c_write32(adapter, 0x0800, 0x03000007);
	ret |= d2dp_i2c_write32(adapter, 0x0900, 0x00000005);
	mdelay(10);
	ret |= d2dp_i2c_write32(adapter, 0x0904, 0x00000005);
	if (mode == 1)
		ret |= d2dp_i2c_write32(adapter, 0x0914, 0x0022051c);
	else if (mode == 2)
		ret |= d2dp_i2c_write32(adapter, 0x0914, 0x00250115);
	else if (mode == 3)
		ret |= d2dp_i2c_write32(adapter, 0x0914, 0x00320346);
	else if (mode == 4)
		ret |= d2dp_i2c_write32(adapter, 0x0914, 0x0032045d);
	else if (mode == 5)
		ret |= d2dp_i2c_write32(adapter, 0x0914, 0x0032025d);
	ret |= d2dp_i2c_write32(adapter, 0x0908, 0x00000005);
	mdelay(10);
	if (dp_lane == 1) {
		ret |= d2dp_i2c_write32(adapter, 0x0800, 0x13001103);
		ret |= d2dp_i2c_write32(adapter, 0x0800, 0x03000003);
	} else if (dp_lane == 2) {
		ret |= d2dp_i2c_write32(adapter, 0x0800, 0x13001107);
		ret |= d2dp_i2c_write32(adapter, 0x0800, 0x03000007);
	}
	mdelay(10);
	if (dp_lane == 1) {
		count = 0;
		do {
			ret |= d2dp_i2c_read(adapter, 0x0800, sizeof(u32), (u8 *)&val);
			count++;
			mdelay(5);
		} while (val != 0x03010003 && count < 5);
		pr_debug("d2dp addr=0x%04x 0x%08x count=%d\n", 0x0800, val, count);
	} else if (dp_lane == 2) {
		count = 0;
		do {
			ret |= d2dp_i2c_read(adapter, 0x0800, sizeof(u32), (u8 *)&val);
			count++;
			mdelay(5);
		} while (val != 0x03010007 && count < 5);
		pr_debug("d2dp addr=0x%04x 0x%08x count=%d\n",
				0x0800, val, count);
	}
	ret |= d2dp_i2c_write32(adapter, 0x0664, 0x0001063f);
	ret |= d2dp_i2c_write32(adapter, 0x0668, 0x00000001);
	ret |= d2dp_i2c_write32(adapter, 0x0660, 0x00000009);
	mdelay(10);
	count = 0;
	do {
		ret |= d2dp_i2c_read(adapter, 0x068c, sizeof(u32), (u8 *)&val);
		count++;
		mdelay(5);
	} while ((val & 0x00000003) && count < 5);
	pr_debug("d2dp addr=0x%04x 0x%08x count=%d\n", 0x068c, val, count);
	ret |= d2dp_i2c_read(adapter, 0x067c, sizeof(u32), (u8 *)&val);
	pr_debug("d2dp addr=0x%04x 0x%08x\n", 0x067c, val);
	mdelay(10);
	ret |= d2dp_i2c_write32(adapter, 0x0668, 0x00000002);
	ret |= d2dp_i2c_write32(adapter, 0x0660, 0x00000009);
	mdelay(10);
	count = 0;
	do {
		ret |= d2dp_i2c_read(adapter, 0x068c, sizeof(u32), (u8 *)&val);
		count++;
		mdelay(5);
	} while ((val & 0x00000003) && count < 5);
	pr_debug("d2dp addr=0x%04x 0x%08x count=%d\n", 0x068c, val, count);
	mdelay(10);
	ret |= d2dp_i2c_read(adapter, 0x067c, sizeof(u32), (u8 *)&val);
	pr_debug("d2dp addr=0x%04x 0x%08x\n", 0x067c, val);
	mdelay(10);
	ret |= d2dp_i2c_write32(adapter, 0x0668, 0x00000100);
	if (mode == 1)
		ret |= d2dp_i2c_write32(adapter, 0x066c, 0x0000010a);
	else if (mode == 2)
		ret |= d2dp_i2c_write32(adapter, 0x066c, 0x00000106);
	else if (mode == 3 || mode == 4 || mode == 5)
		ret |= d2dp_i2c_write32(adapter, 0x066c, 0x0000020a);
	ret |= d2dp_i2c_write32(adapter, 0x0660, 0x00000108);
	ret |= d2dp_i2c_write32(adapter, 0x0668, 0x00000108);
	ret |= d2dp_i2c_write32(adapter, 0x066c, 0x00000001);
	ret |= d2dp_i2c_write32(adapter, 0x0660, 0x00000008);
	mdelay(10);
	ret |= d2dp_i2c_write32(adapter, 0x06e4, 0x00000021);
	ret |= d2dp_i2c_write32(adapter, 0x06d8, 0xf600000d);
	mdelay(10);
	if (mode == 1)
		ret |= d2dp_i2c_write32(adapter, 0x06a0, 0x00003183);
	else if (mode == 2)
		ret |= d2dp_i2c_write32(adapter, 0x06a0, 0x00003181);
	else if (mode == 3 || mode == 4 || mode == 5)
		ret |= d2dp_i2c_write32(adapter, 0x06a0, 0x00003187);
	mdelay(10);
	ret |= d2dp_i2c_write32(adapter, 0x0600, 0x00000001);
	mdelay(10);
	ret |= d2dp_i2c_read(adapter, 0x06d0, sizeof(u32), (u8 *)&val);
	pr_debug("d2dp addr=0x%04x 0x%08x\n", 0x06d0, val);
	mdelay(10);
	ret |= d2dp_i2c_write32(adapter, 0x06e4, 0x00000022);
	mdelay(10);
	if (mode == 1)
		ret |= d2dp_i2c_write32(adapter, 0x06a0, 0x00003283);
	else if (mode == 2)
		ret |= d2dp_i2c_write32(adapter, 0x06a0, 0x00003281);
	else if (mode == 3 || mode == 4 || mode == 5)
		ret |= d2dp_i2c_write32(adapter, 0x06a0, 0x00003287);
	mdelay(10);
	ret |= d2dp_i2c_read(adapter, 0x06d0, sizeof(u32), (u8 *)&val);
	pr_debug("d2dp addr=0x%04x 0x%08x\n", 0x06d0, val);
	mdelay(10);
	ret |= d2dp_i2c_write32(adapter, 0x0668, 0x00000102);
	ret |= d2dp_i2c_write32(adapter, 0x066c, 0x00000000);
	ret |= d2dp_i2c_write32(adapter, 0x0660, 0x00000008);
	mdelay(10);
	if (mode == 1)
		ret |= d2dp_i2c_write32(adapter, 0x06a0, 0x00001083);
	else if (mode == 2)
		ret |= d2dp_i2c_write32(adapter, 0x06a0, 0x00001081);
	else if (mode == 3 || mode == 4 || mode == 5)
		ret |= d2dp_i2c_write32(adapter, 0x06a0, 0x00001087);
	mdelay(10);
	ret |= d2dp_i2c_write32(adapter, 0x0668, 0x00000200);
	ret |= d2dp_i2c_write32(adapter, 0x0660, 0x00000409);
	mdelay(10);
	count = 0;
	do {
		ret |= d2dp_i2c_read(adapter, 0x068c, sizeof(u32), (u8 *)&val);
		count++;
		mdelay(5);
	} while ((val & 0x00000003) && count < 5);
	pr_debug("d2dp addr=0x%04x 0x%08x count=%d\n", 0x068c, val, count);
	ret |= d2dp_i2c_read(adapter, 0x067c, sizeof(u32), (u8 *)&val);
	pr_debug("d2dp addr=0x%04x 0x%08x\n", 0x067c, val);
	ret |= d2dp_i2c_read(adapter, 0x0680, sizeof(u32), (u8 *)&val);
	pr_debug("d2dp addr=0x%04x 0x%08x\n", 0x0680, val);
	mdelay(10);

	if (!is_colorbar) {
		if (mode == 1) {
			ret |= d2dp_i2c_write32(adapter, 0x013c, 0x00020003);
			ret |= d2dp_i2c_write32(adapter, 0x0114, 0x00000002);
			ret |= d2dp_i2c_write32(adapter, 0x0164, 0x00000002);
			ret |= d2dp_i2c_write32(adapter, 0x0168, 0x00000002);
			ret |= d2dp_i2c_write32(adapter, 0x016c, 0x00000002);
			ret |= d2dp_i2c_write32(adapter, 0x0170, 0x00000002);
			ret |= d2dp_i2c_write32(adapter, 0x0134, 0x00000007);
			ret |= d2dp_i2c_write32(adapter, 0x0210, 0x00000007);
		} else if (mode == 2) {
			ret |= d2dp_i2c_write32(adapter, 0x013c, 0x000a000c);
			ret |= d2dp_i2c_write32(adapter, 0x0114, 0x00000008);
			ret |= d2dp_i2c_write32(adapter, 0x0164, 0x0000000e);
			ret |= d2dp_i2c_write32(adapter, 0x0168, 0x0000000e);
			ret |= d2dp_i2c_write32(adapter, 0x016c, 0x0000000e);
			ret |= d2dp_i2c_write32(adapter, 0x0170, 0x0000000e);
			ret |= d2dp_i2c_write32(adapter, 0x0134, 0x00000007);
			ret |= d2dp_i2c_write32(adapter, 0x0210, 0x00000007);
		} else if (mode == 3) {
			ret |= d2dp_i2c_write32(adapter, 0x013c, 0x00050006);
			ret |= d2dp_i2c_write32(adapter, 0x0114, 0x00000004);
			ret |= d2dp_i2c_write32(adapter, 0x0164, 0x00000004);
			ret |= d2dp_i2c_write32(adapter, 0x0168, 0x00000004);
			ret |= d2dp_i2c_write32(adapter, 0x016c, 0x00000004);
			ret |= d2dp_i2c_write32(adapter, 0x0170, 0x00000004);
			ret |= d2dp_i2c_write32(adapter, 0x0134, 0x0000000f);
			ret |= d2dp_i2c_write32(adapter, 0x0210, 0x0000000f);
		} else if (mode == 4) {
			ret |= d2dp_i2c_write32(adapter, 0x013c, 0x00030005);
			ret |= d2dp_i2c_write32(adapter, 0x0114, 0x00000003);
			ret |= d2dp_i2c_write32(adapter, 0x0164, 0x00000002);
			ret |= d2dp_i2c_write32(adapter, 0x0168, 0x00000002);
			ret |= d2dp_i2c_write32(adapter, 0x016c, 0x00000002);
			ret |= d2dp_i2c_write32(adapter, 0x0170, 0x00000002);
			ret |= d2dp_i2c_write32(adapter, 0x0134, 0x0000001f);
			ret |= d2dp_i2c_write32(adapter, 0x0210, 0x0000001f);
		} else if (mode == 5) {
			ret |= d2dp_i2c_write32(adapter, 0x013c, 0x0008000b);
			ret |= d2dp_i2c_write32(adapter, 0x0114, 0x00000008);
			ret |= d2dp_i2c_write32(adapter, 0x0164, 0x00000008);
			ret |= d2dp_i2c_write32(adapter, 0x0168, 0x00000008);
			ret |= d2dp_i2c_write32(adapter, 0x016c, 0x00000008);
			ret |= d2dp_i2c_write32(adapter, 0x0170, 0x00000008);
			ret |= d2dp_i2c_write32(adapter, 0x0134, 0x0000001f);
			ret |= d2dp_i2c_write32(adapter, 0x0210, 0x0000001f);
		}
		ret |= d2dp_i2c_write32(adapter, 0x0104, 0x00000001);
		ret |= d2dp_i2c_write32(adapter, 0x0204, 0x00000001);
		mdelay(10);
	}
	if (mode == 1) {
		ret |= d2dp_i2c_write32(adapter, 0x0450, 0x01e00100);
		if (!is_colorbar) {
			ret |= d2dp_i2c_write32(adapter, 0x0454, 0x003c003e);
			ret |= d2dp_i2c_write32(adapter, 0x045c, 0x001e0006);
			ret |= d2dp_i2c_write32(adapter, 0x0464, 0x00000001);
		}
	} else if (mode == 2) {
		ret |= d2dp_i2c_write32(adapter, 0x0450, 0x02800100);
		ret |= d2dp_i2c_write32(adapter, 0x0454, 0x00580080);
		ret |= d2dp_i2c_write32(adapter, 0x0458, 0x002c0320);
		ret |= d2dp_i2c_write32(adapter, 0x045c, 0x00170004);
		ret |= d2dp_i2c_write32(adapter, 0x0460, 0x00070258);
		ret |= d2dp_i2c_write32(adapter, 0x0464, 0x00000001);
	} else if (mode == 3) {
		ret |= d2dp_i2c_write32(adapter, 0x0450, 0x1c200100);
		if (!is_colorbar) {
			ret |= d2dp_i2c_write32(adapter, 0x0454, 0x00dc0028);
			ret |= d2dp_i2c_write32(adapter, 0x045c, 0x00140005);
			ret |= d2dp_i2c_write32(adapter, 0x0464, 0x00000001);
		}
	} else if (mode == 4 || mode == 5) {
		ret |= d2dp_i2c_write32(adapter, 0x0450, 0x05800100);
		if (!is_colorbar) {
			ret |= d2dp_i2c_write32(adapter, 0x0454, 0x0094002c);
			ret |= d2dp_i2c_write32(adapter, 0x045c, 0x00240005);
			ret |= d2dp_i2c_write32(adapter, 0x0464, 0x00000001);
		}
	}
	mdelay(10);
	if (mode == 1) {
		ret |= d2dp_i2c_write32(adapter, 0x0644, 0x002f034a);
		ret |= d2dp_i2c_write32(adapter, 0x0648, 0x020d0355);
		ret |= d2dp_i2c_write32(adapter, 0x064c, 0x0024007a);
		ret |= d2dp_i2c_write32(adapter, 0x0650, 0x01e002d0);
		ret |= d2dp_i2c_write32(adapter, 0x0654, 0x8006803e);
	} else if (mode == 2) {
		ret |= d2dp_i2c_write32(adapter, 0x0644, 0x003e03f8);
		ret |= d2dp_i2c_write32(adapter, 0x0648, 0x027a0424);
		ret |= d2dp_i2c_write32(adapter, 0x064c, 0x001b00d8);
		ret |= d2dp_i2c_write32(adapter, 0x0650, 0x02580320);
		ret |= d2dp_i2c_write32(adapter, 0x0654, 0x80048080);
	} else if (mode == 3) {
		ret |= d2dp_i2c_write32(adapter, 0x0644, 0x002f0604);
		ret |= d2dp_i2c_write32(adapter, 0x0648, 0x02ee07c7);
		ret |= d2dp_i2c_write32(adapter, 0x064c, 0x00190104);
		ret |= d2dp_i2c_write32(adapter, 0x0650, 0x02d00500);
		ret |= d2dp_i2c_write32(adapter, 0x0654, 0x80058028);
	} else if (mode == 4 || mode == 5) {
		ret |= d2dp_i2c_write32(adapter, 0x0644, 0x002f0840);
		ret |= d2dp_i2c_write32(adapter, 0x0648, 0x04650898);
		ret |= d2dp_i2c_write32(adapter, 0x064c, 0x002900c0);
		ret |= d2dp_i2c_write32(adapter, 0x0650, 0x04380780);
		ret |= d2dp_i2c_write32(adapter, 0x0654, 0x8005802c);
	}
	mdelay(10);
	ret |= d2dp_i2c_write32(adapter, 0x0658, 0x1f3f0020);
	mdelay(10);
	if (is_colorbar) {
		/* for colorbar test */
		if (mode == 1 || mode == 3 || mode == 4 || mode == 5)
			ret |= d2dp_i2c_write32(adapter, 0x0a00, 0x78146312);
		else if (mode == 2)
			ret |= d2dp_i2c_write32(adapter, 0x0a00, 0x78006312);
	}
	if (mode == 1) {
		ret |= d2dp_i2c_write32(adapter, 0x0610, 0x00000070);
		ret |= d2dp_i2c_write32(adapter, 0x0614, 0x00000465);
	} else if (mode == 2) {
		ret |= d2dp_i2c_write32(adapter, 0x0610, 0x00000038);
		ret |= d2dp_i2c_write32(adapter, 0x0614, 0x000000e1);
	} else if (mode == 3) {
		ret |= d2dp_i2c_write32(adapter, 0x0610, 0x00000070);
		ret |= d2dp_i2c_write32(adapter, 0x0614, 0x00000195);
	} else if (mode == 4) {
		ret |= d2dp_i2c_write32(adapter, 0x0610, 0x0000003e);
		ret |= d2dp_i2c_write32(adapter, 0x0614, 0x000000e1);
	} else if (mode == 5) {
		ret |= d2dp_i2c_write32(adapter, 0x0610, 0x0000007c);
		ret |= d2dp_i2c_write32(adapter, 0x0614, 0x000000e1);
	}
	mdelay(10);
	ret |= d2dp_i2c_write32(adapter, 0x0600, 0x00000041);
	ret |= d2dp_i2c_write32(adapter, 0x0600, 0x00000043);
	mdelay(10);
	if (is_colorbar) {
		/* for colorbar test */
		ret |= d2dp_i2c_write32(adapter, 0x0510, 0x00000003);
	} else
		ret |= d2dp_i2c_write32(adapter, 0x0510, 0x00000001);
	mdelay(10);
	ret |= d2dp_i2c_read(adapter, 0x0610, sizeof(u32), (u8 *)&val);
	pr_debug("d2dp addr=0x%04x 0x%08x\n", 0x0610, val);
	ret |= d2dp_i2c_read(adapter, 0x0614, sizeof(u32), (u8 *)&val);
	pr_debug("d2dp addr=0x%04x 0x%08x\n", 0x0614, val);
	ret |= d2dp_i2c_read(adapter, 0x0618, sizeof(u32), (u8 *)&val);
	pr_debug("d2dp addr=0x%04x 0x%08x\n", 0x0618, val);
	mdelay(10);
	ret |= d2dp_i2c_read(adapter, 0x0508, sizeof(u32), (u8 *)&val);
	pr_debug("d2dp addr=0x%04x 0x%08x\n", 0x0508, val);
	mdelay(10);
	ret |= d2dp_i2c_read(adapter, 0x0220, sizeof(u32), (u8 *)&val);
	pr_debug("d2dp addr=0x%04x 0x%08x\n", 0x0220, val);
	mdelay(10);
	if (mode == 1 || mode == 3 || mode == 4 || mode == 5)
		ret |= d2dp_i2c_write32(adapter, 0x0448, 0x00000080);

	mutex_unlock(&d2dp_lock);

	return 0;

err:
	mutex_unlock(&d2dp_lock);

	return -EINVAL;
}

#endif /* CONFIG_FB_TZ3000_USE_D2DP */
#ifdef CONFIG_FB_TZ3000_USE_D2DPI
static DEFINE_MUTEX(d2dpi_lock);

static inline int d2dpi_i2c_read(struct i2c_adapter *adapter,
			 u16 addr, u16 count, u8 *buf)
{
	int ret, retries;
	u8 msg_buf[2];
	struct i2c_msg msgs[] = {
		{
			.addr   = D2DPI_I2C_ADDR,
			.flags  = 0,
			.len    = 2,
			.buf    = (u8 *)&msg_buf[0],
		}, {
			.addr   = D2DPI_I2C_ADDR,
			.flags  = I2C_M_RD,
			.len    = count,
			.buf    = (u8 *)buf,
		}
	};

	u8 *paddr = (u8 *)&addr;

	msg_buf[0] = paddr[1];
	msg_buf[1] = paddr[0];

	for (retries = 3; retries > 0; retries--) {
		ret = i2c_transfer(adapter, msgs, 2);
		if (ret == 2)
			return 0;

		if (ret != -EAGAIN)
			break;
	}
	if (ret != 2)
		pr_err("i2c_transfer addr=0x%04x read error %d\n", addr, ret);

	return ret < 0 ? ret : -EIO;
}

static inline int d2dpi_i2c_write32(struct i2c_adapter *adapter,
			    u16 addr, u32 val)
{
	int ret, retries;
	unsigned int ii;
	u8 msg_buf[2 + sizeof(u32)];
	struct i2c_msg msgs[] = {
		{
			.addr   = D2DPI_I2C_ADDR,
			.flags  = 0,
			.len    = 2 + sizeof(u32),
			.buf    = (u8 *)&msg_buf[0],
		}
	};

	u8 *paddr = (u8 *)&addr;
	u8 *pbuf = (u8 *)&val;

	msg_buf[0] = paddr[1];
	msg_buf[1] = paddr[0];
	for (ii = 0; ii < sizeof(u32); ii++)
		msg_buf[2 + ii] = pbuf[ii];

	for (retries = 3; retries > 0; retries--) {
		ret = i2c_transfer(adapter, msgs, 1);
		if (ret == 1)
			return 0;

		if (ret != -EAGAIN)
			break;
	}
	if (ret != 1)
		pr_err("i2c_transfer addr=0x%04x write error %d\n", addr, ret);

	return ret < 0 ? ret : -EIO;
}

static void d2dpi_reset(void)
{
	int val;

	mutex_lock(&d2dpi_lock);

	val = gpio_get_value(D2DPI_RESET_GPIO);
	if (val == 0)
		pr_debug("gpio%d=low : D2DPI reset\n", D2DPI_RESET_GPIO);
	else
		pr_debug("gpio%d=High: D2DPI unreset\n", D2DPI_RESET_GPIO);
	if (val > 0) {
		gpio_set_value(D2DPI_RESET_GPIO, 0);
		mdelay(10);
		val = gpio_get_value(D2DPI_RESET_GPIO);
		if (val == 0)
			pr_debug("gpio%d=low : D2DPI reset\n", D2DPI_RESET_GPIO);
		else
			pr_debug("gpio%d=High: D2DPI unreset\n", D2DPI_RESET_GPIO);
	}
	gpio_set_value(D2DPI_RESET_GPIO, 1);
	mdelay(10);
	val = gpio_get_value(D2DPI_RESET_GPIO);
	if (val == 0)
		pr_debug("gpio%d=low : D2DPI reset\n", D2DPI_RESET_GPIO);
	else
		pr_debug("gpio%d=High: D2DPI unreset\n", D2DPI_RESET_GPIO);

	mdelay(10);

	mutex_unlock(&d2dpi_lock);
}

static int d2dpi_init(u32 mode)
{
	int ret;
	struct i2c_adapter *adapter;

	switch (mode) {
	case 2:		/*  800x 600@60P */
		break;
	default:
		pr_err("This mode is not supported : %d\n", mode);
		return 0;
		break;
	}

	mutex_lock(&d2dpi_lock);

	adapter = i2c_get_adapter(D2DPI_I2C_BUS);
	if (!adapter) {
		pr_err("Failed to get I2C adapter, bus %d\n", 2);
		goto err;
	}

	ret  = d2dpi_i2c_write32(adapter, 0x0448, 0x00000080);	/* POCTRL */
	ret |= d2dpi_i2c_write32(adapter, 0x06a0, 0x00003080);	/* DP0_SRCCTRL */
	ret |= d2dpi_i2c_write32(adapter, 0x0918, 0x00000101);	/* SYS_PLLPARAM */
	ret |= d2dpi_i2c_write32(adapter, 0x0914, 0x00150219);	/* PXL_PLLPARAM */

	ret |= d2dpi_i2c_write32(adapter, 0x0900, 0x00000001);	/* DP0_PLLCTRL */
	mdelay(10);
	ret |= d2dpi_i2c_write32(adapter, 0x0900, 0x00000005);	/* DP0_PLLCTRL */

	ret |= d2dpi_i2c_write32(adapter, 0x0908, 0x00000001);	/* PXL_PLLCTRL */
	mdelay(10);
	ret |= d2dpi_i2c_write32(adapter, 0x0908, 0x00000005);	/* PXL_PLLCTRL */

	ret  = d2dpi_i2c_write32(adapter, 0x013c, 0x000A000C);	/* PPI_TX_RX_TA */
	ret |= d2dpi_i2c_write32(adapter, 0x0114, 0x00000008);	/* LPTXTIMCNT */
	ret |= d2dpi_i2c_write32(adapter, 0x0164, 0x0000000E);	/* D0S_CLRSIPOCOUNT */
	ret |= d2dpi_i2c_write32(adapter, 0x0168, 0x0000000E);	/* D1S_CLRSIPOCOUNT */
	ret |= d2dpi_i2c_write32(adapter, 0x016c, 0x0000000E);	/* D2S_CLRSIPOCOUNT */
	ret |= d2dpi_i2c_write32(adapter, 0x0170, 0x0000000E);	/* D3S_CLRSIPOCOUNT */
	ret |= d2dpi_i2c_write32(adapter, 0x0134, 0x00000007);	/* PPI_LANEENABLE */
	ret |= d2dpi_i2c_write32(adapter, 0x0210, 0x00000007);	/* DSI_LANEENABLE */
	ret |= d2dpi_i2c_write32(adapter, 0x0104, 0x00000001);	/* STARTPPI */
	ret |= d2dpi_i2c_write32(adapter, 0x0204, 0x00000001);	/* STARTDSI */

	ret |= d2dpi_i2c_write32(adapter, 0x0450, 0x03F00100);	/* VPCTRL */
	ret |= d2dpi_i2c_write32(adapter, 0x0454, 0x00180080);	/* HTIM01 */
	ret |= d2dpi_i2c_write32(adapter, 0x045c, 0x00040001);	/* VTIM01 */
	ret |= d2dpi_i2c_write32(adapter, 0x0464, 0x00000001);	/* VFUEN0 */
	ret |= d2dpi_i2c_write32(adapter, 0x0510, 0x00000001);	/* SYSCTRL */

	mutex_unlock(&d2dpi_lock);

	return 0;

err:
	mutex_unlock(&d2dpi_lock);

	return -EINVAL;
}

#endif /* CONFIG_FB_TZ3000_USE_D2DPI */
static void dispif_control_pmu(void __iomem *regs, u32 en)
{
	volatile u32 PLLDSI_0, PLLDSI_1;

	switch (en) {
	case cgate_off:
#if defined(DISPIF_800X600_60HZ_A) || defined(DISPIF_800X600_60HZ_B)
		PLLDSI_0 = dispif_read_reg(regs, PMU_PLLConfig_PLLDSI_0_OFFS);
		PLLDSI_0 |= 0x80000000;
		dispif_write_reg(regs, PMU_PLLConfig_PLLDSI_0_OFFS, PLLDSI_0);
		PLLDSI_1 = 0x0100077a;
		dispif_write_reg(regs, PMU_PLLConfig_PLLDSI_1_OFFS, PLLDSI_1);
		PLLDSI_0 = dispif_read_reg(regs, PMU_PLLConfig_PLLDSI_0_OFFS);
		PLLDSI_0 &= ~0x80000000;
		dispif_write_reg(regs, PMU_PLLConfig_PLLDSI_0_OFFS, PLLDSI_0);
		udelay(1000);

#else
		PLLDSI_0 = dispif_read_reg(regs, PMU_PLLConfig_PLLDSI_0_OFFS);
		PLLDSI_0 |= 0x80000000;
		dispif_write_reg(regs, PMU_PLLConfig_PLLDSI_0_OFFS, PLLDSI_0);
		PLLDSI_1 = 0x0100046b;
		dispif_write_reg(regs, PMU_PLLConfig_PLLDSI_1_OFFS, PLLDSI_1);
		PLLDSI_0 = dispif_read_reg(regs, PMU_PLLConfig_PLLDSI_0_OFFS);
		PLLDSI_0 &= ~0x80000000;
		dispif_write_reg(regs, PMU_PLLConfig_PLLDSI_0_OFFS, PLLDSI_0);
		udelay(1000);

#endif /* defined(DISPIF_800X600_60HZ_x) */
		/* Gating Clk OFF */
		dispif_write_reg(regs, PMU_ClockGatingOff_eastpierSS_0_OFFS, 0x0003000f);
		dispif_write_reg(regs, PMU_SoftResetOff_eastpierSS_0_OFFS, 0x0003000f);
#if 0
		dispif_write_reg(regs, PMU_ClockGatingOff_dispifSS_0_OFFS, 0x00000101);
#else
		clk_prepare_enable(priv.clk_dispif);
#endif
		dispif_write_reg(regs, PMU_SoftResetOff_dispifSS_0_OFFS, 0x00000003);
		break;
	case cgate_on:
		/* Gating Clk ON */
		dispif_write_reg(regs, PMU_SoftResetOn_dispifSS_0_OFFS, 0x00000003);
#if 0
		dispif_write_reg(regs, PMU_ClockGatingOn_dispifSS_0_OFFS, 0x00000101);
#else
		clk_disable_unprepare(priv.clk_dispif);
#endif

		PLLDSI_0 = dispif_read_reg(regs, PMU_PLLConfig_PLLDSI_0_OFFS);
		PLLDSI_0 |= 0x80000000;
		dispif_write_reg(regs, PMU_PLLConfig_PLLDSI_0_OFFS, PLLDSI_0);
		PLLDSI_1 = 0x0100046b;
		dispif_write_reg(regs, PMU_PLLConfig_PLLDSI_1_OFFS, PLLDSI_1);
		PLLDSI_0 = dispif_read_reg(regs, PMU_PLLConfig_PLLDSI_0_OFFS);
		PLLDSI_0 &= ~0x80000000;
		dispif_write_reg(regs, PMU_PLLConfig_PLLDSI_0_OFFS, PLLDSI_0);
		udelay(1000);
		break;
	}
}

static void dispif_control_irq(void __iomem *regs, u32 ctrl)
{
	switch (ctrl) {
	case irq_disable_all:
		/* irq disable all */
		dispif_write_reg(regs, DISPIF_IRQ_EN_OFFS, 0x00000000);
		break;
	case irq_enable_all:
		/* irq enable all */
		dispif_write_reg(regs, DISPIF_IRQ_EN_OFFS, 0x01111111);
		break;
	case irq_stat_clear_all:
		/* irq status clear all */
		dispif_write_reg(regs, DISPIF_IRQ_STAT_OFFS, 0x01111111);
		break;
	}
}

static void dispif_control_dtg(void __iomem *regs, u32 ctrl)
{
	switch (ctrl) {
	case dtg_start:
		/* DTG start */
		dispif_write_reg(regs, DISPIF_DTG_START_OFFS, 0x00000001);
		break;
	case dtg_stop:
		/* DTG stop */
		dispif_write_reg(regs, DISPIF_DTG_STOP_OFFS, 0x00000001);
		break;
	case dtg_force_stop:
		/* DTG force stop */
		dispif_write_reg(regs, DISPIF_DTG_FORCE_STOP_OFFS, 0x00000001);
		break;
	}
}

static void dispif_set_dtg(void __iomem *regs, u32 mode)
{
	switch (mode) {
	case 1:
		/* 720x480(2574x525) */
		dispif_write_reg(regs, DISPIF_HV_DLY_OFFS, 0x00010001);
		dispif_write_reg(regs, DISPIF_HV_MAX_OFFS, 0x020D0A0E);
		dispif_write_reg(regs, DISPIF_HD_OFFS, 0x00BA0001);
		dispif_write_reg(regs, DISPIF_VD_R_OFFS, 0x00010001);
		dispif_write_reg(regs, DISPIF_VD_F_OFFS, 0x00060A0E);
		dispif_write_reg(regs, DISPIF_HBLK_OFFS, 0x016E09DF);
		dispif_write_reg(regs, DISPIF_VBLK_OFFS, 0x00240205);
		dispif_write_reg(regs, DISPIF_HS_0_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_HBLK2_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_HD2_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_HS_0_SET1_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_HS_0_SET2_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_MDI_GO_OFFS, 0x00010001);
		break;
	case 2:
		/* 800x600(1056x628) */
		dispif_write_reg(regs, DISPIF_HV_DLY_OFFS, 0x00010001);
#if defined(DISPIF_800X600_60HZ_A)
		dispif_write_reg(regs, DISPIF_HV_MAX_OFFS, 0x02740C60);
#elif defined(DISPIF_800X600_60HZ_B)
		dispif_write_reg(regs, DISPIF_HV_MAX_OFFS, 0x027A0C6C);
#elif defined(DISPIF_800X600_60HZ_C)
		dispif_write_reg(regs, DISPIF_HV_MAX_OFFS, 0x027A0C6C);
#endif /* defined(DISPIF_800X600_60HZ_x) */
		dispif_write_reg(regs, DISPIF_HD_OFFS, 0x01800001);
		dispif_write_reg(regs, DISPIF_VD_R_OFFS, 0x00010001);
#if defined(DISPIF_800X600_60HZ_A)
		dispif_write_reg(regs, DISPIF_VD_F_OFFS, 0x00040C60);
#elif defined(DISPIF_800X600_60HZ_B)
		dispif_write_reg(regs, DISPIF_VD_F_OFFS, 0x00040C6C);
#elif defined(DISPIF_800X600_60HZ_C)
		dispif_write_reg(regs, DISPIF_VD_F_OFFS, 0x00040C6C);
#endif /* defined(DISPIF_800X600_60HZ_x) */
		dispif_write_reg(regs, DISPIF_HBLK_OFFS, 0x02880BE9);
		dispif_write_reg(regs, DISPIF_VBLK_OFFS, 0x001B0274);
		dispif_write_reg(regs, DISPIF_HS_0_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_HBLK2_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_HD2_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_HS_0_SET1_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_HS_0_SET2_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_MDI_GO_OFFS, 0x00010001);
		break;
	case 3:
		/* 1280x720(3960x750) */
		dispif_write_reg(regs, DISPIF_HV_DLY_OFFS, 0x00010001);
#if defined(DISPIF_1280X720_50HZ)
		dispif_write_reg(regs, DISPIF_HV_MAX_OFFS, 0x02EE0F78);
#elif defined(DISPIF_1280X720_60HZ)
		dispif_write_reg(regs, DISPIF_HV_MAX_OFFS, 0x02EE0CE4);
#endif /* defined(DISPIF_1280X720_xxHZ) */
		dispif_write_reg(regs, DISPIF_HD_OFFS, 0x00500001);
		dispif_write_reg(regs, DISPIF_VD_R_OFFS, 0x00010001);
#if defined(DISPIF_1280X720_50HZ)
		dispif_write_reg(regs, DISPIF_VD_F_OFFS, 0x00050F78);
#elif defined(DISPIF_1280X720_60HZ)
		dispif_write_reg(regs, DISPIF_VD_F_OFFS, 0x00050CE4);
#endif /* defined(DISPIF_1280X720_xxHZ) */
		dispif_write_reg(regs, DISPIF_HBLK_OFFS, 0x02080C09);
		dispif_write_reg(regs, DISPIF_VBLK_OFFS, 0x001902EA);
		dispif_write_reg(regs, DISPIF_HS_0_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_HBLK2_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_HD2_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_HS_0_SET1_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_HS_0_SET2_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_MDI_GO_OFFS, 0x00010001);
		break;
	case 4:
	case 5:
		/* 1920x1080(3300x1125) */
		dispif_write_reg(regs, DISPIF_HV_DLY_OFFS, 0x00010001);
		dispif_write_reg(regs, DISPIF_HV_MAX_OFFS, 0x04650CE4);
		dispif_write_reg(regs, DISPIF_HD_OFFS, 0x00420001);
		dispif_write_reg(regs, DISPIF_VD_R_OFFS, 0x00010001);
		dispif_write_reg(regs, DISPIF_VD_F_OFFS, 0x00050CE4);
		dispif_write_reg(regs, DISPIF_HBLK_OFFS, 0x01200C61);
		dispif_write_reg(regs, DISPIF_VBLK_OFFS, 0x00290462);
		dispif_write_reg(regs, DISPIF_HS_0_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_HBLK2_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_HD2_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_HS_0_SET1_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_HS_0_SET2_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_MDI_GO_OFFS, 0x00010001);
		break;
	}
}

static void dispif_set_ppi(void __iomem *regs, u32 mode)
{
	switch (mode) {
	case 1:
		/* 720x480@60P */
		dispif_write_reg(regs, DISPIF_DSI_PPI_LINEINTCNT_OFFS, 0x00001FA5);
		dispif_write_reg(regs, DISPIF_DSI_PPI_LPTXTIMECNT_OFFS, 0x00000004);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TCLK_HEADERCNT_OFFS, 0x00000A03);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TCLK_TRAILCNT_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_DSI_PPI_THS_HEADERCNT_OFFS, 0x00000004);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TWAKEUP_OFFS, 0x00003F49);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TCLK_POSTCNT_OFFS, 0x00000007);
		dispif_write_reg(regs, DISPIF_DSI_PPI_THS_TRAILCNT_OFFS, 0x00000002);
		dispif_write_reg(regs, DISPIF_DSI_PPI_HSTXVREGCNT_OFFS, 0x00000020);
		dispif_write_reg(regs, DISPIF_DSI_PPI_HSTXVREGTN_OFFS, 0x0000001F);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TXOPTIONCNTRL_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_DSI_PPI_BTACNTRL1_OFFS, 0x00030002);
		dispif_write_reg(regs, DISPIF_DSI_PPI_STARTCNTRL_OFFS, 0x00000001);
		break;
	case 2:
		/* 800x600@60P */
#if defined(DISPIF_800X600_60HZ_A)
		dispif_write_reg(regs, DISPIF_DSI_PPI_LINEINTCNT_OFFS, 0x00002EE0);
		dispif_write_reg(regs, DISPIF_DSI_PPI_LPTXTIMECNT_OFFS, 0x00000006);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TCLK_HEADERCNT_OFFS, 0x00000F06);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TCLK_TRAILCNT_OFFS, 0x00000004);
		dispif_write_reg(regs, DISPIF_DSI_PPI_THS_HEADERCNT_OFFS, 0x00000706);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TWAKEUP_OFFS, 0x00004E20);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TCLK_POSTCNT_OFFS, 0x0000000B);
		dispif_write_reg(regs, DISPIF_DSI_PPI_THS_TRAILCNT_OFFS, 0x00000005);
		dispif_write_reg(regs, DISPIF_DSI_PPI_HSTXVREGCNT_OFFS, 0x00000020);
		dispif_write_reg(regs, DISPIF_DSI_PPI_HSTXVREGTN_OFFS, 0x00000007);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TXOPTIONCNTRL_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_DSI_PPI_BTACNTRL1_OFFS, 0x00180006);
#elif defined(DISPIF_800X600_60HZ_B)
		dispif_write_reg(regs, DISPIF_DSI_PPI_LINEINTCNT_OFFS, 0x00002F40);
		dispif_write_reg(regs, DISPIF_DSI_PPI_LPTXTIMECNT_OFFS, 0x00000007);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TCLK_HEADERCNT_OFFS, 0x00001007);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TCLK_TRAILCNT_OFFS, 0x00000004);
		dispif_write_reg(regs, DISPIF_DSI_PPI_THS_HEADERCNT_OFFS, 0x00000807);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TWAKEUP_OFFS, 0x00004380);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TCLK_POSTCNT_OFFS, 0x0000000B);
		dispif_write_reg(regs, DISPIF_DSI_PPI_THS_TRAILCNT_OFFS, 0x00000005);
		dispif_write_reg(regs, DISPIF_DSI_PPI_HSTXVREGCNT_OFFS, 0x00000020);
		dispif_write_reg(regs, DISPIF_DSI_PPI_HSTXVREGTN_OFFS, 0x00000007);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TXOPTIONCNTRL_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_DSI_PPI_BTACNTRL1_OFFS, 0x001C0007);
#elif defined(DISPIF_800X600_60HZ_C)
		dispif_write_reg(regs, DISPIF_DSI_PPI_LINEINTCNT_OFFS, 0x00002F3E);
		dispif_write_reg(regs, DISPIF_DSI_PPI_LPTXTIMECNT_OFFS, 0x00000007);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TCLK_HEADERCNT_OFFS, 0x00001007);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TCLK_TRAILCNT_OFFS, 0x00000004);
		dispif_write_reg(regs, DISPIF_DSI_PPI_THS_HEADERCNT_OFFS, 0x00000807);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TWAKEUP_OFFS, 0x0000437D);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TCLK_POSTCNT_OFFS, 0x0000000B);
		dispif_write_reg(regs, DISPIF_DSI_PPI_THS_TRAILCNT_OFFS, 0x00000005);
		dispif_write_reg(regs, DISPIF_DSI_PPI_HSTXVREGCNT_OFFS, 0x00000020);
		dispif_write_reg(regs, DISPIF_DSI_PPI_HSTXVREGTN_OFFS, 0x00000007);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TXOPTIONCNTRL_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_DSI_PPI_BTACNTRL1_OFFS, 0x001C0007);
#endif /* defined(DISPIF_800X600_60HZ_x) */
/*		dispif_write_reg(regs, 0x03E4, 0x00000000);	*/
		dispif_write_reg(regs, DISPIF_DSI_PPI_STARTCNTRL_OFFS, 0x00000001);
		break;
	case 3:
		/* 1280x720@50P */
		dispif_write_reg(regs, DISPIF_DSI_PPI_LINEINTCNT_OFFS, 0x00003a03);
		dispif_write_reg(regs, DISPIF_DSI_PPI_LPTXTIMECNT_OFFS, 0x00000007);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TCLK_HEADERCNT_OFFS, 0x00001507);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TCLK_TRAILCNT_OFFS, 0x00000005);
		dispif_write_reg(regs, DISPIF_DSI_PPI_THS_HEADERCNT_OFFS, 0x00000307);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TWAKEUP_OFFS, 0x00004884);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TCLK_POSTCNT_OFFS, 0x0000000B);
		dispif_write_reg(regs, DISPIF_DSI_PPI_THS_TRAILCNT_OFFS, 0x00000004);
		dispif_write_reg(regs, DISPIF_DSI_PPI_HSTXVREGCNT_OFFS, 0x00000020);
		dispif_write_reg(regs, DISPIF_DSI_PPI_HSTXVREGTN_OFFS, 0x0000001F);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TXOPTIONCNTRL_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_DSI_PPI_BTACNTRL1_OFFS, 0x00070008);
		dispif_write_reg(regs, DISPIF_DSI_PPI_STARTCNTRL_OFFS, 0x00000001);
		break;
	case 4:
		/* 1920x1080@30P */
		dispif_write_reg(regs, DISPIF_DSI_PPI_LINEINTCNT_OFFS, 0x00002b83);
		dispif_write_reg(regs, DISPIF_DSI_PPI_LPTXTIMECNT_OFFS, 0x00000006);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TCLK_HEADERCNT_OFFS, 0x00002005);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TCLK_TRAILCNT_OFFS, 0x00000003);
		dispif_write_reg(regs, DISPIF_DSI_PPI_THS_HEADERCNT_OFFS, 0x00000505);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TWAKEUP_OFFS, 0x00003e28);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TCLK_POSTCNT_OFFS, 0x00000007);
		dispif_write_reg(regs, DISPIF_DSI_PPI_THS_TRAILCNT_OFFS, 0x00000003);
		dispif_write_reg(regs, DISPIF_DSI_PPI_HSTXVREGCNT_OFFS, 0x00000020);
		dispif_write_reg(regs, DISPIF_DSI_PPI_HSTXVREGTN_OFFS, 0x0000001F);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TXOPTIONCNTRL_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_DSI_PPI_BTACNTRL1_OFFS, 0x000b0008);
		dispif_write_reg(regs, DISPIF_DSI_PPI_STARTCNTRL_OFFS, 0x00000001);
	case 5:
		/* 1920x1080@60P */
		dispif_write_reg(regs, DISPIF_DSI_PPI_LINEINTCNT_OFFS, 0x00005705);
		dispif_write_reg(regs, DISPIF_DSI_PPI_LPTXTIMECNT_OFFS, 0x0000000b);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TCLK_HEADERCNT_OFFS, 0x0000200a);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TCLK_TRAILCNT_OFFS, 0x00000005);
		dispif_write_reg(regs, DISPIF_DSI_PPI_THS_HEADERCNT_OFFS, 0x00000a0a);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TWAKEUP_OFFS, 0x00004884);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TCLK_POSTCNT_OFFS, 0x0000000E);
		dispif_write_reg(regs, DISPIF_DSI_PPI_THS_TRAILCNT_OFFS, 0x00000006);
		dispif_write_reg(regs, DISPIF_DSI_PPI_HSTXVREGCNT_OFFS, 0x00000020);
		dispif_write_reg(regs, DISPIF_DSI_PPI_HSTXVREGTN_OFFS, 0x0000001F);
		dispif_write_reg(regs, DISPIF_DSI_PPI_TXOPTIONCNTRL_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_DSI_PPI_BTACNTRL1_OFFS, 0x000b0008);
		dispif_write_reg(regs, DISPIF_DSI_PPI_STARTCNTRL_OFFS, 0x00000001);
		break;
	}
}

static void dispif_control_dsi(void __iomem *regs, u32 ctrl)
{
	switch (ctrl) {
	case dsi_reset:
		/* DSI reset */
		dispif_write_reg(regs, DISPIF_DSI_RESET_OFFS, 0x0000003e);
		break;
	case dsi_continue:
		/* DSI continue */
		dispif_write_reg(regs, DISPIF_DSI_CONTINUE_OFFS, 0x00000001);
		break;
	case dsi_pause:
		/* DSI pause */
		dispif_write_reg(regs, DISPIF_DSI_PAUSE_OFFS, 0x00000001);
		break;
	case dsi_start:
		/* DSI start */
		dispif_write_reg(regs, DISPIF_DSI_START_OFFS, 0x00000001);
		break;
	case dsi_int_clear:
		/* DSI INT clear */
		dispif_write_reg(regs, DISPIF_DSI_INT_CLR_OFFS, 0xffffffff);
		break;
	}
}

static void dispif_set_dsi_cq0(void __iomem *regs, u32 mode)
{
	/* CQ */
	switch (mode) {
	case 1:
		/* 720x480 */
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0xA6002000);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x83000080);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x95000000);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0xA30000A2);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x0415FFFF);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28800005);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000001);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000002);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000031);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x04030004);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000001);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000021);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000002);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000031);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000008);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000011);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000002);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000031);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x0403001C);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000001);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000021);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000002);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000031);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000001);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000021);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000002);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000031);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000010);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x4008703E);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x040501DE);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x40002419);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000021);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000002);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000031);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000010);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x4008703E);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x40002419);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000021);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000002);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000031);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x04030007);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000001);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000021);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000002);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000031);
		break;
	case 2:
		/* 800x600 */
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0xA6002000);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x83000080);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x95000000);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0xA30000A2);
#if defined(DISPIF_800X600_60HZ_A)
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x040FFFFF);
#elif defined(DISPIF_800X600_60HZ_B)
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x0410FFFF);
#elif defined(DISPIF_800X600_60HZ_C)
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x0410FFFF);
#endif /* defined(DISPIF_800X600_60HZ_x) */
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28800005);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000001);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x40017619);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000031);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x04030002);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000001);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000021);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x40017619);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000031);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000008);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000011);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x40017619);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000031);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x04030015);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000001);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000021);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x40017619);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000031);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000001);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x04050257);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000021);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x40017619);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000031);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x4000FE19);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x4009603E);
#if defined(DISPIF_800X600_60HZ_A)
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x40006C19);
#elif defined(DISPIF_800X600_60HZ_B)
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x40007819);
#elif defined(DISPIF_800X600_60HZ_C)
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x40007819);
#endif /* defined(DISPIF_800X600_60HZ_x) */
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000021);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x40017619);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000031);

#if defined(DISPIF_800X600_60HZ_A)
#if 0
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x0403FFFF);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000001);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000021);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x40017619);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000031);
#endif
#elif defined(DISPIF_800X600_60HZ_B)
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x04030005);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000001);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000021);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x40017619);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000031);
#elif defined(DISPIF_800X600_60HZ_C)
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x04030005);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000001);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000021);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x40017619);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000031);
#endif /* defined(DISPIF_800X600_60HZ_x) */
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x0C000000);
		break;
	case 3:
		/* 1280x720 */
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0xA6002000);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x83000080);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x95000000);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0xA30000A4);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x040BFFFF);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28800005);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000001);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000002);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000031);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x04030003);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000001);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000021);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000002);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000031);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000008);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000011);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000002);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000031);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x04030012);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000001);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000021);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000002);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000031);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x040502CF);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000001);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000021);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000002);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000031);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000010);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x400F003E);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x04030004);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000001);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000021);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000002);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000031);
		break;
	case 4:
	case 5:
		/* 1920x1080 */
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0xA6002000);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x83000080);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x95000000);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0xA30000A6);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x040BFFFF);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28800005);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000001);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x40007A19);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000031);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x04030003);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000001);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000021);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x40007A19);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000031);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000008);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000011);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x40007A19);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000031);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x04030022);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000001);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000021);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x40007A19);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000031);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x04050437);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000001);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000021);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x40007A19);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000031);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000010);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x4016803E);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x04030003);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x28000001);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000021);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x40007A19);
		dispif_write_reg(regs, DISPIF_DSI_CQ0_OFFS, 0x10000031);
		break;
	}
}

static void dispif_set_dphy(void __iomem *regs, u32 mode)
{
	switch (mode) {
	case 0:
		dispif_write_reg(regs, DISPIF_DSI_DPHY_CLWCNTRL_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_DSI_DPHY_D0WCNTRL_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_DSI_DPHY_D1WCNTRL_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_DSI_DPHY_D2WCNTRL_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_DSI_DPHY_D3WCNTRL_OFFS, 0x00000000);
		break;
	case 1:
	case 2:
		/* 720x480 2lane */
		/* 800x600 2lane */
		dispif_write_reg(regs, DISPIF_DSI_DPHY_CLWCNTRL_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_DSI_DPHY_D0WCNTRL_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_DSI_DPHY_D1WCNTRL_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_DSI_DPHY_D2WCNTRL_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_DSI_DPHY_D3WCNTRL_OFFS, 0x00000000);
		break;
	case 3:
		/* 1280x720 3lanes */
		dispif_write_reg(regs, DISPIF_DSI_DPHY_CLWCNTRL_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_DSI_DPHY_D0WCNTRL_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_DSI_DPHY_D1WCNTRL_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_DSI_DPHY_D2WCNTRL_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_DSI_DPHY_D3WCNTRL_OFFS, 0x00000000);
		break;
	case 4:
	case 5:
		/* 1920x1080 4lanes */
		dispif_write_reg(regs, DISPIF_DSI_DPHY_CLWCNTRL_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_DSI_DPHY_D0WCNTRL_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_DSI_DPHY_D1WCNTRL_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_DSI_DPHY_D2WCNTRL_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_DSI_DPHY_D3WCNTRL_OFFS, 0x00000001);
		break;
	}
}

static void dispif_set_pll(void __iomem *regs, u32 mode)
{
	switch (mode) {
	case 0:
		/* PLL off */
		dispif_write_reg(regs, DISPIF_ENABLE_OFFS, 0x00000000);
	case 1:
		/* 720x480 ; PLL SET:40.5 */
		dispif_write_reg(regs, DISPIF_PRD_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_FBD_OFFS, 0x00000017);
		dispif_write_reg(regs, DISPIF_FRS_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_CKEN_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_ENABLE_OFFS, 0x00000001);
		break;
	case 2:
#if defined(DISPIF_800X600_60HZ_A)
		/* 800x600 ; PLL SET: 60.484 */
		dispif_write_reg(regs, DISPIF_PRD_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_FBD_OFFS, 0x00000031);
		dispif_write_reg(regs, DISPIF_FRS_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_CKEN_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_ENABLE_OFFS, 0x00000001);
#elif defined(DISPIF_800X600_60HZ_B)
		/* 800x600 ; PLL SET: 60 */
		dispif_write_reg(regs, DISPIF_PRD_OFFS, 0x00000004);
		dispif_write_reg(regs, DISPIF_FBD_OFFS, 0x000000FB);
		dispif_write_reg(regs, DISPIF_FRS_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_CKEN_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_ENABLE_OFFS, 0x00000001);
#elif defined(DISPIF_800X600_60HZ_C)
		/* 800x600 ; PLL SET: 60.484 */
		dispif_write_reg(regs, DISPIF_PRD_OFFS, 0x00000005);
		dispif_write_reg(regs, DISPIF_FBD_OFFS, 0x000000D6);
		dispif_write_reg(regs, DISPIF_FRS_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_CKEN_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_ENABLE_OFFS, 0x00000001);
#endif /* defined(DISPIF_800X600_60HZ_X) */
		break;
	case 3:
		/* 1280x720 ; PLL SET:74.25 */
		dispif_write_reg(regs, DISPIF_PRD_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_FBD_OFFS, 0x00000015);
		dispif_write_reg(regs, DISPIF_FRS_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_CKEN_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_ENABLE_OFFS, 0x00000001);
		break;
	case 4:
		/* 1920x1080@30P ; PLL SET:55.69 */
		dispif_write_reg(regs, DISPIF_PRD_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_FBD_OFFS, 0x00000020);
		dispif_write_reg(regs, DISPIF_FRS_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_CKEN_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_ENABLE_OFFS, 0x00000001);
		break;
	case 5:
		/* 1920x1080@60P ; PLL SET:111.375 */
		dispif_write_reg(regs, DISPIF_PRD_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_FBD_OFFS, 0x00000020);
		dispif_write_reg(regs, DISPIF_FRS_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_CKEN_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_ENABLE_OFFS, 0x00000001);
		break;
	}
}

static void dispif_control_cgate(void __iomem *regs, u32 en)
{
	switch (en) {
	case cgate_off:
		/* Gating Clk OFF */
		dispif_write_reg(regs, DISPIF_DISPIF_CGATE_OFFS, 0x00000113);
		break;
	case cgate_on:
		/* Gating Clk ON */
		dispif_write_reg(regs, DISPIF_DISPIF_CGATE_OFFS, 0x00000000);
		break;
	}
}

static int dispif_set_fconv(void __iomem *regs, u32 mode, u32 xres, u32 yres, u32 format)
{
	u32 fconva_is_yuv = (priv.fconva_format & 0x00000003);
	u32 fconvb_is_yuv = (priv.fconvb_format & 0x00000003);
	u32 fconva_line_length[3] = { priv.fconva_in_xres * (priv.fconva_bpp / 8), 0, 0 };
	u32 fconvb_line_length[3] = { priv.fconvb_in_xres * (priv.fconvb_bpp / 8), 0, 0 };
	u32 fconva_lines[3] = { priv.fconva_in_yres, 0, 0 };
	u32 fconvb_lines[3] = { priv.fconvb_in_yres, 0, 0 };
	u32 fconva_plane_order = 0;
	u32 fconvb_plane_order = 0;
	u32 baseaddr[4][3] = {
		{ priv.fconva_in_base, 0, 0 },
		{ priv.fconva_in_base, 0, 0 },
		{ priv.fconvb_in_base, 0, 0 },
		{ priv.fconvb_in_base, 0, 0 },
	};
	u32 sel_alpha = grobal_alpha;
	u32 ii;

#if 0
	switch (mode) {
	case 1:
		priv.fconva_in_xres = priv.fconvb_in_xres = 720;
		priv.fconva_in_yres = priv.fconvb_in_yres = 480;
		priv.fconva_out_xres = priv.fconvb_out_xres = 720;
		priv.fconva_out_yres = priv.fconvb_out_yres = 480;
		break;
	case 2:
		priv.fconva_in_xres = priv.fconvb_in_xres = 800;
		priv.fconva_in_yres = priv.fconvb_in_yres = 600;
		priv.fconva_out_xres = priv.fconvb_out_xres = 800;
		priv.fconva_out_yres = priv.fconvb_out_yres = 600;
		break;
	case 3:
		priv.fconva_in_xres = priv.fconvb_in_xres = 1280;
		priv.fconva_in_yres = priv.fconvb_in_yres = 720;
		priv.fconva_out_xres = priv.fconvb_out_xres = 1280;
		priv.fconva_out_yres = priv.fconvb_out_yres = 720;
		break;
	case 4:
	case 5:
		priv.fconva_in_xres = priv.fconvb_in_xres = 1920;
		priv.fconva_in_yres = priv.fconvb_in_yres = 1080;
		priv.fconva_out_xres = priv.fconvb_out_xres = 1920;
		priv.fconva_out_yres = priv.fconvb_out_yres = 1080;
		break;
	}
#else
	priv.fconva_in_xres = priv.fconvb_in_xres = xres;
	priv.fconva_in_yres = priv.fconvb_in_yres = yres;
	switch (mode) {
	case 1:
		priv.fconva_out_xres = priv.fconvb_out_xres = 720;
		priv.fconva_out_yres = priv.fconvb_out_yres = 480;
		break;
	case 2:
		priv.fconva_out_xres = priv.fconvb_out_xres = 800;
		priv.fconva_out_yres = priv.fconvb_out_yres = 600;
		break;
	case 3:
		priv.fconva_out_xres = priv.fconvb_out_xres = 1280;
		priv.fconva_out_yres = priv.fconvb_out_yres = 720;
		break;
	case 4:
	case 5:
		priv.fconva_out_xres = priv.fconvb_out_xres = 1920;
		priv.fconva_out_yres = priv.fconvb_out_yres = 1080;
		break;
	}
#endif
	switch (format) {
	case 0:	/* ARGB8888 */
		priv.fconva_format = priv.fconvb_format = ARGB32_ARGB8888;
		priv.fconva_bpp = priv.fconvb_bpp = 32;
		fconva_plane_order = fconvb_plane_order = 0;
		fconva_line_length[0] = priv.fconva_in_xres * (priv.fconva_bpp / 8);
		fconvb_line_length[0] = priv.fconvb_in_xres * (priv.fconvb_bpp / 8);
		fconva_line_length[1] = 0;
		fconvb_line_length[1] = 0;
		fconva_line_length[2] = 0;
		fconvb_line_length[2] = 0;
		fconva_lines[0] = priv.fconva_in_yres;
		fconvb_lines[0] = priv.fconvb_in_yres;
		fconva_lines[1] = 0;
		fconvb_lines[1] = 0;
		fconva_lines[2] = 0;
		fconvb_lines[2] = 0;
		break;
	case 1:	/* RGB565 */
		priv.fconva_format = priv.fconvb_format = RGB16_RGB565;
		priv.fconva_bpp = priv.fconvb_bpp = 16;
		fconva_plane_order = fconvb_plane_order = 0;
		fconva_line_length[0] = priv.fconva_in_xres * (priv.fconva_bpp / 8);
		fconvb_line_length[0] = priv.fconvb_in_xres * (priv.fconvb_bpp / 8);
		fconva_line_length[1] = 0;
		fconvb_line_length[1] = 0;
		fconva_line_length[2] = 0;
		fconvb_line_length[2] = 0;
		fconva_lines[0] = priv.fconva_in_yres;
		fconvb_lines[0] = priv.fconvb_in_yres;
		fconva_lines[1] = 0;
		fconvb_lines[1] = 0;
		fconva_lines[2] = 0;
		fconvb_lines[2] = 0;
		break;
	case 2:	/* ARGB1555 */
		priv.fconva_format = priv.fconvb_format = ARGB16_ARGB1555;
		priv.fconva_bpp = priv.fconvb_bpp = 16;
		fconva_plane_order = fconvb_plane_order = 0;
		fconva_line_length[0] = priv.fconva_in_xres * (priv.fconva_bpp / 8);
		fconvb_line_length[0] = priv.fconvb_in_xres * (priv.fconvb_bpp / 8);
		fconva_line_length[1] = 0;
		fconvb_line_length[1] = 0;
		fconva_line_length[2] = 0;
		fconvb_line_length[2] = 0;
		fconva_lines[0] = priv.fconva_in_yres;
		fconvb_lines[0] = priv.fconvb_in_yres;
		fconva_lines[1] = 0;
		fconvb_lines[1] = 0;
		fconva_lines[2] = 0;
		fconvb_lines[2] = 0;
		break;
	case 3:	/* NV12 */
		priv.fconva_format = priv.fconvb_format = YCbCr420_Y8_Cb8Cr8;
		priv.fconva_bpp = priv.fconvb_bpp = 12;
		fconva_plane_order = fconvb_plane_order = 0;
		fconva_line_length[0] = priv.fconva_in_xres;
		fconvb_line_length[0] = priv.fconvb_in_xres;
		fconva_line_length[1] = priv.fconva_in_xres;
		fconvb_line_length[1] = priv.fconvb_in_xres;
		fconva_line_length[2] = 0;
		fconvb_line_length[2] = 0;
		fconva_lines[0] = priv.fconva_in_yres;
		fconvb_lines[0] = priv.fconvb_in_yres;
		fconva_lines[1] = priv.fconva_in_yres / 2;
		fconvb_lines[1] = priv.fconvb_in_yres / 2;
		fconva_lines[2] = 0;
		fconvb_lines[2] = 0;
		break;
	case 4:	/* YV12 */
		priv.fconva_format = priv.fconvb_format = YCbCr420_Y8_Cb8_Cr8;
		priv.fconva_bpp = priv.fconvb_bpp = 12;
		fconva_plane_order = fconvb_plane_order = 1;
		fconva_line_length[0] = priv.fconva_in_xres;
		fconvb_line_length[0] = priv.fconvb_in_xres;
		fconva_line_length[1] = priv.fconva_in_xres / 2;
		fconvb_line_length[1] = priv.fconvb_in_xres / 2;
		fconva_line_length[2] = priv.fconva_in_xres / 2;
		fconvb_line_length[2] = priv.fconvb_in_xres / 2;
		fconva_lines[0] = priv.fconva_in_yres;
		fconvb_lines[0] = priv.fconvb_in_yres;
		fconva_lines[1] = priv.fconva_in_yres / 2;
		fconvb_lines[1] = priv.fconvb_in_yres / 2;
		fconva_lines[2] = priv.fconva_in_yres / 2;
		fconvb_lines[2] = priv.fconvb_in_yres / 2;
		break;
	case 5:	/* I420 */
		priv.fconva_format = priv.fconvb_format = YCbCr420_Y8_Cb8_Cr8;
		priv.fconva_bpp = priv.fconvb_bpp = 12;
		fconva_plane_order = fconvb_plane_order = 0;
		fconva_line_length[0] = priv.fconva_in_xres;
		fconvb_line_length[0] = priv.fconvb_in_xres;
		fconva_line_length[1] = priv.fconva_in_xres / 2;
		fconvb_line_length[1] = priv.fconvb_in_xres / 2;
		fconva_line_length[2] = priv.fconva_in_xres / 2;
		fconvb_line_length[2] = priv.fconvb_in_xres / 2;
		fconva_lines[0] = priv.fconva_in_yres;
		fconvb_lines[0] = priv.fconvb_in_yres;
		fconva_lines[1] = priv.fconva_in_yres / 2;
		fconvb_lines[1] = priv.fconvb_in_yres / 2;
		fconva_lines[2] = priv.fconva_in_yres / 2;
		fconvb_lines[2] = priv.fconvb_in_yres / 2;
		break;
	case 6:	/* 422P */
		priv.fconva_format = priv.fconvb_format = YCbCr422_Y8_Cb8_Cr8;
		priv.fconva_bpp = priv.fconvb_bpp = 16;
		fconva_plane_order = fconvb_plane_order = 0;
		fconva_line_length[0] = priv.fconva_in_xres;
		fconvb_line_length[0] = priv.fconvb_in_xres;
		fconva_line_length[1] = priv.fconva_in_xres / 2;
		fconvb_line_length[1] = priv.fconvb_in_xres / 2;
		fconva_line_length[2] = priv.fconva_in_xres / 2;
		fconvb_line_length[2] = priv.fconvb_in_xres / 2;
		fconva_lines[0] = priv.fconva_in_yres;
		fconvb_lines[0] = priv.fconvb_in_yres;
		fconva_lines[1] = priv.fconva_in_yres;
		fconvb_lines[1] = priv.fconvb_in_yres;
		fconva_lines[2] = priv.fconva_in_yres;
		fconvb_lines[2] = priv.fconvb_in_yres;
		break;
	case 7:	/* YUV444P */
		priv.fconva_format = priv.fconvb_format = YCbCr444_Y8_Cb8_Cr8;
		priv.fconva_bpp = priv.fconvb_bpp = 24;
		fconva_plane_order = fconvb_plane_order = 0;
		fconva_line_length[0] = priv.fconva_in_xres;
		fconvb_line_length[0] = priv.fconvb_in_xres;
		fconva_line_length[1] = priv.fconva_in_xres;
		fconvb_line_length[1] = priv.fconvb_in_xres;
		fconva_line_length[2] = priv.fconva_in_xres;
		fconvb_line_length[2] = priv.fconvb_in_xres;
		fconva_lines[0] = priv.fconva_in_yres;
		fconvb_lines[0] = priv.fconvb_in_yres;
		fconva_lines[1] = priv.fconva_in_yres;
		fconvb_lines[1] = priv.fconvb_in_yres;
		fconva_lines[2] = priv.fconva_in_yres;
		fconvb_lines[2] = priv.fconvb_in_yres;
		break;
	case 8:	/* AYUV444 */
		priv.fconva_format = priv.fconvb_format = YCbCr444_AYCbCr8888;
		priv.fconva_bpp = priv.fconvb_bpp = 32;
		fconva_plane_order = fconvb_plane_order = 0;
		fconva_line_length[0] = priv.fconva_in_xres;
		fconvb_line_length[0] = priv.fconvb_in_xres;
		fconva_line_length[1] = 0;
		fconvb_line_length[1] = 0;
		fconva_line_length[2] = 0;
		fconvb_line_length[2] = 0;
		fconva_lines[0] = priv.fconva_in_yres;
		fconvb_lines[0] = priv.fconvb_in_yres;
		fconva_lines[1] = 0;
		fconvb_lines[1] = 0;
		fconva_lines[2] = 0;
		fconvb_lines[2] = 0;
		break;
	case 9:	/* ABGR8888 */
		priv.fconva_format = priv.fconvb_format = ARGB32_ABGR8888;
		priv.fconva_bpp = priv.fconvb_bpp = 32;
		fconva_plane_order = fconvb_plane_order = 0;
		fconva_line_length[0] = priv.fconva_in_xres * (priv.fconva_bpp / 8);
		fconvb_line_length[0] = priv.fconvb_in_xres * (priv.fconvb_bpp / 8);
		fconva_line_length[1] = 0;
		fconvb_line_length[1] = 0;
		fconva_line_length[2] = 0;
		fconvb_line_length[2] = 0;
		fconva_lines[0] = priv.fconva_in_yres;
		fconvb_lines[0] = priv.fconvb_in_yres;
		fconva_lines[1] = 0;
		fconvb_lines[1] = 0;
		fconva_lines[2] = 0;
		fconvb_lines[2] = 0;
		break;
	case 10:	/* BGR565 */
		priv.fconva_format = priv.fconvb_format = RGB16_BGR565;
		priv.fconva_bpp = priv.fconvb_bpp = 16;
		fconva_plane_order = fconvb_plane_order = 0;
		fconva_line_length[0] = priv.fconva_in_xres * (priv.fconva_bpp / 8);
		fconvb_line_length[0] = priv.fconvb_in_xres * (priv.fconvb_bpp / 8);
		fconva_line_length[1] = 0;
		fconvb_line_length[1] = 0;
		fconva_line_length[2] = 0;
		fconvb_line_length[2] = 0;
		fconva_lines[0] = priv.fconva_in_yres;
		fconvb_lines[0] = priv.fconvb_in_yres;
		fconva_lines[1] = 0;
		fconvb_lines[1] = 0;
		fconva_lines[2] = 0;
		fconvb_lines[2] = 0;
		break;
	case 11:	/* ABGR1555 */
		priv.fconva_format = priv.fconvb_format = ARGB16_ABGR1555;
		priv.fconva_bpp = priv.fconvb_bpp = 16;
		fconva_plane_order = fconvb_plane_order = 0;
		fconva_line_length[0] = priv.fconva_in_xres * (priv.fconva_bpp / 8);
		fconvb_line_length[0] = priv.fconvb_in_xres * (priv.fconvb_bpp / 8);
		fconva_line_length[1] = 0;
		fconvb_line_length[1] = 0;
		fconva_line_length[2] = 0;
		fconvb_line_length[2] = 0;
		fconva_lines[0] = priv.fconva_in_yres;
		fconvb_lines[0] = priv.fconvb_in_yres;
		fconva_lines[1] = 0;
		fconvb_lines[1] = 0;
		fconva_lines[2] = 0;
		fconvb_lines[2] = 0;
		break;
	}
	{
		fconva_is_yuv = (priv.fconva_format & 0x00000003);
		fconvb_is_yuv = (priv.fconvb_format & 0x00000003);

		for (ii = 0; ii < 3; ii++) {
			priv.fconva_line_length[ii] = fconva_line_length[ii];
			priv.fconvb_line_length[ii] = fconvb_line_length[ii];

			priv.fconva_size[ii] = fconva_line_length[ii] * fconva_lines[ii];
			priv.fconvb_size[ii] = fconvb_line_length[ii] * fconvb_lines[ii];

			priv.fconva_size_virtual[ii] = priv.fconva_size[ii] * magnification;
			priv.fconvb_size_virtual[ii] = priv.fconvb_size[ii] * magnification;
		}

		if (fconva_plane_order == 1) {
			priv.fconva_baseaddr[0] = priv.fconva_in_base;
			priv.fconva_baseaddr[2] = priv.fconva_baseaddr[0] + priv.fconva_size_virtual[0];
			priv.fconva_baseaddr[1] = priv.fconva_baseaddr[2] + priv.fconva_size_virtual[2];

			priv.fconvb_baseaddr[0] = priv.fconvb_in_base;
			priv.fconvb_baseaddr[2] = priv.fconvb_baseaddr[0] + priv.fconvb_size_virtual[0];
			priv.fconvb_baseaddr[1] = priv.fconvb_baseaddr[2] + priv.fconvb_size_virtual[2];
		} else {
			priv.fconva_baseaddr[0] = priv.fconva_in_base;
			priv.fconva_baseaddr[1] = priv.fconva_baseaddr[0] + priv.fconva_size_virtual[0];
			priv.fconva_baseaddr[2] = priv.fconva_baseaddr[1] + priv.fconva_size_virtual[1];

			priv.fconvb_baseaddr[0] = priv.fconvb_in_base;
			priv.fconvb_baseaddr[1] = priv.fconvb_baseaddr[0] + priv.fconvb_size_virtual[0];
			priv.fconvb_baseaddr[2] = priv.fconvb_baseaddr[1] + priv.fconvb_size_virtual[1];
		}

		for (ii = 0; ii < 3; ii++) {
			baseaddr[0][ii] = priv.fconva_baseaddr[ii];
			baseaddr[1][ii] = priv.fconva_baseaddr[ii];
			baseaddr[2][ii] = priv.fconvb_baseaddr[ii];
			baseaddr[3][ii] = priv.fconvb_baseaddr[ii];
		}
	}

	{
		/* */
		dispif_write_reg(regs, DISPIF_FCONVA_SET_SEL_ALPHA_OFFS, sel_alpha);
	}
	{
		/* set ITU-R BT.601 to RGB matrix */
		dispif_write_reg(regs, DISPIF_FCONVA_SET_Y2RMTX_OFFSET_OFFS, 0x00800000);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_Y2RMTX_COEF00_OFFS, 0x00000080);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_Y2RMTX_COEF01_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_Y2RMTX_COEF02_OFFS, 0x000000b3);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_Y2RMTX_COEF10_OFFS, 0x00000080);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_Y2RMTX_COEF11_OFFS, 0x000003d4);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_Y2RMTX_COEF12_OFFS, 0x000003a5);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_Y2RMTX_COEF20_OFFS, 0x00000080);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_Y2RMTX_COEF21_OFFS, 0x000000e5);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_Y2RMTX_COEF22_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_RGBLIMIT_OFFS, 0x000000ff);
	}
	{
		/* set RGB to ITU-R BT.601 matrix */
		dispif_write_reg(regs, DISPIF_FCONVA_SET_R2YMTX_OFFSET_OFFS, 0x00800000);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_R2YMTX_COEF00_OFFS, 0x00000026);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_R2YMTX_COEF01_OFFS, 0x0000004b);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_R2YMTX_COEF02_OFFS, 0x0000000e);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_R2YMTX_COEF10_OFFS, 0x000003eb);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_R2YMTX_COEF11_OFFS, 0x000003d6);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_R2YMTX_COEF12_OFFS, 0x00000040);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_R2YMTX_COEF20_OFFS, 0x00000040);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_R2YMTX_COEF21_OFFS, 0x000003cb);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_R2YMTX_COEF22_OFFS, 0x000003f6);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_YLIMIT_OFFS, 0x000000ff);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_CLIMIT_OFFS, 0x000000ff);
	}
	{
		/* set input format*/
		dispif_write_reg(regs, DISPIF_FCONVA_SET_IN_FORMAT0_OFFS, priv.fconva_format);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_IN_HSIZE0_OFFS, priv.fconva_in_xres);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_IN_VSIZE0_OFFS, priv.fconva_in_yres);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_IN_BASEADDR_GY0_OFFS, baseaddr[0][0]);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_IN_BASEADDR_BCB0_OFFS, baseaddr[0][1]);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_IN_BASEADDR_RCR0_OFFS, baseaddr[0][2]);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_IN_PITCH_GY0_OFFS, priv.fconva_line_length[0]);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_IN_PITCH_BCB0_OFFS, priv.fconva_line_length[1]);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_IN_PITCH_RCR0_OFFS, priv.fconva_line_length[2]);

		dispif_write_reg(regs, DISPIF_FCONVA_SET_IN_FORMAT1_OFFS, priv.fconva_format);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_IN_HSIZE1_OFFS, priv.fconva_in_xres);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_IN_VSIZE1_OFFS, priv.fconva_in_yres);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_IN_BASEADDR_GY1_OFFS, baseaddr[1][0]);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_IN_BASEADDR_BCB1_OFFS, baseaddr[1][1]);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_IN_BASEADDR_RCR1_OFFS, baseaddr[1][2]);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_IN_PITCH_GY1_OFFS, priv.fconva_line_length[0]);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_IN_PITCH_BCB1_OFFS, priv.fconva_line_length[1]);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_IN_PITCH_RCR1_OFFS, priv.fconva_line_length[2]);
#if 0
		dispif_write_reg(regs, 0x1268, 0x00000000);
		dispif_write_reg(regs, 0x126c, 0x00000000);
		dispif_write_reg(regs, 0x1270, 0x00010000);
		dispif_write_reg(regs, 0x1274, 0x00010000);
		dispif_write_reg(regs, 0x1278, 0x00000000);
		dispif_write_reg(regs, 0x127c, 0x00000000);
#endif
	}
	{
		/* set output format*/
		dispif_write_reg(regs, DISPIF_FCONVA_SET_OUT_FORMAT0_OFFS, ARGB32_ARGB8888);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_OUT_HSIZE0_OFFS, priv.fconva_out_xres);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_OUT_VSIZE0_OFFS, priv.fconva_out_yres);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_OUT_BASEADDR_GY0_OFFS, priv.fconva_out_base);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_OUT_BASEADDR_BCB0_OFFS, priv.fconva_out_base);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_OUT_BASEADDR_RCR0_OFFS, priv.fconva_out_base);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_OUT_PITCH_GY0_OFFS, priv.fconva_out_xres * sizeof(u32));
		dispif_write_reg(regs, DISPIF_FCONVA_SET_OUT_PITCH_BCB0_OFFS, priv.fconva_out_xres * sizeof(u32));
		dispif_write_reg(regs, DISPIF_FCONVA_SET_OUT_PITCH_RCR0_OFFS, priv.fconva_out_xres * sizeof(u32));
		dispif_write_reg(regs, DISPIF_FCONVA_SET_FORCE_MODE0_OFFS, 0x00000000);
		if (fconva_is_yuv) {
			dispif_write_reg(regs, DISPIF_FCONVA_SET_FORCE_GY0_OFFS, 0x00000000);
			dispif_write_reg(regs, DISPIF_FCONVA_SET_FORCE_BCB0_OFFS, 0x00000080);
			dispif_write_reg(regs, DISPIF_FCONVA_SET_FORCE_RCR0_OFFS, 0x00000080);
		} else {
			dispif_write_reg(regs, DISPIF_FCONVA_SET_FORCE_GY0_OFFS, 0x00000000);
			dispif_write_reg(regs, DISPIF_FCONVA_SET_FORCE_BCB0_OFFS, 0x00000000);
			dispif_write_reg(regs, DISPIF_FCONVA_SET_FORCE_RCR0_OFFS, 0x00000000);
		}
		dispif_write_reg(regs, DISPIF_FCONVA_SET_FORCE_A0_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_CROP0_OFFS, 0x00000000);

		dispif_write_reg(regs, DISPIF_FCONVA_SET_OUT_FORMAT1_OFFS, ARGB32_ARGB8888);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_OUT_HSIZE1_OFFS, priv.fconva_out_xres);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_OUT_VSIZE1_OFFS, priv.fconva_out_yres);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_OUT_BASEADDR_GY1_OFFS, priv.fconva_out_base);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_OUT_BASEADDR_BCB1_OFFS, priv.fconva_out_base);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_OUT_BASEADDR_RCR1_OFFS, priv.fconva_out_base);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_OUT_PITCH_GY1_OFFS, priv.fconva_out_xres * sizeof(u32));
		dispif_write_reg(regs, DISPIF_FCONVA_SET_OUT_PITCH_BCB1_OFFS, priv.fconva_out_xres * sizeof(u32));
		dispif_write_reg(regs, DISPIF_FCONVA_SET_OUT_PITCH_RCR1_OFFS, priv.fconva_out_xres * sizeof(u32));
#if 0
		dispif_write_reg(regs, 0x1368, 0x00000000);
		dispif_write_reg(regs, 0x136c, 0x00000000);
		dispif_write_reg(regs, 0x1370, 0x00010000);
		dispif_write_reg(regs, 0x1374, 0x00010000);
		dispif_write_reg(regs, 0x1378, 0x00000000);
		dispif_write_reg(regs, 0x137c, 0x00000000);
#endif
		dispif_write_reg(regs, DISPIF_FCONVA_SET_FORCE_MODE1_OFFS, 0x00000000);
		if (fconva_is_yuv) {
			dispif_write_reg(regs, DISPIF_FCONVA_SET_FORCE_GY1_OFFS, 0x00000000);
			dispif_write_reg(regs, DISPIF_FCONVA_SET_FORCE_BCB1_OFFS, 0x00000080);
			dispif_write_reg(regs, DISPIF_FCONVA_SET_FORCE_RCR1_OFFS, 0x00000080);
		} else {
			dispif_write_reg(regs, DISPIF_FCONVA_SET_FORCE_GY1_OFFS, 0x00000000);
			dispif_write_reg(regs, DISPIF_FCONVA_SET_FORCE_BCB1_OFFS, 0x00000000);
			dispif_write_reg(regs, DISPIF_FCONVA_SET_FORCE_RCR1_OFFS, 0x00000000);
		}
		dispif_write_reg(regs, DISPIF_FCONVA_SET_FORCE_A1_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_FCONVA_SET_CROP1_OFFS, 0x00000000);
	}
	{
		/* */
		dispif_write_reg(regs, DISPIF_FCONVB_SET_SEL_ALPHA_OFFS, sel_alpha);
	}
	{
		/* set ITU-R BT.601 to RGB matrix */
		dispif_write_reg(regs, DISPIF_FCONVB_SET_Y2RMTX_OFFSET_OFFS, 0x00800000);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_Y2RMTX_COEF00_OFFS, 0x00000080);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_Y2RMTX_COEF01_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_Y2RMTX_COEF02_OFFS, 0x000000b3);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_Y2RMTX_COEF10_OFFS, 0x00000080);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_Y2RMTX_COEF11_OFFS, 0x000003d4);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_Y2RMTX_COEF12_OFFS, 0x000003a5);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_Y2RMTX_COEF20_OFFS, 0x00000080);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_Y2RMTX_COEF21_OFFS, 0x000000e5);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_Y2RMTX_COEF22_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_RGBLIMIT_OFFS, 0x000000ff);
	}
	{
		/* set RGB to ITU-R BT.601 matrix */
		dispif_write_reg(regs, DISPIF_FCONVB_SET_R2YMTX_OFFSET_OFFS, 0x00800000);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_R2YMTX_COEF00_OFFS, 0x00000026);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_R2YMTX_COEF01_OFFS, 0x0000004b);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_R2YMTX_COEF02_OFFS, 0x0000000e);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_R2YMTX_COEF10_OFFS, 0x000003eb);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_R2YMTX_COEF11_OFFS, 0x000003d6);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_R2YMTX_COEF12_OFFS, 0x00000040);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_R2YMTX_COEF20_OFFS, 0x00000040);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_R2YMTX_COEF21_OFFS, 0x000003cb);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_R2YMTX_COEF22_OFFS, 0x000003f6);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_YLIMIT_OFFS, 0x000000ff);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_CLIMIT_OFFS, 0x000000ff);
	}
	{
		/* set input format*/
		dispif_write_reg(regs, DISPIF_FCONVB_SET_IN_FORMAT0_OFFS, priv.fconvb_format);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_IN_HSIZE0_OFFS, priv.fconvb_in_xres);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_IN_VSIZE0_OFFS, priv.fconvb_in_yres);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_IN_BASEADDR_GY0_OFFS, baseaddr[2][0]);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_IN_BASEADDR_BCB0_OFFS, baseaddr[2][1]);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_IN_BASEADDR_RCR0_OFFS, baseaddr[2][2]);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_IN_PITCH_GY0_OFFS, priv.fconvb_line_length[0]);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_IN_PITCH_BCB0_OFFS, priv.fconvb_line_length[1]);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_IN_PITCH_RCR0_OFFS, priv.fconvb_line_length[2]);

		dispif_write_reg(regs, DISPIF_FCONVB_SET_IN_FORMAT1_OFFS, priv.fconvb_format);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_IN_HSIZE1_OFFS, priv.fconvb_in_xres);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_IN_VSIZE1_OFFS, priv.fconvb_in_yres);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_IN_BASEADDR_GY1_OFFS, baseaddr[3][0]);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_IN_BASEADDR_BCB1_OFFS, baseaddr[3][1]);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_IN_BASEADDR_RCR1_OFFS, baseaddr[3][2]);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_IN_PITCH_GY1_OFFS, priv.fconvb_line_length[0]);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_IN_PITCH_BCB1_OFFS, priv.fconvb_line_length[1]);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_IN_PITCH_RCR1_OFFS, priv.fconvb_line_length[2]);
#if 0
		dispif_write_reg(regs, 0x2268, 0x00000000);
		dispif_write_reg(regs, 0x226c, 0x00000000);
		dispif_write_reg(regs, 0x2270, 0x00010000);
		dispif_write_reg(regs, 0x2274, 0x00010000);
		dispif_write_reg(regs, 0x2278, 0x00000000);
		dispif_write_reg(regs, 0x227c, 0x00000000);
#endif
	}
	{
		/* set output format*/
		dispif_write_reg(regs, DISPIF_FCONVB_SET_OUT_FORMAT0_OFFS, ARGB32_ARGB8888);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_OUT_HSIZE0_OFFS, priv.fconvb_out_xres);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_OUT_VSIZE0_OFFS, priv.fconvb_out_yres);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_OUT_BASEADDR_GY0_OFFS, priv.fconvb_out_base);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_OUT_BASEADDR_BCB0_OFFS, priv.fconvb_out_base);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_OUT_BASEADDR_RCR0_OFFS, priv.fconvb_out_base);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_OUT_PITCH_GY0_OFFS, priv.fconvb_out_xres * sizeof(u32));
		dispif_write_reg(regs, DISPIF_FCONVB_SET_OUT_PITCH_BCB0_OFFS, priv.fconvb_out_xres * sizeof(u32));
		dispif_write_reg(regs, DISPIF_FCONVB_SET_OUT_PITCH_RCR0_OFFS, priv.fconvb_out_xres * sizeof(u32));
		dispif_write_reg(regs, DISPIF_FCONVB_SET_FORCE_MODE0_OFFS, 0x00000000);
		if (fconvb_is_yuv) {
			dispif_write_reg(regs, DISPIF_FCONVB_SET_FORCE_GY0_OFFS, 0x00000000);
			dispif_write_reg(regs, DISPIF_FCONVB_SET_FORCE_BCB0_OFFS, 0x00000080);
			dispif_write_reg(regs, DISPIF_FCONVB_SET_FORCE_RCR0_OFFS, 0x00000080);
		} else {
			dispif_write_reg(regs, DISPIF_FCONVB_SET_FORCE_GY0_OFFS, 0x00000000);
			dispif_write_reg(regs, DISPIF_FCONVB_SET_FORCE_BCB0_OFFS, 0x00000000);
			dispif_write_reg(regs, DISPIF_FCONVB_SET_FORCE_RCR0_OFFS, 0x00000000);
		}
		dispif_write_reg(regs, DISPIF_FCONVB_SET_FORCE_A0_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_CROP0_OFFS, 0x00000000);

		dispif_write_reg(regs, DISPIF_FCONVB_SET_OUT_FORMAT1_OFFS, ARGB32_ARGB8888);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_OUT_HSIZE1_OFFS, priv.fconvb_out_xres);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_OUT_VSIZE1_OFFS, priv.fconvb_out_yres);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_OUT_BASEADDR_GY1_OFFS, priv.fconvb_out_base);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_OUT_BASEADDR_BCB1_OFFS, priv.fconvb_out_base);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_OUT_BASEADDR_RCR1_OFFS, priv.fconvb_out_base);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_OUT_PITCH_GY1_OFFS, priv.fconvb_out_xres * sizeof(u32));
		dispif_write_reg(regs, DISPIF_FCONVB_SET_OUT_PITCH_BCB1_OFFS, priv.fconvb_out_xres * sizeof(u32));
		dispif_write_reg(regs, DISPIF_FCONVB_SET_OUT_PITCH_RCR1_OFFS, priv.fconvb_out_xres * sizeof(u32));
#if 0
		dispif_write_reg(regs, 0x2368, 0x00000000);
		dispif_write_reg(regs, 0x236c, 0x00000000);
		dispif_write_reg(regs, 0x2370, 0x00010000);
		dispif_write_reg(regs, 0x2374, 0x00010000);
		dispif_write_reg(regs, 0x2378, 0x00000000);
		dispif_write_reg(regs, 0x237c, 0x00000000);
#endif
		dispif_write_reg(regs, DISPIF_FCONVB_SET_FORCE_MODE1_OFFS, 0x00000000);
		if (fconvb_is_yuv) {
			dispif_write_reg(regs, DISPIF_FCONVB_SET_FORCE_GY1_OFFS, 0x00000000);
			dispif_write_reg(regs, DISPIF_FCONVB_SET_FORCE_BCB1_OFFS, 0x00000080);
			dispif_write_reg(regs, DISPIF_FCONVB_SET_FORCE_RCR1_OFFS, 0x00000080);
		} else {
			dispif_write_reg(regs, DISPIF_FCONVB_SET_FORCE_GY1_OFFS, 0x00000000);
			dispif_write_reg(regs, DISPIF_FCONVB_SET_FORCE_BCB1_OFFS, 0x00000000);
			dispif_write_reg(regs, DISPIF_FCONVB_SET_FORCE_RCR1_OFFS, 0x00000000);
		}
		dispif_write_reg(regs, DISPIF_FCONVB_SET_FORCE_A1_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_CROP1_OFFS, 0x00000000);
	}
	{
		dispif_write_reg(regs, DISPIF_FCONVC_ACT_OFFS, 0x00000001);
		dispif_write_reg(regs, DISPIF_FCONVC_SETTING_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_FCONVC_KICKA_CHANNEL_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_FCONVC_KICKA_TB_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_FCONVC_KICKB_CHANNEL_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_FCONVC_KICKB_TB_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_FCONVC_MGSETTING_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_FCONVC_DSIERRFIXVAL_OFFS, 0x00000000);
	}
	{
		dispif_write_reg(regs, DISPIF_FCONVA_SET_IRQ_MASK_OFFS, 0x000000d1);
		dispif_write_reg(regs, DISPIF_FCONVB_SET_IRQ_MASK_OFFS, 0x000000d1);
		dispif_write_reg(regs, DISPIF_FCONVA_IRQ_OFFS, 0x00000000);
		dispif_write_reg(regs, DISPIF_FCONVB_IRQ_OFFS, 0x00000000);
	}

	return 0;
}

static int dispif_setup(void)
{
	unsigned int ii;

	priv.fconva_channel = 0;
	priv.fconvb_channel = 0;
	priv.fconva_flip = 0;
	priv.fconvb_flip = 0;
	for (ii = 0; ii < 3; ii++)
		priv.fconva_pan_offset[ii] = 0;

#ifdef CONFIG_FB_TZ3000_USE_D2DP
	d2dp_reset();
#endif /* CONFIG_FB_TZ3000_USE_D2DP */
#ifdef CONFIG_FB_TZ3000_USE_D2DPI
	d2dpi_reset();
#endif /* CONFIG_FB_TZ3000_USE_D2DPI */

	dispif_control_pmu(priv.pmu_regs, cgate_off);

	dispif_set_pll(priv.dispif_regs, fb_mode);
	mdelay(1);
	dispif_control_cgate(priv.dispif_regs, cgate_off);
	dispif_set_dphy(priv.dispif_regs, fb_mode);

#ifdef CONFIG_FB_TZ3000_USE_D2DP
	d2dp_init(fb_mode);
#endif /* CONFIG_FB_TZ3000_USE_D2DP */
#ifdef CONFIG_FB_TZ3000_USE_D2DPI
	d2dpi_init(fb_mode);
#endif /* CONFIG_FB_TZ3000_USE_D2DPI */

	dispif_set_ppi(priv.dispif_regs, fb_mode);
	dispif_control_dsi(priv.dispif_regs, dsi_start);
	dispif_control_dsi(priv.dispif_regs, dsi_pause);
	dispif_set_fconv(priv.dispif_regs, fb_mode, xres, yres, pixelformat);
	dispif_control_irq(priv.dispif_regs, irq_stat_clear_all);
	dispif_control_irq(priv.dispif_regs, irq_disable_all);
	dispif_control_dsi(priv.dispif_regs, dsi_int_clear);
	dispif_set_dtg(priv.dispif_regs, fb_mode);
	dispif_control_dsi(priv.dispif_regs, dsi_int_clear);
	dispif_set_dtg(priv.dispif_regs, fb_mode);
	dispif_set_dsi_cq0(priv.dispif_regs, fb_mode);
	dispif_control_dsi(priv.dispif_regs, dsi_continue);
	mdelay(2);
	dispif_control_dtg(priv.dispif_regs, dtg_start);

	return 0;
}

static void dispif_cleanup(void)
{
	dispif_control_dtg(priv.dispif_regs, dtg_stop);
	mdelay(2);
	dispif_control_dsi(priv.dispif_regs, dsi_reset);
	dispif_control_irq(priv.dispif_regs, irq_stat_clear_all);
	dispif_control_irq(priv.dispif_regs, irq_disable_all);
	dispif_control_dsi(priv.dispif_regs, dsi_int_clear);
	dispif_set_dphy(priv.dispif_regs, 0);
	dispif_control_cgate(priv.dispif_regs, cgate_on);
	mdelay(1);

	dispif_control_pmu(priv.pmu_regs, cgate_on);

#ifdef CONFIG_FB_TZ3000_USE_D2DPI
	d2dpi_reset();
#endif /* CONFIG_FB_TZ3000_USE_D2DPI */
#ifdef CONFIG_FB_TZ3000_USE_D2DP
	d2dp_reset();
#endif /* CONFIG_FB_TZ3000_USE_D2DP */
}

static struct fb_var_screeninfo tz3000fb_default __devinitdata = {
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
	.sync =		FB_SYNC_VERT_HIGH_ACT,
	.vmode =	FB_VMODE_NONINTERLACED,
	.rotate =	0,
	.colorspace =	V4L2_COLORSPACE_SRGB,
};

static struct fb_videomode modedb[] __devinitdata = {
	{
		NULL, 60,  720,  480, 37037,  60,  16,  30, 9,  62, 6,
		0,
		FB_VMODE_NONINTERLACED,
		0
	}, {
		NULL, 60,  800,  600, 25000,  88,  40,  23, 1, 128, 4,
		FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED,
		0
	}, {
#if defined(DISPIF_1280X720_50HZ)
		NULL, 50, 1280,  720, 13468, 220, 440,  20, 5,  40, 5,
		FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED,
		0
	}, {
#elif defined(DISPIF_1280X720_60HZ)
		NULL, 60, 1280,  720, 13468, 220, 110,  20, 5,  40, 5,
		FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED,
		0
	}, {
#endif /* defined(DISPIF_1280X720_xxHZ) */
		NULL, 30, 1920, 1080, 13468, 148,  88,  36, 4,  44, 5,
		FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED,
		0
	}, {
		NULL, 60, 1920, 1080,  6734, 148,  88,  36, 4,  44, 5,
		FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED,
		0
	}
};

static struct fb_fix_screeninfo tz3000fb_fix __devinitdata = {
	.id =		"TZ3000 DISPIF",
	.type =		FB_TYPE_PACKED_PIXELS,
	.visual =	FB_VISUAL_TRUECOLOR,
	.xpanstep =	1,
	.ypanstep =	(DEFAULT_FB_MAGNIFICATION > 1) ? 1 : 0,
	.ywrapstep =	0,
	.line_length =	(DEFAULT_XRES * (DEFAULT_BPP / 8)),
	.accel =	FB_ACCEL_NONE,
	.capabilities = FB_CAP_FOURCC,
};

static int tz3000fb_check_var(struct fb_var_screeninfo *var,
			      struct fb_info *info);
static int tz3000fb_set_par(struct fb_info *info);
static int tz3000fb_setcolreg(u_int regno, u_int red, u_int green, u_int blue,
			      u_int transp, struct fb_info *info);
static int tz3000fb_pan_display(struct fb_var_screeninfo *var,
				struct fb_info *info);
static int tz3000fb_mmap(struct fb_info *info,
			 struct vm_area_struct *vma);
static int tz3000fb_ioctl(struct fb_info *info,
			  unsigned int cmd,
			  unsigned long arg);

static struct fb_ops tz3000fb_ops = {
	.owner		= THIS_MODULE,
	.fb_read        = fb_sys_read,
	.fb_write       = fb_sys_write,
	.fb_check_var	= tz3000fb_check_var,
	.fb_set_par	= tz3000fb_set_par,
	.fb_setcolreg	= tz3000fb_setcolreg,
	.fb_pan_display	= tz3000fb_pan_display,
	.fb_fillrect	= sys_fillrect,
	.fb_copyarea	= sys_copyarea,
	.fb_imageblit	= sys_imageblit,
	.fb_mmap	= tz3000fb_mmap,
	.fb_ioctl	= tz3000fb_ioctl,
};

    /*
     *  Internal routines
     */
static int tz3000fb_wait_for_vsync(void)
{
	int ret;
	u32 irq_en = dispif_read_reg(priv.dispif_regs, DISPIF_IRQ_EN_OFFS);

	/* Enable VSync End interrupt and be careful not to acknowledge any
	 * pending interrupt.
	 */
	irq_en |= 0x01000000; /* enable vsync_en */
	dispif_write_reg(priv.dispif_regs, DISPIF_IRQ_EN_OFFS, irq_en);

	ret = wait_for_completion_interruptible_timeout(&priv.vsync_completion,
							msecs_to_jiffies(100));
	if (!ret)
		return -ETIMEDOUT;

	return 0;
}

static int tz3000fb_wait_for_frame_end(unsigned int fconv)
{
	int ret;
	u32 fconva_irq_mask = dispif_read_reg(priv.dispif_regs, DISPIF_FCONVA_SET_IRQ_MASK_OFFS);
	u32 fconvb_irq_mask = dispif_read_reg(priv.dispif_regs, DISPIF_FCONVB_SET_IRQ_MASK_OFFS);

	/* Enable Frame End interrupt and be careful not to acknowledge any
	 * pending interrupt.
	 */
	switch (fconv) {
	case fconva:
		fconva_irq_mask &= ~0x00000001; /* enable frame_end_mask */
		dispif_write_reg(priv.dispif_regs, DISPIF_FCONVA_SET_IRQ_MASK_OFFS, fconva_irq_mask);

		ret = wait_for_completion_interruptible_timeout(&priv.fconva_frame_end_completion,
								msecs_to_jiffies(100));
		if (!ret)
			return -ETIMEDOUT;
		break;
	case fconvb:
		fconva_irq_mask &= ~0x00000001; /* enable frame_end_mask */
		dispif_write_reg(priv.dispif_regs, DISPIF_FCONVB_SET_IRQ_MASK_OFFS, fconvb_irq_mask);

		ret = wait_for_completion_interruptible_timeout(&priv.fconvb_frame_end_completion,
								msecs_to_jiffies(100));
		if (!ret)
			return -ETIMEDOUT;
		break;
	}

	return 0;
}

static irqreturn_t tz3000fb_dispif_intr(int irq, void *data)
{
	unsigned long flag;
	u32 irq_stat  = dispif_read_reg(priv.dispif_regs, DISPIF_IRQ_STAT_OFFS);
	u32 irq_en    = dispif_read_reg(priv.dispif_regs, DISPIF_IRQ_EN_OFFS);
	u32 irq_clear = (irq_stat & irq_en);
	u32 dsi_int   = dispif_read_reg(priv.dispif_regs, DISPIF_DSI_INT_OFFS);
	u32 dsi_clear = (dsi_int & 0xffffffff);

	spin_lock_irqsave(&priv.dispif_slock, flag);

	dispif_write_reg(priv.dispif_regs, DISPIF_IRQ_STAT_OFFS, irq_clear);
	dispif_write_reg(priv.dispif_regs, DISPIF_DSI_INT_CLR_OFFS, dsi_clear);

	if (irq_stat & 0x01000000)
		complete(&priv.vsync_completion);

	spin_unlock_irqrestore(&priv.dispif_slock, flag);

	return IRQ_HANDLED;
}

static irqreturn_t tz3000fb_dispif_errintr(int irq, void *data)
{
	unsigned long flag;
	u32 fconva_irq = dispif_read_reg(priv.dispif_regs, DISPIF_FCONVA_IRQ_OFFS);
	u32 fconvb_irq = dispif_read_reg(priv.dispif_regs, DISPIF_FCONVB_IRQ_OFFS);

	spin_lock_irqsave(&priv.dispif_slock, flag);

	dispif_write_reg(priv.dispif_regs, DISPIF_FCONVA_IRQ_OFFS, 0x000000f1);
	dispif_write_reg(priv.dispif_regs, DISPIF_FCONVB_IRQ_OFFS, 0x000000f1);

	if (fconva_irq & 0x00000010)
		pr_err("fconva: START_ERROR_IRQ\n");
	if (fconva_irq & 0x00000020)
		pr_err("fconva: REG_ERROR_IRQ\n");
	if (fconva_irq & 0x00000040)
		pr_err("fconva: DISP_ERROR_IRQ\n");
	if (fconva_irq & 0x00000080)
		pr_err("fconva: MERGE_ERROR_IRQ\n");

	if (fconvb_irq & 0x00000010)
		pr_err("fconvb: START_ERROR_IRQ\n");
	if (fconvb_irq & 0x00000020)
		pr_err("fconvb: REG_ERROR_IRQ\n");
	if (fconvb_irq & 0x00000040)
		pr_err("fconvb: DISP_ERROR_IRQ\n");
	if (fconvb_irq & 0x00000080)
		pr_err("fconvb: MERGE_ERROR_IRQ\n");

	if (fconva_irq & 0x00000001) {
		if (priv.fconva_flip) {
			if (priv.fconva_channel == 0) {
				/* select channel 1 */
				priv.fconva_channel = 1;
			} else {
				/* select channel 0 */
				priv.fconva_channel = 0;
			}
			priv.fconva_flip--;
		}
		complete(&priv.fconva_frame_end_completion);
	}
	if (fconvb_irq & 0x00000001)
		complete(&priv.fconvb_frame_end_completion);

	spin_unlock_irqrestore(&priv.dispif_slock, flag);

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

static int tz3000fb_check_var(struct fb_var_screeninfo *var,
			      struct fb_info *info)
{
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

	if (var->grayscale > 1) {
		switch (var->grayscale) {
		case V4L2_PIX_FMT_RGB32:
			var->bits_per_pixel = 32;
			break;
		case V4L2_PIX_FMT_RGB565:	/* RGB16_RGB565 */
			var->bits_per_pixel = 16;
			break;
		case V4L2_PIX_FMT_RGB555:	/* ARGB16_ARGB1555 */
			var->bits_per_pixel = 16;
			break;
		case V4L2_PIX_FMT_YUV32:	/* YCbCr444_AYCbCr8888 (YUV4) */
			var->bits_per_pixel = 32;
			break;
		case V4L2_PIX_FMT_YUV444P:	/* YCbCr444_Y8_Cb8_Cr8 (444P) */
			var->bits_per_pixel = 24;
			break;
		case V4L2_PIX_FMT_YUV422P:	/* YCbCr422_Y8_Cb8_Cr8 (422P) */
			var->bits_per_pixel = 16;
			break;
		case V4L2_PIX_FMT_NV12:		/* YCbCr420_Y8_Cb8Cr8 (NV12) */
			var->bits_per_pixel = 12;
			break;
		case V4L2_PIX_FMT_YVU420:	/* YCbCr420_Y8_Cb8_Cr8 (YV12) */
			var->bits_per_pixel = 12;
			break;
		case V4L2_PIX_FMT_YUV420:	/* YCbCr420_Y8_Cb8_Cr8 (I420) */
			var->bits_per_pixel = 12;
			break;
		default:
			return -EINVAL;
		}
	} else {
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
	}

#if 0
	if (var->yres <= 480) {
		var->xres = 720;
		var->yres = 480;
		var->xres_virtual = 720;
		var->yres_virtual = 480 * magnification;
	} else if (var->yres <= 600) {
		var->xres = 800;
		var->yres = 600;
		var->xres_virtual = 800;
		var->yres_virtual = 600 * magnification;
	} else if (var->yres <= 720) {
		var->xres = 1280;
		var->yres = 720;
		var->xres_virtual = 1280;
		var->yres_virtual = 720 * magnification;
	} else if (var->yres <= 1080) {
		var->xres = 1920;
		var->yres = 1080;
		var->xres_virtual = 1920;
		var->yres_virtual = 1080 * magnification;
	} else
		return -EINVAL;

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
	if (line_length * var->yres_virtual > priv.fconva_in_size)
		return -ENOMEM;

	/*
	 * Now that we checked it we alter var. The reason being is that the video
	 * mode passed in might not work but slight changes to it might make it
	 * work. This way we let the user know what is acceptable.
	 */
	if (var->grayscale > 1)
		set_rgba(var, 0, 0, 0, 0, 0, 0, 0, 0);
	else {
		switch (var->bits_per_pixel) {
		case 16:
			if (var->green.length == 5) {
				if (var->red.offset) {
					/* ARGB 1555 */
#ifdef STRICT_COLOR_CHECK
					if (var->red.offset    != 10 || var->red.length    !=  5 ||
					    var->green.offset  !=  5 || var->green.length  !=  5 ||
					    var->blue.offset   !=  0 || var->blue.length   !=  5)
						return -EINVAL;
#endif /* STRICT_COLOR_CHECK */
					if (var->transp.length)
						set_rgba(var, 10, 5, 5, 5, 0, 5, 15, 1);
					else
						set_rgba(var, 10, 5, 5, 5, 0, 5, 0, 0);
				} else {
					/* ABGR 1555 */
#ifdef STRICT_COLOR_CHECK
					if (var->red.offset    !=  0 || var->red.length    !=  5 ||
					    var->green.offset  !=  5 || var->green.length  !=  5 ||
					    var->blue.offset   != 10 || var->blue.length   !=  5)
						return -EINVAL;
#endif /* STRICT_COLOR_CHECK */
					if (var->transp.length)
						set_rgba(var, 0, 5, 5, 5, 10, 5, 15, 1);
					else
						set_rgba(var, 0, 5, 5, 5, 10, 5, 0, 0);
				}
			} else {
				if (var->red.offset) {
					/* RGB 565 */
#ifdef STRICT_COLOR_CHECK
					if (var->red.offset    != 11 || var->red.length    != 5 ||
					    var->green.offset  !=  5 || var->green.length  != 6 ||
					    var->blue.offset   !=  0 || var->blue.length   != 5 ||
									var->transp.length != 0)
						return -EINVAL;
#endif /* STRICT_COLOR_CHECK */
					set_rgba(var, 11, 5, 5, 6, 0, 5, 0, 0);
				} else {
					/* BGR 565 */
#ifdef STRICT_COLOR_CHECK
					if (var->red.offset    !=  0 || var->red.length    != 5 ||
					    var->green.offset  !=  5 || var->green.length  != 6 ||
					    var->blue.offset   != 11 || var->blue.length   != 5 ||
									var->transp.length != 0)
						return -EINVAL;
#endif /* STRICT_COLOR_CHECK */
					set_rgba(var, 0, 5, 5, 6, 11, 5, 0, 0);
				}
			}
			break;
		case 32:
			if (var->red.offset) {
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
			} else {
				/* ABGR 8888 */
#ifdef STRICT_COLOR_CHECK
				if (var->red.offset    !=  0 || var->red.length    != 8 ||
				    var->green.offset  !=  8 || var->green.length  != 8 ||
				    var->blue.offset   != 16 || var->blue.length   != 8)
					return -EINVAL;
				set_rgba(var, 0, 8, 8, 8, 16, 8, 24, 8);
#else
				if (var->transp.length)
					set_rgba(var, 0, 8, 8, 8, 16, 8, 24, 8);
				else
					set_rgba(var, 0, 8, 8, 8, 16, 8, 0, 0);
#endif /* STRICT_COLOR_CHECK */
			}
			break;
		}
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
static int tz3000fb_set_par(struct fb_info *info)
{
	u32 fconva_is_yuv;

	info->fix.line_length = get_line_length(info->var.xres_virtual,
						info->var.bits_per_pixel);

	dispif_cleanup();

	if (info->var.xres <= 720 && info->var.yres <= 480)
		fb_mode = 1;
	else if (info->var.xres <= 800 && info->var.yres <= 600)
		fb_mode = 2;
	else if (info->var.xres <= 1280 && info->var.yres <= 720)
		fb_mode = 3;
	else if (info->var.xres <= 1920 && info->var.yres <= 1080)
		fb_mode = 4;

	xres = info->var.xres;
	yres = info->var.yres;

	if (info->var.grayscale > 1) {
		info->fix.type = FB_TYPE_FOURCC;
		info->fix.visual = FB_VISUAL_FOURCC;
		switch (info->var.grayscale) {
		case V4L2_PIX_FMT_RGB32:
			pixelformat = 0;	/* ARGB32_ARGB8888 */
			break;
		case V4L2_PIX_FMT_RGB565:	/* RGB16_RGB565 */
			pixelformat = 1;
			break;
		case V4L2_PIX_FMT_RGB555:	/* ARGB16_ARGB1555 */
			pixelformat = 2;
			break;
		case V4L2_PIX_FMT_YUV32:	/* YCbCr444_AYCbCr8888 (YUV4) */
			pixelformat = 8;
			break;
		case V4L2_PIX_FMT_YUV444P:	/* YCbCr444_Y8_Cb8_Cr8 (444P) */
			pixelformat = 7;
			break;
		case V4L2_PIX_FMT_YUV422P:	/* YCbCr422_Y8_Cb8_Cr8 (422P) */
			pixelformat = 6;
			break;
		case V4L2_PIX_FMT_NV12:		/* YCbCr420_Y8_Cb8Cr8 (NV12) */
			pixelformat = 3;
			break;
		case V4L2_PIX_FMT_YVU420:	/* YCbCr420_Y8_Cb8_Cr8 (YV12) */
			pixelformat = 4;
			break;
		case V4L2_PIX_FMT_YUV420:	/* YCbCr420_Y8_Cb8_Cr8 (I420) */
			pixelformat = 5;
			break;
		}
	} else {
		info->fix.type = FB_TYPE_PACKED_PIXELS;
		info->fix.visual = FB_VISUAL_TRUECOLOR;
		if (info->var.bits_per_pixel == 32) {
			if (info->var.red.offset)
				pixelformat = 0;	/* ARGB32_ARGB8888 */
			else
				pixelformat = 9;	/* ARGB32_ABGR8888 */
		} else if (info->var.bits_per_pixel == 16 && info->var.green.length != 5) {
			if (info->var.red.offset)
				pixelformat = 1;	/* RGB16_RGB565 */
			else
				pixelformat = 10;	/* RGB16_BGR565 */
		} else if (info->var.bits_per_pixel == 16 && info->var.green.length == 5) {
			if (info->var.red.offset)
				pixelformat = 2;	/* ARGB16_ARGB1555 */
			else
				pixelformat = 11;	/* ARGB16_ABGR1555 */
		}
	}

	dispif_setup();

	fconva_is_yuv = (priv.fconva_format & 0x00000003);
	switch (fconva_is_yuv) {
	case 1:
		info->fix.ypanstep = (magnification > 1) ? 1 : 0;
		break;
	case 2:
	case 3:
		info->fix.ypanstep = (magnification > 1) ? 2 : 0;
		break;
	default:
		info->fix.ypanstep = (magnification > 1) ? 1 : 0;
		break;
	}

	return 0;
}

    /*
     *  Set a single color register. The values supplied are already
     *  rounded down to the hardware's capabilities (according to the
     *  entries in the var structure). Return != 0 for invalid regno.
     */

static int tz3000fb_setcolreg(u_int regno, u_int red, u_int green, u_int blue,
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

static int tz3000fb_pan_display(struct fb_var_screeninfo *var,
				struct fb_info *info)
{
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
		u32 baseaddr[3];
		u32 fconva_pan_offset[3];
		unsigned int ii;

		switch (priv.fconva_format) {
		case YCbCr420_Y8_Cb8Cr8:
			fconva_pan_offset[0] = (var->yoffset
					* info->var.xres_virtual
					+ var->xoffset);
			fconva_pan_offset[1] = ((var->yoffset / 2)
					* info->var.xres_virtual
					+ var->xoffset);
			fconva_pan_offset[2] = 0;
			break;
		case RGB24_R8_G8_B8:
		case YCbCr444_Y8_Cb8_Cr8:
			fconva_pan_offset[0] =
			fconva_pan_offset[1] =
			fconva_pan_offset[2] = (var->yoffset
					* info->var.xres_virtual
					+ var->xoffset);
			break;
		case YCbCr422_Y8_Cb8_Cr8:
			fconva_pan_offset[0] = (var->yoffset
					* info->var.xres_virtual
					+ var->xoffset);
			fconva_pan_offset[1] =
			fconva_pan_offset[2] = ((var->yoffset / 2)
					* info->var.xres_virtual
					+ var->xoffset);
			break;
		case YCbCr420_Y8_Cb8_Cr8:
			fconva_pan_offset[0] = (var->yoffset
					* info->var.xres_virtual
					+ var->xoffset);
			fconva_pan_offset[1] =
			fconva_pan_offset[2] = ((var->yoffset / 2)
					* (info->var.xres_virtual / 2)
					+ (var->xoffset / 2));
			break;
		default:
			fconva_pan_offset[0] = (var->yoffset
					* info->var.xres_virtual + var->xoffset)
					* info->var.bits_per_pixel / 8;
			fconva_pan_offset[1] = 0;
			fconva_pan_offset[2] = 0;
			break;
		}

		if ((priv.fconva_pan_offset[0] == fconva_pan_offset[0])
			&& (priv.fconva_pan_offset[1] == fconva_pan_offset[1])
			&& (priv.fconva_pan_offset[2] == fconva_pan_offset[2]))
			return 0;

		for (ii = 0; ii < 3; ii++) {
			priv.fconva_pan_offset[ii] = fconva_pan_offset[ii];
			baseaddr[ii] = priv.fconva_baseaddr[ii] + priv.fconva_pan_offset[ii];
		}

		while (priv.fconva_flip > ((info->var.yres_virtual / info->var.yres) - 1)) {
			int ret = tz3000fb_wait_for_frame_end(fconva);
			if (!ret)
				pr_debug("tz3000fb_pan_display() timeout\n");
		}
		if (priv.fconva_channel == 0) {
			/* update baseaddr of channel 1 */
			dispif_write_reg(priv.dispif_regs, DISPIF_FCONVA_SET_IN_BASEADDR_GY1_OFFS, baseaddr[0]);
			dispif_write_reg(priv.dispif_regs, DISPIF_FCONVA_SET_IN_BASEADDR_BCB1_OFFS, baseaddr[1]);
			dispif_write_reg(priv.dispif_regs, DISPIF_FCONVA_SET_IN_BASEADDR_RCR1_OFFS, baseaddr[2]);
			dispif_write_reg(priv.dispif_regs, DISPIF_FCONVC_KICKA_CHANNEL_OFFS, 0x00000001);
		} else {
			/* update baseaddr of channel 0 */
			dispif_write_reg(priv.dispif_regs, DISPIF_FCONVA_SET_IN_BASEADDR_GY0_OFFS, baseaddr[0]);
			dispif_write_reg(priv.dispif_regs, DISPIF_FCONVA_SET_IN_BASEADDR_BCB0_OFFS, baseaddr[1]);
			dispif_write_reg(priv.dispif_regs, DISPIF_FCONVA_SET_IN_BASEADDR_RCR0_OFFS, baseaddr[2]);
			dispif_write_reg(priv.dispif_regs, DISPIF_FCONVC_KICKA_CHANNEL_OFFS, 0x00000000);
		}
		priv.fconva_flip++;
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

static int tz3000fb_mmap(struct fb_info *info,
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

static void tz3000fb_get_vblank(struct fb_vblank *vblank)
{
	memset(vblank, 0, sizeof(*vblank));
	vblank->flags = FB_VBLANK_HAVE_VSYNC;

	return;
}

static int tz3000fb_ioctl(struct fb_info *info, unsigned int cmd,
			  unsigned long arg)
{
	int retval = 0;
	void __user *argp = (void __user *)arg;
	struct fb_vblank vblank;

	switch (cmd) {
	case FBIOGET_VBLANK:
		tz3000fb_get_vblank(&vblank);

		if (copy_to_user(argp, &vblank, sizeof(vblank))) {
			pr_err("copy_to_user()\n");
			retval = -EFAULT;
		}
		break;
	case FBIO_WAITFORVSYNC:
		{
			retval = tz3000fb_wait_for_frame_end(fconva);
			break;
		}
	default:
		retval = -ENOIOCTLCMD;
		break;
	}
	return retval;
}

#ifdef CONFIG_PM
int tz3000fb_hw_start(void)
{
	/* start clock */
	clk_prepare_enable(priv.clk_dispif);

	return 0;
}

int tz3000fb_hw_stop(void)
{
	/* stop clock */
	clk_disable_unprepare(priv.clk_dispif);

	return 0;
}

static int tz3000fb_suspend(struct device *dev)
{
	if (module_refcount(dev->driver->owner->mkobj.mod) > 0)
		return -EBUSY;

	dispif_cleanup();
	tz3000fb_hw_stop();

	return 0;
}

static int tz3000fb_resume(struct device *dev)
{
	tz3000fb_hw_start();
	/* setting of register */
	dispif_cleanup();
	dispif_setup();

	return 0;
}

#endif
int tz3000fb_runtime_suspend(struct device *dev)
{
	/* stop clock */
	clk_disable_unprepare(priv.clk_dispif);

	return 0;
}

int tz3000fb_runtime_resume(struct device *dev)
{
	/* start clock */
	clk_prepare_enable(priv.clk_dispif);

	return 0;
}

#ifndef MODULE
/*
 * The TZ3000 framebuffer driver is only enabled if explicitly
 * requested by passing 'video=tz3000fb:' (or any actual options).
 */
static int __init tz3000fb_setup(char *options)
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

static int __devinit tz3000fb_probe(struct platform_device *pdev)
{
	struct fb_info *info;
	int retval = -ENOMEM;
	struct resource *dispif, *pmu;

	memset(&priv, 0, sizeof(struct tz3000fb_dev));

	priv.dev = &pdev->dev;

	/* Mapping to PMU register */
	pmu = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!pmu) {
		pr_err("dispif platform_get_resource() failed [pmu]\n");
		retval = -ENOENT;
		goto err0;
	}
	priv.pmu_regs = ioremap_nocache(CPU_PMU_REG_BASE, CPU_PMU_REG_SIZE);
	if (!priv.pmu_regs) {
		pr_err("dispif ioremap_nocache failed\n");
		goto err0;
	}

	/* Mapping to LCDC register */
	dispif = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (!dispif) {
		pr_err("dispif platform_get_resource() failed [dispif]\n");
		retval = -ENOENT;
		goto err0;
	}
	priv.dispif_regs = ioremap_nocache(CPU_DISPIF_REG_BASE, CPU_DISPIF_REG_SIZE);
	if (!priv.dispif_regs) {
		pr_err("dispif ioremap_nocache failed\n");
		goto err0;
	}

	if (magnification > MAX_FB_MAGNIFICATION) {
		dev_warn(&pdev->dev, "Illegal magnification %lu. Force set %u\n",
			 magnification, MAX_FB_MAGNIFICATION);
		magnification = MAX_FB_MAGNIFICATION;
	}

	priv.fconva_out_size = PAGE_ALIGN(MAX_FRAME_SIZE);
	priv.fconvb_out_size = PAGE_ALIGN(MAX_FRAME_SIZE);
	priv.fconva_in_size  = PAGE_ALIGN(MAX_FB_SIZE);
	priv.fconvb_in_size  = 0;

	if (priv.fconva_out_size > 0) {
		priv.fconva_out_memory = dma_alloc_coherent(
				NULL,
				priv.fconva_out_size,
				(dma_addr_t *)&priv.fconva_out_base,
				GFP_KERNEL);
		if (!priv.fconva_out_memory)
			goto err1;
	}
	if (priv.fconvb_out_size > 0) {
		priv.fconvb_out_memory = dma_alloc_coherent(
				NULL,
				priv.fconvb_out_size,
				(dma_addr_t *)&priv.fconvb_out_base,
				GFP_KERNEL);
		if (!priv.fconvb_out_memory)
			goto err1;
	}
	if (priv.fconva_in_size > 0) {
		priv.fconva_memory = dma_alloc_coherent(
				NULL,
				priv.fconva_in_size,
				(dma_addr_t *)&priv.fconva_in_base,
				GFP_KERNEL);
		if (!priv.fconva_memory)
			goto err1;
	}
	if (priv.fconvb_in_size > 0) {
		priv.fconvb_memory = dma_alloc_coherent(
				NULL,
				priv.fconvb_in_size,
				(dma_addr_t *)&priv.fconvb_in_base,
				GFP_KERNEL);
		if (!priv.fconvb_memory)
			goto err1;
	}

	/*
	 * VFB must clear memory to prevent kernel info
	 * leakage into userspace
	 * VGA-based drivers MUST NOT clear memory if
	 * they want to be able to take over vgacon
	 */
	if (priv.fconva_in_size > 0)
		memset(priv.fconva_memory, 0, priv.fconva_in_size);
	if (priv.fconvb_in_size > 0)
		memset(priv.fconvb_memory, 0, priv.fconvb_in_size);

	info = framebuffer_alloc(sizeof(u32) * 256, &pdev->dev);
	if (!info)
		goto err1;

	info->screen_base = (char __iomem *)priv.fconva_memory;
	info->fbops = &tz3000fb_ops;

	priv.fconva_in_xres = priv.fconva_out_xres = DEFAULT_XRES;
	priv.fconvb_in_xres = priv.fconvb_out_xres = DEFAULT_XRES;
	priv.fconva_in_yres = priv.fconva_out_yres = DEFAULT_YRES;
	priv.fconvb_in_yres = priv.fconvb_out_yres = DEFAULT_YRES;
	priv.fconva_bpp    = DEFAULT_BPP;
	priv.fconvb_bpp    = DEFAULT_BPP;
	priv.fconva_format = DEFAULT_FORMAT;
	priv.fconvb_format = DEFAULT_FORMAT;

	retval = fb_find_mode(&info->var, info, NULL, modedb,
			      ARRAY_SIZE(modedb), &modedb[1], DEFAULT_BPP);

	if (!retval || (retval == 4))
		info->var = tz3000fb_default;
	tz3000fb_fix.smem_start = (unsigned long)priv.fconva_memory;
	tz3000fb_fix.smem_len = priv.fconva_in_size;
	tz3000fb_fix.ypanstep = (magnification > 1) ? 1 : 0;
	info->fix = tz3000fb_fix;
	info->pseudo_palette = info->par;
	info->par = NULL;
	info->flags = FBINFO_FLAG_DEFAULT;
	switch (fb_mode) {
	case 1:
		xres = info->var.xres = (info->var.xres > 720) ? 720 : info->var.xres;
		yres = info->var.yres = (info->var.yres > 480) ? 480 : info->var.yres;
		break;
	case 2:
		xres = info->var.xres = (info->var.xres > 800) ? 800 : info->var.xres;
		yres = info->var.yres = (info->var.yres > 600) ? 600 : info->var.yres;
		break;
	case 3:
		xres = info->var.xres = (info->var.xres > 1280) ? 1280 : info->var.xres;
		yres = info->var.yres = (info->var.yres > 720) ? 720 : info->var.yres;
		break;
	case 4:
	case 5:
		xres = info->var.xres = (info->var.xres > 1920) ? 1920 : info->var.xres;
		yres = info->var.yres = (info->var.yres > 1080) ? 1080 : info->var.yres;
		break;
	}
	info->var.xres_virtual = info->var.xres;
	info->var.yres_virtual = info->var.yres * magnification;

	retval = fb_alloc_cmap(&info->cmap, 256, 0);
	if (retval < 0)
		goto err2;

	retval = register_framebuffer(info);
	if (retval < 0)
		goto err3;
	platform_set_drvdata(pdev, info);

	spin_lock_init(&priv.dispif_slock);

	retval = request_irq(TZ3000_IRQ_DISPIF_HBLANKININT, tz3000fb_dispif_intr,
			     IRQF_SHARED, tz3000fb_devname, &priv);
	if (retval) {
		dev_err(&pdev->dev, "Unable to register interrupt.\n");
		goto err4_9;
	}
	retval = request_irq(TZ3000_IRQ_DISPIF_VBLANKININT, tz3000fb_dispif_intr,
			     IRQF_SHARED, tz3000fb_devname, &priv);
	if (retval) {
		dev_err(&pdev->dev, "Unable to register interrupt.\n");
		goto err4_8;
	}
	retval = request_irq(TZ3000_IRQ_DISPIF_VBLANKOUTINT, tz3000fb_dispif_intr,
			     IRQF_SHARED, tz3000fb_devname, &priv);
	if (retval) {
		dev_err(&pdev->dev, "Unable to register interrupt.\n");
		goto err4_7;
	}
	retval = request_irq(TZ3000_IRQ_DISPIF_HBLANKININT2, tz3000fb_dispif_intr,
			     IRQF_SHARED, tz3000fb_devname, &priv);
	if (retval) {
		dev_err(&pdev->dev, "Unable to register interrupt.\n");
		goto err4_6;
	}
	retval = request_irq(TZ3000_IRQ_DISPIF_HBLANKININT3, tz3000fb_dispif_intr,
			     IRQF_SHARED, tz3000fb_devname, &priv);
	if (retval) {
		dev_err(&pdev->dev, "Unable to register interrupt.\n");
		goto err4_5;
	}
	retval = request_irq(TZ3000_IRQ_DISPIF_DSIINT, tz3000fb_dispif_intr,
			     IRQF_SHARED, tz3000fb_devname, &priv);
	if (retval) {
		dev_err(&pdev->dev, "Unable to register interrupt.\n");
		goto err4_4;
	}
	retval = request_irq(TZ3000_IRQ_DISPIF_INTFRAME, tz3000fb_dispif_errintr,
			     IRQF_SHARED, tz3000fb_devname, &priv);
	if (retval) {
		dev_err(&pdev->dev, "Unable to register interrupt.\n");
		goto err4_3;
	}
	retval = request_irq(TZ3000_IRQ_DISPIF_INTERR, tz3000fb_dispif_errintr,
			     IRQF_SHARED, tz3000fb_devname, &priv);
	if (retval) {
		dev_err(&pdev->dev, "Unable to register interrupt.\n");
		goto err4_2;
	}
	retval = request_irq(TZ3000_IRQRE_DISPIF_VBLANKINEDGEINT, tz3000fb_dispif_intr,
			     IRQF_SHARED | IRQF_TRIGGER_RISING, tz3000fb_devname, &priv);
	if (retval) {
		dev_err(&pdev->dev, "Unable to register interrupt.\n");
		goto err4_1;
	}
	retval = request_irq(TZ3000_IRQRE_DISPIF_VSYNC, tz3000fb_dispif_intr,
			     IRQF_SHARED | IRQF_TRIGGER_RISING, tz3000fb_devname, &priv);
	if (retval) {
		dev_err(&pdev->dev, "Unable to register interrupt.\n");
		goto err4;
	}

	init_completion(&priv.vsync_completion);
	init_completion(&priv.fconva_frame_end_completion);
	init_completion(&priv.fconvb_frame_end_completion);

	priv.clk_dispif = clk_get(&(pdev->dev), "dispif");
	if (IS_ERR(priv.clk_dispif)) {
		dev_err(&pdev->dev, "clk_get(%s, dispif) failed\n",
					dev_name(&(pdev->dev)));
		retval = -EFAULT;
		goto err5;
	}

#if IS_ENABLED(CONFIG_PM_RUNTIME)
	pm_runtime_enable(&(pdev->dev));

	/* call tz3000fb_runtime_resume() directly */
	pm_runtime_get_sync(&(pdev->dev));

#else
	tz3000fb_runtime_resume(&(pdev->dev));

#endif /* IS_ENABLED(CONFIG_PM_RUNTIME) */
	dispif_cleanup();
	retval = dispif_setup();
	if (retval < 0)
		goto err6;

	pr_info("fb%d: TZ3000 frame buffer device, using %dK of dispif work memory (FCONVA_OUT)\n",
		info->node, PAGE_ALIGN(MAX_FRAME_SIZE) >> 10);
	pr_info("fb%d: TZ3000 frame buffer device, using %dK of dispif work memory (FCONVB_OUT)\n",
		info->node, PAGE_ALIGN(MAX_FRAME_SIZE) >> 10);
	pr_info("fb%d: TZ3000 frame buffer device, using %ldK of video memory (FCONVA_IN)\n",
		info->node, priv.fconva_in_size >> 10);
	pr_info("fb%d: TZ3000 frame buffer device, using %ldK of video memory (FCONVB_IN)\n",
		info->node, priv.fconvb_in_size >> 10);

	return 0;

	dispif_cleanup();
err6:
	clk_put(priv.clk_dispif);
err5:
	free_irq(TZ3000_IRQRE_DISPIF_VSYNC, &priv);
err4:
	free_irq(TZ3000_IRQRE_DISPIF_VBLANKINEDGEINT, &priv);
err4_1:
	free_irq(TZ3000_IRQ_DISPIF_INTERR, &priv);
err4_2:
	free_irq(TZ3000_IRQ_DISPIF_INTFRAME, &priv);
err4_3:
	free_irq(TZ3000_IRQ_DISPIF_DSIINT, &priv);
err4_4:
	free_irq(TZ3000_IRQ_DISPIF_HBLANKININT3, &priv);
err4_5:
	free_irq(TZ3000_IRQ_DISPIF_HBLANKININT2, &priv);
err4_6:
	free_irq(TZ3000_IRQ_DISPIF_VBLANKOUTINT, &priv);
err4_7:
	free_irq(TZ3000_IRQ_DISPIF_VBLANKININT, &priv);
err4_8:
	free_irq(TZ3000_IRQ_DISPIF_HBLANKININT, &priv);
err4_9:
	unregister_framebuffer(info);
err3:
	fb_dealloc_cmap(&info->cmap);
err2:
	framebuffer_release(info);
err1:
	if (priv.fconva_memory)
		dma_free_coherent(NULL, priv.fconva_in_size,
				  priv.fconva_memory,
				  (dma_addr_t)priv.fconva_in_base);
	if (priv.fconvb_memory)
		dma_free_coherent(NULL, priv.fconvb_in_size,
				  priv.fconvb_memory,
				  (dma_addr_t)priv.fconvb_in_base);
	if (priv.fconva_out_memory)
		dma_free_coherent(NULL, priv.fconva_out_size,
				  priv.fconva_out_memory,
				  (dma_addr_t)priv.fconva_out_base);
	if (priv.fconvb_out_memory)
		dma_free_coherent(NULL, priv.fconvb_out_size,
				  priv.fconvb_out_memory,
				  (dma_addr_t)priv.fconvb_out_base);
err0:
	if (priv.pmu_regs)
		iounmap(priv.pmu_regs);
	if (priv.dispif_regs)
		iounmap(priv.dispif_regs);

	return retval;
}

static int __devexit tz3000fb_remove(struct platform_device *pdev)
{
	struct fb_info *info = platform_get_drvdata(pdev);

	if (info) {
		dispif_cleanup();

#if IS_ENABLED(CONFIG_PM_RUNTIME)
		/* call tz3000fb_runtime_suspend() directly */
		pm_runtime_put_sync(&(pdev->dev));

		pm_runtime_disable(&(pdev->dev));
#else
		tz3000fb_runtime_suspend(&(pdev->dev));
#endif /* IS_ENABLED(CONFIG_PM_RUNTIME) */
		clk_put(priv.clk_dispif);

		free_irq(TZ3000_IRQRE_DISPIF_VSYNC, &priv);
		free_irq(TZ3000_IRQRE_DISPIF_VBLANKINEDGEINT, &priv);
		free_irq(TZ3000_IRQ_DISPIF_INTERR, &priv);
		free_irq(TZ3000_IRQ_DISPIF_INTFRAME, &priv);
		free_irq(TZ3000_IRQ_DISPIF_DSIINT, &priv);
		free_irq(TZ3000_IRQ_DISPIF_HBLANKININT3, &priv);
		free_irq(TZ3000_IRQ_DISPIF_HBLANKININT2, &priv);
		free_irq(TZ3000_IRQ_DISPIF_VBLANKOUTINT, &priv);
		free_irq(TZ3000_IRQ_DISPIF_VBLANKININT, &priv);
		free_irq(TZ3000_IRQ_DISPIF_HBLANKININT, &priv);

		unregister_framebuffer(info);

		fb_dealloc_cmap(&info->cmap);
		framebuffer_release(info);

		if (priv.fconva_memory)
			dma_free_coherent(NULL, priv.fconva_in_size,
					  priv.fconva_memory,
					  (dma_addr_t)priv.fconva_in_base);
		if (priv.fconvb_memory)
			dma_free_coherent(NULL, priv.fconvb_in_size,
					  priv.fconvb_memory,
					  (dma_addr_t)priv.fconvb_in_base);
		if (priv.fconva_out_memory)
			dma_free_coherent(NULL, priv.fconva_out_size,
					  priv.fconva_out_memory,
					  (dma_addr_t)priv.fconva_out_base);
		if (priv.fconvb_out_memory)
			dma_free_coherent(NULL, priv.fconvb_out_size,
					  priv.fconvb_out_memory,
					  (dma_addr_t)priv.fconvb_out_base);
		if (priv.pmu_regs)
			iounmap(priv.pmu_regs);
		if (priv.dispif_regs)
			iounmap(priv.dispif_regs);
	}

	return 0;
}

#ifdef CONFIG_PM
static int tz3000fb_freeze(struct device *dev)
{
	dispif_cleanup();
	tz3000fb_hw_stop();

	return 0;
}

static int tz3000fb_restore(struct device *dev)
{
	int retval;

	/* dispif hardware initialize for hibernation */
	dispif_cleanup();
	retval = dispif_setup();

	return retval;
}

static const struct dev_pm_ops tz3000fb_pm_ops = {
	.suspend = tz3000fb_suspend,
	.resume = tz3000fb_resume,
	.freeze = tz3000fb_freeze,
	.thaw = tz3000fb_resume,
	.restore = tz3000fb_restore,
#if IS_ENABLED(CONFIG_PM_RUNTIME)
	.runtime_suspend = tz3000fb_runtime_suspend,
	.runtime_resume = tz3000fb_runtime_resume,
#endif /* IS_ENABLED(CONFIG_PM_RUNTIME) */
};

#endif
static struct platform_driver tz3000fb_driver = {
	.probe	= tz3000fb_probe,
	.remove = tz3000fb_remove,
	.driver = {
		.name	= "tz3000fb",
		.owner = THIS_MODULE,
#ifdef CONFIG_PM
		.pm = &tz3000fb_pm_ops,
#endif
	},
};

static int __init tz3000fb_init(void)
{
	int ret = 0;
#ifndef MODULE
	char *option = NULL;

	if (fb_get_options("tz3000fb", &option))
		return -ENODEV;
	tz3000fb_setup(option);
#endif

	ret = platform_driver_register(&tz3000fb_driver);

	return ret;
}

module_init(tz3000fb_init);

#ifdef MODULE
static void __exit tz3000fb_exit(void)
{
	platform_driver_unregister(&tz3000fb_driver);
}

module_exit(tz3000fb_exit);

/* MODULE INFORMATION */
MODULE_AUTHOR("TOSHIBA Corporation");
MODULE_DESCRIPTION("Display Driver");
MODULE_VERSION(DISPLAY_DRIVER_VERSION);
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("display");
#endif				/* MODULE */
