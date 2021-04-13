/*
 * sound/soc/codecs/tlv320adc3xxx.c
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

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/pm.h>
#include <linux/i2c.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>

#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/soc.h>
#include <sound/soc-dapm.h>
#include <sound/initval.h>

#include "tlv320adc3xxx.h"

/*
 * ****************************************************************************
 *  Macros
 * ****************************************************************************
 *
 */

#define ADC3xxx_DEBUG

#define xprintk(level, fmt, args...) \
	printk(level "tlv320adc3xxx: " fmt , ## args)

#ifdef ADC3xx_CODEC_DEBUG
	#define dprintk(level, fmt, args...) \
		printk(level "tlv320adc3xxx:%s(): " fmt , __func__ , ## args)
#else
	#define dprintk(level, fmt, args...)
#endif

#define ERROR(fmt, args...) \
	xprintk(KERN_ERR , fmt , ## args)
#define INFO(fmt, args...) \
	xprintk(KERN_INFO , fmt , ## args)
#define DBG(fmt, args...) \
	dprintk(KERN_ERR , fmt , ## args)

#define DEFAULT_SYSCLK		(12000000)	/* 12MHz */
#define DEFAULT_FORMAT		(SND_SOC_DAIFMT_I2S | \
				 SND_SOC_DAIFMT_CBM_CFM | \
				 SND_SOC_DAIFMT_NB_NF)

/* codec private data */
struct adc3xxx_priv {
	unsigned int sysclk;
	unsigned int fmt;
	int master;
	u8 page_no;

	void *control_data;
};

static int adc3xxx_set_bias_level(struct snd_soc_codec *,
			enum snd_soc_bias_level);

/*
 * adc3xxx initialization data
 * This structure initialization contains the initialization required for
 * ADC3xxx.
 * These registers values (reg_val) are written into the respective ADC3xxx
 * register offset (reg_offset) to  initialize ADC3xxx.
 * These values are used in adc3xxx_init() function only.
 */
struct adc3xxx_configs {
	u8 reg_offset;
	u8 reg_val;
};

/* The global Register Initialization sequence Array. During the Audio Driver
 * Initialization, this array will be utilized to perform the default
 * initialization of the audio Driver.
 */
static const struct adc3xxx_configs adc3xxx_reg_init[] = {
	/* Select IN1L/IN1R Single Ended (0dB) inputs
	 * use value 10 for no connection, this enables dapm
	 * to switch ON/OFF inputs using MS Bit only.
	 * with this setup, -6dB input option is not used.
	 */
	{LEFT_PGA_SEL_1, 0xA8},
	{RIGHT_PGA_SEL_1, 0xA8},
	/* mute Left PGA + default gain */
	{LEFT_APGA_CTRL, 0x99},
	/* mute Right PGA + default gain */
	{RIGHT_APGA_CTRL, 0x99},
	/* MICBIAS1=2.5V, MICBIAS2=2.5V */
	{MICBIAS_CTRL, 0x50},
	/* Use PLL for generating clocks from MCLK */
	{CLKGEN_MUX, USE_PLL},
	/* I2S, 16LE, codec as Master */
	{INTERFACE_CTRL_1, 0x0C},
	/*BDIV_CLKIN = ADC_CLK, BCLK & WCLK active when power-down */
	{INTERFACE_CTRL_2, 0x02},

	#ifdef ADC3101_CODEC_SUPPORT
	/* Use Primary BCLK and WCLK */
	{INTERFACE_CTRL_4, 0x0},
	#endif

	/* Left AGC Maximum Gain to 40db */
	{LEFT_CHN_AGC_3, 0x50},
	/* Right AGC Maximum Gain to 40db */
	{RIGHT_CHN_AGC_3, 0X50},
	/* ADC control, Gain soft-stepping disabled */
	{ADC_DIGITAL, 0x02},
	/* Fine Gain 0dB, Left/Right ADC Unmute */
	{ADC_FGA, 0x00},

	#ifdef ADC3101_CODEC_SUPPORT
	/* DMCLK output = ADC_MOD_CLK */
	{GPIO2_CTRL, 0x28},
	/* DMDIN is in Dig_Mic_In mode */
	{GPIO1_CTRL, 0x04},
	#endif

	/* Left ADC Channel Volume Control */
	{LADC_VOL, 0x00},
	/* Right ADC Channel Volume Control */
	{RADC_VOL, 0x00},
};


/*
 * PLL and Clock settings
 *   adc_clkin   = mclk * r * k / p = pll_clk
 *   adc_clk     = adc_clkin / nadc
 *   adc_mod_clk = adc_clk / madc
 */

static const struct adc3xxx_rate_divs adc3xxx_divs[] = {
#if IS_ENABLED(CONFIG_ARCH_TZ3000)
	/* TZ3000 Andes */
	/* mclk,   rate,  p, r, j, d,    nadc, madc, aosr, adc_clk */
	/* 11.025k rate */
	{12000000, 11025, 1, 1, 6, 8208, 29,   2,    128,  2822400},
	/* 12k rate */
	{12000000, 12000, 1, 1, 8, 1920, 32,   2,    128,  3072000},
	/* 18k rate */
	{12000000, 18000, 1, 1, 6, 9120, 18,   2,    128,  4608000},
	/* 22.05k rate */
	{12000000, 22050, 1, 1, 7,  560, 15,   2,    128,  5644800},
	/* 24k rate */
	{12000000, 24000, 1, 1, 8, 1920, 16,   2,    128,  6144000},
	/* 29.4k rate */
	{12000000, 29400, 1, 1, 7, 5264, 12,   2,    128,  7526400},
	/* 32k rate */
	{12000000, 32000, 1, 1, 8, 1920, 12,   2,    128,  8192000},
	/* 36k rate */
	{12000000, 36000, 1, 1, 6, 9120,  9,   2,    128,  9216000},
	/* 44.1k rate */
	{12000000, 44100, 1, 1, 7, 5264,  8,   2,    128,  11289600},
	/* 48k rate */
	{12000000, 48000, 1, 1, 7, 1680,  7,   2,    128,  12288000},
	/* 58.8k rate */
	{12000000, 58800, 1, 1, 7, 5264,  6,   4,     64,  15052800},
	/* 64k rate */
	{12000000, 64000, 1, 1, 8, 1920,  6,   4,     64,  16384000},
	/* 72k rate */
	{12000000, 72000, 1, 1, 7, 6800,  5,   4,     64,  18432000},
	/* 88.2k rate */
	{12000000, 88200, 1, 1, 7, 5264,  4,   4,     64,  22579200},
	/* 96k rate */
	{12000000, 96000, 1, 1, 8, 1920,  4,   4,     64,  24576000},
#else
	/* TZ2000 Gregory */
	/* mclk,   rate,  p, r, j, d,    nadc, madc, aosr, adc_clk */
	/* mclk=11.2896MHz */
	/* 11.025k rate */
	{11289600, 11025, 1, 1, 8,    0, 32,   2,    128,  2822400},
	/* 22.05k rate */
	{11289600, 22050, 1, 1, 8,    0, 16,   2,    128,  5644800},
	/* 29.4k rate */
	{11289600, 29400, 1, 1, 8,    0, 12,   2,    128,  7526400},
	/* 44.1k rate */
	{11289600, 44100, 1, 1, 8,    0,  8,   2,    128,  11289600},
	/* 58.8k rate */
	{11289600, 58800, 1, 1, 8,    0,  6,   4,     64,  15052800},
	/* 88.2k rate */
	{11289600, 88200, 1, 1, 8,    0,  4,   4,     64,  22579200},
	/* mclk=12.288MHz */
	/* 12k rate */
	{12288000, 12000, 1, 1, 8,    0, 32,   2,    128,  3072000},
	/* 24k rate */
	{12288000, 24000, 1, 1, 8,    0, 16,   2,    128,  6144000},
	/* 32k rate */
	{12288000, 32000, 1, 1, 8,    0, 12,   2,    128,  8192000},
	/* 48k rate */
	{12288000, 48000, 1, 1, 8,    0,  8,   2,    128,  12288000},
	/* 64k rate */
	{12288000, 64000, 1, 1, 8,    0,  6,   4,     64,  16384000},
	/* 96k rate */
	{12288000, 96000, 1, 1, 8,    0,  4,   4,     64,  24576000},
	/* mclk=18.432MHz */
	/* 18k rate */
	{18432000, 18000, 1, 1, 5,    0, 20,   2,    128,  4608000},
	/* 36k rate */
	{18432000, 36000, 1, 1, 5,    0, 10,   2,    128,  9216000},
	/* 48k rate */
	{18432000, 48000, 1, 1, 5,    0,  5,   3,    128,  18432000},
	/* 72k rate */
	{18432000, 72000, 1, 1, 5,    0,  5,   4,     64,  18432000},
	/* 96k rate */
	{18432000, 96000, 1, 1, 5,    0,  5,   3,     64,  18432000},
	/* mclk=24.576MHz */
	/* 24k rate */
	{24576000, 24000, 1, 1, 8,    0, 32,   2,    128,  6144000},
	/* 48k rate */
	{24576000, 48000, 1, 1, 8,    0, 16,   2,    128,  12288000},
	/* 64k rate */
	{24576000, 64000, 1, 1, 8,    0,  6,   4,     64,  16384000},
	/* 96k rate */
	{24576000, 96000, 1, 1, 8,    0,  8,   4,     64,  24576000},
#endif
};

static inline int adc3xxx_get_divs(int mclk, int rate)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(adc3xxx_divs); i++) {
		if ((adc3xxx_divs[i].rate == rate)
		    && (adc3xxx_divs[i].mclk == mclk)) {
			return i;
		}
	}
	ERROR("Master clock and sample rate is not supported\n");
	return -EINVAL;
}

static int adc3xxx_change_page(struct snd_soc_codec *codec, u8 new_page)
{
	struct adc3xxx_priv *adc3xxx = snd_soc_codec_get_drvdata(codec);
	u8 data[2];
	int ret;

	data[0] = 0x0;
	data[1] = new_page;
	ret = codec->hw_write(codec->control_data, data, 2);
	if (ret == 2) {
		adc3xxx->page_no = new_page;
		return 0;
	} else {
		return ret;
	}
}

static int adc3xxx_write(struct snd_soc_codec *codec, unsigned int reg,
		  unsigned int value)
{
	struct adc3xxx_priv *adc3xxx = snd_soc_codec_get_drvdata(codec);
	u8 data[2];
	u8 page;
	int ret;

	page = reg / ADC3xxx_PAGE_SIZE;
	if (adc3xxx->page_no != page) {
		ret = adc3xxx_change_page(codec, page);
		if (ret != 0)
			return ret;
	}

	/* data is
	 *   D15..D8 adc3xxx register offset
	 *   D7...D0 register data
	 */
	data[0] = reg % ADC3xxx_PAGE_SIZE;
	data[1] = value & 0xFF;

	DBG("I2C_WRITE 0x%02X(%d),0x%02X(%d)\n",
		data[0], data[0], data[1], data[1]);
	if (codec->hw_write(codec->control_data, data, 2) == 2)
		return 0;
	else
		return -EIO;
}

static unsigned int adc3xxx_read(struct snd_soc_codec *codec,
			unsigned int reg)
{
	struct adc3xxx_priv *adc3xxx = snd_soc_codec_get_drvdata(codec);
	u8 page;
	unsigned int data;
	int ret;

	page = reg / ADC3xxx_PAGE_SIZE;
	if (adc3xxx->page_no != page) {
		ret = adc3xxx_change_page(codec, page);
		if (ret != 0)
			return ret;
	}
	data = i2c_smbus_read_byte_data(codec->control_data,
					(reg % ADC3xxx_PAGE_SIZE));
	DBG("I2S_READ 0x%02X(%d),0x%02X(%d)\n",
		reg, reg, data, data);
	return data;
}

static u32 adc3xxx_rates[] = {
/*	8000,*/
	11025,
	12000,
	16000,
	18000,
	22050,
	24000,
	29400,
	32000,
	36000,
	44100,
	48000,
	58800,
	64000,
	72000,
	88200,
	96000
};

static struct snd_pcm_hw_constraint_list adc3xxx_constraints = {
	.count  = ARRAY_SIZE(adc3xxx_rates),
	.list   = adc3xxx_rates,
};


static int snd_soc_adc3xxx_put_volsw(struct snd_kcontrol *kcontrol,
				     struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_codec *codec = snd_kcontrol_chip(kcontrol);
	s8 val1, val2;
	u8 reg;

	val1 = ucontrol->value.integer.value[0];
	val2 = ucontrol->value.integer.value[1];

	if ((val1 >= ADC_POS_VOL)) {
		if (val1 > ADC_MAX_VOLUME)
			val1 = ADC_MAX_VOLUME;
		val1 = val1 - ADC_POS_VOL;
	} else if ((val1 >= 0) && (val1 <= 23)) {
		val1 = ADC_POS_VOL - val1;
		val1 = 128 - val1;
	} else {
		return -EINVAL;
	}

	if (val2 >= ADC_POS_VOL) {
		if (val2 > ADC_MAX_VOLUME)
			val2 = ADC_MAX_VOLUME;
		val2 = val2 - ADC_POS_VOL;
	} else if ((val2 >= 0) && (val2 <= 23)) {
		val2 = ADC_POS_VOL - val2;
		val2 = 128 - val2;
	} else {
		return -EINVAL;
	}

	reg = (u8)snd_soc_read(codec, LADC_VOL) & (~0x7F);
	snd_soc_write(codec, LADC_VOL, reg | (val1 << 0));
	reg = (u8)snd_soc_read(codec, RADC_VOL) & (~0x7F);
	snd_soc_write(codec, RADC_VOL, reg | (val2 << 0));

	return 0;
}

static int snd_soc_adc3xxx_get_volsw(struct snd_kcontrol *kcontrol,
				     struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_codec *codec = snd_kcontrol_chip(kcontrol);
	u8 val1;
	u8 val2;

	val1 = (u8)snd_soc_read(codec, LADC_VOL) & (0x7F);
	if ((val1 >= 0) && (val1 <= 40))
		val1 = val1 + ADC_POS_VOL;
	else if ((val1 >= 104) && (val1 <= 127))
		val1 = val1 - 104;
	else
		return -EINVAL;

	val2 = (u8)snd_soc_read(codec, RADC_VOL) & (0x7F);
	if ((val2 >= 0) && (val2 <= 40))
		val2 = val2 + ADC_POS_VOL;
	else if ((val2 >= 104) && (val2 <= 127))
		val2 = val2 - 104;
	else
		return -EINVAL;

	ucontrol->value.integer.value[0] = val1;
	ucontrol->value.integer.value[1] = val2;
	return 0;

}

#define SOC_ADC3xxx_DOUBLE_R(xname, reg_left, reg_right, xshift, xmax, xinvert) \
{	.iface = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname), \
	.info = snd_soc_info_volsw, \
	.get = snd_soc_adc3xxx_get_volsw, .put = snd_soc_adc3xxx_put_volsw, \
	.private_value = (unsigned long)&(struct soc_mixer_control) \
		{.reg = reg_left, .rreg = reg_right, .shift = xshift, \
		 .max = xmax, .invert = xinvert} }

static const char *micbias_voltage[] = { "off", "2V", "2.5V", "AVDD" };
static const char *linein_attenuation[] = { "0db", "-6db" };
static const char *adc_softstepping[] = { "1 step", "2 step", "off" };

#define MICBIAS1_ENUM		0
#define MICBIAS2_ENUM		1
#define ATTLINEL1_ENUM		2
#define ATTLINEL2_ENUM		3
#define ATTLINEL3_ENUM		4
#define ATTLINER1_ENUM		5
#define ATTLINER2_ENUM		6
#define ATTLINER3_ENUM		7
#define ADCSOFTSTEP_ENUM	8

/* Creates an array of the Single Ended Widgets*/
static const struct soc_enum adc3xxx_enum[] = {
	SOC_ENUM_SINGLE(MICBIAS_CTRL, 5, 4, micbias_voltage),
	SOC_ENUM_SINGLE(MICBIAS_CTRL, 3, 4, micbias_voltage),
	SOC_ENUM_SINGLE(LEFT_PGA_SEL_1, 0, 2, linein_attenuation),
	SOC_ENUM_SINGLE(LEFT_PGA_SEL_1, 2, 2, linein_attenuation),
	SOC_ENUM_SINGLE(LEFT_PGA_SEL_1, 4, 2, linein_attenuation),
	SOC_ENUM_SINGLE(RIGHT_PGA_SEL_1, 0, 2, linein_attenuation),
	SOC_ENUM_SINGLE(RIGHT_PGA_SEL_1, 2, 2, linein_attenuation),
	SOC_ENUM_SINGLE(RIGHT_PGA_SEL_1, 4, 2, linein_attenuation),
	SOC_ENUM_SINGLE(ADC_DIGITAL, 0, 3, adc_softstepping),
};
/* Various Controls For adc3xxx */
static const struct snd_kcontrol_new adc3xxx_snd_controls[] = {
	/* PGA Gain Volume Control */
	SOC_DOUBLE_R("PGA Gain Volume Control (0=0dB, 80=40dB)",
		    LEFT_APGA_CTRL, RIGHT_APGA_CTRL, 0, 0x50, 0),
	/* Audio gain control (AGC) */
	SOC_DOUBLE_R("Audio Gain Control (AGC)", LEFT_CHN_AGC_1,
		     RIGHT_CHN_AGC_1, 7, 0x01, 0),
	/* AGC Target level control */
	SOC_DOUBLE_R("AGC Target Level Control", LEFT_CHN_AGC_1,
		     RIGHT_CHN_AGC_1, 4, 0x07, 1),
	/* AGC Maximum PGA applicable */
	SOC_DOUBLE_R("AGC Maximum PGA Control", LEFT_CHN_AGC_3,
		     RIGHT_CHN_AGC_3, 0, 0x50, 0),
	/* AGC Attack Time control */
	SOC_DOUBLE_R("AGC Attack Time control", LEFT_CHN_AGC_4,
		     RIGHT_CHN_AGC_4, 3, 0x1F, 0),
	/* AGC Decay Time control */
	SOC_DOUBLE_R("AGC Decay Time control", LEFT_CHN_AGC_5,
		     RIGHT_CHN_AGC_5, 3, 0x1F, 0),
	/* AGC Noise Bounce control */
	SOC_DOUBLE_R("AGC Noice bounce control", LEFT_CHN_AGC_6,
		     RIGHT_CHN_AGC_6, 0, 0x1F, 0),
	/* AGC Signal Bounce control */
	SOC_DOUBLE_R("AGC Signal bounce control", LEFT_CHN_AGC_7,
		     RIGHT_CHN_AGC_7, 0, 0x0F, 0),
	/* Mic Bias voltage */
	SOC_ENUM("Mic Bias 1 Voltage", adc3xxx_enum[MICBIAS1_ENUM]),
	SOC_ENUM("Mic Bias 2 Voltage", adc3xxx_enum[MICBIAS2_ENUM]),
	/* ADC soft stepping */
	SOC_ENUM("ADC soft stepping", adc3xxx_enum[ADCSOFTSTEP_ENUM]),
	/* Left/Right Input attenuation */
	SOC_ENUM("Left Linein1 input attenuation",
		 adc3xxx_enum[ATTLINEL1_ENUM]),
	SOC_ENUM("Left Linein2 input attenuation",
		 adc3xxx_enum[ATTLINEL2_ENUM]),
	SOC_ENUM("Left Linein3 input attenuation",
		 adc3xxx_enum[ATTLINEL3_ENUM]),
	SOC_ENUM("Right Linein1 input attenuation",
		 adc3xxx_enum[ATTLINER1_ENUM]),
	SOC_ENUM("Right Linein2 input attenuation",
		 adc3xxx_enum[ATTLINER2_ENUM]),
	SOC_ENUM("Right Linein3 input attenuation",
		 adc3xxx_enum[ATTLINER3_ENUM]),
	/* ADC Volume */
	SOC_ADC3xxx_DOUBLE_R("ADC Volume Control (0=-12dB, 64=+20dB)", LADC_VOL,
		 RADC_VOL, 0, 64, 0),
	/* ADC Fine Volume */
	SOC_SINGLE("Left ADC Fine Volume (0=-0.4dB, 4=0dB)", ADC_FGA, 4, 4, 1),
	SOC_SINGLE("Right ADC Fine Volume (0=-0.4dB, 4=0dB)", ADC_FGA, 0, 4, 1),
};

/* Left input selection, Single Ended inputs and Differential inputs */
static const struct snd_kcontrol_new left_input_mixer_controls[] = {
	SOC_DAPM_SINGLE("IN1_L switch", LEFT_PGA_SEL_1, 1, 0x1, 1),
	SOC_DAPM_SINGLE("IN2_L switch", LEFT_PGA_SEL_1, 3, 0x1, 1),
	SOC_DAPM_SINGLE("IN3_L switch", LEFT_PGA_SEL_1, 5, 0x1, 1),
	SOC_DAPM_SINGLE("DIF1_L switch", LEFT_PGA_SEL_1, 7, 0x1, 1),
	SOC_DAPM_SINGLE("DIF2_L switch", LEFT_PGA_SEL_2, 5, 0x1, 1),
	SOC_DAPM_SINGLE("DIF3_L switch", LEFT_PGA_SEL_2, 3, 0x1, 1),
	SOC_DAPM_SINGLE("IN1_R switch", LEFT_PGA_SEL_2, 1, 0x1, 1),
};

/* Right input selection, Single Ended inputs and Differential inputs */
static const struct snd_kcontrol_new right_input_mixer_controls[] = {
	SOC_DAPM_SINGLE("IN1_R switch", RIGHT_PGA_SEL_1, 1, 0x1, 1),
	SOC_DAPM_SINGLE("IN2_R switch", RIGHT_PGA_SEL_1, 3, 0x1, 1),
	SOC_DAPM_SINGLE("IN3_R switch", RIGHT_PGA_SEL_1, 5, 0x1, 1),
	SOC_DAPM_SINGLE("DIF1_R switch", RIGHT_PGA_SEL_1, 7, 0x1, 1),
	SOC_DAPM_SINGLE("DIF2_R switch", RIGHT_PGA_SEL_2, 5, 0x1, 1),
	SOC_DAPM_SINGLE("DIF3_R switch", RIGHT_PGA_SEL_2, 3, 0x1, 1),
	SOC_DAPM_SINGLE("IN1_L switch", RIGHT_PGA_SEL_2, 1, 0x1, 1),
};

/* Left Digital Mic input for left ADC */
static const struct snd_kcontrol_new left_input_dmic_controls[] = {
	SOC_DAPM_SINGLE("Left ADC switch", ADC_DIGITAL, 3, 0x1, 0),
};

/* Right Digital Mic input for Right ADC */
static const struct snd_kcontrol_new right_input_dmic_controls[] = {
	SOC_DAPM_SINGLE("Right ADC switch", ADC_DIGITAL, 2, 0x1, 0),
};

/* adc3xxx Widget structure */
static const struct snd_soc_dapm_widget adc3xxx_dapm_widgets[] = {

	/* Left Input Selection */
	SND_SOC_DAPM_MIXER("Left Input Selection", SND_SOC_NOPM, 0, 0,
			   &left_input_mixer_controls[0],
			   ARRAY_SIZE(left_input_mixer_controls)),
	/* Right Input Selection */
	SND_SOC_DAPM_MIXER("Right Input Selection", SND_SOC_NOPM, 0, 0,
			   &right_input_mixer_controls[0],
			   ARRAY_SIZE(right_input_mixer_controls)),
	/*PGA selection */
	SND_SOC_DAPM_PGA("Left PGA", LEFT_APGA_CTRL, 7, 1, NULL, 0),
	SND_SOC_DAPM_PGA("Right PGA", RIGHT_APGA_CTRL, 7, 1, NULL, 0),

	/*Digital Microphone Input Control for Left/Right ADC */
	SND_SOC_DAPM_MIXER("Left DMic Input", SND_SOC_NOPM, 0, 0,
			&left_input_dmic_controls[0],
			ARRAY_SIZE(left_input_dmic_controls)),
	SND_SOC_DAPM_MIXER("Right DMic Input", SND_SOC_NOPM , 0, 0,
			&right_input_dmic_controls[0],
			ARRAY_SIZE(right_input_dmic_controls)),

	/* Left/Right ADC */
	SND_SOC_DAPM_ADC("Left ADC", "Left Capture", ADC_DIGITAL, 7, 0),
	SND_SOC_DAPM_ADC("Right ADC", "Right Capture", ADC_DIGITAL, 6, 0),

	/* Inputs */
	SND_SOC_DAPM_INPUT("IN1_L"),
	SND_SOC_DAPM_INPUT("IN1_R"),
	SND_SOC_DAPM_INPUT("IN2_L"),
	SND_SOC_DAPM_INPUT("IN2_R"),
	SND_SOC_DAPM_INPUT("IN3_L"),
	SND_SOC_DAPM_INPUT("IN3_R"),
	SND_SOC_DAPM_INPUT("DIF1_L"),
	SND_SOC_DAPM_INPUT("DIF2_L"),
	SND_SOC_DAPM_INPUT("DIF3_L"),
	SND_SOC_DAPM_INPUT("DIF1_R"),
	SND_SOC_DAPM_INPUT("DIF2_R"),
	SND_SOC_DAPM_INPUT("DIF3_R"),
	SND_SOC_DAPM_INPUT("DMic_L"),
	SND_SOC_DAPM_INPUT("DMic_R"),
};

/* DAPM Routing related array declaration */
static const struct snd_soc_dapm_route adc3xxx_dapm_routes[] = {
/* Left input selection from switchs */
	{"Left Input Selection", "IN1_L switch", "IN1_L"},
	{"Left Input Selection", "IN2_L switch", "IN2_L"},
	{"Left Input Selection", "IN3_L switch", "IN3_L"},
	{"Left Input Selection", "DIF1_L switch", "DIF1_L"},
	{"Left Input Selection", "DIF2_L switch", "DIF2_L"},
	{"Left Input Selection", "DIF3_L switch", "DIF3_L"},
	{"Left Input Selection", "IN1_R switch", "IN1_R"},

/* Left input selection to left PGA */
	{"Left PGA", NULL, "Left Input Selection"},

/* Left PGA to left ADC */
	{"Left ADC", NULL, "Left PGA"},

/* Right input selection from switchs */
	{"Right Input Selection", "IN1_R switch", "IN1_R"},
	{"Right Input Selection", "IN2_R switch", "IN2_R"},
	{"Right Input Selection", "IN3_R switch", "IN3_R"},
	{"Right Input Selection", "DIF1_R switch", "DIF1_R"},
	{"Right Input Selection", "DIF2_R switch", "DIF2_R"},
	{"Right Input Selection", "DIF3_R switch", "DIF3_R"},
	{"Right Input Selection", "IN1_L switch", "IN1_L"},

/* Right input selection to right PGA */
	{"Right PGA", NULL, "Right Input Selection"},

/* Right PGA to right ADC */
	{"Right ADC", NULL, "Right PGA"},

/* Left DMic Input selection from switch */
	{"Left DMic Input", "Left ADC switch", "DMic_L"},

/* Left DMic to left ADC */
	{"Left ADC", NULL, "Left DMic Input"},

/* Right DMic Input selection from switch */
	{"Right DMic Input", "Right ADC switch", "DMic_R"},

/* Right DMic to right ADC */
	{"Right ADC", NULL, "Right DMic Input"},
};

static int adc3xxx_add_widgets(struct snd_soc_codec *codec)
{
	snd_soc_dapm_new_controls(&codec->dapm, adc3xxx_dapm_widgets,
			ARRAY_SIZE(adc3xxx_dapm_widgets));

	/* set up audio path interconnects */
	snd_soc_dapm_add_routes(&codec->dapm, adc3xxx_dapm_routes,
			ARRAY_SIZE(adc3xxx_dapm_routes));
	snd_soc_dapm_new_widgets(&codec->dapm);
	return 0;
}

static int adc3xxx_startup(struct snd_pcm_substream *substream,
		struct snd_soc_dai *dai)
{
	DBG("enter\n");

	snd_pcm_hw_constraint_list(substream->runtime, 0,
			SNDRV_PCM_HW_PARAM_RATE,
			&adc3xxx_constraints);
	return 0;
}

static int adc3xxx_hw_params(struct snd_pcm_substream *substream,
		struct snd_pcm_hw_params *params,
		struct snd_soc_dai *dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_codec *codec = rtd->codec;
	struct adc3xxx_priv *adc3xxx = snd_soc_codec_get_drvdata(codec);
	int i, width = 16;
	u8 data, bdiv;

	DBG("enter(%s)\n", rtd->dai_link->stream_name);

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		return 0;

	i = adc3xxx_get_divs(adc3xxx->sysclk, params_rate(params));
	if (i < 0) {
		ERROR("Clock configuration is not supported\n");
		return i;
	}

	/* select data word length */
	data = (u8)snd_soc_read(codec, INTERFACE_CTRL_1) & (~WLENGTH_MASK);
	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S16_LE:
		width = 16;
		break;
	case SNDRV_PCM_FORMAT_S20_3LE:
		data |= (0x01 << 4);
		width = 20;
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
		data |= (0x02 << 4);
		width = 24;
		break;
	case SNDRV_PCM_FORMAT_S32_LE:
		data |= (0x03 << 4);
		width = 32;
		break;
	}
	snd_soc_write(codec, INTERFACE_CTRL_1, data);

	/* P & R values */
	snd_soc_write(codec, PLL_PROG_PR,
		((adc3xxx_divs[i].pll_p << PLLP_SHIFT) | \
		 (adc3xxx_divs[i].pll_r << PLLR_SHIFT)));

	/* J value */
	snd_soc_write(codec, PLL_PROG_J, adc3xxx_divs[i].pll_j & PLLJ_MASK);
	/* D value */
	snd_soc_write(codec, PLL_PROG_D_LSB,
		adc3xxx_divs[i].pll_d & PLLD_LSB_MASK);
	snd_soc_write(codec, PLL_PROG_D_MSB,
		(adc3xxx_divs[i].pll_d >> 8) & PLLD_MSB_MASK);
	/* NADC */
	snd_soc_write(codec, ADC_NADC, adc3xxx_divs[i].nadc & NADC_MASK);
	/* MADC */
	snd_soc_write(codec, ADC_MADC, adc3xxx_divs[i].madc & MADC_MASK);
	/* AOSR */
	snd_soc_write(codec, ADC_AOSR, adc3xxx_divs[i].aosr & AOSR_MASK);
	/* BDIV N Value */
	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S16_LE:
		width = 16 * 2;
		break;
	default:
	case SNDRV_PCM_FORMAT_S32_LE:
		width = 32 * 2;
		break;
	}
	bdiv = adc3xxx_divs[i].adc_clk / (adc3xxx_divs[i].rate * width);
	snd_soc_write(codec, BCLK_N_DIV, bdiv & BDIV_MASK);

	adc3xxx_set_bias_level(codec, SND_SOC_BIAS_PREPARE);
	adc3xxx_set_bias_level(codec, SND_SOC_BIAS_ON);

	return 0;
}

static int adc3xxx_hw_free(struct snd_pcm_substream *substream,
			struct snd_soc_dai *dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_codec *codec = rtd->codec;

	DBG("enter(%s)\n", rtd->dai_link->stream_name);

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		return 0;

	adc3xxx_set_bias_level(codec, SND_SOC_BIAS_PREPARE);
	adc3xxx_set_bias_level(codec, SND_SOC_BIAS_STANDBY);

	return 0;
}

static int adc3xxx_set_dai_sysclk(struct snd_soc_dai *codec_dai,
		int clk_id, unsigned int freq, int dir)
{
	struct adc3xxx_priv *adc3xxx = snd_soc_dai_get_drvdata(codec_dai);

	DBG("enter(freq=%d)\n", freq);

	if (dir == SND_SOC_CLOCK_OUT)
		return 0;

	adc3xxx->sysclk = freq;
	return 0;
}


static int adc3xxx_set_dai_fmt(struct snd_soc_dai *codec_dai,
			unsigned int fmt)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	struct adc3xxx_priv *adc3xxx = snd_soc_dai_get_drvdata(codec_dai);
	u8 iface_reg;
	u8 prb_sel_reg;

	DBG("enter (fmt=0x%08X)\n", fmt);

	iface_reg = snd_soc_read(codec, INTERFACE_CTRL_1) & (~FMT_MASK);

	/* set master/slave audio interface */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		DBG("codec master\n");
		adc3xxx->master = 1;
		iface_reg |= BCLK_MASTER | WCLK_MASTER;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		DBG("codec slave\n");
		adc3xxx->master = 0;
		iface_reg &= ~(BCLK_MASTER | WCLK_MASTER);
		break;
	case SND_SOC_DAIFMT_CBS_CFM: /* new case..just for debugging */
		DBG("codec slave(BCLK by codec ie BCLK output)\n");
		adc3xxx->master = 0;
		/* BCLK by codec ie BCLK output */
		iface_reg |=  (BCLK_MASTER);
		iface_reg &= ~(WCLK_MASTER);
		break;
	default:
		ERROR("Invalid DAI master/slave interface\n");
		return -EINVAL;
	}

	/*
	 * match both interface format and signal polarities since they
	 * are fixed
	 */
	iface_reg &= ~(0xC0);
	switch (fmt & (SND_SOC_DAIFMT_FORMAT_MASK | SND_SOC_DAIFMT_INV_MASK)) {
	case (SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF):
		prb_sel_reg = 0x01;
		break;
	case (SND_SOC_DAIFMT_DSP_A | SND_SOC_DAIFMT_IB_NF):
		iface_reg |= (0x01 << 6);
		prb_sel_reg = 0x04;
		break;
	case (SND_SOC_DAIFMT_DSP_B | SND_SOC_DAIFMT_IB_NF):
		iface_reg |= (0x01 << 6);
		prb_sel_reg = 0x04;
		break;
	case (SND_SOC_DAIFMT_RIGHT_J | SND_SOC_DAIFMT_NB_NF):
		iface_reg |= (0x02 << 6);
		prb_sel_reg = 0x04;
		break;
	case (SND_SOC_DAIFMT_LEFT_J | SND_SOC_DAIFMT_NB_NF):
		iface_reg |= (0x03 << 6);
		prb_sel_reg = 0x04;
		break;
	default:
		ERROR("Invalid DAI format\n");
		return -EINVAL;
	}

	/* set iface */
	snd_soc_write(codec, INTERFACE_CTRL_1, iface_reg);

	adc3xxx->fmt = fmt;

	return 0;
}

static int adc3xxx_set_bias_level(struct snd_soc_codec *codec,
			enum snd_soc_bias_level level)
{
	struct adc3xxx_priv *adc3xxx = snd_soc_codec_get_drvdata(codec);
	u8 reg;

	DBG("enter\n");

	/* Check if the New Bias level is equal to the existing one,
	   if so return */
	if (codec->dapm.bias_level == level)
		return 0;

	/* all power is driven by DAPM system */
	switch (level) {
	case SND_SOC_BIAS_ON:
		DBG("SND_SOC_BIAS_ON: master=%d\n", adc3xxx->master);
		if (adc3xxx->master) {
			/* Enable pll */
			reg = (u8)snd_soc_read(codec, PLL_PROG_PR);
			snd_soc_write(codec, PLL_PROG_PR, reg | ENABLE_PLL);

			/* 10msec delay needed after PLL power-up */
			mdelay(10);

			/* Switch on NADC Divider */
			reg = (u8)snd_soc_read(codec, ADC_NADC);
			snd_soc_write(codec, ADC_NADC, reg | ENABLE_NADC);

			/* Switch on MADC Divider */
			reg = (u8)snd_soc_read(codec, ADC_MADC);
			snd_soc_write(codec, ADC_MADC, reg | ENABLE_MADC);

			/* Switch on BCLK_N Divider */
			reg = (u8)snd_soc_read(codec, BCLK_N_DIV);
			snd_soc_write(codec, BCLK_N_DIV, reg | ENABLE_BCLK);
		} else {
			/* Enable pll */
			reg = (u8)snd_soc_read(codec, PLL_PROG_PR);
			snd_soc_write(codec, PLL_PROG_PR, reg | ENABLE_PLL);

			/* 10msec delay needed after PLL power-up */
			mdelay(10);

			/* Switch on NADC Divider */
			reg = (u8)snd_soc_read(codec, ADC_NADC);
			snd_soc_write(codec, ADC_NADC, reg | ENABLE_NADC);

			/* Switch on MADC Divider */
			reg = (u8)snd_soc_read(codec, ADC_MADC);
			snd_soc_write(codec, ADC_MADC, reg | ENABLE_MADC);

			/* Switch on BCLK_N Divider */
			reg = (u8)snd_soc_read(codec, BCLK_N_DIV);
			snd_soc_write(codec, BCLK_N_DIV, reg | ENABLE_BCLK);

		}
		break;

		/* partial On */
	case SND_SOC_BIAS_PREPARE:
		DBG("SND_SOC_BIAS_PREPARE: master=%d\n", adc3xxx->master);
		break;

		/* Off, with power */
	case SND_SOC_BIAS_STANDBY:
		DBG("SND_SOC_BIAS_STANDBY: master=%d\n", adc3xxx->master);
		if (adc3xxx->master) {
			/* switch off pll */
			reg = (u8)snd_soc_read(codec, PLL_PROG_PR);
			snd_soc_write(codec, PLL_PROG_PR, reg & (~ENABLE_PLL));

			/* Switch off NADC Divider */
			reg = (u8)snd_soc_read(codec, ADC_NADC);
			snd_soc_write(codec, ADC_NADC, reg & (~ENABLE_NADC));

			/* Switch off MADC Divider */
			reg = (u8)snd_soc_read(codec, ADC_MADC);
			snd_soc_write(codec, ADC_MADC, reg & (~ENABLE_MADC));

			/* Switch off BCLK_N Divider */
			reg = (u8)snd_soc_read(codec, BCLK_N_DIV);
			snd_soc_write(codec, BCLK_N_DIV, reg & (~ENABLE_BCLK));
		}
		break;

		/* Off without power */
	case SND_SOC_BIAS_OFF:
		DBG("SND_SOC_BIAS_OFF: master=%d\n", adc3xxx->master);
		/* power off Left/Right ADC channels */
		reg = (u8)snd_soc_read(codec, ADC_DIGITAL);
		snd_soc_write(codec, ADC_DIGITAL,
			reg & ~(LADC_PWR_ON | RADC_PWR_ON));

		/* Turn off PLLs */
		if (adc3xxx->master) {
			/* switch off pll */
			reg = (u8)snd_soc_read(codec, PLL_PROG_PR);
			snd_soc_write(codec, PLL_PROG_PR, reg & (~ENABLE_PLL));

			/* Switch off NADC Divider */
			reg = (u8)snd_soc_read(codec, ADC_NADC);
			snd_soc_write(codec, ADC_NADC, reg & (~ENABLE_NADC));

			/* Switch off MADC Divider */
			reg = (u8)snd_soc_read(codec, ADC_MADC);
			snd_soc_write(codec, ADC_MADC, reg & (~ENABLE_MADC));

			/* Switch off BCLK_N Divider */
			reg = (u8)snd_soc_read(codec, BCLK_N_DIV);
			snd_soc_write(codec, BCLK_N_DIV, reg & (~ENABLE_BCLK));
		}
		break;
	}
	codec->dapm.bias_level = level;

	return 0;
}

static const struct snd_soc_dai_ops adc3xxx_dai_ops = {
	.startup	= adc3xxx_startup,
	.hw_params	= adc3xxx_hw_params,
	.hw_free	= adc3xxx_hw_free,
	.set_fmt	= adc3xxx_set_dai_fmt,
	.set_sysclk	= adc3xxx_set_dai_sysclk,
};

static struct snd_soc_dai_driver adc3xxx_dai = {
	.name = ADC3xxx_CODEC_DAI_NAME,
	.playback = {
		.stream_name = "Playback",
		/*.channels_min = 1,*/
		.channels_min = 2, /* unsupported mono */
		.channels_max = 2,
		.rates = ADC3xxx_RATES,
		.formats = ADC3xxx_FORMATS,},
	.capture = {
		.stream_name = "Capture",
		/*.channels_min = 1,*/
		.channels_min = 2, /* unsupported mono */
		.channels_max = 2,
		.rates = ADC3xxx_RATES,
		.formats = ADC3xxx_FORMATS,},
	.ops = &adc3xxx_dai_ops,
};

static int adc3xxx_i2c_init(struct snd_soc_codec *codec)
{
	int i, ret = 0;

	DBG("enter\n");

	/* Select Page 0 */
	snd_soc_write(codec, PAGE_SELECT, 0);
	/* Issue software reset to adc3xxx */
	snd_soc_write(codec, RESET, SOFT_RESET);

	for (i = 0;
	     i < sizeof(adc3xxx_reg_init) / sizeof(struct adc3xxx_configs);
	     i++) {
		snd_soc_write(codec, adc3xxx_reg_init[i].reg_offset,
			adc3xxx_reg_init[i].reg_val);
	}

	return ret;
}


static int adc3xxx_suspend(struct snd_soc_codec *codec)
{
	adc3xxx_set_bias_level(codec, SND_SOC_BIAS_OFF);

	return 0;
}

static int adc3xxx_resume(struct snd_soc_codec *codec)
{
	adc3xxx_set_bias_level(codec, SND_SOC_BIAS_STANDBY);

	return 0;
}

static int adc3xxx_probe(struct snd_soc_codec *codec)
{
	struct adc3xxx_priv *adc3xxx = snd_soc_codec_get_drvdata(codec);
	int ret = 0;

	INFO("ADC3xxx Audio Codec %s\n", ADC3xxx_VERSION);

	codec->hw_write = (hw_write_t)i2c_master_send;
	codec->control_data = adc3xxx->control_data;

	ret = adc3xxx_i2c_init(codec);
	if (ret < 0) {
		ERROR("adc3xxx: failed to initialize ADC3xxx\n");
		return ret;
	}

	/* power on device */
	adc3xxx_set_bias_level(codec, SND_SOC_BIAS_STANDBY);
	snd_soc_add_codec_controls(codec, adc3xxx_snd_controls,
		ARRAY_SIZE(adc3xxx_snd_controls));

	adc3xxx_add_widgets(codec);

	return ret;
}

static int adc3xxx_remove(struct snd_soc_codec *codec)
{
	adc3xxx_set_bias_level(codec, SND_SOC_BIAS_OFF);
	return 0;
}

static struct snd_soc_codec_driver soc_codec_dev_adc3xxx = {
	.read = adc3xxx_read,
	.write = adc3xxx_write,
	.probe = adc3xxx_probe,
	.remove = adc3xxx_remove,
	.suspend = adc3xxx_suspend,
	.resume = adc3xxx_resume,
};

/*
 * If the i2c layer weren't so broken, we could pass this kind of data
 * around
 */
static __devinit int adc3xxx_i2c_probe(struct i2c_client *i2c,
		const struct i2c_device_id *i2c_id)
{
	struct adc3xxx_priv *adc3xxx;
	int ret;

	DBG("enter\n");

	adc3xxx = devm_kzalloc(&i2c->dev, sizeof(struct adc3xxx_priv), GFP_KERNEL);
	if (adc3xxx == NULL)
		return -ENOMEM;
	memset(adc3xxx, 0x00, sizeof(*adc3xxx));

	adc3xxx->sysclk = DEFAULT_SYSCLK;
	adc3xxx->fmt = DEFAULT_FORMAT;
	adc3xxx->control_data = i2c;
	i2c_set_clientdata(i2c, adc3xxx);

	ret =  snd_soc_register_codec(&i2c->dev, &soc_codec_dev_adc3xxx,
			&adc3xxx_dai, 1);
	if (ret < 0) {
		ERROR("adc3xxx: failed to snd_soc_register_codec()\n");
		i2c_set_clientdata(i2c, NULL);
		return ret;
	}

	return ret;
}

static int __devexit adc3xxx_i2c_remove(struct i2c_client *i2c)
{
	snd_soc_unregister_codec(&i2c->dev);
	return 0;
}

static const struct i2c_device_id adc3xxx_id[] = {
	{"tlv320adc3xxx", 0},
	{}
};

MODULE_DEVICE_TABLE(i2c, adc3xxx_id);

static struct i2c_driver adc3xxx_i2c_driver = {
	.driver = {
		.name = ADC3xxx_CODEC_DEV_NAME,
		.owner = THIS_MODULE,
	},
	.probe	  = adc3xxx_i2c_probe,
	.remove =   __devexit_p(adc3xxx_i2c_remove),
	.id_table = adc3xxx_id,
};
module_i2c_driver(adc3xxx_i2c_driver);

MODULE_AUTHOR("TOSHIBA Corporation");
MODULE_DESCRIPTION("ASoC TLV320ADC3xxx codec driver");
MODULE_LICENSE("GPL v2");
