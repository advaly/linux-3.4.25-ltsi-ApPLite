/*
 * linux/drivers/input/touchscreen/fusion.c
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

#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/input/mt.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <asm/mach-types.h>
#include <mach/hardware.h>
#include <mach/platform.h>
#include <mach/irqs.h>
#include "fusion.h"


static ulong interval = 16;
module_param(interval, ulong, 0644);
MODULE_PARM_DESC(interval, "Interval of input event (msec)");

static struct fusion_f07a_0102_data fusion_f07a_0102;

static int fusion_f07a_0102_write_u8(u8 addr, u8 data)
{
	return i2c_smbus_write_byte_data(fusion_f07a_0102.client, addr, data);
}

static int fusion_f07a_0102_read_u8(u8 addr)
{
	return i2c_smbus_read_byte_data(fusion_f07a_0102.client, addr);
}

static int fusion_f07a_0102_read_block(u8 addr, u8 len, u8 *data)
{
	u8 msgbuf0[1] = { addr };
	u16 slave = fusion_f07a_0102.client->addr;
	u16 flags = fusion_f07a_0102.client->flags;
	struct i2c_msg msg[2] = { { slave, flags, 1, msgbuf0 },
				  { slave, flags | I2C_M_RD, len, data } };

	return i2c_transfer(fusion_f07a_0102.client->adapter, msg, ARRAY_SIZE(msg));
}

static int fusion_f07a_0102_register_input(void)
{
	int ret;
	struct input_dev *dev;

	dev = fusion_f07a_0102.input = input_allocate_device();
	if (dev == NULL)
		return -ENOMEM;

	dev->name = DRIVER_TP;
	dev->id.bustype = BUS_I2C;
	dev->dev.parent = &fusion_f07a_0102.client->dev;
	dev->phys = DRIVER_TP "/input0";

	__set_bit(BTN_TOUCH, dev->keybit);
	__set_bit(ABS_PRESSURE, dev->absbit);
	input_set_abs_params(dev, ABS_X, 0, PIXEL_XMAX-1, 0, 0);
	input_set_abs_params(dev, ABS_Y, 0, PIXEL_YMAX-1, 0, 0);
	input_set_abs_params(dev, ABS_PRESSURE, 0, 255, 0, 0);

	__set_bit(EV_SYN, dev->evbit);
	__set_bit(EV_KEY, dev->evbit);
	__set_bit(EV_ABS, dev->evbit);

	input_set_abs_params(dev, ABS_MT_POSITION_X, 0, PIXEL_XMAX-1, 0, 0);
	input_set_abs_params(dev, ABS_MT_POSITION_Y, 0, PIXEL_YMAX-1, 0, 0);
	input_set_abs_params(dev, ABS_MT_PRESSURE, 0, 255, 0, 0);
	input_mt_init_slots(dev, MAX_TOUCH+1);

	input_set_drvdata(dev, &fusion_f07a_0102);

	ret = input_register_device(dev);
	if (ret < 0)
		goto end;

	return 0;

end:
	input_free_device(dev);

	return ret;
}

#define WC_RETRY_COUNT	3
static int fusion_f07a_0102_write_complete(void)
{
	int ret, i;

	for (i = 0; i < WC_RETRY_COUNT; i++) {
		ret = fusion_f07a_0102_write_u8(FUSION_SCAN_COMPLETE, 0);
		if (ret == 0)
			break;
		else
			dev_err(&fusion_f07a_0102.client->dev, "Write complete failed(%d): %d\n", i, ret);
	}

	 return ret;
}

#define val_cut_max(x, max)	\
do {					\
	if (x > max)			\
		x = max;		\
} while (0)

#define DATA_START	FUSION_DATA_INFO
#define	DATA_END	FUSION_SECOND_TOUCHID_TIPSWITCH
#define DATA_LEN	(DATA_END - DATA_START + 1)
#define DATA_OFF(x)	((x) - DATA_START)

static int fusion_f07a_0102_read_sensor(void)
{
	int	ret;
	u8	data[DATA_LEN];
#define DATA(x) (data[DATA_OFF(x)])
	ret = fusion_f07a_0102_read_block(DATA_START, DATA_LEN, data);
	if (ret < 0) {
		dev_err(&fusion_f07a_0102.client->dev,
			"Read block failed: %d\n", ret);
			fusion_f07a_0102_write_complete();

		return ret;
	}

	fusion_f07a_0102.y1 = DATA(FUSION_Y1_POS_HI) << 8;
	fusion_f07a_0102.y1 |= DATA(FUSION_Y1_POS_LO);
	fusion_f07a_0102.x1 = DATA(FUSION_X1_POS_HI) << 8;
	fusion_f07a_0102.x1 |= DATA(FUSION_X1_POS_LO);
	fusion_f07a_0102.z1 = DATA(FUSION_FIRST_TOUCH_POINT_PRESS);
	fusion_f07a_0102.tip1 = DATA(FUSION_FIRST_TOUCHID_TIPSWITCH) & 0x0f;
	fusion_f07a_0102.tid1 = (DATA(FUSION_FIRST_TOUCHID_TIPSWITCH) & 0xf0) >> 4;

	fusion_f07a_0102.y2 = DATA(FUSION_Y2_POS_HI) << 8;
	fusion_f07a_0102.y2 |= DATA(FUSION_Y2_POS_LO);
	fusion_f07a_0102.x2 = DATA(FUSION_X2_POS_HI) << 8;
	fusion_f07a_0102.x2 |= DATA(FUSION_X2_POS_LO);
	fusion_f07a_0102.z2 = DATA(FUSION_SECOND_TOUCH_POINT_PRESS);
	fusion_f07a_0102.tip2 = DATA(FUSION_SECOND_TOUCHID_TIPSWITCH) & 0x0f;
	fusion_f07a_0102.tid2 = (DATA(FUSION_SECOND_TOUCHID_TIPSWITCH) & 0xf0) >> 4;

	fusion_f07a_0102.x1 = ((PIXEL_XMAX * fusion_f07a_0102.x1) / FUSION_7_XMAX);
	fusion_f07a_0102.y1 = ((PIXEL_YMAX * fusion_f07a_0102.y1) / FUSION_7_YMAX);
	fusion_f07a_0102.x2 = ((PIXEL_XMAX * fusion_f07a_0102.x2) / FUSION_7_XMAX);
	fusion_f07a_0102.y2 = ((PIXEL_YMAX * fusion_f07a_0102.y2) / FUSION_7_YMAX);

#undef DATA
	return 0;
}

static irqreturn_t fusion_f07a_0102_interrupt(int irq, void *dev_id)
{
	struct input_dev	*dev = fusion_f07a_0102.input;
	unsigned int		cur_msec;

	if (fusion_f07a_0102_read_sensor() < 0)
		goto irq_end;

	val_cut_max(fusion_f07a_0102.x1, PIXEL_XMAX-1);
	val_cut_max(fusion_f07a_0102.y1, PIXEL_YMAX-1);
	val_cut_max(fusion_f07a_0102.x2, PIXEL_XMAX-1);
	val_cut_max(fusion_f07a_0102.y2, PIXEL_YMAX-1);

	cur_msec = jiffies_to_msecs(jiffies);
	if ((fusion_f07a_0102.data.tip1 != fusion_f07a_0102.tip1) ||
	    (fusion_f07a_0102.data.tip2 != fusion_f07a_0102.tip2) ||
	    (cur_msec - fusion_f07a_0102.data.report_msec) > interval) {
		if (fusion_f07a_0102.tip1 == 1) {
			input_mt_slot(dev, (fusion_f07a_0102.tid1));
			input_mt_report_slot_state(dev, MT_TOOL_FINGER, true);
			input_report_abs(dev, ABS_MT_POSITION_X, fusion_f07a_0102.x1);
			input_report_abs(dev, ABS_MT_POSITION_Y, fusion_f07a_0102.y1);
			input_report_abs(dev, ABS_MT_PRESSURE, fusion_f07a_0102.z1);
		} else {
			if (fusion_f07a_0102.data.tip1 == 1) {
				input_mt_slot(dev, (fusion_f07a_0102.tid1));
				input_mt_report_slot_state(dev, MT_TOOL_FINGER, false);
				input_report_abs(dev, ABS_MT_PRESSURE, 0);
			}
		}

		if (fusion_f07a_0102.tip2 == 1) {
			input_mt_slot(dev, (fusion_f07a_0102.tid2));
			input_mt_report_slot_state(dev, MT_TOOL_FINGER, true);
			input_report_abs(dev, ABS_MT_POSITION_X, fusion_f07a_0102.x2);
			input_report_abs(dev, ABS_MT_POSITION_Y, fusion_f07a_0102.y2);
			input_report_abs(dev, ABS_MT_PRESSURE, fusion_f07a_0102.z2);
		} else {
			if (fusion_f07a_0102.data.tip2 == 1) {
				input_mt_slot(dev, (fusion_f07a_0102.tid2));
				input_mt_report_slot_state(dev, MT_TOOL_FINGER, false);
				input_report_abs(dev, ABS_MT_PRESSURE, 0);
			}
		}
		
		if (fusion_f07a_0102.tip1) {
			input_report_abs(dev, ABS_X, fusion_f07a_0102.x1);
			input_report_abs(dev, ABS_Y, fusion_f07a_0102.y1);
			input_report_key(dev, BTN_TOUCH, 1);
			input_report_abs(dev, ABS_PRESSURE, fusion_f07a_0102.z1);
		} else {
			input_report_key(dev, BTN_TOUCH, 0);
			input_report_abs(dev, ABS_PRESSURE, 0);
		}
		
		input_sync(dev);
		
		fusion_f07a_0102.data.tip1 = fusion_f07a_0102.tip1;
		fusion_f07a_0102.data.tip2 = fusion_f07a_0102.tip2;
		fusion_f07a_0102.data.report_msec = cur_msec;
	}

	fusion_f07a_0102_write_complete();
	
irq_end:
	return IRQ_HANDLED;
}

static const u8 *g_ver_product[4] = {
	"10Z8", "70Z7", "43Z6", ""
};

static int __devinit fusion_f07a_0102_probe(struct i2c_client *i2c,
					const struct i2c_device_id *id)
{
	int	ret;
	u8	ver_product, ver_id, gpio_no;
	u32	version;

	fusion_f07a_0102.client = i2c;
	i2c_set_clientdata(i2c, &fusion_f07a_0102);
	
	printk(KERN_INFO "fusion :Touchscreen registered with bus id (%d) with slave address 0x%x\n",
			 i2c_adapter_id(fusion_f07a_0102.client->adapter),
			 fusion_f07a_0102.client->addr);

	ret = fusion_f07a_0102_read_u8(FUSION_FIRM_VERSION1);
	if (ret < 0) {
		dev_err(&i2c->dev, "query failed: %d\n", ret);
		goto end;
	}

	ver_product = (((u8)ret) & 0xc0) >> 6;
	version = (10 + ((((u32)ret)&0x30) >> 4)) * 100000;
	version += (((u32)ret)&0xf) * 1000;

	ret = fusion_f07a_0102_read_u8(FUSION_FIRM_VERSION2);
	if (ret < 0) {
		dev_err(&i2c->dev, "query failed: %d\n", ret);
		goto end;
	}

	ver_id = ((u8)(ret) & 0x6) >> 1;
	version += ((((u32)ret) & 0xf8) >> 3) * 10;
	version += (((u32)ret) & 0x1) + 1; /* 0 is build 1, 1 is build 2 */

	printk(KERN_INFO "fusion version product %s(%d)\n", g_ver_product[ver_product], ver_product);
	printk(KERN_INFO "fusion version id %s(%d)\n", ver_id ? "1.4" : "1.0", ver_id);
	printk(KERN_INFO "fusion version series (%d)\n", version);

	if (ver_product != FUSION_PRODUCT_INFO_7) {
		dev_err(&i2c->dev, "illegal product id: %d\n", ver_product);
		ret = -ENODEV;
		goto end;
	}
	
	ret = fusion_f07a_0102_write_u8(FUSION_RESET_CONTROL, 0x80);
	if (ret < 0) {
		dev_err(&i2c->dev, "device reset failed: %d\n", ret);
		goto end;
	}
	
	mdelay(125);
	
	ret = fusion_f07a_0102_register_input();
	if (ret < 0) {
		dev_err(&i2c->dev, "can't register input: %d\n", ver_product);
		ret = -ENODEV;
		goto end;
	}

	if (machine_is_tz2000eva())
		gpio_no = GPIO_45;
	else
		gpio_no = GPIO_44;
	
	fusion_f07a_0102.irq = gpio_to_irq(gpio_no);
	ret = request_threaded_irq(fusion_f07a_0102.irq, NULL,
				   fusion_f07a_0102_interrupt,
				   IRQF_TRIGGER_RISING | IRQF_ONESHOT, DRIVER_TP,
				   &fusion_f07a_0102);
	if (ret < 0) {
		dev_err(&i2c->dev, "can't get irq %d: %d\n", fusion_f07a_0102.irq, ret);
		goto end2;
	}

	ret = fusion_f07a_0102_write_u8(FUSION_SCAN_COMPLETE, 0);
	if (ret < 0) {
		dev_err(&i2c->dev, "scan complete failed: %d\n", ret);
		goto end3;
	}

	return 0;

end3:
	free_irq(fusion_f07a_0102.irq, &fusion_f07a_0102);
end2:
	input_unregister_device(fusion_f07a_0102.input);
	input_free_device(fusion_f07a_0102.input);
end:
	i2c_set_clientdata(i2c, NULL);
	return ret;
}

static int __devexit fusion_f07a_0102_remove(struct i2c_client *i2c)
{
	free_irq(fusion_f07a_0102.irq, &fusion_f07a_0102);
	input_unregister_device(fusion_f07a_0102.input);
	input_free_device(fusion_f07a_0102.input);
	i2c_set_clientdata(i2c, NULL);

	printk(KERN_INFO "fusion_f07a_0102 driver removed\n");

	return 0;
}

#ifdef CONFIG_PM
static int fusion_f07a_0102_suspend(struct device *dev)
{
	disable_irq(fusion_f07a_0102.irq);

	return 0;
}

static int fusion_f07a_0102_resume(struct device *dev)
{
	int	ret = 0;
	struct i2c_client *i2c = to_i2c_client(dev);
	
	ret = fusion_f07a_0102_write_u8(FUSION_RESET_CONTROL, 0x80);
	if (ret < 0) {
		dev_err(&i2c->dev, "write FUSION_RESET_CONTROL fail: %d\n", ret);
	}
	
	mdelay(125);
	
	ret = fusion_f07a_0102_write_u8(FUSION_SCAN_COMPLETE, 0);
	if (ret < 0) {
		dev_err(&i2c->dev, "write FUSION_SCAN_COMPLETE fail: %d\n", ret);
	}
	
	enable_irq(fusion_f07a_0102.irq);
	
	return 0;
}

static const struct dev_pm_ops fusion_f07a_0102_dev_pm_ops = {
	SET_SYSTEM_SLEEP_PM_OPS(fusion_f07a_0102_suspend, fusion_f07a_0102_resume)
};
#endif

static const struct i2c_device_id fusion_f07a_0102_id[] = {
	{ DRIVER_TP, 2 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, fusion_f07a_0102_id);

static struct i2c_driver fusion_f07a_0102_driver = {
	.driver = {
		.name		= DRIVER_TP,
		.owner		= THIS_MODULE,
#ifdef CONFIG_PM
		.pm		= &fusion_f07a_0102_dev_pm_ops,
#endif
	},
	.probe		= fusion_f07a_0102_probe,
	.remove		= __devexit_p(fusion_f07a_0102_remove),
	.id_table	= fusion_f07a_0102_id,
};
module_i2c_driver(fusion_f07a_0102_driver);

MODULE_AUTHOR("TOSHIBA Corporation");
MODULE_DESCRIPTION("Glenfiddich Touchscreen Driver(F07A-0102)");
MODULE_LICENSE("GPL v2");

