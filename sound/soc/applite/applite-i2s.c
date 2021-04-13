/*
 * sound/soc/applite/applite-i2s.c
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

#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/dma-mapping.h>
#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/time.h>
#include <linux/fsl/mxs-dma.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/soc.h>
#include <asm/mach-types.h>
#include <mach/hardware.h>
#include <linux/pm_runtime.h>

#include "applite-tzxxx.h"
#include "applite-dma.h"
#include "applite-i2s.h"

#define xprintk(level, fmt, args...) \
	printk(level "snd-applite-i2s: " fmt , ## args)

#ifdef APPLITE_I2S_DEBUG
	#define dprintk(level, fmt, args...) \
		printk(level "snd-applite-i2s:%s(): " fmt , __func__ , ## args)
#else
	#define dprintk(level, fmt, args...)
#endif

#define ERROR(fmt, args...) \
	xprintk(KERN_ERR , fmt , ## args)
#define INFO(fmt, args...) \
	xprintk(KERN_INFO , fmt , ## args)
#define DBG(fmt, args...) \
	dprintk(KERN_ERR , fmt , ## args)

#define AL_I2S_RATES		(SNDRV_PCM_RATE_8000_192000 | \
				 SNDRV_PCM_RATE_KNOT)
#define AL_I2S_FORMATS \
	(SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S32_LE)

#include "audio_config.h"


static unsigned int al_i2s_reset_bit[] = {
	PMU_SOFTRESETON_I2SO0,	/* I2SO0 */
	PMU_SOFTRESETON_I2SI0,	/* I2SI0 */
#if IS_ENABLED(CONFIG_ARCH_TZ3000)
	PMU_SOFTRESETON_I2SO1,	/* I2SO1 */
	PMU_SOFTRESETON_I2SI1,	/* I2SI1 */
#endif
};

#if IS_ENABLED(CONFIG_ARCH_TZ3000)
static unsigned int al_i2s_clock_sel_bit[] = {
	GCONF_I2SSEL_I2SSEL0,	/* I2SO0 */
	GCONF_I2SSEL_I2SSEL1,	/* I2SI0 */
	GCONF_I2SSEL_I2SSEL2,	/* I2SO1 */
	GCONF_I2SSEL_I2SSEL2,	/* I2SI1 */
};

static int al_i2s_asdioc_sel[] = {
	-1,	/* I2SO0:non */
	-1,	/* I2SI0:non */
	 0,	/* I2SO1:bit off */
	 1	/* I2SI1:bit on*/
};
#endif

#if IS_ENABLED(CONFIG_ARCH_TZ3000)
enum clk_name {
	e_CLK_I2SI0 = 0,
	e_CLK_I2SI1,
	e_CLK_I2SO0,
	e_CLK_I2SO1,
	e_CLK_I2SC0,
	e_CLK_AMCLK,
	e_CLK_IO_AMCLKO,
	e_CLK_MAX_NUM
};
#else /* !CONFIG_ARCH_TZ3000 */
enum clk_name {
	e_CLK_I2SI0 = 0,
	e_CLK_I2SO0,
	e_CLK_I2SC0,
	e_CLK_AMCLK,
	e_CLK_IO_AMCLKO,
	e_CLK_MAX_NUM
};
#endif /* CONFIG_ARCH_TZ3000 */

static struct clk *al_i2s_clk;
static unsigned int i2s_usecount;

int al_i2s_clk_setup(struct device *dev)
{
	al_i2s_clk = clk_get(dev, "i2s");
	if (IS_ERR(al_i2s_clk)) {
		dev_err(dev, "clk_get(%s, %s) failed\n",
			dev_name(dev), "i2s");
		return -EFAULT;
	}
	return 0;
}
EXPORT_SYMBOL_GPL(al_i2s_clk_setup);

void al_i2s_clk_allput(void)
{
	clk_put(al_i2s_clk);
}
EXPORT_SYMBOL_GPL(al_i2s_clk_allput);

int al_i2s_hw_reset(int on)
{
	void __iomem *iomem;

	iomem = ioremap(CPU_PMU_REG_BASE, CPU_PMU_REG_SIZE);
	if (!iomem)
		return -ENXIO;
	DBG("enter on/off=%d\n", on);
	if (!on) {
		/* reset off */
		reg_out(PMU_SOFTRESETON_ALL,
			REG_PMU(iomem, SoftResetOn_periSS_2_OFFS));
#if 1
		clk_prepare_enable(al_i2s_clk);
#else
		reg_out(PMU_CLOCKGATINGOFF_ALL,
			REG_PMU(iomem, ClockGatingOff_periSS_2_OFFS));
#endif
		reg_out(PMU_SOFTRESETOFF_ALL,
			REG_PMU(iomem, SoftResetOff_periSS_2_OFFS));
	} else {
		/* reset on */
		reg_out(PMU_SOFTRESETON_ALL,
			REG_PMU(iomem, SoftResetOn_periSS_2_OFFS));
#if 1
		clk_disable_unprepare(al_i2s_clk);
#else
		reg_out(PMU_CLOCKGATINGON_ALL,
			REG_PMU(iomem, ClockGatingOn_periSS_2_OFFS));
#endif
	}
	iounmap(iomem);

	return 0;
}
EXPORT_SYMBOL_GPL(al_i2s_hw_reset);

int al_i2s_hw_busy(int mych)
{
	void __iomem *iomem;
	u32 regadrs;
#if IS_ENABLED(CONFIG_ARCH_TZ3000)
	unsigned int selector;
#endif
	unsigned int busy[AL_I2S_CHMAX];
	int i;

	DBG("%d:enter\n", mych);

	for (i = 0; i < AL_I2S_CHMAX; i++)
		busy[i] = 0;

#if IS_ENABLED(CONFIG_ARCH_TZ3000)
	iomem = ioremap(CPU_GCONF_REG_BASE, CPU_GCONF_REG_SIZE);
	regadrs = (u32)((unsigned long)iomem);
	reg_in(&selector, REG_GCONF(regadrs, I2SSEL_OFFS));
	DBG("I2SSEL=0x%08x\n", selector);
	iounmap(iomem);

	/* I2SO* */
	iomem = ioremap(CPU_I2SO_REG_BASE, CPU_I2SO_REG_SIZE);
	regadrs = (u32)((unsigned long)iomem);
	if (mych != AL_I2SO0_CH) {
		reg_in(&busy[AL_I2SO0_CH], REG_I2S(regadrs, BUSY_OFS));
		DBG("I2SO0_BUSY=0x%08x\n", busy[AL_I2SO0_CH]);
		busy[AL_I2SO0_CH] &= (1<<I2S_BUSY_BUSY_SHIFT);
		if (busy[AL_I2SO0_CH]) {
			if (selector&GCONF_I2SSEL_I2SSEL0) {
				/* i2s slave */
				busy[AL_I2SO0_CH] = 0;
			}
		}
	}
	if (mych != AL_I2SO1_CH) {
		reg_in(&busy[AL_I2SO1_CH], REG_I2S(regadrs+0x1000, BUSY_OFS));
		DBG("I2SO1_BUSY=0x%08x\n", busy[AL_I2SO1_CH]);
		busy[AL_I2SO1_CH] &= (1<<I2S_BUSY_BUSY_SHIFT);
		if (busy[AL_I2SO1_CH]) {
			if (selector&GCONF_I2SSEL_I2SSEL2) {
				/* i2s slave */
				busy[AL_I2SO1_CH] = 0;
			}
		}
	}
	iounmap(iomem);

	/* I2SI* */
	iomem = ioremap(CPU_I2SI_REG_BASE, CPU_I2SI_REG_SIZE);
	regadrs = (u32)((unsigned long)iomem);
	if (mych != AL_I2SI0_CH) {
		reg_in(&busy[AL_I2SI0_CH], REG_I2S(regadrs, BUSY_OFS));
		DBG("I2SI0_BUSY=0x%08x\n", busy[AL_I2SI0_CH]);
		busy[AL_I2SI0_CH] &= (1<<I2S_BUSY_BUSY_SHIFT);
		if (busy[AL_I2SI0_CH]) {
			if (selector&GCONF_I2SSEL_I2SSEL1) {
				/* i2s slave */
				busy[AL_I2SI0_CH] = 0;
			}
		}
	}
	if (mych != AL_I2SI1_CH) {
		reg_in(&busy[AL_I2SI1_CH], REG_I2S(regadrs+0x1000, BUSY_OFS));
		DBG("I2SI1_BUSY=0x%08x\n", busy[AL_I2SI1_CH]);
		busy[AL_I2SI1_CH] &= (1<<I2S_BUSY_BUSY_SHIFT);
		if (busy[AL_I2SI1_CH]) {
			if (selector&GCONF_I2SSEL_I2SSEL2) {
				/* i2s slave */
				busy[AL_I2SI1_CH] = 0;
			}
		}
	}
	iounmap(iomem);
#else
	/* I2SO* */
	iomem = ioremap(CPU_I2SO_REG_BASE, CPU_I2SO_REG_SIZE);
	regadrs = (u32)iomem;
	if (mych != AL_I2SO0_CH) {
		reg_in(&busy[AL_I2SO0_CH], REG_I2S(regadrs, BUSY_OFS));
		DBG("I2SO0_BUSY=0x%08x\n", busy[AL_I2SO0_CH]);
		busy[AL_I2SO0_CH] &= (1<<I2S_BUSY_BUSY_SHIFT);
	}
	iounmap(iomem);

	/* I2SI* */
	iomem = ioremap(CPU_I2SI_REG_BASE, CPU_I2SI_REG_SIZE);
	regadrs = (u32)iomem;
	if (mych != AL_I2SI0_CH) {
		reg_in(&busy[AL_I2SI0_CH], REG_I2S(regadrs, BUSY_OFS));
		DBG("I2SI0_BUSY=0x%08x\n", busy[AL_I2SI0_CH]);
		busy[AL_I2SI0_CH] &= (1<<I2S_BUSY_BUSY_SHIFT);
	}
	iounmap(iomem);
#endif
	for (i = 0; i < AL_I2S_CHMAX; i++) {
		if (busy[i])
			return 1; /* busy */
	}

	return 0;
}
EXPORT_SYMBOL_GPL(al_i2s_hw_busy);

int al_i2s_get_version(void)
{
	return 0x100;
}
EXPORT_SYMBOL_GPL(al_i2s_get_version);

static int al_i2s_set_dai_sysclk(struct snd_soc_dai *cpu_dai,
			int clk_id, unsigned int freq, int dir)
{
	struct al_i2s *priv = snd_soc_dai_get_drvdata(cpu_dai);

	DBG("I2S%d:enter(freq=%d)\n", priv->i2s_param[SNDRV_PCM_STREAM_PLAYBACK].ch ? 1 : 0, freq);

	switch (freq) {
	case 24576000:
		/* Audio Clock is 24.5760MHz */
		priv->audioclk_num[SNDRV_PCM_STREAM_PLAYBACK] = AUDIO_CLOCK_24_5760MHZ;
		priv->audioclk_num[SNDRV_PCM_STREAM_CAPTURE] = AUDIO_CLOCK_24_5760MHZ;
		break;
	case 18432000:
		/* Audio Clock is 18.4320MHz */
		priv->audioclk_num[SNDRV_PCM_STREAM_PLAYBACK] = AUDIO_CLOCK_18_4320MHZ;
		priv->audioclk_num[SNDRV_PCM_STREAM_CAPTURE] = AUDIO_CLOCK_18_4320MHZ;
		break;
	case 12288000:
		/* Audio Clock is 12.2880MHz */
		priv->audioclk_num[SNDRV_PCM_STREAM_PLAYBACK] = AUDIO_CLOCK_12_2880MHZ;
		priv->audioclk_num[SNDRV_PCM_STREAM_CAPTURE] = AUDIO_CLOCK_12_2880MHZ;
		break;
	case 11289600:
		/* Audio Clock is 11.2896MHz */
		priv->audioclk_num[SNDRV_PCM_STREAM_PLAYBACK] = AUDIO_CLOCK_11_2896MHZ;
		priv->audioclk_num[SNDRV_PCM_STREAM_CAPTURE] = AUDIO_CLOCK_11_2896MHZ;
		break;
	default:
		/* i2s slave */
		priv->audioclk_num[SNDRV_PCM_STREAM_PLAYBACK] = AUDIO_CLOCK_MAX;
		priv->audioclk_num[SNDRV_PCM_STREAM_CAPTURE] = AUDIO_CLOCK_MAX;
		break;
	}
	priv->mclk[SNDRV_PCM_STREAM_PLAYBACK] = freq;
	priv->mclk[SNDRV_PCM_STREAM_CAPTURE] = freq;

	return 0;
}

static int al_i2s_set_dai_fmt(struct snd_soc_dai *cpu_dai, unsigned int fmt)
{
	struct al_i2s *priv = snd_soc_dai_get_drvdata(cpu_dai);

	DBG("I2S%d:enter\n", priv->i2s_param[SNDRV_PCM_STREAM_PLAYBACK].ch ? 1 : 0);

	priv->fmt[SNDRV_PCM_STREAM_PLAYBACK] = (fmt&SND_SOC_DAIFMT_FORMAT_MASK);
	priv->fmt[SNDRV_PCM_STREAM_CAPTURE] = (fmt&SND_SOC_DAIFMT_FORMAT_MASK);

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		priv->fmt_num[SNDRV_PCM_STREAM_PLAYBACK] = AUDIO_FORMAT_I2S;
		priv->fmt_num[SNDRV_PCM_STREAM_CAPTURE] = AUDIO_FORMAT_I2S;
		break;
	case SND_SOC_DAIFMT_DSP_A:
	case SND_SOC_DAIFMT_DSP_B:
	case SND_SOC_DAIFMT_RIGHT_J:
	case SND_SOC_DAIFMT_LEFT_J:
		priv->fmt_num[SNDRV_PCM_STREAM_PLAYBACK] = AUDIO_FORMAT_MAX;
		priv->fmt_num[SNDRV_PCM_STREAM_CAPTURE] = AUDIO_FORMAT_MAX;
		break;
	default:
		dev_err(priv->dev, "unsupported format(%x)\n", fmt);
		return -EINVAL;
	}

	return 0;
}

static int al_i2s_startup(struct snd_pcm_substream *substream,
				struct snd_soc_dai *cpu_dai)
{
#ifdef APPLITE_I2S_DEBUG
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
#endif
	struct al_i2s *priv = snd_soc_dai_get_drvdata(cpu_dai);
	u32 fifo;
	int stream = substream->stream;

	DBG("I2S%d:enter(%s)\n", priv->i2s_param[SNDRV_PCM_STREAM_PLAYBACK].ch ? 1 : 0, rtd->dai_link->stream_name);

	i2s_usecount++;
#if IS_ENABLED(CONFIG_PM_RUNTIME)
	DBG("pm_runtime_get_sync(%p)\n", priv->dev);
	pm_runtime_get_sync(priv->dev);
#else
	if (i2s_usecount == 1)
		al_i2s_hw_reset(0); /* reset off */
#endif
	DBG("i2s_usecount(%d)\n", i2s_usecount);

	fifo = REG_I2S(priv->iomem[stream], LMEM00_OFS);
	DBG("%d:fifo:%08x\n", priv->i2s_param[stream].ch, fifo);
	snd_soc_dai_set_dma_data(cpu_dai, substream, (void *)fifo);

	priv->i2s_param[stream].status = I2S_STATUS_STARTUP;

	return 0;
}

static void al_i2s_shutdown(struct snd_pcm_substream *substream,
				struct snd_soc_dai *cpu_dai)
{
#ifdef APPLITE_I2S_DEBUG
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
#endif
	struct al_i2s *priv = snd_soc_dai_get_drvdata(cpu_dai);
	int stream = substream->stream;

	DBG("I2S%d:enter(%s)\n", priv->i2s_param[SNDRV_PCM_STREAM_PLAYBACK].ch ? 1 : 0, rtd->dai_link->stream_name);

	i2s_usecount--;
#if IS_ENABLED(CONFIG_PM_RUNTIME)
	DBG("pm_runtime_put_sync(%p)\n", priv->dev);
	pm_runtime_put_sync(priv->dev);
#else
	if (i2s_usecount == 0)
		al_i2s_hw_reset(1); /* reset on */
#endif
	DBG("i2s_usecount(%d)\n", i2s_usecount);

	priv->i2s_param[stream].status = I2S_STATUS_SHUTDOWN;

	return;
}

static int al_i2s_format(struct al_i2s *priv, snd_pcm_format_t format)
{
	int rtn = CONFIG_DATA_FORMAT_MAX;
	switch (format) {
	case SNDRV_PCM_FORMAT_S16_LE:
		rtn = CONFIG_DATA_FORMAT_16BIT; /* 16bit */
		break;
	case SNDRV_PCM_FORMAT_S32_LE:
		rtn = CONFIG_DATA_FORMAT_32BIT; /* 32bit */
		break;
	default:
		dev_err(priv->dev, "unsupported format [format=%08x]\n",
			format);
		break;
	}

	return rtn;
}

static unsigned int al_i2s_regval(struct al_i2s *priv,
		struct al_i2s_param *i2s_param, int ch, int stream, int reg)
{
	int err = 0;
	u32 val = INVALID_REG_VAL;
	u32 data_format;
	u32 audio_wave;

	switch (reg) {
	case I2S_AUDIOSET_OFS:
		data_format = al_i2s_format(priv, i2s_param->format);
		if (i2s_param->channels == 1)
			audio_wave = CONFIG_WAVE_MONO;
		else
			audio_wave = CONFIG_WAVE_STEREO;
		if (priv->master[stream]) {
			/* i2s master */
			err = get_audio_config_val(
				priv->audioclk_num[stream], data_format,
				audio_wave, (u32)i2s_param->rate, &val);
		} else {
			/* i2s slave */
			err = get_audio_config_default(
				priv->audioclk_num[stream], data_format,
				audio_wave, (u32)i2s_param->rate, &val);
		}
		if (err < 0) {
			dev_err(priv->dev, "unsupported audio set\n");
			pr_err("audio clock   : %d\n", priv->mclk[stream]);
			pr_err("channels      : %d\n", i2s_param->channels);
			pr_err("format        : 0x%08x\n", i2s_param->format);
			pr_err("sampling rate : 0x%08x\n", i2s_param->rate);
			return INVALID_REG_VAL;
		}
		break;

	case I2S_MODESET_OFS:
		if (ch == AL_I2SC_CH)
			val = I2S_MODESET_IESEL_MASTER;
		else
			val = I2S_MODESET_IESEL_SLAVE;
		if (i2s_param->channels > 1) {
			switch (priv->fmt_num[stream]) {
			case AUDIO_FORMAT_I2S:
				/* I2S Stereo */
				val |= I2S_MODESET_WS_I2S_STEREO;
				break;
			case AUDIO_FORMAT_LR:
				/* LR Stereo */
				val |= I2S_MODESET_WS_LR_STEREO;
				break;
			case AUDIO_FORMAT_MAX:
				/* LR Stereo */
				val |= I2S_MODESET_WS_LR_STEREO;
				break;
			}
		} else {
			/* PCM Mono */
			if (!priv->mono_rev)
				val |= I2S_MODESET_WS_MONO;
			else
				val |= I2S_MODESET_WS_MONO_REV;
		}
		break;
	}
	return val;
}

#ifdef APPLITE_I2S_DEBUG
static char *al_i2s_fmt_to_str(snd_pcm_format_t format)
{
	switch (format) {
	case SNDRV_PCM_FORMAT_S8:
		return "S8";
	case SNDRV_PCM_FORMAT_U8:
		return "U8";
	case SNDRV_PCM_FORMAT_S16_LE:
		return "S16_LE";
	case SNDRV_PCM_FORMAT_S16_BE:
		return "S16_BE";
	case SNDRV_PCM_FORMAT_U16_LE:
		return "U16_LE";
	case SNDRV_PCM_FORMAT_U16_BE:
		return "U16_BE";
	case SNDRV_PCM_FORMAT_S24_LE:
		return "S24_LE";
	case SNDRV_PCM_FORMAT_S24_BE:
		return "S24_BE";
	case SNDRV_PCM_FORMAT_U24_LE:
		return "U24_LE";
	case SNDRV_PCM_FORMAT_U24_BE:
		return "U24_BE";
	case SNDRV_PCM_FORMAT_S32_LE:
		return "S32_LE";
	case SNDRV_PCM_FORMAT_S32_BE:
		return "S32_BE";
	case SNDRV_PCM_FORMAT_U32_LE:
		return "U32_LE";
	case SNDRV_PCM_FORMAT_U32_BE:
		return "U32_BE";
	default:
		return "unkown";
	}

	return "unkown";
}
#endif

static int al_i2s_hw_params(struct snd_pcm_substream *substream,
			     struct snd_pcm_hw_params *hw_params,
			     struct snd_soc_dai *cpu_dai)
{
#ifdef APPLITE_I2S_DEBUG
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
#endif
	struct al_i2s *priv = snd_soc_dai_get_drvdata(cpu_dai);
	unsigned long flags;
	int stream = substream->stream;

	DBG("I2S%d:enter(%s)\n", priv->i2s_param[SNDRV_PCM_STREAM_PLAYBACK].ch ? 1 : 0, rtd->dai_link->stream_name);

	spin_lock_irqsave(&priv->lock, flags);

	priv->i2s_param[stream].substream = substream;
	priv->i2s_param[stream].format = params_format(hw_params);
	priv->i2s_param[stream].rate = params_rate(hw_params);
	priv->i2s_param[stream].channels = params_channels(hw_params);
	priv->i2s_param[stream].offset = 0;
	priv->i2s_param[stream].periods = params_periods(hw_params);
	priv->i2s_param[stream].period_bytes = params_period_bytes(hw_params);

	DBG("format=%s(0x%x),channels=%d,rate=%d\n",
		al_i2s_fmt_to_str(priv->i2s_param[stream].format),
		priv->i2s_param[stream].format,
		priv->i2s_param[stream].channels,
		priv->i2s_param[stream].rate
	);
	DBG("%d:period_bytes=%d,periods=%d\n",
		priv->i2s_param[stream].ch,
		priv->i2s_param[stream].period_bytes,
		priv->i2s_param[stream].periods
	);

	/* check parameter */
	if (al_i2s_regval(priv,
			&priv->i2s_param[stream],
			priv->i2s_param[stream].ch,
			stream,
			I2S_AUDIOSET_OFS) == INVALID_REG_VAL) {
		spin_unlock_irqrestore(&priv->lock, flags);
		return -EINVAL;
	}

	priv->i2s_param[stream].status = I2S_STATUS_RUNNING;

	spin_unlock_irqrestore(&priv->lock, flags);

	return 0;
}

static int al_i2s_start(struct al_i2s *priv, int stream)
{
	unsigned int outval;
	u32 regadrs;

#if IS_ENABLED(CONFIG_ARCH_TZ3000)
	/* GCONF_I2SSEL */
	regadrs = (u32)((unsigned long)priv->iobase[IOBASE_GCONF]);
	reg_in(&outval, REG_GCONF(regadrs, I2SSEL_OFFS));
	if (priv->master[stream]) {
		/* i2s master */
		outval &= ~al_i2s_clock_sel_bit[priv->i2s_param[stream].ch];
	} else {
		/* i2s slave */
		outval |= al_i2s_clock_sel_bit[priv->i2s_param[stream].ch];
	}
	if (!al_i2s_asdioc_sel[priv->i2s_param[stream].ch])
		outval &= ~GCONF_I2SSEL_OE_N_IN;
	else
		outval |= GCONF_I2SSEL_OE_N_IN;
	reg_out(outval, REG_GCONF(regadrs, I2SSEL_OFFS));
#endif

	/* setup I2SC module */
	if (!al_i2s_hw_busy(priv->i2s_param[stream].ch) &&
	    (priv->master[stream] || priv->clock_out[stream])) {
		/* Bit clokc, L/R clock out */
		if (priv->master[stream]) {
			switch (priv->audioclk_num[stream]) {
			case AUDIO_CLOCK_24_5760MHZ:
				outval = PMU_AUDIO_CLOCK_0_24_5760MHZ;
				break;
			case AUDIO_CLOCK_18_4320MHZ:
				outval = PMU_AUDIO_CLOCK_0_18_4320MHZ;
				break;
			case AUDIO_CLOCK_12_2880MHZ:
				outval = PMU_AUDIO_CLOCK_0_12_2880MHZ;
				break;
			case AUDIO_CLOCK_11_2896MHZ:
				outval = PMU_AUDIO_CLOCK_0_11_2896MHZ;
				break;
			default:
				dev_err(priv->dev, "unsupported audio clock [%d]\n", priv->mclk[stream]);
				return -EINVAL;
			}
		} else {
			outval = PMU_AUDIO_CLOCK_0_11_2896MHZ;
		}
		regadrs = (u32)((unsigned long)priv->iobase[IOBASE_PMU]);
		reg_out(outval, REG_PMU(regadrs, AUDIO_CLOCK_0_OFFS));

		/* synchronous clock generation */
		regadrs = (u32)((unsigned long)priv->iobase[IOBASE_I2SC]);
		outval = al_i2s_regval(priv,
				&priv->i2s_param[stream],
				AL_I2SC_CH,
				stream,
				I2S_MODESET_OFS);
		if (outval == INVALID_REG_VAL)
			return -EINVAL;
		reg_out(outval, REG_I2S(regadrs, MODESET_OFS));
		outval = al_i2s_regval(priv,
				&priv->i2s_param[stream],
				AL_I2SC_CH,
				stream,
				I2S_AUDIOSET_OFS);
		if (outval == INVALID_REG_VAL)
			return -EINVAL;
		reg_out(outval, REG_I2S(regadrs, AUDIOSET_OFS));
		outval = 1 << I2S_START_MCKSTART_SHIFT;
		reg_out(outval, REG_I2S(regadrs, START_OFS));
	}

	/* setup I2S* module */
	regadrs = (u32)((unsigned long)priv->iobase[stream]);
	outval = al_i2s_regval(priv,
			&priv->i2s_param[stream],
			priv->i2s_param[stream].ch,
			stream,
			I2S_MODESET_OFS);
	if (outval == INVALID_REG_VAL)
		return -EINVAL;
	reg_out(outval, REG_I2S(regadrs, MODESET_OFS));
	outval = al_i2s_regval(priv,
			&priv->i2s_param[stream],
			priv->i2s_param[stream].ch,
			stream,
			I2S_AUDIOSET_OFS);
	if (outval == INVALID_REG_VAL)
		return -EINVAL;
	reg_out(outval, REG_I2S(regadrs, AUDIOSET_OFS));

	/* setup interrupt mask */
#ifndef USE_I2S_INTERRUPT
	outval = 1 << I2S_INT_INT_SHIFT;
#else
	outval = 0;
#endif
	reg_out(outval, REG_I2S(regadrs, INTMASK_OFS));
	outval = 2 << I2S_INTSET_INTSET_SHIFT;
	reg_out(outval, REG_I2S(regadrs, INTSET_OFS));
	outval = 1 << I2S_START_MCKSTART_SHIFT;
	reg_out(outval, REG_I2S(regadrs, START_OFS));

	/* release mute */
	outval = 1 << I2S_MUTE_MUTE_SHIFT;
	reg_out(outval, REG_I2S(regadrs, MUTE_OFS));

	/* start transfer */
	outval = 1 << I2S_START_SPKSTART_SHIFT;
	reg_out(outval, REG_I2S(regadrs, START_OFS));

	return 0;
}

static int al_i2s_stop(struct al_i2s *priv, int stream)
{
	unsigned int outval;
	u32 regadrs = (u32)((unsigned long)priv->iobase[stream]);

	/* mute */
	outval = 0 << I2S_MUTE_MUTE_SHIFT;
	reg_out(outval, REG_I2S(regadrs, MUTE_OFS));

	/* reset on I2S module */
	outval = al_i2s_reset_bit[priv->i2s_param[stream].ch];
	if (!al_i2s_hw_busy(priv->i2s_param[stream].ch) &&
	    (priv->master[stream] || priv->clock_out[stream]))
		outval |= PMU_SOFTRESETON_I2SC0;
	regadrs = (u32)((unsigned long)priv->iobase[IOBASE_PMU]);
	reg_out(outval, REG_PMU(regadrs, SoftResetOn_periSS_2_OFFS));

	/* reset off I2S module */
	reg_out(outval, REG_PMU(regadrs, SoftResetOff_periSS_2_OFFS));

	return 0;
}

static int al_i2s_trigger(struct snd_pcm_substream *substream, int cmd,
				struct snd_soc_dai *cpu_dai)
{
	int err = 0;
	int stream = substream->stream;
#ifdef APPLITE_I2S_DEBUG
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
#endif
	struct al_i2s *priv = snd_soc_dai_get_drvdata(cpu_dai);
	unsigned long flags;

	DBG("I2S%d:enter(%s)\n", priv->i2s_param[SNDRV_PCM_STREAM_PLAYBACK].ch ? 1 : 0, rtd->dai_link->stream_name);

	priv->i2s_param[stream].offset = 0;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		spin_lock_irqsave(&priv->lock, flags);
		err = al_i2s_start(priv, stream);
		spin_unlock_irqrestore(&priv->lock, flags);
		break;

	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		spin_lock_irqsave(&priv->lock, flags);
		err = al_i2s_stop(priv, stream);
		spin_unlock_irqrestore(&priv->lock, flags);
		break;
	}

	return err;
}

static const struct snd_soc_dai_ops al_i2s_dai_ops = {
	.startup = al_i2s_startup,
	.shutdown = al_i2s_shutdown,
	.trigger = al_i2s_trigger,
	.hw_params = al_i2s_hw_params,
	.set_sysclk = al_i2s_set_dai_sysclk,
	.set_fmt = al_i2s_set_dai_fmt,
};

static int al_i2s_dai_probe(struct snd_soc_dai *dai)
{
	struct al_i2s *priv = dev_get_drvdata(dai->dev);

	DBG("I2S%d:enter\n", priv->i2s_param[SNDRV_PCM_STREAM_PLAYBACK].ch ? 1 : 0);

	snd_soc_dai_set_drvdata(dai, priv);

	return 0;
}

#ifdef USE_I2S_INTERRUPT
static irqreturn_t al_i2s_irq_int(int irq, void *dev_id)
{
	struct al_i2s *priv = dev_id;
	unsigned int stat;
	u32 regadrs;
	int stream;

	if (priv->ioirq[I2SO_IRQ_INT] == irq) {
		regadrs = (u32)priv->iobase[IOBASE_I2SO];
		stream = SNDRV_PCM_STREAM_PLAYBACK;
	} else {
		regadrs = (u32)priv->iobase[IOBASE_I2SI];
		stream = SNDRV_PCM_STREAM_CAPTURE;
	}

	stat = __raw_readl((void __iomem *)REG_I2S(regadrs, INTSTAT_OFS));
	stat &= ~((1<<I2S_INT_ORERR_SHIFT)|(1<<I2S_INT_URERR_SHIFT));
	/*__raw_writel(stat, (void __iomem *)REG_I2S(regadrs, INTCLR_OFS));*/

	priv->i2s_param[stream].offset += priv->i2s_param[stream].period_bytes;
	priv->i2s_param[stream].offset %=
		priv->i2s_param[stream].period_bytes * priv->i2s_param[stream].periods;
#if 0
	ERROR("%d:offset=%lu(%d)\n", priv->i2s_param[stream].ch,
		priv->i2s_param[stream].offset, priv->i2s_param[stream].period_bytes);
#endif
	snd_pcm_period_elapsed(priv->i2s_param[stream].substream);

	return IRQ_RETVAL(IRQ_HANDLED);
}
#endif

static irqreturn_t al_i2s_irq_err(int irq, void *dev_id)
{
	struct al_i2s *priv = dev_id;
	unsigned int stat;
	u32 regadrs;

	if (priv->ioirq[I2SO_IRQ_ERR] == irq)
		regadrs = (u32)((unsigned long)priv->iobase[IOBASE_I2SO]);
	else
		regadrs = (u32)((unsigned long)priv->iobase[IOBASE_I2SI]);

	stat = __raw_readl((void __iomem *)REG_I2S(regadrs, INTSTAT_OFS));
	stat &= ~(1<<I2S_INT_INT_SHIFT);
	__raw_writel(stat, (void __iomem *)REG_I2S(regadrs, INTCLR_OFS));

	if (stat) {
		__raw_writel((1<<I2S_INT_URERR_SHIFT)|(1<<I2S_INT_ORERR_SHIFT),
			(void __iomem *)REG_I2S(regadrs, INTMASK_OFS));
	}

	return IRQ_RETVAL(IRQ_HANDLED);
}

static struct snd_soc_dai_driver applite_i2s_dai = {
	.name   = "applite-i2s",
	.probe  = al_i2s_dai_probe,
	.playback = {
		.channels_min = 1,
		.channels_max = 2,
		.rates = (SNDRV_PCM_RATE_8000_192000 | SNDRV_PCM_RATE_KNOT),
		.formats = (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S32_LE),
	},
	.capture = {
		.channels_min = 1,
		.channels_max = 2,
		.rates = (SNDRV_PCM_RATE_8000_192000 | SNDRV_PCM_RATE_KNOT),
		.formats = (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S32_LE),
	},
	.ops = &al_i2s_dai_ops,
};

static int __devinit al_i2s_probe(struct platform_device *pdev)
{
	int err = 0;
	int i;
	struct resource *res;
	struct al_i2s *priv;
	struct platform_device *soc_dai_dev;

	DBG("%d:enter\n", pdev->id);

	if ((pdev->id != 0) && (pdev->id != 1)) {
		dev_err(&pdev->dev, "illegal id %d\n", pdev->id);
		return -EINVAL;
	}

	priv = vzalloc(sizeof(struct al_i2s));
	if (!priv) {
		dev_err(&pdev->dev, "Failed to allocate private data!\n");
		return -ENOMEM;
	}
	memset(priv, 0x00, sizeof(struct al_i2s));

	priv->pdev = pdev;
	priv->dev = &pdev->dev;

	/* Playback(I2SO) */
	if (!pdev->id)
		priv->i2s_param[SNDRV_PCM_STREAM_PLAYBACK].ch = AL_I2SO0_CH;
	else
		priv->i2s_param[SNDRV_PCM_STREAM_PLAYBACK].ch = AL_I2SO1_CH;
	priv->i2s_param[SNDRV_PCM_STREAM_PLAYBACK].status = I2S_STATUS_SHUTDOWN;
	priv->audioclk_num[SNDRV_PCM_STREAM_PLAYBACK] = AUDIO_CLOCK_MAX;
	priv->fmt_num[SNDRV_PCM_STREAM_PLAYBACK] = AUDIO_FORMAT_MAX;

	/* Capture(I2SI) */
	if (!pdev->id)
		priv->i2s_param[SNDRV_PCM_STREAM_CAPTURE].ch = AL_I2SI0_CH;
	else
		priv->i2s_param[SNDRV_PCM_STREAM_CAPTURE].ch = AL_I2SI1_CH;
	priv->i2s_param[SNDRV_PCM_STREAM_CAPTURE].status = I2S_STATUS_SHUTDOWN;
	priv->audioclk_num[SNDRV_PCM_STREAM_CAPTURE] = AUDIO_CLOCK_MAX;
	priv->fmt_num[SNDRV_PCM_STREAM_CAPTURE] = AUDIO_FORMAT_MAX;

	spin_lock_init(&priv->lock);
	platform_set_drvdata(pdev, priv);
	i2s_usecount = 0;

	/* ioremap */
	for (i = 0; i < IOBASE_MAX; i++) {
		res = platform_get_resource(pdev, IORESOURCE_MEM, i);
		if (!res) {
			dev_err(&pdev->dev, "cannot find register resource %d\n", i);
			err = -EINVAL;
			goto __err1;
		}
		DBG("%d:resource %d: 0x%08x-0x%08x(%d)\n",
			pdev->id,
			i, res->start, res->end, resource_size(res));
		priv->iobase[i] = ioremap(res->start, resource_size(res));
		if (!priv->iobase[i]) {
			dev_err(&pdev->dev, "ioremap failed(resource %d)\n", i);
			err = -ENXIO;
			goto __err1;
		}
		priv->iomem[i] = res->start;
	}

	/* request irq */
	for (i = 0; i < IRQ_MAX; i++) {
		res = platform_get_resource(pdev, IORESOURCE_IRQ, i);
		if (!res) {
			dev_err(&pdev->dev, "cannot find register irq %d\n", i);
			err = -EINVAL;
			goto __err1;
		}
		DBG("%d:irq %d: %d\n", pdev->id, i, res->start);
		if ((i == I2SO_IRQ_ERR) || (i == I2SI_IRQ_ERR)) {
			/* error interrupt */
			err = request_irq(res->start, al_i2s_irq_err, 0, "I2S", priv);
			if (err < 0) {
				dev_err(&pdev->dev, "request_irq failed(irq=%d)\n",
					res->start);
				goto __err1;
			}
			priv->ioirq[i] = res->start;
#ifdef USE_I2S_INTERRUPT
		} else {
			/* transfer interrupt */
			err = request_irq(res->start, al_i2s_irq_int, 0, "I2S", priv);
			if (err < 0) {
				dev_err(&pdev->dev, "request_irq failed(irq=%d)\n",
					res->start);
				goto __err1;
			}
			priv->ioirq[i] = res->start;
#endif
		}
	}

	soc_dai_dev = &priv->soc_dai_pdev;
	soc_dai_dev->id = pdev->id;
	soc_dai_dev->name = "applite-i2s";

	err = snd_soc_register_dai(&pdev->dev, &applite_i2s_dai);
	if (err) {
		dev_err(&pdev->dev, "register DAIs failed\n");
		goto __err1;
	}

	err = al_i2s_clk_setup(&(pdev->dev));
	if (err) {
		dev_err(&pdev->dev, "clk_get failed\n");
		goto __err2;
	}
	pm_runtime_enable(&(pdev->dev));

	return 0;

__err2:
	snd_soc_unregister_dai(&pdev->dev);
__err1:
	for (i = 0; i < IOBASE_MAX; i++) {
		if (priv->iobase[i])
			iounmap(priv->iobase[i]);
	}
	for (i = 0; i < IRQ_MAX; i++) {
		if (priv->ioirq[i])
			free_irq(priv->ioirq[i], priv);
	}
	platform_set_drvdata(pdev, NULL);
	vfree(priv);

	return err;
}

static int __devexit al_i2s_remove(struct platform_device *pdev)
{
	int i;
	struct al_i2s *priv = platform_get_drvdata(pdev);
	struct platform_device *soc_dai_dev;

	if (priv)
		DBG("I2S%d:enter\n", priv->i2s_param[SNDRV_PCM_STREAM_PLAYBACK].ch ? 1 : 0);
	else
		DBG("enter\n");

	pm_runtime_disable(&(pdev->dev));
	al_i2s_clk_allput();

	snd_soc_unregister_dai(&pdev->dev);
	soc_dai_dev = &priv->soc_dai_pdev;
	if (priv) {
		for (i = 0; i < IOBASE_MAX; i++) {
			if (priv->iobase[i])
				iounmap(priv->iobase[i]);
		}
		for (i = 0; i < IRQ_MAX; i++) {
			if (priv->ioirq[i])
				free_irq(priv->ioirq[i], priv);
		}
		platform_set_drvdata(pdev, NULL);
		vfree(priv);
	}

	return 0;
}

static int al_i2s_suspend(struct device *dev)
{
	DBG("enter\n");
	DBG("usecount:%d\n", i2s_usecount);
	if (i2s_usecount > 0)
		return -EBUSY;

	return 0;
}

static int al_i2s_resume(struct device *dev)
{
	DBG("enter\n");
	return 0;
}

static int al_i2s_runtime_suspend(struct device *dev)
{
	DBG("enter\n");
	al_i2s_hw_reset(1); /* reset on */
	return 0;
}

static int al_i2s_runtime_resume(struct device *dev)
{
	DBG("enter(%p)\n", dev);
	al_i2s_hw_reset(0); /* reset off */
	return 0;
}

static const struct dev_pm_ops al_i2s_pm_ops = {
	.suspend = al_i2s_suspend,
	.resume = al_i2s_resume,
	.runtime_suspend = al_i2s_runtime_suspend,
	.runtime_resume = al_i2s_runtime_resume,
};

static struct platform_driver al_i2s_driver = {
	.probe = al_i2s_probe,
	.remove = __devexit_p(al_i2s_remove),

	.driver = {
		.name = "applite-i2s",
		.owner = THIS_MODULE,
		.pm = &al_i2s_pm_ops,
	},
};

module_platform_driver(al_i2s_driver);

MODULE_AUTHOR("TOSHIBA Corporation");
MODULE_DESCRIPTION("ApP Lite ASoC I2S driver");
MODULE_LICENSE("GPL v2");
