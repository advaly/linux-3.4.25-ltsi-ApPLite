/*
 * arch/arm/mach-tz3000/include/mach/regs/usb2dc_reg_def.h
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

#ifndef _USB2DC_REG_DEF_H
#define _USB2DC_REG_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

// GOTGCTL Register
#define USB2DC_GOTGCTL_OFS                       0x00000000
// SesReqScs bitfiled (RO) Reset=0
#define USB2DC_GOTGCTL_SESREQSCS_MASK            0x1
#define USB2DC_GOTGCTL_SESREQSCS_SHIFT           0 
#define USB2DC_GOTGCTL_SESREQSCS_BIT             0x1
#define USB2DC_GOTGCTL_SESREQSCS_BITWIDTH        1
// SesReq bitfiled (RW) Reset=0
#define USB2DC_GOTGCTL_SESREQ_MASK               0x2
#define USB2DC_GOTGCTL_SESREQ_SHIFT              1 
#define USB2DC_GOTGCTL_SESREQ_BIT                0x1
#define USB2DC_GOTGCTL_SESREQ_BITWIDTH           1
// Reserved5 bitfiled (RO) Reset=0
#define USB2DC_GOTGCTL_RESERVED5_MASK            0x3C
#define USB2DC_GOTGCTL_RESERVED5_SHIFT           2 
#define USB2DC_GOTGCTL_RESERVED5_BIT             0xF
#define USB2DC_GOTGCTL_RESERVED5_BITWIDTH        4
// BvalidOvEn bitfiled (RW) Reset=0
#define USB2DC_GOTGCTL_BVALIDOVEN_MASK           0x40
#define USB2DC_GOTGCTL_BVALIDOVEN_SHIFT          6 
#define USB2DC_GOTGCTL_BVALIDOVEN_BIT            0x1
#define USB2DC_GOTGCTL_BVALIDOVEN_BITWIDTH       1
// BvalidOvVal bitfiled (RW) Reset=0
#define USB2DC_GOTGCTL_BVALIDOVVAL_MASK          0x80
#define USB2DC_GOTGCTL_BVALIDOVVAL_SHIFT         7 
#define USB2DC_GOTGCTL_BVALIDOVVAL_BIT           0x1
#define USB2DC_GOTGCTL_BVALIDOVVAL_BITWIDTH      1
// HstNegScs bitfiled (RO) Reset=0
#define USB2DC_GOTGCTL_HSTNEGSCS_MASK            0x100
#define USB2DC_GOTGCTL_HSTNEGSCS_SHIFT           8 
#define USB2DC_GOTGCTL_HSTNEGSCS_BIT             0x1
#define USB2DC_GOTGCTL_HSTNEGSCS_BITWIDTH        1
// HNPReq bitfiled (RW) Reset=0
#define USB2DC_GOTGCTL_HNPREQ_MASK               0x200
#define USB2DC_GOTGCTL_HNPREQ_SHIFT              9 
#define USB2DC_GOTGCTL_HNPREQ_BIT                0x1
#define USB2DC_GOTGCTL_HNPREQ_BITWIDTH           1
// Reserved4 bitfiled (RO) Reset=0
#define USB2DC_GOTGCTL_RESERVED4_MASK            0x400
#define USB2DC_GOTGCTL_RESERVED4_SHIFT           10 
#define USB2DC_GOTGCTL_RESERVED4_BIT             0x1
#define USB2DC_GOTGCTL_RESERVED4_BITWIDTH        1
// DevHNPEn bitfiled (RW) Reset=0
#define USB2DC_GOTGCTL_DEVHNPEN_MASK             0x800
#define USB2DC_GOTGCTL_DEVHNPEN_SHIFT            11 
#define USB2DC_GOTGCTL_DEVHNPEN_BIT              0x1
#define USB2DC_GOTGCTL_DEVHNPEN_BITWIDTH         1
// Reserved3 bitfiled (RO) Reset=0
#define USB2DC_GOTGCTL_RESERVED3_MASK            0xF000
#define USB2DC_GOTGCTL_RESERVED3_SHIFT           12 
#define USB2DC_GOTGCTL_RESERVED3_BIT             0xF
#define USB2DC_GOTGCTL_RESERVED3_BITWIDTH        4
// ConIDSts bitfiled (RW) Reset=1
#define USB2DC_GOTGCTL_CONIDSTS_MASK             0x10000
#define USB2DC_GOTGCTL_CONIDSTS_SHIFT            16 
#define USB2DC_GOTGCTL_CONIDSTS_BIT              0x1
#define USB2DC_GOTGCTL_CONIDSTS_BITWIDTH         1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_GOTGCTL_RESERVED2_MASK            0x60000
#define USB2DC_GOTGCTL_RESERVED2_SHIFT           17 
#define USB2DC_GOTGCTL_RESERVED2_BIT             0x3
#define USB2DC_GOTGCTL_RESERVED2_BITWIDTH        2
// BSesVld bitfiled (RO) Reset=1
#define USB2DC_GOTGCTL_BSESVLD_MASK              0x80000
#define USB2DC_GOTGCTL_BSESVLD_SHIFT             19 
#define USB2DC_GOTGCTL_BSESVLD_BIT               0x1
#define USB2DC_GOTGCTL_BSESVLD_BITWIDTH          1
// OTGVer bitfiled (RW) Reset=0
#define USB2DC_GOTGCTL_OTGVER_MASK               0x100000
#define USB2DC_GOTGCTL_OTGVER_SHIFT              20 
#define USB2DC_GOTGCTL_OTGVER_BIT                0x1
#define USB2DC_GOTGCTL_OTGVER_BITWIDTH           1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_GOTGCTL_RESERVED_MASK             0xFFE00000
#define USB2DC_GOTGCTL_RESERVED_SHIFT            21 
#define USB2DC_GOTGCTL_RESERVED_BIT              0x7FF
#define USB2DC_GOTGCTL_RESERVED_BITWIDTH         11
// GOTGINT Register
#define USB2DC_GOTGINT_OFS                       0x00000004
// Reserved4 bitfiled (RO) Reset=0
#define USB2DC_GOTGINT_RESERVED4_MASK            0x3
#define USB2DC_GOTGINT_RESERVED4_SHIFT           0 
#define USB2DC_GOTGINT_RESERVED4_BIT             0x3
#define USB2DC_GOTGINT_RESERVED4_BITWIDTH        2
// SesEndDet bitfiled (RO) Reset=0
#define USB2DC_GOTGINT_SESENDDET_MASK            0x4
#define USB2DC_GOTGINT_SESENDDET_SHIFT           2 
#define USB2DC_GOTGINT_SESENDDET_BIT             0x1
#define USB2DC_GOTGINT_SESENDDET_BITWIDTH        1
// Reserved3 bitfiled (RO) Reset=0
#define USB2DC_GOTGINT_RESERVED3_MASK            0xF8
#define USB2DC_GOTGINT_RESERVED3_SHIFT           3 
#define USB2DC_GOTGINT_RESERVED3_BIT             0x1F
#define USB2DC_GOTGINT_RESERVED3_BITWIDTH        5
// SesReqSucStsChng bitfiled (RO) Reset=0
#define USB2DC_GOTGINT_SESREQSUCSTSCHNG_MASK     0x100
#define USB2DC_GOTGINT_SESREQSUCSTSCHNG_SHIFT    8 
#define USB2DC_GOTGINT_SESREQSUCSTSCHNG_BIT      0x1
#define USB2DC_GOTGINT_SESREQSUCSTSCHNG_BITWIDTH 1
// HstNegSucStsChng bitfiled (RO) Reset=0
#define USB2DC_GOTGINT_HSTNEGSUCSTSCHNG_MASK     0x200
#define USB2DC_GOTGINT_HSTNEGSUCSTSCHNG_SHIFT    9 
#define USB2DC_GOTGINT_HSTNEGSUCSTSCHNG_BIT      0x1
#define USB2DC_GOTGINT_HSTNEGSUCSTSCHNG_BITWIDTH 1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_GOTGINT_RESERVED2_MASK            0x1FC00
#define USB2DC_GOTGINT_RESERVED2_SHIFT           10 
#define USB2DC_GOTGINT_RESERVED2_BIT             0x7F
#define USB2DC_GOTGINT_RESERVED2_BITWIDTH        7
// HstNegDet bitfiled (RO) Reset=0
#define USB2DC_GOTGINT_HSTNEGDET_MASK            0x20000
#define USB2DC_GOTGINT_HSTNEGDET_SHIFT           17 
#define USB2DC_GOTGINT_HSTNEGDET_BIT             0x1
#define USB2DC_GOTGINT_HSTNEGDET_BITWIDTH        1
// ADevTOUTChg bitfiled (RO) Reset=0
#define USB2DC_GOTGINT_ADEVTOUTCHG_MASK          0x40000
#define USB2DC_GOTGINT_ADEVTOUTCHG_SHIFT         18 
#define USB2DC_GOTGINT_ADEVTOUTCHG_BIT           0x1
#define USB2DC_GOTGINT_ADEVTOUTCHG_BITWIDTH      1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_GOTGINT_RESERVED_MASK             0xFFF80000
#define USB2DC_GOTGINT_RESERVED_SHIFT            19 
#define USB2DC_GOTGINT_RESERVED_BIT              0x1FFF
#define USB2DC_GOTGINT_RESERVED_BITWIDTH         13
// GAHBCFG Register
#define USB2DC_GAHBCFG_OFS                       0x00000008
// GlblIntrMsk bitfiled (RW) Reset=0
#define USB2DC_GAHBCFG_GLBLINTRMSK_MASK          0x1
#define USB2DC_GAHBCFG_GLBLINTRMSK_SHIFT         0 
#define USB2DC_GAHBCFG_GLBLINTRMSK_BIT           0x1
#define USB2DC_GAHBCFG_GLBLINTRMSK_BITWIDTH      1
// HBstLen bitfiled (RW) Reset=0
#define USB2DC_GAHBCFG_HBSTLEN_MASK              0x1E
#define USB2DC_GAHBCFG_HBSTLEN_SHIFT             1 
#define USB2DC_GAHBCFG_HBSTLEN_BIT               0xF
#define USB2DC_GAHBCFG_HBSTLEN_BITWIDTH          4
// DMAEn bitfiled (RW) Reset=0
#define USB2DC_GAHBCFG_DMAEN_MASK                0x20
#define USB2DC_GAHBCFG_DMAEN_SHIFT               5 
#define USB2DC_GAHBCFG_DMAEN_BIT                 0x1
#define USB2DC_GAHBCFG_DMAEN_BITWIDTH            1
// Reserved3 bitfiled (RO) Reset=0
#define USB2DC_GAHBCFG_RESERVED3_MASK            0x40
#define USB2DC_GAHBCFG_RESERVED3_SHIFT           6 
#define USB2DC_GAHBCFG_RESERVED3_BIT             0x1
#define USB2DC_GAHBCFG_RESERVED3_BITWIDTH        1
// NPTxFEmpLvl bitfiled (RW) Reset=0
#define USB2DC_GAHBCFG_NPTXFEMPLVL_MASK          0x80
#define USB2DC_GAHBCFG_NPTXFEMPLVL_SHIFT         7 
#define USB2DC_GAHBCFG_NPTXFEMPLVL_BIT           0x1
#define USB2DC_GAHBCFG_NPTXFEMPLVL_BITWIDTH      1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_GAHBCFG_RESERVED2_MASK            0x1FFF00
#define USB2DC_GAHBCFG_RESERVED2_SHIFT           8 
#define USB2DC_GAHBCFG_RESERVED2_BIT             0x1FFF
#define USB2DC_GAHBCFG_RESERVED2_BITWIDTH        13
// RemMemSupp bitfiled (RW) Reset=0
#define USB2DC_GAHBCFG_REMMEMSUPP_MASK           0x200000
#define USB2DC_GAHBCFG_REMMEMSUPP_SHIFT          21 
#define USB2DC_GAHBCFG_REMMEMSUPP_BIT            0x1
#define USB2DC_GAHBCFG_REMMEMSUPP_BITWIDTH       1
// NotiAllDmaWrit bitfiled (RW) Reset=0
#define USB2DC_GAHBCFG_NOTIALLDMAWRIT_MASK       0x400000
#define USB2DC_GAHBCFG_NOTIALLDMAWRIT_SHIFT      22 
#define USB2DC_GAHBCFG_NOTIALLDMAWRIT_BIT        0x1
#define USB2DC_GAHBCFG_NOTIALLDMAWRIT_BITWIDTH   1
// AHBSingle bitfiled (RW) Reset=0
#define USB2DC_GAHBCFG_AHBSINGLE_MASK            0x800000
#define USB2DC_GAHBCFG_AHBSINGLE_SHIFT           23 
#define USB2DC_GAHBCFG_AHBSINGLE_BIT             0x1
#define USB2DC_GAHBCFG_AHBSINGLE_BITWIDTH        1
// InvDescEndianess bitfiled (RW) Reset=0
#define USB2DC_GAHBCFG_INVDESCENDIANESS_MASK     0x1000000
#define USB2DC_GAHBCFG_INVDESCENDIANESS_SHIFT    24 
#define USB2DC_GAHBCFG_INVDESCENDIANESS_BIT      0x1
#define USB2DC_GAHBCFG_INVDESCENDIANESS_BITWIDTH 1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_GAHBCFG_RESERVED_MASK             0xFE000000
#define USB2DC_GAHBCFG_RESERVED_SHIFT            25 
#define USB2DC_GAHBCFG_RESERVED_BIT              0x7F
#define USB2DC_GAHBCFG_RESERVED_BITWIDTH         7
// GUSBCFG Register
#define USB2DC_GUSBCFG_OFS                       0x0000000C
// TOutCal bitfiled (RW) Reset=0
#define USB2DC_GUSBCFG_TOUTCAL_MASK              0x7
#define USB2DC_GUSBCFG_TOUTCAL_SHIFT             0 
#define USB2DC_GUSBCFG_TOUTCAL_BIT               0x7
#define USB2DC_GUSBCFG_TOUTCAL_BITWIDTH          3
// PHYIf bitfiled (RO) Reset=1
#define USB2DC_GUSBCFG_PHYIF_MASK                0x8
#define USB2DC_GUSBCFG_PHYIF_SHIFT               3 
#define USB2DC_GUSBCFG_PHYIF_BIT                 0x1
#define USB2DC_GUSBCFG_PHYIF_BITWIDTH            1
// ULPI_UTMI_Sel bitfiled (RO) Reset=0
#define USB2DC_GUSBCFG_ULPI_UTMI_SEL_MASK        0x10
#define USB2DC_GUSBCFG_ULPI_UTMI_SEL_SHIFT       4 
#define USB2DC_GUSBCFG_ULPI_UTMI_SEL_BIT         0x1
#define USB2DC_GUSBCFG_ULPI_UTMI_SEL_BITWIDTH    1
// FSIntf bitfiled (RO) Reset=0
#define USB2DC_GUSBCFG_FSINTF_MASK               0x20
#define USB2DC_GUSBCFG_FSINTF_SHIFT              5 
#define USB2DC_GUSBCFG_FSINTF_BIT                0x1
#define USB2DC_GUSBCFG_FSINTF_BITWIDTH           1
// PHYSel bitfiled (RO) Reset=0
#define USB2DC_GUSBCFG_PHYSEL_MASK               0x40
#define USB2DC_GUSBCFG_PHYSEL_SHIFT              6 
#define USB2DC_GUSBCFG_PHYSEL_BIT                0x1
#define USB2DC_GUSBCFG_PHYSEL_BITWIDTH           1
// Reserved6 bitfiled (RO) Reset=0
#define USB2DC_GUSBCFG_RESERVED6_MASK            0x380
#define USB2DC_GUSBCFG_RESERVED6_SHIFT           7 
#define USB2DC_GUSBCFG_RESERVED6_BIT             0x7
#define USB2DC_GUSBCFG_RESERVED6_BITWIDTH        3
// USBTrdTim bitfiled (RW) Reset=101
#define USB2DC_GUSBCFG_USBTRDTIM_MASK            0x3C00
#define USB2DC_GUSBCFG_USBTRDTIM_SHIFT           10 
#define USB2DC_GUSBCFG_USBTRDTIM_BIT             0xF
#define USB2DC_GUSBCFG_USBTRDTIM_BITWIDTH        4
// Reserved5 bitfiled (RO) Reset=0
#define USB2DC_GUSBCFG_RESERVED5_MASK            0x4000
#define USB2DC_GUSBCFG_RESERVED5_SHIFT           14 
#define USB2DC_GUSBCFG_RESERVED5_BIT             0x1
#define USB2DC_GUSBCFG_RESERVED5_BITWIDTH        1
// PhyLPwrClkSel bitfiled (RW) Reset=0
#define USB2DC_GUSBCFG_PHYLPWRCLKSEL_MASK        0x8000
#define USB2DC_GUSBCFG_PHYLPWRCLKSEL_SHIFT       15 
#define USB2DC_GUSBCFG_PHYLPWRCLKSEL_BIT         0x1
#define USB2DC_GUSBCFG_PHYLPWRCLKSEL_BITWIDTH    1
// Reserved4 bitfiled (RO) Reset=0
#define USB2DC_GUSBCFG_RESERVED4_MASK            0x3F0000
#define USB2DC_GUSBCFG_RESERVED4_SHIFT           16 
#define USB2DC_GUSBCFG_RESERVED4_BIT             0x3F
#define USB2DC_GUSBCFG_RESERVED4_BITWIDTH        6
// TermSelDLPulse bitfiled (RW) Reset=0
#define USB2DC_GUSBCFG_TERMSELDLPULSE_MASK       0x400000
#define USB2DC_GUSBCFG_TERMSELDLPULSE_SHIFT      22 
#define USB2DC_GUSBCFG_TERMSELDLPULSE_BIT        0x1
#define USB2DC_GUSBCFG_TERMSELDLPULSE_BITWIDTH   1
// Reserved3 bitfiled (RO) Reset=0
#define USB2DC_GUSBCFG_RESERVED3_MASK            0x3800000
#define USB2DC_GUSBCFG_RESERVED3_SHIFT           23 
#define USB2DC_GUSBCFG_RESERVED3_BIT             0x7
#define USB2DC_GUSBCFG_RESERVED3_BITWIDTH        3
// IC_USBCap bitfiled (RO) Reset=0
#define USB2DC_GUSBCFG_IC_USBCAP_MASK            0x4000000
#define USB2DC_GUSBCFG_IC_USBCAP_SHIFT           26 
#define USB2DC_GUSBCFG_IC_USBCAP_BIT             0x1
#define USB2DC_GUSBCFG_IC_USBCAP_BITWIDTH        1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_GUSBCFG_RESERVED2_MASK            0x8000000
#define USB2DC_GUSBCFG_RESERVED2_SHIFT           27 
#define USB2DC_GUSBCFG_RESERVED2_BIT             0x1
#define USB2DC_GUSBCFG_RESERVED2_BITWIDTH        1
// TxEndDelay bitfiled (RW) Reset=0
#define USB2DC_GUSBCFG_TXENDDELAY_MASK           0x10000000
#define USB2DC_GUSBCFG_TXENDDELAY_SHIFT          28 
#define USB2DC_GUSBCFG_TXENDDELAY_BIT            0x1
#define USB2DC_GUSBCFG_TXENDDELAY_BITWIDTH       1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_GUSBCFG_RESERVED_MASK             0x60000000
#define USB2DC_GUSBCFG_RESERVED_SHIFT            29 
#define USB2DC_GUSBCFG_RESERVED_BIT              0x3
#define USB2DC_GUSBCFG_RESERVED_BITWIDTH         2
// CorruptTxPkt bitfiled (WO) Reset=0
#define USB2DC_GUSBCFG_CORRUPTTXPKT_MASK         0x80000000
#define USB2DC_GUSBCFG_CORRUPTTXPKT_SHIFT        31 
#define USB2DC_GUSBCFG_CORRUPTTXPKT_BIT          0x1
#define USB2DC_GUSBCFG_CORRUPTTXPKT_BITWIDTH     1
// GRSTCTL Register
#define USB2DC_GRSTCTL_OFS                       0x00000010
// CSftRst bitfiled (RO) Reset=0
#define USB2DC_GRSTCTL_CSFTRST_MASK              0x1
#define USB2DC_GRSTCTL_CSFTRST_SHIFT             0 
#define USB2DC_GRSTCTL_CSFTRST_BIT               0x1
#define USB2DC_GRSTCTL_CSFTRST_BITWIDTH          1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_GRSTCTL_RESERVED2_MASK            0xE
#define USB2DC_GRSTCTL_RESERVED2_SHIFT           1 
#define USB2DC_GRSTCTL_RESERVED2_BIT             0x7
#define USB2DC_GRSTCTL_RESERVED2_BITWIDTH        3
// RxFFlsh bitfiled (RO) Reset=0
#define USB2DC_GRSTCTL_RXFFLSH_MASK              0x10
#define USB2DC_GRSTCTL_RXFFLSH_SHIFT             4 
#define USB2DC_GRSTCTL_RXFFLSH_BIT               0x1
#define USB2DC_GRSTCTL_RXFFLSH_BITWIDTH          1
// TxFFlsh bitfiled (RO) Reset=0
#define USB2DC_GRSTCTL_TXFFLSH_MASK              0x20
#define USB2DC_GRSTCTL_TXFFLSH_SHIFT             5 
#define USB2DC_GRSTCTL_TXFFLSH_BIT               0x1
#define USB2DC_GRSTCTL_TXFFLSH_BITWIDTH          1
// TxFNum bitfiled (RW) Reset=0
#define USB2DC_GRSTCTL_TXFNUM_MASK               0x7C0
#define USB2DC_GRSTCTL_TXFNUM_SHIFT              6 
#define USB2DC_GRSTCTL_TXFNUM_BIT                0x1F
#define USB2DC_GRSTCTL_TXFNUM_BITWIDTH           5
// Reserved bitfiled (RO) Reset=0
#define USB2DC_GRSTCTL_RESERVED_MASK             0x3FFFF800
#define USB2DC_GRSTCTL_RESERVED_SHIFT            11 
#define USB2DC_GRSTCTL_RESERVED_BIT              0x7FFFF
#define USB2DC_GRSTCTL_RESERVED_BITWIDTH         19
// DMAReq bitfiled (RO) Reset=0
#define USB2DC_GRSTCTL_DMAREQ_MASK               0x40000000
#define USB2DC_GRSTCTL_DMAREQ_SHIFT              30 
#define USB2DC_GRSTCTL_DMAREQ_BIT                0x1
#define USB2DC_GRSTCTL_DMAREQ_BITWIDTH           1
// AHBIdle bitfiled (RO) Reset=1
#define USB2DC_GRSTCTL_AHBIDLE_MASK              0x80000000
#define USB2DC_GRSTCTL_AHBIDLE_SHIFT             31 
#define USB2DC_GRSTCTL_AHBIDLE_BIT               0x1
#define USB2DC_GRSTCTL_AHBIDLE_BITWIDTH          1
// GINTSTS Register
#define USB2DC_GINTSTS_OFS                       0x00000014
// CurMod bitfiled (RO) Reset=0
#define USB2DC_GINTSTS_CURMOD_MASK               0x1
#define USB2DC_GINTSTS_CURMOD_SHIFT              0 
#define USB2DC_GINTSTS_CURMOD_BIT                0x1
#define USB2DC_GINTSTS_CURMOD_BITWIDTH           1
// ModeMis bitfiled (RO) Reset=0
#define USB2DC_GINTSTS_MODEMIS_MASK              0x2
#define USB2DC_GINTSTS_MODEMIS_SHIFT             1 
#define USB2DC_GINTSTS_MODEMIS_BIT               0x1
#define USB2DC_GINTSTS_MODEMIS_BITWIDTH          1
// OTGInt bitfiled (RO) Reset=0
#define USB2DC_GINTSTS_OTGINT_MASK               0x4
#define USB2DC_GINTSTS_OTGINT_SHIFT              2 
#define USB2DC_GINTSTS_OTGINT_BIT                0x1
#define USB2DC_GINTSTS_OTGINT_BITWIDTH           1
// Sof bitfiled (RO) Reset=0
#define USB2DC_GINTSTS_SOF_MASK                  0x8
#define USB2DC_GINTSTS_SOF_SHIFT                 3 
#define USB2DC_GINTSTS_SOF_BIT                   0x1
#define USB2DC_GINTSTS_SOF_BITWIDTH              1
// RxFLvl bitfiled (RO) Reset=0
#define USB2DC_GINTSTS_RXFLVL_MASK               0x10
#define USB2DC_GINTSTS_RXFLVL_SHIFT              4 
#define USB2DC_GINTSTS_RXFLVL_BIT                0x1
#define USB2DC_GINTSTS_RXFLVL_BITWIDTH           1
// Reserved5 bitfiled (RO) Reset=0
#define USB2DC_GINTSTS_RESERVED5_MASK            0x20
#define USB2DC_GINTSTS_RESERVED5_SHIFT           5 
#define USB2DC_GINTSTS_RESERVED5_BIT             0x1
#define USB2DC_GINTSTS_RESERVED5_BITWIDTH        1
// GINNakEff bitfiled (RO) Reset=0
#define USB2DC_GINTSTS_GINNAKEFF_MASK            0x40
#define USB2DC_GINTSTS_GINNAKEFF_SHIFT           6 
#define USB2DC_GINTSTS_GINNAKEFF_BIT             0x1
#define USB2DC_GINTSTS_GINNAKEFF_BITWIDTH        1
// GOUTNakEff bitfiled (RO) Reset=0
#define USB2DC_GINTSTS_GOUTNAKEFF_MASK           0x80
#define USB2DC_GINTSTS_GOUTNAKEFF_SHIFT          7 
#define USB2DC_GINTSTS_GOUTNAKEFF_BIT            0x1
#define USB2DC_GINTSTS_GOUTNAKEFF_BITWIDTH       1
// Reserved4 bitfiled (RO) Reset=0
#define USB2DC_GINTSTS_RESERVED4_MASK            0x300
#define USB2DC_GINTSTS_RESERVED4_SHIFT           8 
#define USB2DC_GINTSTS_RESERVED4_BIT             0x3
#define USB2DC_GINTSTS_RESERVED4_BITWIDTH        2
// ErlySusp bitfiled (RO) Reset=0
#define USB2DC_GINTSTS_ERLYSUSP_MASK             0x400
#define USB2DC_GINTSTS_ERLYSUSP_SHIFT            10 
#define USB2DC_GINTSTS_ERLYSUSP_BIT              0x1
#define USB2DC_GINTSTS_ERLYSUSP_BITWIDTH         1
// USBSusp bitfiled (RO) Reset=0
#define USB2DC_GINTSTS_USBSUSP_MASK              0x800
#define USB2DC_GINTSTS_USBSUSP_SHIFT             11 
#define USB2DC_GINTSTS_USBSUSP_BIT               0x1
#define USB2DC_GINTSTS_USBSUSP_BITWIDTH          1
// USBRst bitfiled (RO) Reset=0
#define USB2DC_GINTSTS_USBRST_MASK               0x1000
#define USB2DC_GINTSTS_USBRST_SHIFT              12 
#define USB2DC_GINTSTS_USBRST_BIT                0x1
#define USB2DC_GINTSTS_USBRST_BITWIDTH           1
// EnumDone bitfiled (RO) Reset=0
#define USB2DC_GINTSTS_ENUMDONE_MASK             0x2000
#define USB2DC_GINTSTS_ENUMDONE_SHIFT            13 
#define USB2DC_GINTSTS_ENUMDONE_BIT              0x1
#define USB2DC_GINTSTS_ENUMDONE_BITWIDTH         1
// ISOOutDrop bitfiled (RO) Reset=0
#define USB2DC_GINTSTS_ISOOUTDROP_MASK           0x4000
#define USB2DC_GINTSTS_ISOOUTDROP_SHIFT          14 
#define USB2DC_GINTSTS_ISOOUTDROP_BIT            0x1
#define USB2DC_GINTSTS_ISOOUTDROP_BITWIDTH       1
// EOPF bitfiled (RO) Reset=0
#define USB2DC_GINTSTS_EOPF_MASK                 0x8000
#define USB2DC_GINTSTS_EOPF_SHIFT                15 
#define USB2DC_GINTSTS_EOPF_BIT                  0x1
#define USB2DC_GINTSTS_EOPF_BITWIDTH             1
// Reserved3 bitfiled (RO) Reset=0
#define USB2DC_GINTSTS_RESERVED3_MASK            0x10000
#define USB2DC_GINTSTS_RESERVED3_SHIFT           16 
#define USB2DC_GINTSTS_RESERVED3_BIT             0x1
#define USB2DC_GINTSTS_RESERVED3_BITWIDTH        1
// EPMis bitfiled (RO) Reset=0
#define USB2DC_GINTSTS_EPMIS_MASK                0x20000
#define USB2DC_GINTSTS_EPMIS_SHIFT               17 
#define USB2DC_GINTSTS_EPMIS_BIT                 0x1
#define USB2DC_GINTSTS_EPMIS_BITWIDTH            1
// IEPInt bitfiled (RO) Reset=0
#define USB2DC_GINTSTS_IEPINT_MASK               0x40000
#define USB2DC_GINTSTS_IEPINT_SHIFT              18 
#define USB2DC_GINTSTS_IEPINT_BIT                0x1
#define USB2DC_GINTSTS_IEPINT_BITWIDTH           1
// OEPInt bitfiled (RO) Reset=0
#define USB2DC_GINTSTS_OEPINT_MASK               0x80000
#define USB2DC_GINTSTS_OEPINT_SHIFT              19 
#define USB2DC_GINTSTS_OEPINT_BIT                0x1
#define USB2DC_GINTSTS_OEPINT_BITWIDTH           1
// incompISOIN bitfiled (RO) Reset=0
#define USB2DC_GINTSTS_INCOMPISOIN_MASK          0x100000
#define USB2DC_GINTSTS_INCOMPISOIN_SHIFT         20 
#define USB2DC_GINTSTS_INCOMPISOIN_BIT           0x1
#define USB2DC_GINTSTS_INCOMPISOIN_BITWIDTH      1
// incompISOOUT bitfiled (RO) Reset=0
#define USB2DC_GINTSTS_INCOMPISOOUT_MASK         0x200000
#define USB2DC_GINTSTS_INCOMPISOOUT_SHIFT        21 
#define USB2DC_GINTSTS_INCOMPISOOUT_BIT          0x1
#define USB2DC_GINTSTS_INCOMPISOOUT_BITWIDTH     1
// FetSusp bitfiled (RO) Reset=0
#define USB2DC_GINTSTS_FETSUSP_MASK              0x400000
#define USB2DC_GINTSTS_FETSUSP_SHIFT             22 
#define USB2DC_GINTSTS_FETSUSP_BIT               0x1
#define USB2DC_GINTSTS_FETSUSP_BITWIDTH          1
// ResetDet bitfiled (RO) Reset=0
#define USB2DC_GINTSTS_RESETDET_MASK             0x800000
#define USB2DC_GINTSTS_RESETDET_SHIFT            23 
#define USB2DC_GINTSTS_RESETDET_BIT              0x1
#define USB2DC_GINTSTS_RESETDET_BITWIDTH         1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_GINTSTS_RESERVED2_MASK            0xF000000
#define USB2DC_GINTSTS_RESERVED2_SHIFT           24 
#define USB2DC_GINTSTS_RESERVED2_BIT             0xF
#define USB2DC_GINTSTS_RESERVED2_BITWIDTH        4
// ConIDStsChng bitfiled (RO) Reset=1
#define USB2DC_GINTSTS_CONIDSTSCHNG_MASK         0x10000000
#define USB2DC_GINTSTS_CONIDSTSCHNG_SHIFT        28 
#define USB2DC_GINTSTS_CONIDSTSCHNG_BIT          0x1
#define USB2DC_GINTSTS_CONIDSTSCHNG_BITWIDTH     1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_GINTSTS_RESERVED_MASK             0x20000000
#define USB2DC_GINTSTS_RESERVED_SHIFT            29 
#define USB2DC_GINTSTS_RESERVED_BIT              0x1
#define USB2DC_GINTSTS_RESERVED_BITWIDTH         1
// SessReqInt bitfiled (RO) Reset=0
#define USB2DC_GINTSTS_SESSREQINT_MASK           0x40000000
#define USB2DC_GINTSTS_SESSREQINT_SHIFT          30 
#define USB2DC_GINTSTS_SESSREQINT_BIT            0x1
#define USB2DC_GINTSTS_SESSREQINT_BITWIDTH       1
// WkUpInt bitfiled (RO) Reset=0
#define USB2DC_GINTSTS_WKUPINT_MASK              0x80000000
#define USB2DC_GINTSTS_WKUPINT_SHIFT             31 
#define USB2DC_GINTSTS_WKUPINT_BIT               0x1
#define USB2DC_GINTSTS_WKUPINT_BITWIDTH          1
// GINTMSK Register
#define USB2DC_GINTMSK_OFS                       0x00000018
// Reserved5 bitfiled (RO) Reset=0
#define USB2DC_GINTMSK_RESERVED5_MASK            0x1
#define USB2DC_GINTMSK_RESERVED5_SHIFT           0 
#define USB2DC_GINTMSK_RESERVED5_BIT             0x1
#define USB2DC_GINTMSK_RESERVED5_BITWIDTH        1
// ModeMisMsk bitfiled (RW) Reset=0
#define USB2DC_GINTMSK_MODEMISMSK_MASK           0x2
#define USB2DC_GINTMSK_MODEMISMSK_SHIFT          1 
#define USB2DC_GINTMSK_MODEMISMSK_BIT            0x1
#define USB2DC_GINTMSK_MODEMISMSK_BITWIDTH       1
// OTGIntMsk bitfiled (RW) Reset=0
#define USB2DC_GINTMSK_OTGINTMSK_MASK            0x4
#define USB2DC_GINTMSK_OTGINTMSK_SHIFT           2 
#define USB2DC_GINTMSK_OTGINTMSK_BIT             0x1
#define USB2DC_GINTMSK_OTGINTMSK_BITWIDTH        1
// SofMsk bitfiled (RW) Reset=0
#define USB2DC_GINTMSK_SOFMSK_MASK               0x8
#define USB2DC_GINTMSK_SOFMSK_SHIFT              3 
#define USB2DC_GINTMSK_SOFMSK_BIT                0x1
#define USB2DC_GINTMSK_SOFMSK_BITWIDTH           1
// RxFLvlMsk bitfiled (RW) Reset=0
#define USB2DC_GINTMSK_RXFLVLMSK_MASK            0x10
#define USB2DC_GINTMSK_RXFLVLMSK_SHIFT           4 
#define USB2DC_GINTMSK_RXFLVLMSK_BIT             0x1
#define USB2DC_GINTMSK_RXFLVLMSK_BITWIDTH        1
// Reserved4 bitfiled (RO) Reset=0
#define USB2DC_GINTMSK_RESERVED4_MASK            0x20
#define USB2DC_GINTMSK_RESERVED4_SHIFT           5 
#define USB2DC_GINTMSK_RESERVED4_BIT             0x1
#define USB2DC_GINTMSK_RESERVED4_BITWIDTH        1
// GINNakEffMsk bitfiled (RW) Reset=0
#define USB2DC_GINTMSK_GINNAKEFFMSK_MASK         0x40
#define USB2DC_GINTMSK_GINNAKEFFMSK_SHIFT        6 
#define USB2DC_GINTMSK_GINNAKEFFMSK_BIT          0x1
#define USB2DC_GINTMSK_GINNAKEFFMSK_BITWIDTH     1
// GOUTNakEffMsk bitfiled (RW) Reset=0
#define USB2DC_GINTMSK_GOUTNAKEFFMSK_MASK        0x80
#define USB2DC_GINTMSK_GOUTNAKEFFMSK_SHIFT       7 
#define USB2DC_GINTMSK_GOUTNAKEFFMSK_BIT         0x1
#define USB2DC_GINTMSK_GOUTNAKEFFMSK_BITWIDTH    1
// Reserved3 bitfiled (RO) Reset=0
#define USB2DC_GINTMSK_RESERVED3_MASK            0x300
#define USB2DC_GINTMSK_RESERVED3_SHIFT           8 
#define USB2DC_GINTMSK_RESERVED3_BIT             0x3
#define USB2DC_GINTMSK_RESERVED3_BITWIDTH        2
// ErlySuspMsk bitfiled (RW) Reset=0
#define USB2DC_GINTMSK_ERLYSUSPMSK_MASK          0x400
#define USB2DC_GINTMSK_ERLYSUSPMSK_SHIFT         10 
#define USB2DC_GINTMSK_ERLYSUSPMSK_BIT           0x1
#define USB2DC_GINTMSK_ERLYSUSPMSK_BITWIDTH      1
// USBSuspMsk bitfiled (RW) Reset=0
#define USB2DC_GINTMSK_USBSUSPMSK_MASK           0x800
#define USB2DC_GINTMSK_USBSUSPMSK_SHIFT          11 
#define USB2DC_GINTMSK_USBSUSPMSK_BIT            0x1
#define USB2DC_GINTMSK_USBSUSPMSK_BITWIDTH       1
// USBRstMsk bitfiled (RW) Reset=0
#define USB2DC_GINTMSK_USBRSTMSK_MASK            0x1000
#define USB2DC_GINTMSK_USBRSTMSK_SHIFT           12 
#define USB2DC_GINTMSK_USBRSTMSK_BIT             0x1
#define USB2DC_GINTMSK_USBRSTMSK_BITWIDTH        1
// EnumDoneMsk bitfiled (RW) Reset=0
#define USB2DC_GINTMSK_ENUMDONEMSK_MASK          0x2000
#define USB2DC_GINTMSK_ENUMDONEMSK_SHIFT         13 
#define USB2DC_GINTMSK_ENUMDONEMSK_BIT           0x1
#define USB2DC_GINTMSK_ENUMDONEMSK_BITWIDTH      1
// ISOOutDropMsk bitfiled (RW) Reset=0
#define USB2DC_GINTMSK_ISOOUTDROPMSK_MASK        0x4000
#define USB2DC_GINTMSK_ISOOUTDROPMSK_SHIFT       14 
#define USB2DC_GINTMSK_ISOOUTDROPMSK_BIT         0x1
#define USB2DC_GINTMSK_ISOOUTDROPMSK_BITWIDTH    1
// EOPFMsk bitfiled (RW) Reset=0
#define USB2DC_GINTMSK_EOPFMSK_MASK              0x8000
#define USB2DC_GINTMSK_EOPFMSK_SHIFT             15 
#define USB2DC_GINTMSK_EOPFMSK_BIT               0x1
#define USB2DC_GINTMSK_EOPFMSK_BITWIDTH          1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_GINTMSK_RESERVED2_MASK            0x10000
#define USB2DC_GINTMSK_RESERVED2_SHIFT           16 
#define USB2DC_GINTMSK_RESERVED2_BIT             0x1
#define USB2DC_GINTMSK_RESERVED2_BITWIDTH        1
// EPMisMsk bitfiled (RW) Reset=0
#define USB2DC_GINTMSK_EPMISMSK_MASK             0x20000
#define USB2DC_GINTMSK_EPMISMSK_SHIFT            17 
#define USB2DC_GINTMSK_EPMISMSK_BIT              0x1
#define USB2DC_GINTMSK_EPMISMSK_BITWIDTH         1
// IEPIntMsk bitfiled (RW) Reset=0
#define USB2DC_GINTMSK_IEPINTMSK_MASK            0x40000
#define USB2DC_GINTMSK_IEPINTMSK_SHIFT           18 
#define USB2DC_GINTMSK_IEPINTMSK_BIT             0x1
#define USB2DC_GINTMSK_IEPINTMSK_BITWIDTH        1
// OEPIntMsk bitfiled (RW) Reset=0
#define USB2DC_GINTMSK_OEPINTMSK_MASK            0x80000
#define USB2DC_GINTMSK_OEPINTMSK_SHIFT           19 
#define USB2DC_GINTMSK_OEPINTMSK_BIT             0x1
#define USB2DC_GINTMSK_OEPINTMSK_BITWIDTH        1
// incompISOINMsk bitfiled (RW) Reset=0
#define USB2DC_GINTMSK_INCOMPISOINMSK_MASK       0x100000
#define USB2DC_GINTMSK_INCOMPISOINMSK_SHIFT      20 
#define USB2DC_GINTMSK_INCOMPISOINMSK_BIT        0x1
#define USB2DC_GINTMSK_INCOMPISOINMSK_BITWIDTH   1
// incompISOOUTMsk bitfiled (RW) Reset=0
#define USB2DC_GINTMSK_INCOMPISOOUTMSK_MASK      0x200000
#define USB2DC_GINTMSK_INCOMPISOOUTMSK_SHIFT     21 
#define USB2DC_GINTMSK_INCOMPISOOUTMSK_BIT       0x1
#define USB2DC_GINTMSK_INCOMPISOOUTMSK_BITWIDTH  1
// FetSuspMsk bitfiled (RW) Reset=0
#define USB2DC_GINTMSK_FETSUSPMSK_MASK           0x400000
#define USB2DC_GINTMSK_FETSUSPMSK_SHIFT          22 
#define USB2DC_GINTMSK_FETSUSPMSK_BIT            0x1
#define USB2DC_GINTMSK_FETSUSPMSK_BITWIDTH       1
// ResetDetMsk bitfiled (RW) Reset=0
#define USB2DC_GINTMSK_RESETDETMSK_MASK          0x800000
#define USB2DC_GINTMSK_RESETDETMSK_SHIFT         23 
#define USB2DC_GINTMSK_RESETDETMSK_BIT           0x1
#define USB2DC_GINTMSK_RESETDETMSK_BITWIDTH      1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_GINTMSK_RESERVED_MASK             0xF000000
#define USB2DC_GINTMSK_RESERVED_SHIFT            24 
#define USB2DC_GINTMSK_RESERVED_BIT              0xF
#define USB2DC_GINTMSK_RESERVED_BITWIDTH         4
// ConIDStsChngMsk bitfiled (RW) Reset=0
#define USB2DC_GINTMSK_CONIDSTSCHNGMSK_MASK      0x10000000
#define USB2DC_GINTMSK_CONIDSTSCHNGMSK_SHIFT     28 
#define USB2DC_GINTMSK_CONIDSTSCHNGMSK_BIT       0x1
#define USB2DC_GINTMSK_CONIDSTSCHNGMSK_BITWIDTH  1
// DisconnIntMsk bitfiled (RW) Reset=0
#define USB2DC_GINTMSK_DISCONNINTMSK_MASK        0x20000000
#define USB2DC_GINTMSK_DISCONNINTMSK_SHIFT       29 
#define USB2DC_GINTMSK_DISCONNINTMSK_BIT         0x1
#define USB2DC_GINTMSK_DISCONNINTMSK_BITWIDTH    1
// SessReqIntMsk bitfiled (RW) Reset=0
#define USB2DC_GINTMSK_SESSREQINTMSK_MASK        0x40000000
#define USB2DC_GINTMSK_SESSREQINTMSK_SHIFT       30 
#define USB2DC_GINTMSK_SESSREQINTMSK_BIT         0x1
#define USB2DC_GINTMSK_SESSREQINTMSK_BITWIDTH    1
// WkUpIntMsk bitfiled (RW) Reset=0
#define USB2DC_GINTMSK_WKUPINTMSK_MASK           0x80000000
#define USB2DC_GINTMSK_WKUPINTMSK_SHIFT          31 
#define USB2DC_GINTMSK_WKUPINTMSK_BIT            0x1
#define USB2DC_GINTMSK_WKUPINTMSK_BITWIDTH       1
// GRXSTSR Register
#define USB2DC_GRXSTSR_OFS                       0x0000001C
// EPNum bitfiled (RO) Reset=0
#define USB2DC_GRXSTSR_EPNUM_MASK                0xF
#define USB2DC_GRXSTSR_EPNUM_SHIFT               0 
#define USB2DC_GRXSTSR_EPNUM_BIT                 0xF
#define USB2DC_GRXSTSR_EPNUM_BITWIDTH            4
// BCnt bitfiled (RO) Reset=0
#define USB2DC_GRXSTSR_BCNT_MASK                 0x7FF0
#define USB2DC_GRXSTSR_BCNT_SHIFT                4 
#define USB2DC_GRXSTSR_BCNT_BIT                  0x7FF
#define USB2DC_GRXSTSR_BCNT_BITWIDTH             11
// DPID bitfiled (RO) Reset=0
#define USB2DC_GRXSTSR_DPID_MASK                 0x18000
#define USB2DC_GRXSTSR_DPID_SHIFT                15 
#define USB2DC_GRXSTSR_DPID_BIT                  0x3
#define USB2DC_GRXSTSR_DPID_BITWIDTH             2
// PktSts bitfiled (RO) Reset=0
#define USB2DC_GRXSTSR_PKTSTS_MASK               0x1E0000
#define USB2DC_GRXSTSR_PKTSTS_SHIFT              17 
#define USB2DC_GRXSTSR_PKTSTS_BIT                0xF
#define USB2DC_GRXSTSR_PKTSTS_BITWIDTH           4
// FN bitfiled (RO) Reset=0
#define USB2DC_GRXSTSR_FN_MASK                   0x1E00000
#define USB2DC_GRXSTSR_FN_SHIFT                  21 
#define USB2DC_GRXSTSR_FN_BIT                    0xF
#define USB2DC_GRXSTSR_FN_BITWIDTH               4
// Reserved bitfiled (RO) Reset=0
#define USB2DC_GRXSTSR_RESERVED_MASK             0xFE000000
#define USB2DC_GRXSTSR_RESERVED_SHIFT            25 
#define USB2DC_GRXSTSR_RESERVED_BIT              0x7F
#define USB2DC_GRXSTSR_RESERVED_BITWIDTH         7
// GRXSTSP Register
#define USB2DC_GRXSTSP_OFS                       0x00000020
// EPNum bitfiled (RO) Reset=0
#define USB2DC_GRXSTSP_EPNUM_MASK                0xF
#define USB2DC_GRXSTSP_EPNUM_SHIFT               0 
#define USB2DC_GRXSTSP_EPNUM_BIT                 0xF
#define USB2DC_GRXSTSP_EPNUM_BITWIDTH            4
// BCnt bitfiled (RO) Reset=0
#define USB2DC_GRXSTSP_BCNT_MASK                 0x7FF0
#define USB2DC_GRXSTSP_BCNT_SHIFT                4 
#define USB2DC_GRXSTSP_BCNT_BIT                  0x7FF
#define USB2DC_GRXSTSP_BCNT_BITWIDTH             11
// DPID bitfiled (RO) Reset=0
#define USB2DC_GRXSTSP_DPID_MASK                 0x18000
#define USB2DC_GRXSTSP_DPID_SHIFT                15 
#define USB2DC_GRXSTSP_DPID_BIT                  0x3
#define USB2DC_GRXSTSP_DPID_BITWIDTH             2
// PktSts bitfiled (RO) Reset=0
#define USB2DC_GRXSTSP_PKTSTS_MASK               0x1E0000
#define USB2DC_GRXSTSP_PKTSTS_SHIFT              17 
#define USB2DC_GRXSTSP_PKTSTS_BIT                0xF
#define USB2DC_GRXSTSP_PKTSTS_BITWIDTH           4
// FN bitfiled (RO) Reset=0
#define USB2DC_GRXSTSP_FN_MASK                   0x1E00000
#define USB2DC_GRXSTSP_FN_SHIFT                  21 
#define USB2DC_GRXSTSP_FN_BIT                    0xF
#define USB2DC_GRXSTSP_FN_BITWIDTH               4
// Reserved bitfiled (RO) Reset=0
#define USB2DC_GRXSTSP_RESERVED_MASK             0xFE000000
#define USB2DC_GRXSTSP_RESERVED_SHIFT            25 
#define USB2DC_GRXSTSP_RESERVED_BIT              0x7F
#define USB2DC_GRXSTSP_RESERVED_BITWIDTH         7
// GRXFSIZ Register
#define USB2DC_GRXFSIZ_OFS                       0x00000024
// RxFDep bitfiled (RW) Reset=110110010010
#define USB2DC_GRXFSIZ_RXFDEP_MASK               0xFFF
#define USB2DC_GRXFSIZ_RXFDEP_SHIFT              0 
#define USB2DC_GRXFSIZ_RXFDEP_BIT                0xFFF
#define USB2DC_GRXFSIZ_RXFDEP_BITWIDTH           12
// Reserved bitfiled (RO) Reset=0
#define USB2DC_GRXFSIZ_RESERVED_MASK             0xFFFFF000
#define USB2DC_GRXFSIZ_RESERVED_SHIFT            12 
#define USB2DC_GRXFSIZ_RESERVED_BIT              0xFFFFF
#define USB2DC_GRXFSIZ_RESERVED_BITWIDTH         20
// GNPTXFSIZ Register
#define USB2DC_GNPTXFSIZ_OFS                     0x00000028
// INEPTxF0StAddr bitfiled (RW) Reset=110110010010
#define USB2DC_GNPTXFSIZ_INEPTXF0STADDR_MASK     0xFFF
#define USB2DC_GNPTXFSIZ_INEPTXF0STADDR_SHIFT    0 
#define USB2DC_GNPTXFSIZ_INEPTXF0STADDR_BIT      0xFFF
#define USB2DC_GNPTXFSIZ_INEPTXF0STADDR_BITWIDTH 12
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_GNPTXFSIZ_RESERVED2_MASK          0xF000
#define USB2DC_GNPTXFSIZ_RESERVED2_SHIFT         12 
#define USB2DC_GNPTXFSIZ_RESERVED2_BIT           0xF
#define USB2DC_GNPTXFSIZ_RESERVED2_BITWIDTH      4
// INEPTxF0Dep bitfiled (RW) Reset=1000000
#define USB2DC_GNPTXFSIZ_INEPTXF0DEP_MASK        0x7F0000
#define USB2DC_GNPTXFSIZ_INEPTXF0DEP_SHIFT       16 
#define USB2DC_GNPTXFSIZ_INEPTXF0DEP_BIT         0x7F
#define USB2DC_GNPTXFSIZ_INEPTXF0DEP_BITWIDTH    7
// Reserved bitfiled (RO) Reset=0
#define USB2DC_GNPTXFSIZ_RESERVED_MASK           0xFF800000
#define USB2DC_GNPTXFSIZ_RESERVED_SHIFT          23 
#define USB2DC_GNPTXFSIZ_RESERVED_BIT            0x1FF
#define USB2DC_GNPTXFSIZ_RESERVED_BITWIDTH       9
// GSNPSID Register
#define USB2DC_GSNPSID_OFS                       0x00000040
// SynopsysID bitfiled (RO) Reset=1001111010101000011000000001010
#define USB2DC_GSNPSID_SYNOPSYSID_MASK           0xFFFFFFFF
#define USB2DC_GSNPSID_SYNOPSYSID_SHIFT          0 
#define USB2DC_GSNPSID_SYNOPSYSID_BIT            0xFFFFFFFF
#define USB2DC_GSNPSID_SYNOPSYSID_BITWIDTH       32
// GHWCFG1 Register
#define USB2DC_GHWCFG1_OFS                       0x00000044
// EpDir bitfiled (RO) Reset=0
#define USB2DC_GHWCFG1_EPDIR_MASK                0xFFFFFFFF
#define USB2DC_GHWCFG1_EPDIR_SHIFT               0 
#define USB2DC_GHWCFG1_EPDIR_BIT                 0xFFFFFFFF
#define USB2DC_GHWCFG1_EPDIR_BITWIDTH            32
// GHWCFG2 Register
#define USB2DC_GHWCFG2_OFS                       0x00000048
// OtgMode bitfiled (RO) Reset=100
#define USB2DC_GHWCFG2_OTGMODE_MASK              0x7
#define USB2DC_GHWCFG2_OTGMODE_SHIFT             0 
#define USB2DC_GHWCFG2_OTGMODE_BIT               0x7
#define USB2DC_GHWCFG2_OTGMODE_BITWIDTH          3
// OtgArch bitfiled (RO) Reset=10
#define USB2DC_GHWCFG2_OTGARCH_MASK              0x18
#define USB2DC_GHWCFG2_OTGARCH_SHIFT             3 
#define USB2DC_GHWCFG2_OTGARCH_BIT               0x3
#define USB2DC_GHWCFG2_OTGARCH_BITWIDTH          2
// SingPnt bitfiled (RO) Reset=0
#define USB2DC_GHWCFG2_SINGPNT_MASK              0x20
#define USB2DC_GHWCFG2_SINGPNT_SHIFT             5 
#define USB2DC_GHWCFG2_SINGPNT_BIT               0x1
#define USB2DC_GHWCFG2_SINGPNT_BITWIDTH          1
// HSPhyType bitfiled (RO) Reset=1
#define USB2DC_GHWCFG2_HSPHYTYPE_MASK            0xC0
#define USB2DC_GHWCFG2_HSPHYTYPE_SHIFT           6 
#define USB2DC_GHWCFG2_HSPHYTYPE_BIT             0x3
#define USB2DC_GHWCFG2_HSPHYTYPE_BITWIDTH        2
// FSPhyType bitfiled (RO) Reset=0
#define USB2DC_GHWCFG2_FSPHYTYPE_MASK            0x300
#define USB2DC_GHWCFG2_FSPHYTYPE_SHIFT           8 
#define USB2DC_GHWCFG2_FSPHYTYPE_BIT             0x3
#define USB2DC_GHWCFG2_FSPHYTYPE_BITWIDTH        2
// NumDevEps bitfiled (RO) Reset=110
#define USB2DC_GHWCFG2_NUMDEVEPS_MASK            0x3C00
#define USB2DC_GHWCFG2_NUMDEVEPS_SHIFT           10 
#define USB2DC_GHWCFG2_NUMDEVEPS_BIT             0xF
#define USB2DC_GHWCFG2_NUMDEVEPS_BITWIDTH        4
// NumHstChnl bitfiled (RO) Reset=11
#define USB2DC_GHWCFG2_NUMHSTCHNL_MASK           0x3C000
#define USB2DC_GHWCFG2_NUMHSTCHNL_SHIFT          14 
#define USB2DC_GHWCFG2_NUMHSTCHNL_BIT            0xF
#define USB2DC_GHWCFG2_NUMHSTCHNL_BITWIDTH       4
// PerioSupport bitfiled (RO) Reset=0
#define USB2DC_GHWCFG2_PERIOSUPPORT_MASK         0x40000
#define USB2DC_GHWCFG2_PERIOSUPPORT_SHIFT        18 
#define USB2DC_GHWCFG2_PERIOSUPPORT_BIT          0x1
#define USB2DC_GHWCFG2_PERIOSUPPORT_BITWIDTH     1
// DynFifoSizing bitfiled (RO) Reset=1
#define USB2DC_GHWCFG2_DYNFIFOSIZING_MASK        0x80000
#define USB2DC_GHWCFG2_DYNFIFOSIZING_SHIFT       19 
#define USB2DC_GHWCFG2_DYNFIFOSIZING_BIT         0x1
#define USB2DC_GHWCFG2_DYNFIFOSIZING_BITWIDTH    1
// MultiProcIntrpt bitfiled (RO) Reset=1
#define USB2DC_GHWCFG2_MULTIPROCINTRPT_MASK      0x100000
#define USB2DC_GHWCFG2_MULTIPROCINTRPT_SHIFT     20 
#define USB2DC_GHWCFG2_MULTIPROCINTRPT_BIT       0x1
#define USB2DC_GHWCFG2_MULTIPROCINTRPT_BITWIDTH  1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_GHWCFG2_RESERVED2_MASK            0x200000
#define USB2DC_GHWCFG2_RESERVED2_SHIFT           21 
#define USB2DC_GHWCFG2_RESERVED2_BIT             0x1
#define USB2DC_GHWCFG2_RESERVED2_BITWIDTH        1
// NPTxQDepth bitfiled (RO) Reset=10
#define USB2DC_GHWCFG2_NPTXQDEPTH_MASK           0xC00000
#define USB2DC_GHWCFG2_NPTXQDEPTH_SHIFT          22 
#define USB2DC_GHWCFG2_NPTXQDEPTH_BIT            0x3
#define USB2DC_GHWCFG2_NPTXQDEPTH_BITWIDTH       2
// PTxQDepth bitfiled (RO) Reset=10
#define USB2DC_GHWCFG2_PTXQDEPTH_MASK            0x3000000
#define USB2DC_GHWCFG2_PTXQDEPTH_SHIFT           24 
#define USB2DC_GHWCFG2_PTXQDEPTH_BIT             0x3
#define USB2DC_GHWCFG2_PTXQDEPTH_BITWIDTH        2
// TknQDepth bitfiled (RO) Reset=1000
#define USB2DC_GHWCFG2_TKNQDEPTH_MASK            0x7C000000
#define USB2DC_GHWCFG2_TKNQDEPTH_SHIFT           26 
#define USB2DC_GHWCFG2_TKNQDEPTH_BIT             0x1F
#define USB2DC_GHWCFG2_TKNQDEPTH_BITWIDTH        5
// Reserved bitfiled (RO) Reset=0
#define USB2DC_GHWCFG2_RESERVED_MASK             0x80000000
#define USB2DC_GHWCFG2_RESERVED_SHIFT            31 
#define USB2DC_GHWCFG2_RESERVED_BIT              0x1
#define USB2DC_GHWCFG2_RESERVED_BITWIDTH         1
// GHWCFG3 Register
#define USB2DC_GHWCFG3_OFS                       0x0000004C
// XferSizeWidth bitfiled (RO) Reset=1000
#define USB2DC_GHWCFG3_XFERSIZEWIDTH_MASK        0xF
#define USB2DC_GHWCFG3_XFERSIZEWIDTH_SHIFT       0 
#define USB2DC_GHWCFG3_XFERSIZEWIDTH_BIT         0xF
#define USB2DC_GHWCFG3_XFERSIZEWIDTH_BITWIDTH    4
// PktSizeWidth bitfiled (RO) Reset=110
#define USB2DC_GHWCFG3_PKTSIZEWIDTH_MASK         0x70
#define USB2DC_GHWCFG3_PKTSIZEWIDTH_SHIFT        4 
#define USB2DC_GHWCFG3_PKTSIZEWIDTH_BIT          0x7
#define USB2DC_GHWCFG3_PKTSIZEWIDTH_BITWIDTH     3
// OtgEn bitfiled (RO) Reset=0
#define USB2DC_GHWCFG3_OTGEN_MASK                0x80
#define USB2DC_GHWCFG3_OTGEN_SHIFT               7 
#define USB2DC_GHWCFG3_OTGEN_BIT                 0x1
#define USB2DC_GHWCFG3_OTGEN_BITWIDTH            1
// I2CIntSel bitfiled (RO) Reset=0
#define USB2DC_GHWCFG3_I2CINTSEL_MASK            0x100
#define USB2DC_GHWCFG3_I2CINTSEL_SHIFT           8 
#define USB2DC_GHWCFG3_I2CINTSEL_BIT             0x1
#define USB2DC_GHWCFG3_I2CINTSEL_BITWIDTH        1
// VndctlSupt bitfiled (RO) Reset=0
#define USB2DC_GHWCFG3_VNDCTLSUPT_MASK           0x200
#define USB2DC_GHWCFG3_VNDCTLSUPT_SHIFT          9 
#define USB2DC_GHWCFG3_VNDCTLSUPT_BIT            0x1
#define USB2DC_GHWCFG3_VNDCTLSUPT_BITWIDTH       1
// OptFeature bitfiled (RO) Reset=1
#define USB2DC_GHWCFG3_OPTFEATURE_MASK           0x400
#define USB2DC_GHWCFG3_OPTFEATURE_SHIFT          10 
#define USB2DC_GHWCFG3_OPTFEATURE_BIT            0x1
#define USB2DC_GHWCFG3_OPTFEATURE_BITWIDTH       1
// RstType bitfiled (RO) Reset=0
#define USB2DC_GHWCFG3_RSTTYPE_MASK              0x800
#define USB2DC_GHWCFG3_RSTTYPE_SHIFT             11 
#define USB2DC_GHWCFG3_RSTTYPE_BIT               0x1
#define USB2DC_GHWCFG3_RSTTYPE_BITWIDTH          1
// ADPSupport bitfiled (RO) Reset=0
#define USB2DC_GHWCFG3_ADPSUPPORT_MASK           0x1000
#define USB2DC_GHWCFG3_ADPSUPPORT_SHIFT          12 
#define USB2DC_GHWCFG3_ADPSUPPORT_BIT            0x1
#define USB2DC_GHWCFG3_ADPSUPPORT_BITWIDTH       1
// HSICMode bitfiled (RO) Reset=0
#define USB2DC_GHWCFG3_HSICMODE_MASK             0x2000
#define USB2DC_GHWCFG3_HSICMODE_SHIFT            13 
#define USB2DC_GHWCFG3_HSICMODE_BIT              0x1
#define USB2DC_GHWCFG3_HSICMODE_BITWIDTH         1
// BCSupport bitfiled (RO) Reset=0
#define USB2DC_GHWCFG3_BCSUPPORT_MASK            0x4000
#define USB2DC_GHWCFG3_BCSUPPORT_SHIFT           14 
#define USB2DC_GHWCFG3_BCSUPPORT_BIT             0x1
#define USB2DC_GHWCFG3_BCSUPPORT_BITWIDTH        1
// LPMMode bitfiled (RO) Reset=0
#define USB2DC_GHWCFG3_LPMMODE_MASK              0x8000
#define USB2DC_GHWCFG3_LPMMODE_SHIFT             15 
#define USB2DC_GHWCFG3_LPMMODE_BIT               0x1
#define USB2DC_GHWCFG3_LPMMODE_BITWIDTH          1
// DfifoDepth bitfiled (RO) Reset=110101011010
#define USB2DC_GHWCFG3_DFIFODEPTH_MASK           0xFFFF0000
#define USB2DC_GHWCFG3_DFIFODEPTH_SHIFT          16 
#define USB2DC_GHWCFG3_DFIFODEPTH_BIT            0xFFFF
#define USB2DC_GHWCFG3_DFIFODEPTH_BITWIDTH       16
// GHWCFG4 Register
#define USB2DC_GHWCFG4_OFS                       0x00000050
// NumDevPerioEps bitfiled (RO) Reset=0
#define USB2DC_GHWCFG4_NUMDEVPERIOEPS_MASK       0xF
#define USB2DC_GHWCFG4_NUMDEVPERIOEPS_SHIFT      0 
#define USB2DC_GHWCFG4_NUMDEVPERIOEPS_BIT        0xF
#define USB2DC_GHWCFG4_NUMDEVPERIOEPS_BITWIDTH   4
// PartialPwrDn bitfiled (RO) Reset=1
#define USB2DC_GHWCFG4_PARTIALPWRDN_MASK         0x10
#define USB2DC_GHWCFG4_PARTIALPWRDN_SHIFT        4 
#define USB2DC_GHWCFG4_PARTIALPWRDN_BIT          0x1
#define USB2DC_GHWCFG4_PARTIALPWRDN_BITWIDTH     1
// AhbFreq bitfiled (RO) Reset=1
#define USB2DC_GHWCFG4_AHBFREQ_MASK              0x20
#define USB2DC_GHWCFG4_AHBFREQ_SHIFT             5 
#define USB2DC_GHWCFG4_AHBFREQ_BIT               0x1
#define USB2DC_GHWCFG4_AHBFREQ_BITWIDTH          1
// Hibernation bitfiled (RO) Reset=0
#define USB2DC_GHWCFG4_HIBERNATION_MASK          0x40
#define USB2DC_GHWCFG4_HIBERNATION_SHIFT         6 
#define USB2DC_GHWCFG4_HIBERNATION_BIT           0x1
#define USB2DC_GHWCFG4_HIBERNATION_BITWIDTH      1
// ExtendedHibernation bitfiled (RO) Reset=0
#define USB2DC_GHWCFG4_EXTENDEDHIBERNATION_MASK  0x80
#define USB2DC_GHWCFG4_EXTENDEDHIBERNATION_SHIFT 7 
#define USB2DC_GHWCFG4_EXTENDEDHIBERNATION_BIT   0x1
#define USB2DC_GHWCFG4_EXTENDEDHIBERNATION_BITWIDTH 1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_GHWCFG4_RESERVED_MASK             0x3F00
#define USB2DC_GHWCFG4_RESERVED_SHIFT            8 
#define USB2DC_GHWCFG4_RESERVED_BIT              0x3F
#define USB2DC_GHWCFG4_RESERVED_BITWIDTH         6
// PhyDataWidth bitfiled (RO) Reset=1
#define USB2DC_GHWCFG4_PHYDATAWIDTH_MASK         0xC000
#define USB2DC_GHWCFG4_PHYDATAWIDTH_SHIFT        14 
#define USB2DC_GHWCFG4_PHYDATAWIDTH_BIT          0x3
#define USB2DC_GHWCFG4_PHYDATAWIDTH_BITWIDTH     2
// NumCtlEps bitfiled (RO) Reset=0
#define USB2DC_GHWCFG4_NUMCTLEPS_MASK            0xF0000
#define USB2DC_GHWCFG4_NUMCTLEPS_SHIFT           16 
#define USB2DC_GHWCFG4_NUMCTLEPS_BIT             0xF
#define USB2DC_GHWCFG4_NUMCTLEPS_BITWIDTH        4
// IddgFltr bitfiled (RO) Reset=0
#define USB2DC_GHWCFG4_IDDGFLTR_MASK             0x100000
#define USB2DC_GHWCFG4_IDDGFLTR_SHIFT            20 
#define USB2DC_GHWCFG4_IDDGFLTR_BIT              0x1
#define USB2DC_GHWCFG4_IDDGFLTR_BITWIDTH         1
// VBusValidFltr bitfiled (RO) Reset=0
#define USB2DC_GHWCFG4_VBUSVALIDFLTR_MASK        0x200000
#define USB2DC_GHWCFG4_VBUSVALIDFLTR_SHIFT       21 
#define USB2DC_GHWCFG4_VBUSVALIDFLTR_BIT         0x1
#define USB2DC_GHWCFG4_VBUSVALIDFLTR_BITWIDTH    1
// AValidFltr bitfiled (RO) Reset=0
#define USB2DC_GHWCFG4_AVALIDFLTR_MASK           0x400000
#define USB2DC_GHWCFG4_AVALIDFLTR_SHIFT          22 
#define USB2DC_GHWCFG4_AVALIDFLTR_BIT            0x1
#define USB2DC_GHWCFG4_AVALIDFLTR_BITWIDTH       1
// BValidFltr bitfiled (RO) Reset=0
#define USB2DC_GHWCFG4_BVALIDFLTR_MASK           0x800000
#define USB2DC_GHWCFG4_BVALIDFLTR_SHIFT          23 
#define USB2DC_GHWCFG4_BVALIDFLTR_BIT            0x1
#define USB2DC_GHWCFG4_BVALIDFLTR_BITWIDTH       1
// SessEndFltr bitfiled (RO) Reset=0
#define USB2DC_GHWCFG4_SESSENDFLTR_MASK          0x1000000
#define USB2DC_GHWCFG4_SESSENDFLTR_SHIFT         24 
#define USB2DC_GHWCFG4_SESSENDFLTR_BIT           0x1
#define USB2DC_GHWCFG4_SESSENDFLTR_BITWIDTH      1
// DedFifoMode bitfiled (RO) Reset=1
#define USB2DC_GHWCFG4_DEDFIFOMODE_MASK          0x2000000
#define USB2DC_GHWCFG4_DEDFIFOMODE_SHIFT         25 
#define USB2DC_GHWCFG4_DEDFIFOMODE_BIT           0x1
#define USB2DC_GHWCFG4_DEDFIFOMODE_BITWIDTH      1
// INEps bitfiled (RO) Reset=110
#define USB2DC_GHWCFG4_INEPS_MASK                0x3C000000
#define USB2DC_GHWCFG4_INEPS_SHIFT               26 
#define USB2DC_GHWCFG4_INEPS_BIT                 0xF
#define USB2DC_GHWCFG4_INEPS_BITWIDTH            4
// DescDMAEnabled bitfiled (RO) Reset=1
#define USB2DC_GHWCFG4_DESCDMAENABLED_MASK       0x40000000
#define USB2DC_GHWCFG4_DESCDMAENABLED_SHIFT      30 
#define USB2DC_GHWCFG4_DESCDMAENABLED_BIT        0x1
#define USB2DC_GHWCFG4_DESCDMAENABLED_BITWIDTH   1
// DescDMA bitfiled (RO) Reset=1
#define USB2DC_GHWCFG4_DESCDMA_MASK              0x80000000
#define USB2DC_GHWCFG4_DESCDMA_SHIFT             31 
#define USB2DC_GHWCFG4_DESCDMA_BIT               0x1
#define USB2DC_GHWCFG4_DESCDMA_BITWIDTH          1
// GDFIFOCFG Register
#define USB2DC_GDFIFOCFG_OFS                     0x0000005C
// GDFIFOCfg bitfiled (RW) Reset=110110010010
#define USB2DC_GDFIFOCFG_GDFIFOCFG_MASK          0xFFFF
#define USB2DC_GDFIFOCFG_GDFIFOCFG_SHIFT         0 
#define USB2DC_GDFIFOCFG_GDFIFOCFG_BIT           0xFFFF
#define USB2DC_GDFIFOCFG_GDFIFOCFG_BITWIDTH      16
// EPInfoBaseAddr bitfiled (RW) Reset=110101011010
#define USB2DC_GDFIFOCFG_EPINFOBASEADDR_MASK     0xFFFF0000
#define USB2DC_GDFIFOCFG_EPINFOBASEADDR_SHIFT    16 
#define USB2DC_GDFIFOCFG_EPINFOBASEADDR_BIT      0xFFFF
#define USB2DC_GDFIFOCFG_EPINFOBASEADDR_BITWIDTH 16
// DIEPTXF1 Register
#define USB2DC_DIEPTXF1_OFS                      0x00000104
// INEPnTxFStAddr bitfiled (RW) Reset=110111010010
#define USB2DC_DIEPTXF1_INEPNTXFSTADDR_MASK      0xFFF
#define USB2DC_DIEPTXF1_INEPNTXFSTADDR_SHIFT     0 
#define USB2DC_DIEPTXF1_INEPNTXFSTADDR_BIT       0xFFF
#define USB2DC_DIEPTXF1_INEPNTXFSTADDR_BITWIDTH  12
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DIEPTXF1_RESERVED2_MASK           0xF000
#define USB2DC_DIEPTXF1_RESERVED2_SHIFT          12 
#define USB2DC_DIEPTXF1_RESERVED2_BIT            0xF
#define USB2DC_DIEPTXF1_RESERVED2_BITWIDTH       4
// INEPnTxFDep bitfiled (RW) Reset=1100000000
#define USB2DC_DIEPTXF1_INEPNTXFDEP_MASK         0x3FF0000
#define USB2DC_DIEPTXF1_INEPNTXFDEP_SHIFT        16 
#define USB2DC_DIEPTXF1_INEPNTXFDEP_BIT          0x3FF
#define USB2DC_DIEPTXF1_INEPNTXFDEP_BITWIDTH     10
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPTXF1_RESERVED_MASK            0xFC000000
#define USB2DC_DIEPTXF1_RESERVED_SHIFT           26 
#define USB2DC_DIEPTXF1_RESERVED_BIT             0x3F
#define USB2DC_DIEPTXF1_RESERVED_BITWIDTH        6
// DIEPTXF2 Register
#define USB2DC_DIEPTXF2_OFS                      0x00000108
// INEPnTxFStAddr bitfiled (RW) Reset=1000011010010
#define USB2DC_DIEPTXF2_INEPNTXFSTADDR_MASK      0x1FFF
#define USB2DC_DIEPTXF2_INEPNTXFSTADDR_SHIFT     0 
#define USB2DC_DIEPTXF2_INEPNTXFSTADDR_BIT       0x1FFF
#define USB2DC_DIEPTXF2_INEPNTXFSTADDR_BITWIDTH  13
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DIEPTXF2_RESERVED2_MASK           0xE000
#define USB2DC_DIEPTXF2_RESERVED2_SHIFT          13 
#define USB2DC_DIEPTXF2_RESERVED2_BIT            0x7
#define USB2DC_DIEPTXF2_RESERVED2_BITWIDTH       3
// INEPnTxFDep bitfiled (RW) Reset=1100000000
#define USB2DC_DIEPTXF2_INEPNTXFDEP_MASK         0x3FF0000
#define USB2DC_DIEPTXF2_INEPNTXFDEP_SHIFT        16 
#define USB2DC_DIEPTXF2_INEPNTXFDEP_BIT          0x3FF
#define USB2DC_DIEPTXF2_INEPNTXFDEP_BITWIDTH     10
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPTXF2_RESERVED_MASK            0xFC000000
#define USB2DC_DIEPTXF2_RESERVED_SHIFT           26 
#define USB2DC_DIEPTXF2_RESERVED_BIT             0x3F
#define USB2DC_DIEPTXF2_RESERVED_BITWIDTH        6
// DIEPTXF3 Register
#define USB2DC_DIEPTXF3_OFS                      0x0000010C
// INEPnTxFStAddr bitfiled (RW) Reset=1001111010010
#define USB2DC_DIEPTXF3_INEPNTXFSTADDR_MASK      0x1FFF
#define USB2DC_DIEPTXF3_INEPNTXFSTADDR_SHIFT     0 
#define USB2DC_DIEPTXF3_INEPNTXFSTADDR_BIT       0x1FFF
#define USB2DC_DIEPTXF3_INEPNTXFSTADDR_BITWIDTH  13
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DIEPTXF3_RESERVED2_MASK           0xE000
#define USB2DC_DIEPTXF3_RESERVED2_SHIFT          13 
#define USB2DC_DIEPTXF3_RESERVED2_BIT            0x7
#define USB2DC_DIEPTXF3_RESERVED2_BITWIDTH       3
// INEPnTxFDep bitfiled (RW) Reset=1000000000
#define USB2DC_DIEPTXF3_INEPNTXFDEP_MASK         0x3FF0000
#define USB2DC_DIEPTXF3_INEPNTXFDEP_SHIFT        16 
#define USB2DC_DIEPTXF3_INEPNTXFDEP_BIT          0x3FF
#define USB2DC_DIEPTXF3_INEPNTXFDEP_BITWIDTH     10
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPTXF3_RESERVED_MASK            0xFC000000
#define USB2DC_DIEPTXF3_RESERVED_SHIFT           26 
#define USB2DC_DIEPTXF3_RESERVED_BIT             0x3F
#define USB2DC_DIEPTXF3_RESERVED_BITWIDTH        6
// DIEPTXF4 Register
#define USB2DC_DIEPTXF4_OFS                      0x00000110
// INEPnTxFStAddr bitfiled (RW) Reset=1010111010010
#define USB2DC_DIEPTXF4_INEPNTXFSTADDR_MASK      0x1FFF
#define USB2DC_DIEPTXF4_INEPNTXFSTADDR_SHIFT     0 
#define USB2DC_DIEPTXF4_INEPNTXFSTADDR_BIT       0x1FFF
#define USB2DC_DIEPTXF4_INEPNTXFSTADDR_BITWIDTH  13
// reserved2 bitfiled (RO) Reset=0
#define USB2DC_DIEPTXF4_RESERVED2_MASK           0xE000
#define USB2DC_DIEPTXF4_RESERVED2_SHIFT          13 
#define USB2DC_DIEPTXF4_RESERVED2_BIT            0x7
#define USB2DC_DIEPTXF4_RESERVED2_BITWIDTH       3
// INEPnTxFDep bitfiled (RW) Reset=1000000000
#define USB2DC_DIEPTXF4_INEPNTXFDEP_MASK         0x3FF0000
#define USB2DC_DIEPTXF4_INEPNTXFDEP_SHIFT        16 
#define USB2DC_DIEPTXF4_INEPNTXFDEP_BIT          0x3FF
#define USB2DC_DIEPTXF4_INEPNTXFDEP_BITWIDTH     10
// reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPTXF4_RESERVED_MASK            0xFC000000
#define USB2DC_DIEPTXF4_RESERVED_SHIFT           26 
#define USB2DC_DIEPTXF4_RESERVED_BIT             0x3F
#define USB2DC_DIEPTXF4_RESERVED_BITWIDTH        6
// DIEPTXF5 Register
#define USB2DC_DIEPTXF5_OFS                      0x00000114
// INEPnTxFStAddr bitfiled (RW) Reset=1011111010010
#define USB2DC_DIEPTXF5_INEPNTXFSTADDR_MASK      0x1FFF
#define USB2DC_DIEPTXF5_INEPNTXFSTADDR_SHIFT     0 
#define USB2DC_DIEPTXF5_INEPNTXFSTADDR_BIT       0x1FFF
#define USB2DC_DIEPTXF5_INEPNTXFSTADDR_BITWIDTH  13
// reserved2 bitfiled (RO) Reset=0
#define USB2DC_DIEPTXF5_RESERVED2_MASK           0xE000
#define USB2DC_DIEPTXF5_RESERVED2_SHIFT          13 
#define USB2DC_DIEPTXF5_RESERVED2_BIT            0x7
#define USB2DC_DIEPTXF5_RESERVED2_BITWIDTH       3
// INEPnTxFDep bitfiled (RW) Reset=100000000
#define USB2DC_DIEPTXF5_INEPNTXFDEP_MASK         0x1FF0000
#define USB2DC_DIEPTXF5_INEPNTXFDEP_SHIFT        16 
#define USB2DC_DIEPTXF5_INEPNTXFDEP_BIT          0x1FF
#define USB2DC_DIEPTXF5_INEPNTXFDEP_BITWIDTH     9
// reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPTXF5_RESERVED_MASK            0xFE000000
#define USB2DC_DIEPTXF5_RESERVED_SHIFT           25 
#define USB2DC_DIEPTXF5_RESERVED_BIT             0x7F
#define USB2DC_DIEPTXF5_RESERVED_BITWIDTH        7
// DIEPTXF6 Register
#define USB2DC_DIEPTXF6_OFS                      0x00000118
// INEPnTxFStAddr bitfiled (RW) Reset=1100011010010
#define USB2DC_DIEPTXF6_INEPNTXFSTADDR_MASK      0x1FFF
#define USB2DC_DIEPTXF6_INEPNTXFSTADDR_SHIFT     0 
#define USB2DC_DIEPTXF6_INEPNTXFSTADDR_BIT       0x1FFF
#define USB2DC_DIEPTXF6_INEPNTXFSTADDR_BITWIDTH  13
// reserved2 bitfiled (RO) Reset=0
#define USB2DC_DIEPTXF6_RESERVED2_MASK           0xE000
#define USB2DC_DIEPTXF6_RESERVED2_SHIFT          13 
#define USB2DC_DIEPTXF6_RESERVED2_BIT            0x7
#define USB2DC_DIEPTXF6_RESERVED2_BITWIDTH       3
// INEPnTxFDep bitfiled (RW) Reset=100000000
#define USB2DC_DIEPTXF6_INEPNTXFDEP_MASK         0x1FF0000
#define USB2DC_DIEPTXF6_INEPNTXFDEP_SHIFT        16 
#define USB2DC_DIEPTXF6_INEPNTXFDEP_BIT          0x1FF
#define USB2DC_DIEPTXF6_INEPNTXFDEP_BITWIDTH     9
// reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPTXF6_RESERVED_MASK            0xFE000000
#define USB2DC_DIEPTXF6_RESERVED_SHIFT           25 
#define USB2DC_DIEPTXF6_RESERVED_BIT             0x7F
#define USB2DC_DIEPTXF6_RESERVED_BITWIDTH        7
// DCFG Register
#define USB2DC_DCFG_OFS                          0x00000800
// DevSpd bitfiled (RW) Reset=0
#define USB2DC_DCFG_DEVSPD_MASK                  0x3
#define USB2DC_DCFG_DEVSPD_SHIFT                 0 
#define USB2DC_DCFG_DEVSPD_BIT                   0x3
#define USB2DC_DCFG_DEVSPD_BITWIDTH              2
// NZStsOUTHShk bitfiled (RW) Reset=0
#define USB2DC_DCFG_NZSTSOUTHSHK_MASK            0x4
#define USB2DC_DCFG_NZSTSOUTHSHK_SHIFT           2 
#define USB2DC_DCFG_NZSTSOUTHSHK_BIT             0x1
#define USB2DC_DCFG_NZSTSOUTHSHK_BITWIDTH        1
// Ena32KHzSusp bitfiled (RW) Reset=0
#define USB2DC_DCFG_ENA32KHZSUSP_MASK            0x8
#define USB2DC_DCFG_ENA32KHZSUSP_SHIFT           3 
#define USB2DC_DCFG_ENA32KHZSUSP_BIT             0x1
#define USB2DC_DCFG_ENA32KHZSUSP_BITWIDTH        1
// DevAddr bitfiled (RW) Reset=0
#define USB2DC_DCFG_DEVADDR_MASK                 0x7F0
#define USB2DC_DCFG_DEVADDR_SHIFT                4 
#define USB2DC_DCFG_DEVADDR_BIT                  0x7F
#define USB2DC_DCFG_DEVADDR_BITWIDTH             7
// PerFrInt bitfiled (RW) Reset=0
#define USB2DC_DCFG_PERFRINT_MASK                0x1800
#define USB2DC_DCFG_PERFRINT_SHIFT               11 
#define USB2DC_DCFG_PERFRINT_BIT                 0x3
#define USB2DC_DCFG_PERFRINT_BITWIDTH            2
// EnDevOutNak bitfiled (RW) Reset=0
#define USB2DC_DCFG_ENDEVOUTNAK_MASK             0x2000
#define USB2DC_DCFG_ENDEVOUTNAK_SHIFT            13 
#define USB2DC_DCFG_ENDEVOUTNAK_BIT              0x1
#define USB2DC_DCFG_ENDEVOUTNAK_BITWIDTH         1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DCFG_RESERVED_MASK                0x7FC000
#define USB2DC_DCFG_RESERVED_SHIFT               14 
#define USB2DC_DCFG_RESERVED_BIT                 0x1FF
#define USB2DC_DCFG_RESERVED_BITWIDTH            9
// DescDMA bitfiled (RW) Reset=0
#define USB2DC_DCFG_DESCDMA_MASK                 0x800000
#define USB2DC_DCFG_DESCDMA_SHIFT                23 
#define USB2DC_DCFG_DESCDMA_BIT                  0x1
#define USB2DC_DCFG_DESCDMA_BITWIDTH             1
// PerSchIntvl bitfiled (RW) Reset=0
#define USB2DC_DCFG_PERSCHINTVL_MASK             0x3000000
#define USB2DC_DCFG_PERSCHINTVL_SHIFT            24 
#define USB2DC_DCFG_PERSCHINTVL_BIT              0x3
#define USB2DC_DCFG_PERSCHINTVL_BITWIDTH         2
// ResValid bitfiled (RW) Reset=10
#define USB2DC_DCFG_RESVALID_MASK                0xFC000000
#define USB2DC_DCFG_RESVALID_SHIFT               26 
#define USB2DC_DCFG_RESVALID_BIT                 0x3F
#define USB2DC_DCFG_RESVALID_BITWIDTH            6
// DCTL Register
#define USB2DC_DCTL_OFS                          0x00000804
// RmtWkUpSig bitfiled (RW) Reset=0
#define USB2DC_DCTL_RMTWKUPSIG_MASK              0x1
#define USB2DC_DCTL_RMTWKUPSIG_SHIFT             0 
#define USB2DC_DCTL_RMTWKUPSIG_BIT               0x1
#define USB2DC_DCTL_RMTWKUPSIG_BITWIDTH          1
// SftDiscon bitfiled (RW) Reset=1
#define USB2DC_DCTL_SFTDISCON_MASK               0x2
#define USB2DC_DCTL_SFTDISCON_SHIFT              1 
#define USB2DC_DCTL_SFTDISCON_BIT                0x1
#define USB2DC_DCTL_SFTDISCON_BITWIDTH           1
// GNPINNakSts bitfiled (RO) Reset=0
#define USB2DC_DCTL_GNPINNAKSTS_MASK             0x4
#define USB2DC_DCTL_GNPINNAKSTS_SHIFT            2 
#define USB2DC_DCTL_GNPINNAKSTS_BIT              0x1
#define USB2DC_DCTL_GNPINNAKSTS_BITWIDTH         1
// GOUTNakSts bitfiled (RO) Reset=0
#define USB2DC_DCTL_GOUTNAKSTS_MASK              0x8
#define USB2DC_DCTL_GOUTNAKSTS_SHIFT             3 
#define USB2DC_DCTL_GOUTNAKSTS_BIT               0x1
#define USB2DC_DCTL_GOUTNAKSTS_BITWIDTH          1
// TstCtl bitfiled (RW) Reset=0
#define USB2DC_DCTL_TSTCTL_MASK                  0x70
#define USB2DC_DCTL_TSTCTL_SHIFT                 4 
#define USB2DC_DCTL_TSTCTL_BIT                   0x7
#define USB2DC_DCTL_TSTCTL_BITWIDTH              3
// SGNPInNak bitfiled (WO) Reset=0
#define USB2DC_DCTL_SGNPINNAK_MASK               0x80
#define USB2DC_DCTL_SGNPINNAK_SHIFT              7 
#define USB2DC_DCTL_SGNPINNAK_BIT                0x1
#define USB2DC_DCTL_SGNPINNAK_BITWIDTH           1
// CGNPInNak bitfiled (WO) Reset=0
#define USB2DC_DCTL_CGNPINNAK_MASK               0x100
#define USB2DC_DCTL_CGNPINNAK_SHIFT              8 
#define USB2DC_DCTL_CGNPINNAK_BIT                0x1
#define USB2DC_DCTL_CGNPINNAK_BITWIDTH           1
// SGOUTNak bitfiled (WO) Reset=0
#define USB2DC_DCTL_SGOUTNAK_MASK                0x200
#define USB2DC_DCTL_SGOUTNAK_SHIFT               9 
#define USB2DC_DCTL_SGOUTNAK_BIT                 0x1
#define USB2DC_DCTL_SGOUTNAK_BITWIDTH            1
// CGOUTNak bitfiled (WO) Reset=0
#define USB2DC_DCTL_CGOUTNAK_MASK                0x400
#define USB2DC_DCTL_CGOUTNAK_SHIFT               10 
#define USB2DC_DCTL_CGOUTNAK_BIT                 0x1
#define USB2DC_DCTL_CGOUTNAK_BITWIDTH            1
// PWROnPrgDone bitfiled (RW) Reset=0
#define USB2DC_DCTL_PWRONPRGDONE_MASK            0x800
#define USB2DC_DCTL_PWRONPRGDONE_SHIFT           11 
#define USB2DC_DCTL_PWRONPRGDONE_BIT             0x1
#define USB2DC_DCTL_PWRONPRGDONE_BITWIDTH        1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DCTL_RESERVED2_MASK               0x1000
#define USB2DC_DCTL_RESERVED2_SHIFT              12 
#define USB2DC_DCTL_RESERVED2_BIT                0x1
#define USB2DC_DCTL_RESERVED2_BITWIDTH           1
// GMC bitfiled (RW) Reset=0
#define USB2DC_DCTL_GMC_MASK                     0x6000
#define USB2DC_DCTL_GMC_SHIFT                    13 
#define USB2DC_DCTL_GMC_BIT                      0x3
#define USB2DC_DCTL_GMC_BITWIDTH                 2
// IgnrFrmNum bitfiled (RW) Reset=0
#define USB2DC_DCTL_IGNRFRMNUM_MASK              0x8000
#define USB2DC_DCTL_IGNRFRMNUM_SHIFT             15 
#define USB2DC_DCTL_IGNRFRMNUM_BIT               0x1
#define USB2DC_DCTL_IGNRFRMNUM_BITWIDTH          1
// NakOnBble bitfiled (RW) Reset=0
#define USB2DC_DCTL_NAKONBBLE_MASK               0x10000
#define USB2DC_DCTL_NAKONBBLE_SHIFT              16 
#define USB2DC_DCTL_NAKONBBLE_BIT                0x1
#define USB2DC_DCTL_NAKONBBLE_BITWIDTH           1
// EnContOnBNA bitfiled (RW) Reset=0
#define USB2DC_DCTL_ENCONTONBNA_MASK             0x20000
#define USB2DC_DCTL_ENCONTONBNA_SHIFT            17 
#define USB2DC_DCTL_ENCONTONBNA_BIT              0x1
#define USB2DC_DCTL_ENCONTONBNA_BITWIDTH         1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DCTL_RESERVED_MASK                0xFFFC0000
#define USB2DC_DCTL_RESERVED_SHIFT               18 
#define USB2DC_DCTL_RESERVED_BIT                 0x3FFF
#define USB2DC_DCTL_RESERVED_BITWIDTH            14
// DSTS Register
#define USB2DC_DSTS_OFS                          0x00000808
// SuspSts bitfiled (RO) Reset=0
#define USB2DC_DSTS_SUSPSTS_MASK                 0x1
#define USB2DC_DSTS_SUSPSTS_SHIFT                0 
#define USB2DC_DSTS_SUSPSTS_BIT                  0x1
#define USB2DC_DSTS_SUSPSTS_BITWIDTH             1
// EnumSpd bitfiled (RO) Reset=1
#define USB2DC_DSTS_ENUMSPD_MASK                 0x6
#define USB2DC_DSTS_ENUMSPD_SHIFT                1 
#define USB2DC_DSTS_ENUMSPD_BIT                  0x3
#define USB2DC_DSTS_ENUMSPD_BITWIDTH             2
// ErrticErr bitfiled (RO) Reset=0
#define USB2DC_DSTS_ERRTICERR_MASK               0x8
#define USB2DC_DSTS_ERRTICERR_SHIFT              3 
#define USB2DC_DSTS_ERRTICERR_BIT                0x1
#define USB2DC_DSTS_ERRTICERR_BITWIDTH           1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DSTS_RESERVED2_MASK               0xF0
#define USB2DC_DSTS_RESERVED2_SHIFT              4 
#define USB2DC_DSTS_RESERVED2_BIT                0xF
#define USB2DC_DSTS_RESERVED2_BITWIDTH           4
// SOFFN bitfiled (RO) Reset=0
#define USB2DC_DSTS_SOFFN_MASK                   0x3FFF00
#define USB2DC_DSTS_SOFFN_SHIFT                  8 
#define USB2DC_DSTS_SOFFN_BIT                    0x3FFF
#define USB2DC_DSTS_SOFFN_BITWIDTH               14
// DevLnSts bitfiled (RO) Reset=0
#define USB2DC_DSTS_DEVLNSTS_MASK                0xC00000
#define USB2DC_DSTS_DEVLNSTS_SHIFT               22 
#define USB2DC_DSTS_DEVLNSTS_BIT                 0x3
#define USB2DC_DSTS_DEVLNSTS_BITWIDTH            2
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DSTS_RESERVED_MASK                0xFF000000
#define USB2DC_DSTS_RESERVED_SHIFT               24 
#define USB2DC_DSTS_RESERVED_BIT                 0xFF
#define USB2DC_DSTS_RESERVED_BITWIDTH            8
// DIEPMSK Register
#define USB2DC_DIEPMSK_OFS                       0x00000810
// XferComplMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPMSK_XFERCOMPLMSK_MASK         0x1
#define USB2DC_DIEPMSK_XFERCOMPLMSK_SHIFT        0 
#define USB2DC_DIEPMSK_XFERCOMPLMSK_BIT          0x1
#define USB2DC_DIEPMSK_XFERCOMPLMSK_BITWIDTH     1
// EPDisbldMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPMSK_EPDISBLDMSK_MASK          0x2
#define USB2DC_DIEPMSK_EPDISBLDMSK_SHIFT         1 
#define USB2DC_DIEPMSK_EPDISBLDMSK_BIT           0x1
#define USB2DC_DIEPMSK_EPDISBLDMSK_BITWIDTH      1
// AHBErrMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPMSK_AHBERRMSK_MASK            0x4
#define USB2DC_DIEPMSK_AHBERRMSK_SHIFT           2 
#define USB2DC_DIEPMSK_AHBERRMSK_BIT             0x1
#define USB2DC_DIEPMSK_AHBERRMSK_BITWIDTH        1
// TimeOUTMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPMSK_TIMEOUTMSK_MASK           0x8
#define USB2DC_DIEPMSK_TIMEOUTMSK_SHIFT          3 
#define USB2DC_DIEPMSK_TIMEOUTMSK_BIT            0x1
#define USB2DC_DIEPMSK_TIMEOUTMSK_BITWIDTH       1
// INTknTXFEmpMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPMSK_INTKNTXFEMPMSK_MASK       0x10
#define USB2DC_DIEPMSK_INTKNTXFEMPMSK_SHIFT      4 
#define USB2DC_DIEPMSK_INTKNTXFEMPMSK_BIT        0x1
#define USB2DC_DIEPMSK_INTKNTXFEMPMSK_BITWIDTH   1
// INTknEPMisMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPMSK_INTKNEPMISMSK_MASK        0x20
#define USB2DC_DIEPMSK_INTKNEPMISMSK_SHIFT       5 
#define USB2DC_DIEPMSK_INTKNEPMISMSK_BIT         0x1
#define USB2DC_DIEPMSK_INTKNEPMISMSK_BITWIDTH    1
// INEPNakEffMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPMSK_INEPNAKEFFMSK_MASK        0x40
#define USB2DC_DIEPMSK_INEPNAKEFFMSK_SHIFT       6 
#define USB2DC_DIEPMSK_INEPNAKEFFMSK_BIT         0x1
#define USB2DC_DIEPMSK_INEPNAKEFFMSK_BITWIDTH    1
// Reserved3 bitfiled (RO) Reset=0
#define USB2DC_DIEPMSK_RESERVED3_MASK            0x80
#define USB2DC_DIEPMSK_RESERVED3_SHIFT           7 
#define USB2DC_DIEPMSK_RESERVED3_BIT             0x1
#define USB2DC_DIEPMSK_RESERVED3_BITWIDTH        1
// TxfifoUndrnMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPMSK_TXFIFOUNDRNMSK_MASK       0x100
#define USB2DC_DIEPMSK_TXFIFOUNDRNMSK_SHIFT      8 
#define USB2DC_DIEPMSK_TXFIFOUNDRNMSK_BIT        0x1
#define USB2DC_DIEPMSK_TXFIFOUNDRNMSK_BITWIDTH   1
// BNAInIntrMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPMSK_BNAININTRMSK_MASK         0x200
#define USB2DC_DIEPMSK_BNAININTRMSK_SHIFT        9 
#define USB2DC_DIEPMSK_BNAININTRMSK_BIT          0x1
#define USB2DC_DIEPMSK_BNAININTRMSK_BITWIDTH     1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DIEPMSK_RESERVED2_MASK            0x1C00
#define USB2DC_DIEPMSK_RESERVED2_SHIFT           10 
#define USB2DC_DIEPMSK_RESERVED2_BIT             0x7
#define USB2DC_DIEPMSK_RESERVED2_BITWIDTH        3
// NAKMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPMSK_NAKMSK_MASK               0x2000
#define USB2DC_DIEPMSK_NAKMSK_SHIFT              13 
#define USB2DC_DIEPMSK_NAKMSK_BIT                0x1
#define USB2DC_DIEPMSK_NAKMSK_BITWIDTH           1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPMSK_RESERVED_MASK             0xFFFFC000
#define USB2DC_DIEPMSK_RESERVED_SHIFT            14 
#define USB2DC_DIEPMSK_RESERVED_BIT              0x3FFFF
#define USB2DC_DIEPMSK_RESERVED_BITWIDTH         18
// DOEPMSK Register
#define USB2DC_DOEPMSK_OFS                       0x00000814
// XferComplMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPMSK_XFERCOMPLMSK_MASK         0x1
#define USB2DC_DOEPMSK_XFERCOMPLMSK_SHIFT        0 
#define USB2DC_DOEPMSK_XFERCOMPLMSK_BIT          0x1
#define USB2DC_DOEPMSK_XFERCOMPLMSK_BITWIDTH     1
// EPDisbldMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPMSK_EPDISBLDMSK_MASK          0x2
#define USB2DC_DOEPMSK_EPDISBLDMSK_SHIFT         1 
#define USB2DC_DOEPMSK_EPDISBLDMSK_BIT           0x1
#define USB2DC_DOEPMSK_EPDISBLDMSK_BITWIDTH      1
// AHBErrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPMSK_AHBERRMSK_MASK            0x4
#define USB2DC_DOEPMSK_AHBERRMSK_SHIFT           2 
#define USB2DC_DOEPMSK_AHBERRMSK_BIT             0x1
#define USB2DC_DOEPMSK_AHBERRMSK_BITWIDTH        1
// SetUPMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPMSK_SETUPMSK_MASK             0x8
#define USB2DC_DOEPMSK_SETUPMSK_SHIFT            3 
#define USB2DC_DOEPMSK_SETUPMSK_BIT              0x1
#define USB2DC_DOEPMSK_SETUPMSK_BITWIDTH         1
// OUTTknEPdisMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPMSK_OUTTKNEPDISMSK_MASK       0x10
#define USB2DC_DOEPMSK_OUTTKNEPDISMSK_SHIFT      4 
#define USB2DC_DOEPMSK_OUTTKNEPDISMSK_BIT        0x1
#define USB2DC_DOEPMSK_OUTTKNEPDISMSK_BITWIDTH   1
// StsPhseRcvdMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPMSK_STSPHSERCVDMSK_MASK       0x20
#define USB2DC_DOEPMSK_STSPHSERCVDMSK_SHIFT      5 
#define USB2DC_DOEPMSK_STSPHSERCVDMSK_BIT        0x1
#define USB2DC_DOEPMSK_STSPHSERCVDMSK_BITWIDTH   1
// Back2BackSETup bitfiled (RW) Reset=0
#define USB2DC_DOEPMSK_BACK2BACKSETUP_MASK       0x40
#define USB2DC_DOEPMSK_BACK2BACKSETUP_SHIFT      6 
#define USB2DC_DOEPMSK_BACK2BACKSETUP_BIT        0x1
#define USB2DC_DOEPMSK_BACK2BACKSETUP_BITWIDTH   1
// Reserved3 bitfiled (RO) Reset=0
#define USB2DC_DOEPMSK_RESERVED3_MASK            0x80
#define USB2DC_DOEPMSK_RESERVED3_SHIFT           7 
#define USB2DC_DOEPMSK_RESERVED3_BIT             0x1
#define USB2DC_DOEPMSK_RESERVED3_BITWIDTH        1
// OutPktErrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPMSK_OUTPKTERRMSK_MASK         0x100
#define USB2DC_DOEPMSK_OUTPKTERRMSK_SHIFT        8 
#define USB2DC_DOEPMSK_OUTPKTERRMSK_BIT          0x1
#define USB2DC_DOEPMSK_OUTPKTERRMSK_BITWIDTH     1
// BnaOutIntrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPMSK_BNAOUTINTRMSK_MASK        0x200
#define USB2DC_DOEPMSK_BNAOUTINTRMSK_SHIFT       9 
#define USB2DC_DOEPMSK_BNAOUTINTRMSK_BIT         0x1
#define USB2DC_DOEPMSK_BNAOUTINTRMSK_BITWIDTH    1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DOEPMSK_RESERVED2_MASK            0xC00
#define USB2DC_DOEPMSK_RESERVED2_SHIFT           10 
#define USB2DC_DOEPMSK_RESERVED2_BIT             0x3
#define USB2DC_DOEPMSK_RESERVED2_BITWIDTH        2
// BbleErrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPMSK_BBLEERRMSK_MASK           0x1000
#define USB2DC_DOEPMSK_BBLEERRMSK_SHIFT          12 
#define USB2DC_DOEPMSK_BBLEERRMSK_BIT            0x1
#define USB2DC_DOEPMSK_BBLEERRMSK_BITWIDTH       1
// NAKMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPMSK_NAKMSK_MASK               0x2000
#define USB2DC_DOEPMSK_NAKMSK_SHIFT              13 
#define USB2DC_DOEPMSK_NAKMSK_BIT                0x1
#define USB2DC_DOEPMSK_NAKMSK_BITWIDTH           1
// NYETMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPMSK_NYETMSK_MASK              0x4000
#define USB2DC_DOEPMSK_NYETMSK_SHIFT             14 
#define USB2DC_DOEPMSK_NYETMSK_BIT               0x1
#define USB2DC_DOEPMSK_NYETMSK_BITWIDTH          1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DOEPMSK_RESERVED_MASK             0xFFFF8000
#define USB2DC_DOEPMSK_RESERVED_SHIFT            15 
#define USB2DC_DOEPMSK_RESERVED_BIT              0x1FFFF
#define USB2DC_DOEPMSK_RESERVED_BITWIDTH         17
// DAINT Register
#define USB2DC_DAINT_OFS                         0x00000818
// InEpInt0 bitfiled (RO) Reset=0
#define USB2DC_DAINT_INEPINT0_MASK               0x1
#define USB2DC_DAINT_INEPINT0_SHIFT              0 
#define USB2DC_DAINT_INEPINT0_BIT                0x1
#define USB2DC_DAINT_INEPINT0_BITWIDTH           1
// InEpInt1 bitfiled (RO) Reset=0
#define USB2DC_DAINT_INEPINT1_MASK               0x2
#define USB2DC_DAINT_INEPINT1_SHIFT              1 
#define USB2DC_DAINT_INEPINT1_BIT                0x1
#define USB2DC_DAINT_INEPINT1_BITWIDTH           1
// InEpInt2 bitfiled (RO) Reset=0
#define USB2DC_DAINT_INEPINT2_MASK               0x4
#define USB2DC_DAINT_INEPINT2_SHIFT              2 
#define USB2DC_DAINT_INEPINT2_BIT                0x1
#define USB2DC_DAINT_INEPINT2_BITWIDTH           1
// InEpInt3 bitfiled (RO) Reset=0
#define USB2DC_DAINT_INEPINT3_MASK               0x8
#define USB2DC_DAINT_INEPINT3_SHIFT              3 
#define USB2DC_DAINT_INEPINT3_BIT                0x1
#define USB2DC_DAINT_INEPINT3_BITWIDTH           1
// InEpInt4 bitfiled (RO) Reset=0
#define USB2DC_DAINT_INEPINT4_MASK               0x10
#define USB2DC_DAINT_INEPINT4_SHIFT              4 
#define USB2DC_DAINT_INEPINT4_BIT                0x1
#define USB2DC_DAINT_INEPINT4_BITWIDTH           1
// InEpInt5 bitfiled (RO) Reset=0
#define USB2DC_DAINT_INEPINT5_MASK               0x20
#define USB2DC_DAINT_INEPINT5_SHIFT              5 
#define USB2DC_DAINT_INEPINT5_BIT                0x1
#define USB2DC_DAINT_INEPINT5_BITWIDTH           1
// InEpInt6 bitfiled (RO) Reset=0
#define USB2DC_DAINT_INEPINT6_MASK               0x40
#define USB2DC_DAINT_INEPINT6_SHIFT              6 
#define USB2DC_DAINT_INEPINT6_BIT                0x1
#define USB2DC_DAINT_INEPINT6_BITWIDTH           1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DAINT_RESERVED2_MASK              0xFF80
#define USB2DC_DAINT_RESERVED2_SHIFT             7 
#define USB2DC_DAINT_RESERVED2_BIT               0x1FF
#define USB2DC_DAINT_RESERVED2_BITWIDTH          9
// OutEPInt0 bitfiled (RO) Reset=0
#define USB2DC_DAINT_OUTEPINT0_MASK              0x10000
#define USB2DC_DAINT_OUTEPINT0_SHIFT             16 
#define USB2DC_DAINT_OUTEPINT0_BIT               0x1
#define USB2DC_DAINT_OUTEPINT0_BITWIDTH          1
// OutEPInt1 bitfiled (RO) Reset=0
#define USB2DC_DAINT_OUTEPINT1_MASK              0x20000
#define USB2DC_DAINT_OUTEPINT1_SHIFT             17 
#define USB2DC_DAINT_OUTEPINT1_BIT               0x1
#define USB2DC_DAINT_OUTEPINT1_BITWIDTH          1
// OutEPInt2 bitfiled (RO) Reset=0
#define USB2DC_DAINT_OUTEPINT2_MASK              0x40000
#define USB2DC_DAINT_OUTEPINT2_SHIFT             18 
#define USB2DC_DAINT_OUTEPINT2_BIT               0x1
#define USB2DC_DAINT_OUTEPINT2_BITWIDTH          1
// OutEPInt3 bitfiled (RO) Reset=0
#define USB2DC_DAINT_OUTEPINT3_MASK              0x80000
#define USB2DC_DAINT_OUTEPINT3_SHIFT             19 
#define USB2DC_DAINT_OUTEPINT3_BIT               0x1
#define USB2DC_DAINT_OUTEPINT3_BITWIDTH          1
// OutEPInt4 bitfiled (RO) Reset=0
#define USB2DC_DAINT_OUTEPINT4_MASK              0x100000
#define USB2DC_DAINT_OUTEPINT4_SHIFT             20 
#define USB2DC_DAINT_OUTEPINT4_BIT               0x1
#define USB2DC_DAINT_OUTEPINT4_BITWIDTH          1
// OutEPInt5 bitfiled (RO) Reset=0
#define USB2DC_DAINT_OUTEPINT5_MASK              0x200000
#define USB2DC_DAINT_OUTEPINT5_SHIFT             21 
#define USB2DC_DAINT_OUTEPINT5_BIT               0x1
#define USB2DC_DAINT_OUTEPINT5_BITWIDTH          1
// OutEPInt6 bitfiled (RO) Reset=0
#define USB2DC_DAINT_OUTEPINT6_MASK              0x400000
#define USB2DC_DAINT_OUTEPINT6_SHIFT             22 
#define USB2DC_DAINT_OUTEPINT6_BIT               0x1
#define USB2DC_DAINT_OUTEPINT6_BITWIDTH          1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DAINT_RESERVED_MASK               0xFF800000
#define USB2DC_DAINT_RESERVED_SHIFT              23 
#define USB2DC_DAINT_RESERVED_BIT                0x1FF
#define USB2DC_DAINT_RESERVED_BITWIDTH           9
// DAINTMSK Register
#define USB2DC_DAINTMSK_OFS                      0x0000081C
// InEpMsk0 bitfiled (RW) Reset=0
#define USB2DC_DAINTMSK_INEPMSK0_MASK            0x1
#define USB2DC_DAINTMSK_INEPMSK0_SHIFT           0 
#define USB2DC_DAINTMSK_INEPMSK0_BIT             0x1
#define USB2DC_DAINTMSK_INEPMSK0_BITWIDTH        1
// InEpMsk1 bitfiled (RW) Reset=0
#define USB2DC_DAINTMSK_INEPMSK1_MASK            0x2
#define USB2DC_DAINTMSK_INEPMSK1_SHIFT           1 
#define USB2DC_DAINTMSK_INEPMSK1_BIT             0x1
#define USB2DC_DAINTMSK_INEPMSK1_BITWIDTH        1
// InEpMsk2 bitfiled (RW) Reset=0
#define USB2DC_DAINTMSK_INEPMSK2_MASK            0x4
#define USB2DC_DAINTMSK_INEPMSK2_SHIFT           2 
#define USB2DC_DAINTMSK_INEPMSK2_BIT             0x1
#define USB2DC_DAINTMSK_INEPMSK2_BITWIDTH        1
// InEpMsk3 bitfiled (RW) Reset=0
#define USB2DC_DAINTMSK_INEPMSK3_MASK            0x8
#define USB2DC_DAINTMSK_INEPMSK3_SHIFT           3 
#define USB2DC_DAINTMSK_INEPMSK3_BIT             0x1
#define USB2DC_DAINTMSK_INEPMSK3_BITWIDTH        1
// InEpMsk4 bitfiled (RW) Reset=0
#define USB2DC_DAINTMSK_INEPMSK4_MASK            0x10
#define USB2DC_DAINTMSK_INEPMSK4_SHIFT           4 
#define USB2DC_DAINTMSK_INEPMSK4_BIT             0x1
#define USB2DC_DAINTMSK_INEPMSK4_BITWIDTH        1
// InEpMsk5 bitfiled (RW) Reset=0
#define USB2DC_DAINTMSK_INEPMSK5_MASK            0x20
#define USB2DC_DAINTMSK_INEPMSK5_SHIFT           5 
#define USB2DC_DAINTMSK_INEPMSK5_BIT             0x1
#define USB2DC_DAINTMSK_INEPMSK5_BITWIDTH        1
// InEpMsk6 bitfiled (RW) Reset=0
#define USB2DC_DAINTMSK_INEPMSK6_MASK            0x40
#define USB2DC_DAINTMSK_INEPMSK6_SHIFT           6 
#define USB2DC_DAINTMSK_INEPMSK6_BIT             0x1
#define USB2DC_DAINTMSK_INEPMSK6_BITWIDTH        1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DAINTMSK_RESERVED2_MASK           0xFF80
#define USB2DC_DAINTMSK_RESERVED2_SHIFT          7 
#define USB2DC_DAINTMSK_RESERVED2_BIT            0x1FF
#define USB2DC_DAINTMSK_RESERVED2_BITWIDTH       9
// OutEPMsk0 bitfiled (RW) Reset=0
#define USB2DC_DAINTMSK_OUTEPMSK0_MASK           0x10000
#define USB2DC_DAINTMSK_OUTEPMSK0_SHIFT          16 
#define USB2DC_DAINTMSK_OUTEPMSK0_BIT            0x1
#define USB2DC_DAINTMSK_OUTEPMSK0_BITWIDTH       1
// OutEPMsk1 bitfiled (RW) Reset=0
#define USB2DC_DAINTMSK_OUTEPMSK1_MASK           0x20000
#define USB2DC_DAINTMSK_OUTEPMSK1_SHIFT          17 
#define USB2DC_DAINTMSK_OUTEPMSK1_BIT            0x1
#define USB2DC_DAINTMSK_OUTEPMSK1_BITWIDTH       1
// OutEPMsk2 bitfiled (RW) Reset=0
#define USB2DC_DAINTMSK_OUTEPMSK2_MASK           0x40000
#define USB2DC_DAINTMSK_OUTEPMSK2_SHIFT          18 
#define USB2DC_DAINTMSK_OUTEPMSK2_BIT            0x1
#define USB2DC_DAINTMSK_OUTEPMSK2_BITWIDTH       1
// OutEPMsk3 bitfiled (RW) Reset=0
#define USB2DC_DAINTMSK_OUTEPMSK3_MASK           0x80000
#define USB2DC_DAINTMSK_OUTEPMSK3_SHIFT          19 
#define USB2DC_DAINTMSK_OUTEPMSK3_BIT            0x1
#define USB2DC_DAINTMSK_OUTEPMSK3_BITWIDTH       1
// OutEPMsk4 bitfiled (RW) Reset=0
#define USB2DC_DAINTMSK_OUTEPMSK4_MASK           0x100000
#define USB2DC_DAINTMSK_OUTEPMSK4_SHIFT          20 
#define USB2DC_DAINTMSK_OUTEPMSK4_BIT            0x1
#define USB2DC_DAINTMSK_OUTEPMSK4_BITWIDTH       1
// OutEPMsk5 bitfiled (RW) Reset=0
#define USB2DC_DAINTMSK_OUTEPMSK5_MASK           0x200000
#define USB2DC_DAINTMSK_OUTEPMSK5_SHIFT          21 
#define USB2DC_DAINTMSK_OUTEPMSK5_BIT            0x1
#define USB2DC_DAINTMSK_OUTEPMSK5_BITWIDTH       1
// OutEPMsk6 bitfiled (RW) Reset=0
#define USB2DC_DAINTMSK_OUTEPMSK6_MASK           0x400000
#define USB2DC_DAINTMSK_OUTEPMSK6_SHIFT          22 
#define USB2DC_DAINTMSK_OUTEPMSK6_BIT            0x1
#define USB2DC_DAINTMSK_OUTEPMSK6_BITWIDTH       1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DAINTMSK_RESERVED_MASK            0xFF800000
#define USB2DC_DAINTMSK_RESERVED_SHIFT           23 
#define USB2DC_DAINTMSK_RESERVED_BIT             0x1FF
#define USB2DC_DAINTMSK_RESERVED_BITWIDTH        9
// DVBUSDIS Register
#define USB2DC_DVBUSDIS_OFS                      0x00000828
// DVBUSDis bitfiled (RW) Reset=101110001111
#define USB2DC_DVBUSDIS_DVBUSDIS_MASK            0xFFFF
#define USB2DC_DVBUSDIS_DVBUSDIS_SHIFT           0 
#define USB2DC_DVBUSDIS_DVBUSDIS_BIT             0xFFFF
#define USB2DC_DVBUSDIS_DVBUSDIS_BITWIDTH        16
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DVBUSDIS_RESERVED_MASK            0xFFFF0000
#define USB2DC_DVBUSDIS_RESERVED_SHIFT           16 
#define USB2DC_DVBUSDIS_RESERVED_BIT             0xFFFF
#define USB2DC_DVBUSDIS_RESERVED_BITWIDTH        16
// DVBUSPULSE Register
#define USB2DC_DVBUSPULSE_OFS                    0x0000082C
// DVBUSPulse bitfiled (RW) Reset=1011000110
#define USB2DC_DVBUSPULSE_DVBUSPULSE_MASK        0xFFF
#define USB2DC_DVBUSPULSE_DVBUSPULSE_SHIFT       0 
#define USB2DC_DVBUSPULSE_DVBUSPULSE_BIT         0xFFF
#define USB2DC_DVBUSPULSE_DVBUSPULSE_BITWIDTH    12
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DVBUSPULSE_RESERVED_MASK          0xFFFFF000
#define USB2DC_DVBUSPULSE_RESERVED_SHIFT         12 
#define USB2DC_DVBUSPULSE_RESERVED_BIT           0xFFFFF
#define USB2DC_DVBUSPULSE_RESERVED_BITWIDTH      20
// DTHRCTL Register
#define USB2DC_DTHRCTL_OFS                       0x00000830
// NonISOThrEn bitfiled (RW) Reset=0
#define USB2DC_DTHRCTL_NONISOTHREN_MASK          0x1
#define USB2DC_DTHRCTL_NONISOTHREN_SHIFT         0 
#define USB2DC_DTHRCTL_NONISOTHREN_BIT           0x1
#define USB2DC_DTHRCTL_NONISOTHREN_BITWIDTH      1
// ISOThrEn bitfiled (RW) Reset=0
#define USB2DC_DTHRCTL_ISOTHREN_MASK             0x2
#define USB2DC_DTHRCTL_ISOTHREN_SHIFT            1 
#define USB2DC_DTHRCTL_ISOTHREN_BIT              0x1
#define USB2DC_DTHRCTL_ISOTHREN_BITWIDTH         1
// TxThrLen bitfiled (RW) Reset=1000
#define USB2DC_DTHRCTL_TXTHRLEN_MASK             0x7FC
#define USB2DC_DTHRCTL_TXTHRLEN_SHIFT            2 
#define USB2DC_DTHRCTL_TXTHRLEN_BIT              0x1FF
#define USB2DC_DTHRCTL_TXTHRLEN_BITWIDTH         9
// AHBThrRatio bitfiled (RW) Reset=0
#define USB2DC_DTHRCTL_AHBTHRRATIO_MASK          0x1800
#define USB2DC_DTHRCTL_AHBTHRRATIO_SHIFT         11 
#define USB2DC_DTHRCTL_AHBTHRRATIO_BIT           0x3
#define USB2DC_DTHRCTL_AHBTHRRATIO_BITWIDTH      2
// Reserved3 bitfiled (RO) Reset=0
#define USB2DC_DTHRCTL_RESERVED3_MASK            0xE000
#define USB2DC_DTHRCTL_RESERVED3_SHIFT           13 
#define USB2DC_DTHRCTL_RESERVED3_BIT             0x7
#define USB2DC_DTHRCTL_RESERVED3_BITWIDTH        3
// RxThrEn bitfiled (RW) Reset=0
#define USB2DC_DTHRCTL_RXTHREN_MASK              0x10000
#define USB2DC_DTHRCTL_RXTHREN_SHIFT             16 
#define USB2DC_DTHRCTL_RXTHREN_BIT               0x1
#define USB2DC_DTHRCTL_RXTHREN_BITWIDTH          1
// RxThrLen bitfiled (RW) Reset=1000
#define USB2DC_DTHRCTL_RXTHRLEN_MASK             0x3FE0000
#define USB2DC_DTHRCTL_RXTHRLEN_SHIFT            17 
#define USB2DC_DTHRCTL_RXTHRLEN_BIT              0x1FF
#define USB2DC_DTHRCTL_RXTHRLEN_BITWIDTH         9
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DTHRCTL_RESERVED2_MASK            0x4000000
#define USB2DC_DTHRCTL_RESERVED2_SHIFT           26 
#define USB2DC_DTHRCTL_RESERVED2_BIT             0x1
#define USB2DC_DTHRCTL_RESERVED2_BITWIDTH        1
// ArbPrkEn bitfiled (RW) Reset=1
#define USB2DC_DTHRCTL_ARBPRKEN_MASK             0x8000000
#define USB2DC_DTHRCTL_ARBPRKEN_SHIFT            27 
#define USB2DC_DTHRCTL_ARBPRKEN_BIT              0x1
#define USB2DC_DTHRCTL_ARBPRKEN_BITWIDTH         1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DTHRCTL_RESERVED_MASK             0xF0000000
#define USB2DC_DTHRCTL_RESERVED_SHIFT            28 
#define USB2DC_DTHRCTL_RESERVED_BIT              0xF
#define USB2DC_DTHRCTL_RESERVED_BITWIDTH         4
// DIEPEMPMSK Register
#define USB2DC_DIEPEMPMSK_OFS                    0x00000834
// InEpTxfEmpMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEMPMSK_INEPTXFEMPMSK_MASK     0xFFFF
#define USB2DC_DIEPEMPMSK_INEPTXFEMPMSK_SHIFT    0 
#define USB2DC_DIEPEMPMSK_INEPTXFEMPMSK_BIT      0xFFFF
#define USB2DC_DIEPEMPMSK_INEPTXFEMPMSK_BITWIDTH 16
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPEMPMSK_RESERVED_MASK          0xFFFF0000
#define USB2DC_DIEPEMPMSK_RESERVED_SHIFT         16 
#define USB2DC_DIEPEMPMSK_RESERVED_BIT           0xFFFF
#define USB2DC_DIEPEMPMSK_RESERVED_BITWIDTH      16
// DEACHINT Register
#define USB2DC_DEACHINT_OFS                      0x00000838
// EchInEpInt bitfiled (RO) Reset=0
#define USB2DC_DEACHINT_ECHINEPINT_MASK          0xFFFF
#define USB2DC_DEACHINT_ECHINEPINT_SHIFT         0 
#define USB2DC_DEACHINT_ECHINEPINT_BIT           0xFFFF
#define USB2DC_DEACHINT_ECHINEPINT_BITWIDTH      16
// EchOutEPInt bitfiled (RO) Reset=0
#define USB2DC_DEACHINT_ECHOUTEPINT_MASK         0xFFFF0000
#define USB2DC_DEACHINT_ECHOUTEPINT_SHIFT        16 
#define USB2DC_DEACHINT_ECHOUTEPINT_BIT          0xFFFF
#define USB2DC_DEACHINT_ECHOUTEPINT_BITWIDTH     16
// DEACHINTMSK Register
#define USB2DC_DEACHINTMSK_OFS                   0x0000083C
// EchInEpMsk bitfiled (RW) Reset=0
#define USB2DC_DEACHINTMSK_ECHINEPMSK_MASK       0xFFFF
#define USB2DC_DEACHINTMSK_ECHINEPMSK_SHIFT      0 
#define USB2DC_DEACHINTMSK_ECHINEPMSK_BIT        0xFFFF
#define USB2DC_DEACHINTMSK_ECHINEPMSK_BITWIDTH   16
// EchOutEpMsk bitfiled (RW) Reset=0
#define USB2DC_DEACHINTMSK_ECHOUTEPMSK_MASK      0xFFFF0000
#define USB2DC_DEACHINTMSK_ECHOUTEPMSK_SHIFT     16 
#define USB2DC_DEACHINTMSK_ECHOUTEPMSK_BIT       0xFFFF
#define USB2DC_DEACHINTMSK_ECHOUTEPMSK_BITWIDTH  16
// DIEPEACHMSK0 Register
#define USB2DC_DIEPEACHMSK0_OFS                  0x00000840
// XferComplMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK0_XFERCOMPLMSK_MASK    0x1
#define USB2DC_DIEPEACHMSK0_XFERCOMPLMSK_SHIFT   0 
#define USB2DC_DIEPEACHMSK0_XFERCOMPLMSK_BIT     0x1
#define USB2DC_DIEPEACHMSK0_XFERCOMPLMSK_BITWIDTH 1
// EPDisbldMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK0_EPDISBLDMSK_MASK     0x2
#define USB2DC_DIEPEACHMSK0_EPDISBLDMSK_SHIFT    1 
#define USB2DC_DIEPEACHMSK0_EPDISBLDMSK_BIT      0x1
#define USB2DC_DIEPEACHMSK0_EPDISBLDMSK_BITWIDTH 1
// AHBErrMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK0_AHBERRMSK_MASK       0x4
#define USB2DC_DIEPEACHMSK0_AHBERRMSK_SHIFT      2 
#define USB2DC_DIEPEACHMSK0_AHBERRMSK_BIT        0x1
#define USB2DC_DIEPEACHMSK0_AHBERRMSK_BITWIDTH   1
// TimeOUTMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK0_TIMEOUTMSK_MASK      0x8
#define USB2DC_DIEPEACHMSK0_TIMEOUTMSK_SHIFT     3 
#define USB2DC_DIEPEACHMSK0_TIMEOUTMSK_BIT       0x1
#define USB2DC_DIEPEACHMSK0_TIMEOUTMSK_BITWIDTH  1
// INTknTXFEmpMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK0_INTKNTXFEMPMSK_MASK  0x10
#define USB2DC_DIEPEACHMSK0_INTKNTXFEMPMSK_SHIFT 4 
#define USB2DC_DIEPEACHMSK0_INTKNTXFEMPMSK_BIT   0x1
#define USB2DC_DIEPEACHMSK0_INTKNTXFEMPMSK_BITWIDTH 1
// INTknEPMisMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK0_INTKNEPMISMSK_MASK   0x20
#define USB2DC_DIEPEACHMSK0_INTKNEPMISMSK_SHIFT  5 
#define USB2DC_DIEPEACHMSK0_INTKNEPMISMSK_BIT    0x1
#define USB2DC_DIEPEACHMSK0_INTKNEPMISMSK_BITWIDTH 1
// INEPNakEffMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK0_INEPNAKEFFMSK_MASK   0x40
#define USB2DC_DIEPEACHMSK0_INEPNAKEFFMSK_SHIFT  6 
#define USB2DC_DIEPEACHMSK0_INEPNAKEFFMSK_BIT    0x1
#define USB2DC_DIEPEACHMSK0_INEPNAKEFFMSK_BITWIDTH 1
// Reserved3 bitfiled (RO) Reset=0
#define USB2DC_DIEPEACHMSK0_RESERVED3_MASK       0x80
#define USB2DC_DIEPEACHMSK0_RESERVED3_SHIFT      7 
#define USB2DC_DIEPEACHMSK0_RESERVED3_BIT        0x1
#define USB2DC_DIEPEACHMSK0_RESERVED3_BITWIDTH   1
// TxfifoUndrnMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK0_TXFIFOUNDRNMSK_MASK  0x100
#define USB2DC_DIEPEACHMSK0_TXFIFOUNDRNMSK_SHIFT 8 
#define USB2DC_DIEPEACHMSK0_TXFIFOUNDRNMSK_BIT   0x1
#define USB2DC_DIEPEACHMSK0_TXFIFOUNDRNMSK_BITWIDTH 1
// BNAInIntrMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK0_BNAININTRMSK_MASK    0x200
#define USB2DC_DIEPEACHMSK0_BNAININTRMSK_SHIFT   9 
#define USB2DC_DIEPEACHMSK0_BNAININTRMSK_BIT     0x1
#define USB2DC_DIEPEACHMSK0_BNAININTRMSK_BITWIDTH 1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DIEPEACHMSK0_RESERVED2_MASK       0x1C00
#define USB2DC_DIEPEACHMSK0_RESERVED2_SHIFT      10 
#define USB2DC_DIEPEACHMSK0_RESERVED2_BIT        0x7
#define USB2DC_DIEPEACHMSK0_RESERVED2_BITWIDTH   3
// NAKMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK0_NAKMSK_MASK          0x2000
#define USB2DC_DIEPEACHMSK0_NAKMSK_SHIFT         13 
#define USB2DC_DIEPEACHMSK0_NAKMSK_BIT           0x1
#define USB2DC_DIEPEACHMSK0_NAKMSK_BITWIDTH      1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPEACHMSK0_RESERVED_MASK        0xFFFFC000
#define USB2DC_DIEPEACHMSK0_RESERVED_SHIFT       14 
#define USB2DC_DIEPEACHMSK0_RESERVED_BIT         0x3FFFF
#define USB2DC_DIEPEACHMSK0_RESERVED_BITWIDTH    18
// DIEPEACHMSK1 Register
#define USB2DC_DIEPEACHMSK1_OFS                  0x00000844
// XferComplMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK1_XFERCOMPLMSK_MASK    0x1
#define USB2DC_DIEPEACHMSK1_XFERCOMPLMSK_SHIFT   0 
#define USB2DC_DIEPEACHMSK1_XFERCOMPLMSK_BIT     0x1
#define USB2DC_DIEPEACHMSK1_XFERCOMPLMSK_BITWIDTH 1
// EPDisbldMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK1_EPDISBLDMSK_MASK     0x2
#define USB2DC_DIEPEACHMSK1_EPDISBLDMSK_SHIFT    1 
#define USB2DC_DIEPEACHMSK1_EPDISBLDMSK_BIT      0x1
#define USB2DC_DIEPEACHMSK1_EPDISBLDMSK_BITWIDTH 1
// AHBErrMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK1_AHBERRMSK_MASK       0x4
#define USB2DC_DIEPEACHMSK1_AHBERRMSK_SHIFT      2 
#define USB2DC_DIEPEACHMSK1_AHBERRMSK_BIT        0x1
#define USB2DC_DIEPEACHMSK1_AHBERRMSK_BITWIDTH   1
// TimeOUTMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK1_TIMEOUTMSK_MASK      0x8
#define USB2DC_DIEPEACHMSK1_TIMEOUTMSK_SHIFT     3 
#define USB2DC_DIEPEACHMSK1_TIMEOUTMSK_BIT       0x1
#define USB2DC_DIEPEACHMSK1_TIMEOUTMSK_BITWIDTH  1
// INTknTXFEmpMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK1_INTKNTXFEMPMSK_MASK  0x10
#define USB2DC_DIEPEACHMSK1_INTKNTXFEMPMSK_SHIFT 4 
#define USB2DC_DIEPEACHMSK1_INTKNTXFEMPMSK_BIT   0x1
#define USB2DC_DIEPEACHMSK1_INTKNTXFEMPMSK_BITWIDTH 1
// INTknEPMisMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK1_INTKNEPMISMSK_MASK   0x20
#define USB2DC_DIEPEACHMSK1_INTKNEPMISMSK_SHIFT  5 
#define USB2DC_DIEPEACHMSK1_INTKNEPMISMSK_BIT    0x1
#define USB2DC_DIEPEACHMSK1_INTKNEPMISMSK_BITWIDTH 1
// INEPNakEffMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK1_INEPNAKEFFMSK_MASK   0x40
#define USB2DC_DIEPEACHMSK1_INEPNAKEFFMSK_SHIFT  6 
#define USB2DC_DIEPEACHMSK1_INEPNAKEFFMSK_BIT    0x1
#define USB2DC_DIEPEACHMSK1_INEPNAKEFFMSK_BITWIDTH 1
// Reserved3 bitfiled (RO) Reset=0
#define USB2DC_DIEPEACHMSK1_RESERVED3_MASK       0x80
#define USB2DC_DIEPEACHMSK1_RESERVED3_SHIFT      7 
#define USB2DC_DIEPEACHMSK1_RESERVED3_BIT        0x1
#define USB2DC_DIEPEACHMSK1_RESERVED3_BITWIDTH   1
// TxfifoUndrnMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK1_TXFIFOUNDRNMSK_MASK  0x100
#define USB2DC_DIEPEACHMSK1_TXFIFOUNDRNMSK_SHIFT 8 
#define USB2DC_DIEPEACHMSK1_TXFIFOUNDRNMSK_BIT   0x1
#define USB2DC_DIEPEACHMSK1_TXFIFOUNDRNMSK_BITWIDTH 1
// BNAInIntrMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK1_BNAININTRMSK_MASK    0x200
#define USB2DC_DIEPEACHMSK1_BNAININTRMSK_SHIFT   9 
#define USB2DC_DIEPEACHMSK1_BNAININTRMSK_BIT     0x1
#define USB2DC_DIEPEACHMSK1_BNAININTRMSK_BITWIDTH 1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DIEPEACHMSK1_RESERVED2_MASK       0x1C00
#define USB2DC_DIEPEACHMSK1_RESERVED2_SHIFT      10 
#define USB2DC_DIEPEACHMSK1_RESERVED2_BIT        0x7
#define USB2DC_DIEPEACHMSK1_RESERVED2_BITWIDTH   3
// NAKMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK1_NAKMSK_MASK          0x2000
#define USB2DC_DIEPEACHMSK1_NAKMSK_SHIFT         13 
#define USB2DC_DIEPEACHMSK1_NAKMSK_BIT           0x1
#define USB2DC_DIEPEACHMSK1_NAKMSK_BITWIDTH      1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPEACHMSK1_RESERVED_MASK        0xFFFFC000
#define USB2DC_DIEPEACHMSK1_RESERVED_SHIFT       14 
#define USB2DC_DIEPEACHMSK1_RESERVED_BIT         0x3FFFF
#define USB2DC_DIEPEACHMSK1_RESERVED_BITWIDTH    18
// DIEPEACHMSK2 Register
#define USB2DC_DIEPEACHMSK2_OFS                  0x00000848
// XferComplMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK2_XFERCOMPLMSK_MASK    0x1
#define USB2DC_DIEPEACHMSK2_XFERCOMPLMSK_SHIFT   0 
#define USB2DC_DIEPEACHMSK2_XFERCOMPLMSK_BIT     0x1
#define USB2DC_DIEPEACHMSK2_XFERCOMPLMSK_BITWIDTH 1
// EPDisbldMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK2_EPDISBLDMSK_MASK     0x2
#define USB2DC_DIEPEACHMSK2_EPDISBLDMSK_SHIFT    1 
#define USB2DC_DIEPEACHMSK2_EPDISBLDMSK_BIT      0x1
#define USB2DC_DIEPEACHMSK2_EPDISBLDMSK_BITWIDTH 1
// AHBErrMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK2_AHBERRMSK_MASK       0x4
#define USB2DC_DIEPEACHMSK2_AHBERRMSK_SHIFT      2 
#define USB2DC_DIEPEACHMSK2_AHBERRMSK_BIT        0x1
#define USB2DC_DIEPEACHMSK2_AHBERRMSK_BITWIDTH   1
// TimeOUTMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK2_TIMEOUTMSK_MASK      0x8
#define USB2DC_DIEPEACHMSK2_TIMEOUTMSK_SHIFT     3 
#define USB2DC_DIEPEACHMSK2_TIMEOUTMSK_BIT       0x1
#define USB2DC_DIEPEACHMSK2_TIMEOUTMSK_BITWIDTH  1
// INTknTXFEmpMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK2_INTKNTXFEMPMSK_MASK  0x10
#define USB2DC_DIEPEACHMSK2_INTKNTXFEMPMSK_SHIFT 4 
#define USB2DC_DIEPEACHMSK2_INTKNTXFEMPMSK_BIT   0x1
#define USB2DC_DIEPEACHMSK2_INTKNTXFEMPMSK_BITWIDTH 1
// INTknEPMisMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK2_INTKNEPMISMSK_MASK   0x20
#define USB2DC_DIEPEACHMSK2_INTKNEPMISMSK_SHIFT  5 
#define USB2DC_DIEPEACHMSK2_INTKNEPMISMSK_BIT    0x1
#define USB2DC_DIEPEACHMSK2_INTKNEPMISMSK_BITWIDTH 1
// INEPNakEffMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK2_INEPNAKEFFMSK_MASK   0x40
#define USB2DC_DIEPEACHMSK2_INEPNAKEFFMSK_SHIFT  6 
#define USB2DC_DIEPEACHMSK2_INEPNAKEFFMSK_BIT    0x1
#define USB2DC_DIEPEACHMSK2_INEPNAKEFFMSK_BITWIDTH 1
// Reserved3 bitfiled (RO) Reset=0
#define USB2DC_DIEPEACHMSK2_RESERVED3_MASK       0x80
#define USB2DC_DIEPEACHMSK2_RESERVED3_SHIFT      7 
#define USB2DC_DIEPEACHMSK2_RESERVED3_BIT        0x1
#define USB2DC_DIEPEACHMSK2_RESERVED3_BITWIDTH   1
// TxfifoUndrnMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK2_TXFIFOUNDRNMSK_MASK  0x100
#define USB2DC_DIEPEACHMSK2_TXFIFOUNDRNMSK_SHIFT 8 
#define USB2DC_DIEPEACHMSK2_TXFIFOUNDRNMSK_BIT   0x1
#define USB2DC_DIEPEACHMSK2_TXFIFOUNDRNMSK_BITWIDTH 1
// BNAInIntrMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK2_BNAININTRMSK_MASK    0x200
#define USB2DC_DIEPEACHMSK2_BNAININTRMSK_SHIFT   9 
#define USB2DC_DIEPEACHMSK2_BNAININTRMSK_BIT     0x1
#define USB2DC_DIEPEACHMSK2_BNAININTRMSK_BITWIDTH 1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DIEPEACHMSK2_RESERVED2_MASK       0x1C00
#define USB2DC_DIEPEACHMSK2_RESERVED2_SHIFT      10 
#define USB2DC_DIEPEACHMSK2_RESERVED2_BIT        0x7
#define USB2DC_DIEPEACHMSK2_RESERVED2_BITWIDTH   3
// NAKMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK2_NAKMSK_MASK          0x2000
#define USB2DC_DIEPEACHMSK2_NAKMSK_SHIFT         13 
#define USB2DC_DIEPEACHMSK2_NAKMSK_BIT           0x1
#define USB2DC_DIEPEACHMSK2_NAKMSK_BITWIDTH      1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPEACHMSK2_RESERVED_MASK        0xFFFFC000
#define USB2DC_DIEPEACHMSK2_RESERVED_SHIFT       14 
#define USB2DC_DIEPEACHMSK2_RESERVED_BIT         0x3FFFF
#define USB2DC_DIEPEACHMSK2_RESERVED_BITWIDTH    18
// DIEPEACHMSK3 Register
#define USB2DC_DIEPEACHMSK3_OFS                  0x0000084C
// XferComplMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK3_XFERCOMPLMSK_MASK    0x1
#define USB2DC_DIEPEACHMSK3_XFERCOMPLMSK_SHIFT   0 
#define USB2DC_DIEPEACHMSK3_XFERCOMPLMSK_BIT     0x1
#define USB2DC_DIEPEACHMSK3_XFERCOMPLMSK_BITWIDTH 1
// EPDisbldMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK3_EPDISBLDMSK_MASK     0x2
#define USB2DC_DIEPEACHMSK3_EPDISBLDMSK_SHIFT    1 
#define USB2DC_DIEPEACHMSK3_EPDISBLDMSK_BIT      0x1
#define USB2DC_DIEPEACHMSK3_EPDISBLDMSK_BITWIDTH 1
// AHBErrMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK3_AHBERRMSK_MASK       0x4
#define USB2DC_DIEPEACHMSK3_AHBERRMSK_SHIFT      2 
#define USB2DC_DIEPEACHMSK3_AHBERRMSK_BIT        0x1
#define USB2DC_DIEPEACHMSK3_AHBERRMSK_BITWIDTH   1
// TimeOUTMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK3_TIMEOUTMSK_MASK      0x8
#define USB2DC_DIEPEACHMSK3_TIMEOUTMSK_SHIFT     3 
#define USB2DC_DIEPEACHMSK3_TIMEOUTMSK_BIT       0x1
#define USB2DC_DIEPEACHMSK3_TIMEOUTMSK_BITWIDTH  1
// INTknTXFEmpMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK3_INTKNTXFEMPMSK_MASK  0x10
#define USB2DC_DIEPEACHMSK3_INTKNTXFEMPMSK_SHIFT 4 
#define USB2DC_DIEPEACHMSK3_INTKNTXFEMPMSK_BIT   0x1
#define USB2DC_DIEPEACHMSK3_INTKNTXFEMPMSK_BITWIDTH 1
// INTknEPMisMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK3_INTKNEPMISMSK_MASK   0x20
#define USB2DC_DIEPEACHMSK3_INTKNEPMISMSK_SHIFT  5 
#define USB2DC_DIEPEACHMSK3_INTKNEPMISMSK_BIT    0x1
#define USB2DC_DIEPEACHMSK3_INTKNEPMISMSK_BITWIDTH 1
// INEPNakEffMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK3_INEPNAKEFFMSK_MASK   0x40
#define USB2DC_DIEPEACHMSK3_INEPNAKEFFMSK_SHIFT  6 
#define USB2DC_DIEPEACHMSK3_INEPNAKEFFMSK_BIT    0x1
#define USB2DC_DIEPEACHMSK3_INEPNAKEFFMSK_BITWIDTH 1
// Reserved3 bitfiled (RO) Reset=0
#define USB2DC_DIEPEACHMSK3_RESERVED3_MASK       0x80
#define USB2DC_DIEPEACHMSK3_RESERVED3_SHIFT      7 
#define USB2DC_DIEPEACHMSK3_RESERVED3_BIT        0x1
#define USB2DC_DIEPEACHMSK3_RESERVED3_BITWIDTH   1
// TxfifoUndrnMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK3_TXFIFOUNDRNMSK_MASK  0x100
#define USB2DC_DIEPEACHMSK3_TXFIFOUNDRNMSK_SHIFT 8 
#define USB2DC_DIEPEACHMSK3_TXFIFOUNDRNMSK_BIT   0x1
#define USB2DC_DIEPEACHMSK3_TXFIFOUNDRNMSK_BITWIDTH 1
// BNAInIntrMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK3_BNAININTRMSK_MASK    0x200
#define USB2DC_DIEPEACHMSK3_BNAININTRMSK_SHIFT   9 
#define USB2DC_DIEPEACHMSK3_BNAININTRMSK_BIT     0x1
#define USB2DC_DIEPEACHMSK3_BNAININTRMSK_BITWIDTH 1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DIEPEACHMSK3_RESERVED2_MASK       0x1C00
#define USB2DC_DIEPEACHMSK3_RESERVED2_SHIFT      10 
#define USB2DC_DIEPEACHMSK3_RESERVED2_BIT        0x7
#define USB2DC_DIEPEACHMSK3_RESERVED2_BITWIDTH   3
// NAKMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK3_NAKMSK_MASK          0x2000
#define USB2DC_DIEPEACHMSK3_NAKMSK_SHIFT         13 
#define USB2DC_DIEPEACHMSK3_NAKMSK_BIT           0x1
#define USB2DC_DIEPEACHMSK3_NAKMSK_BITWIDTH      1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPEACHMSK3_RESERVED_MASK        0xFFFFC000
#define USB2DC_DIEPEACHMSK3_RESERVED_SHIFT       14 
#define USB2DC_DIEPEACHMSK3_RESERVED_BIT         0x3FFFF
#define USB2DC_DIEPEACHMSK3_RESERVED_BITWIDTH    18
// DIEPEACHMSK4 Register
#define USB2DC_DIEPEACHMSK4_OFS                  0x00000850
// XferComplMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK4_XFERCOMPLMSK_MASK    0x1
#define USB2DC_DIEPEACHMSK4_XFERCOMPLMSK_SHIFT   0 
#define USB2DC_DIEPEACHMSK4_XFERCOMPLMSK_BIT     0x1
#define USB2DC_DIEPEACHMSK4_XFERCOMPLMSK_BITWIDTH 1
// EPDisbldMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK4_EPDISBLDMSK_MASK     0x2
#define USB2DC_DIEPEACHMSK4_EPDISBLDMSK_SHIFT    1 
#define USB2DC_DIEPEACHMSK4_EPDISBLDMSK_BIT      0x1
#define USB2DC_DIEPEACHMSK4_EPDISBLDMSK_BITWIDTH 1
// AHBErrMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK4_AHBERRMSK_MASK       0x4
#define USB2DC_DIEPEACHMSK4_AHBERRMSK_SHIFT      2 
#define USB2DC_DIEPEACHMSK4_AHBERRMSK_BIT        0x1
#define USB2DC_DIEPEACHMSK4_AHBERRMSK_BITWIDTH   1
// TimeOUTMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK4_TIMEOUTMSK_MASK      0x8
#define USB2DC_DIEPEACHMSK4_TIMEOUTMSK_SHIFT     3 
#define USB2DC_DIEPEACHMSK4_TIMEOUTMSK_BIT       0x1
#define USB2DC_DIEPEACHMSK4_TIMEOUTMSK_BITWIDTH  1
// INTknTXFEmpMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK4_INTKNTXFEMPMSK_MASK  0x10
#define USB2DC_DIEPEACHMSK4_INTKNTXFEMPMSK_SHIFT 4 
#define USB2DC_DIEPEACHMSK4_INTKNTXFEMPMSK_BIT   0x1
#define USB2DC_DIEPEACHMSK4_INTKNTXFEMPMSK_BITWIDTH 1
// INTknEPMisMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK4_INTKNEPMISMSK_MASK   0x20
#define USB2DC_DIEPEACHMSK4_INTKNEPMISMSK_SHIFT  5 
#define USB2DC_DIEPEACHMSK4_INTKNEPMISMSK_BIT    0x1
#define USB2DC_DIEPEACHMSK4_INTKNEPMISMSK_BITWIDTH 1
// INEPNakEffMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK4_INEPNAKEFFMSK_MASK   0x40
#define USB2DC_DIEPEACHMSK4_INEPNAKEFFMSK_SHIFT  6 
#define USB2DC_DIEPEACHMSK4_INEPNAKEFFMSK_BIT    0x1
#define USB2DC_DIEPEACHMSK4_INEPNAKEFFMSK_BITWIDTH 1
// Reserved3 bitfiled (RO) Reset=0
#define USB2DC_DIEPEACHMSK4_RESERVED3_MASK       0x80
#define USB2DC_DIEPEACHMSK4_RESERVED3_SHIFT      7 
#define USB2DC_DIEPEACHMSK4_RESERVED3_BIT        0x1
#define USB2DC_DIEPEACHMSK4_RESERVED3_BITWIDTH   1
// TxfifoUndrnMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK4_TXFIFOUNDRNMSK_MASK  0x100
#define USB2DC_DIEPEACHMSK4_TXFIFOUNDRNMSK_SHIFT 8 
#define USB2DC_DIEPEACHMSK4_TXFIFOUNDRNMSK_BIT   0x1
#define USB2DC_DIEPEACHMSK4_TXFIFOUNDRNMSK_BITWIDTH 1
// BNAInIntrMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK4_BNAININTRMSK_MASK    0x200
#define USB2DC_DIEPEACHMSK4_BNAININTRMSK_SHIFT   9 
#define USB2DC_DIEPEACHMSK4_BNAININTRMSK_BIT     0x1
#define USB2DC_DIEPEACHMSK4_BNAININTRMSK_BITWIDTH 1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DIEPEACHMSK4_RESERVED2_MASK       0x1C00
#define USB2DC_DIEPEACHMSK4_RESERVED2_SHIFT      10 
#define USB2DC_DIEPEACHMSK4_RESERVED2_BIT        0x7
#define USB2DC_DIEPEACHMSK4_RESERVED2_BITWIDTH   3
// NAKMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK4_NAKMSK_MASK          0x2000
#define USB2DC_DIEPEACHMSK4_NAKMSK_SHIFT         13 
#define USB2DC_DIEPEACHMSK4_NAKMSK_BIT           0x1
#define USB2DC_DIEPEACHMSK4_NAKMSK_BITWIDTH      1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPEACHMSK4_RESERVED_MASK        0xFFFFC000
#define USB2DC_DIEPEACHMSK4_RESERVED_SHIFT       14 
#define USB2DC_DIEPEACHMSK4_RESERVED_BIT         0x3FFFF
#define USB2DC_DIEPEACHMSK4_RESERVED_BITWIDTH    18
// DIEPEACHMSK5 Register
#define USB2DC_DIEPEACHMSK5_OFS                  0x00000854
// XferComplMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK5_XFERCOMPLMSK_MASK    0x1
#define USB2DC_DIEPEACHMSK5_XFERCOMPLMSK_SHIFT   0 
#define USB2DC_DIEPEACHMSK5_XFERCOMPLMSK_BIT     0x1
#define USB2DC_DIEPEACHMSK5_XFERCOMPLMSK_BITWIDTH 1
// EPDisbldMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK5_EPDISBLDMSK_MASK     0x2
#define USB2DC_DIEPEACHMSK5_EPDISBLDMSK_SHIFT    1 
#define USB2DC_DIEPEACHMSK5_EPDISBLDMSK_BIT      0x1
#define USB2DC_DIEPEACHMSK5_EPDISBLDMSK_BITWIDTH 1
// AHBErrMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK5_AHBERRMSK_MASK       0x4
#define USB2DC_DIEPEACHMSK5_AHBERRMSK_SHIFT      2 
#define USB2DC_DIEPEACHMSK5_AHBERRMSK_BIT        0x1
#define USB2DC_DIEPEACHMSK5_AHBERRMSK_BITWIDTH   1
// TimeOUTMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK5_TIMEOUTMSK_MASK      0x8
#define USB2DC_DIEPEACHMSK5_TIMEOUTMSK_SHIFT     3 
#define USB2DC_DIEPEACHMSK5_TIMEOUTMSK_BIT       0x1
#define USB2DC_DIEPEACHMSK5_TIMEOUTMSK_BITWIDTH  1
// INTknTXFEmpMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK5_INTKNTXFEMPMSK_MASK  0x10
#define USB2DC_DIEPEACHMSK5_INTKNTXFEMPMSK_SHIFT 4 
#define USB2DC_DIEPEACHMSK5_INTKNTXFEMPMSK_BIT   0x1
#define USB2DC_DIEPEACHMSK5_INTKNTXFEMPMSK_BITWIDTH 1
// INTknEPMisMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK5_INTKNEPMISMSK_MASK   0x20
#define USB2DC_DIEPEACHMSK5_INTKNEPMISMSK_SHIFT  5 
#define USB2DC_DIEPEACHMSK5_INTKNEPMISMSK_BIT    0x1
#define USB2DC_DIEPEACHMSK5_INTKNEPMISMSK_BITWIDTH 1
// INEPNakEffMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK5_INEPNAKEFFMSK_MASK   0x40
#define USB2DC_DIEPEACHMSK5_INEPNAKEFFMSK_SHIFT  6 
#define USB2DC_DIEPEACHMSK5_INEPNAKEFFMSK_BIT    0x1
#define USB2DC_DIEPEACHMSK5_INEPNAKEFFMSK_BITWIDTH 1
// Reserved3 bitfiled (RO) Reset=0
#define USB2DC_DIEPEACHMSK5_RESERVED3_MASK       0x80
#define USB2DC_DIEPEACHMSK5_RESERVED3_SHIFT      7 
#define USB2DC_DIEPEACHMSK5_RESERVED3_BIT        0x1
#define USB2DC_DIEPEACHMSK5_RESERVED3_BITWIDTH   1
// TxfifoUndrnMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK5_TXFIFOUNDRNMSK_MASK  0x100
#define USB2DC_DIEPEACHMSK5_TXFIFOUNDRNMSK_SHIFT 8 
#define USB2DC_DIEPEACHMSK5_TXFIFOUNDRNMSK_BIT   0x1
#define USB2DC_DIEPEACHMSK5_TXFIFOUNDRNMSK_BITWIDTH 1
// BNAInIntrMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK5_BNAININTRMSK_MASK    0x200
#define USB2DC_DIEPEACHMSK5_BNAININTRMSK_SHIFT   9 
#define USB2DC_DIEPEACHMSK5_BNAININTRMSK_BIT     0x1
#define USB2DC_DIEPEACHMSK5_BNAININTRMSK_BITWIDTH 1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DIEPEACHMSK5_RESERVED2_MASK       0x1C00
#define USB2DC_DIEPEACHMSK5_RESERVED2_SHIFT      10 
#define USB2DC_DIEPEACHMSK5_RESERVED2_BIT        0x7
#define USB2DC_DIEPEACHMSK5_RESERVED2_BITWIDTH   3
// NAKMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK5_NAKMSK_MASK          0x2000
#define USB2DC_DIEPEACHMSK5_NAKMSK_SHIFT         13 
#define USB2DC_DIEPEACHMSK5_NAKMSK_BIT           0x1
#define USB2DC_DIEPEACHMSK5_NAKMSK_BITWIDTH      1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPEACHMSK5_RESERVED_MASK        0xFFFFC000
#define USB2DC_DIEPEACHMSK5_RESERVED_SHIFT       14 
#define USB2DC_DIEPEACHMSK5_RESERVED_BIT         0x3FFFF
#define USB2DC_DIEPEACHMSK5_RESERVED_BITWIDTH    18
// DIEPEACHMSK6 Register
#define USB2DC_DIEPEACHMSK6_OFS                  0x00000858
// XferComplMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK6_XFERCOMPLMSK_MASK    0x1
#define USB2DC_DIEPEACHMSK6_XFERCOMPLMSK_SHIFT   0 
#define USB2DC_DIEPEACHMSK6_XFERCOMPLMSK_BIT     0x1
#define USB2DC_DIEPEACHMSK6_XFERCOMPLMSK_BITWIDTH 1
// EPDisbldMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK6_EPDISBLDMSK_MASK     0x2
#define USB2DC_DIEPEACHMSK6_EPDISBLDMSK_SHIFT    1 
#define USB2DC_DIEPEACHMSK6_EPDISBLDMSK_BIT      0x1
#define USB2DC_DIEPEACHMSK6_EPDISBLDMSK_BITWIDTH 1
// AHBErrMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK6_AHBERRMSK_MASK       0x4
#define USB2DC_DIEPEACHMSK6_AHBERRMSK_SHIFT      2 
#define USB2DC_DIEPEACHMSK6_AHBERRMSK_BIT        0x1
#define USB2DC_DIEPEACHMSK6_AHBERRMSK_BITWIDTH   1
// TimeOUTMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK6_TIMEOUTMSK_MASK      0x8
#define USB2DC_DIEPEACHMSK6_TIMEOUTMSK_SHIFT     3 
#define USB2DC_DIEPEACHMSK6_TIMEOUTMSK_BIT       0x1
#define USB2DC_DIEPEACHMSK6_TIMEOUTMSK_BITWIDTH  1
// INTknTXFEmpMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK6_INTKNTXFEMPMSK_MASK  0x10
#define USB2DC_DIEPEACHMSK6_INTKNTXFEMPMSK_SHIFT 4 
#define USB2DC_DIEPEACHMSK6_INTKNTXFEMPMSK_BIT   0x1
#define USB2DC_DIEPEACHMSK6_INTKNTXFEMPMSK_BITWIDTH 1
// INTknEPMisMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK6_INTKNEPMISMSK_MASK   0x20
#define USB2DC_DIEPEACHMSK6_INTKNEPMISMSK_SHIFT  5 
#define USB2DC_DIEPEACHMSK6_INTKNEPMISMSK_BIT    0x1
#define USB2DC_DIEPEACHMSK6_INTKNEPMISMSK_BITWIDTH 1
// INEPNakEffMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK6_INEPNAKEFFMSK_MASK   0x40
#define USB2DC_DIEPEACHMSK6_INEPNAKEFFMSK_SHIFT  6 
#define USB2DC_DIEPEACHMSK6_INEPNAKEFFMSK_BIT    0x1
#define USB2DC_DIEPEACHMSK6_INEPNAKEFFMSK_BITWIDTH 1
// Reserved3 bitfiled (RO) Reset=0
#define USB2DC_DIEPEACHMSK6_RESERVED3_MASK       0x80
#define USB2DC_DIEPEACHMSK6_RESERVED3_SHIFT      7 
#define USB2DC_DIEPEACHMSK6_RESERVED3_BIT        0x1
#define USB2DC_DIEPEACHMSK6_RESERVED3_BITWIDTH   1
// TxfifoUndrnMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK6_TXFIFOUNDRNMSK_MASK  0x100
#define USB2DC_DIEPEACHMSK6_TXFIFOUNDRNMSK_SHIFT 8 
#define USB2DC_DIEPEACHMSK6_TXFIFOUNDRNMSK_BIT   0x1
#define USB2DC_DIEPEACHMSK6_TXFIFOUNDRNMSK_BITWIDTH 1
// BNAInIntrMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK6_BNAININTRMSK_MASK    0x200
#define USB2DC_DIEPEACHMSK6_BNAININTRMSK_SHIFT   9 
#define USB2DC_DIEPEACHMSK6_BNAININTRMSK_BIT     0x1
#define USB2DC_DIEPEACHMSK6_BNAININTRMSK_BITWIDTH 1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DIEPEACHMSK6_RESERVED2_MASK       0x1C00
#define USB2DC_DIEPEACHMSK6_RESERVED2_SHIFT      10 
#define USB2DC_DIEPEACHMSK6_RESERVED2_BIT        0x7
#define USB2DC_DIEPEACHMSK6_RESERVED2_BITWIDTH   3
// NAKMsk bitfiled (RW) Reset=0
#define USB2DC_DIEPEACHMSK6_NAKMSK_MASK          0x2000
#define USB2DC_DIEPEACHMSK6_NAKMSK_SHIFT         13 
#define USB2DC_DIEPEACHMSK6_NAKMSK_BIT           0x1
#define USB2DC_DIEPEACHMSK6_NAKMSK_BITWIDTH      1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPEACHMSK6_RESERVED_MASK        0xFFFFC000
#define USB2DC_DIEPEACHMSK6_RESERVED_SHIFT       14 
#define USB2DC_DIEPEACHMSK6_RESERVED_BIT         0x3FFFF
#define USB2DC_DIEPEACHMSK6_RESERVED_BITWIDTH    18
// DOEPEACHMSK0 Register
#define USB2DC_DOEPEACHMSK0_OFS                  0x00000880
// XferComplMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK0_XFERCOMPLMSK_MASK    0x1
#define USB2DC_DOEPEACHMSK0_XFERCOMPLMSK_SHIFT   0 
#define USB2DC_DOEPEACHMSK0_XFERCOMPLMSK_BIT     0x1
#define USB2DC_DOEPEACHMSK0_XFERCOMPLMSK_BITWIDTH 1
// EPDisbldMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK0_EPDISBLDMSK_MASK     0x2
#define USB2DC_DOEPEACHMSK0_EPDISBLDMSK_SHIFT    1 
#define USB2DC_DOEPEACHMSK0_EPDISBLDMSK_BIT      0x1
#define USB2DC_DOEPEACHMSK0_EPDISBLDMSK_BITWIDTH 1
// AHBErrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK0_AHBERRMSK_MASK       0x4
#define USB2DC_DOEPEACHMSK0_AHBERRMSK_SHIFT      2 
#define USB2DC_DOEPEACHMSK0_AHBERRMSK_BIT        0x1
#define USB2DC_DOEPEACHMSK0_AHBERRMSK_BITWIDTH   1
// SetUPMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK0_SETUPMSK_MASK        0x8
#define USB2DC_DOEPEACHMSK0_SETUPMSK_SHIFT       3 
#define USB2DC_DOEPEACHMSK0_SETUPMSK_BIT         0x1
#define USB2DC_DOEPEACHMSK0_SETUPMSK_BITWIDTH    1
// OUTTknEPdisMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK0_OUTTKNEPDISMSK_MASK  0x10
#define USB2DC_DOEPEACHMSK0_OUTTKNEPDISMSK_SHIFT 4 
#define USB2DC_DOEPEACHMSK0_OUTTKNEPDISMSK_BIT   0x1
#define USB2DC_DOEPEACHMSK0_OUTTKNEPDISMSK_BITWIDTH 1
// Reserved4 bitfiled (RO) Reset=0
#define USB2DC_DOEPEACHMSK0_RESERVED4_MASK       0x20
#define USB2DC_DOEPEACHMSK0_RESERVED4_SHIFT      5 
#define USB2DC_DOEPEACHMSK0_RESERVED4_BIT        0x1
#define USB2DC_DOEPEACHMSK0_RESERVED4_BITWIDTH   1
// Back2BackSETup bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK0_BACK2BACKSETUP_MASK  0x40
#define USB2DC_DOEPEACHMSK0_BACK2BACKSETUP_SHIFT 6 
#define USB2DC_DOEPEACHMSK0_BACK2BACKSETUP_BIT   0x1
#define USB2DC_DOEPEACHMSK0_BACK2BACKSETUP_BITWIDTH 1
// Reserved3 bitfiled (RO) Reset=0
#define USB2DC_DOEPEACHMSK0_RESERVED3_MASK       0x80
#define USB2DC_DOEPEACHMSK0_RESERVED3_SHIFT      7 
#define USB2DC_DOEPEACHMSK0_RESERVED3_BIT        0x1
#define USB2DC_DOEPEACHMSK0_RESERVED3_BITWIDTH   1
// OutPktErrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK0_OUTPKTERRMSK_MASK    0x100
#define USB2DC_DOEPEACHMSK0_OUTPKTERRMSK_SHIFT   8 
#define USB2DC_DOEPEACHMSK0_OUTPKTERRMSK_BIT     0x1
#define USB2DC_DOEPEACHMSK0_OUTPKTERRMSK_BITWIDTH 1
// BnaOutIntrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK0_BNAOUTINTRMSK_MASK   0x200
#define USB2DC_DOEPEACHMSK0_BNAOUTINTRMSK_SHIFT  9 
#define USB2DC_DOEPEACHMSK0_BNAOUTINTRMSK_BIT    0x1
#define USB2DC_DOEPEACHMSK0_BNAOUTINTRMSK_BITWIDTH 1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DOEPEACHMSK0_RESERVED2_MASK       0xC00
#define USB2DC_DOEPEACHMSK0_RESERVED2_SHIFT      10 
#define USB2DC_DOEPEACHMSK0_RESERVED2_BIT        0x3
#define USB2DC_DOEPEACHMSK0_RESERVED2_BITWIDTH   2
// BbleErrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK0_BBLEERRMSK_MASK      0x1000
#define USB2DC_DOEPEACHMSK0_BBLEERRMSK_SHIFT     12 
#define USB2DC_DOEPEACHMSK0_BBLEERRMSK_BIT       0x1
#define USB2DC_DOEPEACHMSK0_BBLEERRMSK_BITWIDTH  1
// NAKMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK0_NAKMSK_MASK          0x2000
#define USB2DC_DOEPEACHMSK0_NAKMSK_SHIFT         13 
#define USB2DC_DOEPEACHMSK0_NAKMSK_BIT           0x1
#define USB2DC_DOEPEACHMSK0_NAKMSK_BITWIDTH      1
// NYETMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK0_NYETMSK_MASK         0x4000
#define USB2DC_DOEPEACHMSK0_NYETMSK_SHIFT        14 
#define USB2DC_DOEPEACHMSK0_NYETMSK_BIT          0x1
#define USB2DC_DOEPEACHMSK0_NYETMSK_BITWIDTH     1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DOEPEACHMSK0_RESERVED_MASK        0xFFFF8000
#define USB2DC_DOEPEACHMSK0_RESERVED_SHIFT       15 
#define USB2DC_DOEPEACHMSK0_RESERVED_BIT         0x1FFFF
#define USB2DC_DOEPEACHMSK0_RESERVED_BITWIDTH    17
// DOEPEACHMSK1 Register
#define USB2DC_DOEPEACHMSK1_OFS                  0x00000884
// XferComplMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK1_XFERCOMPLMSK_MASK    0x1
#define USB2DC_DOEPEACHMSK1_XFERCOMPLMSK_SHIFT   0 
#define USB2DC_DOEPEACHMSK1_XFERCOMPLMSK_BIT     0x1
#define USB2DC_DOEPEACHMSK1_XFERCOMPLMSK_BITWIDTH 1
// EPDisbldMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK1_EPDISBLDMSK_MASK     0x2
#define USB2DC_DOEPEACHMSK1_EPDISBLDMSK_SHIFT    1 
#define USB2DC_DOEPEACHMSK1_EPDISBLDMSK_BIT      0x1
#define USB2DC_DOEPEACHMSK1_EPDISBLDMSK_BITWIDTH 1
// AHBErrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK1_AHBERRMSK_MASK       0x4
#define USB2DC_DOEPEACHMSK1_AHBERRMSK_SHIFT      2 
#define USB2DC_DOEPEACHMSK1_AHBERRMSK_BIT        0x1
#define USB2DC_DOEPEACHMSK1_AHBERRMSK_BITWIDTH   1
// SetUPMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK1_SETUPMSK_MASK        0x8
#define USB2DC_DOEPEACHMSK1_SETUPMSK_SHIFT       3 
#define USB2DC_DOEPEACHMSK1_SETUPMSK_BIT         0x1
#define USB2DC_DOEPEACHMSK1_SETUPMSK_BITWIDTH    1
// OUTTknEPdisMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK1_OUTTKNEPDISMSK_MASK  0x10
#define USB2DC_DOEPEACHMSK1_OUTTKNEPDISMSK_SHIFT 4 
#define USB2DC_DOEPEACHMSK1_OUTTKNEPDISMSK_BIT   0x1
#define USB2DC_DOEPEACHMSK1_OUTTKNEPDISMSK_BITWIDTH 1
// Reserved4 bitfiled (RO) Reset=0
#define USB2DC_DOEPEACHMSK1_RESERVED4_MASK       0x20
#define USB2DC_DOEPEACHMSK1_RESERVED4_SHIFT      5 
#define USB2DC_DOEPEACHMSK1_RESERVED4_BIT        0x1
#define USB2DC_DOEPEACHMSK1_RESERVED4_BITWIDTH   1
// Back2BackSETup bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK1_BACK2BACKSETUP_MASK  0x40
#define USB2DC_DOEPEACHMSK1_BACK2BACKSETUP_SHIFT 6 
#define USB2DC_DOEPEACHMSK1_BACK2BACKSETUP_BIT   0x1
#define USB2DC_DOEPEACHMSK1_BACK2BACKSETUP_BITWIDTH 1
// Reserved3 bitfiled (RO) Reset=0
#define USB2DC_DOEPEACHMSK1_RESERVED3_MASK       0x80
#define USB2DC_DOEPEACHMSK1_RESERVED3_SHIFT      7 
#define USB2DC_DOEPEACHMSK1_RESERVED3_BIT        0x1
#define USB2DC_DOEPEACHMSK1_RESERVED3_BITWIDTH   1
// OutPktErrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK1_OUTPKTERRMSK_MASK    0x100
#define USB2DC_DOEPEACHMSK1_OUTPKTERRMSK_SHIFT   8 
#define USB2DC_DOEPEACHMSK1_OUTPKTERRMSK_BIT     0x1
#define USB2DC_DOEPEACHMSK1_OUTPKTERRMSK_BITWIDTH 1
// BnaOutIntrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK1_BNAOUTINTRMSK_MASK   0x200
#define USB2DC_DOEPEACHMSK1_BNAOUTINTRMSK_SHIFT  9 
#define USB2DC_DOEPEACHMSK1_BNAOUTINTRMSK_BIT    0x1
#define USB2DC_DOEPEACHMSK1_BNAOUTINTRMSK_BITWIDTH 1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DOEPEACHMSK1_RESERVED2_MASK       0xC00
#define USB2DC_DOEPEACHMSK1_RESERVED2_SHIFT      10 
#define USB2DC_DOEPEACHMSK1_RESERVED2_BIT        0x3
#define USB2DC_DOEPEACHMSK1_RESERVED2_BITWIDTH   2
// BbleErrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK1_BBLEERRMSK_MASK      0x1000
#define USB2DC_DOEPEACHMSK1_BBLEERRMSK_SHIFT     12 
#define USB2DC_DOEPEACHMSK1_BBLEERRMSK_BIT       0x1
#define USB2DC_DOEPEACHMSK1_BBLEERRMSK_BITWIDTH  1
// NAKMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK1_NAKMSK_MASK          0x2000
#define USB2DC_DOEPEACHMSK1_NAKMSK_SHIFT         13 
#define USB2DC_DOEPEACHMSK1_NAKMSK_BIT           0x1
#define USB2DC_DOEPEACHMSK1_NAKMSK_BITWIDTH      1
// NYETMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK1_NYETMSK_MASK         0x4000
#define USB2DC_DOEPEACHMSK1_NYETMSK_SHIFT        14 
#define USB2DC_DOEPEACHMSK1_NYETMSK_BIT          0x1
#define USB2DC_DOEPEACHMSK1_NYETMSK_BITWIDTH     1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DOEPEACHMSK1_RESERVED_MASK        0xFFFF8000
#define USB2DC_DOEPEACHMSK1_RESERVED_SHIFT       15 
#define USB2DC_DOEPEACHMSK1_RESERVED_BIT         0x1FFFF
#define USB2DC_DOEPEACHMSK1_RESERVED_BITWIDTH    17
// DOEPEACHMSK2 Register
#define USB2DC_DOEPEACHMSK2_OFS                  0x00000888
// XferComplMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK2_XFERCOMPLMSK_MASK    0x1
#define USB2DC_DOEPEACHMSK2_XFERCOMPLMSK_SHIFT   0 
#define USB2DC_DOEPEACHMSK2_XFERCOMPLMSK_BIT     0x1
#define USB2DC_DOEPEACHMSK2_XFERCOMPLMSK_BITWIDTH 1
// EPDisbldMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK2_EPDISBLDMSK_MASK     0x2
#define USB2DC_DOEPEACHMSK2_EPDISBLDMSK_SHIFT    1 
#define USB2DC_DOEPEACHMSK2_EPDISBLDMSK_BIT      0x1
#define USB2DC_DOEPEACHMSK2_EPDISBLDMSK_BITWIDTH 1
// AHBErrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK2_AHBERRMSK_MASK       0x4
#define USB2DC_DOEPEACHMSK2_AHBERRMSK_SHIFT      2 
#define USB2DC_DOEPEACHMSK2_AHBERRMSK_BIT        0x1
#define USB2DC_DOEPEACHMSK2_AHBERRMSK_BITWIDTH   1
// SetUPMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK2_SETUPMSK_MASK        0x8
#define USB2DC_DOEPEACHMSK2_SETUPMSK_SHIFT       3 
#define USB2DC_DOEPEACHMSK2_SETUPMSK_BIT         0x1
#define USB2DC_DOEPEACHMSK2_SETUPMSK_BITWIDTH    1
// OUTTknEPdisMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK2_OUTTKNEPDISMSK_MASK  0x10
#define USB2DC_DOEPEACHMSK2_OUTTKNEPDISMSK_SHIFT 4 
#define USB2DC_DOEPEACHMSK2_OUTTKNEPDISMSK_BIT   0x1
#define USB2DC_DOEPEACHMSK2_OUTTKNEPDISMSK_BITWIDTH 1
// Reserved4 bitfiled (RO) Reset=0
#define USB2DC_DOEPEACHMSK2_RESERVED4_MASK       0x20
#define USB2DC_DOEPEACHMSK2_RESERVED4_SHIFT      5 
#define USB2DC_DOEPEACHMSK2_RESERVED4_BIT        0x1
#define USB2DC_DOEPEACHMSK2_RESERVED4_BITWIDTH   1
// Back2BackSETup bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK2_BACK2BACKSETUP_MASK  0x40
#define USB2DC_DOEPEACHMSK2_BACK2BACKSETUP_SHIFT 6 
#define USB2DC_DOEPEACHMSK2_BACK2BACKSETUP_BIT   0x1
#define USB2DC_DOEPEACHMSK2_BACK2BACKSETUP_BITWIDTH 1
// Reserved3 bitfiled (RO) Reset=0
#define USB2DC_DOEPEACHMSK2_RESERVED3_MASK       0x80
#define USB2DC_DOEPEACHMSK2_RESERVED3_SHIFT      7 
#define USB2DC_DOEPEACHMSK2_RESERVED3_BIT        0x1
#define USB2DC_DOEPEACHMSK2_RESERVED3_BITWIDTH   1
// OutPktErrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK2_OUTPKTERRMSK_MASK    0x100
#define USB2DC_DOEPEACHMSK2_OUTPKTERRMSK_SHIFT   8 
#define USB2DC_DOEPEACHMSK2_OUTPKTERRMSK_BIT     0x1
#define USB2DC_DOEPEACHMSK2_OUTPKTERRMSK_BITWIDTH 1
// BnaOutIntrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK2_BNAOUTINTRMSK_MASK   0x200
#define USB2DC_DOEPEACHMSK2_BNAOUTINTRMSK_SHIFT  9 
#define USB2DC_DOEPEACHMSK2_BNAOUTINTRMSK_BIT    0x1
#define USB2DC_DOEPEACHMSK2_BNAOUTINTRMSK_BITWIDTH 1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DOEPEACHMSK2_RESERVED2_MASK       0xC00
#define USB2DC_DOEPEACHMSK2_RESERVED2_SHIFT      10 
#define USB2DC_DOEPEACHMSK2_RESERVED2_BIT        0x3
#define USB2DC_DOEPEACHMSK2_RESERVED2_BITWIDTH   2
// BbleErrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK2_BBLEERRMSK_MASK      0x1000
#define USB2DC_DOEPEACHMSK2_BBLEERRMSK_SHIFT     12 
#define USB2DC_DOEPEACHMSK2_BBLEERRMSK_BIT       0x1
#define USB2DC_DOEPEACHMSK2_BBLEERRMSK_BITWIDTH  1
// NAKMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK2_NAKMSK_MASK          0x2000
#define USB2DC_DOEPEACHMSK2_NAKMSK_SHIFT         13 
#define USB2DC_DOEPEACHMSK2_NAKMSK_BIT           0x1
#define USB2DC_DOEPEACHMSK2_NAKMSK_BITWIDTH      1
// NYETMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK2_NYETMSK_MASK         0x4000
#define USB2DC_DOEPEACHMSK2_NYETMSK_SHIFT        14 
#define USB2DC_DOEPEACHMSK2_NYETMSK_BIT          0x1
#define USB2DC_DOEPEACHMSK2_NYETMSK_BITWIDTH     1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DOEPEACHMSK2_RESERVED_MASK        0xFFFF8000
#define USB2DC_DOEPEACHMSK2_RESERVED_SHIFT       15 
#define USB2DC_DOEPEACHMSK2_RESERVED_BIT         0x1FFFF
#define USB2DC_DOEPEACHMSK2_RESERVED_BITWIDTH    17
// DOEPEACHMSK3 Register
#define USB2DC_DOEPEACHMSK3_OFS                  0x0000088C
// XferComplMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK3_XFERCOMPLMSK_MASK    0x1
#define USB2DC_DOEPEACHMSK3_XFERCOMPLMSK_SHIFT   0 
#define USB2DC_DOEPEACHMSK3_XFERCOMPLMSK_BIT     0x1
#define USB2DC_DOEPEACHMSK3_XFERCOMPLMSK_BITWIDTH 1
// EPDisbldMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK3_EPDISBLDMSK_MASK     0x2
#define USB2DC_DOEPEACHMSK3_EPDISBLDMSK_SHIFT    1 
#define USB2DC_DOEPEACHMSK3_EPDISBLDMSK_BIT      0x1
#define USB2DC_DOEPEACHMSK3_EPDISBLDMSK_BITWIDTH 1
// AHBErrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK3_AHBERRMSK_MASK       0x4
#define USB2DC_DOEPEACHMSK3_AHBERRMSK_SHIFT      2 
#define USB2DC_DOEPEACHMSK3_AHBERRMSK_BIT        0x1
#define USB2DC_DOEPEACHMSK3_AHBERRMSK_BITWIDTH   1
// SetUPMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK3_SETUPMSK_MASK        0x8
#define USB2DC_DOEPEACHMSK3_SETUPMSK_SHIFT       3 
#define USB2DC_DOEPEACHMSK3_SETUPMSK_BIT         0x1
#define USB2DC_DOEPEACHMSK3_SETUPMSK_BITWIDTH    1
// OUTTknEPdisMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK3_OUTTKNEPDISMSK_MASK  0x10
#define USB2DC_DOEPEACHMSK3_OUTTKNEPDISMSK_SHIFT 4 
#define USB2DC_DOEPEACHMSK3_OUTTKNEPDISMSK_BIT   0x1
#define USB2DC_DOEPEACHMSK3_OUTTKNEPDISMSK_BITWIDTH 1
// Reserved4 bitfiled (RO) Reset=0
#define USB2DC_DOEPEACHMSK3_RESERVED4_MASK       0x20
#define USB2DC_DOEPEACHMSK3_RESERVED4_SHIFT      5 
#define USB2DC_DOEPEACHMSK3_RESERVED4_BIT        0x1
#define USB2DC_DOEPEACHMSK3_RESERVED4_BITWIDTH   1
// Back2BackSETup bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK3_BACK2BACKSETUP_MASK  0x40
#define USB2DC_DOEPEACHMSK3_BACK2BACKSETUP_SHIFT 6 
#define USB2DC_DOEPEACHMSK3_BACK2BACKSETUP_BIT   0x1
#define USB2DC_DOEPEACHMSK3_BACK2BACKSETUP_BITWIDTH 1
// Reserved3 bitfiled (RO) Reset=0
#define USB2DC_DOEPEACHMSK3_RESERVED3_MASK       0x80
#define USB2DC_DOEPEACHMSK3_RESERVED3_SHIFT      7 
#define USB2DC_DOEPEACHMSK3_RESERVED3_BIT        0x1
#define USB2DC_DOEPEACHMSK3_RESERVED3_BITWIDTH   1
// OutPktErrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK3_OUTPKTERRMSK_MASK    0x100
#define USB2DC_DOEPEACHMSK3_OUTPKTERRMSK_SHIFT   8 
#define USB2DC_DOEPEACHMSK3_OUTPKTERRMSK_BIT     0x1
#define USB2DC_DOEPEACHMSK3_OUTPKTERRMSK_BITWIDTH 1
// BnaOutIntrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK3_BNAOUTINTRMSK_MASK   0x200
#define USB2DC_DOEPEACHMSK3_BNAOUTINTRMSK_SHIFT  9 
#define USB2DC_DOEPEACHMSK3_BNAOUTINTRMSK_BIT    0x1
#define USB2DC_DOEPEACHMSK3_BNAOUTINTRMSK_BITWIDTH 1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DOEPEACHMSK3_RESERVED2_MASK       0xC00
#define USB2DC_DOEPEACHMSK3_RESERVED2_SHIFT      10 
#define USB2DC_DOEPEACHMSK3_RESERVED2_BIT        0x3
#define USB2DC_DOEPEACHMSK3_RESERVED2_BITWIDTH   2
// BbleErrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK3_BBLEERRMSK_MASK      0x1000
#define USB2DC_DOEPEACHMSK3_BBLEERRMSK_SHIFT     12 
#define USB2DC_DOEPEACHMSK3_BBLEERRMSK_BIT       0x1
#define USB2DC_DOEPEACHMSK3_BBLEERRMSK_BITWIDTH  1
// NAKMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK3_NAKMSK_MASK          0x2000
#define USB2DC_DOEPEACHMSK3_NAKMSK_SHIFT         13 
#define USB2DC_DOEPEACHMSK3_NAKMSK_BIT           0x1
#define USB2DC_DOEPEACHMSK3_NAKMSK_BITWIDTH      1
// NYETMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK3_NYETMSK_MASK         0x4000
#define USB2DC_DOEPEACHMSK3_NYETMSK_SHIFT        14 
#define USB2DC_DOEPEACHMSK3_NYETMSK_BIT          0x1
#define USB2DC_DOEPEACHMSK3_NYETMSK_BITWIDTH     1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DOEPEACHMSK3_RESERVED_MASK        0xFFFF8000
#define USB2DC_DOEPEACHMSK3_RESERVED_SHIFT       15 
#define USB2DC_DOEPEACHMSK3_RESERVED_BIT         0x1FFFF
#define USB2DC_DOEPEACHMSK3_RESERVED_BITWIDTH    17
// DOEPEACHMSK4 Register
#define USB2DC_DOEPEACHMSK4_OFS                  0x00000890
// XferComplMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK4_XFERCOMPLMSK_MASK    0x1
#define USB2DC_DOEPEACHMSK4_XFERCOMPLMSK_SHIFT   0 
#define USB2DC_DOEPEACHMSK4_XFERCOMPLMSK_BIT     0x1
#define USB2DC_DOEPEACHMSK4_XFERCOMPLMSK_BITWIDTH 1
// EPDisbldMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK4_EPDISBLDMSK_MASK     0x2
#define USB2DC_DOEPEACHMSK4_EPDISBLDMSK_SHIFT    1 
#define USB2DC_DOEPEACHMSK4_EPDISBLDMSK_BIT      0x1
#define USB2DC_DOEPEACHMSK4_EPDISBLDMSK_BITWIDTH 1
// AHBErrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK4_AHBERRMSK_MASK       0x4
#define USB2DC_DOEPEACHMSK4_AHBERRMSK_SHIFT      2 
#define USB2DC_DOEPEACHMSK4_AHBERRMSK_BIT        0x1
#define USB2DC_DOEPEACHMSK4_AHBERRMSK_BITWIDTH   1
// SetUPMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK4_SETUPMSK_MASK        0x8
#define USB2DC_DOEPEACHMSK4_SETUPMSK_SHIFT       3 
#define USB2DC_DOEPEACHMSK4_SETUPMSK_BIT         0x1
#define USB2DC_DOEPEACHMSK4_SETUPMSK_BITWIDTH    1
// OUTTknEPdisMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK4_OUTTKNEPDISMSK_MASK  0x10
#define USB2DC_DOEPEACHMSK4_OUTTKNEPDISMSK_SHIFT 4 
#define USB2DC_DOEPEACHMSK4_OUTTKNEPDISMSK_BIT   0x1
#define USB2DC_DOEPEACHMSK4_OUTTKNEPDISMSK_BITWIDTH 1
// Reserved4 bitfiled (RO) Reset=0
#define USB2DC_DOEPEACHMSK4_RESERVED4_MASK       0x20
#define USB2DC_DOEPEACHMSK4_RESERVED4_SHIFT      5 
#define USB2DC_DOEPEACHMSK4_RESERVED4_BIT        0x1
#define USB2DC_DOEPEACHMSK4_RESERVED4_BITWIDTH   1
// Back2BackSETup bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK4_BACK2BACKSETUP_MASK  0x40
#define USB2DC_DOEPEACHMSK4_BACK2BACKSETUP_SHIFT 6 
#define USB2DC_DOEPEACHMSK4_BACK2BACKSETUP_BIT   0x1
#define USB2DC_DOEPEACHMSK4_BACK2BACKSETUP_BITWIDTH 1
// Reserved3 bitfiled (RO) Reset=0
#define USB2DC_DOEPEACHMSK4_RESERVED3_MASK       0x80
#define USB2DC_DOEPEACHMSK4_RESERVED3_SHIFT      7 
#define USB2DC_DOEPEACHMSK4_RESERVED3_BIT        0x1
#define USB2DC_DOEPEACHMSK4_RESERVED3_BITWIDTH   1
// OutPktErrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK4_OUTPKTERRMSK_MASK    0x100
#define USB2DC_DOEPEACHMSK4_OUTPKTERRMSK_SHIFT   8 
#define USB2DC_DOEPEACHMSK4_OUTPKTERRMSK_BIT     0x1
#define USB2DC_DOEPEACHMSK4_OUTPKTERRMSK_BITWIDTH 1
// BnaOutIntrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK4_BNAOUTINTRMSK_MASK   0x200
#define USB2DC_DOEPEACHMSK4_BNAOUTINTRMSK_SHIFT  9 
#define USB2DC_DOEPEACHMSK4_BNAOUTINTRMSK_BIT    0x1
#define USB2DC_DOEPEACHMSK4_BNAOUTINTRMSK_BITWIDTH 1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DOEPEACHMSK4_RESERVED2_MASK       0xC00
#define USB2DC_DOEPEACHMSK4_RESERVED2_SHIFT      10 
#define USB2DC_DOEPEACHMSK4_RESERVED2_BIT        0x3
#define USB2DC_DOEPEACHMSK4_RESERVED2_BITWIDTH   2
// BbleErrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK4_BBLEERRMSK_MASK      0x1000
#define USB2DC_DOEPEACHMSK4_BBLEERRMSK_SHIFT     12 
#define USB2DC_DOEPEACHMSK4_BBLEERRMSK_BIT       0x1
#define USB2DC_DOEPEACHMSK4_BBLEERRMSK_BITWIDTH  1
// NAKMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK4_NAKMSK_MASK          0x2000
#define USB2DC_DOEPEACHMSK4_NAKMSK_SHIFT         13 
#define USB2DC_DOEPEACHMSK4_NAKMSK_BIT           0x1
#define USB2DC_DOEPEACHMSK4_NAKMSK_BITWIDTH      1
// NYETMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK4_NYETMSK_MASK         0x4000
#define USB2DC_DOEPEACHMSK4_NYETMSK_SHIFT        14 
#define USB2DC_DOEPEACHMSK4_NYETMSK_BIT          0x1
#define USB2DC_DOEPEACHMSK4_NYETMSK_BITWIDTH     1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DOEPEACHMSK4_RESERVED_MASK        0xFFFF8000
#define USB2DC_DOEPEACHMSK4_RESERVED_SHIFT       15 
#define USB2DC_DOEPEACHMSK4_RESERVED_BIT         0x1FFFF
#define USB2DC_DOEPEACHMSK4_RESERVED_BITWIDTH    17
// DOEPEACHMSK5 Register
#define USB2DC_DOEPEACHMSK5_OFS                  0x00000894
// XferComplMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK5_XFERCOMPLMSK_MASK    0x1
#define USB2DC_DOEPEACHMSK5_XFERCOMPLMSK_SHIFT   0 
#define USB2DC_DOEPEACHMSK5_XFERCOMPLMSK_BIT     0x1
#define USB2DC_DOEPEACHMSK5_XFERCOMPLMSK_BITWIDTH 1
// EPDisbldMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK5_EPDISBLDMSK_MASK     0x2
#define USB2DC_DOEPEACHMSK5_EPDISBLDMSK_SHIFT    1 
#define USB2DC_DOEPEACHMSK5_EPDISBLDMSK_BIT      0x1
#define USB2DC_DOEPEACHMSK5_EPDISBLDMSK_BITWIDTH 1
// AHBErrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK5_AHBERRMSK_MASK       0x4
#define USB2DC_DOEPEACHMSK5_AHBERRMSK_SHIFT      2 
#define USB2DC_DOEPEACHMSK5_AHBERRMSK_BIT        0x1
#define USB2DC_DOEPEACHMSK5_AHBERRMSK_BITWIDTH   1
// SetUPMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK5_SETUPMSK_MASK        0x8
#define USB2DC_DOEPEACHMSK5_SETUPMSK_SHIFT       3 
#define USB2DC_DOEPEACHMSK5_SETUPMSK_BIT         0x1
#define USB2DC_DOEPEACHMSK5_SETUPMSK_BITWIDTH    1
// OUTTknEPdisMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK5_OUTTKNEPDISMSK_MASK  0x10
#define USB2DC_DOEPEACHMSK5_OUTTKNEPDISMSK_SHIFT 4 
#define USB2DC_DOEPEACHMSK5_OUTTKNEPDISMSK_BIT   0x1
#define USB2DC_DOEPEACHMSK5_OUTTKNEPDISMSK_BITWIDTH 1
// Reserved4 bitfiled (RO) Reset=0
#define USB2DC_DOEPEACHMSK5_RESERVED4_MASK       0x20
#define USB2DC_DOEPEACHMSK5_RESERVED4_SHIFT      5 
#define USB2DC_DOEPEACHMSK5_RESERVED4_BIT        0x1
#define USB2DC_DOEPEACHMSK5_RESERVED4_BITWIDTH   1
// Back2BackSETup bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK5_BACK2BACKSETUP_MASK  0x40
#define USB2DC_DOEPEACHMSK5_BACK2BACKSETUP_SHIFT 6 
#define USB2DC_DOEPEACHMSK5_BACK2BACKSETUP_BIT   0x1
#define USB2DC_DOEPEACHMSK5_BACK2BACKSETUP_BITWIDTH 1
// Reserved3 bitfiled (RO) Reset=0
#define USB2DC_DOEPEACHMSK5_RESERVED3_MASK       0x80
#define USB2DC_DOEPEACHMSK5_RESERVED3_SHIFT      7 
#define USB2DC_DOEPEACHMSK5_RESERVED3_BIT        0x1
#define USB2DC_DOEPEACHMSK5_RESERVED3_BITWIDTH   1
// OutPktErrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK5_OUTPKTERRMSK_MASK    0x100
#define USB2DC_DOEPEACHMSK5_OUTPKTERRMSK_SHIFT   8 
#define USB2DC_DOEPEACHMSK5_OUTPKTERRMSK_BIT     0x1
#define USB2DC_DOEPEACHMSK5_OUTPKTERRMSK_BITWIDTH 1
// BnaOutIntrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK5_BNAOUTINTRMSK_MASK   0x200
#define USB2DC_DOEPEACHMSK5_BNAOUTINTRMSK_SHIFT  9 
#define USB2DC_DOEPEACHMSK5_BNAOUTINTRMSK_BIT    0x1
#define USB2DC_DOEPEACHMSK5_BNAOUTINTRMSK_BITWIDTH 1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DOEPEACHMSK5_RESERVED2_MASK       0xC00
#define USB2DC_DOEPEACHMSK5_RESERVED2_SHIFT      10 
#define USB2DC_DOEPEACHMSK5_RESERVED2_BIT        0x3
#define USB2DC_DOEPEACHMSK5_RESERVED2_BITWIDTH   2
// BbleErrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK5_BBLEERRMSK_MASK      0x1000
#define USB2DC_DOEPEACHMSK5_BBLEERRMSK_SHIFT     12 
#define USB2DC_DOEPEACHMSK5_BBLEERRMSK_BIT       0x1
#define USB2DC_DOEPEACHMSK5_BBLEERRMSK_BITWIDTH  1
// NAKMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK5_NAKMSK_MASK          0x2000
#define USB2DC_DOEPEACHMSK5_NAKMSK_SHIFT         13 
#define USB2DC_DOEPEACHMSK5_NAKMSK_BIT           0x1
#define USB2DC_DOEPEACHMSK5_NAKMSK_BITWIDTH      1
// NYETMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK5_NYETMSK_MASK         0x4000
#define USB2DC_DOEPEACHMSK5_NYETMSK_SHIFT        14 
#define USB2DC_DOEPEACHMSK5_NYETMSK_BIT          0x1
#define USB2DC_DOEPEACHMSK5_NYETMSK_BITWIDTH     1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DOEPEACHMSK5_RESERVED_MASK        0xFFFF8000
#define USB2DC_DOEPEACHMSK5_RESERVED_SHIFT       15 
#define USB2DC_DOEPEACHMSK5_RESERVED_BIT         0x1FFFF
#define USB2DC_DOEPEACHMSK5_RESERVED_BITWIDTH    17
// DOEPEACHMSK6 Register
#define USB2DC_DOEPEACHMSK6_OFS                  0x00000898
// XferComplMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK6_XFERCOMPLMSK_MASK    0x1
#define USB2DC_DOEPEACHMSK6_XFERCOMPLMSK_SHIFT   0 
#define USB2DC_DOEPEACHMSK6_XFERCOMPLMSK_BIT     0x1
#define USB2DC_DOEPEACHMSK6_XFERCOMPLMSK_BITWIDTH 1
// EPDisbldMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK6_EPDISBLDMSK_MASK     0x2
#define USB2DC_DOEPEACHMSK6_EPDISBLDMSK_SHIFT    1 
#define USB2DC_DOEPEACHMSK6_EPDISBLDMSK_BIT      0x1
#define USB2DC_DOEPEACHMSK6_EPDISBLDMSK_BITWIDTH 1
// AHBErrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK6_AHBERRMSK_MASK       0x4
#define USB2DC_DOEPEACHMSK6_AHBERRMSK_SHIFT      2 
#define USB2DC_DOEPEACHMSK6_AHBERRMSK_BIT        0x1
#define USB2DC_DOEPEACHMSK6_AHBERRMSK_BITWIDTH   1
// SetUPMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK6_SETUPMSK_MASK        0x8
#define USB2DC_DOEPEACHMSK6_SETUPMSK_SHIFT       3 
#define USB2DC_DOEPEACHMSK6_SETUPMSK_BIT         0x1
#define USB2DC_DOEPEACHMSK6_SETUPMSK_BITWIDTH    1
// OUTTknEPdisMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK6_OUTTKNEPDISMSK_MASK  0x10
#define USB2DC_DOEPEACHMSK6_OUTTKNEPDISMSK_SHIFT 4 
#define USB2DC_DOEPEACHMSK6_OUTTKNEPDISMSK_BIT   0x1
#define USB2DC_DOEPEACHMSK6_OUTTKNEPDISMSK_BITWIDTH 1
// Reserved4 bitfiled (RO) Reset=0
#define USB2DC_DOEPEACHMSK6_RESERVED4_MASK       0x20
#define USB2DC_DOEPEACHMSK6_RESERVED4_SHIFT      5 
#define USB2DC_DOEPEACHMSK6_RESERVED4_BIT        0x1
#define USB2DC_DOEPEACHMSK6_RESERVED4_BITWIDTH   1
// Back2BackSETup bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK6_BACK2BACKSETUP_MASK  0x40
#define USB2DC_DOEPEACHMSK6_BACK2BACKSETUP_SHIFT 6 
#define USB2DC_DOEPEACHMSK6_BACK2BACKSETUP_BIT   0x1
#define USB2DC_DOEPEACHMSK6_BACK2BACKSETUP_BITWIDTH 1
// Reserved3 bitfiled (RO) Reset=0
#define USB2DC_DOEPEACHMSK6_RESERVED3_MASK       0x80
#define USB2DC_DOEPEACHMSK6_RESERVED3_SHIFT      7 
#define USB2DC_DOEPEACHMSK6_RESERVED3_BIT        0x1
#define USB2DC_DOEPEACHMSK6_RESERVED3_BITWIDTH   1
// OutPktErrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK6_OUTPKTERRMSK_MASK    0x100
#define USB2DC_DOEPEACHMSK6_OUTPKTERRMSK_SHIFT   8 
#define USB2DC_DOEPEACHMSK6_OUTPKTERRMSK_BIT     0x1
#define USB2DC_DOEPEACHMSK6_OUTPKTERRMSK_BITWIDTH 1
// BnaOutIntrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK6_BNAOUTINTRMSK_MASK   0x200
#define USB2DC_DOEPEACHMSK6_BNAOUTINTRMSK_SHIFT  9 
#define USB2DC_DOEPEACHMSK6_BNAOUTINTRMSK_BIT    0x1
#define USB2DC_DOEPEACHMSK6_BNAOUTINTRMSK_BITWIDTH 1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DOEPEACHMSK6_RESERVED2_MASK       0xC00
#define USB2DC_DOEPEACHMSK6_RESERVED2_SHIFT      10 
#define USB2DC_DOEPEACHMSK6_RESERVED2_BIT        0x3
#define USB2DC_DOEPEACHMSK6_RESERVED2_BITWIDTH   2
// BbleErrMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK6_BBLEERRMSK_MASK      0x1000
#define USB2DC_DOEPEACHMSK6_BBLEERRMSK_SHIFT     12 
#define USB2DC_DOEPEACHMSK6_BBLEERRMSK_BIT       0x1
#define USB2DC_DOEPEACHMSK6_BBLEERRMSK_BITWIDTH  1
// NAKMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK6_NAKMSK_MASK          0x2000
#define USB2DC_DOEPEACHMSK6_NAKMSK_SHIFT         13 
#define USB2DC_DOEPEACHMSK6_NAKMSK_BIT           0x1
#define USB2DC_DOEPEACHMSK6_NAKMSK_BITWIDTH      1
// NYETMsk bitfiled (RW) Reset=0
#define USB2DC_DOEPEACHMSK6_NYETMSK_MASK         0x4000
#define USB2DC_DOEPEACHMSK6_NYETMSK_SHIFT        14 
#define USB2DC_DOEPEACHMSK6_NYETMSK_BIT          0x1
#define USB2DC_DOEPEACHMSK6_NYETMSK_BITWIDTH     1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DOEPEACHMSK6_RESERVED_MASK        0xFFFF8000
#define USB2DC_DOEPEACHMSK6_RESERVED_SHIFT       15 
#define USB2DC_DOEPEACHMSK6_RESERVED_BIT         0x1FFFF
#define USB2DC_DOEPEACHMSK6_RESERVED_BITWIDTH    17
// DIEPCTL0 Register
#define USB2DC_DIEPCTL0_OFS                      0x00000900
// MPS bitfiled (RW) Reset=0
#define USB2DC_DIEPCTL0_MPS_MASK                 0x3
#define USB2DC_DIEPCTL0_MPS_SHIFT                0 
#define USB2DC_DIEPCTL0_MPS_BIT                  0x3
#define USB2DC_DIEPCTL0_MPS_BITWIDTH             2
// Reserved4 bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL0_RESERVED4_MASK           0x7FFC
#define USB2DC_DIEPCTL0_RESERVED4_SHIFT          2 
#define USB2DC_DIEPCTL0_RESERVED4_BIT            0x1FFF
#define USB2DC_DIEPCTL0_RESERVED4_BITWIDTH       13
// USBActEP bitfiled (RO) Reset=1
#define USB2DC_DIEPCTL0_USBACTEP_MASK            0x8000
#define USB2DC_DIEPCTL0_USBACTEP_SHIFT           15 
#define USB2DC_DIEPCTL0_USBACTEP_BIT             0x1
#define USB2DC_DIEPCTL0_USBACTEP_BITWIDTH        1
// Reserved3 bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL0_RESERVED3_MASK           0x10000
#define USB2DC_DIEPCTL0_RESERVED3_SHIFT          16 
#define USB2DC_DIEPCTL0_RESERVED3_BIT            0x1
#define USB2DC_DIEPCTL0_RESERVED3_BITWIDTH       1
// NAKSts bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL0_NAKSTS_MASK              0x20000
#define USB2DC_DIEPCTL0_NAKSTS_SHIFT             17 
#define USB2DC_DIEPCTL0_NAKSTS_BIT               0x1
#define USB2DC_DIEPCTL0_NAKSTS_BITWIDTH          1
// EPType bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL0_EPTYPE_MASK              0xC0000
#define USB2DC_DIEPCTL0_EPTYPE_SHIFT             18 
#define USB2DC_DIEPCTL0_EPTYPE_BIT               0x3
#define USB2DC_DIEPCTL0_EPTYPE_BITWIDTH          2
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL0_RESERVED2_MASK           0x100000
#define USB2DC_DIEPCTL0_RESERVED2_SHIFT          20 
#define USB2DC_DIEPCTL0_RESERVED2_BIT            0x1
#define USB2DC_DIEPCTL0_RESERVED2_BITWIDTH       1
// Stall bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL0_STALL_MASK               0x200000
#define USB2DC_DIEPCTL0_STALL_SHIFT              21 
#define USB2DC_DIEPCTL0_STALL_BIT                0x1
#define USB2DC_DIEPCTL0_STALL_BITWIDTH           1
// TxFNum bitfiled (RW) Reset=0
#define USB2DC_DIEPCTL0_TXFNUM_MASK              0x3C00000
#define USB2DC_DIEPCTL0_TXFNUM_SHIFT             22 
#define USB2DC_DIEPCTL0_TXFNUM_BIT               0xF
#define USB2DC_DIEPCTL0_TXFNUM_BITWIDTH          4
// CNAK bitfiled (WO) Reset=0
#define USB2DC_DIEPCTL0_CNAK_MASK                0x4000000
#define USB2DC_DIEPCTL0_CNAK_SHIFT               26 
#define USB2DC_DIEPCTL0_CNAK_BIT                 0x1
#define USB2DC_DIEPCTL0_CNAK_BITWIDTH            1
// SNAK bitfiled (WO) Reset=0
#define USB2DC_DIEPCTL0_SNAK_MASK                0x8000000
#define USB2DC_DIEPCTL0_SNAK_SHIFT               27 
#define USB2DC_DIEPCTL0_SNAK_BIT                 0x1
#define USB2DC_DIEPCTL0_SNAK_BITWIDTH            1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL0_RESERVED_MASK            0x30000000
#define USB2DC_DIEPCTL0_RESERVED_SHIFT           28 
#define USB2DC_DIEPCTL0_RESERVED_BIT             0x3
#define USB2DC_DIEPCTL0_RESERVED_BITWIDTH        2
// EPDis bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL0_EPDIS_MASK               0x40000000
#define USB2DC_DIEPCTL0_EPDIS_SHIFT              30 
#define USB2DC_DIEPCTL0_EPDIS_BIT                0x1
#define USB2DC_DIEPCTL0_EPDIS_BITWIDTH           1
// EPEna bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL0_EPENA_MASK               0x80000000
#define USB2DC_DIEPCTL0_EPENA_SHIFT              31 
#define USB2DC_DIEPCTL0_EPENA_BIT                0x1
#define USB2DC_DIEPCTL0_EPENA_BITWIDTH           1
// DIEPINT0 Register
#define USB2DC_DIEPINT0_OFS                      0x00000908
// XferCompl bitfiled (RO) Reset=0
#define USB2DC_DIEPINT0_XFERCOMPL_MASK           0x1
#define USB2DC_DIEPINT0_XFERCOMPL_SHIFT          0 
#define USB2DC_DIEPINT0_XFERCOMPL_BIT            0x1
#define USB2DC_DIEPINT0_XFERCOMPL_BITWIDTH       1
// EPDisbld bitfiled (RO) Reset=0
#define USB2DC_DIEPINT0_EPDISBLD_MASK            0x2
#define USB2DC_DIEPINT0_EPDISBLD_SHIFT           1 
#define USB2DC_DIEPINT0_EPDISBLD_BIT             0x1
#define USB2DC_DIEPINT0_EPDISBLD_BITWIDTH        1
// AHBErr bitfiled (RO) Reset=0
#define USB2DC_DIEPINT0_AHBERR_MASK              0x4
#define USB2DC_DIEPINT0_AHBERR_SHIFT             2 
#define USB2DC_DIEPINT0_AHBERR_BIT               0x1
#define USB2DC_DIEPINT0_AHBERR_BITWIDTH          1
// TimeOUT bitfiled (RO) Reset=0
#define USB2DC_DIEPINT0_TIMEOUT_MASK             0x8
#define USB2DC_DIEPINT0_TIMEOUT_SHIFT            3 
#define USB2DC_DIEPINT0_TIMEOUT_BIT              0x1
#define USB2DC_DIEPINT0_TIMEOUT_BITWIDTH         1
// INTknTXFEmp bitfiled (RO) Reset=0
#define USB2DC_DIEPINT0_INTKNTXFEMP_MASK         0x10
#define USB2DC_DIEPINT0_INTKNTXFEMP_SHIFT        4 
#define USB2DC_DIEPINT0_INTKNTXFEMP_BIT          0x1
#define USB2DC_DIEPINT0_INTKNTXFEMP_BITWIDTH     1
// INTknEPMis bitfiled (RO) Reset=0
#define USB2DC_DIEPINT0_INTKNEPMIS_MASK          0x20
#define USB2DC_DIEPINT0_INTKNEPMIS_SHIFT         5 
#define USB2DC_DIEPINT0_INTKNEPMIS_BIT           0x1
#define USB2DC_DIEPINT0_INTKNEPMIS_BITWIDTH      1
// INEPNakEff bitfiled (RO) Reset=0
#define USB2DC_DIEPINT0_INEPNAKEFF_MASK          0x40
#define USB2DC_DIEPINT0_INEPNAKEFF_SHIFT         6 
#define USB2DC_DIEPINT0_INEPNAKEFF_BIT           0x1
#define USB2DC_DIEPINT0_INEPNAKEFF_BITWIDTH      1
// TxFEmp bitfiled (RO) Reset=1
#define USB2DC_DIEPINT0_TXFEMP_MASK              0x80
#define USB2DC_DIEPINT0_TXFEMP_SHIFT             7 
#define USB2DC_DIEPINT0_TXFEMP_BIT               0x1
#define USB2DC_DIEPINT0_TXFEMP_BITWIDTH          1
// TxfifoUndrn bitfiled (RO) Reset=0
#define USB2DC_DIEPINT0_TXFIFOUNDRN_MASK         0x100
#define USB2DC_DIEPINT0_TXFIFOUNDRN_SHIFT        8 
#define USB2DC_DIEPINT0_TXFIFOUNDRN_BIT          0x1
#define USB2DC_DIEPINT0_TXFIFOUNDRN_BITWIDTH     1
// BNAIntr bitfiled (RO) Reset=0
#define USB2DC_DIEPINT0_BNAINTR_MASK             0x200
#define USB2DC_DIEPINT0_BNAINTR_SHIFT            9 
#define USB2DC_DIEPINT0_BNAINTR_BIT              0x1
#define USB2DC_DIEPINT0_BNAINTR_BITWIDTH         1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DIEPINT0_RESERVED2_MASK           0x400
#define USB2DC_DIEPINT0_RESERVED2_SHIFT          10 
#define USB2DC_DIEPINT0_RESERVED2_BIT            0x1
#define USB2DC_DIEPINT0_RESERVED2_BITWIDTH       1
// PktDrpSts bitfiled (RO) Reset=0
#define USB2DC_DIEPINT0_PKTDRPSTS_MASK           0x800
#define USB2DC_DIEPINT0_PKTDRPSTS_SHIFT          11 
#define USB2DC_DIEPINT0_PKTDRPSTS_BIT            0x1
#define USB2DC_DIEPINT0_PKTDRPSTS_BITWIDTH       1
// BbleErr bitfiled (RO) Reset=0
#define USB2DC_DIEPINT0_BBLEERR_MASK             0x1000
#define USB2DC_DIEPINT0_BBLEERR_SHIFT            12 
#define USB2DC_DIEPINT0_BBLEERR_BIT              0x1
#define USB2DC_DIEPINT0_BBLEERR_BITWIDTH         1
// NAKIntrpt bitfiled (RO) Reset=0
#define USB2DC_DIEPINT0_NAKINTRPT_MASK           0x2000
#define USB2DC_DIEPINT0_NAKINTRPT_SHIFT          13 
#define USB2DC_DIEPINT0_NAKINTRPT_BIT            0x1
#define USB2DC_DIEPINT0_NAKINTRPT_BITWIDTH       1
// NYETIntrpt bitfiled (RO) Reset=0
#define USB2DC_DIEPINT0_NYETINTRPT_MASK          0x4000
#define USB2DC_DIEPINT0_NYETINTRPT_SHIFT         14 
#define USB2DC_DIEPINT0_NYETINTRPT_BIT           0x1
#define USB2DC_DIEPINT0_NYETINTRPT_BITWIDTH      1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPINT0_RESERVED_MASK            0xFFFF8000
#define USB2DC_DIEPINT0_RESERVED_SHIFT           15 
#define USB2DC_DIEPINT0_RESERVED_BIT             0x1FFFF
#define USB2DC_DIEPINT0_RESERVED_BITWIDTH        17
// DIEPTSIZ0 Register
#define USB2DC_DIEPTSIZ0_OFS                     0x00000910
// XferSize bitfiled (RW) Reset=0
#define USB2DC_DIEPTSIZ0_XFERSIZE_MASK           0x7F
#define USB2DC_DIEPTSIZ0_XFERSIZE_SHIFT          0 
#define USB2DC_DIEPTSIZ0_XFERSIZE_BIT            0x7F
#define USB2DC_DIEPTSIZ0_XFERSIZE_BITWIDTH       7
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DIEPTSIZ0_RESERVED2_MASK          0x7FF80
#define USB2DC_DIEPTSIZ0_RESERVED2_SHIFT         7 
#define USB2DC_DIEPTSIZ0_RESERVED2_BIT           0xFFF
#define USB2DC_DIEPTSIZ0_RESERVED2_BITWIDTH      12
// PktCnt bitfiled (RW) Reset=0
#define USB2DC_DIEPTSIZ0_PKTCNT_MASK             0x180000
#define USB2DC_DIEPTSIZ0_PKTCNT_SHIFT            19 
#define USB2DC_DIEPTSIZ0_PKTCNT_BIT              0x3
#define USB2DC_DIEPTSIZ0_PKTCNT_BITWIDTH         2
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPTSIZ0_RESERVED_MASK           0xFFE00000
#define USB2DC_DIEPTSIZ0_RESERVED_SHIFT          21 
#define USB2DC_DIEPTSIZ0_RESERVED_BIT            0x7FF
#define USB2DC_DIEPTSIZ0_RESERVED_BITWIDTH       11
// DIEPDMA0 Register
#define USB2DC_DIEPDMA0_OFS                      0x00000914
// DMAAddr bitfiled (RW) Reset=0
#define USB2DC_DIEPDMA0_DMAADDR_MASK             0xFFFFFFFF
#define USB2DC_DIEPDMA0_DMAADDR_SHIFT            0 
#define USB2DC_DIEPDMA0_DMAADDR_BIT              0xFFFFFFFF
#define USB2DC_DIEPDMA0_DMAADDR_BITWIDTH         32
// DTXFSTS0 Register
#define USB2DC_DTXFSTS0_OFS                      0x00000918
// INEPTxFSpcAvail bitfiled (RO) Reset=1000000
#define USB2DC_DTXFSTS0_INEPTXFSPCAVAIL_MASK     0xFFFF
#define USB2DC_DTXFSTS0_INEPTXFSPCAVAIL_SHIFT    0 
#define USB2DC_DTXFSTS0_INEPTXFSPCAVAIL_BIT      0xFFFF
#define USB2DC_DTXFSTS0_INEPTXFSPCAVAIL_BITWIDTH 16
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DTXFSTS0_RESERVED_MASK            0xFFFF0000
#define USB2DC_DTXFSTS0_RESERVED_SHIFT           16 
#define USB2DC_DTXFSTS0_RESERVED_BIT             0xFFFF
#define USB2DC_DTXFSTS0_RESERVED_BITWIDTH        16
// DIEPDMAB0 Register
#define USB2DC_DIEPDMAB0_OFS                     0x0000091C
// DMABufferAddr bitfiled (RO) Reset=0
#define USB2DC_DIEPDMAB0_DMABUFFERADDR_MASK      0xFFFFFFFF
#define USB2DC_DIEPDMAB0_DMABUFFERADDR_SHIFT     0 
#define USB2DC_DIEPDMAB0_DMABUFFERADDR_BIT       0xFFFFFFFF
#define USB2DC_DIEPDMAB0_DMABUFFERADDR_BITWIDTH  32
// DIEPCTL1 Register
#define USB2DC_DIEPCTL1_OFS                      0x00000920
// MPS bitfiled (RW) Reset=0
#define USB2DC_DIEPCTL1_MPS_MASK                 0x7FF
#define USB2DC_DIEPCTL1_MPS_SHIFT                0 
#define USB2DC_DIEPCTL1_MPS_BIT                  0x7FF
#define USB2DC_DIEPCTL1_MPS_BITWIDTH             11
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL1_RESERVED2_MASK           0x7800
#define USB2DC_DIEPCTL1_RESERVED2_SHIFT          11 
#define USB2DC_DIEPCTL1_RESERVED2_BIT            0xF
#define USB2DC_DIEPCTL1_RESERVED2_BITWIDTH       4
// USBActEP bitfiled (RW) Reset=0
#define USB2DC_DIEPCTL1_USBACTEP_MASK            0x8000
#define USB2DC_DIEPCTL1_USBACTEP_SHIFT           15 
#define USB2DC_DIEPCTL1_USBACTEP_BIT             0x1
#define USB2DC_DIEPCTL1_USBACTEP_BITWIDTH        1
// DPID bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL1_DPID_MASK                0x10000
#define USB2DC_DIEPCTL1_DPID_SHIFT               16 
#define USB2DC_DIEPCTL1_DPID_BIT                 0x1
#define USB2DC_DIEPCTL1_DPID_BITWIDTH            1
// NAKSts bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL1_NAKSTS_MASK              0x20000
#define USB2DC_DIEPCTL1_NAKSTS_SHIFT             17 
#define USB2DC_DIEPCTL1_NAKSTS_BIT               0x1
#define USB2DC_DIEPCTL1_NAKSTS_BITWIDTH          1
// EPType bitfiled (RW) Reset=0
#define USB2DC_DIEPCTL1_EPTYPE_MASK              0xC0000
#define USB2DC_DIEPCTL1_EPTYPE_SHIFT             18 
#define USB2DC_DIEPCTL1_EPTYPE_BIT               0x3
#define USB2DC_DIEPCTL1_EPTYPE_BITWIDTH          2
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL1_RESERVED_MASK            0x100000
#define USB2DC_DIEPCTL1_RESERVED_SHIFT           20 
#define USB2DC_DIEPCTL1_RESERVED_BIT             0x1
#define USB2DC_DIEPCTL1_RESERVED_BITWIDTH        1
// Stall bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL1_STALL_MASK               0x200000
#define USB2DC_DIEPCTL1_STALL_SHIFT              21 
#define USB2DC_DIEPCTL1_STALL_BIT                0x1
#define USB2DC_DIEPCTL1_STALL_BITWIDTH           1
// TxFNum bitfiled (RW) Reset=0
#define USB2DC_DIEPCTL1_TXFNUM_MASK              0x3C00000
#define USB2DC_DIEPCTL1_TXFNUM_SHIFT             22 
#define USB2DC_DIEPCTL1_TXFNUM_BIT               0xF
#define USB2DC_DIEPCTL1_TXFNUM_BITWIDTH          4
// CNAK bitfiled (WO) Reset=0
#define USB2DC_DIEPCTL1_CNAK_MASK                0x4000000
#define USB2DC_DIEPCTL1_CNAK_SHIFT               26 
#define USB2DC_DIEPCTL1_CNAK_BIT                 0x1
#define USB2DC_DIEPCTL1_CNAK_BITWIDTH            1
// SNAK bitfiled (WO) Reset=0
#define USB2DC_DIEPCTL1_SNAK_MASK                0x8000000
#define USB2DC_DIEPCTL1_SNAK_SHIFT               27 
#define USB2DC_DIEPCTL1_SNAK_BIT                 0x1
#define USB2DC_DIEPCTL1_SNAK_BITWIDTH            1
// SetD0PID bitfiled (WO) Reset=0
#define USB2DC_DIEPCTL1_SETD0PID_MASK            0x10000000
#define USB2DC_DIEPCTL1_SETD0PID_SHIFT           28 
#define USB2DC_DIEPCTL1_SETD0PID_BIT             0x1
#define USB2DC_DIEPCTL1_SETD0PID_BITWIDTH        1
// SetD1PID bitfiled (WO) Reset=0
#define USB2DC_DIEPCTL1_SETD1PID_MASK            0x20000000
#define USB2DC_DIEPCTL1_SETD1PID_SHIFT           29 
#define USB2DC_DIEPCTL1_SETD1PID_BIT             0x1
#define USB2DC_DIEPCTL1_SETD1PID_BITWIDTH        1
// EPDis bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL1_EPDIS_MASK               0x40000000
#define USB2DC_DIEPCTL1_EPDIS_SHIFT              30 
#define USB2DC_DIEPCTL1_EPDIS_BIT                0x1
#define USB2DC_DIEPCTL1_EPDIS_BITWIDTH           1
// EPEna bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL1_EPENA_MASK               0x80000000
#define USB2DC_DIEPCTL1_EPENA_SHIFT              31 
#define USB2DC_DIEPCTL1_EPENA_BIT                0x1
#define USB2DC_DIEPCTL1_EPENA_BITWIDTH           1
// DIEPINT1 Register
#define USB2DC_DIEPINT1_OFS                      0x00000928
// XferCompl bitfiled (RO) Reset=0
#define USB2DC_DIEPINT1_XFERCOMPL_MASK           0x1
#define USB2DC_DIEPINT1_XFERCOMPL_SHIFT          0 
#define USB2DC_DIEPINT1_XFERCOMPL_BIT            0x1
#define USB2DC_DIEPINT1_XFERCOMPL_BITWIDTH       1
// EPDisbld bitfiled (RO) Reset=0
#define USB2DC_DIEPINT1_EPDISBLD_MASK            0x2
#define USB2DC_DIEPINT1_EPDISBLD_SHIFT           1 
#define USB2DC_DIEPINT1_EPDISBLD_BIT             0x1
#define USB2DC_DIEPINT1_EPDISBLD_BITWIDTH        1
// AHBErr bitfiled (RO) Reset=0
#define USB2DC_DIEPINT1_AHBERR_MASK              0x4
#define USB2DC_DIEPINT1_AHBERR_SHIFT             2 
#define USB2DC_DIEPINT1_AHBERR_BIT               0x1
#define USB2DC_DIEPINT1_AHBERR_BITWIDTH          1
// TimeOUT bitfiled (RO) Reset=0
#define USB2DC_DIEPINT1_TIMEOUT_MASK             0x8
#define USB2DC_DIEPINT1_TIMEOUT_SHIFT            3 
#define USB2DC_DIEPINT1_TIMEOUT_BIT              0x1
#define USB2DC_DIEPINT1_TIMEOUT_BITWIDTH         1
// INTknTXFEmp bitfiled (RO) Reset=0
#define USB2DC_DIEPINT1_INTKNTXFEMP_MASK         0x10
#define USB2DC_DIEPINT1_INTKNTXFEMP_SHIFT        4 
#define USB2DC_DIEPINT1_INTKNTXFEMP_BIT          0x1
#define USB2DC_DIEPINT1_INTKNTXFEMP_BITWIDTH     1
// INTknEPMis bitfiled (RO) Reset=0
#define USB2DC_DIEPINT1_INTKNEPMIS_MASK          0x20
#define USB2DC_DIEPINT1_INTKNEPMIS_SHIFT         5 
#define USB2DC_DIEPINT1_INTKNEPMIS_BIT           0x1
#define USB2DC_DIEPINT1_INTKNEPMIS_BITWIDTH      1
// INEPNakEff bitfiled (RO) Reset=0
#define USB2DC_DIEPINT1_INEPNAKEFF_MASK          0x40
#define USB2DC_DIEPINT1_INEPNAKEFF_SHIFT         6 
#define USB2DC_DIEPINT1_INEPNAKEFF_BIT           0x1
#define USB2DC_DIEPINT1_INEPNAKEFF_BITWIDTH      1
// TxFEmp bitfiled (RO) Reset=1
#define USB2DC_DIEPINT1_TXFEMP_MASK              0x80
#define USB2DC_DIEPINT1_TXFEMP_SHIFT             7 
#define USB2DC_DIEPINT1_TXFEMP_BIT               0x1
#define USB2DC_DIEPINT1_TXFEMP_BITWIDTH          1
// TxfifoUndrn bitfiled (RO) Reset=0
#define USB2DC_DIEPINT1_TXFIFOUNDRN_MASK         0x100
#define USB2DC_DIEPINT1_TXFIFOUNDRN_SHIFT        8 
#define USB2DC_DIEPINT1_TXFIFOUNDRN_BIT          0x1
#define USB2DC_DIEPINT1_TXFIFOUNDRN_BITWIDTH     1
// BNAIntr bitfiled (RO) Reset=0
#define USB2DC_DIEPINT1_BNAINTR_MASK             0x200
#define USB2DC_DIEPINT1_BNAINTR_SHIFT            9 
#define USB2DC_DIEPINT1_BNAINTR_BIT              0x1
#define USB2DC_DIEPINT1_BNAINTR_BITWIDTH         1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DIEPINT1_RESERVED2_MASK           0x400
#define USB2DC_DIEPINT1_RESERVED2_SHIFT          10 
#define USB2DC_DIEPINT1_RESERVED2_BIT            0x1
#define USB2DC_DIEPINT1_RESERVED2_BITWIDTH       1
// PktDrpSts bitfiled (RO) Reset=0
#define USB2DC_DIEPINT1_PKTDRPSTS_MASK           0x800
#define USB2DC_DIEPINT1_PKTDRPSTS_SHIFT          11 
#define USB2DC_DIEPINT1_PKTDRPSTS_BIT            0x1
#define USB2DC_DIEPINT1_PKTDRPSTS_BITWIDTH       1
// BbleErr bitfiled (RO) Reset=0
#define USB2DC_DIEPINT1_BBLEERR_MASK             0x1000
#define USB2DC_DIEPINT1_BBLEERR_SHIFT            12 
#define USB2DC_DIEPINT1_BBLEERR_BIT              0x1
#define USB2DC_DIEPINT1_BBLEERR_BITWIDTH         1
// NAKIntrpt bitfiled (RO) Reset=0
#define USB2DC_DIEPINT1_NAKINTRPT_MASK           0x2000
#define USB2DC_DIEPINT1_NAKINTRPT_SHIFT          13 
#define USB2DC_DIEPINT1_NAKINTRPT_BIT            0x1
#define USB2DC_DIEPINT1_NAKINTRPT_BITWIDTH       1
// NYETIntrpt bitfiled (RO) Reset=0
#define USB2DC_DIEPINT1_NYETINTRPT_MASK          0x4000
#define USB2DC_DIEPINT1_NYETINTRPT_SHIFT         14 
#define USB2DC_DIEPINT1_NYETINTRPT_BIT           0x1
#define USB2DC_DIEPINT1_NYETINTRPT_BITWIDTH      1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPINT1_RESERVED_MASK            0xFFFF8000
#define USB2DC_DIEPINT1_RESERVED_SHIFT           15 
#define USB2DC_DIEPINT1_RESERVED_BIT             0x1FFFF
#define USB2DC_DIEPINT1_RESERVED_BITWIDTH        17
// DIEPTSIZ1 Register
#define USB2DC_DIEPTSIZ1_OFS                     0x00000930
// XferSize bitfiled (RW) Reset=0
#define USB2DC_DIEPTSIZ1_XFERSIZE_MASK           0x7FFFF
#define USB2DC_DIEPTSIZ1_XFERSIZE_SHIFT          0 
#define USB2DC_DIEPTSIZ1_XFERSIZE_BIT            0x7FFFF
#define USB2DC_DIEPTSIZ1_XFERSIZE_BITWIDTH       19
// PktCnt bitfiled (RW) Reset=0
#define USB2DC_DIEPTSIZ1_PKTCNT_MASK             0x1FF80000
#define USB2DC_DIEPTSIZ1_PKTCNT_SHIFT            19 
#define USB2DC_DIEPTSIZ1_PKTCNT_BIT              0x3FF
#define USB2DC_DIEPTSIZ1_PKTCNT_BITWIDTH         10
// MC bitfiled (RW) Reset=0
#define USB2DC_DIEPTSIZ1_MC_MASK                 0x60000000
#define USB2DC_DIEPTSIZ1_MC_SHIFT                29 
#define USB2DC_DIEPTSIZ1_MC_BIT                  0x3
#define USB2DC_DIEPTSIZ1_MC_BITWIDTH             2
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPTSIZ1_RESERVED_MASK           0x80000000
#define USB2DC_DIEPTSIZ1_RESERVED_SHIFT          31 
#define USB2DC_DIEPTSIZ1_RESERVED_BIT            0x1
#define USB2DC_DIEPTSIZ1_RESERVED_BITWIDTH       1
// DIEPDMA1 Register
#define USB2DC_DIEPDMA1_OFS                      0x00000934
// DMAAddr bitfiled (RW) Reset=0
#define USB2DC_DIEPDMA1_DMAADDR_MASK             0xFFFFFFFF
#define USB2DC_DIEPDMA1_DMAADDR_SHIFT            0 
#define USB2DC_DIEPDMA1_DMAADDR_BIT              0xFFFFFFFF
#define USB2DC_DIEPDMA1_DMAADDR_BITWIDTH         32
// DTXFSTS1 Register
#define USB2DC_DTXFSTS1_OFS                      0x00000938
// INEPTxFSpcAvail bitfiled (RO) Reset=1100000000
#define USB2DC_DTXFSTS1_INEPTXFSPCAVAIL_MASK     0xFFFF
#define USB2DC_DTXFSTS1_INEPTXFSPCAVAIL_SHIFT    0 
#define USB2DC_DTXFSTS1_INEPTXFSPCAVAIL_BIT      0xFFFF
#define USB2DC_DTXFSTS1_INEPTXFSPCAVAIL_BITWIDTH 16
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DTXFSTS1_RESERVED_MASK            0xFFFF0000
#define USB2DC_DTXFSTS1_RESERVED_SHIFT           16 
#define USB2DC_DTXFSTS1_RESERVED_BIT             0xFFFF
#define USB2DC_DTXFSTS1_RESERVED_BITWIDTH        16
// DIEPDMAB1 Register
#define USB2DC_DIEPDMAB1_OFS                     0x0000093C
// DMABufferAddr bitfiled (RO) Reset=0
#define USB2DC_DIEPDMAB1_DMABUFFERADDR_MASK      0xFFFFFFFF
#define USB2DC_DIEPDMAB1_DMABUFFERADDR_SHIFT     0 
#define USB2DC_DIEPDMAB1_DMABUFFERADDR_BIT       0xFFFFFFFF
#define USB2DC_DIEPDMAB1_DMABUFFERADDR_BITWIDTH  32
// DIEPCTL2 Register
#define USB2DC_DIEPCTL2_OFS                      0x00000940
// MPS bitfiled (RW) Reset=0
#define USB2DC_DIEPCTL2_MPS_MASK                 0x7FF
#define USB2DC_DIEPCTL2_MPS_SHIFT                0 
#define USB2DC_DIEPCTL2_MPS_BIT                  0x7FF
#define USB2DC_DIEPCTL2_MPS_BITWIDTH             11
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL2_RESERVED2_MASK           0x7800
#define USB2DC_DIEPCTL2_RESERVED2_SHIFT          11 
#define USB2DC_DIEPCTL2_RESERVED2_BIT            0xF
#define USB2DC_DIEPCTL2_RESERVED2_BITWIDTH       4
// USBActEP bitfiled (RW) Reset=0
#define USB2DC_DIEPCTL2_USBACTEP_MASK            0x8000
#define USB2DC_DIEPCTL2_USBACTEP_SHIFT           15 
#define USB2DC_DIEPCTL2_USBACTEP_BIT             0x1
#define USB2DC_DIEPCTL2_USBACTEP_BITWIDTH        1
// DPID bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL2_DPID_MASK                0x10000
#define USB2DC_DIEPCTL2_DPID_SHIFT               16 
#define USB2DC_DIEPCTL2_DPID_BIT                 0x1
#define USB2DC_DIEPCTL2_DPID_BITWIDTH            1
// NAKSts bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL2_NAKSTS_MASK              0x20000
#define USB2DC_DIEPCTL2_NAKSTS_SHIFT             17 
#define USB2DC_DIEPCTL2_NAKSTS_BIT               0x1
#define USB2DC_DIEPCTL2_NAKSTS_BITWIDTH          1
// EPType bitfiled (RW) Reset=0
#define USB2DC_DIEPCTL2_EPTYPE_MASK              0xC0000
#define USB2DC_DIEPCTL2_EPTYPE_SHIFT             18 
#define USB2DC_DIEPCTL2_EPTYPE_BIT               0x3
#define USB2DC_DIEPCTL2_EPTYPE_BITWIDTH          2
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL2_RESERVED_MASK            0x100000
#define USB2DC_DIEPCTL2_RESERVED_SHIFT           20 
#define USB2DC_DIEPCTL2_RESERVED_BIT             0x1
#define USB2DC_DIEPCTL2_RESERVED_BITWIDTH        1
// Stall bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL2_STALL_MASK               0x200000
#define USB2DC_DIEPCTL2_STALL_SHIFT              21 
#define USB2DC_DIEPCTL2_STALL_BIT                0x1
#define USB2DC_DIEPCTL2_STALL_BITWIDTH           1
// TxFNum bitfiled (RW) Reset=0
#define USB2DC_DIEPCTL2_TXFNUM_MASK              0x3C00000
#define USB2DC_DIEPCTL2_TXFNUM_SHIFT             22 
#define USB2DC_DIEPCTL2_TXFNUM_BIT               0xF
#define USB2DC_DIEPCTL2_TXFNUM_BITWIDTH          4
// CNAK bitfiled (WO) Reset=0
#define USB2DC_DIEPCTL2_CNAK_MASK                0x4000000
#define USB2DC_DIEPCTL2_CNAK_SHIFT               26 
#define USB2DC_DIEPCTL2_CNAK_BIT                 0x1
#define USB2DC_DIEPCTL2_CNAK_BITWIDTH            1
// SNAK bitfiled (WO) Reset=0
#define USB2DC_DIEPCTL2_SNAK_MASK                0x8000000
#define USB2DC_DIEPCTL2_SNAK_SHIFT               27 
#define USB2DC_DIEPCTL2_SNAK_BIT                 0x1
#define USB2DC_DIEPCTL2_SNAK_BITWIDTH            1
// SetD0PID bitfiled (WO) Reset=0
#define USB2DC_DIEPCTL2_SETD0PID_MASK            0x10000000
#define USB2DC_DIEPCTL2_SETD0PID_SHIFT           28 
#define USB2DC_DIEPCTL2_SETD0PID_BIT             0x1
#define USB2DC_DIEPCTL2_SETD0PID_BITWIDTH        1
// SetD1PID bitfiled (WO) Reset=0
#define USB2DC_DIEPCTL2_SETD1PID_MASK            0x20000000
#define USB2DC_DIEPCTL2_SETD1PID_SHIFT           29 
#define USB2DC_DIEPCTL2_SETD1PID_BIT             0x1
#define USB2DC_DIEPCTL2_SETD1PID_BITWIDTH        1
// EPDis bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL2_EPDIS_MASK               0x40000000
#define USB2DC_DIEPCTL2_EPDIS_SHIFT              30 
#define USB2DC_DIEPCTL2_EPDIS_BIT                0x1
#define USB2DC_DIEPCTL2_EPDIS_BITWIDTH           1
// EPEna bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL2_EPENA_MASK               0x80000000
#define USB2DC_DIEPCTL2_EPENA_SHIFT              31 
#define USB2DC_DIEPCTL2_EPENA_BIT                0x1
#define USB2DC_DIEPCTL2_EPENA_BITWIDTH           1
// DIEPINT2 Register
#define USB2DC_DIEPINT2_OFS                      0x00000948
// XferCompl bitfiled (RO) Reset=0
#define USB2DC_DIEPINT2_XFERCOMPL_MASK           0x1
#define USB2DC_DIEPINT2_XFERCOMPL_SHIFT          0 
#define USB2DC_DIEPINT2_XFERCOMPL_BIT            0x1
#define USB2DC_DIEPINT2_XFERCOMPL_BITWIDTH       1
// EPDisbld bitfiled (RO) Reset=0
#define USB2DC_DIEPINT2_EPDISBLD_MASK            0x2
#define USB2DC_DIEPINT2_EPDISBLD_SHIFT           1 
#define USB2DC_DIEPINT2_EPDISBLD_BIT             0x1
#define USB2DC_DIEPINT2_EPDISBLD_BITWIDTH        1
// AHBErr bitfiled (RO) Reset=0
#define USB2DC_DIEPINT2_AHBERR_MASK              0x4
#define USB2DC_DIEPINT2_AHBERR_SHIFT             2 
#define USB2DC_DIEPINT2_AHBERR_BIT               0x1
#define USB2DC_DIEPINT2_AHBERR_BITWIDTH          1
// TimeOUT bitfiled (RO) Reset=0
#define USB2DC_DIEPINT2_TIMEOUT_MASK             0x8
#define USB2DC_DIEPINT2_TIMEOUT_SHIFT            3 
#define USB2DC_DIEPINT2_TIMEOUT_BIT              0x1
#define USB2DC_DIEPINT2_TIMEOUT_BITWIDTH         1
// INTknTXFEmp bitfiled (RO) Reset=0
#define USB2DC_DIEPINT2_INTKNTXFEMP_MASK         0x10
#define USB2DC_DIEPINT2_INTKNTXFEMP_SHIFT        4 
#define USB2DC_DIEPINT2_INTKNTXFEMP_BIT          0x1
#define USB2DC_DIEPINT2_INTKNTXFEMP_BITWIDTH     1
// INTknEPMis bitfiled (RO) Reset=0
#define USB2DC_DIEPINT2_INTKNEPMIS_MASK          0x20
#define USB2DC_DIEPINT2_INTKNEPMIS_SHIFT         5 
#define USB2DC_DIEPINT2_INTKNEPMIS_BIT           0x1
#define USB2DC_DIEPINT2_INTKNEPMIS_BITWIDTH      1
// INEPNakEff bitfiled (RO) Reset=0
#define USB2DC_DIEPINT2_INEPNAKEFF_MASK          0x40
#define USB2DC_DIEPINT2_INEPNAKEFF_SHIFT         6 
#define USB2DC_DIEPINT2_INEPNAKEFF_BIT           0x1
#define USB2DC_DIEPINT2_INEPNAKEFF_BITWIDTH      1
// TxFEmp bitfiled (RO) Reset=1
#define USB2DC_DIEPINT2_TXFEMP_MASK              0x80
#define USB2DC_DIEPINT2_TXFEMP_SHIFT             7 
#define USB2DC_DIEPINT2_TXFEMP_BIT               0x1
#define USB2DC_DIEPINT2_TXFEMP_BITWIDTH          1
// TxfifoUndrn bitfiled (RO) Reset=0
#define USB2DC_DIEPINT2_TXFIFOUNDRN_MASK         0x100
#define USB2DC_DIEPINT2_TXFIFOUNDRN_SHIFT        8 
#define USB2DC_DIEPINT2_TXFIFOUNDRN_BIT          0x1
#define USB2DC_DIEPINT2_TXFIFOUNDRN_BITWIDTH     1
// BNAIntr bitfiled (RO) Reset=0
#define USB2DC_DIEPINT2_BNAINTR_MASK             0x200
#define USB2DC_DIEPINT2_BNAINTR_SHIFT            9 
#define USB2DC_DIEPINT2_BNAINTR_BIT              0x1
#define USB2DC_DIEPINT2_BNAINTR_BITWIDTH         1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DIEPINT2_RESERVED2_MASK           0x400
#define USB2DC_DIEPINT2_RESERVED2_SHIFT          10 
#define USB2DC_DIEPINT2_RESERVED2_BIT            0x1
#define USB2DC_DIEPINT2_RESERVED2_BITWIDTH       1
// PktDrpSts bitfiled (RO) Reset=0
#define USB2DC_DIEPINT2_PKTDRPSTS_MASK           0x800
#define USB2DC_DIEPINT2_PKTDRPSTS_SHIFT          11 
#define USB2DC_DIEPINT2_PKTDRPSTS_BIT            0x1
#define USB2DC_DIEPINT2_PKTDRPSTS_BITWIDTH       1
// BbleErr bitfiled (RO) Reset=0
#define USB2DC_DIEPINT2_BBLEERR_MASK             0x1000
#define USB2DC_DIEPINT2_BBLEERR_SHIFT            12 
#define USB2DC_DIEPINT2_BBLEERR_BIT              0x1
#define USB2DC_DIEPINT2_BBLEERR_BITWIDTH         1
// NAKIntrpt bitfiled (RO) Reset=0
#define USB2DC_DIEPINT2_NAKINTRPT_MASK           0x2000
#define USB2DC_DIEPINT2_NAKINTRPT_SHIFT          13 
#define USB2DC_DIEPINT2_NAKINTRPT_BIT            0x1
#define USB2DC_DIEPINT2_NAKINTRPT_BITWIDTH       1
// NYETIntrpt bitfiled (RO) Reset=0
#define USB2DC_DIEPINT2_NYETINTRPT_MASK          0x4000
#define USB2DC_DIEPINT2_NYETINTRPT_SHIFT         14 
#define USB2DC_DIEPINT2_NYETINTRPT_BIT           0x1
#define USB2DC_DIEPINT2_NYETINTRPT_BITWIDTH      1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPINT2_RESERVED_MASK            0xFFFF8000
#define USB2DC_DIEPINT2_RESERVED_SHIFT           15 
#define USB2DC_DIEPINT2_RESERVED_BIT             0x1FFFF
#define USB2DC_DIEPINT2_RESERVED_BITWIDTH        17
// DIEPTSIZ2 Register
#define USB2DC_DIEPTSIZ2_OFS                     0x00000950
// XferSize bitfiled (RW) Reset=0
#define USB2DC_DIEPTSIZ2_XFERSIZE_MASK           0x7FFFF
#define USB2DC_DIEPTSIZ2_XFERSIZE_SHIFT          0 
#define USB2DC_DIEPTSIZ2_XFERSIZE_BIT            0x7FFFF
#define USB2DC_DIEPTSIZ2_XFERSIZE_BITWIDTH       19
// PktCnt bitfiled (RW) Reset=0
#define USB2DC_DIEPTSIZ2_PKTCNT_MASK             0x1FF80000
#define USB2DC_DIEPTSIZ2_PKTCNT_SHIFT            19 
#define USB2DC_DIEPTSIZ2_PKTCNT_BIT              0x3FF
#define USB2DC_DIEPTSIZ2_PKTCNT_BITWIDTH         10
// MC bitfiled (RW) Reset=0
#define USB2DC_DIEPTSIZ2_MC_MASK                 0x60000000
#define USB2DC_DIEPTSIZ2_MC_SHIFT                29 
#define USB2DC_DIEPTSIZ2_MC_BIT                  0x3
#define USB2DC_DIEPTSIZ2_MC_BITWIDTH             2
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPTSIZ2_RESERVED_MASK           0x80000000
#define USB2DC_DIEPTSIZ2_RESERVED_SHIFT          31 
#define USB2DC_DIEPTSIZ2_RESERVED_BIT            0x1
#define USB2DC_DIEPTSIZ2_RESERVED_BITWIDTH       1
// DIEPDMA2 Register
#define USB2DC_DIEPDMA2_OFS                      0x00000954
// DMAAddr bitfiled (RW) Reset=0
#define USB2DC_DIEPDMA2_DMAADDR_MASK             0xFFFFFFFF
#define USB2DC_DIEPDMA2_DMAADDR_SHIFT            0 
#define USB2DC_DIEPDMA2_DMAADDR_BIT              0xFFFFFFFF
#define USB2DC_DIEPDMA2_DMAADDR_BITWIDTH         32
// DTXFSTS2 Register
#define USB2DC_DTXFSTS2_OFS                      0x00000958
// INEPTxFSpcAvail bitfiled (RO) Reset=1100000000
#define USB2DC_DTXFSTS2_INEPTXFSPCAVAIL_MASK     0xFFFF
#define USB2DC_DTXFSTS2_INEPTXFSPCAVAIL_SHIFT    0 
#define USB2DC_DTXFSTS2_INEPTXFSPCAVAIL_BIT      0xFFFF
#define USB2DC_DTXFSTS2_INEPTXFSPCAVAIL_BITWIDTH 16
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DTXFSTS2_RESERVED_MASK            0xFFFF0000
#define USB2DC_DTXFSTS2_RESERVED_SHIFT           16 
#define USB2DC_DTXFSTS2_RESERVED_BIT             0xFFFF
#define USB2DC_DTXFSTS2_RESERVED_BITWIDTH        16
// DIEPDMAB2 Register
#define USB2DC_DIEPDMAB2_OFS                     0x0000095C
// DMABufferAddr bitfiled (RO) Reset=0
#define USB2DC_DIEPDMAB2_DMABUFFERADDR_MASK      0xFFFFFFFF
#define USB2DC_DIEPDMAB2_DMABUFFERADDR_SHIFT     0 
#define USB2DC_DIEPDMAB2_DMABUFFERADDR_BIT       0xFFFFFFFF
#define USB2DC_DIEPDMAB2_DMABUFFERADDR_BITWIDTH  32
// DIEPCTL3 Register
#define USB2DC_DIEPCTL3_OFS                      0x00000960
// MPS bitfiled (RW) Reset=0
#define USB2DC_DIEPCTL3_MPS_MASK                 0x7FF
#define USB2DC_DIEPCTL3_MPS_SHIFT                0 
#define USB2DC_DIEPCTL3_MPS_BIT                  0x7FF
#define USB2DC_DIEPCTL3_MPS_BITWIDTH             11
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL3_RESERVED2_MASK           0x7800
#define USB2DC_DIEPCTL3_RESERVED2_SHIFT          11 
#define USB2DC_DIEPCTL3_RESERVED2_BIT            0xF
#define USB2DC_DIEPCTL3_RESERVED2_BITWIDTH       4
// USBActEP bitfiled (RW) Reset=0
#define USB2DC_DIEPCTL3_USBACTEP_MASK            0x8000
#define USB2DC_DIEPCTL3_USBACTEP_SHIFT           15 
#define USB2DC_DIEPCTL3_USBACTEP_BIT             0x1
#define USB2DC_DIEPCTL3_USBACTEP_BITWIDTH        1
// DPID bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL3_DPID_MASK                0x10000
#define USB2DC_DIEPCTL3_DPID_SHIFT               16 
#define USB2DC_DIEPCTL3_DPID_BIT                 0x1
#define USB2DC_DIEPCTL3_DPID_BITWIDTH            1
// NAKSts bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL3_NAKSTS_MASK              0x20000
#define USB2DC_DIEPCTL3_NAKSTS_SHIFT             17 
#define USB2DC_DIEPCTL3_NAKSTS_BIT               0x1
#define USB2DC_DIEPCTL3_NAKSTS_BITWIDTH          1
// EPType bitfiled (RW) Reset=0
#define USB2DC_DIEPCTL3_EPTYPE_MASK              0xC0000
#define USB2DC_DIEPCTL3_EPTYPE_SHIFT             18 
#define USB2DC_DIEPCTL3_EPTYPE_BIT               0x3
#define USB2DC_DIEPCTL3_EPTYPE_BITWIDTH          2
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL3_RESERVED_MASK            0x100000
#define USB2DC_DIEPCTL3_RESERVED_SHIFT           20 
#define USB2DC_DIEPCTL3_RESERVED_BIT             0x1
#define USB2DC_DIEPCTL3_RESERVED_BITWIDTH        1
// Stall bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL3_STALL_MASK               0x200000
#define USB2DC_DIEPCTL3_STALL_SHIFT              21 
#define USB2DC_DIEPCTL3_STALL_BIT                0x1
#define USB2DC_DIEPCTL3_STALL_BITWIDTH           1
// TxFNum bitfiled (RW) Reset=0
#define USB2DC_DIEPCTL3_TXFNUM_MASK              0x3C00000
#define USB2DC_DIEPCTL3_TXFNUM_SHIFT             22 
#define USB2DC_DIEPCTL3_TXFNUM_BIT               0xF
#define USB2DC_DIEPCTL3_TXFNUM_BITWIDTH          4
// CNAK bitfiled (WO) Reset=0
#define USB2DC_DIEPCTL3_CNAK_MASK                0x4000000
#define USB2DC_DIEPCTL3_CNAK_SHIFT               26 
#define USB2DC_DIEPCTL3_CNAK_BIT                 0x1
#define USB2DC_DIEPCTL3_CNAK_BITWIDTH            1
// SNAK bitfiled (WO) Reset=0
#define USB2DC_DIEPCTL3_SNAK_MASK                0x8000000
#define USB2DC_DIEPCTL3_SNAK_SHIFT               27 
#define USB2DC_DIEPCTL3_SNAK_BIT                 0x1
#define USB2DC_DIEPCTL3_SNAK_BITWIDTH            1
// SetD0PID bitfiled (WO) Reset=0
#define USB2DC_DIEPCTL3_SETD0PID_MASK            0x10000000
#define USB2DC_DIEPCTL3_SETD0PID_SHIFT           28 
#define USB2DC_DIEPCTL3_SETD0PID_BIT             0x1
#define USB2DC_DIEPCTL3_SETD0PID_BITWIDTH        1
// SetD1PID bitfiled (WO) Reset=0
#define USB2DC_DIEPCTL3_SETD1PID_MASK            0x20000000
#define USB2DC_DIEPCTL3_SETD1PID_SHIFT           29 
#define USB2DC_DIEPCTL3_SETD1PID_BIT             0x1
#define USB2DC_DIEPCTL3_SETD1PID_BITWIDTH        1
// EPDis bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL3_EPDIS_MASK               0x40000000
#define USB2DC_DIEPCTL3_EPDIS_SHIFT              30 
#define USB2DC_DIEPCTL3_EPDIS_BIT                0x1
#define USB2DC_DIEPCTL3_EPDIS_BITWIDTH           1
// EPEna bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL3_EPENA_MASK               0x80000000
#define USB2DC_DIEPCTL3_EPENA_SHIFT              31 
#define USB2DC_DIEPCTL3_EPENA_BIT                0x1
#define USB2DC_DIEPCTL3_EPENA_BITWIDTH           1
// DIEPINT3 Register
#define USB2DC_DIEPINT3_OFS                      0x00000968
// XferCompl bitfiled (RO) Reset=0
#define USB2DC_DIEPINT3_XFERCOMPL_MASK           0x1
#define USB2DC_DIEPINT3_XFERCOMPL_SHIFT          0 
#define USB2DC_DIEPINT3_XFERCOMPL_BIT            0x1
#define USB2DC_DIEPINT3_XFERCOMPL_BITWIDTH       1
// EPDisbld bitfiled (RO) Reset=0
#define USB2DC_DIEPINT3_EPDISBLD_MASK            0x2
#define USB2DC_DIEPINT3_EPDISBLD_SHIFT           1 
#define USB2DC_DIEPINT3_EPDISBLD_BIT             0x1
#define USB2DC_DIEPINT3_EPDISBLD_BITWIDTH        1
// AHBErr bitfiled (RO) Reset=0
#define USB2DC_DIEPINT3_AHBERR_MASK              0x4
#define USB2DC_DIEPINT3_AHBERR_SHIFT             2 
#define USB2DC_DIEPINT3_AHBERR_BIT               0x1
#define USB2DC_DIEPINT3_AHBERR_BITWIDTH          1
// TimeOUT bitfiled (RO) Reset=0
#define USB2DC_DIEPINT3_TIMEOUT_MASK             0x8
#define USB2DC_DIEPINT3_TIMEOUT_SHIFT            3 
#define USB2DC_DIEPINT3_TIMEOUT_BIT              0x1
#define USB2DC_DIEPINT3_TIMEOUT_BITWIDTH         1
// INTknTXFEmp bitfiled (RO) Reset=0
#define USB2DC_DIEPINT3_INTKNTXFEMP_MASK         0x10
#define USB2DC_DIEPINT3_INTKNTXFEMP_SHIFT        4 
#define USB2DC_DIEPINT3_INTKNTXFEMP_BIT          0x1
#define USB2DC_DIEPINT3_INTKNTXFEMP_BITWIDTH     1
// INTknEPMis bitfiled (RO) Reset=0
#define USB2DC_DIEPINT3_INTKNEPMIS_MASK          0x20
#define USB2DC_DIEPINT3_INTKNEPMIS_SHIFT         5 
#define USB2DC_DIEPINT3_INTKNEPMIS_BIT           0x1
#define USB2DC_DIEPINT3_INTKNEPMIS_BITWIDTH      1
// INEPNakEff bitfiled (RO) Reset=0
#define USB2DC_DIEPINT3_INEPNAKEFF_MASK          0x40
#define USB2DC_DIEPINT3_INEPNAKEFF_SHIFT         6 
#define USB2DC_DIEPINT3_INEPNAKEFF_BIT           0x1
#define USB2DC_DIEPINT3_INEPNAKEFF_BITWIDTH      1
// TxFEmp bitfiled (RO) Reset=1
#define USB2DC_DIEPINT3_TXFEMP_MASK              0x80
#define USB2DC_DIEPINT3_TXFEMP_SHIFT             7 
#define USB2DC_DIEPINT3_TXFEMP_BIT               0x1
#define USB2DC_DIEPINT3_TXFEMP_BITWIDTH          1
// TxfifoUndrn bitfiled (RO) Reset=0
#define USB2DC_DIEPINT3_TXFIFOUNDRN_MASK         0x100
#define USB2DC_DIEPINT3_TXFIFOUNDRN_SHIFT        8 
#define USB2DC_DIEPINT3_TXFIFOUNDRN_BIT          0x1
#define USB2DC_DIEPINT3_TXFIFOUNDRN_BITWIDTH     1
// BNAIntr bitfiled (RO) Reset=0
#define USB2DC_DIEPINT3_BNAINTR_MASK             0x200
#define USB2DC_DIEPINT3_BNAINTR_SHIFT            9 
#define USB2DC_DIEPINT3_BNAINTR_BIT              0x1
#define USB2DC_DIEPINT3_BNAINTR_BITWIDTH         1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DIEPINT3_RESERVED2_MASK           0x400
#define USB2DC_DIEPINT3_RESERVED2_SHIFT          10 
#define USB2DC_DIEPINT3_RESERVED2_BIT            0x1
#define USB2DC_DIEPINT3_RESERVED2_BITWIDTH       1
// PktDrpSts bitfiled (RO) Reset=0
#define USB2DC_DIEPINT3_PKTDRPSTS_MASK           0x800
#define USB2DC_DIEPINT3_PKTDRPSTS_SHIFT          11 
#define USB2DC_DIEPINT3_PKTDRPSTS_BIT            0x1
#define USB2DC_DIEPINT3_PKTDRPSTS_BITWIDTH       1
// BbleErr bitfiled (RO) Reset=0
#define USB2DC_DIEPINT3_BBLEERR_MASK             0x1000
#define USB2DC_DIEPINT3_BBLEERR_SHIFT            12 
#define USB2DC_DIEPINT3_BBLEERR_BIT              0x1
#define USB2DC_DIEPINT3_BBLEERR_BITWIDTH         1
// NAKIntrpt bitfiled (RO) Reset=0
#define USB2DC_DIEPINT3_NAKINTRPT_MASK           0x2000
#define USB2DC_DIEPINT3_NAKINTRPT_SHIFT          13 
#define USB2DC_DIEPINT3_NAKINTRPT_BIT            0x1
#define USB2DC_DIEPINT3_NAKINTRPT_BITWIDTH       1
// NYETIntrpt bitfiled (RO) Reset=0
#define USB2DC_DIEPINT3_NYETINTRPT_MASK          0x4000
#define USB2DC_DIEPINT3_NYETINTRPT_SHIFT         14 
#define USB2DC_DIEPINT3_NYETINTRPT_BIT           0x1
#define USB2DC_DIEPINT3_NYETINTRPT_BITWIDTH      1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPINT3_RESERVED_MASK            0xFFFF8000
#define USB2DC_DIEPINT3_RESERVED_SHIFT           15 
#define USB2DC_DIEPINT3_RESERVED_BIT             0x1FFFF
#define USB2DC_DIEPINT3_RESERVED_BITWIDTH        17
// DIEPTSIZ3 Register
#define USB2DC_DIEPTSIZ3_OFS                     0x00000970
// XferSize bitfiled (RW) Reset=0
#define USB2DC_DIEPTSIZ3_XFERSIZE_MASK           0x7FFFF
#define USB2DC_DIEPTSIZ3_XFERSIZE_SHIFT          0 
#define USB2DC_DIEPTSIZ3_XFERSIZE_BIT            0x7FFFF
#define USB2DC_DIEPTSIZ3_XFERSIZE_BITWIDTH       19
// PktCnt bitfiled (RW) Reset=0
#define USB2DC_DIEPTSIZ3_PKTCNT_MASK             0x1FF80000
#define USB2DC_DIEPTSIZ3_PKTCNT_SHIFT            19 
#define USB2DC_DIEPTSIZ3_PKTCNT_BIT              0x3FF
#define USB2DC_DIEPTSIZ3_PKTCNT_BITWIDTH         10
// MC bitfiled (RW) Reset=0
#define USB2DC_DIEPTSIZ3_MC_MASK                 0x60000000
#define USB2DC_DIEPTSIZ3_MC_SHIFT                29 
#define USB2DC_DIEPTSIZ3_MC_BIT                  0x3
#define USB2DC_DIEPTSIZ3_MC_BITWIDTH             2
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPTSIZ3_RESERVED_MASK           0x80000000
#define USB2DC_DIEPTSIZ3_RESERVED_SHIFT          31 
#define USB2DC_DIEPTSIZ3_RESERVED_BIT            0x1
#define USB2DC_DIEPTSIZ3_RESERVED_BITWIDTH       1
// DIEPDMA3 Register
#define USB2DC_DIEPDMA3_OFS                      0x00000974
// DMAAddr bitfiled (RW) Reset=0
#define USB2DC_DIEPDMA3_DMAADDR_MASK             0xFFFFFFFF
#define USB2DC_DIEPDMA3_DMAADDR_SHIFT            0 
#define USB2DC_DIEPDMA3_DMAADDR_BIT              0xFFFFFFFF
#define USB2DC_DIEPDMA3_DMAADDR_BITWIDTH         32
// DTXFSTS3 Register
#define USB2DC_DTXFSTS3_OFS                      0x00000978
// INEPTxFSpcAvail bitfiled (RO) Reset=1000000000
#define USB2DC_DTXFSTS3_INEPTXFSPCAVAIL_MASK     0xFFFF
#define USB2DC_DTXFSTS3_INEPTXFSPCAVAIL_SHIFT    0 
#define USB2DC_DTXFSTS3_INEPTXFSPCAVAIL_BIT      0xFFFF
#define USB2DC_DTXFSTS3_INEPTXFSPCAVAIL_BITWIDTH 16
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DTXFSTS3_RESERVED_MASK            0xFFFF0000
#define USB2DC_DTXFSTS3_RESERVED_SHIFT           16 
#define USB2DC_DTXFSTS3_RESERVED_BIT             0xFFFF
#define USB2DC_DTXFSTS3_RESERVED_BITWIDTH        16
// DIEPDMAB3 Register
#define USB2DC_DIEPDMAB3_OFS                     0x0000097C
// DMABufferAddr bitfiled (RO) Reset=0
#define USB2DC_DIEPDMAB3_DMABUFFERADDR_MASK      0xFFFFFFFF
#define USB2DC_DIEPDMAB3_DMABUFFERADDR_SHIFT     0 
#define USB2DC_DIEPDMAB3_DMABUFFERADDR_BIT       0xFFFFFFFF
#define USB2DC_DIEPDMAB3_DMABUFFERADDR_BITWIDTH  32
// DIEPCTL4 Register
#define USB2DC_DIEPCTL4_OFS                      0x00000980
// MPS bitfiled (RW) Reset=0
#define USB2DC_DIEPCTL4_MPS_MASK                 0x7FF
#define USB2DC_DIEPCTL4_MPS_SHIFT                0 
#define USB2DC_DIEPCTL4_MPS_BIT                  0x7FF
#define USB2DC_DIEPCTL4_MPS_BITWIDTH             11
// reserved2 bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL4_RESERVED2_MASK           0x7800
#define USB2DC_DIEPCTL4_RESERVED2_SHIFT          11 
#define USB2DC_DIEPCTL4_RESERVED2_BIT            0xF
#define USB2DC_DIEPCTL4_RESERVED2_BITWIDTH       4
// USBActEP bitfiled (RW) Reset=0
#define USB2DC_DIEPCTL4_USBACTEP_MASK            0x8000
#define USB2DC_DIEPCTL4_USBACTEP_SHIFT           15 
#define USB2DC_DIEPCTL4_USBACTEP_BIT             0x1
#define USB2DC_DIEPCTL4_USBACTEP_BITWIDTH        1
// DPID bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL4_DPID_MASK                0x10000
#define USB2DC_DIEPCTL4_DPID_SHIFT               16 
#define USB2DC_DIEPCTL4_DPID_BIT                 0x1
#define USB2DC_DIEPCTL4_DPID_BITWIDTH            1
// NAKSts bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL4_NAKSTS_MASK              0x20000
#define USB2DC_DIEPCTL4_NAKSTS_SHIFT             17 
#define USB2DC_DIEPCTL4_NAKSTS_BIT               0x1
#define USB2DC_DIEPCTL4_NAKSTS_BITWIDTH          1
// EPType bitfiled (RW) Reset=0
#define USB2DC_DIEPCTL4_EPTYPE_MASK              0xC0000
#define USB2DC_DIEPCTL4_EPTYPE_SHIFT             18 
#define USB2DC_DIEPCTL4_EPTYPE_BIT               0x3
#define USB2DC_DIEPCTL4_EPTYPE_BITWIDTH          2
// reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL4_RESERVED_MASK            0x100000
#define USB2DC_DIEPCTL4_RESERVED_SHIFT           20 
#define USB2DC_DIEPCTL4_RESERVED_BIT             0x1
#define USB2DC_DIEPCTL4_RESERVED_BITWIDTH        1
// Stall bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL4_STALL_MASK               0x200000
#define USB2DC_DIEPCTL4_STALL_SHIFT              21 
#define USB2DC_DIEPCTL4_STALL_BIT                0x1
#define USB2DC_DIEPCTL4_STALL_BITWIDTH           1
// TxFNum bitfiled (RW) Reset=0
#define USB2DC_DIEPCTL4_TXFNUM_MASK              0x3C00000
#define USB2DC_DIEPCTL4_TXFNUM_SHIFT             22 
#define USB2DC_DIEPCTL4_TXFNUM_BIT               0xF
#define USB2DC_DIEPCTL4_TXFNUM_BITWIDTH          4
// CNAK bitfiled (WO) Reset=0
#define USB2DC_DIEPCTL4_CNAK_MASK                0x4000000
#define USB2DC_DIEPCTL4_CNAK_SHIFT               26 
#define USB2DC_DIEPCTL4_CNAK_BIT                 0x1
#define USB2DC_DIEPCTL4_CNAK_BITWIDTH            1
// SNAK bitfiled (WO) Reset=0
#define USB2DC_DIEPCTL4_SNAK_MASK                0x8000000
#define USB2DC_DIEPCTL4_SNAK_SHIFT               27 
#define USB2DC_DIEPCTL4_SNAK_BIT                 0x1
#define USB2DC_DIEPCTL4_SNAK_BITWIDTH            1
// SetD0PID bitfiled (WO) Reset=0
#define USB2DC_DIEPCTL4_SETD0PID_MASK            0x10000000
#define USB2DC_DIEPCTL4_SETD0PID_SHIFT           28 
#define USB2DC_DIEPCTL4_SETD0PID_BIT             0x1
#define USB2DC_DIEPCTL4_SETD0PID_BITWIDTH        1
// SetD1PID bitfiled (WO) Reset=0
#define USB2DC_DIEPCTL4_SETD1PID_MASK            0x20000000
#define USB2DC_DIEPCTL4_SETD1PID_SHIFT           29 
#define USB2DC_DIEPCTL4_SETD1PID_BIT             0x1
#define USB2DC_DIEPCTL4_SETD1PID_BITWIDTH        1
// EPDis bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL4_EPDIS_MASK               0x40000000
#define USB2DC_DIEPCTL4_EPDIS_SHIFT              30 
#define USB2DC_DIEPCTL4_EPDIS_BIT                0x1
#define USB2DC_DIEPCTL4_EPDIS_BITWIDTH           1
// EPEna bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL4_EPENA_MASK               0x80000000
#define USB2DC_DIEPCTL4_EPENA_SHIFT              31 
#define USB2DC_DIEPCTL4_EPENA_BIT                0x1
#define USB2DC_DIEPCTL4_EPENA_BITWIDTH           1
// DIEPINT4 Register
#define USB2DC_DIEPINT4_OFS                      0x00000988
// XferCompl bitfiled (RO) Reset=0
#define USB2DC_DIEPINT4_XFERCOMPL_MASK           0x1
#define USB2DC_DIEPINT4_XFERCOMPL_SHIFT          0 
#define USB2DC_DIEPINT4_XFERCOMPL_BIT            0x1
#define USB2DC_DIEPINT4_XFERCOMPL_BITWIDTH       1
// EPDisbld bitfiled (RO) Reset=0
#define USB2DC_DIEPINT4_EPDISBLD_MASK            0x2
#define USB2DC_DIEPINT4_EPDISBLD_SHIFT           1 
#define USB2DC_DIEPINT4_EPDISBLD_BIT             0x1
#define USB2DC_DIEPINT4_EPDISBLD_BITWIDTH        1
// AHBErr bitfiled (RO) Reset=0
#define USB2DC_DIEPINT4_AHBERR_MASK              0x4
#define USB2DC_DIEPINT4_AHBERR_SHIFT             2 
#define USB2DC_DIEPINT4_AHBERR_BIT               0x1
#define USB2DC_DIEPINT4_AHBERR_BITWIDTH          1
// TimeOUT bitfiled (RO) Reset=0
#define USB2DC_DIEPINT4_TIMEOUT_MASK             0x8
#define USB2DC_DIEPINT4_TIMEOUT_SHIFT            3 
#define USB2DC_DIEPINT4_TIMEOUT_BIT              0x1
#define USB2DC_DIEPINT4_TIMEOUT_BITWIDTH         1
// INTknTXFEmp bitfiled (RO) Reset=0
#define USB2DC_DIEPINT4_INTKNTXFEMP_MASK         0x10
#define USB2DC_DIEPINT4_INTKNTXFEMP_SHIFT        4 
#define USB2DC_DIEPINT4_INTKNTXFEMP_BIT          0x1
#define USB2DC_DIEPINT4_INTKNTXFEMP_BITWIDTH     1
// INTknEPMis bitfiled (RO) Reset=0
#define USB2DC_DIEPINT4_INTKNEPMIS_MASK          0x20
#define USB2DC_DIEPINT4_INTKNEPMIS_SHIFT         5 
#define USB2DC_DIEPINT4_INTKNEPMIS_BIT           0x1
#define USB2DC_DIEPINT4_INTKNEPMIS_BITWIDTH      1
// INEPNakEff bitfiled (RO) Reset=0
#define USB2DC_DIEPINT4_INEPNAKEFF_MASK          0x40
#define USB2DC_DIEPINT4_INEPNAKEFF_SHIFT         6 
#define USB2DC_DIEPINT4_INEPNAKEFF_BIT           0x1
#define USB2DC_DIEPINT4_INEPNAKEFF_BITWIDTH      1
// TxFEmp bitfiled (RO) Reset=1
#define USB2DC_DIEPINT4_TXFEMP_MASK              0x80
#define USB2DC_DIEPINT4_TXFEMP_SHIFT             7 
#define USB2DC_DIEPINT4_TXFEMP_BIT               0x1
#define USB2DC_DIEPINT4_TXFEMP_BITWIDTH          1
// TxfifoUndrn bitfiled (RO) Reset=0
#define USB2DC_DIEPINT4_TXFIFOUNDRN_MASK         0x100
#define USB2DC_DIEPINT4_TXFIFOUNDRN_SHIFT        8 
#define USB2DC_DIEPINT4_TXFIFOUNDRN_BIT          0x1
#define USB2DC_DIEPINT4_TXFIFOUNDRN_BITWIDTH     1
// BNAIntr bitfiled (RO) Reset=0
#define USB2DC_DIEPINT4_BNAINTR_MASK             0x200
#define USB2DC_DIEPINT4_BNAINTR_SHIFT            9 
#define USB2DC_DIEPINT4_BNAINTR_BIT              0x1
#define USB2DC_DIEPINT4_BNAINTR_BITWIDTH         1
// reserved2 bitfiled (RO) Reset=0
#define USB2DC_DIEPINT4_RESERVED2_MASK           0x400
#define USB2DC_DIEPINT4_RESERVED2_SHIFT          10 
#define USB2DC_DIEPINT4_RESERVED2_BIT            0x1
#define USB2DC_DIEPINT4_RESERVED2_BITWIDTH       1
// PktDrpSts bitfiled (RO) Reset=0
#define USB2DC_DIEPINT4_PKTDRPSTS_MASK           0x800
#define USB2DC_DIEPINT4_PKTDRPSTS_SHIFT          11 
#define USB2DC_DIEPINT4_PKTDRPSTS_BIT            0x1
#define USB2DC_DIEPINT4_PKTDRPSTS_BITWIDTH       1
// BbleErr bitfiled (RO) Reset=0
#define USB2DC_DIEPINT4_BBLEERR_MASK             0x1000
#define USB2DC_DIEPINT4_BBLEERR_SHIFT            12 
#define USB2DC_DIEPINT4_BBLEERR_BIT              0x1
#define USB2DC_DIEPINT4_BBLEERR_BITWIDTH         1
// NAKIntrpt bitfiled (RO) Reset=0
#define USB2DC_DIEPINT4_NAKINTRPT_MASK           0x2000
#define USB2DC_DIEPINT4_NAKINTRPT_SHIFT          13 
#define USB2DC_DIEPINT4_NAKINTRPT_BIT            0x1
#define USB2DC_DIEPINT4_NAKINTRPT_BITWIDTH       1
// NYETIntrpt bitfiled (RO) Reset=0
#define USB2DC_DIEPINT4_NYETINTRPT_MASK          0x4000
#define USB2DC_DIEPINT4_NYETINTRPT_SHIFT         14 
#define USB2DC_DIEPINT4_NYETINTRPT_BIT           0x1
#define USB2DC_DIEPINT4_NYETINTRPT_BITWIDTH      1
// reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPINT4_RESERVED_MASK            0xFFFF8000
#define USB2DC_DIEPINT4_RESERVED_SHIFT           15 
#define USB2DC_DIEPINT4_RESERVED_BIT             0x1FFFF
#define USB2DC_DIEPINT4_RESERVED_BITWIDTH        17
// DIEPTSIZ4 Register
#define USB2DC_DIEPTSIZ4_OFS                     0x00000990
// XferSize bitfiled (RW) Reset=0
#define USB2DC_DIEPTSIZ4_XFERSIZE_MASK           0x7FFFF
#define USB2DC_DIEPTSIZ4_XFERSIZE_SHIFT          0 
#define USB2DC_DIEPTSIZ4_XFERSIZE_BIT            0x7FFFF
#define USB2DC_DIEPTSIZ4_XFERSIZE_BITWIDTH       19
// PktCnt bitfiled (RW) Reset=0
#define USB2DC_DIEPTSIZ4_PKTCNT_MASK             0x1FF80000
#define USB2DC_DIEPTSIZ4_PKTCNT_SHIFT            19 
#define USB2DC_DIEPTSIZ4_PKTCNT_BIT              0x3FF
#define USB2DC_DIEPTSIZ4_PKTCNT_BITWIDTH         10
// MC bitfiled (RW) Reset=0
#define USB2DC_DIEPTSIZ4_MC_MASK                 0x60000000
#define USB2DC_DIEPTSIZ4_MC_SHIFT                29 
#define USB2DC_DIEPTSIZ4_MC_BIT                  0x3
#define USB2DC_DIEPTSIZ4_MC_BITWIDTH             2
// reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPTSIZ4_RESERVED_MASK           0x80000000
#define USB2DC_DIEPTSIZ4_RESERVED_SHIFT          31 
#define USB2DC_DIEPTSIZ4_RESERVED_BIT            0x1
#define USB2DC_DIEPTSIZ4_RESERVED_BITWIDTH       1
// DIEPDMA4 Register
#define USB2DC_DIEPDMA4_OFS                      0x00000994
// DMAAddr bitfiled (RW) Reset=0
#define USB2DC_DIEPDMA4_DMAADDR_MASK             0xFFFFFFFF
#define USB2DC_DIEPDMA4_DMAADDR_SHIFT            0 
#define USB2DC_DIEPDMA4_DMAADDR_BIT              0xFFFFFFFF
#define USB2DC_DIEPDMA4_DMAADDR_BITWIDTH         32
// DTXFSTS4 Register
#define USB2DC_DTXFSTS4_OFS                      0x00000998
// INEPTxFSpcAvail bitfiled (RO) Reset=1000000000
#define USB2DC_DTXFSTS4_INEPTXFSPCAVAIL_MASK     0xFFFF
#define USB2DC_DTXFSTS4_INEPTXFSPCAVAIL_SHIFT    0 
#define USB2DC_DTXFSTS4_INEPTXFSPCAVAIL_BIT      0xFFFF
#define USB2DC_DTXFSTS4_INEPTXFSPCAVAIL_BITWIDTH 16
// reserved bitfiled (RO) Reset=0
#define USB2DC_DTXFSTS4_RESERVED_MASK            0xFFFF0000
#define USB2DC_DTXFSTS4_RESERVED_SHIFT           16 
#define USB2DC_DTXFSTS4_RESERVED_BIT             0xFFFF
#define USB2DC_DTXFSTS4_RESERVED_BITWIDTH        16
// DIEPDMAB4 Register
#define USB2DC_DIEPDMAB4_OFS                     0x0000099C
// DMABufferAddr bitfiled (RO) Reset=0
#define USB2DC_DIEPDMAB4_DMABUFFERADDR_MASK      0xFFFFFFFF
#define USB2DC_DIEPDMAB4_DMABUFFERADDR_SHIFT     0 
#define USB2DC_DIEPDMAB4_DMABUFFERADDR_BIT       0xFFFFFFFF
#define USB2DC_DIEPDMAB4_DMABUFFERADDR_BITWIDTH  32
// DIEPCTL5 Register
#define USB2DC_DIEPCTL5_OFS                      0x000009A0
// MPS bitfiled (RW) Reset=0
#define USB2DC_DIEPCTL5_MPS_MASK                 0x7FF
#define USB2DC_DIEPCTL5_MPS_SHIFT                0 
#define USB2DC_DIEPCTL5_MPS_BIT                  0x7FF
#define USB2DC_DIEPCTL5_MPS_BITWIDTH             11
// reserved2 bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL5_RESERVED2_MASK           0x7800
#define USB2DC_DIEPCTL5_RESERVED2_SHIFT          11 
#define USB2DC_DIEPCTL5_RESERVED2_BIT            0xF
#define USB2DC_DIEPCTL5_RESERVED2_BITWIDTH       4
// USBActEP bitfiled (RW) Reset=0
#define USB2DC_DIEPCTL5_USBACTEP_MASK            0x8000
#define USB2DC_DIEPCTL5_USBACTEP_SHIFT           15 
#define USB2DC_DIEPCTL5_USBACTEP_BIT             0x1
#define USB2DC_DIEPCTL5_USBACTEP_BITWIDTH        1
// DPID bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL5_DPID_MASK                0x10000
#define USB2DC_DIEPCTL5_DPID_SHIFT               16 
#define USB2DC_DIEPCTL5_DPID_BIT                 0x1
#define USB2DC_DIEPCTL5_DPID_BITWIDTH            1
// NAKSts bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL5_NAKSTS_MASK              0x20000
#define USB2DC_DIEPCTL5_NAKSTS_SHIFT             17 
#define USB2DC_DIEPCTL5_NAKSTS_BIT               0x1
#define USB2DC_DIEPCTL5_NAKSTS_BITWIDTH          1
// EPType bitfiled (RW) Reset=0
#define USB2DC_DIEPCTL5_EPTYPE_MASK              0xC0000
#define USB2DC_DIEPCTL5_EPTYPE_SHIFT             18 
#define USB2DC_DIEPCTL5_EPTYPE_BIT               0x3
#define USB2DC_DIEPCTL5_EPTYPE_BITWIDTH          2
// reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL5_RESERVED_MASK            0x100000
#define USB2DC_DIEPCTL5_RESERVED_SHIFT           20 
#define USB2DC_DIEPCTL5_RESERVED_BIT             0x1
#define USB2DC_DIEPCTL5_RESERVED_BITWIDTH        1
// Stall bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL5_STALL_MASK               0x200000
#define USB2DC_DIEPCTL5_STALL_SHIFT              21 
#define USB2DC_DIEPCTL5_STALL_BIT                0x1
#define USB2DC_DIEPCTL5_STALL_BITWIDTH           1
// TxFNum bitfiled (RW) Reset=0
#define USB2DC_DIEPCTL5_TXFNUM_MASK              0x3C00000
#define USB2DC_DIEPCTL5_TXFNUM_SHIFT             22 
#define USB2DC_DIEPCTL5_TXFNUM_BIT               0xF
#define USB2DC_DIEPCTL5_TXFNUM_BITWIDTH          4
// CNAK bitfiled (WO) Reset=0
#define USB2DC_DIEPCTL5_CNAK_MASK                0x4000000
#define USB2DC_DIEPCTL5_CNAK_SHIFT               26 
#define USB2DC_DIEPCTL5_CNAK_BIT                 0x1
#define USB2DC_DIEPCTL5_CNAK_BITWIDTH            1
// SNAK bitfiled (WO) Reset=0
#define USB2DC_DIEPCTL5_SNAK_MASK                0x8000000
#define USB2DC_DIEPCTL5_SNAK_SHIFT               27 
#define USB2DC_DIEPCTL5_SNAK_BIT                 0x1
#define USB2DC_DIEPCTL5_SNAK_BITWIDTH            1
// SetD0PID bitfiled (WO) Reset=0
#define USB2DC_DIEPCTL5_SETD0PID_MASK            0x10000000
#define USB2DC_DIEPCTL5_SETD0PID_SHIFT           28 
#define USB2DC_DIEPCTL5_SETD0PID_BIT             0x1
#define USB2DC_DIEPCTL5_SETD0PID_BITWIDTH        1
// SetD1PID bitfiled (WO) Reset=0
#define USB2DC_DIEPCTL5_SETD1PID_MASK            0x20000000
#define USB2DC_DIEPCTL5_SETD1PID_SHIFT           29 
#define USB2DC_DIEPCTL5_SETD1PID_BIT             0x1
#define USB2DC_DIEPCTL5_SETD1PID_BITWIDTH        1
// EPDis bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL5_EPDIS_MASK               0x40000000
#define USB2DC_DIEPCTL5_EPDIS_SHIFT              30 
#define USB2DC_DIEPCTL5_EPDIS_BIT                0x1
#define USB2DC_DIEPCTL5_EPDIS_BITWIDTH           1
// EPEna bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL5_EPENA_MASK               0x80000000
#define USB2DC_DIEPCTL5_EPENA_SHIFT              31 
#define USB2DC_DIEPCTL5_EPENA_BIT                0x1
#define USB2DC_DIEPCTL5_EPENA_BITWIDTH           1
// DIEPINT5 Register
#define USB2DC_DIEPINT5_OFS                      0x000009A8
// XferCompl bitfiled (RO) Reset=0
#define USB2DC_DIEPINT5_XFERCOMPL_MASK           0x1
#define USB2DC_DIEPINT5_XFERCOMPL_SHIFT          0 
#define USB2DC_DIEPINT5_XFERCOMPL_BIT            0x1
#define USB2DC_DIEPINT5_XFERCOMPL_BITWIDTH       1
// EPDisbld bitfiled (RO) Reset=0
#define USB2DC_DIEPINT5_EPDISBLD_MASK            0x2
#define USB2DC_DIEPINT5_EPDISBLD_SHIFT           1 
#define USB2DC_DIEPINT5_EPDISBLD_BIT             0x1
#define USB2DC_DIEPINT5_EPDISBLD_BITWIDTH        1
// AHBErr bitfiled (RO) Reset=0
#define USB2DC_DIEPINT5_AHBERR_MASK              0x4
#define USB2DC_DIEPINT5_AHBERR_SHIFT             2 
#define USB2DC_DIEPINT5_AHBERR_BIT               0x1
#define USB2DC_DIEPINT5_AHBERR_BITWIDTH          1
// TimeOUT bitfiled (RO) Reset=0
#define USB2DC_DIEPINT5_TIMEOUT_MASK             0x8
#define USB2DC_DIEPINT5_TIMEOUT_SHIFT            3 
#define USB2DC_DIEPINT5_TIMEOUT_BIT              0x1
#define USB2DC_DIEPINT5_TIMEOUT_BITWIDTH         1
// INTknTXFEmp bitfiled (RO) Reset=0
#define USB2DC_DIEPINT5_INTKNTXFEMP_MASK         0x10
#define USB2DC_DIEPINT5_INTKNTXFEMP_SHIFT        4 
#define USB2DC_DIEPINT5_INTKNTXFEMP_BIT          0x1
#define USB2DC_DIEPINT5_INTKNTXFEMP_BITWIDTH     1
// INTknEPMis bitfiled (RO) Reset=0
#define USB2DC_DIEPINT5_INTKNEPMIS_MASK          0x20
#define USB2DC_DIEPINT5_INTKNEPMIS_SHIFT         5 
#define USB2DC_DIEPINT5_INTKNEPMIS_BIT           0x1
#define USB2DC_DIEPINT5_INTKNEPMIS_BITWIDTH      1
// INEPNakEff bitfiled (RO) Reset=0
#define USB2DC_DIEPINT5_INEPNAKEFF_MASK          0x40
#define USB2DC_DIEPINT5_INEPNAKEFF_SHIFT         6 
#define USB2DC_DIEPINT5_INEPNAKEFF_BIT           0x1
#define USB2DC_DIEPINT5_INEPNAKEFF_BITWIDTH      1
// TxFEmp bitfiled (RO) Reset=1
#define USB2DC_DIEPINT5_TXFEMP_MASK              0x80
#define USB2DC_DIEPINT5_TXFEMP_SHIFT             7 
#define USB2DC_DIEPINT5_TXFEMP_BIT               0x1
#define USB2DC_DIEPINT5_TXFEMP_BITWIDTH          1
// TxfifoUndrn bitfiled (RO) Reset=0
#define USB2DC_DIEPINT5_TXFIFOUNDRN_MASK         0x100
#define USB2DC_DIEPINT5_TXFIFOUNDRN_SHIFT        8 
#define USB2DC_DIEPINT5_TXFIFOUNDRN_BIT          0x1
#define USB2DC_DIEPINT5_TXFIFOUNDRN_BITWIDTH     1
// BNAIntr bitfiled (RO) Reset=0
#define USB2DC_DIEPINT5_BNAINTR_MASK             0x200
#define USB2DC_DIEPINT5_BNAINTR_SHIFT            9 
#define USB2DC_DIEPINT5_BNAINTR_BIT              0x1
#define USB2DC_DIEPINT5_BNAINTR_BITWIDTH         1
// reserved2 bitfiled (RO) Reset=0
#define USB2DC_DIEPINT5_RESERVED2_MASK           0x400
#define USB2DC_DIEPINT5_RESERVED2_SHIFT          10 
#define USB2DC_DIEPINT5_RESERVED2_BIT            0x1
#define USB2DC_DIEPINT5_RESERVED2_BITWIDTH       1
// PktDrpSts bitfiled (RO) Reset=0
#define USB2DC_DIEPINT5_PKTDRPSTS_MASK           0x800
#define USB2DC_DIEPINT5_PKTDRPSTS_SHIFT          11 
#define USB2DC_DIEPINT5_PKTDRPSTS_BIT            0x1
#define USB2DC_DIEPINT5_PKTDRPSTS_BITWIDTH       1
// BbleErr bitfiled (RO) Reset=0
#define USB2DC_DIEPINT5_BBLEERR_MASK             0x1000
#define USB2DC_DIEPINT5_BBLEERR_SHIFT            12 
#define USB2DC_DIEPINT5_BBLEERR_BIT              0x1
#define USB2DC_DIEPINT5_BBLEERR_BITWIDTH         1
// NAKIntrpt bitfiled (RO) Reset=0
#define USB2DC_DIEPINT5_NAKINTRPT_MASK           0x2000
#define USB2DC_DIEPINT5_NAKINTRPT_SHIFT          13 
#define USB2DC_DIEPINT5_NAKINTRPT_BIT            0x1
#define USB2DC_DIEPINT5_NAKINTRPT_BITWIDTH       1
// NYETIntrpt bitfiled (RO) Reset=0
#define USB2DC_DIEPINT5_NYETINTRPT_MASK          0x4000
#define USB2DC_DIEPINT5_NYETINTRPT_SHIFT         14 
#define USB2DC_DIEPINT5_NYETINTRPT_BIT           0x1
#define USB2DC_DIEPINT5_NYETINTRPT_BITWIDTH      1
// reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPINT5_RESERVED_MASK            0xFFFF8000
#define USB2DC_DIEPINT5_RESERVED_SHIFT           15 
#define USB2DC_DIEPINT5_RESERVED_BIT             0x1FFFF
#define USB2DC_DIEPINT5_RESERVED_BITWIDTH        17
// DIEPTSIZ5 Register
#define USB2DC_DIEPTSIZ5_OFS                     0x000009B0
// XferSize bitfiled (RW) Reset=0
#define USB2DC_DIEPTSIZ5_XFERSIZE_MASK           0x7FFFF
#define USB2DC_DIEPTSIZ5_XFERSIZE_SHIFT          0 
#define USB2DC_DIEPTSIZ5_XFERSIZE_BIT            0x7FFFF
#define USB2DC_DIEPTSIZ5_XFERSIZE_BITWIDTH       19
// PktCnt bitfiled (RW) Reset=0
#define USB2DC_DIEPTSIZ5_PKTCNT_MASK             0x1FF80000
#define USB2DC_DIEPTSIZ5_PKTCNT_SHIFT            19 
#define USB2DC_DIEPTSIZ5_PKTCNT_BIT              0x3FF
#define USB2DC_DIEPTSIZ5_PKTCNT_BITWIDTH         10
// MC bitfiled (RW) Reset=0
#define USB2DC_DIEPTSIZ5_MC_MASK                 0x60000000
#define USB2DC_DIEPTSIZ5_MC_SHIFT                29 
#define USB2DC_DIEPTSIZ5_MC_BIT                  0x3
#define USB2DC_DIEPTSIZ5_MC_BITWIDTH             2
// reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPTSIZ5_RESERVED_MASK           0x80000000
#define USB2DC_DIEPTSIZ5_RESERVED_SHIFT          31 
#define USB2DC_DIEPTSIZ5_RESERVED_BIT            0x1
#define USB2DC_DIEPTSIZ5_RESERVED_BITWIDTH       1
// DIEPDMA5 Register
#define USB2DC_DIEPDMA5_OFS                      0x000009B4
// DMAAddr bitfiled (RW) Reset=0
#define USB2DC_DIEPDMA5_DMAADDR_MASK             0xFFFFFFFF
#define USB2DC_DIEPDMA5_DMAADDR_SHIFT            0 
#define USB2DC_DIEPDMA5_DMAADDR_BIT              0xFFFFFFFF
#define USB2DC_DIEPDMA5_DMAADDR_BITWIDTH         32
// DTXFSTS5 Register
#define USB2DC_DTXFSTS5_OFS                      0x000009B8
// INEPTxFSpcAvail bitfiled (RO) Reset=100000000
#define USB2DC_DTXFSTS5_INEPTXFSPCAVAIL_MASK     0xFFFF
#define USB2DC_DTXFSTS5_INEPTXFSPCAVAIL_SHIFT    0 
#define USB2DC_DTXFSTS5_INEPTXFSPCAVAIL_BIT      0xFFFF
#define USB2DC_DTXFSTS5_INEPTXFSPCAVAIL_BITWIDTH 16
// reserved bitfiled (RO) Reset=0
#define USB2DC_DTXFSTS5_RESERVED_MASK            0xFFFF0000
#define USB2DC_DTXFSTS5_RESERVED_SHIFT           16 
#define USB2DC_DTXFSTS5_RESERVED_BIT             0xFFFF
#define USB2DC_DTXFSTS5_RESERVED_BITWIDTH        16
// DIEPDMAB5 Register
#define USB2DC_DIEPDMAB5_OFS                     0x000009BC
// DMABufferAddr bitfiled (RO) Reset=0
#define USB2DC_DIEPDMAB5_DMABUFFERADDR_MASK      0xFFFFFFFF
#define USB2DC_DIEPDMAB5_DMABUFFERADDR_SHIFT     0 
#define USB2DC_DIEPDMAB5_DMABUFFERADDR_BIT       0xFFFFFFFF
#define USB2DC_DIEPDMAB5_DMABUFFERADDR_BITWIDTH  32
// DIEPCTL6 Register
#define USB2DC_DIEPCTL6_OFS                      0x000009C0
// MPS bitfiled (RW) Reset=0
#define USB2DC_DIEPCTL6_MPS_MASK                 0x7FF
#define USB2DC_DIEPCTL6_MPS_SHIFT                0 
#define USB2DC_DIEPCTL6_MPS_BIT                  0x7FF
#define USB2DC_DIEPCTL6_MPS_BITWIDTH             11
// reserved2 bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL6_RESERVED2_MASK           0x7800
#define USB2DC_DIEPCTL6_RESERVED2_SHIFT          11 
#define USB2DC_DIEPCTL6_RESERVED2_BIT            0xF
#define USB2DC_DIEPCTL6_RESERVED2_BITWIDTH       4
// USBActEP bitfiled (RW) Reset=0
#define USB2DC_DIEPCTL6_USBACTEP_MASK            0x8000
#define USB2DC_DIEPCTL6_USBACTEP_SHIFT           15 
#define USB2DC_DIEPCTL6_USBACTEP_BIT             0x1
#define USB2DC_DIEPCTL6_USBACTEP_BITWIDTH        1
// DPID bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL6_DPID_MASK                0x10000
#define USB2DC_DIEPCTL6_DPID_SHIFT               16 
#define USB2DC_DIEPCTL6_DPID_BIT                 0x1
#define USB2DC_DIEPCTL6_DPID_BITWIDTH            1
// NAKSts bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL6_NAKSTS_MASK              0x20000
#define USB2DC_DIEPCTL6_NAKSTS_SHIFT             17 
#define USB2DC_DIEPCTL6_NAKSTS_BIT               0x1
#define USB2DC_DIEPCTL6_NAKSTS_BITWIDTH          1
// EPType bitfiled (RW) Reset=0
#define USB2DC_DIEPCTL6_EPTYPE_MASK              0xC0000
#define USB2DC_DIEPCTL6_EPTYPE_SHIFT             18 
#define USB2DC_DIEPCTL6_EPTYPE_BIT               0x3
#define USB2DC_DIEPCTL6_EPTYPE_BITWIDTH          2
// reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL6_RESERVED_MASK            0x100000
#define USB2DC_DIEPCTL6_RESERVED_SHIFT           20 
#define USB2DC_DIEPCTL6_RESERVED_BIT             0x1
#define USB2DC_DIEPCTL6_RESERVED_BITWIDTH        1
// Stall bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL6_STALL_MASK               0x200000
#define USB2DC_DIEPCTL6_STALL_SHIFT              21 
#define USB2DC_DIEPCTL6_STALL_BIT                0x1
#define USB2DC_DIEPCTL6_STALL_BITWIDTH           1
// TxFNum bitfiled (RW) Reset=0
#define USB2DC_DIEPCTL6_TXFNUM_MASK              0x3C00000
#define USB2DC_DIEPCTL6_TXFNUM_SHIFT             22 
#define USB2DC_DIEPCTL6_TXFNUM_BIT               0xF
#define USB2DC_DIEPCTL6_TXFNUM_BITWIDTH          4
// CNAK bitfiled (WO) Reset=0
#define USB2DC_DIEPCTL6_CNAK_MASK                0x4000000
#define USB2DC_DIEPCTL6_CNAK_SHIFT               26 
#define USB2DC_DIEPCTL6_CNAK_BIT                 0x1
#define USB2DC_DIEPCTL6_CNAK_BITWIDTH            1
// SNAK bitfiled (WO) Reset=0
#define USB2DC_DIEPCTL6_SNAK_MASK                0x8000000
#define USB2DC_DIEPCTL6_SNAK_SHIFT               27 
#define USB2DC_DIEPCTL6_SNAK_BIT                 0x1
#define USB2DC_DIEPCTL6_SNAK_BITWIDTH            1
// SetD0PID bitfiled (WO) Reset=0
#define USB2DC_DIEPCTL6_SETD0PID_MASK            0x10000000
#define USB2DC_DIEPCTL6_SETD0PID_SHIFT           28 
#define USB2DC_DIEPCTL6_SETD0PID_BIT             0x1
#define USB2DC_DIEPCTL6_SETD0PID_BITWIDTH        1
// SetD1PID bitfiled (WO) Reset=0
#define USB2DC_DIEPCTL6_SETD1PID_MASK            0x20000000
#define USB2DC_DIEPCTL6_SETD1PID_SHIFT           29 
#define USB2DC_DIEPCTL6_SETD1PID_BIT             0x1
#define USB2DC_DIEPCTL6_SETD1PID_BITWIDTH        1
// EPDis bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL6_EPDIS_MASK               0x40000000
#define USB2DC_DIEPCTL6_EPDIS_SHIFT              30 
#define USB2DC_DIEPCTL6_EPDIS_BIT                0x1
#define USB2DC_DIEPCTL6_EPDIS_BITWIDTH           1
// EPEna bitfiled (RO) Reset=0
#define USB2DC_DIEPCTL6_EPENA_MASK               0x80000000
#define USB2DC_DIEPCTL6_EPENA_SHIFT              31 
#define USB2DC_DIEPCTL6_EPENA_BIT                0x1
#define USB2DC_DIEPCTL6_EPENA_BITWIDTH           1
// DIEPINT6 Register
#define USB2DC_DIEPINT6_OFS                      0x000009C8
// XferCompl bitfiled (RO) Reset=0
#define USB2DC_DIEPINT6_XFERCOMPL_MASK           0x1
#define USB2DC_DIEPINT6_XFERCOMPL_SHIFT          0 
#define USB2DC_DIEPINT6_XFERCOMPL_BIT            0x1
#define USB2DC_DIEPINT6_XFERCOMPL_BITWIDTH       1
// EPDisbld bitfiled (RO) Reset=0
#define USB2DC_DIEPINT6_EPDISBLD_MASK            0x2
#define USB2DC_DIEPINT6_EPDISBLD_SHIFT           1 
#define USB2DC_DIEPINT6_EPDISBLD_BIT             0x1
#define USB2DC_DIEPINT6_EPDISBLD_BITWIDTH        1
// AHBErr bitfiled (RO) Reset=0
#define USB2DC_DIEPINT6_AHBERR_MASK              0x4
#define USB2DC_DIEPINT6_AHBERR_SHIFT             2 
#define USB2DC_DIEPINT6_AHBERR_BIT               0x1
#define USB2DC_DIEPINT6_AHBERR_BITWIDTH          1
// TimeOUT bitfiled (RO) Reset=0
#define USB2DC_DIEPINT6_TIMEOUT_MASK             0x8
#define USB2DC_DIEPINT6_TIMEOUT_SHIFT            3 
#define USB2DC_DIEPINT6_TIMEOUT_BIT              0x1
#define USB2DC_DIEPINT6_TIMEOUT_BITWIDTH         1
// INTknTXFEmp bitfiled (RO) Reset=0
#define USB2DC_DIEPINT6_INTKNTXFEMP_MASK         0x10
#define USB2DC_DIEPINT6_INTKNTXFEMP_SHIFT        4 
#define USB2DC_DIEPINT6_INTKNTXFEMP_BIT          0x1
#define USB2DC_DIEPINT6_INTKNTXFEMP_BITWIDTH     1
// INTknEPMis bitfiled (RO) Reset=0
#define USB2DC_DIEPINT6_INTKNEPMIS_MASK          0x20
#define USB2DC_DIEPINT6_INTKNEPMIS_SHIFT         5 
#define USB2DC_DIEPINT6_INTKNEPMIS_BIT           0x1
#define USB2DC_DIEPINT6_INTKNEPMIS_BITWIDTH      1
// INEPNakEff bitfiled (RO) Reset=0
#define USB2DC_DIEPINT6_INEPNAKEFF_MASK          0x40
#define USB2DC_DIEPINT6_INEPNAKEFF_SHIFT         6 
#define USB2DC_DIEPINT6_INEPNAKEFF_BIT           0x1
#define USB2DC_DIEPINT6_INEPNAKEFF_BITWIDTH      1
// TxFEmp bitfiled (RO) Reset=1
#define USB2DC_DIEPINT6_TXFEMP_MASK              0x80
#define USB2DC_DIEPINT6_TXFEMP_SHIFT             7 
#define USB2DC_DIEPINT6_TXFEMP_BIT               0x1
#define USB2DC_DIEPINT6_TXFEMP_BITWIDTH          1
// TxfifoUndrn bitfiled (RO) Reset=0
#define USB2DC_DIEPINT6_TXFIFOUNDRN_MASK         0x100
#define USB2DC_DIEPINT6_TXFIFOUNDRN_SHIFT        8 
#define USB2DC_DIEPINT6_TXFIFOUNDRN_BIT          0x1
#define USB2DC_DIEPINT6_TXFIFOUNDRN_BITWIDTH     1
// BNAIntr bitfiled (RO) Reset=0
#define USB2DC_DIEPINT6_BNAINTR_MASK             0x200
#define USB2DC_DIEPINT6_BNAINTR_SHIFT            9 
#define USB2DC_DIEPINT6_BNAINTR_BIT              0x1
#define USB2DC_DIEPINT6_BNAINTR_BITWIDTH         1
// reserved2 bitfiled (RO) Reset=0
#define USB2DC_DIEPINT6_RESERVED2_MASK           0x400
#define USB2DC_DIEPINT6_RESERVED2_SHIFT          10 
#define USB2DC_DIEPINT6_RESERVED2_BIT            0x1
#define USB2DC_DIEPINT6_RESERVED2_BITWIDTH       1
// PktDrpSts bitfiled (RO) Reset=0
#define USB2DC_DIEPINT6_PKTDRPSTS_MASK           0x800
#define USB2DC_DIEPINT6_PKTDRPSTS_SHIFT          11 
#define USB2DC_DIEPINT6_PKTDRPSTS_BIT            0x1
#define USB2DC_DIEPINT6_PKTDRPSTS_BITWIDTH       1
// BbleErr bitfiled (RO) Reset=0
#define USB2DC_DIEPINT6_BBLEERR_MASK             0x1000
#define USB2DC_DIEPINT6_BBLEERR_SHIFT            12 
#define USB2DC_DIEPINT6_BBLEERR_BIT              0x1
#define USB2DC_DIEPINT6_BBLEERR_BITWIDTH         1
// NAKIntrpt bitfiled (RO) Reset=0
#define USB2DC_DIEPINT6_NAKINTRPT_MASK           0x2000
#define USB2DC_DIEPINT6_NAKINTRPT_SHIFT          13 
#define USB2DC_DIEPINT6_NAKINTRPT_BIT            0x1
#define USB2DC_DIEPINT6_NAKINTRPT_BITWIDTH       1
// NYETIntrpt bitfiled (RO) Reset=0
#define USB2DC_DIEPINT6_NYETINTRPT_MASK          0x4000
#define USB2DC_DIEPINT6_NYETINTRPT_SHIFT         14 
#define USB2DC_DIEPINT6_NYETINTRPT_BIT           0x1
#define USB2DC_DIEPINT6_NYETINTRPT_BITWIDTH      1
// reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPINT6_RESERVED_MASK            0xFFFF8000
#define USB2DC_DIEPINT6_RESERVED_SHIFT           15 
#define USB2DC_DIEPINT6_RESERVED_BIT             0x1FFFF
#define USB2DC_DIEPINT6_RESERVED_BITWIDTH        17
// DIEPTSIZ6 Register
#define USB2DC_DIEPTSIZ6_OFS                     0x000009D0
// XferSize bitfiled (RW) Reset=0
#define USB2DC_DIEPTSIZ6_XFERSIZE_MASK           0x7FFFF
#define USB2DC_DIEPTSIZ6_XFERSIZE_SHIFT          0 
#define USB2DC_DIEPTSIZ6_XFERSIZE_BIT            0x7FFFF
#define USB2DC_DIEPTSIZ6_XFERSIZE_BITWIDTH       19
// PktCnt bitfiled (RW) Reset=0
#define USB2DC_DIEPTSIZ6_PKTCNT_MASK             0x1FF80000
#define USB2DC_DIEPTSIZ6_PKTCNT_SHIFT            19 
#define USB2DC_DIEPTSIZ6_PKTCNT_BIT              0x3FF
#define USB2DC_DIEPTSIZ6_PKTCNT_BITWIDTH         10
// MC bitfiled (RW) Reset=0
#define USB2DC_DIEPTSIZ6_MC_MASK                 0x60000000
#define USB2DC_DIEPTSIZ6_MC_SHIFT                29 
#define USB2DC_DIEPTSIZ6_MC_BIT                  0x3
#define USB2DC_DIEPTSIZ6_MC_BITWIDTH             2
// reserved bitfiled (RO) Reset=0
#define USB2DC_DIEPTSIZ6_RESERVED_MASK           0x80000000
#define USB2DC_DIEPTSIZ6_RESERVED_SHIFT          31 
#define USB2DC_DIEPTSIZ6_RESERVED_BIT            0x1
#define USB2DC_DIEPTSIZ6_RESERVED_BITWIDTH       1
// DIEPDMA6 Register
#define USB2DC_DIEPDMA6_OFS                      0x000009D4
// DMAAddr bitfiled (RW) Reset=0
#define USB2DC_DIEPDMA6_DMAADDR_MASK             0xFFFFFFFF
#define USB2DC_DIEPDMA6_DMAADDR_SHIFT            0 
#define USB2DC_DIEPDMA6_DMAADDR_BIT              0xFFFFFFFF
#define USB2DC_DIEPDMA6_DMAADDR_BITWIDTH         32
// DTXFSTS6 Register
#define USB2DC_DTXFSTS6_OFS                      0x000009D8
// INEPTxFSpcAvail bitfiled (RO) Reset=100000000
#define USB2DC_DTXFSTS6_INEPTXFSPCAVAIL_MASK     0xFFFF
#define USB2DC_DTXFSTS6_INEPTXFSPCAVAIL_SHIFT    0 
#define USB2DC_DTXFSTS6_INEPTXFSPCAVAIL_BIT      0xFFFF
#define USB2DC_DTXFSTS6_INEPTXFSPCAVAIL_BITWIDTH 16
// reserved bitfiled (RO) Reset=0
#define USB2DC_DTXFSTS6_RESERVED_MASK            0xFFFF0000
#define USB2DC_DTXFSTS6_RESERVED_SHIFT           16 
#define USB2DC_DTXFSTS6_RESERVED_BIT             0xFFFF
#define USB2DC_DTXFSTS6_RESERVED_BITWIDTH        16
// DIEPDMAB6 Register
#define USB2DC_DIEPDMAB6_OFS                     0x000009DC
// DMABufferAddr bitfiled (RO) Reset=0
#define USB2DC_DIEPDMAB6_DMABUFFERADDR_MASK      0xFFFFFFFF
#define USB2DC_DIEPDMAB6_DMABUFFERADDR_SHIFT     0 
#define USB2DC_DIEPDMAB6_DMABUFFERADDR_BIT       0xFFFFFFFF
#define USB2DC_DIEPDMAB6_DMABUFFERADDR_BITWIDTH  32
// DOEPCTL0 Register
#define USB2DC_DOEPCTL0_OFS                      0x00000B00
// MPS bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL0_MPS_MASK                 0x3
#define USB2DC_DOEPCTL0_MPS_SHIFT                0 
#define USB2DC_DOEPCTL0_MPS_BIT                  0x3
#define USB2DC_DOEPCTL0_MPS_BITWIDTH             2
// Reserved4 bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL0_RESERVED4_MASK           0x7FFC
#define USB2DC_DOEPCTL0_RESERVED4_SHIFT          2 
#define USB2DC_DOEPCTL0_RESERVED4_BIT            0x1FFF
#define USB2DC_DOEPCTL0_RESERVED4_BITWIDTH       13
// USBActEP bitfiled (RO) Reset=1
#define USB2DC_DOEPCTL0_USBACTEP_MASK            0x8000
#define USB2DC_DOEPCTL0_USBACTEP_SHIFT           15 
#define USB2DC_DOEPCTL0_USBACTEP_BIT             0x1
#define USB2DC_DOEPCTL0_USBACTEP_BITWIDTH        1
// Reserved3 bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL0_RESERVED3_MASK           0x10000
#define USB2DC_DOEPCTL0_RESERVED3_SHIFT          16 
#define USB2DC_DOEPCTL0_RESERVED3_BIT            0x1
#define USB2DC_DOEPCTL0_RESERVED3_BITWIDTH       1
// NAKSts bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL0_NAKSTS_MASK              0x20000
#define USB2DC_DOEPCTL0_NAKSTS_SHIFT             17 
#define USB2DC_DOEPCTL0_NAKSTS_BIT               0x1
#define USB2DC_DOEPCTL0_NAKSTS_BITWIDTH          1
// EPType bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL0_EPTYPE_MASK              0xC0000
#define USB2DC_DOEPCTL0_EPTYPE_SHIFT             18 
#define USB2DC_DOEPCTL0_EPTYPE_BIT               0x3
#define USB2DC_DOEPCTL0_EPTYPE_BITWIDTH          2
// Snp bitfiled (RW) Reset=0
#define USB2DC_DOEPCTL0_SNP_MASK                 0x100000
#define USB2DC_DOEPCTL0_SNP_SHIFT                20 
#define USB2DC_DOEPCTL0_SNP_BIT                  0x1
#define USB2DC_DOEPCTL0_SNP_BITWIDTH             1
// Stall bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL0_STALL_MASK               0x200000
#define USB2DC_DOEPCTL0_STALL_SHIFT              21 
#define USB2DC_DOEPCTL0_STALL_BIT                0x1
#define USB2DC_DOEPCTL0_STALL_BITWIDTH           1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL0_RESERVED2_MASK           0x3C00000
#define USB2DC_DOEPCTL0_RESERVED2_SHIFT          22 
#define USB2DC_DOEPCTL0_RESERVED2_BIT            0xF
#define USB2DC_DOEPCTL0_RESERVED2_BITWIDTH       4
// CNAK bitfiled (WO) Reset=0
#define USB2DC_DOEPCTL0_CNAK_MASK                0x4000000
#define USB2DC_DOEPCTL0_CNAK_SHIFT               26 
#define USB2DC_DOEPCTL0_CNAK_BIT                 0x1
#define USB2DC_DOEPCTL0_CNAK_BITWIDTH            1
// SNAK bitfiled (WO) Reset=0
#define USB2DC_DOEPCTL0_SNAK_MASK                0x8000000
#define USB2DC_DOEPCTL0_SNAK_SHIFT               27 
#define USB2DC_DOEPCTL0_SNAK_BIT                 0x1
#define USB2DC_DOEPCTL0_SNAK_BITWIDTH            1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL0_RESERVED_MASK            0x30000000
#define USB2DC_DOEPCTL0_RESERVED_SHIFT           28 
#define USB2DC_DOEPCTL0_RESERVED_BIT             0x3
#define USB2DC_DOEPCTL0_RESERVED_BITWIDTH        2
// EPDis bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL0_EPDIS_MASK               0x40000000
#define USB2DC_DOEPCTL0_EPDIS_SHIFT              30 
#define USB2DC_DOEPCTL0_EPDIS_BIT                0x1
#define USB2DC_DOEPCTL0_EPDIS_BITWIDTH           1
// EPEna bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL0_EPENA_MASK               0x80000000
#define USB2DC_DOEPCTL0_EPENA_SHIFT              31 
#define USB2DC_DOEPCTL0_EPENA_BIT                0x1
#define USB2DC_DOEPCTL0_EPENA_BITWIDTH           1
// DOEPINT0 Register
#define USB2DC_DOEPINT0_OFS                      0x00000B08
// XferCompl bitfiled (RO) Reset=0
#define USB2DC_DOEPINT0_XFERCOMPL_MASK           0x1
#define USB2DC_DOEPINT0_XFERCOMPL_SHIFT          0 
#define USB2DC_DOEPINT0_XFERCOMPL_BIT            0x1
#define USB2DC_DOEPINT0_XFERCOMPL_BITWIDTH       1
// EPDisbld bitfiled (RO) Reset=0
#define USB2DC_DOEPINT0_EPDISBLD_MASK            0x2
#define USB2DC_DOEPINT0_EPDISBLD_SHIFT           1 
#define USB2DC_DOEPINT0_EPDISBLD_BIT             0x1
#define USB2DC_DOEPINT0_EPDISBLD_BITWIDTH        1
// AHBErr bitfiled (RO) Reset=0
#define USB2DC_DOEPINT0_AHBERR_MASK              0x4
#define USB2DC_DOEPINT0_AHBERR_SHIFT             2 
#define USB2DC_DOEPINT0_AHBERR_BIT               0x1
#define USB2DC_DOEPINT0_AHBERR_BITWIDTH          1
// SetUp bitfiled (RO) Reset=0
#define USB2DC_DOEPINT0_SETUP_MASK               0x8
#define USB2DC_DOEPINT0_SETUP_SHIFT              3 
#define USB2DC_DOEPINT0_SETUP_BIT                0x1
#define USB2DC_DOEPINT0_SETUP_BITWIDTH           1
// OUTTknEPdis bitfiled (RO) Reset=0
#define USB2DC_DOEPINT0_OUTTKNEPDIS_MASK         0x10
#define USB2DC_DOEPINT0_OUTTKNEPDIS_SHIFT        4 
#define USB2DC_DOEPINT0_OUTTKNEPDIS_BIT          0x1
#define USB2DC_DOEPINT0_OUTTKNEPDIS_BITWIDTH     1
// StsPhseRcvd bitfiled (RO) Reset=0
#define USB2DC_DOEPINT0_STSPHSERCVD_MASK         0x20
#define USB2DC_DOEPINT0_STSPHSERCVD_SHIFT        5 
#define USB2DC_DOEPINT0_STSPHSERCVD_BIT          0x1
#define USB2DC_DOEPINT0_STSPHSERCVD_BITWIDTH     1
// Back2BackSETup bitfiled (RO) Reset=0
#define USB2DC_DOEPINT0_BACK2BACKSETUP_MASK      0x40
#define USB2DC_DOEPINT0_BACK2BACKSETUP_SHIFT     6 
#define USB2DC_DOEPINT0_BACK2BACKSETUP_BIT       0x1
#define USB2DC_DOEPINT0_BACK2BACKSETUP_BITWIDTH  1
// Reserved3 bitfiled (RO) Reset=0
#define USB2DC_DOEPINT0_RESERVED3_MASK           0x80
#define USB2DC_DOEPINT0_RESERVED3_SHIFT          7 
#define USB2DC_DOEPINT0_RESERVED3_BIT            0x1
#define USB2DC_DOEPINT0_RESERVED3_BITWIDTH       1
// OutPktErr bitfiled (RO) Reset=0
#define USB2DC_DOEPINT0_OUTPKTERR_MASK           0x100
#define USB2DC_DOEPINT0_OUTPKTERR_SHIFT          8 
#define USB2DC_DOEPINT0_OUTPKTERR_BIT            0x1
#define USB2DC_DOEPINT0_OUTPKTERR_BITWIDTH       1
// BNAIntr bitfiled (RO) Reset=0
#define USB2DC_DOEPINT0_BNAINTR_MASK             0x200
#define USB2DC_DOEPINT0_BNAINTR_SHIFT            9 
#define USB2DC_DOEPINT0_BNAINTR_BIT              0x1
#define USB2DC_DOEPINT0_BNAINTR_BITWIDTH         1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DOEPINT0_RESERVED2_MASK           0x400
#define USB2DC_DOEPINT0_RESERVED2_SHIFT          10 
#define USB2DC_DOEPINT0_RESERVED2_BIT            0x1
#define USB2DC_DOEPINT0_RESERVED2_BITWIDTH       1
// PktDrpSts bitfiled (RO) Reset=0
#define USB2DC_DOEPINT0_PKTDRPSTS_MASK           0x800
#define USB2DC_DOEPINT0_PKTDRPSTS_SHIFT          11 
#define USB2DC_DOEPINT0_PKTDRPSTS_BIT            0x1
#define USB2DC_DOEPINT0_PKTDRPSTS_BITWIDTH       1
// BbleErr bitfiled (RO) Reset=0
#define USB2DC_DOEPINT0_BBLEERR_MASK             0x1000
#define USB2DC_DOEPINT0_BBLEERR_SHIFT            12 
#define USB2DC_DOEPINT0_BBLEERR_BIT              0x1
#define USB2DC_DOEPINT0_BBLEERR_BITWIDTH         1
// NAKIntrpt bitfiled (RO) Reset=0
#define USB2DC_DOEPINT0_NAKINTRPT_MASK           0x2000
#define USB2DC_DOEPINT0_NAKINTRPT_SHIFT          13 
#define USB2DC_DOEPINT0_NAKINTRPT_BIT            0x1
#define USB2DC_DOEPINT0_NAKINTRPT_BITWIDTH       1
// NYETIntrpt bitfiled (RO) Reset=0
#define USB2DC_DOEPINT0_NYETINTRPT_MASK          0x4000
#define USB2DC_DOEPINT0_NYETINTRPT_SHIFT         14 
#define USB2DC_DOEPINT0_NYETINTRPT_BIT           0x1
#define USB2DC_DOEPINT0_NYETINTRPT_BITWIDTH      1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DOEPINT0_RESERVED_MASK            0xFFFF8000
#define USB2DC_DOEPINT0_RESERVED_SHIFT           15 
#define USB2DC_DOEPINT0_RESERVED_BIT             0x1FFFF
#define USB2DC_DOEPINT0_RESERVED_BITWIDTH        17
// DOEPTSIZ0 Register
#define USB2DC_DOEPTSIZ0_OFS                     0x00000B10
// XferSize bitfiled (RW) Reset=0
#define USB2DC_DOEPTSIZ0_XFERSIZE_MASK           0x7F
#define USB2DC_DOEPTSIZ0_XFERSIZE_SHIFT          0 
#define USB2DC_DOEPTSIZ0_XFERSIZE_BIT            0x7F
#define USB2DC_DOEPTSIZ0_XFERSIZE_BITWIDTH       7
// Reserved3 bitfiled (RO) Reset=0
#define USB2DC_DOEPTSIZ0_RESERVED3_MASK          0x7FF80
#define USB2DC_DOEPTSIZ0_RESERVED3_SHIFT         7 
#define USB2DC_DOEPTSIZ0_RESERVED3_BIT           0xFFF
#define USB2DC_DOEPTSIZ0_RESERVED3_BITWIDTH      12
// PktCnt bitfiled (RW) Reset=0
#define USB2DC_DOEPTSIZ0_PKTCNT_MASK             0x80000
#define USB2DC_DOEPTSIZ0_PKTCNT_SHIFT            19 
#define USB2DC_DOEPTSIZ0_PKTCNT_BIT              0x1
#define USB2DC_DOEPTSIZ0_PKTCNT_BITWIDTH         1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DOEPTSIZ0_RESERVED2_MASK          0x1FF00000
#define USB2DC_DOEPTSIZ0_RESERVED2_SHIFT         20 
#define USB2DC_DOEPTSIZ0_RESERVED2_BIT           0x1FF
#define USB2DC_DOEPTSIZ0_RESERVED2_BITWIDTH      9
// SUPCnt bitfiled (RW) Reset=0
#define USB2DC_DOEPTSIZ0_SUPCNT_MASK             0x60000000
#define USB2DC_DOEPTSIZ0_SUPCNT_SHIFT            29 
#define USB2DC_DOEPTSIZ0_SUPCNT_BIT              0x3
#define USB2DC_DOEPTSIZ0_SUPCNT_BITWIDTH         2
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DOEPTSIZ0_RESERVED_MASK           0x80000000
#define USB2DC_DOEPTSIZ0_RESERVED_SHIFT          31 
#define USB2DC_DOEPTSIZ0_RESERVED_BIT            0x1
#define USB2DC_DOEPTSIZ0_RESERVED_BITWIDTH       1
// DOEPDMA0 Register
#define USB2DC_DOEPDMA0_OFS                      0x00000B14
// DMAAddr bitfiled (RW) Reset=0
#define USB2DC_DOEPDMA0_DMAADDR_MASK             0xFFFFFFFF
#define USB2DC_DOEPDMA0_DMAADDR_SHIFT            0 
#define USB2DC_DOEPDMA0_DMAADDR_BIT              0xFFFFFFFF
#define USB2DC_DOEPDMA0_DMAADDR_BITWIDTH         32
// DOEPDMAB0 Register
#define USB2DC_DOEPDMAB0_OFS                     0x00000B1C
// DMABufferAddr bitfiled (RO) Reset=0
#define USB2DC_DOEPDMAB0_DMABUFFERADDR_MASK      0xFFFFFFFF
#define USB2DC_DOEPDMAB0_DMABUFFERADDR_SHIFT     0 
#define USB2DC_DOEPDMAB0_DMABUFFERADDR_BIT       0xFFFFFFFF
#define USB2DC_DOEPDMAB0_DMABUFFERADDR_BITWIDTH  32
// DOEPCTL1 Register
#define USB2DC_DOEPCTL1_OFS                      0x00000B20
// MPS bitfiled (RW) Reset=0
#define USB2DC_DOEPCTL1_MPS_MASK                 0x7FF
#define USB2DC_DOEPCTL1_MPS_SHIFT                0 
#define USB2DC_DOEPCTL1_MPS_BIT                  0x7FF
#define USB2DC_DOEPCTL1_MPS_BITWIDTH             11
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL1_RESERVED2_MASK           0x7800
#define USB2DC_DOEPCTL1_RESERVED2_SHIFT          11 
#define USB2DC_DOEPCTL1_RESERVED2_BIT            0xF
#define USB2DC_DOEPCTL1_RESERVED2_BITWIDTH       4
// USBActEP bitfiled (RW) Reset=0
#define USB2DC_DOEPCTL1_USBACTEP_MASK            0x8000
#define USB2DC_DOEPCTL1_USBACTEP_SHIFT           15 
#define USB2DC_DOEPCTL1_USBACTEP_BIT             0x1
#define USB2DC_DOEPCTL1_USBACTEP_BITWIDTH        1
// DPID bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL1_DPID_MASK                0x10000
#define USB2DC_DOEPCTL1_DPID_SHIFT               16 
#define USB2DC_DOEPCTL1_DPID_BIT                 0x1
#define USB2DC_DOEPCTL1_DPID_BITWIDTH            1
// NAKSts bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL1_NAKSTS_MASK              0x20000
#define USB2DC_DOEPCTL1_NAKSTS_SHIFT             17 
#define USB2DC_DOEPCTL1_NAKSTS_BIT               0x1
#define USB2DC_DOEPCTL1_NAKSTS_BITWIDTH          1
// EPType bitfiled (RW) Reset=0
#define USB2DC_DOEPCTL1_EPTYPE_MASK              0xC0000
#define USB2DC_DOEPCTL1_EPTYPE_SHIFT             18 
#define USB2DC_DOEPCTL1_EPTYPE_BIT               0x3
#define USB2DC_DOEPCTL1_EPTYPE_BITWIDTH          2
// Snp bitfiled (RW) Reset=0
#define USB2DC_DOEPCTL1_SNP_MASK                 0x100000
#define USB2DC_DOEPCTL1_SNP_SHIFT                20 
#define USB2DC_DOEPCTL1_SNP_BIT                  0x1
#define USB2DC_DOEPCTL1_SNP_BITWIDTH             1
// Stall bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL1_STALL_MASK               0x200000
#define USB2DC_DOEPCTL1_STALL_SHIFT              21 
#define USB2DC_DOEPCTL1_STALL_BIT                0x1
#define USB2DC_DOEPCTL1_STALL_BITWIDTH           1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL1_RESERVED_MASK            0x3C00000
#define USB2DC_DOEPCTL1_RESERVED_SHIFT           22 
#define USB2DC_DOEPCTL1_RESERVED_BIT             0xF
#define USB2DC_DOEPCTL1_RESERVED_BITWIDTH        4
// CNAK bitfiled (WO) Reset=0
#define USB2DC_DOEPCTL1_CNAK_MASK                0x4000000
#define USB2DC_DOEPCTL1_CNAK_SHIFT               26 
#define USB2DC_DOEPCTL1_CNAK_BIT                 0x1
#define USB2DC_DOEPCTL1_CNAK_BITWIDTH            1
// SNAK bitfiled (WO) Reset=0
#define USB2DC_DOEPCTL1_SNAK_MASK                0x8000000
#define USB2DC_DOEPCTL1_SNAK_SHIFT               27 
#define USB2DC_DOEPCTL1_SNAK_BIT                 0x1
#define USB2DC_DOEPCTL1_SNAK_BITWIDTH            1
// SetD0PID bitfiled (WO) Reset=0
#define USB2DC_DOEPCTL1_SETD0PID_MASK            0x10000000
#define USB2DC_DOEPCTL1_SETD0PID_SHIFT           28 
#define USB2DC_DOEPCTL1_SETD0PID_BIT             0x1
#define USB2DC_DOEPCTL1_SETD0PID_BITWIDTH        1
// SetD1PID bitfiled (WO) Reset=0
#define USB2DC_DOEPCTL1_SETD1PID_MASK            0x20000000
#define USB2DC_DOEPCTL1_SETD1PID_SHIFT           29 
#define USB2DC_DOEPCTL1_SETD1PID_BIT             0x1
#define USB2DC_DOEPCTL1_SETD1PID_BITWIDTH        1
// EPDis bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL1_EPDIS_MASK               0x40000000
#define USB2DC_DOEPCTL1_EPDIS_SHIFT              30 
#define USB2DC_DOEPCTL1_EPDIS_BIT                0x1
#define USB2DC_DOEPCTL1_EPDIS_BITWIDTH           1
// EPEna bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL1_EPENA_MASK               0x80000000
#define USB2DC_DOEPCTL1_EPENA_SHIFT              31 
#define USB2DC_DOEPCTL1_EPENA_BIT                0x1
#define USB2DC_DOEPCTL1_EPENA_BITWIDTH           1
// DOEPINT1 Register
#define USB2DC_DOEPINT1_OFS                      0x00000B28
// XferCompl bitfiled (RO) Reset=0
#define USB2DC_DOEPINT1_XFERCOMPL_MASK           0x1
#define USB2DC_DOEPINT1_XFERCOMPL_SHIFT          0 
#define USB2DC_DOEPINT1_XFERCOMPL_BIT            0x1
#define USB2DC_DOEPINT1_XFERCOMPL_BITWIDTH       1
// EPDisbld bitfiled (RO) Reset=0
#define USB2DC_DOEPINT1_EPDISBLD_MASK            0x2
#define USB2DC_DOEPINT1_EPDISBLD_SHIFT           1 
#define USB2DC_DOEPINT1_EPDISBLD_BIT             0x1
#define USB2DC_DOEPINT1_EPDISBLD_BITWIDTH        1
// AHBErr bitfiled (RO) Reset=0
#define USB2DC_DOEPINT1_AHBERR_MASK              0x4
#define USB2DC_DOEPINT1_AHBERR_SHIFT             2 
#define USB2DC_DOEPINT1_AHBERR_BIT               0x1
#define USB2DC_DOEPINT1_AHBERR_BITWIDTH          1
// SetUp bitfiled (RO) Reset=0
#define USB2DC_DOEPINT1_SETUP_MASK               0x8
#define USB2DC_DOEPINT1_SETUP_SHIFT              3 
#define USB2DC_DOEPINT1_SETUP_BIT                0x1
#define USB2DC_DOEPINT1_SETUP_BITWIDTH           1
// OUTTknEPdis bitfiled (RO) Reset=0
#define USB2DC_DOEPINT1_OUTTKNEPDIS_MASK         0x10
#define USB2DC_DOEPINT1_OUTTKNEPDIS_SHIFT        4 
#define USB2DC_DOEPINT1_OUTTKNEPDIS_BIT          0x1
#define USB2DC_DOEPINT1_OUTTKNEPDIS_BITWIDTH     1
// StsPhseRcvd bitfiled (RO) Reset=0
#define USB2DC_DOEPINT1_STSPHSERCVD_MASK         0x20
#define USB2DC_DOEPINT1_STSPHSERCVD_SHIFT        5 
#define USB2DC_DOEPINT1_STSPHSERCVD_BIT          0x1
#define USB2DC_DOEPINT1_STSPHSERCVD_BITWIDTH     1
// Back2BackSETup bitfiled (RO) Reset=0
#define USB2DC_DOEPINT1_BACK2BACKSETUP_MASK      0x40
#define USB2DC_DOEPINT1_BACK2BACKSETUP_SHIFT     6 
#define USB2DC_DOEPINT1_BACK2BACKSETUP_BIT       0x1
#define USB2DC_DOEPINT1_BACK2BACKSETUP_BITWIDTH  1
// Reserved3 bitfiled (RO) Reset=0
#define USB2DC_DOEPINT1_RESERVED3_MASK           0x80
#define USB2DC_DOEPINT1_RESERVED3_SHIFT          7 
#define USB2DC_DOEPINT1_RESERVED3_BIT            0x1
#define USB2DC_DOEPINT1_RESERVED3_BITWIDTH       1
// OutPktErr bitfiled (RO) Reset=0
#define USB2DC_DOEPINT1_OUTPKTERR_MASK           0x100
#define USB2DC_DOEPINT1_OUTPKTERR_SHIFT          8 
#define USB2DC_DOEPINT1_OUTPKTERR_BIT            0x1
#define USB2DC_DOEPINT1_OUTPKTERR_BITWIDTH       1
// BNAIntr bitfiled (RO) Reset=0
#define USB2DC_DOEPINT1_BNAINTR_MASK             0x200
#define USB2DC_DOEPINT1_BNAINTR_SHIFT            9 
#define USB2DC_DOEPINT1_BNAINTR_BIT              0x1
#define USB2DC_DOEPINT1_BNAINTR_BITWIDTH         1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DOEPINT1_RESERVED2_MASK           0x400
#define USB2DC_DOEPINT1_RESERVED2_SHIFT          10 
#define USB2DC_DOEPINT1_RESERVED2_BIT            0x1
#define USB2DC_DOEPINT1_RESERVED2_BITWIDTH       1
// PktDrpSts bitfiled (RO) Reset=0
#define USB2DC_DOEPINT1_PKTDRPSTS_MASK           0x800
#define USB2DC_DOEPINT1_PKTDRPSTS_SHIFT          11 
#define USB2DC_DOEPINT1_PKTDRPSTS_BIT            0x1
#define USB2DC_DOEPINT1_PKTDRPSTS_BITWIDTH       1
// BbleErr bitfiled (RO) Reset=0
#define USB2DC_DOEPINT1_BBLEERR_MASK             0x1000
#define USB2DC_DOEPINT1_BBLEERR_SHIFT            12 
#define USB2DC_DOEPINT1_BBLEERR_BIT              0x1
#define USB2DC_DOEPINT1_BBLEERR_BITWIDTH         1
// NAKIntrpt bitfiled (RO) Reset=0
#define USB2DC_DOEPINT1_NAKINTRPT_MASK           0x2000
#define USB2DC_DOEPINT1_NAKINTRPT_SHIFT          13 
#define USB2DC_DOEPINT1_NAKINTRPT_BIT            0x1
#define USB2DC_DOEPINT1_NAKINTRPT_BITWIDTH       1
// NYETIntrpt bitfiled (RO) Reset=0
#define USB2DC_DOEPINT1_NYETINTRPT_MASK          0x4000
#define USB2DC_DOEPINT1_NYETINTRPT_SHIFT         14 
#define USB2DC_DOEPINT1_NYETINTRPT_BIT           0x1
#define USB2DC_DOEPINT1_NYETINTRPT_BITWIDTH      1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DOEPINT1_RESERVED_MASK            0xFFFF8000
#define USB2DC_DOEPINT1_RESERVED_SHIFT           15 
#define USB2DC_DOEPINT1_RESERVED_BIT             0x1FFFF
#define USB2DC_DOEPINT1_RESERVED_BITWIDTH        17
// DOEPTSIZ1 Register
#define USB2DC_DOEPTSIZ1_OFS                     0x00000B30
// XferSize bitfiled (RW) Reset=0
#define USB2DC_DOEPTSIZ1_XFERSIZE_MASK           0x7FFFF
#define USB2DC_DOEPTSIZ1_XFERSIZE_SHIFT          0 
#define USB2DC_DOEPTSIZ1_XFERSIZE_BIT            0x7FFFF
#define USB2DC_DOEPTSIZ1_XFERSIZE_BITWIDTH       19
// PktCnt bitfiled (RW) Reset=0
#define USB2DC_DOEPTSIZ1_PKTCNT_MASK             0x1FF80000
#define USB2DC_DOEPTSIZ1_PKTCNT_SHIFT            19 
#define USB2DC_DOEPTSIZ1_PKTCNT_BIT              0x3FF
#define USB2DC_DOEPTSIZ1_PKTCNT_BITWIDTH         10
// RxDPID bitfiled (RO) Reset=0
#define USB2DC_DOEPTSIZ1_RXDPID_MASK             0x60000000
#define USB2DC_DOEPTSIZ1_RXDPID_SHIFT            29 
#define USB2DC_DOEPTSIZ1_RXDPID_BIT              0x3
#define USB2DC_DOEPTSIZ1_RXDPID_BITWIDTH         2
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DOEPTSIZ1_RESERVED_MASK           0x80000000
#define USB2DC_DOEPTSIZ1_RESERVED_SHIFT          31 
#define USB2DC_DOEPTSIZ1_RESERVED_BIT            0x1
#define USB2DC_DOEPTSIZ1_RESERVED_BITWIDTH       1
// DOEPDMA1 Register
#define USB2DC_DOEPDMA1_OFS                      0x00000B34
// DMAAddr bitfiled (RW) Reset=0
#define USB2DC_DOEPDMA1_DMAADDR_MASK             0xFFFFFFFF
#define USB2DC_DOEPDMA1_DMAADDR_SHIFT            0 
#define USB2DC_DOEPDMA1_DMAADDR_BIT              0xFFFFFFFF
#define USB2DC_DOEPDMA1_DMAADDR_BITWIDTH         32
// DOEPDMAB1 Register
#define USB2DC_DOEPDMAB1_OFS                     0x00000B3C
// DMABufferAddr bitfiled (RO) Reset=0
#define USB2DC_DOEPDMAB1_DMABUFFERADDR_MASK      0xFFFFFFFF
#define USB2DC_DOEPDMAB1_DMABUFFERADDR_SHIFT     0 
#define USB2DC_DOEPDMAB1_DMABUFFERADDR_BIT       0xFFFFFFFF
#define USB2DC_DOEPDMAB1_DMABUFFERADDR_BITWIDTH  32
// DOEPCTL2 Register
#define USB2DC_DOEPCTL2_OFS                      0x00000B40
// MPS bitfiled (RW) Reset=0
#define USB2DC_DOEPCTL2_MPS_MASK                 0x7FF
#define USB2DC_DOEPCTL2_MPS_SHIFT                0 
#define USB2DC_DOEPCTL2_MPS_BIT                  0x7FF
#define USB2DC_DOEPCTL2_MPS_BITWIDTH             11
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL2_RESERVED2_MASK           0x7800
#define USB2DC_DOEPCTL2_RESERVED2_SHIFT          11 
#define USB2DC_DOEPCTL2_RESERVED2_BIT            0xF
#define USB2DC_DOEPCTL2_RESERVED2_BITWIDTH       4
// USBActEP bitfiled (RW) Reset=0
#define USB2DC_DOEPCTL2_USBACTEP_MASK            0x8000
#define USB2DC_DOEPCTL2_USBACTEP_SHIFT           15 
#define USB2DC_DOEPCTL2_USBACTEP_BIT             0x1
#define USB2DC_DOEPCTL2_USBACTEP_BITWIDTH        1
// DPID bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL2_DPID_MASK                0x10000
#define USB2DC_DOEPCTL2_DPID_SHIFT               16 
#define USB2DC_DOEPCTL2_DPID_BIT                 0x1
#define USB2DC_DOEPCTL2_DPID_BITWIDTH            1
// NAKSts bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL2_NAKSTS_MASK              0x20000
#define USB2DC_DOEPCTL2_NAKSTS_SHIFT             17 
#define USB2DC_DOEPCTL2_NAKSTS_BIT               0x1
#define USB2DC_DOEPCTL2_NAKSTS_BITWIDTH          1
// EPType bitfiled (RW) Reset=0
#define USB2DC_DOEPCTL2_EPTYPE_MASK              0xC0000
#define USB2DC_DOEPCTL2_EPTYPE_SHIFT             18 
#define USB2DC_DOEPCTL2_EPTYPE_BIT               0x3
#define USB2DC_DOEPCTL2_EPTYPE_BITWIDTH          2
// Snp bitfiled (RW) Reset=0
#define USB2DC_DOEPCTL2_SNP_MASK                 0x100000
#define USB2DC_DOEPCTL2_SNP_SHIFT                20 
#define USB2DC_DOEPCTL2_SNP_BIT                  0x1
#define USB2DC_DOEPCTL2_SNP_BITWIDTH             1
// Stall bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL2_STALL_MASK               0x200000
#define USB2DC_DOEPCTL2_STALL_SHIFT              21 
#define USB2DC_DOEPCTL2_STALL_BIT                0x1
#define USB2DC_DOEPCTL2_STALL_BITWIDTH           1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL2_RESERVED_MASK            0x3C00000
#define USB2DC_DOEPCTL2_RESERVED_SHIFT           22 
#define USB2DC_DOEPCTL2_RESERVED_BIT             0xF
#define USB2DC_DOEPCTL2_RESERVED_BITWIDTH        4
// CNAK bitfiled (WO) Reset=0
#define USB2DC_DOEPCTL2_CNAK_MASK                0x4000000
#define USB2DC_DOEPCTL2_CNAK_SHIFT               26 
#define USB2DC_DOEPCTL2_CNAK_BIT                 0x1
#define USB2DC_DOEPCTL2_CNAK_BITWIDTH            1
// SNAK bitfiled (WO) Reset=0
#define USB2DC_DOEPCTL2_SNAK_MASK                0x8000000
#define USB2DC_DOEPCTL2_SNAK_SHIFT               27 
#define USB2DC_DOEPCTL2_SNAK_BIT                 0x1
#define USB2DC_DOEPCTL2_SNAK_BITWIDTH            1
// SetD0PID bitfiled (WO) Reset=0
#define USB2DC_DOEPCTL2_SETD0PID_MASK            0x10000000
#define USB2DC_DOEPCTL2_SETD0PID_SHIFT           28 
#define USB2DC_DOEPCTL2_SETD0PID_BIT             0x1
#define USB2DC_DOEPCTL2_SETD0PID_BITWIDTH        1
// SetD1PID bitfiled (WO) Reset=0
#define USB2DC_DOEPCTL2_SETD1PID_MASK            0x20000000
#define USB2DC_DOEPCTL2_SETD1PID_SHIFT           29 
#define USB2DC_DOEPCTL2_SETD1PID_BIT             0x1
#define USB2DC_DOEPCTL2_SETD1PID_BITWIDTH        1
// EPDis bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL2_EPDIS_MASK               0x40000000
#define USB2DC_DOEPCTL2_EPDIS_SHIFT              30 
#define USB2DC_DOEPCTL2_EPDIS_BIT                0x1
#define USB2DC_DOEPCTL2_EPDIS_BITWIDTH           1
// EPEna bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL2_EPENA_MASK               0x80000000
#define USB2DC_DOEPCTL2_EPENA_SHIFT              31 
#define USB2DC_DOEPCTL2_EPENA_BIT                0x1
#define USB2DC_DOEPCTL2_EPENA_BITWIDTH           1
// DOEPINT2 Register
#define USB2DC_DOEPINT2_OFS                      0x00000B48
// XferCompl bitfiled (RO) Reset=0
#define USB2DC_DOEPINT2_XFERCOMPL_MASK           0x1
#define USB2DC_DOEPINT2_XFERCOMPL_SHIFT          0 
#define USB2DC_DOEPINT2_XFERCOMPL_BIT            0x1
#define USB2DC_DOEPINT2_XFERCOMPL_BITWIDTH       1
// EPDisbld bitfiled (RO) Reset=0
#define USB2DC_DOEPINT2_EPDISBLD_MASK            0x2
#define USB2DC_DOEPINT2_EPDISBLD_SHIFT           1 
#define USB2DC_DOEPINT2_EPDISBLD_BIT             0x1
#define USB2DC_DOEPINT2_EPDISBLD_BITWIDTH        1
// AHBErr bitfiled (RO) Reset=0
#define USB2DC_DOEPINT2_AHBERR_MASK              0x4
#define USB2DC_DOEPINT2_AHBERR_SHIFT             2 
#define USB2DC_DOEPINT2_AHBERR_BIT               0x1
#define USB2DC_DOEPINT2_AHBERR_BITWIDTH          1
// SetUp bitfiled (RO) Reset=0
#define USB2DC_DOEPINT2_SETUP_MASK               0x8
#define USB2DC_DOEPINT2_SETUP_SHIFT              3 
#define USB2DC_DOEPINT2_SETUP_BIT                0x1
#define USB2DC_DOEPINT2_SETUP_BITWIDTH           1
// OUTTknEPdis bitfiled (RO) Reset=0
#define USB2DC_DOEPINT2_OUTTKNEPDIS_MASK         0x10
#define USB2DC_DOEPINT2_OUTTKNEPDIS_SHIFT        4 
#define USB2DC_DOEPINT2_OUTTKNEPDIS_BIT          0x1
#define USB2DC_DOEPINT2_OUTTKNEPDIS_BITWIDTH     1
// StsPhseRcvd bitfiled (RO) Reset=0
#define USB2DC_DOEPINT2_STSPHSERCVD_MASK         0x20
#define USB2DC_DOEPINT2_STSPHSERCVD_SHIFT        5 
#define USB2DC_DOEPINT2_STSPHSERCVD_BIT          0x1
#define USB2DC_DOEPINT2_STSPHSERCVD_BITWIDTH     1
// Back2BackSETup bitfiled (RO) Reset=0
#define USB2DC_DOEPINT2_BACK2BACKSETUP_MASK      0x40
#define USB2DC_DOEPINT2_BACK2BACKSETUP_SHIFT     6 
#define USB2DC_DOEPINT2_BACK2BACKSETUP_BIT       0x1
#define USB2DC_DOEPINT2_BACK2BACKSETUP_BITWIDTH  1
// Reserved3 bitfiled (RO) Reset=0
#define USB2DC_DOEPINT2_RESERVED3_MASK           0x80
#define USB2DC_DOEPINT2_RESERVED3_SHIFT          7 
#define USB2DC_DOEPINT2_RESERVED3_BIT            0x1
#define USB2DC_DOEPINT2_RESERVED3_BITWIDTH       1
// OutPktErr bitfiled (RO) Reset=0
#define USB2DC_DOEPINT2_OUTPKTERR_MASK           0x100
#define USB2DC_DOEPINT2_OUTPKTERR_SHIFT          8 
#define USB2DC_DOEPINT2_OUTPKTERR_BIT            0x1
#define USB2DC_DOEPINT2_OUTPKTERR_BITWIDTH       1
// BNAIntr bitfiled (RO) Reset=0
#define USB2DC_DOEPINT2_BNAINTR_MASK             0x200
#define USB2DC_DOEPINT2_BNAINTR_SHIFT            9 
#define USB2DC_DOEPINT2_BNAINTR_BIT              0x1
#define USB2DC_DOEPINT2_BNAINTR_BITWIDTH         1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DOEPINT2_RESERVED2_MASK           0x400
#define USB2DC_DOEPINT2_RESERVED2_SHIFT          10 
#define USB2DC_DOEPINT2_RESERVED2_BIT            0x1
#define USB2DC_DOEPINT2_RESERVED2_BITWIDTH       1
// PktDrpSts bitfiled (RO) Reset=0
#define USB2DC_DOEPINT2_PKTDRPSTS_MASK           0x800
#define USB2DC_DOEPINT2_PKTDRPSTS_SHIFT          11 
#define USB2DC_DOEPINT2_PKTDRPSTS_BIT            0x1
#define USB2DC_DOEPINT2_PKTDRPSTS_BITWIDTH       1
// BbleErr bitfiled (RO) Reset=0
#define USB2DC_DOEPINT2_BBLEERR_MASK             0x1000
#define USB2DC_DOEPINT2_BBLEERR_SHIFT            12 
#define USB2DC_DOEPINT2_BBLEERR_BIT              0x1
#define USB2DC_DOEPINT2_BBLEERR_BITWIDTH         1
// NAKIntrpt bitfiled (RO) Reset=0
#define USB2DC_DOEPINT2_NAKINTRPT_MASK           0x2000
#define USB2DC_DOEPINT2_NAKINTRPT_SHIFT          13 
#define USB2DC_DOEPINT2_NAKINTRPT_BIT            0x1
#define USB2DC_DOEPINT2_NAKINTRPT_BITWIDTH       1
// NYETIntrpt bitfiled (RO) Reset=0
#define USB2DC_DOEPINT2_NYETINTRPT_MASK          0x4000
#define USB2DC_DOEPINT2_NYETINTRPT_SHIFT         14 
#define USB2DC_DOEPINT2_NYETINTRPT_BIT           0x1
#define USB2DC_DOEPINT2_NYETINTRPT_BITWIDTH      1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DOEPINT2_RESERVED_MASK            0xFFFF8000
#define USB2DC_DOEPINT2_RESERVED_SHIFT           15 
#define USB2DC_DOEPINT2_RESERVED_BIT             0x1FFFF
#define USB2DC_DOEPINT2_RESERVED_BITWIDTH        17
// DOEPTSIZ2 Register
#define USB2DC_DOEPTSIZ2_OFS                     0x00000B50
// XferSize bitfiled (RW) Reset=0
#define USB2DC_DOEPTSIZ2_XFERSIZE_MASK           0x7FFFF
#define USB2DC_DOEPTSIZ2_XFERSIZE_SHIFT          0 
#define USB2DC_DOEPTSIZ2_XFERSIZE_BIT            0x7FFFF
#define USB2DC_DOEPTSIZ2_XFERSIZE_BITWIDTH       19
// PktCnt bitfiled (RW) Reset=0
#define USB2DC_DOEPTSIZ2_PKTCNT_MASK             0x1FF80000
#define USB2DC_DOEPTSIZ2_PKTCNT_SHIFT            19 
#define USB2DC_DOEPTSIZ2_PKTCNT_BIT              0x3FF
#define USB2DC_DOEPTSIZ2_PKTCNT_BITWIDTH         10
// RxDPID bitfiled (RO) Reset=0
#define USB2DC_DOEPTSIZ2_RXDPID_MASK             0x60000000
#define USB2DC_DOEPTSIZ2_RXDPID_SHIFT            29 
#define USB2DC_DOEPTSIZ2_RXDPID_BIT              0x3
#define USB2DC_DOEPTSIZ2_RXDPID_BITWIDTH         2
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DOEPTSIZ2_RESERVED_MASK           0x80000000
#define USB2DC_DOEPTSIZ2_RESERVED_SHIFT          31 
#define USB2DC_DOEPTSIZ2_RESERVED_BIT            0x1
#define USB2DC_DOEPTSIZ2_RESERVED_BITWIDTH       1
// DOEPDMA2 Register
#define USB2DC_DOEPDMA2_OFS                      0x00000B54
// DMAAddr bitfiled (RW) Reset=0
#define USB2DC_DOEPDMA2_DMAADDR_MASK             0xFFFFFFFF
#define USB2DC_DOEPDMA2_DMAADDR_SHIFT            0 
#define USB2DC_DOEPDMA2_DMAADDR_BIT              0xFFFFFFFF
#define USB2DC_DOEPDMA2_DMAADDR_BITWIDTH         32
// DOEPDMAB2 Register
#define USB2DC_DOEPDMAB2_OFS                     0x00000B5C
// DMABufferAddr bitfiled (RO) Reset=0
#define USB2DC_DOEPDMAB2_DMABUFFERADDR_MASK      0xFFFFFFFF
#define USB2DC_DOEPDMAB2_DMABUFFERADDR_SHIFT     0 
#define USB2DC_DOEPDMAB2_DMABUFFERADDR_BIT       0xFFFFFFFF
#define USB2DC_DOEPDMAB2_DMABUFFERADDR_BITWIDTH  32
// DOEPCTL3 Register
#define USB2DC_DOEPCTL3_OFS                      0x00000B60
// MPS bitfiled (RW) Reset=0
#define USB2DC_DOEPCTL3_MPS_MASK                 0x7FF
#define USB2DC_DOEPCTL3_MPS_SHIFT                0 
#define USB2DC_DOEPCTL3_MPS_BIT                  0x7FF
#define USB2DC_DOEPCTL3_MPS_BITWIDTH             11
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL3_RESERVED2_MASK           0x7800
#define USB2DC_DOEPCTL3_RESERVED2_SHIFT          11 
#define USB2DC_DOEPCTL3_RESERVED2_BIT            0xF
#define USB2DC_DOEPCTL3_RESERVED2_BITWIDTH       4
// USBActEP bitfiled (RW) Reset=0
#define USB2DC_DOEPCTL3_USBACTEP_MASK            0x8000
#define USB2DC_DOEPCTL3_USBACTEP_SHIFT           15 
#define USB2DC_DOEPCTL3_USBACTEP_BIT             0x1
#define USB2DC_DOEPCTL3_USBACTEP_BITWIDTH        1
// DPID bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL3_DPID_MASK                0x10000
#define USB2DC_DOEPCTL3_DPID_SHIFT               16 
#define USB2DC_DOEPCTL3_DPID_BIT                 0x1
#define USB2DC_DOEPCTL3_DPID_BITWIDTH            1
// NAKSts bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL3_NAKSTS_MASK              0x20000
#define USB2DC_DOEPCTL3_NAKSTS_SHIFT             17 
#define USB2DC_DOEPCTL3_NAKSTS_BIT               0x1
#define USB2DC_DOEPCTL3_NAKSTS_BITWIDTH          1
// EPType bitfiled (RW) Reset=0
#define USB2DC_DOEPCTL3_EPTYPE_MASK              0xC0000
#define USB2DC_DOEPCTL3_EPTYPE_SHIFT             18 
#define USB2DC_DOEPCTL3_EPTYPE_BIT               0x3
#define USB2DC_DOEPCTL3_EPTYPE_BITWIDTH          2
// Snp bitfiled (RW) Reset=0
#define USB2DC_DOEPCTL3_SNP_MASK                 0x100000
#define USB2DC_DOEPCTL3_SNP_SHIFT                20 
#define USB2DC_DOEPCTL3_SNP_BIT                  0x1
#define USB2DC_DOEPCTL3_SNP_BITWIDTH             1
// Stall bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL3_STALL_MASK               0x200000
#define USB2DC_DOEPCTL3_STALL_SHIFT              21 
#define USB2DC_DOEPCTL3_STALL_BIT                0x1
#define USB2DC_DOEPCTL3_STALL_BITWIDTH           1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL3_RESERVED_MASK            0x3C00000
#define USB2DC_DOEPCTL3_RESERVED_SHIFT           22 
#define USB2DC_DOEPCTL3_RESERVED_BIT             0xF
#define USB2DC_DOEPCTL3_RESERVED_BITWIDTH        4
// CNAK bitfiled (WO) Reset=0
#define USB2DC_DOEPCTL3_CNAK_MASK                0x4000000
#define USB2DC_DOEPCTL3_CNAK_SHIFT               26 
#define USB2DC_DOEPCTL3_CNAK_BIT                 0x1
#define USB2DC_DOEPCTL3_CNAK_BITWIDTH            1
// SNAK bitfiled (WO) Reset=0
#define USB2DC_DOEPCTL3_SNAK_MASK                0x8000000
#define USB2DC_DOEPCTL3_SNAK_SHIFT               27 
#define USB2DC_DOEPCTL3_SNAK_BIT                 0x1
#define USB2DC_DOEPCTL3_SNAK_BITWIDTH            1
// SetD0PID bitfiled (WO) Reset=0
#define USB2DC_DOEPCTL3_SETD0PID_MASK            0x10000000
#define USB2DC_DOEPCTL3_SETD0PID_SHIFT           28 
#define USB2DC_DOEPCTL3_SETD0PID_BIT             0x1
#define USB2DC_DOEPCTL3_SETD0PID_BITWIDTH        1
// SetD1PID bitfiled (WO) Reset=0
#define USB2DC_DOEPCTL3_SETD1PID_MASK            0x20000000
#define USB2DC_DOEPCTL3_SETD1PID_SHIFT           29 
#define USB2DC_DOEPCTL3_SETD1PID_BIT             0x1
#define USB2DC_DOEPCTL3_SETD1PID_BITWIDTH        1
// EPDis bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL3_EPDIS_MASK               0x40000000
#define USB2DC_DOEPCTL3_EPDIS_SHIFT              30 
#define USB2DC_DOEPCTL3_EPDIS_BIT                0x1
#define USB2DC_DOEPCTL3_EPDIS_BITWIDTH           1
// EPEna bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL3_EPENA_MASK               0x80000000
#define USB2DC_DOEPCTL3_EPENA_SHIFT              31 
#define USB2DC_DOEPCTL3_EPENA_BIT                0x1
#define USB2DC_DOEPCTL3_EPENA_BITWIDTH           1
// DOEPINT3 Register
#define USB2DC_DOEPINT3_OFS                      0x00000B68
// XferCompl bitfiled (RO) Reset=0
#define USB2DC_DOEPINT3_XFERCOMPL_MASK           0x1
#define USB2DC_DOEPINT3_XFERCOMPL_SHIFT          0 
#define USB2DC_DOEPINT3_XFERCOMPL_BIT            0x1
#define USB2DC_DOEPINT3_XFERCOMPL_BITWIDTH       1
// EPDisbld bitfiled (RO) Reset=0
#define USB2DC_DOEPINT3_EPDISBLD_MASK            0x2
#define USB2DC_DOEPINT3_EPDISBLD_SHIFT           1 
#define USB2DC_DOEPINT3_EPDISBLD_BIT             0x1
#define USB2DC_DOEPINT3_EPDISBLD_BITWIDTH        1
// AHBErr bitfiled (RO) Reset=0
#define USB2DC_DOEPINT3_AHBERR_MASK              0x4
#define USB2DC_DOEPINT3_AHBERR_SHIFT             2 
#define USB2DC_DOEPINT3_AHBERR_BIT               0x1
#define USB2DC_DOEPINT3_AHBERR_BITWIDTH          1
// SetUp bitfiled (RO) Reset=0
#define USB2DC_DOEPINT3_SETUP_MASK               0x8
#define USB2DC_DOEPINT3_SETUP_SHIFT              3 
#define USB2DC_DOEPINT3_SETUP_BIT                0x1
#define USB2DC_DOEPINT3_SETUP_BITWIDTH           1
// OUTTknEPdis bitfiled (RO) Reset=0
#define USB2DC_DOEPINT3_OUTTKNEPDIS_MASK         0x10
#define USB2DC_DOEPINT3_OUTTKNEPDIS_SHIFT        4 
#define USB2DC_DOEPINT3_OUTTKNEPDIS_BIT          0x1
#define USB2DC_DOEPINT3_OUTTKNEPDIS_BITWIDTH     1
// StsPhseRcvd bitfiled (RO) Reset=0
#define USB2DC_DOEPINT3_STSPHSERCVD_MASK         0x20
#define USB2DC_DOEPINT3_STSPHSERCVD_SHIFT        5 
#define USB2DC_DOEPINT3_STSPHSERCVD_BIT          0x1
#define USB2DC_DOEPINT3_STSPHSERCVD_BITWIDTH     1
// Back2BackSETup bitfiled (RO) Reset=0
#define USB2DC_DOEPINT3_BACK2BACKSETUP_MASK      0x40
#define USB2DC_DOEPINT3_BACK2BACKSETUP_SHIFT     6 
#define USB2DC_DOEPINT3_BACK2BACKSETUP_BIT       0x1
#define USB2DC_DOEPINT3_BACK2BACKSETUP_BITWIDTH  1
// Reserved3 bitfiled (RO) Reset=0
#define USB2DC_DOEPINT3_RESERVED3_MASK           0x80
#define USB2DC_DOEPINT3_RESERVED3_SHIFT          7 
#define USB2DC_DOEPINT3_RESERVED3_BIT            0x1
#define USB2DC_DOEPINT3_RESERVED3_BITWIDTH       1
// OutPktErr bitfiled (RO) Reset=0
#define USB2DC_DOEPINT3_OUTPKTERR_MASK           0x100
#define USB2DC_DOEPINT3_OUTPKTERR_SHIFT          8 
#define USB2DC_DOEPINT3_OUTPKTERR_BIT            0x1
#define USB2DC_DOEPINT3_OUTPKTERR_BITWIDTH       1
// BNAIntr bitfiled (RO) Reset=0
#define USB2DC_DOEPINT3_BNAINTR_MASK             0x200
#define USB2DC_DOEPINT3_BNAINTR_SHIFT            9 
#define USB2DC_DOEPINT3_BNAINTR_BIT              0x1
#define USB2DC_DOEPINT3_BNAINTR_BITWIDTH         1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_DOEPINT3_RESERVED2_MASK           0x400
#define USB2DC_DOEPINT3_RESERVED2_SHIFT          10 
#define USB2DC_DOEPINT3_RESERVED2_BIT            0x1
#define USB2DC_DOEPINT3_RESERVED2_BITWIDTH       1
// PktDrpSts bitfiled (RO) Reset=0
#define USB2DC_DOEPINT3_PKTDRPSTS_MASK           0x800
#define USB2DC_DOEPINT3_PKTDRPSTS_SHIFT          11 
#define USB2DC_DOEPINT3_PKTDRPSTS_BIT            0x1
#define USB2DC_DOEPINT3_PKTDRPSTS_BITWIDTH       1
// BbleErr bitfiled (RO) Reset=0
#define USB2DC_DOEPINT3_BBLEERR_MASK             0x1000
#define USB2DC_DOEPINT3_BBLEERR_SHIFT            12 
#define USB2DC_DOEPINT3_BBLEERR_BIT              0x1
#define USB2DC_DOEPINT3_BBLEERR_BITWIDTH         1
// NAKIntrpt bitfiled (RO) Reset=0
#define USB2DC_DOEPINT3_NAKINTRPT_MASK           0x2000
#define USB2DC_DOEPINT3_NAKINTRPT_SHIFT          13 
#define USB2DC_DOEPINT3_NAKINTRPT_BIT            0x1
#define USB2DC_DOEPINT3_NAKINTRPT_BITWIDTH       1
// NYETIntrpt bitfiled (RO) Reset=0
#define USB2DC_DOEPINT3_NYETINTRPT_MASK          0x4000
#define USB2DC_DOEPINT3_NYETINTRPT_SHIFT         14 
#define USB2DC_DOEPINT3_NYETINTRPT_BIT           0x1
#define USB2DC_DOEPINT3_NYETINTRPT_BITWIDTH      1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DOEPINT3_RESERVED_MASK            0xFFFF8000
#define USB2DC_DOEPINT3_RESERVED_SHIFT           15 
#define USB2DC_DOEPINT3_RESERVED_BIT             0x1FFFF
#define USB2DC_DOEPINT3_RESERVED_BITWIDTH        17
// DOEPTSIZ3 Register
#define USB2DC_DOEPTSIZ3_OFS                     0x00000B70
// XferSize bitfiled (RW) Reset=0
#define USB2DC_DOEPTSIZ3_XFERSIZE_MASK           0x7FFFF
#define USB2DC_DOEPTSIZ3_XFERSIZE_SHIFT          0 
#define USB2DC_DOEPTSIZ3_XFERSIZE_BIT            0x7FFFF
#define USB2DC_DOEPTSIZ3_XFERSIZE_BITWIDTH       19
// PktCnt bitfiled (RW) Reset=0
#define USB2DC_DOEPTSIZ3_PKTCNT_MASK             0x1FF80000
#define USB2DC_DOEPTSIZ3_PKTCNT_SHIFT            19 
#define USB2DC_DOEPTSIZ3_PKTCNT_BIT              0x3FF
#define USB2DC_DOEPTSIZ3_PKTCNT_BITWIDTH         10
// RxDPID bitfiled (RO) Reset=0
#define USB2DC_DOEPTSIZ3_RXDPID_MASK             0x60000000
#define USB2DC_DOEPTSIZ3_RXDPID_SHIFT            29 
#define USB2DC_DOEPTSIZ3_RXDPID_BIT              0x3
#define USB2DC_DOEPTSIZ3_RXDPID_BITWIDTH         2
// Reserved bitfiled (RO) Reset=0
#define USB2DC_DOEPTSIZ3_RESERVED_MASK           0x80000000
#define USB2DC_DOEPTSIZ3_RESERVED_SHIFT          31 
#define USB2DC_DOEPTSIZ3_RESERVED_BIT            0x1
#define USB2DC_DOEPTSIZ3_RESERVED_BITWIDTH       1
// DOEPDMA3 Register
#define USB2DC_DOEPDMA3_OFS                      0x00000B74
// DMAAddr bitfiled (RW) Reset=0
#define USB2DC_DOEPDMA3_DMAADDR_MASK             0xFFFFFFFF
#define USB2DC_DOEPDMA3_DMAADDR_SHIFT            0 
#define USB2DC_DOEPDMA3_DMAADDR_BIT              0xFFFFFFFF
#define USB2DC_DOEPDMA3_DMAADDR_BITWIDTH         32
// DOEPDMAB3 Register
#define USB2DC_DOEPDMAB3_OFS                     0x00000B7C
// DMABufferAddr bitfiled (RO) Reset=0
#define USB2DC_DOEPDMAB3_DMABUFFERADDR_MASK      0xFFFFFFFF
#define USB2DC_DOEPDMAB3_DMABUFFERADDR_SHIFT     0 
#define USB2DC_DOEPDMAB3_DMABUFFERADDR_BIT       0xFFFFFFFF
#define USB2DC_DOEPDMAB3_DMABUFFERADDR_BITWIDTH  32
// DOEPCTL4 Register
#define USB2DC_DOEPCTL4_OFS                      0x00000B80
// MPS bitfiled (RW) Reset=0
#define USB2DC_DOEPCTL4_MPS_MASK                 0x7FF
#define USB2DC_DOEPCTL4_MPS_SHIFT                0 
#define USB2DC_DOEPCTL4_MPS_BIT                  0x7FF
#define USB2DC_DOEPCTL4_MPS_BITWIDTH             11
// reserved2 bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL4_RESERVED2_MASK           0x7800
#define USB2DC_DOEPCTL4_RESERVED2_SHIFT          11 
#define USB2DC_DOEPCTL4_RESERVED2_BIT            0xF
#define USB2DC_DOEPCTL4_RESERVED2_BITWIDTH       4
// USBActEP bitfiled (RW) Reset=0
#define USB2DC_DOEPCTL4_USBACTEP_MASK            0x8000
#define USB2DC_DOEPCTL4_USBACTEP_SHIFT           15 
#define USB2DC_DOEPCTL4_USBACTEP_BIT             0x1
#define USB2DC_DOEPCTL4_USBACTEP_BITWIDTH        1
// DPID bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL4_DPID_MASK                0x10000
#define USB2DC_DOEPCTL4_DPID_SHIFT               16 
#define USB2DC_DOEPCTL4_DPID_BIT                 0x1
#define USB2DC_DOEPCTL4_DPID_BITWIDTH            1
// NAKSts bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL4_NAKSTS_MASK              0x20000
#define USB2DC_DOEPCTL4_NAKSTS_SHIFT             17 
#define USB2DC_DOEPCTL4_NAKSTS_BIT               0x1
#define USB2DC_DOEPCTL4_NAKSTS_BITWIDTH          1
// EPType bitfiled (RW) Reset=0
#define USB2DC_DOEPCTL4_EPTYPE_MASK              0xC0000
#define USB2DC_DOEPCTL4_EPTYPE_SHIFT             18 
#define USB2DC_DOEPCTL4_EPTYPE_BIT               0x3
#define USB2DC_DOEPCTL4_EPTYPE_BITWIDTH          2
// Snp bitfiled (RW) Reset=0
#define USB2DC_DOEPCTL4_SNP_MASK                 0x100000
#define USB2DC_DOEPCTL4_SNP_SHIFT                20 
#define USB2DC_DOEPCTL4_SNP_BIT                  0x1
#define USB2DC_DOEPCTL4_SNP_BITWIDTH             1
// Stall bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL4_STALL_MASK               0x200000
#define USB2DC_DOEPCTL4_STALL_SHIFT              21 
#define USB2DC_DOEPCTL4_STALL_BIT                0x1
#define USB2DC_DOEPCTL4_STALL_BITWIDTH           1
// reserved bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL4_RESERVED_MASK            0x3C00000
#define USB2DC_DOEPCTL4_RESERVED_SHIFT           22 
#define USB2DC_DOEPCTL4_RESERVED_BIT             0xF
#define USB2DC_DOEPCTL4_RESERVED_BITWIDTH        4
// CNAK bitfiled (WO) Reset=0
#define USB2DC_DOEPCTL4_CNAK_MASK                0x4000000
#define USB2DC_DOEPCTL4_CNAK_SHIFT               26 
#define USB2DC_DOEPCTL4_CNAK_BIT                 0x1
#define USB2DC_DOEPCTL4_CNAK_BITWIDTH            1
// SNAK bitfiled (WO) Reset=0
#define USB2DC_DOEPCTL4_SNAK_MASK                0x8000000
#define USB2DC_DOEPCTL4_SNAK_SHIFT               27 
#define USB2DC_DOEPCTL4_SNAK_BIT                 0x1
#define USB2DC_DOEPCTL4_SNAK_BITWIDTH            1
// SetD0PID bitfiled (WO) Reset=0
#define USB2DC_DOEPCTL4_SETD0PID_MASK            0x10000000
#define USB2DC_DOEPCTL4_SETD0PID_SHIFT           28 
#define USB2DC_DOEPCTL4_SETD0PID_BIT             0x1
#define USB2DC_DOEPCTL4_SETD0PID_BITWIDTH        1
// SetD1PID bitfiled (WO) Reset=0
#define USB2DC_DOEPCTL4_SETD1PID_MASK            0x20000000
#define USB2DC_DOEPCTL4_SETD1PID_SHIFT           29 
#define USB2DC_DOEPCTL4_SETD1PID_BIT             0x1
#define USB2DC_DOEPCTL4_SETD1PID_BITWIDTH        1
// EPDis bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL4_EPDIS_MASK               0x40000000
#define USB2DC_DOEPCTL4_EPDIS_SHIFT              30 
#define USB2DC_DOEPCTL4_EPDIS_BIT                0x1
#define USB2DC_DOEPCTL4_EPDIS_BITWIDTH           1
// EPEna bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL4_EPENA_MASK               0x80000000
#define USB2DC_DOEPCTL4_EPENA_SHIFT              31 
#define USB2DC_DOEPCTL4_EPENA_BIT                0x1
#define USB2DC_DOEPCTL4_EPENA_BITWIDTH           1
// DOEPINT4 Register
#define USB2DC_DOEPINT4_OFS                      0x00000B88
// XferCompl bitfiled (RO) Reset=0
#define USB2DC_DOEPINT4_XFERCOMPL_MASK           0x1
#define USB2DC_DOEPINT4_XFERCOMPL_SHIFT          0 
#define USB2DC_DOEPINT4_XFERCOMPL_BIT            0x1
#define USB2DC_DOEPINT4_XFERCOMPL_BITWIDTH       1
// EPDisbld bitfiled (RO) Reset=0
#define USB2DC_DOEPINT4_EPDISBLD_MASK            0x2
#define USB2DC_DOEPINT4_EPDISBLD_SHIFT           1 
#define USB2DC_DOEPINT4_EPDISBLD_BIT             0x1
#define USB2DC_DOEPINT4_EPDISBLD_BITWIDTH        1
// AHBErr bitfiled (RO) Reset=0
#define USB2DC_DOEPINT4_AHBERR_MASK              0x4
#define USB2DC_DOEPINT4_AHBERR_SHIFT             2 
#define USB2DC_DOEPINT4_AHBERR_BIT               0x1
#define USB2DC_DOEPINT4_AHBERR_BITWIDTH          1
// SetUp bitfiled (RO) Reset=0
#define USB2DC_DOEPINT4_SETUP_MASK               0x8
#define USB2DC_DOEPINT4_SETUP_SHIFT              3 
#define USB2DC_DOEPINT4_SETUP_BIT                0x1
#define USB2DC_DOEPINT4_SETUP_BITWIDTH           1
// OUTTknEPdis bitfiled (RO) Reset=0
#define USB2DC_DOEPINT4_OUTTKNEPDIS_MASK         0x10
#define USB2DC_DOEPINT4_OUTTKNEPDIS_SHIFT        4 
#define USB2DC_DOEPINT4_OUTTKNEPDIS_BIT          0x1
#define USB2DC_DOEPINT4_OUTTKNEPDIS_BITWIDTH     1
// StsPhseRcvd bitfiled (RO) Reset=0
#define USB2DC_DOEPINT4_STSPHSERCVD_MASK         0x20
#define USB2DC_DOEPINT4_STSPHSERCVD_SHIFT        5 
#define USB2DC_DOEPINT4_STSPHSERCVD_BIT          0x1
#define USB2DC_DOEPINT4_STSPHSERCVD_BITWIDTH     1
// Back2BackSETup bitfiled (RO) Reset=0
#define USB2DC_DOEPINT4_BACK2BACKSETUP_MASK      0x40
#define USB2DC_DOEPINT4_BACK2BACKSETUP_SHIFT     6 
#define USB2DC_DOEPINT4_BACK2BACKSETUP_BIT       0x1
#define USB2DC_DOEPINT4_BACK2BACKSETUP_BITWIDTH  1
// reserved3 bitfiled (RO) Reset=0
#define USB2DC_DOEPINT4_RESERVED3_MASK           0x80
#define USB2DC_DOEPINT4_RESERVED3_SHIFT          7 
#define USB2DC_DOEPINT4_RESERVED3_BIT            0x1
#define USB2DC_DOEPINT4_RESERVED3_BITWIDTH       1
// OutPktErr bitfiled (RO) Reset=0
#define USB2DC_DOEPINT4_OUTPKTERR_MASK           0x100
#define USB2DC_DOEPINT4_OUTPKTERR_SHIFT          8 
#define USB2DC_DOEPINT4_OUTPKTERR_BIT            0x1
#define USB2DC_DOEPINT4_OUTPKTERR_BITWIDTH       1
// BNAIntr bitfiled (RO) Reset=0
#define USB2DC_DOEPINT4_BNAINTR_MASK             0x200
#define USB2DC_DOEPINT4_BNAINTR_SHIFT            9 
#define USB2DC_DOEPINT4_BNAINTR_BIT              0x1
#define USB2DC_DOEPINT4_BNAINTR_BITWIDTH         1
// reserved2 bitfiled (RO) Reset=0
#define USB2DC_DOEPINT4_RESERVED2_MASK           0x400
#define USB2DC_DOEPINT4_RESERVED2_SHIFT          10 
#define USB2DC_DOEPINT4_RESERVED2_BIT            0x1
#define USB2DC_DOEPINT4_RESERVED2_BITWIDTH       1
// PktDrpSts bitfiled (RO) Reset=0
#define USB2DC_DOEPINT4_PKTDRPSTS_MASK           0x800
#define USB2DC_DOEPINT4_PKTDRPSTS_SHIFT          11 
#define USB2DC_DOEPINT4_PKTDRPSTS_BIT            0x1
#define USB2DC_DOEPINT4_PKTDRPSTS_BITWIDTH       1
// BbleErr bitfiled (RO) Reset=0
#define USB2DC_DOEPINT4_BBLEERR_MASK             0x1000
#define USB2DC_DOEPINT4_BBLEERR_SHIFT            12 
#define USB2DC_DOEPINT4_BBLEERR_BIT              0x1
#define USB2DC_DOEPINT4_BBLEERR_BITWIDTH         1
// NAKIntrpt bitfiled (RO) Reset=0
#define USB2DC_DOEPINT4_NAKINTRPT_MASK           0x2000
#define USB2DC_DOEPINT4_NAKINTRPT_SHIFT          13 
#define USB2DC_DOEPINT4_NAKINTRPT_BIT            0x1
#define USB2DC_DOEPINT4_NAKINTRPT_BITWIDTH       1
// NYETIntrpt bitfiled (RO) Reset=0
#define USB2DC_DOEPINT4_NYETINTRPT_MASK          0x4000
#define USB2DC_DOEPINT4_NYETINTRPT_SHIFT         14 
#define USB2DC_DOEPINT4_NYETINTRPT_BIT           0x1
#define USB2DC_DOEPINT4_NYETINTRPT_BITWIDTH      1
// reserved bitfiled (RO) Reset=0
#define USB2DC_DOEPINT4_RESERVED_MASK            0xFFFF8000
#define USB2DC_DOEPINT4_RESERVED_SHIFT           15 
#define USB2DC_DOEPINT4_RESERVED_BIT             0x1FFFF
#define USB2DC_DOEPINT4_RESERVED_BITWIDTH        17
// DOEPTSIZ4 Register
#define USB2DC_DOEPTSIZ4_OFS                     0x00000B90
// XferSize bitfiled (RW) Reset=0
#define USB2DC_DOEPTSIZ4_XFERSIZE_MASK           0x7FFFF
#define USB2DC_DOEPTSIZ4_XFERSIZE_SHIFT          0 
#define USB2DC_DOEPTSIZ4_XFERSIZE_BIT            0x7FFFF
#define USB2DC_DOEPTSIZ4_XFERSIZE_BITWIDTH       19
// PktCnt bitfiled (RW) Reset=0
#define USB2DC_DOEPTSIZ4_PKTCNT_MASK             0x1FF80000
#define USB2DC_DOEPTSIZ4_PKTCNT_SHIFT            19 
#define USB2DC_DOEPTSIZ4_PKTCNT_BIT              0x3FF
#define USB2DC_DOEPTSIZ4_PKTCNT_BITWIDTH         10
// RxDPID bitfiled (RO) Reset=0
#define USB2DC_DOEPTSIZ4_RXDPID_MASK             0x60000000
#define USB2DC_DOEPTSIZ4_RXDPID_SHIFT            29 
#define USB2DC_DOEPTSIZ4_RXDPID_BIT              0x3
#define USB2DC_DOEPTSIZ4_RXDPID_BITWIDTH         2
// reserved bitfiled (RO) Reset=0
#define USB2DC_DOEPTSIZ4_RESERVED_MASK           0x80000000
#define USB2DC_DOEPTSIZ4_RESERVED_SHIFT          31 
#define USB2DC_DOEPTSIZ4_RESERVED_BIT            0x1
#define USB2DC_DOEPTSIZ4_RESERVED_BITWIDTH       1
// DOEPDMA4 Register
#define USB2DC_DOEPDMA4_OFS                      0x00000B94
// DMAAddr bitfiled (RW) Reset=0
#define USB2DC_DOEPDMA4_DMAADDR_MASK             0xFFFFFFFF
#define USB2DC_DOEPDMA4_DMAADDR_SHIFT            0 
#define USB2DC_DOEPDMA4_DMAADDR_BIT              0xFFFFFFFF
#define USB2DC_DOEPDMA4_DMAADDR_BITWIDTH         32
// DOEPDMAB4 Register
#define USB2DC_DOEPDMAB4_OFS                     0x00000B9C
// DMABufferAddr bitfiled (RO) Reset=0
#define USB2DC_DOEPDMAB4_DMABUFFERADDR_MASK      0xFFFFFFFF
#define USB2DC_DOEPDMAB4_DMABUFFERADDR_SHIFT     0 
#define USB2DC_DOEPDMAB4_DMABUFFERADDR_BIT       0xFFFFFFFF
#define USB2DC_DOEPDMAB4_DMABUFFERADDR_BITWIDTH  32
// DOEPCTL5 Register
#define USB2DC_DOEPCTL5_OFS                      0x00000BA0
// MPS bitfiled (RW) Reset=0
#define USB2DC_DOEPCTL5_MPS_MASK                 0x7FF
#define USB2DC_DOEPCTL5_MPS_SHIFT                0 
#define USB2DC_DOEPCTL5_MPS_BIT                  0x7FF
#define USB2DC_DOEPCTL5_MPS_BITWIDTH             11
// reserved2 bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL5_RESERVED2_MASK           0x7800
#define USB2DC_DOEPCTL5_RESERVED2_SHIFT          11 
#define USB2DC_DOEPCTL5_RESERVED2_BIT            0xF
#define USB2DC_DOEPCTL5_RESERVED2_BITWIDTH       4
// USBActEP bitfiled (RW) Reset=0
#define USB2DC_DOEPCTL5_USBACTEP_MASK            0x8000
#define USB2DC_DOEPCTL5_USBACTEP_SHIFT           15 
#define USB2DC_DOEPCTL5_USBACTEP_BIT             0x1
#define USB2DC_DOEPCTL5_USBACTEP_BITWIDTH        1
// DPID bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL5_DPID_MASK                0x10000
#define USB2DC_DOEPCTL5_DPID_SHIFT               16 
#define USB2DC_DOEPCTL5_DPID_BIT                 0x1
#define USB2DC_DOEPCTL5_DPID_BITWIDTH            1
// NAKSts bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL5_NAKSTS_MASK              0x20000
#define USB2DC_DOEPCTL5_NAKSTS_SHIFT             17 
#define USB2DC_DOEPCTL5_NAKSTS_BIT               0x1
#define USB2DC_DOEPCTL5_NAKSTS_BITWIDTH          1
// EPType bitfiled (RW) Reset=0
#define USB2DC_DOEPCTL5_EPTYPE_MASK              0xC0000
#define USB2DC_DOEPCTL5_EPTYPE_SHIFT             18 
#define USB2DC_DOEPCTL5_EPTYPE_BIT               0x3
#define USB2DC_DOEPCTL5_EPTYPE_BITWIDTH          2
// Snp bitfiled (RW) Reset=0
#define USB2DC_DOEPCTL5_SNP_MASK                 0x100000
#define USB2DC_DOEPCTL5_SNP_SHIFT                20 
#define USB2DC_DOEPCTL5_SNP_BIT                  0x1
#define USB2DC_DOEPCTL5_SNP_BITWIDTH             1
// Stall bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL5_STALL_MASK               0x200000
#define USB2DC_DOEPCTL5_STALL_SHIFT              21 
#define USB2DC_DOEPCTL5_STALL_BIT                0x1
#define USB2DC_DOEPCTL5_STALL_BITWIDTH           1
// reserved bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL5_RESERVED_MASK            0x3C00000
#define USB2DC_DOEPCTL5_RESERVED_SHIFT           22 
#define USB2DC_DOEPCTL5_RESERVED_BIT             0xF
#define USB2DC_DOEPCTL5_RESERVED_BITWIDTH        4
// CNAK bitfiled (WO) Reset=0
#define USB2DC_DOEPCTL5_CNAK_MASK                0x4000000
#define USB2DC_DOEPCTL5_CNAK_SHIFT               26 
#define USB2DC_DOEPCTL5_CNAK_BIT                 0x1
#define USB2DC_DOEPCTL5_CNAK_BITWIDTH            1
// SNAK bitfiled (WO) Reset=0
#define USB2DC_DOEPCTL5_SNAK_MASK                0x8000000
#define USB2DC_DOEPCTL5_SNAK_SHIFT               27 
#define USB2DC_DOEPCTL5_SNAK_BIT                 0x1
#define USB2DC_DOEPCTL5_SNAK_BITWIDTH            1
// SetD0PID bitfiled (WO) Reset=0
#define USB2DC_DOEPCTL5_SETD0PID_MASK            0x10000000
#define USB2DC_DOEPCTL5_SETD0PID_SHIFT           28 
#define USB2DC_DOEPCTL5_SETD0PID_BIT             0x1
#define USB2DC_DOEPCTL5_SETD0PID_BITWIDTH        1
// SetD1PID bitfiled (WO) Reset=0
#define USB2DC_DOEPCTL5_SETD1PID_MASK            0x20000000
#define USB2DC_DOEPCTL5_SETD1PID_SHIFT           29 
#define USB2DC_DOEPCTL5_SETD1PID_BIT             0x1
#define USB2DC_DOEPCTL5_SETD1PID_BITWIDTH        1
// EPDis bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL5_EPDIS_MASK               0x40000000
#define USB2DC_DOEPCTL5_EPDIS_SHIFT              30 
#define USB2DC_DOEPCTL5_EPDIS_BIT                0x1
#define USB2DC_DOEPCTL5_EPDIS_BITWIDTH           1
// EPEna bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL5_EPENA_MASK               0x80000000
#define USB2DC_DOEPCTL5_EPENA_SHIFT              31 
#define USB2DC_DOEPCTL5_EPENA_BIT                0x1
#define USB2DC_DOEPCTL5_EPENA_BITWIDTH           1
// DOEPINT5 Register
#define USB2DC_DOEPINT5_OFS                      0x00000BA8
// XferCompl bitfiled (RO) Reset=0
#define USB2DC_DOEPINT5_XFERCOMPL_MASK           0x1
#define USB2DC_DOEPINT5_XFERCOMPL_SHIFT          0 
#define USB2DC_DOEPINT5_XFERCOMPL_BIT            0x1
#define USB2DC_DOEPINT5_XFERCOMPL_BITWIDTH       1
// EPDisbld bitfiled (RO) Reset=0
#define USB2DC_DOEPINT5_EPDISBLD_MASK            0x2
#define USB2DC_DOEPINT5_EPDISBLD_SHIFT           1 
#define USB2DC_DOEPINT5_EPDISBLD_BIT             0x1
#define USB2DC_DOEPINT5_EPDISBLD_BITWIDTH        1
// AHBErr bitfiled (RO) Reset=0
#define USB2DC_DOEPINT5_AHBERR_MASK              0x4
#define USB2DC_DOEPINT5_AHBERR_SHIFT             2 
#define USB2DC_DOEPINT5_AHBERR_BIT               0x1
#define USB2DC_DOEPINT5_AHBERR_BITWIDTH          1
// SetUp bitfiled (RO) Reset=0
#define USB2DC_DOEPINT5_SETUP_MASK               0x8
#define USB2DC_DOEPINT5_SETUP_SHIFT              3 
#define USB2DC_DOEPINT5_SETUP_BIT                0x1
#define USB2DC_DOEPINT5_SETUP_BITWIDTH           1
// OUTTknEPdis bitfiled (RO) Reset=0
#define USB2DC_DOEPINT5_OUTTKNEPDIS_MASK         0x10
#define USB2DC_DOEPINT5_OUTTKNEPDIS_SHIFT        4 
#define USB2DC_DOEPINT5_OUTTKNEPDIS_BIT          0x1
#define USB2DC_DOEPINT5_OUTTKNEPDIS_BITWIDTH     1
// StsPhseRcvd bitfiled (RO) Reset=0
#define USB2DC_DOEPINT5_STSPHSERCVD_MASK         0x20
#define USB2DC_DOEPINT5_STSPHSERCVD_SHIFT        5 
#define USB2DC_DOEPINT5_STSPHSERCVD_BIT          0x1
#define USB2DC_DOEPINT5_STSPHSERCVD_BITWIDTH     1
// Back2BackSETup bitfiled (RO) Reset=0
#define USB2DC_DOEPINT5_BACK2BACKSETUP_MASK      0x40
#define USB2DC_DOEPINT5_BACK2BACKSETUP_SHIFT     6 
#define USB2DC_DOEPINT5_BACK2BACKSETUP_BIT       0x1
#define USB2DC_DOEPINT5_BACK2BACKSETUP_BITWIDTH  1
// reserved3 bitfiled (RO) Reset=0
#define USB2DC_DOEPINT5_RESERVED3_MASK           0x80
#define USB2DC_DOEPINT5_RESERVED3_SHIFT          7 
#define USB2DC_DOEPINT5_RESERVED3_BIT            0x1
#define USB2DC_DOEPINT5_RESERVED3_BITWIDTH       1
// OutPktErr bitfiled (RO) Reset=0
#define USB2DC_DOEPINT5_OUTPKTERR_MASK           0x100
#define USB2DC_DOEPINT5_OUTPKTERR_SHIFT          8 
#define USB2DC_DOEPINT5_OUTPKTERR_BIT            0x1
#define USB2DC_DOEPINT5_OUTPKTERR_BITWIDTH       1
// BNAIntr bitfiled (RO) Reset=0
#define USB2DC_DOEPINT5_BNAINTR_MASK             0x200
#define USB2DC_DOEPINT5_BNAINTR_SHIFT            9 
#define USB2DC_DOEPINT5_BNAINTR_BIT              0x1
#define USB2DC_DOEPINT5_BNAINTR_BITWIDTH         1
// reserved2 bitfiled (RO) Reset=0
#define USB2DC_DOEPINT5_RESERVED2_MASK           0x400
#define USB2DC_DOEPINT5_RESERVED2_SHIFT          10 
#define USB2DC_DOEPINT5_RESERVED2_BIT            0x1
#define USB2DC_DOEPINT5_RESERVED2_BITWIDTH       1
// PktDrpSts bitfiled (RO) Reset=0
#define USB2DC_DOEPINT5_PKTDRPSTS_MASK           0x800
#define USB2DC_DOEPINT5_PKTDRPSTS_SHIFT          11 
#define USB2DC_DOEPINT5_PKTDRPSTS_BIT            0x1
#define USB2DC_DOEPINT5_PKTDRPSTS_BITWIDTH       1
// BbleErr bitfiled (RO) Reset=0
#define USB2DC_DOEPINT5_BBLEERR_MASK             0x1000
#define USB2DC_DOEPINT5_BBLEERR_SHIFT            12 
#define USB2DC_DOEPINT5_BBLEERR_BIT              0x1
#define USB2DC_DOEPINT5_BBLEERR_BITWIDTH         1
// NAKIntrpt bitfiled (RO) Reset=0
#define USB2DC_DOEPINT5_NAKINTRPT_MASK           0x2000
#define USB2DC_DOEPINT5_NAKINTRPT_SHIFT          13 
#define USB2DC_DOEPINT5_NAKINTRPT_BIT            0x1
#define USB2DC_DOEPINT5_NAKINTRPT_BITWIDTH       1
// NYETIntrpt bitfiled (RO) Reset=0
#define USB2DC_DOEPINT5_NYETINTRPT_MASK          0x4000
#define USB2DC_DOEPINT5_NYETINTRPT_SHIFT         14 
#define USB2DC_DOEPINT5_NYETINTRPT_BIT           0x1
#define USB2DC_DOEPINT5_NYETINTRPT_BITWIDTH      1
// reserved bitfiled (RO) Reset=0
#define USB2DC_DOEPINT5_RESERVED_MASK            0xFFFF8000
#define USB2DC_DOEPINT5_RESERVED_SHIFT           15 
#define USB2DC_DOEPINT5_RESERVED_BIT             0x1FFFF
#define USB2DC_DOEPINT5_RESERVED_BITWIDTH        17
// DOEPTSIZ5 Register
#define USB2DC_DOEPTSIZ5_OFS                     0x00000BB0
// XferSize bitfiled (RW) Reset=0
#define USB2DC_DOEPTSIZ5_XFERSIZE_MASK           0x7FFFF
#define USB2DC_DOEPTSIZ5_XFERSIZE_SHIFT          0 
#define USB2DC_DOEPTSIZ5_XFERSIZE_BIT            0x7FFFF
#define USB2DC_DOEPTSIZ5_XFERSIZE_BITWIDTH       19
// PktCnt bitfiled (RW) Reset=0
#define USB2DC_DOEPTSIZ5_PKTCNT_MASK             0x1FF80000
#define USB2DC_DOEPTSIZ5_PKTCNT_SHIFT            19 
#define USB2DC_DOEPTSIZ5_PKTCNT_BIT              0x3FF
#define USB2DC_DOEPTSIZ5_PKTCNT_BITWIDTH         10
// RxDPID bitfiled (RO) Reset=0
#define USB2DC_DOEPTSIZ5_RXDPID_MASK             0x60000000
#define USB2DC_DOEPTSIZ5_RXDPID_SHIFT            29 
#define USB2DC_DOEPTSIZ5_RXDPID_BIT              0x3
#define USB2DC_DOEPTSIZ5_RXDPID_BITWIDTH         2
// reserved bitfiled (RO) Reset=0
#define USB2DC_DOEPTSIZ5_RESERVED_MASK           0x80000000
#define USB2DC_DOEPTSIZ5_RESERVED_SHIFT          31 
#define USB2DC_DOEPTSIZ5_RESERVED_BIT            0x1
#define USB2DC_DOEPTSIZ5_RESERVED_BITWIDTH       1
// DOEPDMA5 Register
#define USB2DC_DOEPDMA5_OFS                      0x00000BB4
// DMAAddr bitfiled (RW) Reset=0
#define USB2DC_DOEPDMA5_DMAADDR_MASK             0xFFFFFFFF
#define USB2DC_DOEPDMA5_DMAADDR_SHIFT            0 
#define USB2DC_DOEPDMA5_DMAADDR_BIT              0xFFFFFFFF
#define USB2DC_DOEPDMA5_DMAADDR_BITWIDTH         32
// DOEPDMAB5 Register
#define USB2DC_DOEPDMAB5_OFS                     0x00000BBC
// DMABufferAddr bitfiled (RO) Reset=0
#define USB2DC_DOEPDMAB5_DMABUFFERADDR_MASK      0xFFFFFFFF
#define USB2DC_DOEPDMAB5_DMABUFFERADDR_SHIFT     0 
#define USB2DC_DOEPDMAB5_DMABUFFERADDR_BIT       0xFFFFFFFF
#define USB2DC_DOEPDMAB5_DMABUFFERADDR_BITWIDTH  32
// DOEPCTL6 Register
#define USB2DC_DOEPCTL6_OFS                      0x00000BC0
// MPS bitfiled (RW) Reset=0
#define USB2DC_DOEPCTL6_MPS_MASK                 0x7FF
#define USB2DC_DOEPCTL6_MPS_SHIFT                0 
#define USB2DC_DOEPCTL6_MPS_BIT                  0x7FF
#define USB2DC_DOEPCTL6_MPS_BITWIDTH             11
// reserved2 bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL6_RESERVED2_MASK           0x7800
#define USB2DC_DOEPCTL6_RESERVED2_SHIFT          11 
#define USB2DC_DOEPCTL6_RESERVED2_BIT            0xF
#define USB2DC_DOEPCTL6_RESERVED2_BITWIDTH       4
// USBActEP bitfiled (RW) Reset=0
#define USB2DC_DOEPCTL6_USBACTEP_MASK            0x8000
#define USB2DC_DOEPCTL6_USBACTEP_SHIFT           15 
#define USB2DC_DOEPCTL6_USBACTEP_BIT             0x1
#define USB2DC_DOEPCTL6_USBACTEP_BITWIDTH        1
// DPID bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL6_DPID_MASK                0x10000
#define USB2DC_DOEPCTL6_DPID_SHIFT               16 
#define USB2DC_DOEPCTL6_DPID_BIT                 0x1
#define USB2DC_DOEPCTL6_DPID_BITWIDTH            1
// NAKSts bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL6_NAKSTS_MASK              0x20000
#define USB2DC_DOEPCTL6_NAKSTS_SHIFT             17 
#define USB2DC_DOEPCTL6_NAKSTS_BIT               0x1
#define USB2DC_DOEPCTL6_NAKSTS_BITWIDTH          1
// EPType bitfiled (RW) Reset=0
#define USB2DC_DOEPCTL6_EPTYPE_MASK              0xC0000
#define USB2DC_DOEPCTL6_EPTYPE_SHIFT             18 
#define USB2DC_DOEPCTL6_EPTYPE_BIT               0x3
#define USB2DC_DOEPCTL6_EPTYPE_BITWIDTH          2
// Snp bitfiled (RW) Reset=0
#define USB2DC_DOEPCTL6_SNP_MASK                 0x100000
#define USB2DC_DOEPCTL6_SNP_SHIFT                20 
#define USB2DC_DOEPCTL6_SNP_BIT                  0x1
#define USB2DC_DOEPCTL6_SNP_BITWIDTH             1
// Stall bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL6_STALL_MASK               0x200000
#define USB2DC_DOEPCTL6_STALL_SHIFT              21 
#define USB2DC_DOEPCTL6_STALL_BIT                0x1
#define USB2DC_DOEPCTL6_STALL_BITWIDTH           1
// reserved bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL6_RESERVED_MASK            0x3C00000
#define USB2DC_DOEPCTL6_RESERVED_SHIFT           22 
#define USB2DC_DOEPCTL6_RESERVED_BIT             0xF
#define USB2DC_DOEPCTL6_RESERVED_BITWIDTH        4
// CNAK bitfiled (WO) Reset=0
#define USB2DC_DOEPCTL6_CNAK_MASK                0x4000000
#define USB2DC_DOEPCTL6_CNAK_SHIFT               26 
#define USB2DC_DOEPCTL6_CNAK_BIT                 0x1
#define USB2DC_DOEPCTL6_CNAK_BITWIDTH            1
// SNAK bitfiled (WO) Reset=0
#define USB2DC_DOEPCTL6_SNAK_MASK                0x8000000
#define USB2DC_DOEPCTL6_SNAK_SHIFT               27 
#define USB2DC_DOEPCTL6_SNAK_BIT                 0x1
#define USB2DC_DOEPCTL6_SNAK_BITWIDTH            1
// SetD0PID bitfiled (WO) Reset=0
#define USB2DC_DOEPCTL6_SETD0PID_MASK            0x10000000
#define USB2DC_DOEPCTL6_SETD0PID_SHIFT           28 
#define USB2DC_DOEPCTL6_SETD0PID_BIT             0x1
#define USB2DC_DOEPCTL6_SETD0PID_BITWIDTH        1
// SetD1PID bitfiled (WO) Reset=0
#define USB2DC_DOEPCTL6_SETD1PID_MASK            0x20000000
#define USB2DC_DOEPCTL6_SETD1PID_SHIFT           29 
#define USB2DC_DOEPCTL6_SETD1PID_BIT             0x1
#define USB2DC_DOEPCTL6_SETD1PID_BITWIDTH        1
// EPDis bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL6_EPDIS_MASK               0x40000000
#define USB2DC_DOEPCTL6_EPDIS_SHIFT              30 
#define USB2DC_DOEPCTL6_EPDIS_BIT                0x1
#define USB2DC_DOEPCTL6_EPDIS_BITWIDTH           1
// EPEna bitfiled (RO) Reset=0
#define USB2DC_DOEPCTL6_EPENA_MASK               0x80000000
#define USB2DC_DOEPCTL6_EPENA_SHIFT              31 
#define USB2DC_DOEPCTL6_EPENA_BIT                0x1
#define USB2DC_DOEPCTL6_EPENA_BITWIDTH           1
// DOEPINT6 Register
#define USB2DC_DOEPINT6_OFS                      0x00000BC8
// XferCompl bitfiled (RO) Reset=0
#define USB2DC_DOEPINT6_XFERCOMPL_MASK           0x1
#define USB2DC_DOEPINT6_XFERCOMPL_SHIFT          0 
#define USB2DC_DOEPINT6_XFERCOMPL_BIT            0x1
#define USB2DC_DOEPINT6_XFERCOMPL_BITWIDTH       1
// EPDisbld bitfiled (RO) Reset=0
#define USB2DC_DOEPINT6_EPDISBLD_MASK            0x2
#define USB2DC_DOEPINT6_EPDISBLD_SHIFT           1 
#define USB2DC_DOEPINT6_EPDISBLD_BIT             0x1
#define USB2DC_DOEPINT6_EPDISBLD_BITWIDTH        1
// AHBErr bitfiled (RO) Reset=0
#define USB2DC_DOEPINT6_AHBERR_MASK              0x4
#define USB2DC_DOEPINT6_AHBERR_SHIFT             2 
#define USB2DC_DOEPINT6_AHBERR_BIT               0x1
#define USB2DC_DOEPINT6_AHBERR_BITWIDTH          1
// SetUp bitfiled (RO) Reset=0
#define USB2DC_DOEPINT6_SETUP_MASK               0x8
#define USB2DC_DOEPINT6_SETUP_SHIFT              3 
#define USB2DC_DOEPINT6_SETUP_BIT                0x1
#define USB2DC_DOEPINT6_SETUP_BITWIDTH           1
// OUTTknEPdis bitfiled (RO) Reset=0
#define USB2DC_DOEPINT6_OUTTKNEPDIS_MASK         0x10
#define USB2DC_DOEPINT6_OUTTKNEPDIS_SHIFT        4 
#define USB2DC_DOEPINT6_OUTTKNEPDIS_BIT          0x1
#define USB2DC_DOEPINT6_OUTTKNEPDIS_BITWIDTH     1
// StsPhseRcvd bitfiled (RO) Reset=0
#define USB2DC_DOEPINT6_STSPHSERCVD_MASK         0x20
#define USB2DC_DOEPINT6_STSPHSERCVD_SHIFT        5 
#define USB2DC_DOEPINT6_STSPHSERCVD_BIT          0x1
#define USB2DC_DOEPINT6_STSPHSERCVD_BITWIDTH     1
// Back2BackSETup bitfiled (RO) Reset=0
#define USB2DC_DOEPINT6_BACK2BACKSETUP_MASK      0x40
#define USB2DC_DOEPINT6_BACK2BACKSETUP_SHIFT     6 
#define USB2DC_DOEPINT6_BACK2BACKSETUP_BIT       0x1
#define USB2DC_DOEPINT6_BACK2BACKSETUP_BITWIDTH  1
// reserved3 bitfiled (RO) Reset=0
#define USB2DC_DOEPINT6_RESERVED3_MASK           0x80
#define USB2DC_DOEPINT6_RESERVED3_SHIFT          7 
#define USB2DC_DOEPINT6_RESERVED3_BIT            0x1
#define USB2DC_DOEPINT6_RESERVED3_BITWIDTH       1
// OutPktErr bitfiled (RO) Reset=0
#define USB2DC_DOEPINT6_OUTPKTERR_MASK           0x100
#define USB2DC_DOEPINT6_OUTPKTERR_SHIFT          8 
#define USB2DC_DOEPINT6_OUTPKTERR_BIT            0x1
#define USB2DC_DOEPINT6_OUTPKTERR_BITWIDTH       1
// BNAIntr bitfiled (RO) Reset=0
#define USB2DC_DOEPINT6_BNAINTR_MASK             0x200
#define USB2DC_DOEPINT6_BNAINTR_SHIFT            9 
#define USB2DC_DOEPINT6_BNAINTR_BIT              0x1
#define USB2DC_DOEPINT6_BNAINTR_BITWIDTH         1
// reserved2 bitfiled (RO) Reset=0
#define USB2DC_DOEPINT6_RESERVED2_MASK           0x400
#define USB2DC_DOEPINT6_RESERVED2_SHIFT          10 
#define USB2DC_DOEPINT6_RESERVED2_BIT            0x1
#define USB2DC_DOEPINT6_RESERVED2_BITWIDTH       1
// PktDrpSts bitfiled (RO) Reset=0
#define USB2DC_DOEPINT6_PKTDRPSTS_MASK           0x800
#define USB2DC_DOEPINT6_PKTDRPSTS_SHIFT          11 
#define USB2DC_DOEPINT6_PKTDRPSTS_BIT            0x1
#define USB2DC_DOEPINT6_PKTDRPSTS_BITWIDTH       1
// BbleErr bitfiled (RO) Reset=0
#define USB2DC_DOEPINT6_BBLEERR_MASK             0x1000
#define USB2DC_DOEPINT6_BBLEERR_SHIFT            12 
#define USB2DC_DOEPINT6_BBLEERR_BIT              0x1
#define USB2DC_DOEPINT6_BBLEERR_BITWIDTH         1
// NAKIntrpt bitfiled (RO) Reset=0
#define USB2DC_DOEPINT6_NAKINTRPT_MASK           0x2000
#define USB2DC_DOEPINT6_NAKINTRPT_SHIFT          13 
#define USB2DC_DOEPINT6_NAKINTRPT_BIT            0x1
#define USB2DC_DOEPINT6_NAKINTRPT_BITWIDTH       1
// NYETIntrpt bitfiled (RO) Reset=0
#define USB2DC_DOEPINT6_NYETINTRPT_MASK          0x4000
#define USB2DC_DOEPINT6_NYETINTRPT_SHIFT         14 
#define USB2DC_DOEPINT6_NYETINTRPT_BIT           0x1
#define USB2DC_DOEPINT6_NYETINTRPT_BITWIDTH      1
// reserved bitfiled (RO) Reset=0
#define USB2DC_DOEPINT6_RESERVED_MASK            0xFFFF8000
#define USB2DC_DOEPINT6_RESERVED_SHIFT           15 
#define USB2DC_DOEPINT6_RESERVED_BIT             0x1FFFF
#define USB2DC_DOEPINT6_RESERVED_BITWIDTH        17
// DOEPTSIZ6 Register
#define USB2DC_DOEPTSIZ6_OFS                     0x00000BD0
// XferSize bitfiled (RW) Reset=0
#define USB2DC_DOEPTSIZ6_XFERSIZE_MASK           0x7FFFF
#define USB2DC_DOEPTSIZ6_XFERSIZE_SHIFT          0 
#define USB2DC_DOEPTSIZ6_XFERSIZE_BIT            0x7FFFF
#define USB2DC_DOEPTSIZ6_XFERSIZE_BITWIDTH       19
// PktCnt bitfiled (RW) Reset=0
#define USB2DC_DOEPTSIZ6_PKTCNT_MASK             0x1FF80000
#define USB2DC_DOEPTSIZ6_PKTCNT_SHIFT            19 
#define USB2DC_DOEPTSIZ6_PKTCNT_BIT              0x3FF
#define USB2DC_DOEPTSIZ6_PKTCNT_BITWIDTH         10
// RxDPID bitfiled (RO) Reset=0
#define USB2DC_DOEPTSIZ6_RXDPID_MASK             0x60000000
#define USB2DC_DOEPTSIZ6_RXDPID_SHIFT            29 
#define USB2DC_DOEPTSIZ6_RXDPID_BIT              0x3
#define USB2DC_DOEPTSIZ6_RXDPID_BITWIDTH         2
// reserved bitfiled (RO) Reset=0
#define USB2DC_DOEPTSIZ6_RESERVED_MASK           0x80000000
#define USB2DC_DOEPTSIZ6_RESERVED_SHIFT          31 
#define USB2DC_DOEPTSIZ6_RESERVED_BIT            0x1
#define USB2DC_DOEPTSIZ6_RESERVED_BITWIDTH       1
// DOEPDMA6 Register
#define USB2DC_DOEPDMA6_OFS                      0x00000BD4
// DMAAddr bitfiled (RW) Reset=0
#define USB2DC_DOEPDMA6_DMAADDR_MASK             0xFFFFFFFF
#define USB2DC_DOEPDMA6_DMAADDR_SHIFT            0 
#define USB2DC_DOEPDMA6_DMAADDR_BIT              0xFFFFFFFF
#define USB2DC_DOEPDMA6_DMAADDR_BITWIDTH         32
// DOEPDMAB6 Register
#define USB2DC_DOEPDMAB6_OFS                     0x00000BDC
// DMABufferAddr bitfiled (RO) Reset=0
#define USB2DC_DOEPDMAB6_DMABUFFERADDR_MASK      0xFFFFFFFF
#define USB2DC_DOEPDMAB6_DMABUFFERADDR_SHIFT     0 
#define USB2DC_DOEPDMAB6_DMABUFFERADDR_BIT       0xFFFFFFFF
#define USB2DC_DOEPDMAB6_DMABUFFERADDR_BITWIDTH  32
// PCGCCTL Register
#define USB2DC_PCGCCTL_OFS                       0x00000E00
// StopPclk bitfiled (RW) Reset=0
#define USB2DC_PCGCCTL_STOPPCLK_MASK             0x1
#define USB2DC_PCGCCTL_STOPPCLK_SHIFT            0 
#define USB2DC_PCGCCTL_STOPPCLK_BIT              0x1
#define USB2DC_PCGCCTL_STOPPCLK_BITWIDTH         1
// GateHclk bitfiled (RW) Reset=0
#define USB2DC_PCGCCTL_GATEHCLK_MASK             0x2
#define USB2DC_PCGCCTL_GATEHCLK_SHIFT            1 
#define USB2DC_PCGCCTL_GATEHCLK_BIT              0x1
#define USB2DC_PCGCCTL_GATEHCLK_BITWIDTH         1
// PwrClmp bitfiled (RW) Reset=0
#define USB2DC_PCGCCTL_PWRCLMP_MASK              0x4
#define USB2DC_PCGCCTL_PWRCLMP_SHIFT             2 
#define USB2DC_PCGCCTL_PWRCLMP_BIT               0x1
#define USB2DC_PCGCCTL_PWRCLMP_BITWIDTH          1
// RstPdwnModule bitfiled (RW) Reset=0
#define USB2DC_PCGCCTL_RSTPDWNMODULE_MASK        0x8
#define USB2DC_PCGCCTL_RSTPDWNMODULE_SHIFT       3 
#define USB2DC_PCGCCTL_RSTPDWNMODULE_BIT         0x1
#define USB2DC_PCGCCTL_RSTPDWNMODULE_BITWIDTH    1
// Reserved2 bitfiled (RO) Reset=0
#define USB2DC_PCGCCTL_RESERVED2_MASK            0x30
#define USB2DC_PCGCCTL_RESERVED2_SHIFT           4 
#define USB2DC_PCGCCTL_RESERVED2_BIT             0x3
#define USB2DC_PCGCCTL_RESERVED2_BITWIDTH        2
// PhySleep bitfiled (RO) Reset=0
#define USB2DC_PCGCCTL_PHYSLEEP_MASK             0x40
#define USB2DC_PCGCCTL_PHYSLEEP_SHIFT            6 
#define USB2DC_PCGCCTL_PHYSLEEP_BIT              0x1
#define USB2DC_PCGCCTL_PHYSLEEP_BITWIDTH         1
// L1Suspended bitfiled (RO) Reset=0
#define USB2DC_PCGCCTL_L1SUSPENDED_MASK          0x80
#define USB2DC_PCGCCTL_L1SUSPENDED_SHIFT         7 
#define USB2DC_PCGCCTL_L1SUSPENDED_BIT           0x1
#define USB2DC_PCGCCTL_L1SUSPENDED_BITWIDTH      1
// Reserved bitfiled (RO) Reset=0
#define USB2DC_PCGCCTL_RESERVED_MASK             0xFFFFFF00
#define USB2DC_PCGCCTL_RESERVED_SHIFT            8 
#define USB2DC_PCGCCTL_RESERVED_BIT              0xFFFFFF
#define USB2DC_PCGCCTL_RESERVED_BITWIDTH         24

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _USB2DC_REG_DEF_H */
