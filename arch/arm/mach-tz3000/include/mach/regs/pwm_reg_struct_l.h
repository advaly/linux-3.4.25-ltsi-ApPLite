/*
 * arch/arm/mach-tz3000/include/mach/regs/pwm_reg_struct_l.h
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

#ifndef _PWM_REG_STRUCT_L_H
#define _PWM_REG_STRUCT_L_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // PWM0_CR Register
struct PWM_PWM0_CR {
	unsigned int ENB:1;		// [0]
	unsigned int UPD:1;		// [1]
	unsigned int reserved1:6;		// [7:2]
	unsigned int POL:1;		// [8]
	unsigned int LVS:1;		// [9]
	unsigned int reserved2:6;		// [15:10]
	unsigned int DIV:4;		// [19:16]
	unsigned int reserved3:4;		// [23:20]
	unsigned int fixed:2;		// [25:24]
	unsigned int reserved4:2;		// [27:26]
	unsigned int ENBSEL:2;		// [29:28]
	unsigned int reserved5:2;		// [31:30]
};
 // PWM0_FREQ Register
struct PWM_PWM0_FREQ {
	unsigned int FREQ:32;		// [31:0]
};
 // PWM0_DUTY Register
struct PWM_PWM0_DUTY {
	unsigned int DUTY:32;		// [31:0]
};
 // PWM0_ITERATION Register
struct PWM_PWM0_ITERATION {
	unsigned int ITERATION:16;		// [15:0]
	unsigned int reserved:16;		// [31:16]
};
 // PWM0_CURFREQ Register
struct PWM_PWM0_CURFREQ {
	unsigned int CURFREQ:32;		// [31:0]
};
 // PWM0_CURDUTY Register
struct PWM_PWM0_CURDUTY {
	unsigned int INTC0:32;		// [31:0]
};
 // PWM0_CURITER Register
struct PWM_PWM0_CURITER {
	unsigned int CURITER:16;		// [15:0]
	unsigned int CURCYCLE:16;		// [31:16]
};
 // PWM0_COUNT Register
struct PWM_PWM0_COUNT {
	unsigned int COUNT:32;		// [31:0]
};
 // PWM1_CR Register
struct PWM_PWM1_CR {
	unsigned int ENB:1;		// [0]
	unsigned int UPD:1;		// [1]
	unsigned int reserved1:6;		// [7:2]
	unsigned int POL:1;		// [8]
	unsigned int LVS:1;		// [9]
	unsigned int reserved2:6;		// [15:10]
	unsigned int DIV:4;		// [19:16]
	unsigned int reserved3:4;		// [23:20]
	unsigned int fixed:2;		// [25:24]
	unsigned int reserved4:2;		// [27:26]
	unsigned int ENBSEL:2;		// [29:28]
	unsigned int reserved5:2;		// [31:30]
};
 // PWM1_FREQ Register
struct PWM_PWM1_FREQ {
	unsigned int FREQ:32;		// [31:0]
};
 // PWM1_DUTY Register
struct PWM_PWM1_DUTY {
	unsigned int DUTY:32;		// [31:0]
};
 // PWM1_ITERATION Register
struct PWM_PWM1_ITERATION {
	unsigned int ITERATION:16;		// [15:0]
	unsigned int reserved:16;		// [31:16]
};
 // PWM1_CURFREQ Register
struct PWM_PWM1_CURFREQ {
	unsigned int CURFREQ:32;		// [31:0]
};
 // PWM1_CURDUTY Register
struct PWM_PWM1_CURDUTY {
	unsigned int INTC0:32;		// [31:0]
};
 // PWM1_CURITER Register
struct PWM_PWM1_CURITER {
	unsigned int CURITER:16;		// [15:0]
	unsigned int CURCYCLE:16;		// [31:16]
};
 // PWM1_COUNT Register
struct PWM_PWM1_COUNT {
	unsigned int COUNT:32;		// [31:0]
};
 // PWM2_CR Register
struct PWM_PWM2_CR {
	unsigned int ENB:1;		// [0]
	unsigned int UPD:1;		// [1]
	unsigned int reserved1:6;		// [7:2]
	unsigned int POL:1;		// [8]
	unsigned int LVS:1;		// [9]
	unsigned int reserved2:6;		// [15:10]
	unsigned int DIV:4;		// [19:16]
	unsigned int reserved3:4;		// [23:20]
	unsigned int fixed:2;		// [25:24]
	unsigned int reserved4:2;		// [27:26]
	unsigned int ENBSEL:2;		// [29:28]
	unsigned int reserved5:2;		// [31:30]
};
 // PWM2_FREQ Register
struct PWM_PWM2_FREQ {
	unsigned int FREQ:32;		// [31:0]
};
 // PWM2_DUTY Register
struct PWM_PWM2_DUTY {
	unsigned int DUTY:32;		// [31:0]
};
 // PWM2_ITERATION Register
struct PWM_PWM2_ITERATION {
	unsigned int ITERATION:16;		// [15:0]
	unsigned int reserved:16;		// [31:16]
};
 // PWM2_CURFREQ Register
struct PWM_PWM2_CURFREQ {
	unsigned int CURFREQ:32;		// [31:0]
};
 // PWM2_CURDUTY Register
struct PWM_PWM2_CURDUTY {
	unsigned int INTC0:32;		// [31:0]
};
 // PWM2_CURITER Register
struct PWM_PWM2_CURITER {
	unsigned int CURITER:16;		// [15:0]
	unsigned int CURCYCLE:16;		// [31:16]
};
 // PWM2_COUNT Register
struct PWM_PWM2_COUNT {
	unsigned int COUNT:32;		// [31:0]
};
 // PWM3_CR Register
struct PWM_PWM3_CR {
	unsigned int ENB:1;		// [0]
	unsigned int UPD:1;		// [1]
	unsigned int reserved1:6;		// [7:2]
	unsigned int POL:1;		// [8]
	unsigned int LVS:1;		// [9]
	unsigned int reserved2:6;		// [15:10]
	unsigned int DIV:4;		// [19:16]
	unsigned int reserved3:4;		// [23:20]
	unsigned int fixed:2;		// [25:24]
	unsigned int reserved4:2;		// [27:26]
	unsigned int ENBSEL:2;		// [29:28]
	unsigned int reserved5:2;		// [31:30]
};
 // PWM3_FREQ Register
struct PWM_PWM3_FREQ {
	unsigned int FREQ:32;		// [31:0]
};
 // PWM3_DUTY Register
struct PWM_PWM3_DUTY {
	unsigned int DUTY:32;		// [31:0]
};
 // PWM3_ITERATION Register
struct PWM_PWM3_ITERATION {
	unsigned int ITERATION:16;		// [15:0]
	unsigned int reserved:16;		// [31:16]
};
 // PWM3_CURFREQ Register
struct PWM_PWM3_CURFREQ {
	unsigned int CURFREQ:32;		// [31:0]
};
 // PWM3_CURDUTY Register
struct PWM_PWM3_CURDUTY {
	unsigned int INTC0:32;		// [31:0]
};
 // PWM3_CURITER Register
struct PWM_PWM3_CURITER {
	unsigned int CURITER:16;		// [15:0]
	unsigned int CURCYCLE:16;		// [31:16]
};
 // PWM3_COUNT Register
struct PWM_PWM3_COUNT {
	unsigned int COUNT:32;		// [31:0]
};
 // PWM4_CR Register
struct PWM_PWM4_CR {
	unsigned int ENB:1;		// [0]
	unsigned int UPD:1;		// [1]
	unsigned int reserved1:6;		// [7:2]
	unsigned int POL:1;		// [8]
	unsigned int LVS:1;		// [9]
	unsigned int reserved2:6;		// [15:10]
	unsigned int DIV:4;		// [19:16]
	unsigned int reserved3:4;		// [23:20]
	unsigned int fixed:2;		// [25:24]
	unsigned int reserved4:2;		// [27:26]
	unsigned int ENBSEL:2;		// [29:28]
	unsigned int reserved5:2;		// [31:30]
};
 // PWM4_FREQ Register
struct PWM_PWM4_FREQ {
	unsigned int FREQ:32;		// [31:0]
};
 // PWM4_DUTY Register
struct PWM_PWM4_DUTY {
	unsigned int DUTY:32;		// [31:0]
};
 // PWM4_ITERATION Register
struct PWM_PWM4_ITERATION {
	unsigned int ITERATION:16;		// [15:0]
	unsigned int reserved:16;		// [31:16]
};
 // PWM4_CURFREQ Register
struct PWM_PWM4_CURFREQ {
	unsigned int CURFREQ:32;		// [31:0]
};
 // PWM4_CURDUTY Register
struct PWM_PWM4_CURDUTY {
	unsigned int INTC0:32;		// [31:0]
};
 // PWM4_CURITER Register
struct PWM_PWM4_CURITER {
	unsigned int CURITER:16;		// [15:0]
	unsigned int CURCYCLE:16;		// [31:16]
};
 // PWM4_COUNT Register
struct PWM_PWM4_COUNT {
	unsigned int COUNT:32;		// [31:0]
};
 // PWM5_CR Register
struct PWM_PWM5_CR {
	unsigned int ENB:1;		// [0]
	unsigned int UPD:1;		// [1]
	unsigned int reserved1:6;		// [7:2]
	unsigned int POL:1;		// [8]
	unsigned int LVS:1;		// [9]
	unsigned int reserved2:6;		// [15:10]
	unsigned int DIV:4;		// [19:16]
	unsigned int reserved3:4;		// [23:20]
	unsigned int fixed:2;		// [25:24]
	unsigned int reserved4:2;		// [27:26]
	unsigned int ENBSEL:2;		// [29:28]
	unsigned int reserved5:2;		// [31:30]
};
 // PWM5_FREQ Register
struct PWM_PWM5_FREQ {
	unsigned int FREQ:32;		// [31:0]
};
 // PWM5_DUTY Register
struct PWM_PWM5_DUTY {
	unsigned int DUTY:32;		// [31:0]
};
 // PWM5_ITERATION Register
struct PWM_PWM5_ITERATION {
	unsigned int ITERATION:16;		// [15:0]
	unsigned int reserved:16;		// [31:16]
};
 // PWM5_CURFREQ Register
struct PWM_PWM5_CURFREQ {
	unsigned int CURFREQ:32;		// [31:0]
};
 // PWM5_CURDUTY Register
struct PWM_PWM5_CURDUTY {
	unsigned int INTC0:32;		// [31:0]
};
 // PWM5_CURITER Register
struct PWM_PWM5_CURITER {
	unsigned int CURITER:16;		// [15:0]
	unsigned int CURCYCLE:16;		// [31:16]
};
 // PWM5_COUNT Register
struct PWM_PWM5_COUNT {
	unsigned int COUNT:32;		// [31:0]
};
 // PWM_SYSTEM Register
struct PWM_PWM_SYSTEM {
	unsigned int COUNT:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // PWM_GENB Register
struct PWM_PWM_GENB {
	unsigned int GENB0:1;		// [0]
	unsigned int reserved3:3;		// [3:1]
	unsigned int GENB1:1;		// [4]
	unsigned int reserved2:3;		// [7:5]
	unsigned int GENB2:1;		// [8]
	unsigned int reserved:23;		// [31:9]
};
 // PWM_INTCONFIG Register
struct PWM_PWM_INTCONFIG {
	unsigned int INTMODE0:1;		// [0]
	unsigned int INTMODE1:1;		// [1]
	unsigned int INTMODE2:1;		// [2]
	unsigned int INTMODE3:1;		// [3]
	unsigned int INTMODE4:1;		// [4]
	unsigned int INTMODE5:1;		// [5]
	unsigned int reserved:26;		// [31:6]
};
 // PWM_INTMASK Register
struct PWM_PWM_INTMASK {
	unsigned int INTMASK0:1;		// [0]
	unsigned int INTMASK1:1;		// [1]
	unsigned int INTMASK2:1;		// [2]
	unsigned int INTMASK3:1;		// [3]
	unsigned int INTMASK4:1;		// [4]
	unsigned int INTMASK5:1;		// [5]
	unsigned int reserved2:10;		// [15:6]
	unsigned int ERRMASK0:1;		// [16]
	unsigned int ERRMASK1:1;		// [17]
	unsigned int ERRMASK2:1;		// [18]
	unsigned int ERRMASK3:1;		// [19]
	unsigned int ERRMASK4:1;		// [20]
	unsigned int ERRMASK5:1;		// [21]
	unsigned int reserved:10;		// [31:22]
};
 // PWM_INTSTATUS Register
struct PWM_PWM_INTSTATUS {
	unsigned int INTSTATUS0:1;		// [0]
	unsigned int INTSTATUS1:1;		// [1]
	unsigned int INTSTATUS2:1;		// [2]
	unsigned int INTSTATUS3:1;		// [3]
	unsigned int INTSTATUS4:1;		// [4]
	unsigned int INTSTATUS5:1;		// [5]
	unsigned int reserved2:10;		// [15:6]
	unsigned int ERRSTATUS0:1;		// [16]
	unsigned int ERRSTATUS1:1;		// [17]
	unsigned int ERRSTATUS2:1;		// [18]
	unsigned int ERRSTATUS3:1;		// [19]
	unsigned int ERRSTATUS4:1;		// [20]
	unsigned int ERRSTATUS5:1;		// [21]
	unsigned int reserved:10;		// [31:22]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _PWM_REG_STRUCT_L_H */
