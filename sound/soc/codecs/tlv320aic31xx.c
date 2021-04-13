/*
 * sound/soc/codecs/tlv320aic31xx.c
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
 *	power=b		Default false, Power Control
 *			(true is power on/off, false is always power up)
 *                                      24.5760, 18.4320, 12.2880, or 11.2896)
 *      mute=b		Default false, Mute Control
 *			(true is mute/unmute, false is always unmute)
 */


/******************************************************************************
 * INCLUDE HEADER FILES
 *****************************************************************************/
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/pm.h>
#include <linux/i2c.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/gpio.h>
/*#include <linux/switch.h>*/
#include <linux/clk.h>
#include <linux/device.h>
#include <linux/dma-mapping.h>
#include <linux/interrupt.h>
#include <linux/dmaengine.h>
#include <asm/mach-types.h>

#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/soc.h>
#include <sound/soc-dapm.h>
#include <sound/initval.h>
/*#include <linux/regulator/consumer.h>*/
#include "tlv320aic31xx.h"
#include <linux/clk.h>
#include <sound/tlv.h>

/******************************************************************************
 * GLOBAL VARIABLES
 *****************************************************************************/

/* Encapsulate the module parameter settings */
static struct codec_ctrl_data {
	bool power_ctrl;
	bool mute_ctrl;
} ctrl_data = {
	.power_ctrl     = true,
	.mute_ctrl      = true,
};

module_param_named(power, ctrl_data.power_ctrl, bool, S_IRUGO);
MODULE_PARM_DESC(power, "Power Control (false, or true)");

module_param_named(mute, ctrl_data.mute_ctrl, bool, S_IRUGO);
MODULE_PARM_DESC(mute, "Mute Control (false, or true)");


static struct aic31xx_priv *aic_priv;
#ifdef AIC31xx_REGULATOR
struct regulator *audio_regulator;
#endif

/* Used to maintain the Register Access control*/
static u8 aic31xx_reg_ctl;

/* Global Variables introduced to reduce Headphone Analog Volume Control
 * Registers at run-time */
/*static struct i2c_msg i2c_right_transaction[120];*/
/*static struct i2c_msg i2c_left_transaction[120];*/

static int aic31xx_mute_codec(struct snd_soc_codec *codec, int mute);
static int aic31xx_write(struct snd_soc_codec *codec, unsigned int reg,
		unsigned int value);
static unsigned int aic31xx_read(struct snd_soc_codec *codec, unsigned int reg);
static int aic31xx_hp_power_up(struct snd_soc_codec *codec);
static int aic31xx_hp_power_down(struct snd_soc_codec *codec);

#define SOC_SINGLE_AIC31XX_N(xname, reg, shift, max, invert)\
{\
	.iface = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = n_control_info, .get = n_control_get,\
	.put = n_control_put, \
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE, \
	.private_value =  SOC_SINGLE_VALUE(reg, shift, max, invert) }




#define SOC_SINGLE_AIC31XX(xname) {					\
	.iface = SNDRV_CTL_ELEM_IFACE_MIXER,			\
	.name = xname,					\
	.info = __new_control_info,			\
	.get = __new_control_get,			\
	.put = __new_control_put,			\
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,	\
}

/*
 *----------------------------------------------------------------------------
 * Function : n_control_info
 * Purpose  : This function is to initialize data for new control required to
 *            program the AIC3110 registers.
 *
 *----------------------------------------------------------------------------
 */
#if 0
static unsigned int n_control_info(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_info *uinfo)
{
	struct soc_mixer_control *mc =
		(struct soc_mixer_control *)kcontrol->private_value;
	int max = mc->max;
	unsigned int shift = mc->shift;
	unsigned int rshift = mc->rshift;

	DBG("### %s\n", __func__);

	if (max == 1)
		uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	else
		uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;

	uinfo->count = shift == rshift ? 1 : 2;
	uinfo->value.integer.min = 0;
	uinfo->value.integer.max = max;
	return 0;
}
#endif

/*
 *----------------------------------------------------------------------------
 * Function : n_control_get
 * Purpose  : This function is to read data of new control for
 *            program the AIC3110 registers.
 *
 *----------------------------------------------------------------------------
 */
#if 0
static unsigned int n_control_get(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_codec *codec = snd_kcontrol_chip(kcontrol);
	u32 val, reg;
	unsigned short mask, shift;
	struct soc_mixer_control *mc =
		(struct soc_mixer_control *)kcontrol->private_value;

	DBG("### %s\n", __func__);

	reg = mc->reg;
	if (!strcmp(kcontrol->id.name, "ADC COARSE GAIN")) {
		mask = 0xFF;
		shift = 0;
		val = aic31xx_read(codec, reg);
		ucontrol->value.integer.value[0] =
			(val >= 40) ? (val - 40) : (val);
	}

	return 0;
}
#endif

/*
 *----------------------------------------------------------------------------
 * Function : __new_control_put
 * Purpose  : new_control_put is called to pass data from user/application to
 *            the driver.
 *
 *----------------------------------------------------------------------------
 */
#if 0
static unsigned int n_control_put(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_codec *codec = snd_kcontrol_chip(kcontrol);
	struct soc_mixer_control *mc =
		(struct soc_mixer_control *)kcontrol->private_value;
	u8 val, val_mask;
	int reg, err;
	unsigned int invert = mc->invert;
	int max = mc->max;

	DBG("### %s\n", __func__);

	reg = mc->reg;
	val = ucontrol->value.integer.value[0];
	if (invert)
		val = max - val;
	if (!strcmp(kcontrol->id.name, "ADC COARSE GAIN")) {
		val = (val >= 0) ? (val + 40) : (40);
		val_mask = 0xFF;
	}

	err = snd_soc_update_bits_locked(codec, reg, val_mask, val);
	if (err < 0) {
		pr_err("%s : Error while updating bits\n", AUDIO_NAME);
		return err;
	}


	return 0;
}
#endif

/*
 *--------------------------------------------------------------------------
 * aic31xx_hp_power_up
 * This function is used to power up the Headset Driver.
 *--------------------------------------------------------------------------
*/
static int aic31xx_hp_power_up(struct snd_soc_codec *codec)
{
	struct aic31xx_priv *aic31xx = snd_soc_codec_get_drvdata(codec);
	u8 value;
	int counter;

	DBG("### %s\n", __func__);

	if (!aic31xx->i2c_regs_status) {
		aic31xx_write(codec, HP_POP_CTRL,
				(HP_POWER_UP_1_2_SEC | HP_DRIVER_3_9_MS));

		aic31xx->i2c_regs_status = 1;
	}

	/* Switch off the Speaker Driver since the Playback is on Headphone */
	aic31xx_write(codec, CLASSD_SPEAKER_AMP, SPK_DRV_OFF);

	/* Switch ON Left and Right Headphone Drivers. Switching them before
	 * Headphone Volume ramp helps in reducing the pop sounds.  */
	value = aic31xx_read(codec, HEADPHONE_DRIVER);
	aic31xx_write(codec, HEADPHONE_DRIVER, (value | 0xC0));

	/* Check for the DAC FLAG Register to know if the HP
	   Driver is powered up */
	counter = 0;
	do {
		mdelay(5);
		value = aic31xx_read(codec, DAC_FLAG_1);
		counter++;
	} while ((value & 0x22) == 0);

	return 0;
}

/*
 *--------------------------------------------------------------------------
 * aic31xx_hp_power_down
 * This function is used to power down the Headset Driver.
 *--------------------------------------------------------------------------
*/
static int aic31xx_hp_power_down(struct snd_soc_codec *codec)
{
	u8 value;
	int counter;
	struct aic31xx_priv *aic31xx = snd_soc_codec_get_drvdata(codec);

	DBG("### %s\n", __func__);

	if (ctrl_data.power_ctrl == false) {
		/* Always power up */
		DBG("#### Always power up\n");
		return 0;
	}

	/* MUTE the Headphone Left and Right */
	value = aic31xx_read(codec, HPL_DRIVER);
	aic31xx_write(codec, HPL_DRIVER, (value & ~HP_UNMUTE));

	value = aic31xx_read(codec, HPR_DRIVER);
	aic31xx_write(codec, HPR_DRIVER, (value & ~HP_UNMUTE));

	/* Switch off the Head phone Drivers */
	value = aic31xx_read(codec, HEADPHONE_DRIVER);
	aic31xx_write(codec, HEADPHONE_DRIVER, (value & ~0xC0));

	/* Now first check if the HP Driver is fully powered down */
	counter = 0;
	do {
		mdelay(1);
		value = aic31xx_read(codec, DAC_FLAG_1);
		counter++;
	} while ((counter < 200) && ((value & 0x22) != 0));

	/* Configure the i2c_regs_status to zero once again */
	aic31xx->i2c_regs_status = 0;

	return 0;
}

/*
 * Global Var aic31xx_reg
 *
 * Used to maintain a cache of Page 0 and 1 Register values.
 */
#if defined(AIC3110_CODEC_SUPPORT)
static const u8 aic31xx_reg[AIC31xx_CACHEREGNUM] = {
	/* Page 0 Registers */
	0x00,
	0x00, 0x12, 0x00, 0x00, 0x11, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01,
	0x01, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x01, 0x80, 0x00, 0x00,
	0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0x55,
	0x55, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x14, 0x0c, 0x00, 0x00,
	0x00, 0x6f, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0xee, 0x10, 0xd8,
	0x7e, 0xe3, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x10, 0x32, 0x54, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x12, 0x02,
	/* Page 1 Registers */
	0x01, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

#elif defined(AIC3100_CODEC_SUPPORT)
static const u8 aic31xx_reg[AIC31XX_CACHEREGNUM] = { /* Page 0
							HPL_DRIVER  Registers */
	0x00, 0x00, 0x12, 0x00, 0x00, 0x11, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01,
	0x01, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x01, 0x80, 0x00, 0x00,
	0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0x55,
	0x55, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x14, 0x0c, 0x00, 0x00,
	0x00, 0x6f, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0xee, 0x10, 0xd8,
	0x7e, 0xe3, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x10, 0x32, 0x54, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x12, 0x02,
	/* Page 1 Registers */
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

#endif

/*
 * aic31xx_change_page
 *
 * This function is to switch between page 0 and page 1.
 */
static int aic31xx_change_page(struct snd_soc_codec *codec, u8 new_page)
{
	struct aic31xx_priv *aic31xx = snd_soc_codec_get_drvdata(codec);
	u8 data[2];

	if (aic31xx == NULL) {
		DBG("%s : Codec Private member NULL..\n", __func__);
		return 0;
	}

	data[0] = 0;
	data[1] = new_page;

	if (codec->hw_write(codec->control_data, data, 2) != 2) {
		pr_err("%s : Error in changing page to 1\n", AUDIO_NAME);
		return -1;
	}
	aic31xx->page_no = new_page;
	return 0;
}

/*
 * aic31xx_write_reg_cache
 * This function is to write aic31xx register cache
 */
static void aic31xx_write_reg_cache(struct snd_soc_codec
		*codec, u16 reg, u8 value)
{
	u8 *cache = codec->reg_cache;

	if (reg >= AIC31xx_CACHEREGNUM)
		return;
	cache[reg] = value;
}

/*
 * aic31xx_write
 *
 * This function is to write to the aic31xx register space.
 */
static int aic31xx_write(struct snd_soc_codec *codec, unsigned int reg,
		unsigned int value)
{
	struct aic31xx_priv *aic31xx = snd_soc_codec_get_drvdata(codec);
	u8 data[2];
	u8 page;

	page = reg / 128;
	data[AIC31XX_REG_OFFSET_INDEX] = reg % 128;

	if (aic31xx->page_no != page)
		aic31xx_change_page(codec, page);


	/* data is * D15..D8 aic31xx register offset * D7...D0
	 * register data
	 */
	data[AIC31XX_REG_DATA_INDEX] = value & AIC31XX_8BITS_MASK;

#if defined(EN_REG_CACHE)
	if ((page == 0) || (page == 1) || (page == 2))
		aic31xx_write_reg_cache(codec, reg, value);
#endif
	if (codec->hw_write(codec->control_data, data, 2) != 2) {
		DBG("%s : Error in i2c write\n", AUDIO_NAME);
		return -EIO;
	}

#if 0
	DBG("%s : page=%d, a=%02X(%d), v=%02X(%d)\n", __func__,
		page,
		data[AIC31XX_REG_OFFSET_INDEX], data[AIC31XX_REG_OFFSET_INDEX],
		data[AIC31XX_REG_DATA_INDEX], data[AIC31XX_REG_DATA_INDEX]);
#endif

#if 0
	if (reg == HPL_DRIVER || reg == HPR_DRIVER ||
	    reg == SPL_DRIVER || reg == SPR_DRIVER) {

		pr_info("%s : page=%d, a=%02X(%d), v=%02X(%d)\n", __func__,
			page,
			data[AIC31XX_REG_OFFSET_INDEX], data[AIC31XX_REG_OFFSET_INDEX],
			data[AIC31XX_REG_DATA_INDEX], data[AIC31XX_REG_DATA_INDEX]);
	}
#endif
	return 0;
}

/*
 * aic31xx_read
 *
 * This function is to read the aic31xx register space.
 */
static unsigned int aic31xx_read(struct snd_soc_codec *codec, unsigned int reg)
{
	struct aic31xx_priv *aic31xx = snd_soc_codec_get_drvdata(codec);
	u8 value;
	u8 page = reg / 128;
	unsigned int req_reg;

	req_reg = reg % 128;
	if (aic31xx->page_no != page)
		aic31xx_change_page(codec, page);

	i2c_master_send(codec->control_data, (char *)&req_reg, 1);
	i2c_master_recv(codec->control_data, &value, 1);

#if 0
	DBG("%s : page=%d, a=%02X(%d), v=%02X(%d)\n", __func__,
		page, reg, reg, value, value);
#endif

#if 0
	if (reg == HPL_DRIVER || reg == HPR_DRIVER ||
	    reg == SPL_DRIVER || reg == SPR_DRIVER) {
		pr_info("%s : page=%d, a=%02X(%d), v=%02X(%d)\n", __func__,
			page, reg, reg, value, value);
	}
#endif
	return value;
}


/*
 *----------------------------------------------------------------------------
 * Function : debug_print_registers
 * Purpose  : Debug routine to dump all the Registers of Page 0
 *
 *----------------------------------------------------------------------------
 */
#if 0
static void debug_print_registers(struct snd_soc_codec *codec)
{
	int i;
	u8 data;

	DBG("### Page 0 Regs from 0 to 117 ###\n");
	for (i = 0; i < 117; i++) {
		data = (u8) aic31xx_read(codec, i);
		DBG("reg = 0x%02x(%d) val = 0x%02x\n", i, i, data);
	}
	DBG("### Page 1 Regs from 30 to 57 ###\n");

	for (i = 158; i < 185; i++) {
		data = (u8) aic31xx_read(codec, i);
		DBG("reg = 0x%02x(%d) val = 0x%02x\n", (i%128), (i%128), data);
	}


	DBG("### SPL_DRIVER_GAIN %d SPR_DRIVER_GAIN %d\n",
			aic31xx_read(codec, SPL_DRIVER),
			aic31xx_read(codec, SPR_DRIVER));

	DBG("### L_ANALOG_VOL_2_SPL %d R_ANLOG_VOL_2_SPR %d\n",
			aic31xx_read(codec, L_ANLOG_VOL_2_SPL),
			aic31xx_read(codec, R_ANLOG_VOL_2_SPR));

	DBG("### LDAC_VOL %d RDAC_VOL %d\n",
			aic31xx_read(codec, LDAC_VOL),
			aic31xx_read(codec, RDAC_VOL));
	DBG("### OVER Temperature STATUS (Page 0 Reg 3) %x\n",
			aic31xx_read(codec, OT_FLAG));
	DBG("### SHORT CIRCUIT STATUS (Page 0 Reg 44) %x\n",
			aic31xx_read(codec, SHORT_CKT_FLAG));

	DBG("### INTR_FLAG: SHORT_CKT(Page 0 Reg 46) %x\n",
			aic31xx_read(codec, DAC_INTR_STATUS));
	DBG("### Speaker_Driver_Short_Circuit (Page 1 Reg 32)%x\n",
			aic31xx_read(codec, CLASSD_SPEAKER_AMP));

	DBG("### MIC_PGA (P1 R47) = 0x%x\n",
			aic31xx_read(codec, MIC_PGA));

	DBG("### ADC_FGA (P0 R82) = 0x%x\n",
			aic31xx_read(codec, ADC_FGA));

	DBG("### ADC_CGA (P0 R83) = 0x%x\n",
			aic31xx_read(codec, ADC_CGA));
}
#endif

/*
 * __new_control_info
 *
 * This function is to initialize data for new control required to * program the
 * AIC31xx registers.
 */
static int __new_control_info(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_info *uinfo)
{
	DBG("### %s\n", __func__);
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.integer.min = 0;
	uinfo->value.integer.max = 65535;

	return 0;
}

/*
 * __new_control_get
 *
 * This function is to read data of new control for program the AIC31xx
 * registers.
 */
static int __new_control_get(struct snd_kcontrol *kcontrol,
			struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_codec *codec = snd_kcontrol_chip(kcontrol);
	u32 val;

	DBG("### %s\n", __func__);

	val = aic31xx_read(codec, aic31xx_reg_ctl);
	ucontrol->value.integer.value[0] = val;

	return 0;
}

/*
 * __new_control_put
 *
 * __new_control_put is called to pass data from user/application to the
 * driver.
 */
static int __new_control_put(struct snd_kcontrol *kcontrol,
			struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_codec *codec = snd_kcontrol_chip(kcontrol);
	struct aic31xx_priv *aic31xx = snd_soc_codec_get_drvdata(codec);

	u32 data_from_user = ucontrol->value.integer.value[0];
	u8 data[2];

	DBG("### %s\n", __func__);

	aic31xx_reg_ctl = data[0] = (u8) ((data_from_user & 0xFF00) >> 8);
	data[1] = (u8) ((data_from_user & 0x00FF));

	if (!data[0])
		aic31xx->page_no = data[1];

	DBG("%s : reg = %d val = %x\n", __func__, data[0], data[1]);

	if (codec->hw_write(codec->control_data, data, 2) != 2) {
		pr_err("%s : Error in i2c write\n", AUDIO_NAME);
		return -EIO;
	}

	return 0;
}

/*
 *----------------------------------------------------------------------------
 * Function : aic31xx_power_up
 * Purpose  : This function powers up the codec.
 *
 *----------------------------------------------------------------------------
 */
static int aic31xx_power_up(struct snd_soc_codec *codec)
{
	struct aic31xx_priv *aic31xx = snd_soc_codec_get_drvdata(codec);
	u8 value;
	u32 counter;

	DBG("### %s\n", __func__);

	mutex_lock(&aic31xx->mutex_codec);

	if (aic31xx->master) {  /* Switch on PLL */
		value = aic31xx_read(codec, CLK_REG_2);
		aic31xx_write(codec, CLK_REG_2, (value | ENABLE_PLL));

		/* Switch on NDAC Divider */
		value = aic31xx_read(codec, NDAC_CLK_REG);
		aic31xx_write(codec, NDAC_CLK_REG, value | ENABLE_NDAC);

		/* Switch on MDAC Divider */
		value = aic31xx_read(codec, MDAC_CLK_REG);
		aic31xx_write(codec, MDAC_CLK_REG, value | ENABLE_MDAC);

		/* Switch on NADC Divider */
		value = aic31xx_read(codec, NADC_CLK_REG);
		aic31xx_write(codec, NADC_CLK_REG, value | ENABLE_MDAC);

		/* Switch on MADC Divider */
		value = aic31xx_read(codec, MADC_CLK_REG);
		aic31xx_write(codec, MADC_CLK_REG, value | ENABLE_MDAC);

		/* Switch on BCLK_N Divider */
		value = aic31xx_read(codec, BCLK_N_VAL);
		aic31xx_write(codec, BCLK_N_VAL, value | ENABLE_BCLK);
	} else {	/* Switch on PLL */
		value = aic31xx_read(codec, CLK_REG_2);
		aic31xx_write(codec, CLK_REG_2, (value | ENABLE_PLL));

		/* Switch on NDAC Divider */
		value = aic31xx_read(codec, NDAC_CLK_REG);
		aic31xx_write(codec, NDAC_CLK_REG, value | ENABLE_NDAC);

		/* Switch on MDAC Divider */
		value = aic31xx_read(codec, MDAC_CLK_REG);
		aic31xx_write(codec, MDAC_CLK_REG, value | ENABLE_MDAC);

		/* Switch on NADC Divider */
		value = aic31xx_read(codec, NADC_CLK_REG);
		aic31xx_write(codec, NADC_CLK_REG, value | ENABLE_MDAC);

		/* Switch on MADC Divider */
		value = aic31xx_read(codec, MADC_CLK_REG);
		aic31xx_write(codec, MADC_CLK_REG, value | ENABLE_MDAC);

		/* Switch on BCLK_N Divider */
		value = aic31xx_read(codec, BCLK_N_VAL);
		aic31xx_write(codec, BCLK_N_VAL, value | ENABLE_BCLK);
	}

	/* We are directly handling the Codec Power up.  */
	if (aic31xx->playback_stream && !aic31xx->power_status[SNDRV_PCM_STREAM_PLAYBACK]) {
		DBG("#### Power Up for Playback\n");
		/* Put the DAC volume and Headphone volume to
		 * lowest levels first
		 *
		aic31xx_write(codec, LDAC_VOL, DAC_DEFAULT_VOL);
		aic31xx_write(codec, RDAC_VOL, DAC_DEFAULT_VOL);
		mdelay (5);

		aic31xx_write(codec, L_ANLOG_VOL_2_HPL, HP_DEFAULT_VOL);
		aic31xx_write(codec, R_ANLOG_VOL_2_HPR, HP_DEFAULT_VOL);
		*/

		/* Switch ON Left and Right DACs */
		value = aic31xx_read(codec, DAC_CHN_REG);
		aic31xx_write(codec, DAC_CHN_REG, (value | ENABLE_DAC_CHN));

		/* Check for the DAC FLAG register to know if the DAC is
		 * really powered up
		 */
		counter = 0;
		do {
			mdelay(1);
			value = aic31xx_read(codec, DAC_FLAG_1);
			counter++;
		} while ((counter < 20) && ((value & 0x88) == 0));
		DBG("%s : Left and Right DAC on Counter %d\n",
				__func__, counter);

		/* Check whether the Headset or Speaker Drive
		    needs Power Up */
		if (aic31xx->headset_connected) {
			/* Switch off the Speaker Driver since the
			   Playback is on Headphone */
			aic31xx_write(codec, CLASSD_SPEAKER_AMP,
							SPK_DRV_OFF);

			if (!aic31xx->i2c_regs_status)
				aic31xx_hp_power_up(codec);
			else
				aic31xx_write(codec, HP_POP_CTRL,
						(HP_POWER_UP_1_2_SEC \
						| HP_DRIVER_3_9_MS));
		} else {
			/* Forcing the ANALOG volume to speaker driver
			   to 0 dB */
			aic31xx_write(codec, L_ANLOG_VOL_2_SPL, 0x80);
			aic31xx_write(codec, R_ANLOG_VOL_2_SPR, 0x80);

			/* Switch ON the Class_D Speaker Amplifier */
			value = aic31xx_read(codec, CLASSD_SPEAKER_AMP);
			aic31xx_write(codec, CLASSD_SPEAKER_AMP,
					(value | SPK_DRV_ON));
			counter = 0;
			do {
				mdelay(1);
				value = aic31xx_read(codec, DAC_FLAG_1);
				counter++;
			} while ((value & 0x11) == 0);
			DBG("%s : SPK Power up Iterations %d\n",
							__func__, counter);
		}
		aic31xx->power_status[SNDRV_PCM_STREAM_PLAYBACK] = 1;
	}

	if (aic31xx->record_stream && !aic31xx->power_status[SNDRV_PCM_STREAM_CAPTURE]) {
		DBG("#### Power Up for Capture\n");
		/* ADC Channel Power Up */
		value = aic31xx_read(codec, ADC_DIG_MIC);
		aic31xx_write(codec, ADC_DIG_MIC, (value | 0x80));

		/* Check for the ADC FLAG register to know if the ADC is
		 * really powered up
		 */
		counter = 0;
		do {
			mdelay(10);
			value = aic31xx_read(codec, ADC_FLAG);
			counter++;
		} while ((counter < 40) && ((value & 0x40) == 0));
		DBG("%s : ADC Channel Power up Iterations %d\n",
				__func__, counter);

		/* Power Up control of MICBIAS */
		value = aic31xx_read(codec, MICBIAS_CTRL);
		aic31xx_write(codec, MICBIAS_CTRL, (value | (BIT1 | BIT0)));
		aic31xx->power_status[SNDRV_PCM_STREAM_CAPTURE] = 1;
	}

	mutex_unlock(&aic31xx->mutex_codec);
	return 0;
}

/*
 *----------------------------------------------------------------------------
 * Function : aic31xx_power_down
 * Purpose  : This function powers down the codec.
 *
 *----------------------------------------------------------------------------
 */
static int aic31xx_power_down(struct snd_soc_codec *codec)
{
	struct aic31xx_priv *aic31xx = snd_soc_codec_get_drvdata(codec);
	u8 value;
	u32 counter;

	DBG("### %s\n", __func__);
	if (ctrl_data.power_ctrl == false) {
		/* Always power up */
		DBG("#### Always power up\n");
		return 0;
	}

	mutex_lock(&aic31xx->mutex_codec);

	/* Speaker Driver Power Down */
	/* Switch OFF the Class_D Speaker Amplifier */
	value = aic31xx_read(codec, CLASSD_SPEAKER_AMP);
	aic31xx_write(codec, CLASSD_SPEAKER_AMP, (value & ~0xC0));

	/* Left and Right Speaker Analog Volume is muted */
	aic31xx_write(codec, L_ANLOG_VOL_2_SPL, SPK_DEFAULT_VOL);
	aic31xx_write(codec, R_ANLOG_VOL_2_SPR, SPK_DEFAULT_VOL);

	/* Switch OFF Left and Right DACs */
	value = aic31xx_read(codec, DAC_CHN_REG);
	aic31xx_write(codec, DAC_CHN_REG, (value & ~ENABLE_DAC_CHN));

	/* Check for the DAC FLAG register to know if the DAC is really
	 * powered down
	 */
	counter = 0;
	do {
		mdelay(5);
		value = aic31xx_read(codec, DAC_FLAG_1);
		counter++;
	} while ((counter < 100) && ((value & 0x88) != 0));
	DBG("%s : Left and Right DAC off Counter %d\n", __func__, counter);

	/* ADC Channel Power down */
	value = aic31xx_read(codec, ADC_DIG_MIC);
	aic31xx_write(codec, ADC_DIG_MIC, (value & ~BIT7));

	/* Check for the ADC FLAG register to know if the ADC is
	 * really powered down
	 */
	counter = 0;
	do {
		mdelay(5);
		value = aic31xx_read(codec, ADC_FLAG);
		counter++;
	} while ((counter < 50) && ((value & 0x40) != 0));
	DBG("%s : Left and Right ADC off Counter %d\n", __func__, counter);

	/* Power down control of MICBIAS */
	value = aic31xx_read(codec, MICBIAS_CTRL);
	aic31xx_write(codec, MICBIAS_CTRL, (value & ~(BIT1 | BIT0)));

	if (ctrl_data.mute_ctrl == true)
		aic31xx->mute[SNDRV_PCM_STREAM_CAPTURE] = 1;

	aic31xx->power_status[SNDRV_PCM_STREAM_PLAYBACK] = 0;
	aic31xx->power_status[SNDRV_PCM_STREAM_CAPTURE] = 0;

	if (aic31xx->master) {
		/* Switch off PLL */
		value = aic31xx_read(codec, CLK_REG_2);
		aic31xx_write(codec, CLK_REG_2, (value & ~ENABLE_PLL));

		/* Switch off NDAC Divider */
		value = aic31xx_read(codec, NDAC_CLK_REG);
		aic31xx_write(codec, NDAC_CLK_REG, value & ~ENABLE_NDAC);

		/* Switch off MDAC Divider */
		value = aic31xx_read(codec, MDAC_CLK_REG);
		aic31xx_write(codec, MDAC_CLK_REG, value & ~ENABLE_MDAC);

		/* Switch off NADC Divider */
		value = aic31xx_read(codec, NADC_CLK_REG);
		aic31xx_write(codec, NADC_CLK_REG, value & ~ENABLE_NDAC);

		/* Switch off MADC Divider */
		value = aic31xx_read(codec, MADC_CLK_REG);
		aic31xx_write(codec, MADC_CLK_REG, value & ~ENABLE_MDAC);
		value = aic31xx_read(codec, BCLK_N_VAL);

		/* Switch off BCLK_N Divider */
		aic31xx_write(codec, BCLK_N_VAL, value & ~ENABLE_BCLK);
	}

	mutex_unlock(&aic31xx->mutex_codec);
	return 0;
}

/*
 *----------------------------------------------------------------------------
 * Function : aic31xx_mic_check
 * Purpose  : This function checks for the status of the Page0 Register 67
 *            [Headset Detect] Register and checks if Bit6 is set. This denotes
 *            that a Jack with Microphone is plugged in or not.
 *
 * Returns  : 1 is the Bit 6 of Pg 0 Reg 67 is set
 *            0 is the Bit 6 of Pg 0 Reg 67 is not set.
 *----------------------------------------------------------------------------
 */
int aic31xx_mic_check(struct snd_soc_codec *codec)
{
	struct aic31xx_priv *aic31xx = snd_soc_codec_get_drvdata(codec);

	u8 mic_status = 0, value;
	u8 regval;
	int count;

	DBG("### %s\n", __func__);

	count = 0;
	do {
		/* Read the Register contents */
		regval = aic31xx_read(codec, HEADSET_DETECT);

		/*
		 * Disabling and enabling the headset detection functionality
		 * to avoid false detection of microphone
		 */
		aic31xx_write(codec, HEADSET_DETECT, regval & ~BIT7);
		mdelay(10);
		regval = aic31xx_read(codec, HEADSET_DETECT);
		value = aic31xx_read(codec, MICBIAS_CTRL);
		aic31xx_write(codec, MICBIAS_CTRL, (value | (BIT1 | BIT0)));

		aic31xx_write(codec, HEADSET_DETECT, regval | BIT7);
		/*
		 * Delay configured with respect to the Debounce time. If headset
		 * debounce time is changing, it should reflect in the delay in the
		 * below line.
		 */
		mdelay(64);
		regval = aic31xx_read(codec, HEADSET_DETECT);
		aic31xx_write(codec, HEADSET_DETECT, regval & ~BIT7);

		value = aic31xx_read(codec, MICBIAS_CTRL);
		aic31xx_write(codec, MICBIAS_CTRL, (value & ~(BIT1 | BIT0)));
		count++;
	} while (!(regval&BIT6) && (count < 10));

	aic31xx->headset_current_status = regval;

	mic_status = (regval & BIT6);
	return mic_status;
}

#ifdef AIC31xx_JACK
void aic31xx_hs_jack_report(struct snd_soc_codec *codec,
			    struct snd_soc_jack *jack, int report)
{
	struct aic31xx_jack_data *hs_jack = &aic_priv->hs_jack;

	DBG("### %s\n", __func__);

	if (&hs_jack->sdev != NULL)
		switch_set_state(&hs_jack->sdev, report);
}

void aic31xx_hs_jack_detect(struct snd_soc_codec *codec,
				struct snd_soc_jack *jack, int report)
{
	struct aic31xx_jack_data *hs_jack = &aic_priv->hs_jack;

	DBG("### %s\n", __func__);

	hs_jack->jack = jack;
	hs_jack->report = report;
}
#endif

/*
 * aic31xx_set_bias_level
 *
 * This function is to get triggered when dapm events occurs.
 */
static int aic31xx_set_bias_level(struct snd_soc_codec *codec,
		enum snd_soc_bias_level level)
{
	DBG("### %s: level %d\n", __func__, level);

	if (level == codec->dapm.bias_level) {
		DBG("%s :Current & previous levels same\n", __func__);
		return 0;
	}

	DBG("%s : New Level %d\n", __func__, level);

	switch (level) {
	/* full On */
	case SND_SOC_BIAS_ON:
		DBG("%s : BIAS_ON\n", __func__);
		aic31xx_power_up(codec);
		break;

	/* partial On */
	case SND_SOC_BIAS_PREPARE:
		DBG("%s : BIAS_PREPARE\n", __func__);
		break;

	/* Off, with power */
	case SND_SOC_BIAS_STANDBY:
		DBG("%s : BIAS_STANDBY\n", __func__);
		aic31xx_power_down(codec);
		break;

	/* Off, without power */
	case SND_SOC_BIAS_OFF:
		DBG("%s : BIAS_OFF\n", __func__);
		aic31xx_hp_power_down(codec);
		aic31xx_power_down(codec);
		break;
	}
	codec->dapm.bias_level = level;

	return 0;
}


/* The updated aic31xx_divs Array for the KCI board having 19.2 Mhz
 * Master Clock Input coming from the FSREF2_CLK pin of OMAP4
 */
static const struct aic31xx_rate_divs aic31xx_divs[] = {
	/* mclk,   rate,  p, j, d,    dosr, ndac, mdac, aosr, nadc, madc, adc_clk */
	/* mclk=11.2896MHz */
	/* 11.025k rate */
	{11289600, 11025, 1, 8,    0, 128,  32,   2,    128,  32,   2,    2822400},
	/* 22.05k rate */
	{11289600, 22050, 1, 8,    0, 128,  16,   2,    128,  16,   2,    5644800},
	/* 29.4k rate */
	{11289600, 29400, 1, 8,    0, 128,  12,   2,    128,  12,   2,    7526400},
	/* 44.1k rate */
	{11289600, 44100, 1, 8,    0, 128,  12,   2,    128,   8,   2,   11289600},
	/* 58.8k rate */
	{11289600, 58800, 1, 8,    0,  64,   8,   4,     64,   6,   4,   15052800},
	/* 88.2k rate */
	{11289600, 88200, 1, 8,    0,  64,   6,   4,     64,   4,   4,   22579200},
	/* mclk=12.288MHz */
	/* 12k rate */
	{12288000, 12000, 1, 8,    0, 128,  32,   2,    128,  32,   2,    3072000},
	/* 24k rate */
	{12288000, 24000, 1, 8,    0, 128,  16,   2,    128,  16,   2,    6144000},
	/* 32k rate */
	{12288000, 32000, 1, 8,    0, 128,  12,   2,    128,  12,   2,    8192000},
	/* 48k rate */
	{12288000, 48000, 1, 8,    0,  64,   8,   4,     64,   8,   4,   12288000},
	/* 64k rate */
	{12288000, 64000, 1, 8,    0,  64,   6,   4,     64,   6,   4,   16384000},
	/* 96k rate */
	{12288000, 96000, 1, 8,    0,  64,   4,   4,     64,   4,   4,   24576000},
	/* mclk=18.432MHz */
	/* 18k rate */
	{18432000, 18000, 1, 5,    0, 128,  20,   2,    128,  20,   2,    4608000},
	/* 36k rate */
	{18432000, 36000, 1, 5,    0, 128,  10,   2,    128,  10,   2,    9216000},
	/* 48k rate */
	{18432000, 48000, 1, 5,    0, 128,   5,   3,    128,   5,   3,   18432000},
	/* 72k rate */
	{18432000, 72000, 1, 5,    0,  64,   5,   4,     64,   5,   4,   18432000},
	/* 96k rate */
	{18432000, 96000, 1, 5,    0,  64,   5,   3,     64,   5,   3,   18432000},
	/* mclk=24.576MHz */
	/* 24k rate */
	{24576000, 24000, 2, 8,    0, 128,  32,   2,    128,  32,   2,   6144000},
	/* 48k rate */
	{24576000, 48000, 2, 8,    0, 128,  16,   2,    128,  16,   2,  12288000},
	/* 64k rate */
	{24576000, 64000, 2, 8,    0, 128,  12,   2,    128,  12,   2,  16384000},
	/* 96k rate */
	{24576000, 96000, 2, 8,    0,  64,   8,   4,     64,   8,   4,  24576000},
	/* 192k rate */
	{24576000, 192000, 2, 8,    0,  32,   2,   8,     32,   2,   8,  49152000},
};


/*
 * aic31xx_get_divs
 *
 * This function is to get required divisor from the "aic31xx_divs" table.
 */
static inline int aic31xx_get_divs(int mclk, int rate)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(aic31xx_divs); i++) {
		if ((aic31xx_divs[i].rate == rate) &&
				(aic31xx_divs[i].mclk == mclk)) {
			return i;
		}
	}
	pr_err("%s : Master clock and sample rate is not supported\n",
		AUDIO_NAME);
	return -EINVAL;
}

static u32 aic31xx_rates[] = {
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
	96000,
	192000
};
static struct snd_pcm_hw_constraint_list aic31xx_constraints = {
	.count  = ARRAY_SIZE(aic31xx_rates),
	.list   = aic31xx_rates,
};


/**
 * aic31xx_startup
 *
 * This function is start up for AIC31xx.
 */
static int aic31xx_startup(struct snd_pcm_substream *substream,
		struct snd_soc_dai *dai)
{
	DBG("### %s\n", __func__);

	snd_pcm_hw_constraint_list(substream->runtime, 0,
			SNDRV_PCM_HW_PARAM_RATE,
			&aic31xx_constraints);
	return 0;
}


/**
 * aic31xx_hw_params
 *
 * This function is to set the hardware parameters for AIC31xx.
 * The functions set the sample rate and audio serial data word length.
 */
static int aic31xx_hw_params(struct snd_pcm_substream *substream,
		struct snd_pcm_hw_params *params,
		struct snd_soc_dai *dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_codec *codec = rtd->codec;
	struct aic31xx_priv *aic31xx = snd_soc_codec_get_drvdata(codec);
	int i;
	u8 data;
	int width = 16;
	u8 bdiv;

	DBG("### %s : aic31xx_hw_params SyCLK %x MUTE %d,%d PowerStatus %d,%d\n",
		__func__,
		aic31xx->sysclk, aic31xx->mute[SNDRV_PCM_STREAM_PLAYBACK], aic31xx->mute[SNDRV_PCM_STREAM_CAPTURE], aic31xx->power_status[SNDRV_PCM_STREAM_PLAYBACK], aic31xx->power_status[SNDRV_PCM_STREAM_CAPTURE]);


	if (substream->stream != SNDRV_PCM_STREAM_PLAYBACK) {
		if (aic31xx->headset_connected) {
			if (aic31xx_mic_check(codec))
				DBG("%s : Headset with MIC Detected. Recording possible.\n", AUDIO_NAME);
			else {
				pr_err("%s : Headset without MIC Inserted. Recording not possible...\n", AUDIO_NAME);
				return -ENODEV;
			}
		}
	}

	/* Setting the playback status */
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		aic31xx->playback_stream = 1;
	else if ((substream->stream != SNDRV_PCM_STREAM_PLAYBACK) && \
							(codec->active < 2))
		aic31xx->playback_stream = 0;

	if (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		aic31xx->record_stream = 1;
	else if ((substream->stream != SNDRV_PCM_STREAM_CAPTURE)  && \
							(codec->active < 2))
		aic31xx->record_stream = 0;

	DBG("%s : playback_stream= %d capture_stream=%d priv_playback_stream= %d priv_record_stream=%d\n",
		AUDIO_NAME,
		SNDRV_PCM_STREAM_PLAYBACK, SNDRV_PCM_STREAM_CAPTURE,
		aic31xx->playback_stream, aic31xx->record_stream);

	codec->dapm.bias_level = 2;

	mutex_lock(&aic31xx->mutex_codec);

	i = aic31xx_get_divs(aic31xx->sysclk, params_rate(params));

	if (i < 0) {
		pr_err("%s : sampling rate not supported\n", AUDIO_NAME);
		mutex_unlock(&aic31xx->mutex_codec);
		return i;
	}

	DBG("%s : Sampling Rate %d\n", __func__, params_rate(params));

	/* We will fix R value to 1 and will make P & J=K.D as
	 * variable  Setting P & R values
	 */

	if (codec->active < 2) {

		snd_soc_update_bits(codec, CLK_REG_2, 0x7F, \
					((aic31xx_divs[i].p_val << 4) | 0x01));

		/* J value */
		snd_soc_update_bits(codec, CLK_REG_3, 0x7F, \
						aic31xx_divs[i].pll_j);

		/* MSB & LSB for D value */
		aic31xx_write(codec, CLK_REG_4, (aic31xx_divs[i].pll_d >> 8));
		aic31xx_write(codec, CLK_REG_5, (aic31xx_divs[i].pll_d & \
					AIC31XX_8BITS_MASK));

		/* NDAC divider value */
		snd_soc_update_bits(codec, NDAC_CLK_REG, 0x7F, \
						aic31xx_divs[i].ndac);

		/* MDAC divider value */
		snd_soc_update_bits(codec, MDAC_CLK_REG , 0x7F, \
						aic31xx_divs[i].mdac);

		/* DOSR MSB & LSB values */
		aic31xx_write(codec, DAC_OSR_MSB, aic31xx_divs[i].dosr >> 8);
		aic31xx_write(codec, DAC_OSR_LSB, \
				aic31xx_divs[i].dosr & AIC31XX_8BITS_MASK);

		/* NADC divider value */
		snd_soc_update_bits(codec, NADC_CLK_REG, 0x7F, \
						aic31xx_divs[i].nadc);

		/* MADC divider value */
		snd_soc_update_bits(codec, MADC_CLK_REG, 0x7F, \
						aic31xx_divs[i].madc);

		/* AOSR value */
		aic31xx_write(codec, ADC_OSR_REG, aic31xx_divs[i].aosr);

		/* BCLK N divider */
		/*snd_soc_update_bits(codec, BCLK_N_VAL, 0x7F, \
						aic31xx_divs[i].blck_N);*/
		switch (params_format(params)) {
		case SNDRV_PCM_FORMAT_S16_LE:
			width = 16 * 2;
			break;
		default:
			width = 32 * 2;
			break;
		}
		bdiv = aic31xx_divs[i].adc_clk / (aic31xx_divs[i].rate * width);
		snd_soc_update_bits(codec, BCLK_N_VAL, 0x7F, bdiv);

		DBG("%s : Writing NDAC %d MDAC %d NADC %d MADC %d DOSR %d AOSR %d\n", __func__,
			aic31xx_divs[i].ndac, aic31xx_divs[i].mdac,
			aic31xx_divs[i].nadc, aic31xx_divs[i].madc,
			aic31xx_divs[i].dosr, aic31xx_divs[i].aosr);
	}

	data = aic31xx_read(codec, INTERFACE_SET_REG_1);

	data = data & ~(3 << 4);

	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S16_LE:
		break;
	case SNDRV_PCM_FORMAT_S20_3LE:
		data |= (AIC31XX_WORD_LEN_20BITS << DATA_LEN_SHIFT);
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
		data |= (AIC31XX_WORD_LEN_24BITS << DATA_LEN_SHIFT);
		break;
	case SNDRV_PCM_FORMAT_S32_LE:
		data |= (AIC31XX_WORD_LEN_32BITS << DATA_LEN_SHIFT);
		break;
	}

	aic31xx_write(codec, INTERFACE_SET_REG_1, data);
	mutex_unlock(&aic31xx->mutex_codec);
	return 0;
}

/*
 *----------------------------------------------------------------------------
 * Function : aic31xx_config_hp_volume
 * Purpose  : This function is used to configure the I2C Transaction Global
 *            Variables. One of them is for ramping down the HP Analog Volume
 *            and the other one is for ramping up the HP Analog Volume
 *
 *----------------------------------------------------------------------------
 */
#if 0
void aic31xx_config_hp_volume(struct snd_soc_codec *codec, int mute)
{
	struct i2c_client *client = codec->control_data;
	struct aic31xx_priv *aic31xx = snd_soc_codec_get_drvdata(codec);

	unsigned int count;
	struct aic31xx_configs  *pReg;
	signed char regval;
	unsigned char low_value;
	unsigned int  reg_update_count;

	DBG("### %s : mute %d\n", __func__, mute);

	/* User has requested to mute or bring down the Headphone Analog Volume
	 * Move from 0 db to -35.2 db
	 */
	if (mute > 0) {
		pReg = &aic31xx->hp_analog_right_vol[0];

		for (count = 0, regval = 0; regval <= 30; \
							count++, regval += 1) {

			(pReg + count)->reg_offset = R_ANLOG_VOL_2_HPR;
			(pReg + count)->reg_val = (0x80 | regval);
		}
		(pReg + (count - 1))->reg_val = (0x80 | \
				HEADPHONE_ANALOG_VOL_MIN);

		pReg = &aic31xx->hp_analog_left_vol[0];

		for (count = 0, regval = 0; regval <= 30; \
							count++, regval += 1) {

			(pReg + count)->reg_offset = L_ANLOG_VOL_2_HPL;
			(pReg + count)->reg_val = (0x80 | regval);
		}
		(pReg + (count - 1))->reg_val = (0x80 | \
				HEADPHONE_ANALOG_VOL_MIN);
		reg_update_count = count - 1;
		DBG("%s : CFG_HP_VOL count %d reg_update %d regval %d\n",
			__func__, count, reg_update_count, regval);
	} else {
		/* User has requested to unmute or bring up the Headphone Analog
		 * Volume Move from -35.2 db to 0 db
		 */
		pReg = &aic31xx->hp_analog_right_vol[0];

		low_value = HEADPHONE_ANALOG_VOL_MIN;

		for (count = 0, regval = low_value; regval >= 0;
				count++, regval -= 1) {
			(pReg + count)->reg_offset = R_ANLOG_VOL_2_HPR;
			(pReg + count)->reg_val = (0x80 | regval);
		}
		(pReg + (count - 1))->reg_val = (0x80);

		pReg = &aic31xx->hp_analog_left_vol[0];

		for (count = 0, regval = low_value; regval >= 0;
				count++, regval -= 1) {
			(pReg + count)->reg_offset = L_ANLOG_VOL_2_HPL;
			(pReg + count)->reg_val = (0x80 | regval);
		}
		(pReg + (count - 1))->reg_val = (0x80);
		reg_update_count = count;
		DBG("%s : CFG_HP_VOL LowVal 0x%x count %d reg_update %d regval %d\n", __func__, low_value, count,
				reg_update_count, regval);
	}

	/* Change to Page 1 */
	aic31xx_change_page(codec, 1);

	if (aic31xx->i2c_regs_status == 0) {
		for (count = 0; count < reg_update_count; count++) {
			i2c_right_transaction[count].addr = client->addr;
			i2c_right_transaction[count].flags =
				client->flags & I2C_M_TEN;
			i2c_right_transaction[count].len = 2;
			i2c_right_transaction[count].buf = (char *)
				&aic31xx->hp_analog_right_vol[count];
		}

		for (count = 0; count < reg_update_count; count++) {
			i2c_left_transaction[count].addr = client->addr;
			i2c_left_transaction[count].flags =
				client->flags & I2C_M_TEN;
			i2c_left_transaction[count].len = 2;
			i2c_left_transaction[count].buf = (char *)
				&aic31xx->hp_analog_left_vol[count];
		}
		aic31xx->i2c_regs_status = 1;
	}
	/* Perform bulk I2C transactions */
	if (i2c_transfer(client->adapter, i2c_right_transaction,
				reg_update_count) != reg_update_count) {
		pr_err("%s : Error while Write burst i2c data error on RIGHT_ANALOG_HPR!\n", AUDIO_NAME);
	}


	if (i2c_transfer(client->adapter, i2c_left_transaction,
				reg_update_count) != reg_update_count) {
		pr_err("%s : Error while Write burst i2c data error on LEFT_ANALOG_HPL!\n", AUDIO_NAME);
	}

	return;
}
#endif

/*
 *----------------------------------------------------------------------------
 * Function : aic31xx_mute_codec
 * Purpose  : This function is to mute or unmute the left and right DAC
 *
 *----------------------------------------------------------------------------
 */
static int aic31xx_mute_codec(struct snd_soc_codec *codec, int mute)
{
	u8 dac_reg;
	u8 value;
	int time_out_counter;
	struct aic31xx_priv *aic31xx = snd_soc_codec_get_drvdata(codec);

	DBG("### %s : mute %d\n", __func__, mute);

	mutex_lock(&aic31xx->mutex_codec);

	if (mute) {
		/* Mute */
		if (codec->active != 0) {
			if ((aic31xx->playback_stream == 1) &&
			    (aic31xx->record_stream == 1)) {
				DBG("%s : session still going on..\n",
					AUDIO_NAME);
				mutex_unlock(&aic31xx->mutex_codec);
				return 0;
			}
		}

		if (aic31xx->playback_stream && !aic31xx->mute[SNDRV_PCM_STREAM_PLAYBACK]) {
			/* Also update the global Playback Status Flag. This is required
			 * for biquad update
			 */
			if (ctrl_data.mute_ctrl == true) {
				aic31xx->playback_status = 0;

				if (aic31xx->headset_connected) {
					/* Page 47 of the datasheets requires unmuting HP and
					   Speaker drivers first */
					/* Mute the Headphone Left and Right */
					value = aic31xx_read(codec, HPL_DRIVER);
					aic31xx_write(codec, HPL_DRIVER, (value & ~HP_UNMUTE));

					value = aic31xx_read(codec, HPR_DRIVER);
					aic31xx_write(codec, HPR_DRIVER, (value & ~HP_UNMUTE));
				} else {
					/* Mute the Class-D L Speaker Driver */
					value = aic31xx_read(codec, SPL_DRIVER);
					aic31xx_write(codec, SPL_DRIVER, (value & ~BIT2));

					/* Mute the Class-D R Speaker Driver */
					value = aic31xx_read(codec, SPR_DRIVER);
					aic31xx_write(codec, SPR_DRIVER, (value & ~BIT2));
				}

				/* Mute the DAC channel */
				dac_reg = aic31xx_read(codec, DAC_MUTE_CTRL_REG);
				aic31xx_write(codec, DAC_MUTE_CTRL_REG, \
						(dac_reg | MUTE_ON));
				aic31xx->mute[SNDRV_PCM_STREAM_PLAYBACK] = 1;
				DBG("%s : DAC MUTE Completed..\n", __func__);
			}
		}

		if (aic31xx->record_stream && !aic31xx->mute[SNDRV_PCM_STREAM_CAPTURE]) {
			if (ctrl_data.mute_ctrl == true) {
				/* Mute the ADC channel */
				value = aic31xx_read(codec, ADC_FGA);
				aic31xx_write(codec, ADC_FGA, (value | BIT7));
				aic31xx->mute[SNDRV_PCM_STREAM_CAPTURE] = 1;
				DBG("%s : ADC MUTE Completed..\n", __func__);
			}
		}

	} else if (!mute) {
		/* Unmute */
		if (aic31xx->playback_stream && aic31xx->mute[SNDRV_PCM_STREAM_PLAYBACK]) {
			/* Check whether Playback or Record Session is about to Start */
			DBG("#### Unmute for Playback\n");
			aic31xx->playback_status = 1;

			/* We will enable the DAC UNMUTE first and finally the
			   Headphone UNMUTE to avoid pops */
			if (aic31xx->headset_connected) {
				/* Switch off the Speaker Driver since the
				   Playback is on Headphone */
				aic31xx_write(codec, CLASSD_SPEAKER_AMP,
							SPK_DRV_OFF);

				/* Read the contents of the Page 0 Reg 63
				   DAC Data-Path Setup Register.
				   Just retain the upper two bits and
				   lower two bits */
				value = (aic31xx_read(codec, DAC_CHN_REG) & 0xC3);
				aic31xx_write(codec, DAC_CHN_REG,
					(value | LDAC_2_LCHN | RDAC_2_RCHN));

				time_out_counter = 0;
				do {
					mdelay(5);
					value = aic31xx_read(codec, DAC_FLAG_2);
					time_out_counter++;
				} while ((time_out_counter < 100) && ((value & 0x11) == 0));

				/* Unmuting the DAC channel */
				dac_reg = aic31xx_read(codec, DAC_MUTE_CTRL_REG);
				aic31xx_write(codec, DAC_MUTE_CTRL_REG,
						(dac_reg & ~MUTE_ON));

				DBG("%s : DAC UNMUTED ...\n", __func__);

				/* Unmuting the Headphone Left and Right */
				value = aic31xx_read(codec, HPL_DRIVER);
				aic31xx_write(codec, HPL_DRIVER,
						(value | HP_UNMUTE));
				value = aic31xx_read(codec, HPR_DRIVER);
				aic31xx_write(codec, HPR_DRIVER,
						(value | HP_UNMUTE));

				DBG("%s : HPL and HPR DRIVER UNMUTED\n",
								__func__);
			} else {
				/* switch on the Speaker Driver
				   at the end of unmuting everything and
				   poll its Completion */
				aic31xx_write(codec, CLASSD_SPEAKER_AMP,
							SPK_DRV_ON);
				/* Check for the DAC FLAG Register to know if
				   the SPK Output Driver is powered up */
				time_out_counter = 0;
				do {
					mdelay(1);
					value = aic31xx_read(codec, DAC_FLAG_1);
					time_out_counter++;
				} while ((value & 0x11) == 0);

				/* Mute the Headphone Left and Right */
				value = aic31xx_read(codec, HPL_DRIVER);
				aic31xx_write(codec, HPL_DRIVER,
						(value & ~HP_UNMUTE));
				value = aic31xx_read(codec, HPR_DRIVER);
				aic31xx_write(codec, HPR_DRIVER,
						(value & ~HP_UNMUTE));

				/* Read the contents of the Page 0 Reg 63
				   DAC Data-Path Setup Register.
				   Just retain the upper two bits and lower
				   two bits */
				value = (aic31xx_read(codec, DAC_CHN_REG) & 0xC3);
				aic31xx_write(codec, DAC_CHN_REG,
					(value | LDAC_2_LCHN | RDAC_2_RCHN));

				/* Restore the values of the DACL and DACR */
				aic31xx_write(codec, LDAC_VOL, 0xF9);
				aic31xx_write(codec, RDAC_VOL, 0xF9);

				time_out_counter = 0;
				do {
					mdelay(5);
					value = aic31xx_read(codec, DAC_FLAG_2);
					time_out_counter++;
				} while ((time_out_counter < 100) && ((value & 0x11) == 0));

				/* Unmuting the DAC channel */
				dac_reg = aic31xx_read(codec, DAC_MUTE_CTRL_REG);
				aic31xx_write(codec, DAC_MUTE_CTRL_REG, (dac_reg &
								~MUTE_ON));

				DBG("%s : DAC UNMUTED ...\n", __func__);

				/* Unmuting THE Left Class-D Speaker Driver */
				value = aic31xx_read(codec, SPL_DRIVER);
				aic31xx_write(codec, SPL_DRIVER, (value | BIT2));

				/* Unmuting THE Right Class-D Speaker Driver */
				value = aic31xx_read(codec, SPR_DRIVER);
				aic31xx_write(codec, SPR_DRIVER, (value | BIT2));

				DBG("%s : SPL and SPR DRIVER UNMUTED\n", __func__);
			}
			aic31xx->mute[SNDRV_PCM_STREAM_PLAYBACK] = 0;
		}

		if (aic31xx->record_stream && aic31xx->mute[SNDRV_PCM_STREAM_CAPTURE]) {
			DBG("#### Unmute for Capture\n");
			/* Unmuting the ADC channel */
			value = aic31xx_read(codec, ADC_FGA);
			aic31xx_write(codec, ADC_FGA, (value & ~BIT7));
			aic31xx->mute[SNDRV_PCM_STREAM_CAPTURE] = 0;
			DBG("%s : ADC UNMUTED ...\n", __func__);
		}
	}

	mutex_unlock(&aic31xx->mutex_codec);
	return 0;
}

/*
 * aic31xx_mute
 * This function is to mute or unmute the left and right DAC
 */
static int aic31xx_mute(struct snd_soc_dai *dai, int mute)
{
	struct snd_soc_codec *codec = dai->codec;

	DBG("### %s : mute %x\n", __func__, mute);
	aic31xx_mute_codec(codec, mute);

#ifdef AIC31x_CODEC_DEBUG
	/*debug_print_registers(codec);*/
#endif

#if 0
	/*#### AGC ENABLE EXAMPLE CODE ####
	 * ## Switch to page 0 */
	/*w 30 00 00 */
	aic31xx_write(codec, PAGE_SELECT, 0);
	/*# Set AGC enable and Target Level = -10 dB
	 *# Target level can be set lower if clipping occurs during speech
	 *# Target level is adjusted considering Max Gain also */
	/*w 30 56 A0 // AGC hysteresis=DISABLE, noise threshold = -90dB */
	aic31xx_write(codec, AGC_CTRL_1, 0xA0);
	/*# Noise threshold should be set at higher level if noisy background
	 *# is present in application */
	/*w 30 57 FE # AGC maximum gain= 40 dB */
	aic31xx_write(codec, AGC_CTRL_2, 0xFE);
	/*# Higher Max gain is a trade off between gaining up a low
	 *# sensitivity MIC,  and the background
	 *# acoustic noise
	 *# Microphone bias voltage (MICBIAS) level can be used to change		 *# the Microphone Sensitivity */
	/*w 30 58 50*/
	aic31xx_write(codec, AGC_CTRL_3, 0x50);
	/*# Attack time=864/Fs w 30 59 68
	 *# Decay time=22016/Fs */
	/*w 30 5A A8*/
	aic31xx_write(codec, AGC_CTRL_5, 0xA8);
	/*# Noise debounce 0 ms
	 *# Noise debounce time can be increased if needed */
	/*w 30 5B 00*/
	aic31xx_write(codec, AGC_CTRL_6, 0x00);
	/*# Signal debounce 0 ms
	 *# Signal debounce time can be increased if needed */
	/*w 30 5C 00*/
	aic31xx_write(codec, AGC_CTRL_7, 0x00);
	/*#### END of AGC SET UP ####*/
#endif

	return 0;
}

/*
 * aic31xx_set_dai_sysclk
 *
 * This function is to the DAI system clock
 */
static int aic31xx_set_dai_sysclk(struct snd_soc_dai *codec_dai,
		int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	struct aic31xx_priv *aic31xx = snd_soc_codec_get_drvdata(codec);

	DBG("### %s : freq %d\n", __func__, freq);
#if 0
	switch (freq) {
	case AIC31XX_FREQ_12000000:
	case AIC31XX_FREQ_24000000:
	case AIC31XX_FREQ_19200000:
		aic31xx->sysclk = freq;
		return 0;
	}
	pr_err("%s : Invalid frequency to set DAI system clock\n", AUDIO_NAME);
	return -EINVAL;
#else
	aic31xx->sysclk = freq;
	return 0;
#endif
}

/*
 * aic31xx_set_dai_fmt
 *
 * This function is to set the DAI format
 */
static int aic31xx_set_dai_fmt(struct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	struct aic31xx_priv *aic31xx = snd_soc_codec_get_drvdata(codec);
	u8 iface_reg = 0;

	DBG("### %s : fmt 0x%08X\n", __func__, fmt);

	/* set master/slave audio interface */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		aic31xx->master = 1;
		iface_reg |= BIT_CLK_MASTER | WORD_CLK_MASTER;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		aic31xx->master = 0;
		iface_reg &= ~(BIT_CLK_MASTER | WORD_CLK_MASTER);
		break;
	case SND_SOC_DAIFMT_CBS_CFM:
		aic31xx->master = 0;
		iface_reg |= BIT_CLK_MASTER;
		iface_reg &= ~(WORD_CLK_MASTER);
		break;
	default:
		pr_err("%s : Invalid DAI master/slave interface\n", AUDIO_NAME);
		return -EINVAL;
	}

	/* interface format */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		break;
	case SND_SOC_DAIFMT_DSP_A:
		iface_reg |= (AIC31XX_DSP_MODE << AUDIO_MODE_SHIFT);
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		iface_reg |= (AIC31XX_RIGHT_JUSTIFIED_MODE << AUDIO_MODE_SHIFT);
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		iface_reg |= (AIC31XX_LEFT_JUSTIFIED_MODE << AUDIO_MODE_SHIFT);
		break;
	default:
		pr_err("%s : Invalid DAI interface format\n", AUDIO_NAME);
		return -EINVAL;
	}

	aic31xx_write(codec, INTERFACE_SET_REG_1, iface_reg);

	return 0;
}

static int aic31xx_dac_power_up_event(struct snd_soc_dapm_widget *w,
			struct snd_kcontrol *kcontrol, int event)
{
	return 0;
}

static int aic31xx_adc_power_up_event(struct snd_soc_dapm_widget *w,
			struct snd_kcontrol *kcontrol, int event)
{
	return 0;
}

static int aic31xx_hp_power_up_event(struct snd_soc_dapm_widget *w,
			struct snd_kcontrol *kcontrol, int event)
{
	return 0;
}

static int aic31xx_sp_event(struct snd_soc_dapm_widget *w,
			struct snd_kcontrol *kcontrol, int event)
{
	return 0;
}

static int pll_power_on_event(struct snd_soc_dapm_widget *w,
			struct snd_kcontrol *kcontrol, int event)
{
	DBG("### %s\n", __func__);

	if (event == (SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD))
		mdelay(10);
	return 0;
}

/* Left Output Mixer */
static const struct snd_kcontrol_new
left_output_mixer_controls[] = {
	SOC_DAPM_SINGLE("From DAC_L", DAC_MIX_CTRL, 6, 1, 0),
	SOC_DAPM_SINGLE("From MIC1LP", DAC_MIX_CTRL, 5, 1, 0),
	SOC_DAPM_SINGLE("From MIC1RP", DAC_MIX_CTRL, 4, 1, 0),
};

/* Right Output Mixer - Valid only for AIC31xx,3110,3100 */
static const struct
snd_kcontrol_new right_output_mixer_controls[] = {
	SOC_DAPM_SINGLE("From DAC_R", DAC_MIX_CTRL, 2, 1, 0),
	SOC_DAPM_SINGLE("From MIC1RP", DAC_MIX_CTRL, 1, 1, 0),
};

static const struct
snd_kcontrol_new pos_mic_pga_controls[] = {
	SOC_DAPM_SINGLE("MIC1LP_PGA_CNTL", MIC_GAIN, 6, 0x3, 0),
	SOC_DAPM_SINGLE("MIC1RP_PGA_CNTL", MIC_GAIN, 4, 0x3, 0),
	SOC_DAPM_SINGLE("MIC1LM_PGA_CNTL", MIC_GAIN, 2, 0x3, 0),
};

static const struct
snd_kcontrol_new neg_mic_pga_controls[] = {
	SOC_DAPM_SINGLE("CM_PGA_CNTL", ADC_IP_SEL, 6, 0x3, 0),
	SOC_DAPM_SINGLE("MIC1LM_PGA_CNTL", ADC_IP_SEL, 4, 0x3, 0),
};

static const struct snd_soc_dapm_widget aic31xx_dapm_widgets[] = {
	/* DACs */
	SND_SOC_DAPM_DAC_E("Left DAC", "Left Playback", DAC_CHN_REG, 7, 0,
			aic31xx_dac_power_up_event, SND_SOC_DAPM_POST_PMU | \
			SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_DAC_E("Right DAC", "Right Playback", DAC_CHN_REG, 6, 0,
			aic31xx_dac_power_up_event, SND_SOC_DAPM_POST_PMU | \
			SND_SOC_DAPM_POST_PMD),

	/* Output Mixers */
	SND_SOC_DAPM_MIXER("Left Output Mixer", SND_SOC_NOPM, 0, 0,
			&left_output_mixer_controls[0],
			ARRAY_SIZE(left_output_mixer_controls)),
	SND_SOC_DAPM_MIXER("Right Output Mixer", SND_SOC_NOPM, 0, 0,
			&right_output_mixer_controls[0],
			ARRAY_SIZE(right_output_mixer_controls)),

	/* Output drivers */
	SND_SOC_DAPM_PGA_E("HPL Driver", HEADPHONE_DRIVER, 7, 0,
			NULL, 0, aic31xx_hp_power_up_event,
			SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA_E("HPR Driver", HEADPHONE_DRIVER, 6, 0,
			NULL, 0, aic31xx_hp_power_up_event,
			SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),

#ifndef AIC3100_CODEC_SUPPORT
	/* For AIC3111 and AIC3110 as it is stereo both left and right channel
	 * class-D can be powered up/down
	 */
	SND_SOC_DAPM_PGA_E("SPL Class - D", CLASSD_SPEAKER_AMP, 7, 0, NULL, 0,
				aic31xx_sp_event, SND_SOC_DAPM_POST_PMU | \
				SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA_E("SPR Class - D", CLASSD_SPEAKER_AMP, 6, 0, NULL, 0,
				aic31xx_sp_event, SND_SOC_DAPM_POST_PMU | \
				SND_SOC_DAPM_POST_PMD),
#endif

#ifdef AIC3100_CODEC_SUPPORT
	/* For AIC3100 as is mono only left
	 * channel class-D can be powered up/down
	 */
	SND_SOC_DAPM_PGA("SPL Class - D", CLASSD_SPEAKER_AMP, 7, 0, NULL, 0,
			aic31xx_sp_event, SND_SOC_DAPM_POST_PMU | \
			SND_SOC_DAPM_POST_PMD),

#endif

	/* ADC */
	SND_SOC_DAPM_ADC_E("ADC", "Capture", ADC_DIG_MIC, 7, 0,
			aic31xx_adc_power_up_event, SND_SOC_DAPM_POST_PMU | \
			SND_SOC_DAPM_POST_PMD),

	/*Input Selection to MIC_PGA*/
	SND_SOC_DAPM_MIXER("P_Input_Mixer", SND_SOC_NOPM, 0, 0,
		&pos_mic_pga_controls[0], ARRAY_SIZE(pos_mic_pga_controls)),
	SND_SOC_DAPM_MIXER("M_Input_Mixer", SND_SOC_NOPM, 0, 0,
		&neg_mic_pga_controls[0], ARRAY_SIZE(neg_mic_pga_controls)),

	/*Enabling & Disabling MIC Gain Ctl */
	SND_SOC_DAPM_PGA("MIC_GAIN_CTL", MIC_PGA, 7, 1, NULL, 0),

	SND_SOC_DAPM_SUPPLY("PLLCLK", CLK_REG_2, 7, 0, pll_power_on_event,
				SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("CODEC_CLK_IN", SND_SOC_NOPM, 0, 0, NULL, 0),
	SND_SOC_DAPM_SUPPLY("NDAC_DIV", NDAC_CLK_REG, 7, 0, NULL, 0),
	SND_SOC_DAPM_SUPPLY("MDAC_DIV", MDAC_CLK_REG, 7, 0, NULL, 0),
	SND_SOC_DAPM_SUPPLY("NADC_DIV", NADC_CLK_REG, 7, 0, NULL, 0),
	SND_SOC_DAPM_SUPPLY("MADC_DIV", MADC_CLK_REG, 7, 0, NULL, 0),
	SND_SOC_DAPM_SUPPLY("BCLK_N_DIV", BCLK_N_VAL, 7, 0, NULL, 0),

	/* Outputs */
	SND_SOC_DAPM_OUTPUT("HPL"),
	SND_SOC_DAPM_OUTPUT("HPR"),
	SND_SOC_DAPM_OUTPUT("SPL"),

#ifndef AIC3100_CODEC_SUPPORT
	SND_SOC_DAPM_OUTPUT("SPR"),
#endif

	/* Inputs */
	SND_SOC_DAPM_INPUT("MIC1LP"),
	SND_SOC_DAPM_INPUT("MIC1RP"),
	SND_SOC_DAPM_INPUT("MIC1LM"),
	SND_SOC_DAPM_INPUT("INTMIC"),

};

static const struct snd_soc_dapm_route
aic31xx_audio_map[] = {

	{"CODEC_CLK_IN", NULL, "PLLCLK"},
	{"NDAC_DIV", NULL, "CODEC_CLK_IN"},
	{"NADC_DIV", NULL, "CODEC_CLK_IN"},
	{"MDAC_DIV", NULL, "NDAC_DIV"},
	{"MADC_DIV", NULL, "NADC_DIV"},
	{"BCLK_N_DIV", NULL, "MADC_DIV"},
	{"BCLK_N_DIV", NULL, "MDAC_DIV"},

	{"ADC", NULL, "MADC_DIV"},
	{"ADC", NULL, "BCLK_N_DIV"},
	{"P_Input_Mixer", "MIC1LP_PGA_CNTL", "MIC1LP"},
	{"P_Input_Mixer", "MIC1RP_PGA_CNTL", "MIC1RP"},
	{"P_Input_Mixer", "MIC1LM_PGA_CNTL", "MIC1LM"},

	{"M_Input_Mixer", "CM_PGA_CNTL", "MIC1LM"},
	{"M_Input_Mixer", "MIC1LM_PGA_CNTL", "MIC1LM"},

	{"MIC_GAIN_CTL", NULL, "P_Input_Mixer"},
	{"MIC_GAIN_CTL", NULL, "M_Input_Mixer"},

	{"ADC", NULL, "MIC_GAIN_CTL"},
	{"ADC", NULL, "INTMIC"},

	{"Left DAC", NULL, "MDAC_DIV" },
	{"Right DAC", NULL, "MDAC_DIV"},
	{"Left DAC", NULL, "BCLK_N_DIV" },
	{"Right DAC", NULL, "BCLK_N_DIV"},

	/* Left Output */
	{"Left Output Mixer", "From DAC_L", "Left DAC"},
	{"Left Output Mixer", "From MIC1LP", "MIC1LP"},
	{"Left Output Mixer", "From MIC1RP", "MIC1RP"},

	/* Right Output */
	{"Right Output Mixer", "From DAC_R", "Right DAC"},
	{"Right Output Mixer", "From MIC1RP", "MIC1RP"},

	/* HPL path */
	{"HPL Driver", NULL, "Left Output Mixer"},
	{"HPL", NULL, "HPL Driver"},

	/* HPR path */
	{"HPR Driver", NULL, "Right Output Mixer"},
	{"HPR", NULL, "HPR Driver"},

	/* SPK L path */
	{"SPL Class - D", NULL, "Left Output Mixer"},
	{"SPL", NULL, "SPL Class - D"},

#ifndef AIC3100_CODEC_SUPPORT
	/* SPK R path */
	{"SPR Class - D", NULL, "Right Output Mixer"},
	{"SPR", NULL, "SPR Class - D"},
#endif
};


/*
 * aic31xx_add_widgets
 *
 * adds all the ASoC Widgets identified by aic31xx_snd_controls array. This
 * routine will be invoked * during the Audio Driver Initialization.
 */
static int aic31xx_add_widgets(struct snd_soc_codec *codec)
{
	struct snd_soc_dapm_context *dapm = &codec->dapm;
	int ret = 0;

	DBG("### %s\n", __func__);

	ret = snd_soc_dapm_new_controls(dapm, aic31xx_dapm_widgets,
					ARRAY_SIZE(aic31xx_dapm_widgets));
	if (!ret)
		DBG("%s : Completed adding dapm widgets size = %d\n",
			__func__, ARRAY_SIZE(aic31xx_dapm_widgets));

	ret = snd_soc_dapm_add_routes(dapm, aic31xx_audio_map,
					ARRAY_SIZE(aic31xx_audio_map));
	if (!ret)
		DBG("%s : Completed adding DAPM routes = %d\n",
			__func__, ARRAY_SIZE(aic31xx_audio_map));

	ret = snd_soc_dapm_new_widgets(dapm);
	if (!ret)
		DBG("%s : widgets updated\n", __func__);

	return 0;
}

static const char *dac_mute[] = {"Unmute", "Mute"};
static const char *adc_mute[] = {"Unmute", "Mute"};
static const char *hpl_pwr[] = {"Off", "On"};
static const char *hpr_pwr[] = {"Off", "On"};
static const char *ldac_pwr[] = {"Off", "On"};
static const char *rdac_pwr[] = {"Off", "On"};

static const char *dacvolume_extra[] = {"L & R Ind Vol", "LVol = RVol",
	"RVol = LVol"};
static const char *dacvolume_control[] = {"control register", "pin"};
static const char *dacsoftstep_control[] = {"1 step / sample",
	"1 step / 2 sample", "disabled"};

static const char *beep_generator[] = {"Disabled", "Enabled"};

static const char *micbias_voltage[] = {"off", "2 V", "2.5 V", "AVDD"};
static const char *dacleftip_control[] = {"off", "left data",
	"right data", "(left + right) / 2"};
static const char *dacrightip_control[] = { "off", "right data", "left data",
	"(left+right)/2" };

static const char *dacvoltage_control[] = {"1.35 V", "5 V ", "1.65 V", "1.8 V"};
static const char *headset_detection[] = {"Disabled", "Enabled"};
static const char *drc_enable[] = {"Disabled", "Enabled"};
static const char *mic1lp_enable[] = {"off", "10 k", "20 k", "40 k"};
static const char *mic1rp_enable[] = {"off", "10 k", "20 k", "40 k"};
static const char *mic1lm_enable[] = {"off", "10 k", "20 k", "40 k"};
static const char *cm_enable[] = {"off", "10 k", "20 k", "40 k"};
static const char *mic_enable[] = {"Gain controlled by D0 - D6", "0 db Gain"};
static const char *mic1_enable[] = {"floating", "connected to CM internally"};


/* Creates an array of the Single Ended Widgets */
static const struct soc_enum aic31xx_enum[] = {
	SOC_ENUM_SINGLE(DAC_MUTE_CTRL_REG, 3, 2, dac_mute),
	SOC_ENUM_SINGLE(DAC_MUTE_CTRL_REG, 2, 2, dac_mute),
	SOC_ENUM_SINGLE(DAC_MUTE_CTRL_REG, 0, 3, dacvolume_extra),
	SOC_ENUM_SINGLE(PIN_VOL_CTRL, 7, 2, dacvolume_control),
	SOC_ENUM_SINGLE(DAC_CHN_REG, 0, 3, dacsoftstep_control),
	SOC_ENUM_SINGLE(LEFT_BEEP_GEN, 7, 2, beep_generator),
	SOC_ENUM_SINGLE(MICBIAS_CTRL, 0, 4, micbias_voltage),
	SOC_ENUM_SINGLE(DAC_CHN_REG, 4, 4, dacleftip_control),
	SOC_ENUM_SINGLE(DAC_CHN_REG, 2, 4, dacrightip_control),
	SOC_ENUM_SINGLE(HEADPHONE_DRIVER, 3, 4, dacvoltage_control),
	SOC_ENUM_SINGLE(HEADSET_DETECT, 7, 2, headset_detection),
	SOC_ENUM_DOUBLE(DRC_CTL_REG_1, 6, 5, 2, drc_enable),
	SOC_ENUM_SINGLE(MIC_GAIN, 6, 4, mic1lp_enable),
	SOC_ENUM_SINGLE(MIC_GAIN, 4, 4, mic1rp_enable),
	SOC_ENUM_SINGLE(MIC_GAIN, 2, 4, mic1lm_enable),
	SOC_ENUM_SINGLE(MIC_PGA, 7, 2, mic_enable),
	SOC_ENUM_SINGLE(ADC_IP_SEL, 6, 4, cm_enable),
	SOC_ENUM_SINGLE(ADC_IP_SEL, 4, 4, mic1lm_enable),
	SOC_ENUM_SINGLE(CM_SET, 7, 2, mic1_enable),
	SOC_ENUM_SINGLE(CM_SET, 6, 2, mic1_enable),
	SOC_ENUM_SINGLE(CM_SET, 5, 2, mic1_enable),
	SOC_ENUM_SINGLE(ADC_FGA, 7, 2, adc_mute),
	SOC_ENUM_SINGLE(HEADPHONE_DRIVER, 7, 2, hpl_pwr),
	SOC_ENUM_SINGLE(HEADPHONE_DRIVER, 6, 2, hpr_pwr),
	SOC_ENUM_SINGLE(DAC_CHN_REG, 7, 2, ldac_pwr),
	SOC_ENUM_SINGLE(DAC_CHN_REG, 6, 2, rdac_pwr),
};


static const DECLARE_TLV_DB_SCALE(dac_vol_tlv, -6350, 50, 0);
static const DECLARE_TLV_DB_SCALE(adc_fgain_tlv, 00, 10, 0);
static const DECLARE_TLV_DB_SCALE(adc_cgain_tlv, -2000, 50, 0);
static const DECLARE_TLV_DB_SCALE(mic_pga_tlv, 0, 50, 0);
static const DECLARE_TLV_DB_SCALE(hp_drv_tlv, 0, 100, 0);
static const DECLARE_TLV_DB_SCALE(class_D_drv_tlv, 600, 600, 0);
static const DECLARE_TLV_DB_SCALE(hp_vol_tlv, -7830, 60, 0);
static const DECLARE_TLV_DB_SCALE(sp_vol_tlv, -7830, 60, 0);

static const struct snd_kcontrol_new aic31xx_snd_controls[] = {
	/* DAC Volume Control */
	 SOC_DOUBLE_R_SX_TLV("DAC Playback Volume", LDAC_VOL, RDAC_VOL, 8,
						0xffffff81, 0x30, dac_vol_tlv),
	/* DAC mute control */
	SOC_ENUM("Left DAC Mute", aic31xx_enum[LMUTE_ENUM]),
	SOC_ENUM("Right DAC Mute", aic31xx_enum[RMUTE_ENUM]),
	/* DAC volume Extra control */
	SOC_ENUM("DAC volume Extra control", aic31xx_enum[DACEXTRA_ENUM]),
	/* DAC volume Control register/pin control */
	SOC_ENUM("DAC volume Control register/pin",
			aic31xx_enum[DACCONTROL_ENUM]),
	/* DAC Volume soft stepping control */
	SOC_ENUM("DAC Volume soft stepping", aic31xx_enum[SOFTSTEP_ENUM]),
	/* HP driver mute control */
	SOC_DOUBLE_R("HP driver mute", HPL_DRIVER, HPR_DRIVER, 2, 1, 0),

	/* SP driver mute control */
	SOC_DOUBLE_R("SP driver mute", SPL_DRIVER, SPR_DRIVER, 2, 1, 0),

	/* ADC FINE GAIN */
	SOC_SINGLE_TLV("ADC FINE GAIN", ADC_FGA, 4, 4, 1, adc_fgain_tlv),
	/* ADC COARSE GAIN */
	SOC_DOUBLE_S8_TLV("ADC COARSE GAIN", ADC_CGA, 0xffffff68, 0x28, \
					adc_cgain_tlv),
	/* ADC MIC PGA GAIN */
	SOC_SINGLE_TLV("ADC MIC_PGA GAIN", MIC_PGA, 0, 119, 0, mic_pga_tlv),

	/* HP driver Volume Control */
	SOC_DOUBLE_R_TLV("HP driver Volume", HPL_DRIVER, HPR_DRIVER, 3, 9,
					0, hp_drv_tlv),
	/* Left DAC input selection control */
	SOC_ENUM("Left DAC input selection", aic31xx_enum[DACLEFTIP_ENUM]),
	/* Right DAC input selection control */
	SOC_ENUM("Right DAC input selection", aic31xx_enum[DACRIGHTIP_ENUM]),

	/* Beep generator Enable/Disable control */
	SOC_ENUM("Beep generator Enable / Disable", aic31xx_enum[BEEP_ENUM]),
	/* Beep generator Volume Control */
	SOC_DOUBLE_R("Beep Volume Control(0 = -61 db, 63 = 2 dB)",
			LEFT_BEEP_GEN, RIGHT_BEEP_GEN, 0, 0x3F, 1),
	/* Beep Length MSB control */
	SOC_SINGLE("Beep Length MSB", BEEP_LENGTH_MSB, 0, 255, 0),
	/* Beep Length MID control */
	SOC_SINGLE("Beep Length MID", BEEP_LENGTH_MID, 0, 255, 0),
	/* Beep Length LSB control */
	SOC_SINGLE("Beep Length LSB", BEEP_LENGTH_LSB, 0, 255, 0),
	/* Beep Sin(x) MSB control */
	SOC_SINGLE("Beep Sin(x) MSB", BEEP_SINX_MSB, 0, 255, 0),
	/* Beep Sin(x) LSB control */
	SOC_SINGLE("Beep Sin(x) LSB", BEEP_SINX_LSB, 0, 255, 0),
	/* Beep Cos(x) MSB control */
	SOC_SINGLE("Beep Cos(x) MSB", BEEP_COSX_MSB, 0, 255, 0),
	/* Beep Cos(x) LSB control */
	SOC_SINGLE("Beep Cos(x) LSB", BEEP_COSX_LSB, 0, 255, 0),

	/* Mic Bias voltage */
	SOC_ENUM("Mic Bias Voltage", aic31xx_enum[MICBIAS_ENUM]),

	/* DAC Processing Block Selection */
	SOC_SINGLE("DAC Processing Block Selection(0 <->25)",
			DAC_PRB_SEL_REG, 0, 0x19, 0),
	/* ADC Processing Block Selection */
	SOC_SINGLE("ADC Processing Block Selection(0 <->25)",
			ADC_PRB_SEL_REG, 0, 0x12, 0),

	/* Throughput of 7-bit vol ADC for pin control */
	SOC_SINGLE("Throughput of 7 - bit vol ADC for pin",
			PIN_VOL_CTRL, 0, 0x07, 0),

	/* Audio gain control (AGC) */
	SOC_SINGLE("Audio Gain Control(AGC)", AGC_CTRL_1, 7, 0x01, 0),
	/* AGC Target level control */
	SOC_SINGLE("AGC Target Level Control", AGC_CTRL_1, 4, 0x07, 1),
	/* AGC Maximum PGA applicable */
	SOC_SINGLE("AGC Maximum PGA Control", AGC_CTRL_3, 0, 0x77, 0),
	/* AGC Attack Time control */
	SOC_SINGLE("AGC Attack Time control", AGC_CTRL_4, 3, 0x1F, 0),
	/* AGC Attack Time Multiply factor */
	SOC_SINGLE("AGC_ATC_TIME_MULTIPLIER", AGC_CTRL_4, 0, 8, 0),
	/* AGC Decay Time control */
	SOC_SINGLE("AGC Decay Time control", AGC_CTRL_5, 3, 0x1F, 0),
	/* AGC Decay Time Multiplier */
	SOC_SINGLE("AGC_DECAY_TIME_MULTIPLIER", AGC_CTRL_5, 0, 8, 0),
	/* AGC HYSTERISIS */
	SOC_SINGLE("AGC_HYSTERISIS", AGC_CTRL_2, 6, 3, 0),
	/* AGC Noise Threshold */
	SOC_SINGLE("AGC_NOISE_THRESHOLD", AGC_CTRL_2, 1, 32, 1),
	/* AGC Noise Bounce control */
	SOC_SINGLE("AGC Noice bounce control", AGC_CTRL_6, 0, 0x1F, 0),
	/* AGC Signal Bounce control */
	SOC_SINGLE("AGC Signal bounce control", AGC_CTRL_7, 0, 0x0F, 0),

	/* HP Output common-mode voltage control */
	SOC_ENUM("HP Output common - mode voltage control",
			aic31xx_enum[VOLTAGE_ENUM]),

	/* Headset detection Enable/Disable control */
	SOC_ENUM("Headset detection Enable / Disable", aic31xx_enum[HSET_ENUM]),

	/* DRC Enable/Disable control */
	SOC_ENUM("DRC Enable / Disable", aic31xx_enum[DRC_ENUM]),
	/* DRC Threshold value control */
	SOC_SINGLE("DRC Threshold value(0 = -3 db, 7 = -24 db)",
			DRC_CTL_REG_1, 2, 0x07, 0),
	/* DRC Hysteresis value control */
	SOC_SINGLE("DRC Hysteresis value(0 = 0 db, 3 = 3 db)",
			DRC_CTL_REG_1, 0, 0x03, 0),
	/* DRC Hold time control */
	SOC_SINGLE("DRC hold time", DRC_CTL_REG_2, 3, 0x0F, 0),
	/* DRC attack rate control */ SOC_SINGLE("DRC attack rate",
			DRC_CTL_REG_3, 4, 0x0F, 0),
	/* DRC decay rate control */
	SOC_SINGLE("DRC decay rate", DRC_CTL_REG_3, 0, 0x0F, 0),
	/* MIC1LP selection for ADC I/P P-terminal */
	SOC_ENUM("MIC1LP selection for ADC I/P P - terminal",
			aic31xx_enum[MIC1LP_ENUM]),
	/* MIC1RP selection for ADC I/P P-terminal */
	SOC_ENUM("MIC1RP selection for ADC I/P P - terminal",
			aic31xx_enum[MIC1RP_ENUM]),
	/* MIC1LM selection for ADC I/P P-terminal */
	SOC_ENUM("MIC1LM selection for ADC I/P P - terminal",
			aic31xx_enum[MIC1LM_ENUM]),
	/* CM selection for ADC I/P M-terminal */
	SOC_ENUM("CM selection for ADC IP M - terminal",
			aic31xx_enum[CM_ENUM]),
	/* MIC1LM selection for ADC I/P M-terminal */
	SOC_ENUM("MIC1LM selection for ADC I/P M - terminal",
			aic31xx_enum[MIC1LMM_ENUM]),
	/* MIC PGA Setting */
	SOC_ENUM("MIC PGA Setting", aic31xx_enum[MIC_ENUM]),
	/* MIC1LP CM Setting */
	SOC_ENUM("MIC1LP CM Setting", aic31xx_enum[MIC1_ENUM]),
	/* MIC1RP CM Setting */
	SOC_ENUM("MIC1RP CM Setting", aic31xx_enum[MIC2_ENUM]),
	/* MIC1LP CM Setting */
	SOC_ENUM("MIC1LM CM Setting", aic31xx_enum[MIC3_ENUM]),
	/* ADC mute control */
	SOC_ENUM("ADC Mute", aic31xx_enum[ADCMUTE_ENUM]),
	/* DAC Left & Right Power Control */
	SOC_ENUM("LDAC_PWR_CTL", aic31xx_enum[LDAC_ENUM]),
	SOC_ENUM("RDAC_PWR_CTL", aic31xx_enum[RDAC_ENUM]),

	/* HP Driver Power up/down control */
	SOC_ENUM("HPL_PWR_CTL", aic31xx_enum[HPL_ENUM]),
	SOC_ENUM("HPR_PWR_CTL", aic31xx_enum[HPR_ENUM]),

	/* MIC PGA Enable/Disable */
	SOC_SINGLE("MIC_PGA_EN_CTL", MIC_PGA, 7, 2, 0),

	/* HP Detect Debounce Time */
	SOC_SINGLE("HP_DETECT_DEBOUNCE_TIME", HEADSET_DETECT, 2, 0x05, 0),
	/* HP Button Press Debounce Time */
	SOC_SINGLE("HP_BUTTON_DEBOUNCE_TIME", HEADSET_DETECT, 0, 0x03, 0),

	/* Added for Debugging */
	SOC_SINGLE("LoopBack_Control", INTERFACE_SET_REG_2, 4, 4, 0),


#ifdef AIC3110_CODEC_SUPPORT
	/* For AIC3110 output is stereo so we are using	SOC_DOUBLE_R macro */

	/* SP Class-D driver output stage gain Control */
	SOC_DOUBLE_R_TLV("Class-D driver Vol", SPL_DRIVER, SPR_DRIVER, 3, 3,
					 0, class_D_drv_tlv),
#endif

#ifdef AIC3100_CODEC_SUPPORT
	/* SP Class-D driver output stage gain Control */
	SOC_SINGLE("Class - D driver Volume(0 = 6 dB, 4 = 24 dB)",
			SPL_DRIVER, 3, 0x04, 0),
#endif

	/* HP Analog Gain Volume Control */
	SOC_DOUBLE_R_TLV("HP Analog Gain", L_ANLOG_VOL_2_HPL, \
			R_ANLOG_VOL_2_HPR, 0, 0x7F, 1, hp_vol_tlv),

#ifdef AIC3110_CODEC_SUPPORT
	/* SP Analog Gain Volume Control */
	SOC_DOUBLE_R_TLV("SP Analog Gain", L_ANLOG_VOL_2_SPL, \
			R_ANLOG_VOL_2_SPR, 0, 0x7F, 1, sp_vol_tlv),
#endif

#ifdef AIC3100_CODEC_SUPPORT
	/* SP Analog Gain Volume Control */
	SOC_SINGLE("SP Analog Gain(0 = 0 dB, 127 = -78.3 dB)",
			L_ANLOG_VOL_2_SPL, 0, 0x7F, 1),
#endif
	/* Program Registers */
	SOC_SINGLE_AIC31XX("Program Registers"),

	SOC_SINGLE("Headset Detect", HEADSET_DETECT, 0, 0xFF, 0),
};


/*
 * The global Register Initialization sequence Array. During the Audio
 * Driver initialization, this array will be utilized to perform the
 * default initialization of the audio Driver.
 */
static const struct
aic31xx_configs aic31xx_reg_init[] = {

	/* Clock settings */
	{CLK_REG_1, CODEC_MUX_VALUE},

	/* Switch off PLL while Initializing Codec */
	{CLK_REG_2, 0x00},
	{CLK_REG_3, 0x00},
	{CLK_REG_4, 0x00},
	{CLK_REG_5, 0x00},
	{NDAC_CLK_REG, 0x00},
	{MDAC_CLK_REG, 0x00},
	{DAC_OSR_MSB, 0x00},
	{DAC_OSR_LSB, 0x00},
	{INTERFACE_SET_REG_1, BCLK_DIR_CTRL},

	/* Switch off BCLK_N Divider */
	{BCLK_N_VAL, 0x00},

	{INTERFACE_SET_REG_2, DAC_MOD_CLK_2_BDIV_CLKIN},
	{INTERFACE_SET_REG_4, 0x10}, /* old value is 0x12 */
	{INTERFACE_SET_REG_5, 0x00}, /* old value is 0x10 */
	{DOUT_CTRL, 0x12}, /* old value is 0x02 */

	/* POP_REMOVAL: Step_1: Setting HP in weakly driver common mode */
	{HPL_DRIVER, 0x00},
	{HPR_DRIVER, 0x00},

	/* Step_2: HP pop removal settings */
	{HP_POP_CTRL, CM_VOLTAGE_FROM_AVDD},
	/* Step_3: Configuring HP in Line out Mode */
	{HP_DRIVER_CTRL, 0x06},

	/* Step_4: Powering up the HP in Line out mode */
	{HEADPHONE_DRIVER, HP_DRIVER_ON},

	/* Step_5: Reconfiguring the CM to Band Gap mode */
	/*	   {HP_POP_CTRL, (BIT7 | HP_POWER_UP_76_2_MSEC |
	 *                        HP_DRIVER_3_9_MS |CM_VOLTAGE_FROM_BAND_GAP)
	 *         },*/
	{HP_POP_CTRL, (BIT7 | HP_POWER_UP_6_1_SEC | HP_DRIVER_3_9_MS | CM_VOLTAGE_FROM_BAND_GAP)},
	{PGA_RAMP_CTRL, 0x70},        /* Speaker Ramp up time scaled to 30.5ms */

	{HEADPHONE_DRIVER, 0x0C},   /* Turn OFF the Headphone Driver by default
				     * and also configure CM Voltage to 1.5V to
				     * reduce THD */
	{CLASSD_SPEAKER_AMP, 0x06},/* Turn OFF the Speaker Driver by default */

	/* DAC Output Mixer Setting */
	{DAC_MIX_CTRL, RDAC_2_RAMP | LDAC_2_LAMP}, /* For aic31xx this is applicable...enabling DAC
						     routing through mixer amplifier individually for left & right
						     DAC..[1][35]... */

	{L_ANLOG_VOL_2_HPL, HP_DEFAULT_VOL},  /* Set volume of left Analog HPL to 0db attenuation [1][36] 0x9E*/
	{R_ANLOG_VOL_2_HPR, HP_DEFAULT_VOL},  /*Only applicable for 31xx...3120 does not have this register [1][37]*/
	{L_ANLOG_VOL_2_SPL, SPK_DEFAULT_VOL}, /*Only applicable for 31xx...3120 does not have this register [1][37] 0x80*/
	{R_ANLOG_VOL_2_SPR, SPK_DEFAULT_VOL}, /*Only applicable for 31xx...3120 does not have this register [1][37]*/

	/* mute HP Driver */
	{HPL_DRIVER, 0x00}, /* Muting HP_left(31xx)/HP(3120)...in [1][40]*/
	{HPR_DRIVER, 0x00}, /* Muting HP_right(31xx)..not present in 3120...[1][41]*/

	{HP_DRIVER_CTRL, 0x00},

	/* Configured the Speaker Driver Gain to 6db. */
	{SPL_DRIVER, 0x00},
	{SPR_DRIVER, 0x00},

	/* Headset Detect setting */
	{INTL_CRTL_REG_1, 0xC0},
	{GPIO_CRTL_REG_1, 0x00},  /* Old value of 0x14 can be used if Codec GPIO is required for Headset Detect */
	{MICBIAS_CTRL, 0x0B},

	/* DAC Channels PWR UP */
	{DAC_CHN_REG, 0x02}, /* Mistral: setting
			       [0][63] to reset value 0x14 (RDAC_2_RCHN | LDAC_2_LCHN)=> DAC
			       power=off DAC delta path =left, vol=soft stepping per sample
			       period...(31xx).*/ /* Unmute DAC channels */
	{DAC_MUTE_CTRL_REG, 0x0C}, /* DAC are muted by default...[0][64] */

	/* DAC volume setting */
	{LDAC_VOL, DAC_DEFAULT_VOL}, /* DAC volume set to default value .[0][65]...*/

	{RDAC_VOL, DAC_DEFAULT_VOL}, /* Only applicable for 31xx...3120
					does not have this register [0][66]*/

	/* ADC Setting */
	{ADC_DIG_MIC, 0x00},	/* this value will be altered during power up
				 * Currently configured to use Digital Microphone
				 * Input */
	{AGC_CTRL_1, 0x00},	/* Previous value was 0xA0, now agc disabled */
	{AGC_CTRL_2, 0xFE},
	{AGC_CTRL_3, 0x50},
	{AGC_CTRL_4, 0xA8},
	{AGC_CTRL_5, 0x00},
	{AGC_CTRL_6, 0x00},

	{ADC_PRB_SEL_REG, 0x04},


	/* ADC Channel Fine Gain */
	/*{ADC_FGA, 0x80},*/
	{ADC_FGA, 0x80|0x40}, /* -0.4db */
	/* ADC channel Coarse Gain */
	{ADC_CGA, 0x00}, /* 0x00 for 0db */
	/*{ADC_CGA, 0x28}, */ /* 20db */
	/* ON the KC1 board MIC1LM has been configured */
/*	{MIC_GAIN, 0x08},  * Old Value 0x04 */
	{MIC_GAIN, 0x18}, /* Old Value 0x04 */
	{ADC_IP_SEL, 0x80}, /* Old value 0x20 */

/*	{CM_SET, 0x20}, */ /* previous value was 0x01 */
	{CM_SET, 0x00}, /* previous value was 0x20 */

	/* Initial Default configuration for ADC PGA */

	{MIC_PGA, 0x44}, /* 34 dB */

	{HP_SPK_ERR_CTL, 0x03}, /* short circuit protection of HP and Speaker power bits */

	/* DAC PRB configured to PRB_1 */
	{DAC_PRB_SEL_REG, 0x01},

	/* Headset detection enabled by default and Debounce programmed to 32 ms
	 * for Headset Detection and 32ms for Headset button-press Detection
	 */
	{HEADSET_DETECT, (HP_DEBOUNCE_32_MS | HS_DETECT_EN | HS_BUTTON_PRESS_32_MS)},

	/* We will use the internal oscillator for all Programmable Delay Timers used for
	 * Headphones debounce time. This improves POP reduction.
	 *
	{TIMER_CLOCK_MCLK_DIVIDER , 0x00},*/
};

/*
 * aic31xx_probe
 *
 * This is first driver function called by the SoC core driver.
 */
static int aic31xx_probe(struct snd_soc_codec *codec)
{
#ifdef AIC31xx_JACK
	struct aic31xx_jack_data *jack;
#endif

	int ret = 0, i, size = 0;

	DBG("### %s\n", __func__);

	codec->control_data = aic_priv->control_data;
	codec->hw_write = (hw_write_t)i2c_master_send;

	aic_priv->page_no = 0;
	aic_priv->power_status[SNDRV_PCM_STREAM_PLAYBACK] = 0;
	aic_priv->power_status[SNDRV_PCM_STREAM_CAPTURE] = 0;
	aic_priv->mute[SNDRV_PCM_STREAM_PLAYBACK] = 1;
	aic_priv->mute[SNDRV_PCM_STREAM_CAPTURE] = 1;
#if IS_ENABLED(CONFIG_ARCH_TZ3000)
	aic_priv->headset_connected = 0;
#else
	if (machine_is_tz2000rb3()) /* Montblanc */
		aic_priv->headset_connected = 1;
	else
		aic_priv->headset_connected = 0;
#endif
	aic_priv->playback_status = 0;
	aic_priv->headset_current_status = 0;
	aic_priv->i2c_regs_status = 0;

	aic31xx_change_page(codec, 0x00);
	aic31xx_write(codec, RESET, 0x01);
	mdelay(10);

#ifdef AIC31x_CODEC_DEBUG
	/*debug_print_registers(codec);*/
#endif

	for (i = 0; i < sizeof(aic31xx_reg_init)/sizeof(struct aic31xx_configs);
									  i++) {
		aic31xx_write(codec, aic31xx_reg_init[i].reg_offset,\
					aic31xx_reg_init[i].reg_val);
		mdelay(5);
	}

#ifdef AIC31x_CODEC_DEBUG
	/*debug_print_registers(codec);*/
#endif
	DBG("%s : Switching the Codec to STANDBY State...\n", __func__);
	size = ARRAY_SIZE(aic31xx_snd_controls);
	ret = snd_soc_add_codec_controls(codec, aic31xx_snd_controls,
			ARRAY_SIZE(aic31xx_snd_controls));

	aic31xx_add_widgets(codec);

	mutex_init(&aic_priv->mutex_codec);

#ifdef AIC31xx_JACK
	/* use switch-class based headset reporting if platform requires it */
	jack = &aic_priv->hs_jack;
	jack->sdev.name = "h2w";
	ret = switch_dev_register(&jack->sdev);
	if (ret)
		dev_err(codec->dev, "error registering switch device %d\n", ret);
#endif

	aic31xx_hp_power_up(codec);

	pr_info("AIC3110 Audio Codec %s, power_ctrl=%s, mute_ctrl=%s\n",
		AIC31XX_VERSION,
		(ctrl_data.power_ctrl == false ? "always power up" : "power up/down"),
		(ctrl_data.mute_ctrl == false ? "always unmute" : "mute/unmute"));

	return ret;
}

/*
 * aic31xx_remove
 *
 * This function is used to unregister the Driver.
 */
static int aic31xx_remove(struct snd_soc_codec *codec)
{
#ifdef AIC31xx_JACK
	struct aic31xx_jack_data *hs_jack = &aic_priv->hs_jack;
#endif
	/*struct snd_soc_dapm_context *dapm = &codec->dapm;*/
	DBG("### %s\n", __func__);

	/* power down chip */
	if (codec->control_data)
		aic31xx_set_bias_level(codec, SND_SOC_BIAS_OFF);

#ifdef NO_PCMS
	snd_soc_free_pcms(socdev);
#endif
	/*snd_soc_dapm_free(dapm);*/
#ifdef AIC31xx_JACK
	switch_dev_unregister(&hs_jack->sdev);
#endif

	return 0;
}

/*
 * aic31xx_suspend
 * This function is to suspend the AIC31xx driver.
 */
static int aic31xx_suspend(struct snd_soc_codec *codec)
{
	int val;
	struct aic31xx_priv *aic31xx = snd_soc_codec_get_drvdata(codec);

	DBG("### %s\n", __func__);

	if (aic31xx->playback_status == 0) {
		aic31xx_set_bias_level(codec, SND_SOC_BIAS_OFF);

		/* Bit 7 of Page 1/ Reg 46 gives the soft powerdown control.
		 * Setting this bit will further reduces the amount of power
		 * consumption
		 */
		val = aic31xx_read(codec, MICBIAS_CTRL);
		aic31xx_write(codec, MICBIAS_CTRL, val | BIT7);

#ifdef AIC31xx_REGULATOR
		regulator_disable(audio_regulator);
#endif
	}
	return 0;
}

/*
 * aic31xx_resume
 * This function is to resume the AIC31xx driver.
 */
static int aic31xx_resume(struct snd_soc_codec *codec)
{
	struct aic31xx_priv *aic31xx = snd_soc_codec_get_drvdata(codec);
	u8 val;

	DBG("### %s\n", __func__);

#ifdef AIC31xx_REGULATO
	if (regulator_set_voltage(audio_regulator, REGU_MIN_VOL, REGU_MAX_VOL))
		pr_err("%s : regulator_set 3V error\n", AUDIO_NAME);

	regulator_enable(audio_regulator);
#endif

	val = aic31xx_read(codec, MICBIAS_CTRL);
	aic31xx_write(codec, MICBIAS_CTRL, val & ~BIT7);

	/* Mute the codec to avoid pops while coming out of Suspend */
	aic31xx->mute[SNDRV_PCM_STREAM_PLAYBACK] = 0;
	aic31xx->mute[SNDRV_PCM_STREAM_CAPTURE] = 0;
	aic31xx_mute_codec(codec, 1);

	return 0;
}

/**
 * @struct snd_soc_codec_dev_aic31xx
 *
 * This structure is soc audio codec device structure which pointer * to basic
 * functions aic31xx_probe(), aic31xx_remove(), aic31xx_suspend() and
 * aic31xx_resume()
 */
struct snd_soc_codec_driver soc_codec_dev_aic31xx = {
	.probe = aic31xx_probe,
	.remove = aic31xx_remove,
	.suspend = aic31xx_suspend,
	.resume = aic31xx_resume,
	.read = aic31xx_read,
	.write = aic31xx_write,
	.set_bias_level = aic31xx_set_bias_level,
	.reg_cache_size = sizeof(aic31xx_reg),
	.reg_word_size = sizeof(u8),
	.reg_cache_default = aic31xx_reg,
};

/**
 * @struct tlv320aic31xx_dai_ops
 *
 * The DAI Operations Structure which contains the call-back function
 * Addresses used by the ALSA Core Layer when operating with this Codec
 * Driver.
 */
static struct snd_soc_dai_ops tlv320aic31xx_dai_ops = {
	.startup = aic31xx_startup,
	.hw_params = aic31xx_hw_params,
	.digital_mute = aic31xx_mute,
	.set_sysclk = aic31xx_set_dai_sysclk,
	.set_fmt = aic31xx_set_dai_fmt,
};

/**
 * @struct tlv320aic31xx_dai
 *
 * SoC Codec DAI driver which has DAI capabilities viz., playback and
 * capture, DAI runtime information viz. state of DAI and pop wait
 * state, and DAI private data.  The AIC31xx rates ranges from 8k to
 * 192k The PCM bit format supported are 16, 20, 24 and 32 bits
 */
struct snd_soc_dai_driver tlv320aic31xx_dai[] = {
	{
		.name = "tlv320aic3110-hifi",
		.playback = {
			.stream_name = "Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = AIC31XX_RATES,
			.formats = AIC31XX_FORMATS,
		},
		.capture = {
			.stream_name = "Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = AIC31XX_RATES,
			.formats = AIC31XX_FORMATS,
		},
		.ops =  &tlv320aic31xx_dai_ops,
	},
};


/*
 * tlv320aic31xx_codec_probe
 * This function is invoked by the soc_probe of the ALSA Core Layer during the
 * execution of Core Layer Initialization. This function is used to register the
 * Audio Codec with the ALSA Core Layer using the snd_soc_register_codec API.
 */
/*static int __devinit tlv320aic31xx_codec_probe(struct platform_device *pdev)*/
static __devinit int tlv320aic31xx_codec_probe(struct i2c_client *i2c,
		const struct i2c_device_id *i2c_id)
{

	int ret;

	DBG("### %s\n", __func__);

	aic_priv = kzalloc(sizeof(struct aic31xx_priv), GFP_KERNEL);

	if (aic_priv == NULL) {
		pr_err("%s : aic31xx_probe kzalloc for Codec Private failed..\n",
			AUDIO_NAME);
		return -ENOMEM;
	}
	DBG("%s : aic31xx_probe: Codec Private allocation fine...\n", __func__);

	aic_priv->control_data = i2c;
	i2c_set_clientdata(i2c, aic_priv);

#ifdef AIC31xx_REGULATO
	audio_regulator = regulator_get(NULL, "audio-pwr");
	if (IS_ERR(audio_regulator))
		pr_err("%s : regulator_get error\n", AUDIO_NAME);

	err = regulator_set_voltage(audio_regulator, REGU_MIN_VOL,
						REGU_MAX_VOL);
	if (err)
		pr_err("%s: regulator_set 3V error\n", AUDIO_NAME);

	regulator_enable(audio_regulator);
#endif
	ret =  snd_soc_register_codec(&i2c->dev,
		&soc_codec_dev_aic31xx, tlv320aic31xx_dai, \
		ARRAY_SIZE(tlv320aic31xx_dai));


	return ret;
}

/*
 * aic31xx_codec_remove
 * This function is to unregister the Audio Codec from the ALSA Core Layer.
 */
static int __devexit aic31xx_codec_remove(struct i2c_client *i2c)
{
	snd_soc_unregister_codec(&i2c->dev);
#ifdef AIC31xx_REGULATO
	regulator_disable(audio_regulator);
	regulator_put(audio_regulator);
#endif
	kfree(aic_priv);

	return 0;
}

/*
 * @struct tlv320aic31xx_i2c_driver
 *
 * Platform Driver structure used to describe the Driver structure.
 */
static const struct i2c_device_id aic31xx_id[] = {
	{"tlv320aic3110", 0},
	{}
};
MODULE_DEVICE_TABLE(i2c, aic31xx_id);

static struct i2c_driver tlv320aic31xx_i2c_driver = {
	.driver = {
		.name = "tlv320aic3110-codec",
		.owner = THIS_MODULE,
	},
	.probe = tlv320aic31xx_codec_probe,
	.remove = __devexit_p(aic31xx_codec_remove),
	.id_table = aic31xx_id,
};

module_i2c_driver(tlv320aic31xx_i2c_driver);

MODULE_AUTHOR("TOSHIBA Corporation");
MODULE_DESCRIPTION("ASoC TLV320AIC31xx codec driver");
MODULE_LICENSE("GPL v2");
