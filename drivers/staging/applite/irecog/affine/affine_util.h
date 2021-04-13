/*
 * linux/drivers/staging/applite/irecog/affine/affine_util.h
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
#ifndef __AFFINE_UTIL_H__
#define __AFFINE_UTIL_H__

#include <linux/applite/irecog/affine_param.h>

#include "affine_driver.h"

SINT affine_config_transformation(struct affine_dev *dev,
				  struct affine_transformation_param *param,
				  ULONG dst_addr, ULONG src_addr);

SINT affine_config_undistort(struct affine_dev *dev,
			     struct affine_undistort_param *param,
			     ULONG dst_addr, ULONG src_addr);

SINT affine_config_table(struct affine_dev *dev,
			 struct affine_table_param *param,
			 ULONG dst_addr, ULONG src_addr, ULONG table_addr);

#endif /* __AFFINE_UTIL_H__ */
