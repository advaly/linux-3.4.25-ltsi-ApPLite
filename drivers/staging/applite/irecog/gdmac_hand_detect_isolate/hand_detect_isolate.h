/*
 * linux/drivers/staging/applite/irecog/gdmac_hand_detect_isolate/hand_detect_isolate.h
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
#ifndef __HAND_DETECT_ISOLATE_H__
#define __HAND_DETECT_ISOLATE_H__

#define MAX_TRANS_NUM 10

#include <linux/applite/irecog/gdmac_hand_detect_isolate_ioctl.h>

#include "hog.h"
#include "gdmac_filter.h"
#include "gdmac_instructions.h"

#define ROI_MODE    0
#define REGION_MODE 1

int hand_detect_isolate_initialize(struct hog_dev hog[],
				   struct dict_dev *dict,
				   struct filter_dev *filter);

void hand_detect_isolate_finalize(void);

int hand_detect_isolate_create_instructions(gdmac_inst *instructions[],
					    struct hog_dev hog[],
					    struct dict_dev *dict,
					    struct filter_dev *filter,
					    gdmac_hand_detect_isolate *param,
					    int32_t mode);

int hand_detect_isolate_create_instructions_one_hand(gdmac_inst *instructions[],
						     struct hog_dev hog[],
						     struct dict_dev *dict,
						     struct filter_dev *filter,
						     gdmac_hand_detect_isolate
						     *param, int32_t mode);

int hand_detect_isolate_create_instructions_single(gdmac_inst *instructions[],
						   struct hog_dev hog[],
						   struct dict_dev *dict,
						   struct filter_dev *filter,
						   gdmac_hand_detect_isolate
						   *param, int32_t mode);

int hand_detect_isolate_parameter_check(gdmac_hand_detect_isolate *param,
					int32_t mode);

void hand_detect_isolate_cache_flush(gdmac_hand_detect_isolate *param);
void hand_detect_isolate_cache_invalidate(gdmac_hand_detect_isolate *param);

#endif /* __HAND_DETECT_ISOLATE_H__ */
