/*
 * drivers/staging/applite/vdu/vd_accessor.h
 *
 * (C) Copyright TOSHIBA Corporation
 * Semiconductor & Storage Products Company 2013
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
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef __VD_ACCESSOR_H__
#define __VD_ACCESSOR_H__

#include "vd_api.h"

enum vd_result vd_acs_init(const struct vd_accessor *acs);
void vd_acs_lock(void);
void vd_acs_unlock(void);
void vd_acs_set(uint32_t offset, uint32_t value);
uint32_t vd_acs_get(uint32_t offset);
void vd_acs_interrupt(uint32_t offset, uint32_t bit);
/*void vd_acs_tas_get(void);*/
/*void vd_acs_tas_release(void);*/

#endif
