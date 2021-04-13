/*
 * linux/drivers/video/applite/applitefb_base.c
 *
 * (C) Copyright TOSHIBA Corporation
 * Semiconductor & Storage Products Company 2013
 *
 * This program is free software;
 * you can redistribute it and/or modifyfb1_baseaddr
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

#include <linux/videodev2.h>
#include <linux/uaccess.h>
#include <linux/i2c.h>
#include <linux/gpio.h>
#include <linux/platform_device.h>
#include <linux/pm_runtime.h>
#include <linux/clk.h>
#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>

#include "applitefb.h"

#include "applitefb_tz3000.h"
#include "applitefb_tz2000.h"

#if IS_ENABLED(CONFIG_FB_TZ2000)
#include "tz2000gfx_internal.h"
#endif

/* MODULE INFORMATION */
MODULE_AUTHOR("TOSHIBA Corporation");
MODULE_DESCRIPTION("Display Driver");
MODULE_VERSION(DISPLAY_DRIVER_VERSION);
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("display");

struct mutex applitefb_lock;
u_long magnification = CONFIG_APPLITEFB_DEFAULT_FB_MAGNIFICATION;
u_long xres = DEFAULT_XRES;
u_long yres = DEFAULT_YRES;
#if IS_ENABLED(CONFIG_FB_TZ2000)
u_long a_alpha = 255;
u_long b_alpha = 255;
u_long c_alpha = 255;
u_long d_alpha = 255;
u_long e_alpha = 255;
#endif
#if IS_ENABLED(CONFIG_FB_TZ3000)
u_long a_alpha = 255;
u_long b_alpha = 255;
u_long sel_alpha;
u_long merge = 2;
ulong g_display_mode = 2;
int probe_flag;
int plane_a_layer;
int plane_b_layer;
#endif

module_param(magnification, ulong, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(magnification, "Num of Framebuffer layer");

module_param(xres, ulong, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(xres, "Set xres value");

module_param(yres, ulong, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(yres, "Set yres value");

#if IS_ENABLED(CONFIG_FB_TZ2000)
module_param(a_alpha, ulong, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(a_alpha, "Set PlaneA alpha value");

#if (CONFIG_APPLITEFB_ENABLE_LAYER > 1)
module_param(b_alpha, ulong, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(b_alpha, "Set PlaneB alpha value");

#if (CONFIG_APPLITEFB_ENABLE_LAYER > 2)
module_param(c_alpha, ulong, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(c_alpha, "Set PlaneC alpha value");

#if (CONFIG_APPLITEFB_ENABLE_LAYER > 3)
module_param(d_alpha, ulong, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(d_alpha, "Set PlaneD alpha value");

#if (CONFIG_APPLITEFB_ENABLE_LAYER > 4)
module_param(e_alpha, ulong, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(e_alpha, "Set PlaneE alpha value");

#endif	/* (CONFIG_APPLITEFB_ENABLE_LAYER > 4) */
#endif	/* (CONFIG_APPLITEFB_ENABLE_LAYER > 3) */
#endif	/* (CONFIG_APPLITEFB_ENABLE_LAYER > 2) */
#endif	/* (CONFIG_APPLITEFB_ENABLE_LAYER > 1) */
#endif
#if IS_ENABLED(CONFIG_FB_TZ3000)
module_param(a_alpha, ulong, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(a_alpha, "Set PlaneA alpha value");

module_param(b_alpha, ulong, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(b_alpha, "Set PlaneB alpha value");

module_param(sel_alpha, ulong, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(sel_alpha,
	"Set alpha source(0:from plane 1:from register)");

module_param(merge, ulong, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(merge,
	"Set merge pattern(0:not merge(fb0 output) 1:not merge(fb1 output) 2:fb1 background 3:fb0 background)");
#endif
#if (IS_BUILTIN(CONFIG_FB_TZ2000) || IS_BUILTIN(CONFIG_FB_TZ3000))
static int __init getparam_parse_magnification(char *str)
{
	u_long par;
	if (get_option(&str, (int *)&par))
		magnification = par;
	return 1;
}
static int __init getparam_parse_xres(char *str)
{
	u_long par;
	if (get_option(&str, (int *)&par))
		xres = par;
	return 1;
}
static int __init getparam_parse_yres(char *str)
{
	u_long par;
	if (get_option(&str, (int *)&par))
		yres = par;
	return 1;
}
#if IS_ENABLED(CONFIG_FB_TZ2000)
static int __init getparam_parse_a_alpha(char *str)
{
	u_long par;
	if (get_option(&str, (int *)&par))
		a_alpha = ((((par < 0) ? 0 : par) > 255) ? 255 : par);
	return 1;
}
static int __init getparam_parse_b_alpha(char *str)
{
	u_long par;
	if (get_option(&str, (int *)&par))
		b_alpha = ((((par < 0) ? 0 : par) > 255) ? 255 : par);
	return 1;
}
static int __init getparam_parse_c_alpha(char *str)
{
	u_long par;
	if (get_option(&str, (int *)&par))
		c_alpha = ((((par < 0) ? 0 : par) > 255) ? 255 : par);
	return 1;
}
static int __init getparam_parse_d_alpha(char *str)
{
	u_long par;
	if (get_option(&str, (int *)&par))
		d_alpha = ((((par < 0) ? 0 : par) > 255) ? 255 : par);
	return 1;
}
static int __init getparam_parse_e_alpha(char *str)
{
	u_long par;
	if (get_option(&str, (int *)&par))
		e_alpha = ((((par < 0) ? 0 : par) > 255) ? 255 : par);
	return 1;
}

#endif
#if IS_ENABLED(CONFIG_FB_TZ3000)
static int __init getparam_parse_a_alpha(char *str)
{
	u_long par;
	if (get_option(&str, (int *)&par))
		a_alpha = ((((par < 0) ? 0 : par) > 255) ? 255 : par);
	return 1;
}
static int __init getparam_parse_b_alpha(char *str)
{
	u_long par;
	if (get_option(&str, (int *)&par))
		b_alpha = ((((par < 0) ? 0 : par) > 255) ? 255 : par);
	return 1;
}
static int __init getparam_parse_sel_alpha(char *str)
{
	u_long par;
	if (get_option(&str, (int *)&par))
		sel_alpha = ((((par < 0) ? 0 : par) > 1) ? 1 : par);
	else
		sel_alpha = 0;
	return 1;
}
static int __init getparam_parse_merge(char *str)
{
	u_long par;
	if (get_option(&str, (int *)&par))
		merge = ((((par < 0) ? 0 : par) > 3) ? 3 : par);
	return 1;
}
#endif

__setup("magnification", getparam_parse_magnification);
__setup("xres", getparam_parse_xres);
__setup("yres", getparam_parse_yres);
#if IS_ENABLED(CONFIG_FB_TZ2000)
__setup("a_alpha", getparam_parse_a_alpha);
__setup("b_alpha", getparam_parse_b_alpha);
__setup("c_alpha", getparam_parse_c_alpha);
__setup("d_alpha", getparam_parse_d_alpha);
__setup("e_alpha", getparam_parse_e_alpha);
#endif
#if IS_ENABLED(CONFIG_FB_TZ3000)
__setup("a_alpha", getparam_parse_a_alpha);
__setup("b_alpha", getparam_parse_b_alpha);
__setup("sel_alpha", getparam_parse_sel_alpha);
__setup("merge", getparam_parse_merge);
#endif

#endif	/* (IS_BUILTIN(CONFIG_FB_TZ2000) || IS_BUILTIN(CONFIG_FB_TZ3000)) */


/*
 * output baseaddress
 */
#if IS_ENABLED(CONFIG_FB_TZ3000)
u32 g_out_baseaddr;
static void *g_out_vram;
static u32 g_max_fb_out_size;
u32 g_out_baseaddr_offset[DEVICE_MAX];
#endif
static u32 g_max_fb_size[DEVICE_MAX];

struct applitefb_dev priv;
struct applitefb_layer g_fb_layer[DEVICE_MAX];
u32 g_disp_xres = DEFAULT_XRES;
u32 g_disp_yres = DEFAULT_YRES;

/*
 * Here we define the default structs fb_fix_screeninfo and fb_var_screeninfo
 * if we don't use modedb. If we do use modedb see xxxfb_init how to use it
 * to get a fb_var_screeninfo. Otherwise define a default var as well.
 */
static struct fb_fix_screeninfo applitefb_fix __devinitdata = {
	/* id smem_start smem_len type type_aux visual
	   xpanstep ypanstep ywranstep line_length mmio_start mmio_len
	   accel capabilities reserved[2] */
	"applitefb", 0, 0, FB_TYPE_PACKED_PIXELS, 0,
	FB_VISUAL_TRUECOLOR, 1, 1, 1,
	(DEFAULT_XRES * DEFAULT_BPP / 8), 0, 0,
#if IS_ENABLED(CONFIG_FB_TZ3000)
	FB_ACCEL_NONE,
#elif IS_ENABLED(CONFIG_FB_TZ2000)
	FB_ACCEL_APPLITE_TZ2000,
#endif
	0, {0, 0},
};


static struct fb_var_screeninfo applitefb_var __devinitdata = {
	/* xres yres xres_virtual yres_virtual xoffset yoffset
	   bits_per_pixel grayscale red green blue transp nonstd
	   activate height width accel_flags clock l_margin r_margin
	   u_margin l_margin hsync_len vsync_len sync vmode
	   rotate colorspace reserved[4] */
	MAX_XRES, MAX_YRES, MAX_XRES, MAX_YRES, 0, 0,
	MAX_BPP, 0, {16, 8, 0}, {8, 8, 0}, {0, 8, 0}, {24, 8, 0}, 0,
	FB_ACTIVATE_NOW, 0, 0, 0, 0, 148, 88,
	36, 4, 0, 0, FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED,
	0, V4L2_COLORSPACE_SRGB, {0, 0, 0, 0}
};

#if IS_ENABLED(CONFIG_FB_TZ3000)
static struct fb_videomode modedb[] __devinitdata = {
	/* name refresh xres yres pixclock l_margin r_margin u_margin l_margin
	   hsync vsync sync vmode flag */
	{/* 720x480 */
		NULL, 60, 720, 480, 37037,  60,  16,  30, 9,  62, 6,
		0,
		FB_VMODE_NONINTERLACED,
		0
	},
	{/* 1280x720 */
#if defined(_1280x720_60HZ_)
		NULL, 60, 1280, 720, 13468, 220, 440,  20, 5,  40, 5,
		FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED,
		0
#else
		NULL, 50, 1280, 720, 13468, 220, 440,  20, 5,  40, 5,
		FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED,
		0
#endif
	},
	{/* 1920x1080 */
		NULL, 30, 1920, 1080, 13468, 148,  88,  36, 4,  44, 5,
		FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED,
		0
	},
	{/* 1920x1080 */
		NULL, 60, 1920, 1080,  6734, 148,  88,  36, 4,  44, 5,
		FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED,
		0
	}
};
#endif

/*
 * Arrangement of lcdc Structure
 */
static const struct applitefb_lcdc_format_info applitema_format_infos[] = {
	{/* YUV4:4:4 Complete separation */
		.fourcc = V4L2_PIX_FMT_YUV444P,
		.bpp = 24,
		.yuv = true,
	},
	{/* YUV4:2:2 Complete separation */
		.fourcc = V4L2_PIX_FMT_YUV422P,
		.bpp = 16,
		.yuv = true,
	},
	{/* YUV4:2:0 Complete separation */
		.fourcc = V4L2_PIX_FMT_YUV420,
		.bpp = 12,
		.yuv = true,
	},
	{/* YUV4:2:0 part separation */
		.fourcc = V4L2_PIX_FMT_NV12,
		.bpp = 12,
		.yuv = true,
	},
	{/* YUV32 Pack */
		.fourcc = V4L2_PIX_FMT_YUV32,
		.bpp = 32,
		.yuv = true,
	}
};

#if IS_ENABLED(CONFIG_FB_TZ3000)
static void calculate_offset(u32 layer)
{

	/* offset calculate */
	g_out_baseaddr_offset[layer] = (g_fb_layer[layer].ypos *
			g_disp_xres *
			DEFAULT_BPP / 8) +
			(g_fb_layer[layer].xpos *
			DEFAULT_BPP / 8);

}
#endif


#if IS_ENABLED(CONFIG_FB_TZ2000)
#define BUF_SIZE 10
#endif
static struct kobject *applitefb_kobj;

#if IS_ENABLED(CONFIG_FB_TZ2000)
static ssize_t is_rgba_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	char	data[BUF_SIZE];
	_FNC_START("\n");
	sscanf(buf, "%s", data);

	if (g_fb_layer[0].format != RGB565) {
		_WAR_LOG("This function is available only when /dev/fb0 is RGB565 format."
			"Current format isn't RGB565.\n");
	} else {
		if (strcmp(data, "1") == 0) {
			_DBG_LOG("set RGBA8888\n");
			priv.is_rgba = true;
			format_adjustment();
		} else if (strcmp(data, "0") == 0) {
			_DBG_LOG("set ARGB8888\n");
			priv.is_rgba = false;
			format_adjustment();
		} else
			_WAR_LOG("Bad parameter was input. Please input 1(RGBA8888) or 0(ARGB8888)\n");
	}
	_FNC_END("\n");
	return strlen(buf);
}

static ssize_t is_rgba_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	_FNC_START("\n");
	_FNC_END("\n");
	 return snprintf(buf, PAGE_SIZE, "%d\n", priv.is_rgba);
}
#endif

static char g_buf[PAGE_SIZE + REGISTER_SIZE];
static ssize_t is_regdump_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	u32 i, ret;
	_FNC_START("\n");
	memset(g_buf, 0, sizeof(g_buf));
	for (i = 0; i < REGISTER_NUM; i++) {
		ret = lcdc_read(&priv, debug_regist[i].reg_offset);
		sprintf(g_buf, "[0x%04x]0x%08x\n",
			debug_regist[i].reg_offset, ret);
		if (strlen(buf) + strlen(g_buf) > PAGE_SIZE)
			break;
		strcat(buf, g_buf);
	}
	_FNC_END("\n");
	return strlen(buf);
}

static void calculate_display_position(u32 node, struct fb_var_screeninfo *var)
{
	if ((g_fb_layer[node].xpos + var->xres > g_disp_xres) &&
		(g_fb_layer[node].ypos + var->yres > g_disp_yres)) {
		g_fb_layer[node].dxres = g_disp_xres - g_fb_layer[node].xpos;
		g_fb_layer[node].dyres = g_disp_yres - g_fb_layer[node].ypos;
	} else if (g_fb_layer[node].xpos + var->xres > g_disp_xres) {
		g_fb_layer[node].dxres = g_disp_xres - g_fb_layer[node].xpos;
		g_fb_layer[node].dyres = var->yres;
	} else if (g_fb_layer[node].ypos + var->yres > g_disp_yres) {
		g_fb_layer[node].dxres = var->xres;
		g_fb_layer[node].dyres = g_disp_yres - g_fb_layer[node].ypos;
	} else {
		g_fb_layer[node].dxres = var->xres;
		g_fb_layer[node].dyres = var->yres;
	}
}


static ssize_t is_lxystart_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	int ret = 0;
	u32 layer;
	u32 lxstart, lystart;

	_FNC_START("\n");
	/* layer/lxstart/lystart */
	sscanf(buf, "%d%d%d", &layer, &lxstart, &lystart);

	if (layer < 0 || layer >= CONFIG_APPLITEFB_ENABLE_LAYER) {
		_ERR_LOG("invalid layer parameter(%d)\n", layer);
		_FNC_END("\n");
		return -EINVAL;
	}
#if IS_ENABLED(CONFIG_FB_TZ2000)
	if ((lxstart < 0) || (lxstart >= g_disp_xres)) {
#else
	if ((lxstart < 0) || (lxstart > (g_disp_xres - HSIZE_MINIMUM_VALUE))) {
#endif
		_ERR_LOG("invalid lxstart parameter(%d),MAX_XRES(%d)\n", lxstart, g_disp_xres);
		_FNC_END("\n");
		return -EINVAL;
	}
#if IS_ENABLED(CONFIG_FB_TZ2000)
	if ((lystart < 0) || (lystart >= g_disp_yres)) {
#else
	if ((lystart < 0) || (lystart > (g_disp_yres - VSIZE_MINIMUM_VALUE))) {
#endif
		_ERR_LOG("invalid lystart parameter(%d),MAX_XRES(%d)\n", lystart, g_disp_yres);
		_FNC_END("\n");
		return -EINVAL;
	}
	/* mask of alignment */
	lxstart = (lxstart & HSIZE_ALIGN_MASK);
	lystart = (lystart & VSIZE_ALIGN_MASK);
	g_fb_layer[layer].xpos = lxstart;
	g_fb_layer[layer].ypos = lystart;
#if IS_ENABLED(CONFIG_FB_TZ3000)
	calculate_offset(layer);
#endif
	calculate_display_position(layer, &priv.info[layer]->var);

	/* Waiting for end of frame */
	ret = applitefb_wait_for_frame_end(layer);

	if (!ret) {
		_ERR_LOG("timeout\n");
		return -ETIMEDOUT;
	} else if (ret < 0) {
		_ERR_LOG("err\n");
		return ret;
	}

	_FNC_END("\n");
	return strlen(buf);

}

static ssize_t is_lxystart_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	u32 i;

	_FNC_START("\n");
	for (i = 0; i < CONFIG_APPLITEFB_ENABLE_LAYER; i++) {
		sprintf(g_buf, "layer:%d(lxstart=%d,lystart=%d)\n",
			i, g_fb_layer[i].xpos, g_fb_layer[i].ypos);
		strcat(buf, g_buf);
	}
	_FNC_END("\n");
	return strlen(buf);
}

#if IS_ENABLED(CONFIG_FB_TZ3000)
static ssize_t is_merge_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	_FNC_START("\n");

	sscanf(buf, "%d", (int *)&merge);

	if (merge > 3) {
		_ERR_LOG("invalid merge parameter(%d)\n", (int)merge);
		_FNC_END("\n");
		return -EINVAL;
	}

	if (merge == 0) {
		plane_output(0);
		_DBG_LOG("merge=%d : not merge(fb0 output)\n", merge);
	} else if (merge == 1) {
		plane_output(1);
		_DBG_LOG("merge=%d : not merge(fb1 output)\n", merge);
	} else {
		plane_output(0);
		_DBG_LOG("merge=%d : merge(2:fb1 background 3:fb0 background)\n", merge);
	}

	_FNC_END("\n");
	return strlen(buf);
}

static ssize_t is_merge_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	_FNC_START("\n");
	_FNC_END("\n");
	 return snprintf(buf, PAGE_SIZE, "merge:%d\n", (int)merge);
}
#endif

#if IS_ENABLED(CONFIG_FB_TZ2000)
static struct kobj_attribute is_rgba_attribute = __ATTR(is_rgba, 0666, is_rgba_show, is_rgba_store);
#endif
static struct kobj_attribute regdump_attribute = __ATTR(regdump, 0666, is_regdump_show, NULL);
static struct kobj_attribute lxystart_attribute = __ATTR(lxystart, 0666, is_lxystart_show, is_lxystart_store);
#if IS_ENABLED(CONFIG_FB_TZ3000)
static struct kobj_attribute merge_attribute = __ATTR(merge, 0666, is_merge_show, is_merge_store);
#endif

static struct attribute *attrs[] = {
#if IS_ENABLED(CONFIG_FB_TZ2000)
	&is_rgba_attribute.attr,
#endif
	&regdump_attribute.attr,
	&lxystart_attribute.attr,
#if IS_ENABLED(CONFIG_FB_TZ3000)
	&merge_attribute.attr,
#endif
	NULL,
};

static struct attribute_group attr_group = {
	.attrs = attrs,
};


static int applitefb_sysfs_init(void)
{
	int retval;
	_FNC_START("\n");
	applitefb_kobj = kobject_create_and_add("applitefb", kernel_kobj);
	if (!applitefb_kobj)
		return -ENOMEM;

	retval = sysfs_create_group(applitefb_kobj, &attr_group);
	if (retval)
		kobject_put(applitefb_kobj);
	_FNC_END("\n");
	return retval;
}

static void applitefb_sysfs_exit(void)
{
	_FNC_START("\n");
	kobject_put(applitefb_kobj);
	_FNC_END("\n");
}



u_long get_display_pixelformat(struct fb_var_screeninfo *var, __u32 *fmt)
{
	_FNC_START("\n");
/* because of fb_set problem (change yuv -> rgb) */
/*
	if (var->grayscale == 1)
		return 2;
*/
	if (var->grayscale > 1) {
		*fmt = var->grayscale;
		_FNC_END("(1)\n");
		return 1;
	} else {
		*fmt = RGB565;
		if (var->bits_per_pixel == 16) {
#if IS_ENABLED(CONFIG_FB_TZ3000)
			if (var->transp.length) {
				if (var->red.offset) {	/* ARGB 1555 */
					_DBG_LOG("format is ARGB1555\n");
					*fmt = ARGB1555;
				} else {		/* ABGR 1555 */
					_DBG_LOG("format is ABGR1555\n");
					*fmt = ABGR1555;
				}
			} else {
				if (var->red.offset) {	/* RGB565 */
					_DBG_LOG("format is RGB565\n");
					*fmt = RGB565;
				} else {		/* BGR565 */
					_DBG_LOG("format is BGR565\n");
					*fmt = BGR565;
				}
			}
#elif IS_ENABLED(CONFIG_FB_TZ2000)
			_DBG_LOG("format is RGB565\n");
			*fmt = RGB565;
#endif
		} else if (var->bits_per_pixel == 32) {
#if IS_ENABLED(CONFIG_FB_TZ3000)
			if (var->transp.offset) {
				if (var->red.offset) {	/* ARGB 8888 */
					_DBG_LOG("format is ARGB8888\n");
					*fmt = ARGB8888;
				} else {		/* ABGR 8888 */
					_DBG_LOG("format is ABGR8888\n");
					*fmt = ABGR8888;
				}
			} else {			/* ARGB 8888 */
				_DBG_LOG("format is ARGB8888\n");
				*fmt = ARGB8888;
			}
#elif IS_ENABLED(CONFIG_FB_TZ2000)
			if (var->blue.offset) {		/* RGBA 8888 */
				_DBG_LOG("format is RGBA8888\n");
				*fmt = RGBA8888;
			} else {			/* ARGB 8888 */
				_DBG_LOG("format is ARGB8888\n");
				*fmt = ARGB8888;
			}
#endif
		} else {
			_FNC_END("(-1)\n");
			return -1;
		}
		_FNC_END("(0)\n");
		return 0;
	}
	_FNC_END("(-1)\n");
	return -1;
}



/*
 * Function for get lcdc Structure
 */
static const struct
applitefb_lcdc_format_info *applitema_format_info(u32 fourcc)
{
	unsigned int i;

	_FNC_START("\n");

	for (i = 0; i < ARRAY_SIZE(applitema_format_infos); i++) {
		if (applitema_format_infos[i].fourcc == fourcc) {
			_FNC_END("\n");
			return &applitema_format_infos[i];
		}
	}
	dprint("%s : specified arg is not match [%d]\n",
		FB_DEVICE_NAME, fourcc);
	_FNC_END("\n");

	return NULL;
}

/*
 * fb_var_screeninfo parameter check
 */
static int
applitefb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	struct applitefb_layer *layer = (struct applitefb_layer *)(info->par);

	_FNC_START("info(offset[%d, %d]) var(offset[%d, %d])\n",
		info->var.xoffset, info->var.yoffset,
		var->xoffset, var->yoffset);

	if (var->vmode & FB_VMODE_CONUPDATE) {
		var->vmode |= FB_VMODE_YWRAP;
		var->xoffset = info->var.xoffset;
		var->yoffset = info->var.yoffset;
		_DBG_LOG("changed FB_VMODE to FB_VMODE_YWRAP\n");
	}

	/*
	 *  Some very basic checks
	 */
	_DEV_LOG("res[%d, %d], virtual[%d, %d]\n", info->node,
		var->xres, var->yres, var->xres_virtual, var->yres_virtual);
	if (!var->xres)
		var->xres = 1;
	if (!var->yres)
		var->yres = 1;
	if (var->xres > var->xres_virtual)
		var->xres_virtual = var->xres;
	if (var->yres > var->yres_virtual)
		var->yres_virtual = var->yres;

	if (var->xres_virtual < var->xoffset + var->xres)
		var->xres_virtual = var->xoffset + var->xres;
	if (var->yres_virtual < var->yoffset + var->yres)
		var->yres_virtual = var->yoffset + var->yres;

	/* check input size */
	if ((var->xres > MAX_XRES) || (var->yres > MAX_YRES))
		return -EINVAL;

	_DEV_LOG("res[%d, %d], virtual[%d, %d]\n", info->node,
		var->xres, var->yres, var->xres_virtual, var->yres_virtual);

#if IS_ENABLED(CONFIG_FB_TZ3000)
	/* check for color space */
	if (var->grayscale > 1) {
		const struct applitefb_lcdc_format_info *format_info;
		_DEV_LOG("format is FOURCC\n", info->node);

		format_info = applitema_format_info(var->grayscale);
		if (!format_info) {
			_ERR_LOG("specified format is not match [%d]\n",
				var->grayscale);
			return -EINVAL;
		}

		var->bits_per_pixel = format_info->bpp;
		var->colorspace = V4L2_COLORSPACE_JPEG;
		set_rgba(var, 0, 0, 0, 0, 0, 0, 0, 0);
	} else {
#else
	{
#endif
		if (get_display_pixelformat(var, &(layer->format)) != 0) {
			_ERR_LOG("specified format is unsuitable"
				" rgba(%d/%d, %d/%d, %d/%d, %d/%d), bpp(%d)\n",
				var->red.length, var->red.offset,
				var->green.length, var->green.offset,
				var->blue.length, var->blue.offset,
				var->transp.length, var->transp.offset,
				var->bits_per_pixel);
			return -EINVAL;
		}
		switch (layer->format) {
#if IS_ENABLED(CONFIG_FB_TZ3000)
		case ARGB1555:
			var->bits_per_pixel = 16;
			set_rgba(var, 10, 5, 5, 5, 0, 5, 15, 1);
			break;
		case ABGR1555:
			var->bits_per_pixel = 16;
			set_rgba(var, 0, 5, 5, 5, 10, 5, 15, 1);
			break;
		case BGR565:
			var->bits_per_pixel = 16;
			set_rgba(var, 0, 5, 5, 6, 11, 5, 0, 0);
			break;
		case ABGR8888:
			var->bits_per_pixel = 32;
			set_rgba(var, 0, 8, 8, 8, 16, 8, 24, 8);
			break;
#endif
		case RGB565:
			var->bits_per_pixel = 16;
			set_rgba(var, 11, 5, 5, 6, 0, 5, 0, 0);
			break;
		case ARGB8888:
			var->bits_per_pixel = 32;
			set_rgba(var, 16, 8, 8, 8, 0, 8, 24, 8);
			break;
#if IS_ENABLED(CONFIG_FB_TZ2000)
		case RGBA8888:
			var->bits_per_pixel = 32;
			set_rgba(var, 24, 8, 16, 8, 8, 8, 0, 8);
			break;
#endif
		default:
			_ERR_LOG("specified format is unsuitable"
				" rgba(%d/%d, %d/%d, %d/%d, %d/%d), bpp(%d)\n",
				var->red.length, var->red.offset,
				var->green.length, var->green.offset,
				var->blue.length, var->blue.offset,
				var->transp.length, var->transp.offset,
				var->bits_per_pixel);
			return -EINVAL;
		}
	}

	/* reset offset position, when resigning */
	if ((info->var.bits_per_pixel != var->bits_per_pixel) ||
		(info->var.xres_virtual != var->xres_virtual) ||
		(info->var.yres_virtual != var->yres_virtual) ||
		(info->var.xres != var->xres) ||
		(info->var.yres != var->yres)) {
		layer->xoffset = 0;
		layer->yoffset = 0;
	}

	_DEV_LOG("rgba(%d/%d, %d/%d, %d/%d, %d/%d), bpp(%d), clrsps(%d)\n",
			info->node,
			var->red.offset, var->red.length,
			var->green.offset, var->green.length,
			var->blue.offset, var->blue.length,
			var->transp.offset, var->transp.length,
			var->bits_per_pixel, var->colorspace);
	_FNC_END("\n");
	return 0;
}

static void *
applitefb_alocate_memory_framebuffer(u32 memsize, dma_addr_t *addr)
{
	void *vram;

	/* Memory reservation for input framebuffer */
	vram = dma_alloc_coherent(NULL, ALIGN(memsize, PAGE_SIZE),
		addr, GFP_KERNEL);
	return vram;
}

static void
applitefb_release_memory_framebuffer(int node, u32 memsize, void *vram, __u32 addr)
{
	if (vram) {
#if IS_ENABLED(CONFIG_FB_TZ2000)
		if (node == GFX_DEVICE)
			dma_free_coherent(NULL,  ALIGN(memsize + gfx_size, PAGE_SIZE), vram, addr);
		else
#endif
			dma_free_coherent(NULL, ALIGN(memsize, PAGE_SIZE), vram, addr);
	}
}


/*
 * Set of fb_var_screeninfo parameter
 */
static int applitefb_set_par(struct fb_info *info)
{
	u32 baseaddr[3] = {0, 0, 0};
#if IS_ENABLED(CONFIG_FB_TZ3000)
	u32 max_fb_out_size_new = 0;
#endif
	int i = 0;
	const struct applitefb_lcdc_format_info *format_info;
	struct applitefb_layer *layer = (struct applitefb_layer *)(info->par);

	mutex_lock(&applitefb_lock);
	_FNC_START("\n");
	_DEV_LOG("fix(type(%d), visual(%d), line_length(%d)\n", info->node,
		info->fix.type, info->fix.visual, info->fix.line_length);

	info->fix.line_length = get_line_length(info->var.xres_virtual,
						info->var.bits_per_pixel);

	_DEV_LOG("fix(type(%d), visual(%d), line_length(%d)\n", info->node,
		info->fix.type, info->fix.visual, info->fix.line_length);

	if (info->var.grayscale > 1) {		/* Use FOURCC */
		_DBG_LOG("format is FOURCC\n");
		format_info = applitema_format_info(info->var.grayscale);

		if (!format_info) {
			_ERR_LOG("specified format is not match [%d]\n",
				info->var.grayscale);
			mutex_unlock(&applitefb_lock);
			return -1;
		}
		info->fix.type = FB_TYPE_FOURCC;
		info->fix.visual = FB_VISUAL_FOURCC;

	} else {
		info->fix.type = FB_TYPE_PACKED_PIXELS;
		info->fix.visual = FB_VISUAL_TRUECOLOR;
		layer->addr[0] = info->fix.smem_start;
	}
	_DEV_LOG("fix(type(%d), visual(%d), line_length(%d)\n", info->node,
		info->fix.type, info->fix.visual, info->fix.line_length);

#if IS_ENABLED(CONFIG_FB_TZ2000)
	if (layer->layer == 0) {
		switch (layer->format) {
		case RGBA8888:
			priv.is_rgba = true;
			break;
		case ARGB8888:
			priv.is_rgba = false;
			break;
		case RGB565:
			break;
		default:
			_ERR_LOG("invalid format selected[%d]\n", layer->format);
			mutex_unlock(&applitefb_lock);
			return -1;
		}
		_DEV_LOG("priv(is_rgba[%d])\n", info->node, priv.is_rgba);
	} else if (((layer->format == ARGB8888) && (priv.is_rgba == true)) ||
		 ((layer->format == RGBA8888) && (priv.is_rgba == false))) {
		_ERR_LOG("invalid parameter(format[%d], is_rgba[%d])\n", layer->format, priv.is_rgba);
		mutex_unlock(&applitefb_lock);
		return -1;
	}

	format_adjustment();
#endif

#if IS_ENABLED(CONFIG_FB_TZ2000)
	applitefb_lcdc_disable();
#else
	applitefb_lcdc_finalize();
#endif

#if IS_ENABLED(CONFIG_FB_TZ3000)
	switch (info->var.grayscale) {
	case V4L2_PIX_FMT_YUV444P:/* YUV4:4:4 Complete separation */
		layer->format = Y_CB_CR444;
		break;
	case V4L2_PIX_FMT_YUV422P:/* YUV4:2:2 Complete separation */
		layer->format = Y_CB_CR422;
		break;
	case V4L2_PIX_FMT_YUV420:/* YUV4:2:0 Complete separation */
		layer->format = Y_CB_CR420;
		break;
	case V4L2_PIX_FMT_NV12:/* YUV4:2:0 part separation */
		layer->format = Y_CBCR420;
		break;
	case V4L2_PIX_FMT_YUV32:/* AYUV32 Pack */
		layer->format = AYCBCR32;
		break;
	default:
		break;
	}
#endif

#if IS_ENABLED(CONFIG_FB_TZ3000)
	if (layer->layer == 0) {
		g_display_mode = get_display_mode(&info->var) - 1;
		_DBG_LOG("get_display_mode[%lu]\n", g_display_mode);
		max_fb_out_size_new = g_disp_xres * g_disp_yres  * DEFAULT_BPP / 8;

		if (g_max_fb_out_size != max_fb_out_size_new) {
			applitefb_release_memory_framebuffer(-1, g_max_fb_out_size, g_out_vram,
				(dma_addr_t)g_out_baseaddr);
			g_out_vram = applitefb_alocate_memory_framebuffer(max_fb_out_size_new,
				(dma_addr_t *)&g_out_baseaddr);
			if (!g_out_vram) {
				_ERR_LOG("applitefb_alocate_memory_framebuffer()failed [output]\n");
				mutex_unlock(&applitefb_lock);
				/* release memory for output */
				return -ENOMEM;
			}
			g_max_fb_out_size = max_fb_out_size_new;
		}
		calculate_offset(layer->layer);
	}
#endif

	calculate_display_position(layer->layer, &info->var);

	switch (info->var.grayscale) {
#if IS_ENABLED(CONFIG_FB_TZ3000)
	case V4L2_PIX_FMT_YUV444P:/* YUV4:4:4 Complete separation */
		_DEV_LOG("format is V4L2_PIX_FMT_YUV444P\n", info->node);
		layer->format = Y_CB_CR444;
		layer->line_length[0] = info->fix.line_length =
			info->var.xres_virtual;
		layer->line_length[1] = info->var.xres_virtual;
		layer->line_length[2] = info->var.xres_virtual;
		baseaddr[0] = info->fix.smem_start;
		baseaddr[1] = baseaddr[0] +
			info->var.yres_virtual * layer->line_length[0];
		baseaddr[2] = baseaddr[1] +
			info->var.yres_virtual * layer->line_length[1];
		break;
#endif
#if IS_ENABLED(CONFIG_FB_TZ3000)
	case V4L2_PIX_FMT_YUV422P:/* YUV4:2:2 Complete separation */
		_DEV_LOG("format is V4L2_PIX_FMT_YUV422P\n", info->node);
		layer->format = Y_CB_CR422;
		layer->line_length[0] = info->fix.line_length =
			info->var.xres_virtual;
		layer->line_length[1] = info->var.xres_virtual;
		layer->line_length[2] = info->var.xres_virtual;
		baseaddr[0] = info->fix.smem_start;
		baseaddr[1] = baseaddr[0] +
			info->var.yres_virtual * layer->line_length[0];
		baseaddr[2] = baseaddr[1] +
			info->var.yres_virtual * layer->line_length[1];
		break;
#endif
#if IS_ENABLED(CONFIG_FB_TZ3000)
	case V4L2_PIX_FMT_YUV420:/* YUV4:2:0 Complete separation */
		_DEV_LOG("format is V4L2_PIX_FMT_YUV420\n", info->node);
		layer->format = Y_CB_CR420;
		layer->line_length[0] = info->fix.line_length =
			info->var.xres_virtual;
		layer->line_length[1] = info->var.xres_virtual;
		layer->line_length[2] = info->var.xres_virtual;
		baseaddr[0] = info->fix.smem_start;
		baseaddr[1] = baseaddr[0] +
			info->var.yres_virtual * layer->line_length[0];
		baseaddr[2] = baseaddr[1] +
			info->var.yres_virtual / 2 * layer->line_length[1];
		break;
#endif
#if IS_ENABLED(CONFIG_FB_TZ3000)
	case V4L2_PIX_FMT_NV12:/* YUV4:2:0 part separation */
		_DEV_LOG("format is V4L2_PIX_FMT_NV12\n", info->node);
		layer->format = Y_CBCR420;
		layer->line_length[0] = info->fix.line_length =
			info->var.xres_virtual;
		layer->line_length[1] = info->var.xres_virtual;
		baseaddr[0] = info->fix.smem_start;
		baseaddr[1] = baseaddr[0] +
			info->var.yres_virtual * layer->line_length[0];
		break;
#endif
#if IS_ENABLED(CONFIG_FB_TZ3000)
	case V4L2_PIX_FMT_YUV32:/* AYUV32 Pack */
		_DEV_LOG("format is V4L2_PIX_FMT_YUV32\n", info->node);
		layer->format = AYCBCR32;
		layer->line_length[0] = info->fix.line_length =
			info->var.xres_virtual * info->var.bits_per_pixel / 8;
		baseaddr[0] = info->fix.smem_start;
		break;
#endif
	default:
		_DEV_LOG("select default\n", info->node);
		layer->line_length[0] = info->fix.line_length =
			info->var.xres_virtual * info->var.bits_per_pixel / 8;
		baseaddr[0] = info->fix.smem_start;
		baseaddr[1] = baseaddr[0] + info->var.xres_virtual *
			info->var.bits_per_pixel / 8 * info->var.yres_virtual;
		baseaddr[2] = baseaddr[1];
	}
	priv.xres = info->var.xres;
	priv.yres = info->var.yres;
	_DEV_LOG("priv(xres[%d], yres[%d])\n",
				info->node, priv.xres, priv.yres);

	if (info->var.grayscale) {
		for (i = 0; i < MAX_PLANE; i++)
			layer->addr[i] = baseaddr[i];
	}

#if IS_ENABLED(CONFIG_FB_TZ2000)
	applitefb_lcdc_enable(&(info->var));
#else
	applitefb_lcdc_initialize(&(info->var));
#endif
	_FNC_END("\n");
	mutex_unlock(&applitefb_lock);
	return 0;
}

/*
 * if applitefb_setcolreg is called, return 0.
 */
static int
applitefb_setcolreg(unsigned regno, unsigned red, unsigned green,
			   unsigned blue, unsigned transp,
			   struct fb_info *info)
{
	return 0;
}

/*
 * Pan the display
 */
static int applitefb_pan_display(struct fb_var_screeninfo *var,
			     struct fb_info *info)
{
	int ret;
	struct applitefb_layer *layer = (struct applitefb_layer *)(info->par);
	_FNC_START("\n");
	_DEV_LOG("xoffset=%d, yoffset=%d\n",
		info->node, var->xoffset, var->yoffset);

	/* Parameter check of offset */
	if (var->vmode & FB_VMODE_YWRAP) {
		if ((var->yoffset < 0)
			|| (var->yoffset >= info->var.yres_virtual)
			|| var->xoffset) {
			_ERR_LOG("specified parameter is unsuitable "
				"offset(%d, %d), yres_virtual[%d]\n",
				var->xoffset, var->yoffset,
				info->var.yres_virtual);
			return -EINVAL;
		}
	} else {
		if (((var->xoffset + info->var.xres) > info->var.xres_virtual)
			|| ((var->yoffset + info->var.yres) > info->var.yres_virtual)) {
			_ERR_LOG("specified parameter is unsuitable "
				"xoffset[%d], xres[%d], xres_virtual[%d],"
				"yoffset[%d], yres[%d], yres_virtual[%d]\n",
				var->xoffset, info->var.xres,
				info->var.xres_virtual,
				var->yoffset, info->var.yres,
				info->var.yres_virtual);
			return -EINVAL;
		}
	}

	if ((layer->yoffset == var->yoffset) &&
		(layer->xoffset == var->xoffset)) {
		_DEV_LOG("var->yoffset,xoffset not change\n", info->node);
		return 0;
	}
	info->var.xoffset = layer->xoffset = var->xoffset;
	info->var.yoffset = layer->yoffset = var->yoffset;

	ret = pan_display(var, info);

	if (var->vmode & FB_VMODE_YWRAP) {
		_DEV_LOG("var->vmode is FB_VMODE_YWRAP\n", info->node);
		info->var.vmode |= FB_VMODE_YWRAP;
	} else {
		_DEV_LOG("var->vmode is not  FB_VMODE_YWRAP\n", info->node);
		info->var.vmode &= ~FB_VMODE_YWRAP;
	}

	_FNC_END("\n");
	return ret;
}

/*
 * Get parameter of vblank
 */
static void applitefb_get_vblank(struct fb_vblank *vblank)
{
	_FNC_START("\n");
	memset(vblank, 0, sizeof(*vblank));
	vblank->flags = FB_VBLANK_HAVE_VSYNC;
	_FNC_END("\n");
	return;
}


static int applitefb_ioctl(struct fb_info *info, unsigned int cmd,
			  unsigned long arg)
{
	int retval;
	void __user *argp = (void __user *)arg;
	struct fb_vblank vblank;

	_FNC_START("\n");
	retval = 0;
	switch (cmd) {
	/* get parameter of vblank structure */
	case FBIOGET_VBLANK:
		_DEV_LOG("execute applitefb_get_vblank()\n", info->node);
		applitefb_get_vblank(&vblank);

		if (copy_to_user(argp, &vblank, sizeof(vblank))) {
			_ERR_LOG("copy_to_user()\n");
			retval = -EFAULT;
		}
		break;
	/* wait for interruption of vsync */
	case FBIO_WAITFORVSYNC:
		_DEV_LOG("execute applitefb_wait_for_vsync()\n", info->node);
		retval = applitefb_wait_for_vsync(info);
		break;
	default:
		retval = applitefb_local_ioctl(info, cmd, arg);
		break;
	}
	_FNC_END("\n");
	return retval;
}


/*
 * mapping to virtual memory
 */
static int applitefb_mmap(struct fb_info *info, struct vm_area_struct *vma)
{
	unsigned long size = vma->vm_end - vma->vm_start;
	unsigned long offset = vma->vm_pgoff << PAGE_SHIFT;
	unsigned long pos = info->fix.smem_start + offset;

	_FNC_START("\n");

	if (offset + size > info->fix.smem_len)
		return -EINVAL;

	vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);

	if (io_remap_pfn_range(vma, vma->vm_start, pos >> PAGE_SHIFT, size,
				vma->vm_page_prot))
		return -EAGAIN;

	vma->vm_flags |= VM_RESERVED;

	_FNC_END("\n");
	return 0;
}

static struct fb_ops applite_speyfb_ops = {
	.owner		= THIS_MODULE,
	.fb_read	= fb_sys_read,
	.fb_write	= fb_sys_write,
	.fb_check_var	= applitefb_check_var,
	.fb_set_par	= applitefb_set_par,
	.fb_setcolreg	= applitefb_setcolreg,
	.fb_pan_display	= applitefb_pan_display,
	.fb_fillrect	= sys_fillrect,
	.fb_copyarea	= sys_copyarea,
	.fb_imageblit	= sys_imageblit,
	.fb_mmap	= applitefb_mmap,
	.fb_ioctl	= applitefb_ioctl,
};

/*
 *  Initialization
 */
static int __devinit applitefb_probe(struct platform_device *pdev)
{
	int i, retval = -ENOMEM;
	dma_addr_t in_baseaddr = 0;
	struct resource *lcdc, *pmu;
#if IS_ENABLED(CONFIG_FB_TZ2000)
	struct resource *gfx;
#endif
	struct fb_bitfield red		= {16, 8, 0};
	struct fb_bitfield green	= { 8, 8, 0};
	struct fb_bitfield blue		= { 0, 8, 0};
	struct fb_bitfield transp	= {24, 8, 0};

	_FNC_START("\n");

	memset(&priv, 0, sizeof(struct applitefb_dev));

	priv.dev = &pdev->dev;

	/* Mapping to PMU register */
	pmu = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!pmu) {
		_ERR_LOG("platform_get_resource() failed [pmu]\n");
		retval = -ENOENT;
		goto fail_1;
	}
	priv.pmu_regs = ioremap_nocache(pmu->start, resource_size(pmu));
	if (!priv.pmu_regs) {
		dprint("%s : ioremap_nocache() failed [pmu]\n", FB_DEVICE_NAME);
		goto fail_1;
	}

	/* Mapping to LCDC register */
	lcdc = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (!lcdc) {
		_ERR_LOG("platform_get_resource() failed [lcdc]\n");
		retval = -ENOENT;
		goto fail_1;
	}
	priv.lcdc_regs = ioremap_nocache(lcdc->start, resource_size(lcdc));
	if (!priv.lcdc_regs) {
		_ERR_LOG("ioremap_nocache() failed [lcdc]\n");
		goto fail_1;
	}

#if IS_ENABLED(CONFIG_FB_TZ2000)
	/* Mapping to GFX register */
	gfx = platform_get_resource(pdev, IORESOURCE_MEM, 2);
	if (!gfx) {
		_ERR_LOG("platform_get_resource() failed [gfx]\n");
		retval = -ENOENT;
		goto fail_1;
	}
	priv.gfx_regs = ioremap_nocache(gfx->start, resource_size(gfx));
	if (!priv.gfx_regs) {
		_ERR_LOG("ioremap_nocache() failed [gfx]\n");
		goto fail_1;
	}
#endif

	for (i = 0; i < CONFIG_APPLITEFB_ENABLE_LAYER; i++) {
		/* Memory reservation for framebuffer structure */
		priv.info[i] = framebuffer_alloc(sizeof(struct fb_info),
			&pdev->dev);
		if (!priv.info[i]) {
			_ERR_LOG("fb%d : framebuffer_alloc() failed\n", i);
			goto fail_2;
		}

		priv.info[i]->fix = applitefb_fix;
#if IS_ENABLED(CONFIG_FB_TZ2000)
		if (i != 0)
			priv.info[i]->fix.accel = FB_ACCEL_NONE;
#endif
		priv.info[i]->var.xres = xres;
		priv.info[i]->var.yres = yres;

		/* Memory reservation for input framebuffer */
#if IS_ENABLED(CONFIG_FB_TZ3000)
		g_out_baseaddr_offset[i] = 0;
		if (i == 0)
			g_display_mode = get_display_mode(&priv.info[i]->var) - 1;
#endif

#if IS_ENABLED(CONFIG_FB_TZ2000)
		if (i == GFX_DEVICE) {
			g_max_fb_size[i] = (MAX_XRES * MAX_YRES * magnification * MAX_BPP / 8);
			g_fb_layer[i].vram = applitefb_alocate_memory_framebuffer(g_max_fb_size[i] + gfx_size,
				&in_baseaddr);
		} else
#endif
		{
			g_max_fb_size[i] = xres * yres * magnification * DEFAULT_BPP / 8;
			g_fb_layer[i].vram = applitefb_alocate_memory_framebuffer(g_max_fb_size[i],
				&in_baseaddr);
		}

		if (!g_fb_layer[i].vram) {
			_ERR_LOG("fb%d : applitefb_alocate_memory_framebuffer()failed [in]\n", i);
			goto fail_2;
		}
#if IS_ENABLED(CONFIG_FB_TZ2000)
		if (i == GFX_DEVICE) {
			priv.info[i]->fix.smem_len =
				ALIGN(g_max_fb_size[i] + gfx_size, PAGE_SIZE);
		} else
#endif
		{
			priv.info[i]->fix.smem_len =
				ALIGN(g_max_fb_size[i], PAGE_SIZE);
		}

		priv.info[i]->screen_base =
				(char __iomem *)g_fb_layer[i].vram;
		priv.info[i]->fix.smem_start = (unsigned long)in_baseaddr;
		g_fb_layer[i].addr[0] = (__u32)in_baseaddr;

		priv.info[i]->fbops = &applite_speyfb_ops;
		priv.info[i]->flags = FBINFO_DEFAULT;

		priv.info[i]->fix.line_length = xres * (DEFAULT_BPP / 8);

		/* search fb_mode from DB */
		if (i == 0) {
#if IS_ENABLED(CONFIG_FB_TZ2000)
			retval = fb_find_mode(&priv.info[i]->var, priv.info[i],
				NULL, NULL, 0, NULL, DEFAULT_BPP);
#elif IS_ENABLED(CONFIG_FB_TZ3000)
			retval = fb_find_mode(&priv.info[i]->var, priv.info[i],
				NULL, modedb,  ARRAY_SIZE(modedb),
				NULL, DEFAULT_BPP);
#endif
			_DEV_LOG("fb_find_mode() = %d\n", i, retval);
			if (!retval || retval == 4) {
				priv.info[i]->var = applitefb_var;
#if IS_ENABLED(CONFIG_FB_TZ3000)
				priv.info[i]->var.yres_virtual *= magnification;
#endif
				_DEV_LOG("default var setting[rtn=%d]\n",
					i, retval);
			}
		}
		priv.info[i]->var.activate = FB_ACTIVATE_FORCE;
		priv.info[i]->var.bits_per_pixel = DEFAULT_BPP;
		priv.info[i]->var.red = red;
		priv.info[i]->var.green = green;
		priv.info[i]->var.blue = blue;
		priv.info[i]->var.transp = transp;
		priv.info[i]->var.xres = xres;
		priv.info[i]->var.yres = yres;
		priv.info[i]->var.xres_virtual = priv.info[i]->var.xres;
		priv.info[i]->var.yres_virtual =
				priv.info[i]->var.yres * magnification;
		priv.info[i]->par = &g_fb_layer[i];
		g_fb_layer[i].layer = i;
		g_fb_layer[i].format = ARGB8888;
		g_fb_layer[i].line_length[0] = 0;
		g_fb_layer[i].xoffset = 0;
		g_fb_layer[i].yoffset = 0;
		g_fb_layer[i].xpos = 0;
		g_fb_layer[i].ypos = 0;
		g_fb_layer[i].xpos_old = 0;
		g_fb_layer[i].ypos_old = 0;

		calculate_display_position(i, &priv.info[i]->var);
		/* call function of framework */
		retval = register_framebuffer(priv.info[i]);
		if (retval < 0) {
			_ERR_LOG("fb%d : register_framebuffer() failed[rtn=%d]\n",
				i, retval);
			goto fail_2;
		}

		applitefb_check_var(&priv.info[i]->var, priv.info[i]);
		g_fb_layer[i].line_length[0] = priv.info[i]->var.xres_virtual *
			priv.info[i]->var.bits_per_pixel / 8;
	}
#if IS_ENABLED(CONFIG_FB_TZ2000)
	priv.is_rgba = false;
#endif
	priv.xres = xres;
	priv.yres = yres;

	spin_lock_init(&priv.lcdc_slock);
#if IS_ENABLED(CONFIG_FB_TZ3000)
	probe_flag = 0;
	plane_a_layer = 0;
	plane_b_layer = 1;
	g_max_fb_out_size = g_disp_xres * g_disp_yres * DEFAULT_BPP / 8;
	/* Memory reservation for output framebuffer */
	g_out_vram = applitefb_alocate_memory_framebuffer(g_max_fb_out_size,
		(dma_addr_t *)&g_out_baseaddr);
	if (!g_out_vram) {
		_ERR_LOG("dma_alloc_coherent()failed [output]\n");
		retval = -ENOMEM;
		goto fail_2;
	}
#endif

	init_completion(&priv.vsync_completion);
	init_completion(&priv.fconva_frame_end_completion);
	init_completion(&priv.fconvb_frame_end_completion);
	mutex_init(&applitefb_lock);

	/* Registration interrupt handler */
	regist_irq(pdev);

	priv.pdev = pdev;
	priv.clk_dispif = clk_get(&(pdev->dev), "lcdc");
	if (IS_ERR(priv.clk_dispif)) {
		_ERR_LOG("clk_get(%s, dispif) failed\n",
					dev_name(&(pdev->dev)));
		/* Release of interruption */
		_free_irq(pdev);
		retval = -EFAULT;
		goto fail_2;
	}
#if IS_ENABLED(CONFIG_FB_TZ2000)
	priv.clk_gfx = clk_get(&(pdev->dev), "gfx");
	if (IS_ERR(priv.clk_gfx)) {
		_ERR_LOG("clk_get(%s, gfx) failed\n", dev_name(&(pdev->dev)));
		/* Release of interruption */
		_free_irq(pdev);
		clk_put(priv.clk_dispif);
		retval = -EFAULT;
		goto fail_2;
	}
#endif

	retval = applitefb_sysfs_init();
	if (retval) {
		_ERR_LOG("applitefb_sysfs_init failed[%d]\n", retval);
		/* Release of interruption */
		_free_irq(pdev);
		clk_put(priv.clk_dispif);
		goto fail_3;
	}

#if IS_ENABLED(CONFIG_FB_TZ2000)
	tz2000gfx_init();
#endif
	_DBG_LOG("pm_runtime_enable start\n");
	pm_runtime_enable(&(pdev->dev));

#if IS_ENABLED(CONFIG_PM_RUNTIME)
	_DBG_LOG("pm_runtime_get_sync start\n");
	/* call applitefb_runtime_resume() directly */
	pm_runtime_get_sync(&(pdev->dev));
#else
	applitefb_runtime_resume(&(pdev->dev));
#endif

	/* setting of register */
	applitefb_lcdc_finalize();
	applitefb_lcdc_initialize(&priv.info[0]->var);

	return 0;
fail_3:
	kobject_put(applitefb_kobj);
fail_2:
	for (i = 0; i < CONFIG_APPLITEFB_ENABLE_LAYER; i++) {
		if (priv.info[i]) {
			/* call function of framework */
			unregister_framebuffer(priv.info[i]);
			framebuffer_release(priv.info[i]);
		}
	}
	/* release memory for input */
	for (i = 0; i < CONFIG_APPLITEFB_ENABLE_LAYER; i++) {
		applitefb_release_memory_framebuffer(i, g_max_fb_size[i],
			g_fb_layer[i].vram, (dma_addr_t)g_fb_layer[i].addr[0]);
	}
#if IS_ENABLED(CONFIG_FB_TZ3000)
	/* release memory for output */
	applitefb_release_memory_framebuffer(-1, g_max_fb_out_size,
		g_out_vram, (dma_addr_t)g_out_baseaddr);
#endif
fail_1:
#if IS_ENABLED(CONFIG_FB_TZ2000)
	if (priv.gfx_regs) {
		iounmap(priv.gfx_regs);
		dprint("%s : iounmap() success [gfx]\n", FB_DEVICE_NAME);
	}
#endif
	if (priv.pmu_regs) {
		iounmap(priv.pmu_regs);
		dprint("%s : iounmap() success [pmu]\n", FB_DEVICE_NAME);
	}
	if (priv.lcdc_regs) {
		iounmap(priv.lcdc_regs);
		dprint("%s : iounmap() success [lcdc]\n", FB_DEVICE_NAME);
	}
	priv.fail = 1;
	_FNC_END("failed [rtn = %d]\n", retval);
	return retval;
}

/*
 *  Cleanup
 */
static int __devexit applitefb_remove(struct platform_device *pdev)
{
	int i;

	dprint("%s : enter applitefb_remove()\n", FB_DEVICE_NAME);

	if (priv.fail)
		return 0;

	_FNC_START("\n");
	if (priv.info[0]) {
		applitefb_lcdc_finalize();

#if IS_ENABLED(CONFIG_FB_TZ2000)
		tz2000gfx_exit();
#endif
#if IS_ENABLED(CONFIG_PM_RUNTIME)
		/* call applitefb_runtime_suspend() directly */
		_DBG_LOG("pm_runtime_put_sync start\n");
		pm_runtime_put_sync(&(pdev->dev));
#else
		applitefb_runtime_suspend(&(pdev->dev));
#endif
		_DBG_LOG("pm_runtime_disable start\n");
		pm_runtime_disable(&(pdev->dev));
		clk_put(priv.clk_dispif);
#if IS_ENABLED(CONFIG_FB_TZ2000)
		clk_put(priv.clk_gfx);
#endif

#if IS_ENABLED(CONFIG_FB_TZ2000)
		if (priv.gfx_regs)
			iounmap(priv.gfx_regs);
#endif
		if (priv.pmu_regs)
			iounmap(priv.pmu_regs);
		if (priv.lcdc_regs)
			iounmap(priv.lcdc_regs);

		/* Release of interruption */
		_free_irq(pdev);
	}
	for (i = 0; i < CONFIG_APPLITEFB_ENABLE_LAYER; i++) {
		struct applitefb_layer *layer = (struct applitefb_layer *)(priv.info[i]->par);
		applitefb_release_memory_framebuffer(i, g_max_fb_size[i],
			layer->vram, (dma_addr_t)(priv.info[i]->fix.smem_start));
		/* call function of framework */
		unregister_framebuffer(priv.info[i]);

		framebuffer_release(priv.info[i]);
	}
#if IS_ENABLED(CONFIG_FB_TZ3000)
	/* release memory for output */

	applitefb_release_memory_framebuffer(-1, g_max_fb_out_size, g_out_vram,
		(dma_addr_t)g_out_baseaddr);
#endif

	applitefb_sysfs_exit();

	_FNC_END("\n");
	return 0;
}

#ifdef CONFIG_PM
static int applitefb_suspend(struct device *dev)
{
	_FNC_START("refcount:%ld\n",
			module_refcount(dev->driver->owner->mkobj.mod));
	if (module_refcount(dev->driver->owner->mkobj.mod) > 0)
		return -EBUSY;

	applitefb_lcdc_finalize();
	applitefb_hw_stop();
	return 0;
}

static int applitefb_resume(struct device *dev)
{
	_FNC_START("\n");

	applitefb_hw_start();
	/* setting of register */
	applitefb_lcdc_finalize();
	applitefb_lcdc_initialize(&priv.info[0]->var);

	return 0;
}

static int applitefb_freeze(struct device *dev)
{
	applitefb_lcdc_finalize();
	applitefb_hw_stop();

	return 0;
}

static const struct dev_pm_ops applitefb_pm_ops = {
	.suspend = applitefb_suspend,
	.resume = applitefb_resume,
	.freeze = applitefb_freeze,
	.thaw = applitefb_resume,
	.restore = applitefb_resume,
#if IS_ENABLED(CONFIG_PM_RUNTIME)
	.runtime_suspend = applitefb_runtime_suspend,
	.runtime_resume = applitefb_runtime_resume,
#endif /* IS_ENABLED(CONFIG_PM_RUNTIME) */
};

#endif

static struct platform_driver applitefb_driver = {
	.probe = applitefb_probe,
	.remove = applitefb_remove,
	.driver = {
		.name = "applitefb",
		.owner = THIS_MODULE,
#ifdef CONFIG_PM
		.pm = &applitefb_pm_ops,
#endif
	},
};


static int __init applitefb_init(void)
{
	int ret;
	dprint("%s : enter applitefb_init()\n", FB_DEVICE_NAME);
	/* registration driver of framebuffer */
	ret = platform_driver_register(&applitefb_driver);

	dprint("%s : leave applitefb_init()\n", FB_DEVICE_NAME);
	return ret;
}

static void __exit applitefb_exit(void)
{
	dprint("%s : enter applitefb_exit()\n", FB_DEVICE_NAME);
	/* Unregistration driver of framebuffer */
	platform_driver_unregister(&applitefb_driver);
	dprint("%s : leave applitefb_exit()\n", FB_DEVICE_NAME);
}


module_init(applitefb_init);
module_exit(applitefb_exit);

