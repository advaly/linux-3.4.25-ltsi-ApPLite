/*
 * arch/arm/mach-tz2000/include/mach/regs/yuvc_offs_def.h
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

#ifndef YUVC_OFFS_DEF_H
#define YUVC_OFFS_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

#define YUVC_YUVC_START_OFFS           0x00000000
#define YUVC_YUVC_RESET_OFFS           0x00000004
#define YUVC_YUVC_MODE_OFFS            0x00000008
#define YUVC_YUVC_SIZE_OFFS            0x0000000C
#define YUVC_YUVC_OFFSET_Y_OFFS        0x00000010
#define YUVC_YUVC_OFFSET_UV_OFFS       0x00000014
#define YUVC_YUVC_YCOEF_RG_OFFS        0x00000018
#define YUVC_YUVC_YCOEF_B_OFFS         0x0000001C
#define YUVC_YUVC_UCOEF_RG_OFFS        0x00000020
#define YUVC_YUVC_UCOEF_B_OFFS         0x00000024
#define YUVC_YUVC_VCOEF_RG_OFFS        0x00000028
#define YUVC_YUVC_VCOEF_B_OFFS         0x0000002C
#define YUVC_YUVC_OFFSET_RG_OFFS       0x00000030
#define YUVC_YUVC_OFFSET_B_OFFS        0x00000034
#define YUVC_YUVC_STADR_OFFS           0x00000100
#define YUVC_YUVC_ENDADR_OFFS          0x00000104
#define YUVC_YUVC_DMRADR_OFFS          0x00000118
#define YUVC_YUVC_CFG_OFFS             0x0000011C
#define YUVC_YUVC_INT_MASK_OFFS        0x00000120
#define YUVC_YUVC_W_ENABLE_OFFS        0x00000134
#define YUVC_YUVC_W00_STADR_OFFS       0x00000300
#define YUVC_YUVC_W00_ENDADR_OFFS      0x00000304
#define YUVC_YUVC_W00_HEIGHT_OFFS      0x00000308
#define YUVC_YUVC_W00_PITCH_OFFS       0x0000030C
#define YUVC_YUVC_W00_CFG0_OFFS        0x00000310
#define YUVC_YUVC_W00_SRAM_BASE_OFFS   0x00000318
#define YUVC_YUVC_W00_SRAM_SIZE_OFFS   0x0000031C
#define YUVC_YUVC_W00_INTL_OFFS        0x00000320
#define YUVC_YUVC_W01_STADR_OFFS       0x00000340
#define YUVC_YUVC_W01_ENDADR_OFFS      0x00000344
#define YUVC_YUVC_W01_HEIGHT_OFFS      0x00000348
#define YUVC_YUVC_W01_PITCH_OFFS       0x0000034C
#define YUVC_YUVC_W01_CFG0_OFFS        0x00000350
#define YUVC_YUVC_W01_CFG1_OFFS        0x00000354
#define YUVC_YUVC_W01_SRAM_BASE_OFFS   0x00000358
#define YUVC_YUVC_W01_SRAM_SIZE_OFFS   0x0000035C
#define YUVC_YUVC_W01_INTL_OFFS        0x00000360
#define YUVC_YUVC_MODE_BUF_OFFS        0x00000800
#define YUVC_YUVC_SIZE_BUF_OFFS        0x00000804
#define YUVC_YUVC_OFFSET_Y_BUF_OFFS    0x00000808
#define YUVC_YUVC_OFFSET_UV_BUF_OFFS   0x0000080C
#define YUVC_YUVC_YCOEF_RG_BUF_OFFS    0x00000810
#define YUVC_YUVC_YCOEF_B_BUF_OFFS     0x00000814
#define YUVC_YUVC_UCOEF_RG_BUF_OFFS    0x00000818
#define YUVC_YUVC_UCOEF_B_BUF_OFFS     0x0000081C
#define YUVC_YUVC_VCOEF_RG_BUF_OFFS    0x00000820
#define YUVC_YUVC_VCOEF_B_BUF_OFFS     0x00000824
#define YUVC_YUVC_OFFSET_RG_BUF_OFFS   0x00000828
#define YUVC_YUVC_OFFSET_B_BUF_OFFS    0x0000082C
#define YUVC_YUVC_W_ENABLE_BUF_OFFS    0x00000904
#define YUVC_YUVC_W00_STADR_BUF_OFFS   0x00000C00
#define YUVC_YUVC_W00_ENDADR_BUF_OFFS  0x00000C04
#define YUVC_YUVC_W00_HEIGHT_BUF_OFFS  0x00000C08
#define YUVC_YUVC_W00_PITCH_BUF_OFFS   0x00000C0C
#define YUVC_YUVC_W00_CFG0_BUF_OFFS    0x00000C10
#define YUVC_YUVC_W01_STADR_BUF_OFFS   0x00000C20
#define YUVC_YUVC_W01_ENDADR_BUF_OFFS  0x00000C24
#define YUVC_YUVC_W01_HEIGHT_BUF_OFFS  0x00000C28
#define YUVC_YUVC_W01_PITCH_BUF_OFFS   0x00000C2C
#define YUVC_YUVC_W01_CFG0_BUF_OFFS    0x00000C30
#define YUVC_YUVC_STATUS_OFFS          0x00000E00
#define YUVC_YUVC_INT_OFFS             0x00000E04
#define YUVC_YUVC_W_SRAM_OFFS          0x00000E0C
#define YUVC_YUVC_W_STOP_OFFS          0x00000E14
#define YUVC_YUVC_W_RUN_OFFS           0x00000E1C

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* YUVC_OFFS_DEF_H */
