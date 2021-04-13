/*
 * arch/arm/mach-tz3000/include/mach/regs/vconv_reg_struct_b.h
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

#ifndef _VCONV_REG_STRUCT_B_H
#define _VCONV_REG_STRUCT_B_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // VCONV_START Register
struct VCONV_VCONV_START {
	unsigned int Reserved:30;		// [31:2]
	unsigned int CHANNEL:1;		// [1]
	unsigned int START:1;		// [0]
};
 // VCONV_ABORT Register
struct VCONV_VCONV_ABORT {
	unsigned int Reserved:31;		// [31:1]
	unsigned int ABORT:1;		// [0]
};
 // VCONV_SET_DUMMY_READ Register
struct VCONV_VCONV_SET_DUMMY_READ {
	unsigned int Reserved:28;		// [31:4]
	unsigned int DUMMY_READ:4;		// [3:0]
};
 // VCONV_SET_BUSIF Register
struct VCONV_VCONV_SET_BUSIF {
	unsigned int Reserved:28;		// [31:4]
	unsigned int OUTSTAND_CMD:4;		// [3:0]
};
 // VCONV_SET_SEL_ALPHA Register
struct VCONV_VCONV_SET_SEL_ALPHA {
	unsigned int Reserved:31;		// [31:1]
	unsigned int SEL_ALPHA:1;		// [0]
};
 // VCONV_IRQ Register
struct VCONV_VCONV_IRQ {
	unsigned int Reserved2:24;		// [31:8]
	unsigned int MERGE_ERROR_IRQ:1;		// [7]
	unsigned int DISP_ERROR_IRQ:1;		// [6]
	unsigned int REG_ERROR_IRQ:1;		// [5]
	unsigned int START_ERROR_IRQ:1;		// [4]
	unsigned int Reserved:3;		// [3:1]
	unsigned int FRAME_END_IRQ:1;		// [0]
};
 // VCONV_SET_IRQ_MASK Register
struct VCONV_VCONV_SET_IRQ_MASK {
	unsigned int Reserved2:24;		// [31:8]
	unsigned int MERGE_ERROR_MASK:1;		// [7]
	unsigned int DISP_ERROR_MASK:1;		// [6]
	unsigned int REG_ERROR_MASK:1;		// [5]
	unsigned int START_ERROR_MASK:1;		// [4]
	unsigned int Reserved:3;		// [3:1]
	unsigned int FRAME_END_MASK:1;		// [0]
};
 // VCONV_SET_Y2RMTX_OFFSET Register
struct VCONV_VCONV_SET_Y2RMTX_OFFSET {
	unsigned int Reserved2:8;		// [31:24]
	unsigned int Y2R_COFFSET:8;		// [23:16]
	unsigned int Reserved:8;		// [15:8]
	unsigned int Y2R_YOFFSET:8;		// [7:0]
};
 // VCONV_SET_Y2RMTX_COEF00 Register
struct VCONV_VCONV_SET_Y2RMTX_COEF00 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int Y2R_COEF00:10;		// [9:0]
};
 // VCONV_SET_Y2RMTX_COEF01 Register
struct VCONV_VCONV_SET_Y2RMTX_COEF01 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int Y2R_COEF01:10;		// [9:0]
};
 // VCONV_SET_Y2RMTX_COEF02 Register
struct VCONV_VCONV_SET_Y2RMTX_COEF02 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int Y2R_COEF02:10;		// [9:0]
};
 // VCONV_SET_Y2RMTX_COEF10 Register
struct VCONV_VCONV_SET_Y2RMTX_COEF10 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int Y2R_COEF10:10;		// [9:0]
};
 // VCONV_SET_Y2RMTX_COEF11 Register
struct VCONV_VCONV_SET_Y2RMTX_COEF11 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int Y2R_COEF11:10;		// [9:0]
};
 // VCONV_SET_Y2RMTX_COEF12 Register
struct VCONV_VCONV_SET_Y2RMTX_COEF12 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int Y2R_COEF12:10;		// [9:0]
};
 // VCONV_SET_Y2RMTX_COEF20 Register
struct VCONV_VCONV_SET_Y2RMTX_COEF20 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int Y2R_COEF20:10;		// [9:0]
};
 // VCONV_SET_Y2RMTX_COEF21 Register
struct VCONV_VCONV_SET_Y2RMTX_COEF21 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int Y2R_COEF21:10;		// [9:0]
};
 // VCONV_SET_Y2RMTX_COEF22 Register
struct VCONV_VCONV_SET_Y2RMTX_COEF22 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int Y2R_COEF22:10;		// [9:0]
};
 // VCONV_SET_RGBLIMIT Register
struct VCONV_VCONV_SET_RGBLIMIT {
	unsigned int Reserved2:8;		// [31:24]
	unsigned int Y2R_RGBMIN_LIMIT:8;		// [23:16]
	unsigned int Reserved:8;		// [15:8]
	unsigned int Y2R_RGBMAX_LIMIT:8;		// [7:0]
};
 // VCONV_SET_R2YMTX_OFFSET Register
struct VCONV_VCONV_SET_R2YMTX_OFFSET {
	unsigned int Reserved2:8;		// [31:24]
	unsigned int R2Y_COFFSET:8;		// [23:16]
	unsigned int Reserved:8;		// [15:8]
	unsigned int R2Y_YOFFSET:8;		// [7:0]
};
 // VCONV_SET_R2YMTX_COEF00 Register
struct VCONV_VCONV_SET_R2YMTX_COEF00 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int R2Y_COEF00:10;		// [9:0]
};
 // VCONV_SET_R2YMTX_COEF01 Register
struct VCONV_VCONV_SET_R2YMTX_COEF01 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int R2Y_COEF01:10;		// [9:0]
};
 // VCONV_SET_R2YMTX_COEF02 Register
struct VCONV_VCONV_SET_R2YMTX_COEF02 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int R2Y_COEF02:10;		// [9:0]
};
 // VCONV_SET_R2YMTX_COEF10 Register
struct VCONV_VCONV_SET_R2YMTX_COEF10 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int R2Y_COEF10:10;		// [9:0]
};
 // VCONV_SET_R2YMTX_COEF11 Register
struct VCONV_VCONV_SET_R2YMTX_COEF11 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int R2Y_COEF11:10;		// [9:0]
};
 // VCONV_SET_R2YMTX_COEF12 Register
struct VCONV_VCONV_SET_R2YMTX_COEF12 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int R2Y_COEF12:10;		// [9:0]
};
 // VCONV_SET_R2YMTX_COEF20 Register
struct VCONV_VCONV_SET_R2YMTX_COEF20 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int R2Y_COEF20:10;		// [9:0]
};
 // VCONV_SET_R2YMTX_COEF21 Register
struct VCONV_VCONV_SET_R2YMTX_COEF21 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int R2Y_COEF21:10;		// [9:0]
};
 // VCONV_SET_R2YMTX_COEF22 Register
struct VCONV_VCONV_SET_R2YMTX_COEF22 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int R2Y_COEF22:10;		// [9:0]
};
 // VCONV_SET_YLIMIT Register
struct VCONV_VCONV_SET_YLIMIT {
	unsigned int Reserved2:8;		// [31:24]
	unsigned int R2Y_YMIN_LIMIT:8;		// [23:16]
	unsigned int Reserved:8;		// [15:8]
	unsigned int R2Y_YMAX_LIMIT:8;		// [7:0]
};
 // VCONV_SET_CLIMIT Register
struct VCONV_VCONV_SET_CLIMIT {
	unsigned int Reserved2:8;		// [31:24]
	unsigned int R2Y_CMIN_LIMIT:8;		// [23:16]
	unsigned int Reserved:8;		// [15:8]
	unsigned int R2Y_CMAX_LIMIT:8;		// [7:0]
};
 // VCONV_TRANS_IN_FORMAT Register
struct VCONV_VCONV_TRANS_IN_FORMAT {
	unsigned int Reserved4:8;		// [31:24]
	unsigned int IN_FORMATID:8;		// [23:16]
	unsigned int Reserved3:7;		// [15:9]
	unsigned int IN_SCAN:1;		// [8]
	unsigned int Reserved2:2;		// [7:6]
	unsigned int IN_PLANE:2;		// [5:4]
	unsigned int Reserved:2;		// [3:2]
	unsigned int IN_COLORFORMAT:2;		// [1:0]
};
 // VCONV_TRANS_IN_HSIZE Register
struct VCONV_VCONV_TRANS_IN_HSIZE {
	unsigned int Reserved:21;		// [31:11]
	unsigned int IN_HSIZE:11;		// [10:0]
};
 // VCONV_TRANS_IN_VSIZE Register
struct VCONV_VCONV_TRANS_IN_VSIZE {
	unsigned int Reserved:21;		// [31:11]
	unsigned int IN_VSIZE:11;		// [10:0]
};
 // VCONV_TRANS_IN_BASEADDR_A Register
struct VCONV_VCONV_TRANS_IN_BASEADDR_A {
	unsigned int IN_BADDR_A:32;		// [31:0]
};
 // VCONV_TRANS_IN_BASEADDR_B Register
struct VCONV_VCONV_TRANS_IN_BASEADDR_B {
	unsigned int IN_BADDR_B:32;		// [31:0]
};
 // VCONV_TRANS_IN_BASEADDR_C Register
struct VCONV_VCONV_TRANS_IN_BASEADDR_C {
	unsigned int IN_BADDR_C:32;		// [31:0]
};
 // VCONV_TRANS_IN_PITCH_A Register
struct VCONV_VCONV_TRANS_IN_PITCH_A {
	unsigned int Reserved:19;		// [31:13]
	unsigned int IN_PITCH_A:13;		// [12:0]
};
 // VCONV_TRANS_IN_PITCH_B Register
struct VCONV_VCONV_TRANS_IN_PITCH_B {
	unsigned int Reserved:19;		// [31:13]
	unsigned int IN_PITCH_B:13;		// [12:0]
};
 // VCONV_TRANS_IN_PITCH_C Register
struct VCONV_VCONV_TRANS_IN_PITCH_C {
	unsigned int Reserved:19;		// [31:13]
	unsigned int IN_PITCH_C:13;		// [12:0]
};
 // VCONV_TRANS_OUT_FORMAT Register
struct VCONV_VCONV_TRANS_OUT_FORMAT {
	unsigned int Reserved4:8;		// [31:24]
	unsigned int OUT_FORMATID:8;		// [23:16]
	unsigned int Reserved3:7;		// [15:9]
	unsigned int OUT_SCAN:1;		// [8]
	unsigned int Reserved2:2;		// [7:6]
	unsigned int OUT_PLANE:2;		// [5:4]
	unsigned int Reserved:2;		// [3:2]
	unsigned int OUT_COLORFORMAT:2;		// [1:0]
};
 // VCONV_TRANS_OUT_HSIZE Register
struct VCONV_VCONV_TRANS_OUT_HSIZE {
	unsigned int Reserved:21;		// [31:11]
	unsigned int OUT_HSIZE:11;		// [10:0]
};
 // VCONV_TRANS_OUT_VSIZE Register
struct VCONV_VCONV_TRANS_OUT_VSIZE {
	unsigned int Reserved:21;		// [31:11]
	unsigned int OUT_VSIZE:11;		// [10:0]
};
 // VCONV_TRANS_OUT_BASEADDR_A Register
struct VCONV_VCONV_TRANS_OUT_BASEADDR_A {
	unsigned int OUT_BADDR_A:32;		// [31:0]
};
 // VCONV_TRANS_OUT_BASEADDR_B Register
struct VCONV_VCONV_TRANS_OUT_BASEADDR_B {
	unsigned int OUT_BADDR_B:32;		// [31:0]
};
 // VCONV_TRANS_OUT_BASEADDR_C Register
struct VCONV_VCONV_TRANS_OUT_BASEADDR_C {
	unsigned int OUT_BADDR_C:32;		// [31:0]
};
 // VCONV_TRANS_OUT_PITCH_A Register
struct VCONV_VCONV_TRANS_OUT_PITCH_A {
	unsigned int Reserved:19;		// [31:13]
	unsigned int OUT_PITCH_A:13;		// [12:0]
};
 // VCONV_TRANS_OUT_PITCH_B Register
struct VCONV_VCONV_TRANS_OUT_PITCH_B {
	unsigned int Reserved:19;		// [31:13]
	unsigned int OUT_PITCH_B:13;		// [12:0]
};
 // VCONV_TRANS_OUT_PITCH_C Register
struct VCONV_VCONV_TRANS_OUT_PITCH_C {
	unsigned int Reserved:19;		// [31:13]
	unsigned int OUT_PITCH_C:13;		// [12:0]
};
 // VCONV_TRANS_OUT_HOFFSET Register
struct VCONV_VCONV_TRANS_OUT_HOFFSET {
	unsigned int Reserved:21;		// [31:11]
	unsigned int OUT_HOFFSET:11;		// [10:0]
};
 // VCONV_TRANS_OUT_VOFFSET Register
struct VCONV_VCONV_TRANS_OUT_VOFFSET {
	unsigned int Reserved:21;		// [31:11]
	unsigned int OUT_VOFFSET:11;		// [10:0]
};
 // VCONV_TRANS_OUT_HSCALE Register
struct VCONV_VCONV_TRANS_OUT_HSCALE {
	unsigned int Reserved:13;		// [31:19]
	unsigned int HSCALE_INTEGER:3;		// [18:16]
	unsigned int HSCALE_FRACTON:16;		// [15:0]
};
 // VCONV_TRANS_OUT_VSCALE Register
struct VCONV_VCONV_TRANS_OUT_VSCALE {
	unsigned int Reserved:13;		// [31:19]
	unsigned int VSCALE_INTEGER:3;		// [18:16]
	unsigned int VSCALE_FRACTON:16;		// [15:0]
};
 // VCONV_TRANS_OUT_HDELTA Register
struct VCONV_VCONV_TRANS_OUT_HDELTA {
	unsigned int Reserved:21;		// [31:11]
	unsigned int reserved2:1;		// [10]
	unsigned int HDELTA:10;		// [9:0]
};
 // VCONV_TRANS_OUT_VDELTA Register
struct VCONV_VCONV_TRANS_OUT_VDELTA {
	unsigned int Reserved:21;		// [31:11]
	unsigned int reserved2:1;		// [10]
	unsigned int VDELTA:10;		// [9:0]
};
 // VCONV_TRANS_FORCE_MODE Register
struct VCONV_VCONV_TRANS_FORCE_MODE {
	unsigned int Reserved:31;		// [31:1]
	unsigned int FORCE_MODE:1;		// [0]
};
 // VCONV_CH_FORCE_GY Register
struct VCONV_VCONV_CH_FORCE_GY {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_GY:8;		// [7:0]
};
 // VCONV_CH_FORCE_BCB Register
struct VCONV_VCONV_CH_FORCE_BCB {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_BCB:8;		// [7:0]
};
 // VCONV_CH_FORCE_R Register
struct VCONV_VCONV_CH_FORCE_R {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_RCR:8;		// [7:0]
};
 // VCONV_CH_FORCE_A Register
struct VCONV_VCONV_CH_FORCE_A {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_ALPHA:8;		// [7:0]
};
 // VCONV_TRANS_CROP Register
struct VCONV_VCONV_TRANS_CROP {
	unsigned int Reserved4:4;		// [31:28]
	unsigned int CROP_RIGHT:4;		// [27:24]
	unsigned int Reserved3:4;		// [23:20]
	unsigned int CROP_LEFT:4;		// [19:16]
	unsigned int Reserved2:4;		// [15:12]
	unsigned int CROP_LOWER:4;		// [11:8]
	unsigned int Reserved:4;		// [7:4]
	unsigned int CROP_UPPER:4;		// [3:0]
};
 // VCONV_TRANS_STATUS Register
struct VCONV_VCONV_TRANS_STATUS {
	unsigned int Reserved2:23;		// [31:9]
	unsigned int MERGE_STATUS:1;		// [8]
	unsigned int Reserved:6;		// [7:2]
	unsigned int TRANS_CHANNEL:1;		// [1]
	unsigned int TRUNS_STATUS:1;		// [0]
};
 // VCONV_TRANS_LINE Register
struct VCONV_VCONV_TRANS_LINE {
	unsigned int Reserved2:5;		// [31:27]
	unsigned int OUTPUT_LINE:11;		// [26:16]
	unsigned int Reserved:5;		// [15:11]
	unsigned int INPUT_LINE:11;		// [10:0]
};
 // VCONV_SET_IN_FORMAT0 Register
struct VCONV_VCONV_SET_IN_FORMAT0 {
	unsigned int Reserved4:8;		// [31:24]
	unsigned int IN_FORMATID0:8;		// [23:16]
	unsigned int Reserved3:7;		// [15:9]
	unsigned int IN_SCAN0:1;		// [8]
	unsigned int Reserved2:2;		// [7:6]
	unsigned int IN_PLANE0:2;		// [5:4]
	unsigned int Reserved:2;		// [3:2]
	unsigned int IN_COLORFORMAT0:2;		// [1:0]
};
 // VCONV_SET_IN_HSIZE0 Register
struct VCONV_VCONV_SET_IN_HSIZE0 {
	unsigned int Reserved:21;		// [31:11]
	unsigned int IN_HSIZE0:11;		// [10:0]
};
 // VCONV_SET_IN_VSIZE0 Register
struct VCONV_VCONV_SET_IN_VSIZE0 {
	unsigned int Reserved:21;		// [31:11]
	unsigned int IN_VSIZE0:11;		// [10:0]
};
 // VCONV_SET_IN_BASEADDR_A0 Register
struct VCONV_VCONV_SET_IN_BASEADDR_A0 {
	unsigned int IN_BADDR_A0:32;		// [31:0]
};
 // VCONV_SET_IN_BASEADDR_B0 Register
struct VCONV_VCONV_SET_IN_BASEADDR_B0 {
	unsigned int IN_BADDR_B0:32;		// [31:0]
};
 // VCONV_SET_IN_BASEADDR_C0 Register
struct VCONV_VCONV_SET_IN_BASEADDR_C0 {
	unsigned int IN_BADDR_C0:32;		// [31:0]
};
 // VCONV_SET_IN_PITCH_A0 Register
struct VCONV_VCONV_SET_IN_PITCH_A0 {
	unsigned int Reserved:19;		// [31:13]
	unsigned int IN_PITCH_A0:13;		// [12:0]
};
 // VCONV_SET_IN_PITCH_B0 Register
struct VCONV_VCONV_SET_IN_PITCH_B0 {
	unsigned int Reserved:19;		// [31:13]
	unsigned int IN_PITCH_B0:13;		// [12:0]
};
 // VCONV_SET_IN_PITCH_C0 Register
struct VCONV_VCONV_SET_IN_PITCH_C0 {
	unsigned int Reserved:19;		// [31:13]
	unsigned int IN_PITCH_C0:13;		// [12:0]
};
 // VCONV_SET_OUT_FORMAT0 Register
struct VCONV_VCONV_SET_OUT_FORMAT0 {
	unsigned int Reserved4:8;		// [31:24]
	unsigned int OUT_FORMATID0:8;		// [23:16]
	unsigned int Reserved3:7;		// [15:9]
	unsigned int OUT_SCAN0:1;		// [8]
	unsigned int Reserved2:2;		// [7:6]
	unsigned int OUT_PLANE0:2;		// [5:4]
	unsigned int Reserved:2;		// [3:2]
	unsigned int OUT_COLORFORMAT0:2;		// [1:0]
};
 // VCONV_SET_OUT_HSIZE0 Register
struct VCONV_VCONV_SET_OUT_HSIZE0 {
	unsigned int Reserved:21;		// [31:11]
	unsigned int OUT_HSIZE0:11;		// [10:0]
};
 // VCONV_SET_OUT_VSIZE0 Register
struct VCONV_VCONV_SET_OUT_VSIZE0 {
	unsigned int Reserved:21;		// [31:11]
	unsigned int OUT_VSIZE0:11;		// [10:0]
};
 // VCONV_SET_OUT_BASEADDR_A0 Register
struct VCONV_VCONV_SET_OUT_BASEADDR_A0 {
	unsigned int OUT_BADDR_A0:32;		// [31:0]
};
 // VCONV_SET_OUT_BASEADDR_B0 Register
struct VCONV_VCONV_SET_OUT_BASEADDR_B0 {
	unsigned int OUT_BADDR_B0:32;		// [31:0]
};
 // VCONV_SET_OUT_BASEADDR_C0 Register
struct VCONV_VCONV_SET_OUT_BASEADDR_C0 {
	unsigned int OUT_BADDR_C0:32;		// [31:0]
};
 // VCONV_SET_OUT_PITCH_A0 Register
struct VCONV_VCONV_SET_OUT_PITCH_A0 {
	unsigned int Reserved:19;		// [31:13]
	unsigned int OUT_PITCH_A0:13;		// [12:0]
};
 // VCONV_SET_OUT_PITCH_B0 Register
struct VCONV_VCONV_SET_OUT_PITCH_B0 {
	unsigned int Reserved:19;		// [31:13]
	unsigned int OUT_PITCH_B0:13;		// [12:0]
};
 // VCONV_SET_OUT_PITCH_C0 Register
struct VCONV_VCONV_SET_OUT_PITCH_C0 {
	unsigned int Reserved:19;		// [31:13]
	unsigned int OUT_PITCH_C0:13;		// [12:0]
};
 // VCONV_SET_OUT_HOFFSET0 Register
struct VCONV_VCONV_SET_OUT_HOFFSET0 {
	unsigned int Reserved:21;		// [31:11]
	unsigned int OUT_HOFFSET0:11;		// [10:0]
};
 // VCONV_SET_OUT_VOFFSET0 Register
struct VCONV_VCONV_SET_OUT_VOFFSET0 {
	unsigned int Reserved:21;		// [31:11]
	unsigned int OUT_VOFFSET0:11;		// [10:0]
};
 // VCONV_SET_OUT_HSCALE0 Register
struct VCONV_VCONV_SET_OUT_HSCALE0 {
	unsigned int Reserved:13;		// [31:19]
	unsigned int HSCALE_INTEGER0:3;		// [18:16]
	unsigned int HSCALE_FRACTON0:16;		// [15:0]
};
 // VCONV_SET_OUT_VSCALE0 Register
struct VCONV_VCONV_SET_OUT_VSCALE0 {
	unsigned int Reserved:13;		// [31:19]
	unsigned int VSCALE_INTEGER0:3;		// [18:16]
	unsigned int VSCALE_FRACTON0:16;		// [15:0]
};
 // VCONV_SET_OUT_HDELTA0 Register
struct VCONV_VCONV_SET_OUT_HDELTA0 {
	unsigned int Reserved:21;		// [31:11]
	unsigned int reserved2:1;		// [10]
	unsigned int HDELTA0:10;		// [9:0]
};
 // VCONV_SET_OUT_VDELTA0 Register
struct VCONV_VCONV_SET_OUT_VDELTA0 {
	unsigned int Reserved:21;		// [31:11]
	unsigned int reserved2:1;		// [10]
	unsigned int VDELTA0:10;		// [9:0]
};
 // VCONV_SET_FORCE_MODE0 Register
struct VCONV_VCONV_SET_FORCE_MODE0 {
	unsigned int Reserved:31;		// [31:1]
	unsigned int FORCE_MODE0:1;		// [0]
};
 // VCONV_SET_FORCE_GY0 Register
struct VCONV_VCONV_SET_FORCE_GY0 {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_GY0:8;		// [7:0]
};
 // VCONV_SET_FORCE_BCB0 Register
struct VCONV_VCONV_SET_FORCE_BCB0 {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_BCB0:8;		// [7:0]
};
 // VCONV_SET_FORCE_RCR0 Register
struct VCONV_VCONV_SET_FORCE_RCR0 {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_RCR0:8;		// [7:0]
};
 // VCONV_SET_FORCE_A0 Register
struct VCONV_VCONV_SET_FORCE_A0 {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_ALPHA0:8;		// [7:0]
};
 // VCONV_SET_CROP0 Register
struct VCONV_VCONV_SET_CROP0 {
	unsigned int Reserved4:4;		// [31:28]
	unsigned int CROP_RIGHT0:4;		// [27:24]
	unsigned int Reserved3:4;		// [23:20]
	unsigned int CROP_LEFT0:4;		// [19:16]
	unsigned int Reserved2:4;		// [15:12]
	unsigned int CROP_LOWER0:4;		// [11:8]
	unsigned int Reserved:4;		// [7:4]
	unsigned int CROP_UPPER0:4;		// [3:0]
};
 // VCONV_SET_IN_FORMAT1 Register
struct VCONV_VCONV_SET_IN_FORMAT1 {
	unsigned int Reserved4:8;		// [31:24]
	unsigned int IN_FORMATID1:8;		// [23:16]
	unsigned int Reserved3:7;		// [15:9]
	unsigned int IN_SCAN1:1;		// [8]
	unsigned int Reserved2:2;		// [7:6]
	unsigned int IN_PLANE1:2;		// [5:4]
	unsigned int Reserved:2;		// [3:2]
	unsigned int IN_COLORFORMAT1:2;		// [1:0]
};
 // VCONV_SET_IN_HSIZE1 Register
struct VCONV_VCONV_SET_IN_HSIZE1 {
	unsigned int Reserved:21;		// [31:11]
	unsigned int IN_HSIZE1:11;		// [10:0]
};
 // VCONV_SET_IN_VSIZE1 Register
struct VCONV_VCONV_SET_IN_VSIZE1 {
	unsigned int Reserved:21;		// [31:11]
	unsigned int IN_VSIZE1:11;		// [10:0]
};
 // VCONV_SET_IN_BASEADDR_A1 Register
struct VCONV_VCONV_SET_IN_BASEADDR_A1 {
	unsigned int IN_BADDR_A1:32;		// [31:0]
};
 // VCONV_SET_IN_BASEADDR_B1 Register
struct VCONV_VCONV_SET_IN_BASEADDR_B1 {
	unsigned int IN_BADDR_B1:32;		// [31:0]
};
 // VCONV_SET_IN_BASEADDR_C1 Register
struct VCONV_VCONV_SET_IN_BASEADDR_C1 {
	unsigned int IN_BADDR_C1:32;		// [31:0]
};
 // VCONV_SET_IN_PITCH_A1 Register
struct VCONV_VCONV_SET_IN_PITCH_A1 {
	unsigned int Reserved:19;		// [31:13]
	unsigned int IN_PITCH_A1:13;		// [12:0]
};
 // VCONV_SET_IN_PITCH_B1 Register
struct VCONV_VCONV_SET_IN_PITCH_B1 {
	unsigned int Reserved:19;		// [31:13]
	unsigned int IN_PITCH_B1:13;		// [12:0]
};
 // VCONV_SET_IN_PITCH_C1 Register
struct VCONV_VCONV_SET_IN_PITCH_C1 {
	unsigned int Reserved:19;		// [31:13]
	unsigned int IN_PITCH_C1:13;		// [12:0]
};
 // VCONV_SET_OUT_FORMAT1 Register
struct VCONV_VCONV_SET_OUT_FORMAT1 {
	unsigned int Reserved4:8;		// [31:24]
	unsigned int OUT_FORMATID1:8;		// [23:16]
	unsigned int Reserved3:7;		// [15:9]
	unsigned int OUT_SCAN1:1;		// [8]
	unsigned int Reserved2:2;		// [7:6]
	unsigned int OUT_PLANE1:2;		// [5:4]
	unsigned int Reserved:2;		// [3:2]
	unsigned int OUT_COLORFORMAT1:2;		// [1:0]
};
 // VCONV_SET_OUT_HSIZE1 Register
struct VCONV_VCONV_SET_OUT_HSIZE1 {
	unsigned int Reserved:21;		// [31:11]
	unsigned int OUT_HSIZE1:11;		// [10:0]
};
 // VCONV_SET_OUT_VSIZE1 Register
struct VCONV_VCONV_SET_OUT_VSIZE1 {
	unsigned int Reserved:21;		// [31:11]
	unsigned int OUT_VSIZE1:11;		// [10:0]
};
 // VCONV_SET_OUT_BASEADDR_A1 Register
struct VCONV_VCONV_SET_OUT_BASEADDR_A1 {
	unsigned int OUT_BADDR_A1:32;		// [31:0]
};
 // VCONV_SET_OUT_BASEADDR_B1 Register
struct VCONV_VCONV_SET_OUT_BASEADDR_B1 {
	unsigned int OUT_BADDR_B1:32;		// [31:0]
};
 // VCONV_SET_OUT_BASEADDR_C1 Register
struct VCONV_VCONV_SET_OUT_BASEADDR_C1 {
	unsigned int OUT_BADDR_C1:32;		// [31:0]
};
 // VCONV_SET_OUT_PITCH_A1 Register
struct VCONV_VCONV_SET_OUT_PITCH_A1 {
	unsigned int Reserved:19;		// [31:13]
	unsigned int OUT_PITCH_A1:13;		// [12:0]
};
 // VCONV_SET_OUT_PITCH_B1 Register
struct VCONV_VCONV_SET_OUT_PITCH_B1 {
	unsigned int Reserved:19;		// [31:13]
	unsigned int OUT_PITCH_B1:13;		// [12:0]
};
 // VCONV_SET_OUT_PITCH_C1 Register
struct VCONV_VCONV_SET_OUT_PITCH_C1 {
	unsigned int Reserved:19;		// [31:13]
	unsigned int OUT_PITCH_C1:13;		// [12:0]
};
 // VCONV_SET_OUT_HOFFSET1 Register
struct VCONV_VCONV_SET_OUT_HOFFSET1 {
	unsigned int Reserved:21;		// [31:11]
	unsigned int OUT_HOFFSET1:11;		// [10:0]
};
 // VCONV_SET_OUT_VOFFSET1 Register
struct VCONV_VCONV_SET_OUT_VOFFSET1 {
	unsigned int Reserved:21;		// [31:11]
	unsigned int OUT_VOFFSET1:11;		// [10:0]
};
 // VCONV_SET_OUT_HSCALE1 Register
struct VCONV_VCONV_SET_OUT_HSCALE1 {
	unsigned int Reserved:13;		// [31:19]
	unsigned int HSCALE_INTEGER1:3;		// [18:16]
	unsigned int HSCALE_FRACTON1:16;		// [15:0]
};
 // VCONV_SET_OUT_VSCALE1 Register
struct VCONV_VCONV_SET_OUT_VSCALE1 {
	unsigned int Reserved:13;		// [31:19]
	unsigned int VSCALE_INTEGER1:3;		// [18:16]
	unsigned int VSCALE_FRACTON1:16;		// [15:0]
};
 // VCONV_SET_OUT_HDELTA1 Register
struct VCONV_VCONV_SET_OUT_HDELTA1 {
	unsigned int Reserved:21;		// [31:11]
	unsigned int reserved2:1;		// [10]
	unsigned int HDELTA1:10;		// [9:0]
};
 // VCONV_SET_OUT_VDELTA1 Register
struct VCONV_VCONV_SET_OUT_VDELTA1 {
	unsigned int Reserved:21;		// [31:11]
	unsigned int reserved2:1;		// [10]
	unsigned int VDELTA1:10;		// [9:0]
};
 // VCONV_SET_FORCE_MODE1 Register
struct VCONV_VCONV_SET_FORCE_MODE1 {
	unsigned int Reserved:31;		// [31:1]
	unsigned int FORCE_MODE1:1;		// [0]
};
 // VCONV_SET_FORCE_GY1 Register
struct VCONV_VCONV_SET_FORCE_GY1 {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_GY1:8;		// [7:0]
};
 // VCONV_SET_FORCE_BCB1 Register
struct VCONV_VCONV_SET_FORCE_BCB1 {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_BCB1:8;		// [7:0]
};
 // VCONV_SET_FORCE_RCR1 Register
struct VCONV_VCONV_SET_FORCE_RCR1 {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_RCR1:8;		// [7:0]
};
 // VCONV_SET_FORCE_A1 Register
struct VCONV_VCONV_SET_FORCE_A1 {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_ALPHA1:8;		// [7:0]
};
 // VCONV_SET_CROP1 Register
struct VCONV_VCONV_SET_CROP1 {
	unsigned int Reserved4:4;		// [31:28]
	unsigned int CROP_RIGHT1:4;		// [27:24]
	unsigned int Reserved3:4;		// [23:20]
	unsigned int CROP_LEFT1:4;		// [19:16]
	unsigned int Reserved2:4;		// [15:12]
	unsigned int CROP_LOWER1:4;		// [11:8]
	unsigned int Reserved:4;		// [7:4]
	unsigned int CROP_UPPER1:4;		// [3:0]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _VCONV_REG_STRUCT_B_H */
