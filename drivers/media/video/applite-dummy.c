/*
 * linux/drivers/media/video/applite-dummy.c
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

#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/v4l2-mediabus.h>
#include <linux/videodev2.h>
#include <linux/vmalloc.h>
#include <linux/platform_device.h>

#include <media/soc_camera.h>

/* ----------------------------------------------------------------------- */

#define DUMMY_MAX_WIDTH		1920
#define DUMMY_MAX_HEIGHT	1080

/* ----------------------------------------------------------------------- */

struct dummy_priv {
	struct soc_camera_link		link;
	struct platform_device		soc_cam_dev;
	struct platform_device		*pdev;

	struct soc_camera_device	*icd;
	struct v4l2_subdev		subdev;

	int				width;
	int				height;
	int				mbps;
};

/* ----------------------------------------------------------------------- */
static enum v4l2_mbus_pixelcode dummy_codes[] = {
	V4L2_MBUS_FMT_UYVY8_2X8,
};

/* ----------------------------------------------------------------------- */

static int dummy_s_power(struct v4l2_subdev *sd, int on)
{
	return 0;
}

static struct v4l2_subdev_core_ops dummy_core_ops = {
	.s_power		= dummy_s_power,
};

/* ----------------------------------------------------------------------- */

/* Start/Stop streaming from the device */
static int dummy_s_stream(struct v4l2_subdev *sd, int enable)
{
	return 0;
}

static int dummy_cropcap(struct v4l2_subdev *sd, struct v4l2_cropcap *a)
{
	a->bounds.left			= 0;
	a->bounds.top			= 0;
	a->bounds.width			= DUMMY_MAX_WIDTH;
	a->bounds.height		= DUMMY_MAX_HEIGHT;
	a->defrect			= a->bounds;
	a->type				= V4L2_BUF_TYPE_VIDEO_CAPTURE;
	a->pixelaspect.numerator	= 1;
	a->pixelaspect.denominator	= 1;

	return 0;
}

static int dummy_g_crop(struct v4l2_subdev *sd, struct v4l2_crop *a)
{
	a->c.left		= 0;
	a->c.top		= 0;
	a->c.width		= DUMMY_MAX_WIDTH;
	a->c.height		= DUMMY_MAX_HEIGHT;
	a->type			= V4L2_BUF_TYPE_VIDEO_CAPTURE;

	return 0;
}

static int dummy_enum_fmt(struct v4l2_subdev *sd, unsigned int index,
			   enum v4l2_mbus_pixelcode *code)
{
	if (index >= ARRAY_SIZE(dummy_codes))
		return -EINVAL;

	*code = dummy_codes[index];

	return 0;
}

static int dummy_try_fmt(struct v4l2_subdev *sd,
			  struct v4l2_mbus_framefmt *mf)
{
	mf->code	= V4L2_MBUS_FMT_UYVY8_2X8;
	mf->colorspace	= V4L2_COLORSPACE_SMPTE170M;
	mf->field	= V4L2_FIELD_NONE;

	return 0;
}

static int dummy_g_fmt(struct v4l2_subdev *sd,
			struct v4l2_mbus_framefmt *mf)
{
	mf->width	= 640;
	mf->height	= 480;
	mf->code	= V4L2_MBUS_FMT_UYVY8_2X8;
	mf->colorspace	= V4L2_COLORSPACE_SMPTE170M;
	mf->field	= V4L2_FIELD_NONE;

	return 0;
}

static int dummy_s_fmt(struct v4l2_subdev *sd,
			struct v4l2_mbus_framefmt *mf)
{
	struct dummy_priv *priv =
			container_of(sd, struct dummy_priv, subdev);
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

	mf->code	= code;
	mf->colorspace	= cspace;

	priv->width = mf->width;
	priv->height = mf->height;

	return ret;
}

/* Request bus settings on camera side */
static int dummy_g_mbus_config(struct v4l2_subdev *sd,
				struct v4l2_mbus_config *cfg)
{
	struct dummy_priv *priv =
			container_of(sd, struct dummy_priv, subdev);

	cfg->flags = V4L2_MBUS_CSI2_1_LANE | V4L2_MBUS_CSI2_CHANNEL_1 |
			V4L2_MBUS_CSI2_CONTINUOUS_CLOCK,
	cfg->flags |= V4L2_MBUS_CSI2_SET_MBPS(priv->mbps);
	cfg->type = V4L2_MBUS_CSI2;

	return 0;
}

static int dummy_s_parm(struct v4l2_subdev *sd, struct v4l2_streamparm *parms)
{
	return 0;
}

static struct v4l2_subdev_video_ops dummy_video_ops = {
	.s_stream	= dummy_s_stream,

	.cropcap	= dummy_cropcap,
	.g_crop		= dummy_g_crop,

	.enum_mbus_fmt	= dummy_enum_fmt,
	.try_mbus_fmt	= dummy_try_fmt,
	.g_mbus_fmt	= dummy_g_fmt,
	.s_mbus_fmt	= dummy_s_fmt,
	.g_mbus_config	= dummy_g_mbus_config,

	.s_parm		= dummy_s_parm,
};

/* ----------------------------------------------------------------------- */

static struct v4l2_subdev_ops dummy_subdev_ops = {
	.core	= &dummy_core_ops,
	.video	= &dummy_video_ops,
};

/* ----------------------------------------------------------------------- */

static int dummy_camera_add(struct soc_camera_device *icd)
{
	struct dummy_priv *priv =
			container_of(icd->link, struct dummy_priv, link);
	struct soc_camera_host *ici;
	int ret;

	if (!priv)
		return -ENODEV;

	priv->icd = icd;

	/* soc-camera convention: control's drvdata points to the subdev */
	platform_set_drvdata(priv->pdev, &priv->subdev);
	/* Set the control device reference */
	icd->control = &priv->pdev->dev;

	ici = to_soc_camera_host(icd->parent);

	v4l2_subdev_init(&priv->subdev, &dummy_subdev_ops);
	v4l2_set_subdevdata(&priv->subdev, priv);
	strncpy(priv->subdev.name,
			dev_name(&priv->pdev->dev), V4L2_SUBDEV_NAME_SIZE);

	ret = v4l2_device_register_subdev(&ici->v4l2_dev, &priv->subdev);
	if (ret)
		return ret;

	return 0;
}

static void dummy_camera_del(struct soc_camera_device *icd)
{
	struct dummy_priv *priv =
		container_of(icd->link, struct dummy_priv, link);

	if (!priv)
		return;

	priv->icd = NULL;
	icd->control = NULL;
	v4l2_device_unregister_subdev(&priv->subdev);

	platform_set_drvdata(priv->pdev, priv);
}

static int dummy_probe(struct platform_device *pdev)
{
	struct dummy_priv *priv;
	struct soc_camera_link *link;
	struct platform_device *soc_cam_dev;

	priv = vzalloc(sizeof(struct dummy_priv));
	if (!priv) {
		dev_err(&pdev->dev, "Failed to allocate private data!\n");
		return -ENOMEM;
	}

	priv->pdev = pdev;
	if (pdev->dev.platform_data)
		priv->mbps = (int)pdev->dev.platform_data;

	platform_set_drvdata(pdev, priv);

	link = &priv->link;
	link->bus_id = pdev->id;
	link->add_device = dummy_camera_add;
	link->del_device = dummy_camera_del;
	soc_cam_dev = &priv->soc_cam_dev;
	soc_cam_dev->id = pdev->id;
	soc_cam_dev->name = "soc-camera-pdrv";
	soc_cam_dev->dev.platform_data = link;
	platform_device_register(soc_cam_dev);

	return 0;
}

static int dummy_remove(struct platform_device *pdev)
{
	struct dummy_priv *priv = platform_get_drvdata(pdev);

	platform_device_unregister(&priv->soc_cam_dev);

	platform_set_drvdata(pdev, NULL);
	vfree(priv);

	return 0;
}

static struct platform_driver dummy_platform_driver = {
	.driver		= {
		.name	= "applite_dummy_camera",
		.owner	= THIS_MODULE,
	},
	.probe		= dummy_probe,
	.remove		= dummy_remove,
};

module_platform_driver(dummy_platform_driver);

MODULE_DESCRIPTION("Applite dummy camera driver");
MODULE_LICENSE("GPL v2");
