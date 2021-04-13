/*
 * arch/arm/mach-tz3000/include/mach/regs/usb3hc_offs_def.h
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

#ifndef USB3HC_OFFS_DEF_H
#define USB3HC_OFFS_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

#define USB3HC_CAPLENGTH_OFFS          0x00000000
#define USB3HC_HCSPARAMS1_OFFS         0x00000004
#define USB3HC_HCSPARAMS2_OFFS         0x00000008
#define USB3HC_HCSPARAMS3_OFFS         0x0000000C
#define USB3HC_HCCPARAMS_OFFS          0x00000010
#define USB3HC_DBOFF_OFFS              0x00000014
#define USB3HC_RTSOFF_OFFS             0x00000018
#define USB3HC_USBCMD_OFFS             0x00000020
#define USB3HC_USBSTS_OFFS             0x00000024
#define USB3HC_PAGESIZE_OFFS           0x00000028
#define USB3HC_DNCTRL_OFFS             0x00000034
#define USB3HC_CRCR_LO_OFFS            0x00000038
#define USB3HC_CRCR_HI_OFFS            0x0000003C
#define USB3HC_DCBAAP_LO_OFFS          0x00000050
#define USB3HC_DCBAAP_HI_OFFS          0x00000054
#define USB3HC_CONFIG_OFFS             0x00000058
#define USB3HC_PORTSC_0_OFFS           0x00000420
#define USB3HC_PORTPMSC_20_0_OFFS      0x00000424
#define USB3HC_PORTLI_0_OFFS           0x00000428
#define USB3HC_PORTSC_1_OFFS           0x00000430
#define USB3HC_PORTPMSC_SS_0_OFFS      0x00000434
#define USB3HC_PORTLI_1_OFFS           0x00000438
#define USB3HC_MFINDEX_OFFS            0x00000440
#define USB3HC_IMAN_0_OFFS             0x00000460
#define USB3HC_IMOD_0_OFFS             0x00000464
#define USB3HC_ERSTSZ_0_OFFS           0x00000468
#define USB3HC_ERSTBA_LO_0_OFFS        0x00000470
#define USB3HC_ERSTBA_HI_0_OFFS        0x00000474
#define USB3HC_ERDP_LO_0_OFFS          0x00000478
#define USB3HC_ERDP_HI_0_OFFS          0x0000047C
#define USB3HC_DB_0_OFFS               0x00000480
#define USB3HC_DB_1_OFFS               0x00000484
#define USB3HC_DB_2_OFFS               0x00000488
#define USB3HC_DB_3_OFFS               0x0000048C
#define USB3HC_DB_4_OFFS               0x00000490
#define USB3HC_DB_5_OFFS               0x00000494
#define USB3HC_DB_6_OFFS               0x00000498
#define USB3HC_DB_7_OFFS               0x0000049C
#define USB3HC_DB_8_OFFS               0x000004A0
#define USB3HC_DB_9_OFFS               0x000004A4
#define USB3HC_DB_10_OFFS              0x000004A8
#define USB3HC_DB_11_OFFS              0x000004AC
#define USB3HC_DB_12_OFFS              0x000004B0
#define USB3HC_DB_13_OFFS              0x000004B4
#define USB3HC_DB_14_OFFS              0x000004B8
#define USB3HC_DB_15_OFFS              0x000004BC
#define USB3HC_DB_16_OFFS              0x000004C0
#define USB3HC_DB_17_OFFS              0x000004C4
#define USB3HC_DB_18_OFFS              0x000004C8
#define USB3HC_DB_19_OFFS              0x000004CC
#define USB3HC_DB_20_OFFS              0x000004D0
#define USB3HC_DB_21_OFFS              0x000004D4
#define USB3HC_DB_22_OFFS              0x000004D8
#define USB3HC_DB_23_OFFS              0x000004DC
#define USB3HC_DB_24_OFFS              0x000004E0
#define USB3HC_DB_25_OFFS              0x000004E4
#define USB3HC_DB_26_OFFS              0x000004E8
#define USB3HC_DB_27_OFFS              0x000004EC
#define USB3HC_DB_28_OFFS              0x000004F0
#define USB3HC_DB_29_OFFS              0x000004F4
#define USB3HC_DB_30_OFFS              0x000004F8
#define USB3HC_DB_31_OFFS              0x000004FC
#define USB3HC_DB_32_OFFS              0x00000500
#define USB3HC_DB_33_OFFS              0x00000504
#define USB3HC_DB_34_OFFS              0x00000508
#define USB3HC_DB_35_OFFS              0x0000050C
#define USB3HC_DB_36_OFFS              0x00000510
#define USB3HC_DB_37_OFFS              0x00000514
#define USB3HC_DB_38_OFFS              0x00000518
#define USB3HC_DB_39_OFFS              0x0000051C
#define USB3HC_DB_40_OFFS              0x00000520
#define USB3HC_DB_41_OFFS              0x00000524
#define USB3HC_DB_42_OFFS              0x00000528
#define USB3HC_DB_43_OFFS              0x0000052C
#define USB3HC_DB_44_OFFS              0x00000530
#define USB3HC_DB_45_OFFS              0x00000534
#define USB3HC_DB_46_OFFS              0x00000538
#define USB3HC_DB_47_OFFS              0x0000053C
#define USB3HC_DB_48_OFFS              0x00000540
#define USB3HC_DB_49_OFFS              0x00000544
#define USB3HC_DB_50_OFFS              0x00000548
#define USB3HC_DB_51_OFFS              0x0000054C
#define USB3HC_DB_52_OFFS              0x00000550
#define USB3HC_DB_53_OFFS              0x00000554
#define USB3HC_DB_54_OFFS              0x00000558
#define USB3HC_DB_55_OFFS              0x0000055C
#define USB3HC_DB_56_OFFS              0x00000560
#define USB3HC_DB_57_OFFS              0x00000564
#define USB3HC_DB_58_OFFS              0x00000568
#define USB3HC_DB_59_OFFS              0x0000056C
#define USB3HC_DB_60_OFFS              0x00000570
#define USB3HC_DB_61_OFFS              0x00000574
#define USB3HC_DB_62_OFFS              0x00000578
#define USB3HC_DB_63_OFFS              0x0000057C
#define USB3HC_DB_64_OFFS              0x00000580
#define USB3HC_DB_65_OFFS              0x00000584
#define USB3HC_DB_66_OFFS              0x00000588
#define USB3HC_DB_67_OFFS              0x0000058C
#define USB3HC_DB_68_OFFS              0x00000590
#define USB3HC_DB_69_OFFS              0x00000594
#define USB3HC_DB_70_OFFS              0x00000598
#define USB3HC_DB_71_OFFS              0x0000059C
#define USB3HC_DB_72_OFFS              0x000005A0
#define USB3HC_DB_73_OFFS              0x000005A4
#define USB3HC_DB_74_OFFS              0x000005A8
#define USB3HC_DB_75_OFFS              0x000005AC
#define USB3HC_DB_76_OFFS              0x000005B0
#define USB3HC_DB_77_OFFS              0x000005B4
#define USB3HC_DB_78_OFFS              0x000005B8
#define USB3HC_DB_79_OFFS              0x000005BC
#define USB3HC_DB_80_OFFS              0x000005C0
#define USB3HC_DB_81_OFFS              0x000005C4
#define USB3HC_DB_82_OFFS              0x000005C8
#define USB3HC_DB_83_OFFS              0x000005CC
#define USB3HC_DB_84_OFFS              0x000005D0
#define USB3HC_DB_85_OFFS              0x000005D4
#define USB3HC_DB_86_OFFS              0x000005D8
#define USB3HC_DB_87_OFFS              0x000005DC
#define USB3HC_DB_88_OFFS              0x000005E0
#define USB3HC_DB_89_OFFS              0x000005E4
#define USB3HC_DB_90_OFFS              0x000005E8
#define USB3HC_DB_91_OFFS              0x000005EC
#define USB3HC_DB_92_OFFS              0x000005F0
#define USB3HC_DB_93_OFFS              0x000005F4
#define USB3HC_DB_94_OFFS              0x000005F8
#define USB3HC_DB_95_OFFS              0x000005FC
#define USB3HC_DB_96_OFFS              0x00000600
#define USB3HC_DB_97_OFFS              0x00000604
#define USB3HC_DB_98_OFFS              0x00000608
#define USB3HC_DB_99_OFFS              0x0000060C
#define USB3HC_DB_100_OFFS             0x00000610
#define USB3HC_DB_101_OFFS             0x00000614
#define USB3HC_DB_102_OFFS             0x00000618
#define USB3HC_DB_103_OFFS             0x0000061C
#define USB3HC_DB_104_OFFS             0x00000620
#define USB3HC_DB_105_OFFS             0x00000624
#define USB3HC_DB_106_OFFS             0x00000628
#define USB3HC_DB_107_OFFS             0x0000062C
#define USB3HC_DB_108_OFFS             0x00000630
#define USB3HC_DB_109_OFFS             0x00000634
#define USB3HC_DB_110_OFFS             0x00000638
#define USB3HC_DB_111_OFFS             0x0000063C
#define USB3HC_DB_112_OFFS             0x00000640
#define USB3HC_DB_113_OFFS             0x00000644
#define USB3HC_DB_114_OFFS             0x00000648
#define USB3HC_DB_115_OFFS             0x0000064C
#define USB3HC_DB_116_OFFS             0x00000650
#define USB3HC_DB_117_OFFS             0x00000654
#define USB3HC_DB_118_OFFS             0x00000658
#define USB3HC_DB_119_OFFS             0x0000065C
#define USB3HC_DB_120_OFFS             0x00000660
#define USB3HC_DB_121_OFFS             0x00000664
#define USB3HC_DB_122_OFFS             0x00000668
#define USB3HC_DB_123_OFFS             0x0000066C
#define USB3HC_DB_124_OFFS             0x00000670
#define USB3HC_DB_125_OFFS             0x00000674
#define USB3HC_DB_126_OFFS             0x00000678
#define USB3HC_USBLEGSUP_OFFS          0x00000880
#define USB3HC_USBLEGCTLSTS_OFFS       0x00000884
#define USB3HC_SUPTPRT2_DW0_OFFS       0x00000890
#define USB3HC_SUPTPRT2_DW1_OFFS       0x00000894
#define USB3HC_SUPTPRT2_DW2_OFFS       0x00000898
#define USB3HC_SUPTPRT2_DW3_OFFS       0x0000089C
#define USB3HC_SUPTPRT3_DW0_OFFS       0x000008A0
#define USB3HC_SUPTPRT3_DW1_OFFS       0x000008A4
#define USB3HC_SUPTPRT3_DW2_OFFS       0x000008A8
#define USB3HC_SUPTPRT3_DW3_OFFS       0x000008AC

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* USB3HC_OFFS_DEF_H */
