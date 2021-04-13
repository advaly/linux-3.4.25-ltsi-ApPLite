/*
 * linux/drivers/staging/applite/irecog/gdmac_hand_detect_isolate/filter_parameter_gdmac.h
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
#ifndef FILTER_PARAMETER_GDMAC_H
#define FILTER_PARAMETER_GDMAC_H

#include <linux/applite/irecog/basic_type.h>
#include "gdmac_filter.h"

/*----------------------------------------------------------------*/
/*                      Macro Definition                          */
/*----------------------------------------------------------------*/
/** Bit Offset in Filter Ratio Register */
#define FILTER_RATIO_BIT_BITACC            (0)
#define FILTER_RATIO_BIT_WIDTH             (2)
#define FILTER_RATIO_BIT_HEIGHT            (4)
/*----------------------------------------------------------------*/
/*                      Macro Function Definition                 */
/*----------------------------------------------------------------*/
/*----------------------------------------------------------------*/
/*                      typedef Definition                        */
/*----------------------------------------------------------------*/
/*----------------------------------------------------------------*/
/*                      struct/enum Definition                    */
/*----------------------------------------------------------------*/
enum filter_ratio_e {
	FILTER_RATIO_1_4HV = ((0 << FILTER_RATIO_BIT_HEIGHT)
			      | (0 << FILTER_RATIO_BIT_WIDTH)),

	FILTER_RATIO_1_2HV = ((1 << FILTER_RATIO_BIT_HEIGHT)
			      | (1 << FILTER_RATIO_BIT_WIDTH)),

	FILTER_RATIO_1_2H = ((2 << FILTER_RATIO_BIT_HEIGHT)
			     | (1 << FILTER_RATIO_BIT_WIDTH)),

	FILTER_RATIO_1_2V = ((1 << FILTER_RATIO_BIT_HEIGHT)
			     | (2 << FILTER_RATIO_BIT_WIDTH)),

	FILTER_RATIO_1HV = ((2 << FILTER_RATIO_BIT_HEIGHT)
			    | (2 << FILTER_RATIO_BIT_WIDTH)),

	FILTER_RATIO_2HV = ((3 << FILTER_RATIO_BIT_HEIGHT)
			    | (3 << FILTER_RATIO_BIT_WIDTH)),

	FILTER_RATIO_2H = ((2 << FILTER_RATIO_BIT_HEIGHT)
			   | (3 << FILTER_RATIO_BIT_WIDTH)),

	FILTER_RATIO_2V = ((3 << FILTER_RATIO_BIT_HEIGHT)
			   | (2 << FILTER_RATIO_BIT_WIDTH))
};
typedef enum filter_ratio_e FILTER_RATIO;

enum filter_bit_acc_s {
	FILTER_BITACC_S8 = (0 << FILTER_RATIO_BIT_BITACC),
	FILTER_BITACC_U8 = (1 << FILTER_RATIO_BIT_BITACC),
	FILTER_BITACC_S16 = (2 << FILTER_RATIO_BIT_BITACC)
};
typedef enum filter_bit_acc_s FILTER_BIT_ACC;

/**
 * @brief Struct of Filter Parameter
 */
struct filter_paramset_s {
	SINT *addr;		/*!< Base Address of Input/Output Paramter */
	SINT HIF_addr;		/*!< FilerHW HIF Address */
	SINT size;		/*!< Transfer Size in 64 Bytes */
};
typedef struct filter_paramset_s FILTER_PARAMSET;

/**
 * @brief Struct of Filter Channel Info
 */
struct filter_channel_info_s {
	UINT addr;		  /**< Input/Output Image Address */
	FILTER_RATIO ratio;	   /**< Image Transfer Ratio */
	FILTER_BIT_ACC bit_accuracy;
				   /**< Bit Accuracy */
	UINT line_offset;	   /**< Line Offset @ Rectangle Transfer in Byte */
};
typedef struct filter_channel_info_s FILTER_CHANNEL_INFO;

/**
 * @brief FILTER Parameter Definition
 */
struct filter_parameter_s {
	UINT sequence_id;	/* Sequence ID in Sequence List */
	SINT in_channel_num;	/* Number of Input Channel */
	SINT out_channel_num;	/* Number of Output Channel */
	SINT frame_num;		/* Number of Frames */

	/* Need To Be Setting for Size Modification */
	USHORT width;		   /**< width(Require for size modification) */
	USHORT height;		   /**< height(Require for size modification) */
	/* Array of Input Channel Information */
	FILTER_CHANNEL_INFO in_channel_info[FILTER_INCH_NUM];

	/* Array of Output Channel Information */
	FILTER_CHANNEL_INFO out_channel_info[FILTER_OUTCH_NUM];

	/* Array of Input Parameter Information */
	FILTER_PARAMSET input_param[FILTER_PARA_NUM];

	/* Array of Input Parameter Information */
	FILTER_PARAMSET output_param[FILTER_PARA_NUM];

	/* Pointer of Descriptor Table of Parameters to be Modified */
	UINT hif_param_num;
	FILTER_HIF_PARAM *hif_param;

};
typedef struct filter_parameter_s FILTER_PARAMETER;

#endif /* FILTER_PARAMETER_H */
