/*
 * arch/arm/mach-tz3000/include/mach/regs/camif_reg_struct_b.h
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

#ifndef _CAMIF_REG_STRUCT_B_H
#define _CAMIF_REG_STRUCT_B_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // CAM_STADR Register
struct CAMIF_CAM_STADR {
	unsigned int cf_mb_stadr:32;		// [31:0]
};
 // CAM_ENDADR Register
struct CAMIF_CAM_ENDADR {
	unsigned int cf_mb_endadr:32;		// [31:0]
};
 // CAM_DMRADR Register
struct CAMIF_CAM_DMRADR {
	unsigned int cf_dr_adr:32;		// [31:0]
};
 // CAM_CFG Register
struct CAMIF_CAM_CFG {
	unsigned int reserved4:7;		// [31:25]
	unsigned int cf_vdmacctrl:1;		// [24]
	unsigned int reserved3:5;		// [23:19]
	unsigned int cf_accmd_queue_depth:3;		// [18:16]
	unsigned int reserved2:5;		// [15:11]
	unsigned int cf_cmd_queue_depth:3;		// [10:8]
	unsigned int reserved:4;		// [7:4]
	unsigned int cf_dr_enable_g03:1;		// [3]
	unsigned int cf_dr_enable_g02:1;		// [2]
	unsigned int cf_dr_enable_g01:1;		// [1]
	unsigned int cf_dr_enable_g00:1;		// [0]
};
 // CAM_INT_MASK Register
struct CAMIF_CAM_INT_MASK {
	unsigned int reserved2:12;		// [31:20]
	unsigned int cf_abort_mask_g03:1;		// [19]
	unsigned int cf_abort_mask_g02:1;		// [18]
	unsigned int cf_abort_mask_g01:1;		// [17]
	unsigned int cf_abort_mask_g00:1;		// [16]
	unsigned int cf_mb_err_mask:1;		// [15]
	unsigned int reserved:11;		// [14:4]
	unsigned int cf_int_mask_g03:1;		// [3]
	unsigned int cf_int_mask_g02:1;		// [2]
	unsigned int cf_int_mask_g01:1;		// [1]
	unsigned int cf_int_mask_g00:1;		// [0]
};
 // CAM_W_ENABLE Register
struct CAMIF_CAM_W_ENABLE {
	unsigned int reserved:20;		// [31:12]
	unsigned int cf_enable_w11:1;		// [11]
	unsigned int cf_enable_w10:1;		// [10]
	unsigned int cf_enable_w09:1;		// [9]
	unsigned int cf_enable_w08:1;		// [8]
	unsigned int cf_enable_w07:1;		// [7]
	unsigned int cf_enable_w06:1;		// [6]
	unsigned int cf_enable_w05:1;		// [5]
	unsigned int cf_enable_w04:1;		// [4]
	unsigned int cf_enable_w03:1;		// [3]
	unsigned int cf_enable_w02:1;		// [2]
	unsigned int cf_enable_w01:1;		// [1]
	unsigned int cf_enable_w00:1;		// [0]
};
 // CAM_CTRL Register
struct CAMIF_CAM_CTRL {
	unsigned int reserved:28;		// [31:4]
	unsigned int cf_force_abort_g03:1;		// [3]
	unsigned int cf_force_abort_g02:1;		// [2]
	unsigned int cf_force_abort_g01:1;		// [1]
	unsigned int cf_force_abort_g00:1;		// [0]
};
 // CAM_W00_STADR Register
struct CAMIF_CAM_W00_STADR {
	unsigned int cf_stadr_w00:32;		// [31:0]
};
 // CAM_W00_ENDADR Register
struct CAMIF_CAM_W00_ENDADR {
	unsigned int cf_endadr_w00:32;		// [31:0]
};
 // CAM_W00_HEIGHT Register
struct CAMIF_CAM_W00_HEIGHT {
	unsigned int reserved:18;		// [31:14]
	unsigned int cf_height_w00:14;		// [13:0]
};
 // CAM_W00_PITCH Register
struct CAMIF_CAM_W00_PITCH {
	unsigned int reserved:13;		// [31:19]
	unsigned int cf_pitch_w00:19;		// [18:0]
};
 // CAM_W00_CFG0 Register
struct CAMIF_CAM_W00_CFG0 {
	unsigned int reserved4:6;		// [31:26]
	unsigned int cf_buf_th_w00:2;		// [25:24]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_sram_th_w00:5;		// [20:16]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_datawidth_w00:2;		// [9:8]
	unsigned int reserved:8;		// [7:0]
};
 // CAM_W00_CFG1 Register
struct CAMIF_CAM_W00_CFG1 {
	unsigned int reserved2:15;		// [31:17]
	unsigned int cf_endian_w00:1;		// [16]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_maskbyte_w00:3;		// [2:0]
};
 // CAM_W00_SRAM_BASE Register
struct CAMIF_CAM_W00_SRAM_BASE {
	unsigned int reserved:21;		// [31:11]
	unsigned int cf_sram_base_w00:11;		// [10:0]
};
 // CAM_W00_SRAM_SIZE Register
struct CAMIF_CAM_W00_SRAM_SIZE {
	unsigned int reserved:21;		// [31:11]
	unsigned int cf_sram_size_w00:11;		// [10:0]
};
 // CAM_W00_INTL Register
struct CAMIF_CAM_W00_INTL {
	unsigned int reserved2:8;		// [31:24]
	unsigned int cf_init_interval_period_w00:8;		// [23:16]
	unsigned int reserved:4;		// [15:12]
	unsigned int cf_init_interval_w00:6;		// [11:6]
	unsigned int cf_interval_w00:6;		// [5:0]
};
 // CAM_W01_STADR Register
struct CAMIF_CAM_W01_STADR {
	unsigned int cf_stadr_w01:32;		// [31:0]
};
 // CAM_W01_ENDADR Register
struct CAMIF_CAM_W01_ENDADR {
	unsigned int cf_endadr_w01:32;		// [31:0]
};
 // CAM_W01_HEIGHT Register
struct CAMIF_CAM_W01_HEIGHT {
	unsigned int reserved:18;		// [31:14]
	unsigned int cf_height_w01:14;		// [13:0]
};
 // CAM_W01_PITCH Register
struct CAMIF_CAM_W01_PITCH {
	unsigned int reserved:13;		// [31:19]
	unsigned int cf_pitch_w01:19;		// [18:0]
};
 // CAM_W01_CFG0 Register
struct CAMIF_CAM_W01_CFG0 {
	unsigned int reserved4:6;		// [31:26]
	unsigned int cf_buf_th_w01:2;		// [25:24]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_sram_th_w01:5;		// [20:16]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_datawidth_w01:2;		// [9:8]
	unsigned int reserved:8;		// [7:0]
};
 // CAM_W01_CFG1 Register
struct CAMIF_CAM_W01_CFG1 {
	unsigned int reserved2:15;		// [31:17]
	unsigned int cf_endian_w01:1;		// [16]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_maskbyte_w01:3;		// [2:0]
};
 // CAM_W01_SRAM_BASE Register
struct CAMIF_CAM_W01_SRAM_BASE {
	unsigned int reserved:21;		// [31:11]
	unsigned int cf_sram_base_w01:11;		// [10:0]
};
 // CAM_W01_SRAM_SIZE Register
struct CAMIF_CAM_W01_SRAM_SIZE {
	unsigned int reserved:21;		// [31:11]
	unsigned int cf_sram_size_w01:11;		// [10:0]
};
 // CAM_W01_INTL Register
struct CAMIF_CAM_W01_INTL {
	unsigned int reserved2:8;		// [31:24]
	unsigned int cf_init_interval_period_w01:8;		// [23:16]
	unsigned int reserved:4;		// [15:12]
	unsigned int cf_init_interval_w01:6;		// [11:6]
	unsigned int cf_interval_w01:6;		// [5:0]
};
 // CAM_W02_STADR Register
struct CAMIF_CAM_W02_STADR {
	unsigned int cf_stadr_w02:32;		// [31:0]
};
 // CAM_W02_ENDADR Register
struct CAMIF_CAM_W02_ENDADR {
	unsigned int cf_endadr_w02:32;		// [31:0]
};
 // CAM_W02_HEIGHT Register
struct CAMIF_CAM_W02_HEIGHT {
	unsigned int reserved:18;		// [31:14]
	unsigned int cf_height_w02:14;		// [13:0]
};
 // CAM_W02_PITCH Register
struct CAMIF_CAM_W02_PITCH {
	unsigned int reserved:13;		// [31:19]
	unsigned int cf_pitch_w02:19;		// [18:0]
};
 // CAM_W02_CFG0 Register
struct CAMIF_CAM_W02_CFG0 {
	unsigned int reserved4:6;		// [31:26]
	unsigned int cf_buf_th_w02:2;		// [25:24]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_sram_th_w02:5;		// [20:16]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_datawidth_w02:2;		// [9:8]
	unsigned int reserved:8;		// [7:0]
};
 // CAM_W02_CFG1 Register
struct CAMIF_CAM_W02_CFG1 {
	unsigned int reserved2:15;		// [31:17]
	unsigned int cf_endian_w02:1;		// [16]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_maskbyte_w02:3;		// [2:0]
};
 // CAM_W02_SRAM_BASE Register
struct CAMIF_CAM_W02_SRAM_BASE {
	unsigned int reserved:21;		// [31:11]
	unsigned int cf_sram_base_w02:11;		// [10:0]
};
 // CAM_W02_SRAM_SIZE Register
struct CAMIF_CAM_W02_SRAM_SIZE {
	unsigned int reserved:21;		// [31:11]
	unsigned int cf_sram_size_w02:11;		// [10:0]
};
 // CAM_W02_INTL Register
struct CAMIF_CAM_W02_INTL {
	unsigned int reserved2:8;		// [31:24]
	unsigned int cf_init_interval_period_w02:8;		// [23:16]
	unsigned int reserved:4;		// [15:12]
	unsigned int cf_init_interval_w02:6;		// [11:6]
	unsigned int cf_interval_w02:6;		// [5:0]
};
 // CAM_W03_STADR Register
struct CAMIF_CAM_W03_STADR {
	unsigned int cf_stadr_w03:32;		// [31:0]
};
 // CAM_W03_ENDADR Register
struct CAMIF_CAM_W03_ENDADR {
	unsigned int cf_endadr_w03:32;		// [31:0]
};
 // CAM_W03_HEIGHT Register
struct CAMIF_CAM_W03_HEIGHT {
	unsigned int reserved:18;		// [31:14]
	unsigned int cf_height_w03:14;		// [13:0]
};
 // CAM_W03_PITCH Register
struct CAMIF_CAM_W03_PITCH {
	unsigned int reserved:13;		// [31:19]
	unsigned int cf_pitch_w03:19;		// [18:0]
};
 // CAM_W03_CFG0 Register
struct CAMIF_CAM_W03_CFG0 {
	unsigned int reserved4:6;		// [31:26]
	unsigned int cf_buf_th_w03:2;		// [25:24]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_sram_th_w03:5;		// [20:16]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_datawidth_w03:2;		// [9:8]
	unsigned int reserved:8;		// [7:0]
};
 // CAM_W03_CFG1 Register
struct CAMIF_CAM_W03_CFG1 {
	unsigned int reserved2:15;		// [31:17]
	unsigned int cf_endian_w03:1;		// [16]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_maskbyte_w03:3;		// [2:0]
};
 // CAM_W03_SRAM_BASE Register
struct CAMIF_CAM_W03_SRAM_BASE {
	unsigned int reserved:21;		// [31:11]
	unsigned int cf_sram_base_w03:11;		// [10:0]
};
 // CAM_W03_SRAM_SIZE Register
struct CAMIF_CAM_W03_SRAM_SIZE {
	unsigned int reserved:21;		// [31:11]
	unsigned int cf_sram_size_w03:11;		// [10:0]
};
 // CAM_W03_INTL Register
struct CAMIF_CAM_W03_INTL {
	unsigned int reserved2:8;		// [31:24]
	unsigned int cf_init_interval_period_w03:8;		// [23:16]
	unsigned int reserved:4;		// [15:12]
	unsigned int cf_init_interval_w03:6;		// [11:6]
	unsigned int cf_interval_w03:6;		// [5:0]
};
 // CAM_W04_STADR Register
struct CAMIF_CAM_W04_STADR {
	unsigned int cf_stadr_w04:32;		// [31:0]
};
 // CAM_W04_ENDADR Register
struct CAMIF_CAM_W04_ENDADR {
	unsigned int cf_endadr_w04:32;		// [31:0]
};
 // CAM_W04_HEIGHT Register
struct CAMIF_CAM_W04_HEIGHT {
	unsigned int reserved:18;		// [31:14]
	unsigned int cf_height_w04:14;		// [13:0]
};
 // CAM_W04_PITCH Register
struct CAMIF_CAM_W04_PITCH {
	unsigned int reserved:13;		// [31:19]
	unsigned int cf_pitch_w04:19;		// [18:0]
};
 // CAM_W04_CFG0 Register
struct CAMIF_CAM_W04_CFG0 {
	unsigned int reserved4:6;		// [31:26]
	unsigned int cf_buf_th_w04:2;		// [25:24]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_sram_th_w04:5;		// [20:16]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_datawidth_w04:2;		// [9:8]
	unsigned int reserved:8;		// [7:0]
};
 // CAM_W04_CFG1 Register
struct CAMIF_CAM_W04_CFG1 {
	unsigned int reserved2:15;		// [31:17]
	unsigned int cf_endian_w04:1;		// [16]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_maskbyte_w04:3;		// [2:0]
};
 // CAM_W04_SRAM_BASE Register
struct CAMIF_CAM_W04_SRAM_BASE {
	unsigned int reserved:21;		// [31:11]
	unsigned int cf_sram_base_w04:11;		// [10:0]
};
 // CAM_W04_SRAM_SIZE Register
struct CAMIF_CAM_W04_SRAM_SIZE {
	unsigned int reserved:21;		// [31:11]
	unsigned int cf_sram_size_w04:11;		// [10:0]
};
 // CAM_W04_INTL Register
struct CAMIF_CAM_W04_INTL {
	unsigned int reserved2:8;		// [31:24]
	unsigned int cf_init_interval_period_w04:8;		// [23:16]
	unsigned int reserved:4;		// [15:12]
	unsigned int cf_init_interval_w04:6;		// [11:6]
	unsigned int cf_interval_w04:6;		// [5:0]
};
 // CAM_W05_STADR Register
struct CAMIF_CAM_W05_STADR {
	unsigned int cf_stadr_w05:32;		// [31:0]
};
 // CAM_W05_ENDADR Register
struct CAMIF_CAM_W05_ENDADR {
	unsigned int cf_endadr_w05:32;		// [31:0]
};
 // CAM_W05_HEIGHT Register
struct CAMIF_CAM_W05_HEIGHT {
	unsigned int reserved:18;		// [31:14]
	unsigned int cf_height_w05:14;		// [13:0]
};
 // CAM_W05_PITCH Register
struct CAMIF_CAM_W05_PITCH {
	unsigned int reserved:13;		// [31:19]
	unsigned int cf_pitch_w05:19;		// [18:0]
};
 // CAM_W05_CFG0 Register
struct CAMIF_CAM_W05_CFG0 {
	unsigned int reserved4:6;		// [31:26]
	unsigned int cf_buf_th_w05:2;		// [25:24]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_sram_th_w05:5;		// [20:16]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_datawidth_w05:2;		// [9:8]
	unsigned int reserved:8;		// [7:0]
};
 // CAM_W05_CFG1 Register
struct CAMIF_CAM_W05_CFG1 {
	unsigned int reserved2:15;		// [31:17]
	unsigned int cf_endian_w05:1;		// [16]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_maskbyte_w05:3;		// [2:0]
};
 // CAM_W05_SRAM_BASE Register
struct CAMIF_CAM_W05_SRAM_BASE {
	unsigned int reserved:21;		// [31:11]
	unsigned int cf_sram_base_w05:11;		// [10:0]
};
 // CAM_W05_SRAM_SIZE Register
struct CAMIF_CAM_W05_SRAM_SIZE {
	unsigned int reserved:21;		// [31:11]
	unsigned int cf_sram_size_w05:11;		// [10:0]
};
 // CAM_W05_INTL Register
struct CAMIF_CAM_W05_INTL {
	unsigned int reserved2:8;		// [31:24]
	unsigned int cf_init_interval_period_w05:8;		// [23:16]
	unsigned int reserved:4;		// [15:12]
	unsigned int cf_init_interval_w05:6;		// [11:6]
	unsigned int cf_interval_w05:6;		// [5:0]
};
 // CAM_W06_STADR Register
struct CAMIF_CAM_W06_STADR {
	unsigned int cf_stadr_w06:32;		// [31:0]
};
 // CAM_W06_ENDADR Register
struct CAMIF_CAM_W06_ENDADR {
	unsigned int cf_endadr_w06:32;		// [31:0]
};
 // CAM_W06_HEIGHT Register
struct CAMIF_CAM_W06_HEIGHT {
	unsigned int reserved:18;		// [31:14]
	unsigned int cf_height_w06:14;		// [13:0]
};
 // CAM_W06_PITCH Register
struct CAMIF_CAM_W06_PITCH {
	unsigned int reserved:13;		// [31:19]
	unsigned int cf_pitch_w06:19;		// [18:0]
};
 // CAM_W06_CFG0 Register
struct CAMIF_CAM_W06_CFG0 {
	unsigned int reserved4:6;		// [31:26]
	unsigned int cf_buf_th_w06:2;		// [25:24]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_sram_th_w06:5;		// [20:16]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_datawidth_w06:2;		// [9:8]
	unsigned int reserved:8;		// [7:0]
};
 // CAM_W06_CFG1 Register
struct CAMIF_CAM_W06_CFG1 {
	unsigned int reserved2:15;		// [31:17]
	unsigned int cf_endian_w06:1;		// [16]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_maskbyte_w06:3;		// [2:0]
};
 // CAM_W06_SRAM_BASE Register
struct CAMIF_CAM_W06_SRAM_BASE {
	unsigned int reserved:21;		// [31:11]
	unsigned int cf_sram_base_w06:11;		// [10:0]
};
 // CAM_W06_SRAM_SIZE Register
struct CAMIF_CAM_W06_SRAM_SIZE {
	unsigned int reserved:21;		// [31:11]
	unsigned int cf_sram_size_w06:11;		// [10:0]
};
 // CAM_W06_INTL Register
struct CAMIF_CAM_W06_INTL {
	unsigned int reserved2:8;		// [31:24]
	unsigned int cf_init_interval_period_w06:8;		// [23:16]
	unsigned int reserved:4;		// [15:12]
	unsigned int cf_init_interval_w06:6;		// [11:6]
	unsigned int cf_interval_w06:6;		// [5:0]
};
 // CAM_W07_STADR Register
struct CAMIF_CAM_W07_STADR {
	unsigned int cf_stadr_w07:32;		// [31:0]
};
 // CAM_W07_ENDADR Register
struct CAMIF_CAM_W07_ENDADR {
	unsigned int cf_endadr_w07:32;		// [31:0]
};
 // CAM_W07_HEIGHT Register
struct CAMIF_CAM_W07_HEIGHT {
	unsigned int reserved:18;		// [31:14]
	unsigned int cf_height_w07:14;		// [13:0]
};
 // CAM_W07_PITCH Register
struct CAMIF_CAM_W07_PITCH {
	unsigned int reserved:13;		// [31:19]
	unsigned int cf_pitch_w07:19;		// [18:0]
};
 // CAM_W07_CFG0 Register
struct CAMIF_CAM_W07_CFG0 {
	unsigned int reserved4:6;		// [31:26]
	unsigned int cf_buf_th_w07:2;		// [25:24]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_sram_th_w07:5;		// [20:16]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_datawidth_w07:2;		// [9:8]
	unsigned int reserved:8;		// [7:0]
};
 // CAM_W07_CFG1 Register
struct CAMIF_CAM_W07_CFG1 {
	unsigned int reserved2:15;		// [31:17]
	unsigned int cf_endian_w07:1;		// [16]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_maskbyte_w07:3;		// [2:0]
};
 // CAM_W07_SRAM_BASE Register
struct CAMIF_CAM_W07_SRAM_BASE {
	unsigned int reserved:21;		// [31:11]
	unsigned int cf_sram_base_w07:11;		// [10:0]
};
 // CAM_W07_SRAM_SIZE Register
struct CAMIF_CAM_W07_SRAM_SIZE {
	unsigned int reserved:21;		// [31:11]
	unsigned int cf_sram_size_w07:11;		// [10:0]
};
 // CAM_W07_INTL Register
struct CAMIF_CAM_W07_INTL {
	unsigned int reserved2:8;		// [31:24]
	unsigned int cf_init_interval_period_w07:8;		// [23:16]
	unsigned int reserved:4;		// [15:12]
	unsigned int cf_init_interval_w07:6;		// [11:6]
	unsigned int cf_interval_w07:6;		// [5:0]
};
 // CAM_W08_STADR Register
struct CAMIF_CAM_W08_STADR {
	unsigned int cf_stadr_w08:32;		// [31:0]
};
 // CAM_W08_ENDADR Register
struct CAMIF_CAM_W08_ENDADR {
	unsigned int cf_endadr_w08:32;		// [31:0]
};
 // CAM_W08_HEIGHT Register
struct CAMIF_CAM_W08_HEIGHT {
	unsigned int reserved:18;		// [31:14]
	unsigned int cf_height_w08:14;		// [13:0]
};
 // CAM_W08_PITCH Register
struct CAMIF_CAM_W08_PITCH {
	unsigned int reserved:13;		// [31:19]
	unsigned int cf_pitch_w08:19;		// [18:0]
};
 // CAM_W08_CFG0 Register
struct CAMIF_CAM_W08_CFG0 {
	unsigned int reserved4:6;		// [31:26]
	unsigned int cf_buf_th_w08:2;		// [25:24]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_sram_th_w08:5;		// [20:16]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_datawidth_w08:2;		// [9:8]
	unsigned int reserved:8;		// [7:0]
};
 // CAM_W08_CFG1 Register
struct CAMIF_CAM_W08_CFG1 {
	unsigned int reserved2:15;		// [31:17]
	unsigned int cf_endian_w08:1;		// [16]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_maskbyte_w08:3;		// [2:0]
};
 // CAM_W08_SRAM_BASE Register
struct CAMIF_CAM_W08_SRAM_BASE {
	unsigned int reserved:21;		// [31:11]
	unsigned int cf_sram_base_w08:11;		// [10:0]
};
 // CAM_W08_SRAM_SIZE Register
struct CAMIF_CAM_W08_SRAM_SIZE {
	unsigned int reserved:21;		// [31:11]
	unsigned int cf_sram_size_w08:11;		// [10:0]
};
 // CAM_W08_INTL Register
struct CAMIF_CAM_W08_INTL {
	unsigned int reserved2:8;		// [31:24]
	unsigned int cf_init_interval_period_w08:8;		// [23:16]
	unsigned int reserved:4;		// [15:12]
	unsigned int cf_init_interval_w08:6;		// [11:6]
	unsigned int cf_interval_w08:6;		// [5:0]
};
 // CAM_W09_STADR Register
struct CAMIF_CAM_W09_STADR {
	unsigned int cf_stadr_w09:32;		// [31:0]
};
 // CAM_W09_ENDADR Register
struct CAMIF_CAM_W09_ENDADR {
	unsigned int cf_endadr_w09:32;		// [31:0]
};
 // CAM_W09_HEIGHT Register
struct CAMIF_CAM_W09_HEIGHT {
	unsigned int reserved:18;		// [31:14]
	unsigned int cf_height_w09:14;		// [13:0]
};
 // CAM_W09_PITCH Register
struct CAMIF_CAM_W09_PITCH {
	unsigned int reserved:13;		// [31:19]
	unsigned int cf_pitch_w09:19;		// [18:0]
};
 // CAM_W09_CFG0 Register
struct CAMIF_CAM_W09_CFG0 {
	unsigned int reserved4:6;		// [31:26]
	unsigned int cf_buf_th_w09:2;		// [25:24]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_sram_th_w09:5;		// [20:16]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_datawidth_w09:2;		// [9:8]
	unsigned int reserved:8;		// [7:0]
};
 // CAM_W09_CFG1 Register
struct CAMIF_CAM_W09_CFG1 {
	unsigned int reserved2:15;		// [31:17]
	unsigned int cf_endian_w09:1;		// [16]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_maskbyte_w09:3;		// [2:0]
};
 // CAM_W09_SRAM_BASE Register
struct CAMIF_CAM_W09_SRAM_BASE {
	unsigned int reserved:21;		// [31:11]
	unsigned int cf_sram_base_w09:11;		// [10:0]
};
 // CAM_W09_SRAM_SIZE Register
struct CAMIF_CAM_W09_SRAM_SIZE {
	unsigned int reserved:21;		// [31:11]
	unsigned int cf_sram_size_w09:11;		// [10:0]
};
 // CAM_W09_INTL Register
struct CAMIF_CAM_W09_INTL {
	unsigned int reserved2:8;		// [31:24]
	unsigned int cf_init_interval_period_w09:8;		// [23:16]
	unsigned int reserved:4;		// [15:12]
	unsigned int cf_init_interval_w09:6;		// [11:6]
	unsigned int cf_interval_w09:6;		// [5:0]
};
 // CAM_W10_STADR Register
struct CAMIF_CAM_W10_STADR {
	unsigned int cf_stadr_w10:32;		// [31:0]
};
 // CAM_W10_ENDADR Register
struct CAMIF_CAM_W10_ENDADR {
	unsigned int cf_endadr_w10:32;		// [31:0]
};
 // CAM_W10_HEIGHT Register
struct CAMIF_CAM_W10_HEIGHT {
	unsigned int reserved:18;		// [31:14]
	unsigned int cf_height_w10:14;		// [13:0]
};
 // CAM_W10_PITCH Register
struct CAMIF_CAM_W10_PITCH {
	unsigned int reserved:13;		// [31:19]
	unsigned int cf_pitch_w10:19;		// [18:0]
};
 // CAM_W10_CFG0 Register
struct CAMIF_CAM_W10_CFG0 {
	unsigned int reserved4:6;		// [31:26]
	unsigned int cf_buf_th_w10:2;		// [25:24]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_sram_th_w10:5;		// [20:16]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_datawidth_w10:2;		// [9:8]
	unsigned int reserved:8;		// [7:0]
};
 // CAM_W10_CFG1 Register
struct CAMIF_CAM_W10_CFG1 {
	unsigned int reserved2:15;		// [31:17]
	unsigned int cf_endian_w10:1;		// [16]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_maskbyte_w10:3;		// [2:0]
};
 // CAM_W10_SRAM_BASE Register
struct CAMIF_CAM_W10_SRAM_BASE {
	unsigned int reserved:21;		// [31:11]
	unsigned int cf_sram_base_w10:11;		// [10:0]
};
 // CAM_W10_SRAM_SIZE Register
struct CAMIF_CAM_W10_SRAM_SIZE {
	unsigned int reserved:21;		// [31:11]
	unsigned int cf_sram_size_w10:11;		// [10:0]
};
 // CAM_W10_INTL Register
struct CAMIF_CAM_W10_INTL {
	unsigned int reserved2:8;		// [31:24]
	unsigned int cf_init_interval_period_w10:8;		// [23:16]
	unsigned int reserved:4;		// [15:12]
	unsigned int cf_init_interval_w10:6;		// [11:6]
	unsigned int cf_interval_w10:6;		// [5:0]
};
 // CAM_W11_STADR Register
struct CAMIF_CAM_W11_STADR {
	unsigned int cf_stadr_w11:32;		// [31:0]
};
 // CAM_W11_ENDADR Register
struct CAMIF_CAM_W11_ENDADR {
	unsigned int cf_endadr_w11:32;		// [31:0]
};
 // CAM_W11_HEIGHT Register
struct CAMIF_CAM_W11_HEIGHT {
	unsigned int reserved:18;		// [31:14]
	unsigned int cf_height_w11:14;		// [13:0]
};
 // CAM_W11_PITCH Register
struct CAMIF_CAM_W11_PITCH {
	unsigned int reserved:13;		// [31:19]
	unsigned int cf_pitch_w11:19;		// [18:0]
};
 // CAM_W11_CFG0 Register
struct CAMIF_CAM_W11_CFG0 {
	unsigned int reserved4:6;		// [31:26]
	unsigned int cf_buf_th_w11:2;		// [25:24]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_sram_th_w11:5;		// [20:16]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_datawidth_w11:2;		// [9:8]
	unsigned int reserved:8;		// [7:0]
};
 // CAM_W11_CFG1 Register
struct CAMIF_CAM_W11_CFG1 {
	unsigned int reserved2:15;		// [31:17]
	unsigned int cf_endian_w11:1;		// [16]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_maskbyte_w11:3;		// [2:0]
};
 // CAM_W11_SRAM_BASE Register
struct CAMIF_CAM_W11_SRAM_BASE {
	unsigned int reserved:21;		// [31:11]
	unsigned int cf_sram_base_w11:11;		// [10:0]
};
 // CAM_W11_SRAM_SIZE Register
struct CAMIF_CAM_W11_SRAM_SIZE {
	unsigned int reserved:21;		// [31:11]
	unsigned int cf_sram_size_w11:11;		// [10:0]
};
 // CAM_W11_INTL Register
struct CAMIF_CAM_W11_INTL {
	unsigned int reserved2:8;		// [31:24]
	unsigned int cf_init_interval_period_w11:8;		// [23:16]
	unsigned int reserved:4;		// [15:12]
	unsigned int cf_init_interval_w11:6;		// [11:6]
	unsigned int cf_interval_w11:6;		// [5:0]
};
 // CAM_W_ENABLE_BUF Register
struct CAMIF_CAM_W_ENABLE_BUF {
	unsigned int reserved:20;		// [31:12]
	unsigned int cf_enable_w11:1;		// [11]
	unsigned int cf_enable_w10:1;		// [10]
	unsigned int cf_enable_w09:1;		// [9]
	unsigned int cf_enable_w08:1;		// [8]
	unsigned int cf_enable_w07:1;		// [7]
	unsigned int cf_enable_w06:1;		// [6]
	unsigned int cf_enable_w05:1;		// [5]
	unsigned int cf_enable_w04:1;		// [4]
	unsigned int cf_enable_w03:1;		// [3]
	unsigned int cf_enable_w02:1;		// [2]
	unsigned int cf_enable_w01:1;		// [1]
	unsigned int cf_enable_w00:1;		// [0]
};
 // CAM_W00_STADR_BUF Register
struct CAMIF_CAM_W00_STADR_BUF {
	unsigned int cf_stadr_w00:32;		// [31:0]
};
 // CAM_W00_ENDADR_BUF Register
struct CAMIF_CAM_W00_ENDADR_BUF {
	unsigned int cf_endadr_w00:32;		// [31:0]
};
 // CAM_W00_HEIGHT_BUF Register
struct CAMIF_CAM_W00_HEIGHT_BUF {
	unsigned int reserved:18;		// [31:14]
	unsigned int cf_height_w00:14;		// [13:0]
};
 // CAM_W00_PITCH_BUF Register
struct CAMIF_CAM_W00_PITCH_BUF {
	unsigned int reserved:13;		// [31:19]
	unsigned int cf_pitch_w00:19;		// [18:0]
};
 // CAM_W00_CFG0_BUF Register
struct CAMIF_CAM_W00_CFG0_BUF {
	unsigned int reserved4:6;		// [31:26]
	unsigned int cf_buf_th_w00:2;		// [25:24]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_sram_th_w00:5;		// [20:16]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_datawidth_w00:2;		// [9:8]
	unsigned int reserved:8;		// [7:0]
};
 // CAM_W00_CFG1_BUF Register
struct CAMIF_CAM_W00_CFG1_BUF {
	unsigned int reserved2:15;		// [31:17]
	unsigned int cf_endian_w00:1;		// [16]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_maskbyte_w00:3;		// [2:0]
};
 // CAM_W01_STADR_BUF Register
struct CAMIF_CAM_W01_STADR_BUF {
	unsigned int cf_stadr_w01:32;		// [31:0]
};
 // CAM_W01_ENDADR_BUF Register
struct CAMIF_CAM_W01_ENDADR_BUF {
	unsigned int cf_endadr_w01:32;		// [31:0]
};
 // CAM_W01_HEIGHT_BUF Register
struct CAMIF_CAM_W01_HEIGHT_BUF {
	unsigned int reserved:18;		// [31:14]
	unsigned int cf_height_w01:14;		// [13:0]
};
 // CAM_W01_PITCH_BUF Register
struct CAMIF_CAM_W01_PITCH_BUF {
	unsigned int reserved:13;		// [31:19]
	unsigned int cf_pitch_w01:19;		// [18:0]
};
 // CAM_W01_CFG0_BUF Register
struct CAMIF_CAM_W01_CFG0_BUF {
	unsigned int reserved4:6;		// [31:26]
	unsigned int cf_buf_th_w01:2;		// [25:24]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_sram_th_w01:5;		// [20:16]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_datawidth_w01:2;		// [9:8]
	unsigned int reserved:8;		// [7:0]
};
 // CAM_W01_CFG1_BUF Register
struct CAMIF_CAM_W01_CFG1_BUF {
	unsigned int reserved2:15;		// [31:17]
	unsigned int cf_endian_w01:1;		// [16]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_maskbyte_w01:3;		// [2:0]
};
 // CAM_W02_STADR_BUF Register
struct CAMIF_CAM_W02_STADR_BUF {
	unsigned int cf_stadr_w02:32;		// [31:0]
};
 // CAM_W02_ENDADR_BUF Register
struct CAMIF_CAM_W02_ENDADR_BUF {
	unsigned int cf_endadr_w02:32;		// [31:0]
};
 // CAM_W02_HEIGHT_BUF Register
struct CAMIF_CAM_W02_HEIGHT_BUF {
	unsigned int reserved:18;		// [31:14]
	unsigned int cf_height_w02:14;		// [13:0]
};
 // CAM_W02_PITCH_BUF Register
struct CAMIF_CAM_W02_PITCH_BUF {
	unsigned int reserved:13;		// [31:19]
	unsigned int cf_pitch_w02:19;		// [18:0]
};
 // CAM_W02_CFG0_BUF Register
struct CAMIF_CAM_W02_CFG0_BUF {
	unsigned int reserved4:6;		// [31:26]
	unsigned int cf_buf_th_w02:2;		// [25:24]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_sram_th_w02:5;		// [20:16]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_datawidth_w02:2;		// [9:8]
	unsigned int reserved:8;		// [7:0]
};
 // CAM_W02_CFG1_BUF Register
struct CAMIF_CAM_W02_CFG1_BUF {
	unsigned int reserved2:15;		// [31:17]
	unsigned int cf_endian_w02:1;		// [16]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_maskbyte_w02:3;		// [2:0]
};
 // CAM_W03_STADR_BUF Register
struct CAMIF_CAM_W03_STADR_BUF {
	unsigned int cf_stadr_w03:32;		// [31:0]
};
 // CAM_W03_ENDADR_BUF Register
struct CAMIF_CAM_W03_ENDADR_BUF {
	unsigned int cf_endadr_w03:32;		// [31:0]
};
 // CAM_W03_HEIGHT_BUF Register
struct CAMIF_CAM_W03_HEIGHT_BUF {
	unsigned int reserved:18;		// [31:14]
	unsigned int cf_height_w03:14;		// [13:0]
};
 // CAM_W03_PITCH_BUF Register
struct CAMIF_CAM_W03_PITCH_BUF {
	unsigned int reserved:13;		// [31:19]
	unsigned int cf_pitch_w03:19;		// [18:0]
};
 // CAM_W03_CFG0_BUF Register
struct CAMIF_CAM_W03_CFG0_BUF {
	unsigned int reserved4:6;		// [31:26]
	unsigned int cf_buf_th_w03:2;		// [25:24]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_sram_th_w03:5;		// [20:16]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_datawidth_w03:2;		// [9:8]
	unsigned int reserved:8;		// [7:0]
};
 // CAM_W03_CFG1_BUF Register
struct CAMIF_CAM_W03_CFG1_BUF {
	unsigned int reserved2:15;		// [31:17]
	unsigned int cf_endian_w03:1;		// [16]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_maskbyte_w03:3;		// [2:0]
};
 // CAM_W04_STADR_BUF Register
struct CAMIF_CAM_W04_STADR_BUF {
	unsigned int cf_stadr_w04:32;		// [31:0]
};
 // CAM_W04_ENDADR_BUF Register
struct CAMIF_CAM_W04_ENDADR_BUF {
	unsigned int cf_endadr_w04:32;		// [31:0]
};
 // CAM_W04_HEIGHT_BUF Register
struct CAMIF_CAM_W04_HEIGHT_BUF {
	unsigned int reserved:18;		// [31:14]
	unsigned int cf_height_w04:14;		// [13:0]
};
 // CAM_W04_PITCH_BUF Register
struct CAMIF_CAM_W04_PITCH_BUF {
	unsigned int reserved:13;		// [31:19]
	unsigned int cf_pitch_w04:19;		// [18:0]
};
 // CAM_W04_CFG0_BUF Register
struct CAMIF_CAM_W04_CFG0_BUF {
	unsigned int reserved4:6;		// [31:26]
	unsigned int cf_buf_th_w04:2;		// [25:24]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_sram_th_w04:5;		// [20:16]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_datawidth_w04:2;		// [9:8]
	unsigned int reserved:8;		// [7:0]
};
 // CAM_W04_CFG1_BUF Register
struct CAMIF_CAM_W04_CFG1_BUF {
	unsigned int reserved2:15;		// [31:17]
	unsigned int cf_endian_w04:1;		// [16]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_maskbyte_w04:3;		// [2:0]
};
 // CAM_W05_STADR_BUF Register
struct CAMIF_CAM_W05_STADR_BUF {
	unsigned int cf_stadr_w05:32;		// [31:0]
};
 // CAM_W05_ENDADR_BUF Register
struct CAMIF_CAM_W05_ENDADR_BUF {
	unsigned int cf_endadr_w05:32;		// [31:0]
};
 // CAM_W05_HEIGHT_BUF Register
struct CAMIF_CAM_W05_HEIGHT_BUF {
	unsigned int reserved:18;		// [31:14]
	unsigned int cf_height_w05:14;		// [13:0]
};
 // CAM_W05_PITCH_BUF Register
struct CAMIF_CAM_W05_PITCH_BUF {
	unsigned int reserved:13;		// [31:19]
	unsigned int cf_pitch_w05:19;		// [18:0]
};
 // CAM_W05_CFG0_BUF Register
struct CAMIF_CAM_W05_CFG0_BUF {
	unsigned int reserved4:6;		// [31:26]
	unsigned int cf_buf_th_w05:2;		// [25:24]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_sram_th_w05:5;		// [20:16]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_datawidth_w05:2;		// [9:8]
	unsigned int reserved:8;		// [7:0]
};
 // CAM_W05_CFG1_BUF Register
struct CAMIF_CAM_W05_CFG1_BUF {
	unsigned int reserved2:15;		// [31:17]
	unsigned int cf_endian_w05:1;		// [16]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_maskbyte_w05:3;		// [2:0]
};
 // CAM_W06_STADR_BUF Register
struct CAMIF_CAM_W06_STADR_BUF {
	unsigned int cf_stadr_w06:32;		// [31:0]
};
 // CAM_W06_ENDADR_BUF Register
struct CAMIF_CAM_W06_ENDADR_BUF {
	unsigned int cf_endadr_w06:32;		// [31:0]
};
 // CAM_W06_HEIGHT_BUF Register
struct CAMIF_CAM_W06_HEIGHT_BUF {
	unsigned int reserved:18;		// [31:14]
	unsigned int cf_height_w06:14;		// [13:0]
};
 // CAM_W06_PITCH_BUF Register
struct CAMIF_CAM_W06_PITCH_BUF {
	unsigned int reserved:13;		// [31:19]
	unsigned int cf_pitch_w06:19;		// [18:0]
};
 // CAM_W06_CFG0_BUF Register
struct CAMIF_CAM_W06_CFG0_BUF {
	unsigned int reserved4:6;		// [31:26]
	unsigned int cf_buf_th_w06:2;		// [25:24]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_sram_th_w06:5;		// [20:16]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_datawidth_w06:2;		// [9:8]
	unsigned int reserved:8;		// [7:0]
};
 // CAM_W06_CFG1_BUF Register
struct CAMIF_CAM_W06_CFG1_BUF {
	unsigned int reserved2:15;		// [31:17]
	unsigned int cf_endian_w06:1;		// [16]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_maskbyte_w06:3;		// [2:0]
};
 // CAM_W07_STADR_BUF Register
struct CAMIF_CAM_W07_STADR_BUF {
	unsigned int cf_stadr_w07:32;		// [31:0]
};
 // CAM_W07_ENDADR_BUF Register
struct CAMIF_CAM_W07_ENDADR_BUF {
	unsigned int cf_endadr_w07:32;		// [31:0]
};
 // CAM_W07_HEIGHT_BUF Register
struct CAMIF_CAM_W07_HEIGHT_BUF {
	unsigned int reserved:18;		// [31:14]
	unsigned int cf_height_w07:14;		// [13:0]
};
 // CAM_W07_PITCH_BUF Register
struct CAMIF_CAM_W07_PITCH_BUF {
	unsigned int reserved:13;		// [31:19]
	unsigned int cf_pitch_w07:19;		// [18:0]
};
 // CAM_W07_CFG0_BUF Register
struct CAMIF_CAM_W07_CFG0_BUF {
	unsigned int reserved4:6;		// [31:26]
	unsigned int cf_buf_th_w07:2;		// [25:24]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_sram_th_w07:5;		// [20:16]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_datawidth_w07:2;		// [9:8]
	unsigned int reserved:8;		// [7:0]
};
 // CAM_W07_CFG1_BUF Register
struct CAMIF_CAM_W07_CFG1_BUF {
	unsigned int reserved2:15;		// [31:17]
	unsigned int cf_endian_w07:1;		// [16]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_maskbyte_w07:3;		// [2:0]
};
 // CAM_W08_STADR_BUF Register
struct CAMIF_CAM_W08_STADR_BUF {
	unsigned int cf_stadr_w08:32;		// [31:0]
};
 // CAM_W08_ENDADR_BUF Register
struct CAMIF_CAM_W08_ENDADR_BUF {
	unsigned int cf_endadr_w08:32;		// [31:0]
};
 // CAM_W08_HEIGHT_BUF Register
struct CAMIF_CAM_W08_HEIGHT_BUF {
	unsigned int reserved:18;		// [31:14]
	unsigned int cf_height_w08:14;		// [13:0]
};
 // CAM_W08_PITCH_BUF Register
struct CAMIF_CAM_W08_PITCH_BUF {
	unsigned int reserved:13;		// [31:19]
	unsigned int cf_pitch_w08:19;		// [18:0]
};
 // CAM_W08_CFG0_BUF Register
struct CAMIF_CAM_W08_CFG0_BUF {
	unsigned int reserved4:6;		// [31:26]
	unsigned int cf_buf_th_w08:2;		// [25:24]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_sram_th_w08:5;		// [20:16]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_datawidth_w08:2;		// [9:8]
	unsigned int reserved:8;		// [7:0]
};
 // CAM_W08_CFG1_BUF Register
struct CAMIF_CAM_W08_CFG1_BUF {
	unsigned int reserved2:15;		// [31:17]
	unsigned int cf_endian_w08:1;		// [16]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_maskbyte_w08:3;		// [2:0]
};
 // CAM_W09_STADR_BUF Register
struct CAMIF_CAM_W09_STADR_BUF {
	unsigned int cf_stadr_w09:32;		// [31:0]
};
 // CAM_W09_ENDADR_BUF Register
struct CAMIF_CAM_W09_ENDADR_BUF {
	unsigned int cf_endadr_w09:32;		// [31:0]
};
 // CAM_W09_HEIGHT_BUF Register
struct CAMIF_CAM_W09_HEIGHT_BUF {
	unsigned int reserved:18;		// [31:14]
	unsigned int cf_height_w09:14;		// [13:0]
};
 // CAM_W09_PITCH_BUF Register
struct CAMIF_CAM_W09_PITCH_BUF {
	unsigned int reserved:13;		// [31:19]
	unsigned int cf_pitch_w09:19;		// [18:0]
};
 // CAM_W09_CFG0_BUF Register
struct CAMIF_CAM_W09_CFG0_BUF {
	unsigned int reserved4:6;		// [31:26]
	unsigned int cf_buf_th_w09:2;		// [25:24]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_sram_th_w09:5;		// [20:16]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_datawidth_w09:2;		// [9:8]
	unsigned int reserved:8;		// [7:0]
};
 // CAM_W09_CFG1_BUF Register
struct CAMIF_CAM_W09_CFG1_BUF {
	unsigned int reserved2:15;		// [31:17]
	unsigned int cf_endian_w09:1;		// [16]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_maskbyte_w09:3;		// [2:0]
};
 // CAM_W10_STADR_BUF Register
struct CAMIF_CAM_W10_STADR_BUF {
	unsigned int cf_stadr_w10:32;		// [31:0]
};
 // CAM_W10_ENDADR_BUF Register
struct CAMIF_CAM_W10_ENDADR_BUF {
	unsigned int cf_endadr_w10:32;		// [31:0]
};
 // CAM_W10_HEIGHT_BUF Register
struct CAMIF_CAM_W10_HEIGHT_BUF {
	unsigned int reserved:18;		// [31:14]
	unsigned int cf_height_w10:14;		// [13:0]
};
 // CAM_W10_PITCH_BUF Register
struct CAMIF_CAM_W10_PITCH_BUF {
	unsigned int reserved:13;		// [31:19]
	unsigned int cf_pitch_w10:19;		// [18:0]
};
 // CAM_W10_CFG0_BUF Register
struct CAMIF_CAM_W10_CFG0_BUF {
	unsigned int reserved4:6;		// [31:26]
	unsigned int cf_buf_th_w10:2;		// [25:24]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_sram_th_w10:5;		// [20:16]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_datawidth_w10:2;		// [9:8]
	unsigned int reserved:8;		// [7:0]
};
 // CAM_W10_CFG1_BUF Register
struct CAMIF_CAM_W10_CFG1_BUF {
	unsigned int reserved2:15;		// [31:17]
	unsigned int cf_endian_w10:1;		// [16]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_maskbyte_w10:3;		// [2:0]
};
 // CAM_W11_STADR_BUF Register
struct CAMIF_CAM_W11_STADR_BUF {
	unsigned int cf_stadr_w11:32;		// [31:0]
};
 // CAM_W11_ENDADR_BUF Register
struct CAMIF_CAM_W11_ENDADR_BUF {
	unsigned int cf_endadr_w11:32;		// [31:0]
};
 // CAM_W11_HEIGHT_BUF Register
struct CAMIF_CAM_W11_HEIGHT_BUF {
	unsigned int reserved:18;		// [31:14]
	unsigned int cf_height_w11:14;		// [13:0]
};
 // CAM_W11_PITCH_BUF Register
struct CAMIF_CAM_W11_PITCH_BUF {
	unsigned int reserved:13;		// [31:19]
	unsigned int cf_pitch_w11:19;		// [18:0]
};
 // CAM_W11_CFG0_BUF Register
struct CAMIF_CAM_W11_CFG0_BUF {
	unsigned int reserved4:6;		// [31:26]
	unsigned int cf_buf_th_w11:2;		// [25:24]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_sram_th_w11:5;		// [20:16]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_datawidth_w11:2;		// [9:8]
	unsigned int reserved:8;		// [7:0]
};
 // CAM_W11_CFG1_BUF Register
struct CAMIF_CAM_W11_CFG1_BUF {
	unsigned int reserved2:15;		// [31:17]
	unsigned int cf_endian_w11:1;		// [16]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_maskbyte_w11:3;		// [2:0]
};
 // CAM_STATUS Register
struct CAMIF_CAM_STATUS {
	unsigned int reserved3:12;		// [31:20]
	unsigned int accmd_num:4;		// [19:16]
	unsigned int reserved2:5;		// [15:11]
	unsigned int cmd_num:3;		// [10:8]
	unsigned int reserved:6;		// [7:2]
	unsigned int mb_error_inband:1;		// [1]
	unsigned int mb_error_region:1;		// [0]
};
 // CAM_INT Register
struct CAMIF_CAM_INT {
	unsigned int reserved2:12;		// [31:20]
	unsigned int abort_g03:1;		// [19]
	unsigned int abort_g02:1;		// [18]
	unsigned int abort_g01:1;		// [17]
	unsigned int abort_g00:1;		// [16]
	unsigned int mb_err:1;		// [15]
	unsigned int reserved:11;		// [14:4]
	unsigned int int_g03:1;		// [3]
	unsigned int int_g02:1;		// [2]
	unsigned int int_g01:1;		// [1]
	unsigned int int_g00:1;		// [0]
};
 // CAM_W_SRAM Register
struct CAMIF_CAM_W_SRAM {
	unsigned int reserved:20;		// [31:12]
	unsigned int full_w11:1;		// [11]
	unsigned int full_w10:1;		// [10]
	unsigned int full_w09:1;		// [9]
	unsigned int full_w08:1;		// [8]
	unsigned int full_w07:1;		// [7]
	unsigned int full_w06:1;		// [6]
	unsigned int full_w05:1;		// [5]
	unsigned int full_w04:1;		// [4]
	unsigned int full_w03:1;		// [3]
	unsigned int full_w02:1;		// [2]
	unsigned int full_w01:1;		// [1]
	unsigned int full_w00:1;		// [0]
};
 // CAM_W_STOP Register
struct CAMIF_CAM_W_STOP {
	unsigned int reserved:20;		// [31:12]
	unsigned int abort_w11:1;		// [11]
	unsigned int abort_w10:1;		// [10]
	unsigned int abort_w09:1;		// [9]
	unsigned int abort_w08:1;		// [8]
	unsigned int abort_w07:1;		// [7]
	unsigned int abort_w06:1;		// [6]
	unsigned int abort_w05:1;		// [5]
	unsigned int abort_w04:1;		// [4]
	unsigned int abort_w03:1;		// [3]
	unsigned int abort_w02:1;		// [2]
	unsigned int abort_w01:1;		// [1]
	unsigned int abort_w00:1;		// [0]
};
 // CAM_W_RUN Register
struct CAMIF_CAM_W_RUN {
	unsigned int reserved:20;		// [31:12]
	unsigned int run_w11:1;		// [11]
	unsigned int run_w10:1;		// [10]
	unsigned int run_w09:1;		// [9]
	unsigned int run_w08:1;		// [8]
	unsigned int run_w07:1;		// [7]
	unsigned int run_w06:1;		// [6]
	unsigned int run_w05:1;		// [5]
	unsigned int run_w04:1;		// [4]
	unsigned int run_w03:1;		// [3]
	unsigned int run_w02:1;		// [2]
	unsigned int run_w01:1;		// [1]
	unsigned int run_w00:1;		// [0]
};
 // CAM_D00_STADRMON Register
struct CAMIF_CAM_D00_STADRMON {
	unsigned int last_accepted_adr_d00:32;		// [31:0]
};
 // CAM_D01_STADRMON Register
struct CAMIF_CAM_D01_STADRMON {
	unsigned int last_accepted_adr_d01:32;		// [31:0]
};
 // CAM_D02_STADRMON Register
struct CAMIF_CAM_D02_STADRMON {
	unsigned int last_accepted_adr_d02:32;		// [31:0]
};
 // CAM_D03_STADRMON Register
struct CAMIF_CAM_D03_STADRMON {
	unsigned int last_accepted_adr_d03:32;		// [31:0]
};
 // CAM_W00_LINEMON Register
struct CAMIF_CAM_W00_LINEMON {
	unsigned int reserved:18;		// [31:14]
	unsigned int linecount_w00:14;		// [13:0]
};
 // CAM_W00_STADRMON Register
struct CAMIF_CAM_W00_STADRMON {
	unsigned int last_accepted_adr_w00:32;		// [31:0]
};
 // CAM_W01_LINEMON Register
struct CAMIF_CAM_W01_LINEMON {
	unsigned int reserved:18;		// [31:14]
	unsigned int linecount_w01:14;		// [13:0]
};
 // CAM_W01_STADRMON Register
struct CAMIF_CAM_W01_STADRMON {
	unsigned int last_accepted_adr_w01:32;		// [31:0]
};
 // CAM_W02_LINEMON Register
struct CAMIF_CAM_W02_LINEMON {
	unsigned int reserved:18;		// [31:14]
	unsigned int linecount_w02:14;		// [13:0]
};
 // CAM_W02_STADRMON Register
struct CAMIF_CAM_W02_STADRMON {
	unsigned int last_accepted_adr_w02:32;		// [31:0]
};
 // CAM_W03_LINEMON Register
struct CAMIF_CAM_W03_LINEMON {
	unsigned int reserved:18;		// [31:14]
	unsigned int linecount_w03:14;		// [13:0]
};
 // CAM_W03_STADRMON Register
struct CAMIF_CAM_W03_STADRMON {
	unsigned int last_accepted_adr_w03:32;		// [31:0]
};
 // CAM_W04_LINEMON Register
struct CAMIF_CAM_W04_LINEMON {
	unsigned int reserved:18;		// [31:14]
	unsigned int linecount_w04:14;		// [13:0]
};
 // CAM_W04_STADRMON Register
struct CAMIF_CAM_W04_STADRMON {
	unsigned int last_accepted_adr_w04:32;		// [31:0]
};
 // CAM_W05_LINEMON Register
struct CAMIF_CAM_W05_LINEMON {
	unsigned int reserved:18;		// [31:14]
	unsigned int linecount_w05:14;		// [13:0]
};
 // CAM_W05_STADRMON Register
struct CAMIF_CAM_W05_STADRMON {
	unsigned int last_accepted_adr_w05:32;		// [31:0]
};
 // CAM_W06_LINEMON Register
struct CAMIF_CAM_W06_LINEMON {
	unsigned int reserved:18;		// [31:14]
	unsigned int linecount_w06:14;		// [13:0]
};
 // CAM_W06_STADRMON Register
struct CAMIF_CAM_W06_STADRMON {
	unsigned int last_accepted_adr_w06:32;		// [31:0]
};
 // CAM_W07_LINEMON Register
struct CAMIF_CAM_W07_LINEMON {
	unsigned int reserved:18;		// [31:14]
	unsigned int linecount_w07:14;		// [13:0]
};
 // CAM_W07_STADRMON Register
struct CAMIF_CAM_W07_STADRMON {
	unsigned int last_accepted_adr_w07:32;		// [31:0]
};
 // CAM_W08_LINEMON Register
struct CAMIF_CAM_W08_LINEMON {
	unsigned int reserved:18;		// [31:14]
	unsigned int linecount_w08:14;		// [13:0]
};
 // CAM_W08_STADRMON Register
struct CAMIF_CAM_W08_STADRMON {
	unsigned int last_accepted_adr_w08:32;		// [31:0]
};
 // CAM_W09_LINEMON Register
struct CAMIF_CAM_W09_LINEMON {
	unsigned int reserved:18;		// [31:14]
	unsigned int linecount_w09:14;		// [13:0]
};
 // CAM_W09_STADRMON Register
struct CAMIF_CAM_W09_STADRMON {
	unsigned int last_accepted_adr_w09:32;		// [31:0]
};
 // CAM_W10_LINEMON Register
struct CAMIF_CAM_W10_LINEMON {
	unsigned int reserved:18;		// [31:14]
	unsigned int linecount_w10:14;		// [13:0]
};
 // CAM_W10_STADRMON Register
struct CAMIF_CAM_W10_STADRMON {
	unsigned int last_accepted_adr_w10:32;		// [31:0]
};
 // CAM_W11_LINEMON Register
struct CAMIF_CAM_W11_LINEMON {
	unsigned int reserved:18;		// [31:14]
	unsigned int linecount_w11:14;		// [13:0]
};
 // CAM_W11_STADRMON Register
struct CAMIF_CAM_W11_STADRMON {
	unsigned int last_accepted_adr_w11:32;		// [31:0]
};
 // CRX0_CDSIRX_CLKEN Register
struct CAMIF_CRX0_CDSIRX_CLKEN {
	unsigned int reserved:31;		// [31:1]
	unsigned int CDSIRXEn:1;		// [0]
};
 // CRX0_CDSIRX_CLKSEL Register
struct CAMIF_CRX0_CDSIRX_CLKSEL {
	unsigned int reserved:22;		// [31:10]
	unsigned int PPIHsRxClkSel:2;		// [9:8]
	unsigned int reserved2:7;		// [7:1]
	unsigned int PPIHsRxClkEn:1;		// [0]
};
 // CRX0_MODE_CONFIG Register
struct CAMIF_CRX0_MODE_CONFIG {
	unsigned int reserved:31;		// [31:1]
	unsigned int CSI2Mode:1;		// [0]
};
 // CRX0_CDSIRX_SYSTEM_INIT Register
struct CAMIF_CRX0_CDSIRX_SYSTEM_INIT {
	unsigned int reserved:31;		// [31:1]
	unsigned int SysInit:1;		// [0]
};
 // CRX0_LANE_ENABLE Register
struct CAMIF_CRX0_LANE_ENABLE {
	unsigned int reserved:27;		// [31:5]
	unsigned int CLaneEn:1;		// [4]
	unsigned int reserved2:1;		// [3]
	unsigned int DTLaneEn:3;		// [2:0]
};
 // CRX0_VC_ENABLE Register
struct CAMIF_CRX0_VC_ENABLE {
	unsigned int reserved:28;		// [31:4]
	unsigned int VC3En:1;		// [3]
	unsigned int VC2En:1;		// [2]
	unsigned int VC1En:1;		// [1]
	unsigned int VC0En:1;		// [0]
};
 // CRX0_CDSIRX_START Register
struct CAMIF_CRX0_CDSIRX_START {
	unsigned int reserved:31;		// [31:1]
	unsigned int CDSIRXStart:1;		// [0]
};
 // CRX0_LINE_INIT_COUNT Register
struct CAMIF_CRX0_LINE_INIT_COUNT {
	unsigned int reserved:16;		// [31:16]
	unsigned int LINEINITCNT:16;		// [15:0]
};
 // CRX0_HSRXTO_COUNT Register
struct CAMIF_CRX0_HSRXTO_COUNT {
	unsigned int HSToCnt:32;		// [31:0]
};
 // CRX0_FUNC_ENABLE Register
struct CAMIF_CRX0_FUNC_ENABLE {
	unsigned int DebugMdEn:1;		// [31]
	unsigned int reserved:6;		// [30:25]
	unsigned int reserved2:1;		// [23]
	unsigned int LNGPKTINTEn:1;		// [22]
	unsigned int SHTPKTINTEn:1;		// [21]
	unsigned int RXERRINTEn:1;		// [18]
	unsigned int LPRXSTATEEn:1;		// [16]
	unsigned int reserved3:1;		// [15]
	unsigned int LNGPKTINTSTATEEn:1;		// [14]
	unsigned int SHTPKTINTSTATEEn:1;		// [13]
	unsigned int RXERRINTSTATEEn:1;		// [10]
	unsigned int LPRXSTATEINTSTATEEn:1;		// [8]
	unsigned int reserved4:4;		// [7:4]
	unsigned int HSTOCntEn:1;		// [0]
};
 // CRX0_FUNC_MODE Register
struct CAMIF_CRX0_FUNC_MODE {
	unsigned int reserved:21;		// [31:11]
	unsigned int CntAutoRxMd:1;		// [10]
	unsigned int HsToAutoRxMd:1;		// [9]
	unsigned int LpToAutoRxMd:1;		// [8]
	unsigned int reserved2:6;		// [7:2]
	unsigned int BlankPktRcvEn:1;		// [1]
	unsigned int EoTpEn:1;		// [0]
};
 // CRX0_LPRX_STATE_INT_STAT Register
struct CAMIF_CRX0_LPRX_STATE_INT_STAT {
	unsigned int reserved:3;		// [31:29]
	unsigned int CLU1psExit:1;		// [28]
	unsigned int D3UlpsExit:1;		// [27]
	unsigned int D2UlpsExit:1;		// [26]
	unsigned int D1UlpsExit:1;		// [25]
	unsigned int D0UlpsExit:1;		// [24]
	unsigned int reserved2:3;		// [23:21]
	unsigned int CLUlpsEnter:1;		// [20]
	unsigned int D3UlpsEnter:1;		// [19]
	unsigned int D2UlpsEnter:1;		// [18]
	unsigned int D1UlpsEnter:1;		// [17]
	unsigned int D0UlpsEnter:1;		// [16]
	unsigned int reserved3:3;		// [15:13]
	unsigned int CLStopRise:1;		// [12]
	unsigned int D3StopRise:1;		// [11]
	unsigned int D2StopRise:1;		// [10]
	unsigned int D1StopRise:1;		// [9]
	unsigned int D0StopRise:1;		// [8]
	unsigned int reserved4:3;		// [7:5]
	unsigned int AutoCalDone:1;		// [4]
	unsigned int reserved5:1;		// [1]
	unsigned int LineInitDone:1;		// [0]
};
 // CRX0_LPRX_STATE_INT_MASK Register
struct CAMIF_CRX0_LPRX_STATE_INT_MASK {
	unsigned int reserved:3;		// [31:29]
	unsigned int MaskCLUlpsExit:1;		// [28]
	unsigned int MaskD3UlpsExit:1;		// [27]
	unsigned int MaskD2UlpsExit:1;		// [26]
	unsigned int MaskD1UlpsExit:1;		// [25]
	unsigned int MaskD0UlpsExit:1;		// [24]
	unsigned int reserved2:3;		// [23:21]
	unsigned int MaskCLUlpsEnter:1;		// [20]
	unsigned int MaskD3UlpsEnter:1;		// [19]
	unsigned int MaskD2UlpsEnter:1;		// [18]
	unsigned int MaskD1UlpsEnter:1;		// [17]
	unsigned int MaskD0UlpsEnter:1;		// [16]
	unsigned int reserved3:3;		// [15:13]
	unsigned int MaskCLStopRise:1;		// [12]
	unsigned int MaskD3StopRise:1;		// [11]
	unsigned int MaskD2StopRise:1;		// [10]
	unsigned int MaskD1StopRise:1;		// [9]
	unsigned int MaskD0StopRise:1;		// [8]
	unsigned int reserved4:3;		// [7:5]
	unsigned int MaskAutoCalDone:1;		// [4]
	unsigned int reserved5:1;		// [1]
	unsigned int MaskLineInitDone:1;		// [0]
};
 // CRX0_CDSIRX_INTERNAL_STAT Register
struct CAMIF_CRX0_CDSIRX_INTERNAL_STAT {
	unsigned int reserved:4;		// [31:28]
	unsigned int D3_HSRXBUSY:1;		// [27]
	unsigned int D3_LPRXBUSY:1;		// [26]
	unsigned int D2_HSRXBUSY:1;		// [25]
	unsigned int D2_LPRXBUSY:1;		// [24]
	unsigned int D1_HSRXBUSY:1;		// [23]
	unsigned int D1_LPRXBUSY:1;		// [22]
	unsigned int reserved2:1;		// [21]
	unsigned int D0_LPTXBUSY:1;		// [20]
	unsigned int D0_HSRXBUSY:1;		// [19]
	unsigned int D0_LPRXBUSY:1;		// [18]
	unsigned int CL_HSRXBUSY:1;		// [17]
	unsigned int CL_LPRXBUSY:1;		// [16]
	unsigned int reserved3:13;		// [15:3]
	unsigned int CDSI_RXBUSY:1;		// [0]
};
 // CRX0_RXERR_INT_STAT Register
struct CAMIF_CRX0_RXERR_INT_STAT {
	unsigned int ErrRxFifoOvf:1;		// [31]
	unsigned int reserved:1;		// [30]
	unsigned int ErrHsRxTo:1;		// [29]
	unsigned int reserved2:3;		// [28:26]
	unsigned int ErrLdSq:1;		// [25]
	unsigned int reserved3:8;		// [23:16]
	unsigned int reserved4:1;		// [14]
	unsigned int ErrInvalid:1;		// [13]
	unsigned int ErrVCID:1;		// [12]
	unsigned int ErrDataType:1;		// [11]
	unsigned int ErrChecksum:1;		// [10]
	unsigned int ErrEccDbl:1;		// [9]
	unsigned int ErrEccCrctd:1;		// [8]
	unsigned int reserved5:1;		// [7]
	unsigned int ErrCntrl:1;		// [6]
	unsigned int reserved6:1;		// [5]
	unsigned int ErrEsc:1;		// [3]
	unsigned int ErrSotSyncHs:1;		// [1]
	unsigned int ErrSotHs:1;		// [0]
};
 // CRX0_RXERR_INT_MASK Register
struct CAMIF_CRX0_RXERR_INT_MASK {
	unsigned int MaskErrRxFifoOvf:1;		// [31]
	unsigned int reserved:1;		// [30]
	unsigned int MaskErrHsRxTo:1;		// [29]
	unsigned int reserved2:3;		// [28:26]
	unsigned int MaskErrLdSq:1;		// [25]
	unsigned int reserved3:8;		// [23:16]
	unsigned int reserved4:1;		// [14]
	unsigned int MaskErrInvalid:1;		// [13]
	unsigned int MaskErrVCID:1;		// [12]
	unsigned int MaskErrDataType:1;		// [11]
	unsigned int MaskErrChecksum:1;		// [10]
	unsigned int MaskErrEccDbl:1;		// [9]
	unsigned int MaskErrEccCrctd:1;		// [8]
	unsigned int reserved5:1;		// [7]
	unsigned int MaskErrCntrl:1;		// [6]
	unsigned int reserved6:1;		// [5]
	unsigned int MaskErrEsc:1;		// [3]
	unsigned int MaskErrSotSyncHs:1;		// [1]
	unsigned int MaskErrSotHs:1;		// [0]
};
 // CRX0_ERR_STATUS Register
struct CAMIF_CRX0_ERR_STATUS {
	unsigned int reserved:16;		// [31:16]
	unsigned int reserved2:1;		// [14]
	unsigned int ErrInvalid:1;		// [13]
	unsigned int ErrVCID:1;		// [12]
	unsigned int ErrDataType:1;		// [11]
	unsigned int ErrChecksum:1;		// [10]
	unsigned int ErrEccDbl:1;		// [9]
	unsigned int ErrEccCrctd:1;		// [8]
	unsigned int ErrCntLp:1;		// [7]
	unsigned int ErrCntrl:1;		// [6]
	unsigned int ErrTo:1;		// [5]
	unsigned int ErrEsc:1;		// [3]
	unsigned int ErrSotSyncHs:1;		// [1]
	unsigned int ErrSotHs:1;		// [0]
};
 // CRX0_PPI_HSRX_CNTRL Register
struct CAMIF_CRX0_PPI_HSRX_CNTRL {
	unsigned int reserved:1;		// [31]
	unsigned int CLHSRXENFCTRL:1;		// [30]
	unsigned int reserved2:4;		// [29:26]
	unsigned int DTHSRXENRCTRL:2;		// [25:24]
	unsigned int reserved3:6;		// [23:18]
	unsigned int CLS_ATMR:2;		// [17:16]
	unsigned int reserved4:2;		// [15:14]
	unsigned int D3S_ATMR:2;		// [13:12]
	unsigned int reserved5:2;		// [11:10]
	unsigned int D2S_ATMR:2;		// [9:8]
	unsigned int reserved6:2;		// [7:6]
	unsigned int D1S_ATMR:2;		// [5:4]
	unsigned int reserved7:2;		// [3:2]
	unsigned int D0S_ATMR:2;		// [1:0]
};
 // CRX0_PPI_HSRX_COUNT Register
struct CAMIF_CRX0_PPI_HSRX_COUNT {
	unsigned int CLSETTLECnt:8;		// [31:24]
	unsigned int reserved:4;		// [23:20]
	unsigned int DTHSEXITCnt:4;		// [19:16]
	unsigned int HSSETTLECnt:8;		// [15:8]
	unsigned int DTCLRSIPOCnt:8;		// [7:0]
};
 // CRX0_PPI_DPHY_DLYCNTRL Register
struct CAMIF_CRX0_PPI_DPHY_DLYCNTRL {
	unsigned int reserved:12;		// [31:20]
	unsigned int CLS_DLYCNTRL:4;		// [19:16]
	unsigned int D3S_DLYCNTRL:4;		// [15:12]
	unsigned int D2S_DLYCNTRL:4;		// [11:8]
	unsigned int D1S_DLYCNTRL:4;		// [7:4]
	unsigned int D0S_DLYCNTRL:4;		// [3:0]
};
 // CRX0_PPI_DPHY_LPRX_THSLD Register
struct CAMIF_CRX0_PPI_DPHY_LPRX_THSLD {
	unsigned int reserved:22;		// [31:10]
	unsigned int CLS_CUTRSEL:1;		// [9]
	unsigned int CLS_LPRXVTHLOW:1;		// [8]
	unsigned int D3S_CUTRSEL:1;		// [7]
	unsigned int D3S_LPRXVTHLOW:1;		// [6]
	unsigned int D2S_CUTRSEL:1;		// [5]
	unsigned int D2S_LPRXVTHLOW:1;		// [4]
	unsigned int D1S_CUTRSEL:1;		// [3]
	unsigned int D1S_LPRXVTHLOW:1;		// [2]
	unsigned int D0S_CUTRSEL:1;		// [1]
	unsigned int D0S_LPRXVTHLOW:1;		// [0]
};
 // CRX0_PPI_DPHY_LPRXCALCNTRL Register
struct CAMIF_CRX0_PPI_DPHY_LPRXCALCNTRL {
	unsigned int reserved:8;		// [31:24]
	unsigned int AutoCalCnt:8;		// [23:16]
	unsigned int reserved2:9;		// [15:7]
	unsigned int LPRXCALTRIM:3;		// [6:4]
	unsigned int reserved3:2;		// [3:2]
	unsigned int LPRXCALRES:1;		// [1]
	unsigned int LPRXCALEN:1;		// [0]
};
 // CRX0_PPI_DPHY_LPRXAUTOCALST Register
struct CAMIF_CRX0_PPI_DPHY_LPRXAUTOCALST {
	unsigned int reserved:31;		// [31:1]
	unsigned int AutoCalStrt:1;		// [0]
};
 // CRX0_LANE_STATUS_HS Register
struct CAMIF_CRX0_LANE_STATUS_HS {
	unsigned int reserved:24;		// [31:8]
	unsigned int CLRxActiveHS:1;		// [7]
	unsigned int reserved2:3;		// [6:4]
	unsigned int D3RxActiveHS:1;		// [3]
	unsigned int D2RxActiveHS:1;		// [2]
	unsigned int D1RxActiveHS:1;		// [1]
	unsigned int D0RxActiveHS:1;		// [0]
};
 // CRX0_LANE_STATUS_LP Register
struct CAMIF_CRX0_LANE_STATUS_LP {
	unsigned int reserved:7;		// [31:25]
	unsigned int ClUlpsEsc:1;		// [23]
	unsigned int L0Direction:1;		// [22]
	unsigned int reserved2:2;		// [21:20]
	unsigned int L3UlpsEsc:1;		// [19]
	unsigned int L2UlpsEsc:1;		// [18]
	unsigned int L1UlpsEsc:1;		// [17]
	unsigned int L0UlpsEsc:1;		// [16]
	unsigned int ClUlpsActive:1;		// [15]
	unsigned int reserved3:3;		// [14:12]
	unsigned int L3UlpsActive:1;		// [11]
	unsigned int L2UlpsActive:1;		// [10]
	unsigned int L1UlpsActive:1;		// [9]
	unsigned int L0UlpsActive:1;		// [8]
	unsigned int ClStopState:1;		// [7]
	unsigned int reserved4:3;		// [6:4]
	unsigned int L3StopState:1;		// [3]
	unsigned int L2StopState:1;		// [2]
	unsigned int L1StopState:1;		// [1]
	unsigned int L0StopState:1;		// [0]
};
 // CRX0_VC0_SH_INT_STAT Register
struct CAMIF_CRX0_VC0_SH_INT_STAT {
	unsigned int reserved:16;		// [31:16]
	unsigned int VC0_GSP8:1;		// [15]
	unsigned int VC0_GSP7:1;		// [14]
	unsigned int VC0_GSP6:1;		// [13]
	unsigned int VC0_GSP5:1;		// [12]
	unsigned int VC0_GSP4:1;		// [11]
	unsigned int VC0_GSP3:1;		// [10]
	unsigned int VC0_GSP2:1;		// [9]
	unsigned int VC0_GSP1:1;		// [8]
	unsigned int reserved2:4;		// [7:4]
	unsigned int VC0_LE:1;		// [3]
	unsigned int VC0_LS:1;		// [2]
	unsigned int VC0_FE:1;		// [1]
	unsigned int VC0_FS:1;		// [0]
};
 // CRX0_VC0_SH_INT_MASK Register
struct CAMIF_CRX0_VC0_SH_INT_MASK {
	unsigned int reserved:16;		// [31:16]
	unsigned int MaskVC0_GSP8:1;		// [15]
	unsigned int MaskVC0_GSP7:1;		// [14]
	unsigned int MaskVC0_GSP6:1;		// [13]
	unsigned int MaskVC0_GSP5:1;		// [12]
	unsigned int MaskVC0_GSP4:1;		// [11]
	unsigned int MaskVC0_GSP3:1;		// [10]
	unsigned int MaskVC0_GSP2:1;		// [9]
	unsigned int MaskVC0_GSP1:1;		// [8]
	unsigned int reserved2:4;		// [7:4]
	unsigned int MaskVC0_LE:1;		// [3]
	unsigned int MaskVC0_LS:1;		// [2]
	unsigned int MaskVC0_FE:1;		// [1]
	unsigned int MaskVC0_FS:1;		// [0]
};
 // CRX0_VC0_LN0_INT_STAT Register
struct CAMIF_CRX0_VC0_LN0_INT_STAT {
	unsigned int reserved:2;		// [31:30]
	unsigned int VC0_RAW14:1;		// [29]
	unsigned int VC0_RAW12:1;		// [28]
	unsigned int VC0_RAW10:1;		// [27]
	unsigned int VC0_RAW8:1;		// [26]
	unsigned int VC0_RAW7:1;		// [25]
	unsigned int VC0_RAW6:1;		// [24]
	unsigned int reserved2:3;		// [23:21]
	unsigned int VC0_RGB888:1;		// [20]
	unsigned int VC0_RGB666:1;		// [19]
	unsigned int VC0_RGB565:1;		// [18]
	unsigned int VC0_RGB555:1;		// [17]
	unsigned int VC0_RGB444:1;		// [16]
	unsigned int VC0_YUV422_10:1;		// [15]
	unsigned int VC0_YUV422_8:1;		// [14]
	unsigned int VC0_YUV420_10_Chr:1;		// [13]
	unsigned int VC0_YUV420_8_Chr:1;		// [12]
	unsigned int reserved3:1;		// [11]
	unsigned int VC0_LegYUV420_8:1;		// [10]
	unsigned int VC0_YUV420_10:1;		// [9]
	unsigned int VC0_YUV420_8:1;		// [8]
	unsigned int reserved4:5;		// [7:3]
	unsigned int VC0_Embedded:1;		// [2]
	unsigned int VC0_Blank:1;		// [1]
	unsigned int VC0_Null:1;		// [0]
};
 // CRX0_VC0_LN1_INT_STAT Register
struct CAMIF_CRX0_VC0_LN1_INT_STAT {
	unsigned int reserved:24;		// [31:8]
	unsigned int VC0_define8:1;		// [7]
	unsigned int VC0_define7:1;		// [6]
	unsigned int VC0_define6:1;		// [5]
	unsigned int VC0_define5:1;		// [4]
	unsigned int VC0_define4:1;		// [3]
	unsigned int VC0_define3:1;		// [2]
	unsigned int VC0_define2:1;		// [1]
	unsigned int VC0_define1:1;		// [0]
};
 // CRX0_VC0_LN0_INT_MASK Register
struct CAMIF_CRX0_VC0_LN0_INT_MASK {
	unsigned int reserved:2;		// [31:30]
	unsigned int MaskVC0_RAW14:1;		// [29]
	unsigned int MaskVC0_RAW12:1;		// [28]
	unsigned int MaskVC0_RAW10:1;		// [27]
	unsigned int MaskVC0_RAW8:1;		// [26]
	unsigned int MaskVC0_RAW7:1;		// [25]
	unsigned int MaskVC0_RAW6:1;		// [24]
	unsigned int reserved2:3;		// [23:21]
	unsigned int MaskVC0_RGB888:1;		// [20]
	unsigned int MaskVC0_RGB666:1;		// [19]
	unsigned int MaskVC0_RGB565:1;		// [18]
	unsigned int MaskVC0_RGB555:1;		// [17]
	unsigned int MaskVC0_RGB444:1;		// [16]
	unsigned int MaskVC0_YUV422_10:1;		// [15]
	unsigned int MaskVC0_YUV422_8:1;		// [14]
	unsigned int MaskVC0_YUV420_10_Chr:1;		// [13]
	unsigned int MaskVC0_YUV420_8_Chr:1;		// [12]
	unsigned int reserved3:1;		// [11]
	unsigned int MaskVC0_LegYUV420_8:1;		// [10]
	unsigned int MaskVC0_YUV420_10:1;		// [9]
	unsigned int MaskVC0_YUV420_8:1;		// [8]
	unsigned int reserved4:5;		// [7:3]
	unsigned int MaskVC0_Embedded:1;		// [2]
	unsigned int MaskVC0_Blank:1;		// [1]
	unsigned int MaskVC0_Null:1;		// [0]
};
 // CRX0_VC0_LN1_INT_MASK Register
struct CAMIF_CRX0_VC0_LN1_INT_MASK {
	unsigned int reserved:24;		// [31:8]
	unsigned int MaskVC0_define8:1;		// [7]
	unsigned int MaskVC0_define7:1;		// [6]
	unsigned int MaskVC0_define6:1;		// [5]
	unsigned int MaskVC0_define5:1;		// [4]
	unsigned int MaskVC0_define4:1;		// [3]
	unsigned int MaskVC0_define3:1;		// [2]
	unsigned int MaskVC0_define2:1;		// [1]
	unsigned int MaskVC0_define1:1;		// [0]
};
 // CRX0_RCV_PKT_HEADER Register
struct CAMIF_CRX0_RCV_PKT_HEADER {
	unsigned int LatestECC:8;		// [31:24]
	unsigned int LatestWC1Data:8;		// [23:16]
	unsigned int LatestWC0Data:8;		// [15:8]
	unsigned int LatestVC:2;		// [7:6]
	unsigned int LatestDT:6;		// [5:0]
};
 // CRX0_VC0_FNLN_STAT Register
struct CAMIF_CRX0_VC0_FNLN_STAT {
	unsigned int VC0_FN:16;		// [31:16]
	unsigned int VC0_LN:16;		// [15:0]
};
 // CRX1_CDSIRX_CLKEN Register
struct CAMIF_CRX1_CDSIRX_CLKEN {
	unsigned int reserved:31;		// [31:1]
	unsigned int CDSIRXEn:1;		// [0]
};
 // CRX1_CDSIRX_CLKSEL Register
struct CAMIF_CRX1_CDSIRX_CLKSEL {
	unsigned int reserved:22;		// [31:10]
	unsigned int PPIHsRxClkSel:2;		// [9:8]
	unsigned int reserved2:7;		// [7:1]
	unsigned int PPIHsRxClkEn:1;		// [0]
};
 // CRX1_MODE_CONFIG Register
struct CAMIF_CRX1_MODE_CONFIG {
	unsigned int reserved:31;		// [31:1]
	unsigned int CSI2Mode:1;		// [0]
};
 // CRX1_CDSIRX_SYSTEM_INIT Register
struct CAMIF_CRX1_CDSIRX_SYSTEM_INIT {
	unsigned int reserved:31;		// [31:1]
	unsigned int SysInit:1;		// [0]
};
 // CRX1_LANE_ENABLE Register
struct CAMIF_CRX1_LANE_ENABLE {
	unsigned int reserved:27;		// [31:5]
	unsigned int CLaneEn:1;		// [4]
	unsigned int reserved2:1;		// [3]
	unsigned int DTLaneEn:3;		// [2:0]
};
 // CRX1_VC_ENABLE Register
struct CAMIF_CRX1_VC_ENABLE {
	unsigned int reserved:28;		// [31:4]
	unsigned int VC3En:1;		// [3]
	unsigned int VC2En:1;		// [2]
	unsigned int VC1En:1;		// [1]
	unsigned int VC0En:1;		// [0]
};
 // CRX1_CDSIRX_START Register
struct CAMIF_CRX1_CDSIRX_START {
	unsigned int reserved:31;		// [31:1]
	unsigned int CDSIRXStart:1;		// [0]
};
 // CRX1_LINE_INIT_COUNT Register
struct CAMIF_CRX1_LINE_INIT_COUNT {
	unsigned int reserved:16;		// [31:16]
	unsigned int LINEINITCNT:16;		// [15:0]
};
 // CRX1_HSRXTO_COUNT Register
struct CAMIF_CRX1_HSRXTO_COUNT {
	unsigned int HSToCnt:32;		// [31:0]
};
 // CRX1_FUNC_ENABLE Register
struct CAMIF_CRX1_FUNC_ENABLE {
	unsigned int DebugMdEn:1;		// [31]
	unsigned int reserved:6;		// [30:25]
	unsigned int reserved2:1;		// [23]
	unsigned int LNGPKTINTEn:1;		// [22]
	unsigned int SHTPKTINTEn:1;		// [21]
	unsigned int RXERRINTEn:1;		// [18]
	unsigned int LPRXSTATEEn:1;		// [16]
	unsigned int reserved3:1;		// [15]
	unsigned int LNGPKTINTSTATEEn:1;		// [14]
	unsigned int SHTPKTINTSTATEEn:1;		// [13]
	unsigned int RXERRINTSTATEEn:1;		// [10]
	unsigned int LPRXSTATEINTSTATEEn:1;		// [8]
	unsigned int reserved4:4;		// [7:4]
	unsigned int HSTOCntEn:1;		// [0]
};
 // CRX1_FUNC_MODE Register
struct CAMIF_CRX1_FUNC_MODE {
	unsigned int reserved:21;		// [31:11]
	unsigned int CntAutoRxMd:1;		// [10]
	unsigned int HsToAutoRxMd:1;		// [9]
	unsigned int LpToAutoRxMd:1;		// [8]
	unsigned int reserved2:6;		// [7:2]
	unsigned int BlankPktRcvEn:1;		// [1]
	unsigned int EoTpEn:1;		// [0]
};
 // CRX1_LPRX_STATE_INT_STAT Register
struct CAMIF_CRX1_LPRX_STATE_INT_STAT {
	unsigned int reserved:3;		// [31:29]
	unsigned int CLU1psExit:1;		// [28]
	unsigned int D3UlpsExit:1;		// [27]
	unsigned int D2UlpsExit:1;		// [26]
	unsigned int D1UlpsExit:1;		// [25]
	unsigned int D0UlpsExit:1;		// [24]
	unsigned int reserved2:3;		// [23:21]
	unsigned int CLUlpsEnter:1;		// [20]
	unsigned int D3UlpsEnter:1;		// [19]
	unsigned int D2UlpsEnter:1;		// [18]
	unsigned int D1UlpsEnter:1;		// [17]
	unsigned int D0UlpsEnter:1;		// [16]
	unsigned int reserved3:3;		// [15:13]
	unsigned int CLStopRise:1;		// [12]
	unsigned int D3StopRise:1;		// [11]
	unsigned int D2StopRise:1;		// [10]
	unsigned int D1StopRise:1;		// [9]
	unsigned int D0StopRise:1;		// [8]
	unsigned int reserved4:3;		// [7:5]
	unsigned int AutoCalDone:1;		// [4]
	unsigned int reserved5:1;		// [1]
	unsigned int LineInitDone:1;		// [0]
};
 // CRX1_LPRX_STATE_INT_MASK Register
struct CAMIF_CRX1_LPRX_STATE_INT_MASK {
	unsigned int reserved:3;		// [31:29]
	unsigned int MaskCLUlpsExit:1;		// [28]
	unsigned int MaskD3UlpsExit:1;		// [27]
	unsigned int MaskD2UlpsExit:1;		// [26]
	unsigned int MaskD1UlpsExit:1;		// [25]
	unsigned int MaskD0UlpsExit:1;		// [24]
	unsigned int reserved2:3;		// [23:21]
	unsigned int MaskCLUlpsEnter:1;		// [20]
	unsigned int MaskD3UlpsEnter:1;		// [19]
	unsigned int MaskD2UlpsEnter:1;		// [18]
	unsigned int MaskD1UlpsEnter:1;		// [17]
	unsigned int MaskD0UlpsEnter:1;		// [16]
	unsigned int reserved3:3;		// [15:13]
	unsigned int MaskCLStopRise:1;		// [12]
	unsigned int MaskD3StopRise:1;		// [11]
	unsigned int MaskD2StopRise:1;		// [10]
	unsigned int MaskD1StopRise:1;		// [9]
	unsigned int MaskD0StopRise:1;		// [8]
	unsigned int reserved4:3;		// [7:5]
	unsigned int MaskAutoCalDone:1;		// [4]
	unsigned int reserved5:1;		// [1]
	unsigned int MaskLineInitDone:1;		// [0]
};
 // CRX1_CDSIRX_INTERNAL_STAT Register
struct CAMIF_CRX1_CDSIRX_INTERNAL_STAT {
	unsigned int reserved:4;		// [31:28]
	unsigned int D3_HSRXBUSY:1;		// [27]
	unsigned int D3_LPRXBUSY:1;		// [26]
	unsigned int D2_HSRXBUSY:1;		// [25]
	unsigned int D2_LPRXBUSY:1;		// [24]
	unsigned int D1_HSRXBUSY:1;		// [23]
	unsigned int D1_LPRXBUSY:1;		// [22]
	unsigned int reserved2:1;		// [21]
	unsigned int D0_LPTXBUSY:1;		// [20]
	unsigned int D0_HSRXBUSY:1;		// [19]
	unsigned int D0_LPRXBUSY:1;		// [18]
	unsigned int CL_HSRXBUSY:1;		// [17]
	unsigned int CL_LPRXBUSY:1;		// [16]
	unsigned int reserved3:13;		// [15:3]
	unsigned int CDSI_RXBUSY:1;		// [0]
};
 // CRX1_RXERR_INT_STAT Register
struct CAMIF_CRX1_RXERR_INT_STAT {
	unsigned int ErrRxFifoOvf:1;		// [31]
	unsigned int reserved:1;		// [30]
	unsigned int ErrHsRxTo:1;		// [29]
	unsigned int reserved2:3;		// [28:26]
	unsigned int ErrLdSq:1;		// [25]
	unsigned int reserved3:8;		// [23:16]
	unsigned int reserved4:1;		// [14]
	unsigned int ErrInvalid:1;		// [13]
	unsigned int ErrVCID:1;		// [12]
	unsigned int ErrDataType:1;		// [11]
	unsigned int ErrChecksum:1;		// [10]
	unsigned int ErrEccDbl:1;		// [9]
	unsigned int ErrEccCrctd:1;		// [8]
	unsigned int reserved5:1;		// [7]
	unsigned int ErrCntrl:1;		// [6]
	unsigned int reserved6:1;		// [5]
	unsigned int ErrEsc:1;		// [3]
	unsigned int ErrSotSyncHs:1;		// [1]
	unsigned int ErrSotHs:1;		// [0]
};
 // CRX1_RXERR_INT_MASK Register
struct CAMIF_CRX1_RXERR_INT_MASK {
	unsigned int MaskErrRxFifoOvf:1;		// [31]
	unsigned int reserved:1;		// [30]
	unsigned int MaskErrHsRxTo:1;		// [29]
	unsigned int reserved2:3;		// [28:26]
	unsigned int MaskErrLdSq:1;		// [25]
	unsigned int reserved3:8;		// [23:16]
	unsigned int reserved4:1;		// [14]
	unsigned int MaskErrInvalid:1;		// [13]
	unsigned int MaskErrVCID:1;		// [12]
	unsigned int MaskErrDataType:1;		// [11]
	unsigned int MaskErrChecksum:1;		// [10]
	unsigned int MaskErrEccDbl:1;		// [9]
	unsigned int MaskErrEccCrctd:1;		// [8]
	unsigned int reserved5:1;		// [7]
	unsigned int MaskErrCntrl:1;		// [6]
	unsigned int reserved6:1;		// [5]
	unsigned int MaskErrEsc:1;		// [3]
	unsigned int MaskErrSotSyncHs:1;		// [1]
	unsigned int MaskErrSotHs:1;		// [0]
};
 // CRX1_ERR_STATUS Register
struct CAMIF_CRX1_ERR_STATUS {
	unsigned int reserved:16;		// [31:16]
	unsigned int reserved2:1;		// [14]
	unsigned int ErrInvalid:1;		// [13]
	unsigned int ErrVCID:1;		// [12]
	unsigned int ErrDataType:1;		// [11]
	unsigned int ErrChecksum:1;		// [10]
	unsigned int ErrEccDbl:1;		// [9]
	unsigned int ErrEccCrctd:1;		// [8]
	unsigned int ErrCntLp:1;		// [7]
	unsigned int ErrCntrl:1;		// [6]
	unsigned int ErrTo:1;		// [5]
	unsigned int ErrEsc:1;		// [3]
	unsigned int ErrSotSyncHs:1;		// [1]
	unsigned int ErrSotHs:1;		// [0]
};
 // CRX1_PPI_HSRX_CNTRL Register
struct CAMIF_CRX1_PPI_HSRX_CNTRL {
	unsigned int reserved:1;		// [31]
	unsigned int CLHSRXENFCTRL:1;		// [30]
	unsigned int reserved2:4;		// [29:26]
	unsigned int DTHSRXENRCTRL:2;		// [25:24]
	unsigned int reserved3:6;		// [23:18]
	unsigned int CLS_ATMR:2;		// [17:16]
	unsigned int reserved4:2;		// [15:14]
	unsigned int D3S_ATMR:2;		// [13:12]
	unsigned int reserved5:2;		// [11:10]
	unsigned int D2S_ATMR:2;		// [9:8]
	unsigned int reserved6:2;		// [7:6]
	unsigned int D1S_ATMR:2;		// [5:4]
	unsigned int reserved7:2;		// [3:2]
	unsigned int D0S_ATMR:2;		// [1:0]
};
 // CRX1_PPI_HSRX_COUNT Register
struct CAMIF_CRX1_PPI_HSRX_COUNT {
	unsigned int CLSETTLECnt:8;		// [31:24]
	unsigned int reserved:4;		// [23:20]
	unsigned int DTHSEXITCnt:4;		// [19:16]
	unsigned int HSSETTLECnt:8;		// [15:8]
	unsigned int DTCLRSIPOCnt:8;		// [7:0]
};
 // CRX1_PPI_DPHY_DLYCNTRL Register
struct CAMIF_CRX1_PPI_DPHY_DLYCNTRL {
	unsigned int reserved:12;		// [31:20]
	unsigned int CLS_DLYCNTRL:4;		// [19:16]
	unsigned int D3S_DLYCNTRL:4;		// [15:12]
	unsigned int D2S_DLYCNTRL:4;		// [11:8]
	unsigned int D1S_DLYCNTRL:4;		// [7:4]
	unsigned int D0S_DLYCNTRL:4;		// [3:0]
};
 // CRX1_PPI_DPHY_LPRX_THSLD Register
struct CAMIF_CRX1_PPI_DPHY_LPRX_THSLD {
	unsigned int reserved:22;		// [31:10]
	unsigned int CLS_CUTRSEL:1;		// [9]
	unsigned int CLS_LPRXVTHLOW:1;		// [8]
	unsigned int D3S_CUTRSEL:1;		// [7]
	unsigned int D3S_LPRXVTHLOW:1;		// [6]
	unsigned int D2S_CUTRSEL:1;		// [5]
	unsigned int D2S_LPRXVTHLOW:1;		// [4]
	unsigned int D1S_CUTRSEL:1;		// [3]
	unsigned int D1S_LPRXVTHLOW:1;		// [2]
	unsigned int D0S_CUTRSEL:1;		// [1]
	unsigned int D0S_LPRXVTHLOW:1;		// [0]
};
 // CRX1_PPI_DPHY_LPRXCALCNTRL Register
struct CAMIF_CRX1_PPI_DPHY_LPRXCALCNTRL {
	unsigned int reserved:8;		// [31:24]
	unsigned int AutoCalCnt:8;		// [23:16]
	unsigned int reserved2:9;		// [15:7]
	unsigned int LPRXCALTRIM:3;		// [6:4]
	unsigned int reserved3:2;		// [3:2]
	unsigned int LPRXCALRES:1;		// [1]
	unsigned int LPRXCALEN:1;		// [0]
};
 // CRX1_PPI_DPHY_LPRXAUTOCALST Register
struct CAMIF_CRX1_PPI_DPHY_LPRXAUTOCALST {
	unsigned int reserved:31;		// [31:1]
	unsigned int AutoCalStrt:1;		// [0]
};
 // CRX1_LANE_STATUS_HS Register
struct CAMIF_CRX1_LANE_STATUS_HS {
	unsigned int reserved:24;		// [31:8]
	unsigned int CLRxActiveHS:1;		// [7]
	unsigned int reserved2:3;		// [6:4]
	unsigned int D3RxActiveHS:1;		// [3]
	unsigned int D2RxActiveHS:1;		// [2]
	unsigned int D1RxActiveHS:1;		// [1]
	unsigned int D0RxActiveHS:1;		// [0]
};
 // CRX1_LANE_STATUS_LP Register
struct CAMIF_CRX1_LANE_STATUS_LP {
	unsigned int reserved:7;		// [31:25]
	unsigned int ClUlpsEsc:1;		// [23]
	unsigned int L0Direction:1;		// [22]
	unsigned int reserved2:2;		// [21:20]
	unsigned int L3UlpsEsc:1;		// [19]
	unsigned int L2UlpsEsc:1;		// [18]
	unsigned int L1UlpsEsc:1;		// [17]
	unsigned int L0UlpsEsc:1;		// [16]
	unsigned int ClUlpsActive:1;		// [15]
	unsigned int reserved3:3;		// [14:12]
	unsigned int L3UlpsActive:1;		// [11]
	unsigned int L2UlpsActive:1;		// [10]
	unsigned int L1UlpsActive:1;		// [9]
	unsigned int L0UlpsActive:1;		// [8]
	unsigned int ClStopState:1;		// [7]
	unsigned int reserved4:3;		// [6:4]
	unsigned int L3StopState:1;		// [3]
	unsigned int L2StopState:1;		// [2]
	unsigned int L1StopState:1;		// [1]
	unsigned int L0StopState:1;		// [0]
};
 // CRX1_VC0_SH_INT_STAT Register
struct CAMIF_CRX1_VC0_SH_INT_STAT {
	unsigned int reserved:16;		// [31:16]
	unsigned int VC0_GSP8:1;		// [15]
	unsigned int VC0_GSP7:1;		// [14]
	unsigned int VC0_GSP6:1;		// [13]
	unsigned int VC0_GSP5:1;		// [12]
	unsigned int VC0_GSP4:1;		// [11]
	unsigned int VC0_GSP3:1;		// [10]
	unsigned int VC0_GSP2:1;		// [9]
	unsigned int VC0_GSP1:1;		// [8]
	unsigned int reserved2:4;		// [7:4]
	unsigned int VC0_LE:1;		// [3]
	unsigned int VC0_LS:1;		// [2]
	unsigned int VC0_FE:1;		// [1]
	unsigned int VC0_FS:1;		// [0]
};
 // CRX1_VC0_SH_INT_MASK Register
struct CAMIF_CRX1_VC0_SH_INT_MASK {
	unsigned int reserved:16;		// [31:16]
	unsigned int MaskVC0_GSP8:1;		// [15]
	unsigned int MaskVC0_GSP7:1;		// [14]
	unsigned int MaskVC0_GSP6:1;		// [13]
	unsigned int MaskVC0_GSP5:1;		// [12]
	unsigned int MaskVC0_GSP4:1;		// [11]
	unsigned int MaskVC0_GSP3:1;		// [10]
	unsigned int MaskVC0_GSP2:1;		// [9]
	unsigned int MaskVC0_GSP1:1;		// [8]
	unsigned int reserved2:4;		// [7:4]
	unsigned int MaskVC0_LE:1;		// [3]
	unsigned int MaskVC0_LS:1;		// [2]
	unsigned int MaskVC0_FE:1;		// [1]
	unsigned int MaskVC0_FS:1;		// [0]
};
 // CRX1_VC0_LN0_INT_STAT Register
struct CAMIF_CRX1_VC0_LN0_INT_STAT {
	unsigned int reserved:2;		// [31:30]
	unsigned int VC0_RAW14:1;		// [29]
	unsigned int VC0_RAW12:1;		// [28]
	unsigned int VC0_RAW10:1;		// [27]
	unsigned int VC0_RAW8:1;		// [26]
	unsigned int VC0_RAW7:1;		// [25]
	unsigned int VC0_RAW6:1;		// [24]
	unsigned int reserved2:3;		// [23:21]
	unsigned int VC0_RGB888:1;		// [20]
	unsigned int VC0_RGB666:1;		// [19]
	unsigned int VC0_RGB565:1;		// [18]
	unsigned int VC0_RGB555:1;		// [17]
	unsigned int VC0_RGB444:1;		// [16]
	unsigned int VC0_YUV422_10:1;		// [15]
	unsigned int VC0_YUV422_8:1;		// [14]
	unsigned int VC0_YUV420_10_Chr:1;		// [13]
	unsigned int VC0_YUV420_8_Chr:1;		// [12]
	unsigned int reserved3:1;		// [11]
	unsigned int VC0_LegYUV420_8:1;		// [10]
	unsigned int VC0_YUV420_10:1;		// [9]
	unsigned int VC0_YUV420_8:1;		// [8]
	unsigned int reserved4:5;		// [7:3]
	unsigned int VC0_Embedded:1;		// [2]
	unsigned int VC0_Blank:1;		// [1]
	unsigned int VC0_Null:1;		// [0]
};
 // CRX1_VC0_LN1_INT_STAT Register
struct CAMIF_CRX1_VC0_LN1_INT_STAT {
	unsigned int reserved:24;		// [31:8]
	unsigned int VC0_define8:1;		// [7]
	unsigned int VC0_define7:1;		// [6]
	unsigned int VC0_define6:1;		// [5]
	unsigned int VC0_define5:1;		// [4]
	unsigned int VC0_define4:1;		// [3]
	unsigned int VC0_define3:1;		// [2]
	unsigned int VC0_define2:1;		// [1]
	unsigned int VC0_define1:1;		// [0]
};
 // CRX1_VC0_LN0_INT_MASK Register
struct CAMIF_CRX1_VC0_LN0_INT_MASK {
	unsigned int reserved:2;		// [31:30]
	unsigned int MaskVC0_RAW14:1;		// [29]
	unsigned int MaskVC0_RAW12:1;		// [28]
	unsigned int MaskVC0_RAW10:1;		// [27]
	unsigned int MaskVC0_RAW8:1;		// [26]
	unsigned int MaskVC0_RAW7:1;		// [25]
	unsigned int MaskVC0_RAW6:1;		// [24]
	unsigned int reserved2:3;		// [23:21]
	unsigned int MaskVC0_RGB888:1;		// [20]
	unsigned int MaskVC0_RGB666:1;		// [19]
	unsigned int MaskVC0_RGB565:1;		// [18]
	unsigned int MaskVC0_RGB555:1;		// [17]
	unsigned int MaskVC0_RGB444:1;		// [16]
	unsigned int MaskVC0_YUV422_10:1;		// [15]
	unsigned int MaskVC0_YUV422_8:1;		// [14]
	unsigned int MaskVC0_YUV420_10_Chr:1;		// [13]
	unsigned int MaskVC0_YUV420_8_Chr:1;		// [12]
	unsigned int reserved3:1;		// [11]
	unsigned int MaskVC0_LegYUV420_8:1;		// [10]
	unsigned int MaskVC0_YUV420_10:1;		// [9]
	unsigned int MaskVC0_YUV420_8:1;		// [8]
	unsigned int reserved4:5;		// [7:3]
	unsigned int MaskVC0_Embedded:1;		// [2]
	unsigned int MaskVC0_Blank:1;		// [1]
	unsigned int MaskVC0_Null:1;		// [0]
};
 // CRX1_VC0_LN1_INT_MASK Register
struct CAMIF_CRX1_VC0_LN1_INT_MASK {
	unsigned int reserved:24;		// [31:8]
	unsigned int MaskVC0_define8:1;		// [7]
	unsigned int MaskVC0_define7:1;		// [6]
	unsigned int MaskVC0_define6:1;		// [5]
	unsigned int MaskVC0_define5:1;		// [4]
	unsigned int MaskVC0_define4:1;		// [3]
	unsigned int MaskVC0_define3:1;		// [2]
	unsigned int MaskVC0_define2:1;		// [1]
	unsigned int MaskVC0_define1:1;		// [0]
};
 // CRX1_RCV_PKT_HEADER Register
struct CAMIF_CRX1_RCV_PKT_HEADER {
	unsigned int LatestECC:8;		// [31:24]
	unsigned int LatestWC1Data:8;		// [23:16]
	unsigned int LatestWC0Data:8;		// [15:8]
	unsigned int LatestVC:2;		// [7:6]
	unsigned int LatestDT:6;		// [5:0]
};
 // CRX1_VC0_FNLN_STAT Register
struct CAMIF_CRX1_VC0_FNLN_STAT {
	unsigned int VC0_FN:16;		// [31:16]
	unsigned int VC0_LN:16;		// [15:0]
};
 // CRX2_CDSIRX_CLKEN Register
struct CAMIF_CRX2_CDSIRX_CLKEN {
	unsigned int reserved:31;		// [31:1]
	unsigned int CDSIRXEn:1;		// [0]
};
 // CRX2_CDSIRX_CLKSEL Register
struct CAMIF_CRX2_CDSIRX_CLKSEL {
	unsigned int reserved:22;		// [31:10]
	unsigned int PPIHsRxClkSel:2;		// [9:8]
	unsigned int reserved2:7;		// [7:1]
	unsigned int PPIHsRxClkEn:1;		// [0]
};
 // CRX2_MODE_CONFIG Register
struct CAMIF_CRX2_MODE_CONFIG {
	unsigned int reserved:31;		// [31:1]
	unsigned int CSI2Mode:1;		// [0]
};
 // CRX2_CDSIRX_SYSTEM_INIT Register
struct CAMIF_CRX2_CDSIRX_SYSTEM_INIT {
	unsigned int reserved:31;		// [31:1]
	unsigned int SysInit:1;		// [0]
};
 // CRX2_LANE_ENABLE Register
struct CAMIF_CRX2_LANE_ENABLE {
	unsigned int reserved:27;		// [31:5]
	unsigned int CLaneEn:1;		// [4]
	unsigned int reserved2:1;		// [3]
	unsigned int DTLaneEn:3;		// [2:0]
};
 // CRX2_VC_ENABLE Register
struct CAMIF_CRX2_VC_ENABLE {
	unsigned int reserved:28;		// [31:4]
	unsigned int VC3En:1;		// [3]
	unsigned int VC2En:1;		// [2]
	unsigned int VC1En:1;		// [1]
	unsigned int VC0En:1;		// [0]
};
 // CRX2_CDSIRX_START Register
struct CAMIF_CRX2_CDSIRX_START {
	unsigned int reserved:31;		// [31:1]
	unsigned int CDSIRXStart:1;		// [0]
};
 // CRX2_LINE_INIT_COUNT Register
struct CAMIF_CRX2_LINE_INIT_COUNT {
	unsigned int reserved:16;		// [31:16]
	unsigned int LINEINITCNT:16;		// [15:0]
};
 // CRX2_HSRXTO_COUNT Register
struct CAMIF_CRX2_HSRXTO_COUNT {
	unsigned int HSToCnt:32;		// [31:0]
};
 // CRX2_FUNC_ENABLE Register
struct CAMIF_CRX2_FUNC_ENABLE {
	unsigned int DebugMdEn:1;		// [31]
	unsigned int reserved:6;		// [30:25]
	unsigned int reserved2:1;		// [23]
	unsigned int LNGPKTINTEn:1;		// [22]
	unsigned int SHTPKTINTEn:1;		// [21]
	unsigned int RXERRINTEn:1;		// [18]
	unsigned int LPRXSTATEEn:1;		// [16]
	unsigned int reserved3:1;		// [15]
	unsigned int LNGPKTINTSTATEEn:1;		// [14]
	unsigned int SHTPKTINTSTATEEn:1;		// [13]
	unsigned int RXERRINTSTATEEn:1;		// [10]
	unsigned int LPRXSTATEINTSTATEEn:1;		// [8]
	unsigned int reserved4:4;		// [7:4]
	unsigned int HSTOCntEn:1;		// [0]
};
 // CRX2_FUNC_MODE Register
struct CAMIF_CRX2_FUNC_MODE {
	unsigned int reserved:21;		// [31:11]
	unsigned int CntAutoRxMd:1;		// [10]
	unsigned int HsToAutoRxMd:1;		// [9]
	unsigned int LpToAutoRxMd:1;		// [8]
	unsigned int reserved2:6;		// [7:2]
	unsigned int BlankPktRcvEn:1;		// [1]
	unsigned int EoTpEn:1;		// [0]
};
 // CRX2_LPRX_STATE_INT_STAT Register
struct CAMIF_CRX2_LPRX_STATE_INT_STAT {
	unsigned int reserved:3;		// [31:29]
	unsigned int CLU1psExit:1;		// [28]
	unsigned int D3UlpsExit:1;		// [27]
	unsigned int D2UlpsExit:1;		// [26]
	unsigned int D1UlpsExit:1;		// [25]
	unsigned int D0UlpsExit:1;		// [24]
	unsigned int reserved2:3;		// [23:21]
	unsigned int CLUlpsEnter:1;		// [20]
	unsigned int D3UlpsEnter:1;		// [19]
	unsigned int D2UlpsEnter:1;		// [18]
	unsigned int D1UlpsEnter:1;		// [17]
	unsigned int D0UlpsEnter:1;		// [16]
	unsigned int reserved3:3;		// [15:13]
	unsigned int CLStopRise:1;		// [12]
	unsigned int D3StopRise:1;		// [11]
	unsigned int D2StopRise:1;		// [10]
	unsigned int D1StopRise:1;		// [9]
	unsigned int D0StopRise:1;		// [8]
	unsigned int reserved4:3;		// [7:5]
	unsigned int AutoCalDone:1;		// [4]
	unsigned int reserved5:1;		// [1]
	unsigned int LineInitDone:1;		// [0]
};
 // CRX2_LPRX_STATE_INT_MASK Register
struct CAMIF_CRX2_LPRX_STATE_INT_MASK {
	unsigned int reserved:3;		// [31:29]
	unsigned int MaskCLUlpsExit:1;		// [28]
	unsigned int MaskD3UlpsExit:1;		// [27]
	unsigned int MaskD2UlpsExit:1;		// [26]
	unsigned int MaskD1UlpsExit:1;		// [25]
	unsigned int MaskD0UlpsExit:1;		// [24]
	unsigned int reserved2:3;		// [23:21]
	unsigned int MaskCLUlpsEnter:1;		// [20]
	unsigned int MaskD3UlpsEnter:1;		// [19]
	unsigned int MaskD2UlpsEnter:1;		// [18]
	unsigned int MaskD1UlpsEnter:1;		// [17]
	unsigned int MaskD0UlpsEnter:1;		// [16]
	unsigned int reserved3:3;		// [15:13]
	unsigned int MaskCLStopRise:1;		// [12]
	unsigned int MaskD3StopRise:1;		// [11]
	unsigned int MaskD2StopRise:1;		// [10]
	unsigned int MaskD1StopRise:1;		// [9]
	unsigned int MaskD0StopRise:1;		// [8]
	unsigned int reserved4:3;		// [7:5]
	unsigned int MaskAutoCalDone:1;		// [4]
	unsigned int reserved5:1;		// [1]
	unsigned int MaskLineInitDone:1;		// [0]
};
 // CRX2_CDSIRX_INTERNAL_STAT Register
struct CAMIF_CRX2_CDSIRX_INTERNAL_STAT {
	unsigned int reserved:4;		// [31:28]
	unsigned int D3_HSRXBUSY:1;		// [27]
	unsigned int D3_LPRXBUSY:1;		// [26]
	unsigned int D2_HSRXBUSY:1;		// [25]
	unsigned int D2_LPRXBUSY:1;		// [24]
	unsigned int D1_HSRXBUSY:1;		// [23]
	unsigned int D1_LPRXBUSY:1;		// [22]
	unsigned int reserved2:1;		// [21]
	unsigned int D0_LPTXBUSY:1;		// [20]
	unsigned int D0_HSRXBUSY:1;		// [19]
	unsigned int D0_LPRXBUSY:1;		// [18]
	unsigned int CL_HSRXBUSY:1;		// [17]
	unsigned int CL_LPRXBUSY:1;		// [16]
	unsigned int reserved3:13;		// [15:3]
	unsigned int CDSI_RXBUSY:1;		// [0]
};
 // CRX2_RXERR_INT_STAT Register
struct CAMIF_CRX2_RXERR_INT_STAT {
	unsigned int ErrRxFifoOvf:1;		// [31]
	unsigned int reserved:1;		// [30]
	unsigned int ErrHsRxTo:1;		// [29]
	unsigned int reserved2:3;		// [28:26]
	unsigned int ErrLdSq:1;		// [25]
	unsigned int reserved3:8;		// [23:16]
	unsigned int reserved4:1;		// [14]
	unsigned int ErrInvalid:1;		// [13]
	unsigned int ErrVCID:1;		// [12]
	unsigned int ErrDataType:1;		// [11]
	unsigned int ErrChecksum:1;		// [10]
	unsigned int ErrEccDbl:1;		// [9]
	unsigned int ErrEccCrctd:1;		// [8]
	unsigned int reserved5:1;		// [7]
	unsigned int ErrCntrl:1;		// [6]
	unsigned int reserved6:1;		// [5]
	unsigned int ErrEsc:1;		// [3]
	unsigned int ErrSotSyncHs:1;		// [1]
	unsigned int ErrSotHs:1;		// [0]
};
 // CRX2_RXERR_INT_MASK Register
struct CAMIF_CRX2_RXERR_INT_MASK {
	unsigned int MaskErrRxFifoOvf:1;		// [31]
	unsigned int reserved:1;		// [30]
	unsigned int MaskErrHsRxTo:1;		// [29]
	unsigned int reserved2:3;		// [28:26]
	unsigned int MaskErrLdSq:1;		// [25]
	unsigned int reserved3:8;		// [23:16]
	unsigned int reserved4:1;		// [14]
	unsigned int MaskErrInvalid:1;		// [13]
	unsigned int MaskErrVCID:1;		// [12]
	unsigned int MaskErrDataType:1;		// [11]
	unsigned int MaskErrChecksum:1;		// [10]
	unsigned int MaskErrEccDbl:1;		// [9]
	unsigned int MaskErrEccCrctd:1;		// [8]
	unsigned int reserved5:1;		// [7]
	unsigned int MaskErrCntrl:1;		// [6]
	unsigned int reserved6:1;		// [5]
	unsigned int MaskErrEsc:1;		// [3]
	unsigned int MaskErrSotSyncHs:1;		// [1]
	unsigned int MaskErrSotHs:1;		// [0]
};
 // CRX2_ERR_STATUS Register
struct CAMIF_CRX2_ERR_STATUS {
	unsigned int reserved:16;		// [31:16]
	unsigned int reserved2:1;		// [14]
	unsigned int ErrInvalid:1;		// [13]
	unsigned int ErrVCID:1;		// [12]
	unsigned int ErrDataType:1;		// [11]
	unsigned int ErrChecksum:1;		// [10]
	unsigned int ErrEccDbl:1;		// [9]
	unsigned int ErrEccCrctd:1;		// [8]
	unsigned int ErrCntLp:1;		// [7]
	unsigned int ErrCntrl:1;		// [6]
	unsigned int ErrTo:1;		// [5]
	unsigned int ErrEsc:1;		// [3]
	unsigned int ErrSotSyncHs:1;		// [1]
	unsigned int ErrSotHs:1;		// [0]
};
 // CRX2_PPI_HSRX_CNTRL Register
struct CAMIF_CRX2_PPI_HSRX_CNTRL {
	unsigned int reserved:1;		// [31]
	unsigned int CLHSRXENFCTRL:1;		// [30]
	unsigned int reserved2:4;		// [29:26]
	unsigned int DTHSRXENRCTRL:2;		// [25:24]
	unsigned int reserved3:6;		// [23:18]
	unsigned int CLS_ATMR:2;		// [17:16]
	unsigned int reserved4:2;		// [15:14]
	unsigned int D3S_ATMR:2;		// [13:12]
	unsigned int reserved5:2;		// [11:10]
	unsigned int D2S_ATMR:2;		// [9:8]
	unsigned int reserved6:2;		// [7:6]
	unsigned int D1S_ATMR:2;		// [5:4]
	unsigned int reserved7:2;		// [3:2]
	unsigned int D0S_ATMR:2;		// [1:0]
};
 // CRX2_PPI_HSRX_COUNT Register
struct CAMIF_CRX2_PPI_HSRX_COUNT {
	unsigned int CLSETTLECnt:8;		// [31:24]
	unsigned int reserved:4;		// [23:20]
	unsigned int DTHSEXITCnt:4;		// [19:16]
	unsigned int HSSETTLECnt:8;		// [15:8]
	unsigned int DTCLRSIPOCnt:8;		// [7:0]
};
 // CRX2_PPI_DPHY_DLYCNTRL Register
struct CAMIF_CRX2_PPI_DPHY_DLYCNTRL {
	unsigned int reserved:12;		// [31:20]
	unsigned int CLS_DLYCNTRL:4;		// [19:16]
	unsigned int D3S_DLYCNTRL:4;		// [15:12]
	unsigned int D2S_DLYCNTRL:4;		// [11:8]
	unsigned int D1S_DLYCNTRL:4;		// [7:4]
	unsigned int D0S_DLYCNTRL:4;		// [3:0]
};
 // CRX2_PPI_DPHY_LPRX_THSLD Register
struct CAMIF_CRX2_PPI_DPHY_LPRX_THSLD {
	unsigned int reserved:22;		// [31:10]
	unsigned int CLS_CUTRSEL:1;		// [9]
	unsigned int CLS_LPRXVTHLOW:1;		// [8]
	unsigned int D3S_CUTRSEL:1;		// [7]
	unsigned int D3S_LPRXVTHLOW:1;		// [6]
	unsigned int D2S_CUTRSEL:1;		// [5]
	unsigned int D2S_LPRXVTHLOW:1;		// [4]
	unsigned int D1S_CUTRSEL:1;		// [3]
	unsigned int D1S_LPRXVTHLOW:1;		// [2]
	unsigned int D0S_CUTRSEL:1;		// [1]
	unsigned int D0S_LPRXVTHLOW:1;		// [0]
};
 // CRX2_PPI_DPHY_LPRXCALCNTRL Register
struct CAMIF_CRX2_PPI_DPHY_LPRXCALCNTRL {
	unsigned int reserved:8;		// [31:24]
	unsigned int AutoCalCnt:8;		// [23:16]
	unsigned int reserved2:9;		// [15:7]
	unsigned int LPRXCALTRIM:3;		// [6:4]
	unsigned int reserved3:2;		// [3:2]
	unsigned int LPRXCALRES:1;		// [1]
	unsigned int LPRXCALEN:1;		// [0]
};
 // CRX2_PPI_DPHY_LPRXAUTOCALST Register
struct CAMIF_CRX2_PPI_DPHY_LPRXAUTOCALST {
	unsigned int reserved:31;		// [31:1]
	unsigned int AutoCalStrt:1;		// [0]
};
 // CRX2_LANE_STATUS_HS Register
struct CAMIF_CRX2_LANE_STATUS_HS {
	unsigned int reserved:24;		// [31:8]
	unsigned int CLRxActiveHS:1;		// [7]
	unsigned int reserved2:3;		// [6:4]
	unsigned int D3RxActiveHS:1;		// [3]
	unsigned int D2RxActiveHS:1;		// [2]
	unsigned int D1RxActiveHS:1;		// [1]
	unsigned int D0RxActiveHS:1;		// [0]
};
 // CRX2_LANE_STATUS_LP Register
struct CAMIF_CRX2_LANE_STATUS_LP {
	unsigned int reserved:7;		// [31:25]
	unsigned int ClUlpsEsc:1;		// [23]
	unsigned int L0Direction:1;		// [22]
	unsigned int reserved2:2;		// [21:20]
	unsigned int L3UlpsEsc:1;		// [19]
	unsigned int L2UlpsEsc:1;		// [18]
	unsigned int L1UlpsEsc:1;		// [17]
	unsigned int L0UlpsEsc:1;		// [16]
	unsigned int ClUlpsActive:1;		// [15]
	unsigned int reserved3:3;		// [14:12]
	unsigned int L3UlpsActive:1;		// [11]
	unsigned int L2UlpsActive:1;		// [10]
	unsigned int L1UlpsActive:1;		// [9]
	unsigned int L0UlpsActive:1;		// [8]
	unsigned int ClStopState:1;		// [7]
	unsigned int reserved4:3;		// [6:4]
	unsigned int L3StopState:1;		// [3]
	unsigned int L2StopState:1;		// [2]
	unsigned int L1StopState:1;		// [1]
	unsigned int L0StopState:1;		// [0]
};
 // CRX2_VC0_SH_INT_STAT Register
struct CAMIF_CRX2_VC0_SH_INT_STAT {
	unsigned int reserved:16;		// [31:16]
	unsigned int VC0_GSP8:1;		// [15]
	unsigned int VC0_GSP7:1;		// [14]
	unsigned int VC0_GSP6:1;		// [13]
	unsigned int VC0_GSP5:1;		// [12]
	unsigned int VC0_GSP4:1;		// [11]
	unsigned int VC0_GSP3:1;		// [10]
	unsigned int VC0_GSP2:1;		// [9]
	unsigned int VC0_GSP1:1;		// [8]
	unsigned int reserved2:4;		// [7:4]
	unsigned int VC0_LE:1;		// [3]
	unsigned int VC0_LS:1;		// [2]
	unsigned int VC0_FE:1;		// [1]
	unsigned int VC0_FS:1;		// [0]
};
 // CRX2_VC0_SH_INT_MASK Register
struct CAMIF_CRX2_VC0_SH_INT_MASK {
	unsigned int reserved:16;		// [31:16]
	unsigned int MaskVC0_GSP8:1;		// [15]
	unsigned int MaskVC0_GSP7:1;		// [14]
	unsigned int MaskVC0_GSP6:1;		// [13]
	unsigned int MaskVC0_GSP5:1;		// [12]
	unsigned int MaskVC0_GSP4:1;		// [11]
	unsigned int MaskVC0_GSP3:1;		// [10]
	unsigned int MaskVC0_GSP2:1;		// [9]
	unsigned int MaskVC0_GSP1:1;		// [8]
	unsigned int reserved2:4;		// [7:4]
	unsigned int MaskVC0_LE:1;		// [3]
	unsigned int MaskVC0_LS:1;		// [2]
	unsigned int MaskVC0_FE:1;		// [1]
	unsigned int MaskVC0_FS:1;		// [0]
};
 // CRX2_VC0_LN0_INT_STAT Register
struct CAMIF_CRX2_VC0_LN0_INT_STAT {
	unsigned int reserved:2;		// [31:30]
	unsigned int VC0_RAW14:1;		// [29]
	unsigned int VC0_RAW12:1;		// [28]
	unsigned int VC0_RAW10:1;		// [27]
	unsigned int VC0_RAW8:1;		// [26]
	unsigned int VC0_RAW7:1;		// [25]
	unsigned int VC0_RAW6:1;		// [24]
	unsigned int reserved2:3;		// [23:21]
	unsigned int VC0_RGB888:1;		// [20]
	unsigned int VC0_RGB666:1;		// [19]
	unsigned int VC0_RGB565:1;		// [18]
	unsigned int VC0_RGB555:1;		// [17]
	unsigned int VC0_RGB444:1;		// [16]
	unsigned int VC0_YUV422_10:1;		// [15]
	unsigned int VC0_YUV422_8:1;		// [14]
	unsigned int VC0_YUV420_10_Chr:1;		// [13]
	unsigned int VC0_YUV420_8_Chr:1;		// [12]
	unsigned int reserved3:1;		// [11]
	unsigned int VC0_LegYUV420_8:1;		// [10]
	unsigned int VC0_YUV420_10:1;		// [9]
	unsigned int VC0_YUV420_8:1;		// [8]
	unsigned int reserved4:5;		// [7:3]
	unsigned int VC0_Embedded:1;		// [2]
	unsigned int VC0_Blank:1;		// [1]
	unsigned int VC0_Null:1;		// [0]
};
 // CRX2_VC0_LN1_INT_STAT Register
struct CAMIF_CRX2_VC0_LN1_INT_STAT {
	unsigned int reserved:24;		// [31:8]
	unsigned int VC0_define8:1;		// [7]
	unsigned int VC0_define7:1;		// [6]
	unsigned int VC0_define6:1;		// [5]
	unsigned int VC0_define5:1;		// [4]
	unsigned int VC0_define4:1;		// [3]
	unsigned int VC0_define3:1;		// [2]
	unsigned int VC0_define2:1;		// [1]
	unsigned int VC0_define1:1;		// [0]
};
 // CRX2_VC0_LN0_INT_MASK Register
struct CAMIF_CRX2_VC0_LN0_INT_MASK {
	unsigned int reserved:2;		// [31:30]
	unsigned int MaskVC0_RAW14:1;		// [29]
	unsigned int MaskVC0_RAW12:1;		// [28]
	unsigned int MaskVC0_RAW10:1;		// [27]
	unsigned int MaskVC0_RAW8:1;		// [26]
	unsigned int MaskVC0_RAW7:1;		// [25]
	unsigned int MaskVC0_RAW6:1;		// [24]
	unsigned int reserved2:3;		// [23:21]
	unsigned int MaskVC0_RGB888:1;		// [20]
	unsigned int MaskVC0_RGB666:1;		// [19]
	unsigned int MaskVC0_RGB565:1;		// [18]
	unsigned int MaskVC0_RGB555:1;		// [17]
	unsigned int MaskVC0_RGB444:1;		// [16]
	unsigned int MaskVC0_YUV422_10:1;		// [15]
	unsigned int MaskVC0_YUV422_8:1;		// [14]
	unsigned int MaskVC0_YUV420_10_Chr:1;		// [13]
	unsigned int MaskVC0_YUV420_8_Chr:1;		// [12]
	unsigned int reserved3:1;		// [11]
	unsigned int MaskVC0_LegYUV420_8:1;		// [10]
	unsigned int MaskVC0_YUV420_10:1;		// [9]
	unsigned int MaskVC0_YUV420_8:1;		// [8]
	unsigned int reserved4:5;		// [7:3]
	unsigned int MaskVC0_Embedded:1;		// [2]
	unsigned int MaskVC0_Blank:1;		// [1]
	unsigned int MaskVC0_Null:1;		// [0]
};
 // CRX2_VC0_LN1_INT_MASK Register
struct CAMIF_CRX2_VC0_LN1_INT_MASK {
	unsigned int reserved:24;		// [31:8]
	unsigned int MaskVC0_define8:1;		// [7]
	unsigned int MaskVC0_define7:1;		// [6]
	unsigned int MaskVC0_define6:1;		// [5]
	unsigned int MaskVC0_define5:1;		// [4]
	unsigned int MaskVC0_define4:1;		// [3]
	unsigned int MaskVC0_define3:1;		// [2]
	unsigned int MaskVC0_define2:1;		// [1]
	unsigned int MaskVC0_define1:1;		// [0]
};
 // CRX2_RCV_PKT_HEADER Register
struct CAMIF_CRX2_RCV_PKT_HEADER {
	unsigned int LatestECC:8;		// [31:24]
	unsigned int LatestWC1Data:8;		// [23:16]
	unsigned int LatestWC0Data:8;		// [15:8]
	unsigned int LatestVC:2;		// [7:6]
	unsigned int LatestDT:6;		// [5:0]
};
 // CRX2_VC0_FNLN_STAT Register
struct CAMIF_CRX2_VC0_FNLN_STAT {
	unsigned int VC0_FN:16;		// [31:16]
	unsigned int VC0_LN:16;		// [15:0]
};
 // CRX3_CDSIRX_CLKEN Register
struct CAMIF_CRX3_CDSIRX_CLKEN {
	unsigned int reserved:31;		// [31:1]
	unsigned int CDSIRXEn:1;		// [0]
};
 // CRX3_CDSIRX_CLKSEL Register
struct CAMIF_CRX3_CDSIRX_CLKSEL {
	unsigned int reserved:22;		// [31:10]
	unsigned int PPIHsRxClkSel:2;		// [9:8]
	unsigned int reserved2:7;		// [7:1]
	unsigned int PPIHsRxClkEn:1;		// [0]
};
 // CRX3_MODE_CONFIG Register
struct CAMIF_CRX3_MODE_CONFIG {
	unsigned int reserved:31;		// [31:1]
	unsigned int CSI2Mode:1;		// [0]
};
 // CRX3_CDSIRX_SYSTEM_INIT Register
struct CAMIF_CRX3_CDSIRX_SYSTEM_INIT {
	unsigned int reserved:31;		// [31:1]
	unsigned int SysInit:1;		// [0]
};
 // CRX3_LANE_ENABLE Register
struct CAMIF_CRX3_LANE_ENABLE {
	unsigned int reserved:27;		// [31:5]
	unsigned int CLaneEn:1;		// [4]
	unsigned int reserved2:1;		// [3]
	unsigned int DTLaneEn:3;		// [2:0]
};
 // CRX3_VC_ENABLE Register
struct CAMIF_CRX3_VC_ENABLE {
	unsigned int reserved:28;		// [31:4]
	unsigned int VC3En:1;		// [3]
	unsigned int VC2En:1;		// [2]
	unsigned int VC1En:1;		// [1]
	unsigned int VC0En:1;		// [0]
};
 // CRX3_CDSIRX_START Register
struct CAMIF_CRX3_CDSIRX_START {
	unsigned int reserved:31;		// [31:1]
	unsigned int CDSIRXStart:1;		// [0]
};
 // CRX3_LINE_INIT_COUNT Register
struct CAMIF_CRX3_LINE_INIT_COUNT {
	unsigned int reserved:16;		// [31:16]
	unsigned int LINEINITCNT:16;		// [15:0]
};
 // CRX3_HSRXTO_COUNT Register
struct CAMIF_CRX3_HSRXTO_COUNT {
	unsigned int HSToCnt:32;		// [31:0]
};
 // CRX3_FUNC_ENABLE Register
struct CAMIF_CRX3_FUNC_ENABLE {
	unsigned int DebugMdEn:1;		// [31]
	unsigned int reserved:6;		// [30:25]
	unsigned int reserved2:1;		// [23]
	unsigned int LNGPKTINTEn:1;		// [22]
	unsigned int SHTPKTINTEn:1;		// [21]
	unsigned int RXERRINTEn:1;		// [18]
	unsigned int LPRXSTATEEn:1;		// [16]
	unsigned int reserved3:1;		// [15]
	unsigned int LNGPKTINTSTATEEn:1;		// [14]
	unsigned int SHTPKTINTSTATEEn:1;		// [13]
	unsigned int RXERRINTSTATEEn:1;		// [10]
	unsigned int LPRXSTATEINTSTATEEn:1;		// [8]
	unsigned int reserved4:4;		// [7:4]
	unsigned int HSTOCntEn:1;		// [0]
};
 // CRX3_FUNC_MODE Register
struct CAMIF_CRX3_FUNC_MODE {
	unsigned int reserved:21;		// [31:11]
	unsigned int CntAutoRxMd:1;		// [10]
	unsigned int HsToAutoRxMd:1;		// [9]
	unsigned int LpToAutoRxMd:1;		// [8]
	unsigned int reserved2:6;		// [7:2]
	unsigned int BlankPktRcvEn:1;		// [1]
	unsigned int EoTpEn:1;		// [0]
};
 // CRX3_LPRX_STATE_INT_STAT Register
struct CAMIF_CRX3_LPRX_STATE_INT_STAT {
	unsigned int reserved:3;		// [31:29]
	unsigned int CLU1psExit:1;		// [28]
	unsigned int D3UlpsExit:1;		// [27]
	unsigned int D2UlpsExit:1;		// [26]
	unsigned int D1UlpsExit:1;		// [25]
	unsigned int D0UlpsExit:1;		// [24]
	unsigned int reserved2:3;		// [23:21]
	unsigned int CLUlpsEnter:1;		// [20]
	unsigned int D3UlpsEnter:1;		// [19]
	unsigned int D2UlpsEnter:1;		// [18]
	unsigned int D1UlpsEnter:1;		// [17]
	unsigned int D0UlpsEnter:1;		// [16]
	unsigned int reserved3:3;		// [15:13]
	unsigned int CLStopRise:1;		// [12]
	unsigned int D3StopRise:1;		// [11]
	unsigned int D2StopRise:1;		// [10]
	unsigned int D1StopRise:1;		// [9]
	unsigned int D0StopRise:1;		// [8]
	unsigned int reserved4:3;		// [7:5]
	unsigned int AutoCalDone:1;		// [4]
	unsigned int reserved5:1;		// [1]
	unsigned int LineInitDone:1;		// [0]
};
 // CRX3_LPRX_STATE_INT_MASK Register
struct CAMIF_CRX3_LPRX_STATE_INT_MASK {
	unsigned int reserved:3;		// [31:29]
	unsigned int MaskCLUlpsExit:1;		// [28]
	unsigned int MaskD3UlpsExit:1;		// [27]
	unsigned int MaskD2UlpsExit:1;		// [26]
	unsigned int MaskD1UlpsExit:1;		// [25]
	unsigned int MaskD0UlpsExit:1;		// [24]
	unsigned int reserved2:3;		// [23:21]
	unsigned int MaskCLUlpsEnter:1;		// [20]
	unsigned int MaskD3UlpsEnter:1;		// [19]
	unsigned int MaskD2UlpsEnter:1;		// [18]
	unsigned int MaskD1UlpsEnter:1;		// [17]
	unsigned int MaskD0UlpsEnter:1;		// [16]
	unsigned int reserved3:3;		// [15:13]
	unsigned int MaskCLStopRise:1;		// [12]
	unsigned int MaskD3StopRise:1;		// [11]
	unsigned int MaskD2StopRise:1;		// [10]
	unsigned int MaskD1StopRise:1;		// [9]
	unsigned int MaskD0StopRise:1;		// [8]
	unsigned int reserved4:3;		// [7:5]
	unsigned int MaskAutoCalDone:1;		// [4]
	unsigned int reserved5:1;		// [1]
	unsigned int MaskLineInitDone:1;		// [0]
};
 // CRX3_CDSIRX_INTERNAL_STAT Register
struct CAMIF_CRX3_CDSIRX_INTERNAL_STAT {
	unsigned int reserved:4;		// [31:28]
	unsigned int D3_HSRXBUSY:1;		// [27]
	unsigned int D3_LPRXBUSY:1;		// [26]
	unsigned int D2_HSRXBUSY:1;		// [25]
	unsigned int D2_LPRXBUSY:1;		// [24]
	unsigned int D1_HSRXBUSY:1;		// [23]
	unsigned int D1_LPRXBUSY:1;		// [22]
	unsigned int reserved2:1;		// [21]
	unsigned int D0_LPTXBUSY:1;		// [20]
	unsigned int D0_HSRXBUSY:1;		// [19]
	unsigned int D0_LPRXBUSY:1;		// [18]
	unsigned int CL_HSRXBUSY:1;		// [17]
	unsigned int CL_LPRXBUSY:1;		// [16]
	unsigned int reserved3:13;		// [15:3]
	unsigned int CDSI_RXBUSY:1;		// [0]
};
 // CRX3_RXERR_INT_STAT Register
struct CAMIF_CRX3_RXERR_INT_STAT {
	unsigned int ErrRxFifoOvf:1;		// [31]
	unsigned int reserved:1;		// [30]
	unsigned int ErrHsRxTo:1;		// [29]
	unsigned int reserved2:3;		// [28:26]
	unsigned int ErrLdSq:1;		// [25]
	unsigned int reserved3:8;		// [23:16]
	unsigned int reserved4:1;		// [14]
	unsigned int ErrInvalid:1;		// [13]
	unsigned int ErrVCID:1;		// [12]
	unsigned int ErrDataType:1;		// [11]
	unsigned int ErrChecksum:1;		// [10]
	unsigned int ErrEccDbl:1;		// [9]
	unsigned int ErrEccCrctd:1;		// [8]
	unsigned int reserved5:1;		// [7]
	unsigned int ErrCntrl:1;		// [6]
	unsigned int reserved6:1;		// [5]
	unsigned int ErrEsc:1;		// [3]
	unsigned int ErrSotSyncHs:1;		// [1]
	unsigned int ErrSotHs:1;		// [0]
};
 // CRX3_RXERR_INT_MASK Register
struct CAMIF_CRX3_RXERR_INT_MASK {
	unsigned int MaskErrRxFifoOvf:1;		// [31]
	unsigned int reserved:1;		// [30]
	unsigned int MaskErrHsRxTo:1;		// [29]
	unsigned int reserved2:3;		// [28:26]
	unsigned int MaskErrLdSq:1;		// [25]
	unsigned int reserved3:8;		// [23:16]
	unsigned int reserved4:1;		// [14]
	unsigned int MaskErrInvalid:1;		// [13]
	unsigned int MaskErrVCID:1;		// [12]
	unsigned int MaskErrDataType:1;		// [11]
	unsigned int MaskErrChecksum:1;		// [10]
	unsigned int MaskErrEccDbl:1;		// [9]
	unsigned int MaskErrEccCrctd:1;		// [8]
	unsigned int reserved5:1;		// [7]
	unsigned int MaskErrCntrl:1;		// [6]
	unsigned int reserved6:1;		// [5]
	unsigned int MaskErrEsc:1;		// [3]
	unsigned int MaskErrSotSyncHs:1;		// [1]
	unsigned int MaskErrSotHs:1;		// [0]
};
 // CRX3_ERR_STATUS Register
struct CAMIF_CRX3_ERR_STATUS {
	unsigned int reserved:16;		// [31:16]
	unsigned int reserved2:1;		// [14]
	unsigned int ErrInvalid:1;		// [13]
	unsigned int ErrVCID:1;		// [12]
	unsigned int ErrDataType:1;		// [11]
	unsigned int ErrChecksum:1;		// [10]
	unsigned int ErrEccDbl:1;		// [9]
	unsigned int ErrEccCrctd:1;		// [8]
	unsigned int ErrCntLp:1;		// [7]
	unsigned int ErrCntrl:1;		// [6]
	unsigned int ErrTo:1;		// [5]
	unsigned int ErrEsc:1;		// [3]
	unsigned int ErrSotSyncHs:1;		// [1]
	unsigned int ErrSotHs:1;		// [0]
};
 // CRX3_PPI_HSRX_CNTRL Register
struct CAMIF_CRX3_PPI_HSRX_CNTRL {
	unsigned int reserved:1;		// [31]
	unsigned int CLHSRXENFCTRL:1;		// [30]
	unsigned int reserved2:4;		// [29:26]
	unsigned int DTHSRXENRCTRL:2;		// [25:24]
	unsigned int reserved3:6;		// [23:18]
	unsigned int CLS_ATMR:2;		// [17:16]
	unsigned int reserved4:2;		// [15:14]
	unsigned int D3S_ATMR:2;		// [13:12]
	unsigned int reserved5:2;		// [11:10]
	unsigned int D2S_ATMR:2;		// [9:8]
	unsigned int reserved6:2;		// [7:6]
	unsigned int D1S_ATMR:2;		// [5:4]
	unsigned int reserved7:2;		// [3:2]
	unsigned int D0S_ATMR:2;		// [1:0]
};
 // CRX3_PPI_HSRX_COUNT Register
struct CAMIF_CRX3_PPI_HSRX_COUNT {
	unsigned int CLSETTLECnt:8;		// [31:24]
	unsigned int reserved:4;		// [23:20]
	unsigned int DTHSEXITCnt:4;		// [19:16]
	unsigned int HSSETTLECnt:8;		// [15:8]
	unsigned int DTCLRSIPOCnt:8;		// [7:0]
};
 // CRX3_PPI_DPHY_DLYCNTRL Register
struct CAMIF_CRX3_PPI_DPHY_DLYCNTRL {
	unsigned int reserved:12;		// [31:20]
	unsigned int CLS_DLYCNTRL:4;		// [19:16]
	unsigned int D3S_DLYCNTRL:4;		// [15:12]
	unsigned int D2S_DLYCNTRL:4;		// [11:8]
	unsigned int D1S_DLYCNTRL:4;		// [7:4]
	unsigned int D0S_DLYCNTRL:4;		// [3:0]
};
 // CRX3_PPI_DPHY_LPRX_THSLD Register
struct CAMIF_CRX3_PPI_DPHY_LPRX_THSLD {
	unsigned int reserved:22;		// [31:10]
	unsigned int CLS_CUTRSEL:1;		// [9]
	unsigned int CLS_LPRXVTHLOW:1;		// [8]
	unsigned int D3S_CUTRSEL:1;		// [7]
	unsigned int D3S_LPRXVTHLOW:1;		// [6]
	unsigned int D2S_CUTRSEL:1;		// [5]
	unsigned int D2S_LPRXVTHLOW:1;		// [4]
	unsigned int D1S_CUTRSEL:1;		// [3]
	unsigned int D1S_LPRXVTHLOW:1;		// [2]
	unsigned int D0S_CUTRSEL:1;		// [1]
	unsigned int D0S_LPRXVTHLOW:1;		// [0]
};
 // CRX3_PPI_DPHY_LPRXCALCNTRL Register
struct CAMIF_CRX3_PPI_DPHY_LPRXCALCNTRL {
	unsigned int reserved:8;		// [31:24]
	unsigned int AutoCalCnt:8;		// [23:16]
	unsigned int reserved2:9;		// [15:7]
	unsigned int LPRXCALTRIM:3;		// [6:4]
	unsigned int reserved3:2;		// [3:2]
	unsigned int LPRXCALRES:1;		// [1]
	unsigned int LPRXCALEN:1;		// [0]
};
 // CRX3_PPI_DPHY_LPRXAUTOCALST Register
struct CAMIF_CRX3_PPI_DPHY_LPRXAUTOCALST {
	unsigned int reserved:31;		// [31:1]
	unsigned int AutoCalStrt:1;		// [0]
};
 // CRX3_LANE_STATUS_HS Register
struct CAMIF_CRX3_LANE_STATUS_HS {
	unsigned int reserved:24;		// [31:8]
	unsigned int CLRxActiveHS:1;		// [7]
	unsigned int reserved2:3;		// [6:4]
	unsigned int D3RxActiveHS:1;		// [3]
	unsigned int D2RxActiveHS:1;		// [2]
	unsigned int D1RxActiveHS:1;		// [1]
	unsigned int D0RxActiveHS:1;		// [0]
};
 // CRX3_LANE_STATUS_LP Register
struct CAMIF_CRX3_LANE_STATUS_LP {
	unsigned int reserved:7;		// [31:25]
	unsigned int ClUlpsEsc:1;		// [23]
	unsigned int L0Direction:1;		// [22]
	unsigned int reserved2:2;		// [21:20]
	unsigned int L3UlpsEsc:1;		// [19]
	unsigned int L2UlpsEsc:1;		// [18]
	unsigned int L1UlpsEsc:1;		// [17]
	unsigned int L0UlpsEsc:1;		// [16]
	unsigned int ClUlpsActive:1;		// [15]
	unsigned int reserved3:3;		// [14:12]
	unsigned int L3UlpsActive:1;		// [11]
	unsigned int L2UlpsActive:1;		// [10]
	unsigned int L1UlpsActive:1;		// [9]
	unsigned int L0UlpsActive:1;		// [8]
	unsigned int ClStopState:1;		// [7]
	unsigned int reserved4:3;		// [6:4]
	unsigned int L3StopState:1;		// [3]
	unsigned int L2StopState:1;		// [2]
	unsigned int L1StopState:1;		// [1]
	unsigned int L0StopState:1;		// [0]
};
 // CRX3_VC0_SH_INT_STAT Register
struct CAMIF_CRX3_VC0_SH_INT_STAT {
	unsigned int reserved:16;		// [31:16]
	unsigned int VC0_GSP8:1;		// [15]
	unsigned int VC0_GSP7:1;		// [14]
	unsigned int VC0_GSP6:1;		// [13]
	unsigned int VC0_GSP5:1;		// [12]
	unsigned int VC0_GSP4:1;		// [11]
	unsigned int VC0_GSP3:1;		// [10]
	unsigned int VC0_GSP2:1;		// [9]
	unsigned int VC0_GSP1:1;		// [8]
	unsigned int reserved2:4;		// [7:4]
	unsigned int VC0_LE:1;		// [3]
	unsigned int VC0_LS:1;		// [2]
	unsigned int VC0_FE:1;		// [1]
	unsigned int VC0_FS:1;		// [0]
};
 // CRX3_VC0_SH_INT_MASK Register
struct CAMIF_CRX3_VC0_SH_INT_MASK {
	unsigned int reserved:16;		// [31:16]
	unsigned int MaskVC0_GSP8:1;		// [15]
	unsigned int MaskVC0_GSP7:1;		// [14]
	unsigned int MaskVC0_GSP6:1;		// [13]
	unsigned int MaskVC0_GSP5:1;		// [12]
	unsigned int MaskVC0_GSP4:1;		// [11]
	unsigned int MaskVC0_GSP3:1;		// [10]
	unsigned int MaskVC0_GSP2:1;		// [9]
	unsigned int MaskVC0_GSP1:1;		// [8]
	unsigned int reserved2:4;		// [7:4]
	unsigned int MaskVC0_LE:1;		// [3]
	unsigned int MaskVC0_LS:1;		// [2]
	unsigned int MaskVC0_FE:1;		// [1]
	unsigned int MaskVC0_FS:1;		// [0]
};
 // CRX3_VC0_LN0_INT_STAT Register
struct CAMIF_CRX3_VC0_LN0_INT_STAT {
	unsigned int reserved:2;		// [31:30]
	unsigned int VC0_RAW14:1;		// [29]
	unsigned int VC0_RAW12:1;		// [28]
	unsigned int VC0_RAW10:1;		// [27]
	unsigned int VC0_RAW8:1;		// [26]
	unsigned int VC0_RAW7:1;		// [25]
	unsigned int VC0_RAW6:1;		// [24]
	unsigned int reserved2:3;		// [23:21]
	unsigned int VC0_RGB888:1;		// [20]
	unsigned int VC0_RGB666:1;		// [19]
	unsigned int VC0_RGB565:1;		// [18]
	unsigned int VC0_RGB555:1;		// [17]
	unsigned int VC0_RGB444:1;		// [16]
	unsigned int VC0_YUV422_10:1;		// [15]
	unsigned int VC0_YUV422_8:1;		// [14]
	unsigned int VC0_YUV420_10_Chr:1;		// [13]
	unsigned int VC0_YUV420_8_Chr:1;		// [12]
	unsigned int reserved3:1;		// [11]
	unsigned int VC0_LegYUV420_8:1;		// [10]
	unsigned int VC0_YUV420_10:1;		// [9]
	unsigned int VC0_YUV420_8:1;		// [8]
	unsigned int reserved4:5;		// [7:3]
	unsigned int VC0_Embedded:1;		// [2]
	unsigned int VC0_Blank:1;		// [1]
	unsigned int VC0_Null:1;		// [0]
};
 // CRX3_VC0_LN1_INT_STAT Register
struct CAMIF_CRX3_VC0_LN1_INT_STAT {
	unsigned int reserved:24;		// [31:8]
	unsigned int VC0_define8:1;		// [7]
	unsigned int VC0_define7:1;		// [6]
	unsigned int VC0_define6:1;		// [5]
	unsigned int VC0_define5:1;		// [4]
	unsigned int VC0_define4:1;		// [3]
	unsigned int VC0_define3:1;		// [2]
	unsigned int VC0_define2:1;		// [1]
	unsigned int VC0_define1:1;		// [0]
};
 // CRX3_VC0_LN0_INT_MASK Register
struct CAMIF_CRX3_VC0_LN0_INT_MASK {
	unsigned int reserved:2;		// [31:30]
	unsigned int MaskVC0_RAW14:1;		// [29]
	unsigned int MaskVC0_RAW12:1;		// [28]
	unsigned int MaskVC0_RAW10:1;		// [27]
	unsigned int MaskVC0_RAW8:1;		// [26]
	unsigned int MaskVC0_RAW7:1;		// [25]
	unsigned int MaskVC0_RAW6:1;		// [24]
	unsigned int reserved2:3;		// [23:21]
	unsigned int MaskVC0_RGB888:1;		// [20]
	unsigned int MaskVC0_RGB666:1;		// [19]
	unsigned int MaskVC0_RGB565:1;		// [18]
	unsigned int MaskVC0_RGB555:1;		// [17]
	unsigned int MaskVC0_RGB444:1;		// [16]
	unsigned int MaskVC0_YUV422_10:1;		// [15]
	unsigned int MaskVC0_YUV422_8:1;		// [14]
	unsigned int MaskVC0_YUV420_10_Chr:1;		// [13]
	unsigned int MaskVC0_YUV420_8_Chr:1;		// [12]
	unsigned int reserved3:1;		// [11]
	unsigned int MaskVC0_LegYUV420_8:1;		// [10]
	unsigned int MaskVC0_YUV420_10:1;		// [9]
	unsigned int MaskVC0_YUV420_8:1;		// [8]
	unsigned int reserved4:5;		// [7:3]
	unsigned int MaskVC0_Embedded:1;		// [2]
	unsigned int MaskVC0_Blank:1;		// [1]
	unsigned int MaskVC0_Null:1;		// [0]
};
 // CRX3_VC0_LN1_INT_MASK Register
struct CAMIF_CRX3_VC0_LN1_INT_MASK {
	unsigned int reserved:24;		// [31:8]
	unsigned int MaskVC0_define8:1;		// [7]
	unsigned int MaskVC0_define7:1;		// [6]
	unsigned int MaskVC0_define6:1;		// [5]
	unsigned int MaskVC0_define5:1;		// [4]
	unsigned int MaskVC0_define4:1;		// [3]
	unsigned int MaskVC0_define3:1;		// [2]
	unsigned int MaskVC0_define2:1;		// [1]
	unsigned int MaskVC0_define1:1;		// [0]
};
 // CRX3_RCV_PKT_HEADER Register
struct CAMIF_CRX3_RCV_PKT_HEADER {
	unsigned int LatestECC:8;		// [31:24]
	unsigned int LatestWC1Data:8;		// [23:16]
	unsigned int LatestWC0Data:8;		// [15:8]
	unsigned int LatestVC:2;		// [7:6]
	unsigned int LatestDT:6;		// [5:0]
};
 // CRX3_VC0_FNLN_STAT Register
struct CAMIF_CRX3_VC0_FNLN_STAT {
	unsigned int VC0_FN:16;		// [31:16]
	unsigned int VC0_LN:16;		// [15:0]
};
 // CDF0_ENABLE Register
struct CAMIF_CDF0_ENABLE {
	unsigned int reserved:31;		// [31:1]
	unsigned int enable:1;		// [0]
};
 // CDF0_SKIP_FRAME Register
struct CAMIF_CDF0_SKIP_FRAME {
	unsigned int reserved:31;		// [31:1]
	unsigned int skip_frame:1;		// [0]
};
 // CDF0_SELECT_INPUT_PORT Register
struct CAMIF_CDF0_SELECT_INPUT_PORT {
	unsigned int reserved:31;		// [31:1]
	unsigned int select_input_port:1;		// [0]
};
 // CDF0_CNTRL_INPUT_HEIGHT Register
struct CAMIF_CDF0_CNTRL_INPUT_HEIGHT {
	unsigned int reserved:18;		// [31:14]
	unsigned int input_height:14;		// [13:0]
};
 // CDF0_CNTRL_INPUT_WIDTH Register
struct CAMIF_CDF0_CNTRL_INPUT_WIDTH {
	unsigned int reserved:18;		// [31:14]
	unsigned int input_width:14;		// [13:0]
};
 // CDF0_CNTRL_CONVERSION Register
struct CAMIF_CDF0_CNTRL_CONVERSION {
	unsigned int reserved:30;		// [31:2]
	unsigned int color_format_conversion:2;		// [1:0]
};
 // CDF0_CNTRL_MEMORY_OUTPUT Register
struct CAMIF_CDF0_CNTRL_MEMORY_OUTPUT {
	unsigned int reserved:15;		// [31:17]
	unsigned int endian:1;		// [16]
	unsigned int reserved2:7;		// [15:9]
	unsigned int swap_yc_or_cbcr:1;		// [8]
	unsigned int reserved3:6;		// [7:2]
	unsigned int memory_output_format:2;		// [1:0]
};
 // CDF0_INT_STAT Register
struct CAMIF_CDF0_INT_STAT {
	unsigned int reserved:20;		// [31:12]
	unsigned int vsync:1;		// [11]
	unsigned int hsync_n:1;		// [10]
	unsigned int frame_transfer_finished:1;		// [9]
	unsigned int color_format_conversion_error:1;		// [8]
	unsigned int memory_output_error:1;		// [7]
	unsigned int y_bus_congestion_error:1;		// [6]
	unsigned int cb_bus_congestion_error:1;		// [5]
	unsigned int cr_bus_congestion_error:1;		// [4]
	unsigned int input_color_format_error:1;		// [3]
	unsigned int input_height_error:1;		// [2]
	unsigned int input_width_error:1;		// [1]
	unsigned int no_frame_end_error:1;		// [0]
};
 // CDF0_INT_MASK Register
struct CAMIF_CDF0_INT_MASK {
	unsigned int reserved:20;		// [31:12]
	unsigned int mask_vsync:1;		// [11]
	unsigned int mask_hsync_n:1;		// [10]
	unsigned int mask_frame_transfer_finished:1;		// [9]
	unsigned int mask_color_format_conversion_error:1;		// [8]
	unsigned int mask_memory_output_error:1;		// [7]
	unsigned int mask_y_bus_congestion_error:1;		// [6]
	unsigned int mask_cb_bus_congestion_error:1;		// [5]
	unsigned int mask_cr_bus_congestion_error:1;		// [4]
	unsigned int mask_input_color_format_error:1;		// [3]
	unsigned int mask_input_height_error:1;		// [2]
	unsigned int mask_input_width_error:1;		// [1]
	unsigned int mask_no_frame_end_error:1;		// [0]
};
 // CDF0_INT_HSYNCN_LINENUM Register
struct CAMIF_CDF0_INT_HSYNCN_LINENUM {
	unsigned int reserved:18;		// [31:14]
	unsigned int linenum:14;		// [13:0]
};
 // CDF0_RECEIVED_COLOR_FORMAT Register
struct CAMIF_CDF0_RECEIVED_COLOR_FORMAT {
	unsigned int reserved:26;		// [31:6]
	unsigned int received_color_format:6;		// [5:0]
};
 // CDF0_RECEIVED_IMAGE_SIZE Register
struct CAMIF_CDF0_RECEIVED_IMAGE_SIZE {
	unsigned int reserved:2;		// [31:30]
	unsigned int received_image_height:14;		// [29:16]
	unsigned int received_image_width:16;		// [15:0]
};
 // CDF0_SKIP_FRAME_DB Register
struct CAMIF_CDF0_SKIP_FRAME_DB {
	unsigned int reserved:31;		// [31:1]
	unsigned int skip_frame_db:1;		// [0]
};
 // CDF0_SELECT_INPUT_PORT_DB Register
struct CAMIF_CDF0_SELECT_INPUT_PORT_DB {
	unsigned int reserved:31;		// [31:1]
	unsigned int select_input_port_db:1;		// [0]
};
 // CDF0_CNTRL_INPUT_HEIGHT_DB Register
struct CAMIF_CDF0_CNTRL_INPUT_HEIGHT_DB {
	unsigned int reserved:18;		// [31:14]
	unsigned int input_height_db:14;		// [13:0]
};
 // CDF0_CNTRL_INPUT_WIDTH_DB Register
struct CAMIF_CDF0_CNTRL_INPUT_WIDTH_DB {
	unsigned int reserved:18;		// [31:14]
	unsigned int input_width_db:14;		// [13:0]
};
 // CDF0_CNTRL_CONVERSION_DB Register
struct CAMIF_CDF0_CNTRL_CONVERSION_DB {
	unsigned int reserved:30;		// [31:2]
	unsigned int color_format_conversion_db:2;		// [1:0]
};
 // CDF0_CNTRL_MEMORY_OUTPUT_DB Register
struct CAMIF_CDF0_CNTRL_MEMORY_OUTPUT_DB {
	unsigned int reserved:15;		// [31:17]
	unsigned int endian_db:1;		// [16]
	unsigned int reserved2:7;		// [15:9]
	unsigned int swap_yc_or_cbcr_db:1;		// [8]
	unsigned int reserved3:6;		// [7:2]
	unsigned int memory_output_format_db:2;		// [1:0]
};
 // CDF0_INT_HSYNCN_LINENUM_DB Register
struct CAMIF_CDF0_INT_HSYNCN_LINENUM_DB {
	unsigned int reserved:18;		// [31:14]
	unsigned int linenum_db:14;		// [13:0]
};
 // CDF1_ENABLE Register
struct CAMIF_CDF1_ENABLE {
	unsigned int reserved:31;		// [31:1]
	unsigned int enable:1;		// [0]
};
 // CDF1_SKIP_FRAME Register
struct CAMIF_CDF1_SKIP_FRAME {
	unsigned int reserved:31;		// [31:1]
	unsigned int skip_frame:1;		// [0]
};
 // CDF1_SELECT_INPUT_PORT Register
struct CAMIF_CDF1_SELECT_INPUT_PORT {
	unsigned int reserved:31;		// [31:1]
	unsigned int select_input_port:1;		// [0]
};
 // CDF1_CNTRL_INPUT_HEIGHT Register
struct CAMIF_CDF1_CNTRL_INPUT_HEIGHT {
	unsigned int reserved:18;		// [31:14]
	unsigned int input_height:14;		// [13:0]
};
 // CDF1_CNTRL_INPUT_WIDTH Register
struct CAMIF_CDF1_CNTRL_INPUT_WIDTH {
	unsigned int reserved:18;		// [31:14]
	unsigned int input_width:14;		// [13:0]
};
 // CDF1_CNTRL_CONVERSION Register
struct CAMIF_CDF1_CNTRL_CONVERSION {
	unsigned int reserved:30;		// [31:2]
	unsigned int color_format_conversion:2;		// [1:0]
};
 // CDF1_CNTRL_MEMORY_OUTPUT Register
struct CAMIF_CDF1_CNTRL_MEMORY_OUTPUT {
	unsigned int reserved:15;		// [31:17]
	unsigned int endian:1;		// [16]
	unsigned int reserved2:7;		// [15:9]
	unsigned int swap_yc_or_cbcr:1;		// [8]
	unsigned int reserved3:6;		// [7:2]
	unsigned int memory_output_format:2;		// [1:0]
};
 // CDF1_INT_STAT Register
struct CAMIF_CDF1_INT_STAT {
	unsigned int reserved:20;		// [31:12]
	unsigned int vsync:1;		// [11]
	unsigned int hsync_n:1;		// [10]
	unsigned int frame_transfer_finished:1;		// [9]
	unsigned int color_format_conversion_error:1;		// [8]
	unsigned int memory_output_error:1;		// [7]
	unsigned int y_bus_congestion_error:1;		// [6]
	unsigned int cb_bus_congestion_error:1;		// [5]
	unsigned int cr_bus_congestion_error:1;		// [4]
	unsigned int input_color_format_error:1;		// [3]
	unsigned int input_height_error:1;		// [2]
	unsigned int input_width_error:1;		// [1]
	unsigned int no_frame_end_error:1;		// [0]
};
 // CDF1_INT_MASK Register
struct CAMIF_CDF1_INT_MASK {
	unsigned int reserved:20;		// [31:12]
	unsigned int mask_vsync:1;		// [11]
	unsigned int mask_hsync_n:1;		// [10]
	unsigned int mask_frame_transfer_finished:1;		// [9]
	unsigned int mask_color_format_conversion_error:1;		// [8]
	unsigned int mask_memory_output_error:1;		// [7]
	unsigned int mask_y_bus_congestion_error:1;		// [6]
	unsigned int mask_cb_bus_congestion_error:1;		// [5]
	unsigned int mask_cr_bus_congestion_error:1;		// [4]
	unsigned int mask_input_color_format_error:1;		// [3]
	unsigned int mask_input_height_error:1;		// [2]
	unsigned int mask_input_width_error:1;		// [1]
	unsigned int mask_no_frame_end_error:1;		// [0]
};
 // CDF1_INT_HSYNCN_LINENUM Register
struct CAMIF_CDF1_INT_HSYNCN_LINENUM {
	unsigned int reserved:18;		// [31:14]
	unsigned int linenum:14;		// [13:0]
};
 // CDF1_RECEIVED_COLOR_FORMAT Register
struct CAMIF_CDF1_RECEIVED_COLOR_FORMAT {
	unsigned int reserved:26;		// [31:6]
	unsigned int received_color_format:6;		// [5:0]
};
 // CDF1_RECEIVED_IMAGE_SIZE Register
struct CAMIF_CDF1_RECEIVED_IMAGE_SIZE {
	unsigned int reserved:2;		// [31:30]
	unsigned int received_image_height:14;		// [29:16]
	unsigned int received_image_width:16;		// [15:0]
};
 // CDF1_SKIP_FRAME_DB Register
struct CAMIF_CDF1_SKIP_FRAME_DB {
	unsigned int reserved:31;		// [31:1]
	unsigned int skip_frame_db:1;		// [0]
};
 // CDF1_SELECT_INPUT_PORT_DB Register
struct CAMIF_CDF1_SELECT_INPUT_PORT_DB {
	unsigned int reserved:31;		// [31:1]
	unsigned int select_input_port_db:1;		// [0]
};
 // CDF1_CNTRL_INPUT_HEIGHT_DB Register
struct CAMIF_CDF1_CNTRL_INPUT_HEIGHT_DB {
	unsigned int reserved:18;		// [31:14]
	unsigned int input_height_db:14;		// [13:0]
};
 // CDF1_CNTRL_INPUT_WIDTH_DB Register
struct CAMIF_CDF1_CNTRL_INPUT_WIDTH_DB {
	unsigned int reserved:18;		// [31:14]
	unsigned int input_width_db:14;		// [13:0]
};
 // CDF1_CNTRL_CONVERSION_DB Register
struct CAMIF_CDF1_CNTRL_CONVERSION_DB {
	unsigned int reserved:30;		// [31:2]
	unsigned int color_format_conversion_db:2;		// [1:0]
};
 // CDF1_CNTRL_MEMORY_OUTPUT_DB Register
struct CAMIF_CDF1_CNTRL_MEMORY_OUTPUT_DB {
	unsigned int reserved:15;		// [31:17]
	unsigned int endian_db:1;		// [16]
	unsigned int reserved2:7;		// [15:9]
	unsigned int swap_yc_or_cbcr_db:1;		// [8]
	unsigned int reserved3:6;		// [7:2]
	unsigned int memory_output_format_db:2;		// [1:0]
};
 // CDF1_INT_HSYNCN_LINENUM_DB Register
struct CAMIF_CDF1_INT_HSYNCN_LINENUM_DB {
	unsigned int reserved:18;		// [31:14]
	unsigned int linenum_db:14;		// [13:0]
};
 // CDF2_ENABLE Register
struct CAMIF_CDF2_ENABLE {
	unsigned int reserved:31;		// [31:1]
	unsigned int enable:1;		// [0]
};
 // CDF2_SKIP_FRAME Register
struct CAMIF_CDF2_SKIP_FRAME {
	unsigned int reserved:31;		// [31:1]
	unsigned int skip_frame:1;		// [0]
};
 // CDF2_SELECT_INPUT_PORT Register
struct CAMIF_CDF2_SELECT_INPUT_PORT {
	unsigned int reserved:31;		// [31:1]
	unsigned int select_input_port:1;		// [0]
};
 // CDF2_CNTRL_INPUT_HEIGHT Register
struct CAMIF_CDF2_CNTRL_INPUT_HEIGHT {
	unsigned int reserved:18;		// [31:14]
	unsigned int input_height:14;		// [13:0]
};
 // CDF2_CNTRL_INPUT_WIDTH Register
struct CAMIF_CDF2_CNTRL_INPUT_WIDTH {
	unsigned int reserved:18;		// [31:14]
	unsigned int input_width:14;		// [13:0]
};
 // CDF2_CNTRL_CONVERSION Register
struct CAMIF_CDF2_CNTRL_CONVERSION {
	unsigned int reserved:30;		// [31:2]
	unsigned int color_format_conversion:2;		// [1:0]
};
 // CDF2_CNTRL_MEMORY_OUTPUT Register
struct CAMIF_CDF2_CNTRL_MEMORY_OUTPUT {
	unsigned int reserved:15;		// [31:17]
	unsigned int endian:1;		// [16]
	unsigned int reserved2:7;		// [15:9]
	unsigned int swap_yc_or_cbcr:1;		// [8]
	unsigned int reserved3:6;		// [7:2]
	unsigned int memory_output_format:2;		// [1:0]
};
 // CDF2_INT_STAT Register
struct CAMIF_CDF2_INT_STAT {
	unsigned int reserved:20;		// [31:12]
	unsigned int vsync:1;		// [11]
	unsigned int hsync_n:1;		// [10]
	unsigned int frame_transfer_finished:1;		// [9]
	unsigned int color_format_conversion_error:1;		// [8]
	unsigned int memory_output_error:1;		// [7]
	unsigned int y_bus_congestion_error:1;		// [6]
	unsigned int cb_bus_congestion_error:1;		// [5]
	unsigned int cr_bus_congestion_error:1;		// [4]
	unsigned int input_color_format_error:1;		// [3]
	unsigned int input_height_error:1;		// [2]
	unsigned int input_width_error:1;		// [1]
	unsigned int no_frame_end_error:1;		// [0]
};
 // CDF2_INT_MASK Register
struct CAMIF_CDF2_INT_MASK {
	unsigned int reserved:20;		// [31:12]
	unsigned int mask_vsync:1;		// [11]
	unsigned int mask_hsync_n:1;		// [10]
	unsigned int mask_frame_transfer_finished:1;		// [9]
	unsigned int mask_color_format_conversion_error:1;		// [8]
	unsigned int mask_memory_output_error:1;		// [7]
	unsigned int mask_y_bus_congestion_error:1;		// [6]
	unsigned int mask_cb_bus_congestion_error:1;		// [5]
	unsigned int mask_cr_bus_congestion_error:1;		// [4]
	unsigned int mask_input_color_format_error:1;		// [3]
	unsigned int mask_input_height_error:1;		// [2]
	unsigned int mask_input_width_error:1;		// [1]
	unsigned int mask_no_frame_end_error:1;		// [0]
};
 // CDF2_INT_HSYNCN_LINENUM Register
struct CAMIF_CDF2_INT_HSYNCN_LINENUM {
	unsigned int reserved:18;		// [31:14]
	unsigned int linenum:14;		// [13:0]
};
 // CDF2_RECEIVED_COLOR_FORMAT Register
struct CAMIF_CDF2_RECEIVED_COLOR_FORMAT {
	unsigned int reserved:26;		// [31:6]
	unsigned int received_color_format:6;		// [5:0]
};
 // CDF2_RECEIVED_IMAGE_SIZE Register
struct CAMIF_CDF2_RECEIVED_IMAGE_SIZE {
	unsigned int reserved:2;		// [31:30]
	unsigned int received_image_height:14;		// [29:16]
	unsigned int received_image_width:16;		// [15:0]
};
 // CDF2_SKIP_FRAME_DB Register
struct CAMIF_CDF2_SKIP_FRAME_DB {
	unsigned int reserved:31;		// [31:1]
	unsigned int skip_frame_db:1;		// [0]
};
 // CDF2_SELECT_INPUT_PORT_DB Register
struct CAMIF_CDF2_SELECT_INPUT_PORT_DB {
	unsigned int reserved:31;		// [31:1]
	unsigned int select_input_port_db:1;		// [0]
};
 // CDF2_CNTRL_INPUT_HEIGHT_DB Register
struct CAMIF_CDF2_CNTRL_INPUT_HEIGHT_DB {
	unsigned int reserved:18;		// [31:14]
	unsigned int input_height_db:14;		// [13:0]
};
 // CDF2_CNTRL_INPUT_WIDTH_DB Register
struct CAMIF_CDF2_CNTRL_INPUT_WIDTH_DB {
	unsigned int reserved:18;		// [31:14]
	unsigned int input_width_db:14;		// [13:0]
};
 // CDF2_CNTRL_CONVERSION_DB Register
struct CAMIF_CDF2_CNTRL_CONVERSION_DB {
	unsigned int reserved:30;		// [31:2]
	unsigned int color_format_conversion_db:2;		// [1:0]
};
 // CDF2_CNTRL_MEMORY_OUTPUT_DB Register
struct CAMIF_CDF2_CNTRL_MEMORY_OUTPUT_DB {
	unsigned int reserved:15;		// [31:17]
	unsigned int endian_db:1;		// [16]
	unsigned int reserved2:7;		// [15:9]
	unsigned int swap_yc_or_cbcr_db:1;		// [8]
	unsigned int reserved3:6;		// [7:2]
	unsigned int memory_output_format_db:2;		// [1:0]
};
 // CDF2_INT_HSYNCN_LINENUM_DB Register
struct CAMIF_CDF2_INT_HSYNCN_LINENUM_DB {
	unsigned int reserved:18;		// [31:14]
	unsigned int linenum_db:14;		// [13:0]
};
 // CDF3_ENABLE Register
struct CAMIF_CDF3_ENABLE {
	unsigned int reserved:31;		// [31:1]
	unsigned int enable:1;		// [0]
};
 // CDF3_SKIP_FRAME Register
struct CAMIF_CDF3_SKIP_FRAME {
	unsigned int reserved:31;		// [31:1]
	unsigned int skip_frame:1;		// [0]
};
 // CDF3_SELECT_INPUT_PORT Register
struct CAMIF_CDF3_SELECT_INPUT_PORT {
	unsigned int reserved:31;		// [31:1]
	unsigned int select_input_port:1;		// [0]
};
 // CDF3_CNTRL_INPUT_HEIGHT Register
struct CAMIF_CDF3_CNTRL_INPUT_HEIGHT {
	unsigned int reserved:18;		// [31:14]
	unsigned int input_height:14;		// [13:0]
};
 // CDF3_CNTRL_INPUT_WIDTH Register
struct CAMIF_CDF3_CNTRL_INPUT_WIDTH {
	unsigned int reserved:18;		// [31:14]
	unsigned int input_width:14;		// [13:0]
};
 // CDF3_CNTRL_CONVERSION Register
struct CAMIF_CDF3_CNTRL_CONVERSION {
	unsigned int reserved:30;		// [31:2]
	unsigned int color_format_conversion:2;		// [1:0]
};
 // CDF3_CNTRL_MEMORY_OUTPUT Register
struct CAMIF_CDF3_CNTRL_MEMORY_OUTPUT {
	unsigned int reserved:15;		// [31:17]
	unsigned int endian:1;		// [16]
	unsigned int reserved2:7;		// [15:9]
	unsigned int swap_yc_or_cbcr:1;		// [8]
	unsigned int reserved3:6;		// [7:2]
	unsigned int memory_output_format:2;		// [1:0]
};
 // CDF3_INT_STAT Register
struct CAMIF_CDF3_INT_STAT {
	unsigned int reserved:20;		// [31:12]
	unsigned int vsync:1;		// [11]
	unsigned int hsync_n:1;		// [10]
	unsigned int frame_transfer_finished:1;		// [9]
	unsigned int color_format_conversion_error:1;		// [8]
	unsigned int memory_output_error:1;		// [7]
	unsigned int y_bus_congestion_error:1;		// [6]
	unsigned int cb_bus_congestion_error:1;		// [5]
	unsigned int cr_bus_congestion_error:1;		// [4]
	unsigned int input_color_format_error:1;		// [3]
	unsigned int input_height_error:1;		// [2]
	unsigned int input_width_error:1;		// [1]
	unsigned int no_frame_end_error:1;		// [0]
};
 // CDF3_INT_MASK Register
struct CAMIF_CDF3_INT_MASK {
	unsigned int reserved:20;		// [31:12]
	unsigned int mask_vsync:1;		// [11]
	unsigned int mask_hsync_n:1;		// [10]
	unsigned int mask_frame_transfer_finished:1;		// [9]
	unsigned int mask_color_format_conversion_error:1;		// [8]
	unsigned int mask_memory_output_error:1;		// [7]
	unsigned int mask_y_bus_congestion_error:1;		// [6]
	unsigned int mask_cb_bus_congestion_error:1;		// [5]
	unsigned int mask_cr_bus_congestion_error:1;		// [4]
	unsigned int mask_input_color_format_error:1;		// [3]
	unsigned int mask_input_height_error:1;		// [2]
	unsigned int mask_input_width_error:1;		// [1]
	unsigned int mask_no_frame_end_error:1;		// [0]
};
 // CDF3_INT_HSYNCN_LINENUM Register
struct CAMIF_CDF3_INT_HSYNCN_LINENUM {
	unsigned int reserved:18;		// [31:14]
	unsigned int linenum:14;		// [13:0]
};
 // CDF3_RECEIVED_COLOR_FORMAT Register
struct CAMIF_CDF3_RECEIVED_COLOR_FORMAT {
	unsigned int reserved:26;		// [31:6]
	unsigned int received_color_format:6;		// [5:0]
};
 // CDF3_RECEIVED_IMAGE_SIZE Register
struct CAMIF_CDF3_RECEIVED_IMAGE_SIZE {
	unsigned int reserved:2;		// [31:30]
	unsigned int received_image_height:14;		// [29:16]
	unsigned int received_image_width:16;		// [15:0]
};
 // CDF3_SKIP_FRAME_DB Register
struct CAMIF_CDF3_SKIP_FRAME_DB {
	unsigned int reserved:31;		// [31:1]
	unsigned int skip_frame_db:1;		// [0]
};
 // CDF3_SELECT_INPUT_PORT_DB Register
struct CAMIF_CDF3_SELECT_INPUT_PORT_DB {
	unsigned int reserved:31;		// [31:1]
	unsigned int select_input_port_db:1;		// [0]
};
 // CDF3_CNTRL_INPUT_HEIGHT_DB Register
struct CAMIF_CDF3_CNTRL_INPUT_HEIGHT_DB {
	unsigned int reserved:18;		// [31:14]
	unsigned int input_height_db:14;		// [13:0]
};
 // CDF3_CNTRL_INPUT_WIDTH_DB Register
struct CAMIF_CDF3_CNTRL_INPUT_WIDTH_DB {
	unsigned int reserved:18;		// [31:14]
	unsigned int input_width_db:14;		// [13:0]
};
 // CDF3_CNTRL_CONVERSION_DB Register
struct CAMIF_CDF3_CNTRL_CONVERSION_DB {
	unsigned int reserved:30;		// [31:2]
	unsigned int color_format_conversion_db:2;		// [1:0]
};
 // CDF3_CNTRL_MEMORY_OUTPUT_DB Register
struct CAMIF_CDF3_CNTRL_MEMORY_OUTPUT_DB {
	unsigned int reserved:15;		// [31:17]
	unsigned int endian_db:1;		// [16]
	unsigned int reserved2:7;		// [15:9]
	unsigned int swap_yc_or_cbcr_db:1;		// [8]
	unsigned int reserved3:6;		// [7:2]
	unsigned int memory_output_format_db:2;		// [1:0]
};
 // CDF3_INT_HSYNCN_LINENUM_DB Register
struct CAMIF_CDF3_INT_HSYNCN_LINENUM_DB {
	unsigned int reserved:18;		// [31:14]
	unsigned int linenum_db:14;		// [13:0]
};
 // CDPHY_LANE_CONFIG Register
struct CAMIF_CDPHY_LANE_CONFIG {
	unsigned int reserved:29;		// [31:3]
	unsigned int lane_config:3;		// [2:0]
};
 // CAMIF_INT_SRC_SUB_MOD Register
struct CAMIF_CAMIF_INT_SRC_SUB_MOD {
	unsigned int irq_camif_LPRXSTATEINT_csirx3:1;		// [31]
	unsigned int irq_camif_RXERRINT_csirx3:1;		// [30]
	unsigned int irq_camif_SHTPKTINT_csirx3:1;		// [29]
	unsigned int irq_camif_LNGPKTINT_csirx3:1;		// [28]
	unsigned int irq_camif_LPRXSTATEINT_csirx2:1;		// [27]
	unsigned int irq_camif_RXERRINT_csirx2:1;		// [26]
	unsigned int irq_camif_SHTPKTINT_csirx2:1;		// [25]
	unsigned int irq_camif_LNGPKTINT_csirx2:1;		// [24]
	unsigned int irq_camif_LPRXSTATEINT_csirx1:1;		// [23]
	unsigned int irq_camif_RXERRINT_csirx1:1;		// [22]
	unsigned int irq_camif_SHTPKTINT_csirx1:1;		// [21]
	unsigned int irq_camif_LNGPKTINT_csirx1:1;		// [20]
	unsigned int irq_camif_LPRXSTATEINT_csirx0:1;		// [19]
	unsigned int irq_camif_RXERRINT_csirx0:1;		// [18]
	unsigned int irq_camif_SHTPKTINT_csirx0:1;		// [17]
	unsigned int irq_camif_LNGPKTINT_csirx0:1;		// [16]
	unsigned int reserved:4;		// [15:12]
	unsigned int irq_camif_csidf3:1;		// [11]
	unsigned int irq_camif_csidf2:1;		// [10]
	unsigned int irq_camif_csidf1:1;		// [9]
	unsigned int irq_camif_csidf0:1;		// [8]
	unsigned int reserved2:7;		// [7:1]
	unsigned int irq_camif_cvdmac:1;		// [0]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _CAMIF_REG_STRUCT_B_H */
