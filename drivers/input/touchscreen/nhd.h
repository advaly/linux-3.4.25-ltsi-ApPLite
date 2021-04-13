/*
 * linux/drivers/input/touchscreen/nhd.h
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

#ifndef __NHD_H__
#define __NHD_H__

#define NHD_DEVICE_MODE			(0x00)
#define NHD_GEST_ID			(0x01)
#define NHD_TD_STATUS			(0x02)
#define NHD_TOUCH1_XH			(0x03)
#define NHD_TOUCH1_XL			(0x04)
#define NHD_TOUCH1_YH			(0x05)
#define NHD_TOUCH1_YL			(0x06)
#define NHD_TOUCH2_XH			(0x09)
#define NHD_TOUCH2_XL			(0x0a)
#define NHD_TOUCH2_YH			(0x0b)
#define NHD_TOUCH2_YL			(0x0c)
#define NHD_TOUCH3_XH			(0x0f)
#define NHD_TOUCH3_XL			(0x10)
#define NHD_TOUCH3_YH			(0x11)
#define NHD_TOUCH3_YL			(0x12)
#define NHD_TOUCH4_XH			(0x15)
#define NHD_TOUCH4_XL			(0x16)
#define NHD_TOUCH4_YH			(0x17)
#define NHD_TOUCH4_YL			(0x18)
#define NHD_TOUCH5_XH			(0x1b)
#define NHD_TOUCH5_XL			(0x1c)
#define NHD_TOUCH5_YH			(0x1d)
#define NHD_TOUCH5_YL			(0x1e)
#define NHD_ID_G_THGROUP		(0x80)
#define NHD_ID_G_THPEAK			(0x81)
#define NHD_ID_G_THCAL			(0x82)
#define NHD_ID_G_THWATER		(0x83)
#define NHD_ID_G_THTEMP			(0x84)
#define NHD_ID_G_THDIFF			(0x85)
#define NHD_ID_G_CTRL			(0x86)
#define NHD_ID_G_TIME_ENTER_MONITOR	(0x87)
#define NHD_ID_G_PERIODACTIVE		(0x88)
#define NHD_ID_G_PERIODMONITOR		(0x89)
#define NHD_ID_G_AUTO_CLB_MODE		(0xa0)
#define NHD_ID_G_LIB_VERSION_H		(0xa1)
#define NHD_ID_G_LIB_VERSION_L		(0xa2)
#define NHD_ID_G_CIPHER			(0xa3)
#define NHD_ID_G_MODE			(0xa4)
#define NHD_ID_G_PMODE			(0xa5)
#define NHD_ID_G_FIRMID			(0xa6)
#define NHD_ID_G_STATE			(0xa7)
#define NHD_ID_G_FT5201ID		(0xa8)
#define NHD_ID_G_ERR			(0xa9)

#define NHD_NORMAL_OPERATION_MODE	(0x00)

#define NHD_MODE_ENABLE			(0x00)
#define NHD_MODE_DISABLE		(0x01)

#define NHD_PMODE_ACTIVE		(0x00)
#define NHD_PMODE_HIBERNATE		(0x03)

#define NHD_STATE_CONFIGURE		(0x00)
#define NHD_STATE_WORK			(0x01)
#define NHD_STATE_CALIBRATION		(0x02)
#define NHD_STATE_FACTORY		(0x03)
#define NHD_STATE_AUTO_CALIBRATION	(0x04)

#define NHD_EVENT_PUT_DOWN		(0x0)
#define NHD_EVENT_PUT_UP		(0x1)
#define NHD_EVENT_CONTACT		(0x2)
#define NHD_EVENT_RESERVED		(0x3)

#define MAX_TOUCH			(5)
#define TOUCH_DATA_SIZE			(6)

#define NHD_CHIP_ID			(0x82)

#define NHD_X_MAX			(480)
#define NHD_Y_MAX			(272)

#define DRIVER_TP			"nhd_tp"

#define	GPIO_44				(44)
#define	GPIO_45				(45)

struct nhd_event_data {
	u8			num_of_touch;
	u32			report_msec;
};

struct nhd_ts_data {
	struct i2c_client	*client;
	struct input_dev	*in_dev;
	u32			irq;
	struct nhd_event_data	data;
};

struct st_touch_data {
	u8	event;
	u8	tid;
	u16	x;
	u16	y;
};

#endif
