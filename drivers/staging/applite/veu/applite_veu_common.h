/*
 * drivers/staging/applite/veu/applite_veu_common.h
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

#if !defined(__VEU_DRIVER_COMMON_MODULE_H__)
#define __VEU_DRIVER_COMMON_MODULE_H__

/*===================================
include Files
===================================*/
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/list.h>
#include <linux/semaphore.h>
#include <linux/wait.h>
#include <linux/interrupt.h>

#include "ve_api.h"

/*===================================
Types and structures defined
===================================*/


/*===================================
Exported Variables
===================================*/


/*===================================
Exported Functions prototypes
===================================*/

static inline void veu_com_frameid_clear(struct veu_frameid_tbl *ftbl)
{
	ftbl->frameid_wp = 0;
	ftbl->frameid_rp_encoded = 0;
	ftbl->frameid_rp_nalout = 0;
	ftbl->frameid_rp_release = 0;
}

static inline int veu_com_frameid_empty(struct veu_frameid_tbl *ftbl)
{
	if ((ftbl->frameid_wp == ftbl->frameid_rp_encoded) &&
		(ftbl->frameid_wp == ftbl->frameid_rp_nalout) &&
		(ftbl->frameid_wp == ftbl->frameid_rp_release))
		return 1;  /* empty */

	return 0;
}

static inline void veu_com_frameid_add(struct veu_frameid_tbl *ftbl,
	uint64_t frameid)
{
	ftbl->frameid_tbl[ftbl->frameid_wp] = frameid;
	ftbl->frameid_wp++;
	if (ftbl->frameid_wp == VEU_FRAMEID_TBL_MAX)
		ftbl->frameid_wp = 0;

	ftbl->frameid_tbl[ftbl->frameid_wp] = -1;

	if (ftbl->frameid_wp == ftbl->frameid_rp_encoded) {
		ftbl->frameid_rp_encoded++;
		if (ftbl->frameid_rp_encoded == VEU_FRAMEID_TBL_MAX)
			ftbl->frameid_rp_encoded = 0;
	}
	if (ftbl->frameid_wp == ftbl->frameid_rp_nalout) {
		ftbl->frameid_rp_nalout++;
		if (ftbl->frameid_rp_nalout == VEU_FRAMEID_TBL_MAX)
			ftbl->frameid_rp_nalout = 0;
	}
	if (ftbl->frameid_wp == ftbl->frameid_rp_release) {
		ftbl->frameid_rp_release++;
		if (ftbl->frameid_rp_release == VEU_FRAMEID_TBL_MAX)
			ftbl->frameid_rp_release = 0;
	}
}

static inline uint64_t veu_com_frameid_encoded(struct veu_frameid_tbl *ftbl)
{
	uint64_t frameid = -1;

	if (ftbl->frameid_rp_encoded == ftbl->frameid_wp)
		return frameid;  /* nothing */

	frameid = ftbl->frameid_tbl[ftbl->frameid_rp_encoded];
	ftbl->frameid_rp_encoded++;
	if (ftbl->frameid_rp_encoded == VEU_FRAMEID_TBL_MAX)
		ftbl->frameid_rp_encoded = 0;

	return frameid;
}

static inline uint64_t veu_com_frameid_nalout(struct veu_frameid_tbl *ftbl)
{
	uint64_t frameid = -1;

	if (ftbl->frameid_rp_nalout == ftbl->frameid_wp)
		return frameid;  /* nothing */

	frameid = ftbl->frameid_tbl[ftbl->frameid_rp_nalout];
	ftbl->frameid_rp_nalout++;
	if (ftbl->frameid_rp_nalout == VEU_FRAMEID_TBL_MAX)
		ftbl->frameid_rp_nalout = 0;

	return frameid;
}

static inline uint64_t veu_com_frameid_release(struct veu_frameid_tbl *ftbl)
{
	uint64_t frameid = -1;

	if (ftbl->frameid_rp_release == ftbl->frameid_wp)
		return frameid;  /* nothing */

	frameid = ftbl->frameid_tbl[ftbl->frameid_rp_release];
	ftbl->frameid_rp_release++;
	if (ftbl->frameid_rp_release == VEU_FRAMEID_TBL_MAX)
		ftbl->frameid_rp_release = 0;

	return frameid;
}

#endif    /* __VEU_DRIVER_COMMON_MODULE_H__ */

