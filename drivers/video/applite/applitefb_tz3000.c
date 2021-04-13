/*
 * linux/drivers/video/applite/applitefb_tz3000.c
 *
 * (C) Copyright TOSHIBA Corporation
 * Semiconductor & Storage Products Company 2013
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
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/fb.h>
#include <linux/init.h>
#include <linux/pci.h>

#include <linux/videodev2.h>
#include <mach/regs/pmu_offs_def.h>
#include <mach/regs/dispif_offs_def.h>
#include <linux/uaccess.h>
#include <linux/i2c.h>
#include <linux/gpio.h>
#include <linux/clk.h>

#include "applitefb.h"
#include "applitefb_tz3000.h"
#if IS_ENABLED(CONFIG_D2DP)
	#include "d2dp.h"
#endif

#undef	_TEST_VCODEC_PERFORMANCE_
#if defined(_TEST_VCODEC_PERFORMANCE_)	/* for VCODEC performance (enable FRAME_END Interrupt) */
static __u32	counter;
static __u32	prev_counter;
static __u32	bPan;
#endif

enum regist {
	DISPIF_PRD,
	DISPIF_FBD,
	DISPIF_FRS,
	DISPIF_CKEN,
	DISPIF_ENABLE,
	DISPIF_DSI_DPHY_CLWCNTRL,
	DISPIF_DSI_DPHY_D0WCNTRL,
	DISPIF_DSI_DPHY_D1WCNTRL,
	DISPIF_DSI_DPHY_D2WCNTRL,
	DISPIF_DSI_DPHY_D3WCNTRL,
	DISPIF_DSI_PPI_LINEINTCNT,
	DISPIF_DSI_PPI_LPTXTIMECNT,
	DISPIF_DSI_PPI_TCLK_HEADERCNT,
	DISPIF_DSI_PPI_TCLK_TRAILCNT,
	DISPIF_DSI_PPI_THS_HEADERCNT,
	DISPIF_DSI_PPI_TWAKEUP,
	DISPIF_DSI_PPI_TCLK_POSTCNT,
	DISPIF_DSI_PPI_THS_TRAILCNT,
	DISPIF_DSI_PPI_HSTXVREGCNT,
	DISPIF_DSI_PPI_HSTXVREGTN,
	DISPIF_DSI_PPI_TXOPTIONCNTRL,
	DISPIF_DSI_PPI_BTACNTRL1,
	DISPIF_DSI_PPI_STARTCNTRL,
	DISPIF_HV_DLY,
	DISPIF_HV_MAX,
	DISPIF_HD,
	DISPIF_VD_R,
	DISPIF_VD_F,
	DISPIF_HBLK,
	DISPIF_VBLK,
	DISPIF_HS_0,
	DISPIF_HBLK2,
	DISPIF_HD2,
	DISPIF_HS_0_SET1,
	DISPIF_HS_0_SET2,
	DISPIF_MDI_GO,
	MAX_DISPIF_REGS
};

enum fconv_regist {
	SET_SEL_ALPHA,
	Y2RMTX_OFFSET,
	Y2RMTX_COEF00,
	Y2RMTX_COEF01,
	Y2RMTX_COEF02,
	Y2RMTX_COEF10,
	Y2RMTX_COEF11,
	Y2RMTX_COEF12,
	Y2RMTX_COEF20,
	Y2RMTX_COEF21,
	Y2RMTX_COEF22,
	RGBLIMIT,
	FORCE_MODE0,
	FORCE_GY0,
	FORCE_BCB0,
	FORCE_RCR0,
	FORCE_A0,
	CROP0,
	IRQ,
	IRQ_MASK
};

/* PLL Setting Table */
static struct reg_param tz3000_reg_param[][MAX_DISPIF_REGS] = {
	{/* 720x480 */
		{0, DISPIF_PRD_OFFS,			0x00000000},
		{0, DISPIF_FBD_OFFS,			0x00000017},
		{0, DISPIF_FRS_OFFS,			0x00000001},
		{0, DISPIF_CKEN_OFFS,			0x00000001},
		{0, DISPIF_ENABLE_OFFS,			0x00000001},
		{0, DISPIF_DSI_DPHY_CLWCNTRL_OFFS,	0x00000001},
		{0, DISPIF_DSI_DPHY_D0WCNTRL_OFFS,	0x00000001},
		{0, DISPIF_DSI_DPHY_D1WCNTRL_OFFS,	0x00000001},
		{0, DISPIF_DSI_DPHY_D2WCNTRL_OFFS,	0x00000000},
		{0, DISPIF_DSI_DPHY_D3WCNTRL_OFFS,	0x00000000},
		{0, DISPIF_DSI_PPI_LINEINTCNT_OFFS,	0x00001FA4},
		{0, DISPIF_DSI_PPI_LPTXTIMECNT_OFFS,    0x00000005},
		{0, DISPIF_DSI_PPI_TCLK_HEADERCNT_OFFS, 0x00000B05},
		{0, DISPIF_DSI_PPI_TCLK_TRAILCNT_OFFS,  0x00000003},
		{0, DISPIF_DSI_PPI_THS_HEADERCNT_OFFS,  0x00000505},
		{0, DISPIF_DSI_PPI_TWAKEUP_OFFS,	0x00003F48},
		{0, DISPIF_DSI_PPI_TCLK_POSTCNT_OFFS,   0x00000009},
		{0, DISPIF_DSI_PPI_THS_TRAILCNT_OFFS,   0x00000003},
		{0, DISPIF_DSI_PPI_HSTXVREGCNT_OFFS,    0x00000020},
		{0, DISPIF_DSI_PPI_HSTXVREGTN_OFFS,	0x00000007},
		{0, DISPIF_DSI_PPI_TXOPTIONCNTRL_OFFS,  0x00000001},
		{0, DISPIF_DSI_PPI_BTACNTRL1_OFFS,	0x00140005},
		{0, DISPIF_DSI_PPI_STARTCNTRL_OFFS,	0x00000001},
		{0, DISPIF_HV_DLY_OFFS,			0x00010001},
		{0, DISPIF_HV_MAX_OFFS,			0x020D0A0E},
		{0, DISPIF_HD_OFFS,			0x00BA0001},
		{0, DISPIF_VD_R_OFFS,			0x00010001},
		{0, DISPIF_VD_F_OFFS,			0x00060A0E},
		{0, DISPIF_HBLK_OFFS,			0x016E09DF},
		{0, DISPIF_VBLK_OFFS,			0x00240205},
		{0, DISPIF_HS_0_OFFS,			0x00000000},
		{0, DISPIF_HBLK2_OFFS,			0x00000000},
		{0, DISPIF_HD2_OFFS,			0x00000001},
		{0, DISPIF_HS_0_SET1_OFFS,		0x00000000 },
		{0, DISPIF_HS_0_SET2_OFFS,		0x00000000},
		{0, DISPIF_MDI_GO_OFFS,			0x00010001}
	},
	{/* 1280x720 */
		{0, DISPIF_PRD_OFFS,			0x00000000},
		{0, DISPIF_FBD_OFFS,			0x00000015},
		{0, DISPIF_FRS_OFFS,			0x00000000},
		{0, DISPIF_CKEN_OFFS,			0x00000001},
		{0, DISPIF_ENABLE_OFFS,			0x00000001},
		{0, DISPIF_DSI_DPHY_CLWCNTRL_OFFS,	0x00000001},
		{0, DISPIF_DSI_DPHY_D0WCNTRL_OFFS,	0x00000001},
		{0, DISPIF_DSI_DPHY_D1WCNTRL_OFFS,	0x00000001},
		{0, DISPIF_DSI_DPHY_D2WCNTRL_OFFS,	0x00000001},
		{0, DISPIF_DSI_DPHY_D3WCNTRL_OFFS,	0x00000000},
		{0, DISPIF_DSI_PPI_LINEINTCNT_OFFS,	0x00003a02},
		{0, DISPIF_DSI_PPI_LPTXTIMECNT_OFFS,	0x00000008},
		{0, DISPIF_DSI_PPI_TCLK_HEADERCNT_OFFS,	0x00001308},
		{0, DISPIF_DSI_PPI_TCLK_TRAILCNT_OFFS,	0x00000005},
		{0, DISPIF_DSI_PPI_THS_HEADERCNT_OFFS,	0x00000908},
		{0, DISPIF_DSI_PPI_TWAKEUP_OFFS,	0x00004883},
		{0, DISPIF_DSI_PPI_TCLK_POSTCNT_OFFS,	0x0000000B},
		{0, DISPIF_DSI_PPI_THS_TRAILCNT_OFFS,	0x00000005},
		{0, DISPIF_DSI_PPI_HSTXVREGCNT_OFFS,	0x00000020},
		{0, DISPIF_DSI_PPI_HSTXVREGTN_OFFS,	0x0000000F},
		{0, DISPIF_DSI_PPI_TXOPTIONCNTRL_OFFS,	0x00000001},
		{0, DISPIF_DSI_PPI_BTACNTRL1_OFFS,	0x00200008},
		{0, DISPIF_DSI_PPI_STARTCNTRL_OFFS,	0x00000001},
		{0, DISPIF_HV_DLY_OFFS,			0x00010001},
#if defined(_1280x720_60HZ_)
		{0, DISPIF_HV_MAX_OFFS,			0x02EE0CE4},
#else
		{0, DISPIF_HV_MAX_OFFS,			0x02EE0F78},
#endif
		{0, DISPIF_HD_OFFS,			0x00500001},
		{0, DISPIF_VD_R_OFFS,			0x00010001},
#if defined(_1280x720_60HZ_)
		{0, DISPIF_VD_F_OFFS,			0x00050CE4},
#else
		{0, DISPIF_VD_F_OFFS,			0x00050F78},
#endif
		{0, DISPIF_HBLK_OFFS,			0x02080C09},
		{0, DISPIF_VBLK_OFFS,			0x001902EA},
		{0, DISPIF_HS_0_OFFS,			0x00000000},
		{0, DISPIF_HBLK2_OFFS,			0x00000000},
		{0, DISPIF_HD2_OFFS,			0x00000001},
		{0, DISPIF_HS_0_SET1_OFFS,		0x00000000},
		{0, DISPIF_HS_0_SET2_OFFS,		0x00000000},
		{0, DISPIF_MDI_GO_OFFS,			0x00010001}
	},
	{/* 1920x1080 */
		{0, DISPIF_PRD_OFFS,			0x00000000},
		{0, DISPIF_FBD_OFFS,			0x00000020},
		{0, DISPIF_FRS_OFFS,			0x00000001},
		{0, DISPIF_CKEN_OFFS,			0x00000001},
		{0, DISPIF_ENABLE_OFFS,			0x00000001},
		{0, DISPIF_DSI_DPHY_CLWCNTRL_OFFS,	0x00000001},
		{0, DISPIF_DSI_DPHY_D0WCNTRL_OFFS,	0x00000001},
		{0, DISPIF_DSI_DPHY_D1WCNTRL_OFFS,	0x00000001},
		{0, DISPIF_DSI_DPHY_D2WCNTRL_OFFS,	0x00000001},
		{0, DISPIF_DSI_DPHY_D3WCNTRL_OFFS,	0x00000001},
		{0, DISPIF_DSI_PPI_LINEINTCNT_OFFS,	0x00002b82},
		{0, DISPIF_DSI_PPI_LPTXTIMECNT_OFFS,	0x00000006},
		{0, DISPIF_DSI_PPI_TCLK_HEADERCNT_OFFS,	0x00000e06},
		{0, DISPIF_DSI_PPI_TCLK_TRAILCNT_OFFS,	0x00000004},
		{0, DISPIF_DSI_PPI_THS_HEADERCNT_OFFS,	0x00000706},
		{0, DISPIF_DSI_PPI_TWAKEUP_OFFS,	0x00004883},
		{0, DISPIF_DSI_PPI_TCLK_POSTCNT_OFFS,	0x0000000a},
		{0, DISPIF_DSI_PPI_THS_TRAILCNT_OFFS,	0x00000004},
		{0, DISPIF_DSI_PPI_HSTXVREGCNT_OFFS,	0x00000020},
		{0, DISPIF_DSI_PPI_HSTXVREGTN_OFFS,	0x0000001F},
		{0, DISPIF_DSI_PPI_TXOPTIONCNTRL_OFFS,	0x00000001},
		{0, DISPIF_DSI_PPI_BTACNTRL1_OFFS,	0x00180006},
		{0, DISPIF_DSI_PPI_STARTCNTRL_OFFS,	0x00000001},
		{0, DISPIF_HV_DLY_OFFS,			0x00010001},
		{0, DISPIF_HV_MAX_OFFS,			0x04650CE4},
		{0, DISPIF_HD_OFFS,			0x00420001},
		{0, DISPIF_VD_R_OFFS,			0x00010001},
		{0, DISPIF_VD_F_OFFS,			0x00050CE4},
		{0, DISPIF_HBLK_OFFS,			0x01200C61},
		{0, DISPIF_VBLK_OFFS,			0x00290462},
		{0, DISPIF_HS_0_OFFS,			0x00000000},
		{0, DISPIF_HBLK2_OFFS,			0x00000000},
		{0, DISPIF_HD2_OFFS,			0x00000001},
		{0, DISPIF_HS_0_SET1_OFFS,		0x00000000},
		{0, DISPIF_HS_0_SET2_OFFS,		0x00000000},
		{0, DISPIF_MDI_GO_OFFS,			0x00010001}
	}
};


/* Command queue Setting Table */
static struct reg_param tz3000_CQ_reg_param[4][COMMANDQUEUE_MAX] = {
	{/* 720x480 */
		{0, DISPIF_DSI_CQ0_OFFS, 0xA6002000},
		{0, DISPIF_DSI_CQ0_OFFS, 0x83000080},
		{0, DISPIF_DSI_CQ0_OFFS, 0x95000000},
		{0, DISPIF_DSI_CQ0_OFFS, 0xA30000A2},
		{0, DISPIF_DSI_CQ0_OFFS, 0x0415FFFF},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28800005},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000001},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000002},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000031},
		{0, DISPIF_DSI_CQ0_OFFS, 0x04030004},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000001},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000021},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000002},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000031},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000008},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000011},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000002},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000031},
		{0, DISPIF_DSI_CQ0_OFFS, 0x0403001C},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000001},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000021},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000002},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000031},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000001},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000021},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000002},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000031},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000010},
		{0, DISPIF_DSI_CQ0_OFFS, 0x4008703E},
		{0, DISPIF_DSI_CQ0_OFFS, 0x040501DE},
		{0, DISPIF_DSI_CQ0_OFFS, 0x40002419},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000021},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000002},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000031},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000010},
		{0, DISPIF_DSI_CQ0_OFFS, 0x4008703E},
		{0, DISPIF_DSI_CQ0_OFFS, 0x40002419},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000021},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000002},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000031},
		{0, DISPIF_DSI_CQ0_OFFS, 0x04030007},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000001},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000021},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000002},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000031}
	},
	{/* 1280x720 */
		{0, DISPIF_DSI_CQ0_OFFS, 0xA6002000},
		{0, DISPIF_DSI_CQ0_OFFS, 0x83000080},
		{0, DISPIF_DSI_CQ0_OFFS, 0x95000000},
		{0, DISPIF_DSI_CQ0_OFFS, 0xA30000A4},
		{0, DISPIF_DSI_CQ0_OFFS, 0x040BFFFF},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28800005},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000001},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000002},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000031},
		{0, DISPIF_DSI_CQ0_OFFS, 0x04030003},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000001},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000021},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000002},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000031},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000008},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000011},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000002},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000031},
		{0, DISPIF_DSI_CQ0_OFFS, 0x04030012},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000001},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000021},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000002},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000031},
		{0, DISPIF_DSI_CQ0_OFFS, 0x040502CF},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000001},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000021},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000002},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000031},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000010},
		{0, DISPIF_DSI_CQ0_OFFS, 0x400F003E},
		{0, DISPIF_DSI_CQ0_OFFS, 0x04030004},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000001},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000021},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000002},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000031},
		{1, 0x0000, 0x00000000},
		{1, 0x0000, 0x00000000},
		{1, 0x0000, 0x00000000},
		{1, 0x0000, 0x00000000},
		{1, 0x0000, 0x00000000},
		{1, 0x0000, 0x00000000},
		{1, 0x0000, 0x00000000},
		{1, 0x0000, 0x00000000},
		{1, 0x0000, 0x00000000},
		{1, 0x0000, 0x00000000}
	},
	{/* 1920x1080 */
		{0, DISPIF_DSI_CQ0_OFFS, 0xA6002000},
		{0, DISPIF_DSI_CQ0_OFFS, 0x83000080},
		{0, DISPIF_DSI_CQ0_OFFS, 0x95000000},
		{0, DISPIF_DSI_CQ0_OFFS, 0xA30000A6},
		{0, DISPIF_DSI_CQ0_OFFS, 0x040BFFFF},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28800005},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000001},
		{0, DISPIF_DSI_CQ0_OFFS, 0x40007A19},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000031},
		{0, DISPIF_DSI_CQ0_OFFS, 0x04030003},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000001},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000021},
		{0, DISPIF_DSI_CQ0_OFFS, 0x40007A19},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000031},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000008},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000011},
		{0, DISPIF_DSI_CQ0_OFFS, 0x40007A19},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000031},
		{0, DISPIF_DSI_CQ0_OFFS, 0x04030022},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000001},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000021},
		{0, DISPIF_DSI_CQ0_OFFS, 0x40007A19},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000031},
		{0, DISPIF_DSI_CQ0_OFFS, 0x04050437},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000001},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000021},
		{0, DISPIF_DSI_CQ0_OFFS, 0x40007A19},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000031},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000010},
		{0, DISPIF_DSI_CQ0_OFFS, 0x4016803E},
		{0, DISPIF_DSI_CQ0_OFFS, 0x04030003},
		{0, DISPIF_DSI_CQ0_OFFS, 0x28000001},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000021},
		{0, DISPIF_DSI_CQ0_OFFS, 0x40007A19},
		{0, DISPIF_DSI_CQ0_OFFS, 0x10000031},
		{1, 0x0000, 0x00000000},
		{1, 0x0000, 0x00000000},
		{1, 0x0000, 0x00000000},
		{1, 0x0000, 0x00000000},
		{1, 0x0000, 0x00000000},
		{1, 0x0000, 0x00000000},
		{1, 0x0000, 0x00000000},
		{1, 0x0000, 0x00000000},
		{1, 0x0000, 0x00000000},
		{1, 0x0000, 0x00000000}
	}
};

static u32 regist[2][20] = {
	{
		DISPIF_FCONVA_SET_SEL_ALPHA_OFFS,
		DISPIF_FCONVA_SET_Y2RMTX_OFFSET_OFFS,
		DISPIF_FCONVA_SET_Y2RMTX_COEF00_OFFS,
		DISPIF_FCONVA_SET_Y2RMTX_COEF01_OFFS,
		DISPIF_FCONVA_SET_Y2RMTX_COEF02_OFFS,
		DISPIF_FCONVA_SET_Y2RMTX_COEF10_OFFS,
		DISPIF_FCONVA_SET_Y2RMTX_COEF11_OFFS,
		DISPIF_FCONVA_SET_Y2RMTX_COEF12_OFFS,
		DISPIF_FCONVA_SET_Y2RMTX_COEF20_OFFS,
		DISPIF_FCONVA_SET_Y2RMTX_COEF21_OFFS,
		DISPIF_FCONVA_SET_Y2RMTX_COEF22_OFFS,
		DISPIF_FCONVA_SET_RGBLIMIT_OFFS,
		DISPIF_FCONVA_SET_FORCE_MODE0_OFFS,
		DISPIF_FCONVA_SET_FORCE_GY0_OFFS,
		DISPIF_FCONVA_SET_FORCE_BCB0_OFFS,
		DISPIF_FCONVA_SET_FORCE_RCR0_OFFS,
		DISPIF_FCONVA_SET_FORCE_A0_OFFS,
		DISPIF_FCONVA_SET_CROP0_OFFS,
		DISPIF_FCONVA_IRQ_OFFS,
		DISPIF_FCONVA_SET_IRQ_MASK_OFFS,
	},
	{
		DISPIF_FCONVB_SET_SEL_ALPHA_OFFS,
		DISPIF_FCONVB_SET_Y2RMTX_OFFSET_OFFS,
		DISPIF_FCONVB_SET_Y2RMTX_COEF00_OFFS,
		DISPIF_FCONVB_SET_Y2RMTX_COEF01_OFFS,
		DISPIF_FCONVB_SET_Y2RMTX_COEF02_OFFS,
		DISPIF_FCONVB_SET_Y2RMTX_COEF10_OFFS,
		DISPIF_FCONVB_SET_Y2RMTX_COEF11_OFFS,
		DISPIF_FCONVB_SET_Y2RMTX_COEF12_OFFS,
		DISPIF_FCONVB_SET_Y2RMTX_COEF20_OFFS,
		DISPIF_FCONVB_SET_Y2RMTX_COEF21_OFFS,
		DISPIF_FCONVB_SET_Y2RMTX_COEF22_OFFS,
		DISPIF_FCONVB_SET_RGBLIMIT_OFFS,
		DISPIF_FCONVB_SET_FORCE_MODE0_OFFS,
		DISPIF_FCONVB_SET_FORCE_GY0_OFFS,
		DISPIF_FCONVB_SET_FORCE_BCB0_OFFS,
		DISPIF_FCONVB_SET_FORCE_RCR0_OFFS,
		DISPIF_FCONVB_SET_FORCE_A0_OFFS,
		DISPIF_FCONVB_SET_CROP0_OFFS,
		DISPIF_FCONVB_IRQ_OFFS,
		DISPIF_FCONVB_SET_IRQ_MASK_OFFS,
	},
};


struct debug_reg_param debug_regist[] = {
	{ "MDI_GO"				, 0x0020 },
	{ "HV_MAX"				, 0x0030 },
	{ "HV_DLY"				, 0x0034 },
	{ "HBLK"				, 0x0038 },
	{ "HBLK2"				, 0x003C },
	{ "HD"					, 0x0040 },
	{ "HD2"					, 0x0044 },
	{ "VBLK"				, 0x0050 },
	{ "VD_R"				, 0x0054 },
	{ "VD_F"				, 0x0058 },
	{ "DTG_START"				, 0x0060 },
	{ "DTG_STOP"				, 0x0064 },
	{ "DTG_FORCE_STOP"			, 0x0068 },
	{ "HS_0"				, 0x0070 },
	{ "HS_0_SET1"				, 0x0074 },
	{ "HS_0_SET2"				, 0x0078 },
	{ "IRQ_EN"				, 0x0080 },
	{ "IRQ_STAT"				, 0x0084 },
	{ "DTG_STAT"				, 0x0090 },
	{ "DATA_STAT"				, 0x0094 },
	{ "HSBCLK_POL"				, 0x00A0 },
	{ "DSI_DPHY_CLW_DPHYCONTTX"		, 0x0800 },
	{ "DSI_DPHY_D0W_DPHYCONTTX"		, 0x0804 },
	{ "DSI_DPHY_D1W_DPHYCONTTX"		, 0x0808 },
	{ "DSI_DPHY_D2W_DPHYCONTTX"		, 0x080C },
	{ "DSI_DPHY_D3W_DPHYCONTTX"		, 0x0810 },
	{ "DSI_DPHY_CLWCNTRL"			, 0x0840 },
	{ "DSI_DPHY_D0WCNTRL"			, 0x0844 },
	{ "DSI_DPHY_D1WCNTRL"			, 0x0848 },
	{ "DSI_DPHY_D2WCNTRL"			, 0x084C },
	{ "DSI_DPHY_D3WCNTRL"			, 0x0850 },
	{ "DSI_D0W_DPHYCONTRX"			, 0x0860 },
	{ "LPRXCAL"				, 0x0864 },
	{ "BYPCKEN"				, 0x0900 },
	{ "CKEN"				, 0x0904 },
	{ "CKTRISTATE"				, 0x0908 },
	{ "ENABLE"				, 0x090C },
	{ "EXTFBEN"				, 0x0910 },
	{ "FBD"					, 0x0914 },
	{ "FRS"					, 0x0918 },
	{ "LBWS"				, 0x091C },
	{ "LFBREN"				, 0x0920 },
	{ "PRD"					, 0x0924 },
	{ "TEST"				, 0x0930 },
	{ "DISPIF_CGATE"			, 0x0980 },
	{ "DISPIF_IRQMOD"			, 0x0984 },
	{ "DISPIF_IRQSEL"			, 0x0988 },
	{ "FCONVA_START"			, 0x1000 },
	{ "FCONVA_ABORT"			, 0x1004 },
	{ "FCONVA_SET_DUMMY_READ"		, 0x1010 },
	{ "FCONVA_SET_BUSIF"			, 0x1014 },
	{ "FCONVA_SET_SEL_ALPHA"		, 0x1018 },
	{ "FCONVA_IRQ"				, 0x1020 },
	{ "FCONVA_SET_IRQ_MASK"			, 0x1024 },
	{ "FCONVA_TRANS_IN_FORMAT"		, 0x1100 },
	{ "FCONVA_TRANS_IN_HSIZE"		, 0x1104 },
	{ "FCONVA_TRANS_IN_VSIZE"		, 0x1108 },
	{ "FCONVA_TRANS_IN_BASEADDR_GY"		, 0x1110 },
	{ "FCONVA_TRANS_IN_BASEADDR_BCB"	, 0x1114 },
	{ "FCONVA_TRANS_IN_BASEADDR_RCR"	, 0x1118 },
	{ "FCONVA_TRANS_IN_PITCH_GY"		, 0x111C },
	{ "FCONVA_TRANS_IN_PITCH_BCB"		, 0x1120 },
	{ "FCONVA_TRANS_IN_PITCH_RCR"		, 0x1124 },
	{ "FCONVA_TRANS_OUT_FORMAT"		, 0x1140 },
	{ "FCONVA_TRANS_OUT_HSIZE"		, 0x1144 },
	{ "FCONVA_TRANS_OUT_VSIZE"		, 0x1148 },
	{ "FCONVA_TRANS_OUT_BASEADDR_GY"	, 0x1150 },
	{ "FCONVA_TRANS_OUT_BASEADDR_BCB"	, 0x1154 },
	{ "FCONVA_TRANS_OUT_BASEADDR_RCR"	, 0x1158 },
	{ "FCONVA_TRANS_OUT_PITCH_GY"		, 0x115C },
	{ "FCONVA_TRANS_OUT_PITCH_BCB"		, 0x1160 },
	{ "FCONVA_TRANS_OUT_PITCH_RCR"		, 0x1164 },
	{ "FCONVA_TRANS_FORCE_MODE"		, 0x1180 },
	{ "FCONVA_CH_FORCE_GY"			, 0x1184 },
	{ "FCONVA_CH_FORCE_BCB"			, 0x1188 },
	{ "FCONVA_CH_FORCE_R"			, 0x118C },
	{ "FCONVA_CH_FORCE_A"			, 0x1190 },
	{ "FCONVA_SET_IN_FORMAT0"		, 0x1200 },
	{ "FCONVA_SET_IN_HSIZE0"		, 0x1204 },
	{ "FCONVA_SET_IN_VSIZE0"		, 0x1208 },
	{ "FCONVA_SET_IN_BASEADDR_GY0"		, 0x1210 },
	{ "FCONVA_SET_IN_BASEADDR_BCB0"		, 0x1214 },
	{ "FCONVA_SET_IN_BASEADDR_RCR0"		, 0x1218 },
	{ "FCONVA_SET_IN_PITCH_GY0"		, 0x121C },
	{ "FCONVA_SET_IN_PITCH_BCB0"		, 0x1220 },
	{ "FCONVA_SET_IN_PITCH_RCR0"		, 0x1224 },
	{ "FCONVA_SET_OUT_FORMAT0"		, 0x1240 },
	{ "FCONVA_SET_OUT_HSIZE0"		, 0x1244 },
	{ "FCONVA_SET_OUT_VSIZE0"		, 0x1248 },
	{ "FCONVA_SET_OUT_BASEADDR_GY0"		, 0x1250 },
	{ "FCONVA_SET_OUT_BASEADDR_BCB0"	, 0x1254 },
	{ "FCONVA_SET_OUT_BASEADDR_RCR0"	, 0x1258 },
	{ "FCONVA_SET_OUT_PITCH_GY0"		, 0x125C },
	{ "FCONVA_SET_OUT_PITCH_BCB0"		, 0x1260 },
	{ "FCONVA_SET_OUT_PITCH_RCR0"		, 0x1264 },
	{ "FCONVA_SET_FORCE_MODE0"		, 0x1280 },
	{ "FCONVA_SET_FORCE_GY0"		, 0x1284 },
	{ "FCONVA_SET_FORCE_BCB0"		, 0x1288 },
	{ "FCONVA_SET_FORCE_RCR0"		, 0x128C },
	{ "FCONVA_SET_FORCE_A0"			, 0x1290 },
	{ "FCONVA_SET_CROP0"			, 0x12B0 },
	{ "FCONVA_SET_IN_FORMAT1"		, 0x1300 },
	{ "FCONVA_SET_IN_HSIZE1"		, 0x1304 },
	{ "FCONVA_SET_IN_VSIZE1"		, 0x1308 },
	{ "FCONVA_SET_IN_BASEADDR_GY1"		, 0x1310 },
	{ "FCONVA_SET_IN_BASEADDR_BCB1"		, 0x1314 },
	{ "FCONVA_SET_IN_BASEADDR_RCR1"		, 0x1318 },
	{ "FCONVA_SET_IN_PITCH_GY1"		, 0x131C },
	{ "FCONVA_SET_IN_PITCH_BCB1"		, 0x1320 },
	{ "FCONVA_SET_IN_PITCH_RCR1"		, 0x1324 },
	{ "FCONVA_SET_OUT_FORMAT1"		, 0x1340 },
	{ "FCONVA_SET_OUT_HSIZE1"		, 0x1344 },
	{ "FCONVA_SET_OUT_VSIZE1"		, 0x1348 },
	{ "FCONVA_SET_OUT_BASEADDR_GY1"		, 0x1350 },
	{ "FCONVA_SET_OUT_BASEADDR_BCB1"	, 0x1354 },
	{ "FCONVA_SET_OUT_BASEADDR_RCR1"	, 0x1358 },
	{ "FCONVA_SET_OUT_PITCH_GY1"		, 0x135C },
	{ "FCONVA_SET_OUT_PITCH_BCB1"		, 0x1360 },
	{ "FCONVA_SET_OUT_PITCH_RCR1"		, 0x1364 },
	{ "FCONVA_SET_FORCE_MODE1"		, 0x1380 },
	{ "FCONVA_SET_FORCE_GY1"		, 0x1384 },
	{ "FCONVA_SET_FORCE_BCB1"		, 0x1388 },
	{ "FCONVA_SET_FORCE_RCR1"		, 0x138C },
	{ "FCONVA_SET_FORCE_A1"			, 0x1390 },
	{ "FCONVA_SET_CROP1"			, 0x13B0 },
	{ "FCONVB_START"			, 0x2000 },
	{ "FCONVB_ABORT"			, 0x2004 },
	{ "FCONVB_SET_DUMMY_READ"		, 0x2010 },
	{ "FCONVB_SET_BUSIF"			, 0x2014 },
	{ "FCONVB_SET_SEL_ALPHA"		, 0x2018 },
	{ "FCONVB_IRQ"				, 0x2020 },
	{ "FCONVB_SET_IRQ_MASK"			, 0x2024 },
	{ "FCONVB_TRANS_IN_FORMAT"		, 0x2100 },
	{ "FCONVB_TRANS_IN_HSIZE"		, 0x2104 },
	{ "FCONVB_TRANS_IN_VSIZE"		, 0x2108 },
	{ "FCONVB_TRANS_IN_BASEADDR_GY"		, 0x2110 },
	{ "FCONVB_TRANS_IN_BASEADDR_BCB"	, 0x2114 },
	{ "FCONVB_TRANS_IN_BASEADDR_RCR"	, 0x2118 },
	{ "FCONVB_TRANS_IN_PITCH_GY"		, 0x211C },
	{ "FCONVB_TRANS_IN_PITCH_BCB"		, 0x2120 },
	{ "FCONVB_TRANS_IN_PITCH_RCR"		, 0x2124 },
	{ "FCONVB_TRANS_OUT_FORMAT"		, 0x2140 },
	{ "FCONVB_TRANS_OUT_HSIZE"		, 0x2144 },
	{ "FCONVB_TRANS_OUT_VSIZE"		, 0x2148 },
	{ "FCONVB_TRANS_OUT_BASEADDR_GY"	, 0x2150 },
	{ "FCONVB_TRANS_OUT_BASEADDR_BCB"	, 0x2154 },
	{ "FCONVB_TRANS_OUT_BASEADDR_RCR"	, 0x2158 },
	{ "FCONVB_TRANS_OUT_PITCH_GY"		, 0x215C },
	{ "FCONVB_TRANS_OUT_PITCH_BCB"		, 0x2160 },
	{ "FCONVB_TRANS_OUT_PITCH_RCR"		, 0x2164 },
	{ "FCONVB_TRANS_FORCE_MODE"		, 0x2180 },
	{ "FCONVB_CH_FORCE_GY"			, 0x2184 },
	{ "FCONVB_CH_FORCE_BCB"			, 0x2188 },
	{ "FCONVB_CH_FORCE_R"			, 0x218C },
	{ "FCONVB_CH_FORCE_A"			, 0x2190 },
	{ "FCONVB_TRANS_CROP"			, 0x21B0 },
	{ "FCONVB_TRANS_STATUS"			, 0x21D0 },
	{ "FCONVB_TRANS_LINE"			, 0x21D4 },
	{ "FCONVB_SET_IN_FORMAT0"		, 0x2200 },
	{ "FCONVB_SET_IN_HSIZE0"		, 0x2204 },
	{ "FCONVB_SET_IN_VSIZE0"		, 0x2208 },
	{ "FCONVB_SET_IN_BASEADDR_GY0"		, 0x2210 },
	{ "FCONVB_SET_IN_BASEADDR_BCB0"		, 0x2214 },
	{ "FCONVB_SET_IN_BASEADDR_RCR0"		, 0x2218 },
	{ "FCONVB_SET_IN_PITCH_GY0"		, 0x221C },
	{ "FCONVB_SET_IN_PITCH_BCB0"		, 0x2220 },
	{ "FCONVB_SET_IN_PITCH_RCR0"		, 0x2224 },
	{ "FCONVB_SET_OUT_FORMAT0"		, 0x2240 },
	{ "FCONVB_SET_OUT_HSIZE0"		, 0x2244 },
	{ "FCONVB_SET_OUT_VSIZE0"		, 0x2248 },
	{ "FCONVB_SET_OUT_BASEADDR_GY0"		, 0x2250 },
	{ "FCONVB_SET_OUT_BASEADDR_BCB0"	, 0x2254 },
	{ "FCONVB_SET_OUT_BASEADDR_RCR0"	, 0x2258 },
	{ "FCONVB_SET_OUT_PITCH_GY0"		, 0x225C },
	{ "FCONVB_SET_OUT_PITCH_BCB0"		, 0x2260 },
	{ "FCONVB_SET_OUT_PITCH_RCR0"		, 0x2264 },
	{ "FCONVB_SET_FORCE_MODE0"		, 0x2280 },
	{ "FCONVB_SET_FORCE_GY0"		, 0x2284 },
	{ "FCONVB_SET_FORCE_BCB0"		, 0x2288 },
	{ "FCONVB_SET_FORCE_RCR0"		, 0x228C },
	{ "FCONVB_SET_FORCE_A0"			, 0x2290 },
	{ "FCONVB_SET_CROP0"			, 0x22B0 },
	{ "FCONVB_SET_IN_FORMAT1"		, 0x2300 },
	{ "FCONVB_SET_IN_HSIZE1"		, 0x2304 },
	{ "FCONVB_SET_IN_VSIZE1"		, 0x2308 },
	{ "FCONVB_SET_IN_BASEADDR_GY1"		, 0x2310 },
	{ "FCONVB_SET_IN_BASEADDR_BCB1"		, 0x2314 },
	{ "FCONVB_SET_IN_BASEADDR_RCR1"		, 0x2318 },
	{ "FCONVB_SET_IN_PITCH_GY1"		, 0x231C },
	{ "FCONVB_SET_IN_PITCH_BCB1"		, 0x2320 },
	{ "FCONVB_SET_IN_PITCH_RCR1"		, 0x2324 },
	{ "FCONVB_SET_OUT_FORMAT1"		, 0x2340 },
	{ "FCONVB_SET_OUT_HSIZE1"		, 0x2344 },
	{ "FCONVB_SET_OUT_VSIZE1"		, 0x2348 },
	{ "FCONVB_SET_OUT_BASEADDR_GY1"		, 0x2350 },
	{ "FCONVB_SET_OUT_BASEADDR_BCB1"	, 0x2354 },
	{ "FCONVB_SET_OUT_BASEADDR_RCR1"	, 0x2358 },
	{ "FCONVB_SET_OUT_PITCH_GY1"		, 0x235C },
	{ "FCONVB_SET_OUT_PITCH_BCB1"		, 0x2360 },
	{ "FCONVB_SET_OUT_PITCH_RCR1"		, 0x2364 },
	{ "FCONVB_SET_FORCE_MODE1"		, 0x2380 },
	{ "FCONVB_SET_FORCE_GY1"		, 0x2384 },
	{ "FCONVB_SET_FORCE_BCB1"		, 0x2388 },
	{ "FCONVB_SET_FORCE_RCR1"		, 0x238C },
	{ "FCONVB_SET_FORCE_A1"			, 0x2390 },
	{ "FCONVB_SET_CROP1"			, 0x23B0 },
	{ "FCONVC_ACT"				, 0x3000 },
	{ "FCONVC_SETTING"			, 0x3004 },
	{ "FCONVC_KICKA_CHANNEL"		, 0x3010 },
	{ "FCONVC_KICKA_TB"			, 0x3014 },
	{ "FCONVC_KICKB_CHANNEL"		, 0x3018 },
	{ "FCONVC_KICKB_TB"			, 0x301C },
	{ "FCONVC_MGSETTING"			, 0x3020 },
	{ "FCONVC_DSIERRFIXVAL"			, 0x3024 }
};

static inline void plane_a_set(void);
static inline void plane_b_set(void);
static inline void plane_a_display_position(void);
static inline void plane_b_display_position(void);


static void applitefb_reg_write(u32 mode, u32 regist)
{
	lcdc_write(&priv,
		tz3000_reg_param[mode][regist].reg_offset,
		tz3000_reg_param[mode][regist].val);
}

/* waits till the vsync interruption. */
int applitefb_wait_for_frame_end(unsigned int fconv)
{
	int ret = 0;
	u32 fconva_irq_mask;
	u32 fconvb_irq_mask;

	fconva_irq_mask = lcdc_read(&priv, DISPIF_FCONVA_SET_IRQ_MASK_OFFS);
	fconvb_irq_mask = lcdc_read(&priv, DISPIF_FCONVB_SET_IRQ_MASK_OFFS);

#if defined(_TEST_VCODEC_PERFORMANCE_)	/* for VCODEC performance (enable FRAME_END Interrupt) */
		bPan = 1;
#endif
	_FNC_START("(fb%d)\n", fconv);

	if ((merge < 2) && (fconv != FCONVA))
		return 1; /* no timeout */

	/* Enable Frame End interrupt and be careful not to acknowledge any
	 * pending interrupt.
	 */
	switch (fconv) {
	case FCONVA:
		_DEV_LOG("wait for fconva transfer end\n", fconv);
		/* enable frame_end_mask */
		fconva_irq_mask &= ~FRAME_TRANSFER_END;
		lcdc_write(&priv,
			DISPIF_FCONVA_SET_IRQ_MASK_OFFS, fconva_irq_mask);

		ret = wait_for_completion_interruptible_timeout(
			&priv.fconva_frame_end_completion,
			msecs_to_jiffies(100));

		if (!ret) {
			_ERR_LOG("fb%d timeout!\n", fconv);
			return -ETIMEDOUT;
		} else if (ret < 0) {
			_ERR_LOG("fb%d err[%d]\n", fconv, ret);
			return ret;
		}
		_DEV_LOG("wake up!\n", fconv);
		break;
	case FCONVB:
		_DEV_LOG("wait for fconvb transfer end\n", fconv);
		/* enable frame_end_mask */
		fconvb_irq_mask &= ~FRAME_TRANSFER_END;
		lcdc_write(&priv,
			DISPIF_FCONVB_SET_IRQ_MASK_OFFS, fconvb_irq_mask);

		ret = wait_for_completion_interruptible_timeout(
			&priv.fconvb_frame_end_completion,
			msecs_to_jiffies(100));

		if (!ret) {
			dprint("%s : fconvb_frame_end timeout!\n",
				FB_DEVICE_NAME);
			return -ETIMEDOUT;
		} else if (ret < 0) {
			dprint("%s : fconvb_frame_end err[%d]\n",
				FB_DEVICE_NAME, ret);
			return ret;
		}
		dprint("%s : fconvb_frame_end wake up!\n", FB_DEVICE_NAME);
		break;
	}
	_FNC_END("\n");
	return ret;
}


int applitefb_wait_for_vsync(struct fb_info *info)
{
	int retval;
	struct applitefb_layer *layer = (struct applitefb_layer *)(info->par);
	_FNC_START("\n");

	retval = applitefb_wait_for_frame_end(layer->layer);
	_FNC_END("\n");
	return retval;
}

/* Function for get lcd_type */
__u32 get_display_mode(struct fb_var_screeninfo *var)
{
	__u32 display_mode = DISPLAY_MODE_1920_1080_30P;
	_FNC_START("\n");
	dprint("%s : var->xres[%d],var->yres[%d]\n",
		FB_DEVICE_NAME, var->xres, var->yres);
	if (var->xres <= 720 && var->yres <= 480) {
		display_mode = DISPLAY_MODE_720_480_60P;
		g_disp_xres = 720;
		g_disp_yres = 480;
	} else if (var->xres <= 1280 && var->yres <= 720) {
		display_mode = DISPLAY_MODE_1280_720_60P;
		g_disp_xres = 1280;
		g_disp_yres = 720;
	} else if (var->xres <= 1920 && var->yres <= 1080) {
		display_mode = DISPLAY_MODE_1920_1080_30P;
		g_disp_xres = 1920;
		g_disp_yres = 1080;
	}
	_FNC_END("(display_mode:%d)\n", display_mode);
	return display_mode;
}


/* Pan the display */
int pan_display(struct fb_var_screeninfo *var, struct fb_info *info)
{
	int ret, i;
	u32 offset[MAX_PLANE];
	struct applitefb_layer *layer = (struct applitefb_layer *)(info->par);

	switch (layer->format) {
	case Y_CB_CR420:
		offset[0] = info->fix.smem_start;
		offset[1] = offset[0] +
			info->var.yres_virtual * layer->line_length[0];
		offset[2] = offset[1] +
			info->var.yres_virtual / 2 * layer->line_length[1];
		offset[0] += (var->yoffset * info->var.xres_virtual) +
				(var->xoffset);
		offset[1] +=
			(var->yoffset * info->var.xres_virtual / 2) +
				 (var->xoffset / 2);
		offset[2] +=
			(var->yoffset * info->var.xres_virtual / 2) +
				 (var->xoffset / 2);
		break;
	case AYCBCR32:
		offset[0] = info->fix.smem_start;
		offset[1] = offset[0];
		offset[2] = offset[1];
		offset[0] += (var->yoffset * info->var.xres_virtual *
				info->var.bits_per_pixel / 8) +
					(var->xoffset * info->var.bits_per_pixel / 8);
		break;
	case Y_CB_CR444:
		offset[0] = info->fix.smem_start;
		offset[1] = offset[0] +
			info->var.yres_virtual * layer->line_length[0];
		offset[2] = offset[1] +
			info->var.yres_virtual * layer->line_length[1];
		offset[0] += (var->yoffset * info->var.xres_virtual) +
				(var->xoffset);
		offset[1] +=
				(var->yoffset * info->var.xres_virtual) +
					(var->xoffset);
		offset[2] +=
				(var->yoffset * info->var.xres_virtual) +
					(var->xoffset);
		break;
	case Y_CBCR420:
		offset[0] = info->fix.smem_start;
		offset[1] = offset[0] +
			info->var.yres_virtual * layer->line_length[0];
		offset[2] = offset[1];
		offset[0] += (var->yoffset * info->var.xres_virtual) +
				(var->xoffset);
		offset[1] +=
				(var->yoffset * info->var.xres_virtual / 2) +
						(var->xoffset);
		break;
	case Y_CB_CR422:
		offset[0] = info->fix.smem_start;
		offset[1] = offset[0] +
			info->var.yres_virtual * layer->line_length[0];
		offset[2] = offset[1] +
			info->var.yres_virtual * layer->line_length[1];
		offset[0] += (var->yoffset * info->var.xres_virtual) +
				(var->xoffset);
		offset[1] +=
				(var->yoffset * info->var.xres_virtual) +
					(var->xoffset / 2);
		offset[2] +=
				(var->yoffset * info->var.xres_virtual) +
					(var->xoffset / 2);
		break;
	default:
		offset[0] = offset[1] = offset[2] =
			info->fix.smem_start +
			(var->yoffset * info->var.xres_virtual *
			info->var.bits_per_pixel / 8) +
			(var->xoffset * info->var.bits_per_pixel / 8);
	}

	for (i = 0; i < MAX_PLANE; i++)
		layer->addr[i] = offset[i];

	_FNC_START("\n");
	/* Waiting for end of frame */
	ret = applitefb_wait_for_frame_end(layer->layer);

	if (!ret) {
		_ERR_LOG("pan_display() fconv%c timeout\n", 'a' + layer->layer);
		return -ETIMEDOUT;
	} else if (ret < 0) {
		_ERR_LOG("pan_display() fconv%c err\n", 'a' + layer->layer);
		return ret;
	}

	_FNC_END("\n");
	return ret;
}


/* Registration interrupt handler */
void regist_irq(struct platform_device *pdev)
{
	int i, retval, irq[10];

	_FNC_START("\n");

	for (i = 0; i < 10; i++)
		irq[i] = platform_get_irq(pdev, i);

	for (i = 0; i < 10; i++) {
		/* Registration interrupt handler */
		if ((irq[i] == IRQ_DISPIF_INTFRAME) ||
			(irq[i] == IRQ_DISPIF_INTERR)) {
			retval = request_irq(irq[i],
			handle_irq2, IRQF_SHARED, "applitefb", &priv);
			dprint("%s : regist handle_irq2[%d]\n",
				FB_DEVICE_NAME, irq[i]);
		} else {
			retval = request_irq(irq[i],
				handle_irq, IRQF_SHARED, "applitefb", &priv);
			dprint("%s : regist handle_irq[%d]\n",
				FB_DEVICE_NAME, irq[i]);
		}
		if (retval) {
			_ERR_LOG("request_irq[%d] failed\n", irq[i]);
			retval = -EBUSY;
			goto fail_1;
		}
	}
	_FNC_END("\n");
	return;

fail_1:
	/* Release of interruption */
	for ( ; i > 0; i--)
		free_irq(irq[i-1], &priv);
	return;
}

/* Release of interruption */
void _free_irq(struct platform_device *pdev)
{
	int i, irq;

	_FNC_START("\n");
	/* Release of interruption */
	for (i = 0; i < 10; i++) {
		irq = platform_get_irq(pdev, i);
		free_irq(irq, &priv);
	}

	_FNC_END("\n");
}

/* fconva register setting when framebuffer is initialized */
static void fconv_initialize(struct fb_var_screeninfo *var,
	unsigned int fconv)
{
	_FNC_START("(fconv:%d)\n", fconv);

	/* alpha setting */
	if (sel_alpha == 0)
		lcdc_write(&priv, regist[fconv][SET_SEL_ALPHA], 1);
	else
		lcdc_write(&priv, regist[fconv][SET_SEL_ALPHA], 0);

	/* offset of change YCbCr to RGB */
	lcdc_write(&priv, regist[fconv][Y2RMTX_OFFSET], C_OFFSET_IS_128);
	lcdc_write(&priv, regist[fconv][Y2RMTX_COEF00], C00_IS_128);
	lcdc_write(&priv, regist[fconv][Y2RMTX_COEF01], C01_IS_0);
	lcdc_write(&priv, regist[fconv][Y2RMTX_COEF02], C02_IS_179);
	lcdc_write(&priv, regist[fconv][Y2RMTX_COEF10], C10_IS_128);
	lcdc_write(&priv, regist[fconv][Y2RMTX_COEF11], C11_IS_980);
	lcdc_write(&priv, regist[fconv][Y2RMTX_COEF12], C12_IS_933);
	lcdc_write(&priv, regist[fconv][Y2RMTX_COEF20], C20_IS_128);
	lcdc_write(&priv, regist[fconv][Y2RMTX_COEF21], C21_IS_229);
	lcdc_write(&priv, regist[fconv][Y2RMTX_COEF22], C22_IS_0);
	lcdc_write(&priv, regist[fconv][RGBLIMIT], Y2R_RGBLIMIT_IS_255);

	/* fconva/b in/out setting */
	if (fconv)
		plane_b_set();
	else
		plane_a_set();

	lcdc_write(&priv, regist[fconv][FORCE_MODE0], FORCE_MODE_NOT_USE);
	_DEV_LOG("var->grayscale is (%d)\n", fconv, var->grayscale);
	if (var->grayscale) {
		lcdc_write(&priv, regist[fconv][FORCE_GY0], FORCE_GY0_IS_0);
		lcdc_write(&priv, regist[fconv][FORCE_BCB0], FORCE_BCB0_IS_128);
		lcdc_write(&priv, regist[fconv][FORCE_RCR0], FORCE_RCR0_IS_128);
	} else {
		lcdc_write(&priv, regist[fconv][FORCE_GY0], FORCE_GY0_IS_0);
		lcdc_write(&priv, regist[fconv][FORCE_BCB0], FORCE_BCB0_IS_0);
		lcdc_write(&priv, regist[fconv][FORCE_RCR0], FORCE_RCR0_IS_0);
	}

	/* setting of Cropping */
	lcdc_write(&priv, regist[fconv][CROP0], CROP0_IS_0);

	/* setting of interruption */
	/* enable to mask */
	/* clear of interruption */
	lcdc_write(&priv, regist[fconv][IRQ], IRQ_CLEAR);

	/* clear of mask */
	lcdc_write(&priv, regist[fconv][IRQ_MASK], IRQ__MASK_CLEAR);
	_FNC_END("\n");
}

static inline void plane_a_display_position(void)
{
	lcdc_write(&priv, DISPIF_FCONVA_SET_IN_HSIZE0_OFFS, g_fb_layer[plane_a_layer].dxres);
	lcdc_write(&priv, DISPIF_FCONVA_SET_IN_VSIZE0_OFFS, g_fb_layer[plane_a_layer].dyres);

	/* offset calculate */
	lcdc_write(&priv,
		DISPIF_FCONVA_SET_OUT_BASEADDR_GY0_OFFS, (u32)(g_out_baseaddr + g_out_baseaddr_offset[0]));
	lcdc_write(&priv,
		DISPIF_FCONVA_SET_OUT_BASEADDR_BCB0_OFFS, (u32)(g_out_baseaddr + g_out_baseaddr_offset[0]));
	lcdc_write(&priv,
		DISPIF_FCONVA_SET_OUT_BASEADDR_RCR0_OFFS, (u32)(g_out_baseaddr + g_out_baseaddr_offset[0]));

	g_fb_layer[plane_a_layer].xpos_old = g_fb_layer[plane_a_layer].xpos;
	g_fb_layer[plane_a_layer].ypos_old = g_fb_layer[plane_a_layer].ypos;
}

static inline void plane_b_display_position(void)
{

	lcdc_write(&priv, DISPIF_FCONVB_SET_IN_HSIZE0_OFFS, g_fb_layer[plane_b_layer].dxres);
	lcdc_write(&priv, DISPIF_FCONVB_SET_IN_VSIZE0_OFFS, g_fb_layer[plane_b_layer].dyres);

	/* offset calculate */
	lcdc_write(&priv,
		DISPIF_FCONVB_SET_OUT_BASEADDR_GY0_OFFS, (u32)(g_out_baseaddr + g_out_baseaddr_offset[1]));
	lcdc_write(&priv,
		DISPIF_FCONVB_SET_OUT_BASEADDR_BCB0_OFFS, (u32)(g_out_baseaddr + g_out_baseaddr_offset[1]));
	lcdc_write(&priv,
		DISPIF_FCONVB_SET_OUT_BASEADDR_RCR0_OFFS, (u32)(g_out_baseaddr + g_out_baseaddr_offset[1]));

	g_fb_layer[plane_b_layer].xpos_old = g_fb_layer[plane_b_layer].xpos;
	g_fb_layer[plane_b_layer].ypos_old = g_fb_layer[plane_b_layer].ypos;
}

static inline void plane_a_pan(void)
{
	struct applitefb_layer *layer = &(g_fb_layer[plane_a_layer]);

	lcdc_write(&priv,
		DISPIF_FCONVA_SET_IN_BASEADDR_GY0_OFFS, (u32)layer->addr[0]);
	lcdc_write(&priv,
		DISPIF_FCONVA_SET_IN_BASEADDR_BCB0_OFFS, (u32)layer->addr[1]);
	lcdc_write(&priv,
		DISPIF_FCONVA_SET_IN_BASEADDR_RCR0_OFFS, (u32)layer->addr[2]);
/*
	lcdc_write(&priv, DISPIF_FCONVC_KICKA_CHANNEL_OFFS, CHANNEL_IS_0);
*/
	if ((g_fb_layer[plane_a_layer].xpos != g_fb_layer[plane_a_layer].xpos_old) ||
		(g_fb_layer[plane_a_layer].ypos != g_fb_layer[plane_a_layer].ypos_old))
		plane_a_display_position();
}

static inline void plane_b_pan(void)
{
	struct applitefb_layer *layer = &(g_fb_layer[plane_b_layer]);

	lcdc_write(&priv,
		DISPIF_FCONVB_SET_IN_BASEADDR_GY0_OFFS, (u32)layer->addr[0]);
	lcdc_write(&priv,
		DISPIF_FCONVB_SET_IN_BASEADDR_BCB0_OFFS, (u32)layer->addr[1]);
	lcdc_write(&priv,
		DISPIF_FCONVB_SET_IN_BASEADDR_RCR0_OFFS, (u32)layer->addr[2]);
/*
	lcdc_write(&priv, DISPIF_FCONVC_KICKB_CHANNEL_OFFS, CHANNEL_IS_0);
*/
	if ((g_fb_layer[plane_b_layer].xpos != g_fb_layer[plane_b_layer].xpos_old) ||
		(g_fb_layer[plane_b_layer].ypos != g_fb_layer[plane_b_layer].ypos_old))
		plane_b_display_position();
}

void plane_pan(int node)
{
	_FNC_START("node[%d]\n", node);

	if (node == 0)
		plane_a_pan();
	else
		plane_b_pan();

	_FNC_END("\n");
}

/* fconva register setting */
static inline void plane_a_set(void)
{
	struct applitefb_layer *layer = &(g_fb_layer[plane_a_layer]);

	_FNC_START("\n");

	/* input format setting (channel0) */
	lcdc_write(&priv, DISPIF_FCONVA_SET_IN_FORMAT0_OFFS, layer->format);
	plane_a_display_position();
	lcdc_write(&priv,
		DISPIF_FCONVA_SET_IN_BASEADDR_GY0_OFFS, (u32)layer->addr[0]);
	lcdc_write(&priv,
		DISPIF_FCONVA_SET_IN_BASEADDR_BCB0_OFFS, (u32)layer->addr[1]);
	lcdc_write(&priv,
		DISPIF_FCONVA_SET_IN_BASEADDR_RCR0_OFFS, (u32)layer->addr[2]);
	lcdc_write(&priv,
		DISPIF_FCONVA_SET_IN_PITCH_GY0_OFFS, layer->line_length[0]);
	lcdc_write(&priv,
		DISPIF_FCONVA_SET_IN_PITCH_BCB0_OFFS, layer->line_length[1]);
	lcdc_write(&priv,
		DISPIF_FCONVA_SET_IN_PITCH_RCR0_OFFS, layer->line_length[2]);

	/* output format setting (channel0) */
	lcdc_write(&priv, DISPIF_FCONVA_SET_OUT_FORMAT0_OFFS, ABGR8888);
	lcdc_write(&priv, DISPIF_FCONVA_SET_OUT_HSIZE0_OFFS, g_disp_xres);
	lcdc_write(&priv, DISPIF_FCONVA_SET_OUT_VSIZE0_OFFS, g_disp_yres);
	lcdc_write(&priv,
		DISPIF_FCONVA_SET_OUT_PITCH_GY0_OFFS, g_disp_xres * sizeof(u32));
	lcdc_write(&priv,
		DISPIF_FCONVA_SET_OUT_PITCH_BCB0_OFFS, g_disp_xres * sizeof(u32));
	lcdc_write(&priv,
		DISPIF_FCONVA_SET_OUT_PITCH_RCR0_OFFS, g_disp_xres * sizeof(u32));
	lcdc_write(&priv, DISPIF_FCONVA_SET_FORCE_A0_OFFS, a_alpha);

	_FNC_END("\n");
}


/* fconvb register setting */
static inline void plane_b_set(void)
{
	struct applitefb_layer *layer = &(g_fb_layer[plane_b_layer]);

	_FNC_START("\n");

	/* input format setting (channel0) */
	lcdc_write(&priv, DISPIF_FCONVB_SET_IN_FORMAT0_OFFS, layer->format);
	plane_b_display_position();
	lcdc_write(&priv,
		DISPIF_FCONVB_SET_IN_BASEADDR_GY0_OFFS, (u32)layer->addr[0]);
	lcdc_write(&priv,
		DISPIF_FCONVB_SET_IN_BASEADDR_BCB0_OFFS, (u32)layer->addr[1]);
	lcdc_write(&priv,
		DISPIF_FCONVB_SET_IN_BASEADDR_RCR0_OFFS, (u32)layer->addr[2]);
	lcdc_write(&priv,
		DISPIF_FCONVB_SET_IN_PITCH_GY0_OFFS, layer->line_length[0]);
	lcdc_write(&priv,
		DISPIF_FCONVB_SET_IN_PITCH_BCB0_OFFS, layer->line_length[1]);
	lcdc_write(&priv,
		DISPIF_FCONVB_SET_IN_PITCH_RCR0_OFFS, layer->line_length[2]);

	/* output format setting (channel0) */
	lcdc_write(&priv, DISPIF_FCONVB_SET_OUT_FORMAT0_OFFS, ABGR8888);
	lcdc_write(&priv, DISPIF_FCONVB_SET_OUT_HSIZE0_OFFS, g_disp_xres);
	lcdc_write(&priv, DISPIF_FCONVB_SET_OUT_VSIZE0_OFFS, g_disp_yres);
	lcdc_write(&priv,
		DISPIF_FCONVB_SET_OUT_PITCH_GY0_OFFS, g_disp_xres * sizeof(u32));
	lcdc_write(&priv,
		DISPIF_FCONVB_SET_OUT_PITCH_BCB0_OFFS, g_disp_xres * sizeof(u32));
	lcdc_write(&priv,
		DISPIF_FCONVB_SET_OUT_PITCH_RCR0_OFFS, g_disp_xres * sizeof(u32));
	lcdc_write(&priv, DISPIF_FCONVB_SET_FORCE_A0_OFFS, b_alpha);

	_FNC_END("\n");
}

void plane_set(int node)
{
	_FNC_START("node[%d]\n", node);

	if (node == 0)
		plane_a_set();
	else
		plane_b_set();

	_FNC_END("\n");
}

/* fconvc register setting when framebuffer is initialized */
static void fconvc_initialize(struct fb_var_screeninfo *var)
{
	u32 fconvc_setting, fconvc_mgsetting;

	_FNC_START("\n");
	dprint("%s : merge is %lu\n", FB_DEVICE_NAME, merge);
	fconvc_setting = FCONVC_SETTING_ALL0;
	fconvc_mgsetting = ALPHAMODE_IS_0;

#if (CONFIG_APPLITEFB_ENABLE_LAYER == 1)
	merge = 0;
#endif
	switch (merge) {
	case MERGE_DISABLE_FB0_OUT:
	case MERGE_DISABLE_FB1_OUT:
		dprint("%s : merge is MERGE_DISABLE\n",
			FB_DEVICE_NAME);
		fconvc_setting = FCONVC_SETTING_ALL0;
		fconvc_mgsetting = ALPHAMODE_IS_0;
		break;
	case FB1_BACKGROUND_MERGE:
		dprint("%s : merge is FB1_BACKGROUND_MERGE\n",
			FB_DEVICE_NAME);
		fconvc_setting = MERGE_EN;
		fconvc_mgsetting = (ALPHAMODEA_IS_3 | ALPHAMODEB_IS_3);
		break;
	case FB0_BACKGROUND_MERGE:
		dprint("%s : merge is FB0_BACKGROUND_MERGE\n",
			FB_DEVICE_NAME);
		fconvc_setting = MERGE_EN;
		fconvc_mgsetting = (ALPHAMODEA_IS_0 | ALPHAMODEB_IS_0);
		break;
	}

	lcdc_write(&priv, DISPIF_FCONVC_ACT_OFFS, FCONVC_ACT_ON);
	lcdc_write(&priv, DISPIF_FCONVC_SETTING_OFFS, fconvc_setting);
	lcdc_write(&priv, DISPIF_FCONVC_KICKA_CHANNEL_OFFS, CHANNEL_IS_0);
	lcdc_write(&priv, DISPIF_FCONVC_KICKA_TB_OFFS, FIELD_IS_TOP);
	lcdc_write(&priv, DISPIF_FCONVC_KICKB_CHANNEL_OFFS, CHANNEL_IS_0);
	lcdc_write(&priv, DISPIF_FCONVC_KICKB_TB_OFFS, FIELD_IS_TOP);
	lcdc_write(&priv, DISPIF_FCONVC_MGSETTING_OFFS, fconvc_mgsetting);
	lcdc_write(&priv, DISPIF_FCONVC_DSIERRFIXVAL_OFFS, DSIERRFIXVAL_IS_0);

	_FNC_END("\n");
}

/* register setting when framebuffer is initialized */
void applitefb_lcdc_initialize(struct fb_var_screeninfo *var)
{
	int i, j, k;

	_FNC_START("\n");

#if IS_ENABLED(CONFIG_D2DP)
	/* reset d2dp */
	d2dp_reset();
	dprint("%s : d2dp_reset() finish\n", FB_DEVICE_NAME);
#endif

	udelay(500);
	for (k = 0; k < 2; k++) {
		pmu_write(&priv, PMU_SoftResetOff_dispifSS_0_OFFS,
			(PMU_SRST_ERST | PMU_SRST_ASYNCERST));
	}

	/* PLL enable */
	applitefb_reg_write(g_display_mode, DISPIF_PRD);
	applitefb_reg_write(g_display_mode, DISPIF_FBD);
	applitefb_reg_write(g_display_mode, DISPIF_FRS);
	applitefb_reg_write(g_display_mode, DISPIF_CKEN);
	applitefb_reg_write(g_display_mode, DISPIF_ENABLE);
	mdelay(1);

	/* LCDC Clk Gating ON */
	lcdc_write(&priv, DISPIF_DISPIF_CGATE_OFFS,
		(MDI_CGATE | DTG_CGATE | DSITX_CGATE | DSITX_HS_CGATE));

	/* adjust the output timing of DPHY Lane */
	lcdc_write(&priv, DISPIF_DSI_DPHY_CLW_DPHYCONTTX_OFFS, DPHY_LANE_CLW);
	lcdc_write(&priv, DISPIF_DSI_DPHY_D0W_DPHYCONTTX_OFFS, DPHY_LANE_D0W);
	lcdc_write(&priv, DISPIF_DSI_DPHY_D1W_DPHYCONTTX_OFFS, DPHY_LANE_D1W);
	lcdc_write(&priv, DISPIF_DSI_DPHY_D2W_DPHYCONTTX_OFFS, DPHY_LANE_D2W);
	lcdc_write(&priv, DISPIF_DSI_DPHY_D3W_DPHYCONTTX_OFFS, DPHY_LANE_D3W);

	/* LCDC DPHY Lane Disable */
	applitefb_reg_write(g_display_mode, DISPIF_DSI_DPHY_CLWCNTRL);
	applitefb_reg_write(g_display_mode, DISPIF_DSI_DPHY_D0WCNTRL);
	applitefb_reg_write(g_display_mode, DISPIF_DSI_DPHY_D1WCNTRL);
	applitefb_reg_write(g_display_mode, DISPIF_DSI_DPHY_D2WCNTRL);
	applitefb_reg_write(g_display_mode, DISPIF_DSI_DPHY_D3WCNTRL);

#if IS_ENABLED(CONFIG_D2DP)
	/* initialize d2dp */
	d2dp_init(g_display_mode);
	dprint("%s : d2dp_init() finish\n", FB_DEVICE_NAME);
#endif

	/* LCDC DSI register initialize */
	applitefb_reg_write(g_display_mode, DISPIF_DSI_PPI_LPTXTIMECNT);
	applitefb_reg_write(g_display_mode, DISPIF_DSI_PPI_TCLK_HEADERCNT);
	applitefb_reg_write(g_display_mode, DISPIF_DSI_PPI_TCLK_TRAILCNT);
	applitefb_reg_write(g_display_mode, DISPIF_DSI_PPI_THS_HEADERCNT);
	applitefb_reg_write(g_display_mode, DISPIF_DSI_PPI_TWAKEUP);
	applitefb_reg_write(g_display_mode, DISPIF_DSI_PPI_TCLK_POSTCNT);
	applitefb_reg_write(g_display_mode, DISPIF_DSI_PPI_THS_TRAILCNT);
	applitefb_reg_write(g_display_mode, DISPIF_DSI_PPI_HSTXVREGCNT);
	applitefb_reg_write(g_display_mode, DISPIF_DSI_PPI_HSTXVREGTN);
	applitefb_reg_write(g_display_mode, DISPIF_DSI_PPI_TXOPTIONCNTRL);
	applitefb_reg_write(g_display_mode, DISPIF_DSI_PPI_BTACNTRL1);
	applitefb_reg_write(g_display_mode, DISPIF_DSI_PPI_STARTCNTRL);

	/* LCDC DSI initialize */
	lcdc_write(&priv, DISPIF_DSI_START_OFFS, DSI_START);

	/* LCDC DSITX PAUSE */
	lcdc_write(&priv, DISPIF_DSI_PAUSE_OFFS, DSI_PAUSE);

	/* FrameBuffer setting */
	/* FCONVA setting */
	fconv_initialize(var, FCONVA);

	/* FCONVB setting */
	fconv_initialize(var, FCONVB);

	/* FCONVC setting */
	fconvc_initialize(var);

	/* LCDC IRQ initialize */
	/* clear of IRQ status */
	lcdc_write(&priv, DISPIF_IRQ_STAT_OFFS,
		VSYNC_IRQ_STAT | VBLK_EDGE_IRQ_STAT | HBLK_START_IRQ3_STAT |
		HBLK_START_IRQ2_STAT | HBLK_START_IRQ1_STAT |
		VBLK_START_IRQ_STAT | VBLK_END_IRQ_STAT);

	/* clear of mask */
	lcdc_write(&priv, DISPIF_IRQ_EN_OFFS, IRQ_EN_CLEAR);


	/* LCDC DSI clear */
	/* delete of interruption 1:delete */
	lcdc_write(&priv, DISPIF_DSI_INT_CLR_OFFS, DSI_CLEAR);

	/* LCDC DTG setting */
	applitefb_reg_write(g_display_mode, DISPIF_HV_DLY);
	applitefb_reg_write(g_display_mode, DISPIF_HV_MAX);
	applitefb_reg_write(g_display_mode, DISPIF_HD);
	applitefb_reg_write(g_display_mode, DISPIF_VD_R);
	applitefb_reg_write(g_display_mode, DISPIF_VD_F);
	applitefb_reg_write(g_display_mode, DISPIF_HBLK);
	applitefb_reg_write(g_display_mode, DISPIF_VBLK);
	applitefb_reg_write(g_display_mode, DISPIF_HS_0);
	applitefb_reg_write(g_display_mode, DISPIF_HBLK2);
	applitefb_reg_write(g_display_mode, DISPIF_HD2);
	applitefb_reg_write(g_display_mode, DISPIF_HS_0_SET1);
	applitefb_reg_write(g_display_mode, DISPIF_HS_0_SET2);
	applitefb_reg_write(g_display_mode, DISPIF_MDI_GO);

	/* LCDC CQ setting */
	for (j = 0; j < NOP_COUNT_MAX; j++)
		lcdc_write(&priv, DISPIF_FCONVA_IRQ_OFFS, FCONVA_IRQ_CLEAR);

	for (i = 0; i < COMMANDQUEUE_MAX; i++) {
		if (tz3000_CQ_reg_param[g_display_mode][i].reg_flag != 1) {
			lcdc_write(&priv,
				tz3000_CQ_reg_param[g_display_mode][i].reg_offset,
				tz3000_CQ_reg_param[g_display_mode][i].val);
			for (j = 0; j < NOP_COUNT_MAX; j++)
				lcdc_write(&priv, DISPIF_FCONVA_IRQ_OFFS, FCONVA_IRQ_CLEAR);
		}
	}

	/* LCDC DSITX CONTINUE */
	lcdc_write(&priv, DISPIF_DSI_CONTINUE_OFFS, DSI_CONTINUE);

	mdelay(2);

	/* LCDC DTG START */
	lcdc_write(&priv, DISPIF_DTG_START_OFFS, DTG_START);

	_FNC_END("\n");
}

/* register setting when framebuffer is finalized */
void applitefb_lcdc_finalize(void)
{
	u32 dtg_stat;
	int i = 0;

	_FNC_START("\n");

	/* LCDC DTG STOP */
	lcdc_write(&priv, DISPIF_DTG_STOP_OFFS, DTG_STOP);

	mdelay(2);

	if (probe_flag != 0) {
		for (i = 0; i < DTG_STAT_READ_MAX; i++) {
			dtg_stat = lcdc_read(&priv, DISPIF_DTG_STAT_OFFS);
			if (dtg_stat == 0x0)
				break;
			mdelay(2);
		}
		if (i == DTG_STAT_READ_MAX)
			_ERR_LOG("status not disable. dtg_stat=0x%x\n", dtg_stat);
	} else
		probe_flag = 1;

	/* LCDC DSI RESET */
	lcdc_write(&priv, DISPIF_DSI_RESET_OFFS,
		(RST_LPFIFO | RST_RXFIFO | RST_CQ1 | RST_CQ0 | RST_CONF));

	/* LCDC IRQ CLEAR */
	lcdc_write(&priv, DISPIF_IRQ_STAT_OFFS,
		VSYNC_IRQ_STAT | VBLK_EDGE_IRQ_STAT | HBLK_START_IRQ3_STAT |
		HBLK_START_IRQ2_STAT | HBLK_START_IRQ1_STAT |
		VBLK_START_IRQ_STAT | VBLK_END_IRQ_STAT);
	lcdc_write(&priv, DISPIF_IRQ_EN_OFFS, IRQ_EN_CLEAR);
	lcdc_write(&priv, DISPIF_DSI_INT_CLR_OFFS, IRQ_EN_ERASE);

	/* LCDC DSI clear */
	/* delete of interruption 1:delete */
	lcdc_write(&priv, DISPIF_DSI_INT_CLR_OFFS, DSI_CLEAR);

	/* LCDC LANE DISABLE */
	lcdc_write(&priv, DISPIF_DSI_DPHY_CLWCNTRL_OFFS, LANE_DISABLE);
	lcdc_write(&priv, DISPIF_DSI_DPHY_D0WCNTRL_OFFS, LANE_DISABLE);
	lcdc_write(&priv, DISPIF_DSI_DPHY_D1WCNTRL_OFFS, LANE_DISABLE);
	lcdc_write(&priv, DISPIF_DSI_DPHY_D2WCNTRL_OFFS, LANE_DISABLE);
	lcdc_write(&priv, DISPIF_DSI_DPHY_D3WCNTRL_OFFS, LANE_DISABLE);

	/* CLOCKGATING ON */
	lcdc_write(&priv, DISPIF_DISPIF_CGATE_OFFS, CGATE_ON);
	mdelay(1);
	pmu_write(&priv, PMU_SoftResetOn_dispifSS_0_OFFS,
		(PMU_SRST_ERST | PMU_SRST_ASYNCERST));

	d2dp_reset();

	_FNC_END("\n");
}


/* Interrupt handler */
irqreturn_t handle_irq(int irq, void *data)
{
	unsigned long flag;
	u32 irq_stat, irq_en, irq_clear, dsi_int, dsi_clear;

	/* interruption status 1:generated interruption */
	irq_stat = lcdc_read(&priv, DISPIF_IRQ_STAT_OFFS);

	/* mask of interruption 0:interruption is be masked */
	irq_en = lcdc_read(&priv, DISPIF_IRQ_EN_OFFS);
	irq_clear = (irq_stat & irq_en);

	/* management of DSI interruption */
	dsi_int   = lcdc_read(&priv, DISPIF_DSI_INT_OFFS);
	dsi_clear = (dsi_int & DSI_INT_MASK);

	spin_lock_irqsave(&priv.lcdc_slock, flag);

	/* clear of interruption */
	lcdc_write(&priv, DISPIF_IRQ_STAT_OFFS, irq_clear);

	/* delete of interruption 1:delete */
	lcdc_write(&priv, DISPIF_DSI_INT_CLR_OFFS, dsi_clear);

	spin_unlock_irqrestore(&priv.lcdc_slock, flag);
	return IRQ_HANDLED;
}

/* Interrupt handler */
irqreturn_t handle_irq2(int irq, void *data)
{
	unsigned long flag;
	u32 fconva_irq, fconvb_irq, fconva_irq_mask, fconvb_irq_mask;

	spin_lock_irqsave(&priv.lcdc_slock, flag);

	/* interruption status of fconva 1:assert */
	fconva_irq = lcdc_read(&priv, DISPIF_FCONVA_IRQ_OFFS);
	fconva_irq_mask = lcdc_read(&priv, DISPIF_FCONVA_SET_IRQ_MASK_OFFS);
	/* clear of interruption */
	/* deassert all interruption of fconva */
	lcdc_write(&priv, DISPIF_FCONVA_IRQ_OFFS,
		MERGE_ERR_IRQ | OUTPUT_DELAY_IRQ | REGISTER_SET_ERR_IRQ
		| START_TIMING_ERR_IRQ | FRAME_TRANSFER_END_IRQ);
	/* frame transfer interruption */
	if (!(fconva_irq_mask & FRAME_TRANSFER_END_IRQ) && (fconva_irq & FRAME_TRANSFER_END_IRQ)) {
#if defined(_TEST_VCODEC_PERFORMANCE_)	/* for VCODEC performance (enable FRAME_END Interrupt) */
		counter++;
		if (bPan == 1) {
			bPan = 0;
			if ((prev_counter + 1) < counter) {
				_ERR_LOG("[VCODEC] counter over (%d, %d)\n",
					counter, prev_counter);
			}
			prev_counter = counter;
#endif
		dprint("%s : wake up fconva\n", FB_DEVICE_NAME);

		plane_a_pan();

#if defined(_TEST_VCODEC_PERFORMANCE_)	/* for VCODEC performance (enable FRAME_END Interrupt) */
#else
		/* disable frame_end_mask */
		fconva_irq_mask |= FRAME_TRANSFER_END;
		lcdc_write(&priv,
			DISPIF_FCONVA_SET_IRQ_MASK_OFFS, fconva_irq_mask);
#endif

		complete(&priv.fconva_frame_end_completion);	/* wake up */
#if defined(_TEST_VCODEC_PERFORMANCE_)	/* for VCODEC performance (enable FRAME_END Interrupt) */
		}
#endif
	}

	/* interruption status of fconvb 1:assert */
	fconvb_irq = lcdc_read(&priv, DISPIF_FCONVB_IRQ_OFFS);
	fconvb_irq_mask = lcdc_read(&priv, DISPIF_FCONVB_SET_IRQ_MASK_OFFS);
	/* clear of interruption */
	/* deassert all interruption of fconvb */
	lcdc_write(&priv, DISPIF_FCONVB_IRQ_OFFS,
		MERGE_ERR_IRQ | OUTPUT_DELAY_IRQ | REGISTER_SET_ERR_IRQ
		| START_TIMING_ERR_IRQ | FRAME_TRANSFER_END_IRQ);
	if (!(fconvb_irq_mask & FRAME_TRANSFER_END_IRQ) && (fconvb_irq & FRAME_TRANSFER_END_IRQ)) {
		dprint("%s : wake up fconvb\n", FB_DEVICE_NAME);

		plane_b_pan();
		fconvb_irq_mask |= FRAME_TRANSFER_END;
		lcdc_write(&priv,
			DISPIF_FCONVB_SET_IRQ_MASK_OFFS, fconvb_irq_mask);

		complete(&priv.fconvb_frame_end_completion);	/* wake up */
	}

	if (fconva_irq & START_TIMING_ERR_IRQ)
		_ERR_LOG("fconva: START_ERROR_IRQ\n");
	if (fconva_irq & REGISTER_SET_ERR_IRQ)
		_ERR_LOG("fconva:REG_ERROR_IRQ\n");
	if (fconva_irq & OUTPUT_DELAY_IRQ)
		_ERR_LOG("fconva:DISP_ERROR_IRQ\n");
	if (fconva_irq & MERGE_ERR_IRQ)
		_ERR_LOG("fconva:MERGE_ERROR_IRQ\n");

	if (fconvb_irq & START_TIMING_ERR_IRQ)
		_ERR_LOG("fconvb: START_ERROR_IRQ\n");
	if (fconvb_irq & REGISTER_SET_ERR_IRQ)
		_ERR_LOG("fconvb:REG_ERROR_IRQ\n");
	if (fconvb_irq & OUTPUT_DELAY_IRQ)
		_ERR_LOG("fconvb:DISP_ERROR_IRQ\n");
	if (fconvb_irq & MERGE_ERR_IRQ)
		_ERR_LOG("fconvb:MERGE_ERROR_IRQ\n");

	spin_unlock_irqrestore(&priv.lcdc_slock, flag);
	return IRQ_HANDLED;
}

int applitefb_local_ioctl(struct fb_info *info, unsigned int cmd,
			  unsigned long arg)
{
	return -ENOIOCTLCMD;
}

int applitefb_hw_start(void)
{
	_FNC_START("\n");
	/* start clock */
	clk_prepare_enable(priv.clk_dispif);

	_FNC_END("\n");
	return 0;
}

int applitefb_hw_stop(void)
{
	_FNC_START("\n");

	probe_flag = 0;
	/* stop clock */
	clk_disable_unprepare(priv.clk_dispif);

	_FNC_END("\n");
	return 0;
}

int applitefb_runtime_suspend(struct device *dev)
{
	_FNC_START("\n");
	/* stop clock */
	clk_disable_unprepare(priv.clk_dispif);

	_FNC_END("\n");
	return 0;
}

int applitefb_runtime_resume(struct device *dev)
{
	_FNC_START("\n");
	/* start clock */
	clk_prepare_enable(priv.clk_dispif);

	_FNC_END("\n");
	return 0;
}

void plane_output(int output)
{
	fconvc_initialize(NULL);

	if (output == 0) {
		plane_a_layer = 0;
		plane_b_layer = 1;
		g_fb_layer[0].layer = 0;
		g_fb_layer[1].layer = 1;
		plane_a_set();
		plane_b_set();
		_DBG_LOG("output=0, plane_a_layer=0, plane_b_layer=1\n");
	} else if (output == 1) {
		plane_a_layer = 1;
		plane_b_layer = 0;
		g_fb_layer[0].layer = 1;
		g_fb_layer[1].layer = 0;
		plane_a_set();
		_DBG_LOG("output=1, plane_a_layer=1, plane_b_layer=0\n");
	}
}

