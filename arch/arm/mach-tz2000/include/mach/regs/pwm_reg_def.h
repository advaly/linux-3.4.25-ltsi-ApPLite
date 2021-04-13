/*
 * arch/arm/mach-tz2000/include/mach/regs/pwm_reg_def.h
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

#ifndef _PWM_REG_DEF_H
#define _PWM_REG_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

// PWM0_CR Register
#define PWM_PWM0_CR_OFS                          0x00000000
// ENB bitfiled (RW) Reset=0
#define PWM_PWM0_CR_ENB_MASK                     0x1
#define PWM_PWM0_CR_ENB_SHIFT                    0 
#define PWM_PWM0_CR_ENB_BIT                      0x1
#define PWM_PWM0_CR_ENB_BITWIDTH                 1
// UPD bitfiled (RW) Reset=0
#define PWM_PWM0_CR_UPD_MASK                     0x2
#define PWM_PWM0_CR_UPD_SHIFT                    1 
#define PWM_PWM0_CR_UPD_BIT                      0x1
#define PWM_PWM0_CR_UPD_BITWIDTH                 1
// reserved1 bitfiled (RO) Reset=0
#define PWM_PWM0_CR_RESERVED1_MASK               0xFC
#define PWM_PWM0_CR_RESERVED1_SHIFT              2 
#define PWM_PWM0_CR_RESERVED1_BIT                0x3F
#define PWM_PWM0_CR_RESERVED1_BITWIDTH           6
// POL bitfiled (RW) Reset=0
#define PWM_PWM0_CR_POL_MASK                     0x100
#define PWM_PWM0_CR_POL_SHIFT                    8 
#define PWM_PWM0_CR_POL_BIT                      0x1
#define PWM_PWM0_CR_POL_BITWIDTH                 1
// LVS bitfiled (RW) Reset=0
#define PWM_PWM0_CR_LVS_MASK                     0x200
#define PWM_PWM0_CR_LVS_SHIFT                    9 
#define PWM_PWM0_CR_LVS_BIT                      0x1
#define PWM_PWM0_CR_LVS_BITWIDTH                 1
// reserved2 bitfiled (RO) Reset=0
#define PWM_PWM0_CR_RESERVED2_MASK               0xFC00
#define PWM_PWM0_CR_RESERVED2_SHIFT              10 
#define PWM_PWM0_CR_RESERVED2_BIT                0x3F
#define PWM_PWM0_CR_RESERVED2_BITWIDTH           6
// DIV bitfiled (RW) Reset=0
#define PWM_PWM0_CR_DIV_MASK                     0xF0000
#define PWM_PWM0_CR_DIV_SHIFT                    16 
#define PWM_PWM0_CR_DIV_BIT                      0xF
#define PWM_PWM0_CR_DIV_BITWIDTH                 4
// reserved3 bitfiled (RO) Reset=0
#define PWM_PWM0_CR_RESERVED3_MASK               0xF00000
#define PWM_PWM0_CR_RESERVED3_SHIFT              20 
#define PWM_PWM0_CR_RESERVED3_BIT                0xF
#define PWM_PWM0_CR_RESERVED3_BITWIDTH           4
// fixed bitfiled (RW) Reset=0
#define PWM_PWM0_CR_FIXED_MASK                   0x3000000
#define PWM_PWM0_CR_FIXED_SHIFT                  24 
#define PWM_PWM0_CR_FIXED_BIT                    0x3
#define PWM_PWM0_CR_FIXED_BITWIDTH               2
// reserved4 bitfiled (RO) Reset=0
#define PWM_PWM0_CR_RESERVED4_MASK               0xC000000
#define PWM_PWM0_CR_RESERVED4_SHIFT              26 
#define PWM_PWM0_CR_RESERVED4_BIT                0x3
#define PWM_PWM0_CR_RESERVED4_BITWIDTH           2
// ENBSEL bitfiled (RW) Reset=0
#define PWM_PWM0_CR_ENBSEL_MASK                  0x30000000
#define PWM_PWM0_CR_ENBSEL_SHIFT                 28 
#define PWM_PWM0_CR_ENBSEL_BIT                   0x3
#define PWM_PWM0_CR_ENBSEL_BITWIDTH              2
// reserved5 bitfiled (RO) Reset=0
#define PWM_PWM0_CR_RESERVED5_MASK               0xC0000000
#define PWM_PWM0_CR_RESERVED5_SHIFT              30 
#define PWM_PWM0_CR_RESERVED5_BIT                0x3
#define PWM_PWM0_CR_RESERVED5_BITWIDTH           2
// PWM0_FREQ Register
#define PWM_PWM0_FREQ_OFS                        0x00000004
// FREQ bitfiled (RW) Reset=0
#define PWM_PWM0_FREQ_FREQ_MASK                  0xFFFFFFFF
#define PWM_PWM0_FREQ_FREQ_SHIFT                 0 
#define PWM_PWM0_FREQ_FREQ_BIT                   0xFFFFFFFF
#define PWM_PWM0_FREQ_FREQ_BITWIDTH              32
// PWM0_DUTY Register
#define PWM_PWM0_DUTY_OFS                        0x00000008
// DUTY bitfiled (RW) Reset=0
#define PWM_PWM0_DUTY_DUTY_MASK                  0xFFFFFFFF
#define PWM_PWM0_DUTY_DUTY_SHIFT                 0 
#define PWM_PWM0_DUTY_DUTY_BIT                   0xFFFFFFFF
#define PWM_PWM0_DUTY_DUTY_BITWIDTH              32
// PWM0_ITERATION Register
#define PWM_PWM0_ITERATION_OFS                   0x0000000C
// ITERATION bitfiled (RW) Reset=0
#define PWM_PWM0_ITERATION_ITERATION_MASK        0xFFFF
#define PWM_PWM0_ITERATION_ITERATION_SHIFT       0 
#define PWM_PWM0_ITERATION_ITERATION_BIT         0xFFFF
#define PWM_PWM0_ITERATION_ITERATION_BITWIDTH    16
// reserved bitfiled (RO) Reset=0
#define PWM_PWM0_ITERATION_RESERVED_MASK         0xFFFF0000
#define PWM_PWM0_ITERATION_RESERVED_SHIFT        16 
#define PWM_PWM0_ITERATION_RESERVED_BIT          0xFFFF
#define PWM_PWM0_ITERATION_RESERVED_BITWIDTH     16
// PWM0_CURFREQ Register
#define PWM_PWM0_CURFREQ_OFS                     0x00000010
// CURFREQ bitfiled (RO) Reset=0
#define PWM_PWM0_CURFREQ_CURFREQ_MASK            0xFFFFFFFF
#define PWM_PWM0_CURFREQ_CURFREQ_SHIFT           0 
#define PWM_PWM0_CURFREQ_CURFREQ_BIT             0xFFFFFFFF
#define PWM_PWM0_CURFREQ_CURFREQ_BITWIDTH        32
// PWM0_CURDUTY Register
#define PWM_PWM0_CURDUTY_OFS                     0x00000014
// INTC0 bitfiled (RO) Reset=0
#define PWM_PWM0_CURDUTY_INTC0_MASK              0xFFFFFFFF
#define PWM_PWM0_CURDUTY_INTC0_SHIFT             0 
#define PWM_PWM0_CURDUTY_INTC0_BIT               0xFFFFFFFF
#define PWM_PWM0_CURDUTY_INTC0_BITWIDTH          32
// PWM0_CURITER Register
#define PWM_PWM0_CURITER_OFS                     0x00000018
// CURITER bitfiled (RO) Reset=0
#define PWM_PWM0_CURITER_CURITER_MASK            0xFFFF
#define PWM_PWM0_CURITER_CURITER_SHIFT           0 
#define PWM_PWM0_CURITER_CURITER_BIT             0xFFFF
#define PWM_PWM0_CURITER_CURITER_BITWIDTH        16
// CURCYCLE bitfiled (RO) Reset=0
#define PWM_PWM0_CURITER_CURCYCLE_MASK           0xFFFF0000
#define PWM_PWM0_CURITER_CURCYCLE_SHIFT          16 
#define PWM_PWM0_CURITER_CURCYCLE_BIT            0xFFFF
#define PWM_PWM0_CURITER_CURCYCLE_BITWIDTH       16
// PWM0_COUNT Register
#define PWM_PWM0_COUNT_OFS                       0x0000001C
// COUNT bitfiled (RO) Reset=0
#define PWM_PWM0_COUNT_COUNT_MASK                0xFFFFFFFF
#define PWM_PWM0_COUNT_COUNT_SHIFT               0 
#define PWM_PWM0_COUNT_COUNT_BIT                 0xFFFFFFFF
#define PWM_PWM0_COUNT_COUNT_BITWIDTH            32
// PWM1_CR Register
#define PWM_PWM1_CR_OFS                          0x00000020
// ENB bitfiled (RW) Reset=0
#define PWM_PWM1_CR_ENB_MASK                     0x1
#define PWM_PWM1_CR_ENB_SHIFT                    0 
#define PWM_PWM1_CR_ENB_BIT                      0x1
#define PWM_PWM1_CR_ENB_BITWIDTH                 1
// UPD bitfiled (RW) Reset=0
#define PWM_PWM1_CR_UPD_MASK                     0x2
#define PWM_PWM1_CR_UPD_SHIFT                    1 
#define PWM_PWM1_CR_UPD_BIT                      0x1
#define PWM_PWM1_CR_UPD_BITWIDTH                 1
// reserved1 bitfiled (RO) Reset=0
#define PWM_PWM1_CR_RESERVED1_MASK               0xFC
#define PWM_PWM1_CR_RESERVED1_SHIFT              2 
#define PWM_PWM1_CR_RESERVED1_BIT                0x3F
#define PWM_PWM1_CR_RESERVED1_BITWIDTH           6
// POL bitfiled (RW) Reset=0
#define PWM_PWM1_CR_POL_MASK                     0x100
#define PWM_PWM1_CR_POL_SHIFT                    8 
#define PWM_PWM1_CR_POL_BIT                      0x1
#define PWM_PWM1_CR_POL_BITWIDTH                 1
// LVS bitfiled (RW) Reset=0
#define PWM_PWM1_CR_LVS_MASK                     0x200
#define PWM_PWM1_CR_LVS_SHIFT                    9 
#define PWM_PWM1_CR_LVS_BIT                      0x1
#define PWM_PWM1_CR_LVS_BITWIDTH                 1
// reserved2 bitfiled (RO) Reset=0
#define PWM_PWM1_CR_RESERVED2_MASK               0xFC00
#define PWM_PWM1_CR_RESERVED2_SHIFT              10 
#define PWM_PWM1_CR_RESERVED2_BIT                0x3F
#define PWM_PWM1_CR_RESERVED2_BITWIDTH           6
// DIV bitfiled (RW) Reset=0
#define PWM_PWM1_CR_DIV_MASK                     0xF0000
#define PWM_PWM1_CR_DIV_SHIFT                    16 
#define PWM_PWM1_CR_DIV_BIT                      0xF
#define PWM_PWM1_CR_DIV_BITWIDTH                 4
// reserved3 bitfiled (RO) Reset=0
#define PWM_PWM1_CR_RESERVED3_MASK               0xF00000
#define PWM_PWM1_CR_RESERVED3_SHIFT              20 
#define PWM_PWM1_CR_RESERVED3_BIT                0xF
#define PWM_PWM1_CR_RESERVED3_BITWIDTH           4
// fixed bitfiled (RW) Reset=0
#define PWM_PWM1_CR_FIXED_MASK                   0x3000000
#define PWM_PWM1_CR_FIXED_SHIFT                  24 
#define PWM_PWM1_CR_FIXED_BIT                    0x3
#define PWM_PWM1_CR_FIXED_BITWIDTH               2
// reserved4 bitfiled (RO) Reset=0
#define PWM_PWM1_CR_RESERVED4_MASK               0xC000000
#define PWM_PWM1_CR_RESERVED4_SHIFT              26 
#define PWM_PWM1_CR_RESERVED4_BIT                0x3
#define PWM_PWM1_CR_RESERVED4_BITWIDTH           2
// ENBSEL bitfiled (RW) Reset=0
#define PWM_PWM1_CR_ENBSEL_MASK                  0x30000000
#define PWM_PWM1_CR_ENBSEL_SHIFT                 28 
#define PWM_PWM1_CR_ENBSEL_BIT                   0x3
#define PWM_PWM1_CR_ENBSEL_BITWIDTH              2
// reserved5 bitfiled (RO) Reset=0
#define PWM_PWM1_CR_RESERVED5_MASK               0xC0000000
#define PWM_PWM1_CR_RESERVED5_SHIFT              30 
#define PWM_PWM1_CR_RESERVED5_BIT                0x3
#define PWM_PWM1_CR_RESERVED5_BITWIDTH           2
// PWM1_FREQ Register
#define PWM_PWM1_FREQ_OFS                        0x00000024
// FREQ bitfiled (RW) Reset=0
#define PWM_PWM1_FREQ_FREQ_MASK                  0xFFFFFFFF
#define PWM_PWM1_FREQ_FREQ_SHIFT                 0 
#define PWM_PWM1_FREQ_FREQ_BIT                   0xFFFFFFFF
#define PWM_PWM1_FREQ_FREQ_BITWIDTH              32
// PWM1_DUTY Register
#define PWM_PWM1_DUTY_OFS                        0x00000028
// DUTY bitfiled (RW) Reset=0
#define PWM_PWM1_DUTY_DUTY_MASK                  0xFFFFFFFF
#define PWM_PWM1_DUTY_DUTY_SHIFT                 0 
#define PWM_PWM1_DUTY_DUTY_BIT                   0xFFFFFFFF
#define PWM_PWM1_DUTY_DUTY_BITWIDTH              32
// PWM1_ITERATION Register
#define PWM_PWM1_ITERATION_OFS                   0x0000002C
// ITERATION bitfiled (RW) Reset=0
#define PWM_PWM1_ITERATION_ITERATION_MASK        0xFFFF
#define PWM_PWM1_ITERATION_ITERATION_SHIFT       0 
#define PWM_PWM1_ITERATION_ITERATION_BIT         0xFFFF
#define PWM_PWM1_ITERATION_ITERATION_BITWIDTH    16
// reserved bitfiled (RO) Reset=0
#define PWM_PWM1_ITERATION_RESERVED_MASK         0xFFFF0000
#define PWM_PWM1_ITERATION_RESERVED_SHIFT        16 
#define PWM_PWM1_ITERATION_RESERVED_BIT          0xFFFF
#define PWM_PWM1_ITERATION_RESERVED_BITWIDTH     16
// PWM1_CURFREQ Register
#define PWM_PWM1_CURFREQ_OFS                     0x00000030
// CURFREQ bitfiled (RO) Reset=0
#define PWM_PWM1_CURFREQ_CURFREQ_MASK            0xFFFFFFFF
#define PWM_PWM1_CURFREQ_CURFREQ_SHIFT           0 
#define PWM_PWM1_CURFREQ_CURFREQ_BIT             0xFFFFFFFF
#define PWM_PWM1_CURFREQ_CURFREQ_BITWIDTH        32
// PWM1_CURDUTY Register
#define PWM_PWM1_CURDUTY_OFS                     0x00000034
// INTC0 bitfiled (RO) Reset=0
#define PWM_PWM1_CURDUTY_INTC0_MASK              0xFFFFFFFF
#define PWM_PWM1_CURDUTY_INTC0_SHIFT             0 
#define PWM_PWM1_CURDUTY_INTC0_BIT               0xFFFFFFFF
#define PWM_PWM1_CURDUTY_INTC0_BITWIDTH          32
// PWM1_CURITER Register
#define PWM_PWM1_CURITER_OFS                     0x00000038
// CURITER bitfiled (RO) Reset=0
#define PWM_PWM1_CURITER_CURITER_MASK            0xFFFF
#define PWM_PWM1_CURITER_CURITER_SHIFT           0 
#define PWM_PWM1_CURITER_CURITER_BIT             0xFFFF
#define PWM_PWM1_CURITER_CURITER_BITWIDTH        16
// CURCYCLE bitfiled (RO) Reset=0
#define PWM_PWM1_CURITER_CURCYCLE_MASK           0xFFFF0000
#define PWM_PWM1_CURITER_CURCYCLE_SHIFT          16 
#define PWM_PWM1_CURITER_CURCYCLE_BIT            0xFFFF
#define PWM_PWM1_CURITER_CURCYCLE_BITWIDTH       16
// PWM1_COUNT Register
#define PWM_PWM1_COUNT_OFS                       0x0000003C
// COUNT bitfiled (RO) Reset=0
#define PWM_PWM1_COUNT_COUNT_MASK                0xFFFFFFFF
#define PWM_PWM1_COUNT_COUNT_SHIFT               0 
#define PWM_PWM1_COUNT_COUNT_BIT                 0xFFFFFFFF
#define PWM_PWM1_COUNT_COUNT_BITWIDTH            32
// PWM2_CR Register
#define PWM_PWM2_CR_OFS                          0x00000040
// ENB bitfiled (RW) Reset=0
#define PWM_PWM2_CR_ENB_MASK                     0x1
#define PWM_PWM2_CR_ENB_SHIFT                    0 
#define PWM_PWM2_CR_ENB_BIT                      0x1
#define PWM_PWM2_CR_ENB_BITWIDTH                 1
// UPD bitfiled (RW) Reset=0
#define PWM_PWM2_CR_UPD_MASK                     0x2
#define PWM_PWM2_CR_UPD_SHIFT                    1 
#define PWM_PWM2_CR_UPD_BIT                      0x1
#define PWM_PWM2_CR_UPD_BITWIDTH                 1
// reserved1 bitfiled (RO) Reset=0
#define PWM_PWM2_CR_RESERVED1_MASK               0xFC
#define PWM_PWM2_CR_RESERVED1_SHIFT              2 
#define PWM_PWM2_CR_RESERVED1_BIT                0x3F
#define PWM_PWM2_CR_RESERVED1_BITWIDTH           6
// POL bitfiled (RW) Reset=0
#define PWM_PWM2_CR_POL_MASK                     0x100
#define PWM_PWM2_CR_POL_SHIFT                    8 
#define PWM_PWM2_CR_POL_BIT                      0x1
#define PWM_PWM2_CR_POL_BITWIDTH                 1
// LVS bitfiled (RW) Reset=0
#define PWM_PWM2_CR_LVS_MASK                     0x200
#define PWM_PWM2_CR_LVS_SHIFT                    9 
#define PWM_PWM2_CR_LVS_BIT                      0x1
#define PWM_PWM2_CR_LVS_BITWIDTH                 1
// reserved2 bitfiled (RO) Reset=0
#define PWM_PWM2_CR_RESERVED2_MASK               0xFC00
#define PWM_PWM2_CR_RESERVED2_SHIFT              10 
#define PWM_PWM2_CR_RESERVED2_BIT                0x3F
#define PWM_PWM2_CR_RESERVED2_BITWIDTH           6
// DIV bitfiled (RW) Reset=0
#define PWM_PWM2_CR_DIV_MASK                     0xF0000
#define PWM_PWM2_CR_DIV_SHIFT                    16 
#define PWM_PWM2_CR_DIV_BIT                      0xF
#define PWM_PWM2_CR_DIV_BITWIDTH                 4
// reserved3 bitfiled (RO) Reset=0
#define PWM_PWM2_CR_RESERVED3_MASK               0xF00000
#define PWM_PWM2_CR_RESERVED3_SHIFT              20 
#define PWM_PWM2_CR_RESERVED3_BIT                0xF
#define PWM_PWM2_CR_RESERVED3_BITWIDTH           4
// fixed bitfiled (RW) Reset=0
#define PWM_PWM2_CR_FIXED_MASK                   0x3000000
#define PWM_PWM2_CR_FIXED_SHIFT                  24 
#define PWM_PWM2_CR_FIXED_BIT                    0x3
#define PWM_PWM2_CR_FIXED_BITWIDTH               2
// reserved4 bitfiled (RO) Reset=0
#define PWM_PWM2_CR_RESERVED4_MASK               0xC000000
#define PWM_PWM2_CR_RESERVED4_SHIFT              26 
#define PWM_PWM2_CR_RESERVED4_BIT                0x3
#define PWM_PWM2_CR_RESERVED4_BITWIDTH           2
// ENBSEL bitfiled (RW) Reset=0
#define PWM_PWM2_CR_ENBSEL_MASK                  0x30000000
#define PWM_PWM2_CR_ENBSEL_SHIFT                 28 
#define PWM_PWM2_CR_ENBSEL_BIT                   0x3
#define PWM_PWM2_CR_ENBSEL_BITWIDTH              2
// reserved5 bitfiled (RO) Reset=0
#define PWM_PWM2_CR_RESERVED5_MASK               0xC0000000
#define PWM_PWM2_CR_RESERVED5_SHIFT              30 
#define PWM_PWM2_CR_RESERVED5_BIT                0x3
#define PWM_PWM2_CR_RESERVED5_BITWIDTH           2
// PWM2_FREQ Register
#define PWM_PWM2_FREQ_OFS                        0x00000044
// FREQ bitfiled (RW) Reset=0
#define PWM_PWM2_FREQ_FREQ_MASK                  0xFFFFFFFF
#define PWM_PWM2_FREQ_FREQ_SHIFT                 0 
#define PWM_PWM2_FREQ_FREQ_BIT                   0xFFFFFFFF
#define PWM_PWM2_FREQ_FREQ_BITWIDTH              32
// PWM2_DUTY Register
#define PWM_PWM2_DUTY_OFS                        0x00000048
// DUTY bitfiled (RW) Reset=0
#define PWM_PWM2_DUTY_DUTY_MASK                  0xFFFFFFFF
#define PWM_PWM2_DUTY_DUTY_SHIFT                 0 
#define PWM_PWM2_DUTY_DUTY_BIT                   0xFFFFFFFF
#define PWM_PWM2_DUTY_DUTY_BITWIDTH              32
// PWM2_ITERATION Register
#define PWM_PWM2_ITERATION_OFS                   0x0000004C
// ITERATION bitfiled (RW) Reset=0
#define PWM_PWM2_ITERATION_ITERATION_MASK        0xFFFF
#define PWM_PWM2_ITERATION_ITERATION_SHIFT       0 
#define PWM_PWM2_ITERATION_ITERATION_BIT         0xFFFF
#define PWM_PWM2_ITERATION_ITERATION_BITWIDTH    16
// reserved bitfiled (RO) Reset=0
#define PWM_PWM2_ITERATION_RESERVED_MASK         0xFFFF0000
#define PWM_PWM2_ITERATION_RESERVED_SHIFT        16 
#define PWM_PWM2_ITERATION_RESERVED_BIT          0xFFFF
#define PWM_PWM2_ITERATION_RESERVED_BITWIDTH     16
// PWM2_CURFREQ Register
#define PWM_PWM2_CURFREQ_OFS                     0x00000050
// CURFREQ bitfiled (RO) Reset=0
#define PWM_PWM2_CURFREQ_CURFREQ_MASK            0xFFFFFFFF
#define PWM_PWM2_CURFREQ_CURFREQ_SHIFT           0 
#define PWM_PWM2_CURFREQ_CURFREQ_BIT             0xFFFFFFFF
#define PWM_PWM2_CURFREQ_CURFREQ_BITWIDTH        32
// PWM2_CURDUTY Register
#define PWM_PWM2_CURDUTY_OFS                     0x00000054
// INTC0 bitfiled (RO) Reset=0
#define PWM_PWM2_CURDUTY_INTC0_MASK              0xFFFFFFFF
#define PWM_PWM2_CURDUTY_INTC0_SHIFT             0 
#define PWM_PWM2_CURDUTY_INTC0_BIT               0xFFFFFFFF
#define PWM_PWM2_CURDUTY_INTC0_BITWIDTH          32
// PWM2_CURITER Register
#define PWM_PWM2_CURITER_OFS                     0x00000058
// CURITER bitfiled (RO) Reset=0
#define PWM_PWM2_CURITER_CURITER_MASK            0xFFFF
#define PWM_PWM2_CURITER_CURITER_SHIFT           0 
#define PWM_PWM2_CURITER_CURITER_BIT             0xFFFF
#define PWM_PWM2_CURITER_CURITER_BITWIDTH        16
// CURCYCLE bitfiled (RO) Reset=0
#define PWM_PWM2_CURITER_CURCYCLE_MASK           0xFFFF0000
#define PWM_PWM2_CURITER_CURCYCLE_SHIFT          16 
#define PWM_PWM2_CURITER_CURCYCLE_BIT            0xFFFF
#define PWM_PWM2_CURITER_CURCYCLE_BITWIDTH       16
// PWM2_COUNT Register
#define PWM_PWM2_COUNT_OFS                       0x0000005C
// COUNT bitfiled (RO) Reset=0
#define PWM_PWM2_COUNT_COUNT_MASK                0xFFFFFFFF
#define PWM_PWM2_COUNT_COUNT_SHIFT               0 
#define PWM_PWM2_COUNT_COUNT_BIT                 0xFFFFFFFF
#define PWM_PWM2_COUNT_COUNT_BITWIDTH            32
// PWM3_CR Register
#define PWM_PWM3_CR_OFS                          0x00000060
// ENB bitfiled (RW) Reset=0
#define PWM_PWM3_CR_ENB_MASK                     0x1
#define PWM_PWM3_CR_ENB_SHIFT                    0 
#define PWM_PWM3_CR_ENB_BIT                      0x1
#define PWM_PWM3_CR_ENB_BITWIDTH                 1
// UPD bitfiled (RW) Reset=0
#define PWM_PWM3_CR_UPD_MASK                     0x2
#define PWM_PWM3_CR_UPD_SHIFT                    1 
#define PWM_PWM3_CR_UPD_BIT                      0x1
#define PWM_PWM3_CR_UPD_BITWIDTH                 1
// reserved1 bitfiled (RO) Reset=0
#define PWM_PWM3_CR_RESERVED1_MASK               0xFC
#define PWM_PWM3_CR_RESERVED1_SHIFT              2 
#define PWM_PWM3_CR_RESERVED1_BIT                0x3F
#define PWM_PWM3_CR_RESERVED1_BITWIDTH           6
// POL bitfiled (RW) Reset=0
#define PWM_PWM3_CR_POL_MASK                     0x100
#define PWM_PWM3_CR_POL_SHIFT                    8 
#define PWM_PWM3_CR_POL_BIT                      0x1
#define PWM_PWM3_CR_POL_BITWIDTH                 1
// LVS bitfiled (RW) Reset=0
#define PWM_PWM3_CR_LVS_MASK                     0x200
#define PWM_PWM3_CR_LVS_SHIFT                    9 
#define PWM_PWM3_CR_LVS_BIT                      0x1
#define PWM_PWM3_CR_LVS_BITWIDTH                 1
// reserved2 bitfiled (RO) Reset=0
#define PWM_PWM3_CR_RESERVED2_MASK               0xFC00
#define PWM_PWM3_CR_RESERVED2_SHIFT              10 
#define PWM_PWM3_CR_RESERVED2_BIT                0x3F
#define PWM_PWM3_CR_RESERVED2_BITWIDTH           6
// DIV bitfiled (RW) Reset=0
#define PWM_PWM3_CR_DIV_MASK                     0xF0000
#define PWM_PWM3_CR_DIV_SHIFT                    16 
#define PWM_PWM3_CR_DIV_BIT                      0xF
#define PWM_PWM3_CR_DIV_BITWIDTH                 4
// reserved3 bitfiled (RO) Reset=0
#define PWM_PWM3_CR_RESERVED3_MASK               0xF00000
#define PWM_PWM3_CR_RESERVED3_SHIFT              20 
#define PWM_PWM3_CR_RESERVED3_BIT                0xF
#define PWM_PWM3_CR_RESERVED3_BITWIDTH           4
// fixed bitfiled (RW) Reset=0
#define PWM_PWM3_CR_FIXED_MASK                   0x3000000
#define PWM_PWM3_CR_FIXED_SHIFT                  24 
#define PWM_PWM3_CR_FIXED_BIT                    0x3
#define PWM_PWM3_CR_FIXED_BITWIDTH               2
// reserved4 bitfiled (RO) Reset=0
#define PWM_PWM3_CR_RESERVED4_MASK               0xC000000
#define PWM_PWM3_CR_RESERVED4_SHIFT              26 
#define PWM_PWM3_CR_RESERVED4_BIT                0x3
#define PWM_PWM3_CR_RESERVED4_BITWIDTH           2
// ENBSEL bitfiled (RW) Reset=0
#define PWM_PWM3_CR_ENBSEL_MASK                  0x30000000
#define PWM_PWM3_CR_ENBSEL_SHIFT                 28 
#define PWM_PWM3_CR_ENBSEL_BIT                   0x3
#define PWM_PWM3_CR_ENBSEL_BITWIDTH              2
// reserved5 bitfiled (RO) Reset=0
#define PWM_PWM3_CR_RESERVED5_MASK               0xC0000000
#define PWM_PWM3_CR_RESERVED5_SHIFT              30 
#define PWM_PWM3_CR_RESERVED5_BIT                0x3
#define PWM_PWM3_CR_RESERVED5_BITWIDTH           2
// PWM3_FREQ Register
#define PWM_PWM3_FREQ_OFS                        0x00000064
// FREQ bitfiled (RW) Reset=0
#define PWM_PWM3_FREQ_FREQ_MASK                  0xFFFFFFFF
#define PWM_PWM3_FREQ_FREQ_SHIFT                 0 
#define PWM_PWM3_FREQ_FREQ_BIT                   0xFFFFFFFF
#define PWM_PWM3_FREQ_FREQ_BITWIDTH              32
// PWM3_DUTY Register
#define PWM_PWM3_DUTY_OFS                        0x00000068
// DUTY bitfiled (RW) Reset=0
#define PWM_PWM3_DUTY_DUTY_MASK                  0xFFFFFFFF
#define PWM_PWM3_DUTY_DUTY_SHIFT                 0 
#define PWM_PWM3_DUTY_DUTY_BIT                   0xFFFFFFFF
#define PWM_PWM3_DUTY_DUTY_BITWIDTH              32
// PWM3_ITERATION Register
#define PWM_PWM3_ITERATION_OFS                   0x0000006C
// ITERATION bitfiled (RW) Reset=0
#define PWM_PWM3_ITERATION_ITERATION_MASK        0xFFFF
#define PWM_PWM3_ITERATION_ITERATION_SHIFT       0 
#define PWM_PWM3_ITERATION_ITERATION_BIT         0xFFFF
#define PWM_PWM3_ITERATION_ITERATION_BITWIDTH    16
// reserved bitfiled (RO) Reset=0
#define PWM_PWM3_ITERATION_RESERVED_MASK         0xFFFF0000
#define PWM_PWM3_ITERATION_RESERVED_SHIFT        16 
#define PWM_PWM3_ITERATION_RESERVED_BIT          0xFFFF
#define PWM_PWM3_ITERATION_RESERVED_BITWIDTH     16
// PWM3_CURFREQ Register
#define PWM_PWM3_CURFREQ_OFS                     0x00000070
// CURFREQ bitfiled (RO) Reset=0
#define PWM_PWM3_CURFREQ_CURFREQ_MASK            0xFFFFFFFF
#define PWM_PWM3_CURFREQ_CURFREQ_SHIFT           0 
#define PWM_PWM3_CURFREQ_CURFREQ_BIT             0xFFFFFFFF
#define PWM_PWM3_CURFREQ_CURFREQ_BITWIDTH        32
// PWM3_CURDUTY Register
#define PWM_PWM3_CURDUTY_OFS                     0x00000074
// INTC0 bitfiled (RO) Reset=0
#define PWM_PWM3_CURDUTY_INTC0_MASK              0xFFFFFFFF
#define PWM_PWM3_CURDUTY_INTC0_SHIFT             0 
#define PWM_PWM3_CURDUTY_INTC0_BIT               0xFFFFFFFF
#define PWM_PWM3_CURDUTY_INTC0_BITWIDTH          32
// PWM3_CURITER Register
#define PWM_PWM3_CURITER_OFS                     0x00000078
// CURITER bitfiled (RO) Reset=0
#define PWM_PWM3_CURITER_CURITER_MASK            0xFFFF
#define PWM_PWM3_CURITER_CURITER_SHIFT           0 
#define PWM_PWM3_CURITER_CURITER_BIT             0xFFFF
#define PWM_PWM3_CURITER_CURITER_BITWIDTH        16
// CURCYCLE bitfiled (RO) Reset=0
#define PWM_PWM3_CURITER_CURCYCLE_MASK           0xFFFF0000
#define PWM_PWM3_CURITER_CURCYCLE_SHIFT          16 
#define PWM_PWM3_CURITER_CURCYCLE_BIT            0xFFFF
#define PWM_PWM3_CURITER_CURCYCLE_BITWIDTH       16
// PWM3_COUNT Register
#define PWM_PWM3_COUNT_OFS                       0x0000007C
// COUNT bitfiled (RO) Reset=0
#define PWM_PWM3_COUNT_COUNT_MASK                0xFFFFFFFF
#define PWM_PWM3_COUNT_COUNT_SHIFT               0 
#define PWM_PWM3_COUNT_COUNT_BIT                 0xFFFFFFFF
#define PWM_PWM3_COUNT_COUNT_BITWIDTH            32
// PWM4_CR Register
#define PWM_PWM4_CR_OFS                          0x00000080
// ENB bitfiled (RW) Reset=0
#define PWM_PWM4_CR_ENB_MASK                     0x1
#define PWM_PWM4_CR_ENB_SHIFT                    0 
#define PWM_PWM4_CR_ENB_BIT                      0x1
#define PWM_PWM4_CR_ENB_BITWIDTH                 1
// UPD bitfiled (RW) Reset=0
#define PWM_PWM4_CR_UPD_MASK                     0x2
#define PWM_PWM4_CR_UPD_SHIFT                    1 
#define PWM_PWM4_CR_UPD_BIT                      0x1
#define PWM_PWM4_CR_UPD_BITWIDTH                 1
// reserved1 bitfiled (RO) Reset=0
#define PWM_PWM4_CR_RESERVED1_MASK               0xFC
#define PWM_PWM4_CR_RESERVED1_SHIFT              2 
#define PWM_PWM4_CR_RESERVED1_BIT                0x3F
#define PWM_PWM4_CR_RESERVED1_BITWIDTH           6
// POL bitfiled (RW) Reset=0
#define PWM_PWM4_CR_POL_MASK                     0x100
#define PWM_PWM4_CR_POL_SHIFT                    8 
#define PWM_PWM4_CR_POL_BIT                      0x1
#define PWM_PWM4_CR_POL_BITWIDTH                 1
// LVS bitfiled (RW) Reset=0
#define PWM_PWM4_CR_LVS_MASK                     0x200
#define PWM_PWM4_CR_LVS_SHIFT                    9 
#define PWM_PWM4_CR_LVS_BIT                      0x1
#define PWM_PWM4_CR_LVS_BITWIDTH                 1
// reserved2 bitfiled (RO) Reset=0
#define PWM_PWM4_CR_RESERVED2_MASK               0xFC00
#define PWM_PWM4_CR_RESERVED2_SHIFT              10 
#define PWM_PWM4_CR_RESERVED2_BIT                0x3F
#define PWM_PWM4_CR_RESERVED2_BITWIDTH           6
// DIV bitfiled (RW) Reset=0
#define PWM_PWM4_CR_DIV_MASK                     0xF0000
#define PWM_PWM4_CR_DIV_SHIFT                    16 
#define PWM_PWM4_CR_DIV_BIT                      0xF
#define PWM_PWM4_CR_DIV_BITWIDTH                 4
// reserved3 bitfiled (RO) Reset=0
#define PWM_PWM4_CR_RESERVED3_MASK               0xF00000
#define PWM_PWM4_CR_RESERVED3_SHIFT              20 
#define PWM_PWM4_CR_RESERVED3_BIT                0xF
#define PWM_PWM4_CR_RESERVED3_BITWIDTH           4
// fixed bitfiled (RW) Reset=0
#define PWM_PWM4_CR_FIXED_MASK                   0x3000000
#define PWM_PWM4_CR_FIXED_SHIFT                  24 
#define PWM_PWM4_CR_FIXED_BIT                    0x3
#define PWM_PWM4_CR_FIXED_BITWIDTH               2
// reserved4 bitfiled (RO) Reset=0
#define PWM_PWM4_CR_RESERVED4_MASK               0xC000000
#define PWM_PWM4_CR_RESERVED4_SHIFT              26 
#define PWM_PWM4_CR_RESERVED4_BIT                0x3
#define PWM_PWM4_CR_RESERVED4_BITWIDTH           2
// ENBSEL bitfiled (RW) Reset=0
#define PWM_PWM4_CR_ENBSEL_MASK                  0x30000000
#define PWM_PWM4_CR_ENBSEL_SHIFT                 28 
#define PWM_PWM4_CR_ENBSEL_BIT                   0x3
#define PWM_PWM4_CR_ENBSEL_BITWIDTH              2
// reserved5 bitfiled (RO) Reset=0
#define PWM_PWM4_CR_RESERVED5_MASK               0xC0000000
#define PWM_PWM4_CR_RESERVED5_SHIFT              30 
#define PWM_PWM4_CR_RESERVED5_BIT                0x3
#define PWM_PWM4_CR_RESERVED5_BITWIDTH           2
// PWM4_FREQ Register
#define PWM_PWM4_FREQ_OFS                        0x00000084
// FREQ bitfiled (RW) Reset=0
#define PWM_PWM4_FREQ_FREQ_MASK                  0xFFFFFFFF
#define PWM_PWM4_FREQ_FREQ_SHIFT                 0 
#define PWM_PWM4_FREQ_FREQ_BIT                   0xFFFFFFFF
#define PWM_PWM4_FREQ_FREQ_BITWIDTH              32
// PWM4_DUTY Register
#define PWM_PWM4_DUTY_OFS                        0x00000088
// DUTY bitfiled (RW) Reset=0
#define PWM_PWM4_DUTY_DUTY_MASK                  0xFFFFFFFF
#define PWM_PWM4_DUTY_DUTY_SHIFT                 0 
#define PWM_PWM4_DUTY_DUTY_BIT                   0xFFFFFFFF
#define PWM_PWM4_DUTY_DUTY_BITWIDTH              32
// PWM4_ITERATION Register
#define PWM_PWM4_ITERATION_OFS                   0x0000008C
// ITERATION bitfiled (RW) Reset=0
#define PWM_PWM4_ITERATION_ITERATION_MASK        0xFFFF
#define PWM_PWM4_ITERATION_ITERATION_SHIFT       0 
#define PWM_PWM4_ITERATION_ITERATION_BIT         0xFFFF
#define PWM_PWM4_ITERATION_ITERATION_BITWIDTH    16
// reserved bitfiled (RO) Reset=0
#define PWM_PWM4_ITERATION_RESERVED_MASK         0xFFFF0000
#define PWM_PWM4_ITERATION_RESERVED_SHIFT        16 
#define PWM_PWM4_ITERATION_RESERVED_BIT          0xFFFF
#define PWM_PWM4_ITERATION_RESERVED_BITWIDTH     16
// PWM4_CURFREQ Register
#define PWM_PWM4_CURFREQ_OFS                     0x00000090
// CURFREQ bitfiled (RO) Reset=0
#define PWM_PWM4_CURFREQ_CURFREQ_MASK            0xFFFFFFFF
#define PWM_PWM4_CURFREQ_CURFREQ_SHIFT           0 
#define PWM_PWM4_CURFREQ_CURFREQ_BIT             0xFFFFFFFF
#define PWM_PWM4_CURFREQ_CURFREQ_BITWIDTH        32
// PWM4_CURDUTY Register
#define PWM_PWM4_CURDUTY_OFS                     0x00000094
// INTC0 bitfiled (RO) Reset=0
#define PWM_PWM4_CURDUTY_INTC0_MASK              0xFFFFFFFF
#define PWM_PWM4_CURDUTY_INTC0_SHIFT             0 
#define PWM_PWM4_CURDUTY_INTC0_BIT               0xFFFFFFFF
#define PWM_PWM4_CURDUTY_INTC0_BITWIDTH          32
// PWM4_CURITER Register
#define PWM_PWM4_CURITER_OFS                     0x00000098
// CURITER bitfiled (RO) Reset=0
#define PWM_PWM4_CURITER_CURITER_MASK            0xFFFF
#define PWM_PWM4_CURITER_CURITER_SHIFT           0 
#define PWM_PWM4_CURITER_CURITER_BIT             0xFFFF
#define PWM_PWM4_CURITER_CURITER_BITWIDTH        16
// CURCYCLE bitfiled (RO) Reset=0
#define PWM_PWM4_CURITER_CURCYCLE_MASK           0xFFFF0000
#define PWM_PWM4_CURITER_CURCYCLE_SHIFT          16 
#define PWM_PWM4_CURITER_CURCYCLE_BIT            0xFFFF
#define PWM_PWM4_CURITER_CURCYCLE_BITWIDTH       16
// PWM4_COUNT Register
#define PWM_PWM4_COUNT_OFS                       0x0000009C
// COUNT bitfiled (RO) Reset=0
#define PWM_PWM4_COUNT_COUNT_MASK                0xFFFFFFFF
#define PWM_PWM4_COUNT_COUNT_SHIFT               0 
#define PWM_PWM4_COUNT_COUNT_BIT                 0xFFFFFFFF
#define PWM_PWM4_COUNT_COUNT_BITWIDTH            32
// PWM_SYSTEM Register
#define PWM_PWM_SYSTEM_OFS                       0x00000200
// SWRST bitfiled (RW) Reset=0
#define PWM_PWM_SYSTEM_SWRST_MASK                0x1
#define PWM_PWM_SYSTEM_SWRST_SHIFT               0 
#define PWM_PWM_SYSTEM_SWRST_BIT                 0x1
#define PWM_PWM_SYSTEM_SWRST_BITWIDTH            1
// reserved bitfiled (RO) Reset=0
#define PWM_PWM_SYSTEM_RESERVED_MASK             0xFFFFFFFE
#define PWM_PWM_SYSTEM_RESERVED_SHIFT            1 
#define PWM_PWM_SYSTEM_RESERVED_BIT              0x7FFFFFFF
#define PWM_PWM_SYSTEM_RESERVED_BITWIDTH         31
// PWM_GENB Register
#define PWM_PWM_GENB_OFS                         0x00000204
// GENB0 bitfiled (RW) Reset=0
#define PWM_PWM_GENB_GENB0_MASK                  0x1
#define PWM_PWM_GENB_GENB0_SHIFT                 0 
#define PWM_PWM_GENB_GENB0_BIT                   0x1
#define PWM_PWM_GENB_GENB0_BITWIDTH              1
// reserved3 bitfiled (RO) Reset=0
#define PWM_PWM_GENB_RESERVED3_MASK              0xE
#define PWM_PWM_GENB_RESERVED3_SHIFT             1 
#define PWM_PWM_GENB_RESERVED3_BIT               0x7
#define PWM_PWM_GENB_RESERVED3_BITWIDTH          3
// GENB1 bitfiled (RW) Reset=0
#define PWM_PWM_GENB_GENB1_MASK                  0x10
#define PWM_PWM_GENB_GENB1_SHIFT                 4 
#define PWM_PWM_GENB_GENB1_BIT                   0x1
#define PWM_PWM_GENB_GENB1_BITWIDTH              1
// reserved2 bitfiled (RO) Reset=0
#define PWM_PWM_GENB_RESERVED2_MASK              0xE0
#define PWM_PWM_GENB_RESERVED2_SHIFT             5 
#define PWM_PWM_GENB_RESERVED2_BIT               0x7
#define PWM_PWM_GENB_RESERVED2_BITWIDTH          3
// GENB2 bitfiled (RW) Reset=0
#define PWM_PWM_GENB_GENB2_MASK                  0x100
#define PWM_PWM_GENB_GENB2_SHIFT                 8 
#define PWM_PWM_GENB_GENB2_BIT                   0x1
#define PWM_PWM_GENB_GENB2_BITWIDTH              1
// reserved bitfiled (RO) Reset=0
#define PWM_PWM_GENB_RESERVED_MASK               0xFFFFFE00
#define PWM_PWM_GENB_RESERVED_SHIFT              9 
#define PWM_PWM_GENB_RESERVED_BIT                0x7FFFFF
#define PWM_PWM_GENB_RESERVED_BITWIDTH           23
// PWM_INTCONFIG Register
#define PWM_PWM_INTCONFIG_OFS                    0x00000220
// INTMODE0 bitfiled (RW) Reset=0
#define PWM_PWM_INTCONFIG_INTMODE0_MASK          0x1
#define PWM_PWM_INTCONFIG_INTMODE0_SHIFT         0 
#define PWM_PWM_INTCONFIG_INTMODE0_BIT           0x1
#define PWM_PWM_INTCONFIG_INTMODE0_BITWIDTH      1
// INTMODE1 bitfiled (RW) Reset=0
#define PWM_PWM_INTCONFIG_INTMODE1_MASK          0x2
#define PWM_PWM_INTCONFIG_INTMODE1_SHIFT         1 
#define PWM_PWM_INTCONFIG_INTMODE1_BIT           0x1
#define PWM_PWM_INTCONFIG_INTMODE1_BITWIDTH      1
// INTMODE2 bitfiled (RW) Reset=0
#define PWM_PWM_INTCONFIG_INTMODE2_MASK          0x4
#define PWM_PWM_INTCONFIG_INTMODE2_SHIFT         2 
#define PWM_PWM_INTCONFIG_INTMODE2_BIT           0x1
#define PWM_PWM_INTCONFIG_INTMODE2_BITWIDTH      1
// INTMODE3 bitfiled (RW) Reset=0
#define PWM_PWM_INTCONFIG_INTMODE3_MASK          0x8
#define PWM_PWM_INTCONFIG_INTMODE3_SHIFT         3 
#define PWM_PWM_INTCONFIG_INTMODE3_BIT           0x1
#define PWM_PWM_INTCONFIG_INTMODE3_BITWIDTH      1
// INTMODE4 bitfiled (RW) Reset=0
#define PWM_PWM_INTCONFIG_INTMODE4_MASK          0x10
#define PWM_PWM_INTCONFIG_INTMODE4_SHIFT         4 
#define PWM_PWM_INTCONFIG_INTMODE4_BIT           0x1
#define PWM_PWM_INTCONFIG_INTMODE4_BITWIDTH      1
// reserved bitfiled (RO) Reset=0
#define PWM_PWM_INTCONFIG_RESERVED_MASK          0x7FFFFFE0
#define PWM_PWM_INTCONFIG_RESERVED_SHIFT         5 
#define PWM_PWM_INTCONFIG_RESERVED_BIT           0x3FFFFFF
#define PWM_PWM_INTCONFIG_RESERVED_BITWIDTH      26
// reserved2 bitfiled (RO) Reset=0
#define PWM_PWM_INTCONFIG_RESERVED2_MASK         0x80000000
#define PWM_PWM_INTCONFIG_RESERVED2_SHIFT        31 
#define PWM_PWM_INTCONFIG_RESERVED2_BIT          0x1
#define PWM_PWM_INTCONFIG_RESERVED2_BITWIDTH     1
// PWM_INTMASK Register
#define PWM_PWM_INTMASK_OFS                      0x00000224
// INTMASK0 bitfiled (RW) Reset=0
#define PWM_PWM_INTMASK_INTMASK0_MASK            0x1
#define PWM_PWM_INTMASK_INTMASK0_SHIFT           0 
#define PWM_PWM_INTMASK_INTMASK0_BIT             0x1
#define PWM_PWM_INTMASK_INTMASK0_BITWIDTH        1
// INTMASK1 bitfiled (RW) Reset=0
#define PWM_PWM_INTMASK_INTMASK1_MASK            0x2
#define PWM_PWM_INTMASK_INTMASK1_SHIFT           1 
#define PWM_PWM_INTMASK_INTMASK1_BIT             0x1
#define PWM_PWM_INTMASK_INTMASK1_BITWIDTH        1
// INTMASK2 bitfiled (RW) Reset=0
#define PWM_PWM_INTMASK_INTMASK2_MASK            0x4
#define PWM_PWM_INTMASK_INTMASK2_SHIFT           2 
#define PWM_PWM_INTMASK_INTMASK2_BIT             0x1
#define PWM_PWM_INTMASK_INTMASK2_BITWIDTH        1
// INTMASK3 bitfiled (RW) Reset=0
#define PWM_PWM_INTMASK_INTMASK3_MASK            0x8
#define PWM_PWM_INTMASK_INTMASK3_SHIFT           3 
#define PWM_PWM_INTMASK_INTMASK3_BIT             0x1
#define PWM_PWM_INTMASK_INTMASK3_BITWIDTH        1
// INTMASK4 bitfiled (RW) Reset=0
#define PWM_PWM_INTMASK_INTMASK4_MASK            0x10
#define PWM_PWM_INTMASK_INTMASK4_SHIFT           4 
#define PWM_PWM_INTMASK_INTMASK4_BIT             0x1
#define PWM_PWM_INTMASK_INTMASK4_BITWIDTH        1
// reserved2 bitfiled (RO) Reset=0
#define PWM_PWM_INTMASK_RESERVED2_MASK           0x7FE0
#define PWM_PWM_INTMASK_RESERVED2_SHIFT          5 
#define PWM_PWM_INTMASK_RESERVED2_BIT            0x3FF
#define PWM_PWM_INTMASK_RESERVED2_BITWIDTH       10
// reserved3 bitfiled (RO) Reset=0
#define PWM_PWM_INTMASK_RESERVED3_MASK           0x8000
#define PWM_PWM_INTMASK_RESERVED3_SHIFT          15 
#define PWM_PWM_INTMASK_RESERVED3_BIT            0x1
#define PWM_PWM_INTMASK_RESERVED3_BITWIDTH       1
// ERRMASK0 bitfiled (RW) Reset=0
#define PWM_PWM_INTMASK_ERRMASK0_MASK            0x10000
#define PWM_PWM_INTMASK_ERRMASK0_SHIFT           16 
#define PWM_PWM_INTMASK_ERRMASK0_BIT             0x1
#define PWM_PWM_INTMASK_ERRMASK0_BITWIDTH        1
// ERRMASK1 bitfiled (RW) Reset=0
#define PWM_PWM_INTMASK_ERRMASK1_MASK            0x20000
#define PWM_PWM_INTMASK_ERRMASK1_SHIFT           17 
#define PWM_PWM_INTMASK_ERRMASK1_BIT             0x1
#define PWM_PWM_INTMASK_ERRMASK1_BITWIDTH        1
// ERRMASK2 bitfiled (RW) Reset=0
#define PWM_PWM_INTMASK_ERRMASK2_MASK            0x40000
#define PWM_PWM_INTMASK_ERRMASK2_SHIFT           18 
#define PWM_PWM_INTMASK_ERRMASK2_BIT             0x1
#define PWM_PWM_INTMASK_ERRMASK2_BITWIDTH        1
// ERRMASK3 bitfiled (RW) Reset=0
#define PWM_PWM_INTMASK_ERRMASK3_MASK            0x80000
#define PWM_PWM_INTMASK_ERRMASK3_SHIFT           19 
#define PWM_PWM_INTMASK_ERRMASK3_BIT             0x1
#define PWM_PWM_INTMASK_ERRMASK3_BITWIDTH        1
// ERRMASK4 bitfiled (RW) Reset=0
#define PWM_PWM_INTMASK_ERRMASK4_MASK            0x100000
#define PWM_PWM_INTMASK_ERRMASK4_SHIFT           20 
#define PWM_PWM_INTMASK_ERRMASK4_BIT             0x1
#define PWM_PWM_INTMASK_ERRMASK4_BITWIDTH        1
// reserved bitfiled (RO) Reset=0
#define PWM_PWM_INTMASK_RESERVED_MASK            0x7FE00000
#define PWM_PWM_INTMASK_RESERVED_SHIFT           21 
#define PWM_PWM_INTMASK_RESERVED_BIT             0x3FF
#define PWM_PWM_INTMASK_RESERVED_BITWIDTH        10
// reserved4 bitfiled (RO) Reset=0
#define PWM_PWM_INTMASK_RESERVED4_MASK           0x80000000
#define PWM_PWM_INTMASK_RESERVED4_SHIFT          31 
#define PWM_PWM_INTMASK_RESERVED4_BIT            0x1
#define PWM_PWM_INTMASK_RESERVED4_BITWIDTH       1
// PWM_INTSTATUS Register
#define PWM_PWM_INTSTATUS_OFS                    0x00000228
// INTSTATUS0 bitfiled (RW) Reset=0
#define PWM_PWM_INTSTATUS_INTSTATUS0_MASK        0x1
#define PWM_PWM_INTSTATUS_INTSTATUS0_SHIFT       0 
#define PWM_PWM_INTSTATUS_INTSTATUS0_BIT         0x1
#define PWM_PWM_INTSTATUS_INTSTATUS0_BITWIDTH    1
// INTSTATUS1 bitfiled (RW) Reset=0
#define PWM_PWM_INTSTATUS_INTSTATUS1_MASK        0x2
#define PWM_PWM_INTSTATUS_INTSTATUS1_SHIFT       1 
#define PWM_PWM_INTSTATUS_INTSTATUS1_BIT         0x1
#define PWM_PWM_INTSTATUS_INTSTATUS1_BITWIDTH    1
// INTSTATUS2 bitfiled (RW) Reset=0
#define PWM_PWM_INTSTATUS_INTSTATUS2_MASK        0x4
#define PWM_PWM_INTSTATUS_INTSTATUS2_SHIFT       2 
#define PWM_PWM_INTSTATUS_INTSTATUS2_BIT         0x1
#define PWM_PWM_INTSTATUS_INTSTATUS2_BITWIDTH    1
// INTSTATUS3 bitfiled (RW) Reset=0
#define PWM_PWM_INTSTATUS_INTSTATUS3_MASK        0x8
#define PWM_PWM_INTSTATUS_INTSTATUS3_SHIFT       3 
#define PWM_PWM_INTSTATUS_INTSTATUS3_BIT         0x1
#define PWM_PWM_INTSTATUS_INTSTATUS3_BITWIDTH    1
// INTSTATUS4 bitfiled (RW) Reset=0
#define PWM_PWM_INTSTATUS_INTSTATUS4_MASK        0x10
#define PWM_PWM_INTSTATUS_INTSTATUS4_SHIFT       4 
#define PWM_PWM_INTSTATUS_INTSTATUS4_BIT         0x1
#define PWM_PWM_INTSTATUS_INTSTATUS4_BITWIDTH    1
// reserved2 bitfiled (RO) Reset=0
#define PWM_PWM_INTSTATUS_RESERVED2_MASK         0x7FE0
#define PWM_PWM_INTSTATUS_RESERVED2_SHIFT        5 
#define PWM_PWM_INTSTATUS_RESERVED2_BIT          0x3FF
#define PWM_PWM_INTSTATUS_RESERVED2_BITWIDTH     10
// reserved3 bitfiled (RO) Reset=0
#define PWM_PWM_INTSTATUS_RESERVED3_MASK         0x8000
#define PWM_PWM_INTSTATUS_RESERVED3_SHIFT        15 
#define PWM_PWM_INTSTATUS_RESERVED3_BIT          0x1
#define PWM_PWM_INTSTATUS_RESERVED3_BITWIDTH     1
// ERRSTATUS0 bitfiled (RW) Reset=0
#define PWM_PWM_INTSTATUS_ERRSTATUS0_MASK        0x10000
#define PWM_PWM_INTSTATUS_ERRSTATUS0_SHIFT       16 
#define PWM_PWM_INTSTATUS_ERRSTATUS0_BIT         0x1
#define PWM_PWM_INTSTATUS_ERRSTATUS0_BITWIDTH    1
// ERRSTATUS1 bitfiled (RW) Reset=0
#define PWM_PWM_INTSTATUS_ERRSTATUS1_MASK        0x20000
#define PWM_PWM_INTSTATUS_ERRSTATUS1_SHIFT       17 
#define PWM_PWM_INTSTATUS_ERRSTATUS1_BIT         0x1
#define PWM_PWM_INTSTATUS_ERRSTATUS1_BITWIDTH    1
// ERRSTATUS2 bitfiled (RW) Reset=0
#define PWM_PWM_INTSTATUS_ERRSTATUS2_MASK        0x40000
#define PWM_PWM_INTSTATUS_ERRSTATUS2_SHIFT       18 
#define PWM_PWM_INTSTATUS_ERRSTATUS2_BIT         0x1
#define PWM_PWM_INTSTATUS_ERRSTATUS2_BITWIDTH    1
// ERRSTATUS3 bitfiled (RW) Reset=0
#define PWM_PWM_INTSTATUS_ERRSTATUS3_MASK        0x80000
#define PWM_PWM_INTSTATUS_ERRSTATUS3_SHIFT       19 
#define PWM_PWM_INTSTATUS_ERRSTATUS3_BIT         0x1
#define PWM_PWM_INTSTATUS_ERRSTATUS3_BITWIDTH    1
// ERRSTATUS4 bitfiled (RW) Reset=0
#define PWM_PWM_INTSTATUS_ERRSTATUS4_MASK        0x100000
#define PWM_PWM_INTSTATUS_ERRSTATUS4_SHIFT       20 
#define PWM_PWM_INTSTATUS_ERRSTATUS4_BIT         0x1
#define PWM_PWM_INTSTATUS_ERRSTATUS4_BITWIDTH    1
// reserved bitfiled (RO) Reset=0
#define PWM_PWM_INTSTATUS_RESERVED_MASK          0x7FE00000
#define PWM_PWM_INTSTATUS_RESERVED_SHIFT         21 
#define PWM_PWM_INTSTATUS_RESERVED_BIT           0x3FF
#define PWM_PWM_INTSTATUS_RESERVED_BITWIDTH      10
// reserved4 bitfiled (RO) Reset=0
#define PWM_PWM_INTSTATUS_RESERVED4_MASK         0x80000000
#define PWM_PWM_INTSTATUS_RESERVED4_SHIFT        31 
#define PWM_PWM_INTSTATUS_RESERVED4_BIT          0x1
#define PWM_PWM_INTSTATUS_RESERVED4_BITWIDTH     1

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _PWM_REG_DEF_H */
