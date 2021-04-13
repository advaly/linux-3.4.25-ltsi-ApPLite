/*
 * arch/arm/mach-tz2000/include/mach/regs/usb2hco_offs_def.h
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

#ifndef USB2HCO_OFFS_DEF_H
#define USB2HCO_OFFS_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

#define USB2HCO_HcRevision_OFFS        0x00000000
#define USB2HCO_HcControl_OFFS         0x00000004
#define USB2HCO_HcCommandStatus_OFFS   0x00000008
#define USB2HCO_HcInterruptStatus_OFFS 0x0000000C
#define USB2HCO_HcInterruptEnable_OFFS 0x00000010
#define USB2HCO_HcInterruptDisable_OFFS 0x00000014
#define USB2HCO_HcHCCA_OFFS            0x00000018
#define USB2HCO_HcPeriodCurrentED_OFFS 0x0000001C
#define USB2HCO_HcControlHeadED_OFFS   0x00000020
#define USB2HCO_HcControlCurrentED_OFFS 0x00000024
#define USB2HCO_HcBulkHeadED_OFFS      0x00000028
#define USB2HCO_HcBulkCurrentED_OFFS   0x0000002C
#define USB2HCO_HcDoneHead_OFFS        0x00000030
#define USB2HCO_HcFmInterval_OFFS      0x00000034
#define USB2HCO_HcFmRemaining_OFFS     0x00000038
#define USB2HCO_HcFmNumber_OFFS        0x0000003C
#define USB2HCO_HcPeriodicStart_OFFS   0x00000040
#define USB2HCO_HcLSThreshold_OFFS     0x00000044
#define USB2HCO_HcRhDescriptorA_OFFS   0x00000048
#define USB2HCO_HcRhDescriptorB_OFFS   0x0000004C
#define USB2HCO_HcRhStatus_OFFS        0x00000050
#define USB2HCO_HcRhPortStatus_0_OFFS  0x00000054

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* USB2HCO_OFFS_DEF_H */
