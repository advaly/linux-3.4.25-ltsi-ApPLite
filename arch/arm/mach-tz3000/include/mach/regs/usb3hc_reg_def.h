/*
 * arch/arm/mach-tz3000/include/mach/regs/usb3hc_reg_def.h
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

#ifndef _USB3HC_REG_DEF_H
#define _USB3HC_REG_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

// CAPLENGTH Register
#define USB3HC_CAPLENGTH_OFS                     0x00000000
// CAPLENGTH bitfiled (RO) Reset=100000
#define USB3HC_CAPLENGTH_CAPLENGTH_MASK          0xFF
#define USB3HC_CAPLENGTH_CAPLENGTH_SHIFT         0 
#define USB3HC_CAPLENGTH_CAPLENGTH_BIT           0xFF
#define USB3HC_CAPLENGTH_CAPLENGTH_BITWIDTH      8
// RSVD0 bitfiled (RO) Reset=0
#define USB3HC_CAPLENGTH_RSVD0_MASK              0xFF00
#define USB3HC_CAPLENGTH_RSVD0_SHIFT             8 
#define USB3HC_CAPLENGTH_RSVD0_BIT               0xFF
#define USB3HC_CAPLENGTH_RSVD0_BITWIDTH          8
// HCIVERSION bitfiled (RO) Reset=100000000
#define USB3HC_CAPLENGTH_HCIVERSION_MASK         0xFFFF0000
#define USB3HC_CAPLENGTH_HCIVERSION_SHIFT        16 
#define USB3HC_CAPLENGTH_HCIVERSION_BIT          0xFFFF
#define USB3HC_CAPLENGTH_HCIVERSION_BITWIDTH     16
// HCSPARAMS1 Register
#define USB3HC_HCSPARAMS1_OFS                    0x00000004
// MAXSLOTS bitfiled (RO) Reset=1111111
#define USB3HC_HCSPARAMS1_MAXSLOTS_MASK          0xFF
#define USB3HC_HCSPARAMS1_MAXSLOTS_SHIFT         0 
#define USB3HC_HCSPARAMS1_MAXSLOTS_BIT           0xFF
#define USB3HC_HCSPARAMS1_MAXSLOTS_BITWIDTH      8
// MAXINTRS bitfiled (RO) Reset=1
#define USB3HC_HCSPARAMS1_MAXINTRS_MASK          0x7FF00
#define USB3HC_HCSPARAMS1_MAXINTRS_SHIFT         8 
#define USB3HC_HCSPARAMS1_MAXINTRS_BIT           0x7FF
#define USB3HC_HCSPARAMS1_MAXINTRS_BITWIDTH      11
// RSVD1 bitfiled (RO) Reset=0
#define USB3HC_HCSPARAMS1_RSVD1_MASK             0xF80000
#define USB3HC_HCSPARAMS1_RSVD1_SHIFT            19 
#define USB3HC_HCSPARAMS1_RSVD1_BIT              0x1F
#define USB3HC_HCSPARAMS1_RSVD1_BITWIDTH         5
// MAXPORTS bitfiled (RO) Reset=10
#define USB3HC_HCSPARAMS1_MAXPORTS_MASK          0xFF000000
#define USB3HC_HCSPARAMS1_MAXPORTS_SHIFT         24 
#define USB3HC_HCSPARAMS1_MAXPORTS_BIT           0xFF
#define USB3HC_HCSPARAMS1_MAXPORTS_BITWIDTH      8
// HCSPARAMS2 Register
#define USB3HC_HCSPARAMS2_OFS                    0x00000008
// IST bitfiled (RO) Reset=1
#define USB3HC_HCSPARAMS2_IST_MASK               0xF
#define USB3HC_HCSPARAMS2_IST_SHIFT              0 
#define USB3HC_HCSPARAMS2_IST_BIT                0xF
#define USB3HC_HCSPARAMS2_IST_BITWIDTH           4
// ERSTMAX bitfiled (RO) Reset=1111
#define USB3HC_HCSPARAMS2_ERSTMAX_MASK           0xF0
#define USB3HC_HCSPARAMS2_ERSTMAX_SHIFT          4 
#define USB3HC_HCSPARAMS2_ERSTMAX_BIT            0xF
#define USB3HC_HCSPARAMS2_ERSTMAX_BITWIDTH       4
// RSVD2 bitfiled (RO) Reset=0
#define USB3HC_HCSPARAMS2_RSVD2_MASK             0x1FFF00
#define USB3HC_HCSPARAMS2_RSVD2_SHIFT            8 
#define USB3HC_HCSPARAMS2_RSVD2_BIT              0x1FFF
#define USB3HC_HCSPARAMS2_RSVD2_BITWIDTH         13
// MAXSCRATCHPADBUFS_HI bitfiled (RO) Reset=0
#define USB3HC_HCSPARAMS2_MAXSCRATCHPADBUFS_HI_MASK 0x3E00000
#define USB3HC_HCSPARAMS2_MAXSCRATCHPADBUFS_HI_SHIFT 21 
#define USB3HC_HCSPARAMS2_MAXSCRATCHPADBUFS_HI_BIT 0x1F
#define USB3HC_HCSPARAMS2_MAXSCRATCHPADBUFS_HI_BITWIDTH 5
// SPR bitfiled (RO) Reset=1
#define USB3HC_HCSPARAMS2_SPR_MASK               0x4000000
#define USB3HC_HCSPARAMS2_SPR_SHIFT              26 
#define USB3HC_HCSPARAMS2_SPR_BIT                0x1
#define USB3HC_HCSPARAMS2_SPR_BITWIDTH           1
// MAXSCRATCHPADBUFS bitfiled (RO) Reset=10
#define USB3HC_HCSPARAMS2_MAXSCRATCHPADBUFS_MASK 0xF8000000
#define USB3HC_HCSPARAMS2_MAXSCRATCHPADBUFS_SHIFT 27 
#define USB3HC_HCSPARAMS2_MAXSCRATCHPADBUFS_BIT  0x1F
#define USB3HC_HCSPARAMS2_MAXSCRATCHPADBUFS_BITWIDTH 5
// HCSPARAMS3 Register
#define USB3HC_HCSPARAMS3_OFS                    0x0000000C
// U1_DEVICE_EXIT_LAT bitfiled (RO) Reset=1010
#define USB3HC_HCSPARAMS3_U1_DEVICE_EXIT_LAT_MASK 0xFF
#define USB3HC_HCSPARAMS3_U1_DEVICE_EXIT_LAT_SHIFT 0 
#define USB3HC_HCSPARAMS3_U1_DEVICE_EXIT_LAT_BIT 0xFF
#define USB3HC_HCSPARAMS3_U1_DEVICE_EXIT_LAT_BITWIDTH 8
// RSVD3 bitfiled (RO) Reset=0
#define USB3HC_HCSPARAMS3_RSVD3_MASK             0xFF00
#define USB3HC_HCSPARAMS3_RSVD3_SHIFT            8 
#define USB3HC_HCSPARAMS3_RSVD3_BIT              0xFF
#define USB3HC_HCSPARAMS3_RSVD3_BITWIDTH         8
// U2_DEVICE_EXIT_LAT bitfiled (RO) Reset=11111111111
#define USB3HC_HCSPARAMS3_U2_DEVICE_EXIT_LAT_MASK 0xFFFF0000
#define USB3HC_HCSPARAMS3_U2_DEVICE_EXIT_LAT_SHIFT 16 
#define USB3HC_HCSPARAMS3_U2_DEVICE_EXIT_LAT_BIT 0xFFFF
#define USB3HC_HCSPARAMS3_U2_DEVICE_EXIT_LAT_BITWIDTH 16
// HCCPARAMS Register
#define USB3HC_HCCPARAMS_OFS                     0x00000010
// AC64 bitfiled (RO) Reset=0
#define USB3HC_HCCPARAMS_AC64_MASK               0x1
#define USB3HC_HCCPARAMS_AC64_SHIFT              0 
#define USB3HC_HCCPARAMS_AC64_BIT                0x1
#define USB3HC_HCCPARAMS_AC64_BITWIDTH           1
// BNC bitfiled (RO) Reset=0
#define USB3HC_HCCPARAMS_BNC_MASK                0x2
#define USB3HC_HCCPARAMS_BNC_SHIFT               1 
#define USB3HC_HCCPARAMS_BNC_BIT                 0x1
#define USB3HC_HCCPARAMS_BNC_BITWIDTH            1
// CSZ bitfiled (RO) Reset=0
#define USB3HC_HCCPARAMS_CSZ_MASK                0x4
#define USB3HC_HCCPARAMS_CSZ_SHIFT               2 
#define USB3HC_HCCPARAMS_CSZ_BIT                 0x1
#define USB3HC_HCCPARAMS_CSZ_BITWIDTH            1
// PPC bitfiled (RO) Reset=0
#define USB3HC_HCCPARAMS_PPC_MASK                0x8
#define USB3HC_HCCPARAMS_PPC_SHIFT               3 
#define USB3HC_HCCPARAMS_PPC_BIT                 0x1
#define USB3HC_HCCPARAMS_PPC_BITWIDTH            1
// PIND bitfiled (RO) Reset=0
#define USB3HC_HCCPARAMS_PIND_MASK               0x10
#define USB3HC_HCCPARAMS_PIND_SHIFT              4 
#define USB3HC_HCCPARAMS_PIND_BIT                0x1
#define USB3HC_HCCPARAMS_PIND_BITWIDTH           1
// LHRC bitfiled (RO) Reset=1
#define USB3HC_HCCPARAMS_LHRC_MASK               0x20
#define USB3HC_HCCPARAMS_LHRC_SHIFT              5 
#define USB3HC_HCCPARAMS_LHRC_BIT                0x1
#define USB3HC_HCCPARAMS_LHRC_BITWIDTH           1
// LTC bitfiled (RO) Reset=1
#define USB3HC_HCCPARAMS_LTC_MASK                0x40
#define USB3HC_HCCPARAMS_LTC_SHIFT               6 
#define USB3HC_HCCPARAMS_LTC_BIT                 0x1
#define USB3HC_HCCPARAMS_LTC_BITWIDTH            1
// NSS bitfiled (RO) Reset=0
#define USB3HC_HCCPARAMS_NSS_MASK                0x80
#define USB3HC_HCCPARAMS_NSS_SHIFT               7 
#define USB3HC_HCCPARAMS_NSS_BIT                 0x1
#define USB3HC_HCCPARAMS_NSS_BITWIDTH            1
// PAE bitfiled (RO) Reset=0
#define USB3HC_HCCPARAMS_PAE_MASK                0x100
#define USB3HC_HCCPARAMS_PAE_SHIFT               8 
#define USB3HC_HCCPARAMS_PAE_BIT                 0x1
#define USB3HC_HCCPARAMS_PAE_BITWIDTH            1
// RSVD3 bitfiled (RO) Reset=0
#define USB3HC_HCCPARAMS_RSVD3_MASK              0xE00
#define USB3HC_HCCPARAMS_RSVD3_SHIFT             9 
#define USB3HC_HCCPARAMS_RSVD3_BIT               0x7
#define USB3HC_HCCPARAMS_RSVD3_BITWIDTH          3
// MAXPSASIZE bitfiled (RO) Reset=1111
#define USB3HC_HCCPARAMS_MAXPSASIZE_MASK         0xF000
#define USB3HC_HCCPARAMS_MAXPSASIZE_SHIFT        12 
#define USB3HC_HCCPARAMS_MAXPSASIZE_BIT          0xF
#define USB3HC_HCCPARAMS_MAXPSASIZE_BITWIDTH     4
// XECP bitfiled (RO) Reset=1000100000
#define USB3HC_HCCPARAMS_XECP_MASK               0xFFFF0000
#define USB3HC_HCCPARAMS_XECP_SHIFT              16 
#define USB3HC_HCCPARAMS_XECP_BIT                0xFFFF
#define USB3HC_HCCPARAMS_XECP_BITWIDTH           16
// DBOFF Register
#define USB3HC_DBOFF_OFS                         0x00000014
// RSVD4 bitfiled (RO) Reset=0
#define USB3HC_DBOFF_RSVD4_MASK                  0x3
#define USB3HC_DBOFF_RSVD4_SHIFT                 0 
#define USB3HC_DBOFF_RSVD4_BIT                   0x3
#define USB3HC_DBOFF_RSVD4_BITWIDTH              2
// DOORBELL_ARRAY_OFFSET bitfiled (RO) Reset=100100000
#define USB3HC_DBOFF_DOORBELL_ARRAY_OFFSET_MASK  0xFFFFFFFC
#define USB3HC_DBOFF_DOORBELL_ARRAY_OFFSET_SHIFT 2 
#define USB3HC_DBOFF_DOORBELL_ARRAY_OFFSET_BIT   0x3FFFFFFF
#define USB3HC_DBOFF_DOORBELL_ARRAY_OFFSET_BITWIDTH 30
// RTSOFF Register
#define USB3HC_RTSOFF_OFS                        0x00000018
// RSVD5 bitfiled (RO) Reset=0
#define USB3HC_RTSOFF_RSVD5_MASK                 0x1F
#define USB3HC_RTSOFF_RSVD5_SHIFT                0 
#define USB3HC_RTSOFF_RSVD5_BIT                  0x1F
#define USB3HC_RTSOFF_RSVD5_BITWIDTH             5
// RUNTIME_REG_SPACE_OFFSET bitfiled (RO) Reset=100010
#define USB3HC_RTSOFF_RUNTIME_REG_SPACE_OFFSET_MASK 0xFFFFFFE0
#define USB3HC_RTSOFF_RUNTIME_REG_SPACE_OFFSET_SHIFT 5 
#define USB3HC_RTSOFF_RUNTIME_REG_SPACE_OFFSET_BIT 0x7FFFFFF
#define USB3HC_RTSOFF_RUNTIME_REG_SPACE_OFFSET_BITWIDTH 27
// USBCMD Register
#define USB3HC_USBCMD_OFS                        0x00000020
// R_S bitfiled (RW) Reset=0
#define USB3HC_USBCMD_R_S_MASK                   0x1
#define USB3HC_USBCMD_R_S_SHIFT                  0 
#define USB3HC_USBCMD_R_S_BIT                    0x1
#define USB3HC_USBCMD_R_S_BITWIDTH               1
// HCRST bitfiled (RW) Reset=0
#define USB3HC_USBCMD_HCRST_MASK                 0x2
#define USB3HC_USBCMD_HCRST_SHIFT                1 
#define USB3HC_USBCMD_HCRST_BIT                  0x1
#define USB3HC_USBCMD_HCRST_BITWIDTH             1
// INTE bitfiled (RW) Reset=0
#define USB3HC_USBCMD_INTE_MASK                  0x4
#define USB3HC_USBCMD_INTE_SHIFT                 2 
#define USB3HC_USBCMD_INTE_BIT                   0x1
#define USB3HC_USBCMD_INTE_BITWIDTH              1
// HSEE bitfiled (RW) Reset=0
#define USB3HC_USBCMD_HSEE_MASK                  0x8
#define USB3HC_USBCMD_HSEE_SHIFT                 3 
#define USB3HC_USBCMD_HSEE_BIT                   0x1
#define USB3HC_USBCMD_HSEE_BITWIDTH              1
// RSVD7 bitfiled (RO) Reset=0
#define USB3HC_USBCMD_RSVD7_MASK                 0x70
#define USB3HC_USBCMD_RSVD7_SHIFT                4 
#define USB3HC_USBCMD_RSVD7_BIT                  0x7
#define USB3HC_USBCMD_RSVD7_BITWIDTH             3
// LHCRST bitfiled (RW) Reset=1
#define USB3HC_USBCMD_LHCRST_MASK                0x80
#define USB3HC_USBCMD_LHCRST_SHIFT               7 
#define USB3HC_USBCMD_LHCRST_BIT                 0x1
#define USB3HC_USBCMD_LHCRST_BITWIDTH            1
// CSS bitfiled (RW) Reset=1
#define USB3HC_USBCMD_CSS_MASK                   0x100
#define USB3HC_USBCMD_CSS_SHIFT                  8 
#define USB3HC_USBCMD_CSS_BIT                    0x1
#define USB3HC_USBCMD_CSS_BITWIDTH               1
// CRS bitfiled (RW) Reset=0
#define USB3HC_USBCMD_CRS_MASK                   0x200
#define USB3HC_USBCMD_CRS_SHIFT                  9 
#define USB3HC_USBCMD_CRS_BIT                    0x1
#define USB3HC_USBCMD_CRS_BITWIDTH               1
// EWE bitfiled (RW) Reset=0
#define USB3HC_USBCMD_EWE_MASK                   0x400
#define USB3HC_USBCMD_EWE_SHIFT                  10 
#define USB3HC_USBCMD_EWE_BIT                    0x1
#define USB3HC_USBCMD_EWE_BITWIDTH               1
// EU3S bitfiled (RW) Reset=0
#define USB3HC_USBCMD_EU3S_MASK                  0x800
#define USB3HC_USBCMD_EU3S_SHIFT                 11 
#define USB3HC_USBCMD_EU3S_BIT                   0x1
#define USB3HC_USBCMD_EU3S_BITWIDTH              1
// RSVD8 bitfiled (RO) Reset=1111
#define USB3HC_USBCMD_RSVD8_MASK                 0xFFFFF000
#define USB3HC_USBCMD_RSVD8_SHIFT                12 
#define USB3HC_USBCMD_RSVD8_BIT                  0xFFFFF
#define USB3HC_USBCMD_RSVD8_BITWIDTH             20
// USBSTS Register
#define USB3HC_USBSTS_OFS                        0x00000024
// HCH bitfiled (RO) Reset=1
#define USB3HC_USBSTS_HCH_MASK                   0x1
#define USB3HC_USBSTS_HCH_SHIFT                  0 
#define USB3HC_USBSTS_HCH_BIT                    0x1
#define USB3HC_USBSTS_HCH_BITWIDTH               1
// RSVD9 bitfiled (RO) Reset=0
#define USB3HC_USBSTS_RSVD9_MASK                 0x2
#define USB3HC_USBSTS_RSVD9_SHIFT                1 
#define USB3HC_USBSTS_RSVD9_BIT                  0x1
#define USB3HC_USBSTS_RSVD9_BITWIDTH             1
// HSE bitfiled (RW) Reset=0
#define USB3HC_USBSTS_HSE_MASK                   0x4
#define USB3HC_USBSTS_HSE_SHIFT                  2 
#define USB3HC_USBSTS_HSE_BIT                    0x1
#define USB3HC_USBSTS_HSE_BITWIDTH               1
// EINT bitfiled (RW) Reset=0
#define USB3HC_USBSTS_EINT_MASK                  0x8
#define USB3HC_USBSTS_EINT_SHIFT                 3 
#define USB3HC_USBSTS_EINT_BIT                   0x1
#define USB3HC_USBSTS_EINT_BITWIDTH              1
// PCD bitfiled (RW) Reset=0
#define USB3HC_USBSTS_PCD_MASK                   0x10
#define USB3HC_USBSTS_PCD_SHIFT                  4 
#define USB3HC_USBSTS_PCD_BIT                    0x1
#define USB3HC_USBSTS_PCD_BITWIDTH               1
// RSVD10 bitfiled (RO) Reset=0
#define USB3HC_USBSTS_RSVD10_MASK                0xE0
#define USB3HC_USBSTS_RSVD10_SHIFT               5 
#define USB3HC_USBSTS_RSVD10_BIT                 0x7
#define USB3HC_USBSTS_RSVD10_BITWIDTH            3
// SSS bitfiled (RO) Reset=0
#define USB3HC_USBSTS_SSS_MASK                   0x100
#define USB3HC_USBSTS_SSS_SHIFT                  8 
#define USB3HC_USBSTS_SSS_BIT                    0x1
#define USB3HC_USBSTS_SSS_BITWIDTH               1
// RSS bitfiled (RO) Reset=0
#define USB3HC_USBSTS_RSS_MASK                   0x200
#define USB3HC_USBSTS_RSS_SHIFT                  9 
#define USB3HC_USBSTS_RSS_BIT                    0x1
#define USB3HC_USBSTS_RSS_BITWIDTH               1
// SRE bitfiled (RW) Reset=0
#define USB3HC_USBSTS_SRE_MASK                   0x400
#define USB3HC_USBSTS_SRE_SHIFT                  10 
#define USB3HC_USBSTS_SRE_BIT                    0x1
#define USB3HC_USBSTS_SRE_BITWIDTH               1
// CNR bitfiled (RO) Reset=1
#define USB3HC_USBSTS_CNR_MASK                   0x800
#define USB3HC_USBSTS_CNR_SHIFT                  11 
#define USB3HC_USBSTS_CNR_BIT                    0x1
#define USB3HC_USBSTS_CNR_BITWIDTH               1
// HCE bitfiled (RO) Reset=0
#define USB3HC_USBSTS_HCE_MASK                   0x1000
#define USB3HC_USBSTS_HCE_SHIFT                  12 
#define USB3HC_USBSTS_HCE_BIT                    0x1
#define USB3HC_USBSTS_HCE_BITWIDTH               1
// RSVD11 bitfiled (RO) Reset=0
#define USB3HC_USBSTS_RSVD11_MASK                0xFFFFE000
#define USB3HC_USBSTS_RSVD11_SHIFT               13 
#define USB3HC_USBSTS_RSVD11_BIT                 0x7FFFF
#define USB3HC_USBSTS_RSVD11_BITWIDTH            19
// PAGESIZE Register
#define USB3HC_PAGESIZE_OFS                      0x00000028
// PAGE_SIZE bitfiled (RO) Reset=1
#define USB3HC_PAGESIZE_PAGE_SIZE_MASK           0xFFFF
#define USB3HC_PAGESIZE_PAGE_SIZE_SHIFT          0 
#define USB3HC_PAGESIZE_PAGE_SIZE_BIT            0xFFFF
#define USB3HC_PAGESIZE_PAGE_SIZE_BITWIDTH       16
// RSVD12 bitfiled (RO) Reset=0
#define USB3HC_PAGESIZE_RSVD12_MASK              0xFFFF0000
#define USB3HC_PAGESIZE_RSVD12_SHIFT             16 
#define USB3HC_PAGESIZE_RSVD12_BIT               0xFFFF
#define USB3HC_PAGESIZE_RSVD12_BITWIDTH          16
// DNCTRL Register
#define USB3HC_DNCTRL_OFS                        0x00000034
// N0_N15 bitfiled (RW) Reset=0
#define USB3HC_DNCTRL_N0_N15_MASK                0xFFFF
#define USB3HC_DNCTRL_N0_N15_SHIFT               0 
#define USB3HC_DNCTRL_N0_N15_BIT                 0xFFFF
#define USB3HC_DNCTRL_N0_N15_BITWIDTH            16
// RSVD13 bitfiled (RO) Reset=0
#define USB3HC_DNCTRL_RSVD13_MASK                0xFFFF0000
#define USB3HC_DNCTRL_RSVD13_SHIFT               16 
#define USB3HC_DNCTRL_RSVD13_BIT                 0xFFFF
#define USB3HC_DNCTRL_RSVD13_BITWIDTH            16
// CRCR_LO Register
#define USB3HC_CRCR_LO_OFS                       0x00000038
// RCS bitfiled (RW) Reset=0
#define USB3HC_CRCR_LO_RCS_MASK                  0x1
#define USB3HC_CRCR_LO_RCS_SHIFT                 0 
#define USB3HC_CRCR_LO_RCS_BIT                   0x1
#define USB3HC_CRCR_LO_RCS_BITWIDTH              1
// CS bitfiled (RW) Reset=0
#define USB3HC_CRCR_LO_CS_MASK                   0x2
#define USB3HC_CRCR_LO_CS_SHIFT                  1 
#define USB3HC_CRCR_LO_CS_BIT                    0x1
#define USB3HC_CRCR_LO_CS_BITWIDTH               1
// CA bitfiled (RW) Reset=0
#define USB3HC_CRCR_LO_CA_MASK                   0x4
#define USB3HC_CRCR_LO_CA_SHIFT                  2 
#define USB3HC_CRCR_LO_CA_BIT                    0x1
#define USB3HC_CRCR_LO_CA_BITWIDTH               1
// CRR bitfiled (RW) Reset=0
#define USB3HC_CRCR_LO_CRR_MASK                  0x8
#define USB3HC_CRCR_LO_CRR_SHIFT                 3 
#define USB3HC_CRCR_LO_CRR_BIT                   0x1
#define USB3HC_CRCR_LO_CRR_BITWIDTH              1
// RSVD14 bitfiled (RO) Reset=0
#define USB3HC_CRCR_LO_RSVD14_MASK               0x30
#define USB3HC_CRCR_LO_RSVD14_SHIFT              4 
#define USB3HC_CRCR_LO_RSVD14_BIT                0x3
#define USB3HC_CRCR_LO_RSVD14_BITWIDTH           2
// CMD_RING_PNTR bitfiled (RW) Reset=0
#define USB3HC_CRCR_LO_CMD_RING_PNTR_MASK        0xFFFFFFC0
#define USB3HC_CRCR_LO_CMD_RING_PNTR_SHIFT       6 
#define USB3HC_CRCR_LO_CMD_RING_PNTR_BIT         0x3FFFFFF
#define USB3HC_CRCR_LO_CMD_RING_PNTR_BITWIDTH    26
// CRCR_HI Register
#define USB3HC_CRCR_HI_OFS                       0x0000003C
// CMD_RING_PNTR bitfiled (RW) Reset=0
#define USB3HC_CRCR_HI_CMD_RING_PNTR_MASK        0xFFFFFFFF
#define USB3HC_CRCR_HI_CMD_RING_PNTR_SHIFT       0 
#define USB3HC_CRCR_HI_CMD_RING_PNTR_BIT         0xFFFFFFFF
#define USB3HC_CRCR_HI_CMD_RING_PNTR_BITWIDTH    32
// DCBAAP_LO Register
#define USB3HC_DCBAAP_LO_OFS                     0x00000050
// RSVD16 bitfiled (RO) Reset=0
#define USB3HC_DCBAAP_LO_RSVD16_MASK             0x3F
#define USB3HC_DCBAAP_LO_RSVD16_SHIFT            0 
#define USB3HC_DCBAAP_LO_RSVD16_BIT              0x3F
#define USB3HC_DCBAAP_LO_RSVD16_BITWIDTH         6
// DEVICE_CONTEXT_BAAP bitfiled (RW) Reset=0
#define USB3HC_DCBAAP_LO_DEVICE_CONTEXT_BAAP_MASK 0xFFFFFFC0
#define USB3HC_DCBAAP_LO_DEVICE_CONTEXT_BAAP_SHIFT 6 
#define USB3HC_DCBAAP_LO_DEVICE_CONTEXT_BAAP_BIT 0x3FFFFFF
#define USB3HC_DCBAAP_LO_DEVICE_CONTEXT_BAAP_BITWIDTH 26
// DCBAAP_HI Register
#define USB3HC_DCBAAP_HI_OFS                     0x00000054
// DEVICE_CONTEXT_BAAP bitfiled (RW) Reset=0
#define USB3HC_DCBAAP_HI_DEVICE_CONTEXT_BAAP_MASK 0xFFFFFFFF
#define USB3HC_DCBAAP_HI_DEVICE_CONTEXT_BAAP_SHIFT 0 
#define USB3HC_DCBAAP_HI_DEVICE_CONTEXT_BAAP_BIT 0xFFFFFFFF
#define USB3HC_DCBAAP_HI_DEVICE_CONTEXT_BAAP_BITWIDTH 32
// CONFIG Register
#define USB3HC_CONFIG_OFS                        0x00000058
// MAXSLOTSEN bitfiled (RW) Reset=0
#define USB3HC_CONFIG_MAXSLOTSEN_MASK            0xFF
#define USB3HC_CONFIG_MAXSLOTSEN_SHIFT           0 
#define USB3HC_CONFIG_MAXSLOTSEN_BIT             0xFF
#define USB3HC_CONFIG_MAXSLOTSEN_BITWIDTH        8
// RSVD17 bitfiled (RO) Reset=0
#define USB3HC_CONFIG_RSVD17_MASK                0xFFFFFF00
#define USB3HC_CONFIG_RSVD17_SHIFT               8 
#define USB3HC_CONFIG_RSVD17_BIT                 0xFFFFFF
#define USB3HC_CONFIG_RSVD17_BITWIDTH            24
// PORTSC_0 Register
#define USB3HC_PORTSC_0_OFS                      0x00000420
// CCS bitfiled (RO) Reset=0
#define USB3HC_PORTSC_0_CCS_MASK                 0x1
#define USB3HC_PORTSC_0_CCS_SHIFT                0 
#define USB3HC_PORTSC_0_CCS_BIT                  0x1
#define USB3HC_PORTSC_0_CCS_BITWIDTH             1
// PED bitfiled (RW) Reset=0
#define USB3HC_PORTSC_0_PED_MASK                 0x2
#define USB3HC_PORTSC_0_PED_SHIFT                1 
#define USB3HC_PORTSC_0_PED_BIT                  0x1
#define USB3HC_PORTSC_0_PED_BITWIDTH             1
// RSVD18 bitfiled (RO) Reset=0
#define USB3HC_PORTSC_0_RSVD18_MASK              0x4
#define USB3HC_PORTSC_0_RSVD18_SHIFT             2 
#define USB3HC_PORTSC_0_RSVD18_BIT               0x1
#define USB3HC_PORTSC_0_RSVD18_BITWIDTH          1
// OCA bitfiled (RW) Reset=0
#define USB3HC_PORTSC_0_OCA_MASK                 0x8
#define USB3HC_PORTSC_0_OCA_SHIFT                3 
#define USB3HC_PORTSC_0_OCA_BIT                  0x1
#define USB3HC_PORTSC_0_OCA_BITWIDTH             1
// PR bitfiled (RW) Reset=0
#define USB3HC_PORTSC_0_PR_MASK                  0x10
#define USB3HC_PORTSC_0_PR_SHIFT                 4 
#define USB3HC_PORTSC_0_PR_BIT                   0x1
#define USB3HC_PORTSC_0_PR_BITWIDTH              1
// PLS bitfiled (RW) Reset=101
#define USB3HC_PORTSC_0_PLS_MASK                 0x1E0
#define USB3HC_PORTSC_0_PLS_SHIFT                5 
#define USB3HC_PORTSC_0_PLS_BIT                  0xF
#define USB3HC_PORTSC_0_PLS_BITWIDTH             4
// PP bitfiled (RW) Reset=1
#define USB3HC_PORTSC_0_PP_MASK                  0x200
#define USB3HC_PORTSC_0_PP_SHIFT                 9 
#define USB3HC_PORTSC_0_PP_BIT                   0x1
#define USB3HC_PORTSC_0_PP_BITWIDTH              1
// PORTSPEED bitfiled (RO) Reset=0
#define USB3HC_PORTSC_0_PORTSPEED_MASK           0x3C00
#define USB3HC_PORTSC_0_PORTSPEED_SHIFT          10 
#define USB3HC_PORTSC_0_PORTSPEED_BIT            0xF
#define USB3HC_PORTSC_0_PORTSPEED_BITWIDTH       4
// PIC bitfiled (RW) Reset=0
#define USB3HC_PORTSC_0_PIC_MASK                 0xC000
#define USB3HC_PORTSC_0_PIC_SHIFT                14 
#define USB3HC_PORTSC_0_PIC_BIT                  0x3
#define USB3HC_PORTSC_0_PIC_BITWIDTH             2
// LWS bitfiled (RW) Reset=0
#define USB3HC_PORTSC_0_LWS_MASK                 0x10000
#define USB3HC_PORTSC_0_LWS_SHIFT                16 
#define USB3HC_PORTSC_0_LWS_BIT                  0x1
#define USB3HC_PORTSC_0_LWS_BITWIDTH             1
// CSC bitfiled (RW) Reset=0
#define USB3HC_PORTSC_0_CSC_MASK                 0x20000
#define USB3HC_PORTSC_0_CSC_SHIFT                17 
#define USB3HC_PORTSC_0_CSC_BIT                  0x1
#define USB3HC_PORTSC_0_CSC_BITWIDTH             1
// PEC bitfiled (RW) Reset=1
#define USB3HC_PORTSC_0_PEC_MASK                 0x40000
#define USB3HC_PORTSC_0_PEC_SHIFT                18 
#define USB3HC_PORTSC_0_PEC_BIT                  0x1
#define USB3HC_PORTSC_0_PEC_BITWIDTH             1
// WRC bitfiled (RW) Reset=0
#define USB3HC_PORTSC_0_WRC_MASK                 0x80000
#define USB3HC_PORTSC_0_WRC_SHIFT                19 
#define USB3HC_PORTSC_0_WRC_BIT                  0x1
#define USB3HC_PORTSC_0_WRC_BITWIDTH             1
// OCC bitfiled (RW) Reset=0
#define USB3HC_PORTSC_0_OCC_MASK                 0x100000
#define USB3HC_PORTSC_0_OCC_SHIFT                20 
#define USB3HC_PORTSC_0_OCC_BIT                  0x1
#define USB3HC_PORTSC_0_OCC_BITWIDTH             1
// PRC bitfiled (RW) Reset=0
#define USB3HC_PORTSC_0_PRC_MASK                 0x200000
#define USB3HC_PORTSC_0_PRC_SHIFT                21 
#define USB3HC_PORTSC_0_PRC_BIT                  0x1
#define USB3HC_PORTSC_0_PRC_BITWIDTH             1
// PLC bitfiled (RW) Reset=0
#define USB3HC_PORTSC_0_PLC_MASK                 0x400000
#define USB3HC_PORTSC_0_PLC_SHIFT                22 
#define USB3HC_PORTSC_0_PLC_BIT                  0x1
#define USB3HC_PORTSC_0_PLC_BITWIDTH             1
// CEC bitfiled (RW) Reset=0
#define USB3HC_PORTSC_0_CEC_MASK                 0x800000
#define USB3HC_PORTSC_0_CEC_SHIFT                23 
#define USB3HC_PORTSC_0_CEC_BIT                  0x1
#define USB3HC_PORTSC_0_CEC_BITWIDTH             1
// CAS bitfiled (RO) Reset=0
#define USB3HC_PORTSC_0_CAS_MASK                 0x1000000
#define USB3HC_PORTSC_0_CAS_SHIFT                24 
#define USB3HC_PORTSC_0_CAS_BIT                  0x1
#define USB3HC_PORTSC_0_CAS_BITWIDTH             1
// WCE bitfiled (RW) Reset=0
#define USB3HC_PORTSC_0_WCE_MASK                 0x2000000
#define USB3HC_PORTSC_0_WCE_SHIFT                25 
#define USB3HC_PORTSC_0_WCE_BIT                  0x1
#define USB3HC_PORTSC_0_WCE_BITWIDTH             1
// WDE bitfiled (RW) Reset=0
#define USB3HC_PORTSC_0_WDE_MASK                 0x4000000
#define USB3HC_PORTSC_0_WDE_SHIFT                26 
#define USB3HC_PORTSC_0_WDE_BIT                  0x1
#define USB3HC_PORTSC_0_WDE_BITWIDTH             1
// WOE bitfiled (RW) Reset=1
#define USB3HC_PORTSC_0_WOE_MASK                 0x8000000
#define USB3HC_PORTSC_0_WOE_SHIFT                27 
#define USB3HC_PORTSC_0_WOE_BIT                  0x1
#define USB3HC_PORTSC_0_WOE_BITWIDTH             1
// RSVD20 bitfiled (RO) Reset=0
#define USB3HC_PORTSC_0_RSVD20_MASK              0x30000000
#define USB3HC_PORTSC_0_RSVD20_SHIFT             28 
#define USB3HC_PORTSC_0_RSVD20_BIT               0x3
#define USB3HC_PORTSC_0_RSVD20_BITWIDTH          2
// DR bitfiled (RW) Reset=0
#define USB3HC_PORTSC_0_DR_MASK                  0x40000000
#define USB3HC_PORTSC_0_DR_SHIFT                 30 
#define USB3HC_PORTSC_0_DR_BIT                   0x1
#define USB3HC_PORTSC_0_DR_BITWIDTH              1
// WPR bitfiled (RW) Reset=0
#define USB3HC_PORTSC_0_WPR_MASK                 0x80000000
#define USB3HC_PORTSC_0_WPR_SHIFT                31 
#define USB3HC_PORTSC_0_WPR_BIT                  0x1
#define USB3HC_PORTSC_0_WPR_BITWIDTH             1
// PORTPMSC_20_0 Register
#define USB3HC_PORTPMSC_20_0_OFS                 0x00000424
// L1S bitfiled (RO) Reset=0
#define USB3HC_PORTPMSC_20_0_L1S_MASK            0x7
#define USB3HC_PORTPMSC_20_0_L1S_SHIFT           0 
#define USB3HC_PORTPMSC_20_0_L1S_BIT             0x7
#define USB3HC_PORTPMSC_20_0_L1S_BITWIDTH        3
// PWE bitfiled (RW) Reset=0
#define USB3HC_PORTPMSC_20_0_PWE_MASK            0x8
#define USB3HC_PORTPMSC_20_0_PWE_SHIFT           3 
#define USB3HC_PORTPMSC_20_0_PWE_BIT             0x1
#define USB3HC_PORTPMSC_20_0_PWE_BITWIDTH        1
// HIRD bitfiled (RW) Reset=0
#define USB3HC_PORTPMSC_20_0_HIRD_MASK           0xF0
#define USB3HC_PORTPMSC_20_0_HIRD_SHIFT          4 
#define USB3HC_PORTPMSC_20_0_HIRD_BIT            0xF
#define USB3HC_PORTPMSC_20_0_HIRD_BITWIDTH       4
// L1DSLOT bitfiled (RW) Reset=0
#define USB3HC_PORTPMSC_20_0_L1DSLOT_MASK        0xFF00
#define USB3HC_PORTPMSC_20_0_L1DSLOT_SHIFT       8 
#define USB3HC_PORTPMSC_20_0_L1DSLOT_BIT         0xFF
#define USB3HC_PORTPMSC_20_0_L1DSLOT_BITWIDTH    8
// HLE bitfiled (RW) Reset=0
#define USB3HC_PORTPMSC_20_0_HLE_MASK            0x10000
#define USB3HC_PORTPMSC_20_0_HLE_SHIFT           16 
#define USB3HC_PORTPMSC_20_0_HLE_BIT             0x1
#define USB3HC_PORTPMSC_20_0_HLE_BITWIDTH        1
// Rsvd10 bitfiled (RO) Reset=0
#define USB3HC_PORTPMSC_20_0_RSVD10_MASK         0xFFE0000
#define USB3HC_PORTPMSC_20_0_RSVD10_SHIFT        17 
#define USB3HC_PORTPMSC_20_0_RSVD10_BIT          0x7FF
#define USB3HC_PORTPMSC_20_0_RSVD10_BITWIDTH     11
// PRTTSTCTRL bitfiled (RW) Reset=0
#define USB3HC_PORTPMSC_20_0_PRTTSTCTRL_MASK     0xF0000000
#define USB3HC_PORTPMSC_20_0_PRTTSTCTRL_SHIFT    28 
#define USB3HC_PORTPMSC_20_0_PRTTSTCTRL_BIT      0xF
#define USB3HC_PORTPMSC_20_0_PRTTSTCTRL_BITWIDTH 4
// PORTLI_0 Register
#define USB3HC_PORTLI_0_OFS                      0x00000428
// LINK_ERROR_COUNT bitfiled (RO) Reset=0
#define USB3HC_PORTLI_0_LINK_ERROR_COUNT_MASK    0xFFFF
#define USB3HC_PORTLI_0_LINK_ERROR_COUNT_SHIFT   0 
#define USB3HC_PORTLI_0_LINK_ERROR_COUNT_BIT     0xFFFF
#define USB3HC_PORTLI_0_LINK_ERROR_COUNT_BITWIDTH 16
// RSVD22 bitfiled (RO) Reset=0
#define USB3HC_PORTLI_0_RSVD22_MASK              0xFFFF0000
#define USB3HC_PORTLI_0_RSVD22_SHIFT             16 
#define USB3HC_PORTLI_0_RSVD22_BIT               0xFFFF
#define USB3HC_PORTLI_0_RSVD22_BITWIDTH          16
// PORTSC_1 Register
#define USB3HC_PORTSC_1_OFS                      0x00000430
// CCS bitfiled (RO) Reset=0
#define USB3HC_PORTSC_1_CCS_MASK                 0x1
#define USB3HC_PORTSC_1_CCS_SHIFT                0 
#define USB3HC_PORTSC_1_CCS_BIT                  0x1
#define USB3HC_PORTSC_1_CCS_BITWIDTH             1
// PED bitfiled (RW) Reset=0
#define USB3HC_PORTSC_1_PED_MASK                 0x2
#define USB3HC_PORTSC_1_PED_SHIFT                1 
#define USB3HC_PORTSC_1_PED_BIT                  0x1
#define USB3HC_PORTSC_1_PED_BITWIDTH             1
// RSVD18 bitfiled (RO) Reset=0
#define USB3HC_PORTSC_1_RSVD18_MASK              0x4
#define USB3HC_PORTSC_1_RSVD18_SHIFT             2 
#define USB3HC_PORTSC_1_RSVD18_BIT               0x1
#define USB3HC_PORTSC_1_RSVD18_BITWIDTH          1
// OCA bitfiled (RW) Reset=0
#define USB3HC_PORTSC_1_OCA_MASK                 0x8
#define USB3HC_PORTSC_1_OCA_SHIFT                3 
#define USB3HC_PORTSC_1_OCA_BIT                  0x1
#define USB3HC_PORTSC_1_OCA_BITWIDTH             1
// PR bitfiled (RW) Reset=0
#define USB3HC_PORTSC_1_PR_MASK                  0x10
#define USB3HC_PORTSC_1_PR_SHIFT                 4 
#define USB3HC_PORTSC_1_PR_BIT                   0x1
#define USB3HC_PORTSC_1_PR_BITWIDTH              1
// PLS bitfiled (RW) Reset=101
#define USB3HC_PORTSC_1_PLS_MASK                 0x1E0
#define USB3HC_PORTSC_1_PLS_SHIFT                5 
#define USB3HC_PORTSC_1_PLS_BIT                  0xF
#define USB3HC_PORTSC_1_PLS_BITWIDTH             4
// PP bitfiled (RW) Reset=1
#define USB3HC_PORTSC_1_PP_MASK                  0x200
#define USB3HC_PORTSC_1_PP_SHIFT                 9 
#define USB3HC_PORTSC_1_PP_BIT                   0x1
#define USB3HC_PORTSC_1_PP_BITWIDTH              1
// PORTSPEED bitfiled (RO) Reset=0
#define USB3HC_PORTSC_1_PORTSPEED_MASK           0x3C00
#define USB3HC_PORTSC_1_PORTSPEED_SHIFT          10 
#define USB3HC_PORTSC_1_PORTSPEED_BIT            0xF
#define USB3HC_PORTSC_1_PORTSPEED_BITWIDTH       4
// PIC bitfiled (RW) Reset=0
#define USB3HC_PORTSC_1_PIC_MASK                 0xC000
#define USB3HC_PORTSC_1_PIC_SHIFT                14 
#define USB3HC_PORTSC_1_PIC_BIT                  0x3
#define USB3HC_PORTSC_1_PIC_BITWIDTH             2
// LWS bitfiled (RW) Reset=0
#define USB3HC_PORTSC_1_LWS_MASK                 0x10000
#define USB3HC_PORTSC_1_LWS_SHIFT                16 
#define USB3HC_PORTSC_1_LWS_BIT                  0x1
#define USB3HC_PORTSC_1_LWS_BITWIDTH             1
// CSC bitfiled (RW) Reset=0
#define USB3HC_PORTSC_1_CSC_MASK                 0x20000
#define USB3HC_PORTSC_1_CSC_SHIFT                17 
#define USB3HC_PORTSC_1_CSC_BIT                  0x1
#define USB3HC_PORTSC_1_CSC_BITWIDTH             1
// PEC bitfiled (RW) Reset=1
#define USB3HC_PORTSC_1_PEC_MASK                 0x40000
#define USB3HC_PORTSC_1_PEC_SHIFT                18 
#define USB3HC_PORTSC_1_PEC_BIT                  0x1
#define USB3HC_PORTSC_1_PEC_BITWIDTH             1
// WRC bitfiled (RW) Reset=0
#define USB3HC_PORTSC_1_WRC_MASK                 0x80000
#define USB3HC_PORTSC_1_WRC_SHIFT                19 
#define USB3HC_PORTSC_1_WRC_BIT                  0x1
#define USB3HC_PORTSC_1_WRC_BITWIDTH             1
// OCC bitfiled (RW) Reset=0
#define USB3HC_PORTSC_1_OCC_MASK                 0x100000
#define USB3HC_PORTSC_1_OCC_SHIFT                20 
#define USB3HC_PORTSC_1_OCC_BIT                  0x1
#define USB3HC_PORTSC_1_OCC_BITWIDTH             1
// PRC bitfiled (RW) Reset=0
#define USB3HC_PORTSC_1_PRC_MASK                 0x200000
#define USB3HC_PORTSC_1_PRC_SHIFT                21 
#define USB3HC_PORTSC_1_PRC_BIT                  0x1
#define USB3HC_PORTSC_1_PRC_BITWIDTH             1
// PLC bitfiled (RW) Reset=0
#define USB3HC_PORTSC_1_PLC_MASK                 0x400000
#define USB3HC_PORTSC_1_PLC_SHIFT                22 
#define USB3HC_PORTSC_1_PLC_BIT                  0x1
#define USB3HC_PORTSC_1_PLC_BITWIDTH             1
// CEC bitfiled (RW) Reset=0
#define USB3HC_PORTSC_1_CEC_MASK                 0x800000
#define USB3HC_PORTSC_1_CEC_SHIFT                23 
#define USB3HC_PORTSC_1_CEC_BIT                  0x1
#define USB3HC_PORTSC_1_CEC_BITWIDTH             1
// CAS bitfiled (RO) Reset=0
#define USB3HC_PORTSC_1_CAS_MASK                 0x1000000
#define USB3HC_PORTSC_1_CAS_SHIFT                24 
#define USB3HC_PORTSC_1_CAS_BIT                  0x1
#define USB3HC_PORTSC_1_CAS_BITWIDTH             1
// WCE bitfiled (RW) Reset=0
#define USB3HC_PORTSC_1_WCE_MASK                 0x2000000
#define USB3HC_PORTSC_1_WCE_SHIFT                25 
#define USB3HC_PORTSC_1_WCE_BIT                  0x1
#define USB3HC_PORTSC_1_WCE_BITWIDTH             1
// WDE bitfiled (RW) Reset=0
#define USB3HC_PORTSC_1_WDE_MASK                 0x4000000
#define USB3HC_PORTSC_1_WDE_SHIFT                26 
#define USB3HC_PORTSC_1_WDE_BIT                  0x1
#define USB3HC_PORTSC_1_WDE_BITWIDTH             1
// WOE bitfiled (RW) Reset=1
#define USB3HC_PORTSC_1_WOE_MASK                 0x8000000
#define USB3HC_PORTSC_1_WOE_SHIFT                27 
#define USB3HC_PORTSC_1_WOE_BIT                  0x1
#define USB3HC_PORTSC_1_WOE_BITWIDTH             1
// RSVD20 bitfiled (RO) Reset=0
#define USB3HC_PORTSC_1_RSVD20_MASK              0x30000000
#define USB3HC_PORTSC_1_RSVD20_SHIFT             28 
#define USB3HC_PORTSC_1_RSVD20_BIT               0x3
#define USB3HC_PORTSC_1_RSVD20_BITWIDTH          2
// DR bitfiled (RW) Reset=0
#define USB3HC_PORTSC_1_DR_MASK                  0x40000000
#define USB3HC_PORTSC_1_DR_SHIFT                 30 
#define USB3HC_PORTSC_1_DR_BIT                   0x1
#define USB3HC_PORTSC_1_DR_BITWIDTH              1
// WPR bitfiled (RW) Reset=0
#define USB3HC_PORTSC_1_WPR_MASK                 0x80000000
#define USB3HC_PORTSC_1_WPR_SHIFT                31 
#define USB3HC_PORTSC_1_WPR_BIT                  0x1
#define USB3HC_PORTSC_1_WPR_BITWIDTH             1
// PORTPMSC_SS_0 Register
#define USB3HC_PORTPMSC_SS_0_OFS                 0x00000434
// U1_TIMEOUT bitfiled (RO) Reset=0
#define USB3HC_PORTPMSC_SS_0_U1_TIMEOUT_MASK     0xFF
#define USB3HC_PORTPMSC_SS_0_U1_TIMEOUT_SHIFT    0 
#define USB3HC_PORTPMSC_SS_0_U1_TIMEOUT_BIT      0xFF
#define USB3HC_PORTPMSC_SS_0_U1_TIMEOUT_BITWIDTH 8
// U2_TIMEOUT bitfiled (RW) Reset=0
#define USB3HC_PORTPMSC_SS_0_U2_TIMEOUT_MASK     0xFF00
#define USB3HC_PORTPMSC_SS_0_U2_TIMEOUT_SHIFT    8 
#define USB3HC_PORTPMSC_SS_0_U2_TIMEOUT_BIT      0xFF
#define USB3HC_PORTPMSC_SS_0_U2_TIMEOUT_BITWIDTH 8
// FLA bitfiled (RW) Reset=0
#define USB3HC_PORTPMSC_SS_0_FLA_MASK            0x10000
#define USB3HC_PORTPMSC_SS_0_FLA_SHIFT           16 
#define USB3HC_PORTPMSC_SS_0_FLA_BIT             0x1
#define USB3HC_PORTPMSC_SS_0_FLA_BITWIDTH        1
// RSVD21 bitfiled (RW) Reset=0
#define USB3HC_PORTPMSC_SS_0_RSVD21_MASK         0xFFFE0000
#define USB3HC_PORTPMSC_SS_0_RSVD21_SHIFT        17 
#define USB3HC_PORTPMSC_SS_0_RSVD21_BIT          0x7FFF
#define USB3HC_PORTPMSC_SS_0_RSVD21_BITWIDTH     15
// PORTLI_1 Register
#define USB3HC_PORTLI_1_OFS                      0x00000438
// LINK_ERROR_COUNT bitfiled (RO) Reset=0
#define USB3HC_PORTLI_1_LINK_ERROR_COUNT_MASK    0xFFFF
#define USB3HC_PORTLI_1_LINK_ERROR_COUNT_SHIFT   0 
#define USB3HC_PORTLI_1_LINK_ERROR_COUNT_BIT     0xFFFF
#define USB3HC_PORTLI_1_LINK_ERROR_COUNT_BITWIDTH 16
// RSVD22 bitfiled (RO) Reset=0
#define USB3HC_PORTLI_1_RSVD22_MASK              0xFFFF0000
#define USB3HC_PORTLI_1_RSVD22_SHIFT             16 
#define USB3HC_PORTLI_1_RSVD22_BIT               0xFFFF
#define USB3HC_PORTLI_1_RSVD22_BITWIDTH          16
// MFINDEX Register
#define USB3HC_MFINDEX_OFS                       0x00000440
// MICROFRAME_INDEX bitfiled (RO) Reset=0
#define USB3HC_MFINDEX_MICROFRAME_INDEX_MASK     0x3FFF
#define USB3HC_MFINDEX_MICROFRAME_INDEX_SHIFT    0 
#define USB3HC_MFINDEX_MICROFRAME_INDEX_BIT      0x3FFF
#define USB3HC_MFINDEX_MICROFRAME_INDEX_BITWIDTH 14
// RSVD23 bitfiled (RO) Reset=0
#define USB3HC_MFINDEX_RSVD23_MASK               0xFFFFC000
#define USB3HC_MFINDEX_RSVD23_SHIFT              14 
#define USB3HC_MFINDEX_RSVD23_BIT                0x3FFFF
#define USB3HC_MFINDEX_RSVD23_BITWIDTH           18
// IMAN_0 Register
#define USB3HC_IMAN_0_OFS                        0x00000460
// IP bitfiled (RW) Reset=0
#define USB3HC_IMAN_0_IP_MASK                    0x1
#define USB3HC_IMAN_0_IP_SHIFT                   0 
#define USB3HC_IMAN_0_IP_BIT                     0x1
#define USB3HC_IMAN_0_IP_BITWIDTH                1
// IE bitfiled (RW) Reset=0
#define USB3HC_IMAN_0_IE_MASK                    0x2
#define USB3HC_IMAN_0_IE_SHIFT                   1 
#define USB3HC_IMAN_0_IE_BIT                     0x1
#define USB3HC_IMAN_0_IE_BITWIDTH                1
// RSVD25 bitfiled (RO) Reset=0
#define USB3HC_IMAN_0_RSVD25_MASK                0xFFFFFFFC
#define USB3HC_IMAN_0_RSVD25_SHIFT               2 
#define USB3HC_IMAN_0_RSVD25_BIT                 0x3FFFFFFF
#define USB3HC_IMAN_0_RSVD25_BITWIDTH            30
// IMOD_0 Register
#define USB3HC_IMOD_0_OFS                        0x00000464
// IMODI bitfiled (RW) Reset=111110100000
#define USB3HC_IMOD_0_IMODI_MASK                 0xFFFF
#define USB3HC_IMOD_0_IMODI_SHIFT                0 
#define USB3HC_IMOD_0_IMODI_BIT                  0xFFFF
#define USB3HC_IMOD_0_IMODI_BITWIDTH             16
// IMODC bitfiled (RW) Reset=0
#define USB3HC_IMOD_0_IMODC_MASK                 0xFFFF0000
#define USB3HC_IMOD_0_IMODC_SHIFT                16 
#define USB3HC_IMOD_0_IMODC_BIT                  0xFFFF
#define USB3HC_IMOD_0_IMODC_BITWIDTH             16
// ERSTSZ_0 Register
#define USB3HC_ERSTSZ_0_OFS                      0x00000468
// ERS_TABLE_SIZE bitfiled (RW) Reset=0
#define USB3HC_ERSTSZ_0_ERS_TABLE_SIZE_MASK      0xFFFF
#define USB3HC_ERSTSZ_0_ERS_TABLE_SIZE_SHIFT     0 
#define USB3HC_ERSTSZ_0_ERS_TABLE_SIZE_BIT       0xFFFF
#define USB3HC_ERSTSZ_0_ERS_TABLE_SIZE_BITWIDTH  16
// RSVD26 bitfiled (RO) Reset=0
#define USB3HC_ERSTSZ_0_RSVD26_MASK              0xFFFF0000
#define USB3HC_ERSTSZ_0_RSVD26_SHIFT             16 
#define USB3HC_ERSTSZ_0_RSVD26_BIT               0xFFFF
#define USB3HC_ERSTSZ_0_RSVD26_BITWIDTH          16
// ERSTBA_LO_0 Register
#define USB3HC_ERSTBA_LO_0_OFS                   0x00000470
// RSVD28 bitfiled (RO) Reset=0
#define USB3HC_ERSTBA_LO_0_RSVD28_MASK           0x3F
#define USB3HC_ERSTBA_LO_0_RSVD28_SHIFT          0 
#define USB3HC_ERSTBA_LO_0_RSVD28_BIT            0x3F
#define USB3HC_ERSTBA_LO_0_RSVD28_BITWIDTH       6
// ERS_TABLE_BAR bitfiled (RW) Reset=0
#define USB3HC_ERSTBA_LO_0_ERS_TABLE_BAR_MASK    0xFFFFFFC0
#define USB3HC_ERSTBA_LO_0_ERS_TABLE_BAR_SHIFT   6 
#define USB3HC_ERSTBA_LO_0_ERS_TABLE_BAR_BIT     0x3FFFFFF
#define USB3HC_ERSTBA_LO_0_ERS_TABLE_BAR_BITWIDTH 26
// ERSTBA_HI_0 Register
#define USB3HC_ERSTBA_HI_0_OFS                   0x00000474
// ERS_TABLE_BAR bitfiled (RW) Reset=0
#define USB3HC_ERSTBA_HI_0_ERS_TABLE_BAR_MASK    0xFFFFFFFF
#define USB3HC_ERSTBA_HI_0_ERS_TABLE_BAR_SHIFT   0 
#define USB3HC_ERSTBA_HI_0_ERS_TABLE_BAR_BIT     0xFFFFFFFF
#define USB3HC_ERSTBA_HI_0_ERS_TABLE_BAR_BITWIDTH 32
// ERDP_LO_0 Register
#define USB3HC_ERDP_LO_0_OFS                     0x00000478
// DESI bitfiled (RW) Reset=0
#define USB3HC_ERDP_LO_0_DESI_MASK               0x7
#define USB3HC_ERDP_LO_0_DESI_SHIFT              0 
#define USB3HC_ERDP_LO_0_DESI_BIT                0x7
#define USB3HC_ERDP_LO_0_DESI_BITWIDTH           3
// EHB bitfiled (RW) Reset=0
#define USB3HC_ERDP_LO_0_EHB_MASK                0x8
#define USB3HC_ERDP_LO_0_EHB_SHIFT               3 
#define USB3HC_ERDP_LO_0_EHB_BIT                 0x1
#define USB3HC_ERDP_LO_0_EHB_BITWIDTH            1
// ERD_PNTR bitfiled (RW) Reset=0
#define USB3HC_ERDP_LO_0_ERD_PNTR_MASK           0xFFFFFFF0
#define USB3HC_ERDP_LO_0_ERD_PNTR_SHIFT          4 
#define USB3HC_ERDP_LO_0_ERD_PNTR_BIT            0xFFFFFFF
#define USB3HC_ERDP_LO_0_ERD_PNTR_BITWIDTH       28
// ERDP_HI_0 Register
#define USB3HC_ERDP_HI_0_OFS                     0x0000047C
// ERD_PNTR bitfiled (RW) Reset=0
#define USB3HC_ERDP_HI_0_ERD_PNTR_MASK           0xFFFFFFFF
#define USB3HC_ERDP_HI_0_ERD_PNTR_SHIFT          0 
#define USB3HC_ERDP_HI_0_ERD_PNTR_BIT            0xFFFFFFFF
#define USB3HC_ERDP_HI_0_ERD_PNTR_BITWIDTH       32
// DB_0 Register
#define USB3HC_DB_0_OFS                          0x00000480
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_0_DB_TARGET_MASK               0xFF
#define USB3HC_DB_0_DB_TARGET_SHIFT              0 
#define USB3HC_DB_0_DB_TARGET_BIT                0xFF
#define USB3HC_DB_0_DB_TARGET_BITWIDTH           8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_0_RSVD29_MASK                  0xFF00
#define USB3HC_DB_0_RSVD29_SHIFT                 8 
#define USB3HC_DB_0_RSVD29_BIT                   0xFF
#define USB3HC_DB_0_RSVD29_BITWIDTH              8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_0_DB_STREAM_ID_MASK            0xFFFF0000
#define USB3HC_DB_0_DB_STREAM_ID_SHIFT           16 
#define USB3HC_DB_0_DB_STREAM_ID_BIT             0xFFFF
#define USB3HC_DB_0_DB_STREAM_ID_BITWIDTH        16
// DB_1 Register
#define USB3HC_DB_1_OFS                          0x00000484
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_1_DB_TARGET_MASK               0xFF
#define USB3HC_DB_1_DB_TARGET_SHIFT              0 
#define USB3HC_DB_1_DB_TARGET_BIT                0xFF
#define USB3HC_DB_1_DB_TARGET_BITWIDTH           8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_1_RSVD29_MASK                  0xFF00
#define USB3HC_DB_1_RSVD29_SHIFT                 8 
#define USB3HC_DB_1_RSVD29_BIT                   0xFF
#define USB3HC_DB_1_RSVD29_BITWIDTH              8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_1_DB_STREAM_ID_MASK            0xFFFF0000
#define USB3HC_DB_1_DB_STREAM_ID_SHIFT           16 
#define USB3HC_DB_1_DB_STREAM_ID_BIT             0xFFFF
#define USB3HC_DB_1_DB_STREAM_ID_BITWIDTH        16
// DB_2 Register
#define USB3HC_DB_2_OFS                          0x00000488
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_2_DB_TARGET_MASK               0xFF
#define USB3HC_DB_2_DB_TARGET_SHIFT              0 
#define USB3HC_DB_2_DB_TARGET_BIT                0xFF
#define USB3HC_DB_2_DB_TARGET_BITWIDTH           8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_2_RSVD29_MASK                  0xFF00
#define USB3HC_DB_2_RSVD29_SHIFT                 8 
#define USB3HC_DB_2_RSVD29_BIT                   0xFF
#define USB3HC_DB_2_RSVD29_BITWIDTH              8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_2_DB_STREAM_ID_MASK            0xFFFF0000
#define USB3HC_DB_2_DB_STREAM_ID_SHIFT           16 
#define USB3HC_DB_2_DB_STREAM_ID_BIT             0xFFFF
#define USB3HC_DB_2_DB_STREAM_ID_BITWIDTH        16
// DB_3 Register
#define USB3HC_DB_3_OFS                          0x0000048C
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_3_DB_TARGET_MASK               0xFF
#define USB3HC_DB_3_DB_TARGET_SHIFT              0 
#define USB3HC_DB_3_DB_TARGET_BIT                0xFF
#define USB3HC_DB_3_DB_TARGET_BITWIDTH           8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_3_RSVD29_MASK                  0xFF00
#define USB3HC_DB_3_RSVD29_SHIFT                 8 
#define USB3HC_DB_3_RSVD29_BIT                   0xFF
#define USB3HC_DB_3_RSVD29_BITWIDTH              8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_3_DB_STREAM_ID_MASK            0xFFFF0000
#define USB3HC_DB_3_DB_STREAM_ID_SHIFT           16 
#define USB3HC_DB_3_DB_STREAM_ID_BIT             0xFFFF
#define USB3HC_DB_3_DB_STREAM_ID_BITWIDTH        16
// DB_4 Register
#define USB3HC_DB_4_OFS                          0x00000490
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_4_DB_TARGET_MASK               0xFF
#define USB3HC_DB_4_DB_TARGET_SHIFT              0 
#define USB3HC_DB_4_DB_TARGET_BIT                0xFF
#define USB3HC_DB_4_DB_TARGET_BITWIDTH           8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_4_RSVD29_MASK                  0xFF00
#define USB3HC_DB_4_RSVD29_SHIFT                 8 
#define USB3HC_DB_4_RSVD29_BIT                   0xFF
#define USB3HC_DB_4_RSVD29_BITWIDTH              8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_4_DB_STREAM_ID_MASK            0xFFFF0000
#define USB3HC_DB_4_DB_STREAM_ID_SHIFT           16 
#define USB3HC_DB_4_DB_STREAM_ID_BIT             0xFFFF
#define USB3HC_DB_4_DB_STREAM_ID_BITWIDTH        16
// DB_5 Register
#define USB3HC_DB_5_OFS                          0x00000494
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_5_DB_TARGET_MASK               0xFF
#define USB3HC_DB_5_DB_TARGET_SHIFT              0 
#define USB3HC_DB_5_DB_TARGET_BIT                0xFF
#define USB3HC_DB_5_DB_TARGET_BITWIDTH           8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_5_RSVD29_MASK                  0xFF00
#define USB3HC_DB_5_RSVD29_SHIFT                 8 
#define USB3HC_DB_5_RSVD29_BIT                   0xFF
#define USB3HC_DB_5_RSVD29_BITWIDTH              8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_5_DB_STREAM_ID_MASK            0xFFFF0000
#define USB3HC_DB_5_DB_STREAM_ID_SHIFT           16 
#define USB3HC_DB_5_DB_STREAM_ID_BIT             0xFFFF
#define USB3HC_DB_5_DB_STREAM_ID_BITWIDTH        16
// DB_6 Register
#define USB3HC_DB_6_OFS                          0x00000498
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_6_DB_TARGET_MASK               0xFF
#define USB3HC_DB_6_DB_TARGET_SHIFT              0 
#define USB3HC_DB_6_DB_TARGET_BIT                0xFF
#define USB3HC_DB_6_DB_TARGET_BITWIDTH           8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_6_RSVD29_MASK                  0xFF00
#define USB3HC_DB_6_RSVD29_SHIFT                 8 
#define USB3HC_DB_6_RSVD29_BIT                   0xFF
#define USB3HC_DB_6_RSVD29_BITWIDTH              8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_6_DB_STREAM_ID_MASK            0xFFFF0000
#define USB3HC_DB_6_DB_STREAM_ID_SHIFT           16 
#define USB3HC_DB_6_DB_STREAM_ID_BIT             0xFFFF
#define USB3HC_DB_6_DB_STREAM_ID_BITWIDTH        16
// DB_7 Register
#define USB3HC_DB_7_OFS                          0x0000049C
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_7_DB_TARGET_MASK               0xFF
#define USB3HC_DB_7_DB_TARGET_SHIFT              0 
#define USB3HC_DB_7_DB_TARGET_BIT                0xFF
#define USB3HC_DB_7_DB_TARGET_BITWIDTH           8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_7_RSVD29_MASK                  0xFF00
#define USB3HC_DB_7_RSVD29_SHIFT                 8 
#define USB3HC_DB_7_RSVD29_BIT                   0xFF
#define USB3HC_DB_7_RSVD29_BITWIDTH              8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_7_DB_STREAM_ID_MASK            0xFFFF0000
#define USB3HC_DB_7_DB_STREAM_ID_SHIFT           16 
#define USB3HC_DB_7_DB_STREAM_ID_BIT             0xFFFF
#define USB3HC_DB_7_DB_STREAM_ID_BITWIDTH        16
// DB_8 Register
#define USB3HC_DB_8_OFS                          0x000004A0
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_8_DB_TARGET_MASK               0xFF
#define USB3HC_DB_8_DB_TARGET_SHIFT              0 
#define USB3HC_DB_8_DB_TARGET_BIT                0xFF
#define USB3HC_DB_8_DB_TARGET_BITWIDTH           8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_8_RSVD29_MASK                  0xFF00
#define USB3HC_DB_8_RSVD29_SHIFT                 8 
#define USB3HC_DB_8_RSVD29_BIT                   0xFF
#define USB3HC_DB_8_RSVD29_BITWIDTH              8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_8_DB_STREAM_ID_MASK            0xFFFF0000
#define USB3HC_DB_8_DB_STREAM_ID_SHIFT           16 
#define USB3HC_DB_8_DB_STREAM_ID_BIT             0xFFFF
#define USB3HC_DB_8_DB_STREAM_ID_BITWIDTH        16
// DB_9 Register
#define USB3HC_DB_9_OFS                          0x000004A4
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_9_DB_TARGET_MASK               0xFF
#define USB3HC_DB_9_DB_TARGET_SHIFT              0 
#define USB3HC_DB_9_DB_TARGET_BIT                0xFF
#define USB3HC_DB_9_DB_TARGET_BITWIDTH           8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_9_RSVD29_MASK                  0xFF00
#define USB3HC_DB_9_RSVD29_SHIFT                 8 
#define USB3HC_DB_9_RSVD29_BIT                   0xFF
#define USB3HC_DB_9_RSVD29_BITWIDTH              8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_9_DB_STREAM_ID_MASK            0xFFFF0000
#define USB3HC_DB_9_DB_STREAM_ID_SHIFT           16 
#define USB3HC_DB_9_DB_STREAM_ID_BIT             0xFFFF
#define USB3HC_DB_9_DB_STREAM_ID_BITWIDTH        16
// DB_10 Register
#define USB3HC_DB_10_OFS                         0x000004A8
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_10_DB_TARGET_MASK              0xFF
#define USB3HC_DB_10_DB_TARGET_SHIFT             0 
#define USB3HC_DB_10_DB_TARGET_BIT               0xFF
#define USB3HC_DB_10_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_10_RSVD29_MASK                 0xFF00
#define USB3HC_DB_10_RSVD29_SHIFT                8 
#define USB3HC_DB_10_RSVD29_BIT                  0xFF
#define USB3HC_DB_10_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_10_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_10_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_10_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_10_DB_STREAM_ID_BITWIDTH       16
// DB_11 Register
#define USB3HC_DB_11_OFS                         0x000004AC
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_11_DB_TARGET_MASK              0xFF
#define USB3HC_DB_11_DB_TARGET_SHIFT             0 
#define USB3HC_DB_11_DB_TARGET_BIT               0xFF
#define USB3HC_DB_11_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_11_RSVD29_MASK                 0xFF00
#define USB3HC_DB_11_RSVD29_SHIFT                8 
#define USB3HC_DB_11_RSVD29_BIT                  0xFF
#define USB3HC_DB_11_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_11_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_11_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_11_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_11_DB_STREAM_ID_BITWIDTH       16
// DB_12 Register
#define USB3HC_DB_12_OFS                         0x000004B0
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_12_DB_TARGET_MASK              0xFF
#define USB3HC_DB_12_DB_TARGET_SHIFT             0 
#define USB3HC_DB_12_DB_TARGET_BIT               0xFF
#define USB3HC_DB_12_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_12_RSVD29_MASK                 0xFF00
#define USB3HC_DB_12_RSVD29_SHIFT                8 
#define USB3HC_DB_12_RSVD29_BIT                  0xFF
#define USB3HC_DB_12_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_12_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_12_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_12_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_12_DB_STREAM_ID_BITWIDTH       16
// DB_13 Register
#define USB3HC_DB_13_OFS                         0x000004B4
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_13_DB_TARGET_MASK              0xFF
#define USB3HC_DB_13_DB_TARGET_SHIFT             0 
#define USB3HC_DB_13_DB_TARGET_BIT               0xFF
#define USB3HC_DB_13_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_13_RSVD29_MASK                 0xFF00
#define USB3HC_DB_13_RSVD29_SHIFT                8 
#define USB3HC_DB_13_RSVD29_BIT                  0xFF
#define USB3HC_DB_13_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_13_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_13_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_13_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_13_DB_STREAM_ID_BITWIDTH       16
// DB_14 Register
#define USB3HC_DB_14_OFS                         0x000004B8
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_14_DB_TARGET_MASK              0xFF
#define USB3HC_DB_14_DB_TARGET_SHIFT             0 
#define USB3HC_DB_14_DB_TARGET_BIT               0xFF
#define USB3HC_DB_14_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_14_RSVD29_MASK                 0xFF00
#define USB3HC_DB_14_RSVD29_SHIFT                8 
#define USB3HC_DB_14_RSVD29_BIT                  0xFF
#define USB3HC_DB_14_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_14_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_14_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_14_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_14_DB_STREAM_ID_BITWIDTH       16
// DB_15 Register
#define USB3HC_DB_15_OFS                         0x000004BC
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_15_DB_TARGET_MASK              0xFF
#define USB3HC_DB_15_DB_TARGET_SHIFT             0 
#define USB3HC_DB_15_DB_TARGET_BIT               0xFF
#define USB3HC_DB_15_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_15_RSVD29_MASK                 0xFF00
#define USB3HC_DB_15_RSVD29_SHIFT                8 
#define USB3HC_DB_15_RSVD29_BIT                  0xFF
#define USB3HC_DB_15_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_15_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_15_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_15_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_15_DB_STREAM_ID_BITWIDTH       16
// DB_16 Register
#define USB3HC_DB_16_OFS                         0x000004C0
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_16_DB_TARGET_MASK              0xFF
#define USB3HC_DB_16_DB_TARGET_SHIFT             0 
#define USB3HC_DB_16_DB_TARGET_BIT               0xFF
#define USB3HC_DB_16_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_16_RSVD29_MASK                 0xFF00
#define USB3HC_DB_16_RSVD29_SHIFT                8 
#define USB3HC_DB_16_RSVD29_BIT                  0xFF
#define USB3HC_DB_16_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_16_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_16_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_16_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_16_DB_STREAM_ID_BITWIDTH       16
// DB_17 Register
#define USB3HC_DB_17_OFS                         0x000004C4
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_17_DB_TARGET_MASK              0xFF
#define USB3HC_DB_17_DB_TARGET_SHIFT             0 
#define USB3HC_DB_17_DB_TARGET_BIT               0xFF
#define USB3HC_DB_17_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_17_RSVD29_MASK                 0xFF00
#define USB3HC_DB_17_RSVD29_SHIFT                8 
#define USB3HC_DB_17_RSVD29_BIT                  0xFF
#define USB3HC_DB_17_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_17_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_17_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_17_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_17_DB_STREAM_ID_BITWIDTH       16
// DB_18 Register
#define USB3HC_DB_18_OFS                         0x000004C8
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_18_DB_TARGET_MASK              0xFF
#define USB3HC_DB_18_DB_TARGET_SHIFT             0 
#define USB3HC_DB_18_DB_TARGET_BIT               0xFF
#define USB3HC_DB_18_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_18_RSVD29_MASK                 0xFF00
#define USB3HC_DB_18_RSVD29_SHIFT                8 
#define USB3HC_DB_18_RSVD29_BIT                  0xFF
#define USB3HC_DB_18_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_18_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_18_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_18_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_18_DB_STREAM_ID_BITWIDTH       16
// DB_19 Register
#define USB3HC_DB_19_OFS                         0x000004CC
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_19_DB_TARGET_MASK              0xFF
#define USB3HC_DB_19_DB_TARGET_SHIFT             0 
#define USB3HC_DB_19_DB_TARGET_BIT               0xFF
#define USB3HC_DB_19_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_19_RSVD29_MASK                 0xFF00
#define USB3HC_DB_19_RSVD29_SHIFT                8 
#define USB3HC_DB_19_RSVD29_BIT                  0xFF
#define USB3HC_DB_19_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_19_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_19_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_19_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_19_DB_STREAM_ID_BITWIDTH       16
// DB_20 Register
#define USB3HC_DB_20_OFS                         0x000004D0
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_20_DB_TARGET_MASK              0xFF
#define USB3HC_DB_20_DB_TARGET_SHIFT             0 
#define USB3HC_DB_20_DB_TARGET_BIT               0xFF
#define USB3HC_DB_20_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_20_RSVD29_MASK                 0xFF00
#define USB3HC_DB_20_RSVD29_SHIFT                8 
#define USB3HC_DB_20_RSVD29_BIT                  0xFF
#define USB3HC_DB_20_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_20_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_20_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_20_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_20_DB_STREAM_ID_BITWIDTH       16
// DB_21 Register
#define USB3HC_DB_21_OFS                         0x000004D4
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_21_DB_TARGET_MASK              0xFF
#define USB3HC_DB_21_DB_TARGET_SHIFT             0 
#define USB3HC_DB_21_DB_TARGET_BIT               0xFF
#define USB3HC_DB_21_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_21_RSVD29_MASK                 0xFF00
#define USB3HC_DB_21_RSVD29_SHIFT                8 
#define USB3HC_DB_21_RSVD29_BIT                  0xFF
#define USB3HC_DB_21_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_21_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_21_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_21_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_21_DB_STREAM_ID_BITWIDTH       16
// DB_22 Register
#define USB3HC_DB_22_OFS                         0x000004D8
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_22_DB_TARGET_MASK              0xFF
#define USB3HC_DB_22_DB_TARGET_SHIFT             0 
#define USB3HC_DB_22_DB_TARGET_BIT               0xFF
#define USB3HC_DB_22_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_22_RSVD29_MASK                 0xFF00
#define USB3HC_DB_22_RSVD29_SHIFT                8 
#define USB3HC_DB_22_RSVD29_BIT                  0xFF
#define USB3HC_DB_22_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_22_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_22_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_22_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_22_DB_STREAM_ID_BITWIDTH       16
// DB_23 Register
#define USB3HC_DB_23_OFS                         0x000004DC
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_23_DB_TARGET_MASK              0xFF
#define USB3HC_DB_23_DB_TARGET_SHIFT             0 
#define USB3HC_DB_23_DB_TARGET_BIT               0xFF
#define USB3HC_DB_23_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_23_RSVD29_MASK                 0xFF00
#define USB3HC_DB_23_RSVD29_SHIFT                8 
#define USB3HC_DB_23_RSVD29_BIT                  0xFF
#define USB3HC_DB_23_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_23_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_23_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_23_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_23_DB_STREAM_ID_BITWIDTH       16
// DB_24 Register
#define USB3HC_DB_24_OFS                         0x000004E0
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_24_DB_TARGET_MASK              0xFF
#define USB3HC_DB_24_DB_TARGET_SHIFT             0 
#define USB3HC_DB_24_DB_TARGET_BIT               0xFF
#define USB3HC_DB_24_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_24_RSVD29_MASK                 0xFF00
#define USB3HC_DB_24_RSVD29_SHIFT                8 
#define USB3HC_DB_24_RSVD29_BIT                  0xFF
#define USB3HC_DB_24_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_24_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_24_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_24_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_24_DB_STREAM_ID_BITWIDTH       16
// DB_25 Register
#define USB3HC_DB_25_OFS                         0x000004E4
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_25_DB_TARGET_MASK              0xFF
#define USB3HC_DB_25_DB_TARGET_SHIFT             0 
#define USB3HC_DB_25_DB_TARGET_BIT               0xFF
#define USB3HC_DB_25_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_25_RSVD29_MASK                 0xFF00
#define USB3HC_DB_25_RSVD29_SHIFT                8 
#define USB3HC_DB_25_RSVD29_BIT                  0xFF
#define USB3HC_DB_25_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_25_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_25_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_25_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_25_DB_STREAM_ID_BITWIDTH       16
// DB_26 Register
#define USB3HC_DB_26_OFS                         0x000004E8
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_26_DB_TARGET_MASK              0xFF
#define USB3HC_DB_26_DB_TARGET_SHIFT             0 
#define USB3HC_DB_26_DB_TARGET_BIT               0xFF
#define USB3HC_DB_26_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_26_RSVD29_MASK                 0xFF00
#define USB3HC_DB_26_RSVD29_SHIFT                8 
#define USB3HC_DB_26_RSVD29_BIT                  0xFF
#define USB3HC_DB_26_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_26_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_26_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_26_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_26_DB_STREAM_ID_BITWIDTH       16
// DB_27 Register
#define USB3HC_DB_27_OFS                         0x000004EC
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_27_DB_TARGET_MASK              0xFF
#define USB3HC_DB_27_DB_TARGET_SHIFT             0 
#define USB3HC_DB_27_DB_TARGET_BIT               0xFF
#define USB3HC_DB_27_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_27_RSVD29_MASK                 0xFF00
#define USB3HC_DB_27_RSVD29_SHIFT                8 
#define USB3HC_DB_27_RSVD29_BIT                  0xFF
#define USB3HC_DB_27_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_27_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_27_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_27_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_27_DB_STREAM_ID_BITWIDTH       16
// DB_28 Register
#define USB3HC_DB_28_OFS                         0x000004F0
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_28_DB_TARGET_MASK              0xFF
#define USB3HC_DB_28_DB_TARGET_SHIFT             0 
#define USB3HC_DB_28_DB_TARGET_BIT               0xFF
#define USB3HC_DB_28_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_28_RSVD29_MASK                 0xFF00
#define USB3HC_DB_28_RSVD29_SHIFT                8 
#define USB3HC_DB_28_RSVD29_BIT                  0xFF
#define USB3HC_DB_28_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_28_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_28_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_28_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_28_DB_STREAM_ID_BITWIDTH       16
// DB_29 Register
#define USB3HC_DB_29_OFS                         0x000004F4
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_29_DB_TARGET_MASK              0xFF
#define USB3HC_DB_29_DB_TARGET_SHIFT             0 
#define USB3HC_DB_29_DB_TARGET_BIT               0xFF
#define USB3HC_DB_29_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_29_RSVD29_MASK                 0xFF00
#define USB3HC_DB_29_RSVD29_SHIFT                8 
#define USB3HC_DB_29_RSVD29_BIT                  0xFF
#define USB3HC_DB_29_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_29_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_29_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_29_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_29_DB_STREAM_ID_BITWIDTH       16
// DB_30 Register
#define USB3HC_DB_30_OFS                         0x000004F8
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_30_DB_TARGET_MASK              0xFF
#define USB3HC_DB_30_DB_TARGET_SHIFT             0 
#define USB3HC_DB_30_DB_TARGET_BIT               0xFF
#define USB3HC_DB_30_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_30_RSVD29_MASK                 0xFF00
#define USB3HC_DB_30_RSVD29_SHIFT                8 
#define USB3HC_DB_30_RSVD29_BIT                  0xFF
#define USB3HC_DB_30_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_30_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_30_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_30_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_30_DB_STREAM_ID_BITWIDTH       16
// DB_31 Register
#define USB3HC_DB_31_OFS                         0x000004FC
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_31_DB_TARGET_MASK              0xFF
#define USB3HC_DB_31_DB_TARGET_SHIFT             0 
#define USB3HC_DB_31_DB_TARGET_BIT               0xFF
#define USB3HC_DB_31_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_31_RSVD29_MASK                 0xFF00
#define USB3HC_DB_31_RSVD29_SHIFT                8 
#define USB3HC_DB_31_RSVD29_BIT                  0xFF
#define USB3HC_DB_31_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_31_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_31_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_31_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_31_DB_STREAM_ID_BITWIDTH       16
// DB_32 Register
#define USB3HC_DB_32_OFS                         0x00000500
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_32_DB_TARGET_MASK              0xFF
#define USB3HC_DB_32_DB_TARGET_SHIFT             0 
#define USB3HC_DB_32_DB_TARGET_BIT               0xFF
#define USB3HC_DB_32_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_32_RSVD29_MASK                 0xFF00
#define USB3HC_DB_32_RSVD29_SHIFT                8 
#define USB3HC_DB_32_RSVD29_BIT                  0xFF
#define USB3HC_DB_32_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_32_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_32_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_32_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_32_DB_STREAM_ID_BITWIDTH       16
// DB_33 Register
#define USB3HC_DB_33_OFS                         0x00000504
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_33_DB_TARGET_MASK              0xFF
#define USB3HC_DB_33_DB_TARGET_SHIFT             0 
#define USB3HC_DB_33_DB_TARGET_BIT               0xFF
#define USB3HC_DB_33_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_33_RSVD29_MASK                 0xFF00
#define USB3HC_DB_33_RSVD29_SHIFT                8 
#define USB3HC_DB_33_RSVD29_BIT                  0xFF
#define USB3HC_DB_33_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_33_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_33_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_33_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_33_DB_STREAM_ID_BITWIDTH       16
// DB_34 Register
#define USB3HC_DB_34_OFS                         0x00000508
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_34_DB_TARGET_MASK              0xFF
#define USB3HC_DB_34_DB_TARGET_SHIFT             0 
#define USB3HC_DB_34_DB_TARGET_BIT               0xFF
#define USB3HC_DB_34_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_34_RSVD29_MASK                 0xFF00
#define USB3HC_DB_34_RSVD29_SHIFT                8 
#define USB3HC_DB_34_RSVD29_BIT                  0xFF
#define USB3HC_DB_34_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_34_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_34_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_34_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_34_DB_STREAM_ID_BITWIDTH       16
// DB_35 Register
#define USB3HC_DB_35_OFS                         0x0000050C
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_35_DB_TARGET_MASK              0xFF
#define USB3HC_DB_35_DB_TARGET_SHIFT             0 
#define USB3HC_DB_35_DB_TARGET_BIT               0xFF
#define USB3HC_DB_35_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_35_RSVD29_MASK                 0xFF00
#define USB3HC_DB_35_RSVD29_SHIFT                8 
#define USB3HC_DB_35_RSVD29_BIT                  0xFF
#define USB3HC_DB_35_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_35_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_35_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_35_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_35_DB_STREAM_ID_BITWIDTH       16
// DB_36 Register
#define USB3HC_DB_36_OFS                         0x00000510
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_36_DB_TARGET_MASK              0xFF
#define USB3HC_DB_36_DB_TARGET_SHIFT             0 
#define USB3HC_DB_36_DB_TARGET_BIT               0xFF
#define USB3HC_DB_36_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_36_RSVD29_MASK                 0xFF00
#define USB3HC_DB_36_RSVD29_SHIFT                8 
#define USB3HC_DB_36_RSVD29_BIT                  0xFF
#define USB3HC_DB_36_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_36_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_36_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_36_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_36_DB_STREAM_ID_BITWIDTH       16
// DB_37 Register
#define USB3HC_DB_37_OFS                         0x00000514
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_37_DB_TARGET_MASK              0xFF
#define USB3HC_DB_37_DB_TARGET_SHIFT             0 
#define USB3HC_DB_37_DB_TARGET_BIT               0xFF
#define USB3HC_DB_37_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_37_RSVD29_MASK                 0xFF00
#define USB3HC_DB_37_RSVD29_SHIFT                8 
#define USB3HC_DB_37_RSVD29_BIT                  0xFF
#define USB3HC_DB_37_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_37_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_37_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_37_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_37_DB_STREAM_ID_BITWIDTH       16
// DB_38 Register
#define USB3HC_DB_38_OFS                         0x00000518
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_38_DB_TARGET_MASK              0xFF
#define USB3HC_DB_38_DB_TARGET_SHIFT             0 
#define USB3HC_DB_38_DB_TARGET_BIT               0xFF
#define USB3HC_DB_38_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_38_RSVD29_MASK                 0xFF00
#define USB3HC_DB_38_RSVD29_SHIFT                8 
#define USB3HC_DB_38_RSVD29_BIT                  0xFF
#define USB3HC_DB_38_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_38_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_38_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_38_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_38_DB_STREAM_ID_BITWIDTH       16
// DB_39 Register
#define USB3HC_DB_39_OFS                         0x0000051C
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_39_DB_TARGET_MASK              0xFF
#define USB3HC_DB_39_DB_TARGET_SHIFT             0 
#define USB3HC_DB_39_DB_TARGET_BIT               0xFF
#define USB3HC_DB_39_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_39_RSVD29_MASK                 0xFF00
#define USB3HC_DB_39_RSVD29_SHIFT                8 
#define USB3HC_DB_39_RSVD29_BIT                  0xFF
#define USB3HC_DB_39_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_39_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_39_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_39_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_39_DB_STREAM_ID_BITWIDTH       16
// DB_40 Register
#define USB3HC_DB_40_OFS                         0x00000520
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_40_DB_TARGET_MASK              0xFF
#define USB3HC_DB_40_DB_TARGET_SHIFT             0 
#define USB3HC_DB_40_DB_TARGET_BIT               0xFF
#define USB3HC_DB_40_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_40_RSVD29_MASK                 0xFF00
#define USB3HC_DB_40_RSVD29_SHIFT                8 
#define USB3HC_DB_40_RSVD29_BIT                  0xFF
#define USB3HC_DB_40_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_40_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_40_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_40_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_40_DB_STREAM_ID_BITWIDTH       16
// DB_41 Register
#define USB3HC_DB_41_OFS                         0x00000524
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_41_DB_TARGET_MASK              0xFF
#define USB3HC_DB_41_DB_TARGET_SHIFT             0 
#define USB3HC_DB_41_DB_TARGET_BIT               0xFF
#define USB3HC_DB_41_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_41_RSVD29_MASK                 0xFF00
#define USB3HC_DB_41_RSVD29_SHIFT                8 
#define USB3HC_DB_41_RSVD29_BIT                  0xFF
#define USB3HC_DB_41_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_41_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_41_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_41_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_41_DB_STREAM_ID_BITWIDTH       16
// DB_42 Register
#define USB3HC_DB_42_OFS                         0x00000528
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_42_DB_TARGET_MASK              0xFF
#define USB3HC_DB_42_DB_TARGET_SHIFT             0 
#define USB3HC_DB_42_DB_TARGET_BIT               0xFF
#define USB3HC_DB_42_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_42_RSVD29_MASK                 0xFF00
#define USB3HC_DB_42_RSVD29_SHIFT                8 
#define USB3HC_DB_42_RSVD29_BIT                  0xFF
#define USB3HC_DB_42_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_42_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_42_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_42_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_42_DB_STREAM_ID_BITWIDTH       16
// DB_43 Register
#define USB3HC_DB_43_OFS                         0x0000052C
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_43_DB_TARGET_MASK              0xFF
#define USB3HC_DB_43_DB_TARGET_SHIFT             0 
#define USB3HC_DB_43_DB_TARGET_BIT               0xFF
#define USB3HC_DB_43_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_43_RSVD29_MASK                 0xFF00
#define USB3HC_DB_43_RSVD29_SHIFT                8 
#define USB3HC_DB_43_RSVD29_BIT                  0xFF
#define USB3HC_DB_43_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_43_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_43_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_43_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_43_DB_STREAM_ID_BITWIDTH       16
// DB_44 Register
#define USB3HC_DB_44_OFS                         0x00000530
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_44_DB_TARGET_MASK              0xFF
#define USB3HC_DB_44_DB_TARGET_SHIFT             0 
#define USB3HC_DB_44_DB_TARGET_BIT               0xFF
#define USB3HC_DB_44_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_44_RSVD29_MASK                 0xFF00
#define USB3HC_DB_44_RSVD29_SHIFT                8 
#define USB3HC_DB_44_RSVD29_BIT                  0xFF
#define USB3HC_DB_44_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_44_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_44_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_44_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_44_DB_STREAM_ID_BITWIDTH       16
// DB_45 Register
#define USB3HC_DB_45_OFS                         0x00000534
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_45_DB_TARGET_MASK              0xFF
#define USB3HC_DB_45_DB_TARGET_SHIFT             0 
#define USB3HC_DB_45_DB_TARGET_BIT               0xFF
#define USB3HC_DB_45_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_45_RSVD29_MASK                 0xFF00
#define USB3HC_DB_45_RSVD29_SHIFT                8 
#define USB3HC_DB_45_RSVD29_BIT                  0xFF
#define USB3HC_DB_45_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_45_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_45_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_45_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_45_DB_STREAM_ID_BITWIDTH       16
// DB_46 Register
#define USB3HC_DB_46_OFS                         0x00000538
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_46_DB_TARGET_MASK              0xFF
#define USB3HC_DB_46_DB_TARGET_SHIFT             0 
#define USB3HC_DB_46_DB_TARGET_BIT               0xFF
#define USB3HC_DB_46_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_46_RSVD29_MASK                 0xFF00
#define USB3HC_DB_46_RSVD29_SHIFT                8 
#define USB3HC_DB_46_RSVD29_BIT                  0xFF
#define USB3HC_DB_46_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_46_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_46_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_46_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_46_DB_STREAM_ID_BITWIDTH       16
// DB_47 Register
#define USB3HC_DB_47_OFS                         0x0000053C
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_47_DB_TARGET_MASK              0xFF
#define USB3HC_DB_47_DB_TARGET_SHIFT             0 
#define USB3HC_DB_47_DB_TARGET_BIT               0xFF
#define USB3HC_DB_47_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_47_RSVD29_MASK                 0xFF00
#define USB3HC_DB_47_RSVD29_SHIFT                8 
#define USB3HC_DB_47_RSVD29_BIT                  0xFF
#define USB3HC_DB_47_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_47_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_47_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_47_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_47_DB_STREAM_ID_BITWIDTH       16
// DB_48 Register
#define USB3HC_DB_48_OFS                         0x00000540
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_48_DB_TARGET_MASK              0xFF
#define USB3HC_DB_48_DB_TARGET_SHIFT             0 
#define USB3HC_DB_48_DB_TARGET_BIT               0xFF
#define USB3HC_DB_48_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_48_RSVD29_MASK                 0xFF00
#define USB3HC_DB_48_RSVD29_SHIFT                8 
#define USB3HC_DB_48_RSVD29_BIT                  0xFF
#define USB3HC_DB_48_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_48_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_48_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_48_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_48_DB_STREAM_ID_BITWIDTH       16
// DB_49 Register
#define USB3HC_DB_49_OFS                         0x00000544
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_49_DB_TARGET_MASK              0xFF
#define USB3HC_DB_49_DB_TARGET_SHIFT             0 
#define USB3HC_DB_49_DB_TARGET_BIT               0xFF
#define USB3HC_DB_49_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_49_RSVD29_MASK                 0xFF00
#define USB3HC_DB_49_RSVD29_SHIFT                8 
#define USB3HC_DB_49_RSVD29_BIT                  0xFF
#define USB3HC_DB_49_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_49_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_49_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_49_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_49_DB_STREAM_ID_BITWIDTH       16
// DB_50 Register
#define USB3HC_DB_50_OFS                         0x00000548
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_50_DB_TARGET_MASK              0xFF
#define USB3HC_DB_50_DB_TARGET_SHIFT             0 
#define USB3HC_DB_50_DB_TARGET_BIT               0xFF
#define USB3HC_DB_50_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_50_RSVD29_MASK                 0xFF00
#define USB3HC_DB_50_RSVD29_SHIFT                8 
#define USB3HC_DB_50_RSVD29_BIT                  0xFF
#define USB3HC_DB_50_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_50_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_50_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_50_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_50_DB_STREAM_ID_BITWIDTH       16
// DB_51 Register
#define USB3HC_DB_51_OFS                         0x0000054C
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_51_DB_TARGET_MASK              0xFF
#define USB3HC_DB_51_DB_TARGET_SHIFT             0 
#define USB3HC_DB_51_DB_TARGET_BIT               0xFF
#define USB3HC_DB_51_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_51_RSVD29_MASK                 0xFF00
#define USB3HC_DB_51_RSVD29_SHIFT                8 
#define USB3HC_DB_51_RSVD29_BIT                  0xFF
#define USB3HC_DB_51_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_51_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_51_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_51_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_51_DB_STREAM_ID_BITWIDTH       16
// DB_52 Register
#define USB3HC_DB_52_OFS                         0x00000550
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_52_DB_TARGET_MASK              0xFF
#define USB3HC_DB_52_DB_TARGET_SHIFT             0 
#define USB3HC_DB_52_DB_TARGET_BIT               0xFF
#define USB3HC_DB_52_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_52_RSVD29_MASK                 0xFF00
#define USB3HC_DB_52_RSVD29_SHIFT                8 
#define USB3HC_DB_52_RSVD29_BIT                  0xFF
#define USB3HC_DB_52_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_52_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_52_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_52_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_52_DB_STREAM_ID_BITWIDTH       16
// DB_53 Register
#define USB3HC_DB_53_OFS                         0x00000554
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_53_DB_TARGET_MASK              0xFF
#define USB3HC_DB_53_DB_TARGET_SHIFT             0 
#define USB3HC_DB_53_DB_TARGET_BIT               0xFF
#define USB3HC_DB_53_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_53_RSVD29_MASK                 0xFF00
#define USB3HC_DB_53_RSVD29_SHIFT                8 
#define USB3HC_DB_53_RSVD29_BIT                  0xFF
#define USB3HC_DB_53_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_53_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_53_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_53_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_53_DB_STREAM_ID_BITWIDTH       16
// DB_54 Register
#define USB3HC_DB_54_OFS                         0x00000558
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_54_DB_TARGET_MASK              0xFF
#define USB3HC_DB_54_DB_TARGET_SHIFT             0 
#define USB3HC_DB_54_DB_TARGET_BIT               0xFF
#define USB3HC_DB_54_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_54_RSVD29_MASK                 0xFF00
#define USB3HC_DB_54_RSVD29_SHIFT                8 
#define USB3HC_DB_54_RSVD29_BIT                  0xFF
#define USB3HC_DB_54_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_54_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_54_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_54_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_54_DB_STREAM_ID_BITWIDTH       16
// DB_55 Register
#define USB3HC_DB_55_OFS                         0x0000055C
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_55_DB_TARGET_MASK              0xFF
#define USB3HC_DB_55_DB_TARGET_SHIFT             0 
#define USB3HC_DB_55_DB_TARGET_BIT               0xFF
#define USB3HC_DB_55_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_55_RSVD29_MASK                 0xFF00
#define USB3HC_DB_55_RSVD29_SHIFT                8 
#define USB3HC_DB_55_RSVD29_BIT                  0xFF
#define USB3HC_DB_55_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_55_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_55_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_55_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_55_DB_STREAM_ID_BITWIDTH       16
// DB_56 Register
#define USB3HC_DB_56_OFS                         0x00000560
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_56_DB_TARGET_MASK              0xFF
#define USB3HC_DB_56_DB_TARGET_SHIFT             0 
#define USB3HC_DB_56_DB_TARGET_BIT               0xFF
#define USB3HC_DB_56_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_56_RSVD29_MASK                 0xFF00
#define USB3HC_DB_56_RSVD29_SHIFT                8 
#define USB3HC_DB_56_RSVD29_BIT                  0xFF
#define USB3HC_DB_56_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_56_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_56_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_56_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_56_DB_STREAM_ID_BITWIDTH       16
// DB_57 Register
#define USB3HC_DB_57_OFS                         0x00000564
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_57_DB_TARGET_MASK              0xFF
#define USB3HC_DB_57_DB_TARGET_SHIFT             0 
#define USB3HC_DB_57_DB_TARGET_BIT               0xFF
#define USB3HC_DB_57_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_57_RSVD29_MASK                 0xFF00
#define USB3HC_DB_57_RSVD29_SHIFT                8 
#define USB3HC_DB_57_RSVD29_BIT                  0xFF
#define USB3HC_DB_57_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_57_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_57_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_57_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_57_DB_STREAM_ID_BITWIDTH       16
// DB_58 Register
#define USB3HC_DB_58_OFS                         0x00000568
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_58_DB_TARGET_MASK              0xFF
#define USB3HC_DB_58_DB_TARGET_SHIFT             0 
#define USB3HC_DB_58_DB_TARGET_BIT               0xFF
#define USB3HC_DB_58_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_58_RSVD29_MASK                 0xFF00
#define USB3HC_DB_58_RSVD29_SHIFT                8 
#define USB3HC_DB_58_RSVD29_BIT                  0xFF
#define USB3HC_DB_58_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_58_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_58_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_58_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_58_DB_STREAM_ID_BITWIDTH       16
// DB_59 Register
#define USB3HC_DB_59_OFS                         0x0000056C
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_59_DB_TARGET_MASK              0xFF
#define USB3HC_DB_59_DB_TARGET_SHIFT             0 
#define USB3HC_DB_59_DB_TARGET_BIT               0xFF
#define USB3HC_DB_59_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_59_RSVD29_MASK                 0xFF00
#define USB3HC_DB_59_RSVD29_SHIFT                8 
#define USB3HC_DB_59_RSVD29_BIT                  0xFF
#define USB3HC_DB_59_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_59_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_59_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_59_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_59_DB_STREAM_ID_BITWIDTH       16
// DB_60 Register
#define USB3HC_DB_60_OFS                         0x00000570
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_60_DB_TARGET_MASK              0xFF
#define USB3HC_DB_60_DB_TARGET_SHIFT             0 
#define USB3HC_DB_60_DB_TARGET_BIT               0xFF
#define USB3HC_DB_60_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_60_RSVD29_MASK                 0xFF00
#define USB3HC_DB_60_RSVD29_SHIFT                8 
#define USB3HC_DB_60_RSVD29_BIT                  0xFF
#define USB3HC_DB_60_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_60_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_60_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_60_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_60_DB_STREAM_ID_BITWIDTH       16
// DB_61 Register
#define USB3HC_DB_61_OFS                         0x00000574
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_61_DB_TARGET_MASK              0xFF
#define USB3HC_DB_61_DB_TARGET_SHIFT             0 
#define USB3HC_DB_61_DB_TARGET_BIT               0xFF
#define USB3HC_DB_61_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_61_RSVD29_MASK                 0xFF00
#define USB3HC_DB_61_RSVD29_SHIFT                8 
#define USB3HC_DB_61_RSVD29_BIT                  0xFF
#define USB3HC_DB_61_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_61_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_61_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_61_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_61_DB_STREAM_ID_BITWIDTH       16
// DB_62 Register
#define USB3HC_DB_62_OFS                         0x00000578
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_62_DB_TARGET_MASK              0xFF
#define USB3HC_DB_62_DB_TARGET_SHIFT             0 
#define USB3HC_DB_62_DB_TARGET_BIT               0xFF
#define USB3HC_DB_62_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_62_RSVD29_MASK                 0xFF00
#define USB3HC_DB_62_RSVD29_SHIFT                8 
#define USB3HC_DB_62_RSVD29_BIT                  0xFF
#define USB3HC_DB_62_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_62_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_62_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_62_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_62_DB_STREAM_ID_BITWIDTH       16
// DB_63 Register
#define USB3HC_DB_63_OFS                         0x0000057C
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_63_DB_TARGET_MASK              0xFF
#define USB3HC_DB_63_DB_TARGET_SHIFT             0 
#define USB3HC_DB_63_DB_TARGET_BIT               0xFF
#define USB3HC_DB_63_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_63_RSVD29_MASK                 0xFF00
#define USB3HC_DB_63_RSVD29_SHIFT                8 
#define USB3HC_DB_63_RSVD29_BIT                  0xFF
#define USB3HC_DB_63_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_63_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_63_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_63_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_63_DB_STREAM_ID_BITWIDTH       16
// DB_64 Register
#define USB3HC_DB_64_OFS                         0x00000580
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_64_DB_TARGET_MASK              0xFF
#define USB3HC_DB_64_DB_TARGET_SHIFT             0 
#define USB3HC_DB_64_DB_TARGET_BIT               0xFF
#define USB3HC_DB_64_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_64_RSVD29_MASK                 0xFF00
#define USB3HC_DB_64_RSVD29_SHIFT                8 
#define USB3HC_DB_64_RSVD29_BIT                  0xFF
#define USB3HC_DB_64_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_64_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_64_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_64_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_64_DB_STREAM_ID_BITWIDTH       16
// DB_65 Register
#define USB3HC_DB_65_OFS                         0x00000584
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_65_DB_TARGET_MASK              0xFF
#define USB3HC_DB_65_DB_TARGET_SHIFT             0 
#define USB3HC_DB_65_DB_TARGET_BIT               0xFF
#define USB3HC_DB_65_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_65_RSVD29_MASK                 0xFF00
#define USB3HC_DB_65_RSVD29_SHIFT                8 
#define USB3HC_DB_65_RSVD29_BIT                  0xFF
#define USB3HC_DB_65_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_65_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_65_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_65_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_65_DB_STREAM_ID_BITWIDTH       16
// DB_66 Register
#define USB3HC_DB_66_OFS                         0x00000588
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_66_DB_TARGET_MASK              0xFF
#define USB3HC_DB_66_DB_TARGET_SHIFT             0 
#define USB3HC_DB_66_DB_TARGET_BIT               0xFF
#define USB3HC_DB_66_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_66_RSVD29_MASK                 0xFF00
#define USB3HC_DB_66_RSVD29_SHIFT                8 
#define USB3HC_DB_66_RSVD29_BIT                  0xFF
#define USB3HC_DB_66_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_66_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_66_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_66_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_66_DB_STREAM_ID_BITWIDTH       16
// DB_67 Register
#define USB3HC_DB_67_OFS                         0x0000058C
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_67_DB_TARGET_MASK              0xFF
#define USB3HC_DB_67_DB_TARGET_SHIFT             0 
#define USB3HC_DB_67_DB_TARGET_BIT               0xFF
#define USB3HC_DB_67_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_67_RSVD29_MASK                 0xFF00
#define USB3HC_DB_67_RSVD29_SHIFT                8 
#define USB3HC_DB_67_RSVD29_BIT                  0xFF
#define USB3HC_DB_67_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_67_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_67_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_67_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_67_DB_STREAM_ID_BITWIDTH       16
// DB_68 Register
#define USB3HC_DB_68_OFS                         0x00000590
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_68_DB_TARGET_MASK              0xFF
#define USB3HC_DB_68_DB_TARGET_SHIFT             0 
#define USB3HC_DB_68_DB_TARGET_BIT               0xFF
#define USB3HC_DB_68_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_68_RSVD29_MASK                 0xFF00
#define USB3HC_DB_68_RSVD29_SHIFT                8 
#define USB3HC_DB_68_RSVD29_BIT                  0xFF
#define USB3HC_DB_68_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_68_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_68_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_68_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_68_DB_STREAM_ID_BITWIDTH       16
// DB_69 Register
#define USB3HC_DB_69_OFS                         0x00000594
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_69_DB_TARGET_MASK              0xFF
#define USB3HC_DB_69_DB_TARGET_SHIFT             0 
#define USB3HC_DB_69_DB_TARGET_BIT               0xFF
#define USB3HC_DB_69_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_69_RSVD29_MASK                 0xFF00
#define USB3HC_DB_69_RSVD29_SHIFT                8 
#define USB3HC_DB_69_RSVD29_BIT                  0xFF
#define USB3HC_DB_69_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_69_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_69_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_69_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_69_DB_STREAM_ID_BITWIDTH       16
// DB_70 Register
#define USB3HC_DB_70_OFS                         0x00000598
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_70_DB_TARGET_MASK              0xFF
#define USB3HC_DB_70_DB_TARGET_SHIFT             0 
#define USB3HC_DB_70_DB_TARGET_BIT               0xFF
#define USB3HC_DB_70_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_70_RSVD29_MASK                 0xFF00
#define USB3HC_DB_70_RSVD29_SHIFT                8 
#define USB3HC_DB_70_RSVD29_BIT                  0xFF
#define USB3HC_DB_70_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_70_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_70_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_70_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_70_DB_STREAM_ID_BITWIDTH       16
// DB_71 Register
#define USB3HC_DB_71_OFS                         0x0000059C
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_71_DB_TARGET_MASK              0xFF
#define USB3HC_DB_71_DB_TARGET_SHIFT             0 
#define USB3HC_DB_71_DB_TARGET_BIT               0xFF
#define USB3HC_DB_71_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_71_RSVD29_MASK                 0xFF00
#define USB3HC_DB_71_RSVD29_SHIFT                8 
#define USB3HC_DB_71_RSVD29_BIT                  0xFF
#define USB3HC_DB_71_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_71_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_71_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_71_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_71_DB_STREAM_ID_BITWIDTH       16
// DB_72 Register
#define USB3HC_DB_72_OFS                         0x000005A0
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_72_DB_TARGET_MASK              0xFF
#define USB3HC_DB_72_DB_TARGET_SHIFT             0 
#define USB3HC_DB_72_DB_TARGET_BIT               0xFF
#define USB3HC_DB_72_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_72_RSVD29_MASK                 0xFF00
#define USB3HC_DB_72_RSVD29_SHIFT                8 
#define USB3HC_DB_72_RSVD29_BIT                  0xFF
#define USB3HC_DB_72_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_72_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_72_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_72_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_72_DB_STREAM_ID_BITWIDTH       16
// DB_73 Register
#define USB3HC_DB_73_OFS                         0x000005A4
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_73_DB_TARGET_MASK              0xFF
#define USB3HC_DB_73_DB_TARGET_SHIFT             0 
#define USB3HC_DB_73_DB_TARGET_BIT               0xFF
#define USB3HC_DB_73_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_73_RSVD29_MASK                 0xFF00
#define USB3HC_DB_73_RSVD29_SHIFT                8 
#define USB3HC_DB_73_RSVD29_BIT                  0xFF
#define USB3HC_DB_73_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_73_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_73_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_73_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_73_DB_STREAM_ID_BITWIDTH       16
// DB_74 Register
#define USB3HC_DB_74_OFS                         0x000005A8
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_74_DB_TARGET_MASK              0xFF
#define USB3HC_DB_74_DB_TARGET_SHIFT             0 
#define USB3HC_DB_74_DB_TARGET_BIT               0xFF
#define USB3HC_DB_74_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_74_RSVD29_MASK                 0xFF00
#define USB3HC_DB_74_RSVD29_SHIFT                8 
#define USB3HC_DB_74_RSVD29_BIT                  0xFF
#define USB3HC_DB_74_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_74_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_74_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_74_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_74_DB_STREAM_ID_BITWIDTH       16
// DB_75 Register
#define USB3HC_DB_75_OFS                         0x000005AC
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_75_DB_TARGET_MASK              0xFF
#define USB3HC_DB_75_DB_TARGET_SHIFT             0 
#define USB3HC_DB_75_DB_TARGET_BIT               0xFF
#define USB3HC_DB_75_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_75_RSVD29_MASK                 0xFF00
#define USB3HC_DB_75_RSVD29_SHIFT                8 
#define USB3HC_DB_75_RSVD29_BIT                  0xFF
#define USB3HC_DB_75_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_75_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_75_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_75_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_75_DB_STREAM_ID_BITWIDTH       16
// DB_76 Register
#define USB3HC_DB_76_OFS                         0x000005B0
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_76_DB_TARGET_MASK              0xFF
#define USB3HC_DB_76_DB_TARGET_SHIFT             0 
#define USB3HC_DB_76_DB_TARGET_BIT               0xFF
#define USB3HC_DB_76_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_76_RSVD29_MASK                 0xFF00
#define USB3HC_DB_76_RSVD29_SHIFT                8 
#define USB3HC_DB_76_RSVD29_BIT                  0xFF
#define USB3HC_DB_76_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_76_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_76_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_76_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_76_DB_STREAM_ID_BITWIDTH       16
// DB_77 Register
#define USB3HC_DB_77_OFS                         0x000005B4
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_77_DB_TARGET_MASK              0xFF
#define USB3HC_DB_77_DB_TARGET_SHIFT             0 
#define USB3HC_DB_77_DB_TARGET_BIT               0xFF
#define USB3HC_DB_77_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_77_RSVD29_MASK                 0xFF00
#define USB3HC_DB_77_RSVD29_SHIFT                8 
#define USB3HC_DB_77_RSVD29_BIT                  0xFF
#define USB3HC_DB_77_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_77_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_77_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_77_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_77_DB_STREAM_ID_BITWIDTH       16
// DB_78 Register
#define USB3HC_DB_78_OFS                         0x000005B8
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_78_DB_TARGET_MASK              0xFF
#define USB3HC_DB_78_DB_TARGET_SHIFT             0 
#define USB3HC_DB_78_DB_TARGET_BIT               0xFF
#define USB3HC_DB_78_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_78_RSVD29_MASK                 0xFF00
#define USB3HC_DB_78_RSVD29_SHIFT                8 
#define USB3HC_DB_78_RSVD29_BIT                  0xFF
#define USB3HC_DB_78_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_78_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_78_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_78_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_78_DB_STREAM_ID_BITWIDTH       16
// DB_79 Register
#define USB3HC_DB_79_OFS                         0x000005BC
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_79_DB_TARGET_MASK              0xFF
#define USB3HC_DB_79_DB_TARGET_SHIFT             0 
#define USB3HC_DB_79_DB_TARGET_BIT               0xFF
#define USB3HC_DB_79_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_79_RSVD29_MASK                 0xFF00
#define USB3HC_DB_79_RSVD29_SHIFT                8 
#define USB3HC_DB_79_RSVD29_BIT                  0xFF
#define USB3HC_DB_79_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_79_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_79_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_79_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_79_DB_STREAM_ID_BITWIDTH       16
// DB_80 Register
#define USB3HC_DB_80_OFS                         0x000005C0
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_80_DB_TARGET_MASK              0xFF
#define USB3HC_DB_80_DB_TARGET_SHIFT             0 
#define USB3HC_DB_80_DB_TARGET_BIT               0xFF
#define USB3HC_DB_80_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_80_RSVD29_MASK                 0xFF00
#define USB3HC_DB_80_RSVD29_SHIFT                8 
#define USB3HC_DB_80_RSVD29_BIT                  0xFF
#define USB3HC_DB_80_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_80_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_80_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_80_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_80_DB_STREAM_ID_BITWIDTH       16
// DB_81 Register
#define USB3HC_DB_81_OFS                         0x000005C4
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_81_DB_TARGET_MASK              0xFF
#define USB3HC_DB_81_DB_TARGET_SHIFT             0 
#define USB3HC_DB_81_DB_TARGET_BIT               0xFF
#define USB3HC_DB_81_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_81_RSVD29_MASK                 0xFF00
#define USB3HC_DB_81_RSVD29_SHIFT                8 
#define USB3HC_DB_81_RSVD29_BIT                  0xFF
#define USB3HC_DB_81_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_81_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_81_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_81_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_81_DB_STREAM_ID_BITWIDTH       16
// DB_82 Register
#define USB3HC_DB_82_OFS                         0x000005C8
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_82_DB_TARGET_MASK              0xFF
#define USB3HC_DB_82_DB_TARGET_SHIFT             0 
#define USB3HC_DB_82_DB_TARGET_BIT               0xFF
#define USB3HC_DB_82_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_82_RSVD29_MASK                 0xFF00
#define USB3HC_DB_82_RSVD29_SHIFT                8 
#define USB3HC_DB_82_RSVD29_BIT                  0xFF
#define USB3HC_DB_82_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_82_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_82_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_82_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_82_DB_STREAM_ID_BITWIDTH       16
// DB_83 Register
#define USB3HC_DB_83_OFS                         0x000005CC
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_83_DB_TARGET_MASK              0xFF
#define USB3HC_DB_83_DB_TARGET_SHIFT             0 
#define USB3HC_DB_83_DB_TARGET_BIT               0xFF
#define USB3HC_DB_83_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_83_RSVD29_MASK                 0xFF00
#define USB3HC_DB_83_RSVD29_SHIFT                8 
#define USB3HC_DB_83_RSVD29_BIT                  0xFF
#define USB3HC_DB_83_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_83_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_83_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_83_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_83_DB_STREAM_ID_BITWIDTH       16
// DB_84 Register
#define USB3HC_DB_84_OFS                         0x000005D0
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_84_DB_TARGET_MASK              0xFF
#define USB3HC_DB_84_DB_TARGET_SHIFT             0 
#define USB3HC_DB_84_DB_TARGET_BIT               0xFF
#define USB3HC_DB_84_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_84_RSVD29_MASK                 0xFF00
#define USB3HC_DB_84_RSVD29_SHIFT                8 
#define USB3HC_DB_84_RSVD29_BIT                  0xFF
#define USB3HC_DB_84_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_84_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_84_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_84_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_84_DB_STREAM_ID_BITWIDTH       16
// DB_85 Register
#define USB3HC_DB_85_OFS                         0x000005D4
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_85_DB_TARGET_MASK              0xFF
#define USB3HC_DB_85_DB_TARGET_SHIFT             0 
#define USB3HC_DB_85_DB_TARGET_BIT               0xFF
#define USB3HC_DB_85_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_85_RSVD29_MASK                 0xFF00
#define USB3HC_DB_85_RSVD29_SHIFT                8 
#define USB3HC_DB_85_RSVD29_BIT                  0xFF
#define USB3HC_DB_85_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_85_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_85_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_85_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_85_DB_STREAM_ID_BITWIDTH       16
// DB_86 Register
#define USB3HC_DB_86_OFS                         0x000005D8
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_86_DB_TARGET_MASK              0xFF
#define USB3HC_DB_86_DB_TARGET_SHIFT             0 
#define USB3HC_DB_86_DB_TARGET_BIT               0xFF
#define USB3HC_DB_86_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_86_RSVD29_MASK                 0xFF00
#define USB3HC_DB_86_RSVD29_SHIFT                8 
#define USB3HC_DB_86_RSVD29_BIT                  0xFF
#define USB3HC_DB_86_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_86_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_86_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_86_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_86_DB_STREAM_ID_BITWIDTH       16
// DB_87 Register
#define USB3HC_DB_87_OFS                         0x000005DC
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_87_DB_TARGET_MASK              0xFF
#define USB3HC_DB_87_DB_TARGET_SHIFT             0 
#define USB3HC_DB_87_DB_TARGET_BIT               0xFF
#define USB3HC_DB_87_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_87_RSVD29_MASK                 0xFF00
#define USB3HC_DB_87_RSVD29_SHIFT                8 
#define USB3HC_DB_87_RSVD29_BIT                  0xFF
#define USB3HC_DB_87_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_87_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_87_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_87_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_87_DB_STREAM_ID_BITWIDTH       16
// DB_88 Register
#define USB3HC_DB_88_OFS                         0x000005E0
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_88_DB_TARGET_MASK              0xFF
#define USB3HC_DB_88_DB_TARGET_SHIFT             0 
#define USB3HC_DB_88_DB_TARGET_BIT               0xFF
#define USB3HC_DB_88_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_88_RSVD29_MASK                 0xFF00
#define USB3HC_DB_88_RSVD29_SHIFT                8 
#define USB3HC_DB_88_RSVD29_BIT                  0xFF
#define USB3HC_DB_88_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_88_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_88_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_88_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_88_DB_STREAM_ID_BITWIDTH       16
// DB_89 Register
#define USB3HC_DB_89_OFS                         0x000005E4
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_89_DB_TARGET_MASK              0xFF
#define USB3HC_DB_89_DB_TARGET_SHIFT             0 
#define USB3HC_DB_89_DB_TARGET_BIT               0xFF
#define USB3HC_DB_89_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_89_RSVD29_MASK                 0xFF00
#define USB3HC_DB_89_RSVD29_SHIFT                8 
#define USB3HC_DB_89_RSVD29_BIT                  0xFF
#define USB3HC_DB_89_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_89_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_89_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_89_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_89_DB_STREAM_ID_BITWIDTH       16
// DB_90 Register
#define USB3HC_DB_90_OFS                         0x000005E8
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_90_DB_TARGET_MASK              0xFF
#define USB3HC_DB_90_DB_TARGET_SHIFT             0 
#define USB3HC_DB_90_DB_TARGET_BIT               0xFF
#define USB3HC_DB_90_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_90_RSVD29_MASK                 0xFF00
#define USB3HC_DB_90_RSVD29_SHIFT                8 
#define USB3HC_DB_90_RSVD29_BIT                  0xFF
#define USB3HC_DB_90_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_90_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_90_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_90_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_90_DB_STREAM_ID_BITWIDTH       16
// DB_91 Register
#define USB3HC_DB_91_OFS                         0x000005EC
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_91_DB_TARGET_MASK              0xFF
#define USB3HC_DB_91_DB_TARGET_SHIFT             0 
#define USB3HC_DB_91_DB_TARGET_BIT               0xFF
#define USB3HC_DB_91_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_91_RSVD29_MASK                 0xFF00
#define USB3HC_DB_91_RSVD29_SHIFT                8 
#define USB3HC_DB_91_RSVD29_BIT                  0xFF
#define USB3HC_DB_91_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_91_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_91_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_91_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_91_DB_STREAM_ID_BITWIDTH       16
// DB_92 Register
#define USB3HC_DB_92_OFS                         0x000005F0
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_92_DB_TARGET_MASK              0xFF
#define USB3HC_DB_92_DB_TARGET_SHIFT             0 
#define USB3HC_DB_92_DB_TARGET_BIT               0xFF
#define USB3HC_DB_92_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_92_RSVD29_MASK                 0xFF00
#define USB3HC_DB_92_RSVD29_SHIFT                8 
#define USB3HC_DB_92_RSVD29_BIT                  0xFF
#define USB3HC_DB_92_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_92_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_92_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_92_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_92_DB_STREAM_ID_BITWIDTH       16
// DB_93 Register
#define USB3HC_DB_93_OFS                         0x000005F4
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_93_DB_TARGET_MASK              0xFF
#define USB3HC_DB_93_DB_TARGET_SHIFT             0 
#define USB3HC_DB_93_DB_TARGET_BIT               0xFF
#define USB3HC_DB_93_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_93_RSVD29_MASK                 0xFF00
#define USB3HC_DB_93_RSVD29_SHIFT                8 
#define USB3HC_DB_93_RSVD29_BIT                  0xFF
#define USB3HC_DB_93_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_93_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_93_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_93_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_93_DB_STREAM_ID_BITWIDTH       16
// DB_94 Register
#define USB3HC_DB_94_OFS                         0x000005F8
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_94_DB_TARGET_MASK              0xFF
#define USB3HC_DB_94_DB_TARGET_SHIFT             0 
#define USB3HC_DB_94_DB_TARGET_BIT               0xFF
#define USB3HC_DB_94_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_94_RSVD29_MASK                 0xFF00
#define USB3HC_DB_94_RSVD29_SHIFT                8 
#define USB3HC_DB_94_RSVD29_BIT                  0xFF
#define USB3HC_DB_94_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_94_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_94_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_94_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_94_DB_STREAM_ID_BITWIDTH       16
// DB_95 Register
#define USB3HC_DB_95_OFS                         0x000005FC
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_95_DB_TARGET_MASK              0xFF
#define USB3HC_DB_95_DB_TARGET_SHIFT             0 
#define USB3HC_DB_95_DB_TARGET_BIT               0xFF
#define USB3HC_DB_95_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_95_RSVD29_MASK                 0xFF00
#define USB3HC_DB_95_RSVD29_SHIFT                8 
#define USB3HC_DB_95_RSVD29_BIT                  0xFF
#define USB3HC_DB_95_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_95_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_95_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_95_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_95_DB_STREAM_ID_BITWIDTH       16
// DB_96 Register
#define USB3HC_DB_96_OFS                         0x00000600
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_96_DB_TARGET_MASK              0xFF
#define USB3HC_DB_96_DB_TARGET_SHIFT             0 
#define USB3HC_DB_96_DB_TARGET_BIT               0xFF
#define USB3HC_DB_96_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_96_RSVD29_MASK                 0xFF00
#define USB3HC_DB_96_RSVD29_SHIFT                8 
#define USB3HC_DB_96_RSVD29_BIT                  0xFF
#define USB3HC_DB_96_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_96_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_96_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_96_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_96_DB_STREAM_ID_BITWIDTH       16
// DB_97 Register
#define USB3HC_DB_97_OFS                         0x00000604
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_97_DB_TARGET_MASK              0xFF
#define USB3HC_DB_97_DB_TARGET_SHIFT             0 
#define USB3HC_DB_97_DB_TARGET_BIT               0xFF
#define USB3HC_DB_97_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_97_RSVD29_MASK                 0xFF00
#define USB3HC_DB_97_RSVD29_SHIFT                8 
#define USB3HC_DB_97_RSVD29_BIT                  0xFF
#define USB3HC_DB_97_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_97_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_97_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_97_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_97_DB_STREAM_ID_BITWIDTH       16
// DB_98 Register
#define USB3HC_DB_98_OFS                         0x00000608
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_98_DB_TARGET_MASK              0xFF
#define USB3HC_DB_98_DB_TARGET_SHIFT             0 
#define USB3HC_DB_98_DB_TARGET_BIT               0xFF
#define USB3HC_DB_98_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_98_RSVD29_MASK                 0xFF00
#define USB3HC_DB_98_RSVD29_SHIFT                8 
#define USB3HC_DB_98_RSVD29_BIT                  0xFF
#define USB3HC_DB_98_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_98_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_98_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_98_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_98_DB_STREAM_ID_BITWIDTH       16
// DB_99 Register
#define USB3HC_DB_99_OFS                         0x0000060C
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_99_DB_TARGET_MASK              0xFF
#define USB3HC_DB_99_DB_TARGET_SHIFT             0 
#define USB3HC_DB_99_DB_TARGET_BIT               0xFF
#define USB3HC_DB_99_DB_TARGET_BITWIDTH          8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_99_RSVD29_MASK                 0xFF00
#define USB3HC_DB_99_RSVD29_SHIFT                8 
#define USB3HC_DB_99_RSVD29_BIT                  0xFF
#define USB3HC_DB_99_RSVD29_BITWIDTH             8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_99_DB_STREAM_ID_MASK           0xFFFF0000
#define USB3HC_DB_99_DB_STREAM_ID_SHIFT          16 
#define USB3HC_DB_99_DB_STREAM_ID_BIT            0xFFFF
#define USB3HC_DB_99_DB_STREAM_ID_BITWIDTH       16
// DB_100 Register
#define USB3HC_DB_100_OFS                        0x00000610
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_100_DB_TARGET_MASK             0xFF
#define USB3HC_DB_100_DB_TARGET_SHIFT            0 
#define USB3HC_DB_100_DB_TARGET_BIT              0xFF
#define USB3HC_DB_100_DB_TARGET_BITWIDTH         8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_100_RSVD29_MASK                0xFF00
#define USB3HC_DB_100_RSVD29_SHIFT               8 
#define USB3HC_DB_100_RSVD29_BIT                 0xFF
#define USB3HC_DB_100_RSVD29_BITWIDTH            8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_100_DB_STREAM_ID_MASK          0xFFFF0000
#define USB3HC_DB_100_DB_STREAM_ID_SHIFT         16 
#define USB3HC_DB_100_DB_STREAM_ID_BIT           0xFFFF
#define USB3HC_DB_100_DB_STREAM_ID_BITWIDTH      16
// DB_101 Register
#define USB3HC_DB_101_OFS                        0x00000614
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_101_DB_TARGET_MASK             0xFF
#define USB3HC_DB_101_DB_TARGET_SHIFT            0 
#define USB3HC_DB_101_DB_TARGET_BIT              0xFF
#define USB3HC_DB_101_DB_TARGET_BITWIDTH         8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_101_RSVD29_MASK                0xFF00
#define USB3HC_DB_101_RSVD29_SHIFT               8 
#define USB3HC_DB_101_RSVD29_BIT                 0xFF
#define USB3HC_DB_101_RSVD29_BITWIDTH            8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_101_DB_STREAM_ID_MASK          0xFFFF0000
#define USB3HC_DB_101_DB_STREAM_ID_SHIFT         16 
#define USB3HC_DB_101_DB_STREAM_ID_BIT           0xFFFF
#define USB3HC_DB_101_DB_STREAM_ID_BITWIDTH      16
// DB_102 Register
#define USB3HC_DB_102_OFS                        0x00000618
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_102_DB_TARGET_MASK             0xFF
#define USB3HC_DB_102_DB_TARGET_SHIFT            0 
#define USB3HC_DB_102_DB_TARGET_BIT              0xFF
#define USB3HC_DB_102_DB_TARGET_BITWIDTH         8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_102_RSVD29_MASK                0xFF00
#define USB3HC_DB_102_RSVD29_SHIFT               8 
#define USB3HC_DB_102_RSVD29_BIT                 0xFF
#define USB3HC_DB_102_RSVD29_BITWIDTH            8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_102_DB_STREAM_ID_MASK          0xFFFF0000
#define USB3HC_DB_102_DB_STREAM_ID_SHIFT         16 
#define USB3HC_DB_102_DB_STREAM_ID_BIT           0xFFFF
#define USB3HC_DB_102_DB_STREAM_ID_BITWIDTH      16
// DB_103 Register
#define USB3HC_DB_103_OFS                        0x0000061C
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_103_DB_TARGET_MASK             0xFF
#define USB3HC_DB_103_DB_TARGET_SHIFT            0 
#define USB3HC_DB_103_DB_TARGET_BIT              0xFF
#define USB3HC_DB_103_DB_TARGET_BITWIDTH         8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_103_RSVD29_MASK                0xFF00
#define USB3HC_DB_103_RSVD29_SHIFT               8 
#define USB3HC_DB_103_RSVD29_BIT                 0xFF
#define USB3HC_DB_103_RSVD29_BITWIDTH            8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_103_DB_STREAM_ID_MASK          0xFFFF0000
#define USB3HC_DB_103_DB_STREAM_ID_SHIFT         16 
#define USB3HC_DB_103_DB_STREAM_ID_BIT           0xFFFF
#define USB3HC_DB_103_DB_STREAM_ID_BITWIDTH      16
// DB_104 Register
#define USB3HC_DB_104_OFS                        0x00000620
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_104_DB_TARGET_MASK             0xFF
#define USB3HC_DB_104_DB_TARGET_SHIFT            0 
#define USB3HC_DB_104_DB_TARGET_BIT              0xFF
#define USB3HC_DB_104_DB_TARGET_BITWIDTH         8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_104_RSVD29_MASK                0xFF00
#define USB3HC_DB_104_RSVD29_SHIFT               8 
#define USB3HC_DB_104_RSVD29_BIT                 0xFF
#define USB3HC_DB_104_RSVD29_BITWIDTH            8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_104_DB_STREAM_ID_MASK          0xFFFF0000
#define USB3HC_DB_104_DB_STREAM_ID_SHIFT         16 
#define USB3HC_DB_104_DB_STREAM_ID_BIT           0xFFFF
#define USB3HC_DB_104_DB_STREAM_ID_BITWIDTH      16
// DB_105 Register
#define USB3HC_DB_105_OFS                        0x00000624
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_105_DB_TARGET_MASK             0xFF
#define USB3HC_DB_105_DB_TARGET_SHIFT            0 
#define USB3HC_DB_105_DB_TARGET_BIT              0xFF
#define USB3HC_DB_105_DB_TARGET_BITWIDTH         8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_105_RSVD29_MASK                0xFF00
#define USB3HC_DB_105_RSVD29_SHIFT               8 
#define USB3HC_DB_105_RSVD29_BIT                 0xFF
#define USB3HC_DB_105_RSVD29_BITWIDTH            8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_105_DB_STREAM_ID_MASK          0xFFFF0000
#define USB3HC_DB_105_DB_STREAM_ID_SHIFT         16 
#define USB3HC_DB_105_DB_STREAM_ID_BIT           0xFFFF
#define USB3HC_DB_105_DB_STREAM_ID_BITWIDTH      16
// DB_106 Register
#define USB3HC_DB_106_OFS                        0x00000628
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_106_DB_TARGET_MASK             0xFF
#define USB3HC_DB_106_DB_TARGET_SHIFT            0 
#define USB3HC_DB_106_DB_TARGET_BIT              0xFF
#define USB3HC_DB_106_DB_TARGET_BITWIDTH         8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_106_RSVD29_MASK                0xFF00
#define USB3HC_DB_106_RSVD29_SHIFT               8 
#define USB3HC_DB_106_RSVD29_BIT                 0xFF
#define USB3HC_DB_106_RSVD29_BITWIDTH            8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_106_DB_STREAM_ID_MASK          0xFFFF0000
#define USB3HC_DB_106_DB_STREAM_ID_SHIFT         16 
#define USB3HC_DB_106_DB_STREAM_ID_BIT           0xFFFF
#define USB3HC_DB_106_DB_STREAM_ID_BITWIDTH      16
// DB_107 Register
#define USB3HC_DB_107_OFS                        0x0000062C
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_107_DB_TARGET_MASK             0xFF
#define USB3HC_DB_107_DB_TARGET_SHIFT            0 
#define USB3HC_DB_107_DB_TARGET_BIT              0xFF
#define USB3HC_DB_107_DB_TARGET_BITWIDTH         8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_107_RSVD29_MASK                0xFF00
#define USB3HC_DB_107_RSVD29_SHIFT               8 
#define USB3HC_DB_107_RSVD29_BIT                 0xFF
#define USB3HC_DB_107_RSVD29_BITWIDTH            8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_107_DB_STREAM_ID_MASK          0xFFFF0000
#define USB3HC_DB_107_DB_STREAM_ID_SHIFT         16 
#define USB3HC_DB_107_DB_STREAM_ID_BIT           0xFFFF
#define USB3HC_DB_107_DB_STREAM_ID_BITWIDTH      16
// DB_108 Register
#define USB3HC_DB_108_OFS                        0x00000630
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_108_DB_TARGET_MASK             0xFF
#define USB3HC_DB_108_DB_TARGET_SHIFT            0 
#define USB3HC_DB_108_DB_TARGET_BIT              0xFF
#define USB3HC_DB_108_DB_TARGET_BITWIDTH         8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_108_RSVD29_MASK                0xFF00
#define USB3HC_DB_108_RSVD29_SHIFT               8 
#define USB3HC_DB_108_RSVD29_BIT                 0xFF
#define USB3HC_DB_108_RSVD29_BITWIDTH            8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_108_DB_STREAM_ID_MASK          0xFFFF0000
#define USB3HC_DB_108_DB_STREAM_ID_SHIFT         16 
#define USB3HC_DB_108_DB_STREAM_ID_BIT           0xFFFF
#define USB3HC_DB_108_DB_STREAM_ID_BITWIDTH      16
// DB_109 Register
#define USB3HC_DB_109_OFS                        0x00000634
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_109_DB_TARGET_MASK             0xFF
#define USB3HC_DB_109_DB_TARGET_SHIFT            0 
#define USB3HC_DB_109_DB_TARGET_BIT              0xFF
#define USB3HC_DB_109_DB_TARGET_BITWIDTH         8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_109_RSVD29_MASK                0xFF00
#define USB3HC_DB_109_RSVD29_SHIFT               8 
#define USB3HC_DB_109_RSVD29_BIT                 0xFF
#define USB3HC_DB_109_RSVD29_BITWIDTH            8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_109_DB_STREAM_ID_MASK          0xFFFF0000
#define USB3HC_DB_109_DB_STREAM_ID_SHIFT         16 
#define USB3HC_DB_109_DB_STREAM_ID_BIT           0xFFFF
#define USB3HC_DB_109_DB_STREAM_ID_BITWIDTH      16
// DB_110 Register
#define USB3HC_DB_110_OFS                        0x00000638
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_110_DB_TARGET_MASK             0xFF
#define USB3HC_DB_110_DB_TARGET_SHIFT            0 
#define USB3HC_DB_110_DB_TARGET_BIT              0xFF
#define USB3HC_DB_110_DB_TARGET_BITWIDTH         8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_110_RSVD29_MASK                0xFF00
#define USB3HC_DB_110_RSVD29_SHIFT               8 
#define USB3HC_DB_110_RSVD29_BIT                 0xFF
#define USB3HC_DB_110_RSVD29_BITWIDTH            8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_110_DB_STREAM_ID_MASK          0xFFFF0000
#define USB3HC_DB_110_DB_STREAM_ID_SHIFT         16 
#define USB3HC_DB_110_DB_STREAM_ID_BIT           0xFFFF
#define USB3HC_DB_110_DB_STREAM_ID_BITWIDTH      16
// DB_111 Register
#define USB3HC_DB_111_OFS                        0x0000063C
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_111_DB_TARGET_MASK             0xFF
#define USB3HC_DB_111_DB_TARGET_SHIFT            0 
#define USB3HC_DB_111_DB_TARGET_BIT              0xFF
#define USB3HC_DB_111_DB_TARGET_BITWIDTH         8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_111_RSVD29_MASK                0xFF00
#define USB3HC_DB_111_RSVD29_SHIFT               8 
#define USB3HC_DB_111_RSVD29_BIT                 0xFF
#define USB3HC_DB_111_RSVD29_BITWIDTH            8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_111_DB_STREAM_ID_MASK          0xFFFF0000
#define USB3HC_DB_111_DB_STREAM_ID_SHIFT         16 
#define USB3HC_DB_111_DB_STREAM_ID_BIT           0xFFFF
#define USB3HC_DB_111_DB_STREAM_ID_BITWIDTH      16
// DB_112 Register
#define USB3HC_DB_112_OFS                        0x00000640
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_112_DB_TARGET_MASK             0xFF
#define USB3HC_DB_112_DB_TARGET_SHIFT            0 
#define USB3HC_DB_112_DB_TARGET_BIT              0xFF
#define USB3HC_DB_112_DB_TARGET_BITWIDTH         8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_112_RSVD29_MASK                0xFF00
#define USB3HC_DB_112_RSVD29_SHIFT               8 
#define USB3HC_DB_112_RSVD29_BIT                 0xFF
#define USB3HC_DB_112_RSVD29_BITWIDTH            8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_112_DB_STREAM_ID_MASK          0xFFFF0000
#define USB3HC_DB_112_DB_STREAM_ID_SHIFT         16 
#define USB3HC_DB_112_DB_STREAM_ID_BIT           0xFFFF
#define USB3HC_DB_112_DB_STREAM_ID_BITWIDTH      16
// DB_113 Register
#define USB3HC_DB_113_OFS                        0x00000644
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_113_DB_TARGET_MASK             0xFF
#define USB3HC_DB_113_DB_TARGET_SHIFT            0 
#define USB3HC_DB_113_DB_TARGET_BIT              0xFF
#define USB3HC_DB_113_DB_TARGET_BITWIDTH         8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_113_RSVD29_MASK                0xFF00
#define USB3HC_DB_113_RSVD29_SHIFT               8 
#define USB3HC_DB_113_RSVD29_BIT                 0xFF
#define USB3HC_DB_113_RSVD29_BITWIDTH            8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_113_DB_STREAM_ID_MASK          0xFFFF0000
#define USB3HC_DB_113_DB_STREAM_ID_SHIFT         16 
#define USB3HC_DB_113_DB_STREAM_ID_BIT           0xFFFF
#define USB3HC_DB_113_DB_STREAM_ID_BITWIDTH      16
// DB_114 Register
#define USB3HC_DB_114_OFS                        0x00000648
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_114_DB_TARGET_MASK             0xFF
#define USB3HC_DB_114_DB_TARGET_SHIFT            0 
#define USB3HC_DB_114_DB_TARGET_BIT              0xFF
#define USB3HC_DB_114_DB_TARGET_BITWIDTH         8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_114_RSVD29_MASK                0xFF00
#define USB3HC_DB_114_RSVD29_SHIFT               8 
#define USB3HC_DB_114_RSVD29_BIT                 0xFF
#define USB3HC_DB_114_RSVD29_BITWIDTH            8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_114_DB_STREAM_ID_MASK          0xFFFF0000
#define USB3HC_DB_114_DB_STREAM_ID_SHIFT         16 
#define USB3HC_DB_114_DB_STREAM_ID_BIT           0xFFFF
#define USB3HC_DB_114_DB_STREAM_ID_BITWIDTH      16
// DB_115 Register
#define USB3HC_DB_115_OFS                        0x0000064C
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_115_DB_TARGET_MASK             0xFF
#define USB3HC_DB_115_DB_TARGET_SHIFT            0 
#define USB3HC_DB_115_DB_TARGET_BIT              0xFF
#define USB3HC_DB_115_DB_TARGET_BITWIDTH         8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_115_RSVD29_MASK                0xFF00
#define USB3HC_DB_115_RSVD29_SHIFT               8 
#define USB3HC_DB_115_RSVD29_BIT                 0xFF
#define USB3HC_DB_115_RSVD29_BITWIDTH            8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_115_DB_STREAM_ID_MASK          0xFFFF0000
#define USB3HC_DB_115_DB_STREAM_ID_SHIFT         16 
#define USB3HC_DB_115_DB_STREAM_ID_BIT           0xFFFF
#define USB3HC_DB_115_DB_STREAM_ID_BITWIDTH      16
// DB_116 Register
#define USB3HC_DB_116_OFS                        0x00000650
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_116_DB_TARGET_MASK             0xFF
#define USB3HC_DB_116_DB_TARGET_SHIFT            0 
#define USB3HC_DB_116_DB_TARGET_BIT              0xFF
#define USB3HC_DB_116_DB_TARGET_BITWIDTH         8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_116_RSVD29_MASK                0xFF00
#define USB3HC_DB_116_RSVD29_SHIFT               8 
#define USB3HC_DB_116_RSVD29_BIT                 0xFF
#define USB3HC_DB_116_RSVD29_BITWIDTH            8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_116_DB_STREAM_ID_MASK          0xFFFF0000
#define USB3HC_DB_116_DB_STREAM_ID_SHIFT         16 
#define USB3HC_DB_116_DB_STREAM_ID_BIT           0xFFFF
#define USB3HC_DB_116_DB_STREAM_ID_BITWIDTH      16
// DB_117 Register
#define USB3HC_DB_117_OFS                        0x00000654
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_117_DB_TARGET_MASK             0xFF
#define USB3HC_DB_117_DB_TARGET_SHIFT            0 
#define USB3HC_DB_117_DB_TARGET_BIT              0xFF
#define USB3HC_DB_117_DB_TARGET_BITWIDTH         8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_117_RSVD29_MASK                0xFF00
#define USB3HC_DB_117_RSVD29_SHIFT               8 
#define USB3HC_DB_117_RSVD29_BIT                 0xFF
#define USB3HC_DB_117_RSVD29_BITWIDTH            8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_117_DB_STREAM_ID_MASK          0xFFFF0000
#define USB3HC_DB_117_DB_STREAM_ID_SHIFT         16 
#define USB3HC_DB_117_DB_STREAM_ID_BIT           0xFFFF
#define USB3HC_DB_117_DB_STREAM_ID_BITWIDTH      16
// DB_118 Register
#define USB3HC_DB_118_OFS                        0x00000658
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_118_DB_TARGET_MASK             0xFF
#define USB3HC_DB_118_DB_TARGET_SHIFT            0 
#define USB3HC_DB_118_DB_TARGET_BIT              0xFF
#define USB3HC_DB_118_DB_TARGET_BITWIDTH         8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_118_RSVD29_MASK                0xFF00
#define USB3HC_DB_118_RSVD29_SHIFT               8 
#define USB3HC_DB_118_RSVD29_BIT                 0xFF
#define USB3HC_DB_118_RSVD29_BITWIDTH            8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_118_DB_STREAM_ID_MASK          0xFFFF0000
#define USB3HC_DB_118_DB_STREAM_ID_SHIFT         16 
#define USB3HC_DB_118_DB_STREAM_ID_BIT           0xFFFF
#define USB3HC_DB_118_DB_STREAM_ID_BITWIDTH      16
// DB_119 Register
#define USB3HC_DB_119_OFS                        0x0000065C
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_119_DB_TARGET_MASK             0xFF
#define USB3HC_DB_119_DB_TARGET_SHIFT            0 
#define USB3HC_DB_119_DB_TARGET_BIT              0xFF
#define USB3HC_DB_119_DB_TARGET_BITWIDTH         8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_119_RSVD29_MASK                0xFF00
#define USB3HC_DB_119_RSVD29_SHIFT               8 
#define USB3HC_DB_119_RSVD29_BIT                 0xFF
#define USB3HC_DB_119_RSVD29_BITWIDTH            8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_119_DB_STREAM_ID_MASK          0xFFFF0000
#define USB3HC_DB_119_DB_STREAM_ID_SHIFT         16 
#define USB3HC_DB_119_DB_STREAM_ID_BIT           0xFFFF
#define USB3HC_DB_119_DB_STREAM_ID_BITWIDTH      16
// DB_120 Register
#define USB3HC_DB_120_OFS                        0x00000660
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_120_DB_TARGET_MASK             0xFF
#define USB3HC_DB_120_DB_TARGET_SHIFT            0 
#define USB3HC_DB_120_DB_TARGET_BIT              0xFF
#define USB3HC_DB_120_DB_TARGET_BITWIDTH         8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_120_RSVD29_MASK                0xFF00
#define USB3HC_DB_120_RSVD29_SHIFT               8 
#define USB3HC_DB_120_RSVD29_BIT                 0xFF
#define USB3HC_DB_120_RSVD29_BITWIDTH            8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_120_DB_STREAM_ID_MASK          0xFFFF0000
#define USB3HC_DB_120_DB_STREAM_ID_SHIFT         16 
#define USB3HC_DB_120_DB_STREAM_ID_BIT           0xFFFF
#define USB3HC_DB_120_DB_STREAM_ID_BITWIDTH      16
// DB_121 Register
#define USB3HC_DB_121_OFS                        0x00000664
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_121_DB_TARGET_MASK             0xFF
#define USB3HC_DB_121_DB_TARGET_SHIFT            0 
#define USB3HC_DB_121_DB_TARGET_BIT              0xFF
#define USB3HC_DB_121_DB_TARGET_BITWIDTH         8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_121_RSVD29_MASK                0xFF00
#define USB3HC_DB_121_RSVD29_SHIFT               8 
#define USB3HC_DB_121_RSVD29_BIT                 0xFF
#define USB3HC_DB_121_RSVD29_BITWIDTH            8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_121_DB_STREAM_ID_MASK          0xFFFF0000
#define USB3HC_DB_121_DB_STREAM_ID_SHIFT         16 
#define USB3HC_DB_121_DB_STREAM_ID_BIT           0xFFFF
#define USB3HC_DB_121_DB_STREAM_ID_BITWIDTH      16
// DB_122 Register
#define USB3HC_DB_122_OFS                        0x00000668
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_122_DB_TARGET_MASK             0xFF
#define USB3HC_DB_122_DB_TARGET_SHIFT            0 
#define USB3HC_DB_122_DB_TARGET_BIT              0xFF
#define USB3HC_DB_122_DB_TARGET_BITWIDTH         8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_122_RSVD29_MASK                0xFF00
#define USB3HC_DB_122_RSVD29_SHIFT               8 
#define USB3HC_DB_122_RSVD29_BIT                 0xFF
#define USB3HC_DB_122_RSVD29_BITWIDTH            8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_122_DB_STREAM_ID_MASK          0xFFFF0000
#define USB3HC_DB_122_DB_STREAM_ID_SHIFT         16 
#define USB3HC_DB_122_DB_STREAM_ID_BIT           0xFFFF
#define USB3HC_DB_122_DB_STREAM_ID_BITWIDTH      16
// DB_123 Register
#define USB3HC_DB_123_OFS                        0x0000066C
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_123_DB_TARGET_MASK             0xFF
#define USB3HC_DB_123_DB_TARGET_SHIFT            0 
#define USB3HC_DB_123_DB_TARGET_BIT              0xFF
#define USB3HC_DB_123_DB_TARGET_BITWIDTH         8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_123_RSVD29_MASK                0xFF00
#define USB3HC_DB_123_RSVD29_SHIFT               8 
#define USB3HC_DB_123_RSVD29_BIT                 0xFF
#define USB3HC_DB_123_RSVD29_BITWIDTH            8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_123_DB_STREAM_ID_MASK          0xFFFF0000
#define USB3HC_DB_123_DB_STREAM_ID_SHIFT         16 
#define USB3HC_DB_123_DB_STREAM_ID_BIT           0xFFFF
#define USB3HC_DB_123_DB_STREAM_ID_BITWIDTH      16
// DB_124 Register
#define USB3HC_DB_124_OFS                        0x00000670
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_124_DB_TARGET_MASK             0xFF
#define USB3HC_DB_124_DB_TARGET_SHIFT            0 
#define USB3HC_DB_124_DB_TARGET_BIT              0xFF
#define USB3HC_DB_124_DB_TARGET_BITWIDTH         8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_124_RSVD29_MASK                0xFF00
#define USB3HC_DB_124_RSVD29_SHIFT               8 
#define USB3HC_DB_124_RSVD29_BIT                 0xFF
#define USB3HC_DB_124_RSVD29_BITWIDTH            8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_124_DB_STREAM_ID_MASK          0xFFFF0000
#define USB3HC_DB_124_DB_STREAM_ID_SHIFT         16 
#define USB3HC_DB_124_DB_STREAM_ID_BIT           0xFFFF
#define USB3HC_DB_124_DB_STREAM_ID_BITWIDTH      16
// DB_125 Register
#define USB3HC_DB_125_OFS                        0x00000674
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_125_DB_TARGET_MASK             0xFF
#define USB3HC_DB_125_DB_TARGET_SHIFT            0 
#define USB3HC_DB_125_DB_TARGET_BIT              0xFF
#define USB3HC_DB_125_DB_TARGET_BITWIDTH         8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_125_RSVD29_MASK                0xFF00
#define USB3HC_DB_125_RSVD29_SHIFT               8 
#define USB3HC_DB_125_RSVD29_BIT                 0xFF
#define USB3HC_DB_125_RSVD29_BITWIDTH            8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_125_DB_STREAM_ID_MASK          0xFFFF0000
#define USB3HC_DB_125_DB_STREAM_ID_SHIFT         16 
#define USB3HC_DB_125_DB_STREAM_ID_BIT           0xFFFF
#define USB3HC_DB_125_DB_STREAM_ID_BITWIDTH      16
// DB_126 Register
#define USB3HC_DB_126_OFS                        0x00000678
// DB_TARGET bitfiled (RW) Reset=0
#define USB3HC_DB_126_DB_TARGET_MASK             0xFF
#define USB3HC_DB_126_DB_TARGET_SHIFT            0 
#define USB3HC_DB_126_DB_TARGET_BIT              0xFF
#define USB3HC_DB_126_DB_TARGET_BITWIDTH         8
// RSVD29 bitfiled (RO) Reset=0
#define USB3HC_DB_126_RSVD29_MASK                0xFF00
#define USB3HC_DB_126_RSVD29_SHIFT               8 
#define USB3HC_DB_126_RSVD29_BIT                 0xFF
#define USB3HC_DB_126_RSVD29_BITWIDTH            8
// DB_STREAM_ID bitfiled (RW) Reset=0
#define USB3HC_DB_126_DB_STREAM_ID_MASK          0xFFFF0000
#define USB3HC_DB_126_DB_STREAM_ID_SHIFT         16 
#define USB3HC_DB_126_DB_STREAM_ID_BIT           0xFFFF
#define USB3HC_DB_126_DB_STREAM_ID_BITWIDTH      16
// USBLEGSUP Register
#define USB3HC_USBLEGSUP_OFS                     0x00000880
// CAPABILITY_ID bitfiled (RO) Reset=1
#define USB3HC_USBLEGSUP_CAPABILITY_ID_MASK      0xFF
#define USB3HC_USBLEGSUP_CAPABILITY_ID_SHIFT     0 
#define USB3HC_USBLEGSUP_CAPABILITY_ID_BIT       0xFF
#define USB3HC_USBLEGSUP_CAPABILITY_ID_BITWIDTH  8
// NEXT_CAPABILITY_POINTER bitfiled (RO) Reset=100
#define USB3HC_USBLEGSUP_NEXT_CAPABILITY_POINTER_MASK 0xFF00
#define USB3HC_USBLEGSUP_NEXT_CAPABILITY_POINTER_SHIFT 8 
#define USB3HC_USBLEGSUP_NEXT_CAPABILITY_POINTER_BIT 0xFF
#define USB3HC_USBLEGSUP_NEXT_CAPABILITY_POINTER_BITWIDTH 8
// HC_BIOS_OWNED bitfiled (RW) Reset=0
#define USB3HC_USBLEGSUP_HC_BIOS_OWNED_MASK      0x10000
#define USB3HC_USBLEGSUP_HC_BIOS_OWNED_SHIFT     16 
#define USB3HC_USBLEGSUP_HC_BIOS_OWNED_BIT       0x1
#define USB3HC_USBLEGSUP_HC_BIOS_OWNED_BITWIDTH  1
// RSVD30 bitfiled (RO) Reset=0
#define USB3HC_USBLEGSUP_RSVD30_MASK             0xFE0000
#define USB3HC_USBLEGSUP_RSVD30_SHIFT            17 
#define USB3HC_USBLEGSUP_RSVD30_BIT              0x7F
#define USB3HC_USBLEGSUP_RSVD30_BITWIDTH         7
// HC_OS_OWNED bitfiled (RW) Reset=0
#define USB3HC_USBLEGSUP_HC_OS_OWNED_MASK        0x1000000
#define USB3HC_USBLEGSUP_HC_OS_OWNED_SHIFT       24 
#define USB3HC_USBLEGSUP_HC_OS_OWNED_BIT         0x1
#define USB3HC_USBLEGSUP_HC_OS_OWNED_BITWIDTH    1
// RSVD31 bitfiled (RO) Reset=0
#define USB3HC_USBLEGSUP_RSVD31_MASK             0xFE000000
#define USB3HC_USBLEGSUP_RSVD31_SHIFT            25 
#define USB3HC_USBLEGSUP_RSVD31_BIT              0x7F
#define USB3HC_USBLEGSUP_RSVD31_BITWIDTH         7
// USBLEGCTLSTS Register
#define USB3HC_USBLEGCTLSTS_OFS                  0x00000884
// USB_SMI_ENABLE bitfiled (RW) Reset=0
#define USB3HC_USBLEGCTLSTS_USB_SMI_ENABLE_MASK  0x1
#define USB3HC_USBLEGCTLSTS_USB_SMI_ENABLE_SHIFT 0 
#define USB3HC_USBLEGCTLSTS_USB_SMI_ENABLE_BIT   0x1
#define USB3HC_USBLEGCTLSTS_USB_SMI_ENABLE_BITWIDTH 1
// RSVD32 bitfiled (RO) Reset=0
#define USB3HC_USBLEGCTLSTS_RSVD32_MASK          0xE
#define USB3HC_USBLEGCTLSTS_RSVD32_SHIFT         1 
#define USB3HC_USBLEGCTLSTS_RSVD32_BIT           0x7
#define USB3HC_USBLEGCTLSTS_RSVD32_BITWIDTH      3
// SMI_ON_HOST_E bitfiled (RW) Reset=0
#define USB3HC_USBLEGCTLSTS_SMI_ON_HOST_E_MASK   0x10
#define USB3HC_USBLEGCTLSTS_SMI_ON_HOST_E_SHIFT  4 
#define USB3HC_USBLEGCTLSTS_SMI_ON_HOST_E_BIT    0x1
#define USB3HC_USBLEGCTLSTS_SMI_ON_HOST_E_BITWIDTH 1
// RSVD33 bitfiled (RO) Reset=0
#define USB3HC_USBLEGCTLSTS_RSVD33_MASK          0x1FE0
#define USB3HC_USBLEGCTLSTS_RSVD33_SHIFT         5 
#define USB3HC_USBLEGCTLSTS_RSVD33_BIT           0xFF
#define USB3HC_USBLEGCTLSTS_RSVD33_BITWIDTH      8
// SMI_ON_OS_E bitfiled (RW) Reset=0
#define USB3HC_USBLEGCTLSTS_SMI_ON_OS_E_MASK     0x2000
#define USB3HC_USBLEGCTLSTS_SMI_ON_OS_E_SHIFT    13 
#define USB3HC_USBLEGCTLSTS_SMI_ON_OS_E_BIT      0x1
#define USB3HC_USBLEGCTLSTS_SMI_ON_OS_E_BITWIDTH 1
// SMI_ON_PCI_E bitfiled (RW) Reset=0
#define USB3HC_USBLEGCTLSTS_SMI_ON_PCI_E_MASK    0x4000
#define USB3HC_USBLEGCTLSTS_SMI_ON_PCI_E_SHIFT   14 
#define USB3HC_USBLEGCTLSTS_SMI_ON_PCI_E_BIT     0x1
#define USB3HC_USBLEGCTLSTS_SMI_ON_PCI_E_BITWIDTH 1
// SMI_ON_BAR_E bitfiled (RW) Reset=0
#define USB3HC_USBLEGCTLSTS_SMI_ON_BAR_E_MASK    0x8000
#define USB3HC_USBLEGCTLSTS_SMI_ON_BAR_E_SHIFT   15 
#define USB3HC_USBLEGCTLSTS_SMI_ON_BAR_E_BIT     0x1
#define USB3HC_USBLEGCTLSTS_SMI_ON_BAR_E_BITWIDTH 1
// SMI_ON_EVENT bitfiled (RO) Reset=0
#define USB3HC_USBLEGCTLSTS_SMI_ON_EVENT_MASK    0x10000
#define USB3HC_USBLEGCTLSTS_SMI_ON_EVENT_SHIFT   16 
#define USB3HC_USBLEGCTLSTS_SMI_ON_EVENT_BIT     0x1
#define USB3HC_USBLEGCTLSTS_SMI_ON_EVENT_BITWIDTH 1
// RSVD34 bitfiled (RO) Reset=0
#define USB3HC_USBLEGCTLSTS_RSVD34_MASK          0xE0000
#define USB3HC_USBLEGCTLSTS_RSVD34_SHIFT         17 
#define USB3HC_USBLEGCTLSTS_RSVD34_BIT           0x7
#define USB3HC_USBLEGCTLSTS_RSVD34_BITWIDTH      3
// SMI_ON_HOST bitfiled (RO) Reset=0
#define USB3HC_USBLEGCTLSTS_SMI_ON_HOST_MASK     0x100000
#define USB3HC_USBLEGCTLSTS_SMI_ON_HOST_SHIFT    20 
#define USB3HC_USBLEGCTLSTS_SMI_ON_HOST_BIT      0x1
#define USB3HC_USBLEGCTLSTS_SMI_ON_HOST_BITWIDTH 1
// RSVD35 bitfiled (RO) Reset=0
#define USB3HC_USBLEGCTLSTS_RSVD35_MASK          0x1FE00000
#define USB3HC_USBLEGCTLSTS_RSVD35_SHIFT         21 
#define USB3HC_USBLEGCTLSTS_RSVD35_BIT           0xFF
#define USB3HC_USBLEGCTLSTS_RSVD35_BITWIDTH      8
// SMI_ON_OS bitfiled (RW) Reset=0
#define USB3HC_USBLEGCTLSTS_SMI_ON_OS_MASK       0x20000000
#define USB3HC_USBLEGCTLSTS_SMI_ON_OS_SHIFT      29 
#define USB3HC_USBLEGCTLSTS_SMI_ON_OS_BIT        0x1
#define USB3HC_USBLEGCTLSTS_SMI_ON_OS_BITWIDTH   1
// SMI_ON_PCI bitfiled (RW) Reset=0
#define USB3HC_USBLEGCTLSTS_SMI_ON_PCI_MASK      0x40000000
#define USB3HC_USBLEGCTLSTS_SMI_ON_PCI_SHIFT     30 
#define USB3HC_USBLEGCTLSTS_SMI_ON_PCI_BIT       0x1
#define USB3HC_USBLEGCTLSTS_SMI_ON_PCI_BITWIDTH  1
// SMI_ON_BAR bitfiled (RW) Reset=0
#define USB3HC_USBLEGCTLSTS_SMI_ON_BAR_MASK      0x80000000
#define USB3HC_USBLEGCTLSTS_SMI_ON_BAR_SHIFT     31 
#define USB3HC_USBLEGCTLSTS_SMI_ON_BAR_BIT       0x1
#define USB3HC_USBLEGCTLSTS_SMI_ON_BAR_BITWIDTH  1
// SUPTPRT2_DW0 Register
#define USB3HC_SUPTPRT2_DW0_OFS                  0x00000890
// CAPABILITY_ID bitfiled (RO) Reset=10
#define USB3HC_SUPTPRT2_DW0_CAPABILITY_ID_MASK   0xFF
#define USB3HC_SUPTPRT2_DW0_CAPABILITY_ID_SHIFT  0 
#define USB3HC_SUPTPRT2_DW0_CAPABILITY_ID_BIT    0xFF
#define USB3HC_SUPTPRT2_DW0_CAPABILITY_ID_BITWIDTH 8
// NEXT_CAPABILITY_POINTER bitfiled (RO) Reset=100
#define USB3HC_SUPTPRT2_DW0_NEXT_CAPABILITY_POINTER_MASK 0xFF00
#define USB3HC_SUPTPRT2_DW0_NEXT_CAPABILITY_POINTER_SHIFT 8 
#define USB3HC_SUPTPRT2_DW0_NEXT_CAPABILITY_POINTER_BIT 0xFF
#define USB3HC_SUPTPRT2_DW0_NEXT_CAPABILITY_POINTER_BITWIDTH 8
// MINOR_REVISION bitfiled (RO) Reset=0
#define USB3HC_SUPTPRT2_DW0_MINOR_REVISION_MASK  0xFF0000
#define USB3HC_SUPTPRT2_DW0_MINOR_REVISION_SHIFT 16 
#define USB3HC_SUPTPRT2_DW0_MINOR_REVISION_BIT   0xFF
#define USB3HC_SUPTPRT2_DW0_MINOR_REVISION_BITWIDTH 8
// MAJOR_REVISION bitfiled (RO) Reset=10
#define USB3HC_SUPTPRT2_DW0_MAJOR_REVISION_MASK  0xFF000000
#define USB3HC_SUPTPRT2_DW0_MAJOR_REVISION_SHIFT 24 
#define USB3HC_SUPTPRT2_DW0_MAJOR_REVISION_BIT   0xFF
#define USB3HC_SUPTPRT2_DW0_MAJOR_REVISION_BITWIDTH 8
// SUPTPRT2_DW1 Register
#define USB3HC_SUPTPRT2_DW1_OFS                  0x00000894
// NAME_STRING bitfiled (RO) Reset=100000010000100101001101010101
#define USB3HC_SUPTPRT2_DW1_NAME_STRING_MASK     0xFFFFFFFF
#define USB3HC_SUPTPRT2_DW1_NAME_STRING_SHIFT    0 
#define USB3HC_SUPTPRT2_DW1_NAME_STRING_BIT      0xFFFFFFFF
#define USB3HC_SUPTPRT2_DW1_NAME_STRING_BITWIDTH 32
// SUPTPRT2_DW2 Register
#define USB3HC_SUPTPRT2_DW2_OFS                  0x00000898
// COMPATIBLE_PORT_OFFSET bitfiled (RO) Reset=1
#define USB3HC_SUPTPRT2_DW2_COMPATIBLE_PORT_OFFSET_MASK 0xFF
#define USB3HC_SUPTPRT2_DW2_COMPATIBLE_PORT_OFFSET_SHIFT 0 
#define USB3HC_SUPTPRT2_DW2_COMPATIBLE_PORT_OFFSET_BIT 0xFF
#define USB3HC_SUPTPRT2_DW2_COMPATIBLE_PORT_OFFSET_BITWIDTH 8
// COMPATIBLE_PORT_COUNT bitfiled (RO) Reset=1
#define USB3HC_SUPTPRT2_DW2_COMPATIBLE_PORT_COUNT_MASK 0xFF00
#define USB3HC_SUPTPRT2_DW2_COMPATIBLE_PORT_COUNT_SHIFT 8 
#define USB3HC_SUPTPRT2_DW2_COMPATIBLE_PORT_COUNT_BIT 0xFF
#define USB3HC_SUPTPRT2_DW2_COMPATIBLE_PORT_COUNT_BITWIDTH 8
// Rsvd8 bitfiled (RO) Reset=0
#define USB3HC_SUPTPRT2_DW2_RSVD8_MASK           0x10000
#define USB3HC_SUPTPRT2_DW2_RSVD8_SHIFT          16 
#define USB3HC_SUPTPRT2_DW2_RSVD8_BIT            0x1
#define USB3HC_SUPTPRT2_DW2_RSVD8_BITWIDTH       1
// HSO bitfiled (RO) Reset=0
#define USB3HC_SUPTPRT2_DW2_HSO_MASK             0x20000
#define USB3HC_SUPTPRT2_DW2_HSO_SHIFT            17 
#define USB3HC_SUPTPRT2_DW2_HSO_BIT              0x1
#define USB3HC_SUPTPRT2_DW2_HSO_BITWIDTH         1
// IHI bitfiled (RO) Reset=0
#define USB3HC_SUPTPRT2_DW2_IHI_MASK             0x40000
#define USB3HC_SUPTPRT2_DW2_IHI_SHIFT            18 
#define USB3HC_SUPTPRT2_DW2_IHI_BIT              0x1
#define USB3HC_SUPTPRT2_DW2_IHI_BITWIDTH         1
// HLC bitfiled (RO) Reset=1
#define USB3HC_SUPTPRT2_DW2_HLC_MASK             0x80000
#define USB3HC_SUPTPRT2_DW2_HLC_SHIFT            19 
#define USB3HC_SUPTPRT2_DW2_HLC_BIT              0x1
#define USB3HC_SUPTPRT2_DW2_HLC_BITWIDTH         1
// Rsvd14 bitfiled (RO) Reset=0
#define USB3HC_SUPTPRT2_DW2_RSVD14_MASK          0xFF00000
#define USB3HC_SUPTPRT2_DW2_RSVD14_SHIFT         20 
#define USB3HC_SUPTPRT2_DW2_RSVD14_BIT           0xFF
#define USB3HC_SUPTPRT2_DW2_RSVD14_BITWIDTH      8
// PSIC bitfiled (RO) Reset=0
#define USB3HC_SUPTPRT2_DW2_PSIC_MASK            0xF0000000
#define USB3HC_SUPTPRT2_DW2_PSIC_SHIFT           28 
#define USB3HC_SUPTPRT2_DW2_PSIC_BIT             0xF
#define USB3HC_SUPTPRT2_DW2_PSIC_BITWIDTH        4
// SUPTPRT2_DW3 Register
#define USB3HC_SUPTPRT2_DW3_OFS                  0x0000089C
// PROTCL_SLT_TY bitfiled (RO) Reset=0
#define USB3HC_SUPTPRT2_DW3_PROTCL_SLT_TY_MASK   0x1F
#define USB3HC_SUPTPRT2_DW3_PROTCL_SLT_TY_SHIFT  0 
#define USB3HC_SUPTPRT2_DW3_PROTCL_SLT_TY_BIT    0x1F
#define USB3HC_SUPTPRT2_DW3_PROTCL_SLT_TY_BITWIDTH 5
// reserved bitfiled (RO) Reset=0
#define USB3HC_SUPTPRT2_DW3_RESERVED_MASK        0xFFFFFFE0
#define USB3HC_SUPTPRT2_DW3_RESERVED_SHIFT       5 
#define USB3HC_SUPTPRT2_DW3_RESERVED_BIT         0x7FFFFFF
#define USB3HC_SUPTPRT2_DW3_RESERVED_BITWIDTH    27
// SUPTPRT3_DW0 Register
#define USB3HC_SUPTPRT3_DW0_OFS                  0x000008A0
// CAPABILITY_ID bitfiled (RO) Reset=10
#define USB3HC_SUPTPRT3_DW0_CAPABILITY_ID_MASK   0xFF
#define USB3HC_SUPTPRT3_DW0_CAPABILITY_ID_SHIFT  0 
#define USB3HC_SUPTPRT3_DW0_CAPABILITY_ID_BIT    0xFF
#define USB3HC_SUPTPRT3_DW0_CAPABILITY_ID_BITWIDTH 8
// NEXT_CAPABILITY_POINTER bitfiled (RO) Reset=0
#define USB3HC_SUPTPRT3_DW0_NEXT_CAPABILITY_POINTER_MASK 0xFF00
#define USB3HC_SUPTPRT3_DW0_NEXT_CAPABILITY_POINTER_SHIFT 8 
#define USB3HC_SUPTPRT3_DW0_NEXT_CAPABILITY_POINTER_BIT 0xFF
#define USB3HC_SUPTPRT3_DW0_NEXT_CAPABILITY_POINTER_BITWIDTH 8
// MINOR_REVISION bitfiled (RO) Reset=0
#define USB3HC_SUPTPRT3_DW0_MINOR_REVISION_MASK  0xFF0000
#define USB3HC_SUPTPRT3_DW0_MINOR_REVISION_SHIFT 16 
#define USB3HC_SUPTPRT3_DW0_MINOR_REVISION_BIT   0xFF
#define USB3HC_SUPTPRT3_DW0_MINOR_REVISION_BITWIDTH 8
// MAJOR_REVISION bitfiled (RO) Reset=11
#define USB3HC_SUPTPRT3_DW0_MAJOR_REVISION_MASK  0xFF000000
#define USB3HC_SUPTPRT3_DW0_MAJOR_REVISION_SHIFT 24 
#define USB3HC_SUPTPRT3_DW0_MAJOR_REVISION_BIT   0xFF
#define USB3HC_SUPTPRT3_DW0_MAJOR_REVISION_BITWIDTH 8
// SUPTPRT3_DW1 Register
#define USB3HC_SUPTPRT3_DW1_OFS                  0x000008A4
// NAME_STRING bitfiled (RO) Reset=100000010000100101001101010101
#define USB3HC_SUPTPRT3_DW1_NAME_STRING_MASK     0xFFFFFFFF
#define USB3HC_SUPTPRT3_DW1_NAME_STRING_SHIFT    0 
#define USB3HC_SUPTPRT3_DW1_NAME_STRING_BIT      0xFFFFFFFF
#define USB3HC_SUPTPRT3_DW1_NAME_STRING_BITWIDTH 32
// SUPTPRT3_DW2 Register
#define USB3HC_SUPTPRT3_DW2_OFS                  0x000008A8
// COMPATIBLE_PORT_OFFSET bitfiled (RO) Reset=10
#define USB3HC_SUPTPRT3_DW2_COMPATIBLE_PORT_OFFSET_MASK 0xFF
#define USB3HC_SUPTPRT3_DW2_COMPATIBLE_PORT_OFFSET_SHIFT 0 
#define USB3HC_SUPTPRT3_DW2_COMPATIBLE_PORT_OFFSET_BIT 0xFF
#define USB3HC_SUPTPRT3_DW2_COMPATIBLE_PORT_OFFSET_BITWIDTH 8
// COMPATIBLE_PORT_COUNT bitfiled (RO) Reset=1
#define USB3HC_SUPTPRT3_DW2_COMPATIBLE_PORT_COUNT_MASK 0xFF00
#define USB3HC_SUPTPRT3_DW2_COMPATIBLE_PORT_COUNT_SHIFT 8 
#define USB3HC_SUPTPRT3_DW2_COMPATIBLE_PORT_COUNT_BIT 0xFF
#define USB3HC_SUPTPRT3_DW2_COMPATIBLE_PORT_COUNT_BITWIDTH 8
// RSVD34 bitfiled (RO) Reset=0
#define USB3HC_SUPTPRT3_DW2_RSVD34_MASK          0xFFF0000
#define USB3HC_SUPTPRT3_DW2_RSVD34_SHIFT         16 
#define USB3HC_SUPTPRT3_DW2_RSVD34_BIT           0xFFF
#define USB3HC_SUPTPRT3_DW2_RSVD34_BITWIDTH      12
// PSIC bitfiled (RO) Reset=0
#define USB3HC_SUPTPRT3_DW2_PSIC_MASK            0xF0000000
#define USB3HC_SUPTPRT3_DW2_PSIC_SHIFT           28 
#define USB3HC_SUPTPRT3_DW2_PSIC_BIT             0xF
#define USB3HC_SUPTPRT3_DW2_PSIC_BITWIDTH        4
// SUPTPRT3_DW3 Register
#define USB3HC_SUPTPRT3_DW3_OFS                  0x000008AC
// PROTCL_SLT_TY bitfiled (RO) Reset=0
#define USB3HC_SUPTPRT3_DW3_PROTCL_SLT_TY_MASK   0x1F
#define USB3HC_SUPTPRT3_DW3_PROTCL_SLT_TY_SHIFT  0 
#define USB3HC_SUPTPRT3_DW3_PROTCL_SLT_TY_BIT    0x1F
#define USB3HC_SUPTPRT3_DW3_PROTCL_SLT_TY_BITWIDTH 5
// Rsvd7 bitfiled (RO) Reset=0
#define USB3HC_SUPTPRT3_DW3_RSVD7_MASK           0xFFFFFFE0
#define USB3HC_SUPTPRT3_DW3_RSVD7_SHIFT          5 
#define USB3HC_SUPTPRT3_DW3_RSVD7_BIT            0x7FFFFFF
#define USB3HC_SUPTPRT3_DW3_RSVD7_BITWIDTH       27

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _USB3HC_REG_DEF_H */
