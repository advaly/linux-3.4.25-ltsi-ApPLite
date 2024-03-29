/*
 * arch/arm/mach-tz2000/include/mach/regs/usb2hco_reg_def.h
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

#ifndef _USB2HCO_REG_DEF_H
#define _USB2HCO_REG_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

// HcRevision Register
#define USB2HCO_HCREVISION_OFS                   0x00000000
// REV bitfiled (RO) Reset=10000
#define USB2HCO_HCREVISION_REV_MASK              0xFF
#define USB2HCO_HCREVISION_REV_SHIFT             0 
#define USB2HCO_HCREVISION_REV_BIT               0xFF
#define USB2HCO_HCREVISION_REV_BITWIDTH          8
// Legacy bitfiled (RO) Reset=0
#define USB2HCO_HCREVISION_LEGACY_MASK           0x100
#define USB2HCO_HCREVISION_LEGACY_SHIFT          8 
#define USB2HCO_HCREVISION_LEGACY_BIT            0x1
#define USB2HCO_HCREVISION_LEGACY_BITWIDTH       1
// Reserved bitfiled (RO) Reset=0
#define USB2HCO_HCREVISION_RESERVED_MASK         0xFFFFFE00
#define USB2HCO_HCREVISION_RESERVED_SHIFT        9 
#define USB2HCO_HCREVISION_RESERVED_BIT          0x7FFFFF
#define USB2HCO_HCREVISION_RESERVED_BITWIDTH     23
// HcControl Register
#define USB2HCO_HCCONTROL_OFS                    0x00000004
// CBSR bitfiled (RW) Reset=0
#define USB2HCO_HCCONTROL_CBSR_MASK              0x3
#define USB2HCO_HCCONTROL_CBSR_SHIFT             0 
#define USB2HCO_HCCONTROL_CBSR_BIT               0x3
#define USB2HCO_HCCONTROL_CBSR_BITWIDTH          2
// PLE bitfiled (RW) Reset=0
#define USB2HCO_HCCONTROL_PLE_MASK               0x4
#define USB2HCO_HCCONTROL_PLE_SHIFT              2 
#define USB2HCO_HCCONTROL_PLE_BIT                0x1
#define USB2HCO_HCCONTROL_PLE_BITWIDTH           1
// IE bitfiled (RW) Reset=0
#define USB2HCO_HCCONTROL_IE_MASK                0x8
#define USB2HCO_HCCONTROL_IE_SHIFT               3 
#define USB2HCO_HCCONTROL_IE_BIT                 0x1
#define USB2HCO_HCCONTROL_IE_BITWIDTH            1
// CLE bitfiled (RW) Reset=0
#define USB2HCO_HCCONTROL_CLE_MASK               0x10
#define USB2HCO_HCCONTROL_CLE_SHIFT              4 
#define USB2HCO_HCCONTROL_CLE_BIT                0x1
#define USB2HCO_HCCONTROL_CLE_BITWIDTH           1
// BLE bitfiled (RW) Reset=0
#define USB2HCO_HCCONTROL_BLE_MASK               0x20
#define USB2HCO_HCCONTROL_BLE_SHIFT              5 
#define USB2HCO_HCCONTROL_BLE_BIT                0x1
#define USB2HCO_HCCONTROL_BLE_BITWIDTH           1
// HCFS bitfiled (RW) Reset=0
#define USB2HCO_HCCONTROL_HCFS_MASK              0xC0
#define USB2HCO_HCCONTROL_HCFS_SHIFT             6 
#define USB2HCO_HCCONTROL_HCFS_BIT               0x3
#define USB2HCO_HCCONTROL_HCFS_BITWIDTH          2
// IR bitfiled (RW) Reset=0
#define USB2HCO_HCCONTROL_IR_MASK                0x100
#define USB2HCO_HCCONTROL_IR_SHIFT               8 
#define USB2HCO_HCCONTROL_IR_BIT                 0x1
#define USB2HCO_HCCONTROL_IR_BITWIDTH            1
// RWC bitfiled (RW) Reset=0
#define USB2HCO_HCCONTROL_RWC_MASK               0x200
#define USB2HCO_HCCONTROL_RWC_SHIFT              9 
#define USB2HCO_HCCONTROL_RWC_BIT                0x1
#define USB2HCO_HCCONTROL_RWC_BITWIDTH           1
// RWE bitfiled (RW) Reset=0
#define USB2HCO_HCCONTROL_RWE_MASK               0x400
#define USB2HCO_HCCONTROL_RWE_SHIFT              10 
#define USB2HCO_HCCONTROL_RWE_BIT                0x1
#define USB2HCO_HCCONTROL_RWE_BITWIDTH           1
// Reserved bitfiled (RO) Reset=0
#define USB2HCO_HCCONTROL_RESERVED_MASK          0xFFFFF800
#define USB2HCO_HCCONTROL_RESERVED_SHIFT         11 
#define USB2HCO_HCCONTROL_RESERVED_BIT           0x1FFFFF
#define USB2HCO_HCCONTROL_RESERVED_BITWIDTH      21
// HcCommandStatus Register
#define USB2HCO_HCCOMMANDSTATUS_OFS              0x00000008
// HCR bitfiled (RW) Reset=0
#define USB2HCO_HCCOMMANDSTATUS_HCR_MASK         0x1
#define USB2HCO_HCCOMMANDSTATUS_HCR_SHIFT        0 
#define USB2HCO_HCCOMMANDSTATUS_HCR_BIT          0x1
#define USB2HCO_HCCOMMANDSTATUS_HCR_BITWIDTH     1
// CLF bitfiled (RW) Reset=0
#define USB2HCO_HCCOMMANDSTATUS_CLF_MASK         0x2
#define USB2HCO_HCCOMMANDSTATUS_CLF_SHIFT        1 
#define USB2HCO_HCCOMMANDSTATUS_CLF_BIT          0x1
#define USB2HCO_HCCOMMANDSTATUS_CLF_BITWIDTH     1
// BLF bitfiled (RW) Reset=0
#define USB2HCO_HCCOMMANDSTATUS_BLF_MASK         0x4
#define USB2HCO_HCCOMMANDSTATUS_BLF_SHIFT        2 
#define USB2HCO_HCCOMMANDSTATUS_BLF_BIT          0x1
#define USB2HCO_HCCOMMANDSTATUS_BLF_BITWIDTH     1
// Reserved2 bitfiled (RO) Reset=0
#define USB2HCO_HCCOMMANDSTATUS_RESERVED2_MASK   0xFFF8
#define USB2HCO_HCCOMMANDSTATUS_RESERVED2_SHIFT  3 
#define USB2HCO_HCCOMMANDSTATUS_RESERVED2_BIT    0x1FFF
#define USB2HCO_HCCOMMANDSTATUS_RESERVED2_BITWIDTH 13
// SOC bitfiled (RO) Reset=0
#define USB2HCO_HCCOMMANDSTATUS_SOC_MASK         0x30000
#define USB2HCO_HCCOMMANDSTATUS_SOC_SHIFT        16 
#define USB2HCO_HCCOMMANDSTATUS_SOC_BIT          0x3
#define USB2HCO_HCCOMMANDSTATUS_SOC_BITWIDTH     2
// Reserved bitfiled (RO) Reset=0
#define USB2HCO_HCCOMMANDSTATUS_RESERVED_MASK    0xFFFC0000
#define USB2HCO_HCCOMMANDSTATUS_RESERVED_SHIFT   18 
#define USB2HCO_HCCOMMANDSTATUS_RESERVED_BIT     0x3FFF
#define USB2HCO_HCCOMMANDSTATUS_RESERVED_BITWIDTH 14
// HcInterruptStatus Register
#define USB2HCO_HCINTERRUPTSTATUS_OFS            0x0000000C
// SO bitfiled (RW) Reset=0
#define USB2HCO_HCINTERRUPTSTATUS_SO_MASK        0x1
#define USB2HCO_HCINTERRUPTSTATUS_SO_SHIFT       0 
#define USB2HCO_HCINTERRUPTSTATUS_SO_BIT         0x1
#define USB2HCO_HCINTERRUPTSTATUS_SO_BITWIDTH    1
// WDH bitfiled (RW) Reset=0
#define USB2HCO_HCINTERRUPTSTATUS_WDH_MASK       0x2
#define USB2HCO_HCINTERRUPTSTATUS_WDH_SHIFT      1 
#define USB2HCO_HCINTERRUPTSTATUS_WDH_BIT        0x1
#define USB2HCO_HCINTERRUPTSTATUS_WDH_BITWIDTH   1
// SF bitfiled (RW) Reset=0
#define USB2HCO_HCINTERRUPTSTATUS_SF_MASK        0x4
#define USB2HCO_HCINTERRUPTSTATUS_SF_SHIFT       2 
#define USB2HCO_HCINTERRUPTSTATUS_SF_BIT         0x1
#define USB2HCO_HCINTERRUPTSTATUS_SF_BITWIDTH    1
// RD bitfiled (RW) Reset=0
#define USB2HCO_HCINTERRUPTSTATUS_RD_MASK        0x8
#define USB2HCO_HCINTERRUPTSTATUS_RD_SHIFT       3 
#define USB2HCO_HCINTERRUPTSTATUS_RD_BIT         0x1
#define USB2HCO_HCINTERRUPTSTATUS_RD_BITWIDTH    1
// UE bitfiled (RW) Reset=0
#define USB2HCO_HCINTERRUPTSTATUS_UE_MASK        0x10
#define USB2HCO_HCINTERRUPTSTATUS_UE_SHIFT       4 
#define USB2HCO_HCINTERRUPTSTATUS_UE_BIT         0x1
#define USB2HCO_HCINTERRUPTSTATUS_UE_BITWIDTH    1
// FNO bitfiled (RW) Reset=0
#define USB2HCO_HCINTERRUPTSTATUS_FNO_MASK       0x20
#define USB2HCO_HCINTERRUPTSTATUS_FNO_SHIFT      5 
#define USB2HCO_HCINTERRUPTSTATUS_FNO_BIT        0x1
#define USB2HCO_HCINTERRUPTSTATUS_FNO_BITWIDTH   1
// RHSC bitfiled (RW) Reset=0
#define USB2HCO_HCINTERRUPTSTATUS_RHSC_MASK      0x40
#define USB2HCO_HCINTERRUPTSTATUS_RHSC_SHIFT     6 
#define USB2HCO_HCINTERRUPTSTATUS_RHSC_BIT       0x1
#define USB2HCO_HCINTERRUPTSTATUS_RHSC_BITWIDTH  1
// Reserved2 bitfiled (RO) Reset=0
#define USB2HCO_HCINTERRUPTSTATUS_RESERVED2_MASK 0x3FFFFF80
#define USB2HCO_HCINTERRUPTSTATUS_RESERVED2_SHIFT 7 
#define USB2HCO_HCINTERRUPTSTATUS_RESERVED2_BIT  0x7FFFFF
#define USB2HCO_HCINTERRUPTSTATUS_RESERVED2_BITWIDTH 23
// OC bitfiled (RW) Reset=0
#define USB2HCO_HCINTERRUPTSTATUS_OC_MASK        0x40000000
#define USB2HCO_HCINTERRUPTSTATUS_OC_SHIFT       30 
#define USB2HCO_HCINTERRUPTSTATUS_OC_BIT         0x1
#define USB2HCO_HCINTERRUPTSTATUS_OC_BITWIDTH    1
// Reserved bitfiled (RO) Reset=0
#define USB2HCO_HCINTERRUPTSTATUS_RESERVED_MASK  0x80000000
#define USB2HCO_HCINTERRUPTSTATUS_RESERVED_SHIFT 31 
#define USB2HCO_HCINTERRUPTSTATUS_RESERVED_BIT   0x1
#define USB2HCO_HCINTERRUPTSTATUS_RESERVED_BITWIDTH 1
// HcInterruptEnable Register
#define USB2HCO_HCINTERRUPTENABLE_OFS            0x00000010
// SO bitfiled (RW) Reset=0
#define USB2HCO_HCINTERRUPTENABLE_SO_MASK        0x1
#define USB2HCO_HCINTERRUPTENABLE_SO_SHIFT       0 
#define USB2HCO_HCINTERRUPTENABLE_SO_BIT         0x1
#define USB2HCO_HCINTERRUPTENABLE_SO_BITWIDTH    1
// WDH bitfiled (RW) Reset=0
#define USB2HCO_HCINTERRUPTENABLE_WDH_MASK       0x2
#define USB2HCO_HCINTERRUPTENABLE_WDH_SHIFT      1 
#define USB2HCO_HCINTERRUPTENABLE_WDH_BIT        0x1
#define USB2HCO_HCINTERRUPTENABLE_WDH_BITWIDTH   1
// SF bitfiled (RW) Reset=0
#define USB2HCO_HCINTERRUPTENABLE_SF_MASK        0x4
#define USB2HCO_HCINTERRUPTENABLE_SF_SHIFT       2 
#define USB2HCO_HCINTERRUPTENABLE_SF_BIT         0x1
#define USB2HCO_HCINTERRUPTENABLE_SF_BITWIDTH    1
// RD bitfiled (RW) Reset=0
#define USB2HCO_HCINTERRUPTENABLE_RD_MASK        0x8
#define USB2HCO_HCINTERRUPTENABLE_RD_SHIFT       3 
#define USB2HCO_HCINTERRUPTENABLE_RD_BIT         0x1
#define USB2HCO_HCINTERRUPTENABLE_RD_BITWIDTH    1
// UE bitfiled (RW) Reset=0
#define USB2HCO_HCINTERRUPTENABLE_UE_MASK        0x10
#define USB2HCO_HCINTERRUPTENABLE_UE_SHIFT       4 
#define USB2HCO_HCINTERRUPTENABLE_UE_BIT         0x1
#define USB2HCO_HCINTERRUPTENABLE_UE_BITWIDTH    1
// FNO bitfiled (RW) Reset=0
#define USB2HCO_HCINTERRUPTENABLE_FNO_MASK       0x20
#define USB2HCO_HCINTERRUPTENABLE_FNO_SHIFT      5 
#define USB2HCO_HCINTERRUPTENABLE_FNO_BIT        0x1
#define USB2HCO_HCINTERRUPTENABLE_FNO_BITWIDTH   1
// RHSC bitfiled (RW) Reset=0
#define USB2HCO_HCINTERRUPTENABLE_RHSC_MASK      0x40
#define USB2HCO_HCINTERRUPTENABLE_RHSC_SHIFT     6 
#define USB2HCO_HCINTERRUPTENABLE_RHSC_BIT       0x1
#define USB2HCO_HCINTERRUPTENABLE_RHSC_BITWIDTH  1
// Reserved bitfiled (RO) Reset=0
#define USB2HCO_HCINTERRUPTENABLE_RESERVED_MASK  0x3FFFFF80
#define USB2HCO_HCINTERRUPTENABLE_RESERVED_SHIFT 7 
#define USB2HCO_HCINTERRUPTENABLE_RESERVED_BIT   0x7FFFFF
#define USB2HCO_HCINTERRUPTENABLE_RESERVED_BITWIDTH 23
// OC bitfiled (RW) Reset=0
#define USB2HCO_HCINTERRUPTENABLE_OC_MASK        0x40000000
#define USB2HCO_HCINTERRUPTENABLE_OC_SHIFT       30 
#define USB2HCO_HCINTERRUPTENABLE_OC_BIT         0x1
#define USB2HCO_HCINTERRUPTENABLE_OC_BITWIDTH    1
// MIE bitfiled (RW) Reset=0
#define USB2HCO_HCINTERRUPTENABLE_MIE_MASK       0x80000000
#define USB2HCO_HCINTERRUPTENABLE_MIE_SHIFT      31 
#define USB2HCO_HCINTERRUPTENABLE_MIE_BIT        0x1
#define USB2HCO_HCINTERRUPTENABLE_MIE_BITWIDTH   1
// HcInterruptDisable Register
#define USB2HCO_HCINTERRUPTDISABLE_OFS           0x00000014
// SO bitfiled (RW) Reset=0
#define USB2HCO_HCINTERRUPTDISABLE_SO_MASK       0x1
#define USB2HCO_HCINTERRUPTDISABLE_SO_SHIFT      0 
#define USB2HCO_HCINTERRUPTDISABLE_SO_BIT        0x1
#define USB2HCO_HCINTERRUPTDISABLE_SO_BITWIDTH   1
// WDH bitfiled (RW) Reset=0
#define USB2HCO_HCINTERRUPTDISABLE_WDH_MASK      0x2
#define USB2HCO_HCINTERRUPTDISABLE_WDH_SHIFT     1 
#define USB2HCO_HCINTERRUPTDISABLE_WDH_BIT       0x1
#define USB2HCO_HCINTERRUPTDISABLE_WDH_BITWIDTH  1
// SF bitfiled (RW) Reset=0
#define USB2HCO_HCINTERRUPTDISABLE_SF_MASK       0x4
#define USB2HCO_HCINTERRUPTDISABLE_SF_SHIFT      2 
#define USB2HCO_HCINTERRUPTDISABLE_SF_BIT        0x1
#define USB2HCO_HCINTERRUPTDISABLE_SF_BITWIDTH   1
// RD bitfiled (RW) Reset=0
#define USB2HCO_HCINTERRUPTDISABLE_RD_MASK       0x8
#define USB2HCO_HCINTERRUPTDISABLE_RD_SHIFT      3 
#define USB2HCO_HCINTERRUPTDISABLE_RD_BIT        0x1
#define USB2HCO_HCINTERRUPTDISABLE_RD_BITWIDTH   1
// UE bitfiled (RW) Reset=0
#define USB2HCO_HCINTERRUPTDISABLE_UE_MASK       0x10
#define USB2HCO_HCINTERRUPTDISABLE_UE_SHIFT      4 
#define USB2HCO_HCINTERRUPTDISABLE_UE_BIT        0x1
#define USB2HCO_HCINTERRUPTDISABLE_UE_BITWIDTH   1
// FNO bitfiled (RW) Reset=0
#define USB2HCO_HCINTERRUPTDISABLE_FNO_MASK      0x20
#define USB2HCO_HCINTERRUPTDISABLE_FNO_SHIFT     5 
#define USB2HCO_HCINTERRUPTDISABLE_FNO_BIT       0x1
#define USB2HCO_HCINTERRUPTDISABLE_FNO_BITWIDTH  1
// RHSC bitfiled (RW) Reset=0
#define USB2HCO_HCINTERRUPTDISABLE_RHSC_MASK     0x40
#define USB2HCO_HCINTERRUPTDISABLE_RHSC_SHIFT    6 
#define USB2HCO_HCINTERRUPTDISABLE_RHSC_BIT      0x1
#define USB2HCO_HCINTERRUPTDISABLE_RHSC_BITWIDTH 1
// Reserved bitfiled (RO) Reset=0
#define USB2HCO_HCINTERRUPTDISABLE_RESERVED_MASK 0x3FFFFF80
#define USB2HCO_HCINTERRUPTDISABLE_RESERVED_SHIFT 7 
#define USB2HCO_HCINTERRUPTDISABLE_RESERVED_BIT  0x7FFFFF
#define USB2HCO_HCINTERRUPTDISABLE_RESERVED_BITWIDTH 23
// OC bitfiled (RW) Reset=0
#define USB2HCO_HCINTERRUPTDISABLE_OC_MASK       0x40000000
#define USB2HCO_HCINTERRUPTDISABLE_OC_SHIFT      30 
#define USB2HCO_HCINTERRUPTDISABLE_OC_BIT        0x1
#define USB2HCO_HCINTERRUPTDISABLE_OC_BITWIDTH   1
// MIE bitfiled (RW) Reset=0
#define USB2HCO_HCINTERRUPTDISABLE_MIE_MASK      0x80000000
#define USB2HCO_HCINTERRUPTDISABLE_MIE_SHIFT     31 
#define USB2HCO_HCINTERRUPTDISABLE_MIE_BIT       0x1
#define USB2HCO_HCINTERRUPTDISABLE_MIE_BITWIDTH  1
// HcHCCA Register
#define USB2HCO_HCHCCA_OFS                       0x00000018
// Reserved bitfiled (RO) Reset=0
#define USB2HCO_HCHCCA_RESERVED_MASK             0xFF
#define USB2HCO_HCHCCA_RESERVED_SHIFT            0 
#define USB2HCO_HCHCCA_RESERVED_BIT              0xFF
#define USB2HCO_HCHCCA_RESERVED_BITWIDTH         8
// HCCA bitfiled (RW) Reset=0
#define USB2HCO_HCHCCA_HCCA_MASK                 0xFFFFFF00
#define USB2HCO_HCHCCA_HCCA_SHIFT                8 
#define USB2HCO_HCHCCA_HCCA_BIT                  0xFFFFFF
#define USB2HCO_HCHCCA_HCCA_BITWIDTH             24
// HcPeriodCurrentED Register
#define USB2HCO_HCPERIODCURRENTED_OFS            0x0000001C
// Reserved bitfiled (RO) Reset=0
#define USB2HCO_HCPERIODCURRENTED_RESERVED_MASK  0xF
#define USB2HCO_HCPERIODCURRENTED_RESERVED_SHIFT 0 
#define USB2HCO_HCPERIODCURRENTED_RESERVED_BIT   0xF
#define USB2HCO_HCPERIODCURRENTED_RESERVED_BITWIDTH 4
// PCED bitfiled (RO) Reset=0
#define USB2HCO_HCPERIODCURRENTED_PCED_MASK      0xFFFFFFF0
#define USB2HCO_HCPERIODCURRENTED_PCED_SHIFT     4 
#define USB2HCO_HCPERIODCURRENTED_PCED_BIT       0xFFFFFFF
#define USB2HCO_HCPERIODCURRENTED_PCED_BITWIDTH  28
// HcControlHeadED Register
#define USB2HCO_HCCONTROLHEADED_OFS              0x00000020
// Reserved bitfiled (RO) Reset=0
#define USB2HCO_HCCONTROLHEADED_RESERVED_MASK    0xF
#define USB2HCO_HCCONTROLHEADED_RESERVED_SHIFT   0 
#define USB2HCO_HCCONTROLHEADED_RESERVED_BIT     0xF
#define USB2HCO_HCCONTROLHEADED_RESERVED_BITWIDTH 4
// CHED bitfiled (RW) Reset=0
#define USB2HCO_HCCONTROLHEADED_CHED_MASK        0xFFFFFFF0
#define USB2HCO_HCCONTROLHEADED_CHED_SHIFT       4 
#define USB2HCO_HCCONTROLHEADED_CHED_BIT         0xFFFFFFF
#define USB2HCO_HCCONTROLHEADED_CHED_BITWIDTH    28
// HcControlCurrentED Register
#define USB2HCO_HCCONTROLCURRENTED_OFS           0x00000024
// Reserved bitfiled (RO) Reset=0
#define USB2HCO_HCCONTROLCURRENTED_RESERVED_MASK 0xF
#define USB2HCO_HCCONTROLCURRENTED_RESERVED_SHIFT 0 
#define USB2HCO_HCCONTROLCURRENTED_RESERVED_BIT  0xF
#define USB2HCO_HCCONTROLCURRENTED_RESERVED_BITWIDTH 4
// CCED bitfiled (RW) Reset=0
#define USB2HCO_HCCONTROLCURRENTED_CCED_MASK     0xFFFFFFF0
#define USB2HCO_HCCONTROLCURRENTED_CCED_SHIFT    4 
#define USB2HCO_HCCONTROLCURRENTED_CCED_BIT      0xFFFFFFF
#define USB2HCO_HCCONTROLCURRENTED_CCED_BITWIDTH 28
// HcBulkHeadED Register
#define USB2HCO_HCBULKHEADED_OFS                 0x00000028
// Reserved bitfiled (RO) Reset=0
#define USB2HCO_HCBULKHEADED_RESERVED_MASK       0xF
#define USB2HCO_HCBULKHEADED_RESERVED_SHIFT      0 
#define USB2HCO_HCBULKHEADED_RESERVED_BIT        0xF
#define USB2HCO_HCBULKHEADED_RESERVED_BITWIDTH   4
// BHED bitfiled (RW) Reset=0
#define USB2HCO_HCBULKHEADED_BHED_MASK           0xFFFFFFF0
#define USB2HCO_HCBULKHEADED_BHED_SHIFT          4 
#define USB2HCO_HCBULKHEADED_BHED_BIT            0xFFFFFFF
#define USB2HCO_HCBULKHEADED_BHED_BITWIDTH       28
// HcBulkCurrentED Register
#define USB2HCO_HCBULKCURRENTED_OFS              0x0000002C
// Reserved bitfiled (RO) Reset=0
#define USB2HCO_HCBULKCURRENTED_RESERVED_MASK    0xF
#define USB2HCO_HCBULKCURRENTED_RESERVED_SHIFT   0 
#define USB2HCO_HCBULKCURRENTED_RESERVED_BIT     0xF
#define USB2HCO_HCBULKCURRENTED_RESERVED_BITWIDTH 4
// BCED bitfiled (RW) Reset=0
#define USB2HCO_HCBULKCURRENTED_BCED_MASK        0xFFFFFFF0
#define USB2HCO_HCBULKCURRENTED_BCED_SHIFT       4 
#define USB2HCO_HCBULKCURRENTED_BCED_BIT         0xFFFFFFF
#define USB2HCO_HCBULKCURRENTED_BCED_BITWIDTH    28
// HcDoneHead Register
#define USB2HCO_HCDONEHEAD_OFS                   0x00000030
// Reserved bitfiled (RO) Reset=0
#define USB2HCO_HCDONEHEAD_RESERVED_MASK         0xF
#define USB2HCO_HCDONEHEAD_RESERVED_SHIFT        0 
#define USB2HCO_HCDONEHEAD_RESERVED_BIT          0xF
#define USB2HCO_HCDONEHEAD_RESERVED_BITWIDTH     4
// DH bitfiled (RO) Reset=0
#define USB2HCO_HCDONEHEAD_DH_MASK               0xFFFFFFF0
#define USB2HCO_HCDONEHEAD_DH_SHIFT              4 
#define USB2HCO_HCDONEHEAD_DH_BIT                0xFFFFFFF
#define USB2HCO_HCDONEHEAD_DH_BITWIDTH           28
// HcFmInterval Register
#define USB2HCO_HCFMINTERVAL_OFS                 0x00000034
// FI bitfiled (RW) Reset=10111011011111
#define USB2HCO_HCFMINTERVAL_FI_MASK             0x3FFF
#define USB2HCO_HCFMINTERVAL_FI_SHIFT            0 
#define USB2HCO_HCFMINTERVAL_FI_BIT              0x3FFF
#define USB2HCO_HCFMINTERVAL_FI_BITWIDTH         14
// Reserved bitfiled (RO) Reset=0
#define USB2HCO_HCFMINTERVAL_RESERVED_MASK       0xC000
#define USB2HCO_HCFMINTERVAL_RESERVED_SHIFT      14 
#define USB2HCO_HCFMINTERVAL_RESERVED_BIT        0x3
#define USB2HCO_HCFMINTERVAL_RESERVED_BITWIDTH   2
// FSMPS bitfiled (RW) Reset=0
#define USB2HCO_HCFMINTERVAL_FSMPS_MASK          0x7FFF0000
#define USB2HCO_HCFMINTERVAL_FSMPS_SHIFT         16 
#define USB2HCO_HCFMINTERVAL_FSMPS_BIT           0x7FFF
#define USB2HCO_HCFMINTERVAL_FSMPS_BITWIDTH      15
// FIT bitfiled (RW) Reset=0
#define USB2HCO_HCFMINTERVAL_FIT_MASK            0x80000000
#define USB2HCO_HCFMINTERVAL_FIT_SHIFT           31 
#define USB2HCO_HCFMINTERVAL_FIT_BIT             0x1
#define USB2HCO_HCFMINTERVAL_FIT_BITWIDTH        1
// HcFmRemaining Register
#define USB2HCO_HCFMREMAINING_OFS                0x00000038
// FR bitfiled (RW) Reset=0
#define USB2HCO_HCFMREMAINING_FR_MASK            0x3FFF
#define USB2HCO_HCFMREMAINING_FR_SHIFT           0 
#define USB2HCO_HCFMREMAINING_FR_BIT             0x3FFF
#define USB2HCO_HCFMREMAINING_FR_BITWIDTH        14
// Reserved bitfiled (RO) Reset=0
#define USB2HCO_HCFMREMAINING_RESERVED_MASK      0x7FFFC000
#define USB2HCO_HCFMREMAINING_RESERVED_SHIFT     14 
#define USB2HCO_HCFMREMAINING_RESERVED_BIT       0x1FFFF
#define USB2HCO_HCFMREMAINING_RESERVED_BITWIDTH  17
// FRT bitfiled (RW) Reset=0
#define USB2HCO_HCFMREMAINING_FRT_MASK           0x80000000
#define USB2HCO_HCFMREMAINING_FRT_SHIFT          31 
#define USB2HCO_HCFMREMAINING_FRT_BIT            0x1
#define USB2HCO_HCFMREMAINING_FRT_BITWIDTH       1
// HcFmNumber Register
#define USB2HCO_HCFMNUMBER_OFS                   0x0000003C
// FN bitfiled (RO) Reset=0
#define USB2HCO_HCFMNUMBER_FN_MASK               0xFFFF
#define USB2HCO_HCFMNUMBER_FN_SHIFT              0 
#define USB2HCO_HCFMNUMBER_FN_BIT                0xFFFF
#define USB2HCO_HCFMNUMBER_FN_BITWIDTH           16
// Reserved bitfiled (RO) Reset=0
#define USB2HCO_HCFMNUMBER_RESERVED_MASK         0xFFFF0000
#define USB2HCO_HCFMNUMBER_RESERVED_SHIFT        16 
#define USB2HCO_HCFMNUMBER_RESERVED_BIT          0xFFFF
#define USB2HCO_HCFMNUMBER_RESERVED_BITWIDTH     16
// HcPeriodicStart Register
#define USB2HCO_HCPERIODICSTART_OFS              0x00000040
// PS bitfiled (RW) Reset=0
#define USB2HCO_HCPERIODICSTART_PS_MASK          0x3FFF
#define USB2HCO_HCPERIODICSTART_PS_SHIFT         0 
#define USB2HCO_HCPERIODICSTART_PS_BIT           0x3FFF
#define USB2HCO_HCPERIODICSTART_PS_BITWIDTH      14
// Reserved bitfiled (RO) Reset=0
#define USB2HCO_HCPERIODICSTART_RESERVED_MASK    0xFFFFC000
#define USB2HCO_HCPERIODICSTART_RESERVED_SHIFT   14 
#define USB2HCO_HCPERIODICSTART_RESERVED_BIT     0x3FFFF
#define USB2HCO_HCPERIODICSTART_RESERVED_BITWIDTH 18
// HcLSThreshold Register
#define USB2HCO_HCLSTHRESHOLD_OFS                0x00000044
// LST bitfiled (RW) Reset=11000101000
#define USB2HCO_HCLSTHRESHOLD_LST_MASK           0xFFF
#define USB2HCO_HCLSTHRESHOLD_LST_SHIFT          0 
#define USB2HCO_HCLSTHRESHOLD_LST_BIT            0xFFF
#define USB2HCO_HCLSTHRESHOLD_LST_BITWIDTH       12
// Reserved bitfiled (RO) Reset=0
#define USB2HCO_HCLSTHRESHOLD_RESERVED_MASK      0xFFFFF000
#define USB2HCO_HCLSTHRESHOLD_RESERVED_SHIFT     12 
#define USB2HCO_HCLSTHRESHOLD_RESERVED_BIT       0xFFFFF
#define USB2HCO_HCLSTHRESHOLD_RESERVED_BITWIDTH  20
// HcRhDescriptorA Register
#define USB2HCO_HCRHDESCRIPTORA_OFS              0x00000048
// NDP bitfiled (RO) Reset=1
#define USB2HCO_HCRHDESCRIPTORA_NDP_MASK         0xFF
#define USB2HCO_HCRHDESCRIPTORA_NDP_SHIFT        0 
#define USB2HCO_HCRHDESCRIPTORA_NDP_BIT          0xFF
#define USB2HCO_HCRHDESCRIPTORA_NDP_BITWIDTH     8
// PSM bitfiled (RW) Reset=0
#define USB2HCO_HCRHDESCRIPTORA_PSM_MASK         0x100
#define USB2HCO_HCRHDESCRIPTORA_PSM_SHIFT        8 
#define USB2HCO_HCRHDESCRIPTORA_PSM_BIT          0x1
#define USB2HCO_HCRHDESCRIPTORA_PSM_BITWIDTH     1
// NPS bitfiled (RW) Reset=1
#define USB2HCO_HCRHDESCRIPTORA_NPS_MASK         0x200
#define USB2HCO_HCRHDESCRIPTORA_NPS_SHIFT        9 
#define USB2HCO_HCRHDESCRIPTORA_NPS_BIT          0x1
#define USB2HCO_HCRHDESCRIPTORA_NPS_BITWIDTH     1
// Reserved2 bitfiled (RO) Reset=0
#define USB2HCO_HCRHDESCRIPTORA_RESERVED2_MASK   0x400
#define USB2HCO_HCRHDESCRIPTORA_RESERVED2_SHIFT  10 
#define USB2HCO_HCRHDESCRIPTORA_RESERVED2_BIT    0x1
#define USB2HCO_HCRHDESCRIPTORA_RESERVED2_BITWIDTH 1
// OCPM bitfiled (RW) Reset=0
#define USB2HCO_HCRHDESCRIPTORA_OCPM_MASK        0x800
#define USB2HCO_HCRHDESCRIPTORA_OCPM_SHIFT       11 
#define USB2HCO_HCRHDESCRIPTORA_OCPM_BIT         0x1
#define USB2HCO_HCRHDESCRIPTORA_OCPM_BITWIDTH    1
// NOCP bitfiled (RW) Reset=1
#define USB2HCO_HCRHDESCRIPTORA_NOCP_MASK        0x1000
#define USB2HCO_HCRHDESCRIPTORA_NOCP_SHIFT       12 
#define USB2HCO_HCRHDESCRIPTORA_NOCP_BIT         0x1
#define USB2HCO_HCRHDESCRIPTORA_NOCP_BITWIDTH    1
// Reserved bitfiled (RO) Reset=0
#define USB2HCO_HCRHDESCRIPTORA_RESERVED_MASK    0xFFE000
#define USB2HCO_HCRHDESCRIPTORA_RESERVED_SHIFT   13 
#define USB2HCO_HCRHDESCRIPTORA_RESERVED_BIT     0x7FF
#define USB2HCO_HCRHDESCRIPTORA_RESERVED_BITWIDTH 11
// POTPGT bitfiled (RW) Reset=10
#define USB2HCO_HCRHDESCRIPTORA_POTPGT_MASK      0xFF000000
#define USB2HCO_HCRHDESCRIPTORA_POTPGT_SHIFT     24 
#define USB2HCO_HCRHDESCRIPTORA_POTPGT_BIT       0xFF
#define USB2HCO_HCRHDESCRIPTORA_POTPGT_BITWIDTH  8
// HcRhDescriptorB Register
#define USB2HCO_HCRHDESCRIPTORB_OFS              0x0000004C
// Reserved3 bitfiled (RO) Reset=0
#define USB2HCO_HCRHDESCRIPTORB_RESERVED3_MASK   0x1
#define USB2HCO_HCRHDESCRIPTORB_RESERVED3_SHIFT  0 
#define USB2HCO_HCRHDESCRIPTORB_RESERVED3_BIT    0x1
#define USB2HCO_HCRHDESCRIPTORB_RESERVED3_BITWIDTH 1
// DR bitfiled (RW) Reset=0
#define USB2HCO_HCRHDESCRIPTORB_DR_MASK          0x2
#define USB2HCO_HCRHDESCRIPTORB_DR_SHIFT         1 
#define USB2HCO_HCRHDESCRIPTORB_DR_BIT           0x1
#define USB2HCO_HCRHDESCRIPTORB_DR_BITWIDTH      1
// Reserved2 bitfiled (RO) Reset=0
#define USB2HCO_HCRHDESCRIPTORB_RESERVED2_MASK   0x1FFFC
#define USB2HCO_HCRHDESCRIPTORB_RESERVED2_SHIFT  2 
#define USB2HCO_HCRHDESCRIPTORB_RESERVED2_BIT    0x7FFF
#define USB2HCO_HCRHDESCRIPTORB_RESERVED2_BITWIDTH 15
// PPCM bitfiled (RW) Reset=0
#define USB2HCO_HCRHDESCRIPTORB_PPCM_MASK        0x20000
#define USB2HCO_HCRHDESCRIPTORB_PPCM_SHIFT       17 
#define USB2HCO_HCRHDESCRIPTORB_PPCM_BIT         0x1
#define USB2HCO_HCRHDESCRIPTORB_PPCM_BITWIDTH    1
// Reserved bitfiled (RO) Reset=0
#define USB2HCO_HCRHDESCRIPTORB_RESERVED_MASK    0xFFFC0000
#define USB2HCO_HCRHDESCRIPTORB_RESERVED_SHIFT   18 
#define USB2HCO_HCRHDESCRIPTORB_RESERVED_BIT     0x3FFF
#define USB2HCO_HCRHDESCRIPTORB_RESERVED_BITWIDTH 14
// HcRhStatus Register
#define USB2HCO_HCRHSTATUS_OFS                   0x00000050
// Reserved4 bitfiled (RO) Reset=0
#define USB2HCO_HCRHSTATUS_RESERVED4_MASK        0x1
#define USB2HCO_HCRHSTATUS_RESERVED4_SHIFT       0 
#define USB2HCO_HCRHSTATUS_RESERVED4_BIT         0x1
#define USB2HCO_HCRHSTATUS_RESERVED4_BITWIDTH    1
// OCI bitfiled (RW) Reset=0
#define USB2HCO_HCRHSTATUS_OCI_MASK              0x2
#define USB2HCO_HCRHSTATUS_OCI_SHIFT             1 
#define USB2HCO_HCRHSTATUS_OCI_BIT               0x1
#define USB2HCO_HCRHSTATUS_OCI_BITWIDTH          1
// Reserved3 bitfiled (RO) Reset=0
#define USB2HCO_HCRHSTATUS_RESERVED3_MASK        0x7FFC
#define USB2HCO_HCRHSTATUS_RESERVED3_SHIFT       2 
#define USB2HCO_HCRHSTATUS_RESERVED3_BIT         0x1FFF
#define USB2HCO_HCRHSTATUS_RESERVED3_BITWIDTH    13
// DRWE bitfiled (RW) Reset=0
#define USB2HCO_HCRHSTATUS_DRWE_MASK             0x8000
#define USB2HCO_HCRHSTATUS_DRWE_SHIFT            15 
#define USB2HCO_HCRHSTATUS_DRWE_BIT              0x1
#define USB2HCO_HCRHSTATUS_DRWE_BITWIDTH         1
// Reserved2 bitfiled (RO) Reset=0
#define USB2HCO_HCRHSTATUS_RESERVED2_MASK        0x10000
#define USB2HCO_HCRHSTATUS_RESERVED2_SHIFT       16 
#define USB2HCO_HCRHSTATUS_RESERVED2_BIT         0x1
#define USB2HCO_HCRHSTATUS_RESERVED2_BITWIDTH    1
// OCIC bitfiled (RW) Reset=0
#define USB2HCO_HCRHSTATUS_OCIC_MASK             0x20000
#define USB2HCO_HCRHSTATUS_OCIC_SHIFT            17 
#define USB2HCO_HCRHSTATUS_OCIC_BIT              0x1
#define USB2HCO_HCRHSTATUS_OCIC_BITWIDTH         1
// Reserved bitfiled (RO) Reset=0
#define USB2HCO_HCRHSTATUS_RESERVED_MASK         0xFFFC0000
#define USB2HCO_HCRHSTATUS_RESERVED_SHIFT        18 
#define USB2HCO_HCRHSTATUS_RESERVED_BIT          0x3FFF
#define USB2HCO_HCRHSTATUS_RESERVED_BITWIDTH     14
// HcRhPortStatus_0 Register
#define USB2HCO_HCRHPORTSTATUS_0_OFS             0x00000054
// CCS bitfiled (RW) Reset=0
#define USB2HCO_HCRHPORTSTATUS_0_CCS_MASK        0x1
#define USB2HCO_HCRHPORTSTATUS_0_CCS_SHIFT       0 
#define USB2HCO_HCRHPORTSTATUS_0_CCS_BIT         0x1
#define USB2HCO_HCRHPORTSTATUS_0_CCS_BITWIDTH    1
// PES bitfiled (RW) Reset=0
#define USB2HCO_HCRHPORTSTATUS_0_PES_MASK        0x2
#define USB2HCO_HCRHPORTSTATUS_0_PES_SHIFT       1 
#define USB2HCO_HCRHPORTSTATUS_0_PES_BIT         0x1
#define USB2HCO_HCRHPORTSTATUS_0_PES_BITWIDTH    1
// PSS bitfiled (RW) Reset=0
#define USB2HCO_HCRHPORTSTATUS_0_PSS_MASK        0x4
#define USB2HCO_HCRHPORTSTATUS_0_PSS_SHIFT       2 
#define USB2HCO_HCRHPORTSTATUS_0_PSS_BIT         0x1
#define USB2HCO_HCRHPORTSTATUS_0_PSS_BITWIDTH    1
// POCI bitfiled (RW) Reset=0
#define USB2HCO_HCRHPORTSTATUS_0_POCI_MASK       0x8
#define USB2HCO_HCRHPORTSTATUS_0_POCI_SHIFT      3 
#define USB2HCO_HCRHPORTSTATUS_0_POCI_BIT        0x1
#define USB2HCO_HCRHPORTSTATUS_0_POCI_BITWIDTH   1
// PRS bitfiled (RW) Reset=0
#define USB2HCO_HCRHPORTSTATUS_0_PRS_MASK        0x10
#define USB2HCO_HCRHPORTSTATUS_0_PRS_SHIFT       4 
#define USB2HCO_HCRHPORTSTATUS_0_PRS_BIT         0x1
#define USB2HCO_HCRHPORTSTATUS_0_PRS_BITWIDTH    1
// Reserved3 bitfiled (RO) Reset=0
#define USB2HCO_HCRHPORTSTATUS_0_RESERVED3_MASK  0xE0
#define USB2HCO_HCRHPORTSTATUS_0_RESERVED3_SHIFT 5 
#define USB2HCO_HCRHPORTSTATUS_0_RESERVED3_BIT   0x7
#define USB2HCO_HCRHPORTSTATUS_0_RESERVED3_BITWIDTH 3
// PPS bitfiled (RW) Reset=1
#define USB2HCO_HCRHPORTSTATUS_0_PPS_MASK        0x100
#define USB2HCO_HCRHPORTSTATUS_0_PPS_SHIFT       8 
#define USB2HCO_HCRHPORTSTATUS_0_PPS_BIT         0x1
#define USB2HCO_HCRHPORTSTATUS_0_PPS_BITWIDTH    1
// LSDA bitfiled (RW) Reset=0
#define USB2HCO_HCRHPORTSTATUS_0_LSDA_MASK       0x200
#define USB2HCO_HCRHPORTSTATUS_0_LSDA_SHIFT      9 
#define USB2HCO_HCRHPORTSTATUS_0_LSDA_BIT        0x1
#define USB2HCO_HCRHPORTSTATUS_0_LSDA_BITWIDTH   1
// Reserved2 bitfiled (RO) Reset=0
#define USB2HCO_HCRHPORTSTATUS_0_RESERVED2_MASK  0xFC00
#define USB2HCO_HCRHPORTSTATUS_0_RESERVED2_SHIFT 10 
#define USB2HCO_HCRHPORTSTATUS_0_RESERVED2_BIT   0x3F
#define USB2HCO_HCRHPORTSTATUS_0_RESERVED2_BITWIDTH 6
// CSC bitfiled (RW) Reset=0
#define USB2HCO_HCRHPORTSTATUS_0_CSC_MASK        0x10000
#define USB2HCO_HCRHPORTSTATUS_0_CSC_SHIFT       16 
#define USB2HCO_HCRHPORTSTATUS_0_CSC_BIT         0x1
#define USB2HCO_HCRHPORTSTATUS_0_CSC_BITWIDTH    1
// PESC bitfiled (RW) Reset=0
#define USB2HCO_HCRHPORTSTATUS_0_PESC_MASK       0x20000
#define USB2HCO_HCRHPORTSTATUS_0_PESC_SHIFT      17 
#define USB2HCO_HCRHPORTSTATUS_0_PESC_BIT        0x1
#define USB2HCO_HCRHPORTSTATUS_0_PESC_BITWIDTH   1
// PSSC bitfiled (RW) Reset=0
#define USB2HCO_HCRHPORTSTATUS_0_PSSC_MASK       0x40000
#define USB2HCO_HCRHPORTSTATUS_0_PSSC_SHIFT      18 
#define USB2HCO_HCRHPORTSTATUS_0_PSSC_BIT        0x1
#define USB2HCO_HCRHPORTSTATUS_0_PSSC_BITWIDTH   1
// OCIC bitfiled (RW) Reset=0
#define USB2HCO_HCRHPORTSTATUS_0_OCIC_MASK       0x80000
#define USB2HCO_HCRHPORTSTATUS_0_OCIC_SHIFT      19 
#define USB2HCO_HCRHPORTSTATUS_0_OCIC_BIT        0x1
#define USB2HCO_HCRHPORTSTATUS_0_OCIC_BITWIDTH   1
// PRSC bitfiled (RW) Reset=0
#define USB2HCO_HCRHPORTSTATUS_0_PRSC_MASK       0x100000
#define USB2HCO_HCRHPORTSTATUS_0_PRSC_SHIFT      20 
#define USB2HCO_HCRHPORTSTATUS_0_PRSC_BIT        0x1
#define USB2HCO_HCRHPORTSTATUS_0_PRSC_BITWIDTH   1
// Reserved bitfiled (RO) Reset=0
#define USB2HCO_HCRHPORTSTATUS_0_RESERVED_MASK   0xFFE00000
#define USB2HCO_HCRHPORTSTATUS_0_RESERVED_SHIFT  21 
#define USB2HCO_HCRHPORTSTATUS_0_RESERVED_BIT    0x7FF
#define USB2HCO_HCRHPORTSTATUS_0_RESERVED_BITWIDTH 11

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _USB2HCO_REG_DEF_H */
