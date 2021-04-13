/*
 * linux/drivers/input/touchscreen/it7260_sts.c
 *
 * (C) Copyright TOSHIBA Corporation
 * Semiconductor & Storage Products Company 2014
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
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/pm.h>
#include <linux/gpio.h>
#include <linux/slab.h>
#include <asm/mach-types.h>
#include <asm/io.h>
#include <linux/i2c.h>
#include <linux/timer.h>
#include <linux/delay.h>

/* buffer address */
#define CMD_BUF		0x20	/* command buffer (write only) */
#define SYS_CMD_BUF	0x40	/* systerm command buffer (write only) */
#define QUERY_BUF	0x80	/* query buffer (read only) */
#define CMD_RSP_BUF	0xA0	/* command response buffer (read only) */
#define SYS_CMD_RSP_BUF	0xC0	/* systerm command response buffer (read only) */
#define POINT_INFO_BUF	0xE0	/* point information buffer (read only) */

#undef DEBUG_IT7260_TS
#define DISABLE_I2C_DRIVER_PM

#define IT7260_X_RESOLUTION		(480)
#define IT7260_Y_RESOLUTION		(272)
#define SCREEN_X_RESOLUTION		(480)
#define SCREEN_Y_RESOLUTION		(272)
#define QUERY_BUF_READ_MAX		(200)

#undef USE_EVENT_KEY
#undef RESET_IT7260_TS_IN_PROBE

#define USE_TZ2000GPIO_INT
#undef USE_TZ2000GPIO_LEVEL_INT
#define USE_IRQ_LEVEL_LOW
#undef USE_IRQ_LEVEL_HIGH
#undef USE_IRQ_EDGE_FALLING
#undef USE_IRQ_EDGE_RISING

#define GPIO_44		(44)
#define GPIO_45		(45)
static int gpio_no = GPIO_44;

static ulong delay = (0); /* default:(HZ / 20) */
module_param(delay, ulong, 0644);
MODULE_PARM_DESC(delay, "Set touchscreen controller sample delay. (jiffies)");

static ulong interval = 16;
module_param(interval, ulong, 0644);
MODULE_PARM_DESC(interval, "Interval of input event (msec)");

struct it7260_ts_data {
	unsigned short xpos;
	unsigned short ypos;
	unsigned char pressure;
	unsigned int report_msec;
};

struct it7260_ts_priv {
	struct i2c_client *client;
	struct input_dev *input;
	struct delayed_work work;
	struct mutex mutex;
	int irq;
	struct it7260_ts_data data;
};

static int it7260_identify_capsensor(struct i2c_client *client);
static int it7260_firmware_information(struct i2c_client *client, unsigned char *rom_fw, unsigned char *flash_fw);
static int it7260_2d_resolutions(struct i2c_client *client, unsigned char id);
static int it7260_flash_size(struct i2c_client *client, unsigned short *size);
static int it7260_interrupt_notification_status(struct i2c_client *client, unsigned char *enable, unsigned char *type);
static int it7260_gesture_information(struct i2c_client *client);
static int it7260_configuration_version(struct i2c_client *client, unsigned char *ver, unsigned char *autotune);
static int it7260_set_capsensor_information(struct i2c_client *client, unsigned char enable, unsigned char type);
static int it7260_reset_queue(struct i2c_client *client);
static int it7260_reset(struct i2c_client *client);

/**
 * i2c_master_read_it7260 - issue two I2C message in master receive mode
 * @client: handler to slave device
 * @buf_index: buffer address
 * @buf_data: where to store data read from slave
 * @len_data: the bytes of buf_data to read
 *
 * returns negative errno, or else the number of bytes read
 */
static int i2c_master_read_it7260(struct i2c_client *client,
		unsigned char buf_index, unsigned char *buf_data,
		unsigned short len_data)
{
	int ret;
	struct i2c_msg msgs[2] = {
		{
			.addr = client->addr,
			.flags = I2C_M_NOSTART,
			.len = 1,
			.buf = &buf_index,
		},
		{
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = len_data,
			.buf = buf_data,
		}
	};

	ret = i2c_transfer(client->adapter, msgs, 2);

	return (ret == 2) ? len_data : ret;
}

/**
 * i2c_master_write_it7260 - issue a single I2C message in master transmit mode
 * @client: handler to slave device
 * @buf_index: buffer address
 * @buf_data: data that wile be write to the slave
 * @len_data: the bytes of buf_data to write
 *
 * returns negative errno, or else the number of bytes written
 */
static int i2c_master_write_it7260(struct i2c_client *client,
		unsigned char buf_index, unsigned char const *buf_data,
		unsigned short len_data)
{
	unsigned char buf[17];
	int ret;

	struct i2c_msg msgs[1] = {
		{
			.addr = client->addr,
			.flags = 0, /* default write flag */
			.len = len_data + 1,
			.buf = buf,
		}
	};

	buf[0] = buf_index;
	memcpy(&buf[1], buf_data, len_data);

	ret = i2c_transfer(client->adapter, msgs, 1);

	return (ret == 1) ? sizeof(buf) : ret;
}

/**
 * it7260_ts_poscheck - delayed work
 *
 * get the informations of contacts from slave and report it
 */
static void it7260_ts_poscheck(struct work_struct *work)
{
	struct it7260_ts_priv *priv = container_of(work,
							struct it7260_ts_priv, work.work);
	unsigned char buf[14];
	unsigned short xpos = 0, ypos = 0;
	unsigned char pressure;
	unsigned char query = 0;
	unsigned int cur_msec;

	mutex_lock(&priv->mutex);

	i2c_master_read_it7260(priv->client, QUERY_BUF, &query, 1);
	if (!(query & 0x80)) {
#ifdef DEBUG_IT7260_TS
		dev_info(&priv->client->dev, "no finger touch\n");
#endif
		goto out;
	}

	memset(&buf, 0, sizeof(buf));

	i2c_master_read_it7260(priv->client, POINT_INFO_BUF, buf, 14);

	/* touch key */
	if (buf[0] == 0x41) {
#ifdef DEBUG_IT7260_TS
		dev_info(&priv->client->dev, "the key number %d\n", buf[1]);
#endif
#if defined(USE_EVENT_KEY)
		if (buf[1] == 0x04)
			input_report_key(priv->input, KEY_HOME, !!buf[2]);
		else if (buf[1] == 0x03)
			input_report_key(priv->input, KEY_MENU, !!buf[2]);
		else if (buf[1] == 0x02)
			input_report_key(priv->input, KEY_BACK, !!buf[2]);
		else if (buf[1] == 0x01)
			input_report_key(priv->input, KEY_POWER, !!buf[2]);
		else
			goto out;

#endif
		input_sync(priv->input);
		goto out;
	}

	xpos = IT7260_X_RESOLUTION - (((buf[3] & 0x0F) << 8) | buf[2]);
	ypos = IT7260_Y_RESOLUTION - (((buf[3] & 0xF0) << 4) | buf[4]);
	pressure = buf[5];
#ifdef DEBUG_IT7260_TS
	dev_info(&priv->client->dev, "xpos = %d, ypos = %d, pressure= %d\n",
							xpos, ypos, pressure);
#endif

	cur_msec = jiffies_to_msecs(jiffies);
	if ((priv->data.pressure != pressure) ||
	    (priv->data.report_msec > cur_msec) ||
	    (cur_msec - priv->data.report_msec) > interval) {
		input_report_key(priv->input, BTN_TOUCH, !!pressure);
		if (xpos < IT7260_X_RESOLUTION && ypos < IT7260_Y_RESOLUTION) {
			input_report_abs(priv->input, ABS_X, xpos);
			input_report_abs(priv->input, ABS_Y, ypos);
		}
		input_report_abs(priv->input, ABS_PRESSURE, pressure);
		input_sync(priv->input);

		priv->data.xpos = xpos;
		priv->data.ypos = ypos;
		priv->data.pressure = pressure;
		priv->data.report_msec = cur_msec;
	}

out:
	mutex_unlock(&priv->mutex);
	enable_irq(priv->irq);
}

static irqreturn_t it7260_ts_isr(int irq, void *dev_id)
{
	struct it7260_ts_priv *priv = dev_id;

	disable_irq_nosync(irq);
	schedule_delayed_work(&priv->work, delay);

	return IRQ_HANDLED;
}

/**
 * it7260_identify_capsensor - identify capacitance sensor model
 *
 * returns error -1, or else success 0
 */
static int it7260_identify_capsensor(struct i2c_client *client)
{
	unsigned char buf[10];
	unsigned char query = 0;
	unsigned long count;

	count = 0;
	i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	while ((query & 0x01) && (count++ < QUERY_BUF_READ_MAX)) {
		udelay(1);
		i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	}
	if (count >= QUERY_BUF_READ_MAX)
		dev_err(&client->dev, "%s(%d)@%s:Reading of the query buffer is busy.\n", __FILE__, __LINE__, __func__);

#ifdef DEBUG_IT7260_TS
	dev_info(&client->dev, "Identify cap sensor\n");
#endif

	/* 0x00: the command of identify cap sensor */
	buf[0] = 0x00;
	i2c_master_write_it7260(client, CMD_BUF, buf, 1);

	count = 0;
	i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	while ((query & 0x01) && (count++ < QUERY_BUF_READ_MAX)) {
		udelay(1);
		i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	}
	if (count >= QUERY_BUF_READ_MAX)
		dev_err(&client->dev, "%s(%d)@%s:Reading of the query buffer is busy.\n", __FILE__, __LINE__, __func__);

#ifdef DEBUG_IT7260_TS
	dev_info(&client->dev, "Command status 0x%04x\n", query);
#endif

	memset(&buf, 0, sizeof(buf));
	i2c_master_read_it7260(client, CMD_RSP_BUF, buf, 10);

#ifdef DEBUG_IT7260_TS
	dev_info(&client->dev, "Vendor ID : %c%c%c\n", buf[1], buf[2], buf[3]);
	dev_info(&client->dev, "Device ID : %c%c%c%c\n", buf[4], buf[5], buf[6], buf[7]);
	dev_info(&client->dev, "Device Version : %c%c\n", buf[8], buf[9]);
#endif

	if (buf[1] != 'I' || buf[2] != 'T' || buf[3] != 'E') {
		dev_err(&client->dev, "Identify cap sensor error\n");
		return -1;
	}

	return 0;
}

static int it7260_firmware_information(struct i2c_client *client, unsigned char *rom_fw, unsigned char *flash_fw)
{
	unsigned char buf[9];
	unsigned char query = 0;
	unsigned long count;

	count = 0;
	i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	while ((query & 0x01) && (count++ < QUERY_BUF_READ_MAX)) {
		udelay(1);
		i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	}
	if (count >= QUERY_BUF_READ_MAX)
		dev_err(&client->dev, "%s(%d)@%s:Reading of the query buffer is busy.\n", __FILE__, __LINE__, __func__);

#ifdef DEBUG_IT7260_TS
	dev_info(&client->dev, "Get firmware information\n");
#endif

	/* 0x01, 0x00: the command of get firmware information */
	buf[0] = 0x01;
	buf[1] = 0x00;
	i2c_master_write_it7260(client, CMD_BUF, buf, 2);

	count = 0;
	i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	while ((query & 0x01) && (count++ < QUERY_BUF_READ_MAX)) {
		udelay(1);
		i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	}
	if (count >= QUERY_BUF_READ_MAX)
		dev_err(&client->dev, "%s(%d)@%s:Reading of the query buffer is busy.\n", __FILE__, __LINE__, __func__);

#ifdef DEBUG_IT7260_TS
	dev_info(&client->dev, "Command status 0x%04x\n", query);
#endif

	memset(&buf, 0, sizeof(buf));
	i2c_master_read_it7260(client, CMD_RSP_BUF, buf, 9);

#ifdef DEBUG_IT7260_TS
	dev_info(&client->dev, "len = %d\n", buf[0]);
	dev_info(&client->dev, "ROM FW Version : %02x.%02x.%02x.%02x\n", buf[1], buf[2], buf[3], buf[4]);
	dev_info(&client->dev, "Flash FW Version : %02x.%02x.%02x.%02x\n", buf[5], buf[6], buf[7], buf[8]);
#endif

	if (query || buf[0] != 9) {
		dev_err(&client->dev, "Command status error 0x%04x\n", query);
		return -1;
	}

	(*rom_fw++) = buf[1];
	(*rom_fw++) = buf[2];
	(*rom_fw++) = buf[3];
	(*rom_fw++) = buf[4];

	(*flash_fw++) = buf[5];
	(*flash_fw++) = buf[6];
	(*flash_fw++) = buf[7];
	(*flash_fw++) = buf[8];

	return 0;
}

static int it7260_2d_resolutions(struct i2c_client *client, unsigned char id)
{
	unsigned char buf[11];
	unsigned char query = 0;
	unsigned long count;

	count = 0;
	i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	while ((query & 0x01) && (count++ < QUERY_BUF_READ_MAX)) {
		udelay(1);
		i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	}
	if (count >= QUERY_BUF_READ_MAX)
		dev_err(&client->dev, "%s(%d)@%s:Reading of the query buffer is busy.\n", __FILE__, __LINE__, __func__);

#ifdef DEBUG_IT7260_TS
	dev_info(&client->dev, "Get panel resolutions\n");
#endif

	/* 0x01, 0x02: the command of get panel resolutions */
	buf[0] = 0x01;
	buf[1] = 0x02;
	buf[2] = id;
	i2c_master_write_it7260(client, CMD_BUF, buf, 3);

	count = 0;
	i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	while ((query & 0x01) && (count++ < QUERY_BUF_READ_MAX)) {
		udelay(1);
		i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	}
	if (count >= QUERY_BUF_READ_MAX)
		dev_err(&client->dev, "%s(%d)@%s:Reading of the query buffer is busy.\n", __FILE__, __LINE__, __func__);

#ifdef DEBUG_IT7260_TS
	dev_info(&client->dev, "Command status 0x%04x\n", query);
#endif

	memset(&buf, 0, sizeof(buf));
	i2c_master_read_it7260(client, CMD_RSP_BUF, buf, 11);

#ifdef DEBUG_IT7260_TS
	dev_info(&client->dev, "len = %d\n", buf[0]);
	dev_info(&client->dev, "ID : 0x%02x\n", buf[1]);
	dev_info(&client->dev, "X Resolution : %d\n", *(unsigned short *)&buf[2]);
	dev_info(&client->dev, "Y Resolution : %d\n", *(unsigned short *)&buf[4]);
	dev_info(&client->dev, "Base Step : %d\n", buf[6]);
	dev_info(&client->dev, "2D Type : 0x%02x\n", buf[7]);
	dev_info(&client->dev, "Stage A : 0x%02x\n", buf[8]);
	dev_info(&client->dev, "Stage B : 0x%02x\n", buf[9]);
	dev_info(&client->dev, "Stage C : 0x%02x\n", buf[10]);
#endif

	if (query || buf[0] != 11) {
		dev_err(&client->dev, "Command status error 0x%04x\n", query);
		return -1;
	}

	return 0;
}

static int it7260_flash_size(struct i2c_client *client, unsigned short *size)
{
	unsigned char buf[3];
	unsigned char query = 0;
	unsigned long count;

	count = 0;
	i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	while ((query & 0x01) && (count++ < QUERY_BUF_READ_MAX)) {
		udelay(1);
		i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	}
	if (count >= QUERY_BUF_READ_MAX)
		dev_err(&client->dev, "%s(%d)@%s:Reading of the query buffer is busy.\n", __FILE__, __LINE__, __func__);

#ifdef DEBUG_IT7260_TS
	dev_info(&client->dev, "Get flash size in byte\n");
#endif

	/* 0x01, 0x03: the command of get flash size in byte */
	buf[0] = 0x01;
	buf[1] = 0x03;
	i2c_master_write_it7260(client, CMD_BUF, buf, 2);

	count = 0;
	i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	while ((query & 0x01) && (count++ < QUERY_BUF_READ_MAX)) {
		udelay(1);
		i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	}
	if (count >= QUERY_BUF_READ_MAX)
		dev_err(&client->dev, "%s(%d)@%s:Reading of the query buffer is busy.\n", __FILE__, __LINE__, __func__);

#ifdef DEBUG_IT7260_TS
	dev_info(&client->dev, "Command status 0x%04x\n", query);
#endif

	memset(&buf, 0, sizeof(buf));
	i2c_master_read_it7260(client, CMD_RSP_BUF, buf, 3);

#ifdef DEBUG_IT7260_TS
	dev_info(&client->dev, "len = %d\n", buf[0]);
	dev_info(&client->dev, "Flash Size : 0x%04x\n", *(unsigned short *)&buf[1]);
#endif

	if (query || buf[0] != 3) {
		dev_err(&client->dev, "Command status error 0x%04x\n", query);
		return -1;
	}

	(*size) = *(unsigned short *)&buf[1];

	return 0;
}

static int it7260_interrupt_notification_status(struct i2c_client *client, unsigned char *enable, unsigned char *type)
{
	unsigned char buf[2];
	unsigned char query = 0;
	unsigned long count;

	count = 0;
	i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	while ((query & 0x01) && (count++ < QUERY_BUF_READ_MAX)) {
		udelay(1);
		i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	}
	if (count >= QUERY_BUF_READ_MAX)
		dev_err(&client->dev, "%s(%d)@%s:Reading of the query buffer is busy.\n", __FILE__, __LINE__, __func__);

#ifdef DEBUG_IT7260_TS
	dev_info(&client->dev, "Get interrupt notification status\n");
#endif

	/* 0x01, 0x04: the command of the to get interrupt notification status */
	buf[0] = 0x01;
	buf[1] = 0x04;
	i2c_master_write_it7260(client, CMD_BUF, buf, 2);

	count = 0;
	i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	while ((query & 0x01) && (count++ < QUERY_BUF_READ_MAX)) {
		udelay(1);
		i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	}
	if (count >= QUERY_BUF_READ_MAX)
		dev_err(&client->dev, "%s(%d)@%s:Reading of the query buffer is busy.\n", __FILE__, __LINE__, __func__);

#ifdef DEBUG_IT7260_TS
	dev_info(&client->dev, "Command status 0x%04x\n", query);
#endif

	memset(&buf, 0, sizeof(buf));
	i2c_master_read_it7260(client, CMD_RSP_BUF, buf, 2);

#ifdef DEBUG_IT7260_TS
	dev_info(&client->dev, "Status = 0x%02x, Type = 0x%02x\n", buf[0], buf[1]);
#endif

	if (query) {
		dev_err(&client->dev, "Command status error 0x%04x\n", query);
		return -1;
	}

	(*enable) = buf[0];
	(*type) = buf[1];

	return 0;
}

static int it7260_gesture_information(struct i2c_client *client)
{
	unsigned char buf[11];
	unsigned char query = 0;
	unsigned long count;

	count = 0;
	i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	while ((query & 0x01) && (count++ < QUERY_BUF_READ_MAX)) {
		udelay(1);
		i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	}
	if (count >= QUERY_BUF_READ_MAX)
		dev_err(&client->dev, "%s(%d)@%s:Reading of the query buffer is busy.\n", __FILE__, __LINE__, __func__);

#ifdef DEBUG_IT7260_TS
	dev_info(&client->dev, "Get the gesture mode\n");
#endif

	/* 0x01, 0x05: the command of get the gesture mode */
	buf[0] = 0x01;
	buf[1] = 0x05;
	buf[2] = 0x00;
	i2c_master_write_it7260(client, CMD_BUF, buf, 3);

	count = 0;
	i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	while ((query & 0x01) && (count++ < QUERY_BUF_READ_MAX)) {
		udelay(1);
		i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	}
	if (count >= QUERY_BUF_READ_MAX)
		dev_err(&client->dev, "%s(%d)@%s:Reading of the query buffer is busy.\n", __FILE__, __LINE__, __func__);

#ifdef DEBUG_IT7260_TS
	dev_info(&client->dev, "Command status 0x%04x\n", query);
#endif

	memset(&buf, 0, sizeof(buf));
	i2c_master_read_it7260(client, CMD_RSP_BUF, buf, 14);

#ifdef DEBUG_IT7260_TS
	dev_info(&client->dev, "len = %d\n", buf[0]);
	dev_info(&client->dev, "Gestures Support : 0x%02x\n", buf[1]);
	dev_info(&client->dev, "1-Finger Gesture : 0x%016llx\n", *(unsigned long long *)&buf[2]);
	dev_info(&client->dev, "2-Finger Gesture : 0x%016llx\n", *(unsigned long long *)&buf[6]);
	dev_info(&client->dev, "3-Finger Gesture : 0x%016llx\n", *(unsigned long long *)&buf[10]);
#endif

	if (query || buf[0] != 14) {
		dev_err(&client->dev, "Command status error 0x%04x\n", query);
		return -1;
	}

	return 0;
}

static int it7260_configuration_version(struct i2c_client *client, unsigned char *ver, unsigned char *autotune)
{
	unsigned char buf[7];
	unsigned char query = 0;
	unsigned long count;

	count = 0;
	i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	while ((query & 0x01) && (count++ < QUERY_BUF_READ_MAX)) {
		udelay(1);
		i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	}
	if (count >= QUERY_BUF_READ_MAX)
		dev_err(&client->dev, "%s(%d)@%s:Reading of the query buffer is busy.\n", __FILE__, __LINE__, __func__);

#ifdef DEBUG_IT7260_TS
	dev_info(&client->dev, "Get the configuration version\n");
#endif

	/* 0x01, 0x06: the command of get the configuration version */
	buf[0] = 0x01;
	buf[1] = 0x06;
	i2c_master_write_it7260(client, CMD_BUF, buf, 2);

	count = 0;
	i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	while ((query & 0x01) && (count++ < QUERY_BUF_READ_MAX)) {
		udelay(1);
		i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	}
	if (count >= QUERY_BUF_READ_MAX)
		dev_err(&client->dev, "%s(%d)@%s:Reading of the query buffer is busy.\n", __FILE__, __LINE__, __func__);

#ifdef DEBUG_IT7260_TS
	dev_info(&client->dev, "Command status 0x%04x\n", query);
#endif

	memset(&buf, 0, sizeof(buf));
	i2c_master_read_it7260(client, CMD_RSP_BUF, buf, 7);

#ifdef DEBUG_IT7260_TS
	dev_info(&client->dev, "len = %d\n", buf[0]);
	dev_info(&client->dev, "Version : %02x.%02x.%02x.%02x\n", buf[1], buf[2], buf[3], buf[4]);
	dev_info(&client->dev, "Auto-tune Flag : %02x.%02x\n", buf[5], buf[6]);
#endif

	if (query || (buf[0] != 5 && buf[0] != 7)) {
		dev_err(&client->dev, "Command status error 0x%04x\n", query);
		return -1;
	}

	(*ver++) = buf[1];
	(*ver++) = buf[2];
	(*ver++) = buf[3];
	(*ver++) = buf[4];
	if (buf[0] == 7) {
		(*autotune++) = buf[5];
		(*autotune++) = buf[6];
	} else {
		(*autotune++) = 0;
		(*autotune++) = 0;
	}

	return 0;
}

static int it7260_set_capsensor_information(struct i2c_client *client, unsigned char enable, unsigned char type)
{
	unsigned char buf[5];
	unsigned char query = 0;
	unsigned long count;

	count = 0;
	i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	while ((query & 0x01) && (count++ < QUERY_BUF_READ_MAX)) {
		udelay(1);
		i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	}
	if (count >= QUERY_BUF_READ_MAX)
		dev_err(&client->dev, "%s(%d)@%s:Reading of the query buffer is busy.\n", __FILE__, __LINE__, __func__);

#ifdef DEBUG_IT7260_TS
	dev_info(&client->dev, "Set cap sensor\n");
#endif

	switch (enable) {
	case 0x00:
#ifdef DEBUG_IT7260_TS
		dev_info(&client->dev, "Interrupt Disable\n");
#endif
		break;
	case 0x01:
#ifdef DEBUG_IT7260_TS
		dev_info(&client->dev, "Interrupt Enable\n");
#endif
		break;
	default:
		dev_err(&client->dev, "invalid parameter enable = 0x%02x\n", enable);
		return -1;
		break;
	}

	switch (type) {
	case 0x00:
#ifdef DEBUG_IT7260_TS
		dev_info(&client->dev, "Low level trigger\n");
#endif
		break;
	case 0x01:
#ifdef DEBUG_IT7260_TS
		dev_info(&client->dev, "High level trigger\n");
#endif
		break;
	case 0x10:
#ifdef DEBUG_IT7260_TS
		dev_info(&client->dev, "Falling edge trigger\n");
#endif
		break;
	case 0x11:
#ifdef DEBUG_IT7260_TS
		dev_info(&client->dev, "Rising edge trigger\n");
#endif
		break;
	default:
		dev_err(&client->dev, "invalid parameter type = 0x%02x\n", type);
		return -1;
		break;
	}

	/* 0x02, 0x04: the command of interrupt notification status */
	buf[0] = 0x02;
	buf[1] = 0x04;
	buf[2] = enable;
	buf[3] = type;
	i2c_master_write_it7260(client, CMD_BUF, buf, 4);

	count = 0;
	i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	while ((query & 0x01) && (count++ < QUERY_BUF_READ_MAX)) {
		udelay(1);
		i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	}
	if (count >= QUERY_BUF_READ_MAX)
		dev_err(&client->dev, "%s(%d)@%s:Reading of the query buffer is busy.\n", __FILE__, __LINE__, __func__);

#ifdef DEBUG_IT7260_TS
	dev_info(&client->dev, "Command status 0x%04x\n", query);
#endif

	if (query) {
		dev_err(&client->dev, "Command status error 0x%04x\n", query);
		return -1;
	}

	return 0;
}

static int it7260_reset_queue(struct i2c_client *client)
{
	unsigned char buf[2];
	unsigned char query = 0;
	unsigned long count;

	count = 0;
	i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	while ((query & 0x01) && (count++ < QUERY_BUF_READ_MAX)) {
		udelay(1);
		i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	}
	if (count >= QUERY_BUF_READ_MAX)
		dev_err(&client->dev, "%s(%d)@%s:Reading of the query buffer is busy.\n", __FILE__, __LINE__, __func__);

#ifdef DEBUG_IT7260_TS
	dev_info(&client->dev, "Reset the queue\n");
#endif

	/* 0x07: the command of reset the queue */
	buf[0] = 0x07;
	i2c_master_write_it7260(client, CMD_BUF, buf, 1);

	count = 0;
	i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	while ((query & 0x01) && (count++ < QUERY_BUF_READ_MAX)) {
		udelay(1);
		i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	}
	if (count >= QUERY_BUF_READ_MAX)
		dev_err(&client->dev, "%s(%d)@%s:Reading of the query buffer is busy.\n", __FILE__, __LINE__, __func__);

#ifdef DEBUG_IT7260_TS
	dev_info(&client->dev, "Command status 0x%04x\n", query);
#endif

	return 0;
}

static int it7260_reset(struct i2c_client *client)
{
	unsigned char buf[2];
	unsigned char query = 0;
	unsigned long count;

	count = 0;
	i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	while ((query & 0x01) && (count++ < QUERY_BUF_READ_MAX)) {
		udelay(1);
		i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	}
	if (count >= QUERY_BUF_READ_MAX)
		dev_err(&client->dev, "%s(%d)@%s:Reading of the query buffer is busy.\n", __FILE__, __LINE__, __func__);

#ifdef DEBUG_IT7260_TS
	dev_info(&client->dev, "Reset IT7260\n");
#endif

	/* 0x6F: the command is used for reset IT7250/IT7260 */
	buf[0] = 0x6F;
	i2c_master_write_it7260(client, CMD_BUF, buf, 1);

	mdelay(200);

	count = 0;
	i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	while ((query & 0x01) && (count++ < QUERY_BUF_READ_MAX)) {
		udelay(1);
		i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
	}
	if (count >= QUERY_BUF_READ_MAX)
		dev_err(&client->dev, "%s(%d)@%s:Reading of the query buffer is busy.\n", __FILE__, __LINE__, __func__);

#ifdef DEBUG_IT7260_TS
	dev_info(&client->dev, "Command status 0x%04x\n", query);
#endif

	return 0;
}

static int it7260_ts_probe(struct i2c_client *client,
			const struct i2c_device_id *idp)
{
	struct it7260_ts_priv *priv;
	struct input_dev *input;
	int error;

	error = it7260_identify_capsensor(client);
	if (error) {
		dev_err(&client->dev, "cannot identify the touch screen\n");
		goto err0;
	}

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv) {
		dev_err(&client->dev, "failed to allocate driver data\n");
		error = -ENOMEM;
		goto err0;
	}

#ifdef RESET_IT7260_TS_IN_PROBE
	it7260_reset(client);

#endif /* RESET_IT7260_TS_IN_PROBE */
	mutex_init(&priv->mutex);

	dev_set_drvdata(&client->dev, priv);

	input = input_allocate_device();
	if (!input) {
		dev_err(&client->dev, "failed to allocate input device\n");
		error = -ENOMEM;
		goto err1;
	}

	input->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);

#if defined(USE_EVENT_KEY)
	input_set_capability(input, EV_KEY, KEY_MENU);
	input_set_capability(input, EV_KEY, KEY_BACK);
	input_set_capability(input, EV_KEY, KEY_HOME);
	input_set_capability(input, EV_KEY, KEY_POWER);

#endif
	input_set_abs_params(input, ABS_X, 0, SCREEN_X_RESOLUTION - 1, 0, 0);
	input_set_abs_params(input, ABS_Y, 0, SCREEN_Y_RESOLUTION - 1, 0, 0);
	input_set_abs_params(input, ABS_PRESSURE, 0, 16, 0, 0);

	input->name = "it7260 touch screen";
	input->phys = "I2C";
	input->id.bustype = BUS_I2C;
	input->dev.parent = &client->dev;

	input_set_drvdata(input, priv);

	priv->client = client;
	priv->input = input;
	INIT_DELAYED_WORK(&priv->work, it7260_ts_poscheck);
	if (machine_is_tz2000eva())
		gpio_no = GPIO_45;
	else
		gpio_no = GPIO_44;
	client->irq = gpio_to_irq(gpio_no);
	priv->irq = client->irq;

#if defined(USE_IRQ_LEVEL_LOW)
	error = it7260_set_capsensor_information(client, 0x01, 0x00);
#elif defined(USE_IRQ_LEVEL_HIGH)
	error = it7260_set_capsensor_information(client, 0x01, 0x01);
#elif defined(USE_IRQ_EDGE_FALLING)
	error = it7260_set_capsensor_information(client, 0x01, 0x10);
#elif defined(USE_IRQ_EDGE_RISING)
	error = it7260_set_capsensor_information(client, 0x01, 0x11);
#endif
	if (error) {
		dev_err(&client->dev, "cannot set identify the touch screen information\n");
		goto err0;
	}

	error = input_register_device(input);
	if (error) {
		dev_err(&client->dev, "failed to register input device\n");
		goto err1;
	}

#if defined(USE_TZ2000GPIO_INT)
#if defined(USE_IRQ_LEVEL_LOW)
#if defined(USE_TZ2000GPIO_LEVEL_INT)
	error = request_threaded_irq(priv->irq, NULL, it7260_ts_isr, IRQF_TRIGGER_LOW | IRQF_ONESHOT,
						client->name, priv);
#else
	error = request_threaded_irq(priv->irq, NULL, it7260_ts_isr, IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
						client->name, priv);
#endif
#elif defined(USE_IRQ_LEVEL_HIGH)
#if defined(USE_TZ2000GPIO_LEVEL_INT)
	error = request_threaded_irq(priv->irq, NULL, it7260_ts_isr, IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
						client->name, priv);
#else
	error = request_threaded_irq(priv->irq, NULL, it7260_ts_isr, IRQF_TRIGGER_RISING | IRQF_ONESHOT,
						client->name, priv);
#endif
#elif defined(USE_IRQ_EDGE_FALLING)
	error = request_threaded_irq(priv->irq, NULL, it7260_ts_isr, IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
						client->name, priv);
#elif defined(USE_IRQ_EDGE_RISING)
	error = request_threaded_irq(priv->irq, NULL, it7260_ts_isr, IRQF_TRIGGER_RISING | IRQF_ONESHOT,
						client->name, priv);
#endif
	if (error) {
		dev_err(&client->dev, "unable to request touchscreen IRQ\n");
		goto err2;
	}

#endif /* defined(USE_TZ2000GPIO_INT) */
	device_init_wakeup(&client->dev, 1);

	return 0;

err2:
	input_unregister_device(input);
	input = NULL;
err1:
	input_free_device(input);
	kfree(priv);
err0:
	dev_set_drvdata(&client->dev, NULL);
	return error;
}

static int __devexit it7260_ts_remove(struct i2c_client *client)
{
	struct it7260_ts_priv *priv = dev_get_drvdata(&client->dev);

#if defined(USE_TZ2000GPIO_INT)
	free_irq(priv->irq, priv);
#endif /* defined(USE_TZ2000GPIO_INT) */
	cancel_delayed_work_sync(&priv->work);
	input_unregister_device(priv->input);
	kfree(priv);

	dev_set_drvdata(&client->dev, NULL);

	return 0;
}

#ifndef DISABLE_I2C_DRIVER_PM
#ifdef CONFIG_PM
static int it7260_ts_suspend(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	int ret = -1;
	u8 suspend_cmd[] = {0x04, 0x00, 0x02};
	struct it7260_ts_priv *priv = i2c_get_clientdata(client);

	if (device_may_wakeup(&client->dev)) {
		enable_irq_wake(priv->irq);
		if (sizeof(suspend_cmd) == i2c_master_write_it7260(client,
					CMD_BUF, suspend_cmd, 3))
			ret = 0;
	}
	dev_err(&client->dev, "suspend touch screen\n");

	return ret;
}

static int it7260_ts_resume(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	int ret = -1;
	unsigned char query;
	struct it7260_ts_priv *priv = i2c_get_clientdata(client);

	if (device_may_wakeup(&client->dev)) {
		i2c_master_read_it7260(client, QUERY_BUF, &query, 1);
		disable_irq_wake(priv->irq);
		ret = 0;
	}
	dev_err(&client->dev, "resume touch screen\n");

	return ret;
}

static const struct dev_pm_ops it7260_ts_pm_ops = {
	SET_SYSTEM_SLEEP_PM_OPS(it7260_ts_suspend, it7260_ts_resume)
};
#endif
#endif

static const struct i2c_device_id it7260_ts_id[] = {
	{"IT7260", 0},
	{"IT7250", 1},
	{}			/* should not omit */
};
MODULE_DEVICE_TABLE(i2c, it7260_ts_id);

static struct i2c_driver it7260_ts_driver = {
	.driver = {
		.name	= "IT7260-ts",
		.owner		= THIS_MODULE,
#ifndef DISABLE_I2C_DRIVER_PM
#ifdef CONFIG_PM
		.pm		= &it7260_ts_pm_ops,
#endif
#endif
	},
	.probe = it7260_ts_probe,
	.remove = __devexit_p(it7260_ts_remove),
	.id_table = it7260_ts_id,
};

module_i2c_driver(it7260_ts_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("TOSHIBA Corporation");
MODULE_DESCRIPTION("it7260 touchscreen driver (single touch)");
