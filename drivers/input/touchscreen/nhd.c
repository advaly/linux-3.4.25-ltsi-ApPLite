/*
 * linux/drivers/input/touchscreen/nhd.c
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
#include <linux/slab.h>
#include <asm/mach-types.h>
#include <mach/hardware.h>
#include <mach/platform.h>
#include <mach/irqs.h>
#include "nhd.h"

#define DATA_START	(NHD_DEVICE_MODE)
#define DATA_LEN	(NHD_TOUCH5_YL-DATA_START+1)

static ulong interval = 16;
module_param(interval, ulong, 0644);
MODULE_PARM_DESC(interval, "Interval of input event (msec)");

static int nhd_read_data(struct i2c_client *i2c, char *buf, int buflen)
{
	u8		msgbuf0[] = {DATA_START};
	u16		slave = i2c->addr;
	u16		flags = i2c->flags;
	struct i2c_msg	msg[] = { {slave, flags, 1, msgbuf0},
				  {slave, flags | I2C_M_RD, buflen, buf} };

	return i2c_transfer(i2c->adapter, msg, ARRAY_SIZE(msg));
}

static int nhd_init_chip(struct nhd_ts_data *data)
{
	int retval;
	struct i2c_client *i2c = data->client;

	retval = i2c_smbus_write_byte_data(i2c, NHD_DEVICE_MODE,
					   NHD_NORMAL_OPERATION_MODE);
	if (retval < 0) {
		dev_err(&i2c->dev, "Device Mode reg write failed\n");
		return retval;
	}

	return 0;
}

static irqreturn_t nhd_irq(int irq, void *device_data)
{
	struct nhd_ts_data	*data = device_data;
	struct i2c_client	*i2c = data->client;
	int			ret, i;
	char			buf[DATA_LEN];
	u8			num_of_touch;
	struct st_touch_data	tdata[MAX_TOUCH] = {{0, 0, 0, 0},}, *t;
	unsigned int		cur_msec;

	ret = nhd_read_data(i2c, buf, DATA_LEN);
	if (ret < 0) {
		dev_err(&i2c->dev, "Read block failed: %d\n", ret);
		goto irq_end;
	}

	num_of_touch = *(buf + NHD_TD_STATUS) & 0x7;

	cur_msec = jiffies_to_msecs(jiffies);
	if ((data->data.num_of_touch != num_of_touch) ||
	    (cur_msec - data->data.report_msec) > interval) {
		for (i = 0; i < MAX_TOUCH; i++) {
			t = &tdata[i];
			t->event = (*(buf + NHD_TOUCH1_XH + i*TOUCH_DATA_SIZE) >> 6) & 0x3;
			t->x = (*(buf + NHD_TOUCH1_XH + i*TOUCH_DATA_SIZE) & 0xf) << 8;
			t->x |= *(buf + NHD_TOUCH1_XL + i*TOUCH_DATA_SIZE);
			t->tid = (*(buf + NHD_TOUCH1_YH + i*TOUCH_DATA_SIZE) >> 4) & 0xf;
			t->y = (*(buf + NHD_TOUCH1_YH + i*TOUCH_DATA_SIZE) & 0xf) << 8;
			t->y |= *(buf + NHD_TOUCH1_YL + i*TOUCH_DATA_SIZE);
			if ((t->event == NHD_EVENT_PUT_DOWN) || (t->event == NHD_EVENT_CONTACT)) {
				input_mt_slot(data->in_dev, t->tid+1);
				input_mt_report_slot_state(data->in_dev, MT_TOOL_FINGER, true);
				input_report_abs(data->in_dev, ABS_MT_POSITION_X, t->x);
				input_report_abs(data->in_dev, ABS_MT_POSITION_Y, t->y);
				input_report_abs(data->in_dev, ABS_MT_PRESSURE, 255);
			} else if (t->event == NHD_EVENT_PUT_UP) {
				input_mt_slot(data->in_dev, t->tid+1);		
				input_mt_report_slot_state(data->in_dev, MT_TOOL_FINGER, false);
				input_report_abs(data->in_dev, ABS_MT_PRESSURE, 0);
			} else if (t->event == NHD_EVENT_RESERVED){
				break;
			}
		}

		if (num_of_touch) {
			t = &tdata[0];
			input_report_abs(data->in_dev, ABS_X, t->x);
			input_report_abs(data->in_dev, ABS_Y, t->y);
			input_report_key(data->in_dev, BTN_TOUCH, 1);
			input_report_abs(data->in_dev, ABS_PRESSURE, 255);
		} else {
			input_report_key(data->in_dev, BTN_TOUCH, 0);
			input_report_abs(data->in_dev, ABS_PRESSURE, 0);
		}
		input_sync(data->in_dev);

		data->data.num_of_touch = num_of_touch;
		data->data.report_msec = cur_msec;
	}

irq_end:
	return IRQ_HANDLED;
}

static int __devinit nhd_probe(struct i2c_client *i2c,
			       const struct i2c_device_id *id)
{
	struct nhd_ts_data	*nhd_data;
	struct input_dev	*in_dev;
	int			error;
	int			gpio_no;
	u8			vendor;

	printk(KERN_INFO "nhd :Touchscreen registered with bus id (%d) with slave address 0x%x\n",
			 i2c_adapter_id(i2c->adapter), i2c->addr);

	nhd_data = kzalloc(sizeof(struct nhd_ts_data), GFP_KERNEL);
	in_dev = input_allocate_device();
	if (!nhd_data || !in_dev) {
		dev_err(&i2c->dev, "device memory alloc failed\n");
		error = -ENOMEM;
		goto err_free_mem;
	}

	nhd_data->in_dev = in_dev;
	nhd_data->client = i2c;

	i2c_set_clientdata(i2c, nhd_data);

	error = i2c_smbus_read_byte_data(i2c, NHD_ID_G_FT5201ID);
	if (error < 0) {
		dev_err(&i2c->dev, "query failed: %d\n", error);
		goto err_i2c_clientdata;
	}

	vendor = error & 0xff;
	printk(KERN_INFO "nhd vendor's chip id: %x\n", vendor);
	
	if (vendor != NHD_CHIP_ID) {
		dev_err(&i2c->dev, "not support chip\n");
		goto err_i2c_clientdata;
	}
	
	/* register the device to input subsystem */
	in_dev->name = DRIVER_TP;
	in_dev->id.bustype = BUS_I2C;
	in_dev->dev.parent = &i2c->dev;
	in_dev->phys = DRIVER_TP "/input0";

	__set_bit(BTN_TOUCH, in_dev->keybit);
	__set_bit(ABS_PRESSURE, in_dev->absbit);
	input_set_abs_params(in_dev, ABS_X, 0, NHD_X_MAX - 1, 0, 0);
	input_set_abs_params(in_dev, ABS_Y, 0, NHD_Y_MAX - 1, 0, 0);
	input_set_abs_params(in_dev, ABS_PRESSURE, 0, 255, 0, 0);

	__set_bit(EV_SYN, in_dev->evbit);
	__set_bit(EV_KEY, in_dev->evbit);
	__set_bit(EV_ABS, in_dev->evbit);
	input_set_abs_params(in_dev, ABS_MT_POSITION_X, 0, NHD_X_MAX - 1, 0, 0);
	input_set_abs_params(in_dev, ABS_MT_POSITION_Y, 0, NHD_Y_MAX - 1, 0, 0);
	input_set_abs_params(in_dev, ABS_MT_PRESSURE, 0, 255, 0, 0);
	input_mt_init_slots(in_dev, MAX_TOUCH+1);
	
	input_set_drvdata(in_dev, nhd_data);

	error = input_register_device(in_dev);
	if (error) {
		dev_err(&i2c->dev, "failed to register input device\n");
		goto err_i2c_clientdata;
	}

	if (machine_is_tz2000eva())
		gpio_no = GPIO_45;
	else
		gpio_no = GPIO_44;

	nhd_data->irq = gpio_to_irq(gpio_no);
	error = request_threaded_irq(nhd_data->irq, NULL, nhd_irq,
				     IRQF_TRIGGER_FALLING | IRQF_ONESHOT, DRIVER_TP, nhd_data);
	if (error) {
		dev_err(&i2c->dev, "request irq %d failed\n", nhd_data->irq);
		goto err_unregister_device;
	}
	
	/* configure the touch panel controller */
	error = nhd_init_chip(nhd_data);
	if (error) {
		dev_err(&i2c->dev, "error in nhd config\n");
		goto err_free_irq;
	}

	return 0;

err_free_irq:
	free_irq(nhd_data->irq, nhd_data);
err_unregister_device:
	input_unregister_device(nhd_data->in_dev);
err_i2c_clientdata:
	i2c_set_clientdata(i2c, NULL);
err_free_mem:
	input_free_device(in_dev);
	kfree(nhd_data);

	return error;
}

static int __devexit nhd_remove(struct i2c_client *i2c)
{
	struct nhd_ts_data *nhd_data = i2c_get_clientdata(i2c);

	free_irq(nhd_data->irq, nhd_data);
	input_unregister_device(nhd_data->in_dev);
	input_free_device(nhd_data->in_dev);
	i2c_set_clientdata(i2c, NULL);
	kfree(nhd_data);

	printk(KERN_INFO "nhd driver removed\n");

	return 0;
}

#ifdef CONFIG_PM
static int nhd_suspend(struct device *dev)
{
	struct i2c_client *i2c = to_i2c_client(dev);
	struct nhd_ts_data *nhd_data = i2c_get_clientdata(i2c);

	disable_irq(nhd_data->irq);

	return 0;
}

static int nhd_resume(struct device *dev)
{
	int ret;
	struct i2c_client *i2c = to_i2c_client(dev);
	struct nhd_ts_data *nhd_data = i2c_get_clientdata(i2c);

	ret = nhd_init_chip(nhd_data);
	if (ret < 0) {
		dev_err(&i2c->dev, "nhd controller config failed\n");
		return ret;
	}
	
	enable_irq(nhd_data->irq);
	
	return 0;
}

static const struct dev_pm_ops nhd_dev_pm_ops = {
	SET_SYSTEM_SLEEP_PM_OPS(nhd_suspend, nhd_resume)
};
#endif

static const struct i2c_device_id nhd_id[] = {
	{ DRIVER_TP, 2 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, nhd_id);

static struct i2c_driver nhd_driver = {
	.driver	= {
		.name		= DRIVER_TP,
		.owner		= THIS_MODULE,
#ifdef CONFIG_PM
		.pm		= &nhd_dev_pm_ops,
#endif
	},
	.probe		= nhd_probe,
	.remove		= __devexit_p(nhd_remove),
	.id_table	= nhd_id,
};
module_i2c_driver(nhd_driver);

MODULE_AUTHOR("TOSHIBA Corporation");
MODULE_DESCRIPTION("Glenfiddich Touchscreen Driver(NHD4.3)");
MODULE_LICENSE("GPL v2");

