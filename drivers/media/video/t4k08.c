/*
 * linux/drivers/media/video/t4k08.c
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

/* ----------------------------------------------------------------------- */

#define T4K08_MAX_WIDTH		1280
#define T4K08_MAX_HEIGHT	720

#define T4K08_CSI2_MBPS		350

#define FRAME_RATE_MAX		30

/* ----------------------------------------------------------------------- */

struct t4k08_priv {
	struct soc_camera_link		link;
	struct platform_device		soc_cam_dev;
	struct platform_device		*pdev;

	struct soc_camera_device	*icd;
	struct v4l2_subdev		subdev;

	int				width;
	int				height;
	int				current_enable;
	int				rate_div;
};

struct t4k08_reg {
	u16	reg;
	u8	val;
};

/* ----------------------------------------------------------------------- */
static enum v4l2_mbus_pixelcode t4k08_codes[] = {
	V4L2_MBUS_FMT_UYVY8_2X8,
};

static int t4k08_rate_div[] = { 1, 2, 4, 6, 8, 10, 12 };

static const struct {
	u32 width;
	u32 height;
} t4k08_framesizes[] = {
	{1280, 720},
	{ 640, 480},
	{ 640, 360},
	{ 320, 240},
	{ 320, 180},
};

static struct t4k08_reg t4k08_common_set_regs[] = {
	{0x3032, 0x82},
	{0x3080, 0x68},
	{0x3088, 0x00},
	{0x30A2, 0x02},
	{0x30A6, 0x00},
	{0x3100, 0xD0},
	{0x3102, 0x65},
	{0x3108, 0x4B},
	{0x3129, 0x5F},
	{0x312A, 0x14},
	{0x312B, 0x36},
	{0x312C, 0x30},
	{0x312E, 0x75},
	{0x312F, 0x38},
	{0x3132, 0x33},
	{0x3136, 0x8F},
	{0x3137, 0x10},
	{0x3138, 0x0B},
	{0x313B, 0x09},
	{0x313E, 0x5C},
	{0x313F, 0x6F},
	{0x3145, 0x26},
	{0x3156, 0x60},
	{0x3184, 0x30},
	{0x31A0, 0xBF},
	{0x3300, 0x80},
	{0x3301, 0x01},
	{0x3303, 0x40},
	{0x3306, 0x30},
	{0x3310, 0x20},
	{0x3312, 0x10},
	{0x3314, 0x08},
	{0x3315, 0x60},
	{0x3324, 0x40},
	{0x3325, 0x40},
	{0x3400, 0x00},
	{0x351F, 0x80},
};

static struct t4k08_reg t4k08_320x180_regs[] = {
	{0x3019, 0x00},
	{0x301A, 0x40},
	{0x3020, 0x01},
	{0x3021, 0x40},
	{0x3022, 0x00},
	{0x3023, 0xB4},
};

static struct t4k08_reg t4k08_qvga_regs[] = {
	{0x3019, 0x00},
	{0x301A, 0x30},
	{0x3020, 0x01},
	{0x3021, 0x40},
	{0x3022, 0x00},
	{0x3023, 0xF0},
};

static struct t4k08_reg t4k08_640x360_regs[] = {
	{0x3019, 0x00},
	{0x301A, 0x20},
	{0x3020, 0x02},
	{0x3021, 0x80},
	{0x3022, 0x01},
	{0x3023, 0x68},
};

static struct t4k08_reg t4k08_vga_regs[] = {
	{0x3019, 0x00},
	{0x301A, 0x18},
	{0x3020, 0x02},
	{0x3021, 0x80},
	{0x3022, 0x01},
	{0x3023, 0xE0},
};

static struct t4k08_reg t4k08_720p_regs[] = {
	{0x3019, 0x00},
	{0x301A, 0x10},
	{0x3020, 0x05},
	{0x3021, 0x00},
	{0x3022, 0x02},
	{0x3023, 0xD0},
};

static struct t4k08_reg t4k08_rate_regs[] = {
	{0x3048, 0x01},
	{0x3049, 0x01},
};

static struct t4k08_reg t4k08_start_regs[] = {
	{0x3010, 0x01},
};

static struct t4k08_reg t4k08_stop_regs[] = {
	{0x3010, 0x00},
};

/* ----------------------------------------------------------------------- */
static int t4k08_reg_read(struct i2c_client *client, u16 sub_addr)
{
	struct i2c_msg msg[2];
	u8 buf;
	int ret;

	sub_addr = swab16(sub_addr);

	msg[0].addr  = client->addr;
	msg[0].flags = 0;
	msg[0].len   = 2;
	msg[0].buf   = (u8 *)&sub_addr;
	msg[1].addr  = client->addr;
	msg[1].flags = I2C_M_RD;
	msg[1].len   = 1;
	msg[1].buf   = &buf;

	ret = i2c_transfer(client->adapter, msg, 2);
	if (ret < 0)
		return ret;

	ret = buf;
	return ret;
}

static int t4k08_reg_write(struct i2c_client *client, u16 sub_addr, u8 data)
{
	struct i2c_msg msg;
	u8 buf[3];
	int ret;

	buf[0] = (sub_addr >> 8) & 0xff;
	buf[1] = sub_addr & 0xff;
	buf[2] = data;

	msg.addr  = client->addr;
	msg.flags = 0;
	msg.len   = 3;
	msg.buf   = buf;

	ret = i2c_transfer(client->adapter, &msg, 1);
	if (ret >= 0)
		ret = 0;

	return ret;
}

static int t4k08_write_regs(struct i2c_client *client,
			struct t4k08_reg *regs, int num)
{
	int i, ret;

	for (i = 0; i < num; i++) {
		ret = t4k08_reg_write(client,
				regs[i].reg, regs[i].val);
		if (ret < 0) {
			dev_err(&client->dev,
				"w_err addr=0x%x ret=%d\n", regs[i].reg, ret);
			return ret;
		}
	}
	return 0;
}

#define WRITE_REGS(x)	t4k08_write_regs(client, x, ARRAY_SIZE(x))

static int t4k08_capture_start(struct t4k08_priv *priv)
{
	struct i2c_client *client = v4l2_get_subdevdata(&priv->subdev);

	WRITE_REGS(t4k08_common_set_regs);

	switch (priv->width) {
	case 320:
		if (priv->height == 180)
			WRITE_REGS(t4k08_320x180_regs);
		else
			WRITE_REGS(t4k08_qvga_regs);
		break;
	case 640:
		if (priv->height == 360)
			WRITE_REGS(t4k08_640x360_regs);
		else
			WRITE_REGS(t4k08_vga_regs);
		break;
	default:
		WRITE_REGS(t4k08_720p_regs);
		break;
	}

	t4k08_rate_regs[0].val = priv->rate_div;
	t4k08_rate_regs[1].val = priv->rate_div;
	WRITE_REGS(t4k08_rate_regs);

	WRITE_REGS(t4k08_start_regs);

	return 0;
}

static int t4k08_capture_stop(struct t4k08_priv *priv)
{
	struct i2c_client *client = v4l2_get_subdevdata(&priv->subdev);

	WRITE_REGS(t4k08_stop_regs);

	return 0;
}

/* ----------------------------------------------------------------------- */

static int t4k08_s_power(struct v4l2_subdev *sd, int on)
{
	return 0;
}

#ifdef CONFIG_VIDEO_ADV_DEBUG
static int t4k08_get_register(struct v4l2_subdev *sd,
			       struct v4l2_dbg_register *reg)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int ret;

	ret = t4k08_reg_read(client, reg->reg);
	if (ret < 0)
		return ret;

	reg->val = ret;

	return 0;
}

static int t4k08_set_register(struct v4l2_subdev *sd,
			       struct v4l2_dbg_register *reg)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	return t4k08_reg_write(client, reg->reg, reg->val);
}
#endif

static struct v4l2_subdev_core_ops t4k08_core_ops = {
	.s_power		= t4k08_s_power,
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.g_register		= t4k08_get_register,
	.s_register		= t4k08_set_register,
#endif
};

/* ----------------------------------------------------------------------- */

/* Start/Stop streaming from the device */
static int t4k08_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct t4k08_priv *priv =
			container_of(sd, struct t4k08_priv, subdev);

	if (priv->current_enable == enable)
		return 0;

	priv->current_enable = enable;

	if (enable) {
		dev_dbg(sd->v4l2_dev->dev, "%s: Start Streaming\n", __func__);
		/* start camera module */
		t4k08_capture_start(priv);
	} else {
		dev_dbg(sd->v4l2_dev->dev, "%s: Stop Streaming\n", __func__);
		/* stop camera module */
		t4k08_capture_stop(priv);
	}
	return 0;
}

static int t4k08_cropcap(struct v4l2_subdev *sd, struct v4l2_cropcap *a)
{
	a->bounds.left			= 0;
	a->bounds.top			= 0;
	a->bounds.width			= T4K08_MAX_WIDTH;
	a->bounds.height		= T4K08_MAX_HEIGHT;
	a->defrect			= a->bounds;
	a->type				= V4L2_BUF_TYPE_VIDEO_CAPTURE;
	a->pixelaspect.numerator	= 1;
	a->pixelaspect.denominator	= 1;

	return 0;
}

static int t4k08_g_crop(struct v4l2_subdev *sd, struct v4l2_crop *a)
{
	a->c.left		= 0;
	a->c.top		= 0;
	a->c.width		= T4K08_MAX_WIDTH;
	a->c.height		= T4K08_MAX_HEIGHT;
	a->type			= V4L2_BUF_TYPE_VIDEO_CAPTURE;

	return 0;
}

static int t4k08_s_crop(struct v4l2_subdev *sd, struct v4l2_crop *a)
{
	return 0;
}

static int t4k08_enum_fmt(struct v4l2_subdev *sd, unsigned int index,
			   enum v4l2_mbus_pixelcode *code)
{
	if (index >= ARRAY_SIZE(t4k08_codes))
		return -EINVAL;

	*code = t4k08_codes[index];

	return 0;
}

/* select nearest higher resolution for capture */
static void t4k08_res_roundup(u32 *width, u32 *height)
{
	int i;

	for (i = ARRAY_SIZE(t4k08_framesizes) - 1; i >= 0; i--) {
		if (t4k08_framesizes[i].width >= *width &&
				t4k08_framesizes[i].height >= *height) {
			*width = t4k08_framesizes[i].width;
			*height = t4k08_framesizes[i].height;
			return;
		}
	}

	*width = t4k08_framesizes[0].width;
	*height = t4k08_framesizes[0].height;
}

static int t4k08_try_fmt(struct v4l2_subdev *sd,
			  struct v4l2_mbus_framefmt *mf)
{
	t4k08_res_roundup(&mf->width, &mf->height);

	mf->code	= V4L2_MBUS_FMT_UYVY8_2X8;
	mf->colorspace	= V4L2_COLORSPACE_SMPTE170M;
	mf->field	= V4L2_FIELD_NONE;

	return 0;
}

static int t4k08_g_fmt(struct v4l2_subdev *sd,
			struct v4l2_mbus_framefmt *mf)
{
	/* default VGA */
	mf->width	= 640;
	mf->height	= 480;
	mf->code	= V4L2_MBUS_FMT_UYVY8_2X8;
	mf->colorspace	= V4L2_COLORSPACE_SMPTE170M;
	mf->field	= V4L2_FIELD_NONE;

	return 0;
}

/* set the format we will capture in */
static int t4k08_s_fmt(struct v4l2_subdev *sd,
			struct v4l2_mbus_framefmt *mf)
{
	struct t4k08_priv *priv =
			container_of(sd, struct t4k08_priv, subdev);
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

	t4k08_res_roundup(&mf->width, &mf->height);

	mf->code	= code;
	mf->colorspace	= cspace;

	priv->width = mf->width;
	priv->height = mf->height;

	return ret;
}

/* Request bus settings on camera side */
static int t4k08_g_mbus_config(struct v4l2_subdev *sd,
				struct v4l2_mbus_config *cfg)
{
	cfg->flags = V4L2_MBUS_CSI2_1_LANE | V4L2_MBUS_CSI2_CHANNEL_0 |
			V4L2_MBUS_CSI2_CONTINUOUS_CLOCK;
	cfg->flags |= V4L2_MBUS_CSI2_SET_MBPS(T4K08_CSI2_MBPS);
	cfg->type = V4L2_MBUS_CSI2;

	return 0;
}

static int t4k08_g_parm(struct v4l2_subdev *sd, struct v4l2_streamparm *parms)
{
	struct t4k08_priv *priv =
			container_of(sd, struct t4k08_priv, subdev);
	struct v4l2_captureparm *cp = &parms->parm.capture;

	if (parms->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	memset(cp, 0, sizeof(*cp));
	cp->capability = V4L2_CAP_TIMEPERFRAME;
	cp->timeperframe.numerator = priv->rate_div;
	cp->timeperframe.denominator = FRAME_RATE_MAX;

	return 0;
}

static int t4k08_s_parm(struct v4l2_subdev *sd, struct v4l2_streamparm *parms)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct t4k08_priv *priv =
			container_of(sd, struct t4k08_priv, subdev);
	struct v4l2_captureparm *cp = &parms->parm.capture;
	struct v4l2_fract *tpf = &cp->timeperframe;
	int i, div;

	if (parms->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	if (tpf->numerator == 0 || tpf->denominator == 0)
		div = 1;  /* Reset to full rate */
	else
		div = (tpf->numerator * FRAME_RATE_MAX) / tpf->denominator;

	for (i = 0; i < ARRAY_SIZE(t4k08_rate_div) - 1; i++) {
		if (t4k08_rate_div[i] >= div)
			break;
	}

	priv->rate_div = t4k08_rate_div[i];
	tpf->numerator = t4k08_rate_div[i];
	tpf->denominator = FRAME_RATE_MAX;

	dev_dbg(&client->dev, "Set Frame interval: %u/%u s\n",
			tpf->numerator, tpf->denominator);

	return 0;
}

static int t4k08_enum_frameintervals(struct v4l2_subdev *sd,
		struct v4l2_frmivalenum *interval)
{
	if (interval->index >= ARRAY_SIZE(t4k08_rate_div))
		return -EINVAL;
	interval->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	interval->discrete.numerator = t4k08_rate_div[interval->index];
	interval->discrete.denominator = FRAME_RATE_MAX;
	return 0;
}

static int t4k08_enum_framesizes(struct v4l2_subdev *sd,
		struct v4l2_frmsizeenum *fsize)
{
	if (fsize->index >= ARRAY_SIZE(t4k08_framesizes))
		return -EINVAL;

	fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	fsize->discrete.width = t4k08_framesizes[fsize->index].width;
	fsize->discrete.height = t4k08_framesizes[fsize->index].height;

	return 0;
}

static struct v4l2_subdev_video_ops t4k08_video_ops = {
	.s_stream	= t4k08_s_stream,

	.cropcap	= t4k08_cropcap,
	.g_crop		= t4k08_g_crop,
	.s_crop		= t4k08_s_crop,

	.enum_mbus_fmt	= t4k08_enum_fmt,
	.try_mbus_fmt	= t4k08_try_fmt,
	.g_mbus_fmt	= t4k08_g_fmt,
	.s_mbus_fmt	= t4k08_s_fmt,
	.g_mbus_config	= t4k08_g_mbus_config,

	.g_parm		= t4k08_g_parm,
	.s_parm		= t4k08_s_parm,
	.enum_frameintervals = t4k08_enum_frameintervals,
	.enum_framesizes = t4k08_enum_framesizes,
};

/* ----------------------------------------------------------------------- */

static struct v4l2_subdev_ops t4k08_subdev_ops = {
	.core	= &t4k08_core_ops,
	.video	= &t4k08_video_ops,
};

/* ----------------------------------------------------------------------- */

static int t4k08_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct t4k08_priv *priv;
	struct soc_camera_link *icl = soc_camera_i2c_to_link(client);
	int ret, chip_id;

	if (!icl) {
		dev_err(&client->dev, "Missing platform_data for driver\n");
		return -EINVAL;
	}

	priv = vzalloc(sizeof(struct t4k08_priv));
	if (!priv) {
		dev_err(&client->dev, "Failed to allocate private data!\n");
		return -ENOMEM;
	}

	priv->rate_div = 1;

	ret = t4k08_reg_read(client, 0x3000);
	if (ret < 0)
		goto err;
	chip_id = ret << 8;
	ret = t4k08_reg_read(client, 0x3001);
	if (ret < 0)
		goto err;
	chip_id |= ret;

	v4l2_i2c_subdev_init(&priv->subdev, client, &t4k08_subdev_ops);

	dev_info(&client->dev, "t4k08 chip ID 0x%04x\n", chip_id);

	return 0;

err:
	vfree(priv);
	return ret;
}

static int t4k08_remove(struct i2c_client *client)
{
	struct v4l2_subdev *sd = i2c_get_clientdata(client);
	struct t4k08_priv *priv =
			container_of(sd, struct t4k08_priv, subdev);

	v4l2_device_unregister_subdev(sd);
	vfree(priv);

	return 0;
}

static const struct i2c_device_id t4k08_id[] = {
	{ "t4k08", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, t4k08_id);

static struct i2c_driver t4k08_i2c_driver = {
	.driver = {
		.name = "t4k08",
	},
	.probe		= t4k08_probe,
	.remove		= t4k08_remove,
	.id_table	= t4k08_id,
};
module_i2c_driver(t4k08_i2c_driver);

MODULE_DESCRIPTION("SoC Camera driver for t4k08");
MODULE_LICENSE("GPL v2");
