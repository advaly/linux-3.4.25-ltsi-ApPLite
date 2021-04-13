/*
 * arch/arm/mach-tz2000/include/mach/regs/gpio_reg_def.h
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

#ifndef _GPIO_REG_DEF_H
#define _GPIO_REG_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

// GP0_CR Register
#define GPIO_GP0_CR_OFS                          0x00000000
// CR bitfiled (RW) Reset=0
#define GPIO_GP0_CR_CR_MASK                      0xFFFFFFFF
#define GPIO_GP0_CR_CR_SHIFT                     0 
#define GPIO_GP0_CR_CR_BIT                       0xFFFFFFFF
#define GPIO_GP0_CR_CR_BITWIDTH                  32
// GP0_DR Register
#define GPIO_GP0_DR_OFS                          0x00000004
// DR bitfiled (RO) Reset=0
#define GPIO_GP0_DR_DR_MASK                      0xFFFFFFFF
#define GPIO_GP0_DR_DR_SHIFT                     0 
#define GPIO_GP0_DR_DR_BIT                       0xFFFFFFFF
#define GPIO_GP0_DR_DR_BITWIDTH                  32
// GP0_ODS Register
#define GPIO_GP0_ODS_OFS                         0x00000008
// ODS bitfiled (RW) Reset=0
#define GPIO_GP0_ODS_ODS_MASK                    0xFFFFFFFF
#define GPIO_GP0_ODS_ODS_SHIFT                   0 
#define GPIO_GP0_ODS_ODS_BIT                     0xFFFFFFFF
#define GPIO_GP0_ODS_ODS_BITWIDTH                32
// GP0_ODC Register
#define GPIO_GP0_ODC_OFS                         0x0000000C
// ODC bitfiled (RW) Reset=0
#define GPIO_GP0_ODC_ODC_MASK                    0xFFFFFFFF
#define GPIO_GP0_ODC_ODC_SHIFT                   0 
#define GPIO_GP0_ODC_ODC_BIT                     0xFFFFFFFF
#define GPIO_GP0_ODC_ODC_BITWIDTH                32
// GP_INTS Register
#define GPIO_GP_INTS_OFS                         0x00000010
// INT bitfiled (RO) Reset=0
#define GPIO_GP_INTS_INT_MASK                    0x1F
#define GPIO_GP_INTS_INT_SHIFT                   0 
#define GPIO_GP_INTS_INT_BIT                     0x1F
#define GPIO_GP_INTS_INT_BITWIDTH                5
// reserved bitfiled (RO) Reset=0
#define GPIO_GP_INTS_RESERVED_MASK               0xFFFFFFE0
#define GPIO_GP_INTS_RESERVED_SHIFT              5 
#define GPIO_GP_INTS_RESERVED_BIT                0x7FFFFFF
#define GPIO_GP_INTS_RESERVED_BITWIDTH           27
// GP0_INTC0 Register
#define GPIO_GP0_INTC0_OFS                       0x00000014
// INTC0 bitfiled (RW) Reset=0
#define GPIO_GP0_INTC0_INTC0_MASK                0xFFFFFFFF
#define GPIO_GP0_INTC0_INTC0_SHIFT               0 
#define GPIO_GP0_INTC0_INTC0_BIT                 0xFFFFFFFF
#define GPIO_GP0_INTC0_INTC0_BITWIDTH            32
// GP0_INTC1 Register
#define GPIO_GP0_INTC1_OFS                       0x00000018
// INTC1 bitfiled (RW) Reset=0
#define GPIO_GP0_INTC1_INTC1_MASK                0xFFFFFFFF
#define GPIO_GP0_INTC1_INTC1_SHIFT               0 
#define GPIO_GP0_INTC1_INTC1_BIT                 0xFFFFFFFF
#define GPIO_GP0_INTC1_INTC1_BITWIDTH            32
// GP0_INTM0 Register
#define GPIO_GP0_INTM0_OFS                       0x0000001C
// INTM0 bitfiled (RW) Reset=11111111111111111111111111111111
#define GPIO_GP0_INTM0_INTM0_MASK                0xFFFFFFFF
#define GPIO_GP0_INTM0_INTM0_SHIFT               0 
#define GPIO_GP0_INTM0_INTM0_BIT                 0xFFFFFFFF
#define GPIO_GP0_INTM0_INTM0_BITWIDTH            32
// GP0_SMP Register
#define GPIO_GP0_SMP_OFS                         0x00000030
// smp_interval bitfiled (RW) Reset=0
#define GPIO_GP0_SMP_SMP_INTERVAL_MASK           0xFFFF
#define GPIO_GP0_SMP_SMP_INTERVAL_SHIFT          0 
#define GPIO_GP0_SMP_SMP_INTERVAL_BIT            0xFFFF
#define GPIO_GP0_SMP_SMP_INTERVAL_BITWIDTH       16
// smp_point_number bitfiled (RW) Reset=0
#define GPIO_GP0_SMP_SMP_POINT_NUMBER_MASK       0x70000
#define GPIO_GP0_SMP_SMP_POINT_NUMBER_SHIFT      16 
#define GPIO_GP0_SMP_SMP_POINT_NUMBER_BIT        0x7
#define GPIO_GP0_SMP_SMP_POINT_NUMBER_BITWIDTH   3
// reserved bitfiled (RO) Reset=0
#define GPIO_GP0_SMP_RESERVED_MASK               0xFFF80000
#define GPIO_GP0_SMP_RESERVED_SHIFT              19 
#define GPIO_GP0_SMP_RESERVED_BIT                0x1FFF
#define GPIO_GP0_SMP_RESERVED_BITWIDTH           13
// GP0_ODR Register
#define GPIO_GP0_ODR_OFS                         0x00000034
// ODR bitfiled (RW) Reset=0
#define GPIO_GP0_ODR_ODR_MASK                    0xFFFFFFFF
#define GPIO_GP0_ODR_ODR_SHIFT                   0 
#define GPIO_GP0_ODR_ODR_BIT                     0xFFFFFFFF
#define GPIO_GP0_ODR_ODR_BITWIDTH                32
// GP0_IR0 Register
#define GPIO_GP0_IR0_OFS                         0x00000038
// STAT bitfiled (RW) Reset=0
#define GPIO_GP0_IR0_STAT_MASK                   0xFFFFFFFF
#define GPIO_GP0_IR0_STAT_SHIFT                  0 
#define GPIO_GP0_IR0_STAT_BIT                    0xFFFFFFFF
#define GPIO_GP0_IR0_STAT_BITWIDTH               32
// GP0_PUDEN Register
#define GPIO_GP0_PUDEN_OFS                       0x00000050
// PUDEN bitfiled (RW) Reset=0
#define GPIO_GP0_PUDEN_PUDEN_MASK                0xFFFFFFFF
#define GPIO_GP0_PUDEN_PUDEN_SHIFT               0 
#define GPIO_GP0_PUDEN_PUDEN_BIT                 0xFFFFFFFF
#define GPIO_GP0_PUDEN_PUDEN_BITWIDTH            32
// GP0_PUDSEL Register
#define GPIO_GP0_PUDSEL_OFS                      0x00000054
// PUDSEL bitfiled (RW) Reset=0
#define GPIO_GP0_PUDSEL_PUDSEL_MASK              0xFFFFFFFF
#define GPIO_GP0_PUDSEL_PUDSEL_SHIFT             0 
#define GPIO_GP0_PUDSEL_PUDSEL_BIT               0xFFFFFFFF
#define GPIO_GP0_PUDSEL_PUDSEL_BITWIDTH          32
// GP0_INPEN Register
#define GPIO_GP0_INPEN_OFS                       0x00000058
// INPEN bitfiled (RW) Reset=0
#define GPIO_GP0_INPEN_INPEN_MASK                0xFFFFFFFF
#define GPIO_GP0_INPEN_INPEN_SHIFT               0 
#define GPIO_GP0_INPEN_INPEN_BIT                 0xFFFFFFFF
#define GPIO_GP0_INPEN_INPEN_BITWIDTH            32
// GP1_CR Register
#define GPIO_GP1_CR_OFS                          0x00001000
// CR bitfiled (RW) Reset=0
#define GPIO_GP1_CR_CR_MASK                      0xFFFFFFFF
#define GPIO_GP1_CR_CR_SHIFT                     0 
#define GPIO_GP1_CR_CR_BIT                       0xFFFFFFFF
#define GPIO_GP1_CR_CR_BITWIDTH                  32
// GP1_DR Register
#define GPIO_GP1_DR_OFS                          0x00001004
// DR bitfiled (RO) Reset=0
#define GPIO_GP1_DR_DR_MASK                      0xFFFFFFFF
#define GPIO_GP1_DR_DR_SHIFT                     0 
#define GPIO_GP1_DR_DR_BIT                       0xFFFFFFFF
#define GPIO_GP1_DR_DR_BITWIDTH                  32
// GP1_ODS Register
#define GPIO_GP1_ODS_OFS                         0x00001008
// ODS bitfiled (RW) Reset=0
#define GPIO_GP1_ODS_ODS_MASK                    0xFFFFFFFF
#define GPIO_GP1_ODS_ODS_SHIFT                   0 
#define GPIO_GP1_ODS_ODS_BIT                     0xFFFFFFFF
#define GPIO_GP1_ODS_ODS_BITWIDTH                32
// GP1_ODC Register
#define GPIO_GP1_ODC_OFS                         0x0000100C
// ODC bitfiled (RW) Reset=0
#define GPIO_GP1_ODC_ODC_MASK                    0xFFFFFFFF
#define GPIO_GP1_ODC_ODC_SHIFT                   0 
#define GPIO_GP1_ODC_ODC_BIT                     0xFFFFFFFF
#define GPIO_GP1_ODC_ODC_BITWIDTH                32
// GP1_INTS Register
#define GPIO_GP1_INTS_OFS                        0x00001010
// INT bitfiled (RO) Reset=0
#define GPIO_GP1_INTS_INT_MASK                   0x1F
#define GPIO_GP1_INTS_INT_SHIFT                  0 
#define GPIO_GP1_INTS_INT_BIT                    0x1F
#define GPIO_GP1_INTS_INT_BITWIDTH               5
// reserved bitfiled (RO) Reset=0
#define GPIO_GP1_INTS_RESERVED_MASK              0xFFFFFFE0
#define GPIO_GP1_INTS_RESERVED_SHIFT             5 
#define GPIO_GP1_INTS_RESERVED_BIT               0x7FFFFFF
#define GPIO_GP1_INTS_RESERVED_BITWIDTH          27
// GP1_INTC0 Register
#define GPIO_GP1_INTC0_OFS                       0x00001014
// INTC0 bitfiled (RW) Reset=0
#define GPIO_GP1_INTC0_INTC0_MASK                0xFFFFFFFF
#define GPIO_GP1_INTC0_INTC0_SHIFT               0 
#define GPIO_GP1_INTC0_INTC0_BIT                 0xFFFFFFFF
#define GPIO_GP1_INTC0_INTC0_BITWIDTH            32
// GP1_INTC1 Register
#define GPIO_GP1_INTC1_OFS                       0x00001018
// INTC1 bitfiled (RW) Reset=0
#define GPIO_GP1_INTC1_INTC1_MASK                0xFFFFFFFF
#define GPIO_GP1_INTC1_INTC1_SHIFT               0 
#define GPIO_GP1_INTC1_INTC1_BIT                 0xFFFFFFFF
#define GPIO_GP1_INTC1_INTC1_BITWIDTH            32
// GP1_INTM0 Register
#define GPIO_GP1_INTM0_OFS                       0x0000101C
// INTM0 bitfiled (RW) Reset=11111111111111111111111111111111
#define GPIO_GP1_INTM0_INTM0_MASK                0xFFFFFFFF
#define GPIO_GP1_INTM0_INTM0_SHIFT               0 
#define GPIO_GP1_INTM0_INTM0_BIT                 0xFFFFFFFF
#define GPIO_GP1_INTM0_INTM0_BITWIDTH            32
// GP1_SMP Register
#define GPIO_GP1_SMP_OFS                         0x00001030
// smp_interval bitfiled (RW) Reset=0
#define GPIO_GP1_SMP_SMP_INTERVAL_MASK           0xFFFF
#define GPIO_GP1_SMP_SMP_INTERVAL_SHIFT          0 
#define GPIO_GP1_SMP_SMP_INTERVAL_BIT            0xFFFF
#define GPIO_GP1_SMP_SMP_INTERVAL_BITWIDTH       16
// smp_point_number bitfiled (RW) Reset=0
#define GPIO_GP1_SMP_SMP_POINT_NUMBER_MASK       0x70000
#define GPIO_GP1_SMP_SMP_POINT_NUMBER_SHIFT      16 
#define GPIO_GP1_SMP_SMP_POINT_NUMBER_BIT        0x7
#define GPIO_GP1_SMP_SMP_POINT_NUMBER_BITWIDTH   3
// reserved bitfiled (RO) Reset=0
#define GPIO_GP1_SMP_RESERVED_MASK               0xFFF80000
#define GPIO_GP1_SMP_RESERVED_SHIFT              19 
#define GPIO_GP1_SMP_RESERVED_BIT                0x1FFF
#define GPIO_GP1_SMP_RESERVED_BITWIDTH           13
// GP1_ODR Register
#define GPIO_GP1_ODR_OFS                         0x00001034
// ODR bitfiled (RW) Reset=0
#define GPIO_GP1_ODR_ODR_MASK                    0xFFFFFFFF
#define GPIO_GP1_ODR_ODR_SHIFT                   0 
#define GPIO_GP1_ODR_ODR_BIT                     0xFFFFFFFF
#define GPIO_GP1_ODR_ODR_BITWIDTH                32
// GP1_IR0 Register
#define GPIO_GP1_IR0_OFS                         0x00001038
// STAT bitfiled (RW) Reset=0
#define GPIO_GP1_IR0_STAT_MASK                   0xFFFFFFFF
#define GPIO_GP1_IR0_STAT_SHIFT                  0 
#define GPIO_GP1_IR0_STAT_BIT                    0xFFFFFFFF
#define GPIO_GP1_IR0_STAT_BITWIDTH               32
// GP1_PUDEN Register
#define GPIO_GP1_PUDEN_OFS                       0x00001050
// PUDEN bitfiled (RW) Reset=0
#define GPIO_GP1_PUDEN_PUDEN_MASK                0xFFFFFFFF
#define GPIO_GP1_PUDEN_PUDEN_SHIFT               0 
#define GPIO_GP1_PUDEN_PUDEN_BIT                 0xFFFFFFFF
#define GPIO_GP1_PUDEN_PUDEN_BITWIDTH            32
// GP1_PUDSEL Register
#define GPIO_GP1_PUDSEL_OFS                      0x00001054
// PUDSEL bitfiled (RW) Reset=0
#define GPIO_GP1_PUDSEL_PUDSEL_MASK              0xFFFFFFFF
#define GPIO_GP1_PUDSEL_PUDSEL_SHIFT             0 
#define GPIO_GP1_PUDSEL_PUDSEL_BIT               0xFFFFFFFF
#define GPIO_GP1_PUDSEL_PUDSEL_BITWIDTH          32
// GP1_INPEN Register
#define GPIO_GP1_INPEN_OFS                       0x00001058
// INPEN bitfiled (RW) Reset=0
#define GPIO_GP1_INPEN_INPEN_MASK                0xFFFFFFFF
#define GPIO_GP1_INPEN_INPEN_SHIFT               0 
#define GPIO_GP1_INPEN_INPEN_BIT                 0xFFFFFFFF
#define GPIO_GP1_INPEN_INPEN_BITWIDTH            32

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _GPIO_REG_DEF_H */
