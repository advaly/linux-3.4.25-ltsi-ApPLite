/*
 * arch/arm/mach-tz2000/include/mach/regs/dtree_reg_def.h
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

#ifndef _DTREE_REG_DEF_H
#define _DTREE_REG_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

// REV1 Register
#define DTREE_REV1_OFS                           0x00000004
// PCODE bitfiled (RO) Reset=10000000000000
#define DTREE_REV1_PCODE_MASK                    0xFFFF
#define DTREE_REV1_PCODE_SHIFT                   0 
#define DTREE_REV1_PCODE_BIT                     0xFFFF
#define DTREE_REV1_PCODE_BITWIDTH                16
// reserved bitfiled (RO) Reset=0
#define DTREE_REV1_RESERVED_MASK                 0xFFFF0000
#define DTREE_REV1_RESERVED_SHIFT                16 
#define DTREE_REV1_RESERVED_BIT                  0xFFFF
#define DTREE_REV1_RESERVED_BITWIDTH             16

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DTREE_REG_DEF_H */
