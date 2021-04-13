/*
 * linux/drivers/input/touchscreen/fusion.h
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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef __FUSION__H__
#define __FUSION__H__

#define FUSION_DATA_INFO			(0x00)
#define FUSION_Y1_POS_HI			(0x01)
#define FUSION_Y1_POS_LO			(0x02)
#define FUSION_X1_POS_HI			(0x03)
#define FUSION_X1_POS_LO			(0x04)
#define FUSION_FIRST_TOUCH_POINT_PRESS		(0x05)
#define FUSION_FIRST_TOUCHID_TIPSWITCH		(0x06)
#define FUSION_Y2_POS_HI			(0x07)
#define FUSION_Y2_POS_LO			(0x08)
#define FUSION_X2_POS_HI			(0x09)
#define FUSION_X2_POS_LO			(0x0a)
#define FUSION_SECOND_TOUCH_POINT_PRESS		(0x0b)
#define FUSION_SECOND_TOUCHID_TIPSWITCH		(0x0c)
#define FUSION_FIRM_VERSION1			(0x0e)
#define FUSION_FIRM_VERSION2			(0x0f)
#define FUSION_RESET_CONTROL			(0x10)
#define FUSION_SCAN_COMPLETE			(0x11)
#define FUSION_FIRM_UPDATE_CONTROL		(0x14)

#define FUSION_PRODUCT_INFO_7			(0x01)

#define FUSION_7_XMAX				(1500)
#define FUSION_7_YMAX				(900)

#define	FUSION_7_SAVE_PT1			(0x1)
#define	FUSION_7_SAVE_PT2			(0x2)

#define DRIVER_TP				"fusion7_tp"

#define	GPIO_44					(44)
#define	GPIO_45					(45)

#define PIXEL_XMAX				(800)
#define PIXEL_YMAX				(480)

#define MAX_TOUCH				(2)

struct fusion_f07a_0102_event_data {
	u8				tip1;
	u8				tip2;
	u32				report_msec;
};

struct fusion_f07a_0102_data {
	struct i2c_client		*client;
	struct input_dev		*input;
	u16				x1;
	u16				y1;
	u8				z1;
	u8				tip1;
	u8				tid1;
	u16				x2;
	u16				y2;
	u8				z2;
	u8				tip2;
	u8				tid2;
	u32				irq;
	struct fusion_f07a_0102_event_data data;
};

#endif
