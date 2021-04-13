/*
 * linux/drivers/staging/applite/syscon/applite_syscon.h
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

#if !defined(__APPLITE_SYSCON_H__)
#define __APPLITE_SYSCON_H__

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/*===================================
 include Files
===================================*/
#include <linux/ioctl.h>


/*===================================
 Types and structures   defined
===================================*/

#define SYSCON_MAX_DRAM_SIZE	(0x10000)	/* 64KiB */
#define SYSCON_MAX_CMD_SIZE	(0x60)		/* 96B */


/* structures */
struct syscon_cmd {
	__u8		cmd_req[SYSCON_MAX_CMD_SIZE];
	__u8		cmd_rsp[SYSCON_MAX_CMD_SIZE];
	__u32		req_size;
	__u8		*req_data;
	__u32		rsp_size;
	__u8		*rsp_data;
};


/* ioctl command code */
#define	IOC_SYSCON_L_CMD	_IOWR('s', 1, struct syscon_cmd *)
#define IOC_SYSCON_S_CMD	_IOWR('s', 2, struct syscon_cmd *)



/*===================================
Exported Variables
===================================*/


/*===================================
Exported Functions prototypes
===================================*/

#ifdef __KERNEL__

void applitesyscon_pm_request(int arg);

#endif	/* __KERNEL__ */


#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* __APPLITE_SYSCON_H__ */

