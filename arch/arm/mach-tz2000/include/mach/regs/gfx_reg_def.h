/*
 * arch/arm/mach-tz2000/include/mach/regs/gfx_reg_def.h
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

#ifndef _GFX_REG_DEF_H
#define _GFX_REG_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

// GASCR Register
#define GFX_GASCR_OFS                            0x00000000
// GARESET bitfiled (RW) Reset=0
#define GFX_GASCR_GARESET_MASK                   0x1
#define GFX_GASCR_GARESET_SHIFT                  0 
#define GFX_GASCR_GARESET_BIT                    0x1
#define GFX_GASCR_GARESET_BITWIDTH               1
// GAEN bitfiled (RW) Reset=0
#define GFX_GASCR_GAEN_MASK                      0x2
#define GFX_GASCR_GAEN_SHIFT                     1 
#define GFX_GASCR_GAEN_BIT                       0x1
#define GFX_GASCR_GAEN_BITWIDTH                  1
// reserved2 bitfiled (RO) Reset=0
#define GFX_GASCR_RESERVED2_MASK                 0xFC
#define GFX_GASCR_RESERVED2_SHIFT                2 
#define GFX_GASCR_RESERVED2_BIT                  0x3F
#define GFX_GASCR_RESERVED2_BITWIDTH             6
// DISRA bitfiled (RW) Reset=0
#define GFX_GASCR_DISRA_MASK                     0x100
#define GFX_GASCR_DISRA_SHIFT                    8 
#define GFX_GASCR_DISRA_BIT                      0x1
#define GFX_GASCR_DISRA_BITWIDTH                 1
// reserved bitfiled (RO) Reset=0
#define GFX_GASCR_RESERVED_MASK                  0xFFFFFE00
#define GFX_GASCR_RESERVED_SHIFT                 9 
#define GFX_GASCR_RESERVED_BIT                   0x7FFFFF
#define GFX_GASCR_RESERVED_BITWIDTH              23
// GACLAR Register
#define GFX_GACLAR_OFS                           0x00000004
// reserved bitfiled (RO) Reset=0
#define GFX_GACLAR_RESERVED_MASK                 0x7
#define GFX_GACLAR_RESERVED_SHIFT                0 
#define GFX_GACLAR_RESERVED_BIT                  0x7
#define GFX_GACLAR_RESERVED_BITWIDTH             3
// CSLA bitfiled (RW) Reset=0
#define GFX_GACLAR_CSLA_MASK                     0xFFFFFFF8
#define GFX_GACLAR_CSLA_SHIFT                    3 
#define GFX_GACLAR_CSLA_BIT                      0x1FFFFFFF
#define GFX_GACLAR_CSLA_BITWIDTH                 29
// GASR Register
#define GFX_GASR_OFS                             0x00000008
// BUSY bitfiled (RO) Reset=0
#define GFX_GASR_BUSY_MASK                       0x1
#define GFX_GASR_BUSY_SHIFT                      0 
#define GFX_GASR_BUSY_BIT                        0x1
#define GFX_GASR_BUSY_BITWIDTH                   1
// reserved2 bitfiled (RO) Reset=0
#define GFX_GASR_RESERVED2_MASK                  0x2
#define GFX_GASR_RESERVED2_SHIFT                 1 
#define GFX_GASR_RESERVED2_BIT                   0x1
#define GFX_GASR_RESERVED2_BITWIDTH              1
// CSCEF bitfiled (RO) Reset=0
#define GFX_GASR_CSCEF_MASK                      0x4
#define GFX_GASR_CSCEF_SHIFT                     2 
#define GFX_GASR_CSCEF_BIT                       0x1
#define GFX_GASR_CSCEF_BITWIDTH                  1
// CSLEF bitfiled (RO) Reset=1
#define GFX_GASR_CSLEF_MASK                      0x8
#define GFX_GASR_CSLEF_SHIFT                     3 
#define GFX_GASR_CSLEF_BIT                       0x1
#define GFX_GASR_CSLEF_BITWIDTH                  1
// reserved bitfiled (RO) Reset=0
#define GFX_GASR_RESERVED_MASK                   0xFFFFFFF0
#define GFX_GASR_RESERVED_SHIFT                  4 
#define GFX_GASR_RESERVED_BIT                    0xFFFFFFF
#define GFX_GASR_RESERVED_BITWIDTH               28
// GAICR Register
#define GFX_GAICR_OFS                            0x0000000C
// GACENDI bitfiled (RW) Reset=0
#define GFX_GAICR_GACENDI_MASK                   0x1
#define GFX_GAICR_GACENDI_SHIFT                  0 
#define GFX_GAICR_GACENDI_BIT                    0x1
#define GFX_GAICR_GACENDI_BITWIDTH               1
// reserved bitfiled (RO) Reset=0
#define GFX_GAICR_RESERVED_MASK                  0x2
#define GFX_GAICR_RESERVED_SHIFT                 1 
#define GFX_GAICR_RESERVED_BIT                   0x1
#define GFX_GAICR_RESERVED_BITWIDTH              1
// CSCEI bitfiled (RW) Reset=0
#define GFX_GAICR_CSCEI_MASK                     0x4
#define GFX_GAICR_CSCEI_SHIFT                    2 
#define GFX_GAICR_CSCEI_BIT                      0x1
#define GFX_GAICR_CSCEI_BITWIDTH                 1
// CSLEI bitfiled (RW) Reset=0
#define GFX_GAICR_CSLEI_MASK                     0x8
#define GFX_GAICR_CSLEI_SHIFT                    3 
#define GFX_GAICR_CSLEI_BIT                      0x1
#define GFX_GAICR_CSLEI_BITWIDTH                 1
// GAWBWI bitfiled (RW) Reset=0
#define GFX_GAICR_GAWBWI_MASK                    0x10
#define GFX_GAICR_GAWBWI_SHIFT                   4 
#define GFX_GAICR_GAWBWI_BIT                     0x1
#define GFX_GAICR_GAWBWI_BITWIDTH                1
// GAWBRI bitfiled (RW) Reset=0
#define GFX_GAICR_GAWBRI_MASK                    0x20
#define GFX_GAICR_GAWBRI_SHIFT                   5 
#define GFX_GAICR_GAWBRI_BIT                     0x1
#define GFX_GAICR_GAWBRI_BITWIDTH                1
// GACBI bitfiled (RW) Reset=0
#define GFX_GAICR_GACBI_MASK                     0x40
#define GFX_GAICR_GACBI_SHIFT                    6 
#define GFX_GAICR_GACBI_BIT                      0x1
#define GFX_GAICR_GACBI_BITWIDTH                 1
// GARBI bitfiled (RW) Reset=0
#define GFX_GAICR_GARBI_MASK                     0x80
#define GFX_GAICR_GARBI_SHIFT                    7 
#define GFX_GAICR_GARBI_BIT                      0x1
#define GFX_GAICR_GARBI_BITWIDTH                 1
// CSLUI bitfiled (RW) Reset=0
#define GFX_GAICR_CSLUI_MASK                     0xFFFFFF00
#define GFX_GAICR_CSLUI_SHIFT                    8 
#define GFX_GAICR_CSLUI_BIT                      0xFFFFFF
#define GFX_GAICR_CSLUI_BITWIDTH                 24
// GAIMR Register
#define GFX_GAIMR_OFS                            0x00000010
// GACENDIM bitfiled (RW) Reset=0
#define GFX_GAIMR_GACENDIM_MASK                  0x1
#define GFX_GAIMR_GACENDIM_SHIFT                 0 
#define GFX_GAIMR_GACENDIM_BIT                   0x1
#define GFX_GAIMR_GACENDIM_BITWIDTH              1
// reserved bitfiled (RO) Reset=0
#define GFX_GAIMR_RESERVED_MASK                  0x2
#define GFX_GAIMR_RESERVED_SHIFT                 1 
#define GFX_GAIMR_RESERVED_BIT                   0x1
#define GFX_GAIMR_RESERVED_BITWIDTH              1
// CSCEIM bitfiled (RW) Reset=0
#define GFX_GAIMR_CSCEIM_MASK                    0x4
#define GFX_GAIMR_CSCEIM_SHIFT                   2 
#define GFX_GAIMR_CSCEIM_BIT                     0x1
#define GFX_GAIMR_CSCEIM_BITWIDTH                1
// CSLEIM bitfiled (RW) Reset=0
#define GFX_GAIMR_CSLEIM_MASK                    0x8
#define GFX_GAIMR_CSLEIM_SHIFT                   3 
#define GFX_GAIMR_CSLEIM_BIT                     0x1
#define GFX_GAIMR_CSLEIM_BITWIDTH                1
// GAWBWIM bitfiled (RW) Reset=0
#define GFX_GAIMR_GAWBWIM_MASK                   0x10
#define GFX_GAIMR_GAWBWIM_SHIFT                  4 
#define GFX_GAIMR_GAWBWIM_BIT                    0x1
#define GFX_GAIMR_GAWBWIM_BITWIDTH               1
// GAWBRIM bitfiled (RW) Reset=0
#define GFX_GAIMR_GAWBRIM_MASK                   0x20
#define GFX_GAIMR_GAWBRIM_SHIFT                  5 
#define GFX_GAIMR_GAWBRIM_BIT                    0x1
#define GFX_GAIMR_GAWBRIM_BITWIDTH               1
// GACBIM bitfiled (RW) Reset=0
#define GFX_GAIMR_GACBIM_MASK                    0x40
#define GFX_GAIMR_GACBIM_SHIFT                   6 
#define GFX_GAIMR_GACBIM_BIT                     0x1
#define GFX_GAIMR_GACBIM_BITWIDTH                1
// GARBIM bitfiled (RW) Reset=0
#define GFX_GAIMR_GARBIM_MASK                    0x80
#define GFX_GAIMR_GARBIM_SHIFT                   7 
#define GFX_GAIMR_GARBIM_BIT                     0x1
#define GFX_GAIMR_GARBIM_BITWIDTH                1
// CSLUIM bitfiled (RW) Reset=0
#define GFX_GAIMR_CSLUIM_MASK                    0xFFFFFF00
#define GFX_GAIMR_CSLUIM_SHIFT                   8 
#define GFX_GAIMR_CSLUIM_BIT                     0xFFFFFF
#define GFX_GAIMR_CSLUIM_BITWIDTH                24
// GADR Register
#define GFX_GADR_OFS                             0x00000014
// GAD bitfiled (RW) Reset=0
#define GFX_GADR_GAD_MASK                        0xFFFF
#define GFX_GADR_GAD_SHIFT                       0 
#define GFX_GADR_GAD_BIT                         0xFFFF
#define GFX_GADR_GAD_BITWIDTH                    16
// reserved bitfiled (RO) Reset=0
#define GFX_GADR_RESERVED_MASK                   0xFFFF0000
#define GFX_GADR_RESERVED_SHIFT                  16 
#define GFX_GADR_RESERVED_BIT                    0xFFFF
#define GFX_GADR_RESERVED_BITWIDTH               16
// GARBBEAR Register
#define GFX_GARBBEAR_OFS                         0x00000020
// reserved bitfiled (RO) Reset=0
#define GFX_GARBBEAR_RESERVED_MASK               0x7
#define GFX_GARBBEAR_RESERVED_SHIFT              0 
#define GFX_GARBBEAR_RESERVED_BIT                0x7
#define GFX_GARBBEAR_RESERVED_BITWIDTH           3
// RBA bitfiled (RO) Reset=0
#define GFX_GARBBEAR_RBA_MASK                    0xFFFFFFF8
#define GFX_GARBBEAR_RBA_SHIFT                   3 
#define GFX_GARBBEAR_RBA_BIT                     0x1FFFFFFF
#define GFX_GARBBEAR_RBA_BITWIDTH                29
// GARBBECR Register
#define GFX_GARBBECR_OFS                         0x00000024
// WR bitfiled (RO) Reset=0
#define GFX_GARBBECR_WR_MASK                     0x1
#define GFX_GARBBECR_WR_SHIFT                    0 
#define GFX_GARBBECR_WR_BIT                      0x1
#define GFX_GARBBECR_WR_BITWIDTH                 1
// BTYPE bitfiled (RO) Reset=0
#define GFX_GARBBECR_BTYPE_MASK                  0x2
#define GFX_GARBBECR_BTYPE_SHIFT                 1 
#define GFX_GARBBECR_BTYPE_BIT                   0x1
#define GFX_GARBBECR_BTYPE_BITWIDTH              1
// BSIZE bitfiled (RO) Reset=0
#define GFX_GARBBECR_BSIZE_MASK                  0x1C
#define GFX_GARBBECR_BSIZE_SHIFT                 2 
#define GFX_GARBBECR_BSIZE_BIT                   0x7
#define GFX_GARBBECR_BSIZE_BITWIDTH              3
// RTYPE bitfiled (RO) Reset=0
#define GFX_GARBBECR_RTYPE_MASK                  0x60
#define GFX_GARBBECR_RTYPE_SHIFT                 5 
#define GFX_GARBBECR_RTYPE_BIT                   0x3
#define GFX_GARBBECR_RTYPE_BITWIDTH              2
// reserved2 bitfiled (RO) Reset=0
#define GFX_GARBBECR_RESERVED2_MASK              0x80
#define GFX_GARBBECR_RESERVED2_SHIFT             7 
#define GFX_GARBBECR_RESERVED2_BIT               0x1
#define GFX_GARBBECR_RESERVED2_BITWIDTH          1
// BEN bitfiled (RO) Reset=0
#define GFX_GARBBECR_BEN_MASK                    0xFF00
#define GFX_GARBBECR_BEN_SHIFT                   8 
#define GFX_GARBBECR_BEN_BIT                     0xFF
#define GFX_GARBBECR_BEN_BITWIDTH                8
// ID bitfiled (RO) Reset=0
#define GFX_GARBBECR_ID_MASK                     0xF0000
#define GFX_GARBBECR_ID_SHIFT                    16 
#define GFX_GARBBECR_ID_BIT                      0xF
#define GFX_GARBBECR_ID_BITWIDTH                 4
// LEN bitfiled (RO) Reset=0
#define GFX_GARBBECR_LEN_MASK                    0xF00000
#define GFX_GARBBECR_LEN_SHIFT                   20 
#define GFX_GARBBECR_LEN_BIT                     0xF
#define GFX_GARBBECR_LEN_BITWIDTH                4
// reserved bitfiled (RO) Reset=0
#define GFX_GARBBECR_RESERVED_MASK               0xFF000000
#define GFX_GARBBECR_RESERVED_SHIFT              24 
#define GFX_GARBBECR_RESERVED_BIT                0xFF
#define GFX_GARBBECR_RESERVED_BITWIDTH           8
// GACBBEAR Register
#define GFX_GACBBEAR_OFS                         0x00000028
// reserved bitfiled (RO) Reset=0
#define GFX_GACBBEAR_RESERVED_MASK               0x7
#define GFX_GACBBEAR_RESERVED_SHIFT              0 
#define GFX_GACBBEAR_RESERVED_BIT                0x7
#define GFX_GACBBEAR_RESERVED_BITWIDTH           3
// CBA bitfiled (RO) Reset=0
#define GFX_GACBBEAR_CBA_MASK                    0xFFFFFFF8
#define GFX_GACBBEAR_CBA_SHIFT                   3 
#define GFX_GACBBEAR_CBA_BIT                     0x1FFFFFFF
#define GFX_GACBBEAR_CBA_BITWIDTH                29
// GACBBECR Register
#define GFX_GACBBECR_OFS                         0x0000002C
// WR bitfiled (RO) Reset=0
#define GFX_GACBBECR_WR_MASK                     0x1
#define GFX_GACBBECR_WR_SHIFT                    0 
#define GFX_GACBBECR_WR_BIT                      0x1
#define GFX_GACBBECR_WR_BITWIDTH                 1
// BTYPE bitfiled (RO) Reset=0
#define GFX_GACBBECR_BTYPE_MASK                  0x2
#define GFX_GACBBECR_BTYPE_SHIFT                 1 
#define GFX_GACBBECR_BTYPE_BIT                   0x1
#define GFX_GACBBECR_BTYPE_BITWIDTH              1
// BSIZE bitfiled (RO) Reset=0
#define GFX_GACBBECR_BSIZE_MASK                  0x1C
#define GFX_GACBBECR_BSIZE_SHIFT                 2 
#define GFX_GACBBECR_BSIZE_BIT                   0x7
#define GFX_GACBBECR_BSIZE_BITWIDTH              3
// RTYPE bitfiled (RO) Reset=0
#define GFX_GACBBECR_RTYPE_MASK                  0x60
#define GFX_GACBBECR_RTYPE_SHIFT                 5 
#define GFX_GACBBECR_RTYPE_BIT                   0x3
#define GFX_GACBBECR_RTYPE_BITWIDTH              2
// reserved2 bitfiled (RO) Reset=0
#define GFX_GACBBECR_RESERVED2_MASK              0x80
#define GFX_GACBBECR_RESERVED2_SHIFT             7 
#define GFX_GACBBECR_RESERVED2_BIT               0x1
#define GFX_GACBBECR_RESERVED2_BITWIDTH          1
// BEN bitfiled (RO) Reset=0
#define GFX_GACBBECR_BEN_MASK                    0xFF00
#define GFX_GACBBECR_BEN_SHIFT                   8 
#define GFX_GACBBECR_BEN_BIT                     0xFF
#define GFX_GACBBECR_BEN_BITWIDTH                8
// ID bitfiled (RO) Reset=0
#define GFX_GACBBECR_ID_MASK                     0xF0000
#define GFX_GACBBECR_ID_SHIFT                    16 
#define GFX_GACBBECR_ID_BIT                      0xF
#define GFX_GACBBECR_ID_BITWIDTH                 4
// LEN bitfiled (RO) Reset=0
#define GFX_GACBBECR_LEN_MASK                    0xF00000
#define GFX_GACBBECR_LEN_SHIFT                   20 
#define GFX_GACBBECR_LEN_BIT                     0xF
#define GFX_GACBBECR_LEN_BITWIDTH                4
// reserved bitfiled (RO) Reset=0
#define GFX_GACBBECR_RESERVED_MASK               0xFF000000
#define GFX_GACBBECR_RESERVED_SHIFT              24 
#define GFX_GACBBECR_RESERVED_BIT                0xFF
#define GFX_GACBBECR_RESERVED_BITWIDTH           8
// GAWBRBEAR Register
#define GFX_GAWBRBEAR_OFS                        0x00000030
// reserved bitfiled (RO) Reset=0
#define GFX_GAWBRBEAR_RESERVED_MASK              0x7
#define GFX_GAWBRBEAR_RESERVED_SHIFT             0 
#define GFX_GAWBRBEAR_RESERVED_BIT               0x7
#define GFX_GAWBRBEAR_RESERVED_BITWIDTH          3
// WBRA bitfiled (RO) Reset=0
#define GFX_GAWBRBEAR_WBRA_MASK                  0xFFFFFFF8
#define GFX_GAWBRBEAR_WBRA_SHIFT                 3 
#define GFX_GAWBRBEAR_WBRA_BIT                   0x1FFFFFFF
#define GFX_GAWBRBEAR_WBRA_BITWIDTH              29
// GAWBRBECR Register
#define GFX_GAWBRBECR_OFS                        0x00000034
// WR bitfiled (RO) Reset=0
#define GFX_GAWBRBECR_WR_MASK                    0x1
#define GFX_GAWBRBECR_WR_SHIFT                   0 
#define GFX_GAWBRBECR_WR_BIT                     0x1
#define GFX_GAWBRBECR_WR_BITWIDTH                1
// BTYPE bitfiled (RO) Reset=0
#define GFX_GAWBRBECR_BTYPE_MASK                 0x2
#define GFX_GAWBRBECR_BTYPE_SHIFT                1 
#define GFX_GAWBRBECR_BTYPE_BIT                  0x1
#define GFX_GAWBRBECR_BTYPE_BITWIDTH             1
// BSIZE bitfiled (RO) Reset=0
#define GFX_GAWBRBECR_BSIZE_MASK                 0x1C
#define GFX_GAWBRBECR_BSIZE_SHIFT                2 
#define GFX_GAWBRBECR_BSIZE_BIT                  0x7
#define GFX_GAWBRBECR_BSIZE_BITWIDTH             3
// RTYPE bitfiled (RO) Reset=0
#define GFX_GAWBRBECR_RTYPE_MASK                 0x60
#define GFX_GAWBRBECR_RTYPE_SHIFT                5 
#define GFX_GAWBRBECR_RTYPE_BIT                  0x3
#define GFX_GAWBRBECR_RTYPE_BITWIDTH             2
// reserved2 bitfiled (RO) Reset=0
#define GFX_GAWBRBECR_RESERVED2_MASK             0x80
#define GFX_GAWBRBECR_RESERVED2_SHIFT            7 
#define GFX_GAWBRBECR_RESERVED2_BIT              0x1
#define GFX_GAWBRBECR_RESERVED2_BITWIDTH         1
// BEN bitfiled (RO) Reset=0
#define GFX_GAWBRBECR_BEN_MASK                   0xFF00
#define GFX_GAWBRBECR_BEN_SHIFT                  8 
#define GFX_GAWBRBECR_BEN_BIT                    0xFF
#define GFX_GAWBRBECR_BEN_BITWIDTH               8
// ID bitfiled (RO) Reset=0
#define GFX_GAWBRBECR_ID_MASK                    0xF0000
#define GFX_GAWBRBECR_ID_SHIFT                   16 
#define GFX_GAWBRBECR_ID_BIT                     0xF
#define GFX_GAWBRBECR_ID_BITWIDTH                4
// LEN bitfiled (RO) Reset=0
#define GFX_GAWBRBECR_LEN_MASK                   0xF00000
#define GFX_GAWBRBECR_LEN_SHIFT                  20 
#define GFX_GAWBRBECR_LEN_BIT                    0xF
#define GFX_GAWBRBECR_LEN_BITWIDTH               4
// reserved bitfiled (RO) Reset=0
#define GFX_GAWBRBECR_RESERVED_MASK              0xFF000000
#define GFX_GAWBRBECR_RESERVED_SHIFT             24 
#define GFX_GAWBRBECR_RESERVED_BIT               0xFF
#define GFX_GAWBRBECR_RESERVED_BITWIDTH          8
// GAWBWBEAR Register
#define GFX_GAWBWBEAR_OFS                        0x00000038
// reserved bitfiled (RO) Reset=0
#define GFX_GAWBWBEAR_RESERVED_MASK              0x7
#define GFX_GAWBWBEAR_RESERVED_SHIFT             0 
#define GFX_GAWBWBEAR_RESERVED_BIT               0x7
#define GFX_GAWBWBEAR_RESERVED_BITWIDTH          3
// WBWA bitfiled (RO) Reset=0
#define GFX_GAWBWBEAR_WBWA_MASK                  0xFFFFFFF8
#define GFX_GAWBWBEAR_WBWA_SHIFT                 3 
#define GFX_GAWBWBEAR_WBWA_BIT                   0x1FFFFFFF
#define GFX_GAWBWBEAR_WBWA_BITWIDTH              29
// GAWBWBECR Register
#define GFX_GAWBWBECR_OFS                        0x0000003C
// WR bitfiled (RO) Reset=0
#define GFX_GAWBWBECR_WR_MASK                    0x1
#define GFX_GAWBWBECR_WR_SHIFT                   0 
#define GFX_GAWBWBECR_WR_BIT                     0x1
#define GFX_GAWBWBECR_WR_BITWIDTH                1
// BTYPE bitfiled (RO) Reset=0
#define GFX_GAWBWBECR_BTYPE_MASK                 0x2
#define GFX_GAWBWBECR_BTYPE_SHIFT                1 
#define GFX_GAWBWBECR_BTYPE_BIT                  0x1
#define GFX_GAWBWBECR_BTYPE_BITWIDTH             1
// BSIZE bitfiled (RO) Reset=0
#define GFX_GAWBWBECR_BSIZE_MASK                 0x1C
#define GFX_GAWBWBECR_BSIZE_SHIFT                2 
#define GFX_GAWBWBECR_BSIZE_BIT                  0x7
#define GFX_GAWBWBECR_BSIZE_BITWIDTH             3
// RTYPE bitfiled (RO) Reset=0
#define GFX_GAWBWBECR_RTYPE_MASK                 0x60
#define GFX_GAWBWBECR_RTYPE_SHIFT                5 
#define GFX_GAWBWBECR_RTYPE_BIT                  0x3
#define GFX_GAWBWBECR_RTYPE_BITWIDTH             2
// reserved2 bitfiled (RO) Reset=0
#define GFX_GAWBWBECR_RESERVED2_MASK             0x80
#define GFX_GAWBWBECR_RESERVED2_SHIFT            7 
#define GFX_GAWBWBECR_RESERVED2_BIT              0x1
#define GFX_GAWBWBECR_RESERVED2_BITWIDTH         1
// BEN bitfiled (RO) Reset=0
#define GFX_GAWBWBECR_BEN_MASK                   0xFF00
#define GFX_GAWBWBECR_BEN_SHIFT                  8 
#define GFX_GAWBWBECR_BEN_BIT                    0xFF
#define GFX_GAWBWBECR_BEN_BITWIDTH               8
// ID bitfiled (RO) Reset=0
#define GFX_GAWBWBECR_ID_MASK                    0xF0000
#define GFX_GAWBWBECR_ID_SHIFT                   16 
#define GFX_GAWBWBECR_ID_BIT                     0xF
#define GFX_GAWBWBECR_ID_BITWIDTH                4
// LEN bitfiled (RO) Reset=0
#define GFX_GAWBWBECR_LEN_MASK                   0xF00000
#define GFX_GAWBWBECR_LEN_SHIFT                  20 
#define GFX_GAWBWBECR_LEN_BIT                    0xF
#define GFX_GAWBWBECR_LEN_BITWIDTH               4
// reserved bitfiled (RO) Reset=0
#define GFX_GAWBWBECR_RESERVED_MASK              0xFF000000
#define GFX_GAWBWBECR_RESERVED_SHIFT             24 
#define GFX_GAWBWBECR_RESERVED_BIT               0xFF
#define GFX_GAWBWBECR_RESERVED_BITWIDTH          8
// GAMPR0LR Register
#define GFX_GAMPR0LR_OFS                         0x00000040
// reserved bitfiled (RO) Reset=0
#define GFX_GAMPR0LR_RESERVED_MASK               0xFFF
#define GFX_GAMPR0LR_RESERVED_SHIFT              0 
#define GFX_GAMPR0LR_RESERVED_BIT                0xFFF
#define GFX_GAMPR0LR_RESERVED_BITWIDTH           12
// MPR0L bitfiled (RW) Reset=0
#define GFX_GAMPR0LR_MPR0L_MASK                  0xFFFFF000
#define GFX_GAMPR0LR_MPR0L_SHIFT                 12 
#define GFX_GAMPR0LR_MPR0L_BIT                   0xFFFFF
#define GFX_GAMPR0LR_MPR0L_BITWIDTH              20
// GAMPR0HR Register
#define GFX_GAMPR0HR_OFS                         0x00000044
// reserved bitfiled (RO) Reset=0
#define GFX_GAMPR0HR_RESERVED_MASK               0xFFF
#define GFX_GAMPR0HR_RESERVED_SHIFT              0 
#define GFX_GAMPR0HR_RESERVED_BIT                0xFFF
#define GFX_GAMPR0HR_RESERVED_BITWIDTH           12
// MPR0H bitfiled (RW) Reset=11111111111111111111
#define GFX_GAMPR0HR_MPR0H_MASK                  0xFFFFF000
#define GFX_GAMPR0HR_MPR0H_SHIFT                 12 
#define GFX_GAMPR0HR_MPR0H_BIT                   0xFFFFF
#define GFX_GAMPR0HR_MPR0H_BITWIDTH              20
// GAMPR1LR Register
#define GFX_GAMPR1LR_OFS                         0x00000048
// reserved bitfiled (RO) Reset=0
#define GFX_GAMPR1LR_RESERVED_MASK               0xFFF
#define GFX_GAMPR1LR_RESERVED_SHIFT              0 
#define GFX_GAMPR1LR_RESERVED_BIT                0xFFF
#define GFX_GAMPR1LR_RESERVED_BITWIDTH           12
// MPR0L bitfiled (RW) Reset=0
#define GFX_GAMPR1LR_MPR0L_MASK                  0xFFFFF000
#define GFX_GAMPR1LR_MPR0L_SHIFT                 12 
#define GFX_GAMPR1LR_MPR0L_BIT                   0xFFFFF
#define GFX_GAMPR1LR_MPR0L_BITWIDTH              20
// GAMPR1HR Register
#define GFX_GAMPR1HR_OFS                         0x0000004C
// reserved bitfiled (RO) Reset=0
#define GFX_GAMPR1HR_RESERVED_MASK               0xFFF
#define GFX_GAMPR1HR_RESERVED_SHIFT              0 
#define GFX_GAMPR1HR_RESERVED_BIT                0xFFF
#define GFX_GAMPR1HR_RESERVED_BITWIDTH           12
// MPR0H bitfiled (RW) Reset=11111111111111111111
#define GFX_GAMPR1HR_MPR0H_MASK                  0xFFFFF000
#define GFX_GAMPR1HR_MPR0H_SHIFT                 12 
#define GFX_GAMPR1HR_MPR0H_BIT                   0xFFFFF
#define GFX_GAMPR1HR_MPR0H_BITWIDTH              20
// GAMPICR Register
#define GFX_GAMPICR_OFS                          0x00000050
// GAMPI bitfiled (RW) Reset=0
#define GFX_GAMPICR_GAMPI_MASK                   0x1
#define GFX_GAMPICR_GAMPI_SHIFT                  0 
#define GFX_GAMPICR_GAMPI_BIT                    0x1
#define GFX_GAMPICR_GAMPI_BITWIDTH               1
// GAMPCI bitfiled (RW) Reset=0
#define GFX_GAMPICR_GAMPCI_MASK                  0x2
#define GFX_GAMPICR_GAMPCI_SHIFT                 1 
#define GFX_GAMPICR_GAMPCI_BIT                   0x1
#define GFX_GAMPICR_GAMPCI_BITWIDTH              1
// reserved bitfiled (RO) Reset=0
#define GFX_GAMPICR_RESERVED_MASK                0xFFFFFFFC
#define GFX_GAMPICR_RESERVED_SHIFT               2 
#define GFX_GAMPICR_RESERVED_BIT                 0x3FFFFFFF
#define GFX_GAMPICR_RESERVED_BITWIDTH            30
// GAMPIMR Register
#define GFX_GAMPIMR_OFS                          0x00000054
// GAMPIM bitfiled (RW) Reset=0
#define GFX_GAMPIMR_GAMPIM_MASK                  0x1
#define GFX_GAMPIMR_GAMPIM_SHIFT                 0 
#define GFX_GAMPIMR_GAMPIM_BIT                   0x1
#define GFX_GAMPIMR_GAMPIM_BITWIDTH              1
// GAMPCIM bitfiled (RW) Reset=0
#define GFX_GAMPIMR_GAMPCIM_MASK                 0x2
#define GFX_GAMPIMR_GAMPCIM_SHIFT                1 
#define GFX_GAMPIMR_GAMPCIM_BIT                  0x1
#define GFX_GAMPIMR_GAMPCIM_BITWIDTH             1
// reserved bitfiled (RO) Reset=0
#define GFX_GAMPIMR_RESERVED_MASK                0xFFFFFFFC
#define GFX_GAMPIMR_RESERVED_SHIFT               2 
#define GFX_GAMPIMR_RESERVED_BIT                 0x3FFFFFFF
#define GFX_GAMPIMR_RESERVED_BITWIDTH            30
// GAMPACR Register
#define GFX_GAMPACR_OFS                          0x00000058
// reserved bitfiled (RO) Reset=0
#define GFX_GAMPACR_RESERVED_MASK                0x7
#define GFX_GAMPACR_RESERVED_SHIFT               0 
#define GFX_GAMPACR_RESERVED_BIT                 0x7
#define GFX_GAMPACR_RESERVED_BITWIDTH            3
// MPVA bitfiled (RO) Reset=0
#define GFX_GAMPACR_MPVA_MASK                    0xFFFFFFF8
#define GFX_GAMPACR_MPVA_SHIFT                   3 
#define GFX_GAMPACR_MPVA_BIT                     0x1FFFFFFF
#define GFX_GAMPACR_MPVA_BITWIDTH                29
// GAGPR0 Register
#define GFX_GAGPR0_OFS                           0x00000080
// GAGPR0 bitfiled (RW) Reset=0
#define GFX_GAGPR0_GAGPR0_MASK                   0xFFFFFFFF
#define GFX_GAGPR0_GAGPR0_SHIFT                  0 
#define GFX_GAGPR0_GAGPR0_BIT                    0xFFFFFFFF
#define GFX_GAGPR0_GAGPR0_BITWIDTH               32
// GAGPR1 Register
#define GFX_GAGPR1_OFS                           0x00000084
// GAGPR1 bitfiled (RW) Reset=0
#define GFX_GAGPR1_GAGPR1_MASK                   0xFFFFFFFF
#define GFX_GAGPR1_GAGPR1_SHIFT                  0 
#define GFX_GAGPR1_GAGPR1_BIT                    0xFFFFFFFF
#define GFX_GAGPR1_GAGPR1_BITWIDTH               32
// GAGPR2 Register
#define GFX_GAGPR2_OFS                           0x00000088
// GAGPR2 bitfiled (RW) Reset=0
#define GFX_GAGPR2_GAGPR2_MASK                   0xFFFFFFFF
#define GFX_GAGPR2_GAGPR2_SHIFT                  0 
#define GFX_GAGPR2_GAGPR2_BIT                    0xFFFFFFFF
#define GFX_GAGPR2_GAGPR2_BITWIDTH               32
// GAGPR3 Register
#define GFX_GAGPR3_OFS                           0x0000008C
// GAGPR3 bitfiled (RW) Reset=0
#define GFX_GAGPR3_GAGPR3_MASK                   0xFFFFFFFF
#define GFX_GAGPR3_GAGPR3_SHIFT                  0 
#define GFX_GAGPR3_GAGPR3_BIT                    0xFFFFFFFF
#define GFX_GAGPR3_GAGPR3_BITWIDTH               32
// GAGPR4 Register
#define GFX_GAGPR4_OFS                           0x00000090
// GAGPR4 bitfiled (RW) Reset=0
#define GFX_GAGPR4_GAGPR4_MASK                   0xFFFFFFFF
#define GFX_GAGPR4_GAGPR4_SHIFT                  0 
#define GFX_GAGPR4_GAGPR4_BIT                    0xFFFFFFFF
#define GFX_GAGPR4_GAGPR4_BITWIDTH               32
// GAGPR5 Register
#define GFX_GAGPR5_OFS                           0x00000094
// GAGPR5 bitfiled (RW) Reset=0
#define GFX_GAGPR5_GAGPR5_MASK                   0xFFFFFFFF
#define GFX_GAGPR5_GAGPR5_SHIFT                  0 
#define GFX_GAGPR5_GAGPR5_BIT                    0xFFFFFFFF
#define GFX_GAGPR5_GAGPR5_BITWIDTH               32
// GAGPR6 Register
#define GFX_GAGPR6_OFS                           0x00000098
// GAGPR6 bitfiled (RW) Reset=0
#define GFX_GAGPR6_GAGPR6_MASK                   0xFFFFFFFF
#define GFX_GAGPR6_GAGPR6_SHIFT                  0 
#define GFX_GAGPR6_GAGPR6_BIT                    0xFFFFFFFF
#define GFX_GAGPR6_GAGPR6_BITWIDTH               32
// GAGPR7 Register
#define GFX_GAGPR7_OFS                           0x0000009C
// GAGPR7 bitfiled (RW) Reset=0
#define GFX_GAGPR7_GAGPR7_MASK                   0xFFFFFFFF
#define GFX_GAGPR7_GAGPR7_SHIFT                  0 
#define GFX_GAGPR7_GAGPR7_BIT                    0xFFFFFFFF
#define GFX_GAGPR7_GAGPR7_BITWIDTH               32
// GAGPR8 Register
#define GFX_GAGPR8_OFS                           0x000000A0
// GAGPR8 bitfiled (RW) Reset=0
#define GFX_GAGPR8_GAGPR8_MASK                   0xFFFFFFFF
#define GFX_GAGPR8_GAGPR8_SHIFT                  0 
#define GFX_GAGPR8_GAGPR8_BIT                    0xFFFFFFFF
#define GFX_GAGPR8_GAGPR8_BITWIDTH               32
// GAGPR9 Register
#define GFX_GAGPR9_OFS                           0x000000A4
// GAGPR9 bitfiled (RW) Reset=0
#define GFX_GAGPR9_GAGPR9_MASK                   0xFFFFFFFF
#define GFX_GAGPR9_GAGPR9_SHIFT                  0 
#define GFX_GAGPR9_GAGPR9_BIT                    0xFFFFFFFF
#define GFX_GAGPR9_GAGPR9_BITWIDTH               32
// GAGPR10 Register
#define GFX_GAGPR10_OFS                          0x000000A8
// GAGPR10 bitfiled (RW) Reset=0
#define GFX_GAGPR10_GAGPR10_MASK                 0xFFFFFFFF
#define GFX_GAGPR10_GAGPR10_SHIFT                0 
#define GFX_GAGPR10_GAGPR10_BIT                  0xFFFFFFFF
#define GFX_GAGPR10_GAGPR10_BITWIDTH             32
// GAGPR11 Register
#define GFX_GAGPR11_OFS                          0x000000AC
// GAGPR11 bitfiled (RW) Reset=0
#define GFX_GAGPR11_GAGPR11_MASK                 0xFFFFFFFF
#define GFX_GAGPR11_GAGPR11_SHIFT                0 
#define GFX_GAGPR11_GAGPR11_BIT                  0xFFFFFFFF
#define GFX_GAGPR11_GAGPR11_BITWIDTH             32
// GAGPR12 Register
#define GFX_GAGPR12_OFS                          0x000000B0
// GAGPR12 bitfiled (RW) Reset=0
#define GFX_GAGPR12_GAGPR12_MASK                 0xFFFFFFFF
#define GFX_GAGPR12_GAGPR12_SHIFT                0 
#define GFX_GAGPR12_GAGPR12_BIT                  0xFFFFFFFF
#define GFX_GAGPR12_GAGPR12_BITWIDTH             32
// GAGPR13 Register
#define GFX_GAGPR13_OFS                          0x000000B4
// GAGPR13 bitfiled (RW) Reset=0
#define GFX_GAGPR13_GAGPR13_MASK                 0xFFFFFFFF
#define GFX_GAGPR13_GAGPR13_SHIFT                0 
#define GFX_GAGPR13_GAGPR13_BIT                  0xFFFFFFFF
#define GFX_GAGPR13_GAGPR13_BITWIDTH             32
// GAGPR14 Register
#define GFX_GAGPR14_OFS                          0x000000B8
// GAGPR14 bitfiled (RW) Reset=0
#define GFX_GAGPR14_GAGPR14_MASK                 0xFFFFFFFF
#define GFX_GAGPR14_GAGPR14_SHIFT                0 
#define GFX_GAGPR14_GAGPR14_BIT                  0xFFFFFFFF
#define GFX_GAGPR14_GAGPR14_BITWIDTH             32
// GAGPR15 Register
#define GFX_GAGPR15_OFS                          0x000000BC
// GAGPR15 bitfiled (RW) Reset=0
#define GFX_GAGPR15_GAGPR15_MASK                 0xFFFFFFFF
#define GFX_GAGPR15_GAGPR15_SHIFT                0 
#define GFX_GAGPR15_GAGPR15_BIT                  0xFFFFFFFF
#define GFX_GAGPR15_GAGPR15_BITWIDTH             32
// GAGPR16 Register
#define GFX_GAGPR16_OFS                          0x000000C0
// GAGPR16 bitfiled (RW) Reset=0
#define GFX_GAGPR16_GAGPR16_MASK                 0xFFFFFFFF
#define GFX_GAGPR16_GAGPR16_SHIFT                0 
#define GFX_GAGPR16_GAGPR16_BIT                  0xFFFFFFFF
#define GFX_GAGPR16_GAGPR16_BITWIDTH             32
// GAGPR17 Register
#define GFX_GAGPR17_OFS                          0x000000C4
// GAGPR17 bitfiled (RW) Reset=0
#define GFX_GAGPR17_GAGPR17_MASK                 0xFFFFFFFF
#define GFX_GAGPR17_GAGPR17_SHIFT                0 
#define GFX_GAGPR17_GAGPR17_BIT                  0xFFFFFFFF
#define GFX_GAGPR17_GAGPR17_BITWIDTH             32
// GAGPR18 Register
#define GFX_GAGPR18_OFS                          0x000000C8
// GAGPR18 bitfiled (RW) Reset=0
#define GFX_GAGPR18_GAGPR18_MASK                 0xFFFFFFFF
#define GFX_GAGPR18_GAGPR18_SHIFT                0 
#define GFX_GAGPR18_GAGPR18_BIT                  0xFFFFFFFF
#define GFX_GAGPR18_GAGPR18_BITWIDTH             32
// GAGPR19 Register
#define GFX_GAGPR19_OFS                          0x000000CC
// GAGPR19 bitfiled (RW) Reset=0
#define GFX_GAGPR19_GAGPR19_MASK                 0xFFFFFFFF
#define GFX_GAGPR19_GAGPR19_SHIFT                0 
#define GFX_GAGPR19_GAGPR19_BIT                  0xFFFFFFFF
#define GFX_GAGPR19_GAGPR19_BITWIDTH             32
// GAGPR20 Register
#define GFX_GAGPR20_OFS                          0x000000D0
// GAGPR20 bitfiled (RW) Reset=0
#define GFX_GAGPR20_GAGPR20_MASK                 0xFFFFFFFF
#define GFX_GAGPR20_GAGPR20_SHIFT                0 
#define GFX_GAGPR20_GAGPR20_BIT                  0xFFFFFFFF
#define GFX_GAGPR20_GAGPR20_BITWIDTH             32
// GAGPR21 Register
#define GFX_GAGPR21_OFS                          0x000000D4
// GAGPR21 bitfiled (RW) Reset=0
#define GFX_GAGPR21_GAGPR21_MASK                 0xFFFFFFFF
#define GFX_GAGPR21_GAGPR21_SHIFT                0 
#define GFX_GAGPR21_GAGPR21_BIT                  0xFFFFFFFF
#define GFX_GAGPR21_GAGPR21_BITWIDTH             32
// GAGPR22 Register
#define GFX_GAGPR22_OFS                          0x000000D8
// GAGPR22 bitfiled (RW) Reset=0
#define GFX_GAGPR22_GAGPR22_MASK                 0xFFFFFFFF
#define GFX_GAGPR22_GAGPR22_SHIFT                0 
#define GFX_GAGPR22_GAGPR22_BIT                  0xFFFFFFFF
#define GFX_GAGPR22_GAGPR22_BITWIDTH             32
// GAGPR23 Register
#define GFX_GAGPR23_OFS                          0x000000DC
// GAGPR23 bitfiled (RW) Reset=0
#define GFX_GAGPR23_GAGPR23_MASK                 0xFFFFFFFF
#define GFX_GAGPR23_GAGPR23_SHIFT                0 
#define GFX_GAGPR23_GAGPR23_BIT                  0xFFFFFFFF
#define GFX_GAGPR23_GAGPR23_BITWIDTH             32
// GAGPR24 Register
#define GFX_GAGPR24_OFS                          0x000000E0
// GAGPR24 bitfiled (RW) Reset=0
#define GFX_GAGPR24_GAGPR24_MASK                 0xFFFFFFFF
#define GFX_GAGPR24_GAGPR24_SHIFT                0 
#define GFX_GAGPR24_GAGPR24_BIT                  0xFFFFFFFF
#define GFX_GAGPR24_GAGPR24_BITWIDTH             32
// GAGPR25 Register
#define GFX_GAGPR25_OFS                          0x000000E4
// GAGPR25 bitfiled (RW) Reset=0
#define GFX_GAGPR25_GAGPR25_MASK                 0xFFFFFFFF
#define GFX_GAGPR25_GAGPR25_SHIFT                0 
#define GFX_GAGPR25_GAGPR25_BIT                  0xFFFFFFFF
#define GFX_GAGPR25_GAGPR25_BITWIDTH             32
// GAGPR26 Register
#define GFX_GAGPR26_OFS                          0x000000E8
// GAGPR26 bitfiled (RW) Reset=0
#define GFX_GAGPR26_GAGPR26_MASK                 0xFFFFFFFF
#define GFX_GAGPR26_GAGPR26_SHIFT                0 
#define GFX_GAGPR26_GAGPR26_BIT                  0xFFFFFFFF
#define GFX_GAGPR26_GAGPR26_BITWIDTH             32
// GAGPR27 Register
#define GFX_GAGPR27_OFS                          0x000000EC
// GAGPR27 bitfiled (RW) Reset=0
#define GFX_GAGPR27_GAGPR27_MASK                 0xFFFFFFFF
#define GFX_GAGPR27_GAGPR27_SHIFT                0 
#define GFX_GAGPR27_GAGPR27_BIT                  0xFFFFFFFF
#define GFX_GAGPR27_GAGPR27_BITWIDTH             32
// GAGPR28 Register
#define GFX_GAGPR28_OFS                          0x000000F0
// GAGPR28 bitfiled (RW) Reset=0
#define GFX_GAGPR28_GAGPR28_MASK                 0xFFFFFFFF
#define GFX_GAGPR28_GAGPR28_SHIFT                0 
#define GFX_GAGPR28_GAGPR28_BIT                  0xFFFFFFFF
#define GFX_GAGPR28_GAGPR28_BITWIDTH             32
// GAGPR29 Register
#define GFX_GAGPR29_OFS                          0x000000F4
// GAGPR29 bitfiled (RW) Reset=0
#define GFX_GAGPR29_GAGPR29_MASK                 0xFFFFFFFF
#define GFX_GAGPR29_GAGPR29_SHIFT                0 
#define GFX_GAGPR29_GAGPR29_BIT                  0xFFFFFFFF
#define GFX_GAGPR29_GAGPR29_BITWIDTH             32
// GAGPR30 Register
#define GFX_GAGPR30_OFS                          0x000000F8
// GAGPR30 bitfiled (RW) Reset=0
#define GFX_GAGPR30_GAGPR30_MASK                 0xFFFFFFFF
#define GFX_GAGPR30_GAGPR30_SHIFT                0 
#define GFX_GAGPR30_GAGPR30_BIT                  0xFFFFFFFF
#define GFX_GAGPR30_GAGPR30_BITWIDTH             32
// GAGPR31 Register
#define GFX_GAGPR31_OFS                          0x000000FC
// GAGPR31 bitfiled (RW) Reset=0
#define GFX_GAGPR31_GAGPR31_MASK                 0xFFFFFFFF
#define GFX_GAGPR31_GAGPR31_SHIFT                0 
#define GFX_GAGPR31_GAGPR31_BIT                  0xFFFFFFFF
#define GFX_GAGPR31_GAGPR31_BITWIDTH             32
// GACMDL Register
#define GFX_GACMDL_OFS                           0x00000100
// GACMDL bitfiled (RW) Reset=0
#define GFX_GACMDL_GACMDL_MASK                   0xFFFFFFFF
#define GFX_GACMDL_GACMDL_SHIFT                  0 
#define GFX_GACMDL_GACMDL_BIT                    0xFFFFFFFF
#define GFX_GACMDL_GACMDL_BITWIDTH               32
// GACMDH Register
#define GFX_GACMDH_OFS                           0x00000104
// GACMDH bitfiled (RW) Reset=0
#define GFX_GACMDH_GACMDH_MASK                   0xFFFFFFFF
#define GFX_GACMDH_GACMDH_SHIFT                  0 
#define GFX_GACMDH_GACMDH_BIT                    0xFFFFFFFF
#define GFX_GACMDH_GACMDH_BITWIDTH               32
// DEFC0 Register
#define GFX_DEFC0_OFS                            0x00000200
// FC3 bitfiled (RW) Reset=0
#define GFX_DEFC0_FC3_MASK                       0xFF
#define GFX_DEFC0_FC3_SHIFT                      0 
#define GFX_DEFC0_FC3_BIT                        0xFF
#define GFX_DEFC0_FC3_BITWIDTH                   8
// FC2 bitfiled (RW) Reset=0
#define GFX_DEFC0_FC2_MASK                       0xFF00
#define GFX_DEFC0_FC2_SHIFT                      8 
#define GFX_DEFC0_FC2_BIT                        0xFF
#define GFX_DEFC0_FC2_BITWIDTH                   8
// FC1 bitfiled (RW) Reset=0
#define GFX_DEFC0_FC1_MASK                       0xFF0000
#define GFX_DEFC0_FC1_SHIFT                      16 
#define GFX_DEFC0_FC1_BIT                        0xFF
#define GFX_DEFC0_FC1_BITWIDTH                   8
// FC0 bitfiled (RW) Reset=0
#define GFX_DEFC0_FC0_MASK                       0xFF000000
#define GFX_DEFC0_FC0_SHIFT                      24 
#define GFX_DEFC0_FC0_BIT                        0xFF
#define GFX_DEFC0_FC0_BITWIDTH                   8
// DEFC1 Register
#define GFX_DEFC1_OFS                            0x00000204
// FC7 bitfiled (RW) Reset=0
#define GFX_DEFC1_FC7_MASK                       0xFF
#define GFX_DEFC1_FC7_SHIFT                      0 
#define GFX_DEFC1_FC7_BIT                        0xFF
#define GFX_DEFC1_FC7_BITWIDTH                   8
// FC6 bitfiled (RW) Reset=0
#define GFX_DEFC1_FC6_MASK                       0xFF00
#define GFX_DEFC1_FC6_SHIFT                      8 
#define GFX_DEFC1_FC6_BIT                        0xFF
#define GFX_DEFC1_FC6_BITWIDTH                   8
// FC5 bitfiled (RW) Reset=0
#define GFX_DEFC1_FC5_MASK                       0xFF0000
#define GFX_DEFC1_FC5_SHIFT                      16 
#define GFX_DEFC1_FC5_BIT                        0xFF
#define GFX_DEFC1_FC5_BITWIDTH                   8
// FC4 bitfiled (RW) Reset=0
#define GFX_DEFC1_FC4_MASK                       0xFF000000
#define GFX_DEFC1_FC4_SHIFT                      24 
#define GFX_DEFC1_FC4_BIT                        0xFF
#define GFX_DEFC1_FC4_BITWIDTH                   8
// DEFC2 Register
#define GFX_DEFC2_OFS                            0x00000208
// FC11 bitfiled (RW) Reset=0
#define GFX_DEFC2_FC11_MASK                      0xFF
#define GFX_DEFC2_FC11_SHIFT                     0 
#define GFX_DEFC2_FC11_BIT                       0xFF
#define GFX_DEFC2_FC11_BITWIDTH                  8
// FC10 bitfiled (RW) Reset=0
#define GFX_DEFC2_FC10_MASK                      0xFF00
#define GFX_DEFC2_FC10_SHIFT                     8 
#define GFX_DEFC2_FC10_BIT                       0xFF
#define GFX_DEFC2_FC10_BITWIDTH                  8
// FC9 bitfiled (RW) Reset=0
#define GFX_DEFC2_FC9_MASK                       0xFF0000
#define GFX_DEFC2_FC9_SHIFT                      16 
#define GFX_DEFC2_FC9_BIT                        0xFF
#define GFX_DEFC2_FC9_BITWIDTH                   8
// FC8 bitfiled (RW) Reset=0
#define GFX_DEFC2_FC8_MASK                       0xFF000000
#define GFX_DEFC2_FC8_SHIFT                      24 
#define GFX_DEFC2_FC8_BIT                        0xFF
#define GFX_DEFC2_FC8_BITWIDTH                   8
// DEFC3 Register
#define GFX_DEFC3_OFS                            0x0000020C
// FC15 bitfiled (RW) Reset=0
#define GFX_DEFC3_FC15_MASK                      0xFF
#define GFX_DEFC3_FC15_SHIFT                     0 
#define GFX_DEFC3_FC15_BIT                       0xFF
#define GFX_DEFC3_FC15_BITWIDTH                  8
// FC14 bitfiled (RW) Reset=0
#define GFX_DEFC3_FC14_MASK                      0xFF00
#define GFX_DEFC3_FC14_SHIFT                     8 
#define GFX_DEFC3_FC14_BIT                       0xFF
#define GFX_DEFC3_FC14_BITWIDTH                  8
// FC13 bitfiled (RW) Reset=0
#define GFX_DEFC3_FC13_MASK                      0xFF0000
#define GFX_DEFC3_FC13_SHIFT                     16 
#define GFX_DEFC3_FC13_BIT                       0xFF
#define GFX_DEFC3_FC13_BITWIDTH                  8
// FC12 bitfiled (RW) Reset=0
#define GFX_DEFC3_FC12_MASK                      0xFF000000
#define GFX_DEFC3_FC12_SHIFT                     24 
#define GFX_DEFC3_FC12_BIT                       0xFF
#define GFX_DEFC3_FC12_BITWIDTH                  8
// DEFC4 Register
#define GFX_DEFC4_OFS                            0x00000210
// FC19 bitfiled (RW) Reset=0
#define GFX_DEFC4_FC19_MASK                      0xFF
#define GFX_DEFC4_FC19_SHIFT                     0 
#define GFX_DEFC4_FC19_BIT                       0xFF
#define GFX_DEFC4_FC19_BITWIDTH                  8
// FC18 bitfiled (RW) Reset=0
#define GFX_DEFC4_FC18_MASK                      0xFF00
#define GFX_DEFC4_FC18_SHIFT                     8 
#define GFX_DEFC4_FC18_BIT                       0xFF
#define GFX_DEFC4_FC18_BITWIDTH                  8
// FC17 bitfiled (RW) Reset=0
#define GFX_DEFC4_FC17_MASK                      0xFF0000
#define GFX_DEFC4_FC17_SHIFT                     16 
#define GFX_DEFC4_FC17_BIT                       0xFF
#define GFX_DEFC4_FC17_BITWIDTH                  8
// FC16 bitfiled (RW) Reset=0
#define GFX_DEFC4_FC16_MASK                      0xFF000000
#define GFX_DEFC4_FC16_SHIFT                     24 
#define GFX_DEFC4_FC16_BIT                       0xFF
#define GFX_DEFC4_FC16_BITWIDTH                  8
// DEFC5 Register
#define GFX_DEFC5_OFS                            0x00000214
// FC23 bitfiled (RW) Reset=0
#define GFX_DEFC5_FC23_MASK                      0xFF
#define GFX_DEFC5_FC23_SHIFT                     0 
#define GFX_DEFC5_FC23_BIT                       0xFF
#define GFX_DEFC5_FC23_BITWIDTH                  8
// FC22 bitfiled (RW) Reset=0
#define GFX_DEFC5_FC22_MASK                      0xFF00
#define GFX_DEFC5_FC22_SHIFT                     8 
#define GFX_DEFC5_FC22_BIT                       0xFF
#define GFX_DEFC5_FC22_BITWIDTH                  8
// FC21 bitfiled (RW) Reset=0
#define GFX_DEFC5_FC21_MASK                      0xFF0000
#define GFX_DEFC5_FC21_SHIFT                     16 
#define GFX_DEFC5_FC21_BIT                       0xFF
#define GFX_DEFC5_FC21_BITWIDTH                  8
// FC20 bitfiled (RW) Reset=0
#define GFX_DEFC5_FC20_MASK                      0xFF000000
#define GFX_DEFC5_FC20_SHIFT                     24 
#define GFX_DEFC5_FC20_BIT                       0xFF
#define GFX_DEFC5_FC20_BITWIDTH                  8
// DEFC6 Register
#define GFX_DEFC6_OFS                            0x00000218
// FC27 bitfiled (RW) Reset=0
#define GFX_DEFC6_FC27_MASK                      0xFF
#define GFX_DEFC6_FC27_SHIFT                     0 
#define GFX_DEFC6_FC27_BIT                       0xFF
#define GFX_DEFC6_FC27_BITWIDTH                  8
// FC26 bitfiled (RW) Reset=0
#define GFX_DEFC6_FC26_MASK                      0xFF00
#define GFX_DEFC6_FC26_SHIFT                     8 
#define GFX_DEFC6_FC26_BIT                       0xFF
#define GFX_DEFC6_FC26_BITWIDTH                  8
// FC25 bitfiled (RW) Reset=0
#define GFX_DEFC6_FC25_MASK                      0xFF0000
#define GFX_DEFC6_FC25_SHIFT                     16 
#define GFX_DEFC6_FC25_BIT                       0xFF
#define GFX_DEFC6_FC25_BITWIDTH                  8
// FC24 bitfiled (RW) Reset=0
#define GFX_DEFC6_FC24_MASK                      0xFF000000
#define GFX_DEFC6_FC24_SHIFT                     24 
#define GFX_DEFC6_FC24_BIT                       0xFF
#define GFX_DEFC6_FC24_BITWIDTH                  8
// DEFC7 Register
#define GFX_DEFC7_OFS                            0x0000021C
// FC31 bitfiled (RW) Reset=0
#define GFX_DEFC7_FC31_MASK                      0xFF
#define GFX_DEFC7_FC31_SHIFT                     0 
#define GFX_DEFC7_FC31_BIT                       0xFF
#define GFX_DEFC7_FC31_BITWIDTH                  8
// FC30 bitfiled (RW) Reset=0
#define GFX_DEFC7_FC30_MASK                      0xFF00
#define GFX_DEFC7_FC30_SHIFT                     8 
#define GFX_DEFC7_FC30_BIT                       0xFF
#define GFX_DEFC7_FC30_BITWIDTH                  8
// FC29 bitfiled (RW) Reset=0
#define GFX_DEFC7_FC29_MASK                      0xFF0000
#define GFX_DEFC7_FC29_SHIFT                     16 
#define GFX_DEFC7_FC29_BIT                       0xFF
#define GFX_DEFC7_FC29_BITWIDTH                  8
// FC28 bitfiled (RW) Reset=0
#define GFX_DEFC7_FC28_MASK                      0xFF000000
#define GFX_DEFC7_FC28_SHIFT                     24 
#define GFX_DEFC7_FC28_BIT                       0xFF
#define GFX_DEFC7_FC28_BITWIDTH                  8
// DEFC8 Register
#define GFX_DEFC8_OFS                            0x00000220
// FC35 bitfiled (RW) Reset=0
#define GFX_DEFC8_FC35_MASK                      0xFF
#define GFX_DEFC8_FC35_SHIFT                     0 
#define GFX_DEFC8_FC35_BIT                       0xFF
#define GFX_DEFC8_FC35_BITWIDTH                  8
// FC34 bitfiled (RW) Reset=0
#define GFX_DEFC8_FC34_MASK                      0xFF00
#define GFX_DEFC8_FC34_SHIFT                     8 
#define GFX_DEFC8_FC34_BIT                       0xFF
#define GFX_DEFC8_FC34_BITWIDTH                  8
// FC33 bitfiled (RW) Reset=0
#define GFX_DEFC8_FC33_MASK                      0xFF0000
#define GFX_DEFC8_FC33_SHIFT                     16 
#define GFX_DEFC8_FC33_BIT                       0xFF
#define GFX_DEFC8_FC33_BITWIDTH                  8
// FC32 bitfiled (RW) Reset=0
#define GFX_DEFC8_FC32_MASK                      0xFF000000
#define GFX_DEFC8_FC32_SHIFT                     24 
#define GFX_DEFC8_FC32_BIT                       0xFF
#define GFX_DEFC8_FC32_BITWIDTH                  8
// DEFC9 Register
#define GFX_DEFC9_OFS                            0x00000224
// FC39 bitfiled (RW) Reset=0
#define GFX_DEFC9_FC39_MASK                      0xFF
#define GFX_DEFC9_FC39_SHIFT                     0 
#define GFX_DEFC9_FC39_BIT                       0xFF
#define GFX_DEFC9_FC39_BITWIDTH                  8
// FC38 bitfiled (RW) Reset=0
#define GFX_DEFC9_FC38_MASK                      0xFF00
#define GFX_DEFC9_FC38_SHIFT                     8 
#define GFX_DEFC9_FC38_BIT                       0xFF
#define GFX_DEFC9_FC38_BITWIDTH                  8
// FC37 bitfiled (RW) Reset=0
#define GFX_DEFC9_FC37_MASK                      0xFF0000
#define GFX_DEFC9_FC37_SHIFT                     16 
#define GFX_DEFC9_FC37_BIT                       0xFF
#define GFX_DEFC9_FC37_BITWIDTH                  8
// FC36 bitfiled (RW) Reset=0
#define GFX_DEFC9_FC36_MASK                      0xFF000000
#define GFX_DEFC9_FC36_SHIFT                     24 
#define GFX_DEFC9_FC36_BIT                       0xFF
#define GFX_DEFC9_FC36_BITWIDTH                  8
// DEFC10 Register
#define GFX_DEFC10_OFS                           0x00000228
// FC43 bitfiled (RW) Reset=0
#define GFX_DEFC10_FC43_MASK                     0xFF
#define GFX_DEFC10_FC43_SHIFT                    0 
#define GFX_DEFC10_FC43_BIT                      0xFF
#define GFX_DEFC10_FC43_BITWIDTH                 8
// FC42 bitfiled (RW) Reset=0
#define GFX_DEFC10_FC42_MASK                     0xFF00
#define GFX_DEFC10_FC42_SHIFT                    8 
#define GFX_DEFC10_FC42_BIT                      0xFF
#define GFX_DEFC10_FC42_BITWIDTH                 8
// FC41 bitfiled (RW) Reset=0
#define GFX_DEFC10_FC41_MASK                     0xFF0000
#define GFX_DEFC10_FC41_SHIFT                    16 
#define GFX_DEFC10_FC41_BIT                      0xFF
#define GFX_DEFC10_FC41_BITWIDTH                 8
// FC40 bitfiled (RW) Reset=0
#define GFX_DEFC10_FC40_MASK                     0xFF000000
#define GFX_DEFC10_FC40_SHIFT                    24 
#define GFX_DEFC10_FC40_BIT                      0xFF
#define GFX_DEFC10_FC40_BITWIDTH                 8
// DEFC11 Register
#define GFX_DEFC11_OFS                           0x0000022C
// FC47 bitfiled (RW) Reset=0
#define GFX_DEFC11_FC47_MASK                     0xFF
#define GFX_DEFC11_FC47_SHIFT                    0 
#define GFX_DEFC11_FC47_BIT                      0xFF
#define GFX_DEFC11_FC47_BITWIDTH                 8
// FC46 bitfiled (RW) Reset=0
#define GFX_DEFC11_FC46_MASK                     0xFF00
#define GFX_DEFC11_FC46_SHIFT                    8 
#define GFX_DEFC11_FC46_BIT                      0xFF
#define GFX_DEFC11_FC46_BITWIDTH                 8
// FC45 bitfiled (RW) Reset=0
#define GFX_DEFC11_FC45_MASK                     0xFF0000
#define GFX_DEFC11_FC45_SHIFT                    16 
#define GFX_DEFC11_FC45_BIT                      0xFF
#define GFX_DEFC11_FC45_BITWIDTH                 8
// FC44 bitfiled (RW) Reset=0
#define GFX_DEFC11_FC44_MASK                     0xFF000000
#define GFX_DEFC11_FC44_SHIFT                    24 
#define GFX_DEFC11_FC44_BIT                      0xFF
#define GFX_DEFC11_FC44_BITWIDTH                 8
// DEFC12 Register
#define GFX_DEFC12_OFS                           0x00000230
// FC51 bitfiled (RW) Reset=0
#define GFX_DEFC12_FC51_MASK                     0xFF
#define GFX_DEFC12_FC51_SHIFT                    0 
#define GFX_DEFC12_FC51_BIT                      0xFF
#define GFX_DEFC12_FC51_BITWIDTH                 8
// FC50 bitfiled (RW) Reset=0
#define GFX_DEFC12_FC50_MASK                     0xFF00
#define GFX_DEFC12_FC50_SHIFT                    8 
#define GFX_DEFC12_FC50_BIT                      0xFF
#define GFX_DEFC12_FC50_BITWIDTH                 8
// FC49 bitfiled (RW) Reset=0
#define GFX_DEFC12_FC49_MASK                     0xFF0000
#define GFX_DEFC12_FC49_SHIFT                    16 
#define GFX_DEFC12_FC49_BIT                      0xFF
#define GFX_DEFC12_FC49_BITWIDTH                 8
// FC48 bitfiled (RW) Reset=0
#define GFX_DEFC12_FC48_MASK                     0xFF000000
#define GFX_DEFC12_FC48_SHIFT                    24 
#define GFX_DEFC12_FC48_BIT                      0xFF
#define GFX_DEFC12_FC48_BITWIDTH                 8
// DEFC13 Register
#define GFX_DEFC13_OFS                           0x00000234
// FC55 bitfiled (RW) Reset=0
#define GFX_DEFC13_FC55_MASK                     0xFF
#define GFX_DEFC13_FC55_SHIFT                    0 
#define GFX_DEFC13_FC55_BIT                      0xFF
#define GFX_DEFC13_FC55_BITWIDTH                 8
// FC54 bitfiled (RW) Reset=0
#define GFX_DEFC13_FC54_MASK                     0xFF00
#define GFX_DEFC13_FC54_SHIFT                    8 
#define GFX_DEFC13_FC54_BIT                      0xFF
#define GFX_DEFC13_FC54_BITWIDTH                 8
// FC53 bitfiled (RW) Reset=0
#define GFX_DEFC13_FC53_MASK                     0xFF0000
#define GFX_DEFC13_FC53_SHIFT                    16 
#define GFX_DEFC13_FC53_BIT                      0xFF
#define GFX_DEFC13_FC53_BITWIDTH                 8
// FC52 bitfiled (RW) Reset=0
#define GFX_DEFC13_FC52_MASK                     0xFF000000
#define GFX_DEFC13_FC52_SHIFT                    24 
#define GFX_DEFC13_FC52_BIT                      0xFF
#define GFX_DEFC13_FC52_BITWIDTH                 8
// DEFC14 Register
#define GFX_DEFC14_OFS                           0x00000238
// FC59 bitfiled (RW) Reset=0
#define GFX_DEFC14_FC59_MASK                     0xFF
#define GFX_DEFC14_FC59_SHIFT                    0 
#define GFX_DEFC14_FC59_BIT                      0xFF
#define GFX_DEFC14_FC59_BITWIDTH                 8
// FC58 bitfiled (RW) Reset=0
#define GFX_DEFC14_FC58_MASK                     0xFF00
#define GFX_DEFC14_FC58_SHIFT                    8 
#define GFX_DEFC14_FC58_BIT                      0xFF
#define GFX_DEFC14_FC58_BITWIDTH                 8
// FC57 bitfiled (RW) Reset=0
#define GFX_DEFC14_FC57_MASK                     0xFF0000
#define GFX_DEFC14_FC57_SHIFT                    16 
#define GFX_DEFC14_FC57_BIT                      0xFF
#define GFX_DEFC14_FC57_BITWIDTH                 8
// FC56 bitfiled (RW) Reset=0
#define GFX_DEFC14_FC56_MASK                     0xFF000000
#define GFX_DEFC14_FC56_SHIFT                    24 
#define GFX_DEFC14_FC56_BIT                      0xFF
#define GFX_DEFC14_FC56_BITWIDTH                 8
// DEFC15 Register
#define GFX_DEFC15_OFS                           0x0000023C
// FC63 bitfiled (RW) Reset=0
#define GFX_DEFC15_FC63_MASK                     0xFF
#define GFX_DEFC15_FC63_SHIFT                    0 
#define GFX_DEFC15_FC63_BIT                      0xFF
#define GFX_DEFC15_FC63_BITWIDTH                 8
// FC62 bitfiled (RW) Reset=0
#define GFX_DEFC15_FC62_MASK                     0xFF00
#define GFX_DEFC15_FC62_SHIFT                    8 
#define GFX_DEFC15_FC62_BIT                      0xFF
#define GFX_DEFC15_FC62_BITWIDTH                 8
// FC61 bitfiled (RW) Reset=0
#define GFX_DEFC15_FC61_MASK                     0xFF0000
#define GFX_DEFC15_FC61_SHIFT                    16 
#define GFX_DEFC15_FC61_BIT                      0xFF
#define GFX_DEFC15_FC61_BITWIDTH                 8
// FC60 bitfiled (RW) Reset=0
#define GFX_DEFC15_FC60_MASK                     0xFF000000
#define GFX_DEFC15_FC60_SHIFT                    24 
#define GFX_DEFC15_FC60_BIT                      0xFF
#define GFX_DEFC15_FC60_BITWIDTH                 8
// DEFC16 Register
#define GFX_DEFC16_OFS                           0x00000240
// FC67 bitfiled (RW) Reset=0
#define GFX_DEFC16_FC67_MASK                     0xFF
#define GFX_DEFC16_FC67_SHIFT                    0 
#define GFX_DEFC16_FC67_BIT                      0xFF
#define GFX_DEFC16_FC67_BITWIDTH                 8
// FC66 bitfiled (RW) Reset=0
#define GFX_DEFC16_FC66_MASK                     0xFF00
#define GFX_DEFC16_FC66_SHIFT                    8 
#define GFX_DEFC16_FC66_BIT                      0xFF
#define GFX_DEFC16_FC66_BITWIDTH                 8
// FC65 bitfiled (RW) Reset=0
#define GFX_DEFC16_FC65_MASK                     0xFF0000
#define GFX_DEFC16_FC65_SHIFT                    16 
#define GFX_DEFC16_FC65_BIT                      0xFF
#define GFX_DEFC16_FC65_BITWIDTH                 8
// FC64 bitfiled (RW) Reset=0
#define GFX_DEFC16_FC64_MASK                     0xFF000000
#define GFX_DEFC16_FC64_SHIFT                    24 
#define GFX_DEFC16_FC64_BIT                      0xFF
#define GFX_DEFC16_FC64_BITWIDTH                 8
// DEFC17 Register
#define GFX_DEFC17_OFS                           0x00000244
// FC71 bitfiled (RW) Reset=0
#define GFX_DEFC17_FC71_MASK                     0xFF
#define GFX_DEFC17_FC71_SHIFT                    0 
#define GFX_DEFC17_FC71_BIT                      0xFF
#define GFX_DEFC17_FC71_BITWIDTH                 8
// FC70 bitfiled (RW) Reset=0
#define GFX_DEFC17_FC70_MASK                     0xFF00
#define GFX_DEFC17_FC70_SHIFT                    8 
#define GFX_DEFC17_FC70_BIT                      0xFF
#define GFX_DEFC17_FC70_BITWIDTH                 8
// FC69 bitfiled (RW) Reset=0
#define GFX_DEFC17_FC69_MASK                     0xFF0000
#define GFX_DEFC17_FC69_SHIFT                    16 
#define GFX_DEFC17_FC69_BIT                      0xFF
#define GFX_DEFC17_FC69_BITWIDTH                 8
// FC68 bitfiled (RW) Reset=0
#define GFX_DEFC17_FC68_MASK                     0xFF000000
#define GFX_DEFC17_FC68_SHIFT                    24 
#define GFX_DEFC17_FC68_BIT                      0xFF
#define GFX_DEFC17_FC68_BITWIDTH                 8
// DEFC18 Register
#define GFX_DEFC18_OFS                           0x00000248
// FC75 bitfiled (RW) Reset=0
#define GFX_DEFC18_FC75_MASK                     0xFF
#define GFX_DEFC18_FC75_SHIFT                    0 
#define GFX_DEFC18_FC75_BIT                      0xFF
#define GFX_DEFC18_FC75_BITWIDTH                 8
// FC74 bitfiled (RW) Reset=0
#define GFX_DEFC18_FC74_MASK                     0xFF00
#define GFX_DEFC18_FC74_SHIFT                    8 
#define GFX_DEFC18_FC74_BIT                      0xFF
#define GFX_DEFC18_FC74_BITWIDTH                 8
// FC73 bitfiled (RW) Reset=0
#define GFX_DEFC18_FC73_MASK                     0xFF0000
#define GFX_DEFC18_FC73_SHIFT                    16 
#define GFX_DEFC18_FC73_BIT                      0xFF
#define GFX_DEFC18_FC73_BITWIDTH                 8
// FC72 bitfiled (RW) Reset=0
#define GFX_DEFC18_FC72_MASK                     0xFF000000
#define GFX_DEFC18_FC72_SHIFT                    24 
#define GFX_DEFC18_FC72_BIT                      0xFF
#define GFX_DEFC18_FC72_BITWIDTH                 8
// DEFC19 Register
#define GFX_DEFC19_OFS                           0x0000024C
// FC79 bitfiled (RW) Reset=0
#define GFX_DEFC19_FC79_MASK                     0xFF
#define GFX_DEFC19_FC79_SHIFT                    0 
#define GFX_DEFC19_FC79_BIT                      0xFF
#define GFX_DEFC19_FC79_BITWIDTH                 8
// FC78 bitfiled (RW) Reset=0
#define GFX_DEFC19_FC78_MASK                     0xFF00
#define GFX_DEFC19_FC78_SHIFT                    8 
#define GFX_DEFC19_FC78_BIT                      0xFF
#define GFX_DEFC19_FC78_BITWIDTH                 8
// FC77 bitfiled (RW) Reset=0
#define GFX_DEFC19_FC77_MASK                     0xFF0000
#define GFX_DEFC19_FC77_SHIFT                    16 
#define GFX_DEFC19_FC77_BIT                      0xFF
#define GFX_DEFC19_FC77_BITWIDTH                 8
// FC76 bitfiled (RW) Reset=0
#define GFX_DEFC19_FC76_MASK                     0xFF000000
#define GFX_DEFC19_FC76_SHIFT                    24 
#define GFX_DEFC19_FC76_BIT                      0xFF
#define GFX_DEFC19_FC76_BITWIDTH                 8
// DEFC20 Register
#define GFX_DEFC20_OFS                           0x00000250
// FC83 bitfiled (RW) Reset=0
#define GFX_DEFC20_FC83_MASK                     0xFF
#define GFX_DEFC20_FC83_SHIFT                    0 
#define GFX_DEFC20_FC83_BIT                      0xFF
#define GFX_DEFC20_FC83_BITWIDTH                 8
// FC82 bitfiled (RW) Reset=0
#define GFX_DEFC20_FC82_MASK                     0xFF00
#define GFX_DEFC20_FC82_SHIFT                    8 
#define GFX_DEFC20_FC82_BIT                      0xFF
#define GFX_DEFC20_FC82_BITWIDTH                 8
// FC81 bitfiled (RW) Reset=0
#define GFX_DEFC20_FC81_MASK                     0xFF0000
#define GFX_DEFC20_FC81_SHIFT                    16 
#define GFX_DEFC20_FC81_BIT                      0xFF
#define GFX_DEFC20_FC81_BITWIDTH                 8
// FC80 bitfiled (RW) Reset=0
#define GFX_DEFC20_FC80_MASK                     0xFF000000
#define GFX_DEFC20_FC80_SHIFT                    24 
#define GFX_DEFC20_FC80_BIT                      0xFF
#define GFX_DEFC20_FC80_BITWIDTH                 8
// DEFC21 Register
#define GFX_DEFC21_OFS                           0x00000254
// FC87 bitfiled (RW) Reset=0
#define GFX_DEFC21_FC87_MASK                     0xFF
#define GFX_DEFC21_FC87_SHIFT                    0 
#define GFX_DEFC21_FC87_BIT                      0xFF
#define GFX_DEFC21_FC87_BITWIDTH                 8
// FC86 bitfiled (RW) Reset=0
#define GFX_DEFC21_FC86_MASK                     0xFF00
#define GFX_DEFC21_FC86_SHIFT                    8 
#define GFX_DEFC21_FC86_BIT                      0xFF
#define GFX_DEFC21_FC86_BITWIDTH                 8
// FC85 bitfiled (RW) Reset=0
#define GFX_DEFC21_FC85_MASK                     0xFF0000
#define GFX_DEFC21_FC85_SHIFT                    16 
#define GFX_DEFC21_FC85_BIT                      0xFF
#define GFX_DEFC21_FC85_BITWIDTH                 8
// FC84 bitfiled (RW) Reset=0
#define GFX_DEFC21_FC84_MASK                     0xFF000000
#define GFX_DEFC21_FC84_SHIFT                    24 
#define GFX_DEFC21_FC84_BIT                      0xFF
#define GFX_DEFC21_FC84_BITWIDTH                 8
// DEFC22 Register
#define GFX_DEFC22_OFS                           0x00000258
// FC91 bitfiled (RW) Reset=0
#define GFX_DEFC22_FC91_MASK                     0xFF
#define GFX_DEFC22_FC91_SHIFT                    0 
#define GFX_DEFC22_FC91_BIT                      0xFF
#define GFX_DEFC22_FC91_BITWIDTH                 8
// FC90 bitfiled (RW) Reset=0
#define GFX_DEFC22_FC90_MASK                     0xFF00
#define GFX_DEFC22_FC90_SHIFT                    8 
#define GFX_DEFC22_FC90_BIT                      0xFF
#define GFX_DEFC22_FC90_BITWIDTH                 8
// FC89 bitfiled (RW) Reset=0
#define GFX_DEFC22_FC89_MASK                     0xFF0000
#define GFX_DEFC22_FC89_SHIFT                    16 
#define GFX_DEFC22_FC89_BIT                      0xFF
#define GFX_DEFC22_FC89_BITWIDTH                 8
// FC88 bitfiled (RW) Reset=0
#define GFX_DEFC22_FC88_MASK                     0xFF000000
#define GFX_DEFC22_FC88_SHIFT                    24 
#define GFX_DEFC22_FC88_BIT                      0xFF
#define GFX_DEFC22_FC88_BITWIDTH                 8
// DEFC23 Register
#define GFX_DEFC23_OFS                           0x0000025C
// FC95 bitfiled (RW) Reset=0
#define GFX_DEFC23_FC95_MASK                     0xFF
#define GFX_DEFC23_FC95_SHIFT                    0 
#define GFX_DEFC23_FC95_BIT                      0xFF
#define GFX_DEFC23_FC95_BITWIDTH                 8
// FC94 bitfiled (RW) Reset=0
#define GFX_DEFC23_FC94_MASK                     0xFF00
#define GFX_DEFC23_FC94_SHIFT                    8 
#define GFX_DEFC23_FC94_BIT                      0xFF
#define GFX_DEFC23_FC94_BITWIDTH                 8
// FC93 bitfiled (RW) Reset=0
#define GFX_DEFC23_FC93_MASK                     0xFF0000
#define GFX_DEFC23_FC93_SHIFT                    16 
#define GFX_DEFC23_FC93_BIT                      0xFF
#define GFX_DEFC23_FC93_BITWIDTH                 8
// FC92 bitfiled (RW) Reset=0
#define GFX_DEFC23_FC92_MASK                     0xFF000000
#define GFX_DEFC23_FC92_SHIFT                    24 
#define GFX_DEFC23_FC92_BIT                      0xFF
#define GFX_DEFC23_FC92_BITWIDTH                 8
// DEFC24 Register
#define GFX_DEFC24_OFS                           0x00000260
// FC99 bitfiled (RW) Reset=0
#define GFX_DEFC24_FC99_MASK                     0xFF
#define GFX_DEFC24_FC99_SHIFT                    0 
#define GFX_DEFC24_FC99_BIT                      0xFF
#define GFX_DEFC24_FC99_BITWIDTH                 8
// FC98 bitfiled (RW) Reset=0
#define GFX_DEFC24_FC98_MASK                     0xFF00
#define GFX_DEFC24_FC98_SHIFT                    8 
#define GFX_DEFC24_FC98_BIT                      0xFF
#define GFX_DEFC24_FC98_BITWIDTH                 8
// FC97 bitfiled (RW) Reset=0
#define GFX_DEFC24_FC97_MASK                     0xFF0000
#define GFX_DEFC24_FC97_SHIFT                    16 
#define GFX_DEFC24_FC97_BIT                      0xFF
#define GFX_DEFC24_FC97_BITWIDTH                 8
// FC96 bitfiled (RW) Reset=0
#define GFX_DEFC24_FC96_MASK                     0xFF000000
#define GFX_DEFC24_FC96_SHIFT                    24 
#define GFX_DEFC24_FC96_BIT                      0xFF
#define GFX_DEFC24_FC96_BITWIDTH                 8
// DEFC25 Register
#define GFX_DEFC25_OFS                           0x00000264
// FC103 bitfiled (RW) Reset=0
#define GFX_DEFC25_FC103_MASK                    0xFF
#define GFX_DEFC25_FC103_SHIFT                   0 
#define GFX_DEFC25_FC103_BIT                     0xFF
#define GFX_DEFC25_FC103_BITWIDTH                8
// FC102 bitfiled (RW) Reset=0
#define GFX_DEFC25_FC102_MASK                    0xFF00
#define GFX_DEFC25_FC102_SHIFT                   8 
#define GFX_DEFC25_FC102_BIT                     0xFF
#define GFX_DEFC25_FC102_BITWIDTH                8
// FC101 bitfiled (RW) Reset=0
#define GFX_DEFC25_FC101_MASK                    0xFF0000
#define GFX_DEFC25_FC101_SHIFT                   16 
#define GFX_DEFC25_FC101_BIT                     0xFF
#define GFX_DEFC25_FC101_BITWIDTH                8
// FC100 bitfiled (RW) Reset=0
#define GFX_DEFC25_FC100_MASK                    0xFF000000
#define GFX_DEFC25_FC100_SHIFT                   24 
#define GFX_DEFC25_FC100_BIT                     0xFF
#define GFX_DEFC25_FC100_BITWIDTH                8
// DEFC26 Register
#define GFX_DEFC26_OFS                           0x00000268
// FC107 bitfiled (RW) Reset=0
#define GFX_DEFC26_FC107_MASK                    0xFF
#define GFX_DEFC26_FC107_SHIFT                   0 
#define GFX_DEFC26_FC107_BIT                     0xFF
#define GFX_DEFC26_FC107_BITWIDTH                8
// FC106 bitfiled (RW) Reset=0
#define GFX_DEFC26_FC106_MASK                    0xFF00
#define GFX_DEFC26_FC106_SHIFT                   8 
#define GFX_DEFC26_FC106_BIT                     0xFF
#define GFX_DEFC26_FC106_BITWIDTH                8
// FC105 bitfiled (RW) Reset=0
#define GFX_DEFC26_FC105_MASK                    0xFF0000
#define GFX_DEFC26_FC105_SHIFT                   16 
#define GFX_DEFC26_FC105_BIT                     0xFF
#define GFX_DEFC26_FC105_BITWIDTH                8
// FC104 bitfiled (RW) Reset=0
#define GFX_DEFC26_FC104_MASK                    0xFF000000
#define GFX_DEFC26_FC104_SHIFT                   24 
#define GFX_DEFC26_FC104_BIT                     0xFF
#define GFX_DEFC26_FC104_BITWIDTH                8
// DEFC27 Register
#define GFX_DEFC27_OFS                           0x0000026C
// FC111 bitfiled (RW) Reset=0
#define GFX_DEFC27_FC111_MASK                    0xFF
#define GFX_DEFC27_FC111_SHIFT                   0 
#define GFX_DEFC27_FC111_BIT                     0xFF
#define GFX_DEFC27_FC111_BITWIDTH                8
// FC110 bitfiled (RW) Reset=0
#define GFX_DEFC27_FC110_MASK                    0xFF00
#define GFX_DEFC27_FC110_SHIFT                   8 
#define GFX_DEFC27_FC110_BIT                     0xFF
#define GFX_DEFC27_FC110_BITWIDTH                8
// FC109 bitfiled (RW) Reset=0
#define GFX_DEFC27_FC109_MASK                    0xFF0000
#define GFX_DEFC27_FC109_SHIFT                   16 
#define GFX_DEFC27_FC109_BIT                     0xFF
#define GFX_DEFC27_FC109_BITWIDTH                8
// FC108 bitfiled (RW) Reset=0
#define GFX_DEFC27_FC108_MASK                    0xFF000000
#define GFX_DEFC27_FC108_SHIFT                   24 
#define GFX_DEFC27_FC108_BIT                     0xFF
#define GFX_DEFC27_FC108_BITWIDTH                8
// DEFC28 Register
#define GFX_DEFC28_OFS                           0x00000270
// FC115 bitfiled (RW) Reset=0
#define GFX_DEFC28_FC115_MASK                    0xFF
#define GFX_DEFC28_FC115_SHIFT                   0 
#define GFX_DEFC28_FC115_BIT                     0xFF
#define GFX_DEFC28_FC115_BITWIDTH                8
// FC114 bitfiled (RW) Reset=0
#define GFX_DEFC28_FC114_MASK                    0xFF00
#define GFX_DEFC28_FC114_SHIFT                   8 
#define GFX_DEFC28_FC114_BIT                     0xFF
#define GFX_DEFC28_FC114_BITWIDTH                8
// FC113 bitfiled (RW) Reset=0
#define GFX_DEFC28_FC113_MASK                    0xFF0000
#define GFX_DEFC28_FC113_SHIFT                   16 
#define GFX_DEFC28_FC113_BIT                     0xFF
#define GFX_DEFC28_FC113_BITWIDTH                8
// FC112 bitfiled (RW) Reset=0
#define GFX_DEFC28_FC112_MASK                    0xFF000000
#define GFX_DEFC28_FC112_SHIFT                   24 
#define GFX_DEFC28_FC112_BIT                     0xFF
#define GFX_DEFC28_FC112_BITWIDTH                8
// DEFC29 Register
#define GFX_DEFC29_OFS                           0x00000274
// FC119 bitfiled (RW) Reset=0
#define GFX_DEFC29_FC119_MASK                    0xFF
#define GFX_DEFC29_FC119_SHIFT                   0 
#define GFX_DEFC29_FC119_BIT                     0xFF
#define GFX_DEFC29_FC119_BITWIDTH                8
// FC118 bitfiled (RW) Reset=0
#define GFX_DEFC29_FC118_MASK                    0xFF00
#define GFX_DEFC29_FC118_SHIFT                   8 
#define GFX_DEFC29_FC118_BIT                     0xFF
#define GFX_DEFC29_FC118_BITWIDTH                8
// FC117 bitfiled (RW) Reset=0
#define GFX_DEFC29_FC117_MASK                    0xFF0000
#define GFX_DEFC29_FC117_SHIFT                   16 
#define GFX_DEFC29_FC117_BIT                     0xFF
#define GFX_DEFC29_FC117_BITWIDTH                8
// FC116 bitfiled (RW) Reset=0
#define GFX_DEFC29_FC116_MASK                    0xFF000000
#define GFX_DEFC29_FC116_SHIFT                   24 
#define GFX_DEFC29_FC116_BIT                     0xFF
#define GFX_DEFC29_FC116_BITWIDTH                8
// DEFC30 Register
#define GFX_DEFC30_OFS                           0x00000278
// FC123 bitfiled (RW) Reset=0
#define GFX_DEFC30_FC123_MASK                    0xFF
#define GFX_DEFC30_FC123_SHIFT                   0 
#define GFX_DEFC30_FC123_BIT                     0xFF
#define GFX_DEFC30_FC123_BITWIDTH                8
// FC122 bitfiled (RW) Reset=0
#define GFX_DEFC30_FC122_MASK                    0xFF00
#define GFX_DEFC30_FC122_SHIFT                   8 
#define GFX_DEFC30_FC122_BIT                     0xFF
#define GFX_DEFC30_FC122_BITWIDTH                8
// FC121 bitfiled (RW) Reset=0
#define GFX_DEFC30_FC121_MASK                    0xFF0000
#define GFX_DEFC30_FC121_SHIFT                   16 
#define GFX_DEFC30_FC121_BIT                     0xFF
#define GFX_DEFC30_FC121_BITWIDTH                8
// FC120 bitfiled (RW) Reset=0
#define GFX_DEFC30_FC120_MASK                    0xFF000000
#define GFX_DEFC30_FC120_SHIFT                   24 
#define GFX_DEFC30_FC120_BIT                     0xFF
#define GFX_DEFC30_FC120_BITWIDTH                8
// DEFC31 Register
#define GFX_DEFC31_OFS                           0x0000027C
// FC127 bitfiled (RW) Reset=0
#define GFX_DEFC31_FC127_MASK                    0xFF
#define GFX_DEFC31_FC127_SHIFT                   0 
#define GFX_DEFC31_FC127_BIT                     0xFF
#define GFX_DEFC31_FC127_BITWIDTH                8
// FC126 bitfiled (RW) Reset=0
#define GFX_DEFC31_FC126_MASK                    0xFF00
#define GFX_DEFC31_FC126_SHIFT                   8 
#define GFX_DEFC31_FC126_BIT                     0xFF
#define GFX_DEFC31_FC126_BITWIDTH                8
// FC125 bitfiled (RW) Reset=0
#define GFX_DEFC31_FC125_MASK                    0xFF0000
#define GFX_DEFC31_FC125_SHIFT                   16 
#define GFX_DEFC31_FC125_BIT                     0xFF
#define GFX_DEFC31_FC125_BITWIDTH                8
// FC124 bitfiled (RW) Reset=0
#define GFX_DEFC31_FC124_MASK                    0xFF000000
#define GFX_DEFC31_FC124_SHIFT                   24 
#define GFX_DEFC31_FC124_BIT                     0xFF
#define GFX_DEFC31_FC124_BITWIDTH                8
// DEFC32 Register
#define GFX_DEFC32_OFS                           0x00000280
// FC131 bitfiled (RW) Reset=0
#define GFX_DEFC32_FC131_MASK                    0xFF
#define GFX_DEFC32_FC131_SHIFT                   0 
#define GFX_DEFC32_FC131_BIT                     0xFF
#define GFX_DEFC32_FC131_BITWIDTH                8
// FC130 bitfiled (RW) Reset=0
#define GFX_DEFC32_FC130_MASK                    0xFF00
#define GFX_DEFC32_FC130_SHIFT                   8 
#define GFX_DEFC32_FC130_BIT                     0xFF
#define GFX_DEFC32_FC130_BITWIDTH                8
// FC129 bitfiled (RW) Reset=0
#define GFX_DEFC32_FC129_MASK                    0xFF0000
#define GFX_DEFC32_FC129_SHIFT                   16 
#define GFX_DEFC32_FC129_BIT                     0xFF
#define GFX_DEFC32_FC129_BITWIDTH                8
// FC128 bitfiled (RW) Reset=0
#define GFX_DEFC32_FC128_MASK                    0xFF000000
#define GFX_DEFC32_FC128_SHIFT                   24 
#define GFX_DEFC32_FC128_BIT                     0xFF
#define GFX_DEFC32_FC128_BITWIDTH                8
// DEFC33 Register
#define GFX_DEFC33_OFS                           0x00000284
// FC135 bitfiled (RW) Reset=0
#define GFX_DEFC33_FC135_MASK                    0xFF
#define GFX_DEFC33_FC135_SHIFT                   0 
#define GFX_DEFC33_FC135_BIT                     0xFF
#define GFX_DEFC33_FC135_BITWIDTH                8
// FC134 bitfiled (RW) Reset=0
#define GFX_DEFC33_FC134_MASK                    0xFF00
#define GFX_DEFC33_FC134_SHIFT                   8 
#define GFX_DEFC33_FC134_BIT                     0xFF
#define GFX_DEFC33_FC134_BITWIDTH                8
// FC133 bitfiled (RW) Reset=0
#define GFX_DEFC33_FC133_MASK                    0xFF0000
#define GFX_DEFC33_FC133_SHIFT                   16 
#define GFX_DEFC33_FC133_BIT                     0xFF
#define GFX_DEFC33_FC133_BITWIDTH                8
// FC132 bitfiled (RW) Reset=0
#define GFX_DEFC33_FC132_MASK                    0xFF000000
#define GFX_DEFC33_FC132_SHIFT                   24 
#define GFX_DEFC33_FC132_BIT                     0xFF
#define GFX_DEFC33_FC132_BITWIDTH                8
// DEFC34 Register
#define GFX_DEFC34_OFS                           0x00000288
// FC139 bitfiled (RW) Reset=0
#define GFX_DEFC34_FC139_MASK                    0xFF
#define GFX_DEFC34_FC139_SHIFT                   0 
#define GFX_DEFC34_FC139_BIT                     0xFF
#define GFX_DEFC34_FC139_BITWIDTH                8
// FC138 bitfiled (RW) Reset=0
#define GFX_DEFC34_FC138_MASK                    0xFF00
#define GFX_DEFC34_FC138_SHIFT                   8 
#define GFX_DEFC34_FC138_BIT                     0xFF
#define GFX_DEFC34_FC138_BITWIDTH                8
// FC137 bitfiled (RW) Reset=0
#define GFX_DEFC34_FC137_MASK                    0xFF0000
#define GFX_DEFC34_FC137_SHIFT                   16 
#define GFX_DEFC34_FC137_BIT                     0xFF
#define GFX_DEFC34_FC137_BITWIDTH                8
// FC136 bitfiled (RW) Reset=0
#define GFX_DEFC34_FC136_MASK                    0xFF000000
#define GFX_DEFC34_FC136_SHIFT                   24 
#define GFX_DEFC34_FC136_BIT                     0xFF
#define GFX_DEFC34_FC136_BITWIDTH                8
// DEFC35 Register
#define GFX_DEFC35_OFS                           0x0000028C
// FC143 bitfiled (RW) Reset=0
#define GFX_DEFC35_FC143_MASK                    0xFF
#define GFX_DEFC35_FC143_SHIFT                   0 
#define GFX_DEFC35_FC143_BIT                     0xFF
#define GFX_DEFC35_FC143_BITWIDTH                8
// FC142 bitfiled (RW) Reset=0
#define GFX_DEFC35_FC142_MASK                    0xFF00
#define GFX_DEFC35_FC142_SHIFT                   8 
#define GFX_DEFC35_FC142_BIT                     0xFF
#define GFX_DEFC35_FC142_BITWIDTH                8
// FC141 bitfiled (RW) Reset=0
#define GFX_DEFC35_FC141_MASK                    0xFF0000
#define GFX_DEFC35_FC141_SHIFT                   16 
#define GFX_DEFC35_FC141_BIT                     0xFF
#define GFX_DEFC35_FC141_BITWIDTH                8
// FC140 bitfiled (RW) Reset=0
#define GFX_DEFC35_FC140_MASK                    0xFF000000
#define GFX_DEFC35_FC140_SHIFT                   24 
#define GFX_DEFC35_FC140_BIT                     0xFF
#define GFX_DEFC35_FC140_BITWIDTH                8
// DEFC36 Register
#define GFX_DEFC36_OFS                           0x00000290
// FC147 bitfiled (RW) Reset=0
#define GFX_DEFC36_FC147_MASK                    0xFF
#define GFX_DEFC36_FC147_SHIFT                   0 
#define GFX_DEFC36_FC147_BIT                     0xFF
#define GFX_DEFC36_FC147_BITWIDTH                8
// FC146 bitfiled (RW) Reset=0
#define GFX_DEFC36_FC146_MASK                    0xFF00
#define GFX_DEFC36_FC146_SHIFT                   8 
#define GFX_DEFC36_FC146_BIT                     0xFF
#define GFX_DEFC36_FC146_BITWIDTH                8
// FC145 bitfiled (RW) Reset=0
#define GFX_DEFC36_FC145_MASK                    0xFF0000
#define GFX_DEFC36_FC145_SHIFT                   16 
#define GFX_DEFC36_FC145_BIT                     0xFF
#define GFX_DEFC36_FC145_BITWIDTH                8
// FC144 bitfiled (RW) Reset=0
#define GFX_DEFC36_FC144_MASK                    0xFF000000
#define GFX_DEFC36_FC144_SHIFT                   24 
#define GFX_DEFC36_FC144_BIT                     0xFF
#define GFX_DEFC36_FC144_BITWIDTH                8
// DEFC37 Register
#define GFX_DEFC37_OFS                           0x00000294
// FC151 bitfiled (RW) Reset=0
#define GFX_DEFC37_FC151_MASK                    0xFF
#define GFX_DEFC37_FC151_SHIFT                   0 
#define GFX_DEFC37_FC151_BIT                     0xFF
#define GFX_DEFC37_FC151_BITWIDTH                8
// FC150 bitfiled (RW) Reset=0
#define GFX_DEFC37_FC150_MASK                    0xFF00
#define GFX_DEFC37_FC150_SHIFT                   8 
#define GFX_DEFC37_FC150_BIT                     0xFF
#define GFX_DEFC37_FC150_BITWIDTH                8
// FC149 bitfiled (RW) Reset=0
#define GFX_DEFC37_FC149_MASK                    0xFF0000
#define GFX_DEFC37_FC149_SHIFT                   16 
#define GFX_DEFC37_FC149_BIT                     0xFF
#define GFX_DEFC37_FC149_BITWIDTH                8
// FC148 bitfiled (RW) Reset=0
#define GFX_DEFC37_FC148_MASK                    0xFF000000
#define GFX_DEFC37_FC148_SHIFT                   24 
#define GFX_DEFC37_FC148_BIT                     0xFF
#define GFX_DEFC37_FC148_BITWIDTH                8
// DEFC38 Register
#define GFX_DEFC38_OFS                           0x00000298
// FC155 bitfiled (RW) Reset=0
#define GFX_DEFC38_FC155_MASK                    0xFF
#define GFX_DEFC38_FC155_SHIFT                   0 
#define GFX_DEFC38_FC155_BIT                     0xFF
#define GFX_DEFC38_FC155_BITWIDTH                8
// FC154 bitfiled (RW) Reset=0
#define GFX_DEFC38_FC154_MASK                    0xFF00
#define GFX_DEFC38_FC154_SHIFT                   8 
#define GFX_DEFC38_FC154_BIT                     0xFF
#define GFX_DEFC38_FC154_BITWIDTH                8
// FC153 bitfiled (RW) Reset=0
#define GFX_DEFC38_FC153_MASK                    0xFF0000
#define GFX_DEFC38_FC153_SHIFT                   16 
#define GFX_DEFC38_FC153_BIT                     0xFF
#define GFX_DEFC38_FC153_BITWIDTH                8
// FC152 bitfiled (RW) Reset=0
#define GFX_DEFC38_FC152_MASK                    0xFF000000
#define GFX_DEFC38_FC152_SHIFT                   24 
#define GFX_DEFC38_FC152_BIT                     0xFF
#define GFX_DEFC38_FC152_BITWIDTH                8
// DEFC39 Register
#define GFX_DEFC39_OFS                           0x0000029C
// FC159 bitfiled (RW) Reset=0
#define GFX_DEFC39_FC159_MASK                    0xFF
#define GFX_DEFC39_FC159_SHIFT                   0 
#define GFX_DEFC39_FC159_BIT                     0xFF
#define GFX_DEFC39_FC159_BITWIDTH                8
// FC158 bitfiled (RW) Reset=0
#define GFX_DEFC39_FC158_MASK                    0xFF00
#define GFX_DEFC39_FC158_SHIFT                   8 
#define GFX_DEFC39_FC158_BIT                     0xFF
#define GFX_DEFC39_FC158_BITWIDTH                8
// FC157 bitfiled (RW) Reset=0
#define GFX_DEFC39_FC157_MASK                    0xFF0000
#define GFX_DEFC39_FC157_SHIFT                   16 
#define GFX_DEFC39_FC157_BIT                     0xFF
#define GFX_DEFC39_FC157_BITWIDTH                8
// FC156 bitfiled (RW) Reset=0
#define GFX_DEFC39_FC156_MASK                    0xFF000000
#define GFX_DEFC39_FC156_SHIFT                   24 
#define GFX_DEFC39_FC156_BIT                     0xFF
#define GFX_DEFC39_FC156_BITWIDTH                8
// DEFC40 Register
#define GFX_DEFC40_OFS                           0x000002A0
// FC163 bitfiled (RW) Reset=0
#define GFX_DEFC40_FC163_MASK                    0xFF
#define GFX_DEFC40_FC163_SHIFT                   0 
#define GFX_DEFC40_FC163_BIT                     0xFF
#define GFX_DEFC40_FC163_BITWIDTH                8
// FC162 bitfiled (RW) Reset=0
#define GFX_DEFC40_FC162_MASK                    0xFF00
#define GFX_DEFC40_FC162_SHIFT                   8 
#define GFX_DEFC40_FC162_BIT                     0xFF
#define GFX_DEFC40_FC162_BITWIDTH                8
// FC161 bitfiled (RW) Reset=0
#define GFX_DEFC40_FC161_MASK                    0xFF0000
#define GFX_DEFC40_FC161_SHIFT                   16 
#define GFX_DEFC40_FC161_BIT                     0xFF
#define GFX_DEFC40_FC161_BITWIDTH                8
// FC160 bitfiled (RW) Reset=0
#define GFX_DEFC40_FC160_MASK                    0xFF000000
#define GFX_DEFC40_FC160_SHIFT                   24 
#define GFX_DEFC40_FC160_BIT                     0xFF
#define GFX_DEFC40_FC160_BITWIDTH                8
// DEFC41 Register
#define GFX_DEFC41_OFS                           0x000002A4
// FC167 bitfiled (RW) Reset=0
#define GFX_DEFC41_FC167_MASK                    0xFF
#define GFX_DEFC41_FC167_SHIFT                   0 
#define GFX_DEFC41_FC167_BIT                     0xFF
#define GFX_DEFC41_FC167_BITWIDTH                8
// FC166 bitfiled (RW) Reset=0
#define GFX_DEFC41_FC166_MASK                    0xFF00
#define GFX_DEFC41_FC166_SHIFT                   8 
#define GFX_DEFC41_FC166_BIT                     0xFF
#define GFX_DEFC41_FC166_BITWIDTH                8
// FC165 bitfiled (RW) Reset=0
#define GFX_DEFC41_FC165_MASK                    0xFF0000
#define GFX_DEFC41_FC165_SHIFT                   16 
#define GFX_DEFC41_FC165_BIT                     0xFF
#define GFX_DEFC41_FC165_BITWIDTH                8
// FC164 bitfiled (RW) Reset=0
#define GFX_DEFC41_FC164_MASK                    0xFF000000
#define GFX_DEFC41_FC164_SHIFT                   24 
#define GFX_DEFC41_FC164_BIT                     0xFF
#define GFX_DEFC41_FC164_BITWIDTH                8
// DEFC42 Register
#define GFX_DEFC42_OFS                           0x000002A8
// FC171 bitfiled (RW) Reset=0
#define GFX_DEFC42_FC171_MASK                    0xFF
#define GFX_DEFC42_FC171_SHIFT                   0 
#define GFX_DEFC42_FC171_BIT                     0xFF
#define GFX_DEFC42_FC171_BITWIDTH                8
// FC170 bitfiled (RW) Reset=0
#define GFX_DEFC42_FC170_MASK                    0xFF00
#define GFX_DEFC42_FC170_SHIFT                   8 
#define GFX_DEFC42_FC170_BIT                     0xFF
#define GFX_DEFC42_FC170_BITWIDTH                8
// FC169 bitfiled (RW) Reset=0
#define GFX_DEFC42_FC169_MASK                    0xFF0000
#define GFX_DEFC42_FC169_SHIFT                   16 
#define GFX_DEFC42_FC169_BIT                     0xFF
#define GFX_DEFC42_FC169_BITWIDTH                8
// FC168 bitfiled (RW) Reset=0
#define GFX_DEFC42_FC168_MASK                    0xFF000000
#define GFX_DEFC42_FC168_SHIFT                   24 
#define GFX_DEFC42_FC168_BIT                     0xFF
#define GFX_DEFC42_FC168_BITWIDTH                8
// DEFC43 Register
#define GFX_DEFC43_OFS                           0x000002AC
// FC175 bitfiled (RW) Reset=0
#define GFX_DEFC43_FC175_MASK                    0xFF
#define GFX_DEFC43_FC175_SHIFT                   0 
#define GFX_DEFC43_FC175_BIT                     0xFF
#define GFX_DEFC43_FC175_BITWIDTH                8
// FC174 bitfiled (RW) Reset=0
#define GFX_DEFC43_FC174_MASK                    0xFF00
#define GFX_DEFC43_FC174_SHIFT                   8 
#define GFX_DEFC43_FC174_BIT                     0xFF
#define GFX_DEFC43_FC174_BITWIDTH                8
// FC173 bitfiled (RW) Reset=0
#define GFX_DEFC43_FC173_MASK                    0xFF0000
#define GFX_DEFC43_FC173_SHIFT                   16 
#define GFX_DEFC43_FC173_BIT                     0xFF
#define GFX_DEFC43_FC173_BITWIDTH                8
// FC172 bitfiled (RW) Reset=0
#define GFX_DEFC43_FC172_MASK                    0xFF000000
#define GFX_DEFC43_FC172_SHIFT                   24 
#define GFX_DEFC43_FC172_BIT                     0xFF
#define GFX_DEFC43_FC172_BITWIDTH                8
// DEFC44 Register
#define GFX_DEFC44_OFS                           0x000002B0
// FC179 bitfiled (RW) Reset=0
#define GFX_DEFC44_FC179_MASK                    0xFF
#define GFX_DEFC44_FC179_SHIFT                   0 
#define GFX_DEFC44_FC179_BIT                     0xFF
#define GFX_DEFC44_FC179_BITWIDTH                8
// FC178 bitfiled (RW) Reset=0
#define GFX_DEFC44_FC178_MASK                    0xFF00
#define GFX_DEFC44_FC178_SHIFT                   8 
#define GFX_DEFC44_FC178_BIT                     0xFF
#define GFX_DEFC44_FC178_BITWIDTH                8
// FC177 bitfiled (RW) Reset=0
#define GFX_DEFC44_FC177_MASK                    0xFF0000
#define GFX_DEFC44_FC177_SHIFT                   16 
#define GFX_DEFC44_FC177_BIT                     0xFF
#define GFX_DEFC44_FC177_BITWIDTH                8
// FC176 bitfiled (RW) Reset=0
#define GFX_DEFC44_FC176_MASK                    0xFF000000
#define GFX_DEFC44_FC176_SHIFT                   24 
#define GFX_DEFC44_FC176_BIT                     0xFF
#define GFX_DEFC44_FC176_BITWIDTH                8
// DEFC45 Register
#define GFX_DEFC45_OFS                           0x000002B4
// FC183 bitfiled (RW) Reset=0
#define GFX_DEFC45_FC183_MASK                    0xFF
#define GFX_DEFC45_FC183_SHIFT                   0 
#define GFX_DEFC45_FC183_BIT                     0xFF
#define GFX_DEFC45_FC183_BITWIDTH                8
// FC182 bitfiled (RW) Reset=0
#define GFX_DEFC45_FC182_MASK                    0xFF00
#define GFX_DEFC45_FC182_SHIFT                   8 
#define GFX_DEFC45_FC182_BIT                     0xFF
#define GFX_DEFC45_FC182_BITWIDTH                8
// FC181 bitfiled (RW) Reset=0
#define GFX_DEFC45_FC181_MASK                    0xFF0000
#define GFX_DEFC45_FC181_SHIFT                   16 
#define GFX_DEFC45_FC181_BIT                     0xFF
#define GFX_DEFC45_FC181_BITWIDTH                8
// FC180 bitfiled (RW) Reset=0
#define GFX_DEFC45_FC180_MASK                    0xFF000000
#define GFX_DEFC45_FC180_SHIFT                   24 
#define GFX_DEFC45_FC180_BIT                     0xFF
#define GFX_DEFC45_FC180_BITWIDTH                8
// DEFC46 Register
#define GFX_DEFC46_OFS                           0x000002B8
// FC187 bitfiled (RW) Reset=0
#define GFX_DEFC46_FC187_MASK                    0xFF
#define GFX_DEFC46_FC187_SHIFT                   0 
#define GFX_DEFC46_FC187_BIT                     0xFF
#define GFX_DEFC46_FC187_BITWIDTH                8
// FC186 bitfiled (RW) Reset=0
#define GFX_DEFC46_FC186_MASK                    0xFF00
#define GFX_DEFC46_FC186_SHIFT                   8 
#define GFX_DEFC46_FC186_BIT                     0xFF
#define GFX_DEFC46_FC186_BITWIDTH                8
// FC185 bitfiled (RW) Reset=0
#define GFX_DEFC46_FC185_MASK                    0xFF0000
#define GFX_DEFC46_FC185_SHIFT                   16 
#define GFX_DEFC46_FC185_BIT                     0xFF
#define GFX_DEFC46_FC185_BITWIDTH                8
// FC184 bitfiled (RW) Reset=0
#define GFX_DEFC46_FC184_MASK                    0xFF000000
#define GFX_DEFC46_FC184_SHIFT                   24 
#define GFX_DEFC46_FC184_BIT                     0xFF
#define GFX_DEFC46_FC184_BITWIDTH                8
// DEFC47 Register
#define GFX_DEFC47_OFS                           0x000002BC
// FC191 bitfiled (RW) Reset=0
#define GFX_DEFC47_FC191_MASK                    0xFF
#define GFX_DEFC47_FC191_SHIFT                   0 
#define GFX_DEFC47_FC191_BIT                     0xFF
#define GFX_DEFC47_FC191_BITWIDTH                8
// FC190 bitfiled (RW) Reset=0
#define GFX_DEFC47_FC190_MASK                    0xFF00
#define GFX_DEFC47_FC190_SHIFT                   8 
#define GFX_DEFC47_FC190_BIT                     0xFF
#define GFX_DEFC47_FC190_BITWIDTH                8
// FC189 bitfiled (RW) Reset=0
#define GFX_DEFC47_FC189_MASK                    0xFF0000
#define GFX_DEFC47_FC189_SHIFT                   16 
#define GFX_DEFC47_FC189_BIT                     0xFF
#define GFX_DEFC47_FC189_BITWIDTH                8
// FC188 bitfiled (RW) Reset=0
#define GFX_DEFC47_FC188_MASK                    0xFF000000
#define GFX_DEFC47_FC188_SHIFT                   24 
#define GFX_DEFC47_FC188_BIT                     0xFF
#define GFX_DEFC47_FC188_BITWIDTH                8
// DEFC48 Register
#define GFX_DEFC48_OFS                           0x000002C0
// FC195 bitfiled (RW) Reset=0
#define GFX_DEFC48_FC195_MASK                    0xFF
#define GFX_DEFC48_FC195_SHIFT                   0 
#define GFX_DEFC48_FC195_BIT                     0xFF
#define GFX_DEFC48_FC195_BITWIDTH                8
// FC194 bitfiled (RW) Reset=0
#define GFX_DEFC48_FC194_MASK                    0xFF00
#define GFX_DEFC48_FC194_SHIFT                   8 
#define GFX_DEFC48_FC194_BIT                     0xFF
#define GFX_DEFC48_FC194_BITWIDTH                8
// FC193 bitfiled (RW) Reset=0
#define GFX_DEFC48_FC193_MASK                    0xFF0000
#define GFX_DEFC48_FC193_SHIFT                   16 
#define GFX_DEFC48_FC193_BIT                     0xFF
#define GFX_DEFC48_FC193_BITWIDTH                8
// FC192 bitfiled (RW) Reset=0
#define GFX_DEFC48_FC192_MASK                    0xFF000000
#define GFX_DEFC48_FC192_SHIFT                   24 
#define GFX_DEFC48_FC192_BIT                     0xFF
#define GFX_DEFC48_FC192_BITWIDTH                8
// DEFC49 Register
#define GFX_DEFC49_OFS                           0x000002C4
// FC199 bitfiled (RW) Reset=0
#define GFX_DEFC49_FC199_MASK                    0xFF
#define GFX_DEFC49_FC199_SHIFT                   0 
#define GFX_DEFC49_FC199_BIT                     0xFF
#define GFX_DEFC49_FC199_BITWIDTH                8
// FC198 bitfiled (RW) Reset=0
#define GFX_DEFC49_FC198_MASK                    0xFF00
#define GFX_DEFC49_FC198_SHIFT                   8 
#define GFX_DEFC49_FC198_BIT                     0xFF
#define GFX_DEFC49_FC198_BITWIDTH                8
// FC197 bitfiled (RW) Reset=0
#define GFX_DEFC49_FC197_MASK                    0xFF0000
#define GFX_DEFC49_FC197_SHIFT                   16 
#define GFX_DEFC49_FC197_BIT                     0xFF
#define GFX_DEFC49_FC197_BITWIDTH                8
// FC196 bitfiled (RW) Reset=0
#define GFX_DEFC49_FC196_MASK                    0xFF000000
#define GFX_DEFC49_FC196_SHIFT                   24 
#define GFX_DEFC49_FC196_BIT                     0xFF
#define GFX_DEFC49_FC196_BITWIDTH                8
// DEFC50 Register
#define GFX_DEFC50_OFS                           0x000002C8
// FC203 bitfiled (RW) Reset=0
#define GFX_DEFC50_FC203_MASK                    0xFF
#define GFX_DEFC50_FC203_SHIFT                   0 
#define GFX_DEFC50_FC203_BIT                     0xFF
#define GFX_DEFC50_FC203_BITWIDTH                8
// FC202 bitfiled (RW) Reset=0
#define GFX_DEFC50_FC202_MASK                    0xFF00
#define GFX_DEFC50_FC202_SHIFT                   8 
#define GFX_DEFC50_FC202_BIT                     0xFF
#define GFX_DEFC50_FC202_BITWIDTH                8
// FC201 bitfiled (RW) Reset=0
#define GFX_DEFC50_FC201_MASK                    0xFF0000
#define GFX_DEFC50_FC201_SHIFT                   16 
#define GFX_DEFC50_FC201_BIT                     0xFF
#define GFX_DEFC50_FC201_BITWIDTH                8
// FC200 bitfiled (RW) Reset=0
#define GFX_DEFC50_FC200_MASK                    0xFF000000
#define GFX_DEFC50_FC200_SHIFT                   24 
#define GFX_DEFC50_FC200_BIT                     0xFF
#define GFX_DEFC50_FC200_BITWIDTH                8
// DEFC51 Register
#define GFX_DEFC51_OFS                           0x000002CC
// FC207 bitfiled (RW) Reset=0
#define GFX_DEFC51_FC207_MASK                    0xFF
#define GFX_DEFC51_FC207_SHIFT                   0 
#define GFX_DEFC51_FC207_BIT                     0xFF
#define GFX_DEFC51_FC207_BITWIDTH                8
// FC206 bitfiled (RW) Reset=0
#define GFX_DEFC51_FC206_MASK                    0xFF00
#define GFX_DEFC51_FC206_SHIFT                   8 
#define GFX_DEFC51_FC206_BIT                     0xFF
#define GFX_DEFC51_FC206_BITWIDTH                8
// FC205 bitfiled (RW) Reset=0
#define GFX_DEFC51_FC205_MASK                    0xFF0000
#define GFX_DEFC51_FC205_SHIFT                   16 
#define GFX_DEFC51_FC205_BIT                     0xFF
#define GFX_DEFC51_FC205_BITWIDTH                8
// FC204 bitfiled (RW) Reset=0
#define GFX_DEFC51_FC204_MASK                    0xFF000000
#define GFX_DEFC51_FC204_SHIFT                   24 
#define GFX_DEFC51_FC204_BIT                     0xFF
#define GFX_DEFC51_FC204_BITWIDTH                8
// DEFC52 Register
#define GFX_DEFC52_OFS                           0x000002D0
// FC211 bitfiled (RW) Reset=0
#define GFX_DEFC52_FC211_MASK                    0xFF
#define GFX_DEFC52_FC211_SHIFT                   0 
#define GFX_DEFC52_FC211_BIT                     0xFF
#define GFX_DEFC52_FC211_BITWIDTH                8
// FC210 bitfiled (RW) Reset=0
#define GFX_DEFC52_FC210_MASK                    0xFF00
#define GFX_DEFC52_FC210_SHIFT                   8 
#define GFX_DEFC52_FC210_BIT                     0xFF
#define GFX_DEFC52_FC210_BITWIDTH                8
// FC209 bitfiled (RW) Reset=0
#define GFX_DEFC52_FC209_MASK                    0xFF0000
#define GFX_DEFC52_FC209_SHIFT                   16 
#define GFX_DEFC52_FC209_BIT                     0xFF
#define GFX_DEFC52_FC209_BITWIDTH                8
// FC208 bitfiled (RW) Reset=0
#define GFX_DEFC52_FC208_MASK                    0xFF000000
#define GFX_DEFC52_FC208_SHIFT                   24 
#define GFX_DEFC52_FC208_BIT                     0xFF
#define GFX_DEFC52_FC208_BITWIDTH                8
// DEFC53 Register
#define GFX_DEFC53_OFS                           0x000002D4
// FC215 bitfiled (RW) Reset=0
#define GFX_DEFC53_FC215_MASK                    0xFF
#define GFX_DEFC53_FC215_SHIFT                   0 
#define GFX_DEFC53_FC215_BIT                     0xFF
#define GFX_DEFC53_FC215_BITWIDTH                8
// FC214 bitfiled (RW) Reset=0
#define GFX_DEFC53_FC214_MASK                    0xFF00
#define GFX_DEFC53_FC214_SHIFT                   8 
#define GFX_DEFC53_FC214_BIT                     0xFF
#define GFX_DEFC53_FC214_BITWIDTH                8
// FC213 bitfiled (RW) Reset=0
#define GFX_DEFC53_FC213_MASK                    0xFF0000
#define GFX_DEFC53_FC213_SHIFT                   16 
#define GFX_DEFC53_FC213_BIT                     0xFF
#define GFX_DEFC53_FC213_BITWIDTH                8
// FC212 bitfiled (RW) Reset=0
#define GFX_DEFC53_FC212_MASK                    0xFF000000
#define GFX_DEFC53_FC212_SHIFT                   24 
#define GFX_DEFC53_FC212_BIT                     0xFF
#define GFX_DEFC53_FC212_BITWIDTH                8
// DEFC54 Register
#define GFX_DEFC54_OFS                           0x000002D8
// FC219 bitfiled (RW) Reset=0
#define GFX_DEFC54_FC219_MASK                    0xFF
#define GFX_DEFC54_FC219_SHIFT                   0 
#define GFX_DEFC54_FC219_BIT                     0xFF
#define GFX_DEFC54_FC219_BITWIDTH                8
// FC218 bitfiled (RW) Reset=0
#define GFX_DEFC54_FC218_MASK                    0xFF00
#define GFX_DEFC54_FC218_SHIFT                   8 
#define GFX_DEFC54_FC218_BIT                     0xFF
#define GFX_DEFC54_FC218_BITWIDTH                8
// FC217 bitfiled (RW) Reset=0
#define GFX_DEFC54_FC217_MASK                    0xFF0000
#define GFX_DEFC54_FC217_SHIFT                   16 
#define GFX_DEFC54_FC217_BIT                     0xFF
#define GFX_DEFC54_FC217_BITWIDTH                8
// FC216 bitfiled (RW) Reset=0
#define GFX_DEFC54_FC216_MASK                    0xFF000000
#define GFX_DEFC54_FC216_SHIFT                   24 
#define GFX_DEFC54_FC216_BIT                     0xFF
#define GFX_DEFC54_FC216_BITWIDTH                8
// DEFC55 Register
#define GFX_DEFC55_OFS                           0x000002DC
// FC223 bitfiled (RW) Reset=0
#define GFX_DEFC55_FC223_MASK                    0xFF
#define GFX_DEFC55_FC223_SHIFT                   0 
#define GFX_DEFC55_FC223_BIT                     0xFF
#define GFX_DEFC55_FC223_BITWIDTH                8
// FC222 bitfiled (RW) Reset=0
#define GFX_DEFC55_FC222_MASK                    0xFF00
#define GFX_DEFC55_FC222_SHIFT                   8 
#define GFX_DEFC55_FC222_BIT                     0xFF
#define GFX_DEFC55_FC222_BITWIDTH                8
// FC221 bitfiled (RW) Reset=0
#define GFX_DEFC55_FC221_MASK                    0xFF0000
#define GFX_DEFC55_FC221_SHIFT                   16 
#define GFX_DEFC55_FC221_BIT                     0xFF
#define GFX_DEFC55_FC221_BITWIDTH                8
// FC220 bitfiled (RW) Reset=0
#define GFX_DEFC55_FC220_MASK                    0xFF000000
#define GFX_DEFC55_FC220_SHIFT                   24 
#define GFX_DEFC55_FC220_BIT                     0xFF
#define GFX_DEFC55_FC220_BITWIDTH                8
// DEFC56 Register
#define GFX_DEFC56_OFS                           0x000002E0
// FC227 bitfiled (RW) Reset=0
#define GFX_DEFC56_FC227_MASK                    0xFF
#define GFX_DEFC56_FC227_SHIFT                   0 
#define GFX_DEFC56_FC227_BIT                     0xFF
#define GFX_DEFC56_FC227_BITWIDTH                8
// FC226 bitfiled (RW) Reset=0
#define GFX_DEFC56_FC226_MASK                    0xFF00
#define GFX_DEFC56_FC226_SHIFT                   8 
#define GFX_DEFC56_FC226_BIT                     0xFF
#define GFX_DEFC56_FC226_BITWIDTH                8
// FC225 bitfiled (RW) Reset=0
#define GFX_DEFC56_FC225_MASK                    0xFF0000
#define GFX_DEFC56_FC225_SHIFT                   16 
#define GFX_DEFC56_FC225_BIT                     0xFF
#define GFX_DEFC56_FC225_BITWIDTH                8
// FC224 bitfiled (RW) Reset=0
#define GFX_DEFC56_FC224_MASK                    0xFF000000
#define GFX_DEFC56_FC224_SHIFT                   24 
#define GFX_DEFC56_FC224_BIT                     0xFF
#define GFX_DEFC56_FC224_BITWIDTH                8
// DEFC57 Register
#define GFX_DEFC57_OFS                           0x000002E4
// FC231 bitfiled (RW) Reset=0
#define GFX_DEFC57_FC231_MASK                    0xFF
#define GFX_DEFC57_FC231_SHIFT                   0 
#define GFX_DEFC57_FC231_BIT                     0xFF
#define GFX_DEFC57_FC231_BITWIDTH                8
// FC230 bitfiled (RW) Reset=0
#define GFX_DEFC57_FC230_MASK                    0xFF00
#define GFX_DEFC57_FC230_SHIFT                   8 
#define GFX_DEFC57_FC230_BIT                     0xFF
#define GFX_DEFC57_FC230_BITWIDTH                8
// FC229 bitfiled (RW) Reset=0
#define GFX_DEFC57_FC229_MASK                    0xFF0000
#define GFX_DEFC57_FC229_SHIFT                   16 
#define GFX_DEFC57_FC229_BIT                     0xFF
#define GFX_DEFC57_FC229_BITWIDTH                8
// FC228 bitfiled (RW) Reset=0
#define GFX_DEFC57_FC228_MASK                    0xFF000000
#define GFX_DEFC57_FC228_SHIFT                   24 
#define GFX_DEFC57_FC228_BIT                     0xFF
#define GFX_DEFC57_FC228_BITWIDTH                8
// DEFC58 Register
#define GFX_DEFC58_OFS                           0x000002E8
// FC235 bitfiled (RW) Reset=0
#define GFX_DEFC58_FC235_MASK                    0xFF
#define GFX_DEFC58_FC235_SHIFT                   0 
#define GFX_DEFC58_FC235_BIT                     0xFF
#define GFX_DEFC58_FC235_BITWIDTH                8
// FC234 bitfiled (RW) Reset=0
#define GFX_DEFC58_FC234_MASK                    0xFF00
#define GFX_DEFC58_FC234_SHIFT                   8 
#define GFX_DEFC58_FC234_BIT                     0xFF
#define GFX_DEFC58_FC234_BITWIDTH                8
// FC233 bitfiled (RW) Reset=0
#define GFX_DEFC58_FC233_MASK                    0xFF0000
#define GFX_DEFC58_FC233_SHIFT                   16 
#define GFX_DEFC58_FC233_BIT                     0xFF
#define GFX_DEFC58_FC233_BITWIDTH                8
// FC232 bitfiled (RW) Reset=0
#define GFX_DEFC58_FC232_MASK                    0xFF000000
#define GFX_DEFC58_FC232_SHIFT                   24 
#define GFX_DEFC58_FC232_BIT                     0xFF
#define GFX_DEFC58_FC232_BITWIDTH                8
// DEFC59 Register
#define GFX_DEFC59_OFS                           0x000002EC
// FC239 bitfiled (RW) Reset=0
#define GFX_DEFC59_FC239_MASK                    0xFF
#define GFX_DEFC59_FC239_SHIFT                   0 
#define GFX_DEFC59_FC239_BIT                     0xFF
#define GFX_DEFC59_FC239_BITWIDTH                8
// FC238 bitfiled (RW) Reset=0
#define GFX_DEFC59_FC238_MASK                    0xFF00
#define GFX_DEFC59_FC238_SHIFT                   8 
#define GFX_DEFC59_FC238_BIT                     0xFF
#define GFX_DEFC59_FC238_BITWIDTH                8
// FC237 bitfiled (RW) Reset=0
#define GFX_DEFC59_FC237_MASK                    0xFF0000
#define GFX_DEFC59_FC237_SHIFT                   16 
#define GFX_DEFC59_FC237_BIT                     0xFF
#define GFX_DEFC59_FC237_BITWIDTH                8
// FC236 bitfiled (RW) Reset=0
#define GFX_DEFC59_FC236_MASK                    0xFF000000
#define GFX_DEFC59_FC236_SHIFT                   24 
#define GFX_DEFC59_FC236_BIT                     0xFF
#define GFX_DEFC59_FC236_BITWIDTH                8
// DEFC60 Register
#define GFX_DEFC60_OFS                           0x000002F0
// FC243 bitfiled (RW) Reset=0
#define GFX_DEFC60_FC243_MASK                    0xFF
#define GFX_DEFC60_FC243_SHIFT                   0 
#define GFX_DEFC60_FC243_BIT                     0xFF
#define GFX_DEFC60_FC243_BITWIDTH                8
// FC242 bitfiled (RW) Reset=0
#define GFX_DEFC60_FC242_MASK                    0xFF00
#define GFX_DEFC60_FC242_SHIFT                   8 
#define GFX_DEFC60_FC242_BIT                     0xFF
#define GFX_DEFC60_FC242_BITWIDTH                8
// FC241 bitfiled (RW) Reset=0
#define GFX_DEFC60_FC241_MASK                    0xFF0000
#define GFX_DEFC60_FC241_SHIFT                   16 
#define GFX_DEFC60_FC241_BIT                     0xFF
#define GFX_DEFC60_FC241_BITWIDTH                8
// FC240 bitfiled (RW) Reset=0
#define GFX_DEFC60_FC240_MASK                    0xFF000000
#define GFX_DEFC60_FC240_SHIFT                   24 
#define GFX_DEFC60_FC240_BIT                     0xFF
#define GFX_DEFC60_FC240_BITWIDTH                8
// DEFC61 Register
#define GFX_DEFC61_OFS                           0x000002F4
// FC247 bitfiled (RW) Reset=0
#define GFX_DEFC61_FC247_MASK                    0xFF
#define GFX_DEFC61_FC247_SHIFT                   0 
#define GFX_DEFC61_FC247_BIT                     0xFF
#define GFX_DEFC61_FC247_BITWIDTH                8
// FC246 bitfiled (RW) Reset=0
#define GFX_DEFC61_FC246_MASK                    0xFF00
#define GFX_DEFC61_FC246_SHIFT                   8 
#define GFX_DEFC61_FC246_BIT                     0xFF
#define GFX_DEFC61_FC246_BITWIDTH                8
// FC245 bitfiled (RW) Reset=0
#define GFX_DEFC61_FC245_MASK                    0xFF0000
#define GFX_DEFC61_FC245_SHIFT                   16 
#define GFX_DEFC61_FC245_BIT                     0xFF
#define GFX_DEFC61_FC245_BITWIDTH                8
// FC244 bitfiled (RW) Reset=0
#define GFX_DEFC61_FC244_MASK                    0xFF000000
#define GFX_DEFC61_FC244_SHIFT                   24 
#define GFX_DEFC61_FC244_BIT                     0xFF
#define GFX_DEFC61_FC244_BITWIDTH                8
// DEFC62 Register
#define GFX_DEFC62_OFS                           0x000002F8
// FC251 bitfiled (RW) Reset=0
#define GFX_DEFC62_FC251_MASK                    0xFF
#define GFX_DEFC62_FC251_SHIFT                   0 
#define GFX_DEFC62_FC251_BIT                     0xFF
#define GFX_DEFC62_FC251_BITWIDTH                8
// FC250 bitfiled (RW) Reset=0
#define GFX_DEFC62_FC250_MASK                    0xFF00
#define GFX_DEFC62_FC250_SHIFT                   8 
#define GFX_DEFC62_FC250_BIT                     0xFF
#define GFX_DEFC62_FC250_BITWIDTH                8
// FC249 bitfiled (RW) Reset=0
#define GFX_DEFC62_FC249_MASK                    0xFF0000
#define GFX_DEFC62_FC249_SHIFT                   16 
#define GFX_DEFC62_FC249_BIT                     0xFF
#define GFX_DEFC62_FC249_BITWIDTH                8
// FC248 bitfiled (RW) Reset=0
#define GFX_DEFC62_FC248_MASK                    0xFF000000
#define GFX_DEFC62_FC248_SHIFT                   24 
#define GFX_DEFC62_FC248_BIT                     0xFF
#define GFX_DEFC62_FC248_BITWIDTH                8
// DEFC63 Register
#define GFX_DEFC63_OFS                           0x000002FC
// FC255 bitfiled (RW) Reset=0
#define GFX_DEFC63_FC255_MASK                    0xFF
#define GFX_DEFC63_FC255_SHIFT                   0 
#define GFX_DEFC63_FC255_BIT                     0xFF
#define GFX_DEFC63_FC255_BITWIDTH                8
// FC254 bitfiled (RW) Reset=0
#define GFX_DEFC63_FC254_MASK                    0xFF00
#define GFX_DEFC63_FC254_SHIFT                   8 
#define GFX_DEFC63_FC254_BIT                     0xFF
#define GFX_DEFC63_FC254_BITWIDTH                8
// FC253 bitfiled (RW) Reset=0
#define GFX_DEFC63_FC253_MASK                    0xFF0000
#define GFX_DEFC63_FC253_SHIFT                   16 
#define GFX_DEFC63_FC253_BIT                     0xFF
#define GFX_DEFC63_FC253_BITWIDTH                8
// FC252 bitfiled (RW) Reset=0
#define GFX_DEFC63_FC252_MASK                    0xFF000000
#define GFX_DEFC63_FC252_SHIFT                   24 
#define GFX_DEFC63_FC252_BIT                     0xFF
#define GFX_DEFC63_FC252_BITWIDTH                8

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _GFX_REG_DEF_H */
