/*
 * arch/arm/mach-tz3000/include/mach/regs/usb2dc_offs_def.h
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

#ifndef USB2DC_OFFS_DEF_H
#define USB2DC_OFFS_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

#define USB2DC_GOTGCTL_OFFS            0x00000000
#define USB2DC_GOTGINT_OFFS            0x00000004
#define USB2DC_GAHBCFG_OFFS            0x00000008
#define USB2DC_GUSBCFG_OFFS            0x0000000C
#define USB2DC_GRSTCTL_OFFS            0x00000010
#define USB2DC_GINTSTS_OFFS            0x00000014
#define USB2DC_GINTMSK_OFFS            0x00000018
#define USB2DC_GRXSTSR_OFFS            0x0000001C
#define USB2DC_GRXSTSP_OFFS            0x00000020
#define USB2DC_GRXFSIZ_OFFS            0x00000024
#define USB2DC_GNPTXFSIZ_OFFS          0x00000028
#define USB2DC_GSNPSID_OFFS            0x00000040
#define USB2DC_GHWCFG1_OFFS            0x00000044
#define USB2DC_GHWCFG2_OFFS            0x00000048
#define USB2DC_GHWCFG3_OFFS            0x0000004C
#define USB2DC_GHWCFG4_OFFS            0x00000050
#define USB2DC_GDFIFOCFG_OFFS          0x0000005C
#define USB2DC_DIEPTXF1_OFFS           0x00000104
#define USB2DC_DIEPTXF2_OFFS           0x00000108
#define USB2DC_DIEPTXF3_OFFS           0x0000010C
#define USB2DC_DIEPTXF4_OFFS           0x00000110
#define USB2DC_DIEPTXF5_OFFS           0x00000114
#define USB2DC_DIEPTXF6_OFFS           0x00000118
#define USB2DC_DCFG_OFFS               0x00000800
#define USB2DC_DCTL_OFFS               0x00000804
#define USB2DC_DSTS_OFFS               0x00000808
#define USB2DC_DIEPMSK_OFFS            0x00000810
#define USB2DC_DOEPMSK_OFFS            0x00000814
#define USB2DC_DAINT_OFFS              0x00000818
#define USB2DC_DAINTMSK_OFFS           0x0000081C
#define USB2DC_DVBUSDIS_OFFS           0x00000828
#define USB2DC_DVBUSPULSE_OFFS         0x0000082C
#define USB2DC_DTHRCTL_OFFS            0x00000830
#define USB2DC_DIEPEMPMSK_OFFS         0x00000834
#define USB2DC_DEACHINT_OFFS           0x00000838
#define USB2DC_DEACHINTMSK_OFFS        0x0000083C
#define USB2DC_DIEPEACHMSK0_OFFS       0x00000840
#define USB2DC_DIEPEACHMSK1_OFFS       0x00000844
#define USB2DC_DIEPEACHMSK2_OFFS       0x00000848
#define USB2DC_DIEPEACHMSK3_OFFS       0x0000084C
#define USB2DC_DIEPEACHMSK4_OFFS       0x00000850
#define USB2DC_DIEPEACHMSK5_OFFS       0x00000854
#define USB2DC_DIEPEACHMSK6_OFFS       0x00000858
#define USB2DC_DOEPEACHMSK0_OFFS       0x00000880
#define USB2DC_DOEPEACHMSK1_OFFS       0x00000884
#define USB2DC_DOEPEACHMSK2_OFFS       0x00000888
#define USB2DC_DOEPEACHMSK3_OFFS       0x0000088C
#define USB2DC_DOEPEACHMSK4_OFFS       0x00000890
#define USB2DC_DOEPEACHMSK5_OFFS       0x00000894
#define USB2DC_DOEPEACHMSK6_OFFS       0x00000898
#define USB2DC_DIEPCTL0_OFFS           0x00000900
#define USB2DC_DIEPINT0_OFFS           0x00000908
#define USB2DC_DIEPTSIZ0_OFFS          0x00000910
#define USB2DC_DIEPDMA0_OFFS           0x00000914
#define USB2DC_DTXFSTS0_OFFS           0x00000918
#define USB2DC_DIEPDMAB0_OFFS          0x0000091C
#define USB2DC_DIEPCTL1_OFFS           0x00000920
#define USB2DC_DIEPINT1_OFFS           0x00000928
#define USB2DC_DIEPTSIZ1_OFFS          0x00000930
#define USB2DC_DIEPDMA1_OFFS           0x00000934
#define USB2DC_DTXFSTS1_OFFS           0x00000938
#define USB2DC_DIEPDMAB1_OFFS          0x0000093C
#define USB2DC_DIEPCTL2_OFFS           0x00000940
#define USB2DC_DIEPINT2_OFFS           0x00000948
#define USB2DC_DIEPTSIZ2_OFFS          0x00000950
#define USB2DC_DIEPDMA2_OFFS           0x00000954
#define USB2DC_DTXFSTS2_OFFS           0x00000958
#define USB2DC_DIEPDMAB2_OFFS          0x0000095C
#define USB2DC_DIEPCTL3_OFFS           0x00000960
#define USB2DC_DIEPINT3_OFFS           0x00000968
#define USB2DC_DIEPTSIZ3_OFFS          0x00000970
#define USB2DC_DIEPDMA3_OFFS           0x00000974
#define USB2DC_DTXFSTS3_OFFS           0x00000978
#define USB2DC_DIEPDMAB3_OFFS          0x0000097C
#define USB2DC_DIEPCTL4_OFFS           0x00000980
#define USB2DC_DIEPINT4_OFFS           0x00000988
#define USB2DC_DIEPTSIZ4_OFFS          0x00000990
#define USB2DC_DIEPDMA4_OFFS           0x00000994
#define USB2DC_DTXFSTS4_OFFS           0x00000998
#define USB2DC_DIEPDMAB4_OFFS          0x0000099C
#define USB2DC_DIEPCTL5_OFFS           0x000009A0
#define USB2DC_DIEPINT5_OFFS           0x000009A8
#define USB2DC_DIEPTSIZ5_OFFS          0x000009B0
#define USB2DC_DIEPDMA5_OFFS           0x000009B4
#define USB2DC_DTXFSTS5_OFFS           0x000009B8
#define USB2DC_DIEPDMAB5_OFFS          0x000009BC
#define USB2DC_DIEPCTL6_OFFS           0x000009C0
#define USB2DC_DIEPINT6_OFFS           0x000009C8
#define USB2DC_DIEPTSIZ6_OFFS          0x000009D0
#define USB2DC_DIEPDMA6_OFFS           0x000009D4
#define USB2DC_DTXFSTS6_OFFS           0x000009D8
#define USB2DC_DIEPDMAB6_OFFS          0x000009DC
#define USB2DC_DOEPCTL0_OFFS           0x00000B00
#define USB2DC_DOEPINT0_OFFS           0x00000B08
#define USB2DC_DOEPTSIZ0_OFFS          0x00000B10
#define USB2DC_DOEPDMA0_OFFS           0x00000B14
#define USB2DC_DOEPDMAB0_OFFS          0x00000B1C
#define USB2DC_DOEPCTL1_OFFS           0x00000B20
#define USB2DC_DOEPINT1_OFFS           0x00000B28
#define USB2DC_DOEPTSIZ1_OFFS          0x00000B30
#define USB2DC_DOEPDMA1_OFFS           0x00000B34
#define USB2DC_DOEPDMAB1_OFFS          0x00000B3C
#define USB2DC_DOEPCTL2_OFFS           0x00000B40
#define USB2DC_DOEPINT2_OFFS           0x00000B48
#define USB2DC_DOEPTSIZ2_OFFS          0x00000B50
#define USB2DC_DOEPDMA2_OFFS           0x00000B54
#define USB2DC_DOEPDMAB2_OFFS          0x00000B5C
#define USB2DC_DOEPCTL3_OFFS           0x00000B60
#define USB2DC_DOEPINT3_OFFS           0x00000B68
#define USB2DC_DOEPTSIZ3_OFFS          0x00000B70
#define USB2DC_DOEPDMA3_OFFS           0x00000B74
#define USB2DC_DOEPDMAB3_OFFS          0x00000B7C
#define USB2DC_DOEPCTL4_OFFS           0x00000B80
#define USB2DC_DOEPINT4_OFFS           0x00000B88
#define USB2DC_DOEPTSIZ4_OFFS          0x00000B90
#define USB2DC_DOEPDMA4_OFFS           0x00000B94
#define USB2DC_DOEPDMAB4_OFFS          0x00000B9C
#define USB2DC_DOEPCTL5_OFFS           0x00000BA0
#define USB2DC_DOEPINT5_OFFS           0x00000BA8
#define USB2DC_DOEPTSIZ5_OFFS          0x00000BB0
#define USB2DC_DOEPDMA5_OFFS           0x00000BB4
#define USB2DC_DOEPDMAB5_OFFS          0x00000BBC
#define USB2DC_DOEPCTL6_OFFS           0x00000BC0
#define USB2DC_DOEPINT6_OFFS           0x00000BC8
#define USB2DC_DOEPTSIZ6_OFFS          0x00000BD0
#define USB2DC_DOEPDMA6_OFFS           0x00000BD4
#define USB2DC_DOEPDMAB6_OFFS          0x00000BDC
#define USB2DC_PCGCCTL_OFFS            0x00000E00

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* USB2DC_OFFS_DEF_H */
