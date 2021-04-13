/*
 * arch/arm/mach-tz3000/include/mach/regs/sadc_reg_def.h
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

#ifndef _SADC_REG_DEF_H
#define _SADC_REG_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

// SAD00CH Register
#define SADC_SAD00CH_OFS                         0x00000000
// SAD00CH bitfiled (RO) Reset=0
#define SADC_SAD00CH_SAD00CH_MASK                0x3FF
#define SADC_SAD00CH_SAD00CH_SHIFT               0 
#define SADC_SAD00CH_SAD00CH_BIT                 0x3FF
#define SADC_SAD00CH_SAD00CH_BITWIDTH            10
// reserved bitfiled (RO) Reset=0
#define SADC_SAD00CH_RESERVED_MASK               0xFFFFFC00
#define SADC_SAD00CH_RESERVED_SHIFT              10 
#define SADC_SAD00CH_RESERVED_BIT                0x3FFFFF
#define SADC_SAD00CH_RESERVED_BITWIDTH           22
// SAD01CH Register
#define SADC_SAD01CH_OFS                         0x00000004
// SAD01CH bitfiled (RO) Reset=0
#define SADC_SAD01CH_SAD01CH_MASK                0x3FF
#define SADC_SAD01CH_SAD01CH_SHIFT               0 
#define SADC_SAD01CH_SAD01CH_BIT                 0x3FF
#define SADC_SAD01CH_SAD01CH_BITWIDTH            10
// reserved bitfiled (RO) Reset=0
#define SADC_SAD01CH_RESERVED_MASK               0xFFFFFC00
#define SADC_SAD01CH_RESERVED_SHIFT              10 
#define SADC_SAD01CH_RESERVED_BIT                0x3FFFFF
#define SADC_SAD01CH_RESERVED_BITWIDTH           22
// SAD02CH Register
#define SADC_SAD02CH_OFS                         0x00000008
// SAD02CH bitfiled (RO) Reset=0
#define SADC_SAD02CH_SAD02CH_MASK                0x3FF
#define SADC_SAD02CH_SAD02CH_SHIFT               0 
#define SADC_SAD02CH_SAD02CH_BIT                 0x3FF
#define SADC_SAD02CH_SAD02CH_BITWIDTH            10
// reserved bitfiled (RO) Reset=0
#define SADC_SAD02CH_RESERVED_MASK               0xFFFFFC00
#define SADC_SAD02CH_RESERVED_SHIFT              10 
#define SADC_SAD02CH_RESERVED_BIT                0x3FFFFF
#define SADC_SAD02CH_RESERVED_BITWIDTH           22
// SAD03CH Register
#define SADC_SAD03CH_OFS                         0x0000000C
// SAD03CH bitfiled (RO) Reset=0
#define SADC_SAD03CH_SAD03CH_MASK                0x3FF
#define SADC_SAD03CH_SAD03CH_SHIFT               0 
#define SADC_SAD03CH_SAD03CH_BIT                 0x3FF
#define SADC_SAD03CH_SAD03CH_BITWIDTH            10
// reserved bitfiled (RO) Reset=0
#define SADC_SAD03CH_RESERVED_MASK               0xFFFFFC00
#define SADC_SAD03CH_RESERVED_SHIFT              10 
#define SADC_SAD03CH_RESERVED_BIT                0x3FFFFF
#define SADC_SAD03CH_RESERVED_BITWIDTH           22
// SAD04CH Register
#define SADC_SAD04CH_OFS                         0x00000010
// SAD04CH bitfiled (RO) Reset=0
#define SADC_SAD04CH_SAD04CH_MASK                0x3FF
#define SADC_SAD04CH_SAD04CH_SHIFT               0 
#define SADC_SAD04CH_SAD04CH_BIT                 0x3FF
#define SADC_SAD04CH_SAD04CH_BITWIDTH            10
// reserved bitfiled (RO) Reset=0
#define SADC_SAD04CH_RESERVED_MASK               0xFFFFFC00
#define SADC_SAD04CH_RESERVED_SHIFT              10 
#define SADC_SAD04CH_RESERVED_BIT                0x3FFFFF
#define SADC_SAD04CH_RESERVED_BITWIDTH           22
// SAD05CH Register
#define SADC_SAD05CH_OFS                         0x00000014
// SAD05CH bitfiled (RO) Reset=0
#define SADC_SAD05CH_SAD05CH_MASK                0x3FF
#define SADC_SAD05CH_SAD05CH_SHIFT               0 
#define SADC_SAD05CH_SAD05CH_BIT                 0x3FF
#define SADC_SAD05CH_SAD05CH_BITWIDTH            10
// reserved bitfiled (RO) Reset=0
#define SADC_SAD05CH_RESERVED_MASK               0xFFFFFC00
#define SADC_SAD05CH_RESERVED_SHIFT              10 
#define SADC_SAD05CH_RESERVED_BIT                0x3FFFFF
#define SADC_SAD05CH_RESERVED_BITWIDTH           22
// SADCTRL Register
#define SADC_SADCTRL_OFS                         0x00000040
// RST bitfiled (RW) Reset=1
#define SADC_SADCTRL_RST_MASK                    0x1
#define SADC_SADCTRL_RST_SHIFT                   0 
#define SADC_SADCTRL_RST_BIT                     0x1
#define SADC_SADCTRL_RST_BITWIDTH                1
// STB bitfiled (RW) Reset=1
#define SADC_SADCTRL_STB_MASK                    0x2
#define SADC_SADCTRL_STB_SHIFT                   1 
#define SADC_SADCTRL_STB_BIT                     0x1
#define SADC_SADCTRL_STB_BITWIDTH                1
// Valid bitfiled (RO) Reset=1
#define SADC_SADCTRL_VALID_MASK                  0x4
#define SADC_SADCTRL_VALID_SHIFT                 2 
#define SADC_SADCTRL_VALID_BIT                   0x1
#define SADC_SADCTRL_VALID_BITWIDTH              1
// reserved bitfiled (RO) Reset=0
#define SADC_SADCTRL_RESERVED_MASK               0xFFFFFFF8
#define SADC_SADCTRL_RESERVED_SHIFT              3 
#define SADC_SADCTRL_RESERVED_BIT                0x1FFFFFFF
#define SADC_SADCTRL_RESERVED_BITWIDTH           29
// SADDEBUG Register
#define SADC_SADDEBUG_OFS                        0x00000044
// STATUS bitfiled (RO) Reset=0
#define SADC_SADDEBUG_STATUS_MASK                0x7
#define SADC_SADDEBUG_STATUS_SHIFT               0 
#define SADC_SADDEBUG_STATUS_BIT                 0x7
#define SADC_SADDEBUG_STATUS_BITWIDTH            3
// reserved2 bitfiled (RO) Reset=0
#define SADC_SADDEBUG_RESERVED2_MASK             0x8
#define SADC_SADDEBUG_RESERVED2_SHIFT            3 
#define SADC_SADDEBUG_RESERVED2_BIT              0x1
#define SADC_SADDEBUG_RESERVED2_BITWIDTH         1
// SEQERR0 bitfiled (RO) Reset=0
#define SADC_SADDEBUG_SEQERR0_MASK               0x10
#define SADC_SADDEBUG_SEQERR0_SHIFT              4 
#define SADC_SADDEBUG_SEQERR0_BIT                0x1
#define SADC_SADDEBUG_SEQERR0_BITWIDTH           1
// SEQERR1 bitfiled (RO) Reset=0
#define SADC_SADDEBUG_SEQERR1_MASK               0x20
#define SADC_SADDEBUG_SEQERR1_SHIFT              5 
#define SADC_SADDEBUG_SEQERR1_BIT                0x1
#define SADC_SADDEBUG_SEQERR1_BITWIDTH           1
// SEQERR2 bitfiled (RO) Reset=0
#define SADC_SADDEBUG_SEQERR2_MASK               0x40
#define SADC_SADDEBUG_SEQERR2_SHIFT              6 
#define SADC_SADDEBUG_SEQERR2_BIT                0x1
#define SADC_SADDEBUG_SEQERR2_BITWIDTH           1
// reserved bitfiled (RO) Reset=0
#define SADC_SADDEBUG_RESERVED_MASK              0xFFFFFF80
#define SADC_SADDEBUG_RESERVED_SHIFT             7 
#define SADC_SADDEBUG_RESERVED_BIT               0x1FFFFFF
#define SADC_SADDEBUG_RESERVED_BITWIDTH          25

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SADC_REG_DEF_H */
