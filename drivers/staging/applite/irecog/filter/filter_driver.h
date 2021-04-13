/*
 * linux/drivers/staging/applite/irecog/filter/filter_driver.h
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
#ifndef __FILTER_DRIVER_H__
#define __FILTER_DRIVER_H__

#include <linux/applite/irecog/basic_type.h>
#include <linux/applite/irecog/drv_cmn.h>

#include <linux/platform_device.h>
#include <linux/pm_runtime.h>

#include "filter_public.h"
#include "filter_descript.h"
#include "drv_defs.h"

/**************************************************/
/*
 * version definitions
 */
/**************************************************/
#define DRV_FILTER_VERSION_MAJOR      DRV_VERSION_MAJOR
#define DRV_FILTER_VERSION_MINOR      12
#define DRV_FILTER_VERSION_SUBMINOR   0
#define DRV_FILTER_VERSION_STR        DRV_STR(DRV_FILTER_VERSION_MAJOR) "." DRV_STR(DRV_FILTER_VERSION_MINOR) "." DRV_STR(DRV_FILTER_VERSION_SUBMINOR)

/* param buff size (32KB) */
#define PARAM_BUFF_SIZE                     (32768)

/* chardev */
#define FILTER_MAJOR                        0	/* dynamic allocation */
#define FILTER_MINOR                        0
#define FILTER_NR_DEVS                      1

/* control register */
#define FILTER_NAME                         "filter"

/* Reset Command */
#define FILTER_RESET_BIT  (0x02)

/* Interrupt Status */
#define FILTER_HW_INIT_END           (1U<<0)
#define FILTER_HW_NON_LAST_IMG_END   (1U<<1)
#define FILTER_HW_LAST_IMG_END       (1U<<2)
#define FILTER_HW_NON_LAST_PARAM_END (1U<<3)
#define FILTER_HW_LAST_PARAM_END     (1U<<4)
#define FILTER_HW_LSC_ERROR          (1U<<9)
#define FILTER_HW_QF_ERROR           (1U<<11)
#define FILTER_HW_LME_ERROR          (1U<<13)
#define FILTER_HW_PSBAC_ERROR        (1U<<14)

#define FILTER_HW_ERROR_STATUS  (FILTER_HW_LSC_ERROR | \
				FILTER_HW_QF_ERROR | \
				FILTER_HW_LME_ERROR | \
				FILTER_HW_PSBAC_ERROR)

/* Filter status */
#define FILTER_STATUS_INIT_KICKED   0
#define FILTER_STATUS_INIT_DONE     1
#define FILTER_STATUS_EXE_DONE      2
#define FILTER_STATUS_ERROR         3
#define FILTER_STATUS_OTHERS        4

/* HIF parameter base address */
#define FILTER_FW_IMAGE         (0x90000000)

/** Number of Filter Input/Output Channels */
#define FILTER_INCH_NUM      (4)
#define FILTER_OUTCH_NUM     (4)
#define FILTER_PARA_NUM      (4)

/* parameter */
#define FILTER_MAX_IMG_WIDTH						1280
#define FILTER_MAX_IMG_HEIGHT						1024

#define FILTER_SOBEL_DIR_MIN_IMG_WIDTH				66
#define FILTER_SOBEL_DIR_MIN_IMG_HEIGHT				4
#define FILTER_SOBEL_DIR_MAX_IMG_WIDTH				FILTER_MAX_IMG_WIDTH
#define FILTER_SOBEL_DIR_MAX_IMG_HEIGHT				FILTER_MAX_IMG_HEIGHT

#define FILTER_IMG_SMOOTH_MIN_IMG_WIDTH				72
#define FILTER_IMG_SMOOTH_MIN_IMG_HEIGHT			16
#define FILTER_IMG_SMOOTH_MAX_IMG_WIDTH				FILTER_MAX_IMG_WIDTH
#define FILTER_IMG_SMOOTH_MAX_IMG_HEIGHT			FILTER_MAX_IMG_HEIGHT

#define FILTER_AVE_IMG_MAX_IMG_WIDTH				640
#define FILTER_AVE_IMG_MAX_IMG_HEIGHT				480

#define FILTER_CORRECT_COLOR_MIN_IMG_WIDTH			80
#define FILTER_CORRECT_COLOR_MIN_IMG_HEIGHT			4
#define FILTER_CORRECT_COLOR_MAX_IMG_WIDTH			FILTER_MAX_IMG_WIDTH
#define FILTER_CORRECT_COLOR_MAX_IMG_HEIGHT			FILTER_MAX_IMG_HEIGHT

#define FILTER_TONEMAP_LUMA_MIN_IMG_WIDTH			80
#define FILTER_TONEMAP_LUMA_MIN_IMG_HEIGHT		4
#define FILTER_TONEMAP_LUMA_MAX_IMG_WIDTH			FILTER_MAX_IMG_WIDTH
#define FILTER_TONEMAP_LUMA_MAX_IMG_HEIGHT		FILTER_MAX_IMG_HEIGHT

#define FILTER_NR_MIN_IMG_WIDTH			80
#define FILTER_NR_MIN_IMG_HEIGHT		4
#define FILTER_NR_MAX_IMG_WIDTH			FILTER_MAX_IMG_WIDTH
#define FILTER_NR_MAX_IMG_HEIGHT		FILTER_MAX_IMG_HEIGHT

#define FILTER_NR_MIN_TH			0
#define FILTER_NR_MAX_TH			255

#define FILTER_LPITCH_ALIGN_MASK	0x0000003f	/* 64byte alignment */

#define FILTER_IMG_DEPTH8							8
#define FILTER_IMG_DEPTH16							16

#define FILTER_IMG_SMOOTH_FILTER_SIZE_3				3
#define FILTER_IMG_SMOOTH_FILTER_SIZE_5				5

#define FILTER_IMG_SMOOTH_MIN_NORMALIZER			0
#define FILTER_IMG_SMOOTH_MAX_NORMALIZER			16

#define FILTER_CORRECT_COLOR_MIN_COLOR_RATE			16
#define FILTER_CORRECT_COLOR_MAX_COLOR_RATE			63

#define FILTER_TONEMAPPING_LUMA_MIN_BLEND			0
#define FILTER_TONEMAPPING_LUMA_MAX_BLEND			255

#define FILTER_TONEMAPPING_LUMA_BLOCK_W 8
#define FILTER_TONEMAPPING_LUMA_BLOCK_H 5
#define FILTER_TONEMAPPING_LUMA_BIN_NUM 256
#define FILTER_TONEMAPPING_LUMA_LUT_SIZE (8192*2)

struct filter_dev {
	struct cdev cdev;
	struct device *device;
	struct platform_device *pdev;
	void __iomem *reg_base;

	/* memory region for filter parameter */
	void __iomem *param_base;
	int param_size;

	int hif_param_num;

#ifndef ENABLE_QEMU_FPARAM
	void *filter_base_virt;
	unsigned long filter_base_phys;
#endif

	FILTER_HIF_PARAM *tonemap_hif_param;
	void *tonemap;

	unsigned long buffer_cache_ctl;
};

struct filter_dev_set {
	struct filter_dev ioctl_dev;
};

SSHORT *dd_FILTER_get_HIF_address(struct filter_dev *dev, SINT sequence_id,
				      /**< Filter Sequence Id */
				  UINT HIF_address);
			      /**< HIF Address */
SINT dd_FILTER_send_request(struct filter_dev *dev, FILTER_DESCRIPT *descript);

#endif /* __FILTER_DRIVER_H__ */
