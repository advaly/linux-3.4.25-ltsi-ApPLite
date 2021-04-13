/*
 * arch/arm/mach-tz2000/include/mach/regs/usb2hce_offs_def.h
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

#ifndef USB2HCE_OFFS_DEF_H
#define USB2HCE_OFFS_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

#define USB2HCE_HCCAPBASE_OFFS         0x00000000
#define USB2HCE_HCSPARAMS_OFFS         0x00000004
#define USB2HCE_HCCPARAMS_OFFS         0x00000008
#define USB2HCE_USBCMD_OFFS            0x00000010
#define USB2HCE_USBSTS_OFFS            0x00000014
#define USB2HCE_USBINTR_OFFS           0x00000018
#define USB2HCE_FRINDEX_OFFS           0x0000001C
#define USB2HCE_CTRLDSSEGMENT_OFFS     0x00000020
#define USB2HCE_PERIODICLISTBASE_OFFS  0x00000024
#define USB2HCE_ASYNCLISTADDR_OFFS     0x00000028
#define USB2HCE_CONFIGFLAG_OFFS        0x00000050
#define USB2HCE_PORTSC_0_OFFS          0x00000054

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* USB2HCE_OFFS_DEF_H */
