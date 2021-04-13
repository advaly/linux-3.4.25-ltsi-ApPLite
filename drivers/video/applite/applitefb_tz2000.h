/*
 * linux/drivers/video/applite/applitefb_tz2000.h
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
#if !defined(__APPLITE_FB_TZ2000_H__)
#define __APPLITE_FB_TZ2000_H__

#if IS_ENABLED(CONFIG_FB_TZ2000)

#include <linux/types.h>


#define DEVICE_MAX			5	/* fb0 - fb4 */
#define GFX_DEVICE			0	/* GFX for fb0 */
#define NOT_GFX_DEVICE			-1
#if IS_ENABLED(CONFIG_FB_APPLITE_PANEL_F07A_0102)
#define MAX_XRES			800
#define MAX_YRES			480
#define DISPLAY_MODE			1
#elif IS_ENABLED(CONFIG_FB_APPLITE_PANEL_NHD4_3) || \
	IS_ENABLED(CONFIG_FB_APPLITE_PANEL_NHD4_3_59) || \
	IS_ENABLED(CONFIG_FB_APPLITE_PANEL_NHD4_3_29) || \
	IS_ENABLED(CONFIG_FB_APPLITE_PANEL_ILI6480G2_59) || \
	IS_ENABLED(CONFIG_FB_APPLITE_PANEL_ILI6480G2_29)
#define MAX_XRES			480
#define MAX_YRES			272
#define DISPLAY_MODE			0
#endif	/* CONFIG_FB_APPLITE_PANEL_xxx */

#define DEFAULT_XRES			MAX_XRES
#define DEFAULT_YRES			MAX_YRES
#define DEFAULT_FIX_XRES		MAX_XRES
#define DEFAULT_FIX_YRES		MAX_YRES

/* format type */
#define RGB565				0
#define ARGB8888			1
#define RGBA8888			2

/* Interruption number */
#define IRQ_LCDC(x)			(179 + (x))	/* 179 - 180 */

/* base address of register */
#define TZ2000_LCDC_BASE		0x0a000000
#define TZ2000_LCDC_SIZE		0x00001000

/* GDCDCR_L */
#define HDISP_MODE			0x00000001
#define CSYNC				0x00000008
#define DOTCLOCK_SELECT			0x00002000
#define DOTCLOCK_POLARITY		0x00001000
#define LAYER_A_EN			0x01000000
#define LAYER_A_FORMAT_IS_16BIT		0x00100000	/* 0:32bit(RGBAorARGB) 1:16bit(RGB) */
#if (CONFIG_APPLITEFB_ENABLE_LAYER > 1)
	#define LAYER_B_EN		0x04000000
#else
	#define LAYER_B_EN		0x00000000
#endif	/* CONFIG_APPLITEFB_ENABLE_LAYER > 1 */

#if (CONFIG_APPLITEFB_ENABLE_LAYER > 2)
	#define LAYER_C_EN		0x10000000
#else
	#define LAYER_C_EN		0x00000000
#endif	/* CONFIG_APPLITEFB_ENABLE_LAYER > 2 */

#if (CONFIG_APPLITEFB_ENABLE_LAYER > 3)
	#define LAYER_D_EN		0x40000000
#else
	#define LAYER_D_EN		0x00000000
#endif	/* CONFIG_APPLITEFB_ENABLE_LAYER > 3 */
#if (CONFIG_APPLITEFB_ENABLE_LAYER > 4)
	#define LAYER_E_EN		0x00000001
#else
	#define LAYER_E_EN		0x00000000
#endif	/* CONFIG_APPLITEFB_ENABLE_LAYER > 4 */

#define LAYER_B_FORMAT_IS_16BIT		0x00200000	/* 0:32bit(RGBAorARGB) 1:16bit(RGB) */
#define LAYER_C_FORMAT_IS_16BIT		0x00400000	/* 0:32bit(RGBAorARGB) 1:16bit(RGB) */
#define LAYER_D_FORMAT_IS_16BIT		0x00800000	/* 0:32bit(RGBAorARGB) 1:16bit(RGB) */
#define GDCDCR_L_CLEAR			0x00000000

/* GDCDCR_U */
#define GDC_ON				0x80000000
#define LAD				0x00200000
#define BIT_FORMAT_IS_32		0x00100000
#define LAYER_E_FORMAT_IS_16BIT		0x00000010	/* 0:32bit(RGBAorARGB) 1:16bit(RGB) */
#define GDCDCR_U_CLEAR			0x00000000

/* GDCLSRx_L */
#define _LHS(h)				((__u32)h << 16)
#define _LVS(v)				((__u32)v <<  0)
#define _MK_GDCLSRx_L(h, v)		(_LHS(h) | _LVS(v))

/* GDCLDRx_L */
#define _LWIDTH(w)			((__u32)w << 16)
#define _LHEIGHT(h)			((__u32)h <<  0)
#define _MK_GDCLDRx_L(w, h)		(_LWIDTH(w) | _LHEIGHT(h))

/* GDCINTR_L */
#define DATA_LOAD_END_IRQ		0x80000000
#define DATA_LOAD_END_IRQ_MASK		0x08000000
#define HSYNC_IRQ_IS_256		0x01000000
#define GDC_ERR_IRQ_FLAG		0x00008000
#define VSYNCROCK_IRQ_FLAG		0x00004000
#define OUTPUT_FIFO_IRQ_FLAG		0x00002000
#define INPUT_FIFO_IRQ_FLAG		0x00001000
#define GDC_ERR_IRQ_MASK		0x00000800
#define VSYNCROCK_IRQ_MASK		0x00000400
#define OUTPUT_FIFO_IRQ_MASK		0x00000200
#define INPUT_FIFO_IRQ_MASK		0x00000100
#define GBUS_ERR_IRQ_FLAG		0x00000080
#define VSYNC_IRQ_FLAG			0x00000040
#define HSYNC_IRQ_FLAG			0x00000020
#define GAPIF_IRQ_FLAG			0x00000010
#define GBUS_ERR_IRQ			0x00000008
#define VSYNC_IRQ_MASK			0x00000004
#define HSYNC_IRQ_MASK			0x00000002
#define GAPIF_IRQ_MASK			0x00000001
#define GDCINTR_L_CLEAR			0x00000000
#define IRQ_FLAG			(GDC_ERR_IRQ_FLAG |		\
					 VSYNCROCK_IRQ_FLAG |		\
					 OUTPUT_FIFO_IRQ_FLAG |		\
					 INPUT_FIFO_IRQ_FLAG |		\
					 GBUS_ERR_IRQ_FLAG |		\
					 VSYNC_IRQ_FLAG |		\
					 HSYNC_IRQ_FLAG |		\
					 GAPIF_IRQ_FLAG)

#define IRQ_MASK			(DATA_LOAD_END_IRQ_MASK |	\
					 GDC_ERR_IRQ_MASK |		\
					 VSYNCROCK_IRQ_MASK |		\
					 OUTPUT_FIFO_IRQ_MASK |		\
					 INPUT_FIFO_IRQ_MASK |		\
					 GBUS_ERR_IRQ |			\
					 VSYNC_IRQ_MASK |		\
					 HSYNC_IRQ_MASK |		\
					 GAPIF_IRQ_MASK)
/* GDCINTR_U */
#define PIXELCHECK_ERR_IRQ_FLAG		0x00000020
#define PIXELCHECK_EVENT_IRQ_FLAG	0x00000010
#define PIXELCHECK_ERR_IRQ		0x00000002
#define PIXELCHECK_EVENT_IRQ		0x00000001
#define GDCINTR_U_CLEAR			0x00000000

/* PMU */
#define CLOCKGATINGON			0x00000101
#define SOFTRESETON			0x00000001
#define PLLCONFIG0_ALLOC		0xa7153000
#define PLLCONFIG1_ALLOC		0x0001014a

#if IS_ENABLED(CONFIG_FB_APPLITE_PANEL_F07A_0102)
#define PANELCLOCK_VAL			0x00000002
#define PLLCONFIG0_VAL			0x27153000
#define PLLCONFIG1_VAL			0x0000014a
#elif IS_ENABLED(CONFIG_FB_APPLITE_PANEL_NHD4_3)
#define PANELCLOCK_VAL			0x00000001
#define PLLCONFIG0_VAL			0xa7153000
#define PLLCONFIG1_VAL			0x0001014a
#elif IS_ENABLED(CONFIG_FB_APPLITE_PANEL_NHD4_3_59)
#define PANELCLOCK_VAL			0x00000003
#define PLLCONFIG0_VAL			0xa70c3200
#define PLLCONFIG1_VAL			0x000e0435
#elif IS_ENABLED(CONFIG_FB_APPLITE_PANEL_NHD4_3_29)
#define PANELCLOCK_VAL			0x00000003
#define PLLCONFIG0_VAL			0xa70c3200
#define PLLCONFIG1_VAL			0x000e0423
#elif IS_ENABLED(CONFIG_FB_APPLITE_PANEL_ILI6480G2_59)
#define PANELCLOCK_VAL			0x00000003
#define PLLCONFIG0_VAL			0xa70c3200
#define PLLCONFIG1_VAL			0x000e0435
#elif IS_ENABLED(CONFIG_FB_APPLITE_PANEL_ILI6480G2_29)
#define PANELCLOCK_VAL			0x00000000
#define PLLCONFIG0_VAL			0xa7153100
#define PLLCONFIG1_VAL			0x0001033b
#endif	/* CONFIG_FB_APPLITE_PANEL_xxx */

#define REGISTER_NUM			57

/*===================================
Exported Functions prototypes
===================================*/

/*===================================
Exported Variable prototypes
===================================*/


#endif	/* IS_ENABLED(CONFIG_FB_TZ2000) */

#endif	/*__APPLITE_FB_TZ2000_H__*/

