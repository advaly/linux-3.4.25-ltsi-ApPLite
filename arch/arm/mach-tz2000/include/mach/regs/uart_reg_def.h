/*
 * arch/arm/mach-tz2000/include/mach/regs/uart_reg_def.h
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

#ifndef _UART_REG_DEF_H
#define _UART_REG_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

// UA0_RBR_THR_DLL Register
#define UART_UA0_RBR_THR_DLL_OFS                 0x00000000
// RBR_THR_DLL bitfiled (RW) Reset=0
#define UART_UA0_RBR_THR_DLL_RBR_THR_DLL_MASK    0xFF
#define UART_UA0_RBR_THR_DLL_RBR_THR_DLL_SHIFT   0 
#define UART_UA0_RBR_THR_DLL_RBR_THR_DLL_BIT     0xFF
#define UART_UA0_RBR_THR_DLL_RBR_THR_DLL_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define UART_UA0_RBR_THR_DLL_RESERVED_MASK       0xFFFFFF00
#define UART_UA0_RBR_THR_DLL_RESERVED_SHIFT      8 
#define UART_UA0_RBR_THR_DLL_RESERVED_BIT        0xFFFFFF
#define UART_UA0_RBR_THR_DLL_RESERVED_BITWIDTH   24
// UA0_IER_DLH Register
#define UART_UA0_IER_DLH_OFS                     0x00000004
// ERBFI_DLH0 bitfiled (RW) Reset=0
#define UART_UA0_IER_DLH_ERBFI_DLH0_MASK         0x1
#define UART_UA0_IER_DLH_ERBFI_DLH0_SHIFT        0 
#define UART_UA0_IER_DLH_ERBFI_DLH0_BIT          0x1
#define UART_UA0_IER_DLH_ERBFI_DLH0_BITWIDTH     1
// ETBEI_DLH1 bitfiled (RW) Reset=0
#define UART_UA0_IER_DLH_ETBEI_DLH1_MASK         0x2
#define UART_UA0_IER_DLH_ETBEI_DLH1_SHIFT        1 
#define UART_UA0_IER_DLH_ETBEI_DLH1_BIT          0x1
#define UART_UA0_IER_DLH_ETBEI_DLH1_BITWIDTH     1
// ELSI_DLH2 bitfiled (RW) Reset=0
#define UART_UA0_IER_DLH_ELSI_DLH2_MASK          0x4
#define UART_UA0_IER_DLH_ELSI_DLH2_SHIFT         2 
#define UART_UA0_IER_DLH_ELSI_DLH2_BIT           0x1
#define UART_UA0_IER_DLH_ELSI_DLH2_BITWIDTH      1
// EDSSI_DLH3 bitfiled (RW) Reset=0
#define UART_UA0_IER_DLH_EDSSI_DLH3_MASK         0x8
#define UART_UA0_IER_DLH_EDSSI_DLH3_SHIFT        3 
#define UART_UA0_IER_DLH_EDSSI_DLH3_BIT          0x1
#define UART_UA0_IER_DLH_EDSSI_DLH3_BITWIDTH     1
// DLH64 bitfiled (RW) Reset=0
#define UART_UA0_IER_DLH_DLH64_MASK              0x70
#define UART_UA0_IER_DLH_DLH64_SHIFT             4 
#define UART_UA0_IER_DLH_DLH64_BIT               0x7
#define UART_UA0_IER_DLH_DLH64_BITWIDTH          3
// PTIME_DLH7 bitfiled (RW) Reset=0
#define UART_UA0_IER_DLH_PTIME_DLH7_MASK         0x80
#define UART_UA0_IER_DLH_PTIME_DLH7_SHIFT        7 
#define UART_UA0_IER_DLH_PTIME_DLH7_BIT          0x1
#define UART_UA0_IER_DLH_PTIME_DLH7_BITWIDTH     1
// reserved bitfiled (RO) Reset=0
#define UART_UA0_IER_DLH_RESERVED_MASK           0xFFFFFF00
#define UART_UA0_IER_DLH_RESERVED_SHIFT          8 
#define UART_UA0_IER_DLH_RESERVED_BIT            0xFFFFFF
#define UART_UA0_IER_DLH_RESERVED_BITWIDTH       24
// UA0_FCR_IIR Register
#define UART_UA0_FCR_IIR_OFS                     0x00000008
// IID0_FIFOE bitfiled (RW) Reset=1
#define UART_UA0_FCR_IIR_IID0_FIFOE_MASK         0x1
#define UART_UA0_FCR_IIR_IID0_FIFOE_SHIFT        0 
#define UART_UA0_FCR_IIR_IID0_FIFOE_BIT          0x1
#define UART_UA0_FCR_IIR_IID0_FIFOE_BITWIDTH     1
// IID1_RFIFOR bitfiled (RW) Reset=0
#define UART_UA0_FCR_IIR_IID1_RFIFOR_MASK        0x2
#define UART_UA0_FCR_IIR_IID1_RFIFOR_SHIFT       1 
#define UART_UA0_FCR_IIR_IID1_RFIFOR_BIT         0x1
#define UART_UA0_FCR_IIR_IID1_RFIFOR_BITWIDTH    1
// IID2_XFIFOR bitfiled (RW) Reset=0
#define UART_UA0_FCR_IIR_IID2_XFIFOR_MASK        0x4
#define UART_UA0_FCR_IIR_IID2_XFIFOR_SHIFT       2 
#define UART_UA0_FCR_IIR_IID2_XFIFOR_BIT         0x1
#define UART_UA0_FCR_IIR_IID2_XFIFOR_BITWIDTH    1
// IID3_DMAM bitfiled (RW) Reset=0
#define UART_UA0_FCR_IIR_IID3_DMAM_MASK          0x8
#define UART_UA0_FCR_IIR_IID3_DMAM_SHIFT         3 
#define UART_UA0_FCR_IIR_IID3_DMAM_BIT           0x1
#define UART_UA0_FCR_IIR_IID3_DMAM_BITWIDTH      1
// TET bitfiled (RW) Reset=0
#define UART_UA0_FCR_IIR_TET_MASK                0x30
#define UART_UA0_FCR_IIR_TET_SHIFT               4 
#define UART_UA0_FCR_IIR_TET_BIT                 0x3
#define UART_UA0_FCR_IIR_TET_BITWIDTH            2
// FIFOSE_RCVR bitfiled (RW) Reset=0
#define UART_UA0_FCR_IIR_FIFOSE_RCVR_MASK        0xC0
#define UART_UA0_FCR_IIR_FIFOSE_RCVR_SHIFT       6 
#define UART_UA0_FCR_IIR_FIFOSE_RCVR_BIT         0x3
#define UART_UA0_FCR_IIR_FIFOSE_RCVR_BITWIDTH    2
// reserved bitfiled (RO) Reset=0
#define UART_UA0_FCR_IIR_RESERVED_MASK           0xFFFFFF00
#define UART_UA0_FCR_IIR_RESERVED_SHIFT          8 
#define UART_UA0_FCR_IIR_RESERVED_BIT            0xFFFFFF
#define UART_UA0_FCR_IIR_RESERVED_BITWIDTH       24
// UA0_LCR Register
#define UART_UA0_LCR_OFS                         0x0000000C
// DLS bitfiled (RW) Reset=0
#define UART_UA0_LCR_DLS_MASK                    0x3
#define UART_UA0_LCR_DLS_SHIFT                   0 
#define UART_UA0_LCR_DLS_BIT                     0x3
#define UART_UA0_LCR_DLS_BITWIDTH                2
// STOP bitfiled (RW) Reset=0
#define UART_UA0_LCR_STOP_MASK                   0x4
#define UART_UA0_LCR_STOP_SHIFT                  2 
#define UART_UA0_LCR_STOP_BIT                    0x1
#define UART_UA0_LCR_STOP_BITWIDTH               1
// PEN bitfiled (RW) Reset=0
#define UART_UA0_LCR_PEN_MASK                    0x8
#define UART_UA0_LCR_PEN_SHIFT                   3 
#define UART_UA0_LCR_PEN_BIT                     0x1
#define UART_UA0_LCR_PEN_BITWIDTH                1
// EPS bitfiled (RW) Reset=0
#define UART_UA0_LCR_EPS_MASK                    0x10
#define UART_UA0_LCR_EPS_SHIFT                   4 
#define UART_UA0_LCR_EPS_BIT                     0x1
#define UART_UA0_LCR_EPS_BITWIDTH                1
// SP bitfiled (RW) Reset=0
#define UART_UA0_LCR_SP_MASK                     0x20
#define UART_UA0_LCR_SP_SHIFT                    5 
#define UART_UA0_LCR_SP_BIT                      0x1
#define UART_UA0_LCR_SP_BITWIDTH                 1
// Break bitfiled (RW) Reset=0
#define UART_UA0_LCR_BREAK_MASK                  0x40
#define UART_UA0_LCR_BREAK_SHIFT                 6 
#define UART_UA0_LCR_BREAK_BIT                   0x1
#define UART_UA0_LCR_BREAK_BITWIDTH              1
// DLAB bitfiled (RW) Reset=0
#define UART_UA0_LCR_DLAB_MASK                   0x80
#define UART_UA0_LCR_DLAB_SHIFT                  7 
#define UART_UA0_LCR_DLAB_BIT                    0x1
#define UART_UA0_LCR_DLAB_BITWIDTH               1
// reserved bitfiled (RO) Reset=0
#define UART_UA0_LCR_RESERVED_MASK               0xFFFFFF00
#define UART_UA0_LCR_RESERVED_SHIFT              8 
#define UART_UA0_LCR_RESERVED_BIT                0xFFFFFF
#define UART_UA0_LCR_RESERVED_BITWIDTH           24
// UA0_MCR Register
#define UART_UA0_MCR_OFS                         0x00000010
// DTR bitfiled (RW) Reset=0
#define UART_UA0_MCR_DTR_MASK                    0x1
#define UART_UA0_MCR_DTR_SHIFT                   0 
#define UART_UA0_MCR_DTR_BIT                     0x1
#define UART_UA0_MCR_DTR_BITWIDTH                1
// RTS bitfiled (RW) Reset=0
#define UART_UA0_MCR_RTS_MASK                    0x2
#define UART_UA0_MCR_RTS_SHIFT                   1 
#define UART_UA0_MCR_RTS_BIT                     0x1
#define UART_UA0_MCR_RTS_BITWIDTH                1
// OUT1 bitfiled (RW) Reset=0
#define UART_UA0_MCR_OUT1_MASK                   0x4
#define UART_UA0_MCR_OUT1_SHIFT                  2 
#define UART_UA0_MCR_OUT1_BIT                    0x1
#define UART_UA0_MCR_OUT1_BITWIDTH               1
// OUT2 bitfiled (RW) Reset=0
#define UART_UA0_MCR_OUT2_MASK                   0x8
#define UART_UA0_MCR_OUT2_SHIFT                  3 
#define UART_UA0_MCR_OUT2_BIT                    0x1
#define UART_UA0_MCR_OUT2_BITWIDTH               1
// LoopBack bitfiled (RW) Reset=0
#define UART_UA0_MCR_LOOPBACK_MASK               0x10
#define UART_UA0_MCR_LOOPBACK_SHIFT              4 
#define UART_UA0_MCR_LOOPBACK_BIT                0x1
#define UART_UA0_MCR_LOOPBACK_BITWIDTH           1
// AFCE bitfiled (RW) Reset=0
#define UART_UA0_MCR_AFCE_MASK                   0x20
#define UART_UA0_MCR_AFCE_SHIFT                  5 
#define UART_UA0_MCR_AFCE_BIT                    0x1
#define UART_UA0_MCR_AFCE_BITWIDTH               1
// SIRE bitfiled (RW) Reset=0
#define UART_UA0_MCR_SIRE_MASK                   0x40
#define UART_UA0_MCR_SIRE_SHIFT                  6 
#define UART_UA0_MCR_SIRE_BIT                    0x1
#define UART_UA0_MCR_SIRE_BITWIDTH               1
// reserved bitfiled (RO) Reset=0
#define UART_UA0_MCR_RESERVED_MASK               0xFFFFFF80
#define UART_UA0_MCR_RESERVED_SHIFT              7 
#define UART_UA0_MCR_RESERVED_BIT                0x1FFFFFF
#define UART_UA0_MCR_RESERVED_BITWIDTH           25
// UA0_LSR Register
#define UART_UA0_LSR_OFS                         0x00000014
// DR bitfiled (RO) Reset=0
#define UART_UA0_LSR_DR_MASK                     0x1
#define UART_UA0_LSR_DR_SHIFT                    0 
#define UART_UA0_LSR_DR_BIT                      0x1
#define UART_UA0_LSR_DR_BITWIDTH                 1
// OE bitfiled (RO) Reset=0
#define UART_UA0_LSR_OE_MASK                     0x2
#define UART_UA0_LSR_OE_SHIFT                    1 
#define UART_UA0_LSR_OE_BIT                      0x1
#define UART_UA0_LSR_OE_BITWIDTH                 1
// PE bitfiled (RO) Reset=0
#define UART_UA0_LSR_PE_MASK                     0x4
#define UART_UA0_LSR_PE_SHIFT                    2 
#define UART_UA0_LSR_PE_BIT                      0x1
#define UART_UA0_LSR_PE_BITWIDTH                 1
// FE bitfiled (RO) Reset=0
#define UART_UA0_LSR_FE_MASK                     0x8
#define UART_UA0_LSR_FE_SHIFT                    3 
#define UART_UA0_LSR_FE_BIT                      0x1
#define UART_UA0_LSR_FE_BITWIDTH                 1
// BI bitfiled (RO) Reset=0
#define UART_UA0_LSR_BI_MASK                     0x10
#define UART_UA0_LSR_BI_SHIFT                    4 
#define UART_UA0_LSR_BI_BIT                      0x1
#define UART_UA0_LSR_BI_BITWIDTH                 1
// THRE bitfiled (RO) Reset=1
#define UART_UA0_LSR_THRE_MASK                   0x20
#define UART_UA0_LSR_THRE_SHIFT                  5 
#define UART_UA0_LSR_THRE_BIT                    0x1
#define UART_UA0_LSR_THRE_BITWIDTH               1
// TEMT bitfiled (RO) Reset=1
#define UART_UA0_LSR_TEMT_MASK                   0x40
#define UART_UA0_LSR_TEMT_SHIFT                  6 
#define UART_UA0_LSR_TEMT_BIT                    0x1
#define UART_UA0_LSR_TEMT_BITWIDTH               1
// RFE bitfiled (RO) Reset=0
#define UART_UA0_LSR_RFE_MASK                    0x80
#define UART_UA0_LSR_RFE_SHIFT                   7 
#define UART_UA0_LSR_RFE_BIT                     0x1
#define UART_UA0_LSR_RFE_BITWIDTH                1
// reserved bitfiled (RO) Reset=0
#define UART_UA0_LSR_RESERVED_MASK               0xFFFFFF00
#define UART_UA0_LSR_RESERVED_SHIFT              8 
#define UART_UA0_LSR_RESERVED_BIT                0xFFFFFF
#define UART_UA0_LSR_RESERVED_BITWIDTH           24
// UA0_MSR Register
#define UART_UA0_MSR_OFS                         0x00000018
// DCTS bitfiled (RO) Reset=0
#define UART_UA0_MSR_DCTS_MASK                   0x1
#define UART_UA0_MSR_DCTS_SHIFT                  0 
#define UART_UA0_MSR_DCTS_BIT                    0x1
#define UART_UA0_MSR_DCTS_BITWIDTH               1
// DDSR bitfiled (RO) Reset=0
#define UART_UA0_MSR_DDSR_MASK                   0x2
#define UART_UA0_MSR_DDSR_SHIFT                  1 
#define UART_UA0_MSR_DDSR_BIT                    0x1
#define UART_UA0_MSR_DDSR_BITWIDTH               1
// TERI bitfiled (RO) Reset=0
#define UART_UA0_MSR_TERI_MASK                   0x4
#define UART_UA0_MSR_TERI_SHIFT                  2 
#define UART_UA0_MSR_TERI_BIT                    0x1
#define UART_UA0_MSR_TERI_BITWIDTH               1
// DDCD bitfiled (RO) Reset=0
#define UART_UA0_MSR_DDCD_MASK                   0x8
#define UART_UA0_MSR_DDCD_SHIFT                  3 
#define UART_UA0_MSR_DDCD_BIT                    0x1
#define UART_UA0_MSR_DDCD_BITWIDTH               1
// CTS bitfiled (RO) Reset=0
#define UART_UA0_MSR_CTS_MASK                    0x10
#define UART_UA0_MSR_CTS_SHIFT                   4 
#define UART_UA0_MSR_CTS_BIT                     0x1
#define UART_UA0_MSR_CTS_BITWIDTH                1
// DSR bitfiled (RO) Reset=0
#define UART_UA0_MSR_DSR_MASK                    0x20
#define UART_UA0_MSR_DSR_SHIFT                   5 
#define UART_UA0_MSR_DSR_BIT                     0x1
#define UART_UA0_MSR_DSR_BITWIDTH                1
// RI bitfiled (RO) Reset=0
#define UART_UA0_MSR_RI_MASK                     0x40
#define UART_UA0_MSR_RI_SHIFT                    6 
#define UART_UA0_MSR_RI_BIT                      0x1
#define UART_UA0_MSR_RI_BITWIDTH                 1
// DCD bitfiled (RO) Reset=0
#define UART_UA0_MSR_DCD_MASK                    0x80
#define UART_UA0_MSR_DCD_SHIFT                   7 
#define UART_UA0_MSR_DCD_BIT                     0x1
#define UART_UA0_MSR_DCD_BITWIDTH                1
// reserved bitfiled (RO) Reset=0
#define UART_UA0_MSR_RESERVED_MASK               0xFFFFFF00
#define UART_UA0_MSR_RESERVED_SHIFT              8 
#define UART_UA0_MSR_RESERVED_BIT                0xFFFFFF
#define UART_UA0_MSR_RESERVED_BITWIDTH           24
// UA0_SCR Register
#define UART_UA0_SCR_OFS                         0x0000001C
// SCR bitfiled (RW) Reset=0
#define UART_UA0_SCR_SCR_MASK                    0xFF
#define UART_UA0_SCR_SCR_SHIFT                   0 
#define UART_UA0_SCR_SCR_BIT                     0xFF
#define UART_UA0_SCR_SCR_BITWIDTH                8
// reserved bitfiled (RO) Reset=0
#define UART_UA0_SCR_RESERVED_MASK               0xFFFFFF00
#define UART_UA0_SCR_RESERVED_SHIFT              8 
#define UART_UA0_SCR_RESERVED_BIT                0xFFFFFF
#define UART_UA0_SCR_RESERVED_BITWIDTH           24
// UA0_FAR Register
#define UART_UA0_FAR_OFS                         0x00000070
// FAR bitfiled (RW) Reset=0
#define UART_UA0_FAR_FAR_MASK                    0x1
#define UART_UA0_FAR_FAR_SHIFT                   0 
#define UART_UA0_FAR_FAR_BIT                     0x1
#define UART_UA0_FAR_FAR_BITWIDTH                1
// reserved bitfiled (RO) Reset=0
#define UART_UA0_FAR_RESERVED_MASK               0xFFFFFFFE
#define UART_UA0_FAR_RESERVED_SHIFT              1 
#define UART_UA0_FAR_RESERVED_BIT                0x7FFFFFFF
#define UART_UA0_FAR_RESERVED_BITWIDTH           31
// UA0_TFR Register
#define UART_UA0_TFR_OFS                         0x00000074
// TFR bitfiled (RO) Reset=0
#define UART_UA0_TFR_TFR_MASK                    0xFF
#define UART_UA0_TFR_TFR_SHIFT                   0 
#define UART_UA0_TFR_TFR_BIT                     0xFF
#define UART_UA0_TFR_TFR_BITWIDTH                8
// reserved bitfiled (RO) Reset=0
#define UART_UA0_TFR_RESERVED_MASK               0xFFFFFF00
#define UART_UA0_TFR_RESERVED_SHIFT              8 
#define UART_UA0_TFR_RESERVED_BIT                0xFFFFFF
#define UART_UA0_TFR_RESERVED_BITWIDTH           24
// UA0_RFW Register
#define UART_UA0_RFW_OFS                         0x00000078
// RFWD bitfiled (RW) Reset=0
#define UART_UA0_RFW_RFWD_MASK                   0xFF
#define UART_UA0_RFW_RFWD_SHIFT                  0 
#define UART_UA0_RFW_RFWD_BIT                    0xFF
#define UART_UA0_RFW_RFWD_BITWIDTH               8
// RFPE bitfiled (RW) Reset=0
#define UART_UA0_RFW_RFPE_MASK                   0x100
#define UART_UA0_RFW_RFPE_SHIFT                  8 
#define UART_UA0_RFW_RFPE_BIT                    0x1
#define UART_UA0_RFW_RFPE_BITWIDTH               1
// RFFE bitfiled (RW) Reset=0
#define UART_UA0_RFW_RFFE_MASK                   0x200
#define UART_UA0_RFW_RFFE_SHIFT                  9 
#define UART_UA0_RFW_RFFE_BIT                    0x1
#define UART_UA0_RFW_RFFE_BITWIDTH               1
// reserved bitfiled (RO) Reset=0
#define UART_UA0_RFW_RESERVED_MASK               0xFFFFFC00
#define UART_UA0_RFW_RESERVED_SHIFT              10 
#define UART_UA0_RFW_RESERVED_BIT                0x3FFFFF
#define UART_UA0_RFW_RESERVED_BITWIDTH           22
// UA0_USR Register
#define UART_UA0_USR_OFS                         0x0000007C
// BUSY bitfiled (RO) Reset=0
#define UART_UA0_USR_BUSY_MASK                   0x1
#define UART_UA0_USR_BUSY_SHIFT                  0 
#define UART_UA0_USR_BUSY_BIT                    0x1
#define UART_UA0_USR_BUSY_BITWIDTH               1
// TFNF bitfiled (RO) Reset=1
#define UART_UA0_USR_TFNF_MASK                   0x2
#define UART_UA0_USR_TFNF_SHIFT                  1 
#define UART_UA0_USR_TFNF_BIT                    0x1
#define UART_UA0_USR_TFNF_BITWIDTH               1
// TFE bitfiled (RO) Reset=1
#define UART_UA0_USR_TFE_MASK                    0x4
#define UART_UA0_USR_TFE_SHIFT                   2 
#define UART_UA0_USR_TFE_BIT                     0x1
#define UART_UA0_USR_TFE_BITWIDTH                1
// RFNE bitfiled (RO) Reset=0
#define UART_UA0_USR_RFNE_MASK                   0x8
#define UART_UA0_USR_RFNE_SHIFT                  3 
#define UART_UA0_USR_RFNE_BIT                    0x1
#define UART_UA0_USR_RFNE_BITWIDTH               1
// RFF bitfiled (RO) Reset=0
#define UART_UA0_USR_RFF_MASK                    0x10
#define UART_UA0_USR_RFF_SHIFT                   4 
#define UART_UA0_USR_RFF_BIT                     0x1
#define UART_UA0_USR_RFF_BITWIDTH                1
// reserved bitfiled (RO) Reset=0
#define UART_UA0_USR_RESERVED_MASK               0xFFFFFFE0
#define UART_UA0_USR_RESERVED_SHIFT              5 
#define UART_UA0_USR_RESERVED_BIT                0x7FFFFFF
#define UART_UA0_USR_RESERVED_BITWIDTH           27
// UA0_TFL Register
#define UART_UA0_TFL_OFS                         0x00000080
// TFL bitfiled (RO) Reset=0
#define UART_UA0_TFL_TFL_MASK                    0x1F
#define UART_UA0_TFL_TFL_SHIFT                   0 
#define UART_UA0_TFL_TFL_BIT                     0x1F
#define UART_UA0_TFL_TFL_BITWIDTH                5
// reserved bitfiled (RO) Reset=0
#define UART_UA0_TFL_RESERVED_MASK               0xFFFFFFE0
#define UART_UA0_TFL_RESERVED_SHIFT              5 
#define UART_UA0_TFL_RESERVED_BIT                0x7FFFFFF
#define UART_UA0_TFL_RESERVED_BITWIDTH           27
// UA0_RFL Register
#define UART_UA0_RFL_OFS                         0x00000084
// RFL bitfiled (RO) Reset=0
#define UART_UA0_RFL_RFL_MASK                    0x1F
#define UART_UA0_RFL_RFL_SHIFT                   0 
#define UART_UA0_RFL_RFL_BIT                     0x1F
#define UART_UA0_RFL_RFL_BITWIDTH                5
// reserved bitfiled (RO) Reset=0
#define UART_UA0_RFL_RESERVED_MASK               0xFFFFFFE0
#define UART_UA0_RFL_RESERVED_SHIFT              5 
#define UART_UA0_RFL_RESERVED_BIT                0x7FFFFFF
#define UART_UA0_RFL_RESERVED_BITWIDTH           27
// UA0_HTX Register
#define UART_UA0_HTX_OFS                         0x000000A4
// HTX bitfiled (RW) Reset=0
#define UART_UA0_HTX_HTX_MASK                    0x1
#define UART_UA0_HTX_HTX_SHIFT                   0 
#define UART_UA0_HTX_HTX_BIT                     0x1
#define UART_UA0_HTX_HTX_BITWIDTH                1
// reserved bitfiled (RO) Reset=0
#define UART_UA0_HTX_RESERVED_MASK               0xFFFFFFFE
#define UART_UA0_HTX_RESERVED_SHIFT              1 
#define UART_UA0_HTX_RESERVED_BIT                0x7FFFFFFF
#define UART_UA0_HTX_RESERVED_BITWIDTH           31
// UA0_DMASA Register
#define UART_UA0_DMASA_OFS                       0x000000A8
// DMASA bitfiled (RW) Reset=0
#define UART_UA0_DMASA_DMASA_MASK                0x1
#define UART_UA0_DMASA_DMASA_SHIFT               0 
#define UART_UA0_DMASA_DMASA_BIT                 0x1
#define UART_UA0_DMASA_DMASA_BITWIDTH            1
// reserved bitfiled (RO) Reset=0
#define UART_UA0_DMASA_RESERVED_MASK             0xFFFFFFFE
#define UART_UA0_DMASA_RESERVED_SHIFT            1 
#define UART_UA0_DMASA_RESERVED_BIT              0x7FFFFFFF
#define UART_UA0_DMASA_RESERVED_BITWIDTH         31
// UA0_CPR Register
#define UART_UA0_CPR_OFS                         0x000000F4
// APB_DATA_WIDTH bitfiled (RO) Reset=10
#define UART_UA0_CPR_APB_DATA_WIDTH_MASK         0x3
#define UART_UA0_CPR_APB_DATA_WIDTH_SHIFT        0 
#define UART_UA0_CPR_APB_DATA_WIDTH_BIT          0x3
#define UART_UA0_CPR_APB_DATA_WIDTH_BITWIDTH     2
// reserved3 bitfiled (RO) Reset=0
#define UART_UA0_CPR_RESERVED3_MASK              0xC
#define UART_UA0_CPR_RESERVED3_SHIFT             2 
#define UART_UA0_CPR_RESERVED3_BIT               0x3
#define UART_UA0_CPR_RESERVED3_BITWIDTH          2
// AFCE_MODE bitfiled (RO) Reset=1
#define UART_UA0_CPR_AFCE_MODE_MASK              0x10
#define UART_UA0_CPR_AFCE_MODE_SHIFT             4 
#define UART_UA0_CPR_AFCE_MODE_BIT               0x1
#define UART_UA0_CPR_AFCE_MODE_BITWIDTH          1
// THRE_MODE bitfiled (RO) Reset=1
#define UART_UA0_CPR_THRE_MODE_MASK              0x20
#define UART_UA0_CPR_THRE_MODE_SHIFT             5 
#define UART_UA0_CPR_THRE_MODE_BIT               0x1
#define UART_UA0_CPR_THRE_MODE_BITWIDTH          1
// SIR_MODE bitfiled (RO) Reset=0
#define UART_UA0_CPR_SIR_MODE_MASK               0x40
#define UART_UA0_CPR_SIR_MODE_SHIFT              6 
#define UART_UA0_CPR_SIR_MODE_BIT                0x1
#define UART_UA0_CPR_SIR_MODE_BITWIDTH           1
// SIR_LP_MODE bitfiled (RO) Reset=0
#define UART_UA0_CPR_SIR_LP_MODE_MASK            0x80
#define UART_UA0_CPR_SIR_LP_MODE_SHIFT           7 
#define UART_UA0_CPR_SIR_LP_MODE_BIT             0x1
#define UART_UA0_CPR_SIR_LP_MODE_BITWIDTH        1
// ADDITIONAL_FEAT bitfiled (RO) Reset=1
#define UART_UA0_CPR_ADDITIONAL_FEAT_MASK        0x100
#define UART_UA0_CPR_ADDITIONAL_FEAT_SHIFT       8 
#define UART_UA0_CPR_ADDITIONAL_FEAT_BIT         0x1
#define UART_UA0_CPR_ADDITIONAL_FEAT_BITWIDTH    1
// FIFO_ACCESS bitfiled (RO) Reset=1
#define UART_UA0_CPR_FIFO_ACCESS_MASK            0x200
#define UART_UA0_CPR_FIFO_ACCESS_SHIFT           9 
#define UART_UA0_CPR_FIFO_ACCESS_BIT             0x1
#define UART_UA0_CPR_FIFO_ACCESS_BITWIDTH        1
// FIFO_STAT bitfiled (RO) Reset=1
#define UART_UA0_CPR_FIFO_STAT_MASK              0x400
#define UART_UA0_CPR_FIFO_STAT_SHIFT             10 
#define UART_UA0_CPR_FIFO_STAT_BIT               0x1
#define UART_UA0_CPR_FIFO_STAT_BITWIDTH          1
// SHADOW bitfiled (RO) Reset=0
#define UART_UA0_CPR_SHADOW_MASK                 0x800
#define UART_UA0_CPR_SHADOW_SHIFT                11 
#define UART_UA0_CPR_SHADOW_BIT                  0x1
#define UART_UA0_CPR_SHADOW_BITWIDTH             1
// UART_ADD_ENCODED_PARAMS bitfiled (RO) Reset=1
#define UART_UA0_CPR_UART_ADD_ENCODED_PARAMS_MASK 0x1000
#define UART_UA0_CPR_UART_ADD_ENCODED_PARAMS_SHIFT 12 
#define UART_UA0_CPR_UART_ADD_ENCODED_PARAMS_BIT 0x1
#define UART_UA0_CPR_UART_ADD_ENCODED_PARAMS_BITWIDTH 1
// DMA_EXTRA bitfiled (RO) Reset=1
#define UART_UA0_CPR_DMA_EXTRA_MASK              0x2000
#define UART_UA0_CPR_DMA_EXTRA_SHIFT             13 
#define UART_UA0_CPR_DMA_EXTRA_BIT               0x1
#define UART_UA0_CPR_DMA_EXTRA_BITWIDTH          1
// reserved2 bitfiled (RO) Reset=0
#define UART_UA0_CPR_RESERVED2_MASK              0xC000
#define UART_UA0_CPR_RESERVED2_SHIFT             14 
#define UART_UA0_CPR_RESERVED2_BIT               0x3
#define UART_UA0_CPR_RESERVED2_BITWIDTH          2
// FIFO_MODE bitfiled (RO) Reset=1
#define UART_UA0_CPR_FIFO_MODE_MASK              0xFF0000
#define UART_UA0_CPR_FIFO_MODE_SHIFT             16 
#define UART_UA0_CPR_FIFO_MODE_BIT               0xFF
#define UART_UA0_CPR_FIFO_MODE_BITWIDTH          8
// reserved bitfiled (RO) Reset=0
#define UART_UA0_CPR_RESERVED_MASK               0xFF000000
#define UART_UA0_CPR_RESERVED_SHIFT              24 
#define UART_UA0_CPR_RESERVED_BIT                0xFF
#define UART_UA0_CPR_RESERVED_BITWIDTH           8
// UA0_UCV Register
#define UART_UA0_UCV_OFS                         0x000000F8
// UART_Component_Version bitfiled (RO) Reset=110011001100010011010000101010
#define UART_UA0_UCV_UART_COMPONENT_VERSION_MASK 0xFFFFFFFF
#define UART_UA0_UCV_UART_COMPONENT_VERSION_SHIFT 0 
#define UART_UA0_UCV_UART_COMPONENT_VERSION_BIT  0xFFFFFFFF
#define UART_UA0_UCV_UART_COMPONENT_VERSION_BITWIDTH 32
// UA0_CTR Register
#define UART_UA0_CTR_OFS                         0x000000FC
// Peripheral_ID bitfiled (RO) Reset=1000100010101110000000100010000
#define UART_UA0_CTR_PERIPHERAL_ID_MASK          0xFFFFFFFF
#define UART_UA0_CTR_PERIPHERAL_ID_SHIFT         0 
#define UART_UA0_CTR_PERIPHERAL_ID_BIT           0xFFFFFFFF
#define UART_UA0_CTR_PERIPHERAL_ID_BITWIDTH      32
// UA1_RBR_THR_DLL Register
#define UART_UA1_RBR_THR_DLL_OFS                 0x00001000
// RBR_THR_DLL bitfiled (RW) Reset=0
#define UART_UA1_RBR_THR_DLL_RBR_THR_DLL_MASK    0xFF
#define UART_UA1_RBR_THR_DLL_RBR_THR_DLL_SHIFT   0 
#define UART_UA1_RBR_THR_DLL_RBR_THR_DLL_BIT     0xFF
#define UART_UA1_RBR_THR_DLL_RBR_THR_DLL_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define UART_UA1_RBR_THR_DLL_RESERVED_MASK       0xFFFFFF00
#define UART_UA1_RBR_THR_DLL_RESERVED_SHIFT      8 
#define UART_UA1_RBR_THR_DLL_RESERVED_BIT        0xFFFFFF
#define UART_UA1_RBR_THR_DLL_RESERVED_BITWIDTH   24
// UA1_IER_DLH Register
#define UART_UA1_IER_DLH_OFS                     0x00001004
// ERBFI_DLH0 bitfiled (RW) Reset=0
#define UART_UA1_IER_DLH_ERBFI_DLH0_MASK         0x1
#define UART_UA1_IER_DLH_ERBFI_DLH0_SHIFT        0 
#define UART_UA1_IER_DLH_ERBFI_DLH0_BIT          0x1
#define UART_UA1_IER_DLH_ERBFI_DLH0_BITWIDTH     1
// ETBEI_DLH1 bitfiled (RW) Reset=0
#define UART_UA1_IER_DLH_ETBEI_DLH1_MASK         0x2
#define UART_UA1_IER_DLH_ETBEI_DLH1_SHIFT        1 
#define UART_UA1_IER_DLH_ETBEI_DLH1_BIT          0x1
#define UART_UA1_IER_DLH_ETBEI_DLH1_BITWIDTH     1
// ELSI_DLH2 bitfiled (RW) Reset=0
#define UART_UA1_IER_DLH_ELSI_DLH2_MASK          0x4
#define UART_UA1_IER_DLH_ELSI_DLH2_SHIFT         2 
#define UART_UA1_IER_DLH_ELSI_DLH2_BIT           0x1
#define UART_UA1_IER_DLH_ELSI_DLH2_BITWIDTH      1
// EDSSI_DLH3 bitfiled (RW) Reset=0
#define UART_UA1_IER_DLH_EDSSI_DLH3_MASK         0x8
#define UART_UA1_IER_DLH_EDSSI_DLH3_SHIFT        3 
#define UART_UA1_IER_DLH_EDSSI_DLH3_BIT          0x1
#define UART_UA1_IER_DLH_EDSSI_DLH3_BITWIDTH     1
// DLH64 bitfiled (RW) Reset=0
#define UART_UA1_IER_DLH_DLH64_MASK              0x70
#define UART_UA1_IER_DLH_DLH64_SHIFT             4 
#define UART_UA1_IER_DLH_DLH64_BIT               0x7
#define UART_UA1_IER_DLH_DLH64_BITWIDTH          3
// PTIME_DLH7 bitfiled (RW) Reset=0
#define UART_UA1_IER_DLH_PTIME_DLH7_MASK         0x80
#define UART_UA1_IER_DLH_PTIME_DLH7_SHIFT        7 
#define UART_UA1_IER_DLH_PTIME_DLH7_BIT          0x1
#define UART_UA1_IER_DLH_PTIME_DLH7_BITWIDTH     1
// reserved bitfiled (RO) Reset=0
#define UART_UA1_IER_DLH_RESERVED_MASK           0xFFFFFF00
#define UART_UA1_IER_DLH_RESERVED_SHIFT          8 
#define UART_UA1_IER_DLH_RESERVED_BIT            0xFFFFFF
#define UART_UA1_IER_DLH_RESERVED_BITWIDTH       24
// UA1_FCR_IIR Register
#define UART_UA1_FCR_IIR_OFS                     0x00001008
// IID0_FIFOE bitfiled (RW) Reset=1
#define UART_UA1_FCR_IIR_IID0_FIFOE_MASK         0x1
#define UART_UA1_FCR_IIR_IID0_FIFOE_SHIFT        0 
#define UART_UA1_FCR_IIR_IID0_FIFOE_BIT          0x1
#define UART_UA1_FCR_IIR_IID0_FIFOE_BITWIDTH     1
// IID1_RFIFOR bitfiled (RW) Reset=0
#define UART_UA1_FCR_IIR_IID1_RFIFOR_MASK        0x2
#define UART_UA1_FCR_IIR_IID1_RFIFOR_SHIFT       1 
#define UART_UA1_FCR_IIR_IID1_RFIFOR_BIT         0x1
#define UART_UA1_FCR_IIR_IID1_RFIFOR_BITWIDTH    1
// IID2_XFIFOR bitfiled (RW) Reset=0
#define UART_UA1_FCR_IIR_IID2_XFIFOR_MASK        0x4
#define UART_UA1_FCR_IIR_IID2_XFIFOR_SHIFT       2 
#define UART_UA1_FCR_IIR_IID2_XFIFOR_BIT         0x1
#define UART_UA1_FCR_IIR_IID2_XFIFOR_BITWIDTH    1
// IID3_DMAM bitfiled (RW) Reset=0
#define UART_UA1_FCR_IIR_IID3_DMAM_MASK          0x8
#define UART_UA1_FCR_IIR_IID3_DMAM_SHIFT         3 
#define UART_UA1_FCR_IIR_IID3_DMAM_BIT           0x1
#define UART_UA1_FCR_IIR_IID3_DMAM_BITWIDTH      1
// TET bitfiled (RW) Reset=0
#define UART_UA1_FCR_IIR_TET_MASK                0x30
#define UART_UA1_FCR_IIR_TET_SHIFT               4 
#define UART_UA1_FCR_IIR_TET_BIT                 0x3
#define UART_UA1_FCR_IIR_TET_BITWIDTH            2
// FIFOSE_RCVR bitfiled (RW) Reset=0
#define UART_UA1_FCR_IIR_FIFOSE_RCVR_MASK        0xC0
#define UART_UA1_FCR_IIR_FIFOSE_RCVR_SHIFT       6 
#define UART_UA1_FCR_IIR_FIFOSE_RCVR_BIT         0x3
#define UART_UA1_FCR_IIR_FIFOSE_RCVR_BITWIDTH    2
// reserved bitfiled (RO) Reset=0
#define UART_UA1_FCR_IIR_RESERVED_MASK           0xFFFFFF00
#define UART_UA1_FCR_IIR_RESERVED_SHIFT          8 
#define UART_UA1_FCR_IIR_RESERVED_BIT            0xFFFFFF
#define UART_UA1_FCR_IIR_RESERVED_BITWIDTH       24
// UA1_LCR Register
#define UART_UA1_LCR_OFS                         0x0000100C
// DLS bitfiled (RW) Reset=0
#define UART_UA1_LCR_DLS_MASK                    0x3
#define UART_UA1_LCR_DLS_SHIFT                   0 
#define UART_UA1_LCR_DLS_BIT                     0x3
#define UART_UA1_LCR_DLS_BITWIDTH                2
// STOP bitfiled (RW) Reset=0
#define UART_UA1_LCR_STOP_MASK                   0x4
#define UART_UA1_LCR_STOP_SHIFT                  2 
#define UART_UA1_LCR_STOP_BIT                    0x1
#define UART_UA1_LCR_STOP_BITWIDTH               1
// PEN bitfiled (RW) Reset=0
#define UART_UA1_LCR_PEN_MASK                    0x8
#define UART_UA1_LCR_PEN_SHIFT                   3 
#define UART_UA1_LCR_PEN_BIT                     0x1
#define UART_UA1_LCR_PEN_BITWIDTH                1
// EPS bitfiled (RW) Reset=0
#define UART_UA1_LCR_EPS_MASK                    0x10
#define UART_UA1_LCR_EPS_SHIFT                   4 
#define UART_UA1_LCR_EPS_BIT                     0x1
#define UART_UA1_LCR_EPS_BITWIDTH                1
// SP bitfiled (RW) Reset=0
#define UART_UA1_LCR_SP_MASK                     0x20
#define UART_UA1_LCR_SP_SHIFT                    5 
#define UART_UA1_LCR_SP_BIT                      0x1
#define UART_UA1_LCR_SP_BITWIDTH                 1
// Break bitfiled (RW) Reset=0
#define UART_UA1_LCR_BREAK_MASK                  0x40
#define UART_UA1_LCR_BREAK_SHIFT                 6 
#define UART_UA1_LCR_BREAK_BIT                   0x1
#define UART_UA1_LCR_BREAK_BITWIDTH              1
// DLAB bitfiled (RW) Reset=0
#define UART_UA1_LCR_DLAB_MASK                   0x80
#define UART_UA1_LCR_DLAB_SHIFT                  7 
#define UART_UA1_LCR_DLAB_BIT                    0x1
#define UART_UA1_LCR_DLAB_BITWIDTH               1
// reserved bitfiled (RO) Reset=0
#define UART_UA1_LCR_RESERVED_MASK               0xFFFFFF00
#define UART_UA1_LCR_RESERVED_SHIFT              8 
#define UART_UA1_LCR_RESERVED_BIT                0xFFFFFF
#define UART_UA1_LCR_RESERVED_BITWIDTH           24
// UA1_MCR Register
#define UART_UA1_MCR_OFS                         0x00001010
// DTR bitfiled (RW) Reset=0
#define UART_UA1_MCR_DTR_MASK                    0x1
#define UART_UA1_MCR_DTR_SHIFT                   0 
#define UART_UA1_MCR_DTR_BIT                     0x1
#define UART_UA1_MCR_DTR_BITWIDTH                1
// RTS bitfiled (RW) Reset=0
#define UART_UA1_MCR_RTS_MASK                    0x2
#define UART_UA1_MCR_RTS_SHIFT                   1 
#define UART_UA1_MCR_RTS_BIT                     0x1
#define UART_UA1_MCR_RTS_BITWIDTH                1
// OUT1 bitfiled (RW) Reset=0
#define UART_UA1_MCR_OUT1_MASK                   0x4
#define UART_UA1_MCR_OUT1_SHIFT                  2 
#define UART_UA1_MCR_OUT1_BIT                    0x1
#define UART_UA1_MCR_OUT1_BITWIDTH               1
// OUT2 bitfiled (RW) Reset=0
#define UART_UA1_MCR_OUT2_MASK                   0x8
#define UART_UA1_MCR_OUT2_SHIFT                  3 
#define UART_UA1_MCR_OUT2_BIT                    0x1
#define UART_UA1_MCR_OUT2_BITWIDTH               1
// LoopBack bitfiled (RW) Reset=0
#define UART_UA1_MCR_LOOPBACK_MASK               0x10
#define UART_UA1_MCR_LOOPBACK_SHIFT              4 
#define UART_UA1_MCR_LOOPBACK_BIT                0x1
#define UART_UA1_MCR_LOOPBACK_BITWIDTH           1
// AFCE bitfiled (RW) Reset=0
#define UART_UA1_MCR_AFCE_MASK                   0x20
#define UART_UA1_MCR_AFCE_SHIFT                  5 
#define UART_UA1_MCR_AFCE_BIT                    0x1
#define UART_UA1_MCR_AFCE_BITWIDTH               1
// SIRE bitfiled (RW) Reset=0
#define UART_UA1_MCR_SIRE_MASK                   0x40
#define UART_UA1_MCR_SIRE_SHIFT                  6 
#define UART_UA1_MCR_SIRE_BIT                    0x1
#define UART_UA1_MCR_SIRE_BITWIDTH               1
// reserved bitfiled (RO) Reset=0
#define UART_UA1_MCR_RESERVED_MASK               0xFFFFFF80
#define UART_UA1_MCR_RESERVED_SHIFT              7 
#define UART_UA1_MCR_RESERVED_BIT                0x1FFFFFF
#define UART_UA1_MCR_RESERVED_BITWIDTH           25
// UA1_LSR Register
#define UART_UA1_LSR_OFS                         0x00001014
// DR bitfiled (RO) Reset=0
#define UART_UA1_LSR_DR_MASK                     0x1
#define UART_UA1_LSR_DR_SHIFT                    0 
#define UART_UA1_LSR_DR_BIT                      0x1
#define UART_UA1_LSR_DR_BITWIDTH                 1
// OE bitfiled (RO) Reset=0
#define UART_UA1_LSR_OE_MASK                     0x2
#define UART_UA1_LSR_OE_SHIFT                    1 
#define UART_UA1_LSR_OE_BIT                      0x1
#define UART_UA1_LSR_OE_BITWIDTH                 1
// PE bitfiled (RO) Reset=0
#define UART_UA1_LSR_PE_MASK                     0x4
#define UART_UA1_LSR_PE_SHIFT                    2 
#define UART_UA1_LSR_PE_BIT                      0x1
#define UART_UA1_LSR_PE_BITWIDTH                 1
// FE bitfiled (RO) Reset=0
#define UART_UA1_LSR_FE_MASK                     0x8
#define UART_UA1_LSR_FE_SHIFT                    3 
#define UART_UA1_LSR_FE_BIT                      0x1
#define UART_UA1_LSR_FE_BITWIDTH                 1
// BI bitfiled (RO) Reset=0
#define UART_UA1_LSR_BI_MASK                     0x10
#define UART_UA1_LSR_BI_SHIFT                    4 
#define UART_UA1_LSR_BI_BIT                      0x1
#define UART_UA1_LSR_BI_BITWIDTH                 1
// THRE bitfiled (RO) Reset=1
#define UART_UA1_LSR_THRE_MASK                   0x20
#define UART_UA1_LSR_THRE_SHIFT                  5 
#define UART_UA1_LSR_THRE_BIT                    0x1
#define UART_UA1_LSR_THRE_BITWIDTH               1
// TEMT bitfiled (RO) Reset=1
#define UART_UA1_LSR_TEMT_MASK                   0x40
#define UART_UA1_LSR_TEMT_SHIFT                  6 
#define UART_UA1_LSR_TEMT_BIT                    0x1
#define UART_UA1_LSR_TEMT_BITWIDTH               1
// RFE bitfiled (RO) Reset=0
#define UART_UA1_LSR_RFE_MASK                    0x80
#define UART_UA1_LSR_RFE_SHIFT                   7 
#define UART_UA1_LSR_RFE_BIT                     0x1
#define UART_UA1_LSR_RFE_BITWIDTH                1
// reserved bitfiled (RO) Reset=0
#define UART_UA1_LSR_RESERVED_MASK               0xFFFFFF00
#define UART_UA1_LSR_RESERVED_SHIFT              8 
#define UART_UA1_LSR_RESERVED_BIT                0xFFFFFF
#define UART_UA1_LSR_RESERVED_BITWIDTH           24
// UA1_MSR Register
#define UART_UA1_MSR_OFS                         0x00001018
// DCTS bitfiled (RO) Reset=0
#define UART_UA1_MSR_DCTS_MASK                   0x1
#define UART_UA1_MSR_DCTS_SHIFT                  0 
#define UART_UA1_MSR_DCTS_BIT                    0x1
#define UART_UA1_MSR_DCTS_BITWIDTH               1
// DDSR bitfiled (RO) Reset=0
#define UART_UA1_MSR_DDSR_MASK                   0x2
#define UART_UA1_MSR_DDSR_SHIFT                  1 
#define UART_UA1_MSR_DDSR_BIT                    0x1
#define UART_UA1_MSR_DDSR_BITWIDTH               1
// TERI bitfiled (RO) Reset=0
#define UART_UA1_MSR_TERI_MASK                   0x4
#define UART_UA1_MSR_TERI_SHIFT                  2 
#define UART_UA1_MSR_TERI_BIT                    0x1
#define UART_UA1_MSR_TERI_BITWIDTH               1
// DDCD bitfiled (RO) Reset=0
#define UART_UA1_MSR_DDCD_MASK                   0x8
#define UART_UA1_MSR_DDCD_SHIFT                  3 
#define UART_UA1_MSR_DDCD_BIT                    0x1
#define UART_UA1_MSR_DDCD_BITWIDTH               1
// CTS bitfiled (RO) Reset=0
#define UART_UA1_MSR_CTS_MASK                    0x10
#define UART_UA1_MSR_CTS_SHIFT                   4 
#define UART_UA1_MSR_CTS_BIT                     0x1
#define UART_UA1_MSR_CTS_BITWIDTH                1
// DSR bitfiled (RO) Reset=0
#define UART_UA1_MSR_DSR_MASK                    0x20
#define UART_UA1_MSR_DSR_SHIFT                   5 
#define UART_UA1_MSR_DSR_BIT                     0x1
#define UART_UA1_MSR_DSR_BITWIDTH                1
// RI bitfiled (RO) Reset=0
#define UART_UA1_MSR_RI_MASK                     0x40
#define UART_UA1_MSR_RI_SHIFT                    6 
#define UART_UA1_MSR_RI_BIT                      0x1
#define UART_UA1_MSR_RI_BITWIDTH                 1
// DCD bitfiled (RO) Reset=0
#define UART_UA1_MSR_DCD_MASK                    0x80
#define UART_UA1_MSR_DCD_SHIFT                   7 
#define UART_UA1_MSR_DCD_BIT                     0x1
#define UART_UA1_MSR_DCD_BITWIDTH                1
// reserved bitfiled (RO) Reset=0
#define UART_UA1_MSR_RESERVED_MASK               0xFFFFFF00
#define UART_UA1_MSR_RESERVED_SHIFT              8 
#define UART_UA1_MSR_RESERVED_BIT                0xFFFFFF
#define UART_UA1_MSR_RESERVED_BITWIDTH           24
// UA1_SCR Register
#define UART_UA1_SCR_OFS                         0x0000101C
// SCR bitfiled (RW) Reset=0
#define UART_UA1_SCR_SCR_MASK                    0xFF
#define UART_UA1_SCR_SCR_SHIFT                   0 
#define UART_UA1_SCR_SCR_BIT                     0xFF
#define UART_UA1_SCR_SCR_BITWIDTH                8
// reserved bitfiled (RO) Reset=0
#define UART_UA1_SCR_RESERVED_MASK               0xFFFFFF00
#define UART_UA1_SCR_RESERVED_SHIFT              8 
#define UART_UA1_SCR_RESERVED_BIT                0xFFFFFF
#define UART_UA1_SCR_RESERVED_BITWIDTH           24
// UA1_FAR Register
#define UART_UA1_FAR_OFS                         0x00001070
// FAR bitfiled (RW) Reset=0
#define UART_UA1_FAR_FAR_MASK                    0x1
#define UART_UA1_FAR_FAR_SHIFT                   0 
#define UART_UA1_FAR_FAR_BIT                     0x1
#define UART_UA1_FAR_FAR_BITWIDTH                1
// reserved bitfiled (RO) Reset=0
#define UART_UA1_FAR_RESERVED_MASK               0xFFFFFFFE
#define UART_UA1_FAR_RESERVED_SHIFT              1 
#define UART_UA1_FAR_RESERVED_BIT                0x7FFFFFFF
#define UART_UA1_FAR_RESERVED_BITWIDTH           31
// UA1_TFR Register
#define UART_UA1_TFR_OFS                         0x00001074
// TFR bitfiled (RO) Reset=0
#define UART_UA1_TFR_TFR_MASK                    0xFF
#define UART_UA1_TFR_TFR_SHIFT                   0 
#define UART_UA1_TFR_TFR_BIT                     0xFF
#define UART_UA1_TFR_TFR_BITWIDTH                8
// reserved bitfiled (RO) Reset=0
#define UART_UA1_TFR_RESERVED_MASK               0xFFFFFF00
#define UART_UA1_TFR_RESERVED_SHIFT              8 
#define UART_UA1_TFR_RESERVED_BIT                0xFFFFFF
#define UART_UA1_TFR_RESERVED_BITWIDTH           24
// UA1_RFW Register
#define UART_UA1_RFW_OFS                         0x00001078
// RFWD bitfiled (RW) Reset=0
#define UART_UA1_RFW_RFWD_MASK                   0xFF
#define UART_UA1_RFW_RFWD_SHIFT                  0 
#define UART_UA1_RFW_RFWD_BIT                    0xFF
#define UART_UA1_RFW_RFWD_BITWIDTH               8
// RFPE bitfiled (RW) Reset=0
#define UART_UA1_RFW_RFPE_MASK                   0x100
#define UART_UA1_RFW_RFPE_SHIFT                  8 
#define UART_UA1_RFW_RFPE_BIT                    0x1
#define UART_UA1_RFW_RFPE_BITWIDTH               1
// RFFE bitfiled (RW) Reset=0
#define UART_UA1_RFW_RFFE_MASK                   0x200
#define UART_UA1_RFW_RFFE_SHIFT                  9 
#define UART_UA1_RFW_RFFE_BIT                    0x1
#define UART_UA1_RFW_RFFE_BITWIDTH               1
// reserved bitfiled (RO) Reset=0
#define UART_UA1_RFW_RESERVED_MASK               0xFFFFFC00
#define UART_UA1_RFW_RESERVED_SHIFT              10 
#define UART_UA1_RFW_RESERVED_BIT                0x3FFFFF
#define UART_UA1_RFW_RESERVED_BITWIDTH           22
// UA1_USR Register
#define UART_UA1_USR_OFS                         0x0000107C
// BUSY bitfiled (RO) Reset=0
#define UART_UA1_USR_BUSY_MASK                   0x1
#define UART_UA1_USR_BUSY_SHIFT                  0 
#define UART_UA1_USR_BUSY_BIT                    0x1
#define UART_UA1_USR_BUSY_BITWIDTH               1
// TFNF bitfiled (RO) Reset=1
#define UART_UA1_USR_TFNF_MASK                   0x2
#define UART_UA1_USR_TFNF_SHIFT                  1 
#define UART_UA1_USR_TFNF_BIT                    0x1
#define UART_UA1_USR_TFNF_BITWIDTH               1
// TFE bitfiled (RO) Reset=1
#define UART_UA1_USR_TFE_MASK                    0x4
#define UART_UA1_USR_TFE_SHIFT                   2 
#define UART_UA1_USR_TFE_BIT                     0x1
#define UART_UA1_USR_TFE_BITWIDTH                1
// RFNE bitfiled (RO) Reset=0
#define UART_UA1_USR_RFNE_MASK                   0x8
#define UART_UA1_USR_RFNE_SHIFT                  3 
#define UART_UA1_USR_RFNE_BIT                    0x1
#define UART_UA1_USR_RFNE_BITWIDTH               1
// RFF bitfiled (RO) Reset=0
#define UART_UA1_USR_RFF_MASK                    0x10
#define UART_UA1_USR_RFF_SHIFT                   4 
#define UART_UA1_USR_RFF_BIT                     0x1
#define UART_UA1_USR_RFF_BITWIDTH                1
// reserved bitfiled (RO) Reset=0
#define UART_UA1_USR_RESERVED_MASK               0xFFFFFFE0
#define UART_UA1_USR_RESERVED_SHIFT              5 
#define UART_UA1_USR_RESERVED_BIT                0x7FFFFFF
#define UART_UA1_USR_RESERVED_BITWIDTH           27
// UA1_TFL Register
#define UART_UA1_TFL_OFS                         0x00001080
// TFL bitfiled (RO) Reset=0
#define UART_UA1_TFL_TFL_MASK                    0x1F
#define UART_UA1_TFL_TFL_SHIFT                   0 
#define UART_UA1_TFL_TFL_BIT                     0x1F
#define UART_UA1_TFL_TFL_BITWIDTH                5
// reserved bitfiled (RO) Reset=0
#define UART_UA1_TFL_RESERVED_MASK               0xFFFFFFE0
#define UART_UA1_TFL_RESERVED_SHIFT              5 
#define UART_UA1_TFL_RESERVED_BIT                0x7FFFFFF
#define UART_UA1_TFL_RESERVED_BITWIDTH           27
// UA1_RFL Register
#define UART_UA1_RFL_OFS                         0x00001084
// RFL bitfiled (RO) Reset=0
#define UART_UA1_RFL_RFL_MASK                    0x1F
#define UART_UA1_RFL_RFL_SHIFT                   0 
#define UART_UA1_RFL_RFL_BIT                     0x1F
#define UART_UA1_RFL_RFL_BITWIDTH                5
// reserved bitfiled (RO) Reset=0
#define UART_UA1_RFL_RESERVED_MASK               0xFFFFFFE0
#define UART_UA1_RFL_RESERVED_SHIFT              5 
#define UART_UA1_RFL_RESERVED_BIT                0x7FFFFFF
#define UART_UA1_RFL_RESERVED_BITWIDTH           27
// UA1_HTX Register
#define UART_UA1_HTX_OFS                         0x000010A4
// HTX bitfiled (RW) Reset=0
#define UART_UA1_HTX_HTX_MASK                    0x1
#define UART_UA1_HTX_HTX_SHIFT                   0 
#define UART_UA1_HTX_HTX_BIT                     0x1
#define UART_UA1_HTX_HTX_BITWIDTH                1
// reserved bitfiled (RO) Reset=0
#define UART_UA1_HTX_RESERVED_MASK               0xFFFFFFFE
#define UART_UA1_HTX_RESERVED_SHIFT              1 
#define UART_UA1_HTX_RESERVED_BIT                0x7FFFFFFF
#define UART_UA1_HTX_RESERVED_BITWIDTH           31
// UA1_DMASA Register
#define UART_UA1_DMASA_OFS                       0x000010A8
// DMASA bitfiled (RW) Reset=0
#define UART_UA1_DMASA_DMASA_MASK                0x1
#define UART_UA1_DMASA_DMASA_SHIFT               0 
#define UART_UA1_DMASA_DMASA_BIT                 0x1
#define UART_UA1_DMASA_DMASA_BITWIDTH            1
// reserved bitfiled (RO) Reset=0
#define UART_UA1_DMASA_RESERVED_MASK             0xFFFFFFFE
#define UART_UA1_DMASA_RESERVED_SHIFT            1 
#define UART_UA1_DMASA_RESERVED_BIT              0x7FFFFFFF
#define UART_UA1_DMASA_RESERVED_BITWIDTH         31
// UA1_CPR Register
#define UART_UA1_CPR_OFS                         0x000010F4
// APB_DATA_WIDTH bitfiled (RO) Reset=10
#define UART_UA1_CPR_APB_DATA_WIDTH_MASK         0x3
#define UART_UA1_CPR_APB_DATA_WIDTH_SHIFT        0 
#define UART_UA1_CPR_APB_DATA_WIDTH_BIT          0x3
#define UART_UA1_CPR_APB_DATA_WIDTH_BITWIDTH     2
// reserved3 bitfiled (RO) Reset=0
#define UART_UA1_CPR_RESERVED3_MASK              0xC
#define UART_UA1_CPR_RESERVED3_SHIFT             2 
#define UART_UA1_CPR_RESERVED3_BIT               0x3
#define UART_UA1_CPR_RESERVED3_BITWIDTH          2
// AFCE_MODE bitfiled (RO) Reset=1
#define UART_UA1_CPR_AFCE_MODE_MASK              0x10
#define UART_UA1_CPR_AFCE_MODE_SHIFT             4 
#define UART_UA1_CPR_AFCE_MODE_BIT               0x1
#define UART_UA1_CPR_AFCE_MODE_BITWIDTH          1
// THRE_MODE bitfiled (RO) Reset=1
#define UART_UA1_CPR_THRE_MODE_MASK              0x20
#define UART_UA1_CPR_THRE_MODE_SHIFT             5 
#define UART_UA1_CPR_THRE_MODE_BIT               0x1
#define UART_UA1_CPR_THRE_MODE_BITWIDTH          1
// SIR_MODE bitfiled (RO) Reset=0
#define UART_UA1_CPR_SIR_MODE_MASK               0x40
#define UART_UA1_CPR_SIR_MODE_SHIFT              6 
#define UART_UA1_CPR_SIR_MODE_BIT                0x1
#define UART_UA1_CPR_SIR_MODE_BITWIDTH           1
// SIR_LP_MODE bitfiled (RO) Reset=0
#define UART_UA1_CPR_SIR_LP_MODE_MASK            0x80
#define UART_UA1_CPR_SIR_LP_MODE_SHIFT           7 
#define UART_UA1_CPR_SIR_LP_MODE_BIT             0x1
#define UART_UA1_CPR_SIR_LP_MODE_BITWIDTH        1
// ADDITIONAL_FEAT bitfiled (RO) Reset=1
#define UART_UA1_CPR_ADDITIONAL_FEAT_MASK        0x100
#define UART_UA1_CPR_ADDITIONAL_FEAT_SHIFT       8 
#define UART_UA1_CPR_ADDITIONAL_FEAT_BIT         0x1
#define UART_UA1_CPR_ADDITIONAL_FEAT_BITWIDTH    1
// FIFO_ACCESS bitfiled (RO) Reset=1
#define UART_UA1_CPR_FIFO_ACCESS_MASK            0x200
#define UART_UA1_CPR_FIFO_ACCESS_SHIFT           9 
#define UART_UA1_CPR_FIFO_ACCESS_BIT             0x1
#define UART_UA1_CPR_FIFO_ACCESS_BITWIDTH        1
// FIFO_STAT bitfiled (RO) Reset=1
#define UART_UA1_CPR_FIFO_STAT_MASK              0x400
#define UART_UA1_CPR_FIFO_STAT_SHIFT             10 
#define UART_UA1_CPR_FIFO_STAT_BIT               0x1
#define UART_UA1_CPR_FIFO_STAT_BITWIDTH          1
// SHADOW bitfiled (RO) Reset=0
#define UART_UA1_CPR_SHADOW_MASK                 0x800
#define UART_UA1_CPR_SHADOW_SHIFT                11 
#define UART_UA1_CPR_SHADOW_BIT                  0x1
#define UART_UA1_CPR_SHADOW_BITWIDTH             1
// UART_ADD_ENCODED_PARAMS bitfiled (RO) Reset=1
#define UART_UA1_CPR_UART_ADD_ENCODED_PARAMS_MASK 0x1000
#define UART_UA1_CPR_UART_ADD_ENCODED_PARAMS_SHIFT 12 
#define UART_UA1_CPR_UART_ADD_ENCODED_PARAMS_BIT 0x1
#define UART_UA1_CPR_UART_ADD_ENCODED_PARAMS_BITWIDTH 1
// DMA_EXTRA bitfiled (RO) Reset=1
#define UART_UA1_CPR_DMA_EXTRA_MASK              0x2000
#define UART_UA1_CPR_DMA_EXTRA_SHIFT             13 
#define UART_UA1_CPR_DMA_EXTRA_BIT               0x1
#define UART_UA1_CPR_DMA_EXTRA_BITWIDTH          1
// reserved2 bitfiled (RO) Reset=0
#define UART_UA1_CPR_RESERVED2_MASK              0xC000
#define UART_UA1_CPR_RESERVED2_SHIFT             14 
#define UART_UA1_CPR_RESERVED2_BIT               0x3
#define UART_UA1_CPR_RESERVED2_BITWIDTH          2
// FIFO_MODE bitfiled (RO) Reset=1
#define UART_UA1_CPR_FIFO_MODE_MASK              0xFF0000
#define UART_UA1_CPR_FIFO_MODE_SHIFT             16 
#define UART_UA1_CPR_FIFO_MODE_BIT               0xFF
#define UART_UA1_CPR_FIFO_MODE_BITWIDTH          8
// reserved bitfiled (RO) Reset=0
#define UART_UA1_CPR_RESERVED_MASK               0xFF000000
#define UART_UA1_CPR_RESERVED_SHIFT              24 
#define UART_UA1_CPR_RESERVED_BIT                0xFF
#define UART_UA1_CPR_RESERVED_BITWIDTH           8
// UA1_UCV Register
#define UART_UA1_UCV_OFS                         0x000010F8
// UART_Component_Version bitfiled (RO) Reset=110011001100010011010000101010
#define UART_UA1_UCV_UART_COMPONENT_VERSION_MASK 0xFFFFFFFF
#define UART_UA1_UCV_UART_COMPONENT_VERSION_SHIFT 0 
#define UART_UA1_UCV_UART_COMPONENT_VERSION_BIT  0xFFFFFFFF
#define UART_UA1_UCV_UART_COMPONENT_VERSION_BITWIDTH 32
// UA1_CTR Register
#define UART_UA1_CTR_OFS                         0x000010FC
// Peripheral_ID bitfiled (RO) Reset=1000100010101110000000100010000
#define UART_UA1_CTR_PERIPHERAL_ID_MASK          0xFFFFFFFF
#define UART_UA1_CTR_PERIPHERAL_ID_SHIFT         0 
#define UART_UA1_CTR_PERIPHERAL_ID_BIT           0xFFFFFFFF
#define UART_UA1_CTR_PERIPHERAL_ID_BITWIDTH      32
// UA2_RBR_THR_DLL Register
#define UART_UA2_RBR_THR_DLL_OFS                 0x00002000
// RBR_THR_DLL bitfiled (RW) Reset=0
#define UART_UA2_RBR_THR_DLL_RBR_THR_DLL_MASK    0xFF
#define UART_UA2_RBR_THR_DLL_RBR_THR_DLL_SHIFT   0 
#define UART_UA2_RBR_THR_DLL_RBR_THR_DLL_BIT     0xFF
#define UART_UA2_RBR_THR_DLL_RBR_THR_DLL_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define UART_UA2_RBR_THR_DLL_RESERVED_MASK       0xFFFFFF00
#define UART_UA2_RBR_THR_DLL_RESERVED_SHIFT      8 
#define UART_UA2_RBR_THR_DLL_RESERVED_BIT        0xFFFFFF
#define UART_UA2_RBR_THR_DLL_RESERVED_BITWIDTH   24
// UA2_IER_DLH Register
#define UART_UA2_IER_DLH_OFS                     0x00002004
// ERBFI_DLH0 bitfiled (RW) Reset=0
#define UART_UA2_IER_DLH_ERBFI_DLH0_MASK         0x1
#define UART_UA2_IER_DLH_ERBFI_DLH0_SHIFT        0 
#define UART_UA2_IER_DLH_ERBFI_DLH0_BIT          0x1
#define UART_UA2_IER_DLH_ERBFI_DLH0_BITWIDTH     1
// ETBEI_DLH1 bitfiled (RW) Reset=0
#define UART_UA2_IER_DLH_ETBEI_DLH1_MASK         0x2
#define UART_UA2_IER_DLH_ETBEI_DLH1_SHIFT        1 
#define UART_UA2_IER_DLH_ETBEI_DLH1_BIT          0x1
#define UART_UA2_IER_DLH_ETBEI_DLH1_BITWIDTH     1
// ELSI_DLH2 bitfiled (RW) Reset=0
#define UART_UA2_IER_DLH_ELSI_DLH2_MASK          0x4
#define UART_UA2_IER_DLH_ELSI_DLH2_SHIFT         2 
#define UART_UA2_IER_DLH_ELSI_DLH2_BIT           0x1
#define UART_UA2_IER_DLH_ELSI_DLH2_BITWIDTH      1
// EDSSI_DLH3 bitfiled (RW) Reset=0
#define UART_UA2_IER_DLH_EDSSI_DLH3_MASK         0x8
#define UART_UA2_IER_DLH_EDSSI_DLH3_SHIFT        3 
#define UART_UA2_IER_DLH_EDSSI_DLH3_BIT          0x1
#define UART_UA2_IER_DLH_EDSSI_DLH3_BITWIDTH     1
// DLH64 bitfiled (RW) Reset=0
#define UART_UA2_IER_DLH_DLH64_MASK              0x70
#define UART_UA2_IER_DLH_DLH64_SHIFT             4 
#define UART_UA2_IER_DLH_DLH64_BIT               0x7
#define UART_UA2_IER_DLH_DLH64_BITWIDTH          3
// PTIME_DLH7 bitfiled (RW) Reset=0
#define UART_UA2_IER_DLH_PTIME_DLH7_MASK         0x80
#define UART_UA2_IER_DLH_PTIME_DLH7_SHIFT        7 
#define UART_UA2_IER_DLH_PTIME_DLH7_BIT          0x1
#define UART_UA2_IER_DLH_PTIME_DLH7_BITWIDTH     1
// reserved bitfiled (RO) Reset=0
#define UART_UA2_IER_DLH_RESERVED_MASK           0xFFFFFF00
#define UART_UA2_IER_DLH_RESERVED_SHIFT          8 
#define UART_UA2_IER_DLH_RESERVED_BIT            0xFFFFFF
#define UART_UA2_IER_DLH_RESERVED_BITWIDTH       24
// UA2_FCR_IIR Register
#define UART_UA2_FCR_IIR_OFS                     0x00002008
// IID0_FIFOE bitfiled (RW) Reset=1
#define UART_UA2_FCR_IIR_IID0_FIFOE_MASK         0x1
#define UART_UA2_FCR_IIR_IID0_FIFOE_SHIFT        0 
#define UART_UA2_FCR_IIR_IID0_FIFOE_BIT          0x1
#define UART_UA2_FCR_IIR_IID0_FIFOE_BITWIDTH     1
// IID1_RFIFOR bitfiled (RW) Reset=0
#define UART_UA2_FCR_IIR_IID1_RFIFOR_MASK        0x2
#define UART_UA2_FCR_IIR_IID1_RFIFOR_SHIFT       1 
#define UART_UA2_FCR_IIR_IID1_RFIFOR_BIT         0x1
#define UART_UA2_FCR_IIR_IID1_RFIFOR_BITWIDTH    1
// IID2_XFIFOR bitfiled (RW) Reset=0
#define UART_UA2_FCR_IIR_IID2_XFIFOR_MASK        0x4
#define UART_UA2_FCR_IIR_IID2_XFIFOR_SHIFT       2 
#define UART_UA2_FCR_IIR_IID2_XFIFOR_BIT         0x1
#define UART_UA2_FCR_IIR_IID2_XFIFOR_BITWIDTH    1
// IID3_DMAM bitfiled (RW) Reset=0
#define UART_UA2_FCR_IIR_IID3_DMAM_MASK          0x8
#define UART_UA2_FCR_IIR_IID3_DMAM_SHIFT         3 
#define UART_UA2_FCR_IIR_IID3_DMAM_BIT           0x1
#define UART_UA2_FCR_IIR_IID3_DMAM_BITWIDTH      1
// TET bitfiled (RW) Reset=0
#define UART_UA2_FCR_IIR_TET_MASK                0x30
#define UART_UA2_FCR_IIR_TET_SHIFT               4 
#define UART_UA2_FCR_IIR_TET_BIT                 0x3
#define UART_UA2_FCR_IIR_TET_BITWIDTH            2
// FIFOSE_RCVR bitfiled (RW) Reset=0
#define UART_UA2_FCR_IIR_FIFOSE_RCVR_MASK        0xC0
#define UART_UA2_FCR_IIR_FIFOSE_RCVR_SHIFT       6 
#define UART_UA2_FCR_IIR_FIFOSE_RCVR_BIT         0x3
#define UART_UA2_FCR_IIR_FIFOSE_RCVR_BITWIDTH    2
// reserved bitfiled (RO) Reset=0
#define UART_UA2_FCR_IIR_RESERVED_MASK           0xFFFFFF00
#define UART_UA2_FCR_IIR_RESERVED_SHIFT          8 
#define UART_UA2_FCR_IIR_RESERVED_BIT            0xFFFFFF
#define UART_UA2_FCR_IIR_RESERVED_BITWIDTH       24
// UA2_LCR Register
#define UART_UA2_LCR_OFS                         0x0000200C
// DLS bitfiled (RW) Reset=0
#define UART_UA2_LCR_DLS_MASK                    0x3
#define UART_UA2_LCR_DLS_SHIFT                   0 
#define UART_UA2_LCR_DLS_BIT                     0x3
#define UART_UA2_LCR_DLS_BITWIDTH                2
// STOP bitfiled (RW) Reset=0
#define UART_UA2_LCR_STOP_MASK                   0x4
#define UART_UA2_LCR_STOP_SHIFT                  2 
#define UART_UA2_LCR_STOP_BIT                    0x1
#define UART_UA2_LCR_STOP_BITWIDTH               1
// PEN bitfiled (RW) Reset=0
#define UART_UA2_LCR_PEN_MASK                    0x8
#define UART_UA2_LCR_PEN_SHIFT                   3 
#define UART_UA2_LCR_PEN_BIT                     0x1
#define UART_UA2_LCR_PEN_BITWIDTH                1
// EPS bitfiled (RW) Reset=0
#define UART_UA2_LCR_EPS_MASK                    0x10
#define UART_UA2_LCR_EPS_SHIFT                   4 
#define UART_UA2_LCR_EPS_BIT                     0x1
#define UART_UA2_LCR_EPS_BITWIDTH                1
// SP bitfiled (RW) Reset=0
#define UART_UA2_LCR_SP_MASK                     0x20
#define UART_UA2_LCR_SP_SHIFT                    5 
#define UART_UA2_LCR_SP_BIT                      0x1
#define UART_UA2_LCR_SP_BITWIDTH                 1
// Break bitfiled (RW) Reset=0
#define UART_UA2_LCR_BREAK_MASK                  0x40
#define UART_UA2_LCR_BREAK_SHIFT                 6 
#define UART_UA2_LCR_BREAK_BIT                   0x1
#define UART_UA2_LCR_BREAK_BITWIDTH              1
// DLAB bitfiled (RW) Reset=0
#define UART_UA2_LCR_DLAB_MASK                   0x80
#define UART_UA2_LCR_DLAB_SHIFT                  7 
#define UART_UA2_LCR_DLAB_BIT                    0x1
#define UART_UA2_LCR_DLAB_BITWIDTH               1
// reserved bitfiled (RO) Reset=0
#define UART_UA2_LCR_RESERVED_MASK               0xFFFFFF00
#define UART_UA2_LCR_RESERVED_SHIFT              8 
#define UART_UA2_LCR_RESERVED_BIT                0xFFFFFF
#define UART_UA2_LCR_RESERVED_BITWIDTH           24
// UA2_MCR Register
#define UART_UA2_MCR_OFS                         0x00002010
// DTR bitfiled (RW) Reset=0
#define UART_UA2_MCR_DTR_MASK                    0x1
#define UART_UA2_MCR_DTR_SHIFT                   0 
#define UART_UA2_MCR_DTR_BIT                     0x1
#define UART_UA2_MCR_DTR_BITWIDTH                1
// RTS bitfiled (RW) Reset=0
#define UART_UA2_MCR_RTS_MASK                    0x2
#define UART_UA2_MCR_RTS_SHIFT                   1 
#define UART_UA2_MCR_RTS_BIT                     0x1
#define UART_UA2_MCR_RTS_BITWIDTH                1
// OUT1 bitfiled (RW) Reset=0
#define UART_UA2_MCR_OUT1_MASK                   0x4
#define UART_UA2_MCR_OUT1_SHIFT                  2 
#define UART_UA2_MCR_OUT1_BIT                    0x1
#define UART_UA2_MCR_OUT1_BITWIDTH               1
// OUT2 bitfiled (RW) Reset=0
#define UART_UA2_MCR_OUT2_MASK                   0x8
#define UART_UA2_MCR_OUT2_SHIFT                  3 
#define UART_UA2_MCR_OUT2_BIT                    0x1
#define UART_UA2_MCR_OUT2_BITWIDTH               1
// LoopBack bitfiled (RW) Reset=0
#define UART_UA2_MCR_LOOPBACK_MASK               0x10
#define UART_UA2_MCR_LOOPBACK_SHIFT              4 
#define UART_UA2_MCR_LOOPBACK_BIT                0x1
#define UART_UA2_MCR_LOOPBACK_BITWIDTH           1
// AFCE bitfiled (RW) Reset=0
#define UART_UA2_MCR_AFCE_MASK                   0x20
#define UART_UA2_MCR_AFCE_SHIFT                  5 
#define UART_UA2_MCR_AFCE_BIT                    0x1
#define UART_UA2_MCR_AFCE_BITWIDTH               1
// SIRE bitfiled (RW) Reset=0
#define UART_UA2_MCR_SIRE_MASK                   0x40
#define UART_UA2_MCR_SIRE_SHIFT                  6 
#define UART_UA2_MCR_SIRE_BIT                    0x1
#define UART_UA2_MCR_SIRE_BITWIDTH               1
// reserved bitfiled (RO) Reset=0
#define UART_UA2_MCR_RESERVED_MASK               0xFFFFFF80
#define UART_UA2_MCR_RESERVED_SHIFT              7 
#define UART_UA2_MCR_RESERVED_BIT                0x1FFFFFF
#define UART_UA2_MCR_RESERVED_BITWIDTH           25
// UA2_LSR Register
#define UART_UA2_LSR_OFS                         0x00002014
// DR bitfiled (RO) Reset=0
#define UART_UA2_LSR_DR_MASK                     0x1
#define UART_UA2_LSR_DR_SHIFT                    0 
#define UART_UA2_LSR_DR_BIT                      0x1
#define UART_UA2_LSR_DR_BITWIDTH                 1
// OE bitfiled (RO) Reset=0
#define UART_UA2_LSR_OE_MASK                     0x2
#define UART_UA2_LSR_OE_SHIFT                    1 
#define UART_UA2_LSR_OE_BIT                      0x1
#define UART_UA2_LSR_OE_BITWIDTH                 1
// PE bitfiled (RO) Reset=0
#define UART_UA2_LSR_PE_MASK                     0x4
#define UART_UA2_LSR_PE_SHIFT                    2 
#define UART_UA2_LSR_PE_BIT                      0x1
#define UART_UA2_LSR_PE_BITWIDTH                 1
// FE bitfiled (RO) Reset=0
#define UART_UA2_LSR_FE_MASK                     0x8
#define UART_UA2_LSR_FE_SHIFT                    3 
#define UART_UA2_LSR_FE_BIT                      0x1
#define UART_UA2_LSR_FE_BITWIDTH                 1
// BI bitfiled (RO) Reset=0
#define UART_UA2_LSR_BI_MASK                     0x10
#define UART_UA2_LSR_BI_SHIFT                    4 
#define UART_UA2_LSR_BI_BIT                      0x1
#define UART_UA2_LSR_BI_BITWIDTH                 1
// THRE bitfiled (RO) Reset=1
#define UART_UA2_LSR_THRE_MASK                   0x20
#define UART_UA2_LSR_THRE_SHIFT                  5 
#define UART_UA2_LSR_THRE_BIT                    0x1
#define UART_UA2_LSR_THRE_BITWIDTH               1
// TEMT bitfiled (RO) Reset=1
#define UART_UA2_LSR_TEMT_MASK                   0x40
#define UART_UA2_LSR_TEMT_SHIFT                  6 
#define UART_UA2_LSR_TEMT_BIT                    0x1
#define UART_UA2_LSR_TEMT_BITWIDTH               1
// RFE bitfiled (RO) Reset=0
#define UART_UA2_LSR_RFE_MASK                    0x80
#define UART_UA2_LSR_RFE_SHIFT                   7 
#define UART_UA2_LSR_RFE_BIT                     0x1
#define UART_UA2_LSR_RFE_BITWIDTH                1
// reserved bitfiled (RO) Reset=0
#define UART_UA2_LSR_RESERVED_MASK               0xFFFFFF00
#define UART_UA2_LSR_RESERVED_SHIFT              8 
#define UART_UA2_LSR_RESERVED_BIT                0xFFFFFF
#define UART_UA2_LSR_RESERVED_BITWIDTH           24
// UA2_MSR Register
#define UART_UA2_MSR_OFS                         0x00002018
// DCTS bitfiled (RO) Reset=0
#define UART_UA2_MSR_DCTS_MASK                   0x1
#define UART_UA2_MSR_DCTS_SHIFT                  0 
#define UART_UA2_MSR_DCTS_BIT                    0x1
#define UART_UA2_MSR_DCTS_BITWIDTH               1
// DDSR bitfiled (RO) Reset=0
#define UART_UA2_MSR_DDSR_MASK                   0x2
#define UART_UA2_MSR_DDSR_SHIFT                  1 
#define UART_UA2_MSR_DDSR_BIT                    0x1
#define UART_UA2_MSR_DDSR_BITWIDTH               1
// TERI bitfiled (RO) Reset=0
#define UART_UA2_MSR_TERI_MASK                   0x4
#define UART_UA2_MSR_TERI_SHIFT                  2 
#define UART_UA2_MSR_TERI_BIT                    0x1
#define UART_UA2_MSR_TERI_BITWIDTH               1
// DDCD bitfiled (RO) Reset=0
#define UART_UA2_MSR_DDCD_MASK                   0x8
#define UART_UA2_MSR_DDCD_SHIFT                  3 
#define UART_UA2_MSR_DDCD_BIT                    0x1
#define UART_UA2_MSR_DDCD_BITWIDTH               1
// CTS bitfiled (RO) Reset=0
#define UART_UA2_MSR_CTS_MASK                    0x10
#define UART_UA2_MSR_CTS_SHIFT                   4 
#define UART_UA2_MSR_CTS_BIT                     0x1
#define UART_UA2_MSR_CTS_BITWIDTH                1
// DSR bitfiled (RO) Reset=0
#define UART_UA2_MSR_DSR_MASK                    0x20
#define UART_UA2_MSR_DSR_SHIFT                   5 
#define UART_UA2_MSR_DSR_BIT                     0x1
#define UART_UA2_MSR_DSR_BITWIDTH                1
// RI bitfiled (RO) Reset=0
#define UART_UA2_MSR_RI_MASK                     0x40
#define UART_UA2_MSR_RI_SHIFT                    6 
#define UART_UA2_MSR_RI_BIT                      0x1
#define UART_UA2_MSR_RI_BITWIDTH                 1
// DCD bitfiled (RO) Reset=0
#define UART_UA2_MSR_DCD_MASK                    0x80
#define UART_UA2_MSR_DCD_SHIFT                   7 
#define UART_UA2_MSR_DCD_BIT                     0x1
#define UART_UA2_MSR_DCD_BITWIDTH                1
// reserved bitfiled (RO) Reset=0
#define UART_UA2_MSR_RESERVED_MASK               0xFFFFFF00
#define UART_UA2_MSR_RESERVED_SHIFT              8 
#define UART_UA2_MSR_RESERVED_BIT                0xFFFFFF
#define UART_UA2_MSR_RESERVED_BITWIDTH           24
// UA2_SCR Register
#define UART_UA2_SCR_OFS                         0x0000201C
// SCR bitfiled (RW) Reset=0
#define UART_UA2_SCR_SCR_MASK                    0xFF
#define UART_UA2_SCR_SCR_SHIFT                   0 
#define UART_UA2_SCR_SCR_BIT                     0xFF
#define UART_UA2_SCR_SCR_BITWIDTH                8
// reserved bitfiled (RO) Reset=0
#define UART_UA2_SCR_RESERVED_MASK               0xFFFFFF00
#define UART_UA2_SCR_RESERVED_SHIFT              8 
#define UART_UA2_SCR_RESERVED_BIT                0xFFFFFF
#define UART_UA2_SCR_RESERVED_BITWIDTH           24
// UA2_FAR Register
#define UART_UA2_FAR_OFS                         0x00002070
// FAR bitfiled (RW) Reset=0
#define UART_UA2_FAR_FAR_MASK                    0x1
#define UART_UA2_FAR_FAR_SHIFT                   0 
#define UART_UA2_FAR_FAR_BIT                     0x1
#define UART_UA2_FAR_FAR_BITWIDTH                1
// reserved bitfiled (RO) Reset=0
#define UART_UA2_FAR_RESERVED_MASK               0xFFFFFFFE
#define UART_UA2_FAR_RESERVED_SHIFT              1 
#define UART_UA2_FAR_RESERVED_BIT                0x7FFFFFFF
#define UART_UA2_FAR_RESERVED_BITWIDTH           31
// UA2_TFR Register
#define UART_UA2_TFR_OFS                         0x00002074
// TFR bitfiled (RO) Reset=0
#define UART_UA2_TFR_TFR_MASK                    0xFF
#define UART_UA2_TFR_TFR_SHIFT                   0 
#define UART_UA2_TFR_TFR_BIT                     0xFF
#define UART_UA2_TFR_TFR_BITWIDTH                8
// reserved bitfiled (RO) Reset=0
#define UART_UA2_TFR_RESERVED_MASK               0xFFFFFF00
#define UART_UA2_TFR_RESERVED_SHIFT              8 
#define UART_UA2_TFR_RESERVED_BIT                0xFFFFFF
#define UART_UA2_TFR_RESERVED_BITWIDTH           24
// UA2_RFW Register
#define UART_UA2_RFW_OFS                         0x00002078
// RFWD bitfiled (RW) Reset=0
#define UART_UA2_RFW_RFWD_MASK                   0xFF
#define UART_UA2_RFW_RFWD_SHIFT                  0 
#define UART_UA2_RFW_RFWD_BIT                    0xFF
#define UART_UA2_RFW_RFWD_BITWIDTH               8
// RFPE bitfiled (RW) Reset=0
#define UART_UA2_RFW_RFPE_MASK                   0x100
#define UART_UA2_RFW_RFPE_SHIFT                  8 
#define UART_UA2_RFW_RFPE_BIT                    0x1
#define UART_UA2_RFW_RFPE_BITWIDTH               1
// RFFE bitfiled (RW) Reset=0
#define UART_UA2_RFW_RFFE_MASK                   0x200
#define UART_UA2_RFW_RFFE_SHIFT                  9 
#define UART_UA2_RFW_RFFE_BIT                    0x1
#define UART_UA2_RFW_RFFE_BITWIDTH               1
// reserved bitfiled (RO) Reset=0
#define UART_UA2_RFW_RESERVED_MASK               0xFFFFFC00
#define UART_UA2_RFW_RESERVED_SHIFT              10 
#define UART_UA2_RFW_RESERVED_BIT                0x3FFFFF
#define UART_UA2_RFW_RESERVED_BITWIDTH           22
// UA2_USR Register
#define UART_UA2_USR_OFS                         0x0000207C
// BUSY bitfiled (RO) Reset=0
#define UART_UA2_USR_BUSY_MASK                   0x1
#define UART_UA2_USR_BUSY_SHIFT                  0 
#define UART_UA2_USR_BUSY_BIT                    0x1
#define UART_UA2_USR_BUSY_BITWIDTH               1
// TFNF bitfiled (RO) Reset=1
#define UART_UA2_USR_TFNF_MASK                   0x2
#define UART_UA2_USR_TFNF_SHIFT                  1 
#define UART_UA2_USR_TFNF_BIT                    0x1
#define UART_UA2_USR_TFNF_BITWIDTH               1
// TFE bitfiled (RO) Reset=1
#define UART_UA2_USR_TFE_MASK                    0x4
#define UART_UA2_USR_TFE_SHIFT                   2 
#define UART_UA2_USR_TFE_BIT                     0x1
#define UART_UA2_USR_TFE_BITWIDTH                1
// RFNE bitfiled (RO) Reset=0
#define UART_UA2_USR_RFNE_MASK                   0x8
#define UART_UA2_USR_RFNE_SHIFT                  3 
#define UART_UA2_USR_RFNE_BIT                    0x1
#define UART_UA2_USR_RFNE_BITWIDTH               1
// RFF bitfiled (RO) Reset=0
#define UART_UA2_USR_RFF_MASK                    0x10
#define UART_UA2_USR_RFF_SHIFT                   4 
#define UART_UA2_USR_RFF_BIT                     0x1
#define UART_UA2_USR_RFF_BITWIDTH                1
// reserved bitfiled (RO) Reset=0
#define UART_UA2_USR_RESERVED_MASK               0xFFFFFFE0
#define UART_UA2_USR_RESERVED_SHIFT              5 
#define UART_UA2_USR_RESERVED_BIT                0x7FFFFFF
#define UART_UA2_USR_RESERVED_BITWIDTH           27
// UA2_TFL Register
#define UART_UA2_TFL_OFS                         0x00002080
// TFL bitfiled (RO) Reset=0
#define UART_UA2_TFL_TFL_MASK                    0x1F
#define UART_UA2_TFL_TFL_SHIFT                   0 
#define UART_UA2_TFL_TFL_BIT                     0x1F
#define UART_UA2_TFL_TFL_BITWIDTH                5
// reserved bitfiled (RO) Reset=0
#define UART_UA2_TFL_RESERVED_MASK               0xFFFFFFE0
#define UART_UA2_TFL_RESERVED_SHIFT              5 
#define UART_UA2_TFL_RESERVED_BIT                0x7FFFFFF
#define UART_UA2_TFL_RESERVED_BITWIDTH           27
// UA2_RFL Register
#define UART_UA2_RFL_OFS                         0x00002084
// RFL bitfiled (RO) Reset=0
#define UART_UA2_RFL_RFL_MASK                    0x1F
#define UART_UA2_RFL_RFL_SHIFT                   0 
#define UART_UA2_RFL_RFL_BIT                     0x1F
#define UART_UA2_RFL_RFL_BITWIDTH                5
// reserved bitfiled (RO) Reset=0
#define UART_UA2_RFL_RESERVED_MASK               0xFFFFFFE0
#define UART_UA2_RFL_RESERVED_SHIFT              5 
#define UART_UA2_RFL_RESERVED_BIT                0x7FFFFFF
#define UART_UA2_RFL_RESERVED_BITWIDTH           27
// UA2_HTX Register
#define UART_UA2_HTX_OFS                         0x000020A4
// HTX bitfiled (RW) Reset=0
#define UART_UA2_HTX_HTX_MASK                    0x1
#define UART_UA2_HTX_HTX_SHIFT                   0 
#define UART_UA2_HTX_HTX_BIT                     0x1
#define UART_UA2_HTX_HTX_BITWIDTH                1
// reserved bitfiled (RO) Reset=0
#define UART_UA2_HTX_RESERVED_MASK               0xFFFFFFFE
#define UART_UA2_HTX_RESERVED_SHIFT              1 
#define UART_UA2_HTX_RESERVED_BIT                0x7FFFFFFF
#define UART_UA2_HTX_RESERVED_BITWIDTH           31
// UA2_DMASA Register
#define UART_UA2_DMASA_OFS                       0x000020A8
// DMASA bitfiled (RW) Reset=0
#define UART_UA2_DMASA_DMASA_MASK                0x1
#define UART_UA2_DMASA_DMASA_SHIFT               0 
#define UART_UA2_DMASA_DMASA_BIT                 0x1
#define UART_UA2_DMASA_DMASA_BITWIDTH            1
// reserved bitfiled (RO) Reset=0
#define UART_UA2_DMASA_RESERVED_MASK             0xFFFFFFFE
#define UART_UA2_DMASA_RESERVED_SHIFT            1 
#define UART_UA2_DMASA_RESERVED_BIT              0x7FFFFFFF
#define UART_UA2_DMASA_RESERVED_BITWIDTH         31
// UA2_CPR Register
#define UART_UA2_CPR_OFS                         0x000020F4
// APB_DATA_WIDTH bitfiled (RO) Reset=10
#define UART_UA2_CPR_APB_DATA_WIDTH_MASK         0x3
#define UART_UA2_CPR_APB_DATA_WIDTH_SHIFT        0 
#define UART_UA2_CPR_APB_DATA_WIDTH_BIT          0x3
#define UART_UA2_CPR_APB_DATA_WIDTH_BITWIDTH     2
// reserved3 bitfiled (RO) Reset=0
#define UART_UA2_CPR_RESERVED3_MASK              0xC
#define UART_UA2_CPR_RESERVED3_SHIFT             2 
#define UART_UA2_CPR_RESERVED3_BIT               0x3
#define UART_UA2_CPR_RESERVED3_BITWIDTH          2
// AFCE_MODE bitfiled (RO) Reset=1
#define UART_UA2_CPR_AFCE_MODE_MASK              0x10
#define UART_UA2_CPR_AFCE_MODE_SHIFT             4 
#define UART_UA2_CPR_AFCE_MODE_BIT               0x1
#define UART_UA2_CPR_AFCE_MODE_BITWIDTH          1
// THRE_MODE bitfiled (RO) Reset=1
#define UART_UA2_CPR_THRE_MODE_MASK              0x20
#define UART_UA2_CPR_THRE_MODE_SHIFT             5 
#define UART_UA2_CPR_THRE_MODE_BIT               0x1
#define UART_UA2_CPR_THRE_MODE_BITWIDTH          1
// SIR_MODE bitfiled (RO) Reset=0
#define UART_UA2_CPR_SIR_MODE_MASK               0x40
#define UART_UA2_CPR_SIR_MODE_SHIFT              6 
#define UART_UA2_CPR_SIR_MODE_BIT                0x1
#define UART_UA2_CPR_SIR_MODE_BITWIDTH           1
// SIR_LP_MODE bitfiled (RO) Reset=0
#define UART_UA2_CPR_SIR_LP_MODE_MASK            0x80
#define UART_UA2_CPR_SIR_LP_MODE_SHIFT           7 
#define UART_UA2_CPR_SIR_LP_MODE_BIT             0x1
#define UART_UA2_CPR_SIR_LP_MODE_BITWIDTH        1
// ADDITIONAL_FEAT bitfiled (RO) Reset=1
#define UART_UA2_CPR_ADDITIONAL_FEAT_MASK        0x100
#define UART_UA2_CPR_ADDITIONAL_FEAT_SHIFT       8 
#define UART_UA2_CPR_ADDITIONAL_FEAT_BIT         0x1
#define UART_UA2_CPR_ADDITIONAL_FEAT_BITWIDTH    1
// FIFO_ACCESS bitfiled (RO) Reset=1
#define UART_UA2_CPR_FIFO_ACCESS_MASK            0x200
#define UART_UA2_CPR_FIFO_ACCESS_SHIFT           9 
#define UART_UA2_CPR_FIFO_ACCESS_BIT             0x1
#define UART_UA2_CPR_FIFO_ACCESS_BITWIDTH        1
// FIFO_STAT bitfiled (RO) Reset=1
#define UART_UA2_CPR_FIFO_STAT_MASK              0x400
#define UART_UA2_CPR_FIFO_STAT_SHIFT             10 
#define UART_UA2_CPR_FIFO_STAT_BIT               0x1
#define UART_UA2_CPR_FIFO_STAT_BITWIDTH          1
// SHADOW bitfiled (RO) Reset=0
#define UART_UA2_CPR_SHADOW_MASK                 0x800
#define UART_UA2_CPR_SHADOW_SHIFT                11 
#define UART_UA2_CPR_SHADOW_BIT                  0x1
#define UART_UA2_CPR_SHADOW_BITWIDTH             1
// UART_ADD_ENCODED_PARAMS bitfiled (RO) Reset=1
#define UART_UA2_CPR_UART_ADD_ENCODED_PARAMS_MASK 0x1000
#define UART_UA2_CPR_UART_ADD_ENCODED_PARAMS_SHIFT 12 
#define UART_UA2_CPR_UART_ADD_ENCODED_PARAMS_BIT 0x1
#define UART_UA2_CPR_UART_ADD_ENCODED_PARAMS_BITWIDTH 1
// DMA_EXTRA bitfiled (RO) Reset=1
#define UART_UA2_CPR_DMA_EXTRA_MASK              0x2000
#define UART_UA2_CPR_DMA_EXTRA_SHIFT             13 
#define UART_UA2_CPR_DMA_EXTRA_BIT               0x1
#define UART_UA2_CPR_DMA_EXTRA_BITWIDTH          1
// reserved2 bitfiled (RO) Reset=0
#define UART_UA2_CPR_RESERVED2_MASK              0xC000
#define UART_UA2_CPR_RESERVED2_SHIFT             14 
#define UART_UA2_CPR_RESERVED2_BIT               0x3
#define UART_UA2_CPR_RESERVED2_BITWIDTH          2
// FIFO_MODE bitfiled (RO) Reset=1
#define UART_UA2_CPR_FIFO_MODE_MASK              0xFF0000
#define UART_UA2_CPR_FIFO_MODE_SHIFT             16 
#define UART_UA2_CPR_FIFO_MODE_BIT               0xFF
#define UART_UA2_CPR_FIFO_MODE_BITWIDTH          8
// reserved bitfiled (RO) Reset=0
#define UART_UA2_CPR_RESERVED_MASK               0xFF000000
#define UART_UA2_CPR_RESERVED_SHIFT              24 
#define UART_UA2_CPR_RESERVED_BIT                0xFF
#define UART_UA2_CPR_RESERVED_BITWIDTH           8
// UA2_UCV Register
#define UART_UA2_UCV_OFS                         0x000020F8
// UART_Component_Version bitfiled (RO) Reset=110011001100010011010000101010
#define UART_UA2_UCV_UART_COMPONENT_VERSION_MASK 0xFFFFFFFF
#define UART_UA2_UCV_UART_COMPONENT_VERSION_SHIFT 0 
#define UART_UA2_UCV_UART_COMPONENT_VERSION_BIT  0xFFFFFFFF
#define UART_UA2_UCV_UART_COMPONENT_VERSION_BITWIDTH 32
// UA2_CTR Register
#define UART_UA2_CTR_OFS                         0x000020FC
// Peripheral_ID bitfiled (RO) Reset=1000100010101110000000100010000
#define UART_UA2_CTR_PERIPHERAL_ID_MASK          0xFFFFFFFF
#define UART_UA2_CTR_PERIPHERAL_ID_SHIFT         0 
#define UART_UA2_CTR_PERIPHERAL_ID_BIT           0xFFFFFFFF
#define UART_UA2_CTR_PERIPHERAL_ID_BITWIDTH      32
// UA3_RBR_THR_DLL Register
#define UART_UA3_RBR_THR_DLL_OFS                 0x00003000
// RBR_THR_DLL bitfiled (RW) Reset=0
#define UART_UA3_RBR_THR_DLL_RBR_THR_DLL_MASK    0xFF
#define UART_UA3_RBR_THR_DLL_RBR_THR_DLL_SHIFT   0 
#define UART_UA3_RBR_THR_DLL_RBR_THR_DLL_BIT     0xFF
#define UART_UA3_RBR_THR_DLL_RBR_THR_DLL_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define UART_UA3_RBR_THR_DLL_RESERVED_MASK       0xFFFFFF00
#define UART_UA3_RBR_THR_DLL_RESERVED_SHIFT      8 
#define UART_UA3_RBR_THR_DLL_RESERVED_BIT        0xFFFFFF
#define UART_UA3_RBR_THR_DLL_RESERVED_BITWIDTH   24
// UA3_IER_DLH Register
#define UART_UA3_IER_DLH_OFS                     0x00003004
// ERBFI_DLH0 bitfiled (RW) Reset=0
#define UART_UA3_IER_DLH_ERBFI_DLH0_MASK         0x1
#define UART_UA3_IER_DLH_ERBFI_DLH0_SHIFT        0 
#define UART_UA3_IER_DLH_ERBFI_DLH0_BIT          0x1
#define UART_UA3_IER_DLH_ERBFI_DLH0_BITWIDTH     1
// ETBEI_DLH1 bitfiled (RW) Reset=0
#define UART_UA3_IER_DLH_ETBEI_DLH1_MASK         0x2
#define UART_UA3_IER_DLH_ETBEI_DLH1_SHIFT        1 
#define UART_UA3_IER_DLH_ETBEI_DLH1_BIT          0x1
#define UART_UA3_IER_DLH_ETBEI_DLH1_BITWIDTH     1
// ELSI_DLH2 bitfiled (RW) Reset=0
#define UART_UA3_IER_DLH_ELSI_DLH2_MASK          0x4
#define UART_UA3_IER_DLH_ELSI_DLH2_SHIFT         2 
#define UART_UA3_IER_DLH_ELSI_DLH2_BIT           0x1
#define UART_UA3_IER_DLH_ELSI_DLH2_BITWIDTH      1
// EDSSI_DLH3 bitfiled (RW) Reset=0
#define UART_UA3_IER_DLH_EDSSI_DLH3_MASK         0x8
#define UART_UA3_IER_DLH_EDSSI_DLH3_SHIFT        3 
#define UART_UA3_IER_DLH_EDSSI_DLH3_BIT          0x1
#define UART_UA3_IER_DLH_EDSSI_DLH3_BITWIDTH     1
// DLH64 bitfiled (RW) Reset=0
#define UART_UA3_IER_DLH_DLH64_MASK              0x70
#define UART_UA3_IER_DLH_DLH64_SHIFT             4 
#define UART_UA3_IER_DLH_DLH64_BIT               0x7
#define UART_UA3_IER_DLH_DLH64_BITWIDTH          3
// PTIME_DLH7 bitfiled (RW) Reset=0
#define UART_UA3_IER_DLH_PTIME_DLH7_MASK         0x80
#define UART_UA3_IER_DLH_PTIME_DLH7_SHIFT        7 
#define UART_UA3_IER_DLH_PTIME_DLH7_BIT          0x1
#define UART_UA3_IER_DLH_PTIME_DLH7_BITWIDTH     1
// reserved bitfiled (RO) Reset=0
#define UART_UA3_IER_DLH_RESERVED_MASK           0xFFFFFF00
#define UART_UA3_IER_DLH_RESERVED_SHIFT          8 
#define UART_UA3_IER_DLH_RESERVED_BIT            0xFFFFFF
#define UART_UA3_IER_DLH_RESERVED_BITWIDTH       24
// UA3_FCR_IIR Register
#define UART_UA3_FCR_IIR_OFS                     0x00003008
// IID0_FIFOE bitfiled (RW) Reset=0
#define UART_UA3_FCR_IIR_IID0_FIFOE_MASK         0x1
#define UART_UA3_FCR_IIR_IID0_FIFOE_SHIFT        0 
#define UART_UA3_FCR_IIR_IID0_FIFOE_BIT          0x1
#define UART_UA3_FCR_IIR_IID0_FIFOE_BITWIDTH     1
// IID1_RFIFOR bitfiled (RW) Reset=0
#define UART_UA3_FCR_IIR_IID1_RFIFOR_MASK        0x2
#define UART_UA3_FCR_IIR_IID1_RFIFOR_SHIFT       1 
#define UART_UA3_FCR_IIR_IID1_RFIFOR_BIT         0x1
#define UART_UA3_FCR_IIR_IID1_RFIFOR_BITWIDTH    1
// IID2_XFIFOR bitfiled (RW) Reset=0
#define UART_UA3_FCR_IIR_IID2_XFIFOR_MASK        0x4
#define UART_UA3_FCR_IIR_IID2_XFIFOR_SHIFT       2 
#define UART_UA3_FCR_IIR_IID2_XFIFOR_BIT         0x1
#define UART_UA3_FCR_IIR_IID2_XFIFOR_BITWIDTH    1
// IID3_DMAM bitfiled (RW) Reset=0
#define UART_UA3_FCR_IIR_IID3_DMAM_MASK          0x8
#define UART_UA3_FCR_IIR_IID3_DMAM_SHIFT         3 
#define UART_UA3_FCR_IIR_IID3_DMAM_BIT           0x1
#define UART_UA3_FCR_IIR_IID3_DMAM_BITWIDTH      1
// TET bitfiled (RW) Reset=0
#define UART_UA3_FCR_IIR_TET_MASK                0x30
#define UART_UA3_FCR_IIR_TET_SHIFT               4 
#define UART_UA3_FCR_IIR_TET_BIT                 0x3
#define UART_UA3_FCR_IIR_TET_BITWIDTH            2
// FIFOSE_RCVR bitfiled (RW) Reset=0
#define UART_UA3_FCR_IIR_FIFOSE_RCVR_MASK        0xC0
#define UART_UA3_FCR_IIR_FIFOSE_RCVR_SHIFT       6 
#define UART_UA3_FCR_IIR_FIFOSE_RCVR_BIT         0x3
#define UART_UA3_FCR_IIR_FIFOSE_RCVR_BITWIDTH    2
// reserved bitfiled (RO) Reset=0
#define UART_UA3_FCR_IIR_RESERVED_MASK           0xFFFFFF00
#define UART_UA3_FCR_IIR_RESERVED_SHIFT          8 
#define UART_UA3_FCR_IIR_RESERVED_BIT            0xFFFFFF
#define UART_UA3_FCR_IIR_RESERVED_BITWIDTH       24
// UA3_LCR Register
#define UART_UA3_LCR_OFS                         0x0000300C
// DLS bitfiled (RW) Reset=0
#define UART_UA3_LCR_DLS_MASK                    0x3
#define UART_UA3_LCR_DLS_SHIFT                   0 
#define UART_UA3_LCR_DLS_BIT                     0x3
#define UART_UA3_LCR_DLS_BITWIDTH                2
// STOP bitfiled (RW) Reset=0
#define UART_UA3_LCR_STOP_MASK                   0x4
#define UART_UA3_LCR_STOP_SHIFT                  2 
#define UART_UA3_LCR_STOP_BIT                    0x1
#define UART_UA3_LCR_STOP_BITWIDTH               1
// PEN bitfiled (RW) Reset=0
#define UART_UA3_LCR_PEN_MASK                    0x8
#define UART_UA3_LCR_PEN_SHIFT                   3 
#define UART_UA3_LCR_PEN_BIT                     0x1
#define UART_UA3_LCR_PEN_BITWIDTH                1
// EPS bitfiled (RW) Reset=0
#define UART_UA3_LCR_EPS_MASK                    0x10
#define UART_UA3_LCR_EPS_SHIFT                   4 
#define UART_UA3_LCR_EPS_BIT                     0x1
#define UART_UA3_LCR_EPS_BITWIDTH                1
// SP bitfiled (RW) Reset=0
#define UART_UA3_LCR_SP_MASK                     0x20
#define UART_UA3_LCR_SP_SHIFT                    5 
#define UART_UA3_LCR_SP_BIT                      0x1
#define UART_UA3_LCR_SP_BITWIDTH                 1
// Break bitfiled (RW) Reset=0
#define UART_UA3_LCR_BREAK_MASK                  0x40
#define UART_UA3_LCR_BREAK_SHIFT                 6 
#define UART_UA3_LCR_BREAK_BIT                   0x1
#define UART_UA3_LCR_BREAK_BITWIDTH              1
// DLAB bitfiled (RW) Reset=0
#define UART_UA3_LCR_DLAB_MASK                   0x80
#define UART_UA3_LCR_DLAB_SHIFT                  7 
#define UART_UA3_LCR_DLAB_BIT                    0x1
#define UART_UA3_LCR_DLAB_BITWIDTH               1
// reserved bitfiled (RO) Reset=0
#define UART_UA3_LCR_RESERVED_MASK               0xFFFFFF00
#define UART_UA3_LCR_RESERVED_SHIFT              8 
#define UART_UA3_LCR_RESERVED_BIT                0xFFFFFF
#define UART_UA3_LCR_RESERVED_BITWIDTH           24
// UA3_MCR Register
#define UART_UA3_MCR_OFS                         0x00003010
// DTR bitfiled (RW) Reset=0
#define UART_UA3_MCR_DTR_MASK                    0x1
#define UART_UA3_MCR_DTR_SHIFT                   0 
#define UART_UA3_MCR_DTR_BIT                     0x1
#define UART_UA3_MCR_DTR_BITWIDTH                1
// RTS bitfiled (RW) Reset=0
#define UART_UA3_MCR_RTS_MASK                    0x2
#define UART_UA3_MCR_RTS_SHIFT                   1 
#define UART_UA3_MCR_RTS_BIT                     0x1
#define UART_UA3_MCR_RTS_BITWIDTH                1
// OUT1 bitfiled (RW) Reset=0
#define UART_UA3_MCR_OUT1_MASK                   0x4
#define UART_UA3_MCR_OUT1_SHIFT                  2 
#define UART_UA3_MCR_OUT1_BIT                    0x1
#define UART_UA3_MCR_OUT1_BITWIDTH               1
// OUT2 bitfiled (RW) Reset=0
#define UART_UA3_MCR_OUT2_MASK                   0x8
#define UART_UA3_MCR_OUT2_SHIFT                  3 
#define UART_UA3_MCR_OUT2_BIT                    0x1
#define UART_UA3_MCR_OUT2_BITWIDTH               1
// LoopBack bitfiled (RW) Reset=0
#define UART_UA3_MCR_LOOPBACK_MASK               0x10
#define UART_UA3_MCR_LOOPBACK_SHIFT              4 
#define UART_UA3_MCR_LOOPBACK_BIT                0x1
#define UART_UA3_MCR_LOOPBACK_BITWIDTH           1
// AFCE bitfiled (RW) Reset=0
#define UART_UA3_MCR_AFCE_MASK                   0x20
#define UART_UA3_MCR_AFCE_SHIFT                  5 
#define UART_UA3_MCR_AFCE_BIT                    0x1
#define UART_UA3_MCR_AFCE_BITWIDTH               1
// SIRE bitfiled (RW) Reset=0
#define UART_UA3_MCR_SIRE_MASK                   0x40
#define UART_UA3_MCR_SIRE_SHIFT                  6 
#define UART_UA3_MCR_SIRE_BIT                    0x1
#define UART_UA3_MCR_SIRE_BITWIDTH               1
// reserved bitfiled (RO) Reset=0
#define UART_UA3_MCR_RESERVED_MASK               0xFFFFFF80
#define UART_UA3_MCR_RESERVED_SHIFT              7 
#define UART_UA3_MCR_RESERVED_BIT                0x1FFFFFF
#define UART_UA3_MCR_RESERVED_BITWIDTH           25
// UA3_LSR Register
#define UART_UA3_LSR_OFS                         0x00003014
// DR bitfiled (RO) Reset=0
#define UART_UA3_LSR_DR_MASK                     0x1
#define UART_UA3_LSR_DR_SHIFT                    0 
#define UART_UA3_LSR_DR_BIT                      0x1
#define UART_UA3_LSR_DR_BITWIDTH                 1
// OE bitfiled (RO) Reset=0
#define UART_UA3_LSR_OE_MASK                     0x2
#define UART_UA3_LSR_OE_SHIFT                    1 
#define UART_UA3_LSR_OE_BIT                      0x1
#define UART_UA3_LSR_OE_BITWIDTH                 1
// PE bitfiled (RO) Reset=0
#define UART_UA3_LSR_PE_MASK                     0x4
#define UART_UA3_LSR_PE_SHIFT                    2 
#define UART_UA3_LSR_PE_BIT                      0x1
#define UART_UA3_LSR_PE_BITWIDTH                 1
// FE bitfiled (RO) Reset=0
#define UART_UA3_LSR_FE_MASK                     0x8
#define UART_UA3_LSR_FE_SHIFT                    3 
#define UART_UA3_LSR_FE_BIT                      0x1
#define UART_UA3_LSR_FE_BITWIDTH                 1
// BI bitfiled (RO) Reset=0
#define UART_UA3_LSR_BI_MASK                     0x10
#define UART_UA3_LSR_BI_SHIFT                    4 
#define UART_UA3_LSR_BI_BIT                      0x1
#define UART_UA3_LSR_BI_BITWIDTH                 1
// THRE bitfiled (RO) Reset=1
#define UART_UA3_LSR_THRE_MASK                   0x20
#define UART_UA3_LSR_THRE_SHIFT                  5 
#define UART_UA3_LSR_THRE_BIT                    0x1
#define UART_UA3_LSR_THRE_BITWIDTH               1
// TEMT bitfiled (RO) Reset=1
#define UART_UA3_LSR_TEMT_MASK                   0x40
#define UART_UA3_LSR_TEMT_SHIFT                  6 
#define UART_UA3_LSR_TEMT_BIT                    0x1
#define UART_UA3_LSR_TEMT_BITWIDTH               1
// RFE bitfiled (RO) Reset=0
#define UART_UA3_LSR_RFE_MASK                    0x80
#define UART_UA3_LSR_RFE_SHIFT                   7 
#define UART_UA3_LSR_RFE_BIT                     0x1
#define UART_UA3_LSR_RFE_BITWIDTH                1
// reserved bitfiled (RO) Reset=0
#define UART_UA3_LSR_RESERVED_MASK               0xFFFFFF00
#define UART_UA3_LSR_RESERVED_SHIFT              8 
#define UART_UA3_LSR_RESERVED_BIT                0xFFFFFF
#define UART_UA3_LSR_RESERVED_BITWIDTH           24
// UA3_MSR Register
#define UART_UA3_MSR_OFS                         0x00003018
// DCTS bitfiled (RO) Reset=0
#define UART_UA3_MSR_DCTS_MASK                   0x1
#define UART_UA3_MSR_DCTS_SHIFT                  0 
#define UART_UA3_MSR_DCTS_BIT                    0x1
#define UART_UA3_MSR_DCTS_BITWIDTH               1
// DDSR bitfiled (RO) Reset=0
#define UART_UA3_MSR_DDSR_MASK                   0x2
#define UART_UA3_MSR_DDSR_SHIFT                  1 
#define UART_UA3_MSR_DDSR_BIT                    0x1
#define UART_UA3_MSR_DDSR_BITWIDTH               1
// TERI bitfiled (RO) Reset=0
#define UART_UA3_MSR_TERI_MASK                   0x4
#define UART_UA3_MSR_TERI_SHIFT                  2 
#define UART_UA3_MSR_TERI_BIT                    0x1
#define UART_UA3_MSR_TERI_BITWIDTH               1
// DDCD bitfiled (RO) Reset=0
#define UART_UA3_MSR_DDCD_MASK                   0x8
#define UART_UA3_MSR_DDCD_SHIFT                  3 
#define UART_UA3_MSR_DDCD_BIT                    0x1
#define UART_UA3_MSR_DDCD_BITWIDTH               1
// CTS bitfiled (RO) Reset=0
#define UART_UA3_MSR_CTS_MASK                    0x10
#define UART_UA3_MSR_CTS_SHIFT                   4 
#define UART_UA3_MSR_CTS_BIT                     0x1
#define UART_UA3_MSR_CTS_BITWIDTH                1
// DSR bitfiled (RO) Reset=0
#define UART_UA3_MSR_DSR_MASK                    0x20
#define UART_UA3_MSR_DSR_SHIFT                   5 
#define UART_UA3_MSR_DSR_BIT                     0x1
#define UART_UA3_MSR_DSR_BITWIDTH                1
// RI bitfiled (RO) Reset=0
#define UART_UA3_MSR_RI_MASK                     0x40
#define UART_UA3_MSR_RI_SHIFT                    6 
#define UART_UA3_MSR_RI_BIT                      0x1
#define UART_UA3_MSR_RI_BITWIDTH                 1
// DCD bitfiled (RO) Reset=0
#define UART_UA3_MSR_DCD_MASK                    0x80
#define UART_UA3_MSR_DCD_SHIFT                   7 
#define UART_UA3_MSR_DCD_BIT                     0x1
#define UART_UA3_MSR_DCD_BITWIDTH                1
// reserved bitfiled (RO) Reset=0
#define UART_UA3_MSR_RESERVED_MASK               0xFFFFFF00
#define UART_UA3_MSR_RESERVED_SHIFT              8 
#define UART_UA3_MSR_RESERVED_BIT                0xFFFFFF
#define UART_UA3_MSR_RESERVED_BITWIDTH           24
// UA3_SCR Register
#define UART_UA3_SCR_OFS                         0x0000301C
// SCR bitfiled (RW) Reset=0
#define UART_UA3_SCR_SCR_MASK                    0xFF
#define UART_UA3_SCR_SCR_SHIFT                   0 
#define UART_UA3_SCR_SCR_BIT                     0xFF
#define UART_UA3_SCR_SCR_BITWIDTH                8
// reserved bitfiled (RO) Reset=0
#define UART_UA3_SCR_RESERVED_MASK               0xFFFFFF00
#define UART_UA3_SCR_RESERVED_SHIFT              8 
#define UART_UA3_SCR_RESERVED_BIT                0xFFFFFF
#define UART_UA3_SCR_RESERVED_BITWIDTH           24
// UA3_FAR Register
#define UART_UA3_FAR_OFS                         0x00003070
// FAR bitfiled (RW) Reset=0
#define UART_UA3_FAR_FAR_MASK                    0x1
#define UART_UA3_FAR_FAR_SHIFT                   0 
#define UART_UA3_FAR_FAR_BIT                     0x1
#define UART_UA3_FAR_FAR_BITWIDTH                1
// reserved bitfiled (RO) Reset=0
#define UART_UA3_FAR_RESERVED_MASK               0xFFFFFFFE
#define UART_UA3_FAR_RESERVED_SHIFT              1 
#define UART_UA3_FAR_RESERVED_BIT                0x7FFFFFFF
#define UART_UA3_FAR_RESERVED_BITWIDTH           31
// UA3_TFR Register
#define UART_UA3_TFR_OFS                         0x00003074
// TFR bitfiled (RO) Reset=0
#define UART_UA3_TFR_TFR_MASK                    0xFF
#define UART_UA3_TFR_TFR_SHIFT                   0 
#define UART_UA3_TFR_TFR_BIT                     0xFF
#define UART_UA3_TFR_TFR_BITWIDTH                8
// reserved bitfiled (RO) Reset=0
#define UART_UA3_TFR_RESERVED_MASK               0xFFFFFF00
#define UART_UA3_TFR_RESERVED_SHIFT              8 
#define UART_UA3_TFR_RESERVED_BIT                0xFFFFFF
#define UART_UA3_TFR_RESERVED_BITWIDTH           24
// UA3_RFW Register
#define UART_UA3_RFW_OFS                         0x00003078
// RFWD bitfiled (RW) Reset=0
#define UART_UA3_RFW_RFWD_MASK                   0xFF
#define UART_UA3_RFW_RFWD_SHIFT                  0 
#define UART_UA3_RFW_RFWD_BIT                    0xFF
#define UART_UA3_RFW_RFWD_BITWIDTH               8
// RFPE bitfiled (RW) Reset=0
#define UART_UA3_RFW_RFPE_MASK                   0x100
#define UART_UA3_RFW_RFPE_SHIFT                  8 
#define UART_UA3_RFW_RFPE_BIT                    0x1
#define UART_UA3_RFW_RFPE_BITWIDTH               1
// RFFE bitfiled (RW) Reset=0
#define UART_UA3_RFW_RFFE_MASK                   0x200
#define UART_UA3_RFW_RFFE_SHIFT                  9 
#define UART_UA3_RFW_RFFE_BIT                    0x1
#define UART_UA3_RFW_RFFE_BITWIDTH               1
// reserved bitfiled (RO) Reset=0
#define UART_UA3_RFW_RESERVED_MASK               0xFFFFFC00
#define UART_UA3_RFW_RESERVED_SHIFT              10 
#define UART_UA3_RFW_RESERVED_BIT                0x3FFFFF
#define UART_UA3_RFW_RESERVED_BITWIDTH           22
// UA3_USR Register
#define UART_UA3_USR_OFS                         0x0000307C
// BUSY bitfiled (RO) Reset=0
#define UART_UA3_USR_BUSY_MASK                   0x1
#define UART_UA3_USR_BUSY_SHIFT                  0 
#define UART_UA3_USR_BUSY_BIT                    0x1
#define UART_UA3_USR_BUSY_BITWIDTH               1
// TFNF bitfiled (RO) Reset=1
#define UART_UA3_USR_TFNF_MASK                   0x2
#define UART_UA3_USR_TFNF_SHIFT                  1 
#define UART_UA3_USR_TFNF_BIT                    0x1
#define UART_UA3_USR_TFNF_BITWIDTH               1
// TFE bitfiled (RO) Reset=1
#define UART_UA3_USR_TFE_MASK                    0x4
#define UART_UA3_USR_TFE_SHIFT                   2 
#define UART_UA3_USR_TFE_BIT                     0x1
#define UART_UA3_USR_TFE_BITWIDTH                1
// RFNE bitfiled (RO) Reset=0
#define UART_UA3_USR_RFNE_MASK                   0x8
#define UART_UA3_USR_RFNE_SHIFT                  3 
#define UART_UA3_USR_RFNE_BIT                    0x1
#define UART_UA3_USR_RFNE_BITWIDTH               1
// RFF bitfiled (RO) Reset=0
#define UART_UA3_USR_RFF_MASK                    0x10
#define UART_UA3_USR_RFF_SHIFT                   4 
#define UART_UA3_USR_RFF_BIT                     0x1
#define UART_UA3_USR_RFF_BITWIDTH                1
// reserved bitfiled (RO) Reset=0
#define UART_UA3_USR_RESERVED_MASK               0xFFFFFFE0
#define UART_UA3_USR_RESERVED_SHIFT              5 
#define UART_UA3_USR_RESERVED_BIT                0x7FFFFFF
#define UART_UA3_USR_RESERVED_BITWIDTH           27
// UA3_TFL Register
#define UART_UA3_TFL_OFS                         0x00003080
// TFL bitfiled (RO) Reset=0
#define UART_UA3_TFL_TFL_MASK                    0x1F
#define UART_UA3_TFL_TFL_SHIFT                   0 
#define UART_UA3_TFL_TFL_BIT                     0x1F
#define UART_UA3_TFL_TFL_BITWIDTH                5
// reserved bitfiled (RO) Reset=0
#define UART_UA3_TFL_RESERVED_MASK               0xFFFFFFE0
#define UART_UA3_TFL_RESERVED_SHIFT              5 
#define UART_UA3_TFL_RESERVED_BIT                0x7FFFFFF
#define UART_UA3_TFL_RESERVED_BITWIDTH           27
// UA3_RFL Register
#define UART_UA3_RFL_OFS                         0x00003084
// RFL bitfiled (RO) Reset=0
#define UART_UA3_RFL_RFL_MASK                    0x1F
#define UART_UA3_RFL_RFL_SHIFT                   0 
#define UART_UA3_RFL_RFL_BIT                     0x1F
#define UART_UA3_RFL_RFL_BITWIDTH                5
// reserved bitfiled (RO) Reset=0
#define UART_UA3_RFL_RESERVED_MASK               0xFFFFFFE0
#define UART_UA3_RFL_RESERVED_SHIFT              5 
#define UART_UA3_RFL_RESERVED_BIT                0x7FFFFFF
#define UART_UA3_RFL_RESERVED_BITWIDTH           27
// UA3_HTX Register
#define UART_UA3_HTX_OFS                         0x000030A4
// HTX bitfiled (RW) Reset=0
#define UART_UA3_HTX_HTX_MASK                    0x1
#define UART_UA3_HTX_HTX_SHIFT                   0 
#define UART_UA3_HTX_HTX_BIT                     0x1
#define UART_UA3_HTX_HTX_BITWIDTH                1
// reserved bitfiled (RO) Reset=0
#define UART_UA3_HTX_RESERVED_MASK               0xFFFFFFFE
#define UART_UA3_HTX_RESERVED_SHIFT              1 
#define UART_UA3_HTX_RESERVED_BIT                0x7FFFFFFF
#define UART_UA3_HTX_RESERVED_BITWIDTH           31
// UA3_DMASA Register
#define UART_UA3_DMASA_OFS                       0x000030A8
// DMASA bitfiled (RW) Reset=0
#define UART_UA3_DMASA_DMASA_MASK                0x1
#define UART_UA3_DMASA_DMASA_SHIFT               0 
#define UART_UA3_DMASA_DMASA_BIT                 0x1
#define UART_UA3_DMASA_DMASA_BITWIDTH            1
// reserved bitfiled (RO) Reset=0
#define UART_UA3_DMASA_RESERVED_MASK             0xFFFFFFFE
#define UART_UA3_DMASA_RESERVED_SHIFT            1 
#define UART_UA3_DMASA_RESERVED_BIT              0x7FFFFFFF
#define UART_UA3_DMASA_RESERVED_BITWIDTH         31
// UA3_CPR Register
#define UART_UA3_CPR_OFS                         0x000030F4
// APB_DATA_WIDTH bitfiled (RO) Reset=10
#define UART_UA3_CPR_APB_DATA_WIDTH_MASK         0x3
#define UART_UA3_CPR_APB_DATA_WIDTH_SHIFT        0 
#define UART_UA3_CPR_APB_DATA_WIDTH_BIT          0x3
#define UART_UA3_CPR_APB_DATA_WIDTH_BITWIDTH     2
// reserved3 bitfiled (RO) Reset=0
#define UART_UA3_CPR_RESERVED3_MASK              0xC
#define UART_UA3_CPR_RESERVED3_SHIFT             2 
#define UART_UA3_CPR_RESERVED3_BIT               0x3
#define UART_UA3_CPR_RESERVED3_BITWIDTH          2
// AFCE_MODE bitfiled (RO) Reset=1
#define UART_UA3_CPR_AFCE_MODE_MASK              0x10
#define UART_UA3_CPR_AFCE_MODE_SHIFT             4 
#define UART_UA3_CPR_AFCE_MODE_BIT               0x1
#define UART_UA3_CPR_AFCE_MODE_BITWIDTH          1
// THRE_MODE bitfiled (RO) Reset=1
#define UART_UA3_CPR_THRE_MODE_MASK              0x20
#define UART_UA3_CPR_THRE_MODE_SHIFT             5 
#define UART_UA3_CPR_THRE_MODE_BIT               0x1
#define UART_UA3_CPR_THRE_MODE_BITWIDTH          1
// SIR_MODE bitfiled (RO) Reset=0
#define UART_UA3_CPR_SIR_MODE_MASK               0x40
#define UART_UA3_CPR_SIR_MODE_SHIFT              6 
#define UART_UA3_CPR_SIR_MODE_BIT                0x1
#define UART_UA3_CPR_SIR_MODE_BITWIDTH           1
// SIR_LP_MODE bitfiled (RO) Reset=0
#define UART_UA3_CPR_SIR_LP_MODE_MASK            0x80
#define UART_UA3_CPR_SIR_LP_MODE_SHIFT           7 
#define UART_UA3_CPR_SIR_LP_MODE_BIT             0x1
#define UART_UA3_CPR_SIR_LP_MODE_BITWIDTH        1
// ADDITIONAL_FEAT bitfiled (RO) Reset=1
#define UART_UA3_CPR_ADDITIONAL_FEAT_MASK        0x100
#define UART_UA3_CPR_ADDITIONAL_FEAT_SHIFT       8 
#define UART_UA3_CPR_ADDITIONAL_FEAT_BIT         0x1
#define UART_UA3_CPR_ADDITIONAL_FEAT_BITWIDTH    1
// FIFO_ACCESS bitfiled (RO) Reset=1
#define UART_UA3_CPR_FIFO_ACCESS_MASK            0x200
#define UART_UA3_CPR_FIFO_ACCESS_SHIFT           9 
#define UART_UA3_CPR_FIFO_ACCESS_BIT             0x1
#define UART_UA3_CPR_FIFO_ACCESS_BITWIDTH        1
// FIFO_STAT bitfiled (RO) Reset=1
#define UART_UA3_CPR_FIFO_STAT_MASK              0x400
#define UART_UA3_CPR_FIFO_STAT_SHIFT             10 
#define UART_UA3_CPR_FIFO_STAT_BIT               0x1
#define UART_UA3_CPR_FIFO_STAT_BITWIDTH          1
// SHADOW bitfiled (RO) Reset=0
#define UART_UA3_CPR_SHADOW_MASK                 0x800
#define UART_UA3_CPR_SHADOW_SHIFT                11 
#define UART_UA3_CPR_SHADOW_BIT                  0x1
#define UART_UA3_CPR_SHADOW_BITWIDTH             1
// UART_ADD_ENCODED_PARAMS bitfiled (RO) Reset=1
#define UART_UA3_CPR_UART_ADD_ENCODED_PARAMS_MASK 0x1000
#define UART_UA3_CPR_UART_ADD_ENCODED_PARAMS_SHIFT 12 
#define UART_UA3_CPR_UART_ADD_ENCODED_PARAMS_BIT 0x1
#define UART_UA3_CPR_UART_ADD_ENCODED_PARAMS_BITWIDTH 1
// DMA_EXTRA bitfiled (RO) Reset=1
#define UART_UA3_CPR_DMA_EXTRA_MASK              0x2000
#define UART_UA3_CPR_DMA_EXTRA_SHIFT             13 
#define UART_UA3_CPR_DMA_EXTRA_BIT               0x1
#define UART_UA3_CPR_DMA_EXTRA_BITWIDTH          1
// reserved2 bitfiled (RO) Reset=0
#define UART_UA3_CPR_RESERVED2_MASK              0xC000
#define UART_UA3_CPR_RESERVED2_SHIFT             14 
#define UART_UA3_CPR_RESERVED2_BIT               0x3
#define UART_UA3_CPR_RESERVED2_BITWIDTH          2
// FIFO_MODE bitfiled (RO) Reset=1
#define UART_UA3_CPR_FIFO_MODE_MASK              0xFF0000
#define UART_UA3_CPR_FIFO_MODE_SHIFT             16 
#define UART_UA3_CPR_FIFO_MODE_BIT               0xFF
#define UART_UA3_CPR_FIFO_MODE_BITWIDTH          8
// reserved bitfiled (RO) Reset=0
#define UART_UA3_CPR_RESERVED_MASK               0xFF000000
#define UART_UA3_CPR_RESERVED_SHIFT              24 
#define UART_UA3_CPR_RESERVED_BIT                0xFF
#define UART_UA3_CPR_RESERVED_BITWIDTH           8
// UA3_UCV Register
#define UART_UA3_UCV_OFS                         0x000030F8
// UART_Component_Version bitfiled (RO) Reset=110011001100010011010000101010
#define UART_UA3_UCV_UART_COMPONENT_VERSION_MASK 0xFFFFFFFF
#define UART_UA3_UCV_UART_COMPONENT_VERSION_SHIFT 0 
#define UART_UA3_UCV_UART_COMPONENT_VERSION_BIT  0xFFFFFFFF
#define UART_UA3_UCV_UART_COMPONENT_VERSION_BITWIDTH 32
// UA3_CTR Register
#define UART_UA3_CTR_OFS                         0x000030FC
// Peripheral_ID bitfiled (RO) Reset=1000100010101110000000100010000
#define UART_UA3_CTR_PERIPHERAL_ID_MASK          0xFFFFFFFF
#define UART_UA3_CTR_PERIPHERAL_ID_SHIFT         0 
#define UART_UA3_CTR_PERIPHERAL_ID_BIT           0xFFFFFFFF
#define UART_UA3_CTR_PERIPHERAL_ID_BITWIDTH      32

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _UART_REG_DEF_H */
