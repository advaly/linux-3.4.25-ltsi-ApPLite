/*
 * linux/drivers/staging/applite/irecog/gdmac_hand_detect_isolate/gdmac_filter.h
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
#ifndef __GDMAC_FILTER_H__
#define __GDMAC_FILTER_H__

#include "filter_descript.h"
#include "gdmac_instructions.h"

/* HIF parameter base address */
#define FILTER_FW_IMAGE         (0x90000000)

/** Number of Filter Input/Output Channels */
#define FILTER_INCH_NUM      (4)
#define FILTER_OUTCH_NUM     (4)
#define FILTER_PARA_NUM      (4)

struct filter_dev {
	gdmac_inst *inst;
	unsigned long reg_base;
	void __iomem *param_base;
	int param_size;
	/*  int hif_param_num; */
#ifndef ENABLE_QEMU_FPARAM
	void *filter_base_virt;
	unsigned long filter_base_phys;
#endif
};

SSHORT *dd_gdmac_FILTER_get_HIF_address(struct filter_dev *dev,
					SINT sequence_id,
							      /**< Filter Sequence Id */
					UINT HIF_address);    /**< HIF Address */
SINT dd_gdmac_FILTER_send_request(struct filter_dev *dev,
				  FILTER_DESCRIPT *descript);

void filter_clear_int(struct filter_dev *dev);

#endif /* __GDMAC_FILTER_H__ */
