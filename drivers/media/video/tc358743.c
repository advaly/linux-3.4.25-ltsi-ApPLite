/*
 * linux/drivers/media/video/tc358743.c
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

#define __DEBUG
#define __DEBUG_2

#include <linux/delay.h>
#include <linux/i2c.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/v4l2-mediabus.h>
#include <linux/videodev2.h>
#include <linux/vmalloc.h>
#include <linux/platform_device.h>
#include <media/soc_camera.h>
#include <media/v4l2-chip-ident.h>
#include <media/v4l2-common.h>
#include "tc358743.h"

#ifdef DEBUG_2
	#define dev_dbg2	dev_dbg
#else
	#define dev_dbg2(x, y, ...) { \
	}
#endif

#define MAX_SIZE_4		4
#define DEF_SIZE_1		1

/* ----------------------------------------------------------------------- */
static enum v4l2_mbus_pixelcode tc358743_codes[] = {
	V4L2_MBUS_FMT_UYVY8_2X8,
};


/* ----------------------------------------------------------------------- */
static int tc358743_reg_read(struct i2c_client *client, u16 sub_addr, u8 *data, u8 size)
{
	struct i2c_msg msg[2];
	u8 buf[4];
	int ret, i;

	if ((!size) || (size > MAX_SIZE_4))
		size = DEF_SIZE_1;

	sub_addr = swab16(sub_addr);

	msg[0].addr  = client->addr;
	msg[0].flags = 0;
	msg[0].len   = 2;
	msg[0].buf   = (u8 *)&sub_addr;
	msg[1].addr  = client->addr;
	msg[1].flags = I2C_M_RD;
	msg[1].len   = size;
	msg[1].buf   = &buf[0];

	ret = i2c_transfer(client->adapter, msg, 2);
	if (ret < 0) {
		dev_err(&client->dev, "%s: i2c error %d\n", __func__, ret);
		return ret;
	}

	for (i = 0; i < size; i++)
		data[i] = buf[i];

	dev_dbg2(&client->dev, "%s: size=%d\n", __func__, size);
	return ret;
}

static int tc358743_reg_write(struct i2c_client *client, u16 sub_addr, u32 data, u8 size)
{
	struct i2c_msg msg;
	u8 buf[6];
	int ret, i;

	if ((!size) || (size > MAX_SIZE_4))
		size = DEF_SIZE_1;

	buf[0] = (sub_addr >> 8) & 0xff;
	buf[1] = sub_addr & 0xff;
	for (i = 0; i < size; i++)
		buf[i+2] = (data >> 8*i) & 0xFF;

	msg.addr  = client->addr;
	msg.flags = 0;
	msg.len   = size + sizeof(sub_addr);	/* register size + address size */
	msg.buf   = &buf[0];

	ret = i2c_transfer(client->adapter, &msg, 1);
	if (ret >= 0)
		ret = 0;
	else
		dev_err(&client->dev, "%s: i2c error %d\n", __func__, ret);

	return ret;
}

static int tc358743_write_regs(struct i2c_client *client,
			struct tc358743_reg *regs, int num)
{
	int i, ret;

	for (i = 0; i < num; i++) {
		ret = tc358743_reg_write(client,
				regs[i].reg, regs[i].data, regs[i].len);
		if (ret < 0) {
			dev_err(&client->dev, "%s: (%d)w_err addr=0x%x ret=%d\n",
				__func__, i, regs[i].reg, ret);
			return ret;
		}
	}
	return 0;
}

#define WRITE_REGS(x)	tc358743_write_regs(client, x, ARRAY_SIZE(x))

static int tc358743_capture_start(struct tc358743_priv *priv)
{
	struct i2c_client *client = v4l2_get_subdevdata(&priv->subdev);

	if (priv->rate_div == 1) {	/* 60fps */
		dev_dbg2(&client->dev, "%s: rate_div=%d\n",
			__func__, priv->rate_div);

		WRITE_REGS(tc358743_60fps_set1_regs);

		udelay(1000);	/* 1ms delay */

		WRITE_REGS(tc358743_60fps_set2_regs);

		WRITE_REGS(tc358743_60fps_set3_regs);

		WRITE_REGS(tc358743_60fps_set4_regs);
	} else {	/* 30fps */
		dev_dbg2(&client->dev, "%s: rate_div=%d\n",
			__func__, priv->rate_div);

		WRITE_REGS(tc358743_30fps_set1_regs);

		udelay(1000);	/* 1ms delay */

		WRITE_REGS(tc358743_30fps_set2_regs);

		WRITE_REGS(tc358743_30fps_set3_regs);

		WRITE_REGS(tc358743_30fps_set4_regs);
	}

	return 0;
}

static int tc358743_capture_stop(struct tc358743_priv *priv)
{
	struct i2c_client *client = v4l2_get_subdevdata(&priv->subdev);

	dev_dbg2(&client->dev, "%s: rate_div=%d\n",
			__func__, priv->rate_div);
	WRITE_REGS(tc358743_stop_regs);
	return 0;
}

/* ----------------------------------------------------------------------- */

static int tc358743_s_power(struct v4l2_subdev *sd, int on)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	dev_dbg(&client->dev, "%s: call\n", __func__);
	return 0;
}

#ifdef CONFIG_VIDEO_ADV_DEBUG
static int tc358743_get_register(struct v4l2_subdev *sd,
			       struct v4l2_dbg_register *reg)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int ret;

	ret = tc358743_reg_read(client, reg->reg, (u8 *)&reg->val, reg->size);
	if (ret < 0)
		return ret;

	return 0;
}

static int tc358743_set_register(struct v4l2_subdev *sd,
			       struct v4l2_dbg_register *reg)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	return tc358743_reg_write(client, reg->reg, (u32)reg->val, reg->size);
}
#endif

static struct v4l2_subdev_core_ops tc358743_core_ops = {
	.s_power		= tc358743_s_power,
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.g_register		= tc358743_get_register,
	.s_register		= tc358743_set_register,
#endif
};

/* ----------------------------------------------------------------------- */

/* Start/Stop streaming from the device */
static int tc358743_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct tc358743_priv *priv =
			container_of(sd, struct tc358743_priv, subdev);

	if (priv->current_enable == enable)
		return 0;

	priv->current_enable = enable;

	if (enable) {
		dev_dbg(sd->v4l2_dev->dev, "%s: Start Streaming(%dfps)\n", __func__
			, (FRAME_RATE_MAX/priv->rate_div));
		/* start camera module */
		tc358743_capture_start(priv);
	} else {
		dev_dbg(sd->v4l2_dev->dev, "%s: Stop Streaming\n", __func__);
		/* stop camera module */
		tc358743_capture_stop(priv);
	}
	return 0;
}

static int tc358743_cropcap(struct v4l2_subdev *sd, struct v4l2_cropcap *a)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	dev_dbg(&client->dev, "%s: call\n", __func__);
	a->bounds.left			= 0;
	a->bounds.top			= 0;
	a->bounds.width			= TC358743_MAX_WIDTH;
	a->bounds.height		= TC358743_MAX_HEIGHT;
	a->defrect			= a->bounds;
	a->type				= V4L2_BUF_TYPE_VIDEO_CAPTURE;
	a->pixelaspect.numerator	= 1;
	a->pixelaspect.denominator	= 1;

	return 0;
}

static int tc358743_g_crop(struct v4l2_subdev *sd, struct v4l2_crop *a)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	dev_dbg(&client->dev, "%s: call\n", __func__);
	a->c.left		= 0;
	a->c.top		= 0;
	a->c.width		= TC358743_MAX_WIDTH;
	a->c.height		= TC358743_MAX_HEIGHT;
	a->type			= V4L2_BUF_TYPE_VIDEO_CAPTURE;

	return 0;
}

static int tc358743_s_crop(struct v4l2_subdev *sd, struct v4l2_crop *a)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	dev_dbg(&client->dev, "%s: call\n", __func__);
	return 0;
}

static int tc358743_enum_fmt(struct v4l2_subdev *sd, unsigned int index,
			   enum v4l2_mbus_pixelcode *code)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	dev_dbg2(&client->dev, "%s: call%d\n", __func__, index);
	if (index >= ARRAY_SIZE(tc358743_codes))
		return -EINVAL;

	*code = tc358743_codes[index];
	dev_dbg(&client->dev, "%s: code=0x%04x\n", __func__, *code);

	return 0;
}

/* select nearest higher resolution for capture */
static void tc358743_res_roundup(u32 *width, u32 *height)
{
	int i;

	pr_debug("%s: request width=%d height=%d\n",
		__func__, *width, *height);

	for (i = ARRAY_SIZE(tc358743_framesizes) - 1; i >= 0; i--) {
		if (tc358743_framesizes[i].width >= *width &&
				tc358743_framesizes[i].height >= *height) {
			*width = tc358743_framesizes[i].width;
			*height = tc358743_framesizes[i].height;
			return;
		}
	}

	*width = tc358743_framesizes[0].width;
	*height = tc358743_framesizes[0].height;

	pr_debug("%s: select width=%d height=%d\n",
		__func__, *width, *height);
}

static int tc358743_try_fmt(struct v4l2_subdev *sd,
			  struct v4l2_mbus_framefmt *mf)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	dev_dbg2(&client->dev, "%s: try width=%d height=%d\n",
		__func__, mf->width, mf->height);
	tc358743_res_roundup(&mf->width, &mf->height);

	mf->code	= V4L2_MBUS_FMT_UYVY8_2X8;
	mf->colorspace	= V4L2_COLORSPACE_SMPTE170M;
	mf->field	= V4L2_FIELD_NONE;

	dev_dbg(&client->dev, "%s: width=%d height=%d code=0x%04x colorspace=%d field=%d\n",
		__func__, mf->width, mf->height, mf->code, mf->colorspace, mf->field);
	return 0;
}

static int tc358743_g_fmt(struct v4l2_subdev *sd,
			struct v4l2_mbus_framefmt *mf)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	/* default FHD */
	mf->width	= 1920;
	mf->height	= 1080;
	mf->code	= V4L2_MBUS_FMT_UYVY8_2X8;
	mf->colorspace	= V4L2_COLORSPACE_SMPTE170M;
	mf->field	= V4L2_FIELD_NONE;

	dev_dbg(&client->dev, "%s: width=%d height=%d code=0x%04x colorspace=%d field=%d\n",
		__func__, mf->width, mf->height, mf->code, mf->colorspace, mf->field);
	return 0;
}

/* set the format we will capture in */
static int tc358743_s_fmt(struct v4l2_subdev *sd,
			struct v4l2_mbus_framefmt *mf)
{
	struct tc358743_priv *priv =
			container_of(sd, struct tc358743_priv, subdev);
	enum v4l2_colorspace cspace;
	enum v4l2_mbus_pixelcode code = mf->code;
	int ret = 0;
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	dev_dbg2(&client->dev, "%s: set code=0x%04x\n", __func__, code);

	switch (code) {
	case V4L2_MBUS_FMT_UYVY8_2X8:
		cspace = V4L2_COLORSPACE_SMPTE170M;
		break;
	default:
		return -EINVAL;
	}

	tc358743_res_roundup(&mf->width, &mf->height);

	mf->code	= code;
	mf->colorspace	= cspace;

	priv->width = mf->width;
	priv->height = mf->height;

	dev_dbg(&client->dev, "%s: width=%d height=%d code=0x%04x colorspace=%d\n",
		__func__, priv->width, priv->height, code, cspace);
	return ret;
}

/* Request bus settings on camera side */
static int tc358743_g_mbus_config(struct v4l2_subdev *sd,
				struct v4l2_mbus_config *cfg)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct tc358743_priv *priv =
			container_of(sd, struct tc358743_priv, subdev);

	cfg->flags = V4L2_MBUS_CSI2_LANES | V4L2_MBUS_CSI2_CHANNEL_0 |
			V4L2_MBUS_CSI2_CONTINUOUS_CLOCK;
	cfg->flags |= V4L2_MBUS_CSI2_SET_MBPS(tc358743_csi2_mpbps[priv->rate_div-1]);
	cfg->type = V4L2_MBUS_CSI2;

	dev_dbg(&client->dev, "%s: flags=0x%x type=%d\n", __func__, cfg->flags, cfg->type);
	return 0;
}

static int tc358743_g_parm(struct v4l2_subdev *sd, struct v4l2_streamparm *parms)
{
	struct tc358743_priv *priv =
			container_of(sd, struct tc358743_priv, subdev);
	struct v4l2_captureparm *cp = &parms->parm.capture;
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	dev_dbg2(&client->dev, "%s: type=%d\n", __func__, parms->type);

	if (parms->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	memset(cp, 0, sizeof(*cp));
	cp->capability = V4L2_CAP_TIMEPERFRAME;
	cp->timeperframe.numerator = priv->rate_div;
	cp->timeperframe.denominator = FRAME_RATE_MAX;

	dev_dbg(&client->dev, "%s: Get Frame interval: %u/%u s capability=%d\n", __func__,
		cp->timeperframe.numerator, cp->timeperframe.denominator, cp->capability);
	return 0;
}

static int tc358743_s_parm(struct v4l2_subdev *sd, struct v4l2_streamparm *parms)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct tc358743_priv *priv =
			container_of(sd, struct tc358743_priv, subdev);
	struct v4l2_captureparm *cp = &parms->parm.capture;
	struct v4l2_fract *tpf = &cp->timeperframe;
	int i, div;

	if (parms->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	dev_dbg2(&client->dev, "%s: Set param: %u/%u s\n",
			__func__, tpf->numerator, tpf->denominator);
	if (tpf->numerator == 0 || tpf->denominator == 0)
		div = 1;  /* Reset to full rate */
	else
		div = (tpf->numerator * FRAME_RATE_MAX) / tpf->denominator;

	for (i = 0; i < ARRAY_SIZE(tc358743_rate_div) - 1; i++) {
		if (tc358743_rate_div[i] >= div)
			break;
	}

	priv->rate_div = tc358743_rate_div[i];
	tpf->numerator = tc358743_rate_div[i];
	tpf->denominator = FRAME_RATE_MAX;

	dev_dbg(&client->dev, "%s: Set Frame interval: %u/%u s\n",
			__func__, tpf->numerator, tpf->denominator);
	return 0;
}

static int tc358743_enum_frameintervals(struct v4l2_subdev *sd,
		struct v4l2_frmivalenum *interval)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	if (interval->index >= ARRAY_SIZE(tc358743_rate_div))
		return -EINVAL;
	interval->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	interval->discrete.numerator = tc358743_rate_div[interval->index];
	interval->discrete.denominator = FRAME_RATE_MAX;

	dev_dbg(&client->dev, "%s: type=%d %u/%u s\n", __func__,
		interval->type, interval->discrete.numerator, interval->discrete.denominator);
	return 0;
}

static int tc358743_enum_framesizes(struct v4l2_subdev *sd,
		struct v4l2_frmsizeenum *fsize)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	if (fsize->index >= ARRAY_SIZE(tc358743_framesizes))
		return -EINVAL;

	fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	fsize->discrete.width = tc358743_framesizes[fsize->index].width;
	fsize->discrete.height = tc358743_framesizes[fsize->index].height;

	dev_dbg(&client->dev, "%s: type=%d width=%d height=%d\n", __func__,
		fsize->type, fsize->discrete.width, fsize->discrete.height);
	return 0;
}

static struct v4l2_subdev_video_ops tc358743_video_ops = {
	.s_stream	= tc358743_s_stream,

	.cropcap	= tc358743_cropcap,
	.g_crop		= tc358743_g_crop,
	.s_crop		= tc358743_s_crop,

	.enum_mbus_fmt	= tc358743_enum_fmt,
	.try_mbus_fmt	= tc358743_try_fmt,
	.g_mbus_fmt	= tc358743_g_fmt,
	.s_mbus_fmt	= tc358743_s_fmt,
	.g_mbus_config	= tc358743_g_mbus_config,

	.g_parm		= tc358743_g_parm,
	.s_parm		= tc358743_s_parm,
	.enum_frameintervals = tc358743_enum_frameintervals,
	.enum_framesizes = tc358743_enum_framesizes,
};

/* ----------------------------------------------------------------------- */

static struct v4l2_subdev_ops tc358743_subdev_ops = {
	.core	= &tc358743_core_ops,
	.video	= &tc358743_video_ops,
};

/* ----------------------------------------------------------------------- */

static int tc358743_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct tc358743_priv *priv;
	struct soc_camera_link *icl = soc_camera_i2c_to_link(client);
	int ret, chip_id;

	dev_dbg2(&client->dev, "%s : call\n", __func__);

	if (!icl) {
		dev_err(&client->dev, "Missing platform_data for driver\n");
		return -EINVAL;
	}

	priv = vzalloc(sizeof(struct tc358743_priv));
	if (!priv) {
		dev_err(&client->dev, "Failed to allocate private data!\n");
		return -ENOMEM;
	}

	priv->rate_div = 1;

	ret = tc358743_reg_read(client, 0x0000, (u8 *)&chip_id, 2);
	if (ret < 0) {
		dev_err(&client->dev, "%s : i2c read error(%d)\n", __func__, ret);
		goto err;
	}

	dev_info(&client->dev, "tc358743 chip ID 0x%02x  rev. ID 0x%02x\n",
			 (chip_id>>8)&0xff, chip_id&0xff);

	v4l2_i2c_subdev_init(&priv->subdev, client, &tc358743_subdev_ops);

	return 0;

err:
	vfree(priv);
	return ret;
}

static int tc358743_remove(struct i2c_client *client)
{
	struct v4l2_subdev *sd = i2c_get_clientdata(client);
	struct tc358743_priv *priv =
			container_of(sd, struct tc358743_priv, subdev);

	dev_dbg2(&client->dev, "%s : call\n", __func__);

	v4l2_device_unregister_subdev(sd);
	vfree(priv);

	return 0;
}

static const struct i2c_device_id tc358743_id[] = {
	{ "tc358743", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, tc358743_id);

static struct i2c_driver tc358743_i2c_driver = {
	.driver = {
		.name = "tc358743",
	},
	.probe		= tc358743_probe,
	.remove		= tc358743_remove,
	.id_table	= tc358743_id,
};
module_i2c_driver(tc358743_i2c_driver);

MODULE_DESCRIPTION("SoC Camera driver for tc358743");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("TOSHIBA Corporation");
