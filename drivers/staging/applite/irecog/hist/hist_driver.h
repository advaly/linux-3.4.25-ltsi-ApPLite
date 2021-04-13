/*
 * linux/drivers/staging/applite/irecog/hist/hist_driver.h
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
#ifndef __HIST_DRIVER_H__
#define __HIST_DRIVER_H__

#include <linux/applite/irecog/drv_cmn.h>

#include <linux/platform_device.h>
#include <linux/pm_runtime.h>

#include <mach/regs/irecog_offs_def.h>
#include <mach/regs/irecog_reg_def.h>
#include "drv_defs.h"
#include "drv_dmabuf.h"

/**************************************************/
/*
 * version definitions
 */
/**************************************************/
#define DRV_HIST_VERSION_MAJOR        DRV_VERSION_MAJOR
#define DRV_HIST_VERSION_MINOR        3
#define DRV_HIST_VERSION_SUBMINOR     0
#define DRV_HIST_VERSION_STR          DRV_STR(DRV_HIST_VERSION_MAJOR) "." DRV_STR(DRV_HIST_VERSION_MINOR) "." DRV_STR(DRV_HIST_VERSION_SUBMINOR)

#define HIST_MAJOR            0	/* dynamic allocation */
#define HIST_MINOR            0
#define HIST_NR_DEVS          1

#define HIST_NAME             "hist"


struct hist_dev {
	struct cdev cdev;
	struct device *device;
	struct platform_device *pdev;
	void __iomem *reg_base;

	struct drv_dmabuf_conv_adr src_buf;
	struct drv_dmabuf_conv_adr score_buf;
	struct drv_dmabuf_conv_adr dst_buf;
};


#endif /* __HIST_DRIVER_H__ */
