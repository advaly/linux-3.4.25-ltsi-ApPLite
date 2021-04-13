/*
 * sound/soc/applite/applite-pcm.c
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

#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/dma-mapping.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/dmaengine.h>
#include <linux/fsl/mxs-dma.h>
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
#include "applite-pcm.h"
#include "applite-i2s.h"

#define xprintk(level, fmt, args...) \
	printk(level "snd-applite-pcm: " fmt , ## args)
#ifdef APPLITE_PCM_DEBUG
	#define dprintk(level, fmt, args...) \
		printk(level "snd-applite-pcm:%s(): " fmt , __func__ , ## args)
#else
	#define dprintk(level, fmt, args...)
#endif

#define ERROR(fmt, args...) \
	xprintk(KERN_ERR , fmt , ## args)
#define INFO(fmt, args...) \
	xprintk(KERN_INFO , fmt , ## args)
#define DBG(fmt, args...) \
	dprintk(KERN_ERR , fmt , ## args)

static int al_pcm_period_byte = USE_PERIODS_MAX;

static struct snd_pcm_hardware snd_al_hardware = {
	.info			= (SNDRV_PCM_INFO_INTERLEAVED |
				   SNDRV_PCM_INFO_PAUSE |
				   SNDRV_PCM_INFO_RESUME |
				   SNDRV_PCM_INFO_MMAP_VALID |
				   SNDRV_PCM_INFO_MMAP),
	.formats		= USE_FORMATS,
	.rates			= USE_RATES,
	.rate_min		= USE_RATE_MIN,
	.rate_max		= USE_RATE_MAX,
	.channels_min		= USE_CHANNELS_MIN,
	.channels_max		= USE_CHANNELS_MAX,
	.period_bytes_min	= USE_PERIOD_BYTES_MIN,
	.period_bytes_max	= USE_PERIOD_BYTES_MAX,
	.periods_min		= USE_PERIODS_MIN,
	.periods_max		= USE_PERIODS_MAX,
	.buffer_bytes_max	= MAX_BUFFER_SIZE,
	.fifo_size		= USE_FIFO_SIZE,

};

static int snd_al_get_peri[] = {
	DMA_PERI_CH4,	/* I2SO0 */
	DMA_PERI_CH5,	/* I2SI0 */
	DMA_PERI_CH6,	/* I2SO1 */
	DMA_PERI_CH7	/* I2SI1 */
};

void snd_al_pcm_period_byte(int period_byte)
{
#ifndef USE_I2S_INTERRUPT
	DBG("enter()\n");

	if ((period_byte > 0) && (9 > period_byte))
		al_pcm_period_byte = period_byte;

	/*snd_al_hardware.period_bytes_min = al_pcm_period_byte * 1024;*/
	snd_al_hardware.period_bytes_max = al_pcm_period_byte * 1024;
	/*snd_al_hardware.buffer_bytes_max = (al_pcm_period_byte * 2) * 1024;*/
#endif
}
EXPORT_SYMBOL_GPL(snd_al_pcm_period_byte);

static void snd_al_pcm_dma_callback(void *dma_async_param, int bytes)
{
	struct snd_pcm_substream *substream = dma_async_param;
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct al_pcm_runtime *al_rtd = runtime->private_data;

#if 0
	ERROR("%s:jiffies=%lu\n", __func__, jiffies);
#endif

	al_rtd->offset += bytes;
	al_rtd->offset %=
		al_rtd->period_bytes * al_rtd->periods;

	snd_pcm_period_elapsed((struct snd_pcm_substream *)dma_async_param);
}

static int snd_al_pcm_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *hw_params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct al_pcm_runtime *al_rtd = runtime->private_data;
	struct al_i2s *i2s = snd_soc_dai_get_drvdata(rtd->cpu_dai);
	struct DMA_parameters dma_param;

	DBG("enter(%s)\n", rtd->dai_link->stream_name);

	snd_pcm_set_runtime_buffer(substream, &substream->dma_buffer);

	al_rtd->format = params_format(hw_params);
	al_rtd->rate = params_rate(hw_params);
	al_rtd->channels = params_channels(hw_params);
	al_rtd->size = params_buffer_bytes(hw_params);
	al_rtd->periods = params_periods(hw_params);
	al_rtd->period_bytes = params_period_bytes(hw_params);
	al_rtd->offset = 0;
	al_rtd->period_time = HZ / (params_rate(hw_params) /
		params_period_size(hw_params));
	al_rtd->buf = (unsigned int *)substream->dma_buffer.area;
	al_rtd->dma_addr = runtime->dma_addr;
	al_rtd->pcm_status = AL_PCM_STOP;

	DBG("buffer_bytes=%ld, periods=%u, period_bytes=%u\n",
		al_rtd->size, al_rtd->periods, al_rtd->period_bytes);

	/* setup DMA */
	dma_param.peripheral = snd_al_get_peri[i2s->i2s_param[substream->stream].ch];
	dma_param.trans_size  = al_rtd->size;
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		dma_param.direction = PL330_M2P_DMA;
		dma_param.src_addr = al_rtd->dma_addr;
		dma_param.dst_addr =
			(unsigned long)snd_soc_dai_get_dma_data(rtd->cpu_dai, substream);
		DBG("SNDRV_PCM_STREAM_PLAYBACK: src=%x, dst=%x, peri=%d\n", (u32)dma_param.src_addr, (u32)dma_param.dst_addr, (int)dma_param.peripheral);
		dma_param.ccr.src_mode = 1;             /* [0] SAI */
		dma_param.ccr.src_burst_size = 2;       /* [3:1] SS32 */
		dma_param.ccr.src_burst_len = 15;       /* [7:4] SB16 */
		dma_param.ccr.src_protect = 0;
		dma_param.ccr.src_cache = 0;
		dma_param.ccr.dst_mode = 0;             /* [14] DAF */
		dma_param.ccr.dst_burst_size = 2;       /* [17:15] DS32 */
		dma_param.ccr.dst_burst_len = 15;       /* [21:18] DB16 */
		dma_param.ccr.dst_protect = 0;
		dma_param.ccr.dst_cache = 0;
		dma_param.ccr.swap_size = 0;
	} else {
		dma_param.direction = PL330_P2M_DMA;
		dma_param.src_addr =
			(unsigned long)snd_soc_dai_get_dma_data(rtd->cpu_dai, substream);
		dma_param.dst_addr = al_rtd->dma_addr;
		DBG("SNDRV_PCM_STREAM_CAPTURE: src=%x, dst=%x, peri=%d\n", (u32)dma_param.src_addr, (u32)dma_param.dst_addr, (int)dma_param.peripheral);
		dma_param.ccr.src_mode = 0;             /* [0] SAF */
		dma_param.ccr.src_burst_size = 2;       /* [3:1] SS32 */
		dma_param.ccr.src_burst_len = 15;       /* [7:4] SB16 */
		dma_param.ccr.src_protect = 0;
		dma_param.ccr.src_cache = 0;
		dma_param.ccr.dst_mode = 1;             /* [14] DAI */
		dma_param.ccr.dst_burst_size = 2;       /* [17:15] DS32 */
		dma_param.ccr.dst_burst_len = 15;       /* [21:18] DB16 */
		dma_param.ccr.dst_protect = 0;
		dma_param.ccr.dst_cache = 0;
		dma_param.ccr.swap_size = 0;
	}
	dma_param.irq_enable = 1;
	dma_param.forever = 1;                  /* DMA Infinite Loop - 0(off) */
	dma_param.bw_jump = 0;
	dma_param.last_req = 1;

	dma_param.period_bytes = al_rtd->period_bytes;
	dma_param.periods = al_rtd->periods;
	dma_param.callback = snd_al_pcm_dma_callback;
	dma_param.callback_param = substream;
	setup_DMA_channel(&al_rtd->dma_ctrl, dma_param);

	return 0;
}

static int snd_al_pcm_hw_free(struct snd_pcm_substream *substream)
{
#ifdef APPLITE_PCM_DEBUG
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
#endif

	DBG("enter(%s)\n", rtd->dai_link->stream_name);

	snd_pcm_set_runtime_buffer(substream, NULL);

	return 0;
}

static int snd_al_open(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct al_pcm_runtime *al_rtd = NULL;
	int err;

	DBG("enter(%s)\n", rtd->dai_link->stream_name);

	snd_soc_set_runtime_hwparams(substream, &snd_al_hardware);
	err = snd_pcm_hw_constraint_step(runtime, 0,
			SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 128);
	if (err < 0)
		return err;
	err = snd_pcm_hw_constraint_step(runtime, 0,
			SNDRV_PCM_HW_PARAM_BUFFER_BYTES, 128);
	if (err < 0)
		return err;
	err = snd_pcm_hw_constraint_integer(runtime,
				SNDRV_PCM_HW_PARAM_PERIODS);
	if (err < 0)
		return err;

	err = -ENOMEM;
	al_rtd = kzalloc(sizeof(*al_rtd), GFP_KERNEL);
	if (!al_rtd) {
		pr_err("%s : memory alloc failed [len=%d]\n",
			AL_PCM_AUDIO, sizeof(*rtd));
		return err;
	}
	memset(al_rtd, 0x00, sizeof(*al_rtd));

	al_rtd->pcm_status = AL_PCM_OPEN;
	al_rtd->substream = substream;

	/* alloc DMA channel */
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		err = alloc_DMA_channel(&al_rtd->dma_ctrl, DMA_CH_AUTO);
	else
		err = alloc_DMA_channel(&al_rtd->dma_ctrl, DMA_CH_AUTO);
	if (err < 0) {
		kfree(al_rtd);
		return err;
	}

	runtime->private_data = al_rtd;

	return 0;
}

static int snd_al_close(struct snd_pcm_substream *substream)
{
#ifdef APPLITE_PCM_DEBUG
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
#endif
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct al_pcm_runtime *al_rtd = runtime->private_data;

	DBG("enter(%s)\n", rtd->dai_link->stream_name);

	free_DMA_channel(&al_rtd->dma_ctrl);

	kfree(al_rtd);

	runtime->private_data = NULL;

	return 0;
}

static int snd_al_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
#ifdef APPLITE_PCM_DEBUG
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
#endif
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct al_pcm_runtime *al_rtd = runtime->private_data;
	int err = 0;

	DBG("enter(%s)\n", rtd->dai_link->stream_name);

	if (al_rtd->pcm_status == AL_PCM_OPEN)
		return 0;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		al_rtd->offset = 0;
		if (al_rtd->pcm_status == AL_PCM_STOP)
			start_DMA_channel(&al_rtd->dma_ctrl, 0);
		al_rtd->pcm_status = AL_PCM_START;
		break;

	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		if (al_rtd->pcm_status == AL_PCM_START)
			stop_DMA_channel(&al_rtd->dma_ctrl);
		al_rtd->offset = 0;
		al_rtd->pcm_status = AL_PCM_STOP;
		break;

	default:
		err = -EINVAL;
		break;
	}

	return err;
}

static snd_pcm_uframes_t snd_al_pcm_pointer(struct snd_pcm_substream *substream)
{
#ifdef USE_I2S_INTERRUPT
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct al_i2s *i2s = snd_soc_dai_get_drvdata(rtd->cpu_dai);
#endif
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct al_pcm_runtime *al_rtd = runtime->private_data;
	snd_pcm_uframes_t position = 0;

#ifdef USE_I2S_INTERRUPT
	al_rtd->offset = i2s->i2s_param.offset;
#endif
	position = bytes_to_frames(substream->runtime, al_rtd->offset);

	return position;
}

static int snd_al_pcm_mmap(struct snd_pcm_substream *substream,
		struct vm_area_struct *vma)
{
	struct snd_pcm_runtime *runtime = substream->runtime;

	return dma_mmap_writecombine(substream->pcm->card->dev, vma,
					runtime->dma_area,
					runtime->dma_addr,
					runtime->dma_bytes);
}

static struct snd_pcm_ops al_pcm_ops = {
	.open		= snd_al_open,
	.close		= snd_al_close,
	.ioctl		= snd_pcm_lib_ioctl,
	.hw_params	= snd_al_pcm_hw_params,
	.hw_free	= snd_al_pcm_hw_free,
	.trigger	= snd_al_pcm_trigger,
	.pointer	= snd_al_pcm_pointer,
	.mmap		= snd_al_pcm_mmap,
};

static int al_pcm_preallocate_dma_buffer(struct snd_pcm *pcm, int stream)
{
	struct snd_pcm_substream *substream = pcm->streams[stream].substream;
	struct snd_dma_buffer *buf = &substream->dma_buffer;
	size_t size = snd_al_hardware.buffer_bytes_max;

	DBG("enter(size=%d)\n", size);

	buf->dev.type = SNDRV_DMA_TYPE_DEV;
	buf->dev.dev = pcm->card->dev;
	buf->private_data = NULL;
	buf->area = dma_alloc_writecombine(pcm->card->dev, size,
					   &buf->addr, GFP_KERNEL);
	if (!buf->area)
		return -ENOMEM;
	buf->bytes = size;

	return 0;
}

static u64 al_pcm_dmamask = DMA_BIT_MASK(32);
static int al_pcm_new(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_card *card = rtd->card->snd_card;
	struct snd_pcm *pcm = rtd->pcm;
	int ret = 0;

	DBG("enter(%s)\n", rtd->dai_link->stream_name);

	if (!card->dev->dma_mask)
		card->dev->dma_mask = &al_pcm_dmamask;
	if (!card->dev->coherent_dma_mask)
		card->dev->coherent_dma_mask = DMA_BIT_MASK(32);

	if (pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream) {
		ret = al_pcm_preallocate_dma_buffer(pcm,
			SNDRV_PCM_STREAM_PLAYBACK);
		if (ret)
			goto out;
	}

	if (pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream) {
		ret = al_pcm_preallocate_dma_buffer(pcm,
			SNDRV_PCM_STREAM_CAPTURE);
		if (ret)
			goto out;
	}

out:
	return ret;
}

static void al_pcm_free(struct snd_pcm *pcm)
{
	struct snd_pcm_substream *substream;
	struct snd_soc_pcm_runtime *rtd;
	struct snd_dma_buffer *buf;
	int stream;

	DBG("enter\n");

	for (stream = 0; stream < 2; stream++) {
		substream = pcm->streams[stream].substream;
		if (!substream)
			continue;

		buf = &substream->dma_buffer;
		if (!buf->area)
			continue;

		dma_free_writecombine(pcm->card->dev, buf->bytes,
				      buf->area, buf->addr);
		buf->area = NULL;

		rtd = substream->private_data;
		if (!rtd)
			continue;

	}
}

static struct snd_soc_platform_driver al_soc_platform = {
	.ops		= &al_pcm_ops,
	.pcm_new	= al_pcm_new,
	.pcm_free	= al_pcm_free,
};

static int __devinit al_soc_platform_probe(struct platform_device *pdev)
{
	int err;

	DBG("enter\n");

	err = start_DMA_controller();
	if (err)
		return err;

	return snd_soc_register_platform(&pdev->dev, &al_soc_platform);
}

static int __devexit al_soc_platform_remove(struct platform_device *pdev)
{
	DBG("enter\n");

	stop_DMA_controller();
	snd_soc_unregister_platform(&pdev->dev);

	return 0;
}


static struct platform_driver al_pcm_driver = {
	.driver = {
		.name = AL_PCM_AUDIO,
		.owner = THIS_MODULE,
	},
	.probe = al_soc_platform_probe,
	.remove = __devexit_p(al_soc_platform_remove),
};

module_platform_driver(al_pcm_driver);

MODULE_AUTHOR("TOSHIBA Corporation");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:applite-pcm-audio");
