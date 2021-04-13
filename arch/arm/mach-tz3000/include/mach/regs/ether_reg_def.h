/*
 * arch/arm/mach-tz3000/include/mach/regs/ether_reg_def.h
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

#ifndef _ETHER_REG_DEF_H
#define _ETHER_REG_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

// EMACDRR Register
#define ETHER_EMACDRR_OFS                        0x00000000
// DRDADR bitfiled (RW) Reset=1100000000000000000000000000
#define ETHER_EMACDRR_DRDADR_MASK                0xFFFFFFFF
#define ETHER_EMACDRR_DRDADR_SHIFT               0 
#define ETHER_EMACDRR_DRDADR_BIT                 0xFFFFFFFF
#define ETHER_EMACDRR_DRDADR_BITWIDTH            32
// EMACDRTRGR Register
#define ETHER_EMACDRTRGR_OFS                     0x00000004
// Reserved3 bitfiled (RO) Reset=0
#define ETHER_EMACDRTRGR_RESERVED3_MASK          0x3
#define ETHER_EMACDRTRGR_RESERVED3_SHIFT         0 
#define ETHER_EMACDRTRGR_RESERVED3_BIT           0x3
#define ETHER_EMACDRTRGR_RESERVED3_BITWIDTH      2
// DRDMSK bitfiled (RW) Reset=0
#define ETHER_EMACDRTRGR_DRDMSK_MASK             0x1FFC
#define ETHER_EMACDRTRGR_DRDMSK_SHIFT            2 
#define ETHER_EMACDRTRGR_DRDMSK_BIT              0x7FF
#define ETHER_EMACDRTRGR_DRDMSK_BITWIDTH         11
// Reserved2 bitfiled (RO) Reset=0
#define ETHER_EMACDRTRGR_RESERVED2_MASK          0x3E000
#define ETHER_EMACDRTRGR_RESERVED2_SHIFT         13 
#define ETHER_EMACDRTRGR_RESERVED2_BIT           0x1F
#define ETHER_EMACDRTRGR_RESERVED2_BITWIDTH      5
// DRDTRG bitfiled (RW) Reset=0
#define ETHER_EMACDRTRGR_DRDTRG_MASK             0x1FFC0000
#define ETHER_EMACDRTRGR_DRDTRG_SHIFT            18 
#define ETHER_EMACDRTRGR_DRDTRG_BIT              0x7FF
#define ETHER_EMACDRTRGR_DRDTRG_BITWIDTH         11
// Reserved bitfiled (RO) Reset=0
#define ETHER_EMACDRTRGR_RESERVED_MASK           0xE0000000
#define ETHER_EMACDRTRGR_RESERVED_SHIFT          29 
#define ETHER_EMACDRTRGR_RESERVED_BIT            0x7
#define ETHER_EMACDRTRGR_RESERVED_BITWIDTH       3
// EMACDRENR Register
#define ETHER_EMACDRENR_OFS                      0x00000008
// DRDEN bitfiled (RW) Reset=0
#define ETHER_EMACDRENR_DRDEN_MASK               0x1
#define ETHER_EMACDRENR_DRDEN_SHIFT              0 
#define ETHER_EMACDRENR_DRDEN_BIT                0x1
#define ETHER_EMACDRENR_DRDEN_BITWIDTH           1
// Reserved bitfiled (RO) Reset=0
#define ETHER_EMACDRENR_RESERVED_MASK            0xFFFFFFFE
#define ETHER_EMACDRENR_RESERVED_SHIFT           1 
#define ETHER_EMACDRENR_RESERVED_BIT             0x7FFFFFFF
#define ETHER_EMACDRENR_RESERVED_BITWIDTH        31
// EMACINTR Register
#define ETHER_EMACINTR_OFS                       0x00000020
// DMAINT bitfiled (RO) Reset=0
#define ETHER_EMACINTR_DMAINT_MASK               0x1
#define ETHER_EMACINTR_DMAINT_SHIFT              0 
#define ETHER_EMACINTR_DMAINT_BIT                0x1
#define ETHER_EMACINTR_DMAINT_BITWIDTH           1
// SERR bitfiled (RW) Reset=0
#define ETHER_EMACINTR_SERR_MASK                 0x2
#define ETHER_EMACINTR_SERR_SHIFT                1 
#define ETHER_EMACINTR_SERR_BIT                  0x1
#define ETHER_EMACINTR_SERR_BITWIDTH             1
// Reserved bitfiled (RO) Reset=0
#define ETHER_EMACINTR_RESERVED_MASK             0xFFFFFFFC
#define ETHER_EMACINTR_RESERVED_SHIFT            2 
#define ETHER_EMACINTR_RESERVED_BIT              0x3FFFFFFF
#define ETHER_EMACINTR_RESERVED_BITWIDTH         30
// EMACINTENR Register
#define ETHER_EMACINTENR_OFS                     0x00000024
// DMAINT bitfiled (RW) Reset=0
#define ETHER_EMACINTENR_DMAINT_MASK             0x1
#define ETHER_EMACINTENR_DMAINT_SHIFT            0 
#define ETHER_EMACINTENR_DMAINT_BIT              0x1
#define ETHER_EMACINTENR_DMAINT_BITWIDTH         1
// SERR bitfiled (RW) Reset=0
#define ETHER_EMACINTENR_SERR_MASK               0x2
#define ETHER_EMACINTENR_SERR_SHIFT              1 
#define ETHER_EMACINTENR_SERR_BIT                0x1
#define ETHER_EMACINTENR_SERR_BITWIDTH           1
// Reserved bitfiled (RO) Reset=0
#define ETHER_EMACINTENR_RESERVED_MASK           0xFFFFFFFC
#define ETHER_EMACINTENR_RESERVED_SHIFT          2 
#define ETHER_EMACINTENR_RESERVED_BIT            0x3FFFFFFF
#define ETHER_EMACINTENR_RESERVED_BITWIDTH       30
// EMACINTDCR Register
#define ETHER_EMACINTDCR_OFS                     0x00000028
// IDLYEN bitfiled (RW) Reset=0
#define ETHER_EMACINTDCR_IDLYEN_MASK             0x1
#define ETHER_EMACINTDCR_IDLYEN_SHIFT            0 
#define ETHER_EMACINTDCR_IDLYEN_BIT              0x1
#define ETHER_EMACINTDCR_IDLYEN_BITWIDTH         1
// Reserved2 bitfiled (RO) Reset=0
#define ETHER_EMACINTDCR_RESERVED2_MASK          0xE
#define ETHER_EMACINTDCR_RESERVED2_SHIFT         1 
#define ETHER_EMACINTDCR_RESERVED2_BIT           0x7
#define ETHER_EMACINTDCR_RESERVED2_BITWIDTH      3
// IDLY bitfiled (RW) Reset=0
#define ETHER_EMACINTDCR_IDLY_MASK               0x1FFFFF0
#define ETHER_EMACINTDCR_IDLY_SHIFT              4 
#define ETHER_EMACINTDCR_IDLY_BIT                0x1FFFFF
#define ETHER_EMACINTDCR_IDLY_BITWIDTH           21
// Reserved bitfiled (RO) Reset=0
#define ETHER_EMACINTDCR_RESERVED_MASK           0xFE000000
#define ETHER_EMACINTDCR_RESERVED_SHIFT          25 
#define ETHER_EMACINTDCR_RESERVED_BIT            0x7F
#define ETHER_EMACINTDCR_RESERVED_BITWIDTH       7
// EMACFINFR Register
#define ETHER_EMACFINFR_OFS                      0x000000F8
// PHYIF bitfiled (RO) Reset=10
#define ETHER_EMACFINFR_PHYIF_MASK               0x7
#define ETHER_EMACFINFR_PHYIF_SHIFT              0 
#define ETHER_EMACFINFR_PHYIF_BIT                0x7
#define ETHER_EMACFINFR_PHYIF_BITWIDTH           3
// PHYIFWAR bitfiled (RO) Reset=1
#define ETHER_EMACFINFR_PHYIFWAR_MASK            0x8
#define ETHER_EMACFINFR_PHYIFWAR_SHIFT           3 
#define ETHER_EMACFINFR_PHYIFWAR_BIT             0x1
#define ETHER_EMACFINFR_PHYIFWAR_BITWIDTH        1
// MACFLT bitfiled (RO) Reset=1
#define ETHER_EMACFINFR_MACFLT_MASK              0x30
#define ETHER_EMACFINFR_MACFLT_SHIFT             4 
#define ETHER_EMACFINFR_MACFLT_BIT               0x3
#define ETHER_EMACFINFR_MACFLT_BITWIDTH          2
// Reserved5 bitfiled (RO) Reset=0
#define ETHER_EMACFINFR_RESERVED5_MASK           0xFC0
#define ETHER_EMACFINFR_RESERVED5_SHIFT          6 
#define ETHER_EMACFINFR_RESERVED5_BIT            0x3F
#define ETHER_EMACFINFR_RESERVED5_BITWIDTH       6
// PHYINT_N bitfiled (RO) Reset=1
#define ETHER_EMACFINFR_PHYINT_N_MASK            0x1000
#define ETHER_EMACFINFR_PHYINT_N_SHIFT           12 
#define ETHER_EMACFINFR_PHYINT_N_BIT             0x1
#define ETHER_EMACFINFR_PHYINT_N_BITWIDTH        1
// Reserved4 bitfiled (RO) Reset=0
#define ETHER_EMACFINFR_RESERVED4_MASK           0xE000
#define ETHER_EMACFINFR_RESERVED4_SHIFT          13 
#define ETHER_EMACFINFR_RESERVED4_BIT            0x7
#define ETHER_EMACFINFR_RESERVED4_BITWIDTH       3
// RFSZ bitfiled (RO) Reset=1
#define ETHER_EMACFINFR_RFSZ_MASK                0x30000
#define ETHER_EMACFINFR_RFSZ_SHIFT               16 
#define ETHER_EMACFINFR_RFSZ_BIT                 0x3
#define ETHER_EMACFINFR_RFSZ_BITWIDTH            2
// Reserved3 bitfiled (RO) Reset=0
#define ETHER_EMACFINFR_RESERVED3_MASK           0xC0000
#define ETHER_EMACFINFR_RESERVED3_SHIFT          18 
#define ETHER_EMACFINFR_RESERVED3_BIT            0x3
#define ETHER_EMACFINFR_RESERVED3_BITWIDTH       2
// TFSZ bitfiled (RO) Reset=0
#define ETHER_EMACFINFR_TFSZ_MASK                0x300000
#define ETHER_EMACFINFR_TFSZ_SHIFT               20 
#define ETHER_EMACFINFR_TFSZ_BIT                 0x3
#define ETHER_EMACFINFR_TFSZ_BITWIDTH            2
// Reserved2 bitfiled (RO) Reset=0
#define ETHER_EMACFINFR_RESERVED2_MASK           0xFC00000
#define ETHER_EMACFINFR_RESERVED2_SHIFT          22 
#define ETHER_EMACFINFR_RESERVED2_BIT            0x3F
#define ETHER_EMACFINFR_RESERVED2_BITWIDTH       6
// INTDLY bitfiled (RO) Reset=1
#define ETHER_EMACFINFR_INTDLY_MASK              0x10000000
#define ETHER_EMACFINFR_INTDLY_SHIFT             28 
#define ETHER_EMACFINFR_INTDLY_BIT               0x1
#define ETHER_EMACFINFR_INTDLY_BITWIDTH          1
// Reserved bitfiled (RO) Reset=0
#define ETHER_EMACFINFR_RESERVED_MASK            0xE0000000
#define ETHER_EMACFINFR_RESERVED_SHIFT           29 
#define ETHER_EMACFINFR_RESERVED_BIT             0x7
#define ETHER_EMACFINFR_RESERVED_BITWIDTH        3
// DMACR Register
#define ETHER_DMACR_OFS                          0x00001000
// SWRR bitfiled (RW) Reset=0
#define ETHER_DMACR_SWRR_MASK                    0x1
#define ETHER_DMACR_SWRR_SHIFT                   0 
#define ETHER_DMACR_SWRR_BIT                     0x1
#define ETHER_DMACR_SWRR_BITWIDTH                1
// SWRT bitfiled (RW) Reset=0
#define ETHER_DMACR_SWRT_MASK                    0x2
#define ETHER_DMACR_SWRT_SHIFT                   1 
#define ETHER_DMACR_SWRT_BIT                     0x1
#define ETHER_DMACR_SWRT_BITWIDTH                1
// Reserved2 bitfiled (RO) Reset=0
#define ETHER_DMACR_RESERVED2_MASK               0xC
#define ETHER_DMACR_RESERVED2_SHIFT              2 
#define ETHER_DMACR_RESERVED2_BIT                0x3
#define ETHER_DMACR_RESERVED2_BITWIDTH           2
// DL bitfiled (RW) Reset=0
#define ETHER_DMACR_DL_MASK                      0x30
#define ETHER_DMACR_DL_SHIFT                     4 
#define ETHER_DMACR_DL_BIT                       0x3
#define ETHER_DMACR_DL_BITWIDTH                  2
// DE bitfiled (RW) Reset=0
#define ETHER_DMACR_DE_MASK                      0x40
#define ETHER_DMACR_DE_SHIFT                     6 
#define ETHER_DMACR_DE_BIT                       0x1
#define ETHER_DMACR_DE_BITWIDTH                  1
// Reserved bitfiled (RO) Reset=0
#define ETHER_DMACR_RESERVED_MASK                0xFFFFFF80
#define ETHER_DMACR_RESERVED_SHIFT               7 
#define ETHER_DMACR_RESERVED_BIT                 0x1FFFFFF
#define ETHER_DMACR_RESERVED_BITWIDTH            25
// DMATXR Register
#define ETHER_DMATXR_OFS                         0x00001008
// TRNS bitfiled (RW) Reset=0
#define ETHER_DMATXR_TRNS_MASK                   0x3
#define ETHER_DMATXR_TRNS_SHIFT                  0 
#define ETHER_DMATXR_TRNS_BIT                    0x3
#define ETHER_DMATXR_TRNS_BITWIDTH               2
// Reserved bitfiled (RO) Reset=0
#define ETHER_DMATXR_RESERVED_MASK               0xFFFFFFFC
#define ETHER_DMATXR_RESERVED_SHIFT              2 
#define ETHER_DMATXR_RESERVED_BIT                0x3FFFFFFF
#define ETHER_DMATXR_RESERVED_BITWIDTH           30
// DMARXR Register
#define ETHER_DMARXR_OFS                         0x00001010
// RCV bitfiled (RW) Reset=0
#define ETHER_DMARXR_RCV_MASK                    0x1
#define ETHER_DMARXR_RCV_SHIFT                   0 
#define ETHER_DMARXR_RCV_BIT                     0x1
#define ETHER_DMARXR_RCV_BITWIDTH                1
// Reserved bitfiled (RO) Reset=0
#define ETHER_DMARXR_RESERVED_MASK               0xFFFFFFFE
#define ETHER_DMARXR_RESERVED_SHIFT              1 
#define ETHER_DMARXR_RESERVED_BIT                0x7FFFFFFF
#define ETHER_DMARXR_RESERVED_BITWIDTH           31
// DMAINTR Register
#define ETHER_DMAINTR_OFS                        0x00001028
// RINT1 bitfiled (RW) Reset=0
#define ETHER_DMAINTR_RINT1_MASK                 0x1
#define ETHER_DMAINTR_RINT1_SHIFT                0 
#define ETHER_DMAINTR_RINT1_BIT                  0x1
#define ETHER_DMAINTR_RINT1_BITWIDTH             1
// RINT2 bitfiled (RW) Reset=0
#define ETHER_DMAINTR_RINT2_MASK                 0x2
#define ETHER_DMAINTR_RINT2_SHIFT                1 
#define ETHER_DMAINTR_RINT2_BIT                  0x1
#define ETHER_DMAINTR_RINT2_BITWIDTH             1
// RINT3 bitfiled (RW) Reset=0
#define ETHER_DMAINTR_RINT3_MASK                 0x4
#define ETHER_DMAINTR_RINT3_SHIFT                2 
#define ETHER_DMAINTR_RINT3_BIT                  0x1
#define ETHER_DMAINTR_RINT3_BITWIDTH             1
// RINT4 bitfiled (RW) Reset=0
#define ETHER_DMAINTR_RINT4_MASK                 0x8
#define ETHER_DMAINTR_RINT4_SHIFT                3 
#define ETHER_DMAINTR_RINT4_BIT                  0x1
#define ETHER_DMAINTR_RINT4_BITWIDTH             1
// RINT5 bitfiled (RW) Reset=0
#define ETHER_DMAINTR_RINT5_MASK                 0x10
#define ETHER_DMAINTR_RINT5_SHIFT                4 
#define ETHER_DMAINTR_RINT5_BIT                  0x1
#define ETHER_DMAINTR_RINT5_BITWIDTH             1
// RINT6 bitfiled (RW) Reset=0
#define ETHER_DMAINTR_RINT6_MASK                 0x20
#define ETHER_DMAINTR_RINT6_SHIFT                5 
#define ETHER_DMAINTR_RINT6_BIT                  0x1
#define ETHER_DMAINTR_RINT6_BITWIDTH             1
// RINT7 bitfiled (RW) Reset=0
#define ETHER_DMAINTR_RINT7_MASK                 0x40
#define ETHER_DMAINTR_RINT7_SHIFT                6 
#define ETHER_DMAINTR_RINT7_BIT                  0x1
#define ETHER_DMAINTR_RINT7_BITWIDTH             1
// RINT8 bitfiled (RW) Reset=0
#define ETHER_DMAINTR_RINT8_MASK                 0x80
#define ETHER_DMAINTR_RINT8_SHIFT                7 
#define ETHER_DMAINTR_RINT8_BIT                  0x1
#define ETHER_DMAINTR_RINT8_BITWIDTH             1
// TINT1 bitfiled (RW) Reset=0
#define ETHER_DMAINTR_TINT1_MASK                 0x100
#define ETHER_DMAINTR_TINT1_SHIFT                8 
#define ETHER_DMAINTR_TINT1_BIT                  0x1
#define ETHER_DMAINTR_TINT1_BITWIDTH             1
// TINT2 bitfiled (RW) Reset=0
#define ETHER_DMAINTR_TINT2_MASK                 0x200
#define ETHER_DMAINTR_TINT2_SHIFT                9 
#define ETHER_DMAINTR_TINT2_BIT                  0x1
#define ETHER_DMAINTR_TINT2_BITWIDTH             1
// TINT3 bitfiled (RW) Reset=0
#define ETHER_DMAINTR_TINT3_MASK                 0x400
#define ETHER_DMAINTR_TINT3_SHIFT                10 
#define ETHER_DMAINTR_TINT3_BIT                  0x1
#define ETHER_DMAINTR_TINT3_BITWIDTH             1
// Reserved2 bitfiled (RO) Reset=0
#define ETHER_DMAINTR_RESERVED2_MASK             0xF800
#define ETHER_DMAINTR_RESERVED2_SHIFT            11 
#define ETHER_DMAINTR_RESERVED2_BIT              0x1F
#define ETHER_DMAINTR_RESERVED2_BITWIDTH         5
// RFE bitfiled (RW) Reset=0
#define ETHER_DMAINTR_RFE_MASK                   0x10000
#define ETHER_DMAINTR_RFE_SHIFT                  16 
#define ETHER_DMAINTR_RFE_BIT                    0x1
#define ETHER_DMAINTR_RFE_BITWIDTH               1
// RDE bitfiled (RW) Reset=0
#define ETHER_DMAINTR_RDE_MASK                   0x20000
#define ETHER_DMAINTR_RDE_SHIFT                  17 
#define ETHER_DMAINTR_RDE_BIT                    0x1
#define ETHER_DMAINTR_RDE_BITWIDTH               1
// FRC bitfiled (RW) Reset=0
#define ETHER_DMAINTR_FRC_MASK                   0x40000
#define ETHER_DMAINTR_FRC_SHIFT                  18 
#define ETHER_DMAINTR_FRC_BIT                    0x1
#define ETHER_DMAINTR_FRC_BITWIDTH               1
// TFE bitfiled (RW) Reset=0
#define ETHER_DMAINTR_TFE_MASK                   0x80000
#define ETHER_DMAINTR_TFE_SHIFT                  19 
#define ETHER_DMAINTR_TFE_BIT                    0x1
#define ETHER_DMAINTR_TFE_BITWIDTH               1
// TDE bitfiled (RW) Reset=0
#define ETHER_DMAINTR_TDE_MASK                   0x100000
#define ETHER_DMAINTR_TDE_SHIFT                  20 
#define ETHER_DMAINTR_TDE_BIT                    0x1
#define ETHER_DMAINTR_TDE_BITWIDTH               1
// FTC0 bitfiled (RW) Reset=0
#define ETHER_DMAINTR_FTC0_MASK                  0x200000
#define ETHER_DMAINTR_FTC0_SHIFT                 21 
#define ETHER_DMAINTR_FTC0_BIT                   0x1
#define ETHER_DMAINTR_FTC0_BITWIDTH              1
// MINT bitfiled (RO) Reset=0
#define ETHER_DMAINTR_MINT_MASK                  0x400000
#define ETHER_DMAINTR_MINT_SHIFT                 22 
#define ETHER_DMAINTR_MINT_BIT                   0x1
#define ETHER_DMAINTR_MINT_BITWIDTH              1
// Reserved bitfiled (RO) Reset=0
#define ETHER_DMAINTR_RESERVED_MASK              0x800000
#define ETHER_DMAINTR_RESERVED_SHIFT             23 
#define ETHER_DMAINTR_RESERVED_BIT               0x1
#define ETHER_DMAINTR_RESERVED_BITWIDTH          1
// RFRMER bitfiled (RW) Reset=0
#define ETHER_DMAINTR_RFRMER_MASK                0x1000000
#define ETHER_DMAINTR_RFRMER_SHIFT               24 
#define ETHER_DMAINTR_RFRMER_BIT                 0x1
#define ETHER_DMAINTR_RFRMER_BITWIDTH            1
// RABT bitfiled (RW) Reset=0
#define ETHER_DMAINTR_RABT_MASK                  0x2000000
#define ETHER_DMAINTR_RABT_SHIFT                 25 
#define ETHER_DMAINTR_RABT_BIT                   0x1
#define ETHER_DMAINTR_RABT_BITWIDTH              1
// TABT bitfiled (RW) Reset=0
#define ETHER_DMAINTR_TABT_MASK                  0x4000000
#define ETHER_DMAINTR_TABT_SHIFT                 26 
#define ETHER_DMAINTR_TABT_BIT                   0x1
#define ETHER_DMAINTR_TABT_BITWIDTH              1
// ROC bitfiled (RW) Reset=0
#define ETHER_DMAINTR_ROC_MASK                   0x8000000
#define ETHER_DMAINTR_ROC_SHIFT                  27 
#define ETHER_DMAINTR_ROC_BIT                    0x1
#define ETHER_DMAINTR_ROC_BITWIDTH               1
// TUC bitfiled (RW) Reset=0
#define ETHER_DMAINTR_TUC_MASK                   0x10000000
#define ETHER_DMAINTR_TUC_SHIFT                  28 
#define ETHER_DMAINTR_TUC_BIT                    0x1
#define ETHER_DMAINTR_TUC_BITWIDTH               1
// FTC1 bitfiled (RW) Reset=0
#define ETHER_DMAINTR_FTC1_MASK                  0x20000000
#define ETHER_DMAINTR_FTC1_SHIFT                 29 
#define ETHER_DMAINTR_FTC1_BIT                   0x1
#define ETHER_DMAINTR_FTC1_BITWIDTH              1
// WB0 bitfiled (RW) Reset=0
#define ETHER_DMAINTR_WB0_MASK                   0x40000000
#define ETHER_DMAINTR_WB0_SHIFT                  30 
#define ETHER_DMAINTR_WB0_BIT                    0x1
#define ETHER_DMAINTR_WB0_BITWIDTH               1
// WB1 bitfiled (RW) Reset=0
#define ETHER_DMAINTR_WB1_MASK                   0x80000000
#define ETHER_DMAINTR_WB1_SHIFT                  31 
#define ETHER_DMAINTR_WB1_BIT                    0x1
#define ETHER_DMAINTR_WB1_BITWIDTH               1
// DMAINTENR Register
#define ETHER_DMAINTENR_OFS                      0x00001030
// RINT1 bitfiled (RW) Reset=0
#define ETHER_DMAINTENR_RINT1_MASK               0x1
#define ETHER_DMAINTENR_RINT1_SHIFT              0 
#define ETHER_DMAINTENR_RINT1_BIT                0x1
#define ETHER_DMAINTENR_RINT1_BITWIDTH           1
// RINT2 bitfiled (RW) Reset=0
#define ETHER_DMAINTENR_RINT2_MASK               0x2
#define ETHER_DMAINTENR_RINT2_SHIFT              1 
#define ETHER_DMAINTENR_RINT2_BIT                0x1
#define ETHER_DMAINTENR_RINT2_BITWIDTH           1
// RINT3 bitfiled (RW) Reset=0
#define ETHER_DMAINTENR_RINT3_MASK               0x4
#define ETHER_DMAINTENR_RINT3_SHIFT              2 
#define ETHER_DMAINTENR_RINT3_BIT                0x1
#define ETHER_DMAINTENR_RINT3_BITWIDTH           1
// RINT4 bitfiled (RW) Reset=0
#define ETHER_DMAINTENR_RINT4_MASK               0x8
#define ETHER_DMAINTENR_RINT4_SHIFT              3 
#define ETHER_DMAINTENR_RINT4_BIT                0x1
#define ETHER_DMAINTENR_RINT4_BITWIDTH           1
// RINT5 bitfiled (RW) Reset=0
#define ETHER_DMAINTENR_RINT5_MASK               0x10
#define ETHER_DMAINTENR_RINT5_SHIFT              4 
#define ETHER_DMAINTENR_RINT5_BIT                0x1
#define ETHER_DMAINTENR_RINT5_BITWIDTH           1
// RINT6 bitfiled (RW) Reset=0
#define ETHER_DMAINTENR_RINT6_MASK               0x20
#define ETHER_DMAINTENR_RINT6_SHIFT              5 
#define ETHER_DMAINTENR_RINT6_BIT                0x1
#define ETHER_DMAINTENR_RINT6_BITWIDTH           1
// RINT7 bitfiled (RW) Reset=0
#define ETHER_DMAINTENR_RINT7_MASK               0x40
#define ETHER_DMAINTENR_RINT7_SHIFT              6 
#define ETHER_DMAINTENR_RINT7_BIT                0x1
#define ETHER_DMAINTENR_RINT7_BITWIDTH           1
// RINT8 bitfiled (RW) Reset=0
#define ETHER_DMAINTENR_RINT8_MASK               0x80
#define ETHER_DMAINTENR_RINT8_SHIFT              7 
#define ETHER_DMAINTENR_RINT8_BIT                0x1
#define ETHER_DMAINTENR_RINT8_BITWIDTH           1
// TINT1 bitfiled (RW) Reset=0
#define ETHER_DMAINTENR_TINT1_MASK               0x100
#define ETHER_DMAINTENR_TINT1_SHIFT              8 
#define ETHER_DMAINTENR_TINT1_BIT                0x1
#define ETHER_DMAINTENR_TINT1_BITWIDTH           1
// TINT2 bitfiled (RW) Reset=0
#define ETHER_DMAINTENR_TINT2_MASK               0x200
#define ETHER_DMAINTENR_TINT2_SHIFT              9 
#define ETHER_DMAINTENR_TINT2_BIT                0x1
#define ETHER_DMAINTENR_TINT2_BITWIDTH           1
// TINT3 bitfiled (RW) Reset=0
#define ETHER_DMAINTENR_TINT3_MASK               0x400
#define ETHER_DMAINTENR_TINT3_SHIFT              10 
#define ETHER_DMAINTENR_TINT3_BIT                0x1
#define ETHER_DMAINTENR_TINT3_BITWIDTH           1
// Reserved2 bitfiled (RO) Reset=0
#define ETHER_DMAINTENR_RESERVED2_MASK           0xF800
#define ETHER_DMAINTENR_RESERVED2_SHIFT          11 
#define ETHER_DMAINTENR_RESERVED2_BIT            0x1F
#define ETHER_DMAINTENR_RESERVED2_BITWIDTH       5
// RFE bitfiled (RW) Reset=0
#define ETHER_DMAINTENR_RFE_MASK                 0x10000
#define ETHER_DMAINTENR_RFE_SHIFT                16 
#define ETHER_DMAINTENR_RFE_BIT                  0x1
#define ETHER_DMAINTENR_RFE_BITWIDTH             1
// RDE bitfiled (RW) Reset=0
#define ETHER_DMAINTENR_RDE_MASK                 0x20000
#define ETHER_DMAINTENR_RDE_SHIFT                17 
#define ETHER_DMAINTENR_RDE_BIT                  0x1
#define ETHER_DMAINTENR_RDE_BITWIDTH             1
// FRC bitfiled (RW) Reset=0
#define ETHER_DMAINTENR_FRC_MASK                 0x40000
#define ETHER_DMAINTENR_FRC_SHIFT                18 
#define ETHER_DMAINTENR_FRC_BIT                  0x1
#define ETHER_DMAINTENR_FRC_BITWIDTH             1
// TFE bitfiled (RW) Reset=0
#define ETHER_DMAINTENR_TFE_MASK                 0x80000
#define ETHER_DMAINTENR_TFE_SHIFT                19 
#define ETHER_DMAINTENR_TFE_BIT                  0x1
#define ETHER_DMAINTENR_TFE_BITWIDTH             1
// TDE bitfiled (RW) Reset=0
#define ETHER_DMAINTENR_TDE_MASK                 0x100000
#define ETHER_DMAINTENR_TDE_SHIFT                20 
#define ETHER_DMAINTENR_TDE_BIT                  0x1
#define ETHER_DMAINTENR_TDE_BITWIDTH             1
// FTC0 bitfiled (RW) Reset=0
#define ETHER_DMAINTENR_FTC0_MASK                0x200000
#define ETHER_DMAINTENR_FTC0_SHIFT               21 
#define ETHER_DMAINTENR_FTC0_BIT                 0x1
#define ETHER_DMAINTENR_FTC0_BITWIDTH            1
// MINT bitfiled (RW) Reset=0
#define ETHER_DMAINTENR_MINT_MASK                0x400000
#define ETHER_DMAINTENR_MINT_SHIFT               22 
#define ETHER_DMAINTENR_MINT_BIT                 0x1
#define ETHER_DMAINTENR_MINT_BITWIDTH            1
// Reserved bitfiled (RO) Reset=0
#define ETHER_DMAINTENR_RESERVED_MASK            0x800000
#define ETHER_DMAINTENR_RESERVED_SHIFT           23 
#define ETHER_DMAINTENR_RESERVED_BIT             0x1
#define ETHER_DMAINTENR_RESERVED_BITWIDTH        1
// RFRMER bitfiled (RW) Reset=0
#define ETHER_DMAINTENR_RFRMER_MASK              0x1000000
#define ETHER_DMAINTENR_RFRMER_SHIFT             24 
#define ETHER_DMAINTENR_RFRMER_BIT               0x1
#define ETHER_DMAINTENR_RFRMER_BITWIDTH          1
// RABT bitfiled (RW) Reset=0
#define ETHER_DMAINTENR_RABT_MASK                0x2000000
#define ETHER_DMAINTENR_RABT_SHIFT               25 
#define ETHER_DMAINTENR_RABT_BIT                 0x1
#define ETHER_DMAINTENR_RABT_BITWIDTH            1
// TABT bitfiled (RW) Reset=0
#define ETHER_DMAINTENR_TABT_MASK                0x4000000
#define ETHER_DMAINTENR_TABT_SHIFT               26 
#define ETHER_DMAINTENR_TABT_BIT                 0x1
#define ETHER_DMAINTENR_TABT_BITWIDTH            1
// ROC bitfiled (RW) Reset=0
#define ETHER_DMAINTENR_ROC_MASK                 0x8000000
#define ETHER_DMAINTENR_ROC_SHIFT                27 
#define ETHER_DMAINTENR_ROC_BIT                  0x1
#define ETHER_DMAINTENR_ROC_BITWIDTH             1
// TUC bitfiled (RW) Reset=0
#define ETHER_DMAINTENR_TUC_MASK                 0x10000000
#define ETHER_DMAINTENR_TUC_SHIFT                28 
#define ETHER_DMAINTENR_TUC_BIT                  0x1
#define ETHER_DMAINTENR_TUC_BITWIDTH             1
// FTC1 bitfiled (RW) Reset=0
#define ETHER_DMAINTENR_FTC1_MASK                0x20000000
#define ETHER_DMAINTENR_FTC1_SHIFT               29 
#define ETHER_DMAINTENR_FTC1_BIT                 0x1
#define ETHER_DMAINTENR_FTC1_BITWIDTH            1
// WB0 bitfiled (RW) Reset=0
#define ETHER_DMAINTENR_WB0_MASK                 0x40000000
#define ETHER_DMAINTENR_WB0_SHIFT                30 
#define ETHER_DMAINTENR_WB0_BIT                  0x1
#define ETHER_DMAINTENR_WB0_BITWIDTH             1
// WB1 bitfiled (RW) Reset=0
#define ETHER_DMAINTENR_WB1_MASK                 0x80000000
#define ETHER_DMAINTENR_WB1_SHIFT                31 
#define ETHER_DMAINTENR_WB1_BIT                  0x1
#define ETHER_DMAINTENR_WB1_BITWIDTH             1
// ERRMSKR Register
#define ETHER_ERRMSKR_OFS                        0x00001038
// RINT1 bitfiled (RW) Reset=0
#define ETHER_ERRMSKR_RINT1_MASK                 0x1
#define ETHER_ERRMSKR_RINT1_SHIFT                0 
#define ETHER_ERRMSKR_RINT1_BIT                  0x1
#define ETHER_ERRMSKR_RINT1_BITWIDTH             1
// RINT2 bitfiled (RW) Reset=0
#define ETHER_ERRMSKR_RINT2_MASK                 0x2
#define ETHER_ERRMSKR_RINT2_SHIFT                1 
#define ETHER_ERRMSKR_RINT2_BIT                  0x1
#define ETHER_ERRMSKR_RINT2_BITWIDTH             1
// RINT3 bitfiled (RW) Reset=0
#define ETHER_ERRMSKR_RINT3_MASK                 0x4
#define ETHER_ERRMSKR_RINT3_SHIFT                2 
#define ETHER_ERRMSKR_RINT3_BIT                  0x1
#define ETHER_ERRMSKR_RINT3_BITWIDTH             1
// RINT4 bitfiled (RW) Reset=0
#define ETHER_ERRMSKR_RINT4_MASK                 0x8
#define ETHER_ERRMSKR_RINT4_SHIFT                3 
#define ETHER_ERRMSKR_RINT4_BIT                  0x1
#define ETHER_ERRMSKR_RINT4_BITWIDTH             1
// RINT5 bitfiled (RW) Reset=0
#define ETHER_ERRMSKR_RINT5_MASK                 0x10
#define ETHER_ERRMSKR_RINT5_SHIFT                4 
#define ETHER_ERRMSKR_RINT5_BIT                  0x1
#define ETHER_ERRMSKR_RINT5_BITWIDTH             1
// RINT6 bitfiled (RW) Reset=0
#define ETHER_ERRMSKR_RINT6_MASK                 0x20
#define ETHER_ERRMSKR_RINT6_SHIFT                5 
#define ETHER_ERRMSKR_RINT6_BIT                  0x1
#define ETHER_ERRMSKR_RINT6_BITWIDTH             1
// RINT7 bitfiled (RW) Reset=0
#define ETHER_ERRMSKR_RINT7_MASK                 0x40
#define ETHER_ERRMSKR_RINT7_SHIFT                6 
#define ETHER_ERRMSKR_RINT7_BIT                  0x1
#define ETHER_ERRMSKR_RINT7_BITWIDTH             1
// RINT8 bitfiled (RW) Reset=0
#define ETHER_ERRMSKR_RINT8_MASK                 0x80
#define ETHER_ERRMSKR_RINT8_SHIFT                7 
#define ETHER_ERRMSKR_RINT8_BIT                  0x1
#define ETHER_ERRMSKR_RINT8_BITWIDTH             1
// TINT1 bitfiled (RW) Reset=0
#define ETHER_ERRMSKR_TINT1_MASK                 0x100
#define ETHER_ERRMSKR_TINT1_SHIFT                8 
#define ETHER_ERRMSKR_TINT1_BIT                  0x1
#define ETHER_ERRMSKR_TINT1_BITWIDTH             1
// TINT2 bitfiled (RW) Reset=0
#define ETHER_ERRMSKR_TINT2_MASK                 0x200
#define ETHER_ERRMSKR_TINT2_SHIFT                9 
#define ETHER_ERRMSKR_TINT2_BIT                  0x1
#define ETHER_ERRMSKR_TINT2_BITWIDTH             1
// TINT3 bitfiled (RW) Reset=0
#define ETHER_ERRMSKR_TINT3_MASK                 0x400
#define ETHER_ERRMSKR_TINT3_SHIFT                10 
#define ETHER_ERRMSKR_TINT3_BIT                  0x1
#define ETHER_ERRMSKR_TINT3_BITWIDTH             1
// Reserved2 bitfiled (RO) Reset=0
#define ETHER_ERRMSKR_RESERVED2_MASK             0xF800
#define ETHER_ERRMSKR_RESERVED2_SHIFT            11 
#define ETHER_ERRMSKR_RESERVED2_BIT              0x1F
#define ETHER_ERRMSKR_RESERVED2_BITWIDTH         5
// RABT bitfiled (RW) Reset=0
#define ETHER_ERRMSKR_RABT_MASK                  0x10000
#define ETHER_ERRMSKR_RABT_SHIFT                 16 
#define ETHER_ERRMSKR_RABT_BIT                   0x1
#define ETHER_ERRMSKR_RABT_BITWIDTH              1
// TABT bitfiled (RW) Reset=0
#define ETHER_ERRMSKR_TABT_MASK                  0x20000
#define ETHER_ERRMSKR_TABT_SHIFT                 17 
#define ETHER_ERRMSKR_TABT_BIT                   0x1
#define ETHER_ERRMSKR_TABT_BITWIDTH              1
// Reserved bitfiled (RO) Reset=0
#define ETHER_ERRMSKR_RESERVED_MASK              0xFFFC0000
#define ETHER_ERRMSKR_RESERVED_SHIFT             18 
#define ETHER_ERRMSKR_RESERVED_BIT               0x3FFF
#define ETHER_ERRMSKR_RESERVED_BITWIDTH          14
// RXMISCNTR Register
#define ETHER_RXMISCNTR_OFS                      0x00001040
// MIS bitfiled (RW) Reset=0
#define ETHER_RXMISCNTR_MIS_MASK                 0xFFFF
#define ETHER_RXMISCNTR_MIS_SHIFT                0 
#define ETHER_RXMISCNTR_MIS_BIT                  0xFFFF
#define ETHER_RXMISCNTR_MIS_BITWIDTH             16
// Reserved bitfiled (RO) Reset=0
#define ETHER_RXMISCNTR_RESERVED_MASK            0xFFFF0000
#define ETHER_RXMISCNTR_RESERVED_SHIFT           16 
#define ETHER_RXMISCNTR_RESERVED_BIT             0xFFFF
#define ETHER_RXMISCNTR_RESERVED_BITWIDTH        16
// TXFIFOTHR Register
#define ETHER_TXFIFOTHR_OFS                      0x00001048
// FO bitfiled (RW) Reset=0
#define ETHER_TXFIFOTHR_FO_MASK                  0x7FF
#define ETHER_TXFIFOTHR_FO_SHIFT                 0 
#define ETHER_TXFIFOTHR_FO_BIT                   0x7FF
#define ETHER_TXFIFOTHR_FO_BITWIDTH              11
// Reserved bitfiled (RO) Reset=0
#define ETHER_TXFIFOTHR_RESERVED_MASK            0xFFFFF800
#define ETHER_TXFIFOTHR_RESERVED_SHIFT           11 
#define ETHER_TXFIFOTHR_RESERVED_BIT             0x1FFFFF
#define ETHER_TXFIFOTHR_RESERVED_BITWIDTH        21
// FIFOSIZER Register
#define ETHER_FIFOSIZER_OFS                      0x00001050
// RA bitfiled (RW) Reset=0
#define ETHER_FIFOSIZER_RA_MASK                  0xFF
#define ETHER_FIFOSIZER_RA_SHIFT                 0 
#define ETHER_FIFOSIZER_RA_BIT                   0xFF
#define ETHER_FIFOSIZER_RA_BITWIDTH              8
// TA bitfiled (RW) Reset=0
#define ETHER_FIFOSIZER_TA_MASK                  0x1F00
#define ETHER_FIFOSIZER_TA_SHIFT                 8 
#define ETHER_FIFOSIZER_TA_BIT                   0x1F
#define ETHER_FIFOSIZER_TA_BITWIDTH              5
// Reserved bitfiled (RO) Reset=0
#define ETHER_FIFOSIZER_RESERVED_MASK            0xFFFFE000
#define ETHER_FIFOSIZER_RESERVED_SHIFT           13 
#define ETHER_FIFOSIZER_RESERVED_BIT             0x7FFFF
#define ETHER_FIFOSIZER_RESERVED_BITWIDTH        19
// DMARXMODR Register
#define ETHER_DMARXMODR_OFS                      0x00001058
// RCVMOD bitfiled (RW) Reset=0
#define ETHER_DMARXMODR_RCVMOD_MASK              0x1
#define ETHER_DMARXMODR_RCVMOD_SHIFT             0 
#define ETHER_DMARXMODR_RCVMOD_BIT               0x1
#define ETHER_DMARXMODR_RCVMOD_BITWIDTH          1
// Reserved bitfiled (RO) Reset=0
#define ETHER_DMARXMODR_RESERVED_MASK            0xFFFFFFFE
#define ETHER_DMARXMODR_RESERVED_SHIFT           1 
#define ETHER_DMARXMODR_RESERVED_BIT             0x7FFFFFFF
#define ETHER_DMARXMODR_RESERVED_BITWIDTH        31
// RXPADR Register
#define ETHER_RXPADR_OFS                         0x00001060
// PADP bitfiled (RW) Reset=0
#define ETHER_RXPADR_PADP_MASK                   0xFFFF
#define ETHER_RXPADR_PADP_SHIFT                  0 
#define ETHER_RXPADR_PADP_BIT                    0xFFFF
#define ETHER_RXPADR_PADP_BITWIDTH               16
// PADS bitfiled (RW) Reset=0
#define ETHER_RXPADR_PADS_MASK                   0x1F0000
#define ETHER_RXPADR_PADS_SHIFT                  16 
#define ETHER_RXPADR_PADS_BIT                    0x1F
#define ETHER_RXPADR_PADS_BITWIDTH               5
// Reserved bitfiled (RO) Reset=0
#define ETHER_RXPADR_RESERVED_MASK               0xFFE00000
#define ETHER_RXPADR_RESERVED_SHIFT              21 
#define ETHER_RXPADR_RESERVED_BIT                0x7FF
#define ETHER_RXPADR_RESERVED_BITWIDTH           11
// RXFIFOTHR Register
#define ETHER_RXFIFOTHR_OFS                      0x00001068
// RFD bitfiled (RW) Reset=11111111
#define ETHER_RXFIFOTHR_RFD_MASK                 0xFF
#define ETHER_RXFIFOTHR_RFD_SHIFT                0 
#define ETHER_RXFIFOTHR_RFD_BIT                  0xFF
#define ETHER_RXFIFOTHR_RFD_BITWIDTH             8
// Reserved2 bitfiled (RO) Reset=0
#define ETHER_RXFIFOTHR_RESERVED2_MASK           0xFF00
#define ETHER_RXFIFOTHR_RESERVED2_SHIFT          8 
#define ETHER_RXFIFOTHR_RESERVED2_BIT            0xFF
#define ETHER_RXFIFOTHR_RESERVED2_BITWIDTH       8
// RFF bitfiled (RW) Reset=10111
#define ETHER_RXFIFOTHR_RFF_MASK                 0x1F0000
#define ETHER_RXFIFOTHR_RFF_SHIFT                16 
#define ETHER_RXFIFOTHR_RFF_BIT                  0x1F
#define ETHER_RXFIFOTHR_RFF_BITWIDTH             5
// Reserved bitfiled (RO) Reset=0
#define ETHER_RXFIFOTHR_RESERVED_MASK            0xFFE00000
#define ETHER_RXFIFOTHR_RESERVED_SHIFT           21 
#define ETHER_RXFIFOTHR_RESERVED_BIT             0x7FF
#define ETHER_RXFIFOTHR_RESERVED_BITWIDTH        11
// TXFIFOSTSR Register
#define ETHER_TXFIFOSTSR_OFS                     0x00001080
// DAM bitfiled (RO) Reset=0
#define ETHER_TXFIFOSTSR_DAM_MASK                0xFF
#define ETHER_TXFIFOSTSR_DAM_SHIFT               0 
#define ETHER_TXFIFOSTSR_DAM_BIT                 0xFF
#define ETHER_TXFIFOSTSR_DAM_BITWIDTH            8
// Reserved4 bitfiled (RO) Reset=0
#define ETHER_TXFIFOSTSR_RESERVED4_MASK          0xFF00
#define ETHER_TXFIFOSTSR_RESERVED4_SHIFT         8 
#define ETHER_TXFIFOSTSR_RESERVED4_BIT           0xFF
#define ETHER_TXFIFOSTSR_RESERVED4_BITWIDTH      8
// FAM bitfiled (RO) Reset=0
#define ETHER_TXFIFOSTSR_FAM_MASK                0x70000
#define ETHER_TXFIFOSTSR_FAM_SHIFT               16 
#define ETHER_TXFIFOSTSR_FAM_BIT                 0x7
#define ETHER_TXFIFOSTSR_FAM_BITWIDTH            3
// Reserved3 bitfiled (RO) Reset=0
#define ETHER_TXFIFOSTSR_RESERVED3_MASK          0xF80000
#define ETHER_TXFIFOSTSR_RESERVED3_SHIFT         19 
#define ETHER_TXFIFOSTSR_RESERVED3_BIT           0x1F
#define ETHER_TXFIFOSTSR_RESERVED3_BITWIDTH      5
// D_EN bitfiled (RO) Reset=1
#define ETHER_TXFIFOSTSR_D_EN_MASK               0x1000000
#define ETHER_TXFIFOSTSR_D_EN_SHIFT              24 
#define ETHER_TXFIFOSTSR_D_EN_BIT                0x1
#define ETHER_TXFIFOSTSR_D_EN_BITWIDTH           1
// F_EN bitfiled (RO) Reset=1
#define ETHER_TXFIFOSTSR_F_EN_MASK               0x2000000
#define ETHER_TXFIFOSTSR_F_EN_SHIFT              25 
#define ETHER_TXFIFOSTSR_F_EN_BIT                0x1
#define ETHER_TXFIFOSTSR_F_EN_BITWIDTH           1
// WB bitfiled (RO) Reset=0
#define ETHER_TXFIFOSTSR_WB_MASK                 0x4000000
#define ETHER_TXFIFOSTSR_WB_SHIFT                26 
#define ETHER_TXFIFOSTSR_WB_BIT                  0x1
#define ETHER_TXFIFOSTSR_WB_BITWIDTH             1
// Reserved2 bitfiled (RO) Reset=0
#define ETHER_TXFIFOSTSR_RESERVED2_MASK          0x8000000
#define ETHER_TXFIFOSTSR_RESERVED2_SHIFT         27 
#define ETHER_TXFIFOSTSR_RESERVED2_BIT           0x1
#define ETHER_TXFIFOSTSR_RESERVED2_BITWIDTH      1
// STP bitfiled (RO) Reset=0
#define ETHER_TXFIFOSTSR_STP_MASK                0x10000000
#define ETHER_TXFIFOSTSR_STP_SHIFT               28 
#define ETHER_TXFIFOSTSR_STP_BIT                 0x1
#define ETHER_TXFIFOSTSR_STP_BITWIDTH            1
// DMA bitfiled (RO) Reset=0
#define ETHER_TXFIFOSTSR_DMA_MASK                0x20000000
#define ETHER_TXFIFOSTSR_DMA_SHIFT               29 
#define ETHER_TXFIFOSTSR_DMA_BIT                 0x1
#define ETHER_TXFIFOSTSR_DMA_BITWIDTH            1
// WAI bitfiled (RO) Reset=0
#define ETHER_TXFIFOSTSR_WAI_MASK                0x40000000
#define ETHER_TXFIFOSTSR_WAI_SHIFT               30 
#define ETHER_TXFIFOSTSR_WAI_BIT                 0x1
#define ETHER_TXFIFOSTSR_WAI_BITWIDTH            1
// Reserved bitfiled (RO) Reset=0
#define ETHER_TXFIFOSTSR_RESERVED_MASK           0x80000000
#define ETHER_TXFIFOSTSR_RESERVED_SHIFT          31 
#define ETHER_TXFIFOSTSR_RESERVED_BIT            0x1
#define ETHER_TXFIFOSTSR_RESERVED_BITWIDTH       1
// RXFIFOSTSR Register
#define ETHER_RXFIFOSTSR_OFS                     0x00001088
// DAM bitfiled (RO) Reset=0
#define ETHER_RXFIFOSTSR_DAM_MASK                0xFFF
#define ETHER_RXFIFOSTSR_DAM_SHIFT               0 
#define ETHER_RXFIFOSTSR_DAM_BIT                 0xFFF
#define ETHER_RXFIFOSTSR_DAM_BITWIDTH            12
// Reserved3 bitfiled (RO) Reset=0
#define ETHER_RXFIFOSTSR_RESERVED3_MASK          0xF000
#define ETHER_RXFIFOSTSR_RESERVED3_SHIFT         12 
#define ETHER_RXFIFOSTSR_RESERVED3_BIT           0xF
#define ETHER_RXFIFOSTSR_RESERVED3_BITWIDTH      4
// FAM bitfiled (RO) Reset=0
#define ETHER_RXFIFOSTSR_FAM_MASK                0x1F0000
#define ETHER_RXFIFOSTSR_FAM_SHIFT               16 
#define ETHER_RXFIFOSTSR_FAM_BIT                 0x1F
#define ETHER_RXFIFOSTSR_FAM_BITWIDTH            5
// Reserved2 bitfiled (RO) Reset=0
#define ETHER_RXFIFOSTSR_RESERVED2_MASK          0xE00000
#define ETHER_RXFIFOSTSR_RESERVED2_SHIFT         21 
#define ETHER_RXFIFOSTSR_RESERVED2_BIT           0x7
#define ETHER_RXFIFOSTSR_RESERVED2_BITWIDTH      3
// D_EN bitfiled (RO) Reset=0
#define ETHER_RXFIFOSTSR_D_EN_MASK               0x1000000
#define ETHER_RXFIFOSTSR_D_EN_SHIFT              24 
#define ETHER_RXFIFOSTSR_D_EN_BIT                0x1
#define ETHER_RXFIFOSTSR_D_EN_BITWIDTH           1
// F_EN bitfiled (RO) Reset=0
#define ETHER_RXFIFOSTSR_F_EN_MASK               0x2000000
#define ETHER_RXFIFOSTSR_F_EN_SHIFT              25 
#define ETHER_RXFIFOSTSR_F_EN_BIT                0x1
#define ETHER_RXFIFOSTSR_F_EN_BITWIDTH           1
// Reserved bitfiled (RO) Reset=0
#define ETHER_RXFIFOSTSR_RESERVED_MASK           0xFC000000
#define ETHER_RXFIFOSTSR_RESERVED_SHIFT          26 
#define ETHER_RXFIFOSTSR_RESERVED_BIT            0x3F
#define ETHER_RXFIFOSTSR_RESERVED_BITWIDTH       6
// MACCR Register
#define ETHER_MACCR_OFS                          0x00001100
// PRM bitfiled (RW) Reset=0
#define ETHER_MACCR_PRM_MASK                     0x1
#define ETHER_MACCR_PRM_SHIFT                    0 
#define ETHER_MACCR_PRM_BIT                      0x1
#define ETHER_MACCR_PRM_BITWIDTH                 1
// DPM bitfiled (RW) Reset=0
#define ETHER_MACCR_DPM_MASK                     0x2
#define ETHER_MACCR_DPM_SHIFT                    1 
#define ETHER_MACCR_DPM_BIT                      0x1
#define ETHER_MACCR_DPM_BITWIDTH                 1
// Reserved4 bitfiled (RO) Reset=0
#define ETHER_MACCR_RESERVED4_MASK               0x1C
#define ETHER_MACCR_RESERVED4_SHIFT              2 
#define ETHER_MACCR_RESERVED4_BIT                0x7
#define ETHER_MACCR_RESERVED4_BITWIDTH           3
// TPE bitfiled (RW) Reset=0
#define ETHER_MACCR_TPE_MASK                     0x20
#define ETHER_MACCR_TPE_SHIFT                    5 
#define ETHER_MACCR_TPE_BIT                      0x1
#define ETHER_MACCR_TPE_BITWIDTH                 1
// RPE bitfiled (RW) Reset=0
#define ETHER_MACCR_RPE_MASK                     0x40
#define ETHER_MACCR_RPE_SHIFT                    6 
#define ETHER_MACCR_RPE_BIT                      0x1
#define ETHER_MACCR_RPE_BITWIDTH                 1
// Reserved3 bitfiled (RO) Reset=0
#define ETHER_MACCR_RESERVED3_MASK               0xFF80
#define ETHER_MACCR_RESERVED3_SHIFT              7 
#define ETHER_MACCR_RESERVED3_BIT                0x1FF
#define ETHER_MACCR_RESERVED3_BITWIDTH           9
// TXF bitfiled (RW) Reset=0
#define ETHER_MACCR_TXF_MASK                     0x10000
#define ETHER_MACCR_TXF_SHIFT                    16 
#define ETHER_MACCR_TXF_BIT                      0x1
#define ETHER_MACCR_TXF_BITWIDTH                 1
// RXF bitfiled (RW) Reset=0
#define ETHER_MACCR_RXF_MASK                     0x20000
#define ETHER_MACCR_RXF_SHIFT                    17 
#define ETHER_MACCR_RXF_BIT                      0x1
#define ETHER_MACCR_RXF_BITWIDTH                 1
// PFR bitfiled (RW) Reset=0
#define ETHER_MACCR_PFR_MASK                     0x40000
#define ETHER_MACCR_PFR_SHIFT                    18 
#define ETHER_MACCR_PFR_BIT                      0x1
#define ETHER_MACCR_PFR_BITWIDTH                 1
// TZPF bitfiled (RW) Reset=0
#define ETHER_MACCR_TZPF_MASK                    0x80000
#define ETHER_MACCR_TZPF_SHIFT                   19 
#define ETHER_MACCR_TZPF_BIT                     0x1
#define ETHER_MACCR_TZPF_BITWIDTH                1
// RZPF bitfiled (RW) Reset=0
#define ETHER_MACCR_RZPF_MASK                    0x100000
#define ETHER_MACCR_RZPF_SHIFT                   20 
#define ETHER_MACCR_RZPF_BIT                     0x1
#define ETHER_MACCR_RZPF_BITWIDTH                1
// DPAD bitfiled (RW) Reset=0
#define ETHER_MACCR_DPAD_MASK                    0x200000
#define ETHER_MACCR_DPAD_SHIFT                   21 
#define ETHER_MACCR_DPAD_BIT                     0x1
#define ETHER_MACCR_DPAD_BITWIDTH                1
// Reserved2 bitfiled (RO) Reset=0
#define ETHER_MACCR_RESERVED2_MASK               0x400000
#define ETHER_MACCR_RESERVED2_SHIFT              22 
#define ETHER_MACCR_RESERVED2_BIT                0x1
#define ETHER_MACCR_RESERVED2_BITWIDTH           1
// RCSC bitfiled (RW) Reset=0
#define ETHER_MACCR_RCSC_MASK                    0x800000
#define ETHER_MACCR_RCSC_SHIFT                   23 
#define ETHER_MACCR_RCSC_BIT                     0x1
#define ETHER_MACCR_RCSC_BITWIDTH                1
// TCPT bitfiled (RW) Reset=0
#define ETHER_MACCR_TCPT_MASK                    0x1000000
#define ETHER_MACCR_TCPT_SHIFT                   24 
#define ETHER_MACCR_TCPT_BIT                     0x1
#define ETHER_MACCR_TCPT_BITWIDTH                1
// RCPT bitfiled (RW) Reset=0
#define ETHER_MACCR_RCPT_MASK                    0x2000000
#define ETHER_MACCR_RCPT_SHIFT                   25 
#define ETHER_MACCR_RCPT_BIT                     0x1
#define ETHER_MACCR_RCPT_BITWIDTH                1
// TRCCM bitfiled (RW) Reset=0
#define ETHER_MACCR_TRCCM_MASK                   0x4000000
#define ETHER_MACCR_TRCCM_SHIFT                  26 
#define ETHER_MACCR_TRCCM_BIT                    0x1
#define ETHER_MACCR_TRCCM_BITWIDTH               1
// Reserved bitfiled (RO) Reset=0
#define ETHER_MACCR_RESERVED_MASK                0xF8000000
#define ETHER_MACCR_RESERVED_SHIFT               27 
#define ETHER_MACCR_RESERVED_BIT                 0x1F
#define ETHER_MACCR_RESERVED_BITWIDTH            5
// LENLMTR Register
#define ETHER_LENLMTR_OFS                        0x00001108
// LENLMT bitfiled (RW) Reset=0
#define ETHER_LENLMTR_LENLMT_MASK                0x3FFFF
#define ETHER_LENLMTR_LENLMT_SHIFT               0 
#define ETHER_LENLMTR_LENLMT_BIT                 0x3FFFF
#define ETHER_LENLMTR_LENLMT_BITWIDTH            18
// Reserved bitfiled (RO) Reset=0
#define ETHER_LENLMTR_RESERVED_MASK              0xFFFC0000
#define ETHER_LENLMTR_RESERVED_SHIFT             18 
#define ETHER_LENLMTR_RESERVED_BIT               0x3FFF
#define ETHER_LENLMTR_RESERVED_BITWIDTH          14
// MACINTR Register
#define ETHER_MACINTR_OFS                        0x00001110
// FCI bitfiled (RW) Reset=0
#define ETHER_MACINTR_FCI_MASK                   0x1
#define ETHER_MACINTR_FCI_SHIFT                  0 
#define ETHER_MACINTR_FCI_BIT                    0x1
#define ETHER_MACINTR_FCI_BITWIDTH               1
// Reserved2 bitfiled (RO) Reset=0
#define ETHER_MACINTR_RESERVED2_MASK             0xE
#define ETHER_MACINTR_RESERVED2_SHIFT            1 
#define ETHER_MACINTR_RESERVED2_BIT              0x7
#define ETHER_MACINTR_RESERVED2_BITWIDTH         3
// PFRI bitfiled (RW) Reset=0
#define ETHER_MACINTR_PFRI_MASK                  0x10
#define ETHER_MACINTR_PFRI_SHIFT                 4 
#define ETHER_MACINTR_PFRI_BIT                   0x1
#define ETHER_MACINTR_PFRI_BITWIDTH              1
// Reserved bitfiled (RO) Reset=0
#define ETHER_MACINTR_RESERVED_MASK              0xFFFFFFE0
#define ETHER_MACINTR_RESERVED_SHIFT             5 
#define ETHER_MACINTR_RESERVED_BIT               0x7FFFFFF
#define ETHER_MACINTR_RESERVED_BITWIDTH          27
// MACINTENR Register
#define ETHER_MACINTENR_OFS                      0x00001118
// FCI bitfiled (RW) Reset=0
#define ETHER_MACINTENR_FCI_MASK                 0x1
#define ETHER_MACINTENR_FCI_SHIFT                0 
#define ETHER_MACINTENR_FCI_BIT                  0x1
#define ETHER_MACINTENR_FCI_BITWIDTH             1
// Reserved2 bitfiled (RO) Reset=0
#define ETHER_MACINTENR_RESERVED2_MASK           0xE
#define ETHER_MACINTENR_RESERVED2_SHIFT          1 
#define ETHER_MACINTENR_RESERVED2_BIT            0x7
#define ETHER_MACINTENR_RESERVED2_BITWIDTH       3
// PFRI bitfiled (RW) Reset=0
#define ETHER_MACINTENR_PFRI_MASK                0x10
#define ETHER_MACINTENR_PFRI_SHIFT               4 
#define ETHER_MACINTENR_PFRI_BIT                 0x1
#define ETHER_MACINTENR_PFRI_BITWIDTH            1
// Reserved bitfiled (RO) Reset=0
#define ETHER_MACINTENR_RESERVED_MASK            0xFFFFFFE0
#define ETHER_MACINTENR_RESERVED_SHIFT           5 
#define ETHER_MACINTENR_RESERVED_BIT             0x7FFFFFF
#define ETHER_MACINTENR_RESERVED_BITWIDTH        27
// PHYINTR Register
#define ETHER_PHYINTR_OFS                        0x0000112C
// PHYIP bitfiled (RW) Reset=0
#define ETHER_PHYINTR_PHYIP_MASK                 0x1
#define ETHER_PHYINTR_PHYIP_SHIFT                0 
#define ETHER_PHYINTR_PHYIP_BIT                  0x1
#define ETHER_PHYINTR_PHYIP_BITWIDTH             1
// Reserved bitfiled (RO) Reset=0
#define ETHER_PHYINTR_RESERVED_MASK              0xFFFFFFFE
#define ETHER_PHYINTR_RESERVED_SHIFT             1 
#define ETHER_PHYINTR_RESERVED_BIT               0x7FFFFFFF
#define ETHER_PHYINTR_RESERVED_BITWIDTH          31
// RGIBSR Register
#define ETHER_RGIBSR_OFS                         0x00001134
// Reserved bitfiled (RO) Reset=0
#define ETHER_RGIBSR_RESERVED_MASK               0xFFFFFFFF
#define ETHER_RGIBSR_RESERVED_SHIFT              0 
#define ETHER_RGIBSR_RESERVED_BIT                0xFFFFFFFF
#define ETHER_RGIBSR_RESERVED_BITWIDTH           32
// MACSTSR Register
#define ETHER_MACSTSR_OFS                        0x00001138
// Reserved2 bitfiled (RO) Reset=0
#define ETHER_MACSTSR_RESERVED2_MASK             0x1
#define ETHER_MACSTSR_RESERVED2_SHIFT            0 
#define ETHER_MACSTSR_RESERVED2_BIT              0x1
#define ETHER_MACSTSR_RESERVED2_BITWIDTH         1
// DUPLEX bitfiled (RO) Reset=0
#define ETHER_MACSTSR_DUPLEX_MASK                0x2
#define ETHER_MACSTSR_DUPLEX_SHIFT               1 
#define ETHER_MACSTSR_DUPLEX_BIT                 0x1
#define ETHER_MACSTSR_DUPLEX_BITWIDTH            1
// SPEED bitfiled (RO) Reset=0
#define ETHER_MACSTSR_SPEED_MASK                 0xC
#define ETHER_MACSTSR_SPEED_SHIFT                2 
#define ETHER_MACSTSR_SPEED_BIT                  0x3
#define ETHER_MACSTSR_SPEED_BITWIDTH             2
// Reserved bitfiled (RO) Reset=0
#define ETHER_MACSTSR_RESERVED_MASK              0xFFFFFFF0
#define ETHER_MACSTSR_RESERVED_SHIFT             4 
#define ETHER_MACSTSR_RESERVED_BIT               0xFFFFFFF
#define ETHER_MACSTSR_RESERVED_BITWIDTH          28
// PHYIFR Register
#define ETHER_PHYIFR_OFS                         0x00001140
// SEL_PHYIF bitfiled (RW) Reset=1
#define ETHER_PHYIFR_SEL_PHYIF_MASK              0x1
#define ETHER_PHYIFR_SEL_PHYIF_SHIFT             0 
#define ETHER_PHYIFR_SEL_PHYIF_BIT               0x1
#define ETHER_PHYIFR_SEL_PHYIF_BITWIDTH          1
// Reserved bitfiled (RO) Reset=0
#define ETHER_PHYIFR_RESERVED_MASK               0xFFFE
#define ETHER_PHYIFR_RESERVED_SHIFT              1 
#define ETHER_PHYIFR_RESERVED_BIT                0x7FFF
#define ETHER_PHYIFR_RESERVED_BITWIDTH           15
// CYC_CLKSW bitfiled (RW) Reset=1111111111111111
#define ETHER_PHYIFR_CYC_CLKSW_MASK              0xFFFF0000
#define ETHER_PHYIFR_CYC_CLKSW_SHIFT             16 
#define ETHER_PHYIFR_CYC_CLKSW_BIT               0xFFFF
#define ETHER_PHYIFR_CYC_CLKSW_BITWIDTH          16
// APFTPR Register
#define ETHER_APFTPR_OFS                         0x00001154
// APFTP bitfiled (RW) Reset=0
#define ETHER_APFTPR_APFTP_MASK                  0xFFFF
#define ETHER_APFTPR_APFTP_SHIFT                 0 
#define ETHER_APFTPR_APFTP_BIT                   0xFFFF
#define ETHER_APFTPR_APFTP_BITWIDTH              16
// Reserved bitfiled (RO) Reset=0
#define ETHER_APFTPR_RESERVED_MASK               0xFFFF0000
#define ETHER_APFTPR_RESERVED_SHIFT              16 
#define ETHER_APFTPR_RESERVED_BIT                0xFFFF
#define ETHER_APFTPR_RESERVED_BITWIDTH           16
// MPFTPR Register
#define ETHER_MPFTPR_OFS                         0x00001158
// MPFTP bitfiled (RW) Reset=0
#define ETHER_MPFTPR_MPFTP_MASK                  0xFFFF
#define ETHER_MPFTPR_MPFTP_SHIFT                 0 
#define ETHER_MPFTPR_MPFTP_BIT                   0xFFFF
#define ETHER_MPFTPR_MPFTP_BITWIDTH              16
// Reserved bitfiled (RO) Reset=0
#define ETHER_MPFTPR_RESERVED_MASK               0xFFFF0000
#define ETHER_MPFTPR_RESERVED_SHIFT              16 
#define ETHER_MPFTPR_RESERVED_BIT                0xFFFF
#define ETHER_MPFTPR_RESERVED_BITWIDTH           16
// PFTXCNTR Register
#define ETHER_PFTXCNTR_OFS                       0x0000115C
// PFTXCNT bitfiled (RO) Reset=0
#define ETHER_PFTXCNTR_PFTXCNT_MASK              0xFFFF
#define ETHER_PFTXCNTR_PFTXCNT_SHIFT             0 
#define ETHER_PFTXCNTR_PFTXCNT_BIT               0xFFFF
#define ETHER_PFTXCNTR_PFTXCNT_BITWIDTH          16
// Reserved bitfiled (RO) Reset=0
#define ETHER_PFTXCNTR_RESERVED_MASK             0xFFFF0000
#define ETHER_PFTXCNTR_RESERVED_SHIFT            16 
#define ETHER_PFTXCNTR_RESERVED_BIT              0xFFFF
#define ETHER_PFTXCNTR_RESERVED_BITWIDTH         16
// PFRXCNTR Register
#define ETHER_PFRXCNTR_OFS                       0x00001160
// PFRXCNT bitfiled (RO) Reset=0
#define ETHER_PFRXCNTR_PFRXCNT_MASK              0xFFFF
#define ETHER_PFRXCNTR_PFRXCNT_SHIFT             0 
#define ETHER_PFRXCNTR_PFRXCNT_BIT               0xFFFF
#define ETHER_PFRXCNTR_PFRXCNT_BITWIDTH          16
// Reserved bitfiled (RO) Reset=0
#define ETHER_PFRXCNTR_RESERVED_MASK             0xFFFF0000
#define ETHER_PFRXCNTR_RESERVED_SHIFT            16 
#define ETHER_PFRXCNTR_RESERVED_BIT              0xFFFF
#define ETHER_PFRXCNTR_RESERVED_BITWIDTH         16
// PFRTLMTR Register
#define ETHER_PFRTLMTR_OFS                       0x00001164
// PFRTLMT bitfiled (RW) Reset=0
#define ETHER_PFRTLMTR_PFRTLMT_MASK              0xFFFF
#define ETHER_PFRTLMTR_PFRTLMT_SHIFT             0 
#define ETHER_PFRTLMTR_PFRTLMT_BIT               0xFFFF
#define ETHER_PFRTLMTR_PFRTLMT_BITWIDTH          16
// Reserved bitfiled (RO) Reset=0
#define ETHER_PFRTLMTR_RESERVED_MASK             0xFFFF0000
#define ETHER_PFRTLMTR_RESERVED_SHIFT            16 
#define ETHER_PFRTLMTR_RESERVED_BIT              0xFFFF
#define ETHER_PFRTLMTR_RESERVED_BITWIDTH         16
// PFRTCNTR Register
#define ETHER_PFRTCNTR_OFS                       0x00001168
// PFRTCNT bitfiled (RO) Reset=0
#define ETHER_PFRTCNTR_PFRTCNT_MASK              0xFFFF
#define ETHER_PFRTCNTR_PFRTCNT_SHIFT             0 
#define ETHER_PFRTCNTR_PFRTCNT_BIT               0xFFFF
#define ETHER_PFRTCNTR_PFRTCNT_BITWIDTH          16
// Reserved bitfiled (RO) Reset=0
#define ETHER_PFRTCNTR_RESERVED_MASK             0xFFFF0000
#define ETHER_PFRTCNTR_RESERVED_SHIFT            16 
#define ETHER_PFRTCNTR_RESERVED_BIT              0xFFFF
#define ETHER_PFRTCNTR_RESERVED_BITWIDTH         16
// MACGCR Register
#define ETHER_MACGCR_OFS                         0x000011B0
// Reserved3 bitfiled (RO) Reset=0
#define ETHER_MACGCR_RESERVED3_MASK              0x1
#define ETHER_MACGCR_RESERVED3_SHIFT             0 
#define ETHER_MACGCR_RESERVED3_BIT               0x1
#define ETHER_MACGCR_RESERVED3_BITWIDTH          1
// BSE bitfiled (RW) Reset=0
#define ETHER_MACGCR_BSE_MASK                    0x2
#define ETHER_MACGCR_BSE_SHIFT                   1 
#define ETHER_MACGCR_BSE_BIT                     0x1
#define ETHER_MACGCR_BSE_BITWIDTH                1
// Reserved2 bitfiled (RO) Reset=0
#define ETHER_MACGCR_RESERVED2_MASK              0xC
#define ETHER_MACGCR_RESERVED2_SHIFT             2 
#define ETHER_MACGCR_RESERVED2_BIT               0x3
#define ETHER_MACGCR_RESERVED2_BITWIDTH          2
// SPEED bitfiled (RW) Reset=0
#define ETHER_MACGCR_SPEED_MASK                  0x30
#define ETHER_MACGCR_SPEED_SHIFT                 4 
#define ETHER_MACGCR_SPEED_BIT                   0x3
#define ETHER_MACGCR_SPEED_BITWIDTH              2
// Reserved bitfiled (RO) Reset=0
#define ETHER_MACGCR_RESERVED_MASK               0xFFFFFFC0
#define ETHER_MACGCR_RESERVED_SHIFT              6 
#define ETHER_MACGCR_RESERVED_BIT                0x3FFFFFF
#define ETHER_MACGCR_RESERVED_BITWIDTH           26
// BSTLMTR Register
#define ETHER_BSTLMTR_OFS                        0x000011B4
// BSTLMT bitfiled (RW) Reset=100000000000
#define ETHER_BSTLMTR_BSTLMT_MASK                0xFFF
#define ETHER_BSTLMTR_BSTLMT_SHIFT               0 
#define ETHER_BSTLMTR_BSTLMT_BIT                 0xFFF
#define ETHER_BSTLMTR_BSTLMT_BITWIDTH            12
// Reserved bitfiled (RO) Reset=0
#define ETHER_BSTLMTR_RESERVED_MASK              0xFFFFF000
#define ETHER_BSTLMTR_RESERVED_SHIFT             12 
#define ETHER_BSTLMTR_RESERVED_BIT               0xFFFFF
#define ETHER_BSTLMTR_RESERVED_BITWIDTH          20
// UMACAR Register
#define ETHER_UMACAR_OFS                         0x000011C0
// UMADR bitfiled (RW) Reset=0
#define ETHER_UMACAR_UMADR_MASK                  0xFFFFFFFF
#define ETHER_UMACAR_UMADR_SHIFT                 0 
#define ETHER_UMACAR_UMADR_BIT                   0xFFFFFFFF
#define ETHER_UMACAR_UMADR_BITWIDTH              32
// LMACAR Register
#define ETHER_LMACAR_OFS                         0x000011C8
// LMADR bitfiled (RW) Reset=0
#define ETHER_LMACAR_LMADR_MASK                  0xFFFF
#define ETHER_LMACAR_LMADR_SHIFT                 0 
#define ETHER_LMACAR_LMADR_BIT                   0xFFFF
#define ETHER_LMACAR_LMADR_BITWIDTH              16
// Reserved bitfiled (RO) Reset=0
#define ETHER_LMACAR_RESERVED_MASK               0xFFFF0000
#define ETHER_LMACAR_RESERVED_SHIFT              16 
#define ETHER_LMACAR_RESERVED_BIT                0xFFFF
#define ETHER_LMACAR_RESERVED_BITWIDTH           16
// TINT1CNTR Register
#define ETHER_TINT1CNTR_OFS                      0x00001300
// TINT1CNT bitfiled (RW) Reset=0
#define ETHER_TINT1CNTR_TINT1CNT_MASK            0xFFFF
#define ETHER_TINT1CNTR_TINT1CNT_SHIFT           0 
#define ETHER_TINT1CNTR_TINT1CNT_BIT             0xFFFF
#define ETHER_TINT1CNTR_TINT1CNT_BITWIDTH        16
// Reserved bitfiled (RO) Reset=0
#define ETHER_TINT1CNTR_RESERVED_MASK            0xFFFF0000
#define ETHER_TINT1CNTR_RESERVED_SHIFT           16 
#define ETHER_TINT1CNTR_RESERVED_BIT             0xFFFF
#define ETHER_TINT1CNTR_RESERVED_BITWIDTH        16
// TINT2CNTR Register
#define ETHER_TINT2CNTR_OFS                      0x00001308
// TINT2CNT bitfiled (RW) Reset=0
#define ETHER_TINT2CNTR_TINT2CNT_MASK            0xFFFF
#define ETHER_TINT2CNTR_TINT2CNT_SHIFT           0 
#define ETHER_TINT2CNTR_TINT2CNT_BIT             0xFFFF
#define ETHER_TINT2CNTR_TINT2CNT_BITWIDTH        16
// Reserved bitfiled (RO) Reset=0
#define ETHER_TINT2CNTR_RESERVED_MASK            0xFFFF0000
#define ETHER_TINT2CNTR_RESERVED_SHIFT           16 
#define ETHER_TINT2CNTR_RESERVED_BIT             0xFFFF
#define ETHER_TINT2CNTR_RESERVED_BITWIDTH        16
// TINT3CNTR Register
#define ETHER_TINT3CNTR_OFS                      0x00001310
// TINT3CNT bitfiled (RW) Reset=0
#define ETHER_TINT3CNTR_TINT3CNT_MASK            0xFFFF
#define ETHER_TINT3CNTR_TINT3CNT_SHIFT           0 
#define ETHER_TINT3CNTR_TINT3CNT_BIT             0xFFFF
#define ETHER_TINT3CNTR_TINT3CNT_BITWIDTH        16
// Reserved bitfiled (RO) Reset=0
#define ETHER_TINT3CNTR_RESERVED_MASK            0xFFFF0000
#define ETHER_TINT3CNTR_RESERVED_SHIFT           16 
#define ETHER_TINT3CNTR_RESERVED_BIT             0xFFFF
#define ETHER_TINT3CNTR_RESERVED_BITWIDTH        16
// RINT1CNTR Register
#define ETHER_RINT1CNTR_OFS                      0x00001340
// RINT1CNT bitfiled (RW) Reset=0
#define ETHER_RINT1CNTR_RINT1CNT_MASK            0xFFFF
#define ETHER_RINT1CNTR_RINT1CNT_SHIFT           0 
#define ETHER_RINT1CNTR_RINT1CNT_BIT             0xFFFF
#define ETHER_RINT1CNTR_RINT1CNT_BITWIDTH        16
// Reserved bitfiled (RO) Reset=0
#define ETHER_RINT1CNTR_RESERVED_MASK            0xFFFF0000
#define ETHER_RINT1CNTR_RESERVED_SHIFT           16 
#define ETHER_RINT1CNTR_RESERVED_BIT             0xFFFF
#define ETHER_RINT1CNTR_RESERVED_BITWIDTH        16
// RINT2CNTR Register
#define ETHER_RINT2CNTR_OFS                      0x00001348
// RINT2CNT bitfiled (RW) Reset=0
#define ETHER_RINT2CNTR_RINT2CNT_MASK            0xFFFF
#define ETHER_RINT2CNTR_RINT2CNT_SHIFT           0 
#define ETHER_RINT2CNTR_RINT2CNT_BIT             0xFFFF
#define ETHER_RINT2CNTR_RINT2CNT_BITWIDTH        16
// Reserved bitfiled (RO) Reset=0
#define ETHER_RINT2CNTR_RESERVED_MASK            0xFFFF0000
#define ETHER_RINT2CNTR_RESERVED_SHIFT           16 
#define ETHER_RINT2CNTR_RESERVED_BIT             0xFFFF
#define ETHER_RINT2CNTR_RESERVED_BITWIDTH        16
// RINT3CNTR Register
#define ETHER_RINT3CNTR_OFS                      0x00001350
// RINT3CNT bitfiled (RW) Reset=0
#define ETHER_RINT3CNTR_RINT3CNT_MASK            0xFFFF
#define ETHER_RINT3CNTR_RINT3CNT_SHIFT           0 
#define ETHER_RINT3CNTR_RINT3CNT_BIT             0xFFFF
#define ETHER_RINT3CNTR_RINT3CNT_BITWIDTH        16
// Reserved bitfiled (RO) Reset=0
#define ETHER_RINT3CNTR_RESERVED_MASK            0xFFFF0000
#define ETHER_RINT3CNTR_RESERVED_SHIFT           16 
#define ETHER_RINT3CNTR_RESERVED_BIT             0xFFFF
#define ETHER_RINT3CNTR_RESERVED_BITWIDTH        16
// RINT4CNTR Register
#define ETHER_RINT4CNTR_OFS                      0x00001358
// RINT4CNT bitfiled (RW) Reset=0
#define ETHER_RINT4CNTR_RINT4CNT_MASK            0xFFFF
#define ETHER_RINT4CNTR_RINT4CNT_SHIFT           0 
#define ETHER_RINT4CNTR_RINT4CNT_BIT             0xFFFF
#define ETHER_RINT4CNTR_RINT4CNT_BITWIDTH        16
// Reserved bitfiled (RO) Reset=0
#define ETHER_RINT4CNTR_RESERVED_MASK            0xFFFF0000
#define ETHER_RINT4CNTR_RESERVED_SHIFT           16 
#define ETHER_RINT4CNTR_RESERVED_BIT             0xFFFF
#define ETHER_RINT4CNTR_RESERVED_BITWIDTH        16
// RINT5CNTR Register
#define ETHER_RINT5CNTR_OFS                      0x00001360
// RINT5CNT bitfiled (RW) Reset=0
#define ETHER_RINT5CNTR_RINT5CNT_MASK            0xFFFF
#define ETHER_RINT5CNTR_RINT5CNT_SHIFT           0 
#define ETHER_RINT5CNTR_RINT5CNT_BIT             0xFFFF
#define ETHER_RINT5CNTR_RINT5CNT_BITWIDTH        16
// Reserved bitfiled (RO) Reset=0
#define ETHER_RINT5CNTR_RESERVED_MASK            0xFFFF0000
#define ETHER_RINT5CNTR_RESERVED_SHIFT           16 
#define ETHER_RINT5CNTR_RESERVED_BIT             0xFFFF
#define ETHER_RINT5CNTR_RESERVED_BITWIDTH        16
// RINT6CNTR Register
#define ETHER_RINT6CNTR_OFS                      0x00001368
// RINT6CNT bitfiled (RW) Reset=0
#define ETHER_RINT6CNTR_RINT6CNT_MASK            0xFFFF
#define ETHER_RINT6CNTR_RINT6CNT_SHIFT           0 
#define ETHER_RINT6CNTR_RINT6CNT_BIT             0xFFFF
#define ETHER_RINT6CNTR_RINT6CNT_BITWIDTH        16
// Reserved bitfiled (RO) Reset=0
#define ETHER_RINT6CNTR_RESERVED_MASK            0xFFFF0000
#define ETHER_RINT6CNTR_RESERVED_SHIFT           16 
#define ETHER_RINT6CNTR_RESERVED_BIT             0xFFFF
#define ETHER_RINT6CNTR_RESERVED_BITWIDTH        16
// RINT7CNTR Register
#define ETHER_RINT7CNTR_OFS                      0x00001370
// RINT7CNT bitfiled (RW) Reset=0
#define ETHER_RINT7CNTR_RINT7CNT_MASK            0xFFFF
#define ETHER_RINT7CNTR_RINT7CNT_SHIFT           0 
#define ETHER_RINT7CNTR_RINT7CNT_BIT             0xFFFF
#define ETHER_RINT7CNTR_RINT7CNT_BITWIDTH        16
// Reserved bitfiled (RO) Reset=0
#define ETHER_RINT7CNTR_RESERVED_MASK            0xFFFF0000
#define ETHER_RINT7CNTR_RESERVED_SHIFT           16 
#define ETHER_RINT7CNTR_RESERVED_BIT             0xFFFF
#define ETHER_RINT7CNTR_RESERVED_BITWIDTH        16
// RINT8CNTR Register
#define ETHER_RINT8CNTR_OFS                      0x00001378
// RINT8CNT bitfiled (RW) Reset=0
#define ETHER_RINT8CNTR_RINT8CNT_MASK            0xFFFF
#define ETHER_RINT8CNTR_RINT8CNT_SHIFT           0 
#define ETHER_RINT8CNTR_RINT8CNT_BIT             0xFFFF
#define ETHER_RINT8CNTR_RINT8CNT_BITWIDTH        16
// Reserved bitfiled (RO) Reset=0
#define ETHER_RINT8CNTR_RESERVED_MASK            0xFFFF0000
#define ETHER_RINT8CNTR_RESERVED_SHIFT           16 
#define ETHER_RINT8CNTR_RESERVED_BIT             0xFFFF
#define ETHER_RINT8CNTR_RESERVED_BITWIDTH        16
// MDIOSTSR Register
#define ETHER_MDIOSTSR_OFS                       0x00001380
// BSY bitfiled (RO) Reset=0
#define ETHER_MDIOSTSR_BSY_MASK                  0x1
#define ETHER_MDIOSTSR_BSY_SHIFT                 0 
#define ETHER_MDIOSTSR_BSY_BIT                   0x1
#define ETHER_MDIOSTSR_BSY_BITWIDTH              1
// Reserved bitfiled (RO) Reset=0
#define ETHER_MDIOSTSR_RESERVED_MASK             0xFFFFFFFE
#define ETHER_MDIOSTSR_RESERVED_SHIFT            1 
#define ETHER_MDIOSTSR_RESERVED_BIT              0x7FFFFFFF
#define ETHER_MDIOSTSR_RESERVED_BITWIDTH         31
// MDIOCMDR Register
#define ETHER_MDIOCMDR_OFS                       0x00001384
// OP bitfiled (RW) Reset=0
#define ETHER_MDIOCMDR_OP_MASK                   0x3
#define ETHER_MDIOCMDR_OP_SHIFT                  0 
#define ETHER_MDIOCMDR_OP_BIT                    0x3
#define ETHER_MDIOCMDR_OP_BITWIDTH               2
// Reserved bitfiled (RO) Reset=0
#define ETHER_MDIOCMDR_RESERVED_MASK             0xFFFFFFFC
#define ETHER_MDIOCMDR_RESERVED_SHIFT            2 
#define ETHER_MDIOCMDR_RESERVED_BIT              0x3FFFFFFF
#define ETHER_MDIOCMDR_RESERVED_BITWIDTH         30
// MDIOADRR Register
#define ETHER_MDIOADRR_OFS                       0x00001388
// PHYREG bitfiled (RW) Reset=0
#define ETHER_MDIOADRR_PHYREG_MASK               0x1F
#define ETHER_MDIOADRR_PHYREG_SHIFT              0 
#define ETHER_MDIOADRR_PHYREG_BIT                0x1F
#define ETHER_MDIOADRR_PHYREG_BITWIDTH           5
// PHYADR bitfiled (RW) Reset=0
#define ETHER_MDIOADRR_PHYADR_MASK               0x3E0
#define ETHER_MDIOADRR_PHYADR_SHIFT              5 
#define ETHER_MDIOADRR_PHYADR_BIT                0x1F
#define ETHER_MDIOADRR_PHYADR_BITWIDTH           5
// Reserved bitfiled (RO) Reset=0
#define ETHER_MDIOADRR_RESERVED_MASK             0xFFFFFC00
#define ETHER_MDIOADRR_RESERVED_SHIFT            10 
#define ETHER_MDIOADRR_RESERVED_BIT              0x3FFFFF
#define ETHER_MDIOADRR_RESERVED_BITWIDTH         22
// MDIODATR Register
#define ETHER_MDIODATR_OFS                       0x0000138C
// PHYDATA bitfiled (RW) Reset=0
#define ETHER_MDIODATR_PHYDATA_MASK              0xFFFF
#define ETHER_MDIODATR_PHYDATA_SHIFT             0 
#define ETHER_MDIODATR_PHYDATA_BIT               0xFFFF
#define ETHER_MDIODATR_PHYDATA_BITWIDTH          16
// Reserved bitfiled (RO) Reset=0
#define ETHER_MDIODATR_RESERVED_MASK             0xFFFF0000
#define ETHER_MDIODATR_RESERVED_SHIFT            16 
#define ETHER_MDIODATR_RESERVED_BIT              0xFFFF
#define ETHER_MDIODATR_RESERVED_BITWIDTH         16
// MDIOCYCR Register
#define ETHER_MDIOCYCR_OFS                       0x00001390
// CYCOCLK bitfiled (RW) Reset=11111111
#define ETHER_MDIOCYCR_CYCOCLK_MASK              0xFF
#define ETHER_MDIOCYCR_CYCOCLK_SHIFT             0 
#define ETHER_MDIOCYCR_CYCOCLK_BIT               0xFF
#define ETHER_MDIOCYCR_CYCOCLK_BITWIDTH          8
// Reserved bitfiled (RO) Reset=0
#define ETHER_MDIOCYCR_RESERVED_MASK             0xFFFFFF00
#define ETHER_MDIOCYCR_RESERVED_SHIFT            8 
#define ETHER_MDIOCYCR_RESERVED_BIT              0xFFFFFF
#define ETHER_MDIOCYCR_RESERVED_BITWIDTH         24
// DESCCR Register
#define ETHER_DESCCR_OFS                         0x00001400
// ENR bitfiled (RW) Reset=0
#define ETHER_DESCCR_ENR_MASK                    0x1
#define ETHER_DESCCR_ENR_SHIFT                   0 
#define ETHER_DESCCR_ENR_BIT                     0x1
#define ETHER_DESCCR_ENR_BITWIDTH                1
// ENT bitfiled (RW) Reset=0
#define ETHER_DESCCR_ENT_MASK                    0x2
#define ETHER_DESCCR_ENT_SHIFT                   1 
#define ETHER_DESCCR_ENT_BIT                     0x1
#define ETHER_DESCCR_ENT_BITWIDTH                1
// Reserved bitfiled (RO) Reset=0
#define ETHER_DESCCR_RESERVED_MASK               0xFFFFFFFC
#define ETHER_DESCCR_RESERVED_SHIFT              2 
#define ETHER_DESCCR_RESERVED_BIT                0x3FFFFFFF
#define ETHER_DESCCR_RESERVED_BITWIDTH           30
// DTXSPAR Register
#define ETHER_DTXSPAR_OFS                        0x00001410
// Reserved bitfiled (RO) Reset=0
#define ETHER_DTXSPAR_RESERVED_MASK              0xF
#define ETHER_DTXSPAR_RESERVED_SHIFT             0 
#define ETHER_DTXSPAR_RESERVED_BIT               0xF
#define ETHER_DTXSPAR_RESERVED_BITWIDTH          4
// DTXSPA bitfiled (RW) Reset=0
#define ETHER_DTXSPAR_DTXSPA_MASK                0xFFFFFFF0
#define ETHER_DTXSPAR_DTXSPA_SHIFT               4 
#define ETHER_DTXSPAR_DTXSPA_BIT                 0xFFFFFFF
#define ETHER_DTXSPAR_DTXSPA_BITWIDTH            28
// DTXCPAR Register
#define ETHER_DTXCPAR_OFS                        0x00001414
// Reserved bitfiled (RO) Reset=0
#define ETHER_DTXCPAR_RESERVED_MASK              0xF
#define ETHER_DTXCPAR_RESERVED_SHIFT             0 
#define ETHER_DTXCPAR_RESERVED_BIT               0xF
#define ETHER_DTXCPAR_RESERVED_BITWIDTH          4
// DTXCPA bitfiled (RW) Reset=0
#define ETHER_DTXCPAR_DTXCPA_MASK                0xFFFFFFF0
#define ETHER_DTXCPAR_DTXCPA_SHIFT               4 
#define ETHER_DTXCPAR_DTXCPA_BIT                 0xFFFFFFF
#define ETHER_DTXCPAR_DTXCPA_BITWIDTH            28
// DTXLPAR Register
#define ETHER_DTXLPAR_OFS                        0x00001418
// Reserved bitfiled (RO) Reset=0
#define ETHER_DTXLPAR_RESERVED_MASK              0xF
#define ETHER_DTXLPAR_RESERVED_SHIFT             0 
#define ETHER_DTXLPAR_RESERVED_BIT               0xF
#define ETHER_DTXLPAR_RESERVED_BITWIDTH          4
// DTXLPA bitfiled (RW) Reset=0
#define ETHER_DTXLPAR_DTXLPA_MASK                0xFFFFFFF0
#define ETHER_DTXLPAR_DTXLPA_SHIFT               4 
#define ETHER_DTXLPAR_DTXLPA_BIT                 0xFFFFFFF
#define ETHER_DTXLPAR_DTXLPA_BITWIDTH            28
// DTXDLR Register
#define ETHER_DTXDLR_OFS                         0x0000141C
// DTXDL bitfiled (RW) Reset=0
#define ETHER_DTXDLR_DTXDL_MASK                  0x1
#define ETHER_DTXDLR_DTXDL_SHIFT                 0 
#define ETHER_DTXDLR_DTXDL_BIT                   0x1
#define ETHER_DTXDLR_DTXDL_BITWIDTH              1
// Reserved bitfiled (RO) Reset=0
#define ETHER_DTXDLR_RESERVED_MASK               0xFFFFFFFE
#define ETHER_DTXDLR_RESERVED_SHIFT              1 
#define ETHER_DTXDLR_RESERVED_BIT                0x7FFFFFFF
#define ETHER_DTXDLR_RESERVED_BITWIDTH           31
// DRXSPAR Register
#define ETHER_DRXSPAR_OFS                        0x00001430
// Reserved bitfiled (RO) Reset=0
#define ETHER_DRXSPAR_RESERVED_MASK              0xF
#define ETHER_DRXSPAR_RESERVED_SHIFT             0 
#define ETHER_DRXSPAR_RESERVED_BIT               0xF
#define ETHER_DRXSPAR_RESERVED_BITWIDTH          4
// DRXSPA bitfiled (RW) Reset=0
#define ETHER_DRXSPAR_DRXSPA_MASK                0xFFFFFFF0
#define ETHER_DRXSPAR_DRXSPA_SHIFT               4 
#define ETHER_DRXSPAR_DRXSPA_BIT                 0xFFFFFFF
#define ETHER_DRXSPAR_DRXSPA_BITWIDTH            28
// DRXCPAR Register
#define ETHER_DRXCPAR_OFS                        0x00001434
// Reserved bitfiled (RO) Reset=0
#define ETHER_DRXCPAR_RESERVED_MASK              0xF
#define ETHER_DRXCPAR_RESERVED_SHIFT             0 
#define ETHER_DRXCPAR_RESERVED_BIT               0xF
#define ETHER_DRXCPAR_RESERVED_BITWIDTH          4
// DRXCPA bitfiled (RW) Reset=0
#define ETHER_DRXCPAR_DRXCPA_MASK                0xFFFFFFF0
#define ETHER_DRXCPAR_DRXCPA_SHIFT               4 
#define ETHER_DRXCPAR_DRXCPA_BIT                 0xFFFFFFF
#define ETHER_DRXCPAR_DRXCPA_BITWIDTH            28
// DRXLPAR Register
#define ETHER_DRXLPAR_OFS                        0x00001438
// Reserved bitfiled (RO) Reset=0
#define ETHER_DRXLPAR_RESERVED_MASK              0xF
#define ETHER_DRXLPAR_RESERVED_SHIFT             0 
#define ETHER_DRXLPAR_RESERVED_BIT               0xF
#define ETHER_DRXLPAR_RESERVED_BITWIDTH          4
// DRXLPA bitfiled (RW) Reset=0
#define ETHER_DRXLPAR_DRXLPA_MASK                0xFFFFFFF0
#define ETHER_DRXLPAR_DRXLPA_SHIFT               4 
#define ETHER_DRXLPAR_DRXLPA_BIT                 0xFFFFFFF
#define ETHER_DRXLPAR_DRXLPA_BITWIDTH            28
// DRXDLR Register
#define ETHER_DRXDLR_OFS                         0x0000143C
// DTXDL bitfiled (RW) Reset=0
#define ETHER_DRXDLR_DTXDL_MASK                  0x1
#define ETHER_DRXDLR_DTXDL_SHIFT                 0 
#define ETHER_DRXDLR_DTXDL_BIT                   0x1
#define ETHER_DRXDLR_DTXDL_BITWIDTH              1
// Reserved bitfiled (RO) Reset=0
#define ETHER_DRXDLR_RESERVED_MASK               0xFFFFFFFE
#define ETHER_DRXDLR_RESERVED_SHIFT              1 
#define ETHER_DRXDLR_RESERVED_BIT                0x7FFFFFFF
#define ETHER_DRXDLR_RESERVED_BITWIDTH           31
// FMAR00HR Register
#define ETHER_FMAR00HR_OFS                       0x00001500
// FUMADR bitfiled (RW) Reset=0
#define ETHER_FMAR00HR_FUMADR_MASK               0xFFFFFFFF
#define ETHER_FMAR00HR_FUMADR_SHIFT              0 
#define ETHER_FMAR00HR_FUMADR_BIT                0xFFFFFFFF
#define ETHER_FMAR00HR_FUMADR_BITWIDTH           32
// FMAR00LR Register
#define ETHER_FMAR00LR_OFS                       0x00001504
// FLMADR bitfiled (RW) Reset=0
#define ETHER_FMAR00LR_FLMADR_MASK               0xFFFF
#define ETHER_FMAR00LR_FLMADR_SHIFT              0 
#define ETHER_FMAR00LR_FLMADR_BIT                0xFFFF
#define ETHER_FMAR00LR_FLMADR_BITWIDTH           16
// Reserved bitfiled (RO) Reset=0
#define ETHER_FMAR00LR_RESERVED_MASK             0xFFFF0000
#define ETHER_FMAR00LR_RESERVED_SHIFT            16 
#define ETHER_FMAR00LR_RESERVED_BIT              0xFFFF
#define ETHER_FMAR00LR_RESERVED_BITWIDTH         16
// FMAR01HR Register
#define ETHER_FMAR01HR_OFS                       0x00001508
// FUMADR bitfiled (RW) Reset=0
#define ETHER_FMAR01HR_FUMADR_MASK               0xFFFFFFFF
#define ETHER_FMAR01HR_FUMADR_SHIFT              0 
#define ETHER_FMAR01HR_FUMADR_BIT                0xFFFFFFFF
#define ETHER_FMAR01HR_FUMADR_BITWIDTH           32
// FMAR01LR Register
#define ETHER_FMAR01LR_OFS                       0x0000150C
// FLMADR bitfiled (RW) Reset=0
#define ETHER_FMAR01LR_FLMADR_MASK               0xFFFF
#define ETHER_FMAR01LR_FLMADR_SHIFT              0 
#define ETHER_FMAR01LR_FLMADR_BIT                0xFFFF
#define ETHER_FMAR01LR_FLMADR_BITWIDTH           16
// Reserved bitfiled (RO) Reset=0
#define ETHER_FMAR01LR_RESERVED_MASK             0xFFFF0000
#define ETHER_FMAR01LR_RESERVED_SHIFT            16 
#define ETHER_FMAR01LR_RESERVED_BIT              0xFFFF
#define ETHER_FMAR01LR_RESERVED_BITWIDTH         16
// FMAR02HR Register
#define ETHER_FMAR02HR_OFS                       0x00001510
// FUMADR bitfiled (RW) Reset=0
#define ETHER_FMAR02HR_FUMADR_MASK               0xFFFFFFFF
#define ETHER_FMAR02HR_FUMADR_SHIFT              0 
#define ETHER_FMAR02HR_FUMADR_BIT                0xFFFFFFFF
#define ETHER_FMAR02HR_FUMADR_BITWIDTH           32
// FMAR02LR Register
#define ETHER_FMAR02LR_OFS                       0x00001514
// FLMADR bitfiled (RW) Reset=0
#define ETHER_FMAR02LR_FLMADR_MASK               0xFFFF
#define ETHER_FMAR02LR_FLMADR_SHIFT              0 
#define ETHER_FMAR02LR_FLMADR_BIT                0xFFFF
#define ETHER_FMAR02LR_FLMADR_BITWIDTH           16
// Reserved bitfiled (RO) Reset=0
#define ETHER_FMAR02LR_RESERVED_MASK             0xFFFF0000
#define ETHER_FMAR02LR_RESERVED_SHIFT            16 
#define ETHER_FMAR02LR_RESERVED_BIT              0xFFFF
#define ETHER_FMAR02LR_RESERVED_BITWIDTH         16
// FMAR03HR Register
#define ETHER_FMAR03HR_OFS                       0x00001518
// FUMADR bitfiled (RW) Reset=0
#define ETHER_FMAR03HR_FUMADR_MASK               0xFFFFFFFF
#define ETHER_FMAR03HR_FUMADR_SHIFT              0 
#define ETHER_FMAR03HR_FUMADR_BIT                0xFFFFFFFF
#define ETHER_FMAR03HR_FUMADR_BITWIDTH           32
// FMAR03LR Register
#define ETHER_FMAR03LR_OFS                       0x0000151C
// FLMADR bitfiled (RW) Reset=0
#define ETHER_FMAR03LR_FLMADR_MASK               0xFFFF
#define ETHER_FMAR03LR_FLMADR_SHIFT              0 
#define ETHER_FMAR03LR_FLMADR_BIT                0xFFFF
#define ETHER_FMAR03LR_FLMADR_BITWIDTH           16
// Reserved bitfiled (RO) Reset=0
#define ETHER_FMAR03LR_RESERVED_MASK             0xFFFF0000
#define ETHER_FMAR03LR_RESERVED_SHIFT            16 
#define ETHER_FMAR03LR_RESERVED_BIT              0xFFFF
#define ETHER_FMAR03LR_RESERVED_BITWIDTH         16
// FMAR04HR Register
#define ETHER_FMAR04HR_OFS                       0x00001520
// FUMADR bitfiled (RW) Reset=0
#define ETHER_FMAR04HR_FUMADR_MASK               0xFFFFFFFF
#define ETHER_FMAR04HR_FUMADR_SHIFT              0 
#define ETHER_FMAR04HR_FUMADR_BIT                0xFFFFFFFF
#define ETHER_FMAR04HR_FUMADR_BITWIDTH           32
// FMAR04LR Register
#define ETHER_FMAR04LR_OFS                       0x00001524
// FLMADR bitfiled (RW) Reset=0
#define ETHER_FMAR04LR_FLMADR_MASK               0xFFFF
#define ETHER_FMAR04LR_FLMADR_SHIFT              0 
#define ETHER_FMAR04LR_FLMADR_BIT                0xFFFF
#define ETHER_FMAR04LR_FLMADR_BITWIDTH           16
// Reserved bitfiled (RO) Reset=0
#define ETHER_FMAR04LR_RESERVED_MASK             0xFFFF0000
#define ETHER_FMAR04LR_RESERVED_SHIFT            16 
#define ETHER_FMAR04LR_RESERVED_BIT              0xFFFF
#define ETHER_FMAR04LR_RESERVED_BITWIDTH         16
// FMAR05HR Register
#define ETHER_FMAR05HR_OFS                       0x00001528
// FUMADR bitfiled (RW) Reset=0
#define ETHER_FMAR05HR_FUMADR_MASK               0xFFFFFFFF
#define ETHER_FMAR05HR_FUMADR_SHIFT              0 
#define ETHER_FMAR05HR_FUMADR_BIT                0xFFFFFFFF
#define ETHER_FMAR05HR_FUMADR_BITWIDTH           32
// FMAR05LR Register
#define ETHER_FMAR05LR_OFS                       0x0000152C
// FLMADR bitfiled (RW) Reset=0
#define ETHER_FMAR05LR_FLMADR_MASK               0xFFFF
#define ETHER_FMAR05LR_FLMADR_SHIFT              0 
#define ETHER_FMAR05LR_FLMADR_BIT                0xFFFF
#define ETHER_FMAR05LR_FLMADR_BITWIDTH           16
// Reserved bitfiled (RO) Reset=0
#define ETHER_FMAR05LR_RESERVED_MASK             0xFFFF0000
#define ETHER_FMAR05LR_RESERVED_SHIFT            16 
#define ETHER_FMAR05LR_RESERVED_BIT              0xFFFF
#define ETHER_FMAR05LR_RESERVED_BITWIDTH         16
// FMAR06HR Register
#define ETHER_FMAR06HR_OFS                       0x00001530
// FUMADR bitfiled (RW) Reset=0
#define ETHER_FMAR06HR_FUMADR_MASK               0xFFFFFFFF
#define ETHER_FMAR06HR_FUMADR_SHIFT              0 
#define ETHER_FMAR06HR_FUMADR_BIT                0xFFFFFFFF
#define ETHER_FMAR06HR_FUMADR_BITWIDTH           32
// FMAR06LR Register
#define ETHER_FMAR06LR_OFS                       0x00001534
// FLMADR bitfiled (RW) Reset=0
#define ETHER_FMAR06LR_FLMADR_MASK               0xFFFF
#define ETHER_FMAR06LR_FLMADR_SHIFT              0 
#define ETHER_FMAR06LR_FLMADR_BIT                0xFFFF
#define ETHER_FMAR06LR_FLMADR_BITWIDTH           16
// Reserved bitfiled (RO) Reset=0
#define ETHER_FMAR06LR_RESERVED_MASK             0xFFFF0000
#define ETHER_FMAR06LR_RESERVED_SHIFT            16 
#define ETHER_FMAR06LR_RESERVED_BIT              0xFFFF
#define ETHER_FMAR06LR_RESERVED_BITWIDTH         16
// FMAR07HR Register
#define ETHER_FMAR07HR_OFS                       0x00001538
// FUMADR bitfiled (RW) Reset=0
#define ETHER_FMAR07HR_FUMADR_MASK               0xFFFFFFFF
#define ETHER_FMAR07HR_FUMADR_SHIFT              0 
#define ETHER_FMAR07HR_FUMADR_BIT                0xFFFFFFFF
#define ETHER_FMAR07HR_FUMADR_BITWIDTH           32
// FMAR07LR Register
#define ETHER_FMAR07LR_OFS                       0x0000153C
// FLMADR bitfiled (RW) Reset=0
#define ETHER_FMAR07LR_FLMADR_MASK               0xFFFF
#define ETHER_FMAR07LR_FLMADR_SHIFT              0 
#define ETHER_FMAR07LR_FLMADR_BIT                0xFFFF
#define ETHER_FMAR07LR_FLMADR_BITWIDTH           16
// Reserved bitfiled (RO) Reset=0
#define ETHER_FMAR07LR_RESERVED_MASK             0xFFFF0000
#define ETHER_FMAR07LR_RESERVED_SHIFT            16 
#define ETHER_FMAR07LR_RESERVED_BIT              0xFFFF
#define ETHER_FMAR07LR_RESERVED_BITWIDTH         16
// FLTCR Register
#define ETHER_FLTCR_OFS                          0x000015E0
// ENBL bitfiled (RW) Reset=0
#define ETHER_FLTCR_ENBL_MASK                    0x1
#define ETHER_FLTCR_ENBL_SHIFT                   0 
#define ETHER_FLTCR_ENBL_BIT                     0x1
#define ETHER_FLTCR_ENBL_BITWIDTH                1
// Reserved2 bitfiled (RO) Reset=0
#define ETHER_FLTCR_RESERVED2_MASK               0xE
#define ETHER_FLTCR_RESERVED2_SHIFT              1 
#define ETHER_FLTCR_RESERVED2_BIT                0x7
#define ETHER_FLTCR_RESERVED2_BITWIDTH           3
// MODE bitfiled (RW) Reset=0
#define ETHER_FLTCR_MODE_MASK                    0x10
#define ETHER_FLTCR_MODE_SHIFT                   4 
#define ETHER_FLTCR_MODE_BIT                     0x1
#define ETHER_FLTCR_MODE_BITWIDTH                1
// Reserved bitfiled (RO) Reset=0
#define ETHER_FLTCR_RESERVED_MASK                0xFFFFFFE0
#define ETHER_FLTCR_RESERVED_SHIFT               5 
#define ETHER_FLTCR_RESERVED_BIT                 0x7FFFFFF
#define ETHER_FLTCR_RESERVED_BITWIDTH            27
// FLTENTR Register
#define ETHER_FLTENTR_OFS                        0x000015E4
// ENT_EN bitfiled (RW) Reset=0
#define ETHER_FLTENTR_ENT_EN_MASK                0xFF
#define ETHER_FLTENTR_ENT_EN_SHIFT               0 
#define ETHER_FLTENTR_ENT_EN_BIT                 0xFF
#define ETHER_FLTENTR_ENT_EN_BITWIDTH            8
// Reserved2 bitfiled (RO) Reset=0
#define ETHER_FLTENTR_RESERVED2_MASK             0xFF00
#define ETHER_FLTENTR_RESERVED2_SHIFT            8 
#define ETHER_FLTENTR_RESERVED2_BIT              0xFF
#define ETHER_FLTENTR_RESERVED2_BITWIDTH         8
// ENT_EN_WE bitfiled (RO) Reset=0
#define ETHER_FLTENTR_ENT_EN_WE_MASK             0xFF0000
#define ETHER_FLTENTR_ENT_EN_WE_SHIFT            16 
#define ETHER_FLTENTR_ENT_EN_WE_BIT              0xFF
#define ETHER_FLTENTR_ENT_EN_WE_BITWIDTH         8
// Reserved bitfiled (RO) Reset=0
#define ETHER_FLTENTR_RESERVED_MASK              0xFF000000
#define ETHER_FLTENTR_RESERVED_SHIFT             24 
#define ETHER_FLTENTR_RESERVED_BIT               0xFF
#define ETHER_FLTENTR_RESERVED_BITWIDTH          8
// FLTFWCNTR Register
#define ETHER_FLTFWCNTR_OFS                      0x000015F0
// FORWARD bitfiled (RW) Reset=0
#define ETHER_FLTFWCNTR_FORWARD_MASK             0xFFFF
#define ETHER_FLTFWCNTR_FORWARD_SHIFT            0 
#define ETHER_FLTFWCNTR_FORWARD_BIT              0xFFFF
#define ETHER_FLTFWCNTR_FORWARD_BITWIDTH         16
// Reserved bitfiled (RO) Reset=0
#define ETHER_FLTFWCNTR_RESERVED_MASK            0xFFFF0000
#define ETHER_FLTFWCNTR_RESERVED_SHIFT           16 
#define ETHER_FLTFWCNTR_RESERVED_BIT             0xFFFF
#define ETHER_FLTFWCNTR_RESERVED_BITWIDTH        16
// FLTDRCNTR Register
#define ETHER_FLTDRCNTR_OFS                      0x000015F4
// DROP bitfiled (RW) Reset=0
#define ETHER_FLTDRCNTR_DROP_MASK                0xFFFF
#define ETHER_FLTDRCNTR_DROP_SHIFT               0 
#define ETHER_FLTDRCNTR_DROP_BIT                 0xFFFF
#define ETHER_FLTDRCNTR_DROP_BITWIDTH            16
// Reserved bitfiled (RO) Reset=0
#define ETHER_FLTDRCNTR_RESERVED_MASK            0xFFFF0000
#define ETHER_FLTDRCNTR_RESERVED_SHIFT           16 
#define ETHER_FLTDRCNTR_RESERVED_BIT             0xFFFF
#define ETHER_FLTDRCNTR_RESERVED_BITWIDTH        16

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _ETHER_REG_DEF_H */
