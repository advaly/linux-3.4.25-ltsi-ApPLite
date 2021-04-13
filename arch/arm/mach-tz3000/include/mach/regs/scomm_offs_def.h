/*
 * arch/arm/mach-tz3000/include/mach/regs/scomm_offs_def.h
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

#ifndef SCOMM_OFFS_DEF_H
#define SCOMM_OFFS_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

#define SCOMM_TAS_NONSEC_OFFS          0x00000000
#define SCOMM_INT_NONSEC_OFFS          0x00000004
#define SCOMM_TAS_SECURE_OFFS          0x00000010
#define SCOMM_INT_SECURE_OFFS          0x00000014

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SCOMM_OFFS_DEF_H */
