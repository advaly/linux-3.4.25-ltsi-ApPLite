/*
 * arch/arm/mach-tz2000/include/mach/regs/telomere_offs_def.h
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

#ifndef TELOMERE_OFFS_DEF_H
#define TELOMERE_OFFS_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

#define TELOMERE_NCM_MODE_OFFS         0x00000000
#define TELOMERE_NCM_STAT_OFFS         0x00000014
#define TELOMERE_NANDC_SETTING_OFFS    0x00000024
#define TELOMERE_NANDC_STAT_OFFS       0x00000028
#define TELOMERE_INTM_STAT_OFFS        0x00000080
#define TELOMERE_INTM_MSKEDSTAT_OFFS   0x00000084
#define TELOMERE_INTM_CLR_OFFS         0x00000088
#define TELOMERE_INTM_MASK_OFFS        0x0000008C
#define TELOMERE_CCTRL_MFADDR_OFFS     0x000000E0
#define TELOMERE_CCTRL_MFSIZE_OFFS     0x000000E4
#define TELOMERE_GPR_0_OFFS            0x00000100
#define TELOMERE_GPR_1_OFFS            0x00000104
#define TELOMERE_GPR_2_OFFS            0x00000108
#define TELOMERE_GPR_3_OFFS            0x0000010C
#define TELOMERE_BINSEMA_0_OFFS        0x00000180
#define TELOMERE_BINSEMA_1_OFFS        0x00000184
#define TELOMERE_BINSEMA_2_OFFS        0x00000188
#define TELOMERE_BINSEMA_3_OFFS        0x0000018C
#define TELOMERE_MAILBOX_M2N_OFFS      0x000001C0
#define TELOMERE_MAILBOX_M2NC_OFFS     0x000001C4
#define TELOMERE_MAILBOX_N2M_OFFS      0x000001C8
#define TELOMERE_MAILBOX_N2MC_OFFS     0x000001CC
#define TELOMERE_BINSEMA_REF_0_OFFS    0x00000200
#define TELOMERE_BINSEMA_REF_1_OFFS    0x00000204
#define TELOMERE_BINSEMA_REF_2_OFFS    0x00000208
#define TELOMERE_BINSEMA_REF_3_OFFS    0x0000020C
#define TELOMERE_INTN_STAT_OFFS        0x00001000
#define TELOMERE_INTN_MSKEDSTAT_OFFS   0x00001004
#define TELOMERE_INTN_MASK_OFFS        0x0000100C

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TELOMERE_OFFS_DEF_H */
