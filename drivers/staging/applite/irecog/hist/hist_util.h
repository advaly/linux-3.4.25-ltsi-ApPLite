/*
 * linux/drivers/staging/applite/irecog/hist/hist_util.h
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
#ifndef __HIST_UTIL_H__
#define __HIST_UTIL_H__

#include <linux/kernel.h>
#include <linux/applite/irecog/basic_type.h>

#include "hist_descript.h"

#ifdef __cplusplus
extern "C" {
#endif

	enum SType { TYPE_UCHAR = 0, TYPE_USHORT, TYPE_SCHAR, TYPE_SSHORT };
	enum BSize { BIN_256 = 0, BIN_512, BIN_1024 };
	enum TSize { TABLE_256 = 0, TABLE_512, TABLE_1024, TABLE_2048 };

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
	    );

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
	    );

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
	    );

/* Sets only the I/O data addresses in the HIST_DESCRIPT structure.  */
	SINT dd_HIST_part_config_addr(HIST_DESCRIPT *descript,	/* Pointer to the HIST_DESCRIPT structure. */
				      VOID *dst_addr,	/* Specify the data output destination address. */
				      const VOID *src_addr,	/* Specify the start address of input data. */
				      const VOID *score_addr	/* Specify the start address of polling value data. */
	    );

#ifdef __cplusplus
}
#endif
#endif				/* __HIST_UTIL_H__ */
