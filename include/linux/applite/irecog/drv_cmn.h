/*
 * linux/include/linux/applite/drv_cmn.h
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
#ifndef DRV_CMN_H_
#define DRV_CMN_H_

/**************************************************/
/*
 * version definitions
 */
/**************************************************/
#define DRV_STR_(A) #A
#define DRV_STR(A)  DRV_STR_(A)

#define DRV_VERSION_MAJOR      0

#define DRV_VERSION_SIZE       (4 + 1 + 4 + 1 + 4)	/* xxxx.xxxx.xxxx */

struct drv_version {
	char version[DRV_VERSION_SIZE + 1];	/* '\0' */
};
typedef struct drv_version drv_version_t;

#endif /* DRV_CMN_H__ */
