/*
 * arch/arm/mach-tz3000/include/mach/regs/gconf_reg_def.h
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

#ifndef _GCONF_REG_DEF_H
#define _GCONF_REG_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

// I2SSEL Register
#define GCONF_I2SSEL_OFS                         0x00000000
// OE_N bitfiled (RW) Reset=1
#define GCONF_I2SSEL_OE_N_MASK                   0x1
#define GCONF_I2SSEL_OE_N_SHIFT                  0 
#define GCONF_I2SSEL_OE_N_BIT                    0x1
#define GCONF_I2SSEL_OE_N_BITWIDTH               1
// I2SSEL bitfiled (RW) Reset=0
#define GCONF_I2SSEL_I2SSEL_MASK                 0xE
#define GCONF_I2SSEL_I2SSEL_SHIFT                1 
#define GCONF_I2SSEL_I2SSEL_BIT                  0x7
#define GCONF_I2SSEL_I2SSEL_BITWIDTH             3
// reserved1 bitfiled (RO) Reset=0
#define GCONF_I2SSEL_RESERVED1_MASK              0xFFFFFFF0
#define GCONF_I2SSEL_RESERVED1_SHIFT             4 
#define GCONF_I2SSEL_RESERVED1_BIT               0xFFFFFFF
#define GCONF_I2SSEL_RESERVED1_BITWIDTH          28
// PINSHARE0 Register
#define GCONF_PINSHARE0_OFS                      0x00000010
// reserved1 bitfiled (RO) Reset=0
#define GCONF_PINSHARE0_RESERVED1_MASK           0xFF
#define GCONF_PINSHARE0_RESERVED1_SHIFT          0 
#define GCONF_PINSHARE0_RESERVED1_BIT            0xFF
#define GCONF_PINSHARE0_RESERVED1_BITWIDTH       8
// GPIO_SEL0 bitfiled (RW) Reset=0
#define GCONF_PINSHARE0_GPIO_SEL0_MASK           0xFFFFFF00
#define GCONF_PINSHARE0_GPIO_SEL0_SHIFT          8 
#define GCONF_PINSHARE0_GPIO_SEL0_BIT            0xFFFFFF
#define GCONF_PINSHARE0_GPIO_SEL0_BITWIDTH       24
// PINSHARE1 Register
#define GCONF_PINSHARE1_OFS                      0x00000014
// GPIO_SEL1 bitfiled (RW) Reset=0
#define GCONF_PINSHARE1_GPIO_SEL1_MASK           0xFFFFFFFF
#define GCONF_PINSHARE1_GPIO_SEL1_SHIFT          0 
#define GCONF_PINSHARE1_GPIO_SEL1_BIT            0xFFFFFFFF
#define GCONF_PINSHARE1_GPIO_SEL1_BITWIDTH       32
// PINSHARE2 Register
#define GCONF_PINSHARE2_OFS                      0x00000020
// SDIME_SEL bitfiled (RW) Reset=1
#define GCONF_PINSHARE2_SDIME_SEL_MASK           0x1
#define GCONF_PINSHARE2_SDIME_SEL_SHIFT          0 
#define GCONF_PINSHARE2_SDIME_SEL_BIT            0x1
#define GCONF_PINSHARE2_SDIME_SEL_BITWIDTH       1
// reserved1 bitfiled (RO) Reset=0
#define GCONF_PINSHARE2_RESERVED1_MASK           0xFFFFFFFE
#define GCONF_PINSHARE2_RESERVED1_SHIFT          1 
#define GCONF_PINSHARE2_RESERVED1_BIT            0x7FFFFFFF
#define GCONF_PINSHARE2_RESERVED1_BITWIDTH       31
// PINSHARE3 Register
#define GCONF_PINSHARE3_OFS                      0x00000028
// eMMC2_SEL bitfiled (RW) Reset=0
#define GCONF_PINSHARE3_EMMC2_SEL_MASK           0x1
#define GCONF_PINSHARE3_EMMC2_SEL_SHIFT          0 
#define GCONF_PINSHARE3_EMMC2_SEL_BIT            0x1
#define GCONF_PINSHARE3_EMMC2_SEL_BITWIDTH       1
// reserved1 bitfiled (RO) Reset=0
#define GCONF_PINSHARE3_RESERVED1_MASK           0xFFFFFFFE
#define GCONF_PINSHARE3_RESERVED1_SHIFT          1 
#define GCONF_PINSHARE3_RESERVED1_BIT            0x7FFFFFFF
#define GCONF_PINSHARE3_RESERVED1_BITWIDTH       31
// CPU_EVENT Register
#define GCONF_CPU_EVENT_OFS                      0x00000038
// CPU_EVENT bitfiled (RW) Reset=0
#define GCONF_CPU_EVENT_CPU_EVENT_MASK           0x1
#define GCONF_CPU_EVENT_CPU_EVENT_SHIFT          0 
#define GCONF_CPU_EVENT_CPU_EVENT_BIT            0x1
#define GCONF_CPU_EVENT_CPU_EVENT_BITWIDTH       1
// reserved bitfiled (RO) Reset=0
#define GCONF_CPU_EVENT_RESERVED_MASK            0x7FFFFFFE
#define GCONF_CPU_EVENT_RESERVED_SHIFT           1 
#define GCONF_CPU_EVENT_RESERVED_BIT             0x3FFFFFFF
#define GCONF_CPU_EVENT_RESERVED_BITWIDTH        30
// reserved2 bitfiled (RO) Reset=0
#define GCONF_CPU_EVENT_RESERVED2_MASK           0x80000000
#define GCONF_CPU_EVENT_RESERVED2_SHIFT          31 
#define GCONF_CPU_EVENT_RESERVED2_BIT            0x1
#define GCONF_CPU_EVENT_RESERVED2_BITWIDTH       1
// CPU_STANDBY_STATUS Register
#define GCONF_CPU_STANDBY_STATUS_OFS             0x0000003C
// CPU_STANDBYWFI bitfiled (RO) Reset=0
#define GCONF_CPU_STANDBY_STATUS_CPU_STANDBYWFI_MASK 0x3
#define GCONF_CPU_STANDBY_STATUS_CPU_STANDBYWFI_SHIFT 0 
#define GCONF_CPU_STANDBY_STATUS_CPU_STANDBYWFI_BIT 0x3
#define GCONF_CPU_STANDBY_STATUS_CPU_STANDBYWFI_BITWIDTH 2
// reserved2 bitfiled (RO) Reset=0
#define GCONF_CPU_STANDBY_STATUS_RESERVED2_MASK  0xC
#define GCONF_CPU_STANDBY_STATUS_RESERVED2_SHIFT 2 
#define GCONF_CPU_STANDBY_STATUS_RESERVED2_BIT   0x3
#define GCONF_CPU_STANDBY_STATUS_RESERVED2_BITWIDTH 2
// CPU_STANDBYWFE bitfiled (RO) Reset=0
#define GCONF_CPU_STANDBY_STATUS_CPU_STANDBYWFE_MASK 0x30
#define GCONF_CPU_STANDBY_STATUS_CPU_STANDBYWFE_SHIFT 4 
#define GCONF_CPU_STANDBY_STATUS_CPU_STANDBYWFE_BIT 0x3
#define GCONF_CPU_STANDBY_STATUS_CPU_STANDBYWFE_BITWIDTH 2
// reserved bitfiled (RO) Reset=0
#define GCONF_CPU_STANDBY_STATUS_RESERVED_MASK   0xFFFFFFC0
#define GCONF_CPU_STANDBY_STATUS_RESERVED_SHIFT  6 
#define GCONF_CPU_STANDBY_STATUS_RESERVED_BIT    0x3FFFFFF
#define GCONF_CPU_STANDBY_STATUS_RESERVED_BITWIDTH 26
// GDMAC_CTRL0 Register
#define GCONF_GDMAC_CTRL0_OFS                    0x00000040
// PCLKEN bitfiled (RW) Reset=1
#define GCONF_GDMAC_CTRL0_PCLKEN_MASK            0x1
#define GCONF_GDMAC_CTRL0_PCLKEN_SHIFT           0 
#define GCONF_GDMAC_CTRL0_PCLKEN_BIT             0x1
#define GCONF_GDMAC_CTRL0_PCLKEN_BITWIDTH        1
// BOOT_FROM_PC bitfiled (RW) Reset=0
#define GCONF_GDMAC_CTRL0_BOOT_FROM_PC_MASK      0x2
#define GCONF_GDMAC_CTRL0_BOOT_FROM_PC_SHIFT     1 
#define GCONF_GDMAC_CTRL0_BOOT_FROM_PC_BIT       0x1
#define GCONF_GDMAC_CTRL0_BOOT_FROM_PC_BITWIDTH  1
// BOOT_MANAGER_NS bitfiled (RW) Reset=1
#define GCONF_GDMAC_CTRL0_BOOT_MANAGER_NS_MASK   0x4
#define GCONF_GDMAC_CTRL0_BOOT_MANAGER_NS_SHIFT  2 
#define GCONF_GDMAC_CTRL0_BOOT_MANAGER_NS_BIT    0x1
#define GCONF_GDMAC_CTRL0_BOOT_MANAGER_NS_BITWIDTH 1
// reserved bitfiled (RO) Reset=0
#define GCONF_GDMAC_CTRL0_RESERVED_MASK          0xFFFFFFF8
#define GCONF_GDMAC_CTRL0_RESERVED_SHIFT         3 
#define GCONF_GDMAC_CTRL0_RESERVED_BIT           0x1FFFFFFF
#define GCONF_GDMAC_CTRL0_RESERVED_BITWIDTH      29
// GDMAC_CTRL1 Register
#define GCONF_GDMAC_CTRL1_OFS                    0x00000044
// BOOT_ADDR bitfiled (RW) Reset=0
#define GCONF_GDMAC_CTRL1_BOOT_ADDR_MASK         0xFFFFFFFF
#define GCONF_GDMAC_CTRL1_BOOT_ADDR_SHIFT        0 
#define GCONF_GDMAC_CTRL1_BOOT_ADDR_BIT          0xFFFFFFFF
#define GCONF_GDMAC_CTRL1_BOOT_ADDR_BITWIDTH     32
// GDMAC_CTRL2 Register
#define GCONF_GDMAC_CTRL2_OFS                    0x00000048
// BOOT_IRQ_NS bitfiled (RW) Reset=11111111111111111111111111111111
#define GCONF_GDMAC_CTRL2_BOOT_IRQ_NS_MASK       0xFFFFFFFF
#define GCONF_GDMAC_CTRL2_BOOT_IRQ_NS_SHIFT      0 
#define GCONF_GDMAC_CTRL2_BOOT_IRQ_NS_BIT        0xFFFFFFFF
#define GCONF_GDMAC_CTRL2_BOOT_IRQ_NS_BITWIDTH   32
// GDMAC_CTRL3 Register
#define GCONF_GDMAC_CTRL3_OFS                    0x0000004C
// BOOT_PERIPH_NS bitfiled (RW) Reset=11111111111111111111111111111111
#define GCONF_GDMAC_CTRL3_BOOT_PERIPH_NS_MASK    0xFFFFFFFF
#define GCONF_GDMAC_CTRL3_BOOT_PERIPH_NS_SHIFT   0 
#define GCONF_GDMAC_CTRL3_BOOT_PERIPH_NS_BIT     0xFFFFFFFF
#define GCONF_GDMAC_CTRL3_BOOT_PERIPH_NS_BITWIDTH 32
// GDMAC_CTRL4 Register
#define GCONF_GDMAC_CTRL4_OFS                    0x00000050
// SYNCSEL bitfiled (RW) Reset=0
#define GCONF_GDMAC_CTRL4_SYNCSEL_MASK           0x3FFFFFFF
#define GCONF_GDMAC_CTRL4_SYNCSEL_SHIFT          0 
#define GCONF_GDMAC_CTRL4_SYNCSEL_BIT            0x3FFFFFFF
#define GCONF_GDMAC_CTRL4_SYNCSEL_BITWIDTH       30
// reserved bitfiled (RO) Reset=0
#define GCONF_GDMAC_CTRL4_RESERVED_MASK          0xC0000000
#define GCONF_GDMAC_CTRL4_RESERVED_SHIFT         30 
#define GCONF_GDMAC_CTRL4_RESERVED_BIT           0x3
#define GCONF_GDMAC_CTRL4_RESERVED_BITWIDTH      2
// GDMAC_CTRL5 Register
#define GCONF_GDMAC_CTRL5_OFS                    0x00000054
// ENABLE_DMACTC bitfiled (RW) Reset=0
#define GCONF_GDMAC_CTRL5_ENABLE_DMACTC_MASK     0x3FFFFFFF
#define GCONF_GDMAC_CTRL5_ENABLE_DMACTC_SHIFT    0 
#define GCONF_GDMAC_CTRL5_ENABLE_DMACTC_BIT      0x3FFFFFFF
#define GCONF_GDMAC_CTRL5_ENABLE_DMACTC_BITWIDTH 30
// reserved bitfiled (RO) Reset=0
#define GCONF_GDMAC_CTRL5_RESERVED_MASK          0xC0000000
#define GCONF_GDMAC_CTRL5_RESERVED_SHIFT         30 
#define GCONF_GDMAC_CTRL5_RESERVED_BIT           0x3
#define GCONF_GDMAC_CTRL5_RESERVED_BITWIDTH      2

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _GCONF_REG_DEF_H */
