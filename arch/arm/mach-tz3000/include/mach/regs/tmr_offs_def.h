/*
 * arch/arm/mach-tz3000/include/mach/regs/tmr_offs_def.h
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

#ifndef TMR_OFFS_DEF_H
#define TMR_OFFS_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

#define TMR_T0Control_OFFS             0x00000000
#define TMR_T0Interrupt_Status_OFFS    0x00000004
#define TMR_T0Compare_A_OFFS           0x00000008
#define TMR_T0Interval_Mode_OFFS       0x00000010
#define TMR_T0Timer_Counter_Clock_Divider_OFFS 0x00000020
#define TMR_T0Watchdog_Timer_Mode_OFFS 0x00000040
#define TMR_T0Timer_Counter_Read_OFFS  0x000000F0
#define TMR_T1Control_OFFS             0x00000100
#define TMR_T1Interrupt_Status_OFFS    0x00000104
#define TMR_T1Compare_A_OFFS           0x00000108
#define TMR_T1Interval_Mode_OFFS       0x00000110
#define TMR_T1Timer_Counter_Clock_Divider_OFFS 0x00000120
#define TMR_T1Watchdog_Timer_Mode_OFFS 0x00000140
#define TMR_T1Timer_Counter_Read_OFFS  0x000001F0
#define TMR_T2Control_OFFS             0x00000200
#define TMR_T2Interrupt_Status_OFFS    0x00000204
#define TMR_T2Compare_A_OFFS           0x00000208
#define TMR_T2Interval_Mode_OFFS       0x00000210
#define TMR_T2Timer_Counter_Clock_Divider_OFFS 0x00000220
#define TMR_T2Watchdog_Timer_Mode_OFFS 0x00000240
#define TMR_T2Timer_Counter_Read_OFFS  0x000002F0
#define TMR_T3Control_OFFS             0x00000300
#define TMR_T3Interrupt_Status_OFFS    0x00000304
#define TMR_T3Compare_A_OFFS           0x00000308
#define TMR_T3Interval_Mode_OFFS       0x00000310
#define TMR_T3Timer_Counter_Clock_Divider_OFFS 0x00000320
#define TMR_T3Watchdog_Timer_Mode_OFFS 0x00000340
#define TMR_T3Timer_Counter_Read_OFFS  0x000003F0

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TMR_OFFS_DEF_H */
