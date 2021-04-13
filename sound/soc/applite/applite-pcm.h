/*
 * sound/soc/applite/applite-pcm.h
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

#ifndef _APPLITE_PCM_H
#define _APPLITE_PCM_H

#include "applite-tzxxx.h"

/*#define APPLITE_PCM_DEBUG	1*/
#undef APPLITE_PCM_DEBUG

/* defaults */
#if IS_ENABLED(CONFIG_ARCH_TZ3000)
#define MAX_PCM_DEVICES		4
#else
#define MAX_PCM_DEVICES		2
#endif
#ifdef USE_I2S_INTERRUPT
	#define MIN_PERIOD_SIZE		(128)	/* 128byte */
	#define USE_PERIOD_BYTES_MIN	MIN_PERIOD_SIZE
	#define USE_PERIOD_BYTES_MAX	MIN_PERIOD_SIZE
	#define USE_PERIODS_MIN		1
	#define USE_PERIODS_MAX		64
#else
	/*#define USE_PERIOD_BYTES_MIN	128*/
	#define USE_PERIOD_BYTES_MIN	1024
	#define USE_PERIOD_BYTES_MAX	(8*1024)
	#define USE_PERIODS_MIN		1
	#define USE_PERIODS_MAX		64
#endif
#define MAX_BUFFER_SIZE		(64*1024)

#define USE_FORMATS		(SNDRV_PCM_FMTBIT_S16_LE |\
				 SNDRV_PCM_FMTBIT_S32_LE)
#define USE_RATES		(SNDRV_PCM_RATE_KNOT |\
				 SNDRV_PCM_RATE_8000_192000)
#define USE_RATE_MIN		8000
#define USE_RATE_MAX		192000
#define USE_CHANNELS_MIN	1
#define USE_CHANNELS_MAX	2
#define USE_FIFO_SIZE		1

#define AL_PCM_AUDIO		"applite-pcm-audio"

enum al_pcm_status {
	AL_PCM_OPEN = 0,
	AL_PCM_STOP,
	AL_PCM_START
};

struct al_pcm_runtime {
	enum al_pcm_status pcm_status;
	struct snd_pcm_substream *substream;

	snd_pcm_format_t format;
	unsigned int rate;
	int channels;
	int period_bytes;
	int periods;
	unsigned long offset;
	unsigned long size;
	void *buf;
	int period_time;
	unsigned long dma_addr;

	struct DMA_controller dma_ctrl;
};

extern void snd_al_pcm_period_byte(int period_byte);

#endif /* _APPLITE_PCM_H */
