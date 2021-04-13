/*
 * arch/arm/mach-tz3000/include/mach/regs/si2c0_offs_def.h
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

#ifndef SI2C0_OFFS_DEF_H
#define SI2C0_OFFS_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

#define SI2C0_SIC0_IC_CON_OFFS         0x00000000
#define SI2C0_SIC0_IC_TAR_OFFS         0x00000004
#define SI2C0_SIC0_IC_SAR_OFFS         0x00000008
#define SI2C0_SIC0_IC_DATA_CMD_OFFS    0x00000010
#define SI2C0_SIC0_IC_SS_SCL_HCNT_OFFS 0x00000014
#define SI2C0_SIC0_IC_SS_SCL_LCNT_OFFS 0x00000018
#define SI2C0_SIC0_IC_FS_SCL_HCNT_OFFS 0x0000001C
#define SI2C0_SIC0_IC_FS_SCL_LCNT_OFFS 0x00000020
#define SI2C0_SIC0_IC_INTR_STAT_OFFS   0x0000002C
#define SI2C0_SIC0_IC_INTR_MASK_OFFS   0x00000030
#define SI2C0_SIC0_IC_RAW_INTR_STAT_OFFS 0x00000034
#define SI2C0_SIC0_IC_RX_TL_OFFS       0x00000038
#define SI2C0_SIC0_IC_TX_TL_OFFS       0x0000003C
#define SI2C0_SIC0_IC_CLR_INTR_OFFS    0x00000040
#define SI2C0_SIC0_IC_CLR_RX_UNDER_OFFS 0x00000044
#define SI2C0_SIC0_IC_CLR_RX_OVER_OFFS 0x00000048
#define SI2C0_SIC0_IC_CLR_TX_OVER_OFFS 0x0000004C
#define SI2C0_SIC0_IC_CLR_RD_REQ_OFFS  0x00000050
#define SI2C0_SIC0_IC_CLR_TX_ABRT_OFFS 0x00000054
#define SI2C0_SIC0_IC_CLR_RX_DONE_OFFS 0x00000058
#define SI2C0_SIC0_IC_CLR_ACTIVITY_OFFS 0x0000005C
#define SI2C0_SIC0_IC_CLR_STOP_DET_OFFS 0x00000060
#define SI2C0_SIC0_IC_CLR_START_DET_OFFS 0x00000064
#define SI2C0_SIC0_IC_CLR_GEN_CALL_OFFS 0x00000068
#define SI2C0_SIC0_IC_ENABLE_OFFS      0x0000006C
#define SI2C0_SIC0_IC_STATUS_OFFS      0x00000070
#define SI2C0_SIC0_IC_TXFLR_OFFS       0x00000074
#define SI2C0_SIC0_IC_RXFLR_OFFS       0x00000078
#define SI2C0_SIC0_IC_SDA_HOLD_OFFS    0x0000007C
#define SI2C0_SIC0_IC_TX_ABRT_SOURCE_OFFS 0x00000080
#define SI2C0_SIC0_IC_SLV_DATA_NACK_ONLY_OFFS 0x00000084
#define SI2C0_SIC0_IC_SDA_SETUP_OFFS   0x00000094
#define SI2C0_SIC0_IC_ACK_GENERAL_CALL_OFFS 0x00000098
#define SI2C0_SIC0_IC_ENABLE_STATUS_OFFS 0x0000009C
#define SI2C0_SIC0_IC_FS_SPKLEN_OFFS   0x000000A0
#define SI2C0_SIC0_IC_COMP_PARAM_1_OFFS 0x000000F4
#define SI2C0_SIC0_IC_COMP_VERSION_OFFS 0x000000F8
#define SI2C0_SIC0_IC_COMP_TYPE_OFFS   0x000000FC

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SI2C0_OFFS_DEF_H */
