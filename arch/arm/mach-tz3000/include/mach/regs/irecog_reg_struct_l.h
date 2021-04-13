/*
 * arch/arm/mach-tz3000/include/mach/regs/irecog_reg_struct_l.h
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

#ifndef _IRECOG_REG_STRUCT_L_H
#define _IRECOG_REG_STRUCT_L_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // rpyramid_PYM_STADR Register
struct IRECOG_RPYRAMID_PYM_STADR {
	unsigned int cf_mb_stadr:32;		// [31:0]
};
 // rpyramid_PYM_ENDADR Register
struct IRECOG_RPYRAMID_PYM_ENDADR {
	unsigned int cf_mb_endadr:32;		// [31:0]
};
 // rpyramid_PYM_DMRADR Register
struct IRECOG_RPYRAMID_PYM_DMRADR {
	unsigned int cf_dr_adr:32;		// [31:0]
};
 // rpyramid_PYM_CFG Register
struct IRECOG_RPYRAMID_PYM_CFG {
	unsigned int cf_dr_enable_g00:1;		// [0]
	unsigned int reserved:7;		// [7:1]
	unsigned int cf_cmd_queue_depth:3;		// [10:8]
	unsigned int reserved2:5;		// [15:11]
	unsigned int cf_accmd_queue_depth:3;		// [18:16]
	unsigned int reserved3:5;		// [23:19]
	unsigned int cf_vdmacctrl:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_INT_MASK Register
struct IRECOG_RPYRAMID_PYM_INT_MASK {
	unsigned int cf_int_mask_g00:1;		// [0]
	unsigned int reserved:14;		// [14:1]
	unsigned int cf_mb_err_mask:1;		// [15]
	unsigned int cf_abort_mask_g00:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_R_ENABLE Register
struct IRECOG_RPYRAMID_PYM_R_ENABLE {
	unsigned int cf_enable_r00:1;		// [0]
	unsigned int cf_enable_r01:1;		// [1]
	unsigned int cf_enable_r02:1;		// [2]
	unsigned int reserved:29;		// [31:3]
};
 // rpyramid_PYM_W_ENABLE Register
struct IRECOG_RPYRAMID_PYM_W_ENABLE {
	unsigned int cf_enable_w00:1;		// [0]
	unsigned int cf_enable_w01:1;		// [1]
	unsigned int cf_enable_w02:1;		// [2]
	unsigned int cf_enable_w03:1;		// [3]
	unsigned int cf_enable_w04:1;		// [4]
	unsigned int cf_enable_w05:1;		// [5]
	unsigned int cf_enable_w06:1;		// [6]
	unsigned int cf_enable_w07:1;		// [7]
	unsigned int cf_enable_w08:1;		// [8]
	unsigned int cf_enable_w09:1;		// [9]
	unsigned int cf_enable_w10:1;		// [10]
	unsigned int cf_enable_w11:1;		// [11]
	unsigned int reserved:20;		// [31:12]
};
 // rpyramid_PYM_T_ENABLE Register
struct IRECOG_RPYRAMID_PYM_T_ENABLE {
	unsigned int cf_enable_t00:1;		// [0]
	unsigned int cf_enable_t01:1;		// [1]
	unsigned int cf_enable_t02:1;		// [2]
	unsigned int cf_enable_t03:1;		// [3]
	unsigned int cf_enable_t04:1;		// [4]
	unsigned int cf_enable_t05:1;		// [5]
	unsigned int cf_enable_t06:1;		// [6]
	unsigned int cf_enable_t07:1;		// [7]
	unsigned int cf_enable_t08:1;		// [8]
	unsigned int cf_enable_t09:1;		// [9]
	unsigned int cf_enable_t10:1;		// [10]
	unsigned int cf_enable_t11:1;		// [11]
	unsigned int cf_enable_t12:1;		// [12]
	unsigned int cf_enable_t13:1;		// [13]
	unsigned int cf_enable_t14:1;		// [14]
	unsigned int cf_enable_t15:1;		// [15]
	unsigned int reserved:16;		// [31:16]
};
 // rpyramid_PYM_CTRL Register
struct IRECOG_RPYRAMID_PYM_CTRL {
	unsigned int cf_force_abort_g00:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // rpyramid_PYM_T00_CFG Register
struct IRECOG_RPYRAMID_PYM_T00_CFG {
	unsigned int reserved:4;		// [3:0]
	unsigned int cf_endian_t00:1;		// [4]
	unsigned int reserved2:3;		// [7:5]
	unsigned int cf_datawidth_t00:2;		// [9:8]
	unsigned int reserved3:6;		// [15:10]
	unsigned int cf_sram_th_t00:5;		// [20:16]
	unsigned int reserved4:3;		// [23:21]
	unsigned int cf_buf_th_t00:1;		// [24]
	unsigned int reserved5:7;		// [31:25]
};
 // rpyramid_PYM_T00_SRAM_BASE Register
struct IRECOG_RPYRAMID_PYM_T00_SRAM_BASE {
	unsigned int cf_sram_base_t00:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // rpyramid_PYM_T00_SRAM_SIZE Register
struct IRECOG_RPYRAMID_PYM_T00_SRAM_SIZE {
	unsigned int cf_sram_size_t00:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // rpyramid_PYM_T00_INTL Register
struct IRECOG_RPYRAMID_PYM_T00_INTL {
	unsigned int cf_interval_t00:6;		// [5:0]
	unsigned int cf_init_interval_t00:6;		// [11:6]
	unsigned int reserved:4;		// [15:12]
	unsigned int cf_init_interval_period_t00:8;		// [23:16]
	unsigned int reserved2:8;		// [31:24]
};
 // rpyramid_PYM_T00_STADR Register
struct IRECOG_RPYRAMID_PYM_T00_STADR {
	unsigned int cf_td_stadr_t00:32;		// [31:0]
};
 // rpyramid_PYM_T00_SIZE Register
struct IRECOG_RPYRAMID_PYM_T00_SIZE {
	unsigned int cf_td_size_t00:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_T01_STADR Register
struct IRECOG_RPYRAMID_PYM_T01_STADR {
	unsigned int cf_td_stadr_t01:32;		// [31:0]
};
 // rpyramid_PYM_T01_SIZE Register
struct IRECOG_RPYRAMID_PYM_T01_SIZE {
	unsigned int cf_td_size_t01:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_T02_STADR Register
struct IRECOG_RPYRAMID_PYM_T02_STADR {
	unsigned int cf_td_stadr_t02:32;		// [31:0]
};
 // rpyramid_PYM_T02_SIZE Register
struct IRECOG_RPYRAMID_PYM_T02_SIZE {
	unsigned int cf_td_size_t02:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_T03_STADR Register
struct IRECOG_RPYRAMID_PYM_T03_STADR {
	unsigned int cf_td_stadr_t03:32;		// [31:0]
};
 // rpyramid_PYM_T03_SIZE Register
struct IRECOG_RPYRAMID_PYM_T03_SIZE {
	unsigned int cf_td_size_t03:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_T04_STADR Register
struct IRECOG_RPYRAMID_PYM_T04_STADR {
	unsigned int cf_td_stadr_t04:32;		// [31:0]
};
 // rpyramid_PYM_T04_SIZE Register
struct IRECOG_RPYRAMID_PYM_T04_SIZE {
	unsigned int cf_td_size_t04:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_T05_STADR Register
struct IRECOG_RPYRAMID_PYM_T05_STADR {
	unsigned int cf_td_stadr_t05:32;		// [31:0]
};
 // rpyramid_PYM_T05_SIZE Register
struct IRECOG_RPYRAMID_PYM_T05_SIZE {
	unsigned int cf_td_size_t05:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_T06_STADR Register
struct IRECOG_RPYRAMID_PYM_T06_STADR {
	unsigned int cf_td_stadr_t06:32;		// [31:0]
};
 // rpyramid_PYM_T06_SIZE Register
struct IRECOG_RPYRAMID_PYM_T06_SIZE {
	unsigned int cf_td_size_t06:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_T07_STADR Register
struct IRECOG_RPYRAMID_PYM_T07_STADR {
	unsigned int cf_td_stadr_t07:32;		// [31:0]
};
 // rpyramid_PYM_T07_SIZE Register
struct IRECOG_RPYRAMID_PYM_T07_SIZE {
	unsigned int cf_td_size_t07:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_T08_STADR Register
struct IRECOG_RPYRAMID_PYM_T08_STADR {
	unsigned int cf_td_stadr_t08:32;		// [31:0]
};
 // rpyramid_PYM_T08_SIZE Register
struct IRECOG_RPYRAMID_PYM_T08_SIZE {
	unsigned int cf_td_size_t08:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_T09_STADR Register
struct IRECOG_RPYRAMID_PYM_T09_STADR {
	unsigned int cf_td_stadr_t09:32;		// [31:0]
};
 // rpyramid_PYM_T09_SIZE Register
struct IRECOG_RPYRAMID_PYM_T09_SIZE {
	unsigned int cf_td_size_t09:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_T10_STADR Register
struct IRECOG_RPYRAMID_PYM_T10_STADR {
	unsigned int cf_td_stadr_t10:32;		// [31:0]
};
 // rpyramid_PYM_T10_SIZE Register
struct IRECOG_RPYRAMID_PYM_T10_SIZE {
	unsigned int cf_td_size_t10:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_T11_STADR Register
struct IRECOG_RPYRAMID_PYM_T11_STADR {
	unsigned int cf_td_stadr_t11:32;		// [31:0]
};
 // rpyramid_PYM_T11_SIZE Register
struct IRECOG_RPYRAMID_PYM_T11_SIZE {
	unsigned int cf_td_size_t11:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_T12_STADR Register
struct IRECOG_RPYRAMID_PYM_T12_STADR {
	unsigned int cf_td_stadr_t12:32;		// [31:0]
};
 // rpyramid_PYM_T12_SIZE Register
struct IRECOG_RPYRAMID_PYM_T12_SIZE {
	unsigned int cf_td_size_t12:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_T13_STADR Register
struct IRECOG_RPYRAMID_PYM_T13_STADR {
	unsigned int cf_td_stadr_t13:32;		// [31:0]
};
 // rpyramid_PYM_T13_SIZE Register
struct IRECOG_RPYRAMID_PYM_T13_SIZE {
	unsigned int cf_td_size_t13:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_T14_STADR Register
struct IRECOG_RPYRAMID_PYM_T14_STADR {
	unsigned int cf_td_stadr_t14:32;		// [31:0]
};
 // rpyramid_PYM_T14_SIZE Register
struct IRECOG_RPYRAMID_PYM_T14_SIZE {
	unsigned int cf_td_size_t14:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_T15_STADR Register
struct IRECOG_RPYRAMID_PYM_T15_STADR {
	unsigned int cf_td_stadr_t15:32;		// [31:0]
};
 // rpyramid_PYM_T15_SIZE Register
struct IRECOG_RPYRAMID_PYM_T15_SIZE {
	unsigned int cf_td_size_t15:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_R00_STADR Register
struct IRECOG_RPYRAMID_PYM_R00_STADR {
	unsigned int cf_stadr_r00:32;		// [31:0]
};
 // rpyramid_PYM_R00_ENDADR Register
struct IRECOG_RPYRAMID_PYM_R00_ENDADR {
	unsigned int cf_endadr_r00:32;		// [31:0]
};
 // rpyramid_PYM_R00_HEIGHT Register
struct IRECOG_RPYRAMID_PYM_R00_HEIGHT {
	unsigned int cf_height_r00:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_R00_PITCH Register
struct IRECOG_RPYRAMID_PYM_R00_PITCH {
	unsigned int cf_pitch_r00:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // rpyramid_PYM_R00_CFG0 Register
struct IRECOG_RPYRAMID_PYM_R00_CFG0 {
	unsigned int reserved:8;		// [7:0]
	unsigned int cf_datawidth_r00:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_sram_th_r00:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_buf_th_r00:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_R00_CFG1 Register
struct IRECOG_RPYRAMID_PYM_R00_CFG1 {
	unsigned int reserved:16;		// [15:0]
	unsigned int cf_endian_r00:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_R00_SRAM_BASE Register
struct IRECOG_RPYRAMID_PYM_R00_SRAM_BASE {
	unsigned int cf_sram_base_r00:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // rpyramid_PYM_R00_SRAM_SIZE Register
struct IRECOG_RPYRAMID_PYM_R00_SRAM_SIZE {
	unsigned int cf_sram_size_r00:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // rpyramid_PYM_R00_INTL Register
struct IRECOG_RPYRAMID_PYM_R00_INTL {
	unsigned int cf_interval_r00:6;		// [5:0]
	unsigned int cf_init_interval_r00:6;		// [11:6]
	unsigned int reserved:4;		// [15:12]
	unsigned int cf_init_interval_period_r00:8;		// [23:16]
	unsigned int reserved2:8;		// [31:24]
};
 // rpyramid_PYM_R01_STADR Register
struct IRECOG_RPYRAMID_PYM_R01_STADR {
	unsigned int cf_stadr_r01:32;		// [31:0]
};
 // rpyramid_PYM_R01_ENDADR Register
struct IRECOG_RPYRAMID_PYM_R01_ENDADR {
	unsigned int cf_endadr_r01:32;		// [31:0]
};
 // rpyramid_PYM_R01_HEIGHT Register
struct IRECOG_RPYRAMID_PYM_R01_HEIGHT {
	unsigned int cf_height_r01:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_R01_PITCH Register
struct IRECOG_RPYRAMID_PYM_R01_PITCH {
	unsigned int cf_pitch_r01:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // rpyramid_PYM_R01_CFG0 Register
struct IRECOG_RPYRAMID_PYM_R01_CFG0 {
	unsigned int reserved:8;		// [7:0]
	unsigned int cf_datawidth_r01:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_sram_th_r01:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_buf_th_r01:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_R01_CFG1 Register
struct IRECOG_RPYRAMID_PYM_R01_CFG1 {
	unsigned int reserved:16;		// [15:0]
	unsigned int cf_endian_r01:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_R01_SRAM_BASE Register
struct IRECOG_RPYRAMID_PYM_R01_SRAM_BASE {
	unsigned int cf_sram_base_r01:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // rpyramid_PYM_R01_SRAM_SIZE Register
struct IRECOG_RPYRAMID_PYM_R01_SRAM_SIZE {
	unsigned int cf_sram_size_r01:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // rpyramid_PYM_R01_INTL Register
struct IRECOG_RPYRAMID_PYM_R01_INTL {
	unsigned int cf_interval_r01:6;		// [5:0]
	unsigned int cf_init_interval_r01:6;		// [11:6]
	unsigned int reserved:4;		// [15:12]
	unsigned int cf_init_interval_period_r01:8;		// [23:16]
	unsigned int reserved2:8;		// [31:24]
};
 // rpyramid_PYM_R02_STADR Register
struct IRECOG_RPYRAMID_PYM_R02_STADR {
	unsigned int cf_stadr_r02:32;		// [31:0]
};
 // rpyramid_PYM_R02_ENDADR Register
struct IRECOG_RPYRAMID_PYM_R02_ENDADR {
	unsigned int cf_endadr_r02:32;		// [31:0]
};
 // rpyramid_PYM_R02_HEIGHT Register
struct IRECOG_RPYRAMID_PYM_R02_HEIGHT {
	unsigned int cf_height_r02:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_R02_PITCH Register
struct IRECOG_RPYRAMID_PYM_R02_PITCH {
	unsigned int cf_pitch_r02:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // rpyramid_PYM_R02_CFG0 Register
struct IRECOG_RPYRAMID_PYM_R02_CFG0 {
	unsigned int reserved:8;		// [7:0]
	unsigned int cf_datawidth_r02:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_sram_th_r02:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_buf_th_r02:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_R02_CFG1 Register
struct IRECOG_RPYRAMID_PYM_R02_CFG1 {
	unsigned int reserved:16;		// [15:0]
	unsigned int cf_endian_r02:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_R02_SRAM_BASE Register
struct IRECOG_RPYRAMID_PYM_R02_SRAM_BASE {
	unsigned int cf_sram_base_r02:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // rpyramid_PYM_R02_SRAM_SIZE Register
struct IRECOG_RPYRAMID_PYM_R02_SRAM_SIZE {
	unsigned int cf_sram_size_r02:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // rpyramid_PYM_R02_INTL Register
struct IRECOG_RPYRAMID_PYM_R02_INTL {
	unsigned int cf_interval_r02:6;		// [5:0]
	unsigned int cf_init_interval_r02:6;		// [11:6]
	unsigned int reserved:4;		// [15:12]
	unsigned int cf_init_interval_period_r02:8;		// [23:16]
	unsigned int reserved2:8;		// [31:24]
};
 // rpyramid_PYM_W00_STADR Register
struct IRECOG_RPYRAMID_PYM_W00_STADR {
	unsigned int cf_stadr_w00:32;		// [31:0]
};
 // rpyramid_PYM_W00_ENDADR Register
struct IRECOG_RPYRAMID_PYM_W00_ENDADR {
	unsigned int cf_endadr_w00:32;		// [31:0]
};
 // rpyramid_PYM_W00_HEIGHT Register
struct IRECOG_RPYRAMID_PYM_W00_HEIGHT {
	unsigned int cf_height_w00:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W00_PITCH Register
struct IRECOG_RPYRAMID_PYM_W00_PITCH {
	unsigned int cf_pitch_w00:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // rpyramid_PYM_W00_CFG0 Register
struct IRECOG_RPYRAMID_PYM_W00_CFG0 {
	unsigned int reserved:8;		// [7:0]
	unsigned int cf_datawidth_w00:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_sram_th_w00:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_buf_th_w00:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_W00_CFG1 Register
struct IRECOG_RPYRAMID_PYM_W00_CFG1 {
	unsigned int cf_maskbyte_w00:3;		// [2:0]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_endian_w00:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_W00_SRAM_BASE Register
struct IRECOG_RPYRAMID_PYM_W00_SRAM_BASE {
	unsigned int cf_sram_base_w00:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W00_SRAM_SIZE Register
struct IRECOG_RPYRAMID_PYM_W00_SRAM_SIZE {
	unsigned int cf_sram_size_w00:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W00_INTL Register
struct IRECOG_RPYRAMID_PYM_W00_INTL {
	unsigned int cf_interval_w00:6;		// [5:0]
	unsigned int cf_init_interval_w00:6;		// [11:6]
	unsigned int reserved:4;		// [15:12]
	unsigned int cf_init_interval_period_w00:8;		// [23:16]
	unsigned int reserved2:8;		// [31:24]
};
 // rpyramid_PYM_W01_STADR Register
struct IRECOG_RPYRAMID_PYM_W01_STADR {
	unsigned int cf_stadr_w01:32;		// [31:0]
};
 // rpyramid_PYM_W01_ENDADR Register
struct IRECOG_RPYRAMID_PYM_W01_ENDADR {
	unsigned int cf_endadr_w01:32;		// [31:0]
};
 // rpyramid_PYM_W01_HEIGHT Register
struct IRECOG_RPYRAMID_PYM_W01_HEIGHT {
	unsigned int cf_height_w01:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W01_PITCH Register
struct IRECOG_RPYRAMID_PYM_W01_PITCH {
	unsigned int cf_pitch_w01:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // rpyramid_PYM_W01_CFG0 Register
struct IRECOG_RPYRAMID_PYM_W01_CFG0 {
	unsigned int reserved:8;		// [7:0]
	unsigned int cf_datawidth_w01:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_sram_th_w01:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_buf_th_w01:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_W01_CFG1 Register
struct IRECOG_RPYRAMID_PYM_W01_CFG1 {
	unsigned int cf_maskbyte_w01:3;		// [2:0]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_endian_w01:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_W01_SRAM_BASE Register
struct IRECOG_RPYRAMID_PYM_W01_SRAM_BASE {
	unsigned int cf_sram_base_w01:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W01_SRAM_SIZE Register
struct IRECOG_RPYRAMID_PYM_W01_SRAM_SIZE {
	unsigned int cf_sram_size_w01:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W01_INTL Register
struct IRECOG_RPYRAMID_PYM_W01_INTL {
	unsigned int cf_interval_w01:6;		// [5:0]
	unsigned int cf_init_interval_w01:6;		// [11:6]
	unsigned int reserved:4;		// [15:12]
	unsigned int cf_init_interval_period_w01:8;		// [23:16]
	unsigned int reserved2:8;		// [31:24]
};
 // rpyramid_PYM_W02_STADR Register
struct IRECOG_RPYRAMID_PYM_W02_STADR {
	unsigned int cf_stadr_w02:32;		// [31:0]
};
 // rpyramid_PYM_W02_ENDADR Register
struct IRECOG_RPYRAMID_PYM_W02_ENDADR {
	unsigned int cf_endadr_w02:32;		// [31:0]
};
 // rpyramid_PYM_W02_HEIGHT Register
struct IRECOG_RPYRAMID_PYM_W02_HEIGHT {
	unsigned int cf_height_w02:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W02_PITCH Register
struct IRECOG_RPYRAMID_PYM_W02_PITCH {
	unsigned int cf_pitch_w02:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // rpyramid_PYM_W02_CFG0 Register
struct IRECOG_RPYRAMID_PYM_W02_CFG0 {
	unsigned int reserved:8;		// [7:0]
	unsigned int cf_datawidth_w02:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_sram_th_w02:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_buf_th_w02:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_W02_CFG1 Register
struct IRECOG_RPYRAMID_PYM_W02_CFG1 {
	unsigned int cf_maskbyte_w02:3;		// [2:0]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_endian_w02:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_W02_SRAM_BASE Register
struct IRECOG_RPYRAMID_PYM_W02_SRAM_BASE {
	unsigned int cf_sram_base_w02:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W02_SRAM_SIZE Register
struct IRECOG_RPYRAMID_PYM_W02_SRAM_SIZE {
	unsigned int cf_sram_size_w02:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W02_INTL Register
struct IRECOG_RPYRAMID_PYM_W02_INTL {
	unsigned int cf_interval_w02:6;		// [5:0]
	unsigned int cf_init_interval_w02:6;		// [11:6]
	unsigned int reserved:4;		// [15:12]
	unsigned int cf_init_interval_period_w02:8;		// [23:16]
	unsigned int reserved2:8;		// [31:24]
};
 // rpyramid_PYM_W03_STADR Register
struct IRECOG_RPYRAMID_PYM_W03_STADR {
	unsigned int cf_stadr_w03:32;		// [31:0]
};
 // rpyramid_PYM_W03_ENDADR Register
struct IRECOG_RPYRAMID_PYM_W03_ENDADR {
	unsigned int cf_endadr_w03:32;		// [31:0]
};
 // rpyramid_PYM_W03_HEIGHT Register
struct IRECOG_RPYRAMID_PYM_W03_HEIGHT {
	unsigned int cf_height_w03:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W03_PITCH Register
struct IRECOG_RPYRAMID_PYM_W03_PITCH {
	unsigned int cf_pitch_w03:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // rpyramid_PYM_W03_CFG0 Register
struct IRECOG_RPYRAMID_PYM_W03_CFG0 {
	unsigned int reserved:8;		// [7:0]
	unsigned int cf_datawidth_w03:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_sram_th_w03:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_buf_th_w03:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_W03_CFG1 Register
struct IRECOG_RPYRAMID_PYM_W03_CFG1 {
	unsigned int cf_maskbyte_w03:3;		// [2:0]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_endian_w03:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_W03_SRAM_BASE Register
struct IRECOG_RPYRAMID_PYM_W03_SRAM_BASE {
	unsigned int cf_sram_base_w03:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W03_SRAM_SIZE Register
struct IRECOG_RPYRAMID_PYM_W03_SRAM_SIZE {
	unsigned int cf_sram_size_w03:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W03_INTL Register
struct IRECOG_RPYRAMID_PYM_W03_INTL {
	unsigned int cf_interval_w03:6;		// [5:0]
	unsigned int cf_init_interval_w03:6;		// [11:6]
	unsigned int reserved:4;		// [15:12]
	unsigned int cf_init_interval_period_w03:8;		// [23:16]
	unsigned int reserved2:8;		// [31:24]
};
 // rpyramid_PYM_W04_STADR Register
struct IRECOG_RPYRAMID_PYM_W04_STADR {
	unsigned int cf_stadr_w04:32;		// [31:0]
};
 // rpyramid_PYM_W04_ENDADR Register
struct IRECOG_RPYRAMID_PYM_W04_ENDADR {
	unsigned int cf_endadr_w04:32;		// [31:0]
};
 // rpyramid_PYM_W04_HEIGHT Register
struct IRECOG_RPYRAMID_PYM_W04_HEIGHT {
	unsigned int cf_height_w04:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W04_PITCH Register
struct IRECOG_RPYRAMID_PYM_W04_PITCH {
	unsigned int cf_pitch_w04:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // rpyramid_PYM_W04_CFG0 Register
struct IRECOG_RPYRAMID_PYM_W04_CFG0 {
	unsigned int reserved:8;		// [7:0]
	unsigned int cf_datawidth_w04:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_sram_th_w04:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_buf_th_w04:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_W04_CFG1 Register
struct IRECOG_RPYRAMID_PYM_W04_CFG1 {
	unsigned int cf_maskbyte_w04:3;		// [2:0]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_endian_w04:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_W04_SRAM_BASE Register
struct IRECOG_RPYRAMID_PYM_W04_SRAM_BASE {
	unsigned int cf_sram_base_w04:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W04_SRAM_SIZE Register
struct IRECOG_RPYRAMID_PYM_W04_SRAM_SIZE {
	unsigned int cf_sram_size_w04:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W04_INTL Register
struct IRECOG_RPYRAMID_PYM_W04_INTL {
	unsigned int cf_interval_w04:6;		// [5:0]
	unsigned int cf_init_interval_w04:6;		// [11:6]
	unsigned int reserved:4;		// [15:12]
	unsigned int cf_init_interval_period_w04:8;		// [23:16]
	unsigned int reserved2:8;		// [31:24]
};
 // rpyramid_PYM_W05_STADR Register
struct IRECOG_RPYRAMID_PYM_W05_STADR {
	unsigned int cf_stadr_w05:32;		// [31:0]
};
 // rpyramid_PYM_W05_ENDADR Register
struct IRECOG_RPYRAMID_PYM_W05_ENDADR {
	unsigned int cf_endadr_w05:32;		// [31:0]
};
 // rpyramid_PYM_W05_HEIGHT Register
struct IRECOG_RPYRAMID_PYM_W05_HEIGHT {
	unsigned int cf_height_w05:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W05_PITCH Register
struct IRECOG_RPYRAMID_PYM_W05_PITCH {
	unsigned int cf_pitch_w05:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // rpyramid_PYM_W05_CFG0 Register
struct IRECOG_RPYRAMID_PYM_W05_CFG0 {
	unsigned int reserved:8;		// [7:0]
	unsigned int cf_datawidth_w05:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_sram_th_w05:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_buf_th_w05:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_W05_CFG1 Register
struct IRECOG_RPYRAMID_PYM_W05_CFG1 {
	unsigned int cf_maskbyte_w05:3;		// [2:0]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_endian_w05:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_W05_SRAM_BASE Register
struct IRECOG_RPYRAMID_PYM_W05_SRAM_BASE {
	unsigned int cf_sram_base_w05:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W05_SRAM_SIZE Register
struct IRECOG_RPYRAMID_PYM_W05_SRAM_SIZE {
	unsigned int cf_sram_size_w05:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W05_INTL Register
struct IRECOG_RPYRAMID_PYM_W05_INTL {
	unsigned int cf_interval_w05:6;		// [5:0]
	unsigned int cf_init_interval_w05:6;		// [11:6]
	unsigned int reserved:4;		// [15:12]
	unsigned int cf_init_interval_period_w05:8;		// [23:16]
	unsigned int reserved2:8;		// [31:24]
};
 // rpyramid_PYM_W06_STADR Register
struct IRECOG_RPYRAMID_PYM_W06_STADR {
	unsigned int cf_stadr_w06:32;		// [31:0]
};
 // rpyramid_PYM_W06_ENDADR Register
struct IRECOG_RPYRAMID_PYM_W06_ENDADR {
	unsigned int cf_endadr_w06:32;		// [31:0]
};
 // rpyramid_PYM_W06_HEIGHT Register
struct IRECOG_RPYRAMID_PYM_W06_HEIGHT {
	unsigned int cf_height_w06:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W06_PITCH Register
struct IRECOG_RPYRAMID_PYM_W06_PITCH {
	unsigned int cf_pitch_w06:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // rpyramid_PYM_W06_CFG0 Register
struct IRECOG_RPYRAMID_PYM_W06_CFG0 {
	unsigned int reserved:8;		// [7:0]
	unsigned int cf_datawidth_w06:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_sram_th_w06:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_buf_th_w06:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_W06_CFG1 Register
struct IRECOG_RPYRAMID_PYM_W06_CFG1 {
	unsigned int cf_maskbyte_w06:3;		// [2:0]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_endian_w06:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_W06_SRAM_BASE Register
struct IRECOG_RPYRAMID_PYM_W06_SRAM_BASE {
	unsigned int cf_sram_base_w06:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W06_SRAM_SIZE Register
struct IRECOG_RPYRAMID_PYM_W06_SRAM_SIZE {
	unsigned int cf_sram_size_w06:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W06_INTL Register
struct IRECOG_RPYRAMID_PYM_W06_INTL {
	unsigned int cf_interval_w06:6;		// [5:0]
	unsigned int cf_init_interval_w06:6;		// [11:6]
	unsigned int reserved:4;		// [15:12]
	unsigned int cf_init_interval_period_w06:8;		// [23:16]
	unsigned int reserved2:8;		// [31:24]
};
 // rpyramid_PYM_W07_STADR Register
struct IRECOG_RPYRAMID_PYM_W07_STADR {
	unsigned int cf_stadr_w07:32;		// [31:0]
};
 // rpyramid_PYM_W07_ENDADR Register
struct IRECOG_RPYRAMID_PYM_W07_ENDADR {
	unsigned int cf_endadr_w07:32;		// [31:0]
};
 // rpyramid_PYM_W07_HEIGHT Register
struct IRECOG_RPYRAMID_PYM_W07_HEIGHT {
	unsigned int cf_height_w07:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W07_PITCH Register
struct IRECOG_RPYRAMID_PYM_W07_PITCH {
	unsigned int cf_pitch_w07:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // rpyramid_PYM_W07_CFG0 Register
struct IRECOG_RPYRAMID_PYM_W07_CFG0 {
	unsigned int reserved:8;		// [7:0]
	unsigned int cf_datawidth_w07:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_sram_th_w07:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_buf_th_w07:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_W07_CFG1 Register
struct IRECOG_RPYRAMID_PYM_W07_CFG1 {
	unsigned int cf_maskbyte_w07:3;		// [2:0]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_endian_w07:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_W07_SRAM_BASE Register
struct IRECOG_RPYRAMID_PYM_W07_SRAM_BASE {
	unsigned int cf_sram_base_w07:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W07_SRAM_SIZE Register
struct IRECOG_RPYRAMID_PYM_W07_SRAM_SIZE {
	unsigned int cf_sram_size_w07:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W07_INTL Register
struct IRECOG_RPYRAMID_PYM_W07_INTL {
	unsigned int cf_interval_w07:6;		// [5:0]
	unsigned int cf_init_interval_w07:6;		// [11:6]
	unsigned int reserved:4;		// [15:12]
	unsigned int cf_init_interval_period_w07:8;		// [23:16]
	unsigned int reserved2:8;		// [31:24]
};
 // rpyramid_PYM_W08_STADR Register
struct IRECOG_RPYRAMID_PYM_W08_STADR {
	unsigned int cf_stadr_w08:32;		// [31:0]
};
 // rpyramid_PYM_W08_ENDADR Register
struct IRECOG_RPYRAMID_PYM_W08_ENDADR {
	unsigned int cf_endadr_w08:32;		// [31:0]
};
 // rpyramid_PYM_W08_HEIGHT Register
struct IRECOG_RPYRAMID_PYM_W08_HEIGHT {
	unsigned int cf_height_w08:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W08_PITCH Register
struct IRECOG_RPYRAMID_PYM_W08_PITCH {
	unsigned int cf_pitch_w08:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // rpyramid_PYM_W08_CFG0 Register
struct IRECOG_RPYRAMID_PYM_W08_CFG0 {
	unsigned int reserved:8;		// [7:0]
	unsigned int cf_datawidth_w08:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_sram_th_w08:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_buf_th_w08:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_W08_CFG1 Register
struct IRECOG_RPYRAMID_PYM_W08_CFG1 {
	unsigned int cf_maskbyte_w08:3;		// [2:0]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_endian_w08:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_W08_SRAM_BASE Register
struct IRECOG_RPYRAMID_PYM_W08_SRAM_BASE {
	unsigned int cf_sram_base_w08:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W08_SRAM_SIZE Register
struct IRECOG_RPYRAMID_PYM_W08_SRAM_SIZE {
	unsigned int cf_sram_size_w08:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W08_INTL Register
struct IRECOG_RPYRAMID_PYM_W08_INTL {
	unsigned int cf_interval_w08:6;		// [5:0]
	unsigned int cf_init_interval_w08:6;		// [11:6]
	unsigned int reserved:4;		// [15:12]
	unsigned int cf_init_interval_period_w08:8;		// [23:16]
	unsigned int reserved2:8;		// [31:24]
};
 // rpyramid_PYM_W09_STADR Register
struct IRECOG_RPYRAMID_PYM_W09_STADR {
	unsigned int cf_stadr_w09:32;		// [31:0]
};
 // rpyramid_PYM_W09_ENDADR Register
struct IRECOG_RPYRAMID_PYM_W09_ENDADR {
	unsigned int cf_endadr_w09:32;		// [31:0]
};
 // rpyramid_PYM_W09_HEIGHT Register
struct IRECOG_RPYRAMID_PYM_W09_HEIGHT {
	unsigned int cf_height_w09:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W09_PITCH Register
struct IRECOG_RPYRAMID_PYM_W09_PITCH {
	unsigned int cf_pitch_w09:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // rpyramid_PYM_W09_CFG0 Register
struct IRECOG_RPYRAMID_PYM_W09_CFG0 {
	unsigned int reserved:8;		// [7:0]
	unsigned int cf_datawidth_w09:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_sram_th_w09:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_buf_th_w09:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_W09_CFG1 Register
struct IRECOG_RPYRAMID_PYM_W09_CFG1 {
	unsigned int cf_maskbyte_w09:3;		// [2:0]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_endian_w09:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_W09_SRAM_BASE Register
struct IRECOG_RPYRAMID_PYM_W09_SRAM_BASE {
	unsigned int cf_sram_base_w09:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W09_SRAM_SIZE Register
struct IRECOG_RPYRAMID_PYM_W09_SRAM_SIZE {
	unsigned int cf_sram_size_w09:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W09_INTL Register
struct IRECOG_RPYRAMID_PYM_W09_INTL {
	unsigned int cf_interval_w09:6;		// [5:0]
	unsigned int cf_init_interval_w09:6;		// [11:6]
	unsigned int reserved:4;		// [15:12]
	unsigned int cf_init_interval_period_w09:8;		// [23:16]
	unsigned int reserved2:8;		// [31:24]
};
 // rpyramid_PYM_W10_STADR Register
struct IRECOG_RPYRAMID_PYM_W10_STADR {
	unsigned int cf_stadr_w10:32;		// [31:0]
};
 // rpyramid_PYM_W10_ENDADR Register
struct IRECOG_RPYRAMID_PYM_W10_ENDADR {
	unsigned int cf_endadr_w10:32;		// [31:0]
};
 // rpyramid_PYM_W10_HEIGHT Register
struct IRECOG_RPYRAMID_PYM_W10_HEIGHT {
	unsigned int cf_height_w10:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W10_PITCH Register
struct IRECOG_RPYRAMID_PYM_W10_PITCH {
	unsigned int cf_pitch_w10:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // rpyramid_PYM_W10_CFG0 Register
struct IRECOG_RPYRAMID_PYM_W10_CFG0 {
	unsigned int reserved:8;		// [7:0]
	unsigned int cf_datawidth_w10:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_sram_th_w10:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_buf_th_w10:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_W10_CFG1 Register
struct IRECOG_RPYRAMID_PYM_W10_CFG1 {
	unsigned int cf_maskbyte_w10:3;		// [2:0]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_endian_w10:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_W10_SRAM_BASE Register
struct IRECOG_RPYRAMID_PYM_W10_SRAM_BASE {
	unsigned int cf_sram_base_w10:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W10_SRAM_SIZE Register
struct IRECOG_RPYRAMID_PYM_W10_SRAM_SIZE {
	unsigned int cf_sram_size_w10:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W10_INTL Register
struct IRECOG_RPYRAMID_PYM_W10_INTL {
	unsigned int cf_interval_w10:6;		// [5:0]
	unsigned int cf_init_interval_w10:6;		// [11:6]
	unsigned int reserved:4;		// [15:12]
	unsigned int cf_init_interval_period_w10:8;		// [23:16]
	unsigned int reserved2:8;		// [31:24]
};
 // rpyramid_PYM_W11_STADR Register
struct IRECOG_RPYRAMID_PYM_W11_STADR {
	unsigned int cf_stadr_w11:32;		// [31:0]
};
 // rpyramid_PYM_W11_ENDADR Register
struct IRECOG_RPYRAMID_PYM_W11_ENDADR {
	unsigned int cf_endadr_w11:32;		// [31:0]
};
 // rpyramid_PYM_W11_HEIGHT Register
struct IRECOG_RPYRAMID_PYM_W11_HEIGHT {
	unsigned int cf_height_w11:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W11_PITCH Register
struct IRECOG_RPYRAMID_PYM_W11_PITCH {
	unsigned int cf_pitch_w11:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // rpyramid_PYM_W11_CFG0 Register
struct IRECOG_RPYRAMID_PYM_W11_CFG0 {
	unsigned int reserved:8;		// [7:0]
	unsigned int cf_datawidth_w11:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_sram_th_w11:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_buf_th_w11:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_W11_CFG1 Register
struct IRECOG_RPYRAMID_PYM_W11_CFG1 {
	unsigned int cf_maskbyte_w11:3;		// [2:0]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_endian_w11:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_W11_SRAM_BASE Register
struct IRECOG_RPYRAMID_PYM_W11_SRAM_BASE {
	unsigned int cf_sram_base_w11:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W11_SRAM_SIZE Register
struct IRECOG_RPYRAMID_PYM_W11_SRAM_SIZE {
	unsigned int cf_sram_size_w11:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W11_INTL Register
struct IRECOG_RPYRAMID_PYM_W11_INTL {
	unsigned int cf_interval_w11:6;		// [5:0]
	unsigned int cf_init_interval_w11:6;		// [11:6]
	unsigned int reserved:4;		// [15:12]
	unsigned int cf_init_interval_period_w11:8;		// [23:16]
	unsigned int reserved2:8;		// [31:24]
};
 // rpyramid_PYM_R_ENABLE_BUF Register
struct IRECOG_RPYRAMID_PYM_R_ENABLE_BUF {
	unsigned int cf_enable_r00:1;		// [0]
	unsigned int cf_enable_r01:1;		// [1]
	unsigned int cf_enable_r02:1;		// [2]
	unsigned int reserved:29;		// [31:3]
};
 // rpyramid_PYM_W_ENABLE_BUF Register
struct IRECOG_RPYRAMID_PYM_W_ENABLE_BUF {
	unsigned int cf_enable_w00:1;		// [0]
	unsigned int cf_enable_w01:1;		// [1]
	unsigned int cf_enable_w02:1;		// [2]
	unsigned int cf_enable_w03:1;		// [3]
	unsigned int cf_enable_w04:1;		// [4]
	unsigned int cf_enable_w05:1;		// [5]
	unsigned int cf_enable_w06:1;		// [6]
	unsigned int cf_enable_w07:1;		// [7]
	unsigned int cf_enable_w08:1;		// [8]
	unsigned int cf_enable_w09:1;		// [9]
	unsigned int cf_enable_w10:1;		// [10]
	unsigned int cf_enable_w11:1;		// [11]
	unsigned int reserved:20;		// [31:12]
};
 // rpyramid_PYM_T_ENABLE_BUF Register
struct IRECOG_RPYRAMID_PYM_T_ENABLE_BUF {
	unsigned int cf_enable_t00:1;		// [0]
	unsigned int cf_enable_t01:1;		// [1]
	unsigned int cf_enable_t02:1;		// [2]
	unsigned int cf_enable_t03:1;		// [3]
	unsigned int cf_enable_t04:1;		// [4]
	unsigned int cf_enable_t05:1;		// [5]
	unsigned int cf_enable_t06:1;		// [6]
	unsigned int cf_enable_t07:1;		// [7]
	unsigned int cf_enable_t08:1;		// [8]
	unsigned int cf_enable_t09:1;		// [9]
	unsigned int cf_enable_t10:1;		// [10]
	unsigned int cf_enable_t11:1;		// [11]
	unsigned int cf_enable_t12:1;		// [12]
	unsigned int cf_enable_t13:1;		// [13]
	unsigned int cf_enable_t14:1;		// [14]
	unsigned int cf_enable_t15:1;		// [15]
	unsigned int reserved:16;		// [31:16]
};
 // rpyramid_PYM_T00_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_T00_STADR_BUF {
	unsigned int cf_td_stadr_t00:32;		// [31:0]
};
 // rpyramid_PYM_T00_SIZE_BUF Register
struct IRECOG_RPYRAMID_PYM_T00_SIZE_BUF {
	unsigned int cf_td_size_t00:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_T01_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_T01_STADR_BUF {
	unsigned int cf_td_stadr_t01:32;		// [31:0]
};
 // rpyramid_PYM_T01_SIZE_BUF Register
struct IRECOG_RPYRAMID_PYM_T01_SIZE_BUF {
	unsigned int cf_td_size_t01:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_T02_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_T02_STADR_BUF {
	unsigned int cf_td_stadr_t02:32;		// [31:0]
};
 // rpyramid_PYM_T02_SIZE_BUF Register
struct IRECOG_RPYRAMID_PYM_T02_SIZE_BUF {
	unsigned int cf_td_size_t02:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_T03_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_T03_STADR_BUF {
	unsigned int cf_td_stadr_t03:32;		// [31:0]
};
 // rpyramid_PYM_T03_SIZE_BUF Register
struct IRECOG_RPYRAMID_PYM_T03_SIZE_BUF {
	unsigned int cf_td_size_t03:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_T04_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_T04_STADR_BUF {
	unsigned int cf_td_stadr_t04:32;		// [31:0]
};
 // rpyramid_PYM_T04_SIZE_BUF Register
struct IRECOG_RPYRAMID_PYM_T04_SIZE_BUF {
	unsigned int cf_td_size_t04:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_T05_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_T05_STADR_BUF {
	unsigned int cf_td_stadr_t05:32;		// [31:0]
};
 // rpyramid_PYM_T05_SIZE_BUF Register
struct IRECOG_RPYRAMID_PYM_T05_SIZE_BUF {
	unsigned int cf_td_size_t05:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_T06_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_T06_STADR_BUF {
	unsigned int cf_td_stadr_t06:32;		// [31:0]
};
 // rpyramid_PYM_T06_SIZE_BUF Register
struct IRECOG_RPYRAMID_PYM_T06_SIZE_BUF {
	unsigned int cf_td_size_t06:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_T07_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_T07_STADR_BUF {
	unsigned int cf_td_stadr_t07:32;		// [31:0]
};
 // rpyramid_PYM_T07_SIZE_BUF Register
struct IRECOG_RPYRAMID_PYM_T07_SIZE_BUF {
	unsigned int cf_td_size_t07:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_T08_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_T08_STADR_BUF {
	unsigned int cf_td_stadr_t08:32;		// [31:0]
};
 // rpyramid_PYM_T08_SIZE_BUF Register
struct IRECOG_RPYRAMID_PYM_T08_SIZE_BUF {
	unsigned int cf_td_size_t08:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_T09_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_T09_STADR_BUF {
	unsigned int cf_td_stadr_t09:32;		// [31:0]
};
 // rpyramid_PYM_T09_SIZE_BUF Register
struct IRECOG_RPYRAMID_PYM_T09_SIZE_BUF {
	unsigned int cf_td_size_t09:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_T10_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_T10_STADR_BUF {
	unsigned int cf_td_stadr_t10:32;		// [31:0]
};
 // rpyramid_PYM_T10_SIZE_BUF Register
struct IRECOG_RPYRAMID_PYM_T10_SIZE_BUF {
	unsigned int cf_td_size_t10:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_T11_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_T11_STADR_BUF {
	unsigned int cf_td_stadr_t11:32;		// [31:0]
};
 // rpyramid_PYM_T11_SIZE_BUF Register
struct IRECOG_RPYRAMID_PYM_T11_SIZE_BUF {
	unsigned int cf_td_size_t11:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_T12_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_T12_STADR_BUF {
	unsigned int cf_td_stadr_t12:32;		// [31:0]
};
 // rpyramid_PYM_T12_SIZE_BUF Register
struct IRECOG_RPYRAMID_PYM_T12_SIZE_BUF {
	unsigned int cf_td_size_t12:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_T13_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_T13_STADR_BUF {
	unsigned int cf_td_stadr_t13:32;		// [31:0]
};
 // rpyramid_PYM_T13_SIZE_BUF Register
struct IRECOG_RPYRAMID_PYM_T13_SIZE_BUF {
	unsigned int cf_td_size_t13:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_T14_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_T14_STADR_BUF {
	unsigned int cf_td_stadr_t14:32;		// [31:0]
};
 // rpyramid_PYM_T14_SIZE_BUF Register
struct IRECOG_RPYRAMID_PYM_T14_SIZE_BUF {
	unsigned int cf_td_size_t14:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_T15_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_T15_STADR_BUF {
	unsigned int cf_td_stadr_t15:32;		// [31:0]
};
 // rpyramid_PYM_T15_SIZE_BUF Register
struct IRECOG_RPYRAMID_PYM_T15_SIZE_BUF {
	unsigned int cf_td_size_t15:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // rpyramid_PYM_R00_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_R00_STADR_BUF {
	unsigned int cf_stadr_r00:32;		// [31:0]
};
 // rpyramid_PYM_R00_ENDADR_BUF Register
struct IRECOG_RPYRAMID_PYM_R00_ENDADR_BUF {
	unsigned int cf_endadr_r00:32;		// [31:0]
};
 // rpyramid_PYM_R00_HEIGHT_BUF Register
struct IRECOG_RPYRAMID_PYM_R00_HEIGHT_BUF {
	unsigned int cf_height_r00:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_R00_PITCH_BUF Register
struct IRECOG_RPYRAMID_PYM_R00_PITCH_BUF {
	unsigned int cf_pitch_r00:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // rpyramid_PYM_R00_CFG0_BUF Register
struct IRECOG_RPYRAMID_PYM_R00_CFG0_BUF {
	unsigned int reserved:8;		// [7:0]
	unsigned int cf_datawidth_r00:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_sram_th_r00:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_buf_th_r00:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_R00_CFG1_BUF Register
struct IRECOG_RPYRAMID_PYM_R00_CFG1_BUF {
	unsigned int reserved:16;		// [15:0]
	unsigned int cf_endian_r00:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_R01_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_R01_STADR_BUF {
	unsigned int cf_stadr_r01:32;		// [31:0]
};
 // rpyramid_PYM_R01_ENDADR_BUF Register
struct IRECOG_RPYRAMID_PYM_R01_ENDADR_BUF {
	unsigned int cf_endadr_r01:32;		// [31:0]
};
 // rpyramid_PYM_R01_HEIGHT_BUF Register
struct IRECOG_RPYRAMID_PYM_R01_HEIGHT_BUF {
	unsigned int cf_height_r01:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_R01_PITCH_BUF Register
struct IRECOG_RPYRAMID_PYM_R01_PITCH_BUF {
	unsigned int cf_pitch_r01:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // rpyramid_PYM_R01_CFG0_BUF Register
struct IRECOG_RPYRAMID_PYM_R01_CFG0_BUF {
	unsigned int reserved:8;		// [7:0]
	unsigned int cf_datawidth_r01:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_sram_th_r01:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_buf_th_r01:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_R01_CFG1_BUF Register
struct IRECOG_RPYRAMID_PYM_R01_CFG1_BUF {
	unsigned int reserved:16;		// [15:0]
	unsigned int cf_endian_r01:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_R02_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_R02_STADR_BUF {
	unsigned int cf_stadr_r02:32;		// [31:0]
};
 // rpyramid_PYM_R02_ENDADR_BUF Register
struct IRECOG_RPYRAMID_PYM_R02_ENDADR_BUF {
	unsigned int cf_endadr_r02:32;		// [31:0]
};
 // rpyramid_PYM_R02_HEIGHT_BUF Register
struct IRECOG_RPYRAMID_PYM_R02_HEIGHT_BUF {
	unsigned int cf_height_r02:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_R02_PITCH_BUF Register
struct IRECOG_RPYRAMID_PYM_R02_PITCH_BUF {
	unsigned int cf_pitch_r02:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // rpyramid_PYM_R02_CFG0_BUF Register
struct IRECOG_RPYRAMID_PYM_R02_CFG0_BUF {
	unsigned int reserved:8;		// [7:0]
	unsigned int cf_datawidth_r02:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_sram_th_r02:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_buf_th_r02:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_R02_CFG1_BUF Register
struct IRECOG_RPYRAMID_PYM_R02_CFG1_BUF {
	unsigned int reserved:16;		// [15:0]
	unsigned int cf_endian_r02:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_W00_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_W00_STADR_BUF {
	unsigned int cf_stadr_w00:32;		// [31:0]
};
 // rpyramid_PYM_W00_ENDADR_BUF Register
struct IRECOG_RPYRAMID_PYM_W00_ENDADR_BUF {
	unsigned int cf_endadr_w00:32;		// [31:0]
};
 // rpyramid_PYM_W00_HEIGHT_BUF Register
struct IRECOG_RPYRAMID_PYM_W00_HEIGHT_BUF {
	unsigned int cf_height_w00:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W00_PITCH_BUF Register
struct IRECOG_RPYRAMID_PYM_W00_PITCH_BUF {
	unsigned int cf_pitch_w00:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // rpyramid_PYM_W00_CFG0_BUF Register
struct IRECOG_RPYRAMID_PYM_W00_CFG0_BUF {
	unsigned int reserved:8;		// [7:0]
	unsigned int cf_datawidth_w00:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_sram_th_w00:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_buf_th_w00:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_W00_CFG1_BUF Register
struct IRECOG_RPYRAMID_PYM_W00_CFG1_BUF {
	unsigned int cf_maskbyte_w00:3;		// [2:0]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_endian_w00:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_W01_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_W01_STADR_BUF {
	unsigned int cf_stadr_w01:32;		// [31:0]
};
 // rpyramid_PYM_W01_ENDADR_BUF Register
struct IRECOG_RPYRAMID_PYM_W01_ENDADR_BUF {
	unsigned int cf_endadr_w01:32;		// [31:0]
};
 // rpyramid_PYM_W01_HEIGHT_BUF Register
struct IRECOG_RPYRAMID_PYM_W01_HEIGHT_BUF {
	unsigned int cf_height_w01:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W01_PITCH_BUF Register
struct IRECOG_RPYRAMID_PYM_W01_PITCH_BUF {
	unsigned int cf_pitch_w01:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // rpyramid_PYM_W01_CFG0_BUF Register
struct IRECOG_RPYRAMID_PYM_W01_CFG0_BUF {
	unsigned int reserved:8;		// [7:0]
	unsigned int cf_datawidth_w01:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_sram_th_w01:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_buf_th_w01:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_W01_CFG1_BUF Register
struct IRECOG_RPYRAMID_PYM_W01_CFG1_BUF {
	unsigned int cf_maskbyte_w01:3;		// [2:0]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_endian_w01:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_W02_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_W02_STADR_BUF {
	unsigned int cf_stadr_w02:32;		// [31:0]
};
 // rpyramid_PYM_W02_ENDADR_BUF Register
struct IRECOG_RPYRAMID_PYM_W02_ENDADR_BUF {
	unsigned int cf_endadr_w02:32;		// [31:0]
};
 // rpyramid_PYM_W02_HEIGHT_BUF Register
struct IRECOG_RPYRAMID_PYM_W02_HEIGHT_BUF {
	unsigned int cf_height_w02:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W02_PITCH_BUF Register
struct IRECOG_RPYRAMID_PYM_W02_PITCH_BUF {
	unsigned int cf_pitch_w02:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // rpyramid_PYM_W02_CFG0_BUF Register
struct IRECOG_RPYRAMID_PYM_W02_CFG0_BUF {
	unsigned int reserved:8;		// [7:0]
	unsigned int cf_datawidth_w02:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_sram_th_w02:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_buf_th_w02:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_W02_CFG1_BUF Register
struct IRECOG_RPYRAMID_PYM_W02_CFG1_BUF {
	unsigned int cf_maskbyte_w02:3;		// [2:0]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_endian_w02:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_W03_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_W03_STADR_BUF {
	unsigned int cf_stadr_w03:32;		// [31:0]
};
 // rpyramid_PYM_W03_ENDADR_BUF Register
struct IRECOG_RPYRAMID_PYM_W03_ENDADR_BUF {
	unsigned int cf_endadr_w03:32;		// [31:0]
};
 // rpyramid_PYM_W03_HEIGHT_BUF Register
struct IRECOG_RPYRAMID_PYM_W03_HEIGHT_BUF {
	unsigned int cf_height_w03:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W03_PITCH_BUF Register
struct IRECOG_RPYRAMID_PYM_W03_PITCH_BUF {
	unsigned int cf_pitch_w03:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // rpyramid_PYM_W03_CFG0_BUF Register
struct IRECOG_RPYRAMID_PYM_W03_CFG0_BUF {
	unsigned int reserved:8;		// [7:0]
	unsigned int cf_datawidth_w03:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_sram_th_w03:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_buf_th_w03:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_W03_CFG1_BUF Register
struct IRECOG_RPYRAMID_PYM_W03_CFG1_BUF {
	unsigned int cf_maskbyte_w03:3;		// [2:0]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_endian_w03:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_W04_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_W04_STADR_BUF {
	unsigned int cf_stadr_w04:32;		// [31:0]
};
 // rpyramid_PYM_W04_ENDADR_BUF Register
struct IRECOG_RPYRAMID_PYM_W04_ENDADR_BUF {
	unsigned int cf_endadr_w04:32;		// [31:0]
};
 // rpyramid_PYM_W04_HEIGHT_BUF Register
struct IRECOG_RPYRAMID_PYM_W04_HEIGHT_BUF {
	unsigned int cf_height_w04:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W04_PITCH_BUF Register
struct IRECOG_RPYRAMID_PYM_W04_PITCH_BUF {
	unsigned int cf_pitch_w04:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // rpyramid_PYM_W04_CFG0_BUF Register
struct IRECOG_RPYRAMID_PYM_W04_CFG0_BUF {
	unsigned int reserved:8;		// [7:0]
	unsigned int cf_datawidth_w04:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_sram_th_w04:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_buf_th_w04:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_W04_CFG1_BUF Register
struct IRECOG_RPYRAMID_PYM_W04_CFG1_BUF {
	unsigned int cf_maskbyte_w04:3;		// [2:0]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_endian_w04:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_W05_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_W05_STADR_BUF {
	unsigned int cf_stadr_w05:32;		// [31:0]
};
 // rpyramid_PYM_W05_ENDADR_BUF Register
struct IRECOG_RPYRAMID_PYM_W05_ENDADR_BUF {
	unsigned int cf_endadr_w05:32;		// [31:0]
};
 // rpyramid_PYM_W05_HEIGHT_BUF Register
struct IRECOG_RPYRAMID_PYM_W05_HEIGHT_BUF {
	unsigned int cf_height_w05:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W05_PITCH_BUF Register
struct IRECOG_RPYRAMID_PYM_W05_PITCH_BUF {
	unsigned int cf_pitch_w05:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // rpyramid_PYM_W05_CFG0_BUF Register
struct IRECOG_RPYRAMID_PYM_W05_CFG0_BUF {
	unsigned int reserved:8;		// [7:0]
	unsigned int cf_datawidth_w05:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_sram_th_w05:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_buf_th_w05:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_W05_CFG1_BUF Register
struct IRECOG_RPYRAMID_PYM_W05_CFG1_BUF {
	unsigned int cf_maskbyte_w05:3;		// [2:0]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_endian_w05:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_W06_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_W06_STADR_BUF {
	unsigned int cf_stadr_w06:32;		// [31:0]
};
 // rpyramid_PYM_W06_ENDADR_BUF Register
struct IRECOG_RPYRAMID_PYM_W06_ENDADR_BUF {
	unsigned int cf_endadr_w06:32;		// [31:0]
};
 // rpyramid_PYM_W06_HEIGHT_BUF Register
struct IRECOG_RPYRAMID_PYM_W06_HEIGHT_BUF {
	unsigned int cf_height_w06:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W06_PITCH_BUF Register
struct IRECOG_RPYRAMID_PYM_W06_PITCH_BUF {
	unsigned int cf_pitch_w06:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // rpyramid_PYM_W06_CFG0_BUF Register
struct IRECOG_RPYRAMID_PYM_W06_CFG0_BUF {
	unsigned int reserved:8;		// [7:0]
	unsigned int cf_datawidth_w06:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_sram_th_w06:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_buf_th_w06:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_W06_CFG1_BUF Register
struct IRECOG_RPYRAMID_PYM_W06_CFG1_BUF {
	unsigned int cf_maskbyte_w06:3;		// [2:0]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_endian_w06:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_W07_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_W07_STADR_BUF {
	unsigned int cf_stadr_w07:32;		// [31:0]
};
 // rpyramid_PYM_W07_ENDADR_BUF Register
struct IRECOG_RPYRAMID_PYM_W07_ENDADR_BUF {
	unsigned int cf_endadr_w07:32;		// [31:0]
};
 // rpyramid_PYM_W07_HEIGHT_BUF Register
struct IRECOG_RPYRAMID_PYM_W07_HEIGHT_BUF {
	unsigned int cf_height_w07:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W07_PITCH_BUF Register
struct IRECOG_RPYRAMID_PYM_W07_PITCH_BUF {
	unsigned int cf_pitch_w07:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // rpyramid_PYM_W07_CFG0_BUF Register
struct IRECOG_RPYRAMID_PYM_W07_CFG0_BUF {
	unsigned int reserved:8;		// [7:0]
	unsigned int cf_datawidth_w07:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_sram_th_w07:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_buf_th_w07:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_W07_CFG1_BUF Register
struct IRECOG_RPYRAMID_PYM_W07_CFG1_BUF {
	unsigned int cf_maskbyte_w07:3;		// [2:0]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_endian_w07:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_W08_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_W08_STADR_BUF {
	unsigned int cf_stadr_w08:32;		// [31:0]
};
 // rpyramid_PYM_W08_ENDADR_BUF Register
struct IRECOG_RPYRAMID_PYM_W08_ENDADR_BUF {
	unsigned int cf_endadr_w08:32;		// [31:0]
};
 // rpyramid_PYM_W08_HEIGHT_BUF Register
struct IRECOG_RPYRAMID_PYM_W08_HEIGHT_BUF {
	unsigned int cf_height_w08:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W08_PITCH_BUF Register
struct IRECOG_RPYRAMID_PYM_W08_PITCH_BUF {
	unsigned int cf_pitch_w08:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // rpyramid_PYM_W08_CFG0_BUF Register
struct IRECOG_RPYRAMID_PYM_W08_CFG0_BUF {
	unsigned int reserved:8;		// [7:0]
	unsigned int cf_datawidth_w08:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_sram_th_w08:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_buf_th_w08:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_W08_CFG1_BUF Register
struct IRECOG_RPYRAMID_PYM_W08_CFG1_BUF {
	unsigned int cf_maskbyte_w08:3;		// [2:0]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_endian_w08:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_W09_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_W09_STADR_BUF {
	unsigned int cf_stadr_w09:32;		// [31:0]
};
 // rpyramid_PYM_W09_ENDADR_BUF Register
struct IRECOG_RPYRAMID_PYM_W09_ENDADR_BUF {
	unsigned int cf_endadr_w09:32;		// [31:0]
};
 // rpyramid_PYM_W09_HEIGHT_BUF Register
struct IRECOG_RPYRAMID_PYM_W09_HEIGHT_BUF {
	unsigned int cf_height_w09:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W09_PITCH_BUF Register
struct IRECOG_RPYRAMID_PYM_W09_PITCH_BUF {
	unsigned int cf_pitch_w09:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // rpyramid_PYM_W09_CFG0_BUF Register
struct IRECOG_RPYRAMID_PYM_W09_CFG0_BUF {
	unsigned int reserved:8;		// [7:0]
	unsigned int cf_datawidth_w09:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_sram_th_w09:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_buf_th_w09:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_W09_CFG1_BUF Register
struct IRECOG_RPYRAMID_PYM_W09_CFG1_BUF {
	unsigned int cf_maskbyte_w09:3;		// [2:0]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_endian_w09:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_W10_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_W10_STADR_BUF {
	unsigned int cf_stadr_w10:32;		// [31:0]
};
 // rpyramid_PYM_W10_ENDADR_BUF Register
struct IRECOG_RPYRAMID_PYM_W10_ENDADR_BUF {
	unsigned int cf_endadr_w10:32;		// [31:0]
};
 // rpyramid_PYM_W10_HEIGHT_BUF Register
struct IRECOG_RPYRAMID_PYM_W10_HEIGHT_BUF {
	unsigned int cf_height_w10:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W10_PITCH_BUF Register
struct IRECOG_RPYRAMID_PYM_W10_PITCH_BUF {
	unsigned int cf_pitch_w10:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // rpyramid_PYM_W10_CFG0_BUF Register
struct IRECOG_RPYRAMID_PYM_W10_CFG0_BUF {
	unsigned int reserved:8;		// [7:0]
	unsigned int cf_datawidth_w10:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_sram_th_w10:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_buf_th_w10:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_W10_CFG1_BUF Register
struct IRECOG_RPYRAMID_PYM_W10_CFG1_BUF {
	unsigned int cf_maskbyte_w10:3;		// [2:0]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_endian_w10:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_W11_STADR_BUF Register
struct IRECOG_RPYRAMID_PYM_W11_STADR_BUF {
	unsigned int cf_stadr_w11:32;		// [31:0]
};
 // rpyramid_PYM_W11_ENDADR_BUF Register
struct IRECOG_RPYRAMID_PYM_W11_ENDADR_BUF {
	unsigned int cf_endadr_w11:32;		// [31:0]
};
 // rpyramid_PYM_W11_HEIGHT_BUF Register
struct IRECOG_RPYRAMID_PYM_W11_HEIGHT_BUF {
	unsigned int cf_height_w11:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W11_PITCH_BUF Register
struct IRECOG_RPYRAMID_PYM_W11_PITCH_BUF {
	unsigned int cf_pitch_w11:14;		// [13:0]
	unsigned int reserved:18;		// [31:14]
};
 // rpyramid_PYM_W11_CFG0_BUF Register
struct IRECOG_RPYRAMID_PYM_W11_CFG0_BUF {
	unsigned int reserved:8;		// [7:0]
	unsigned int cf_datawidth_w11:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int cf_sram_th_w11:5;		// [20:16]
	unsigned int reserved3:3;		// [23:21]
	unsigned int cf_buf_th_w11:1;		// [24]
	unsigned int reserved4:7;		// [31:25]
};
 // rpyramid_PYM_W11_CFG1_BUF Register
struct IRECOG_RPYRAMID_PYM_W11_CFG1_BUF {
	unsigned int cf_maskbyte_w11:3;		// [2:0]
	unsigned int reserved:13;		// [15:3]
	unsigned int cf_endian_w11:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_STATUS Register
struct IRECOG_RPYRAMID_PYM_STATUS {
	unsigned int mb_error_region:1;		// [0]
	unsigned int mb_error_inband:1;		// [1]
	unsigned int reserved:6;		// [7:2]
	unsigned int cmd_num:3;		// [10:8]
	unsigned int reserved2:5;		// [15:11]
	unsigned int accmd_num:4;		// [19:16]
	unsigned int reserved3:12;		// [31:20]
};
 // rpyramid_PYM_INT Register
struct IRECOG_RPYRAMID_PYM_INT {
	unsigned int int_g00:1;		// [0]
	unsigned int reserved:14;		// [14:1]
	unsigned int mb_err:1;		// [15]
	unsigned int abort_g00:1;		// [16]
	unsigned int reserved2:15;		// [31:17]
};
 // rpyramid_PYM_R_SRAM Register
struct IRECOG_RPYRAMID_PYM_R_SRAM {
	unsigned int empty_r00:1;		// [0]
	unsigned int empty_r01:1;		// [1]
	unsigned int empty_r02:1;		// [2]
	unsigned int reserved:29;		// [31:3]
};
 // rpyramid_PYM_W_SRAM Register
struct IRECOG_RPYRAMID_PYM_W_SRAM {
	unsigned int full_w00:1;		// [0]
	unsigned int full_w01:1;		// [1]
	unsigned int full_w02:1;		// [2]
	unsigned int full_w03:1;		// [3]
	unsigned int full_w04:1;		// [4]
	unsigned int full_w05:1;		// [5]
	unsigned int full_w06:1;		// [6]
	unsigned int full_w07:1;		// [7]
	unsigned int full_w08:1;		// [8]
	unsigned int full_w09:1;		// [9]
	unsigned int full_w10:1;		// [10]
	unsigned int full_w11:1;		// [11]
	unsigned int reserved:20;		// [31:12]
};
 // rpyramid_PYM_R_STOP Register
struct IRECOG_RPYRAMID_PYM_R_STOP {
	unsigned int abort_r00:1;		// [0]
	unsigned int abort_r01:1;		// [1]
	unsigned int abort_r02:1;		// [2]
	unsigned int reserved:29;		// [31:3]
};
 // rpyramid_PYM_W_STOP Register
struct IRECOG_RPYRAMID_PYM_W_STOP {
	unsigned int abort_w00:1;		// [0]
	unsigned int abort_w01:1;		// [1]
	unsigned int abort_w02:1;		// [2]
	unsigned int abort_w03:1;		// [3]
	unsigned int abort_w04:1;		// [4]
	unsigned int abort_w05:1;		// [5]
	unsigned int abort_w06:1;		// [6]
	unsigned int abort_w07:1;		// [7]
	unsigned int abort_w08:1;		// [8]
	unsigned int abort_w09:1;		// [9]
	unsigned int abort_w10:1;		// [10]
	unsigned int abort_w11:1;		// [11]
	unsigned int reserved:20;		// [31:12]
};
 // rpyramid_PYM_R_RUN Register
struct IRECOG_RPYRAMID_PYM_R_RUN {
	unsigned int run_r00:1;		// [0]
	unsigned int run_r01:1;		// [1]
	unsigned int run_r02:1;		// [2]
	unsigned int reserved:29;		// [31:3]
};
 // rpyramid_PYM_W_RUN Register
struct IRECOG_RPYRAMID_PYM_W_RUN {
	unsigned int run_w00:1;		// [0]
	unsigned int run_w01:1;		// [1]
	unsigned int run_w02:1;		// [2]
	unsigned int run_w03:1;		// [3]
	unsigned int run_w04:1;		// [4]
	unsigned int run_w05:1;		// [5]
	unsigned int run_w06:1;		// [6]
	unsigned int run_w07:1;		// [7]
	unsigned int run_w08:1;		// [8]
	unsigned int run_w09:1;		// [9]
	unsigned int run_w10:1;		// [10]
	unsigned int run_w11:1;		// [11]
	unsigned int reserved:20;		// [31:12]
};
 // rpyramid_PYM_T_RUN Register
struct IRECOG_RPYRAMID_PYM_T_RUN {
	unsigned int run_tp00:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // rpyramid_PYM_D00_STADRMON Register
struct IRECOG_RPYRAMID_PYM_D00_STADRMON {
	unsigned int last_accepted_adr_d00:32;		// [31:0]
};
 // rpyramid_PYM_T00_STADRMON Register
struct IRECOG_RPYRAMID_PYM_T00_STADRMON {
	unsigned int last_accepted_adr_t00:32;		// [31:0]
};
 // rpyramid_PYM_R00_LINEMON Register
struct IRECOG_RPYRAMID_PYM_R00_LINEMON {
	unsigned int linecount_r00:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_R00_STADRMON Register
struct IRECOG_RPYRAMID_PYM_R00_STADRMON {
	unsigned int last_accepted_adr_r00:32;		// [31:0]
};
 // rpyramid_PYM_R01_LINEMON Register
struct IRECOG_RPYRAMID_PYM_R01_LINEMON {
	unsigned int linecount_r01:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_R01_STADRMON Register
struct IRECOG_RPYRAMID_PYM_R01_STADRMON {
	unsigned int last_accepted_adr_r01:32;		// [31:0]
};
 // rpyramid_PYM_R02_LINEMON Register
struct IRECOG_RPYRAMID_PYM_R02_LINEMON {
	unsigned int linecount_r02:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_R02_STADRMON Register
struct IRECOG_RPYRAMID_PYM_R02_STADRMON {
	unsigned int last_accepted_adr_r02:32;		// [31:0]
};
 // rpyramid_PYM_W00_LINEMON Register
struct IRECOG_RPYRAMID_PYM_W00_LINEMON {
	unsigned int linecount_w00:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W00_STADRMON Register
struct IRECOG_RPYRAMID_PYM_W00_STADRMON {
	unsigned int last_accepted_adr_w00:32;		// [31:0]
};
 // rpyramid_PYM_W01_LINEMON Register
struct IRECOG_RPYRAMID_PYM_W01_LINEMON {
	unsigned int linecount_w01:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W01_STADRMON Register
struct IRECOG_RPYRAMID_PYM_W01_STADRMON {
	unsigned int last_accepted_adr_w01:32;		// [31:0]
};
 // rpyramid_PYM_W02_LINEMON Register
struct IRECOG_RPYRAMID_PYM_W02_LINEMON {
	unsigned int linecount_w02:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W02_STADRMON Register
struct IRECOG_RPYRAMID_PYM_W02_STADRMON {
	unsigned int last_accepted_adr_w02:32;		// [31:0]
};
 // rpyramid_PYM_W03_LINEMON Register
struct IRECOG_RPYRAMID_PYM_W03_LINEMON {
	unsigned int linecount_w03:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W03_STADRMON Register
struct IRECOG_RPYRAMID_PYM_W03_STADRMON {
	unsigned int last_accepted_adr_w03:32;		// [31:0]
};
 // rpyramid_PYM_W04_LINEMON Register
struct IRECOG_RPYRAMID_PYM_W04_LINEMON {
	unsigned int linecount_w04:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W04_STADRMON Register
struct IRECOG_RPYRAMID_PYM_W04_STADRMON {
	unsigned int last_accepted_adr_w04:32;		// [31:0]
};
 // rpyramid_PYM_W05_LINEMON Register
struct IRECOG_RPYRAMID_PYM_W05_LINEMON {
	unsigned int linecount_w05:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W05_STADRMON Register
struct IRECOG_RPYRAMID_PYM_W05_STADRMON {
	unsigned int last_accepted_adr_w05:32;		// [31:0]
};
 // rpyramid_PYM_W06_LINEMON Register
struct IRECOG_RPYRAMID_PYM_W06_LINEMON {
	unsigned int linecount_w06:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W06_STADRMON Register
struct IRECOG_RPYRAMID_PYM_W06_STADRMON {
	unsigned int last_accepted_adr_w06:32;		// [31:0]
};
 // rpyramid_PYM_W07_LINEMON Register
struct IRECOG_RPYRAMID_PYM_W07_LINEMON {
	unsigned int linecount_w07:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W07_STADRMON Register
struct IRECOG_RPYRAMID_PYM_W07_STADRMON {
	unsigned int last_accepted_adr_w07:32;		// [31:0]
};
 // rpyramid_PYM_W08_LINEMON Register
struct IRECOG_RPYRAMID_PYM_W08_LINEMON {
	unsigned int linecount_w08:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W08_STADRMON Register
struct IRECOG_RPYRAMID_PYM_W08_STADRMON {
	unsigned int last_accepted_adr_w08:32;		// [31:0]
};
 // rpyramid_PYM_W09_LINEMON Register
struct IRECOG_RPYRAMID_PYM_W09_LINEMON {
	unsigned int linecount_w09:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W09_STADRMON Register
struct IRECOG_RPYRAMID_PYM_W09_STADRMON {
	unsigned int last_accepted_adr_w09:32;		// [31:0]
};
 // rpyramid_PYM_W10_LINEMON Register
struct IRECOG_RPYRAMID_PYM_W10_LINEMON {
	unsigned int linecount_w10:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W10_STADRMON Register
struct IRECOG_RPYRAMID_PYM_W10_STADRMON {
	unsigned int last_accepted_adr_w10:32;		// [31:0]
};
 // rpyramid_PYM_W11_LINEMON Register
struct IRECOG_RPYRAMID_PYM_W11_LINEMON {
	unsigned int linecount_w11:10;		// [9:0]
	unsigned int reserved:22;		// [31:10]
};
 // rpyramid_PYM_W11_STADRMON Register
struct IRECOG_RPYRAMID_PYM_W11_STADRMON {
	unsigned int last_accepted_adr_w11:32;		// [31:0]
};
 // rpyramid_RSCALER_CS_START Register
struct IRECOG_RPYRAMID_RSCALER_CS_START {
	unsigned int csa_start:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // rpyramid_RSCALER_CS_RESET Register
struct IRECOG_RPYRAMID_RSCALER_CS_RESET {
	unsigned int csa_reset:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // rpyramid_RSCALER_CS_MODE Register
struct IRECOG_RPYRAMID_RSCALER_CS_MODE {
	unsigned int reserved4:4;		// [3:0]
	unsigned int csa_in444:2;		// [5:4]
	unsigned int reserved3:2;		// [7:6]
	unsigned int csa_out444:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_actcr4:1;		// [16]
	unsigned int csa_actcb4:1;		// [17]
	unsigned int csa_acty4:1;		// [18]
	unsigned int csa_actcr3:1;		// [19]
	unsigned int csa_actcb3:1;		// [20]
	unsigned int csa_acty3:1;		// [21]
	unsigned int csa_actcr2:1;		// [22]
	unsigned int csa_actcb2:1;		// [23]
	unsigned int csa_acty2:1;		// [24]
	unsigned int csa_actcr1:1;		// [25]
	unsigned int csa_actcb1:1;		// [26]
	unsigned int csa_acty1:1;		// [27]
	unsigned int reserved:4;		// [31:28]
};
 // rpyramid_RSCALER_CS_YHVSIN Register
struct IRECOG_RPYRAMID_RSCALER_CS_YHVSIN {
	unsigned int csa_yvszin:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_yhszin:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_CHVSIN Register
struct IRECOG_RPYRAMID_RSCALER_CS_CHVSIN {
	unsigned int csa_cvszin:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_chszin:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_YHV1SZOUT Register
struct IRECOG_RPYRAMID_RSCALER_CS_YHV1SZOUT {
	unsigned int csa_yv1szout:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_yh1szout:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_CHV1SZOUT Register
struct IRECOG_RPYRAMID_RSCALER_CS_CHV1SZOUT {
	unsigned int csa_cv1szout:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_ch1szout:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_YHV2SZOUT Register
struct IRECOG_RPYRAMID_RSCALER_CS_YHV2SZOUT {
	unsigned int csa_yv2szout:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_yh2szout:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_CHV2SZOUT Register
struct IRECOG_RPYRAMID_RSCALER_CS_CHV2SZOUT {
	unsigned int csa_cv2szout:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_ch2szout:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_YHV3SZOUT Register
struct IRECOG_RPYRAMID_RSCALER_CS_YHV3SZOUT {
	unsigned int csa_yv3szout:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_yh3szout:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_CHV3SZOUT Register
struct IRECOG_RPYRAMID_RSCALER_CS_CHV3SZOUT {
	unsigned int csa_cv3szout:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_ch3szout:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_YHV4SZOUT Register
struct IRECOG_RPYRAMID_RSCALER_CS_YHV4SZOUT {
	unsigned int csa_yv4szout:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_yh4szout:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_CHV4SZOUT Register
struct IRECOG_RPYRAMID_RSCALER_CS_CHV4SZOUT {
	unsigned int csa_cv4szout:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_ch4szout:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_OAINSET Register
struct IRECOG_RPYRAMID_RSCALER_CS_OAINSET {
	unsigned int csa_croainlevel:8;		// [7:0]
	unsigned int csa_cboainlevel:8;		// [15:8]
	unsigned int csa_yoainlevel:8;		// [23:16]
	unsigned int csa_oainset:1;		// [24]
	unsigned int reserved:7;		// [31:25]
};
 // rpyramid_RSCALER_CS_OAOUTSET1 Register
struct IRECOG_RPYRAMID_RSCALER_CS_OAOUTSET1 {
	unsigned int csa_croaoutlevel1:8;		// [7:0]
	unsigned int csa_cboaoutlevel1:8;		// [15:8]
	unsigned int csa_yoaoutlevel1:8;		// [23:16]
	unsigned int ccsa_oaoutset1:1;		// [24]
	unsigned int reserved:7;		// [31:25]
};
 // rpyramid_RSCALER_CS_OAOUTSET2 Register
struct IRECOG_RPYRAMID_RSCALER_CS_OAOUTSET2 {
	unsigned int csa_croaoutlevel2:8;		// [7:0]
	unsigned int csa_cboaoutlevel2:8;		// [15:8]
	unsigned int csa_yoaoutlevel2:8;		// [23:16]
	unsigned int ccsa_oaoutset2:1;		// [24]
	unsigned int reserved:7;		// [31:25]
};
 // rpyramid_RSCALER_CS_OAOUTSET3 Register
struct IRECOG_RPYRAMID_RSCALER_CS_OAOUTSET3 {
	unsigned int csa_croaoutlevel3:8;		// [7:0]
	unsigned int csa_cboaoutlevel3:8;		// [15:8]
	unsigned int csa_yoaoutlevel3:8;		// [23:16]
	unsigned int ccsa_oaoutset3:1;		// [24]
	unsigned int reserved:7;		// [31:25]
};
 // rpyramid_RSCALER_CS_OAOUTSET4 Register
struct IRECOG_RPYRAMID_RSCALER_CS_OAOUTSET4 {
	unsigned int csa_croaoutlevel4:8;		// [7:0]
	unsigned int csa_cboaoutlevel4:8;		// [15:8]
	unsigned int csa_yoaoutlevel4:8;		// [23:16]
	unsigned int ccsa_oaoutset4:1;		// [24]
	unsigned int reserved:7;		// [31:25]
};
 // rpyramid_RSCALER_CS_YHFILMODE Register
struct IRECOG_RPYRAMID_RSCALER_CS_YHFILMODE {
	unsigned int csa_yhfil_mode:3;		// [2:0]
	unsigned int reserved2:1;		// [3]
	unsigned int csa_yhfil_thmode:1;		// [4]
	unsigned int reserved:27;		// [31:5]
};
 // rpyramid_RSCALER_CS_YHFILPSMODE Register
struct IRECOG_RPYRAMID_RSCALER_CS_YHFILPSMODE {
	unsigned int csa_yhfil_szin:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_yhfil_psact:1;		// [16]
	unsigned int reserved:15;		// [31:17]
};
 // rpyramid_RSCALER_CS_YPHOS Register
struct IRECOG_RPYRAMID_RSCALER_CS_YPHOS {
	unsigned int reserved2:7;		// [6:0]
	unsigned int csa_yphos:21;		// [27:7]
	unsigned int reserved:4;		// [31:28]
};
 // rpyramid_RSCALER_CS_YH1FILBASE Register
struct IRECOG_RPYRAMID_RSCALER_CS_YH1FILBASE {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_yh1fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_H1OAOUTSET Register
struct IRECOG_RPYRAMID_RSCALER_CS_H1OAOUTSET {
	unsigned int csa_h1oaoutst:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_h1oaoutw:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_YVFILMODE Register
struct IRECOG_RPYRAMID_RSCALER_CS_YVFILMODE {
	unsigned int csa_yvfil_mode:3;		// [2:0]
	unsigned int reserved2:1;		// [3]
	unsigned int csa_yvfil_thmode:1;		// [4]
	unsigned int reserved:27;		// [31:5]
};
 // rpyramid_RSCALER_CS_YVFILPSMODE Register
struct IRECOG_RPYRAMID_RSCALER_CS_YVFILPSMODE {
	unsigned int csa_yvfil_szin:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_yvfil_psact:1;		// [16]
	unsigned int reserved:15;		// [31:17]
};
 // rpyramid_RSCALER_CS_YPVOS Register
struct IRECOG_RPYRAMID_RSCALER_CS_YPVOS {
	unsigned int reserved2:7;		// [6:0]
	unsigned int csa_ypvos:24;		// [30:7]
	unsigned int reserved:1;		// [31]
};
 // rpyramid_RSCALER_CS_YV1FILBASE Register
struct IRECOG_RPYRAMID_RSCALER_CS_YV1FILBASE {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_yv1fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_V1OAOUTSET Register
struct IRECOG_RPYRAMID_RSCALER_CS_V1OAOUTSET {
	unsigned int csa_v1oaoutst:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_v1oaoutw:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_CHFILMODE Register
struct IRECOG_RPYRAMID_RSCALER_CS_CHFILMODE {
	unsigned int csa_chfil_mode:3;		// [2:0]
	unsigned int reserved2:1;		// [3]
	unsigned int csa_chfil_thmode:1;		// [4]
	unsigned int reserved:27;		// [31:5]
};
 // rpyramid_RSCALER_CS_CHFILPSMODE Register
struct IRECOG_RPYRAMID_RSCALER_CS_CHFILPSMODE {
	unsigned int csa_chfil_szin:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_chfil_psact:1;		// [16]
	unsigned int reserved:15;		// [31:17]
};
 // rpyramid_RSCALER_CS_CPHOS Register
struct IRECOG_RPYRAMID_RSCALER_CS_CPHOS {
	unsigned int reserved2:7;		// [6:0]
	unsigned int csa_cphos:21;		// [27:7]
	unsigned int reserved:4;		// [31:28]
};
 // rpyramid_RSCALER_CS_CH1FILBASE Register
struct IRECOG_RPYRAMID_RSCALER_CS_CH1FILBASE {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_ch1fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_CVFILMODE Register
struct IRECOG_RPYRAMID_RSCALER_CS_CVFILMODE {
	unsigned int csa_cvfil_mode:3;		// [2:0]
	unsigned int reserved2:1;		// [3]
	unsigned int csa_cvfil_thmode:1;		// [4]
	unsigned int reserved:27;		// [31:5]
};
 // rpyramid_RSCALER_CS_CVFILPSMODE Register
struct IRECOG_RPYRAMID_RSCALER_CS_CVFILPSMODE {
	unsigned int csa_cvfil_szin:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_cvfil_psact:1;		// [16]
	unsigned int reserved:15;		// [31:17]
};
 // rpyramid_RSCALER_CS_CPVOS Register
struct IRECOG_RPYRAMID_RSCALER_CS_CPVOS {
	unsigned int reserved2:7;		// [6:0]
	unsigned int csa_cpvos:24;		// [30:7]
	unsigned int reserved:1;		// [31]
};
 // rpyramid_RSCALER_CS_CV1FILBASE Register
struct IRECOG_RPYRAMID_RSCALER_CS_CV1FILBASE {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_cv1fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_YH2FILBASE Register
struct IRECOG_RPYRAMID_RSCALER_CS_YH2FILBASE {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_yh2fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_H2OAOUTSET Register
struct IRECOG_RPYRAMID_RSCALER_CS_H2OAOUTSET {
	unsigned int csa_h2oaoutst:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_h2oaoutw:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_YV2FILBASE Register
struct IRECOG_RPYRAMID_RSCALER_CS_YV2FILBASE {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_yv2fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_V2OAOUTSET Register
struct IRECOG_RPYRAMID_RSCALER_CS_V2OAOUTSET {
	unsigned int csa_v2oaoutst:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_v2oaoutw:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_CH2FILBASE Register
struct IRECOG_RPYRAMID_RSCALER_CS_CH2FILBASE {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_ch2fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_CV2FILBASE Register
struct IRECOG_RPYRAMID_RSCALER_CS_CV2FILBASE {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_cv2fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_YH3FILBASE Register
struct IRECOG_RPYRAMID_RSCALER_CS_YH3FILBASE {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_yh3fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_H3OAOUTSET Register
struct IRECOG_RPYRAMID_RSCALER_CS_H3OAOUTSET {
	unsigned int csa_h3oaoutst:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_h3oaoutw:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_YV3FILBASE Register
struct IRECOG_RPYRAMID_RSCALER_CS_YV3FILBASE {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_yv3fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_V3OAOUTSET Register
struct IRECOG_RPYRAMID_RSCALER_CS_V3OAOUTSET {
	unsigned int csa_v3oaoutst:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_v3oaoutw:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_CH3FILBASE Register
struct IRECOG_RPYRAMID_RSCALER_CS_CH3FILBASE {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_ch3fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_CV3FILBASE Register
struct IRECOG_RPYRAMID_RSCALER_CS_CV3FILBASE {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_cv3fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_YH4FILBASE Register
struct IRECOG_RPYRAMID_RSCALER_CS_YH4FILBASE {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_yh4fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_H4OAOUTSET Register
struct IRECOG_RPYRAMID_RSCALER_CS_H4OAOUTSET {
	unsigned int csa_h4oaoutst:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_h4oaoutw:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_YV4FILBASE Register
struct IRECOG_RPYRAMID_RSCALER_CS_YV4FILBASE {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_yv4fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_V4OAOUTSET Register
struct IRECOG_RPYRAMID_RSCALER_CS_V4OAOUTSET {
	unsigned int csa_v4oaoutst:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_v4oaoutw:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_CH4FILBASE Register
struct IRECOG_RPYRAMID_RSCALER_CS_CH4FILBASE {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_ch4fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_CV4FILBASE Register
struct IRECOG_RPYRAMID_RSCALER_CS_CV4FILBASE {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_cv4fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_DEBUG Register
struct IRECOG_RPYRAMID_RSCALER_CS_DEBUG {
	unsigned int csa_debug_tapsel:3;		// [2:0]
	unsigned int reserved2:5;		// [7:3]
	unsigned int csa_debug_pcntena:1;		// [8]
	unsigned int reserved:23;		// [31:9]
};
 // rpyramid_RSCALER_CS_Y2VLINE Register
struct IRECOG_RPYRAMID_RSCALER_CS_Y2VLINE {
	unsigned int csa_r_y3vline:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_r_y4vline:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_Y1VLINE Register
struct IRECOG_RPYRAMID_RSCALER_CS_Y1VLINE {
	unsigned int csa_r_y1vline:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_r_y2vline:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_CB2VLINE Register
struct IRECOG_RPYRAMID_RSCALER_CS_CB2VLINE {
	unsigned int csa_r_cb3vline:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_r_cb4vline:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_CB1VLINE Register
struct IRECOG_RPYRAMID_RSCALER_CS_CB1VLINE {
	unsigned int csa_r_cb1vline:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_r_cb2vline:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_CR2VLINE Register
struct IRECOG_RPYRAMID_RSCALER_CS_CR2VLINE {
	unsigned int csa_r_cr3vline:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_r_cr4vline:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_CR1VLINE Register
struct IRECOG_RPYRAMID_RSCALER_CS_CR1VLINE {
	unsigned int csa_r_cr1vline:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_r_cr2vline:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_TAP_STATUS Register
struct IRECOG_RPYRAMID_RSCALER_CS_TAP_STATUS {
	unsigned int csa_r_tapdl_finx:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // rpyramid_RSCALER_CS_ERR Register
struct IRECOG_RPYRAMID_RSCALER_CS_ERR {
	unsigned int csa_r_err:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // rpyramid_RSCALER_CS_PCNT Register
struct IRECOG_RPYRAMID_RSCALER_CS_PCNT {
	unsigned int csa_r_pcnt:24;		// [23:0]
	unsigned int reserved:8;		// [31:24]
};
 // rpyramid_RSCALER_CS_MODE_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_MODE_BUF {
	unsigned int reserved4:4;		// [3:0]
	unsigned int csa_in444:2;		// [5:4]
	unsigned int reserved3:2;		// [7:6]
	unsigned int csa_out444:2;		// [9:8]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_actcr4:1;		// [16]
	unsigned int csa_actcb4:1;		// [17]
	unsigned int csa_acty4:1;		// [18]
	unsigned int csa_actcr3:1;		// [19]
	unsigned int csa_actcb3:1;		// [20]
	unsigned int csa_acty3:1;		// [21]
	unsigned int csa_actcr2:1;		// [22]
	unsigned int csa_actcb2:1;		// [23]
	unsigned int csa_acty2:1;		// [24]
	unsigned int csa_actcr1:1;		// [25]
	unsigned int csa_actcb1:1;		// [26]
	unsigned int csa_acty1:1;		// [27]
	unsigned int reserved:4;		// [31:28]
};
 // rpyramid_RSCALER_CS_YHVSIN_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_YHVSIN_BUF {
	unsigned int csa_yvszin:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_yhszin:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_CHVSIN_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_CHVSIN_BUF {
	unsigned int csa_cvszin:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_chszin:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_YHV1SZOUT_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_YHV1SZOUT_BUF {
	unsigned int csa_yv1szout:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_yh1szout:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_CHV1SZOUT_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_CHV1SZOUT_BUF {
	unsigned int csa_cv1szout:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_ch1szout:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_YHV2SZOUT_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_YHV2SZOUT_BUF {
	unsigned int csa_yv2szout:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_yh2szout:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_CHV2SZOUT_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_CHV2SZOUT_BUF {
	unsigned int csa_cv2szout:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_ch2szout:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_YHV3SZOUT_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_YHV3SZOUT_BUF {
	unsigned int csa_yv3szout:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_yh3szout:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_CHV3SZOUT_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_CHV3SZOUT_BUF {
	unsigned int csa_cv3szout:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_ch3szout:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_YHV4SZOUT_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_YHV4SZOUT_BUF {
	unsigned int csa_yv4szout:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_yh4szout:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_CHV4SZOUT_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_CHV4SZOUT_BUF {
	unsigned int csa_cv4szout:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_ch4szout:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_OAINSET_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_OAINSET_BUF {
	unsigned int csa_croainlevel:8;		// [7:0]
	unsigned int csa_cboainlevel:8;		// [15:8]
	unsigned int csa_yoainlevel:8;		// [23:16]
	unsigned int csa_oainset:1;		// [24]
	unsigned int reserved:7;		// [31:25]
};
 // rpyramid_RSCALER_CS_OAOUTSET1_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_OAOUTSET1_BUF {
	unsigned int csa_croaoutlevel1:8;		// [7:0]
	unsigned int csa_cboaoutlevel1:8;		// [15:8]
	unsigned int csa_yoaoutlevel1:8;		// [23:16]
	unsigned int ccsa_oaoutset1:1;		// [24]
	unsigned int reserved:7;		// [31:25]
};
 // rpyramid_RSCALER_CS_OAOUTSET2_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_OAOUTSET2_BUF {
	unsigned int csa_croaoutlevel2:8;		// [7:0]
	unsigned int csa_cboaoutlevel2:8;		// [15:8]
	unsigned int csa_yoaoutlevel2:8;		// [23:16]
	unsigned int ccsa_oaoutset2:1;		// [24]
	unsigned int reserved:7;		// [31:25]
};
 // rpyramid_RSCALER_CS_OAOUTSET3_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_OAOUTSET3_BUF {
	unsigned int csa_croaoutlevel3:8;		// [7:0]
	unsigned int csa_cboaoutlevel3:8;		// [15:8]
	unsigned int csa_yoaoutlevel3:8;		// [23:16]
	unsigned int ccsa_oaoutset3:1;		// [24]
	unsigned int reserved:7;		// [31:25]
};
 // rpyramid_RSCALER_CS_OAOUTSET4_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_OAOUTSET4_BUF {
	unsigned int csa_croaoutlevel4:8;		// [7:0]
	unsigned int csa_cboaoutlevel4:8;		// [15:8]
	unsigned int csa_yoaoutlevel4:8;		// [23:16]
	unsigned int ccsa_oaoutset4:1;		// [24]
	unsigned int reserved:7;		// [31:25]
};
 // rpyramid_RSCALER_CS_YHFILMODE_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_YHFILMODE_BUF {
	unsigned int csa_yhfil_mode:3;		// [2:0]
	unsigned int reserved2:1;		// [3]
	unsigned int csa_yhfil_thmode:1;		// [4]
	unsigned int reserved:27;		// [31:5]
};
 // rpyramid_RSCALER_CS_YHFILPSMODE_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_YHFILPSMODE_BUF {
	unsigned int csa_yhfil_szin:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_yhfil_psact:1;		// [16]
	unsigned int reserved:15;		// [31:17]
};
 // rpyramid_RSCALER_CS_YPHOS_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_YPHOS_BUF {
	unsigned int reserved2:7;		// [6:0]
	unsigned int csa_yphos:21;		// [27:7]
	unsigned int reserved:4;		// [31:28]
};
 // rpyramid_RSCALER_CS_YH1FILBASE_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_YH1FILBASE_BUF {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_yh1fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_H1OAOUTSET_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_H1OAOUTSET_BUF {
	unsigned int csa_h1oaoutst:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_h1oaoutw:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_YVFILMODE_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_YVFILMODE_BUF {
	unsigned int csa_yvfil_mode:3;		// [2:0]
	unsigned int reserved2:1;		// [3]
	unsigned int csa_yvfil_thmode:1;		// [4]
	unsigned int reserved:27;		// [31:5]
};
 // rpyramid_RSCALER_CS_YVFILPSMODE_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_YVFILPSMODE_BUF {
	unsigned int csa_yvfil_szin:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_yvfil_psact:1;		// [16]
	unsigned int reserved:15;		// [31:17]
};
 // rpyramid_RSCALER_CS_YPVOS_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_YPVOS_BUF {
	unsigned int reserved2:7;		// [6:0]
	unsigned int csa_ypvos:24;		// [30:7]
	unsigned int reserved:1;		// [31]
};
 // rpyramid_RSCALER_CS_YV1FILBASE_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_YV1FILBASE_BUF {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_yv1fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_V1OAOUTSET_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_V1OAOUTSET_BUF {
	unsigned int csa_v1oaoutst:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_v1oaoutw:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_CHFILMODE_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_CHFILMODE_BUF {
	unsigned int csa_chfil_mode:3;		// [2:0]
	unsigned int reserved2:1;		// [3]
	unsigned int csa_chfil_thmode:1;		// [4]
	unsigned int reserved:27;		// [31:5]
};
 // rpyramid_RSCALER_CS_CHFILPSMODE_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_CHFILPSMODE_BUF {
	unsigned int csa_chfil_szin:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_chfil_psact:1;		// [16]
	unsigned int reserved:15;		// [31:17]
};
 // rpyramid_RSCALER_CS_CPHOS_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_CPHOS_BUF {
	unsigned int reserved2:7;		// [6:0]
	unsigned int csa_cphos:21;		// [27:7]
	unsigned int reserved:4;		// [31:28]
};
 // rpyramid_RSCALER_CS_CH1FILBASE_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_CH1FILBASE_BUF {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_ch1fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_CVFILMODE_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_CVFILMODE_BUF {
	unsigned int csa_cvfil_mode:3;		// [2:0]
	unsigned int reserved2:1;		// [3]
	unsigned int csa_cvfil_thmode:1;		// [4]
	unsigned int reserved:27;		// [31:5]
};
 // rpyramid_RSCALER_CS_CVFILPSMODE_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_CVFILPSMODE_BUF {
	unsigned int csa_cvfil_szin:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_cvfil_psact:1;		// [16]
	unsigned int reserved:15;		// [31:17]
};
 // rpyramid_RSCALER_CS_CPVOS_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_CPVOS_BUF {
	unsigned int reserved2:7;		// [6:0]
	unsigned int csa_cpvos:24;		// [30:7]
	unsigned int reserved:1;		// [31]
};
 // rpyramid_RSCALER_CS_CV1FILBASE_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_CV1FILBASE_BUF {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_cv1fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_YH2FILBASE_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_YH2FILBASE_BUF {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_yh2fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_H2OAOUTSET_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_H2OAOUTSET_BUF {
	unsigned int csa_h2oaoutst:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_h2oaoutw:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_YV2FILBASE_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_YV2FILBASE_BUF {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_yv2fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_V2OAOUTSET_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_V2OAOUTSET_BUF {
	unsigned int csa_v2oaoutst:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_v2oaoutw:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_CH2FILBASE_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_CH2FILBASE_BUF {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_ch2fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_CV2FILBASE_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_CV2FILBASE_BUF {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_cv2fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_YH3FILBASE_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_YH3FILBASE_BUF {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_yh3fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_H3OAOUTSET_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_H3OAOUTSET_BUF {
	unsigned int csa_h3oaoutst:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_h3oaoutw:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_YV3FILBASE_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_YV3FILBASE_BUF {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_yv3fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_V3OAOUTSET_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_V3OAOUTSET_BUF {
	unsigned int csa_v3oaoutst:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_v3oaoutw:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_CH3FILBASE_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_CH3FILBASE_BUF {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_ch3fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_CV3FILBASE_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_CV3FILBASE_BUF {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_cv3fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_YH4FILBASE_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_YH4FILBASE_BUF {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_yh4fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_H4OAOUTSET_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_H4OAOUTSET_BUF {
	unsigned int csa_h4oaoutst:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_h4oaoutw:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_YV4FILBASE_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_YV4FILBASE_BUF {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_yv4fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_V4OAOUTSET_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_V4OAOUTSET_BUF {
	unsigned int csa_v4oaoutst:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int csa_v4oaoutw:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rpyramid_RSCALER_CS_CH4FILBASE_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_CH4FILBASE_BUF {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_ch4fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_CV4FILBASE_BUF Register
struct IRECOG_RPYRAMID_RSCALER_CS_CV4FILBASE_BUF {
	unsigned int reserved2:3;		// [2:0]
	unsigned int csa_cv4fil_base:19;		// [21:3]
	unsigned int reserved:10;		// [31:22]
};
 // rpyramid_RSCALER_CS_YHTAP00 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YHTAP00 {
	unsigned int csa_yhtap01:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yhtap00:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YHTAP01 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YHTAP01 {
	unsigned int csa_yhtap03:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yhtap02:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YHTAP02 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YHTAP02 {
	unsigned int csa_yhtap05:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yhtap04:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YHTAP03 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YHTAP03 {
	unsigned int csa_yhtap07:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yhtap06:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YHTAP04 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YHTAP04 {
	unsigned int csa_yhtap09:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yhtap08:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YHTAP05 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YHTAP05 {
	unsigned int csa_yhtap11:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yhtap10:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YHTAP06 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YHTAP06 {
	unsigned int csa_yhtap13:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yhtap12:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YHTAP07 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YHTAP07 {
	unsigned int csa_yhtap15:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yhtap14:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YHTAP08 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YHTAP08 {
	unsigned int csa_yhtap17:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yhtap16:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YHTAP09 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YHTAP09 {
	unsigned int csa_yhtap19:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yhtap18:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YHTAP10 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YHTAP10 {
	unsigned int csa_yhtap21:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yhtap20:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YHTAP11 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YHTAP11 {
	unsigned int csa_yhtap23:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yhtap22:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YHTAP12 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YHTAP12 {
	unsigned int csa_yhtap25:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yhtap24:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YHTAP13 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YHTAP13 {
	unsigned int csa_yhtap27:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yhtap26:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YHTAP14 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YHTAP14 {
	unsigned int csa_yhtap29:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yhtap28:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YHTAP15 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YHTAP15 {
	unsigned int csa_yhtap31:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yhtap30:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YVTAP00 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YVTAP00 {
	unsigned int csa_yvtap01:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yvtap00:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YVTAP01 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YVTAP01 {
	unsigned int csa_yvtap03:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yvtap02:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YVTAP02 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YVTAP02 {
	unsigned int csa_yvtap05:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yvtap04:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YVTAP03 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YVTAP03 {
	unsigned int csa_yvtap07:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yvtap06:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YVTAP04 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YVTAP04 {
	unsigned int csa_yvtap09:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yvtap08:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YVTAP05 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YVTAP05 {
	unsigned int csa_yvtap11:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yvtap10:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YVTAP06 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YVTAP06 {
	unsigned int csa_yvtap13:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yvtap12:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YVTAP07 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YVTAP07 {
	unsigned int csa_yvtap15:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yvtap14:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YVTAP08 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YVTAP08 {
	unsigned int csa_yvtap17:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yvtap16:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YVTAP09 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YVTAP09 {
	unsigned int csa_yvtap19:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yvtap18:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YVTAP10 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YVTAP10 {
	unsigned int csa_yvtap21:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yvtap20:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YVTAP11 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YVTAP11 {
	unsigned int csa_yvtap23:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yvtap22:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YVTAP12 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YVTAP12 {
	unsigned int csa_yvtap25:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yvtap24:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YVTAP13 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YVTAP13 {
	unsigned int csa_yvtap27:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yvtap26:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YVTAP14 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YVTAP14 {
	unsigned int csa_yvtap29:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yvtap28:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_YVTAP15 Register
struct IRECOG_RPYRAMID_RSCALER_CS_YVTAP15 {
	unsigned int csa_yvtap31:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_yvtap30:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CHTAP00 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CHTAP00 {
	unsigned int csa_chtap01:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_chtap00:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CHTAP01 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CHTAP01 {
	unsigned int csa_chtap03:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_chtap02:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CHTAP02 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CHTAP02 {
	unsigned int csa_chtap05:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_chtap04:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CHTAP03 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CHTAP03 {
	unsigned int csa_chtap07:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_chtap06:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CHTAP04 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CHTAP04 {
	unsigned int csa_chtap09:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_chtap08:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CHTAP05 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CHTAP05 {
	unsigned int csa_chtap11:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_chtap10:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CHTAP06 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CHTAP06 {
	unsigned int csa_chtap13:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_chtap12:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CHTAP07 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CHTAP07 {
	unsigned int csa_chtap15:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_chtap14:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CHTAP08 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CHTAP08 {
	unsigned int csa_chtap17:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_chtap16:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CHTAP09 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CHTAP09 {
	unsigned int csa_chtap19:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_chtap18:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CHTAP10 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CHTAP10 {
	unsigned int csa_chtap21:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_chtap20:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CHTAP11 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CHTAP11 {
	unsigned int csa_chtap23:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_chtap22:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CHTAP12 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CHTAP12 {
	unsigned int csa_chtap25:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_chtap24:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CHTAP13 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CHTAP13 {
	unsigned int csa_chtap27:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_chtap26:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CHTAP14 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CHTAP14 {
	unsigned int csa_chtap29:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_chtap28:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CHTAP15 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CHTAP15 {
	unsigned int csa_chtap31:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_chtap30:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CVTAP00 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CVTAP00 {
	unsigned int csa_cvtap01:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_cvtap00:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CVTAP01 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CVTAP01 {
	unsigned int csa_cvtap03:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_cvtap02:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CVTAP02 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CVTAP02 {
	unsigned int csa_cvtap05:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_cvtap04:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CVTAP03 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CVTAP03 {
	unsigned int csa_cvtap07:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_cvtap06:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CVTAP04 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CVTAP04 {
	unsigned int csa_cvtap09:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_cvtap08:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CVTAP05 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CVTAP05 {
	unsigned int csa_cvtap11:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_cvtap10:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CVTAP06 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CVTAP06 {
	unsigned int csa_cvtap13:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_cvtap12:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CVTAP07 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CVTAP07 {
	unsigned int csa_cvtap15:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_cvtap14:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CVTAP08 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CVTAP08 {
	unsigned int csa_cvtap17:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_cvtap16:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CVTAP09 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CVTAP09 {
	unsigned int csa_cvtap19:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_cvtap18:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CVTAP10 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CVTAP10 {
	unsigned int csa_cvtap21:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_cvtap20:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CVTAP11 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CVTAP11 {
	unsigned int csa_cvtap23:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_cvtap22:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CVTAP12 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CVTAP12 {
	unsigned int csa_cvtap25:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_cvtap24:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CVTAP13 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CVTAP13 {
	unsigned int csa_cvtap27:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_cvtap26:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CVTAP14 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CVTAP14 {
	unsigned int csa_cvtap29:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_cvtap28:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rpyramid_RSCALER_CS_CVTAP15 Register
struct IRECOG_RPYRAMID_RSCALER_CS_CVTAP15 {
	unsigned int csa_cvtap31:10;		// [9:0]
	unsigned int reserved2:6;		// [15:10]
	unsigned int csa_cvtap30:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // raffine_Control_Register Register
struct IRECOG_RAFFINE_CONTROL_REGISTER {
	unsigned int CMD:1;		// [0]
	unsigned int O_RST:1;		// [1]
	unsigned int C_RST:1;		// [2]
	unsigned int T_RST:1;		// [3]
	unsigned int reserved2:4;		// [7:4]
	unsigned int YP_FLTL:1;		// [8]
	unsigned int YP_FLTU:1;		// [9]
	unsigned int YP_INTL:1;		// [10]
	unsigned int YP_INTU:1;		// [11]
	unsigned int XP_FLTL:1;		// [12]
	unsigned int XP_FLTU:1;		// [13]
	unsigned int XP_INTL:1;		// [14]
	unsigned int XP_INTU:1;		// [15]
	unsigned int IL_NUM_r:5;		// [20:16]
	unsigned int IL_NUM_w:6;		// [26:21]
	unsigned int reserved:5;		// [31:27]
};
 // raffine_Mode_Register Register
struct IRECOG_RAFFINE_MODE_REGISTER {
	unsigned int O_MODE:1;		// [0]
	unsigned int reserved2:1;		// [1]
	unsigned int PX_MODE:1;		// [2]
	unsigned int CNV_MODE:2;		// [4:3]
	unsigned int PSZ:1;		// [5]
	unsigned int PF_CBL:1;		// [6]
	unsigned int B_DIR:1;		// [7]
	unsigned int reserved:5;		// [12:8]
	unsigned int TB_T:3;		// [15:13]
	unsigned int FILL_P:16;		// [31:16]
};
 // raffine_output_picture_correction Register
struct IRECOG_RAFFINE_OUTPUT_PICTURE_CORRECTION {
	unsigned int reserved:8;		// [7:0]
	unsigned int AVE_ADJ:8;		// [15:8]
	unsigned int MAX_P:16;		// [31:16]
};
 // raffine_interrupt_mask Register
struct IRECOG_RAFFINE_INTERRUPT_MASK {
	unsigned int END_MASK:1;		// [0]
	unsigned int reserved4:7;		// [7:1]
	unsigned int LINE_OUT_MASK:1;		// [8]
	unsigned int reserved3:5;		// [13:9]
	unsigned int reserved2:1;		// [14]
	unsigned int reserved:17;		// [31:15]
};
 // raffine_status_Register Register
struct IRECOG_RAFFINE_STATUS_REGISTER {
	unsigned int END:1;		// [0]
	unsigned int reserved5:7;		// [7:1]
	unsigned int LINE_OUT:1;		// [8]
	unsigned int reserved4:5;		// [13:9]
	unsigned int reserved3:1;		// [14]
	unsigned int reserved2:1;		// [15]
	unsigned int reserved:16;		// [31:16]
};
 // raffine_coordinate_point_of_operation Register
struct IRECOG_RAFFINE_COORDINATE_POINT_OF_OPERATION {
	unsigned int OUT_LPOS:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // raffine_input_picture_size Register
struct IRECOG_RAFFINE_INPUT_PICTURE_SIZE {
	unsigned int SRC_HIGT:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int SRC_WDTH:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // raffine_input_picture_address Register
struct IRECOG_RAFFINE_INPUT_PICTURE_ADDRESS {
	unsigned int SRC_ADDR_r:6;		// [5:0]
	unsigned int SRC_ADDR_w:26;		// [31:6]
};
 // raffine_output_coordinate_origin Register
struct IRECOG_RAFFINE_OUTPUT_COORDINATE_ORIGIN {
	unsigned int DST_VBGN:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int DST_HBGN:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // raffine_output_picture_size Register
struct IRECOG_RAFFINE_OUTPUT_PICTURE_SIZE {
	unsigned int DST_HIGT:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int DST_WDTH:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // raffine_output_picture_address Register
struct IRECOG_RAFFINE_OUTPUT_PICTURE_ADDRESS {
	unsigned int DST_ADDR_r:6;		// [5:0]
	unsigned int DST_ADDR_w:26;		// [31:6]
};
 // raffine_input_output_picture_pitch Register
struct IRECOG_RAFFINE_INPUT_OUTPUT_PICTURE_PITCH {
	unsigned int DST_L_PTCH:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int SRC_L_PTCH:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // raffine_table_address Register
struct IRECOG_RAFFINE_TABLE_ADDRESS {
	unsigned int TBL_ADDR_r:8;		// [7:0]
	unsigned int TBL_ADDR_w:24;		// [31:8]
};
 // raffine_table_pitch Register
struct IRECOG_RAFFINE_TABLE_PITCH {
	unsigned int TBL_PTCH:11;		// [10:0]
	unsigned int reserved:21;		// [31:11]
};
 // raffine_affine_parameter0 Register
struct IRECOG_RAFFINE_AFFINE_PARAMETER0 {
	unsigned int AFFN_P0:28;		// [27:0]
	unsigned int reserved:4;		// [31:28]
};
 // raffine_affine_parameter1 Register
struct IRECOG_RAFFINE_AFFINE_PARAMETER1 {
	unsigned int AFFN_P1:28;		// [27:0]
	unsigned int reserved:4;		// [31:28]
};
 // raffine_affine_parameter2 Register
struct IRECOG_RAFFINE_AFFINE_PARAMETER2 {
	unsigned int AFFN_P2:28;		// [27:0]
	unsigned int reserved:4;		// [31:28]
};
 // raffine_affine_parameter3 Register
struct IRECOG_RAFFINE_AFFINE_PARAMETER3 {
	unsigned int AFFN_P3:28;		// [27:0]
	unsigned int reserved:4;		// [31:28]
};
 // raffine_affine_parameter4 Register
struct IRECOG_RAFFINE_AFFINE_PARAMETER4 {
	unsigned int AFFN_P4:28;		// [27:0]
	unsigned int reserved:4;		// [31:28]
};
 // raffine_affine_parameter5 Register
struct IRECOG_RAFFINE_AFFINE_PARAMETER5 {
	unsigned int AFFN_P5:28;		// [27:0]
	unsigned int reserved:4;		// [31:28]
};
 // raffine_strain_compensation_parameter0 Register
struct IRECOG_RAFFINE_STRAIN_COMPENSATION_PARAMETER0 {
	unsigned int DIST_P0:22;		// [21:0]
	unsigned int reserved:10;		// [31:22]
};
 // raffine_strain_compensation_parameter1 Register
struct IRECOG_RAFFINE_STRAIN_COMPENSATION_PARAMETER1 {
	unsigned int DIST_P1:22;		// [21:0]
	unsigned int reserved:10;		// [31:22]
};
 // raffine_strain_compensation_parameter2 Register
struct IRECOG_RAFFINE_STRAIN_COMPENSATION_PARAMETER2 {
	unsigned int DIST_P2:18;		// [17:0]
	unsigned int reserved:14;		// [31:18]
};
 // raffine_strain_compensation_parameter3 Register
struct IRECOG_RAFFINE_STRAIN_COMPENSATION_PARAMETER3 {
	unsigned int DIST_P3:18;		// [17:0]
	unsigned int reserved:14;		// [31:18]
};
 // raffine_strain_compensation_parameter4 Register
struct IRECOG_RAFFINE_STRAIN_COMPENSATION_PARAMETER4 {
	unsigned int DIST_P4:19;		// [18:0]
	unsigned int reserved:13;		// [31:19]
};
 // raffine_strain_compensation_parameter5 Register
struct IRECOG_RAFFINE_STRAIN_COMPENSATION_PARAMETER5 {
	unsigned int DIST_P5:19;		// [18:0]
	unsigned int reserved:13;		// [31:19]
};
 // raffine_strain_compensation_parameter6 Register
struct IRECOG_RAFFINE_STRAIN_COMPENSATION_PARAMETER6 {
	unsigned int DIST_P6:24;		// [23:0]
	unsigned int reserved:8;		// [31:24]
};
 // raffine_strain_compensation_parameter7 Register
struct IRECOG_RAFFINE_STRAIN_COMPENSATION_PARAMETER7 {
	unsigned int DIST_P7:25;		// [24:0]
	unsigned int reserved:7;		// [31:25]
};
 // raffine_strain_compensation_parameter8 Register
struct IRECOG_RAFFINE_STRAIN_COMPENSATION_PARAMETER8 {
	unsigned int DIST_P8:25;		// [24:0]
	unsigned int reserved:7;		// [31:25]
};
 // raffine_strain_compensation_parameter9 Register
struct IRECOG_RAFFINE_STRAIN_COMPENSATION_PARAMETER9 {
	unsigned int DIST_P9:25;		// [24:0]
	unsigned int reserved:7;		// [31:25]
};
 // raffine_strain_compensation_parameter10 Register
struct IRECOG_RAFFINE_STRAIN_COMPENSATION_PARAMETER10 {
	unsigned int DIST_P10:25;		// [24:0]
	unsigned int reserved:7;		// [31:25]
};
 // raffine_strain_compensation_parameter11 Register
struct IRECOG_RAFFINE_STRAIN_COMPENSATION_PARAMETER11 {
	unsigned int DIST_P11:25;		// [24:0]
	unsigned int reserved:7;		// [31:25]
};
 // raffine_debug_break Register
struct IRECOG_RAFFINE_DEBUG_BREAK {
	unsigned int BRK_VPOS:11;		// [10:0]
	unsigned int BRK_HPOS:11;		// [21:11]
	unsigned int POS_DBG:1;		// [22]
	unsigned int reserved:9;		// [31:23]
};
 // raffine_write_buffer_coordinate_point Register
struct IRECOG_RAFFINE_WRITE_BUFFER_COORDINATE_POINT {
	unsigned int WB_VPOS:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int WB_HPOS:11;		// [26:16]
	unsigned int reserved:4;		// [30:27]
	unsigned int Valid:1;		// [31]
};
 // raffine_write_buffer_data Register
struct IRECOG_RAFFINE_WRITE_BUFFER_DATA {
	unsigned int WB_DATA:16;		// [15:0]
	unsigned int reserved:16;		// [31:16]
};
 // raffine_convert_coordinate_point Register
struct IRECOG_RAFFINE_CONVERT_COORDINATE_POINT {
	unsigned int CVT_VPOS:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int CVT_HPOS:11;		// [26:16]
	unsigned int reserved:4;		// [30:27]
	unsigned int Valid:1;		// [31]
};
 // raffine_horizontal_coordinate_point_of_original Register
struct IRECOG_RAFFINE_HORIZONTAL_COORDINATE_POINT_OF_ORIGINAL {
	unsigned int CVT_SRC_HPOS:32;		// [31:0]
};
 // raffine_vertical_coordinate_point_of_original Register
struct IRECOG_RAFFINE_VERTICAL_COORDINATE_POINT_OF_ORIGINAL {
	unsigned int CVT_SRC_VPOS:32;		// [31:0]
};
 // raffine_upper_line_data Register
struct IRECOG_RAFFINE_UPPER_LINE_DATA {
	unsigned int CVT_DATA1:16;		// [15:0]
	unsigned int CVT_DATA0:16;		// [31:16]
};
 // raffine_under_line_data Register
struct IRECOG_RAFFINE_UNDER_LINE_DATA {
	unsigned int CVT_DATA3:16;		// [15:0]
	unsigned int CVT_DATA2:16;		// [31:16]
};
 // raffine_cache_write_command Register
struct IRECOG_RAFFINE_CACHE_WRITE_COMMAND {
	unsigned int reserved2:5;		// [4:0]
	unsigned int Offset:5;		// [9:5]
	unsigned int Index:8;		// [17:10]
	unsigned int reserved:8;		// [25:18]
	unsigned int WEN:1;		// [26]
	unsigned int OO:1;		// [27]
	unsigned int OE:1;		// [28]
	unsigned int EO:1;		// [29]
	unsigned int EE:1;		// [30]
	unsigned int P_C:1;		// [31]
};
 // raffine_cache_write_data Register
struct IRECOG_RAFFINE_CACHE_WRITE_DATA {
	unsigned int Data:16;		// [15:0]
	unsigned int Tag:8;		// [23:16]
	unsigned int reserved:6;		// [29:24]
	unsigned int Flag:2;		// [31:30]
};
 // rhist_Control_and_Status_Register Register
struct IRECOG_RHIST_CONTROL_AND_STATUS_REGISTER {
	unsigned int CMD:1;		// [0]
	unsigned int RST:1;		// [1]
	unsigned int reserved:30;		// [31:2]
};
 // rhist_Mode_Register Register
struct IRECOG_RHIST_MODE_REGISTER {
	unsigned int MODE:1;		// [0]
	unsigned int SHIFT:4;		// [4:1]
	unsigned int reserved:11;		// [15:5]
	unsigned int OFFSET:16;		// [31:16]
};
 // rhist_interrupt_status Register
struct IRECOG_RHIST_INTERRUPT_STATUS {
	unsigned int END:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // rhist_interrupt_mask Register
struct IRECOG_RHIST_INTERRUPT_MASK {
	unsigned int END_MASK:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // rhist_Histogram_Function_Register Register
struct IRECOG_RHIST_HISTOGRAM_FUNCTION_REGISTER {
	unsigned int HIST_MODE:1;		// [0]
	unsigned int BIN_NUM:2;		// [2:1]
	unsigned int BIN_CLR:1;		// [3]
	unsigned int OUTL:1;		// [4]
	unsigned int OEN:1;		// [5]
	unsigned int reserved:26;		// [31:6]
};
 // rhist_Table_Convertion_Function_Register Register
struct IRECOG_RHIST_TABLE_CONVERTION_FUNCTION_REGISTER {
	unsigned int TBIN_SIZE:2;		// [1:0]
	unsigned int TB_LOAD:1;		// [2]
	unsigned int reserved:29;		// [31:3]
};
 // rhist_Statistics_Function_Register Register
struct IRECOG_RHIST_STATISTICS_FUNCTION_REGISTER {
	unsigned int STAT_TH:17;		// [16:0]
	unsigned int STAT_MODE:1;		// [17]
	unsigned int STAT_CLR:1;		// [18]
	unsigned int reserved:13;		// [31:19]
};
 // rhist_Source_0_Address_Register Register
struct IRECOG_RHIST_SOURCE_0_ADDRESS_REGISTER {
	unsigned int SRC0_ADDR_r:4;		// [3:0]
	unsigned int SRC0_ADDR_w:28;		// [31:4]
};
 // rhist_Source_1_Address_Register Register
struct IRECOG_RHIST_SOURCE_1_ADDRESS_REGISTER {
	unsigned int SRC1_ADDR_r:4;		// [3:0]
	unsigned int SRC1_ADDR_w:28;		// [31:4]
};
 // rhist_Source_0_Line_Pitch_Register Register
struct IRECOG_RHIST_SOURCE_0_LINE_PITCH_REGISTER {
	unsigned int SRC0_LPTCH:32;		// [31:0]
};
 // rhist_Source_1_Line_Pitch_Register Register
struct IRECOG_RHIST_SOURCE_1_LINE_PITCH_REGISTER {
	unsigned int SRC1_LPTCH:32;		// [31:0]
};
 // rhist_Source_0_Size_Register Register
struct IRECOG_RHIST_SOURCE_0_SIZE_REGISTER {
	unsigned int SRC0_WDTH:16;		// [15:0]
	unsigned int SRC0_HIGT:13;		// [28:16]
	unsigned int SRC0_ARY:1;		// [29]
	unsigned int SRC0_FMT:2;		// [31:30]
};
 // rhist_Source_1_Size_Register Register
struct IRECOG_RHIST_SOURCE_1_SIZE_REGISTER {
	unsigned int SRC1_WDTH:16;		// [15:0]
	unsigned int SRC1_HIGT:13;		// [28:16]
	unsigned int SRC1_ARY:1;		// [29]
	unsigned int SRC1_FMT0:1;		// [30]
	unsigned int SRC1_FMT1:1;		// [31]
};
 // rhist_Source_0_Sampling_Register_0 Register
struct IRECOG_RHIST_SOURCE_0_SAMPLING_REGISTER_0 {
	unsigned int SRC0_SX:8;		// [7:0]
	unsigned int SRC0_SY:8;		// [15:8]
	unsigned int SRC0_SP_OFFSET:4;		// [19:16]
	unsigned int reserved:12;		// [31:20]
};
 // rhist_Source_0_Sampling_Register_1 Register
struct IRECOG_RHIST_SOURCE_0_SAMPLING_REGISTER_1 {
	unsigned int SRC0_NX:16;		// [15:0]
	unsigned int SRC0_NY:13;		// [28:16]
	unsigned int reserved:3;		// [31:29]
};
 // rhist_Source_1_Sampling_Register_0 Register
struct IRECOG_RHIST_SOURCE_1_SAMPLING_REGISTER_0 {
	unsigned int SRC1_SX:8;		// [7:0]
	unsigned int SRC1_SY:8;		// [15:8]
	unsigned int SRC1_SP_OFFSET:4;		// [19:16]
	unsigned int reserved:12;		// [31:20]
};
 // rhist_Source_1_Sampling_Register_1 Register
struct IRECOG_RHIST_SOURCE_1_SAMPLING_REGISTER_1 {
	unsigned int SRC1_NX:16;		// [15:0]
	unsigned int SRC1_NY:13;		// [28:16]
	unsigned int reserved:3;		// [31:29]
};
 // rhist_Destination_0_Address_Register Register
struct IRECOG_RHIST_DESTINATION_0_ADDRESS_REGISTER {
	unsigned int DST0_ADDR_r:4;		// [3:0]
	unsigned int DST0_ADDR_w:28;		// [31:4]
};
 // rhist_Destination_0_Line_Pitch_Register Register
struct IRECOG_RHIST_DESTINATION_0_LINE_PITCH_REGISTER {
	unsigned int DST0_LPTCH:32;		// [31:0]
};
 // rhist_Destination_0_Format_Register Register
struct IRECOG_RHIST_DESTINATION_0_FORMAT_REGISTER {
	unsigned int DST0_WDTH:16;		// [15:0]
	unsigned int DST0_HIGT:13;		// [28:16]
	unsigned int DST0_ARY:1;		// [29]
	unsigned int DST0_FMT:2;		// [31:30]
};
 // rhist_Statistics_Result_0_Register Register
struct IRECOG_RHIST_STATISTICS_RESULT_0_REGISTER {
	unsigned int STAT_R0:32;		// [31:0]
};
 // rhist_Statistics_Result_1_Register Register
struct IRECOG_RHIST_STATISTICS_RESULT_1_REGISTER {
	unsigned int STAT_R1:32;		// [31:0]
};
 // rhist_Statistics_Result_2_Register Register
struct IRECOG_RHIST_STATISTICS_RESULT_2_REGISTER {
	unsigned int STAT_R2:32;		// [31:0]
};
 // rmatch_Control_and_Status_Register Register
struct IRECOG_RMATCH_CONTROL_AND_STATUS_REGISTER {
	unsigned int CMD:1;		// [0]
	unsigned int RST:1;		// [1]
	unsigned int INT:1;		// [2]
	unsigned int reserved:29;		// [31:3]
};
 // rmatch_Mode_Register Register
struct IRECOG_RMATCH_MODE_REGISTER {
	unsigned int Mode:2;		// [1:0]
	unsigned int CROSS_CHECK:1;		// [2]
	unsigned int reserved2:1;		// [3]
	unsigned int CC_LIMIT:4;		// [7:4]
	unsigned int OFF_Y:6;		// [13:8]
	unsigned int reserved:18;		// [31:14]
};
 // rmatch_Pitch_Size_Register Register
struct IRECOG_RMATCH_PITCH_SIZE_REGISTER {
	unsigned int CUR_P:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int REF_P:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rmatch_Reference_Image_Size_register Register
struct IRECOG_RMATCH_REFERENCE_IMAGE_SIZE_REGISTER {
	unsigned int REF_H:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int REF_W:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rmatch_Input_Image_Search_Area_Posion_Register Register
struct IRECOG_RMATCH_INPUT_IMAGE_SEARCH_AREA_POSION_REGISTER {
	unsigned int CA_Y:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int CA_X:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rmatch_Input_Image_Search_Area_Size_Register Register
struct IRECOG_RMATCH_INPUT_IMAGE_SEARCH_AREA_SIZE_REGISTER {
	unsigned int CA_H:11;		// [10:0]
	unsigned int reserved2:5;		// [15:11]
	unsigned int CA_W:11;		// [26:16]
	unsigned int reserved:5;		// [31:27]
};
 // rmatch_Block_Size_and_Disparity_Register Register
struct IRECOG_RMATCH_BLOCK_SIZE_AND_DISPARITY_REGISTER {
	unsigned int D1:8;		// [7:0]
	unsigned int D2:8;		// [15:8]
	unsigned int BLK_H:4;		// [19:16]
	unsigned int BLK_W:4;		// [23:20]
	unsigned int reserved:8;		// [31:24]
};
 // rmatch_Input_Image_Address_Register Register
struct IRECOG_RMATCH_INPUT_IMAGE_ADDRESS_REGISTER {
	unsigned int CUR_A:32;		// [31:0]
};
 // rmatch_Reference_Image_Address_Register Register
struct IRECOG_RMATCH_REFERENCE_IMAGE_ADDRESS_REGISTER {
	unsigned int REF_A:32;		// [31:0]
};
 // rmatch_Parameter_Set_Address_Register Register
struct IRECOG_RMATCH_PARAMETER_SET_ADDRESS_REGISTER {
	unsigned int PARAM_A:32;		// [31:0]
};
 // rmatch_Output_Set_1_Address_Register Register
struct IRECOG_RMATCH_OUTPUT_SET_1_ADDRESS_REGISTER {
	unsigned int OUT1_A:32;		// [31:0]
};
 // rmatch_Output_Set_2_Address_Register Register
struct IRECOG_RMATCH_OUTPUT_SET_2_ADDRESS_REGISTER {
	unsigned int OUT2_A:32;		// [31:0]
};
 // rmatch_Progress_Register Register
struct IRECOG_RMATCH_PROGRESS_REGISTER {
	unsigned int TOTAL:14;		// [13:0]
	unsigned int reserved2:2;		// [15:14]
	unsigned int PASS:14;		// [29:16]
	unsigned int reserved:2;		// [31:30]
};
 // rfilter_RST Register
struct IRECOG_RFILTER_RST {
	unsigned int RST:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // rfilter_CMD Register
struct IRECOG_RFILTER_CMD {
	unsigned int CMD:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // rfilter_INTMASK Register
struct IRECOG_RFILTER_INTMASK {
	unsigned int INITSET:1;		// [0]
	unsigned int NLFOT:1;		// [1]
	unsigned int LFOT:1;		// [2]
	unsigned int NLPT:1;		// [3]
	unsigned int LPT:1;		// [4]
	unsigned int reserved5:4;		// [8:5]
	unsigned int LSC:1;		// [9]
	unsigned int reserved4:1;		// [10]
	unsigned int QF:1;		// [11]
	unsigned int reserved3:1;		// [12]
	unsigned int LME:1;		// [13]
	unsigned int PSBAC:1;		// [14]
	unsigned int reserved2:1;		// [15]
	unsigned int reserved:16;		// [31:16]
};
 // rfilter_INTCLR Register
struct IRECOG_RFILTER_INTCLR {
	unsigned int INITSET:1;		// [0]
	unsigned int NLFOT:1;		// [1]
	unsigned int LFOT:1;		// [2]
	unsigned int NLPT:1;		// [3]
	unsigned int LPT:1;		// [4]
	unsigned int reserved6:3;		// [7:5]
	unsigned int reserved5:1;		// [8]
	unsigned int LSC:1;		// [9]
	unsigned int reserved4:1;		// [10]
	unsigned int QF:1;		// [11]
	unsigned int reserved3:1;		// [12]
	unsigned int LME:1;		// [13]
	unsigned int PSBAC:1;		// [14]
	unsigned int reserved2:1;		// [15]
	unsigned int reserved:16;		// [31:16]
};
 // rfilter_INTSTAT Register
struct IRECOG_RFILTER_INTSTAT {
	unsigned int INITSET:1;		// [0]
	unsigned int NLFOT:1;		// [1]
	unsigned int LFOT:1;		// [2]
	unsigned int NLPT:1;		// [3]
	unsigned int LPT:1;		// [4]
	unsigned int reserved4:4;		// [8:5]
	unsigned int LSC:1;		// [9]
	unsigned int reserved3:1;		// [10]
	unsigned int QF:1;		// [11]
	unsigned int reserved2:1;		// [12]
	unsigned int LME:1;		// [13]
	unsigned int PSBAC:1;		// [14]
	unsigned int reserved:17;		// [31:15]
};
 // rfilter_IFRMCNTV Register
struct IRECOG_RFILTER_IFRMCNTV {
	unsigned int IFRMCNTV:16;		// [15:0]
	unsigned int reserved:16;		// [31:16]
};
 // rfilter_IADDR Register
struct IRECOG_RFILTER_IADDR {
	unsigned int IADDR:32;		// [31:0]
};
 // rfilter_OFRMCNTV Register
struct IRECOG_RFILTER_OFRMCNTV {
	unsigned int OFRMCNTV:16;		// [15:0]
	unsigned int reserved:16;		// [31:16]
};
 // rfilter_OADDR Register
struct IRECOG_RFILTER_OADDR {
	unsigned int OADDR:32;		// [31:0]
};
 // rfilter_TRNSSTAT Register
struct IRECOG_RFILTER_TRNSSTAT {
	unsigned int PT:1;		// [0]
	unsigned int OIT:1;		// [1]
	unsigned int IIT:1;		// [2]
	unsigned int IST:1;		// [3]
	unsigned int reserved:28;		// [31:4]
};
 // rfilter_CRNTFRMNUM Register
struct IRECOG_RFILTER_CRNTFRMNUM {
	unsigned int CRNTFRMNUM:16;		// [15:0]
	unsigned int reserved:16;		// [31:16]
};
 // rfilter_INITSTART Register
struct IRECOG_RFILTER_INITSTART {
	unsigned int INITSTART:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // rfilter_IMGSTART Register
struct IRECOG_RFILTER_IMGSTART {
	unsigned int IMGSTART:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // rfilter_INITTRNUM Register
struct IRECOG_RFILTER_INITTRNUM {
	unsigned int INITTRNUM:4;		// [3:0]
	unsigned int reserved:28;		// [31:4]
};
 // rfilter_IMGFRMCHNUM Register
struct IRECOG_RFILTER_IMGFRMCHNUM {
	unsigned int OCHNUM:4;		// [3:0]
	unsigned int ICHNUM:4;		// [7:4]
	unsigned int reserved:8;		// [15:8]
	unsigned int FNUM:16;		// [31:16]
};
 // rfilter_PRMTRNUM Register
struct IRECOG_RFILTER_PRMTRNUM {
	unsigned int M2CTRNUM:3;		// [2:0]
	unsigned int reserved4:1;		// [3]
	unsigned int reserved3:12;		// [15:4]
	unsigned int C2MTRNUM:3;		// [18:16]
	unsigned int reserved2:1;		// [19]
	unsigned int reserved:12;		// [31:20]
};
 // rfilter_DINITIADDR0 Register
struct IRECOG_RFILTER_DINITIADDR0 {
	unsigned int reserved:4;		// [3:0]
	unsigned int DINITIADDR0:28;		// [31:4]
};
 // rfilter_CINITADDRSIZE0 Register
struct IRECOG_RFILTER_CINITADDRSIZE0 {
	unsigned int CHIFADDR0:14;		// [13:0]
	unsigned int reserved2:2;		// [15:14]
	unsigned int CINITSIZE0:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rfilter_DINITIADDR1 Register
struct IRECOG_RFILTER_DINITIADDR1 {
	unsigned int reserved:4;		// [3:0]
	unsigned int DINITIADDR1:28;		// [31:4]
};
 // rfilter_CINITADDRSIZE1 Register
struct IRECOG_RFILTER_CINITADDRSIZE1 {
	unsigned int CHIFADDR1:14;		// [13:0]
	unsigned int reserved2:2;		// [15:14]
	unsigned int CINITSIZE1:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rfilter_DINITIADDR2 Register
struct IRECOG_RFILTER_DINITIADDR2 {
	unsigned int reserved:4;		// [3:0]
	unsigned int DINITIADDR2:28;		// [31:4]
};
 // rfilter_CINITADDRSIZE2 Register
struct IRECOG_RFILTER_CINITADDRSIZE2 {
	unsigned int CHIFADDR2:14;		// [13:0]
	unsigned int reserved2:2;		// [15:14]
	unsigned int CINITSIZE2:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rfilter_DINITIADDR3 Register
struct IRECOG_RFILTER_DINITIADDR3 {
	unsigned int reserved:4;		// [3:0]
	unsigned int DINITIADDR3:28;		// [31:4]
};
 // rfilter_CINITADDRSIZE3 Register
struct IRECOG_RFILTER_CINITADDRSIZE3 {
	unsigned int CHIFADDR3:14;		// [13:0]
	unsigned int reserved2:2;		// [15:14]
	unsigned int CINITSIZE3:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rfilter_DINITIADDR4 Register
struct IRECOG_RFILTER_DINITIADDR4 {
	unsigned int reserved:4;		// [3:0]
	unsigned int DINITIADDR4:28;		// [31:4]
};
 // rfilter_CINITADDRSIZE4 Register
struct IRECOG_RFILTER_CINITADDRSIZE4 {
	unsigned int CHIFADDR4:14;		// [13:0]
	unsigned int reserved2:2;		// [15:14]
	unsigned int CINITSIZE4:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rfilter_DINITIADDR5 Register
struct IRECOG_RFILTER_DINITIADDR5 {
	unsigned int reserved:4;		// [3:0]
	unsigned int DINITIADDR5:28;		// [31:4]
};
 // rfilter_CINITADDRSIZE5 Register
struct IRECOG_RFILTER_CINITADDRSIZE5 {
	unsigned int CHIFADDR5:14;		// [13:0]
	unsigned int reserved2:2;		// [15:14]
	unsigned int CINITSIZE5:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rfilter_DINITIADDR6 Register
struct IRECOG_RFILTER_DINITIADDR6 {
	unsigned int reserved:4;		// [3:0]
	unsigned int DINITIADDR6:28;		// [31:4]
};
 // rfilter_CINITADDRSIZE6 Register
struct IRECOG_RFILTER_CINITADDRSIZE6 {
	unsigned int CHIFADDR6:14;		// [13:0]
	unsigned int reserved2:2;		// [15:14]
	unsigned int CINITSIZE6:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rfilter_DINITIADDR7 Register
struct IRECOG_RFILTER_DINITIADDR7 {
	unsigned int reserved:4;		// [3:0]
	unsigned int DINITIADDR7:28;		// [31:4]
};
 // rfilter_CINITADDRSIZE7 Register
struct IRECOG_RFILTER_CINITADDRSIZE7 {
	unsigned int CHIFADDR7:14;		// [13:0]
	unsigned int reserved2:2;		// [15:14]
	unsigned int CINITSIZE7:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rfilter_OIMG0INITADDR Register
struct IRECOG_RFILTER_OIMG0INITADDR {
	unsigned int reserved:4;		// [3:0]
	unsigned int OIMG0INITADDR:28;		// [31:4]
};
 // rfilter_OIMG0RATIOOFFSET Register
struct IRECOG_RFILTER_OIMG0RATIOOFFSET {
	unsigned int OIMG0LOFFSET:16;		// [15:0]
	unsigned int OIMG0BITPREC:2;		// [17:16]
	unsigned int OIMG0VRATIO:2;		// [19:18]
	unsigned int OIMG0HRATIO:2;		// [21:20]
	unsigned int reserved:10;		// [31:22]
};
 // rfilter_IIMG0INITADDR Register
struct IRECOG_RFILTER_IIMG0INITADDR {
	unsigned int reserved:4;		// [3:0]
	unsigned int IIMG0INITADDR:28;		// [31:4]
};
 // rfilter_IIMG0RATIOOFFSET Register
struct IRECOG_RFILTER_IIMG0RATIOOFFSET {
	unsigned int IIMG0LOFFSET:16;		// [15:0]
	unsigned int IIMG0BITPREC:2;		// [17:16]
	unsigned int IIMG0VRATIO:2;		// [19:18]
	unsigned int IIMG0HRATIO:2;		// [21:20]
	unsigned int reserved:10;		// [31:22]
};
 // rfilter_OIMG1INITADDR Register
struct IRECOG_RFILTER_OIMG1INITADDR {
	unsigned int reserved:4;		// [3:0]
	unsigned int OIMG1INITADDR:28;		// [31:4]
};
 // rfilter_OIMG1RATIOOFFSET Register
struct IRECOG_RFILTER_OIMG1RATIOOFFSET {
	unsigned int OIMG1LOFFSET:16;		// [15:0]
	unsigned int OIMG1BITPREC:2;		// [17:16]
	unsigned int OIMG1VRATIO:2;		// [19:18]
	unsigned int OIMG1HRATIO:2;		// [21:20]
	unsigned int reserved:10;		// [31:22]
};
 // rfilter_IIMG1INITADDR Register
struct IRECOG_RFILTER_IIMG1INITADDR {
	unsigned int reserved:4;		// [3:0]
	unsigned int IIMG1INITADDR:28;		// [31:4]
};
 // rfilter_IIMG1RATIOOFFSET Register
struct IRECOG_RFILTER_IIMG1RATIOOFFSET {
	unsigned int IIMG1LOFFSET:16;		// [15:0]
	unsigned int IIMG1BITPREC:2;		// [17:16]
	unsigned int IIMG1VRATIO:2;		// [19:18]
	unsigned int IIMG1HRATIO:2;		// [21:20]
	unsigned int reserved:10;		// [31:22]
};
 // rfilter_OIMG2INITADDR Register
struct IRECOG_RFILTER_OIMG2INITADDR {
	unsigned int reserved:4;		// [3:0]
	unsigned int OIMG2INITADDR:28;		// [31:4]
};
 // rfilter_OIMG2RATIOOFFSET Register
struct IRECOG_RFILTER_OIMG2RATIOOFFSET {
	unsigned int OIMG2LOFFSET:16;		// [15:0]
	unsigned int OIMG2BITPREC:2;		// [17:16]
	unsigned int OIMG2VRATIO:2;		// [19:18]
	unsigned int OIMG2HRATIO:2;		// [21:20]
	unsigned int reserved:10;		// [31:22]
};
 // rfilter_IMG2INITADDR Register
struct IRECOG_RFILTER_IMG2INITADDR {
	unsigned int reserved:4;		// [3:0]
	unsigned int IIMG2INITADDR:28;		// [31:4]
};
 // rfilter_IIMG2RATIOOFFSET Register
struct IRECOG_RFILTER_IIMG2RATIOOFFSET {
	unsigned int IIMG2LOFFSET:16;		// [15:0]
	unsigned int IIMG2BITPREC:2;		// [17:16]
	unsigned int IIMG2VRATIO:2;		// [19:18]
	unsigned int IIMG2HRATIO:2;		// [21:20]
	unsigned int reserved:10;		// [31:22]
};
 // rfilter_OIMG3INITADDR Register
struct IRECOG_RFILTER_OIMG3INITADDR {
	unsigned int reserved:4;		// [3:0]
	unsigned int OIMG3INITADDR:28;		// [31:4]
};
 // rfilter_OIMG3RATIOOFFSET Register
struct IRECOG_RFILTER_OIMG3RATIOOFFSET {
	unsigned int OIMG3LOFFSET:16;		// [15:0]
	unsigned int OIMG3BITPREC:2;		// [17:16]
	unsigned int OIMG3VRATIO:2;		// [19:18]
	unsigned int OIMG3HRATIO:2;		// [21:20]
	unsigned int reserved:10;		// [31:22]
};
 // rfilter_IIMG3INITADDR Register
struct IRECOG_RFILTER_IIMG3INITADDR {
	unsigned int reserved:4;		// [3:0]
	unsigned int IIMG3INITADDR:28;		// [31:4]
};
 // rfilter_IIMG3RATIOOFFSET Register
struct IRECOG_RFILTER_IIMG3RATIOOFFSET {
	unsigned int IIMG3LOFFSET:16;		// [15:0]
	unsigned int IIMG3BITPREC:2;		// [17:16]
	unsigned int IIMG3VRATIO:2;		// [19:18]
	unsigned int IIMG3HRATIO:2;		// [21:20]
	unsigned int reserved:10;		// [31:22]
};
 // rfilter_OPRM0MMADDR Register
struct IRECOG_RFILTER_OPRM0MMADDR {
	unsigned int reserved:4;		// [3:0]
	unsigned int OPRM0MMADDR:28;		// [31:4]
};
 // rfilter_OPRM0SIZEHIFADDR Register
struct IRECOG_RFILTER_OPRM0SIZEHIFADDR {
	unsigned int OPRM0HIFADDR:14;		// [13:0]
	unsigned int reserved2:2;		// [15:14]
	unsigned int OPRM0SIZE:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rfilter_IPRM0MMADDR Register
struct IRECOG_RFILTER_IPRM0MMADDR {
	unsigned int reserved:4;		// [3:0]
	unsigned int IPRM0MMADDR:28;		// [31:4]
};
 // rfilter_IPRM0SIZEHIFADDR Register
struct IRECOG_RFILTER_IPRM0SIZEHIFADDR {
	unsigned int IPRM0HIFADDR:14;		// [13:0]
	unsigned int reserved2:2;		// [15:14]
	unsigned int IPRM0SIZEHIFADDR:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rfilter_OPRM1MMADDR Register
struct IRECOG_RFILTER_OPRM1MMADDR {
	unsigned int reserved:4;		// [3:0]
	unsigned int OPRM1MMADDR:28;		// [31:4]
};
 // rfilter_OPRM1SIZEHIFADDR Register
struct IRECOG_RFILTER_OPRM1SIZEHIFADDR {
	unsigned int OPRM1HIFADDR:14;		// [13:0]
	unsigned int reserved2:2;		// [15:14]
	unsigned int OPRM1SIZE:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rfilter_IPRM1MMADDR Register
struct IRECOG_RFILTER_IPRM1MMADDR {
	unsigned int reserved:4;		// [3:0]
	unsigned int IPRM1MMADDR:28;		// [31:4]
};
 // rfilter_IPRM1SIZEHIFADDR Register
struct IRECOG_RFILTER_IPRM1SIZEHIFADDR {
	unsigned int IPRM1HIFADDR:14;		// [13:0]
	unsigned int reserved2:2;		// [15:14]
	unsigned int IPRM1SIZE:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rfilter_OPRM2MMADDR Register
struct IRECOG_RFILTER_OPRM2MMADDR {
	unsigned int reserved:4;		// [3:0]
	unsigned int OPRM2MMADDR:28;		// [31:4]
};
 // rfilter_OPRM2SIZEHIFADDR Register
struct IRECOG_RFILTER_OPRM2SIZEHIFADDR {
	unsigned int OPRM2HIFADDR:14;		// [13:0]
	unsigned int reserved2:2;		// [15:14]
	unsigned int OPRM2SIZE:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rfilter_IPRM2MMADDR Register
struct IRECOG_RFILTER_IPRM2MMADDR {
	unsigned int reserved:4;		// [3:0]
	unsigned int IPRM2MMADDR:28;		// [31:4]
};
 // rfilter_IPRM2SIZEHIFADDR Register
struct IRECOG_RFILTER_IPRM2SIZEHIFADDR {
	unsigned int IPRM2HIFADDR:14;		// [13:0]
	unsigned int reserved2:2;		// [15:14]
	unsigned int IPRM2SIZE:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rfilter_OPRM3MMADDR Register
struct IRECOG_RFILTER_OPRM3MMADDR {
	unsigned int reserved:4;		// [3:0]
	unsigned int OPRM3MMADDR:28;		// [31:4]
};
 // rfilter_OPRM3SIZEHIFADDR Register
struct IRECOG_RFILTER_OPRM3SIZEHIFADDR {
	unsigned int OPRM3HIFADDR:14;		// [13:0]
	unsigned int reserved2:2;		// [15:14]
	unsigned int OPRM3SIZE:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rfilter_IPRM3MMADDR Register
struct IRECOG_RFILTER_IPRM3MMADDR {
	unsigned int reserved:4;		// [3:0]
	unsigned int IPRM3MMADDR:28;		// [31:4]
};
 // rfilter_IPRM3SIZEHIFADDR Register
struct IRECOG_RFILTER_IPRM3SIZEHIFADDR {
	unsigned int IPRM3HIFADDR:14;		// [13:0]
	unsigned int reserved2:2;		// [15:14]
	unsigned int IPRM3SIZE:10;		// [25:16]
	unsigned int reserved:6;		// [31:26]
};
 // rfilter_DBGMODE Register
struct IRECOG_RFILTER_DBGMODE {
	unsigned int DBGMODE:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // rfilter_SSYNCSTAT Register
struct IRECOG_RFILTER_SSYNCSTAT {
	unsigned int SSYNCSTAT:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // rfilter_DUMPHIFADDR Register
struct IRECOG_RFILTER_DUMPHIFADDR {
	unsigned int DUMPHIFADDR:19;		// [18:0]
	unsigned int reserved:13;		// [31:19]
};
 // rfilter_DUMPSTART Register
struct IRECOG_RFILTER_DUMPSTART {
	unsigned int DUMPSTART:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // rfilter_DUMPHIFDATA Register
struct IRECOG_RFILTER_DUMPHIFDATA {
	unsigned int DUMPHIFDATA:16;		// [15:0]
	unsigned int reserved:16;		// [31:16]
};
 // rcohog0_Control_Register Register
struct IRECOG_RCOHOG0_CONTROL_REGISTER {
	unsigned int CMD:1;		// [0]
	unsigned int RST:1;		// [1]
	unsigned int reserved2:8;		// [9:2]
	unsigned int IL_NUM:5;		// [14:10]
	unsigned int IL_HALT:1;		// [15]
	unsigned int reserved:16;		// [31:16]
};
 // rcohog0_Function_Register Register
struct IRECOG_RCOHOG0_FUNCTION_REGISTER {
	unsigned int FUNC_MODE:2;		// [1:0]
	unsigned int HOG_MODE:1;		// [2]
	unsigned int ROI_MODE:1;		// [3]
	unsigned int DICT_NUM:2;		// [5:4]
	unsigned int reserved:26;		// [31:6]
};
 // rcohog0_Interrupt_Mask_Register Register
struct IRECOG_RCOHOG0_INTERRUPT_MASK_REGISTER {
	unsigned int END_MASK:1;		// [0]
	unsigned int reserved2:7;		// [7:1]
	unsigned int ROI_OUT_MASK:1;		// [8]
	unsigned int ROI_OUT_HALT_MASK:1;		// [9]
	unsigned int LH_OFL_MASK:1;		// [10]
	unsigned int LH_OFU_MASK:1;		// [11]
	unsigned int reserved:20;		// [31:12]
};
 // rcohog0_Interrupt_Status_Register Register
struct IRECOG_RCOHOG0_INTERRUPT_STATUS_REGISTER {
	unsigned int END:1;		// [0]
	unsigned int reserved2:7;		// [7:1]
	unsigned int ROI_OUT:1;		// [8]
	unsigned int ROI_OUT_HALT:1;		// [9]
	unsigned int LH_OFL:1;		// [10]
	unsigned int LH_OFU:1;		// [11]
	unsigned int reserved:20;		// [31:12]
};
 // rcohog0_Cell_Format_Register Register
struct IRECOG_RCOHOG0_CELL_FORMAT_REGISTER {
	unsigned int CELL_NUM_W:3;		// [2:0]
	unsigned int CELL_NUM_H:3;		// [5:3]
	unsigned int reserved:10;		// [15:6]
	unsigned int CELL_SIZE_W:8;		// [23:16]
	unsigned int CELL_SIZE_H:8;		// [31:24]
};
 // rcohog0_Region_Of_Interest_Size_Register Register
struct IRECOG_RCOHOG0_REGION_OF_INTEREST_SIZE_REGISTER {
	unsigned int ROI_WDTH:12;		// [11:0]
	unsigned int reserved2:4;		// [15:12]
	unsigned int ROI_HIGT:12;		// [27:16]
	unsigned int reserved:4;		// [31:28]
};
 // rcohog0_Region_Of_Interest_Stride_Register Register
struct IRECOG_RCOHOG0_REGION_OF_INTEREST_STRIDE_REGISTER {
	unsigned int ROI_NUM:16;		// [15:0]
	unsigned int ROI_STRIDE_W:8;		// [23:16]
	unsigned int ROI_STRIDE_H:8;		// [31:24]
};
 // rcohog0_Source_0_Address_Register Register
struct IRECOG_RCOHOG0_SOURCE_0_ADDRESS_REGISTER {
	unsigned int SRC0_ADDR:32;		// [31:0]
};
 // rcohog0_Source_1_Address_Register Register
struct IRECOG_RCOHOG0_SOURCE_1_ADDRESS_REGISTER {
	unsigned int SRC1_ADDR:32;		// [31:0]
};
 // rcohog0_Source_0_Line_Pitch_Register Register
struct IRECOG_RCOHOG0_SOURCE_0_LINE_PITCH_REGISTER {
	unsigned int SRC0_LPTCH_r:4;		// [3:0]
	unsigned int SRC0_LPTCH_w:28;		// [31:4]
};
 // rcohog0_Source_1_Line_Pitch_Register Register
struct IRECOG_RCOHOG0_SOURCE_1_LINE_PITCH_REGISTER {
	unsigned int SRC1_LPTCH_r:4;		// [3:0]
	unsigned int SRC1_LPTCH_w:28;		// [31:4]
};
 // rcohog0_Source_0_Size_Register Register
struct IRECOG_RCOHOG0_SOURCE_0_SIZE_REGISTER {
	unsigned int SRC0_WDTH:16;		// [15:0]
	unsigned int SRC0_HIGT:12;		// [27:16]
	unsigned int SRC0_HBOFFSET:1;		// [28]
	unsigned int SRC0_FMT:3;		// [31:29]
};
 // rcohog0_Source_1_Size_Register Register
struct IRECOG_RCOHOG0_SOURCE_1_SIZE_REGISTER {
	unsigned int SRC1_WDTH:16;		// [15:0]
	unsigned int SRC1_HIGT:12;		// [27:16]
	unsigned int SRC1_HBOFFSET:1;		// [28]
	unsigned int SRC1_FMT:3;		// [31:29]
};
 // rcohog0_Destination_0_Address_Register Register
struct IRECOG_RCOHOG0_DESTINATION_0_ADDRESS_REGISTER {
	unsigned int DST0_ADDR_r:4;		// [3:0]
	unsigned int DST0_ADDR_w:28;		// [31:4]
};
 // rcohog0_Destination_0_Format_Register Register
struct IRECOG_RCOHOG0_DESTINATION_0_FORMAT_REGISTER {
	unsigned int DST0_WDTH:32;		// [31:0]
};
 // rcohog0_Region_Of_Interest_Output_Number_Register Register
struct IRECOG_RCOHOG0_REGION_OF_INTEREST_OUTPUT_NUMBER_REGISTER {
	unsigned int OUT_ROI_NUM:16;		// [15:0]
	unsigned int reserved:16;		// [31:16]
};
 // reserved_rcohog0_0 Register
struct IRECOG_RESERVED_RCOHOG0_0 {
	unsigned int reserved:32;		// [31:0]
};
 // reserved_rcohog0_1 Register
struct IRECOG_RESERVED_RCOHOG0_1 {
	unsigned int reserved:32;		// [31:0]
};
 // rcohog1_Control_Register Register
struct IRECOG_RCOHOG1_CONTROL_REGISTER {
	unsigned int CMD:1;		// [0]
	unsigned int RST:1;		// [1]
	unsigned int reserved2:8;		// [9:2]
	unsigned int IL_NUM:5;		// [14:10]
	unsigned int IL_HALT:1;		// [15]
	unsigned int reserved:16;		// [31:16]
};
 // rcohog1_Function_Register Register
struct IRECOG_RCOHOG1_FUNCTION_REGISTER {
	unsigned int FUNC_MODE:2;		// [1:0]
	unsigned int HOG_MODE:1;		// [2]
	unsigned int ROI_MODE:1;		// [3]
	unsigned int DICT_NUM:2;		// [5:4]
	unsigned int reserved:26;		// [31:6]
};
 // rcohog1_Interrupt_Mask_Register Register
struct IRECOG_RCOHOG1_INTERRUPT_MASK_REGISTER {
	unsigned int END_MASK:1;		// [0]
	unsigned int reserved2:7;		// [7:1]
	unsigned int ROI_OUT_MASK:1;		// [8]
	unsigned int ROI_OUT_HALT_MASK:1;		// [9]
	unsigned int LH_OFL_MASK:1;		// [10]
	unsigned int LH_OFU_MASK:1;		// [11]
	unsigned int reserved:20;		// [31:12]
};
 // rcohog1_Interrupt_Status_Register Register
struct IRECOG_RCOHOG1_INTERRUPT_STATUS_REGISTER {
	unsigned int END:1;		// [0]
	unsigned int reserved2:7;		// [7:1]
	unsigned int ROI_OUT:1;		// [8]
	unsigned int ROI_OUT_HALT:1;		// [9]
	unsigned int LH_OFL:1;		// [10]
	unsigned int LH_OFU:1;		// [11]
	unsigned int reserved:20;		// [31:12]
};
 // rcohog1_Cell_Format_Register Register
struct IRECOG_RCOHOG1_CELL_FORMAT_REGISTER {
	unsigned int CELL_NUM_W:3;		// [2:0]
	unsigned int CELL_NUM_H:3;		// [5:3]
	unsigned int reserved:10;		// [15:6]
	unsigned int CELL_SIZE_W:8;		// [23:16]
	unsigned int CELL_SIZE_H:8;		// [31:24]
};
 // rcohog1_Region_Of_Interest_Size_Register Register
struct IRECOG_RCOHOG1_REGION_OF_INTEREST_SIZE_REGISTER {
	unsigned int ROI_WDTH:12;		// [11:0]
	unsigned int reserved2:4;		// [15:12]
	unsigned int ROI_HIGT:12;		// [27:16]
	unsigned int reserved:4;		// [31:28]
};
 // rcohog1_Region_Of_Interest_Stride_Register Register
struct IRECOG_RCOHOG1_REGION_OF_INTEREST_STRIDE_REGISTER {
	unsigned int ROI_NUM:16;		// [15:0]
	unsigned int ROI_STRIDE_W:8;		// [23:16]
	unsigned int ROI_STRIDE_H:8;		// [31:24]
};
 // rcohog1_Source_0_Address_Register Register
struct IRECOG_RCOHOG1_SOURCE_0_ADDRESS_REGISTER {
	unsigned int SRC0_ADDR:32;		// [31:0]
};
 // rcohog1_Source_1_Address_Register Register
struct IRECOG_RCOHOG1_SOURCE_1_ADDRESS_REGISTER {
	unsigned int SRC1_ADDR:32;		// [31:0]
};
 // rcohog1_Source_0_Line_Pitch_Register Register
struct IRECOG_RCOHOG1_SOURCE_0_LINE_PITCH_REGISTER {
	unsigned int SRC0_LPTCH_r:4;		// [3:0]
	unsigned int SRC0_LPTCH_w:28;		// [31:4]
};
 // rcohog1_Source_1_Line_Pitch_Register Register
struct IRECOG_RCOHOG1_SOURCE_1_LINE_PITCH_REGISTER {
	unsigned int SRC1_LPTCH_r:4;		// [3:0]
	unsigned int SRC1_LPTCH_w:28;		// [31:4]
};
 // rcohog1_Source_0_Size_Register Register
struct IRECOG_RCOHOG1_SOURCE_0_SIZE_REGISTER {
	unsigned int SRC0_WDTH:16;		// [15:0]
	unsigned int SRC0_HIGT:12;		// [27:16]
	unsigned int SRC0_HBOFFSET:1;		// [28]
	unsigned int SRC0_FMT:3;		// [31:29]
};
 // rcohog1_Source_1_Size_Register Register
struct IRECOG_RCOHOG1_SOURCE_1_SIZE_REGISTER {
	unsigned int SRC1_WDTH:16;		// [15:0]
	unsigned int SRC1_HIGT:12;		// [27:16]
	unsigned int SRC1_HBOFFSET:1;		// [28]
	unsigned int SRC1_FMT:3;		// [31:29]
};
 // rcohog1_Destination_0_Address_Register Register
struct IRECOG_RCOHOG1_DESTINATION_0_ADDRESS_REGISTER {
	unsigned int DST0_ADDR_r:4;		// [3:0]
	unsigned int DST0_ADDR_w:28;		// [31:4]
};
 // rcohog1_Destination_0_Format_Register Register
struct IRECOG_RCOHOG1_DESTINATION_0_FORMAT_REGISTER {
	unsigned int DST0_WDTH:32;		// [31:0]
};
 // rcohog1_Region_Of_Interest_Output_Number_Register Register
struct IRECOG_RCOHOG1_REGION_OF_INTEREST_OUTPUT_NUMBER_REGISTER {
	unsigned int OUT_ROI_NUM:16;		// [15:0]
	unsigned int reserved:16;		// [31:16]
};
 // reserved_rcohog1_0 Register
struct IRECOG_RESERVED_RCOHOG1_0 {
	unsigned int reserved:32;		// [31:0]
};
 // reserved_rcohog1_1 Register
struct IRECOG_RESERVED_RCOHOG1_1 {
	unsigned int reserved:32;		// [31:0]
};
 // rcohog_Control_Register Register
struct IRECOG_RCOHOG_CONTROL_REGISTER {
	unsigned int cohog_select:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _IRECOG_REG_STRUCT_L_H */
