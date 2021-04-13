/*
 * linux/include/linux/applite/hog_param.h
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
#ifndef __HOG_PARAM_H__
#define __HOG_PARAM_H__

#include "basic_type.h"
#include "drv_cache_ctrl_defs.h"

#define HOG_DICT_BANK_MODE0     0
#define HOG_DICT_BANK_MODE1     1

struct roi_coord {
	ULONG x;
	ULONG y;
};

struct hog_dict_param {
	ULONG dict_num;
	ULONG cell_num_w;
	ULONG cell_num_h;
	ULONG cell_size_w;
	ULONG cell_size_h;
	ULONG weight_size;
	ULONG weight_adr;
	ULONG format_size;
	ULONG format_adr;
	ULONG buffer_cache_ctl;
};

struct hog_svm_position_param {
	ULONG dict_num;
	ULONG cell_num_w;
	ULONG cell_num_h;
	ULONG cell_size_w;
	ULONG cell_size_h;
	ULONG roi_num;
	struct roi_coord *roi_list;
	ULONG dir_adr;
	ULONG dir_pitch;
	ULONG dir_height;
	ULONG dst_adr;
	ULONG buffer_cache_ctl;
};

struct hog_svm_region_param {
	ULONG dict_num;
	ULONG cell_num_w;
	ULONG cell_num_h;
	ULONG cell_size_w;
	ULONG cell_size_h;
	ULONG roi_num_w;
	ULONG roi_num_h;
	ULONG roi_stride_w;
	ULONG roi_stride_h;
	ULONG dir_adr;
	ULONG dir_pitch;
	ULONG dir_width;
	ULONG dir_height;
	ULONG dst_adr;
	ULONG buffer_cache_ctl;
};

#endif /* __HOG_PARAM_H__ */
