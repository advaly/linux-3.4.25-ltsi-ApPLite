/*
 * linux/drivers/staging/applite/irecog/affine/affine_driver.h
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
#ifndef __AFFINE_DRIVER_H__
#define __AFFINE_DRIVER_H__

#include <linux/applite/irecog/drv_cmn.h>

#include <linux/platform_device.h>
#include <linux/pm_runtime.h>

#include <mach/regs/irecog_offs_def.h>
#include <mach/regs/irecog_reg_def.h>
#include "drv_defs.h"

/* temporary add */
#define AFFINE_OFFSET(x) ((x) - IRECOG_raffine_Control_Register_OFFS)

/* Interrupt status */
#define AFFINE_STATC_HW_END     1
/* reset */
#define AFFINE_RESET            0xe
/* Affine Int Clear Bits */
#define AFFINE_CLEAR_BITS                      (0xFFFFUL)
/* Interrupt Mask Setting */
#define AFFINE_INTMASK_NORMAL   0x0	/* no mask */
/* cnv mode */
#define AFFINE_CNV_MODE_TRANS   0
#define AFFINE_CNV_MODE_TABLE   1
#define AFFINE_CNV_MODE_UNDIST  2
/* temporary add */

/**************************************************/
/*
 * version definitions
 */
/**************************************************/
#define DRV_AFFINE_VERSION_MAJOR        DRV_VERSION_MAJOR
#define DRV_AFFINE_VERSION_MINOR        6
#define DRV_AFFINE_VERSION_SUBMINOR     0
#define DRV_AFFINE_VERSION_STR          DRV_STR(DRV_AFFINE_VERSION_MAJOR) "." DRV_STR(DRV_AFFINE_VERSION_MINOR) "." DRV_STR(DRV_AFFINE_VERSION_SUBMINOR)

#define AFFINE_MAJOR            0	/* dynamic allocation */
#define AFFINE_MINOR            0
#define AFFINE_NR_DEVS          1

#define AFFINE_NAME             "affine"

/* status */
#define AFFINE_EXE_DONE         0x0
#define AFFINE_KICKED           0x1
#define AFFINE_ERROR            0x2

#define AFFINE_MAX_IMG_WIDTH    2048
#define AFFINE_MAX_IMG_HEIGHT   2048
#define AFFINE_MAX_IMG_PITCH    2048

#define AFFINE_MIN_IMG_WIDTH    1
#define AFFINE_MIN_IMG_HEIGHT   1
#define AFFINE_MIN_IMG_PITCH    64

#define AFFINE_MAX_CENTER_X     (2047.0F)
#define AFFINE_MAX_CENTER_Y     (2047.0F)
#define AFFINE_MIN_CENTER_X     (0.0F)
#define AFFINE_MIN_CENTER_Y     (0.0F)

struct affine_dev {
	struct cdev cdev;
	struct device *device;
	struct platform_device *pdev;
	void __iomem *reg_base;
};

#endif /* __AFFINE_DRIVER_H__ */
