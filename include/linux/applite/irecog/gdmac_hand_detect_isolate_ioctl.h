/*
 * linux/include/linux/applite/gdmac_hand_detect_isolate_ioctl.h
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
#ifndef __GDMAC_HAND_DETECT_ISOLATE_IOCTL_H__
#define __GDMAC_HAND_DETECT_ISOLATE_IOCTL_H__

#include <linux/ioctl.h>
#include "hog_param.h"
#include "drv_cache_ctrl_defs.h"

#define GDMAC_HAND_DETECT_ISOLATE_DICT_NUM  2
#define GDMAC_HAND_DETECT_ISOLATE_LAYER_NUM 9

/* image size */
#define DIR_IMAGE_OUT0_W 380	/* layer0 */
#define DIR_IMAGE_OUT0_H 285
#define DIR_IMAGE_OUT1_W 320	/* layer1 */
#define DIR_IMAGE_OUT1_H 240
#define DIR_IMAGE_OUT2_W 269	/* layer2 */
#define DIR_IMAGE_OUT2_H 201
#define DIR_IMAGE_OUT3_W 226	/* layer3 */
#define DIR_IMAGE_OUT3_H 169
#define DIR_IMAGE_OUT4_W 190	/* layer4 */
#define DIR_IMAGE_OUT4_H 142
#define DIR_IMAGE_OUT5_W 160	/* layer5 */
#define DIR_IMAGE_OUT5_H 120
#define DIR_IMAGE_OUT6_W 134	/* layer6 */
#define DIR_IMAGE_OUT6_H 100
#define DIR_IMAGE_OUT7_W 113	/* layer7 */
#define DIR_IMAGE_OUT7_H  84
#define DIR_IMAGE_OUT8_W  95	/* layer8 */
#define DIR_IMAGE_OUT8_H  71

#define HAND_NUM_ONE  1
#define HAND_NUM_BOTH 2

struct hog_setting {
	ULONG input_image_pitch;
	ULONG input_image_adr;
	USHORT threshold;

	/* roi param */
	ULONG roi_num[GDMAC_HAND_DETECT_ISOLATE_DICT_NUM];
	struct roi_coord *roi_list[GDMAC_HAND_DETECT_ISOLATE_DICT_NUM];

	/* region param */
	ULONG roi_num_w[GDMAC_HAND_DETECT_ISOLATE_DICT_NUM];
	ULONG roi_num_h[GDMAC_HAND_DETECT_ISOLATE_DICT_NUM];
	ULONG roi_stride_w[GDMAC_HAND_DETECT_ISOLATE_DICT_NUM];
	ULONG roi_stride_h[GDMAC_HAND_DETECT_ISOLATE_DICT_NUM];

	ULONG dst_adr[GDMAC_HAND_DETECT_ISOLATE_DICT_NUM];
	ULONG dst_dir_thr_adr;
	ULONG dst_dir_nothr_adr;
	ULONG dst_dir_int_adr;
};

typedef struct {
	struct hog_dict_param dict[GDMAC_HAND_DETECT_ISOLATE_DICT_NUM];
	struct hog_setting setting[GDMAC_HAND_DETECT_ISOLATE_LAYER_NUM];
	ULONG dict_bank_mode;
	ULONG hand_num;
	ULONG layer_min;
	ULONG layer_max;
	ULONG buffer_cache_ctl;
} gdmac_hand_detect_isolate;

#define GDMAC_HAND_DETECT_ISOLATE_REG_TYPE_SECURE     0
#define GDMAC_HAND_DETECT_ISOLATE_REG_TYPE_NON_SECURE 1

#define GDMAC_HAND_DETECT_ISOLATE_IOCTL_MAGIC  0x00
#define GDMAC_IOCTL_HAND_DETECT_ISOLATE                 _IOW(GDMAC_HAND_DETECT_ISOLATE_IOCTL_MAGIC, 0x0, gdmac_hand_detect_isolate)
#define GDMAC_IOCTL_HAND_DETECT_ISOLATE_GET_VERSION     _IO(GDMAC_HAND_DETECT_ISOLATE_IOCTL_MAGIC, 0x1)
#define GDMAC_IOCTL_HAND_DETECT_ISOLATE_SET_FPARAM_ADDR _IOW(GDMAC_HAND_DETECT_ISOLATE_IOCTL_MAGIC, 0x2, uint32_t)
#define GDMAC_IOCTL_HAND_DETECT_ISOLATE_SET_REG_TYPE    _IOW(GDMAC_HAND_DETECT_ISOLATE_IOCTL_MAGIC, 0x3, uint32_t)
#define GDMAC_IOCTL_HAND_DETECT_ISOLATE_INITIALIZE      _IO(GDMAC_HAND_DETECT_ISOLATE_IOCTL_MAGIC,  0x4)

#define GDMAC_IOCTL_HAND_DETECT_ISOLATE_REGION          _IOW(GDMAC_HAND_DETECT_ISOLATE_IOCTL_MAGIC, 0x5, gdmac_hand_detect_isolate)

#endif /* __GDMAC_HAND_DETECT_ISOLATE_IOCTL_H__ */
