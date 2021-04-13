/*
 * linux/drivers/staging/applite/irecog/pyramid/pyramid_driver.h
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
#ifndef __PYRAMID_DRIVER_H__
#define __PYRAMID_DRIVER_H__

#include <linux/applite/irecog/drv_cmn.h>
#include "drv_defs.h"
#include "pyramid_public.h"

#define _RS_CS_YHFILBASE_INTERVAL 0x80
#define _RS_CS_YVFILBASE_INTERVAL 0x80
#define _RS_CS_CHFILBASE_INTERVAL 0x80
#define _RS_CS_CVFILBASE_INTERVAL 0x80
#define _RS_CS_YHVSZOUT_INTERVAL 0x08
#define _RS_CS_CHVSZOUT_INTERVAL 0x08
#define _RS_CS_OAOUTSET_INTERVAL 0x4
#define _RS_CS_OAOUTSET_NUM      4
#define _RS_CS_HOAOUTSET_INTERVAL 0x80
#define _RS_CS_HOAOUTSET_NUM      4
#define _RS_CS_VOAOUTSET_INTERVAL 0x80
#define _RS_CS_VOAOUTSET_NUM      4

/**************************************************/
/*
 * version definitions
 */
/**************************************************/
#define DRV_PYRAMID_VERSION_MAJOR      DRV_VERSION_MAJOR
#define DRV_PYRAMID_VERSION_MINOR      9
#define DRV_PYRAMID_VERSION_SUBMINOR   0
#define DRV_PYRAMID_VERSION_STR        DRV_STR(DRV_PYRAMID_VERSION_MAJOR) "." DRV_STR(DRV_PYRAMID_VERSION_MINOR) "." DRV_STR(DRV_PYRAMID_VERSION_SUBMINOR)

#define PYRAMID_MAJOR     0	/* dynamic allocation */
#define PYRAMID_MINOR     0
#define PYRAMID_NR_DEVS   1

#define PYRAMID_NAME "pyramid"

#endif /* __PYRAMID_DRIVER_H__ */
