/*
 * arch/arm/mach-tz2000/include/mach/regs/yuvc_reg_struct_l.h
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
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef _YUVC_REG_STRUCT_L_H
#define _YUVC_REG_STRUCT_L_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // YUVC_START Register
struct YUVC_YUVC_START {
	unsigned int yuvc_start:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // YUVC_RESET Register
struct YUVC_YUVC_RESET {
	unsigned int yuvc_reset:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // YUVC_MODE Register
struct YUVC_YUVC_MODE {
	unsigned int cf_inmode:2;		// [1:0]
	unsigned int reserved4:2;		// [3:2]
	unsigned int cf_outmode:2;		// [5:4]
	unsigned int reserved3:2;		// [7:6]
	unsigned int cf_rgblimit:1;		// [8]
	unsigned int reserved2:7;		// [15:9]
	unsigned int cf_alpha:8;		// [23:16]
	unsigned int reserved:8;		// [31:24]
};
 // YUVC_SIZE Register
struct YUVC_YUVC_SIZE {
	unsigned int cf_hsize:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int cf_vsize:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // YUVC_OFFSET_Y Register
struct YUVC_YUVC_OFFSET_Y {
	unsigned int cf_yoffset:9;		// [8:0]
	unsigned int reserved:23;		// [31:9]
};
 // YUVC_OFFSET_UV Register
struct YUVC_YUVC_OFFSET_UV {
	unsigned int cf_voffset:9;		// [8:0]
	unsigned int reserved2:7;		// [15:9]
	unsigned int cf_uoffset:9;		// [24:16]
	unsigned int reserved:7;		// [31:25]
};
 // YUVC_YCOEF_RG Register
struct YUVC_YUVC_YCOEF_RG {
	unsigned int cf_ycoef_g:9;		// [8:0]
	unsigned int reserved2:7;		// [15:9]
	unsigned int cf_ycoef_r:9;		// [24:16]
	unsigned int reserved:7;		// [31:25]
};
 // YUVC_YCOEF_B Register
struct YUVC_YUVC_YCOEF_B {
	unsigned int cf_ycoef_b:9;		// [8:0]
	unsigned int reserved:23;		// [31:9]
};
 // YUVC_UCOEF_RG Register
struct YUVC_YUVC_UCOEF_RG {
	unsigned int cf_ucoef_g:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_ucoef_r:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // YUVC_UCOEF_B Register
struct YUVC_YUVC_UCOEF_B {
	unsigned int cf_ucoef_b:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // YUVC_VCOEF_RG Register
struct YUVC_YUVC_VCOEF_RG {
	unsigned int cf_vcoef_g:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_vcoef_r:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // YUVC_VCOEF_B Register
struct YUVC_YUVC_VCOEF_B {
	unsigned int cf_vcoef_b:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // YUVC_OFFSET_RG Register
struct YUVC_YUVC_OFFSET_RG {
	unsigned int cf_goffset:9;		// [8:0]
	unsigned int reserved2:7;		// [15:9]
	unsigned int cf_roffset:9;		// [24:16]
	unsigned int reserved:7;		// [31:25]
};
 // YUVC_OFFSET_B Register
struct YUVC_YUVC_OFFSET_B {
	unsigned int cf_boffset:9;		// [8:0]
	unsigned int reserved:23;		// [31:9]
};
 // YUVC_STADR Register
struct YUVC_YUVC_STADR {
	unsigned int cf_mb_stadr:32;		// [31:0]
};
 // YUVC_ENDADR Register
struct YUVC_YUVC_ENDADR {
	unsigned int cf_mb_endadr:32;		// [31:0]
};
 // YUVC_DMRADR Register
struct YUVC_YUVC_DMRADR {
	unsigned int cf_dr_adr:32;		// [31:0]
};
 // YUVC_CFG Register
struct YUVC_YUVC_CFG {
	unsigned int cf_dr_enable_g00:1;		// [0]
};
 // YUVC_INT_MASK Register
struct YUVC_YUVC_INT_MASK {
	unsigned int cf_int_mask_g00:1;		// [0]
	unsigned int reserved2:14;		// [14:1]
	unsigned int cf_mb_err_mask:1;		// [15]
	unsigned int cf_abort_mask_g00:1;		// [16]
	unsigned int reserved:15;		// [31:17]
};
 // YUVC_W_ENABLE Register
struct YUVC_YUVC_W_ENABLE {
	unsigned int cf_enable_w00:1;		// [0]
	unsigned int cf_enable_w01:1;		// [1]
	unsigned int reserved:30;		// [31:2]
};
 // YUVC_W00_STADR Register
struct YUVC_YUVC_W00_STADR {
	unsigned int cf_stadr_w00:32;		// [31:0]
};
 // YUVC_W00_ENDADR Register
struct YUVC_YUVC_W00_ENDADR {
	unsigned int cf_endadr_w00:32;		// [31:0]
};
 // YUVC_W00_HEIGHT Register
struct YUVC_YUVC_W00_HEIGHT {
	unsigned int cf_height_w00:12;		// [11:0]
	unsigned int reserved:20;		// [31:12]
};
 // YUVC_W00_PITCH Register
struct YUVC_YUVC_W00_PITCH {
	unsigned int cf_pitch_w00:16;		// [15:0]
	unsigned int reserved:16;		// [31:16]
};
 // YUVC_W00_CFG0 Register
struct YUVC_YUVC_W00_CFG0 {
	unsigned int reserved4:8;		// [7:0]
	unsigned int cf_datawidth_w00:2;		// [9:8]
};
 // YUVC_W00_SRAM_BASE Register
struct YUVC_YUVC_W00_SRAM_BASE {
	unsigned int cf_sram_base_w00:6;		// [5:0]
	unsigned int reserved:26;		// [31:6]
};
 // YUVC_W00_SRAM_SIZE Register
struct YUVC_YUVC_W00_SRAM_SIZE {
	unsigned int cf_sram_size_w00:6;		// [5:0]
	unsigned int reserved:26;		// [31:6]
};
 // YUVC_W00_INTL Register
struct YUVC_YUVC_W00_INTL {
	unsigned int cf_interval_w00:6;		// [5:0]
	unsigned int cf_init_interval_w00:6;		// [11:6]
	unsigned int reserved2:4;		// [15:12]
	unsigned int cf_init_interval_period_w00:8;		// [23:16]
	unsigned int reserved:8;		// [31:24]
};
 // YUVC_W01_STADR Register
struct YUVC_YUVC_W01_STADR {
	unsigned int cf_stadr_w01:32;		// [31:0]
};
 // YUVC_W01_ENDADR Register
struct YUVC_YUVC_W01_ENDADR {
	unsigned int cf_endadr_w01:32;		// [31:0]
};
 // YUVC_W01_HEIGHT Register
struct YUVC_YUVC_W01_HEIGHT {
	unsigned int cf_height_w01:12;		// [11:0]
	unsigned int reserved:20;		// [31:12]
};
 // YUVC_W01_PITCH Register
struct YUVC_YUVC_W01_PITCH {
	unsigned int cf_pitch_w01:16;		// [15:0]
	unsigned int reserved:16;		// [31:16]
};
 // YUVC_W01_CFG0 Register
struct YUVC_YUVC_W01_CFG0 {
	unsigned int reserved4:8;		// [7:0]
	unsigned int cf_datawidth_w01:2;		// [9:8]
};
 // YUVC_W01_CFG1 Register
struct YUVC_YUVC_W01_CFG1 {
	unsigned int cf_maskbyte_w01:3;		// [2:0]
	unsigned int reserved2:13;		// [15:3]
	unsigned int cf_endian_w01:1;		// [16]
	unsigned int reserved:15;		// [31:17]
};
 // YUVC_W01_SRAM_BASE Register
struct YUVC_YUVC_W01_SRAM_BASE {
	unsigned int cf_sram_base_w01:6;		// [5:0]
	unsigned int reserved:26;		// [31:6]
};
 // YUVC_W01_SRAM_SIZE Register
struct YUVC_YUVC_W01_SRAM_SIZE {
	unsigned int cf_sram_size_w01:6;		// [5:0]
	unsigned int reserved:26;		// [31:6]
};
 // YUVC_W01_INTL Register
struct YUVC_YUVC_W01_INTL {
	unsigned int cf_interval_w01:6;		// [5:0]
	unsigned int cf_init_interval_w01:6;		// [11:6]
	unsigned int reserved2:4;		// [15:12]
	unsigned int cf_init_interval_period_w01:8;		// [23:16]
	unsigned int reserved:8;		// [31:24]
};
 // YUVC_MODE_BUF Register
struct YUVC_YUVC_MODE_BUF {
	unsigned int cf_inmode:2;		// [1:0]
	unsigned int reserved4:2;		// [3:2]
	unsigned int cf_outmode:2;		// [5:4]
	unsigned int reserved3:2;		// [7:6]
	unsigned int cf_rgblimit:1;		// [8]
	unsigned int reserved2:7;		// [15:9]
	unsigned int cf_alpha:8;		// [23:16]
	unsigned int reserved:8;		// [31:24]
};
 // YUVC_SIZE_BUF Register
struct YUVC_YUVC_SIZE_BUF {
	unsigned int cf_hsize:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int cf_vsize:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // YUVC_OFFSET_Y_BUF Register
struct YUVC_YUVC_OFFSET_Y_BUF {
	unsigned int cf_yoffset:9;		// [8:0]
	unsigned int reserved:23;		// [31:9]
};
 // YUVC_OFFSET_UV_BUF Register
struct YUVC_YUVC_OFFSET_UV_BUF {
	unsigned int cf_voffset:9;		// [8:0]
	unsigned int reserved2:7;		// [15:9]
	unsigned int cf_uoffset:9;		// [24:16]
	unsigned int reserved:7;		// [31:25]
};
 // YUVC_YCOEF_RG_BUF Register
struct YUVC_YUVC_YCOEF_RG_BUF {
	unsigned int cf_ycoef_g:9;		// [8:0]
	unsigned int reserved2:7;		// [15:9]
	unsigned int cf_ycoef_r:9;		// [24:16]
	unsigned int reserved:7;		// [31:25]
};
 // YUVC_YCOEF_B_BUF Register
struct YUVC_YUVC_YCOEF_B_BUF {
	unsigned int cf_ycoef_b:9;		// [8:0]
	unsigned int reserved:23;		// [31:9]
};
 // YUVC_UCOEF_RG_BUF Register
struct YUVC_YUVC_UCOEF_RG_BUF {
	unsigned int cf_ucoef_g:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_ucoef_r:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // YUVC_UCOEF_B_BUF Register
struct YUVC_YUVC_UCOEF_B_BUF {
	unsigned int cf_ucoef_b:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // YUVC_VCOEF_RG_BUF Register
struct YUVC_YUVC_VCOEF_RG_BUF {
	unsigned int cf_vcoef_g:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_vcoef_r:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // YUVC_VCOEF_B_BUF Register
struct YUVC_YUVC_VCOEF_B_BUF {
	unsigned int cf_vcoef_b:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // YUVC_OFFSET_RG_BUF Register
struct YUVC_YUVC_OFFSET_RG_BUF {
	unsigned int cf_goffset:9;		// [8:0]
	unsigned int reserved2:7;		// [15:9]
	unsigned int cf_roffset:9;		// [24:16]
	unsigned int reserved:7;		// [31:25]
};
 // YUVC_OFFSET_B_BUF Register
struct YUVC_YUVC_OFFSET_B_BUF {
	unsigned int cf_boffset:9;		// [8:0]
	unsigned int reserved:23;		// [31:9]
};
 // YUVC_W_ENABLE_BUF Register
struct YUVC_YUVC_W_ENABLE_BUF {
	unsigned int cf_enable_w00:1;		// [0]
	unsigned int cf_enable_w01:1;		// [1]
	unsigned int reserved:30;		// [31:2]
};
 // YUVC_W00_STADR_BUF Register
struct YUVC_YUVC_W00_STADR_BUF {
	unsigned int cf_stadr_w00:32;		// [31:0]
};
 // YUVC_W00_ENDADR_BUF Register
struct YUVC_YUVC_W00_ENDADR_BUF {
	unsigned int cf_endadr_w00:32;		// [31:0]
};
 // YUVC_W00_HEIGHT_BUF Register
struct YUVC_YUVC_W00_HEIGHT_BUF {
	unsigned int cf_height_w00:12;		// [11:0]
	unsigned int reserved:20;		// [31:12]
};
 // YUVC_W00_PITCH_BUF Register
struct YUVC_YUVC_W00_PITCH_BUF {
	unsigned int cf_pitch_w00:16;		// [15:0]
	unsigned int reserved:16;		// [31:16]
};
 // YUVC_W00_CFG0_BUF Register
struct YUVC_YUVC_W00_CFG0_BUF {
	unsigned int reserved4:8;		// [7:0]
	unsigned int cf_datawidth_w00:2;		// [9:8]
};
 // YUVC_W01_STADR_BUF Register
struct YUVC_YUVC_W01_STADR_BUF {
	unsigned int cf_stadr_w01:32;		// [31:0]
};
 // YUVC_W01_ENDADR_BUF Register
struct YUVC_YUVC_W01_ENDADR_BUF {
	unsigned int cf_endadr_w01:32;		// [31:0]
};
 // YUVC_W01_HEIGHT_BUF Register
struct YUVC_YUVC_W01_HEIGHT_BUF {
	unsigned int cf_height_w01:12;		// [11:0]
	unsigned int reserved:20;		// [31:12]
};
 // YUVC_W01_PITCH_BUF Register
struct YUVC_YUVC_W01_PITCH_BUF {
	unsigned int cf_pitch_w01:16;		// [15:0]
	unsigned int reserved:16;		// [31:16]
};
 // YUVC_W01_CFG0_BUF Register
struct YUVC_YUVC_W01_CFG0_BUF {
	unsigned int reserved4:8;		// [7:0]
	unsigned int cf_datawidth_w01:2;		// [9:8]
};
 // YUVC_STATUS Register
struct YUVC_YUVC_STATUS {
	unsigned int mb_error_region:1;		// [0]
	unsigned int mb_error_inband:1;		// [1]
	unsigned int reserved3:6;		// [7:2]
	unsigned int cmd_num:3;		// [10:8]
	unsigned int reserved2:5;		// [15:11]
	unsigned int accmd_num:4;		// [19:16]
	unsigned int reserved:12;		// [31:20]
};
 // YUVC_INT Register
struct YUVC_YUVC_INT {
	unsigned int int_g00:1;		// [0]
	unsigned int reserved2:14;		// [14:1]
	unsigned int mb_err:1;		// [15]
	unsigned int abort_g00:1;		// [16]
	unsigned int reserved:15;		// [31:17]
};
 // YUVC_W_SRAM Register
struct YUVC_YUVC_W_SRAM {
	unsigned int full_w00:1;		// [0]
	unsigned int full_w01:1;		// [1]
	unsigned int reserved:30;		// [31:2]
};
 // YUVC_W_STOP Register
struct YUVC_YUVC_W_STOP {
	unsigned int abort_w00:1;		// [0]
	unsigned int abort_w01:1;		// [1]
	unsigned int reserved:30;		// [31:2]
};
 // YUVC_W_RUN Register
struct YUVC_YUVC_W_RUN {
	unsigned int run_w00:1;		// [0]
	unsigned int run_w01:1;		// [1]
	unsigned int reserved:30;		// [31:2]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _YUVC_REG_STRUCT_L_H */
