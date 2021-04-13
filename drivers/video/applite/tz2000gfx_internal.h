/*
 * linux/drivers/video/applite/tz2000gfx_internal.h
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

#ifndef __TZ2000_H__
#define __TZ2000_H__


#undef __DBG_TZ2000GFX__
#undef __TEST_TZ2000GFX__


#include <linux/fb.h>

#include "tz2000_regs.h"

#define TZ2000_ALL_INTERRUPT		(GAICR_CSLUI_MASK | \
					 GAICR_GARBI_MASK | \
					 GAICR_GACBI_MASK | \
					 GAICR_GAWBRI_MASK | \
					 GAICR_GAWBWI_MASK | \
					 GAICR_CSLEI_MASK | \
					 GAICR_CSCEI_MASK | \
					 GAICR_GACENDI_MASK)

#define TZ2000_ERR_INTERRUPT		(GAICR_GARBI_MASK | \
					 GAICR_GACBI_MASK | \
					 GAICR_GAWBRI_MASK | \
					 GAICR_GAWBWI_MASK | \
					 GAICR_CSCEI_MASK)


#define ENGINE(v)			MK_VAL64(v, 3, 60)
#define ENGINE_CS			ENGINE(0)
#define ENGINE_BE			ENGINE(1)
#define ENGINE_DE			ENGINE(2)
#define ENGINE_RE			ENGINE(3)
#define ENGINE_TE			ENGINE(4)
#define LENGTH(v)			MK_VAL64(v, 4, 56)
#define LEN_DW				LENGTH(1)
#define CODE(v)				MK_VAL64(v, 8, 48)
#define SPEC(v)				MK_VAL64(v, 5, 32)


/*** Command Scheduler Commands ***/
#define CODE_LGPR			CODE(0x01)
#define CODE_CSWVSYNC			CODE(0x02)
#define CODE_CSUIC			CODE(0x03)
#define CODE_CSGDC0CC			CODE(0x04)
#define CODE_CSGDC1CC			CODE(0x05)
#define CODE_CSEND			CODE(0xFF)

/* Load General Purpose Register Command */
/* g   : number of general-purpose register (0 - 31) */
/* v   : write data (32bit) */
#define C_LGPR(g, v)			\
			(ENGINE_CS | LEN_DW | CODE_LGPR | SPEC(g) | (__u32)(v))

/* Command Scheduler Wait VSYNC Command */
/* v   : VSYNC select (GDC0, FG0, GDC1) */
#define C_CSWVSINC(v)			\
			(ENGINE_CS | LEN_DW | CODE_CSWVSYNC | ((v) & 0x3))
#define VSYNC_SELECT_GDC0		(0)
#define VSYNC_SELECT_FG0		(1)
#define VSYNC_SELECT_GDC1		(2)

/* Command Scheduler User Interrupt Command */
/* v   : interrupt number (0 - 23) */
#define C_CSUIC(v)			\
			(ENGINE_CS | LEN_DW | CODE_CSUIC | ((v) & 0x3F))

/* Command Scheduler GDC0 Configuration Command */
/* r   : GDC0 register address */
/* v   : write data */
#define C_CSGDC0CC(r, v)		\
			(ENGINE_CS | LEN_DW | CODE_CSGDC0CC | \
			 MK_VAL64(r, 16, 32) | MK_VAL64(v, 32, 0))

/* Command Scheduler GDC1 Configuration Command */
/* r   : GDC1 register address */
/* v   : write data */
#define C_CSGDC1CC(r, v)		 \
			(ENGINE_CS | LEN_DW | CODE_CSGDC1CC | \
			 MK_VAL64(r, 16, 32) | MK_VAL64(v, 32, 0))

/* Command Scheduler END Command */
#define C_CSEND		(ENGINE_CS | LEN_DW | CODE_CSEND)


/*** Blitting Engine ***/
#define CODE_BLITO16			CODE(0x02)
#define CODE_BLITB16			CODE(0x03)
#define CODE_BLITO32			CODE(0x04)
#define CODE_BLITBRLEI24		CODE(0x05)
#define CODE_BLITORLEI24		CODE(0x06)
#define CODE_BLITB32			CODE(0x07)
#define CODE_BLITORLEI16		CODE(0x0A)
#define CODE_BLITBRLEI16		CODE(0x0B)
#define CODE_BLITORLEI32		CODE(0x0C)
#define CODE_BLITBRLEI32		CODE(0x0D)
#define CODE_BLITORLEI24A		CODE(0x0E)
#define CODE_BLITBRLEI24A		CODE(0x0F)
#define CODE_BLITOP16			CODE(0x12)
#define CODE_BLITBP16			CODE(0x13)
#define CODE_BLITOP32			CODE(0x14)
#define CODE_BLITBP32			CODE(0x17)

#define BE_CLIP_START_REG		(0)
#define BE_CLIP_WIDTH_REG		(1)
#define BE_CLIP_WIDTH_MASK		MK_MASK(12, 0)
#define BE_CLIP_HEIGHT_REG		(2)
#define BE_CLIP_HEIGHT_MASK		MK_MASK(12, 0)
#define BE_DST_ADR_REG			(4)
#define BE_DST_MEM_WIDTH_REG		(5)
#define BE_DST_WIDTH_MASK		MK_MASK(12, 0)
#define BE_DST_DOT_CNT_REG		(6)
#define BE_DST_DOT_CNT_MASK		MK_MASK(12, 0)
#define BE_DST_LINE_CNT_REG		(7)
#define BE_DST_LINE_CNT_MASK		MK_MASK(12, 0)
#define BE_SRC_ADR_REG			(9)
#define BE_SRC_MEM_WIDTH_REG		(10)
#define BE_SRC_WIDTH_MASK		MK_MASK(12, 0)
#define BE_SRC_ALPHA_REG		(13)
#define BE_SRC_ALPHA_MAKS		MK_MASK(8, 0)
#define BE_SRC_TRANS_PAT_REG		(14)
#define BE_SRC_TRANS_PAT_MASK		MK_MASK(24, 0)
#define BE_DST_ALPHA_REG		(15)
#define BE_DST_ALPHA_MAKS		MK_MASK(8, 0)
#define BE_DST_TRANS_PAT_REG		(16)
#define BE_DST_TRANS_PAT_MASK		MK_MASK(16, 0)
#define BE_RGBA_FILL_PRESET_REG		(17)
#define BE_RGB_FILL_PRESET_REG		(18)
#define BE_RGB_FILL_PRESET_MASK		MK_MASK(16, 0)
#define BE_FADE_FACTOR_REG		(20)
#define BE_FADE_FACTOR_MAKS		MK_MASK(8, 0)
#define BE_ROP_REG			(21)
#define BE_ROP_ROM_MASK			MK_MASK(3, 16)
#define BE_ROP_ROM_VAL(v)		MK_VAL(v, 3, 16)
#define BE_ROP_ROV_MASK			MK_MASK(4, 0)
#define BE_ROP_ROV_VAL(v)		MK_VAL(v, 4, 0)
#define BE_ROP_VAL(m, v)		(MK_VAL(m, 3, 16) | MK_VAL(v, 4, 0))
#define ROP_TO_U32(rop)			BE_ROP_VAL(rop.mode, rop.value)

/* Blit Overwriting 16bit-RGB Command */
/* Blit Overwriting Run-Length Encoded Image 16bit-RGB Command */
/* Blit Overwritng Run-Length Encoded Image 24-bit RGB Command */
/* fmt : destination format (16bit-RGB, RGBA) */
/* clr : transparency colro option (disable, enable) */
/* fad : fading option (no, 4ch, alpha, rgb) */
/* clp : clipping window option (disable, enable) */
#define C_BLITO_RGB(code, fmt, clr, fad, clp)	\
		(ENGINE_BE | LEN_DW | code | MK_VAL(fmt, 1, 4) | \
		 MK_VAL(clr, 1, 3) | MK_VAL(fad, 2, 1) | MK_VAL(clp, 1, 0))

/* Blit Overwritng 32-bit RGBA Command */
/* Blit Overwritng Run-Length Encoded Image 24-bit RGBA Command */
/* Blit Overwritng Run-Length Encoded Image 32-bit RGBA Command */
/* fmt : destination format (16bit-RGB, RGBA) */
/* fad : fading option (no, 4ch, alpha, rgb) */
/* clp : clipping window option (disable, enable) */
#define C_BLITO_RGBA(code, fmt, fad, clp)	\
		(ENGINE_BE | LEN_DW | code | MK_VAL(fmt, 1, 3) | \
		 MK_VAL(fad, 2, 1) | MK_VAL(clp, 1, 0))

/* Blit Overwritng Preset 16-bit RGB Command */
/* Blit Overwritng Preset 32-bit RGBA Command */
/* fad : fading option (no, 4ch, alpha, rgb) */
/* clp : clipping window option (disable, enable) */
#define C_BLITOP_RGB(code, fad, clp)	\
		(ENGINE_BE | LEN_DW | code | MK_VAL(fad, 2, 1) | \
		 MK_VAL(clp, 1, 0))

/* Blit Blending 16-bit RGB Command */
/* Blit Blending 32-bit RGB Command */
/* Blit Blending Run-Length Encoded Image 16-bit RGB Command */
/* Blit Blending Run-Length Encoded Image 24-bit RGB Command */
/* Blit Blending Run-Length Encoded Image 24-bit RGBA Command */
/* Blit Blending Run-Length Encoded Image 32-bit RGBA Command */
/* pt  : protection(disable, enable) */
/*   r : red channel protection (disable, enable) */
/*   g : green channel protection (disable, enable) */
/*   b : blue channel protection (disable, enable) */
/*   a : alpha channel protection (disable, enable) */
/* rop : raster operation (disable, enable) */
/* fmt : destination format (16bit-RGB, RGBA) */
/* blnd: blending order (onto, behind) */
/* clr : transparency colro option (disable, enable) */
/* fad : fading option (no, 4ch, alpha, rgb) */
/* clp : clipping window option (disable, enable) */
#define C_BLITB_RGB(code, pt, rop, fmt, blnd, clr, fad, clp) \
		(ENGINE_BE | LEN_DW | code | MK_VAL(pt, 4, 7) | \
		 MK_VAL(rop, 1, 6) | MK_VAL(fmt, 1, 5) | MK_VAL(blnd, 1, 4) | \
		 MK_VAL(clr, 1, 3) | MK_VAL(fad, 2, 1) | MK_VAL(clp, 1, 0))

/* Blit Blending Preset 16-bit RGB Command */
/* Blit Blending Preset 32-bit RGB Command */
/* pt  : protection(disable, enable) */
/*   r : red channel protection (disable, enable) */
/*   g : green channel protection (disable, enable) */
/*   b : blue channel protection (disable, enable) */
/* rop : raster operation (disable, enable) */
/* blnd: blending order (onto, behind) */
/* fad : fading option (no, 4ch, alpha, rgb) */
/* clp : clipping window option (disable, enable) */
#define C_BLITBP_RGB(code, pt, rop, blnd, fad, clp) \
		(ENGINE_BE | LEN_DW | code | MK_VAL((pt >> 1), 3, 8) | \
		 MK_VAL(rop, 1, 6) | MK_VAL(blnd, 1, 4) | MK_VAL(fad, 2, 1) | \
		 MK_VAL(clp, 1, 0))



/*** Transform Engine ***/
#define CODE_TRANSB			CODE(0x00)
#define CODE_TRANSO			CODE(0x01)

#define TE_DST_ADR_REG			(4)
#define TE_DST_MEM_WIDTH_REG		(5)
#define TE_DST_MEM_WIDTH_MASK		MK_MASK(12, 0)
#define TE_DST_IMG_WIDTH_REG		(6)
#define TE_DST_IMG_WIDTH_MASK		MK_MASK(10, 0)
#define TE_DST_LINE_CNT_REG		(7)
#define TE_DST_LINE_CNT_MASK		MK_MASK(10, 0)
#define TE_SRC_ADR_REG			(9)
#define TE_SRC_MEM_WIDTH_REG		(10)
#define TE_SRC_MEM_WIDTH_MASK		MK_MASK(12, 0)
#define TE_LUT_ADR_REG			(13)
#define TE_LUT_WIDTH_REG		(14)
#define TE_LUT_WIDTH_MASK		MK_MASK(12, 0)
#define TE_LUT_LINE_CNT_REG		(15)
#define TE_LUT_LINE_CNT_MAKS		MK_MASK(10, 0)
#define TE_COLOR_REG			(16)
#define TE_COLOR_DST_MASK		MK_MASK(1, 1)
#define TE_COLOR_RGBA			(0)
#define TE_COLOR_RGB565			(1)
#define TE_COLOR_SRC_MASK		MK_MASK(1, 0)
#define TE_COLOR(s)			((s) == FMT_OPT_RGBA ? 0 : 1)
#define TE_COLOR_VAL(s, d)		(MK_VAL(TE_COLOR(s), 1, 0) | \
					 MK_VAL(TE_COLOR(d), 1, 1))
#define TE_PREDEFINED_COLOR_REG		(17)
#define TE_FADE_FACTOR_REG		(26)
#define TE_FADE_FACTOR_MAKS		MK_MASK(8, 0)
#define TE_SRC_ALPHA_REG		(27)
#define TE_SRC_ALPHA_MASK		MK_MASK(8, 0)
#define TE_DST_ALPHA_REG		(28)
#define TE_DST_ALPHA_MASK		MK_MASK(8, 0)

#define RED_CH_NO_FADE			(0)
#define RED_CH_WITH_FADE		(1)
#define GREE_CH_NO_FADE			(0)
#define GREE_CH_WITH_FADE		(1)
#define BLUE_CH_NO_FADE			(0)
#define BLUE_CH_WITH_FADE		(1)
#define ALPHA_CH_NO_FADE		(0)
#define ALPHA_CH_WITH_FADE		(1)
#define MODE_PIXEL			(0)
#define MODE_COLOR_CH			(1)
#define FILTER_DISABLE			(0)
#define FILTER_ENABLE			(1)

/* Transfomation Blend Command */
/* dp  : protection(disable, enable) */
/*   dr: destination red channel protection (disable, enable) */
/*   dg: destination green channel protection (disable, enable) */
/*   db: destination blue channel protection (disable, enable) */
/*   da: destination alpha channel protection (disable, enable) */
/* sf  : source fading (disable, enable) */
/*   sr: soruce red channel fading (disable, enable) */
/*   sg: soruce green channel fading (disable, enable) */
/*   sb: soruce blue channel fading (disable, enable) */
/*   sa: soruce alpha channel fading (disable, enable) */
/* blnd: blending order (onto, behind) */
/* mode: mode control (pixel, color channel) */
/* flt : filter control (disable, enable) */
#define C_TRANSB(dp, sf, blnd, mode, flt)	\
		(ENGINE_TE | LEN_DW | CODE_TRANSB | MK_VAL(dp, 4, 12) | \
		 MK_VAL(sf, 4, 8) | MK_VAL(blnd, 1, 3) | MK_VAL(mode, 1, 1) | \
		 MK_VAL(flt, 1, 0))

/* Transfomation Overwrite Command */
/* mode: mode control (pixel, color channel) */
/* flt : filter control (disable, enable) */
#define C_TRANSO(m, f)		\
		(ENGINE_TE | LEN_DW | CODE_TRANSO | MK_VAL(m, 1, 1) | \
		 MK_VAL(f, 1, 0))



/*** Rotation Engine ***/
#define CODE_ROTB			CODE(0x00)
#define CODE_ROTO			CODE(0x01)

#define RE_CLIP_START_REG		(1)
#define RE_CLIP_START_X_MASK		MK_MASK(12, 16)
#define RE_CLIP_START_Y_MASK		MK_MASK(12, 0)
#define RE_CLIP_START_VAL(x, y)		(MK_VAL(x, 12, 16) | MK_VAL(y, 12, 0))
#define RE_CLIP_END_REG			(2)
#define RE_CLIP_END_X_MASK		MK_MASK(12, 16)
#define RE_CLIP_END_Y_MASK		MK_MASK(12, 0)
#define RE_CLIP_END_VAL(x, y)		(MK_VAL(x, 12, 16) | MK_VAL(y, 12, 0))
#define RE_DST_ADR_REG			(4)
#define RE_DST_DIM_REG			(5)
#define RE_DST_DIM_H_MASK		MK_MASK(12, 16)
#define RE_DST_DIM_W_MASK		MK_MASK(12, 0)
#define RE_DST_DIM_VAL(w, h)		(MK_VAL(h, 12, 16) | MK_VAL(w, 12, 0))
#define RE_SRC_ADR_REG			(9)
#define RE_SRC_MEM_WIDTH_REG		(10)
#define RE_SRC_MEM_WIDTH_MASK		MK_MASK(12, 0)
#define RE_COLOR_REG			(11)
#define RE_COLOR_DST_MASK		MK_MASK(1, 1)
#define RE_COLOR_SRC_MASK		MK_MASK(1, 0)
#define RE_COLOR(s)			((s) == FMT_OPT_RGBA ? 0 : 1)
#define RE_COLOR_VAL(dst, src)		(MK_VAL(RE_COLOR(dst), 1, 1) | \
					 MK_VAL(RE_COLOR(src), 1, 0))
#define RE_ROT_SX_REG			(12)
#define RE_ROT_SX_MASK			MK_MASK(22, 0)
#define RE_ROT_SHY_REG			(13)
#define RE_ROT_SHY_MASK			MK_MASK(22, 0)
#define RE_ROT_SY_REG			(14)
#define RE_ROT_SY_MASK			MK_MASK(22, 0)
#define RE_ROT_SHX_REG			(15)
#define RE_ROT_SHX_MASK			MK_MASK(22, 0)
#define RE_ROT_FRCC1_REG		(16)
#define RE_ROT_FRCC1_X_MASK		MK_MASK(16, 16)
#define RE_ROT_FRCC1_Y_MASK		MK_MASK(16, 0)
#define RE_ROT_FRCC1_VAL(x, y)		(MK_VAL((x * 16), 16, 16) | \
					 MK_VAL((y * 16), 16, 0))
#define RE_ROT_FRCC2_REG		(17)
#define RE_ROT_FRCC2_X_MASK		MK_MASK(16, 16)
#define RE_ROT_FRCC2_Y_MASK		MK_MASK(16, 0)
#define RE_ROT_FRCC2_VAL(x, y)		RE_ROT_FRCC1_VAL(x, y)
#define RE_ROT_FRCC3_REG		(18)
#define RE_ROT_FRCC3_X_MASK		MK_MASK(16, 16)
#define RE_ROT_FRCC3_Y_MASK		MK_MASK(16, 0)
#define RE_ROT_FRCC3_VAL(x, y)		RE_ROT_FRCC1_VAL(x, y)
#define RE_ROT_FRCC4_REG		(19)
#define RE_ROT_FRCC4_X_MASK		MK_MASK(16, 16)
#define RE_ROT_FRCC4_Y_MASK		MK_MASK(16, 0)
#define RE_ROT_FRCC4_VAL(x, y)		RE_ROT_FRCC1_VAL(x, y)
#define RE_ROT_SRC_POS_REG		(20)
#define RE_ROT_SRC_POS_MASK		MK_MASK(2, 0)
#define RE_ROT_SRC_POS_FRCC1		(0)
#define RE_ROT_SRC_POS_FRCC2		(1)
#define RE_ROT_SRC_POS_FRCC3		(2)
#define RE_ROT_SRC_POS_FRCC4		(3)
#define RE_ROT_W0_REG			(21)
#define RE_ROT_W0_MASK			MK_MASK(22, 0)
#define RE_ROT_W1_REG			(22)
#define RE_ROT_W1_MASK			MK_MASK(22, 0)
#define RE_ROT_W2_REG			(23)
#define RE_ROT_W2_MASK			MK_MASK(22, 0)
#define RE_SRC_FADE_REG			(26)
#define RE_SRC_FADE_MASK		MK_MASK(8, 0)
#define RE_SRC_ALPHA_REG		(27)
#define RE_SRC_ALPHA_MASK		MK_MASK(8, 0)
#define RE_DST_ALPHA_REG		(28)
#define RE_DST_ALPHA_MASK		MK_MASK(8, 0)

/* Rotation Blend Command */
/* dp  : protection(disable, enable) */
/*   dr: destination red channel protection (disable, enable) */
/*   dg: destination green channel protection (disable, enable) */
/*   db: destination blue channel protection (disable, enable) */
/*   da: destination alpha channel protection (disable, enable) */
/* sf  : source fading (disable, enable) */
/*   sr: soruce red channel fading (disable, enable) */
/*   sg: soruce green channel fading (disable, enable) */
/*   sb: soruce blue channel fading (disable, enable) */
/*   sa: soruce alpha channel fading (disable, enable) */
/* blnd: blending order (onto, behind) */
/* clp : clipping window option (disable, enable) */
/* flt : filter control (disable, enable) */
#define C_ROTB(dp, sf, blnd, clp, flt)	\
		(ENGINE_RE | LEN_DW | CODE_ROTB | MK_VAL(dp, 4, 12) | \
		 MK_VAL(sf, 4, 8) | MK_VAL(blnd, 1, 3) | MK_VAL(clp, 1, 1) | \
		 MK_VAL(flt, 1, 0))

/* Rotation Overwrite Command */
/* clp : clipping window option (disable, enable) */
/* flt : filter control (disable, enable) */
#define C_ROTO(clip, flt)		\
		(ENGINE_RE | LEN_DW | CODE_ROTO | MK_VAL(clip, 1, 1) | \
		 MK_VAL(flt, 1, 0))



/*** Drawing Engine ***/
#define CODE_DL32			CODE(0x03)
#define CODE_DL16			CODE(0x04)
#define CODE_DT32			CODE(0x05)
#define CODE_DT16			CODE(0x06)

#define DE_POS_VAL(x1, x2, y1, y2)	\
		(MK_VAL(y1, 12, 20) | MK_VAL(y2, 4, 16) | \
		 MK_VAL(x1, 12, 4) | MK_VAL(x2, 4, 0))
#define DE_RGBA_VAL(r, g, b, a)	\
		(MK_VAL(r, 8, 24) | MK_VAL(g, 8, 16) | MK_VAL(b, 8, 8) | \
		 MK_VAL(a, 8, 0))
#define DE_RGBA16_VAL(r, g, b, a)	\
		(MK_VAL(r, 5, 11) | MK_VAL(g, 6, 5) | MK_VAL(b, 5, 0) | \
		 MK_VAL(a, 8, 16))
#define DE_RGB_VAL(r, g, b)	\
		(MK_VAL(r, 5, 11) | MK_VAL(g, 6, 5) | MK_VAL(b, 5, 0))

#define DE_CLIP_START_REG		(1)
#define DE_CLIP_START_Y_MASK		MK_MASK(12, 16)
#define DE_CLIP_START_X_MASK		MK_MASK(12, 0)
#define DE_CLIP_START_VAL(x, y)		(MK_VAL(y, 12, 16) | MK_VAL(x, 12, 0))
#define DE_CLIP_END_REG			(2)
#define DE_CLIP_END_Y_MASK		MK_MASK(12, 16)
#define DE_CLIP_END_X_MASK		MK_MASK(12, 0)
#define DE_CLIP_END_VAL(x, y)		(MK_VAL(y, 12, 16) | MK_VAL(x, 12, 0))
#define DE_DST_ADR_REG			(4)
#define DE_MEM_DIM_REG			(5)
#define DE_MEM_DIM_H_MASK		MK_MASK(12, 16)
#define DE_MEM_DIM_W_MASK		MK_MASK(12, 0)
#define DE_MEM_DIM_VAL(w, h)		(MK_VAL(h, 12, 16) | MK_VAL(w, 12, 0))
#define DE_LINE_START_REG		(6)
#define DE_LINE_START_Y_INT_MASK	MK_MASK(12, 20)
#define DE_LINE_START_Y_SUB_MASK	MK_MASK(4, 16)
#define DE_LINE_START_X_INT_MASK	MK_MASK(12, 4)
#define DE_LINE_START_X_SUB_MASK	MK_MASK(4, 0)
#define POS_TO_U32(pos)			\
		DE_POS_VAL(pos.x, pos.sub_x, pos.y, pos.sub_y)

#define DE_LINE_END_REG			(7)
#define DE_LINE_END_Y_INT_MASK		MK_MASK(12, 20)
#define DE_LINE_END_Y_SUB_MASK		MK_MASK(4, 16)
#define DE_LINE_END_X_INT_MASK		MK_MASK(12, 4)
#define DE_LINE_END_X_SUB_MASK		MK_MASK(4, 0)
#define DE_TRI_PT1_REG			(6)
#define DE_TRI_PT1_Y_INT_MASK		MK_MASK(12, 20)
#define DE_TRI_PT1_Y_SUB_MASK		MK_MASK(4, 16)
#define DE_TRI_PT1_X_INT_MASK		MK_MASK(12, 4)
#define DE_TRI_PT1_X_SUB_MASK		MK_MASK(4, 0)
#define DE_TRI_PT2_REG			(7)
#define DE_TRI_PT2_Y_INT_MASK		MK_MASK(12, 20)
#define DE_TRI_PT2_Y_SUB_MASK		MK_MASK(4, 16)
#define DE_TRI_PT2_X_INT_MASK		MK_MASK(12, 4)
#define DE_TRI_PT2_X_SUB_MASK		MK_MASK(4, 0)
#define DE_TRI_PT3_REG			(8)
#define DE_TRI_PT3_Y_INT_MASK		MK_MASK(12, 20)
#define DE_TRI_PT3_Y_SUB_MASK		MK_MASK(4, 16)
#define DE_TRI_PT3_X_INT_MASK		MK_MASK(12, 4)
#define DE_TRI_PT3_X_SUB_MASK		MK_MASK(4, 0)
#define DE_LINE_THICK_REG		(9)
#define DE_LINE_THICK_INT_MASK		MK_MASK(8, 4)
#define DE_LINE_THICK_SUB_MASK		MK_MASK(4, 0)
#define DE_LINE_THICK_VAL(th1, th2)	(MK_VAL(th1, 8, 4) | MK_VAL(th2, 4, 0))
#define THICK_TO_U32(t)			DE_LINE_THICK_VAL(t.th, t.sub_th)
#define DE_COLOR_REG			(10)
#define DE_COLOR_RGBA_R_MASK		MK_MASK(8, 24)
#define DE_COLOR_RGBA_G_MASK		MK_MASK(8, 16)
#define DE_COLOR_RGBA_B_MASK		MK_MASK(8, 8)
#define DE_COLOR_RGBA_A_MASK		MK_MASK(8, 0)
#define DE_COLOR_RGB_R_MASK		MK_MASK(5, 11)
#define DE_COLOR_RGB_G_MASK		MK_MASK(6, 5)
#define DE_COLOR_RGB_B_MASK		MK_MASK(5, 0)
#define DE_COLOR_RGB_A_MASK		MK_MASK(8, 16)
#define DE_BK_COLOR_REG			(11)
#define DE_BK_COLOR_RGBA_R_MASK		MK_MASK(8, 24)
#define DE_BK_COLOR_RGBA_G_MASK		MK_MASK(8, 16)
#define DE_BK_COLOR_RGBA_B_MASK		MK_MASK(8, 8)
#define DE_BK_COLOR_RGBA_A_MASK		MK_MASK(8, 0)
#define DE_BK_COLOR_RGB_R_MASK		MK_MASK(5, 11)
#define DE_BK_COLOR_RGB_G_MASK		MK_MASK(6, 5)
#define DE_BK_COLOR_RGB_B_MASK		MK_MASK(5, 0)



/* Drawing Line RGBA32 Command */
/* scap: start point line caps style (non-antialiase, antialiase, circular) */
/* ecap: end point line caps style (non-antialiase, antialiase, circular) */
/* blnd: blending mode (opaque, ransparency, overwrite, saturation) */
/* clp : clipping window option (disable, enable) */
#define CMD_DL(code, scap, ecap, blnd, clp)	\
		(ENGINE_DE | LEN_DW | code | MK_VAL(scap, 4, 8) | \
		 MK_VAL(ecap, 4, 4) | MK_VAL(blnd, 3, 1) | MK_VAL(clp, 1, 0))

#define C_DL32(scap, ecap, blnd, clp)	\
		CMD_DL(CODE_DL32, scap, ecap, blnd, clp)

/* Drawing Line RGB16 Command */
#define C_DL16(scap, ecap, blnd, clip)	\
		CMD_DL(CODE_DL16, scap, ecap, blnd, clp)

/* Drawing Triangle RGBA32 Command */
/* e3  : edge 3 antialiasing (off, on) */
/* e2  : edge 2 antialiasing (off, on) */
/* e1  : edge 1 antialiasing (off, on) */
/* blnd: blending mode (opaque, ransparency, overwrite, saturation) */
/* clp : clipping window option (disable, enable) */

#define CMD_DT(code, e, blnd, clp)	\
		(ENGINE_DE | LEN_DW | code | MK_VAL(e, 3, 4) | \
		 MK_VAL(blnd, 3, 1) | MK_VAL(clp, 1, 0))

#define C_DT32(e, mode, clp)	\
		CMD_DT(CODE_DT32, e, mode, clp)

/* Drawing Triangle RGB16 Command */
#define C_DT16(e, mode, clp)	\
		CMD_DT(CODE_DT16, e, mode, clp)



#define TZ2000GFX_BUFFER_WORDS  0x5000		/* number of 64bit words in command list */
#define TZ2000GFX_BUFFER_EXTRA	(32)		/* for Burst read */
#define TZ2000GFX_BATCH_NUM	(100)		/* num of Batchs */



struct tz2000gfx_share {
	__u64	buffer[2][TZ2000GFX_BUFFER_WORDS + TZ2000GFX_BUFFER_EXTRA];
	__u32	buf_cnt[2];
	__u8	buf_idx;

	int	hw_running;

	__u32	num_starts;
	__u32	num_done;
	__u32	num_interrupts;
	__u32	num_wait_idle;
	__u32	num_idle;
};

struct tz2000gfx_drv {
	__u8 __iomem		*gfxbase;
	__u8 __iomem		*pmubase;
	dma_addr_t		shared_phys;
	struct tz2000gfx_share	*share;
};


int  tz2000gfx_init(void);
void tz2000gfx_exit(void);
#if defined(_MERGE_FBDEV_)
void tz2000gfx_resume(void);
int tz2000gfx_suspend(void);
int tz2000gfx_restore(void);
#endif

#if defined(_MERGE_FBDEV_)
long tz2000gfx_ioctl(struct fb_info *info,
		unsigned int   cmd,
		unsigned long  arg);
#endif

static inline volatile __u32
tz2000_pmu_read(struct tz2000gfx_drv *drv, const volatile __u32 off)
{
#if defined(__DBG_TZ2000GFX__)
	pr_info("%s(%p + %08x)\n", __func__, drv->pmubase, off);
#endif
	return __raw_readl(drv->pmubase + off);
}

static inline void
tz2000_pmu_write(struct tz2000gfx_drv *drv, const volatile __u32 off, __u32 v)
{
#if defined(__DBG_TZ2000GFX__)
	pr_info("%s(%p + %08x) = %08x\n", __func__, drv->pmubase, off, v);
#endif
	__raw_writel(v, drv->pmubase + off);
}

static inline volatile __u32
tz2000_read(struct tz2000gfx_drv *drv, const volatile __u32 off)
{
#if defined(__DBG_TZ2000GFX__)
	pr_info("%s(%p + %08x)\n", __func__, drv->gfxbase, off);
#endif
	return __raw_readl(drv->gfxbase + off);
}

static inline void
tz2000_write(struct tz2000gfx_drv *drv, const volatile __u32 off, __u32 v)
{
#if defined(__DBG_TZ2000GFX__)
	pr_info("%s(%p + %08x) = %08x\n", __func__, drv->gfxbase, off, v);
#endif
	__raw_writel(v, drv->gfxbase + off);
}

static inline void
tz2000_cmdlist_swap(struct tz2000gfx_share *share)
{
#if defined(__DBG_TZ2000GFX__)
	pr_info("%s()[%d][%4d][%4d]\n", __func__, share->buf_idx,
			share->buf_cnt[0], share->buf_cnt[1]);
#endif
	share->buf_cnt[0] = 0;
	share->buf_cnt[1] = 0;
	share->buf_idx = ((share->buf_idx + 1) & 0x01);
#if defined(__DBG_TZ2000GFX__)
	pr_info("%s()[%d][%4d][%04d]\n", __func__, share->buf_idx,
			share->buf_cnt[0], share->buf_cnt[1]);
#endif
}

static inline __u32
tz2000_cmdlist_get_free_size(struct tz2000gfx_share *share)
{
	int ret = TZ2000GFX_BUFFER_WORDS - share->buf_cnt[share->buf_idx];

#if defined(__DBG_TZ2000GFX__)
	pr_info("%s()[%d] = %d\n", __func__, share->buf_idx, ret);
#endif

	return ret;
}

static inline void
tz2000_cmdlist_push(struct tz2000gfx_share *share, __u64 v)
{
#if defined(__DBG_TZ2000GFX__)
	pr_info("%s()[%d][%4d][%016llx]\n", __func__, share->buf_idx,
			share->buf_cnt[share->buf_idx], v);
#endif
	share->buffer[share->buf_idx][share->buf_cnt[share->buf_idx]] = v;
	share->buf_cnt[share->buf_idx]++;
}

static inline void
tz2000_cmdlist_put(struct tz2000gfx_share *share, __u32 idx, __u64 v)
{
#if defined(__DBG_TZ2000GFX__)
	pr_info("%s()[%d] =[%016llx]\n", __func__, share->buf_idx, v);
#endif
	share->buffer[share->buf_idx][idx] = v;
}

static inline void
tz2000_cmdlist_update_wp(struct tz2000gfx_share *share, __u32 inc)
{
#if defined(__DBG_TZ2000GFX__)
	pr_info("%s()[%d][%4d] += [%4d]\n", __func__, share->buf_idx,
			share->buf_cnt[share->buf_idx], inc);
#endif
	share->buf_cnt[share->buf_idx] += inc;
}


#endif

