/*
 * arch/arm/mach-tz2000/include/mach/regs/wconf_offs_def.h
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

#ifndef WCONF_OFFS_DEF_H
#define WCONF_OFFS_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

#define WCONF_EMMC4SD_CFG_CAPABILITY0_OFFS 0x00000000
#define WCONF_EMMC4SD_CFG_CAPABILITY1_OFFS 0x00000008
#define WCONF_EMMC4SD_CFG_MAXCURNT_OFFS 0x00000010
#define WCONF_EMMC4SD_CFG_PRESET0_OFFS 0x00000020
#define WCONF_EMMC4SD_CFG_PRESET1_OFFS 0x00000028
#define WCONF_EMMC4SD_CFG_PRESET2_OFFS 0x00000030
#define WCONF_EMMC4SD_CFG_PRESET3_OFFS 0x00000038
#define WCONF_EMMC4SD_CFG_WKUP_OFFS    0x00000040
#define WCONF_EMMC4SD_CTRL_DLYCHG_OFFS 0x00000050
#define WCONF_EMMC4SD_CTRL_INDLY_OFFS  0x00000058
#define WCONF_EMMC4SD_CTRL_OUTDLY_OFFS 0x00000060
#define WCONF_EMMC4SD_CTRL_DLL0_OFFS   0x00000068
#define WCONF_EMMC4SD_CTRL_DLL1_OFFS   0x00000070
#define WCONF_EMMC8SD_CFG_CAPABILITY0_OFFS 0x00000100
#define WCONF_EMMC8SD_CFG_CAPABILITY1_OFFS 0x00000108
#define WCONF_EMMC8SD_CFG_MAXCURNT_OFFS 0x00000110
#define WCONF_EMMC8SD_CFG_PRESET0_OFFS 0x00000120
#define WCONF_EMMC8SD_CFG_PRESET1_OFFS 0x00000128
#define WCONF_EMMC8SD_CFG_PRESET2_OFFS 0x00000130
#define WCONF_EMMC8SD_CFG_PRESET3_OFFS 0x00000138
#define WCONF_EMMC8SD_CFG_WKUP_OFFS    0x00000140
#define WCONF_EMMC8SD_CTRL_DLYCHG_OFFS 0x00000150
#define WCONF_EMMC8SD_CTRL_INDLY_OFFS  0x00000158
#define WCONF_EMMC8SD_CTRL_OUTDLY_OFFS 0x00000160
#define WCONF_EMMC8SD_CTRL_DLL0_OFFS   0x00000168
#define WCONF_EMMC8SD_CTRL_DLL1_OFFS   0x00000170
#define WCONF_IO_DRVSTR_CTL_OFFS       0x00000200
#define WCONF_USB2HD_FLADJ_OFFS        0x00000500
#define WCONF_USB2PHY_CONFIG0_OFFS     0x00000600
#define WCONF_USB2PHY_CONFIG1_OFFS     0x00000610
#define WCONF_USB2HD_MUX_CTL_OFFS      0x00000700
#define WCONF_USB2HD_REFCLK_OFFS       0x00000704
#define WCONF_USB2HD_STATUS_OFFS       0x00000708

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* WCONF_OFFS_DEF_H */
