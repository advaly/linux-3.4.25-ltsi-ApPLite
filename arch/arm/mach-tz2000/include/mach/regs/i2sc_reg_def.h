/*
 * arch/arm/mach-tz2000/include/mach/regs/i2sc_reg_def.h
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

#ifndef _I2SC_REG_DEF_H
#define _I2SC_REG_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

// START Register
#define I2SC_START_OFS                           0x00000004
// Start bitfiled (RW) Reset=0
#define I2SC_START_START_MASK                    0x1
#define I2SC_START_START_SHIFT                   0 
#define I2SC_START_START_BIT                     0x1
#define I2SC_START_START_BITWIDTH                1
// reserved2 bitfiled (RO) Reset=0
#define I2SC_START_RESERVED2_MASK                0xFE
#define I2SC_START_RESERVED2_SHIFT               1 
#define I2SC_START_RESERVED2_BIT                 0x7F
#define I2SC_START_RESERVED2_BITWIDTH            7
// MCKStart bitfiled (RW) Reset=0
#define I2SC_START_MCKSTART_MASK                 0x100
#define I2SC_START_MCKSTART_SHIFT                8 
#define I2SC_START_MCKSTART_BIT                  0x1
#define I2SC_START_MCKSTART_BITWIDTH             1
// reserved bitfiled (RO) Reset=0
#define I2SC_START_RESERVED_MASK                 0xFFFFFE00
#define I2SC_START_RESERVED_SHIFT                9 
#define I2SC_START_RESERVED_BIT                  0x7FFFFF
#define I2SC_START_RESERVED_BITWIDTH             23
// BUSY Register
#define I2SC_BUSY_OFS                            0x00000008
// Busy bitfiled (RO) Reset=0
#define I2SC_BUSY_BUSY_MASK                      0x1
#define I2SC_BUSY_BUSY_SHIFT                     0 
#define I2SC_BUSY_BUSY_BIT                       0x1
#define I2SC_BUSY_BUSY_BITWIDTH                  1
// SeriBusy bitfiled (RO) Reset=0
#define I2SC_BUSY_SERIBUSY_MASK                  0x2
#define I2SC_BUSY_SERIBUSY_SHIFT                 1 
#define I2SC_BUSY_SERIBUSY_BIT                   0x1
#define I2SC_BUSY_SERIBUSY_BITWIDTH              1
// reserved2 bitfiled (RO) Reset=0
#define I2SC_BUSY_RESERVED2_MASK                 0xFC
#define I2SC_BUSY_RESERVED2_SHIFT                2 
#define I2SC_BUSY_RESERVED2_BIT                  0x3F
#define I2SC_BUSY_RESERVED2_BITWIDTH             6
// MCKBusy bitfiled (RO) Reset=0
#define I2SC_BUSY_MCKBUSY_MASK                   0x100
#define I2SC_BUSY_MCKBUSY_SHIFT                  8 
#define I2SC_BUSY_MCKBUSY_BIT                    0x1
#define I2SC_BUSY_MCKBUSY_BITWIDTH               1
// reserved bitfiled (RO) Reset=0
#define I2SC_BUSY_RESERVED_MASK                  0xFFFFFE00
#define I2SC_BUSY_RESERVED_SHIFT                 9 
#define I2SC_BUSY_RESERVED_BIT                   0x7FFFFF
#define I2SC_BUSY_RESERVED_BITWIDTH              23
// AUDIOSET Register
#define I2SC_AUDIOSET_OFS                        0x00000010
// WordLen bitfiled (RW) Reset=0
#define I2SC_AUDIOSET_WORDLEN_MASK               0x1F
#define I2SC_AUDIOSET_WORDLEN_SHIFT              0 
#define I2SC_AUDIOSET_WORDLEN_BIT                0x1F
#define I2SC_AUDIOSET_WORDLEN_BITWIDTH           5
// reserved3 bitfiled (RO) Reset=0
#define I2SC_AUDIOSET_RESERVED3_MASK             0xE0
#define I2SC_AUDIOSET_RESERVED3_SHIFT            5 
#define I2SC_AUDIOSET_RESERVED3_BIT              0x7
#define I2SC_AUDIOSET_RESERVED3_BITWIDTH         3
// SCLKTOWS bitfiled (RW) Reset=0
#define I2SC_AUDIOSET_SCLKTOWS_MASK              0x100
#define I2SC_AUDIOSET_SCLKTOWS_SHIFT             8 
#define I2SC_AUDIOSET_SCLKTOWS_BIT               0x1
#define I2SC_AUDIOSET_SCLKTOWS_BITWIDTH          1
// reserved2 bitfiled (RO) Reset=0
#define I2SC_AUDIOSET_RESERVED2_MASK             0x600
#define I2SC_AUDIOSET_RESERVED2_SHIFT            9 
#define I2SC_AUDIOSET_RESERVED2_BIT              0x3
#define I2SC_AUDIOSET_RESERVED2_BITWIDTH         2
// Edge bitfiled (RW) Reset=0
#define I2SC_AUDIOSET_EDGE_MASK                  0x800
#define I2SC_AUDIOSET_EDGE_SHIFT                 11 
#define I2SC_AUDIOSET_EDGE_BIT                   0x1
#define I2SC_AUDIOSET_EDGE_BITWIDTH              1
// MtoWS bitfiled (RW) Reset=0
#define I2SC_AUDIOSET_MTOWS_MASK                 0x3000
#define I2SC_AUDIOSET_MTOWS_SHIFT                12 
#define I2SC_AUDIOSET_MTOWS_BIT                  0x3
#define I2SC_AUDIOSET_MTOWS_BITWIDTH             2
// reserved bitfiled (RO) Reset=0
#define I2SC_AUDIOSET_RESERVED_MASK              0xFFFFC000
#define I2SC_AUDIOSET_RESERVED_SHIFT             14 
#define I2SC_AUDIOSET_RESERVED_BIT               0x3FFFF
#define I2SC_AUDIOSET_RESERVED_BITWIDTH          18
// INTSTAT Register
#define I2SC_INTSTAT_OFS                         0x00000014
// Int bitfiled (RO) Reset=0
#define I2SC_INTSTAT_INT_MASK                    0x1
#define I2SC_INTSTAT_INT_SHIFT                   0 
#define I2SC_INTSTAT_INT_BIT                     0x1
#define I2SC_INTSTAT_INT_BITWIDTH                1
// ORErr bitfiled (RO) Reset=0
#define I2SC_INTSTAT_ORERR_MASK                  0x2
#define I2SC_INTSTAT_ORERR_SHIFT                 1 
#define I2SC_INTSTAT_ORERR_BIT                   0x1
#define I2SC_INTSTAT_ORERR_BITWIDTH              1
// URErr bitfiled (RO) Reset=0
#define I2SC_INTSTAT_URERR_MASK                  0x4
#define I2SC_INTSTAT_URERR_SHIFT                 2 
#define I2SC_INTSTAT_URERR_BIT                   0x1
#define I2SC_INTSTAT_URERR_BITWIDTH              1
// reserved bitfiled (RO) Reset=0
#define I2SC_INTSTAT_RESERVED_MASK               0xFFFFFFF8
#define I2SC_INTSTAT_RESERVED_SHIFT              3 
#define I2SC_INTSTAT_RESERVED_BIT                0x1FFFFFFF
#define I2SC_INTSTAT_RESERVED_BITWIDTH           29
// INTMASK Register
#define I2SC_INTMASK_OFS                         0x00000018
// Mask bitfiled (RW) Reset=1
#define I2SC_INTMASK_MASK_MASK                   0x1
#define I2SC_INTMASK_MASK_SHIFT                  0 
#define I2SC_INTMASK_MASK_BIT                    0x1
#define I2SC_INTMASK_MASK_BITWIDTH               1
// ORMask bitfiled (RW) Reset=1
#define I2SC_INTMASK_ORMASK_MASK                 0x2
#define I2SC_INTMASK_ORMASK_SHIFT                1 
#define I2SC_INTMASK_ORMASK_BIT                  0x1
#define I2SC_INTMASK_ORMASK_BITWIDTH             1
// URMask bitfiled (RW) Reset=1
#define I2SC_INTMASK_URMASK_MASK                 0x4
#define I2SC_INTMASK_URMASK_SHIFT                2 
#define I2SC_INTMASK_URMASK_BIT                  0x1
#define I2SC_INTMASK_URMASK_BITWIDTH             1
// reserved2 bitfiled (RO) Reset=0
#define I2SC_INTMASK_RESERVED2_MASK              0xFFF8
#define I2SC_INTMASK_RESERVED2_SHIFT             3 
#define I2SC_INTMASK_RESERVED2_BIT               0x1FFF
#define I2SC_INTMASK_RESERVED2_BITWIDTH          13
// DMACMSK bitfiled (RW) Reset=0
#define I2SC_INTMASK_DMACMSK_MASK                0x10000
#define I2SC_INTMASK_DMACMSK_SHIFT               16 
#define I2SC_INTMASK_DMACMSK_BIT                 0x1
#define I2SC_INTMASK_DMACMSK_BITWIDTH            1
// reserved bitfiled (RO) Reset=0
#define I2SC_INTMASK_RESERVED_MASK               0xFFFE0000
#define I2SC_INTMASK_RESERVED_SHIFT              17 
#define I2SC_INTMASK_RESERVED_BIT                0x7FFF
#define I2SC_INTMASK_RESERVED_BITWIDTH           15
// INTCLR Register
#define I2SC_INTCLR_OFS                          0x0000001C
// IntClr bitfiled (RW) Reset=0
#define I2SC_INTCLR_INTCLR_MASK                  0x1
#define I2SC_INTCLR_INTCLR_SHIFT                 0 
#define I2SC_INTCLR_INTCLR_BIT                   0x1
#define I2SC_INTCLR_INTCLR_BITWIDTH              1
// ORClr bitfiled (RW) Reset=0
#define I2SC_INTCLR_ORCLR_MASK                   0x2
#define I2SC_INTCLR_ORCLR_SHIFT                  1 
#define I2SC_INTCLR_ORCLR_BIT                    0x1
#define I2SC_INTCLR_ORCLR_BITWIDTH               1
// URClr bitfiled (RW) Reset=0
#define I2SC_INTCLR_URCLR_MASK                   0x4
#define I2SC_INTCLR_URCLR_SHIFT                  2 
#define I2SC_INTCLR_URCLR_BIT                    0x1
#define I2SC_INTCLR_URCLR_BITWIDTH               1
// reserved bitfiled (RO) Reset=0
#define I2SC_INTCLR_RESERVED_MASK                0xFFFFFFF8
#define I2SC_INTCLR_RESERVED_SHIFT               3 
#define I2SC_INTCLR_RESERVED_BIT                 0x1FFFFFFF
#define I2SC_INTCLR_RESERVED_BITWIDTH            29
// INTSET Register
#define I2SC_INTSET_OFS                          0x00000020
// IntSet bitfiled (RW) Reset=0
#define I2SC_INTSET_INTSET_MASK                  0x3
#define I2SC_INTSET_INTSET_SHIFT                 0 
#define I2SC_INTSET_INTSET_BIT                   0x3
#define I2SC_INTSET_INTSET_BITWIDTH              2
// reserved bitfiled (RO) Reset=0
#define I2SC_INTSET_RESERVED_MASK                0xFFFFFFFC
#define I2SC_INTSET_RESERVED_SHIFT               2 
#define I2SC_INTSET_RESERVED_BIT                 0x3FFFFFFF
#define I2SC_INTSET_RESERVED_BITWIDTH            30
// MUTE Register
#define I2SC_MUTE_OFS                            0x00000024
// MuteN bitfiled (RW) Reset=0
#define I2SC_MUTE_MUTEN_MASK                     0x1
#define I2SC_MUTE_MUTEN_SHIFT                    0 
#define I2SC_MUTE_MUTEN_BIT                      0x1
#define I2SC_MUTE_MUTEN_BITWIDTH                 1
// reserved bitfiled (RO) Reset=0
#define I2SC_MUTE_RESERVED_MASK                  0xFFFFFFFE
#define I2SC_MUTE_RESERVED_SHIFT                 1 
#define I2SC_MUTE_RESERVED_BIT                   0x7FFFFFFF
#define I2SC_MUTE_RESERVED_BITWIDTH              31
// EPTR Register
#define I2SC_EPTR_OFS                            0x00000028
// ErrPointer bitfiled (RO) Reset=0
#define I2SC_EPTR_ERRPOINTER_MASK                0xFF
#define I2SC_EPTR_ERRPOINTER_SHIFT               0 
#define I2SC_EPTR_ERRPOINTER_BIT                 0xFF
#define I2SC_EPTR_ERRPOINTER_BITWIDTH            8
// reserved bitfiled (RO) Reset=0
#define I2SC_EPTR_RESERVED_MASK                  0xFFFFFF00
#define I2SC_EPTR_RESERVED_SHIFT                 8 
#define I2SC_EPTR_RESERVED_BIT                   0xFFFFFF
#define I2SC_EPTR_RESERVED_BITWIDTH              24
// MODESET Register
#define I2SC_MODESET_OFS                         0x000000F8
// WS bitfiled (RW) Reset=0
#define I2SC_MODESET_WS_MASK                     0x7
#define I2SC_MODESET_WS_SHIFT                    0 
#define I2SC_MODESET_WS_BIT                      0x7
#define I2SC_MODESET_WS_BITWIDTH                 3
// reserved2 bitfiled (RO) Reset=0
#define I2SC_MODESET_RESERVED2_MASK              0x8
#define I2SC_MODESET_RESERVED2_SHIFT             3 
#define I2SC_MODESET_RESERVED2_BIT               0x1
#define I2SC_MODESET_RESERVED2_BITWIDTH          1
// IESEL bitfiled (RW) Reset=0
#define I2SC_MODESET_IESEL_MASK                  0x30
#define I2SC_MODESET_IESEL_SHIFT                 4 
#define I2SC_MODESET_IESEL_BIT                   0x3
#define I2SC_MODESET_IESEL_BITWIDTH              2
// reserved bitfiled (RO) Reset=0
#define I2SC_MODESET_RESERVED_MASK               0xFFFFFFC0
#define I2SC_MODESET_RESERVED_SHIFT              6 
#define I2SC_MODESET_RESERVED_BIT                0x3FFFFFF
#define I2SC_MODESET_RESERVED_BITWIDTH           26

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _I2SC_REG_DEF_H */
