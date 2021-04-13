/*
 * arch/arm/mach-tz3000/include/mach/regs/nandc_offs_def.h
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

#ifndef NANDC_OFFS_DEF_H
#define NANDC_OFFS_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

#define NANDC_memc_status_OFFS         0x00000000
#define NANDC_memif_cfg_OFFS           0x00000004
#define NANDC_mem_cfg_set_OFFS         0x00000008
#define NANDC_mem_cfg_clr_OFFS         0x0000000C
#define NANDC_direct_cmd_OFFS          0x00000010
#define NANDC_set_cycles_OFFS          0x00000014
#define NANDC_set_opmode_OFFS          0x00000018
#define NANDC_refresh_0_OFFS           0x00000020
#define NANDC_refresh_1_OFFS           0x00000024
#define NANDC_nand_cycles0_0_OFFS      0x00000100
#define NANDC_opmode0_0_OFFS           0x00000104
#define NANDC_nand_cycles0_1_OFFS      0x00000120
#define NANDC_opmode0_1_OFFS           0x00000124
#define NANDC_nand_cycles0_2_OFFS      0x00000140
#define NANDC_opmode0_2_OFFS           0x00000144
#define NANDC_nand_cycles0_3_OFFS      0x00000160
#define NANDC_opmode0_3_OFFS           0x00000164
#define NANDC_user_status_OFFS         0x00000200
#define NANDC_user_config_OFFS         0x00000204
#define NANDC_ecc0_status_OFFS         0x00000300
#define NANDC_ecc0_cfg_OFFS            0x00000304
#define NANDC_ecc0_memcmd0_OFFS        0x00000308
#define NANDC_ecc0_memcmd1_OFFS        0x0000030C
#define NANDC_ecc0_addr0_OFFS          0x00000310
#define NANDC_ecc0_addr1_OFFS          0x00000314
#define NANDC_ecc0_block0_OFFS         0x00000318
#define NANDC_ecc0_block1_OFFS         0x0000031C
#define NANDC_ecc0_block2_OFFS         0x00000320
#define NANDC_ecc0_block3_OFFS         0x00000324
#define NANDC_ecc0_extra_block_OFFS    0x00000328
#define NANDC_int_cfg_OFFS             0x00000E00
#define NANDC_int_inputs_OFFS          0x00000E04
#define NANDC_int_outputs_OFFS         0x00000E08
#define NANDC_periph_id_0_OFFS         0x00000FE0
#define NANDC_periph_id_1_OFFS         0x00000FE4
#define NANDC_periph_id_2_OFFS         0x00000FE8
#define NANDC_periph_id_3_OFFS         0x00000FEC
#define NANDC_pcell_id_0_OFFS          0x00000FF0
#define NANDC_pcell_id_1_OFFS          0x00000FF4
#define NANDC_pcell_id_2_OFFS          0x00000FF8
#define NANDC_pcell_id_3_OFFS          0x00000FFC

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NANDC_OFFS_DEF_H */
