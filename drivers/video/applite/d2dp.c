/*
 * linux/drivers/video/applite/d2dp.c
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
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/fb.h>
#include <linux/init.h>
#include <linux/pci.h>

#include <linux/videodev2.h>
#include <mach/regs/pmu_offs_def.h>
#include <mach/regs/dispif_offs_def.h>
#include <linux/uaccess.h>
#include <linux/i2c.h>
#include <linux/gpio.h>

#include "applitefb.h"
#include "d2dp.h"

static DEFINE_MUTEX(d2dp_lock);

/*Setting Table*/
static struct reg_param_d2dp d2dp_reg_param[4][20] = {
	{/* 720x480 */
		{ PXL_PLLPARAM_OFFS,	0x0022051c },
		{ PPI_TX_RX_TA_OFFS,	0x00020003 },
		{ PPI_LPTXTIMECNT_OFFS, 0x00000002 },
		{ CLRSIPOCOUNT0_OFFS,	0x00000002 },
		{ CLRSIPOCOUNT1_OFFS,	0x00000002 },
		{ CLRSIPOCOUNT2_OFFS,	0x00000002 },
		{ CLRSIPOCOUNT3_OFFS,	0x00000002 },
		{ PPI_LANEENABLE_OFFS,	0x00000007 },
		{ DSI_LANEENABLE_OFFS,	0x00000007 },
		{ VPCTRL0_OFFS,		0x01e00100 },
		{ HTIM01_OFFS,		0x003c003e },
		{ VTIM01_OFFS,		0x001e0006 },
		{ VFUEN0_OFFS,		0x00000001 },
		{ DP0_VIDSYNCDLY_OFFS,	0x002f034a },
		{ DP0_TOTALVAL_OFFS,	0x020d0355 },
		{ DP0_STARTVAL_OFFS,	0x0024007a },
		{ DP0_ACTIVEVAL_OFFS,	0x01e002d0 },
		{ DP0_SYNCVAL_OFFS,	0x8006803e },
		{ DP0_VID_FM_OFFS,	0x00000070 },
		{ DP0_VID_N_OFFS,	0x00000465 }
	},
	{/* 1280x720 */
		{ PXL_PLLPARAM_OFFS,	0x00320346 },
		{ PPI_TX_RX_TA_OFFS,	0x00050006 },
		{ PPI_LPTXTIMECNT_OFFS, 0x00000004 },
		{ CLRSIPOCOUNT0_OFFS,	0x00000004 },
		{ CLRSIPOCOUNT1_OFFS,	0x00000004 },
		{ CLRSIPOCOUNT2_OFFS,	0x00000004 },
		{ CLRSIPOCOUNT3_OFFS,	0x0000004 },
		{ PPI_LANEENABLE_OFFS,	0x0000000f },
		{ DSI_LANEENABLE_OFFS,	0x0000000f },
		{ VPCTRL0_OFFS,		0x1c200100 },
		{ HTIM01_OFFS,		0x00dc0028 },
		{ VTIM01_OFFS,		0x00140005 },
		{ VFUEN0_OFFS,		0x00000001 },
		{ DP0_VIDSYNCDLY_OFFS,	0x002f0604 },
		{ DP0_TOTALVAL_OFFS,	0x02ee07c7 },
		{ DP0_STARTVAL_OFFS,	0x00190104 },
		{ DP0_ACTIVEVAL_OFFS,	0x02d00500 },
		{ DP0_SYNCVAL_OFFS,	0x80058028 },
		{ DP0_VID_FM_OFFS,	0x00000070 },
		{ DP0_VID_N_OFFS,	0x00000195 }
	},
	{/* 1920x1080@30P */
		{ PXL_PLLPARAM_OFFS,	0x0032045d },
		{ PPI_TX_RX_TA_OFFS,	0x00030005 },
		{ PPI_LPTXTIMECNT_OFFS, 0x00000003 },
		{ CLRSIPOCOUNT0_OFFS,	0x00000002 },
		{ CLRSIPOCOUNT1_OFFS,	0x00000002 },
		{ CLRSIPOCOUNT2_OFFS,	0x00000002 },
		{ CLRSIPOCOUNT3_OFFS,	0x00000002 },
		{ PPI_LANEENABLE_OFFS,	0x0000001f },
		{ DSI_LANEENABLE_OFFS,	0x0000001f },
		{ VPCTRL0_OFFS,		0x05800100 },
		{ HTIM01_OFFS,		0x0094002c },
		{ VTIM01_OFFS,		0x00240005 },
		{ VFUEN0_OFFS,		0x00000001 },
		{ DP0_VIDSYNCDLY_OFFS,	0x002f0840 },
		{ DP0_TOTALVAL_OFFS,	0x04650898 },
		{ DP0_STARTVAL_OFFS,	0x002900c0 },
		{ DP0_ACTIVEVAL_OFFS,	0x04380780 },
		{ DP0_SYNCVAL_OFFS,	0x8005802c },
		{ DP0_VID_FM_OFFS,	0x0000003e },
		{ DP0_VID_N_OFFS,	0x000000e1 }
	},
	{/* 1920x1080@60P */
		{ PXL_PLLPARAM_OFFS,	0x0032025d },
		{ PPI_TX_RX_TA_OFFS,	0x0008000b },
		{ PPI_LPTXTIMECNT_OFFS, 0x00000008 },
		{ CLRSIPOCOUNT0_OFFS,	0x00000008 },
		{ CLRSIPOCOUNT1_OFFS,	0x00000008 },
		{ CLRSIPOCOUNT2_OFFS,	0x00000008 },
		{ CLRSIPOCOUNT3_OFFS,	0x00000008 },
		{ PPI_LANEENABLE_OFFS,	0x0000001f },
		{ DSI_LANEENABLE_OFFS,	0x0000001f },
		{ VPCTRL0_OFFS,		0x05800100 },
		{ HTIM01_OFFS,		0x0094002c },
		{ VTIM01_OFFS,		0x00240005 },
		{ VFUEN0_OFFS,		0x00000001 },
		{ DP0_VIDSYNCDLY_OFFS,	0x002f0840 },
		{ DP0_TOTALVAL_OFFS,	0x04650898 },
		{ DP0_STARTVAL_OFFS,	0x002900c0 },
		{ DP0_ACTIVEVAL_OFFS,	0x04380780 },
		{ DP0_SYNCVAL_OFFS,	0x8005802c },
		{ DP0_VID_FM_OFFS,	0x0000007c },
		{ DP0_VID_N_OFFS,	0x000000e1 }
	}
};

enum regist {
	PXL_PLLPARAM,
	PPI_TX_RX_TA,
	PPI_LPTXTIMECNT,
	CLRSIPOCOUNT0,
	CLRSIPOCOUNT1,
	CLRSIPOCOUNT2,
	CLRSIPOCOUNT3,
	PPI_LANEENABLE,
	DSI_LANEENABLE,
	VPCTRL0,
	HTIM01,
	VTIM01,
	VFUEN0,
	DP0_VIDSYNCDLY,
	DP0_TOTALVAL,
	DP0_STARTVAL,
	DP0_ACTIVEVAL,
	DP0_SYNCVAL,
	DP0_VID_FM,
	DP0_VID_N
};


static inline void d2dp_i2c_read(struct i2c_adapter *adapter,
			 u16 addr, u16 count, u8 *buf)
{
	int ret, retries;
	u8 msg_buf[2];
	struct i2c_msg msgs[] = {
		{
			.addr   = D2DP_I2C_ADDR,
			.flags  = 0,
			.len    = 2,
			.buf    = (u8 *)&msg_buf[0],
		}, {
			.addr   = D2DP_I2C_ADDR,
			.flags  = I2C_M_RD,
			.len    = count,
			.buf    = (u8 *)buf,
		}
	};

	u8 *paddr = (u8 *)&addr;

	_D2DP_FNC_START("\n");

	msg_buf[0] = paddr[1];
	msg_buf[1] = paddr[0];

	for (retries = 3; retries > 0; retries--) {
		ret = i2c_transfer(adapter, msgs, 2);
		if (ret == 2) {
			_D2DP_DBG_LOG("i2c_transfer() success[rtn=%d]\n", ret);
			_D2DP_FNC_END("\n");
			return;
		}

		if (ret != -EAGAIN) {
			_ERR_LOG("i2c_transfer() failed[rtn=%d]\n", ret);
			break;
		}
	}

	if (ret != 2) {
		_ERR_LOG("i2c_transfer addr=0x%04x read error %d\n", addr, ret);
		_D2DP_FNC_END("\n");
		return;
	}
	_D2DP_FNC_END("\n");
}

static inline void d2dp_i2c_write32(struct i2c_adapter *adapter,
			    u16 addr, u32 val)
{
	int ret, retries;
	unsigned int ii;
	u8 msg_buf[2 + sizeof(u32)];
	struct i2c_msg msgs[] = {
		{
			.addr   = D2DP_I2C_ADDR,
			.flags  = 0,
			.len    = 2 + sizeof(u32),
			.buf    = (u8 *)&msg_buf[0],
		}
	};

	u8 *paddr = (u8 *)&addr;
	u8 *pbuf = (u8 *)&val;

	_D2DP_FNC_START("addr[%04x], val[%08x]\n", addr, val);

	msg_buf[0] = paddr[1];
	msg_buf[1] = paddr[0];
	for (ii = 0; ii < sizeof(u32); ii++)
		msg_buf[2 + ii] = pbuf[ii];

	for (retries = 3; retries > 0; retries--) {
		ret = i2c_transfer(adapter, msgs, 1);
		if (ret == 1) {
			_D2DP_FNC_END("success\n");
			return;
		}

		if (ret != -EAGAIN) {
			_ERR_LOG("i2c_transfer() failed[rtn=%d]\n", ret);
			break;
		}
	}
	if (ret != 1) {
		_ERR_LOG("i2c_transfer addr=0x%04x write error %d\n", addr, ret);
		_D2DP_FNC_END("\n");
		return;
	}
	_D2DP_FNC_END("\n");

}

static void
applitefb_d2dp_reg_write(struct i2c_adapter *adapter, u32 mode, u32 regist)
{
	d2dp_i2c_write32(adapter,
		d2dp_reg_param[mode][regist].reg_offset,
		d2dp_reg_param[mode][regist].val);
	return;
}


void d2dp_reset(void)
{
	int val;

	_D2DP_FNC_START("\n");

	mutex_lock(&d2dp_lock);

	val = gpio_get_value(3);
	_D2DP_DBG_LOG("gpio3=%s : D2DP %sreset\n",
		(val == 0 ? "low" : "high"), (val == 0 ? "" : "un"));
	if (val > 0) {
		_D2DP_DBG_LOG(" set 0 to gpio\n");
		gpio_set_value(3, 0);
		mdelay(10);
		val = gpio_get_value(3);
		_D2DP_DBG_LOG("gpio3=%s : D2DP %sreset\n",
			(val == 0 ? "low" : "high"), (val == 0 ? "" : "un"));
	}
	_D2DP_DBG_LOG("set 1 to gpio\n");
	gpio_set_value(3, 1);
	mdelay(10);
	val = gpio_get_value(3);
	_D2DP_DBG_LOG("gpio3=%s : D2DP %sreset\n",
		(val == 0 ? "low" : "high"), (val == 0 ? "" : "un"));

	mdelay(10);

	mutex_unlock(&d2dp_lock);

	_D2DP_FNC_END("\n");
}

int d2dp_init(u32 mode)
{
	struct i2c_adapter *adapter;
	u32 val;
	u32 count;
	u32 dp_lane = 0;

	_D2DP_FNC_START("mode[%d]\n", mode);

	switch ((mode+1)) {
	case 1:
		_D2DP_DBG_LOG("dp_lane is 1\n");
		dp_lane = 1;
		break;
	case 2:
	case 3:
	case 4:
		_D2DP_DBG_LOG("dp_lane is 2\n");
		dp_lane = 2;
		break;
	}

	mutex_lock(&d2dp_lock);

	adapter = i2c_get_adapter(D2DP_I2C_BUS);
	if (!adapter) {
		_ERR_LOG("Failed to get I2C adapter, bus %d\n", 2);
		goto err;
	}

	d2dp_i2c_read(adapter, IDREG_OFFS, sizeof(u32), (u8 *)&val);
	mdelay(10);

	if (dp_lane == 1)
		d2dp_i2c_write32(adapter, DP0_SRCCTRL_OFFS, 0x00003082);
	else if (dp_lane == 2)
		d2dp_i2c_write32(adapter, DP0_SRCCTRL_OFFS, 0x00003086);

	d2dp_i2c_write32(adapter, DP1_SRCCTRL_OFFS, 0x00000002);
	d2dp_i2c_write32(adapter, SYS_PLLPARAM_OFFS, 0x00000101);
	mdelay(10);

	if (dp_lane == 1)
		d2dp_i2c_write32(adapter, DP_PHY_CTRL_OFFS, 0x03000003);
	else if (dp_lane == 2)
		d2dp_i2c_write32(adapter, DP_PHY_CTRL_OFFS, 0x03000007);

	d2dp_i2c_write32(adapter, DP0_PLLCTRL_OFFS, 0x00000005);
	mdelay(10);

	d2dp_i2c_write32(adapter, DP1_PLLCTRL_OFFS, 0x00000005);
	applitefb_d2dp_reg_write(adapter, mode, PXL_PLLPARAM);
	d2dp_i2c_write32(adapter, PXL_PLLCTRL_OFFS, 0x00000005);
	mdelay(10);

	count = 0;
	if (dp_lane == 1) {
		_D2DP_DBG_LOG("setting of dp_lane1\n");
		d2dp_i2c_write32(adapter, DP_PHY_CTRL_OFFS, 0x13001103);
		d2dp_i2c_write32(adapter, DP_PHY_CTRL_OFFS, 0x03000003);

		mdelay(10);
		do {
			d2dp_i2c_read(adapter,
				DP_PHY_CTRL_OFFS, sizeof(u32), (u8 *)&val);
			count++;
			mdelay(5);
		} while ((val != 0x03010003) && (count < 5));
	} else if (dp_lane == 2) {
		_D2DP_DBG_LOG("setting of dp_lane2\n");
		d2dp_i2c_write32(adapter, DP_PHY_CTRL_OFFS, 0x13001107);
		d2dp_i2c_write32(adapter, DP_PHY_CTRL_OFFS, 0x03000007);
		mdelay(10);

		do {
			d2dp_i2c_read(adapter,
				DP_PHY_CTRL_OFFS, sizeof(u32), (u8 *)&val);
			count++;
			mdelay(5);
		} while ((val != 0x03010007) && (count < 5));
	}
	_D2DP_DBG_LOG("d2dp addr=0x%04x 0x%08x count=%d\n",
					DP_PHY_CTRL_OFFS, val, count);
	d2dp_i2c_write32(adapter, DP0_AUXCFG1_OFFS, 0x0001063f);
	d2dp_i2c_write32(adapter, DP0_AUXADDR_OFFS, 0x00000001);
	d2dp_i2c_write32(adapter, DP0_AUXCFG0_OFFS, 0x00000009);
	mdelay(10);

	count = 0;
	do {
		d2dp_i2c_read(adapter,
			DP0_AUXSTATUS_OFFS, sizeof(u32), (u8 *)&val);
		count++;
		mdelay(5);
	} while ((val & 0x00000003) && (count < 5));
	_D2DP_DBG_LOG("d2dp addr=0x%04x 0x%08x count=%d\n",
					DP0_AUXSTATUS_OFFS, val, count);
	d2dp_i2c_read(adapter, DP0_AUXRDATA0_OFFS, sizeof(u32), (u8 *)&val);
	_D2DP_DBG_LOG("d2dp addr=0x%04x 0x%08x\n", DP0_AUXRDATA0_OFFS, val);
	mdelay(10);

	d2dp_i2c_write32(adapter, DP0_AUXADDR_OFFS, 0x00000002);
	d2dp_i2c_write32(adapter, DP0_AUXCFG0_OFFS, 0x00000009);
	mdelay(10);

	count = 0;
	do {
		d2dp_i2c_read(adapter,
			DP0_AUXSTATUS_OFFS, sizeof(u32), (u8 *)&val);
		count++;
		mdelay(5);
	} while ((val & 0x00000003) && count < 5);
	_D2DP_DBG_LOG("d2dp addr=0x%04x 0x%08x count=%d\n",
					DP0_AUXSTATUS_OFFS, val, count);
	mdelay(10);

	d2dp_i2c_read(adapter,
		DP0_AUXRDATA0_OFFS, sizeof(u32), (u8 *)&val);
	_D2DP_DBG_LOG("d2dp addr=0x%04x 0x%08x\n", DP0_AUXRDATA0_OFFS, val);
	mdelay(10);

	d2dp_i2c_write32(adapter, DP0_AUXADDR_OFFS, 0x00000100);
	if (dp_lane == 1)
		d2dp_i2c_write32(adapter, AUXWDATA0_OFFS, 0x0000010a);
	else if (dp_lane == 2)
		d2dp_i2c_write32(adapter, AUXWDATA0_OFFS, 0x0000020a);

	d2dp_i2c_write32(adapter, DP0_AUXCFG0_OFFS, 0x00000108);
	d2dp_i2c_write32(adapter, DP0_AUXADDR_OFFS, 0x00000108);
	d2dp_i2c_write32(adapter, AUXWDATA0_OFFS, 0x00000001);
	d2dp_i2c_write32(adapter, DP0_AUXCFG0_OFFS, 0x00000008);
	mdelay(10);

	d2dp_i2c_write32(adapter, DP0_SNKLTCTRL_OFFS, 0x00000021);
	d2dp_i2c_write32(adapter, DP0_LTLOOPCTRL_OFFS, 0xf600000d);
	mdelay(10);

	if (dp_lane == 1)
		d2dp_i2c_write32(adapter, DP0_SRCCTRL_OFFS, 0x00003183);
	else if (dp_lane == 2)
		d2dp_i2c_write32(adapter, DP0_SRCCTRL_OFFS, 0x00003187);
	mdelay(10);

	d2dp_i2c_write32(adapter, DP0CTL_OFFS, 0x00000001);
	mdelay(10);

	d2dp_i2c_read(adapter, DP0_LTSTAT_OFFS, sizeof(u32), (u8 *)&val);
	_D2DP_DBG_LOG("d2dp addr=0x%04x 0x%08x\n", DP0_LTSTAT_OFFS, val);
	mdelay(10);

	d2dp_i2c_write32(adapter, DP0_SNKLTCTRL_OFFS, 0x00000022);
	mdelay(10);

	if (dp_lane == 1)
		d2dp_i2c_write32(adapter, DP0_SRCCTRL_OFFS, 0x00003283);
	else if (dp_lane == 2)
		d2dp_i2c_write32(adapter, DP0_SRCCTRL_OFFS, 0x00003287);
	mdelay(10);

	d2dp_i2c_read(adapter, DP0_LTSTAT_OFFS, sizeof(u32), (u8 *)&val);
	_D2DP_DBG_LOG("d2dp addr=0x%04x 0x%08x\n", DP0_LTSTAT_OFFS, val);
	mdelay(10);

	d2dp_i2c_write32(adapter, DP0_AUXADDR_OFFS, 0x00000102);
	d2dp_i2c_write32(adapter, AUXWDATA0_OFFS, 0x00000000);
	d2dp_i2c_write32(adapter, DP0_AUXCFG0_OFFS, 0x00000008);
	mdelay(10);

	if (dp_lane == 1)
		d2dp_i2c_write32(adapter, DP0_SRCCTRL_OFFS, 0x00001083);
	else if (dp_lane == 2)
		d2dp_i2c_write32(adapter, DP0_SRCCTRL_OFFS, 0x00001087);
	mdelay(10);

	d2dp_i2c_write32(adapter, DP0_AUXADDR_OFFS, 0x00000200);
	d2dp_i2c_write32(adapter, DP0_AUXCFG0_OFFS, 0x00000409);
	mdelay(10);

	count = 0;
	do {
		d2dp_i2c_read(adapter,
			DP0_AUXSTATUS_OFFS, sizeof(u32), (u8 *)&val);
		count++;
		mdelay(5);
	} while ((val & 0x00000003) && count < 5);
	_D2DP_DBG_LOG("d2dp addr=0x%04x 0x%08x count=%d\n",
					DP0_AUXSTATUS_OFFS, val, count);
	d2dp_i2c_read(adapter, DP0_AUXRDATA0_OFFS, sizeof(u32), (u8 *)&val);
	_D2DP_DBG_LOG("d2dp addr=0x%04x 0x%08x\n", DP0_AUXRDATA0_OFFS, val);
	d2dp_i2c_read(adapter, DP0_AUXRDATA1_OFFS, sizeof(u32), (u8 *)&val);
	_D2DP_DBG_LOG("d2dp addr=0x%04x 0x%08x\n", DP0_AUXRDATA1_OFFS, val);
	mdelay(10);

	applitefb_d2dp_reg_write(adapter, mode, PPI_TX_RX_TA);
	applitefb_d2dp_reg_write(adapter, mode, PPI_LPTXTIMECNT);
	applitefb_d2dp_reg_write(adapter, mode, CLRSIPOCOUNT0);
	applitefb_d2dp_reg_write(adapter, mode, CLRSIPOCOUNT1);
	applitefb_d2dp_reg_write(adapter, mode, CLRSIPOCOUNT2);
	applitefb_d2dp_reg_write(adapter, mode, CLRSIPOCOUNT3);
	applitefb_d2dp_reg_write(adapter, mode, PPI_LANEENABLE);
	applitefb_d2dp_reg_write(adapter, mode, DSI_LANEENABLE);

	d2dp_i2c_write32(adapter, PPI_STARTPPI_OFFS, 0x00000001);
	d2dp_i2c_write32(adapter, DSI_STARTDSI_OFFS, 0x00000001);
	mdelay(10);

	applitefb_d2dp_reg_write(adapter, mode, VPCTRL0);
	applitefb_d2dp_reg_write(adapter, mode, HTIM01);
	applitefb_d2dp_reg_write(adapter, mode, VTIM01);
	applitefb_d2dp_reg_write(adapter, mode, VFUEN0);
	mdelay(10);

	applitefb_d2dp_reg_write(adapter, mode, DP0_VIDSYNCDLY);
	applitefb_d2dp_reg_write(adapter, mode, DP0_TOTALVAL);
	applitefb_d2dp_reg_write(adapter, mode, DP0_STARTVAL);
	applitefb_d2dp_reg_write(adapter, mode, DP0_ACTIVEVAL);
	applitefb_d2dp_reg_write(adapter, mode, DP0_SYNCVAL);
	mdelay(10);

	d2dp_i2c_write32(adapter, DP0_MISC_OFFS, 0x1f3f0020);
	mdelay(10);

	applitefb_d2dp_reg_write(adapter, mode, DP0_VID_FM);
	applitefb_d2dp_reg_write(adapter, mode, DP0_VID_N);
	mdelay(10);

	d2dp_i2c_write32(adapter, DP0CTL_OFFS, 0x00000041);
	d2dp_i2c_write32(adapter, DP0CTL_OFFS, 0x00000043);
	mdelay(10);

	d2dp_i2c_write32(adapter, SYSCTRL_OFFS, 0x00000001);
	mdelay(10);

	d2dp_i2c_read(adapter, DP0_VID_FM_OFFS, sizeof(u32), (u8 *)&val);
	_D2DP_DBG_LOG("d2dp addr=0x%04x 0x%08x\n", DP0_VID_FM_OFFS, val);
	d2dp_i2c_read(adapter, DP0_VID_N_OFFS, sizeof(u32), (u8 *)&val);
	_D2DP_DBG_LOG("d2dp addr=0x%04x 0x%08x\n", DP0_VID_N_OFFS, val);
	d2dp_i2c_read(adapter, DP0_VID_M_OFFS, sizeof(u32), (u8 *)&val);
	_D2DP_DBG_LOG("d2dp addr=0x%04x 0x%08x\n", DP0_VID_M_OFFS, val);
	mdelay(10);

	d2dp_i2c_read(adapter, SYSSTAT_OFFS, sizeof(u32), (u8 *)&val);
	_D2DP_DBG_LOG("d2dp addr=0x%04x 0x%08x\n", SYSSTAT_OFFS, val);
	mdelay(10);

	d2dp_i2c_read(adapter, DSI_INTSTATUS_OFFS, sizeof(u32), (u8 *)&val);
	_D2DP_DBG_LOG("d2dp addr=0x%04x 0x%08x\n", DSI_INTSTATUS_OFFS, val);
	mdelay(10);

	d2dp_i2c_write32(adapter, PARALLEL_OUT_OFFS, 0x00000080);

	mutex_unlock(&d2dp_lock);

	_D2DP_FNC_END("\n");
	return 0;

err:
	mutex_unlock(&d2dp_lock);

	return -EINVAL;
}
