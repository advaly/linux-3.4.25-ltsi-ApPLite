/*
 * linux/drivers/video/applite/d2dp.h
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
#if !defined(__FRAMEBUFFER_D2DP_MODULE_H__)
#define __FRAMEBUFFER_D2DP_MODULE_H__


#define D2DP_I2C_ADDR			0x0f
#define D2DP_I2C_BUS			2		/* /dev/i2c-2 */

/* DP Link Init */
#define IDREG_OFFS			0x0500
#define DP0_SRCCTRL_OFFS		0x06a0
#define DP1_SRCCTRL_OFFS		0x07a0
#define SYS_PLLPARAM_OFFS		0x0918
#define DP_PHY_CTRL_OFFS		0x0800
#define DP0_PLLCTRL_OFFS		0x0900
#define DP1_PLLCTRL_OFFS		0x0904
#define PXL_PLLPARAM_OFFS		0x0914
#define PXL_PLLCTRL_OFFS		0x0908
#define DP0_AUXCFG1_OFFS		0x0664
#define DP0_AUXADDR_OFFS		0x0668
#define DP0_AUXCFG0_OFFS		0x0660
#define DP0_AUXSTATUS_OFFS		0x068c
#define DP0_AUXRDATA0_OFFS		0x067c
#define AUXWDATA0_OFFS			0x066c
#define DP0_SNKLTCTRL_OFFS		0x06e4
#define DP0_LTLOOPCTRL_OFFS		0x06d8
#define DP0CTL_OFFS			0x0600
#define DP0_LTSTAT_OFFS			0x06d0
#define DP0_AUXRDATA1_OFFS		0x0680

/* Setup DSI video signal */
#define PPI_TX_RX_TA_OFFS		0x013c
#define PPI_LPTXTIMECNT_OFFS		0x0114
#define CLRSIPOCOUNT0_OFFS		0x0164
#define CLRSIPOCOUNT1_OFFS		0x0168
#define CLRSIPOCOUNT2_OFFS		0x016c
#define CLRSIPOCOUNT3_OFFS		0x0170
#define PPI_LANEENABLE_OFFS		0x0134
#define DSI_LANEENABLE_OFFS		0x0210
#define PPI_STARTPPI_OFFS		0x0104
#define DSI_STARTDSI_OFFS		0x0204
#define VPCTRL0_OFFS			0x0450
#define HTIM01_OFFS			0x0454
#define HTIM02_OFFS			0x0458
#define VTIM01_OFFS			0x045c
#define VTIM02_OFFS			0x0460
#define VFUEN0_OFFS			0x0464
#define DP0_VIDSYNCDLY_OFFS		0x0644
#define DP0_TOTALVAL_OFFS		0x0648
#define DP0_STARTVAL_OFFS		0x064c
#define DP0_ACTIVEVAL_OFFS		0x0650
#define DP0_SYNCVAL_OFFS		0x0654
#define DP0_MISC_OFFS			0x0658
#define D2DPTESTCTL_OFFS		0x0A00
#define DP0_VID_FM_OFFS			0x0610
#define DP0_VID_N_OFFS			0x0614
#define SYSCTRL_OFFS			0x0510
#define DP0_VID_M_OFFS			0x0618
#define SYSSTAT_OFFS			0x0508
#define DSI_INTSTATUS_OFFS		0x0220
#define PARALLEL_OUT_OFFS		0x0448


/*===================================
Exported Functions prototypes
===================================*/
void d2dp_reset(void);
int d2dp_init(u32);

/* Register Management Structure */
struct reg_param_d2dp {
	u16 reg_offset;
	u32 val;
};

#endif	/* __FRAMEBUFFER_D2DP_MODULE_H__ */

