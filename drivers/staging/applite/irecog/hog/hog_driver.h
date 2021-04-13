/*
 * linux/drivers/staging/applite/irecog/hog/hog_driver.h
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
#ifndef __HOG_DRIVER_H__
#define __HOG_DRIVER_H__

#include <linux/applite/irecog/drv_cmn.h>

#include <linux/platform_device.h>
#include <linux/pm_runtime.h>

#include "drv_defs.h"
#include "hog_public.h"

/**************************************************/
/*
 * version definitions
 */
/**************************************************/
#define DRV_HOG_VERSION_MAJOR      DRV_VERSION_MAJOR
#define DRV_HOG_VERSION_MINOR      11
#define DRV_HOG_VERSION_SUBMINOR   0
#define DRV_HOG_VERSION_STR        DRV_STR(DRV_HOG_VERSION_MAJOR) "." DRV_STR(DRV_HOG_VERSION_MINOR) "." DRV_STR(DRV_HOG_VERSION_SUBMINOR)

#define HOG_ELEM_NUM    2
#define HOG_ELEM_NR_DEVS    1
#define DICT_NR_DEVS    1

#define HOG_MAJOR       0	/* dynamic allocation */
#define HOG_MINOR       0
#define HOG_NR_DEVS     (HOG_ELEM_NUM * HOG_ELEM_NR_DEVS + DICT_NR_DEVS)

#define HOG_NAME        "hog"
#define HOG0_NAME       "hog0"
#define HOG1_NAME       "hog1"
#define DICT_NAME       "dict"

/* status */
#define HOG_EXE_DONE    0x0
#define HOG_KICKED      0x1
#define HOG_LINEOUT     0x2
#define HOG_ERROR       0x3

#define HOG_DEV_IOCTL   0

#define DICT_DEV_IOCTL  0

#define HOG_HW_END              0x1
#define HOG_HW_LINE_OUT_END     0x100

struct hog_dev {
	struct cdev cdev;
	struct device *device;
	struct platform_device *pdev;
	void __iomem *reg_base;

	int *status;
	wait_queue_head_t *wq;
	struct semaphore *sem;
	struct hog_dev *dev_base;

	int *roi_mode;
	int *roi_num;
	unsigned int *func;
};

struct dict_dev {
	struct cdev cdev;
	struct device *device;
	struct platform_device *pdev;
	void __iomem *reg_base;
};

#endif /* __HOG_DRIVER_H__ */
