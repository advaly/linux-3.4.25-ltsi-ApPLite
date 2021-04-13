/*
 * arch/arm/mach-tz2000/include/mach/regs/ethermac_offs_def.h
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

#ifndef ETHERMAC_OFFS_DEF_H
#define ETHERMAC_OFFS_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

#define ETHERMAC_EMACDRR_OFFS          0x00000000
#define ETHERMAC_EMACDRTRGR_OFFS       0x00000004
#define ETHERMAC_EMACDRENR_OFFS        0x00000008
#define ETHERMAC_EMACINTR_OFFS         0x00000020
#define ETHERMAC_EMACINTENR_OFFS       0x00000024
#define ETHERMAC_EMACINTDCR_OFFS       0x00000028
#define ETHERMAC_EMACFINFR_OFFS        0x000000F8
#define ETHERMAC_DMACR_OFFS            0x00001000
#define ETHERMAC_DMATXR_OFFS           0x00001008
#define ETHERMAC_DMARXR_OFFS           0x00001010
#define ETHERMAC_DMAINTR_OFFS          0x00001028
#define ETHERMAC_DMAINTENR_OFFS        0x00001030
#define ETHERMAC_ERRMSKR_OFFS          0x00001038
#define ETHERMAC_RXMISCNTR_OFFS        0x00001040
#define ETHERMAC_TXFIFOTHR_OFFS        0x00001048
#define ETHERMAC_FIFOSIZER_OFFS        0x00001050
#define ETHERMAC_DMARXMODR_OFFS        0x00001058
#define ETHERMAC_RXPADR_OFFS           0x00001060
#define ETHERMAC_RXFIFOTHR_OFFS        0x00001068
#define ETHERMAC_TXFIFOSTSR_OFFS       0x00001080
#define ETHERMAC_RXFIFOSTSR_OFFS       0x00001088
#define ETHERMAC_MACCR_OFFS            0x00001100
#define ETHERMAC_LENLMTR_OFFS          0x00001108
#define ETHERMAC_MACINTR_OFFS          0x00001110
#define ETHERMAC_MACINTENR_OFFS        0x00001118
#define ETHERMAC_PHYINTR_OFFS          0x0000112C
#define ETHERMAC_RGIBSR_OFFS           0x00001134
#define ETHERMAC_MACSTSR_OFFS          0x00001138
#define ETHERMAC_PHYIFR_OFFS           0x00001140
#define ETHERMAC_APFTPR_OFFS           0x00001154
#define ETHERMAC_MPFTPR_OFFS           0x00001158
#define ETHERMAC_PFTXCNTR_OFFS         0x0000115C
#define ETHERMAC_PFRXCNTR_OFFS         0x00001160
#define ETHERMAC_PFRTLMTR_OFFS         0x00001164
#define ETHERMAC_PFRTCNTR_OFFS         0x00001168
#define ETHERMAC_MACGCR_OFFS           0x000011B0
#define ETHERMAC_BSTLMTR_OFFS          0x000011B4
#define ETHERMAC_UMACAR_OFFS           0x000011C0
#define ETHERMAC_LMACAR_OFFS           0x000011C8
#define ETHERMAC_TINT1CNTR_OFFS        0x00001300
#define ETHERMAC_TINT2CNTR_OFFS        0x00001308
#define ETHERMAC_TINT3CNTR_OFFS        0x00001310
#define ETHERMAC_RINT1CNTR_OFFS        0x00001340
#define ETHERMAC_RINT2CNTR_OFFS        0x00001348
#define ETHERMAC_RINT3CNTR_OFFS        0x00001350
#define ETHERMAC_RINT4CNTR_OFFS        0x00001358
#define ETHERMAC_RINT5CNTR_OFFS        0x00001360
#define ETHERMAC_RINT6CNTR_OFFS        0x00001368
#define ETHERMAC_RINT7CNTR_OFFS        0x00001370
#define ETHERMAC_RINT8CNTR_OFFS        0x00001378
#define ETHERMAC_MDIOSTSR_OFFS         0x00001380
#define ETHERMAC_MDIOCMDR_OFFS         0x00001384
#define ETHERMAC_MDIOADRR_OFFS         0x00001388
#define ETHERMAC_MDIODATR_OFFS         0x0000138C
#define ETHERMAC_MDIOCYCR_OFFS         0x00001390
#define ETHERMAC_DESCCR_OFFS           0x00001400
#define ETHERMAC_DTXSPAR_OFFS          0x00001410
#define ETHERMAC_DTXCPAR_OFFS          0x00001414
#define ETHERMAC_DTXLPAR_OFFS          0x00001418
#define ETHERMAC_DTXDLR_OFFS           0x0000141C
#define ETHERMAC_DRXSPAR_OFFS          0x00001430
#define ETHERMAC_DRXCPAR_OFFS          0x00001434
#define ETHERMAC_DRXLPAR_OFFS          0x00001438
#define ETHERMAC_DRXDLR_OFFS           0x0000143C
#define ETHERMAC_FMAR00HR_OFFS         0x00001500
#define ETHERMAC_FMAR00LR_OFFS         0x00001504
#define ETHERMAC_FMAR01HR_OFFS         0x00001508
#define ETHERMAC_FMAR01LR_OFFS         0x0000150C
#define ETHERMAC_FMAR02HR_OFFS         0x00001510
#define ETHERMAC_FMAR02LR_OFFS         0x00001514
#define ETHERMAC_FMAR03HR_OFFS         0x00001518
#define ETHERMAC_FMAR03LR_OFFS         0x0000151C
#define ETHERMAC_FMAR04HR_OFFS         0x00001520
#define ETHERMAC_FMAR04LR_OFFS         0x00001524
#define ETHERMAC_FMAR05HR_OFFS         0x00001528
#define ETHERMAC_FMAR05LR_OFFS         0x0000152C
#define ETHERMAC_FMAR06HR_OFFS         0x00001530
#define ETHERMAC_FMAR06LR_OFFS         0x00001534
#define ETHERMAC_FMAR07HR_OFFS         0x00001538
#define ETHERMAC_FMAR07LR_OFFS         0x0000153C
#define ETHERMAC_FLTCR_OFFS            0x000015E0
#define ETHERMAC_FLTENTR_OFFS          0x000015E4
#define ETHERMAC_FLTFWCNTR_OFFS        0x000015F0
#define ETHERMAC_FLTDRCNTR_OFFS        0x000015F4

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ETHERMAC_OFFS_DEF_H */
