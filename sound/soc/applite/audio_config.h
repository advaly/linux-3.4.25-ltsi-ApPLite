/*
 * sound/soc/applite/audio_config.h
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

#if !defined(__AUDIO_CONFIG_H__)
#define __AUDIO_CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif        /* __cplusplus */

#define AUDIO_CONFIG_RATE_MAX	4

enum config_wave_num {
	CONFIG_WAVE_STEREO = 0,
	CONFIG_WAVE_MONO,
	CONFIG_WAVE_MAX
};
enum config_data_format_num {
	CONFIG_DATA_FORMAT_16BIT = 0,
	CONFIG_DATA_FORMAT_32BIT,
	CONFIG_DATA_FORMAT_MAX
};

struct audio_config_val_t {
	u32 sampling_rate;
	u32 val;
};

struct audio_config_rate_t {
	char config_name[128];
	struct audio_config_val_t audio_config_val[AUDIO_CONFIG_RATE_MAX];
};

/* Audio Clock:24.5760MHz,Format:16bit,Stereo */
static struct audio_config_rate_t g_audio_245760MHz_16bit_Stereo = {
	.config_name = "Audio Clock:24.5760MHz,Format:16bit,Stereo",
	.audio_config_val[0] = {
		.sampling_rate = 96000,	/* 96KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_128CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT),
	},
	.audio_config_val[1] = {
		.sampling_rate = 64000,	/* 64KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_192CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT),
	},
	.audio_config_val[2] = {
		.sampling_rate = 48000,	/* 48KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_256CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT),
	},
	.audio_config_val[3] = {
		.sampling_rate = 24000,	/* 24KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_512CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT)
	}
};
/* Audio Clock:24.5760MHz,Format:16bit,Mono */
static struct audio_config_rate_t g_audio_245760MHz_16bit_Mono = {
	.config_name = "Audio Clock:24.5760MHz,Format:16bit,Mono",
	.audio_config_val[0] = {
		.sampling_rate = 192000,	/* 192KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_128CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT),
	},
	.audio_config_val[1] = {
		.sampling_rate = 128000,	/* 128KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_192CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT),
	},
	.audio_config_val[2] = {
		.sampling_rate = 96000,	/* 96KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_256CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT),
	},
	.audio_config_val[3] = {
		.sampling_rate = 48000,	/* 48KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_512CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT)
	}
};
/* Audio Clock:24.5760MHz,Format:32bit,Stereo */
static struct audio_config_rate_t g_audio_245760MHz_32bit_Stereo = {
	.config_name = "Audio Clock:24.5760MHz,Format:32bit,Stereo",
	.audio_config_val[0] = {
		.sampling_rate = 96000,	/* 96KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_128CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT),
	},
	.audio_config_val[1] = {
		.sampling_rate = 64000,	/* 64KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_192CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT),
	},
	.audio_config_val[2] = {
		.sampling_rate = 48000,	/* 48KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_256CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT),
	},
	.audio_config_val[3] = {
		.sampling_rate = 24000,	/* 24KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_512CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT)
	}
};
/* Audio Clock:24.5760MHz,Format:32bit,Mono */
static struct audio_config_rate_t g_audio_245760MHz_32bit_Mono = {
	.config_name = "Audio Clock:24.5760MHz,Format:32bit,Mono",
	.audio_config_val[0] = {
		.sampling_rate = 192000,	/* 192KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_128CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT),
	},
	.audio_config_val[1] = {
		.sampling_rate = 128000,	/* 128KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_192CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT),
	},
	.audio_config_val[2] = {
		.sampling_rate = 96000,	/* 96KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_256CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT),
	},
	.audio_config_val[3] = {
		.sampling_rate = 48000,	/* 48KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_512CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT)
	}
};

/**/
/* Audio Clock:18.4320MHz,Format:16bit,Stereo */
static struct audio_config_rate_t g_audio_184320MHz_16bit_Stereo = {
	.config_name = "Audio Clock:18.4320MHz,Format:16bit,Stereo",
	.audio_config_val[0] = {
		.sampling_rate = 72000,	/* 72KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_128CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT),
	},
	.audio_config_val[1] = {
		.sampling_rate = 48000,	/* 48KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_192CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT),
	},
	.audio_config_val[2] = {
		.sampling_rate = 36000,	/* 36KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_256CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT),
	},
	.audio_config_val[3] = {
		.sampling_rate = 18000,	/* 18KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_512CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT)
	}
};
/* Audio Clock:18.4320MHz,Format:16bit,Mono */
static struct audio_config_rate_t g_audio_184320MHz_16bit_Mono = {
	.config_name = "Audio Clock:18.4320MHz,Format:16bit,Mono",
	.audio_config_val[0] = {
		.sampling_rate = 144000,	/* 144KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_128CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT),
	},
	.audio_config_val[1] = {
		.sampling_rate = 96000,	/* 96KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_192CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT),
	},
	.audio_config_val[2] = {
		.sampling_rate = 72000,	/* 72KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_256CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT),
	},
	.audio_config_val[3] = {
		.sampling_rate = 36000,	/* 36KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_512CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT)
	}
};
/* Audio Clock:18.4320MHz,Format:32bit,Stereo */
static struct audio_config_rate_t g_audio_184320MHz_32bit_Stereo = {
	.config_name = "Audio Clock:18.4320MHz,Format:32bit,Stereo",
	.audio_config_val[0] = {
		.sampling_rate = 72000,	/* 72KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_128CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT),
	},
	.audio_config_val[1] = {
		.sampling_rate = 48000,	/* 48KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_192CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT),
	},
	.audio_config_val[2] = {
		.sampling_rate = 36000,	/* 36KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_256CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT),
	},
	.audio_config_val[3] = {
		.sampling_rate = 18000,	/* 18KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_512CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT)
	}
};
/* Audio Clock:18.4320MHz,Format:32bit,Mono */
static struct audio_config_rate_t g_audio_184320MHz_32bit_Mono = {
	.config_name = "Audio Clock:18.4320MHz,Format:32bit,Mono",
	.audio_config_val[0] = {
		.sampling_rate = 144000,	/* 144KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_128CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT),
	},
	.audio_config_val[1] = {
		.sampling_rate = 96000,	/* 96KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_192CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT),
	},
	.audio_config_val[2] = {
		.sampling_rate = 72000,	/* 72KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_256CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT),
	},
	.audio_config_val[3] = {
		.sampling_rate = 36000,	/* 36KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_512CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT)
	}
};

/**/
/* Audio Clock:12.2880MHz,Format:16bit,Stereo */
static struct audio_config_rate_t g_audio_122880MHz_16bit_Stereo = {
	.config_name = "Audio Clock:12.2880MHz,Format:16bit,Stereo",
	.audio_config_val[0] = {
		.sampling_rate = 48000,	/* 48KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_128CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT),
	},
	.audio_config_val[1] = {
		.sampling_rate = 32000,	/* 32KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_192CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT),
	},
	.audio_config_val[2] = {
		.sampling_rate = 24000,	/* 24KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_256CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT),
	},
	.audio_config_val[3] = {
		.sampling_rate = 12000,	/* 12KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_512CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT)
	}
};
/* Audio Clock:12.2880MHz,Format:16bit,Mono */
static struct audio_config_rate_t g_audio_122880MHz_16bit_Mono = {
	.config_name = "Audio Clock:12.2880MHz,Format:16bit,Mono",
	.audio_config_val[0] = {
		.sampling_rate = 96000,	/* 96KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_128CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT),
	},
	.audio_config_val[1] = {
		.sampling_rate = 64000,	/* 64KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_192CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT),
	},
	.audio_config_val[2] = {
		.sampling_rate = 48000,	/* 48KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_256CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT),
	},
	.audio_config_val[3] = {
		.sampling_rate = 24000,	/* 24KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_512CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT)
	}
};
/* Audio Clock:12.2880MHz,Format:32bit,Stereo */
static struct audio_config_rate_t g_audio_122880MHz_32bit_Stereo = {
	.config_name = "Audio Clock:12.2880MHz,Format:32bit,Stereo",
	.audio_config_val[0] = {
		.sampling_rate = 48000,	/* 48KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_128CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT),
	},
	.audio_config_val[1] = {
		.sampling_rate = 32000,	/* 32KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_192CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT),
	},
	.audio_config_val[2] = {
		.sampling_rate = 24000,	/* 24KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_256CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT),
	},
	.audio_config_val[3] = {
		.sampling_rate = 12000,	/* 12KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_512CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT)
	}
};
/* Audio Clock:12.2880MHz,Format:32bit,Mono */
static struct audio_config_rate_t g_audio_122880MHz_32bit_Mono = {
	.config_name = "Audio Clock:12.2880MHz,Format:32bit,Mono",
	.audio_config_val[0] = {
		.sampling_rate = 96000,	/* 96KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_128CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT),
	},
	.audio_config_val[1] = {
		.sampling_rate = 64000,	/* 64KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_192CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT),
	},
	.audio_config_val[2] = {
		.sampling_rate = 48000,	/* 48KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_256CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT),
	},
	.audio_config_val[3] = {
		.sampling_rate = 24000,	/* 24KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_512CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT)
	}
};

/**/
/* Audio Clock:11.2896MHz,Format:16bit,Stereo */
static struct audio_config_rate_t g_audio_112896MHz_16bit_Stereo = {
	.config_name = "Audio Clock:11.2896MHz,Format:16bit,Stereo",
	.audio_config_val[0] = {
		.sampling_rate = 44100,	/* 44.1KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_128CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT),
	},
	.audio_config_val[1] = {
		.sampling_rate = 29400,	/* 29.4KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_192CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT),
	},
	.audio_config_val[2] = {
		.sampling_rate = 22050,	/* 22.05KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_256CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT),
	},
	.audio_config_val[3] = {
		.sampling_rate = 11025,	/* 11.025KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_512CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT)
	}
};
/* Audio Clock:11.2896MHz,Format:16bit,Mono */
static struct audio_config_rate_t g_audio_112896MHz_16bit_Mono = {
	.config_name = "Audio Clock:11.2896MHz,Format:16bit,Mono",
	.audio_config_val[0] = {
		.sampling_rate = 88200,	/* 88.2KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_128CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT),
	},
	.audio_config_val[1] = {
		.sampling_rate = 58800,	/* 58.8KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_192CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT),
	},
	.audio_config_val[2] = {
		.sampling_rate = 44100,	/* 44.1KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_256CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT),
	},
	.audio_config_val[3] = {
		.sampling_rate = 22050,	/* 22.05KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_16CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_512CYCLE|\
			I2S_AUDIOSET_WORDLEN_16BIT)
	}
};
/* Audio Clock:11.2896MHz,Format:32bit,Stereo */
static struct audio_config_rate_t g_audio_112896MHz_32bit_Stereo = {
	.config_name = "Audio Clock:11.2896MHz,Format:32bit,Stereo",
	.audio_config_val[0] = {
		.sampling_rate = 44100,	/* 44.1KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_128CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT),
	},
	.audio_config_val[1] = {
		.sampling_rate = 29400,	/* 29.4KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_192CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT),
	},
	.audio_config_val[2] = {
		.sampling_rate = 22050,	/* 22.05KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_256CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT),
	},
	.audio_config_val[3] = {
		.sampling_rate = 11025,	/* 11.025KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_512CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT)
	}
};
/* Audio Clock:11.2896MHz,Format:32bit,Mono */
static struct audio_config_rate_t g_audio_112896MHz_32bit_Mono = {
	.config_name = "Audio Clock:11.2896MHz,Format:32bit,Mono",
	.audio_config_val[0] = {
		.sampling_rate = 88200,	/* 88.2KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_128CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT),
	},
	.audio_config_val[1] = {
		.sampling_rate = 58800,	/* 58.8KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_192CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT),
	},
	.audio_config_val[2] = {
		.sampling_rate = 44100,	/* 44.1KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_256CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT),
	},
	.audio_config_val[3] = {
		.sampling_rate = 22050,	/* 22.05KHz */
		.val = (I2S_AUDIOSET_SCLKTOWS_32CYCLE|\
			I2S_AUDIOSET_EDGE_RISE|\
			I2S_AUDIOSET_MTOWS_512CYCLE|\
			I2S_AUDIOSET_WORDLEN_32BIT)
	}
};

struct audio_config_t {
	struct audio_config_rate_t *audio_config_rate\
		[CONFIG_DATA_FORMAT_MAX][CONFIG_WAVE_MAX];
};
/* Audio Clock:24.5760MHz */
static struct audio_config_t g_audio_config_245760MHz = {
	.audio_config_rate[CONFIG_DATA_FORMAT_16BIT]\
			[CONFIG_WAVE_STEREO] = \
		&g_audio_245760MHz_16bit_Stereo,
	.audio_config_rate[CONFIG_DATA_FORMAT_16BIT]\
			[CONFIG_WAVE_MONO] = \
		&g_audio_245760MHz_16bit_Mono,
	.audio_config_rate[CONFIG_DATA_FORMAT_32BIT]\
			[CONFIG_WAVE_STEREO] = \
		&g_audio_245760MHz_32bit_Stereo,
	.audio_config_rate[CONFIG_DATA_FORMAT_32BIT]\
			[CONFIG_WAVE_MONO] = \
		&g_audio_245760MHz_32bit_Mono
};
/* Audio Clock:18.4320MHz */
static struct audio_config_t g_audio_config_184320MHz = {
	.audio_config_rate[CONFIG_DATA_FORMAT_16BIT]\
			[CONFIG_WAVE_STEREO] = \
		&g_audio_184320MHz_16bit_Stereo,
	.audio_config_rate[CONFIG_DATA_FORMAT_16BIT]\
			[CONFIG_WAVE_MONO] = \
		&g_audio_184320MHz_16bit_Mono,
	.audio_config_rate[CONFIG_DATA_FORMAT_32BIT]\
			[CONFIG_WAVE_STEREO] = \
		&g_audio_184320MHz_32bit_Stereo,
	.audio_config_rate[CONFIG_DATA_FORMAT_32BIT]\
			[CONFIG_WAVE_MONO] = \
		&g_audio_184320MHz_32bit_Mono
};
/* Audio Clock:12.2880MHz */
static struct audio_config_t g_audio_config_122880MHz = {
	.audio_config_rate[CONFIG_DATA_FORMAT_16BIT]\
			[CONFIG_WAVE_STEREO] = \
		&g_audio_122880MHz_16bit_Stereo,
	.audio_config_rate[CONFIG_DATA_FORMAT_16BIT]\
			[CONFIG_WAVE_MONO] = \
		&g_audio_122880MHz_16bit_Mono,
	.audio_config_rate[CONFIG_DATA_FORMAT_32BIT]\
			[CONFIG_WAVE_STEREO] = \
		&g_audio_122880MHz_32bit_Stereo,
	.audio_config_rate[CONFIG_DATA_FORMAT_32BIT]\
			[CONFIG_WAVE_MONO] = \
		&g_audio_122880MHz_32bit_Mono
};
/* Audio Clock:11.2896MHz */
static struct audio_config_t g_audio_config_112896MHz = {
	.audio_config_rate[CONFIG_DATA_FORMAT_16BIT]\
			[CONFIG_WAVE_STEREO] = \
		&g_audio_112896MHz_16bit_Stereo,
	.audio_config_rate[CONFIG_DATA_FORMAT_16BIT]\
			[CONFIG_WAVE_MONO] = \
		&g_audio_112896MHz_16bit_Mono,
	.audio_config_rate[CONFIG_DATA_FORMAT_32BIT]\
			[CONFIG_WAVE_STEREO] = \
		&g_audio_112896MHz_32bit_Stereo,
	.audio_config_rate[CONFIG_DATA_FORMAT_32BIT]\
			[CONFIG_WAVE_MONO] = \
		&g_audio_112896MHz_32bit_Mono
};


static struct audio_config_t *g_audio_config[AUDIO_CLOCK_MAX] = {
	/* Audio Clock:24.5760MHz */
	&g_audio_config_245760MHz,
	/* Audio Clock:18.4320MHz */
	&g_audio_config_184320MHz,
	/* Audio Clock:12.2880MHz */
	&g_audio_config_122880MHz,
	/* Audio Clock:11.2896MHz */
	&g_audio_config_112896MHz
};

static inline int get_audio_config_val(
			u32 audio_clock,
			u32 data_format,
			u32 audio_wave,
			u32 audio_rate,
			u32 *rtnval)
{
	struct audio_config_t *audio_config;
	struct audio_config_rate_t *audio_config_rate;
	int i;

	DBG("Audio Config:Audio Clock=%d\n", audio_clock);
	DBG("Audio Config:Data Format=%d\n", data_format);
	DBG("Audio Config:Wave=%d\n", audio_wave);
	DBG("Audio Config:Rate=%d\n", audio_rate);


	if (audio_clock >= AUDIO_CLOCK_MAX)
		return -1;

	if (data_format >= CONFIG_DATA_FORMAT_MAX)
		return -1;

	if (audio_wave >= CONFIG_WAVE_MAX)
		return -1;


	audio_config = g_audio_config[audio_clock];
	audio_config_rate =
		audio_config->audio_config_rate[data_format][audio_wave];

	/*INFO("%s\n", audio_config_rate->config_name);*/
	DBG("%s\n", audio_config_rate->config_name);
	for (i = 0; i < AUDIO_CONFIG_RATE_MAX; i++) {
		if (audio_rate ==
		    audio_config_rate->audio_config_val[i].sampling_rate) {
			*rtnval = audio_config_rate->audio_config_val[i].val;
			return 0;
		}
	}

	return -EINVAL;
}

static inline int get_audio_config_default(
			u32 audio_clock,
			u32 data_format,
			u32 audio_wave,
			u32 audio_rate,
			u32 *rtnval)
{
	struct audio_config_t *audio_config;
	struct audio_config_rate_t *audio_config_rate;
	int i, j;

	DBG("Audio Config:Data Format=%d\n", data_format);
	DBG("Audio Config:Wave=%d\n", audio_wave);
	DBG("Audio Config:Rate=%d\n", audio_rate);


	if (data_format >= CONFIG_DATA_FORMAT_MAX)
		return -1;

	if (audio_wave >= CONFIG_WAVE_MAX)
		return -1;

	for (j = 0; j < AUDIO_CLOCK_MAX; j++) {
		audio_config = g_audio_config[j];
		audio_config_rate =
			audio_config->audio_config_rate[data_format][audio_wave];

		/*INFO("%s\n", audio_config_rate->config_name);*/
		for (i = 0; i < AUDIO_CONFIG_RATE_MAX; i++) {
			if (audio_rate ==
				audio_config_rate->audio_config_val[i].sampling_rate) {
				*rtnval = audio_config_rate->audio_config_val[i].val;
				return 0;
			}
		}
	}

	return -EINVAL;
}

#ifdef __cplusplus
}
#endif     /* __cplusplus */


#endif    /* __AUDIO_CONFIG_H__ */

