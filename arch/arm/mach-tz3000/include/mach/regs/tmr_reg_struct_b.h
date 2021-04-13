/*
 * arch/arm/mach-tz3000/include/mach/regs/tmr_reg_struct_b.h
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

#ifndef _TMR_REG_STRUCT_B_H
#define _TMR_REG_STRUCT_B_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // T0Control Register
struct TMR_T0CONTROL {
	unsigned int reserved:24;		// [31:8]
	unsigned int TCE:1;		// [7]
	unsigned int CCDE:1;		// [6]
	unsigned int CRE:1;		// [5]
	unsigned int reserved2:3;		// [4:2]
	unsigned int TMODE:2;		// [1:0]
};
 // T0Interrupt_Status Register
struct TMR_T0INTERRUPT_STATUS {
	unsigned int reserved:28;		// [31:4]
	unsigned int TWIS:1;		// [3]
	unsigned int reserved2:2;		// [2:1]
	unsigned int TIIS:1;		// [0]
};
 // T0Compare_A Register
struct TMR_T0COMPARE_A {
	unsigned int TCVA:32;		// [31:0]
};
 // T0Interval_Mode Register
struct TMR_T0INTERVAL_MODE {
	unsigned int reserved:16;		// [31:16]
	unsigned int TIIE:1;		// [15]
	unsigned int reserved2:14;		// [14:1]
	unsigned int TZCE:1;		// [0]
};
 // T0Timer_Counter_Clock_Divider Register
struct TMR_T0TIMER_COUNTER_CLOCK_DIVIDER {
	unsigned int reserved:29;		// [31:3]
	unsigned int CCD:3;		// [2:0]
};
 // T0Watchdog_Timer_Mode Register
struct TMR_T0WATCHDOG_TIMER_MODE {
	unsigned int reserved:16;		// [31:16]
	unsigned int TWIE:1;		// [15]
	unsigned int reserved2:7;		// [14:8]
	unsigned int WDIS:1;		// [7]
	unsigned int reserved3:6;		// [6:1]
	unsigned int TWC:1;		// [0]
};
 // T0Timer_Counter_Read Register
struct TMR_T0TIMER_COUNTER_READ {
	unsigned int TCNT:32;		// [31:0]
};
 // T1Control Register
struct TMR_T1CONTROL {
	unsigned int reserved:24;		// [31:8]
	unsigned int TCE:1;		// [7]
	unsigned int CCDE:1;		// [6]
	unsigned int CRE:1;		// [5]
	unsigned int reserved2:3;		// [4:2]
	unsigned int TMODE:2;		// [1:0]
};
 // T1Interrupt_Status Register
struct TMR_T1INTERRUPT_STATUS {
	unsigned int reserved:28;		// [31:4]
	unsigned int TWIS:1;		// [3]
	unsigned int reserved2:2;		// [2:1]
	unsigned int TIIS:1;		// [0]
};
 // T1Compare_A Register
struct TMR_T1COMPARE_A {
	unsigned int TCVA:32;		// [31:0]
};
 // T1Interval_Mode Register
struct TMR_T1INTERVAL_MODE {
	unsigned int reserved:16;		// [31:16]
	unsigned int TIIE:1;		// [15]
	unsigned int reserved2:14;		// [14:1]
	unsigned int TZCE:1;		// [0]
};
 // T1Timer_Counter_Clock_Divider Register
struct TMR_T1TIMER_COUNTER_CLOCK_DIVIDER {
	unsigned int reserved:29;		// [31:3]
	unsigned int CCD:3;		// [2:0]
};
 // T1Watchdog_Timer_Mode Register
struct TMR_T1WATCHDOG_TIMER_MODE {
	unsigned int reserved:16;		// [31:16]
	unsigned int TWIE:1;		// [15]
	unsigned int reserved2:7;		// [14:8]
	unsigned int WDIS:1;		// [7]
	unsigned int reserved3:6;		// [6:1]
	unsigned int TWC:1;		// [0]
};
 // T1Timer_Counter_Read Register
struct TMR_T1TIMER_COUNTER_READ {
	unsigned int TCNT:32;		// [31:0]
};
 // T2Control Register
struct TMR_T2CONTROL {
	unsigned int reserved:24;		// [31:8]
	unsigned int TCE:1;		// [7]
	unsigned int CCDE:1;		// [6]
	unsigned int CRE:1;		// [5]
	unsigned int reserved2:3;		// [4:2]
	unsigned int TMODE:2;		// [1:0]
};
 // T2Interrupt_Status Register
struct TMR_T2INTERRUPT_STATUS {
	unsigned int reserved:28;		// [31:4]
	unsigned int TWIS:1;		// [3]
	unsigned int reserved2:2;		// [2:1]
	unsigned int TIIS:1;		// [0]
};
 // T2Compare_A Register
struct TMR_T2COMPARE_A {
	unsigned int TCVA:32;		// [31:0]
};
 // T2Interval_Mode Register
struct TMR_T2INTERVAL_MODE {
	unsigned int reserved:16;		// [31:16]
	unsigned int TIIE:1;		// [15]
	unsigned int reserved2:14;		// [14:1]
	unsigned int TZCE:1;		// [0]
};
 // T2Timer_Counter_Clock_Divider Register
struct TMR_T2TIMER_COUNTER_CLOCK_DIVIDER {
	unsigned int reserved:29;		// [31:3]
	unsigned int CCD:3;		// [2:0]
};
 // T2Watchdog_Timer_Mode Register
struct TMR_T2WATCHDOG_TIMER_MODE {
	unsigned int reserved:16;		// [31:16]
	unsigned int TWIE:1;		// [15]
	unsigned int reserved2:7;		// [14:8]
	unsigned int WDIS:1;		// [7]
	unsigned int reserved3:6;		// [6:1]
	unsigned int TWC:1;		// [0]
};
 // T2Timer_Counter_Read Register
struct TMR_T2TIMER_COUNTER_READ {
	unsigned int TCNT:32;		// [31:0]
};
 // T3Control Register
struct TMR_T3CONTROL {
	unsigned int reserved:24;		// [31:8]
	unsigned int TCE:1;		// [7]
	unsigned int CCDE:1;		// [6]
	unsigned int CRE:1;		// [5]
	unsigned int reserved2:3;		// [4:2]
	unsigned int TMODE:2;		// [1:0]
};
 // T3Interrupt_Status Register
struct TMR_T3INTERRUPT_STATUS {
	unsigned int reserved:28;		// [31:4]
	unsigned int TWIS:1;		// [3]
	unsigned int reserved2:2;		// [2:1]
	unsigned int TIIS:1;		// [0]
};
 // T3Compare_A Register
struct TMR_T3COMPARE_A {
	unsigned int TCVA:32;		// [31:0]
};
 // T3Interval_Mode Register
struct TMR_T3INTERVAL_MODE {
	unsigned int reserved:16;		// [31:16]
	unsigned int TIIE:1;		// [15]
	unsigned int reserved2:14;		// [14:1]
	unsigned int TZCE:1;		// [0]
};
 // T3Timer_Counter_Clock_Divider Register
struct TMR_T3TIMER_COUNTER_CLOCK_DIVIDER {
	unsigned int reserved:29;		// [31:3]
	unsigned int CCD:3;		// [2:0]
};
 // T3Watchdog_Timer_Mode Register
struct TMR_T3WATCHDOG_TIMER_MODE {
	unsigned int reserved:16;		// [31:16]
	unsigned int TWIE:1;		// [15]
	unsigned int reserved2:7;		// [14:8]
	unsigned int WDIS:1;		// [7]
	unsigned int reserved3:6;		// [6:1]
	unsigned int TWC:1;		// [0]
};
 // T3Timer_Counter_Read Register
struct TMR_T3TIMER_COUNTER_READ {
	unsigned int TCNT:32;		// [31:0]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TMR_REG_STRUCT_B_H */
