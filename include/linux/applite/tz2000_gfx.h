/*
 * linux/applite/tz2000_gfx.h
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
#ifndef __TZ2000_GFX_H__
#define __TZ2000_GFX_H__

#include <asm/types.h>



#define ROP_RGBA			(0)
#define ROP_RGB				(1)
#define ROP_A				(2)
#define ROP_RGB_DST_A			(3)
#define ROP_RGB_SRC_A			(4)

#define ROP_ZERO			(0)
#define ROP_SRC_OR_DST_INV		(1)
#define ROP_INV_SRC_AND_DST		(2)
#define ROP_INV_SRC			(3)
#define ROP_SRC_AND_INV_DST		(4)
#define ROP_INV_DST			(5)
#define ROP_SRC_XOR_DST			(6)
#define ROP_SRC_AND_DST_INV		(7)
#define ROP_SRC_AND_DST			(8)
#define ROP_SRC_XOR_DST_INV		(9)
#define ROP_DST				(10)
#define ROP_INV_SRC_OR_DST		(11)
#define ROP_SRC				(12)
#define ROP_SRC_OR_INV_DST		(13)
#define ROP_SRC_OR_DST			(14)
#define ROP_ONE				(15)

/* Blit Engine Command */
#define CMD_BLITO16			(0x02)
#define CMD_BLITB16			(0x03)
#define CMD_BLITO32			(0x04)
#define CMD_BLITBRLEI24			(0x05)
#define CMD_BLITORLEI24			(0x06)
#define CMD_BLITB32			(0x07)
#define CMD_BLITORLEI16			(0x0A)
#define CMD_BLITBRLEI16			(0x0B)
#define CMD_BLITORLEI32			(0x0C)
#define CMD_BLITBRLEI32			(0x0D)
#define CMD_BLITORLEI24A		(0x0E)
#define CMD_BLITBRLEI24A		(0x0F)
#define CMD_BLITOP16			(0x12)
#define CMD_BLITBP16			(0x13)
#define CMD_BLITOP32			(0x14)
#define CMD_BLITBP32			(0x17)
/* Transformation Engine Command */
#define CMD_TRANSB			(0x00)
#define CMD_TRANSO			(0x01)
/* Rotation Engine Command */
#define CMD_ROTB			(0x00)
#define CMD_ROTO			(0x01)
/* Drawing Engine Command */
#define CMD_DL32			(0x03)
#define CMD_DL16			(0x04)
#define CMD_DT32			(0x05)
#define CMD_DT16			(0x06)

#define TRANSCOLOR_OPT_DISABLE		(0)
#define TRANSCOLOR_OPT_ENABLE		(1)

#define FADE_OPT_NO			(0)
#define FADE_OPT_RGBA			(1)
#define FADE_OPT_ALPHA			(2)
#define FADE_OPT_RGB			(3)

#define CLIP_OPT_DISABLE		(0)
#define CLIP_OPT_ENABLE			(1)

#define PROTECT_OPT_R			(0x8)
#define PROTECT_OPT_G			(0x4)
#define PROTECT_OPT_B			(0x2)
#define PROTECT_OPT_A			(0x1)
#define PROTECT_OPT_OFF			(0x0)

#define ROP_OPT_DISABLE			(0)
#define ROP_OPT_ENABLE			(1)

#define BLEND_OPT_ONTO			(0)
#define BLEND_OPT_BEHIND		(1)

#define FMT_OPT_RGB16			(0)
#define FMT_OPT_RGBA			(1)

#define TRANS_FADE_R			(0x08)
#define TRANS_FADE_G			(0x04)
#define TRANS_FADE_B			(0x02)
#define TRANS_FADE_A			(0x01)

#define MODE_OPT_PIXEL			(0x00)
#define MODE_OPT_COLOR_CH		(0x01)

#define FILTER_OPT_DISABLE		(0x00)
#define FILTER_OPT_ENABLE		(0x01)

#define ROT_START_0			(0)
#define ROT_START_1			(1)
#define ROT_START_2			(2)
#define ROT_START_3			(3)

#define LINE_CAP_NO_ANTI		(0)
#define LINE_CAP_ANTI			(1)
#define LINE_CAP_CIRCULAR		(2)
/*#define LINE_BLEND_OPAQUE		(0)*/
/*#define LINE_BLEND_TRANS		(1)*/
/*#define LINE_BLEND_OW			(2)*/
/*#define LINE_BLEND_SATURATION		(3)*/

#define BLEND_OPT_OPAQUE		(0)
#define BLEND_OPT_TRANSPARENCY		(1)
#define BLEND_OPT_OVERWRITE		(2)
#define BLEND_OPT_SATURATION		(3)

#define TRI_EDGE_ANTI_OFF		(0)
#define TRI_EDGE_ANTI_ON		(1)

#define ANTI_OPT_EDGE1_ON		(0x01)
#define ANTI_OPT_EDGE2_ON		(0x02)
#define ANTI_OPT_EDGE3_ON		(0x04)
#define ANTI_OPT_NONE			(0x00)


struct applite_gfx_pt {
	__u16	x;
	__u16	y;
};

struct applite_gfx_rop {
	__u8	mode;
	__u8	value;
};

struct applite_gfx_pos {
	__u16	x;
	__u16	y;
	__u8	sub_x;
	__u8	sub_y;
};

struct applite_gfx_thick {
	__u8	th;
	__u8	sub_th;
};

struct applite_gfx_blit_prm {
	__u32		src_addr;
	__u32		dst_addr;
	__u16		src_width;	/* 1 - 4095 */
	__u16		dst_width;	/* 1 - 4095 */
	__u16		img_width;	/* 1 - 4095 */
	__u16		img_height;	/* 1 - 4095 */
};

struct applite_gfx_line {
	struct applite_gfx_pos	sp;
	struct applite_gfx_pos	ep;
};

struct applite_gfx_triangle {
	struct applite_gfx_pos	pt1;
	struct applite_gfx_pos	pt2;
	struct applite_gfx_pos	pt3;
};

struct applite_gfx_filter {
	__u8	coeff[256];
};


struct applite_gfx_blit {
	__u8		cmd;
	__u8		protect;
	__u8		rop_opt;
	__u8		blend;
	__u8		format;
	__u8		transparency;
	__u8		fade;
	__u8		clip;
	__u32		clip_addr;
	__u16		clip_width;	/* 1 - 4095 */
	__u16		clip_height;	/* 1 - 4095 */
	__u32		src_ckey;
	__u16		dst_ckey;
	__u8		src_alpha;
	__u8		dst_alpha;
	__u32		preset;
	__u8		fade_factor;
	struct applite_gfx_rop	rop;
	__u32		num;
	struct applite_gfx_blit_prm	*blit;
};


struct applite_gfx_transform {
	__u8		cmd;
	__u8		protect;
	__u8		fade;
	__u8		blend;
	__u8		mode;
	__u8		filter;
	__u8		src_fmt;
	__u8		dst_fmt;
	__u32		src_addr;
	__u16		src_width;	/* 1 - 4095 */
	__u8		fade_factor;
	__u8		src_alpha;
	__u32		lut_addr;
	__u16		lut_width;	/* 1 - 4095 */
	__u16		lut_line_cnt;	/* 1 - 1023 */
	__u32		dst_addr;
	__u16		dst_width;	/* 1 - 4095 */
	__u16		img_width;	/* 1 - 1023 */
	__u16		img_line_cnt;	/* 1 - 1023 */
	__u8		dst_alpha;
	__u32		pre_color;
};


struct applite_gfx_rotation {
	__u8		cmd;
	__u8		protect;
	__u8		fade;
	__u8		blend;
	__u8		clip;
	__u8		filter;
	__u8		src_fmt;
	__u8		dst_fmt;
	struct applite_gfx_pt	clip_start;
	struct applite_gfx_pt	clip_end;
	__u32		src_addr;
	__u16		src_width;	/* 1 - 4095 */
	__u8		fade_factor;
	__u8		src_alpha;
	__u32		dst_addr;
	__u16		dst_width;	/* 1 - 4095 */
	__u16		dst_height;	/* 1 - 4095 */
	__u8		dst_alpha;
	__u8		start_pt;
	__u32		sx;
	__u32		shx;
	__u32		shy;
	__u32		sy;
	__u32		w0;
	__u32		w1;
	__u32		w2;
	struct applite_gfx_pt	pt[4];
};


struct applite_gfx_drawline {
	__u8		cmd;
	__u8		sp_caps;
	__u8		ep_caps;
	__u8		blend;
	__u8		clip;
	struct applite_gfx_pt	clip_start;
	struct applite_gfx_pt	clip_end;
	__u32		dst_addr;
	__u16		dst_width;	/* 1 - 4095 */
	__u16		dst_height;	/* 1 - 4095 */
	struct applite_gfx_thick	thick;
	__u32		color;
	__u32		bg_color;
	__u32		num;
	struct applite_gfx_line	*line;
};

struct applite_gfx_filltriangle {
	__u8		cmd;
	__u8		antialiase;
	__u8		blend;
	__u8		clip;
	struct applite_gfx_pt	clip_start;
	struct applite_gfx_pt	clip_end;
	__u32		dst_addr;
	__u16		dst_width;	/* 1 - 4095 */
	__u16		dst_height;	/* 1 - 4095 */
	struct applite_gfx_thick	thick;
	__u32		color;
	__u32		bg_color;
	__u32		num;
	struct applite_gfx_triangle	*triangle;
};


/* initialization and synchronization.
 * Hardware is started from user space via MMIO to DMA registers. */
#define TZ2000GFX_IOCTL_RESET		_IO('G',  0)
#define TZ2000GFX_IOCTL_WAIT_IDLE	_IO('G',  1)
#define TZ2000GFX_IOCTL_EMIT_CMD	_IO('G',  2)
#define TZ2000GFX_IOCTL_DRAWLINE	_IOW('G',  3, struct applite_gfx_drawline)
#define TZ2000GFX_IOCTL_FILLTRIANGLE	_IOW('G',  4, struct applite_gfx_filltriangle)
#define TZ2000GFX_IOCTL_BLIT		_IOW('G',  5, struct applite_gfx_blit)
#define TZ2000GFX_IOCTL_TRANSFORM	_IOW('G',  6, struct applite_gfx_transform)
#define TZ2000GFX_IOCTL_ROTATION	_IOW('G',  7, struct applite_gfx_rotation)
#define TZ2000GFX_IOCTL_COEF		_IOW('G',  8, struct applite_gfx_filter)



#endif

