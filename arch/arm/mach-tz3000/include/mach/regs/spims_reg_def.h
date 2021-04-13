/*
 * arch/arm/mach-tz3000/include/mach/regs/spims_reg_def.h
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

#ifndef _SPIMS_REG_DEF_H
#define _SPIMS_REG_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

// SPI_RXDATA0 Register
#define SPIMS_SPI_RXDATA0_OFS                    0x00000000
// RXDATA bitfiled (RO) Reset=0
#define SPIMS_SPI_RXDATA0_RXDATA_MASK            0xFFFFFFFF
#define SPIMS_SPI_RXDATA0_RXDATA_SHIFT           0 
#define SPIMS_SPI_RXDATA0_RXDATA_BIT             0xFFFFFFFF
#define SPIMS_SPI_RXDATA0_RXDATA_BITWIDTH        32
// SPI_TXDATA0 Register
#define SPIMS_SPI_TXDATA0_OFS                    0x00000004
// TXDATA bitfiled (RW) Reset=0
#define SPIMS_SPI_TXDATA0_TXDATA_MASK            0xFFFFFFFF
#define SPIMS_SPI_TXDATA0_TXDATA_SHIFT           0 
#define SPIMS_SPI_TXDATA0_TXDATA_BIT             0xFFFFFFFF
#define SPIMS_SPI_TXDATA0_TXDATA_BITWIDTH        32
// SPI_SELECT0 Register
#define SPIMS_SPI_SELECT0_OFS                    0x00000008
// MASTER bitfiled (RW) Reset=0
#define SPIMS_SPI_SELECT0_MASTER_MASK            0x1
#define SPIMS_SPI_SELECT0_MASTER_SHIFT           0 
#define SPIMS_SPI_SELECT0_MASTER_BIT             0x1
#define SPIMS_SPI_SELECT0_MASTER_BITWIDTH        1
// reserved2 bitfiled (RO) Reset=0
#define SPIMS_SPI_SELECT0_RESERVED2_MASK         0xFFFE
#define SPIMS_SPI_SELECT0_RESERVED2_SHIFT        1 
#define SPIMS_SPI_SELECT0_RESERVED2_BIT          0x7FFF
#define SPIMS_SPI_SELECT0_RESERVED2_BITWIDTH     15
// CPHA bitfiled (RW) Reset=0
#define SPIMS_SPI_SELECT0_CPHA_MASK              0x10000
#define SPIMS_SPI_SELECT0_CPHA_SHIFT             16 
#define SPIMS_SPI_SELECT0_CPHA_BIT               0x1
#define SPIMS_SPI_SELECT0_CPHA_BITWIDTH          1
// CPOL bitfiled (RW) Reset=0
#define SPIMS_SPI_SELECT0_CPOL_MASK              0x20000
#define SPIMS_SPI_SELECT0_CPOL_SHIFT             17 
#define SPIMS_SPI_SELECT0_CPOL_BIT               0x1
#define SPIMS_SPI_SELECT0_CPOL_BITWIDTH          1
// reserved bitfiled (RO) Reset=0
#define SPIMS_SPI_SELECT0_RESERVED_MASK          0xFFFC0000
#define SPIMS_SPI_SELECT0_RESERVED_SHIFT         18 
#define SPIMS_SPI_SELECT0_RESERVED_BIT           0x3FFF
#define SPIMS_SPI_SELECT0_RESERVED_BITWIDTH      14
// SPI_DIV0 Register
#define SPIMS_SPI_DIV0_OFS                       0x0000000C
// SCALE bitfiled (RW) Reset=1
#define SPIMS_SPI_DIV0_SCALE_MASK                0x7
#define SPIMS_SPI_DIV0_SCALE_SHIFT               0 
#define SPIMS_SPI_DIV0_SCALE_BIT                 0x7
#define SPIMS_SPI_DIV0_SCALE_BITWIDTH            3
// reserved bitfiled (RO) Reset=0
#define SPIMS_SPI_DIV0_RESERVED_MASK             0x7FFFFFF8
#define SPIMS_SPI_DIV0_RESERVED_SHIFT            3 
#define SPIMS_SPI_DIV0_RESERVED_BIT              0xFFFFFFF
#define SPIMS_SPI_DIV0_RESERVED_BITWIDTH         28
// DUMMY bitfiled (RW) Reset=0
#define SPIMS_SPI_DIV0_DUMMY_MASK                0x80000000
#define SPIMS_SPI_DIV0_DUMMY_SHIFT               31 
#define SPIMS_SPI_DIV0_DUMMY_BIT                 0x1
#define SPIMS_SPI_DIV0_DUMMY_BITWIDTH            1
// SPI_ENABLE0 Register
#define SPIMS_SPI_ENABLE0_OFS                    0x00000010
// ENABLE bitfiled (RW) Reset=0
#define SPIMS_SPI_ENABLE0_ENABLE_MASK            0x1
#define SPIMS_SPI_ENABLE0_ENABLE_SHIFT           0 
#define SPIMS_SPI_ENABLE0_ENABLE_BIT             0x1
#define SPIMS_SPI_ENABLE0_ENABLE_BITWIDTH        1
// reserved bitfiled (RO) Reset=0
#define SPIMS_SPI_ENABLE0_RESERVED_MASK          0xFFFFFFFE
#define SPIMS_SPI_ENABLE0_RESERVED_SHIFT         1 
#define SPIMS_SPI_ENABLE0_RESERVED_BIT           0x7FFFFFFF
#define SPIMS_SPI_ENABLE0_RESERVED_BITWIDTH      31
// SPI_FRAME0 Register
#define SPIMS_SPI_FRAME0_OFS                     0x00000014
// LENGTH bitfiled (RW) Reset=0
#define SPIMS_SPI_FRAME0_LENGTH_MASK             0x1F
#define SPIMS_SPI_FRAME0_LENGTH_SHIFT            0 
#define SPIMS_SPI_FRAME0_LENGTH_BIT              0x1F
#define SPIMS_SPI_FRAME0_LENGTH_BITWIDTH         5
// reserved3 bitfiled (RO) Reset=0
#define SPIMS_SPI_FRAME0_RESERVED3_MASK          0xE0
#define SPIMS_SPI_FRAME0_RESERVED3_SHIFT         5 
#define SPIMS_SPI_FRAME0_RESERVED3_BIT           0x7
#define SPIMS_SPI_FRAME0_RESERVED3_BITWIDTH      3
// MSB bitfiled (RW) Reset=0
#define SPIMS_SPI_FRAME0_MSB_MASK                0x100
#define SPIMS_SPI_FRAME0_MSB_SHIFT               8 
#define SPIMS_SPI_FRAME0_MSB_BIT                 0x1
#define SPIMS_SPI_FRAME0_MSB_BITWIDTH            1
// SCSHOLD bitfiled (RW) Reset=0
#define SPIMS_SPI_FRAME0_SCSHOLD_MASK            0x200
#define SPIMS_SPI_FRAME0_SCSHOLD_SHIFT           9 
#define SPIMS_SPI_FRAME0_SCSHOLD_BIT             0x1
#define SPIMS_SPI_FRAME0_SCSHOLD_BITWIDTH        1
// reserved2 bitfiled (RO) Reset=0
#define SPIMS_SPI_FRAME0_RESERVED2_MASK          0xFC00
#define SPIMS_SPI_FRAME0_RESERVED2_SHIFT         10 
#define SPIMS_SPI_FRAME0_RESERVED2_BIT           0x3F
#define SPIMS_SPI_FRAME0_RESERVED2_BITWIDTH      6
// SCK bitfiled (RW) Reset=0
#define SPIMS_SPI_FRAME0_SCK_MASK                0x10000
#define SPIMS_SPI_FRAME0_SCK_SHIFT               16 
#define SPIMS_SPI_FRAME0_SCK_BIT                 0x1
#define SPIMS_SPI_FRAME0_SCK_BITWIDTH            1
// SCS bitfiled (RW) Reset=0
#define SPIMS_SPI_FRAME0_SCS_MASK                0x20000
#define SPIMS_SPI_FRAME0_SCS_SHIFT               17 
#define SPIMS_SPI_FRAME0_SCS_BIT                 0x1
#define SPIMS_SPI_FRAME0_SCS_BITWIDTH            1
// reserved bitfiled (RO) Reset=0
#define SPIMS_SPI_FRAME0_RESERVED_MASK           0x7FFC0000
#define SPIMS_SPI_FRAME0_RESERVED_SHIFT          18 
#define SPIMS_SPI_FRAME0_RESERVED_BIT            0x1FFF
#define SPIMS_SPI_FRAME0_RESERVED_BITWIDTH       13
// MODE bitfiled (RW) Reset=0
#define SPIMS_SPI_FRAME0_MODE_MASK               0x80000000
#define SPIMS_SPI_FRAME0_MODE_SHIFT              31 
#define SPIMS_SPI_FRAME0_MODE_BIT                0x1
#define SPIMS_SPI_FRAME0_MODE_BITWIDTH           1
// SPI_FIFOCLR0 Register
#define SPIMS_SPI_FIFOCLR0_OFS                   0x00000018
// TXFIFOINIT bitfiled (RW) Reset=0
#define SPIMS_SPI_FIFOCLR0_TXFIFOINIT_MASK       0x1
#define SPIMS_SPI_FIFOCLR0_TXFIFOINIT_SHIFT      0 
#define SPIMS_SPI_FIFOCLR0_TXFIFOINIT_BIT        0x1
#define SPIMS_SPI_FIFOCLR0_TXFIFOINIT_BITWIDTH   1
// RXFIFOINIT bitfiled (RW) Reset=0
#define SPIMS_SPI_FIFOCLR0_RXFIFOINIT_MASK       0x2
#define SPIMS_SPI_FIFOCLR0_RXFIFOINIT_SHIFT      1 
#define SPIMS_SPI_FIFOCLR0_RXFIFOINIT_BIT        0x1
#define SPIMS_SPI_FIFOCLR0_RXFIFOINIT_BITWIDTH   1
// reserved bitfiled (RO) Reset=0
#define SPIMS_SPI_FIFOCLR0_RESERVED_MASK         0xFFFFFFFC
#define SPIMS_SPI_FIFOCLR0_RESERVED_SHIFT        2 
#define SPIMS_SPI_FIFOCLR0_RESERVED_BIT          0x3FFFFFFF
#define SPIMS_SPI_FIFOCLR0_RESERVED_BITWIDTH     30
// SPI_IC0 Register
#define SPIMS_SPI_IC0_OFS                        0x0000001C
// FIFOCOND bitfiled (RW) Reset=0
#define SPIMS_SPI_IC0_FIFOCOND_MASK              0xFF
#define SPIMS_SPI_IC0_FIFOCOND_SHIFT             0 
#define SPIMS_SPI_IC0_FIFOCOND_BIT               0xFF
#define SPIMS_SPI_IC0_FIFOCOND_BITWIDTH          8
// reserved bitfiled (RO) Reset=0
#define SPIMS_SPI_IC0_RESERVED_MASK              0xFFFFFF00
#define SPIMS_SPI_IC0_RESERVED_SHIFT             8 
#define SPIMS_SPI_IC0_RESERVED_BIT               0xFFFFFF
#define SPIMS_SPI_IC0_RESERVED_BITWIDTH          24
// SPI_IE0 Register
#define SPIMS_SPI_IE0_OFS                        0x00000020
// INTENB bitfiled (RW) Reset=0
#define SPIMS_SPI_IE0_INTENB_MASK                0x1
#define SPIMS_SPI_IE0_INTENB_SHIFT               0 
#define SPIMS_SPI_IE0_INTENB_BIT                 0x1
#define SPIMS_SPI_IE0_INTENB_BITWIDTH            1
// reserved2 bitfiled (RO) Reset=0
#define SPIMS_SPI_IE0_RESERVED2_MASK             0xFE
#define SPIMS_SPI_IE0_RESERVED2_SHIFT            1 
#define SPIMS_SPI_IE0_RESERVED2_BIT              0x7F
#define SPIMS_SPI_IE0_RESERVED2_BITWIDTH         7
// RXUDFINTENB bitfiled (RW) Reset=0
#define SPIMS_SPI_IE0_RXUDFINTENB_MASK           0x100
#define SPIMS_SPI_IE0_RXUDFINTENB_SHIFT          8 
#define SPIMS_SPI_IE0_RXUDFINTENB_BIT            0x1
#define SPIMS_SPI_IE0_RXUDFINTENB_BITWIDTH       1
// RXOVFINTENB bitfiled (RW) Reset=0
#define SPIMS_SPI_IE0_RXOVFINTENB_MASK           0x200
#define SPIMS_SPI_IE0_RXOVFINTENB_SHIFT          9 
#define SPIMS_SPI_IE0_RXOVFINTENB_BIT            0x1
#define SPIMS_SPI_IE0_RXOVFINTENB_BITWIDTH       1
// TXUDFINTENB bitfiled (RW) Reset=0
#define SPIMS_SPI_IE0_TXUDFINTENB_MASK           0x400
#define SPIMS_SPI_IE0_TXUDFINTENB_SHIFT          10 
#define SPIMS_SPI_IE0_TXUDFINTENB_BIT            0x1
#define SPIMS_SPI_IE0_TXUDFINTENB_BITWIDTH       1
// TXOVFINTENB bitfiled (RW) Reset=0
#define SPIMS_SPI_IE0_TXOVFINTENB_MASK           0x800
#define SPIMS_SPI_IE0_TXOVFINTENB_SHIFT          11 
#define SPIMS_SPI_IE0_TXOVFINTENB_BIT            0x1
#define SPIMS_SPI_IE0_TXOVFINTENB_BITWIDTH       1
// reserved bitfiled (RO) Reset=0
#define SPIMS_SPI_IE0_RESERVED_MASK              0xFFFFF000
#define SPIMS_SPI_IE0_RESERVED_SHIFT             12 
#define SPIMS_SPI_IE0_RESERVED_BIT               0xFFFFF
#define SPIMS_SPI_IE0_RESERVED_BITWIDTH          20
// SPI_IS0 Register
#define SPIMS_SPI_IS0_OFS                        0x00000024
// INTSTATUS bitfiled (RW) Reset=0
#define SPIMS_SPI_IS0_INTSTATUS_MASK             0x1
#define SPIMS_SPI_IS0_INTSTATUS_SHIFT            0 
#define SPIMS_SPI_IS0_INTSTATUS_BIT              0x1
#define SPIMS_SPI_IS0_INTSTATUS_BITWIDTH         1
// reserved2 bitfiled (RO) Reset=0
#define SPIMS_SPI_IS0_RESERVED2_MASK             0xFE
#define SPIMS_SPI_IS0_RESERVED2_SHIFT            1 
#define SPIMS_SPI_IS0_RESERVED2_BIT              0x7F
#define SPIMS_SPI_IS0_RESERVED2_BITWIDTH         7
// RXUDFINTSTATUS bitfiled (RW) Reset=0
#define SPIMS_SPI_IS0_RXUDFINTSTATUS_MASK        0x100
#define SPIMS_SPI_IS0_RXUDFINTSTATUS_SHIFT       8 
#define SPIMS_SPI_IS0_RXUDFINTSTATUS_BIT         0x1
#define SPIMS_SPI_IS0_RXUDFINTSTATUS_BITWIDTH    1
// RXOVFINTSTATUS bitfiled (RW) Reset=0
#define SPIMS_SPI_IS0_RXOVFINTSTATUS_MASK        0x200
#define SPIMS_SPI_IS0_RXOVFINTSTATUS_SHIFT       9 
#define SPIMS_SPI_IS0_RXOVFINTSTATUS_BIT         0x1
#define SPIMS_SPI_IS0_RXOVFINTSTATUS_BITWIDTH    1
// TXUDFINTSTATUS bitfiled (RW) Reset=0
#define SPIMS_SPI_IS0_TXUDFINTSTATUS_MASK        0x400
#define SPIMS_SPI_IS0_TXUDFINTSTATUS_SHIFT       10 
#define SPIMS_SPI_IS0_TXUDFINTSTATUS_BIT         0x1
#define SPIMS_SPI_IS0_TXUDFINTSTATUS_BITWIDTH    1
// TXOVFINTSTATUS bitfiled (RW) Reset=0
#define SPIMS_SPI_IS0_TXOVFINTSTATUS_MASK        0x800
#define SPIMS_SPI_IS0_TXOVFINTSTATUS_SHIFT       11 
#define SPIMS_SPI_IS0_TXOVFINTSTATUS_BIT         0x1
#define SPIMS_SPI_IS0_TXOVFINTSTATUS_BITWIDTH    1
// reserved bitfiled (RO) Reset=0
#define SPIMS_SPI_IS0_RESERVED_MASK              0xFFFFF000
#define SPIMS_SPI_IS0_RESERVED_SHIFT             12 
#define SPIMS_SPI_IS0_RESERVED_BIT               0xFFFFF
#define SPIMS_SPI_IS0_RESERVED_BITWIDTH          20
// SPI_RXFIFONMB0 Register
#define SPIMS_SPI_RXFIFONMB0_OFS                 0x00000028
// NUMBER bitfiled (RO) Reset=0
#define SPIMS_SPI_RXFIFONMB0_NUMBER_MASK         0xFF
#define SPIMS_SPI_RXFIFONMB0_NUMBER_SHIFT        0 
#define SPIMS_SPI_RXFIFONMB0_NUMBER_BIT          0xFF
#define SPIMS_SPI_RXFIFONMB0_NUMBER_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define SPIMS_SPI_RXFIFONMB0_RESERVED_MASK       0xFFFFFF00
#define SPIMS_SPI_RXFIFONMB0_RESERVED_SHIFT      8 
#define SPIMS_SPI_RXFIFONMB0_RESERVED_BIT        0xFFFFFF
#define SPIMS_SPI_RXFIFONMB0_RESERVED_BITWIDTH   24
// SPI_TXFIFONMB0 Register
#define SPIMS_SPI_TXFIFONMB0_OFS                 0x0000002C
// NUMBER bitfiled (RO) Reset=0
#define SPIMS_SPI_TXFIFONMB0_NUMBER_MASK         0xFF
#define SPIMS_SPI_TXFIFONMB0_NUMBER_SHIFT        0 
#define SPIMS_SPI_TXFIFONMB0_NUMBER_BIT          0xFF
#define SPIMS_SPI_TXFIFONMB0_NUMBER_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define SPIMS_SPI_TXFIFONMB0_RESERVED_MASK       0xFFFFFF00
#define SPIMS_SPI_TXFIFONMB0_RESERVED_SHIFT      8 
#define SPIMS_SPI_TXFIFONMB0_RESERVED_BIT        0xFFFFFF
#define SPIMS_SPI_TXFIFONMB0_RESERVED_BITWIDTH   24
// SPI_RXDATA1 Register
#define SPIMS_SPI_RXDATA1_OFS                    0x00010000
// RXDATA bitfiled (RO) Reset=0
#define SPIMS_SPI_RXDATA1_RXDATA_MASK            0xFFFFFFFF
#define SPIMS_SPI_RXDATA1_RXDATA_SHIFT           0 
#define SPIMS_SPI_RXDATA1_RXDATA_BIT             0xFFFFFFFF
#define SPIMS_SPI_RXDATA1_RXDATA_BITWIDTH        32
// SPI_TXDATA1 Register
#define SPIMS_SPI_TXDATA1_OFS                    0x00010004
// TXDATA bitfiled (RW) Reset=0
#define SPIMS_SPI_TXDATA1_TXDATA_MASK            0xFFFFFFFF
#define SPIMS_SPI_TXDATA1_TXDATA_SHIFT           0 
#define SPIMS_SPI_TXDATA1_TXDATA_BIT             0xFFFFFFFF
#define SPIMS_SPI_TXDATA1_TXDATA_BITWIDTH        32
// SPI_SELECT1 Register
#define SPIMS_SPI_SELECT1_OFS                    0x00010008
// MASTER bitfiled (RW) Reset=0
#define SPIMS_SPI_SELECT1_MASTER_MASK            0x1
#define SPIMS_SPI_SELECT1_MASTER_SHIFT           0 
#define SPIMS_SPI_SELECT1_MASTER_BIT             0x1
#define SPIMS_SPI_SELECT1_MASTER_BITWIDTH        1
// reserved2 bitfiled (RO) Reset=0
#define SPIMS_SPI_SELECT1_RESERVED2_MASK         0xFFFE
#define SPIMS_SPI_SELECT1_RESERVED2_SHIFT        1 
#define SPIMS_SPI_SELECT1_RESERVED2_BIT          0x7FFF
#define SPIMS_SPI_SELECT1_RESERVED2_BITWIDTH     15
// CPHA bitfiled (RW) Reset=0
#define SPIMS_SPI_SELECT1_CPHA_MASK              0x10000
#define SPIMS_SPI_SELECT1_CPHA_SHIFT             16 
#define SPIMS_SPI_SELECT1_CPHA_BIT               0x1
#define SPIMS_SPI_SELECT1_CPHA_BITWIDTH          1
// CPOL bitfiled (RW) Reset=0
#define SPIMS_SPI_SELECT1_CPOL_MASK              0x20000
#define SPIMS_SPI_SELECT1_CPOL_SHIFT             17 
#define SPIMS_SPI_SELECT1_CPOL_BIT               0x1
#define SPIMS_SPI_SELECT1_CPOL_BITWIDTH          1
// reserved bitfiled (RO) Reset=0
#define SPIMS_SPI_SELECT1_RESERVED_MASK          0xFFFC0000
#define SPIMS_SPI_SELECT1_RESERVED_SHIFT         18 
#define SPIMS_SPI_SELECT1_RESERVED_BIT           0x3FFF
#define SPIMS_SPI_SELECT1_RESERVED_BITWIDTH      14
// SPI_DIV1 Register
#define SPIMS_SPI_DIV1_OFS                       0x0001000C
// SCALE bitfiled (RW) Reset=0
#define SPIMS_SPI_DIV1_SCALE_MASK                0x7
#define SPIMS_SPI_DIV1_SCALE_SHIFT               0 
#define SPIMS_SPI_DIV1_SCALE_BIT                 0x7
#define SPIMS_SPI_DIV1_SCALE_BITWIDTH            3
// reserved bitfiled (RO) Reset=0
#define SPIMS_SPI_DIV1_RESERVED_MASK             0x7FFFFFF8
#define SPIMS_SPI_DIV1_RESERVED_SHIFT            3 
#define SPIMS_SPI_DIV1_RESERVED_BIT              0xFFFFFFF
#define SPIMS_SPI_DIV1_RESERVED_BITWIDTH         28
// DUMMY bitfiled (RW) Reset=0
#define SPIMS_SPI_DIV1_DUMMY_MASK                0x80000000
#define SPIMS_SPI_DIV1_DUMMY_SHIFT               31 
#define SPIMS_SPI_DIV1_DUMMY_BIT                 0x1
#define SPIMS_SPI_DIV1_DUMMY_BITWIDTH            1
// SPI_ENABLE1 Register
#define SPIMS_SPI_ENABLE1_OFS                    0x00010010
// ENABLE bitfiled (RW) Reset=0
#define SPIMS_SPI_ENABLE1_ENABLE_MASK            0x1
#define SPIMS_SPI_ENABLE1_ENABLE_SHIFT           0 
#define SPIMS_SPI_ENABLE1_ENABLE_BIT             0x1
#define SPIMS_SPI_ENABLE1_ENABLE_BITWIDTH        1
// reserved bitfiled (RO) Reset=0
#define SPIMS_SPI_ENABLE1_RESERVED_MASK          0xFFFFFFFE
#define SPIMS_SPI_ENABLE1_RESERVED_SHIFT         1 
#define SPIMS_SPI_ENABLE1_RESERVED_BIT           0x7FFFFFFF
#define SPIMS_SPI_ENABLE1_RESERVED_BITWIDTH      31
// SPI_FRAME1 Register
#define SPIMS_SPI_FRAME1_OFS                     0x00010014
// LENGTH bitfiled (RW) Reset=0
#define SPIMS_SPI_FRAME1_LENGTH_MASK             0x1F
#define SPIMS_SPI_FRAME1_LENGTH_SHIFT            0 
#define SPIMS_SPI_FRAME1_LENGTH_BIT              0x1F
#define SPIMS_SPI_FRAME1_LENGTH_BITWIDTH         5
// reserved3 bitfiled (RO) Reset=0
#define SPIMS_SPI_FRAME1_RESERVED3_MASK          0xE0
#define SPIMS_SPI_FRAME1_RESERVED3_SHIFT         5 
#define SPIMS_SPI_FRAME1_RESERVED3_BIT           0x7
#define SPIMS_SPI_FRAME1_RESERVED3_BITWIDTH      3
// MSB bitfiled (RW) Reset=0
#define SPIMS_SPI_FRAME1_MSB_MASK                0x100
#define SPIMS_SPI_FRAME1_MSB_SHIFT               8 
#define SPIMS_SPI_FRAME1_MSB_BIT                 0x1
#define SPIMS_SPI_FRAME1_MSB_BITWIDTH            1
// SCSHOLD bitfiled (RW) Reset=0
#define SPIMS_SPI_FRAME1_SCSHOLD_MASK            0x200
#define SPIMS_SPI_FRAME1_SCSHOLD_SHIFT           9 
#define SPIMS_SPI_FRAME1_SCSHOLD_BIT             0x1
#define SPIMS_SPI_FRAME1_SCSHOLD_BITWIDTH        1
// reserved2 bitfiled (RO) Reset=0
#define SPIMS_SPI_FRAME1_RESERVED2_MASK          0xFC00
#define SPIMS_SPI_FRAME1_RESERVED2_SHIFT         10 
#define SPIMS_SPI_FRAME1_RESERVED2_BIT           0x3F
#define SPIMS_SPI_FRAME1_RESERVED2_BITWIDTH      6
// SCK bitfiled (RW) Reset=0
#define SPIMS_SPI_FRAME1_SCK_MASK                0x10000
#define SPIMS_SPI_FRAME1_SCK_SHIFT               16 
#define SPIMS_SPI_FRAME1_SCK_BIT                 0x1
#define SPIMS_SPI_FRAME1_SCK_BITWIDTH            1
// SCS bitfiled (RW) Reset=0
#define SPIMS_SPI_FRAME1_SCS_MASK                0x20000
#define SPIMS_SPI_FRAME1_SCS_SHIFT               17 
#define SPIMS_SPI_FRAME1_SCS_BIT                 0x1
#define SPIMS_SPI_FRAME1_SCS_BITWIDTH            1
// reserved bitfiled (RO) Reset=0
#define SPIMS_SPI_FRAME1_RESERVED_MASK           0x7FFC0000
#define SPIMS_SPI_FRAME1_RESERVED_SHIFT          18 
#define SPIMS_SPI_FRAME1_RESERVED_BIT            0x1FFF
#define SPIMS_SPI_FRAME1_RESERVED_BITWIDTH       13
// MODE bitfiled (RW) Reset=0
#define SPIMS_SPI_FRAME1_MODE_MASK               0x80000000
#define SPIMS_SPI_FRAME1_MODE_SHIFT              31 
#define SPIMS_SPI_FRAME1_MODE_BIT                0x1
#define SPIMS_SPI_FRAME1_MODE_BITWIDTH           1
// SPI_FIFOCLR1 Register
#define SPIMS_SPI_FIFOCLR1_OFS                   0x00010018
// TXFIFOINIT bitfiled (RW) Reset=0
#define SPIMS_SPI_FIFOCLR1_TXFIFOINIT_MASK       0x1
#define SPIMS_SPI_FIFOCLR1_TXFIFOINIT_SHIFT      0 
#define SPIMS_SPI_FIFOCLR1_TXFIFOINIT_BIT        0x1
#define SPIMS_SPI_FIFOCLR1_TXFIFOINIT_BITWIDTH   1
// RXFIFOINIT bitfiled (RW) Reset=0
#define SPIMS_SPI_FIFOCLR1_RXFIFOINIT_MASK       0x2
#define SPIMS_SPI_FIFOCLR1_RXFIFOINIT_SHIFT      1 
#define SPIMS_SPI_FIFOCLR1_RXFIFOINIT_BIT        0x1
#define SPIMS_SPI_FIFOCLR1_RXFIFOINIT_BITWIDTH   1
// reserved bitfiled (RO) Reset=0
#define SPIMS_SPI_FIFOCLR1_RESERVED_MASK         0xFFFFFFFC
#define SPIMS_SPI_FIFOCLR1_RESERVED_SHIFT        2 
#define SPIMS_SPI_FIFOCLR1_RESERVED_BIT          0x3FFFFFFF
#define SPIMS_SPI_FIFOCLR1_RESERVED_BITWIDTH     30
// SPI_IC1 Register
#define SPIMS_SPI_IC1_OFS                        0x0001001C
// FIFOCOND bitfiled (RW) Reset=0
#define SPIMS_SPI_IC1_FIFOCOND_MASK              0xFF
#define SPIMS_SPI_IC1_FIFOCOND_SHIFT             0 
#define SPIMS_SPI_IC1_FIFOCOND_BIT               0xFF
#define SPIMS_SPI_IC1_FIFOCOND_BITWIDTH          8
// reserved bitfiled (RO) Reset=0
#define SPIMS_SPI_IC1_RESERVED_MASK              0xFFFFFF00
#define SPIMS_SPI_IC1_RESERVED_SHIFT             8 
#define SPIMS_SPI_IC1_RESERVED_BIT               0xFFFFFF
#define SPIMS_SPI_IC1_RESERVED_BITWIDTH          24
// SPI_IE1 Register
#define SPIMS_SPI_IE1_OFS                        0x00010020
// INTENB bitfiled (RW) Reset=0
#define SPIMS_SPI_IE1_INTENB_MASK                0x1
#define SPIMS_SPI_IE1_INTENB_SHIFT               0 
#define SPIMS_SPI_IE1_INTENB_BIT                 0x1
#define SPIMS_SPI_IE1_INTENB_BITWIDTH            1
// reserved2 bitfiled (RO) Reset=0
#define SPIMS_SPI_IE1_RESERVED2_MASK             0xFE
#define SPIMS_SPI_IE1_RESERVED2_SHIFT            1 
#define SPIMS_SPI_IE1_RESERVED2_BIT              0x7F
#define SPIMS_SPI_IE1_RESERVED2_BITWIDTH         7
// RXUDFINTENB bitfiled (RW) Reset=0
#define SPIMS_SPI_IE1_RXUDFINTENB_MASK           0x100
#define SPIMS_SPI_IE1_RXUDFINTENB_SHIFT          8 
#define SPIMS_SPI_IE1_RXUDFINTENB_BIT            0x1
#define SPIMS_SPI_IE1_RXUDFINTENB_BITWIDTH       1
// RXOVFINTENB bitfiled (RW) Reset=0
#define SPIMS_SPI_IE1_RXOVFINTENB_MASK           0x200
#define SPIMS_SPI_IE1_RXOVFINTENB_SHIFT          9 
#define SPIMS_SPI_IE1_RXOVFINTENB_BIT            0x1
#define SPIMS_SPI_IE1_RXOVFINTENB_BITWIDTH       1
// TXUDFINTENB bitfiled (RW) Reset=0
#define SPIMS_SPI_IE1_TXUDFINTENB_MASK           0x400
#define SPIMS_SPI_IE1_TXUDFINTENB_SHIFT          10 
#define SPIMS_SPI_IE1_TXUDFINTENB_BIT            0x1
#define SPIMS_SPI_IE1_TXUDFINTENB_BITWIDTH       1
// TXOVFINTENB bitfiled (RW) Reset=0
#define SPIMS_SPI_IE1_TXOVFINTENB_MASK           0x800
#define SPIMS_SPI_IE1_TXOVFINTENB_SHIFT          11 
#define SPIMS_SPI_IE1_TXOVFINTENB_BIT            0x1
#define SPIMS_SPI_IE1_TXOVFINTENB_BITWIDTH       1
// reserved bitfiled (RO) Reset=0
#define SPIMS_SPI_IE1_RESERVED_MASK              0xFFFFF000
#define SPIMS_SPI_IE1_RESERVED_SHIFT             12 
#define SPIMS_SPI_IE1_RESERVED_BIT               0xFFFFF
#define SPIMS_SPI_IE1_RESERVED_BITWIDTH          20
// SPI_IS1 Register
#define SPIMS_SPI_IS1_OFS                        0x00010024
// INTSTATUS bitfiled (RW) Reset=0
#define SPIMS_SPI_IS1_INTSTATUS_MASK             0x1
#define SPIMS_SPI_IS1_INTSTATUS_SHIFT            0 
#define SPIMS_SPI_IS1_INTSTATUS_BIT              0x1
#define SPIMS_SPI_IS1_INTSTATUS_BITWIDTH         1
// reserved2 bitfiled (RO) Reset=0
#define SPIMS_SPI_IS1_RESERVED2_MASK             0xFE
#define SPIMS_SPI_IS1_RESERVED2_SHIFT            1 
#define SPIMS_SPI_IS1_RESERVED2_BIT              0x7F
#define SPIMS_SPI_IS1_RESERVED2_BITWIDTH         7
// RXUDFINTSTATUS bitfiled (RW) Reset=0
#define SPIMS_SPI_IS1_RXUDFINTSTATUS_MASK        0x100
#define SPIMS_SPI_IS1_RXUDFINTSTATUS_SHIFT       8 
#define SPIMS_SPI_IS1_RXUDFINTSTATUS_BIT         0x1
#define SPIMS_SPI_IS1_RXUDFINTSTATUS_BITWIDTH    1
// RXOVFINTSTATUS bitfiled (RW) Reset=0
#define SPIMS_SPI_IS1_RXOVFINTSTATUS_MASK        0x200
#define SPIMS_SPI_IS1_RXOVFINTSTATUS_SHIFT       9 
#define SPIMS_SPI_IS1_RXOVFINTSTATUS_BIT         0x1
#define SPIMS_SPI_IS1_RXOVFINTSTATUS_BITWIDTH    1
// TXUDFINTSTATUS bitfiled (RW) Reset=0
#define SPIMS_SPI_IS1_TXUDFINTSTATUS_MASK        0x400
#define SPIMS_SPI_IS1_TXUDFINTSTATUS_SHIFT       10 
#define SPIMS_SPI_IS1_TXUDFINTSTATUS_BIT         0x1
#define SPIMS_SPI_IS1_TXUDFINTSTATUS_BITWIDTH    1
// TXOVFINTSTATUS bitfiled (RW) Reset=0
#define SPIMS_SPI_IS1_TXOVFINTSTATUS_MASK        0x800
#define SPIMS_SPI_IS1_TXOVFINTSTATUS_SHIFT       11 
#define SPIMS_SPI_IS1_TXOVFINTSTATUS_BIT         0x1
#define SPIMS_SPI_IS1_TXOVFINTSTATUS_BITWIDTH    1
// reserved bitfiled (RO) Reset=0
#define SPIMS_SPI_IS1_RESERVED_MASK              0xFFFFF000
#define SPIMS_SPI_IS1_RESERVED_SHIFT             12 
#define SPIMS_SPI_IS1_RESERVED_BIT               0xFFFFF
#define SPIMS_SPI_IS1_RESERVED_BITWIDTH          20
// SPI_RXFIFONMB1 Register
#define SPIMS_SPI_RXFIFONMB1_OFS                 0x00010028
// NUMBER bitfiled (RO) Reset=0
#define SPIMS_SPI_RXFIFONMB1_NUMBER_MASK         0xFF
#define SPIMS_SPI_RXFIFONMB1_NUMBER_SHIFT        0 
#define SPIMS_SPI_RXFIFONMB1_NUMBER_BIT          0xFF
#define SPIMS_SPI_RXFIFONMB1_NUMBER_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define SPIMS_SPI_RXFIFONMB1_RESERVED_MASK       0xFFFFFF00
#define SPIMS_SPI_RXFIFONMB1_RESERVED_SHIFT      8 
#define SPIMS_SPI_RXFIFONMB1_RESERVED_BIT        0xFFFFFF
#define SPIMS_SPI_RXFIFONMB1_RESERVED_BITWIDTH   24
// SPI_TXFIFONMB1 Register
#define SPIMS_SPI_TXFIFONMB1_OFS                 0x0001002C
// NUMBER bitfiled (RO) Reset=0
#define SPIMS_SPI_TXFIFONMB1_NUMBER_MASK         0xFF
#define SPIMS_SPI_TXFIFONMB1_NUMBER_SHIFT        0 
#define SPIMS_SPI_TXFIFONMB1_NUMBER_BIT          0xFF
#define SPIMS_SPI_TXFIFONMB1_NUMBER_BITWIDTH     8
// reserved bitfiled (RO) Reset=0
#define SPIMS_SPI_TXFIFONMB1_RESERVED_MASK       0xFFFFFF00
#define SPIMS_SPI_TXFIFONMB1_RESERVED_SHIFT      8 
#define SPIMS_SPI_TXFIFONMB1_RESERVED_BIT        0xFFFFFF
#define SPIMS_SPI_TXFIFONMB1_RESERVED_BITWIDTH   24

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SPIMS_REG_DEF_H */
