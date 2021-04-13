/*
 * arch/arm/mach-tz3000/include/mach/regs/nandc_reg_def.h
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

#ifndef _NANDC_REG_DEF_H
#define _NANDC_REG_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

// memc_status Register
#define NANDC_MEMC_STATUS_OFS                    0x00000000
// state bitfiled (RO) Reset=0
#define NANDC_MEMC_STATUS_STATE_MASK             0x1
#define NANDC_MEMC_STATUS_STATE_SHIFT            0 
#define NANDC_MEMC_STATUS_STATE_BIT              0x1
#define NANDC_MEMC_STATUS_STATE_BITWIDTH         1
// int_en0 bitfiled (RO) Reset=0
#define NANDC_MEMC_STATUS_INT_EN0_MASK           0x2
#define NANDC_MEMC_STATUS_INT_EN0_SHIFT          1 
#define NANDC_MEMC_STATUS_INT_EN0_BIT            0x1
#define NANDC_MEMC_STATUS_INT_EN0_BITWIDTH       1
// int_en1 bitfiled (RO) Reset=0
#define NANDC_MEMC_STATUS_INT_EN1_MASK           0x4
#define NANDC_MEMC_STATUS_INT_EN1_SHIFT          2 
#define NANDC_MEMC_STATUS_INT_EN1_BIT            0x1
#define NANDC_MEMC_STATUS_INT_EN1_BITWIDTH       1
// int_status0 bitfiled (RO) Reset=0
#define NANDC_MEMC_STATUS_INT_STATUS0_MASK       0x8
#define NANDC_MEMC_STATUS_INT_STATUS0_SHIFT      3 
#define NANDC_MEMC_STATUS_INT_STATUS0_BIT        0x1
#define NANDC_MEMC_STATUS_INT_STATUS0_BITWIDTH   1
// int_status1 bitfiled (RO) Reset=0
#define NANDC_MEMC_STATUS_INT_STATUS1_MASK       0x10
#define NANDC_MEMC_STATUS_INT_STATUS1_SHIFT      4 
#define NANDC_MEMC_STATUS_INT_STATUS1_BIT        0x1
#define NANDC_MEMC_STATUS_INT_STATUS1_BITWIDTH   1
// raw_int_status0 bitfiled (RO) Reset=0
#define NANDC_MEMC_STATUS_RAW_INT_STATUS0_MASK   0x20
#define NANDC_MEMC_STATUS_RAW_INT_STATUS0_SHIFT  5 
#define NANDC_MEMC_STATUS_RAW_INT_STATUS0_BIT    0x1
#define NANDC_MEMC_STATUS_RAW_INT_STATUS0_BITWIDTH 1
// raw_int_status1 bitfiled (RO) Reset=0
#define NANDC_MEMC_STATUS_RAW_INT_STATUS1_MASK   0x40
#define NANDC_MEMC_STATUS_RAW_INT_STATUS1_SHIFT  6 
#define NANDC_MEMC_STATUS_RAW_INT_STATUS1_BIT    0x1
#define NANDC_MEMC_STATUS_RAW_INT_STATUS1_BITWIDTH 1
// ecc_int_en0 bitfiled (RO) Reset=0
#define NANDC_MEMC_STATUS_ECC_INT_EN0_MASK       0x80
#define NANDC_MEMC_STATUS_ECC_INT_EN0_SHIFT      7 
#define NANDC_MEMC_STATUS_ECC_INT_EN0_BIT        0x1
#define NANDC_MEMC_STATUS_ECC_INT_EN0_BITWIDTH   1
// ecc_int_en1 bitfiled (RO) Reset=0
#define NANDC_MEMC_STATUS_ECC_INT_EN1_MASK       0x100
#define NANDC_MEMC_STATUS_ECC_INT_EN1_SHIFT      8 
#define NANDC_MEMC_STATUS_ECC_INT_EN1_BIT        0x1
#define NANDC_MEMC_STATUS_ECC_INT_EN1_BITWIDTH   1
// ecc_int0 bitfiled (RO) Reset=0
#define NANDC_MEMC_STATUS_ECC_INT0_MASK          0x200
#define NANDC_MEMC_STATUS_ECC_INT0_SHIFT         9 
#define NANDC_MEMC_STATUS_ECC_INT0_BIT           0x1
#define NANDC_MEMC_STATUS_ECC_INT0_BITWIDTH      1
// ecc_int1 bitfiled (RO) Reset=0
#define NANDC_MEMC_STATUS_ECC_INT1_MASK          0x400
#define NANDC_MEMC_STATUS_ECC_INT1_SHIFT         10 
#define NANDC_MEMC_STATUS_ECC_INT1_BIT           0x1
#define NANDC_MEMC_STATUS_ECC_INT1_BITWIDTH      1
// raw_ecc_int0 bitfiled (RO) Reset=0
#define NANDC_MEMC_STATUS_RAW_ECC_INT0_MASK      0x800
#define NANDC_MEMC_STATUS_RAW_ECC_INT0_SHIFT     11 
#define NANDC_MEMC_STATUS_RAW_ECC_INT0_BIT       0x1
#define NANDC_MEMC_STATUS_RAW_ECC_INT0_BITWIDTH  1
// raw_ecc_int1 bitfiled (RO) Reset=0
#define NANDC_MEMC_STATUS_RAW_ECC_INT1_MASK      0x1000
#define NANDC_MEMC_STATUS_RAW_ECC_INT1_SHIFT     12 
#define NANDC_MEMC_STATUS_RAW_ECC_INT1_BIT       0x1
#define NANDC_MEMC_STATUS_RAW_ECC_INT1_BITWIDTH  1
// reserved bitfiled (RO) Reset=0
#define NANDC_MEMC_STATUS_RESERVED_MASK          0xFFFFE000
#define NANDC_MEMC_STATUS_RESERVED_SHIFT         13 
#define NANDC_MEMC_STATUS_RESERVED_BIT           0x7FFFF
#define NANDC_MEMC_STATUS_RESERVED_BITWIDTH      19
// memif_cfg Register
#define NANDC_MEMIF_CFG_OFS                      0x00000004
// memory0_type bitfiled (RO) Reset=10
#define NANDC_MEMIF_CFG_MEMORY0_TYPE_MASK        0x3
#define NANDC_MEMIF_CFG_MEMORY0_TYPE_SHIFT       0 
#define NANDC_MEMIF_CFG_MEMORY0_TYPE_BIT         0x3
#define NANDC_MEMIF_CFG_MEMORY0_TYPE_BITWIDTH    2
// memory0_chips bitfiled (RO) Reset=0
#define NANDC_MEMIF_CFG_MEMORY0_CHIPS_MASK       0xC
#define NANDC_MEMIF_CFG_MEMORY0_CHIPS_SHIFT      2 
#define NANDC_MEMIF_CFG_MEMORY0_CHIPS_BIT        0x3
#define NANDC_MEMIF_CFG_MEMORY0_CHIPS_BITWIDTH   2
// memory0_bytes bitfiled (RO) Reset=0
#define NANDC_MEMIF_CFG_MEMORY0_BYTES_MASK       0x30
#define NANDC_MEMIF_CFG_MEMORY0_BYTES_SHIFT      4 
#define NANDC_MEMIF_CFG_MEMORY0_BYTES_BIT        0x3
#define NANDC_MEMIF_CFG_MEMORY0_BYTES_BITWIDTH   2
// remap0 bitfiled (RO) Reset=0
#define NANDC_MEMIF_CFG_REMAP0_MASK              0x40
#define NANDC_MEMIF_CFG_REMAP0_SHIFT             6 
#define NANDC_MEMIF_CFG_REMAP0_BIT               0x1
#define NANDC_MEMIF_CFG_REMAP0_BITWIDTH          1
// reserved3 bitfiled (RO) Reset=0
#define NANDC_MEMIF_CFG_RESERVED3_MASK           0x80
#define NANDC_MEMIF_CFG_RESERVED3_SHIFT          7 
#define NANDC_MEMIF_CFG_RESERVED3_BIT            0x1
#define NANDC_MEMIF_CFG_RESERVED3_BITWIDTH       1
// memory1_type bitfiled (RO) Reset=0
#define NANDC_MEMIF_CFG_MEMORY1_TYPE_MASK        0x300
#define NANDC_MEMIF_CFG_MEMORY1_TYPE_SHIFT       8 
#define NANDC_MEMIF_CFG_MEMORY1_TYPE_BIT         0x3
#define NANDC_MEMIF_CFG_MEMORY1_TYPE_BITWIDTH    2
// memory1_chips bitfiled (RO) Reset=0
#define NANDC_MEMIF_CFG_MEMORY1_CHIPS_MASK       0xC00
#define NANDC_MEMIF_CFG_MEMORY1_CHIPS_SHIFT      10 
#define NANDC_MEMIF_CFG_MEMORY1_CHIPS_BIT        0x3
#define NANDC_MEMIF_CFG_MEMORY1_CHIPS_BITWIDTH   2
// memory1_bytes bitfiled (RO) Reset=0
#define NANDC_MEMIF_CFG_MEMORY1_BYTES_MASK       0x3000
#define NANDC_MEMIF_CFG_MEMORY1_BYTES_SHIFT      12 
#define NANDC_MEMIF_CFG_MEMORY1_BYTES_BIT        0x3
#define NANDC_MEMIF_CFG_MEMORY1_BYTES_BITWIDTH   2
// remap1 bitfiled (RO) Reset=0
#define NANDC_MEMIF_CFG_REMAP1_MASK              0x4000
#define NANDC_MEMIF_CFG_REMAP1_SHIFT             14 
#define NANDC_MEMIF_CFG_REMAP1_BIT               0x1
#define NANDC_MEMIF_CFG_REMAP1_BITWIDTH          1
// reserved2 bitfiled (RO) Reset=0
#define NANDC_MEMIF_CFG_RESERVED2_MASK           0x8000
#define NANDC_MEMIF_CFG_RESERVED2_SHIFT          15 
#define NANDC_MEMIF_CFG_RESERVED2_BIT            0x1
#define NANDC_MEMIF_CFG_RESERVED2_BITWIDTH       1
// exclusive_monitors bitfiled (RO) Reset=0
#define NANDC_MEMIF_CFG_EXCLUSIVE_MONITORS_MASK  0x30000
#define NANDC_MEMIF_CFG_EXCLUSIVE_MONITORS_SHIFT 16 
#define NANDC_MEMIF_CFG_EXCLUSIVE_MONITORS_BIT   0x3
#define NANDC_MEMIF_CFG_EXCLUSIVE_MONITORS_BITWIDTH 2
// reserved bitfiled (RO) Reset=0
#define NANDC_MEMIF_CFG_RESERVED_MASK            0xFFFC0000
#define NANDC_MEMIF_CFG_RESERVED_SHIFT           18 
#define NANDC_MEMIF_CFG_RESERVED_BIT             0x3FFF
#define NANDC_MEMIF_CFG_RESERVED_BITWIDTH        14
// mem_cfg_set Register
#define NANDC_MEM_CFG_SET_OFS                    0x00000008
// int_enable0 bitfiled (RW) Reset=0
#define NANDC_MEM_CFG_SET_INT_ENABLE0_MASK       0x1
#define NANDC_MEM_CFG_SET_INT_ENABLE0_SHIFT      0 
#define NANDC_MEM_CFG_SET_INT_ENABLE0_BIT        0x1
#define NANDC_MEM_CFG_SET_INT_ENABLE0_BITWIDTH   1
// int_enable1 bitfiled (RW) Reset=0
#define NANDC_MEM_CFG_SET_INT_ENABLE1_MASK       0x2
#define NANDC_MEM_CFG_SET_INT_ENABLE1_SHIFT      1 
#define NANDC_MEM_CFG_SET_INT_ENABLE1_BIT        0x1
#define NANDC_MEM_CFG_SET_INT_ENABLE1_BITWIDTH   1
// low_power_req bitfiled (RW) Reset=0
#define NANDC_MEM_CFG_SET_LOW_POWER_REQ_MASK     0x4
#define NANDC_MEM_CFG_SET_LOW_POWER_REQ_SHIFT    2 
#define NANDC_MEM_CFG_SET_LOW_POWER_REQ_BIT      0x1
#define NANDC_MEM_CFG_SET_LOW_POWER_REQ_BITWIDTH 1
// reserved2 bitfiled (RO) Reset=0
#define NANDC_MEM_CFG_SET_RESERVED2_MASK         0x18
#define NANDC_MEM_CFG_SET_RESERVED2_SHIFT        3 
#define NANDC_MEM_CFG_SET_RESERVED2_BIT          0x3
#define NANDC_MEM_CFG_SET_RESERVED2_BITWIDTH     2
// ecc_int_enable0 bitfiled (RW) Reset=0
#define NANDC_MEM_CFG_SET_ECC_INT_ENABLE0_MASK   0x20
#define NANDC_MEM_CFG_SET_ECC_INT_ENABLE0_SHIFT  5 
#define NANDC_MEM_CFG_SET_ECC_INT_ENABLE0_BIT    0x1
#define NANDC_MEM_CFG_SET_ECC_INT_ENABLE0_BITWIDTH 1
// ecc_int_enable1 bitfiled (RW) Reset=0
#define NANDC_MEM_CFG_SET_ECC_INT_ENABLE1_MASK   0x40
#define NANDC_MEM_CFG_SET_ECC_INT_ENABLE1_SHIFT  6 
#define NANDC_MEM_CFG_SET_ECC_INT_ENABLE1_BIT    0x1
#define NANDC_MEM_CFG_SET_ECC_INT_ENABLE1_BITWIDTH 1
// reserved bitfiled (RO) Reset=0
#define NANDC_MEM_CFG_SET_RESERVED_MASK          0xFFFFFF80
#define NANDC_MEM_CFG_SET_RESERVED_SHIFT         7 
#define NANDC_MEM_CFG_SET_RESERVED_BIT           0x1FFFFFF
#define NANDC_MEM_CFG_SET_RESERVED_BITWIDTH      25
// mem_cfg_clr Register
#define NANDC_MEM_CFG_CLR_OFS                    0x0000000C
// int_disable0 bitfiled (RW) Reset=0
#define NANDC_MEM_CFG_CLR_INT_DISABLE0_MASK      0x1
#define NANDC_MEM_CFG_CLR_INT_DISABLE0_SHIFT     0 
#define NANDC_MEM_CFG_CLR_INT_DISABLE0_BIT       0x1
#define NANDC_MEM_CFG_CLR_INT_DISABLE0_BITWIDTH  1
// int_disable1 bitfiled (RW) Reset=0
#define NANDC_MEM_CFG_CLR_INT_DISABLE1_MASK      0x2
#define NANDC_MEM_CFG_CLR_INT_DISABLE1_SHIFT     1 
#define NANDC_MEM_CFG_CLR_INT_DISABLE1_BIT       0x1
#define NANDC_MEM_CFG_CLR_INT_DISABLE1_BITWIDTH  1
// low_power_exit bitfiled (RW) Reset=0
#define NANDC_MEM_CFG_CLR_LOW_POWER_EXIT_MASK    0x4
#define NANDC_MEM_CFG_CLR_LOW_POWER_EXIT_SHIFT   2 
#define NANDC_MEM_CFG_CLR_LOW_POWER_EXIT_BIT     0x1
#define NANDC_MEM_CFG_CLR_LOW_POWER_EXIT_BITWIDTH 1
// int_clear0 bitfiled (RW) Reset=0
#define NANDC_MEM_CFG_CLR_INT_CLEAR0_MASK        0x8
#define NANDC_MEM_CFG_CLR_INT_CLEAR0_SHIFT       3 
#define NANDC_MEM_CFG_CLR_INT_CLEAR0_BIT         0x1
#define NANDC_MEM_CFG_CLR_INT_CLEAR0_BITWIDTH    1
// int_clear1 bitfiled (RW) Reset=0
#define NANDC_MEM_CFG_CLR_INT_CLEAR1_MASK        0x10
#define NANDC_MEM_CFG_CLR_INT_CLEAR1_SHIFT       4 
#define NANDC_MEM_CFG_CLR_INT_CLEAR1_BIT         0x1
#define NANDC_MEM_CFG_CLR_INT_CLEAR1_BITWIDTH    1
// ecc_int_disable0 bitfiled (RW) Reset=0
#define NANDC_MEM_CFG_CLR_ECC_INT_DISABLE0_MASK  0x20
#define NANDC_MEM_CFG_CLR_ECC_INT_DISABLE0_SHIFT 5 
#define NANDC_MEM_CFG_CLR_ECC_INT_DISABLE0_BIT   0x1
#define NANDC_MEM_CFG_CLR_ECC_INT_DISABLE0_BITWIDTH 1
// ecc_int_disable1 bitfiled (RW) Reset=0
#define NANDC_MEM_CFG_CLR_ECC_INT_DISABLE1_MASK  0x40
#define NANDC_MEM_CFG_CLR_ECC_INT_DISABLE1_SHIFT 6 
#define NANDC_MEM_CFG_CLR_ECC_INT_DISABLE1_BIT   0x1
#define NANDC_MEM_CFG_CLR_ECC_INT_DISABLE1_BITWIDTH 1
// reserved bitfiled (RO) Reset=0
#define NANDC_MEM_CFG_CLR_RESERVED_MASK          0xFFFFFF80
#define NANDC_MEM_CFG_CLR_RESERVED_SHIFT         7 
#define NANDC_MEM_CFG_CLR_RESERVED_BIT           0x1FFFFFF
#define NANDC_MEM_CFG_CLR_RESERVED_BITWIDTH      25
// direct_cmd Register
#define NANDC_DIRECT_CMD_OFS                     0x00000010
// addr_19_to_0 bitfiled (RW) Reset=0
#define NANDC_DIRECT_CMD_ADDR_19_TO_0_MASK       0xFFFFF
#define NANDC_DIRECT_CMD_ADDR_19_TO_0_SHIFT      0 
#define NANDC_DIRECT_CMD_ADDR_19_TO_0_BIT        0xFFFFF
#define NANDC_DIRECT_CMD_ADDR_19_TO_0_BITWIDTH   20
// set_cre bitfiled (RW) Reset=0
#define NANDC_DIRECT_CMD_SET_CRE_MASK            0x100000
#define NANDC_DIRECT_CMD_SET_CRE_SHIFT           20 
#define NANDC_DIRECT_CMD_SET_CRE_BIT             0x1
#define NANDC_DIRECT_CMD_SET_CRE_BITWIDTH        1
// cmd_type bitfiled (RW) Reset=0
#define NANDC_DIRECT_CMD_CMD_TYPE_MASK           0x600000
#define NANDC_DIRECT_CMD_CMD_TYPE_SHIFT          21 
#define NANDC_DIRECT_CMD_CMD_TYPE_BIT            0x3
#define NANDC_DIRECT_CMD_CMD_TYPE_BITWIDTH       2
// chip_nmbr bitfiled (RW) Reset=0
#define NANDC_DIRECT_CMD_CHIP_NMBR_MASK          0x3800000
#define NANDC_DIRECT_CMD_CHIP_NMBR_SHIFT         23 
#define NANDC_DIRECT_CMD_CHIP_NMBR_BIT           0x7
#define NANDC_DIRECT_CMD_CHIP_NMBR_BITWIDTH      3
// reserved bitfiled (RO) Reset=0
#define NANDC_DIRECT_CMD_RESERVED_MASK           0xFC000000
#define NANDC_DIRECT_CMD_RESERVED_SHIFT          26 
#define NANDC_DIRECT_CMD_RESERVED_BIT            0x3F
#define NANDC_DIRECT_CMD_RESERVED_BITWIDTH       6
// set_cycles Register
#define NANDC_SET_CYCLES_OFS                     0x00000014
// set_t0 bitfiled (RW) Reset=0
#define NANDC_SET_CYCLES_SET_T0_MASK             0xF
#define NANDC_SET_CYCLES_SET_T0_SHIFT            0 
#define NANDC_SET_CYCLES_SET_T0_BIT              0xF
#define NANDC_SET_CYCLES_SET_T0_BITWIDTH         4
// set_t1 bitfiled (RW) Reset=0
#define NANDC_SET_CYCLES_SET_T1_MASK             0xF0
#define NANDC_SET_CYCLES_SET_T1_SHIFT            4 
#define NANDC_SET_CYCLES_SET_T1_BIT              0xF
#define NANDC_SET_CYCLES_SET_T1_BITWIDTH         4
// set_t2 bitfiled (RW) Reset=0
#define NANDC_SET_CYCLES_SET_T2_MASK             0x700
#define NANDC_SET_CYCLES_SET_T2_SHIFT            8 
#define NANDC_SET_CYCLES_SET_T2_BIT              0x7
#define NANDC_SET_CYCLES_SET_T2_BITWIDTH         3
// set_t3 bitfiled (RW) Reset=0
#define NANDC_SET_CYCLES_SET_T3_MASK             0x3800
#define NANDC_SET_CYCLES_SET_T3_SHIFT            11 
#define NANDC_SET_CYCLES_SET_T3_BIT              0x7
#define NANDC_SET_CYCLES_SET_T3_BITWIDTH         3
// set_t4 bitfiled (RW) Reset=0
#define NANDC_SET_CYCLES_SET_T4_MASK             0x1C000
#define NANDC_SET_CYCLES_SET_T4_SHIFT            14 
#define NANDC_SET_CYCLES_SET_T4_BIT              0x7
#define NANDC_SET_CYCLES_SET_T4_BITWIDTH         3
// set_t5 bitfiled (RW) Reset=0
#define NANDC_SET_CYCLES_SET_T5_MASK             0xE0000
#define NANDC_SET_CYCLES_SET_T5_SHIFT            17 
#define NANDC_SET_CYCLES_SET_T5_BIT              0x7
#define NANDC_SET_CYCLES_SET_T5_BITWIDTH         3
// set_t6 bitfiled (RW) Reset=0
#define NANDC_SET_CYCLES_SET_T6_MASK             0xF00000
#define NANDC_SET_CYCLES_SET_T6_SHIFT            20 
#define NANDC_SET_CYCLES_SET_T6_BIT              0xF
#define NANDC_SET_CYCLES_SET_T6_BITWIDTH         4
// reserved bitfiled (RO) Reset=0
#define NANDC_SET_CYCLES_RESERVED_MASK           0xFF000000
#define NANDC_SET_CYCLES_RESERVED_SHIFT          24 
#define NANDC_SET_CYCLES_RESERVED_BIT            0xFF
#define NANDC_SET_CYCLES_RESERVED_BITWIDTH       8
// set_opmode Register
#define NANDC_SET_OPMODE_OFS                     0x00000018
// set_mw bitfiled (RW) Reset=0
#define NANDC_SET_OPMODE_SET_MW_MASK             0x3
#define NANDC_SET_OPMODE_SET_MW_SHIFT            0 
#define NANDC_SET_OPMODE_SET_MW_BIT              0x3
#define NANDC_SET_OPMODE_SET_MW_BITWIDTH         2
// set_rd_sync bitfiled (RW) Reset=0
#define NANDC_SET_OPMODE_SET_RD_SYNC_MASK        0x4
#define NANDC_SET_OPMODE_SET_RD_SYNC_SHIFT       2 
#define NANDC_SET_OPMODE_SET_RD_SYNC_BIT         0x1
#define NANDC_SET_OPMODE_SET_RD_SYNC_BITWIDTH    1
// set_rd_bl bitfiled (RW) Reset=0
#define NANDC_SET_OPMODE_SET_RD_BL_MASK          0x38
#define NANDC_SET_OPMODE_SET_RD_BL_SHIFT         3 
#define NANDC_SET_OPMODE_SET_RD_BL_BIT           0x7
#define NANDC_SET_OPMODE_SET_RD_BL_BITWIDTH      3
// set_wr_sync bitfiled (RW) Reset=0
#define NANDC_SET_OPMODE_SET_WR_SYNC_MASK        0x40
#define NANDC_SET_OPMODE_SET_WR_SYNC_SHIFT       6 
#define NANDC_SET_OPMODE_SET_WR_SYNC_BIT         0x1
#define NANDC_SET_OPMODE_SET_WR_SYNC_BITWIDTH    1
// set_wr_bl bitfiled (RW) Reset=0
#define NANDC_SET_OPMODE_SET_WR_BL_MASK          0x380
#define NANDC_SET_OPMODE_SET_WR_BL_SHIFT         7 
#define NANDC_SET_OPMODE_SET_WR_BL_BIT           0x7
#define NANDC_SET_OPMODE_SET_WR_BL_BITWIDTH      3
// set_baa bitfiled (RW) Reset=0
#define NANDC_SET_OPMODE_SET_BAA_MASK            0x400
#define NANDC_SET_OPMODE_SET_BAA_SHIFT           10 
#define NANDC_SET_OPMODE_SET_BAA_BIT             0x1
#define NANDC_SET_OPMODE_SET_BAA_BITWIDTH        1
// set_adv bitfiled (RW) Reset=0
#define NANDC_SET_OPMODE_SET_ADV_MASK            0x800
#define NANDC_SET_OPMODE_SET_ADV_SHIFT           11 
#define NANDC_SET_OPMODE_SET_ADV_BIT             0x1
#define NANDC_SET_OPMODE_SET_ADV_BITWIDTH        1
// set_bls_time bitfiled (RW) Reset=0
#define NANDC_SET_OPMODE_SET_BLS_TIME_MASK       0x1000
#define NANDC_SET_OPMODE_SET_BLS_TIME_SHIFT      12 
#define NANDC_SET_OPMODE_SET_BLS_TIME_BIT        0x1
#define NANDC_SET_OPMODE_SET_BLS_TIME_BITWIDTH   1
// set_burst_align bitfiled (RW) Reset=0
#define NANDC_SET_OPMODE_SET_BURST_ALIGN_MASK    0xE000
#define NANDC_SET_OPMODE_SET_BURST_ALIGN_SHIFT   13 
#define NANDC_SET_OPMODE_SET_BURST_ALIGN_BIT     0x7
#define NANDC_SET_OPMODE_SET_BURST_ALIGN_BITWIDTH 3
// reserved bitfiled (RO) Reset=0
#define NANDC_SET_OPMODE_RESERVED_MASK           0xFFFF0000
#define NANDC_SET_OPMODE_RESERVED_SHIFT          16 
#define NANDC_SET_OPMODE_RESERVED_BIT            0xFFFF
#define NANDC_SET_OPMODE_RESERVED_BITWIDTH       16
// refresh_0 Register
#define NANDC_REFRESH_0_OFS                      0x00000020
// ref_period0 bitfiled (RW) Reset=0
#define NANDC_REFRESH_0_REF_PERIOD0_MASK         0xF
#define NANDC_REFRESH_0_REF_PERIOD0_SHIFT        0 
#define NANDC_REFRESH_0_REF_PERIOD0_BIT          0xF
#define NANDC_REFRESH_0_REF_PERIOD0_BITWIDTH     4
// reserved bitfiled (RO) Reset=0
#define NANDC_REFRESH_0_RESERVED_MASK            0xFFFFFFF0
#define NANDC_REFRESH_0_RESERVED_SHIFT           4 
#define NANDC_REFRESH_0_RESERVED_BIT             0xFFFFFFF
#define NANDC_REFRESH_0_RESERVED_BITWIDTH        28
// refresh_1 Register
#define NANDC_REFRESH_1_OFS                      0x00000024
// ref_period1 bitfiled (RW) Reset=0
#define NANDC_REFRESH_1_REF_PERIOD1_MASK         0xF
#define NANDC_REFRESH_1_REF_PERIOD1_SHIFT        0 
#define NANDC_REFRESH_1_REF_PERIOD1_BIT          0xF
#define NANDC_REFRESH_1_REF_PERIOD1_BITWIDTH     4
// reserved bitfiled (RO) Reset=0
#define NANDC_REFRESH_1_RESERVED_MASK            0xFFFFFFF0
#define NANDC_REFRESH_1_RESERVED_SHIFT           4 
#define NANDC_REFRESH_1_RESERVED_BIT             0xFFFFFFF
#define NANDC_REFRESH_1_RESERVED_BITWIDTH        28
// nand_cycles0_0 Register
#define NANDC_NAND_CYCLES0_0_OFS                 0x00000100
// t_rc0 bitfiled (RO) Reset=1100
#define NANDC_NAND_CYCLES0_0_T_RC0_MASK          0xF
#define NANDC_NAND_CYCLES0_0_T_RC0_SHIFT         0 
#define NANDC_NAND_CYCLES0_0_T_RC0_BIT           0xF
#define NANDC_NAND_CYCLES0_0_T_RC0_BITWIDTH      4
// t_wc0 bitfiled (RO) Reset=1100
#define NANDC_NAND_CYCLES0_0_T_WC0_MASK          0xF0
#define NANDC_NAND_CYCLES0_0_T_WC0_SHIFT         4 
#define NANDC_NAND_CYCLES0_0_T_WC0_BIT           0xF
#define NANDC_NAND_CYCLES0_0_T_WC0_BITWIDTH      4
// t_rea0 bitfiled (RO) Reset=11
#define NANDC_NAND_CYCLES0_0_T_REA0_MASK         0x700
#define NANDC_NAND_CYCLES0_0_T_REA0_SHIFT        8 
#define NANDC_NAND_CYCLES0_0_T_REA0_BIT          0x7
#define NANDC_NAND_CYCLES0_0_T_REA0_BITWIDTH     3
// t_wp0 bitfiled (RO) Reset=101
#define NANDC_NAND_CYCLES0_0_T_WP0_MASK          0x3800
#define NANDC_NAND_CYCLES0_0_T_WP0_SHIFT         11 
#define NANDC_NAND_CYCLES0_0_T_WP0_BIT           0x7
#define NANDC_NAND_CYCLES0_0_T_WP0_BITWIDTH      3
// t_clr0 bitfiled (RO) Reset=10
#define NANDC_NAND_CYCLES0_0_T_CLR0_MASK         0x1C000
#define NANDC_NAND_CYCLES0_0_T_CLR0_SHIFT        14 
#define NANDC_NAND_CYCLES0_0_T_CLR0_BIT          0x7
#define NANDC_NAND_CYCLES0_0_T_CLR0_BITWIDTH     3
// t_ar0 bitfiled (RO) Reset=10
#define NANDC_NAND_CYCLES0_0_T_AR0_MASK          0xE0000
#define NANDC_NAND_CYCLES0_0_T_AR0_SHIFT         17 
#define NANDC_NAND_CYCLES0_0_T_AR0_BIT           0x7
#define NANDC_NAND_CYCLES0_0_T_AR0_BITWIDTH      3
// t_rr0 bitfiled (RO) Reset=1
#define NANDC_NAND_CYCLES0_0_T_RR0_MASK          0xF00000
#define NANDC_NAND_CYCLES0_0_T_RR0_SHIFT         20 
#define NANDC_NAND_CYCLES0_0_T_RR0_BIT           0xF
#define NANDC_NAND_CYCLES0_0_T_RR0_BITWIDTH      4
// reserved bitfiled (RO) Reset=0
#define NANDC_NAND_CYCLES0_0_RESERVED_MASK       0xFF000000
#define NANDC_NAND_CYCLES0_0_RESERVED_SHIFT      24 
#define NANDC_NAND_CYCLES0_0_RESERVED_BIT        0xFF
#define NANDC_NAND_CYCLES0_0_RESERVED_BITWIDTH   8
// opmode0_0 Register
#define NANDC_OPMODE0_0_OFS                      0x00000104
// mw0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_0_MW0_MASK                 0x3
#define NANDC_OPMODE0_0_MW0_SHIFT                0 
#define NANDC_OPMODE0_0_MW0_BIT                  0x3
#define NANDC_OPMODE0_0_MW0_BITWIDTH             2
// rd_sync0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_0_RD_SYNC0_MASK            0x4
#define NANDC_OPMODE0_0_RD_SYNC0_SHIFT           2 
#define NANDC_OPMODE0_0_RD_SYNC0_BIT             0x1
#define NANDC_OPMODE0_0_RD_SYNC0_BITWIDTH        1
// rd_bl0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_0_RD_BL0_MASK              0x38
#define NANDC_OPMODE0_0_RD_BL0_SHIFT             3 
#define NANDC_OPMODE0_0_RD_BL0_BIT               0x7
#define NANDC_OPMODE0_0_RD_BL0_BITWIDTH          3
// wr_sync0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_0_WR_SYNC0_MASK            0x40
#define NANDC_OPMODE0_0_WR_SYNC0_SHIFT           6 
#define NANDC_OPMODE0_0_WR_SYNC0_BIT             0x1
#define NANDC_OPMODE0_0_WR_SYNC0_BITWIDTH        1
// wr_bl0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_0_WR_BL0_MASK              0x380
#define NANDC_OPMODE0_0_WR_BL0_SHIFT             7 
#define NANDC_OPMODE0_0_WR_BL0_BIT               0x7
#define NANDC_OPMODE0_0_WR_BL0_BITWIDTH          3
// baa0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_0_BAA0_MASK                0x400
#define NANDC_OPMODE0_0_BAA0_SHIFT               10 
#define NANDC_OPMODE0_0_BAA0_BIT                 0x1
#define NANDC_OPMODE0_0_BAA0_BITWIDTH            1
// adv0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_0_ADV0_MASK                0x800
#define NANDC_OPMODE0_0_ADV0_SHIFT               11 
#define NANDC_OPMODE0_0_ADV0_BIT                 0x1
#define NANDC_OPMODE0_0_ADV0_BITWIDTH            1
// bls_time0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_0_BLS_TIME0_MASK           0x1000
#define NANDC_OPMODE0_0_BLS_TIME0_SHIFT          12 
#define NANDC_OPMODE0_0_BLS_TIME0_BIT            0x1
#define NANDC_OPMODE0_0_BLS_TIME0_BITWIDTH       1
// burst_align0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_0_BURST_ALIGN0_MASK        0xE000
#define NANDC_OPMODE0_0_BURST_ALIGN0_SHIFT       13 
#define NANDC_OPMODE0_0_BURST_ALIGN0_BIT         0x7
#define NANDC_OPMODE0_0_BURST_ALIGN0_BITWIDTH    3
// addr_mask0 bitfiled (RO) Reset=11111111
#define NANDC_OPMODE0_0_ADDR_MASK0_MASK          0xFF0000
#define NANDC_OPMODE0_0_ADDR_MASK0_SHIFT         16 
#define NANDC_OPMODE0_0_ADDR_MASK0_BIT           0xFF
#define NANDC_OPMODE0_0_ADDR_MASK0_BITWIDTH      8
// addr_match0 bitfiled (RO) Reset=1010
#define NANDC_OPMODE0_0_ADDR_MATCH0_MASK         0xFF000000
#define NANDC_OPMODE0_0_ADDR_MATCH0_SHIFT        24 
#define NANDC_OPMODE0_0_ADDR_MATCH0_BIT          0xFF
#define NANDC_OPMODE0_0_ADDR_MATCH0_BITWIDTH     8
// nand_cycles0_1 Register
#define NANDC_NAND_CYCLES0_1_OFS                 0x00000120
// t_rc0 bitfiled (RO) Reset=0
#define NANDC_NAND_CYCLES0_1_T_RC0_MASK          0xF
#define NANDC_NAND_CYCLES0_1_T_RC0_SHIFT         0 
#define NANDC_NAND_CYCLES0_1_T_RC0_BIT           0xF
#define NANDC_NAND_CYCLES0_1_T_RC0_BITWIDTH      4
// t_wc0 bitfiled (RO) Reset=0
#define NANDC_NAND_CYCLES0_1_T_WC0_MASK          0xF0
#define NANDC_NAND_CYCLES0_1_T_WC0_SHIFT         4 
#define NANDC_NAND_CYCLES0_1_T_WC0_BIT           0xF
#define NANDC_NAND_CYCLES0_1_T_WC0_BITWIDTH      4
// t_rea0 bitfiled (RO) Reset=0
#define NANDC_NAND_CYCLES0_1_T_REA0_MASK         0x700
#define NANDC_NAND_CYCLES0_1_T_REA0_SHIFT        8 
#define NANDC_NAND_CYCLES0_1_T_REA0_BIT          0x7
#define NANDC_NAND_CYCLES0_1_T_REA0_BITWIDTH     3
// t_wp0 bitfiled (RO) Reset=0
#define NANDC_NAND_CYCLES0_1_T_WP0_MASK          0x3800
#define NANDC_NAND_CYCLES0_1_T_WP0_SHIFT         11 
#define NANDC_NAND_CYCLES0_1_T_WP0_BIT           0x7
#define NANDC_NAND_CYCLES0_1_T_WP0_BITWIDTH      3
// t_clr0 bitfiled (RO) Reset=0
#define NANDC_NAND_CYCLES0_1_T_CLR0_MASK         0x1C000
#define NANDC_NAND_CYCLES0_1_T_CLR0_SHIFT        14 
#define NANDC_NAND_CYCLES0_1_T_CLR0_BIT          0x7
#define NANDC_NAND_CYCLES0_1_T_CLR0_BITWIDTH     3
// t_ar0 bitfiled (RO) Reset=0
#define NANDC_NAND_CYCLES0_1_T_AR0_MASK          0xE0000
#define NANDC_NAND_CYCLES0_1_T_AR0_SHIFT         17 
#define NANDC_NAND_CYCLES0_1_T_AR0_BIT           0x7
#define NANDC_NAND_CYCLES0_1_T_AR0_BITWIDTH      3
// t_rr0 bitfiled (RO) Reset=0
#define NANDC_NAND_CYCLES0_1_T_RR0_MASK          0xF00000
#define NANDC_NAND_CYCLES0_1_T_RR0_SHIFT         20 
#define NANDC_NAND_CYCLES0_1_T_RR0_BIT           0xF
#define NANDC_NAND_CYCLES0_1_T_RR0_BITWIDTH      4
// reserved bitfiled (RO) Reset=0
#define NANDC_NAND_CYCLES0_1_RESERVED_MASK       0xFF000000
#define NANDC_NAND_CYCLES0_1_RESERVED_SHIFT      24 
#define NANDC_NAND_CYCLES0_1_RESERVED_BIT        0xFF
#define NANDC_NAND_CYCLES0_1_RESERVED_BITWIDTH   8
// opmode0_1 Register
#define NANDC_OPMODE0_1_OFS                      0x00000124
// mw0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_1_MW0_MASK                 0x3
#define NANDC_OPMODE0_1_MW0_SHIFT                0 
#define NANDC_OPMODE0_1_MW0_BIT                  0x3
#define NANDC_OPMODE0_1_MW0_BITWIDTH             2
// rd_sync0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_1_RD_SYNC0_MASK            0x4
#define NANDC_OPMODE0_1_RD_SYNC0_SHIFT           2 
#define NANDC_OPMODE0_1_RD_SYNC0_BIT             0x1
#define NANDC_OPMODE0_1_RD_SYNC0_BITWIDTH        1
// rd_bl0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_1_RD_BL0_MASK              0x38
#define NANDC_OPMODE0_1_RD_BL0_SHIFT             3 
#define NANDC_OPMODE0_1_RD_BL0_BIT               0x7
#define NANDC_OPMODE0_1_RD_BL0_BITWIDTH          3
// wr_sync0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_1_WR_SYNC0_MASK            0x40
#define NANDC_OPMODE0_1_WR_SYNC0_SHIFT           6 
#define NANDC_OPMODE0_1_WR_SYNC0_BIT             0x1
#define NANDC_OPMODE0_1_WR_SYNC0_BITWIDTH        1
// wr_bl0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_1_WR_BL0_MASK              0x380
#define NANDC_OPMODE0_1_WR_BL0_SHIFT             7 
#define NANDC_OPMODE0_1_WR_BL0_BIT               0x7
#define NANDC_OPMODE0_1_WR_BL0_BITWIDTH          3
// baa0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_1_BAA0_MASK                0x400
#define NANDC_OPMODE0_1_BAA0_SHIFT               10 
#define NANDC_OPMODE0_1_BAA0_BIT                 0x1
#define NANDC_OPMODE0_1_BAA0_BITWIDTH            1
// adv0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_1_ADV0_MASK                0x800
#define NANDC_OPMODE0_1_ADV0_SHIFT               11 
#define NANDC_OPMODE0_1_ADV0_BIT                 0x1
#define NANDC_OPMODE0_1_ADV0_BITWIDTH            1
// bls_time0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_1_BLS_TIME0_MASK           0x1000
#define NANDC_OPMODE0_1_BLS_TIME0_SHIFT          12 
#define NANDC_OPMODE0_1_BLS_TIME0_BIT            0x1
#define NANDC_OPMODE0_1_BLS_TIME0_BITWIDTH       1
// burst_align0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_1_BURST_ALIGN0_MASK        0xE000
#define NANDC_OPMODE0_1_BURST_ALIGN0_SHIFT       13 
#define NANDC_OPMODE0_1_BURST_ALIGN0_BIT         0x7
#define NANDC_OPMODE0_1_BURST_ALIGN0_BITWIDTH    3
// addr_mask0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_1_ADDR_MASK0_MASK          0xFF0000
#define NANDC_OPMODE0_1_ADDR_MASK0_SHIFT         16 
#define NANDC_OPMODE0_1_ADDR_MASK0_BIT           0xFF
#define NANDC_OPMODE0_1_ADDR_MASK0_BITWIDTH      8
// addr_match0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_1_ADDR_MATCH0_MASK         0xFF000000
#define NANDC_OPMODE0_1_ADDR_MATCH0_SHIFT        24 
#define NANDC_OPMODE0_1_ADDR_MATCH0_BIT          0xFF
#define NANDC_OPMODE0_1_ADDR_MATCH0_BITWIDTH     8
// nand_cycles0_2 Register
#define NANDC_NAND_CYCLES0_2_OFS                 0x00000140
// t_rc0 bitfiled (RO) Reset=0
#define NANDC_NAND_CYCLES0_2_T_RC0_MASK          0xF
#define NANDC_NAND_CYCLES0_2_T_RC0_SHIFT         0 
#define NANDC_NAND_CYCLES0_2_T_RC0_BIT           0xF
#define NANDC_NAND_CYCLES0_2_T_RC0_BITWIDTH      4
// t_wc0 bitfiled (RO) Reset=0
#define NANDC_NAND_CYCLES0_2_T_WC0_MASK          0xF0
#define NANDC_NAND_CYCLES0_2_T_WC0_SHIFT         4 
#define NANDC_NAND_CYCLES0_2_T_WC0_BIT           0xF
#define NANDC_NAND_CYCLES0_2_T_WC0_BITWIDTH      4
// t_rea0 bitfiled (RO) Reset=0
#define NANDC_NAND_CYCLES0_2_T_REA0_MASK         0x700
#define NANDC_NAND_CYCLES0_2_T_REA0_SHIFT        8 
#define NANDC_NAND_CYCLES0_2_T_REA0_BIT          0x7
#define NANDC_NAND_CYCLES0_2_T_REA0_BITWIDTH     3
// t_wp0 bitfiled (RO) Reset=0
#define NANDC_NAND_CYCLES0_2_T_WP0_MASK          0x3800
#define NANDC_NAND_CYCLES0_2_T_WP0_SHIFT         11 
#define NANDC_NAND_CYCLES0_2_T_WP0_BIT           0x7
#define NANDC_NAND_CYCLES0_2_T_WP0_BITWIDTH      3
// t_clr0 bitfiled (RO) Reset=0
#define NANDC_NAND_CYCLES0_2_T_CLR0_MASK         0x1C000
#define NANDC_NAND_CYCLES0_2_T_CLR0_SHIFT        14 
#define NANDC_NAND_CYCLES0_2_T_CLR0_BIT          0x7
#define NANDC_NAND_CYCLES0_2_T_CLR0_BITWIDTH     3
// t_ar0 bitfiled (RO) Reset=0
#define NANDC_NAND_CYCLES0_2_T_AR0_MASK          0xE0000
#define NANDC_NAND_CYCLES0_2_T_AR0_SHIFT         17 
#define NANDC_NAND_CYCLES0_2_T_AR0_BIT           0x7
#define NANDC_NAND_CYCLES0_2_T_AR0_BITWIDTH      3
// t_rr0 bitfiled (RO) Reset=0
#define NANDC_NAND_CYCLES0_2_T_RR0_MASK          0xF00000
#define NANDC_NAND_CYCLES0_2_T_RR0_SHIFT         20 
#define NANDC_NAND_CYCLES0_2_T_RR0_BIT           0xF
#define NANDC_NAND_CYCLES0_2_T_RR0_BITWIDTH      4
// reserved bitfiled (RO) Reset=0
#define NANDC_NAND_CYCLES0_2_RESERVED_MASK       0xFF000000
#define NANDC_NAND_CYCLES0_2_RESERVED_SHIFT      24 
#define NANDC_NAND_CYCLES0_2_RESERVED_BIT        0xFF
#define NANDC_NAND_CYCLES0_2_RESERVED_BITWIDTH   8
// opmode0_2 Register
#define NANDC_OPMODE0_2_OFS                      0x00000144
// mw0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_2_MW0_MASK                 0x3
#define NANDC_OPMODE0_2_MW0_SHIFT                0 
#define NANDC_OPMODE0_2_MW0_BIT                  0x3
#define NANDC_OPMODE0_2_MW0_BITWIDTH             2
// rd_sync0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_2_RD_SYNC0_MASK            0x4
#define NANDC_OPMODE0_2_RD_SYNC0_SHIFT           2 
#define NANDC_OPMODE0_2_RD_SYNC0_BIT             0x1
#define NANDC_OPMODE0_2_RD_SYNC0_BITWIDTH        1
// rd_bl0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_2_RD_BL0_MASK              0x38
#define NANDC_OPMODE0_2_RD_BL0_SHIFT             3 
#define NANDC_OPMODE0_2_RD_BL0_BIT               0x7
#define NANDC_OPMODE0_2_RD_BL0_BITWIDTH          3
// wr_sync0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_2_WR_SYNC0_MASK            0x40
#define NANDC_OPMODE0_2_WR_SYNC0_SHIFT           6 
#define NANDC_OPMODE0_2_WR_SYNC0_BIT             0x1
#define NANDC_OPMODE0_2_WR_SYNC0_BITWIDTH        1
// wr_bl0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_2_WR_BL0_MASK              0x380
#define NANDC_OPMODE0_2_WR_BL0_SHIFT             7 
#define NANDC_OPMODE0_2_WR_BL0_BIT               0x7
#define NANDC_OPMODE0_2_WR_BL0_BITWIDTH          3
// baa0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_2_BAA0_MASK                0x400
#define NANDC_OPMODE0_2_BAA0_SHIFT               10 
#define NANDC_OPMODE0_2_BAA0_BIT                 0x1
#define NANDC_OPMODE0_2_BAA0_BITWIDTH            1
// adv0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_2_ADV0_MASK                0x800
#define NANDC_OPMODE0_2_ADV0_SHIFT               11 
#define NANDC_OPMODE0_2_ADV0_BIT                 0x1
#define NANDC_OPMODE0_2_ADV0_BITWIDTH            1
// bls_time0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_2_BLS_TIME0_MASK           0x1000
#define NANDC_OPMODE0_2_BLS_TIME0_SHIFT          12 
#define NANDC_OPMODE0_2_BLS_TIME0_BIT            0x1
#define NANDC_OPMODE0_2_BLS_TIME0_BITWIDTH       1
// burst_align0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_2_BURST_ALIGN0_MASK        0xE000
#define NANDC_OPMODE0_2_BURST_ALIGN0_SHIFT       13 
#define NANDC_OPMODE0_2_BURST_ALIGN0_BIT         0x7
#define NANDC_OPMODE0_2_BURST_ALIGN0_BITWIDTH    3
// addr_mask0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_2_ADDR_MASK0_MASK          0xFF0000
#define NANDC_OPMODE0_2_ADDR_MASK0_SHIFT         16 
#define NANDC_OPMODE0_2_ADDR_MASK0_BIT           0xFF
#define NANDC_OPMODE0_2_ADDR_MASK0_BITWIDTH      8
// addr_match0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_2_ADDR_MATCH0_MASK         0xFF000000
#define NANDC_OPMODE0_2_ADDR_MATCH0_SHIFT        24 
#define NANDC_OPMODE0_2_ADDR_MATCH0_BIT          0xFF
#define NANDC_OPMODE0_2_ADDR_MATCH0_BITWIDTH     8
// nand_cycles0_3 Register
#define NANDC_NAND_CYCLES0_3_OFS                 0x00000160
// t_rc0 bitfiled (RO) Reset=0
#define NANDC_NAND_CYCLES0_3_T_RC0_MASK          0xF
#define NANDC_NAND_CYCLES0_3_T_RC0_SHIFT         0 
#define NANDC_NAND_CYCLES0_3_T_RC0_BIT           0xF
#define NANDC_NAND_CYCLES0_3_T_RC0_BITWIDTH      4
// t_wc0 bitfiled (RO) Reset=0
#define NANDC_NAND_CYCLES0_3_T_WC0_MASK          0xF0
#define NANDC_NAND_CYCLES0_3_T_WC0_SHIFT         4 
#define NANDC_NAND_CYCLES0_3_T_WC0_BIT           0xF
#define NANDC_NAND_CYCLES0_3_T_WC0_BITWIDTH      4
// t_rea0 bitfiled (RO) Reset=0
#define NANDC_NAND_CYCLES0_3_T_REA0_MASK         0x700
#define NANDC_NAND_CYCLES0_3_T_REA0_SHIFT        8 
#define NANDC_NAND_CYCLES0_3_T_REA0_BIT          0x7
#define NANDC_NAND_CYCLES0_3_T_REA0_BITWIDTH     3
// t_wp0 bitfiled (RO) Reset=0
#define NANDC_NAND_CYCLES0_3_T_WP0_MASK          0x3800
#define NANDC_NAND_CYCLES0_3_T_WP0_SHIFT         11 
#define NANDC_NAND_CYCLES0_3_T_WP0_BIT           0x7
#define NANDC_NAND_CYCLES0_3_T_WP0_BITWIDTH      3
// t_clr0 bitfiled (RO) Reset=0
#define NANDC_NAND_CYCLES0_3_T_CLR0_MASK         0x1C000
#define NANDC_NAND_CYCLES0_3_T_CLR0_SHIFT        14 
#define NANDC_NAND_CYCLES0_3_T_CLR0_BIT          0x7
#define NANDC_NAND_CYCLES0_3_T_CLR0_BITWIDTH     3
// t_ar0 bitfiled (RO) Reset=0
#define NANDC_NAND_CYCLES0_3_T_AR0_MASK          0xE0000
#define NANDC_NAND_CYCLES0_3_T_AR0_SHIFT         17 
#define NANDC_NAND_CYCLES0_3_T_AR0_BIT           0x7
#define NANDC_NAND_CYCLES0_3_T_AR0_BITWIDTH      3
// t_rr0 bitfiled (RO) Reset=0
#define NANDC_NAND_CYCLES0_3_T_RR0_MASK          0xF00000
#define NANDC_NAND_CYCLES0_3_T_RR0_SHIFT         20 
#define NANDC_NAND_CYCLES0_3_T_RR0_BIT           0xF
#define NANDC_NAND_CYCLES0_3_T_RR0_BITWIDTH      4
// reserved bitfiled (RO) Reset=0
#define NANDC_NAND_CYCLES0_3_RESERVED_MASK       0xFF000000
#define NANDC_NAND_CYCLES0_3_RESERVED_SHIFT      24 
#define NANDC_NAND_CYCLES0_3_RESERVED_BIT        0xFF
#define NANDC_NAND_CYCLES0_3_RESERVED_BITWIDTH   8
// opmode0_3 Register
#define NANDC_OPMODE0_3_OFS                      0x00000164
// mw0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_3_MW0_MASK                 0x3
#define NANDC_OPMODE0_3_MW0_SHIFT                0 
#define NANDC_OPMODE0_3_MW0_BIT                  0x3
#define NANDC_OPMODE0_3_MW0_BITWIDTH             2
// rd_sync0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_3_RD_SYNC0_MASK            0x4
#define NANDC_OPMODE0_3_RD_SYNC0_SHIFT           2 
#define NANDC_OPMODE0_3_RD_SYNC0_BIT             0x1
#define NANDC_OPMODE0_3_RD_SYNC0_BITWIDTH        1
// rd_bl0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_3_RD_BL0_MASK              0x38
#define NANDC_OPMODE0_3_RD_BL0_SHIFT             3 
#define NANDC_OPMODE0_3_RD_BL0_BIT               0x7
#define NANDC_OPMODE0_3_RD_BL0_BITWIDTH          3
// wr_sync0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_3_WR_SYNC0_MASK            0x40
#define NANDC_OPMODE0_3_WR_SYNC0_SHIFT           6 
#define NANDC_OPMODE0_3_WR_SYNC0_BIT             0x1
#define NANDC_OPMODE0_3_WR_SYNC0_BITWIDTH        1
// wr_bl0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_3_WR_BL0_MASK              0x380
#define NANDC_OPMODE0_3_WR_BL0_SHIFT             7 
#define NANDC_OPMODE0_3_WR_BL0_BIT               0x7
#define NANDC_OPMODE0_3_WR_BL0_BITWIDTH          3
// baa0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_3_BAA0_MASK                0x400
#define NANDC_OPMODE0_3_BAA0_SHIFT               10 
#define NANDC_OPMODE0_3_BAA0_BIT                 0x1
#define NANDC_OPMODE0_3_BAA0_BITWIDTH            1
// adv0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_3_ADV0_MASK                0x800
#define NANDC_OPMODE0_3_ADV0_SHIFT               11 
#define NANDC_OPMODE0_3_ADV0_BIT                 0x1
#define NANDC_OPMODE0_3_ADV0_BITWIDTH            1
// bls_time0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_3_BLS_TIME0_MASK           0x1000
#define NANDC_OPMODE0_3_BLS_TIME0_SHIFT          12 
#define NANDC_OPMODE0_3_BLS_TIME0_BIT            0x1
#define NANDC_OPMODE0_3_BLS_TIME0_BITWIDTH       1
// burst_align0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_3_BURST_ALIGN0_MASK        0xE000
#define NANDC_OPMODE0_3_BURST_ALIGN0_SHIFT       13 
#define NANDC_OPMODE0_3_BURST_ALIGN0_BIT         0x7
#define NANDC_OPMODE0_3_BURST_ALIGN0_BITWIDTH    3
// addr_mask0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_3_ADDR_MASK0_MASK          0xFF0000
#define NANDC_OPMODE0_3_ADDR_MASK0_SHIFT         16 
#define NANDC_OPMODE0_3_ADDR_MASK0_BIT           0xFF
#define NANDC_OPMODE0_3_ADDR_MASK0_BITWIDTH      8
// addr_match0 bitfiled (RO) Reset=0
#define NANDC_OPMODE0_3_ADDR_MATCH0_MASK         0xFF000000
#define NANDC_OPMODE0_3_ADDR_MATCH0_SHIFT        24 
#define NANDC_OPMODE0_3_ADDR_MATCH0_BIT          0xFF
#define NANDC_OPMODE0_3_ADDR_MATCH0_BITWIDTH     8
// user_status Register
#define NANDC_USER_STATUS_OFS                    0x00000200
// user_status bitfiled (RO) Reset=0
#define NANDC_USER_STATUS_USER_STATUS_MASK       0xFF
#define NANDC_USER_STATUS_USER_STATUS_SHIFT      0 
#define NANDC_USER_STATUS_USER_STATUS_BIT        0xFF
#define NANDC_USER_STATUS_USER_STATUS_BITWIDTH   8
// reserved bitfiled (RO) Reset=0
#define NANDC_USER_STATUS_RESERVED_MASK          0xFFFFFF00
#define NANDC_USER_STATUS_RESERVED_SHIFT         8 
#define NANDC_USER_STATUS_RESERVED_BIT           0xFFFFFF
#define NANDC_USER_STATUS_RESERVED_BITWIDTH      24
// user_config Register
#define NANDC_USER_CONFIG_OFS                    0x00000204
// user_config bitfiled (RW) Reset=0
#define NANDC_USER_CONFIG_USER_CONFIG_MASK       0xFF
#define NANDC_USER_CONFIG_USER_CONFIG_SHIFT      0 
#define NANDC_USER_CONFIG_USER_CONFIG_BIT        0xFF
#define NANDC_USER_CONFIG_USER_CONFIG_BITWIDTH   8
// reserved bitfiled (RO) Reset=0
#define NANDC_USER_CONFIG_RESERVED_MASK          0xFFFFFF00
#define NANDC_USER_CONFIG_RESERVED_SHIFT         8 
#define NANDC_USER_CONFIG_RESERVED_BIT           0xFFFFFF
#define NANDC_USER_CONFIG_RESERVED_BITWIDTH      24
// ecc0_status Register
#define NANDC_ECC0_STATUS_OFS                    0x00000300
// ecc_int_status bitfiled (RW) Reset=0
#define NANDC_ECC0_STATUS_ECC_INT_STATUS_MASK    0x3F
#define NANDC_ECC0_STATUS_ECC_INT_STATUS_SHIFT   0 
#define NANDC_ECC0_STATUS_ECC_INT_STATUS_BIT     0x3F
#define NANDC_ECC0_STATUS_ECC_INT_STATUS_BITWIDTH 6
// ecc_status bitfiled (RO) Reset=0
#define NANDC_ECC0_STATUS_ECC_STATUS_MASK        0x40
#define NANDC_ECC0_STATUS_ECC_STATUS_SHIFT       6 
#define NANDC_ECC0_STATUS_ECC_STATUS_BIT         0x1
#define NANDC_ECC0_STATUS_ECC_STATUS_BITWIDTH    1
// ecc_last_status bitfiled (RO) Reset=0
#define NANDC_ECC0_STATUS_ECC_LAST_STATUS_MASK   0x180
#define NANDC_ECC0_STATUS_ECC_LAST_STATUS_SHIFT  7 
#define NANDC_ECC0_STATUS_ECC_LAST_STATUS_BIT    0x3
#define NANDC_ECC0_STATUS_ECC_LAST_STATUS_BITWIDTH 2
// ecc_rd_n_wr bitfiled (RO) Reset=0
#define NANDC_ECC0_STATUS_ECC_RD_N_WR_MASK       0x200
#define NANDC_ECC0_STATUS_ECC_RD_N_WR_SHIFT      9 
#define NANDC_ECC0_STATUS_ECC_RD_N_WR_BIT        0x1
#define NANDC_ECC0_STATUS_ECC_RD_N_WR_BITWIDTH   1
// ecc_value_valid bitfiled (RO) Reset=0
#define NANDC_ECC0_STATUS_ECC_VALUE_VALID_MASK   0x7C00
#define NANDC_ECC0_STATUS_ECC_VALUE_VALID_SHIFT  10 
#define NANDC_ECC0_STATUS_ECC_VALUE_VALID_BIT    0x1F
#define NANDC_ECC0_STATUS_ECC_VALUE_VALID_BITWIDTH 5
// ecc_fail bitfiled (RO) Reset=0
#define NANDC_ECC0_STATUS_ECC_FAIL_MASK          0xF8000
#define NANDC_ECC0_STATUS_ECC_FAIL_SHIFT         15 
#define NANDC_ECC0_STATUS_ECC_FAIL_BIT           0x1F
#define NANDC_ECC0_STATUS_ECC_FAIL_BITWIDTH      5
// ecc_can_correct bitfiled (RO) Reset=0
#define NANDC_ECC0_STATUS_ECC_CAN_CORRECT_MASK   0x1F00000
#define NANDC_ECC0_STATUS_ECC_CAN_CORRECT_SHIFT  20 
#define NANDC_ECC0_STATUS_ECC_CAN_CORRECT_BIT    0x1F
#define NANDC_ECC0_STATUS_ECC_CAN_CORRECT_BITWIDTH 5
// ecc_read bitfiled (RO) Reset=0
#define NANDC_ECC0_STATUS_ECC_READ_MASK          0x3E000000
#define NANDC_ECC0_STATUS_ECC_READ_SHIFT         25 
#define NANDC_ECC0_STATUS_ECC_READ_BIT           0x1F
#define NANDC_ECC0_STATUS_ECC_READ_BITWIDTH      5
// reserved bitfiled (RO) Reset=0
#define NANDC_ECC0_STATUS_RESERVED_MASK          0xC0000000
#define NANDC_ECC0_STATUS_RESERVED_SHIFT         30 
#define NANDC_ECC0_STATUS_RESERVED_BIT           0x3
#define NANDC_ECC0_STATUS_RESERVED_BITWIDTH      2
// ecc0_cfg Register
#define NANDC_ECC0_CFG_OFS                       0x00000304
// page_size bitfiled (RW) Reset=11
#define NANDC_ECC0_CFG_PAGE_SIZE_MASK            0x3
#define NANDC_ECC0_CFG_PAGE_SIZE_SHIFT           0 
#define NANDC_ECC0_CFG_PAGE_SIZE_BIT             0x3
#define NANDC_ECC0_CFG_PAGE_SIZE_BITWIDTH        2
// ecc_mode bitfiled (RW) Reset=0
#define NANDC_ECC0_CFG_ECC_MODE_MASK             0xC
#define NANDC_ECC0_CFG_ECC_MODE_SHIFT            2 
#define NANDC_ECC0_CFG_ECC_MODE_BIT              0x3
#define NANDC_ECC0_CFG_ECC_MODE_BITWIDTH         2
// ecc_read_end bitfiled (RW) Reset=0
#define NANDC_ECC0_CFG_ECC_READ_END_MASK         0x10
#define NANDC_ECC0_CFG_ECC_READ_END_SHIFT        4 
#define NANDC_ECC0_CFG_ECC_READ_END_BIT          0x1
#define NANDC_ECC0_CFG_ECC_READ_END_BITWIDTH     1
// ecc_jump bitfiled (RW) Reset=10
#define NANDC_ECC0_CFG_ECC_JUMP_MASK             0x60
#define NANDC_ECC0_CFG_ECC_JUMP_SHIFT            5 
#define NANDC_ECC0_CFG_ECC_JUMP_BIT              0x3
#define NANDC_ECC0_CFG_ECC_JUMP_BITWIDTH         2
// ecc_ignore_add_eight bitfiled (RW) Reset=0
#define NANDC_ECC0_CFG_ECC_IGNORE_ADD_EIGHT_MASK 0x80
#define NANDC_ECC0_CFG_ECC_IGNORE_ADD_EIGHT_SHIFT 7 
#define NANDC_ECC0_CFG_ECC_IGNORE_ADD_EIGHT_BIT  0x1
#define NANDC_ECC0_CFG_ECC_IGNORE_ADD_EIGHT_BITWIDTH 1
// ecc_int_pass bitfiled (RW) Reset=0
#define NANDC_ECC0_CFG_ECC_INT_PASS_MASK         0x100
#define NANDC_ECC0_CFG_ECC_INT_PASS_SHIFT        8 
#define NANDC_ECC0_CFG_ECC_INT_PASS_BIT          0x1
#define NANDC_ECC0_CFG_ECC_INT_PASS_BITWIDTH     1
// ecc_int_abort bitfiled (RW) Reset=0
#define NANDC_ECC0_CFG_ECC_INT_ABORT_MASK        0x200
#define NANDC_ECC0_CFG_ECC_INT_ABORT_SHIFT       9 
#define NANDC_ECC0_CFG_ECC_INT_ABORT_BIT         0x1
#define NANDC_ECC0_CFG_ECC_INT_ABORT_BITWIDTH    1
// ecc_extra_block bitfiled (RW) Reset=0
#define NANDC_ECC0_CFG_ECC_EXTRA_BLOCK_MASK      0x400
#define NANDC_ECC0_CFG_ECC_EXTRA_BLOCK_SHIFT     10 
#define NANDC_ECC0_CFG_ECC_EXTRA_BLOCK_BIT       0x1
#define NANDC_ECC0_CFG_ECC_EXTRA_BLOCK_BITWIDTH  1
// ecc_extra_block_size bitfiled (RW) Reset=0
#define NANDC_ECC0_CFG_ECC_EXTRA_BLOCK_SIZE_MASK 0x1800
#define NANDC_ECC0_CFG_ECC_EXTRA_BLOCK_SIZE_SHIFT 11 
#define NANDC_ECC0_CFG_ECC_EXTRA_BLOCK_SIZE_BIT  0x3
#define NANDC_ECC0_CFG_ECC_EXTRA_BLOCK_SIZE_BITWIDTH 2
// reserved bitfiled (RO) Reset=0
#define NANDC_ECC0_CFG_RESERVED_MASK             0xFFFFE000
#define NANDC_ECC0_CFG_RESERVED_SHIFT            13 
#define NANDC_ECC0_CFG_RESERVED_BIT              0x7FFFF
#define NANDC_ECC0_CFG_RESERVED_BITWIDTH         19
// ecc0_memcmd0 Register
#define NANDC_ECC0_MEMCMD0_OFS                   0x00000308
// nand0_wr_cmd bitfiled (RW) Reset=10000000
#define NANDC_ECC0_MEMCMD0_NAND0_WR_CMD_MASK     0xFF
#define NANDC_ECC0_MEMCMD0_NAND0_WR_CMD_SHIFT    0 
#define NANDC_ECC0_MEMCMD0_NAND0_WR_CMD_BIT      0xFF
#define NANDC_ECC0_MEMCMD0_NAND0_WR_CMD_BITWIDTH 8
// nand0_rd_cmd bitfiled (RW) Reset=0
#define NANDC_ECC0_MEMCMD0_NAND0_RD_CMD_MASK     0xFF00
#define NANDC_ECC0_MEMCMD0_NAND0_RD_CMD_SHIFT    8 
#define NANDC_ECC0_MEMCMD0_NAND0_RD_CMD_BIT      0xFF
#define NANDC_ECC0_MEMCMD0_NAND0_RD_CMD_BITWIDTH 8
// nand0_rd_end_cmd bitfiled (RW) Reset=110000
#define NANDC_ECC0_MEMCMD0_NAND0_RD_END_CMD_MASK 0xFF0000
#define NANDC_ECC0_MEMCMD0_NAND0_RD_END_CMD_SHIFT 16 
#define NANDC_ECC0_MEMCMD0_NAND0_RD_END_CMD_BIT  0xFF
#define NANDC_ECC0_MEMCMD0_NAND0_RD_END_CMD_BITWIDTH 8
// nand0_rd_end_cmd_v bitfiled (RW) Reset=1
#define NANDC_ECC0_MEMCMD0_NAND0_RD_END_CMD_V_MASK 0x1000000
#define NANDC_ECC0_MEMCMD0_NAND0_RD_END_CMD_V_SHIFT 24 
#define NANDC_ECC0_MEMCMD0_NAND0_RD_END_CMD_V_BIT 0x1
#define NANDC_ECC0_MEMCMD0_NAND0_RD_END_CMD_V_BITWIDTH 1
// reserved bitfiled (RO) Reset=0
#define NANDC_ECC0_MEMCMD0_RESERVED_MASK         0xFE000000
#define NANDC_ECC0_MEMCMD0_RESERVED_SHIFT        25 
#define NANDC_ECC0_MEMCMD0_RESERVED_BIT          0x7F
#define NANDC_ECC0_MEMCMD0_RESERVED_BITWIDTH     7
// ecc0_memcmd1 Register
#define NANDC_ECC0_MEMCMD1_OFS                   0x0000030C
// nand0_wr_col_change bitfiled (RW) Reset=10000101
#define NANDC_ECC0_MEMCMD1_NAND0_WR_COL_CHANGE_MASK 0xFF
#define NANDC_ECC0_MEMCMD1_NAND0_WR_COL_CHANGE_SHIFT 0 
#define NANDC_ECC0_MEMCMD1_NAND0_WR_COL_CHANGE_BIT 0xFF
#define NANDC_ECC0_MEMCMD1_NAND0_WR_COL_CHANGE_BITWIDTH 8
// nand0_rd_col_change bitfiled (RW) Reset=101
#define NANDC_ECC0_MEMCMD1_NAND0_RD_COL_CHANGE_MASK 0xFF00
#define NANDC_ECC0_MEMCMD1_NAND0_RD_COL_CHANGE_SHIFT 8 
#define NANDC_ECC0_MEMCMD1_NAND0_RD_COL_CHANGE_BIT 0xFF
#define NANDC_ECC0_MEMCMD1_NAND0_RD_COL_CHANGE_BITWIDTH 8
// nand0_rd_end_col_change bitfiled (RW) Reset=11100000
#define NANDC_ECC0_MEMCMD1_NAND0_RD_END_COL_CHANGE_MASK 0xFF0000
#define NANDC_ECC0_MEMCMD1_NAND0_RD_END_COL_CHANGE_SHIFT 16 
#define NANDC_ECC0_MEMCMD1_NAND0_RD_END_COL_CHANGE_BIT 0xFF
#define NANDC_ECC0_MEMCMD1_NAND0_RD_END_COL_CHANGE_BITWIDTH 8
// nand0_rd_end_col_change_v bitfiled (RW) Reset=1
#define NANDC_ECC0_MEMCMD1_NAND0_RD_END_COL_CHANGE_V_MASK 0x1000000
#define NANDC_ECC0_MEMCMD1_NAND0_RD_END_COL_CHANGE_V_SHIFT 24 
#define NANDC_ECC0_MEMCMD1_NAND0_RD_END_COL_CHANGE_V_BIT 0x1
#define NANDC_ECC0_MEMCMD1_NAND0_RD_END_COL_CHANGE_V_BITWIDTH 1
// reserved bitfiled (RO) Reset=0
#define NANDC_ECC0_MEMCMD1_RESERVED_MASK         0xFE000000
#define NANDC_ECC0_MEMCMD1_RESERVED_SHIFT        25 
#define NANDC_ECC0_MEMCMD1_RESERVED_BIT          0x7F
#define NANDC_ECC0_MEMCMD1_RESERVED_BITWIDTH     7
// ecc0_addr0 Register
#define NANDC_ECC0_ADDR0_OFS                     0x00000310
// ecc0_add_low bitfiled (RO) Reset=0
#define NANDC_ECC0_ADDR0_ECC0_ADD_LOW_MASK       0xFFFFFFFF
#define NANDC_ECC0_ADDR0_ECC0_ADD_LOW_SHIFT      0 
#define NANDC_ECC0_ADDR0_ECC0_ADD_LOW_BIT        0xFFFFFFFF
#define NANDC_ECC0_ADDR0_ECC0_ADD_LOW_BITWIDTH   32
// ecc0_addr1 Register
#define NANDC_ECC0_ADDR1_OFS                     0x00000314
// ecc0_add_high bitfiled (RO) Reset=0
#define NANDC_ECC0_ADDR1_ECC0_ADD_HIGH_MASK      0xFFFFFF
#define NANDC_ECC0_ADDR1_ECC0_ADD_HIGH_SHIFT     0 
#define NANDC_ECC0_ADDR1_ECC0_ADD_HIGH_BIT       0xFFFFFF
#define NANDC_ECC0_ADDR1_ECC0_ADD_HIGH_BITWIDTH  24
// reserved bitfiled (RO) Reset=0
#define NANDC_ECC0_ADDR1_RESERVED_MASK           0xFF000000
#define NANDC_ECC0_ADDR1_RESERVED_SHIFT          24 
#define NANDC_ECC0_ADDR1_RESERVED_BIT            0xFF
#define NANDC_ECC0_ADDR1_RESERVED_BITWIDTH       8
// ecc0_block0 Register
#define NANDC_ECC0_BLOCK0_OFS                    0x00000318
// ecc0_block0_val bitfiled (RO) Reset=0
#define NANDC_ECC0_BLOCK0_ECC0_BLOCK0_VAL_MASK   0xFFFFFF
#define NANDC_ECC0_BLOCK0_ECC0_BLOCK0_VAL_SHIFT  0 
#define NANDC_ECC0_BLOCK0_ECC0_BLOCK0_VAL_BIT    0xFFFFFF
#define NANDC_ECC0_BLOCK0_ECC0_BLOCK0_VAL_BITWIDTH 24
// reserved bitfiled (RO) Reset=0
#define NANDC_ECC0_BLOCK0_RESERVED_MASK          0x7000000
#define NANDC_ECC0_BLOCK0_RESERVED_SHIFT         24 
#define NANDC_ECC0_BLOCK0_RESERVED_BIT           0x7
#define NANDC_ECC0_BLOCK0_RESERVED_BITWIDTH      3
// ecc0_0_correct bitfiled (RO) Reset=0
#define NANDC_ECC0_BLOCK0_ECC0_0_CORRECT_MASK    0x8000000
#define NANDC_ECC0_BLOCK0_ECC0_0_CORRECT_SHIFT   27 
#define NANDC_ECC0_BLOCK0_ECC0_0_CORRECT_BIT     0x1
#define NANDC_ECC0_BLOCK0_ECC0_0_CORRECT_BITWIDTH 1
// ecc0_0_fail bitfiled (RO) Reset=0
#define NANDC_ECC0_BLOCK0_ECC0_0_FAIL_MASK       0x10000000
#define NANDC_ECC0_BLOCK0_ECC0_0_FAIL_SHIFT      28 
#define NANDC_ECC0_BLOCK0_ECC0_0_FAIL_BIT        0x1
#define NANDC_ECC0_BLOCK0_ECC0_0_FAIL_BITWIDTH   1
// ecc0_0_read bitfiled (RO) Reset=0
#define NANDC_ECC0_BLOCK0_ECC0_0_READ_MASK       0x20000000
#define NANDC_ECC0_BLOCK0_ECC0_0_READ_SHIFT      29 
#define NANDC_ECC0_BLOCK0_ECC0_0_READ_BIT        0x1
#define NANDC_ECC0_BLOCK0_ECC0_0_READ_BITWIDTH   1
// ecc0_0_valid bitfiled (RO) Reset=0
#define NANDC_ECC0_BLOCK0_ECC0_0_VALID_MASK      0x40000000
#define NANDC_ECC0_BLOCK0_ECC0_0_VALID_SHIFT     30 
#define NANDC_ECC0_BLOCK0_ECC0_0_VALID_BIT       0x1
#define NANDC_ECC0_BLOCK0_ECC0_0_VALID_BITWIDTH  1
// ecc0_0_int bitfiled (RW) Reset=0
#define NANDC_ECC0_BLOCK0_ECC0_0_INT_MASK        0x80000000
#define NANDC_ECC0_BLOCK0_ECC0_0_INT_SHIFT       31 
#define NANDC_ECC0_BLOCK0_ECC0_0_INT_BIT         0x1
#define NANDC_ECC0_BLOCK0_ECC0_0_INT_BITWIDTH    1
// ecc0_block1 Register
#define NANDC_ECC0_BLOCK1_OFS                    0x0000031C
// ecc0_block1_val bitfiled (RO) Reset=0
#define NANDC_ECC0_BLOCK1_ECC0_BLOCK1_VAL_MASK   0xFFFFFF
#define NANDC_ECC0_BLOCK1_ECC0_BLOCK1_VAL_SHIFT  0 
#define NANDC_ECC0_BLOCK1_ECC0_BLOCK1_VAL_BIT    0xFFFFFF
#define NANDC_ECC0_BLOCK1_ECC0_BLOCK1_VAL_BITWIDTH 24
// reserved bitfiled (RO) Reset=0
#define NANDC_ECC0_BLOCK1_RESERVED_MASK          0x7000000
#define NANDC_ECC0_BLOCK1_RESERVED_SHIFT         24 
#define NANDC_ECC0_BLOCK1_RESERVED_BIT           0x7
#define NANDC_ECC0_BLOCK1_RESERVED_BITWIDTH      3
// ecc0_1_correct bitfiled (RO) Reset=0
#define NANDC_ECC0_BLOCK1_ECC0_1_CORRECT_MASK    0x8000000
#define NANDC_ECC0_BLOCK1_ECC0_1_CORRECT_SHIFT   27 
#define NANDC_ECC0_BLOCK1_ECC0_1_CORRECT_BIT     0x1
#define NANDC_ECC0_BLOCK1_ECC0_1_CORRECT_BITWIDTH 1
// ecc0_1_fail bitfiled (RO) Reset=0
#define NANDC_ECC0_BLOCK1_ECC0_1_FAIL_MASK       0x10000000
#define NANDC_ECC0_BLOCK1_ECC0_1_FAIL_SHIFT      28 
#define NANDC_ECC0_BLOCK1_ECC0_1_FAIL_BIT        0x1
#define NANDC_ECC0_BLOCK1_ECC0_1_FAIL_BITWIDTH   1
// ecc0_1_read bitfiled (RO) Reset=0
#define NANDC_ECC0_BLOCK1_ECC0_1_READ_MASK       0x20000000
#define NANDC_ECC0_BLOCK1_ECC0_1_READ_SHIFT      29 
#define NANDC_ECC0_BLOCK1_ECC0_1_READ_BIT        0x1
#define NANDC_ECC0_BLOCK1_ECC0_1_READ_BITWIDTH   1
// ecc0_1_valid bitfiled (RO) Reset=0
#define NANDC_ECC0_BLOCK1_ECC0_1_VALID_MASK      0x40000000
#define NANDC_ECC0_BLOCK1_ECC0_1_VALID_SHIFT     30 
#define NANDC_ECC0_BLOCK1_ECC0_1_VALID_BIT       0x1
#define NANDC_ECC0_BLOCK1_ECC0_1_VALID_BITWIDTH  1
// ecc0_1_int bitfiled (RW) Reset=0
#define NANDC_ECC0_BLOCK1_ECC0_1_INT_MASK        0x80000000
#define NANDC_ECC0_BLOCK1_ECC0_1_INT_SHIFT       31 
#define NANDC_ECC0_BLOCK1_ECC0_1_INT_BIT         0x1
#define NANDC_ECC0_BLOCK1_ECC0_1_INT_BITWIDTH    1
// ecc0_block2 Register
#define NANDC_ECC0_BLOCK2_OFS                    0x00000320
// ecc0_block2_val bitfiled (RO) Reset=0
#define NANDC_ECC0_BLOCK2_ECC0_BLOCK2_VAL_MASK   0xFFFFFF
#define NANDC_ECC0_BLOCK2_ECC0_BLOCK2_VAL_SHIFT  0 
#define NANDC_ECC0_BLOCK2_ECC0_BLOCK2_VAL_BIT    0xFFFFFF
#define NANDC_ECC0_BLOCK2_ECC0_BLOCK2_VAL_BITWIDTH 24
// reserved bitfiled (RO) Reset=0
#define NANDC_ECC0_BLOCK2_RESERVED_MASK          0x7000000
#define NANDC_ECC0_BLOCK2_RESERVED_SHIFT         24 
#define NANDC_ECC0_BLOCK2_RESERVED_BIT           0x7
#define NANDC_ECC0_BLOCK2_RESERVED_BITWIDTH      3
// ecc0_2_correct bitfiled (RO) Reset=0
#define NANDC_ECC0_BLOCK2_ECC0_2_CORRECT_MASK    0x8000000
#define NANDC_ECC0_BLOCK2_ECC0_2_CORRECT_SHIFT   27 
#define NANDC_ECC0_BLOCK2_ECC0_2_CORRECT_BIT     0x1
#define NANDC_ECC0_BLOCK2_ECC0_2_CORRECT_BITWIDTH 1
// ecc0_2_fail bitfiled (RO) Reset=0
#define NANDC_ECC0_BLOCK2_ECC0_2_FAIL_MASK       0x10000000
#define NANDC_ECC0_BLOCK2_ECC0_2_FAIL_SHIFT      28 
#define NANDC_ECC0_BLOCK2_ECC0_2_FAIL_BIT        0x1
#define NANDC_ECC0_BLOCK2_ECC0_2_FAIL_BITWIDTH   1
// ecc0_2_read bitfiled (RO) Reset=0
#define NANDC_ECC0_BLOCK2_ECC0_2_READ_MASK       0x20000000
#define NANDC_ECC0_BLOCK2_ECC0_2_READ_SHIFT      29 
#define NANDC_ECC0_BLOCK2_ECC0_2_READ_BIT        0x1
#define NANDC_ECC0_BLOCK2_ECC0_2_READ_BITWIDTH   1
// ecc0_2_valid bitfiled (RO) Reset=0
#define NANDC_ECC0_BLOCK2_ECC0_2_VALID_MASK      0x40000000
#define NANDC_ECC0_BLOCK2_ECC0_2_VALID_SHIFT     30 
#define NANDC_ECC0_BLOCK2_ECC0_2_VALID_BIT       0x1
#define NANDC_ECC0_BLOCK2_ECC0_2_VALID_BITWIDTH  1
// ecc0_2_int bitfiled (RW) Reset=0
#define NANDC_ECC0_BLOCK2_ECC0_2_INT_MASK        0x80000000
#define NANDC_ECC0_BLOCK2_ECC0_2_INT_SHIFT       31 
#define NANDC_ECC0_BLOCK2_ECC0_2_INT_BIT         0x1
#define NANDC_ECC0_BLOCK2_ECC0_2_INT_BITWIDTH    1
// ecc0_block3 Register
#define NANDC_ECC0_BLOCK3_OFS                    0x00000324
// ecc0_block3_val bitfiled (RO) Reset=0
#define NANDC_ECC0_BLOCK3_ECC0_BLOCK3_VAL_MASK   0xFFFFFF
#define NANDC_ECC0_BLOCK3_ECC0_BLOCK3_VAL_SHIFT  0 
#define NANDC_ECC0_BLOCK3_ECC0_BLOCK3_VAL_BIT    0xFFFFFF
#define NANDC_ECC0_BLOCK3_ECC0_BLOCK3_VAL_BITWIDTH 24
// reserved bitfiled (RO) Reset=0
#define NANDC_ECC0_BLOCK3_RESERVED_MASK          0x7000000
#define NANDC_ECC0_BLOCK3_RESERVED_SHIFT         24 
#define NANDC_ECC0_BLOCK3_RESERVED_BIT           0x7
#define NANDC_ECC0_BLOCK3_RESERVED_BITWIDTH      3
// ecc0_3_correct bitfiled (RO) Reset=0
#define NANDC_ECC0_BLOCK3_ECC0_3_CORRECT_MASK    0x8000000
#define NANDC_ECC0_BLOCK3_ECC0_3_CORRECT_SHIFT   27 
#define NANDC_ECC0_BLOCK3_ECC0_3_CORRECT_BIT     0x1
#define NANDC_ECC0_BLOCK3_ECC0_3_CORRECT_BITWIDTH 1
// ecc0_3_fail bitfiled (RO) Reset=0
#define NANDC_ECC0_BLOCK3_ECC0_3_FAIL_MASK       0x10000000
#define NANDC_ECC0_BLOCK3_ECC0_3_FAIL_SHIFT      28 
#define NANDC_ECC0_BLOCK3_ECC0_3_FAIL_BIT        0x1
#define NANDC_ECC0_BLOCK3_ECC0_3_FAIL_BITWIDTH   1
// ecc0_3_read bitfiled (RO) Reset=0
#define NANDC_ECC0_BLOCK3_ECC0_3_READ_MASK       0x20000000
#define NANDC_ECC0_BLOCK3_ECC0_3_READ_SHIFT      29 
#define NANDC_ECC0_BLOCK3_ECC0_3_READ_BIT        0x1
#define NANDC_ECC0_BLOCK3_ECC0_3_READ_BITWIDTH   1
// ecc0_3_valid bitfiled (RO) Reset=0
#define NANDC_ECC0_BLOCK3_ECC0_3_VALID_MASK      0x40000000
#define NANDC_ECC0_BLOCK3_ECC0_3_VALID_SHIFT     30 
#define NANDC_ECC0_BLOCK3_ECC0_3_VALID_BIT       0x1
#define NANDC_ECC0_BLOCK3_ECC0_3_VALID_BITWIDTH  1
// ecc0_3_int bitfiled (RW) Reset=0
#define NANDC_ECC0_BLOCK3_ECC0_3_INT_MASK        0x80000000
#define NANDC_ECC0_BLOCK3_ECC0_3_INT_SHIFT       31 
#define NANDC_ECC0_BLOCK3_ECC0_3_INT_BIT         0x1
#define NANDC_ECC0_BLOCK3_ECC0_3_INT_BITWIDTH    1
// ecc0_extra_block Register
#define NANDC_ECC0_EXTRA_BLOCK_OFS               0x00000328
// ecc0_extra_val bitfiled (RO) Reset=0
#define NANDC_ECC0_EXTRA_BLOCK_ECC0_EXTRA_VAL_MASK 0xFFFFFF
#define NANDC_ECC0_EXTRA_BLOCK_ECC0_EXTRA_VAL_SHIFT 0 
#define NANDC_ECC0_EXTRA_BLOCK_ECC0_EXTRA_VAL_BIT 0xFFFFFF
#define NANDC_ECC0_EXTRA_BLOCK_ECC0_EXTRA_VAL_BITWIDTH 24
// reserved bitfiled (RO) Reset=0
#define NANDC_ECC0_EXTRA_BLOCK_RESERVED_MASK     0x7000000
#define NANDC_ECC0_EXTRA_BLOCK_RESERVED_SHIFT    24 
#define NANDC_ECC0_EXTRA_BLOCK_RESERVED_BIT      0x7
#define NANDC_ECC0_EXTRA_BLOCK_RESERVED_BITWIDTH 3
// ecc0_e_correct bitfiled (RO) Reset=0
#define NANDC_ECC0_EXTRA_BLOCK_ECC0_E_CORRECT_MASK 0x8000000
#define NANDC_ECC0_EXTRA_BLOCK_ECC0_E_CORRECT_SHIFT 27 
#define NANDC_ECC0_EXTRA_BLOCK_ECC0_E_CORRECT_BIT 0x1
#define NANDC_ECC0_EXTRA_BLOCK_ECC0_E_CORRECT_BITWIDTH 1
// ecc0_e_fail bitfiled (RO) Reset=0
#define NANDC_ECC0_EXTRA_BLOCK_ECC0_E_FAIL_MASK  0x10000000
#define NANDC_ECC0_EXTRA_BLOCK_ECC0_E_FAIL_SHIFT 28 
#define NANDC_ECC0_EXTRA_BLOCK_ECC0_E_FAIL_BIT   0x1
#define NANDC_ECC0_EXTRA_BLOCK_ECC0_E_FAIL_BITWIDTH 1
// ecc0_e_read bitfiled (RO) Reset=0
#define NANDC_ECC0_EXTRA_BLOCK_ECC0_E_READ_MASK  0x20000000
#define NANDC_ECC0_EXTRA_BLOCK_ECC0_E_READ_SHIFT 29 
#define NANDC_ECC0_EXTRA_BLOCK_ECC0_E_READ_BIT   0x1
#define NANDC_ECC0_EXTRA_BLOCK_ECC0_E_READ_BITWIDTH 1
// ecc0_e_valid bitfiled (RO) Reset=0
#define NANDC_ECC0_EXTRA_BLOCK_ECC0_E_VALID_MASK 0x40000000
#define NANDC_ECC0_EXTRA_BLOCK_ECC0_E_VALID_SHIFT 30 
#define NANDC_ECC0_EXTRA_BLOCK_ECC0_E_VALID_BIT  0x1
#define NANDC_ECC0_EXTRA_BLOCK_ECC0_E_VALID_BITWIDTH 1
// ecc0_e_int bitfiled (RW) Reset=0
#define NANDC_ECC0_EXTRA_BLOCK_ECC0_E_INT_MASK   0x80000000
#define NANDC_ECC0_EXTRA_BLOCK_ECC0_E_INT_SHIFT  31 
#define NANDC_ECC0_EXTRA_BLOCK_ECC0_E_INT_BIT    0x1
#define NANDC_ECC0_EXTRA_BLOCK_ECC0_E_INT_BITWIDTH 1
// int_cfg Register
#define NANDC_INT_CFG_OFS                        0x00000E00
// int_test_en bitfiled (RW) Reset=0
#define NANDC_INT_CFG_INT_TEST_EN_MASK           0x1
#define NANDC_INT_CFG_INT_TEST_EN_SHIFT          0 
#define NANDC_INT_CFG_INT_TEST_EN_BIT            0x1
#define NANDC_INT_CFG_INT_TEST_EN_BITWIDTH       1
// reserved bitfiled (RO) Reset=0
#define NANDC_INT_CFG_RESERVED_MASK              0xFFFFFFFE
#define NANDC_INT_CFG_RESERVED_SHIFT             1 
#define NANDC_INT_CFG_RESERVED_BIT               0x7FFFFFFF
#define NANDC_INT_CFG_RESERVED_BITWIDTH          31
// int_inputs Register
#define NANDC_INT_INPUTS_OFS                     0x00000E04
// csysreq bitfiled (RO) Reset=1
#define NANDC_INT_INPUTS_CSYSREQ_MASK            0x1
#define NANDC_INT_INPUTS_CSYSREQ_SHIFT           0 
#define NANDC_INT_INPUTS_CSYSREQ_BIT             0x1
#define NANDC_INT_INPUTS_CSYSREQ_BITWIDTH        1
// use_ebi bitfiled (RO) Reset=0
#define NANDC_INT_INPUTS_USE_EBI_MASK            0x2
#define NANDC_INT_INPUTS_USE_EBI_SHIFT           1 
#define NANDC_INT_INPUTS_USE_EBI_BIT             0x1
#define NANDC_INT_INPUTS_USE_EBI_BITWIDTH        1
// ebigrant0 bitfiled (RO) Reset=0
#define NANDC_INT_INPUTS_EBIGRANT0_MASK          0x4
#define NANDC_INT_INPUTS_EBIGRANT0_SHIFT         2 
#define NANDC_INT_INPUTS_EBIGRANT0_BIT           0x1
#define NANDC_INT_INPUTS_EBIGRANT0_BITWIDTH      1
// ebibackoff0 bitfiled (RO) Reset=0
#define NANDC_INT_INPUTS_EBIBACKOFF0_MASK        0x8
#define NANDC_INT_INPUTS_EBIBACKOFF0_SHIFT       3 
#define NANDC_INT_INPUTS_EBIBACKOFF0_BIT         0x1
#define NANDC_INT_INPUTS_EBIBACKOFF0_BITWIDTH    1
// async0 bitfiled (RO) Reset=1
#define NANDC_INT_INPUTS_ASYNC0_MASK             0x10
#define NANDC_INT_INPUTS_ASYNC0_SHIFT            4 
#define NANDC_INT_INPUTS_ASYNC0_BIT              0x1
#define NANDC_INT_INPUTS_ASYNC0_BITWIDTH         1
// msync0 bitfiled (RO) Reset=1
#define NANDC_INT_INPUTS_MSYNC0_MASK             0x20
#define NANDC_INT_INPUTS_MSYNC0_SHIFT            5 
#define NANDC_INT_INPUTS_MSYNC0_BIT              0x1
#define NANDC_INT_INPUTS_MSYNC0_BITWIDTH         1
// ebigrant1 bitfiled (RO) Reset=0
#define NANDC_INT_INPUTS_EBIGRANT1_MASK          0x40
#define NANDC_INT_INPUTS_EBIGRANT1_SHIFT         6 
#define NANDC_INT_INPUTS_EBIGRANT1_BIT           0x1
#define NANDC_INT_INPUTS_EBIGRANT1_BITWIDTH      1
// ebibackoff1 bitfiled (RO) Reset=0
#define NANDC_INT_INPUTS_EBIBACKOFF1_MASK        0x80
#define NANDC_INT_INPUTS_EBIBACKOFF1_SHIFT       7 
#define NANDC_INT_INPUTS_EBIBACKOFF1_BIT         0x1
#define NANDC_INT_INPUTS_EBIBACKOFF1_BITWIDTH    1
// async1 bitfiled (RO) Reset=0
#define NANDC_INT_INPUTS_ASYNC1_MASK             0x100
#define NANDC_INT_INPUTS_ASYNC1_SHIFT            8 
#define NANDC_INT_INPUTS_ASYNC1_BIT              0x1
#define NANDC_INT_INPUTS_ASYNC1_BITWIDTH         1
// msync1 bitfiled (RO) Reset=0
#define NANDC_INT_INPUTS_MSYNC1_MASK             0x200
#define NANDC_INT_INPUTS_MSYNC1_SHIFT            9 
#define NANDC_INT_INPUTS_MSYNC1_BIT              0x1
#define NANDC_INT_INPUTS_MSYNC1_BITWIDTH         1
// reserved bitfiled (RO) Reset=0
#define NANDC_INT_INPUTS_RESERVED_MASK           0xFFFFFC00
#define NANDC_INT_INPUTS_RESERVED_SHIFT          10 
#define NANDC_INT_INPUTS_RESERVED_BIT            0x3FFFFF
#define NANDC_INT_INPUTS_RESERVED_BITWIDTH       22
// int_outputs Register
#define NANDC_INT_OUTPUTS_OFS                    0x00000E08
// cactive_int bitfiled (RW) Reset=0
#define NANDC_INT_OUTPUTS_CACTIVE_INT_MASK       0x1
#define NANDC_INT_OUTPUTS_CACTIVE_INT_SHIFT      0 
#define NANDC_INT_OUTPUTS_CACTIVE_INT_BIT        0x1
#define NANDC_INT_OUTPUTS_CACTIVE_INT_BITWIDTH   1
// csysack_int bitfiled (RW) Reset=0
#define NANDC_INT_OUTPUTS_CSYSACK_INT_MASK       0x2
#define NANDC_INT_OUTPUTS_CSYSACK_INT_SHIFT      1 
#define NANDC_INT_OUTPUTS_CSYSACK_INT_BIT        0x1
#define NANDC_INT_OUTPUTS_CSYSACK_INT_BITWIDTH   1
// ebireq0_int bitfiled (RW) Reset=0
#define NANDC_INT_OUTPUTS_EBIREQ0_INT_MASK       0x4
#define NANDC_INT_OUTPUTS_EBIREQ0_INT_SHIFT      2 
#define NANDC_INT_OUTPUTS_EBIREQ0_INT_BIT        0x1
#define NANDC_INT_OUTPUTS_EBIREQ0_INT_BITWIDTH   1
// ebireq1_int bitfiled (RW) Reset=0
#define NANDC_INT_OUTPUTS_EBIREQ1_INT_MASK       0x8
#define NANDC_INT_OUTPUTS_EBIREQ1_INT_SHIFT      3 
#define NANDC_INT_OUTPUTS_EBIREQ1_INT_BIT        0x1
#define NANDC_INT_OUTPUTS_EBIREQ1_INT_BITWIDTH   1
// smc_int_int bitfiled (RW) Reset=0
#define NANDC_INT_OUTPUTS_SMC_INT_INT_MASK       0x10
#define NANDC_INT_OUTPUTS_SMC_INT_INT_SHIFT      4 
#define NANDC_INT_OUTPUTS_SMC_INT_INT_BIT        0x1
#define NANDC_INT_OUTPUTS_SMC_INT_INT_BITWIDTH   1
// smc_int0_int bitfiled (RW) Reset=0
#define NANDC_INT_OUTPUTS_SMC_INT0_INT_MASK      0x20
#define NANDC_INT_OUTPUTS_SMC_INT0_INT_SHIFT     5 
#define NANDC_INT_OUTPUTS_SMC_INT0_INT_BIT       0x1
#define NANDC_INT_OUTPUTS_SMC_INT0_INT_BITWIDTH  1
// smc_int1_int bitfiled (RW) Reset=0
#define NANDC_INT_OUTPUTS_SMC_INT1_INT_MASK      0x40
#define NANDC_INT_OUTPUTS_SMC_INT1_INT_SHIFT     6 
#define NANDC_INT_OUTPUTS_SMC_INT1_INT_BIT       0x1
#define NANDC_INT_OUTPUTS_SMC_INT1_INT_BITWIDTH  1
// ecc_int0_int bitfiled (RW) Reset=0
#define NANDC_INT_OUTPUTS_ECC_INT0_INT_MASK      0x80
#define NANDC_INT_OUTPUTS_ECC_INT0_INT_SHIFT     7 
#define NANDC_INT_OUTPUTS_ECC_INT0_INT_BIT       0x1
#define NANDC_INT_OUTPUTS_ECC_INT0_INT_BITWIDTH  1
// ecc_int1_int bitfiled (RW) Reset=0
#define NANDC_INT_OUTPUTS_ECC_INT1_INT_MASK      0x100
#define NANDC_INT_OUTPUTS_ECC_INT1_INT_SHIFT     8 
#define NANDC_INT_OUTPUTS_ECC_INT1_INT_BIT       0x1
#define NANDC_INT_OUTPUTS_ECC_INT1_INT_BITWIDTH  1
// reserved bitfiled (RO) Reset=0
#define NANDC_INT_OUTPUTS_RESERVED_MASK          0xFFFFFE00
#define NANDC_INT_OUTPUTS_RESERVED_SHIFT         9 
#define NANDC_INT_OUTPUTS_RESERVED_BIT           0x7FFFFF
#define NANDC_INT_OUTPUTS_RESERVED_BITWIDTH      23
// periph_id_0 Register
#define NANDC_PERIPH_ID_0_OFS                    0x00000FE0
// part_number_0 bitfiled (RO) Reset=1010001
#define NANDC_PERIPH_ID_0_PART_NUMBER_0_MASK     0xFF
#define NANDC_PERIPH_ID_0_PART_NUMBER_0_SHIFT    0 
#define NANDC_PERIPH_ID_0_PART_NUMBER_0_BIT      0xFF
#define NANDC_PERIPH_ID_0_PART_NUMBER_0_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define NANDC_PERIPH_ID_0_RESERVED_MASK          0xFFFFFF00
#define NANDC_PERIPH_ID_0_RESERVED_SHIFT         8 
#define NANDC_PERIPH_ID_0_RESERVED_BIT           0xFFFFFF
#define NANDC_PERIPH_ID_0_RESERVED_BITWIDTH      24
// periph_id_1 Register
#define NANDC_PERIPH_ID_1_OFS                    0x00000FE4
// part_number_1 bitfiled (RO) Reset=11
#define NANDC_PERIPH_ID_1_PART_NUMBER_1_MASK     0xF
#define NANDC_PERIPH_ID_1_PART_NUMBER_1_SHIFT    0 
#define NANDC_PERIPH_ID_1_PART_NUMBER_1_BIT      0xF
#define NANDC_PERIPH_ID_1_PART_NUMBER_1_BITWIDTH 4
// designer_0 bitfiled (RO) Reset=1
#define NANDC_PERIPH_ID_1_DESIGNER_0_MASK        0xF0
#define NANDC_PERIPH_ID_1_DESIGNER_0_SHIFT       4 
#define NANDC_PERIPH_ID_1_DESIGNER_0_BIT         0xF
#define NANDC_PERIPH_ID_1_DESIGNER_0_BITWIDTH    4
// reserved bitfiled (RO) Reset=0
#define NANDC_PERIPH_ID_1_RESERVED_MASK          0xFFFFFF00
#define NANDC_PERIPH_ID_1_RESERVED_SHIFT         8 
#define NANDC_PERIPH_ID_1_RESERVED_BIT           0xFFFFFF
#define NANDC_PERIPH_ID_1_RESERVED_BITWIDTH      24
// periph_id_2 Register
#define NANDC_PERIPH_ID_2_OFS                    0x00000FE8
// designer_1 bitfiled (RO) Reset=100
#define NANDC_PERIPH_ID_2_DESIGNER_1_MASK        0xF
#define NANDC_PERIPH_ID_2_DESIGNER_1_SHIFT       0 
#define NANDC_PERIPH_ID_2_DESIGNER_1_BIT         0xF
#define NANDC_PERIPH_ID_2_DESIGNER_1_BITWIDTH    4
// revision bitfiled (RO) Reset=110
#define NANDC_PERIPH_ID_2_REVISION_MASK          0xF0
#define NANDC_PERIPH_ID_2_REVISION_SHIFT         4 
#define NANDC_PERIPH_ID_2_REVISION_BIT           0xF
#define NANDC_PERIPH_ID_2_REVISION_BITWIDTH      4
// reserved bitfiled (RO) Reset=0
#define NANDC_PERIPH_ID_2_RESERVED_MASK          0xFFFFFF00
#define NANDC_PERIPH_ID_2_RESERVED_SHIFT         8 
#define NANDC_PERIPH_ID_2_RESERVED_BIT           0xFFFFFF
#define NANDC_PERIPH_ID_2_RESERVED_BITWIDTH      24
// periph_id_3 Register
#define NANDC_PERIPH_ID_3_OFS                    0x00000FEC
// reserved bitfiled (RO) Reset=0
#define NANDC_PERIPH_ID_3_RESERVED_MASK          0xFFFFFFFF
#define NANDC_PERIPH_ID_3_RESERVED_SHIFT         0 
#define NANDC_PERIPH_ID_3_RESERVED_BIT           0xFFFFFFFF
#define NANDC_PERIPH_ID_3_RESERVED_BITWIDTH      32
// pcell_id_0 Register
#define NANDC_PCELL_ID_0_OFS                     0x00000FF0
// pcell_id_0 bitfiled (RO) Reset=1101
#define NANDC_PCELL_ID_0_PCELL_ID_0_MASK         0xFF
#define NANDC_PCELL_ID_0_PCELL_ID_0_SHIFT        0 
#define NANDC_PCELL_ID_0_PCELL_ID_0_BIT          0xFF
#define NANDC_PCELL_ID_0_PCELL_ID_0_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define NANDC_PCELL_ID_0_RESERVED_MASK           0xFFFFFF00
#define NANDC_PCELL_ID_0_RESERVED_SHIFT          8 
#define NANDC_PCELL_ID_0_RESERVED_BIT            0xFFFFFF
#define NANDC_PCELL_ID_0_RESERVED_BITWIDTH       24
// pcell_id_1 Register
#define NANDC_PCELL_ID_1_OFS                     0x00000FF4
// pcell_id_1 bitfiled (RO) Reset=11110000
#define NANDC_PCELL_ID_1_PCELL_ID_1_MASK         0xFF
#define NANDC_PCELL_ID_1_PCELL_ID_1_SHIFT        0 
#define NANDC_PCELL_ID_1_PCELL_ID_1_BIT          0xFF
#define NANDC_PCELL_ID_1_PCELL_ID_1_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define NANDC_PCELL_ID_1_RESERVED_MASK           0xFFFFFF00
#define NANDC_PCELL_ID_1_RESERVED_SHIFT          8 
#define NANDC_PCELL_ID_1_RESERVED_BIT            0xFFFFFF
#define NANDC_PCELL_ID_1_RESERVED_BITWIDTH       24
// pcell_id_2 Register
#define NANDC_PCELL_ID_2_OFS                     0x00000FF8
// pcell_id_2 bitfiled (RO) Reset=101
#define NANDC_PCELL_ID_2_PCELL_ID_2_MASK         0xFF
#define NANDC_PCELL_ID_2_PCELL_ID_2_SHIFT        0 
#define NANDC_PCELL_ID_2_PCELL_ID_2_BIT          0xFF
#define NANDC_PCELL_ID_2_PCELL_ID_2_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define NANDC_PCELL_ID_2_RESERVED_MASK           0xFFFFFF00
#define NANDC_PCELL_ID_2_RESERVED_SHIFT          8 
#define NANDC_PCELL_ID_2_RESERVED_BIT            0xFFFFFF
#define NANDC_PCELL_ID_2_RESERVED_BITWIDTH       24
// pcell_id_3 Register
#define NANDC_PCELL_ID_3_OFS                     0x00000FFC
// pcell_id_3 bitfiled (RO) Reset=10110001
#define NANDC_PCELL_ID_3_PCELL_ID_3_MASK         0xFF
#define NANDC_PCELL_ID_3_PCELL_ID_3_SHIFT        0 
#define NANDC_PCELL_ID_3_PCELL_ID_3_BIT          0xFF
#define NANDC_PCELL_ID_3_PCELL_ID_3_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define NANDC_PCELL_ID_3_RESERVED_MASK           0xFFFFFF00
#define NANDC_PCELL_ID_3_RESERVED_SHIFT          8 
#define NANDC_PCELL_ID_3_RESERVED_BIT            0xFFFFFF
#define NANDC_PCELL_ID_3_RESERVED_BITWIDTH       24

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _NANDC_REG_DEF_H */
