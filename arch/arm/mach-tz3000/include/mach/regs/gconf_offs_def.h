/*
 * arch/arm/mach-tz3000/include/mach/regs/gconf_offs_def.h
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

#ifndef GCONF_OFFS_DEF_H
#define GCONF_OFFS_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

#define GCONF_I2SSEL_OFFS              0x00000000
#define GCONF_PINSHARE0_OFFS           0x00000010
#define GCONF_PINSHARE1_OFFS           0x00000014
#define GCONF_PINSHARE2_OFFS           0x00000020
#define GCONF_PINSHARE3_OFFS           0x00000028
#define GCONF_CPU_EVENT_OFFS           0x00000038
#define GCONF_CPU_STANDBY_STATUS_OFFS  0x0000003C
#define GCONF_GDMAC_CTRL0_OFFS         0x00000040
#define GCONF_GDMAC_CTRL1_OFFS         0x00000044
#define GCONF_GDMAC_CTRL2_OFFS         0x00000048
#define GCONF_GDMAC_CTRL3_OFFS         0x0000004C
#define GCONF_GDMAC_CTRL4_OFFS         0x00000050
#define GCONF_GDMAC_CTRL5_OFFS         0x00000054

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GCONF_OFFS_DEF_H */
