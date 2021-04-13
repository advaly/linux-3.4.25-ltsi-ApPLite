/*
 * arch/arm/mach-tz2000/include/mach/regs/gdmac_reg_struct_l.h
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

#ifndef _GDMAC_REG_STRUCT_L_H
#define _GDMAC_REG_STRUCT_L_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // GDT0_DSR Register
struct GDMAC_GDT0_DSR {
	unsigned int DMA_status:4;		// [3:0]
	unsigned int Wakeup_event:5;		// [8:4]
	unsigned int DSN:1;		// [9]
	unsigned int reserved:22;		// [31:10]
};
 // GDT0_DPC Register
struct GDMAC_GDT0_DPC {
	unsigned int pc_mgr:32;		// [31:0]
};
 // GDT0_INTEN Register
struct GDMAC_GDT0_INTEN {
	unsigned int event_irq_select:16;		// [15:0]
	unsigned int reserved:16;		// [31:16]
};
 // GDT0_INT_EVENT_RIS Register
struct GDMAC_GDT0_INT_EVENT_RIS {
	unsigned int DMASEV:16;		// [15:0]
	unsigned int reserved:16;		// [31:16]
};
 // GDT0_INTMIS Register
struct GDMAC_GDT0_INTMIS {
	unsigned int irq_status:16;		// [15:0]
	unsigned int reserved:16;		// [31:16]
};
 // GDT0_INTCLR Register
struct GDMAC_GDT0_INTCLR {
	unsigned int irq_clr:16;		// [15:0]
	unsigned int reserved:16;		// [31:16]
};
 // GDT0_FSRD Register
struct GDMAC_GDT0_FSRD {
	unsigned int fs_mgr:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // GDT0_FSRC Register
struct GDMAC_GDT0_FSRC {
	unsigned int fault_status:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT0_FTRD Register
struct GDMAC_GDT0_FTRD {
	unsigned int undef_instr:1;		// [0]
	unsigned int operand_invalid:1;		// [1]
	unsigned int reserved4:2;		// [3:2]
	unsigned int dmago_err:1;		// [4]
	unsigned int mgr_evnt_err:1;		// [5]
	unsigned int reserved3:10;		// [15:6]
	unsigned int instr_fetch_err:1;		// [16]
	unsigned int reserved2:13;		// [29:17]
	unsigned int dbg_instr:1;		// [30]
	unsigned int reserved:1;		// [31]
};
 // GDT0_FTR0 Register
struct GDMAC_GDT0_FTR0 {
	unsigned int undef_instr:1;		// [0]
	unsigned int operand_invalid:1;		// [1]
	unsigned int reserved4:3;		// [4:2]
	unsigned int ch_evnt_err:1;		// [5]
	unsigned int ch_periph_err:1;		// [6]
	unsigned int ch_rdwr_err:1;		// [7]
	unsigned int reserved3:4;		// [11:8]
	unsigned int mfifo_err:1;		// [12]
	unsigned int st_data_unavailable:1;		// [13]
	unsigned int reserved2:2;		// [15:14]
	unsigned int instr_fetch_err:1;		// [16]
	unsigned int data_write_err:1;		// [17]
	unsigned int data_read_err:1;		// [18]
	unsigned int reserved:11;		// [29:19]
	unsigned int dbg_instr:1;		// [30]
	unsigned int lockup_err:1;		// [31]
};
 // GDT0_FTR1 Register
struct GDMAC_GDT0_FTR1 {
	unsigned int undef_instr:1;		// [0]
	unsigned int operand_invalid:1;		// [1]
	unsigned int reserved4:3;		// [4:2]
	unsigned int ch_evnt_err:1;		// [5]
	unsigned int ch_periph_err:1;		// [6]
	unsigned int ch_rdwr_err:1;		// [7]
	unsigned int reserved3:4;		// [11:8]
	unsigned int mfifo_err:1;		// [12]
	unsigned int st_data_unavailable:1;		// [13]
	unsigned int reserved2:2;		// [15:14]
	unsigned int instr_fetch_err:1;		// [16]
	unsigned int data_write_err:1;		// [17]
	unsigned int data_read_err:1;		// [18]
	unsigned int reserved:11;		// [29:19]
	unsigned int dbg_instr:1;		// [30]
	unsigned int lockup_err:1;		// [31]
};
 // GDT0_FTR2 Register
struct GDMAC_GDT0_FTR2 {
	unsigned int undef_instr:1;		// [0]
	unsigned int operand_invalid:1;		// [1]
	unsigned int reserved4:3;		// [4:2]
	unsigned int ch_evnt_err:1;		// [5]
	unsigned int ch_periph_err:1;		// [6]
	unsigned int ch_rdwr_err:1;		// [7]
	unsigned int reserved3:4;		// [11:8]
	unsigned int mfifo_err:1;		// [12]
	unsigned int st_data_unavailable:1;		// [13]
	unsigned int reserved2:2;		// [15:14]
	unsigned int instr_fetch_err:1;		// [16]
	unsigned int data_write_err:1;		// [17]
	unsigned int data_read_err:1;		// [18]
	unsigned int reserved:11;		// [29:19]
	unsigned int dbg_instr:1;		// [30]
	unsigned int lockup_err:1;		// [31]
};
 // GDT0_FTR3 Register
struct GDMAC_GDT0_FTR3 {
	unsigned int undef_instr:1;		// [0]
	unsigned int operand_invalid:1;		// [1]
	unsigned int reserved4:3;		// [4:2]
	unsigned int ch_evnt_err:1;		// [5]
	unsigned int ch_periph_err:1;		// [6]
	unsigned int ch_rdwr_err:1;		// [7]
	unsigned int reserved3:4;		// [11:8]
	unsigned int mfifo_err:1;		// [12]
	unsigned int st_data_unavailable:1;		// [13]
	unsigned int reserved2:2;		// [15:14]
	unsigned int instr_fetch_err:1;		// [16]
	unsigned int data_write_err:1;		// [17]
	unsigned int data_read_err:1;		// [18]
	unsigned int reserved:11;		// [29:19]
	unsigned int dbg_instr:1;		// [30]
	unsigned int lockup_err:1;		// [31]
};
 // GDT0_FTR4 Register
struct GDMAC_GDT0_FTR4 {
	unsigned int undef_instr:1;		// [0]
	unsigned int operand_invalid:1;		// [1]
	unsigned int reserved4:3;		// [4:2]
	unsigned int ch_evnt_err:1;		// [5]
	unsigned int ch_periph_err:1;		// [6]
	unsigned int ch_rdwr_err:1;		// [7]
	unsigned int reserved3:4;		// [11:8]
	unsigned int mfifo_err:1;		// [12]
	unsigned int st_data_unavailable:1;		// [13]
	unsigned int reserved2:2;		// [15:14]
	unsigned int instr_fetch_err:1;		// [16]
	unsigned int data_write_err:1;		// [17]
	unsigned int data_read_err:1;		// [18]
	unsigned int reserved:11;		// [29:19]
	unsigned int dbg_instr:1;		// [30]
	unsigned int lockup_err:1;		// [31]
};
 // GDT0_FTR5 Register
struct GDMAC_GDT0_FTR5 {
	unsigned int undef_instr:1;		// [0]
	unsigned int operand_invalid:1;		// [1]
	unsigned int reserved4:3;		// [4:2]
	unsigned int ch_evnt_err:1;		// [5]
	unsigned int ch_periph_err:1;		// [6]
	unsigned int ch_rdwr_err:1;		// [7]
	unsigned int reserved3:4;		// [11:8]
	unsigned int mfifo_err:1;		// [12]
	unsigned int st_data_unavailable:1;		// [13]
	unsigned int reserved2:2;		// [15:14]
	unsigned int instr_fetch_err:1;		// [16]
	unsigned int data_write_err:1;		// [17]
	unsigned int data_read_err:1;		// [18]
	unsigned int reserved:11;		// [29:19]
	unsigned int dbg_instr:1;		// [30]
	unsigned int lockup_err:1;		// [31]
};
 // GDT0_FTR6 Register
struct GDMAC_GDT0_FTR6 {
	unsigned int undef_instr:1;		// [0]
	unsigned int operand_invalid:1;		// [1]
	unsigned int reserved4:3;		// [4:2]
	unsigned int ch_evnt_err:1;		// [5]
	unsigned int ch_periph_err:1;		// [6]
	unsigned int ch_rdwr_err:1;		// [7]
	unsigned int reserved3:4;		// [11:8]
	unsigned int mfifo_err:1;		// [12]
	unsigned int st_data_unavailable:1;		// [13]
	unsigned int reserved2:2;		// [15:14]
	unsigned int instr_fetch_err:1;		// [16]
	unsigned int data_write_err:1;		// [17]
	unsigned int data_read_err:1;		// [18]
	unsigned int reserved:11;		// [29:19]
	unsigned int dbg_instr:1;		// [30]
	unsigned int lockup_err:1;		// [31]
};
 // GDT0_FTR7 Register
struct GDMAC_GDT0_FTR7 {
	unsigned int undef_instr:1;		// [0]
	unsigned int operand_invalid:1;		// [1]
	unsigned int reserved4:3;		// [4:2]
	unsigned int ch_evnt_err:1;		// [5]
	unsigned int ch_periph_err:1;		// [6]
	unsigned int ch_rdwr_err:1;		// [7]
	unsigned int reserved3:4;		// [11:8]
	unsigned int mfifo_err:1;		// [12]
	unsigned int st_data_unavailable:1;		// [13]
	unsigned int reserved2:2;		// [15:14]
	unsigned int instr_fetch_err:1;		// [16]
	unsigned int data_write_err:1;		// [17]
	unsigned int data_read_err:1;		// [18]
	unsigned int reserved:11;		// [29:19]
	unsigned int dbg_instr:1;		// [30]
	unsigned int lockup_err:1;		// [31]
};
 // GDT0_CSR0 Register
struct GDMAC_GDT0_CSR0 {
	unsigned int Channel_status:4;		// [3:0]
	unsigned int Wakeup_number:5;		// [8:4]
	unsigned int reserved3:5;		// [13:9]
	unsigned int dmawfp_b_ns:1;		// [14]
	unsigned int dmawfp_periph:1;		// [15]
	unsigned int reserved2:5;		// [20:16]
	unsigned int CSN:1;		// [21]
	unsigned int reserved:10;		// [31:22]
};
 // GDT0_CPC0 Register
struct GDMAC_GDT0_CPC0 {
	unsigned int pc_chnl:32;		// [31:0]
};
 // GDT0_CSR1 Register
struct GDMAC_GDT0_CSR1 {
	unsigned int Channel_status:4;		// [3:0]
	unsigned int Wakeup_number:5;		// [8:4]
	unsigned int reserved3:5;		// [13:9]
	unsigned int dmawfp_b_ns:1;		// [14]
	unsigned int dmawfp_periph:1;		// [15]
	unsigned int reserved2:5;		// [20:16]
	unsigned int CSN:1;		// [21]
	unsigned int reserved:10;		// [31:22]
};
 // GDT0_CPC1 Register
struct GDMAC_GDT0_CPC1 {
	unsigned int pc_chnl:32;		// [31:0]
};
 // GDT0_CSR2 Register
struct GDMAC_GDT0_CSR2 {
	unsigned int Channel_status:4;		// [3:0]
	unsigned int Wakeup_number:5;		// [8:4]
	unsigned int reserved3:5;		// [13:9]
	unsigned int dmawfp_b_ns:1;		// [14]
	unsigned int dmawfp_periph:1;		// [15]
	unsigned int reserved2:5;		// [20:16]
	unsigned int CSN:1;		// [21]
	unsigned int reserved:10;		// [31:22]
};
 // GDT0_CPC2 Register
struct GDMAC_GDT0_CPC2 {
	unsigned int pc_chnl:32;		// [31:0]
};
 // GDT0_CSR3 Register
struct GDMAC_GDT0_CSR3 {
	unsigned int Channel_status:4;		// [3:0]
	unsigned int Wakeup_number:5;		// [8:4]
	unsigned int reserved3:5;		// [13:9]
	unsigned int dmawfp_b_ns:1;		// [14]
	unsigned int dmawfp_periph:1;		// [15]
	unsigned int reserved2:5;		// [20:16]
	unsigned int CSN:1;		// [21]
	unsigned int reserved:10;		// [31:22]
};
 // GDT0_CPC3 Register
struct GDMAC_GDT0_CPC3 {
	unsigned int pc_chnl:32;		// [31:0]
};
 // GDT0_CSR4 Register
struct GDMAC_GDT0_CSR4 {
	unsigned int Channel_status:4;		// [3:0]
	unsigned int Wakeup_number:5;		// [8:4]
	unsigned int reserved3:5;		// [13:9]
	unsigned int dmawfp_b_ns:1;		// [14]
	unsigned int dmawfp_periph:1;		// [15]
	unsigned int reserved2:5;		// [20:16]
	unsigned int CSN:1;		// [21]
	unsigned int reserved:10;		// [31:22]
};
 // GDT0_CPC4 Register
struct GDMAC_GDT0_CPC4 {
	unsigned int pc_chnl:32;		// [31:0]
};
 // GDT0_CSR5 Register
struct GDMAC_GDT0_CSR5 {
	unsigned int Channel_status:4;		// [3:0]
	unsigned int Wakeup_number:5;		// [8:4]
	unsigned int reserved3:5;		// [13:9]
	unsigned int dmawfp_b_ns:1;		// [14]
	unsigned int dmawfp_periph:1;		// [15]
	unsigned int reserved2:5;		// [20:16]
	unsigned int CSN:1;		// [21]
	unsigned int reserved:10;		// [31:22]
};
 // GDT0_CPC5 Register
struct GDMAC_GDT0_CPC5 {
	unsigned int pc_chnl:32;		// [31:0]
};
 // GDT0_CSR6 Register
struct GDMAC_GDT0_CSR6 {
	unsigned int Channel_status:4;		// [3:0]
	unsigned int Wakeup_number:5;		// [8:4]
	unsigned int reserved3:5;		// [13:9]
	unsigned int dmawfp_b_ns:1;		// [14]
	unsigned int dmawfp_periph:1;		// [15]
	unsigned int reserved2:5;		// [20:16]
	unsigned int CSN:1;		// [21]
	unsigned int reserved:10;		// [31:22]
};
 // GDT0_CPC6 Register
struct GDMAC_GDT0_CPC6 {
	unsigned int pc_chnl:32;		// [31:0]
};
 // GDT0_CSR7 Register
struct GDMAC_GDT0_CSR7 {
	unsigned int Channel_status:4;		// [3:0]
	unsigned int Wakeup_number:5;		// [8:4]
	unsigned int reserved3:5;		// [13:9]
	unsigned int dmawfp_b_ns:1;		// [14]
	unsigned int dmawfp_periph:1;		// [15]
	unsigned int reserved2:5;		// [20:16]
	unsigned int CSN:1;		// [21]
	unsigned int reserved:10;		// [31:22]
};
 // GDT0_CPC7 Register
struct GDMAC_GDT0_CPC7 {
	unsigned int pc_chnl:32;		// [31:0]
};
 // GDT0_SAR0 Register
struct GDMAC_GDT0_SAR0 {
	unsigned int src_addr:32;		// [31:0]
};
 // GDT0_DAR0 Register
struct GDMAC_GDT0_DAR0 {
	unsigned int dst_addr:32;		// [31:0]
};
 // GDT0_CCR0 Register
struct GDMAC_GDT0_CCR0 {
	unsigned int src_inc:1;		// [0]
	unsigned int src_burst_size:3;		// [3:1]
	unsigned int src_burst_len:4;		// [7:4]
	unsigned int src_prot_ctrl:3;		// [10:8]
	unsigned int src_cache_ctrl:3;		// [13:11]
	unsigned int dst_inc:1;		// [14]
	unsigned int dst_burst_size:3;		// [17:15]
	unsigned int dst_burst_len:4;		// [21:18]
	unsigned int dst_prot_ctrl:3;		// [24:22]
	unsigned int dst_cache_ctrl:3;		// [27:25]
	unsigned int endian_swap_size:3;		// [30:28]
	unsigned int reserved:1;		// [31]
};
 // GDT0_LC0_0 Register
struct GDMAC_GDT0_LC0_0 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT0_LC1_0 Register
struct GDMAC_GDT0_LC1_0 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT0_SAR1 Register
struct GDMAC_GDT0_SAR1 {
	unsigned int src_addr:32;		// [31:0]
};
 // GDT0_DAR1 Register
struct GDMAC_GDT0_DAR1 {
	unsigned int dst_addr:32;		// [31:0]
};
 // GDT0_CCR1 Register
struct GDMAC_GDT0_CCR1 {
	unsigned int src_inc:1;		// [0]
	unsigned int src_burst_size:3;		// [3:1]
	unsigned int src_burst_len:4;		// [7:4]
	unsigned int src_prot_ctrl:3;		// [10:8]
	unsigned int src_cache_ctrl:3;		// [13:11]
	unsigned int dst_inc:1;		// [14]
	unsigned int dst_burst_size:3;		// [17:15]
	unsigned int dst_burst_len:4;		// [21:18]
	unsigned int dst_prot_ctrl:3;		// [24:22]
	unsigned int dst_cache_ctrl:3;		// [27:25]
	unsigned int endian_swap_size:3;		// [30:28]
	unsigned int reserved:1;		// [31]
};
 // GDT0_LC0_1 Register
struct GDMAC_GDT0_LC0_1 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT0_LC1_1 Register
struct GDMAC_GDT0_LC1_1 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT0_SAR2 Register
struct GDMAC_GDT0_SAR2 {
	unsigned int src_addr:32;		// [31:0]
};
 // GDT0_DAR2 Register
struct GDMAC_GDT0_DAR2 {
	unsigned int dst_addr:32;		// [31:0]
};
 // GDT0_CCR2 Register
struct GDMAC_GDT0_CCR2 {
	unsigned int src_inc:1;		// [0]
	unsigned int src_burst_size:3;		// [3:1]
	unsigned int src_burst_len:4;		// [7:4]
	unsigned int src_prot_ctrl:3;		// [10:8]
	unsigned int src_cache_ctrl:3;		// [13:11]
	unsigned int dst_inc:1;		// [14]
	unsigned int dst_burst_size:3;		// [17:15]
	unsigned int dst_burst_len:4;		// [21:18]
	unsigned int dst_prot_ctrl:3;		// [24:22]
	unsigned int dst_cache_ctrl:3;		// [27:25]
	unsigned int endian_swap_size:3;		// [30:28]
	unsigned int reserved:1;		// [31]
};
 // GDT0_LC0_2 Register
struct GDMAC_GDT0_LC0_2 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT0_LC1_2 Register
struct GDMAC_GDT0_LC1_2 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT0_SAR3 Register
struct GDMAC_GDT0_SAR3 {
	unsigned int src_addr:32;		// [31:0]
};
 // GDT0_DAR3 Register
struct GDMAC_GDT0_DAR3 {
	unsigned int dst_addr:32;		// [31:0]
};
 // GDT0_CCR3 Register
struct GDMAC_GDT0_CCR3 {
	unsigned int src_inc:1;		// [0]
	unsigned int src_burst_size:3;		// [3:1]
	unsigned int src_burst_len:4;		// [7:4]
	unsigned int src_prot_ctrl:3;		// [10:8]
	unsigned int src_cache_ctrl:3;		// [13:11]
	unsigned int dst_inc:1;		// [14]
	unsigned int dst_burst_size:3;		// [17:15]
	unsigned int dst_burst_len:4;		// [21:18]
	unsigned int dst_prot_ctrl:3;		// [24:22]
	unsigned int dst_cache_ctrl:3;		// [27:25]
	unsigned int endian_swap_size:3;		// [30:28]
	unsigned int reserved:1;		// [31]
};
 // GDT0_LC0_3 Register
struct GDMAC_GDT0_LC0_3 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT0_LC1_3 Register
struct GDMAC_GDT0_LC1_3 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT0_SAR4 Register
struct GDMAC_GDT0_SAR4 {
	unsigned int src_addr:32;		// [31:0]
};
 // GDT0_DAR4 Register
struct GDMAC_GDT0_DAR4 {
	unsigned int dst_addr:32;		// [31:0]
};
 // GDT0_CCR4 Register
struct GDMAC_GDT0_CCR4 {
	unsigned int src_inc:1;		// [0]
	unsigned int src_burst_size:3;		// [3:1]
	unsigned int src_burst_len:4;		// [7:4]
	unsigned int src_prot_ctrl:3;		// [10:8]
	unsigned int src_cache_ctrl:3;		// [13:11]
	unsigned int dst_inc:1;		// [14]
	unsigned int dst_burst_size:3;		// [17:15]
	unsigned int dst_burst_len:4;		// [21:18]
	unsigned int dst_prot_ctrl:3;		// [24:22]
	unsigned int dst_cache_ctrl:3;		// [27:25]
	unsigned int endian_swap_size:3;		// [30:28]
	unsigned int reserved:1;		// [31]
};
 // GDT0_LC0_4 Register
struct GDMAC_GDT0_LC0_4 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT0_LC1_4 Register
struct GDMAC_GDT0_LC1_4 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT0_SAR5 Register
struct GDMAC_GDT0_SAR5 {
	unsigned int src_addr:32;		// [31:0]
};
 // GDT0_DAR5 Register
struct GDMAC_GDT0_DAR5 {
	unsigned int dst_addr:32;		// [31:0]
};
 // GDT0_CCR5 Register
struct GDMAC_GDT0_CCR5 {
	unsigned int src_inc:1;		// [0]
	unsigned int src_burst_size:3;		// [3:1]
	unsigned int src_burst_len:4;		// [7:4]
	unsigned int src_prot_ctrl:3;		// [10:8]
	unsigned int src_cache_ctrl:3;		// [13:11]
	unsigned int dst_inc:1;		// [14]
	unsigned int dst_burst_size:3;		// [17:15]
	unsigned int dst_burst_len:4;		// [21:18]
	unsigned int dst_prot_ctrl:3;		// [24:22]
	unsigned int dst_cache_ctrl:3;		// [27:25]
	unsigned int endian_swap_size:3;		// [30:28]
	unsigned int reserved:1;		// [31]
};
 // GDT0_LC0_5 Register
struct GDMAC_GDT0_LC0_5 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT0_LC1_5 Register
struct GDMAC_GDT0_LC1_5 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT0_SAR6 Register
struct GDMAC_GDT0_SAR6 {
	unsigned int src_addr:32;		// [31:0]
};
 // GDT0_DAR6 Register
struct GDMAC_GDT0_DAR6 {
	unsigned int dst_addr:32;		// [31:0]
};
 // GDT0_CCR6 Register
struct GDMAC_GDT0_CCR6 {
	unsigned int src_inc:1;		// [0]
	unsigned int src_burst_size:3;		// [3:1]
	unsigned int src_burst_len:4;		// [7:4]
	unsigned int src_prot_ctrl:3;		// [10:8]
	unsigned int src_cache_ctrl:3;		// [13:11]
	unsigned int dst_inc:1;		// [14]
	unsigned int dst_burst_size:3;		// [17:15]
	unsigned int dst_burst_len:4;		// [21:18]
	unsigned int dst_prot_ctrl:3;		// [24:22]
	unsigned int dst_cache_ctrl:3;		// [27:25]
	unsigned int endian_swap_size:3;		// [30:28]
	unsigned int reserved:1;		// [31]
};
 // GDT0_LC0_6 Register
struct GDMAC_GDT0_LC0_6 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT0_LC1_6 Register
struct GDMAC_GDT0_LC1_6 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT0_SAR7 Register
struct GDMAC_GDT0_SAR7 {
	unsigned int src_addr:32;		// [31:0]
};
 // GDT0_DAR7 Register
struct GDMAC_GDT0_DAR7 {
	unsigned int dst_addr:32;		// [31:0]
};
 // GDT0_CCR7 Register
struct GDMAC_GDT0_CCR7 {
	unsigned int src_inc:1;		// [0]
	unsigned int src_burst_size:3;		// [3:1]
	unsigned int src_burst_len:4;		// [7:4]
	unsigned int src_prot_ctrl:3;		// [10:8]
	unsigned int src_cache_ctrl:3;		// [13:11]
	unsigned int dst_inc:1;		// [14]
	unsigned int dst_burst_size:3;		// [17:15]
	unsigned int dst_burst_len:4;		// [21:18]
	unsigned int dst_prot_ctrl:3;		// [24:22]
	unsigned int dst_cache_ctrl:3;		// [27:25]
	unsigned int endian_swap_size:3;		// [30:28]
	unsigned int reserved:1;		// [31]
};
 // GDT0_LC0_7 Register
struct GDMAC_GDT0_LC0_7 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT0_LC1_7 Register
struct GDMAC_GDT0_LC1_7 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT0_DBGSTATUS Register
struct GDMAC_GDT0_DBGSTATUS {
	unsigned int dbg_status:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // GDT0_DBGCMD Register
struct GDMAC_GDT0_DBGCMD {
	unsigned int dbgcmd:2;		// [1:0]
	unsigned int reserved:30;		// [31:2]
};
 // GDT0_DBGINST0 Register
struct GDMAC_GDT0_DBGINST0 {
	unsigned int Debug_thread:1;		// [0]
	unsigned int reserved2:7;		// [7:1]
	unsigned int Channel_number:3;		// [10:8]
	unsigned int reserved:5;		// [15:11]
	unsigned int Instruction_byte_0:8;		// [23:16]
	unsigned int Instruction_byte_1:8;		// [31:24]
};
 // GDT0_DBGINST1 Register
struct GDMAC_GDT0_DBGINST1 {
	unsigned int Instruction_byte_2:8;		// [7:0]
	unsigned int Instruction_byte_3:8;		// [15:8]
	unsigned int Instruction_byte_4:8;		// [23:16]
	unsigned int Instruction_byte_5:8;		// [31:24]
};
 // GDT0_CR0 Register
struct GDMAC_GDT0_CR0 {
	unsigned int periph_req:1;		// [0]
	unsigned int boot_en:1;		// [1]
	unsigned int mgr_ns_at_rst:1;		// [2]
	unsigned int reserved3:1;		// [3]
	unsigned int num_chnls:3;		// [6:4]
	unsigned int reserved2:5;		// [11:7]
	unsigned int num_periph_req:5;		// [16:12]
	unsigned int num_events:5;		// [21:17]
	unsigned int reserved:10;		// [31:22]
};
 // GDT0_CR1 Register
struct GDMAC_GDT0_CR1 {
	unsigned int i_cache_len:3;		// [2:0]
	unsigned int reserved2:1;		// [3]
	unsigned int num_i_cache_lines:4;		// [7:4]
	unsigned int reserved:24;		// [31:8]
};
 // GDT0_CR2 Register
struct GDMAC_GDT0_CR2 {
	unsigned int boot_addr:32;		// [31:0]
};
 // GDT0_CR3 Register
struct GDMAC_GDT0_CR3 {
	unsigned int INS:16;		// [15:0]
	unsigned int reserved:16;		// [31:16]
};
 // GDT0_CR4 Register
struct GDMAC_GDT0_CR4 {
	unsigned int PNS:24;		// [23:0]
	unsigned int reserved:8;		// [31:24]
};
 // GDT0_CRD Register
struct GDMAC_GDT0_CRD {
	unsigned int data_width:3;		// [2:0]
	unsigned int reserved4:1;		// [3]
	unsigned int wr_cap:3;		// [6:4]
	unsigned int reserved3:1;		// [7]
	unsigned int wr_q_dep:4;		// [11:8]
	unsigned int rd_cap:3;		// [14:12]
	unsigned int reserved2:1;		// [15]
	unsigned int rd_q_dep:4;		// [19:16]
	unsigned int data_buffer_dep:10;		// [29:20]
	unsigned int reserved:2;		// [31:30]
};
 // GDT0_WD Register
struct GDMAC_GDT0_WD {
	unsigned int wd_irq_only:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // GDT0_periph_id_0 Register
struct GDMAC_GDT0_PERIPH_ID_0 {
	unsigned int part_number_0:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT0_periph_id_1 Register
struct GDMAC_GDT0_PERIPH_ID_1 {
	unsigned int part_number_1:4;		// [3:0]
	unsigned int designer_0:4;		// [7:4]
	unsigned int reserved:24;		// [31:8]
};
 // GDT0_periph_id_2 Register
struct GDMAC_GDT0_PERIPH_ID_2 {
	unsigned int designer_1:4;		// [3:0]
	unsigned int revision:4;		// [7:4]
	unsigned int reserved:24;		// [31:8]
};
 // GDT0_periph_id_3 Register
struct GDMAC_GDT0_PERIPH_ID_3 {
	unsigned int revision:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // GDT0_pcell_id_0 Register
struct GDMAC_GDT0_PCELL_ID_0 {
	unsigned int pcell_id_0:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT0_pcell_id_1 Register
struct GDMAC_GDT0_PCELL_ID_1 {
	unsigned int pcell_id_1:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT0_pcell_id_2 Register
struct GDMAC_GDT0_PCELL_ID_2 {
	unsigned int pcell_id_2:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT0_pcell_id_3 Register
struct GDMAC_GDT0_PCELL_ID_3 {
	unsigned int pcell_id_3:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT1_DSR Register
struct GDMAC_GDT1_DSR {
	unsigned int DMA_status:4;		// [3:0]
	unsigned int Wakeup_event:5;		// [8:4]
	unsigned int DSN:1;		// [9]
	unsigned int reserved:22;		// [31:10]
};
 // GDT1_DPC Register
struct GDMAC_GDT1_DPC {
	unsigned int pc_mgr:32;		// [31:0]
};
 // GDT1_INTEN Register
struct GDMAC_GDT1_INTEN {
	unsigned int event_irq_select:16;		// [15:0]
	unsigned int reserved:16;		// [31:16]
};
 // GDT1_INT_EVENT_RIS Register
struct GDMAC_GDT1_INT_EVENT_RIS {
	unsigned int DMASEV:16;		// [15:0]
	unsigned int reserved:16;		// [31:16]
};
 // GDT1_INTMIS Register
struct GDMAC_GDT1_INTMIS {
	unsigned int irq_status:16;		// [15:0]
	unsigned int reserved:16;		// [31:16]
};
 // GDT1_INTCLR Register
struct GDMAC_GDT1_INTCLR {
	unsigned int irq_clr:16;		// [15:0]
	unsigned int reserved:16;		// [31:16]
};
 // GDT1_FSRD Register
struct GDMAC_GDT1_FSRD {
	unsigned int fs_mgr:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // GDT1_FSRC Register
struct GDMAC_GDT1_FSRC {
	unsigned int fault_status:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT1_FTRD Register
struct GDMAC_GDT1_FTRD {
	unsigned int undef_instr:1;		// [0]
	unsigned int operand_invalid:1;		// [1]
	unsigned int reserved4:2;		// [3:2]
	unsigned int dmago_err:1;		// [4]
	unsigned int mgr_evnt_err:1;		// [5]
	unsigned int reserved3:10;		// [15:6]
	unsigned int instr_fetch_err:1;		// [16]
	unsigned int reserved2:13;		// [29:17]
	unsigned int dbg_instr:1;		// [30]
	unsigned int reserved:1;		// [31]
};
 // GDT1_FTR0 Register
struct GDMAC_GDT1_FTR0 {
	unsigned int undef_instr:1;		// [0]
	unsigned int operand_invalid:1;		// [1]
	unsigned int reserved4:3;		// [4:2]
	unsigned int ch_evnt_err:1;		// [5]
	unsigned int ch_periph_err:1;		// [6]
	unsigned int ch_rdwr_err:1;		// [7]
	unsigned int reserved3:4;		// [11:8]
	unsigned int mfifo_err:1;		// [12]
	unsigned int st_data_unavailable:1;		// [13]
	unsigned int reserved2:2;		// [15:14]
	unsigned int instr_fetch_err:1;		// [16]
	unsigned int data_write_err:1;		// [17]
	unsigned int data_read_err:1;		// [18]
	unsigned int reserved:11;		// [29:19]
	unsigned int dbg_instr:1;		// [30]
	unsigned int lockup_err:1;		// [31]
};
 // GDT1_FTR1 Register
struct GDMAC_GDT1_FTR1 {
	unsigned int undef_instr:1;		// [0]
	unsigned int operand_invalid:1;		// [1]
	unsigned int reserved4:3;		// [4:2]
	unsigned int ch_evnt_err:1;		// [5]
	unsigned int ch_periph_err:1;		// [6]
	unsigned int ch_rdwr_err:1;		// [7]
	unsigned int reserved3:4;		// [11:8]
	unsigned int mfifo_err:1;		// [12]
	unsigned int st_data_unavailable:1;		// [13]
	unsigned int reserved2:2;		// [15:14]
	unsigned int instr_fetch_err:1;		// [16]
	unsigned int data_write_err:1;		// [17]
	unsigned int data_read_err:1;		// [18]
	unsigned int reserved:11;		// [29:19]
	unsigned int dbg_instr:1;		// [30]
	unsigned int lockup_err:1;		// [31]
};
 // GDT1_FTR2 Register
struct GDMAC_GDT1_FTR2 {
	unsigned int undef_instr:1;		// [0]
	unsigned int operand_invalid:1;		// [1]
	unsigned int reserved4:3;		// [4:2]
	unsigned int ch_evnt_err:1;		// [5]
	unsigned int ch_periph_err:1;		// [6]
	unsigned int ch_rdwr_err:1;		// [7]
	unsigned int reserved3:4;		// [11:8]
	unsigned int mfifo_err:1;		// [12]
	unsigned int st_data_unavailable:1;		// [13]
	unsigned int reserved2:2;		// [15:14]
	unsigned int instr_fetch_err:1;		// [16]
	unsigned int data_write_err:1;		// [17]
	unsigned int data_read_err:1;		// [18]
	unsigned int reserved:11;		// [29:19]
	unsigned int dbg_instr:1;		// [30]
	unsigned int lockup_err:1;		// [31]
};
 // GDT1_FTR3 Register
struct GDMAC_GDT1_FTR3 {
	unsigned int undef_instr:1;		// [0]
	unsigned int operand_invalid:1;		// [1]
	unsigned int reserved4:3;		// [4:2]
	unsigned int ch_evnt_err:1;		// [5]
	unsigned int ch_periph_err:1;		// [6]
	unsigned int ch_rdwr_err:1;		// [7]
	unsigned int reserved3:4;		// [11:8]
	unsigned int mfifo_err:1;		// [12]
	unsigned int st_data_unavailable:1;		// [13]
	unsigned int reserved2:2;		// [15:14]
	unsigned int instr_fetch_err:1;		// [16]
	unsigned int data_write_err:1;		// [17]
	unsigned int data_read_err:1;		// [18]
	unsigned int reserved:11;		// [29:19]
	unsigned int dbg_instr:1;		// [30]
	unsigned int lockup_err:1;		// [31]
};
 // GDT1_FTR4 Register
struct GDMAC_GDT1_FTR4 {
	unsigned int undef_instr:1;		// [0]
	unsigned int operand_invalid:1;		// [1]
	unsigned int reserved4:3;		// [4:2]
	unsigned int ch_evnt_err:1;		// [5]
	unsigned int ch_periph_err:1;		// [6]
	unsigned int ch_rdwr_err:1;		// [7]
	unsigned int reserved3:4;		// [11:8]
	unsigned int mfifo_err:1;		// [12]
	unsigned int st_data_unavailable:1;		// [13]
	unsigned int reserved2:2;		// [15:14]
	unsigned int instr_fetch_err:1;		// [16]
	unsigned int data_write_err:1;		// [17]
	unsigned int data_read_err:1;		// [18]
	unsigned int reserved:11;		// [29:19]
	unsigned int dbg_instr:1;		// [30]
	unsigned int lockup_err:1;		// [31]
};
 // GDT1_FTR5 Register
struct GDMAC_GDT1_FTR5 {
	unsigned int undef_instr:1;		// [0]
	unsigned int operand_invalid:1;		// [1]
	unsigned int reserved4:3;		// [4:2]
	unsigned int ch_evnt_err:1;		// [5]
	unsigned int ch_periph_err:1;		// [6]
	unsigned int ch_rdwr_err:1;		// [7]
	unsigned int reserved3:4;		// [11:8]
	unsigned int mfifo_err:1;		// [12]
	unsigned int st_data_unavailable:1;		// [13]
	unsigned int reserved2:2;		// [15:14]
	unsigned int instr_fetch_err:1;		// [16]
	unsigned int data_write_err:1;		// [17]
	unsigned int data_read_err:1;		// [18]
	unsigned int reserved:11;		// [29:19]
	unsigned int dbg_instr:1;		// [30]
	unsigned int lockup_err:1;		// [31]
};
 // GDT1_FTR6 Register
struct GDMAC_GDT1_FTR6 {
	unsigned int undef_instr:1;		// [0]
	unsigned int operand_invalid:1;		// [1]
	unsigned int reserved4:3;		// [4:2]
	unsigned int ch_evnt_err:1;		// [5]
	unsigned int ch_periph_err:1;		// [6]
	unsigned int ch_rdwr_err:1;		// [7]
	unsigned int reserved3:4;		// [11:8]
	unsigned int mfifo_err:1;		// [12]
	unsigned int st_data_unavailable:1;		// [13]
	unsigned int reserved2:2;		// [15:14]
	unsigned int instr_fetch_err:1;		// [16]
	unsigned int data_write_err:1;		// [17]
	unsigned int data_read_err:1;		// [18]
	unsigned int reserved:11;		// [29:19]
	unsigned int dbg_instr:1;		// [30]
	unsigned int lockup_err:1;		// [31]
};
 // GDT1_FTR7 Register
struct GDMAC_GDT1_FTR7 {
	unsigned int undef_instr:1;		// [0]
	unsigned int operand_invalid:1;		// [1]
	unsigned int reserved4:3;		// [4:2]
	unsigned int ch_evnt_err:1;		// [5]
	unsigned int ch_periph_err:1;		// [6]
	unsigned int ch_rdwr_err:1;		// [7]
	unsigned int reserved3:4;		// [11:8]
	unsigned int mfifo_err:1;		// [12]
	unsigned int st_data_unavailable:1;		// [13]
	unsigned int reserved2:2;		// [15:14]
	unsigned int instr_fetch_err:1;		// [16]
	unsigned int data_write_err:1;		// [17]
	unsigned int data_read_err:1;		// [18]
	unsigned int reserved:11;		// [29:19]
	unsigned int dbg_instr:1;		// [30]
	unsigned int lockup_err:1;		// [31]
};
 // GDT1_CSR0 Register
struct GDMAC_GDT1_CSR0 {
	unsigned int Channel_status:4;		// [3:0]
	unsigned int Wakeup_number:5;		// [8:4]
	unsigned int reserved3:5;		// [13:9]
	unsigned int dmawfp_b_ns:1;		// [14]
	unsigned int dmawfp_periph:1;		// [15]
	unsigned int reserved2:5;		// [20:16]
	unsigned int CSN:1;		// [21]
	unsigned int reserved:10;		// [31:22]
};
 // GDT1_CPC0 Register
struct GDMAC_GDT1_CPC0 {
	unsigned int pc_chnl:32;		// [31:0]
};
 // GDT1_CSR1 Register
struct GDMAC_GDT1_CSR1 {
	unsigned int Channel_status:4;		// [3:0]
	unsigned int Wakeup_number:5;		// [8:4]
	unsigned int reserved3:5;		// [13:9]
	unsigned int dmawfp_b_ns:1;		// [14]
	unsigned int dmawfp_periph:1;		// [15]
	unsigned int reserved2:5;		// [20:16]
	unsigned int CSN:1;		// [21]
	unsigned int reserved:10;		// [31:22]
};
 // GDT1_CPC1 Register
struct GDMAC_GDT1_CPC1 {
	unsigned int pc_chnl:32;		// [31:0]
};
 // GDT1_CSR2 Register
struct GDMAC_GDT1_CSR2 {
	unsigned int Channel_status:4;		// [3:0]
	unsigned int Wakeup_number:5;		// [8:4]
	unsigned int reserved3:5;		// [13:9]
	unsigned int dmawfp_b_ns:1;		// [14]
	unsigned int dmawfp_periph:1;		// [15]
	unsigned int reserved2:5;		// [20:16]
	unsigned int CSN:1;		// [21]
	unsigned int reserved:10;		// [31:22]
};
 // GDT1_CPC2 Register
struct GDMAC_GDT1_CPC2 {
	unsigned int pc_chnl:32;		// [31:0]
};
 // GDT1_CSR3 Register
struct GDMAC_GDT1_CSR3 {
	unsigned int Channel_status:4;		// [3:0]
	unsigned int Wakeup_number:5;		// [8:4]
	unsigned int reserved3:5;		// [13:9]
	unsigned int dmawfp_b_ns:1;		// [14]
	unsigned int dmawfp_periph:1;		// [15]
	unsigned int reserved2:5;		// [20:16]
	unsigned int CSN:1;		// [21]
	unsigned int reserved:10;		// [31:22]
};
 // GDT1_CPC3 Register
struct GDMAC_GDT1_CPC3 {
	unsigned int pc_chnl:32;		// [31:0]
};
 // GDT1_CSR4 Register
struct GDMAC_GDT1_CSR4 {
	unsigned int Channel_status:4;		// [3:0]
	unsigned int Wakeup_number:5;		// [8:4]
	unsigned int reserved3:5;		// [13:9]
	unsigned int dmawfp_b_ns:1;		// [14]
	unsigned int dmawfp_periph:1;		// [15]
	unsigned int reserved2:5;		// [20:16]
	unsigned int CSN:1;		// [21]
	unsigned int reserved:10;		// [31:22]
};
 // GDT1_CPC4 Register
struct GDMAC_GDT1_CPC4 {
	unsigned int pc_chnl:32;		// [31:0]
};
 // GDT1_CSR5 Register
struct GDMAC_GDT1_CSR5 {
	unsigned int Channel_status:4;		// [3:0]
	unsigned int Wakeup_number:5;		// [8:4]
	unsigned int reserved3:5;		// [13:9]
	unsigned int dmawfp_b_ns:1;		// [14]
	unsigned int dmawfp_periph:1;		// [15]
	unsigned int reserved2:5;		// [20:16]
	unsigned int CSN:1;		// [21]
	unsigned int reserved:10;		// [31:22]
};
 // GDT1_CPC5 Register
struct GDMAC_GDT1_CPC5 {
	unsigned int pc_chnl:32;		// [31:0]
};
 // GDT1_CSR6 Register
struct GDMAC_GDT1_CSR6 {
	unsigned int Channel_status:4;		// [3:0]
	unsigned int Wakeup_number:5;		// [8:4]
	unsigned int reserved3:5;		// [13:9]
	unsigned int dmawfp_b_ns:1;		// [14]
	unsigned int dmawfp_periph:1;		// [15]
	unsigned int reserved2:5;		// [20:16]
	unsigned int CSN:1;		// [21]
	unsigned int reserved:10;		// [31:22]
};
 // GDT1_CPC6 Register
struct GDMAC_GDT1_CPC6 {
	unsigned int pc_chnl:32;		// [31:0]
};
 // GDT1_CSR7 Register
struct GDMAC_GDT1_CSR7 {
	unsigned int Channel_status:4;		// [3:0]
	unsigned int Wakeup_number:5;		// [8:4]
	unsigned int reserved3:5;		// [13:9]
	unsigned int dmawfp_b_ns:1;		// [14]
	unsigned int dmawfp_periph:1;		// [15]
	unsigned int reserved2:5;		// [20:16]
	unsigned int CSN:1;		// [21]
	unsigned int reserved:10;		// [31:22]
};
 // GDT1_CPC7 Register
struct GDMAC_GDT1_CPC7 {
	unsigned int pc_chnl:32;		// [31:0]
};
 // GDT1_SAR0 Register
struct GDMAC_GDT1_SAR0 {
	unsigned int src_addr:32;		// [31:0]
};
 // GDT1_DAR0 Register
struct GDMAC_GDT1_DAR0 {
	unsigned int dst_addr:32;		// [31:0]
};
 // GDT1_CCR0 Register
struct GDMAC_GDT1_CCR0 {
	unsigned int src_inc:1;		// [0]
	unsigned int src_burst_size:3;		// [3:1]
	unsigned int src_burst_len:4;		// [7:4]
	unsigned int src_prot_ctrl:3;		// [10:8]
	unsigned int src_cache_ctrl:3;		// [13:11]
	unsigned int dst_inc:1;		// [14]
	unsigned int dst_burst_size:3;		// [17:15]
	unsigned int dst_burst_len:4;		// [21:18]
	unsigned int dst_prot_ctrl:3;		// [24:22]
	unsigned int dst_cache_ctrl:3;		// [27:25]
	unsigned int endian_swap_size:3;		// [30:28]
	unsigned int reserved:1;		// [31]
};
 // GDT1_LC0_0 Register
struct GDMAC_GDT1_LC0_0 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT1_LC1_0 Register
struct GDMAC_GDT1_LC1_0 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT1_SAR1 Register
struct GDMAC_GDT1_SAR1 {
	unsigned int src_addr:32;		// [31:0]
};
 // GDT1_DAR1 Register
struct GDMAC_GDT1_DAR1 {
	unsigned int dst_addr:32;		// [31:0]
};
 // GDT1_CCR1 Register
struct GDMAC_GDT1_CCR1 {
	unsigned int src_inc:1;		// [0]
	unsigned int src_burst_size:3;		// [3:1]
	unsigned int src_burst_len:4;		// [7:4]
	unsigned int src_prot_ctrl:3;		// [10:8]
	unsigned int src_cache_ctrl:3;		// [13:11]
	unsigned int dst_inc:1;		// [14]
	unsigned int dst_burst_size:3;		// [17:15]
	unsigned int dst_burst_len:4;		// [21:18]
	unsigned int dst_prot_ctrl:3;		// [24:22]
	unsigned int dst_cache_ctrl:3;		// [27:25]
	unsigned int endian_swap_size:3;		// [30:28]
	unsigned int reserved:1;		// [31]
};
 // GDT1_LC0_1 Register
struct GDMAC_GDT1_LC0_1 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT1_LC1_1 Register
struct GDMAC_GDT1_LC1_1 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT1_SAR2 Register
struct GDMAC_GDT1_SAR2 {
	unsigned int src_addr:32;		// [31:0]
};
 // GDT1_DAR2 Register
struct GDMAC_GDT1_DAR2 {
	unsigned int dst_addr:32;		// [31:0]
};
 // GDT1_CCR2 Register
struct GDMAC_GDT1_CCR2 {
	unsigned int src_inc:1;		// [0]
	unsigned int src_burst_size:3;		// [3:1]
	unsigned int src_burst_len:4;		// [7:4]
	unsigned int src_prot_ctrl:3;		// [10:8]
	unsigned int src_cache_ctrl:3;		// [13:11]
	unsigned int dst_inc:1;		// [14]
	unsigned int dst_burst_size:3;		// [17:15]
	unsigned int dst_burst_len:4;		// [21:18]
	unsigned int dst_prot_ctrl:3;		// [24:22]
	unsigned int dst_cache_ctrl:3;		// [27:25]
	unsigned int endian_swap_size:3;		// [30:28]
	unsigned int reserved:1;		// [31]
};
 // GDT1_LC0_2 Register
struct GDMAC_GDT1_LC0_2 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT1_LC1_2 Register
struct GDMAC_GDT1_LC1_2 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT1_SAR3 Register
struct GDMAC_GDT1_SAR3 {
	unsigned int src_addr:32;		// [31:0]
};
 // GDT1_DAR3 Register
struct GDMAC_GDT1_DAR3 {
	unsigned int dst_addr:32;		// [31:0]
};
 // GDT1_CCR3 Register
struct GDMAC_GDT1_CCR3 {
	unsigned int src_inc:1;		// [0]
	unsigned int src_burst_size:3;		// [3:1]
	unsigned int src_burst_len:4;		// [7:4]
	unsigned int src_prot_ctrl:3;		// [10:8]
	unsigned int src_cache_ctrl:3;		// [13:11]
	unsigned int dst_inc:1;		// [14]
	unsigned int dst_burst_size:3;		// [17:15]
	unsigned int dst_burst_len:4;		// [21:18]
	unsigned int dst_prot_ctrl:3;		// [24:22]
	unsigned int dst_cache_ctrl:3;		// [27:25]
	unsigned int endian_swap_size:3;		// [30:28]
	unsigned int reserved:1;		// [31]
};
 // GDT1_LC0_3 Register
struct GDMAC_GDT1_LC0_3 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT1_LC1_3 Register
struct GDMAC_GDT1_LC1_3 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT1_SAR4 Register
struct GDMAC_GDT1_SAR4 {
	unsigned int src_addr:32;		// [31:0]
};
 // GDT1_DAR4 Register
struct GDMAC_GDT1_DAR4 {
	unsigned int dst_addr:32;		// [31:0]
};
 // GDT1_CCR4 Register
struct GDMAC_GDT1_CCR4 {
	unsigned int src_inc:1;		// [0]
	unsigned int src_burst_size:3;		// [3:1]
	unsigned int src_burst_len:4;		// [7:4]
	unsigned int src_prot_ctrl:3;		// [10:8]
	unsigned int src_cache_ctrl:3;		// [13:11]
	unsigned int dst_inc:1;		// [14]
	unsigned int dst_burst_size:3;		// [17:15]
	unsigned int dst_burst_len:4;		// [21:18]
	unsigned int dst_prot_ctrl:3;		// [24:22]
	unsigned int dst_cache_ctrl:3;		// [27:25]
	unsigned int endian_swap_size:3;		// [30:28]
	unsigned int reserved:1;		// [31]
};
 // GDT1_LC0_4 Register
struct GDMAC_GDT1_LC0_4 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT1_LC1_4 Register
struct GDMAC_GDT1_LC1_4 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT1_SAR5 Register
struct GDMAC_GDT1_SAR5 {
	unsigned int src_addr:32;		// [31:0]
};
 // GDT1_DAR5 Register
struct GDMAC_GDT1_DAR5 {
	unsigned int dst_addr:32;		// [31:0]
};
 // GDT1_CCR5 Register
struct GDMAC_GDT1_CCR5 {
	unsigned int src_inc:1;		// [0]
	unsigned int src_burst_size:3;		// [3:1]
	unsigned int src_burst_len:4;		// [7:4]
	unsigned int src_prot_ctrl:3;		// [10:8]
	unsigned int src_cache_ctrl:3;		// [13:11]
	unsigned int dst_inc:1;		// [14]
	unsigned int dst_burst_size:3;		// [17:15]
	unsigned int dst_burst_len:4;		// [21:18]
	unsigned int dst_prot_ctrl:3;		// [24:22]
	unsigned int dst_cache_ctrl:3;		// [27:25]
	unsigned int endian_swap_size:3;		// [30:28]
	unsigned int reserved:1;		// [31]
};
 // GDT1_LC0_5 Register
struct GDMAC_GDT1_LC0_5 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT1_LC1_5 Register
struct GDMAC_GDT1_LC1_5 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT1_SAR6 Register
struct GDMAC_GDT1_SAR6 {
	unsigned int src_addr:32;		// [31:0]
};
 // GDT1_DAR6 Register
struct GDMAC_GDT1_DAR6 {
	unsigned int dst_addr:32;		// [31:0]
};
 // GDT1_CCR6 Register
struct GDMAC_GDT1_CCR6 {
	unsigned int src_inc:1;		// [0]
	unsigned int src_burst_size:3;		// [3:1]
	unsigned int src_burst_len:4;		// [7:4]
	unsigned int src_prot_ctrl:3;		// [10:8]
	unsigned int src_cache_ctrl:3;		// [13:11]
	unsigned int dst_inc:1;		// [14]
	unsigned int dst_burst_size:3;		// [17:15]
	unsigned int dst_burst_len:4;		// [21:18]
	unsigned int dst_prot_ctrl:3;		// [24:22]
	unsigned int dst_cache_ctrl:3;		// [27:25]
	unsigned int endian_swap_size:3;		// [30:28]
	unsigned int reserved:1;		// [31]
};
 // GDT1_LC0_6 Register
struct GDMAC_GDT1_LC0_6 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT1_LC1_6 Register
struct GDMAC_GDT1_LC1_6 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT1_SAR7 Register
struct GDMAC_GDT1_SAR7 {
	unsigned int src_addr:32;		// [31:0]
};
 // GDT1_DAR7 Register
struct GDMAC_GDT1_DAR7 {
	unsigned int dst_addr:32;		// [31:0]
};
 // GDT1_CCR7 Register
struct GDMAC_GDT1_CCR7 {
	unsigned int src_inc:1;		// [0]
	unsigned int src_burst_size:3;		// [3:1]
	unsigned int src_burst_len:4;		// [7:4]
	unsigned int src_prot_ctrl:3;		// [10:8]
	unsigned int src_cache_ctrl:3;		// [13:11]
	unsigned int dst_inc:1;		// [14]
	unsigned int dst_burst_size:3;		// [17:15]
	unsigned int dst_burst_len:4;		// [21:18]
	unsigned int dst_prot_ctrl:3;		// [24:22]
	unsigned int dst_cache_ctrl:3;		// [27:25]
	unsigned int endian_swap_size:3;		// [30:28]
	unsigned int reserved:1;		// [31]
};
 // GDT1_LC0_7 Register
struct GDMAC_GDT1_LC0_7 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT1_LC1_7 Register
struct GDMAC_GDT1_LC1_7 {
	unsigned int Loop_counter_iterations:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT1_DBGSTATUS Register
struct GDMAC_GDT1_DBGSTATUS {
	unsigned int dbg_status:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // GDT1_DBGCMD Register
struct GDMAC_GDT1_DBGCMD {
	unsigned int dbgcmd:2;		// [1:0]
	unsigned int reserved:30;		// [31:2]
};
 // GDT1_DBGINST0 Register
struct GDMAC_GDT1_DBGINST0 {
	unsigned int Debug_thread:1;		// [0]
	unsigned int reserved2:7;		// [7:1]
	unsigned int Channel_number:3;		// [10:8]
	unsigned int reserved:5;		// [15:11]
	unsigned int Instruction_byte_0:8;		// [23:16]
	unsigned int Instruction_byte_1:8;		// [31:24]
};
 // GDT1_DBGINST1 Register
struct GDMAC_GDT1_DBGINST1 {
	unsigned int Instruction_byte_2:8;		// [7:0]
	unsigned int Instruction_byte_3:8;		// [15:8]
	unsigned int Instruction_byte_4:8;		// [23:16]
	unsigned int Instruction_byte_5:8;		// [31:24]
};
 // GDT1_CR0 Register
struct GDMAC_GDT1_CR0 {
	unsigned int periph_req:1;		// [0]
	unsigned int boot_en:1;		// [1]
	unsigned int mgr_ns_at_rst:1;		// [2]
	unsigned int reserved3:1;		// [3]
	unsigned int num_chnls:3;		// [6:4]
	unsigned int reserved2:5;		// [11:7]
	unsigned int num_periph_req:5;		// [16:12]
	unsigned int num_events:5;		// [21:17]
	unsigned int reserved:10;		// [31:22]
};
 // GDT1_CR1 Register
struct GDMAC_GDT1_CR1 {
	unsigned int i_cache_len:3;		// [2:0]
	unsigned int reserved2:1;		// [3]
	unsigned int num_i_cache_lines:4;		// [7:4]
	unsigned int reserved:24;		// [31:8]
};
 // GDT1_CR2 Register
struct GDMAC_GDT1_CR2 {
	unsigned int boot_addr:32;		// [31:0]
};
 // GDT1_CR3 Register
struct GDMAC_GDT1_CR3 {
	unsigned int INS:16;		// [15:0]
	unsigned int reserved:16;		// [31:16]
};
 // GDT1_CR4 Register
struct GDMAC_GDT1_CR4 {
	unsigned int PNS:24;		// [23:0]
	unsigned int reserved:8;		// [31:24]
};
 // GDT1_CRD Register
struct GDMAC_GDT1_CRD {
	unsigned int data_width:3;		// [2:0]
	unsigned int reserved4:1;		// [3]
	unsigned int wr_cap:3;		// [6:4]
	unsigned int reserved3:1;		// [7]
	unsigned int wr_q_dep:4;		// [11:8]
	unsigned int rd_cap:3;		// [14:12]
	unsigned int reserved2:1;		// [15]
	unsigned int rd_q_dep:4;		// [19:16]
	unsigned int data_buffer_dep:10;		// [29:20]
	unsigned int reserved:2;		// [31:30]
};
 // GDT1_WD Register
struct GDMAC_GDT1_WD {
	unsigned int wd_irq_only:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // GDT1_periph_id_0 Register
struct GDMAC_GDT1_PERIPH_ID_0 {
	unsigned int part_number_0:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT1_periph_id_1 Register
struct GDMAC_GDT1_PERIPH_ID_1 {
	unsigned int part_number_1:4;		// [3:0]
	unsigned int designer_0:4;		// [7:4]
	unsigned int reserved:24;		// [31:8]
};
 // GDT1_periph_id_2 Register
struct GDMAC_GDT1_PERIPH_ID_2 {
	unsigned int designer_1:4;		// [3:0]
	unsigned int revision:4;		// [7:4]
	unsigned int reserved:24;		// [31:8]
};
 // GDT1_periph_id_3 Register
struct GDMAC_GDT1_PERIPH_ID_3 {
	unsigned int revision:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // GDT1_pcell_id_0 Register
struct GDMAC_GDT1_PCELL_ID_0 {
	unsigned int pcell_id_0:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT1_pcell_id_1 Register
struct GDMAC_GDT1_PCELL_ID_1 {
	unsigned int pcell_id_1:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT1_pcell_id_2 Register
struct GDMAC_GDT1_PCELL_ID_2 {
	unsigned int pcell_id_2:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // GDT1_pcell_id_3 Register
struct GDMAC_GDT1_PCELL_ID_3 {
	unsigned int pcell_id_3:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _GDMAC_REG_STRUCT_L_H */
