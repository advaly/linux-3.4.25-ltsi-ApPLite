/*
 * arch/arm/mach-tz2000/include/mach/regs/rtc_offs_def.h
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

#ifndef RTC_OFFS_DEF_H
#define RTC_OFFS_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

#define RTC_RTC_TIMESET1_OFFS          0x00000000
#define RTC_RTC_TIMESET2_OFFS          0x00000004
#define RTC_RTC_TIMESET3_OFFS          0x00000008
#define RTC_RTC_TIMESET4_OFFS          0x0000000C
#define RTC_RTC_CTRL_OFFS              0x00000010
#define RTC_RTC_RIS_OFFS               0x00000020
#define RTC_RTC_MIS_OFFS               0x00000024
#define RTC_RTC_INTMASK_OFFS           0x00000028
#define RTC_RTC_PERIODIC_OFFS          0x0000002C
#define RTC_RTC_PERIOD_INTCLR_OFFS     0x00000030
#define RTC_RTC_ALARM_INTCLR_OFFS      0x00000034
#define RTC_RTC_CURRENT1_OFFS          0x00000040
#define RTC_RTC_CURRENT2_OFFS          0x00000044
#define RTC_RTC_CURRENT3_OFFS          0x00000048
#define RTC_RTC_CURRENT4_OFFS          0x0000004C
#define RTC_RTC_ALARM1_OFFS            0x00000050
#define RTC_RTC_ALARM2_OFFS            0x00000054
#define RTC_RTC_ALARM3_OFFS            0x00000058
#define RTC_RTC_TESTMODE_OFFS          0x00000F00
#define RTC_RTC_TESTINT_OFFS           0x00000F04
#define RTC_RTC_TESTCLK_OFFS           0x00000F08
#define RTC_RTC_TESTCLKLD_OFFS         0x00000F0C
#define RTC_RTC_CellID0_OFFS           0x00000FF0
#define RTC_RTC_CellID1_OFFS           0x00000FF4
#define RTC_RTC_CellID2_OFFS           0x00000FF8
#define RTC_RTC_CellID3_OFFS           0x00000FFC

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RTC_OFFS_DEF_H */
