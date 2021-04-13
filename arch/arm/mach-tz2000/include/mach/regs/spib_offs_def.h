/*
 * arch/arm/mach-tz2000/include/mach/regs/spib_offs_def.h
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

#ifndef SPIB_OFFS_DEF_H
#define SPIB_OFFS_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

#define SPIB_SPIB0_FlshMemMap0_OFFS    0x00000000
#define SPIB_SPIB0_FlshMemMap1_OFFS    0x00000004
#define SPIB_SPIB0_DirAccCtrl0_OFFS    0x00000008
#define SPIB_SPIB0_DirAccCtrl1_OFFS    0x0000000C
#define SPIB_SPIB0_DirRdCtrl0_OFFS     0x00000010
#define SPIB_SPIB0_DirRdCtrl1_OFFS     0x00000014
#define SPIB_SPIB0_PrgAccCtrl0_OFFS    0x00000400
#define SPIB_SPIB0_PrgAccCtrl1_OFFS    0x00000404
#define SPIB_SPIB0_PrgAccIntEn_OFFS    0x00000408
#define SPIB_SPIB0_PrgAccStat_OFFS     0x0000040C

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SPIB_OFFS_DEF_H */
