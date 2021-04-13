/*
 * arch/arm/mach-tz3000/include/mach/regs/sgpio_offs_def.h
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

#ifndef SGPIO_OFFS_DEF_H
#define SGPIO_OFFS_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

#define SGPIO_GP_CR_OFFS               0x00000000
#define SGPIO_GP_DR_OFFS               0x00000004
#define SGPIO_GP_ODS_OFFS              0x00000008
#define SGPIO_GP_ODC_OFFS              0x0000000C
#define SGPIO_GP_INTS_OFFS             0x00000010
#define SGPIO_GP_INTC0_OFFS            0x00000014
#define SGPIO_GP_INTC1_OFFS            0x00000018
#define SGPIO_GP_INTM0_OFFS            0x0000001C
#define SGPIO_GP_INTM1_OFFS            0x00000020
#define SGPIO_GP_INTM2_OFFS            0x00000024
#define SGPIO_GP_INTM3_OFFS            0x00000028
#define SGPIO_GP_INTM4_OFFS            0x0000002C
#define SGPIO_GP_SMP_OFFS              0x00000030
#define SGPIO_GP_ODR_OFFS              0x00000034
#define SGPIO_GP_IR0_OFFS              0x00000038
#define SGPIO_GP_IR1_OFFS              0x0000003C
#define SGPIO_GP_IR2_OFFS              0x00000040
#define SGPIO_GP_IR3_OFFS              0x00000044
#define SGPIO_GP_IR4_OFFS              0x00000048
#define SGPIO_GP_PUDEN_OFFS            0x00000050
#define SGPIO_GP_PUDSEL_OFFS           0x00000054
#define SGPIO_GP_INPEN_OFFS            0x00000058

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SGPIO_OFFS_DEF_H */
