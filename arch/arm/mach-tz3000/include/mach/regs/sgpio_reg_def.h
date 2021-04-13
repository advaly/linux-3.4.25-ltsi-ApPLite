/*
 * arch/arm/mach-tz3000/include/mach/regs/sgpio_reg_def.h
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

#ifndef _SGPIO_REG_DEF_H
#define _SGPIO_REG_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

// GP_CR Register
#define SGPIO_GP_CR_OFS                          0x00000000
// CR bitfiled (RW) Reset=0
#define SGPIO_GP_CR_CR_MASK                      0xFFFFFFFF
#define SGPIO_GP_CR_CR_SHIFT                     0 
#define SGPIO_GP_CR_CR_BIT                       0xFFFFFFFF
#define SGPIO_GP_CR_CR_BITWIDTH                  32
// GP_DR Register
#define SGPIO_GP_DR_OFS                          0x00000004
// DR bitfiled (RO) Reset=0
#define SGPIO_GP_DR_DR_MASK                      0xFFFFFFFF
#define SGPIO_GP_DR_DR_SHIFT                     0 
#define SGPIO_GP_DR_DR_BIT                       0xFFFFFFFF
#define SGPIO_GP_DR_DR_BITWIDTH                  32
// GP_ODS Register
#define SGPIO_GP_ODS_OFS                         0x00000008
// ODS bitfiled (RW) Reset=0
#define SGPIO_GP_ODS_ODS_MASK                    0xFFFFFFFF
#define SGPIO_GP_ODS_ODS_SHIFT                   0 
#define SGPIO_GP_ODS_ODS_BIT                     0xFFFFFFFF
#define SGPIO_GP_ODS_ODS_BITWIDTH                32
// GP_ODC Register
#define SGPIO_GP_ODC_OFS                         0x0000000C
// ODC bitfiled (RW) Reset=0
#define SGPIO_GP_ODC_ODC_MASK                    0xFFFFFFFF
#define SGPIO_GP_ODC_ODC_SHIFT                   0 
#define SGPIO_GP_ODC_ODC_BIT                     0xFFFFFFFF
#define SGPIO_GP_ODC_ODC_BITWIDTH                32
// GP_INTS Register
#define SGPIO_GP_INTS_OFS                        0x00000010
// INT bitfiled (RO) Reset=0
#define SGPIO_GP_INTS_INT_MASK                   0x1F
#define SGPIO_GP_INTS_INT_SHIFT                  0 
#define SGPIO_GP_INTS_INT_BIT                    0x1F
#define SGPIO_GP_INTS_INT_BITWIDTH               5
// reserved bitfiled (RO) Reset=0
#define SGPIO_GP_INTS_RESERVED_MASK              0xFFFFFFE0
#define SGPIO_GP_INTS_RESERVED_SHIFT             5 
#define SGPIO_GP_INTS_RESERVED_BIT               0x7FFFFFF
#define SGPIO_GP_INTS_RESERVED_BITWIDTH          27
// GP_INTC0 Register
#define SGPIO_GP_INTC0_OFS                       0x00000014
// INTC0 bitfiled (RW) Reset=0
#define SGPIO_GP_INTC0_INTC0_MASK                0xFFFFFFFF
#define SGPIO_GP_INTC0_INTC0_SHIFT               0 
#define SGPIO_GP_INTC0_INTC0_BIT                 0xFFFFFFFF
#define SGPIO_GP_INTC0_INTC0_BITWIDTH            32
// GP_INTC1 Register
#define SGPIO_GP_INTC1_OFS                       0x00000018
// INTC1 bitfiled (RW) Reset=0
#define SGPIO_GP_INTC1_INTC1_MASK                0xFFFFFFFF
#define SGPIO_GP_INTC1_INTC1_SHIFT               0 
#define SGPIO_GP_INTC1_INTC1_BIT                 0xFFFFFFFF
#define SGPIO_GP_INTC1_INTC1_BITWIDTH            32
// GP_INTM0 Register
#define SGPIO_GP_INTM0_OFS                       0x0000001C
// INTM0 bitfiled (RW) Reset=11111111111111111111111111111111
#define SGPIO_GP_INTM0_INTM0_MASK                0xFFFFFFFF
#define SGPIO_GP_INTM0_INTM0_SHIFT               0 
#define SGPIO_GP_INTM0_INTM0_BIT                 0xFFFFFFFF
#define SGPIO_GP_INTM0_INTM0_BITWIDTH            32
// GP_INTM1 Register
#define SGPIO_GP_INTM1_OFS                       0x00000020
// INTM1 bitfiled (RW) Reset=11111111111111111111111111111111
#define SGPIO_GP_INTM1_INTM1_MASK                0xFFFFFFFF
#define SGPIO_GP_INTM1_INTM1_SHIFT               0 
#define SGPIO_GP_INTM1_INTM1_BIT                 0xFFFFFFFF
#define SGPIO_GP_INTM1_INTM1_BITWIDTH            32
// GP_INTM2 Register
#define SGPIO_GP_INTM2_OFS                       0x00000024
// INTM2 bitfiled (RW) Reset=11111111111111111111111111111111
#define SGPIO_GP_INTM2_INTM2_MASK                0xFFFFFFFF
#define SGPIO_GP_INTM2_INTM2_SHIFT               0 
#define SGPIO_GP_INTM2_INTM2_BIT                 0xFFFFFFFF
#define SGPIO_GP_INTM2_INTM2_BITWIDTH            32
// GP_INTM3 Register
#define SGPIO_GP_INTM3_OFS                       0x00000028
// INTM3 bitfiled (RW) Reset=11111111111111111111111111111111
#define SGPIO_GP_INTM3_INTM3_MASK                0xFFFFFFFF
#define SGPIO_GP_INTM3_INTM3_SHIFT               0 
#define SGPIO_GP_INTM3_INTM3_BIT                 0xFFFFFFFF
#define SGPIO_GP_INTM3_INTM3_BITWIDTH            32
// GP_INTM4 Register
#define SGPIO_GP_INTM4_OFS                       0x0000002C
// INTM4 bitfiled (RW) Reset=11111111111111111111111111111111
#define SGPIO_GP_INTM4_INTM4_MASK                0xFFFFFFFF
#define SGPIO_GP_INTM4_INTM4_SHIFT               0 
#define SGPIO_GP_INTM4_INTM4_BIT                 0xFFFFFFFF
#define SGPIO_GP_INTM4_INTM4_BITWIDTH            32
// GP_SMP Register
#define SGPIO_GP_SMP_OFS                         0x00000030
// SMP_INTERVAL bitfiled (RW) Reset=0
#define SGPIO_GP_SMP_SMP_INTERVAL_MASK           0xFFFF
#define SGPIO_GP_SMP_SMP_INTERVAL_SHIFT          0 
#define SGPIO_GP_SMP_SMP_INTERVAL_BIT            0xFFFF
#define SGPIO_GP_SMP_SMP_INTERVAL_BITWIDTH       16
// SMP_POINT_NUMBER bitfiled (RW) Reset=0
#define SGPIO_GP_SMP_SMP_POINT_NUMBER_MASK       0x70000
#define SGPIO_GP_SMP_SMP_POINT_NUMBER_SHIFT      16 
#define SGPIO_GP_SMP_SMP_POINT_NUMBER_BIT        0x7
#define SGPIO_GP_SMP_SMP_POINT_NUMBER_BITWIDTH   3
// reserved bitfiled (RO) Reset=0
#define SGPIO_GP_SMP_RESERVED_MASK               0xFFF80000
#define SGPIO_GP_SMP_RESERVED_SHIFT              19 
#define SGPIO_GP_SMP_RESERVED_BIT                0x1FFF
#define SGPIO_GP_SMP_RESERVED_BITWIDTH           13
// GP_ODR Register
#define SGPIO_GP_ODR_OFS                         0x00000034
// ODR bitfiled (RW) Reset=0
#define SGPIO_GP_ODR_ODR_MASK                    0xFFFFFFFF
#define SGPIO_GP_ODR_ODR_SHIFT                   0 
#define SGPIO_GP_ODR_ODR_BIT                     0xFFFFFFFF
#define SGPIO_GP_ODR_ODR_BITWIDTH                32
// GP_IR0 Register
#define SGPIO_GP_IR0_OFS                         0x00000038
// STAT bitfiled (RW) Reset=0
#define SGPIO_GP_IR0_STAT_MASK                   0xFFFFFFFF
#define SGPIO_GP_IR0_STAT_SHIFT                  0 
#define SGPIO_GP_IR0_STAT_BIT                    0xFFFFFFFF
#define SGPIO_GP_IR0_STAT_BITWIDTH               32
// GP_IR1 Register
#define SGPIO_GP_IR1_OFS                         0x0000003C
// STAT bitfiled (RW) Reset=0
#define SGPIO_GP_IR1_STAT_MASK                   0xFFFFFFFF
#define SGPIO_GP_IR1_STAT_SHIFT                  0 
#define SGPIO_GP_IR1_STAT_BIT                    0xFFFFFFFF
#define SGPIO_GP_IR1_STAT_BITWIDTH               32
// GP_IR2 Register
#define SGPIO_GP_IR2_OFS                         0x00000040
// STAT bitfiled (RW) Reset=0
#define SGPIO_GP_IR2_STAT_MASK                   0xFFFFFFFF
#define SGPIO_GP_IR2_STAT_SHIFT                  0 
#define SGPIO_GP_IR2_STAT_BIT                    0xFFFFFFFF
#define SGPIO_GP_IR2_STAT_BITWIDTH               32
// GP_IR3 Register
#define SGPIO_GP_IR3_OFS                         0x00000044
// STAT bitfiled (RW) Reset=0
#define SGPIO_GP_IR3_STAT_MASK                   0xFFFFFFFF
#define SGPIO_GP_IR3_STAT_SHIFT                  0 
#define SGPIO_GP_IR3_STAT_BIT                    0xFFFFFFFF
#define SGPIO_GP_IR3_STAT_BITWIDTH               32
// GP_IR4 Register
#define SGPIO_GP_IR4_OFS                         0x00000048
// STAT bitfiled (RW) Reset=0
#define SGPIO_GP_IR4_STAT_MASK                   0xFFFFFFFF
#define SGPIO_GP_IR4_STAT_SHIFT                  0 
#define SGPIO_GP_IR4_STAT_BIT                    0xFFFFFFFF
#define SGPIO_GP_IR4_STAT_BITWIDTH               32
// GP_PUDEN Register
#define SGPIO_GP_PUDEN_OFS                       0x00000050
// PUDEN bitfiled (RW) Reset=0
#define SGPIO_GP_PUDEN_PUDEN_MASK                0xFFFFFFFF
#define SGPIO_GP_PUDEN_PUDEN_SHIFT               0 
#define SGPIO_GP_PUDEN_PUDEN_BIT                 0xFFFFFFFF
#define SGPIO_GP_PUDEN_PUDEN_BITWIDTH            32
// GP_PUDSEL Register
#define SGPIO_GP_PUDSEL_OFS                      0x00000054
// PUDSEL bitfiled (RW) Reset=0
#define SGPIO_GP_PUDSEL_PUDSEL_MASK              0xFFFFFFFF
#define SGPIO_GP_PUDSEL_PUDSEL_SHIFT             0 
#define SGPIO_GP_PUDSEL_PUDSEL_BIT               0xFFFFFFFF
#define SGPIO_GP_PUDSEL_PUDSEL_BITWIDTH          32
// GP_INPEN Register
#define SGPIO_GP_INPEN_OFS                       0x00000058
// INPEN bitfiled (RW) Reset=0
#define SGPIO_GP_INPEN_INPEN_MASK                0xFFFFFFFF
#define SGPIO_GP_INPEN_INPEN_SHIFT               0 
#define SGPIO_GP_INPEN_INPEN_BIT                 0xFFFFFFFF
#define SGPIO_GP_INPEN_INPEN_BITWIDTH            32

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SGPIO_REG_DEF_H */
