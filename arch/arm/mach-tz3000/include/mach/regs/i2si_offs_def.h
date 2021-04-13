/*
 * arch/arm/mach-tz3000/include/mach/regs/i2si_offs_def.h
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

#ifndef I2SI_OFFS_DEF_H
#define I2SI_OFFS_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

#define I2SI_I2SI0_START_OFFS          0x00000004
#define I2SI_I2SI0_BUSY_OFFS           0x00000008
#define I2SI_I2SI0_AUDIOSET_OFFS       0x00000010
#define I2SI_I2S0_INTSTAT_OFFS         0x00000014
#define I2SI_I2SI0_INTMASK_OFFS        0x00000018
#define I2SI_I2SI0_INTCLR_OFFS         0x0000001C
#define I2SI_I2SI0_INTSET_OFFS         0x00000020
#define I2SI_I2SI0_MUTE_OFFS           0x00000024
#define I2SI_I2SI0_EPTR_OFFS           0x00000028
#define I2SI_I2SI0_MODESET_OFFS        0x000000F8
#define I2SI_I2SI0_LMEM_OFFS           0x00000100
#define I2SI_I2SI1_START_OFFS          0x00001004
#define I2SI_I2SI1_BUSY_OFFS           0x00001008
#define I2SI_I2SI1_AUDIOSET_OFFS       0x00001010
#define I2SI_I2SI1_INTSTAT_OFFS        0x00001014
#define I2SI_I2SI1_INTMASK_OFFS        0x00001018
#define I2SI_I2SI1_INTCLR_OFFS         0x0000101C
#define I2SI_I2SI1_INTSET_OFFS         0x00001020
#define I2SI_I2SI1_MUTE_OFFS           0x00001024
#define I2SI_I2SI1_EPTR_OFFS           0x00001028
#define I2SI_I2SI1_MODESET_OFFS        0x000010F8
#define I2SI_I2SI1_LMEM_OFFS           0x00001100

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* I2SI_OFFS_DEF_H */
