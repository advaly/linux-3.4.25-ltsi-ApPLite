/*
 * linux/drivers/staging/applite/irecog/gdmac_pyramid/gdmac_pyramid_driver.h
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
#ifndef __GDMAC_PYRAMID_DRIVER_H__
#define __GDMAC_PYRAMID_DRIVER_H__

#include <linux/applite/irecog/drv_cmn.h>

/**************************************************/
/*
 * version definitions
 */
/**************************************************/
#define DRV_GDMAC_PYRAMID_VERSION_MAJOR      DRV_VERSION_MAJOR
#define DRV_GDMAC_PYRAMID_VERSION_MINOR      12
#define DRV_GDMAC_PYRAMID_VERSION_SUBMINOR   0
#define DRV_GDMAC_PYRAMID_VERSION_STR        DRV_STR(DRV_GDMAC_PYRAMID_VERSION_MAJOR) "." DRV_STR(DRV_GDMAC_PYRAMID_VERSION_MINOR) "." DRV_STR(DRV_GDMAC_PYRAMID_VERSION_SUBMINOR)

#define GDMAC_PYRAMID_MAJOR 0
#define GDMAC_PYRAMID_MINOR 0
#define GDMAC_PYRAMID_NR_DEVS 1

#define GDMAC_PYRAMID_NAME "gdmac_pyramid"

#endif /*  __GDMAC_PYRAMID_DRIVER_H__ */
