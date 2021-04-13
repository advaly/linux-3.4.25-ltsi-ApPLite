/*
 * arch/arm/mach-tz3000/include/mach/regs/fdramc_offs_def.h
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

#ifndef FDRAMC_OFFS_DEF_H
#define FDRAMC_OFFS_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

#define FDRAMC_DRAMType_OFFS           0x0000041C
#define FDRAMC_AddressConfig_CS_OFFS   0x00000420
#define FDRAMC_AddressConfig_Row_OFFS  0x00000424
#define FDRAMC_AddressConfig_Bank_OFFS 0x00000428
#define FDRAMC_AddressConfig_Col_OFFS  0x0000042C
#define FDRAMC_DataConfig_OFFS         0x00000438
#define FDRAMC_BstLenLog_OFFS          0x00000440
#define FDRAMC_MRRBstLenLog_OFFS       0x00000444
#define FDRAMC_BWHalfMode_OFFS         0x00000450
#define FDRAMC_APwrDWtPd_OFFS          0x0000049C
#define FDRAMC_RftoRfMax_OFFS          0x00000504
#define FDRAMC_PAlltoANYPd_OFFS        0x0000050C
#define FDRAMC_InitMtoMPd_OFFS         0x00000514
#define FDRAMC_ReftoANYPd_OFFS         0x0000051C
#define FDRAMC_BkAtoRWPd_OFFS          0x00000524
#define FDRAMC_AtoAPd_OFFS             0x0000052C
#define FDRAMC_BkRtoPPd_OFFS           0x00000530
#define FDRAMC_BkWtoPPd_OFFS           0x00000534
#define FDRAMC_BkPtoANYPd_OFFS         0x0000053C
#define FDRAMC_RtoWPd_OFFS             0x00000544
#define FDRAMC_InitCkeUptoANYPd_OFFS   0x0000054C
#define FDRAMC_BkAtoAPd_OFFS           0x00000550
#define FDRAMC_InitOITPd_OFFS          0x00000554
#define FDRAMC_BkAtoPPd_OFFS           0x0000055C
#define FDRAMC_BkRAtoANYPd_OFFS        0x00000560
#define FDRAMC_BkWAtoANYPd_OFFS        0x00000564
#define FDRAMC_TAWPd_OFFS              0x00000568
#define FDRAMC_FAWPd_OFFS              0x0000056C
#define FDRAMC_WtoRPd_OFFS             0x00000584
#define FDRAMC_InitDLLKPd_OFFS         0x0000058C
#define FDRAMC_SrxtoANYPd_OFFS         0x000005B4
#define FDRAMC_SrxtoRWPd_OFFS          0x000005BC
#define FDRAMC_PdxtoANYPd_OFFS         0x000005C0
#define FDRAMC_PdxtoRWPd_OFFS          0x000005C4
#define FDRAMC_MtoANYPd_OFFS           0x000005CC
#define FDRAMC_ZQCLtoANYPd_OFFS        0x000005D0
#define FDRAMC_InitZQCLtoANYPd_OFFS    0x000005D4
#define FDRAMC_ZQCStoANYPd_OFFS        0x000005DC
#define FDRAMC_RtoPWDPd_OFFS           0x000005FC
#define FDRAMC_PdxtoPWDPd_OFFS         0x00000618
#define FDRAMC_SrxtoPWDPd_OFFS         0x0000061C
#define FDRAMC_SretoSrxPd_OFFS         0x00000620
#define FDRAMC_PdetoPdxPd_OFFS         0x00000628
#define FDRAMC_DRkWtoWPd_OFFS          0x00000634
#define FDRAMC_DRkRtoRPd_OFFS          0x00000638
#define FDRAMC_WRDataLat_OFFS          0x00000704
#define FDRAMC_WRDataEnLat_OFFS        0x0000070C
#define FDRAMC_RDDataLat_OFFS          0x0000071C
#define FDRAMC_CTRLUPD_OFFS            0x00000728
#define FDRAMC_RDtoCTRLUPDPd_OFFS      0x0000072C
#define FDRAMC_CmdTiming_OFFS          0x00000744
#define FDRAMC_RDTiming_OFFS           0x00000748
#define FDRAMC_ODTMode_CS0_OFFS        0x00000780
#define FDRAMC_ODTMode_CS1_OFFS        0x00000784

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* FDRAMC_OFFS_DEF_H */
