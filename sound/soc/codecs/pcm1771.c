/*
 * sound/soc/codecs/pcm1771.h
 *
 * (C) Copyright TOSHIBA Corporation
 * Semiconductor & Storage Products Company 2012
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
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/gpio.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/initval.h>
#include <sound/soc.h>

#include "pcm1771.h"

#define xprintk(level, fmt, args...) \
	printk(level "pcm1771: " fmt , ## args)
#if 0
#define dprintk(level, fmt, args...) \
	printk(level "pcm1771:%s(): " fmt , __func__ , ## args)
#else
#define dprintk(level, fmt, args...)
#endif

#define ERROR(fmt, args...) \
	xprintk(KERN_ERR , fmt , ## args)
#define INFO(fmt, args...) \
	xprintk(KERN_INFO , fmt , ## args)
#define DBG(fmt, args...) \
	dprintk(KERN_ERR , fmt , ## args)


#define PCM1771_VERSION "0.1"

#define PCM1771_RATES (SNDRV_PCM_RATE_8000_192000 | SNDRV_PCM_RATE_KNOT)

static u32 pcm1771_rates[] = {
	11025,
	12000,
	18000,
	22050,
	24000,
	29400,
	32000,
	36000,
	44100,
	48000
/*
	58800,
	64000,
	72000,
	88200,
	96000,
	128000,
	144000,
	192000
*/
};

static struct snd_pcm_hw_constraint_list pcm1771_constraints = {
	.count  = ARRAY_SIZE(pcm1771_rates),
	.list   = pcm1771_rates,
};

static int pcm1771_startup(struct snd_pcm_substream *substream,
		struct snd_soc_dai *dai)
{
	struct snd_pcm_runtime *runtime = substream->runtime;

	DBG("enter\n");

	runtime->hw.rate_min = pcm1771_constraints.list[0];
	runtime->hw.rate_max = pcm1771_constraints.list[pcm1771_constraints.count - 1];
	runtime->hw.rates = (SNDRV_PCM_RATE_8000_192000|SNDRV_PCM_RATE_KNOT);

	snd_pcm_hw_constraint_list(substream->runtime, 0,
			SNDRV_PCM_HW_PARAM_RATE,
			&pcm1771_constraints);
	return 0;
}

static int pcm1771_hw_params(struct snd_pcm_substream *substream,
		struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
	return 0;
}

static int pcm1771_set_dai_fmt(struct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	return 0;
}

static int pcm1771_set_dai_sysclk(struct snd_soc_dai *codec_dai,
		int clk_id, unsigned int freq, int dir)
{
	return 0;
}


static const struct snd_soc_dai_ops pcm1771_dai_ops = {
	.startup	= pcm1771_startup,
	.hw_params	= pcm1771_hw_params,
	.set_fmt	= pcm1771_set_dai_fmt,
	.set_sysclk	= pcm1771_set_dai_sysclk,
};

static struct snd_soc_dai_driver pcm1771_dai = {
	.name = PCM1771_CODEC_DAI_NAME,
	.playback = {
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = PCM1771_RATES,
		/*.formats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S32_LE,*/
		.formats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE,
	},
	.ops = &pcm1771_dai_ops,
};


static int pcm1771_soc_probe(struct snd_soc_codec *codec)
{
	return 0;
}

static int pcm1771_soc_remove(struct snd_soc_codec *codec)
{
	return 0;
}

#ifdef CONFIG_PM
static int pcm1771_soc_suspend(struct snd_soc_codec *codec)
{
	return 0;
}

static int pcm1771_soc_resume(struct snd_soc_codec *codec)
{
	return 0;
}
#else
#define pcm1771_soc_suspend NULL
#define pcm1771_soc_resume NULL
#endif

static struct snd_soc_codec_driver soc_codec_dev_pcm1771 = {
	.probe = 	pcm1771_soc_probe,
	.remove = 	pcm1771_soc_remove,
	.suspend =	pcm1771_soc_suspend,
	.resume =	pcm1771_soc_resume,
};

static int __devinit pcm1771_codec_probe(struct platform_device *pdev)
{
	return snd_soc_register_codec(&pdev->dev,
			&soc_codec_dev_pcm1771, &pcm1771_dai, 1);
}

static int __devexit pcm1771_codec_remove(struct platform_device *pdev)
{
	snd_soc_unregister_codec(&pdev->dev);
	return 0;
}

MODULE_ALIAS("platform:pcm1771-codec");

static struct platform_driver pcm1771_codec_driver = {
	.probe		= pcm1771_codec_probe,
	.remove		= __devexit_p(pcm1771_codec_remove),
	.driver		= {
		.name	= PCM1771_CODEC_DEV_NAME,
		.owner	= THIS_MODULE,
	},
};

module_platform_driver(pcm1771_codec_driver);

MODULE_DESCRIPTION("ASoC PCM1771 driver");
MODULE_AUTHOR("TOSHIBA Corporation");
MODULE_LICENSE("GPL v2");
