/*
 * linux/drivers/staging/applite/irecog/gdmac_pyramid/pyramid.h
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
#ifndef __PYRAMID_H__
#define __PYRAMID_H__

#include <linux/applite/irecog/gdmac_pyramid_ioctl.h>

#include "pyramid_public.h"
#include "gdmac_instructions.h"

int pyramid_initialize(void);
void pyramid_create_instructions(gdmac_inst *inst, gdmac_pyramid *pyramid);
void pyramid_finalize(void);
int pyramid_parameter_check(gdmac_pyramid *pyramid);
void pyramid_cache_flush(gdmac_pyramid *pyramid);
void pyramid_cache_invalidate(gdmac_pyramid *pyramid);

#endif /* __PYRAMID_H__ */
