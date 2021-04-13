/*
 * arch/arm/mach-tz3000/include/mach/regs/ether_offs_def.h
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

#ifndef ETHER_OFFS_DEF_H
#define ETHER_OFFS_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

#define ETHER_EMACDRR_OFFS             0x00000000
#define ETHER_EMACDRTRGR_OFFS          0x00000004
#define ETHER_EMACDRENR_OFFS           0x00000008
#define ETHER_EMACINTR_OFFS            0x00000020
#define ETHER_EMACINTENR_OFFS          0x00000024
#define ETHER_EMACINTDCR_OFFS          0x00000028
#define ETHER_EMACFINFR_OFFS           0x000000F8
#define ETHER_DMACR_OFFS               0x00001000
#define ETHER_DMATXR_OFFS              0x00001008
#define ETHER_DMARXR_OFFS              0x00001010
#define ETHER_DMAINTR_OFFS             0x00001028
#define ETHER_DMAINTENR_OFFS           0x00001030
#define ETHER_ERRMSKR_OFFS             0x00001038
#define ETHER_RXMISCNTR_OFFS           0x00001040
#define ETHER_TXFIFOTHR_OFFS           0x00001048
#define ETHER_FIFOSIZER_OFFS           0x00001050
#define ETHER_DMARXMODR_OFFS           0x00001058
#define ETHER_RXPADR_OFFS              0x00001060
#define ETHER_RXFIFOTHR_OFFS           0x00001068
#define ETHER_TXFIFOSTSR_OFFS          0x00001080
#define ETHER_RXFIFOSTSR_OFFS          0x00001088
#define ETHER_MACCR_OFFS               0x00001100
#define ETHER_LENLMTR_OFFS             0x00001108
#define ETHER_MACINTR_OFFS             0x00001110
#define ETHER_MACINTENR_OFFS           0x00001118
#define ETHER_PHYINTR_OFFS             0x0000112C
#define ETHER_RGIBSR_OFFS              0x00001134
#define ETHER_MACSTSR_OFFS             0x00001138
#define ETHER_PHYIFR_OFFS              0x00001140
#define ETHER_APFTPR_OFFS              0x00001154
#define ETHER_MPFTPR_OFFS              0x00001158
#define ETHER_PFTXCNTR_OFFS            0x0000115C
#define ETHER_PFRXCNTR_OFFS            0x00001160
#define ETHER_PFRTLMTR_OFFS            0x00001164
#define ETHER_PFRTCNTR_OFFS            0x00001168
#define ETHER_MACGCR_OFFS              0x000011B0
#define ETHER_BSTLMTR_OFFS             0x000011B4
#define ETHER_UMACAR_OFFS              0x000011C0
#define ETHER_LMACAR_OFFS              0x000011C8
#define ETHER_TINT1CNTR_OFFS           0x00001300
#define ETHER_TINT2CNTR_OFFS           0x00001308
#define ETHER_TINT3CNTR_OFFS           0x00001310
#define ETHER_RINT1CNTR_OFFS           0x00001340
#define ETHER_RINT2CNTR_OFFS           0x00001348
#define ETHER_RINT3CNTR_OFFS           0x00001350
#define ETHER_RINT4CNTR_OFFS           0x00001358
#define ETHER_RINT5CNTR_OFFS           0x00001360
#define ETHER_RINT6CNTR_OFFS           0x00001368
#define ETHER_RINT7CNTR_OFFS           0x00001370
#define ETHER_RINT8CNTR_OFFS           0x00001378
#define ETHER_MDIOSTSR_OFFS            0x00001380
#define ETHER_MDIOCMDR_OFFS            0x00001384
#define ETHER_MDIOADRR_OFFS            0x00001388
#define ETHER_MDIODATR_OFFS            0x0000138C
#define ETHER_MDIOCYCR_OFFS            0x00001390
#define ETHER_DESCCR_OFFS              0x00001400
#define ETHER_DTXSPAR_OFFS             0x00001410
#define ETHER_DTXCPAR_OFFS             0x00001414
#define ETHER_DTXLPAR_OFFS             0x00001418
#define ETHER_DTXDLR_OFFS              0x0000141C
#define ETHER_DRXSPAR_OFFS             0x00001430
#define ETHER_DRXCPAR_OFFS             0x00001434
#define ETHER_DRXLPAR_OFFS             0x00001438
#define ETHER_DRXDLR_OFFS              0x0000143C
#define ETHER_FMAR00HR_OFFS            0x00001500
#define ETHER_FMAR00LR_OFFS            0x00001504
#define ETHER_FMAR01HR_OFFS            0x00001508
#define ETHER_FMAR01LR_OFFS            0x0000150C
#define ETHER_FMAR02HR_OFFS            0x00001510
#define ETHER_FMAR02LR_OFFS            0x00001514
#define ETHER_FMAR03HR_OFFS            0x00001518
#define ETHER_FMAR03LR_OFFS            0x0000151C
#define ETHER_FMAR04HR_OFFS            0x00001520
#define ETHER_FMAR04LR_OFFS            0x00001524
#define ETHER_FMAR05HR_OFFS            0x00001528
#define ETHER_FMAR05LR_OFFS            0x0000152C
#define ETHER_FMAR06HR_OFFS            0x00001530
#define ETHER_FMAR06LR_OFFS            0x00001534
#define ETHER_FMAR07HR_OFFS            0x00001538
#define ETHER_FMAR07LR_OFFS            0x0000153C
#define ETHER_FLTCR_OFFS               0x000015E0
#define ETHER_FLTENTR_OFFS             0x000015E4
#define ETHER_FLTFWCNTR_OFFS           0x000015F0
#define ETHER_FLTDRCNTR_OFFS           0x000015F4

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ETHER_OFFS_DEF_H */
