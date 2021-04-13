/*
 * arch/arm/mach-tz3000/include/mach/regs/scomm_reg_def.h
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

#ifndef _SCOMM_REG_DEF_H
#define _SCOMM_REG_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

// TAS_NONSEC Register
#define SCOMM_TAS_NONSEC_OFS                     0x00000000
// TAS bitfiled (RW) Reset=0
#define SCOMM_TAS_NONSEC_TAS_MASK                0x1
#define SCOMM_TAS_NONSEC_TAS_SHIFT               0 
#define SCOMM_TAS_NONSEC_TAS_BIT                 0x1
#define SCOMM_TAS_NONSEC_TAS_BITWIDTH            1
// reserved bitfiled (RO) Reset=0
#define SCOMM_TAS_NONSEC_RESERVED_MASK           0xFFFFFFFE
#define SCOMM_TAS_NONSEC_RESERVED_SHIFT          1 
#define SCOMM_TAS_NONSEC_RESERVED_BIT            0x7FFFFFFF
#define SCOMM_TAS_NONSEC_RESERVED_BITWIDTH       31
// INT_NONSEC Register
#define SCOMM_INT_NONSEC_OFS                     0x00000004
// INT bitfiled (RW) Reset=0
#define SCOMM_INT_NONSEC_INT_MASK                0x1
#define SCOMM_INT_NONSEC_INT_SHIFT               0 
#define SCOMM_INT_NONSEC_INT_BIT                 0x1
#define SCOMM_INT_NONSEC_INT_BITWIDTH            1
// reserved bitfiled (RO) Reset=0
#define SCOMM_INT_NONSEC_RESERVED_MASK           0xFFFFFFFE
#define SCOMM_INT_NONSEC_RESERVED_SHIFT          1 
#define SCOMM_INT_NONSEC_RESERVED_BIT            0x7FFFFFFF
#define SCOMM_INT_NONSEC_RESERVED_BITWIDTH       31
// TAS_SECURE Register
#define SCOMM_TAS_SECURE_OFS                     0x00000010
// TAS bitfiled (RW) Reset=0
#define SCOMM_TAS_SECURE_TAS_MASK                0x1
#define SCOMM_TAS_SECURE_TAS_SHIFT               0 
#define SCOMM_TAS_SECURE_TAS_BIT                 0x1
#define SCOMM_TAS_SECURE_TAS_BITWIDTH            1
// reserved bitfiled (RO) Reset=0
#define SCOMM_TAS_SECURE_RESERVED_MASK           0xFFFFFFFE
#define SCOMM_TAS_SECURE_RESERVED_SHIFT          1 
#define SCOMM_TAS_SECURE_RESERVED_BIT            0x7FFFFFFF
#define SCOMM_TAS_SECURE_RESERVED_BITWIDTH       31
// INT_SECURE Register
#define SCOMM_INT_SECURE_OFS                     0x00000014
// INT bitfiled (RW) Reset=0
#define SCOMM_INT_SECURE_INT_MASK                0x1
#define SCOMM_INT_SECURE_INT_SHIFT               0 
#define SCOMM_INT_SECURE_INT_BIT                 0x1
#define SCOMM_INT_SECURE_INT_BITWIDTH            1
// reserved bitfiled (RO) Reset=0
#define SCOMM_INT_SECURE_RESERVED_MASK           0xFFFFFFFE
#define SCOMM_INT_SECURE_RESERVED_SHIFT          1 
#define SCOMM_INT_SECURE_RESERVED_BIT            0x7FFFFFFF
#define SCOMM_INT_SECURE_RESERVED_BITWIDTH       31

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SCOMM_REG_DEF_H */
