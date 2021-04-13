/*
 * arch/arm/mach-tz3000/include/mach/regs/pmu_offs_def.h
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

#ifndef PMU_OFFS_DEF_H
#define PMU_OFFS_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

#define PMU_PowerSwitchOn_TOP_OFFS     0x00000000
#define PMU_PowerSwitchOn_CPU_OFFS     0x00000004
#define PMU_PowerSwitchOn_GPU_OFFS     0x00000008
#define PMU_PowerSwitchOn_VIDEO_OFFS   0x0000000C
#define PMU_PowerSwitchOff_TOP_OFFS    0x00000100
#define PMU_PowerSwitchOff_CPU_OFFS    0x00000104
#define PMU_PowerSwitchOff_GPU_OFFS    0x00000108
#define PMU_PowerSwitchOff_VIDEO_OFFS  0x0000010C
#define PMU_InIsoOn_GPU_OFFS           0x00000208
#define PMU_InIsoOn_VIDEO_OFFS         0x0000020C
#define PMU_InIsoOff_GPU_OFFS          0x00000308
#define PMU_InIsoOff_VIDEO_OFFS        0x0000030C
#define PMU_OutIsoOn_TOP_OFFS          0x00000400
#define PMU_OutIsoOn_CPU_OFFS          0x00000404
#define PMU_OutIsoOn_GPU_OFFS          0x00000408
#define PMU_OutIsoOn_VIDEO_OFFS        0x0000040C
#define PMU_OutIsoOff_TOP_OFFS         0x00000500
#define PMU_OutIsoOff_CPU_OFFS         0x00000504
#define PMU_OutIsoOff_GPU_OFFS         0x00000508
#define PMU_OutIsoOff_VIDEO_OFFS       0x0000050C
#define PMU_ClockGatingOn_westpierSS_0_OFFS 0x00001000
#define PMU_ClockGatingOn_cpuSS_0_OFFS 0x00001010
#define PMU_ClockGatingOn_periSS_0_OFFS 0x00001020
#define PMU_ClockGatingOn_periSS_1_OFFS 0x00001024
#define PMU_ClockGatingOn_periSS_2_OFFS 0x00001028
#define PMU_ClockGatingOn_periSS_3_OFFS 0x0000102C
#define PMU_ClockGatingOn_periSS_4_OFFS 0x00001030
#define PMU_ClockGatingOn_dramcSS_0_OFFS 0x00001040
#define PMU_ClockGatingOn_mbootSS_0_OFFS 0x00001050
#define PMU_ClockGatingOn_dbgmonSS_0_OFFS 0x00001060
#define PMU_ClockGatingOn_eastpierSS_0_OFFS 0x00001100
#define PMU_ClockGatingOn_hsioSS_0_OFFS 0x00001110
#define PMU_ClockGatingOn_dispifSS_0_OFFS 0x00001120
#define PMU_ClockGatingOn_camifSS_0_OFFS 0x00001130
#define PMU_ClockGatingOn_vcodecSS_0_OFFS 0x00001140
#define PMU_ClockGatingOn_vconvSS_0_OFFS 0x00001150
#define PMU_ClockGatingOn_irecogSS_0_OFFS 0x00001160
#define PMU_ClockGatingOn_gpuSS_0_OFFS 0x00001170
#define PMU_ClockGatingOn_econfSS_0_OFFS 0x00001180
#define PMU_ClockGatingOn_etherSS_0_OFFS 0x00001190
#define PMU_ClockGatingOn_emmcSS_0_OFFS 0x000011A0
#define PMU_ClockGatingOn_nandcSS_0_OFFS 0x000011B0
#define PMU_ClockGatingOff_westpierSS_0_OFFS 0x00001400
#define PMU_ClockGatingOff_cpuSS_0_OFFS 0x00001410
#define PMU_ClockGatingOff_periSS_0_OFFS 0x00001420
#define PMU_ClockGatingOff_periSS_1_OFFS 0x00001424
#define PMU_ClockGatingOff_periSS_2_OFFS 0x00001428
#define PMU_ClockGatingOff_periSS_3_OFFS 0x0000142C
#define PMU_ClockGatingOff_periSS_4_OFFS 0x00001430
#define PMU_ClockGatingOff_dramcSS_0_OFFS 0x00001440
#define PMU_ClockGatingOff_mbootSS_0_OFFS 0x00001450
#define PMU_ClockGatingOff_dbgmonSS_0_OFFS 0x00001460
#define PMU_ClockGatingOff_eastpierSS_0_OFFS 0x00001500
#define PMU_ClockGatingOff_hsioSS_0_OFFS 0x00001510
#define PMU_ClockGatingOff_dispifSS_0_OFFS 0x00001520
#define PMU_ClockGatingOff_camifSS_0_OFFS 0x00001530
#define PMU_ClockGatingOff_vcodecSS_0_OFFS 0x00001540
#define PMU_ClockGatingOff_vconvSS_0_OFFS 0x00001550
#define PMU_ClockGatingOff_irecogSS_0_OFFS 0x00001560
#define PMU_ClockGatingOff_gpuSS_0_OFFS 0x00001570
#define PMU_ClockGatingOff_econfSS_0_OFFS 0x00001580
#define PMU_ClockGatingOff_etherSS_0_OFFS 0x00001590
#define PMU_ClockGatingOff_emmcSS_0_OFFS 0x000015A0
#define PMU_ClockGatingOff_nandcSS_0_OFFS 0x000015B0
#define PMU_SoftResetOn_westpierSS_0_OFFS 0x00001800
#define PMU_SoftResetOn_cpuSS_0_OFFS   0x00001810
#define PMU_SoftResetOn_cpuSS_1_OFFS   0x00001814
#define PMU_SoftResetOn_periSS_0_OFFS  0x00001820
#define PMU_SoftResetOn_periSS_1_OFFS  0x00001824
#define PMU_SoftResetOn_periSS_2_OFFS  0x00001828
#define PMU_SoftResetOn_periSS_3_OFFS  0x0000182C
#define PMU_SoftResetOn_periSS_4_OFFS  0x00001830
#define PMU_SoftResetOn_dramcSS_0_OFFS 0x00001840
#define PMU_SoftResetOn_mbootSS_0_OFFS 0x00001850
#define PMU_SoftResetOn_dbgmonSS_0_OFFS 0x00001860
#define PMU_SoftResetOn_eastpierSS_0_OFFS 0x00001900
#define PMU_SoftResetOn_hsioSS_0_OFFS  0x00001910
#define PMU_SoftResetOn_dispifSS_0_OFFS 0x00001920
#define PMU_SoftResetOn_camifSS_0_OFFS 0x00001930
#define PMU_SoftResetOn_vcodecSS_0_OFFS 0x00001940
#define PMU_SoftResetOn_vconvSS_0_OFFS 0x00001950
#define PMU_SoftResetOn_irecogSS_0_OFFS 0x00001960
#define PMU_SoftResetOn_gpuSS_0_OFFS   0x00001970
#define PMU_SoftResetOn_econfSS_0_OFFS 0x00001980
#define PMU_SoftResetOn_etherSS_0_OFFS 0x00001990
#define PMU_SoftResetOn_emmcSS_0_OFFS  0x000019A0
#define PMU_SoftResetOn_nandcSS_0_OFFS 0x000019B0
#define PMU_SoftResetOff_westpierSS_0_OFFS 0x00001C00
#define PMU_SoftResetOff_cpuSS_0_OFFS  0x00001C10
#define PMU_SoftResetOff_cpuSS_1_OFFS  0x00001C14
#define PMU_SoftResetOff_periSS_0_OFFS 0x00001C20
#define PMU_SoftResetOff_periSS_1_OFFS 0x00001C24
#define PMU_SoftResetOff_periSS_2_OFFS 0x00001C28
#define PMU_SoftResetOff_periSS_3_OFFS 0x00001C2C
#define PMU_SoftResetOff_periSS_4_OFFS 0x00001C30
#define PMU_SoftResetOff_dramcSS_0_OFFS 0x00001C40
#define PMU_SoftResetOff_mbootSS_0_OFFS 0x00001C50
#define PMU_SoftResetOff_dbgmonSS_0_OFFS 0x00001C60
#define PMU_SoftResetOff_eastpierSS_0_OFFS 0x00001D00
#define PMU_SoftResetOff_hsioSS_0_OFFS 0x00001D10
#define PMU_SoftResetOff_dispifSS_0_OFFS 0x00001D20
#define PMU_SoftResetOff_camifSS_0_OFFS 0x00001D30
#define PMU_SoftResetOff_vcodecSS_0_OFFS 0x00001D40
#define PMU_SoftResetOff_vconvSS_0_OFFS 0x00001D50
#define PMU_SoftResetOff_irecogSS_0_OFFS 0x00001D60
#define PMU_SoftResetOff_gpuSS_0_OFFS  0x00001D70
#define PMU_SoftResetOff_econfSS_0_OFFS 0x00001D80
#define PMU_SoftResetOff_etherSS_0_OFFS 0x00001D90
#define PMU_SoftResetOff_emmcSS_0_OFFS 0x00001DA0
#define PMU_SoftResetOff_nandcSS_0_OFFS 0x00001DB0
#define PMU_ClockGatingOnForPower_TOP_OFFS 0x00002000
#define PMU_ClockGatingOnForPower_CPU_OFFS 0x00002004
#define PMU_ClockGatingOnForPower_GPU_OFFS 0x00002008
#define PMU_ClockGatingOnForPower_VIDEO_OFFS 0x0000200C
#define PMU_ClockGatingOffForPower_TOP_OFFS 0x00002100
#define PMU_ClockGatingOffForPower_CPU_OFFS 0x00002104
#define PMU_ClockGatingOffForPower_GPU_OFFS 0x00002108
#define PMU_ClockGatingOffForPower_VIDEO_OFFS 0x0000210C
#define PMU_CPU_Clock_Divede_Setting_OFFS 0x00004404
#define PMU_Frequency_GPU_OFFS         0x00004408
#define PMU_Frequency_VIDEO_OFFS       0x0000440C
#define PMU_Frequency_irecogSS_OFFS    0x00004410
#define PMU_AUDIO_CLOCK_0_OFFS         0x00004480
#define PMU_UART_CLOCK_0_OFFS          0x00004490
#define PMU_PLLConfig_PLLCPU_0_OFFS    0x00004500
#define PMU_PLLConfig_PLLCPU_1_OFFS    0x00004504
#define PMU_PLLConfig_PLLETH_0_OFFS    0x00004520
#define PMU_PLLConfig_PLLETH_1_OFFS    0x00004524
#define PMU_PLLConfig_PLLDSI_0_OFFS    0x00004530
#define PMU_PLLConfig_PLLDSI_1_OFFS    0x00004534
#define PMU_PLLConfig_PLLI2S_0_OFFS    0x00004580
#define PMU_PLLConfig_PLLI2S_1_OFFS    0x00004584
#define PMU_PLLConfig_PLLI2S_2_OFFS    0x00004588
#define PMU_PLLConfig_PLLI2S_3_OFFS    0x0000458C
#define PMU_SeqStatus_DFS_GPU_OFFS     0x00005208
#define PMU_SeqStatus_DFS_VIDEO_OFFS   0x0000520C
#define PMU_SeqStatus_DFS_irecogSS_OFFS 0x00005210
#define PMU_SeqStatus_PowerOn_TOP_OFFS 0x00005300
#define PMU_SeqStatus_PowerOn_CPU_OFFS 0x00005304
#define PMU_SeqStatus_PowerOn_GPU_OFFS 0x00005308
#define PMU_SeqStatus_PowerOn_VIDEO_OFFS 0x0000530C
#define PMU_SeqStatus_PowerOff_TOP_OFFS 0x00005400
#define PMU_SeqStatus_PowerOff_CPU_OFFS 0x00005404
#define PMU_SeqStatus_PowerOff_GPU_OFFS 0x00005408
#define PMU_SeqStatus_PowerOff_VIDEO_OFFS 0x0000540C
#define PMU_Status_PswAck_OFFS         0x00005700
#define PMU_ModeStatus_WatchdogTimer_OFFS 0x00005780
#define PMU_Status_Interrupt_OFFS      0x00005790
#define PMU_Mask_Interrupt_OFFS        0x00005794
#define PMU_EFUSE_0_OFFS               0x00006100
#define PMU_EFUSE_1_OFFS               0x00006104

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PMU_OFFS_DEF_H */
