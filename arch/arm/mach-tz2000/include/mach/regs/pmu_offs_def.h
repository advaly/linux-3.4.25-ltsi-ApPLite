/*
 * arch/arm/mach-tz2000/include/mach/regs/pmu_offs_def.h
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
#define PMU_PowerSwitchOff_TOP_OFFS    0x00000100
#define PMU_InIsoOn_TOP_OFFS           0x00000200
#define PMU_InIsoOff_TOP_OFFS          0x00000300
#define PMU_OutIsoOn_TOP_OFFS          0x00000400
#define PMU_OutIsoOn_DRAMC_OFFS        0x00000410
#define PMU_OutIsoOff_TOP_OFFS         0x00000500
#define PMU_OutIsoOff_DRAMC_OFFS       0x00000510
#define PMU_ClockGatingOn_westpierSS_0_OFFS 0x00001000
#define PMU_ClockGatingOn_cpuSS_0_OFFS 0x00001010
#define PMU_ClockGatingOn_periSS_0_OFFS 0x00001020
#define PMU_ClockGatingOn_periSS_1_OFFS 0x00001024
#define PMU_ClockGatingOn_periSS_2_OFFS 0x00001028
#define PMU_ClockGatingOn_periSS_3_OFFS 0x0000102C
#define PMU_ClockGatingOn_periSS_4_OFFS 0x00001030
#define PMU_ClockGatingOn_dramcSS_0_OFFS 0x00001040
#define PMU_ClockGatingOn_mbootSS_0_OFFS 0x00001050
#define PMU_ClockGatingOn_wconfSS_0_OFFS 0x00001080
#define PMU_ClockGatingOn_usb2hdSS_0_OFFS 0x00001118
#define PMU_ClockGatingOn_lcdcSS_0_OFFS 0x00001128
#define PMU_ClockGatingOn_yuvcSS_0_OFFS 0x00001158
#define PMU_ClockGatingOn_gfxSS_0_OFFS 0x00001178
#define PMU_ClockGatingOn_etherSS_0_OFFS 0x00001190
#define PMU_ClockGatingOn_emmcSS_0_OFFS 0x000011A0
#define PMU_ClockGatingOn_telomereSS_0_OFFS 0x000011C0
#define PMU_ClockGatingOff_westpierSS_0_OFFS 0x00001400
#define PMU_ClockGatingOff_cpuSS_0_OFFS 0x00001410
#define PMU_ClockGatingOff_periSS_0_OFFS 0x00001420
#define PMU_ClockGatingOff_periSS_1_OFFS 0x00001424
#define PMU_ClockGatingOff_periSS_2_OFFS 0x00001428
#define PMU_ClockGatingOff_periSS_3_OFFS 0x0000142C
#define PMU_ClockGatingOff_periSS_4_OFFS 0x00001430
#define PMU_ClockGatingOff_dramcSS_0_OFFS 0x00001440
#define PMU_ClockGatingOff_mbootSS_0_OFFS 0x00001450
#define PMU_ClockGatingOff_wconfSS_0_OFFS 0x00001480
#define PMU_ClockGatingOff_usb2hdSS_0_OFFS 0x00001518
#define PMU_ClockGatingOff_lcdcSS_0_OFFS 0x00001528
#define PMU_ClockGatingOff_yuvcSS_0_OFFS 0x00001558
#define PMU_ClockGatingOff_gfxSS_0_OFFS 0x00001578
#define PMU_ClockGatingOff_etherSS_0_OFFS 0x00001590
#define PMU_ClockGatingOff_emmcSS_0_OFFS 0x000015A0
#define PMU_ClockGatingOff_telomereSS_0_OFFS 0x000015C0
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
#define PMU_SoftResetOn_wconfSS_0_OFFS 0x00001880
#define PMU_SoftResetOn_usb2hdSS_0_OFFS 0x00001918
#define PMU_SoftResetOn_lcdcSS_0_OFFS  0x00001928
#define PMU_SoftResetOn_yuvcSS_0_OFFS  0x00001958
#define PMU_SoftResetOn_gfxSS_0_OFFS   0x00001978
#define PMU_SoftResetOn_etherSS_0_OFFS 0x00001990
#define PMU_SoftResetOn_emmcSS_0_OFFS  0x000019A0
#define PMU_SoftResetOn_telomereSS_0_OFFS 0x000019C0
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
#define PMU_SoftResetOff_wconfSS_0_OFFS 0x00001C80
#define PMU_SoftResetOff_usb2hdSS_0_OFFS 0x00001D18
#define PMU_SoftResetOff_lcdcSS_0_OFFS 0x00001D28
#define PMU_SoftResetOff_yuvcSS_0_OFFS 0x00001D58
#define PMU_SoftResetOff_gfxSS_0_OFFS  0x00001D78
#define PMU_SoftResetOff_etherSS_0_OFFS 0x00001D90
#define PMU_SoftResetOff_emmcSS_0_OFFS 0x00001DA0
#define PMU_SoftResetOff_telomereSS_0_OFFS 0x00001DC0
#define PMU_ClockGatingOnForPower_TOP_OFFS 0x00002000
#define PMU_ClockGatingOnForPower_DRAMC_OFFS 0x00002010
#define PMU_ClockGatingOffForPower_TOP_OFFS 0x00002100
#define PMU_ClockGatingOffForPower_DRAMC_OFFS 0x00002110
#define PMU_POREN_OFFS                 0x00002400
#define PMU_DDR_Control_OFFS           0x00002480
#define PMU_USB_Control_OFFS           0x00002484
#define PMU_NAND_Control_OFFS          0x00002488
#define PMU_SPI_Control_OFFS           0x0000248C
#define PMU_CPU_Clock_Divede_Setting_OFFS 0x00004404
#define PMU_PANEL_CLOCK_0_OFFS         0x00004470
#define PMU_AUDIO_CLOCK_0_OFFS         0x00004480
#define PMU_UART_CLOCK_0_OFFS          0x00004490
#define PMU_PLLConfig_PLLLCD_0_OFFS    0x00004530
#define PMU_PLLConfig_PLLLCD_1_OFFS    0x00004534
#define PMU_PLLConfig_PLLI2S_0_OFFS    0x00004580
#define PMU_PLLConfig_PLLI2S_1_OFFS    0x00004584
#define PMU_PLLConfig_PLLI2S_2_OFFS    0x00004588
#define PMU_PLLConfig_PLLI2S_3_OFFS    0x0000458C
#define PMU_Status_PswAck_OFFS         0x00005700
#define PMU_ModeStatus_WatchdogTimer_OFFS 0x00005780
#define PMU_Status_Interrupt_OFFS      0x00005790
#define PMU_Mask_Interrupt_OFFS        0x00005794

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PMU_OFFS_DEF_H */
