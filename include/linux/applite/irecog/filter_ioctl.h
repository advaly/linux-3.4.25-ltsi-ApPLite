/*
 * linux/include/linux/applite/filter_ioctl.h
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
#ifndef __FILTER_IOCTL_H__
#define __FILTER_IOCTL_H__

#include <linux/ioctl.h>
#include "drv_cmn.h"
#include "filter_param.h"

/*
// PYRAMID: 0xB9
// AFFINE: 0xBA
// HIST: 0xBB
// MATCH: 0xBC
// HOG0: 0xBD
// HOG1: 0xBE
// FILTER: 0xBF
*/

#define FILTER_IOCTL_MAGIC          (0xBF)

#define FILTER_IOCTL_SOBEL_DIRECTIION3x3 _IOW(FILTER_IOCTL_MAGIC, 0x00, struct filter_sobel_direction3x3_param)
#define FILTER_IOCTL_IMAGE_SMOOTHING     _IOW(FILTER_IOCTL_MAGIC, 0x01, struct filter_image_smoothing_param)
#define FILTER_IOCTL_AVERAGE_IMAGE       _IOW(FILTER_IOCTL_MAGIC, 0x02, struct filter_average_image_param)
#define FILTER_IOCTL_GET_VERSION         _IOR(FILTER_IOCTL_MAGIC, 0x03, drv_version_t)
#define FILTER_IOCTL_SET_FPARAM_ADDR     _IOW(FILTER_IOCTL_MAGIC, 0x04, uint32_t)
#define FILTER_IOCTL_INITIALIZE          _IO(FILTER_IOCTL_MAGIC,  0x05)
#define FILTER_IOCTL_TONEMAPPING_LUMA    _IOW(FILTER_IOCTL_MAGIC, 0x06, struct filter_tonemapping_luma_param)
#define FILTER_IOCTL_CORRECT_COLOR       _IOW(FILTER_IOCTL_MAGIC, 0x07, struct filter_correct_color_param)
#define FILTER_IOCTL_NOISE_REDUCTION_Y   _IOW(FILTER_IOCTL_MAGIC, 0x08, struct filter_noise_reduction_y_param)
#define FILTER_IOCTL_NOISE_REDUCTION_UV  _IOW(FILTER_IOCTL_MAGIC, 0x09, struct filter_noise_reduction_uv_param)
#define FILTER_IOCTL_BUS_INIT            _IO(FILTER_IOCTL_MAGIC,  0x06)

#endif /* __FILTER_IOCTL_H__ */
