/*
 * linux/drivers/staging/applite/irecog/affine/affine_util.c
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
#include <linux/cdev.h>
#include <linux/io.h>

#include "affine_driver.h"
#include "affine_util.h"

static inline REG_32 dd_AFFINE_register_pack_mode(UINT o_mode, UINT px_mode,
						  UINT cnv_mode, UINT psz,
						  UINT pf_dbl, UINT b_dir,
						  UINT tb_t, UINT fill_p)
{
	return (REG_32)((o_mode & 0x00000001)
			| ((px_mode & 0x00000001) << 2)
			| ((cnv_mode & 0x00000003) << 3)
			| ((psz & 0x00000001) << 5)
			| ((pf_dbl & 0x00000001) << 6)
			| ((b_dir & 0x00000001) << 7)
			| ((tb_t & 0x00000007) << 13)
			| ((fill_p & 0x0000ffff) << 16));
}

static inline REG_32 dd_AFFINE_register_pack_adj_p(UINT ave_adj, UINT max_p)
{
	return (REG_32)(((ave_adj & 0x000000ff) << 8)
			| ((max_p & 0x0000ffff) << 16));
}

static inline REG_32 dd_AFFINE_register_pack_size(UINT wdth, UINT higt)
{
	return (REG_32)(((higt - 1) & 0x000007ff)
			| (((wdth - 1) & 0x000007ff) << 16));
}

static inline REG_32 dd_AFFINE_register_pack_bgn(UINT hbgn, UINT vbgn)
{
	return (REG_32)((vbgn & 0x000007ff)
			| ((hbgn & 0x000007ff) << 16));
}

static inline REG_32 dd_AFFINE_register_pack_pitch(UINT src, UINT dst)
{
	return (REG_32)(((dst - 1) & 0x000007ff)
			| (((src - 1) & 0x000007ff) << 16));
}

static inline REG_32 dd_AFFINE_register_pack_tbl_pitch(UINT tbl_ptch)
{
	return (REG_32)((tbl_ptch - 1) & 0x000007ff);
}

static inline void affine_config_operation(struct affine_dev *dev,
					   ULONG src_depth,
					   ULONG interpolation_mode,
					   ULONG conv_mode,
					   ULONG process_direction,
					   ULONG fill_value,
					   ULONG table_sampling_interval)
{
	REG_32 reg_val;
	UINT psz;
	UINT interpolation_error;
	UINT max_value;

	if (src_depth <= 8) {
		psz = 0;	/* PSZ Bit[5] */
	} else {
		psz = 1;	/* PSZ Bit[5] */
	}

	/* interpolation error */
	if (src_depth <= 8) {
		interpolation_error = 2;
	} else if (src_depth == 9) {
		interpolation_error = 4;
	} else if (src_depth == 10) {
		interpolation_error = 8;
	} else if (src_depth == 11) {
		interpolation_error = 16;
	} else if (src_depth == 12) {
		interpolation_error = 32;
	} else {
		interpolation_error = 32;
	}

	/* max intensity */
	max_value = (1 << src_depth) - 1;

	/* Set Mode */
	reg_val =
	    dd_AFFINE_register_pack_mode(0, interpolation_mode, conv_mode, psz,
					 0, process_direction,
					 table_sampling_interval, fill_value);
	iowrite32(reg_val,
		  dev->reg_base +
		  AFFINE_OFFSET(IRECOG_raffine_Mode_Register_OFFS));

	/* Set ADJP */
	reg_val = dd_AFFINE_register_pack_adj_p(interpolation_error, max_value);
	iowrite32(reg_val,
		  dev->reg_base +
		  AFFINE_OFFSET(IRECOG_raffine_output_picture_correction_OFFS));
}

static inline void affine_config_image(struct affine_dev *dev,
				       ULONG src_addr,
				       ULONG src_width,
				       ULONG src_height,
				       ULONG src_pitch,
				       ULONG dst_addr,
				       ULONG dst_offset_x,
				       ULONG dst_offset_y,
				       ULONG dst_width,
				       ULONG dst_height, ULONG dst_pitch)
{
	REG_32 reg_val;

	/* Set src size */
	reg_val = dd_AFFINE_register_pack_size(src_width, src_height);
	iowrite32(reg_val,
		  dev->reg_base +
		  AFFINE_OFFSET(IRECOG_raffine_input_picture_size_OFFS));

	/* Set src addr */
	iowrite32(src_addr,
		  dev->reg_base +
		  AFFINE_OFFSET(IRECOG_raffine_input_picture_address_OFFS));

	/* Set dst pos */
	reg_val = dd_AFFINE_register_pack_bgn(dst_offset_x, dst_offset_y);
	iowrite32(reg_val,
		  dev->reg_base +
		  AFFINE_OFFSET(IRECOG_raffine_output_coordinate_origin_OFFS));

	/* Set dst size */
	reg_val = dd_AFFINE_register_pack_size(dst_width, dst_height);
	iowrite32(reg_val,
		  dev->reg_base +
		  AFFINE_OFFSET(IRECOG_raffine_output_picture_size_OFFS));

	/* Set dst addr */
	iowrite32(dst_addr,
		  dev->reg_base +
		  AFFINE_OFFSET(IRECOG_raffine_output_picture_address_OFFS));

	/* Set pitch */
	reg_val = dd_AFFINE_register_pack_pitch(src_pitch, dst_pitch);
	iowrite32(reg_val,
		  dev->reg_base +
		  AFFINE_OFFSET
		  (IRECOG_raffine_input_output_picture_pitch_OFFS));
}

SINT affine_config_transformation(struct affine_dev *dev,
				  struct affine_transformation_param *param,
				  ULONG dst_addr, ULONG src_addr)
{
	/* Set operation registers */
	affine_config_operation(dev,
				param->src_depth,
				param->interpolation_mode,
				AFFINE_CNV_MODE_TRANS,
				param->process_direction, param->fill_value, 0);

	/* Set input/output registers */
	affine_config_image(dev,
			    src_addr,
			    param->src_width,
			    param->src_height,
			    param->src_pitch,
			    dst_addr,
			    param->dst_offset_x,
			    param->dst_offset_y,
			    param->dst_width,
			    param->dst_height, param->dst_pitch);

	/* Set affine parameter */
	iowrite32(param->affn_p0,
		  dev->reg_base +
		  AFFINE_OFFSET(IRECOG_raffine_affine_parameter0_OFFS));
	iowrite32(param->affn_p1,
		  dev->reg_base +
		  AFFINE_OFFSET(IRECOG_raffine_affine_parameter1_OFFS));
	iowrite32(param->affn_p2,
		  dev->reg_base +
		  AFFINE_OFFSET(IRECOG_raffine_affine_parameter2_OFFS));
	iowrite32(param->affn_p3,
		  dev->reg_base +
		  AFFINE_OFFSET(IRECOG_raffine_affine_parameter3_OFFS));
	iowrite32(param->affn_p4,
		  dev->reg_base +
		  AFFINE_OFFSET(IRECOG_raffine_affine_parameter4_OFFS));
	iowrite32(param->affn_p5,
		  dev->reg_base +
		  AFFINE_OFFSET(IRECOG_raffine_affine_parameter5_OFFS));

	return 0;
}

SINT affine_config_table(struct affine_dev *dev,
			 struct affine_table_param *param,
			 ULONG dst_addr, ULONG src_addr, ULONG table_addr)
{
	REG_32 reg_val;

	/* Set operation registers */
	affine_config_operation(dev,
				param->src_depth,
				param->interpolation_mode,
				AFFINE_CNV_MODE_TABLE,
				param->process_direction,
				param->fill_value,
				param->table_sampling_interval);

	/* Set input/output registers */
	affine_config_image(dev,
			    src_addr,
			    param->src_width,
			    param->src_height,
			    param->src_pitch,
			    dst_addr,
			    param->dst_offset_x,
			    param->dst_offset_y,
			    param->dst_width,
			    param->dst_height, param->dst_pitch);

	/* Set table parameter */
	iowrite32(table_addr,
		  dev->reg_base +
		  AFFINE_OFFSET(IRECOG_raffine_table_address_OFFS));
	reg_val = dd_AFFINE_register_pack_tbl_pitch(param->table_pitch);
	iowrite32(reg_val,
		  dev->reg_base +
		  AFFINE_OFFSET(IRECOG_raffine_table_pitch_OFFS));

	return 0;
}

SINT affine_config_undistort(struct affine_dev *dev,
			     struct affine_undistort_param *param,
			     ULONG dst_addr, ULONG src_addr)
{
	/* Set operation registers */
	affine_config_operation(dev,
				param->src_depth,
				param->interpolation_mode,
				AFFINE_CNV_MODE_UNDIST,
				param->process_direction, param->fill_value, 0);

	/* Set input/output registers */
	affine_config_image(dev,
			    src_addr,
			    param->src_width,
			    param->src_height,
			    param->src_pitch,
			    dst_addr,
			    param->dst_offset_x,
			    param->dst_offset_y,
			    param->dst_width,
			    param->dst_height, param->dst_pitch);

	/* Set distortion compensation formula parameter */
	iowrite32(param->dist_p0,
		  dev->reg_base +
		  AFFINE_OFFSET
		  (IRECOG_raffine_strain_compensation_parameter0_OFFS));
	iowrite32(param->dist_p1,
		  dev->reg_base +
		  AFFINE_OFFSET
		  (IRECOG_raffine_strain_compensation_parameter1_OFFS));
	iowrite32(param->dist_p2,
		  dev->reg_base +
		  AFFINE_OFFSET
		  (IRECOG_raffine_strain_compensation_parameter2_OFFS));
	iowrite32(param->dist_p3,
		  dev->reg_base +
		  AFFINE_OFFSET
		  (IRECOG_raffine_strain_compensation_parameter3_OFFS));
	iowrite32(param->dist_p4,
		  dev->reg_base +
		  AFFINE_OFFSET
		  (IRECOG_raffine_strain_compensation_parameter4_OFFS));
	iowrite32(param->dist_p5,
		  dev->reg_base +
		  AFFINE_OFFSET
		  (IRECOG_raffine_strain_compensation_parameter5_OFFS));
	iowrite32(param->dist_p6,
		  dev->reg_base +
		  AFFINE_OFFSET
		  (IRECOG_raffine_strain_compensation_parameter6_OFFS));
	iowrite32(param->dist_p7,
		  dev->reg_base +
		  AFFINE_OFFSET
		  (IRECOG_raffine_strain_compensation_parameter7_OFFS));
	iowrite32(param->dist_p8,
		  dev->reg_base +
		  AFFINE_OFFSET
		  (IRECOG_raffine_strain_compensation_parameter8_OFFS));
	iowrite32(param->dist_p9,
		  dev->reg_base +
		  AFFINE_OFFSET
		  (IRECOG_raffine_strain_compensation_parameter9_OFFS));
	iowrite32(param->dist_p10,
		  dev->reg_base +
		  AFFINE_OFFSET
		  (IRECOG_raffine_strain_compensation_parameter10_OFFS));
	iowrite32(param->dist_p11,
		  dev->reg_base +
		  AFFINE_OFFSET
		  (IRECOG_raffine_strain_compensation_parameter11_OFFS));

	return 0;
}
