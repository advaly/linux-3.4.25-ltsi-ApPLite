/*
 * linux/drivers/staging/applite/irecog/hist/hist_descript.h
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

#ifndef _HISTOGRAM_DESCRIPT_H_
#define _HISTOGRAM_DESCRIPT_H_

#include <linux/applite/irecog/basic_type.h>

/* The structure definition for the histogram unit requests. */
struct hist_descript_s {
	/* CTRL */
	REG_32 ctrl;		/* Set the operation control register. The accelerator is executed by writing finally. */

	/* MODE */
	REG_16 mode;		/* Set the operation mode register. The right shift amount in histogram calculation mode[4:1], Operation mode[0]. */
	SSHORT hist_offset;	/* The offset amount in histogram calculation mode. */

	/* INTC */

	/* INTM */

	/* HIST_FUNC */
	REG_32 hist_setting;	/* Sets the items in histogram calculation mode. With/without output[5], Handles outliers[4], With/without initialization[3], The number of Bins[2:1], With/without scores[0]. */

	/* TBCV_FUNC */
	REG_32 table_setting;	/* Set the items in lookup table transformation mode. With/without load of new table[4], Data size before conversion[3:0]. */

	/* STAT_FUNC */
	USHORT threshold;	/* Set the threshold value of the count with conditions in the statistical functions. */
	USHORT condition;	/* Conditions of the count with conditions in the statistical functions[1:0]. */

	/* SRC0_ADDR */
	VOID *src0_addr;	/* Start address of input data (the lower 4 bits are fixed at 0.) */

	/* SRC1_ADDR */
	VOID *src1_addr;	/* Start address of polling value data (the lower 4 bits are fixed at 0.) */

	/* SRC0_LPTCH */
	UINT src0_pitch;	/* Line pitch of input data (the lower 4 bits are fixed at 0.) */

	/* SRC1_LPTCH */
	UINT src1_pitch;	/* Line pitch of polling value data (the lower 4 bits are fixed at 0.) */

	/* SRC0_SIZE */
	USHORT src0_width;	/* Value of the number of input data X-axis elements-1. */
	REG_16 src0_setting;	/* Set the input data items. Type[15:14], 1D array or image[13], Number of input data Y-axis elements[12:0]. */

	/* SRC1_SIZE */
	USHORT src1_width;	/* Value of the number of polling value data X-axis elements-1. */
	REG_16 src1_setting;	/* Set the polling value data items. Type[15:14], 1D array or image[13], Number of polling value data Y-axis elements[12:0]. */

	/* SRC0_SP0 */
	UCHAR src0_sx;		/* Value of the number of input data X-axis elements-1. */
	UCHAR src0_sy;		/* Value of the number of input data Y-axis elements-1. */
	USHORT src0_sp_offset;	/* Line offset amount of input data[3:0]. */

	/* SRC0_SP1 */
	USHORT src0_nx;		/* Value of the X-axis sampling times of the input data-1. */
	USHORT src0_ny;		/* Value of the Y-axis sampling times of the input data-1[12:0]. */

	/* SRC1_SP0 */
	UCHAR src1_sx;		/* Value of the number of polling value data X-axis sampling elements-1. */
	UCHAR src1_sy;		/* Value of the number of polling value data Y-axis sampling elements-1. */
	USHORT src1_sp_offset;	/* Line offset amount of polling value data[3:0]. */

	/* SRC1_SP1 */
	USHORT src1_nx;		/* Value of the polling value data X-axis interval-1. */
	USHORT src1_ny;		/* Value of the polling value data Y-axis sampling times-1[12:0]. */

	/* DST0_ADDR */
	VOID *dst0_addr;	/* Start address of output data(the lower 4 bits are fixed at 0). */

	/* DST0_LPTCH */
	UINT dst0_pitch;	/* Line pitch of output data(the lower 4 bits are fixed at 0). */

	/* The following is read only */
	/* DST0_SIZE */
	/* STAT_R0 */
	/* STAT_R1 */
	/* STAT_R2 */

};

typedef struct hist_descript_s HIST_DESCRIPT;

#endif /* _HISTOGRAM_DESCRIPT_H_ */
