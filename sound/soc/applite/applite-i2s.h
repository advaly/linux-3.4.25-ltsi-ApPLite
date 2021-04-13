/*
 * sound/soc/applite/applite-i2s.h
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

#ifndef _APPLITE_I2S_H
#define _APPLITE_I2S_H

#if IS_ENABLED(CONFIG_ARCH_TZ3000)
#include "mach/regs/cpu_memmap_def.h"
#include "mach/regs/i2sc_offs_def.h"
#include "mach/regs/i2sc_reg_def.h"
#include "mach/regs/i2so_offs_def.h"
#include "mach/regs/i2so_reg_def.h"
#include "mach/regs/i2si_offs_def.h"
#include "mach/regs/i2si_reg_def.h"
#include "mach/regs/pmu_offs_def.h"
#include "mach/regs/pmu_reg_def.h"
#include "mach/regs/gconf_offs_def.h"
#include "mach/regs/gconf_reg_def.h"
#else
#include "mach/regs/cpu_memmap_def.h"
#include "mach/regs/i2sc_offs_def.h"
#include "mach/regs/i2sc_reg_def.h"
#include "mach/regs/i2so_offs_def.h"
#include "mach/regs/i2so_reg_def.h"
#include "mach/regs/i2si_offs_def.h"
#include "mach/regs/i2si_reg_def.h"
#include "mach/regs/pmu_offs_def.h"
#include "mach/regs/pmu_reg_def.h"
#include "mach/regs/gconf_offs_def.h"
#include "mach/regs/gconf_reg_def.h"
#endif

/*#define APPLITE_I2S_DEBUG	1*/
#undef APPLITE_I2S_DEBUG

/****************************************************************************/
/* I2S register                                                             */
/****************************************************************************/

#define I2S_I2SO1_OFS		(I2SO_I2SO1_START_OFFS-I2SO_I2SO0_START_OFFS)
#define I2S_I2SI1_OFS		(I2SI_I2SI1_START_OFFS-I2SI_I2SI0_START_OFFS)

#define I2S_START_OFS		(I2SC_START_OFFS)
  #define I2S_START_MCKSTART_SHIFT	(I2SC_START_MCKSTART_SHIFT)
  #define I2S_START_SPKSTART_SHIFT	(I2SC_START_START_SHIFT)
  #define I2S_START_MICSTART_SHIFT	(I2SC_START_START_SHIFT)
#define I2S_BUSY_OFS		(I2SC_BUSY_OFFS)
  #define I2S_BUSY_BUSY_SHIFT		(I2SC_BUSY_BUSY_SHIFT)
#define I2S_AUDIOSET_OFS	(I2SC_AUDIOSET_OFFS)
  #define I2S_AUDIOSET_WORDLEN_SHIFT	(I2SC_AUDIOSET_WORDLEN_SHIFT)
    /*#define I2S_AUDIOSET_WORDLEN_32BIT (0<<I2S_AUDIOSET_WORDLEN_SHIFT)*/
    #define I2S_AUDIOSET_WORDLEN_32BIT  (32<<I2S_AUDIOSET_WORDLEN_SHIFT)
    #define I2S_AUDIOSET_WORDLEN_16BIT	(16<<I2S_AUDIOSET_WORDLEN_SHIFT)
  #define I2S_AUDIOSET_SCLKTOWS_SHIFT	(I2SC_AUDIOSET_SCLKTOWS_SHIFT)
    #define I2S_AUDIOSET_SCLKTOWS_16CYCLE	(0<<I2S_AUDIOSET_SCLKTOWS_SHIFT)
    #define I2S_AUDIOSET_SCLKTOWS_32CYCLE	(1<<I2S_AUDIOSET_SCLKTOWS_SHIFT)
  #define I2S_AUDIOSET_EDGE_SHIFT	(I2SC_AUDIOSET_EDGE_SHIFT)
    #define I2S_AUDIOSET_EDGE_FALL		(0<<I2S_AUDIOSET_EDGE_SHIFT)
    #define I2S_AUDIOSET_EDGE_RISE		(1<<I2S_AUDIOSET_EDGE_SHIFT)
  #define I2S_AUDIOSET_MTOWS_SHIFT	(I2SC_AUDIOSET_MTOWS_SHIFT)
    #define I2S_AUDIOSET_MTOWS_128CYCLE	(0<<I2S_AUDIOSET_MTOWS_SHIFT)
    #define I2S_AUDIOSET_MTOWS_192CYCLE	(1<<I2S_AUDIOSET_MTOWS_SHIFT)
    #define I2S_AUDIOSET_MTOWS_256CYCLE	(2<<I2S_AUDIOSET_MTOWS_SHIFT)
    #define I2S_AUDIOSET_MTOWS_512CYCLE	(3<<I2S_AUDIOSET_MTOWS_SHIFT)
#define I2S_INTSTAT_OFS		(I2SC_INTSTAT_OFFS)
  #define I2S_INT_INT_SHIFT		(I2SC_INTSTAT_INT_SHIFT)
  #define I2S_INT_ORERR_SHIFT		(I2SC_INTSTAT_ORERR_SHIFT)
  #define I2S_INT_URERR_SHIFT		(I2SC_INTSTAT_URERR_SHIFT)
#define I2S_INTMASK_OFS		(I2SC_INTMASK_OFFS)
  #define I2S_INT_ALL_MASK		((1<<I2S_INT_INT_SHIFT)|\
					 (1<<I2S_INT_ORERR_SHIFT)|\
					 (1<<I2S_INT_URERR_SHIFT))
#define I2S_INTCLR_OFS		(I2SC_INTCLR_OFFS)
#define I2S_INTSET_OFS		(I2SC_INTSET_OFFS)
  #define I2S_INTSET_INTSET_SHIFT	(I2SC_INTSET_INTSET_SHIFT)
#define I2S_MUTE_OFS		(I2SC_MUTE_OFFS)
  #define I2S_MUTE_MUTE_SHIFT		(I2SC_MUTE_MUTEN_SHIFT)
#define I2S_EPTR_OFS		(I2SC_EPTR_OFFS)
#define I2S_MODESET_OFS		(I2SC_MODESET_OFFS)
  #define I2S_MODESET_WS_SHIFT		(I2SC_MODESET_WS_SHIFT)
    #define I2S_MODESET_WS_I2S_STEREO		(0<<I2S_MODESET_WS_SHIFT)
    #define I2S_MODESET_WS_LR_STEREO		(2<<I2S_MODESET_WS_SHIFT)
    #define I2S_MODESET_WS_LR_STEREO_REV	(3<<I2S_MODESET_WS_SHIFT)
    #define I2S_MODESET_WS_MONO			(4<<I2S_MODESET_WS_SHIFT)
    #define I2S_MODESET_WS_MONO_REV		(5<<I2S_MODESET_WS_SHIFT)
  #define I2S_MODESET_IESEL_SHIFT	(I2SC_MODESET_IESEL_SHIFT)
    #define I2S_MODESET_IESEL_MASTER		(0<<I2S_MODESET_IESEL_SHIFT)
    #define I2S_MODESET_IESEL_SLAVE		(1<<I2S_MODESET_IESEL_SHIFT)
#define I2S_LMEM00_OFS		(I2SO_I2SO0_LMEM_OFFS)

#define REG_I2S(p, y)	((u32)((unsigned long)(p))+I2S_##y)


/****************************************************************************/
/* PMU register                                                             */
/****************************************************************************/

/* PMU_SoftResetOn_periSS_2_OFFS */
#if IS_ENABLED(CONFIG_ARCH_TZ3000)
#define PMU_SOFTRESETON_I2SI0 \
	(1<<PMU_SOFTRESETON_PERISS_2_SRST_ASYNCWRSTDIV2_PERI_I2SI0_N_SHIFT)
#define PMU_SOFTRESETON_I2SI1 \
	(1<<PMU_SOFTRESETON_PERISS_2_SRST_ASYNCWRSTDIV2_PERI_I2SI1_N_SHIFT)
#define PMU_SOFTRESETON_I2SO0 \
	(1<<PMU_SOFTRESETON_PERISS_2_SRST_ASYNCWRSTDIV2_PERI_I2SO0_N_SHIFT)
#define PMU_SOFTRESETON_I2SO1 \
	(1<<PMU_SOFTRESETON_PERISS_2_SRST_ASYNCWRSTDIV2_PERI_I2SO1_N_SHIFT)
#define PMU_SOFTRESETON_I2SC0 \
	(1<<PMU_SOFTRESETON_PERISS_2_SRST_ASYNCWRSTDIV2_PERI_I2SC0_N_SHIFT)
#define PMU_SOFTRESETON_ALL	(PMU_SOFTRESETON_I2SI0|\
				 PMU_SOFTRESETON_I2SI1|\
				 PMU_SOFTRESETON_I2SO0|\
				 PMU_SOFTRESETON_I2SO1|\
				 PMU_SOFTRESETON_I2SC0)
#else
#define PMU_SOFTRESETON_I2SI0 \
	(1<<PMU_SOFTRESETON_PERISS_2_SRST_ASYNCWRSTDIV4_PERI_I2SI0_N_SHIFT)
#define PMU_SOFTRESETON_I2SO0 \
	(1<<PMU_SOFTRESETON_PERISS_2_SRST_ASYNCWRSTDIV4_PERI_I2SO0_N_SHIFT)
#define PMU_SOFTRESETON_I2SC0 \
	(1<<PMU_SOFTRESETON_PERISS_2_SRST_ASYNCWRSTDIV4_PERI_I2SC0_N_SHIFT)
#define PMU_SOFTRESETON_ALL	(PMU_SOFTRESETON_I2SI0|\
				 PMU_SOFTRESETON_I2SO0|\
				 PMU_SOFTRESETON_I2SC0)
#endif

/* PMU_ClockGatingOff_periSS_2_OFFS */
#if IS_ENABLED(CONFIG_ARCH_TZ3000)
#define PMU_CLOCKGATINGOFF_I2SI0 \
	(1<<PMU_CLOCKGATINGOFF_PERISS_2_CG_WCLKDIV2_PERI_I2SI0_SHIFT)
#define PMU_CLOCKGATINGOFF_I2SI1 \
	(1<<PMU_CLOCKGATINGOFF_PERISS_2_CG_WCLKDIV2_PERI_I2SI1_SHIFT)
#define PMU_CLOCKGATINGOFF_I2SO0 \
	(1<<PMU_CLOCKGATINGOFF_PERISS_2_CG_WCLKDIV2_PERI_I2SO0_SHIFT)
#define PMU_CLOCKGATINGOFF_I2SO1 \
	(1<<PMU_CLOCKGATINGOFF_PERISS_2_CG_WCLKDIV2_PERI_I2SO1_SHIFT)
#define PMU_CLOCKGATINGOFF_I2SC0 \
	(1<<PMU_CLOCKGATINGOFF_PERISS_2_CG_WCLKDIV2_PERI_I2SC0_SHIFT)
#define PMU_CLOCKGATINGOFF_AMCLK_I2S \
	(1<<PMU_CLOCKGATINGOFF_PERISS_2_CG_AMCLK_I2S_SHIFT)
#define PMU_CLOCKGATINGOFF_IO_AMCLKO \
	(1<<PMU_CLOCKGATINGOFF_PERISS_2_CG_IO_AMCLKO_O_SHIFT)
#define PMU_CLOCKGATINGOFF_ALL	(PMU_CLOCKGATINGOFF_I2SI0|\
				 PMU_CLOCKGATINGOFF_I2SI1|\
				 PMU_CLOCKGATINGOFF_I2SO0|\
				 PMU_CLOCKGATINGOFF_I2SO1|\
				 PMU_CLOCKGATINGOFF_I2SC0|\
				 PMU_CLOCKGATINGOFF_AMCLK_I2S|\
				 PMU_CLOCKGATINGOFF_IO_AMCLKO)
#else
#define PMU_CLOCKGATINGOFF_I2SI0 \
	(1<<PMU_CLOCKGATINGOFF_PERISS_2_CG_WCLKDIV4_PERI_I2SI0_SHIFT)
#define PMU_CLOCKGATINGOFF_I2SO0 \
	(1<<PMU_CLOCKGATINGOFF_PERISS_2_CG_WCLKDIV4_PERI_I2SO0_SHIFT)
#define PMU_CLOCKGATINGOFF_I2SC0 \
	(1<<PMU_CLOCKGATINGOFF_PERISS_2_CG_WCLKDIV4_PERI_I2SC0_SHIFT)
#define PMU_CLOCKGATINGOFF_AMCLK_I2S \
	(1<<PMU_CLOCKGATINGOFF_PERISS_2_CG_AMCLK_I2S_SHIFT)
#define PMU_CLOCKGATINGOFF_IO_AMCLKO \
	(1<<PMU_CLOCKGATINGOFF_PERISS_2_CG_IO_AMCLKO_O_SHIFT)
#define PMU_CLOCKGATINGOFF_ALL	(PMU_CLOCKGATINGOFF_I2SI0|\
				 PMU_CLOCKGATINGOFF_I2SO0|\
				 PMU_CLOCKGATINGOFF_I2SC0|\
				 PMU_CLOCKGATINGOFF_AMCLK_I2S|\
				 PMU_CLOCKGATINGOFF_IO_AMCLKO)
#endif

/* PMU_ClockGatingOn_periSS_2_OFFS */
#if IS_ENABLED(CONFIG_ARCH_TZ3000)
#define PMU_CLOCKGATINGON_I2SI0 \
	(1<<PMU_CLOCKGATINGON_PERISS_2_CG_WCLKDIV2_PERI_I2SI0_SHIFT)
#define PMU_CLOCKGATINGON_I2SI1 \
	(1<<PMU_CLOCKGATINGON_PERISS_2_CG_WCLKDIV2_PERI_I2SI1_SHIFT)
#define PMU_CLOCKGATINGON_I2SO0 \
	(1<<PMU_CLOCKGATINGON_PERISS_2_CG_WCLKDIV2_PERI_I2SO0_SHIFT)
#define PMU_CLOCKGATINGON_I2SO1 \
	(1<<PMU_CLOCKGATINGON_PERISS_2_CG_WCLKDIV2_PERI_I2SO1_SHIFT)
#define PMU_CLOCKGATINGON_I2SC0 \
	(1<<PMU_CLOCKGATINGON_PERISS_2_CG_WCLKDIV2_PERI_I2SC0_SHIFT)
#define PMU_CLOCKGATINGON_AMCLK_I2S \
	(1<<PMU_CLOCKGATINGON_PERISS_2_CG_AMCLK_I2S_SHIFT)
#define PMU_CLOCKGATINGON_IO_AMCLKO \
	(1<<PMU_CLOCKGATINGON_PERISS_2_CG_IO_AMCLKO_O_SHIFT)
#define PMU_CLOCKGATINGON_ALL	(PMU_CLOCKGATINGON_I2SI0|\
				 PMU_CLOCKGATINGON_I2SI1|\
				 PMU_CLOCKGATINGON_I2SO0|\
				 PMU_CLOCKGATINGON_I2SO1|\
				 PMU_CLOCKGATINGON_I2SC0|\
				 PMU_CLOCKGATINGON_AMCLK_I2S|\
				 PMU_CLOCKGATINGON_IO_AMCLKO)
#else
#define PMU_CLOCKGATINGON_I2SI0 \
	(1<<PMU_CLOCKGATINGON_PERISS_2_CG_WCLKDIV4_PERI_I2SI0_SHIFT)
#define PMU_CLOCKGATINGON_I2SO0 \
	(1<<PMU_CLOCKGATINGON_PERISS_2_CG_WCLKDIV4_PERI_I2SO0_SHIFT)
#define PMU_CLOCKGATINGON_I2SC0 \
	(1<<PMU_CLOCKGATINGON_PERISS_2_CG_WCLKDIV4_PERI_I2SC0_SHIFT)
#define PMU_CLOCKGATINGON_AMCLK_I2S \
	(1<<PMU_CLOCKGATINGON_PERISS_2_CG_AMCLK_I2S_SHIFT)
#define PMU_CLOCKGATINGON_IO_AMCLKO \
	(1<<PMU_CLOCKGATINGON_PERISS_2_CG_IO_AMCLKO_O_SHIFT)
#define PMU_CLOCKGATINGON_ALL	(PMU_CLOCKGATINGON_I2SI0|\
				 PMU_CLOCKGATINGON_I2SO0|\
				 PMU_CLOCKGATINGON_I2SC0|\
				 PMU_CLOCKGATINGON_AMCLK_I2S|\
				 PMU_CLOCKGATINGON_IO_AMCLKO)
#endif

/* PMU_SoftResetOff_periSS_2_OFFS */
#if IS_ENABLED(CONFIG_ARCH_TZ3000)
#define PMU_SOFTRESETOFF_I2SI0 \
	(1<<PMU_SOFTRESETOFF_PERISS_2_SRST_ASYNCWRSTDIV2_PERI_I2SI0_N_SHIFT)
#define PMU_SOFTRESETOFF_I2SI1 \
	(1<<PMU_SOFTRESETOFF_PERISS_2_SRST_ASYNCWRSTDIV2_PERI_I2SI1_N_SHIFT)
#define PMU_SOFTRESETOFF_I2SO0 \
	(1<<PMU_SOFTRESETOFF_PERISS_2_SRST_ASYNCWRSTDIV2_PERI_I2SO0_N_SHIFT)
#define PMU_SOFTRESETOFF_I2SO1 \
	(1<<PMU_SOFTRESETOFF_PERISS_2_SRST_ASYNCWRSTDIV2_PERI_I2SO1_N_SHIFT)
#define PMU_SOFTRESETOFF_I2SC0 \
	(1<<PMU_SOFTRESETOFF_PERISS_2_SRST_ASYNCWRSTDIV2_PERI_I2SC0_N_SHIFT)
#define PMU_SOFTRESETOFF_ALL	(PMU_SOFTRESETOFF_I2SI0|\
				 PMU_SOFTRESETOFF_I2SI1|\
				 PMU_SOFTRESETOFF_I2SO0|\
				 PMU_SOFTRESETOFF_I2SO1|\
				 PMU_SOFTRESETOFF_I2SC0)
#else
#define PMU_SOFTRESETOFF_I2SI0 \
	(1<<PMU_SOFTRESETOFF_PERISS_2_SRST_ASYNCWRSTDIV4_PERI_I2SI0_N_SHIFT)
#define PMU_SOFTRESETOFF_I2SO0 \
	(1<<PMU_SOFTRESETOFF_PERISS_2_SRST_ASYNCWRSTDIV4_PERI_I2SO0_N_SHIFT)
#define PMU_SOFTRESETOFF_I2SC0 \
	(1<<PMU_SOFTRESETOFF_PERISS_2_SRST_ASYNCWRSTDIV4_PERI_I2SC0_N_SHIFT)
#define PMU_SOFTRESETOFF_ALL	(PMU_SOFTRESETOFF_I2SI0|\
				 PMU_SOFTRESETOFF_I2SO0|\
				 PMU_SOFTRESETOFF_I2SC0)
#endif



/* PMU_AUDIO_CLOCK_0_OFFS */
/* 11.2896MHz */
#define PMU_AUDIO_CLOCK_0_11_2896MHZ ( \
	(3<<PMU_AUDIO_CLOCK_0_FREQUENCY_IO_AMCLKO_O_SHIFT) | \
	(3<<PMU_AUDIO_CLOCK_0_FREQUENCY_AMCLK_I2S_SHIFT))

/* 12.2880MHz */
#define PMU_AUDIO_CLOCK_0_12_2880MHZ ( \
	(2<<PMU_AUDIO_CLOCK_0_FREQUENCY_IO_AMCLKO_O_SHIFT) | \
	(2<<PMU_AUDIO_CLOCK_0_FREQUENCY_AMCLK_I2S_SHIFT))
/* 18.4320MHz */
#define PMU_AUDIO_CLOCK_0_18_4320MHZ (\
	(1<<PMU_AUDIO_CLOCK_0_FREQUENCY_IO_AMCLKO_O_SHIFT) | \
	(1<<PMU_AUDIO_CLOCK_0_FREQUENCY_AMCLK_I2S_SHIFT))
/* 24.5760MHz */
#define PMU_AUDIO_CLOCK_0_24_5760MHZ (\
	(0<<PMU_AUDIO_CLOCK_0_FREQUENCY_IO_AMCLKO_O_SHIFT) | \
	(0<<PMU_AUDIO_CLOCK_0_FREQUENCY_AMCLK_I2S_SHIFT))

#define REG_PMU(p, y)	((u32)((unsigned long)(p))+PMU_##y)


/****************************************************************************/
/* GCONF register                                                           */
/****************************************************************************/

/* GCONF_I2SSEL_OFFS */
#if IS_ENABLED(CONFIG_ARCH_TZ3000)
#define GCONF_I2SSEL_OE_N_IN		(1<<GCONF_I2SSEL_OE_N_SHIFT)
#define GCONF_I2SSEL_OE_N_OUT		(0<<GCONF_I2SSEL_OE_N_SHIFT)
#define GCONF_I2SSEL_I2SSEL0		(1<<GCONF_I2SSEL_I2SSEL_SHIFT)
#define GCONF_I2SSEL_I2SSEL1		(2<<GCONF_I2SSEL_I2SSEL_SHIFT)
#define GCONF_I2SSEL_I2SSEL2		(4<<GCONF_I2SSEL_I2SSEL_SHIFT)
#endif

#define REG_GCONF(p, y)	((u32)((unsigned long)(p))+GCONF_##y)


#define INVALID_REG_VAL		0xFFFFFFFF

#if 1
#define reg_out(v, a) { \
	__raw_writel(v, (void __iomem *)a); \
}
#define reg_in(v, a) { \
	*v = __raw_readl((void __iomem *)a); \
}
#else
#define reg_out(v, a) { \
	pr_err("reg out:0x%08X,0x%08X\n", (u32)a, (u32)v); \
	__raw_writel(v, (void __iomem *)a); \
}
#define reg_in(v, a) { \
	*v = __raw_readl((void __iomem *)a); \
}
#endif

enum al_i2s_channel {
	AL_I2SO0_CH = 0,
	AL_I2SI0_CH,
	AL_I2SO1_CH,
	AL_I2SI1_CH,
	AL_I2SC_CH,

	AL_I2S_CHMAX
};

enum audio_clock_num {
	AUDIO_CLOCK_24_5760MHZ = 0,
	AUDIO_CLOCK_18_4320MHZ,
	AUDIO_CLOCK_12_2880MHZ,
	AUDIO_CLOCK_11_2896MHZ,
	AUDIO_CLOCK_MAX
};

enum audio_format_num {
	AUDIO_FORMAT_I2S = 0,
	AUDIO_FORMAT_LR,
	AUDIO_FORMAT_MAX
};

enum al_i2s_status {
	I2S_STATUS_SHUTDOWN = 0,
	I2S_STATUS_STARTUP,
	I2S_STATUS_RUNNING
};

struct al_i2s_param {
	int ch;
	enum al_i2s_status status;
	struct snd_pcm_substream *substream;

	snd_pcm_format_t format;
	unsigned int rate;
	int channels;

	unsigned long offset;
	int period_bytes;
	int periods;
};

enum al_iobase_id {
	IOBASE_I2SO = SNDRV_PCM_STREAM_PLAYBACK,
	IOBASE_I2SI = SNDRV_PCM_STREAM_CAPTURE,
	IOBASE_I2SC,
	IOBASE_GCONF,
	IOBASE_PMU,

	IOBASE_MAX
};

enum al_irq_id {
	I2SO_IRQ_INT = 0,
	I2SO_IRQ_ERR,
	I2SI_IRQ_INT,
	I2SI_IRQ_ERR,

	IRQ_MAX
};

struct al_i2s {
	struct device *dev;
	struct platform_device *pdev;
	struct platform_device soc_dai_pdev;

	/*
	 * 0: I2SO
	 * 1: I2SI
	 * 2: I2SC
	 * 3: GCONF
	 * 4: PMU
	 */
	unsigned int iomem[IOBASE_MAX];
	void __iomem *iobase[IOBASE_MAX];

	/*
	 * 0: I2SO INT irq
	 * 1: I2SO ERR irq
	 * 2: I2SI INT irq
	 * 3: I2SI ERR irq
	 */
	int ioirq[IRQ_MAX];
	spinlock_t lock;

	/*
	 * 0: Playback(I2SO)
	 * 1: Capture(I2SI)
	 */
	unsigned int mclk[2];
	unsigned int fmt[2];
	unsigned int master[2];		/* 0: slave, 1: master */
	unsigned int clock_out[2];	/* 0: no clock out, 1: clock out */
	enum audio_clock_num audioclk_num[2];
	enum audio_format_num fmt_num[2];
	struct al_i2s_param i2s_param[2];

	int mono_rev;			/* 0: not-reverse, 1: reverse */
};

int al_i2s_clk_setup(struct device *dev);
void al_i2s_clk_allput(void);
int al_i2s_hw_reset(int);
int al_i2s_hw_busy(int);
int al_i2s_get_version(void);

#endif /* _APPLITE_I2S_H */
