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
#if !defined(__APPLITE_FB_TZ3000_H__)
#define __APPLITE_FB_TZ3000_H__

#if IS_ENABLED(CONFIG_FB_TZ3000)

#include <linux/types.h>

#define DEVICE_MAX			2	/* fb0,fb1 */
#define MAX_XRES			1920
#define MAX_YRES			1080
#define DEFAULT_XRES			1920
#define DEFAULT_YRES			1080
#define DEFAULT_FIX_XRES		1920
#define DEFAULT_FIX_YRES		1080


/* type of plane */
#define FCONVA				0
#define FCONVB				1

/* format type */
#define BGR565				0x00000010
#define RGB565				0x00010010
#define ABGR1555			0x00020010
#define ARGB1555			0x00030010
#define ABGR8888			0x00040010
#define ARGB8888			0x00050010
#define AYCBCR32			0x00000011
#define YCBCR420			0x00000013
#define Y_CBCR420			0x00000023
#define Y_CB_CR444			0x00000031
#define Y_CB_CR422			0x00000032
#define Y_CB_CR420			0x00000033

/* merge type */
#define MERGE_DISABLE_FB0_OUT		0
#define MERGE_DISABLE_FB1_OUT		1
#define FB1_BACKGROUND_MERGE		2
#define FB0_BACKGROUND_MERGE		3


/* Interruption number */
#define IRQ_DISPIF1(x)			(176 + (x))	/* 176 - 183 */
#define IRQ_DISPIF2(x)			(248 + (x))	/* 248 - 249 */
#define IRQ_DISPIF_INTFRAME		182
#define IRQ_DISPIF_INTERR		183

/* base address of register */
#define TZ3000_DISPIF_BASE		0x0B120000
#define TZ3000_DISPIF_SIZE		0x4000

/* Command queue Setting Table */
#define COMMANDQUEUE_MAX		45

/* ClockGatingOff_dispifSS_0 */
#define PMU_CGATE_ECLK			0x00000001
#define PMU_CGATE_DCLK			0x00000100

/* SoftResetOff_dispifSS_0 */
#define PMU_SRST_ERST			0x00000002
#define PMU_SRST_ASYNCERST		0x00000001

/* DISPIF_CGATE */
#define MDI_CGATE			0x00000100
#define DTG_CGATE			0x00000010
#define DSITX_CGATE			0x00000002
#define DSITX_HS_CGATE			0x00000001
#define CGATE_ON			0x00000000

/* DSI_START */
#define DSI_START			0x00000001

/* DSI_PAUSE */
#define DSI_PAUSE			0x00000001

/* DSI_CLEAR */
#define DSI_CLEAR			0xffffffff

/* DSI_RESET */
#define RST_LPFIFO			0x00000020
#define RST_RXFIFO			0x00000010
#define RST_CQ1				0x00000008
#define RST_CQ0				0x00000004
#define RST_CONF			0x00000002

/* DSI_CONTINUE */
#define DSI_CONTINUE			0x00000001

/* DTG_START */
#define DTG_START			0x00000001

/* DTG_STOP */
#define DTG_STOP			0x00000001

/* IRQ_EN */
#define VSYNC_IRQ			0x01000000
#define VBLK_EDGE_IRQ			0x00100000
#define HBLK_START_IRQ3			0x00010000
#define HBLK_START_IRQ2			0x00001000
#define HBLK_START_IRQ1			0x00000100
#define VBLK_START_IRQ			0x00000010
#define VBLK_END_IRQ			0x00000001
#define IRQ_EN_CLEAR			0x00000000
#define IRQ_EN_ERASE			0xffffffff

#define FRAME_TRANSFER_END		0x00000001

/* IRQ_STA */
#define VSYNC_IRQ_STAT			0x01000000
#define VBLK_EDGE_IRQ_STAT		0x00100000
#define HBLK_START_IRQ3_STAT		0x00010000
#define HBLK_START_IRQ2_STAT		0x00001000
#define HBLK_START_IRQ1_STAT		0x00000100
#define VBLK_START_IRQ_STAT		0x00000010
#define VBLK_END_IRQ_STAT		0x00000001
#define IRQ_STAT_CLEAR			0x00000000

/* DSI_INT */
#define DSI_INT_MASK			0xffffffff

/* FCONVA/B_IRQ */
#define MERGE_ERR_IRQ			0x00000080
#define OUTPUT_DELAY_IRQ		0x00000040
#define REGISTER_SET_ERR_IRQ		0x00000020
#define START_TIMING_ERR_IRQ		0x00000010
#define FRAME_TRANSFER_END_IRQ		0x00000001
#define FCONVA_IRQ_CLEAR		0x00000000
#define FCONVB_IRQ_CLEAR		0x00000000

/* LANE DISABLE */
#define LANE_DISABLE			0x00000000

/* FCONVA/B setting */
#define C_OFFSET_IS_128			0x00800000
#define C00_IS_128			0x00000080
#define C01_IS_0			0x00000000
#define C02_IS_179			0x000000b3
#define C10_IS_128			0x00000080
#define C11_IS_980			0x000003d4
#define C12_IS_933			0x000003a5
#define C20_IS_128			0x00000080
#define C21_IS_229			0x000000e5
#define C22_IS_0			0x00000000
#define Y2R_RGBLIMIT_IS_255		0x000000ff
#define FORCE_MODE_NOT_USE		0x00000000
#define FORCE_GY0_IS_0			0x00000000
#define FORCE_BCB0_IS_0			0x00000000
#define FORCE_RCR0_IS_0			0x00000000
#define FORCE_BCB0_IS_128		0x00000080
#define FORCE_RCR0_IS_128		0x00000080
#define ALPHA_IS_0			0x00000000
#define CROP0_IS_0			0x00000000

/* FCONVC setting */
#define FCONVC_ACT_ON			0x00000001
#define FCONVC_SETTING_ALL0		0x00000000
#define CHANNEL_IS_0			0x00000000
#define FIELD_IS_TOP			0x00000000
#define ALPHAMODE_IS_0			0x00000000
#define DSIERRFIXVAL_IS_0		0x00000000
#define MERGE_EN			0x00000001
#define ALPHAMODEA_IS_0			0x00000000
#define ALPHAMODEA_IS_3			0x0000000c
#define ALPHAMODEB_IS_0			0x00000000
#define ALPHAMODEB_IS_3			0x00000003

/* FCONVA_SET_IRQ_MASK */
#define FRAME_END_MASK			0x00000001
#define START_ERROR_MASK		0x00000010
#define REGSET_ERROR_MASK		0x00000020
#define DISP_ERROR_MASK			0x00000040
#define MERGE_ERROR_MASK		0x00000080

/* FCONVA_SET_IRQ */
#define IRQ_CLEAR			0x00000000
#define IRQ__MASK_CLEAR			0x000000d1

#define REGISTER_NUM			334

/* DPHY Lane setting */
#define DPHY_LANE_CLW			0x00000200
#define DPHY_LANE_D0W			0x00000212
#define DPHY_LANE_D1W			0x00000202
#define DPHY_LANE_D2W			0x00000202
#define DPHY_LANE_D3W			0x00000202

/* FCONVA/FCONVB SIZE setting */
#define HSIZE_MINIMUM_VALUE		16
#define VSIZE_MINIMUM_VALUE		8

/* NOP COUNT */
#define NOP_COUNT_MAX			8

/* DTG_STAT READ LOOP COUNT */
#define DTG_STAT_READ_MAX		50

/*===================================
Exported Functions prototypes
===================================*/

/*===================================
Exported Variable prototypes
===================================*/

#endif	/* IS_ENABLED(CONFIG_FB_TZ3000) */

#endif	/*__APPLITE_FB_TZ3000_H__*/

