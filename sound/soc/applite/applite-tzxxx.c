/*
 * sound/soc/applite/applite-tzxxx.c
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

/*
 * Module options:
 *
 *      audioclk=XXX            Default CONFIG_AUDIO_CLOCK_XXX, audio clock (
 *                                      24.5760, 18.4320, 12.2880, or 11.2896)
 *      audiofmt=YYY            Default CONFIG_AUDIO_FORMAT_XXX, audio format (
 *                                      I2S, or LR)
 *      period=N                Default N=8(kbyte), maximum period bytes
 */

#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/dma-mapping.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/dmaengine.h>
#include <linux/kobject.h>
#include <asm/mach-types.h>
#include <linux/pm_runtime.h>
#include <linux/clk.h>

#include <sound/core.h>
#include <sound/initval.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/soc.h>
#include <sound/dmaengine_pcm.h>

#include "applite-tzxxx.h"
#include "applite-dma.h"
#include "applite-i2s.h"
#include "applite-pcm.h"

#define xprintk(level, fmt, args...) \
	printk(level "snd-applite: " fmt , ## args)

#ifdef APPLITE_SND_TZxxx_DEBUG
	#define dprintk(level, fmt, args...) \
		printk(level "snd-applite:%s(): " fmt , __func__ , ## args)
#else
	#define dprintk(level, fmt, args...)
#endif

#define ERROR(fmt, args...) \
	xprintk(KERN_ERR , fmt , ## args)
#define INFO(fmt, args...) \
	xprintk(KERN_INFO , fmt , ## args)
#define DBG(fmt, args...) \
	dprintk(KERN_ERR , fmt , ## args)


#define DRIVER_VERSION_STRING	"0.1"

#define MOD_PARM_AUDIOCLK_24_5760MHZ    "24.5760"
#define MOD_PARM_AUDIOCLK_18_4320MHZ    "18.4320"
#define MOD_PARM_AUDIOCLK_12_2880MHZ    "12.2880"
#define MOD_PARM_AUDIOCLK_11_2896MHZ    "11.2896"
#define MOD_PARM_AUDIOFMT_I2S		"I2S"
#define MOD_PARM_AUDIOFMT_LR		"LR"

static struct {
	char *audioclk_parm;
	char *audiofmt_parm;
	int period_param;
} mod_data = {
#if defined(CONFIG_AUDIO_CLOCK_245760000HZ)
	.audioclk_parm = MOD_PARM_AUDIOCLK_24_5760MHZ,
#elif defined(CONFIG_AUDIO_CLOCK_184320000HZ)
	.audioclk_parm = MOD_PARM_AUDIOCLK_18_4320MHZ,
#elif defined(CONFIG_AUDIO_CLOCK_122880000HZ)
	.audioclk_parm = MOD_PARM_AUDIOCLK_12_2880MHZ,
#elif defined(CONFIG_AUDIO_CLOCK_112896000HZ)
	.audioclk_parm = MOD_PARM_AUDIOCLK_11_2896MHZ,
#else
	.audioclk_parm = MOD_PARM_AUDIOCLK_24_5760MHZ,
#endif
#if defined(CONFIG_AUDIO_FORMAT_I2S)
	.audiofmt_parm = MOD_PARM_AUDIOFMT_I2S,
#elif defined(CONFIG_AUDIO_FORMAT_LR)
	.audiofmt_parm = MOD_PARM_AUDIOFMT_LR,
#else
	.audiofmt_parm = MOD_PARM_AUDIOFMT_I2S,
#endif

	.period_param = CONFIG_AUDIO_PERIOD_BYTES,
};

module_param_named(audioclk, mod_data.audioclk_parm, charp, S_IRUGO);
MODULE_PARM_DESC(transport, "Audio Clock (24.5760, 18.4320, 12.2880, or 11.2896)");
module_param_named(audiofmt, mod_data.audiofmt_parm, charp, S_IRUGO);
MODULE_PARM_DESC(transport, "Audio Format (I2S, or LR)");
module_param_named(period, mod_data.period_param, int, S_IRUGO);
MODULE_PARM_DESC(uf_thr, "period bytes (kbyte)");

#if defined(CONFIG_AUDIO_CLOCK_245760000HZ)
/* default Audio Clock is 24.5760MHz */
static int g_audio_clock = AUDIO_CLOCK_24_5760MHZ;
#elif defined(CONFIG_AUDIO_CLOCK_184320000HZ)
/* default Audio Clock is 18.4320MHz */
static int g_audio_clock = AUDIO_CLOCK_18_4320MHZ;
#elif defined(CONFIG_AUDIO_CLOCK_122880000HZ)
/* default Audio Clock is 12.2880MHz */
static int g_audio_clock = AUDIO_CLOCK_12_2880MHZ;
#elif defined(CONFIG_AUDIO_CLOCK_112896000HZ)
/* default Audio Clock is 11.2896MHz */
static int g_audio_clock = AUDIO_CLOCK_11_2896MHZ;
#else
/* default Audio Clock is unkown */
static int g_audio_clock = AUDIO_CLOCK_24_5760MHZ;
#endif

#if defined(CONFIG_AUDIO_FORMAT_I2S)
/* default Audio Format is I2S */
static int g_audio_format = AUDIO_FORMAT_I2S;
#elif defined(CONFIG_AUDIO_FORMAT_LR)
/* default Audio Format is LR */
static int g_audio_format = AUDIO_FORMAT_LR;
#else
/* default Audio Format is unkown */
static int g_audio_format = AUDIO_FORMAT_I2S;
#endif

/* default Audio period bytes */
static int g_period_byte = CONFIG_AUDIO_PERIOD_BYTES;

static struct snd_pcm_substream *i2s_substream[AL_I2S_CHMAX];

struct al_tzxxx_priv {
	int i2s_master[2];	/* 0: Playback, 1: Capture */
	int codec_master[2];	/* 0: Playback, 1: Capture */
	int codec_dummy[2];	/* 0: Playback, 1: Capture */

	unsigned int codec_sysclk;

};

#ifdef APPLITE_SND_SYSFS
struct sysfs_hw_params {
	int enable;
	u64 formats;
	unsigned int rate;
	unsigned int channels;
	size_t buffer_bytes;
	size_t period_bytes;
	unsigned int periods;
};
static struct sysfs_hw_params set_hw_params[] = {
	{
	.enable = 0,
	},
	{
	.enable = 0,
	},
#if IS_ENABLED(CONFIG_ARCH_TZ3000)
	{
	.enable = 0,
	},
	{
	.enable = 0,
	},
#endif
};
#endif

/* support rates for 24.5760MHz */
static unsigned int stereo_rates_24_5760MHz[] = {
	24000, 48000, 64000, 96000
};
static unsigned int stereo_mono_rates_24_5760MHz[] = {
	24000, 48000, 64000, 96000, 128000, 192000
};
static struct snd_pcm_hw_constraint_list const_stereo_24_5760MHz = {
	.count  = ARRAY_SIZE(stereo_rates_24_5760MHz),
	.list   = stereo_rates_24_5760MHz,
	.mask   = 0,
};
static struct snd_pcm_hw_constraint_list const_stereo_mono_24_5760MHz = {
	.count  = ARRAY_SIZE(stereo_mono_rates_24_5760MHz),
	.list   = stereo_mono_rates_24_5760MHz,
	.mask   = 0,
};

/* support rates for 18.4320MHz */
static unsigned int stereo_rates_18_4320MHz[] = {
	18000, 36000, 48000, 72000
};
static unsigned int stereo_mono_rates_18_4320MHz[] = {
	18000, 36000, 48000, 72000, 96000, 144000
};
static struct snd_pcm_hw_constraint_list const_stereo_18_4320MHz = {
	.count  = ARRAY_SIZE(stereo_rates_18_4320MHz),
	.list   = stereo_rates_18_4320MHz,
	.mask   = 0,
};
static struct snd_pcm_hw_constraint_list const_stereo_mono_18_4320MHz = {
	.count  = ARRAY_SIZE(stereo_mono_rates_18_4320MHz),
	.list   = stereo_mono_rates_18_4320MHz,
	.mask   = 0,
};

/* support rate for 12.2880MHz */
static unsigned int stereo_rates_12_2880MHz[] = {
	12000, 24000, 32000, 48000
};
static unsigned int stereo_mono_rates_12_2880MHz[] = {
	12000, 24000, 32000, 48000, 64000, 96000
};
static struct snd_pcm_hw_constraint_list const_stereo_12_2880MHz = {
	.count  = ARRAY_SIZE(stereo_rates_12_2880MHz),
	.list   = stereo_rates_12_2880MHz,
	.mask   = 0,
};
static struct snd_pcm_hw_constraint_list const_stereo_mono_12_2880MHz = {
	.count  = ARRAY_SIZE(stereo_mono_rates_12_2880MHz),
	.list   = stereo_mono_rates_12_2880MHz,
	.mask   = 0,
};

/* support rate for 11.2896MHz */
static unsigned int stereo_rates_11_2896MHz[] = {
	11025, 22050, 29400, 44100
};
static unsigned int stereo_mono_rates_11_2896MHz[] = {
	11025, 22050, 29400, 44100, 58800, 88200
};
static struct snd_pcm_hw_constraint_list const_stereo_11_2896MHz = {
	.count  = ARRAY_SIZE(stereo_rates_11_2896MHz),
	.list   = stereo_rates_11_2896MHz,
	.mask   = 0,
};
static struct snd_pcm_hw_constraint_list const_stereo_mono_11_2896MHz = {
	.count  = ARRAY_SIZE(stereo_mono_rates_11_2896MHz),
	.list   = stereo_mono_rates_11_2896MHz,
	.mask   = 0,
};

static unsigned int rates_default[] = {
	11025, 12000, 18000, 22050, 24000, 29400,
	32000, 36000, 44100, 48000, 58800, 64000,
	72000, 88200, 96000, 128000, 144000, 192000
};
static struct snd_pcm_hw_constraint_list const_default = {
	.count  = ARRAY_SIZE(rates_default),
	.list   = rates_default,
	.mask   = 0,
};


static int al_tzxxx_hw_constraint_list_master_18_4320MHz(
				struct snd_pcm_runtime *runtime)
{
	unsigned int rate_min;
	unsigned int rate_max;
	int list_count;
	struct snd_pcm_hw_constraint_list *const_list;

#if IS_ENABLED(CONFIG_ARCH_TZ3000)
	/* TZ3000 */
	if (!machine_is_tz3000rb4()) {
		/* Andes */
		list_count =  const_stereo_18_4320MHz.count - 1;
		rate_min   =  const_stereo_18_4320MHz.list[0];
		rate_max   =  const_stereo_18_4320MHz.list[list_count];
		const_list = &const_stereo_18_4320MHz;
	} else {
		/* Manaslu */
		list_count =  const_stereo_mono_18_4320MHz.count - 1;
		rate_min   =  const_stereo_mono_18_4320MHz.list[0];
		rate_max   =  const_stereo_mono_18_4320MHz.list[list_count];
		const_list = &const_stereo_mono_18_4320MHz;
	}
#else /* !CONFIG_ARCH_TZ3000 */
	/* TZ2000 */
	if (!machine_is_tz2000rb3()) {
		/* Gregory */
		list_count =  const_stereo_18_4320MHz.count - 1;
		rate_min   =  const_stereo_18_4320MHz.list[0];
		rate_max   =  const_stereo_18_4320MHz.list[list_count];
		const_list = &const_stereo_18_4320MHz;
	} else {
		/* Montblanc */
		list_count =  const_stereo_mono_18_4320MHz.count - 1;
		rate_min   =  const_stereo_mono_18_4320MHz.list[0];
		rate_max   =  const_stereo_mono_18_4320MHz.list[list_count];
		const_list = &const_stereo_mono_18_4320MHz;
	}
#endif /* CONFIG_ARCH_TZ3000 */
	runtime->hw.rate_min = rate_min;
	runtime->hw.rate_max = rate_max;
	runtime->hw.rates = SNDRV_PCM_RATE_KNOT;
	return snd_pcm_hw_constraint_list(runtime, 0,
			SNDRV_PCM_HW_PARAM_RATE, const_list);
}

static int al_tzxxx_hw_constraint_list_master_12_2880MHz(
				struct snd_pcm_runtime *runtime)
{
	unsigned int rate_min;
	unsigned int rate_max;
	int list_count;
	struct snd_pcm_hw_constraint_list *const_list;

#if IS_ENABLED(CONFIG_ARCH_TZ3000)
	/* TZ3000 */
	if (!machine_is_tz3000rb4()) {
		/* Andes */
		list_count =  const_stereo_12_2880MHz.count - 1;
		rate_min   =  const_stereo_12_2880MHz.list[0];
		rate_max   =  const_stereo_12_2880MHz.list[list_count];
		const_list = &const_stereo_12_2880MHz;
	} else {
		/* Manaslu */
		list_count =  const_stereo_mono_12_2880MHz.count - 1;
		rate_min   =  const_stereo_mono_12_2880MHz.list[0];
		rate_max   =  const_stereo_mono_12_2880MHz.list[list_count];
		const_list = &const_stereo_mono_12_2880MHz;
	}
#else /* !CONFIG_ARCH_TZ3000 */
	/* TZ2000 */
	if (!machine_is_tz2000rb3()) {
		/* Gregory */
		list_count =  const_stereo_12_2880MHz.count - 1;
		rate_min   =  const_stereo_12_2880MHz.list[0];
		rate_max   =  const_stereo_12_2880MHz.list[list_count];
		const_list = &const_stereo_12_2880MHz;
	} else {
		/* Montblanc */
		list_count =  const_stereo_mono_12_2880MHz.count - 1;
		rate_min   =  const_stereo_mono_12_2880MHz.list[0];
		rate_max   =  const_stereo_mono_12_2880MHz.list[list_count];
		const_list = &const_stereo_mono_12_2880MHz;
	}
#endif /* CONFIG_ARCH_TZ3000 */
	runtime->hw.rate_min = rate_min;
	runtime->hw.rate_max = rate_max;
	runtime->hw.rates = SNDRV_PCM_RATE_KNOT;
	return snd_pcm_hw_constraint_list(runtime, 0,
			SNDRV_PCM_HW_PARAM_RATE, const_list);
}

static int al_tzxxx_hw_constraint_list_master_11_2896MHz(
				struct snd_pcm_runtime *runtime)
{
	unsigned int rate_min;
	unsigned int rate_max;
	int list_count;
	struct snd_pcm_hw_constraint_list *const_list;

#if IS_ENABLED(CONFIG_ARCH_TZ3000)
	/* TZ3000 */
	if (!machine_is_tz3000rb4()) {
		/* Andes */
		list_count =  const_stereo_11_2896MHz.count - 1;
		rate_min   =  const_stereo_11_2896MHz.list[0];
		rate_max   =  const_stereo_11_2896MHz.list[list_count];
		const_list = &const_stereo_11_2896MHz;
	} else {
		/* Manaslu */
		list_count =  const_stereo_mono_11_2896MHz.count - 1;
		rate_min   =  const_stereo_mono_11_2896MHz.list[0];
		rate_max   =  const_stereo_mono_11_2896MHz.list[list_count];
		const_list = &const_stereo_mono_11_2896MHz;
	}
#else /* !CONFIG_ARCH_TZ3000 */
	/* TZ2000 */
	if (!machine_is_tz2000rb3()) {
		/* Gregory */
		list_count =  const_stereo_11_2896MHz.count - 1;
		rate_min   =  const_stereo_11_2896MHz.list[0];
		rate_max   =  const_stereo_11_2896MHz.list[list_count];
		const_list = &const_stereo_11_2896MHz;
	} else {
		/* Montblanc */
		list_count =  const_stereo_mono_11_2896MHz.count - 1;
		rate_min   =  const_stereo_mono_11_2896MHz.list[0];
		rate_max   =  const_stereo_mono_11_2896MHz.list[list_count];
		const_list = &const_stereo_mono_11_2896MHz;
	}
#endif /* CONFIG_ARCH_TZ3000 */
	runtime->hw.rate_min = rate_min;
	runtime->hw.rate_max = rate_max;
	runtime->hw.rates = SNDRV_PCM_RATE_KNOT;
	return snd_pcm_hw_constraint_list(runtime, 0,
			SNDRV_PCM_HW_PARAM_RATE, const_list);
}

static int al_tzxxx_hw_constraint_list_master_24_5760MHz(
				struct snd_pcm_runtime *runtime)
{
	unsigned int rate_min;
	unsigned int rate_max;
	int list_count;
	struct snd_pcm_hw_constraint_list *const_list;

#if IS_ENABLED(CONFIG_ARCH_TZ3000)
	/* TZ3000 */
	if (!machine_is_tz3000rb4()) {
		/* Andes */
		list_count =  const_stereo_24_5760MHz.count - 1;
		rate_min   =  const_stereo_24_5760MHz.list[0];
		rate_max   =  const_stereo_24_5760MHz.list[list_count];
		const_list = &const_stereo_24_5760MHz;
	} else {
		/* Manaslu */
		list_count =  const_stereo_mono_24_5760MHz.count - 1;
		rate_min   =  const_stereo_mono_24_5760MHz.list[0];
		rate_max   =  const_stereo_mono_24_5760MHz.list[list_count];
		const_list = &const_stereo_mono_24_5760MHz;
	}
#else /* !CONFIG_ARCH_TZ3000 */
	/* TZ2000 */
	if (!machine_is_tz2000rb3()) {
		/* Gregory */
		list_count =  const_stereo_24_5760MHz.count - 1;
		rate_min   =  const_stereo_24_5760MHz.list[0];
		rate_max   =  const_stereo_24_5760MHz.list[list_count];
		const_list = &const_stereo_24_5760MHz;
	} else {
		/* Montblanc */
		list_count =  const_stereo_mono_24_5760MHz.count - 1;
		rate_min   =  const_stereo_mono_24_5760MHz.list[0];
		rate_max   =  const_stereo_mono_24_5760MHz.list[list_count];
		const_list = &const_stereo_mono_24_5760MHz;
	}
#endif /* CONFIG_ARCH_TZ3000 */
	runtime->hw.rate_min = rate_min;
	runtime->hw.rate_max = rate_max;
	runtime->hw.rates = SNDRV_PCM_RATE_KNOT;
	return snd_pcm_hw_constraint_list(runtime, 0,
			SNDRV_PCM_HW_PARAM_RATE, const_list);
}

static int al_tzxxx_hw_constraint_list_master(struct snd_pcm_runtime *runtime)
{
	int err = 0;

	switch (g_audio_clock) {
	case AUDIO_CLOCK_18_4320MHZ:
		err = al_tzxxx_hw_constraint_list_master_18_4320MHz(
				runtime);
		break;

	case AUDIO_CLOCK_12_2880MHZ:
		err = al_tzxxx_hw_constraint_list_master_12_2880MHz(
				runtime);
		break;

	case AUDIO_CLOCK_11_2896MHZ:
		err = al_tzxxx_hw_constraint_list_master_11_2896MHz(
				runtime);
		break;

	case AUDIO_CLOCK_24_5760MHZ:
		err = al_tzxxx_hw_constraint_list_master_24_5760MHz(
				runtime);
		break;
	}

	return err;
}

static int al_tzxxx_hw_constraint_list_slave(struct snd_pcm_runtime *runtime)
{
	runtime->hw.rate_min = const_default.list[0];
	runtime->hw.rate_max = const_default.list[const_default.count - 1];
	runtime->hw.rates = SNDRV_PCM_RATE_KNOT;
	return snd_pcm_hw_constraint_list(runtime, 0,
			SNDRV_PCM_HW_PARAM_RATE, &const_default);
}

static int al_tzxxx_busy_check(int mych)
{
#if IS_ENABLED(CONFIG_ARCH_TZ3000)
	switch (mych) {
	case AL_I2SO1_CH:
		if (i2s_substream[AL_I2SI1_CH])
			return 1; /* busy */
		break;
	case AL_I2SI1_CH:
		if (i2s_substream[AL_I2SO1_CH])
			return 1; /* busy */
		break;
	}
#endif /* CONFIG_ARCH_TZ3000 */
	return 0;
}

static int al_tzxxx_startup(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct al_i2s *i2s = snd_soc_dai_get_drvdata(rtd->cpu_dai);
	int err;

	DBG("enter(%s)\n", rtd->dai_link->stream_name);

	if (i2s->master[i2s->i2s_param[substream->stream].ch]) {
		/* i2s master */
		DBG("i2s master\n");
		err = al_tzxxx_hw_constraint_list_master(runtime);
	} else {
		/* i2s slave */
		DBG("i2s slave\n");
		err = al_tzxxx_hw_constraint_list_slave(runtime);
	}
	if (err)
		return err;

	/* busy check */
	if (al_tzxxx_busy_check(i2s->i2s_param[substream->stream].ch))
		return -EBUSY;

	i2s_substream[i2s->i2s_param[substream->stream].ch] = substream;

	return 0;
}

static void al_tzxxx_shutdown(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct al_i2s *i2s = snd_soc_dai_get_drvdata(rtd->cpu_dai);

	DBG("enter(%s)\n", rtd->dai_link->stream_name);

	i2s_substream[i2s->i2s_param[substream->stream].ch] = NULL;
}

static int al_tzxxx_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *codec_dai = rtd->codec_dai;
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	unsigned long cpu_fmt = 0;
	unsigned long codec_fmt = 0;
	unsigned long cpu_freq = 0;
	unsigned long codec_freq = 0;
	int cpu_dir, codec_dir;
	int ret = 0;
	struct al_tzxxx_priv *priv =
				snd_soc_card_get_drvdata(rtd->cpu_dai->card);
	struct al_i2s *i2s = snd_soc_dai_get_drvdata(rtd->cpu_dai);

	DBG("enter(%s)\n", rtd->dai_link->stream_name);

	/* format configuration */
	if (priv->i2s_master[substream->stream])
		cpu_fmt = (SND_SOC_DAIFMT_CBS_CFS | SND_SOC_DAIFMT_NB_NF);
	else
		cpu_fmt = (SND_SOC_DAIFMT_CBM_CFM | SND_SOC_DAIFMT_NB_NF);

	if (priv->codec_master[substream->stream])
		codec_fmt = (SND_SOC_DAIFMT_CBM_CFM | SND_SOC_DAIFMT_NB_NF);
	else
		codec_fmt = (SND_SOC_DAIFMT_CBS_CFS | SND_SOC_DAIFMT_NB_NF);

	if (params_channels(params) > 1) {
		if (g_audio_format == AUDIO_FORMAT_I2S) {
			cpu_fmt |= SND_SOC_DAIFMT_I2S;
			codec_fmt |= SND_SOC_DAIFMT_I2S;
		} else {
			cpu_fmt |= SND_SOC_DAIFMT_LEFT_J;
			codec_fmt |= SND_SOC_DAIFMT_LEFT_J;
		}
	} else {
		cpu_fmt |= SND_SOC_DAIFMT_LEFT_J;
		codec_fmt |= SND_SOC_DAIFMT_LEFT_J;
	}

	/* sysclk configuration */
	switch (g_audio_clock) {
	case AUDIO_CLOCK_24_5760MHZ:
		cpu_freq = 24576000;
		break;
	case AUDIO_CLOCK_18_4320MHZ:
		cpu_freq = 18432000;
		break;
	case AUDIO_CLOCK_12_2880MHZ:
		cpu_freq = 12288000;
		break;
	case AUDIO_CLOCK_11_2896MHZ:
		cpu_freq = 11289600;
		break;
	}
	if (priv->codec_sysclk)
		codec_freq = priv->codec_sysclk;
	else
		codec_freq = cpu_freq;

	if (priv->i2s_master[substream->stream]) {
		/* i2s master */
		codec_dir = SND_SOC_CLOCK_IN;
		cpu_dir = SND_SOC_CLOCK_OUT;
	} else {
		/* i2s slave */
		codec_dir = SND_SOC_CLOCK_OUT;
		cpu_dir = SND_SOC_CLOCK_IN;
	}

	if (!priv->codec_dummy[substream->stream]) {
		/* Set the Codec DAI configuration */
		ret = snd_soc_dai_set_fmt(codec_dai, codec_fmt);
		if (ret < 0)
			return ret;

		ret = snd_soc_dai_set_sysclk(codec_dai, 0,
				codec_freq, codec_dir);
		if (ret < 0)
			return ret;
	}

	/* Set the CPU DAI configuration */
	ret = snd_soc_dai_set_fmt(cpu_dai, cpu_fmt);
	if (ret < 0)
		return ret;

	ret = snd_soc_dai_set_sysclk(cpu_dai, 0,
			cpu_freq, cpu_dir);
	if (ret < 0)
		return ret;

#ifdef APPLITE_SND_SYSFS
	set_hw_params[i2s->i2s_param[substream->stream].ch].formats = params_format(params);
	set_hw_params[i2s->i2s_param[substream->stream].ch].rate = params_rate(params);
	set_hw_params[i2s->i2s_param[substream->stream].ch].channels = params_channels(params);
	set_hw_params[i2s->i2s_param[substream->stream].ch].buffer_bytes = params_buffer_bytes(params);
	set_hw_params[i2s->i2s_param[substream->stream].ch].period_bytes = params_period_bytes(params);
	set_hw_params[i2s->i2s_param[substream->stream].ch].periods = params_periods(params);
	set_hw_params[i2s->i2s_param[substream->stream].ch].enable = 1;
#endif
	return 0;
}

static struct snd_soc_ops applite_tzxxx_ops = {
	.startup = al_tzxxx_startup,
	.shutdown = al_tzxxx_shutdown,
	.hw_params = al_tzxxx_hw_params,
};

#if IS_ENABLED(CONFIG_ARCH_TZ3000)
static int al_tzxxx_init_tlv320adc3xxx_andes(struct snd_soc_pcm_runtime *rtd)
{
	struct al_i2s *i2s = snd_soc_dai_get_drvdata(rtd->cpu_dai);
	struct al_tzxxx_priv *priv =
				snd_soc_card_get_drvdata(rtd->cpu_dai->card);

	/*
	 * TZ3000: Andes
	 *   Playback: i2s master, codec slave
	 *   Capture:  i2s slave, codec master
	 */
	priv->i2s_master[SNDRV_PCM_STREAM_PLAYBACK] = 1;
	priv->i2s_master[SNDRV_PCM_STREAM_CAPTURE] = 0;
	priv->codec_master[SNDRV_PCM_STREAM_PLAYBACK] = 0;
	priv->codec_master[SNDRV_PCM_STREAM_CAPTURE] = 1;
	i2s->master[SNDRV_PCM_STREAM_PLAYBACK] = 1;
	i2s->master[SNDRV_PCM_STREAM_CAPTURE] = 0;

	/*
	 * Codec
	 *   DAC: Dummy(PCM1771)
	 *   ADC: TLV320ADC3110
	 *   sysclk: 12MHz
	 */
	priv->codec_dummy[SNDRV_PCM_STREAM_PLAYBACK] = 1;
	priv->codec_sysclk = 12000000;

	i2s->mono_rev = 0; /* mono is no-reverse */

	return 0;
}

static int al_tzxxx_init_tlv320aic3110_manaslu(struct snd_soc_pcm_runtime *rtd)
{
	struct al_i2s *i2s = snd_soc_dai_get_drvdata(rtd->cpu_dai);
	struct al_tzxxx_priv *priv =
				snd_soc_card_get_drvdata(rtd->cpu_dai->card);

	/*
	 * TZ3000: Manaslu
	 *   Playback: i2s master, codec slave
	 *   Capture:  i2s slave, codec slave
	 */
	priv->i2s_master[SNDRV_PCM_STREAM_PLAYBACK] = 1;
	priv->i2s_master[SNDRV_PCM_STREAM_CAPTURE] = 0;
	priv->codec_master[SNDRV_PCM_STREAM_PLAYBACK] = 0;
	priv->codec_master[SNDRV_PCM_STREAM_CAPTURE] = 0;
	i2s->master[SNDRV_PCM_STREAM_PLAYBACK] = 1;
	i2s->master[SNDRV_PCM_STREAM_CAPTURE] = 0;

	/*
	 * Codec
	 *   DAC: TLV320AIC3110
	 *   ADC: TLV320AIC3110
	 *   sysclk: audio clock
	 */
	priv->codec_sysclk = 0;

	i2s->clock_out[SNDRV_PCM_STREAM_CAPTURE] = 1;	/* Bit, L/R Clock On */
	i2s->mono_rev = 1; /* mono is reverse */

	return 0;
}
#endif

#if IS_ENABLED(CONFIG_ARCH_TZ2000)
static int al_tzxxx_init_tlv320adc3xxx_gregory(struct snd_soc_pcm_runtime *rtd)
{
	struct al_i2s *i2s = snd_soc_dai_get_drvdata(rtd->cpu_dai);
	struct al_tzxxx_priv *priv =
				snd_soc_card_get_drvdata(rtd->cpu_dai->card);

	/*
	 * TZ2000: Gregory
	 *   Playback: i2s master, codec slave
	 *   Capture:  i2s master, codec slave
	 */
	priv->i2s_master[SNDRV_PCM_STREAM_PLAYBACK] = 1;
	priv->i2s_master[SNDRV_PCM_STREAM_CAPTURE] = 1;
	priv->codec_master[SNDRV_PCM_STREAM_PLAYBACK] = 0;
	priv->codec_master[SNDRV_PCM_STREAM_CAPTURE] = 0;
	i2s->master[SNDRV_PCM_STREAM_PLAYBACK] = 1;
	i2s->master[SNDRV_PCM_STREAM_CAPTURE] = 1;

	/*
	 * Codec
	 *   DAC: Dummy(PCM1771)
	 *   ADC: TLV320ADC3110
	 *   sysclk: audio clock
	 */
	priv->codec_dummy[SNDRV_PCM_STREAM_PLAYBACK] = 1;
	priv->codec_sysclk = 0;

	i2s->mono_rev = 0; /* mono is no-reverse */

	return 0;
}

static int al_tzxxx_init_tlv320aic3110_montblanc(struct snd_soc_pcm_runtime *rtd)
{
	struct al_i2s *i2s = snd_soc_dai_get_drvdata(rtd->cpu_dai);
	struct al_tzxxx_priv *priv =
				snd_soc_card_get_drvdata(rtd->cpu_dai->card);

	/*
	 * TZ2000: MontBlanc
	 *   Playback: i2s master, codec slave
	 *   Capture:  i2s master, codec slave
	 */
	priv->i2s_master[SNDRV_PCM_STREAM_PLAYBACK] = 1;
	priv->i2s_master[SNDRV_PCM_STREAM_CAPTURE] = 1;
	priv->codec_master[SNDRV_PCM_STREAM_PLAYBACK] = 0;
	priv->codec_master[SNDRV_PCM_STREAM_CAPTURE] = 0;
	i2s->master[SNDRV_PCM_STREAM_PLAYBACK] = 1;
	i2s->master[SNDRV_PCM_STREAM_CAPTURE] = 1;

	/*
	 * Codec
	 *   DAC: TLV320AIC3110
	 *   ADC: TLV320AIC3110
	 *   sysclk: audio clock
	 */
	priv->codec_sysclk = 0;

	i2s->mono_rev = 1; /* mono is reverse */

	return 0;
}
#endif

static struct snd_soc_dai_link al_tzxxx_dai[] = {
	{
		/* I2S0 */
		.name		= "ApP Lite PCM #0",
		.stream_name	= "ApP Lite PCM #0",
		.cpu_dai_name	= "applite-i2s.0",
		.platform_name	= "applite-pcm-audio.0",
		.ops		= &applite_tzxxx_ops,
	},
	{
		/* I2S1 */
		.name		= "ApP Lite PCM #1",
		.stream_name	= "ApP Lite PCM #1",
		.cpu_dai_name	= "applite-i2s.1",
		.platform_name	= "applite-pcm-audio.0",
		.ops		= &applite_tzxxx_ops,
	},
};

static struct snd_soc_card al_tzxxx = {
	.name		= "applite_tzxxx",
	.owner		= THIS_MODULE,
};

#ifdef APPLITE_SND_SYSFS
static struct kobject *al_kobj;
static ssize_t c0d0p_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	struct sysfs_hw_params *params = &set_hw_params[0];

	if (!params->enable)
		return sprintf(buf, "[%s]:not set params\n", attr->attr.name);

	return sprintf(buf, "[%s]:\nformats:%s\nrate:%d\nchan:%d\nbuffer_bytes:%d\nperiod_bytes:%d\nperiods:%d\n",
		attr->attr.name,
		params->formats == SNDRV_PCM_FORMAT_S16_LE ? "S16_LE" : "S32_LE",
		params->rate, params->channels, params->buffer_bytes,
		params->period_bytes, params->periods);
}

static ssize_t c0d0c_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	struct sysfs_hw_params *params = &set_hw_params[1];

	if (!params->enable)
		return sprintf(buf, "[%s]:not set params\n", attr->attr.name);

	return sprintf(buf, "[%s]:\nformats:%s\nrate:%d\nchan:%d\nbuffer_bytes:%d\nperiod_bytes:%d\nperiods:%d\n",
		attr->attr.name,
		params->formats == SNDRV_PCM_FORMAT_S16_LE ? "S16_LE" : "S32_LE",
		params->rate, params->channels, params->buffer_bytes,
		params->period_bytes, params->periods);
}

#if IS_ENABLED(CONFIG_ARCH_TZ3000)
static ssize_t c0d1p_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	struct sysfs_hw_params *params = &set_hw_params[2];

	if (!params->enable)
		return sprintf(buf, "[%s]:not set params\n", attr->attr.name);

	return sprintf(buf, "[%s]\nformats:%s\nrate:%d\nchan:%d\nbuffer_bytes:%d\nperiod_bytes:%d\nperiods:%d\n",
		attr->attr.name,
		params->formats == SNDRV_PCM_FORMAT_S16_LE ? "S16_LE" : "S32_LE",
		params->rate, params->channels, params->buffer_bytes,
		params->period_bytes, params->periods);
}

static ssize_t c0d1c_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	struct sysfs_hw_params *params = &set_hw_params[3];

	if (!params->enable)
		return sprintf(buf, "[%s]:not set params\n", attr->attr.name);

	return sprintf(buf, "[%s]\nformats:%s\nrate:%d\nchan:%d\nbuffer_bytes:%d\nperiod_bytes:%d\nperiods:%d\n",
		attr->attr.name,
		params->formats == SNDRV_PCM_FORMAT_S16_LE ? "S16_LE" : "S32_LE",
		params->rate, params->channels, params->buffer_bytes,
		params->period_bytes, params->periods);
}
#endif

static struct kobj_attribute c0d0p_attribute = __ATTR(pcmC0D0p, 0666, c0d0p_show, NULL);
static struct kobj_attribute c0d0c_attribute = __ATTR(pcmC0D0c, 0666, c0d0c_show, NULL);
#if IS_ENABLED(CONFIG_ARCH_TZ3000)
static struct kobj_attribute c0d1p_attribute = __ATTR(pcmC0D1p, 0666, c0d1p_show, NULL);
static struct kobj_attribute c0d1c_attribute = __ATTR(pcmC0D1c, 0666, c0d1c_show, NULL);
#endif

static struct attribute *attrs[] = {
	&c0d0p_attribute.attr,
	&c0d0c_attribute.attr,
#if IS_ENABLED(CONFIG_ARCH_TZ3000)
	&c0d1p_attribute.attr,
	&c0d1c_attribute.attr,
#endif
	NULL,   /* need to NULL terminate the list of attributes */
};

static struct attribute_group attr_group = {
	.attrs = attrs,
};
static int al_tzxxx_sysfs_init(void)
{
	int ret;

	al_kobj = kobject_create_and_add("applite_pcm", kernel_kobj);
	if (!al_kobj)
		return -ENOMEM;

	ret = sysfs_create_group(al_kobj, &attr_group);
	if (ret) {
		kobject_put(al_kobj);
		al_kobj = NULL;
	}

	return ret;
}

static void al_tzxxx_sysfs_exit(void)
{
	if (al_kobj)
		kobject_put(al_kobj);
}
#endif

static int al_tzxxx_suspend(struct device *dev)
{
	DBG("enter\n");
	DBG("refcount:%ld\n", module_refcount(dev->driver->owner->mkobj.mod));
	if (module_refcount(dev->driver->owner->mkobj.mod) > 0)
		return -EBUSY;

	return 0;
}

static int al_tzxxx_resume(struct device *dev)
{
	DBG("enter\n");
	return 0;
}

static int al_tzxxx_runtime_suspend(struct device *dev)
{
	DBG("enter\n");
	al_i2s_hw_reset(1); /* reset on */
	return 0;
}

static int al_tzxxx_runtime_resume(struct device *dev)
{
	DBG("enter(%p)\n", dev);
	al_i2s_hw_reset(0); /* reset off */
	return 0;
}

static int __devinit al_tzxxx_probe(struct platform_device *pdev)
{
	struct snd_soc_card *card = &al_tzxxx;
	struct al_tzxxx_priv *priv;
	char *audioclk, *audiofmt;
	unsigned int setclk, setfmt;
	int link_num;
	int i;
	int ret;

	DBG("enter\n");

	/* check module parameter */
	if (!strnicmp(mod_data.audioclk_parm,
			MOD_PARM_AUDIOCLK_24_5760MHZ, 10)) {
		g_audio_clock = AUDIO_CLOCK_24_5760MHZ;
		audioclk = mod_data.audioclk_parm;
		setclk = 24576000;
	} else if (!strnicmp(mod_data.audioclk_parm,
			MOD_PARM_AUDIOCLK_18_4320MHZ, 10)) {
		g_audio_clock = AUDIO_CLOCK_18_4320MHZ;
		audioclk = mod_data.audioclk_parm;
		setclk = 18432000;
	} else if (!strnicmp(mod_data.audioclk_parm,
			MOD_PARM_AUDIOCLK_12_2880MHZ, 10)) {
		g_audio_clock = AUDIO_CLOCK_12_2880MHZ;
		audioclk = mod_data.audioclk_parm;
		setclk = 12288000;
	} else if (!strnicmp(mod_data.audioclk_parm,
			MOD_PARM_AUDIOCLK_11_2896MHZ, 10)) {
		g_audio_clock = AUDIO_CLOCK_11_2896MHZ;
		audioclk = mod_data.audioclk_parm;
		setclk = 11289600;
	} else {
		dev_warn(&pdev->dev, "audioclk is unkown (%s)\n",
			mod_data.audioclk_parm);
#if defined(CONFIG_AUDIO_CLOCK_245760000HZ)
		g_audio_clock = AUDIO_CLOCK_24_5760MHZ;
		audioclk = MOD_PARM_AUDIOCLK_24_5760MHZ;
		setclk = 24576000;
#elif defined(CONFIG_AUDIO_CLOCK_184320000HZ)
		g_audio_clock = AUDIO_CLOCK_18_4320MHZ;
		audioclk = MOD_PARM_AUDIOCLK_18_5760MHZ;
		setclk = 18432000;
#elif defined(CONFIG_AUDIO_CLOCK_122880000HZ)
		g_audio_clock = AUDIO_CLOCK_12_2880MHZ;
		audioclk = MOD_PARM_AUDIOCLK_12_2880MHZ;
		setclk = 12288000;
#elif defined(CONFIG_AUDIO_CLOCK_112896000HZ)
		g_audio_clock = AUDIO_CLOCK_11_2896MHZ;
		audioclk = MOD_PARM_AUDIOCLK_11_2896MHZ;
		setclk = 11289600;
#else
		g_audio_clock = AUDIO_CLOCK_24_5760MHZ;
		audioclk = MOD_PARM_AUDIOCLK_24_5760MHZ;
		setclk = 24576000;
#endif
		dev_warn(&pdev->dev, "Audio Clock is set to %sMHz.\n",
			audioclk);
	}

	if (!strnicmp(mod_data.audiofmt_parm,
			MOD_PARM_AUDIOFMT_I2S, 10)) {
		g_audio_format = AUDIO_FORMAT_I2S;
		audiofmt = mod_data.audiofmt_parm;
		setfmt = SND_SOC_DAIFMT_I2S;
	} else if (!strnicmp(mod_data.audiofmt_parm,
			MOD_PARM_AUDIOFMT_LR, 10)) {
		g_audio_format = AUDIO_FORMAT_LR;
		audiofmt = mod_data.audiofmt_parm;
		setfmt = SND_SOC_DAIFMT_I2S;
	} else {
		dev_warn(&pdev->dev, "audiofmt is unkown (%s)\n",
			mod_data.audiofmt_parm);
#if defined(CONFIG_AUDIO_FORMAT_I2S)
		g_audio_format = AUDIO_FORMAT_I2S;
		audiofmt = MOD_PARM_AUDIOFMT_I2S;
		setfmt = SND_SOC_DAIFMT_I2S;
#elif defined(CONFIG_AUDIO_FORMAT_LR)
		g_audio_format = AUDIO_FORMAT_LR;
		audiofmt = MOD_PARM_AUDIOFMT_LR;
		setfmt = SND_SOC_DAIFMT_I2S;
#else
		g_audio_format = AUDIO_FORMAT_I2S;
		audiofmt = MOD_PARM_AUDIOFMT_I2S;
		setfmt = SND_SOC_DAIFMT_I2S;
#endif
		dev_warn(&pdev->dev, "Audio Format is set to %s.\n",
			audiofmt);
	}

	if ((mod_data.period_param < 0) || (mod_data.period_param > 8)) {
		dev_warn(&pdev->dev, "invalid period parameter(1 to 8):%d\n",
			mod_data.period_param);
		mod_data.period_param = CONFIG_AUDIO_PERIOD_BYTES;
	}
	g_period_byte = mod_data.period_param;
#ifndef USE_I2S_INTERRUPT
	snd_al_pcm_period_byte(g_period_byte);
#endif

	priv = vzalloc(sizeof(struct al_tzxxx_priv));
	if (!priv) {
		dev_err(&pdev->dev, "Failed to allocate private data!\n");
		return -ENOMEM;
	}
	memset(priv, 0x00, sizeof(struct al_tzxxx_priv));
	priv->codec_sysclk = setclk;

#if IS_ENABLED(CONFIG_ARCH_TZ3000)
	if (!machine_is_tz3000rb4()) {
		/* Andes */
		/* I2S0 */
		al_tzxxx_dai[0].codec_dai_name = "tlv320adc3xxx-hifi";
		al_tzxxx_dai[0].codec_name = "tlv320adc3xxx-codec.3-0018";
		al_tzxxx_dai[0].init = al_tzxxx_init_tlv320adc3xxx_andes;
	} else {
		/* Manaslu */
		/* I2S0 */
		al_tzxxx_dai[0].codec_dai_name = "tlv320aic3110-hifi";
		al_tzxxx_dai[0].codec_name = "tlv320aic3110-codec.0-0018";
		al_tzxxx_dai[0].init = al_tzxxx_init_tlv320aic3110_manaslu;
	}
	link_num = 1; /* 0: I2SO0/I2SO1 */
#endif /* CONFIG_ARCH_TZ3000 */

#if IS_ENABLED(CONFIG_ARCH_TZ2000)
	if (!machine_is_tz2000rb3()) {
		/* Gregory */
		/* I2S0 */
		al_tzxxx_dai[0].codec_dai_name = "tlv320adc3xxx-hifi";
		al_tzxxx_dai[0].codec_name = "tlv320adc3xxx-codec.3-0018";
		al_tzxxx_dai[0].init = al_tzxxx_init_tlv320adc3xxx_gregory;
	} else {
		/* Montblanc */
		/* I2SI0 */
		al_tzxxx_dai[0].codec_dai_name = "tlv320aic3110-hifi";
		al_tzxxx_dai[0].codec_name = "tlv320aic3110-codec.3-0018";
		al_tzxxx_dai[0].init = al_tzxxx_init_tlv320aic3110_montblanc;
	}
	link_num = 1; /* 0: I2SO0/I2SO1 */
#endif

	card->dai_link = al_tzxxx_dai;
	card->num_links = link_num;
	card->dev = &pdev->dev;
	platform_set_drvdata(pdev, card);

	snd_soc_card_set_drvdata(card, priv);
	ret = snd_soc_register_card(card);
	if (ret) {
		dev_err(&pdev->dev, "snd_soc_register_card failed (%d)\n",
			ret);
		vfree(priv);
		return ret;
	}

	for (i = 0; i < AL_I2S_CHMAX; i++)
		i2s_substream[i] = NULL;

#ifdef APPLITE_SND_SYSFS
	al_tzxxx_sysfs_init();
#endif

	dev_dbg(&pdev->dev, "i2s version:%x\n", al_i2s_get_version());

	dev_info(&pdev->dev, "ApP-Lite Audio Driver [%s] Initialized [Audio Clock:%sMHz][Audio Format:%s][Period Byte:%dKbyte]\n",
		DRIVER_VERSION_STRING, audioclk, audiofmt, g_period_byte);

	return 0;
}

static int __devexit al_tzxxx_remove(struct platform_device *pdev)
{
	struct snd_soc_card *card = platform_get_drvdata(pdev);
	struct al_tzxxx_priv *priv = snd_soc_card_get_drvdata(card);

	DBG("enter\n");

#ifdef APPLITE_SND_SYSFS
	al_tzxxx_sysfs_exit();
#endif

	snd_soc_unregister_card(card);
	platform_set_drvdata(pdev, NULL);
	vfree(priv);

	dev_info(&pdev->dev, "ApP-Lite Audio Driver Uninitialized\n");

	return 0;
}

static const struct dev_pm_ops al_tzxxx_pm_ops = {
	.suspend = al_tzxxx_suspend,
	.resume = al_tzxxx_resume,
	.runtime_suspend = al_tzxxx_runtime_suspend,
	.runtime_resume = al_tzxxx_runtime_resume,
};

static struct platform_driver al_tzxxx_audio_driver = {
	.driver = {
		.name = "applite-tzxxx",
		.owner = THIS_MODULE,
	},
	.probe = al_tzxxx_probe,
	.remove = __devexit_p(al_tzxxx_remove),
};

module_platform_driver(al_tzxxx_audio_driver);

MODULE_AUTHOR("TOSHIBA Corporation");
MODULE_DESCRIPTION("ApP Lite ALSA SoC Machine driver");
MODULE_LICENSE("GPL v2");
MODULE_VERSION(DRIVER_VERSION_STRING);
MODULE_ALIAS("platform:applite-tzxxx");
