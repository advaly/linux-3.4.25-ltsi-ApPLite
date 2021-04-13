/*
 * arch/arm/mach-tz3000/include/mach/regs/nandc_reg_struct_l.h
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

#ifndef _NANDC_REG_STRUCT_L_H
#define _NANDC_REG_STRUCT_L_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // memc_status Register
struct NANDC_MEMC_STATUS {
	unsigned int state:1;		// [0]
	unsigned int int_en0:1;		// [1]
	unsigned int int_en1:1;		// [2]
	unsigned int int_status0:1;		// [3]
	unsigned int int_status1:1;		// [4]
	unsigned int raw_int_status0:1;		// [5]
	unsigned int raw_int_status1:1;		// [6]
	unsigned int ecc_int_en0:1;		// [7]
	unsigned int ecc_int_en1:1;		// [8]
	unsigned int ecc_int0:1;		// [9]
	unsigned int ecc_int1:1;		// [10]
	unsigned int raw_ecc_int0:1;		// [11]
	unsigned int raw_ecc_int1:1;		// [12]
	unsigned int reserved:19;		// [31:13]
};
 // memif_cfg Register
struct NANDC_MEMIF_CFG {
	unsigned int memory0_type:2;		// [1:0]
	unsigned int memory0_chips:2;		// [3:2]
	unsigned int memory0_bytes:2;		// [5:4]
	unsigned int remap0:1;		// [6]
	unsigned int reserved3:1;		// [7]
	unsigned int memory1_type:2;		// [9:8]
	unsigned int memory1_chips:2;		// [11:10]
	unsigned int memory1_bytes:2;		// [13:12]
	unsigned int remap1:1;		// [14]
	unsigned int reserved2:1;		// [15]
	unsigned int exclusive_monitors:2;		// [17:16]
	unsigned int reserved:14;		// [31:18]
};
 // mem_cfg_set Register
struct NANDC_MEM_CFG_SET {
	unsigned int int_enable0:1;		// [0]
	unsigned int int_enable1:1;		// [1]
	unsigned int low_power_req:1;		// [2]
	unsigned int reserved2:2;		// [4:3]
	unsigned int ecc_int_enable0:1;		// [5]
	unsigned int ecc_int_enable1:1;		// [6]
	unsigned int reserved:25;		// [31:7]
};
 // mem_cfg_clr Register
struct NANDC_MEM_CFG_CLR {
	unsigned int int_disable0:1;		// [0]
	unsigned int int_disable1:1;		// [1]
	unsigned int low_power_exit:1;		// [2]
	unsigned int int_clear0:1;		// [3]
	unsigned int int_clear1:1;		// [4]
	unsigned int ecc_int_disable0:1;		// [5]
	unsigned int ecc_int_disable1:1;		// [6]
	unsigned int reserved:25;		// [31:7]
};
 // direct_cmd Register
struct NANDC_DIRECT_CMD {
	unsigned int addr_19_to_0:20;		// [19:0]
	unsigned int set_cre:1;		// [20]
	unsigned int cmd_type:2;		// [22:21]
	unsigned int chip_nmbr:3;		// [25:23]
	unsigned int reserved:6;		// [31:26]
};
 // set_cycles Register
struct NANDC_SET_CYCLES {
	unsigned int set_t0:4;		// [3:0]
	unsigned int set_t1:4;		// [7:4]
	unsigned int set_t2:3;		// [10:8]
	unsigned int set_t3:3;		// [13:11]
	unsigned int set_t4:3;		// [16:14]
	unsigned int set_t5:3;		// [19:17]
	unsigned int set_t6:4;		// [23:20]
	unsigned int reserved:8;		// [31:24]
};
 // set_opmode Register
struct NANDC_SET_OPMODE {
	unsigned int set_mw:2;		// [1:0]
	unsigned int set_rd_sync:1;		// [2]
	unsigned int set_rd_bl:3;		// [5:3]
	unsigned int set_wr_sync:1;		// [6]
	unsigned int set_wr_bl:3;		// [9:7]
	unsigned int set_baa:1;		// [10]
	unsigned int set_adv:1;		// [11]
	unsigned int set_bls_time:1;		// [12]
	unsigned int set_burst_align:3;		// [15:13]
	unsigned int reserved:16;		// [31:16]
};
 // refresh_0 Register
struct NANDC_REFRESH_0 {
	unsigned int ref_period0:4;		// [3:0]
	unsigned int reserved:28;		// [31:4]
};
 // refresh_1 Register
struct NANDC_REFRESH_1 {
	unsigned int ref_period1:4;		// [3:0]
	unsigned int reserved:28;		// [31:4]
};
 // nand_cycles0_0 Register
struct NANDC_NAND_CYCLES0_0 {
	unsigned int t_rc0:4;		// [3:0]
	unsigned int t_wc0:4;		// [7:4]
	unsigned int t_rea0:3;		// [10:8]
	unsigned int t_wp0:3;		// [13:11]
	unsigned int t_clr0:3;		// [16:14]
	unsigned int t_ar0:3;		// [19:17]
	unsigned int t_rr0:4;		// [23:20]
	unsigned int reserved:8;		// [31:24]
};
 // opmode0_0 Register
struct NANDC_OPMODE0_0 {
	unsigned int mw0:2;		// [1:0]
	unsigned int rd_sync0:1;		// [2]
	unsigned int rd_bl0:3;		// [5:3]
	unsigned int wr_sync0:1;		// [6]
	unsigned int wr_bl0:3;		// [9:7]
	unsigned int baa0:1;		// [10]
	unsigned int adv0:1;		// [11]
	unsigned int bls_time0:1;		// [12]
	unsigned int burst_align0:3;		// [15:13]
	unsigned int addr_mask0:8;		// [23:16]
	unsigned int addr_match0:8;		// [31:24]
};
 // nand_cycles0_1 Register
struct NANDC_NAND_CYCLES0_1 {
	unsigned int t_rc0:4;		// [3:0]
	unsigned int t_wc0:4;		// [7:4]
	unsigned int t_rea0:3;		// [10:8]
	unsigned int t_wp0:3;		// [13:11]
	unsigned int t_clr0:3;		// [16:14]
	unsigned int t_ar0:3;		// [19:17]
	unsigned int t_rr0:4;		// [23:20]
	unsigned int reserved:8;		// [31:24]
};
 // opmode0_1 Register
struct NANDC_OPMODE0_1 {
	unsigned int mw0:2;		// [1:0]
	unsigned int rd_sync0:1;		// [2]
	unsigned int rd_bl0:3;		// [5:3]
	unsigned int wr_sync0:1;		// [6]
	unsigned int wr_bl0:3;		// [9:7]
	unsigned int baa0:1;		// [10]
	unsigned int adv0:1;		// [11]
	unsigned int bls_time0:1;		// [12]
	unsigned int burst_align0:3;		// [15:13]
	unsigned int addr_mask0:8;		// [23:16]
	unsigned int addr_match0:8;		// [31:24]
};
 // nand_cycles0_2 Register
struct NANDC_NAND_CYCLES0_2 {
	unsigned int t_rc0:4;		// [3:0]
	unsigned int t_wc0:4;		// [7:4]
	unsigned int t_rea0:3;		// [10:8]
	unsigned int t_wp0:3;		// [13:11]
	unsigned int t_clr0:3;		// [16:14]
	unsigned int t_ar0:3;		// [19:17]
	unsigned int t_rr0:4;		// [23:20]
	unsigned int reserved:8;		// [31:24]
};
 // opmode0_2 Register
struct NANDC_OPMODE0_2 {
	unsigned int mw0:2;		// [1:0]
	unsigned int rd_sync0:1;		// [2]
	unsigned int rd_bl0:3;		// [5:3]
	unsigned int wr_sync0:1;		// [6]
	unsigned int wr_bl0:3;		// [9:7]
	unsigned int baa0:1;		// [10]
	unsigned int adv0:1;		// [11]
	unsigned int bls_time0:1;		// [12]
	unsigned int burst_align0:3;		// [15:13]
	unsigned int addr_mask0:8;		// [23:16]
	unsigned int addr_match0:8;		// [31:24]
};
 // nand_cycles0_3 Register
struct NANDC_NAND_CYCLES0_3 {
	unsigned int t_rc0:4;		// [3:0]
	unsigned int t_wc0:4;		// [7:4]
	unsigned int t_rea0:3;		// [10:8]
	unsigned int t_wp0:3;		// [13:11]
	unsigned int t_clr0:3;		// [16:14]
	unsigned int t_ar0:3;		// [19:17]
	unsigned int t_rr0:4;		// [23:20]
	unsigned int reserved:8;		// [31:24]
};
 // opmode0_3 Register
struct NANDC_OPMODE0_3 {
	unsigned int mw0:2;		// [1:0]
	unsigned int rd_sync0:1;		// [2]
	unsigned int rd_bl0:3;		// [5:3]
	unsigned int wr_sync0:1;		// [6]
	unsigned int wr_bl0:3;		// [9:7]
	unsigned int baa0:1;		// [10]
	unsigned int adv0:1;		// [11]
	unsigned int bls_time0:1;		// [12]
	unsigned int burst_align0:3;		// [15:13]
	unsigned int addr_mask0:8;		// [23:16]
	unsigned int addr_match0:8;		// [31:24]
};
 // user_status Register
struct NANDC_USER_STATUS {
	unsigned int user_status:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // user_config Register
struct NANDC_USER_CONFIG {
	unsigned int user_config:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // ecc0_status Register
struct NANDC_ECC0_STATUS {
	unsigned int ecc_int_status:6;		// [5:0]
	unsigned int ecc_status:1;		// [6]
	unsigned int ecc_last_status:2;		// [8:7]
	unsigned int ecc_rd_n_wr:1;		// [9]
	unsigned int ecc_value_valid:5;		// [14:10]
	unsigned int ecc_fail:5;		// [19:15]
	unsigned int ecc_can_correct:5;		// [24:20]
	unsigned int ecc_read:5;		// [29:25]
	unsigned int reserved:2;		// [31:30]
};
 // ecc0_cfg Register
struct NANDC_ECC0_CFG {
	unsigned int page_size:2;		// [1:0]
	unsigned int ecc_mode:2;		// [3:2]
	unsigned int ecc_read_end:1;		// [4]
	unsigned int ecc_jump:2;		// [6:5]
	unsigned int ecc_ignore_add_eight:1;		// [7]
	unsigned int ecc_int_pass:1;		// [8]
	unsigned int ecc_int_abort:1;		// [9]
	unsigned int ecc_extra_block:1;		// [10]
	unsigned int ecc_extra_block_size:2;		// [12:11]
	unsigned int reserved:19;		// [31:13]
};
 // ecc0_memcmd0 Register
struct NANDC_ECC0_MEMCMD0 {
	unsigned int nand0_wr_cmd:8;		// [7:0]
	unsigned int nand0_rd_cmd:8;		// [15:8]
	unsigned int nand0_rd_end_cmd:8;		// [23:16]
	unsigned int nand0_rd_end_cmd_v:1;		// [24]
	unsigned int reserved:7;		// [31:25]
};
 // ecc0_memcmd1 Register
struct NANDC_ECC0_MEMCMD1 {
	unsigned int nand0_wr_col_change:8;		// [7:0]
	unsigned int nand0_rd_col_change:8;		// [15:8]
	unsigned int nand0_rd_end_col_change:8;		// [23:16]
	unsigned int nand0_rd_end_col_change_v:1;		// [24]
	unsigned int reserved:7;		// [31:25]
};
 // ecc0_addr0 Register
struct NANDC_ECC0_ADDR0 {
	unsigned int ecc0_add_low:32;		// [31:0]
};
 // ecc0_addr1 Register
struct NANDC_ECC0_ADDR1 {
	unsigned int ecc0_add_high:24;		// [23:0]
	unsigned int reserved:8;		// [31:24]
};
 // ecc0_block0 Register
struct NANDC_ECC0_BLOCK0 {
	unsigned int ecc0_block0_val:24;		// [23:0]
	unsigned int reserved:3;		// [26:24]
	unsigned int ecc0_0_correct:1;		// [27]
	unsigned int ecc0_0_fail:1;		// [28]
	unsigned int ecc0_0_read:1;		// [29]
	unsigned int ecc0_0_valid:1;		// [30]
	unsigned int ecc0_0_int:1;		// [31]
};
 // ecc0_block1 Register
struct NANDC_ECC0_BLOCK1 {
	unsigned int ecc0_block1_val:24;		// [23:0]
	unsigned int reserved:3;		// [26:24]
	unsigned int ecc0_1_correct:1;		// [27]
	unsigned int ecc0_1_fail:1;		// [28]
	unsigned int ecc0_1_read:1;		// [29]
	unsigned int ecc0_1_valid:1;		// [30]
	unsigned int ecc0_1_int:1;		// [31]
};
 // ecc0_block2 Register
struct NANDC_ECC0_BLOCK2 {
	unsigned int ecc0_block2_val:24;		// [23:0]
	unsigned int reserved:3;		// [26:24]
	unsigned int ecc0_2_correct:1;		// [27]
	unsigned int ecc0_2_fail:1;		// [28]
	unsigned int ecc0_2_read:1;		// [29]
	unsigned int ecc0_2_valid:1;		// [30]
	unsigned int ecc0_2_int:1;		// [31]
};
 // ecc0_block3 Register
struct NANDC_ECC0_BLOCK3 {
	unsigned int ecc0_block3_val:24;		// [23:0]
	unsigned int reserved:3;		// [26:24]
	unsigned int ecc0_3_correct:1;		// [27]
	unsigned int ecc0_3_fail:1;		// [28]
	unsigned int ecc0_3_read:1;		// [29]
	unsigned int ecc0_3_valid:1;		// [30]
	unsigned int ecc0_3_int:1;		// [31]
};
 // ecc0_extra_block Register
struct NANDC_ECC0_EXTRA_BLOCK {
	unsigned int ecc0_extra_val:24;		// [23:0]
	unsigned int reserved:3;		// [26:24]
	unsigned int ecc0_e_correct:1;		// [27]
	unsigned int ecc0_e_fail:1;		// [28]
	unsigned int ecc0_e_read:1;		// [29]
	unsigned int ecc0_e_valid:1;		// [30]
	unsigned int ecc0_e_int:1;		// [31]
};
 // int_cfg Register
struct NANDC_INT_CFG {
	unsigned int int_test_en:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // int_inputs Register
struct NANDC_INT_INPUTS {
	unsigned int csysreq:1;		// [0]
	unsigned int use_ebi:1;		// [1]
	unsigned int ebigrant0:1;		// [2]
	unsigned int ebibackoff0:1;		// [3]
	unsigned int async0:1;		// [4]
	unsigned int msync0:1;		// [5]
	unsigned int ebigrant1:1;		// [6]
	unsigned int ebibackoff1:1;		// [7]
	unsigned int async1:1;		// [8]
	unsigned int msync1:1;		// [9]
	unsigned int reserved:22;		// [31:10]
};
 // int_outputs Register
struct NANDC_INT_OUTPUTS {
	unsigned int cactive_int:1;		// [0]
	unsigned int csysack_int:1;		// [1]
	unsigned int ebireq0_int:1;		// [2]
	unsigned int ebireq1_int:1;		// [3]
	unsigned int smc_int_int:1;		// [4]
	unsigned int smc_int0_int:1;		// [5]
	unsigned int smc_int1_int:1;		// [6]
	unsigned int ecc_int0_int:1;		// [7]
	unsigned int ecc_int1_int:1;		// [8]
	unsigned int reserved:23;		// [31:9]
};
 // periph_id_0 Register
struct NANDC_PERIPH_ID_0 {
	unsigned int part_number_0:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // periph_id_1 Register
struct NANDC_PERIPH_ID_1 {
	unsigned int part_number_1:4;		// [3:0]
	unsigned int designer_0:4;		// [7:4]
	unsigned int reserved:24;		// [31:8]
};
 // periph_id_2 Register
struct NANDC_PERIPH_ID_2 {
	unsigned int designer_1:4;		// [3:0]
	unsigned int revision:4;		// [7:4]
	unsigned int reserved:24;		// [31:8]
};
 // periph_id_3 Register
struct NANDC_PERIPH_ID_3 {
	unsigned int reserved:32;		// [31:0]
};
 // pcell_id_0 Register
struct NANDC_PCELL_ID_0 {
	unsigned int pcell_id_0:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // pcell_id_1 Register
struct NANDC_PCELL_ID_1 {
	unsigned int pcell_id_1:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // pcell_id_2 Register
struct NANDC_PCELL_ID_2 {
	unsigned int pcell_id_2:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // pcell_id_3 Register
struct NANDC_PCELL_ID_3 {
	unsigned int pcell_id_3:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _NANDC_REG_STRUCT_L_H */
