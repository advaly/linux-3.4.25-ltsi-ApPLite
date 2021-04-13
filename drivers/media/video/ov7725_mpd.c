/*
 * linux/drivers/media/video/ov7725_mpd.c
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
#define DEBUG
#define _DEBUG_OV7725

#include <linux/init.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/v4l2-mediabus.h>
#include <linux/videodev2.h>

#include <media/ov772x.h>
#include <media/soc_camera.h>
#include <media/v4l2-ctrls.h>
#include <media/v4l2-chip-ident.h>
#include <media/v4l2-subdev.h>

#ifdef DEBUG_OV7725
	#define dev_dbgmsg	dev_err
#else
	#define dev_dbgmsg(x, y, ...) { \
	}
#endif

#define VGA_WIDTH	640
#define VGA_HEIGHT	480
#define QVGA_WIDTH	320
#define QVGA_HEIGHT	240

#define OV7725_CSI2_QVGA_MBPS	250
#define OV7725_CSI2_VGA_MBPS	384


#define OV7725_CID_GREEN_BALANCE	(V4L2_CTRL_CLASS_CAMERA | 0x1001)

#define DEF_RED			0x40
#define DEF_BLUE		0x40
#define DEF_GREEN		0x40
#define DEF_GAIN		0x00
#define DEF_AEC			0x0000
#define DEF_AUTO		0x01
#define DEF_MANUAL		0x00

#define REG_GAIN		0x00
#define REG_BLUE		0x01
#define REG_RED			0x02
#define REG_GREEN		0x03
#define REG_AECH		0x08
#define REG_AEC			0x10
#define REG_COM8		0x13
#define COM8_AGC		0x04
#define COM8_AWB		0x02
#define COM8_AEC		0x01
#define REG_AEC			0x10

#define STR_AUTO		"auto"
#define STR_MANUAL		"manual"


struct ov7725_reg {
	u8 reg;
	u8 val;
};

struct ov7725_priv {
	struct v4l2_subdev	subdev;

	struct v4l2_ctrl_handler hdl;
	struct {
		/* exposure/autoexposure cluster */
		struct v4l2_ctrl *autoexposure;
		struct v4l2_ctrl *exposure;
	};
	struct {
		/* gain/autogain cluster */
		struct v4l2_ctrl *autogain;
		struct v4l2_ctrl *gain;
	};
	struct {
		/* blue/red/autowhitebalance cluster */
		struct v4l2_ctrl *autowb;
		struct v4l2_ctrl *red;
		struct v4l2_ctrl *blue;
		struct v4l2_ctrl *green;
	};

	int			model;

	int			width;
	int			height;
	int			current_enable;
	struct mutex lock;
};

static enum v4l2_mbus_pixelcode ov7725_codes[] = {
	V4L2_MBUS_FMT_UYVY8_2X8,
};

/*
 * size list
 */
static const struct {
	u32 width;
	u32 height;
} ov7725_framesizes[] = {
	{ VGA_WIDTH, VGA_HEIGHT},
	{ QVGA_WIDTH, QVGA_HEIGHT},
};

/* register setting */
/* 0x22 0xcc->0xf4 60Hz->50Hz*/
static const struct ov7725_reg ov7725_qvga_regs[] = {
	{0x3d, 0x03}, {0x17, 0x22}, {0x18, 0xa4}, {0x19, 0x07},
	{0x1a, 0xf0}, {0x32, 0x00}, {0x29, 0x50}, {0x2c, 0x78},
	{0x2a, 0x00}, {0x2b, 0x00}, {0x11, 0x00},

	{0x34, 0x01}, {0x33, 0x32}, {0x0c, 0x00},

	{0x42, 0x7f}, {0x4d, 0x09}, {0x63, 0xe0}, {0x64, 0xff},
	{0x65, 0x2f}, {0x66, 0x00}, {0x67, 0x48},

	{0x13, 0xf0}, {0x0d, 0x41}, {0x0f, 0xc5}, {0x14, 0x11},
	{0x22, 0xf4}, {0x23, 0x03}, {0x24, 0x40}, {0x25, 0x30},
	{0x26, 0xa1}, {0x2b, 0x00}, {0x6b, 0xaa}, {0x13, 0xff},

	{0x90, 0x05}, {0x91, 0x01}, {0x92, 0x03}, {0x93, 0x00},
	{0x94, 0xb0}, {0x95, 0x9d}, {0x96, 0x13}, {0x97, 0x16},
	{0x98, 0x7b}, {0x99, 0x91}, {0x9a, 0x1e}, {0x9b, 0x08},
	{0x9c, 0x20}, {0x9e, 0x81}, {0xa6, 0x04},

	{0x7e, 0x0c}, {0x7f, 0x16}, {0x80, 0x2a}, {0x81, 0x4e},
	{0x82, 0x61}, {0x83, 0x6f}, {0x84, 0x7b}, {0x85, 0x86},
	{0x86, 0x8e}, {0x87, 0x97}, {0x88, 0xa4}, {0x89, 0xaf},
	{0x8a, 0xc5}, {0x8b, 0xd7}, {0x8c, 0xe8}, {0x8d, 0x20},

	{0xff, 0xff},
};

static const struct ov7725_reg ov7725_vga_regs[] = {
	{0x3d, 0x03}, {0x17, 0x22}, {0x18, 0xa4}, {0x19, 0x07},
	{0x1a, 0xf0}, {0x32, 0x00}, {0x29, 0xa0}, {0x2c, 0xf0},
	{0x2a, 0x00}, {0x2b, 0x00}, {0x11, 0x00},

	{0x34, 0x01}, {0x33, 0x32}, {0x0c, 0x00},

	{0x42, 0x7f}, {0x4d, 0x09}, {0x63, 0xe0}, {0x64, 0xff},
	{0x65, 0x20}, {0x66, 0x00}, {0x67, 0x48},

	{0x13, 0xf0}, {0x0d, 0x41}, {0x0f, 0xc5}, {0x14, 0x11},
	{0x22, 0xf4}, {0x23, 0x03}, {0x24, 0x40}, {0x25, 0x30},
	{0x26, 0xa1}, {0x6b, 0xaa}, {0x13, 0xff},

	{0x90, 0x05}, {0x91, 0x01}, {0x92, 0x03}, {0x93, 0x00},
	{0x94, 0xb0}, {0x95, 0x9d}, {0x96, 0x13}, {0x97, 0x16},
	{0x98, 0x7b}, {0x99, 0x91}, {0x9a, 0x1e}, {0x9b, 0x08},
	{0x9c, 0x20}, {0x9e, 0x81}, {0xa6, 0x04},

	{0x7e, 0x0c}, {0x7f, 0x16}, {0x80, 0x2a}, {0x81, 0x4e},
	{0x82, 0x61}, {0x83, 0x6f}, {0x84, 0x7b}, {0x85, 0x86},
	{0x86, 0x8e}, {0x87, 0x97}, {0x88, 0xa4}, {0x89, 0xaf},
	{0x8a, 0xc5}, {0x8b, 0xd7}, {0x8c, 0xe8}, {0x8d, 0x20},

	{0xff, 0xff},
};

/* MPD */
#define MPD_ADDR_OFFSET		(0x21 - 0x07)

struct ov7725_mpd_reg {
	u16 reg;
	u16 val;
};

static struct ov7725_mpd_reg ov7725_mpd_qvga_regs[] = {
	{0x0006, 0x0190}, {0x0008, 0x0060}, {0x0022, 0x0280},

	{0x0140, 0x0000}, {0x0142, 0x0000}, {0x0144, 0x0000}, {0x0146, 0x0000},
	{0x0148, 0x0001}, {0x014a, 0x0000}, {0x014c, 0x0001}, {0x014e, 0x0000},
	{0x0150, 0x0001}, {0x0152, 0x0000},

	{0x0210, 0x7530}, {0x0212, 0x0000}, {0x0214, 0x0002}, {0x0216, 0x0000},
	{0x0218, 0x0c01}, {0x021a, 0x0000}, {0x0220, 0x0102}, {0x0222, 0x0000},
	{0x0224, 0x4a38}, {0x0226, 0x0000}, {0x022c, 0x0000}, {0x022e, 0x0000},
	{0x0230, 0x0005}, {0x0232, 0x0000}, {0x0234, 0x0003}, {0x0236, 0x0000},
	{0x0238, 0x0001}, {0x023a, 0x0000}, {0x0204, 0x0001}, {0x0206, 0x0000},
	{0x0518, 0x0001}, {0x051a, 0x0000},

	{0x0500, 0x8081}, {0x0502, 0xa300}, {0x0004, 0x8064},

	{0xffff, 0xffff},
};

static struct ov7725_mpd_reg ov7725_mpd_vga_regs[] = {
	{0x0006, 0x0190}, {0x0008, 0x0060}, {0x0022, 0x0500},

	{0x0140, 0x0000}, {0x0142, 0x0000}, {0x0144, 0x0000}, {0x0146, 0x0000},
	{0x0148, 0x0001}, {0x014a, 0x0000}, {0x014c, 0x0001}, {0x014e, 0x0000},
	{0x0150, 0x0001}, {0x0152, 0x0000},

	{0x0210, 0x7530}, {0x0212, 0x0000}, {0x0214, 0x0002}, {0x0216, 0x0000},
	{0x0218, 0x0c02}, {0x021a, 0x0000}, {0x0220, 0x0102}, {0x0222, 0x0000},
	{0x0224, 0x4a38}, {0x0226, 0x0000}, {0x022c, 0x0000}, {0x022e, 0x0000},
	{0x0230, 0x0005}, {0x0232, 0x0000}, {0x0234, 0x0003}, {0x0236, 0x0000},
	{0x0238, 0x0001}, {0x023a, 0x0000}, {0x0204, 0x0001}, {0x0206, 0x0000},
	{0x0518, 0x0001}, {0x051a, 0x0000},

	{0x0500, 0x8081}, {0x0502, 0xa300}, {0x0004, 0x8064},

	{0xffff, 0xffff},
};

static struct ov7725_priv *to_ov7725(const struct i2c_client *client)
{
	return container_of(i2c_get_clientdata(client),
				struct ov7725_priv, subdev);
}

static int ov7725_reg_read(struct i2c_client *client, u8 addr)
{
	i2c_smbus_write_byte(client, addr);
	return i2c_smbus_read_byte(client);
}

static int ov7725_reg_write(struct i2c_client *client, u8 addr, u8 data)
{
	return i2c_smbus_write_byte_data(client, addr, data);
}

static int ov7725_write_regs(struct i2c_client *client,
			      const struct ov7725_reg *regs)
{
	while (regs->reg != 0xff) {
		int ret = ov7725_reg_write(client, regs->reg, regs->val);
		if (ret < 0)
			return ret;
		regs++;
	}
	return 0;
}

static void reg_dump(struct i2c_client *client)
{
#ifdef DEBUG_OV7725
	dev_dbgmsg(&client->dev, "0x13 COM8  0x%02x\n", ov7725_reg_read(client, 0x13));
	dev_dbgmsg(&client->dev, "0x00 GAIN  0x%02x\n", ov7725_reg_read(client, 0x00));
	dev_dbgmsg(&client->dev, "0x01 BLUE  0x%02x\n", ov7725_reg_read(client, 0x01));
	dev_dbgmsg(&client->dev, "0x02 RED   0x%02x\n", ov7725_reg_read(client, 0x02));
	dev_dbgmsg(&client->dev, "0x03 GREEN 0x%02x\n", ov7725_reg_read(client, 0x03));
	dev_dbgmsg(&client->dev, "0x10 AEC   0x%02x\n", ov7725_reg_read(client, 0x10));
	dev_dbgmsg(&client->dev, "0x08 AECH  0x%02x\n", ov7725_reg_read(client, 0x08));
	dev_dbgmsg(&client->dev, "0x12 COM7  0x%02x\n", ov7725_reg_read(client, 0x12));
	dev_dbgmsg(&client->dev, "0x69 AWBC1 0x%02x\n", ov7725_reg_read(client, 0x69));
#endif
}

static int ov7725_get_com8(struct i2c_client *client, unsigned char mode)
{
	int ret;

	dev_dbgmsg(&client->dev, "%s: start mode=0x%x\n", __func__, mode);
	ret = ov7725_reg_read(client, REG_COM8);
	if (ret < 0)
		return ret;

	/* get mode auto or manual */
	switch (mode) {
	case COM8_AEC:
		ret = (ret & COM8_AEC) ? V4L2_EXPOSURE_AUTO : V4L2_EXPOSURE_MANUAL;
		break;
	case COM8_AWB:
		ret = (ret & COM8_AWB) ? DEF_AUTO : DEF_MANUAL;
		break;
	case COM8_AGC:
		ret = (ret & COM8_AGC) ? DEF_AUTO : DEF_MANUAL;
		break;
	default:
		ret = -EINVAL;
		break;
	}
	dev_dbgmsg(&client->dev, "%s: ret=%d\n", __func__, ret);
	return ret;
}

static int ov7725_set_com8(struct i2c_client *client, unsigned char mode, unsigned char val)
{
	int ret, reg_val;

	dev_dbgmsg(&client->dev, "%s: start mode=0x%x val=%d\n", __func__, mode, val);
	reg_val = ov7725_reg_read(client, REG_COM8);
	if (reg_val < 0)
		return reg_val;

	/* set mode auto or manual */
	switch (mode) {
	case COM8_AEC:
		if (val) /* V4L2_EXPOSURE_MANUAL */
			reg_val &= ~COM8_AEC;
		else /* V4L2_EXPOSURE_AUTO */
			reg_val |= COM8_AEC;
		ret = ov7725_reg_write(client, REG_COM8, (u8)reg_val);
		break;
	case COM8_AWB:
		if (!val) /* DEF_MANUAL */
			reg_val &= ~COM8_AWB;
		else /* DEF_AUTO */
			reg_val |= COM8_AWB;
		ret = ov7725_reg_write(client, REG_COM8, (u8)reg_val);
		break;
	case COM8_AGC:
		if (!val) /* DEF_MANUAL */
			reg_val &= ~COM8_AGC;
		else /* DEF_AUTO */
			reg_val |= COM8_AGC;
		ret = ov7725_reg_write(client, REG_COM8, (u8)reg_val);
		break;
	default:
		ret = -EINVAL;
		dev_dbgmsg(&client->dev, "%s: ret=%d\n", __func__, ret);
		break;
	}
	return ret;
}

static unsigned long ov7725_strtoul(const char *buf, size_t count, size_t *cnt)
{
	unsigned long val;
	char *endp;

	val = simple_strtoul(buf, &endp, 10);
	*cnt = 0;
	if (val <= 0xFFFF)
		*cnt = (size_t)(endp - buf);
	if ((*cnt) && (count == *cnt+1) && (buf[*cnt] == '\n'))
		*cnt += 1;
	return val;
}

static ssize_t ov7725_wb_query_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
{
	ssize_t count;
	struct i2c_client *client = to_i2c_client(dev);
	struct ov7725_priv *priv = to_ov7725(client);

	count = sprintf(buf, "%u,%u,%u\n",
		priv->red->minimum, priv->red->maximum, priv->red->default_value);

	return count;
}

static ssize_t ov7725_wb_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
{
	int ret;
	ssize_t count;
	struct i2c_client *client = to_i2c_client(dev);
	struct ov7725_priv *priv = to_ov7725(client);

	mutex_lock(&priv->lock);
	ret = ov7725_get_com8(client, COM8_AWB);
	if (ret < 0) {
		mutex_unlock(&priv->lock);
		return ret;
	}

	reg_dump(client);
	count = sprintf(buf, "%s\n", ((ret) ? STR_AUTO : STR_MANUAL));

	mutex_unlock(&priv->lock);
	return count;
}

static ssize_t ov7725_wb_store(struct device *dev, struct device_attribute *dev_attr, const char *buf, size_t count)
{
	int ret;
	size_t cnt;
	struct i2c_client *client = to_i2c_client(dev);
	struct ov7725_priv *priv = to_ov7725(client);

	mutex_lock(&priv->lock);
	if (buf[count-1] == '\n')
		cnt = count - 1;
	else
		cnt = count;

	/* check auto mode */
	ret = strnicmp(buf, STR_AUTO, cnt);
	if (!ret) {
		/* set auto mode */
		ret = ov7725_set_com8(client, COM8_AWB, DEF_AUTO);
		if (ret < 0) {
			mutex_unlock(&priv->lock);
			return ret;
		}
		dev_dbgmsg(&client->dev, "%s:%s\n", __func__, buf);
		mutex_unlock(&priv->lock);
		return count;
	}

	/* check manual mode */
	ret = strnicmp(buf, STR_MANUAL, cnt);
	if (!ret) {
		/* set manual mode */
		ret = ov7725_set_com8(client, COM8_AWB, DEF_MANUAL);
		if (ret < 0) {
			mutex_unlock(&priv->lock);
			return ret;
		}
		dev_dbgmsg(&client->dev, "%s:%s\n", __func__, buf);
		mutex_unlock(&priv->lock);
		return count;
	}

	dev_err(&client->dev, "%s: value error :%s\n", __func__, buf);
	mutex_unlock(&priv->lock);
	return -EINVAL;
}

static ssize_t ov7725_red_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
{
	int ret;
	ssize_t count;
	struct i2c_client *client = to_i2c_client(dev);
	struct ov7725_priv *priv = to_ov7725(client);

	mutex_lock(&priv->lock);
	ret = ov7725_reg_read(client, REG_RED);
	if (ret < 0) {
		mutex_unlock(&priv->lock);
		return ret;
	}

	count = sprintf(buf, "%u\n", ret & 0xFF);

	mutex_unlock(&priv->lock);
	return count;
}

static ssize_t ov7725_red_store(struct device *dev, struct device_attribute *dev_attr, const char *buf, size_t count)
{
	int ret;
	size_t cnt;
	u32 reg_val;
	struct i2c_client *client = to_i2c_client(dev);
	struct ov7725_priv *priv = to_ov7725(client);

	mutex_lock(&priv->lock);
	reg_val = ov7725_strtoul(buf, count, &cnt);
	if (reg_val > priv->red->maximum || !cnt) {
		dev_err(&client->dev, "%s: value error :%s\n", __func__, buf);
		mutex_unlock(&priv->lock);
		return -EINVAL;
	} else {
		/* set manual mode */
		ret = ov7725_set_com8(client, COM8_AWB, DEF_MANUAL);
		if (ret < 0) {
			mutex_unlock(&priv->lock);
			return ret;
		}
		/* set manual value */
		ret = ov7725_reg_write(client, REG_RED, (u8)reg_val);
		if (ret < 0) {
			mutex_unlock(&priv->lock);
			return ret;
		}
	}
	dev_dbgmsg(&client->dev, "%s: value=%d\n", __func__, reg_val);
	mutex_unlock(&priv->lock);
	return count;
}

static ssize_t ov7725_blue_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
{
	int ret;
	ssize_t count;
	struct i2c_client *client = to_i2c_client(dev);
	struct ov7725_priv *priv = to_ov7725(client);

	mutex_lock(&priv->lock);
	ret = ov7725_reg_read(client, REG_BLUE);
	if (ret < 0) {
		mutex_unlock(&priv->lock);
		return ret;
	}

	count = sprintf(buf, "%u\n", ret & 0xFF);

	mutex_unlock(&priv->lock);
	return count;
}

static ssize_t ov7725_blue_store(struct device *dev, struct device_attribute *dev_attr, const char *buf, size_t count)
{
	int ret;
	size_t cnt;
	u32 reg_val;
	struct i2c_client *client = to_i2c_client(dev);
	struct ov7725_priv *priv = to_ov7725(client);

	mutex_lock(&priv->lock);
	reg_val = ov7725_strtoul(buf, count, &cnt);
	if (reg_val > priv->blue->maximum || !cnt) {
		dev_err(&client->dev, "%s: value error :%s\n", __func__, buf);
		mutex_unlock(&priv->lock);
		return -EINVAL;
	} else {
		/* set manual mode */
		ret = ov7725_set_com8(client, COM8_AWB, DEF_MANUAL);
		if (ret < 0) {
			mutex_unlock(&priv->lock);
			return ret;
		}
		/* set manual value */
		ret = ov7725_reg_write(client, REG_BLUE, (u8)reg_val);
		if (ret < 0) {
			mutex_unlock(&priv->lock);
			return ret;
		}
	}
	dev_dbgmsg(&client->dev, "%s: value=%d\n", __func__, reg_val);
	mutex_unlock(&priv->lock);
	return count;
}

static ssize_t ov7725_green_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
{
	int ret;
	ssize_t count;
	struct i2c_client *client = to_i2c_client(dev);
	struct ov7725_priv *priv = to_ov7725(client);

	mutex_lock(&priv->lock);
	ret = ov7725_reg_read(client, REG_GREEN);
	if (ret < 0) {
		mutex_unlock(&priv->lock);
		return ret;
	}

	count = sprintf(buf, "%u\n", ret & 0xFF);

	mutex_unlock(&priv->lock);
	return count;
}

static ssize_t ov7725_green_store(struct device *dev, struct device_attribute *dev_attr, const char *buf, size_t count)
{
	int ret;
	size_t cnt;
	u32 reg_val;
	struct i2c_client *client = to_i2c_client(dev);
	struct ov7725_priv *priv = to_ov7725(client);

	mutex_lock(&priv->lock);
	reg_val = ov7725_strtoul(buf, count, &cnt);
	if (reg_val > priv->green->maximum || !cnt) {
		dev_err(&client->dev, "%s: value error :%s\n", __func__, buf);
		mutex_unlock(&priv->lock);
		return -EINVAL;
	} else {
		/* set manual mode */
		ret = ov7725_set_com8(client, COM8_AWB, DEF_MANUAL);
		if (ret < 0) {
			mutex_unlock(&priv->lock);
			return ret;
		}
		/* set manual value */
		ret = ov7725_reg_write(client, REG_GREEN, (u8)reg_val);
		if (ret < 0) {
			mutex_unlock(&priv->lock);
			return ret;
		}
	}
	dev_dbgmsg(&client->dev, "%s: value=%d\n", __func__, reg_val);
	mutex_unlock(&priv->lock);
	return count;
}

static ssize_t ov7725_gain_query_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
{
	ssize_t count;
	struct i2c_client *client = to_i2c_client(dev);
	struct ov7725_priv *priv = to_ov7725(client);

	count = sprintf(buf, "%u,%u,%u\n",
		priv->gain->minimum, priv->gain->maximum, priv->gain->default_value);

	return count;
}

static ssize_t ov7725_gain_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
{
	int ret, val;
	ssize_t count;
	struct i2c_client *client = to_i2c_client(dev);
	struct ov7725_priv *priv = to_ov7725(client);

	mutex_lock(&priv->lock);
	ret = ov7725_get_com8(client, COM8_AGC);
	if (ret < 0) {
		mutex_unlock(&priv->lock);
		return ret;
	}

	val = ov7725_reg_read(client, REG_GAIN);
	if (val < 0) {
		mutex_unlock(&priv->lock);
		return val;
	}

	reg_dump(client);
	count = sprintf(buf, "%s,%u\n", ((ret) ? STR_AUTO : STR_MANUAL), val & 0xFF);

	mutex_unlock(&priv->lock);
	return count;
}

static ssize_t ov7725_gain_store(struct device *dev, struct device_attribute *dev_attr, const char *buf, size_t count)
{
	int ret;
	size_t cnt;
	u32 reg_val;
	struct i2c_client *client = to_i2c_client(dev);
	struct ov7725_priv *priv = to_ov7725(client);

	mutex_lock(&priv->lock);
	if (buf[count-1] == '\n')
		ret = strnicmp(buf, STR_AUTO, count-1);
	else
		ret = strnicmp(buf, STR_AUTO, count);

	if (!ret) {
		/* set auto mode */
		ret = ov7725_set_com8(client, COM8_AGC, DEF_AUTO);
		if (ret < 0) {
			mutex_unlock(&priv->lock);
			return ret;
		}
		dev_dbgmsg(&client->dev, "%s: %s\n", __func__, buf);
	} else {
		reg_val = ov7725_strtoul(buf, count, &cnt);
		if (reg_val > priv->gain->maximum || !cnt) {
			dev_err(&client->dev, "%s: value error :%s\n", __func__, buf);
			mutex_unlock(&priv->lock);
			return -EINVAL;
		} else {
			/* set manual mode */
			ret = ov7725_set_com8(client, COM8_AGC, DEF_MANUAL);
			if (ret < 0) {
				mutex_unlock(&priv->lock);
				return ret;
			}
			ret = ov7725_reg_write(client, REG_GAIN, (u8)reg_val);
			if (ret < 0) {
				mutex_unlock(&priv->lock);
				return ret;
			}
			dev_dbgmsg(&client->dev, "%s:manual value=%d\n", __func__, reg_val);
		}
	}
	mutex_unlock(&priv->lock);
	return count;
}

static ssize_t ov7725_exp_query_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
{
	ssize_t count;
	struct i2c_client *client = to_i2c_client(dev);
	struct ov7725_priv *priv = to_ov7725(client);

	count = sprintf(buf, "%u,%u,%u\n",
		priv->exposure->minimum, priv->exposure->maximum, priv->exposure->default_value);

	return count;
}

static ssize_t ov7725_exp_show(struct device *dev, struct device_attribute *dev_attr, char *buf)
{
	int ret, val, val2;
	ssize_t count;
	struct i2c_client *client = to_i2c_client(dev);
	struct ov7725_priv *priv = to_ov7725(client);

	mutex_lock(&priv->lock);
	ret = ov7725_get_com8(client, COM8_AEC);
	if (ret < 0) {
		mutex_unlock(&priv->lock);
		return ret;
	}

	val = ov7725_reg_read(client, REG_AEC);
	if (val < 0) {
		mutex_unlock(&priv->lock);
		return val;
	}
	val2 = ov7725_reg_read(client, REG_AECH);
	if (val2 < 0) {
		mutex_unlock(&priv->lock);
		return val2;
	}

	reg_dump(client);
	count = sprintf(buf, "%s,%u\n", ((!ret) ? STR_AUTO : STR_MANUAL),
		((val2 & 0xFF)<<8 | (val & 0xFF)));

	mutex_unlock(&priv->lock);
	return count;
}

static ssize_t ov7725_exp_store(struct device *dev, struct device_attribute *dev_attr, const char *buf, size_t count)
{
	int ret;
	size_t cnt;
	u32 reg_val;
	struct i2c_client *client = to_i2c_client(dev);
	struct ov7725_priv *priv = to_ov7725(client);

	mutex_lock(&priv->lock);
	if (buf[count-1] == '\n')
		ret = strnicmp(buf, STR_AUTO, count-1);
	else
		ret = strnicmp(buf, STR_AUTO, count);

	if (!ret) {
		/* set auto mode */
		ret = ov7725_set_com8(client, COM8_AEC, V4L2_EXPOSURE_AUTO);
		if (ret < 0) {
			mutex_unlock(&priv->lock);
			return ret;
		}
		dev_dbgmsg(&client->dev, "%s: %s\n", __func__, buf);
	} else {
		reg_val = ov7725_strtoul(buf, count, &cnt);
		if (reg_val > priv->exposure->maximum || !cnt) {
			dev_err(&client->dev, "%s: value error :%s\n", __func__, buf);
			mutex_unlock(&priv->lock);
			return -EINVAL;
		} else {
			/* set manual mode */
			ret = ov7725_set_com8(client, COM8_AEC, V4L2_EXPOSURE_MANUAL);
			if (ret < 0) {
				mutex_unlock(&priv->lock);
				return ret;
			}
			ret = ov7725_reg_write(client, REG_AEC, reg_val & 0xFF);
			if (ret < 0) {
				mutex_unlock(&priv->lock);
				return ret;
			}
			ret = ov7725_reg_write(client, REG_AECH, (reg_val >> 8) & 0xFF);
			if (ret < 0) {
				mutex_unlock(&priv->lock);
				return ret;
			}
			dev_dbgmsg(&client->dev, "%s:manual value=%d\n", __func__, reg_val);
		}
	}
	mutex_unlock(&priv->lock);
	return count;
}

static DEVICE_ATTR(wb_q, S_IRUGO, ov7725_wb_query_show, NULL);
static DEVICE_ATTR(wb, S_IRUGO | S_IWUSR, ov7725_wb_show, ov7725_wb_store);
static DEVICE_ATTR(red, S_IRUGO | S_IWUSR, ov7725_red_show, ov7725_red_store);
static DEVICE_ATTR(blue, S_IRUGO | S_IWUSR, ov7725_blue_show, ov7725_blue_store);
static DEVICE_ATTR(green, S_IRUGO | S_IWUSR, ov7725_green_show, ov7725_green_store);
static DEVICE_ATTR(gain_q, S_IRUGO, ov7725_gain_query_show, NULL);
static DEVICE_ATTR(gain, S_IRUGO | S_IWUSR, ov7725_gain_show, ov7725_gain_store);
static DEVICE_ATTR(exp_q, S_IRUGO, ov7725_exp_query_show, NULL);
static DEVICE_ATTR(exp, S_IRUGO | S_IWUSR, ov7725_exp_show, ov7725_exp_store);

static int ov7725_attr_create(struct i2c_client *client)
{
	int ret;

	ret = device_create_file(&client->dev, &dev_attr_wb_q);
	if (ret < 0) {
		dev_dbgmsg(&client->dev, "%s:wb_q create error(%d)\n", __func__, ret);
		goto err1;
	}
	ret = device_create_file(&client->dev, &dev_attr_wb);
	if (ret < 0) {
		dev_dbgmsg(&client->dev, "%s:wb create error(%d)\n", __func__, ret);
		goto err2;
	}
	ret = device_create_file(&client->dev, &dev_attr_red);
	if (ret < 0) {
		dev_dbgmsg(&client->dev, "%s:red create error(%d)\n", __func__, ret);
		goto err3;
	}
	ret = device_create_file(&client->dev, &dev_attr_blue);
	if (ret < 0) {
		dev_dbgmsg(&client->dev, "%s:blue create error(%d)\n", __func__, ret);
		goto err4;
	}
	ret = device_create_file(&client->dev, &dev_attr_green);
	if (ret < 0) {
		dev_dbgmsg(&client->dev, "%s:green create error(%d)\n", __func__, ret);
		goto err5;
	}
	ret = device_create_file(&client->dev, &dev_attr_gain_q);
	if (ret < 0) {
		dev_dbgmsg(&client->dev, "%s:gain_q create error(%d)\n", __func__, ret);
		goto err6;
	}
	ret = device_create_file(&client->dev, &dev_attr_gain);
	if (ret < 0) {
		dev_dbgmsg(&client->dev, "%s:gain create error(%d)\n", __func__, ret);
		goto err7;
	}
	ret = device_create_file(&client->dev, &dev_attr_exp_q);
	if (ret < 0) {
		dev_dbgmsg(&client->dev, "%s:exp_q create error(%d)\n", __func__, ret);
		goto err8;
	}
	ret = device_create_file(&client->dev, &dev_attr_exp);
	if (ret < 0) {
		dev_dbgmsg(&client->dev, "%s:exp create error(%d)\n", __func__, ret);
		goto err9;
	}
	return 0;

err9:
	dev_dbgmsg(&client->dev, "%s:exp_q remove\n", __func__);
	device_remove_file(&client->dev, &dev_attr_exp_q);
err8:
	dev_dbgmsg(&client->dev, "%s:gain remove\n", __func__);
	device_remove_file(&client->dev, &dev_attr_gain);
err7:
	dev_dbgmsg(&client->dev, "%s:gain_q remove\n", __func__);
	device_remove_file(&client->dev, &dev_attr_gain_q);
err6:
	dev_dbgmsg(&client->dev, "%s:green remove\n", __func__);
	device_remove_file(&client->dev, &dev_attr_green);
err5:
	dev_dbgmsg(&client->dev, "%s:blue remove\n", __func__);
	device_remove_file(&client->dev, &dev_attr_blue);
err4:
	dev_dbgmsg(&client->dev, "%s:red remove\n", __func__);
	device_remove_file(&client->dev, &dev_attr_red);
err3:
	dev_dbgmsg(&client->dev, "%s:wb remove\n", __func__);
	device_remove_file(&client->dev, &dev_attr_wb);
err2:
	dev_dbgmsg(&client->dev, "%s:wb_q remove\n", __func__);
	device_remove_file(&client->dev, &dev_attr_wb_q);
err1:
	return ret;
}

static void ov7725_attr_remove(struct i2c_client *client)
{
	device_remove_file(&client->dev, &dev_attr_wb_q);
	device_remove_file(&client->dev, &dev_attr_wb);
	device_remove_file(&client->dev, &dev_attr_red);
	device_remove_file(&client->dev, &dev_attr_blue);
	device_remove_file(&client->dev, &dev_attr_green);
	device_remove_file(&client->dev, &dev_attr_gain_q);
	device_remove_file(&client->dev, &dev_attr_gain);
	device_remove_file(&client->dev, &dev_attr_exp_q);
	device_remove_file(&client->dev, &dev_attr_exp);

	dev_dbgmsg(&client->dev, "%s:removed\n", __func__);
	return;
}

/* Get status of additional camera capabilities */
static int ov7725_g_volatile_ctrl(struct v4l2_ctrl *ctrl)
{
	struct ov7725_priv *priv = container_of(ctrl->handler, struct ov7725_priv, hdl);
	struct v4l2_subdev *sd = &priv->subdev;
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int ret = 0;
	int val, val2;

	dev_dbgmsg(&client->dev, "%s:CID=0x%x\n", __func__, ctrl->id);
	mutex_lock(&priv->lock);

	switch (ctrl->id) {
	case V4L2_CID_AUTO_WHITE_BALANCE:
		ret = ov7725_get_com8(client, COM8_AWB);
		if (ret < 0)
			goto unlock;
		priv->autowb->val = ret;
		dev_dbgmsg(&client->dev, "%s:auto value=%d\n", __func__, priv->autowb->val);
		break;
	case V4L2_CID_RED_BALANCE:
		ret = ov7725_reg_read(client, REG_RED);
		if (ret < 0)
			goto unlock;
		priv->red->val = ret;
		dev_dbgmsg(&client->dev, "%s:red value=%d\n", __func__, priv->red->val);
		break;
	case V4L2_CID_BLUE_BALANCE:
		ret = ov7725_reg_read(client, REG_BLUE);
		if (ret < 0)
			goto unlock;
		priv->blue->val = ret;
		dev_dbgmsg(&client->dev, "%s:blue value=%d\n", __func__, priv->blue->val);
		break;
	case OV7725_CID_GREEN_BALANCE:
		ret = ov7725_reg_read(client, REG_GREEN);
		if (ret < 0)
			goto unlock;
		priv->green->val = ret;
		dev_dbgmsg(&client->dev, "%s:green value=%d\n", __func__, priv->green->val);
		break;
	case V4L2_CID_AUTOGAIN:
		ret = ov7725_get_com8(client, COM8_AGC);
		if (ret < 0)
			goto unlock;
		priv->autogain->val = ret;
		dev_dbgmsg(&client->dev, "%s:auto value=%d\n", __func__, priv->autogain->val);
		break;
	case V4L2_CID_GAIN:
		ret = ov7725_reg_read(client, REG_GAIN);
		if (ret < 0)
			goto unlock;
		priv->gain->val = ret;
		dev_dbgmsg(&client->dev, "%s:gain value=%d\n", __func__, priv->gain->val);
		break;
	case V4L2_CID_EXPOSURE_AUTO:
		ret = ov7725_get_com8(client, COM8_AEC);
		if (ret < 0)
			goto unlock;
		priv->autoexposure->val = ret;
		dev_dbgmsg(&client->dev, "%s:auto value=%d\n", __func__, priv->autoexposure->val);
		break;
	case V4L2_CID_EXPOSURE:
		val = ov7725_reg_read(client, REG_AEC);
		if (val < 0) {
			ret = val;
			goto unlock;
		}
		val2 = ov7725_reg_read(client, REG_AECH);
		if (val2 < 0) {
			ret = val2;
			goto unlock;
		}
		priv->exposure->val = ((val2 & 0xFF) << 8) | (val & 0xFF);
		dev_dbgmsg(&client->dev, "%s:exp value=%d\n", __func__, priv->exposure->val);
		break;
	default:
		dev_err(&client->dev, "%s:not support CID\n", __func__);
		ret = -EINVAL;
		break;
	}

unlock:
	mutex_unlock(&priv->lock);
	if (ret < 0)
		return ret;
	return 0;
}

/* Set status of additional camera capabilities */
static int ov7725_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct ov7725_priv *priv = container_of(ctrl->handler, struct ov7725_priv, hdl);
	struct v4l2_subdev *sd = &priv->subdev;
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int ret = 0;

	dev_dbgmsg(&client->dev, "%s:CID=0x%x\n", __func__, ctrl->id);
	mutex_lock(&priv->lock);

	switch (ctrl->id) {
	case V4L2_CID_AUTO_WHITE_BALANCE:
		/* set auto mode */
		ret = ov7725_set_com8(client, COM8_AWB, ctrl->val ? DEF_AUTO : DEF_MANUAL);
		if (ret < 0)
			goto unlock;
		dev_dbgmsg(&client->dev, "%s:value=%d\n", __func__, ctrl->val);
		break;
	case V4L2_CID_RED_BALANCE:
		if (ctrl->val > ctrl->maximum) {
			dev_err(&client->dev, "%s:error value=%d\n", __func__, ctrl->val);
			ret = -EINVAL;
			goto unlock;
		}
		/* set manual mode */
		ret = ov7725_set_com8(client, COM8_AWB, DEF_MANUAL);
		if (ret < 0)
			goto unlock;
		priv->autowb->cur.val = DEF_MANUAL; /* change current auto */
		/* set manual value */
		ret = ov7725_reg_write(client, REG_RED, (u8)ctrl->val);
		if (ret < 0)
			goto unlock;
		dev_dbgmsg(&client->dev, "%s:value=%d\n", __func__, ctrl->val);
		break;
	case V4L2_CID_BLUE_BALANCE:
		if (ctrl->val > ctrl->maximum) {
			dev_err(&client->dev, "%s:error value=%d\n", __func__, ctrl->val);
			ret = -EINVAL;
			goto unlock;
		}
		/* set manual mode */
		ret = ov7725_set_com8(client, COM8_AWB, DEF_MANUAL);
		if (ret < 0)
			goto unlock;
		priv->autowb->cur.val = DEF_MANUAL; /* change current auto */
		/* set manual value */
		ret = ov7725_reg_write(client, REG_BLUE, (u8)ctrl->val);
		if (ret < 0)
			goto unlock;
		dev_dbgmsg(&client->dev, "%s:value=%d\n", __func__, ctrl->val);
		break;
	case OV7725_CID_GREEN_BALANCE:
		if (ctrl->val > ctrl->maximum) {
			dev_err(&client->dev, "%s:error value=%d\n", __func__, ctrl->val);
			ret = -EINVAL;
			goto unlock;
		}
		/* set manual mode */
		ret = ov7725_set_com8(client, COM8_AWB, DEF_MANUAL);
		if (ret < 0)
			goto unlock;
		priv->autowb->cur.val = DEF_MANUAL; /* change current auto */
		/* set manual value */
		ret = ov7725_reg_write(client, REG_GREEN, (u8)ctrl->val);
		if (ret < 0)
			goto unlock;
		dev_dbgmsg(&client->dev, "%s:value=%d\n", __func__, ctrl->val);
		break;
	case V4L2_CID_AUTOGAIN:
		/* set auto mode */
		ret = ov7725_set_com8(client, COM8_AGC, ctrl->val ? DEF_AUTO : DEF_MANUAL);
		if (ret < 0)
			goto unlock;
		dev_dbgmsg(&client->dev, "%s:value=%d\n", __func__, ctrl->val);
		break;
	case V4L2_CID_GAIN:
		if (ctrl->val > ctrl->maximum) {
			dev_err(&client->dev, "%s:error value=%d\n", __func__, ctrl->val);
			ret = -EINVAL;
			goto unlock;
		}
		/* set manual mode */
		ret = ov7725_set_com8(client, COM8_AGC, DEF_MANUAL);
		if (ret < 0)
			goto unlock;
		priv->autogain->cur.val = DEF_MANUAL; /* change current auto */
		ret = ov7725_reg_write(client, REG_GAIN, (u8)ctrl->val);
		if (ret < 0)
			goto unlock;
		dev_dbgmsg(&client->dev, "%s:value=%d\n", __func__, ctrl->val);
		break;
	case V4L2_CID_EXPOSURE_AUTO:
		/* set auto mode */
		ret = ov7725_set_com8(client, COM8_AEC,
			ctrl->val ? V4L2_EXPOSURE_MANUAL : V4L2_EXPOSURE_AUTO);
		if (ret < 0)
			goto unlock;
		dev_dbgmsg(&client->dev, "%s:value=%d\n", __func__, ctrl->val);
		break;
	case V4L2_CID_EXPOSURE:
		if (ctrl->val > ctrl->maximum) {
			dev_err(&client->dev, "%s:error value=%d\n", __func__, ctrl->val);
			ret = -EINVAL;
			goto unlock;
		}
		/* set manual mode */
		ret = ov7725_set_com8(client, COM8_AEC, V4L2_EXPOSURE_MANUAL);
		if (ret < 0)
			goto unlock;
		priv->autoexposure->cur.val = V4L2_EXPOSURE_MANUAL; /* change current auto */
		ret = ov7725_reg_write(client, REG_AEC, ctrl->val & 0xFF);
		if (ret < 0)
			goto unlock;
		ret = ov7725_reg_write(client, REG_AECH, (ctrl->val >> 8) & 0xFF);
		if (ret < 0)
			goto unlock;
		dev_dbgmsg(&client->dev, "%s:value=%d\n", __func__, ctrl->val);
		break;
	default:
		dev_err(&client->dev, "%s:not support CID\n", __func__);
		ret = -EINVAL;
		break;
	}

unlock:
	mutex_unlock(&priv->lock);
	if (ret < 0)
		return ret;
	return 0;
}

static const struct v4l2_ctrl_ops ov7725_ctrl_ops = {
	.g_volatile_ctrl = ov7725_g_volatile_ctrl,
	.s_ctrl = ov7725_s_ctrl,
};

static const struct v4l2_ctrl_config ov7725_ctrls[] = {
	{ /* Green balance */
		.ops	= &ov7725_ctrl_ops,
		.id	= OV7725_CID_GREEN_BALANCE,
		.type	= V4L2_CTRL_TYPE_INTEGER,
		.name	= "Green Balance",
		.min	= 0,
		.max	= 255,
		.def	= DEF_GREEN,
		.step	= 1,
		.flags	= V4L2_CTRL_FLAG_SLIDER,
	},
};


static int ov7725_mpd_reg_read(struct i2c_client *client, u16 addr)
{
	struct i2c_msg msg[2];
	u8 buf[2];
	int ret;

	addr = swab16(addr);

	msg[0].addr  = client->addr - MPD_ADDR_OFFSET;
	msg[0].flags = 0;
	msg[0].len   = 2;
	msg[0].buf   = (u8 *)&addr;
	msg[1].addr  = client->addr - MPD_ADDR_OFFSET;
	msg[1].flags = I2C_M_RD;
	msg[1].len   = 2;
	msg[1].buf   = buf;

	ret = i2c_transfer(client->adapter, msg, 2);
	if (ret < 0)
		return ret;

	ret  = buf[0] << 8;
	ret |= buf[1] << 0;

	return ret;
}

static int ov7725_mpd_reg_write(struct i2c_client *client, u16 addr, u16 data)
{
	struct i2c_msg msg;
	u8 buf[4];
	int ret;

	buf[0] = (addr >> 8) & 0xff;
	buf[1] = addr & 0xff;
	buf[2] = (data >> 8) & 0xff;
	buf[3] = data & 0xff;

	msg.addr  = client->addr - MPD_ADDR_OFFSET;
	msg.flags = 0;
	msg.len   = 4;
	msg.buf   = buf;

	ret = i2c_transfer(client->adapter, &msg, 1);
	if (ret >= 0)
		ret = 0;

	return ret;
}

static int ov7725_mpd_write_regs(struct i2c_client *client,
				const struct ov7725_mpd_reg *regs)
{
	while (regs->reg != 0xffff) {
		int ret = ov7725_mpd_reg_write(client, regs->reg, regs->val);
		if (ret < 0)
			return ret;
		regs++;
	}
	return 0;
}

static int ov7725_capture_start(struct ov7725_priv *priv)
{
	struct i2c_client *client = v4l2_get_subdevdata(&priv->subdev);

	mutex_lock(&priv->lock);
	/* Reset ov7725 & MPD */
	ov7725_mpd_reg_write(client, 0x0002, 0x0001);
	ov7725_reg_write(client, 0x12, 0x80);
	msleep(1);
	ov7725_mpd_reg_write(client, 0x0002, 0x0000);

	switch (priv->width) {
	case 320:
		/* start ov7725 */
		ov7725_write_regs(client, ov7725_qvga_regs);

		/* start MPD */
		ov7725_mpd_reg_write(client, 0x0016, 0x0033);
		ov7725_mpd_reg_write(client, 0x0018, 0x0a03);
		msleep(1);
		ov7725_mpd_reg_write(client, 0x0018, 0x0a13);

		ov7725_mpd_write_regs(client, ov7725_mpd_qvga_regs);
		break;
	default:
		/* start ov7725 */
		ov7725_write_regs(client, ov7725_vga_regs);

		/* start MPD */
		ov7725_mpd_reg_write(client, 0x0016, 0x0027);
		ov7725_mpd_reg_write(client, 0x0018, 0x0603);
		msleep(1);
		ov7725_mpd_reg_write(client, 0x0018, 0x0613);

		ov7725_mpd_write_regs(client, ov7725_mpd_vga_regs);
		break;
	}

	mutex_unlock(&priv->lock);
	return 0;
}

static int ov7725_capture_stop(struct ov7725_priv *priv)
{
	struct i2c_client *client = v4l2_get_subdevdata(&priv->subdev);

	mutex_lock(&priv->lock);
	/* stop MPD */
	ov7725_mpd_reg_write(client, 0x0002, 0x0001);

	mutex_unlock(&priv->lock);
	return 0;
}

static int ov7725_g_chip_ident(struct v4l2_subdev *sd,
			       struct v4l2_dbg_chip_ident *id)
{
	struct ov7725_priv *priv = container_of(sd, struct ov7725_priv, subdev);

	id->ident    = priv->model;
	id->revision = 0;

	return 0;
}

#ifdef CONFIG_VIDEO_ADV_DEBUG
static int ov7725_g_register(struct v4l2_subdev *sd,
			     struct v4l2_dbg_register *reg)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int ret;

	reg->size = 1;
	if (reg->reg > 0xff)
		return -EINVAL;

	ret = ov7725_reg_read(client, reg->reg);
	if (ret < 0)
		return ret;

	reg->val = ret;

	return 0;
}

static int ov7725_s_register(struct v4l2_subdev *sd,
			     struct v4l2_dbg_register *reg)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	if (reg->reg > 0xff ||
	    reg->val > 0xff)
		return -EINVAL;

	return ov7725_reg_write(client, reg->reg, reg->val);
}
#endif

static struct v4l2_subdev_core_ops ov7725_subdev_core_ops = {
	.g_chip_ident	= ov7725_g_chip_ident,
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.g_register	= ov7725_g_register,
	.s_register	= ov7725_s_register,
#endif
};

static int ov7725_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct ov7725_priv *priv =
			container_of(sd, struct ov7725_priv, subdev);

	if (priv->current_enable == enable)
		return 0;

	priv->current_enable = enable;

	if (enable) {
		dev_dbgmsg(sd->v4l2_dev->dev, "%s: Start Streaming\n", __func__);
		/* start camera module */
		ov7725_capture_start(priv);
	} else {
		dev_dbgmsg(sd->v4l2_dev->dev, "%s: Stop Streaming\n", __func__);
		/* stop camera module */
		ov7725_capture_stop(priv);
	}
	return 0;
}

static int ov7725_cropcap(struct v4l2_subdev *sd, struct v4l2_cropcap *a)
{
	a->bounds.left			= 0;
	a->bounds.top			= 0;
	a->bounds.width			= VGA_WIDTH;
	a->bounds.height		= VGA_HEIGHT;
	a->defrect			= a->bounds;
	a->type				= V4L2_BUF_TYPE_VIDEO_CAPTURE;
	a->pixelaspect.numerator	= 1;
	a->pixelaspect.denominator	= 1;
	return 0;
}

static int ov7725_g_crop(struct v4l2_subdev *sd, struct v4l2_crop *a)
{
	a->c.left	= 0;
	a->c.top	= 0;
	a->c.width	= VGA_WIDTH;
	a->c.height	= VGA_HEIGHT;
	a->type		= V4L2_BUF_TYPE_VIDEO_CAPTURE;
	return 0;
}

static int ov7725_enum_fmt(struct v4l2_subdev *sd, unsigned int index,
			   enum v4l2_mbus_pixelcode *code)
{
	if (index >= ARRAY_SIZE(ov7725_codes))
		return -EINVAL;

	*code = ov7725_codes[index];
	return 0;
}

static void ov7725_res_roundup(u32 *width, u32 *height)
{
	int i;

	for (i = ARRAY_SIZE(ov7725_framesizes) - 1; i >= 0; i--) {
		if (ov7725_framesizes[i].width >= *width &&
				ov7725_framesizes[i].height >= *height) {
			*width = ov7725_framesizes[i].width;
			*height = ov7725_framesizes[i].height;
			return;
		}
	}
	*width = ov7725_framesizes[0].width;
	*height = ov7725_framesizes[0].height;
}

static int ov7725_try_fmt(struct v4l2_subdev *sd,
			  struct v4l2_mbus_framefmt *mf)
{
	ov7725_res_roundup(&mf->width, &mf->height);

	mf->code	= V4L2_MBUS_FMT_UYVY8_2X8;
	mf->colorspace	= V4L2_COLORSPACE_SMPTE170M;
	mf->field	= V4L2_FIELD_NONE;
	return 0;
}

static int ov7725_g_fmt(struct v4l2_subdev *sd,
			struct v4l2_mbus_framefmt *mf)
{
	/* default VGA */
	mf->width	= VGA_WIDTH;
	mf->height	= VGA_HEIGHT;
	mf->code	= V4L2_MBUS_FMT_UYVY8_2X8;
	mf->colorspace	= V4L2_COLORSPACE_SMPTE170M;
	mf->field	= V4L2_FIELD_NONE;
	return 0;
}

static int ov7725_s_fmt(struct v4l2_subdev *sd,
			struct v4l2_mbus_framefmt *mf)
{
	struct ov7725_priv *priv =
			container_of(sd, struct ov7725_priv, subdev);
	enum v4l2_colorspace cspace;
	enum v4l2_mbus_pixelcode code = mf->code;
	int ret = 0;

	switch (code) {
	case V4L2_MBUS_FMT_UYVY8_2X8:
		cspace = V4L2_COLORSPACE_SMPTE170M;
		break;
	default:
		return -EINVAL;
	}

	ov7725_res_roundup(&mf->width, &mf->height);

	mf->code	= code;
	mf->colorspace	= cspace;

	priv->width = mf->width;
	priv->height = mf->height;

	return ret;
}

static int ov7725_g_mbus_config(struct v4l2_subdev *sd,
				struct v4l2_mbus_config *cfg)
{
	struct ov7725_priv *priv =
			container_of(sd, struct ov7725_priv, subdev);
	int mbps;

	switch (priv->width) {
	case 320:
		mbps = OV7725_CSI2_QVGA_MBPS;
		break;
	default:
		mbps = OV7725_CSI2_VGA_MBPS;
		break;
	}

	cfg->flags = V4L2_MBUS_CSI2_1_LANE | V4L2_MBUS_CSI2_CHANNEL_0 |
			V4L2_MBUS_CSI2_CONTINUOUS_CLOCK;
	cfg->flags |= V4L2_MBUS_CSI2_SET_MBPS(mbps);
	cfg->type = V4L2_MBUS_CSI2;
	return 0;
}

static int ov7725_g_parm(struct v4l2_subdev *sd, struct v4l2_streamparm *parms)
{
	struct v4l2_captureparm *cp = &parms->parm.capture;

	if (parms->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	memset(cp, 0, sizeof(*cp));
	cp->capability = V4L2_CAP_TIMEPERFRAME;
	cp->timeperframe.numerator = 1;
	cp->timeperframe.denominator = 30;
	return 0;
}

static int ov7725_s_parm(struct v4l2_subdev *sd, struct v4l2_streamparm *parms)
{
	struct v4l2_captureparm *cp = &parms->parm.capture;
	struct v4l2_fract *tpf = &cp->timeperframe;

	if (parms->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	tpf->numerator = 1;
	tpf->denominator = 30;
	return 0;
}

static int ov7725_enum_frameintervals(struct v4l2_subdev *sd,
		struct v4l2_frmivalenum *interval)
{
	if (interval->index >= 1)
		return -EINVAL;

	interval->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	interval->discrete.numerator = 1;
	interval->discrete.denominator = 30;
	return 0;
}

static int ov7725_enum_framesizes(struct v4l2_subdev *sd,
		struct v4l2_frmsizeenum *fsize)
{
	if (fsize->index >= ARRAY_SIZE(ov7725_framesizes))
		return -EINVAL;

	fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	fsize->discrete.width = ov7725_framesizes[fsize->index].width;
	fsize->discrete.height = ov7725_framesizes[fsize->index].height;
	return 0;
}

static struct v4l2_subdev_video_ops ov7725_subdev_video_ops = {
	.s_stream	= ov7725_s_stream,

	.cropcap	= ov7725_cropcap,
	.g_crop		= ov7725_g_crop,

	.enum_mbus_fmt	= ov7725_enum_fmt,
	.try_mbus_fmt	= ov7725_try_fmt,
	.g_mbus_fmt	= ov7725_g_fmt,
	.s_mbus_fmt	= ov7725_s_fmt,
	.g_mbus_config	= ov7725_g_mbus_config,

	.g_parm		= ov7725_g_parm,
	.s_parm		= ov7725_s_parm,
	.enum_frameintervals = ov7725_enum_frameintervals,
	.enum_framesizes = ov7725_enum_framesizes,
};

static struct v4l2_subdev_ops ov7725_subdev_ops = {
	.core	= &ov7725_subdev_core_ops,
	.video	= &ov7725_subdev_video_ops,
};

static int ov7725_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct ov7725_priv *priv;
	struct soc_camera_link *icl = soc_camera_i2c_to_link(client);
	struct i2c_adapter *adapter = to_i2c_adapter(client->dev.parent);
	int ret, pid, mid, mpd_id;

	if (!icl) {
		dev_err(&client->dev, "Missing platform_data for driver\n");
		return -EINVAL;
	}

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_err(&adapter->dev,
			"I2C-Adapter doesn't support "
			"I2C_FUNC_SMBUS_BYTE_DATA\n");
		return -EIO;
	}

	priv = devm_kzalloc(&client->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	ret = ov7725_reg_read(client, 0x0a);
	if (ret < 0)
		return ret;
	pid = ret << 8;
	ret = ov7725_reg_read(client, 0x0b);
	if (ret < 0)
		return ret;
	pid |= ret;
	ret = ov7725_reg_read(client, 0x1c);
	if (ret < 0)
		return ret;
	mid = ret << 8;
	ret = ov7725_reg_read(client, 0x1d);
	if (ret < 0)
		return ret;
	mid |= ret;
	priv->model = V4L2_IDENT_OV7725;

	mpd_id = ov7725_mpd_reg_read(client, 0x00);
	if (mpd_id < 0) {
		dev_err(&client->dev, "MPD read error\n");
		return mpd_id;
	}

	v4l2_i2c_subdev_init(&priv->subdev, client, &ov7725_subdev_ops);
	mutex_init(&priv->lock);

	v4l2_ctrl_handler_init(&priv->hdl, 8);
	priv->autowb = v4l2_ctrl_new_std(&priv->hdl, &ov7725_ctrl_ops,
			V4L2_CID_AUTO_WHITE_BALANCE, 0, 1, 1, 1);
	priv->red = v4l2_ctrl_new_std(&priv->hdl, &ov7725_ctrl_ops,
			V4L2_CID_RED_BALANCE, 0, 0xff, 1, DEF_RED);
	priv->blue = v4l2_ctrl_new_std(&priv->hdl, &ov7725_ctrl_ops,
			V4L2_CID_BLUE_BALANCE, 0, 0xff, 1, DEF_BLUE);
	priv->green = v4l2_ctrl_new_custom(&priv->hdl, &ov7725_ctrls[0], NULL);
	priv->autogain = v4l2_ctrl_new_std(&priv->hdl, &ov7725_ctrl_ops,
			V4L2_CID_AUTOGAIN, 0, 1, 1, 1);
	priv->gain = v4l2_ctrl_new_std(&priv->hdl, &ov7725_ctrl_ops,
			V4L2_CID_GAIN, 0, 0xff, 1, DEF_GAIN);
	priv->autoexposure = v4l2_ctrl_new_std_menu(&priv->hdl,
			&ov7725_ctrl_ops, V4L2_CID_EXPOSURE_AUTO,
			V4L2_EXPOSURE_MANUAL, 0, V4L2_EXPOSURE_AUTO);
	priv->exposure = v4l2_ctrl_new_std(&priv->hdl, &ov7725_ctrl_ops,
			V4L2_CID_EXPOSURE, 0, 0xffff, 1, DEF_AEC);

	priv->subdev.ctrl_handler = &priv->hdl;
	if (priv->hdl.error) {
		ret = priv->hdl.error;
		dev_err(&client->dev, "ctrl handler error\n");
		goto err;
	}
	priv->autowb->flags |= V4L2_CTRL_FLAG_VOLATILE;
	priv->red->flags |= V4L2_CTRL_FLAG_VOLATILE;
	priv->blue->flags |= V4L2_CTRL_FLAG_VOLATILE;
	priv->green->flags |= V4L2_CTRL_FLAG_VOLATILE;
	priv->autogain->flags |= V4L2_CTRL_FLAG_VOLATILE;
	priv->gain->flags |= V4L2_CTRL_FLAG_VOLATILE;
	priv->autoexposure->flags |= V4L2_CTRL_FLAG_VOLATILE;
	priv->exposure->flags |= V4L2_CTRL_FLAG_VOLATILE;

	ret = ov7725_attr_create(client);
	if (ret < 0) {
		dev_err(&client->dev, "sysfs create error\n");
		goto err;
	}

	dev_info(&client->dev, "ov7725 PID=0x%04x MID=0x%04x. MPD=0x%04x\n",
				pid, mid, mpd_id);
	return 0;

err:
	v4l2_ctrl_handler_free(&priv->hdl);
	return ret;
}

static int ov7725_remove(struct i2c_client *client)
{
	struct ov7725_priv *priv = to_ov7725(client);

	v4l2_ctrl_handler_free(&priv->hdl);
	ov7725_attr_remove(client);
	v4l2_device_unregister_subdev(&priv->subdev);
	dev_info(&client->dev, "removed.\n");
	return 0;
}

static const struct i2c_device_id ov7725_id[] = {
	{ "ov7725_mpd", 0 },
	{ },
};
MODULE_DEVICE_TABLE(i2c, ov7725_id);

static struct i2c_driver ov7725_i2c_driver = {
	.driver = {
		.name = "ov7725_mpd",
	},
	.probe    = ov7725_probe,
	.remove   = ov7725_remove,
	.id_table = ov7725_id,
};

module_i2c_driver(ov7725_i2c_driver);

MODULE_DESCRIPTION("SoC Camera driver for ov7725 MPD");
MODULE_AUTHOR("TOSHIBA Corporation");
MODULE_LICENSE("GPL v2");
