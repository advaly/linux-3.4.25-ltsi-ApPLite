/*
 * linux/drivers/staging/applite/irecog/hog/hog_public.h
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
#ifndef __HOG_PUBLIC_H__
#define __HOG_PUBLIC_H__

#include <mach/regs/irecog_offs_def.h>
#include <mach/regs/irecog_reg_def.h>

#define HOG_MODE_DIC            0
#define HOG_MODE_SVM_POSITION   1
#define HOG_MODE_SVM_REGION     2
#define HOG_MODE_FEATURE        3

/* parameter */
#define HOG_MIN_DICT_NUM        1
#define HOG_MAX_DICT_NUM        4
#define HOG_MIN_CELL_NUM        1
#define HOG_MAX_CELL_NUM        6
#define HOG_MIN_CELL_SIZE       1
#define HOG_MAX_CELL_SIZE       256
#define HOG_MAX_ROI_WDTH        768
#define HOG_MAX_ROI_HIGT        (256 * 6)

#define HOG_MAX_ROI_WDTH_REGION  510
#define HOG_MAX_ROI_HIGT_REGION  71

#define HOG_MAX_SRC0_WDTH_REGION 510
#define HOG_MAX_SRC0_HIGT_REGION 1023

#define HOG_MIN_ROI_REGION_NUM  1
#define HOG_MAX_ROI_REGION_NUM  256

#define HOG_MIN_STRIDE_NUM  1
#define HOG_MAX_STRIDE_NUM  256

#define HOG_MIN_ROI_NUM         0x1
#define HOG_MAX_ROI_NUM         0xffffffff

#define HOG_LPITCH_ALIGN_MASK   0x0000003f	/* 64byte alignment */

/* Hog Int Clear Bits */
#define HOG_CLEAR_BITS			(IRECOG_RCOHOG0_INTERRUPT_STATUS_REGISTER_END_MASK | IRECOG_RCOHOG0_INTERRUPT_STATUS_REGISTER_ROI_OUT_MASK \
								 | IRECOG_RCOHOG0_INTERRUPT_STATUS_REGISTER_ROI_OUT_HALT_MASK | IRECOG_RCOHOG0_INTERRUPT_STATUS_REGISTER_LH_OFL_MASK \
								 | IRECOG_RCOHOG0_INTERRUPT_STATUS_REGISTER_LH_OFU_MASK)
#define HOG_INTMASK_NORMAL		(IRECOG_RCOHOG0_INTERRUPT_MASK_REGISTER_LH_OFL_MASK_MASK | IRECOG_RCOHOG0_INTERRUPT_MASK_REGISTER_LH_OFU_MASK_MASK)
#define HOG_OFFSET(x)			((x) - IRECOG_rcohog0_Control_Register_OFFS)

#define DICT_CTRL_OFFSET                (0x0)

enum hog_func_mode_e {
	HOG_FUNC_MODE_DIC = 0,
	HOG_FUNC_MODE_SVM = 1,
	HOG_FUNC_MODE_FEATURE = 2
};

enum hog_src_fmt_e {
	HOG_SRC_FMT_4BIT = 0,	/* 4bit */
	HOG_SRC_FMT_8BIT = 1,	/* 8bit */
	HOG_SRC_FMT_16BIT = 2,	/* 16bit */
	HOG_SRC_FMT_32BIT = 3,	/* 32bit */
	HOG_SRC_FMT_64BIT = 4	/* 64bit */
};

enum hog_mode_e {
	HOG_MODE_COHOG = 0,
	HOG_MODE_IHOG = 1
};

enum hog_roi_mode_e {
	HOG_ROI_MODE_POSITION = 0,
	HOG_ROI_MODE_REGION = 1
};

#endif /* __HOG_PUBLIC_H__ */
