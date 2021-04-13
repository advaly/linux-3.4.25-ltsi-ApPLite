/*
 * linux/drivers/staging/applite/irecog/hist/hist_util.c
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
#include "hist_util.h"

#define DD_NO_ERROR		(0)	/* No errors */
#define DD_ERROR        (-1)	/* Error */

/* Sets the parameters in the HIST_DESCRIPT structure in histogram calculation mode. */
SINT dd_HIST_config_histogram(HIST_DESCRIPT *descript,	/* Pointer to the HIST_DESCRIPT structure. */
			      VOID *histogram_addr,	/* The histogram data output destination address. */
			      const VOID *src_addr,	/* Pointer to the header of the input data. */
			      UINT src_pitch,	/* Input data line pitch. */
			      UINT src_dim,	/* Number of input data dimensions. */
			      UINT src_type,	/* Input data type. */
			      UINT src_x_interval,	/* Input data X-axis sampling interval. */
			      UINT src_y_interval,	/* Input data Y-axis sampling interval. */
			      UINT src_x_num,	/* Input data X-axis sampling times. */
			      UINT src_y_num,	/* Input data Y-axis sampling times. */
			      UINT outlier,	/* Outlier processing method. */
			      UINT clear,	/* Initializes the frequency value. */
			      UINT bin_num,	/* Number of bins. */
			      UINT index_shift,	/* Luminance value shift amount (Specified number of bits are truncated.) */
			      SINT index_offset,	/* Luminance value offset (Polls the value that the offset is subtracted from the luminance value.) */
			      UINT condition,	/* Conditions for adding input data to the internal registers. */
			      SINT threshold	/* Threshold to judge. */
    )
{
	UINT src_width;		/* Number of X-axis data */
	UINT src_height;	/* Number of Y-axis data */
	UINT uaddr;
	UINT offset;

	/* Set Default Value */
	src_width = 0;
	src_height = 0;

	descript->ctrl = 0x00000001UL;	/* Start[0] */

	descript->hist_offset = (SSHORT)index_offset;	/* Offset amount */
	descript->mode = (REG_16) (((index_shift & 0x0f) << 1)
				   | 0x00000000UL);	/* Operation mode[0], Right shift amount[4:1] */

	descript->hist_setting =
	    (REG_32)(((histogram_addr != NULL) ? 0x20U : 0x00U)
		     | ((outlier & 0x01) << 4)
		     | ((clear & 0x01) << 3)
		     | ((bin_num & 0x03) << 1));
	/* With/without output[5], Handles outliers[4], With/without initialization[3], The number of Bins[2:1], With/without scores[0]. */
	descript->table_setting = 0x00000000UL;	/* With/without load of new table[4], Data size before conversion[3:0]. */

	descript->threshold = (USHORT)((USHORT)threshold & 0xffffU);	/* Set the threshold value of the count with conditions in the statistical functions. */
	descript->condition = (USHORT)((condition & 0x01) << 1);	/* Conditions of the count with conditions in the statistical functions[1]. */
	if (threshold < 0) {
		descript->condition |= 0x01;
	}

	uaddr = (UINT)src_addr & 0xfffffff0U;	/* Start address of input data (the lower 4 bits are fixed at 0.) */
	descript->src0_addr = (VOID *)uaddr;

	descript->src1_addr = (VOID *)0x00000000UL;	/* Start address of polling value data (the lower 4 bits are fixed at 0.) */

	descript->src0_pitch = src_pitch - 1;	/* Line pitch of input data (the lower 4 bits are fixed at 0.) */
	descript->src1_pitch = 0x00000000UL;	/* Line pitch of polling value data (the lower 4 bits are fixed at 0.) */

	src_dim -= 1;

	/* src_width and src_height are automatically set as the right value */
	if (src_dim == 0) {
		src_width = (UINT)(src_x_interval * (src_x_num - 1));
	} else if (src_dim == 1) {
		src_width = (UINT)(src_x_interval * (src_x_num - 1));
		src_height = (UINT)(src_y_interval * (src_y_num - 1));
	} else {
		/* do nothing */
	}

	if (src_dim == 0) {
		descript->src0_width = (USHORT)(src_width & 0xffffUL);	/* Value of the number of input data X-axis elements-1. */
		descript->src0_setting = (REG_16) (((src_type & 0x03) << 14)
						   | ((src_dim & 0x01) << 13)
						   | ((src_width >> 16) &
						      0x1fffUL));
		/* Set the input data items. Type[15:14], 1D array or image[13], Number of input data Y-axis elements[12:0]. */
	} else if (src_dim == 1) {
		descript->src0_width = (USHORT)src_width;	/* Value of the number of input data X-axis elements-1. */
		descript->src0_setting = (REG_16) (((src_type & 0x03) << 14)
						   | ((src_dim & 0x01) << 13)
						   | (src_height & 0x1fffUL));
		/* Set the input data items. Type[15:14], 1D array or image[13], Number of input data Y-axis elements[12:0]. */
	} else {
		/* do nothing */
	}

	descript->src1_width = 0x00000000UL;	/* Value of the number of polling value data X-axis elements-1. */
	descript->src1_setting = 0x00000000UL;	/* Set the polling value data items. Type[15:14], 1D array or image[13], Number of polling value data Y-axis elements[12:0]. */

	descript->src0_sx = (UCHAR) (src_x_interval - 1);	/* Value of the number of input data X-axis elements-1. */
	descript->src0_sy = (UCHAR) (src_y_interval - 1);	/* Value of the number of input data Y-axis elements-1. */
	offset = (UINT)src_addr & 0x000fU;	/* Line offset amount of input data[3:0]. */
	if ((src_type == 1) || (src_type == 3)) {
		offset /= 2;
	}

	descript->src0_sp_offset = (USHORT)offset;

	if (src_dim == 0) {
		descript->src0_nx = (USHORT)((src_x_num - 1) & 0xffffUL);	/* Value of the X-axis sampling times of the input data-1. */
		descript->src0_ny = (USHORT)(((src_x_num - 1) >> 16) & 0x1fffUL);	/* Value of the Y-axis sampling times of the input data-1[12:0]. */

	} else if (src_dim == 1) {
		descript->src0_nx = (USHORT)((src_x_num - 1) & 0xffffUL);	/* Value of the X-axis sampling times of the input data-1. */
		descript->src0_ny = (USHORT)((src_y_num - 1) & 0x1fffUL);	/* Value of the Y-axis sampling times of the input data-1[12:0]. */
	} else {
		/* do nothing */
	}

	descript->src1_sx = 0x00;	/* Value of the number of polling value data X-axis sampling elements-1. */
	descript->src1_sy = 0x00;	/* Value of the number of polling value data Y-axis sampling elements-1. */
	descript->src1_sp_offset = 0x0000UL;	/* Line offset amount of polling value data[3:0]. */

	descript->src1_nx = 0x0000UL;	/* Value of the polling value data X-axis interval-1. */
	descript->src1_ny = 0x0000UL;	/* Value of the polling value data Y-axis sampling times-1[12:0]. */

	uaddr = (UINT)histogram_addr & 0xfffffff0U;	/* Start address of output data(the lower 4 bits are fixed at 0). */
	descript->dst0_addr = (VOID *)uaddr;
	descript->dst0_pitch = 0x00000000UL;	/* Line pitch of output data(the lower 4 bits are fixed at 0). */

	return DD_NO_ERROR;

}

/* Sets the parameters in the HIST_DESCRIPT structure in histograms with scores calculation mode. */
SINT dd_HIST_config_scorevoting(HIST_DESCRIPT *descript,	/* Pointer to the HIST_DESCRIPT structure. */
				VOID *histogram_addr,	/* The histogram data output destination address. */
				const VOID *src_addr,	/* Pointer to the header of the input data. */
				UINT src_pitch,	/* Input data line pitch. */
				UINT src_dim,	/* Number of input data dimensions. */
				UINT src_type,	/* Input data type. */
				UINT src_x_interval,	/* Input data X-axis sampling interval. */
				UINT src_y_interval,	/* Input data Y-axis sampling interval. */
				UINT src_x_num,	/* Input data X-axis sampling times. */
				UINT src_y_num,	/* Input data Y-axis sampling times. */
				const VOID *score_addr,	/* Pointer to the header of the poll value. */
				UINT score_pitch,	/* Poll value data line pitch. */
				UINT score_type,	/* Poll value data format. */
				UINT score_x_interval,	/* Polling value data X-axis sampling interval. */
				UINT score_y_interval,	/* Polling value data Y-axis sampling interval. */
				UINT outlier,	/* Outlier processing method. */
				UINT clear,	/* Initializes the frequency value. */
				UINT bin_num,	/* Number of bins. */
				UINT index_shift,	/* Luminance value shift amount (Specified number of bits are truncated.) */
				SINT index_offset,	/* Luminance value offset (Polls the value that the offset is subtracted from the luminance value.) */
				UINT condition,	/* Conditions for adding input data to the internal registers. */
				SINT threshold	/* Threshold to judge. */
    )
{
	UINT src_width;		/* Number of X-axis data */
	UINT src_height;	/* Number of Y-axis data */
	UINT score_width;	/* Number of X-axis data */
	UINT score_height;	/* Number of Y-axis data */
	UINT uaddr;
	UINT offset;

	/* Set Default Value */
	src_width = 0;
	score_width = 0;
	src_height = 0;
	score_height = 0;

	descript->ctrl = 0x00000001UL;	/* Start[0] */

	descript->hist_offset = (SSHORT)index_offset;	/* Offset amount */
	descript->mode = (REG_16) (((index_shift & 0x0f) << 1)
				   | 0x00000000UL);	/* Operation mode[0], Right shift amount[4:1] */

	descript->hist_setting =
	    (REG_32)(((histogram_addr != (VOID *)0) ? 0x20U : 0x00U)
		     | ((outlier & 0x01) << 4)
		     | ((clear & 0x01) << 3)
		     | ((bin_num & 0x03) << 1)
		     | 0x01);
	/* With/without output[5], Handles outliers[4], With/without initialization[3], The number of Bins[2:1], With/without scores[0]. */
	descript->table_setting = 0x00000000UL;	/* With/without load of new table[4], Data size before conversion[3:0]. */

	descript->threshold = (USHORT)((USHORT)threshold & 0xffffU);	/* Set the threshold value of the count with conditions in the statistical functions. */
	descript->condition = (USHORT)((condition & 0x01) << 1);	/* Conditions of the count with conditions in the statistical functions[1:1]. */
	if (threshold < 0) {
		descript->condition |= 0x01;
	}

	uaddr = (UINT)src_addr & 0xfffffff0U;	/* Start address of input data (the lower 4 bits are fixed at 0.) */
	descript->src0_addr = (VOID *)uaddr;
	uaddr = (UINT)score_addr & 0xfffffff0U;	/* Start address of polling value data (the lower 4 bits are fixed at 0.) */
	descript->src1_addr = (VOID *)uaddr;

	descript->src0_pitch = src_pitch - 1;	/* Line pitch of input data (the lower 4 bits are fixed at 0.) */
	descript->src1_pitch = score_pitch - 1;	/* Line pitch of polling value data (the lower 4 bits are fixed at 0.) */

	src_dim -= 1;

	/* src_width and src_height are automatically set as the right value */
	if (src_dim == 0) {
		src_width = (UINT)(src_x_interval * (src_x_num - 1));
		score_width = (UINT)(score_x_interval * (src_x_num - 1));

	} else if (src_dim == 1) {
		src_width = (UINT)(src_x_interval * (src_x_num - 1));
		src_height = (UINT)(src_y_interval * (src_y_num - 1));
		score_width = (UINT)(score_x_interval * (src_x_num - 1));
		score_height = (UINT)(score_y_interval * (src_y_num - 1));
	} else {
		/* do nothing */
	}

	if (src_dim == 0) {
		descript->src0_width = (USHORT)(src_width & 0xffffUL);	/* Value of the number of input data X-axis elements-1. */
		descript->src0_setting = (REG_16) (((src_type & 0x03) << 14)
						   | ((src_dim & 0x01) << 13)
						   | ((src_width >> 16) &
						      0x1fffUL));
		/* Set the input data items. Type[15:14], 1D array or image[13], Number of input data Y-axis elements[12:0]. */

		descript->src1_width = (USHORT)(score_width & 0xffffUL);	/* Value of the number of polling value data X-axis elements-1. */
		descript->src1_setting = (REG_16) (((score_type & 0x03) << 14)
						   | ((src_dim & 0x01) << 13)
						   | ((score_width >> 16) &
						      0x1fffUL));
		/* Set the polling value data items. Type[15:14], 1D array or image[13], Number of polling value data Y-axis elements[12:0]. */
	} else if (src_dim == 1) {
		descript->src0_width = (USHORT)(src_width & 0xffffUL);	/* Value of the number of input data X-axis elements-1. */
		descript->src0_setting = (REG_16) (((src_type & 0x03) << 14)
						   | ((src_dim & 0x01) << 13)
						   | (src_height & 0x1fff));
		/* Set the input data items. Type[15:14], 1D array or image[13], Number of input data Y-axis elements[12:0]. */

		descript->src1_width = (USHORT)(score_width & 0xffffUL);	/* Value of the number of polling value data X-axis elements-1. */
		descript->src1_setting = (REG_16) (((score_type & 0x03) << 14)
						   | ((src_dim & 0x01) << 13)
						   | (score_height & 0x1fffUL));
		/* Set the polling value data items. Type[15:14], 1D array or image[13], Number of polling value data Y-axis elements[12:0]. */
	} else {
		/* do nothing */
	}

	descript->src0_sx = (UCHAR) (src_x_interval - 1);	/* Value of the number of input data X-axis elements-1. */
	descript->src0_sy = (UCHAR) (src_y_interval - 1);	/* Value of the number of input data Y-axis elements-1. */
	offset = (UINT)src_addr & 0x000fU;	/* Line offset amount of input data[3:0]. */
	if ((src_type == 1) || (src_type == 3)) {
		offset /= 2;
	}
	descript->src0_sp_offset = (USHORT)offset;

	descript->src1_sx = (UCHAR) (score_x_interval - 1);	/* Value of the number of polling value data X-axis sampling elements-1. */
	descript->src1_sy = (UCHAR) (score_y_interval - 1);	/* Value of the number of polling value data Y-axis sampling elements-1. */

	offset = (UINT)score_addr & 0x000fU;
	if (score_type == 1) {
		offset /= 2;
	}
	descript->src1_sp_offset = (USHORT)offset;

	if (src_dim == 0) {
		descript->src0_nx = (USHORT)((src_x_num - 1) & 0xffffUL);	/* Value of the X-axis sampling times of the input data-1. */
		descript->src0_ny = (USHORT)(((src_x_num - 1) >> 16) & 0x1fffUL);	/* Value of the Y-axis sampling times of the input data-1[12:0]. */

		descript->src1_nx = (USHORT)((src_x_num - 1) & 0xffffUL);	/* Value of the polling value data X-axis interval-1. */
		descript->src1_ny = (USHORT)(((src_x_num - 1) >> 16) & 0x1fffUL);	/* Value of the polling value data Y-axis sampling times-1[12:0]. */
	} else if (src_dim == 1) {
		descript->src0_nx = (USHORT)((src_x_num - 1) & 0xffffUL);	/* Value of the X-axis sampling times of the input data-1. */
		descript->src0_ny = (USHORT)((src_y_num - 1) & 0x1fffUL);	/* Value of the Y-axis sampling times of the input data-1[12:0]. */

		descript->src1_nx = (USHORT)((src_x_num - 1) & 0xffffUL);	/* Value of the polling value data X-axis interval-1. */
		descript->src1_ny = (USHORT)((src_y_num - 1) & 0x1fffUL);	/* Value of the polling value data Y-axis sampling times-1[12:0]. */

	} else {
		/* do nothing */
	}

	descript->dst0_addr = (VOID *)((UINT)histogram_addr & 0xfffffff0UL);	/* Start address of output data(the lower 4 bits are fixed at 0). */
	descript->dst0_pitch = 0x00000000UL;	/* Line pitch of output data(the lower 4 bits are fixed at 0). */

	return DD_NO_ERROR;

}

/* Sets the parameters in the HIST_DESCRIPT structure in lookup table transformation mode. */
SINT dd_HIST_config_lut(HIST_DESCRIPT *descript,	/* Pointer to the HIST_DESCRIPT structure. */
			VOID *dst_addr,	/* Data output destination address. */
			UINT dst_pitch,	/* Output data line pitch. */
			const VOID *src_addr,	/* Pointer to the header of the input data. */
			UINT src_pitch,	/* Input data line pitch. */
			UINT src_dim,	/* Number of input data dimensions. */
			UINT src_type,	/* Input data type. */
			UINT src_x_interval,	/* Input data X-axis sampling interval. */
			UINT src_y_interval,	/* Input data Y-axis sampling interval. */
			UINT src_x_num,	/* Input data X-axis sampling times. */
			UINT src_y_num,	/* Input data Y-axis sampling times. */
			UINT load_flag,	/* Specify transformation table loading. */
			const UCHAR *table,	/* Start address of transformation table. */
			UINT table_size,	/* Size of transformation table. */
			UINT index_shift,	/* Luminance value shift amount (Specified number of bits are truncated.) */
			SINT index_offset,	/* Luminance value offset (Polls the value that the offset is subtracted from the luminance value.) */
			UINT condition,	/* Conditions for adding input data to the internal registers. */
			SINT threshold	/* Threshold to judge. */
    )
{
	UINT src_width;		/* Number of X-axis data */
	UINT src_height;	/* number of Y-axis data */
	UINT offset;

	/* Set Default Value */
	src_width = 0;
	src_height = 0;

	descript->ctrl = 0x00000001UL;	/* Start[0] */

	descript->hist_offset = (SSHORT)index_offset;	/* Offset amount */
	descript->mode = (REG_16) (((index_shift & 0x0f) << 1)
				   | 0x00000001UL);	/* Operation mode[0], Right shift amount[4:1] */

	descript->hist_setting = 0x00;
	/* With/without output[5], Handles outliers[4], With/without initialization[3], The number of Bins[2:1], With/without scores[0]. */
	descript->table_setting = (REG_32)(((load_flag & 0x01) << 2)
					   | (table_size & 0x03));
	/* With/without load of new table[4], Data size before conversion[3:0]. */

	descript->threshold = (USHORT)((UINT)threshold & 0xffffUL);	/* Set the threshold value of the count with conditions in the statistical functions. */
	descript->condition = (USHORT)((condition & 0x01) << 1);	/* Conditions of the count with conditions in the statistical functions[1:1]. */
	if (threshold < 0) {
		descript->condition |= 0x01;
	}

	descript->src0_addr = (VOID *)((UINT)src_addr & 0xfffffff0UL);	/* Start address of input data (the lower 4 bits are fixed at 0.) */
	descript->src1_addr = (VOID *)((UINT)table & 0xfffffff0UL);	/* Start address of polling value data (the lower 4 bits are fixed at 0.) */

	descript->src0_pitch = src_pitch - 1;	/* Line pitch of input data-1. */
	descript->src1_pitch = 0x0000UL;	/* Line pitch of polling value data-1. */

	src_dim -= 1;

	/* src_width and src_height are automatically set as the right value */
	if (src_dim == 0) {
		src_width = (UINT)(src_x_interval * (src_x_num - 1));
	} else if (src_dim == 1) {
		src_width = (UINT)(src_x_interval * (src_x_num - 1));
		src_height = (UINT)(src_y_interval * (src_y_num - 1));
	} else {
		/* do nothing */
	}

	if (src_dim == 0) {
		descript->src0_width = (USHORT)(src_width & 0xffffUL);	/* Value of the number of input data X-axis elements-1. */
		descript->src0_setting = (REG_16) (((src_type & 0x03) << 14)
						   | ((src_dim & 0x01) << 13)
						   | ((src_width >> 16) &
						      0x1fffUL));
		/* Set the input data items. Type[15:14], 1D array or image[13], Number of input data Y-axis elements[12:0]. */

		descript->src1_width = 0x00;	/* Value of the number of polling value data X-axis elements-1. */
		descript->src1_setting = 0x00;
		/* Set the polling value data items. Type[15:14], 1D array or image[13], Number of polling value data Y-axis elements[12:0]. */
	} else if (src_dim == 1) {
		descript->src0_width = (USHORT)(src_width & 0xffffUL);	/* Value of the number of input data X-axis elements-1. */
		descript->src0_setting = (REG_16) (((src_type & 0x03) << 14)
						   | ((src_dim & 0x01) << 13)
						   | (src_height & 0x1fffUL));
		/* Set the input data items. Type[15:14], 1D array or image[13], Number of input data Y-axis elements[12:0]. */

		descript->src1_width = 0x00;	/* Value of the number of polling value data X-axis elements-1. */
		descript->src1_setting = 0x00;
		/* Set the polling value data items. Type[15:14], 1D array or image[13], Number of polling value data Y-axis elements[12:0]. */
	} else {
		/* do nothing */
	}

	descript->src0_sx = (UCHAR) (src_x_interval - 1);	/* Value of the number of input data X-axis elements-1. */
	descript->src0_sy = (UCHAR) (src_y_interval - 1);	/* Value of the number of input data Y-axis elements-1. */
	offset = (UINT)src_addr & 0x000fU;	/* Line offset amount of input data[3:0]. */
	if ((src_type == 1) || (src_type == 3)) {
		offset /= 2;
	}

	descript->src0_sp_offset = (USHORT)offset;

	descript->src1_sx = 0x00;	/* Value of the number of polling value data X-axis sampling elements-1. */
	descript->src1_sy = 0x00;	/* Value of the number of polling value data Y-axis sampling elements-1. */
	descript->src1_sp_offset = (USHORT)((UINT)table & 0x0000000fUL);	/* Line offset amount of polling value data[3:0]. */

	if (src_dim == 0) {
		descript->src0_nx = (USHORT)((src_x_num - 1) & 0xffffUL);	/* Value of the X-axis sampling times of the input data-1. */
		descript->src0_ny = (USHORT)(((src_x_num - 1) >> 16) & 0x1fffUL);	/* Value of the Y-axis sampling times of the input data-1[12:0]. */

		descript->src1_nx = 0x0000UL;	/* Value of the polling value data X-axis interval-1. */
		descript->src1_ny = 0x0000UL;	/* Value of the polling value data Y-axis sampling times-1[12:0]. */
	} else if (src_dim == 1) {
		descript->src0_nx = (USHORT)((src_x_num - 1) & 0xffffUL);	/* Value of the X-axis sampling times of the input data-1. */
		descript->src0_ny = (USHORT)((src_y_num - 1) & 0x1fffUL);	/* Value of the Y-axis sampling times of the input data-1[12:0]. */

		descript->src1_nx = 0x0000UL;	/* Value of the polling value data X-axis interval-1. */
		descript->src1_ny = 0x0000UL;	/* Value of the polling value data Y-axis sampling times-1[12:0]. */

	} else {
		/* do nothing */
	}

	descript->dst0_addr = (VOID *)((UINT)dst_addr & 0xfffffff0UL);	/* Start address of output data(the lower 4 bits are fixed at 0). */
	descript->dst0_pitch = dst_pitch - 1;	/* Line pitch of output data-1. */

	return DD_NO_ERROR;

}

/* Sets only the I/O data addresses in the HIST_DESCRIPT structure.  */
SINT dd_HIST_part_config_addr(HIST_DESCRIPT *descript,	/* Pointer to the HIST_DESCRIPT structure. */
			      VOID *dst_addr,	/* Specify the data output destination address. */
			      const VOID *src_addr,	/* Specify the start address of input data. */
			      const VOID *score_addr	/* Specify the start address of polling value data. */
    )
{
	SINT status = DD_ERROR;
	UINT offset = 0;
	UINT type = 0;

	/* Start address of output data(the lower 4 bits are fixed at 0). */
	if (dst_addr != NULL) {
		descript->dst0_addr = (VOID *)((UINT)dst_addr & 0xfffffff0UL);
		status = DD_NO_ERROR;
	}

	/* Start address of input data (the lower 4 bits are fixed at 0.) */
	if (src_addr != NULL) {
		descript->src0_addr = (VOID *)((UINT)src_addr & 0xfffffff0UL);
		type = (UINT)(descript->src0_setting >> 14) & 0x03;
		offset = (UINT)src_addr & 0x000fU;
		if ((type == 1) || (type == 3)) {
			offset /= 2;
		}
		descript->src0_sp_offset = (USHORT)offset;
		status = DD_NO_ERROR;
	}

	/* Start address of polling value data (the lower 4 bits are fixed at 0.) */
	if (score_addr != NULL) {
		descript->src1_addr = (VOID *)((UINT)score_addr & 0xfffffff0UL);
		type = (UINT)(descript->src1_setting >> 14) & 0x01;
		offset = (UINT)score_addr & 0x000fU;
		if (type == 1) {
			offset /= 2;
		}
		descript->src1_sp_offset = (USHORT)offset;
		status = DD_NO_ERROR;
	}

	return status;
}
