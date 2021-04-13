/*
 * arch/arm/mach-tz2000/include/mach/regs/rtc_reg_struct_l.h
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

#ifndef _RTC_REG_STRUCT_L_H
#define _RTC_REG_STRUCT_L_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // RTC_TIMESET1 Register
struct RTC_RTC_TIMESET1 {
	unsigned int SECSET_UNDER10:4;		// [3:0]
	unsigned int SECSET_OVER10:3;		// [6:4]
	unsigned int reserved2:1;		// [7]
	unsigned int MINSET_UNDER10:4;		// [11:8]
	unsigned int MINSET_OVER10:3;		// [14:12]
	unsigned int reserved:17;		// [31:15]
};
 // RTC_TIMESET2 Register
struct RTC_RTC_TIMESET2 {
	unsigned int HOURSET_UNDER10:4;		// [3:0]
	unsigned int HOURSET_OVER10:2;		// [5:4]
	unsigned int reserved2:2;		// [7:6]
	unsigned int DAYSET_UNDER10:4;		// [11:8]
	unsigned int DAYSET_OVER10:2;		// [13:12]
	unsigned int reserved:18;		// [31:14]
};
 // RTC_TIMESET3 Register
struct RTC_RTC_TIMESET3 {
	unsigned int MONTHSET_UNDER10:4;		// [3:0]
	unsigned int MONTHSET_OVER10:1;		// [4]
	unsigned int WEEKSET:3;		// [7:5]
	unsigned int YEARSET_UNDER10:4;		// [11:8]
	unsigned int YEARSET_OVER10:4;		// [15:12]
	unsigned int reserved:16;		// [31:16]
};
 // RTC_TIMESET4 Register
struct RTC_RTC_TIMESET4 {
	unsigned int LEAP:2;		// [1:0]
	unsigned int reserved:30;		// [31:2]
};
 // RTC_CTRL Register
struct RTC_RTC_CTRL {
	unsigned int ALRST:1;		// [0]
	unsigned int ALEN:1;		// [1]
	unsigned int PRRST:1;		// [2]
	unsigned int PREN:1;		// [3]
	unsigned int ADJUST:1;		// [4]
	unsigned int HR24_12:1;		// [5]
	unsigned int TMRST:1;		// [6]
	unsigned int TMEN:1;		// [7]
	unsigned int reserved:24;		// [31:8]
};
 // RTC_RIS Register
struct RTC_RTC_RIS {
	unsigned int ALARM_INTRAWST:1;		// [0]
	unsigned int PERIOD_INTRAWST:1;		// [1]
	unsigned int reserved:30;		// [31:2]
};
 // RTC_MIS Register
struct RTC_RTC_MIS {
	unsigned int ALARM_INTMASKST:1;		// [0]
	unsigned int PERIOD_INTMASKST:1;		// [1]
	unsigned int reserved:30;		// [31:2]
};
 // RTC_INTMASK Register
struct RTC_RTC_INTMASK {
	unsigned int ALARM_INTMASK:1;		// [0]
	unsigned int PERIOD_INTMASK:1;		// [1]
	unsigned int reserved:30;		// [31:2]
};
 // RTC_PERIODIC Register
struct RTC_RTC_PERIODIC {
	unsigned int PERIODIC_INTSET:3;		// [2:0]
	unsigned int reserved:29;		// [31:3]
};
 // RTC_PERIOD_INTCLR Register
struct RTC_RTC_PERIOD_INTCLR {
	unsigned int PERIOD_INTCLR:32;		// [31:0]
};
 // RTC_ALARM_INTCLR Register
struct RTC_RTC_ALARM_INTCLR {
	unsigned int ALARM_INTCLR:32;		// [31:0]
};
 // RTC_CURRENT1 Register
struct RTC_RTC_CURRENT1 {
	unsigned int SECVAL_UNDER10:4;		// [3:0]
	unsigned int SECVAL_OVER10:3;		// [6:4]
	unsigned int reserved2:1;		// [7]
	unsigned int MINVAL_UNDER10:4;		// [11:8]
	unsigned int MINVAL_OVER10:3;		// [14:12]
	unsigned int reserved:17;		// [31:15]
};
 // RTC_CURRENT2 Register
struct RTC_RTC_CURRENT2 {
	unsigned int HOURVAL_UNDER10:4;		// [3:0]
	unsigned int HOURVAL_OVER10:2;		// [5:4]
	unsigned int reserved2:2;		// [7:6]
	unsigned int DAYVAL_UNDER10:4;		// [11:8]
	unsigned int DAYVAL_OVER10:2;		// [13:12]
	unsigned int reserved:18;		// [31:14]
};
 // RTC_CURRENT3 Register
struct RTC_RTC_CURRENT3 {
	unsigned int MONTHVAL_UNDER10:4;		// [3:0]
	unsigned int MONTHVAL_OVER10:1;		// [4]
	unsigned int WEEKVAL:3;		// [7:5]
	unsigned int YEARVAL_UNDER10:4;		// [11:8]
	unsigned int YEARVAL_OVER10:4;		// [15:12]
	unsigned int reserved:16;		// [31:16]
};
 // RTC_CURRENT4 Register
struct RTC_RTC_CURRENT4 {
	unsigned int LEAP:2;		// [1:0]
	unsigned int reserved:30;		// [31:2]
};
 // RTC_ALARM1 Register
struct RTC_RTC_ALARM1 {
	unsigned int reserved2:8;		// [7:0]
	unsigned int AL_MINSET_UNDER10:4;		// [11:8]
	unsigned int AL_MINSET_OVER10:3;		// [14:12]
	unsigned int reserved:17;		// [31:15]
};
 // RTC_ALARM2 Register
struct RTC_RTC_ALARM2 {
	unsigned int AL_HOURSET_UNDER10:4;		// [3:0]
	unsigned int AL_HOURSET_OVER10:2;		// [5:4]
	unsigned int reserved2:2;		// [7:6]
	unsigned int AL_DAYSET_UNDER10:4;		// [11:8]
	unsigned int AL_DAYSET_OVER10:2;		// [13:12]
	unsigned int reserved:18;		// [31:14]
};
 // RTC_ALARM3 Register
struct RTC_RTC_ALARM3 {
	unsigned int reserved2:5;		// [4:0]
	unsigned int AL_WEEKSET:3;		// [7:5]
	unsigned int reserved:24;		// [31:8]
};
 // RTC_TESTMODE Register
struct RTC_RTC_TESTMODE {
	unsigned int TESTSET:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // RTC_TESTINT Register
struct RTC_RTC_TESTINT {
	unsigned int TESTINT_ALARM:1;		// [0]
	unsigned int TESTINT_PERIOD:1;		// [1]
	unsigned int reserved:30;		// [31:2]
};
 // RTC_TESTCLK Register
struct RTC_RTC_TESTCLK {
	unsigned int SEC_ACC:1;		// [0]
	unsigned int MIN_ACC:1;		// [1]
	unsigned int HOUR_ACC:1;		// [2]
	unsigned int DAY_ACC:1;		// [3]
	unsigned int MON_ACC:1;		// [4]
	unsigned int YEAR_ACC:1;		// [5]
	unsigned int reserved:26;		// [31:6]
};
 // RTC_TESTCLKLD Register
struct RTC_RTC_TESTCLKLD {
	unsigned int TESTCLKLD:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // RTC_CellID0 Register
struct RTC_RTC_CELLID0 {
	unsigned int RTC_CellID0:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // RTC_CellID1 Register
struct RTC_RTC_CELLID1 {
	unsigned int RTC_CellID1:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // RTC_CellID2 Register
struct RTC_RTC_CELLID2 {
	unsigned int RTC_CellID2:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // RTC_CellID3 Register
struct RTC_RTC_CELLID3 {
	unsigned int RTC_CellID3:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _RTC_REG_STRUCT_L_H */
