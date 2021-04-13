/*
 * arch/arm/mach-tz2000/include/mach/regs/lcdc_reg_def.h
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

#ifndef _LCDC_REG_DEF_H
#define _LCDC_REG_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

// GDCDCR_L Register
#define LCDC_GDCDCR_L_OFS                        0x00000000
// PHDISP bitfiled (RW) Reset=1
#define LCDC_GDCDCR_L_PHDISP_MASK                0x1
#define LCDC_GDCDCR_L_PHDISP_SHIFT               0 
#define LCDC_GDCDCR_L_PHDISP_BIT                 0x1
#define LCDC_GDCDCR_L_PHDISP_BITWIDTH            1
// PHSYNC bitfiled (RW) Reset=0
#define LCDC_GDCDCR_L_PHSYNC_MASK                0x2
#define LCDC_GDCDCR_L_PHSYNC_SHIFT               1 
#define LCDC_GDCDCR_L_PHSYNC_BIT                 0x1
#define LCDC_GDCDCR_L_PHSYNC_BITWIDTH            1
// PVSYNC bitfiled (RW) Reset=0
#define LCDC_GDCDCR_L_PVSYNC_MASK                0x4
#define LCDC_GDCDCR_L_PVSYNC_SHIFT               2 
#define LCDC_GDCDCR_L_PVSYNC_BIT                 0x1
#define LCDC_GDCDCR_L_PVSYNC_BITWIDTH            1
// CSYNC bitfiled (RW) Reset=0
#define LCDC_GDCDCR_L_CSYNC_MASK                 0x8
#define LCDC_GDCDCR_L_CSYNC_SHIFT                3 
#define LCDC_GDCDCR_L_CSYNC_BIT                  0x1
#define LCDC_GDCDCR_L_CSYNC_BITWIDTH             1
// EXTSYNC bitfiled (RW) Reset=1
#define LCDC_GDCDCR_L_EXTSYNC_MASK               0x10
#define LCDC_GDCDCR_L_EXTSYNC_SHIFT              4 
#define LCDC_GDCDCR_L_EXTSYNC_BIT                0x1
#define LCDC_GDCDCR_L_EXTSYNC_BITWIDTH           1
// reserved3 bitfiled (RO) Reset=0
#define LCDC_GDCDCR_L_RESERVED3_MASK             0x20
#define LCDC_GDCDCR_L_RESERVED3_SHIFT            5 
#define LCDC_GDCDCR_L_RESERVED3_BIT              0x1
#define LCDC_GDCDCR_L_RESERVED3_BITWIDTH         1
// reserved2 bitfiled (RO) Reset=0
#define LCDC_GDCDCR_L_RESERVED2_MASK             0x40
#define LCDC_GDCDCR_L_RESERVED2_SHIFT            6 
#define LCDC_GDCDCR_L_RESERVED2_BIT              0x1
#define LCDC_GDCDCR_L_RESERVED2_BITWIDTH         1
// VORD bitfiled (RW) Reset=0
#define LCDC_GDCDCR_L_VORD_MASK                  0x80
#define LCDC_GDCDCR_L_VORD_SHIFT                 7 
#define LCDC_GDCDCR_L_VORD_BIT                   0x1
#define LCDC_GDCDCR_L_VORD_BITWIDTH              1
// ARTH bitfiled (RW) Reset=0
#define LCDC_GDCDCR_L_ARTH_MASK                  0x300
#define LCDC_GDCDCR_L_ARTH_SHIFT                 8 
#define LCDC_GDCDCR_L_ARTH_BIT                   0x3
#define LCDC_GDCDCR_L_ARTH_BITWIDTH              2
// ARTHCD bitfiled (RW) Reset=0
#define LCDC_GDCDCR_L_ARTHCD_MASK                0x400
#define LCDC_GDCDCR_L_ARTHCD_SHIFT               10 
#define LCDC_GDCDCR_L_ARTHCD_BIT                 0x1
#define LCDC_GDCDCR_L_ARTHCD_BITWIDTH            1
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCDCR_L_RESERVED_MASK              0x800
#define LCDC_GDCDCR_L_RESERVED_SHIFT             11 
#define LCDC_GDCDCR_L_RESERVED_BIT               0x1
#define LCDC_GDCDCR_L_RESERVED_BITWIDTH          1
// PDC bitfiled (RW) Reset=1
#define LCDC_GDCDCR_L_PDC_MASK                   0x1000
#define LCDC_GDCDCR_L_PDC_SHIFT                  12 
#define LCDC_GDCDCR_L_PDC_BIT                    0x1
#define LCDC_GDCDCR_L_PDC_BITWIDTH               1
// IDC bitfiled (RW) Reset=1
#define LCDC_GDCDCR_L_IDC_MASK                   0x2000
#define LCDC_GDCDCR_L_IDC_SHIFT                  13 
#define LCDC_GDCDCR_L_IDC_BIT                    0x1
#define LCDC_GDCDCR_L_IDC_BITWIDTH               1
// ADBS bitfiled (RW) Reset=0
#define LCDC_GDCDCR_L_ADBS_MASK                  0x4000
#define LCDC_GDCDCR_L_ADBS_SHIFT                 14 
#define LCDC_GDCDCR_L_ADBS_BIT                   0x1
#define LCDC_GDCDCR_L_ADBS_BITWIDTH              1
// FBACT bitfiled (RO) Reset=0
#define LCDC_GDCDCR_L_FBACT_MASK                 0x8000
#define LCDC_GDCDCR_L_FBACT_SHIFT                15 
#define LCDC_GDCDCR_L_FBACT_BIT                  0x1
#define LCDC_GDCDCR_L_FBACT_BITWIDTH             1
// HDISP bitfiled (RO) Reset=0
#define LCDC_GDCDCR_L_HDISP_MASK                 0x10000
#define LCDC_GDCDCR_L_HDISP_SHIFT                16 
#define LCDC_GDCDCR_L_HDISP_BIT                  0x1
#define LCDC_GDCDCR_L_HDISP_BITWIDTH             1
// HSYNC bitfiled (RO) Reset=1
#define LCDC_GDCDCR_L_HSYNC_MASK                 0x20000
#define LCDC_GDCDCR_L_HSYNC_SHIFT                17 
#define LCDC_GDCDCR_L_HSYNC_BIT                  0x1
#define LCDC_GDCDCR_L_HSYNC_BITWIDTH             1
// VSYNC bitfiled (RO) Reset=1
#define LCDC_GDCDCR_L_VSYNC_MASK                 0x40000
#define LCDC_GDCDCR_L_VSYNC_SHIFT                18 
#define LCDC_GDCDCR_L_VSYNC_BIT                  0x1
#define LCDC_GDCDCR_L_VSYNC_BITWIDTH             1
// GBER bitfiled (RW) Reset=0
#define LCDC_GDCDCR_L_GBER_MASK                  0x80000
#define LCDC_GDCDCR_L_GBER_SHIFT                 19 
#define LCDC_GDCDCR_L_GBER_BIT                   0x1
#define LCDC_GDCDCR_L_GBER_BITWIDTH              1
// A16 bitfiled (RW) Reset=0
#define LCDC_GDCDCR_L_A16_MASK                   0x100000
#define LCDC_GDCDCR_L_A16_SHIFT                  20 
#define LCDC_GDCDCR_L_A16_BIT                    0x1
#define LCDC_GDCDCR_L_A16_BITWIDTH               1
// B16 bitfiled (RW) Reset=0
#define LCDC_GDCDCR_L_B16_MASK                   0x200000
#define LCDC_GDCDCR_L_B16_SHIFT                  21 
#define LCDC_GDCDCR_L_B16_BIT                    0x1
#define LCDC_GDCDCR_L_B16_BITWIDTH               1
// C16 bitfiled (RW) Reset=0
#define LCDC_GDCDCR_L_C16_MASK                   0x400000
#define LCDC_GDCDCR_L_C16_SHIFT                  22 
#define LCDC_GDCDCR_L_C16_BIT                    0x1
#define LCDC_GDCDCR_L_C16_BITWIDTH               1
// D16 bitfiled (RW) Reset=0
#define LCDC_GDCDCR_L_D16_MASK                   0x800000
#define LCDC_GDCDCR_L_D16_SHIFT                  23 
#define LCDC_GDCDCR_L_D16_BIT                    0x1
#define LCDC_GDCDCR_L_D16_BITWIDTH               1
// AEN bitfiled (RW) Reset=0
#define LCDC_GDCDCR_L_AEN_MASK                   0x1000000
#define LCDC_GDCDCR_L_AEN_SHIFT                  24 
#define LCDC_GDCDCR_L_AEN_BIT                    0x1
#define LCDC_GDCDCR_L_AEN_BITWIDTH               1
// WAEN bitfiled (RW) Reset=0
#define LCDC_GDCDCR_L_WAEN_MASK                  0x2000000
#define LCDC_GDCDCR_L_WAEN_SHIFT                 25 
#define LCDC_GDCDCR_L_WAEN_BIT                   0x1
#define LCDC_GDCDCR_L_WAEN_BITWIDTH              1
// BEN bitfiled (RW) Reset=0
#define LCDC_GDCDCR_L_BEN_MASK                   0x4000000
#define LCDC_GDCDCR_L_BEN_SHIFT                  26 
#define LCDC_GDCDCR_L_BEN_BIT                    0x1
#define LCDC_GDCDCR_L_BEN_BITWIDTH               1
// WBEN bitfiled (RW) Reset=0
#define LCDC_GDCDCR_L_WBEN_MASK                  0x8000000
#define LCDC_GDCDCR_L_WBEN_SHIFT                 27 
#define LCDC_GDCDCR_L_WBEN_BIT                   0x1
#define LCDC_GDCDCR_L_WBEN_BITWIDTH              1
// CEN bitfiled (RW) Reset=0
#define LCDC_GDCDCR_L_CEN_MASK                   0x10000000
#define LCDC_GDCDCR_L_CEN_SHIFT                  28 
#define LCDC_GDCDCR_L_CEN_BIT                    0x1
#define LCDC_GDCDCR_L_CEN_BITWIDTH               1
// WCEN bitfiled (RW) Reset=0
#define LCDC_GDCDCR_L_WCEN_MASK                  0x20000000
#define LCDC_GDCDCR_L_WCEN_SHIFT                 29 
#define LCDC_GDCDCR_L_WCEN_BIT                   0x1
#define LCDC_GDCDCR_L_WCEN_BITWIDTH              1
// DEN bitfiled (RW) Reset=0
#define LCDC_GDCDCR_L_DEN_MASK                   0x40000000
#define LCDC_GDCDCR_L_DEN_SHIFT                  30 
#define LCDC_GDCDCR_L_DEN_BIT                    0x1
#define LCDC_GDCDCR_L_DEN_BITWIDTH               1
// WDEN bitfiled (RW) Reset=0
#define LCDC_GDCDCR_L_WDEN_MASK                  0x80000000
#define LCDC_GDCDCR_L_WDEN_SHIFT                 31 
#define LCDC_GDCDCR_L_WDEN_BIT                   0x1
#define LCDC_GDCDCR_L_WDEN_BITWIDTH              1
// GDCDCR_U Register
#define LCDC_GDCDCR_U_OFS                        0x00000004
// EEN bitfiled (RW) Reset=0
#define LCDC_GDCDCR_U_EEN_MASK                   0x1
#define LCDC_GDCDCR_U_EEN_SHIFT                  0 
#define LCDC_GDCDCR_U_EEN_BIT                    0x1
#define LCDC_GDCDCR_U_EEN_BITWIDTH               1
// WEEN bitfiled (RW) Reset=0
#define LCDC_GDCDCR_U_WEEN_MASK                  0x2
#define LCDC_GDCDCR_U_WEEN_SHIFT                 1 
#define LCDC_GDCDCR_U_WEEN_BIT                   0x1
#define LCDC_GDCDCR_U_WEEN_BITWIDTH              1
// reserved5 bitfiled (RO) Reset=0
#define LCDC_GDCDCR_U_RESERVED5_MASK             0xC
#define LCDC_GDCDCR_U_RESERVED5_SHIFT            2 
#define LCDC_GDCDCR_U_RESERVED5_BIT              0x3
#define LCDC_GDCDCR_U_RESERVED5_BITWIDTH         2
// E16 bitfiled (RW) Reset=0
#define LCDC_GDCDCR_U_E16_MASK                   0x10
#define LCDC_GDCDCR_U_E16_SHIFT                  4 
#define LCDC_GDCDCR_U_E16_BIT                    0x1
#define LCDC_GDCDCR_U_E16_BITWIDTH               1
// reserved4 bitfiled (RO) Reset=0
#define LCDC_GDCDCR_U_RESERVED4_MASK             0xE0
#define LCDC_GDCDCR_U_RESERVED4_SHIFT            5 
#define LCDC_GDCDCR_U_RESERVED4_BIT              0x7
#define LCDC_GDCDCR_U_RESERVED4_BITWIDTH         3
// CCEN bitfiled (RW) Reset=0
#define LCDC_GDCDCR_U_CCEN_MASK                  0x100
#define LCDC_GDCDCR_U_CCEN_SHIFT                 8 
#define LCDC_GDCDCR_U_CCEN_BIT                   0x1
#define LCDC_GDCDCR_U_CCEN_BITWIDTH              1
// SCCEN bitfiled (RW) Reset=0
#define LCDC_GDCDCR_U_SCCEN_MASK                 0x200
#define LCDC_GDCDCR_U_SCCEN_SHIFT                9 
#define LCDC_GDCDCR_U_SCCEN_BIT                  0x1
#define LCDC_GDCDCR_U_SCCEN_BITWIDTH             1
// SCCM bitfiled (RW) Reset=0
#define LCDC_GDCDCR_U_SCCM_MASK                  0x400
#define LCDC_GDCDCR_U_SCCM_SHIFT                 10 
#define LCDC_GDCDCR_U_SCCM_BIT                   0x1
#define LCDC_GDCDCR_U_SCCM_BITWIDTH              1
// reserved3 bitfiled (RO) Reset=0
#define LCDC_GDCDCR_U_RESERVED3_MASK             0x800
#define LCDC_GDCDCR_U_RESERVED3_SHIFT            11 
#define LCDC_GDCDCR_U_RESERVED3_BIT              0x1
#define LCDC_GDCDCR_U_RESERVED3_BITWIDTH         1
// DITHEN bitfiled (RW) Reset=0
#define LCDC_GDCDCR_U_DITHEN_MASK                0x3000
#define LCDC_GDCDCR_U_DITHEN_SHIFT               12 
#define LCDC_GDCDCR_U_DITHEN_BIT                 0x3
#define LCDC_GDCDCR_U_DITHEN_BITWIDTH            2
// reserved2 bitfiled (RO) Reset=0
#define LCDC_GDCDCR_U_RESERVED2_MASK             0xFC000
#define LCDC_GDCDCR_U_RESERVED2_SHIFT            14 
#define LCDC_GDCDCR_U_RESERVED2_BIT              0x3F
#define LCDC_GDCDCR_U_RESERVED2_BITWIDTH         6
// ARGBEN bitfiled (RW) Reset=0
#define LCDC_GDCDCR_U_ARGBEN_MASK                0x100000
#define LCDC_GDCDCR_U_ARGBEN_SHIFT               20 
#define LCDC_GDCDCR_U_ARGBEN_BIT                 0x1
#define LCDC_GDCDCR_U_ARGBEN_BITWIDTH            1
// LAD bitfiled (RW) Reset=1
#define LCDC_GDCDCR_U_LAD_MASK                   0x200000
#define LCDC_GDCDCR_U_LAD_SHIFT                  21 
#define LCDC_GDCDCR_U_LAD_BIT                    0x1
#define LCDC_GDCDCR_U_LAD_BITWIDTH               1
// UPDREG bitfiled (RW) Reset=1
#define LCDC_GDCDCR_U_UPDREG_MASK                0xC00000
#define LCDC_GDCDCR_U_UPDREG_SHIFT               22 
#define LCDC_GDCDCR_U_UPDREG_BIT                 0x3
#define LCDC_GDCDCR_U_UPDREG_BITWIDTH            2
// GAPEN bitfiled (RW) Reset=0
#define LCDC_GDCDCR_U_GAPEN_MASK                 0x1000000
#define LCDC_GDCDCR_U_GAPEN_SHIFT                24 
#define LCDC_GDCDCR_U_GAPEN_BIT                  0x1
#define LCDC_GDCDCR_U_GAPEN_BITWIDTH             1
// GAPCOL bitfiled (RW) Reset=0
#define LCDC_GDCDCR_U_GAPCOL_MASK                0x2000000
#define LCDC_GDCDCR_U_GAPCOL_SHIFT               25 
#define LCDC_GDCDCR_U_GAPCOL_BIT                 0x1
#define LCDC_GDCDCR_U_GAPCOL_BITWIDTH            1
// GAPACC bitfiled (RO) Reset=0
#define LCDC_GDCDCR_U_GAPACC_MASK                0x4000000
#define LCDC_GDCDCR_U_GAPACC_SHIFT               26 
#define LCDC_GDCDCR_U_GAPACC_BIT                 0x1
#define LCDC_GDCDCR_U_GAPACC_BITWIDTH            1
// GAPSE bitfiled (RW) Reset=0
#define LCDC_GDCDCR_U_GAPSE_MASK                 0x8000000
#define LCDC_GDCDCR_U_GAPSE_SHIFT                27 
#define LCDC_GDCDCR_U_GAPSE_BIT                  0x1
#define LCDC_GDCDCR_U_GAPSE_BITWIDTH             1
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCDCR_U_RESERVED_MASK              0x10000000
#define LCDC_GDCDCR_U_RESERVED_SHIFT             28 
#define LCDC_GDCDCR_U_RESERVED_BIT               0x1
#define LCDC_GDCDCR_U_RESERVED_BITWIDTH          1
// PNLIFON bitfiled (RO) Reset=0
#define LCDC_GDCDCR_U_PNLIFON_MASK               0x20000000
#define LCDC_GDCDCR_U_PNLIFON_SHIFT              29 
#define LCDC_GDCDCR_U_PNLIFON_BIT                0x1
#define LCDC_GDCDCR_U_PNLIFON_BITWIDTH           1
// DISPIFON bitfiled (RO) Reset=1
#define LCDC_GDCDCR_U_DISPIFON_MASK              0x40000000
#define LCDC_GDCDCR_U_DISPIFON_SHIFT             30 
#define LCDC_GDCDCR_U_DISPIFON_BIT               0x1
#define LCDC_GDCDCR_U_DISPIFON_BITWIDTH          1
// GDCON bitfiled (RW) Reset=0
#define LCDC_GDCDCR_U_GDCON_MASK                 0x80000000
#define LCDC_GDCDCR_U_GDCON_SHIFT                31 
#define LCDC_GDCDCR_U_GDCON_BIT                  0x1
#define LCDC_GDCDCR_U_GDCON_BITWIDTH             1
// GDCLARA0_L Register
#define LCDC_GDCLARA0_L_OFS                      0x00000010
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCLARA0_L_RESERVED_MASK            0x1
#define LCDC_GDCLARA0_L_RESERVED_SHIFT           0 
#define LCDC_GDCLARA0_L_RESERVED_BIT             0x1
#define LCDC_GDCLARA0_L_RESERVED_BITWIDTH        1
// SSCROLL bitfiled (RW) Reset=0
#define LCDC_GDCLARA0_L_SSCROLL_MASK             0x6
#define LCDC_GDCLARA0_L_SSCROLL_SHIFT            1 
#define LCDC_GDCLARA0_L_SSCROLL_BIT              0x3
#define LCDC_GDCLARA0_L_SSCROLL_BITWIDTH         2
// SAR bitfiled (RW) Reset=0
#define LCDC_GDCLARA0_L_SAR_MASK                 0xFFFFFFF8
#define LCDC_GDCLARA0_L_SAR_SHIFT                3 
#define LCDC_GDCLARA0_L_SAR_BIT                  0x1FFFFFFF
#define LCDC_GDCLARA0_L_SAR_BITWIDTH             29
// GDCLARA1_L Register
#define LCDC_GDCLARA1_L_OFS                      0x00000018
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCLARA1_L_RESERVED_MASK            0x1
#define LCDC_GDCLARA1_L_RESERVED_SHIFT           0 
#define LCDC_GDCLARA1_L_RESERVED_BIT             0x1
#define LCDC_GDCLARA1_L_RESERVED_BITWIDTH        1
// SSCROLL bitfiled (RW) Reset=0
#define LCDC_GDCLARA1_L_SSCROLL_MASK             0x6
#define LCDC_GDCLARA1_L_SSCROLL_SHIFT            1 
#define LCDC_GDCLARA1_L_SSCROLL_BIT              0x3
#define LCDC_GDCLARA1_L_SSCROLL_BITWIDTH         2
// SAR bitfiled (RW) Reset=0
#define LCDC_GDCLARA1_L_SAR_MASK                 0xFFFFFFF8
#define LCDC_GDCLARA1_L_SAR_SHIFT                3 
#define LCDC_GDCLARA1_L_SAR_BIT                  0x1FFFFFFF
#define LCDC_GDCLARA1_L_SAR_BITWIDTH             29
// GDCWARA_L Register
#define LCDC_GDCWARA_L_OFS                       0x00000020
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCWARA_L_RESERVED_MASK             0x7
#define LCDC_GDCWARA_L_RESERVED_SHIFT            0 
#define LCDC_GDCWARA_L_RESERVED_BIT              0x7
#define LCDC_GDCWARA_L_RESERVED_BITWIDTH         3
// WAR bitfiled (RW) Reset=0
#define LCDC_GDCWARA_L_WAR_MASK                  0xFFFFFFF8
#define LCDC_GDCWARA_L_WAR_SHIFT                 3 
#define LCDC_GDCWARA_L_WAR_BIT                   0x1FFFFFFF
#define LCDC_GDCWARA_L_WAR_BITWIDTH              29
// GDCBGCR_L Register
#define LCDC_GDCBGCR_L_OFS                       0x00000028
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCBGCR_L_RESERVED_MASK             0xFF
#define LCDC_GDCBGCR_L_RESERVED_SHIFT            0 
#define LCDC_GDCBGCR_L_RESERVED_BIT              0xFF
#define LCDC_GDCBGCR_L_RESERVED_BITWIDTH         8
// BGBLUE bitfiled (RW) Reset=0
#define LCDC_GDCBGCR_L_BGBLUE_MASK               0xFF00
#define LCDC_GDCBGCR_L_BGBLUE_SHIFT              8 
#define LCDC_GDCBGCR_L_BGBLUE_BIT                0xFF
#define LCDC_GDCBGCR_L_BGBLUE_BITWIDTH           8
// BGGREEN bitfiled (RW) Reset=0
#define LCDC_GDCBGCR_L_BGGREEN_MASK              0xFF0000
#define LCDC_GDCBGCR_L_BGGREEN_SHIFT             16 
#define LCDC_GDCBGCR_L_BGGREEN_BIT               0xFF
#define LCDC_GDCBGCR_L_BGGREEN_BITWIDTH          8
// BGRED bitfiled (RW) Reset=0
#define LCDC_GDCBGCR_L_BGRED_MASK                0xFF000000
#define LCDC_GDCBGCR_L_BGRED_SHIFT               24 
#define LCDC_GDCBGCR_L_BGRED_BIT                 0xFF
#define LCDC_GDCBGCR_L_BGRED_BITWIDTH            8
// GDCLARB0_L Register
#define LCDC_GDCLARB0_L_OFS                      0x00000030
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCLARB0_L_RESERVED_MASK            0x1
#define LCDC_GDCLARB0_L_RESERVED_SHIFT           0 
#define LCDC_GDCLARB0_L_RESERVED_BIT             0x1
#define LCDC_GDCLARB0_L_RESERVED_BITWIDTH        1
// SSCROLL bitfiled (RW) Reset=0
#define LCDC_GDCLARB0_L_SSCROLL_MASK             0x6
#define LCDC_GDCLARB0_L_SSCROLL_SHIFT            1 
#define LCDC_GDCLARB0_L_SSCROLL_BIT              0x3
#define LCDC_GDCLARB0_L_SSCROLL_BITWIDTH         2
// SAR bitfiled (RW) Reset=0
#define LCDC_GDCLARB0_L_SAR_MASK                 0xFFFFFFF8
#define LCDC_GDCLARB0_L_SAR_SHIFT                3 
#define LCDC_GDCLARB0_L_SAR_BIT                  0x1FFFFFFF
#define LCDC_GDCLARB0_L_SAR_BITWIDTH             29
// GDCLARB1_L Register
#define LCDC_GDCLARB1_L_OFS                      0x00000038
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCLARB1_L_RESERVED_MASK            0x1
#define LCDC_GDCLARB1_L_RESERVED_SHIFT           0 
#define LCDC_GDCLARB1_L_RESERVED_BIT             0x1
#define LCDC_GDCLARB1_L_RESERVED_BITWIDTH        1
// SSCROLL bitfiled (RW) Reset=0
#define LCDC_GDCLARB1_L_SSCROLL_MASK             0x6
#define LCDC_GDCLARB1_L_SSCROLL_SHIFT            1 
#define LCDC_GDCLARB1_L_SSCROLL_BIT              0x3
#define LCDC_GDCLARB1_L_SSCROLL_BITWIDTH         2
// SAR bitfiled (RW) Reset=0
#define LCDC_GDCLARB1_L_SAR_MASK                 0xFFFFFFF8
#define LCDC_GDCLARB1_L_SAR_SHIFT                3 
#define LCDC_GDCLARB1_L_SAR_BIT                  0x1FFFFFFF
#define LCDC_GDCLARB1_L_SAR_BITWIDTH             29
// GDCWARB_L Register
#define LCDC_GDCWARB_L_OFS                       0x00000040
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCWARB_L_RESERVED_MASK             0x7
#define LCDC_GDCWARB_L_RESERVED_SHIFT            0 
#define LCDC_GDCWARB_L_RESERVED_BIT              0x7
#define LCDC_GDCWARB_L_RESERVED_BITWIDTH         3
// WAR bitfiled (RW) Reset=0
#define LCDC_GDCWARB_L_WAR_MASK                  0xFFFFFFF8
#define LCDC_GDCWARB_L_WAR_SHIFT                 3 
#define LCDC_GDCWARB_L_WAR_BIT                   0x1FFFFFFF
#define LCDC_GDCWARB_L_WAR_BITWIDTH              29
// GDCLARC0_L Register
#define LCDC_GDCLARC0_L_OFS                      0x00000048
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCLARC0_L_RESERVED_MASK            0x1
#define LCDC_GDCLARC0_L_RESERVED_SHIFT           0 
#define LCDC_GDCLARC0_L_RESERVED_BIT             0x1
#define LCDC_GDCLARC0_L_RESERVED_BITWIDTH        1
// SSCROLL bitfiled (RW) Reset=0
#define LCDC_GDCLARC0_L_SSCROLL_MASK             0x6
#define LCDC_GDCLARC0_L_SSCROLL_SHIFT            1 
#define LCDC_GDCLARC0_L_SSCROLL_BIT              0x3
#define LCDC_GDCLARC0_L_SSCROLL_BITWIDTH         2
// SAR bitfiled (RW) Reset=0
#define LCDC_GDCLARC0_L_SAR_MASK                 0xFFFFFFF8
#define LCDC_GDCLARC0_L_SAR_SHIFT                3 
#define LCDC_GDCLARC0_L_SAR_BIT                  0x1FFFFFFF
#define LCDC_GDCLARC0_L_SAR_BITWIDTH             29
// GDCLARC1_L Register
#define LCDC_GDCLARC1_L_OFS                      0x00000050
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCLARC1_L_RESERVED_MASK            0x1
#define LCDC_GDCLARC1_L_RESERVED_SHIFT           0 
#define LCDC_GDCLARC1_L_RESERVED_BIT             0x1
#define LCDC_GDCLARC1_L_RESERVED_BITWIDTH        1
// SSCROLL bitfiled (RW) Reset=0
#define LCDC_GDCLARC1_L_SSCROLL_MASK             0x6
#define LCDC_GDCLARC1_L_SSCROLL_SHIFT            1 
#define LCDC_GDCLARC1_L_SSCROLL_BIT              0x3
#define LCDC_GDCLARC1_L_SSCROLL_BITWIDTH         2
// SAR bitfiled (RW) Reset=0
#define LCDC_GDCLARC1_L_SAR_MASK                 0xFFFFFFF8
#define LCDC_GDCLARC1_L_SAR_SHIFT                3 
#define LCDC_GDCLARC1_L_SAR_BIT                  0x1FFFFFFF
#define LCDC_GDCLARC1_L_SAR_BITWIDTH             29
// GDCLARD0_L Register
#define LCDC_GDCLARD0_L_OFS                      0x00000058
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCLARD0_L_RESERVED_MASK            0x1
#define LCDC_GDCLARD0_L_RESERVED_SHIFT           0 
#define LCDC_GDCLARD0_L_RESERVED_BIT             0x1
#define LCDC_GDCLARD0_L_RESERVED_BITWIDTH        1
// SSCROLL bitfiled (RW) Reset=0
#define LCDC_GDCLARD0_L_SSCROLL_MASK             0x6
#define LCDC_GDCLARD0_L_SSCROLL_SHIFT            1 
#define LCDC_GDCLARD0_L_SSCROLL_BIT              0x3
#define LCDC_GDCLARD0_L_SSCROLL_BITWIDTH         2
// SAR bitfiled (RW) Reset=0
#define LCDC_GDCLARD0_L_SAR_MASK                 0xFFFFFFF8
#define LCDC_GDCLARD0_L_SAR_SHIFT                3 
#define LCDC_GDCLARD0_L_SAR_BIT                  0x1FFFFFFF
#define LCDC_GDCLARD0_L_SAR_BITWIDTH             29
// GDCLARD1_L Register
#define LCDC_GDCLARD1_L_OFS                      0x00000060
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCLARD1_L_RESERVED_MASK            0x1
#define LCDC_GDCLARD1_L_RESERVED_SHIFT           0 
#define LCDC_GDCLARD1_L_RESERVED_BIT             0x1
#define LCDC_GDCLARD1_L_RESERVED_BITWIDTH        1
// SSCROLL bitfiled (RW) Reset=0
#define LCDC_GDCLARD1_L_SSCROLL_MASK             0x6
#define LCDC_GDCLARD1_L_SSCROLL_SHIFT            1 
#define LCDC_GDCLARD1_L_SSCROLL_BIT              0x3
#define LCDC_GDCLARD1_L_SSCROLL_BITWIDTH         2
// SAR bitfiled (RW) Reset=0
#define LCDC_GDCLARD1_L_SAR_MASK                 0xFFFFFFF8
#define LCDC_GDCLARD1_L_SAR_SHIFT                3 
#define LCDC_GDCLARD1_L_SAR_BIT                  0x1FFFFFFF
#define LCDC_GDCLARD1_L_SAR_BITWIDTH             29
// GDCMWRA_L Register
#define LCDC_GDCMWRA_L_OFS                       0x00000068
// MWR bitfiled (RW) Reset=1010000000
#define LCDC_GDCMWRA_L_MWR_MASK                  0x1FFF
#define LCDC_GDCMWRA_L_MWR_SHIFT                 0 
#define LCDC_GDCMWRA_L_MWR_BIT                   0x1FFF
#define LCDC_GDCMWRA_L_MWR_BITWIDTH              13
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCMWRA_L_RESERVED_MASK             0xFFFFE000
#define LCDC_GDCMWRA_L_RESERVED_SHIFT            13 
#define LCDC_GDCMWRA_L_RESERVED_BIT              0x7FFFF
#define LCDC_GDCMWRA_L_RESERVED_BITWIDTH         19
// GDCMWRB_L Register
#define LCDC_GDCMWRB_L_OFS                       0x00000070
// MWR bitfiled (RW) Reset=1010000000
#define LCDC_GDCMWRB_L_MWR_MASK                  0x1FFF
#define LCDC_GDCMWRB_L_MWR_SHIFT                 0 
#define LCDC_GDCMWRB_L_MWR_BIT                   0x1FFF
#define LCDC_GDCMWRB_L_MWR_BITWIDTH              13
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCMWRB_L_RESERVED_MASK             0xFFFFE000
#define LCDC_GDCMWRB_L_RESERVED_SHIFT            13 
#define LCDC_GDCMWRB_L_RESERVED_BIT              0x7FFFF
#define LCDC_GDCMWRB_L_RESERVED_BITWIDTH         19
// GDCMWRC_L Register
#define LCDC_GDCMWRC_L_OFS                       0x00000078
// MWR bitfiled (RW) Reset=1010000000
#define LCDC_GDCMWRC_L_MWR_MASK                  0x1FFF
#define LCDC_GDCMWRC_L_MWR_SHIFT                 0 
#define LCDC_GDCMWRC_L_MWR_BIT                   0x1FFF
#define LCDC_GDCMWRC_L_MWR_BITWIDTH              13
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCMWRC_L_RESERVED_MASK             0xFFFFE000
#define LCDC_GDCMWRC_L_RESERVED_SHIFT            13 
#define LCDC_GDCMWRC_L_RESERVED_BIT              0x7FFFF
#define LCDC_GDCMWRC_L_RESERVED_BITWIDTH         19
// GDCMWRD_L Register
#define LCDC_GDCMWRD_L_OFS                       0x00000080
// MWR bitfiled (RW) Reset=1010000000
#define LCDC_GDCMWRD_L_MWR_MASK                  0x1FFF
#define LCDC_GDCMWRD_L_MWR_SHIFT                 0 
#define LCDC_GDCMWRD_L_MWR_BIT                   0x1FFF
#define LCDC_GDCMWRD_L_MWR_BITWIDTH              13
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCMWRD_L_RESERVED_MASK             0xFFFFE000
#define LCDC_GDCMWRD_L_RESERVED_SHIFT            13 
#define LCDC_GDCMWRD_L_RESERVED_BIT              0x7FFFF
#define LCDC_GDCMWRD_L_RESERVED_BITWIDTH         19
// GDCMWRE_L Register
#define LCDC_GDCMWRE_L_OFS                       0x00000088
// MWR bitfiled (RW) Reset=1010000000
#define LCDC_GDCMWRE_L_MWR_MASK                  0x1FFF
#define LCDC_GDCMWRE_L_MWR_SHIFT                 0 
#define LCDC_GDCMWRE_L_MWR_BIT                   0x1FFF
#define LCDC_GDCMWRE_L_MWR_BITWIDTH              13
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCMWRE_L_RESERVED_MASK             0xFFFFE000
#define LCDC_GDCMWRE_L_RESERVED_SHIFT            13 
#define LCDC_GDCMWRE_L_RESERVED_BIT              0x7FFFF
#define LCDC_GDCMWRE_L_RESERVED_BITWIDTH         19
// GDCLSRA_L Register
#define LCDC_GDCLSRA_L_OFS                       0x00000090
// LVS bitfiled (RW) Reset=1011111
#define LCDC_GDCLSRA_L_LVS_MASK                  0x3FF
#define LCDC_GDCLSRA_L_LVS_SHIFT                 0 
#define LCDC_GDCLSRA_L_LVS_BIT                   0x3FF
#define LCDC_GDCLSRA_L_LVS_BITWIDTH              10
// reserved2 bitfiled (RO) Reset=0
#define LCDC_GDCLSRA_L_RESERVED2_MASK            0xFC00
#define LCDC_GDCLSRA_L_RESERVED2_SHIFT           10 
#define LCDC_GDCLSRA_L_RESERVED2_BIT             0x3F
#define LCDC_GDCLSRA_L_RESERVED2_BITWIDTH        6
// LHS bitfiled (RW) Reset=11000000
#define LCDC_GDCLSRA_L_LHS_MASK                  0x7FF0000
#define LCDC_GDCLSRA_L_LHS_SHIFT                 16 
#define LCDC_GDCLSRA_L_LHS_BIT                   0x7FF
#define LCDC_GDCLSRA_L_LHS_BITWIDTH              11
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCLSRA_L_RESERVED_MASK             0xF8000000
#define LCDC_GDCLSRA_L_RESERVED_SHIFT            27 
#define LCDC_GDCLSRA_L_RESERVED_BIT              0x1F
#define LCDC_GDCLSRA_L_RESERVED_BITWIDTH         5
// GDCLSRB_L Register
#define LCDC_GDCLSRB_L_OFS                       0x00000098
// LVS bitfiled (RW) Reset=1011111
#define LCDC_GDCLSRB_L_LVS_MASK                  0x3FF
#define LCDC_GDCLSRB_L_LVS_SHIFT                 0 
#define LCDC_GDCLSRB_L_LVS_BIT                   0x3FF
#define LCDC_GDCLSRB_L_LVS_BITWIDTH              10
// reserved2 bitfiled (RO) Reset=0
#define LCDC_GDCLSRB_L_RESERVED2_MASK            0xFC00
#define LCDC_GDCLSRB_L_RESERVED2_SHIFT           10 
#define LCDC_GDCLSRB_L_RESERVED2_BIT             0x3F
#define LCDC_GDCLSRB_L_RESERVED2_BITWIDTH        6
// LHS bitfiled (RW) Reset=11000000
#define LCDC_GDCLSRB_L_LHS_MASK                  0x7FF0000
#define LCDC_GDCLSRB_L_LHS_SHIFT                 16 
#define LCDC_GDCLSRB_L_LHS_BIT                   0x7FF
#define LCDC_GDCLSRB_L_LHS_BITWIDTH              11
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCLSRB_L_RESERVED_MASK             0xF8000000
#define LCDC_GDCLSRB_L_RESERVED_SHIFT            27 
#define LCDC_GDCLSRB_L_RESERVED_BIT              0x1F
#define LCDC_GDCLSRB_L_RESERVED_BITWIDTH         5
// GDCLSRC_L Register
#define LCDC_GDCLSRC_L_OFS                       0x000000A0
// LVS bitfiled (RW) Reset=1011111
#define LCDC_GDCLSRC_L_LVS_MASK                  0x3FF
#define LCDC_GDCLSRC_L_LVS_SHIFT                 0 
#define LCDC_GDCLSRC_L_LVS_BIT                   0x3FF
#define LCDC_GDCLSRC_L_LVS_BITWIDTH              10
// reserved2 bitfiled (RO) Reset=0
#define LCDC_GDCLSRC_L_RESERVED2_MASK            0xFC00
#define LCDC_GDCLSRC_L_RESERVED2_SHIFT           10 
#define LCDC_GDCLSRC_L_RESERVED2_BIT             0x3F
#define LCDC_GDCLSRC_L_RESERVED2_BITWIDTH        6
// LHS bitfiled (RW) Reset=11000000
#define LCDC_GDCLSRC_L_LHS_MASK                  0x7FF0000
#define LCDC_GDCLSRC_L_LHS_SHIFT                 16 
#define LCDC_GDCLSRC_L_LHS_BIT                   0x7FF
#define LCDC_GDCLSRC_L_LHS_BITWIDTH              11
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCLSRC_L_RESERVED_MASK             0xF8000000
#define LCDC_GDCLSRC_L_RESERVED_SHIFT            27 
#define LCDC_GDCLSRC_L_RESERVED_BIT              0x1F
#define LCDC_GDCLSRC_L_RESERVED_BITWIDTH         5
// GDCLSRD_L Register
#define LCDC_GDCLSRD_L_OFS                       0x000000A8
// LVS bitfiled (RW) Reset=1011111
#define LCDC_GDCLSRD_L_LVS_MASK                  0x3FF
#define LCDC_GDCLSRD_L_LVS_SHIFT                 0 
#define LCDC_GDCLSRD_L_LVS_BIT                   0x3FF
#define LCDC_GDCLSRD_L_LVS_BITWIDTH              10
// reserved2 bitfiled (RO) Reset=0
#define LCDC_GDCLSRD_L_RESERVED2_MASK            0xFC00
#define LCDC_GDCLSRD_L_RESERVED2_SHIFT           10 
#define LCDC_GDCLSRD_L_RESERVED2_BIT             0x3F
#define LCDC_GDCLSRD_L_RESERVED2_BITWIDTH        6
// LHS bitfiled (RW) Reset=11000000
#define LCDC_GDCLSRD_L_LHS_MASK                  0x7FF0000
#define LCDC_GDCLSRD_L_LHS_SHIFT                 16 
#define LCDC_GDCLSRD_L_LHS_BIT                   0x7FF
#define LCDC_GDCLSRD_L_LHS_BITWIDTH              11
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCLSRD_L_RESERVED_MASK             0xF8000000
#define LCDC_GDCLSRD_L_RESERVED_SHIFT            27 
#define LCDC_GDCLSRD_L_RESERVED_BIT              0x1F
#define LCDC_GDCLSRD_L_RESERVED_BITWIDTH         5
// GDCLSRE_L Register
#define LCDC_GDCLSRE_L_OFS                       0x000000B0
// LVS bitfiled (RW) Reset=1011111
#define LCDC_GDCLSRE_L_LVS_MASK                  0x3FF
#define LCDC_GDCLSRE_L_LVS_SHIFT                 0 
#define LCDC_GDCLSRE_L_LVS_BIT                   0x3FF
#define LCDC_GDCLSRE_L_LVS_BITWIDTH              10
// reserved2 bitfiled (RO) Reset=0
#define LCDC_GDCLSRE_L_RESERVED2_MASK            0xFC00
#define LCDC_GDCLSRE_L_RESERVED2_SHIFT           10 
#define LCDC_GDCLSRE_L_RESERVED2_BIT             0x3F
#define LCDC_GDCLSRE_L_RESERVED2_BITWIDTH        6
// LHS bitfiled (RW) Reset=11000000
#define LCDC_GDCLSRE_L_LHS_MASK                  0x7FF0000
#define LCDC_GDCLSRE_L_LHS_SHIFT                 16 
#define LCDC_GDCLSRE_L_LHS_BIT                   0x7FF
#define LCDC_GDCLSRE_L_LHS_BITWIDTH              11
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCLSRE_L_RESERVED_MASK             0xF8000000
#define LCDC_GDCLSRE_L_RESERVED_SHIFT            27 
#define LCDC_GDCLSRE_L_RESERVED_BIT              0x1F
#define LCDC_GDCLSRE_L_RESERVED_BITWIDTH         5
// GDCLDRA_L Register
#define LCDC_GDCLDRA_L_OFS                       0x000000B8
// LHEIGHT bitfiled (RW) Reset=111100000
#define LCDC_GDCLDRA_L_LHEIGHT_MASK              0x7FF
#define LCDC_GDCLDRA_L_LHEIGHT_SHIFT             0 
#define LCDC_GDCLDRA_L_LHEIGHT_BIT               0x7FF
#define LCDC_GDCLDRA_L_LHEIGHT_BITWIDTH          11
// reserved2 bitfiled (RO) Reset=0
#define LCDC_GDCLDRA_L_RESERVED2_MASK            0xF800
#define LCDC_GDCLDRA_L_RESERVED2_SHIFT           11 
#define LCDC_GDCLDRA_L_RESERVED2_BIT             0x1F
#define LCDC_GDCLDRA_L_RESERVED2_BITWIDTH        5
// LWIDTH bitfiled (RW) Reset=1010000000
#define LCDC_GDCLDRA_L_LWIDTH_MASK               0xFFF0000
#define LCDC_GDCLDRA_L_LWIDTH_SHIFT              16 
#define LCDC_GDCLDRA_L_LWIDTH_BIT                0xFFF
#define LCDC_GDCLDRA_L_LWIDTH_BITWIDTH           12
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCLDRA_L_RESERVED_MASK             0xF0000000
#define LCDC_GDCLDRA_L_RESERVED_SHIFT            28 
#define LCDC_GDCLDRA_L_RESERVED_BIT              0xF
#define LCDC_GDCLDRA_L_RESERVED_BITWIDTH         4
// GDCLDRB_L Register
#define LCDC_GDCLDRB_L_OFS                       0x000000C0
// LHEIGHT bitfiled (RW) Reset=111100000
#define LCDC_GDCLDRB_L_LHEIGHT_MASK              0x7FF
#define LCDC_GDCLDRB_L_LHEIGHT_SHIFT             0 
#define LCDC_GDCLDRB_L_LHEIGHT_BIT               0x7FF
#define LCDC_GDCLDRB_L_LHEIGHT_BITWIDTH          11
// reserved2 bitfiled (RO) Reset=0
#define LCDC_GDCLDRB_L_RESERVED2_MASK            0xF800
#define LCDC_GDCLDRB_L_RESERVED2_SHIFT           11 
#define LCDC_GDCLDRB_L_RESERVED2_BIT             0x1F
#define LCDC_GDCLDRB_L_RESERVED2_BITWIDTH        5
// LWIDTH bitfiled (RW) Reset=1010000000
#define LCDC_GDCLDRB_L_LWIDTH_MASK               0xFFF0000
#define LCDC_GDCLDRB_L_LWIDTH_SHIFT              16 
#define LCDC_GDCLDRB_L_LWIDTH_BIT                0xFFF
#define LCDC_GDCLDRB_L_LWIDTH_BITWIDTH           12
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCLDRB_L_RESERVED_MASK             0xF0000000
#define LCDC_GDCLDRB_L_RESERVED_SHIFT            28 
#define LCDC_GDCLDRB_L_RESERVED_BIT              0xF
#define LCDC_GDCLDRB_L_RESERVED_BITWIDTH         4
// GDCLDRC_L Register
#define LCDC_GDCLDRC_L_OFS                       0x000000C8
// LHEIGHT bitfiled (RW) Reset=111100000
#define LCDC_GDCLDRC_L_LHEIGHT_MASK              0x7FF
#define LCDC_GDCLDRC_L_LHEIGHT_SHIFT             0 
#define LCDC_GDCLDRC_L_LHEIGHT_BIT               0x7FF
#define LCDC_GDCLDRC_L_LHEIGHT_BITWIDTH          11
// reserved2 bitfiled (RO) Reset=0
#define LCDC_GDCLDRC_L_RESERVED2_MASK            0xF800
#define LCDC_GDCLDRC_L_RESERVED2_SHIFT           11 
#define LCDC_GDCLDRC_L_RESERVED2_BIT             0x1F
#define LCDC_GDCLDRC_L_RESERVED2_BITWIDTH        5
// LWIDTH bitfiled (RW) Reset=1010000000
#define LCDC_GDCLDRC_L_LWIDTH_MASK               0xFFF0000
#define LCDC_GDCLDRC_L_LWIDTH_SHIFT              16 
#define LCDC_GDCLDRC_L_LWIDTH_BIT                0xFFF
#define LCDC_GDCLDRC_L_LWIDTH_BITWIDTH           12
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCLDRC_L_RESERVED_MASK             0xF0000000
#define LCDC_GDCLDRC_L_RESERVED_SHIFT            28 
#define LCDC_GDCLDRC_L_RESERVED_BIT              0xF
#define LCDC_GDCLDRC_L_RESERVED_BITWIDTH         4
// GDCLDRD_L Register
#define LCDC_GDCLDRD_L_OFS                       0x000000D0
// LHEIGHT bitfiled (RW) Reset=111100000
#define LCDC_GDCLDRD_L_LHEIGHT_MASK              0x7FF
#define LCDC_GDCLDRD_L_LHEIGHT_SHIFT             0 
#define LCDC_GDCLDRD_L_LHEIGHT_BIT               0x7FF
#define LCDC_GDCLDRD_L_LHEIGHT_BITWIDTH          11
// reserved2 bitfiled (RO) Reset=0
#define LCDC_GDCLDRD_L_RESERVED2_MASK            0xF800
#define LCDC_GDCLDRD_L_RESERVED2_SHIFT           11 
#define LCDC_GDCLDRD_L_RESERVED2_BIT             0x1F
#define LCDC_GDCLDRD_L_RESERVED2_BITWIDTH        5
// LWIDTH bitfiled (RW) Reset=1010000000
#define LCDC_GDCLDRD_L_LWIDTH_MASK               0xFFF0000
#define LCDC_GDCLDRD_L_LWIDTH_SHIFT              16 
#define LCDC_GDCLDRD_L_LWIDTH_BIT                0xFFF
#define LCDC_GDCLDRD_L_LWIDTH_BITWIDTH           12
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCLDRD_L_RESERVED_MASK             0xF0000000
#define LCDC_GDCLDRD_L_RESERVED_SHIFT            28 
#define LCDC_GDCLDRD_L_RESERVED_BIT              0xF
#define LCDC_GDCLDRD_L_RESERVED_BITWIDTH         4
// GDCLDRE_L Register
#define LCDC_GDCLDRE_L_OFS                       0x000000D8
// LHEIGHT bitfiled (RW) Reset=111100000
#define LCDC_GDCLDRE_L_LHEIGHT_MASK              0x7FF
#define LCDC_GDCLDRE_L_LHEIGHT_SHIFT             0 
#define LCDC_GDCLDRE_L_LHEIGHT_BIT               0x7FF
#define LCDC_GDCLDRE_L_LHEIGHT_BITWIDTH          11
// reserved2 bitfiled (RO) Reset=0
#define LCDC_GDCLDRE_L_RESERVED2_MASK            0xF800
#define LCDC_GDCLDRE_L_RESERVED2_SHIFT           11 
#define LCDC_GDCLDRE_L_RESERVED2_BIT             0x1F
#define LCDC_GDCLDRE_L_RESERVED2_BITWIDTH        5
// LWIDTH bitfiled (RW) Reset=1010000000
#define LCDC_GDCLDRE_L_LWIDTH_MASK               0xFFF0000
#define LCDC_GDCLDRE_L_LWIDTH_SHIFT              16 
#define LCDC_GDCLDRE_L_LWIDTH_BIT                0xFFF
#define LCDC_GDCLDRE_L_LWIDTH_BITWIDTH           12
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCLDRE_L_RESERVED_MASK             0xF0000000
#define LCDC_GDCLDRE_L_RESERVED_SHIFT            28 
#define LCDC_GDCLDRE_L_RESERVED_BIT              0xF
#define LCDC_GDCLDRE_L_RESERVED_BITWIDTH         4
// GDCWSRA_L Register
#define LCDC_GDCWSRA_L_OFS                       0x000000E0
// WVDS bitfiled (RW) Reset=1011111
#define LCDC_GDCWSRA_L_WVDS_MASK                 0x3FF
#define LCDC_GDCWSRA_L_WVDS_SHIFT                0 
#define LCDC_GDCWSRA_L_WVDS_BIT                  0x3FF
#define LCDC_GDCWSRA_L_WVDS_BITWIDTH             10
// reserved2 bitfiled (RO) Reset=0
#define LCDC_GDCWSRA_L_RESERVED2_MASK            0xFC00
#define LCDC_GDCWSRA_L_RESERVED2_SHIFT           10 
#define LCDC_GDCWSRA_L_RESERVED2_BIT             0x3F
#define LCDC_GDCWSRA_L_RESERVED2_BITWIDTH        6
// WHDS bitfiled (RW) Reset=11000000
#define LCDC_GDCWSRA_L_WHDS_MASK                 0x7FF0000
#define LCDC_GDCWSRA_L_WHDS_SHIFT                16 
#define LCDC_GDCWSRA_L_WHDS_BIT                  0x7FF
#define LCDC_GDCWSRA_L_WHDS_BITWIDTH             11
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCWSRA_L_RESERVED_MASK             0xF8000000
#define LCDC_GDCWSRA_L_RESERVED_SHIFT            27 
#define LCDC_GDCWSRA_L_RESERVED_BIT              0x1F
#define LCDC_GDCWSRA_L_RESERVED_BITWIDTH         5
// GDCWSRB_L Register
#define LCDC_GDCWSRB_L_OFS                       0x000000E8
// WVDS bitfiled (RW) Reset=1011111
#define LCDC_GDCWSRB_L_WVDS_MASK                 0x3FF
#define LCDC_GDCWSRB_L_WVDS_SHIFT                0 
#define LCDC_GDCWSRB_L_WVDS_BIT                  0x3FF
#define LCDC_GDCWSRB_L_WVDS_BITWIDTH             10
// reserved2 bitfiled (RO) Reset=0
#define LCDC_GDCWSRB_L_RESERVED2_MASK            0xFC00
#define LCDC_GDCWSRB_L_RESERVED2_SHIFT           10 
#define LCDC_GDCWSRB_L_RESERVED2_BIT             0x3F
#define LCDC_GDCWSRB_L_RESERVED2_BITWIDTH        6
// WHDS bitfiled (RW) Reset=11000000
#define LCDC_GDCWSRB_L_WHDS_MASK                 0x7FF0000
#define LCDC_GDCWSRB_L_WHDS_SHIFT                16 
#define LCDC_GDCWSRB_L_WHDS_BIT                  0x7FF
#define LCDC_GDCWSRB_L_WHDS_BITWIDTH             11
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCWSRB_L_RESERVED_MASK             0xF8000000
#define LCDC_GDCWSRB_L_RESERVED_SHIFT            27 
#define LCDC_GDCWSRB_L_RESERVED_BIT              0x1F
#define LCDC_GDCWSRB_L_RESERVED_BITWIDTH         5
// GDCWIMRA_L Register
#define LCDC_GDCWIMRA_L_OFS                      0x000000F0
// WHEIGHT bitfiled (RW) Reset=111100000
#define LCDC_GDCWIMRA_L_WHEIGHT_MASK             0x7FF
#define LCDC_GDCWIMRA_L_WHEIGHT_SHIFT            0 
#define LCDC_GDCWIMRA_L_WHEIGHT_BIT              0x7FF
#define LCDC_GDCWIMRA_L_WHEIGHT_BITWIDTH         11
// reserved2 bitfiled (RO) Reset=0
#define LCDC_GDCWIMRA_L_RESERVED2_MASK           0xF800
#define LCDC_GDCWIMRA_L_RESERVED2_SHIFT          11 
#define LCDC_GDCWIMRA_L_RESERVED2_BIT            0x1F
#define LCDC_GDCWIMRA_L_RESERVED2_BITWIDTH       5
// WWIDTH bitfiled (RW) Reset=1010000000
#define LCDC_GDCWIMRA_L_WWIDTH_MASK              0xFFF0000
#define LCDC_GDCWIMRA_L_WWIDTH_SHIFT             16 
#define LCDC_GDCWIMRA_L_WWIDTH_BIT               0xFFF
#define LCDC_GDCWIMRA_L_WWIDTH_BITWIDTH          12
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCWIMRA_L_RESERVED_MASK            0xF0000000
#define LCDC_GDCWIMRA_L_RESERVED_SHIFT           28 
#define LCDC_GDCWIMRA_L_RESERVED_BIT             0xF
#define LCDC_GDCWIMRA_L_RESERVED_BITWIDTH        4
// GDCWIMRB_L Register
#define LCDC_GDCWIMRB_L_OFS                      0x000000F8
// WHEIGHT bitfiled (RW) Reset=111100000
#define LCDC_GDCWIMRB_L_WHEIGHT_MASK             0x7FF
#define LCDC_GDCWIMRB_L_WHEIGHT_SHIFT            0 
#define LCDC_GDCWIMRB_L_WHEIGHT_BIT              0x7FF
#define LCDC_GDCWIMRB_L_WHEIGHT_BITWIDTH         11
// reserved2 bitfiled (RO) Reset=0
#define LCDC_GDCWIMRB_L_RESERVED2_MASK           0xF800
#define LCDC_GDCWIMRB_L_RESERVED2_SHIFT          11 
#define LCDC_GDCWIMRB_L_RESERVED2_BIT            0x1F
#define LCDC_GDCWIMRB_L_RESERVED2_BITWIDTH       5
// WWIDTH bitfiled (RW) Reset=1010000000
#define LCDC_GDCWIMRB_L_WWIDTH_MASK              0xFFF0000
#define LCDC_GDCWIMRB_L_WWIDTH_SHIFT             16 
#define LCDC_GDCWIMRB_L_WWIDTH_BIT               0xFFF
#define LCDC_GDCWIMRB_L_WWIDTH_BITWIDTH          12
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCWIMRB_L_RESERVED_MASK            0xF0000000
#define LCDC_GDCWIMRB_L_RESERVED_SHIFT           28 
#define LCDC_GDCWIMRB_L_RESERVED_BIT             0xF
#define LCDC_GDCWIMRB_L_RESERVED_BITWIDTH        4
// GDCCAVRA_L Register
#define LCDC_GDCCAVRA_L_OFS                      0x00000100
// ALPHAA bitfiled (RW) Reset=11111111
#define LCDC_GDCCAVRA_L_ALPHAA_MASK              0xFF
#define LCDC_GDCCAVRA_L_ALPHAA_SHIFT             0 
#define LCDC_GDCCAVRA_L_ALPHAA_BIT               0xFF
#define LCDC_GDCCAVRA_L_ALPHAA_BITWIDTH          8
// WALPHAA bitfiled (RW) Reset=11111111
#define LCDC_GDCCAVRA_L_WALPHAA_MASK             0xFF00
#define LCDC_GDCCAVRA_L_WALPHAA_SHIFT            8 
#define LCDC_GDCCAVRA_L_WALPHAA_BIT              0xFF
#define LCDC_GDCCAVRA_L_WALPHAA_BITWIDTH         8
// ALPHAB bitfiled (RW) Reset=11111111
#define LCDC_GDCCAVRA_L_ALPHAB_MASK              0xFF0000
#define LCDC_GDCCAVRA_L_ALPHAB_SHIFT             16 
#define LCDC_GDCCAVRA_L_ALPHAB_BIT               0xFF
#define LCDC_GDCCAVRA_L_ALPHAB_BITWIDTH          8
// WALPHAB bitfiled (RW) Reset=11111111
#define LCDC_GDCCAVRA_L_WALPHAB_MASK             0xFF000000
#define LCDC_GDCCAVRA_L_WALPHAB_SHIFT            24 
#define LCDC_GDCCAVRA_L_WALPHAB_BIT              0xFF
#define LCDC_GDCCAVRA_L_WALPHAB_BITWIDTH         8
// GDCCAVRA_U Register
#define LCDC_GDCCAVRA_U_OFS                      0x00000104
// ALPHAC bitfiled (RW) Reset=11111111
#define LCDC_GDCCAVRA_U_ALPHAC_MASK              0xFF
#define LCDC_GDCCAVRA_U_ALPHAC_SHIFT             0 
#define LCDC_GDCCAVRA_U_ALPHAC_BIT               0xFF
#define LCDC_GDCCAVRA_U_ALPHAC_BITWIDTH          8
// WALPHAC bitfiled (RW) Reset=11111111
#define LCDC_GDCCAVRA_U_WALPHAC_MASK             0xFF00
#define LCDC_GDCCAVRA_U_WALPHAC_SHIFT            8 
#define LCDC_GDCCAVRA_U_WALPHAC_BIT              0xFF
#define LCDC_GDCCAVRA_U_WALPHAC_BITWIDTH         8
// ALPHAD bitfiled (RW) Reset=11111111
#define LCDC_GDCCAVRA_U_ALPHAD_MASK              0xFF0000
#define LCDC_GDCCAVRA_U_ALPHAD_SHIFT             16 
#define LCDC_GDCCAVRA_U_ALPHAD_BIT               0xFF
#define LCDC_GDCCAVRA_U_ALPHAD_BITWIDTH          8
// WALPHAD bitfiled (RW) Reset=11111111
#define LCDC_GDCCAVRA_U_WALPHAD_MASK             0xFF000000
#define LCDC_GDCCAVRA_U_WALPHAD_SHIFT            24 
#define LCDC_GDCCAVRA_U_WALPHAD_BIT              0xFF
#define LCDC_GDCCAVRA_U_WALPHAD_BITWIDTH         8
// GDCCAVRB_L Register
#define LCDC_GDCCAVRB_L_OFS                      0x00000108
// ALPHAE bitfiled (RW) Reset=11111111
#define LCDC_GDCCAVRB_L_ALPHAE_MASK              0xFF
#define LCDC_GDCCAVRB_L_ALPHAE_SHIFT             0 
#define LCDC_GDCCAVRB_L_ALPHAE_BIT               0xFF
#define LCDC_GDCCAVRB_L_ALPHAE_BITWIDTH          8
// WALPHAE bitfiled (RW) Reset=11111111
#define LCDC_GDCCAVRB_L_WALPHAE_MASK             0xFF00
#define LCDC_GDCCAVRB_L_WALPHAE_SHIFT            8 
#define LCDC_GDCCAVRB_L_WALPHAE_BIT              0xFF
#define LCDC_GDCCAVRB_L_WALPHAE_BITWIDTH         8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCAVRB_L_RESERVED_MASK            0xFFFF0000
#define LCDC_GDCCAVRB_L_RESERVED_SHIFT           16 
#define LCDC_GDCCAVRB_L_RESERVED_BIT             0xFFFF
#define LCDC_GDCCAVRB_L_RESERVED_BITWIDTH        16
// GDCHSR_L Register
#define LCDC_GDCHSR_L_OFS                        0x00000110
// HCR bitfiled (RW) Reset=10000000000
#define LCDC_GDCHSR_L_HCR_MASK                   0x1FFF
#define LCDC_GDCHSR_L_HCR_SHIFT                  0 
#define LCDC_GDCHSR_L_HCR_BIT                    0x1FFF
#define LCDC_GDCHSR_L_HCR_BITWIDTH               13
// reserved2 bitfiled (RO) Reset=0
#define LCDC_GDCHSR_L_RESERVED2_MASK             0xE000
#define LCDC_GDCHSR_L_RESERVED2_SHIFT            13 
#define LCDC_GDCHSR_L_RESERVED2_BIT              0x7
#define LCDC_GDCHSR_L_RESERVED2_BITWIDTH         3
// HSPWR bitfiled (RW) Reset=10111
#define LCDC_GDCHSR_L_HSPWR_MASK                 0xFF0000
#define LCDC_GDCHSR_L_HSPWR_SHIFT                16 
#define LCDC_GDCHSR_L_HSPWR_BIT                  0xFF
#define LCDC_GDCHSR_L_HSPWR_BITWIDTH             8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCHSR_L_RESERVED_MASK              0xFF000000
#define LCDC_GDCHSR_L_RESERVED_SHIFT             24 
#define LCDC_GDCHSR_L_RESERVED_BIT               0xFF
#define LCDC_GDCHSR_L_RESERVED_BITWIDTH          8
// GDCVSR_L Register
#define LCDC_GDCVSR_L_OFS                        0x00000118
// VCR bitfiled (RW) Reset=1000001101
#define LCDC_GDCVSR_L_VCR_MASK                   0x7FF
#define LCDC_GDCVSR_L_VCR_SHIFT                  0 
#define LCDC_GDCVSR_L_VCR_BIT                    0x7FF
#define LCDC_GDCVSR_L_VCR_BITWIDTH               11
// reserved3 bitfiled (RO) Reset=0
#define LCDC_GDCVSR_L_RESERVED3_MASK             0xF800
#define LCDC_GDCVSR_L_RESERVED3_SHIFT            11 
#define LCDC_GDCVSR_L_RESERVED3_BIT              0x1F
#define LCDC_GDCVSR_L_RESERVED3_BITWIDTH         5
// VSPWR bitfiled (RW) Reset=10
#define LCDC_GDCVSR_L_VSPWR_MASK                 0xFF0000
#define LCDC_GDCVSR_L_VSPWR_SHIFT                16 
#define LCDC_GDCVSR_L_VSPWR_BIT                  0xFF
#define LCDC_GDCVSR_L_VSPWR_BITWIDTH             8
// reserved2 bitfiled (RO) Reset=0
#define LCDC_GDCVSR_L_RESERVED2_MASK             0x3000000
#define LCDC_GDCVSR_L_RESERVED2_SHIFT            24 
#define LCDC_GDCVSR_L_RESERVED2_BIT              0x3
#define LCDC_GDCVSR_L_RESERVED2_BITWIDTH         2
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCVSR_L_RESERVED_MASK              0xFC000000
#define LCDC_GDCVSR_L_RESERVED_SHIFT             26 
#define LCDC_GDCVSR_L_RESERVED_BIT               0x3F
#define LCDC_GDCVSR_L_RESERVED_BITWIDTH          6
// GDCCBAR0_L Register
#define LCDC_GDCCBAR0_L_OFS                      0x00000128
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCBAR0_L_RESERVED_MASK            0x7
#define LCDC_GDCCBAR0_L_RESERVED_SHIFT           0 
#define LCDC_GDCCBAR0_L_RESERVED_BIT             0x7
#define LCDC_GDCCBAR0_L_RESERVED_BITWIDTH        3
// CBAR bitfiled (RW) Reset=0
#define LCDC_GDCCBAR0_L_CBAR_MASK                0xFFFFFFF8
#define LCDC_GDCCBAR0_L_CBAR_SHIFT               3 
#define LCDC_GDCCBAR0_L_CBAR_BIT                 0x1FFFFFFF
#define LCDC_GDCCBAR0_L_CBAR_BITWIDTH            29
// GDCCBAR1_L Register
#define LCDC_GDCCBAR1_L_OFS                      0x00000130
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCBAR1_L_RESERVED_MASK            0x7
#define LCDC_GDCCBAR1_L_RESERVED_SHIFT           0 
#define LCDC_GDCCBAR1_L_RESERVED_BIT             0x7
#define LCDC_GDCCBAR1_L_RESERVED_BITWIDTH        3
// CBAR bitfiled (RW) Reset=0
#define LCDC_GDCCBAR1_L_CBAR_MASK                0xFFFFFFF8
#define LCDC_GDCCBAR1_L_CBAR_SHIFT               3 
#define LCDC_GDCCBAR1_L_CBAR_BIT                 0x1FFFFFFF
#define LCDC_GDCCBAR1_L_CBAR_BITWIDTH            29
// GDCCBAR2_L Register
#define LCDC_GDCCBAR2_L_OFS                      0x00000138
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCBAR2_L_RESERVED_MASK            0x7
#define LCDC_GDCCBAR2_L_RESERVED_SHIFT           0 
#define LCDC_GDCCBAR2_L_RESERVED_BIT             0x7
#define LCDC_GDCCBAR2_L_RESERVED_BITWIDTH        3
// CBAR bitfiled (RW) Reset=0
#define LCDC_GDCCBAR2_L_CBAR_MASK                0xFFFFFFF8
#define LCDC_GDCCBAR2_L_CBAR_SHIFT               3 
#define LCDC_GDCCBAR2_L_CBAR_BIT                 0x1FFFFFFF
#define LCDC_GDCCBAR2_L_CBAR_BITWIDTH            29
// GDCINTR_L Register
#define LCDC_GDCINTR_L_OFS                       0x00000140
// GAPMSK bitfiled (RW) Reset=0
#define LCDC_GDCINTR_L_GAPMSK_MASK               0x1
#define LCDC_GDCINTR_L_GAPMSK_SHIFT              0 
#define LCDC_GDCINTR_L_GAPMSK_BIT                0x1
#define LCDC_GDCINTR_L_GAPMSK_BITWIDTH           1
// HSYNCMSK bitfiled (RW) Reset=0
#define LCDC_GDCINTR_L_HSYNCMSK_MASK             0x2
#define LCDC_GDCINTR_L_HSYNCMSK_SHIFT            1 
#define LCDC_GDCINTR_L_HSYNCMSK_BIT              0x1
#define LCDC_GDCINTR_L_HSYNCMSK_BITWIDTH         1
// VSYNCMSK bitfiled (RW) Reset=0
#define LCDC_GDCINTR_L_VSYNCMSK_MASK             0x4
#define LCDC_GDCINTR_L_VSYNCMSK_SHIFT            2 
#define LCDC_GDCINTR_L_VSYNCMSK_BIT              0x1
#define LCDC_GDCINTR_L_VSYNCMSK_BITWIDTH         1
// GBERMSK bitfiled (RW) Reset=0
#define LCDC_GDCINTR_L_GBERMSK_MASK              0x8
#define LCDC_GDCINTR_L_GBERMSK_SHIFT             3 
#define LCDC_GDCINTR_L_GBERMSK_BIT               0x1
#define LCDC_GDCINTR_L_GBERMSK_BITWIDTH          1
// GAPINT bitfiled (RW) Reset=0
#define LCDC_GDCINTR_L_GAPINT_MASK               0x10
#define LCDC_GDCINTR_L_GAPINT_SHIFT              4 
#define LCDC_GDCINTR_L_GAPINT_BIT                0x1
#define LCDC_GDCINTR_L_GAPINT_BITWIDTH           1
// HSYNCINT bitfiled (RW) Reset=0
#define LCDC_GDCINTR_L_HSYNCINT_MASK             0x20
#define LCDC_GDCINTR_L_HSYNCINT_SHIFT            5 
#define LCDC_GDCINTR_L_HSYNCINT_BIT              0x1
#define LCDC_GDCINTR_L_HSYNCINT_BITWIDTH         1
// VSYNCINT bitfiled (RW) Reset=0
#define LCDC_GDCINTR_L_VSYNCINT_MASK             0x40
#define LCDC_GDCINTR_L_VSYNCINT_SHIFT            6 
#define LCDC_GDCINTR_L_VSYNCINT_BIT              0x1
#define LCDC_GDCINTR_L_VSYNCINT_BITWIDTH         1
// GBERINT bitfiled (RW) Reset=0
#define LCDC_GDCINTR_L_GBERINT_MASK              0x80
#define LCDC_GDCINTR_L_GBERINT_SHIFT             7 
#define LCDC_GDCINTR_L_GBERINT_BIT               0x1
#define LCDC_GDCINTR_L_GBERINT_BITWIDTH          1
// IFURMSK bitfiled (RW) Reset=0
#define LCDC_GDCINTR_L_IFURMSK_MASK              0x100
#define LCDC_GDCINTR_L_IFURMSK_SHIFT             8 
#define LCDC_GDCINTR_L_IFURMSK_BIT               0x1
#define LCDC_GDCINTR_L_IFURMSK_BITWIDTH          1
// OFURMSK bitfiled (RW) Reset=0
#define LCDC_GDCINTR_L_OFURMSK_MASK              0x200
#define LCDC_GDCINTR_L_OFURMSK_SHIFT             9 
#define LCDC_GDCINTR_L_OFURMSK_BIT               0x1
#define LCDC_GDCINTR_L_OFURMSK_BITWIDTH          1
// VSLMSK bitfiled (RW) Reset=0
#define LCDC_GDCINTR_L_VSLMSK_MASK               0x400
#define LCDC_GDCINTR_L_VSLMSK_SHIFT              10 
#define LCDC_GDCINTR_L_VSLMSK_BIT                0x1
#define LCDC_GDCINTR_L_VSLMSK_BITWIDTH           1
// GPEMSK bitfiled (RW) Reset=0
#define LCDC_GDCINTR_L_GPEMSK_MASK               0x800
#define LCDC_GDCINTR_L_GPEMSK_SHIFT              11 
#define LCDC_GDCINTR_L_GPEMSK_BIT                0x1
#define LCDC_GDCINTR_L_GPEMSK_BITWIDTH           1
// IFURINT bitfiled (RW) Reset=0
#define LCDC_GDCINTR_L_IFURINT_MASK              0x1000
#define LCDC_GDCINTR_L_IFURINT_SHIFT             12 
#define LCDC_GDCINTR_L_IFURINT_BIT               0x1
#define LCDC_GDCINTR_L_IFURINT_BITWIDTH          1
// OFURINT bitfiled (RW) Reset=0
#define LCDC_GDCINTR_L_OFURINT_MASK              0x2000
#define LCDC_GDCINTR_L_OFURINT_SHIFT             13 
#define LCDC_GDCINTR_L_OFURINT_BIT               0x1
#define LCDC_GDCINTR_L_OFURINT_BITWIDTH          1
// VSLINT bitfiled (RW) Reset=0
#define LCDC_GDCINTR_L_VSLINT_MASK               0x4000
#define LCDC_GDCINTR_L_VSLINT_SHIFT              14 
#define LCDC_GDCINTR_L_VSLINT_BIT                0x1
#define LCDC_GDCINTR_L_VSLINT_BITWIDTH           1
// GPEINT bitfiled (RW) Reset=0
#define LCDC_GDCINTR_L_GPEINT_MASK               0x8000
#define LCDC_GDCINTR_L_GPEINT_SHIFT              15 
#define LCDC_GDCINTR_L_GPEINT_BIT                0x1
#define LCDC_GDCINTR_L_GPEINT_BITWIDTH           1
// LINE bitfiled (RW) Reset=0
#define LCDC_GDCINTR_L_LINE_MASK                 0x7FF0000
#define LCDC_GDCINTR_L_LINE_SHIFT                16 
#define LCDC_GDCINTR_L_LINE_BIT                  0x7FF
#define LCDC_GDCINTR_L_LINE_BITWIDTH             11
// DLEMSK bitfiled (RW) Reset=0
#define LCDC_GDCINTR_L_DLEMSK_MASK               0x8000000
#define LCDC_GDCINTR_L_DLEMSK_SHIFT              27 
#define LCDC_GDCINTR_L_DLEMSK_BIT                0x1
#define LCDC_GDCINTR_L_DLEMSK_BITWIDTH           1
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCINTR_L_RESERVED_MASK             0x70000000
#define LCDC_GDCINTR_L_RESERVED_SHIFT            28 
#define LCDC_GDCINTR_L_RESERVED_BIT              0x7
#define LCDC_GDCINTR_L_RESERVED_BITWIDTH         3
// DLEINT bitfiled (RW) Reset=0
#define LCDC_GDCINTR_L_DLEINT_MASK               0x80000000
#define LCDC_GDCINTR_L_DLEINT_SHIFT              31 
#define LCDC_GDCINTR_L_DLEINT_BIT                0x1
#define LCDC_GDCINTR_L_DLEINT_BITWIDTH           1
// GDCINTR_U Register
#define LCDC_GDCINTR_U_OFS                       0x00000144
// APCMSK bitfiled (RW) Reset=0
#define LCDC_GDCINTR_U_APCMSK_MASK               0x1
#define LCDC_GDCINTR_U_APCMSK_SHIFT              0 
#define LCDC_GDCINTR_U_APCMSK_BIT                0x1
#define LCDC_GDCINTR_U_APCMSK_BITWIDTH           1
// APEMSK bitfiled (RW) Reset=0
#define LCDC_GDCINTR_U_APEMSK_MASK               0x2
#define LCDC_GDCINTR_U_APEMSK_SHIFT              1 
#define LCDC_GDCINTR_U_APEMSK_BIT                0x1
#define LCDC_GDCINTR_U_APEMSK_BITWIDTH           1
// reserved2 bitfiled (RO) Reset=0
#define LCDC_GDCINTR_U_RESERVED2_MASK            0xC
#define LCDC_GDCINTR_U_RESERVED2_SHIFT           2 
#define LCDC_GDCINTR_U_RESERVED2_BIT             0x3
#define LCDC_GDCINTR_U_RESERVED2_BITWIDTH        2
// APCINT bitfiled (RW) Reset=0
#define LCDC_GDCINTR_U_APCINT_MASK               0x10
#define LCDC_GDCINTR_U_APCINT_SHIFT              4 
#define LCDC_GDCINTR_U_APCINT_BIT                0x1
#define LCDC_GDCINTR_U_APCINT_BITWIDTH           1
// APEINT bitfiled (RW) Reset=0
#define LCDC_GDCINTR_U_APEINT_MASK               0x20
#define LCDC_GDCINTR_U_APEINT_SHIFT              5 
#define LCDC_GDCINTR_U_APEINT_BIT                0x1
#define LCDC_GDCINTR_U_APEINT_BITWIDTH           1
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCINTR_U_RESERVED_MASK             0xFFFFFFC0
#define LCDC_GDCINTR_U_RESERVED_SHIFT            6 
#define LCDC_GDCINTR_U_RESERVED_BIT              0x3FFFFFF
#define LCDC_GDCINTR_U_RESERVED_BITWIDTH         26
// GDCLARE0_L Register
#define LCDC_GDCLARE0_L_OFS                      0x00000230
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCLARE0_L_RESERVED_MASK            0x1
#define LCDC_GDCLARE0_L_RESERVED_SHIFT           0 
#define LCDC_GDCLARE0_L_RESERVED_BIT             0x1
#define LCDC_GDCLARE0_L_RESERVED_BITWIDTH        1
// SSCROLL bitfiled (RW) Reset=0
#define LCDC_GDCLARE0_L_SSCROLL_MASK             0x6
#define LCDC_GDCLARE0_L_SSCROLL_SHIFT            1 
#define LCDC_GDCLARE0_L_SSCROLL_BIT              0x3
#define LCDC_GDCLARE0_L_SSCROLL_BITWIDTH         2
// SAR bitfiled (RW) Reset=0
#define LCDC_GDCLARE0_L_SAR_MASK                 0xFFFFFFF8
#define LCDC_GDCLARE0_L_SAR_SHIFT                3 
#define LCDC_GDCLARE0_L_SAR_BIT                  0x1FFFFFFF
#define LCDC_GDCLARE0_L_SAR_BITWIDTH             29
// GDCLARE1_L Register
#define LCDC_GDCLARE1_L_OFS                      0x00000238
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCLARE1_L_RESERVED_MASK            0x1
#define LCDC_GDCLARE1_L_RESERVED_SHIFT           0 
#define LCDC_GDCLARE1_L_RESERVED_BIT             0x1
#define LCDC_GDCLARE1_L_RESERVED_BITWIDTH        1
// SSCROLL bitfiled (RW) Reset=0
#define LCDC_GDCLARE1_L_SSCROLL_MASK             0x6
#define LCDC_GDCLARE1_L_SSCROLL_SHIFT            1 
#define LCDC_GDCLARE1_L_SSCROLL_BIT              0x3
#define LCDC_GDCLARE1_L_SSCROLL_BITWIDTH         2
// SAR bitfiled (RW) Reset=0
#define LCDC_GDCLARE1_L_SAR_MASK                 0xFFFFFFF8
#define LCDC_GDCLARE1_L_SAR_SHIFT                3 
#define LCDC_GDCLARE1_L_SAR_BIT                  0x1FFFFFFF
#define LCDC_GDCLARE1_L_SAR_BITWIDTH             29
// GDCWARC_L Register
#define LCDC_GDCWARC_L_OFS                       0x00000240
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCWARC_L_RESERVED_MASK             0x7
#define LCDC_GDCWARC_L_RESERVED_SHIFT            0 
#define LCDC_GDCWARC_L_RESERVED_BIT              0x7
#define LCDC_GDCWARC_L_RESERVED_BITWIDTH         3
// WAR bitfiled (RW) Reset=0
#define LCDC_GDCWARC_L_WAR_MASK                  0xFFFFFFF8
#define LCDC_GDCWARC_L_WAR_SHIFT                 3 
#define LCDC_GDCWARC_L_WAR_BIT                   0x1FFFFFFF
#define LCDC_GDCWARC_L_WAR_BITWIDTH              29
// GDCWARD_L Register
#define LCDC_GDCWARD_L_OFS                       0x00000248
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCWARD_L_RESERVED_MASK             0x7
#define LCDC_GDCWARD_L_RESERVED_SHIFT            0 
#define LCDC_GDCWARD_L_RESERVED_BIT              0x7
#define LCDC_GDCWARD_L_RESERVED_BITWIDTH         3
// WAR bitfiled (RW) Reset=0
#define LCDC_GDCWARD_L_WAR_MASK                  0xFFFFFFF8
#define LCDC_GDCWARD_L_WAR_SHIFT                 3 
#define LCDC_GDCWARD_L_WAR_BIT                   0x1FFFFFFF
#define LCDC_GDCWARD_L_WAR_BITWIDTH              29
// GDCWARE_L Register
#define LCDC_GDCWARE_L_OFS                       0x00000250
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCWARE_L_RESERVED_MASK             0x7
#define LCDC_GDCWARE_L_RESERVED_SHIFT            0 
#define LCDC_GDCWARE_L_RESERVED_BIT              0x7
#define LCDC_GDCWARE_L_RESERVED_BITWIDTH         3
// WAR bitfiled (RW) Reset=0
#define LCDC_GDCWARE_L_WAR_MASK                  0xFFFFFFF8
#define LCDC_GDCWARE_L_WAR_SHIFT                 3 
#define LCDC_GDCWARE_L_WAR_BIT                   0x1FFFFFFF
#define LCDC_GDCWARE_L_WAR_BITWIDTH              29
// GDCWSRC_L Register
#define LCDC_GDCWSRC_L_OFS                       0x00000258
// WVDS bitfiled (RW) Reset=0
#define LCDC_GDCWSRC_L_WVDS_MASK                 0x3FF
#define LCDC_GDCWSRC_L_WVDS_SHIFT                0 
#define LCDC_GDCWSRC_L_WVDS_BIT                  0x3FF
#define LCDC_GDCWSRC_L_WVDS_BITWIDTH             10
// reserved2 bitfiled (RO) Reset=0
#define LCDC_GDCWSRC_L_RESERVED2_MASK            0xFC00
#define LCDC_GDCWSRC_L_RESERVED2_SHIFT           10 
#define LCDC_GDCWSRC_L_RESERVED2_BIT             0x3F
#define LCDC_GDCWSRC_L_RESERVED2_BITWIDTH        6
// WHDS bitfiled (RW) Reset=0
#define LCDC_GDCWSRC_L_WHDS_MASK                 0x7FF0000
#define LCDC_GDCWSRC_L_WHDS_SHIFT                16 
#define LCDC_GDCWSRC_L_WHDS_BIT                  0x7FF
#define LCDC_GDCWSRC_L_WHDS_BITWIDTH             11
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCWSRC_L_RESERVED_MASK             0xF8000000
#define LCDC_GDCWSRC_L_RESERVED_SHIFT            27 
#define LCDC_GDCWSRC_L_RESERVED_BIT              0x1F
#define LCDC_GDCWSRC_L_RESERVED_BITWIDTH         5
// GDCWSRD_L Register
#define LCDC_GDCWSRD_L_OFS                       0x00000260
// WVDS bitfiled (RW) Reset=0
#define LCDC_GDCWSRD_L_WVDS_MASK                 0x3FF
#define LCDC_GDCWSRD_L_WVDS_SHIFT                0 
#define LCDC_GDCWSRD_L_WVDS_BIT                  0x3FF
#define LCDC_GDCWSRD_L_WVDS_BITWIDTH             10
// reserved2 bitfiled (RO) Reset=0
#define LCDC_GDCWSRD_L_RESERVED2_MASK            0xFC00
#define LCDC_GDCWSRD_L_RESERVED2_SHIFT           10 
#define LCDC_GDCWSRD_L_RESERVED2_BIT             0x3F
#define LCDC_GDCWSRD_L_RESERVED2_BITWIDTH        6
// WHDS bitfiled (RW) Reset=0
#define LCDC_GDCWSRD_L_WHDS_MASK                 0x7FF0000
#define LCDC_GDCWSRD_L_WHDS_SHIFT                16 
#define LCDC_GDCWSRD_L_WHDS_BIT                  0x7FF
#define LCDC_GDCWSRD_L_WHDS_BITWIDTH             11
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCWSRD_L_RESERVED_MASK             0xF8000000
#define LCDC_GDCWSRD_L_RESERVED_SHIFT            27 
#define LCDC_GDCWSRD_L_RESERVED_BIT              0x1F
#define LCDC_GDCWSRD_L_RESERVED_BITWIDTH         5
// GDCWSRE_L Register
#define LCDC_GDCWSRE_L_OFS                       0x00000268
// WVDS bitfiled (RW) Reset=0
#define LCDC_GDCWSRE_L_WVDS_MASK                 0x3FF
#define LCDC_GDCWSRE_L_WVDS_SHIFT                0 
#define LCDC_GDCWSRE_L_WVDS_BIT                  0x3FF
#define LCDC_GDCWSRE_L_WVDS_BITWIDTH             10
// reserved2 bitfiled (RO) Reset=0
#define LCDC_GDCWSRE_L_RESERVED2_MASK            0xFC00
#define LCDC_GDCWSRE_L_RESERVED2_SHIFT           10 
#define LCDC_GDCWSRE_L_RESERVED2_BIT             0x3F
#define LCDC_GDCWSRE_L_RESERVED2_BITWIDTH        6
// WHDS bitfiled (RW) Reset=0
#define LCDC_GDCWSRE_L_WHDS_MASK                 0x7FF0000
#define LCDC_GDCWSRE_L_WHDS_SHIFT                16 
#define LCDC_GDCWSRE_L_WHDS_BIT                  0x7FF
#define LCDC_GDCWSRE_L_WHDS_BITWIDTH             11
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCWSRE_L_RESERVED_MASK             0xF8000000
#define LCDC_GDCWSRE_L_RESERVED_SHIFT            27 
#define LCDC_GDCWSRE_L_RESERVED_BIT              0x1F
#define LCDC_GDCWSRE_L_RESERVED_BITWIDTH         5
// GDCWIMRC_L Register
#define LCDC_GDCWIMRC_L_OFS                      0x00000270
// WHEIGHT bitfiled (RW) Reset=0
#define LCDC_GDCWIMRC_L_WHEIGHT_MASK             0x7FF
#define LCDC_GDCWIMRC_L_WHEIGHT_SHIFT            0 
#define LCDC_GDCWIMRC_L_WHEIGHT_BIT              0x7FF
#define LCDC_GDCWIMRC_L_WHEIGHT_BITWIDTH         11
// reserved2 bitfiled (RO) Reset=0
#define LCDC_GDCWIMRC_L_RESERVED2_MASK           0xF800
#define LCDC_GDCWIMRC_L_RESERVED2_SHIFT          11 
#define LCDC_GDCWIMRC_L_RESERVED2_BIT            0x1F
#define LCDC_GDCWIMRC_L_RESERVED2_BITWIDTH       5
// WWIDTH bitfiled (RW) Reset=0
#define LCDC_GDCWIMRC_L_WWIDTH_MASK              0xFFF0000
#define LCDC_GDCWIMRC_L_WWIDTH_SHIFT             16 
#define LCDC_GDCWIMRC_L_WWIDTH_BIT               0xFFF
#define LCDC_GDCWIMRC_L_WWIDTH_BITWIDTH          12
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCWIMRC_L_RESERVED_MASK            0xF0000000
#define LCDC_GDCWIMRC_L_RESERVED_SHIFT           28 
#define LCDC_GDCWIMRC_L_RESERVED_BIT             0xF
#define LCDC_GDCWIMRC_L_RESERVED_BITWIDTH        4
// GDCWIMRD_L Register
#define LCDC_GDCWIMRD_L_OFS                      0x00000278
// WHEIGHT bitfiled (RW) Reset=0
#define LCDC_GDCWIMRD_L_WHEIGHT_MASK             0x7FF
#define LCDC_GDCWIMRD_L_WHEIGHT_SHIFT            0 
#define LCDC_GDCWIMRD_L_WHEIGHT_BIT              0x7FF
#define LCDC_GDCWIMRD_L_WHEIGHT_BITWIDTH         11
// reserved2 bitfiled (RO) Reset=0
#define LCDC_GDCWIMRD_L_RESERVED2_MASK           0xF800
#define LCDC_GDCWIMRD_L_RESERVED2_SHIFT          11 
#define LCDC_GDCWIMRD_L_RESERVED2_BIT            0x1F
#define LCDC_GDCWIMRD_L_RESERVED2_BITWIDTH       5
// WWIDTH bitfiled (RW) Reset=0
#define LCDC_GDCWIMRD_L_WWIDTH_MASK              0xFFF0000
#define LCDC_GDCWIMRD_L_WWIDTH_SHIFT             16 
#define LCDC_GDCWIMRD_L_WWIDTH_BIT               0xFFF
#define LCDC_GDCWIMRD_L_WWIDTH_BITWIDTH          12
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCWIMRD_L_RESERVED_MASK            0xF0000000
#define LCDC_GDCWIMRD_L_RESERVED_SHIFT           28 
#define LCDC_GDCWIMRD_L_RESERVED_BIT             0xF
#define LCDC_GDCWIMRD_L_RESERVED_BITWIDTH        4
// GDCWIMRE_L Register
#define LCDC_GDCWIMRE_L_OFS                      0x00000280
// WHEIGHT bitfiled (RW) Reset=0
#define LCDC_GDCWIMRE_L_WHEIGHT_MASK             0x7FF
#define LCDC_GDCWIMRE_L_WHEIGHT_SHIFT            0 
#define LCDC_GDCWIMRE_L_WHEIGHT_BIT              0x7FF
#define LCDC_GDCWIMRE_L_WHEIGHT_BITWIDTH         11
// reserved2 bitfiled (RO) Reset=0
#define LCDC_GDCWIMRE_L_RESERVED2_MASK           0xF800
#define LCDC_GDCWIMRE_L_RESERVED2_SHIFT          11 
#define LCDC_GDCWIMRE_L_RESERVED2_BIT            0x1F
#define LCDC_GDCWIMRE_L_RESERVED2_BITWIDTH       5
// WWIDTH bitfiled (RW) Reset=0
#define LCDC_GDCWIMRE_L_WWIDTH_MASK              0xFFF0000
#define LCDC_GDCWIMRE_L_WWIDTH_SHIFT             16 
#define LCDC_GDCWIMRE_L_WWIDTH_BIT               0xFFF
#define LCDC_GDCWIMRE_L_WWIDTH_BITWIDTH          12
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCWIMRE_L_RESERVED_MASK            0xF0000000
#define LCDC_GDCWIMRE_L_RESERVED_SHIFT           28 
#define LCDC_GDCWIMRE_L_RESERVED_BIT             0xF
#define LCDC_GDCWIMRE_L_RESERVED_BITWIDTH        4
// GDCSCVRA_L Register
#define LCDC_GDCSCVRA_L_OFS                      0x00000288
// CCV0 bitfiled (RW) Reset=0
#define LCDC_GDCSCVRA_L_CCV0_MASK                0xFFFFFF
#define LCDC_GDCSCVRA_L_CCV0_SHIFT               0 
#define LCDC_GDCSCVRA_L_CCV0_BIT                 0xFFFFFF
#define LCDC_GDCSCVRA_L_CCV0_BITWIDTH            24
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCSCVRA_L_RESERVED_MASK            0x7F000000
#define LCDC_GDCSCVRA_L_RESERVED_SHIFT           24 
#define LCDC_GDCSCVRA_L_RESERVED_BIT             0x7F
#define LCDC_GDCSCVRA_L_RESERVED_BITWIDTH        7
// ACT0 bitfiled (RW) Reset=0
#define LCDC_GDCSCVRA_L_ACT0_MASK                0x80000000
#define LCDC_GDCSCVRA_L_ACT0_SHIFT               31 
#define LCDC_GDCSCVRA_L_ACT0_BIT                 0x1
#define LCDC_GDCSCVRA_L_ACT0_BITWIDTH            1
// GDCSCVRA_U Register
#define LCDC_GDCSCVRA_U_OFS                      0x0000028C
// CCV1 bitfiled (RW) Reset=0
#define LCDC_GDCSCVRA_U_CCV1_MASK                0xFFFFFF
#define LCDC_GDCSCVRA_U_CCV1_SHIFT               0 
#define LCDC_GDCSCVRA_U_CCV1_BIT                 0xFFFFFF
#define LCDC_GDCSCVRA_U_CCV1_BITWIDTH            24
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCSCVRA_U_RESERVED_MASK            0x7F000000
#define LCDC_GDCSCVRA_U_RESERVED_SHIFT           24 
#define LCDC_GDCSCVRA_U_RESERVED_BIT             0x7F
#define LCDC_GDCSCVRA_U_RESERVED_BITWIDTH        7
// ACT1 bitfiled (RW) Reset=0
#define LCDC_GDCSCVRA_U_ACT1_MASK                0x80000000
#define LCDC_GDCSCVRA_U_ACT1_SHIFT               31 
#define LCDC_GDCSCVRA_U_ACT1_BIT                 0x1
#define LCDC_GDCSCVRA_U_ACT1_BITWIDTH            1
// GDCSCVRB_L Register
#define LCDC_GDCSCVRB_L_OFS                      0x00000290
// CCV2 bitfiled (RW) Reset=0
#define LCDC_GDCSCVRB_L_CCV2_MASK                0xFFFFFF
#define LCDC_GDCSCVRB_L_CCV2_SHIFT               0 
#define LCDC_GDCSCVRB_L_CCV2_BIT                 0xFFFFFF
#define LCDC_GDCSCVRB_L_CCV2_BITWIDTH            24
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCSCVRB_L_RESERVED_MASK            0x7F000000
#define LCDC_GDCSCVRB_L_RESERVED_SHIFT           24 
#define LCDC_GDCSCVRB_L_RESERVED_BIT             0x7F
#define LCDC_GDCSCVRB_L_RESERVED_BITWIDTH        7
// ACT2 bitfiled (RW) Reset=0
#define LCDC_GDCSCVRB_L_ACT2_MASK                0x80000000
#define LCDC_GDCSCVRB_L_ACT2_SHIFT               31 
#define LCDC_GDCSCVRB_L_ACT2_BIT                 0x1
#define LCDC_GDCSCVRB_L_ACT2_BITWIDTH            1
// GDCSCVRB_U Register
#define LCDC_GDCSCVRB_U_OFS                      0x00000294
// CCV3 bitfiled (RW) Reset=0
#define LCDC_GDCSCVRB_U_CCV3_MASK                0xFFFFFF
#define LCDC_GDCSCVRB_U_CCV3_SHIFT               0 
#define LCDC_GDCSCVRB_U_CCV3_BIT                 0xFFFFFF
#define LCDC_GDCSCVRB_U_CCV3_BITWIDTH            24
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCSCVRB_U_RESERVED_MASK            0x7F000000
#define LCDC_GDCSCVRB_U_RESERVED_SHIFT           24 
#define LCDC_GDCSCVRB_U_RESERVED_BIT             0x7F
#define LCDC_GDCSCVRB_U_RESERVED_BITWIDTH        7
// ACT3 bitfiled (RW) Reset=0
#define LCDC_GDCSCVRB_U_ACT3_MASK                0x80000000
#define LCDC_GDCSCVRB_U_ACT3_SHIFT               31 
#define LCDC_GDCSCVRB_U_ACT3_BIT                 0x1
#define LCDC_GDCSCVRB_U_ACT3_BITWIDTH            1
// GDCSCVRC_L Register
#define LCDC_GDCSCVRC_L_OFS                      0x00000298
// CCV4 bitfiled (RW) Reset=0
#define LCDC_GDCSCVRC_L_CCV4_MASK                0xFFFFFF
#define LCDC_GDCSCVRC_L_CCV4_SHIFT               0 
#define LCDC_GDCSCVRC_L_CCV4_BIT                 0xFFFFFF
#define LCDC_GDCSCVRC_L_CCV4_BITWIDTH            24
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCSCVRC_L_RESERVED_MASK            0x7F000000
#define LCDC_GDCSCVRC_L_RESERVED_SHIFT           24 
#define LCDC_GDCSCVRC_L_RESERVED_BIT             0x7F
#define LCDC_GDCSCVRC_L_RESERVED_BITWIDTH        7
// ACT4 bitfiled (RW) Reset=0
#define LCDC_GDCSCVRC_L_ACT4_MASK                0x80000000
#define LCDC_GDCSCVRC_L_ACT4_SHIFT               31 
#define LCDC_GDCSCVRC_L_ACT4_BIT                 0x1
#define LCDC_GDCSCVRC_L_ACT4_BITWIDTH            1
// GDCSCVRC_U Register
#define LCDC_GDCSCVRC_U_OFS                      0x0000029C
// CCV5 bitfiled (RW) Reset=0
#define LCDC_GDCSCVRC_U_CCV5_MASK                0xFFFFFF
#define LCDC_GDCSCVRC_U_CCV5_SHIFT               0 
#define LCDC_GDCSCVRC_U_CCV5_BIT                 0xFFFFFF
#define LCDC_GDCSCVRC_U_CCV5_BITWIDTH            24
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCSCVRC_U_RESERVED_MASK            0x7F000000
#define LCDC_GDCSCVRC_U_RESERVED_SHIFT           24 
#define LCDC_GDCSCVRC_U_RESERVED_BIT             0x7F
#define LCDC_GDCSCVRC_U_RESERVED_BITWIDTH        7
// ACT5 bitfiled (RW) Reset=0
#define LCDC_GDCSCVRC_U_ACT5_MASK                0x80000000
#define LCDC_GDCSCVRC_U_ACT5_SHIFT               31 
#define LCDC_GDCSCVRC_U_ACT5_BIT                 0x1
#define LCDC_GDCSCVRC_U_ACT5_BITWIDTH            1
// GDCSCVRD_L Register
#define LCDC_GDCSCVRD_L_OFS                      0x000002A0
// CCV6 bitfiled (RW) Reset=0
#define LCDC_GDCSCVRD_L_CCV6_MASK                0xFFFFFF
#define LCDC_GDCSCVRD_L_CCV6_SHIFT               0 
#define LCDC_GDCSCVRD_L_CCV6_BIT                 0xFFFFFF
#define LCDC_GDCSCVRD_L_CCV6_BITWIDTH            24
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCSCVRD_L_RESERVED_MASK            0x7F000000
#define LCDC_GDCSCVRD_L_RESERVED_SHIFT           24 
#define LCDC_GDCSCVRD_L_RESERVED_BIT             0x7F
#define LCDC_GDCSCVRD_L_RESERVED_BITWIDTH        7
// ACT6 bitfiled (RW) Reset=0
#define LCDC_GDCSCVRD_L_ACT6_MASK                0x80000000
#define LCDC_GDCSCVRD_L_ACT6_SHIFT               31 
#define LCDC_GDCSCVRD_L_ACT6_BIT                 0x1
#define LCDC_GDCSCVRD_L_ACT6_BITWIDTH            1
// GDCSCVRD_U Register
#define LCDC_GDCSCVRD_U_OFS                      0x000002A4
// CCV7 bitfiled (RW) Reset=0
#define LCDC_GDCSCVRD_U_CCV7_MASK                0xFFFFFF
#define LCDC_GDCSCVRD_U_CCV7_SHIFT               0 
#define LCDC_GDCSCVRD_U_CCV7_BIT                 0xFFFFFF
#define LCDC_GDCSCVRD_U_CCV7_BITWIDTH            24
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCSCVRD_U_RESERVED_MASK            0x7F000000
#define LCDC_GDCSCVRD_U_RESERVED_SHIFT           24 
#define LCDC_GDCSCVRD_U_RESERVED_BIT             0x7F
#define LCDC_GDCSCVRD_U_RESERVED_BITWIDTH        7
// ACT7 bitfiled (RW) Reset=0
#define LCDC_GDCSCVRD_U_ACT7_MASK                0x80000000
#define LCDC_GDCSCVRD_U_ACT7_SHIFT               31 
#define LCDC_GDCSCVRD_U_ACT7_BIT                 0x1
#define LCDC_GDCSCVRD_U_ACT7_BITWIDTH            1
// GDCGCAR_L Register
#define LCDC_GDCGCAR_L_OFS                       0x000002A8
// GCAR bitfiled (RO) Reset=0
#define LCDC_GDCGCAR_L_GCAR_MASK                 0xFFFF
#define LCDC_GDCGCAR_L_GCAR_SHIFT                0 
#define LCDC_GDCGCAR_L_GCAR_BIT                  0xFFFF
#define LCDC_GDCGCAR_L_GCAR_BITWIDTH             16
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCGCAR_L_RESERVED_MASK             0xFFFF0000
#define LCDC_GDCGCAR_L_RESERVED_SHIFT            16 
#define LCDC_GDCGCAR_L_RESERVED_BIT              0xFFFF
#define LCDC_GDCGCAR_L_RESERVED_BITWIDTH         16
// GDCDSR_L Register
#define LCDC_GDCDSR_L_OFS                        0x000002B0
// DVS bitfiled (RW) Reset=1011111
#define LCDC_GDCDSR_L_DVS_MASK                   0x3FF
#define LCDC_GDCDSR_L_DVS_SHIFT                  0 
#define LCDC_GDCDSR_L_DVS_BIT                    0x3FF
#define LCDC_GDCDSR_L_DVS_BITWIDTH               10
// reserved2 bitfiled (RO) Reset=0
#define LCDC_GDCDSR_L_RESERVED2_MASK             0xFC00
#define LCDC_GDCDSR_L_RESERVED2_SHIFT            10 
#define LCDC_GDCDSR_L_RESERVED2_BIT              0x3F
#define LCDC_GDCDSR_L_RESERVED2_BITWIDTH         6
// DHS bitfiled (RW) Reset=11000000
#define LCDC_GDCDSR_L_DHS_MASK                   0x7FF0000
#define LCDC_GDCDSR_L_DHS_SHIFT                  16 
#define LCDC_GDCDSR_L_DHS_BIT                    0x7FF
#define LCDC_GDCDSR_L_DHS_BITWIDTH               11
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCDSR_L_RESERVED_MASK              0xF8000000
#define LCDC_GDCDSR_L_RESERVED_SHIFT             27 
#define LCDC_GDCDSR_L_RESERVED_BIT               0x1F
#define LCDC_GDCDSR_L_RESERVED_BITWIDTH          5
// GDCDIMR_L Register
#define LCDC_GDCDIMR_L_OFS                       0x000002B8
// DHEIGHT bitfiled (RW) Reset=111100000
#define LCDC_GDCDIMR_L_DHEIGHT_MASK              0x7FF
#define LCDC_GDCDIMR_L_DHEIGHT_SHIFT             0 
#define LCDC_GDCDIMR_L_DHEIGHT_BIT               0x7FF
#define LCDC_GDCDIMR_L_DHEIGHT_BITWIDTH          11
// reserved2 bitfiled (RO) Reset=0
#define LCDC_GDCDIMR_L_RESERVED2_MASK            0xF800
#define LCDC_GDCDIMR_L_RESERVED2_SHIFT           11 
#define LCDC_GDCDIMR_L_RESERVED2_BIT             0x1F
#define LCDC_GDCDIMR_L_RESERVED2_BITWIDTH        5
// DWIDTH bitfiled (RW) Reset=1010000000
#define LCDC_GDCDIMR_L_DWIDTH_MASK               0xFFF0000
#define LCDC_GDCDIMR_L_DWIDTH_SHIFT              16 
#define LCDC_GDCDIMR_L_DWIDTH_BIT                0xFFF
#define LCDC_GDCDIMR_L_DWIDTH_BITWIDTH           12
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCDIMR_L_RESERVED_MASK             0xF0000000
#define LCDC_GDCDIMR_L_RESERVED_SHIFT            28 
#define LCDC_GDCDIMR_L_RESERVED_BIT              0xF
#define LCDC_GDCDIMR_L_RESERVED_BITWIDTH         4
// GDCPROTR_L Register
#define LCDC_GDCPROTR_L_OFS                      0x000002C0
// GDCWPL bitfiled (RW) Reset=0
#define LCDC_GDCPROTR_L_GDCWPL_MASK              0x3
#define LCDC_GDCPROTR_L_GDCWPL_SHIFT             0 
#define LCDC_GDCPROTR_L_GDCWPL_BIT               0x3
#define LCDC_GDCPROTR_L_GDCWPL_BITWIDTH          2
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCPROTR_L_RESERVED_MASK            0xFFFFFFFC
#define LCDC_GDCPROTR_L_RESERVED_SHIFT           2 
#define LCDC_GDCPROTR_L_RESERVED_BIT             0x3FFFFFFF
#define LCDC_GDCPROTR_L_RESERVED_BITWIDTH        30
// GDCGBEAR_L Register
#define LCDC_GDCGBEAR_L_OFS                      0x000002C8
// GBADDR bitfiled (RO) Reset=0
#define LCDC_GDCGBEAR_L_GBADDR_MASK              0xFFFFFFFF
#define LCDC_GDCGBEAR_L_GBADDR_SHIFT             0 
#define LCDC_GDCGBEAR_L_GBADDR_BIT               0xFFFFFFFF
#define LCDC_GDCGBEAR_L_GBADDR_BITWIDTH          32
// GDCGBECR_L Register
#define LCDC_GDCGBECR_L_OFS                      0x000002D0
// WR bitfiled (RO) Reset=0
#define LCDC_GDCGBECR_L_WR_MASK                  0x1
#define LCDC_GDCGBECR_L_WR_SHIFT                 0 
#define LCDC_GDCGBECR_L_WR_BIT                   0x1
#define LCDC_GDCGBECR_L_WR_BITWIDTH              1
// BTYPE bitfiled (RO) Reset=0
#define LCDC_GDCGBECR_L_BTYPE_MASK               0x2
#define LCDC_GDCGBECR_L_BTYPE_SHIFT              1 
#define LCDC_GDCGBECR_L_BTYPE_BIT                0x1
#define LCDC_GDCGBECR_L_BTYPE_BITWIDTH           1
// BSIZE bitfiled (RO) Reset=0
#define LCDC_GDCGBECR_L_BSIZE_MASK               0x1C
#define LCDC_GDCGBECR_L_BSIZE_SHIFT              2 
#define LCDC_GDCGBECR_L_BSIZE_BIT                0x7
#define LCDC_GDCGBECR_L_BSIZE_BITWIDTH           3
// RTYPE bitfiled (RO) Reset=0
#define LCDC_GDCGBECR_L_RTYPE_MASK               0x60
#define LCDC_GDCGBECR_L_RTYPE_SHIFT              5 
#define LCDC_GDCGBECR_L_RTYPE_BIT                0x3
#define LCDC_GDCGBECR_L_RTYPE_BITWIDTH           2
// reserved2 bitfiled (RO) Reset=0
#define LCDC_GDCGBECR_L_RESERVED2_MASK           0x80
#define LCDC_GDCGBECR_L_RESERVED2_SHIFT          7 
#define LCDC_GDCGBECR_L_RESERVED2_BIT            0x1
#define LCDC_GDCGBECR_L_RESERVED2_BITWIDTH       1
// BEN bitfiled (RO) Reset=0
#define LCDC_GDCGBECR_L_BEN_MASK                 0xFF00
#define LCDC_GDCGBECR_L_BEN_SHIFT                8 
#define LCDC_GDCGBECR_L_BEN_BIT                  0xFF
#define LCDC_GDCGBECR_L_BEN_BITWIDTH             8
// ID bitfiled (RO) Reset=0
#define LCDC_GDCGBECR_L_ID_MASK                  0xF0000
#define LCDC_GDCGBECR_L_ID_SHIFT                 16 
#define LCDC_GDCGBECR_L_ID_BIT                   0xF
#define LCDC_GDCGBECR_L_ID_BITWIDTH              4
// LEN bitfiled (RO) Reset=0
#define LCDC_GDCGBECR_L_LEN_MASK                 0xF00000
#define LCDC_GDCGBECR_L_LEN_SHIFT                20 
#define LCDC_GDCGBECR_L_LEN_BIT                  0xF
#define LCDC_GDCGBECR_L_LEN_BITWIDTH             4
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCGBECR_L_RESERVED_MASK            0xFF000000
#define LCDC_GDCGBECR_L_RESERVED_SHIFT           24 
#define LCDC_GDCGBECR_L_RESERVED_BIT             0xFF
#define LCDC_GDCGBECR_L_RESERVED_BITWIDTH        8
// APCCR_L Register
#define LCDC_APCCR_L_OFS                         0x00000300
// CHKFR bitfiled (RW) Reset=10100
#define LCDC_APCCR_L_CHKFR_MASK                  0x7F
#define LCDC_APCCR_L_CHKFR_SHIFT                 0 
#define LCDC_APCCR_L_CHKFR_BIT                   0x7F
#define LCDC_APCCR_L_CHKFR_BITWIDTH              7
// CHKERR bitfiled (RO) Reset=0
#define LCDC_APCCR_L_CHKERR_MASK                 0x80
#define LCDC_APCCR_L_CHKERR_SHIFT                7 
#define LCDC_APCCR_L_CHKERR_BIT                  0x1
#define LCDC_APCCR_L_CHKERR_BITWIDTH             1
// reserved bitfiled (RO) Reset=0
#define LCDC_APCCR_L_RESERVED_MASK               0x3FFFFF00
#define LCDC_APCCR_L_RESERVED_SHIFT              8 
#define LCDC_APCCR_L_RESERVED_BIT                0x3FFFFF
#define LCDC_APCCR_L_RESERVED_BITWIDTH           22
// AUTO bitfiled (RW) Reset=0
#define LCDC_APCCR_L_AUTO_MASK                   0x40000000
#define LCDC_APCCR_L_AUTO_SHIFT                  30 
#define LCDC_APCCR_L_AUTO_BIT                    0x1
#define LCDC_APCCR_L_AUTO_BITWIDTH               1
// APCON bitfiled (RW) Reset=0
#define LCDC_APCCR_L_APCON_MASK                  0x80000000
#define LCDC_APCCR_L_APCON_SHIFT                 31 
#define LCDC_APCCR_L_APCON_BIT                   0x1
#define LCDC_APCCR_L_APCON_BITWIDTH              1
// APCCR_U Register
#define LCDC_APCCR_U_OFS                         0x00000304
// PG bitfiled (RW) Reset=100011
#define LCDC_APCCR_U_PG_MASK                     0x7F
#define LCDC_APCCR_U_PG_SHIFT                    0 
#define LCDC_APCCR_U_PG_BIT                      0x7F
#define LCDC_APCCR_U_PG_BITWIDTH                 7
// reserved2 bitfiled (RO) Reset=0
#define LCDC_APCCR_U_RESERVED2_MASK              0x80
#define LCDC_APCCR_U_RESERVED2_SHIFT             7 
#define LCDC_APCCR_U_RESERVED2_BIT               0x1
#define LCDC_APCCR_U_RESERVED2_BITWIDTH          1
// reserved bitfiled (RO) Reset=0
#define LCDC_APCCR_U_RESERVED_MASK               0xFFFFFF00
#define LCDC_APCCR_U_RESERVED_SHIFT              8 
#define LCDC_APCCR_U_RESERVED_BIT                0xFFFFFF
#define LCDC_APCCR_U_RESERVED_BITWIDTH           24
// APCCWR_L Register
#define LCDC_APCCWR_L_OFS                        0x00000308
// VCWS bitfiled (RW) Reset=1
#define LCDC_APCCWR_L_VCWS_MASK                  0x7FF
#define LCDC_APCCWR_L_VCWS_SHIFT                 0 
#define LCDC_APCCWR_L_VCWS_BIT                   0x7FF
#define LCDC_APCCWR_L_VCWS_BITWIDTH              11
// reserved2 bitfiled (RO) Reset=0
#define LCDC_APCCWR_L_RESERVED2_MASK             0xF800
#define LCDC_APCCWR_L_RESERVED2_SHIFT            11 
#define LCDC_APCCWR_L_RESERVED2_BIT              0x1F
#define LCDC_APCCWR_L_RESERVED2_BITWIDTH         5
// HCWS bitfiled (RW) Reset=1
#define LCDC_APCCWR_L_HCWS_MASK                  0xFFF0000
#define LCDC_APCCWR_L_HCWS_SHIFT                 16 
#define LCDC_APCCWR_L_HCWS_BIT                   0xFFF
#define LCDC_APCCWR_L_HCWS_BITWIDTH              12
// reserved bitfiled (RO) Reset=0
#define LCDC_APCCWR_L_RESERVED_MASK              0xF0000000
#define LCDC_APCCWR_L_RESERVED_SHIFT             28 
#define LCDC_APCCWR_L_RESERVED_BIT               0xF
#define LCDC_APCCWR_L_RESERVED_BITWIDTH          4
// APCCWR_U Register
#define LCDC_APCCWR_U_OFS                        0x0000030C
// CWHEIGHT bitfiled (RW) Reset=1
#define LCDC_APCCWR_U_CWHEIGHT_MASK              0x7F
#define LCDC_APCCWR_U_CWHEIGHT_SHIFT             0 
#define LCDC_APCCWR_U_CWHEIGHT_BIT               0x7F
#define LCDC_APCCWR_U_CWHEIGHT_BITWIDTH          7
// reserved2 bitfiled (RO) Reset=0
#define LCDC_APCCWR_U_RESERVED2_MASK             0xFF80
#define LCDC_APCCWR_U_RESERVED2_SHIFT            7 
#define LCDC_APCCWR_U_RESERVED2_BIT              0x1FF
#define LCDC_APCCWR_U_RESERVED2_BITWIDTH         9
// CWWIDTH bitfiled (RW) Reset=1000
#define LCDC_APCCWR_U_CWWIDTH_MASK               0xFF0000
#define LCDC_APCCWR_U_CWWIDTH_SHIFT              16 
#define LCDC_APCCWR_U_CWWIDTH_BIT                0xFF
#define LCDC_APCCWR_U_CWWIDTH_BITWIDTH           8
// reserved bitfiled (RO) Reset=0
#define LCDC_APCCWR_U_RESERVED_MASK              0xFF000000
#define LCDC_APCCWR_U_RESERVED_SHIFT             24 
#define LCDC_APCCWR_U_RESERVED_BIT               0xFF
#define LCDC_APCCWR_U_RESERVED_BITWIDTH          8
// APCCSR_L Register
#define LCDC_APCCSR_L_OFS                        0x00000310
// CURCHKSUM bitfiled (RO) Reset=0
#define LCDC_APCCSR_L_CURCHKSUM_MASK             0x3FFFFF
#define LCDC_APCCSR_L_CURCHKSUM_SHIFT            0 
#define LCDC_APCCSR_L_CURCHKSUM_BIT              0x3FFFFF
#define LCDC_APCCSR_L_CURCHKSUM_BITWIDTH         22
// reserved bitfiled (RO) Reset=0
#define LCDC_APCCSR_L_RESERVED_MASK              0xFFC00000
#define LCDC_APCCSR_L_RESERVED_SHIFT             22 
#define LCDC_APCCSR_L_RESERVED_BIT               0x3FF
#define LCDC_APCCSR_L_RESERVED_BITWIDTH          10
// APCCSR_U Register
#define LCDC_APCCSR_U_OFS                        0x00000314
// EXPCHKSUM bitfiled (RW) Reset=0
#define LCDC_APCCSR_U_EXPCHKSUM_MASK             0x3FFFFF
#define LCDC_APCCSR_U_EXPCHKSUM_SHIFT            0 
#define LCDC_APCCSR_U_EXPCHKSUM_BIT              0x3FFFFF
#define LCDC_APCCSR_U_EXPCHKSUM_BITWIDTH         22
// reserved bitfiled (RO) Reset=0
#define LCDC_APCCSR_U_RESERVED_MASK              0xFFC00000
#define LCDC_APCCSR_U_RESERVED_SHIFT             22 
#define LCDC_APCCSR_U_RESERVED_BIT               0x3FF
#define LCDC_APCCSR_U_RESERVED_BITWIDTH          10
// APCPVR_L Register
#define LCDC_APCPVR_L_OFS                        0x00000318
// BLUEL bitfiled (RO) Reset=0
#define LCDC_APCPVR_L_BLUEL_MASK                 0xFF
#define LCDC_APCPVR_L_BLUEL_SHIFT                0 
#define LCDC_APCPVR_L_BLUEL_BIT                  0xFF
#define LCDC_APCPVR_L_BLUEL_BITWIDTH             8
// GREENL bitfiled (RO) Reset=0
#define LCDC_APCPVR_L_GREENL_MASK                0xFF00
#define LCDC_APCPVR_L_GREENL_SHIFT               8 
#define LCDC_APCPVR_L_GREENL_BIT                 0xFF
#define LCDC_APCPVR_L_GREENL_BITWIDTH            8
// REDL bitfiled (RO) Reset=0
#define LCDC_APCPVR_L_REDL_MASK                  0xFF0000
#define LCDC_APCPVR_L_REDL_SHIFT                 16 
#define LCDC_APCPVR_L_REDL_BIT                   0xFF
#define LCDC_APCPVR_L_REDL_BITWIDTH              8
// reserved bitfiled (RO) Reset=0
#define LCDC_APCPVR_L_RESERVED_MASK              0xFF000000
#define LCDC_APCPVR_L_RESERVED_SHIFT             24 
#define LCDC_APCPVR_L_RESERVED_BIT               0xFF
#define LCDC_APCPVR_L_RESERVED_BITWIDTH          8
// APCPVR_U Register
#define LCDC_APCPVR_U_OFS                        0x0000031C
// BLUEP bitfiled (RO) Reset=0
#define LCDC_APCPVR_U_BLUEP_MASK                 0xFF
#define LCDC_APCPVR_U_BLUEP_SHIFT                0 
#define LCDC_APCPVR_U_BLUEP_BIT                  0xFF
#define LCDC_APCPVR_U_BLUEP_BITWIDTH             8
// GREENP bitfiled (RO) Reset=0
#define LCDC_APCPVR_U_GREENP_MASK                0xFF00
#define LCDC_APCPVR_U_GREENP_SHIFT               8 
#define LCDC_APCPVR_U_GREENP_BIT                 0xFF
#define LCDC_APCPVR_U_GREENP_BITWIDTH            8
// REDP bitfiled (RO) Reset=0
#define LCDC_APCPVR_U_REDP_MASK                  0xFF0000
#define LCDC_APCPVR_U_REDP_SHIFT                 16 
#define LCDC_APCPVR_U_REDP_BIT                   0xFF
#define LCDC_APCPVR_U_REDP_BITWIDTH              8
// reserved bitfiled (RO) Reset=0
#define LCDC_APCPVR_U_RESERVED_MASK              0xFF000000
#define LCDC_APCPVR_U_RESERVED_SHIFT             24 
#define LCDC_APCPVR_U_RESERVED_BIT               0xFF
#define LCDC_APCPVR_U_RESERVED_BITWIDTH          8
// APCPROTR_L Register
#define LCDC_APCPROTR_L_OFS                      0x00000320
// APCWPL bitfiled (RW) Reset=0
#define LCDC_APCPROTR_L_APCWPL_MASK              0x3
#define LCDC_APCPROTR_L_APCWPL_SHIFT             0 
#define LCDC_APCPROTR_L_APCWPL_BIT               0x3
#define LCDC_APCPROTR_L_APCWPL_BITWIDTH          2
// reserved bitfiled (RO) Reset=0
#define LCDC_APCPROTR_L_RESERVED_MASK            0xFFFFFFFC
#define LCDC_APCPROTR_L_RESERVED_SHIFT           2 
#define LCDC_APCPROTR_L_RESERVED_BIT             0x3FFFFFFF
#define LCDC_APCPROTR_L_RESERVED_BITWIDTH        30
// GDCCCLUTR0_L Register
#define LCDC_GDCCCLUTR0_L_OFS                    0x00000400
// CLUTR0 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR0_L_CLUTR0_MASK            0xFF
#define LCDC_GDCCCLUTR0_L_CLUTR0_SHIFT           0 
#define LCDC_GDCCCLUTR0_L_CLUTR0_BIT             0xFF
#define LCDC_GDCCCLUTR0_L_CLUTR0_BITWIDTH        8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR0_L_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTR0_L_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTR0_L_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTR0_L_RESERVED_BITWIDTH      24
// GDCCCLUTR0_U Register
#define LCDC_GDCCCLUTR0_U_OFS                    0x00000404
// CLUTR1 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR0_U_CLUTR1_MASK            0xFF
#define LCDC_GDCCCLUTR0_U_CLUTR1_SHIFT           0 
#define LCDC_GDCCCLUTR0_U_CLUTR1_BIT             0xFF
#define LCDC_GDCCCLUTR0_U_CLUTR1_BITWIDTH        8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR0_U_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTR0_U_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTR0_U_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTR0_U_RESERVED_BITWIDTH      24
// GDCCCLUTR1_L Register
#define LCDC_GDCCCLUTR1_L_OFS                    0x00000408
// CLUTR2 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR1_L_CLUTR2_MASK            0xFF
#define LCDC_GDCCCLUTR1_L_CLUTR2_SHIFT           0 
#define LCDC_GDCCCLUTR1_L_CLUTR2_BIT             0xFF
#define LCDC_GDCCCLUTR1_L_CLUTR2_BITWIDTH        8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR1_L_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTR1_L_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTR1_L_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTR1_L_RESERVED_BITWIDTH      24
// GDCCCLUTR1_U Register
#define LCDC_GDCCCLUTR1_U_OFS                    0x0000040C
// CLUTR3 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR1_U_CLUTR3_MASK            0xFF
#define LCDC_GDCCCLUTR1_U_CLUTR3_SHIFT           0 
#define LCDC_GDCCCLUTR1_U_CLUTR3_BIT             0xFF
#define LCDC_GDCCCLUTR1_U_CLUTR3_BITWIDTH        8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR1_U_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTR1_U_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTR1_U_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTR1_U_RESERVED_BITWIDTH      24
// GDCCCLUTR2_L Register
#define LCDC_GDCCCLUTR2_L_OFS                    0x00000410
// CLUTR4 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR2_L_CLUTR4_MASK            0xFF
#define LCDC_GDCCCLUTR2_L_CLUTR4_SHIFT           0 
#define LCDC_GDCCCLUTR2_L_CLUTR4_BIT             0xFF
#define LCDC_GDCCCLUTR2_L_CLUTR4_BITWIDTH        8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR2_L_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTR2_L_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTR2_L_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTR2_L_RESERVED_BITWIDTH      24
// GDCCCLUTR2_U Register
#define LCDC_GDCCCLUTR2_U_OFS                    0x00000414
// CLUTR5 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR2_U_CLUTR5_MASK            0xFF
#define LCDC_GDCCCLUTR2_U_CLUTR5_SHIFT           0 
#define LCDC_GDCCCLUTR2_U_CLUTR5_BIT             0xFF
#define LCDC_GDCCCLUTR2_U_CLUTR5_BITWIDTH        8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR2_U_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTR2_U_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTR2_U_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTR2_U_RESERVED_BITWIDTH      24
// GDCCCLUTR3_L Register
#define LCDC_GDCCCLUTR3_L_OFS                    0x00000418
// CLUTR6 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR3_L_CLUTR6_MASK            0xFF
#define LCDC_GDCCCLUTR3_L_CLUTR6_SHIFT           0 
#define LCDC_GDCCCLUTR3_L_CLUTR6_BIT             0xFF
#define LCDC_GDCCCLUTR3_L_CLUTR6_BITWIDTH        8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR3_L_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTR3_L_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTR3_L_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTR3_L_RESERVED_BITWIDTH      24
// GDCCCLUTR3_U Register
#define LCDC_GDCCCLUTR3_U_OFS                    0x0000041C
// CLUTR7 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR3_U_CLUTR7_MASK            0xFF
#define LCDC_GDCCCLUTR3_U_CLUTR7_SHIFT           0 
#define LCDC_GDCCCLUTR3_U_CLUTR7_BIT             0xFF
#define LCDC_GDCCCLUTR3_U_CLUTR7_BITWIDTH        8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR3_U_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTR3_U_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTR3_U_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTR3_U_RESERVED_BITWIDTH      24
// GDCCCLUTR4_L Register
#define LCDC_GDCCCLUTR4_L_OFS                    0x00000420
// CLUTR8 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR4_L_CLUTR8_MASK            0xFF
#define LCDC_GDCCCLUTR4_L_CLUTR8_SHIFT           0 
#define LCDC_GDCCCLUTR4_L_CLUTR8_BIT             0xFF
#define LCDC_GDCCCLUTR4_L_CLUTR8_BITWIDTH        8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR4_L_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTR4_L_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTR4_L_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTR4_L_RESERVED_BITWIDTH      24
// GDCCCLUTR4_U Register
#define LCDC_GDCCCLUTR4_U_OFS                    0x00000424
// CLUTR9 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR4_U_CLUTR9_MASK            0xFF
#define LCDC_GDCCCLUTR4_U_CLUTR9_SHIFT           0 
#define LCDC_GDCCCLUTR4_U_CLUTR9_BIT             0xFF
#define LCDC_GDCCCLUTR4_U_CLUTR9_BITWIDTH        8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR4_U_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTR4_U_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTR4_U_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTR4_U_RESERVED_BITWIDTH      24
// GDCCCLUTR5_L Register
#define LCDC_GDCCCLUTR5_L_OFS                    0x00000428
// CLUTR10 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR5_L_CLUTR10_MASK           0xFF
#define LCDC_GDCCCLUTR5_L_CLUTR10_SHIFT          0 
#define LCDC_GDCCCLUTR5_L_CLUTR10_BIT            0xFF
#define LCDC_GDCCCLUTR5_L_CLUTR10_BITWIDTH       8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR5_L_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTR5_L_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTR5_L_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTR5_L_RESERVED_BITWIDTH      24
// GDCCCLUTR5_U Register
#define LCDC_GDCCCLUTR5_U_OFS                    0x0000042C
// CLUTR11 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR5_U_CLUTR11_MASK           0xFF
#define LCDC_GDCCCLUTR5_U_CLUTR11_SHIFT          0 
#define LCDC_GDCCCLUTR5_U_CLUTR11_BIT            0xFF
#define LCDC_GDCCCLUTR5_U_CLUTR11_BITWIDTH       8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR5_U_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTR5_U_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTR5_U_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTR5_U_RESERVED_BITWIDTH      24
// GDCCCLUTR6_L Register
#define LCDC_GDCCCLUTR6_L_OFS                    0x00000430
// CLUTR12 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR6_L_CLUTR12_MASK           0xFF
#define LCDC_GDCCCLUTR6_L_CLUTR12_SHIFT          0 
#define LCDC_GDCCCLUTR6_L_CLUTR12_BIT            0xFF
#define LCDC_GDCCCLUTR6_L_CLUTR12_BITWIDTH       8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR6_L_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTR6_L_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTR6_L_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTR6_L_RESERVED_BITWIDTH      24
// GDCCCLUTR6_U Register
#define LCDC_GDCCCLUTR6_U_OFS                    0x00000434
// CLUTR13 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR6_U_CLUTR13_MASK           0xFF
#define LCDC_GDCCCLUTR6_U_CLUTR13_SHIFT          0 
#define LCDC_GDCCCLUTR6_U_CLUTR13_BIT            0xFF
#define LCDC_GDCCCLUTR6_U_CLUTR13_BITWIDTH       8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR6_U_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTR6_U_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTR6_U_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTR6_U_RESERVED_BITWIDTH      24
// GDCCCLUTR7_L Register
#define LCDC_GDCCCLUTR7_L_OFS                    0x00000438
// CLUTR14 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR7_L_CLUTR14_MASK           0xFF
#define LCDC_GDCCCLUTR7_L_CLUTR14_SHIFT          0 
#define LCDC_GDCCCLUTR7_L_CLUTR14_BIT            0xFF
#define LCDC_GDCCCLUTR7_L_CLUTR14_BITWIDTH       8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR7_L_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTR7_L_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTR7_L_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTR7_L_RESERVED_BITWIDTH      24
// GDCCCLUTR7_U Register
#define LCDC_GDCCCLUTR7_U_OFS                    0x0000043C
// CLUTR15 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR7_U_CLUTR15_MASK           0xFF
#define LCDC_GDCCCLUTR7_U_CLUTR15_SHIFT          0 
#define LCDC_GDCCCLUTR7_U_CLUTR15_BIT            0xFF
#define LCDC_GDCCCLUTR7_U_CLUTR15_BITWIDTH       8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR7_U_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTR7_U_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTR7_U_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTR7_U_RESERVED_BITWIDTH      24
// GDCCCLUTR8_L Register
#define LCDC_GDCCCLUTR8_L_OFS                    0x00000440
// CLUTR16 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR8_L_CLUTR16_MASK           0xFF
#define LCDC_GDCCCLUTR8_L_CLUTR16_SHIFT          0 
#define LCDC_GDCCCLUTR8_L_CLUTR16_BIT            0xFF
#define LCDC_GDCCCLUTR8_L_CLUTR16_BITWIDTH       8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR8_L_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTR8_L_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTR8_L_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTR8_L_RESERVED_BITWIDTH      24
// GDCCCLUTR8_U Register
#define LCDC_GDCCCLUTR8_U_OFS                    0x00000444
// CLUTR17 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR8_U_CLUTR17_MASK           0xFF
#define LCDC_GDCCCLUTR8_U_CLUTR17_SHIFT          0 
#define LCDC_GDCCCLUTR8_U_CLUTR17_BIT            0xFF
#define LCDC_GDCCCLUTR8_U_CLUTR17_BITWIDTH       8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR8_U_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTR8_U_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTR8_U_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTR8_U_RESERVED_BITWIDTH      24
// GDCCCLUTR9_L Register
#define LCDC_GDCCCLUTR9_L_OFS                    0x00000448
// CLUTR18 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR9_L_CLUTR18_MASK           0xFF
#define LCDC_GDCCCLUTR9_L_CLUTR18_SHIFT          0 
#define LCDC_GDCCCLUTR9_L_CLUTR18_BIT            0xFF
#define LCDC_GDCCCLUTR9_L_CLUTR18_BITWIDTH       8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR9_L_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTR9_L_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTR9_L_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTR9_L_RESERVED_BITWIDTH      24
// GDCCCLUTR9_U Register
#define LCDC_GDCCCLUTR9_U_OFS                    0x0000044C
// CLUTR19 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR9_U_CLUTR19_MASK           0xFF
#define LCDC_GDCCCLUTR9_U_CLUTR19_SHIFT          0 
#define LCDC_GDCCCLUTR9_U_CLUTR19_BIT            0xFF
#define LCDC_GDCCCLUTR9_U_CLUTR19_BITWIDTH       8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR9_U_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTR9_U_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTR9_U_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTR9_U_RESERVED_BITWIDTH      24
// GDCCCLUTR10_L Register
#define LCDC_GDCCCLUTR10_L_OFS                   0x00000450
// CLUTR20 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR10_L_CLUTR20_MASK          0xFF
#define LCDC_GDCCCLUTR10_L_CLUTR20_SHIFT         0 
#define LCDC_GDCCCLUTR10_L_CLUTR20_BIT           0xFF
#define LCDC_GDCCCLUTR10_L_CLUTR20_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR10_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR10_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR10_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR10_L_RESERVED_BITWIDTH     24
// GDCCCLUTR10_U Register
#define LCDC_GDCCCLUTR10_U_OFS                   0x00000454
// CLUTR21 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR10_U_CLUTR21_MASK          0xFF
#define LCDC_GDCCCLUTR10_U_CLUTR21_SHIFT         0 
#define LCDC_GDCCCLUTR10_U_CLUTR21_BIT           0xFF
#define LCDC_GDCCCLUTR10_U_CLUTR21_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR10_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR10_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR10_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR10_U_RESERVED_BITWIDTH     24
// GDCCCLUTR11_L Register
#define LCDC_GDCCCLUTR11_L_OFS                   0x00000458
// CLUTR22 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR11_L_CLUTR22_MASK          0xFF
#define LCDC_GDCCCLUTR11_L_CLUTR22_SHIFT         0 
#define LCDC_GDCCCLUTR11_L_CLUTR22_BIT           0xFF
#define LCDC_GDCCCLUTR11_L_CLUTR22_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR11_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR11_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR11_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR11_L_RESERVED_BITWIDTH     24
// GDCCCLUTR11_U Register
#define LCDC_GDCCCLUTR11_U_OFS                   0x0000045C
// CLUTR23 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR11_U_CLUTR23_MASK          0xFF
#define LCDC_GDCCCLUTR11_U_CLUTR23_SHIFT         0 
#define LCDC_GDCCCLUTR11_U_CLUTR23_BIT           0xFF
#define LCDC_GDCCCLUTR11_U_CLUTR23_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR11_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR11_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR11_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR11_U_RESERVED_BITWIDTH     24
// GDCCCLUTR12_L Register
#define LCDC_GDCCCLUTR12_L_OFS                   0x00000460
// CLUTR24 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR12_L_CLUTR24_MASK          0xFF
#define LCDC_GDCCCLUTR12_L_CLUTR24_SHIFT         0 
#define LCDC_GDCCCLUTR12_L_CLUTR24_BIT           0xFF
#define LCDC_GDCCCLUTR12_L_CLUTR24_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR12_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR12_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR12_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR12_L_RESERVED_BITWIDTH     24
// GDCCCLUTR12_U Register
#define LCDC_GDCCCLUTR12_U_OFS                   0x00000464
// CLUTR25 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR12_U_CLUTR25_MASK          0xFF
#define LCDC_GDCCCLUTR12_U_CLUTR25_SHIFT         0 
#define LCDC_GDCCCLUTR12_U_CLUTR25_BIT           0xFF
#define LCDC_GDCCCLUTR12_U_CLUTR25_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR12_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR12_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR12_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR12_U_RESERVED_BITWIDTH     24
// GDCCCLUTR13_L Register
#define LCDC_GDCCCLUTR13_L_OFS                   0x00000468
// CLUTR26 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR13_L_CLUTR26_MASK          0xFF
#define LCDC_GDCCCLUTR13_L_CLUTR26_SHIFT         0 
#define LCDC_GDCCCLUTR13_L_CLUTR26_BIT           0xFF
#define LCDC_GDCCCLUTR13_L_CLUTR26_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR13_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR13_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR13_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR13_L_RESERVED_BITWIDTH     24
// GDCCCLUTR13_U Register
#define LCDC_GDCCCLUTR13_U_OFS                   0x0000046C
// CLUTR27 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR13_U_CLUTR27_MASK          0xFF
#define LCDC_GDCCCLUTR13_U_CLUTR27_SHIFT         0 
#define LCDC_GDCCCLUTR13_U_CLUTR27_BIT           0xFF
#define LCDC_GDCCCLUTR13_U_CLUTR27_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR13_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR13_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR13_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR13_U_RESERVED_BITWIDTH     24
// GDCCCLUTR14_L Register
#define LCDC_GDCCCLUTR14_L_OFS                   0x00000470
// CLUTR28 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR14_L_CLUTR28_MASK          0xFF
#define LCDC_GDCCCLUTR14_L_CLUTR28_SHIFT         0 
#define LCDC_GDCCCLUTR14_L_CLUTR28_BIT           0xFF
#define LCDC_GDCCCLUTR14_L_CLUTR28_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR14_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR14_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR14_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR14_L_RESERVED_BITWIDTH     24
// GDCCCLUTR14_U Register
#define LCDC_GDCCCLUTR14_U_OFS                   0x00000474
// CLUTR29 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR14_U_CLUTR29_MASK          0xFF
#define LCDC_GDCCCLUTR14_U_CLUTR29_SHIFT         0 
#define LCDC_GDCCCLUTR14_U_CLUTR29_BIT           0xFF
#define LCDC_GDCCCLUTR14_U_CLUTR29_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR14_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR14_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR14_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR14_U_RESERVED_BITWIDTH     24
// GDCCCLUTR15_L Register
#define LCDC_GDCCCLUTR15_L_OFS                   0x00000478
// CLUTR30 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR15_L_CLUTR30_MASK          0xFF
#define LCDC_GDCCCLUTR15_L_CLUTR30_SHIFT         0 
#define LCDC_GDCCCLUTR15_L_CLUTR30_BIT           0xFF
#define LCDC_GDCCCLUTR15_L_CLUTR30_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR15_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR15_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR15_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR15_L_RESERVED_BITWIDTH     24
// GDCCCLUTR15_U Register
#define LCDC_GDCCCLUTR15_U_OFS                   0x0000047C
// CLUTR31 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR15_U_CLUTR31_MASK          0xFF
#define LCDC_GDCCCLUTR15_U_CLUTR31_SHIFT         0 
#define LCDC_GDCCCLUTR15_U_CLUTR31_BIT           0xFF
#define LCDC_GDCCCLUTR15_U_CLUTR31_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR15_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR15_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR15_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR15_U_RESERVED_BITWIDTH     24
// GDCCCLUTR16_L Register
#define LCDC_GDCCCLUTR16_L_OFS                   0x00000480
// CLUTR32 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR16_L_CLUTR32_MASK          0xFF
#define LCDC_GDCCCLUTR16_L_CLUTR32_SHIFT         0 
#define LCDC_GDCCCLUTR16_L_CLUTR32_BIT           0xFF
#define LCDC_GDCCCLUTR16_L_CLUTR32_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR16_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR16_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR16_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR16_L_RESERVED_BITWIDTH     24
// GDCCCLUTR16_U Register
#define LCDC_GDCCCLUTR16_U_OFS                   0x00000484
// CLUTR33 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR16_U_CLUTR33_MASK          0xFF
#define LCDC_GDCCCLUTR16_U_CLUTR33_SHIFT         0 
#define LCDC_GDCCCLUTR16_U_CLUTR33_BIT           0xFF
#define LCDC_GDCCCLUTR16_U_CLUTR33_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR16_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR16_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR16_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR16_U_RESERVED_BITWIDTH     24
// GDCCCLUTR17_L Register
#define LCDC_GDCCCLUTR17_L_OFS                   0x00000488
// CLUTR34 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR17_L_CLUTR34_MASK          0xFF
#define LCDC_GDCCCLUTR17_L_CLUTR34_SHIFT         0 
#define LCDC_GDCCCLUTR17_L_CLUTR34_BIT           0xFF
#define LCDC_GDCCCLUTR17_L_CLUTR34_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR17_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR17_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR17_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR17_L_RESERVED_BITWIDTH     24
// GDCCCLUTR17_U Register
#define LCDC_GDCCCLUTR17_U_OFS                   0x0000048C
// CLUTR35 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR17_U_CLUTR35_MASK          0xFF
#define LCDC_GDCCCLUTR17_U_CLUTR35_SHIFT         0 
#define LCDC_GDCCCLUTR17_U_CLUTR35_BIT           0xFF
#define LCDC_GDCCCLUTR17_U_CLUTR35_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR17_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR17_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR17_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR17_U_RESERVED_BITWIDTH     24
// GDCCCLUTR18_L Register
#define LCDC_GDCCCLUTR18_L_OFS                   0x00000490
// CLUTR36 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR18_L_CLUTR36_MASK          0xFF
#define LCDC_GDCCCLUTR18_L_CLUTR36_SHIFT         0 
#define LCDC_GDCCCLUTR18_L_CLUTR36_BIT           0xFF
#define LCDC_GDCCCLUTR18_L_CLUTR36_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR18_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR18_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR18_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR18_L_RESERVED_BITWIDTH     24
// GDCCCLUTR18_U Register
#define LCDC_GDCCCLUTR18_U_OFS                   0x00000494
// CLUTR37 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR18_U_CLUTR37_MASK          0xFF
#define LCDC_GDCCCLUTR18_U_CLUTR37_SHIFT         0 
#define LCDC_GDCCCLUTR18_U_CLUTR37_BIT           0xFF
#define LCDC_GDCCCLUTR18_U_CLUTR37_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR18_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR18_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR18_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR18_U_RESERVED_BITWIDTH     24
// GDCCCLUTR19_L Register
#define LCDC_GDCCCLUTR19_L_OFS                   0x00000498
// CLUTR38 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR19_L_CLUTR38_MASK          0xFF
#define LCDC_GDCCCLUTR19_L_CLUTR38_SHIFT         0 
#define LCDC_GDCCCLUTR19_L_CLUTR38_BIT           0xFF
#define LCDC_GDCCCLUTR19_L_CLUTR38_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR19_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR19_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR19_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR19_L_RESERVED_BITWIDTH     24
// GDCCCLUTR19_U Register
#define LCDC_GDCCCLUTR19_U_OFS                   0x0000049C
// CLUTR39 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR19_U_CLUTR39_MASK          0xFF
#define LCDC_GDCCCLUTR19_U_CLUTR39_SHIFT         0 
#define LCDC_GDCCCLUTR19_U_CLUTR39_BIT           0xFF
#define LCDC_GDCCCLUTR19_U_CLUTR39_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR19_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR19_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR19_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR19_U_RESERVED_BITWIDTH     24
// GDCCCLUTR20_L Register
#define LCDC_GDCCCLUTR20_L_OFS                   0x000004A0
// CLUTR40 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR20_L_CLUTR40_MASK          0xFF
#define LCDC_GDCCCLUTR20_L_CLUTR40_SHIFT         0 
#define LCDC_GDCCCLUTR20_L_CLUTR40_BIT           0xFF
#define LCDC_GDCCCLUTR20_L_CLUTR40_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR20_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR20_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR20_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR20_L_RESERVED_BITWIDTH     24
// GDCCCLUTR20_U Register
#define LCDC_GDCCCLUTR20_U_OFS                   0x000004A4
// CLUTR41 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR20_U_CLUTR41_MASK          0xFF
#define LCDC_GDCCCLUTR20_U_CLUTR41_SHIFT         0 
#define LCDC_GDCCCLUTR20_U_CLUTR41_BIT           0xFF
#define LCDC_GDCCCLUTR20_U_CLUTR41_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR20_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR20_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR20_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR20_U_RESERVED_BITWIDTH     24
// GDCCCLUTR21_L Register
#define LCDC_GDCCCLUTR21_L_OFS                   0x000004A8
// CLUTR42 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR21_L_CLUTR42_MASK          0xFF
#define LCDC_GDCCCLUTR21_L_CLUTR42_SHIFT         0 
#define LCDC_GDCCCLUTR21_L_CLUTR42_BIT           0xFF
#define LCDC_GDCCCLUTR21_L_CLUTR42_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR21_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR21_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR21_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR21_L_RESERVED_BITWIDTH     24
// GDCCCLUTR21_U Register
#define LCDC_GDCCCLUTR21_U_OFS                   0x000004AC
// CLUTR43 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR21_U_CLUTR43_MASK          0xFF
#define LCDC_GDCCCLUTR21_U_CLUTR43_SHIFT         0 
#define LCDC_GDCCCLUTR21_U_CLUTR43_BIT           0xFF
#define LCDC_GDCCCLUTR21_U_CLUTR43_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR21_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR21_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR21_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR21_U_RESERVED_BITWIDTH     24
// GDCCCLUTR22_L Register
#define LCDC_GDCCCLUTR22_L_OFS                   0x000004B0
// CLUTR44 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR22_L_CLUTR44_MASK          0xFF
#define LCDC_GDCCCLUTR22_L_CLUTR44_SHIFT         0 
#define LCDC_GDCCCLUTR22_L_CLUTR44_BIT           0xFF
#define LCDC_GDCCCLUTR22_L_CLUTR44_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR22_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR22_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR22_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR22_L_RESERVED_BITWIDTH     24
// GDCCCLUTR22_U Register
#define LCDC_GDCCCLUTR22_U_OFS                   0x000004B4
// CLUTR45 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR22_U_CLUTR45_MASK          0xFF
#define LCDC_GDCCCLUTR22_U_CLUTR45_SHIFT         0 
#define LCDC_GDCCCLUTR22_U_CLUTR45_BIT           0xFF
#define LCDC_GDCCCLUTR22_U_CLUTR45_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR22_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR22_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR22_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR22_U_RESERVED_BITWIDTH     24
// GDCCCLUTR23_L Register
#define LCDC_GDCCCLUTR23_L_OFS                   0x000004B8
// CLUTR46 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR23_L_CLUTR46_MASK          0xFF
#define LCDC_GDCCCLUTR23_L_CLUTR46_SHIFT         0 
#define LCDC_GDCCCLUTR23_L_CLUTR46_BIT           0xFF
#define LCDC_GDCCCLUTR23_L_CLUTR46_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR23_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR23_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR23_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR23_L_RESERVED_BITWIDTH     24
// GDCCCLUTR23_U Register
#define LCDC_GDCCCLUTR23_U_OFS                   0x000004BC
// CLUTR47 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR23_U_CLUTR47_MASK          0xFF
#define LCDC_GDCCCLUTR23_U_CLUTR47_SHIFT         0 
#define LCDC_GDCCCLUTR23_U_CLUTR47_BIT           0xFF
#define LCDC_GDCCCLUTR23_U_CLUTR47_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR23_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR23_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR23_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR23_U_RESERVED_BITWIDTH     24
// GDCCCLUTR24_L Register
#define LCDC_GDCCCLUTR24_L_OFS                   0x000004C0
// CLUTR48 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR24_L_CLUTR48_MASK          0xFF
#define LCDC_GDCCCLUTR24_L_CLUTR48_SHIFT         0 
#define LCDC_GDCCCLUTR24_L_CLUTR48_BIT           0xFF
#define LCDC_GDCCCLUTR24_L_CLUTR48_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR24_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR24_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR24_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR24_L_RESERVED_BITWIDTH     24
// GDCCCLUTR24_U Register
#define LCDC_GDCCCLUTR24_U_OFS                   0x000004C4
// CLUTR49 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR24_U_CLUTR49_MASK          0xFF
#define LCDC_GDCCCLUTR24_U_CLUTR49_SHIFT         0 
#define LCDC_GDCCCLUTR24_U_CLUTR49_BIT           0xFF
#define LCDC_GDCCCLUTR24_U_CLUTR49_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR24_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR24_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR24_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR24_U_RESERVED_BITWIDTH     24
// GDCCCLUTR25_L Register
#define LCDC_GDCCCLUTR25_L_OFS                   0x000004C8
// CLUTR50 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR25_L_CLUTR50_MASK          0xFF
#define LCDC_GDCCCLUTR25_L_CLUTR50_SHIFT         0 
#define LCDC_GDCCCLUTR25_L_CLUTR50_BIT           0xFF
#define LCDC_GDCCCLUTR25_L_CLUTR50_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR25_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR25_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR25_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR25_L_RESERVED_BITWIDTH     24
// GDCCCLUTR25_U Register
#define LCDC_GDCCCLUTR25_U_OFS                   0x000004CC
// CLUTR51 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR25_U_CLUTR51_MASK          0xFF
#define LCDC_GDCCCLUTR25_U_CLUTR51_SHIFT         0 
#define LCDC_GDCCCLUTR25_U_CLUTR51_BIT           0xFF
#define LCDC_GDCCCLUTR25_U_CLUTR51_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR25_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR25_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR25_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR25_U_RESERVED_BITWIDTH     24
// GDCCCLUTR26_L Register
#define LCDC_GDCCCLUTR26_L_OFS                   0x000004D0
// CLUTR52 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR26_L_CLUTR52_MASK          0xFF
#define LCDC_GDCCCLUTR26_L_CLUTR52_SHIFT         0 
#define LCDC_GDCCCLUTR26_L_CLUTR52_BIT           0xFF
#define LCDC_GDCCCLUTR26_L_CLUTR52_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR26_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR26_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR26_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR26_L_RESERVED_BITWIDTH     24
// GDCCCLUTR26_U Register
#define LCDC_GDCCCLUTR26_U_OFS                   0x000004D4
// CLUTR53 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR26_U_CLUTR53_MASK          0xFF
#define LCDC_GDCCCLUTR26_U_CLUTR53_SHIFT         0 
#define LCDC_GDCCCLUTR26_U_CLUTR53_BIT           0xFF
#define LCDC_GDCCCLUTR26_U_CLUTR53_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR26_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR26_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR26_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR26_U_RESERVED_BITWIDTH     24
// GDCCCLUTR27_L Register
#define LCDC_GDCCCLUTR27_L_OFS                   0x000004D8
// CLUTR54 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR27_L_CLUTR54_MASK          0xFF
#define LCDC_GDCCCLUTR27_L_CLUTR54_SHIFT         0 
#define LCDC_GDCCCLUTR27_L_CLUTR54_BIT           0xFF
#define LCDC_GDCCCLUTR27_L_CLUTR54_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR27_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR27_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR27_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR27_L_RESERVED_BITWIDTH     24
// GDCCCLUTR27_U Register
#define LCDC_GDCCCLUTR27_U_OFS                   0x000004DC
// CLUTR55 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR27_U_CLUTR55_MASK          0xFF
#define LCDC_GDCCCLUTR27_U_CLUTR55_SHIFT         0 
#define LCDC_GDCCCLUTR27_U_CLUTR55_BIT           0xFF
#define LCDC_GDCCCLUTR27_U_CLUTR55_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR27_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR27_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR27_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR27_U_RESERVED_BITWIDTH     24
// GDCCCLUTR28_L Register
#define LCDC_GDCCCLUTR28_L_OFS                   0x000004E0
// CLUTR56 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR28_L_CLUTR56_MASK          0xFF
#define LCDC_GDCCCLUTR28_L_CLUTR56_SHIFT         0 
#define LCDC_GDCCCLUTR28_L_CLUTR56_BIT           0xFF
#define LCDC_GDCCCLUTR28_L_CLUTR56_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR28_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR28_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR28_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR28_L_RESERVED_BITWIDTH     24
// GDCCCLUTR28_U Register
#define LCDC_GDCCCLUTR28_U_OFS                   0x000004E4
// CLUTR57 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR28_U_CLUTR57_MASK          0xFF
#define LCDC_GDCCCLUTR28_U_CLUTR57_SHIFT         0 
#define LCDC_GDCCCLUTR28_U_CLUTR57_BIT           0xFF
#define LCDC_GDCCCLUTR28_U_CLUTR57_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR28_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR28_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR28_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR28_U_RESERVED_BITWIDTH     24
// GDCCCLUTR29_L Register
#define LCDC_GDCCCLUTR29_L_OFS                   0x000004E8
// CLUTR58 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR29_L_CLUTR58_MASK          0xFF
#define LCDC_GDCCCLUTR29_L_CLUTR58_SHIFT         0 
#define LCDC_GDCCCLUTR29_L_CLUTR58_BIT           0xFF
#define LCDC_GDCCCLUTR29_L_CLUTR58_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR29_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR29_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR29_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR29_L_RESERVED_BITWIDTH     24
// GDCCCLUTR29_U Register
#define LCDC_GDCCCLUTR29_U_OFS                   0x000004EC
// CLUTR59 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR29_U_CLUTR59_MASK          0xFF
#define LCDC_GDCCCLUTR29_U_CLUTR59_SHIFT         0 
#define LCDC_GDCCCLUTR29_U_CLUTR59_BIT           0xFF
#define LCDC_GDCCCLUTR29_U_CLUTR59_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR29_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR29_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR29_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR29_U_RESERVED_BITWIDTH     24
// GDCCCLUTR30_L Register
#define LCDC_GDCCCLUTR30_L_OFS                   0x000004F0
// CLUTR60 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR30_L_CLUTR60_MASK          0xFF
#define LCDC_GDCCCLUTR30_L_CLUTR60_SHIFT         0 
#define LCDC_GDCCCLUTR30_L_CLUTR60_BIT           0xFF
#define LCDC_GDCCCLUTR30_L_CLUTR60_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR30_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR30_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR30_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR30_L_RESERVED_BITWIDTH     24
// GDCCCLUTR30_U Register
#define LCDC_GDCCCLUTR30_U_OFS                   0x000004F4
// CLUTR61 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR30_U_CLUTR61_MASK          0xFF
#define LCDC_GDCCCLUTR30_U_CLUTR61_SHIFT         0 
#define LCDC_GDCCCLUTR30_U_CLUTR61_BIT           0xFF
#define LCDC_GDCCCLUTR30_U_CLUTR61_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR30_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR30_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR30_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR30_U_RESERVED_BITWIDTH     24
// GDCCCLUTR31_L Register
#define LCDC_GDCCCLUTR31_L_OFS                   0x000004F8
// CLUTR62 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR31_L_CLUTR62_MASK          0xFF
#define LCDC_GDCCCLUTR31_L_CLUTR62_SHIFT         0 
#define LCDC_GDCCCLUTR31_L_CLUTR62_BIT           0xFF
#define LCDC_GDCCCLUTR31_L_CLUTR62_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR31_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR31_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR31_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR31_L_RESERVED_BITWIDTH     24
// GDCCCLUTR31_U Register
#define LCDC_GDCCCLUTR31_U_OFS                   0x000004FC
// CLUTR63 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR31_U_CLUTR63_MASK          0xFF
#define LCDC_GDCCCLUTR31_U_CLUTR63_SHIFT         0 
#define LCDC_GDCCCLUTR31_U_CLUTR63_BIT           0xFF
#define LCDC_GDCCCLUTR31_U_CLUTR63_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR31_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR31_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR31_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR31_U_RESERVED_BITWIDTH     24
// GDCCCLUTR32_L Register
#define LCDC_GDCCCLUTR32_L_OFS                   0x00000500
// CLUTR64 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR32_L_CLUTR64_MASK          0xFF
#define LCDC_GDCCCLUTR32_L_CLUTR64_SHIFT         0 
#define LCDC_GDCCCLUTR32_L_CLUTR64_BIT           0xFF
#define LCDC_GDCCCLUTR32_L_CLUTR64_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR32_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR32_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR32_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR32_L_RESERVED_BITWIDTH     24
// GDCCCLUTR32_U Register
#define LCDC_GDCCCLUTR32_U_OFS                   0x00000504
// CLUTR65 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR32_U_CLUTR65_MASK          0xFF
#define LCDC_GDCCCLUTR32_U_CLUTR65_SHIFT         0 
#define LCDC_GDCCCLUTR32_U_CLUTR65_BIT           0xFF
#define LCDC_GDCCCLUTR32_U_CLUTR65_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR32_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR32_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR32_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR32_U_RESERVED_BITWIDTH     24
// GDCCCLUTR33_L Register
#define LCDC_GDCCCLUTR33_L_OFS                   0x00000508
// CLUTR66 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR33_L_CLUTR66_MASK          0xFF
#define LCDC_GDCCCLUTR33_L_CLUTR66_SHIFT         0 
#define LCDC_GDCCCLUTR33_L_CLUTR66_BIT           0xFF
#define LCDC_GDCCCLUTR33_L_CLUTR66_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR33_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR33_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR33_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR33_L_RESERVED_BITWIDTH     24
// GDCCCLUTR33_U Register
#define LCDC_GDCCCLUTR33_U_OFS                   0x0000050C
// CLUTR67 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR33_U_CLUTR67_MASK          0xFF
#define LCDC_GDCCCLUTR33_U_CLUTR67_SHIFT         0 
#define LCDC_GDCCCLUTR33_U_CLUTR67_BIT           0xFF
#define LCDC_GDCCCLUTR33_U_CLUTR67_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR33_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR33_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR33_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR33_U_RESERVED_BITWIDTH     24
// GDCCCLUTR34_L Register
#define LCDC_GDCCCLUTR34_L_OFS                   0x00000510
// CLUTR68 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR34_L_CLUTR68_MASK          0xFF
#define LCDC_GDCCCLUTR34_L_CLUTR68_SHIFT         0 
#define LCDC_GDCCCLUTR34_L_CLUTR68_BIT           0xFF
#define LCDC_GDCCCLUTR34_L_CLUTR68_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR34_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR34_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR34_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR34_L_RESERVED_BITWIDTH     24
// GDCCCLUTR34_U Register
#define LCDC_GDCCCLUTR34_U_OFS                   0x00000514
// CLUTR69 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR34_U_CLUTR69_MASK          0xFF
#define LCDC_GDCCCLUTR34_U_CLUTR69_SHIFT         0 
#define LCDC_GDCCCLUTR34_U_CLUTR69_BIT           0xFF
#define LCDC_GDCCCLUTR34_U_CLUTR69_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR34_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR34_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR34_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR34_U_RESERVED_BITWIDTH     24
// GDCCCLUTR35_L Register
#define LCDC_GDCCCLUTR35_L_OFS                   0x00000518
// CLUTR70 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR35_L_CLUTR70_MASK          0xFF
#define LCDC_GDCCCLUTR35_L_CLUTR70_SHIFT         0 
#define LCDC_GDCCCLUTR35_L_CLUTR70_BIT           0xFF
#define LCDC_GDCCCLUTR35_L_CLUTR70_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR35_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR35_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR35_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR35_L_RESERVED_BITWIDTH     24
// GDCCCLUTR35_U Register
#define LCDC_GDCCCLUTR35_U_OFS                   0x0000051C
// CLUTR71 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR35_U_CLUTR71_MASK          0xFF
#define LCDC_GDCCCLUTR35_U_CLUTR71_SHIFT         0 
#define LCDC_GDCCCLUTR35_U_CLUTR71_BIT           0xFF
#define LCDC_GDCCCLUTR35_U_CLUTR71_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR35_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR35_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR35_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR35_U_RESERVED_BITWIDTH     24
// GDCCCLUTR36_L Register
#define LCDC_GDCCCLUTR36_L_OFS                   0x00000520
// CLUTR72 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR36_L_CLUTR72_MASK          0xFF
#define LCDC_GDCCCLUTR36_L_CLUTR72_SHIFT         0 
#define LCDC_GDCCCLUTR36_L_CLUTR72_BIT           0xFF
#define LCDC_GDCCCLUTR36_L_CLUTR72_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR36_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR36_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR36_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR36_L_RESERVED_BITWIDTH     24
// GDCCCLUTR36_U Register
#define LCDC_GDCCCLUTR36_U_OFS                   0x00000524
// CLUTR73 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR36_U_CLUTR73_MASK          0xFF
#define LCDC_GDCCCLUTR36_U_CLUTR73_SHIFT         0 
#define LCDC_GDCCCLUTR36_U_CLUTR73_BIT           0xFF
#define LCDC_GDCCCLUTR36_U_CLUTR73_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR36_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR36_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR36_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR36_U_RESERVED_BITWIDTH     24
// GDCCCLUTR37_L Register
#define LCDC_GDCCCLUTR37_L_OFS                   0x00000528
// CLUTR74 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR37_L_CLUTR74_MASK          0xFF
#define LCDC_GDCCCLUTR37_L_CLUTR74_SHIFT         0 
#define LCDC_GDCCCLUTR37_L_CLUTR74_BIT           0xFF
#define LCDC_GDCCCLUTR37_L_CLUTR74_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR37_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR37_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR37_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR37_L_RESERVED_BITWIDTH     24
// GDCCCLUTR37_U Register
#define LCDC_GDCCCLUTR37_U_OFS                   0x0000052C
// CLUTR75 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR37_U_CLUTR75_MASK          0xFF
#define LCDC_GDCCCLUTR37_U_CLUTR75_SHIFT         0 
#define LCDC_GDCCCLUTR37_U_CLUTR75_BIT           0xFF
#define LCDC_GDCCCLUTR37_U_CLUTR75_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR37_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR37_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR37_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR37_U_RESERVED_BITWIDTH     24
// GDCCCLUTR38_L Register
#define LCDC_GDCCCLUTR38_L_OFS                   0x00000530
// CLUTR76 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR38_L_CLUTR76_MASK          0xFF
#define LCDC_GDCCCLUTR38_L_CLUTR76_SHIFT         0 
#define LCDC_GDCCCLUTR38_L_CLUTR76_BIT           0xFF
#define LCDC_GDCCCLUTR38_L_CLUTR76_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR38_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR38_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR38_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR38_L_RESERVED_BITWIDTH     24
// GDCCCLUTR38_U Register
#define LCDC_GDCCCLUTR38_U_OFS                   0x00000534
// CLUTR77 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR38_U_CLUTR77_MASK          0xFF
#define LCDC_GDCCCLUTR38_U_CLUTR77_SHIFT         0 
#define LCDC_GDCCCLUTR38_U_CLUTR77_BIT           0xFF
#define LCDC_GDCCCLUTR38_U_CLUTR77_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR38_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR38_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR38_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR38_U_RESERVED_BITWIDTH     24
// GDCCCLUTR39_L Register
#define LCDC_GDCCCLUTR39_L_OFS                   0x00000538
// CLUTR78 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR39_L_CLUTR78_MASK          0xFF
#define LCDC_GDCCCLUTR39_L_CLUTR78_SHIFT         0 
#define LCDC_GDCCCLUTR39_L_CLUTR78_BIT           0xFF
#define LCDC_GDCCCLUTR39_L_CLUTR78_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR39_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR39_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR39_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR39_L_RESERVED_BITWIDTH     24
// GDCCCLUTR39_U Register
#define LCDC_GDCCCLUTR39_U_OFS                   0x0000053C
// CLUTR79 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR39_U_CLUTR79_MASK          0xFF
#define LCDC_GDCCCLUTR39_U_CLUTR79_SHIFT         0 
#define LCDC_GDCCCLUTR39_U_CLUTR79_BIT           0xFF
#define LCDC_GDCCCLUTR39_U_CLUTR79_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR39_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR39_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR39_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR39_U_RESERVED_BITWIDTH     24
// GDCCCLUTR40_L Register
#define LCDC_GDCCCLUTR40_L_OFS                   0x00000540
// CLUTR80 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR40_L_CLUTR80_MASK          0xFF
#define LCDC_GDCCCLUTR40_L_CLUTR80_SHIFT         0 
#define LCDC_GDCCCLUTR40_L_CLUTR80_BIT           0xFF
#define LCDC_GDCCCLUTR40_L_CLUTR80_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR40_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR40_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR40_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR40_L_RESERVED_BITWIDTH     24
// GDCCCLUTR40_U Register
#define LCDC_GDCCCLUTR40_U_OFS                   0x00000544
// CLUTR81 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR40_U_CLUTR81_MASK          0xFF
#define LCDC_GDCCCLUTR40_U_CLUTR81_SHIFT         0 
#define LCDC_GDCCCLUTR40_U_CLUTR81_BIT           0xFF
#define LCDC_GDCCCLUTR40_U_CLUTR81_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR40_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR40_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR40_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR40_U_RESERVED_BITWIDTH     24
// GDCCCLUTR41_L Register
#define LCDC_GDCCCLUTR41_L_OFS                   0x00000548
// CLUTR82 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR41_L_CLUTR82_MASK          0xFF
#define LCDC_GDCCCLUTR41_L_CLUTR82_SHIFT         0 
#define LCDC_GDCCCLUTR41_L_CLUTR82_BIT           0xFF
#define LCDC_GDCCCLUTR41_L_CLUTR82_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR41_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR41_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR41_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR41_L_RESERVED_BITWIDTH     24
// GDCCCLUTR41_U Register
#define LCDC_GDCCCLUTR41_U_OFS                   0x0000054C
// CLUTR83 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR41_U_CLUTR83_MASK          0xFF
#define LCDC_GDCCCLUTR41_U_CLUTR83_SHIFT         0 
#define LCDC_GDCCCLUTR41_U_CLUTR83_BIT           0xFF
#define LCDC_GDCCCLUTR41_U_CLUTR83_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR41_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR41_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR41_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR41_U_RESERVED_BITWIDTH     24
// GDCCCLUTR42_L Register
#define LCDC_GDCCCLUTR42_L_OFS                   0x00000550
// CLUTR84 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR42_L_CLUTR84_MASK          0xFF
#define LCDC_GDCCCLUTR42_L_CLUTR84_SHIFT         0 
#define LCDC_GDCCCLUTR42_L_CLUTR84_BIT           0xFF
#define LCDC_GDCCCLUTR42_L_CLUTR84_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR42_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR42_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR42_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR42_L_RESERVED_BITWIDTH     24
// GDCCCLUTR42_U Register
#define LCDC_GDCCCLUTR42_U_OFS                   0x00000554
// CLUTR85 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR42_U_CLUTR85_MASK          0xFF
#define LCDC_GDCCCLUTR42_U_CLUTR85_SHIFT         0 
#define LCDC_GDCCCLUTR42_U_CLUTR85_BIT           0xFF
#define LCDC_GDCCCLUTR42_U_CLUTR85_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR42_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR42_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR42_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR42_U_RESERVED_BITWIDTH     24
// GDCCCLUTR43_L Register
#define LCDC_GDCCCLUTR43_L_OFS                   0x00000558
// CLUTR86 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR43_L_CLUTR86_MASK          0xFF
#define LCDC_GDCCCLUTR43_L_CLUTR86_SHIFT         0 
#define LCDC_GDCCCLUTR43_L_CLUTR86_BIT           0xFF
#define LCDC_GDCCCLUTR43_L_CLUTR86_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR43_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR43_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR43_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR43_L_RESERVED_BITWIDTH     24
// GDCCCLUTR43_U Register
#define LCDC_GDCCCLUTR43_U_OFS                   0x0000055C
// CLUTR87 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR43_U_CLUTR87_MASK          0xFF
#define LCDC_GDCCCLUTR43_U_CLUTR87_SHIFT         0 
#define LCDC_GDCCCLUTR43_U_CLUTR87_BIT           0xFF
#define LCDC_GDCCCLUTR43_U_CLUTR87_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR43_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR43_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR43_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR43_U_RESERVED_BITWIDTH     24
// GDCCCLUTR44_L Register
#define LCDC_GDCCCLUTR44_L_OFS                   0x00000560
// CLUTR88 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR44_L_CLUTR88_MASK          0xFF
#define LCDC_GDCCCLUTR44_L_CLUTR88_SHIFT         0 
#define LCDC_GDCCCLUTR44_L_CLUTR88_BIT           0xFF
#define LCDC_GDCCCLUTR44_L_CLUTR88_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR44_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR44_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR44_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR44_L_RESERVED_BITWIDTH     24
// GDCCCLUTR44_U Register
#define LCDC_GDCCCLUTR44_U_OFS                   0x00000564
// CLUTR89 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR44_U_CLUTR89_MASK          0xFF
#define LCDC_GDCCCLUTR44_U_CLUTR89_SHIFT         0 
#define LCDC_GDCCCLUTR44_U_CLUTR89_BIT           0xFF
#define LCDC_GDCCCLUTR44_U_CLUTR89_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR44_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR44_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR44_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR44_U_RESERVED_BITWIDTH     24
// GDCCCLUTR45_L Register
#define LCDC_GDCCCLUTR45_L_OFS                   0x00000568
// CLUTR90 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR45_L_CLUTR90_MASK          0xFF
#define LCDC_GDCCCLUTR45_L_CLUTR90_SHIFT         0 
#define LCDC_GDCCCLUTR45_L_CLUTR90_BIT           0xFF
#define LCDC_GDCCCLUTR45_L_CLUTR90_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR45_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR45_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR45_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR45_L_RESERVED_BITWIDTH     24
// GDCCCLUTR45_U Register
#define LCDC_GDCCCLUTR45_U_OFS                   0x0000056C
// CLUTR91 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR45_U_CLUTR91_MASK          0xFF
#define LCDC_GDCCCLUTR45_U_CLUTR91_SHIFT         0 
#define LCDC_GDCCCLUTR45_U_CLUTR91_BIT           0xFF
#define LCDC_GDCCCLUTR45_U_CLUTR91_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR45_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR45_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR45_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR45_U_RESERVED_BITWIDTH     24
// GDCCCLUTR46_L Register
#define LCDC_GDCCCLUTR46_L_OFS                   0x00000570
// CLUTR92 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR46_L_CLUTR92_MASK          0xFF
#define LCDC_GDCCCLUTR46_L_CLUTR92_SHIFT         0 
#define LCDC_GDCCCLUTR46_L_CLUTR92_BIT           0xFF
#define LCDC_GDCCCLUTR46_L_CLUTR92_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR46_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR46_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR46_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR46_L_RESERVED_BITWIDTH     24
// GDCCCLUTR46_U Register
#define LCDC_GDCCCLUTR46_U_OFS                   0x00000574
// CLUTR93 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR46_U_CLUTR93_MASK          0xFF
#define LCDC_GDCCCLUTR46_U_CLUTR93_SHIFT         0 
#define LCDC_GDCCCLUTR46_U_CLUTR93_BIT           0xFF
#define LCDC_GDCCCLUTR46_U_CLUTR93_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR46_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR46_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR46_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR46_U_RESERVED_BITWIDTH     24
// GDCCCLUTR47_L Register
#define LCDC_GDCCCLUTR47_L_OFS                   0x00000578
// CLUTR94 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR47_L_CLUTR94_MASK          0xFF
#define LCDC_GDCCCLUTR47_L_CLUTR94_SHIFT         0 
#define LCDC_GDCCCLUTR47_L_CLUTR94_BIT           0xFF
#define LCDC_GDCCCLUTR47_L_CLUTR94_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR47_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR47_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR47_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR47_L_RESERVED_BITWIDTH     24
// GDCCCLUTR47_U Register
#define LCDC_GDCCCLUTR47_U_OFS                   0x0000057C
// CLUTR95 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR47_U_CLUTR95_MASK          0xFF
#define LCDC_GDCCCLUTR47_U_CLUTR95_SHIFT         0 
#define LCDC_GDCCCLUTR47_U_CLUTR95_BIT           0xFF
#define LCDC_GDCCCLUTR47_U_CLUTR95_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR47_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR47_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR47_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR47_U_RESERVED_BITWIDTH     24
// GDCCCLUTR48_L Register
#define LCDC_GDCCCLUTR48_L_OFS                   0x00000580
// CLUTR96 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR48_L_CLUTR96_MASK          0xFF
#define LCDC_GDCCCLUTR48_L_CLUTR96_SHIFT         0 
#define LCDC_GDCCCLUTR48_L_CLUTR96_BIT           0xFF
#define LCDC_GDCCCLUTR48_L_CLUTR96_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR48_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR48_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR48_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR48_L_RESERVED_BITWIDTH     24
// GDCCCLUTR48_U Register
#define LCDC_GDCCCLUTR48_U_OFS                   0x00000584
// CLUTR97 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR48_U_CLUTR97_MASK          0xFF
#define LCDC_GDCCCLUTR48_U_CLUTR97_SHIFT         0 
#define LCDC_GDCCCLUTR48_U_CLUTR97_BIT           0xFF
#define LCDC_GDCCCLUTR48_U_CLUTR97_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR48_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR48_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR48_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR48_U_RESERVED_BITWIDTH     24
// GDCCCLUTR49_L Register
#define LCDC_GDCCCLUTR49_L_OFS                   0x00000588
// CLUTR98 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR49_L_CLUTR98_MASK          0xFF
#define LCDC_GDCCCLUTR49_L_CLUTR98_SHIFT         0 
#define LCDC_GDCCCLUTR49_L_CLUTR98_BIT           0xFF
#define LCDC_GDCCCLUTR49_L_CLUTR98_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR49_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR49_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR49_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR49_L_RESERVED_BITWIDTH     24
// GDCCCLUTR49_U Register
#define LCDC_GDCCCLUTR49_U_OFS                   0x0000058C
// CLUTR99 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR49_U_CLUTR99_MASK          0xFF
#define LCDC_GDCCCLUTR49_U_CLUTR99_SHIFT         0 
#define LCDC_GDCCCLUTR49_U_CLUTR99_BIT           0xFF
#define LCDC_GDCCCLUTR49_U_CLUTR99_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR49_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR49_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR49_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR49_U_RESERVED_BITWIDTH     24
// GDCCCLUTR50_L Register
#define LCDC_GDCCCLUTR50_L_OFS                   0x00000590
// CLUTR100 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR50_L_CLUTR100_MASK         0xFF
#define LCDC_GDCCCLUTR50_L_CLUTR100_SHIFT        0 
#define LCDC_GDCCCLUTR50_L_CLUTR100_BIT          0xFF
#define LCDC_GDCCCLUTR50_L_CLUTR100_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR50_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR50_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR50_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR50_L_RESERVED_BITWIDTH     24
// GDCCCLUTR50_U Register
#define LCDC_GDCCCLUTR50_U_OFS                   0x00000594
// CLUTR101 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR50_U_CLUTR101_MASK         0xFF
#define LCDC_GDCCCLUTR50_U_CLUTR101_SHIFT        0 
#define LCDC_GDCCCLUTR50_U_CLUTR101_BIT          0xFF
#define LCDC_GDCCCLUTR50_U_CLUTR101_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR50_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR50_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR50_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR50_U_RESERVED_BITWIDTH     24
// GDCCCLUTR51_L Register
#define LCDC_GDCCCLUTR51_L_OFS                   0x00000598
// CLUTR102 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR51_L_CLUTR102_MASK         0xFF
#define LCDC_GDCCCLUTR51_L_CLUTR102_SHIFT        0 
#define LCDC_GDCCCLUTR51_L_CLUTR102_BIT          0xFF
#define LCDC_GDCCCLUTR51_L_CLUTR102_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR51_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR51_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR51_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR51_L_RESERVED_BITWIDTH     24
// GDCCCLUTR51_U Register
#define LCDC_GDCCCLUTR51_U_OFS                   0x0000059C
// CLUTR103 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR51_U_CLUTR103_MASK         0xFF
#define LCDC_GDCCCLUTR51_U_CLUTR103_SHIFT        0 
#define LCDC_GDCCCLUTR51_U_CLUTR103_BIT          0xFF
#define LCDC_GDCCCLUTR51_U_CLUTR103_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR51_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR51_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR51_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR51_U_RESERVED_BITWIDTH     24
// GDCCCLUTR52_L Register
#define LCDC_GDCCCLUTR52_L_OFS                   0x000005A0
// CLUTR104 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR52_L_CLUTR104_MASK         0xFF
#define LCDC_GDCCCLUTR52_L_CLUTR104_SHIFT        0 
#define LCDC_GDCCCLUTR52_L_CLUTR104_BIT          0xFF
#define LCDC_GDCCCLUTR52_L_CLUTR104_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR52_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR52_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR52_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR52_L_RESERVED_BITWIDTH     24
// GDCCCLUTR52_U Register
#define LCDC_GDCCCLUTR52_U_OFS                   0x000005A4
// CLUTR105 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR52_U_CLUTR105_MASK         0xFF
#define LCDC_GDCCCLUTR52_U_CLUTR105_SHIFT        0 
#define LCDC_GDCCCLUTR52_U_CLUTR105_BIT          0xFF
#define LCDC_GDCCCLUTR52_U_CLUTR105_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR52_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR52_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR52_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR52_U_RESERVED_BITWIDTH     24
// GDCCCLUTR53_L Register
#define LCDC_GDCCCLUTR53_L_OFS                   0x000005A8
// CLUTR106 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR53_L_CLUTR106_MASK         0xFF
#define LCDC_GDCCCLUTR53_L_CLUTR106_SHIFT        0 
#define LCDC_GDCCCLUTR53_L_CLUTR106_BIT          0xFF
#define LCDC_GDCCCLUTR53_L_CLUTR106_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR53_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR53_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR53_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR53_L_RESERVED_BITWIDTH     24
// GDCCCLUTR53_U Register
#define LCDC_GDCCCLUTR53_U_OFS                   0x000005AC
// CLUTR107 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR53_U_CLUTR107_MASK         0xFF
#define LCDC_GDCCCLUTR53_U_CLUTR107_SHIFT        0 
#define LCDC_GDCCCLUTR53_U_CLUTR107_BIT          0xFF
#define LCDC_GDCCCLUTR53_U_CLUTR107_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR53_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR53_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR53_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR53_U_RESERVED_BITWIDTH     24
// GDCCCLUTR54_L Register
#define LCDC_GDCCCLUTR54_L_OFS                   0x000005B0
// CLUTR108 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR54_L_CLUTR108_MASK         0xFF
#define LCDC_GDCCCLUTR54_L_CLUTR108_SHIFT        0 
#define LCDC_GDCCCLUTR54_L_CLUTR108_BIT          0xFF
#define LCDC_GDCCCLUTR54_L_CLUTR108_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR54_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR54_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR54_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR54_L_RESERVED_BITWIDTH     24
// GDCCCLUTR54_U Register
#define LCDC_GDCCCLUTR54_U_OFS                   0x000005B4
// CLUTR109 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR54_U_CLUTR109_MASK         0xFF
#define LCDC_GDCCCLUTR54_U_CLUTR109_SHIFT        0 
#define LCDC_GDCCCLUTR54_U_CLUTR109_BIT          0xFF
#define LCDC_GDCCCLUTR54_U_CLUTR109_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR54_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR54_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR54_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR54_U_RESERVED_BITWIDTH     24
// GDCCCLUTR55_L Register
#define LCDC_GDCCCLUTR55_L_OFS                   0x000005B8
// CLUTR110 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR55_L_CLUTR110_MASK         0xFF
#define LCDC_GDCCCLUTR55_L_CLUTR110_SHIFT        0 
#define LCDC_GDCCCLUTR55_L_CLUTR110_BIT          0xFF
#define LCDC_GDCCCLUTR55_L_CLUTR110_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR55_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR55_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR55_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR55_L_RESERVED_BITWIDTH     24
// GDCCCLUTR55_U Register
#define LCDC_GDCCCLUTR55_U_OFS                   0x000005BC
// CLUTR111 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR55_U_CLUTR111_MASK         0xFF
#define LCDC_GDCCCLUTR55_U_CLUTR111_SHIFT        0 
#define LCDC_GDCCCLUTR55_U_CLUTR111_BIT          0xFF
#define LCDC_GDCCCLUTR55_U_CLUTR111_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR55_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR55_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR55_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR55_U_RESERVED_BITWIDTH     24
// GDCCCLUTR56_L Register
#define LCDC_GDCCCLUTR56_L_OFS                   0x000005C0
// CLUTR112 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR56_L_CLUTR112_MASK         0xFF
#define LCDC_GDCCCLUTR56_L_CLUTR112_SHIFT        0 
#define LCDC_GDCCCLUTR56_L_CLUTR112_BIT          0xFF
#define LCDC_GDCCCLUTR56_L_CLUTR112_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR56_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR56_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR56_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR56_L_RESERVED_BITWIDTH     24
// GDCCCLUTR56_U Register
#define LCDC_GDCCCLUTR56_U_OFS                   0x000005C4
// CLUTR113 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR56_U_CLUTR113_MASK         0xFF
#define LCDC_GDCCCLUTR56_U_CLUTR113_SHIFT        0 
#define LCDC_GDCCCLUTR56_U_CLUTR113_BIT          0xFF
#define LCDC_GDCCCLUTR56_U_CLUTR113_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR56_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR56_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR56_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR56_U_RESERVED_BITWIDTH     24
// GDCCCLUTR57_L Register
#define LCDC_GDCCCLUTR57_L_OFS                   0x000005C8
// CLUTR114 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR57_L_CLUTR114_MASK         0xFF
#define LCDC_GDCCCLUTR57_L_CLUTR114_SHIFT        0 
#define LCDC_GDCCCLUTR57_L_CLUTR114_BIT          0xFF
#define LCDC_GDCCCLUTR57_L_CLUTR114_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR57_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR57_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR57_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR57_L_RESERVED_BITWIDTH     24
// GDCCCLUTR57_U Register
#define LCDC_GDCCCLUTR57_U_OFS                   0x000005CC
// CLUTR115 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR57_U_CLUTR115_MASK         0xFF
#define LCDC_GDCCCLUTR57_U_CLUTR115_SHIFT        0 
#define LCDC_GDCCCLUTR57_U_CLUTR115_BIT          0xFF
#define LCDC_GDCCCLUTR57_U_CLUTR115_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR57_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR57_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR57_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR57_U_RESERVED_BITWIDTH     24
// GDCCCLUTR58_L Register
#define LCDC_GDCCCLUTR58_L_OFS                   0x000005D0
// CLUTR116 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR58_L_CLUTR116_MASK         0xFF
#define LCDC_GDCCCLUTR58_L_CLUTR116_SHIFT        0 
#define LCDC_GDCCCLUTR58_L_CLUTR116_BIT          0xFF
#define LCDC_GDCCCLUTR58_L_CLUTR116_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR58_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR58_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR58_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR58_L_RESERVED_BITWIDTH     24
// GDCCCLUTR58_U Register
#define LCDC_GDCCCLUTR58_U_OFS                   0x000005D4
// CLUTR117 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR58_U_CLUTR117_MASK         0xFF
#define LCDC_GDCCCLUTR58_U_CLUTR117_SHIFT        0 
#define LCDC_GDCCCLUTR58_U_CLUTR117_BIT          0xFF
#define LCDC_GDCCCLUTR58_U_CLUTR117_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR58_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR58_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR58_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR58_U_RESERVED_BITWIDTH     24
// GDCCCLUTR59_L Register
#define LCDC_GDCCCLUTR59_L_OFS                   0x000005D8
// CLUTR118 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR59_L_CLUTR118_MASK         0xFF
#define LCDC_GDCCCLUTR59_L_CLUTR118_SHIFT        0 
#define LCDC_GDCCCLUTR59_L_CLUTR118_BIT          0xFF
#define LCDC_GDCCCLUTR59_L_CLUTR118_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR59_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR59_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR59_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR59_L_RESERVED_BITWIDTH     24
// GDCCCLUTR59_U Register
#define LCDC_GDCCCLUTR59_U_OFS                   0x000005DC
// CLUTR119 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR59_U_CLUTR119_MASK         0xFF
#define LCDC_GDCCCLUTR59_U_CLUTR119_SHIFT        0 
#define LCDC_GDCCCLUTR59_U_CLUTR119_BIT          0xFF
#define LCDC_GDCCCLUTR59_U_CLUTR119_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR59_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR59_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR59_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR59_U_RESERVED_BITWIDTH     24
// GDCCCLUTR60_L Register
#define LCDC_GDCCCLUTR60_L_OFS                   0x000005E0
// CLUTR120 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR60_L_CLUTR120_MASK         0xFF
#define LCDC_GDCCCLUTR60_L_CLUTR120_SHIFT        0 
#define LCDC_GDCCCLUTR60_L_CLUTR120_BIT          0xFF
#define LCDC_GDCCCLUTR60_L_CLUTR120_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR60_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR60_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR60_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR60_L_RESERVED_BITWIDTH     24
// GDCCCLUTR60_U Register
#define LCDC_GDCCCLUTR60_U_OFS                   0x000005E4
// CLUTR121 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR60_U_CLUTR121_MASK         0xFF
#define LCDC_GDCCCLUTR60_U_CLUTR121_SHIFT        0 
#define LCDC_GDCCCLUTR60_U_CLUTR121_BIT          0xFF
#define LCDC_GDCCCLUTR60_U_CLUTR121_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR60_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR60_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR60_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR60_U_RESERVED_BITWIDTH     24
// GDCCCLUTR61_L Register
#define LCDC_GDCCCLUTR61_L_OFS                   0x000005E8
// CLUTR122 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR61_L_CLUTR122_MASK         0xFF
#define LCDC_GDCCCLUTR61_L_CLUTR122_SHIFT        0 
#define LCDC_GDCCCLUTR61_L_CLUTR122_BIT          0xFF
#define LCDC_GDCCCLUTR61_L_CLUTR122_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR61_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR61_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR61_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR61_L_RESERVED_BITWIDTH     24
// GDCCCLUTR61_U Register
#define LCDC_GDCCCLUTR61_U_OFS                   0x000005EC
// CLUTR123 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR61_U_CLUTR123_MASK         0xFF
#define LCDC_GDCCCLUTR61_U_CLUTR123_SHIFT        0 
#define LCDC_GDCCCLUTR61_U_CLUTR123_BIT          0xFF
#define LCDC_GDCCCLUTR61_U_CLUTR123_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR61_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR61_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR61_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR61_U_RESERVED_BITWIDTH     24
// GDCCCLUTR62_L Register
#define LCDC_GDCCCLUTR62_L_OFS                   0x000005F0
// CLUTR124 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR62_L_CLUTR124_MASK         0xFF
#define LCDC_GDCCCLUTR62_L_CLUTR124_SHIFT        0 
#define LCDC_GDCCCLUTR62_L_CLUTR124_BIT          0xFF
#define LCDC_GDCCCLUTR62_L_CLUTR124_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR62_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR62_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR62_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR62_L_RESERVED_BITWIDTH     24
// GDCCCLUTR62_U Register
#define LCDC_GDCCCLUTR62_U_OFS                   0x000005F4
// CLUTR125 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR62_U_CLUTR125_MASK         0xFF
#define LCDC_GDCCCLUTR62_U_CLUTR125_SHIFT        0 
#define LCDC_GDCCCLUTR62_U_CLUTR125_BIT          0xFF
#define LCDC_GDCCCLUTR62_U_CLUTR125_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR62_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR62_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR62_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR62_U_RESERVED_BITWIDTH     24
// GDCCCLUTR63_L Register
#define LCDC_GDCCCLUTR63_L_OFS                   0x000005F8
// CLUTR126 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR63_L_CLUTR126_MASK         0xFF
#define LCDC_GDCCCLUTR63_L_CLUTR126_SHIFT        0 
#define LCDC_GDCCCLUTR63_L_CLUTR126_BIT          0xFF
#define LCDC_GDCCCLUTR63_L_CLUTR126_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR63_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR63_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR63_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR63_L_RESERVED_BITWIDTH     24
// GDCCCLUTR63_U Register
#define LCDC_GDCCCLUTR63_U_OFS                   0x000005FC
// CLUTR127 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR63_U_CLUTR127_MASK         0xFF
#define LCDC_GDCCCLUTR63_U_CLUTR127_SHIFT        0 
#define LCDC_GDCCCLUTR63_U_CLUTR127_BIT          0xFF
#define LCDC_GDCCCLUTR63_U_CLUTR127_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR63_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR63_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR63_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR63_U_RESERVED_BITWIDTH     24
// GDCCCLUTR64_L Register
#define LCDC_GDCCCLUTR64_L_OFS                   0x00000600
// CLUTR128 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR64_L_CLUTR128_MASK         0xFF
#define LCDC_GDCCCLUTR64_L_CLUTR128_SHIFT        0 
#define LCDC_GDCCCLUTR64_L_CLUTR128_BIT          0xFF
#define LCDC_GDCCCLUTR64_L_CLUTR128_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR64_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR64_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR64_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR64_L_RESERVED_BITWIDTH     24
// GDCCCLUTR64_U Register
#define LCDC_GDCCCLUTR64_U_OFS                   0x00000604
// CLUTR129 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR64_U_CLUTR129_MASK         0xFF
#define LCDC_GDCCCLUTR64_U_CLUTR129_SHIFT        0 
#define LCDC_GDCCCLUTR64_U_CLUTR129_BIT          0xFF
#define LCDC_GDCCCLUTR64_U_CLUTR129_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR64_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR64_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR64_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR64_U_RESERVED_BITWIDTH     24
// GDCCCLUTR65_L Register
#define LCDC_GDCCCLUTR65_L_OFS                   0x00000608
// CLUTR130 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR65_L_CLUTR130_MASK         0xFF
#define LCDC_GDCCCLUTR65_L_CLUTR130_SHIFT        0 
#define LCDC_GDCCCLUTR65_L_CLUTR130_BIT          0xFF
#define LCDC_GDCCCLUTR65_L_CLUTR130_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR65_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR65_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR65_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR65_L_RESERVED_BITWIDTH     24
// GDCCCLUTR65_U Register
#define LCDC_GDCCCLUTR65_U_OFS                   0x0000060C
// CLUTR131 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR65_U_CLUTR131_MASK         0xFF
#define LCDC_GDCCCLUTR65_U_CLUTR131_SHIFT        0 
#define LCDC_GDCCCLUTR65_U_CLUTR131_BIT          0xFF
#define LCDC_GDCCCLUTR65_U_CLUTR131_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR65_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR65_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR65_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR65_U_RESERVED_BITWIDTH     24
// GDCCCLUTR66_L Register
#define LCDC_GDCCCLUTR66_L_OFS                   0x00000610
// CLUTR132 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR66_L_CLUTR132_MASK         0xFF
#define LCDC_GDCCCLUTR66_L_CLUTR132_SHIFT        0 
#define LCDC_GDCCCLUTR66_L_CLUTR132_BIT          0xFF
#define LCDC_GDCCCLUTR66_L_CLUTR132_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR66_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR66_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR66_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR66_L_RESERVED_BITWIDTH     24
// GDCCCLUTR66_U Register
#define LCDC_GDCCCLUTR66_U_OFS                   0x00000614
// CLUTR133 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR66_U_CLUTR133_MASK         0xFF
#define LCDC_GDCCCLUTR66_U_CLUTR133_SHIFT        0 
#define LCDC_GDCCCLUTR66_U_CLUTR133_BIT          0xFF
#define LCDC_GDCCCLUTR66_U_CLUTR133_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR66_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR66_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR66_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR66_U_RESERVED_BITWIDTH     24
// GDCCCLUTR67_L Register
#define LCDC_GDCCCLUTR67_L_OFS                   0x00000618
// CLUTR134 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR67_L_CLUTR134_MASK         0xFF
#define LCDC_GDCCCLUTR67_L_CLUTR134_SHIFT        0 
#define LCDC_GDCCCLUTR67_L_CLUTR134_BIT          0xFF
#define LCDC_GDCCCLUTR67_L_CLUTR134_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR67_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR67_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR67_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR67_L_RESERVED_BITWIDTH     24
// GDCCCLUTR67_U Register
#define LCDC_GDCCCLUTR67_U_OFS                   0x0000061C
// CLUTR135 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR67_U_CLUTR135_MASK         0xFF
#define LCDC_GDCCCLUTR67_U_CLUTR135_SHIFT        0 
#define LCDC_GDCCCLUTR67_U_CLUTR135_BIT          0xFF
#define LCDC_GDCCCLUTR67_U_CLUTR135_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR67_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR67_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR67_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR67_U_RESERVED_BITWIDTH     24
// GDCCCLUTR68_L Register
#define LCDC_GDCCCLUTR68_L_OFS                   0x00000620
// CLUTR136 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR68_L_CLUTR136_MASK         0xFF
#define LCDC_GDCCCLUTR68_L_CLUTR136_SHIFT        0 
#define LCDC_GDCCCLUTR68_L_CLUTR136_BIT          0xFF
#define LCDC_GDCCCLUTR68_L_CLUTR136_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR68_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR68_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR68_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR68_L_RESERVED_BITWIDTH     24
// GDCCCLUTR68_U Register
#define LCDC_GDCCCLUTR68_U_OFS                   0x00000624
// CLUTR137 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR68_U_CLUTR137_MASK         0xFF
#define LCDC_GDCCCLUTR68_U_CLUTR137_SHIFT        0 
#define LCDC_GDCCCLUTR68_U_CLUTR137_BIT          0xFF
#define LCDC_GDCCCLUTR68_U_CLUTR137_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR68_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR68_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR68_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR68_U_RESERVED_BITWIDTH     24
// GDCCCLUTR69_L Register
#define LCDC_GDCCCLUTR69_L_OFS                   0x00000628
// CLUTR138 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR69_L_CLUTR138_MASK         0xFF
#define LCDC_GDCCCLUTR69_L_CLUTR138_SHIFT        0 
#define LCDC_GDCCCLUTR69_L_CLUTR138_BIT          0xFF
#define LCDC_GDCCCLUTR69_L_CLUTR138_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR69_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR69_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR69_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR69_L_RESERVED_BITWIDTH     24
// GDCCCLUTR69_U Register
#define LCDC_GDCCCLUTR69_U_OFS                   0x0000062C
// CLUTR139 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR69_U_CLUTR139_MASK         0xFF
#define LCDC_GDCCCLUTR69_U_CLUTR139_SHIFT        0 
#define LCDC_GDCCCLUTR69_U_CLUTR139_BIT          0xFF
#define LCDC_GDCCCLUTR69_U_CLUTR139_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR69_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR69_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR69_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR69_U_RESERVED_BITWIDTH     24
// GDCCCLUTR70_L Register
#define LCDC_GDCCCLUTR70_L_OFS                   0x00000630
// CLUTR140 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR70_L_CLUTR140_MASK         0xFF
#define LCDC_GDCCCLUTR70_L_CLUTR140_SHIFT        0 
#define LCDC_GDCCCLUTR70_L_CLUTR140_BIT          0xFF
#define LCDC_GDCCCLUTR70_L_CLUTR140_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR70_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR70_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR70_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR70_L_RESERVED_BITWIDTH     24
// GDCCCLUTR70_U Register
#define LCDC_GDCCCLUTR70_U_OFS                   0x00000634
// CLUTR141 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR70_U_CLUTR141_MASK         0xFF
#define LCDC_GDCCCLUTR70_U_CLUTR141_SHIFT        0 
#define LCDC_GDCCCLUTR70_U_CLUTR141_BIT          0xFF
#define LCDC_GDCCCLUTR70_U_CLUTR141_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR70_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR70_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR70_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR70_U_RESERVED_BITWIDTH     24
// GDCCCLUTR71_L Register
#define LCDC_GDCCCLUTR71_L_OFS                   0x00000638
// CLUTR142 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR71_L_CLUTR142_MASK         0xFF
#define LCDC_GDCCCLUTR71_L_CLUTR142_SHIFT        0 
#define LCDC_GDCCCLUTR71_L_CLUTR142_BIT          0xFF
#define LCDC_GDCCCLUTR71_L_CLUTR142_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR71_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR71_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR71_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR71_L_RESERVED_BITWIDTH     24
// GDCCCLUTR71_U Register
#define LCDC_GDCCCLUTR71_U_OFS                   0x0000063C
// CLUTR143 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR71_U_CLUTR143_MASK         0xFF
#define LCDC_GDCCCLUTR71_U_CLUTR143_SHIFT        0 
#define LCDC_GDCCCLUTR71_U_CLUTR143_BIT          0xFF
#define LCDC_GDCCCLUTR71_U_CLUTR143_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR71_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR71_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR71_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR71_U_RESERVED_BITWIDTH     24
// GDCCCLUTR72_L Register
#define LCDC_GDCCCLUTR72_L_OFS                   0x00000640
// CLUTR144 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR72_L_CLUTR144_MASK         0xFF
#define LCDC_GDCCCLUTR72_L_CLUTR144_SHIFT        0 
#define LCDC_GDCCCLUTR72_L_CLUTR144_BIT          0xFF
#define LCDC_GDCCCLUTR72_L_CLUTR144_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR72_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR72_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR72_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR72_L_RESERVED_BITWIDTH     24
// GDCCCLUTR72_U Register
#define LCDC_GDCCCLUTR72_U_OFS                   0x00000644
// CLUTR145 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR72_U_CLUTR145_MASK         0xFF
#define LCDC_GDCCCLUTR72_U_CLUTR145_SHIFT        0 
#define LCDC_GDCCCLUTR72_U_CLUTR145_BIT          0xFF
#define LCDC_GDCCCLUTR72_U_CLUTR145_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR72_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR72_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR72_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR72_U_RESERVED_BITWIDTH     24
// GDCCCLUTR73_L Register
#define LCDC_GDCCCLUTR73_L_OFS                   0x00000648
// CLUTR146 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR73_L_CLUTR146_MASK         0xFF
#define LCDC_GDCCCLUTR73_L_CLUTR146_SHIFT        0 
#define LCDC_GDCCCLUTR73_L_CLUTR146_BIT          0xFF
#define LCDC_GDCCCLUTR73_L_CLUTR146_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR73_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR73_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR73_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR73_L_RESERVED_BITWIDTH     24
// GDCCCLUTR73_U Register
#define LCDC_GDCCCLUTR73_U_OFS                   0x0000064C
// CLUTR147 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR73_U_CLUTR147_MASK         0xFF
#define LCDC_GDCCCLUTR73_U_CLUTR147_SHIFT        0 
#define LCDC_GDCCCLUTR73_U_CLUTR147_BIT          0xFF
#define LCDC_GDCCCLUTR73_U_CLUTR147_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR73_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR73_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR73_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR73_U_RESERVED_BITWIDTH     24
// GDCCCLUTR74_L Register
#define LCDC_GDCCCLUTR74_L_OFS                   0x00000650
// CLUTR148 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR74_L_CLUTR148_MASK         0xFF
#define LCDC_GDCCCLUTR74_L_CLUTR148_SHIFT        0 
#define LCDC_GDCCCLUTR74_L_CLUTR148_BIT          0xFF
#define LCDC_GDCCCLUTR74_L_CLUTR148_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR74_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR74_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR74_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR74_L_RESERVED_BITWIDTH     24
// GDCCCLUTR74_U Register
#define LCDC_GDCCCLUTR74_U_OFS                   0x00000654
// CLUTR149 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR74_U_CLUTR149_MASK         0xFF
#define LCDC_GDCCCLUTR74_U_CLUTR149_SHIFT        0 
#define LCDC_GDCCCLUTR74_U_CLUTR149_BIT          0xFF
#define LCDC_GDCCCLUTR74_U_CLUTR149_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR74_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR74_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR74_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR74_U_RESERVED_BITWIDTH     24
// GDCCCLUTR75_L Register
#define LCDC_GDCCCLUTR75_L_OFS                   0x00000658
// CLUTR150 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR75_L_CLUTR150_MASK         0xFF
#define LCDC_GDCCCLUTR75_L_CLUTR150_SHIFT        0 
#define LCDC_GDCCCLUTR75_L_CLUTR150_BIT          0xFF
#define LCDC_GDCCCLUTR75_L_CLUTR150_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR75_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR75_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR75_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR75_L_RESERVED_BITWIDTH     24
// GDCCCLUTR75_U Register
#define LCDC_GDCCCLUTR75_U_OFS                   0x0000065C
// CLUTR151 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR75_U_CLUTR151_MASK         0xFF
#define LCDC_GDCCCLUTR75_U_CLUTR151_SHIFT        0 
#define LCDC_GDCCCLUTR75_U_CLUTR151_BIT          0xFF
#define LCDC_GDCCCLUTR75_U_CLUTR151_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR75_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR75_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR75_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR75_U_RESERVED_BITWIDTH     24
// GDCCCLUTR76_L Register
#define LCDC_GDCCCLUTR76_L_OFS                   0x00000660
// CLUTR152 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR76_L_CLUTR152_MASK         0xFF
#define LCDC_GDCCCLUTR76_L_CLUTR152_SHIFT        0 
#define LCDC_GDCCCLUTR76_L_CLUTR152_BIT          0xFF
#define LCDC_GDCCCLUTR76_L_CLUTR152_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR76_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR76_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR76_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR76_L_RESERVED_BITWIDTH     24
// GDCCCLUTR76_U Register
#define LCDC_GDCCCLUTR76_U_OFS                   0x00000664
// CLUTR153 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR76_U_CLUTR153_MASK         0xFF
#define LCDC_GDCCCLUTR76_U_CLUTR153_SHIFT        0 
#define LCDC_GDCCCLUTR76_U_CLUTR153_BIT          0xFF
#define LCDC_GDCCCLUTR76_U_CLUTR153_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR76_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR76_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR76_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR76_U_RESERVED_BITWIDTH     24
// GDCCCLUTR77_L Register
#define LCDC_GDCCCLUTR77_L_OFS                   0x00000668
// CLUTR154 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR77_L_CLUTR154_MASK         0xFF
#define LCDC_GDCCCLUTR77_L_CLUTR154_SHIFT        0 
#define LCDC_GDCCCLUTR77_L_CLUTR154_BIT          0xFF
#define LCDC_GDCCCLUTR77_L_CLUTR154_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR77_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR77_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR77_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR77_L_RESERVED_BITWIDTH     24
// GDCCCLUTR77_U Register
#define LCDC_GDCCCLUTR77_U_OFS                   0x0000066C
// CLUTR155 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR77_U_CLUTR155_MASK         0xFF
#define LCDC_GDCCCLUTR77_U_CLUTR155_SHIFT        0 
#define LCDC_GDCCCLUTR77_U_CLUTR155_BIT          0xFF
#define LCDC_GDCCCLUTR77_U_CLUTR155_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR77_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR77_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR77_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR77_U_RESERVED_BITWIDTH     24
// GDCCCLUTR78_L Register
#define LCDC_GDCCCLUTR78_L_OFS                   0x00000670
// CLUTR156 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR78_L_CLUTR156_MASK         0xFF
#define LCDC_GDCCCLUTR78_L_CLUTR156_SHIFT        0 
#define LCDC_GDCCCLUTR78_L_CLUTR156_BIT          0xFF
#define LCDC_GDCCCLUTR78_L_CLUTR156_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR78_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR78_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR78_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR78_L_RESERVED_BITWIDTH     24
// GDCCCLUTR78_U Register
#define LCDC_GDCCCLUTR78_U_OFS                   0x00000674
// CLUTR157 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR78_U_CLUTR157_MASK         0xFF
#define LCDC_GDCCCLUTR78_U_CLUTR157_SHIFT        0 
#define LCDC_GDCCCLUTR78_U_CLUTR157_BIT          0xFF
#define LCDC_GDCCCLUTR78_U_CLUTR157_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR78_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR78_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR78_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR78_U_RESERVED_BITWIDTH     24
// GDCCCLUTR79_L Register
#define LCDC_GDCCCLUTR79_L_OFS                   0x00000678
// CLUTR158 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR79_L_CLUTR158_MASK         0xFF
#define LCDC_GDCCCLUTR79_L_CLUTR158_SHIFT        0 
#define LCDC_GDCCCLUTR79_L_CLUTR158_BIT          0xFF
#define LCDC_GDCCCLUTR79_L_CLUTR158_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR79_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR79_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR79_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR79_L_RESERVED_BITWIDTH     24
// GDCCCLUTR79_U Register
#define LCDC_GDCCCLUTR79_U_OFS                   0x0000067C
// CLUTR159 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR79_U_CLUTR159_MASK         0xFF
#define LCDC_GDCCCLUTR79_U_CLUTR159_SHIFT        0 
#define LCDC_GDCCCLUTR79_U_CLUTR159_BIT          0xFF
#define LCDC_GDCCCLUTR79_U_CLUTR159_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR79_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR79_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR79_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR79_U_RESERVED_BITWIDTH     24
// GDCCCLUTR80_L Register
#define LCDC_GDCCCLUTR80_L_OFS                   0x00000680
// CLUTR160 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR80_L_CLUTR160_MASK         0xFF
#define LCDC_GDCCCLUTR80_L_CLUTR160_SHIFT        0 
#define LCDC_GDCCCLUTR80_L_CLUTR160_BIT          0xFF
#define LCDC_GDCCCLUTR80_L_CLUTR160_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR80_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR80_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR80_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR80_L_RESERVED_BITWIDTH     24
// GDCCCLUTR80_U Register
#define LCDC_GDCCCLUTR80_U_OFS                   0x00000684
// CLUTR161 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR80_U_CLUTR161_MASK         0xFF
#define LCDC_GDCCCLUTR80_U_CLUTR161_SHIFT        0 
#define LCDC_GDCCCLUTR80_U_CLUTR161_BIT          0xFF
#define LCDC_GDCCCLUTR80_U_CLUTR161_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR80_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR80_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR80_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR80_U_RESERVED_BITWIDTH     24
// GDCCCLUTR81_L Register
#define LCDC_GDCCCLUTR81_L_OFS                   0x00000688
// CLUTR162 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR81_L_CLUTR162_MASK         0xFF
#define LCDC_GDCCCLUTR81_L_CLUTR162_SHIFT        0 
#define LCDC_GDCCCLUTR81_L_CLUTR162_BIT          0xFF
#define LCDC_GDCCCLUTR81_L_CLUTR162_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR81_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR81_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR81_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR81_L_RESERVED_BITWIDTH     24
// GDCCCLUTR81_U Register
#define LCDC_GDCCCLUTR81_U_OFS                   0x0000068C
// CLUTR163 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR81_U_CLUTR163_MASK         0xFF
#define LCDC_GDCCCLUTR81_U_CLUTR163_SHIFT        0 
#define LCDC_GDCCCLUTR81_U_CLUTR163_BIT          0xFF
#define LCDC_GDCCCLUTR81_U_CLUTR163_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR81_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR81_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR81_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR81_U_RESERVED_BITWIDTH     24
// GDCCCLUTR82_L Register
#define LCDC_GDCCCLUTR82_L_OFS                   0x00000690
// CLUTR164 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR82_L_CLUTR164_MASK         0xFF
#define LCDC_GDCCCLUTR82_L_CLUTR164_SHIFT        0 
#define LCDC_GDCCCLUTR82_L_CLUTR164_BIT          0xFF
#define LCDC_GDCCCLUTR82_L_CLUTR164_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR82_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR82_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR82_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR82_L_RESERVED_BITWIDTH     24
// GDCCCLUTR82_U Register
#define LCDC_GDCCCLUTR82_U_OFS                   0x00000694
// CLUTR165 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR82_U_CLUTR165_MASK         0xFF
#define LCDC_GDCCCLUTR82_U_CLUTR165_SHIFT        0 
#define LCDC_GDCCCLUTR82_U_CLUTR165_BIT          0xFF
#define LCDC_GDCCCLUTR82_U_CLUTR165_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR82_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR82_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR82_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR82_U_RESERVED_BITWIDTH     24
// GDCCCLUTR83_L Register
#define LCDC_GDCCCLUTR83_L_OFS                   0x00000698
// CLUTR166 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR83_L_CLUTR166_MASK         0xFF
#define LCDC_GDCCCLUTR83_L_CLUTR166_SHIFT        0 
#define LCDC_GDCCCLUTR83_L_CLUTR166_BIT          0xFF
#define LCDC_GDCCCLUTR83_L_CLUTR166_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR83_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR83_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR83_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR83_L_RESERVED_BITWIDTH     24
// GDCCCLUTR83_U Register
#define LCDC_GDCCCLUTR83_U_OFS                   0x0000069C
// CLUTR167 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR83_U_CLUTR167_MASK         0xFF
#define LCDC_GDCCCLUTR83_U_CLUTR167_SHIFT        0 
#define LCDC_GDCCCLUTR83_U_CLUTR167_BIT          0xFF
#define LCDC_GDCCCLUTR83_U_CLUTR167_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR83_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR83_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR83_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR83_U_RESERVED_BITWIDTH     24
// GDCCCLUTR84_L Register
#define LCDC_GDCCCLUTR84_L_OFS                   0x000006A0
// CLUTR168 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR84_L_CLUTR168_MASK         0xFF
#define LCDC_GDCCCLUTR84_L_CLUTR168_SHIFT        0 
#define LCDC_GDCCCLUTR84_L_CLUTR168_BIT          0xFF
#define LCDC_GDCCCLUTR84_L_CLUTR168_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR84_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR84_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR84_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR84_L_RESERVED_BITWIDTH     24
// GDCCCLUTR84_U Register
#define LCDC_GDCCCLUTR84_U_OFS                   0x000006A4
// CLUTR169 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR84_U_CLUTR169_MASK         0xFF
#define LCDC_GDCCCLUTR84_U_CLUTR169_SHIFT        0 
#define LCDC_GDCCCLUTR84_U_CLUTR169_BIT          0xFF
#define LCDC_GDCCCLUTR84_U_CLUTR169_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR84_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR84_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR84_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR84_U_RESERVED_BITWIDTH     24
// GDCCCLUTR85_L Register
#define LCDC_GDCCCLUTR85_L_OFS                   0x000006A8
// CLUTR170 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR85_L_CLUTR170_MASK         0xFF
#define LCDC_GDCCCLUTR85_L_CLUTR170_SHIFT        0 
#define LCDC_GDCCCLUTR85_L_CLUTR170_BIT          0xFF
#define LCDC_GDCCCLUTR85_L_CLUTR170_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR85_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR85_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR85_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR85_L_RESERVED_BITWIDTH     24
// GDCCCLUTR85_U Register
#define LCDC_GDCCCLUTR85_U_OFS                   0x000006AC
// CLUTR171 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR85_U_CLUTR171_MASK         0xFF
#define LCDC_GDCCCLUTR85_U_CLUTR171_SHIFT        0 
#define LCDC_GDCCCLUTR85_U_CLUTR171_BIT          0xFF
#define LCDC_GDCCCLUTR85_U_CLUTR171_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR85_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR85_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR85_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR85_U_RESERVED_BITWIDTH     24
// GDCCCLUTR86_L Register
#define LCDC_GDCCCLUTR86_L_OFS                   0x000006B0
// CLUTR172 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR86_L_CLUTR172_MASK         0xFF
#define LCDC_GDCCCLUTR86_L_CLUTR172_SHIFT        0 
#define LCDC_GDCCCLUTR86_L_CLUTR172_BIT          0xFF
#define LCDC_GDCCCLUTR86_L_CLUTR172_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR86_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR86_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR86_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR86_L_RESERVED_BITWIDTH     24
// GDCCCLUTR86_U Register
#define LCDC_GDCCCLUTR86_U_OFS                   0x000006B4
// CLUTR173 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR86_U_CLUTR173_MASK         0xFF
#define LCDC_GDCCCLUTR86_U_CLUTR173_SHIFT        0 
#define LCDC_GDCCCLUTR86_U_CLUTR173_BIT          0xFF
#define LCDC_GDCCCLUTR86_U_CLUTR173_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR86_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR86_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR86_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR86_U_RESERVED_BITWIDTH     24
// GDCCCLUTR87_L Register
#define LCDC_GDCCCLUTR87_L_OFS                   0x000006B8
// CLUTR174 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR87_L_CLUTR174_MASK         0xFF
#define LCDC_GDCCCLUTR87_L_CLUTR174_SHIFT        0 
#define LCDC_GDCCCLUTR87_L_CLUTR174_BIT          0xFF
#define LCDC_GDCCCLUTR87_L_CLUTR174_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR87_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR87_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR87_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR87_L_RESERVED_BITWIDTH     24
// GDCCCLUTR87_U Register
#define LCDC_GDCCCLUTR87_U_OFS                   0x000006BC
// CLUTR175 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR87_U_CLUTR175_MASK         0xFF
#define LCDC_GDCCCLUTR87_U_CLUTR175_SHIFT        0 
#define LCDC_GDCCCLUTR87_U_CLUTR175_BIT          0xFF
#define LCDC_GDCCCLUTR87_U_CLUTR175_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR87_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR87_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR87_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR87_U_RESERVED_BITWIDTH     24
// GDCCCLUTR88_L Register
#define LCDC_GDCCCLUTR88_L_OFS                   0x000006C0
// CLUTR176 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR88_L_CLUTR176_MASK         0xFF
#define LCDC_GDCCCLUTR88_L_CLUTR176_SHIFT        0 
#define LCDC_GDCCCLUTR88_L_CLUTR176_BIT          0xFF
#define LCDC_GDCCCLUTR88_L_CLUTR176_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR88_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR88_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR88_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR88_L_RESERVED_BITWIDTH     24
// GDCCCLUTR88_U Register
#define LCDC_GDCCCLUTR88_U_OFS                   0x000006C4
// CLUTR177 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR88_U_CLUTR177_MASK         0xFF
#define LCDC_GDCCCLUTR88_U_CLUTR177_SHIFT        0 
#define LCDC_GDCCCLUTR88_U_CLUTR177_BIT          0xFF
#define LCDC_GDCCCLUTR88_U_CLUTR177_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR88_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR88_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR88_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR88_U_RESERVED_BITWIDTH     24
// GDCCCLUTR89_L Register
#define LCDC_GDCCCLUTR89_L_OFS                   0x000006C8
// CLUTR178 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR89_L_CLUTR178_MASK         0xFF
#define LCDC_GDCCCLUTR89_L_CLUTR178_SHIFT        0 
#define LCDC_GDCCCLUTR89_L_CLUTR178_BIT          0xFF
#define LCDC_GDCCCLUTR89_L_CLUTR178_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR89_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR89_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR89_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR89_L_RESERVED_BITWIDTH     24
// GDCCCLUTR89_U Register
#define LCDC_GDCCCLUTR89_U_OFS                   0x000006CC
// CLUTR179 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR89_U_CLUTR179_MASK         0xFF
#define LCDC_GDCCCLUTR89_U_CLUTR179_SHIFT        0 
#define LCDC_GDCCCLUTR89_U_CLUTR179_BIT          0xFF
#define LCDC_GDCCCLUTR89_U_CLUTR179_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR89_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR89_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR89_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR89_U_RESERVED_BITWIDTH     24
// GDCCCLUTR90_L Register
#define LCDC_GDCCCLUTR90_L_OFS                   0x000006D0
// CLUTR180 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR90_L_CLUTR180_MASK         0xFF
#define LCDC_GDCCCLUTR90_L_CLUTR180_SHIFT        0 
#define LCDC_GDCCCLUTR90_L_CLUTR180_BIT          0xFF
#define LCDC_GDCCCLUTR90_L_CLUTR180_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR90_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR90_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR90_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR90_L_RESERVED_BITWIDTH     24
// GDCCCLUTR90_U Register
#define LCDC_GDCCCLUTR90_U_OFS                   0x000006D4
// CLUTR181 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR90_U_CLUTR181_MASK         0xFF
#define LCDC_GDCCCLUTR90_U_CLUTR181_SHIFT        0 
#define LCDC_GDCCCLUTR90_U_CLUTR181_BIT          0xFF
#define LCDC_GDCCCLUTR90_U_CLUTR181_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR90_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR90_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR90_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR90_U_RESERVED_BITWIDTH     24
// GDCCCLUTR91_L Register
#define LCDC_GDCCCLUTR91_L_OFS                   0x000006D8
// CLUTR182 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR91_L_CLUTR182_MASK         0xFF
#define LCDC_GDCCCLUTR91_L_CLUTR182_SHIFT        0 
#define LCDC_GDCCCLUTR91_L_CLUTR182_BIT          0xFF
#define LCDC_GDCCCLUTR91_L_CLUTR182_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR91_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR91_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR91_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR91_L_RESERVED_BITWIDTH     24
// GDCCCLUTR91_U Register
#define LCDC_GDCCCLUTR91_U_OFS                   0x000006DC
// CLUTR183 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR91_U_CLUTR183_MASK         0xFF
#define LCDC_GDCCCLUTR91_U_CLUTR183_SHIFT        0 
#define LCDC_GDCCCLUTR91_U_CLUTR183_BIT          0xFF
#define LCDC_GDCCCLUTR91_U_CLUTR183_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR91_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR91_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR91_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR91_U_RESERVED_BITWIDTH     24
// GDCCCLUTR92_L Register
#define LCDC_GDCCCLUTR92_L_OFS                   0x000006E0
// CLUTR184 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR92_L_CLUTR184_MASK         0xFF
#define LCDC_GDCCCLUTR92_L_CLUTR184_SHIFT        0 
#define LCDC_GDCCCLUTR92_L_CLUTR184_BIT          0xFF
#define LCDC_GDCCCLUTR92_L_CLUTR184_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR92_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR92_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR92_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR92_L_RESERVED_BITWIDTH     24
// GDCCCLUTR92_U Register
#define LCDC_GDCCCLUTR92_U_OFS                   0x000006E4
// CLUTR185 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR92_U_CLUTR185_MASK         0xFF
#define LCDC_GDCCCLUTR92_U_CLUTR185_SHIFT        0 
#define LCDC_GDCCCLUTR92_U_CLUTR185_BIT          0xFF
#define LCDC_GDCCCLUTR92_U_CLUTR185_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR92_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR92_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR92_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR92_U_RESERVED_BITWIDTH     24
// GDCCCLUTR93_L Register
#define LCDC_GDCCCLUTR93_L_OFS                   0x000006E8
// CLUTR186 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR93_L_CLUTR186_MASK         0xFF
#define LCDC_GDCCCLUTR93_L_CLUTR186_SHIFT        0 
#define LCDC_GDCCCLUTR93_L_CLUTR186_BIT          0xFF
#define LCDC_GDCCCLUTR93_L_CLUTR186_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR93_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR93_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR93_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR93_L_RESERVED_BITWIDTH     24
// GDCCCLUTR93_U Register
#define LCDC_GDCCCLUTR93_U_OFS                   0x000006EC
// CLUTR187 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR93_U_CLUTR187_MASK         0xFF
#define LCDC_GDCCCLUTR93_U_CLUTR187_SHIFT        0 
#define LCDC_GDCCCLUTR93_U_CLUTR187_BIT          0xFF
#define LCDC_GDCCCLUTR93_U_CLUTR187_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR93_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR93_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR93_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR93_U_RESERVED_BITWIDTH     24
// GDCCCLUTR94_L Register
#define LCDC_GDCCCLUTR94_L_OFS                   0x000006F0
// CLUTR188 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR94_L_CLUTR188_MASK         0xFF
#define LCDC_GDCCCLUTR94_L_CLUTR188_SHIFT        0 
#define LCDC_GDCCCLUTR94_L_CLUTR188_BIT          0xFF
#define LCDC_GDCCCLUTR94_L_CLUTR188_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR94_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR94_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR94_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR94_L_RESERVED_BITWIDTH     24
// GDCCCLUTR94_U Register
#define LCDC_GDCCCLUTR94_U_OFS                   0x000006F4
// CLUTR189 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR94_U_CLUTR189_MASK         0xFF
#define LCDC_GDCCCLUTR94_U_CLUTR189_SHIFT        0 
#define LCDC_GDCCCLUTR94_U_CLUTR189_BIT          0xFF
#define LCDC_GDCCCLUTR94_U_CLUTR189_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR94_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR94_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR94_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR94_U_RESERVED_BITWIDTH     24
// GDCCCLUTR95_L Register
#define LCDC_GDCCCLUTR95_L_OFS                   0x000006F8
// CLUTR190 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR95_L_CLUTR190_MASK         0xFF
#define LCDC_GDCCCLUTR95_L_CLUTR190_SHIFT        0 
#define LCDC_GDCCCLUTR95_L_CLUTR190_BIT          0xFF
#define LCDC_GDCCCLUTR95_L_CLUTR190_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR95_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR95_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR95_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR95_L_RESERVED_BITWIDTH     24
// GDCCCLUTR95_U Register
#define LCDC_GDCCCLUTR95_U_OFS                   0x000006FC
// CLUTR191 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR95_U_CLUTR191_MASK         0xFF
#define LCDC_GDCCCLUTR95_U_CLUTR191_SHIFT        0 
#define LCDC_GDCCCLUTR95_U_CLUTR191_BIT          0xFF
#define LCDC_GDCCCLUTR95_U_CLUTR191_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR95_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR95_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR95_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR95_U_RESERVED_BITWIDTH     24
// GDCCCLUTR96_L Register
#define LCDC_GDCCCLUTR96_L_OFS                   0x00000700
// CLUTR192 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR96_L_CLUTR192_MASK         0xFF
#define LCDC_GDCCCLUTR96_L_CLUTR192_SHIFT        0 
#define LCDC_GDCCCLUTR96_L_CLUTR192_BIT          0xFF
#define LCDC_GDCCCLUTR96_L_CLUTR192_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR96_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR96_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR96_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR96_L_RESERVED_BITWIDTH     24
// GDCCCLUTR96_U Register
#define LCDC_GDCCCLUTR96_U_OFS                   0x00000704
// CLUTR193 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR96_U_CLUTR193_MASK         0xFF
#define LCDC_GDCCCLUTR96_U_CLUTR193_SHIFT        0 
#define LCDC_GDCCCLUTR96_U_CLUTR193_BIT          0xFF
#define LCDC_GDCCCLUTR96_U_CLUTR193_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR96_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR96_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR96_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR96_U_RESERVED_BITWIDTH     24
// GDCCCLUTR97_L Register
#define LCDC_GDCCCLUTR97_L_OFS                   0x00000708
// CLUTR194 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR97_L_CLUTR194_MASK         0xFF
#define LCDC_GDCCCLUTR97_L_CLUTR194_SHIFT        0 
#define LCDC_GDCCCLUTR97_L_CLUTR194_BIT          0xFF
#define LCDC_GDCCCLUTR97_L_CLUTR194_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR97_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR97_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR97_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR97_L_RESERVED_BITWIDTH     24
// GDCCCLUTR97_U Register
#define LCDC_GDCCCLUTR97_U_OFS                   0x0000070C
// CLUTR195 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR97_U_CLUTR195_MASK         0xFF
#define LCDC_GDCCCLUTR97_U_CLUTR195_SHIFT        0 
#define LCDC_GDCCCLUTR97_U_CLUTR195_BIT          0xFF
#define LCDC_GDCCCLUTR97_U_CLUTR195_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR97_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR97_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR97_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR97_U_RESERVED_BITWIDTH     24
// GDCCCLUTR98_L Register
#define LCDC_GDCCCLUTR98_L_OFS                   0x00000710
// CLUTR196 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR98_L_CLUTR196_MASK         0xFF
#define LCDC_GDCCCLUTR98_L_CLUTR196_SHIFT        0 
#define LCDC_GDCCCLUTR98_L_CLUTR196_BIT          0xFF
#define LCDC_GDCCCLUTR98_L_CLUTR196_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR98_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR98_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR98_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR98_L_RESERVED_BITWIDTH     24
// GDCCCLUTR98_U Register
#define LCDC_GDCCCLUTR98_U_OFS                   0x00000714
// CLUTR197 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR98_U_CLUTR197_MASK         0xFF
#define LCDC_GDCCCLUTR98_U_CLUTR197_SHIFT        0 
#define LCDC_GDCCCLUTR98_U_CLUTR197_BIT          0xFF
#define LCDC_GDCCCLUTR98_U_CLUTR197_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR98_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR98_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR98_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR98_U_RESERVED_BITWIDTH     24
// GDCCCLUTR99_L Register
#define LCDC_GDCCCLUTR99_L_OFS                   0x00000718
// CLUTR198 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR99_L_CLUTR198_MASK         0xFF
#define LCDC_GDCCCLUTR99_L_CLUTR198_SHIFT        0 
#define LCDC_GDCCCLUTR99_L_CLUTR198_BIT          0xFF
#define LCDC_GDCCCLUTR99_L_CLUTR198_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR99_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR99_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR99_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR99_L_RESERVED_BITWIDTH     24
// GDCCCLUTR99_U Register
#define LCDC_GDCCCLUTR99_U_OFS                   0x0000071C
// CLUTR199 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR99_U_CLUTR199_MASK         0xFF
#define LCDC_GDCCCLUTR99_U_CLUTR199_SHIFT        0 
#define LCDC_GDCCCLUTR99_U_CLUTR199_BIT          0xFF
#define LCDC_GDCCCLUTR99_U_CLUTR199_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR99_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTR99_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTR99_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTR99_U_RESERVED_BITWIDTH     24
// GDCCCLUTR100_L Register
#define LCDC_GDCCCLUTR100_L_OFS                  0x00000720
// CLUTR200 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR100_L_CLUTR200_MASK        0xFF
#define LCDC_GDCCCLUTR100_L_CLUTR200_SHIFT       0 
#define LCDC_GDCCCLUTR100_L_CLUTR200_BIT         0xFF
#define LCDC_GDCCCLUTR100_L_CLUTR200_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR100_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR100_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR100_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR100_L_RESERVED_BITWIDTH    24
// GDCCCLUTR100_U Register
#define LCDC_GDCCCLUTR100_U_OFS                  0x00000724
// CLUTR201 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR100_U_CLUTR201_MASK        0xFF
#define LCDC_GDCCCLUTR100_U_CLUTR201_SHIFT       0 
#define LCDC_GDCCCLUTR100_U_CLUTR201_BIT         0xFF
#define LCDC_GDCCCLUTR100_U_CLUTR201_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR100_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR100_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR100_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR100_U_RESERVED_BITWIDTH    24
// GDCCCLUTR101_L Register
#define LCDC_GDCCCLUTR101_L_OFS                  0x00000728
// CLUTR202 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR101_L_CLUTR202_MASK        0xFF
#define LCDC_GDCCCLUTR101_L_CLUTR202_SHIFT       0 
#define LCDC_GDCCCLUTR101_L_CLUTR202_BIT         0xFF
#define LCDC_GDCCCLUTR101_L_CLUTR202_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR101_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR101_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR101_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR101_L_RESERVED_BITWIDTH    24
// GDCCCLUTR101_U Register
#define LCDC_GDCCCLUTR101_U_OFS                  0x0000072C
// CLUTR203 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR101_U_CLUTR203_MASK        0xFF
#define LCDC_GDCCCLUTR101_U_CLUTR203_SHIFT       0 
#define LCDC_GDCCCLUTR101_U_CLUTR203_BIT         0xFF
#define LCDC_GDCCCLUTR101_U_CLUTR203_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR101_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR101_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR101_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR101_U_RESERVED_BITWIDTH    24
// GDCCCLUTR102_L Register
#define LCDC_GDCCCLUTR102_L_OFS                  0x00000730
// CLUTR204 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR102_L_CLUTR204_MASK        0xFF
#define LCDC_GDCCCLUTR102_L_CLUTR204_SHIFT       0 
#define LCDC_GDCCCLUTR102_L_CLUTR204_BIT         0xFF
#define LCDC_GDCCCLUTR102_L_CLUTR204_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR102_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR102_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR102_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR102_L_RESERVED_BITWIDTH    24
// GDCCCLUTR102_U Register
#define LCDC_GDCCCLUTR102_U_OFS                  0x00000734
// CLUTR205 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR102_U_CLUTR205_MASK        0xFF
#define LCDC_GDCCCLUTR102_U_CLUTR205_SHIFT       0 
#define LCDC_GDCCCLUTR102_U_CLUTR205_BIT         0xFF
#define LCDC_GDCCCLUTR102_U_CLUTR205_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR102_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR102_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR102_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR102_U_RESERVED_BITWIDTH    24
// GDCCCLUTR103_L Register
#define LCDC_GDCCCLUTR103_L_OFS                  0x00000738
// CLUTR206 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR103_L_CLUTR206_MASK        0xFF
#define LCDC_GDCCCLUTR103_L_CLUTR206_SHIFT       0 
#define LCDC_GDCCCLUTR103_L_CLUTR206_BIT         0xFF
#define LCDC_GDCCCLUTR103_L_CLUTR206_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR103_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR103_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR103_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR103_L_RESERVED_BITWIDTH    24
// GDCCCLUTR103_U Register
#define LCDC_GDCCCLUTR103_U_OFS                  0x0000073C
// CLUTR207 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR103_U_CLUTR207_MASK        0xFF
#define LCDC_GDCCCLUTR103_U_CLUTR207_SHIFT       0 
#define LCDC_GDCCCLUTR103_U_CLUTR207_BIT         0xFF
#define LCDC_GDCCCLUTR103_U_CLUTR207_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR103_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR103_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR103_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR103_U_RESERVED_BITWIDTH    24
// GDCCCLUTR104_L Register
#define LCDC_GDCCCLUTR104_L_OFS                  0x00000740
// CLUTR208 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR104_L_CLUTR208_MASK        0xFF
#define LCDC_GDCCCLUTR104_L_CLUTR208_SHIFT       0 
#define LCDC_GDCCCLUTR104_L_CLUTR208_BIT         0xFF
#define LCDC_GDCCCLUTR104_L_CLUTR208_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR104_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR104_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR104_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR104_L_RESERVED_BITWIDTH    24
// GDCCCLUTR104_U Register
#define LCDC_GDCCCLUTR104_U_OFS                  0x00000744
// CLUTR209 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR104_U_CLUTR209_MASK        0xFF
#define LCDC_GDCCCLUTR104_U_CLUTR209_SHIFT       0 
#define LCDC_GDCCCLUTR104_U_CLUTR209_BIT         0xFF
#define LCDC_GDCCCLUTR104_U_CLUTR209_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR104_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR104_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR104_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR104_U_RESERVED_BITWIDTH    24
// GDCCCLUTR105_L Register
#define LCDC_GDCCCLUTR105_L_OFS                  0x00000748
// CLUTR210 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR105_L_CLUTR210_MASK        0xFF
#define LCDC_GDCCCLUTR105_L_CLUTR210_SHIFT       0 
#define LCDC_GDCCCLUTR105_L_CLUTR210_BIT         0xFF
#define LCDC_GDCCCLUTR105_L_CLUTR210_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR105_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR105_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR105_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR105_L_RESERVED_BITWIDTH    24
// GDCCCLUTR105_U Register
#define LCDC_GDCCCLUTR105_U_OFS                  0x0000074C
// CLUTR211 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR105_U_CLUTR211_MASK        0xFF
#define LCDC_GDCCCLUTR105_U_CLUTR211_SHIFT       0 
#define LCDC_GDCCCLUTR105_U_CLUTR211_BIT         0xFF
#define LCDC_GDCCCLUTR105_U_CLUTR211_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR105_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR105_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR105_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR105_U_RESERVED_BITWIDTH    24
// GDCCCLUTR106_L Register
#define LCDC_GDCCCLUTR106_L_OFS                  0x00000750
// CLUTR212 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR106_L_CLUTR212_MASK        0xFF
#define LCDC_GDCCCLUTR106_L_CLUTR212_SHIFT       0 
#define LCDC_GDCCCLUTR106_L_CLUTR212_BIT         0xFF
#define LCDC_GDCCCLUTR106_L_CLUTR212_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR106_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR106_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR106_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR106_L_RESERVED_BITWIDTH    24
// GDCCCLUTR106_U Register
#define LCDC_GDCCCLUTR106_U_OFS                  0x00000754
// CLUTR213 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR106_U_CLUTR213_MASK        0xFF
#define LCDC_GDCCCLUTR106_U_CLUTR213_SHIFT       0 
#define LCDC_GDCCCLUTR106_U_CLUTR213_BIT         0xFF
#define LCDC_GDCCCLUTR106_U_CLUTR213_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR106_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR106_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR106_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR106_U_RESERVED_BITWIDTH    24
// GDCCCLUTR107_L Register
#define LCDC_GDCCCLUTR107_L_OFS                  0x00000758
// CLUTR214 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR107_L_CLUTR214_MASK        0xFF
#define LCDC_GDCCCLUTR107_L_CLUTR214_SHIFT       0 
#define LCDC_GDCCCLUTR107_L_CLUTR214_BIT         0xFF
#define LCDC_GDCCCLUTR107_L_CLUTR214_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR107_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR107_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR107_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR107_L_RESERVED_BITWIDTH    24
// GDCCCLUTR107_U Register
#define LCDC_GDCCCLUTR107_U_OFS                  0x0000075C
// CLUTR215 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR107_U_CLUTR215_MASK        0xFF
#define LCDC_GDCCCLUTR107_U_CLUTR215_SHIFT       0 
#define LCDC_GDCCCLUTR107_U_CLUTR215_BIT         0xFF
#define LCDC_GDCCCLUTR107_U_CLUTR215_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR107_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR107_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR107_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR107_U_RESERVED_BITWIDTH    24
// GDCCCLUTR108_L Register
#define LCDC_GDCCCLUTR108_L_OFS                  0x00000760
// CLUTR216 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR108_L_CLUTR216_MASK        0xFF
#define LCDC_GDCCCLUTR108_L_CLUTR216_SHIFT       0 
#define LCDC_GDCCCLUTR108_L_CLUTR216_BIT         0xFF
#define LCDC_GDCCCLUTR108_L_CLUTR216_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR108_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR108_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR108_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR108_L_RESERVED_BITWIDTH    24
// GDCCCLUTR108_U Register
#define LCDC_GDCCCLUTR108_U_OFS                  0x00000764
// CLUTR217 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR108_U_CLUTR217_MASK        0xFF
#define LCDC_GDCCCLUTR108_U_CLUTR217_SHIFT       0 
#define LCDC_GDCCCLUTR108_U_CLUTR217_BIT         0xFF
#define LCDC_GDCCCLUTR108_U_CLUTR217_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR108_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR108_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR108_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR108_U_RESERVED_BITWIDTH    24
// GDCCCLUTR109_L Register
#define LCDC_GDCCCLUTR109_L_OFS                  0x00000768
// CLUTR218 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR109_L_CLUTR218_MASK        0xFF
#define LCDC_GDCCCLUTR109_L_CLUTR218_SHIFT       0 
#define LCDC_GDCCCLUTR109_L_CLUTR218_BIT         0xFF
#define LCDC_GDCCCLUTR109_L_CLUTR218_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR109_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR109_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR109_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR109_L_RESERVED_BITWIDTH    24
// GDCCCLUTR109_U Register
#define LCDC_GDCCCLUTR109_U_OFS                  0x0000076C
// CLUTR219 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR109_U_CLUTR219_MASK        0xFF
#define LCDC_GDCCCLUTR109_U_CLUTR219_SHIFT       0 
#define LCDC_GDCCCLUTR109_U_CLUTR219_BIT         0xFF
#define LCDC_GDCCCLUTR109_U_CLUTR219_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR109_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR109_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR109_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR109_U_RESERVED_BITWIDTH    24
// GDCCCLUTR110_L Register
#define LCDC_GDCCCLUTR110_L_OFS                  0x00000770
// CLUTR220 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR110_L_CLUTR220_MASK        0xFF
#define LCDC_GDCCCLUTR110_L_CLUTR220_SHIFT       0 
#define LCDC_GDCCCLUTR110_L_CLUTR220_BIT         0xFF
#define LCDC_GDCCCLUTR110_L_CLUTR220_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR110_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR110_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR110_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR110_L_RESERVED_BITWIDTH    24
// GDCCCLUTR110_U Register
#define LCDC_GDCCCLUTR110_U_OFS                  0x00000774
// CLUTR221 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR110_U_CLUTR221_MASK        0xFF
#define LCDC_GDCCCLUTR110_U_CLUTR221_SHIFT       0 
#define LCDC_GDCCCLUTR110_U_CLUTR221_BIT         0xFF
#define LCDC_GDCCCLUTR110_U_CLUTR221_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR110_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR110_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR110_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR110_U_RESERVED_BITWIDTH    24
// GDCCCLUTR111_L Register
#define LCDC_GDCCCLUTR111_L_OFS                  0x00000778
// CLUTR222 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR111_L_CLUTR222_MASK        0xFF
#define LCDC_GDCCCLUTR111_L_CLUTR222_SHIFT       0 
#define LCDC_GDCCCLUTR111_L_CLUTR222_BIT         0xFF
#define LCDC_GDCCCLUTR111_L_CLUTR222_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR111_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR111_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR111_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR111_L_RESERVED_BITWIDTH    24
// GDCCCLUTR111_U Register
#define LCDC_GDCCCLUTR111_U_OFS                  0x0000077C
// CLUTR223 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR111_U_CLUTR223_MASK        0xFF
#define LCDC_GDCCCLUTR111_U_CLUTR223_SHIFT       0 
#define LCDC_GDCCCLUTR111_U_CLUTR223_BIT         0xFF
#define LCDC_GDCCCLUTR111_U_CLUTR223_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR111_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR111_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR111_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR111_U_RESERVED_BITWIDTH    24
// GDCCCLUTR112_L Register
#define LCDC_GDCCCLUTR112_L_OFS                  0x00000780
// CLUTR224 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR112_L_CLUTR224_MASK        0xFF
#define LCDC_GDCCCLUTR112_L_CLUTR224_SHIFT       0 
#define LCDC_GDCCCLUTR112_L_CLUTR224_BIT         0xFF
#define LCDC_GDCCCLUTR112_L_CLUTR224_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR112_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR112_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR112_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR112_L_RESERVED_BITWIDTH    24
// GDCCCLUTR112_U Register
#define LCDC_GDCCCLUTR112_U_OFS                  0x00000784
// CLUTR225 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR112_U_CLUTR225_MASK        0xFF
#define LCDC_GDCCCLUTR112_U_CLUTR225_SHIFT       0 
#define LCDC_GDCCCLUTR112_U_CLUTR225_BIT         0xFF
#define LCDC_GDCCCLUTR112_U_CLUTR225_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR112_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR112_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR112_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR112_U_RESERVED_BITWIDTH    24
// GDCCCLUTR113_L Register
#define LCDC_GDCCCLUTR113_L_OFS                  0x00000788
// CLUTR226 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR113_L_CLUTR226_MASK        0xFF
#define LCDC_GDCCCLUTR113_L_CLUTR226_SHIFT       0 
#define LCDC_GDCCCLUTR113_L_CLUTR226_BIT         0xFF
#define LCDC_GDCCCLUTR113_L_CLUTR226_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR113_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR113_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR113_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR113_L_RESERVED_BITWIDTH    24
// GDCCCLUTR113_U Register
#define LCDC_GDCCCLUTR113_U_OFS                  0x0000078C
// CLUTR227 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR113_U_CLUTR227_MASK        0xFF
#define LCDC_GDCCCLUTR113_U_CLUTR227_SHIFT       0 
#define LCDC_GDCCCLUTR113_U_CLUTR227_BIT         0xFF
#define LCDC_GDCCCLUTR113_U_CLUTR227_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR113_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR113_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR113_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR113_U_RESERVED_BITWIDTH    24
// GDCCCLUTR114_L Register
#define LCDC_GDCCCLUTR114_L_OFS                  0x00000790
// CLUTR228 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR114_L_CLUTR228_MASK        0xFF
#define LCDC_GDCCCLUTR114_L_CLUTR228_SHIFT       0 
#define LCDC_GDCCCLUTR114_L_CLUTR228_BIT         0xFF
#define LCDC_GDCCCLUTR114_L_CLUTR228_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR114_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR114_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR114_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR114_L_RESERVED_BITWIDTH    24
// GDCCCLUTR114_U Register
#define LCDC_GDCCCLUTR114_U_OFS                  0x00000794
// CLUTR229 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR114_U_CLUTR229_MASK        0xFF
#define LCDC_GDCCCLUTR114_U_CLUTR229_SHIFT       0 
#define LCDC_GDCCCLUTR114_U_CLUTR229_BIT         0xFF
#define LCDC_GDCCCLUTR114_U_CLUTR229_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR114_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR114_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR114_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR114_U_RESERVED_BITWIDTH    24
// GDCCCLUTR115_L Register
#define LCDC_GDCCCLUTR115_L_OFS                  0x00000798
// CLUTR230 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR115_L_CLUTR230_MASK        0xFF
#define LCDC_GDCCCLUTR115_L_CLUTR230_SHIFT       0 
#define LCDC_GDCCCLUTR115_L_CLUTR230_BIT         0xFF
#define LCDC_GDCCCLUTR115_L_CLUTR230_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR115_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR115_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR115_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR115_L_RESERVED_BITWIDTH    24
// GDCCCLUTR115_U Register
#define LCDC_GDCCCLUTR115_U_OFS                  0x0000079C
// CLUTR231 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR115_U_CLUTR231_MASK        0xFF
#define LCDC_GDCCCLUTR115_U_CLUTR231_SHIFT       0 
#define LCDC_GDCCCLUTR115_U_CLUTR231_BIT         0xFF
#define LCDC_GDCCCLUTR115_U_CLUTR231_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR115_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR115_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR115_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR115_U_RESERVED_BITWIDTH    24
// GDCCCLUTR116_L Register
#define LCDC_GDCCCLUTR116_L_OFS                  0x000007A0
// CLUTR232 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR116_L_CLUTR232_MASK        0xFF
#define LCDC_GDCCCLUTR116_L_CLUTR232_SHIFT       0 
#define LCDC_GDCCCLUTR116_L_CLUTR232_BIT         0xFF
#define LCDC_GDCCCLUTR116_L_CLUTR232_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR116_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR116_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR116_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR116_L_RESERVED_BITWIDTH    24
// GDCCCLUTR116_U Register
#define LCDC_GDCCCLUTR116_U_OFS                  0x000007A4
// CLUTR233 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR116_U_CLUTR233_MASK        0xFF
#define LCDC_GDCCCLUTR116_U_CLUTR233_SHIFT       0 
#define LCDC_GDCCCLUTR116_U_CLUTR233_BIT         0xFF
#define LCDC_GDCCCLUTR116_U_CLUTR233_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR116_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR116_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR116_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR116_U_RESERVED_BITWIDTH    24
// GDCCCLUTR117_L Register
#define LCDC_GDCCCLUTR117_L_OFS                  0x000007A8
// CLUTR234 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR117_L_CLUTR234_MASK        0xFF
#define LCDC_GDCCCLUTR117_L_CLUTR234_SHIFT       0 
#define LCDC_GDCCCLUTR117_L_CLUTR234_BIT         0xFF
#define LCDC_GDCCCLUTR117_L_CLUTR234_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR117_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR117_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR117_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR117_L_RESERVED_BITWIDTH    24
// GDCCCLUTR117_U Register
#define LCDC_GDCCCLUTR117_U_OFS                  0x000007AC
// CLUTR235 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR117_U_CLUTR235_MASK        0xFF
#define LCDC_GDCCCLUTR117_U_CLUTR235_SHIFT       0 
#define LCDC_GDCCCLUTR117_U_CLUTR235_BIT         0xFF
#define LCDC_GDCCCLUTR117_U_CLUTR235_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR117_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR117_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR117_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR117_U_RESERVED_BITWIDTH    24
// GDCCCLUTR118_L Register
#define LCDC_GDCCCLUTR118_L_OFS                  0x000007B0
// CLUTR236 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR118_L_CLUTR236_MASK        0xFF
#define LCDC_GDCCCLUTR118_L_CLUTR236_SHIFT       0 
#define LCDC_GDCCCLUTR118_L_CLUTR236_BIT         0xFF
#define LCDC_GDCCCLUTR118_L_CLUTR236_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR118_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR118_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR118_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR118_L_RESERVED_BITWIDTH    24
// GDCCCLUTR118_U Register
#define LCDC_GDCCCLUTR118_U_OFS                  0x000007B4
// CLUTR237 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR118_U_CLUTR237_MASK        0xFF
#define LCDC_GDCCCLUTR118_U_CLUTR237_SHIFT       0 
#define LCDC_GDCCCLUTR118_U_CLUTR237_BIT         0xFF
#define LCDC_GDCCCLUTR118_U_CLUTR237_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR118_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR118_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR118_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR118_U_RESERVED_BITWIDTH    24
// GDCCCLUTR119_L Register
#define LCDC_GDCCCLUTR119_L_OFS                  0x000007B8
// CLUTR238 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR119_L_CLUTR238_MASK        0xFF
#define LCDC_GDCCCLUTR119_L_CLUTR238_SHIFT       0 
#define LCDC_GDCCCLUTR119_L_CLUTR238_BIT         0xFF
#define LCDC_GDCCCLUTR119_L_CLUTR238_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR119_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR119_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR119_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR119_L_RESERVED_BITWIDTH    24
// GDCCCLUTR119_U Register
#define LCDC_GDCCCLUTR119_U_OFS                  0x000007BC
// CLUTR239 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR119_U_CLUTR239_MASK        0xFF
#define LCDC_GDCCCLUTR119_U_CLUTR239_SHIFT       0 
#define LCDC_GDCCCLUTR119_U_CLUTR239_BIT         0xFF
#define LCDC_GDCCCLUTR119_U_CLUTR239_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR119_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR119_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR119_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR119_U_RESERVED_BITWIDTH    24
// GDCCCLUTR120_L Register
#define LCDC_GDCCCLUTR120_L_OFS                  0x000007C0
// CLUTR240 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR120_L_CLUTR240_MASK        0xFF
#define LCDC_GDCCCLUTR120_L_CLUTR240_SHIFT       0 
#define LCDC_GDCCCLUTR120_L_CLUTR240_BIT         0xFF
#define LCDC_GDCCCLUTR120_L_CLUTR240_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR120_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR120_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR120_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR120_L_RESERVED_BITWIDTH    24
// GDCCCLUTR120_U Register
#define LCDC_GDCCCLUTR120_U_OFS                  0x000007C4
// CLUTR241 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR120_U_CLUTR241_MASK        0xFF
#define LCDC_GDCCCLUTR120_U_CLUTR241_SHIFT       0 
#define LCDC_GDCCCLUTR120_U_CLUTR241_BIT         0xFF
#define LCDC_GDCCCLUTR120_U_CLUTR241_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR120_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR120_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR120_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR120_U_RESERVED_BITWIDTH    24
// GDCCCLUTR121_L Register
#define LCDC_GDCCCLUTR121_L_OFS                  0x000007C8
// CLUTR242 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR121_L_CLUTR242_MASK        0xFF
#define LCDC_GDCCCLUTR121_L_CLUTR242_SHIFT       0 
#define LCDC_GDCCCLUTR121_L_CLUTR242_BIT         0xFF
#define LCDC_GDCCCLUTR121_L_CLUTR242_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR121_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR121_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR121_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR121_L_RESERVED_BITWIDTH    24
// GDCCCLUTR121_U Register
#define LCDC_GDCCCLUTR121_U_OFS                  0x000007CC
// CLUTR243 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR121_U_CLUTR243_MASK        0xFF
#define LCDC_GDCCCLUTR121_U_CLUTR243_SHIFT       0 
#define LCDC_GDCCCLUTR121_U_CLUTR243_BIT         0xFF
#define LCDC_GDCCCLUTR121_U_CLUTR243_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR121_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR121_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR121_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR121_U_RESERVED_BITWIDTH    24
// GDCCCLUTR122_L Register
#define LCDC_GDCCCLUTR122_L_OFS                  0x000007D0
// CLUTR244 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR122_L_CLUTR244_MASK        0xFF
#define LCDC_GDCCCLUTR122_L_CLUTR244_SHIFT       0 
#define LCDC_GDCCCLUTR122_L_CLUTR244_BIT         0xFF
#define LCDC_GDCCCLUTR122_L_CLUTR244_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR122_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR122_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR122_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR122_L_RESERVED_BITWIDTH    24
// GDCCCLUTR122_U Register
#define LCDC_GDCCCLUTR122_U_OFS                  0x000007D4
// CLUTR245 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR122_U_CLUTR245_MASK        0xFF
#define LCDC_GDCCCLUTR122_U_CLUTR245_SHIFT       0 
#define LCDC_GDCCCLUTR122_U_CLUTR245_BIT         0xFF
#define LCDC_GDCCCLUTR122_U_CLUTR245_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR122_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR122_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR122_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR122_U_RESERVED_BITWIDTH    24
// GDCCCLUTR123_L Register
#define LCDC_GDCCCLUTR123_L_OFS                  0x000007D8
// CLUTR246 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR123_L_CLUTR246_MASK        0xFF
#define LCDC_GDCCCLUTR123_L_CLUTR246_SHIFT       0 
#define LCDC_GDCCCLUTR123_L_CLUTR246_BIT         0xFF
#define LCDC_GDCCCLUTR123_L_CLUTR246_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR123_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR123_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR123_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR123_L_RESERVED_BITWIDTH    24
// GDCCCLUTR123_U Register
#define LCDC_GDCCCLUTR123_U_OFS                  0x000007DC
// CLUTR247 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR123_U_CLUTR247_MASK        0xFF
#define LCDC_GDCCCLUTR123_U_CLUTR247_SHIFT       0 
#define LCDC_GDCCCLUTR123_U_CLUTR247_BIT         0xFF
#define LCDC_GDCCCLUTR123_U_CLUTR247_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR123_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR123_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR123_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR123_U_RESERVED_BITWIDTH    24
// GDCCCLUTR124_L Register
#define LCDC_GDCCCLUTR124_L_OFS                  0x000007E0
// CLUTR248 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR124_L_CLUTR248_MASK        0xFF
#define LCDC_GDCCCLUTR124_L_CLUTR248_SHIFT       0 
#define LCDC_GDCCCLUTR124_L_CLUTR248_BIT         0xFF
#define LCDC_GDCCCLUTR124_L_CLUTR248_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR124_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR124_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR124_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR124_L_RESERVED_BITWIDTH    24
// GDCCCLUTR124_U Register
#define LCDC_GDCCCLUTR124_U_OFS                  0x000007E4
// CLUTR249 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR124_U_CLUTR249_MASK        0xFF
#define LCDC_GDCCCLUTR124_U_CLUTR249_SHIFT       0 
#define LCDC_GDCCCLUTR124_U_CLUTR249_BIT         0xFF
#define LCDC_GDCCCLUTR124_U_CLUTR249_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR124_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR124_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR124_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR124_U_RESERVED_BITWIDTH    24
// GDCCCLUTR125_L Register
#define LCDC_GDCCCLUTR125_L_OFS                  0x000007E8
// CLUTR250 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR125_L_CLUTR250_MASK        0xFF
#define LCDC_GDCCCLUTR125_L_CLUTR250_SHIFT       0 
#define LCDC_GDCCCLUTR125_L_CLUTR250_BIT         0xFF
#define LCDC_GDCCCLUTR125_L_CLUTR250_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR125_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR125_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR125_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR125_L_RESERVED_BITWIDTH    24
// GDCCCLUTR125_U Register
#define LCDC_GDCCCLUTR125_U_OFS                  0x000007EC
// CLUTR251 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR125_U_CLUTR251_MASK        0xFF
#define LCDC_GDCCCLUTR125_U_CLUTR251_SHIFT       0 
#define LCDC_GDCCCLUTR125_U_CLUTR251_BIT         0xFF
#define LCDC_GDCCCLUTR125_U_CLUTR251_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR125_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR125_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR125_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR125_U_RESERVED_BITWIDTH    24
// GDCCCLUTR126_L Register
#define LCDC_GDCCCLUTR126_L_OFS                  0x000007F0
// CLUTR252 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR126_L_CLUTR252_MASK        0xFF
#define LCDC_GDCCCLUTR126_L_CLUTR252_SHIFT       0 
#define LCDC_GDCCCLUTR126_L_CLUTR252_BIT         0xFF
#define LCDC_GDCCCLUTR126_L_CLUTR252_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR126_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR126_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR126_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR126_L_RESERVED_BITWIDTH    24
// GDCCCLUTR126_U Register
#define LCDC_GDCCCLUTR126_U_OFS                  0x000007F4
// CLUTR253 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR126_U_CLUTR253_MASK        0xFF
#define LCDC_GDCCCLUTR126_U_CLUTR253_SHIFT       0 
#define LCDC_GDCCCLUTR126_U_CLUTR253_BIT         0xFF
#define LCDC_GDCCCLUTR126_U_CLUTR253_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR126_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR126_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR126_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR126_U_RESERVED_BITWIDTH    24
// GDCCCLUTR127_L Register
#define LCDC_GDCCCLUTR127_L_OFS                  0x000007F8
// CLUTR254 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR127_L_CLUTR254_MASK        0xFF
#define LCDC_GDCCCLUTR127_L_CLUTR254_SHIFT       0 
#define LCDC_GDCCCLUTR127_L_CLUTR254_BIT         0xFF
#define LCDC_GDCCCLUTR127_L_CLUTR254_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR127_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR127_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR127_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR127_L_RESERVED_BITWIDTH    24
// GDCCCLUTR127_U Register
#define LCDC_GDCCCLUTR127_U_OFS                  0x000007FC
// CLUTR255 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTR127_U_CLUTR255_MASK        0xFF
#define LCDC_GDCCCLUTR127_U_CLUTR255_SHIFT       0 
#define LCDC_GDCCCLUTR127_U_CLUTR255_BIT         0xFF
#define LCDC_GDCCCLUTR127_U_CLUTR255_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTR127_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTR127_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTR127_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTR127_U_RESERVED_BITWIDTH    24
// GDCCCLUTG0_L Register
#define LCDC_GDCCCLUTG0_L_OFS                    0x00000800
// CLUTG0 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG0_L_CLUTG0_MASK            0xFF
#define LCDC_GDCCCLUTG0_L_CLUTG0_SHIFT           0 
#define LCDC_GDCCCLUTG0_L_CLUTG0_BIT             0xFF
#define LCDC_GDCCCLUTG0_L_CLUTG0_BITWIDTH        8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG0_L_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTG0_L_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTG0_L_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTG0_L_RESERVED_BITWIDTH      24
// GDCCCLUTG0_U Register
#define LCDC_GDCCCLUTG0_U_OFS                    0x00000804
// CLUTG1 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG0_U_CLUTG1_MASK            0xFF
#define LCDC_GDCCCLUTG0_U_CLUTG1_SHIFT           0 
#define LCDC_GDCCCLUTG0_U_CLUTG1_BIT             0xFF
#define LCDC_GDCCCLUTG0_U_CLUTG1_BITWIDTH        8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG0_U_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTG0_U_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTG0_U_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTG0_U_RESERVED_BITWIDTH      24
// GDCCCLUTG1_L Register
#define LCDC_GDCCCLUTG1_L_OFS                    0x00000808
// CLUTG2 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG1_L_CLUTG2_MASK            0xFF
#define LCDC_GDCCCLUTG1_L_CLUTG2_SHIFT           0 
#define LCDC_GDCCCLUTG1_L_CLUTG2_BIT             0xFF
#define LCDC_GDCCCLUTG1_L_CLUTG2_BITWIDTH        8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG1_L_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTG1_L_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTG1_L_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTG1_L_RESERVED_BITWIDTH      24
// GDCCCLUTG1_U Register
#define LCDC_GDCCCLUTG1_U_OFS                    0x0000080C
// CLUTG3 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG1_U_CLUTG3_MASK            0xFF
#define LCDC_GDCCCLUTG1_U_CLUTG3_SHIFT           0 
#define LCDC_GDCCCLUTG1_U_CLUTG3_BIT             0xFF
#define LCDC_GDCCCLUTG1_U_CLUTG3_BITWIDTH        8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG1_U_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTG1_U_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTG1_U_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTG1_U_RESERVED_BITWIDTH      24
// GDCCCLUTG2_L Register
#define LCDC_GDCCCLUTG2_L_OFS                    0x00000810
// CLUTG4 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG2_L_CLUTG4_MASK            0xFF
#define LCDC_GDCCCLUTG2_L_CLUTG4_SHIFT           0 
#define LCDC_GDCCCLUTG2_L_CLUTG4_BIT             0xFF
#define LCDC_GDCCCLUTG2_L_CLUTG4_BITWIDTH        8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG2_L_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTG2_L_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTG2_L_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTG2_L_RESERVED_BITWIDTH      24
// GDCCCLUTG2_U Register
#define LCDC_GDCCCLUTG2_U_OFS                    0x00000814
// CLUTG5 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG2_U_CLUTG5_MASK            0xFF
#define LCDC_GDCCCLUTG2_U_CLUTG5_SHIFT           0 
#define LCDC_GDCCCLUTG2_U_CLUTG5_BIT             0xFF
#define LCDC_GDCCCLUTG2_U_CLUTG5_BITWIDTH        8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG2_U_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTG2_U_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTG2_U_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTG2_U_RESERVED_BITWIDTH      24
// GDCCCLUTG3_L Register
#define LCDC_GDCCCLUTG3_L_OFS                    0x00000818
// CLUTG6 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG3_L_CLUTG6_MASK            0xFF
#define LCDC_GDCCCLUTG3_L_CLUTG6_SHIFT           0 
#define LCDC_GDCCCLUTG3_L_CLUTG6_BIT             0xFF
#define LCDC_GDCCCLUTG3_L_CLUTG6_BITWIDTH        8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG3_L_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTG3_L_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTG3_L_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTG3_L_RESERVED_BITWIDTH      24
// GDCCCLUTG3_U Register
#define LCDC_GDCCCLUTG3_U_OFS                    0x0000081C
// CLUTG7 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG3_U_CLUTG7_MASK            0xFF
#define LCDC_GDCCCLUTG3_U_CLUTG7_SHIFT           0 
#define LCDC_GDCCCLUTG3_U_CLUTG7_BIT             0xFF
#define LCDC_GDCCCLUTG3_U_CLUTG7_BITWIDTH        8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG3_U_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTG3_U_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTG3_U_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTG3_U_RESERVED_BITWIDTH      24
// GDCCCLUTG4_L Register
#define LCDC_GDCCCLUTG4_L_OFS                    0x00000820
// CLUTG8 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG4_L_CLUTG8_MASK            0xFF
#define LCDC_GDCCCLUTG4_L_CLUTG8_SHIFT           0 
#define LCDC_GDCCCLUTG4_L_CLUTG8_BIT             0xFF
#define LCDC_GDCCCLUTG4_L_CLUTG8_BITWIDTH        8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG4_L_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTG4_L_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTG4_L_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTG4_L_RESERVED_BITWIDTH      24
// GDCCCLUTG4_U Register
#define LCDC_GDCCCLUTG4_U_OFS                    0x00000824
// CLUTG9 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG4_U_CLUTG9_MASK            0xFF
#define LCDC_GDCCCLUTG4_U_CLUTG9_SHIFT           0 
#define LCDC_GDCCCLUTG4_U_CLUTG9_BIT             0xFF
#define LCDC_GDCCCLUTG4_U_CLUTG9_BITWIDTH        8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG4_U_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTG4_U_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTG4_U_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTG4_U_RESERVED_BITWIDTH      24
// GDCCCLUTG5_L Register
#define LCDC_GDCCCLUTG5_L_OFS                    0x00000828
// CLUTG10 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG5_L_CLUTG10_MASK           0xFF
#define LCDC_GDCCCLUTG5_L_CLUTG10_SHIFT          0 
#define LCDC_GDCCCLUTG5_L_CLUTG10_BIT            0xFF
#define LCDC_GDCCCLUTG5_L_CLUTG10_BITWIDTH       8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG5_L_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTG5_L_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTG5_L_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTG5_L_RESERVED_BITWIDTH      24
// GDCCCLUTG5_U Register
#define LCDC_GDCCCLUTG5_U_OFS                    0x0000082C
// CLUTG11 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG5_U_CLUTG11_MASK           0xFF
#define LCDC_GDCCCLUTG5_U_CLUTG11_SHIFT          0 
#define LCDC_GDCCCLUTG5_U_CLUTG11_BIT            0xFF
#define LCDC_GDCCCLUTG5_U_CLUTG11_BITWIDTH       8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG5_U_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTG5_U_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTG5_U_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTG5_U_RESERVED_BITWIDTH      24
// GDCCCLUTG6_L Register
#define LCDC_GDCCCLUTG6_L_OFS                    0x00000830
// CLUTG12 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG6_L_CLUTG12_MASK           0xFF
#define LCDC_GDCCCLUTG6_L_CLUTG12_SHIFT          0 
#define LCDC_GDCCCLUTG6_L_CLUTG12_BIT            0xFF
#define LCDC_GDCCCLUTG6_L_CLUTG12_BITWIDTH       8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG6_L_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTG6_L_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTG6_L_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTG6_L_RESERVED_BITWIDTH      24
// GDCCCLUTG6_U Register
#define LCDC_GDCCCLUTG6_U_OFS                    0x00000834
// CLUTG13 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG6_U_CLUTG13_MASK           0xFF
#define LCDC_GDCCCLUTG6_U_CLUTG13_SHIFT          0 
#define LCDC_GDCCCLUTG6_U_CLUTG13_BIT            0xFF
#define LCDC_GDCCCLUTG6_U_CLUTG13_BITWIDTH       8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG6_U_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTG6_U_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTG6_U_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTG6_U_RESERVED_BITWIDTH      24
// GDCCCLUTG7_L Register
#define LCDC_GDCCCLUTG7_L_OFS                    0x00000838
// CLUTG14 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG7_L_CLUTG14_MASK           0xFF
#define LCDC_GDCCCLUTG7_L_CLUTG14_SHIFT          0 
#define LCDC_GDCCCLUTG7_L_CLUTG14_BIT            0xFF
#define LCDC_GDCCCLUTG7_L_CLUTG14_BITWIDTH       8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG7_L_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTG7_L_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTG7_L_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTG7_L_RESERVED_BITWIDTH      24
// GDCCCLUTG7_U Register
#define LCDC_GDCCCLUTG7_U_OFS                    0x0000083C
// CLUTG15 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG7_U_CLUTG15_MASK           0xFF
#define LCDC_GDCCCLUTG7_U_CLUTG15_SHIFT          0 
#define LCDC_GDCCCLUTG7_U_CLUTG15_BIT            0xFF
#define LCDC_GDCCCLUTG7_U_CLUTG15_BITWIDTH       8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG7_U_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTG7_U_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTG7_U_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTG7_U_RESERVED_BITWIDTH      24
// GDCCCLUTG8_L Register
#define LCDC_GDCCCLUTG8_L_OFS                    0x00000840
// CLUTG16 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG8_L_CLUTG16_MASK           0xFF
#define LCDC_GDCCCLUTG8_L_CLUTG16_SHIFT          0 
#define LCDC_GDCCCLUTG8_L_CLUTG16_BIT            0xFF
#define LCDC_GDCCCLUTG8_L_CLUTG16_BITWIDTH       8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG8_L_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTG8_L_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTG8_L_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTG8_L_RESERVED_BITWIDTH      24
// GDCCCLUTG8_U Register
#define LCDC_GDCCCLUTG8_U_OFS                    0x00000844
// CLUTG17 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG8_U_CLUTG17_MASK           0xFF
#define LCDC_GDCCCLUTG8_U_CLUTG17_SHIFT          0 
#define LCDC_GDCCCLUTG8_U_CLUTG17_BIT            0xFF
#define LCDC_GDCCCLUTG8_U_CLUTG17_BITWIDTH       8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG8_U_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTG8_U_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTG8_U_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTG8_U_RESERVED_BITWIDTH      24
// GDCCCLUTG9_L Register
#define LCDC_GDCCCLUTG9_L_OFS                    0x00000848
// CLUTG18 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG9_L_CLUTG18_MASK           0xFF
#define LCDC_GDCCCLUTG9_L_CLUTG18_SHIFT          0 
#define LCDC_GDCCCLUTG9_L_CLUTG18_BIT            0xFF
#define LCDC_GDCCCLUTG9_L_CLUTG18_BITWIDTH       8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG9_L_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTG9_L_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTG9_L_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTG9_L_RESERVED_BITWIDTH      24
// GDCCCLUTG9_U Register
#define LCDC_GDCCCLUTG9_U_OFS                    0x0000084C
// CLUTG19 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG9_U_CLUTG19_MASK           0xFF
#define LCDC_GDCCCLUTG9_U_CLUTG19_SHIFT          0 
#define LCDC_GDCCCLUTG9_U_CLUTG19_BIT            0xFF
#define LCDC_GDCCCLUTG9_U_CLUTG19_BITWIDTH       8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG9_U_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTG9_U_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTG9_U_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTG9_U_RESERVED_BITWIDTH      24
// GDCCCLUTG10_L Register
#define LCDC_GDCCCLUTG10_L_OFS                   0x00000850
// CLUTG20 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG10_L_CLUTG20_MASK          0xFF
#define LCDC_GDCCCLUTG10_L_CLUTG20_SHIFT         0 
#define LCDC_GDCCCLUTG10_L_CLUTG20_BIT           0xFF
#define LCDC_GDCCCLUTG10_L_CLUTG20_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG10_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG10_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG10_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG10_L_RESERVED_BITWIDTH     24
// GDCCCLUTG10_U Register
#define LCDC_GDCCCLUTG10_U_OFS                   0x00000854
// CLUTG21 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG10_U_CLUTG21_MASK          0xFF
#define LCDC_GDCCCLUTG10_U_CLUTG21_SHIFT         0 
#define LCDC_GDCCCLUTG10_U_CLUTG21_BIT           0xFF
#define LCDC_GDCCCLUTG10_U_CLUTG21_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG10_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG10_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG10_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG10_U_RESERVED_BITWIDTH     24
// GDCCCLUTG11_L Register
#define LCDC_GDCCCLUTG11_L_OFS                   0x00000858
// CLUTG22 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG11_L_CLUTG22_MASK          0xFF
#define LCDC_GDCCCLUTG11_L_CLUTG22_SHIFT         0 
#define LCDC_GDCCCLUTG11_L_CLUTG22_BIT           0xFF
#define LCDC_GDCCCLUTG11_L_CLUTG22_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG11_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG11_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG11_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG11_L_RESERVED_BITWIDTH     24
// GDCCCLUTG11_U Register
#define LCDC_GDCCCLUTG11_U_OFS                   0x0000085C
// CLUTG23 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG11_U_CLUTG23_MASK          0xFF
#define LCDC_GDCCCLUTG11_U_CLUTG23_SHIFT         0 
#define LCDC_GDCCCLUTG11_U_CLUTG23_BIT           0xFF
#define LCDC_GDCCCLUTG11_U_CLUTG23_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG11_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG11_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG11_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG11_U_RESERVED_BITWIDTH     24
// GDCCCLUTG12_L Register
#define LCDC_GDCCCLUTG12_L_OFS                   0x00000860
// CLUTG24 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG12_L_CLUTG24_MASK          0xFF
#define LCDC_GDCCCLUTG12_L_CLUTG24_SHIFT         0 
#define LCDC_GDCCCLUTG12_L_CLUTG24_BIT           0xFF
#define LCDC_GDCCCLUTG12_L_CLUTG24_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG12_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG12_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG12_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG12_L_RESERVED_BITWIDTH     24
// GDCCCLUTG12_U Register
#define LCDC_GDCCCLUTG12_U_OFS                   0x00000864
// CLUTG25 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG12_U_CLUTG25_MASK          0xFF
#define LCDC_GDCCCLUTG12_U_CLUTG25_SHIFT         0 
#define LCDC_GDCCCLUTG12_U_CLUTG25_BIT           0xFF
#define LCDC_GDCCCLUTG12_U_CLUTG25_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG12_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG12_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG12_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG12_U_RESERVED_BITWIDTH     24
// GDCCCLUTG13_L Register
#define LCDC_GDCCCLUTG13_L_OFS                   0x00000868
// CLUTG26 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG13_L_CLUTG26_MASK          0xFF
#define LCDC_GDCCCLUTG13_L_CLUTG26_SHIFT         0 
#define LCDC_GDCCCLUTG13_L_CLUTG26_BIT           0xFF
#define LCDC_GDCCCLUTG13_L_CLUTG26_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG13_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG13_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG13_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG13_L_RESERVED_BITWIDTH     24
// GDCCCLUTG13_U Register
#define LCDC_GDCCCLUTG13_U_OFS                   0x0000086C
// CLUTG27 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG13_U_CLUTG27_MASK          0xFF
#define LCDC_GDCCCLUTG13_U_CLUTG27_SHIFT         0 
#define LCDC_GDCCCLUTG13_U_CLUTG27_BIT           0xFF
#define LCDC_GDCCCLUTG13_U_CLUTG27_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG13_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG13_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG13_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG13_U_RESERVED_BITWIDTH     24
// GDCCCLUTG14_L Register
#define LCDC_GDCCCLUTG14_L_OFS                   0x00000870
// CLUTG28 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG14_L_CLUTG28_MASK          0xFF
#define LCDC_GDCCCLUTG14_L_CLUTG28_SHIFT         0 
#define LCDC_GDCCCLUTG14_L_CLUTG28_BIT           0xFF
#define LCDC_GDCCCLUTG14_L_CLUTG28_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG14_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG14_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG14_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG14_L_RESERVED_BITWIDTH     24
// GDCCCLUTG14_U Register
#define LCDC_GDCCCLUTG14_U_OFS                   0x00000874
// CLUTG29 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG14_U_CLUTG29_MASK          0xFF
#define LCDC_GDCCCLUTG14_U_CLUTG29_SHIFT         0 
#define LCDC_GDCCCLUTG14_U_CLUTG29_BIT           0xFF
#define LCDC_GDCCCLUTG14_U_CLUTG29_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG14_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG14_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG14_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG14_U_RESERVED_BITWIDTH     24
// GDCCCLUTG15_L Register
#define LCDC_GDCCCLUTG15_L_OFS                   0x00000878
// CLUTG30 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG15_L_CLUTG30_MASK          0xFF
#define LCDC_GDCCCLUTG15_L_CLUTG30_SHIFT         0 
#define LCDC_GDCCCLUTG15_L_CLUTG30_BIT           0xFF
#define LCDC_GDCCCLUTG15_L_CLUTG30_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG15_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG15_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG15_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG15_L_RESERVED_BITWIDTH     24
// GDCCCLUTG15_U Register
#define LCDC_GDCCCLUTG15_U_OFS                   0x0000087C
// CLUTG31 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG15_U_CLUTG31_MASK          0xFF
#define LCDC_GDCCCLUTG15_U_CLUTG31_SHIFT         0 
#define LCDC_GDCCCLUTG15_U_CLUTG31_BIT           0xFF
#define LCDC_GDCCCLUTG15_U_CLUTG31_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG15_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG15_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG15_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG15_U_RESERVED_BITWIDTH     24
// GDCCCLUTG16_L Register
#define LCDC_GDCCCLUTG16_L_OFS                   0x00000880
// CLUTG32 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG16_L_CLUTG32_MASK          0xFF
#define LCDC_GDCCCLUTG16_L_CLUTG32_SHIFT         0 
#define LCDC_GDCCCLUTG16_L_CLUTG32_BIT           0xFF
#define LCDC_GDCCCLUTG16_L_CLUTG32_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG16_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG16_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG16_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG16_L_RESERVED_BITWIDTH     24
// GDCCCLUTG16_U Register
#define LCDC_GDCCCLUTG16_U_OFS                   0x00000884
// CLUTG33 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG16_U_CLUTG33_MASK          0xFF
#define LCDC_GDCCCLUTG16_U_CLUTG33_SHIFT         0 
#define LCDC_GDCCCLUTG16_U_CLUTG33_BIT           0xFF
#define LCDC_GDCCCLUTG16_U_CLUTG33_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG16_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG16_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG16_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG16_U_RESERVED_BITWIDTH     24
// GDCCCLUTG17_L Register
#define LCDC_GDCCCLUTG17_L_OFS                   0x00000888
// CLUTG34 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG17_L_CLUTG34_MASK          0xFF
#define LCDC_GDCCCLUTG17_L_CLUTG34_SHIFT         0 
#define LCDC_GDCCCLUTG17_L_CLUTG34_BIT           0xFF
#define LCDC_GDCCCLUTG17_L_CLUTG34_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG17_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG17_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG17_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG17_L_RESERVED_BITWIDTH     24
// GDCCCLUTG17_U Register
#define LCDC_GDCCCLUTG17_U_OFS                   0x0000088C
// CLUTG35 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG17_U_CLUTG35_MASK          0xFF
#define LCDC_GDCCCLUTG17_U_CLUTG35_SHIFT         0 
#define LCDC_GDCCCLUTG17_U_CLUTG35_BIT           0xFF
#define LCDC_GDCCCLUTG17_U_CLUTG35_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG17_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG17_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG17_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG17_U_RESERVED_BITWIDTH     24
// GDCCCLUTG18_L Register
#define LCDC_GDCCCLUTG18_L_OFS                   0x00000890
// CLUTG36 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG18_L_CLUTG36_MASK          0xFF
#define LCDC_GDCCCLUTG18_L_CLUTG36_SHIFT         0 
#define LCDC_GDCCCLUTG18_L_CLUTG36_BIT           0xFF
#define LCDC_GDCCCLUTG18_L_CLUTG36_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG18_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG18_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG18_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG18_L_RESERVED_BITWIDTH     24
// GDCCCLUTG18_U Register
#define LCDC_GDCCCLUTG18_U_OFS                   0x00000894
// CLUTG37 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG18_U_CLUTG37_MASK          0xFF
#define LCDC_GDCCCLUTG18_U_CLUTG37_SHIFT         0 
#define LCDC_GDCCCLUTG18_U_CLUTG37_BIT           0xFF
#define LCDC_GDCCCLUTG18_U_CLUTG37_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG18_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG18_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG18_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG18_U_RESERVED_BITWIDTH     24
// GDCCCLUTG19_L Register
#define LCDC_GDCCCLUTG19_L_OFS                   0x00000898
// CLUTG38 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG19_L_CLUTG38_MASK          0xFF
#define LCDC_GDCCCLUTG19_L_CLUTG38_SHIFT         0 
#define LCDC_GDCCCLUTG19_L_CLUTG38_BIT           0xFF
#define LCDC_GDCCCLUTG19_L_CLUTG38_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG19_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG19_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG19_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG19_L_RESERVED_BITWIDTH     24
// GDCCCLUTG19_U Register
#define LCDC_GDCCCLUTG19_U_OFS                   0x0000089C
// CLUTG39 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG19_U_CLUTG39_MASK          0xFF
#define LCDC_GDCCCLUTG19_U_CLUTG39_SHIFT         0 
#define LCDC_GDCCCLUTG19_U_CLUTG39_BIT           0xFF
#define LCDC_GDCCCLUTG19_U_CLUTG39_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG19_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG19_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG19_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG19_U_RESERVED_BITWIDTH     24
// GDCCCLUTG20_L Register
#define LCDC_GDCCCLUTG20_L_OFS                   0x000008A0
// CLUTG40 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG20_L_CLUTG40_MASK          0xFF
#define LCDC_GDCCCLUTG20_L_CLUTG40_SHIFT         0 
#define LCDC_GDCCCLUTG20_L_CLUTG40_BIT           0xFF
#define LCDC_GDCCCLUTG20_L_CLUTG40_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG20_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG20_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG20_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG20_L_RESERVED_BITWIDTH     24
// GDCCCLUTG20_U Register
#define LCDC_GDCCCLUTG20_U_OFS                   0x000008A4
// CLUTG41 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG20_U_CLUTG41_MASK          0xFF
#define LCDC_GDCCCLUTG20_U_CLUTG41_SHIFT         0 
#define LCDC_GDCCCLUTG20_U_CLUTG41_BIT           0xFF
#define LCDC_GDCCCLUTG20_U_CLUTG41_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG20_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG20_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG20_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG20_U_RESERVED_BITWIDTH     24
// GDCCCLUTG21_L Register
#define LCDC_GDCCCLUTG21_L_OFS                   0x000008A8
// CLUTG42 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG21_L_CLUTG42_MASK          0xFF
#define LCDC_GDCCCLUTG21_L_CLUTG42_SHIFT         0 
#define LCDC_GDCCCLUTG21_L_CLUTG42_BIT           0xFF
#define LCDC_GDCCCLUTG21_L_CLUTG42_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG21_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG21_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG21_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG21_L_RESERVED_BITWIDTH     24
// GDCCCLUTG21_U Register
#define LCDC_GDCCCLUTG21_U_OFS                   0x000008AC
// CLUTG43 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG21_U_CLUTG43_MASK          0xFF
#define LCDC_GDCCCLUTG21_U_CLUTG43_SHIFT         0 
#define LCDC_GDCCCLUTG21_U_CLUTG43_BIT           0xFF
#define LCDC_GDCCCLUTG21_U_CLUTG43_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG21_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG21_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG21_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG21_U_RESERVED_BITWIDTH     24
// GDCCCLUTG22_L Register
#define LCDC_GDCCCLUTG22_L_OFS                   0x000008B0
// CLUTG44 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG22_L_CLUTG44_MASK          0xFF
#define LCDC_GDCCCLUTG22_L_CLUTG44_SHIFT         0 
#define LCDC_GDCCCLUTG22_L_CLUTG44_BIT           0xFF
#define LCDC_GDCCCLUTG22_L_CLUTG44_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG22_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG22_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG22_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG22_L_RESERVED_BITWIDTH     24
// GDCCCLUTG22_U Register
#define LCDC_GDCCCLUTG22_U_OFS                   0x000008B4
// CLUTG45 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG22_U_CLUTG45_MASK          0xFF
#define LCDC_GDCCCLUTG22_U_CLUTG45_SHIFT         0 
#define LCDC_GDCCCLUTG22_U_CLUTG45_BIT           0xFF
#define LCDC_GDCCCLUTG22_U_CLUTG45_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG22_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG22_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG22_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG22_U_RESERVED_BITWIDTH     24
// GDCCCLUTG23_L Register
#define LCDC_GDCCCLUTG23_L_OFS                   0x000008B8
// CLUTG46 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG23_L_CLUTG46_MASK          0xFF
#define LCDC_GDCCCLUTG23_L_CLUTG46_SHIFT         0 
#define LCDC_GDCCCLUTG23_L_CLUTG46_BIT           0xFF
#define LCDC_GDCCCLUTG23_L_CLUTG46_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG23_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG23_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG23_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG23_L_RESERVED_BITWIDTH     24
// GDCCCLUTG23_U Register
#define LCDC_GDCCCLUTG23_U_OFS                   0x000008BC
// CLUTG47 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG23_U_CLUTG47_MASK          0xFF
#define LCDC_GDCCCLUTG23_U_CLUTG47_SHIFT         0 
#define LCDC_GDCCCLUTG23_U_CLUTG47_BIT           0xFF
#define LCDC_GDCCCLUTG23_U_CLUTG47_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG23_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG23_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG23_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG23_U_RESERVED_BITWIDTH     24
// GDCCCLUTG24_L Register
#define LCDC_GDCCCLUTG24_L_OFS                   0x000008C0
// CLUTG48 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG24_L_CLUTG48_MASK          0xFF
#define LCDC_GDCCCLUTG24_L_CLUTG48_SHIFT         0 
#define LCDC_GDCCCLUTG24_L_CLUTG48_BIT           0xFF
#define LCDC_GDCCCLUTG24_L_CLUTG48_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG24_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG24_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG24_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG24_L_RESERVED_BITWIDTH     24
// GDCCCLUTG24_U Register
#define LCDC_GDCCCLUTG24_U_OFS                   0x000008C4
// CLUTG49 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG24_U_CLUTG49_MASK          0xFF
#define LCDC_GDCCCLUTG24_U_CLUTG49_SHIFT         0 
#define LCDC_GDCCCLUTG24_U_CLUTG49_BIT           0xFF
#define LCDC_GDCCCLUTG24_U_CLUTG49_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG24_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG24_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG24_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG24_U_RESERVED_BITWIDTH     24
// GDCCCLUTG25_L Register
#define LCDC_GDCCCLUTG25_L_OFS                   0x000008C8
// CLUTG50 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG25_L_CLUTG50_MASK          0xFF
#define LCDC_GDCCCLUTG25_L_CLUTG50_SHIFT         0 
#define LCDC_GDCCCLUTG25_L_CLUTG50_BIT           0xFF
#define LCDC_GDCCCLUTG25_L_CLUTG50_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG25_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG25_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG25_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG25_L_RESERVED_BITWIDTH     24
// GDCCCLUTG25_U Register
#define LCDC_GDCCCLUTG25_U_OFS                   0x000008CC
// CLUTG51 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG25_U_CLUTG51_MASK          0xFF
#define LCDC_GDCCCLUTG25_U_CLUTG51_SHIFT         0 
#define LCDC_GDCCCLUTG25_U_CLUTG51_BIT           0xFF
#define LCDC_GDCCCLUTG25_U_CLUTG51_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG25_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG25_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG25_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG25_U_RESERVED_BITWIDTH     24
// GDCCCLUTG26_L Register
#define LCDC_GDCCCLUTG26_L_OFS                   0x000008D0
// CLUTG52 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG26_L_CLUTG52_MASK          0xFF
#define LCDC_GDCCCLUTG26_L_CLUTG52_SHIFT         0 
#define LCDC_GDCCCLUTG26_L_CLUTG52_BIT           0xFF
#define LCDC_GDCCCLUTG26_L_CLUTG52_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG26_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG26_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG26_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG26_L_RESERVED_BITWIDTH     24
// GDCCCLUTG26_U Register
#define LCDC_GDCCCLUTG26_U_OFS                   0x000008D4
// CLUTG53 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG26_U_CLUTG53_MASK          0xFF
#define LCDC_GDCCCLUTG26_U_CLUTG53_SHIFT         0 
#define LCDC_GDCCCLUTG26_U_CLUTG53_BIT           0xFF
#define LCDC_GDCCCLUTG26_U_CLUTG53_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG26_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG26_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG26_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG26_U_RESERVED_BITWIDTH     24
// GDCCCLUTG27_L Register
#define LCDC_GDCCCLUTG27_L_OFS                   0x000008D8
// CLUTG54 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG27_L_CLUTG54_MASK          0xFF
#define LCDC_GDCCCLUTG27_L_CLUTG54_SHIFT         0 
#define LCDC_GDCCCLUTG27_L_CLUTG54_BIT           0xFF
#define LCDC_GDCCCLUTG27_L_CLUTG54_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG27_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG27_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG27_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG27_L_RESERVED_BITWIDTH     24
// GDCCCLUTG27_U Register
#define LCDC_GDCCCLUTG27_U_OFS                   0x000008DC
// CLUTG55 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG27_U_CLUTG55_MASK          0xFF
#define LCDC_GDCCCLUTG27_U_CLUTG55_SHIFT         0 
#define LCDC_GDCCCLUTG27_U_CLUTG55_BIT           0xFF
#define LCDC_GDCCCLUTG27_U_CLUTG55_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG27_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG27_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG27_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG27_U_RESERVED_BITWIDTH     24
// GDCCCLUTG28_L Register
#define LCDC_GDCCCLUTG28_L_OFS                   0x000008E0
// CLUTG56 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG28_L_CLUTG56_MASK          0xFF
#define LCDC_GDCCCLUTG28_L_CLUTG56_SHIFT         0 
#define LCDC_GDCCCLUTG28_L_CLUTG56_BIT           0xFF
#define LCDC_GDCCCLUTG28_L_CLUTG56_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG28_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG28_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG28_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG28_L_RESERVED_BITWIDTH     24
// GDCCCLUTG28_U Register
#define LCDC_GDCCCLUTG28_U_OFS                   0x000008E4
// CLUTG57 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG28_U_CLUTG57_MASK          0xFF
#define LCDC_GDCCCLUTG28_U_CLUTG57_SHIFT         0 
#define LCDC_GDCCCLUTG28_U_CLUTG57_BIT           0xFF
#define LCDC_GDCCCLUTG28_U_CLUTG57_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG28_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG28_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG28_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG28_U_RESERVED_BITWIDTH     24
// GDCCCLUTG29_L Register
#define LCDC_GDCCCLUTG29_L_OFS                   0x000008E8
// CLUTG58 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG29_L_CLUTG58_MASK          0xFF
#define LCDC_GDCCCLUTG29_L_CLUTG58_SHIFT         0 
#define LCDC_GDCCCLUTG29_L_CLUTG58_BIT           0xFF
#define LCDC_GDCCCLUTG29_L_CLUTG58_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG29_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG29_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG29_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG29_L_RESERVED_BITWIDTH     24
// GDCCCLUTG29_U Register
#define LCDC_GDCCCLUTG29_U_OFS                   0x000008EC
// CLUTG59 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG29_U_CLUTG59_MASK          0xFF
#define LCDC_GDCCCLUTG29_U_CLUTG59_SHIFT         0 
#define LCDC_GDCCCLUTG29_U_CLUTG59_BIT           0xFF
#define LCDC_GDCCCLUTG29_U_CLUTG59_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG29_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG29_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG29_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG29_U_RESERVED_BITWIDTH     24
// GDCCCLUTG30_L Register
#define LCDC_GDCCCLUTG30_L_OFS                   0x000008F0
// CLUTG60 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG30_L_CLUTG60_MASK          0xFF
#define LCDC_GDCCCLUTG30_L_CLUTG60_SHIFT         0 
#define LCDC_GDCCCLUTG30_L_CLUTG60_BIT           0xFF
#define LCDC_GDCCCLUTG30_L_CLUTG60_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG30_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG30_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG30_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG30_L_RESERVED_BITWIDTH     24
// GDCCCLUTG30_U Register
#define LCDC_GDCCCLUTG30_U_OFS                   0x000008F4
// CLUTG61 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG30_U_CLUTG61_MASK          0xFF
#define LCDC_GDCCCLUTG30_U_CLUTG61_SHIFT         0 
#define LCDC_GDCCCLUTG30_U_CLUTG61_BIT           0xFF
#define LCDC_GDCCCLUTG30_U_CLUTG61_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG30_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG30_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG30_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG30_U_RESERVED_BITWIDTH     24
// GDCCCLUTG31_L Register
#define LCDC_GDCCCLUTG31_L_OFS                   0x000008F8
// CLUTG62 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG31_L_CLUTG62_MASK          0xFF
#define LCDC_GDCCCLUTG31_L_CLUTG62_SHIFT         0 
#define LCDC_GDCCCLUTG31_L_CLUTG62_BIT           0xFF
#define LCDC_GDCCCLUTG31_L_CLUTG62_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG31_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG31_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG31_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG31_L_RESERVED_BITWIDTH     24
// GDCCCLUTG31_U Register
#define LCDC_GDCCCLUTG31_U_OFS                   0x000008FC
// CLUTG63 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG31_U_CLUTG63_MASK          0xFF
#define LCDC_GDCCCLUTG31_U_CLUTG63_SHIFT         0 
#define LCDC_GDCCCLUTG31_U_CLUTG63_BIT           0xFF
#define LCDC_GDCCCLUTG31_U_CLUTG63_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG31_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG31_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG31_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG31_U_RESERVED_BITWIDTH     24
// GDCCCLUTG32_L Register
#define LCDC_GDCCCLUTG32_L_OFS                   0x00000900
// CLUTG64 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG32_L_CLUTG64_MASK          0xFF
#define LCDC_GDCCCLUTG32_L_CLUTG64_SHIFT         0 
#define LCDC_GDCCCLUTG32_L_CLUTG64_BIT           0xFF
#define LCDC_GDCCCLUTG32_L_CLUTG64_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG32_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG32_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG32_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG32_L_RESERVED_BITWIDTH     24
// GDCCCLUTG32_U Register
#define LCDC_GDCCCLUTG32_U_OFS                   0x00000904
// CLUTG65 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG32_U_CLUTG65_MASK          0xFF
#define LCDC_GDCCCLUTG32_U_CLUTG65_SHIFT         0 
#define LCDC_GDCCCLUTG32_U_CLUTG65_BIT           0xFF
#define LCDC_GDCCCLUTG32_U_CLUTG65_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG32_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG32_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG32_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG32_U_RESERVED_BITWIDTH     24
// GDCCCLUTG33_L Register
#define LCDC_GDCCCLUTG33_L_OFS                   0x00000908
// CLUTG66 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG33_L_CLUTG66_MASK          0xFF
#define LCDC_GDCCCLUTG33_L_CLUTG66_SHIFT         0 
#define LCDC_GDCCCLUTG33_L_CLUTG66_BIT           0xFF
#define LCDC_GDCCCLUTG33_L_CLUTG66_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG33_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG33_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG33_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG33_L_RESERVED_BITWIDTH     24
// GDCCCLUTG33_U Register
#define LCDC_GDCCCLUTG33_U_OFS                   0x0000090C
// CLUTG67 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG33_U_CLUTG67_MASK          0xFF
#define LCDC_GDCCCLUTG33_U_CLUTG67_SHIFT         0 
#define LCDC_GDCCCLUTG33_U_CLUTG67_BIT           0xFF
#define LCDC_GDCCCLUTG33_U_CLUTG67_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG33_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG33_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG33_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG33_U_RESERVED_BITWIDTH     24
// GDCCCLUTG34_L Register
#define LCDC_GDCCCLUTG34_L_OFS                   0x00000910
// CLUTG68 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG34_L_CLUTG68_MASK          0xFF
#define LCDC_GDCCCLUTG34_L_CLUTG68_SHIFT         0 
#define LCDC_GDCCCLUTG34_L_CLUTG68_BIT           0xFF
#define LCDC_GDCCCLUTG34_L_CLUTG68_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG34_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG34_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG34_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG34_L_RESERVED_BITWIDTH     24
// GDCCCLUTG34_U Register
#define LCDC_GDCCCLUTG34_U_OFS                   0x00000914
// CLUTG69 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG34_U_CLUTG69_MASK          0xFF
#define LCDC_GDCCCLUTG34_U_CLUTG69_SHIFT         0 
#define LCDC_GDCCCLUTG34_U_CLUTG69_BIT           0xFF
#define LCDC_GDCCCLUTG34_U_CLUTG69_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG34_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG34_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG34_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG34_U_RESERVED_BITWIDTH     24
// GDCCCLUTG35_L Register
#define LCDC_GDCCCLUTG35_L_OFS                   0x00000918
// CLUTG70 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG35_L_CLUTG70_MASK          0xFF
#define LCDC_GDCCCLUTG35_L_CLUTG70_SHIFT         0 
#define LCDC_GDCCCLUTG35_L_CLUTG70_BIT           0xFF
#define LCDC_GDCCCLUTG35_L_CLUTG70_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG35_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG35_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG35_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG35_L_RESERVED_BITWIDTH     24
// GDCCCLUTG35_U Register
#define LCDC_GDCCCLUTG35_U_OFS                   0x0000091C
// CLUTG71 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG35_U_CLUTG71_MASK          0xFF
#define LCDC_GDCCCLUTG35_U_CLUTG71_SHIFT         0 
#define LCDC_GDCCCLUTG35_U_CLUTG71_BIT           0xFF
#define LCDC_GDCCCLUTG35_U_CLUTG71_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG35_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG35_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG35_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG35_U_RESERVED_BITWIDTH     24
// GDCCCLUTG36_L Register
#define LCDC_GDCCCLUTG36_L_OFS                   0x00000920
// CLUTG72 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG36_L_CLUTG72_MASK          0xFF
#define LCDC_GDCCCLUTG36_L_CLUTG72_SHIFT         0 
#define LCDC_GDCCCLUTG36_L_CLUTG72_BIT           0xFF
#define LCDC_GDCCCLUTG36_L_CLUTG72_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG36_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG36_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG36_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG36_L_RESERVED_BITWIDTH     24
// GDCCCLUTG36_U Register
#define LCDC_GDCCCLUTG36_U_OFS                   0x00000924
// CLUTG73 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG36_U_CLUTG73_MASK          0xFF
#define LCDC_GDCCCLUTG36_U_CLUTG73_SHIFT         0 
#define LCDC_GDCCCLUTG36_U_CLUTG73_BIT           0xFF
#define LCDC_GDCCCLUTG36_U_CLUTG73_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG36_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG36_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG36_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG36_U_RESERVED_BITWIDTH     24
// GDCCCLUTG37_L Register
#define LCDC_GDCCCLUTG37_L_OFS                   0x00000928
// CLUTG74 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG37_L_CLUTG74_MASK          0xFF
#define LCDC_GDCCCLUTG37_L_CLUTG74_SHIFT         0 
#define LCDC_GDCCCLUTG37_L_CLUTG74_BIT           0xFF
#define LCDC_GDCCCLUTG37_L_CLUTG74_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG37_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG37_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG37_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG37_L_RESERVED_BITWIDTH     24
// GDCCCLUTG37_U Register
#define LCDC_GDCCCLUTG37_U_OFS                   0x0000092C
// CLUTG75 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG37_U_CLUTG75_MASK          0xFF
#define LCDC_GDCCCLUTG37_U_CLUTG75_SHIFT         0 
#define LCDC_GDCCCLUTG37_U_CLUTG75_BIT           0xFF
#define LCDC_GDCCCLUTG37_U_CLUTG75_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG37_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG37_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG37_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG37_U_RESERVED_BITWIDTH     24
// GDCCCLUTG38_L Register
#define LCDC_GDCCCLUTG38_L_OFS                   0x00000930
// CLUTG76 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG38_L_CLUTG76_MASK          0xFF
#define LCDC_GDCCCLUTG38_L_CLUTG76_SHIFT         0 
#define LCDC_GDCCCLUTG38_L_CLUTG76_BIT           0xFF
#define LCDC_GDCCCLUTG38_L_CLUTG76_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG38_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG38_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG38_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG38_L_RESERVED_BITWIDTH     24
// GDCCCLUTG38_U Register
#define LCDC_GDCCCLUTG38_U_OFS                   0x00000934
// CLUTG77 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG38_U_CLUTG77_MASK          0xFF
#define LCDC_GDCCCLUTG38_U_CLUTG77_SHIFT         0 
#define LCDC_GDCCCLUTG38_U_CLUTG77_BIT           0xFF
#define LCDC_GDCCCLUTG38_U_CLUTG77_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG38_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG38_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG38_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG38_U_RESERVED_BITWIDTH     24
// GDCCCLUTG39_L Register
#define LCDC_GDCCCLUTG39_L_OFS                   0x00000938
// CLUTG78 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG39_L_CLUTG78_MASK          0xFF
#define LCDC_GDCCCLUTG39_L_CLUTG78_SHIFT         0 
#define LCDC_GDCCCLUTG39_L_CLUTG78_BIT           0xFF
#define LCDC_GDCCCLUTG39_L_CLUTG78_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG39_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG39_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG39_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG39_L_RESERVED_BITWIDTH     24
// GDCCCLUTG39_U Register
#define LCDC_GDCCCLUTG39_U_OFS                   0x0000093C
// CLUTG79 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG39_U_CLUTG79_MASK          0xFF
#define LCDC_GDCCCLUTG39_U_CLUTG79_SHIFT         0 
#define LCDC_GDCCCLUTG39_U_CLUTG79_BIT           0xFF
#define LCDC_GDCCCLUTG39_U_CLUTG79_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG39_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG39_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG39_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG39_U_RESERVED_BITWIDTH     24
// GDCCCLUTG40_L Register
#define LCDC_GDCCCLUTG40_L_OFS                   0x00000940
// CLUTG80 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG40_L_CLUTG80_MASK          0xFF
#define LCDC_GDCCCLUTG40_L_CLUTG80_SHIFT         0 
#define LCDC_GDCCCLUTG40_L_CLUTG80_BIT           0xFF
#define LCDC_GDCCCLUTG40_L_CLUTG80_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG40_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG40_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG40_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG40_L_RESERVED_BITWIDTH     24
// GDCCCLUTG40_U Register
#define LCDC_GDCCCLUTG40_U_OFS                   0x00000944
// CLUTG81 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG40_U_CLUTG81_MASK          0xFF
#define LCDC_GDCCCLUTG40_U_CLUTG81_SHIFT         0 
#define LCDC_GDCCCLUTG40_U_CLUTG81_BIT           0xFF
#define LCDC_GDCCCLUTG40_U_CLUTG81_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG40_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG40_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG40_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG40_U_RESERVED_BITWIDTH     24
// GDCCCLUTG41_L Register
#define LCDC_GDCCCLUTG41_L_OFS                   0x00000948
// CLUTG82 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG41_L_CLUTG82_MASK          0xFF
#define LCDC_GDCCCLUTG41_L_CLUTG82_SHIFT         0 
#define LCDC_GDCCCLUTG41_L_CLUTG82_BIT           0xFF
#define LCDC_GDCCCLUTG41_L_CLUTG82_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG41_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG41_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG41_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG41_L_RESERVED_BITWIDTH     24
// GDCCCLUTG41_U Register
#define LCDC_GDCCCLUTG41_U_OFS                   0x0000094C
// CLUTG83 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG41_U_CLUTG83_MASK          0xFF
#define LCDC_GDCCCLUTG41_U_CLUTG83_SHIFT         0 
#define LCDC_GDCCCLUTG41_U_CLUTG83_BIT           0xFF
#define LCDC_GDCCCLUTG41_U_CLUTG83_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG41_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG41_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG41_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG41_U_RESERVED_BITWIDTH     24
// GDCCCLUTG42_L Register
#define LCDC_GDCCCLUTG42_L_OFS                   0x00000950
// CLUTG84 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG42_L_CLUTG84_MASK          0xFF
#define LCDC_GDCCCLUTG42_L_CLUTG84_SHIFT         0 
#define LCDC_GDCCCLUTG42_L_CLUTG84_BIT           0xFF
#define LCDC_GDCCCLUTG42_L_CLUTG84_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG42_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG42_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG42_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG42_L_RESERVED_BITWIDTH     24
// GDCCCLUTG42_U Register
#define LCDC_GDCCCLUTG42_U_OFS                   0x00000954
// CLUTG85 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG42_U_CLUTG85_MASK          0xFF
#define LCDC_GDCCCLUTG42_U_CLUTG85_SHIFT         0 
#define LCDC_GDCCCLUTG42_U_CLUTG85_BIT           0xFF
#define LCDC_GDCCCLUTG42_U_CLUTG85_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG42_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG42_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG42_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG42_U_RESERVED_BITWIDTH     24
// GDCCCLUTG43_L Register
#define LCDC_GDCCCLUTG43_L_OFS                   0x00000958
// CLUTG86 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG43_L_CLUTG86_MASK          0xFF
#define LCDC_GDCCCLUTG43_L_CLUTG86_SHIFT         0 
#define LCDC_GDCCCLUTG43_L_CLUTG86_BIT           0xFF
#define LCDC_GDCCCLUTG43_L_CLUTG86_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG43_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG43_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG43_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG43_L_RESERVED_BITWIDTH     24
// GDCCCLUTG43_U Register
#define LCDC_GDCCCLUTG43_U_OFS                   0x0000095C
// CLUTG87 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG43_U_CLUTG87_MASK          0xFF
#define LCDC_GDCCCLUTG43_U_CLUTG87_SHIFT         0 
#define LCDC_GDCCCLUTG43_U_CLUTG87_BIT           0xFF
#define LCDC_GDCCCLUTG43_U_CLUTG87_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG43_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG43_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG43_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG43_U_RESERVED_BITWIDTH     24
// GDCCCLUTG44_L Register
#define LCDC_GDCCCLUTG44_L_OFS                   0x00000960
// CLUTG88 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG44_L_CLUTG88_MASK          0xFF
#define LCDC_GDCCCLUTG44_L_CLUTG88_SHIFT         0 
#define LCDC_GDCCCLUTG44_L_CLUTG88_BIT           0xFF
#define LCDC_GDCCCLUTG44_L_CLUTG88_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG44_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG44_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG44_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG44_L_RESERVED_BITWIDTH     24
// GDCCCLUTG44_U Register
#define LCDC_GDCCCLUTG44_U_OFS                   0x00000964
// CLUTG89 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG44_U_CLUTG89_MASK          0xFF
#define LCDC_GDCCCLUTG44_U_CLUTG89_SHIFT         0 
#define LCDC_GDCCCLUTG44_U_CLUTG89_BIT           0xFF
#define LCDC_GDCCCLUTG44_U_CLUTG89_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG44_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG44_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG44_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG44_U_RESERVED_BITWIDTH     24
// GDCCCLUTG45_L Register
#define LCDC_GDCCCLUTG45_L_OFS                   0x00000968
// CLUTG90 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG45_L_CLUTG90_MASK          0xFF
#define LCDC_GDCCCLUTG45_L_CLUTG90_SHIFT         0 
#define LCDC_GDCCCLUTG45_L_CLUTG90_BIT           0xFF
#define LCDC_GDCCCLUTG45_L_CLUTG90_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG45_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG45_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG45_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG45_L_RESERVED_BITWIDTH     24
// GDCCCLUTG45_U Register
#define LCDC_GDCCCLUTG45_U_OFS                   0x0000096C
// CLUTG91 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG45_U_CLUTG91_MASK          0xFF
#define LCDC_GDCCCLUTG45_U_CLUTG91_SHIFT         0 
#define LCDC_GDCCCLUTG45_U_CLUTG91_BIT           0xFF
#define LCDC_GDCCCLUTG45_U_CLUTG91_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG45_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG45_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG45_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG45_U_RESERVED_BITWIDTH     24
// GDCCCLUTG46_L Register
#define LCDC_GDCCCLUTG46_L_OFS                   0x00000970
// CLUTG92 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG46_L_CLUTG92_MASK          0xFF
#define LCDC_GDCCCLUTG46_L_CLUTG92_SHIFT         0 
#define LCDC_GDCCCLUTG46_L_CLUTG92_BIT           0xFF
#define LCDC_GDCCCLUTG46_L_CLUTG92_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG46_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG46_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG46_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG46_L_RESERVED_BITWIDTH     24
// GDCCCLUTG46_U Register
#define LCDC_GDCCCLUTG46_U_OFS                   0x00000974
// CLUTG93 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG46_U_CLUTG93_MASK          0xFF
#define LCDC_GDCCCLUTG46_U_CLUTG93_SHIFT         0 
#define LCDC_GDCCCLUTG46_U_CLUTG93_BIT           0xFF
#define LCDC_GDCCCLUTG46_U_CLUTG93_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG46_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG46_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG46_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG46_U_RESERVED_BITWIDTH     24
// GDCCCLUTG47_L Register
#define LCDC_GDCCCLUTG47_L_OFS                   0x00000978
// CLUTG94 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG47_L_CLUTG94_MASK          0xFF
#define LCDC_GDCCCLUTG47_L_CLUTG94_SHIFT         0 
#define LCDC_GDCCCLUTG47_L_CLUTG94_BIT           0xFF
#define LCDC_GDCCCLUTG47_L_CLUTG94_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG47_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG47_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG47_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG47_L_RESERVED_BITWIDTH     24
// GDCCCLUTG47_U Register
#define LCDC_GDCCCLUTG47_U_OFS                   0x0000097C
// CLUTG95 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG47_U_CLUTG95_MASK          0xFF
#define LCDC_GDCCCLUTG47_U_CLUTG95_SHIFT         0 
#define LCDC_GDCCCLUTG47_U_CLUTG95_BIT           0xFF
#define LCDC_GDCCCLUTG47_U_CLUTG95_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG47_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG47_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG47_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG47_U_RESERVED_BITWIDTH     24
// GDCCCLUTG48_L Register
#define LCDC_GDCCCLUTG48_L_OFS                   0x00000980
// CLUTG96 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG48_L_CLUTG96_MASK          0xFF
#define LCDC_GDCCCLUTG48_L_CLUTG96_SHIFT         0 
#define LCDC_GDCCCLUTG48_L_CLUTG96_BIT           0xFF
#define LCDC_GDCCCLUTG48_L_CLUTG96_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG48_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG48_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG48_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG48_L_RESERVED_BITWIDTH     24
// GDCCCLUTG48_U Register
#define LCDC_GDCCCLUTG48_U_OFS                   0x00000984
// CLUTG97 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG48_U_CLUTG97_MASK          0xFF
#define LCDC_GDCCCLUTG48_U_CLUTG97_SHIFT         0 
#define LCDC_GDCCCLUTG48_U_CLUTG97_BIT           0xFF
#define LCDC_GDCCCLUTG48_U_CLUTG97_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG48_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG48_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG48_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG48_U_RESERVED_BITWIDTH     24
// GDCCCLUTG49_L Register
#define LCDC_GDCCCLUTG49_L_OFS                   0x00000988
// CLUTG98 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG49_L_CLUTG98_MASK          0xFF
#define LCDC_GDCCCLUTG49_L_CLUTG98_SHIFT         0 
#define LCDC_GDCCCLUTG49_L_CLUTG98_BIT           0xFF
#define LCDC_GDCCCLUTG49_L_CLUTG98_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG49_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG49_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG49_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG49_L_RESERVED_BITWIDTH     24
// GDCCCLUTG49_U Register
#define LCDC_GDCCCLUTG49_U_OFS                   0x0000098C
// CLUTG99 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG49_U_CLUTG99_MASK          0xFF
#define LCDC_GDCCCLUTG49_U_CLUTG99_SHIFT         0 
#define LCDC_GDCCCLUTG49_U_CLUTG99_BIT           0xFF
#define LCDC_GDCCCLUTG49_U_CLUTG99_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG49_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG49_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG49_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG49_U_RESERVED_BITWIDTH     24
// GDCCCLUTG50_L Register
#define LCDC_GDCCCLUTG50_L_OFS                   0x00000990
// CLUTG100 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG50_L_CLUTG100_MASK         0xFF
#define LCDC_GDCCCLUTG50_L_CLUTG100_SHIFT        0 
#define LCDC_GDCCCLUTG50_L_CLUTG100_BIT          0xFF
#define LCDC_GDCCCLUTG50_L_CLUTG100_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG50_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG50_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG50_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG50_L_RESERVED_BITWIDTH     24
// GDCCCLUTG50_U Register
#define LCDC_GDCCCLUTG50_U_OFS                   0x00000994
// CLUTG101 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG50_U_CLUTG101_MASK         0xFF
#define LCDC_GDCCCLUTG50_U_CLUTG101_SHIFT        0 
#define LCDC_GDCCCLUTG50_U_CLUTG101_BIT          0xFF
#define LCDC_GDCCCLUTG50_U_CLUTG101_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG50_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG50_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG50_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG50_U_RESERVED_BITWIDTH     24
// GDCCCLUTG51_L Register
#define LCDC_GDCCCLUTG51_L_OFS                   0x00000998
// CLUTG102 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG51_L_CLUTG102_MASK         0xFF
#define LCDC_GDCCCLUTG51_L_CLUTG102_SHIFT        0 
#define LCDC_GDCCCLUTG51_L_CLUTG102_BIT          0xFF
#define LCDC_GDCCCLUTG51_L_CLUTG102_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG51_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG51_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG51_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG51_L_RESERVED_BITWIDTH     24
// GDCCCLUTG51_U Register
#define LCDC_GDCCCLUTG51_U_OFS                   0x0000099C
// CLUTG103 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG51_U_CLUTG103_MASK         0xFF
#define LCDC_GDCCCLUTG51_U_CLUTG103_SHIFT        0 
#define LCDC_GDCCCLUTG51_U_CLUTG103_BIT          0xFF
#define LCDC_GDCCCLUTG51_U_CLUTG103_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG51_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG51_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG51_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG51_U_RESERVED_BITWIDTH     24
// GDCCCLUTG52_L Register
#define LCDC_GDCCCLUTG52_L_OFS                   0x000009A0
// CLUTG104 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG52_L_CLUTG104_MASK         0xFF
#define LCDC_GDCCCLUTG52_L_CLUTG104_SHIFT        0 
#define LCDC_GDCCCLUTG52_L_CLUTG104_BIT          0xFF
#define LCDC_GDCCCLUTG52_L_CLUTG104_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG52_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG52_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG52_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG52_L_RESERVED_BITWIDTH     24
// GDCCCLUTG52_U Register
#define LCDC_GDCCCLUTG52_U_OFS                   0x000009A4
// CLUTG105 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG52_U_CLUTG105_MASK         0xFF
#define LCDC_GDCCCLUTG52_U_CLUTG105_SHIFT        0 
#define LCDC_GDCCCLUTG52_U_CLUTG105_BIT          0xFF
#define LCDC_GDCCCLUTG52_U_CLUTG105_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG52_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG52_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG52_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG52_U_RESERVED_BITWIDTH     24
// GDCCCLUTG53_L Register
#define LCDC_GDCCCLUTG53_L_OFS                   0x000009A8
// CLUTG106 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG53_L_CLUTG106_MASK         0xFF
#define LCDC_GDCCCLUTG53_L_CLUTG106_SHIFT        0 
#define LCDC_GDCCCLUTG53_L_CLUTG106_BIT          0xFF
#define LCDC_GDCCCLUTG53_L_CLUTG106_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG53_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG53_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG53_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG53_L_RESERVED_BITWIDTH     24
// GDCCCLUTG53_U Register
#define LCDC_GDCCCLUTG53_U_OFS                   0x000009AC
// CLUTG107 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG53_U_CLUTG107_MASK         0xFF
#define LCDC_GDCCCLUTG53_U_CLUTG107_SHIFT        0 
#define LCDC_GDCCCLUTG53_U_CLUTG107_BIT          0xFF
#define LCDC_GDCCCLUTG53_U_CLUTG107_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG53_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG53_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG53_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG53_U_RESERVED_BITWIDTH     24
// GDCCCLUTG54_L Register
#define LCDC_GDCCCLUTG54_L_OFS                   0x000009B0
// CLUTG108 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG54_L_CLUTG108_MASK         0xFF
#define LCDC_GDCCCLUTG54_L_CLUTG108_SHIFT        0 
#define LCDC_GDCCCLUTG54_L_CLUTG108_BIT          0xFF
#define LCDC_GDCCCLUTG54_L_CLUTG108_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG54_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG54_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG54_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG54_L_RESERVED_BITWIDTH     24
// GDCCCLUTG54_U Register
#define LCDC_GDCCCLUTG54_U_OFS                   0x000009B4
// CLUTG109 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG54_U_CLUTG109_MASK         0xFF
#define LCDC_GDCCCLUTG54_U_CLUTG109_SHIFT        0 
#define LCDC_GDCCCLUTG54_U_CLUTG109_BIT          0xFF
#define LCDC_GDCCCLUTG54_U_CLUTG109_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG54_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG54_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG54_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG54_U_RESERVED_BITWIDTH     24
// GDCCCLUTG55_L Register
#define LCDC_GDCCCLUTG55_L_OFS                   0x000009B8
// CLUTG110 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG55_L_CLUTG110_MASK         0xFF
#define LCDC_GDCCCLUTG55_L_CLUTG110_SHIFT        0 
#define LCDC_GDCCCLUTG55_L_CLUTG110_BIT          0xFF
#define LCDC_GDCCCLUTG55_L_CLUTG110_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG55_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG55_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG55_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG55_L_RESERVED_BITWIDTH     24
// GDCCCLUTG55_U Register
#define LCDC_GDCCCLUTG55_U_OFS                   0x000009BC
// CLUTG111 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG55_U_CLUTG111_MASK         0xFF
#define LCDC_GDCCCLUTG55_U_CLUTG111_SHIFT        0 
#define LCDC_GDCCCLUTG55_U_CLUTG111_BIT          0xFF
#define LCDC_GDCCCLUTG55_U_CLUTG111_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG55_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG55_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG55_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG55_U_RESERVED_BITWIDTH     24
// GDCCCLUTG56_L Register
#define LCDC_GDCCCLUTG56_L_OFS                   0x000009C0
// CLUTG112 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG56_L_CLUTG112_MASK         0xFF
#define LCDC_GDCCCLUTG56_L_CLUTG112_SHIFT        0 
#define LCDC_GDCCCLUTG56_L_CLUTG112_BIT          0xFF
#define LCDC_GDCCCLUTG56_L_CLUTG112_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG56_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG56_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG56_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG56_L_RESERVED_BITWIDTH     24
// GDCCCLUTG56_U Register
#define LCDC_GDCCCLUTG56_U_OFS                   0x000009C4
// CLUTG113 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG56_U_CLUTG113_MASK         0xFF
#define LCDC_GDCCCLUTG56_U_CLUTG113_SHIFT        0 
#define LCDC_GDCCCLUTG56_U_CLUTG113_BIT          0xFF
#define LCDC_GDCCCLUTG56_U_CLUTG113_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG56_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG56_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG56_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG56_U_RESERVED_BITWIDTH     24
// GDCCCLUTG57_L Register
#define LCDC_GDCCCLUTG57_L_OFS                   0x000009C8
// CLUTG114 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG57_L_CLUTG114_MASK         0xFF
#define LCDC_GDCCCLUTG57_L_CLUTG114_SHIFT        0 
#define LCDC_GDCCCLUTG57_L_CLUTG114_BIT          0xFF
#define LCDC_GDCCCLUTG57_L_CLUTG114_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG57_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG57_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG57_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG57_L_RESERVED_BITWIDTH     24
// GDCCCLUTG57_U Register
#define LCDC_GDCCCLUTG57_U_OFS                   0x000009CC
// CLUTG115 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG57_U_CLUTG115_MASK         0xFF
#define LCDC_GDCCCLUTG57_U_CLUTG115_SHIFT        0 
#define LCDC_GDCCCLUTG57_U_CLUTG115_BIT          0xFF
#define LCDC_GDCCCLUTG57_U_CLUTG115_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG57_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG57_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG57_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG57_U_RESERVED_BITWIDTH     24
// GDCCCLUTG58_L Register
#define LCDC_GDCCCLUTG58_L_OFS                   0x000009D0
// CLUTG116 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG58_L_CLUTG116_MASK         0xFF
#define LCDC_GDCCCLUTG58_L_CLUTG116_SHIFT        0 
#define LCDC_GDCCCLUTG58_L_CLUTG116_BIT          0xFF
#define LCDC_GDCCCLUTG58_L_CLUTG116_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG58_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG58_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG58_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG58_L_RESERVED_BITWIDTH     24
// GDCCCLUTG58_U Register
#define LCDC_GDCCCLUTG58_U_OFS                   0x000009D4
// CLUTG117 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG58_U_CLUTG117_MASK         0xFF
#define LCDC_GDCCCLUTG58_U_CLUTG117_SHIFT        0 
#define LCDC_GDCCCLUTG58_U_CLUTG117_BIT          0xFF
#define LCDC_GDCCCLUTG58_U_CLUTG117_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG58_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG58_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG58_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG58_U_RESERVED_BITWIDTH     24
// GDCCCLUTG59_L Register
#define LCDC_GDCCCLUTG59_L_OFS                   0x000009D8
// CLUTG118 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG59_L_CLUTG118_MASK         0xFF
#define LCDC_GDCCCLUTG59_L_CLUTG118_SHIFT        0 
#define LCDC_GDCCCLUTG59_L_CLUTG118_BIT          0xFF
#define LCDC_GDCCCLUTG59_L_CLUTG118_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG59_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG59_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG59_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG59_L_RESERVED_BITWIDTH     24
// GDCCCLUTG59_U Register
#define LCDC_GDCCCLUTG59_U_OFS                   0x000009DC
// CLUTG119 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG59_U_CLUTG119_MASK         0xFF
#define LCDC_GDCCCLUTG59_U_CLUTG119_SHIFT        0 
#define LCDC_GDCCCLUTG59_U_CLUTG119_BIT          0xFF
#define LCDC_GDCCCLUTG59_U_CLUTG119_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG59_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG59_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG59_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG59_U_RESERVED_BITWIDTH     24
// GDCCCLUTG60_L Register
#define LCDC_GDCCCLUTG60_L_OFS                   0x000009E0
// CLUTG120 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG60_L_CLUTG120_MASK         0xFF
#define LCDC_GDCCCLUTG60_L_CLUTG120_SHIFT        0 
#define LCDC_GDCCCLUTG60_L_CLUTG120_BIT          0xFF
#define LCDC_GDCCCLUTG60_L_CLUTG120_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG60_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG60_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG60_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG60_L_RESERVED_BITWIDTH     24
// GDCCCLUTG60_U Register
#define LCDC_GDCCCLUTG60_U_OFS                   0x000009E4
// CLUTG121 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG60_U_CLUTG121_MASK         0xFF
#define LCDC_GDCCCLUTG60_U_CLUTG121_SHIFT        0 
#define LCDC_GDCCCLUTG60_U_CLUTG121_BIT          0xFF
#define LCDC_GDCCCLUTG60_U_CLUTG121_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG60_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG60_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG60_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG60_U_RESERVED_BITWIDTH     24
// GDCCCLUTG61_L Register
#define LCDC_GDCCCLUTG61_L_OFS                   0x000009E8
// CLUTG122 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG61_L_CLUTG122_MASK         0xFF
#define LCDC_GDCCCLUTG61_L_CLUTG122_SHIFT        0 
#define LCDC_GDCCCLUTG61_L_CLUTG122_BIT          0xFF
#define LCDC_GDCCCLUTG61_L_CLUTG122_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG61_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG61_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG61_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG61_L_RESERVED_BITWIDTH     24
// GDCCCLUTG61_U Register
#define LCDC_GDCCCLUTG61_U_OFS                   0x000009EC
// CLUTG123 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG61_U_CLUTG123_MASK         0xFF
#define LCDC_GDCCCLUTG61_U_CLUTG123_SHIFT        0 
#define LCDC_GDCCCLUTG61_U_CLUTG123_BIT          0xFF
#define LCDC_GDCCCLUTG61_U_CLUTG123_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG61_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG61_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG61_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG61_U_RESERVED_BITWIDTH     24
// GDCCCLUTG62_L Register
#define LCDC_GDCCCLUTG62_L_OFS                   0x000009F0
// CLUTG124 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG62_L_CLUTG124_MASK         0xFF
#define LCDC_GDCCCLUTG62_L_CLUTG124_SHIFT        0 
#define LCDC_GDCCCLUTG62_L_CLUTG124_BIT          0xFF
#define LCDC_GDCCCLUTG62_L_CLUTG124_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG62_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG62_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG62_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG62_L_RESERVED_BITWIDTH     24
// GDCCCLUTG62_U Register
#define LCDC_GDCCCLUTG62_U_OFS                   0x000009F4
// CLUTG125 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG62_U_CLUTG125_MASK         0xFF
#define LCDC_GDCCCLUTG62_U_CLUTG125_SHIFT        0 
#define LCDC_GDCCCLUTG62_U_CLUTG125_BIT          0xFF
#define LCDC_GDCCCLUTG62_U_CLUTG125_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG62_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG62_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG62_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG62_U_RESERVED_BITWIDTH     24
// GDCCCLUTG63_L Register
#define LCDC_GDCCCLUTG63_L_OFS                   0x000009F8
// CLUTG126 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG63_L_CLUTG126_MASK         0xFF
#define LCDC_GDCCCLUTG63_L_CLUTG126_SHIFT        0 
#define LCDC_GDCCCLUTG63_L_CLUTG126_BIT          0xFF
#define LCDC_GDCCCLUTG63_L_CLUTG126_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG63_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG63_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG63_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG63_L_RESERVED_BITWIDTH     24
// GDCCCLUTG63_U Register
#define LCDC_GDCCCLUTG63_U_OFS                   0x000009FC
// CLUTG127 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG63_U_CLUTG127_MASK         0xFF
#define LCDC_GDCCCLUTG63_U_CLUTG127_SHIFT        0 
#define LCDC_GDCCCLUTG63_U_CLUTG127_BIT          0xFF
#define LCDC_GDCCCLUTG63_U_CLUTG127_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG63_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG63_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG63_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG63_U_RESERVED_BITWIDTH     24
// GDCCCLUTG64_L Register
#define LCDC_GDCCCLUTG64_L_OFS                   0x00000A00
// CLUTG128 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG64_L_CLUTG128_MASK         0xFF
#define LCDC_GDCCCLUTG64_L_CLUTG128_SHIFT        0 
#define LCDC_GDCCCLUTG64_L_CLUTG128_BIT          0xFF
#define LCDC_GDCCCLUTG64_L_CLUTG128_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG64_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG64_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG64_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG64_L_RESERVED_BITWIDTH     24
// GDCCCLUTG64_U Register
#define LCDC_GDCCCLUTG64_U_OFS                   0x00000A04
// CLUTG129 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG64_U_CLUTG129_MASK         0xFF
#define LCDC_GDCCCLUTG64_U_CLUTG129_SHIFT        0 
#define LCDC_GDCCCLUTG64_U_CLUTG129_BIT          0xFF
#define LCDC_GDCCCLUTG64_U_CLUTG129_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG64_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG64_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG64_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG64_U_RESERVED_BITWIDTH     24
// GDCCCLUTG65_L Register
#define LCDC_GDCCCLUTG65_L_OFS                   0x00000A08
// CLUTG130 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG65_L_CLUTG130_MASK         0xFF
#define LCDC_GDCCCLUTG65_L_CLUTG130_SHIFT        0 
#define LCDC_GDCCCLUTG65_L_CLUTG130_BIT          0xFF
#define LCDC_GDCCCLUTG65_L_CLUTG130_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG65_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG65_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG65_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG65_L_RESERVED_BITWIDTH     24
// GDCCCLUTG65_U Register
#define LCDC_GDCCCLUTG65_U_OFS                   0x00000A0C
// CLUTG131 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG65_U_CLUTG131_MASK         0xFF
#define LCDC_GDCCCLUTG65_U_CLUTG131_SHIFT        0 
#define LCDC_GDCCCLUTG65_U_CLUTG131_BIT          0xFF
#define LCDC_GDCCCLUTG65_U_CLUTG131_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG65_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG65_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG65_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG65_U_RESERVED_BITWIDTH     24
// GDCCCLUTG66_L Register
#define LCDC_GDCCCLUTG66_L_OFS                   0x00000A10
// CLUTG132 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG66_L_CLUTG132_MASK         0xFF
#define LCDC_GDCCCLUTG66_L_CLUTG132_SHIFT        0 
#define LCDC_GDCCCLUTG66_L_CLUTG132_BIT          0xFF
#define LCDC_GDCCCLUTG66_L_CLUTG132_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG66_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG66_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG66_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG66_L_RESERVED_BITWIDTH     24
// GDCCCLUTG66_U Register
#define LCDC_GDCCCLUTG66_U_OFS                   0x00000A14
// CLUTG133 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG66_U_CLUTG133_MASK         0xFF
#define LCDC_GDCCCLUTG66_U_CLUTG133_SHIFT        0 
#define LCDC_GDCCCLUTG66_U_CLUTG133_BIT          0xFF
#define LCDC_GDCCCLUTG66_U_CLUTG133_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG66_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG66_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG66_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG66_U_RESERVED_BITWIDTH     24
// GDCCCLUTG67_L Register
#define LCDC_GDCCCLUTG67_L_OFS                   0x00000A18
// CLUTG134 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG67_L_CLUTG134_MASK         0xFF
#define LCDC_GDCCCLUTG67_L_CLUTG134_SHIFT        0 
#define LCDC_GDCCCLUTG67_L_CLUTG134_BIT          0xFF
#define LCDC_GDCCCLUTG67_L_CLUTG134_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG67_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG67_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG67_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG67_L_RESERVED_BITWIDTH     24
// GDCCCLUTG67_U Register
#define LCDC_GDCCCLUTG67_U_OFS                   0x00000A1C
// CLUTG135 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG67_U_CLUTG135_MASK         0xFF
#define LCDC_GDCCCLUTG67_U_CLUTG135_SHIFT        0 
#define LCDC_GDCCCLUTG67_U_CLUTG135_BIT          0xFF
#define LCDC_GDCCCLUTG67_U_CLUTG135_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG67_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG67_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG67_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG67_U_RESERVED_BITWIDTH     24
// GDCCCLUTG68_L Register
#define LCDC_GDCCCLUTG68_L_OFS                   0x00000A20
// CLUTG136 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG68_L_CLUTG136_MASK         0xFF
#define LCDC_GDCCCLUTG68_L_CLUTG136_SHIFT        0 
#define LCDC_GDCCCLUTG68_L_CLUTG136_BIT          0xFF
#define LCDC_GDCCCLUTG68_L_CLUTG136_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG68_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG68_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG68_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG68_L_RESERVED_BITWIDTH     24
// GDCCCLUTG68_U Register
#define LCDC_GDCCCLUTG68_U_OFS                   0x00000A24
// CLUTG137 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG68_U_CLUTG137_MASK         0xFF
#define LCDC_GDCCCLUTG68_U_CLUTG137_SHIFT        0 
#define LCDC_GDCCCLUTG68_U_CLUTG137_BIT          0xFF
#define LCDC_GDCCCLUTG68_U_CLUTG137_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG68_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG68_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG68_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG68_U_RESERVED_BITWIDTH     24
// GDCCCLUTG69_L Register
#define LCDC_GDCCCLUTG69_L_OFS                   0x00000A28
// CLUTG138 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG69_L_CLUTG138_MASK         0xFF
#define LCDC_GDCCCLUTG69_L_CLUTG138_SHIFT        0 
#define LCDC_GDCCCLUTG69_L_CLUTG138_BIT          0xFF
#define LCDC_GDCCCLUTG69_L_CLUTG138_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG69_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG69_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG69_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG69_L_RESERVED_BITWIDTH     24
// GDCCCLUTG69_U Register
#define LCDC_GDCCCLUTG69_U_OFS                   0x00000A2C
// CLUTG139 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG69_U_CLUTG139_MASK         0xFF
#define LCDC_GDCCCLUTG69_U_CLUTG139_SHIFT        0 
#define LCDC_GDCCCLUTG69_U_CLUTG139_BIT          0xFF
#define LCDC_GDCCCLUTG69_U_CLUTG139_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG69_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG69_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG69_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG69_U_RESERVED_BITWIDTH     24
// GDCCCLUTG70_L Register
#define LCDC_GDCCCLUTG70_L_OFS                   0x00000A30
// CLUTG140 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG70_L_CLUTG140_MASK         0xFF
#define LCDC_GDCCCLUTG70_L_CLUTG140_SHIFT        0 
#define LCDC_GDCCCLUTG70_L_CLUTG140_BIT          0xFF
#define LCDC_GDCCCLUTG70_L_CLUTG140_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG70_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG70_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG70_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG70_L_RESERVED_BITWIDTH     24
// GDCCCLUTG70_U Register
#define LCDC_GDCCCLUTG70_U_OFS                   0x00000A34
// CLUTG141 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG70_U_CLUTG141_MASK         0xFF
#define LCDC_GDCCCLUTG70_U_CLUTG141_SHIFT        0 
#define LCDC_GDCCCLUTG70_U_CLUTG141_BIT          0xFF
#define LCDC_GDCCCLUTG70_U_CLUTG141_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG70_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG70_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG70_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG70_U_RESERVED_BITWIDTH     24
// GDCCCLUTG71_L Register
#define LCDC_GDCCCLUTG71_L_OFS                   0x00000A38
// CLUTG142 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG71_L_CLUTG142_MASK         0xFF
#define LCDC_GDCCCLUTG71_L_CLUTG142_SHIFT        0 
#define LCDC_GDCCCLUTG71_L_CLUTG142_BIT          0xFF
#define LCDC_GDCCCLUTG71_L_CLUTG142_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG71_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG71_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG71_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG71_L_RESERVED_BITWIDTH     24
// GDCCCLUTG71_U Register
#define LCDC_GDCCCLUTG71_U_OFS                   0x00000A3C
// CLUTG143 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG71_U_CLUTG143_MASK         0xFF
#define LCDC_GDCCCLUTG71_U_CLUTG143_SHIFT        0 
#define LCDC_GDCCCLUTG71_U_CLUTG143_BIT          0xFF
#define LCDC_GDCCCLUTG71_U_CLUTG143_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG71_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG71_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG71_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG71_U_RESERVED_BITWIDTH     24
// GDCCCLUTG72_L Register
#define LCDC_GDCCCLUTG72_L_OFS                   0x00000A40
// CLUTG144 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG72_L_CLUTG144_MASK         0xFF
#define LCDC_GDCCCLUTG72_L_CLUTG144_SHIFT        0 
#define LCDC_GDCCCLUTG72_L_CLUTG144_BIT          0xFF
#define LCDC_GDCCCLUTG72_L_CLUTG144_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG72_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG72_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG72_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG72_L_RESERVED_BITWIDTH     24
// GDCCCLUTG72_U Register
#define LCDC_GDCCCLUTG72_U_OFS                   0x00000A44
// CLUTG145 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG72_U_CLUTG145_MASK         0xFF
#define LCDC_GDCCCLUTG72_U_CLUTG145_SHIFT        0 
#define LCDC_GDCCCLUTG72_U_CLUTG145_BIT          0xFF
#define LCDC_GDCCCLUTG72_U_CLUTG145_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG72_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG72_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG72_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG72_U_RESERVED_BITWIDTH     24
// GDCCCLUTG73_L Register
#define LCDC_GDCCCLUTG73_L_OFS                   0x00000A48
// CLUTG146 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG73_L_CLUTG146_MASK         0xFF
#define LCDC_GDCCCLUTG73_L_CLUTG146_SHIFT        0 
#define LCDC_GDCCCLUTG73_L_CLUTG146_BIT          0xFF
#define LCDC_GDCCCLUTG73_L_CLUTG146_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG73_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG73_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG73_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG73_L_RESERVED_BITWIDTH     24
// GDCCCLUTG73_U Register
#define LCDC_GDCCCLUTG73_U_OFS                   0x00000A4C
// CLUTG147 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG73_U_CLUTG147_MASK         0xFF
#define LCDC_GDCCCLUTG73_U_CLUTG147_SHIFT        0 
#define LCDC_GDCCCLUTG73_U_CLUTG147_BIT          0xFF
#define LCDC_GDCCCLUTG73_U_CLUTG147_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG73_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG73_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG73_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG73_U_RESERVED_BITWIDTH     24
// GDCCCLUTG74_L Register
#define LCDC_GDCCCLUTG74_L_OFS                   0x00000A50
// CLUTG148 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG74_L_CLUTG148_MASK         0xFF
#define LCDC_GDCCCLUTG74_L_CLUTG148_SHIFT        0 
#define LCDC_GDCCCLUTG74_L_CLUTG148_BIT          0xFF
#define LCDC_GDCCCLUTG74_L_CLUTG148_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG74_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG74_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG74_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG74_L_RESERVED_BITWIDTH     24
// GDCCCLUTG74_U Register
#define LCDC_GDCCCLUTG74_U_OFS                   0x00000A54
// CLUTG149 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG74_U_CLUTG149_MASK         0xFF
#define LCDC_GDCCCLUTG74_U_CLUTG149_SHIFT        0 
#define LCDC_GDCCCLUTG74_U_CLUTG149_BIT          0xFF
#define LCDC_GDCCCLUTG74_U_CLUTG149_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG74_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG74_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG74_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG74_U_RESERVED_BITWIDTH     24
// GDCCCLUTG75_L Register
#define LCDC_GDCCCLUTG75_L_OFS                   0x00000A58
// CLUTG150 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG75_L_CLUTG150_MASK         0xFF
#define LCDC_GDCCCLUTG75_L_CLUTG150_SHIFT        0 
#define LCDC_GDCCCLUTG75_L_CLUTG150_BIT          0xFF
#define LCDC_GDCCCLUTG75_L_CLUTG150_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG75_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG75_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG75_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG75_L_RESERVED_BITWIDTH     24
// GDCCCLUTG75_U Register
#define LCDC_GDCCCLUTG75_U_OFS                   0x00000A5C
// CLUTG151 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG75_U_CLUTG151_MASK         0xFF
#define LCDC_GDCCCLUTG75_U_CLUTG151_SHIFT        0 
#define LCDC_GDCCCLUTG75_U_CLUTG151_BIT          0xFF
#define LCDC_GDCCCLUTG75_U_CLUTG151_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG75_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG75_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG75_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG75_U_RESERVED_BITWIDTH     24
// GDCCCLUTG76_L Register
#define LCDC_GDCCCLUTG76_L_OFS                   0x00000A60
// CLUTG152 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG76_L_CLUTG152_MASK         0xFF
#define LCDC_GDCCCLUTG76_L_CLUTG152_SHIFT        0 
#define LCDC_GDCCCLUTG76_L_CLUTG152_BIT          0xFF
#define LCDC_GDCCCLUTG76_L_CLUTG152_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG76_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG76_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG76_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG76_L_RESERVED_BITWIDTH     24
// GDCCCLUTG76_U Register
#define LCDC_GDCCCLUTG76_U_OFS                   0x00000A64
// CLUTG153 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG76_U_CLUTG153_MASK         0xFF
#define LCDC_GDCCCLUTG76_U_CLUTG153_SHIFT        0 
#define LCDC_GDCCCLUTG76_U_CLUTG153_BIT          0xFF
#define LCDC_GDCCCLUTG76_U_CLUTG153_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG76_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG76_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG76_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG76_U_RESERVED_BITWIDTH     24
// GDCCCLUTG77_L Register
#define LCDC_GDCCCLUTG77_L_OFS                   0x00000A68
// CLUTG154 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG77_L_CLUTG154_MASK         0xFF
#define LCDC_GDCCCLUTG77_L_CLUTG154_SHIFT        0 
#define LCDC_GDCCCLUTG77_L_CLUTG154_BIT          0xFF
#define LCDC_GDCCCLUTG77_L_CLUTG154_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG77_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG77_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG77_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG77_L_RESERVED_BITWIDTH     24
// GDCCCLUTG77_U Register
#define LCDC_GDCCCLUTG77_U_OFS                   0x00000A6C
// CLUTG155 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG77_U_CLUTG155_MASK         0xFF
#define LCDC_GDCCCLUTG77_U_CLUTG155_SHIFT        0 
#define LCDC_GDCCCLUTG77_U_CLUTG155_BIT          0xFF
#define LCDC_GDCCCLUTG77_U_CLUTG155_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG77_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG77_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG77_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG77_U_RESERVED_BITWIDTH     24
// GDCCCLUTG78_L Register
#define LCDC_GDCCCLUTG78_L_OFS                   0x00000A70
// CLUTG156 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG78_L_CLUTG156_MASK         0xFF
#define LCDC_GDCCCLUTG78_L_CLUTG156_SHIFT        0 
#define LCDC_GDCCCLUTG78_L_CLUTG156_BIT          0xFF
#define LCDC_GDCCCLUTG78_L_CLUTG156_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG78_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG78_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG78_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG78_L_RESERVED_BITWIDTH     24
// GDCCCLUTG78_U Register
#define LCDC_GDCCCLUTG78_U_OFS                   0x00000A74
// CLUTG157 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG78_U_CLUTG157_MASK         0xFF
#define LCDC_GDCCCLUTG78_U_CLUTG157_SHIFT        0 
#define LCDC_GDCCCLUTG78_U_CLUTG157_BIT          0xFF
#define LCDC_GDCCCLUTG78_U_CLUTG157_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG78_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG78_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG78_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG78_U_RESERVED_BITWIDTH     24
// GDCCCLUTG79_L Register
#define LCDC_GDCCCLUTG79_L_OFS                   0x00000A78
// CLUTG158 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG79_L_CLUTG158_MASK         0xFF
#define LCDC_GDCCCLUTG79_L_CLUTG158_SHIFT        0 
#define LCDC_GDCCCLUTG79_L_CLUTG158_BIT          0xFF
#define LCDC_GDCCCLUTG79_L_CLUTG158_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG79_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG79_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG79_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG79_L_RESERVED_BITWIDTH     24
// GDCCCLUTG79_U Register
#define LCDC_GDCCCLUTG79_U_OFS                   0x00000A7C
// CLUTG159 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG79_U_CLUTG159_MASK         0xFF
#define LCDC_GDCCCLUTG79_U_CLUTG159_SHIFT        0 
#define LCDC_GDCCCLUTG79_U_CLUTG159_BIT          0xFF
#define LCDC_GDCCCLUTG79_U_CLUTG159_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG79_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG79_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG79_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG79_U_RESERVED_BITWIDTH     24
// GDCCCLUTG80_L Register
#define LCDC_GDCCCLUTG80_L_OFS                   0x00000A80
// CLUTG160 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG80_L_CLUTG160_MASK         0xFF
#define LCDC_GDCCCLUTG80_L_CLUTG160_SHIFT        0 
#define LCDC_GDCCCLUTG80_L_CLUTG160_BIT          0xFF
#define LCDC_GDCCCLUTG80_L_CLUTG160_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG80_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG80_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG80_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG80_L_RESERVED_BITWIDTH     24
// GDCCCLUTG80_U Register
#define LCDC_GDCCCLUTG80_U_OFS                   0x00000A84
// CLUTG161 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG80_U_CLUTG161_MASK         0xFF
#define LCDC_GDCCCLUTG80_U_CLUTG161_SHIFT        0 
#define LCDC_GDCCCLUTG80_U_CLUTG161_BIT          0xFF
#define LCDC_GDCCCLUTG80_U_CLUTG161_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG80_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG80_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG80_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG80_U_RESERVED_BITWIDTH     24
// GDCCCLUTG81_L Register
#define LCDC_GDCCCLUTG81_L_OFS                   0x00000A88
// CLUTG162 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG81_L_CLUTG162_MASK         0xFF
#define LCDC_GDCCCLUTG81_L_CLUTG162_SHIFT        0 
#define LCDC_GDCCCLUTG81_L_CLUTG162_BIT          0xFF
#define LCDC_GDCCCLUTG81_L_CLUTG162_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG81_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG81_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG81_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG81_L_RESERVED_BITWIDTH     24
// GDCCCLUTG81_U Register
#define LCDC_GDCCCLUTG81_U_OFS                   0x00000A8C
// CLUTG163 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG81_U_CLUTG163_MASK         0xFF
#define LCDC_GDCCCLUTG81_U_CLUTG163_SHIFT        0 
#define LCDC_GDCCCLUTG81_U_CLUTG163_BIT          0xFF
#define LCDC_GDCCCLUTG81_U_CLUTG163_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG81_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG81_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG81_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG81_U_RESERVED_BITWIDTH     24
// GDCCCLUTG82_L Register
#define LCDC_GDCCCLUTG82_L_OFS                   0x00000A90
// CLUTG164 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG82_L_CLUTG164_MASK         0xFF
#define LCDC_GDCCCLUTG82_L_CLUTG164_SHIFT        0 
#define LCDC_GDCCCLUTG82_L_CLUTG164_BIT          0xFF
#define LCDC_GDCCCLUTG82_L_CLUTG164_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG82_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG82_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG82_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG82_L_RESERVED_BITWIDTH     24
// GDCCCLUTG82_U Register
#define LCDC_GDCCCLUTG82_U_OFS                   0x00000A94
// CLUTG165 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG82_U_CLUTG165_MASK         0xFF
#define LCDC_GDCCCLUTG82_U_CLUTG165_SHIFT        0 
#define LCDC_GDCCCLUTG82_U_CLUTG165_BIT          0xFF
#define LCDC_GDCCCLUTG82_U_CLUTG165_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG82_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG82_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG82_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG82_U_RESERVED_BITWIDTH     24
// GDCCCLUTG83_L Register
#define LCDC_GDCCCLUTG83_L_OFS                   0x00000A98
// CLUTG166 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG83_L_CLUTG166_MASK         0xFF
#define LCDC_GDCCCLUTG83_L_CLUTG166_SHIFT        0 
#define LCDC_GDCCCLUTG83_L_CLUTG166_BIT          0xFF
#define LCDC_GDCCCLUTG83_L_CLUTG166_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG83_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG83_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG83_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG83_L_RESERVED_BITWIDTH     24
// GDCCCLUTG83_U Register
#define LCDC_GDCCCLUTG83_U_OFS                   0x00000A9C
// CLUTG167 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG83_U_CLUTG167_MASK         0xFF
#define LCDC_GDCCCLUTG83_U_CLUTG167_SHIFT        0 
#define LCDC_GDCCCLUTG83_U_CLUTG167_BIT          0xFF
#define LCDC_GDCCCLUTG83_U_CLUTG167_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG83_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG83_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG83_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG83_U_RESERVED_BITWIDTH     24
// GDCCCLUTG84_L Register
#define LCDC_GDCCCLUTG84_L_OFS                   0x00000AA0
// CLUTG168 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG84_L_CLUTG168_MASK         0xFF
#define LCDC_GDCCCLUTG84_L_CLUTG168_SHIFT        0 
#define LCDC_GDCCCLUTG84_L_CLUTG168_BIT          0xFF
#define LCDC_GDCCCLUTG84_L_CLUTG168_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG84_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG84_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG84_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG84_L_RESERVED_BITWIDTH     24
// GDCCCLUTG84_U Register
#define LCDC_GDCCCLUTG84_U_OFS                   0x00000AA4
// CLUTG169 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG84_U_CLUTG169_MASK         0xFF
#define LCDC_GDCCCLUTG84_U_CLUTG169_SHIFT        0 
#define LCDC_GDCCCLUTG84_U_CLUTG169_BIT          0xFF
#define LCDC_GDCCCLUTG84_U_CLUTG169_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG84_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG84_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG84_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG84_U_RESERVED_BITWIDTH     24
// GDCCCLUTG85_L Register
#define LCDC_GDCCCLUTG85_L_OFS                   0x00000AA8
// CLUTG170 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG85_L_CLUTG170_MASK         0xFF
#define LCDC_GDCCCLUTG85_L_CLUTG170_SHIFT        0 
#define LCDC_GDCCCLUTG85_L_CLUTG170_BIT          0xFF
#define LCDC_GDCCCLUTG85_L_CLUTG170_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG85_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG85_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG85_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG85_L_RESERVED_BITWIDTH     24
// GDCCCLUTG85_U Register
#define LCDC_GDCCCLUTG85_U_OFS                   0x00000AAC
// CLUTG171 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG85_U_CLUTG171_MASK         0xFF
#define LCDC_GDCCCLUTG85_U_CLUTG171_SHIFT        0 
#define LCDC_GDCCCLUTG85_U_CLUTG171_BIT          0xFF
#define LCDC_GDCCCLUTG85_U_CLUTG171_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG85_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG85_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG85_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG85_U_RESERVED_BITWIDTH     24
// GDCCCLUTG86_L Register
#define LCDC_GDCCCLUTG86_L_OFS                   0x00000AB0
// CLUTG172 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG86_L_CLUTG172_MASK         0xFF
#define LCDC_GDCCCLUTG86_L_CLUTG172_SHIFT        0 
#define LCDC_GDCCCLUTG86_L_CLUTG172_BIT          0xFF
#define LCDC_GDCCCLUTG86_L_CLUTG172_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG86_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG86_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG86_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG86_L_RESERVED_BITWIDTH     24
// GDCCCLUTG86_U Register
#define LCDC_GDCCCLUTG86_U_OFS                   0x00000AB4
// CLUTG173 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG86_U_CLUTG173_MASK         0xFF
#define LCDC_GDCCCLUTG86_U_CLUTG173_SHIFT        0 
#define LCDC_GDCCCLUTG86_U_CLUTG173_BIT          0xFF
#define LCDC_GDCCCLUTG86_U_CLUTG173_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG86_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG86_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG86_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG86_U_RESERVED_BITWIDTH     24
// GDCCCLUTG87_L Register
#define LCDC_GDCCCLUTG87_L_OFS                   0x00000AB8
// CLUTG174 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG87_L_CLUTG174_MASK         0xFF
#define LCDC_GDCCCLUTG87_L_CLUTG174_SHIFT        0 
#define LCDC_GDCCCLUTG87_L_CLUTG174_BIT          0xFF
#define LCDC_GDCCCLUTG87_L_CLUTG174_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG87_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG87_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG87_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG87_L_RESERVED_BITWIDTH     24
// GDCCCLUTG87_U Register
#define LCDC_GDCCCLUTG87_U_OFS                   0x00000ABC
// CLUTG175 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG87_U_CLUTG175_MASK         0xFF
#define LCDC_GDCCCLUTG87_U_CLUTG175_SHIFT        0 
#define LCDC_GDCCCLUTG87_U_CLUTG175_BIT          0xFF
#define LCDC_GDCCCLUTG87_U_CLUTG175_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG87_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG87_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG87_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG87_U_RESERVED_BITWIDTH     24
// GDCCCLUTG88_L Register
#define LCDC_GDCCCLUTG88_L_OFS                   0x00000AC0
// CLUTG176 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG88_L_CLUTG176_MASK         0xFF
#define LCDC_GDCCCLUTG88_L_CLUTG176_SHIFT        0 
#define LCDC_GDCCCLUTG88_L_CLUTG176_BIT          0xFF
#define LCDC_GDCCCLUTG88_L_CLUTG176_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG88_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG88_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG88_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG88_L_RESERVED_BITWIDTH     24
// GDCCCLUTG88_U Register
#define LCDC_GDCCCLUTG88_U_OFS                   0x00000AC4
// CLUTG177 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG88_U_CLUTG177_MASK         0xFF
#define LCDC_GDCCCLUTG88_U_CLUTG177_SHIFT        0 
#define LCDC_GDCCCLUTG88_U_CLUTG177_BIT          0xFF
#define LCDC_GDCCCLUTG88_U_CLUTG177_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG88_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG88_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG88_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG88_U_RESERVED_BITWIDTH     24
// GDCCCLUTG89_L Register
#define LCDC_GDCCCLUTG89_L_OFS                   0x00000AC8
// CLUTG178 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG89_L_CLUTG178_MASK         0xFF
#define LCDC_GDCCCLUTG89_L_CLUTG178_SHIFT        0 
#define LCDC_GDCCCLUTG89_L_CLUTG178_BIT          0xFF
#define LCDC_GDCCCLUTG89_L_CLUTG178_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG89_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG89_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG89_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG89_L_RESERVED_BITWIDTH     24
// GDCCCLUTG89_U Register
#define LCDC_GDCCCLUTG89_U_OFS                   0x00000ACC
// CLUTG179 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG89_U_CLUTG179_MASK         0xFF
#define LCDC_GDCCCLUTG89_U_CLUTG179_SHIFT        0 
#define LCDC_GDCCCLUTG89_U_CLUTG179_BIT          0xFF
#define LCDC_GDCCCLUTG89_U_CLUTG179_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG89_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG89_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG89_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG89_U_RESERVED_BITWIDTH     24
// GDCCCLUTG90_L Register
#define LCDC_GDCCCLUTG90_L_OFS                   0x00000AD0
// CLUTG180 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG90_L_CLUTG180_MASK         0xFF
#define LCDC_GDCCCLUTG90_L_CLUTG180_SHIFT        0 
#define LCDC_GDCCCLUTG90_L_CLUTG180_BIT          0xFF
#define LCDC_GDCCCLUTG90_L_CLUTG180_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG90_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG90_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG90_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG90_L_RESERVED_BITWIDTH     24
// GDCCCLUTG90_U Register
#define LCDC_GDCCCLUTG90_U_OFS                   0x00000AD4
// CLUTG181 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG90_U_CLUTG181_MASK         0xFF
#define LCDC_GDCCCLUTG90_U_CLUTG181_SHIFT        0 
#define LCDC_GDCCCLUTG90_U_CLUTG181_BIT          0xFF
#define LCDC_GDCCCLUTG90_U_CLUTG181_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG90_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG90_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG90_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG90_U_RESERVED_BITWIDTH     24
// GDCCCLUTG91_L Register
#define LCDC_GDCCCLUTG91_L_OFS                   0x00000AD8
// CLUTG182 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG91_L_CLUTG182_MASK         0xFF
#define LCDC_GDCCCLUTG91_L_CLUTG182_SHIFT        0 
#define LCDC_GDCCCLUTG91_L_CLUTG182_BIT          0xFF
#define LCDC_GDCCCLUTG91_L_CLUTG182_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG91_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG91_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG91_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG91_L_RESERVED_BITWIDTH     24
// GDCCCLUTG91_U Register
#define LCDC_GDCCCLUTG91_U_OFS                   0x00000ADC
// CLUTG183 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG91_U_CLUTG183_MASK         0xFF
#define LCDC_GDCCCLUTG91_U_CLUTG183_SHIFT        0 
#define LCDC_GDCCCLUTG91_U_CLUTG183_BIT          0xFF
#define LCDC_GDCCCLUTG91_U_CLUTG183_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG91_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG91_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG91_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG91_U_RESERVED_BITWIDTH     24
// GDCCCLUTG92_L Register
#define LCDC_GDCCCLUTG92_L_OFS                   0x00000AE0
// CLUTG184 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG92_L_CLUTG184_MASK         0xFF
#define LCDC_GDCCCLUTG92_L_CLUTG184_SHIFT        0 
#define LCDC_GDCCCLUTG92_L_CLUTG184_BIT          0xFF
#define LCDC_GDCCCLUTG92_L_CLUTG184_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG92_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG92_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG92_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG92_L_RESERVED_BITWIDTH     24
// GDCCCLUTG92_U Register
#define LCDC_GDCCCLUTG92_U_OFS                   0x00000AE4
// CLUTG185 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG92_U_CLUTG185_MASK         0xFF
#define LCDC_GDCCCLUTG92_U_CLUTG185_SHIFT        0 
#define LCDC_GDCCCLUTG92_U_CLUTG185_BIT          0xFF
#define LCDC_GDCCCLUTG92_U_CLUTG185_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG92_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG92_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG92_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG92_U_RESERVED_BITWIDTH     24
// GDCCCLUTG93_L Register
#define LCDC_GDCCCLUTG93_L_OFS                   0x00000AE8
// CLUTG186 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG93_L_CLUTG186_MASK         0xFF
#define LCDC_GDCCCLUTG93_L_CLUTG186_SHIFT        0 
#define LCDC_GDCCCLUTG93_L_CLUTG186_BIT          0xFF
#define LCDC_GDCCCLUTG93_L_CLUTG186_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG93_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG93_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG93_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG93_L_RESERVED_BITWIDTH     24
// GDCCCLUTG93_U Register
#define LCDC_GDCCCLUTG93_U_OFS                   0x00000AEC
// CLUTG187 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG93_U_CLUTG187_MASK         0xFF
#define LCDC_GDCCCLUTG93_U_CLUTG187_SHIFT        0 
#define LCDC_GDCCCLUTG93_U_CLUTG187_BIT          0xFF
#define LCDC_GDCCCLUTG93_U_CLUTG187_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG93_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG93_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG93_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG93_U_RESERVED_BITWIDTH     24
// GDCCCLUTG94_L Register
#define LCDC_GDCCCLUTG94_L_OFS                   0x00000AF0
// CLUTG188 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG94_L_CLUTG188_MASK         0xFF
#define LCDC_GDCCCLUTG94_L_CLUTG188_SHIFT        0 
#define LCDC_GDCCCLUTG94_L_CLUTG188_BIT          0xFF
#define LCDC_GDCCCLUTG94_L_CLUTG188_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG94_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG94_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG94_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG94_L_RESERVED_BITWIDTH     24
// GDCCCLUTG94_U Register
#define LCDC_GDCCCLUTG94_U_OFS                   0x00000AF4
// CLUTG189 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG94_U_CLUTG189_MASK         0xFF
#define LCDC_GDCCCLUTG94_U_CLUTG189_SHIFT        0 
#define LCDC_GDCCCLUTG94_U_CLUTG189_BIT          0xFF
#define LCDC_GDCCCLUTG94_U_CLUTG189_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG94_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG94_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG94_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG94_U_RESERVED_BITWIDTH     24
// GDCCCLUTG95_L Register
#define LCDC_GDCCCLUTG95_L_OFS                   0x00000AF8
// CLUTG190 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG95_L_CLUTG190_MASK         0xFF
#define LCDC_GDCCCLUTG95_L_CLUTG190_SHIFT        0 
#define LCDC_GDCCCLUTG95_L_CLUTG190_BIT          0xFF
#define LCDC_GDCCCLUTG95_L_CLUTG190_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG95_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG95_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG95_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG95_L_RESERVED_BITWIDTH     24
// GDCCCLUTG95_U Register
#define LCDC_GDCCCLUTG95_U_OFS                   0x00000AFC
// CLUTG191 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG95_U_CLUTG191_MASK         0xFF
#define LCDC_GDCCCLUTG95_U_CLUTG191_SHIFT        0 
#define LCDC_GDCCCLUTG95_U_CLUTG191_BIT          0xFF
#define LCDC_GDCCCLUTG95_U_CLUTG191_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG95_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG95_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG95_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG95_U_RESERVED_BITWIDTH     24
// GDCCCLUTG96_L Register
#define LCDC_GDCCCLUTG96_L_OFS                   0x00000B00
// CLUTG192 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG96_L_CLUTG192_MASK         0xFF
#define LCDC_GDCCCLUTG96_L_CLUTG192_SHIFT        0 
#define LCDC_GDCCCLUTG96_L_CLUTG192_BIT          0xFF
#define LCDC_GDCCCLUTG96_L_CLUTG192_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG96_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG96_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG96_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG96_L_RESERVED_BITWIDTH     24
// GDCCCLUTG96_U Register
#define LCDC_GDCCCLUTG96_U_OFS                   0x00000B04
// CLUTG193 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG96_U_CLUTG193_MASK         0xFF
#define LCDC_GDCCCLUTG96_U_CLUTG193_SHIFT        0 
#define LCDC_GDCCCLUTG96_U_CLUTG193_BIT          0xFF
#define LCDC_GDCCCLUTG96_U_CLUTG193_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG96_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG96_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG96_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG96_U_RESERVED_BITWIDTH     24
// GDCCCLUTG97_L Register
#define LCDC_GDCCCLUTG97_L_OFS                   0x00000B08
// CLUTG194 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG97_L_CLUTG194_MASK         0xFF
#define LCDC_GDCCCLUTG97_L_CLUTG194_SHIFT        0 
#define LCDC_GDCCCLUTG97_L_CLUTG194_BIT          0xFF
#define LCDC_GDCCCLUTG97_L_CLUTG194_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG97_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG97_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG97_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG97_L_RESERVED_BITWIDTH     24
// GDCCCLUTG97_U Register
#define LCDC_GDCCCLUTG97_U_OFS                   0x00000B0C
// CLUTG195 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG97_U_CLUTG195_MASK         0xFF
#define LCDC_GDCCCLUTG97_U_CLUTG195_SHIFT        0 
#define LCDC_GDCCCLUTG97_U_CLUTG195_BIT          0xFF
#define LCDC_GDCCCLUTG97_U_CLUTG195_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG97_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG97_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG97_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG97_U_RESERVED_BITWIDTH     24
// GDCCCLUTG98_L Register
#define LCDC_GDCCCLUTG98_L_OFS                   0x00000B10
// CLUTG196 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG98_L_CLUTG196_MASK         0xFF
#define LCDC_GDCCCLUTG98_L_CLUTG196_SHIFT        0 
#define LCDC_GDCCCLUTG98_L_CLUTG196_BIT          0xFF
#define LCDC_GDCCCLUTG98_L_CLUTG196_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG98_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG98_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG98_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG98_L_RESERVED_BITWIDTH     24
// GDCCCLUTG98_U Register
#define LCDC_GDCCCLUTG98_U_OFS                   0x00000B14
// CLUTG197 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG98_U_CLUTG197_MASK         0xFF
#define LCDC_GDCCCLUTG98_U_CLUTG197_SHIFT        0 
#define LCDC_GDCCCLUTG98_U_CLUTG197_BIT          0xFF
#define LCDC_GDCCCLUTG98_U_CLUTG197_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG98_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG98_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG98_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG98_U_RESERVED_BITWIDTH     24
// GDCCCLUTG99_L Register
#define LCDC_GDCCCLUTG99_L_OFS                   0x00000B18
// CLUTG198 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG99_L_CLUTG198_MASK         0xFF
#define LCDC_GDCCCLUTG99_L_CLUTG198_SHIFT        0 
#define LCDC_GDCCCLUTG99_L_CLUTG198_BIT          0xFF
#define LCDC_GDCCCLUTG99_L_CLUTG198_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG99_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG99_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG99_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG99_L_RESERVED_BITWIDTH     24
// GDCCCLUTG99_U Register
#define LCDC_GDCCCLUTG99_U_OFS                   0x00000B1C
// CLUTG199 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG99_U_CLUTG199_MASK         0xFF
#define LCDC_GDCCCLUTG99_U_CLUTG199_SHIFT        0 
#define LCDC_GDCCCLUTG99_U_CLUTG199_BIT          0xFF
#define LCDC_GDCCCLUTG99_U_CLUTG199_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG99_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTG99_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTG99_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTG99_U_RESERVED_BITWIDTH     24
// GDCCCLUTG100_L Register
#define LCDC_GDCCCLUTG100_L_OFS                  0x00000B20
// CLUTG200 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG100_L_CLUTG200_MASK        0xFF
#define LCDC_GDCCCLUTG100_L_CLUTG200_SHIFT       0 
#define LCDC_GDCCCLUTG100_L_CLUTG200_BIT         0xFF
#define LCDC_GDCCCLUTG100_L_CLUTG200_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG100_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG100_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG100_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG100_L_RESERVED_BITWIDTH    24
// GDCCCLUTG100_U Register
#define LCDC_GDCCCLUTG100_U_OFS                  0x00000B24
// CLUTG201 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG100_U_CLUTG201_MASK        0xFF
#define LCDC_GDCCCLUTG100_U_CLUTG201_SHIFT       0 
#define LCDC_GDCCCLUTG100_U_CLUTG201_BIT         0xFF
#define LCDC_GDCCCLUTG100_U_CLUTG201_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG100_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG100_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG100_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG100_U_RESERVED_BITWIDTH    24
// GDCCCLUTG101_L Register
#define LCDC_GDCCCLUTG101_L_OFS                  0x00000B28
// CLUTG202 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG101_L_CLUTG202_MASK        0xFF
#define LCDC_GDCCCLUTG101_L_CLUTG202_SHIFT       0 
#define LCDC_GDCCCLUTG101_L_CLUTG202_BIT         0xFF
#define LCDC_GDCCCLUTG101_L_CLUTG202_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG101_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG101_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG101_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG101_L_RESERVED_BITWIDTH    24
// GDCCCLUTG101_U Register
#define LCDC_GDCCCLUTG101_U_OFS                  0x00000B2C
// CLUTG203 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG101_U_CLUTG203_MASK        0xFF
#define LCDC_GDCCCLUTG101_U_CLUTG203_SHIFT       0 
#define LCDC_GDCCCLUTG101_U_CLUTG203_BIT         0xFF
#define LCDC_GDCCCLUTG101_U_CLUTG203_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG101_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG101_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG101_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG101_U_RESERVED_BITWIDTH    24
// GDCCCLUTG102_L Register
#define LCDC_GDCCCLUTG102_L_OFS                  0x00000B30
// CLUTG204 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG102_L_CLUTG204_MASK        0xFF
#define LCDC_GDCCCLUTG102_L_CLUTG204_SHIFT       0 
#define LCDC_GDCCCLUTG102_L_CLUTG204_BIT         0xFF
#define LCDC_GDCCCLUTG102_L_CLUTG204_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG102_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG102_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG102_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG102_L_RESERVED_BITWIDTH    24
// GDCCCLUTG102_U Register
#define LCDC_GDCCCLUTG102_U_OFS                  0x00000B34
// CLUTG205 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG102_U_CLUTG205_MASK        0xFF
#define LCDC_GDCCCLUTG102_U_CLUTG205_SHIFT       0 
#define LCDC_GDCCCLUTG102_U_CLUTG205_BIT         0xFF
#define LCDC_GDCCCLUTG102_U_CLUTG205_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG102_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG102_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG102_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG102_U_RESERVED_BITWIDTH    24
// GDCCCLUTG103_L Register
#define LCDC_GDCCCLUTG103_L_OFS                  0x00000B38
// CLUTG206 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG103_L_CLUTG206_MASK        0xFF
#define LCDC_GDCCCLUTG103_L_CLUTG206_SHIFT       0 
#define LCDC_GDCCCLUTG103_L_CLUTG206_BIT         0xFF
#define LCDC_GDCCCLUTG103_L_CLUTG206_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG103_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG103_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG103_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG103_L_RESERVED_BITWIDTH    24
// GDCCCLUTG103_U Register
#define LCDC_GDCCCLUTG103_U_OFS                  0x00000B3C
// CLUTG207 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG103_U_CLUTG207_MASK        0xFF
#define LCDC_GDCCCLUTG103_U_CLUTG207_SHIFT       0 
#define LCDC_GDCCCLUTG103_U_CLUTG207_BIT         0xFF
#define LCDC_GDCCCLUTG103_U_CLUTG207_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG103_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG103_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG103_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG103_U_RESERVED_BITWIDTH    24
// GDCCCLUTG104_L Register
#define LCDC_GDCCCLUTG104_L_OFS                  0x00000B40
// CLUTG208 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG104_L_CLUTG208_MASK        0xFF
#define LCDC_GDCCCLUTG104_L_CLUTG208_SHIFT       0 
#define LCDC_GDCCCLUTG104_L_CLUTG208_BIT         0xFF
#define LCDC_GDCCCLUTG104_L_CLUTG208_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG104_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG104_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG104_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG104_L_RESERVED_BITWIDTH    24
// GDCCCLUTG104_U Register
#define LCDC_GDCCCLUTG104_U_OFS                  0x00000B44
// CLUTG209 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG104_U_CLUTG209_MASK        0xFF
#define LCDC_GDCCCLUTG104_U_CLUTG209_SHIFT       0 
#define LCDC_GDCCCLUTG104_U_CLUTG209_BIT         0xFF
#define LCDC_GDCCCLUTG104_U_CLUTG209_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG104_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG104_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG104_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG104_U_RESERVED_BITWIDTH    24
// GDCCCLUTG105_L Register
#define LCDC_GDCCCLUTG105_L_OFS                  0x00000B48
// CLUTG210 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG105_L_CLUTG210_MASK        0xFF
#define LCDC_GDCCCLUTG105_L_CLUTG210_SHIFT       0 
#define LCDC_GDCCCLUTG105_L_CLUTG210_BIT         0xFF
#define LCDC_GDCCCLUTG105_L_CLUTG210_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG105_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG105_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG105_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG105_L_RESERVED_BITWIDTH    24
// GDCCCLUTG105_U Register
#define LCDC_GDCCCLUTG105_U_OFS                  0x00000B4C
// CLUTG211 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG105_U_CLUTG211_MASK        0xFF
#define LCDC_GDCCCLUTG105_U_CLUTG211_SHIFT       0 
#define LCDC_GDCCCLUTG105_U_CLUTG211_BIT         0xFF
#define LCDC_GDCCCLUTG105_U_CLUTG211_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG105_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG105_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG105_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG105_U_RESERVED_BITWIDTH    24
// GDCCCLUTG106_L Register
#define LCDC_GDCCCLUTG106_L_OFS                  0x00000B50
// CLUTG212 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG106_L_CLUTG212_MASK        0xFF
#define LCDC_GDCCCLUTG106_L_CLUTG212_SHIFT       0 
#define LCDC_GDCCCLUTG106_L_CLUTG212_BIT         0xFF
#define LCDC_GDCCCLUTG106_L_CLUTG212_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG106_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG106_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG106_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG106_L_RESERVED_BITWIDTH    24
// GDCCCLUTG106_U Register
#define LCDC_GDCCCLUTG106_U_OFS                  0x00000B54
// CLUTG213 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG106_U_CLUTG213_MASK        0xFF
#define LCDC_GDCCCLUTG106_U_CLUTG213_SHIFT       0 
#define LCDC_GDCCCLUTG106_U_CLUTG213_BIT         0xFF
#define LCDC_GDCCCLUTG106_U_CLUTG213_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG106_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG106_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG106_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG106_U_RESERVED_BITWIDTH    24
// GDCCCLUTG107_L Register
#define LCDC_GDCCCLUTG107_L_OFS                  0x00000B58
// CLUTG214 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG107_L_CLUTG214_MASK        0xFF
#define LCDC_GDCCCLUTG107_L_CLUTG214_SHIFT       0 
#define LCDC_GDCCCLUTG107_L_CLUTG214_BIT         0xFF
#define LCDC_GDCCCLUTG107_L_CLUTG214_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG107_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG107_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG107_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG107_L_RESERVED_BITWIDTH    24
// GDCCCLUTG107_U Register
#define LCDC_GDCCCLUTG107_U_OFS                  0x00000B5C
// CLUTG215 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG107_U_CLUTG215_MASK        0xFF
#define LCDC_GDCCCLUTG107_U_CLUTG215_SHIFT       0 
#define LCDC_GDCCCLUTG107_U_CLUTG215_BIT         0xFF
#define LCDC_GDCCCLUTG107_U_CLUTG215_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG107_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG107_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG107_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG107_U_RESERVED_BITWIDTH    24
// GDCCCLUTG108_L Register
#define LCDC_GDCCCLUTG108_L_OFS                  0x00000B60
// CLUTG216 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG108_L_CLUTG216_MASK        0xFF
#define LCDC_GDCCCLUTG108_L_CLUTG216_SHIFT       0 
#define LCDC_GDCCCLUTG108_L_CLUTG216_BIT         0xFF
#define LCDC_GDCCCLUTG108_L_CLUTG216_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG108_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG108_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG108_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG108_L_RESERVED_BITWIDTH    24
// GDCCCLUTG108_U Register
#define LCDC_GDCCCLUTG108_U_OFS                  0x00000B64
// CLUTG217 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG108_U_CLUTG217_MASK        0xFF
#define LCDC_GDCCCLUTG108_U_CLUTG217_SHIFT       0 
#define LCDC_GDCCCLUTG108_U_CLUTG217_BIT         0xFF
#define LCDC_GDCCCLUTG108_U_CLUTG217_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG108_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG108_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG108_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG108_U_RESERVED_BITWIDTH    24
// GDCCCLUTG109_L Register
#define LCDC_GDCCCLUTG109_L_OFS                  0x00000B68
// CLUTG218 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG109_L_CLUTG218_MASK        0xFF
#define LCDC_GDCCCLUTG109_L_CLUTG218_SHIFT       0 
#define LCDC_GDCCCLUTG109_L_CLUTG218_BIT         0xFF
#define LCDC_GDCCCLUTG109_L_CLUTG218_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG109_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG109_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG109_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG109_L_RESERVED_BITWIDTH    24
// GDCCCLUTG109_U Register
#define LCDC_GDCCCLUTG109_U_OFS                  0x00000B6C
// CLUTG219 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG109_U_CLUTG219_MASK        0xFF
#define LCDC_GDCCCLUTG109_U_CLUTG219_SHIFT       0 
#define LCDC_GDCCCLUTG109_U_CLUTG219_BIT         0xFF
#define LCDC_GDCCCLUTG109_U_CLUTG219_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG109_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG109_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG109_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG109_U_RESERVED_BITWIDTH    24
// GDCCCLUTG110_L Register
#define LCDC_GDCCCLUTG110_L_OFS                  0x00000B70
// CLUTG220 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG110_L_CLUTG220_MASK        0xFF
#define LCDC_GDCCCLUTG110_L_CLUTG220_SHIFT       0 
#define LCDC_GDCCCLUTG110_L_CLUTG220_BIT         0xFF
#define LCDC_GDCCCLUTG110_L_CLUTG220_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG110_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG110_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG110_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG110_L_RESERVED_BITWIDTH    24
// GDCCCLUTG110_U Register
#define LCDC_GDCCCLUTG110_U_OFS                  0x00000B74
// CLUTG221 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG110_U_CLUTG221_MASK        0xFF
#define LCDC_GDCCCLUTG110_U_CLUTG221_SHIFT       0 
#define LCDC_GDCCCLUTG110_U_CLUTG221_BIT         0xFF
#define LCDC_GDCCCLUTG110_U_CLUTG221_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG110_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG110_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG110_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG110_U_RESERVED_BITWIDTH    24
// GDCCCLUTG111_L Register
#define LCDC_GDCCCLUTG111_L_OFS                  0x00000B78
// CLUTG222 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG111_L_CLUTG222_MASK        0xFF
#define LCDC_GDCCCLUTG111_L_CLUTG222_SHIFT       0 
#define LCDC_GDCCCLUTG111_L_CLUTG222_BIT         0xFF
#define LCDC_GDCCCLUTG111_L_CLUTG222_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG111_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG111_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG111_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG111_L_RESERVED_BITWIDTH    24
// GDCCCLUTG111_U Register
#define LCDC_GDCCCLUTG111_U_OFS                  0x00000B7C
// CLUTG223 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG111_U_CLUTG223_MASK        0xFF
#define LCDC_GDCCCLUTG111_U_CLUTG223_SHIFT       0 
#define LCDC_GDCCCLUTG111_U_CLUTG223_BIT         0xFF
#define LCDC_GDCCCLUTG111_U_CLUTG223_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG111_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG111_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG111_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG111_U_RESERVED_BITWIDTH    24
// GDCCCLUTG112_L Register
#define LCDC_GDCCCLUTG112_L_OFS                  0x00000B80
// CLUTG224 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG112_L_CLUTG224_MASK        0xFF
#define LCDC_GDCCCLUTG112_L_CLUTG224_SHIFT       0 
#define LCDC_GDCCCLUTG112_L_CLUTG224_BIT         0xFF
#define LCDC_GDCCCLUTG112_L_CLUTG224_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG112_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG112_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG112_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG112_L_RESERVED_BITWIDTH    24
// GDCCCLUTG112_U Register
#define LCDC_GDCCCLUTG112_U_OFS                  0x00000B84
// CLUTG225 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG112_U_CLUTG225_MASK        0xFF
#define LCDC_GDCCCLUTG112_U_CLUTG225_SHIFT       0 
#define LCDC_GDCCCLUTG112_U_CLUTG225_BIT         0xFF
#define LCDC_GDCCCLUTG112_U_CLUTG225_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG112_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG112_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG112_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG112_U_RESERVED_BITWIDTH    24
// GDCCCLUTG113_L Register
#define LCDC_GDCCCLUTG113_L_OFS                  0x00000B88
// CLUTG226 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG113_L_CLUTG226_MASK        0xFF
#define LCDC_GDCCCLUTG113_L_CLUTG226_SHIFT       0 
#define LCDC_GDCCCLUTG113_L_CLUTG226_BIT         0xFF
#define LCDC_GDCCCLUTG113_L_CLUTG226_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG113_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG113_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG113_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG113_L_RESERVED_BITWIDTH    24
// GDCCCLUTG113_U Register
#define LCDC_GDCCCLUTG113_U_OFS                  0x00000B8C
// CLUTG227 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG113_U_CLUTG227_MASK        0xFF
#define LCDC_GDCCCLUTG113_U_CLUTG227_SHIFT       0 
#define LCDC_GDCCCLUTG113_U_CLUTG227_BIT         0xFF
#define LCDC_GDCCCLUTG113_U_CLUTG227_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG113_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG113_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG113_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG113_U_RESERVED_BITWIDTH    24
// GDCCCLUTG114_L Register
#define LCDC_GDCCCLUTG114_L_OFS                  0x00000B90
// CLUTG228 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG114_L_CLUTG228_MASK        0xFF
#define LCDC_GDCCCLUTG114_L_CLUTG228_SHIFT       0 
#define LCDC_GDCCCLUTG114_L_CLUTG228_BIT         0xFF
#define LCDC_GDCCCLUTG114_L_CLUTG228_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG114_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG114_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG114_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG114_L_RESERVED_BITWIDTH    24
// GDCCCLUTG114_U Register
#define LCDC_GDCCCLUTG114_U_OFS                  0x00000B94
// CLUTG229 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG114_U_CLUTG229_MASK        0xFF
#define LCDC_GDCCCLUTG114_U_CLUTG229_SHIFT       0 
#define LCDC_GDCCCLUTG114_U_CLUTG229_BIT         0xFF
#define LCDC_GDCCCLUTG114_U_CLUTG229_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG114_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG114_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG114_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG114_U_RESERVED_BITWIDTH    24
// GDCCCLUTG115_L Register
#define LCDC_GDCCCLUTG115_L_OFS                  0x00000B98
// CLUTG230 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG115_L_CLUTG230_MASK        0xFF
#define LCDC_GDCCCLUTG115_L_CLUTG230_SHIFT       0 
#define LCDC_GDCCCLUTG115_L_CLUTG230_BIT         0xFF
#define LCDC_GDCCCLUTG115_L_CLUTG230_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG115_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG115_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG115_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG115_L_RESERVED_BITWIDTH    24
// GDCCCLUTG115_U Register
#define LCDC_GDCCCLUTG115_U_OFS                  0x00000B9C
// CLUTG231 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG115_U_CLUTG231_MASK        0xFF
#define LCDC_GDCCCLUTG115_U_CLUTG231_SHIFT       0 
#define LCDC_GDCCCLUTG115_U_CLUTG231_BIT         0xFF
#define LCDC_GDCCCLUTG115_U_CLUTG231_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG115_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG115_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG115_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG115_U_RESERVED_BITWIDTH    24
// GDCCCLUTG116_L Register
#define LCDC_GDCCCLUTG116_L_OFS                  0x00000BA0
// CLUTG232 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG116_L_CLUTG232_MASK        0xFF
#define LCDC_GDCCCLUTG116_L_CLUTG232_SHIFT       0 
#define LCDC_GDCCCLUTG116_L_CLUTG232_BIT         0xFF
#define LCDC_GDCCCLUTG116_L_CLUTG232_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG116_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG116_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG116_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG116_L_RESERVED_BITWIDTH    24
// GDCCCLUTG116_U Register
#define LCDC_GDCCCLUTG116_U_OFS                  0x00000BA4
// CLUTG233 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG116_U_CLUTG233_MASK        0xFF
#define LCDC_GDCCCLUTG116_U_CLUTG233_SHIFT       0 
#define LCDC_GDCCCLUTG116_U_CLUTG233_BIT         0xFF
#define LCDC_GDCCCLUTG116_U_CLUTG233_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG116_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG116_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG116_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG116_U_RESERVED_BITWIDTH    24
// GDCCCLUTG117_L Register
#define LCDC_GDCCCLUTG117_L_OFS                  0x00000BA8
// CLUTG234 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG117_L_CLUTG234_MASK        0xFF
#define LCDC_GDCCCLUTG117_L_CLUTG234_SHIFT       0 
#define LCDC_GDCCCLUTG117_L_CLUTG234_BIT         0xFF
#define LCDC_GDCCCLUTG117_L_CLUTG234_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG117_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG117_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG117_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG117_L_RESERVED_BITWIDTH    24
// GDCCCLUTG117_U Register
#define LCDC_GDCCCLUTG117_U_OFS                  0x00000BAC
// CLUTG235 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG117_U_CLUTG235_MASK        0xFF
#define LCDC_GDCCCLUTG117_U_CLUTG235_SHIFT       0 
#define LCDC_GDCCCLUTG117_U_CLUTG235_BIT         0xFF
#define LCDC_GDCCCLUTG117_U_CLUTG235_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG117_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG117_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG117_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG117_U_RESERVED_BITWIDTH    24
// GDCCCLUTG118_L Register
#define LCDC_GDCCCLUTG118_L_OFS                  0x00000BB0
// CLUTG236 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG118_L_CLUTG236_MASK        0xFF
#define LCDC_GDCCCLUTG118_L_CLUTG236_SHIFT       0 
#define LCDC_GDCCCLUTG118_L_CLUTG236_BIT         0xFF
#define LCDC_GDCCCLUTG118_L_CLUTG236_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG118_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG118_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG118_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG118_L_RESERVED_BITWIDTH    24
// GDCCCLUTG118_U Register
#define LCDC_GDCCCLUTG118_U_OFS                  0x00000BB4
// CLUTG237 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG118_U_CLUTG237_MASK        0xFF
#define LCDC_GDCCCLUTG118_U_CLUTG237_SHIFT       0 
#define LCDC_GDCCCLUTG118_U_CLUTG237_BIT         0xFF
#define LCDC_GDCCCLUTG118_U_CLUTG237_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG118_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG118_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG118_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG118_U_RESERVED_BITWIDTH    24
// GDCCCLUTG119_L Register
#define LCDC_GDCCCLUTG119_L_OFS                  0x00000BB8
// CLUTG238 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG119_L_CLUTG238_MASK        0xFF
#define LCDC_GDCCCLUTG119_L_CLUTG238_SHIFT       0 
#define LCDC_GDCCCLUTG119_L_CLUTG238_BIT         0xFF
#define LCDC_GDCCCLUTG119_L_CLUTG238_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG119_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG119_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG119_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG119_L_RESERVED_BITWIDTH    24
// GDCCCLUTG119_U Register
#define LCDC_GDCCCLUTG119_U_OFS                  0x00000BBC
// CLUTG239 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG119_U_CLUTG239_MASK        0xFF
#define LCDC_GDCCCLUTG119_U_CLUTG239_SHIFT       0 
#define LCDC_GDCCCLUTG119_U_CLUTG239_BIT         0xFF
#define LCDC_GDCCCLUTG119_U_CLUTG239_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG119_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG119_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG119_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG119_U_RESERVED_BITWIDTH    24
// GDCCCLUTG120_L Register
#define LCDC_GDCCCLUTG120_L_OFS                  0x00000BC0
// CLUTG240 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG120_L_CLUTG240_MASK        0xFF
#define LCDC_GDCCCLUTG120_L_CLUTG240_SHIFT       0 
#define LCDC_GDCCCLUTG120_L_CLUTG240_BIT         0xFF
#define LCDC_GDCCCLUTG120_L_CLUTG240_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG120_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG120_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG120_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG120_L_RESERVED_BITWIDTH    24
// GDCCCLUTG120_U Register
#define LCDC_GDCCCLUTG120_U_OFS                  0x00000BC4
// CLUTG241 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG120_U_CLUTG241_MASK        0xFF
#define LCDC_GDCCCLUTG120_U_CLUTG241_SHIFT       0 
#define LCDC_GDCCCLUTG120_U_CLUTG241_BIT         0xFF
#define LCDC_GDCCCLUTG120_U_CLUTG241_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG120_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG120_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG120_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG120_U_RESERVED_BITWIDTH    24
// GDCCCLUTG121_L Register
#define LCDC_GDCCCLUTG121_L_OFS                  0x00000BC8
// CLUTG242 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG121_L_CLUTG242_MASK        0xFF
#define LCDC_GDCCCLUTG121_L_CLUTG242_SHIFT       0 
#define LCDC_GDCCCLUTG121_L_CLUTG242_BIT         0xFF
#define LCDC_GDCCCLUTG121_L_CLUTG242_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG121_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG121_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG121_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG121_L_RESERVED_BITWIDTH    24
// GDCCCLUTG121_U Register
#define LCDC_GDCCCLUTG121_U_OFS                  0x00000BCC
// CLUTG243 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG121_U_CLUTG243_MASK        0xFF
#define LCDC_GDCCCLUTG121_U_CLUTG243_SHIFT       0 
#define LCDC_GDCCCLUTG121_U_CLUTG243_BIT         0xFF
#define LCDC_GDCCCLUTG121_U_CLUTG243_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG121_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG121_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG121_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG121_U_RESERVED_BITWIDTH    24
// GDCCCLUTG122_L Register
#define LCDC_GDCCCLUTG122_L_OFS                  0x00000BD0
// CLUTG244 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG122_L_CLUTG244_MASK        0xFF
#define LCDC_GDCCCLUTG122_L_CLUTG244_SHIFT       0 
#define LCDC_GDCCCLUTG122_L_CLUTG244_BIT         0xFF
#define LCDC_GDCCCLUTG122_L_CLUTG244_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG122_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG122_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG122_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG122_L_RESERVED_BITWIDTH    24
// GDCCCLUTG122_U Register
#define LCDC_GDCCCLUTG122_U_OFS                  0x00000BD4
// CLUTG245 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG122_U_CLUTG245_MASK        0xFF
#define LCDC_GDCCCLUTG122_U_CLUTG245_SHIFT       0 
#define LCDC_GDCCCLUTG122_U_CLUTG245_BIT         0xFF
#define LCDC_GDCCCLUTG122_U_CLUTG245_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG122_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG122_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG122_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG122_U_RESERVED_BITWIDTH    24
// GDCCCLUTG123_L Register
#define LCDC_GDCCCLUTG123_L_OFS                  0x00000BD8
// CLUTG246 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG123_L_CLUTG246_MASK        0xFF
#define LCDC_GDCCCLUTG123_L_CLUTG246_SHIFT       0 
#define LCDC_GDCCCLUTG123_L_CLUTG246_BIT         0xFF
#define LCDC_GDCCCLUTG123_L_CLUTG246_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG123_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG123_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG123_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG123_L_RESERVED_BITWIDTH    24
// GDCCCLUTG123_U Register
#define LCDC_GDCCCLUTG123_U_OFS                  0x00000BDC
// CLUTG247 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG123_U_CLUTG247_MASK        0xFF
#define LCDC_GDCCCLUTG123_U_CLUTG247_SHIFT       0 
#define LCDC_GDCCCLUTG123_U_CLUTG247_BIT         0xFF
#define LCDC_GDCCCLUTG123_U_CLUTG247_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG123_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG123_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG123_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG123_U_RESERVED_BITWIDTH    24
// GDCCCLUTG124_L Register
#define LCDC_GDCCCLUTG124_L_OFS                  0x00000BE0
// CLUTG248 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG124_L_CLUTG248_MASK        0xFF
#define LCDC_GDCCCLUTG124_L_CLUTG248_SHIFT       0 
#define LCDC_GDCCCLUTG124_L_CLUTG248_BIT         0xFF
#define LCDC_GDCCCLUTG124_L_CLUTG248_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG124_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG124_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG124_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG124_L_RESERVED_BITWIDTH    24
// GDCCCLUTG124_U Register
#define LCDC_GDCCCLUTG124_U_OFS                  0x00000BE4
// CLUTG249 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG124_U_CLUTG249_MASK        0xFF
#define LCDC_GDCCCLUTG124_U_CLUTG249_SHIFT       0 
#define LCDC_GDCCCLUTG124_U_CLUTG249_BIT         0xFF
#define LCDC_GDCCCLUTG124_U_CLUTG249_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG124_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG124_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG124_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG124_U_RESERVED_BITWIDTH    24
// GDCCCLUTG125_L Register
#define LCDC_GDCCCLUTG125_L_OFS                  0x00000BE8
// CLUTG250 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG125_L_CLUTG250_MASK        0xFF
#define LCDC_GDCCCLUTG125_L_CLUTG250_SHIFT       0 
#define LCDC_GDCCCLUTG125_L_CLUTG250_BIT         0xFF
#define LCDC_GDCCCLUTG125_L_CLUTG250_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG125_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG125_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG125_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG125_L_RESERVED_BITWIDTH    24
// GDCCCLUTG125_U Register
#define LCDC_GDCCCLUTG125_U_OFS                  0x00000BEC
// CLUTG251 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG125_U_CLUTG251_MASK        0xFF
#define LCDC_GDCCCLUTG125_U_CLUTG251_SHIFT       0 
#define LCDC_GDCCCLUTG125_U_CLUTG251_BIT         0xFF
#define LCDC_GDCCCLUTG125_U_CLUTG251_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG125_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG125_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG125_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG125_U_RESERVED_BITWIDTH    24
// GDCCCLUTG126_L Register
#define LCDC_GDCCCLUTG126_L_OFS                  0x00000BF0
// CLUTG252 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG126_L_CLUTG252_MASK        0xFF
#define LCDC_GDCCCLUTG126_L_CLUTG252_SHIFT       0 
#define LCDC_GDCCCLUTG126_L_CLUTG252_BIT         0xFF
#define LCDC_GDCCCLUTG126_L_CLUTG252_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG126_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG126_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG126_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG126_L_RESERVED_BITWIDTH    24
// GDCCCLUTG126_U Register
#define LCDC_GDCCCLUTG126_U_OFS                  0x00000BF4
// CLUTG253 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG126_U_CLUTG253_MASK        0xFF
#define LCDC_GDCCCLUTG126_U_CLUTG253_SHIFT       0 
#define LCDC_GDCCCLUTG126_U_CLUTG253_BIT         0xFF
#define LCDC_GDCCCLUTG126_U_CLUTG253_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG126_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG126_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG126_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG126_U_RESERVED_BITWIDTH    24
// GDCCCLUTG127_L Register
#define LCDC_GDCCCLUTG127_L_OFS                  0x00000BF8
// CLUTG254 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG127_L_CLUTG254_MASK        0xFF
#define LCDC_GDCCCLUTG127_L_CLUTG254_SHIFT       0 
#define LCDC_GDCCCLUTG127_L_CLUTG254_BIT         0xFF
#define LCDC_GDCCCLUTG127_L_CLUTG254_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG127_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG127_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG127_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG127_L_RESERVED_BITWIDTH    24
// GDCCCLUTG127_U Register
#define LCDC_GDCCCLUTG127_U_OFS                  0x00000BFC
// CLUTG255 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTG127_U_CLUTG255_MASK        0xFF
#define LCDC_GDCCCLUTG127_U_CLUTG255_SHIFT       0 
#define LCDC_GDCCCLUTG127_U_CLUTG255_BIT         0xFF
#define LCDC_GDCCCLUTG127_U_CLUTG255_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTG127_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTG127_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTG127_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTG127_U_RESERVED_BITWIDTH    24
// GDCCCLUTB0_L Register
#define LCDC_GDCCCLUTB0_L_OFS                    0x00000C00
// CLUTB0 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB0_L_CLUTB0_MASK            0xFF
#define LCDC_GDCCCLUTB0_L_CLUTB0_SHIFT           0 
#define LCDC_GDCCCLUTB0_L_CLUTB0_BIT             0xFF
#define LCDC_GDCCCLUTB0_L_CLUTB0_BITWIDTH        8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB0_L_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTB0_L_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTB0_L_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTB0_L_RESERVED_BITWIDTH      24
// GDCCCLUTB0_U Register
#define LCDC_GDCCCLUTB0_U_OFS                    0x00000C04
// CLUTB1 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB0_U_CLUTB1_MASK            0xFF
#define LCDC_GDCCCLUTB0_U_CLUTB1_SHIFT           0 
#define LCDC_GDCCCLUTB0_U_CLUTB1_BIT             0xFF
#define LCDC_GDCCCLUTB0_U_CLUTB1_BITWIDTH        8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB0_U_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTB0_U_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTB0_U_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTB0_U_RESERVED_BITWIDTH      24
// GDCCCLUTB1_L Register
#define LCDC_GDCCCLUTB1_L_OFS                    0x00000C08
// CLUTB2 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB1_L_CLUTB2_MASK            0xFF
#define LCDC_GDCCCLUTB1_L_CLUTB2_SHIFT           0 
#define LCDC_GDCCCLUTB1_L_CLUTB2_BIT             0xFF
#define LCDC_GDCCCLUTB1_L_CLUTB2_BITWIDTH        8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB1_L_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTB1_L_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTB1_L_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTB1_L_RESERVED_BITWIDTH      24
// GDCCCLUTB1_U Register
#define LCDC_GDCCCLUTB1_U_OFS                    0x00000C0C
// CLUTB3 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB1_U_CLUTB3_MASK            0xFF
#define LCDC_GDCCCLUTB1_U_CLUTB3_SHIFT           0 
#define LCDC_GDCCCLUTB1_U_CLUTB3_BIT             0xFF
#define LCDC_GDCCCLUTB1_U_CLUTB3_BITWIDTH        8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB1_U_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTB1_U_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTB1_U_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTB1_U_RESERVED_BITWIDTH      24
// GDCCCLUTB2_L Register
#define LCDC_GDCCCLUTB2_L_OFS                    0x00000C10
// CLUTB4 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB2_L_CLUTB4_MASK            0xFF
#define LCDC_GDCCCLUTB2_L_CLUTB4_SHIFT           0 
#define LCDC_GDCCCLUTB2_L_CLUTB4_BIT             0xFF
#define LCDC_GDCCCLUTB2_L_CLUTB4_BITWIDTH        8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB2_L_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTB2_L_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTB2_L_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTB2_L_RESERVED_BITWIDTH      24
// GDCCCLUTB2_U Register
#define LCDC_GDCCCLUTB2_U_OFS                    0x00000C14
// CLUTB5 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB2_U_CLUTB5_MASK            0xFF
#define LCDC_GDCCCLUTB2_U_CLUTB5_SHIFT           0 
#define LCDC_GDCCCLUTB2_U_CLUTB5_BIT             0xFF
#define LCDC_GDCCCLUTB2_U_CLUTB5_BITWIDTH        8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB2_U_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTB2_U_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTB2_U_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTB2_U_RESERVED_BITWIDTH      24
// GDCCCLUTB3_L Register
#define LCDC_GDCCCLUTB3_L_OFS                    0x00000C18
// CLUTB6 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB3_L_CLUTB6_MASK            0xFF
#define LCDC_GDCCCLUTB3_L_CLUTB6_SHIFT           0 
#define LCDC_GDCCCLUTB3_L_CLUTB6_BIT             0xFF
#define LCDC_GDCCCLUTB3_L_CLUTB6_BITWIDTH        8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB3_L_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTB3_L_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTB3_L_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTB3_L_RESERVED_BITWIDTH      24
// GDCCCLUTB3_U Register
#define LCDC_GDCCCLUTB3_U_OFS                    0x00000C1C
// CLUTB7 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB3_U_CLUTB7_MASK            0xFF
#define LCDC_GDCCCLUTB3_U_CLUTB7_SHIFT           0 
#define LCDC_GDCCCLUTB3_U_CLUTB7_BIT             0xFF
#define LCDC_GDCCCLUTB3_U_CLUTB7_BITWIDTH        8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB3_U_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTB3_U_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTB3_U_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTB3_U_RESERVED_BITWIDTH      24
// GDCCCLUTB4_L Register
#define LCDC_GDCCCLUTB4_L_OFS                    0x00000C20
// CLUTB8 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB4_L_CLUTB8_MASK            0xFF
#define LCDC_GDCCCLUTB4_L_CLUTB8_SHIFT           0 
#define LCDC_GDCCCLUTB4_L_CLUTB8_BIT             0xFF
#define LCDC_GDCCCLUTB4_L_CLUTB8_BITWIDTH        8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB4_L_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTB4_L_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTB4_L_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTB4_L_RESERVED_BITWIDTH      24
// GDCCCLUTB4_U Register
#define LCDC_GDCCCLUTB4_U_OFS                    0x00000C24
// CLUTB9 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB4_U_CLUTB9_MASK            0xFF
#define LCDC_GDCCCLUTB4_U_CLUTB9_SHIFT           0 
#define LCDC_GDCCCLUTB4_U_CLUTB9_BIT             0xFF
#define LCDC_GDCCCLUTB4_U_CLUTB9_BITWIDTH        8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB4_U_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTB4_U_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTB4_U_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTB4_U_RESERVED_BITWIDTH      24
// GDCCCLUTB5_L Register
#define LCDC_GDCCCLUTB5_L_OFS                    0x00000C28
// CLUTB10 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB5_L_CLUTB10_MASK           0xFF
#define LCDC_GDCCCLUTB5_L_CLUTB10_SHIFT          0 
#define LCDC_GDCCCLUTB5_L_CLUTB10_BIT            0xFF
#define LCDC_GDCCCLUTB5_L_CLUTB10_BITWIDTH       8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB5_L_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTB5_L_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTB5_L_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTB5_L_RESERVED_BITWIDTH      24
// GDCCCLUTB5_U Register
#define LCDC_GDCCCLUTB5_U_OFS                    0x00000C2C
// CLUTB11 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB5_U_CLUTB11_MASK           0xFF
#define LCDC_GDCCCLUTB5_U_CLUTB11_SHIFT          0 
#define LCDC_GDCCCLUTB5_U_CLUTB11_BIT            0xFF
#define LCDC_GDCCCLUTB5_U_CLUTB11_BITWIDTH       8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB5_U_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTB5_U_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTB5_U_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTB5_U_RESERVED_BITWIDTH      24
// GDCCCLUTB6_L Register
#define LCDC_GDCCCLUTB6_L_OFS                    0x00000C30
// CLUTB12 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB6_L_CLUTB12_MASK           0xFF
#define LCDC_GDCCCLUTB6_L_CLUTB12_SHIFT          0 
#define LCDC_GDCCCLUTB6_L_CLUTB12_BIT            0xFF
#define LCDC_GDCCCLUTB6_L_CLUTB12_BITWIDTH       8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB6_L_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTB6_L_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTB6_L_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTB6_L_RESERVED_BITWIDTH      24
// GDCCCLUTB6_U Register
#define LCDC_GDCCCLUTB6_U_OFS                    0x00000C34
// CLUTB13 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB6_U_CLUTB13_MASK           0xFF
#define LCDC_GDCCCLUTB6_U_CLUTB13_SHIFT          0 
#define LCDC_GDCCCLUTB6_U_CLUTB13_BIT            0xFF
#define LCDC_GDCCCLUTB6_U_CLUTB13_BITWIDTH       8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB6_U_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTB6_U_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTB6_U_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTB6_U_RESERVED_BITWIDTH      24
// GDCCCLUTB7_L Register
#define LCDC_GDCCCLUTB7_L_OFS                    0x00000C38
// CLUTB14 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB7_L_CLUTB14_MASK           0xFF
#define LCDC_GDCCCLUTB7_L_CLUTB14_SHIFT          0 
#define LCDC_GDCCCLUTB7_L_CLUTB14_BIT            0xFF
#define LCDC_GDCCCLUTB7_L_CLUTB14_BITWIDTH       8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB7_L_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTB7_L_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTB7_L_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTB7_L_RESERVED_BITWIDTH      24
// GDCCCLUTB7_U Register
#define LCDC_GDCCCLUTB7_U_OFS                    0x00000C3C
// CLUTB15 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB7_U_CLUTB15_MASK           0xFF
#define LCDC_GDCCCLUTB7_U_CLUTB15_SHIFT          0 
#define LCDC_GDCCCLUTB7_U_CLUTB15_BIT            0xFF
#define LCDC_GDCCCLUTB7_U_CLUTB15_BITWIDTH       8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB7_U_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTB7_U_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTB7_U_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTB7_U_RESERVED_BITWIDTH      24
// GDCCCLUTB8_L Register
#define LCDC_GDCCCLUTB8_L_OFS                    0x00000C40
// CLUTB16 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB8_L_CLUTB16_MASK           0xFF
#define LCDC_GDCCCLUTB8_L_CLUTB16_SHIFT          0 
#define LCDC_GDCCCLUTB8_L_CLUTB16_BIT            0xFF
#define LCDC_GDCCCLUTB8_L_CLUTB16_BITWIDTH       8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB8_L_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTB8_L_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTB8_L_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTB8_L_RESERVED_BITWIDTH      24
// GDCCCLUTB8_U Register
#define LCDC_GDCCCLUTB8_U_OFS                    0x00000C44
// CLUTB17 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB8_U_CLUTB17_MASK           0xFF
#define LCDC_GDCCCLUTB8_U_CLUTB17_SHIFT          0 
#define LCDC_GDCCCLUTB8_U_CLUTB17_BIT            0xFF
#define LCDC_GDCCCLUTB8_U_CLUTB17_BITWIDTH       8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB8_U_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTB8_U_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTB8_U_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTB8_U_RESERVED_BITWIDTH      24
// GDCCCLUTB9_L Register
#define LCDC_GDCCCLUTB9_L_OFS                    0x00000C48
// CLUTB18 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB9_L_CLUTB18_MASK           0xFF
#define LCDC_GDCCCLUTB9_L_CLUTB18_SHIFT          0 
#define LCDC_GDCCCLUTB9_L_CLUTB18_BIT            0xFF
#define LCDC_GDCCCLUTB9_L_CLUTB18_BITWIDTH       8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB9_L_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTB9_L_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTB9_L_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTB9_L_RESERVED_BITWIDTH      24
// GDCCCLUTB9_U Register
#define LCDC_GDCCCLUTB9_U_OFS                    0x00000C4C
// CLUTB19 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB9_U_CLUTB19_MASK           0xFF
#define LCDC_GDCCCLUTB9_U_CLUTB19_SHIFT          0 
#define LCDC_GDCCCLUTB9_U_CLUTB19_BIT            0xFF
#define LCDC_GDCCCLUTB9_U_CLUTB19_BITWIDTH       8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB9_U_RESERVED_MASK          0xFFFFFF00
#define LCDC_GDCCCLUTB9_U_RESERVED_SHIFT         8 
#define LCDC_GDCCCLUTB9_U_RESERVED_BIT           0xFFFFFF
#define LCDC_GDCCCLUTB9_U_RESERVED_BITWIDTH      24
// GDCCCLUTB10_L Register
#define LCDC_GDCCCLUTB10_L_OFS                   0x00000C50
// CLUTB20 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB10_L_CLUTB20_MASK          0xFF
#define LCDC_GDCCCLUTB10_L_CLUTB20_SHIFT         0 
#define LCDC_GDCCCLUTB10_L_CLUTB20_BIT           0xFF
#define LCDC_GDCCCLUTB10_L_CLUTB20_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB10_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB10_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB10_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB10_L_RESERVED_BITWIDTH     24
// GDCCCLUTB10_U Register
#define LCDC_GDCCCLUTB10_U_OFS                   0x00000C54
// CLUTB21 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB10_U_CLUTB21_MASK          0xFF
#define LCDC_GDCCCLUTB10_U_CLUTB21_SHIFT         0 
#define LCDC_GDCCCLUTB10_U_CLUTB21_BIT           0xFF
#define LCDC_GDCCCLUTB10_U_CLUTB21_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB10_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB10_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB10_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB10_U_RESERVED_BITWIDTH     24
// GDCCCLUTB11_L Register
#define LCDC_GDCCCLUTB11_L_OFS                   0x00000C58
// CLUTB22 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB11_L_CLUTB22_MASK          0xFF
#define LCDC_GDCCCLUTB11_L_CLUTB22_SHIFT         0 
#define LCDC_GDCCCLUTB11_L_CLUTB22_BIT           0xFF
#define LCDC_GDCCCLUTB11_L_CLUTB22_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB11_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB11_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB11_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB11_L_RESERVED_BITWIDTH     24
// GDCCCLUTB11_U Register
#define LCDC_GDCCCLUTB11_U_OFS                   0x00000C5C
// CLUTB23 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB11_U_CLUTB23_MASK          0xFF
#define LCDC_GDCCCLUTB11_U_CLUTB23_SHIFT         0 
#define LCDC_GDCCCLUTB11_U_CLUTB23_BIT           0xFF
#define LCDC_GDCCCLUTB11_U_CLUTB23_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB11_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB11_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB11_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB11_U_RESERVED_BITWIDTH     24
// GDCCCLUTB12_L Register
#define LCDC_GDCCCLUTB12_L_OFS                   0x00000C60
// CLUTB24 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB12_L_CLUTB24_MASK          0xFF
#define LCDC_GDCCCLUTB12_L_CLUTB24_SHIFT         0 
#define LCDC_GDCCCLUTB12_L_CLUTB24_BIT           0xFF
#define LCDC_GDCCCLUTB12_L_CLUTB24_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB12_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB12_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB12_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB12_L_RESERVED_BITWIDTH     24
// GDCCCLUTB12_U Register
#define LCDC_GDCCCLUTB12_U_OFS                   0x00000C64
// CLUTB25 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB12_U_CLUTB25_MASK          0xFF
#define LCDC_GDCCCLUTB12_U_CLUTB25_SHIFT         0 
#define LCDC_GDCCCLUTB12_U_CLUTB25_BIT           0xFF
#define LCDC_GDCCCLUTB12_U_CLUTB25_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB12_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB12_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB12_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB12_U_RESERVED_BITWIDTH     24
// GDCCCLUTB13_L Register
#define LCDC_GDCCCLUTB13_L_OFS                   0x00000C68
// CLUTB26 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB13_L_CLUTB26_MASK          0xFF
#define LCDC_GDCCCLUTB13_L_CLUTB26_SHIFT         0 
#define LCDC_GDCCCLUTB13_L_CLUTB26_BIT           0xFF
#define LCDC_GDCCCLUTB13_L_CLUTB26_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB13_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB13_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB13_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB13_L_RESERVED_BITWIDTH     24
// GDCCCLUTB13_U Register
#define LCDC_GDCCCLUTB13_U_OFS                   0x00000C6C
// CLUTB27 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB13_U_CLUTB27_MASK          0xFF
#define LCDC_GDCCCLUTB13_U_CLUTB27_SHIFT         0 
#define LCDC_GDCCCLUTB13_U_CLUTB27_BIT           0xFF
#define LCDC_GDCCCLUTB13_U_CLUTB27_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB13_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB13_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB13_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB13_U_RESERVED_BITWIDTH     24
// GDCCCLUTB14_L Register
#define LCDC_GDCCCLUTB14_L_OFS                   0x00000C70
// CLUTB28 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB14_L_CLUTB28_MASK          0xFF
#define LCDC_GDCCCLUTB14_L_CLUTB28_SHIFT         0 
#define LCDC_GDCCCLUTB14_L_CLUTB28_BIT           0xFF
#define LCDC_GDCCCLUTB14_L_CLUTB28_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB14_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB14_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB14_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB14_L_RESERVED_BITWIDTH     24
// GDCCCLUTB14_U Register
#define LCDC_GDCCCLUTB14_U_OFS                   0x00000C74
// CLUTB29 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB14_U_CLUTB29_MASK          0xFF
#define LCDC_GDCCCLUTB14_U_CLUTB29_SHIFT         0 
#define LCDC_GDCCCLUTB14_U_CLUTB29_BIT           0xFF
#define LCDC_GDCCCLUTB14_U_CLUTB29_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB14_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB14_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB14_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB14_U_RESERVED_BITWIDTH     24
// GDCCCLUTB15_L Register
#define LCDC_GDCCCLUTB15_L_OFS                   0x00000C78
// CLUTB30 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB15_L_CLUTB30_MASK          0xFF
#define LCDC_GDCCCLUTB15_L_CLUTB30_SHIFT         0 
#define LCDC_GDCCCLUTB15_L_CLUTB30_BIT           0xFF
#define LCDC_GDCCCLUTB15_L_CLUTB30_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB15_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB15_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB15_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB15_L_RESERVED_BITWIDTH     24
// GDCCCLUTB15_U Register
#define LCDC_GDCCCLUTB15_U_OFS                   0x00000C7C
// CLUTB31 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB15_U_CLUTB31_MASK          0xFF
#define LCDC_GDCCCLUTB15_U_CLUTB31_SHIFT         0 
#define LCDC_GDCCCLUTB15_U_CLUTB31_BIT           0xFF
#define LCDC_GDCCCLUTB15_U_CLUTB31_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB15_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB15_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB15_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB15_U_RESERVED_BITWIDTH     24
// GDCCCLUTB16_L Register
#define LCDC_GDCCCLUTB16_L_OFS                   0x00000C80
// CLUTB32 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB16_L_CLUTB32_MASK          0xFF
#define LCDC_GDCCCLUTB16_L_CLUTB32_SHIFT         0 
#define LCDC_GDCCCLUTB16_L_CLUTB32_BIT           0xFF
#define LCDC_GDCCCLUTB16_L_CLUTB32_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB16_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB16_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB16_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB16_L_RESERVED_BITWIDTH     24
// GDCCCLUTB16_U Register
#define LCDC_GDCCCLUTB16_U_OFS                   0x00000C84
// CLUTB33 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB16_U_CLUTB33_MASK          0xFF
#define LCDC_GDCCCLUTB16_U_CLUTB33_SHIFT         0 
#define LCDC_GDCCCLUTB16_U_CLUTB33_BIT           0xFF
#define LCDC_GDCCCLUTB16_U_CLUTB33_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB16_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB16_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB16_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB16_U_RESERVED_BITWIDTH     24
// GDCCCLUTB17_L Register
#define LCDC_GDCCCLUTB17_L_OFS                   0x00000C88
// CLUTB34 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB17_L_CLUTB34_MASK          0xFF
#define LCDC_GDCCCLUTB17_L_CLUTB34_SHIFT         0 
#define LCDC_GDCCCLUTB17_L_CLUTB34_BIT           0xFF
#define LCDC_GDCCCLUTB17_L_CLUTB34_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB17_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB17_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB17_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB17_L_RESERVED_BITWIDTH     24
// GDCCCLUTB17_U Register
#define LCDC_GDCCCLUTB17_U_OFS                   0x00000C8C
// CLUTB35 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB17_U_CLUTB35_MASK          0xFF
#define LCDC_GDCCCLUTB17_U_CLUTB35_SHIFT         0 
#define LCDC_GDCCCLUTB17_U_CLUTB35_BIT           0xFF
#define LCDC_GDCCCLUTB17_U_CLUTB35_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB17_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB17_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB17_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB17_U_RESERVED_BITWIDTH     24
// GDCCCLUTB18_L Register
#define LCDC_GDCCCLUTB18_L_OFS                   0x00000C90
// CLUTB36 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB18_L_CLUTB36_MASK          0xFF
#define LCDC_GDCCCLUTB18_L_CLUTB36_SHIFT         0 
#define LCDC_GDCCCLUTB18_L_CLUTB36_BIT           0xFF
#define LCDC_GDCCCLUTB18_L_CLUTB36_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB18_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB18_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB18_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB18_L_RESERVED_BITWIDTH     24
// GDCCCLUTB18_U Register
#define LCDC_GDCCCLUTB18_U_OFS                   0x00000C94
// CLUTB37 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB18_U_CLUTB37_MASK          0xFF
#define LCDC_GDCCCLUTB18_U_CLUTB37_SHIFT         0 
#define LCDC_GDCCCLUTB18_U_CLUTB37_BIT           0xFF
#define LCDC_GDCCCLUTB18_U_CLUTB37_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB18_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB18_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB18_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB18_U_RESERVED_BITWIDTH     24
// GDCCCLUTB19_L Register
#define LCDC_GDCCCLUTB19_L_OFS                   0x00000C98
// CLUTB38 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB19_L_CLUTB38_MASK          0xFF
#define LCDC_GDCCCLUTB19_L_CLUTB38_SHIFT         0 
#define LCDC_GDCCCLUTB19_L_CLUTB38_BIT           0xFF
#define LCDC_GDCCCLUTB19_L_CLUTB38_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB19_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB19_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB19_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB19_L_RESERVED_BITWIDTH     24
// GDCCCLUTB19_U Register
#define LCDC_GDCCCLUTB19_U_OFS                   0x00000C9C
// CLUTB39 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB19_U_CLUTB39_MASK          0xFF
#define LCDC_GDCCCLUTB19_U_CLUTB39_SHIFT         0 
#define LCDC_GDCCCLUTB19_U_CLUTB39_BIT           0xFF
#define LCDC_GDCCCLUTB19_U_CLUTB39_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB19_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB19_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB19_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB19_U_RESERVED_BITWIDTH     24
// GDCCCLUTB20_L Register
#define LCDC_GDCCCLUTB20_L_OFS                   0x00000CA0
// CLUTB40 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB20_L_CLUTB40_MASK          0xFF
#define LCDC_GDCCCLUTB20_L_CLUTB40_SHIFT         0 
#define LCDC_GDCCCLUTB20_L_CLUTB40_BIT           0xFF
#define LCDC_GDCCCLUTB20_L_CLUTB40_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB20_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB20_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB20_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB20_L_RESERVED_BITWIDTH     24
// GDCCCLUTB20_U Register
#define LCDC_GDCCCLUTB20_U_OFS                   0x00000CA4
// CLUTB41 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB20_U_CLUTB41_MASK          0xFF
#define LCDC_GDCCCLUTB20_U_CLUTB41_SHIFT         0 
#define LCDC_GDCCCLUTB20_U_CLUTB41_BIT           0xFF
#define LCDC_GDCCCLUTB20_U_CLUTB41_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB20_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB20_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB20_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB20_U_RESERVED_BITWIDTH     24
// GDCCCLUTB21_L Register
#define LCDC_GDCCCLUTB21_L_OFS                   0x00000CA8
// CLUTB42 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB21_L_CLUTB42_MASK          0xFF
#define LCDC_GDCCCLUTB21_L_CLUTB42_SHIFT         0 
#define LCDC_GDCCCLUTB21_L_CLUTB42_BIT           0xFF
#define LCDC_GDCCCLUTB21_L_CLUTB42_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB21_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB21_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB21_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB21_L_RESERVED_BITWIDTH     24
// GDCCCLUTB21_U Register
#define LCDC_GDCCCLUTB21_U_OFS                   0x00000CAC
// CLUTB43 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB21_U_CLUTB43_MASK          0xFF
#define LCDC_GDCCCLUTB21_U_CLUTB43_SHIFT         0 
#define LCDC_GDCCCLUTB21_U_CLUTB43_BIT           0xFF
#define LCDC_GDCCCLUTB21_U_CLUTB43_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB21_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB21_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB21_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB21_U_RESERVED_BITWIDTH     24
// GDCCCLUTB22_L Register
#define LCDC_GDCCCLUTB22_L_OFS                   0x00000CB0
// CLUTB44 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB22_L_CLUTB44_MASK          0xFF
#define LCDC_GDCCCLUTB22_L_CLUTB44_SHIFT         0 
#define LCDC_GDCCCLUTB22_L_CLUTB44_BIT           0xFF
#define LCDC_GDCCCLUTB22_L_CLUTB44_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB22_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB22_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB22_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB22_L_RESERVED_BITWIDTH     24
// GDCCCLUTB22_U Register
#define LCDC_GDCCCLUTB22_U_OFS                   0x00000CB4
// CLUTB45 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB22_U_CLUTB45_MASK          0xFF
#define LCDC_GDCCCLUTB22_U_CLUTB45_SHIFT         0 
#define LCDC_GDCCCLUTB22_U_CLUTB45_BIT           0xFF
#define LCDC_GDCCCLUTB22_U_CLUTB45_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB22_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB22_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB22_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB22_U_RESERVED_BITWIDTH     24
// GDCCCLUTB23_L Register
#define LCDC_GDCCCLUTB23_L_OFS                   0x00000CB8
// CLUTB46 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB23_L_CLUTB46_MASK          0xFF
#define LCDC_GDCCCLUTB23_L_CLUTB46_SHIFT         0 
#define LCDC_GDCCCLUTB23_L_CLUTB46_BIT           0xFF
#define LCDC_GDCCCLUTB23_L_CLUTB46_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB23_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB23_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB23_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB23_L_RESERVED_BITWIDTH     24
// GDCCCLUTB23_U Register
#define LCDC_GDCCCLUTB23_U_OFS                   0x00000CBC
// CLUTB47 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB23_U_CLUTB47_MASK          0xFF
#define LCDC_GDCCCLUTB23_U_CLUTB47_SHIFT         0 
#define LCDC_GDCCCLUTB23_U_CLUTB47_BIT           0xFF
#define LCDC_GDCCCLUTB23_U_CLUTB47_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB23_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB23_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB23_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB23_U_RESERVED_BITWIDTH     24
// GDCCCLUTB24_L Register
#define LCDC_GDCCCLUTB24_L_OFS                   0x00000CC0
// CLUTB48 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB24_L_CLUTB48_MASK          0xFF
#define LCDC_GDCCCLUTB24_L_CLUTB48_SHIFT         0 
#define LCDC_GDCCCLUTB24_L_CLUTB48_BIT           0xFF
#define LCDC_GDCCCLUTB24_L_CLUTB48_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB24_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB24_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB24_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB24_L_RESERVED_BITWIDTH     24
// GDCCCLUTB24_U Register
#define LCDC_GDCCCLUTB24_U_OFS                   0x00000CC4
// CLUTB49 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB24_U_CLUTB49_MASK          0xFF
#define LCDC_GDCCCLUTB24_U_CLUTB49_SHIFT         0 
#define LCDC_GDCCCLUTB24_U_CLUTB49_BIT           0xFF
#define LCDC_GDCCCLUTB24_U_CLUTB49_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB24_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB24_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB24_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB24_U_RESERVED_BITWIDTH     24
// GDCCCLUTB25_L Register
#define LCDC_GDCCCLUTB25_L_OFS                   0x00000CC8
// CLUTB50 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB25_L_CLUTB50_MASK          0xFF
#define LCDC_GDCCCLUTB25_L_CLUTB50_SHIFT         0 
#define LCDC_GDCCCLUTB25_L_CLUTB50_BIT           0xFF
#define LCDC_GDCCCLUTB25_L_CLUTB50_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB25_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB25_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB25_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB25_L_RESERVED_BITWIDTH     24
// GDCCCLUTB25_U Register
#define LCDC_GDCCCLUTB25_U_OFS                   0x00000CCC
// CLUTB51 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB25_U_CLUTB51_MASK          0xFF
#define LCDC_GDCCCLUTB25_U_CLUTB51_SHIFT         0 
#define LCDC_GDCCCLUTB25_U_CLUTB51_BIT           0xFF
#define LCDC_GDCCCLUTB25_U_CLUTB51_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB25_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB25_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB25_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB25_U_RESERVED_BITWIDTH     24
// GDCCCLUTB26_L Register
#define LCDC_GDCCCLUTB26_L_OFS                   0x00000CD0
// CLUTB52 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB26_L_CLUTB52_MASK          0xFF
#define LCDC_GDCCCLUTB26_L_CLUTB52_SHIFT         0 
#define LCDC_GDCCCLUTB26_L_CLUTB52_BIT           0xFF
#define LCDC_GDCCCLUTB26_L_CLUTB52_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB26_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB26_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB26_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB26_L_RESERVED_BITWIDTH     24
// GDCCCLUTB26_U Register
#define LCDC_GDCCCLUTB26_U_OFS                   0x00000CD4
// CLUTB53 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB26_U_CLUTB53_MASK          0xFF
#define LCDC_GDCCCLUTB26_U_CLUTB53_SHIFT         0 
#define LCDC_GDCCCLUTB26_U_CLUTB53_BIT           0xFF
#define LCDC_GDCCCLUTB26_U_CLUTB53_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB26_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB26_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB26_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB26_U_RESERVED_BITWIDTH     24
// GDCCCLUTB27_L Register
#define LCDC_GDCCCLUTB27_L_OFS                   0x00000CD8
// CLUTB54 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB27_L_CLUTB54_MASK          0xFF
#define LCDC_GDCCCLUTB27_L_CLUTB54_SHIFT         0 
#define LCDC_GDCCCLUTB27_L_CLUTB54_BIT           0xFF
#define LCDC_GDCCCLUTB27_L_CLUTB54_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB27_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB27_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB27_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB27_L_RESERVED_BITWIDTH     24
// GDCCCLUTB27_U Register
#define LCDC_GDCCCLUTB27_U_OFS                   0x00000CDC
// CLUTB55 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB27_U_CLUTB55_MASK          0xFF
#define LCDC_GDCCCLUTB27_U_CLUTB55_SHIFT         0 
#define LCDC_GDCCCLUTB27_U_CLUTB55_BIT           0xFF
#define LCDC_GDCCCLUTB27_U_CLUTB55_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB27_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB27_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB27_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB27_U_RESERVED_BITWIDTH     24
// GDCCCLUTB28_L Register
#define LCDC_GDCCCLUTB28_L_OFS                   0x00000CE0
// CLUTB56 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB28_L_CLUTB56_MASK          0xFF
#define LCDC_GDCCCLUTB28_L_CLUTB56_SHIFT         0 
#define LCDC_GDCCCLUTB28_L_CLUTB56_BIT           0xFF
#define LCDC_GDCCCLUTB28_L_CLUTB56_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB28_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB28_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB28_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB28_L_RESERVED_BITWIDTH     24
// GDCCCLUTB28_U Register
#define LCDC_GDCCCLUTB28_U_OFS                   0x00000CE4
// CLUTB57 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB28_U_CLUTB57_MASK          0xFF
#define LCDC_GDCCCLUTB28_U_CLUTB57_SHIFT         0 
#define LCDC_GDCCCLUTB28_U_CLUTB57_BIT           0xFF
#define LCDC_GDCCCLUTB28_U_CLUTB57_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB28_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB28_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB28_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB28_U_RESERVED_BITWIDTH     24
// GDCCCLUTB29_L Register
#define LCDC_GDCCCLUTB29_L_OFS                   0x00000CE8
// CLUTB58 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB29_L_CLUTB58_MASK          0xFF
#define LCDC_GDCCCLUTB29_L_CLUTB58_SHIFT         0 
#define LCDC_GDCCCLUTB29_L_CLUTB58_BIT           0xFF
#define LCDC_GDCCCLUTB29_L_CLUTB58_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB29_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB29_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB29_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB29_L_RESERVED_BITWIDTH     24
// GDCCCLUTB29_U Register
#define LCDC_GDCCCLUTB29_U_OFS                   0x00000CEC
// CLUTB59 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB29_U_CLUTB59_MASK          0xFF
#define LCDC_GDCCCLUTB29_U_CLUTB59_SHIFT         0 
#define LCDC_GDCCCLUTB29_U_CLUTB59_BIT           0xFF
#define LCDC_GDCCCLUTB29_U_CLUTB59_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB29_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB29_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB29_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB29_U_RESERVED_BITWIDTH     24
// GDCCCLUTB30_L Register
#define LCDC_GDCCCLUTB30_L_OFS                   0x00000CF0
// CLUTB60 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB30_L_CLUTB60_MASK          0xFF
#define LCDC_GDCCCLUTB30_L_CLUTB60_SHIFT         0 
#define LCDC_GDCCCLUTB30_L_CLUTB60_BIT           0xFF
#define LCDC_GDCCCLUTB30_L_CLUTB60_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB30_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB30_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB30_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB30_L_RESERVED_BITWIDTH     24
// GDCCCLUTB30_U Register
#define LCDC_GDCCCLUTB30_U_OFS                   0x00000CF4
// CLUTB61 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB30_U_CLUTB61_MASK          0xFF
#define LCDC_GDCCCLUTB30_U_CLUTB61_SHIFT         0 
#define LCDC_GDCCCLUTB30_U_CLUTB61_BIT           0xFF
#define LCDC_GDCCCLUTB30_U_CLUTB61_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB30_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB30_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB30_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB30_U_RESERVED_BITWIDTH     24
// GDCCCLUTB31_L Register
#define LCDC_GDCCCLUTB31_L_OFS                   0x00000CF8
// CLUTB62 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB31_L_CLUTB62_MASK          0xFF
#define LCDC_GDCCCLUTB31_L_CLUTB62_SHIFT         0 
#define LCDC_GDCCCLUTB31_L_CLUTB62_BIT           0xFF
#define LCDC_GDCCCLUTB31_L_CLUTB62_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB31_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB31_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB31_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB31_L_RESERVED_BITWIDTH     24
// GDCCCLUTB31_U Register
#define LCDC_GDCCCLUTB31_U_OFS                   0x00000CFC
// CLUTB63 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB31_U_CLUTB63_MASK          0xFF
#define LCDC_GDCCCLUTB31_U_CLUTB63_SHIFT         0 
#define LCDC_GDCCCLUTB31_U_CLUTB63_BIT           0xFF
#define LCDC_GDCCCLUTB31_U_CLUTB63_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB31_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB31_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB31_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB31_U_RESERVED_BITWIDTH     24
// GDCCCLUTB32_L Register
#define LCDC_GDCCCLUTB32_L_OFS                   0x00000D00
// CLUTB64 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB32_L_CLUTB64_MASK          0xFF
#define LCDC_GDCCCLUTB32_L_CLUTB64_SHIFT         0 
#define LCDC_GDCCCLUTB32_L_CLUTB64_BIT           0xFF
#define LCDC_GDCCCLUTB32_L_CLUTB64_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB32_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB32_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB32_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB32_L_RESERVED_BITWIDTH     24
// GDCCCLUTB32_U Register
#define LCDC_GDCCCLUTB32_U_OFS                   0x00000D04
// CLUTB65 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB32_U_CLUTB65_MASK          0xFF
#define LCDC_GDCCCLUTB32_U_CLUTB65_SHIFT         0 
#define LCDC_GDCCCLUTB32_U_CLUTB65_BIT           0xFF
#define LCDC_GDCCCLUTB32_U_CLUTB65_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB32_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB32_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB32_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB32_U_RESERVED_BITWIDTH     24
// GDCCCLUTB33_L Register
#define LCDC_GDCCCLUTB33_L_OFS                   0x00000D08
// CLUTB66 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB33_L_CLUTB66_MASK          0xFF
#define LCDC_GDCCCLUTB33_L_CLUTB66_SHIFT         0 
#define LCDC_GDCCCLUTB33_L_CLUTB66_BIT           0xFF
#define LCDC_GDCCCLUTB33_L_CLUTB66_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB33_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB33_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB33_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB33_L_RESERVED_BITWIDTH     24
// GDCCCLUTB33_U Register
#define LCDC_GDCCCLUTB33_U_OFS                   0x00000D0C
// CLUTB67 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB33_U_CLUTB67_MASK          0xFF
#define LCDC_GDCCCLUTB33_U_CLUTB67_SHIFT         0 
#define LCDC_GDCCCLUTB33_U_CLUTB67_BIT           0xFF
#define LCDC_GDCCCLUTB33_U_CLUTB67_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB33_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB33_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB33_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB33_U_RESERVED_BITWIDTH     24
// GDCCCLUTB34_L Register
#define LCDC_GDCCCLUTB34_L_OFS                   0x00000D10
// CLUTB68 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB34_L_CLUTB68_MASK          0xFF
#define LCDC_GDCCCLUTB34_L_CLUTB68_SHIFT         0 
#define LCDC_GDCCCLUTB34_L_CLUTB68_BIT           0xFF
#define LCDC_GDCCCLUTB34_L_CLUTB68_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB34_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB34_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB34_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB34_L_RESERVED_BITWIDTH     24
// GDCCCLUTB34_U Register
#define LCDC_GDCCCLUTB34_U_OFS                   0x00000D14
// CLUTB69 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB34_U_CLUTB69_MASK          0xFF
#define LCDC_GDCCCLUTB34_U_CLUTB69_SHIFT         0 
#define LCDC_GDCCCLUTB34_U_CLUTB69_BIT           0xFF
#define LCDC_GDCCCLUTB34_U_CLUTB69_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB34_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB34_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB34_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB34_U_RESERVED_BITWIDTH     24
// GDCCCLUTB35_L Register
#define LCDC_GDCCCLUTB35_L_OFS                   0x00000D18
// CLUTB70 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB35_L_CLUTB70_MASK          0xFF
#define LCDC_GDCCCLUTB35_L_CLUTB70_SHIFT         0 
#define LCDC_GDCCCLUTB35_L_CLUTB70_BIT           0xFF
#define LCDC_GDCCCLUTB35_L_CLUTB70_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB35_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB35_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB35_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB35_L_RESERVED_BITWIDTH     24
// GDCCCLUTB35_U Register
#define LCDC_GDCCCLUTB35_U_OFS                   0x00000D1C
// CLUTB71 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB35_U_CLUTB71_MASK          0xFF
#define LCDC_GDCCCLUTB35_U_CLUTB71_SHIFT         0 
#define LCDC_GDCCCLUTB35_U_CLUTB71_BIT           0xFF
#define LCDC_GDCCCLUTB35_U_CLUTB71_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB35_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB35_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB35_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB35_U_RESERVED_BITWIDTH     24
// GDCCCLUTB36_L Register
#define LCDC_GDCCCLUTB36_L_OFS                   0x00000D20
// CLUTB72 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB36_L_CLUTB72_MASK          0xFF
#define LCDC_GDCCCLUTB36_L_CLUTB72_SHIFT         0 
#define LCDC_GDCCCLUTB36_L_CLUTB72_BIT           0xFF
#define LCDC_GDCCCLUTB36_L_CLUTB72_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB36_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB36_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB36_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB36_L_RESERVED_BITWIDTH     24
// GDCCCLUTB36_U Register
#define LCDC_GDCCCLUTB36_U_OFS                   0x00000D24
// CLUTB73 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB36_U_CLUTB73_MASK          0xFF
#define LCDC_GDCCCLUTB36_U_CLUTB73_SHIFT         0 
#define LCDC_GDCCCLUTB36_U_CLUTB73_BIT           0xFF
#define LCDC_GDCCCLUTB36_U_CLUTB73_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB36_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB36_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB36_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB36_U_RESERVED_BITWIDTH     24
// GDCCCLUTB37_L Register
#define LCDC_GDCCCLUTB37_L_OFS                   0x00000D28
// CLUTB74 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB37_L_CLUTB74_MASK          0xFF
#define LCDC_GDCCCLUTB37_L_CLUTB74_SHIFT         0 
#define LCDC_GDCCCLUTB37_L_CLUTB74_BIT           0xFF
#define LCDC_GDCCCLUTB37_L_CLUTB74_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB37_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB37_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB37_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB37_L_RESERVED_BITWIDTH     24
// GDCCCLUTB37_U Register
#define LCDC_GDCCCLUTB37_U_OFS                   0x00000D2C
// CLUTB75 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB37_U_CLUTB75_MASK          0xFF
#define LCDC_GDCCCLUTB37_U_CLUTB75_SHIFT         0 
#define LCDC_GDCCCLUTB37_U_CLUTB75_BIT           0xFF
#define LCDC_GDCCCLUTB37_U_CLUTB75_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB37_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB37_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB37_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB37_U_RESERVED_BITWIDTH     24
// GDCCCLUTB38_L Register
#define LCDC_GDCCCLUTB38_L_OFS                   0x00000D30
// CLUTB76 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB38_L_CLUTB76_MASK          0xFF
#define LCDC_GDCCCLUTB38_L_CLUTB76_SHIFT         0 
#define LCDC_GDCCCLUTB38_L_CLUTB76_BIT           0xFF
#define LCDC_GDCCCLUTB38_L_CLUTB76_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB38_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB38_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB38_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB38_L_RESERVED_BITWIDTH     24
// GDCCCLUTB38_U Register
#define LCDC_GDCCCLUTB38_U_OFS                   0x00000D34
// CLUTB77 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB38_U_CLUTB77_MASK          0xFF
#define LCDC_GDCCCLUTB38_U_CLUTB77_SHIFT         0 
#define LCDC_GDCCCLUTB38_U_CLUTB77_BIT           0xFF
#define LCDC_GDCCCLUTB38_U_CLUTB77_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB38_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB38_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB38_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB38_U_RESERVED_BITWIDTH     24
// GDCCCLUTB39_L Register
#define LCDC_GDCCCLUTB39_L_OFS                   0x00000D38
// CLUTB78 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB39_L_CLUTB78_MASK          0xFF
#define LCDC_GDCCCLUTB39_L_CLUTB78_SHIFT         0 
#define LCDC_GDCCCLUTB39_L_CLUTB78_BIT           0xFF
#define LCDC_GDCCCLUTB39_L_CLUTB78_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB39_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB39_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB39_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB39_L_RESERVED_BITWIDTH     24
// GDCCCLUTB39_U Register
#define LCDC_GDCCCLUTB39_U_OFS                   0x00000D3C
// CLUTB79 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB39_U_CLUTB79_MASK          0xFF
#define LCDC_GDCCCLUTB39_U_CLUTB79_SHIFT         0 
#define LCDC_GDCCCLUTB39_U_CLUTB79_BIT           0xFF
#define LCDC_GDCCCLUTB39_U_CLUTB79_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB39_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB39_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB39_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB39_U_RESERVED_BITWIDTH     24
// GDCCCLUTB40_L Register
#define LCDC_GDCCCLUTB40_L_OFS                   0x00000D40
// CLUTB80 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB40_L_CLUTB80_MASK          0xFF
#define LCDC_GDCCCLUTB40_L_CLUTB80_SHIFT         0 
#define LCDC_GDCCCLUTB40_L_CLUTB80_BIT           0xFF
#define LCDC_GDCCCLUTB40_L_CLUTB80_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB40_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB40_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB40_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB40_L_RESERVED_BITWIDTH     24
// GDCCCLUTB40_U Register
#define LCDC_GDCCCLUTB40_U_OFS                   0x00000D44
// CLUTB81 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB40_U_CLUTB81_MASK          0xFF
#define LCDC_GDCCCLUTB40_U_CLUTB81_SHIFT         0 
#define LCDC_GDCCCLUTB40_U_CLUTB81_BIT           0xFF
#define LCDC_GDCCCLUTB40_U_CLUTB81_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB40_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB40_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB40_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB40_U_RESERVED_BITWIDTH     24
// GDCCCLUTB41_L Register
#define LCDC_GDCCCLUTB41_L_OFS                   0x00000D48
// CLUTB82 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB41_L_CLUTB82_MASK          0xFF
#define LCDC_GDCCCLUTB41_L_CLUTB82_SHIFT         0 
#define LCDC_GDCCCLUTB41_L_CLUTB82_BIT           0xFF
#define LCDC_GDCCCLUTB41_L_CLUTB82_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB41_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB41_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB41_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB41_L_RESERVED_BITWIDTH     24
// GDCCCLUTB41_U Register
#define LCDC_GDCCCLUTB41_U_OFS                   0x00000D4C
// CLUTB83 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB41_U_CLUTB83_MASK          0xFF
#define LCDC_GDCCCLUTB41_U_CLUTB83_SHIFT         0 
#define LCDC_GDCCCLUTB41_U_CLUTB83_BIT           0xFF
#define LCDC_GDCCCLUTB41_U_CLUTB83_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB41_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB41_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB41_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB41_U_RESERVED_BITWIDTH     24
// GDCCCLUTB42_L Register
#define LCDC_GDCCCLUTB42_L_OFS                   0x00000D50
// CLUTB84 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB42_L_CLUTB84_MASK          0xFF
#define LCDC_GDCCCLUTB42_L_CLUTB84_SHIFT         0 
#define LCDC_GDCCCLUTB42_L_CLUTB84_BIT           0xFF
#define LCDC_GDCCCLUTB42_L_CLUTB84_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB42_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB42_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB42_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB42_L_RESERVED_BITWIDTH     24
// GDCCCLUTB42_U Register
#define LCDC_GDCCCLUTB42_U_OFS                   0x00000D54
// CLUTB85 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB42_U_CLUTB85_MASK          0xFF
#define LCDC_GDCCCLUTB42_U_CLUTB85_SHIFT         0 
#define LCDC_GDCCCLUTB42_U_CLUTB85_BIT           0xFF
#define LCDC_GDCCCLUTB42_U_CLUTB85_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB42_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB42_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB42_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB42_U_RESERVED_BITWIDTH     24
// GDCCCLUTB43_L Register
#define LCDC_GDCCCLUTB43_L_OFS                   0x00000D58
// CLUTB86 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB43_L_CLUTB86_MASK          0xFF
#define LCDC_GDCCCLUTB43_L_CLUTB86_SHIFT         0 
#define LCDC_GDCCCLUTB43_L_CLUTB86_BIT           0xFF
#define LCDC_GDCCCLUTB43_L_CLUTB86_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB43_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB43_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB43_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB43_L_RESERVED_BITWIDTH     24
// GDCCCLUTB43_U Register
#define LCDC_GDCCCLUTB43_U_OFS                   0x00000D5C
// CLUTB87 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB43_U_CLUTB87_MASK          0xFF
#define LCDC_GDCCCLUTB43_U_CLUTB87_SHIFT         0 
#define LCDC_GDCCCLUTB43_U_CLUTB87_BIT           0xFF
#define LCDC_GDCCCLUTB43_U_CLUTB87_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB43_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB43_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB43_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB43_U_RESERVED_BITWIDTH     24
// GDCCCLUTB44_L Register
#define LCDC_GDCCCLUTB44_L_OFS                   0x00000D60
// CLUTB88 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB44_L_CLUTB88_MASK          0xFF
#define LCDC_GDCCCLUTB44_L_CLUTB88_SHIFT         0 
#define LCDC_GDCCCLUTB44_L_CLUTB88_BIT           0xFF
#define LCDC_GDCCCLUTB44_L_CLUTB88_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB44_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB44_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB44_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB44_L_RESERVED_BITWIDTH     24
// GDCCCLUTB44_U Register
#define LCDC_GDCCCLUTB44_U_OFS                   0x00000D64
// CLUTB89 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB44_U_CLUTB89_MASK          0xFF
#define LCDC_GDCCCLUTB44_U_CLUTB89_SHIFT         0 
#define LCDC_GDCCCLUTB44_U_CLUTB89_BIT           0xFF
#define LCDC_GDCCCLUTB44_U_CLUTB89_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB44_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB44_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB44_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB44_U_RESERVED_BITWIDTH     24
// GDCCCLUTB45_L Register
#define LCDC_GDCCCLUTB45_L_OFS                   0x00000D68
// CLUTB90 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB45_L_CLUTB90_MASK          0xFF
#define LCDC_GDCCCLUTB45_L_CLUTB90_SHIFT         0 
#define LCDC_GDCCCLUTB45_L_CLUTB90_BIT           0xFF
#define LCDC_GDCCCLUTB45_L_CLUTB90_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB45_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB45_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB45_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB45_L_RESERVED_BITWIDTH     24
// GDCCCLUTB45_U Register
#define LCDC_GDCCCLUTB45_U_OFS                   0x00000D6C
// CLUTB91 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB45_U_CLUTB91_MASK          0xFF
#define LCDC_GDCCCLUTB45_U_CLUTB91_SHIFT         0 
#define LCDC_GDCCCLUTB45_U_CLUTB91_BIT           0xFF
#define LCDC_GDCCCLUTB45_U_CLUTB91_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB45_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB45_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB45_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB45_U_RESERVED_BITWIDTH     24
// GDCCCLUTB46_L Register
#define LCDC_GDCCCLUTB46_L_OFS                   0x00000D70
// CLUTB92 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB46_L_CLUTB92_MASK          0xFF
#define LCDC_GDCCCLUTB46_L_CLUTB92_SHIFT         0 
#define LCDC_GDCCCLUTB46_L_CLUTB92_BIT           0xFF
#define LCDC_GDCCCLUTB46_L_CLUTB92_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB46_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB46_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB46_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB46_L_RESERVED_BITWIDTH     24
// GDCCCLUTB46_U Register
#define LCDC_GDCCCLUTB46_U_OFS                   0x00000D74
// CLUTB93 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB46_U_CLUTB93_MASK          0xFF
#define LCDC_GDCCCLUTB46_U_CLUTB93_SHIFT         0 
#define LCDC_GDCCCLUTB46_U_CLUTB93_BIT           0xFF
#define LCDC_GDCCCLUTB46_U_CLUTB93_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB46_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB46_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB46_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB46_U_RESERVED_BITWIDTH     24
// GDCCCLUTB47_L Register
#define LCDC_GDCCCLUTB47_L_OFS                   0x00000D78
// CLUTB94 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB47_L_CLUTB94_MASK          0xFF
#define LCDC_GDCCCLUTB47_L_CLUTB94_SHIFT         0 
#define LCDC_GDCCCLUTB47_L_CLUTB94_BIT           0xFF
#define LCDC_GDCCCLUTB47_L_CLUTB94_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB47_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB47_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB47_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB47_L_RESERVED_BITWIDTH     24
// GDCCCLUTB47_U Register
#define LCDC_GDCCCLUTB47_U_OFS                   0x00000D7C
// CLUTB95 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB47_U_CLUTB95_MASK          0xFF
#define LCDC_GDCCCLUTB47_U_CLUTB95_SHIFT         0 
#define LCDC_GDCCCLUTB47_U_CLUTB95_BIT           0xFF
#define LCDC_GDCCCLUTB47_U_CLUTB95_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB47_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB47_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB47_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB47_U_RESERVED_BITWIDTH     24
// GDCCCLUTB48_L Register
#define LCDC_GDCCCLUTB48_L_OFS                   0x00000D80
// CLUTB96 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB48_L_CLUTB96_MASK          0xFF
#define LCDC_GDCCCLUTB48_L_CLUTB96_SHIFT         0 
#define LCDC_GDCCCLUTB48_L_CLUTB96_BIT           0xFF
#define LCDC_GDCCCLUTB48_L_CLUTB96_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB48_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB48_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB48_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB48_L_RESERVED_BITWIDTH     24
// GDCCCLUTB48_U Register
#define LCDC_GDCCCLUTB48_U_OFS                   0x00000D84
// CLUTB97 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB48_U_CLUTB97_MASK          0xFF
#define LCDC_GDCCCLUTB48_U_CLUTB97_SHIFT         0 
#define LCDC_GDCCCLUTB48_U_CLUTB97_BIT           0xFF
#define LCDC_GDCCCLUTB48_U_CLUTB97_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB48_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB48_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB48_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB48_U_RESERVED_BITWIDTH     24
// GDCCCLUTB49_L Register
#define LCDC_GDCCCLUTB49_L_OFS                   0x00000D88
// CLUTB98 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB49_L_CLUTB98_MASK          0xFF
#define LCDC_GDCCCLUTB49_L_CLUTB98_SHIFT         0 
#define LCDC_GDCCCLUTB49_L_CLUTB98_BIT           0xFF
#define LCDC_GDCCCLUTB49_L_CLUTB98_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB49_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB49_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB49_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB49_L_RESERVED_BITWIDTH     24
// GDCCCLUTB49_U Register
#define LCDC_GDCCCLUTB49_U_OFS                   0x00000D8C
// CLUTB99 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB49_U_CLUTB99_MASK          0xFF
#define LCDC_GDCCCLUTB49_U_CLUTB99_SHIFT         0 
#define LCDC_GDCCCLUTB49_U_CLUTB99_BIT           0xFF
#define LCDC_GDCCCLUTB49_U_CLUTB99_BITWIDTH      8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB49_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB49_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB49_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB49_U_RESERVED_BITWIDTH     24
// GDCCCLUTB50_L Register
#define LCDC_GDCCCLUTB50_L_OFS                   0x00000D90
// CLUTB100 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB50_L_CLUTB100_MASK         0xFF
#define LCDC_GDCCCLUTB50_L_CLUTB100_SHIFT        0 
#define LCDC_GDCCCLUTB50_L_CLUTB100_BIT          0xFF
#define LCDC_GDCCCLUTB50_L_CLUTB100_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB50_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB50_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB50_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB50_L_RESERVED_BITWIDTH     24
// GDCCCLUTB50_U Register
#define LCDC_GDCCCLUTB50_U_OFS                   0x00000D94
// CLUTB101 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB50_U_CLUTB101_MASK         0xFF
#define LCDC_GDCCCLUTB50_U_CLUTB101_SHIFT        0 
#define LCDC_GDCCCLUTB50_U_CLUTB101_BIT          0xFF
#define LCDC_GDCCCLUTB50_U_CLUTB101_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB50_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB50_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB50_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB50_U_RESERVED_BITWIDTH     24
// GDCCCLUTB51_L Register
#define LCDC_GDCCCLUTB51_L_OFS                   0x00000D98
// CLUTB102 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB51_L_CLUTB102_MASK         0xFF
#define LCDC_GDCCCLUTB51_L_CLUTB102_SHIFT        0 
#define LCDC_GDCCCLUTB51_L_CLUTB102_BIT          0xFF
#define LCDC_GDCCCLUTB51_L_CLUTB102_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB51_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB51_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB51_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB51_L_RESERVED_BITWIDTH     24
// GDCCCLUTB51_U Register
#define LCDC_GDCCCLUTB51_U_OFS                   0x00000D9C
// CLUTB103 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB51_U_CLUTB103_MASK         0xFF
#define LCDC_GDCCCLUTB51_U_CLUTB103_SHIFT        0 
#define LCDC_GDCCCLUTB51_U_CLUTB103_BIT          0xFF
#define LCDC_GDCCCLUTB51_U_CLUTB103_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB51_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB51_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB51_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB51_U_RESERVED_BITWIDTH     24
// GDCCCLUTB52_L Register
#define LCDC_GDCCCLUTB52_L_OFS                   0x00000DA0
// CLUTB104 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB52_L_CLUTB104_MASK         0xFF
#define LCDC_GDCCCLUTB52_L_CLUTB104_SHIFT        0 
#define LCDC_GDCCCLUTB52_L_CLUTB104_BIT          0xFF
#define LCDC_GDCCCLUTB52_L_CLUTB104_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB52_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB52_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB52_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB52_L_RESERVED_BITWIDTH     24
// GDCCCLUTB52_U Register
#define LCDC_GDCCCLUTB52_U_OFS                   0x00000DA4
// CLUTB105 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB52_U_CLUTB105_MASK         0xFF
#define LCDC_GDCCCLUTB52_U_CLUTB105_SHIFT        0 
#define LCDC_GDCCCLUTB52_U_CLUTB105_BIT          0xFF
#define LCDC_GDCCCLUTB52_U_CLUTB105_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB52_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB52_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB52_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB52_U_RESERVED_BITWIDTH     24
// GDCCCLUTB53_L Register
#define LCDC_GDCCCLUTB53_L_OFS                   0x00000DA8
// CLUTB106 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB53_L_CLUTB106_MASK         0xFF
#define LCDC_GDCCCLUTB53_L_CLUTB106_SHIFT        0 
#define LCDC_GDCCCLUTB53_L_CLUTB106_BIT          0xFF
#define LCDC_GDCCCLUTB53_L_CLUTB106_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB53_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB53_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB53_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB53_L_RESERVED_BITWIDTH     24
// GDCCCLUTB53_U Register
#define LCDC_GDCCCLUTB53_U_OFS                   0x00000DAC
// CLUTB107 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB53_U_CLUTB107_MASK         0xFF
#define LCDC_GDCCCLUTB53_U_CLUTB107_SHIFT        0 
#define LCDC_GDCCCLUTB53_U_CLUTB107_BIT          0xFF
#define LCDC_GDCCCLUTB53_U_CLUTB107_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB53_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB53_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB53_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB53_U_RESERVED_BITWIDTH     24
// GDCCCLUTB54_L Register
#define LCDC_GDCCCLUTB54_L_OFS                   0x00000DB0
// CLUTB108 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB54_L_CLUTB108_MASK         0xFF
#define LCDC_GDCCCLUTB54_L_CLUTB108_SHIFT        0 
#define LCDC_GDCCCLUTB54_L_CLUTB108_BIT          0xFF
#define LCDC_GDCCCLUTB54_L_CLUTB108_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB54_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB54_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB54_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB54_L_RESERVED_BITWIDTH     24
// GDCCCLUTB54_U Register
#define LCDC_GDCCCLUTB54_U_OFS                   0x00000DB4
// CLUTB109 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB54_U_CLUTB109_MASK         0xFF
#define LCDC_GDCCCLUTB54_U_CLUTB109_SHIFT        0 
#define LCDC_GDCCCLUTB54_U_CLUTB109_BIT          0xFF
#define LCDC_GDCCCLUTB54_U_CLUTB109_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB54_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB54_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB54_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB54_U_RESERVED_BITWIDTH     24
// GDCCCLUTB55_L Register
#define LCDC_GDCCCLUTB55_L_OFS                   0x00000DB8
// CLUTB110 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB55_L_CLUTB110_MASK         0xFF
#define LCDC_GDCCCLUTB55_L_CLUTB110_SHIFT        0 
#define LCDC_GDCCCLUTB55_L_CLUTB110_BIT          0xFF
#define LCDC_GDCCCLUTB55_L_CLUTB110_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB55_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB55_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB55_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB55_L_RESERVED_BITWIDTH     24
// GDCCCLUTB55_U Register
#define LCDC_GDCCCLUTB55_U_OFS                   0x00000DBC
// CLUTB111 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB55_U_CLUTB111_MASK         0xFF
#define LCDC_GDCCCLUTB55_U_CLUTB111_SHIFT        0 
#define LCDC_GDCCCLUTB55_U_CLUTB111_BIT          0xFF
#define LCDC_GDCCCLUTB55_U_CLUTB111_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB55_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB55_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB55_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB55_U_RESERVED_BITWIDTH     24
// GDCCCLUTB56_L Register
#define LCDC_GDCCCLUTB56_L_OFS                   0x00000DC0
// CLUTB112 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB56_L_CLUTB112_MASK         0xFF
#define LCDC_GDCCCLUTB56_L_CLUTB112_SHIFT        0 
#define LCDC_GDCCCLUTB56_L_CLUTB112_BIT          0xFF
#define LCDC_GDCCCLUTB56_L_CLUTB112_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB56_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB56_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB56_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB56_L_RESERVED_BITWIDTH     24
// GDCCCLUTB56_U Register
#define LCDC_GDCCCLUTB56_U_OFS                   0x00000DC4
// CLUTB113 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB56_U_CLUTB113_MASK         0xFF
#define LCDC_GDCCCLUTB56_U_CLUTB113_SHIFT        0 
#define LCDC_GDCCCLUTB56_U_CLUTB113_BIT          0xFF
#define LCDC_GDCCCLUTB56_U_CLUTB113_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB56_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB56_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB56_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB56_U_RESERVED_BITWIDTH     24
// GDCCCLUTB57_L Register
#define LCDC_GDCCCLUTB57_L_OFS                   0x00000DC8
// CLUTB114 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB57_L_CLUTB114_MASK         0xFF
#define LCDC_GDCCCLUTB57_L_CLUTB114_SHIFT        0 
#define LCDC_GDCCCLUTB57_L_CLUTB114_BIT          0xFF
#define LCDC_GDCCCLUTB57_L_CLUTB114_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB57_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB57_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB57_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB57_L_RESERVED_BITWIDTH     24
// GDCCCLUTB57_U Register
#define LCDC_GDCCCLUTB57_U_OFS                   0x00000DCC
// CLUTB115 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB57_U_CLUTB115_MASK         0xFF
#define LCDC_GDCCCLUTB57_U_CLUTB115_SHIFT        0 
#define LCDC_GDCCCLUTB57_U_CLUTB115_BIT          0xFF
#define LCDC_GDCCCLUTB57_U_CLUTB115_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB57_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB57_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB57_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB57_U_RESERVED_BITWIDTH     24
// GDCCCLUTB58_L Register
#define LCDC_GDCCCLUTB58_L_OFS                   0x00000DD0
// CLUTB116 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB58_L_CLUTB116_MASK         0xFF
#define LCDC_GDCCCLUTB58_L_CLUTB116_SHIFT        0 
#define LCDC_GDCCCLUTB58_L_CLUTB116_BIT          0xFF
#define LCDC_GDCCCLUTB58_L_CLUTB116_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB58_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB58_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB58_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB58_L_RESERVED_BITWIDTH     24
// GDCCCLUTB58_U Register
#define LCDC_GDCCCLUTB58_U_OFS                   0x00000DD4
// CLUTB117 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB58_U_CLUTB117_MASK         0xFF
#define LCDC_GDCCCLUTB58_U_CLUTB117_SHIFT        0 
#define LCDC_GDCCCLUTB58_U_CLUTB117_BIT          0xFF
#define LCDC_GDCCCLUTB58_U_CLUTB117_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB58_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB58_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB58_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB58_U_RESERVED_BITWIDTH     24
// GDCCCLUTB59_L Register
#define LCDC_GDCCCLUTB59_L_OFS                   0x00000DD8
// CLUTB118 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB59_L_CLUTB118_MASK         0xFF
#define LCDC_GDCCCLUTB59_L_CLUTB118_SHIFT        0 
#define LCDC_GDCCCLUTB59_L_CLUTB118_BIT          0xFF
#define LCDC_GDCCCLUTB59_L_CLUTB118_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB59_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB59_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB59_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB59_L_RESERVED_BITWIDTH     24
// GDCCCLUTB59_U Register
#define LCDC_GDCCCLUTB59_U_OFS                   0x00000DDC
// CLUTB119 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB59_U_CLUTB119_MASK         0xFF
#define LCDC_GDCCCLUTB59_U_CLUTB119_SHIFT        0 
#define LCDC_GDCCCLUTB59_U_CLUTB119_BIT          0xFF
#define LCDC_GDCCCLUTB59_U_CLUTB119_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB59_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB59_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB59_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB59_U_RESERVED_BITWIDTH     24
// GDCCCLUTB60_L Register
#define LCDC_GDCCCLUTB60_L_OFS                   0x00000DE0
// CLUTB120 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB60_L_CLUTB120_MASK         0xFF
#define LCDC_GDCCCLUTB60_L_CLUTB120_SHIFT        0 
#define LCDC_GDCCCLUTB60_L_CLUTB120_BIT          0xFF
#define LCDC_GDCCCLUTB60_L_CLUTB120_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB60_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB60_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB60_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB60_L_RESERVED_BITWIDTH     24
// GDCCCLUTB60_U Register
#define LCDC_GDCCCLUTB60_U_OFS                   0x00000DE4
// CLUTB121 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB60_U_CLUTB121_MASK         0xFF
#define LCDC_GDCCCLUTB60_U_CLUTB121_SHIFT        0 
#define LCDC_GDCCCLUTB60_U_CLUTB121_BIT          0xFF
#define LCDC_GDCCCLUTB60_U_CLUTB121_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB60_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB60_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB60_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB60_U_RESERVED_BITWIDTH     24
// GDCCCLUTB61_L Register
#define LCDC_GDCCCLUTB61_L_OFS                   0x00000DE8
// CLUTB122 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB61_L_CLUTB122_MASK         0xFF
#define LCDC_GDCCCLUTB61_L_CLUTB122_SHIFT        0 
#define LCDC_GDCCCLUTB61_L_CLUTB122_BIT          0xFF
#define LCDC_GDCCCLUTB61_L_CLUTB122_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB61_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB61_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB61_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB61_L_RESERVED_BITWIDTH     24
// GDCCCLUTB61_U Register
#define LCDC_GDCCCLUTB61_U_OFS                   0x00000DEC
// CLUTB123 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB61_U_CLUTB123_MASK         0xFF
#define LCDC_GDCCCLUTB61_U_CLUTB123_SHIFT        0 
#define LCDC_GDCCCLUTB61_U_CLUTB123_BIT          0xFF
#define LCDC_GDCCCLUTB61_U_CLUTB123_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB61_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB61_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB61_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB61_U_RESERVED_BITWIDTH     24
// GDCCCLUTB62_L Register
#define LCDC_GDCCCLUTB62_L_OFS                   0x00000DF0
// CLUTB124 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB62_L_CLUTB124_MASK         0xFF
#define LCDC_GDCCCLUTB62_L_CLUTB124_SHIFT        0 
#define LCDC_GDCCCLUTB62_L_CLUTB124_BIT          0xFF
#define LCDC_GDCCCLUTB62_L_CLUTB124_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB62_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB62_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB62_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB62_L_RESERVED_BITWIDTH     24
// GDCCCLUTB62_U Register
#define LCDC_GDCCCLUTB62_U_OFS                   0x00000DF4
// CLUTB125 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB62_U_CLUTB125_MASK         0xFF
#define LCDC_GDCCCLUTB62_U_CLUTB125_SHIFT        0 
#define LCDC_GDCCCLUTB62_U_CLUTB125_BIT          0xFF
#define LCDC_GDCCCLUTB62_U_CLUTB125_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB62_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB62_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB62_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB62_U_RESERVED_BITWIDTH     24
// GDCCCLUTB63_L Register
#define LCDC_GDCCCLUTB63_L_OFS                   0x00000DF8
// CLUTB126 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB63_L_CLUTB126_MASK         0xFF
#define LCDC_GDCCCLUTB63_L_CLUTB126_SHIFT        0 
#define LCDC_GDCCCLUTB63_L_CLUTB126_BIT          0xFF
#define LCDC_GDCCCLUTB63_L_CLUTB126_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB63_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB63_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB63_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB63_L_RESERVED_BITWIDTH     24
// GDCCCLUTB63_U Register
#define LCDC_GDCCCLUTB63_U_OFS                   0x00000DFC
// CLUTB127 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB63_U_CLUTB127_MASK         0xFF
#define LCDC_GDCCCLUTB63_U_CLUTB127_SHIFT        0 
#define LCDC_GDCCCLUTB63_U_CLUTB127_BIT          0xFF
#define LCDC_GDCCCLUTB63_U_CLUTB127_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB63_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB63_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB63_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB63_U_RESERVED_BITWIDTH     24
// GDCCCLUTB64_L Register
#define LCDC_GDCCCLUTB64_L_OFS                   0x00000E00
// CLUTB128 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB64_L_CLUTB128_MASK         0xFF
#define LCDC_GDCCCLUTB64_L_CLUTB128_SHIFT        0 
#define LCDC_GDCCCLUTB64_L_CLUTB128_BIT          0xFF
#define LCDC_GDCCCLUTB64_L_CLUTB128_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB64_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB64_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB64_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB64_L_RESERVED_BITWIDTH     24
// GDCCCLUTB64_U Register
#define LCDC_GDCCCLUTB64_U_OFS                   0x00000E04
// CLUTB129 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB64_U_CLUTB129_MASK         0xFF
#define LCDC_GDCCCLUTB64_U_CLUTB129_SHIFT        0 
#define LCDC_GDCCCLUTB64_U_CLUTB129_BIT          0xFF
#define LCDC_GDCCCLUTB64_U_CLUTB129_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB64_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB64_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB64_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB64_U_RESERVED_BITWIDTH     24
// GDCCCLUTB65_L Register
#define LCDC_GDCCCLUTB65_L_OFS                   0x00000E08
// CLUTB130 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB65_L_CLUTB130_MASK         0xFF
#define LCDC_GDCCCLUTB65_L_CLUTB130_SHIFT        0 
#define LCDC_GDCCCLUTB65_L_CLUTB130_BIT          0xFF
#define LCDC_GDCCCLUTB65_L_CLUTB130_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB65_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB65_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB65_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB65_L_RESERVED_BITWIDTH     24
// GDCCCLUTB65_U Register
#define LCDC_GDCCCLUTB65_U_OFS                   0x00000E0C
// CLUTB131 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB65_U_CLUTB131_MASK         0xFF
#define LCDC_GDCCCLUTB65_U_CLUTB131_SHIFT        0 
#define LCDC_GDCCCLUTB65_U_CLUTB131_BIT          0xFF
#define LCDC_GDCCCLUTB65_U_CLUTB131_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB65_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB65_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB65_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB65_U_RESERVED_BITWIDTH     24
// GDCCCLUTB66_L Register
#define LCDC_GDCCCLUTB66_L_OFS                   0x00000E10
// CLUTB132 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB66_L_CLUTB132_MASK         0xFF
#define LCDC_GDCCCLUTB66_L_CLUTB132_SHIFT        0 
#define LCDC_GDCCCLUTB66_L_CLUTB132_BIT          0xFF
#define LCDC_GDCCCLUTB66_L_CLUTB132_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB66_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB66_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB66_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB66_L_RESERVED_BITWIDTH     24
// GDCCCLUTB66_U Register
#define LCDC_GDCCCLUTB66_U_OFS                   0x00000E14
// CLUTB133 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB66_U_CLUTB133_MASK         0xFF
#define LCDC_GDCCCLUTB66_U_CLUTB133_SHIFT        0 
#define LCDC_GDCCCLUTB66_U_CLUTB133_BIT          0xFF
#define LCDC_GDCCCLUTB66_U_CLUTB133_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB66_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB66_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB66_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB66_U_RESERVED_BITWIDTH     24
// GDCCCLUTB67_L Register
#define LCDC_GDCCCLUTB67_L_OFS                   0x00000E18
// CLUTB134 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB67_L_CLUTB134_MASK         0xFF
#define LCDC_GDCCCLUTB67_L_CLUTB134_SHIFT        0 
#define LCDC_GDCCCLUTB67_L_CLUTB134_BIT          0xFF
#define LCDC_GDCCCLUTB67_L_CLUTB134_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB67_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB67_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB67_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB67_L_RESERVED_BITWIDTH     24
// GDCCCLUTB67_U Register
#define LCDC_GDCCCLUTB67_U_OFS                   0x00000E1C
// CLUTB135 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB67_U_CLUTB135_MASK         0xFF
#define LCDC_GDCCCLUTB67_U_CLUTB135_SHIFT        0 
#define LCDC_GDCCCLUTB67_U_CLUTB135_BIT          0xFF
#define LCDC_GDCCCLUTB67_U_CLUTB135_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB67_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB67_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB67_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB67_U_RESERVED_BITWIDTH     24
// GDCCCLUTB68_L Register
#define LCDC_GDCCCLUTB68_L_OFS                   0x00000E20
// CLUTB136 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB68_L_CLUTB136_MASK         0xFF
#define LCDC_GDCCCLUTB68_L_CLUTB136_SHIFT        0 
#define LCDC_GDCCCLUTB68_L_CLUTB136_BIT          0xFF
#define LCDC_GDCCCLUTB68_L_CLUTB136_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB68_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB68_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB68_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB68_L_RESERVED_BITWIDTH     24
// GDCCCLUTB68_U Register
#define LCDC_GDCCCLUTB68_U_OFS                   0x00000E24
// CLUTB137 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB68_U_CLUTB137_MASK         0xFF
#define LCDC_GDCCCLUTB68_U_CLUTB137_SHIFT        0 
#define LCDC_GDCCCLUTB68_U_CLUTB137_BIT          0xFF
#define LCDC_GDCCCLUTB68_U_CLUTB137_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB68_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB68_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB68_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB68_U_RESERVED_BITWIDTH     24
// GDCCCLUTB69_L Register
#define LCDC_GDCCCLUTB69_L_OFS                   0x00000E28
// CLUTB138 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB69_L_CLUTB138_MASK         0xFF
#define LCDC_GDCCCLUTB69_L_CLUTB138_SHIFT        0 
#define LCDC_GDCCCLUTB69_L_CLUTB138_BIT          0xFF
#define LCDC_GDCCCLUTB69_L_CLUTB138_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB69_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB69_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB69_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB69_L_RESERVED_BITWIDTH     24
// GDCCCLUTB69_U Register
#define LCDC_GDCCCLUTB69_U_OFS                   0x00000E2C
// CLUTB139 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB69_U_CLUTB139_MASK         0xFF
#define LCDC_GDCCCLUTB69_U_CLUTB139_SHIFT        0 
#define LCDC_GDCCCLUTB69_U_CLUTB139_BIT          0xFF
#define LCDC_GDCCCLUTB69_U_CLUTB139_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB69_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB69_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB69_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB69_U_RESERVED_BITWIDTH     24
// GDCCCLUTB70_L Register
#define LCDC_GDCCCLUTB70_L_OFS                   0x00000E30
// CLUTB140 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB70_L_CLUTB140_MASK         0xFF
#define LCDC_GDCCCLUTB70_L_CLUTB140_SHIFT        0 
#define LCDC_GDCCCLUTB70_L_CLUTB140_BIT          0xFF
#define LCDC_GDCCCLUTB70_L_CLUTB140_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB70_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB70_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB70_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB70_L_RESERVED_BITWIDTH     24
// GDCCCLUTB70_U Register
#define LCDC_GDCCCLUTB70_U_OFS                   0x00000E34
// CLUTB141 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB70_U_CLUTB141_MASK         0xFF
#define LCDC_GDCCCLUTB70_U_CLUTB141_SHIFT        0 
#define LCDC_GDCCCLUTB70_U_CLUTB141_BIT          0xFF
#define LCDC_GDCCCLUTB70_U_CLUTB141_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB70_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB70_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB70_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB70_U_RESERVED_BITWIDTH     24
// GDCCCLUTB71_L Register
#define LCDC_GDCCCLUTB71_L_OFS                   0x00000E38
// CLUTB142 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB71_L_CLUTB142_MASK         0xFF
#define LCDC_GDCCCLUTB71_L_CLUTB142_SHIFT        0 
#define LCDC_GDCCCLUTB71_L_CLUTB142_BIT          0xFF
#define LCDC_GDCCCLUTB71_L_CLUTB142_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB71_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB71_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB71_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB71_L_RESERVED_BITWIDTH     24
// GDCCCLUTB71_U Register
#define LCDC_GDCCCLUTB71_U_OFS                   0x00000E3C
// CLUTB143 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB71_U_CLUTB143_MASK         0xFF
#define LCDC_GDCCCLUTB71_U_CLUTB143_SHIFT        0 
#define LCDC_GDCCCLUTB71_U_CLUTB143_BIT          0xFF
#define LCDC_GDCCCLUTB71_U_CLUTB143_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB71_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB71_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB71_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB71_U_RESERVED_BITWIDTH     24
// GDCCCLUTB72_L Register
#define LCDC_GDCCCLUTB72_L_OFS                   0x00000E40
// CLUTB144 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB72_L_CLUTB144_MASK         0xFF
#define LCDC_GDCCCLUTB72_L_CLUTB144_SHIFT        0 
#define LCDC_GDCCCLUTB72_L_CLUTB144_BIT          0xFF
#define LCDC_GDCCCLUTB72_L_CLUTB144_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB72_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB72_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB72_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB72_L_RESERVED_BITWIDTH     24
// GDCCCLUTB72_U Register
#define LCDC_GDCCCLUTB72_U_OFS                   0x00000E44
// CLUTB145 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB72_U_CLUTB145_MASK         0xFF
#define LCDC_GDCCCLUTB72_U_CLUTB145_SHIFT        0 
#define LCDC_GDCCCLUTB72_U_CLUTB145_BIT          0xFF
#define LCDC_GDCCCLUTB72_U_CLUTB145_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB72_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB72_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB72_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB72_U_RESERVED_BITWIDTH     24
// GDCCCLUTB73_L Register
#define LCDC_GDCCCLUTB73_L_OFS                   0x00000E48
// CLUTB146 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB73_L_CLUTB146_MASK         0xFF
#define LCDC_GDCCCLUTB73_L_CLUTB146_SHIFT        0 
#define LCDC_GDCCCLUTB73_L_CLUTB146_BIT          0xFF
#define LCDC_GDCCCLUTB73_L_CLUTB146_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB73_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB73_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB73_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB73_L_RESERVED_BITWIDTH     24
// GDCCCLUTB73_U Register
#define LCDC_GDCCCLUTB73_U_OFS                   0x00000E4C
// CLUTB147 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB73_U_CLUTB147_MASK         0xFF
#define LCDC_GDCCCLUTB73_U_CLUTB147_SHIFT        0 
#define LCDC_GDCCCLUTB73_U_CLUTB147_BIT          0xFF
#define LCDC_GDCCCLUTB73_U_CLUTB147_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB73_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB73_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB73_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB73_U_RESERVED_BITWIDTH     24
// GDCCCLUTB74_L Register
#define LCDC_GDCCCLUTB74_L_OFS                   0x00000E50
// CLUTB148 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB74_L_CLUTB148_MASK         0xFF
#define LCDC_GDCCCLUTB74_L_CLUTB148_SHIFT        0 
#define LCDC_GDCCCLUTB74_L_CLUTB148_BIT          0xFF
#define LCDC_GDCCCLUTB74_L_CLUTB148_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB74_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB74_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB74_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB74_L_RESERVED_BITWIDTH     24
// GDCCCLUTB74_U Register
#define LCDC_GDCCCLUTB74_U_OFS                   0x00000E54
// CLUTB149 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB74_U_CLUTB149_MASK         0xFF
#define LCDC_GDCCCLUTB74_U_CLUTB149_SHIFT        0 
#define LCDC_GDCCCLUTB74_U_CLUTB149_BIT          0xFF
#define LCDC_GDCCCLUTB74_U_CLUTB149_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB74_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB74_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB74_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB74_U_RESERVED_BITWIDTH     24
// GDCCCLUTB75_L Register
#define LCDC_GDCCCLUTB75_L_OFS                   0x00000E58
// CLUTB150 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB75_L_CLUTB150_MASK         0xFF
#define LCDC_GDCCCLUTB75_L_CLUTB150_SHIFT        0 
#define LCDC_GDCCCLUTB75_L_CLUTB150_BIT          0xFF
#define LCDC_GDCCCLUTB75_L_CLUTB150_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB75_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB75_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB75_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB75_L_RESERVED_BITWIDTH     24
// GDCCCLUTB75_U Register
#define LCDC_GDCCCLUTB75_U_OFS                   0x00000E5C
// CLUTB151 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB75_U_CLUTB151_MASK         0xFF
#define LCDC_GDCCCLUTB75_U_CLUTB151_SHIFT        0 
#define LCDC_GDCCCLUTB75_U_CLUTB151_BIT          0xFF
#define LCDC_GDCCCLUTB75_U_CLUTB151_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB75_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB75_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB75_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB75_U_RESERVED_BITWIDTH     24
// GDCCCLUTB76_L Register
#define LCDC_GDCCCLUTB76_L_OFS                   0x00000E60
// CLUTB152 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB76_L_CLUTB152_MASK         0xFF
#define LCDC_GDCCCLUTB76_L_CLUTB152_SHIFT        0 
#define LCDC_GDCCCLUTB76_L_CLUTB152_BIT          0xFF
#define LCDC_GDCCCLUTB76_L_CLUTB152_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB76_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB76_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB76_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB76_L_RESERVED_BITWIDTH     24
// GDCCCLUTB76_U Register
#define LCDC_GDCCCLUTB76_U_OFS                   0x00000E64
// CLUTB153 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB76_U_CLUTB153_MASK         0xFF
#define LCDC_GDCCCLUTB76_U_CLUTB153_SHIFT        0 
#define LCDC_GDCCCLUTB76_U_CLUTB153_BIT          0xFF
#define LCDC_GDCCCLUTB76_U_CLUTB153_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB76_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB76_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB76_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB76_U_RESERVED_BITWIDTH     24
// GDCCCLUTB77_L Register
#define LCDC_GDCCCLUTB77_L_OFS                   0x00000E68
// CLUTB154 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB77_L_CLUTB154_MASK         0xFF
#define LCDC_GDCCCLUTB77_L_CLUTB154_SHIFT        0 
#define LCDC_GDCCCLUTB77_L_CLUTB154_BIT          0xFF
#define LCDC_GDCCCLUTB77_L_CLUTB154_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB77_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB77_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB77_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB77_L_RESERVED_BITWIDTH     24
// GDCCCLUTB77_U Register
#define LCDC_GDCCCLUTB77_U_OFS                   0x00000E6C
// CLUTB155 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB77_U_CLUTB155_MASK         0xFF
#define LCDC_GDCCCLUTB77_U_CLUTB155_SHIFT        0 
#define LCDC_GDCCCLUTB77_U_CLUTB155_BIT          0xFF
#define LCDC_GDCCCLUTB77_U_CLUTB155_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB77_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB77_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB77_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB77_U_RESERVED_BITWIDTH     24
// GDCCCLUTB78_L Register
#define LCDC_GDCCCLUTB78_L_OFS                   0x00000E70
// CLUTB156 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB78_L_CLUTB156_MASK         0xFF
#define LCDC_GDCCCLUTB78_L_CLUTB156_SHIFT        0 
#define LCDC_GDCCCLUTB78_L_CLUTB156_BIT          0xFF
#define LCDC_GDCCCLUTB78_L_CLUTB156_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB78_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB78_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB78_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB78_L_RESERVED_BITWIDTH     24
// GDCCCLUTB78_U Register
#define LCDC_GDCCCLUTB78_U_OFS                   0x00000E74
// CLUTB157 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB78_U_CLUTB157_MASK         0xFF
#define LCDC_GDCCCLUTB78_U_CLUTB157_SHIFT        0 
#define LCDC_GDCCCLUTB78_U_CLUTB157_BIT          0xFF
#define LCDC_GDCCCLUTB78_U_CLUTB157_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB78_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB78_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB78_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB78_U_RESERVED_BITWIDTH     24
// GDCCCLUTB79_L Register
#define LCDC_GDCCCLUTB79_L_OFS                   0x00000E78
// CLUTB158 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB79_L_CLUTB158_MASK         0xFF
#define LCDC_GDCCCLUTB79_L_CLUTB158_SHIFT        0 
#define LCDC_GDCCCLUTB79_L_CLUTB158_BIT          0xFF
#define LCDC_GDCCCLUTB79_L_CLUTB158_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB79_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB79_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB79_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB79_L_RESERVED_BITWIDTH     24
// GDCCCLUTB79_U Register
#define LCDC_GDCCCLUTB79_U_OFS                   0x00000E7C
// CLUTB159 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB79_U_CLUTB159_MASK         0xFF
#define LCDC_GDCCCLUTB79_U_CLUTB159_SHIFT        0 
#define LCDC_GDCCCLUTB79_U_CLUTB159_BIT          0xFF
#define LCDC_GDCCCLUTB79_U_CLUTB159_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB79_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB79_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB79_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB79_U_RESERVED_BITWIDTH     24
// GDCCCLUTB80_L Register
#define LCDC_GDCCCLUTB80_L_OFS                   0x00000E80
// CLUTB160 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB80_L_CLUTB160_MASK         0xFF
#define LCDC_GDCCCLUTB80_L_CLUTB160_SHIFT        0 
#define LCDC_GDCCCLUTB80_L_CLUTB160_BIT          0xFF
#define LCDC_GDCCCLUTB80_L_CLUTB160_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB80_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB80_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB80_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB80_L_RESERVED_BITWIDTH     24
// GDCCCLUTB80_U Register
#define LCDC_GDCCCLUTB80_U_OFS                   0x00000E84
// CLUTB161 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB80_U_CLUTB161_MASK         0xFF
#define LCDC_GDCCCLUTB80_U_CLUTB161_SHIFT        0 
#define LCDC_GDCCCLUTB80_U_CLUTB161_BIT          0xFF
#define LCDC_GDCCCLUTB80_U_CLUTB161_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB80_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB80_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB80_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB80_U_RESERVED_BITWIDTH     24
// GDCCCLUTB81_L Register
#define LCDC_GDCCCLUTB81_L_OFS                   0x00000E88
// CLUTB162 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB81_L_CLUTB162_MASK         0xFF
#define LCDC_GDCCCLUTB81_L_CLUTB162_SHIFT        0 
#define LCDC_GDCCCLUTB81_L_CLUTB162_BIT          0xFF
#define LCDC_GDCCCLUTB81_L_CLUTB162_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB81_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB81_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB81_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB81_L_RESERVED_BITWIDTH     24
// GDCCCLUTB81_U Register
#define LCDC_GDCCCLUTB81_U_OFS                   0x00000E8C
// CLUTB163 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB81_U_CLUTB163_MASK         0xFF
#define LCDC_GDCCCLUTB81_U_CLUTB163_SHIFT        0 
#define LCDC_GDCCCLUTB81_U_CLUTB163_BIT          0xFF
#define LCDC_GDCCCLUTB81_U_CLUTB163_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB81_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB81_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB81_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB81_U_RESERVED_BITWIDTH     24
// GDCCCLUTB82_L Register
#define LCDC_GDCCCLUTB82_L_OFS                   0x00000E90
// CLUTB164 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB82_L_CLUTB164_MASK         0xFF
#define LCDC_GDCCCLUTB82_L_CLUTB164_SHIFT        0 
#define LCDC_GDCCCLUTB82_L_CLUTB164_BIT          0xFF
#define LCDC_GDCCCLUTB82_L_CLUTB164_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB82_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB82_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB82_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB82_L_RESERVED_BITWIDTH     24
// GDCCCLUTB82_U Register
#define LCDC_GDCCCLUTB82_U_OFS                   0x00000E94
// CLUTB165 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB82_U_CLUTB165_MASK         0xFF
#define LCDC_GDCCCLUTB82_U_CLUTB165_SHIFT        0 
#define LCDC_GDCCCLUTB82_U_CLUTB165_BIT          0xFF
#define LCDC_GDCCCLUTB82_U_CLUTB165_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB82_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB82_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB82_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB82_U_RESERVED_BITWIDTH     24
// GDCCCLUTB83_L Register
#define LCDC_GDCCCLUTB83_L_OFS                   0x00000E98
// CLUTB166 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB83_L_CLUTB166_MASK         0xFF
#define LCDC_GDCCCLUTB83_L_CLUTB166_SHIFT        0 
#define LCDC_GDCCCLUTB83_L_CLUTB166_BIT          0xFF
#define LCDC_GDCCCLUTB83_L_CLUTB166_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB83_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB83_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB83_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB83_L_RESERVED_BITWIDTH     24
// GDCCCLUTB83_U Register
#define LCDC_GDCCCLUTB83_U_OFS                   0x00000E9C
// CLUTB167 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB83_U_CLUTB167_MASK         0xFF
#define LCDC_GDCCCLUTB83_U_CLUTB167_SHIFT        0 
#define LCDC_GDCCCLUTB83_U_CLUTB167_BIT          0xFF
#define LCDC_GDCCCLUTB83_U_CLUTB167_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB83_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB83_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB83_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB83_U_RESERVED_BITWIDTH     24
// GDCCCLUTB84_L Register
#define LCDC_GDCCCLUTB84_L_OFS                   0x00000EA0
// CLUTB168 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB84_L_CLUTB168_MASK         0xFF
#define LCDC_GDCCCLUTB84_L_CLUTB168_SHIFT        0 
#define LCDC_GDCCCLUTB84_L_CLUTB168_BIT          0xFF
#define LCDC_GDCCCLUTB84_L_CLUTB168_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB84_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB84_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB84_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB84_L_RESERVED_BITWIDTH     24
// GDCCCLUTB84_U Register
#define LCDC_GDCCCLUTB84_U_OFS                   0x00000EA4
// CLUTB169 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB84_U_CLUTB169_MASK         0xFF
#define LCDC_GDCCCLUTB84_U_CLUTB169_SHIFT        0 
#define LCDC_GDCCCLUTB84_U_CLUTB169_BIT          0xFF
#define LCDC_GDCCCLUTB84_U_CLUTB169_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB84_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB84_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB84_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB84_U_RESERVED_BITWIDTH     24
// GDCCCLUTB85_L Register
#define LCDC_GDCCCLUTB85_L_OFS                   0x00000EA8
// CLUTB170 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB85_L_CLUTB170_MASK         0xFF
#define LCDC_GDCCCLUTB85_L_CLUTB170_SHIFT        0 
#define LCDC_GDCCCLUTB85_L_CLUTB170_BIT          0xFF
#define LCDC_GDCCCLUTB85_L_CLUTB170_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB85_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB85_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB85_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB85_L_RESERVED_BITWIDTH     24
// GDCCCLUTB85_U Register
#define LCDC_GDCCCLUTB85_U_OFS                   0x00000EAC
// CLUTB171 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB85_U_CLUTB171_MASK         0xFF
#define LCDC_GDCCCLUTB85_U_CLUTB171_SHIFT        0 
#define LCDC_GDCCCLUTB85_U_CLUTB171_BIT          0xFF
#define LCDC_GDCCCLUTB85_U_CLUTB171_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB85_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB85_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB85_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB85_U_RESERVED_BITWIDTH     24
// GDCCCLUTB86_L Register
#define LCDC_GDCCCLUTB86_L_OFS                   0x00000EB0
// CLUTB172 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB86_L_CLUTB172_MASK         0xFF
#define LCDC_GDCCCLUTB86_L_CLUTB172_SHIFT        0 
#define LCDC_GDCCCLUTB86_L_CLUTB172_BIT          0xFF
#define LCDC_GDCCCLUTB86_L_CLUTB172_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB86_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB86_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB86_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB86_L_RESERVED_BITWIDTH     24
// GDCCCLUTB86_U Register
#define LCDC_GDCCCLUTB86_U_OFS                   0x00000EB4
// CLUTB173 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB86_U_CLUTB173_MASK         0xFF
#define LCDC_GDCCCLUTB86_U_CLUTB173_SHIFT        0 
#define LCDC_GDCCCLUTB86_U_CLUTB173_BIT          0xFF
#define LCDC_GDCCCLUTB86_U_CLUTB173_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB86_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB86_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB86_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB86_U_RESERVED_BITWIDTH     24
// GDCCCLUTB87_L Register
#define LCDC_GDCCCLUTB87_L_OFS                   0x00000EB8
// CLUTB174 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB87_L_CLUTB174_MASK         0xFF
#define LCDC_GDCCCLUTB87_L_CLUTB174_SHIFT        0 
#define LCDC_GDCCCLUTB87_L_CLUTB174_BIT          0xFF
#define LCDC_GDCCCLUTB87_L_CLUTB174_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB87_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB87_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB87_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB87_L_RESERVED_BITWIDTH     24
// GDCCCLUTB87_U Register
#define LCDC_GDCCCLUTB87_U_OFS                   0x00000EBC
// CLUTB175 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB87_U_CLUTB175_MASK         0xFF
#define LCDC_GDCCCLUTB87_U_CLUTB175_SHIFT        0 
#define LCDC_GDCCCLUTB87_U_CLUTB175_BIT          0xFF
#define LCDC_GDCCCLUTB87_U_CLUTB175_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB87_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB87_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB87_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB87_U_RESERVED_BITWIDTH     24
// GDCCCLUTB88_L Register
#define LCDC_GDCCCLUTB88_L_OFS                   0x00000EC0
// CLUTB176 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB88_L_CLUTB176_MASK         0xFF
#define LCDC_GDCCCLUTB88_L_CLUTB176_SHIFT        0 
#define LCDC_GDCCCLUTB88_L_CLUTB176_BIT          0xFF
#define LCDC_GDCCCLUTB88_L_CLUTB176_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB88_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB88_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB88_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB88_L_RESERVED_BITWIDTH     24
// GDCCCLUTB88_U Register
#define LCDC_GDCCCLUTB88_U_OFS                   0x00000EC4
// CLUTB177 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB88_U_CLUTB177_MASK         0xFF
#define LCDC_GDCCCLUTB88_U_CLUTB177_SHIFT        0 
#define LCDC_GDCCCLUTB88_U_CLUTB177_BIT          0xFF
#define LCDC_GDCCCLUTB88_U_CLUTB177_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB88_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB88_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB88_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB88_U_RESERVED_BITWIDTH     24
// GDCCCLUTB89_L Register
#define LCDC_GDCCCLUTB89_L_OFS                   0x00000EC8
// CLUTB178 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB89_L_CLUTB178_MASK         0xFF
#define LCDC_GDCCCLUTB89_L_CLUTB178_SHIFT        0 
#define LCDC_GDCCCLUTB89_L_CLUTB178_BIT          0xFF
#define LCDC_GDCCCLUTB89_L_CLUTB178_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB89_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB89_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB89_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB89_L_RESERVED_BITWIDTH     24
// GDCCCLUTB89_U Register
#define LCDC_GDCCCLUTB89_U_OFS                   0x00000ECC
// CLUTB179 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB89_U_CLUTB179_MASK         0xFF
#define LCDC_GDCCCLUTB89_U_CLUTB179_SHIFT        0 
#define LCDC_GDCCCLUTB89_U_CLUTB179_BIT          0xFF
#define LCDC_GDCCCLUTB89_U_CLUTB179_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB89_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB89_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB89_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB89_U_RESERVED_BITWIDTH     24
// GDCCCLUTB90_L Register
#define LCDC_GDCCCLUTB90_L_OFS                   0x00000ED0
// CLUTB180 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB90_L_CLUTB180_MASK         0xFF
#define LCDC_GDCCCLUTB90_L_CLUTB180_SHIFT        0 
#define LCDC_GDCCCLUTB90_L_CLUTB180_BIT          0xFF
#define LCDC_GDCCCLUTB90_L_CLUTB180_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB90_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB90_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB90_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB90_L_RESERVED_BITWIDTH     24
// GDCCCLUTB90_U Register
#define LCDC_GDCCCLUTB90_U_OFS                   0x00000ED4
// CLUTB181 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB90_U_CLUTB181_MASK         0xFF
#define LCDC_GDCCCLUTB90_U_CLUTB181_SHIFT        0 
#define LCDC_GDCCCLUTB90_U_CLUTB181_BIT          0xFF
#define LCDC_GDCCCLUTB90_U_CLUTB181_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB90_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB90_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB90_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB90_U_RESERVED_BITWIDTH     24
// GDCCCLUTB91_L Register
#define LCDC_GDCCCLUTB91_L_OFS                   0x00000ED8
// CLUTB182 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB91_L_CLUTB182_MASK         0xFF
#define LCDC_GDCCCLUTB91_L_CLUTB182_SHIFT        0 
#define LCDC_GDCCCLUTB91_L_CLUTB182_BIT          0xFF
#define LCDC_GDCCCLUTB91_L_CLUTB182_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB91_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB91_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB91_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB91_L_RESERVED_BITWIDTH     24
// GDCCCLUTB91_U Register
#define LCDC_GDCCCLUTB91_U_OFS                   0x00000EDC
// CLUTB183 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB91_U_CLUTB183_MASK         0xFF
#define LCDC_GDCCCLUTB91_U_CLUTB183_SHIFT        0 
#define LCDC_GDCCCLUTB91_U_CLUTB183_BIT          0xFF
#define LCDC_GDCCCLUTB91_U_CLUTB183_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB91_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB91_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB91_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB91_U_RESERVED_BITWIDTH     24
// GDCCCLUTB92_L Register
#define LCDC_GDCCCLUTB92_L_OFS                   0x00000EE0
// CLUTB184 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB92_L_CLUTB184_MASK         0xFF
#define LCDC_GDCCCLUTB92_L_CLUTB184_SHIFT        0 
#define LCDC_GDCCCLUTB92_L_CLUTB184_BIT          0xFF
#define LCDC_GDCCCLUTB92_L_CLUTB184_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB92_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB92_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB92_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB92_L_RESERVED_BITWIDTH     24
// GDCCCLUTB92_U Register
#define LCDC_GDCCCLUTB92_U_OFS                   0x00000EE4
// CLUTB185 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB92_U_CLUTB185_MASK         0xFF
#define LCDC_GDCCCLUTB92_U_CLUTB185_SHIFT        0 
#define LCDC_GDCCCLUTB92_U_CLUTB185_BIT          0xFF
#define LCDC_GDCCCLUTB92_U_CLUTB185_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB92_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB92_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB92_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB92_U_RESERVED_BITWIDTH     24
// GDCCCLUTB93_L Register
#define LCDC_GDCCCLUTB93_L_OFS                   0x00000EE8
// CLUTB186 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB93_L_CLUTB186_MASK         0xFF
#define LCDC_GDCCCLUTB93_L_CLUTB186_SHIFT        0 
#define LCDC_GDCCCLUTB93_L_CLUTB186_BIT          0xFF
#define LCDC_GDCCCLUTB93_L_CLUTB186_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB93_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB93_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB93_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB93_L_RESERVED_BITWIDTH     24
// GDCCCLUTB93_U Register
#define LCDC_GDCCCLUTB93_U_OFS                   0x00000EEC
// CLUTB187 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB93_U_CLUTB187_MASK         0xFF
#define LCDC_GDCCCLUTB93_U_CLUTB187_SHIFT        0 
#define LCDC_GDCCCLUTB93_U_CLUTB187_BIT          0xFF
#define LCDC_GDCCCLUTB93_U_CLUTB187_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB93_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB93_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB93_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB93_U_RESERVED_BITWIDTH     24
// GDCCCLUTB94_L Register
#define LCDC_GDCCCLUTB94_L_OFS                   0x00000EF0
// CLUTB188 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB94_L_CLUTB188_MASK         0xFF
#define LCDC_GDCCCLUTB94_L_CLUTB188_SHIFT        0 
#define LCDC_GDCCCLUTB94_L_CLUTB188_BIT          0xFF
#define LCDC_GDCCCLUTB94_L_CLUTB188_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB94_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB94_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB94_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB94_L_RESERVED_BITWIDTH     24
// GDCCCLUTB94_U Register
#define LCDC_GDCCCLUTB94_U_OFS                   0x00000EF4
// CLUTB189 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB94_U_CLUTB189_MASK         0xFF
#define LCDC_GDCCCLUTB94_U_CLUTB189_SHIFT        0 
#define LCDC_GDCCCLUTB94_U_CLUTB189_BIT          0xFF
#define LCDC_GDCCCLUTB94_U_CLUTB189_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB94_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB94_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB94_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB94_U_RESERVED_BITWIDTH     24
// GDCCCLUTB95_L Register
#define LCDC_GDCCCLUTB95_L_OFS                   0x00000EF8
// CLUTB190 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB95_L_CLUTB190_MASK         0xFF
#define LCDC_GDCCCLUTB95_L_CLUTB190_SHIFT        0 
#define LCDC_GDCCCLUTB95_L_CLUTB190_BIT          0xFF
#define LCDC_GDCCCLUTB95_L_CLUTB190_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB95_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB95_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB95_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB95_L_RESERVED_BITWIDTH     24
// GDCCCLUTB95_U Register
#define LCDC_GDCCCLUTB95_U_OFS                   0x00000EFC
// CLUTB191 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB95_U_CLUTB191_MASK         0xFF
#define LCDC_GDCCCLUTB95_U_CLUTB191_SHIFT        0 
#define LCDC_GDCCCLUTB95_U_CLUTB191_BIT          0xFF
#define LCDC_GDCCCLUTB95_U_CLUTB191_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB95_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB95_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB95_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB95_U_RESERVED_BITWIDTH     24
// GDCCCLUTB96_L Register
#define LCDC_GDCCCLUTB96_L_OFS                   0x00000F00
// CLUTB192 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB96_L_CLUTB192_MASK         0xFF
#define LCDC_GDCCCLUTB96_L_CLUTB192_SHIFT        0 
#define LCDC_GDCCCLUTB96_L_CLUTB192_BIT          0xFF
#define LCDC_GDCCCLUTB96_L_CLUTB192_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB96_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB96_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB96_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB96_L_RESERVED_BITWIDTH     24
// GDCCCLUTB96_U Register
#define LCDC_GDCCCLUTB96_U_OFS                   0x00000F04
// CLUTB193 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB96_U_CLUTB193_MASK         0xFF
#define LCDC_GDCCCLUTB96_U_CLUTB193_SHIFT        0 
#define LCDC_GDCCCLUTB96_U_CLUTB193_BIT          0xFF
#define LCDC_GDCCCLUTB96_U_CLUTB193_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB96_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB96_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB96_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB96_U_RESERVED_BITWIDTH     24
// GDCCCLUTB97_L Register
#define LCDC_GDCCCLUTB97_L_OFS                   0x00000F08
// CLUTB194 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB97_L_CLUTB194_MASK         0xFF
#define LCDC_GDCCCLUTB97_L_CLUTB194_SHIFT        0 
#define LCDC_GDCCCLUTB97_L_CLUTB194_BIT          0xFF
#define LCDC_GDCCCLUTB97_L_CLUTB194_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB97_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB97_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB97_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB97_L_RESERVED_BITWIDTH     24
// GDCCCLUTB97_U Register
#define LCDC_GDCCCLUTB97_U_OFS                   0x00000F0C
// CLUTB195 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB97_U_CLUTB195_MASK         0xFF
#define LCDC_GDCCCLUTB97_U_CLUTB195_SHIFT        0 
#define LCDC_GDCCCLUTB97_U_CLUTB195_BIT          0xFF
#define LCDC_GDCCCLUTB97_U_CLUTB195_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB97_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB97_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB97_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB97_U_RESERVED_BITWIDTH     24
// GDCCCLUTB98_L Register
#define LCDC_GDCCCLUTB98_L_OFS                   0x00000F10
// CLUTB196 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB98_L_CLUTB196_MASK         0xFF
#define LCDC_GDCCCLUTB98_L_CLUTB196_SHIFT        0 
#define LCDC_GDCCCLUTB98_L_CLUTB196_BIT          0xFF
#define LCDC_GDCCCLUTB98_L_CLUTB196_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB98_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB98_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB98_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB98_L_RESERVED_BITWIDTH     24
// GDCCCLUTB98_U Register
#define LCDC_GDCCCLUTB98_U_OFS                   0x00000F14
// CLUTB197 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB98_U_CLUTB197_MASK         0xFF
#define LCDC_GDCCCLUTB98_U_CLUTB197_SHIFT        0 
#define LCDC_GDCCCLUTB98_U_CLUTB197_BIT          0xFF
#define LCDC_GDCCCLUTB98_U_CLUTB197_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB98_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB98_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB98_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB98_U_RESERVED_BITWIDTH     24
// GDCCCLUTB99_L Register
#define LCDC_GDCCCLUTB99_L_OFS                   0x00000F18
// CLUTB198 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB99_L_CLUTB198_MASK         0xFF
#define LCDC_GDCCCLUTB99_L_CLUTB198_SHIFT        0 
#define LCDC_GDCCCLUTB99_L_CLUTB198_BIT          0xFF
#define LCDC_GDCCCLUTB99_L_CLUTB198_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB99_L_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB99_L_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB99_L_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB99_L_RESERVED_BITWIDTH     24
// GDCCCLUTB99_U Register
#define LCDC_GDCCCLUTB99_U_OFS                   0x00000F1C
// CLUTB199 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB99_U_CLUTB199_MASK         0xFF
#define LCDC_GDCCCLUTB99_U_CLUTB199_SHIFT        0 
#define LCDC_GDCCCLUTB99_U_CLUTB199_BIT          0xFF
#define LCDC_GDCCCLUTB99_U_CLUTB199_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB99_U_RESERVED_MASK         0xFFFFFF00
#define LCDC_GDCCCLUTB99_U_RESERVED_SHIFT        8 
#define LCDC_GDCCCLUTB99_U_RESERVED_BIT          0xFFFFFF
#define LCDC_GDCCCLUTB99_U_RESERVED_BITWIDTH     24
// GDCCCLUTB100_L Register
#define LCDC_GDCCCLUTB100_L_OFS                  0x00000F20
// CLUTB200 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB100_L_CLUTB200_MASK        0xFF
#define LCDC_GDCCCLUTB100_L_CLUTB200_SHIFT       0 
#define LCDC_GDCCCLUTB100_L_CLUTB200_BIT         0xFF
#define LCDC_GDCCCLUTB100_L_CLUTB200_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB100_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB100_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB100_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB100_L_RESERVED_BITWIDTH    24
// GDCCCLUTB100_U Register
#define LCDC_GDCCCLUTB100_U_OFS                  0x00000F24
// CLUTB201 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB100_U_CLUTB201_MASK        0xFF
#define LCDC_GDCCCLUTB100_U_CLUTB201_SHIFT       0 
#define LCDC_GDCCCLUTB100_U_CLUTB201_BIT         0xFF
#define LCDC_GDCCCLUTB100_U_CLUTB201_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB100_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB100_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB100_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB100_U_RESERVED_BITWIDTH    24
// GDCCCLUTB101_L Register
#define LCDC_GDCCCLUTB101_L_OFS                  0x00000F28
// CLUTB202 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB101_L_CLUTB202_MASK        0xFF
#define LCDC_GDCCCLUTB101_L_CLUTB202_SHIFT       0 
#define LCDC_GDCCCLUTB101_L_CLUTB202_BIT         0xFF
#define LCDC_GDCCCLUTB101_L_CLUTB202_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB101_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB101_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB101_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB101_L_RESERVED_BITWIDTH    24
// GDCCCLUTB101_U Register
#define LCDC_GDCCCLUTB101_U_OFS                  0x00000F2C
// CLUTB203 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB101_U_CLUTB203_MASK        0xFF
#define LCDC_GDCCCLUTB101_U_CLUTB203_SHIFT       0 
#define LCDC_GDCCCLUTB101_U_CLUTB203_BIT         0xFF
#define LCDC_GDCCCLUTB101_U_CLUTB203_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB101_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB101_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB101_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB101_U_RESERVED_BITWIDTH    24
// GDCCCLUTB102_L Register
#define LCDC_GDCCCLUTB102_L_OFS                  0x00000F30
// CLUTB204 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB102_L_CLUTB204_MASK        0xFF
#define LCDC_GDCCCLUTB102_L_CLUTB204_SHIFT       0 
#define LCDC_GDCCCLUTB102_L_CLUTB204_BIT         0xFF
#define LCDC_GDCCCLUTB102_L_CLUTB204_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB102_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB102_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB102_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB102_L_RESERVED_BITWIDTH    24
// GDCCCLUTB102_U Register
#define LCDC_GDCCCLUTB102_U_OFS                  0x00000F34
// CLUTB205 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB102_U_CLUTB205_MASK        0xFF
#define LCDC_GDCCCLUTB102_U_CLUTB205_SHIFT       0 
#define LCDC_GDCCCLUTB102_U_CLUTB205_BIT         0xFF
#define LCDC_GDCCCLUTB102_U_CLUTB205_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB102_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB102_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB102_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB102_U_RESERVED_BITWIDTH    24
// GDCCCLUTB103_L Register
#define LCDC_GDCCCLUTB103_L_OFS                  0x00000F38
// CLUTB206 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB103_L_CLUTB206_MASK        0xFF
#define LCDC_GDCCCLUTB103_L_CLUTB206_SHIFT       0 
#define LCDC_GDCCCLUTB103_L_CLUTB206_BIT         0xFF
#define LCDC_GDCCCLUTB103_L_CLUTB206_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB103_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB103_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB103_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB103_L_RESERVED_BITWIDTH    24
// GDCCCLUTB103_U Register
#define LCDC_GDCCCLUTB103_U_OFS                  0x00000F3C
// CLUTB207 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB103_U_CLUTB207_MASK        0xFF
#define LCDC_GDCCCLUTB103_U_CLUTB207_SHIFT       0 
#define LCDC_GDCCCLUTB103_U_CLUTB207_BIT         0xFF
#define LCDC_GDCCCLUTB103_U_CLUTB207_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB103_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB103_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB103_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB103_U_RESERVED_BITWIDTH    24
// GDCCCLUTB104_L Register
#define LCDC_GDCCCLUTB104_L_OFS                  0x00000F40
// CLUTB208 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB104_L_CLUTB208_MASK        0xFF
#define LCDC_GDCCCLUTB104_L_CLUTB208_SHIFT       0 
#define LCDC_GDCCCLUTB104_L_CLUTB208_BIT         0xFF
#define LCDC_GDCCCLUTB104_L_CLUTB208_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB104_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB104_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB104_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB104_L_RESERVED_BITWIDTH    24
// GDCCCLUTB104_U Register
#define LCDC_GDCCCLUTB104_U_OFS                  0x00000F44
// CLUTB209 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB104_U_CLUTB209_MASK        0xFF
#define LCDC_GDCCCLUTB104_U_CLUTB209_SHIFT       0 
#define LCDC_GDCCCLUTB104_U_CLUTB209_BIT         0xFF
#define LCDC_GDCCCLUTB104_U_CLUTB209_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB104_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB104_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB104_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB104_U_RESERVED_BITWIDTH    24
// GDCCCLUTB105_L Register
#define LCDC_GDCCCLUTB105_L_OFS                  0x00000F48
// CLUTB210 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB105_L_CLUTB210_MASK        0xFF
#define LCDC_GDCCCLUTB105_L_CLUTB210_SHIFT       0 
#define LCDC_GDCCCLUTB105_L_CLUTB210_BIT         0xFF
#define LCDC_GDCCCLUTB105_L_CLUTB210_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB105_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB105_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB105_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB105_L_RESERVED_BITWIDTH    24
// GDCCCLUTB105_U Register
#define LCDC_GDCCCLUTB105_U_OFS                  0x00000F4C
// CLUTB211 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB105_U_CLUTB211_MASK        0xFF
#define LCDC_GDCCCLUTB105_U_CLUTB211_SHIFT       0 
#define LCDC_GDCCCLUTB105_U_CLUTB211_BIT         0xFF
#define LCDC_GDCCCLUTB105_U_CLUTB211_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB105_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB105_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB105_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB105_U_RESERVED_BITWIDTH    24
// GDCCCLUTB106_L Register
#define LCDC_GDCCCLUTB106_L_OFS                  0x00000F50
// CLUTB212 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB106_L_CLUTB212_MASK        0xFF
#define LCDC_GDCCCLUTB106_L_CLUTB212_SHIFT       0 
#define LCDC_GDCCCLUTB106_L_CLUTB212_BIT         0xFF
#define LCDC_GDCCCLUTB106_L_CLUTB212_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB106_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB106_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB106_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB106_L_RESERVED_BITWIDTH    24
// GDCCCLUTB106_U Register
#define LCDC_GDCCCLUTB106_U_OFS                  0x00000F54
// CLUTB213 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB106_U_CLUTB213_MASK        0xFF
#define LCDC_GDCCCLUTB106_U_CLUTB213_SHIFT       0 
#define LCDC_GDCCCLUTB106_U_CLUTB213_BIT         0xFF
#define LCDC_GDCCCLUTB106_U_CLUTB213_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB106_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB106_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB106_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB106_U_RESERVED_BITWIDTH    24
// GDCCCLUTB107_L Register
#define LCDC_GDCCCLUTB107_L_OFS                  0x00000F58
// CLUTB214 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB107_L_CLUTB214_MASK        0xFF
#define LCDC_GDCCCLUTB107_L_CLUTB214_SHIFT       0 
#define LCDC_GDCCCLUTB107_L_CLUTB214_BIT         0xFF
#define LCDC_GDCCCLUTB107_L_CLUTB214_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB107_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB107_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB107_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB107_L_RESERVED_BITWIDTH    24
// GDCCCLUTB107_U Register
#define LCDC_GDCCCLUTB107_U_OFS                  0x00000F5C
// CLUTB215 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB107_U_CLUTB215_MASK        0xFF
#define LCDC_GDCCCLUTB107_U_CLUTB215_SHIFT       0 
#define LCDC_GDCCCLUTB107_U_CLUTB215_BIT         0xFF
#define LCDC_GDCCCLUTB107_U_CLUTB215_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB107_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB107_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB107_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB107_U_RESERVED_BITWIDTH    24
// GDCCCLUTB108_L Register
#define LCDC_GDCCCLUTB108_L_OFS                  0x00000F60
// CLUTB216 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB108_L_CLUTB216_MASK        0xFF
#define LCDC_GDCCCLUTB108_L_CLUTB216_SHIFT       0 
#define LCDC_GDCCCLUTB108_L_CLUTB216_BIT         0xFF
#define LCDC_GDCCCLUTB108_L_CLUTB216_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB108_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB108_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB108_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB108_L_RESERVED_BITWIDTH    24
// GDCCCLUTB108_U Register
#define LCDC_GDCCCLUTB108_U_OFS                  0x00000F64
// CLUTB217 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB108_U_CLUTB217_MASK        0xFF
#define LCDC_GDCCCLUTB108_U_CLUTB217_SHIFT       0 
#define LCDC_GDCCCLUTB108_U_CLUTB217_BIT         0xFF
#define LCDC_GDCCCLUTB108_U_CLUTB217_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB108_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB108_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB108_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB108_U_RESERVED_BITWIDTH    24
// GDCCCLUTB109_L Register
#define LCDC_GDCCCLUTB109_L_OFS                  0x00000F68
// CLUTB218 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB109_L_CLUTB218_MASK        0xFF
#define LCDC_GDCCCLUTB109_L_CLUTB218_SHIFT       0 
#define LCDC_GDCCCLUTB109_L_CLUTB218_BIT         0xFF
#define LCDC_GDCCCLUTB109_L_CLUTB218_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB109_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB109_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB109_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB109_L_RESERVED_BITWIDTH    24
// GDCCCLUTB109_U Register
#define LCDC_GDCCCLUTB109_U_OFS                  0x00000F6C
// CLUTB219 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB109_U_CLUTB219_MASK        0xFF
#define LCDC_GDCCCLUTB109_U_CLUTB219_SHIFT       0 
#define LCDC_GDCCCLUTB109_U_CLUTB219_BIT         0xFF
#define LCDC_GDCCCLUTB109_U_CLUTB219_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB109_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB109_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB109_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB109_U_RESERVED_BITWIDTH    24
// GDCCCLUTB110_L Register
#define LCDC_GDCCCLUTB110_L_OFS                  0x00000F70
// CLUTB220 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB110_L_CLUTB220_MASK        0xFF
#define LCDC_GDCCCLUTB110_L_CLUTB220_SHIFT       0 
#define LCDC_GDCCCLUTB110_L_CLUTB220_BIT         0xFF
#define LCDC_GDCCCLUTB110_L_CLUTB220_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB110_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB110_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB110_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB110_L_RESERVED_BITWIDTH    24
// GDCCCLUTB110_U Register
#define LCDC_GDCCCLUTB110_U_OFS                  0x00000F74
// CLUTB221 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB110_U_CLUTB221_MASK        0xFF
#define LCDC_GDCCCLUTB110_U_CLUTB221_SHIFT       0 
#define LCDC_GDCCCLUTB110_U_CLUTB221_BIT         0xFF
#define LCDC_GDCCCLUTB110_U_CLUTB221_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB110_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB110_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB110_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB110_U_RESERVED_BITWIDTH    24
// GDCCCLUTB111_L Register
#define LCDC_GDCCCLUTB111_L_OFS                  0x00000F78
// CLUTB222 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB111_L_CLUTB222_MASK        0xFF
#define LCDC_GDCCCLUTB111_L_CLUTB222_SHIFT       0 
#define LCDC_GDCCCLUTB111_L_CLUTB222_BIT         0xFF
#define LCDC_GDCCCLUTB111_L_CLUTB222_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB111_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB111_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB111_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB111_L_RESERVED_BITWIDTH    24
// GDCCCLUTB111_U Register
#define LCDC_GDCCCLUTB111_U_OFS                  0x00000F7C
// CLUTB223 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB111_U_CLUTB223_MASK        0xFF
#define LCDC_GDCCCLUTB111_U_CLUTB223_SHIFT       0 
#define LCDC_GDCCCLUTB111_U_CLUTB223_BIT         0xFF
#define LCDC_GDCCCLUTB111_U_CLUTB223_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB111_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB111_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB111_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB111_U_RESERVED_BITWIDTH    24
// GDCCCLUTB112_L Register
#define LCDC_GDCCCLUTB112_L_OFS                  0x00000F80
// CLUTB224 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB112_L_CLUTB224_MASK        0xFF
#define LCDC_GDCCCLUTB112_L_CLUTB224_SHIFT       0 
#define LCDC_GDCCCLUTB112_L_CLUTB224_BIT         0xFF
#define LCDC_GDCCCLUTB112_L_CLUTB224_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB112_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB112_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB112_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB112_L_RESERVED_BITWIDTH    24
// GDCCCLUTB112_U Register
#define LCDC_GDCCCLUTB112_U_OFS                  0x00000F84
// CLUTB225 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB112_U_CLUTB225_MASK        0xFF
#define LCDC_GDCCCLUTB112_U_CLUTB225_SHIFT       0 
#define LCDC_GDCCCLUTB112_U_CLUTB225_BIT         0xFF
#define LCDC_GDCCCLUTB112_U_CLUTB225_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB112_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB112_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB112_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB112_U_RESERVED_BITWIDTH    24
// GDCCCLUTB113_L Register
#define LCDC_GDCCCLUTB113_L_OFS                  0x00000F88
// CLUTB226 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB113_L_CLUTB226_MASK        0xFF
#define LCDC_GDCCCLUTB113_L_CLUTB226_SHIFT       0 
#define LCDC_GDCCCLUTB113_L_CLUTB226_BIT         0xFF
#define LCDC_GDCCCLUTB113_L_CLUTB226_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB113_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB113_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB113_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB113_L_RESERVED_BITWIDTH    24
// GDCCCLUTB113_U Register
#define LCDC_GDCCCLUTB113_U_OFS                  0x00000F8C
// CLUTB227 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB113_U_CLUTB227_MASK        0xFF
#define LCDC_GDCCCLUTB113_U_CLUTB227_SHIFT       0 
#define LCDC_GDCCCLUTB113_U_CLUTB227_BIT         0xFF
#define LCDC_GDCCCLUTB113_U_CLUTB227_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB113_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB113_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB113_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB113_U_RESERVED_BITWIDTH    24
// GDCCCLUTB114_L Register
#define LCDC_GDCCCLUTB114_L_OFS                  0x00000F90
// CLUTB228 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB114_L_CLUTB228_MASK        0xFF
#define LCDC_GDCCCLUTB114_L_CLUTB228_SHIFT       0 
#define LCDC_GDCCCLUTB114_L_CLUTB228_BIT         0xFF
#define LCDC_GDCCCLUTB114_L_CLUTB228_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB114_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB114_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB114_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB114_L_RESERVED_BITWIDTH    24
// GDCCCLUTB114_U Register
#define LCDC_GDCCCLUTB114_U_OFS                  0x00000F94
// CLUTB229 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB114_U_CLUTB229_MASK        0xFF
#define LCDC_GDCCCLUTB114_U_CLUTB229_SHIFT       0 
#define LCDC_GDCCCLUTB114_U_CLUTB229_BIT         0xFF
#define LCDC_GDCCCLUTB114_U_CLUTB229_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB114_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB114_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB114_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB114_U_RESERVED_BITWIDTH    24
// GDCCCLUTB115_L Register
#define LCDC_GDCCCLUTB115_L_OFS                  0x00000F98
// CLUTB230 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB115_L_CLUTB230_MASK        0xFF
#define LCDC_GDCCCLUTB115_L_CLUTB230_SHIFT       0 
#define LCDC_GDCCCLUTB115_L_CLUTB230_BIT         0xFF
#define LCDC_GDCCCLUTB115_L_CLUTB230_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB115_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB115_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB115_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB115_L_RESERVED_BITWIDTH    24
// GDCCCLUTB115_U Register
#define LCDC_GDCCCLUTB115_U_OFS                  0x00000F9C
// CLUTB231 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB115_U_CLUTB231_MASK        0xFF
#define LCDC_GDCCCLUTB115_U_CLUTB231_SHIFT       0 
#define LCDC_GDCCCLUTB115_U_CLUTB231_BIT         0xFF
#define LCDC_GDCCCLUTB115_U_CLUTB231_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB115_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB115_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB115_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB115_U_RESERVED_BITWIDTH    24
// GDCCCLUTB116_L Register
#define LCDC_GDCCCLUTB116_L_OFS                  0x00000FA0
// CLUTB232 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB116_L_CLUTB232_MASK        0xFF
#define LCDC_GDCCCLUTB116_L_CLUTB232_SHIFT       0 
#define LCDC_GDCCCLUTB116_L_CLUTB232_BIT         0xFF
#define LCDC_GDCCCLUTB116_L_CLUTB232_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB116_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB116_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB116_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB116_L_RESERVED_BITWIDTH    24
// GDCCCLUTB116_U Register
#define LCDC_GDCCCLUTB116_U_OFS                  0x00000FA4
// CLUTB233 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB116_U_CLUTB233_MASK        0xFF
#define LCDC_GDCCCLUTB116_U_CLUTB233_SHIFT       0 
#define LCDC_GDCCCLUTB116_U_CLUTB233_BIT         0xFF
#define LCDC_GDCCCLUTB116_U_CLUTB233_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB116_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB116_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB116_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB116_U_RESERVED_BITWIDTH    24
// GDCCCLUTB117_L Register
#define LCDC_GDCCCLUTB117_L_OFS                  0x00000FA8
// CLUTB234 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB117_L_CLUTB234_MASK        0xFF
#define LCDC_GDCCCLUTB117_L_CLUTB234_SHIFT       0 
#define LCDC_GDCCCLUTB117_L_CLUTB234_BIT         0xFF
#define LCDC_GDCCCLUTB117_L_CLUTB234_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB117_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB117_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB117_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB117_L_RESERVED_BITWIDTH    24
// GDCCCLUTB117_U Register
#define LCDC_GDCCCLUTB117_U_OFS                  0x00000FAC
// CLUTB235 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB117_U_CLUTB235_MASK        0xFF
#define LCDC_GDCCCLUTB117_U_CLUTB235_SHIFT       0 
#define LCDC_GDCCCLUTB117_U_CLUTB235_BIT         0xFF
#define LCDC_GDCCCLUTB117_U_CLUTB235_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB117_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB117_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB117_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB117_U_RESERVED_BITWIDTH    24
// GDCCCLUTB118_L Register
#define LCDC_GDCCCLUTB118_L_OFS                  0x00000FB0
// CLUTB236 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB118_L_CLUTB236_MASK        0xFF
#define LCDC_GDCCCLUTB118_L_CLUTB236_SHIFT       0 
#define LCDC_GDCCCLUTB118_L_CLUTB236_BIT         0xFF
#define LCDC_GDCCCLUTB118_L_CLUTB236_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB118_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB118_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB118_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB118_L_RESERVED_BITWIDTH    24
// GDCCCLUTB118_U Register
#define LCDC_GDCCCLUTB118_U_OFS                  0x00000FB4
// CLUTB237 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB118_U_CLUTB237_MASK        0xFF
#define LCDC_GDCCCLUTB118_U_CLUTB237_SHIFT       0 
#define LCDC_GDCCCLUTB118_U_CLUTB237_BIT         0xFF
#define LCDC_GDCCCLUTB118_U_CLUTB237_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB118_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB118_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB118_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB118_U_RESERVED_BITWIDTH    24
// GDCCCLUTB119_L Register
#define LCDC_GDCCCLUTB119_L_OFS                  0x00000FB8
// CLUTB238 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB119_L_CLUTB238_MASK        0xFF
#define LCDC_GDCCCLUTB119_L_CLUTB238_SHIFT       0 
#define LCDC_GDCCCLUTB119_L_CLUTB238_BIT         0xFF
#define LCDC_GDCCCLUTB119_L_CLUTB238_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB119_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB119_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB119_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB119_L_RESERVED_BITWIDTH    24
// GDCCCLUTB119_U Register
#define LCDC_GDCCCLUTB119_U_OFS                  0x00000FBC
// CLUTB239 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB119_U_CLUTB239_MASK        0xFF
#define LCDC_GDCCCLUTB119_U_CLUTB239_SHIFT       0 
#define LCDC_GDCCCLUTB119_U_CLUTB239_BIT         0xFF
#define LCDC_GDCCCLUTB119_U_CLUTB239_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB119_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB119_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB119_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB119_U_RESERVED_BITWIDTH    24
// GDCCCLUTB120_L Register
#define LCDC_GDCCCLUTB120_L_OFS                  0x00000FC0
// CLUTB240 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB120_L_CLUTB240_MASK        0xFF
#define LCDC_GDCCCLUTB120_L_CLUTB240_SHIFT       0 
#define LCDC_GDCCCLUTB120_L_CLUTB240_BIT         0xFF
#define LCDC_GDCCCLUTB120_L_CLUTB240_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB120_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB120_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB120_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB120_L_RESERVED_BITWIDTH    24
// GDCCCLUTB120_U Register
#define LCDC_GDCCCLUTB120_U_OFS                  0x00000FC4
// CLUTB241 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB120_U_CLUTB241_MASK        0xFF
#define LCDC_GDCCCLUTB120_U_CLUTB241_SHIFT       0 
#define LCDC_GDCCCLUTB120_U_CLUTB241_BIT         0xFF
#define LCDC_GDCCCLUTB120_U_CLUTB241_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB120_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB120_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB120_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB120_U_RESERVED_BITWIDTH    24
// GDCCCLUTB121_L Register
#define LCDC_GDCCCLUTB121_L_OFS                  0x00000FC8
// CLUTB242 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB121_L_CLUTB242_MASK        0xFF
#define LCDC_GDCCCLUTB121_L_CLUTB242_SHIFT       0 
#define LCDC_GDCCCLUTB121_L_CLUTB242_BIT         0xFF
#define LCDC_GDCCCLUTB121_L_CLUTB242_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB121_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB121_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB121_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB121_L_RESERVED_BITWIDTH    24
// GDCCCLUTB121_U Register
#define LCDC_GDCCCLUTB121_U_OFS                  0x00000FCC
// CLUTB243 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB121_U_CLUTB243_MASK        0xFF
#define LCDC_GDCCCLUTB121_U_CLUTB243_SHIFT       0 
#define LCDC_GDCCCLUTB121_U_CLUTB243_BIT         0xFF
#define LCDC_GDCCCLUTB121_U_CLUTB243_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB121_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB121_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB121_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB121_U_RESERVED_BITWIDTH    24
// GDCCCLUTB122_L Register
#define LCDC_GDCCCLUTB122_L_OFS                  0x00000FD0
// CLUTB244 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB122_L_CLUTB244_MASK        0xFF
#define LCDC_GDCCCLUTB122_L_CLUTB244_SHIFT       0 
#define LCDC_GDCCCLUTB122_L_CLUTB244_BIT         0xFF
#define LCDC_GDCCCLUTB122_L_CLUTB244_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB122_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB122_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB122_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB122_L_RESERVED_BITWIDTH    24
// GDCCCLUTB122_U Register
#define LCDC_GDCCCLUTB122_U_OFS                  0x00000FD4
// CLUTB245 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB122_U_CLUTB245_MASK        0xFF
#define LCDC_GDCCCLUTB122_U_CLUTB245_SHIFT       0 
#define LCDC_GDCCCLUTB122_U_CLUTB245_BIT         0xFF
#define LCDC_GDCCCLUTB122_U_CLUTB245_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB122_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB122_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB122_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB122_U_RESERVED_BITWIDTH    24
// GDCCCLUTB123_L Register
#define LCDC_GDCCCLUTB123_L_OFS                  0x00000FD8
// CLUTB246 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB123_L_CLUTB246_MASK        0xFF
#define LCDC_GDCCCLUTB123_L_CLUTB246_SHIFT       0 
#define LCDC_GDCCCLUTB123_L_CLUTB246_BIT         0xFF
#define LCDC_GDCCCLUTB123_L_CLUTB246_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB123_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB123_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB123_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB123_L_RESERVED_BITWIDTH    24
// GDCCCLUTB123_U Register
#define LCDC_GDCCCLUTB123_U_OFS                  0x00000FDC
// CLUTB247 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB123_U_CLUTB247_MASK        0xFF
#define LCDC_GDCCCLUTB123_U_CLUTB247_SHIFT       0 
#define LCDC_GDCCCLUTB123_U_CLUTB247_BIT         0xFF
#define LCDC_GDCCCLUTB123_U_CLUTB247_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB123_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB123_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB123_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB123_U_RESERVED_BITWIDTH    24
// GDCCCLUTB124_L Register
#define LCDC_GDCCCLUTB124_L_OFS                  0x00000FE0
// CLUTB248 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB124_L_CLUTB248_MASK        0xFF
#define LCDC_GDCCCLUTB124_L_CLUTB248_SHIFT       0 
#define LCDC_GDCCCLUTB124_L_CLUTB248_BIT         0xFF
#define LCDC_GDCCCLUTB124_L_CLUTB248_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB124_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB124_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB124_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB124_L_RESERVED_BITWIDTH    24
// GDCCCLUTB124_U Register
#define LCDC_GDCCCLUTB124_U_OFS                  0x00000FE4
// CLUTB249 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB124_U_CLUTB249_MASK        0xFF
#define LCDC_GDCCCLUTB124_U_CLUTB249_SHIFT       0 
#define LCDC_GDCCCLUTB124_U_CLUTB249_BIT         0xFF
#define LCDC_GDCCCLUTB124_U_CLUTB249_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB124_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB124_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB124_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB124_U_RESERVED_BITWIDTH    24
// GDCCCLUTB125_L Register
#define LCDC_GDCCCLUTB125_L_OFS                  0x00000FE8
// CLUTB250 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB125_L_CLUTB250_MASK        0xFF
#define LCDC_GDCCCLUTB125_L_CLUTB250_SHIFT       0 
#define LCDC_GDCCCLUTB125_L_CLUTB250_BIT         0xFF
#define LCDC_GDCCCLUTB125_L_CLUTB250_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB125_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB125_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB125_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB125_L_RESERVED_BITWIDTH    24
// GDCCCLUTB125_U Register
#define LCDC_GDCCCLUTB125_U_OFS                  0x00000FEC
// CLUTB251 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB125_U_CLUTB251_MASK        0xFF
#define LCDC_GDCCCLUTB125_U_CLUTB251_SHIFT       0 
#define LCDC_GDCCCLUTB125_U_CLUTB251_BIT         0xFF
#define LCDC_GDCCCLUTB125_U_CLUTB251_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB125_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB125_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB125_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB125_U_RESERVED_BITWIDTH    24
// GDCCCLUTB126_L Register
#define LCDC_GDCCCLUTB126_L_OFS                  0x00000FF0
// CLUTB252 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB126_L_CLUTB252_MASK        0xFF
#define LCDC_GDCCCLUTB126_L_CLUTB252_SHIFT       0 
#define LCDC_GDCCCLUTB126_L_CLUTB252_BIT         0xFF
#define LCDC_GDCCCLUTB126_L_CLUTB252_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB126_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB126_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB126_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB126_L_RESERVED_BITWIDTH    24
// GDCCCLUTB126_U Register
#define LCDC_GDCCCLUTB126_U_OFS                  0x00000FF4
// CLUTB253 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB126_U_CLUTB253_MASK        0xFF
#define LCDC_GDCCCLUTB126_U_CLUTB253_SHIFT       0 
#define LCDC_GDCCCLUTB126_U_CLUTB253_BIT         0xFF
#define LCDC_GDCCCLUTB126_U_CLUTB253_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB126_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB126_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB126_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB126_U_RESERVED_BITWIDTH    24
// GDCCCLUTB127_L Register
#define LCDC_GDCCCLUTB127_L_OFS                  0x00000FF8
// CLUTB254 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB127_L_CLUTB254_MASK        0xFF
#define LCDC_GDCCCLUTB127_L_CLUTB254_SHIFT       0 
#define LCDC_GDCCCLUTB127_L_CLUTB254_BIT         0xFF
#define LCDC_GDCCCLUTB127_L_CLUTB254_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB127_L_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB127_L_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB127_L_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB127_L_RESERVED_BITWIDTH    24
// GDCCCLUTB127_U Register
#define LCDC_GDCCCLUTB127_U_OFS                  0x00000FFC
// CLUTB255 bitfiled (RW) Reset=0
#define LCDC_GDCCCLUTB127_U_CLUTB255_MASK        0xFF
#define LCDC_GDCCCLUTB127_U_CLUTB255_SHIFT       0 
#define LCDC_GDCCCLUTB127_U_CLUTB255_BIT         0xFF
#define LCDC_GDCCCLUTB127_U_CLUTB255_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define LCDC_GDCCCLUTB127_U_RESERVED_MASK        0xFFFFFF00
#define LCDC_GDCCCLUTB127_U_RESERVED_SHIFT       8 
#define LCDC_GDCCCLUTB127_U_RESERVED_BIT         0xFFFFFF
#define LCDC_GDCCCLUTB127_U_RESERVED_BITWIDTH    24

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _LCDC_REG_DEF_H */
