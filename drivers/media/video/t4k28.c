/*
 * linux/drivers/media/video/t4k28.c
 *
 * (C) Copyright TOSHIBA Corporation
 * Semiconductor & Storage Products Company 2014
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

#define DEBUG_T4K28

#include <linux/delay.h>
#include <linux/i2c.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/v4l2-mediabus.h>
#include <linux/videodev2.h>
#include <linux/vmalloc.h>
#include <linux/platform_device.h>
#include <media/soc_camera.h>
#include <media/v4l2-chip-ident.h>
#include <media/v4l2-common.h>


#define T4K28_MAX_WIDTH		1600
#define T4K28_MAX_HEIGHT	1200


#define T4K28_CSI2_MBPS		350

#define FRAME_RATE_MAX		60

/*  T4K28 Register Address */
#define REG_0x3011	(0x3011)
#define REG_0x3401	(0x3401)
#define REG_0x3402	(0x3402)
#define REG_0x3441	(0x3441)
#define REG_0x3500	(0x3500)
#define REG_0x3506	(0x3506)
#define	REG_0x3507	(0x3507)
#define REG_0x3524	(0x3524)
#define REG_0x3525	(0x3525)
#define REG_0x3526	(0x3526)
#define REG_0x3527	(0x3527)
#define REG_0x3528	(0x3528)
#define REG_0x3529	(0x3529)
#define REG_0x350A	(0x350A)
#define REG_0x350B	(0x350B)

/* Number of Control factors suppoted */
#define NUM_CTRL_SUPPORT	12

/* Max register value */
#define T4K28_MAX_REG_VAL	(0xFF)


/* Default values */
#define DEF_RED			0xFF
#define DEF_BLUE		0xFF
#define DEF_GREEN		0xFF
#define DEF_GAIN		0x00
#define DEF_AEC			0x00
#define DEF_AUTO		0x01
#define DEF_MANUAL		0x00
#define DEF_CONTRAST	0x89


#define T4K28_CID_GREEN_BALANCE	(V4L2_CTRL_CLASS_CAMERA | 0x1001)

struct t4k28_priv {
	struct soc_camera_link		link;
	struct platform_device		soc_cam_dev;
	struct platform_device		*pdev;

	struct soc_camera_device	*icd;
	struct v4l2_subdev		subdev;

	struct v4l2_ctrl_handler hdl;
	struct {
		/* exposure/autoexposure cluster */
		struct v4l2_ctrl *autoexposure;
		struct v4l2_ctrl *exposure;
	};
	struct {
		/* gain/autogain cluster */
		struct v4l2_ctrl *autogain;
		struct v4l2_ctrl *gain;
	};
	struct {
		/* blue/red/autowhitebalance cluster */
		struct v4l2_ctrl *autowb;
		struct v4l2_ctrl *red;
		struct v4l2_ctrl *blue;
		struct v4l2_ctrl *green;
	};

	struct v4l2_ctrl *vflip;
	struct v4l2_ctrl *hflip;
	struct v4l2_ctrl *colorfx;
	struct v4l2_ctrl *contrast;
	int				width;
	int				height;
	int				current_enable;
	int				rate_div;

	unsigned int readregaddr;

	struct mutex lock;
};

/* Register */
struct t4k28_reg {
	u16	reg;
	u8	val;
};

/* Format */
static enum v4l2_mbus_pixelcode t4k28_codes[] = {
	V4L2_MBUS_FMT_UYVY8_2X8,
};

/* Supports only 60fps ,30fps and 15fps */
static int t4k28_rate_div[] = { 1, 2, 4};

static const struct {
	u32 width;
	u32 height;
} t4k28_framesizes[] = {
	{1600, 1200},
	{1280, 720},
	{ 800, 600},
	{ 640, 480},
};

/* Capture initialization set registers */
static struct t4k28_reg t4k28_init_set_regs[] = {
{0x3000, 0x0000},
{0x3001, 0x0000},
{0x3005, 0x0000},
{0x3010, 0x0000},
{0x3011, 0x0000},
{0x3012, 0x0002},
{0x3014, 0x0000},
{0x3015, 0x0005},
{0x3016, 0x001C},
{0x3017, 0x0002},
{0x3018, 0x0070},
{0x3019, 0x0000},
{0x301A, 0x0020},
{0x301B, 0x0010},
{0x301C, 0x0001},
{0x3020, 0x0003},
{0x3021, 0x0020},
{0x3022, 0x0002},
{0x3023, 0x0058},
{0x3025, 0x0000},
{0x3026, 0x0000},
{0x3027, 0x0000},
{0x302C, 0x0000},
{0x302D, 0x0000},
{0x302E, 0x0000},
{0x302F, 0x0000},
{0x3030, 0x0000},
{0x3031, 0x0002},
{0x3032, 0x0000},
{0x3033, 0x0083},
{0x3034, 0x0001},
{0x3037, 0x0000},
{0x303C, 0x0080},
{0x303E, 0x0001},
{0x303F, 0x0000},
{0x3040, 0x0080},
{0x3044, 0x0002},
{0x3045, 0x0004},
{0x3046, 0x0000},
{0x3047, 0x0083},
{0x3048, 0x0001},
{0x3049, 0x0001},
{0x304A, 0x0008},
{0x304B, 0x000A},
{0x304C, 0x0000},
{0x304E, 0x0001},
{0x3050, 0x0060},
{0x3051, 0x0082},
{0x3052, 0x0010},
{0x3053, 0x0000},
{0x3055, 0x0084},
{0x3056, 0x0002},
{0x3059, 0x0018},
{0x305A, 0x0000},
{0x3068, 0x00F0},
{0x3069, 0x00F0},
{0x306C, 0x0006},
{0x306D, 0x0040},
{0x306E, 0x0000},
{0x306F, 0x0004},
{0x3070, 0x0006},
{0x3071, 0x0043},
{0x3072, 0x0004},
{0x3073, 0x00B0},
{0x3074, 0x0000},
{0x3075, 0x0004},
{0x3076, 0x0004},
{0x3077, 0x00B3},
{0x307F, 0x0003},
{0x3080, 0x0070},
{0x3081, 0x0028},
{0x3082, 0x0060},
{0x3083, 0x0048},
{0x3084, 0x0040},
{0x3085, 0x0028},
{0x3086, 0x00F8},
{0x3087, 0x0038},
{0x3088, 0x0003},
{0x3089, 0x0003},
{0x308A, 0x0012},
{0x3091, 0x0000},
{0x3095, 0x0078},
{0x3097, 0x0000},
{0x3098, 0x0040},
{0x309A, 0x0000},
{0x309B, 0x0000},
{0x309D, 0x0001},
{0x309E, 0x0000},
{0x309F, 0x0000},
{0x30A0, 0x0000},
{0x30A1, 0x0000},
{0x30A2, 0x00A7},
{0x30A3, 0x0020},
{0x30A4, 0x00FF},
{0x30A5, 0x0080},
{0x30A6, 0x00FF},
{0x30A7, 0x0000},
{0x30A8, 0x0001},
{0x30F1, 0x0000},
{0x30F2, 0x0000},
{0x30FE, 0x0080},
{0x3100, 0x00D2},
{0x3101, 0x00D3},
{0x3102, 0x0045},
{0x3103, 0x0080},
{0x3104, 0x0031},
{0x3105, 0x0002},
{0x3106, 0x0023},
{0x3107, 0x0020},
{0x3108, 0x007B},
{0x3109, 0x0080},
{0x310A, 0x0000},
{0x310B, 0x0000},
{0x3110, 0x0011},
{0x3111, 0x0011},
{0x3112, 0x0000},
{0x3113, 0x0000},
{0x3114, 0x0010},
{0x3115, 0x0022},
{0x3120, 0x0008},
{0x3121, 0x0013},
{0x3122, 0x0033},
{0x3123, 0x000E},
{0x3124, 0x0026},
{0x3125, 0x0000},
{0x3126, 0x000C},
{0x3127, 0x0008},
{0x3128, 0x0080},
{0x3129, 0x0065},
{0x312A, 0x0027},
{0x312B, 0x0077},
{0x312C, 0x0077},
{0x312D, 0x001A},
{0x312E, 0x00B8},
{0x312F, 0x0038},
{0x3130, 0x0080},
{0x3131, 0x0033},
{0x3132, 0x0063},
{0x3133, 0x0000},
{0x3134, 0x00DD},
{0x3135, 0x0007},
{0x3136, 0x00B7},
{0x3137, 0x0011},
{0x3138, 0x000B},
{0x313B, 0x000A},
{0x313C, 0x0005},
{0x313D, 0x0001},
{0x313E, 0x0062},
{0x313F, 0x0085},
{0x3140, 0x0001},
{0x3141, 0x0040},
{0x3142, 0x0080},
{0x3143, 0x0022},
{0x3144, 0x003E},
{0x3145, 0x0032},
{0x3146, 0x002E},
{0x3147, 0x0023},
{0x3148, 0x0022},
{0x3149, 0x0011},
{0x314A, 0x006B},
{0x314B, 0x0030},
{0x314C, 0x0069},
{0x314D, 0x0080},
{0x314E, 0x0031},
{0x314F, 0x0032},
{0x3150, 0x0032},
{0x3151, 0x0003},
{0x3152, 0x000C},
{0x3153, 0x00B3},
{0x3154, 0x0020},
{0x3155, 0x0013},
{0x3156, 0x0066},
{0x3157, 0x0002},
{0x3158, 0x0003},
{0x3159, 0x0001},
{0x315A, 0x0016},
{0x315B, 0x0010},
{0x315C, 0x0000},
{0x315D, 0x0044},
{0x315E, 0x001B},
{0x315F, 0x0052},
{0x3160, 0x0000},
{0x3161, 0x0003},
{0x3162, 0x0000},
{0x3163, 0x00FF},
{0x3164, 0x0000},
{0x3165, 0x0001},
{0x3166, 0x0000},
{0x3167, 0x00FF},
{0x3168, 0x0001},
{0x3169, 0x0000},
{0x3180, 0x0000},
{0x3181, 0x0020},
{0x3182, 0x0040},
{0x3183, 0x0096},
{0x3184, 0x0040},
{0x3185, 0x008F},
{0x3186, 0x0031},
{0x3187, 0x0006},
{0x3188, 0x000C},
{0x3189, 0x0044},
{0x318A, 0x0042},
{0x318B, 0x000B},
{0x318C, 0x0011},
{0x318D, 0x00AA},
{0x318E, 0x0040},
{0x318F, 0x0030},
{0x3190, 0x0003},
{0x3191, 0x0001},
{0x3192, 0x0002},
{0x3193, 0x0003},
{0x3194, 0x0000},
{0x3195, 0x0000},
{0x3196, 0x0000},
{0x3197, 0x00DE},
{0x3198, 0x0000},
{0x3199, 0x0000},
{0x319A, 0x0000},
{0x319B, 0x0000},
{0x319C, 0x0016},
{0x319D, 0x000A},
{0x31A0, 0x00BF},
{0x31A1, 0x00FF},
{0x31A2, 0x0011},
{0x31B0, 0x0000},
{0x31B1, 0x003F},
{0x31B2, 0x001A},
{0x31B3, 0x00C1},
{0x31B4, 0x0003},
{0x31B5, 0x006E},
{0x31B6, 0x001B},
{0x31B7, 0x0005},
{0x31B8, 0x0000},
{0x31B9, 0x0002},
{0x31BA, 0x003F},
{0x31BB, 0x00FF},
{0x3300, 0x00FF},
{0x3301, 0x0035},
{0x3303, 0x0040},
{0x3304, 0x0000},
{0x3305, 0x0000},
{0x3306, 0x0030},
{0x3307, 0x0000},
{0x3308, 0x0087},
{0x330A, 0x0060},
{0x330B, 0x0056},
{0x330D, 0x0079},
{0x330E, 0x00FF},
{0x330F, 0x00FF},
{0x3310, 0x00FF},
{0x3311, 0x007F},
{0x3312, 0x000F},
{0x3313, 0x000F},
{0x3314, 0x0002},
{0x3315, 0x00FF},
{0x3316, 0x0018},
{0x3317, 0x0008},
{0x3318, 0x0060},
{0x3319, 0x0090},
{0x331B, 0x0000},
{0x331C, 0x0000},
{0x331D, 0x0000},
{0x331E, 0x0000},
{0x3322, 0x0020},
{0x3323, 0x0020},
{0x3324, 0x0000},
{0x3325, 0x0060},
{0x3327, 0x0000},
{0x3328, 0x0000},
{0x3329, 0x0080},
{0x332A, 0x0080},
{0x332B, 0x0080},
{0x332C, 0x0080},
{0x332D, 0x0080},
{0x332E, 0x0080},
{0x332F, 0x0007},
{0x3330, 0x0008},
{0x3331, 0x0010},
{0x3332, 0x0000},
{0x3333, 0x0000},
{0x3334, 0x0008},
{0x3335, 0x0002},
{0x3336, 0x0004},
{0x3337, 0x000B},
{0x3338, 0x0005},
{0x3339, 0x000C},
{0x333A, 0x000C},
{0x333B, 0x0088},
{0x333C, 0x00D4},
{0x333D, 0x0054},
{0x333E, 0x0038},
{0x333F, 0x0072},
{0x3340, 0x0022},
{0x3341, 0x0068},
{0x3342, 0x00B4},
{0x3343, 0x0045},
{0x3344, 0x00A0},
{0x3345, 0x00F0},
{0x3346, 0x006C},
{0x3347, 0x0000},
{0x3348, 0x0000},
{0x3349, 0x0000},
{0x334A, 0x0000},
{0x334B, 0x0000},
{0x334C, 0x0000},
{0x334D, 0x0058},
{0x334E, 0x0000},
{0x334F, 0x0098},
{0x3350, 0x0001},
{0x335F, 0x0000},
{0x3360, 0x0000},
{0x3400, 0x00A4},
{0x3401, 0x002A},
{0x3402, 0x0000},
{0x3403, 0x0006},
{0x3404, 0x003A},
{0x3405, 0x00E3},
{0x3406, 0x0022},
{0x3407, 0x0025},
{0x3408, 0x0017},
{0x3409, 0x005C},
{0x340A, 0x0020},
{0x340B, 0x0020},
{0x340C, 0x003B},
{0x340D, 0x002E},
{0x340E, 0x0026},
{0x340F, 0x003F},
{0x3410, 0x0034},
{0x3411, 0x002D},
{0x3412, 0x0028},
{0x3413, 0x0047},
{0x3414, 0x003E},
{0x3415, 0x006A},
{0x3416, 0x005A},
{0x3417, 0x0050},
{0x3418, 0x0048},
{0x3419, 0x0042},
{0x341B, 0x0000},
{0x341C, 0x0040},
{0x341D, 0x0063},
{0x341E, 0x0020},
{0x341F, 0x0088},
{0x3420, 0x006E},
{0x3421, 0x0000},
{0x3422, 0x00B0},
{0x3423, 0x000F},
{0x3424, 0x000F},
{0x3425, 0x000F},
{0x3426, 0x000F},
{0x342B, 0x0020},
{0x342C, 0x0010},
{0x342D, 0x0070},
{0x342E, 0x0090},
{0x342F, 0x0070},
{0x3430, 0x0090},
{0x3431, 0x0020},
{0x3432, 0x0020},
{0x3433, 0x0000},
{0x3434, 0x0000},
{0x3435, 0x0000},
{0x3436, 0x0000},
{0x343F, 0x00C0},
{0x3440, 0x00C0},
{0x3441, 0x0089},
{0x3442, 0x0000},
{0x3443, 0x0000},
{0x3444, 0x0000},
{0x3446, 0x0000},
{0x3447, 0x0000},
{0x3448, 0x0000},
{0x3449, 0x0000},
{0x344A, 0x0000},
{0x344B, 0x0000},
{0x344C, 0x0020},
{0x344D, 0x00FF},
{0x344E, 0x000F},
{0x344F, 0x0020},
{0x3450, 0x0080},
{0x3451, 0x000F},
{0x3452, 0x0055},
{0x3453, 0x0049},
{0x3454, 0x006A},
{0x3455, 0x0093},
{0x345C, 0x0000},
{0x345D, 0x0000},
{0x345E, 0x0000},
{0x3500, 0x00C1},
{0x3501, 0x0001},
{0x3502, 0x0000},
{0x3503, 0x002C},
{0x3504, 0x0001},
{0x3505, 0x0000},
{0x3506, 0x0004},
{0x3507, 0x00D0},
{0x3508, 0x0000},
{0x3509, 0x00BD},
{0x350A, 0x0000},
{0x350B, 0x0020},
{0x350C, 0x0000},
{0x350D, 0x0015},
{0x350E, 0x0015},
{0x350F, 0x0051},
{0x3510, 0x0050},
{0x3511, 0x0010},
{0x3512, 0x0010},
{0x3513, 0x0000},
{0x3514, 0x0000},
{0x3515, 0x0010},
{0x3516, 0x0010},
{0x3517, 0x0010},
{0x3518, 0x0000},
{0x3519, 0x00FF},
{0x351A, 0x00C0},
{0x351B, 0x0000},
{0x351C, 0x006C},
{0x351D, 0x0078},
{0x351E, 0x00D6},
{0x351F, 0x0080},
{0x3520, 0x0026},
{0x3521, 0x0002},
{0x3522, 0x0008},
{0x3523, 0x000C},
{0x3524, 0x0001},
{0x3525, 0x0072},
{0x3526, 0x003D},
{0x3527, 0x0000},
{0x3528, 0x0055},
{0x3529, 0x005A},
{0x352A, 0x0020},
{0x352B, 0x0020},
{0x352C, 0x0020},
{0x352D, 0x0020},
{0x352E, 0x0028},
{0x352F, 0x00D0},
{0x3530, 0x0032},
{0x3531, 0x0028},
{0x3532, 0x0040},
{0x3533, 0x0038},
{0x3534, 0x0000},
{0x3535, 0x0000},
{0x3536, 0x0000},
{0x3537, 0x0000},
{0x3538, 0x0000},
{0x3539, 0x0000},
{0x353A, 0x0000},
{0x353B, 0x0000},
{0x353C, 0x0000},
{0x353D, 0x0000},
{0x353E, 0x0000},
{0x353F, 0x0000},
{0x3540, 0x0000},
{0x3541, 0x0000},
{0x3542, 0x0000},
{0x3543, 0x0000},
{0x3544, 0x0000},
{0x3545, 0x0000},
{0x3546, 0x00C8},
{0x3547, 0x000A},
{0x3548, 0x0084},
{0x3549, 0x0000},
{0x354A, 0x0000},
{0x354B, 0x0000},
{0x354C, 0x0000},
{0x354D, 0x0000},
{0x354E, 0x0000},
{0x354F, 0x0000},
{0x3550, 0x0000},
{0x3551, 0x0003},
{0x3552, 0x0028},
{0x3553, 0x0000},
{0x3554, 0x0060},
{0x3555, 0x00F0},
{0x355D, 0x0080},
{0x355E, 0x00FD},
{0x355F, 0x0003},
{0x3560, 0x0098},
{0x3561, 0x0000},
{0x3562, 0x002C},
{0x3563, 0x0000},
{0x3564, 0x0056},
{0x3565, 0x0000},
{0x3566, 0x0092},
{0x3567, 0x002E},
{0x3568, 0x0000},
{0x3569, 0x0000},
{0x356A, 0x0000},
{0x356B, 0x0000},
{0x356C, 0x00FF},
{0x356D, 0x00FF},
{0x356E, 0x0001},
{0x356F, 0x00B7},
{0x3570, 0x0001},
{0x3571, 0x0000},
{0x3572, 0x0001},
{0x3573, 0x0012},
{0x3574, 0x0001},
{0x3575, 0x0000},
{0x3576, 0x003C},
{0x3577, 0x002A},
{0x3578, 0x00DC},
{0x3579, 0x0009},
{0x357A, 0x0099},
{0x357B, 0x0000},
{0x357C, 0x00E0},
{0x357D, 0x0000},
{0x3900, 0x0000},
{0x3901, 0x0007},
{0x3902, 0x0000},
{0x3903, 0x0000},
{0x3904, 0x0000},
{0x3905, 0x0000},
{0x3906, 0x0000},
{0x3907, 0x0000},
{0x3908, 0x0000},
{0x3909, 0x0000},
{0x390A, 0x0000},
{0x390B, 0x0000},
{0x390C, 0x0000},
{0x30F0, 0x0000},
{0x3010, 0x0001},
};

/* R esolution 640x480@60 */
static struct t4k28_reg t4k28_vga_60fps_regs[] = {
{0x3012, 0x0003},
{0x3015, 0x0005},
{0x3016, 0x001C},
{0x3017, 0x0001},
{0x3018, 0x003A},
{0x3019, 0x0000},
{0x301A, 0x0020},
{0x301B, 0x0010},
{0x301C, 0x0001},
{0x3020, 0x0002},
{0x3021, 0x0080},
{0x3022, 0x0001},
{0x3023, 0x00E0},
{0x3048, 0x0001},
{0x3049, 0x0001},
{0x3012, 0x0002},
};

/* Resolution 640x480@30 */
static struct t4k28_reg t4k28_vga_30fps_regs[] = {
{0x3012, 0x0003},
{0x3015, 0x0005},
{0x3016, 0x001C},
{0x3017, 0x0002},
{0x3018, 0x0070},
{0x3019, 0x0000},
{0x301A, 0x0020},
{0x301B, 0x0010},
{0x301C, 0x0001},
{0x3020, 0x0002},
{0x3021, 0x0080},
{0x3022, 0x0001},
{0x3023, 0x00E0},
{0x3048, 0x0001},
{0x3049, 0x0001},
{0x3012, 0x0002},
};

/* Resolution 800x600  */
static struct t4k28_reg t4k28_600p_regs[] = {
{0x3012, 0x0003},
{0x3015, 0x0005},
{0x3016, 0x001C},
{0x3017, 0x0002},
{0x3018, 0x0070},
{0x3019, 0x0000},
{0x301A, 0x0020},
{0x301B, 0x0010},
{0x301C, 0x0001},
{0x3020, 0x0003},
{0x3021, 0x0020},
{0x3022, 0x0002},
{0x3023, 0x0058},
{0x3048, 0x0001},
{0x3049, 0x0001},
{0x3012, 0x0002},
};

/* Resolution 1280x720 */
static struct t4k28_reg t4k28_720p_regs[] = {
{0x3012, 0x0003},
{0x3015, 0x0005},
{0x3016, 0x001C},
{0x3017, 0x0002},
{0x3018, 0x0070},
{0x3019, 0x0000},
{0x301A, 0x0010},
{0x301B, 0x0000},
{0x301C, 0x0001},
{0x3020, 0x0005},
{0x3021, 0x0000},
{0x3022, 0x0002},
{0x3023, 0x00D0},
{0x3048, 0x0001},
{0x3049, 0x0001},
{0x3012, 0x0002},
};

/* Resolution 1600x1200  */
static struct t4k28_reg t4k28_1200p_regs[] = {
{0x3012, 0x0003},
{0x3015, 0x000A},
{0x3016, 0x0038},
{0x3017, 0x0002},
{0x3018, 0x0070},
{0x3019, 0x0000},
{0x301A, 0x0010},
{0x301B, 0x0000},
{0x301C, 0x0001},
{0x3020, 0x0006},
{0x3021, 0x0040},
{0x3022, 0x0004},
{0x3023, 0x00B0},
{0x3048, 0x0001},
{0x3049, 0x0001},
{0x3012, 0x0002},
};

/* start streaming */
static struct t4k28_reg t4k28_start_regs[] = {
{0x3010, 0x01},
};

/* stop streaming */
static struct t4k28_reg t4k28_stop_regs[] = {
{0x3010, 0x00},
};

/* ----------------------------------------------------------------------- */
static int t4k28_reg_read(struct i2c_client *client, u16 sub_addr)
{
	struct i2c_msg msg[2];
	u8 buf;
	int ret;

	sub_addr = swab16(sub_addr);

	msg[0].addr  = client->addr;
	msg[0].flags = 0;
	msg[0].len   = 2;
	msg[0].buf   = (u8 *)&sub_addr;
	msg[1].addr  = client->addr;
	msg[1].flags = I2C_M_RD;
	msg[1].len   = 1;
	msg[1].buf   = &buf;

	ret = i2c_transfer(client->adapter, msg, 2);
	if (ret < 0)
		return ret;

	ret = buf;
	return ret;
}

static int t4k28_reg_write(struct i2c_client *client, u16 sub_addr, u8 data)
{
	struct i2c_msg msg;
	u8 buf[3];
	int ret;

	buf[0] = (sub_addr >> 8) & 0xff;
	buf[1] = sub_addr & 0xff;
	buf[2] = data;

	msg.addr  = client->addr;
	msg.flags = 0;
	msg.len   = 3;
	msg.buf   = buf;

	ret = i2c_transfer(client->adapter, &msg, 1);
	if (ret >= 0)
		ret = 0;

	return ret;
}

static int t4k28_write_regs(struct i2c_client *client,
			struct t4k28_reg *regs, int num)
{
	int i, ret;

	for (i = 0; i < num; i++) {
		ret = t4k28_reg_write(client,
				regs[i].reg, regs[i].val);
		if (ret < 0) {
			dev_err(&client->dev,
				"w_err addr=0x%x ret=%d\n", regs[i].reg, ret);
			return ret;
		}
	}
	return 0;
}

#define WRITE_REGS(x)	t4k28_write_regs(client, x, ARRAY_SIZE(x))

static int t4k28_capture_start(struct t4k28_priv *priv)
{
	struct i2c_client *client = v4l2_get_subdevdata(&priv->subdev);

	WRITE_REGS(t4k28_init_set_regs);

	switch (priv->width) {

	/* 1280x720 */
	case 1280:
		if (priv->height == 720)
			WRITE_REGS(t4k28_720p_regs);
		break;

	/* 800x600 */
	case 800:
		if (priv->height == 600)
			WRITE_REGS(t4k28_600p_regs);
		break;

	/* 1600x1200 */
	case 1600:
		if (priv->height == 1200)
			WRITE_REGS(t4k28_1200p_regs);
		break;

	/* 640x480 */
	default:
		if (priv->rate_div == 1)
			WRITE_REGS(t4k28_vga_60fps_regs);
		else
			WRITE_REGS(t4k28_vga_30fps_regs);
		break;
	}

	WRITE_REGS(t4k28_start_regs);

	return 0;
}

static int t4k28_capture_stop(struct t4k28_priv *priv)
{
	struct i2c_client *client = v4l2_get_subdevdata(&priv->subdev);

	WRITE_REGS(t4k28_stop_regs);

	return 0;
}

/* ----------------------------------------------------------------------- */

static int t4k28_s_power(struct v4l2_subdev *sd, int on)
{
	return 0;
}

#ifdef CONFIG_VIDEO_ADV_DEBUG
static int t4k28_get_register(struct v4l2_subdev *sd,
			       struct v4l2_dbg_register *reg)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int ret;

	ret = t4k28_reg_read(client, reg->reg);
	if (ret < 0)
		return ret;

	reg->val = ret;

	return 0;
}

static int t4k28_set_register(struct v4l2_subdev *sd,
			       struct v4l2_dbg_register *reg)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	return t4k28_reg_write(client, reg->reg, reg->val);
}
#endif

/* subdev core ops */
static struct v4l2_subdev_core_ops t4k28_core_ops = {
	.s_power		= t4k28_s_power,
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.g_register		= t4k28_get_register,
	.s_register		= t4k28_set_register,
#endif
};

/* ----------------------------------------------------------------------- */

/* Start/Stop streaming from the device */
static int t4k28_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct t4k28_priv *priv =
			container_of(sd, struct t4k28_priv, subdev);

	if (priv->current_enable == enable)
		return 0;

	priv->current_enable = enable;

	if (enable) {
		dev_dbg(sd->v4l2_dev->dev, "%s: Start Streaming\n", __func__);
		/* start camera module */
		t4k28_capture_start(priv);
	} else {
		dev_dbg(sd->v4l2_dev->dev, "%s: Stop Streaming\n", __func__);
		/* stop camera module */
		t4k28_capture_stop(priv);
	}
	return 0;
}

static int t4k28_cropcap(struct v4l2_subdev *sd, struct v4l2_cropcap *a)
{
	a->bounds.left			= 0;
	a->bounds.top			= 0;
	a->bounds.width			= T4K28_MAX_WIDTH;
	a->bounds.height		= T4K28_MAX_HEIGHT;
	a->defrect			= a->bounds;
	a->type				= V4L2_BUF_TYPE_VIDEO_CAPTURE;
	a->pixelaspect.numerator	= 1;
	a->pixelaspect.denominator	= 1;

	return 0;
}

static int t4k28_g_crop(struct v4l2_subdev *sd, struct v4l2_crop *a)
{
	a->c.left		= 0;
	a->c.top		= 0;
	a->c.width		= T4K28_MAX_WIDTH;
	a->c.height		= T4K28_MAX_HEIGHT;
	a->type			= V4L2_BUF_TYPE_VIDEO_CAPTURE;

	return 0;
}

static int t4k28_s_crop(struct v4l2_subdev *sd, struct v4l2_crop *a)
{
	return 0;
}

static int t4k28_enum_fmt(struct v4l2_subdev *sd, unsigned int index,
			   enum v4l2_mbus_pixelcode *code)
{
	if (index >= ARRAY_SIZE(t4k28_codes))
		return -EINVAL;

	*code = t4k28_codes[index];

	return 0;
}

/* select nearest higher resolution for capture */
static void t4k28_res_roundup(u32 *width, u32 *height)
{
	int i;

	for (i = ARRAY_SIZE(t4k28_framesizes) - 1; i >= 0; i--) {
		if (t4k28_framesizes[i].width >= *width &&
				t4k28_framesizes[i].height >= *height) {
			*width = t4k28_framesizes[i].width;
			*height = t4k28_framesizes[i].height;
			return;
		}
	}

	*width = t4k28_framesizes[3].width;
	*height = t4k28_framesizes[3].height;
}

static int t4k28_try_fmt(struct v4l2_subdev *sd,
			  struct v4l2_mbus_framefmt *mf)
{
	t4k28_res_roundup(&mf->width, &mf->height);

	mf->code	= V4L2_MBUS_FMT_UYVY8_2X8;
	mf->colorspace	= V4L2_COLORSPACE_SMPTE170M;
	mf->field	= V4L2_FIELD_NONE;

	return 0;
}

static int t4k28_g_fmt(struct v4l2_subdev *sd,
			struct v4l2_mbus_framefmt *mf)
{
	/* default VGA */
	mf->width	= 640;
	mf->height	= 480;
	mf->code	= V4L2_MBUS_FMT_UYVY8_2X8;
	mf->colorspace	= V4L2_COLORSPACE_SMPTE170M;
	mf->field	= V4L2_FIELD_NONE;

	return 0;
}

/* set the format we will capture in */
static int t4k28_s_fmt(struct v4l2_subdev *sd,
			struct v4l2_mbus_framefmt *mf)
{
	struct t4k28_priv *priv =
			container_of(sd, struct t4k28_priv, subdev);
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

	t4k28_res_roundup(&mf->width, &mf->height);

	mf->code	= code;
	mf->colorspace	= cspace;

	priv->width = mf->width;
	priv->height = mf->height;

	return ret;
}

/* Request bus settings on camera side */
static int t4k28_g_mbus_config(struct v4l2_subdev *sd,
				struct v4l2_mbus_config *cfg)
{
	cfg->flags = V4L2_MBUS_CSI2_1_LANE | V4L2_MBUS_CSI2_CHANNEL_0 |
			V4L2_MBUS_CSI2_CONTINUOUS_CLOCK;
	cfg->flags |= V4L2_MBUS_CSI2_SET_MBPS(T4K28_CSI2_MBPS);
	cfg->type = V4L2_MBUS_CSI2;

	return 0;
}

static int t4k28_g_parm(struct v4l2_subdev *sd, struct v4l2_streamparm *parms)
{
	struct t4k28_priv *priv =
			container_of(sd, struct t4k28_priv, subdev);
	struct v4l2_captureparm *cp = &parms->parm.capture;

	if (parms->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	memset(cp, 0, sizeof(*cp));
	cp->capability = V4L2_CAP_TIMEPERFRAME;
	cp->timeperframe.numerator = priv->rate_div;
	cp->timeperframe.denominator = FRAME_RATE_MAX;

	return 0;
}

static int t4k28_s_parm(struct v4l2_subdev *sd, struct v4l2_streamparm *parms)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct t4k28_priv *priv =
			container_of(sd, struct t4k28_priv, subdev);
	struct v4l2_captureparm *cp = &parms->parm.capture;
	struct v4l2_fract *tpf = &cp->timeperframe;
	int i, div;

	if (parms->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	if (tpf->numerator == 0 || tpf->denominator == 0)
		div = 1;  /* Reset to full rate */
	else
		div = (tpf->numerator * FRAME_RATE_MAX) / tpf->denominator;

	for (i = 0; i < ARRAY_SIZE(t4k28_rate_div) - 1; i++) {
		if (t4k28_rate_div[i] >= div)
			break;
	}

	priv->rate_div = t4k28_rate_div[i];
	tpf->numerator = t4k28_rate_div[i];

	tpf->denominator = FRAME_RATE_MAX;

	dev_dbg(&client->dev, "Set Frame interval: %u/%u s\n",
			tpf->numerator, tpf->denominator);

	return 0;
}

static int t4k28_enum_frameintervals(struct v4l2_subdev *sd,
		struct v4l2_frmivalenum *interval)
{
	if (interval->index >= ARRAY_SIZE(t4k28_rate_div))
		return -EINVAL;
	interval->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	interval->discrete.numerator = t4k28_rate_div[interval->index];
	interval->discrete.denominator = FRAME_RATE_MAX;
	return 0;
}

static int t4k28_enum_framesizes(struct v4l2_subdev *sd,
		struct v4l2_frmsizeenum *fsize)
{
	if (fsize->index >= ARRAY_SIZE(t4k28_framesizes))
		return -EINVAL;

	fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	fsize->discrete.width = t4k28_framesizes[fsize->index].width;
	fsize->discrete.height = t4k28_framesizes[fsize->index].height;

	return 0;
}
/* Video ops internal structure of subdev ops */
static struct v4l2_subdev_video_ops t4k28_video_ops = {
	.s_stream	= t4k28_s_stream,

	.cropcap	= t4k28_cropcap,
	.g_crop		= t4k28_g_crop,
	.s_crop		= t4k28_s_crop,

	.enum_mbus_fmt	= t4k28_enum_fmt,
	.try_mbus_fmt	= t4k28_try_fmt,
	.g_mbus_fmt	= t4k28_g_fmt,
	.s_mbus_fmt	= t4k28_s_fmt,
	.g_mbus_config	= t4k28_g_mbus_config,

	.g_parm		= t4k28_g_parm,
	.s_parm		= t4k28_s_parm,
	.enum_frameintervals = t4k28_enum_frameintervals,
	.enum_framesizes = t4k28_enum_framesizes,
};

/* T4K28 Subdev ops */
static struct v4l2_subdev_ops t4k28_subdev_ops = {
	.core	= &t4k28_core_ops,
	.video	= &t4k28_video_ops,
};

static struct t4k28_priv *to_t4k28(const struct i2c_client *client)
{
	return container_of(i2c_get_clientdata(client),
				struct t4k28_priv, subdev);
}

static unsigned long t4k28_strtoul(const char *buf, size_t count, size_t *cnt)
{
	unsigned long val;
	char *endp;

	val = simple_strtoul(buf, &endp, 16) ;
	*cnt = 0;
	if (val <= 0xFFFF)
		*cnt = (size_t)(endp - buf);
	if ((*cnt) && (count == *cnt+1) && (buf[*cnt] == '\n'))
		*cnt += 1;
	/*pr_info("%s: val=%d cnt=%d\n", __func__, val, *cnt);*/
	return val;
}


static ssize_t t4k28_sysfs_read_reg_show(struct device *dev,
	struct device_attribute *dev_attr, char *buf)
{
	int ret;
	ssize_t count = 0;
	struct i2c_client *client = to_i2c_client(dev);
	struct t4k28_priv *priv = to_t4k28(client);

	mutex_lock(&priv->lock);

	ret = t4k28_reg_read(client, priv->readregaddr);
	if (ret < 0) {
		mutex_unlock(&priv->lock);
		return ret;
	}
	count = sprintf(buf, "Reg Addr:0x%x,Val: 0x%x\n",
		priv->readregaddr, ret);

	mutex_unlock(&priv->lock);

	return count;
}


static ssize_t t4k28_sysfs_read_reg_store(struct device *dev,
	struct device_attribute *dev_attr, const char *buf, size_t count)
{
	int regval;
	ssize_t cnt;

	struct i2c_client *client = to_i2c_client(dev);
	struct t4k28_priv *priv = to_t4k28(client);

	mutex_lock(&priv->lock);

	if (buf == NULL) {
		mutex_unlock(&priv->lock);
		return -EINVAL;
	}

	regval = t4k28_strtoul(buf, count, &cnt);
	priv->readregaddr =  regval;

	mutex_unlock(&priv->lock);
	return count;
}


static ssize_t t4k28_sysfs_write_reg_store(struct device *dev,
	struct device_attribute *dev_attr, const char *buf, size_t count)
{
	int ret, regaddr, regval;
	ssize_t cnt;
	char *value = NULL;

	struct i2c_client *client = to_i2c_client(dev);
	struct t4k28_priv *priv = to_t4k28(client);

	mutex_lock(&priv->lock);

	if (buf == NULL) {
		mutex_unlock(&priv->lock);
		return -EINVAL;
	}

	value = strsep((char **)&buf, ",");

	if (value == NULL) {
		mutex_unlock(&priv->lock);
		return -EINVAL;
	}
	if (buf == NULL) {
		mutex_unlock(&priv->lock);
		return -EINVAL;
	}


	regaddr = t4k28_strtoul(value, count, &cnt);

	regval = t4k28_strtoul(buf, count, &cnt);

	if (regval > T4K28_MAX_REG_VAL) {
		mutex_unlock(&priv->lock);
		return -EINVAL;
	}

#ifdef	DEBUG_T4K28
	printk(KERN_INFO "Reg Addr = 0x%x, Value = 0x%x\n", regaddr, regval);
#endif

	ret  = t4k28_reg_write(client, regaddr, regval);
	if (ret < 0) {
		mutex_unlock(&priv->lock);
		return ret;
	}

	mutex_unlock(&priv->lock);
	return count;
}

static DEVICE_ATTR(t4k28_read_reg, S_IRUGO | S_IWUSR ,
	t4k28_sysfs_read_reg_show, t4k28_sysfs_read_reg_store);
static DEVICE_ATTR(t4k28_write_reg, S_IWUSR, NULL, t4k28_sysfs_write_reg_store);


static int t4k28_attr_create(struct i2c_client *client)
{
	int ret;

	ret = device_create_file(&client->dev, &dev_attr_t4k28_read_reg);
	if (ret < 0)
		goto err1;

	ret = device_create_file(&client->dev, &dev_attr_t4k28_write_reg);
	if (ret < 0)
		goto err2;
	return 0;
err2:

	device_remove_file(&client->dev, &dev_attr_t4k28_read_reg);

err1:
	return ret;
}

static void t4k28_attr_remove(struct i2c_client *client)
{
	device_remove_file(&client->dev, &dev_attr_t4k28_read_reg);
	device_remove_file(&client->dev, &dev_attr_t4k28_write_reg);

	dev_info(&client->dev, "%s:removed\n", __func__);
	return;
}

/* Get status of additional camera capabilities */
static int t4k28_g_volatile_ctrl(struct v4l2_ctrl *ctrl)
{
	struct t4k28_priv *priv = container_of(ctrl->handler,
		struct t4k28_priv, hdl);
	struct v4l2_subdev *sd = &priv->subdev;
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int ret = 0;
	int dataread = 0;
	int upperbits = 0;
	int lowerbits = 0;

#ifdef	DEBUG_T4K28
	printk(KERN_INFO "%s:CID=0x%x\n", __func__, ctrl->id);
#endif
	mutex_lock(&priv->lock);
	switch (ctrl->id) {
	case V4L2_CID_HFLIP:
		dataread = t4k28_reg_read(client, REG_0x3011);
		if (dataread < 0)
			goto unlock;
		priv->hflip->val = dataread & 0x01;
#ifdef	DEBUG_T4K28
	printk(KERN_INFO "%s:Value=0x%x\n", __func__, priv->hflip->val);
#endif
	break;

	case V4L2_CID_VFLIP:
			dataread = t4k28_reg_read(client, REG_0x3011);
			if (dataread < 0)
				goto unlock;
			dataread >>= 1;
			priv->vflip->val = dataread & 0x01;
#ifdef	DEBUG_T4K28
	printk(KERN_INFO "%s:Value=0x%x\n", __func__, priv->vflip->val);
#endif
	break;
	case V4L2_CID_EXPOSURE_AUTO:
		dataread = t4k28_reg_read(client, REG_0x3500);
		if (dataread < 0)
			goto unlock;
		dataread >>= 7;
		priv->autoexposure->val = dataread & 0x01;
#ifdef	DEBUG_T4K28
	printk(KERN_INFO "%s:Value=0x%x\n", __func__, priv->autoexposure->val);
#endif
	break;
	case V4L2_CID_EXPOSURE:
		upperbits = t4k28_reg_read(client, REG_0x3506);
		if (upperbits < 0)
			goto unlock;
		lowerbits = t4k28_reg_read(client, REG_0x3507);
		if (lowerbits < 0)
			goto unlock;
		priv->exposure->val = (upperbits << 8) | lowerbits;
#ifdef	DEBUG_T4K28
	printk(KERN_INFO "%s:Value=0x%x\n", __func__, priv->exposure->val);
#endif
	break;
	case V4L2_CID_AUTOGAIN:
		dataread = t4k28_reg_read(client, REG_0x3500);
		if (dataread < 0)
			goto unlock;

		dataread >>= 7;
		priv->autogain->val = dataread & 0x01;
#ifdef	DEBUG_T4K28
	printk(KERN_INFO "%s:Value=0x%x\n", __func__, priv->autogain->val);
#endif
	break;
	case V4L2_CID_GAIN:
		upperbits = t4k28_reg_read(client, REG_0x350A);
		if (upperbits < 0)
			goto unlock;
		lowerbits = t4k28_reg_read(client, REG_0x350B);
		if (lowerbits < 0)
			goto unlock;
		priv->gain->val = (upperbits << 8) | lowerbits;
#ifdef	DEBUG_T4K28
	printk(KERN_INFO "%s:Value=0x%x\n", __func__, priv->gain->val);
#endif
	break;
	case V4L2_CID_AUTO_WHITE_BALANCE:
		/* get auto white balance */
		dataread = t4k28_reg_read(client, REG_0x3500);
		if (dataread < 0)
			goto unlock;
		dataread >>= 6;
		priv->autowb->val = dataread & 0x01;
#ifdef	DEBUG_T4K28
	printk(KERN_INFO "%s:Value=0x%x\n", __func__, priv->autowb->val);
#endif
	break;
	case V4L2_CID_RED_BALANCE:
		upperbits = t4k28_reg_read(client, REG_0x3524);
		if (upperbits < 0)
			goto unlock;
		lowerbits = t4k28_reg_read(client, REG_0x3525);
		if (lowerbits < 0)
			goto unlock;
		upperbits &= 0x03;
		upperbits = upperbits<<8;
		dataread = upperbits|lowerbits;
		priv->red->val = dataread;
#ifdef	DEBUG_T4K28
	printk(KERN_INFO "%s:Value=0x%x\n", __func__, priv->red->val);
#endif
	break;
	case V4L2_CID_BLUE_BALANCE:
		upperbits = t4k28_reg_read(client, REG_0x3528);
		if (upperbits < 0)
			goto unlock;
		lowerbits = t4k28_reg_read(client, REG_0x3529);
		if (lowerbits < 0)
			goto unlock;
		upperbits &= 0x03;
		upperbits = upperbits << 8;
		dataread = upperbits | lowerbits;
		priv->blue->val = dataread;
#ifdef	DEBUG_T4K28
	printk(KERN_INFO "%s:Value=0x%x\n", __func__, priv->blue->val);
#endif
	break;
	case T4K28_CID_GREEN_BALANCE:
		upperbits = t4k28_reg_read(client, REG_0x3526);
		if (upperbits < 0)
			goto unlock;

		lowerbits = t4k28_reg_read(client, REG_0x3527);
		if (lowerbits < 0)
			goto unlock;
		upperbits &= 0x03;
		upperbits = upperbits << 8;
		dataread = upperbits | lowerbits;
		priv->green->val = dataread;
#ifdef	DEBUG_T4K28
	printk(KERN_INFO "%s:Value=0x%x\n", __func__, priv->green->val);
#endif
	break;
	case V4L2_CID_CONTRAST:
		dataread = t4k28_reg_read(client, REG_0x3441);
		if (dataread < 0)
			goto unlock;
		priv->contrast->val = dataread;
#ifdef	DEBUG_T4K28
	printk(KERN_INFO "%s:Value=0x%x\n", __func__, priv->contrast->val);
#endif
	break;
	case V4L2_CID_COLORFX:
	{
		dataread = t4k28_reg_read(client, REG_0x3402);
		if (dataread < 0)
			goto unlock;
		dataread &= 0x07;
		if (dataread == 3)
			priv->colorfx->val = V4L2_COLORFX_NEGATIVE;
		else if (dataread == 5)
			priv->colorfx->val = V4L2_COLORFX_SEPIA;

		else if (dataread == 6)
			priv->colorfx->val = V4L2_COLORFX_BW;
		else
			priv->colorfx->val = V4L2_COLORFX_NONE;
	}
#ifdef	DEBUG_T4K28
	printk(KERN_INFO "%s:Value=0x%x\n", __func__, priv->colorfx->val);
#endif
	break;
	default:
	dev_err(&client->dev, "%s:not support CID\n", __func__);
	ret = -EINVAL;
	break;
	}
unlock:
	mutex_unlock(&priv->lock);
	if (ret < 0)
		return ret;
	return 0;
}


/* Set Camera Control Capabilities */
static int t4k28_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct t4k28_priv *priv = container_of(ctrl->handler,
		struct t4k28_priv, hdl);
	struct v4l2_subdev *sd = &priv->subdev;
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int ret = 0;
	int dataread = 0;
	int datawrite = 0;
	int upperbits = 0 , lowerbits = 0;
#ifdef	DEBUG_T4K28
	printk(KERN_INFO "%s:CID=0x%x\n", __func__, ctrl->id);
	printk(KERN_INFO "%s:Value=0x%x\n", __func__, ctrl->val);
#endif
	mutex_lock(&priv->lock);
	switch (ctrl->id) {
	case V4L2_CID_AUTO_WHITE_BALANCE:
	{
		/* set auto white balance */
		dataread = t4k28_reg_read(client, REG_0x3500);
		if (dataread < 0)
			goto unlock;
		dataread = dataread | 0x40;
		ret = t4k28_reg_write(client, REG_0x3500, dataread);
		if (ret < 0)
			goto unlock;
	}
	break;
	case V4L2_CID_RED_BALANCE:
	{
		dataread = t4k28_reg_read(client, REG_0x3500);
		if (dataread < 0)
			goto unlock;
		dataread = dataread & 0xBF;
		ret = t4k28_reg_write(client, REG_0x3500, dataread);
		if (ret < 0)
			goto unlock;
		/* Write Red Balance Value */
		datawrite = ctrl->val & 0x03FF;
		upperbits = datawrite >> 8;
		lowerbits = datawrite & 0x0FF;

		dataread = t4k28_reg_read(client, REG_0x3524);
		if (dataread < 0)
			goto unlock;
		dataread &= 0xFC;
		dataread |= upperbits;
		ret = t4k28_reg_write(client, REG_0x3524, dataread);
		if (ret < 0)
			goto unlock;
		ret = t4k28_reg_write(client, REG_0x3525, lowerbits);
		if (ret < 0)
			goto unlock;
	}
	break;
	case V4L2_CID_BLUE_BALANCE:
		{
			dataread = t4k28_reg_read(client, REG_0x3500);
			if (dataread < 0)
				goto unlock;
			dataread = dataread & 0xBF;
			ret = t4k28_reg_write(client, REG_0x3500, dataread);
			if (ret < 0)
				goto unlock;
			/* Write Blue Balance Value */
			datawrite = ctrl->val & 0x03FF;
			upperbits = datawrite >> 8;
			lowerbits = datawrite & 0x0FF;
			dataread = t4k28_reg_read(client, REG_0x3528);
			if (dataread < 0)
				goto unlock;
			dataread &= 0xFC; /* Make lower 2 bits to zero */
			dataread |= upperbits;
			ret = t4k28_reg_write(client, REG_0x3528, dataread);
			if (ret < 0)
				goto unlock;
			ret = t4k28_reg_write(client, REG_0x3529, lowerbits);
			if (ret < 0)
				goto unlock;
		}
	break;
	case T4K28_CID_GREEN_BALANCE:
		{
			/* set manual mode */
			dataread = t4k28_reg_read(client, REG_0x3500);
			if (dataread < 0)
				goto unlock;
			dataread = dataread & 0xBF;
			ret = t4k28_reg_write(client, REG_0x3500, dataread);
			if (ret < 0)
				goto unlock;
			/* Write Green Balance Value */
			datawrite = ctrl->val & 0x03FF;
			upperbits = datawrite >> 8;
			lowerbits = datawrite & 0x0FF;
			dataread = t4k28_reg_read(client, REG_0x3526);
			if (dataread < 0)
				goto unlock;
			dataread &= 0xFC; /* Make lower 2 bits to zero */
			dataread |= upperbits;
			ret = t4k28_reg_write(client, REG_0x3526, dataread);
			if (ret < 0)
				goto unlock;
			ret = t4k28_reg_write(client, REG_0x3527, lowerbits);
			if (ret < 0)
				goto unlock;
		}
		break;
	case V4L2_CID_AUTOGAIN:
		/* set auto gain  mode */
		dataread = t4k28_reg_read(client, REG_0x3500);
		if (dataread < 0)
			goto unlock;
		dataread = dataread | 0x80;
		ret = t4k28_reg_write(client, REG_0x3500, dataread);
		if (ret < 0)
			goto unlock;
	break;
	case V4L2_CID_GAIN:
		{
		/* set manual gain  mode */
		dataread = t4k28_reg_read(client, REG_0x3500);
		if (dataread < 0)
			goto unlock;
		dataread = dataread & 0x7F;
		ret = t4k28_reg_write(client, REG_0x3500, dataread);
		if (ret < 0)
			goto unlock;
		datawrite = ctrl->val & 0x0FFF;
		upperbits = datawrite >> 8;
		lowerbits = datawrite & 0x0FF;
		ret = t4k28_reg_write(client, REG_0x350A, upperbits);
		if (ret < 0)
			goto unlock;
		ret = t4k28_reg_write(client, REG_0x350B, lowerbits);
		if (ret < 0)
			goto unlock;
		}
	break;
	case V4L2_CID_EXPOSURE_AUTO:
		/* set auto exposure mode */
		dataread = t4k28_reg_read(client, REG_0x3500);
		if (dataread < 0)
			goto unlock;
		dataread = dataread | 0x80;
		ret = t4k28_reg_write(client, REG_0x3500, dataread);
		if (ret < 0)
			goto unlock;
	break;
	case V4L2_CID_EXPOSURE:
		{
		/* set manual exposure  mode */
		dataread = t4k28_reg_read(client, REG_0x3500);
		if (dataread < 0)
			goto unlock;
		dataread = dataread & 0x7F;
		ret = t4k28_reg_write(client, REG_0x3500, dataread);
		if (ret < 0)
			goto unlock;
		datawrite = ctrl->val & 0xFFFF;
		upperbits = datawrite >> 8;
		lowerbits = datawrite & 0x00FF;
		ret = t4k28_reg_write(client, REG_0x3506, upperbits);
		if (ret < 0)
			goto unlock;
		ret = t4k28_reg_write(client, REG_0x3507, lowerbits);
		if (ret < 0)
			goto unlock;
		}
	break;
	case V4L2_CID_VFLIP:
		dataread = t4k28_reg_read(client, REG_0x3011);
		if (dataread < 0)
			goto unlock;
		if (ctrl->val)
			dataread = dataread | 0x02;
		else
			dataread = dataread & 0xFD;
		ret = t4k28_reg_write(client, REG_0x3011, dataread);
		if (ret < 0)
			goto unlock;
	break;
	case V4L2_CID_HFLIP:
		dataread = t4k28_reg_read(client, REG_0x3011);
		if (dataread < 0)
			goto unlock;
		if (ctrl->val)
			dataread = dataread | 0x01;
		else
			dataread = dataread & 0xFE;
		ret = t4k28_reg_write(client, REG_0x3011, dataread);
		if (ret < 0)
			goto unlock;
	break;
	case V4L2_CID_COLORFX:
		{
			dataread = 0;
			switch (ctrl->val) {
			case V4L2_COLORFX_BW:
				dataread = t4k28_reg_read(client, REG_0x3402);
				if (dataread < 0)
					goto unlock;
				dataread &= 0xF8;
				dataread |= 0x06;
			break;
			case V4L2_COLORFX_NEGATIVE:
				dataread = t4k28_reg_read(client, REG_0x3402);
				if (dataread < 0)
					goto unlock;
				dataread &= 0xF8;
				dataread |= 0x03;
			break;
			case V4L2_COLORFX_SEPIA:
				dataread = t4k28_reg_read(client, REG_0x3402);
				if (dataread < 0)
					goto unlock;
				dataread &= 0xF8;
				dataread |= 0x05;
			break;
			default:
				dev_err(&client->dev,
					"%s:not support COLORFX\n", __func__);
				ret = -EINVAL;
				goto unlock;
			}
			ret = t4k28_reg_write(client, REG_0x3402, dataread);
			if (ret < 0)
				goto unlock;
		}
	break;
	case V4L2_CID_CONTRAST:
		/* Enable contrast */
		dataread = t4k28_reg_read(client, REG_0x3401);
		if (dataread < 0)
			goto unlock;
		dataread |= 0x20;
		ret = t4k28_reg_write(client, REG_0x3401, dataread);
		if (ret < 0)
			goto unlock;
		/* Write contrast value */
		ctrl->val &= 0xFF;
		ret = t4k28_reg_write(client, REG_0x3441, ctrl->val);
		if (ret < 0)
			goto unlock;
	break;
	default:
		dev_err(&client->dev, "%s:not support CID\n", __func__);
		ret = -EINVAL;
		break;
	}
unlock:
	mutex_unlock(&priv->lock);
	if (ret < 0)
		return ret;
	return 0;
}

static const struct v4l2_ctrl_ops t4k28_ctrl_ops = {
	.g_volatile_ctrl = t4k28_g_volatile_ctrl,
	.s_ctrl = t4k28_s_ctrl,
};


static const struct v4l2_ctrl_config t4k28_ctrls[] = {
	{ /* Green balance */
		.ops	= &t4k28_ctrl_ops,
		.id	= T4K28_CID_GREEN_BALANCE,
		.type	= V4L2_CTRL_TYPE_INTEGER,
		.name	= "Green Balance",
		.min	= 0,
		.max	= 1023,
		.def	= DEF_GREEN,
		.step	= 1,
		.flags	= V4L2_CTRL_FLAG_SLIDER,
	},
};


static int t4k28_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct t4k28_priv *priv;

	/* Check platform data is populated */
	struct soc_camera_link *icl = soc_camera_i2c_to_link(client);
	int ret, chip_id;

	if (!icl) {
		dev_err(&client->dev, "Missing platform_data for driver\n");
		return -EINVAL;
	}

	/* Allocate memory for driver private structure */
	priv = vzalloc(sizeof(struct t4k28_priv));
	if (!priv) {
		dev_err(&client->dev, "Failed to allocate private data!\n");
		return -ENOMEM;
	}

	priv->rate_div = 1;

	ret = t4k28_reg_read(client, 0x3000);
	if (ret < 0)
		goto err;
	chip_id = ret << 8;
	ret = t4k28_reg_read(client, 0x3001);
	if (ret < 0)
		goto err;
	chip_id |= ret;

	v4l2_i2c_subdev_init(&priv->subdev, client, &t4k28_subdev_ops);

	mutex_init(&priv->lock);

	v4l2_ctrl_handler_init(&priv->hdl, NUM_CTRL_SUPPORT);

	priv->autowb = v4l2_ctrl_new_std(&priv->hdl, &t4k28_ctrl_ops,
			V4L2_CID_AUTO_WHITE_BALANCE, 0, 1, 1, 1);
	priv->red = v4l2_ctrl_new_std(&priv->hdl, &t4k28_ctrl_ops,
			V4L2_CID_RED_BALANCE, 0, 0x3ff, 1, DEF_RED);
	priv->blue = v4l2_ctrl_new_std(&priv->hdl, &t4k28_ctrl_ops,
			V4L2_CID_BLUE_BALANCE, 0, 0x3ff, 1, DEF_BLUE);
	priv->green = v4l2_ctrl_new_custom(&priv->hdl, &t4k28_ctrls[0], NULL);
	priv->autogain = v4l2_ctrl_new_std(&priv->hdl, &t4k28_ctrl_ops,
			V4L2_CID_AUTOGAIN, 0, 1, 1, 1);
	priv->gain = v4l2_ctrl_new_std(&priv->hdl, &t4k28_ctrl_ops,
			V4L2_CID_GAIN, 0, 0xfff, 1, DEF_GAIN);
	priv->autoexposure = v4l2_ctrl_new_std_menu(&priv->hdl,
			&t4k28_ctrl_ops, V4L2_CID_EXPOSURE_AUTO,
			V4L2_EXPOSURE_MANUAL, 0, V4L2_EXPOSURE_AUTO);
	priv->exposure = v4l2_ctrl_new_std(&priv->hdl, &t4k28_ctrl_ops,
			V4L2_CID_EXPOSURE, 0, 0xffff, 1, DEF_AEC);
	priv->contrast = v4l2_ctrl_new_std(&priv->hdl, &t4k28_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 0xff, 1, DEF_CONTRAST);
	priv->vflip =  v4l2_ctrl_new_std(&priv->hdl, &t4k28_ctrl_ops,
			V4L2_CID_VFLIP, 0, 1, 1, 0);
	priv->hflip =  v4l2_ctrl_new_std(&priv->hdl, &t4k28_ctrl_ops,
			V4L2_CID_HFLIP, 0, 1, 1, 0);
	priv->colorfx = v4l2_ctrl_new_std_menu(&priv->hdl, &t4k28_ctrl_ops,
			V4L2_CID_COLORFX, 10, 1, V4L2_COLORFX_NONE);
	priv->subdev.ctrl_handler = &priv->hdl;
	if (priv->hdl.error) {
		ret = priv->hdl.error;
		dev_err(&client->dev, "ctrl handler error\n");
		goto err1;
	}
	priv->autowb->flags |= V4L2_CTRL_FLAG_VOLATILE;
	priv->red->flags |= V4L2_CTRL_FLAG_VOLATILE;
	priv->blue->flags |= V4L2_CTRL_FLAG_VOLATILE;
	priv->green->flags |= V4L2_CTRL_FLAG_VOLATILE;
	priv->autogain->flags |= V4L2_CTRL_FLAG_VOLATILE;
	priv->gain->flags |= V4L2_CTRL_FLAG_VOLATILE;
	priv->autoexposure->flags |= V4L2_CTRL_FLAG_VOLATILE;
	priv->exposure->flags |= V4L2_CTRL_FLAG_VOLATILE;
	priv->vflip->flags |= V4L2_CTRL_FLAG_VOLATILE;
	priv->hflip->flags |= V4L2_CTRL_FLAG_VOLATILE;
	priv->colorfx->flags |= V4L2_CTRL_FLAG_VOLATILE;
	priv->contrast->flags |= V4L2_CTRL_FLAG_VOLATILE;


	/* Create sysfs device files */
	ret = t4k28_attr_create(client);
	if (ret < 0) {
		dev_err(&client->dev, "sysfs create error\n");
		goto err1;
	}

	dev_info(&client->dev, "t4k28 chip ID 0x%04x\n", chip_id);

	return 0;

err1:
	v4l2_ctrl_handler_free(&priv->hdl);
	v4l2_device_unregister_subdev(&priv->subdev);
err:
	vfree(priv);
	return ret;
}

static int t4k28_remove(struct i2c_client *client)
{
	/* Get subdev structure from client */
	struct v4l2_subdev *sd = i2c_get_clientdata(client);

	/* Get address of t4k28_priv from subdev using kernel helper function */
	struct t4k28_priv *priv =
			container_of(sd, struct t4k28_priv, subdev);

	/* Remove sysfs device files */
	t4k28_attr_remove(client);

	v4l2_ctrl_handler_free(&priv->hdl);

	/* unregister the v4l2 sub dev which points to sd */
	v4l2_device_unregister_subdev(sd);

	/* Free the driver private structure */
	vfree(priv);

	return 0;
}

/* I2C Device ID (List of slave chips that are supported) */
static const struct i2c_device_id t4k28_id[] = {
	{ "t4k28", 0 },
	{ }
};

MODULE_DEVICE_TABLE(i2c, t4k28_id);

/* I2C Driver structure */
static struct i2c_driver t4k28_i2c_driver = {
	.driver = {
		.name = "t4k28",
	},
	.probe		= t4k28_probe,
	.remove		= t4k28_remove,
	.id_table	= t4k28_id,
};

/* Macro for i2c_add and i2c_del driver */
module_i2c_driver(t4k28_i2c_driver);

MODULE_DESCRIPTION("SoC Camera driver for t4k28");
MODULE_LICENSE("GPL v2");
