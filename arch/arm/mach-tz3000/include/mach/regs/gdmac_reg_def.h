/*
 * arch/arm/mach-tz3000/include/mach/regs/gdmac_reg_def.h
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

#ifndef _GDMAC_REG_DEF_H
#define _GDMAC_REG_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

// GDT0_DSR Register
#define GDMAC_GDT0_DSR_OFS                       0x00000000
// DMA_status bitfiled (RO) Reset=0
#define GDMAC_GDT0_DSR_DMA_STATUS_MASK           0xF
#define GDMAC_GDT0_DSR_DMA_STATUS_SHIFT          0 
#define GDMAC_GDT0_DSR_DMA_STATUS_BIT            0xF
#define GDMAC_GDT0_DSR_DMA_STATUS_BITWIDTH       4
// Wakeup_event bitfiled (RO) Reset=0
#define GDMAC_GDT0_DSR_WAKEUP_EVENT_MASK         0x1F0
#define GDMAC_GDT0_DSR_WAKEUP_EVENT_SHIFT        4 
#define GDMAC_GDT0_DSR_WAKEUP_EVENT_BIT          0x1F
#define GDMAC_GDT0_DSR_WAKEUP_EVENT_BITWIDTH     5
// DSN bitfiled (RO) Reset=1
#define GDMAC_GDT0_DSR_DSN_MASK                  0x200
#define GDMAC_GDT0_DSR_DSN_SHIFT                 9 
#define GDMAC_GDT0_DSR_DSN_BIT                   0x1
#define GDMAC_GDT0_DSR_DSN_BITWIDTH              1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_DSR_RESERVED_MASK             0xFFFFFC00
#define GDMAC_GDT0_DSR_RESERVED_SHIFT            10 
#define GDMAC_GDT0_DSR_RESERVED_BIT              0x3FFFFF
#define GDMAC_GDT0_DSR_RESERVED_BITWIDTH         22
// GDT0_DPC Register
#define GDMAC_GDT0_DPC_OFS                       0x00000004
// pc_mgr bitfiled (RO) Reset=0
#define GDMAC_GDT0_DPC_PC_MGR_MASK               0xFFFFFFFF
#define GDMAC_GDT0_DPC_PC_MGR_SHIFT              0 
#define GDMAC_GDT0_DPC_PC_MGR_BIT                0xFFFFFFFF
#define GDMAC_GDT0_DPC_PC_MGR_BITWIDTH           32
// GDT0_INTEN Register
#define GDMAC_GDT0_INTEN_OFS                     0x00000020
// event_irq_select bitfiled (RW) Reset=0
#define GDMAC_GDT0_INTEN_EVENT_IRQ_SELECT_MASK   0xFFFFFFFF
#define GDMAC_GDT0_INTEN_EVENT_IRQ_SELECT_SHIFT  0 
#define GDMAC_GDT0_INTEN_EVENT_IRQ_SELECT_BIT    0xFFFFFFFF
#define GDMAC_GDT0_INTEN_EVENT_IRQ_SELECT_BITWIDTH 32
// GDT0_INT_EVENT_RIS Register
#define GDMAC_GDT0_INT_EVENT_RIS_OFS             0x00000024
// DMASEV bitfiled (RO) Reset=0
#define GDMAC_GDT0_INT_EVENT_RIS_DMASEV_MASK     0xFFFFFFFF
#define GDMAC_GDT0_INT_EVENT_RIS_DMASEV_SHIFT    0 
#define GDMAC_GDT0_INT_EVENT_RIS_DMASEV_BIT      0xFFFFFFFF
#define GDMAC_GDT0_INT_EVENT_RIS_DMASEV_BITWIDTH 32
// GDT0_INTMIS Register
#define GDMAC_GDT0_INTMIS_OFS                    0x00000028
// irq_status bitfiled (RO) Reset=0
#define GDMAC_GDT0_INTMIS_IRQ_STATUS_MASK        0xFFFFFFFF
#define GDMAC_GDT0_INTMIS_IRQ_STATUS_SHIFT       0 
#define GDMAC_GDT0_INTMIS_IRQ_STATUS_BIT         0xFFFFFFFF
#define GDMAC_GDT0_INTMIS_IRQ_STATUS_BITWIDTH    32
// GDT0_INTCLR Register
#define GDMAC_GDT0_INTCLR_OFS                    0x0000002C
// irq_clr bitfiled (RW) Reset=0
#define GDMAC_GDT0_INTCLR_IRQ_CLR_MASK           0xFFFFFFFF
#define GDMAC_GDT0_INTCLR_IRQ_CLR_SHIFT          0 
#define GDMAC_GDT0_INTCLR_IRQ_CLR_BIT            0xFFFFFFFF
#define GDMAC_GDT0_INTCLR_IRQ_CLR_BITWIDTH       32
// GDT0_FSRD Register
#define GDMAC_GDT0_FSRD_OFS                      0x00000030
// fs_mgr bitfiled (RO) Reset=0
#define GDMAC_GDT0_FSRD_FS_MGR_MASK              0x1
#define GDMAC_GDT0_FSRD_FS_MGR_SHIFT             0 
#define GDMAC_GDT0_FSRD_FS_MGR_BIT               0x1
#define GDMAC_GDT0_FSRD_FS_MGR_BITWIDTH          1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_FSRD_RESERVED_MASK            0xFFFFFFFE
#define GDMAC_GDT0_FSRD_RESERVED_SHIFT           1 
#define GDMAC_GDT0_FSRD_RESERVED_BIT             0x7FFFFFFF
#define GDMAC_GDT0_FSRD_RESERVED_BITWIDTH        31
// GDT0_FSRC Register
#define GDMAC_GDT0_FSRC_OFS                      0x00000034
// fault_status bitfiled (RO) Reset=0
#define GDMAC_GDT0_FSRC_FAULT_STATUS_MASK        0xFF
#define GDMAC_GDT0_FSRC_FAULT_STATUS_SHIFT       0 
#define GDMAC_GDT0_FSRC_FAULT_STATUS_BIT         0xFF
#define GDMAC_GDT0_FSRC_FAULT_STATUS_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_FSRC_RESERVED_MASK            0xFFFFFF00
#define GDMAC_GDT0_FSRC_RESERVED_SHIFT           8 
#define GDMAC_GDT0_FSRC_RESERVED_BIT             0xFFFFFF
#define GDMAC_GDT0_FSRC_RESERVED_BITWIDTH        24
// GDT0_FTRD Register
#define GDMAC_GDT0_FTRD_OFS                      0x00000038
// undef_instr bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTRD_UNDEF_INSTR_MASK         0x1
#define GDMAC_GDT0_FTRD_UNDEF_INSTR_SHIFT        0 
#define GDMAC_GDT0_FTRD_UNDEF_INSTR_BIT          0x1
#define GDMAC_GDT0_FTRD_UNDEF_INSTR_BITWIDTH     1
// operand_invalid bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTRD_OPERAND_INVALID_MASK     0x2
#define GDMAC_GDT0_FTRD_OPERAND_INVALID_SHIFT    1 
#define GDMAC_GDT0_FTRD_OPERAND_INVALID_BIT      0x1
#define GDMAC_GDT0_FTRD_OPERAND_INVALID_BITWIDTH 1
// reserved4 bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTRD_RESERVED4_MASK           0xC
#define GDMAC_GDT0_FTRD_RESERVED4_SHIFT          2 
#define GDMAC_GDT0_FTRD_RESERVED4_BIT            0x3
#define GDMAC_GDT0_FTRD_RESERVED4_BITWIDTH       2
// dmago_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTRD_DMAGO_ERR_MASK           0x10
#define GDMAC_GDT0_FTRD_DMAGO_ERR_SHIFT          4 
#define GDMAC_GDT0_FTRD_DMAGO_ERR_BIT            0x1
#define GDMAC_GDT0_FTRD_DMAGO_ERR_BITWIDTH       1
// mgr_evnt_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTRD_MGR_EVNT_ERR_MASK        0x20
#define GDMAC_GDT0_FTRD_MGR_EVNT_ERR_SHIFT       5 
#define GDMAC_GDT0_FTRD_MGR_EVNT_ERR_BIT         0x1
#define GDMAC_GDT0_FTRD_MGR_EVNT_ERR_BITWIDTH    1
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTRD_RESERVED3_MASK           0xFFC0
#define GDMAC_GDT0_FTRD_RESERVED3_SHIFT          6 
#define GDMAC_GDT0_FTRD_RESERVED3_BIT            0x3FF
#define GDMAC_GDT0_FTRD_RESERVED3_BITWIDTH       10
// instr_fetch_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTRD_INSTR_FETCH_ERR_MASK     0x10000
#define GDMAC_GDT0_FTRD_INSTR_FETCH_ERR_SHIFT    16 
#define GDMAC_GDT0_FTRD_INSTR_FETCH_ERR_BIT      0x1
#define GDMAC_GDT0_FTRD_INSTR_FETCH_ERR_BITWIDTH 1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTRD_RESERVED2_MASK           0x3FFE0000
#define GDMAC_GDT0_FTRD_RESERVED2_SHIFT          17 
#define GDMAC_GDT0_FTRD_RESERVED2_BIT            0x1FFF
#define GDMAC_GDT0_FTRD_RESERVED2_BITWIDTH       13
// dbg_instr bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTRD_DBG_INSTR_MASK           0x40000000
#define GDMAC_GDT0_FTRD_DBG_INSTR_SHIFT          30 
#define GDMAC_GDT0_FTRD_DBG_INSTR_BIT            0x1
#define GDMAC_GDT0_FTRD_DBG_INSTR_BITWIDTH       1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTRD_RESERVED_MASK            0x80000000
#define GDMAC_GDT0_FTRD_RESERVED_SHIFT           31 
#define GDMAC_GDT0_FTRD_RESERVED_BIT             0x1
#define GDMAC_GDT0_FTRD_RESERVED_BITWIDTH        1
// GDT0_FTR0 Register
#define GDMAC_GDT0_FTR0_OFS                      0x00000040
// undef_instr bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR0_UNDEF_INSTR_MASK         0x1
#define GDMAC_GDT0_FTR0_UNDEF_INSTR_SHIFT        0 
#define GDMAC_GDT0_FTR0_UNDEF_INSTR_BIT          0x1
#define GDMAC_GDT0_FTR0_UNDEF_INSTR_BITWIDTH     1
// operand_invalid bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR0_OPERAND_INVALID_MASK     0x2
#define GDMAC_GDT0_FTR0_OPERAND_INVALID_SHIFT    1 
#define GDMAC_GDT0_FTR0_OPERAND_INVALID_BIT      0x1
#define GDMAC_GDT0_FTR0_OPERAND_INVALID_BITWIDTH 1
// reserved4 bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR0_RESERVED4_MASK           0x1C
#define GDMAC_GDT0_FTR0_RESERVED4_SHIFT          2 
#define GDMAC_GDT0_FTR0_RESERVED4_BIT            0x7
#define GDMAC_GDT0_FTR0_RESERVED4_BITWIDTH       3
// ch_evnt_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR0_CH_EVNT_ERR_MASK         0x20
#define GDMAC_GDT0_FTR0_CH_EVNT_ERR_SHIFT        5 
#define GDMAC_GDT0_FTR0_CH_EVNT_ERR_BIT          0x1
#define GDMAC_GDT0_FTR0_CH_EVNT_ERR_BITWIDTH     1
// ch_periph_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR0_CH_PERIPH_ERR_MASK       0x40
#define GDMAC_GDT0_FTR0_CH_PERIPH_ERR_SHIFT      6 
#define GDMAC_GDT0_FTR0_CH_PERIPH_ERR_BIT        0x1
#define GDMAC_GDT0_FTR0_CH_PERIPH_ERR_BITWIDTH   1
// ch_rdwr_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR0_CH_RDWR_ERR_MASK         0x80
#define GDMAC_GDT0_FTR0_CH_RDWR_ERR_SHIFT        7 
#define GDMAC_GDT0_FTR0_CH_RDWR_ERR_BIT          0x1
#define GDMAC_GDT0_FTR0_CH_RDWR_ERR_BITWIDTH     1
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR0_RESERVED3_MASK           0xF00
#define GDMAC_GDT0_FTR0_RESERVED3_SHIFT          8 
#define GDMAC_GDT0_FTR0_RESERVED3_BIT            0xF
#define GDMAC_GDT0_FTR0_RESERVED3_BITWIDTH       4
// mfifo_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR0_MFIFO_ERR_MASK           0x1000
#define GDMAC_GDT0_FTR0_MFIFO_ERR_SHIFT          12 
#define GDMAC_GDT0_FTR0_MFIFO_ERR_BIT            0x1
#define GDMAC_GDT0_FTR0_MFIFO_ERR_BITWIDTH       1
// st_data_unavailable bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR0_ST_DATA_UNAVAILABLE_MASK 0x2000
#define GDMAC_GDT0_FTR0_ST_DATA_UNAVAILABLE_SHIFT 13 
#define GDMAC_GDT0_FTR0_ST_DATA_UNAVAILABLE_BIT  0x1
#define GDMAC_GDT0_FTR0_ST_DATA_UNAVAILABLE_BITWIDTH 1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR0_RESERVED2_MASK           0xC000
#define GDMAC_GDT0_FTR0_RESERVED2_SHIFT          14 
#define GDMAC_GDT0_FTR0_RESERVED2_BIT            0x3
#define GDMAC_GDT0_FTR0_RESERVED2_BITWIDTH       2
// instr_fetch_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR0_INSTR_FETCH_ERR_MASK     0x10000
#define GDMAC_GDT0_FTR0_INSTR_FETCH_ERR_SHIFT    16 
#define GDMAC_GDT0_FTR0_INSTR_FETCH_ERR_BIT      0x1
#define GDMAC_GDT0_FTR0_INSTR_FETCH_ERR_BITWIDTH 1
// data_write_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR0_DATA_WRITE_ERR_MASK      0x20000
#define GDMAC_GDT0_FTR0_DATA_WRITE_ERR_SHIFT     17 
#define GDMAC_GDT0_FTR0_DATA_WRITE_ERR_BIT       0x1
#define GDMAC_GDT0_FTR0_DATA_WRITE_ERR_BITWIDTH  1
// data_read_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR0_DATA_READ_ERR_MASK       0x40000
#define GDMAC_GDT0_FTR0_DATA_READ_ERR_SHIFT      18 
#define GDMAC_GDT0_FTR0_DATA_READ_ERR_BIT        0x1
#define GDMAC_GDT0_FTR0_DATA_READ_ERR_BITWIDTH   1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR0_RESERVED_MASK            0x3FF80000
#define GDMAC_GDT0_FTR0_RESERVED_SHIFT           19 
#define GDMAC_GDT0_FTR0_RESERVED_BIT             0x7FF
#define GDMAC_GDT0_FTR0_RESERVED_BITWIDTH        11
// dbg_instr bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR0_DBG_INSTR_MASK           0x40000000
#define GDMAC_GDT0_FTR0_DBG_INSTR_SHIFT          30 
#define GDMAC_GDT0_FTR0_DBG_INSTR_BIT            0x1
#define GDMAC_GDT0_FTR0_DBG_INSTR_BITWIDTH       1
// lockup_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR0_LOCKUP_ERR_MASK          0x80000000
#define GDMAC_GDT0_FTR0_LOCKUP_ERR_SHIFT         31 
#define GDMAC_GDT0_FTR0_LOCKUP_ERR_BIT           0x1
#define GDMAC_GDT0_FTR0_LOCKUP_ERR_BITWIDTH      1
// GDT0_FTR1 Register
#define GDMAC_GDT0_FTR1_OFS                      0x00000044
// undef_instr bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR1_UNDEF_INSTR_MASK         0x1
#define GDMAC_GDT0_FTR1_UNDEF_INSTR_SHIFT        0 
#define GDMAC_GDT0_FTR1_UNDEF_INSTR_BIT          0x1
#define GDMAC_GDT0_FTR1_UNDEF_INSTR_BITWIDTH     1
// operand_invalid bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR1_OPERAND_INVALID_MASK     0x2
#define GDMAC_GDT0_FTR1_OPERAND_INVALID_SHIFT    1 
#define GDMAC_GDT0_FTR1_OPERAND_INVALID_BIT      0x1
#define GDMAC_GDT0_FTR1_OPERAND_INVALID_BITWIDTH 1
// reserved4 bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR1_RESERVED4_MASK           0x1C
#define GDMAC_GDT0_FTR1_RESERVED4_SHIFT          2 
#define GDMAC_GDT0_FTR1_RESERVED4_BIT            0x7
#define GDMAC_GDT0_FTR1_RESERVED4_BITWIDTH       3
// ch_evnt_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR1_CH_EVNT_ERR_MASK         0x20
#define GDMAC_GDT0_FTR1_CH_EVNT_ERR_SHIFT        5 
#define GDMAC_GDT0_FTR1_CH_EVNT_ERR_BIT          0x1
#define GDMAC_GDT0_FTR1_CH_EVNT_ERR_BITWIDTH     1
// ch_periph_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR1_CH_PERIPH_ERR_MASK       0x40
#define GDMAC_GDT0_FTR1_CH_PERIPH_ERR_SHIFT      6 
#define GDMAC_GDT0_FTR1_CH_PERIPH_ERR_BIT        0x1
#define GDMAC_GDT0_FTR1_CH_PERIPH_ERR_BITWIDTH   1
// ch_rdwr_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR1_CH_RDWR_ERR_MASK         0x80
#define GDMAC_GDT0_FTR1_CH_RDWR_ERR_SHIFT        7 
#define GDMAC_GDT0_FTR1_CH_RDWR_ERR_BIT          0x1
#define GDMAC_GDT0_FTR1_CH_RDWR_ERR_BITWIDTH     1
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR1_RESERVED3_MASK           0xF00
#define GDMAC_GDT0_FTR1_RESERVED3_SHIFT          8 
#define GDMAC_GDT0_FTR1_RESERVED3_BIT            0xF
#define GDMAC_GDT0_FTR1_RESERVED3_BITWIDTH       4
// mfifo_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR1_MFIFO_ERR_MASK           0x1000
#define GDMAC_GDT0_FTR1_MFIFO_ERR_SHIFT          12 
#define GDMAC_GDT0_FTR1_MFIFO_ERR_BIT            0x1
#define GDMAC_GDT0_FTR1_MFIFO_ERR_BITWIDTH       1
// st_data_unavailable bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR1_ST_DATA_UNAVAILABLE_MASK 0x2000
#define GDMAC_GDT0_FTR1_ST_DATA_UNAVAILABLE_SHIFT 13 
#define GDMAC_GDT0_FTR1_ST_DATA_UNAVAILABLE_BIT  0x1
#define GDMAC_GDT0_FTR1_ST_DATA_UNAVAILABLE_BITWIDTH 1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR1_RESERVED2_MASK           0xC000
#define GDMAC_GDT0_FTR1_RESERVED2_SHIFT          14 
#define GDMAC_GDT0_FTR1_RESERVED2_BIT            0x3
#define GDMAC_GDT0_FTR1_RESERVED2_BITWIDTH       2
// instr_fetch_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR1_INSTR_FETCH_ERR_MASK     0x10000
#define GDMAC_GDT0_FTR1_INSTR_FETCH_ERR_SHIFT    16 
#define GDMAC_GDT0_FTR1_INSTR_FETCH_ERR_BIT      0x1
#define GDMAC_GDT0_FTR1_INSTR_FETCH_ERR_BITWIDTH 1
// data_write_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR1_DATA_WRITE_ERR_MASK      0x20000
#define GDMAC_GDT0_FTR1_DATA_WRITE_ERR_SHIFT     17 
#define GDMAC_GDT0_FTR1_DATA_WRITE_ERR_BIT       0x1
#define GDMAC_GDT0_FTR1_DATA_WRITE_ERR_BITWIDTH  1
// data_read_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR1_DATA_READ_ERR_MASK       0x40000
#define GDMAC_GDT0_FTR1_DATA_READ_ERR_SHIFT      18 
#define GDMAC_GDT0_FTR1_DATA_READ_ERR_BIT        0x1
#define GDMAC_GDT0_FTR1_DATA_READ_ERR_BITWIDTH   1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR1_RESERVED_MASK            0x3FF80000
#define GDMAC_GDT0_FTR1_RESERVED_SHIFT           19 
#define GDMAC_GDT0_FTR1_RESERVED_BIT             0x7FF
#define GDMAC_GDT0_FTR1_RESERVED_BITWIDTH        11
// dbg_instr bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR1_DBG_INSTR_MASK           0x40000000
#define GDMAC_GDT0_FTR1_DBG_INSTR_SHIFT          30 
#define GDMAC_GDT0_FTR1_DBG_INSTR_BIT            0x1
#define GDMAC_GDT0_FTR1_DBG_INSTR_BITWIDTH       1
// lockup_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR1_LOCKUP_ERR_MASK          0x80000000
#define GDMAC_GDT0_FTR1_LOCKUP_ERR_SHIFT         31 
#define GDMAC_GDT0_FTR1_LOCKUP_ERR_BIT           0x1
#define GDMAC_GDT0_FTR1_LOCKUP_ERR_BITWIDTH      1
// GDT0_FTR2 Register
#define GDMAC_GDT0_FTR2_OFS                      0x00000048
// undef_instr bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR2_UNDEF_INSTR_MASK         0x1
#define GDMAC_GDT0_FTR2_UNDEF_INSTR_SHIFT        0 
#define GDMAC_GDT0_FTR2_UNDEF_INSTR_BIT          0x1
#define GDMAC_GDT0_FTR2_UNDEF_INSTR_BITWIDTH     1
// operand_invalid bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR2_OPERAND_INVALID_MASK     0x2
#define GDMAC_GDT0_FTR2_OPERAND_INVALID_SHIFT    1 
#define GDMAC_GDT0_FTR2_OPERAND_INVALID_BIT      0x1
#define GDMAC_GDT0_FTR2_OPERAND_INVALID_BITWIDTH 1
// reserved4 bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR2_RESERVED4_MASK           0x1C
#define GDMAC_GDT0_FTR2_RESERVED4_SHIFT          2 
#define GDMAC_GDT0_FTR2_RESERVED4_BIT            0x7
#define GDMAC_GDT0_FTR2_RESERVED4_BITWIDTH       3
// ch_evnt_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR2_CH_EVNT_ERR_MASK         0x20
#define GDMAC_GDT0_FTR2_CH_EVNT_ERR_SHIFT        5 
#define GDMAC_GDT0_FTR2_CH_EVNT_ERR_BIT          0x1
#define GDMAC_GDT0_FTR2_CH_EVNT_ERR_BITWIDTH     1
// ch_periph_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR2_CH_PERIPH_ERR_MASK       0x40
#define GDMAC_GDT0_FTR2_CH_PERIPH_ERR_SHIFT      6 
#define GDMAC_GDT0_FTR2_CH_PERIPH_ERR_BIT        0x1
#define GDMAC_GDT0_FTR2_CH_PERIPH_ERR_BITWIDTH   1
// ch_rdwr_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR2_CH_RDWR_ERR_MASK         0x80
#define GDMAC_GDT0_FTR2_CH_RDWR_ERR_SHIFT        7 
#define GDMAC_GDT0_FTR2_CH_RDWR_ERR_BIT          0x1
#define GDMAC_GDT0_FTR2_CH_RDWR_ERR_BITWIDTH     1
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR2_RESERVED3_MASK           0xF00
#define GDMAC_GDT0_FTR2_RESERVED3_SHIFT          8 
#define GDMAC_GDT0_FTR2_RESERVED3_BIT            0xF
#define GDMAC_GDT0_FTR2_RESERVED3_BITWIDTH       4
// mfifo_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR2_MFIFO_ERR_MASK           0x1000
#define GDMAC_GDT0_FTR2_MFIFO_ERR_SHIFT          12 
#define GDMAC_GDT0_FTR2_MFIFO_ERR_BIT            0x1
#define GDMAC_GDT0_FTR2_MFIFO_ERR_BITWIDTH       1
// st_data_unavailable bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR2_ST_DATA_UNAVAILABLE_MASK 0x2000
#define GDMAC_GDT0_FTR2_ST_DATA_UNAVAILABLE_SHIFT 13 
#define GDMAC_GDT0_FTR2_ST_DATA_UNAVAILABLE_BIT  0x1
#define GDMAC_GDT0_FTR2_ST_DATA_UNAVAILABLE_BITWIDTH 1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR2_RESERVED2_MASK           0xC000
#define GDMAC_GDT0_FTR2_RESERVED2_SHIFT          14 
#define GDMAC_GDT0_FTR2_RESERVED2_BIT            0x3
#define GDMAC_GDT0_FTR2_RESERVED2_BITWIDTH       2
// instr_fetch_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR2_INSTR_FETCH_ERR_MASK     0x10000
#define GDMAC_GDT0_FTR2_INSTR_FETCH_ERR_SHIFT    16 
#define GDMAC_GDT0_FTR2_INSTR_FETCH_ERR_BIT      0x1
#define GDMAC_GDT0_FTR2_INSTR_FETCH_ERR_BITWIDTH 1
// data_write_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR2_DATA_WRITE_ERR_MASK      0x20000
#define GDMAC_GDT0_FTR2_DATA_WRITE_ERR_SHIFT     17 
#define GDMAC_GDT0_FTR2_DATA_WRITE_ERR_BIT       0x1
#define GDMAC_GDT0_FTR2_DATA_WRITE_ERR_BITWIDTH  1
// data_read_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR2_DATA_READ_ERR_MASK       0x40000
#define GDMAC_GDT0_FTR2_DATA_READ_ERR_SHIFT      18 
#define GDMAC_GDT0_FTR2_DATA_READ_ERR_BIT        0x1
#define GDMAC_GDT0_FTR2_DATA_READ_ERR_BITWIDTH   1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR2_RESERVED_MASK            0x3FF80000
#define GDMAC_GDT0_FTR2_RESERVED_SHIFT           19 
#define GDMAC_GDT0_FTR2_RESERVED_BIT             0x7FF
#define GDMAC_GDT0_FTR2_RESERVED_BITWIDTH        11
// dbg_instr bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR2_DBG_INSTR_MASK           0x40000000
#define GDMAC_GDT0_FTR2_DBG_INSTR_SHIFT          30 
#define GDMAC_GDT0_FTR2_DBG_INSTR_BIT            0x1
#define GDMAC_GDT0_FTR2_DBG_INSTR_BITWIDTH       1
// lockup_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR2_LOCKUP_ERR_MASK          0x80000000
#define GDMAC_GDT0_FTR2_LOCKUP_ERR_SHIFT         31 
#define GDMAC_GDT0_FTR2_LOCKUP_ERR_BIT           0x1
#define GDMAC_GDT0_FTR2_LOCKUP_ERR_BITWIDTH      1
// GDT0_FTR3 Register
#define GDMAC_GDT0_FTR3_OFS                      0x0000004C
// undef_instr bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR3_UNDEF_INSTR_MASK         0x1
#define GDMAC_GDT0_FTR3_UNDEF_INSTR_SHIFT        0 
#define GDMAC_GDT0_FTR3_UNDEF_INSTR_BIT          0x1
#define GDMAC_GDT0_FTR3_UNDEF_INSTR_BITWIDTH     1
// operand_invalid bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR3_OPERAND_INVALID_MASK     0x2
#define GDMAC_GDT0_FTR3_OPERAND_INVALID_SHIFT    1 
#define GDMAC_GDT0_FTR3_OPERAND_INVALID_BIT      0x1
#define GDMAC_GDT0_FTR3_OPERAND_INVALID_BITWIDTH 1
// reserved4 bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR3_RESERVED4_MASK           0x1C
#define GDMAC_GDT0_FTR3_RESERVED4_SHIFT          2 
#define GDMAC_GDT0_FTR3_RESERVED4_BIT            0x7
#define GDMAC_GDT0_FTR3_RESERVED4_BITWIDTH       3
// ch_evnt_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR3_CH_EVNT_ERR_MASK         0x20
#define GDMAC_GDT0_FTR3_CH_EVNT_ERR_SHIFT        5 
#define GDMAC_GDT0_FTR3_CH_EVNT_ERR_BIT          0x1
#define GDMAC_GDT0_FTR3_CH_EVNT_ERR_BITWIDTH     1
// ch_periph_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR3_CH_PERIPH_ERR_MASK       0x40
#define GDMAC_GDT0_FTR3_CH_PERIPH_ERR_SHIFT      6 
#define GDMAC_GDT0_FTR3_CH_PERIPH_ERR_BIT        0x1
#define GDMAC_GDT0_FTR3_CH_PERIPH_ERR_BITWIDTH   1
// ch_rdwr_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR3_CH_RDWR_ERR_MASK         0x80
#define GDMAC_GDT0_FTR3_CH_RDWR_ERR_SHIFT        7 
#define GDMAC_GDT0_FTR3_CH_RDWR_ERR_BIT          0x1
#define GDMAC_GDT0_FTR3_CH_RDWR_ERR_BITWIDTH     1
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR3_RESERVED3_MASK           0xF00
#define GDMAC_GDT0_FTR3_RESERVED3_SHIFT          8 
#define GDMAC_GDT0_FTR3_RESERVED3_BIT            0xF
#define GDMAC_GDT0_FTR3_RESERVED3_BITWIDTH       4
// mfifo_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR3_MFIFO_ERR_MASK           0x1000
#define GDMAC_GDT0_FTR3_MFIFO_ERR_SHIFT          12 
#define GDMAC_GDT0_FTR3_MFIFO_ERR_BIT            0x1
#define GDMAC_GDT0_FTR3_MFIFO_ERR_BITWIDTH       1
// st_data_unavailable bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR3_ST_DATA_UNAVAILABLE_MASK 0x2000
#define GDMAC_GDT0_FTR3_ST_DATA_UNAVAILABLE_SHIFT 13 
#define GDMAC_GDT0_FTR3_ST_DATA_UNAVAILABLE_BIT  0x1
#define GDMAC_GDT0_FTR3_ST_DATA_UNAVAILABLE_BITWIDTH 1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR3_RESERVED2_MASK           0xC000
#define GDMAC_GDT0_FTR3_RESERVED2_SHIFT          14 
#define GDMAC_GDT0_FTR3_RESERVED2_BIT            0x3
#define GDMAC_GDT0_FTR3_RESERVED2_BITWIDTH       2
// instr_fetch_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR3_INSTR_FETCH_ERR_MASK     0x10000
#define GDMAC_GDT0_FTR3_INSTR_FETCH_ERR_SHIFT    16 
#define GDMAC_GDT0_FTR3_INSTR_FETCH_ERR_BIT      0x1
#define GDMAC_GDT0_FTR3_INSTR_FETCH_ERR_BITWIDTH 1
// data_write_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR3_DATA_WRITE_ERR_MASK      0x20000
#define GDMAC_GDT0_FTR3_DATA_WRITE_ERR_SHIFT     17 
#define GDMAC_GDT0_FTR3_DATA_WRITE_ERR_BIT       0x1
#define GDMAC_GDT0_FTR3_DATA_WRITE_ERR_BITWIDTH  1
// data_read_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR3_DATA_READ_ERR_MASK       0x40000
#define GDMAC_GDT0_FTR3_DATA_READ_ERR_SHIFT      18 
#define GDMAC_GDT0_FTR3_DATA_READ_ERR_BIT        0x1
#define GDMAC_GDT0_FTR3_DATA_READ_ERR_BITWIDTH   1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR3_RESERVED_MASK            0x3FF80000
#define GDMAC_GDT0_FTR3_RESERVED_SHIFT           19 
#define GDMAC_GDT0_FTR3_RESERVED_BIT             0x7FF
#define GDMAC_GDT0_FTR3_RESERVED_BITWIDTH        11
// dbg_instr bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR3_DBG_INSTR_MASK           0x40000000
#define GDMAC_GDT0_FTR3_DBG_INSTR_SHIFT          30 
#define GDMAC_GDT0_FTR3_DBG_INSTR_BIT            0x1
#define GDMAC_GDT0_FTR3_DBG_INSTR_BITWIDTH       1
// lockup_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR3_LOCKUP_ERR_MASK          0x80000000
#define GDMAC_GDT0_FTR3_LOCKUP_ERR_SHIFT         31 
#define GDMAC_GDT0_FTR3_LOCKUP_ERR_BIT           0x1
#define GDMAC_GDT0_FTR3_LOCKUP_ERR_BITWIDTH      1
// GDT0_FTR4 Register
#define GDMAC_GDT0_FTR4_OFS                      0x00000050
// undef_instr bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR4_UNDEF_INSTR_MASK         0x1
#define GDMAC_GDT0_FTR4_UNDEF_INSTR_SHIFT        0 
#define GDMAC_GDT0_FTR4_UNDEF_INSTR_BIT          0x1
#define GDMAC_GDT0_FTR4_UNDEF_INSTR_BITWIDTH     1
// operand_invalid bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR4_OPERAND_INVALID_MASK     0x2
#define GDMAC_GDT0_FTR4_OPERAND_INVALID_SHIFT    1 
#define GDMAC_GDT0_FTR4_OPERAND_INVALID_BIT      0x1
#define GDMAC_GDT0_FTR4_OPERAND_INVALID_BITWIDTH 1
// reserved4 bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR4_RESERVED4_MASK           0x1C
#define GDMAC_GDT0_FTR4_RESERVED4_SHIFT          2 
#define GDMAC_GDT0_FTR4_RESERVED4_BIT            0x7
#define GDMAC_GDT0_FTR4_RESERVED4_BITWIDTH       3
// ch_evnt_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR4_CH_EVNT_ERR_MASK         0x20
#define GDMAC_GDT0_FTR4_CH_EVNT_ERR_SHIFT        5 
#define GDMAC_GDT0_FTR4_CH_EVNT_ERR_BIT          0x1
#define GDMAC_GDT0_FTR4_CH_EVNT_ERR_BITWIDTH     1
// ch_periph_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR4_CH_PERIPH_ERR_MASK       0x40
#define GDMAC_GDT0_FTR4_CH_PERIPH_ERR_SHIFT      6 
#define GDMAC_GDT0_FTR4_CH_PERIPH_ERR_BIT        0x1
#define GDMAC_GDT0_FTR4_CH_PERIPH_ERR_BITWIDTH   1
// ch_rdwr_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR4_CH_RDWR_ERR_MASK         0x80
#define GDMAC_GDT0_FTR4_CH_RDWR_ERR_SHIFT        7 
#define GDMAC_GDT0_FTR4_CH_RDWR_ERR_BIT          0x1
#define GDMAC_GDT0_FTR4_CH_RDWR_ERR_BITWIDTH     1
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR4_RESERVED3_MASK           0xF00
#define GDMAC_GDT0_FTR4_RESERVED3_SHIFT          8 
#define GDMAC_GDT0_FTR4_RESERVED3_BIT            0xF
#define GDMAC_GDT0_FTR4_RESERVED3_BITWIDTH       4
// mfifo_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR4_MFIFO_ERR_MASK           0x1000
#define GDMAC_GDT0_FTR4_MFIFO_ERR_SHIFT          12 
#define GDMAC_GDT0_FTR4_MFIFO_ERR_BIT            0x1
#define GDMAC_GDT0_FTR4_MFIFO_ERR_BITWIDTH       1
// st_data_unavailable bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR4_ST_DATA_UNAVAILABLE_MASK 0x2000
#define GDMAC_GDT0_FTR4_ST_DATA_UNAVAILABLE_SHIFT 13 
#define GDMAC_GDT0_FTR4_ST_DATA_UNAVAILABLE_BIT  0x1
#define GDMAC_GDT0_FTR4_ST_DATA_UNAVAILABLE_BITWIDTH 1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR4_RESERVED2_MASK           0xC000
#define GDMAC_GDT0_FTR4_RESERVED2_SHIFT          14 
#define GDMAC_GDT0_FTR4_RESERVED2_BIT            0x3
#define GDMAC_GDT0_FTR4_RESERVED2_BITWIDTH       2
// instr_fetch_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR4_INSTR_FETCH_ERR_MASK     0x10000
#define GDMAC_GDT0_FTR4_INSTR_FETCH_ERR_SHIFT    16 
#define GDMAC_GDT0_FTR4_INSTR_FETCH_ERR_BIT      0x1
#define GDMAC_GDT0_FTR4_INSTR_FETCH_ERR_BITWIDTH 1
// data_write_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR4_DATA_WRITE_ERR_MASK      0x20000
#define GDMAC_GDT0_FTR4_DATA_WRITE_ERR_SHIFT     17 
#define GDMAC_GDT0_FTR4_DATA_WRITE_ERR_BIT       0x1
#define GDMAC_GDT0_FTR4_DATA_WRITE_ERR_BITWIDTH  1
// data_read_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR4_DATA_READ_ERR_MASK       0x40000
#define GDMAC_GDT0_FTR4_DATA_READ_ERR_SHIFT      18 
#define GDMAC_GDT0_FTR4_DATA_READ_ERR_BIT        0x1
#define GDMAC_GDT0_FTR4_DATA_READ_ERR_BITWIDTH   1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR4_RESERVED_MASK            0x3FF80000
#define GDMAC_GDT0_FTR4_RESERVED_SHIFT           19 
#define GDMAC_GDT0_FTR4_RESERVED_BIT             0x7FF
#define GDMAC_GDT0_FTR4_RESERVED_BITWIDTH        11
// dbg_instr bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR4_DBG_INSTR_MASK           0x40000000
#define GDMAC_GDT0_FTR4_DBG_INSTR_SHIFT          30 
#define GDMAC_GDT0_FTR4_DBG_INSTR_BIT            0x1
#define GDMAC_GDT0_FTR4_DBG_INSTR_BITWIDTH       1
// lockup_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR4_LOCKUP_ERR_MASK          0x80000000
#define GDMAC_GDT0_FTR4_LOCKUP_ERR_SHIFT         31 
#define GDMAC_GDT0_FTR4_LOCKUP_ERR_BIT           0x1
#define GDMAC_GDT0_FTR4_LOCKUP_ERR_BITWIDTH      1
// GDT0_FTR5 Register
#define GDMAC_GDT0_FTR5_OFS                      0x00000054
// undef_instr bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR5_UNDEF_INSTR_MASK         0x1
#define GDMAC_GDT0_FTR5_UNDEF_INSTR_SHIFT        0 
#define GDMAC_GDT0_FTR5_UNDEF_INSTR_BIT          0x1
#define GDMAC_GDT0_FTR5_UNDEF_INSTR_BITWIDTH     1
// operand_invalid bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR5_OPERAND_INVALID_MASK     0x2
#define GDMAC_GDT0_FTR5_OPERAND_INVALID_SHIFT    1 
#define GDMAC_GDT0_FTR5_OPERAND_INVALID_BIT      0x1
#define GDMAC_GDT0_FTR5_OPERAND_INVALID_BITWIDTH 1
// reserved4 bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR5_RESERVED4_MASK           0x1C
#define GDMAC_GDT0_FTR5_RESERVED4_SHIFT          2 
#define GDMAC_GDT0_FTR5_RESERVED4_BIT            0x7
#define GDMAC_GDT0_FTR5_RESERVED4_BITWIDTH       3
// ch_evnt_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR5_CH_EVNT_ERR_MASK         0x20
#define GDMAC_GDT0_FTR5_CH_EVNT_ERR_SHIFT        5 
#define GDMAC_GDT0_FTR5_CH_EVNT_ERR_BIT          0x1
#define GDMAC_GDT0_FTR5_CH_EVNT_ERR_BITWIDTH     1
// ch_periph_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR5_CH_PERIPH_ERR_MASK       0x40
#define GDMAC_GDT0_FTR5_CH_PERIPH_ERR_SHIFT      6 
#define GDMAC_GDT0_FTR5_CH_PERIPH_ERR_BIT        0x1
#define GDMAC_GDT0_FTR5_CH_PERIPH_ERR_BITWIDTH   1
// ch_rdwr_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR5_CH_RDWR_ERR_MASK         0x80
#define GDMAC_GDT0_FTR5_CH_RDWR_ERR_SHIFT        7 
#define GDMAC_GDT0_FTR5_CH_RDWR_ERR_BIT          0x1
#define GDMAC_GDT0_FTR5_CH_RDWR_ERR_BITWIDTH     1
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR5_RESERVED3_MASK           0xF00
#define GDMAC_GDT0_FTR5_RESERVED3_SHIFT          8 
#define GDMAC_GDT0_FTR5_RESERVED3_BIT            0xF
#define GDMAC_GDT0_FTR5_RESERVED3_BITWIDTH       4
// mfifo_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR5_MFIFO_ERR_MASK           0x1000
#define GDMAC_GDT0_FTR5_MFIFO_ERR_SHIFT          12 
#define GDMAC_GDT0_FTR5_MFIFO_ERR_BIT            0x1
#define GDMAC_GDT0_FTR5_MFIFO_ERR_BITWIDTH       1
// st_data_unavailable bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR5_ST_DATA_UNAVAILABLE_MASK 0x2000
#define GDMAC_GDT0_FTR5_ST_DATA_UNAVAILABLE_SHIFT 13 
#define GDMAC_GDT0_FTR5_ST_DATA_UNAVAILABLE_BIT  0x1
#define GDMAC_GDT0_FTR5_ST_DATA_UNAVAILABLE_BITWIDTH 1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR5_RESERVED2_MASK           0xC000
#define GDMAC_GDT0_FTR5_RESERVED2_SHIFT          14 
#define GDMAC_GDT0_FTR5_RESERVED2_BIT            0x3
#define GDMAC_GDT0_FTR5_RESERVED2_BITWIDTH       2
// instr_fetch_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR5_INSTR_FETCH_ERR_MASK     0x10000
#define GDMAC_GDT0_FTR5_INSTR_FETCH_ERR_SHIFT    16 
#define GDMAC_GDT0_FTR5_INSTR_FETCH_ERR_BIT      0x1
#define GDMAC_GDT0_FTR5_INSTR_FETCH_ERR_BITWIDTH 1
// data_write_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR5_DATA_WRITE_ERR_MASK      0x20000
#define GDMAC_GDT0_FTR5_DATA_WRITE_ERR_SHIFT     17 
#define GDMAC_GDT0_FTR5_DATA_WRITE_ERR_BIT       0x1
#define GDMAC_GDT0_FTR5_DATA_WRITE_ERR_BITWIDTH  1
// data_read_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR5_DATA_READ_ERR_MASK       0x40000
#define GDMAC_GDT0_FTR5_DATA_READ_ERR_SHIFT      18 
#define GDMAC_GDT0_FTR5_DATA_READ_ERR_BIT        0x1
#define GDMAC_GDT0_FTR5_DATA_READ_ERR_BITWIDTH   1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR5_RESERVED_MASK            0x3FF80000
#define GDMAC_GDT0_FTR5_RESERVED_SHIFT           19 
#define GDMAC_GDT0_FTR5_RESERVED_BIT             0x7FF
#define GDMAC_GDT0_FTR5_RESERVED_BITWIDTH        11
// dbg_instr bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR5_DBG_INSTR_MASK           0x40000000
#define GDMAC_GDT0_FTR5_DBG_INSTR_SHIFT          30 
#define GDMAC_GDT0_FTR5_DBG_INSTR_BIT            0x1
#define GDMAC_GDT0_FTR5_DBG_INSTR_BITWIDTH       1
// lockup_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR5_LOCKUP_ERR_MASK          0x80000000
#define GDMAC_GDT0_FTR5_LOCKUP_ERR_SHIFT         31 
#define GDMAC_GDT0_FTR5_LOCKUP_ERR_BIT           0x1
#define GDMAC_GDT0_FTR5_LOCKUP_ERR_BITWIDTH      1
// GDT0_FTR6 Register
#define GDMAC_GDT0_FTR6_OFS                      0x00000058
// undef_instr bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR6_UNDEF_INSTR_MASK         0x1
#define GDMAC_GDT0_FTR6_UNDEF_INSTR_SHIFT        0 
#define GDMAC_GDT0_FTR6_UNDEF_INSTR_BIT          0x1
#define GDMAC_GDT0_FTR6_UNDEF_INSTR_BITWIDTH     1
// operand_invalid bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR6_OPERAND_INVALID_MASK     0x2
#define GDMAC_GDT0_FTR6_OPERAND_INVALID_SHIFT    1 
#define GDMAC_GDT0_FTR6_OPERAND_INVALID_BIT      0x1
#define GDMAC_GDT0_FTR6_OPERAND_INVALID_BITWIDTH 1
// reserved4 bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR6_RESERVED4_MASK           0x1C
#define GDMAC_GDT0_FTR6_RESERVED4_SHIFT          2 
#define GDMAC_GDT0_FTR6_RESERVED4_BIT            0x7
#define GDMAC_GDT0_FTR6_RESERVED4_BITWIDTH       3
// ch_evnt_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR6_CH_EVNT_ERR_MASK         0x20
#define GDMAC_GDT0_FTR6_CH_EVNT_ERR_SHIFT        5 
#define GDMAC_GDT0_FTR6_CH_EVNT_ERR_BIT          0x1
#define GDMAC_GDT0_FTR6_CH_EVNT_ERR_BITWIDTH     1
// ch_periph_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR6_CH_PERIPH_ERR_MASK       0x40
#define GDMAC_GDT0_FTR6_CH_PERIPH_ERR_SHIFT      6 
#define GDMAC_GDT0_FTR6_CH_PERIPH_ERR_BIT        0x1
#define GDMAC_GDT0_FTR6_CH_PERIPH_ERR_BITWIDTH   1
// ch_rdwr_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR6_CH_RDWR_ERR_MASK         0x80
#define GDMAC_GDT0_FTR6_CH_RDWR_ERR_SHIFT        7 
#define GDMAC_GDT0_FTR6_CH_RDWR_ERR_BIT          0x1
#define GDMAC_GDT0_FTR6_CH_RDWR_ERR_BITWIDTH     1
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR6_RESERVED3_MASK           0xF00
#define GDMAC_GDT0_FTR6_RESERVED3_SHIFT          8 
#define GDMAC_GDT0_FTR6_RESERVED3_BIT            0xF
#define GDMAC_GDT0_FTR6_RESERVED3_BITWIDTH       4
// mfifo_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR6_MFIFO_ERR_MASK           0x1000
#define GDMAC_GDT0_FTR6_MFIFO_ERR_SHIFT          12 
#define GDMAC_GDT0_FTR6_MFIFO_ERR_BIT            0x1
#define GDMAC_GDT0_FTR6_MFIFO_ERR_BITWIDTH       1
// st_data_unavailable bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR6_ST_DATA_UNAVAILABLE_MASK 0x2000
#define GDMAC_GDT0_FTR6_ST_DATA_UNAVAILABLE_SHIFT 13 
#define GDMAC_GDT0_FTR6_ST_DATA_UNAVAILABLE_BIT  0x1
#define GDMAC_GDT0_FTR6_ST_DATA_UNAVAILABLE_BITWIDTH 1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR6_RESERVED2_MASK           0xC000
#define GDMAC_GDT0_FTR6_RESERVED2_SHIFT          14 
#define GDMAC_GDT0_FTR6_RESERVED2_BIT            0x3
#define GDMAC_GDT0_FTR6_RESERVED2_BITWIDTH       2
// instr_fetch_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR6_INSTR_FETCH_ERR_MASK     0x10000
#define GDMAC_GDT0_FTR6_INSTR_FETCH_ERR_SHIFT    16 
#define GDMAC_GDT0_FTR6_INSTR_FETCH_ERR_BIT      0x1
#define GDMAC_GDT0_FTR6_INSTR_FETCH_ERR_BITWIDTH 1
// data_write_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR6_DATA_WRITE_ERR_MASK      0x20000
#define GDMAC_GDT0_FTR6_DATA_WRITE_ERR_SHIFT     17 
#define GDMAC_GDT0_FTR6_DATA_WRITE_ERR_BIT       0x1
#define GDMAC_GDT0_FTR6_DATA_WRITE_ERR_BITWIDTH  1
// data_read_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR6_DATA_READ_ERR_MASK       0x40000
#define GDMAC_GDT0_FTR6_DATA_READ_ERR_SHIFT      18 
#define GDMAC_GDT0_FTR6_DATA_READ_ERR_BIT        0x1
#define GDMAC_GDT0_FTR6_DATA_READ_ERR_BITWIDTH   1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR6_RESERVED_MASK            0x3FF80000
#define GDMAC_GDT0_FTR6_RESERVED_SHIFT           19 
#define GDMAC_GDT0_FTR6_RESERVED_BIT             0x7FF
#define GDMAC_GDT0_FTR6_RESERVED_BITWIDTH        11
// dbg_instr bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR6_DBG_INSTR_MASK           0x40000000
#define GDMAC_GDT0_FTR6_DBG_INSTR_SHIFT          30 
#define GDMAC_GDT0_FTR6_DBG_INSTR_BIT            0x1
#define GDMAC_GDT0_FTR6_DBG_INSTR_BITWIDTH       1
// lockup_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR6_LOCKUP_ERR_MASK          0x80000000
#define GDMAC_GDT0_FTR6_LOCKUP_ERR_SHIFT         31 
#define GDMAC_GDT0_FTR6_LOCKUP_ERR_BIT           0x1
#define GDMAC_GDT0_FTR6_LOCKUP_ERR_BITWIDTH      1
// GDT0_FTR7 Register
#define GDMAC_GDT0_FTR7_OFS                      0x0000005C
// undef_instr bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR7_UNDEF_INSTR_MASK         0x1
#define GDMAC_GDT0_FTR7_UNDEF_INSTR_SHIFT        0 
#define GDMAC_GDT0_FTR7_UNDEF_INSTR_BIT          0x1
#define GDMAC_GDT0_FTR7_UNDEF_INSTR_BITWIDTH     1
// operand_invalid bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR7_OPERAND_INVALID_MASK     0x2
#define GDMAC_GDT0_FTR7_OPERAND_INVALID_SHIFT    1 
#define GDMAC_GDT0_FTR7_OPERAND_INVALID_BIT      0x1
#define GDMAC_GDT0_FTR7_OPERAND_INVALID_BITWIDTH 1
// reserved4 bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR7_RESERVED4_MASK           0x1C
#define GDMAC_GDT0_FTR7_RESERVED4_SHIFT          2 
#define GDMAC_GDT0_FTR7_RESERVED4_BIT            0x7
#define GDMAC_GDT0_FTR7_RESERVED4_BITWIDTH       3
// ch_evnt_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR7_CH_EVNT_ERR_MASK         0x20
#define GDMAC_GDT0_FTR7_CH_EVNT_ERR_SHIFT        5 
#define GDMAC_GDT0_FTR7_CH_EVNT_ERR_BIT          0x1
#define GDMAC_GDT0_FTR7_CH_EVNT_ERR_BITWIDTH     1
// ch_periph_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR7_CH_PERIPH_ERR_MASK       0x40
#define GDMAC_GDT0_FTR7_CH_PERIPH_ERR_SHIFT      6 
#define GDMAC_GDT0_FTR7_CH_PERIPH_ERR_BIT        0x1
#define GDMAC_GDT0_FTR7_CH_PERIPH_ERR_BITWIDTH   1
// ch_rdwr_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR7_CH_RDWR_ERR_MASK         0x80
#define GDMAC_GDT0_FTR7_CH_RDWR_ERR_SHIFT        7 
#define GDMAC_GDT0_FTR7_CH_RDWR_ERR_BIT          0x1
#define GDMAC_GDT0_FTR7_CH_RDWR_ERR_BITWIDTH     1
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR7_RESERVED3_MASK           0xF00
#define GDMAC_GDT0_FTR7_RESERVED3_SHIFT          8 
#define GDMAC_GDT0_FTR7_RESERVED3_BIT            0xF
#define GDMAC_GDT0_FTR7_RESERVED3_BITWIDTH       4
// mfifo_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR7_MFIFO_ERR_MASK           0x1000
#define GDMAC_GDT0_FTR7_MFIFO_ERR_SHIFT          12 
#define GDMAC_GDT0_FTR7_MFIFO_ERR_BIT            0x1
#define GDMAC_GDT0_FTR7_MFIFO_ERR_BITWIDTH       1
// st_data_unavailable bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR7_ST_DATA_UNAVAILABLE_MASK 0x2000
#define GDMAC_GDT0_FTR7_ST_DATA_UNAVAILABLE_SHIFT 13 
#define GDMAC_GDT0_FTR7_ST_DATA_UNAVAILABLE_BIT  0x1
#define GDMAC_GDT0_FTR7_ST_DATA_UNAVAILABLE_BITWIDTH 1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR7_RESERVED2_MASK           0xC000
#define GDMAC_GDT0_FTR7_RESERVED2_SHIFT          14 
#define GDMAC_GDT0_FTR7_RESERVED2_BIT            0x3
#define GDMAC_GDT0_FTR7_RESERVED2_BITWIDTH       2
// instr_fetch_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR7_INSTR_FETCH_ERR_MASK     0x10000
#define GDMAC_GDT0_FTR7_INSTR_FETCH_ERR_SHIFT    16 
#define GDMAC_GDT0_FTR7_INSTR_FETCH_ERR_BIT      0x1
#define GDMAC_GDT0_FTR7_INSTR_FETCH_ERR_BITWIDTH 1
// data_write_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR7_DATA_WRITE_ERR_MASK      0x20000
#define GDMAC_GDT0_FTR7_DATA_WRITE_ERR_SHIFT     17 
#define GDMAC_GDT0_FTR7_DATA_WRITE_ERR_BIT       0x1
#define GDMAC_GDT0_FTR7_DATA_WRITE_ERR_BITWIDTH  1
// data_read_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR7_DATA_READ_ERR_MASK       0x40000
#define GDMAC_GDT0_FTR7_DATA_READ_ERR_SHIFT      18 
#define GDMAC_GDT0_FTR7_DATA_READ_ERR_BIT        0x1
#define GDMAC_GDT0_FTR7_DATA_READ_ERR_BITWIDTH   1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR7_RESERVED_MASK            0x3FF80000
#define GDMAC_GDT0_FTR7_RESERVED_SHIFT           19 
#define GDMAC_GDT0_FTR7_RESERVED_BIT             0x7FF
#define GDMAC_GDT0_FTR7_RESERVED_BITWIDTH        11
// dbg_instr bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR7_DBG_INSTR_MASK           0x40000000
#define GDMAC_GDT0_FTR7_DBG_INSTR_SHIFT          30 
#define GDMAC_GDT0_FTR7_DBG_INSTR_BIT            0x1
#define GDMAC_GDT0_FTR7_DBG_INSTR_BITWIDTH       1
// lockup_err bitfiled (RO) Reset=0
#define GDMAC_GDT0_FTR7_LOCKUP_ERR_MASK          0x80000000
#define GDMAC_GDT0_FTR7_LOCKUP_ERR_SHIFT         31 
#define GDMAC_GDT0_FTR7_LOCKUP_ERR_BIT           0x1
#define GDMAC_GDT0_FTR7_LOCKUP_ERR_BITWIDTH      1
// GDT0_CSR0 Register
#define GDMAC_GDT0_CSR0_OFS                      0x00000100
// Channel_status bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR0_CHANNEL_STATUS_MASK      0xF
#define GDMAC_GDT0_CSR0_CHANNEL_STATUS_SHIFT     0 
#define GDMAC_GDT0_CSR0_CHANNEL_STATUS_BIT       0xF
#define GDMAC_GDT0_CSR0_CHANNEL_STATUS_BITWIDTH  4
// Wakeup_number bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR0_WAKEUP_NUMBER_MASK       0x1F0
#define GDMAC_GDT0_CSR0_WAKEUP_NUMBER_SHIFT      4 
#define GDMAC_GDT0_CSR0_WAKEUP_NUMBER_BIT        0x1F
#define GDMAC_GDT0_CSR0_WAKEUP_NUMBER_BITWIDTH   5
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR0_RESERVED3_MASK           0x3E00
#define GDMAC_GDT0_CSR0_RESERVED3_SHIFT          9 
#define GDMAC_GDT0_CSR0_RESERVED3_BIT            0x1F
#define GDMAC_GDT0_CSR0_RESERVED3_BITWIDTH       5
// dmawfp_b_ns bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR0_DMAWFP_B_NS_MASK         0x4000
#define GDMAC_GDT0_CSR0_DMAWFP_B_NS_SHIFT        14 
#define GDMAC_GDT0_CSR0_DMAWFP_B_NS_BIT          0x1
#define GDMAC_GDT0_CSR0_DMAWFP_B_NS_BITWIDTH     1
// dmawfp_periph bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR0_DMAWFP_PERIPH_MASK       0x8000
#define GDMAC_GDT0_CSR0_DMAWFP_PERIPH_SHIFT      15 
#define GDMAC_GDT0_CSR0_DMAWFP_PERIPH_BIT        0x1
#define GDMAC_GDT0_CSR0_DMAWFP_PERIPH_BITWIDTH   1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR0_RESERVED2_MASK           0x1F0000
#define GDMAC_GDT0_CSR0_RESERVED2_SHIFT          16 
#define GDMAC_GDT0_CSR0_RESERVED2_BIT            0x1F
#define GDMAC_GDT0_CSR0_RESERVED2_BITWIDTH       5
// CSN bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR0_CSN_MASK                 0x200000
#define GDMAC_GDT0_CSR0_CSN_SHIFT                21 
#define GDMAC_GDT0_CSR0_CSN_BIT                  0x1
#define GDMAC_GDT0_CSR0_CSN_BITWIDTH             1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR0_RESERVED_MASK            0xFFC00000
#define GDMAC_GDT0_CSR0_RESERVED_SHIFT           22 
#define GDMAC_GDT0_CSR0_RESERVED_BIT             0x3FF
#define GDMAC_GDT0_CSR0_RESERVED_BITWIDTH        10
// GDT0_CPC0 Register
#define GDMAC_GDT0_CPC0_OFS                      0x00000104
// pc_chnl bitfiled (RO) Reset=0
#define GDMAC_GDT0_CPC0_PC_CHNL_MASK             0xFFFFFFFF
#define GDMAC_GDT0_CPC0_PC_CHNL_SHIFT            0 
#define GDMAC_GDT0_CPC0_PC_CHNL_BIT              0xFFFFFFFF
#define GDMAC_GDT0_CPC0_PC_CHNL_BITWIDTH         32
// GDT0_CSR1 Register
#define GDMAC_GDT0_CSR1_OFS                      0x00000108
// Channel_status bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR1_CHANNEL_STATUS_MASK      0xF
#define GDMAC_GDT0_CSR1_CHANNEL_STATUS_SHIFT     0 
#define GDMAC_GDT0_CSR1_CHANNEL_STATUS_BIT       0xF
#define GDMAC_GDT0_CSR1_CHANNEL_STATUS_BITWIDTH  4
// Wakeup_number bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR1_WAKEUP_NUMBER_MASK       0x1F0
#define GDMAC_GDT0_CSR1_WAKEUP_NUMBER_SHIFT      4 
#define GDMAC_GDT0_CSR1_WAKEUP_NUMBER_BIT        0x1F
#define GDMAC_GDT0_CSR1_WAKEUP_NUMBER_BITWIDTH   5
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR1_RESERVED3_MASK           0x3E00
#define GDMAC_GDT0_CSR1_RESERVED3_SHIFT          9 
#define GDMAC_GDT0_CSR1_RESERVED3_BIT            0x1F
#define GDMAC_GDT0_CSR1_RESERVED3_BITWIDTH       5
// dmawfp_b_ns bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR1_DMAWFP_B_NS_MASK         0x4000
#define GDMAC_GDT0_CSR1_DMAWFP_B_NS_SHIFT        14 
#define GDMAC_GDT0_CSR1_DMAWFP_B_NS_BIT          0x1
#define GDMAC_GDT0_CSR1_DMAWFP_B_NS_BITWIDTH     1
// dmawfp_periph bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR1_DMAWFP_PERIPH_MASK       0x8000
#define GDMAC_GDT0_CSR1_DMAWFP_PERIPH_SHIFT      15 
#define GDMAC_GDT0_CSR1_DMAWFP_PERIPH_BIT        0x1
#define GDMAC_GDT0_CSR1_DMAWFP_PERIPH_BITWIDTH   1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR1_RESERVED2_MASK           0x1F0000
#define GDMAC_GDT0_CSR1_RESERVED2_SHIFT          16 
#define GDMAC_GDT0_CSR1_RESERVED2_BIT            0x1F
#define GDMAC_GDT0_CSR1_RESERVED2_BITWIDTH       5
// CSN bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR1_CSN_MASK                 0x200000
#define GDMAC_GDT0_CSR1_CSN_SHIFT                21 
#define GDMAC_GDT0_CSR1_CSN_BIT                  0x1
#define GDMAC_GDT0_CSR1_CSN_BITWIDTH             1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR1_RESERVED_MASK            0xFFC00000
#define GDMAC_GDT0_CSR1_RESERVED_SHIFT           22 
#define GDMAC_GDT0_CSR1_RESERVED_BIT             0x3FF
#define GDMAC_GDT0_CSR1_RESERVED_BITWIDTH        10
// GDT0_CPC1 Register
#define GDMAC_GDT0_CPC1_OFS                      0x0000010C
// pc_chnl bitfiled (RO) Reset=0
#define GDMAC_GDT0_CPC1_PC_CHNL_MASK             0xFFFFFFFF
#define GDMAC_GDT0_CPC1_PC_CHNL_SHIFT            0 
#define GDMAC_GDT0_CPC1_PC_CHNL_BIT              0xFFFFFFFF
#define GDMAC_GDT0_CPC1_PC_CHNL_BITWIDTH         32
// GDT0_CSR2 Register
#define GDMAC_GDT0_CSR2_OFS                      0x00000110
// Channel_status bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR2_CHANNEL_STATUS_MASK      0xF
#define GDMAC_GDT0_CSR2_CHANNEL_STATUS_SHIFT     0 
#define GDMAC_GDT0_CSR2_CHANNEL_STATUS_BIT       0xF
#define GDMAC_GDT0_CSR2_CHANNEL_STATUS_BITWIDTH  4
// Wakeup_number bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR2_WAKEUP_NUMBER_MASK       0x1F0
#define GDMAC_GDT0_CSR2_WAKEUP_NUMBER_SHIFT      4 
#define GDMAC_GDT0_CSR2_WAKEUP_NUMBER_BIT        0x1F
#define GDMAC_GDT0_CSR2_WAKEUP_NUMBER_BITWIDTH   5
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR2_RESERVED3_MASK           0x3E00
#define GDMAC_GDT0_CSR2_RESERVED3_SHIFT          9 
#define GDMAC_GDT0_CSR2_RESERVED3_BIT            0x1F
#define GDMAC_GDT0_CSR2_RESERVED3_BITWIDTH       5
// dmawfp_b_ns bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR2_DMAWFP_B_NS_MASK         0x4000
#define GDMAC_GDT0_CSR2_DMAWFP_B_NS_SHIFT        14 
#define GDMAC_GDT0_CSR2_DMAWFP_B_NS_BIT          0x1
#define GDMAC_GDT0_CSR2_DMAWFP_B_NS_BITWIDTH     1
// dmawfp_periph bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR2_DMAWFP_PERIPH_MASK       0x8000
#define GDMAC_GDT0_CSR2_DMAWFP_PERIPH_SHIFT      15 
#define GDMAC_GDT0_CSR2_DMAWFP_PERIPH_BIT        0x1
#define GDMAC_GDT0_CSR2_DMAWFP_PERIPH_BITWIDTH   1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR2_RESERVED2_MASK           0x1F0000
#define GDMAC_GDT0_CSR2_RESERVED2_SHIFT          16 
#define GDMAC_GDT0_CSR2_RESERVED2_BIT            0x1F
#define GDMAC_GDT0_CSR2_RESERVED2_BITWIDTH       5
// CSN bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR2_CSN_MASK                 0x200000
#define GDMAC_GDT0_CSR2_CSN_SHIFT                21 
#define GDMAC_GDT0_CSR2_CSN_BIT                  0x1
#define GDMAC_GDT0_CSR2_CSN_BITWIDTH             1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR2_RESERVED_MASK            0xFFC00000
#define GDMAC_GDT0_CSR2_RESERVED_SHIFT           22 
#define GDMAC_GDT0_CSR2_RESERVED_BIT             0x3FF
#define GDMAC_GDT0_CSR2_RESERVED_BITWIDTH        10
// GDT0_CPC2 Register
#define GDMAC_GDT0_CPC2_OFS                      0x00000114
// pc_chnl bitfiled (RO) Reset=0
#define GDMAC_GDT0_CPC2_PC_CHNL_MASK             0xFFFFFFFF
#define GDMAC_GDT0_CPC2_PC_CHNL_SHIFT            0 
#define GDMAC_GDT0_CPC2_PC_CHNL_BIT              0xFFFFFFFF
#define GDMAC_GDT0_CPC2_PC_CHNL_BITWIDTH         32
// GDT0_CSR3 Register
#define GDMAC_GDT0_CSR3_OFS                      0x00000118
// Channel_status bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR3_CHANNEL_STATUS_MASK      0xF
#define GDMAC_GDT0_CSR3_CHANNEL_STATUS_SHIFT     0 
#define GDMAC_GDT0_CSR3_CHANNEL_STATUS_BIT       0xF
#define GDMAC_GDT0_CSR3_CHANNEL_STATUS_BITWIDTH  4
// Wakeup_number bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR3_WAKEUP_NUMBER_MASK       0x1F0
#define GDMAC_GDT0_CSR3_WAKEUP_NUMBER_SHIFT      4 
#define GDMAC_GDT0_CSR3_WAKEUP_NUMBER_BIT        0x1F
#define GDMAC_GDT0_CSR3_WAKEUP_NUMBER_BITWIDTH   5
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR3_RESERVED3_MASK           0x3E00
#define GDMAC_GDT0_CSR3_RESERVED3_SHIFT          9 
#define GDMAC_GDT0_CSR3_RESERVED3_BIT            0x1F
#define GDMAC_GDT0_CSR3_RESERVED3_BITWIDTH       5
// dmawfp_b_ns bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR3_DMAWFP_B_NS_MASK         0x4000
#define GDMAC_GDT0_CSR3_DMAWFP_B_NS_SHIFT        14 
#define GDMAC_GDT0_CSR3_DMAWFP_B_NS_BIT          0x1
#define GDMAC_GDT0_CSR3_DMAWFP_B_NS_BITWIDTH     1
// dmawfp_periph bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR3_DMAWFP_PERIPH_MASK       0x8000
#define GDMAC_GDT0_CSR3_DMAWFP_PERIPH_SHIFT      15 
#define GDMAC_GDT0_CSR3_DMAWFP_PERIPH_BIT        0x1
#define GDMAC_GDT0_CSR3_DMAWFP_PERIPH_BITWIDTH   1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR3_RESERVED2_MASK           0x1F0000
#define GDMAC_GDT0_CSR3_RESERVED2_SHIFT          16 
#define GDMAC_GDT0_CSR3_RESERVED2_BIT            0x1F
#define GDMAC_GDT0_CSR3_RESERVED2_BITWIDTH       5
// CSN bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR3_CSN_MASK                 0x200000
#define GDMAC_GDT0_CSR3_CSN_SHIFT                21 
#define GDMAC_GDT0_CSR3_CSN_BIT                  0x1
#define GDMAC_GDT0_CSR3_CSN_BITWIDTH             1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR3_RESERVED_MASK            0xFFC00000
#define GDMAC_GDT0_CSR3_RESERVED_SHIFT           22 
#define GDMAC_GDT0_CSR3_RESERVED_BIT             0x3FF
#define GDMAC_GDT0_CSR3_RESERVED_BITWIDTH        10
// GDT0_CPC3 Register
#define GDMAC_GDT0_CPC3_OFS                      0x0000011C
// pc_chnl bitfiled (RO) Reset=0
#define GDMAC_GDT0_CPC3_PC_CHNL_MASK             0xFFFFFFFF
#define GDMAC_GDT0_CPC3_PC_CHNL_SHIFT            0 
#define GDMAC_GDT0_CPC3_PC_CHNL_BIT              0xFFFFFFFF
#define GDMAC_GDT0_CPC3_PC_CHNL_BITWIDTH         32
// GDT0_CSR4 Register
#define GDMAC_GDT0_CSR4_OFS                      0x00000120
// Channel_status bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR4_CHANNEL_STATUS_MASK      0xF
#define GDMAC_GDT0_CSR4_CHANNEL_STATUS_SHIFT     0 
#define GDMAC_GDT0_CSR4_CHANNEL_STATUS_BIT       0xF
#define GDMAC_GDT0_CSR4_CHANNEL_STATUS_BITWIDTH  4
// Wakeup_number bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR4_WAKEUP_NUMBER_MASK       0x1F0
#define GDMAC_GDT0_CSR4_WAKEUP_NUMBER_SHIFT      4 
#define GDMAC_GDT0_CSR4_WAKEUP_NUMBER_BIT        0x1F
#define GDMAC_GDT0_CSR4_WAKEUP_NUMBER_BITWIDTH   5
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR4_RESERVED3_MASK           0x3E00
#define GDMAC_GDT0_CSR4_RESERVED3_SHIFT          9 
#define GDMAC_GDT0_CSR4_RESERVED3_BIT            0x1F
#define GDMAC_GDT0_CSR4_RESERVED3_BITWIDTH       5
// dmawfp_b_ns bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR4_DMAWFP_B_NS_MASK         0x4000
#define GDMAC_GDT0_CSR4_DMAWFP_B_NS_SHIFT        14 
#define GDMAC_GDT0_CSR4_DMAWFP_B_NS_BIT          0x1
#define GDMAC_GDT0_CSR4_DMAWFP_B_NS_BITWIDTH     1
// dmawfp_periph bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR4_DMAWFP_PERIPH_MASK       0x8000
#define GDMAC_GDT0_CSR4_DMAWFP_PERIPH_SHIFT      15 
#define GDMAC_GDT0_CSR4_DMAWFP_PERIPH_BIT        0x1
#define GDMAC_GDT0_CSR4_DMAWFP_PERIPH_BITWIDTH   1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR4_RESERVED2_MASK           0x1F0000
#define GDMAC_GDT0_CSR4_RESERVED2_SHIFT          16 
#define GDMAC_GDT0_CSR4_RESERVED2_BIT            0x1F
#define GDMAC_GDT0_CSR4_RESERVED2_BITWIDTH       5
// CSN bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR4_CSN_MASK                 0x200000
#define GDMAC_GDT0_CSR4_CSN_SHIFT                21 
#define GDMAC_GDT0_CSR4_CSN_BIT                  0x1
#define GDMAC_GDT0_CSR4_CSN_BITWIDTH             1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR4_RESERVED_MASK            0xFFC00000
#define GDMAC_GDT0_CSR4_RESERVED_SHIFT           22 
#define GDMAC_GDT0_CSR4_RESERVED_BIT             0x3FF
#define GDMAC_GDT0_CSR4_RESERVED_BITWIDTH        10
// GDT0_CPC4 Register
#define GDMAC_GDT0_CPC4_OFS                      0x00000124
// pc_chnl bitfiled (RO) Reset=0
#define GDMAC_GDT0_CPC4_PC_CHNL_MASK             0xFFFFFFFF
#define GDMAC_GDT0_CPC4_PC_CHNL_SHIFT            0 
#define GDMAC_GDT0_CPC4_PC_CHNL_BIT              0xFFFFFFFF
#define GDMAC_GDT0_CPC4_PC_CHNL_BITWIDTH         32
// GDT0_CSR5 Register
#define GDMAC_GDT0_CSR5_OFS                      0x00000128
// Channel_status bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR5_CHANNEL_STATUS_MASK      0xF
#define GDMAC_GDT0_CSR5_CHANNEL_STATUS_SHIFT     0 
#define GDMAC_GDT0_CSR5_CHANNEL_STATUS_BIT       0xF
#define GDMAC_GDT0_CSR5_CHANNEL_STATUS_BITWIDTH  4
// Wakeup_number bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR5_WAKEUP_NUMBER_MASK       0x1F0
#define GDMAC_GDT0_CSR5_WAKEUP_NUMBER_SHIFT      4 
#define GDMAC_GDT0_CSR5_WAKEUP_NUMBER_BIT        0x1F
#define GDMAC_GDT0_CSR5_WAKEUP_NUMBER_BITWIDTH   5
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR5_RESERVED3_MASK           0x3E00
#define GDMAC_GDT0_CSR5_RESERVED3_SHIFT          9 
#define GDMAC_GDT0_CSR5_RESERVED3_BIT            0x1F
#define GDMAC_GDT0_CSR5_RESERVED3_BITWIDTH       5
// dmawfp_b_ns bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR5_DMAWFP_B_NS_MASK         0x4000
#define GDMAC_GDT0_CSR5_DMAWFP_B_NS_SHIFT        14 
#define GDMAC_GDT0_CSR5_DMAWFP_B_NS_BIT          0x1
#define GDMAC_GDT0_CSR5_DMAWFP_B_NS_BITWIDTH     1
// dmawfp_periph bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR5_DMAWFP_PERIPH_MASK       0x8000
#define GDMAC_GDT0_CSR5_DMAWFP_PERIPH_SHIFT      15 
#define GDMAC_GDT0_CSR5_DMAWFP_PERIPH_BIT        0x1
#define GDMAC_GDT0_CSR5_DMAWFP_PERIPH_BITWIDTH   1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR5_RESERVED2_MASK           0x1F0000
#define GDMAC_GDT0_CSR5_RESERVED2_SHIFT          16 
#define GDMAC_GDT0_CSR5_RESERVED2_BIT            0x1F
#define GDMAC_GDT0_CSR5_RESERVED2_BITWIDTH       5
// CSN bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR5_CSN_MASK                 0x200000
#define GDMAC_GDT0_CSR5_CSN_SHIFT                21 
#define GDMAC_GDT0_CSR5_CSN_BIT                  0x1
#define GDMAC_GDT0_CSR5_CSN_BITWIDTH             1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR5_RESERVED_MASK            0xFFC00000
#define GDMAC_GDT0_CSR5_RESERVED_SHIFT           22 
#define GDMAC_GDT0_CSR5_RESERVED_BIT             0x3FF
#define GDMAC_GDT0_CSR5_RESERVED_BITWIDTH        10
// GDT0_CPC5 Register
#define GDMAC_GDT0_CPC5_OFS                      0x0000012C
// pc_chnl bitfiled (RO) Reset=0
#define GDMAC_GDT0_CPC5_PC_CHNL_MASK             0xFFFFFFFF
#define GDMAC_GDT0_CPC5_PC_CHNL_SHIFT            0 
#define GDMAC_GDT0_CPC5_PC_CHNL_BIT              0xFFFFFFFF
#define GDMAC_GDT0_CPC5_PC_CHNL_BITWIDTH         32
// GDT0_CSR6 Register
#define GDMAC_GDT0_CSR6_OFS                      0x00000130
// Channel_status bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR6_CHANNEL_STATUS_MASK      0xF
#define GDMAC_GDT0_CSR6_CHANNEL_STATUS_SHIFT     0 
#define GDMAC_GDT0_CSR6_CHANNEL_STATUS_BIT       0xF
#define GDMAC_GDT0_CSR6_CHANNEL_STATUS_BITWIDTH  4
// Wakeup_number bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR6_WAKEUP_NUMBER_MASK       0x1F0
#define GDMAC_GDT0_CSR6_WAKEUP_NUMBER_SHIFT      4 
#define GDMAC_GDT0_CSR6_WAKEUP_NUMBER_BIT        0x1F
#define GDMAC_GDT0_CSR6_WAKEUP_NUMBER_BITWIDTH   5
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR6_RESERVED3_MASK           0x3E00
#define GDMAC_GDT0_CSR6_RESERVED3_SHIFT          9 
#define GDMAC_GDT0_CSR6_RESERVED3_BIT            0x1F
#define GDMAC_GDT0_CSR6_RESERVED3_BITWIDTH       5
// dmawfp_b_ns bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR6_DMAWFP_B_NS_MASK         0x4000
#define GDMAC_GDT0_CSR6_DMAWFP_B_NS_SHIFT        14 
#define GDMAC_GDT0_CSR6_DMAWFP_B_NS_BIT          0x1
#define GDMAC_GDT0_CSR6_DMAWFP_B_NS_BITWIDTH     1
// dmawfp_periph bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR6_DMAWFP_PERIPH_MASK       0x8000
#define GDMAC_GDT0_CSR6_DMAWFP_PERIPH_SHIFT      15 
#define GDMAC_GDT0_CSR6_DMAWFP_PERIPH_BIT        0x1
#define GDMAC_GDT0_CSR6_DMAWFP_PERIPH_BITWIDTH   1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR6_RESERVED2_MASK           0x1F0000
#define GDMAC_GDT0_CSR6_RESERVED2_SHIFT          16 
#define GDMAC_GDT0_CSR6_RESERVED2_BIT            0x1F
#define GDMAC_GDT0_CSR6_RESERVED2_BITWIDTH       5
// CSN bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR6_CSN_MASK                 0x200000
#define GDMAC_GDT0_CSR6_CSN_SHIFT                21 
#define GDMAC_GDT0_CSR6_CSN_BIT                  0x1
#define GDMAC_GDT0_CSR6_CSN_BITWIDTH             1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR6_RESERVED_MASK            0xFFC00000
#define GDMAC_GDT0_CSR6_RESERVED_SHIFT           22 
#define GDMAC_GDT0_CSR6_RESERVED_BIT             0x3FF
#define GDMAC_GDT0_CSR6_RESERVED_BITWIDTH        10
// GDT0_CPC6 Register
#define GDMAC_GDT0_CPC6_OFS                      0x00000134
// pc_chnl bitfiled (RO) Reset=0
#define GDMAC_GDT0_CPC6_PC_CHNL_MASK             0xFFFFFFFF
#define GDMAC_GDT0_CPC6_PC_CHNL_SHIFT            0 
#define GDMAC_GDT0_CPC6_PC_CHNL_BIT              0xFFFFFFFF
#define GDMAC_GDT0_CPC6_PC_CHNL_BITWIDTH         32
// GDT0_CSR7 Register
#define GDMAC_GDT0_CSR7_OFS                      0x00000138
// Channel_status bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR7_CHANNEL_STATUS_MASK      0xF
#define GDMAC_GDT0_CSR7_CHANNEL_STATUS_SHIFT     0 
#define GDMAC_GDT0_CSR7_CHANNEL_STATUS_BIT       0xF
#define GDMAC_GDT0_CSR7_CHANNEL_STATUS_BITWIDTH  4
// Wakeup_number bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR7_WAKEUP_NUMBER_MASK       0x1F0
#define GDMAC_GDT0_CSR7_WAKEUP_NUMBER_SHIFT      4 
#define GDMAC_GDT0_CSR7_WAKEUP_NUMBER_BIT        0x1F
#define GDMAC_GDT0_CSR7_WAKEUP_NUMBER_BITWIDTH   5
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR7_RESERVED3_MASK           0x3E00
#define GDMAC_GDT0_CSR7_RESERVED3_SHIFT          9 
#define GDMAC_GDT0_CSR7_RESERVED3_BIT            0x1F
#define GDMAC_GDT0_CSR7_RESERVED3_BITWIDTH       5
// dmawfp_b_ns bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR7_DMAWFP_B_NS_MASK         0x4000
#define GDMAC_GDT0_CSR7_DMAWFP_B_NS_SHIFT        14 
#define GDMAC_GDT0_CSR7_DMAWFP_B_NS_BIT          0x1
#define GDMAC_GDT0_CSR7_DMAWFP_B_NS_BITWIDTH     1
// dmawfp_periph bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR7_DMAWFP_PERIPH_MASK       0x8000
#define GDMAC_GDT0_CSR7_DMAWFP_PERIPH_SHIFT      15 
#define GDMAC_GDT0_CSR7_DMAWFP_PERIPH_BIT        0x1
#define GDMAC_GDT0_CSR7_DMAWFP_PERIPH_BITWIDTH   1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR7_RESERVED2_MASK           0x1F0000
#define GDMAC_GDT0_CSR7_RESERVED2_SHIFT          16 
#define GDMAC_GDT0_CSR7_RESERVED2_BIT            0x1F
#define GDMAC_GDT0_CSR7_RESERVED2_BITWIDTH       5
// CSN bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR7_CSN_MASK                 0x200000
#define GDMAC_GDT0_CSR7_CSN_SHIFT                21 
#define GDMAC_GDT0_CSR7_CSN_BIT                  0x1
#define GDMAC_GDT0_CSR7_CSN_BITWIDTH             1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_CSR7_RESERVED_MASK            0xFFC00000
#define GDMAC_GDT0_CSR7_RESERVED_SHIFT           22 
#define GDMAC_GDT0_CSR7_RESERVED_BIT             0x3FF
#define GDMAC_GDT0_CSR7_RESERVED_BITWIDTH        10
// GDT0_CPC7 Register
#define GDMAC_GDT0_CPC7_OFS                      0x0000013C
// pc_chnl bitfiled (RO) Reset=0
#define GDMAC_GDT0_CPC7_PC_CHNL_MASK             0xFFFFFFFF
#define GDMAC_GDT0_CPC7_PC_CHNL_SHIFT            0 
#define GDMAC_GDT0_CPC7_PC_CHNL_BIT              0xFFFFFFFF
#define GDMAC_GDT0_CPC7_PC_CHNL_BITWIDTH         32
// GDT0_SAR0 Register
#define GDMAC_GDT0_SAR0_OFS                      0x00000400
// src_addr bitfiled (RO) Reset=0
#define GDMAC_GDT0_SAR0_SRC_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT0_SAR0_SRC_ADDR_SHIFT           0 
#define GDMAC_GDT0_SAR0_SRC_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT0_SAR0_SRC_ADDR_BITWIDTH        32
// GDT0_DAR0 Register
#define GDMAC_GDT0_DAR0_OFS                      0x00000404
// dst_addr bitfiled (RO) Reset=0
#define GDMAC_GDT0_DAR0_DST_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT0_DAR0_DST_ADDR_SHIFT           0 
#define GDMAC_GDT0_DAR0_DST_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT0_DAR0_DST_ADDR_BITWIDTH        32
// GDT0_CCR0 Register
#define GDMAC_GDT0_CCR0_OFS                      0x00000408
// src_inc bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR0_SRC_INC_MASK             0x1
#define GDMAC_GDT0_CCR0_SRC_INC_SHIFT            0 
#define GDMAC_GDT0_CCR0_SRC_INC_BIT              0x1
#define GDMAC_GDT0_CCR0_SRC_INC_BITWIDTH         1
// src_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR0_SRC_BURST_SIZE_MASK      0xE
#define GDMAC_GDT0_CCR0_SRC_BURST_SIZE_SHIFT     1 
#define GDMAC_GDT0_CCR0_SRC_BURST_SIZE_BIT       0x7
#define GDMAC_GDT0_CCR0_SRC_BURST_SIZE_BITWIDTH  3
// src_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR0_SRC_BURST_LEN_MASK       0xF0
#define GDMAC_GDT0_CCR0_SRC_BURST_LEN_SHIFT      4 
#define GDMAC_GDT0_CCR0_SRC_BURST_LEN_BIT        0xF
#define GDMAC_GDT0_CCR0_SRC_BURST_LEN_BITWIDTH   4
// src_prot_ctrl bitfiled (RO) Reset=10
#define GDMAC_GDT0_CCR0_SRC_PROT_CTRL_MASK       0x700
#define GDMAC_GDT0_CCR0_SRC_PROT_CTRL_SHIFT      8 
#define GDMAC_GDT0_CCR0_SRC_PROT_CTRL_BIT        0x7
#define GDMAC_GDT0_CCR0_SRC_PROT_CTRL_BITWIDTH   3
// src_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR0_SRC_CACHE_CTRL_MASK      0x3800
#define GDMAC_GDT0_CCR0_SRC_CACHE_CTRL_SHIFT     11 
#define GDMAC_GDT0_CCR0_SRC_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT0_CCR0_SRC_CACHE_CTRL_BITWIDTH  3
// dst_inc bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR0_DST_INC_MASK             0x4000
#define GDMAC_GDT0_CCR0_DST_INC_SHIFT            14 
#define GDMAC_GDT0_CCR0_DST_INC_BIT              0x1
#define GDMAC_GDT0_CCR0_DST_INC_BITWIDTH         1
// dst_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR0_DST_BURST_SIZE_MASK      0x38000
#define GDMAC_GDT0_CCR0_DST_BURST_SIZE_SHIFT     15 
#define GDMAC_GDT0_CCR0_DST_BURST_SIZE_BIT       0x7
#define GDMAC_GDT0_CCR0_DST_BURST_SIZE_BITWIDTH  3
// dst_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR0_DST_BURST_LEN_MASK       0x3C0000
#define GDMAC_GDT0_CCR0_DST_BURST_LEN_SHIFT      18 
#define GDMAC_GDT0_CCR0_DST_BURST_LEN_BIT        0xF
#define GDMAC_GDT0_CCR0_DST_BURST_LEN_BITWIDTH   4
// dst_prot_ctrl bitfiled (RO) Reset=10
#define GDMAC_GDT0_CCR0_DST_PROT_CTRL_MASK       0x1C00000
#define GDMAC_GDT0_CCR0_DST_PROT_CTRL_SHIFT      22 
#define GDMAC_GDT0_CCR0_DST_PROT_CTRL_BIT        0x7
#define GDMAC_GDT0_CCR0_DST_PROT_CTRL_BITWIDTH   3
// dst_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR0_DST_CACHE_CTRL_MASK      0xE000000
#define GDMAC_GDT0_CCR0_DST_CACHE_CTRL_SHIFT     25 
#define GDMAC_GDT0_CCR0_DST_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT0_CCR0_DST_CACHE_CTRL_BITWIDTH  3
// endian_swap_size bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR0_ENDIAN_SWAP_SIZE_MASK    0x70000000
#define GDMAC_GDT0_CCR0_ENDIAN_SWAP_SIZE_SHIFT   28 
#define GDMAC_GDT0_CCR0_ENDIAN_SWAP_SIZE_BIT     0x7
#define GDMAC_GDT0_CCR0_ENDIAN_SWAP_SIZE_BITWIDTH 3
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR0_RESERVED_MASK            0x80000000
#define GDMAC_GDT0_CCR0_RESERVED_SHIFT           31 
#define GDMAC_GDT0_CCR0_RESERVED_BIT             0x1
#define GDMAC_GDT0_CCR0_RESERVED_BITWIDTH        1
// GDT0_LC0_0 Register
#define GDMAC_GDT0_LC0_0_OFS                     0x0000040C
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC0_0_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT0_LC0_0_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT0_LC0_0_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT0_LC0_0_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC0_0_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT0_LC0_0_RESERVED_SHIFT          8 
#define GDMAC_GDT0_LC0_0_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT0_LC0_0_RESERVED_BITWIDTH       24
// GDT0_LC1_0 Register
#define GDMAC_GDT0_LC1_0_OFS                     0x00000410
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC1_0_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT0_LC1_0_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT0_LC1_0_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT0_LC1_0_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC1_0_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT0_LC1_0_RESERVED_SHIFT          8 
#define GDMAC_GDT0_LC1_0_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT0_LC1_0_RESERVED_BITWIDTH       24
// GDT0_SAR1 Register
#define GDMAC_GDT0_SAR1_OFS                      0x00000420
// src_addr bitfiled (RO) Reset=0
#define GDMAC_GDT0_SAR1_SRC_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT0_SAR1_SRC_ADDR_SHIFT           0 
#define GDMAC_GDT0_SAR1_SRC_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT0_SAR1_SRC_ADDR_BITWIDTH        32
// GDT0_DAR1 Register
#define GDMAC_GDT0_DAR1_OFS                      0x00000424
// dst_addr bitfiled (RO) Reset=0
#define GDMAC_GDT0_DAR1_DST_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT0_DAR1_DST_ADDR_SHIFT           0 
#define GDMAC_GDT0_DAR1_DST_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT0_DAR1_DST_ADDR_BITWIDTH        32
// GDT0_CCR1 Register
#define GDMAC_GDT0_CCR1_OFS                      0x00000428
// src_inc bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR1_SRC_INC_MASK             0x1
#define GDMAC_GDT0_CCR1_SRC_INC_SHIFT            0 
#define GDMAC_GDT0_CCR1_SRC_INC_BIT              0x1
#define GDMAC_GDT0_CCR1_SRC_INC_BITWIDTH         1
// src_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR1_SRC_BURST_SIZE_MASK      0xE
#define GDMAC_GDT0_CCR1_SRC_BURST_SIZE_SHIFT     1 
#define GDMAC_GDT0_CCR1_SRC_BURST_SIZE_BIT       0x7
#define GDMAC_GDT0_CCR1_SRC_BURST_SIZE_BITWIDTH  3
// src_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR1_SRC_BURST_LEN_MASK       0xF0
#define GDMAC_GDT0_CCR1_SRC_BURST_LEN_SHIFT      4 
#define GDMAC_GDT0_CCR1_SRC_BURST_LEN_BIT        0xF
#define GDMAC_GDT0_CCR1_SRC_BURST_LEN_BITWIDTH   4
// src_prot_ctrl bitfiled (RO) Reset=10
#define GDMAC_GDT0_CCR1_SRC_PROT_CTRL_MASK       0x700
#define GDMAC_GDT0_CCR1_SRC_PROT_CTRL_SHIFT      8 
#define GDMAC_GDT0_CCR1_SRC_PROT_CTRL_BIT        0x7
#define GDMAC_GDT0_CCR1_SRC_PROT_CTRL_BITWIDTH   3
// src_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR1_SRC_CACHE_CTRL_MASK      0x3800
#define GDMAC_GDT0_CCR1_SRC_CACHE_CTRL_SHIFT     11 
#define GDMAC_GDT0_CCR1_SRC_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT0_CCR1_SRC_CACHE_CTRL_BITWIDTH  3
// dst_inc bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR1_DST_INC_MASK             0x4000
#define GDMAC_GDT0_CCR1_DST_INC_SHIFT            14 
#define GDMAC_GDT0_CCR1_DST_INC_BIT              0x1
#define GDMAC_GDT0_CCR1_DST_INC_BITWIDTH         1
// dst_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR1_DST_BURST_SIZE_MASK      0x38000
#define GDMAC_GDT0_CCR1_DST_BURST_SIZE_SHIFT     15 
#define GDMAC_GDT0_CCR1_DST_BURST_SIZE_BIT       0x7
#define GDMAC_GDT0_CCR1_DST_BURST_SIZE_BITWIDTH  3
// dst_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR1_DST_BURST_LEN_MASK       0x3C0000
#define GDMAC_GDT0_CCR1_DST_BURST_LEN_SHIFT      18 
#define GDMAC_GDT0_CCR1_DST_BURST_LEN_BIT        0xF
#define GDMAC_GDT0_CCR1_DST_BURST_LEN_BITWIDTH   4
// dst_prot_ctrl bitfiled (RO) Reset=10
#define GDMAC_GDT0_CCR1_DST_PROT_CTRL_MASK       0x1C00000
#define GDMAC_GDT0_CCR1_DST_PROT_CTRL_SHIFT      22 
#define GDMAC_GDT0_CCR1_DST_PROT_CTRL_BIT        0x7
#define GDMAC_GDT0_CCR1_DST_PROT_CTRL_BITWIDTH   3
// dst_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR1_DST_CACHE_CTRL_MASK      0xE000000
#define GDMAC_GDT0_CCR1_DST_CACHE_CTRL_SHIFT     25 
#define GDMAC_GDT0_CCR1_DST_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT0_CCR1_DST_CACHE_CTRL_BITWIDTH  3
// endian_swap_size bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR1_ENDIAN_SWAP_SIZE_MASK    0x70000000
#define GDMAC_GDT0_CCR1_ENDIAN_SWAP_SIZE_SHIFT   28 
#define GDMAC_GDT0_CCR1_ENDIAN_SWAP_SIZE_BIT     0x7
#define GDMAC_GDT0_CCR1_ENDIAN_SWAP_SIZE_BITWIDTH 3
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR1_RESERVED_MASK            0x80000000
#define GDMAC_GDT0_CCR1_RESERVED_SHIFT           31 
#define GDMAC_GDT0_CCR1_RESERVED_BIT             0x1
#define GDMAC_GDT0_CCR1_RESERVED_BITWIDTH        1
// GDT0_LC0_1 Register
#define GDMAC_GDT0_LC0_1_OFS                     0x0000042C
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC0_1_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT0_LC0_1_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT0_LC0_1_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT0_LC0_1_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC0_1_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT0_LC0_1_RESERVED_SHIFT          8 
#define GDMAC_GDT0_LC0_1_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT0_LC0_1_RESERVED_BITWIDTH       24
// GDT0_LC1_1 Register
#define GDMAC_GDT0_LC1_1_OFS                     0x00000430
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC1_1_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT0_LC1_1_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT0_LC1_1_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT0_LC1_1_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC1_1_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT0_LC1_1_RESERVED_SHIFT          8 
#define GDMAC_GDT0_LC1_1_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT0_LC1_1_RESERVED_BITWIDTH       24
// GDT0_SAR2 Register
#define GDMAC_GDT0_SAR2_OFS                      0x00000440
// src_addr bitfiled (RO) Reset=0
#define GDMAC_GDT0_SAR2_SRC_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT0_SAR2_SRC_ADDR_SHIFT           0 
#define GDMAC_GDT0_SAR2_SRC_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT0_SAR2_SRC_ADDR_BITWIDTH        32
// GDT0_DAR2 Register
#define GDMAC_GDT0_DAR2_OFS                      0x00000444
// dst_addr bitfiled (RO) Reset=0
#define GDMAC_GDT0_DAR2_DST_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT0_DAR2_DST_ADDR_SHIFT           0 
#define GDMAC_GDT0_DAR2_DST_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT0_DAR2_DST_ADDR_BITWIDTH        32
// GDT0_CCR2 Register
#define GDMAC_GDT0_CCR2_OFS                      0x00000448
// src_inc bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR2_SRC_INC_MASK             0x1
#define GDMAC_GDT0_CCR2_SRC_INC_SHIFT            0 
#define GDMAC_GDT0_CCR2_SRC_INC_BIT              0x1
#define GDMAC_GDT0_CCR2_SRC_INC_BITWIDTH         1
// src_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR2_SRC_BURST_SIZE_MASK      0xE
#define GDMAC_GDT0_CCR2_SRC_BURST_SIZE_SHIFT     1 
#define GDMAC_GDT0_CCR2_SRC_BURST_SIZE_BIT       0x7
#define GDMAC_GDT0_CCR2_SRC_BURST_SIZE_BITWIDTH  3
// src_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR2_SRC_BURST_LEN_MASK       0xF0
#define GDMAC_GDT0_CCR2_SRC_BURST_LEN_SHIFT      4 
#define GDMAC_GDT0_CCR2_SRC_BURST_LEN_BIT        0xF
#define GDMAC_GDT0_CCR2_SRC_BURST_LEN_BITWIDTH   4
// src_prot_ctrl bitfiled (RO) Reset=10
#define GDMAC_GDT0_CCR2_SRC_PROT_CTRL_MASK       0x700
#define GDMAC_GDT0_CCR2_SRC_PROT_CTRL_SHIFT      8 
#define GDMAC_GDT0_CCR2_SRC_PROT_CTRL_BIT        0x7
#define GDMAC_GDT0_CCR2_SRC_PROT_CTRL_BITWIDTH   3
// src_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR2_SRC_CACHE_CTRL_MASK      0x3800
#define GDMAC_GDT0_CCR2_SRC_CACHE_CTRL_SHIFT     11 
#define GDMAC_GDT0_CCR2_SRC_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT0_CCR2_SRC_CACHE_CTRL_BITWIDTH  3
// dst_inc bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR2_DST_INC_MASK             0x4000
#define GDMAC_GDT0_CCR2_DST_INC_SHIFT            14 
#define GDMAC_GDT0_CCR2_DST_INC_BIT              0x1
#define GDMAC_GDT0_CCR2_DST_INC_BITWIDTH         1
// dst_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR2_DST_BURST_SIZE_MASK      0x38000
#define GDMAC_GDT0_CCR2_DST_BURST_SIZE_SHIFT     15 
#define GDMAC_GDT0_CCR2_DST_BURST_SIZE_BIT       0x7
#define GDMAC_GDT0_CCR2_DST_BURST_SIZE_BITWIDTH  3
// dst_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR2_DST_BURST_LEN_MASK       0x3C0000
#define GDMAC_GDT0_CCR2_DST_BURST_LEN_SHIFT      18 
#define GDMAC_GDT0_CCR2_DST_BURST_LEN_BIT        0xF
#define GDMAC_GDT0_CCR2_DST_BURST_LEN_BITWIDTH   4
// dst_prot_ctrl bitfiled (RO) Reset=10
#define GDMAC_GDT0_CCR2_DST_PROT_CTRL_MASK       0x1C00000
#define GDMAC_GDT0_CCR2_DST_PROT_CTRL_SHIFT      22 
#define GDMAC_GDT0_CCR2_DST_PROT_CTRL_BIT        0x7
#define GDMAC_GDT0_CCR2_DST_PROT_CTRL_BITWIDTH   3
// dst_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR2_DST_CACHE_CTRL_MASK      0xE000000
#define GDMAC_GDT0_CCR2_DST_CACHE_CTRL_SHIFT     25 
#define GDMAC_GDT0_CCR2_DST_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT0_CCR2_DST_CACHE_CTRL_BITWIDTH  3
// endian_swap_size bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR2_ENDIAN_SWAP_SIZE_MASK    0x70000000
#define GDMAC_GDT0_CCR2_ENDIAN_SWAP_SIZE_SHIFT   28 
#define GDMAC_GDT0_CCR2_ENDIAN_SWAP_SIZE_BIT     0x7
#define GDMAC_GDT0_CCR2_ENDIAN_SWAP_SIZE_BITWIDTH 3
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR2_RESERVED_MASK            0x80000000
#define GDMAC_GDT0_CCR2_RESERVED_SHIFT           31 
#define GDMAC_GDT0_CCR2_RESERVED_BIT             0x1
#define GDMAC_GDT0_CCR2_RESERVED_BITWIDTH        1
// GDT0_LC0_2 Register
#define GDMAC_GDT0_LC0_2_OFS                     0x0000044C
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC0_2_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT0_LC0_2_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT0_LC0_2_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT0_LC0_2_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC0_2_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT0_LC0_2_RESERVED_SHIFT          8 
#define GDMAC_GDT0_LC0_2_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT0_LC0_2_RESERVED_BITWIDTH       24
// GDT0_LC1_2 Register
#define GDMAC_GDT0_LC1_2_OFS                     0x00000450
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC1_2_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT0_LC1_2_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT0_LC1_2_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT0_LC1_2_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC1_2_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT0_LC1_2_RESERVED_SHIFT          8 
#define GDMAC_GDT0_LC1_2_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT0_LC1_2_RESERVED_BITWIDTH       24
// GDT0_SAR3 Register
#define GDMAC_GDT0_SAR3_OFS                      0x00000460
// src_addr bitfiled (RO) Reset=0
#define GDMAC_GDT0_SAR3_SRC_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT0_SAR3_SRC_ADDR_SHIFT           0 
#define GDMAC_GDT0_SAR3_SRC_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT0_SAR3_SRC_ADDR_BITWIDTH        32
// GDT0_DAR3 Register
#define GDMAC_GDT0_DAR3_OFS                      0x00000464
// dst_addr bitfiled (RO) Reset=0
#define GDMAC_GDT0_DAR3_DST_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT0_DAR3_DST_ADDR_SHIFT           0 
#define GDMAC_GDT0_DAR3_DST_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT0_DAR3_DST_ADDR_BITWIDTH        32
// GDT0_CCR3 Register
#define GDMAC_GDT0_CCR3_OFS                      0x00000468
// src_inc bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR3_SRC_INC_MASK             0x1
#define GDMAC_GDT0_CCR3_SRC_INC_SHIFT            0 
#define GDMAC_GDT0_CCR3_SRC_INC_BIT              0x1
#define GDMAC_GDT0_CCR3_SRC_INC_BITWIDTH         1
// src_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR3_SRC_BURST_SIZE_MASK      0xE
#define GDMAC_GDT0_CCR3_SRC_BURST_SIZE_SHIFT     1 
#define GDMAC_GDT0_CCR3_SRC_BURST_SIZE_BIT       0x7
#define GDMAC_GDT0_CCR3_SRC_BURST_SIZE_BITWIDTH  3
// src_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR3_SRC_BURST_LEN_MASK       0xF0
#define GDMAC_GDT0_CCR3_SRC_BURST_LEN_SHIFT      4 
#define GDMAC_GDT0_CCR3_SRC_BURST_LEN_BIT        0xF
#define GDMAC_GDT0_CCR3_SRC_BURST_LEN_BITWIDTH   4
// src_prot_ctrl bitfiled (RO) Reset=10
#define GDMAC_GDT0_CCR3_SRC_PROT_CTRL_MASK       0x700
#define GDMAC_GDT0_CCR3_SRC_PROT_CTRL_SHIFT      8 
#define GDMAC_GDT0_CCR3_SRC_PROT_CTRL_BIT        0x7
#define GDMAC_GDT0_CCR3_SRC_PROT_CTRL_BITWIDTH   3
// src_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR3_SRC_CACHE_CTRL_MASK      0x3800
#define GDMAC_GDT0_CCR3_SRC_CACHE_CTRL_SHIFT     11 
#define GDMAC_GDT0_CCR3_SRC_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT0_CCR3_SRC_CACHE_CTRL_BITWIDTH  3
// dst_inc bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR3_DST_INC_MASK             0x4000
#define GDMAC_GDT0_CCR3_DST_INC_SHIFT            14 
#define GDMAC_GDT0_CCR3_DST_INC_BIT              0x1
#define GDMAC_GDT0_CCR3_DST_INC_BITWIDTH         1
// dst_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR3_DST_BURST_SIZE_MASK      0x38000
#define GDMAC_GDT0_CCR3_DST_BURST_SIZE_SHIFT     15 
#define GDMAC_GDT0_CCR3_DST_BURST_SIZE_BIT       0x7
#define GDMAC_GDT0_CCR3_DST_BURST_SIZE_BITWIDTH  3
// dst_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR3_DST_BURST_LEN_MASK       0x3C0000
#define GDMAC_GDT0_CCR3_DST_BURST_LEN_SHIFT      18 
#define GDMAC_GDT0_CCR3_DST_BURST_LEN_BIT        0xF
#define GDMAC_GDT0_CCR3_DST_BURST_LEN_BITWIDTH   4
// dst_prot_ctrl bitfiled (RO) Reset=10
#define GDMAC_GDT0_CCR3_DST_PROT_CTRL_MASK       0x1C00000
#define GDMAC_GDT0_CCR3_DST_PROT_CTRL_SHIFT      22 
#define GDMAC_GDT0_CCR3_DST_PROT_CTRL_BIT        0x7
#define GDMAC_GDT0_CCR3_DST_PROT_CTRL_BITWIDTH   3
// dst_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR3_DST_CACHE_CTRL_MASK      0xE000000
#define GDMAC_GDT0_CCR3_DST_CACHE_CTRL_SHIFT     25 
#define GDMAC_GDT0_CCR3_DST_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT0_CCR3_DST_CACHE_CTRL_BITWIDTH  3
// endian_swap_size bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR3_ENDIAN_SWAP_SIZE_MASK    0x70000000
#define GDMAC_GDT0_CCR3_ENDIAN_SWAP_SIZE_SHIFT   28 
#define GDMAC_GDT0_CCR3_ENDIAN_SWAP_SIZE_BIT     0x7
#define GDMAC_GDT0_CCR3_ENDIAN_SWAP_SIZE_BITWIDTH 3
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR3_RESERVED_MASK            0x80000000
#define GDMAC_GDT0_CCR3_RESERVED_SHIFT           31 
#define GDMAC_GDT0_CCR3_RESERVED_BIT             0x1
#define GDMAC_GDT0_CCR3_RESERVED_BITWIDTH        1
// GDT0_LC0_3 Register
#define GDMAC_GDT0_LC0_3_OFS                     0x0000046C
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC0_3_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT0_LC0_3_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT0_LC0_3_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT0_LC0_3_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC0_3_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT0_LC0_3_RESERVED_SHIFT          8 
#define GDMAC_GDT0_LC0_3_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT0_LC0_3_RESERVED_BITWIDTH       24
// GDT0_LC1_3 Register
#define GDMAC_GDT0_LC1_3_OFS                     0x00000470
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC1_3_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT0_LC1_3_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT0_LC1_3_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT0_LC1_3_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC1_3_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT0_LC1_3_RESERVED_SHIFT          8 
#define GDMAC_GDT0_LC1_3_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT0_LC1_3_RESERVED_BITWIDTH       24
// GDT0_SAR4 Register
#define GDMAC_GDT0_SAR4_OFS                      0x00000480
// src_addr bitfiled (RO) Reset=0
#define GDMAC_GDT0_SAR4_SRC_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT0_SAR4_SRC_ADDR_SHIFT           0 
#define GDMAC_GDT0_SAR4_SRC_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT0_SAR4_SRC_ADDR_BITWIDTH        32
// GDT0_DAR4 Register
#define GDMAC_GDT0_DAR4_OFS                      0x00000484
// dst_addr bitfiled (RO) Reset=0
#define GDMAC_GDT0_DAR4_DST_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT0_DAR4_DST_ADDR_SHIFT           0 
#define GDMAC_GDT0_DAR4_DST_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT0_DAR4_DST_ADDR_BITWIDTH        32
// GDT0_CCR4 Register
#define GDMAC_GDT0_CCR4_OFS                      0x00000488
// src_inc bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR4_SRC_INC_MASK             0x1
#define GDMAC_GDT0_CCR4_SRC_INC_SHIFT            0 
#define GDMAC_GDT0_CCR4_SRC_INC_BIT              0x1
#define GDMAC_GDT0_CCR4_SRC_INC_BITWIDTH         1
// src_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR4_SRC_BURST_SIZE_MASK      0xE
#define GDMAC_GDT0_CCR4_SRC_BURST_SIZE_SHIFT     1 
#define GDMAC_GDT0_CCR4_SRC_BURST_SIZE_BIT       0x7
#define GDMAC_GDT0_CCR4_SRC_BURST_SIZE_BITWIDTH  3
// src_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR4_SRC_BURST_LEN_MASK       0xF0
#define GDMAC_GDT0_CCR4_SRC_BURST_LEN_SHIFT      4 
#define GDMAC_GDT0_CCR4_SRC_BURST_LEN_BIT        0xF
#define GDMAC_GDT0_CCR4_SRC_BURST_LEN_BITWIDTH   4
// src_prot_ctrl bitfiled (RO) Reset=10
#define GDMAC_GDT0_CCR4_SRC_PROT_CTRL_MASK       0x700
#define GDMAC_GDT0_CCR4_SRC_PROT_CTRL_SHIFT      8 
#define GDMAC_GDT0_CCR4_SRC_PROT_CTRL_BIT        0x7
#define GDMAC_GDT0_CCR4_SRC_PROT_CTRL_BITWIDTH   3
// src_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR4_SRC_CACHE_CTRL_MASK      0x3800
#define GDMAC_GDT0_CCR4_SRC_CACHE_CTRL_SHIFT     11 
#define GDMAC_GDT0_CCR4_SRC_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT0_CCR4_SRC_CACHE_CTRL_BITWIDTH  3
// dst_inc bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR4_DST_INC_MASK             0x4000
#define GDMAC_GDT0_CCR4_DST_INC_SHIFT            14 
#define GDMAC_GDT0_CCR4_DST_INC_BIT              0x1
#define GDMAC_GDT0_CCR4_DST_INC_BITWIDTH         1
// dst_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR4_DST_BURST_SIZE_MASK      0x38000
#define GDMAC_GDT0_CCR4_DST_BURST_SIZE_SHIFT     15 
#define GDMAC_GDT0_CCR4_DST_BURST_SIZE_BIT       0x7
#define GDMAC_GDT0_CCR4_DST_BURST_SIZE_BITWIDTH  3
// dst_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR4_DST_BURST_LEN_MASK       0x3C0000
#define GDMAC_GDT0_CCR4_DST_BURST_LEN_SHIFT      18 
#define GDMAC_GDT0_CCR4_DST_BURST_LEN_BIT        0xF
#define GDMAC_GDT0_CCR4_DST_BURST_LEN_BITWIDTH   4
// dst_prot_ctrl bitfiled (RO) Reset=10
#define GDMAC_GDT0_CCR4_DST_PROT_CTRL_MASK       0x1C00000
#define GDMAC_GDT0_CCR4_DST_PROT_CTRL_SHIFT      22 
#define GDMAC_GDT0_CCR4_DST_PROT_CTRL_BIT        0x7
#define GDMAC_GDT0_CCR4_DST_PROT_CTRL_BITWIDTH   3
// dst_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR4_DST_CACHE_CTRL_MASK      0xE000000
#define GDMAC_GDT0_CCR4_DST_CACHE_CTRL_SHIFT     25 
#define GDMAC_GDT0_CCR4_DST_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT0_CCR4_DST_CACHE_CTRL_BITWIDTH  3
// endian_swap_size bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR4_ENDIAN_SWAP_SIZE_MASK    0x70000000
#define GDMAC_GDT0_CCR4_ENDIAN_SWAP_SIZE_SHIFT   28 
#define GDMAC_GDT0_CCR4_ENDIAN_SWAP_SIZE_BIT     0x7
#define GDMAC_GDT0_CCR4_ENDIAN_SWAP_SIZE_BITWIDTH 3
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR4_RESERVED_MASK            0x80000000
#define GDMAC_GDT0_CCR4_RESERVED_SHIFT           31 
#define GDMAC_GDT0_CCR4_RESERVED_BIT             0x1
#define GDMAC_GDT0_CCR4_RESERVED_BITWIDTH        1
// GDT0_LC0_4 Register
#define GDMAC_GDT0_LC0_4_OFS                     0x0000048C
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC0_4_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT0_LC0_4_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT0_LC0_4_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT0_LC0_4_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC0_4_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT0_LC0_4_RESERVED_SHIFT          8 
#define GDMAC_GDT0_LC0_4_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT0_LC0_4_RESERVED_BITWIDTH       24
// GDT0_LC1_4 Register
#define GDMAC_GDT0_LC1_4_OFS                     0x00000490
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC1_4_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT0_LC1_4_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT0_LC1_4_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT0_LC1_4_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC1_4_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT0_LC1_4_RESERVED_SHIFT          8 
#define GDMAC_GDT0_LC1_4_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT0_LC1_4_RESERVED_BITWIDTH       24
// GDT0_SAR5 Register
#define GDMAC_GDT0_SAR5_OFS                      0x000004A0
// src_addr bitfiled (RO) Reset=0
#define GDMAC_GDT0_SAR5_SRC_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT0_SAR5_SRC_ADDR_SHIFT           0 
#define GDMAC_GDT0_SAR5_SRC_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT0_SAR5_SRC_ADDR_BITWIDTH        32
// GDT0_DAR5 Register
#define GDMAC_GDT0_DAR5_OFS                      0x000004A4
// dst_addr bitfiled (RO) Reset=0
#define GDMAC_GDT0_DAR5_DST_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT0_DAR5_DST_ADDR_SHIFT           0 
#define GDMAC_GDT0_DAR5_DST_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT0_DAR5_DST_ADDR_BITWIDTH        32
// GDT0_CCR5 Register
#define GDMAC_GDT0_CCR5_OFS                      0x000004A8
// src_inc bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR5_SRC_INC_MASK             0x1
#define GDMAC_GDT0_CCR5_SRC_INC_SHIFT            0 
#define GDMAC_GDT0_CCR5_SRC_INC_BIT              0x1
#define GDMAC_GDT0_CCR5_SRC_INC_BITWIDTH         1
// src_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR5_SRC_BURST_SIZE_MASK      0xE
#define GDMAC_GDT0_CCR5_SRC_BURST_SIZE_SHIFT     1 
#define GDMAC_GDT0_CCR5_SRC_BURST_SIZE_BIT       0x7
#define GDMAC_GDT0_CCR5_SRC_BURST_SIZE_BITWIDTH  3
// src_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR5_SRC_BURST_LEN_MASK       0xF0
#define GDMAC_GDT0_CCR5_SRC_BURST_LEN_SHIFT      4 
#define GDMAC_GDT0_CCR5_SRC_BURST_LEN_BIT        0xF
#define GDMAC_GDT0_CCR5_SRC_BURST_LEN_BITWIDTH   4
// src_prot_ctrl bitfiled (RO) Reset=10
#define GDMAC_GDT0_CCR5_SRC_PROT_CTRL_MASK       0x700
#define GDMAC_GDT0_CCR5_SRC_PROT_CTRL_SHIFT      8 
#define GDMAC_GDT0_CCR5_SRC_PROT_CTRL_BIT        0x7
#define GDMAC_GDT0_CCR5_SRC_PROT_CTRL_BITWIDTH   3
// src_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR5_SRC_CACHE_CTRL_MASK      0x3800
#define GDMAC_GDT0_CCR5_SRC_CACHE_CTRL_SHIFT     11 
#define GDMAC_GDT0_CCR5_SRC_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT0_CCR5_SRC_CACHE_CTRL_BITWIDTH  3
// dst_inc bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR5_DST_INC_MASK             0x4000
#define GDMAC_GDT0_CCR5_DST_INC_SHIFT            14 
#define GDMAC_GDT0_CCR5_DST_INC_BIT              0x1
#define GDMAC_GDT0_CCR5_DST_INC_BITWIDTH         1
// dst_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR5_DST_BURST_SIZE_MASK      0x38000
#define GDMAC_GDT0_CCR5_DST_BURST_SIZE_SHIFT     15 
#define GDMAC_GDT0_CCR5_DST_BURST_SIZE_BIT       0x7
#define GDMAC_GDT0_CCR5_DST_BURST_SIZE_BITWIDTH  3
// dst_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR5_DST_BURST_LEN_MASK       0x3C0000
#define GDMAC_GDT0_CCR5_DST_BURST_LEN_SHIFT      18 
#define GDMAC_GDT0_CCR5_DST_BURST_LEN_BIT        0xF
#define GDMAC_GDT0_CCR5_DST_BURST_LEN_BITWIDTH   4
// dst_prot_ctrl bitfiled (RO) Reset=10
#define GDMAC_GDT0_CCR5_DST_PROT_CTRL_MASK       0x1C00000
#define GDMAC_GDT0_CCR5_DST_PROT_CTRL_SHIFT      22 
#define GDMAC_GDT0_CCR5_DST_PROT_CTRL_BIT        0x7
#define GDMAC_GDT0_CCR5_DST_PROT_CTRL_BITWIDTH   3
// dst_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR5_DST_CACHE_CTRL_MASK      0xE000000
#define GDMAC_GDT0_CCR5_DST_CACHE_CTRL_SHIFT     25 
#define GDMAC_GDT0_CCR5_DST_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT0_CCR5_DST_CACHE_CTRL_BITWIDTH  3
// endian_swap_size bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR5_ENDIAN_SWAP_SIZE_MASK    0x70000000
#define GDMAC_GDT0_CCR5_ENDIAN_SWAP_SIZE_SHIFT   28 
#define GDMAC_GDT0_CCR5_ENDIAN_SWAP_SIZE_BIT     0x7
#define GDMAC_GDT0_CCR5_ENDIAN_SWAP_SIZE_BITWIDTH 3
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR5_RESERVED_MASK            0x80000000
#define GDMAC_GDT0_CCR5_RESERVED_SHIFT           31 
#define GDMAC_GDT0_CCR5_RESERVED_BIT             0x1
#define GDMAC_GDT0_CCR5_RESERVED_BITWIDTH        1
// GDT0_LC0_5 Register
#define GDMAC_GDT0_LC0_5_OFS                     0x000004AC
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC0_5_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT0_LC0_5_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT0_LC0_5_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT0_LC0_5_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC0_5_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT0_LC0_5_RESERVED_SHIFT          8 
#define GDMAC_GDT0_LC0_5_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT0_LC0_5_RESERVED_BITWIDTH       24
// GDT0_LC1_5 Register
#define GDMAC_GDT0_LC1_5_OFS                     0x000004B0
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC1_5_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT0_LC1_5_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT0_LC1_5_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT0_LC1_5_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC1_5_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT0_LC1_5_RESERVED_SHIFT          8 
#define GDMAC_GDT0_LC1_5_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT0_LC1_5_RESERVED_BITWIDTH       24
// GDT0_SAR6 Register
#define GDMAC_GDT0_SAR6_OFS                      0x000004C0
// src_addr bitfiled (RO) Reset=0
#define GDMAC_GDT0_SAR6_SRC_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT0_SAR6_SRC_ADDR_SHIFT           0 
#define GDMAC_GDT0_SAR6_SRC_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT0_SAR6_SRC_ADDR_BITWIDTH        32
// GDT0_DAR6 Register
#define GDMAC_GDT0_DAR6_OFS                      0x000004C4
// dst_addr bitfiled (RO) Reset=0
#define GDMAC_GDT0_DAR6_DST_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT0_DAR6_DST_ADDR_SHIFT           0 
#define GDMAC_GDT0_DAR6_DST_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT0_DAR6_DST_ADDR_BITWIDTH        32
// GDT0_CCR6 Register
#define GDMAC_GDT0_CCR6_OFS                      0x000004C8
// src_inc bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR6_SRC_INC_MASK             0x1
#define GDMAC_GDT0_CCR6_SRC_INC_SHIFT            0 
#define GDMAC_GDT0_CCR6_SRC_INC_BIT              0x1
#define GDMAC_GDT0_CCR6_SRC_INC_BITWIDTH         1
// src_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR6_SRC_BURST_SIZE_MASK      0xE
#define GDMAC_GDT0_CCR6_SRC_BURST_SIZE_SHIFT     1 
#define GDMAC_GDT0_CCR6_SRC_BURST_SIZE_BIT       0x7
#define GDMAC_GDT0_CCR6_SRC_BURST_SIZE_BITWIDTH  3
// src_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR6_SRC_BURST_LEN_MASK       0xF0
#define GDMAC_GDT0_CCR6_SRC_BURST_LEN_SHIFT      4 
#define GDMAC_GDT0_CCR6_SRC_BURST_LEN_BIT        0xF
#define GDMAC_GDT0_CCR6_SRC_BURST_LEN_BITWIDTH   4
// src_prot_ctrl bitfiled (RO) Reset=10
#define GDMAC_GDT0_CCR6_SRC_PROT_CTRL_MASK       0x700
#define GDMAC_GDT0_CCR6_SRC_PROT_CTRL_SHIFT      8 
#define GDMAC_GDT0_CCR6_SRC_PROT_CTRL_BIT        0x7
#define GDMAC_GDT0_CCR6_SRC_PROT_CTRL_BITWIDTH   3
// src_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR6_SRC_CACHE_CTRL_MASK      0x3800
#define GDMAC_GDT0_CCR6_SRC_CACHE_CTRL_SHIFT     11 
#define GDMAC_GDT0_CCR6_SRC_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT0_CCR6_SRC_CACHE_CTRL_BITWIDTH  3
// dst_inc bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR6_DST_INC_MASK             0x4000
#define GDMAC_GDT0_CCR6_DST_INC_SHIFT            14 
#define GDMAC_GDT0_CCR6_DST_INC_BIT              0x1
#define GDMAC_GDT0_CCR6_DST_INC_BITWIDTH         1
// dst_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR6_DST_BURST_SIZE_MASK      0x38000
#define GDMAC_GDT0_CCR6_DST_BURST_SIZE_SHIFT     15 
#define GDMAC_GDT0_CCR6_DST_BURST_SIZE_BIT       0x7
#define GDMAC_GDT0_CCR6_DST_BURST_SIZE_BITWIDTH  3
// dst_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR6_DST_BURST_LEN_MASK       0x3C0000
#define GDMAC_GDT0_CCR6_DST_BURST_LEN_SHIFT      18 
#define GDMAC_GDT0_CCR6_DST_BURST_LEN_BIT        0xF
#define GDMAC_GDT0_CCR6_DST_BURST_LEN_BITWIDTH   4
// dst_prot_ctrl bitfiled (RO) Reset=10
#define GDMAC_GDT0_CCR6_DST_PROT_CTRL_MASK       0x1C00000
#define GDMAC_GDT0_CCR6_DST_PROT_CTRL_SHIFT      22 
#define GDMAC_GDT0_CCR6_DST_PROT_CTRL_BIT        0x7
#define GDMAC_GDT0_CCR6_DST_PROT_CTRL_BITWIDTH   3
// dst_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR6_DST_CACHE_CTRL_MASK      0xE000000
#define GDMAC_GDT0_CCR6_DST_CACHE_CTRL_SHIFT     25 
#define GDMAC_GDT0_CCR6_DST_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT0_CCR6_DST_CACHE_CTRL_BITWIDTH  3
// endian_swap_size bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR6_ENDIAN_SWAP_SIZE_MASK    0x70000000
#define GDMAC_GDT0_CCR6_ENDIAN_SWAP_SIZE_SHIFT   28 
#define GDMAC_GDT0_CCR6_ENDIAN_SWAP_SIZE_BIT     0x7
#define GDMAC_GDT0_CCR6_ENDIAN_SWAP_SIZE_BITWIDTH 3
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR6_RESERVED_MASK            0x80000000
#define GDMAC_GDT0_CCR6_RESERVED_SHIFT           31 
#define GDMAC_GDT0_CCR6_RESERVED_BIT             0x1
#define GDMAC_GDT0_CCR6_RESERVED_BITWIDTH        1
// GDT0_LC0_6 Register
#define GDMAC_GDT0_LC0_6_OFS                     0x000004CC
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC0_6_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT0_LC0_6_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT0_LC0_6_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT0_LC0_6_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC0_6_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT0_LC0_6_RESERVED_SHIFT          8 
#define GDMAC_GDT0_LC0_6_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT0_LC0_6_RESERVED_BITWIDTH       24
// GDT0_LC1_6 Register
#define GDMAC_GDT0_LC1_6_OFS                     0x000004D0
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC1_6_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT0_LC1_6_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT0_LC1_6_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT0_LC1_6_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC1_6_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT0_LC1_6_RESERVED_SHIFT          8 
#define GDMAC_GDT0_LC1_6_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT0_LC1_6_RESERVED_BITWIDTH       24
// GDT0_SAR7 Register
#define GDMAC_GDT0_SAR7_OFS                      0x000004E0
// src_addr bitfiled (RO) Reset=0
#define GDMAC_GDT0_SAR7_SRC_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT0_SAR7_SRC_ADDR_SHIFT           0 
#define GDMAC_GDT0_SAR7_SRC_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT0_SAR7_SRC_ADDR_BITWIDTH        32
// GDT0_DAR7 Register
#define GDMAC_GDT0_DAR7_OFS                      0x000004E4
// dst_addr bitfiled (RO) Reset=0
#define GDMAC_GDT0_DAR7_DST_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT0_DAR7_DST_ADDR_SHIFT           0 
#define GDMAC_GDT0_DAR7_DST_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT0_DAR7_DST_ADDR_BITWIDTH        32
// GDT0_CCR7 Register
#define GDMAC_GDT0_CCR7_OFS                      0x000004E8
// src_inc bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR7_SRC_INC_MASK             0x1
#define GDMAC_GDT0_CCR7_SRC_INC_SHIFT            0 
#define GDMAC_GDT0_CCR7_SRC_INC_BIT              0x1
#define GDMAC_GDT0_CCR7_SRC_INC_BITWIDTH         1
// src_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR7_SRC_BURST_SIZE_MASK      0xE
#define GDMAC_GDT0_CCR7_SRC_BURST_SIZE_SHIFT     1 
#define GDMAC_GDT0_CCR7_SRC_BURST_SIZE_BIT       0x7
#define GDMAC_GDT0_CCR7_SRC_BURST_SIZE_BITWIDTH  3
// src_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR7_SRC_BURST_LEN_MASK       0xF0
#define GDMAC_GDT0_CCR7_SRC_BURST_LEN_SHIFT      4 
#define GDMAC_GDT0_CCR7_SRC_BURST_LEN_BIT        0xF
#define GDMAC_GDT0_CCR7_SRC_BURST_LEN_BITWIDTH   4
// src_prot_ctrl bitfiled (RO) Reset=10
#define GDMAC_GDT0_CCR7_SRC_PROT_CTRL_MASK       0x700
#define GDMAC_GDT0_CCR7_SRC_PROT_CTRL_SHIFT      8 
#define GDMAC_GDT0_CCR7_SRC_PROT_CTRL_BIT        0x7
#define GDMAC_GDT0_CCR7_SRC_PROT_CTRL_BITWIDTH   3
// src_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR7_SRC_CACHE_CTRL_MASK      0x3800
#define GDMAC_GDT0_CCR7_SRC_CACHE_CTRL_SHIFT     11 
#define GDMAC_GDT0_CCR7_SRC_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT0_CCR7_SRC_CACHE_CTRL_BITWIDTH  3
// dst_inc bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR7_DST_INC_MASK             0x4000
#define GDMAC_GDT0_CCR7_DST_INC_SHIFT            14 
#define GDMAC_GDT0_CCR7_DST_INC_BIT              0x1
#define GDMAC_GDT0_CCR7_DST_INC_BITWIDTH         1
// dst_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR7_DST_BURST_SIZE_MASK      0x38000
#define GDMAC_GDT0_CCR7_DST_BURST_SIZE_SHIFT     15 
#define GDMAC_GDT0_CCR7_DST_BURST_SIZE_BIT       0x7
#define GDMAC_GDT0_CCR7_DST_BURST_SIZE_BITWIDTH  3
// dst_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR7_DST_BURST_LEN_MASK       0x3C0000
#define GDMAC_GDT0_CCR7_DST_BURST_LEN_SHIFT      18 
#define GDMAC_GDT0_CCR7_DST_BURST_LEN_BIT        0xF
#define GDMAC_GDT0_CCR7_DST_BURST_LEN_BITWIDTH   4
// dst_prot_ctrl bitfiled (RO) Reset=10
#define GDMAC_GDT0_CCR7_DST_PROT_CTRL_MASK       0x1C00000
#define GDMAC_GDT0_CCR7_DST_PROT_CTRL_SHIFT      22 
#define GDMAC_GDT0_CCR7_DST_PROT_CTRL_BIT        0x7
#define GDMAC_GDT0_CCR7_DST_PROT_CTRL_BITWIDTH   3
// dst_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR7_DST_CACHE_CTRL_MASK      0xE000000
#define GDMAC_GDT0_CCR7_DST_CACHE_CTRL_SHIFT     25 
#define GDMAC_GDT0_CCR7_DST_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT0_CCR7_DST_CACHE_CTRL_BITWIDTH  3
// endian_swap_size bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR7_ENDIAN_SWAP_SIZE_MASK    0x70000000
#define GDMAC_GDT0_CCR7_ENDIAN_SWAP_SIZE_SHIFT   28 
#define GDMAC_GDT0_CCR7_ENDIAN_SWAP_SIZE_BIT     0x7
#define GDMAC_GDT0_CCR7_ENDIAN_SWAP_SIZE_BITWIDTH 3
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_CCR7_RESERVED_MASK            0x80000000
#define GDMAC_GDT0_CCR7_RESERVED_SHIFT           31 
#define GDMAC_GDT0_CCR7_RESERVED_BIT             0x1
#define GDMAC_GDT0_CCR7_RESERVED_BITWIDTH        1
// GDT0_LC0_7 Register
#define GDMAC_GDT0_LC0_7_OFS                     0x000004EC
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC0_7_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT0_LC0_7_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT0_LC0_7_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT0_LC0_7_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC0_7_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT0_LC0_7_RESERVED_SHIFT          8 
#define GDMAC_GDT0_LC0_7_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT0_LC0_7_RESERVED_BITWIDTH       24
// GDT0_LC1_7 Register
#define GDMAC_GDT0_LC1_7_OFS                     0x000004F0
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC1_7_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT0_LC1_7_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT0_LC1_7_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT0_LC1_7_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_LC1_7_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT0_LC1_7_RESERVED_SHIFT          8 
#define GDMAC_GDT0_LC1_7_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT0_LC1_7_RESERVED_BITWIDTH       24
// GDT0_DBGSTATUS Register
#define GDMAC_GDT0_DBGSTATUS_OFS                 0x00000D00
// dbg_status bitfiled (RO) Reset=0
#define GDMAC_GDT0_DBGSTATUS_DBG_STATUS_MASK     0x1
#define GDMAC_GDT0_DBGSTATUS_DBG_STATUS_SHIFT    0 
#define GDMAC_GDT0_DBGSTATUS_DBG_STATUS_BIT      0x1
#define GDMAC_GDT0_DBGSTATUS_DBG_STATUS_BITWIDTH 1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_DBGSTATUS_RESERVED_MASK       0xFFFFFFFE
#define GDMAC_GDT0_DBGSTATUS_RESERVED_SHIFT      1 
#define GDMAC_GDT0_DBGSTATUS_RESERVED_BIT        0x7FFFFFFF
#define GDMAC_GDT0_DBGSTATUS_RESERVED_BITWIDTH   31
// GDT0_DBGCMD Register
#define GDMAC_GDT0_DBGCMD_OFS                    0x00000D04
// dbgcmd bitfiled (RW) Reset=0
#define GDMAC_GDT0_DBGCMD_DBGCMD_MASK            0x3
#define GDMAC_GDT0_DBGCMD_DBGCMD_SHIFT           0 
#define GDMAC_GDT0_DBGCMD_DBGCMD_BIT             0x3
#define GDMAC_GDT0_DBGCMD_DBGCMD_BITWIDTH        2
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_DBGCMD_RESERVED_MASK          0xFFFFFFFC
#define GDMAC_GDT0_DBGCMD_RESERVED_SHIFT         2 
#define GDMAC_GDT0_DBGCMD_RESERVED_BIT           0x3FFFFFFF
#define GDMAC_GDT0_DBGCMD_RESERVED_BITWIDTH      30
// GDT0_DBGINST0 Register
#define GDMAC_GDT0_DBGINST0_OFS                  0x00000D08
// Debug_thread bitfiled (RW) Reset=0
#define GDMAC_GDT0_DBGINST0_DEBUG_THREAD_MASK    0x1
#define GDMAC_GDT0_DBGINST0_DEBUG_THREAD_SHIFT   0 
#define GDMAC_GDT0_DBGINST0_DEBUG_THREAD_BIT     0x1
#define GDMAC_GDT0_DBGINST0_DEBUG_THREAD_BITWIDTH 1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT0_DBGINST0_RESERVED2_MASK       0xFE
#define GDMAC_GDT0_DBGINST0_RESERVED2_SHIFT      1 
#define GDMAC_GDT0_DBGINST0_RESERVED2_BIT        0x7F
#define GDMAC_GDT0_DBGINST0_RESERVED2_BITWIDTH   7
// Channel_number bitfiled (RW) Reset=0
#define GDMAC_GDT0_DBGINST0_CHANNEL_NUMBER_MASK  0x700
#define GDMAC_GDT0_DBGINST0_CHANNEL_NUMBER_SHIFT 8 
#define GDMAC_GDT0_DBGINST0_CHANNEL_NUMBER_BIT   0x7
#define GDMAC_GDT0_DBGINST0_CHANNEL_NUMBER_BITWIDTH 3
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_DBGINST0_RESERVED_MASK        0xF800
#define GDMAC_GDT0_DBGINST0_RESERVED_SHIFT       11 
#define GDMAC_GDT0_DBGINST0_RESERVED_BIT         0x1F
#define GDMAC_GDT0_DBGINST0_RESERVED_BITWIDTH    5
// Instruction_byte_0 bitfiled (RW) Reset=0
#define GDMAC_GDT0_DBGINST0_INSTRUCTION_BYTE_0_MASK 0xFF0000
#define GDMAC_GDT0_DBGINST0_INSTRUCTION_BYTE_0_SHIFT 16 
#define GDMAC_GDT0_DBGINST0_INSTRUCTION_BYTE_0_BIT 0xFF
#define GDMAC_GDT0_DBGINST0_INSTRUCTION_BYTE_0_BITWIDTH 8
// Instruction_byte_1 bitfiled (RW) Reset=0
#define GDMAC_GDT0_DBGINST0_INSTRUCTION_BYTE_1_MASK 0xFF000000
#define GDMAC_GDT0_DBGINST0_INSTRUCTION_BYTE_1_SHIFT 24 
#define GDMAC_GDT0_DBGINST0_INSTRUCTION_BYTE_1_BIT 0xFF
#define GDMAC_GDT0_DBGINST0_INSTRUCTION_BYTE_1_BITWIDTH 8
// GDT0_DBGINST1 Register
#define GDMAC_GDT0_DBGINST1_OFS                  0x00000D0C
// Instruction_byte_2 bitfiled (RW) Reset=0
#define GDMAC_GDT0_DBGINST1_INSTRUCTION_BYTE_2_MASK 0xFF
#define GDMAC_GDT0_DBGINST1_INSTRUCTION_BYTE_2_SHIFT 0 
#define GDMAC_GDT0_DBGINST1_INSTRUCTION_BYTE_2_BIT 0xFF
#define GDMAC_GDT0_DBGINST1_INSTRUCTION_BYTE_2_BITWIDTH 8
// Instruction_byte_3 bitfiled (RW) Reset=0
#define GDMAC_GDT0_DBGINST1_INSTRUCTION_BYTE_3_MASK 0xFF00
#define GDMAC_GDT0_DBGINST1_INSTRUCTION_BYTE_3_SHIFT 8 
#define GDMAC_GDT0_DBGINST1_INSTRUCTION_BYTE_3_BIT 0xFF
#define GDMAC_GDT0_DBGINST1_INSTRUCTION_BYTE_3_BITWIDTH 8
// Instruction_byte_4 bitfiled (RW) Reset=0
#define GDMAC_GDT0_DBGINST1_INSTRUCTION_BYTE_4_MASK 0xFF0000
#define GDMAC_GDT0_DBGINST1_INSTRUCTION_BYTE_4_SHIFT 16 
#define GDMAC_GDT0_DBGINST1_INSTRUCTION_BYTE_4_BIT 0xFF
#define GDMAC_GDT0_DBGINST1_INSTRUCTION_BYTE_4_BITWIDTH 8
// Instruction_byte_5 bitfiled (RW) Reset=0
#define GDMAC_GDT0_DBGINST1_INSTRUCTION_BYTE_5_MASK 0xFF000000
#define GDMAC_GDT0_DBGINST1_INSTRUCTION_BYTE_5_SHIFT 24 
#define GDMAC_GDT0_DBGINST1_INSTRUCTION_BYTE_5_BIT 0xFF
#define GDMAC_GDT0_DBGINST1_INSTRUCTION_BYTE_5_BITWIDTH 8
// GDT0_CR0 Register
#define GDMAC_GDT0_CR0_OFS                       0x00000E00
// periph_req bitfiled (RO) Reset=1
#define GDMAC_GDT0_CR0_PERIPH_REQ_MASK           0x1
#define GDMAC_GDT0_CR0_PERIPH_REQ_SHIFT          0 
#define GDMAC_GDT0_CR0_PERIPH_REQ_BIT            0x1
#define GDMAC_GDT0_CR0_PERIPH_REQ_BITWIDTH       1
// boot_en bitfiled (RO) Reset=0
#define GDMAC_GDT0_CR0_BOOT_EN_MASK              0x2
#define GDMAC_GDT0_CR0_BOOT_EN_SHIFT             1 
#define GDMAC_GDT0_CR0_BOOT_EN_BIT               0x1
#define GDMAC_GDT0_CR0_BOOT_EN_BITWIDTH          1
// mgr_ns_at_rst bitfiled (RO) Reset=1
#define GDMAC_GDT0_CR0_MGR_NS_AT_RST_MASK        0x4
#define GDMAC_GDT0_CR0_MGR_NS_AT_RST_SHIFT       2 
#define GDMAC_GDT0_CR0_MGR_NS_AT_RST_BIT         0x1
#define GDMAC_GDT0_CR0_MGR_NS_AT_RST_BITWIDTH    1
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT0_CR0_RESERVED3_MASK            0x8
#define GDMAC_GDT0_CR0_RESERVED3_SHIFT           3 
#define GDMAC_GDT0_CR0_RESERVED3_BIT             0x1
#define GDMAC_GDT0_CR0_RESERVED3_BITWIDTH        1
// num_chnls bitfiled (RO) Reset=111
#define GDMAC_GDT0_CR0_NUM_CHNLS_MASK            0x70
#define GDMAC_GDT0_CR0_NUM_CHNLS_SHIFT           4 
#define GDMAC_GDT0_CR0_NUM_CHNLS_BIT             0x7
#define GDMAC_GDT0_CR0_NUM_CHNLS_BITWIDTH        3
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT0_CR0_RESERVED2_MASK            0xF80
#define GDMAC_GDT0_CR0_RESERVED2_SHIFT           7 
#define GDMAC_GDT0_CR0_RESERVED2_BIT             0x1F
#define GDMAC_GDT0_CR0_RESERVED2_BITWIDTH        5
// num_periph_req bitfiled (RO) Reset=11111
#define GDMAC_GDT0_CR0_NUM_PERIPH_REQ_MASK       0x1F000
#define GDMAC_GDT0_CR0_NUM_PERIPH_REQ_SHIFT      12 
#define GDMAC_GDT0_CR0_NUM_PERIPH_REQ_BIT        0x1F
#define GDMAC_GDT0_CR0_NUM_PERIPH_REQ_BITWIDTH   5
// num_events bitfiled (RO) Reset=11111
#define GDMAC_GDT0_CR0_NUM_EVENTS_MASK           0x3E0000
#define GDMAC_GDT0_CR0_NUM_EVENTS_SHIFT          17 
#define GDMAC_GDT0_CR0_NUM_EVENTS_BIT            0x1F
#define GDMAC_GDT0_CR0_NUM_EVENTS_BITWIDTH       5
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_CR0_RESERVED_MASK             0xFFC00000
#define GDMAC_GDT0_CR0_RESERVED_SHIFT            22 
#define GDMAC_GDT0_CR0_RESERVED_BIT              0x3FF
#define GDMAC_GDT0_CR0_RESERVED_BITWIDTH         10
// GDT0_CR1 Register
#define GDMAC_GDT0_CR1_OFS                       0x00000E04
// i_cache_len bitfiled (RO) Reset=101
#define GDMAC_GDT0_CR1_I_CACHE_LEN_MASK          0x7
#define GDMAC_GDT0_CR1_I_CACHE_LEN_SHIFT         0 
#define GDMAC_GDT0_CR1_I_CACHE_LEN_BIT           0x7
#define GDMAC_GDT0_CR1_I_CACHE_LEN_BITWIDTH      3
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT0_CR1_RESERVED2_MASK            0x8
#define GDMAC_GDT0_CR1_RESERVED2_SHIFT           3 
#define GDMAC_GDT0_CR1_RESERVED2_BIT             0x1
#define GDMAC_GDT0_CR1_RESERVED2_BITWIDTH        1
// num_i_cache_lines bitfiled (RO) Reset=111
#define GDMAC_GDT0_CR1_NUM_I_CACHE_LINES_MASK    0xF0
#define GDMAC_GDT0_CR1_NUM_I_CACHE_LINES_SHIFT   4 
#define GDMAC_GDT0_CR1_NUM_I_CACHE_LINES_BIT     0xF
#define GDMAC_GDT0_CR1_NUM_I_CACHE_LINES_BITWIDTH 4
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_CR1_RESERVED_MASK             0xFFFFFF00
#define GDMAC_GDT0_CR1_RESERVED_SHIFT            8 
#define GDMAC_GDT0_CR1_RESERVED_BIT              0xFFFFFF
#define GDMAC_GDT0_CR1_RESERVED_BITWIDTH         24
// GDT0_CR2 Register
#define GDMAC_GDT0_CR2_OFS                       0x00000E08
// boot_addr bitfiled (RO) Reset=0
#define GDMAC_GDT0_CR2_BOOT_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT0_CR2_BOOT_ADDR_SHIFT           0 
#define GDMAC_GDT0_CR2_BOOT_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT0_CR2_BOOT_ADDR_BITWIDTH        32
// GDT0_CR3 Register
#define GDMAC_GDT0_CR3_OFS                       0x00000E0C
// INS bitfiled (RO) Reset=11111111111111111111111111111111
#define GDMAC_GDT0_CR3_INS_MASK                  0xFFFFFFFF
#define GDMAC_GDT0_CR3_INS_SHIFT                 0 
#define GDMAC_GDT0_CR3_INS_BIT                   0xFFFFFFFF
#define GDMAC_GDT0_CR3_INS_BITWIDTH              32
// GDT0_CR4 Register
#define GDMAC_GDT0_CR4_OFS                       0x00000E10
// PNS bitfiled (RO) Reset=11111111111111111111111111111111
#define GDMAC_GDT0_CR4_PNS_MASK                  0xFFFFFFFF
#define GDMAC_GDT0_CR4_PNS_SHIFT                 0 
#define GDMAC_GDT0_CR4_PNS_BIT                   0xFFFFFFFF
#define GDMAC_GDT0_CR4_PNS_BITWIDTH              32
// GDT0_CRD Register
#define GDMAC_GDT0_CRD_OFS                       0x00000E14
// data_width bitfiled (RO) Reset=11
#define GDMAC_GDT0_CRD_DATA_WIDTH_MASK           0x7
#define GDMAC_GDT0_CRD_DATA_WIDTH_SHIFT          0 
#define GDMAC_GDT0_CRD_DATA_WIDTH_BIT            0x7
#define GDMAC_GDT0_CRD_DATA_WIDTH_BITWIDTH       3
// reserved4 bitfiled (RO) Reset=0
#define GDMAC_GDT0_CRD_RESERVED4_MASK            0x8
#define GDMAC_GDT0_CRD_RESERVED4_SHIFT           3 
#define GDMAC_GDT0_CRD_RESERVED4_BIT             0x1
#define GDMAC_GDT0_CRD_RESERVED4_BITWIDTH        1
// wr_cap bitfiled (RO) Reset=11
#define GDMAC_GDT0_CRD_WR_CAP_MASK               0x70
#define GDMAC_GDT0_CRD_WR_CAP_SHIFT              4 
#define GDMAC_GDT0_CRD_WR_CAP_BIT                0x7
#define GDMAC_GDT0_CRD_WR_CAP_BITWIDTH           3
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT0_CRD_RESERVED3_MASK            0x80
#define GDMAC_GDT0_CRD_RESERVED3_SHIFT           7 
#define GDMAC_GDT0_CRD_RESERVED3_BIT             0x1
#define GDMAC_GDT0_CRD_RESERVED3_BITWIDTH        1
// wr_q_dep bitfiled (RO) Reset=111
#define GDMAC_GDT0_CRD_WR_Q_DEP_MASK             0xF00
#define GDMAC_GDT0_CRD_WR_Q_DEP_SHIFT            8 
#define GDMAC_GDT0_CRD_WR_Q_DEP_BIT              0xF
#define GDMAC_GDT0_CRD_WR_Q_DEP_BITWIDTH         4
// rd_cap bitfiled (RO) Reset=11
#define GDMAC_GDT0_CRD_RD_CAP_MASK               0x7000
#define GDMAC_GDT0_CRD_RD_CAP_SHIFT              12 
#define GDMAC_GDT0_CRD_RD_CAP_BIT                0x7
#define GDMAC_GDT0_CRD_RD_CAP_BITWIDTH           3
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT0_CRD_RESERVED2_MASK            0x8000
#define GDMAC_GDT0_CRD_RESERVED2_SHIFT           15 
#define GDMAC_GDT0_CRD_RESERVED2_BIT             0x1
#define GDMAC_GDT0_CRD_RESERVED2_BITWIDTH        1
// rd_q_dep bitfiled (RO) Reset=111
#define GDMAC_GDT0_CRD_RD_Q_DEP_MASK             0xF0000
#define GDMAC_GDT0_CRD_RD_Q_DEP_SHIFT            16 
#define GDMAC_GDT0_CRD_RD_Q_DEP_BIT              0xF
#define GDMAC_GDT0_CRD_RD_Q_DEP_BITWIDTH         4
// data_buffer_dep bitfiled (RO) Reset=11111
#define GDMAC_GDT0_CRD_DATA_BUFFER_DEP_MASK      0x3FF00000
#define GDMAC_GDT0_CRD_DATA_BUFFER_DEP_SHIFT     20 
#define GDMAC_GDT0_CRD_DATA_BUFFER_DEP_BIT       0x3FF
#define GDMAC_GDT0_CRD_DATA_BUFFER_DEP_BITWIDTH  10
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_CRD_RESERVED_MASK             0xC0000000
#define GDMAC_GDT0_CRD_RESERVED_SHIFT            30 
#define GDMAC_GDT0_CRD_RESERVED_BIT              0x3
#define GDMAC_GDT0_CRD_RESERVED_BITWIDTH         2
// GDT0_WD Register
#define GDMAC_GDT0_WD_OFS                        0x00000E80
// wd_irq_only bitfiled (RW) Reset=0
#define GDMAC_GDT0_WD_WD_IRQ_ONLY_MASK           0x1
#define GDMAC_GDT0_WD_WD_IRQ_ONLY_SHIFT          0 
#define GDMAC_GDT0_WD_WD_IRQ_ONLY_BIT            0x1
#define GDMAC_GDT0_WD_WD_IRQ_ONLY_BITWIDTH       1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_WD_RESERVED_MASK              0xFFFFFFFE
#define GDMAC_GDT0_WD_RESERVED_SHIFT             1 
#define GDMAC_GDT0_WD_RESERVED_BIT               0x7FFFFFFF
#define GDMAC_GDT0_WD_RESERVED_BITWIDTH          31
// GDT0_periph_id_0 Register
#define GDMAC_GDT0_PERIPH_ID_0_OFS               0x00000FE0
// part_number_0 bitfiled (RO) Reset=110000
#define GDMAC_GDT0_PERIPH_ID_0_PART_NUMBER_0_MASK 0xFF
#define GDMAC_GDT0_PERIPH_ID_0_PART_NUMBER_0_SHIFT 0 
#define GDMAC_GDT0_PERIPH_ID_0_PART_NUMBER_0_BIT 0xFF
#define GDMAC_GDT0_PERIPH_ID_0_PART_NUMBER_0_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_PERIPH_ID_0_RESERVED_MASK     0xFFFFFF00
#define GDMAC_GDT0_PERIPH_ID_0_RESERVED_SHIFT    8 
#define GDMAC_GDT0_PERIPH_ID_0_RESERVED_BIT      0xFFFFFF
#define GDMAC_GDT0_PERIPH_ID_0_RESERVED_BITWIDTH 24
// GDT0_periph_id_1 Register
#define GDMAC_GDT0_PERIPH_ID_1_OFS               0x00000FE4
// part_number_1 bitfiled (RO) Reset=11
#define GDMAC_GDT0_PERIPH_ID_1_PART_NUMBER_1_MASK 0xF
#define GDMAC_GDT0_PERIPH_ID_1_PART_NUMBER_1_SHIFT 0 
#define GDMAC_GDT0_PERIPH_ID_1_PART_NUMBER_1_BIT 0xF
#define GDMAC_GDT0_PERIPH_ID_1_PART_NUMBER_1_BITWIDTH 4
// designer_0 bitfiled (RO) Reset=1
#define GDMAC_GDT0_PERIPH_ID_1_DESIGNER_0_MASK   0xF0
#define GDMAC_GDT0_PERIPH_ID_1_DESIGNER_0_SHIFT  4 
#define GDMAC_GDT0_PERIPH_ID_1_DESIGNER_0_BIT    0xF
#define GDMAC_GDT0_PERIPH_ID_1_DESIGNER_0_BITWIDTH 4
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_PERIPH_ID_1_RESERVED_MASK     0xFFFFFF00
#define GDMAC_GDT0_PERIPH_ID_1_RESERVED_SHIFT    8 
#define GDMAC_GDT0_PERIPH_ID_1_RESERVED_BIT      0xFFFFFF
#define GDMAC_GDT0_PERIPH_ID_1_RESERVED_BITWIDTH 24
// GDT0_periph_id_2 Register
#define GDMAC_GDT0_PERIPH_ID_2_OFS               0x00000FE8
// designer_1 bitfiled (RO) Reset=100
#define GDMAC_GDT0_PERIPH_ID_2_DESIGNER_1_MASK   0xF
#define GDMAC_GDT0_PERIPH_ID_2_DESIGNER_1_SHIFT  0 
#define GDMAC_GDT0_PERIPH_ID_2_DESIGNER_1_BIT    0xF
#define GDMAC_GDT0_PERIPH_ID_2_DESIGNER_1_BITWIDTH 4
// revision bitfiled (RO) Reset=10
#define GDMAC_GDT0_PERIPH_ID_2_REVISION_MASK     0xF0
#define GDMAC_GDT0_PERIPH_ID_2_REVISION_SHIFT    4 
#define GDMAC_GDT0_PERIPH_ID_2_REVISION_BIT      0xF
#define GDMAC_GDT0_PERIPH_ID_2_REVISION_BITWIDTH 4
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_PERIPH_ID_2_RESERVED_MASK     0xFFFFFF00
#define GDMAC_GDT0_PERIPH_ID_2_RESERVED_SHIFT    8 
#define GDMAC_GDT0_PERIPH_ID_2_RESERVED_BIT      0xFFFFFF
#define GDMAC_GDT0_PERIPH_ID_2_RESERVED_BITWIDTH 24
// GDT0_periph_id_3 Register
#define GDMAC_GDT0_PERIPH_ID_3_OFS               0x00000FEC
// revision bitfiled (RO) Reset=0
#define GDMAC_GDT0_PERIPH_ID_3_REVISION_MASK     0x1
#define GDMAC_GDT0_PERIPH_ID_3_REVISION_SHIFT    0 
#define GDMAC_GDT0_PERIPH_ID_3_REVISION_BIT      0x1
#define GDMAC_GDT0_PERIPH_ID_3_REVISION_BITWIDTH 1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_PERIPH_ID_3_RESERVED_MASK     0xFFFFFFFE
#define GDMAC_GDT0_PERIPH_ID_3_RESERVED_SHIFT    1 
#define GDMAC_GDT0_PERIPH_ID_3_RESERVED_BIT      0x7FFFFFFF
#define GDMAC_GDT0_PERIPH_ID_3_RESERVED_BITWIDTH 31
// GDT0_pcell_id_0 Register
#define GDMAC_GDT0_PCELL_ID_0_OFS                0x00000FF0
// pcell_id_0 bitfiled (RO) Reset=1101
#define GDMAC_GDT0_PCELL_ID_0_PCELL_ID_0_MASK    0xFF
#define GDMAC_GDT0_PCELL_ID_0_PCELL_ID_0_SHIFT   0 
#define GDMAC_GDT0_PCELL_ID_0_PCELL_ID_0_BIT     0xFF
#define GDMAC_GDT0_PCELL_ID_0_PCELL_ID_0_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_PCELL_ID_0_RESERVED_MASK      0xFFFFFF00
#define GDMAC_GDT0_PCELL_ID_0_RESERVED_SHIFT     8 
#define GDMAC_GDT0_PCELL_ID_0_RESERVED_BIT       0xFFFFFF
#define GDMAC_GDT0_PCELL_ID_0_RESERVED_BITWIDTH  24
// GDT0_pcell_id_1 Register
#define GDMAC_GDT0_PCELL_ID_1_OFS                0x00000FF4
// pcell_id_1 bitfiled (RO) Reset=11110000
#define GDMAC_GDT0_PCELL_ID_1_PCELL_ID_1_MASK    0xFF
#define GDMAC_GDT0_PCELL_ID_1_PCELL_ID_1_SHIFT   0 
#define GDMAC_GDT0_PCELL_ID_1_PCELL_ID_1_BIT     0xFF
#define GDMAC_GDT0_PCELL_ID_1_PCELL_ID_1_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_PCELL_ID_1_RESERVED_MASK      0xFFFFFF00
#define GDMAC_GDT0_PCELL_ID_1_RESERVED_SHIFT     8 
#define GDMAC_GDT0_PCELL_ID_1_RESERVED_BIT       0xFFFFFF
#define GDMAC_GDT0_PCELL_ID_1_RESERVED_BITWIDTH  24
// GDT0_pcell_id_2 Register
#define GDMAC_GDT0_PCELL_ID_2_OFS                0x00000FF8
// pcell_id_2 bitfiled (RO) Reset=101
#define GDMAC_GDT0_PCELL_ID_2_PCELL_ID_2_MASK    0xFF
#define GDMAC_GDT0_PCELL_ID_2_PCELL_ID_2_SHIFT   0 
#define GDMAC_GDT0_PCELL_ID_2_PCELL_ID_2_BIT     0xFF
#define GDMAC_GDT0_PCELL_ID_2_PCELL_ID_2_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_PCELL_ID_2_RESERVED_MASK      0xFFFFFF00
#define GDMAC_GDT0_PCELL_ID_2_RESERVED_SHIFT     8 
#define GDMAC_GDT0_PCELL_ID_2_RESERVED_BIT       0xFFFFFF
#define GDMAC_GDT0_PCELL_ID_2_RESERVED_BITWIDTH  24
// GDT0_pcell_id_3 Register
#define GDMAC_GDT0_PCELL_ID_3_OFS                0x00000FFC
// pcell_id_3 bitfiled (RO) Reset=11000001
#define GDMAC_GDT0_PCELL_ID_3_PCELL_ID_3_MASK    0xFF
#define GDMAC_GDT0_PCELL_ID_3_PCELL_ID_3_SHIFT   0 
#define GDMAC_GDT0_PCELL_ID_3_PCELL_ID_3_BIT     0xFF
#define GDMAC_GDT0_PCELL_ID_3_PCELL_ID_3_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT0_PCELL_ID_3_RESERVED_MASK      0xFFFFFF00
#define GDMAC_GDT0_PCELL_ID_3_RESERVED_SHIFT     8 
#define GDMAC_GDT0_PCELL_ID_3_RESERVED_BIT       0xFFFFFF
#define GDMAC_GDT0_PCELL_ID_3_RESERVED_BITWIDTH  24
// GDT1_DSR Register
#define GDMAC_GDT1_DSR_OFS                       0x00001000
// DMA_status bitfiled (RO) Reset=0
#define GDMAC_GDT1_DSR_DMA_STATUS_MASK           0xF
#define GDMAC_GDT1_DSR_DMA_STATUS_SHIFT          0 
#define GDMAC_GDT1_DSR_DMA_STATUS_BIT            0xF
#define GDMAC_GDT1_DSR_DMA_STATUS_BITWIDTH       4
// Wakeup_event bitfiled (RO) Reset=0
#define GDMAC_GDT1_DSR_WAKEUP_EVENT_MASK         0x1F0
#define GDMAC_GDT1_DSR_WAKEUP_EVENT_SHIFT        4 
#define GDMAC_GDT1_DSR_WAKEUP_EVENT_BIT          0x1F
#define GDMAC_GDT1_DSR_WAKEUP_EVENT_BITWIDTH     5
// DSN bitfiled (RO) Reset=1
#define GDMAC_GDT1_DSR_DSN_MASK                  0x200
#define GDMAC_GDT1_DSR_DSN_SHIFT                 9 
#define GDMAC_GDT1_DSR_DSN_BIT                   0x1
#define GDMAC_GDT1_DSR_DSN_BITWIDTH              1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_DSR_RESERVED_MASK             0xFFFFFC00
#define GDMAC_GDT1_DSR_RESERVED_SHIFT            10 
#define GDMAC_GDT1_DSR_RESERVED_BIT              0x3FFFFF
#define GDMAC_GDT1_DSR_RESERVED_BITWIDTH         22
// GDT1_DPC Register
#define GDMAC_GDT1_DPC_OFS                       0x00001004
// pc_mgr bitfiled (RO) Reset=0
#define GDMAC_GDT1_DPC_PC_MGR_MASK               0xFFFFFFFF
#define GDMAC_GDT1_DPC_PC_MGR_SHIFT              0 
#define GDMAC_GDT1_DPC_PC_MGR_BIT                0xFFFFFFFF
#define GDMAC_GDT1_DPC_PC_MGR_BITWIDTH           32
// GDT1_INTEN Register
#define GDMAC_GDT1_INTEN_OFS                     0x00001020
// event_irq_select bitfiled (RW) Reset=0
#define GDMAC_GDT1_INTEN_EVENT_IRQ_SELECT_MASK   0xFFFFFFFF
#define GDMAC_GDT1_INTEN_EVENT_IRQ_SELECT_SHIFT  0 
#define GDMAC_GDT1_INTEN_EVENT_IRQ_SELECT_BIT    0xFFFFFFFF
#define GDMAC_GDT1_INTEN_EVENT_IRQ_SELECT_BITWIDTH 32
// GDT1_INT_EVENT_RIS Register
#define GDMAC_GDT1_INT_EVENT_RIS_OFS             0x00001024
// DMASEV bitfiled (RO) Reset=0
#define GDMAC_GDT1_INT_EVENT_RIS_DMASEV_MASK     0xFFFFFFFF
#define GDMAC_GDT1_INT_EVENT_RIS_DMASEV_SHIFT    0 
#define GDMAC_GDT1_INT_EVENT_RIS_DMASEV_BIT      0xFFFFFFFF
#define GDMAC_GDT1_INT_EVENT_RIS_DMASEV_BITWIDTH 32
// GDT1_INTMIS Register
#define GDMAC_GDT1_INTMIS_OFS                    0x00001028
// irq_status bitfiled (RO) Reset=0
#define GDMAC_GDT1_INTMIS_IRQ_STATUS_MASK        0xFFFFFFFF
#define GDMAC_GDT1_INTMIS_IRQ_STATUS_SHIFT       0 
#define GDMAC_GDT1_INTMIS_IRQ_STATUS_BIT         0xFFFFFFFF
#define GDMAC_GDT1_INTMIS_IRQ_STATUS_BITWIDTH    32
// GDT1_INTCLR Register
#define GDMAC_GDT1_INTCLR_OFS                    0x0000102C
// irq_clr bitfiled (RW) Reset=0
#define GDMAC_GDT1_INTCLR_IRQ_CLR_MASK           0xFFFFFFFF
#define GDMAC_GDT1_INTCLR_IRQ_CLR_SHIFT          0 
#define GDMAC_GDT1_INTCLR_IRQ_CLR_BIT            0xFFFFFFFF
#define GDMAC_GDT1_INTCLR_IRQ_CLR_BITWIDTH       32
// GDT1_FSRD Register
#define GDMAC_GDT1_FSRD_OFS                      0x00001030
// fs_mgr bitfiled (RO) Reset=0
#define GDMAC_GDT1_FSRD_FS_MGR_MASK              0x1
#define GDMAC_GDT1_FSRD_FS_MGR_SHIFT             0 
#define GDMAC_GDT1_FSRD_FS_MGR_BIT               0x1
#define GDMAC_GDT1_FSRD_FS_MGR_BITWIDTH          1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_FSRD_RESERVED_MASK            0xFFFFFFFE
#define GDMAC_GDT1_FSRD_RESERVED_SHIFT           1 
#define GDMAC_GDT1_FSRD_RESERVED_BIT             0x7FFFFFFF
#define GDMAC_GDT1_FSRD_RESERVED_BITWIDTH        31
// GDT1_FSRC Register
#define GDMAC_GDT1_FSRC_OFS                      0x00001034
// fault_status bitfiled (RO) Reset=0
#define GDMAC_GDT1_FSRC_FAULT_STATUS_MASK        0xFF
#define GDMAC_GDT1_FSRC_FAULT_STATUS_SHIFT       0 
#define GDMAC_GDT1_FSRC_FAULT_STATUS_BIT         0xFF
#define GDMAC_GDT1_FSRC_FAULT_STATUS_BITWIDTH    8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_FSRC_RESERVED_MASK            0xFFFFFF00
#define GDMAC_GDT1_FSRC_RESERVED_SHIFT           8 
#define GDMAC_GDT1_FSRC_RESERVED_BIT             0xFFFFFF
#define GDMAC_GDT1_FSRC_RESERVED_BITWIDTH        24
// GDT1_FTRD Register
#define GDMAC_GDT1_FTRD_OFS                      0x00001038
// undef_instr bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTRD_UNDEF_INSTR_MASK         0x1
#define GDMAC_GDT1_FTRD_UNDEF_INSTR_SHIFT        0 
#define GDMAC_GDT1_FTRD_UNDEF_INSTR_BIT          0x1
#define GDMAC_GDT1_FTRD_UNDEF_INSTR_BITWIDTH     1
// operand_invalid bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTRD_OPERAND_INVALID_MASK     0x2
#define GDMAC_GDT1_FTRD_OPERAND_INVALID_SHIFT    1 
#define GDMAC_GDT1_FTRD_OPERAND_INVALID_BIT      0x1
#define GDMAC_GDT1_FTRD_OPERAND_INVALID_BITWIDTH 1
// reserved4 bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTRD_RESERVED4_MASK           0xC
#define GDMAC_GDT1_FTRD_RESERVED4_SHIFT          2 
#define GDMAC_GDT1_FTRD_RESERVED4_BIT            0x3
#define GDMAC_GDT1_FTRD_RESERVED4_BITWIDTH       2
// dmago_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTRD_DMAGO_ERR_MASK           0x10
#define GDMAC_GDT1_FTRD_DMAGO_ERR_SHIFT          4 
#define GDMAC_GDT1_FTRD_DMAGO_ERR_BIT            0x1
#define GDMAC_GDT1_FTRD_DMAGO_ERR_BITWIDTH       1
// mgr_evnt_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTRD_MGR_EVNT_ERR_MASK        0x20
#define GDMAC_GDT1_FTRD_MGR_EVNT_ERR_SHIFT       5 
#define GDMAC_GDT1_FTRD_MGR_EVNT_ERR_BIT         0x1
#define GDMAC_GDT1_FTRD_MGR_EVNT_ERR_BITWIDTH    1
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTRD_RESERVED3_MASK           0xFFC0
#define GDMAC_GDT1_FTRD_RESERVED3_SHIFT          6 
#define GDMAC_GDT1_FTRD_RESERVED3_BIT            0x3FF
#define GDMAC_GDT1_FTRD_RESERVED3_BITWIDTH       10
// instr_fetch_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTRD_INSTR_FETCH_ERR_MASK     0x10000
#define GDMAC_GDT1_FTRD_INSTR_FETCH_ERR_SHIFT    16 
#define GDMAC_GDT1_FTRD_INSTR_FETCH_ERR_BIT      0x1
#define GDMAC_GDT1_FTRD_INSTR_FETCH_ERR_BITWIDTH 1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTRD_RESERVED2_MASK           0x3FFE0000
#define GDMAC_GDT1_FTRD_RESERVED2_SHIFT          17 
#define GDMAC_GDT1_FTRD_RESERVED2_BIT            0x1FFF
#define GDMAC_GDT1_FTRD_RESERVED2_BITWIDTH       13
// dbg_instr bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTRD_DBG_INSTR_MASK           0x40000000
#define GDMAC_GDT1_FTRD_DBG_INSTR_SHIFT          30 
#define GDMAC_GDT1_FTRD_DBG_INSTR_BIT            0x1
#define GDMAC_GDT1_FTRD_DBG_INSTR_BITWIDTH       1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTRD_RESERVED_MASK            0x80000000
#define GDMAC_GDT1_FTRD_RESERVED_SHIFT           31 
#define GDMAC_GDT1_FTRD_RESERVED_BIT             0x1
#define GDMAC_GDT1_FTRD_RESERVED_BITWIDTH        1
// GDT1_FTR0 Register
#define GDMAC_GDT1_FTR0_OFS                      0x00001040
// undef_instr bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR0_UNDEF_INSTR_MASK         0x1
#define GDMAC_GDT1_FTR0_UNDEF_INSTR_SHIFT        0 
#define GDMAC_GDT1_FTR0_UNDEF_INSTR_BIT          0x1
#define GDMAC_GDT1_FTR0_UNDEF_INSTR_BITWIDTH     1
// operand_invalid bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR0_OPERAND_INVALID_MASK     0x2
#define GDMAC_GDT1_FTR0_OPERAND_INVALID_SHIFT    1 
#define GDMAC_GDT1_FTR0_OPERAND_INVALID_BIT      0x1
#define GDMAC_GDT1_FTR0_OPERAND_INVALID_BITWIDTH 1
// reserved4 bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR0_RESERVED4_MASK           0x1C
#define GDMAC_GDT1_FTR0_RESERVED4_SHIFT          2 
#define GDMAC_GDT1_FTR0_RESERVED4_BIT            0x7
#define GDMAC_GDT1_FTR0_RESERVED4_BITWIDTH       3
// ch_evnt_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR0_CH_EVNT_ERR_MASK         0x20
#define GDMAC_GDT1_FTR0_CH_EVNT_ERR_SHIFT        5 
#define GDMAC_GDT1_FTR0_CH_EVNT_ERR_BIT          0x1
#define GDMAC_GDT1_FTR0_CH_EVNT_ERR_BITWIDTH     1
// ch_periph_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR0_CH_PERIPH_ERR_MASK       0x40
#define GDMAC_GDT1_FTR0_CH_PERIPH_ERR_SHIFT      6 
#define GDMAC_GDT1_FTR0_CH_PERIPH_ERR_BIT        0x1
#define GDMAC_GDT1_FTR0_CH_PERIPH_ERR_BITWIDTH   1
// ch_rdwr_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR0_CH_RDWR_ERR_MASK         0x80
#define GDMAC_GDT1_FTR0_CH_RDWR_ERR_SHIFT        7 
#define GDMAC_GDT1_FTR0_CH_RDWR_ERR_BIT          0x1
#define GDMAC_GDT1_FTR0_CH_RDWR_ERR_BITWIDTH     1
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR0_RESERVED3_MASK           0xF00
#define GDMAC_GDT1_FTR0_RESERVED3_SHIFT          8 
#define GDMAC_GDT1_FTR0_RESERVED3_BIT            0xF
#define GDMAC_GDT1_FTR0_RESERVED3_BITWIDTH       4
// mfifo_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR0_MFIFO_ERR_MASK           0x1000
#define GDMAC_GDT1_FTR0_MFIFO_ERR_SHIFT          12 
#define GDMAC_GDT1_FTR0_MFIFO_ERR_BIT            0x1
#define GDMAC_GDT1_FTR0_MFIFO_ERR_BITWIDTH       1
// st_data_unavailable bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR0_ST_DATA_UNAVAILABLE_MASK 0x2000
#define GDMAC_GDT1_FTR0_ST_DATA_UNAVAILABLE_SHIFT 13 
#define GDMAC_GDT1_FTR0_ST_DATA_UNAVAILABLE_BIT  0x1
#define GDMAC_GDT1_FTR0_ST_DATA_UNAVAILABLE_BITWIDTH 1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR0_RESERVED2_MASK           0xC000
#define GDMAC_GDT1_FTR0_RESERVED2_SHIFT          14 
#define GDMAC_GDT1_FTR0_RESERVED2_BIT            0x3
#define GDMAC_GDT1_FTR0_RESERVED2_BITWIDTH       2
// instr_fetch_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR0_INSTR_FETCH_ERR_MASK     0x10000
#define GDMAC_GDT1_FTR0_INSTR_FETCH_ERR_SHIFT    16 
#define GDMAC_GDT1_FTR0_INSTR_FETCH_ERR_BIT      0x1
#define GDMAC_GDT1_FTR0_INSTR_FETCH_ERR_BITWIDTH 1
// data_write_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR0_DATA_WRITE_ERR_MASK      0x20000
#define GDMAC_GDT1_FTR0_DATA_WRITE_ERR_SHIFT     17 
#define GDMAC_GDT1_FTR0_DATA_WRITE_ERR_BIT       0x1
#define GDMAC_GDT1_FTR0_DATA_WRITE_ERR_BITWIDTH  1
// data_read_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR0_DATA_READ_ERR_MASK       0x40000
#define GDMAC_GDT1_FTR0_DATA_READ_ERR_SHIFT      18 
#define GDMAC_GDT1_FTR0_DATA_READ_ERR_BIT        0x1
#define GDMAC_GDT1_FTR0_DATA_READ_ERR_BITWIDTH   1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR0_RESERVED_MASK            0x3FF80000
#define GDMAC_GDT1_FTR0_RESERVED_SHIFT           19 
#define GDMAC_GDT1_FTR0_RESERVED_BIT             0x7FF
#define GDMAC_GDT1_FTR0_RESERVED_BITWIDTH        11
// dbg_instr bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR0_DBG_INSTR_MASK           0x40000000
#define GDMAC_GDT1_FTR0_DBG_INSTR_SHIFT          30 
#define GDMAC_GDT1_FTR0_DBG_INSTR_BIT            0x1
#define GDMAC_GDT1_FTR0_DBG_INSTR_BITWIDTH       1
// lockup_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR0_LOCKUP_ERR_MASK          0x80000000
#define GDMAC_GDT1_FTR0_LOCKUP_ERR_SHIFT         31 
#define GDMAC_GDT1_FTR0_LOCKUP_ERR_BIT           0x1
#define GDMAC_GDT1_FTR0_LOCKUP_ERR_BITWIDTH      1
// GDT1_FTR1 Register
#define GDMAC_GDT1_FTR1_OFS                      0x00001044
// undef_instr bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR1_UNDEF_INSTR_MASK         0x1
#define GDMAC_GDT1_FTR1_UNDEF_INSTR_SHIFT        0 
#define GDMAC_GDT1_FTR1_UNDEF_INSTR_BIT          0x1
#define GDMAC_GDT1_FTR1_UNDEF_INSTR_BITWIDTH     1
// operand_invalid bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR1_OPERAND_INVALID_MASK     0x2
#define GDMAC_GDT1_FTR1_OPERAND_INVALID_SHIFT    1 
#define GDMAC_GDT1_FTR1_OPERAND_INVALID_BIT      0x1
#define GDMAC_GDT1_FTR1_OPERAND_INVALID_BITWIDTH 1
// reserved4 bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR1_RESERVED4_MASK           0x1C
#define GDMAC_GDT1_FTR1_RESERVED4_SHIFT          2 
#define GDMAC_GDT1_FTR1_RESERVED4_BIT            0x7
#define GDMAC_GDT1_FTR1_RESERVED4_BITWIDTH       3
// ch_evnt_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR1_CH_EVNT_ERR_MASK         0x20
#define GDMAC_GDT1_FTR1_CH_EVNT_ERR_SHIFT        5 
#define GDMAC_GDT1_FTR1_CH_EVNT_ERR_BIT          0x1
#define GDMAC_GDT1_FTR1_CH_EVNT_ERR_BITWIDTH     1
// ch_periph_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR1_CH_PERIPH_ERR_MASK       0x40
#define GDMAC_GDT1_FTR1_CH_PERIPH_ERR_SHIFT      6 
#define GDMAC_GDT1_FTR1_CH_PERIPH_ERR_BIT        0x1
#define GDMAC_GDT1_FTR1_CH_PERIPH_ERR_BITWIDTH   1
// ch_rdwr_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR1_CH_RDWR_ERR_MASK         0x80
#define GDMAC_GDT1_FTR1_CH_RDWR_ERR_SHIFT        7 
#define GDMAC_GDT1_FTR1_CH_RDWR_ERR_BIT          0x1
#define GDMAC_GDT1_FTR1_CH_RDWR_ERR_BITWIDTH     1
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR1_RESERVED3_MASK           0xF00
#define GDMAC_GDT1_FTR1_RESERVED3_SHIFT          8 
#define GDMAC_GDT1_FTR1_RESERVED3_BIT            0xF
#define GDMAC_GDT1_FTR1_RESERVED3_BITWIDTH       4
// mfifo_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR1_MFIFO_ERR_MASK           0x1000
#define GDMAC_GDT1_FTR1_MFIFO_ERR_SHIFT          12 
#define GDMAC_GDT1_FTR1_MFIFO_ERR_BIT            0x1
#define GDMAC_GDT1_FTR1_MFIFO_ERR_BITWIDTH       1
// st_data_unavailable bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR1_ST_DATA_UNAVAILABLE_MASK 0x2000
#define GDMAC_GDT1_FTR1_ST_DATA_UNAVAILABLE_SHIFT 13 
#define GDMAC_GDT1_FTR1_ST_DATA_UNAVAILABLE_BIT  0x1
#define GDMAC_GDT1_FTR1_ST_DATA_UNAVAILABLE_BITWIDTH 1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR1_RESERVED2_MASK           0xC000
#define GDMAC_GDT1_FTR1_RESERVED2_SHIFT          14 
#define GDMAC_GDT1_FTR1_RESERVED2_BIT            0x3
#define GDMAC_GDT1_FTR1_RESERVED2_BITWIDTH       2
// instr_fetch_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR1_INSTR_FETCH_ERR_MASK     0x10000
#define GDMAC_GDT1_FTR1_INSTR_FETCH_ERR_SHIFT    16 
#define GDMAC_GDT1_FTR1_INSTR_FETCH_ERR_BIT      0x1
#define GDMAC_GDT1_FTR1_INSTR_FETCH_ERR_BITWIDTH 1
// data_write_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR1_DATA_WRITE_ERR_MASK      0x20000
#define GDMAC_GDT1_FTR1_DATA_WRITE_ERR_SHIFT     17 
#define GDMAC_GDT1_FTR1_DATA_WRITE_ERR_BIT       0x1
#define GDMAC_GDT1_FTR1_DATA_WRITE_ERR_BITWIDTH  1
// data_read_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR1_DATA_READ_ERR_MASK       0x40000
#define GDMAC_GDT1_FTR1_DATA_READ_ERR_SHIFT      18 
#define GDMAC_GDT1_FTR1_DATA_READ_ERR_BIT        0x1
#define GDMAC_GDT1_FTR1_DATA_READ_ERR_BITWIDTH   1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR1_RESERVED_MASK            0x3FF80000
#define GDMAC_GDT1_FTR1_RESERVED_SHIFT           19 
#define GDMAC_GDT1_FTR1_RESERVED_BIT             0x7FF
#define GDMAC_GDT1_FTR1_RESERVED_BITWIDTH        11
// dbg_instr bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR1_DBG_INSTR_MASK           0x40000000
#define GDMAC_GDT1_FTR1_DBG_INSTR_SHIFT          30 
#define GDMAC_GDT1_FTR1_DBG_INSTR_BIT            0x1
#define GDMAC_GDT1_FTR1_DBG_INSTR_BITWIDTH       1
// lockup_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR1_LOCKUP_ERR_MASK          0x80000000
#define GDMAC_GDT1_FTR1_LOCKUP_ERR_SHIFT         31 
#define GDMAC_GDT1_FTR1_LOCKUP_ERR_BIT           0x1
#define GDMAC_GDT1_FTR1_LOCKUP_ERR_BITWIDTH      1
// GDT1_FTR2 Register
#define GDMAC_GDT1_FTR2_OFS                      0x00001048
// undef_instr bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR2_UNDEF_INSTR_MASK         0x1
#define GDMAC_GDT1_FTR2_UNDEF_INSTR_SHIFT        0 
#define GDMAC_GDT1_FTR2_UNDEF_INSTR_BIT          0x1
#define GDMAC_GDT1_FTR2_UNDEF_INSTR_BITWIDTH     1
// operand_invalid bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR2_OPERAND_INVALID_MASK     0x2
#define GDMAC_GDT1_FTR2_OPERAND_INVALID_SHIFT    1 
#define GDMAC_GDT1_FTR2_OPERAND_INVALID_BIT      0x1
#define GDMAC_GDT1_FTR2_OPERAND_INVALID_BITWIDTH 1
// reserved4 bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR2_RESERVED4_MASK           0x1C
#define GDMAC_GDT1_FTR2_RESERVED4_SHIFT          2 
#define GDMAC_GDT1_FTR2_RESERVED4_BIT            0x7
#define GDMAC_GDT1_FTR2_RESERVED4_BITWIDTH       3
// ch_evnt_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR2_CH_EVNT_ERR_MASK         0x20
#define GDMAC_GDT1_FTR2_CH_EVNT_ERR_SHIFT        5 
#define GDMAC_GDT1_FTR2_CH_EVNT_ERR_BIT          0x1
#define GDMAC_GDT1_FTR2_CH_EVNT_ERR_BITWIDTH     1
// ch_periph_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR2_CH_PERIPH_ERR_MASK       0x40
#define GDMAC_GDT1_FTR2_CH_PERIPH_ERR_SHIFT      6 
#define GDMAC_GDT1_FTR2_CH_PERIPH_ERR_BIT        0x1
#define GDMAC_GDT1_FTR2_CH_PERIPH_ERR_BITWIDTH   1
// ch_rdwr_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR2_CH_RDWR_ERR_MASK         0x80
#define GDMAC_GDT1_FTR2_CH_RDWR_ERR_SHIFT        7 
#define GDMAC_GDT1_FTR2_CH_RDWR_ERR_BIT          0x1
#define GDMAC_GDT1_FTR2_CH_RDWR_ERR_BITWIDTH     1
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR2_RESERVED3_MASK           0xF00
#define GDMAC_GDT1_FTR2_RESERVED3_SHIFT          8 
#define GDMAC_GDT1_FTR2_RESERVED3_BIT            0xF
#define GDMAC_GDT1_FTR2_RESERVED3_BITWIDTH       4
// mfifo_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR2_MFIFO_ERR_MASK           0x1000
#define GDMAC_GDT1_FTR2_MFIFO_ERR_SHIFT          12 
#define GDMAC_GDT1_FTR2_MFIFO_ERR_BIT            0x1
#define GDMAC_GDT1_FTR2_MFIFO_ERR_BITWIDTH       1
// st_data_unavailable bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR2_ST_DATA_UNAVAILABLE_MASK 0x2000
#define GDMAC_GDT1_FTR2_ST_DATA_UNAVAILABLE_SHIFT 13 
#define GDMAC_GDT1_FTR2_ST_DATA_UNAVAILABLE_BIT  0x1
#define GDMAC_GDT1_FTR2_ST_DATA_UNAVAILABLE_BITWIDTH 1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR2_RESERVED2_MASK           0xC000
#define GDMAC_GDT1_FTR2_RESERVED2_SHIFT          14 
#define GDMAC_GDT1_FTR2_RESERVED2_BIT            0x3
#define GDMAC_GDT1_FTR2_RESERVED2_BITWIDTH       2
// instr_fetch_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR2_INSTR_FETCH_ERR_MASK     0x10000
#define GDMAC_GDT1_FTR2_INSTR_FETCH_ERR_SHIFT    16 
#define GDMAC_GDT1_FTR2_INSTR_FETCH_ERR_BIT      0x1
#define GDMAC_GDT1_FTR2_INSTR_FETCH_ERR_BITWIDTH 1
// data_write_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR2_DATA_WRITE_ERR_MASK      0x20000
#define GDMAC_GDT1_FTR2_DATA_WRITE_ERR_SHIFT     17 
#define GDMAC_GDT1_FTR2_DATA_WRITE_ERR_BIT       0x1
#define GDMAC_GDT1_FTR2_DATA_WRITE_ERR_BITWIDTH  1
// data_read_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR2_DATA_READ_ERR_MASK       0x40000
#define GDMAC_GDT1_FTR2_DATA_READ_ERR_SHIFT      18 
#define GDMAC_GDT1_FTR2_DATA_READ_ERR_BIT        0x1
#define GDMAC_GDT1_FTR2_DATA_READ_ERR_BITWIDTH   1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR2_RESERVED_MASK            0x3FF80000
#define GDMAC_GDT1_FTR2_RESERVED_SHIFT           19 
#define GDMAC_GDT1_FTR2_RESERVED_BIT             0x7FF
#define GDMAC_GDT1_FTR2_RESERVED_BITWIDTH        11
// dbg_instr bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR2_DBG_INSTR_MASK           0x40000000
#define GDMAC_GDT1_FTR2_DBG_INSTR_SHIFT          30 
#define GDMAC_GDT1_FTR2_DBG_INSTR_BIT            0x1
#define GDMAC_GDT1_FTR2_DBG_INSTR_BITWIDTH       1
// lockup_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR2_LOCKUP_ERR_MASK          0x80000000
#define GDMAC_GDT1_FTR2_LOCKUP_ERR_SHIFT         31 
#define GDMAC_GDT1_FTR2_LOCKUP_ERR_BIT           0x1
#define GDMAC_GDT1_FTR2_LOCKUP_ERR_BITWIDTH      1
// GDT1_FTR3 Register
#define GDMAC_GDT1_FTR3_OFS                      0x0000104C
// undef_instr bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR3_UNDEF_INSTR_MASK         0x1
#define GDMAC_GDT1_FTR3_UNDEF_INSTR_SHIFT        0 
#define GDMAC_GDT1_FTR3_UNDEF_INSTR_BIT          0x1
#define GDMAC_GDT1_FTR3_UNDEF_INSTR_BITWIDTH     1
// operand_invalid bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR3_OPERAND_INVALID_MASK     0x2
#define GDMAC_GDT1_FTR3_OPERAND_INVALID_SHIFT    1 
#define GDMAC_GDT1_FTR3_OPERAND_INVALID_BIT      0x1
#define GDMAC_GDT1_FTR3_OPERAND_INVALID_BITWIDTH 1
// reserved4 bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR3_RESERVED4_MASK           0x1C
#define GDMAC_GDT1_FTR3_RESERVED4_SHIFT          2 
#define GDMAC_GDT1_FTR3_RESERVED4_BIT            0x7
#define GDMAC_GDT1_FTR3_RESERVED4_BITWIDTH       3
// ch_evnt_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR3_CH_EVNT_ERR_MASK         0x20
#define GDMAC_GDT1_FTR3_CH_EVNT_ERR_SHIFT        5 
#define GDMAC_GDT1_FTR3_CH_EVNT_ERR_BIT          0x1
#define GDMAC_GDT1_FTR3_CH_EVNT_ERR_BITWIDTH     1
// ch_periph_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR3_CH_PERIPH_ERR_MASK       0x40
#define GDMAC_GDT1_FTR3_CH_PERIPH_ERR_SHIFT      6 
#define GDMAC_GDT1_FTR3_CH_PERIPH_ERR_BIT        0x1
#define GDMAC_GDT1_FTR3_CH_PERIPH_ERR_BITWIDTH   1
// ch_rdwr_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR3_CH_RDWR_ERR_MASK         0x80
#define GDMAC_GDT1_FTR3_CH_RDWR_ERR_SHIFT        7 
#define GDMAC_GDT1_FTR3_CH_RDWR_ERR_BIT          0x1
#define GDMAC_GDT1_FTR3_CH_RDWR_ERR_BITWIDTH     1
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR3_RESERVED3_MASK           0xF00
#define GDMAC_GDT1_FTR3_RESERVED3_SHIFT          8 
#define GDMAC_GDT1_FTR3_RESERVED3_BIT            0xF
#define GDMAC_GDT1_FTR3_RESERVED3_BITWIDTH       4
// mfifo_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR3_MFIFO_ERR_MASK           0x1000
#define GDMAC_GDT1_FTR3_MFIFO_ERR_SHIFT          12 
#define GDMAC_GDT1_FTR3_MFIFO_ERR_BIT            0x1
#define GDMAC_GDT1_FTR3_MFIFO_ERR_BITWIDTH       1
// st_data_unavailable bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR3_ST_DATA_UNAVAILABLE_MASK 0x2000
#define GDMAC_GDT1_FTR3_ST_DATA_UNAVAILABLE_SHIFT 13 
#define GDMAC_GDT1_FTR3_ST_DATA_UNAVAILABLE_BIT  0x1
#define GDMAC_GDT1_FTR3_ST_DATA_UNAVAILABLE_BITWIDTH 1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR3_RESERVED2_MASK           0xC000
#define GDMAC_GDT1_FTR3_RESERVED2_SHIFT          14 
#define GDMAC_GDT1_FTR3_RESERVED2_BIT            0x3
#define GDMAC_GDT1_FTR3_RESERVED2_BITWIDTH       2
// instr_fetch_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR3_INSTR_FETCH_ERR_MASK     0x10000
#define GDMAC_GDT1_FTR3_INSTR_FETCH_ERR_SHIFT    16 
#define GDMAC_GDT1_FTR3_INSTR_FETCH_ERR_BIT      0x1
#define GDMAC_GDT1_FTR3_INSTR_FETCH_ERR_BITWIDTH 1
// data_write_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR3_DATA_WRITE_ERR_MASK      0x20000
#define GDMAC_GDT1_FTR3_DATA_WRITE_ERR_SHIFT     17 
#define GDMAC_GDT1_FTR3_DATA_WRITE_ERR_BIT       0x1
#define GDMAC_GDT1_FTR3_DATA_WRITE_ERR_BITWIDTH  1
// data_read_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR3_DATA_READ_ERR_MASK       0x40000
#define GDMAC_GDT1_FTR3_DATA_READ_ERR_SHIFT      18 
#define GDMAC_GDT1_FTR3_DATA_READ_ERR_BIT        0x1
#define GDMAC_GDT1_FTR3_DATA_READ_ERR_BITWIDTH   1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR3_RESERVED_MASK            0x3FF80000
#define GDMAC_GDT1_FTR3_RESERVED_SHIFT           19 
#define GDMAC_GDT1_FTR3_RESERVED_BIT             0x7FF
#define GDMAC_GDT1_FTR3_RESERVED_BITWIDTH        11
// dbg_instr bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR3_DBG_INSTR_MASK           0x40000000
#define GDMAC_GDT1_FTR3_DBG_INSTR_SHIFT          30 
#define GDMAC_GDT1_FTR3_DBG_INSTR_BIT            0x1
#define GDMAC_GDT1_FTR3_DBG_INSTR_BITWIDTH       1
// lockup_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR3_LOCKUP_ERR_MASK          0x80000000
#define GDMAC_GDT1_FTR3_LOCKUP_ERR_SHIFT         31 
#define GDMAC_GDT1_FTR3_LOCKUP_ERR_BIT           0x1
#define GDMAC_GDT1_FTR3_LOCKUP_ERR_BITWIDTH      1
// GDT1_FTR4 Register
#define GDMAC_GDT1_FTR4_OFS                      0x00001050
// undef_instr bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR4_UNDEF_INSTR_MASK         0x1
#define GDMAC_GDT1_FTR4_UNDEF_INSTR_SHIFT        0 
#define GDMAC_GDT1_FTR4_UNDEF_INSTR_BIT          0x1
#define GDMAC_GDT1_FTR4_UNDEF_INSTR_BITWIDTH     1
// operand_invalid bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR4_OPERAND_INVALID_MASK     0x2
#define GDMAC_GDT1_FTR4_OPERAND_INVALID_SHIFT    1 
#define GDMAC_GDT1_FTR4_OPERAND_INVALID_BIT      0x1
#define GDMAC_GDT1_FTR4_OPERAND_INVALID_BITWIDTH 1
// reserved4 bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR4_RESERVED4_MASK           0x1C
#define GDMAC_GDT1_FTR4_RESERVED4_SHIFT          2 
#define GDMAC_GDT1_FTR4_RESERVED4_BIT            0x7
#define GDMAC_GDT1_FTR4_RESERVED4_BITWIDTH       3
// ch_evnt_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR4_CH_EVNT_ERR_MASK         0x20
#define GDMAC_GDT1_FTR4_CH_EVNT_ERR_SHIFT        5 
#define GDMAC_GDT1_FTR4_CH_EVNT_ERR_BIT          0x1
#define GDMAC_GDT1_FTR4_CH_EVNT_ERR_BITWIDTH     1
// ch_periph_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR4_CH_PERIPH_ERR_MASK       0x40
#define GDMAC_GDT1_FTR4_CH_PERIPH_ERR_SHIFT      6 
#define GDMAC_GDT1_FTR4_CH_PERIPH_ERR_BIT        0x1
#define GDMAC_GDT1_FTR4_CH_PERIPH_ERR_BITWIDTH   1
// ch_rdwr_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR4_CH_RDWR_ERR_MASK         0x80
#define GDMAC_GDT1_FTR4_CH_RDWR_ERR_SHIFT        7 
#define GDMAC_GDT1_FTR4_CH_RDWR_ERR_BIT          0x1
#define GDMAC_GDT1_FTR4_CH_RDWR_ERR_BITWIDTH     1
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR4_RESERVED3_MASK           0xF00
#define GDMAC_GDT1_FTR4_RESERVED3_SHIFT          8 
#define GDMAC_GDT1_FTR4_RESERVED3_BIT            0xF
#define GDMAC_GDT1_FTR4_RESERVED3_BITWIDTH       4
// mfifo_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR4_MFIFO_ERR_MASK           0x1000
#define GDMAC_GDT1_FTR4_MFIFO_ERR_SHIFT          12 
#define GDMAC_GDT1_FTR4_MFIFO_ERR_BIT            0x1
#define GDMAC_GDT1_FTR4_MFIFO_ERR_BITWIDTH       1
// st_data_unavailable bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR4_ST_DATA_UNAVAILABLE_MASK 0x2000
#define GDMAC_GDT1_FTR4_ST_DATA_UNAVAILABLE_SHIFT 13 
#define GDMAC_GDT1_FTR4_ST_DATA_UNAVAILABLE_BIT  0x1
#define GDMAC_GDT1_FTR4_ST_DATA_UNAVAILABLE_BITWIDTH 1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR4_RESERVED2_MASK           0xC000
#define GDMAC_GDT1_FTR4_RESERVED2_SHIFT          14 
#define GDMAC_GDT1_FTR4_RESERVED2_BIT            0x3
#define GDMAC_GDT1_FTR4_RESERVED2_BITWIDTH       2
// instr_fetch_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR4_INSTR_FETCH_ERR_MASK     0x10000
#define GDMAC_GDT1_FTR4_INSTR_FETCH_ERR_SHIFT    16 
#define GDMAC_GDT1_FTR4_INSTR_FETCH_ERR_BIT      0x1
#define GDMAC_GDT1_FTR4_INSTR_FETCH_ERR_BITWIDTH 1
// data_write_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR4_DATA_WRITE_ERR_MASK      0x20000
#define GDMAC_GDT1_FTR4_DATA_WRITE_ERR_SHIFT     17 
#define GDMAC_GDT1_FTR4_DATA_WRITE_ERR_BIT       0x1
#define GDMAC_GDT1_FTR4_DATA_WRITE_ERR_BITWIDTH  1
// data_read_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR4_DATA_READ_ERR_MASK       0x40000
#define GDMAC_GDT1_FTR4_DATA_READ_ERR_SHIFT      18 
#define GDMAC_GDT1_FTR4_DATA_READ_ERR_BIT        0x1
#define GDMAC_GDT1_FTR4_DATA_READ_ERR_BITWIDTH   1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR4_RESERVED_MASK            0x3FF80000
#define GDMAC_GDT1_FTR4_RESERVED_SHIFT           19 
#define GDMAC_GDT1_FTR4_RESERVED_BIT             0x7FF
#define GDMAC_GDT1_FTR4_RESERVED_BITWIDTH        11
// dbg_instr bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR4_DBG_INSTR_MASK           0x40000000
#define GDMAC_GDT1_FTR4_DBG_INSTR_SHIFT          30 
#define GDMAC_GDT1_FTR4_DBG_INSTR_BIT            0x1
#define GDMAC_GDT1_FTR4_DBG_INSTR_BITWIDTH       1
// lockup_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR4_LOCKUP_ERR_MASK          0x80000000
#define GDMAC_GDT1_FTR4_LOCKUP_ERR_SHIFT         31 
#define GDMAC_GDT1_FTR4_LOCKUP_ERR_BIT           0x1
#define GDMAC_GDT1_FTR4_LOCKUP_ERR_BITWIDTH      1
// GDT1_FTR5 Register
#define GDMAC_GDT1_FTR5_OFS                      0x00001054
// undef_instr bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR5_UNDEF_INSTR_MASK         0x1
#define GDMAC_GDT1_FTR5_UNDEF_INSTR_SHIFT        0 
#define GDMAC_GDT1_FTR5_UNDEF_INSTR_BIT          0x1
#define GDMAC_GDT1_FTR5_UNDEF_INSTR_BITWIDTH     1
// operand_invalid bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR5_OPERAND_INVALID_MASK     0x2
#define GDMAC_GDT1_FTR5_OPERAND_INVALID_SHIFT    1 
#define GDMAC_GDT1_FTR5_OPERAND_INVALID_BIT      0x1
#define GDMAC_GDT1_FTR5_OPERAND_INVALID_BITWIDTH 1
// reserved4 bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR5_RESERVED4_MASK           0x1C
#define GDMAC_GDT1_FTR5_RESERVED4_SHIFT          2 
#define GDMAC_GDT1_FTR5_RESERVED4_BIT            0x7
#define GDMAC_GDT1_FTR5_RESERVED4_BITWIDTH       3
// ch_evnt_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR5_CH_EVNT_ERR_MASK         0x20
#define GDMAC_GDT1_FTR5_CH_EVNT_ERR_SHIFT        5 
#define GDMAC_GDT1_FTR5_CH_EVNT_ERR_BIT          0x1
#define GDMAC_GDT1_FTR5_CH_EVNT_ERR_BITWIDTH     1
// ch_periph_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR5_CH_PERIPH_ERR_MASK       0x40
#define GDMAC_GDT1_FTR5_CH_PERIPH_ERR_SHIFT      6 
#define GDMAC_GDT1_FTR5_CH_PERIPH_ERR_BIT        0x1
#define GDMAC_GDT1_FTR5_CH_PERIPH_ERR_BITWIDTH   1
// ch_rdwr_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR5_CH_RDWR_ERR_MASK         0x80
#define GDMAC_GDT1_FTR5_CH_RDWR_ERR_SHIFT        7 
#define GDMAC_GDT1_FTR5_CH_RDWR_ERR_BIT          0x1
#define GDMAC_GDT1_FTR5_CH_RDWR_ERR_BITWIDTH     1
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR5_RESERVED3_MASK           0xF00
#define GDMAC_GDT1_FTR5_RESERVED3_SHIFT          8 
#define GDMAC_GDT1_FTR5_RESERVED3_BIT            0xF
#define GDMAC_GDT1_FTR5_RESERVED3_BITWIDTH       4
// mfifo_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR5_MFIFO_ERR_MASK           0x1000
#define GDMAC_GDT1_FTR5_MFIFO_ERR_SHIFT          12 
#define GDMAC_GDT1_FTR5_MFIFO_ERR_BIT            0x1
#define GDMAC_GDT1_FTR5_MFIFO_ERR_BITWIDTH       1
// st_data_unavailable bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR5_ST_DATA_UNAVAILABLE_MASK 0x2000
#define GDMAC_GDT1_FTR5_ST_DATA_UNAVAILABLE_SHIFT 13 
#define GDMAC_GDT1_FTR5_ST_DATA_UNAVAILABLE_BIT  0x1
#define GDMAC_GDT1_FTR5_ST_DATA_UNAVAILABLE_BITWIDTH 1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR5_RESERVED2_MASK           0xC000
#define GDMAC_GDT1_FTR5_RESERVED2_SHIFT          14 
#define GDMAC_GDT1_FTR5_RESERVED2_BIT            0x3
#define GDMAC_GDT1_FTR5_RESERVED2_BITWIDTH       2
// instr_fetch_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR5_INSTR_FETCH_ERR_MASK     0x10000
#define GDMAC_GDT1_FTR5_INSTR_FETCH_ERR_SHIFT    16 
#define GDMAC_GDT1_FTR5_INSTR_FETCH_ERR_BIT      0x1
#define GDMAC_GDT1_FTR5_INSTR_FETCH_ERR_BITWIDTH 1
// data_write_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR5_DATA_WRITE_ERR_MASK      0x20000
#define GDMAC_GDT1_FTR5_DATA_WRITE_ERR_SHIFT     17 
#define GDMAC_GDT1_FTR5_DATA_WRITE_ERR_BIT       0x1
#define GDMAC_GDT1_FTR5_DATA_WRITE_ERR_BITWIDTH  1
// data_read_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR5_DATA_READ_ERR_MASK       0x40000
#define GDMAC_GDT1_FTR5_DATA_READ_ERR_SHIFT      18 
#define GDMAC_GDT1_FTR5_DATA_READ_ERR_BIT        0x1
#define GDMAC_GDT1_FTR5_DATA_READ_ERR_BITWIDTH   1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR5_RESERVED_MASK            0x3FF80000
#define GDMAC_GDT1_FTR5_RESERVED_SHIFT           19 
#define GDMAC_GDT1_FTR5_RESERVED_BIT             0x7FF
#define GDMAC_GDT1_FTR5_RESERVED_BITWIDTH        11
// dbg_instr bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR5_DBG_INSTR_MASK           0x40000000
#define GDMAC_GDT1_FTR5_DBG_INSTR_SHIFT          30 
#define GDMAC_GDT1_FTR5_DBG_INSTR_BIT            0x1
#define GDMAC_GDT1_FTR5_DBG_INSTR_BITWIDTH       1
// lockup_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR5_LOCKUP_ERR_MASK          0x80000000
#define GDMAC_GDT1_FTR5_LOCKUP_ERR_SHIFT         31 
#define GDMAC_GDT1_FTR5_LOCKUP_ERR_BIT           0x1
#define GDMAC_GDT1_FTR5_LOCKUP_ERR_BITWIDTH      1
// GDT1_FTR6 Register
#define GDMAC_GDT1_FTR6_OFS                      0x00001058
// undef_instr bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR6_UNDEF_INSTR_MASK         0x1
#define GDMAC_GDT1_FTR6_UNDEF_INSTR_SHIFT        0 
#define GDMAC_GDT1_FTR6_UNDEF_INSTR_BIT          0x1
#define GDMAC_GDT1_FTR6_UNDEF_INSTR_BITWIDTH     1
// operand_invalid bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR6_OPERAND_INVALID_MASK     0x2
#define GDMAC_GDT1_FTR6_OPERAND_INVALID_SHIFT    1 
#define GDMAC_GDT1_FTR6_OPERAND_INVALID_BIT      0x1
#define GDMAC_GDT1_FTR6_OPERAND_INVALID_BITWIDTH 1
// reserved4 bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR6_RESERVED4_MASK           0x1C
#define GDMAC_GDT1_FTR6_RESERVED4_SHIFT          2 
#define GDMAC_GDT1_FTR6_RESERVED4_BIT            0x7
#define GDMAC_GDT1_FTR6_RESERVED4_BITWIDTH       3
// ch_evnt_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR6_CH_EVNT_ERR_MASK         0x20
#define GDMAC_GDT1_FTR6_CH_EVNT_ERR_SHIFT        5 
#define GDMAC_GDT1_FTR6_CH_EVNT_ERR_BIT          0x1
#define GDMAC_GDT1_FTR6_CH_EVNT_ERR_BITWIDTH     1
// ch_periph_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR6_CH_PERIPH_ERR_MASK       0x40
#define GDMAC_GDT1_FTR6_CH_PERIPH_ERR_SHIFT      6 
#define GDMAC_GDT1_FTR6_CH_PERIPH_ERR_BIT        0x1
#define GDMAC_GDT1_FTR6_CH_PERIPH_ERR_BITWIDTH   1
// ch_rdwr_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR6_CH_RDWR_ERR_MASK         0x80
#define GDMAC_GDT1_FTR6_CH_RDWR_ERR_SHIFT        7 
#define GDMAC_GDT1_FTR6_CH_RDWR_ERR_BIT          0x1
#define GDMAC_GDT1_FTR6_CH_RDWR_ERR_BITWIDTH     1
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR6_RESERVED3_MASK           0xF00
#define GDMAC_GDT1_FTR6_RESERVED3_SHIFT          8 
#define GDMAC_GDT1_FTR6_RESERVED3_BIT            0xF
#define GDMAC_GDT1_FTR6_RESERVED3_BITWIDTH       4
// mfifo_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR6_MFIFO_ERR_MASK           0x1000
#define GDMAC_GDT1_FTR6_MFIFO_ERR_SHIFT          12 
#define GDMAC_GDT1_FTR6_MFIFO_ERR_BIT            0x1
#define GDMAC_GDT1_FTR6_MFIFO_ERR_BITWIDTH       1
// st_data_unavailable bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR6_ST_DATA_UNAVAILABLE_MASK 0x2000
#define GDMAC_GDT1_FTR6_ST_DATA_UNAVAILABLE_SHIFT 13 
#define GDMAC_GDT1_FTR6_ST_DATA_UNAVAILABLE_BIT  0x1
#define GDMAC_GDT1_FTR6_ST_DATA_UNAVAILABLE_BITWIDTH 1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR6_RESERVED2_MASK           0xC000
#define GDMAC_GDT1_FTR6_RESERVED2_SHIFT          14 
#define GDMAC_GDT1_FTR6_RESERVED2_BIT            0x3
#define GDMAC_GDT1_FTR6_RESERVED2_BITWIDTH       2
// instr_fetch_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR6_INSTR_FETCH_ERR_MASK     0x10000
#define GDMAC_GDT1_FTR6_INSTR_FETCH_ERR_SHIFT    16 
#define GDMAC_GDT1_FTR6_INSTR_FETCH_ERR_BIT      0x1
#define GDMAC_GDT1_FTR6_INSTR_FETCH_ERR_BITWIDTH 1
// data_write_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR6_DATA_WRITE_ERR_MASK      0x20000
#define GDMAC_GDT1_FTR6_DATA_WRITE_ERR_SHIFT     17 
#define GDMAC_GDT1_FTR6_DATA_WRITE_ERR_BIT       0x1
#define GDMAC_GDT1_FTR6_DATA_WRITE_ERR_BITWIDTH  1
// data_read_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR6_DATA_READ_ERR_MASK       0x40000
#define GDMAC_GDT1_FTR6_DATA_READ_ERR_SHIFT      18 
#define GDMAC_GDT1_FTR6_DATA_READ_ERR_BIT        0x1
#define GDMAC_GDT1_FTR6_DATA_READ_ERR_BITWIDTH   1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR6_RESERVED_MASK            0x3FF80000
#define GDMAC_GDT1_FTR6_RESERVED_SHIFT           19 
#define GDMAC_GDT1_FTR6_RESERVED_BIT             0x7FF
#define GDMAC_GDT1_FTR6_RESERVED_BITWIDTH        11
// dbg_instr bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR6_DBG_INSTR_MASK           0x40000000
#define GDMAC_GDT1_FTR6_DBG_INSTR_SHIFT          30 
#define GDMAC_GDT1_FTR6_DBG_INSTR_BIT            0x1
#define GDMAC_GDT1_FTR6_DBG_INSTR_BITWIDTH       1
// lockup_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR6_LOCKUP_ERR_MASK          0x80000000
#define GDMAC_GDT1_FTR6_LOCKUP_ERR_SHIFT         31 
#define GDMAC_GDT1_FTR6_LOCKUP_ERR_BIT           0x1
#define GDMAC_GDT1_FTR6_LOCKUP_ERR_BITWIDTH      1
// GDT1_FTR7 Register
#define GDMAC_GDT1_FTR7_OFS                      0x0000105C
// undef_instr bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR7_UNDEF_INSTR_MASK         0x1
#define GDMAC_GDT1_FTR7_UNDEF_INSTR_SHIFT        0 
#define GDMAC_GDT1_FTR7_UNDEF_INSTR_BIT          0x1
#define GDMAC_GDT1_FTR7_UNDEF_INSTR_BITWIDTH     1
// operand_invalid bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR7_OPERAND_INVALID_MASK     0x2
#define GDMAC_GDT1_FTR7_OPERAND_INVALID_SHIFT    1 
#define GDMAC_GDT1_FTR7_OPERAND_INVALID_BIT      0x1
#define GDMAC_GDT1_FTR7_OPERAND_INVALID_BITWIDTH 1
// reserved4 bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR7_RESERVED4_MASK           0x1C
#define GDMAC_GDT1_FTR7_RESERVED4_SHIFT          2 
#define GDMAC_GDT1_FTR7_RESERVED4_BIT            0x7
#define GDMAC_GDT1_FTR7_RESERVED4_BITWIDTH       3
// ch_evnt_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR7_CH_EVNT_ERR_MASK         0x20
#define GDMAC_GDT1_FTR7_CH_EVNT_ERR_SHIFT        5 
#define GDMAC_GDT1_FTR7_CH_EVNT_ERR_BIT          0x1
#define GDMAC_GDT1_FTR7_CH_EVNT_ERR_BITWIDTH     1
// ch_periph_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR7_CH_PERIPH_ERR_MASK       0x40
#define GDMAC_GDT1_FTR7_CH_PERIPH_ERR_SHIFT      6 
#define GDMAC_GDT1_FTR7_CH_PERIPH_ERR_BIT        0x1
#define GDMAC_GDT1_FTR7_CH_PERIPH_ERR_BITWIDTH   1
// ch_rdwr_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR7_CH_RDWR_ERR_MASK         0x80
#define GDMAC_GDT1_FTR7_CH_RDWR_ERR_SHIFT        7 
#define GDMAC_GDT1_FTR7_CH_RDWR_ERR_BIT          0x1
#define GDMAC_GDT1_FTR7_CH_RDWR_ERR_BITWIDTH     1
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR7_RESERVED3_MASK           0xF00
#define GDMAC_GDT1_FTR7_RESERVED3_SHIFT          8 
#define GDMAC_GDT1_FTR7_RESERVED3_BIT            0xF
#define GDMAC_GDT1_FTR7_RESERVED3_BITWIDTH       4
// mfifo_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR7_MFIFO_ERR_MASK           0x1000
#define GDMAC_GDT1_FTR7_MFIFO_ERR_SHIFT          12 
#define GDMAC_GDT1_FTR7_MFIFO_ERR_BIT            0x1
#define GDMAC_GDT1_FTR7_MFIFO_ERR_BITWIDTH       1
// st_data_unavailable bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR7_ST_DATA_UNAVAILABLE_MASK 0x2000
#define GDMAC_GDT1_FTR7_ST_DATA_UNAVAILABLE_SHIFT 13 
#define GDMAC_GDT1_FTR7_ST_DATA_UNAVAILABLE_BIT  0x1
#define GDMAC_GDT1_FTR7_ST_DATA_UNAVAILABLE_BITWIDTH 1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR7_RESERVED2_MASK           0xC000
#define GDMAC_GDT1_FTR7_RESERVED2_SHIFT          14 
#define GDMAC_GDT1_FTR7_RESERVED2_BIT            0x3
#define GDMAC_GDT1_FTR7_RESERVED2_BITWIDTH       2
// instr_fetch_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR7_INSTR_FETCH_ERR_MASK     0x10000
#define GDMAC_GDT1_FTR7_INSTR_FETCH_ERR_SHIFT    16 
#define GDMAC_GDT1_FTR7_INSTR_FETCH_ERR_BIT      0x1
#define GDMAC_GDT1_FTR7_INSTR_FETCH_ERR_BITWIDTH 1
// data_write_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR7_DATA_WRITE_ERR_MASK      0x20000
#define GDMAC_GDT1_FTR7_DATA_WRITE_ERR_SHIFT     17 
#define GDMAC_GDT1_FTR7_DATA_WRITE_ERR_BIT       0x1
#define GDMAC_GDT1_FTR7_DATA_WRITE_ERR_BITWIDTH  1
// data_read_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR7_DATA_READ_ERR_MASK       0x40000
#define GDMAC_GDT1_FTR7_DATA_READ_ERR_SHIFT      18 
#define GDMAC_GDT1_FTR7_DATA_READ_ERR_BIT        0x1
#define GDMAC_GDT1_FTR7_DATA_READ_ERR_BITWIDTH   1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR7_RESERVED_MASK            0x3FF80000
#define GDMAC_GDT1_FTR7_RESERVED_SHIFT           19 
#define GDMAC_GDT1_FTR7_RESERVED_BIT             0x7FF
#define GDMAC_GDT1_FTR7_RESERVED_BITWIDTH        11
// dbg_instr bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR7_DBG_INSTR_MASK           0x40000000
#define GDMAC_GDT1_FTR7_DBG_INSTR_SHIFT          30 
#define GDMAC_GDT1_FTR7_DBG_INSTR_BIT            0x1
#define GDMAC_GDT1_FTR7_DBG_INSTR_BITWIDTH       1
// lockup_err bitfiled (RO) Reset=0
#define GDMAC_GDT1_FTR7_LOCKUP_ERR_MASK          0x80000000
#define GDMAC_GDT1_FTR7_LOCKUP_ERR_SHIFT         31 
#define GDMAC_GDT1_FTR7_LOCKUP_ERR_BIT           0x1
#define GDMAC_GDT1_FTR7_LOCKUP_ERR_BITWIDTH      1
// GDT1_CSR0 Register
#define GDMAC_GDT1_CSR0_OFS                      0x00001100
// Channel_status bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR0_CHANNEL_STATUS_MASK      0xF
#define GDMAC_GDT1_CSR0_CHANNEL_STATUS_SHIFT     0 
#define GDMAC_GDT1_CSR0_CHANNEL_STATUS_BIT       0xF
#define GDMAC_GDT1_CSR0_CHANNEL_STATUS_BITWIDTH  4
// Wakeup_number bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR0_WAKEUP_NUMBER_MASK       0x1F0
#define GDMAC_GDT1_CSR0_WAKEUP_NUMBER_SHIFT      4 
#define GDMAC_GDT1_CSR0_WAKEUP_NUMBER_BIT        0x1F
#define GDMAC_GDT1_CSR0_WAKEUP_NUMBER_BITWIDTH   5
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR0_RESERVED3_MASK           0x3E00
#define GDMAC_GDT1_CSR0_RESERVED3_SHIFT          9 
#define GDMAC_GDT1_CSR0_RESERVED3_BIT            0x1F
#define GDMAC_GDT1_CSR0_RESERVED3_BITWIDTH       5
// dmawfp_b_ns bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR0_DMAWFP_B_NS_MASK         0x4000
#define GDMAC_GDT1_CSR0_DMAWFP_B_NS_SHIFT        14 
#define GDMAC_GDT1_CSR0_DMAWFP_B_NS_BIT          0x1
#define GDMAC_GDT1_CSR0_DMAWFP_B_NS_BITWIDTH     1
// dmawfp_periph bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR0_DMAWFP_PERIPH_MASK       0x8000
#define GDMAC_GDT1_CSR0_DMAWFP_PERIPH_SHIFT      15 
#define GDMAC_GDT1_CSR0_DMAWFP_PERIPH_BIT        0x1
#define GDMAC_GDT1_CSR0_DMAWFP_PERIPH_BITWIDTH   1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR0_RESERVED2_MASK           0x1F0000
#define GDMAC_GDT1_CSR0_RESERVED2_SHIFT          16 
#define GDMAC_GDT1_CSR0_RESERVED2_BIT            0x1F
#define GDMAC_GDT1_CSR0_RESERVED2_BITWIDTH       5
// CSN bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR0_CSN_MASK                 0x200000
#define GDMAC_GDT1_CSR0_CSN_SHIFT                21 
#define GDMAC_GDT1_CSR0_CSN_BIT                  0x1
#define GDMAC_GDT1_CSR0_CSN_BITWIDTH             1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR0_RESERVED_MASK            0xFFC00000
#define GDMAC_GDT1_CSR0_RESERVED_SHIFT           22 
#define GDMAC_GDT1_CSR0_RESERVED_BIT             0x3FF
#define GDMAC_GDT1_CSR0_RESERVED_BITWIDTH        10
// GDT1_CPC0 Register
#define GDMAC_GDT1_CPC0_OFS                      0x00001104
// pc_chnl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CPC0_PC_CHNL_MASK             0xFFFFFFFF
#define GDMAC_GDT1_CPC0_PC_CHNL_SHIFT            0 
#define GDMAC_GDT1_CPC0_PC_CHNL_BIT              0xFFFFFFFF
#define GDMAC_GDT1_CPC0_PC_CHNL_BITWIDTH         32
// GDT1_CSR1 Register
#define GDMAC_GDT1_CSR1_OFS                      0x00001108
// Channel_status bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR1_CHANNEL_STATUS_MASK      0xF
#define GDMAC_GDT1_CSR1_CHANNEL_STATUS_SHIFT     0 
#define GDMAC_GDT1_CSR1_CHANNEL_STATUS_BIT       0xF
#define GDMAC_GDT1_CSR1_CHANNEL_STATUS_BITWIDTH  4
// Wakeup_number bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR1_WAKEUP_NUMBER_MASK       0x1F0
#define GDMAC_GDT1_CSR1_WAKEUP_NUMBER_SHIFT      4 
#define GDMAC_GDT1_CSR1_WAKEUP_NUMBER_BIT        0x1F
#define GDMAC_GDT1_CSR1_WAKEUP_NUMBER_BITWIDTH   5
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR1_RESERVED3_MASK           0x3E00
#define GDMAC_GDT1_CSR1_RESERVED3_SHIFT          9 
#define GDMAC_GDT1_CSR1_RESERVED3_BIT            0x1F
#define GDMAC_GDT1_CSR1_RESERVED3_BITWIDTH       5
// dmawfp_b_ns bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR1_DMAWFP_B_NS_MASK         0x4000
#define GDMAC_GDT1_CSR1_DMAWFP_B_NS_SHIFT        14 
#define GDMAC_GDT1_CSR1_DMAWFP_B_NS_BIT          0x1
#define GDMAC_GDT1_CSR1_DMAWFP_B_NS_BITWIDTH     1
// dmawfp_periph bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR1_DMAWFP_PERIPH_MASK       0x8000
#define GDMAC_GDT1_CSR1_DMAWFP_PERIPH_SHIFT      15 
#define GDMAC_GDT1_CSR1_DMAWFP_PERIPH_BIT        0x1
#define GDMAC_GDT1_CSR1_DMAWFP_PERIPH_BITWIDTH   1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR1_RESERVED2_MASK           0x1F0000
#define GDMAC_GDT1_CSR1_RESERVED2_SHIFT          16 
#define GDMAC_GDT1_CSR1_RESERVED2_BIT            0x1F
#define GDMAC_GDT1_CSR1_RESERVED2_BITWIDTH       5
// CSN bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR1_CSN_MASK                 0x200000
#define GDMAC_GDT1_CSR1_CSN_SHIFT                21 
#define GDMAC_GDT1_CSR1_CSN_BIT                  0x1
#define GDMAC_GDT1_CSR1_CSN_BITWIDTH             1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR1_RESERVED_MASK            0xFFC00000
#define GDMAC_GDT1_CSR1_RESERVED_SHIFT           22 
#define GDMAC_GDT1_CSR1_RESERVED_BIT             0x3FF
#define GDMAC_GDT1_CSR1_RESERVED_BITWIDTH        10
// GDT1_CPC1 Register
#define GDMAC_GDT1_CPC1_OFS                      0x0000110C
// pc_chnl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CPC1_PC_CHNL_MASK             0xFFFFFFFF
#define GDMAC_GDT1_CPC1_PC_CHNL_SHIFT            0 
#define GDMAC_GDT1_CPC1_PC_CHNL_BIT              0xFFFFFFFF
#define GDMAC_GDT1_CPC1_PC_CHNL_BITWIDTH         32
// GDT1_CSR2 Register
#define GDMAC_GDT1_CSR2_OFS                      0x00001110
// Channel_status bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR2_CHANNEL_STATUS_MASK      0xF
#define GDMAC_GDT1_CSR2_CHANNEL_STATUS_SHIFT     0 
#define GDMAC_GDT1_CSR2_CHANNEL_STATUS_BIT       0xF
#define GDMAC_GDT1_CSR2_CHANNEL_STATUS_BITWIDTH  4
// Wakeup_number bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR2_WAKEUP_NUMBER_MASK       0x1F0
#define GDMAC_GDT1_CSR2_WAKEUP_NUMBER_SHIFT      4 
#define GDMAC_GDT1_CSR2_WAKEUP_NUMBER_BIT        0x1F
#define GDMAC_GDT1_CSR2_WAKEUP_NUMBER_BITWIDTH   5
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR2_RESERVED3_MASK           0x3E00
#define GDMAC_GDT1_CSR2_RESERVED3_SHIFT          9 
#define GDMAC_GDT1_CSR2_RESERVED3_BIT            0x1F
#define GDMAC_GDT1_CSR2_RESERVED3_BITWIDTH       5
// dmawfp_b_ns bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR2_DMAWFP_B_NS_MASK         0x4000
#define GDMAC_GDT1_CSR2_DMAWFP_B_NS_SHIFT        14 
#define GDMAC_GDT1_CSR2_DMAWFP_B_NS_BIT          0x1
#define GDMAC_GDT1_CSR2_DMAWFP_B_NS_BITWIDTH     1
// dmawfp_periph bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR2_DMAWFP_PERIPH_MASK       0x8000
#define GDMAC_GDT1_CSR2_DMAWFP_PERIPH_SHIFT      15 
#define GDMAC_GDT1_CSR2_DMAWFP_PERIPH_BIT        0x1
#define GDMAC_GDT1_CSR2_DMAWFP_PERIPH_BITWIDTH   1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR2_RESERVED2_MASK           0x1F0000
#define GDMAC_GDT1_CSR2_RESERVED2_SHIFT          16 
#define GDMAC_GDT1_CSR2_RESERVED2_BIT            0x1F
#define GDMAC_GDT1_CSR2_RESERVED2_BITWIDTH       5
// CSN bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR2_CSN_MASK                 0x200000
#define GDMAC_GDT1_CSR2_CSN_SHIFT                21 
#define GDMAC_GDT1_CSR2_CSN_BIT                  0x1
#define GDMAC_GDT1_CSR2_CSN_BITWIDTH             1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR2_RESERVED_MASK            0xFFC00000
#define GDMAC_GDT1_CSR2_RESERVED_SHIFT           22 
#define GDMAC_GDT1_CSR2_RESERVED_BIT             0x3FF
#define GDMAC_GDT1_CSR2_RESERVED_BITWIDTH        10
// GDT1_CPC2 Register
#define GDMAC_GDT1_CPC2_OFS                      0x00001114
// pc_chnl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CPC2_PC_CHNL_MASK             0xFFFFFFFF
#define GDMAC_GDT1_CPC2_PC_CHNL_SHIFT            0 
#define GDMAC_GDT1_CPC2_PC_CHNL_BIT              0xFFFFFFFF
#define GDMAC_GDT1_CPC2_PC_CHNL_BITWIDTH         32
// GDT1_CSR3 Register
#define GDMAC_GDT1_CSR3_OFS                      0x00001118
// Channel_status bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR3_CHANNEL_STATUS_MASK      0xF
#define GDMAC_GDT1_CSR3_CHANNEL_STATUS_SHIFT     0 
#define GDMAC_GDT1_CSR3_CHANNEL_STATUS_BIT       0xF
#define GDMAC_GDT1_CSR3_CHANNEL_STATUS_BITWIDTH  4
// Wakeup_number bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR3_WAKEUP_NUMBER_MASK       0x1F0
#define GDMAC_GDT1_CSR3_WAKEUP_NUMBER_SHIFT      4 
#define GDMAC_GDT1_CSR3_WAKEUP_NUMBER_BIT        0x1F
#define GDMAC_GDT1_CSR3_WAKEUP_NUMBER_BITWIDTH   5
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR3_RESERVED3_MASK           0x3E00
#define GDMAC_GDT1_CSR3_RESERVED3_SHIFT          9 
#define GDMAC_GDT1_CSR3_RESERVED3_BIT            0x1F
#define GDMAC_GDT1_CSR3_RESERVED3_BITWIDTH       5
// dmawfp_b_ns bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR3_DMAWFP_B_NS_MASK         0x4000
#define GDMAC_GDT1_CSR3_DMAWFP_B_NS_SHIFT        14 
#define GDMAC_GDT1_CSR3_DMAWFP_B_NS_BIT          0x1
#define GDMAC_GDT1_CSR3_DMAWFP_B_NS_BITWIDTH     1
// dmawfp_periph bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR3_DMAWFP_PERIPH_MASK       0x8000
#define GDMAC_GDT1_CSR3_DMAWFP_PERIPH_SHIFT      15 
#define GDMAC_GDT1_CSR3_DMAWFP_PERIPH_BIT        0x1
#define GDMAC_GDT1_CSR3_DMAWFP_PERIPH_BITWIDTH   1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR3_RESERVED2_MASK           0x1F0000
#define GDMAC_GDT1_CSR3_RESERVED2_SHIFT          16 
#define GDMAC_GDT1_CSR3_RESERVED2_BIT            0x1F
#define GDMAC_GDT1_CSR3_RESERVED2_BITWIDTH       5
// CSN bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR3_CSN_MASK                 0x200000
#define GDMAC_GDT1_CSR3_CSN_SHIFT                21 
#define GDMAC_GDT1_CSR3_CSN_BIT                  0x1
#define GDMAC_GDT1_CSR3_CSN_BITWIDTH             1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR3_RESERVED_MASK            0xFFC00000
#define GDMAC_GDT1_CSR3_RESERVED_SHIFT           22 
#define GDMAC_GDT1_CSR3_RESERVED_BIT             0x3FF
#define GDMAC_GDT1_CSR3_RESERVED_BITWIDTH        10
// GDT1_CPC3 Register
#define GDMAC_GDT1_CPC3_OFS                      0x0000111C
// pc_chnl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CPC3_PC_CHNL_MASK             0xFFFFFFFF
#define GDMAC_GDT1_CPC3_PC_CHNL_SHIFT            0 
#define GDMAC_GDT1_CPC3_PC_CHNL_BIT              0xFFFFFFFF
#define GDMAC_GDT1_CPC3_PC_CHNL_BITWIDTH         32
// GDT1_CSR4 Register
#define GDMAC_GDT1_CSR4_OFS                      0x00001120
// Channel_status bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR4_CHANNEL_STATUS_MASK      0xF
#define GDMAC_GDT1_CSR4_CHANNEL_STATUS_SHIFT     0 
#define GDMAC_GDT1_CSR4_CHANNEL_STATUS_BIT       0xF
#define GDMAC_GDT1_CSR4_CHANNEL_STATUS_BITWIDTH  4
// Wakeup_number bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR4_WAKEUP_NUMBER_MASK       0x1F0
#define GDMAC_GDT1_CSR4_WAKEUP_NUMBER_SHIFT      4 
#define GDMAC_GDT1_CSR4_WAKEUP_NUMBER_BIT        0x1F
#define GDMAC_GDT1_CSR4_WAKEUP_NUMBER_BITWIDTH   5
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR4_RESERVED3_MASK           0x3E00
#define GDMAC_GDT1_CSR4_RESERVED3_SHIFT          9 
#define GDMAC_GDT1_CSR4_RESERVED3_BIT            0x1F
#define GDMAC_GDT1_CSR4_RESERVED3_BITWIDTH       5
// dmawfp_b_ns bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR4_DMAWFP_B_NS_MASK         0x4000
#define GDMAC_GDT1_CSR4_DMAWFP_B_NS_SHIFT        14 
#define GDMAC_GDT1_CSR4_DMAWFP_B_NS_BIT          0x1
#define GDMAC_GDT1_CSR4_DMAWFP_B_NS_BITWIDTH     1
// dmawfp_periph bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR4_DMAWFP_PERIPH_MASK       0x8000
#define GDMAC_GDT1_CSR4_DMAWFP_PERIPH_SHIFT      15 
#define GDMAC_GDT1_CSR4_DMAWFP_PERIPH_BIT        0x1
#define GDMAC_GDT1_CSR4_DMAWFP_PERIPH_BITWIDTH   1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR4_RESERVED2_MASK           0x1F0000
#define GDMAC_GDT1_CSR4_RESERVED2_SHIFT          16 
#define GDMAC_GDT1_CSR4_RESERVED2_BIT            0x1F
#define GDMAC_GDT1_CSR4_RESERVED2_BITWIDTH       5
// CSN bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR4_CSN_MASK                 0x200000
#define GDMAC_GDT1_CSR4_CSN_SHIFT                21 
#define GDMAC_GDT1_CSR4_CSN_BIT                  0x1
#define GDMAC_GDT1_CSR4_CSN_BITWIDTH             1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR4_RESERVED_MASK            0xFFC00000
#define GDMAC_GDT1_CSR4_RESERVED_SHIFT           22 
#define GDMAC_GDT1_CSR4_RESERVED_BIT             0x3FF
#define GDMAC_GDT1_CSR4_RESERVED_BITWIDTH        10
// GDT1_CPC4 Register
#define GDMAC_GDT1_CPC4_OFS                      0x00001124
// pc_chnl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CPC4_PC_CHNL_MASK             0xFFFFFFFF
#define GDMAC_GDT1_CPC4_PC_CHNL_SHIFT            0 
#define GDMAC_GDT1_CPC4_PC_CHNL_BIT              0xFFFFFFFF
#define GDMAC_GDT1_CPC4_PC_CHNL_BITWIDTH         32
// GDT1_CSR5 Register
#define GDMAC_GDT1_CSR5_OFS                      0x00001128
// Channel_status bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR5_CHANNEL_STATUS_MASK      0xF
#define GDMAC_GDT1_CSR5_CHANNEL_STATUS_SHIFT     0 
#define GDMAC_GDT1_CSR5_CHANNEL_STATUS_BIT       0xF
#define GDMAC_GDT1_CSR5_CHANNEL_STATUS_BITWIDTH  4
// Wakeup_number bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR5_WAKEUP_NUMBER_MASK       0x1F0
#define GDMAC_GDT1_CSR5_WAKEUP_NUMBER_SHIFT      4 
#define GDMAC_GDT1_CSR5_WAKEUP_NUMBER_BIT        0x1F
#define GDMAC_GDT1_CSR5_WAKEUP_NUMBER_BITWIDTH   5
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR5_RESERVED3_MASK           0x3E00
#define GDMAC_GDT1_CSR5_RESERVED3_SHIFT          9 
#define GDMAC_GDT1_CSR5_RESERVED3_BIT            0x1F
#define GDMAC_GDT1_CSR5_RESERVED3_BITWIDTH       5
// dmawfp_b_ns bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR5_DMAWFP_B_NS_MASK         0x4000
#define GDMAC_GDT1_CSR5_DMAWFP_B_NS_SHIFT        14 
#define GDMAC_GDT1_CSR5_DMAWFP_B_NS_BIT          0x1
#define GDMAC_GDT1_CSR5_DMAWFP_B_NS_BITWIDTH     1
// dmawfp_periph bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR5_DMAWFP_PERIPH_MASK       0x8000
#define GDMAC_GDT1_CSR5_DMAWFP_PERIPH_SHIFT      15 
#define GDMAC_GDT1_CSR5_DMAWFP_PERIPH_BIT        0x1
#define GDMAC_GDT1_CSR5_DMAWFP_PERIPH_BITWIDTH   1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR5_RESERVED2_MASK           0x1F0000
#define GDMAC_GDT1_CSR5_RESERVED2_SHIFT          16 
#define GDMAC_GDT1_CSR5_RESERVED2_BIT            0x1F
#define GDMAC_GDT1_CSR5_RESERVED2_BITWIDTH       5
// CSN bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR5_CSN_MASK                 0x200000
#define GDMAC_GDT1_CSR5_CSN_SHIFT                21 
#define GDMAC_GDT1_CSR5_CSN_BIT                  0x1
#define GDMAC_GDT1_CSR5_CSN_BITWIDTH             1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR5_RESERVED_MASK            0xFFC00000
#define GDMAC_GDT1_CSR5_RESERVED_SHIFT           22 
#define GDMAC_GDT1_CSR5_RESERVED_BIT             0x3FF
#define GDMAC_GDT1_CSR5_RESERVED_BITWIDTH        10
// GDT1_CPC5 Register
#define GDMAC_GDT1_CPC5_OFS                      0x0000112C
// pc_chnl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CPC5_PC_CHNL_MASK             0xFFFFFFFF
#define GDMAC_GDT1_CPC5_PC_CHNL_SHIFT            0 
#define GDMAC_GDT1_CPC5_PC_CHNL_BIT              0xFFFFFFFF
#define GDMAC_GDT1_CPC5_PC_CHNL_BITWIDTH         32
// GDT1_CSR6 Register
#define GDMAC_GDT1_CSR6_OFS                      0x00001130
// Channel_status bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR6_CHANNEL_STATUS_MASK      0xF
#define GDMAC_GDT1_CSR6_CHANNEL_STATUS_SHIFT     0 
#define GDMAC_GDT1_CSR6_CHANNEL_STATUS_BIT       0xF
#define GDMAC_GDT1_CSR6_CHANNEL_STATUS_BITWIDTH  4
// Wakeup_number bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR6_WAKEUP_NUMBER_MASK       0x1F0
#define GDMAC_GDT1_CSR6_WAKEUP_NUMBER_SHIFT      4 
#define GDMAC_GDT1_CSR6_WAKEUP_NUMBER_BIT        0x1F
#define GDMAC_GDT1_CSR6_WAKEUP_NUMBER_BITWIDTH   5
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR6_RESERVED3_MASK           0x3E00
#define GDMAC_GDT1_CSR6_RESERVED3_SHIFT          9 
#define GDMAC_GDT1_CSR6_RESERVED3_BIT            0x1F
#define GDMAC_GDT1_CSR6_RESERVED3_BITWIDTH       5
// dmawfp_b_ns bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR6_DMAWFP_B_NS_MASK         0x4000
#define GDMAC_GDT1_CSR6_DMAWFP_B_NS_SHIFT        14 
#define GDMAC_GDT1_CSR6_DMAWFP_B_NS_BIT          0x1
#define GDMAC_GDT1_CSR6_DMAWFP_B_NS_BITWIDTH     1
// dmawfp_periph bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR6_DMAWFP_PERIPH_MASK       0x8000
#define GDMAC_GDT1_CSR6_DMAWFP_PERIPH_SHIFT      15 
#define GDMAC_GDT1_CSR6_DMAWFP_PERIPH_BIT        0x1
#define GDMAC_GDT1_CSR6_DMAWFP_PERIPH_BITWIDTH   1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR6_RESERVED2_MASK           0x1F0000
#define GDMAC_GDT1_CSR6_RESERVED2_SHIFT          16 
#define GDMAC_GDT1_CSR6_RESERVED2_BIT            0x1F
#define GDMAC_GDT1_CSR6_RESERVED2_BITWIDTH       5
// CSN bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR6_CSN_MASK                 0x200000
#define GDMAC_GDT1_CSR6_CSN_SHIFT                21 
#define GDMAC_GDT1_CSR6_CSN_BIT                  0x1
#define GDMAC_GDT1_CSR6_CSN_BITWIDTH             1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR6_RESERVED_MASK            0xFFC00000
#define GDMAC_GDT1_CSR6_RESERVED_SHIFT           22 
#define GDMAC_GDT1_CSR6_RESERVED_BIT             0x3FF
#define GDMAC_GDT1_CSR6_RESERVED_BITWIDTH        10
// GDT1_CPC6 Register
#define GDMAC_GDT1_CPC6_OFS                      0x00001134
// pc_chnl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CPC6_PC_CHNL_MASK             0xFFFFFFFF
#define GDMAC_GDT1_CPC6_PC_CHNL_SHIFT            0 
#define GDMAC_GDT1_CPC6_PC_CHNL_BIT              0xFFFFFFFF
#define GDMAC_GDT1_CPC6_PC_CHNL_BITWIDTH         32
// GDT1_CSR7 Register
#define GDMAC_GDT1_CSR7_OFS                      0x00001138
// Channel_status bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR7_CHANNEL_STATUS_MASK      0xF
#define GDMAC_GDT1_CSR7_CHANNEL_STATUS_SHIFT     0 
#define GDMAC_GDT1_CSR7_CHANNEL_STATUS_BIT       0xF
#define GDMAC_GDT1_CSR7_CHANNEL_STATUS_BITWIDTH  4
// Wakeup_number bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR7_WAKEUP_NUMBER_MASK       0x1F0
#define GDMAC_GDT1_CSR7_WAKEUP_NUMBER_SHIFT      4 
#define GDMAC_GDT1_CSR7_WAKEUP_NUMBER_BIT        0x1F
#define GDMAC_GDT1_CSR7_WAKEUP_NUMBER_BITWIDTH   5
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR7_RESERVED3_MASK           0x3E00
#define GDMAC_GDT1_CSR7_RESERVED3_SHIFT          9 
#define GDMAC_GDT1_CSR7_RESERVED3_BIT            0x1F
#define GDMAC_GDT1_CSR7_RESERVED3_BITWIDTH       5
// dmawfp_b_ns bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR7_DMAWFP_B_NS_MASK         0x4000
#define GDMAC_GDT1_CSR7_DMAWFP_B_NS_SHIFT        14 
#define GDMAC_GDT1_CSR7_DMAWFP_B_NS_BIT          0x1
#define GDMAC_GDT1_CSR7_DMAWFP_B_NS_BITWIDTH     1
// dmawfp_periph bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR7_DMAWFP_PERIPH_MASK       0x8000
#define GDMAC_GDT1_CSR7_DMAWFP_PERIPH_SHIFT      15 
#define GDMAC_GDT1_CSR7_DMAWFP_PERIPH_BIT        0x1
#define GDMAC_GDT1_CSR7_DMAWFP_PERIPH_BITWIDTH   1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR7_RESERVED2_MASK           0x1F0000
#define GDMAC_GDT1_CSR7_RESERVED2_SHIFT          16 
#define GDMAC_GDT1_CSR7_RESERVED2_BIT            0x1F
#define GDMAC_GDT1_CSR7_RESERVED2_BITWIDTH       5
// CSN bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR7_CSN_MASK                 0x200000
#define GDMAC_GDT1_CSR7_CSN_SHIFT                21 
#define GDMAC_GDT1_CSR7_CSN_BIT                  0x1
#define GDMAC_GDT1_CSR7_CSN_BITWIDTH             1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_CSR7_RESERVED_MASK            0xFFC00000
#define GDMAC_GDT1_CSR7_RESERVED_SHIFT           22 
#define GDMAC_GDT1_CSR7_RESERVED_BIT             0x3FF
#define GDMAC_GDT1_CSR7_RESERVED_BITWIDTH        10
// GDT1_CPC7 Register
#define GDMAC_GDT1_CPC7_OFS                      0x0000113C
// pc_chnl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CPC7_PC_CHNL_MASK             0xFFFFFFFF
#define GDMAC_GDT1_CPC7_PC_CHNL_SHIFT            0 
#define GDMAC_GDT1_CPC7_PC_CHNL_BIT              0xFFFFFFFF
#define GDMAC_GDT1_CPC7_PC_CHNL_BITWIDTH         32
// GDT1_SAR0 Register
#define GDMAC_GDT1_SAR0_OFS                      0x00001400
// src_addr bitfiled (RO) Reset=0
#define GDMAC_GDT1_SAR0_SRC_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT1_SAR0_SRC_ADDR_SHIFT           0 
#define GDMAC_GDT1_SAR0_SRC_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT1_SAR0_SRC_ADDR_BITWIDTH        32
// GDT1_DAR0 Register
#define GDMAC_GDT1_DAR0_OFS                      0x00001404
// dst_addr bitfiled (RO) Reset=0
#define GDMAC_GDT1_DAR0_DST_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT1_DAR0_DST_ADDR_SHIFT           0 
#define GDMAC_GDT1_DAR0_DST_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT1_DAR0_DST_ADDR_BITWIDTH        32
// GDT1_CCR0 Register
#define GDMAC_GDT1_CCR0_OFS                      0x00001408
// src_inc bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR0_SRC_INC_MASK             0x1
#define GDMAC_GDT1_CCR0_SRC_INC_SHIFT            0 
#define GDMAC_GDT1_CCR0_SRC_INC_BIT              0x1
#define GDMAC_GDT1_CCR0_SRC_INC_BITWIDTH         1
// src_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR0_SRC_BURST_SIZE_MASK      0xE
#define GDMAC_GDT1_CCR0_SRC_BURST_SIZE_SHIFT     1 
#define GDMAC_GDT1_CCR0_SRC_BURST_SIZE_BIT       0x7
#define GDMAC_GDT1_CCR0_SRC_BURST_SIZE_BITWIDTH  3
// src_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR0_SRC_BURST_LEN_MASK       0xF0
#define GDMAC_GDT1_CCR0_SRC_BURST_LEN_SHIFT      4 
#define GDMAC_GDT1_CCR0_SRC_BURST_LEN_BIT        0xF
#define GDMAC_GDT1_CCR0_SRC_BURST_LEN_BITWIDTH   4
// src_prot_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR0_SRC_PROT_CTRL_MASK       0x700
#define GDMAC_GDT1_CCR0_SRC_PROT_CTRL_SHIFT      8 
#define GDMAC_GDT1_CCR0_SRC_PROT_CTRL_BIT        0x7
#define GDMAC_GDT1_CCR0_SRC_PROT_CTRL_BITWIDTH   3
// src_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR0_SRC_CACHE_CTRL_MASK      0x3800
#define GDMAC_GDT1_CCR0_SRC_CACHE_CTRL_SHIFT     11 
#define GDMAC_GDT1_CCR0_SRC_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT1_CCR0_SRC_CACHE_CTRL_BITWIDTH  3
// dst_inc bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR0_DST_INC_MASK             0x4000
#define GDMAC_GDT1_CCR0_DST_INC_SHIFT            14 
#define GDMAC_GDT1_CCR0_DST_INC_BIT              0x1
#define GDMAC_GDT1_CCR0_DST_INC_BITWIDTH         1
// dst_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR0_DST_BURST_SIZE_MASK      0x38000
#define GDMAC_GDT1_CCR0_DST_BURST_SIZE_SHIFT     15 
#define GDMAC_GDT1_CCR0_DST_BURST_SIZE_BIT       0x7
#define GDMAC_GDT1_CCR0_DST_BURST_SIZE_BITWIDTH  3
// dst_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR0_DST_BURST_LEN_MASK       0x3C0000
#define GDMAC_GDT1_CCR0_DST_BURST_LEN_SHIFT      18 
#define GDMAC_GDT1_CCR0_DST_BURST_LEN_BIT        0xF
#define GDMAC_GDT1_CCR0_DST_BURST_LEN_BITWIDTH   4
// dst_prot_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR0_DST_PROT_CTRL_MASK       0x1C00000
#define GDMAC_GDT1_CCR0_DST_PROT_CTRL_SHIFT      22 
#define GDMAC_GDT1_CCR0_DST_PROT_CTRL_BIT        0x7
#define GDMAC_GDT1_CCR0_DST_PROT_CTRL_BITWIDTH   3
// dst_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR0_DST_CACHE_CTRL_MASK      0xE000000
#define GDMAC_GDT1_CCR0_DST_CACHE_CTRL_SHIFT     25 
#define GDMAC_GDT1_CCR0_DST_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT1_CCR0_DST_CACHE_CTRL_BITWIDTH  3
// endian_swap_size bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR0_ENDIAN_SWAP_SIZE_MASK    0x70000000
#define GDMAC_GDT1_CCR0_ENDIAN_SWAP_SIZE_SHIFT   28 
#define GDMAC_GDT1_CCR0_ENDIAN_SWAP_SIZE_BIT     0x7
#define GDMAC_GDT1_CCR0_ENDIAN_SWAP_SIZE_BITWIDTH 3
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR0_RESERVED_MASK            0x80000000
#define GDMAC_GDT1_CCR0_RESERVED_SHIFT           31 
#define GDMAC_GDT1_CCR0_RESERVED_BIT             0x1
#define GDMAC_GDT1_CCR0_RESERVED_BITWIDTH        1
// GDT1_LC0_0 Register
#define GDMAC_GDT1_LC0_0_OFS                     0x0000140C
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC0_0_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT1_LC0_0_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT1_LC0_0_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT1_LC0_0_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC0_0_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT1_LC0_0_RESERVED_SHIFT          8 
#define GDMAC_GDT1_LC0_0_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT1_LC0_0_RESERVED_BITWIDTH       24
// GDT1_LC1_0 Register
#define GDMAC_GDT1_LC1_0_OFS                     0x00001410
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC1_0_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT1_LC1_0_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT1_LC1_0_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT1_LC1_0_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC1_0_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT1_LC1_0_RESERVED_SHIFT          8 
#define GDMAC_GDT1_LC1_0_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT1_LC1_0_RESERVED_BITWIDTH       24
// GDT1_SAR1 Register
#define GDMAC_GDT1_SAR1_OFS                      0x00001420
// src_addr bitfiled (RO) Reset=0
#define GDMAC_GDT1_SAR1_SRC_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT1_SAR1_SRC_ADDR_SHIFT           0 
#define GDMAC_GDT1_SAR1_SRC_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT1_SAR1_SRC_ADDR_BITWIDTH        32
// GDT1_DAR1 Register
#define GDMAC_GDT1_DAR1_OFS                      0x00001424
// dst_addr bitfiled (RO) Reset=0
#define GDMAC_GDT1_DAR1_DST_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT1_DAR1_DST_ADDR_SHIFT           0 
#define GDMAC_GDT1_DAR1_DST_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT1_DAR1_DST_ADDR_BITWIDTH        32
// GDT1_CCR1 Register
#define GDMAC_GDT1_CCR1_OFS                      0x00001428
// src_inc bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR1_SRC_INC_MASK             0x1
#define GDMAC_GDT1_CCR1_SRC_INC_SHIFT            0 
#define GDMAC_GDT1_CCR1_SRC_INC_BIT              0x1
#define GDMAC_GDT1_CCR1_SRC_INC_BITWIDTH         1
// src_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR1_SRC_BURST_SIZE_MASK      0xE
#define GDMAC_GDT1_CCR1_SRC_BURST_SIZE_SHIFT     1 
#define GDMAC_GDT1_CCR1_SRC_BURST_SIZE_BIT       0x7
#define GDMAC_GDT1_CCR1_SRC_BURST_SIZE_BITWIDTH  3
// src_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR1_SRC_BURST_LEN_MASK       0xF0
#define GDMAC_GDT1_CCR1_SRC_BURST_LEN_SHIFT      4 
#define GDMAC_GDT1_CCR1_SRC_BURST_LEN_BIT        0xF
#define GDMAC_GDT1_CCR1_SRC_BURST_LEN_BITWIDTH   4
// src_prot_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR1_SRC_PROT_CTRL_MASK       0x700
#define GDMAC_GDT1_CCR1_SRC_PROT_CTRL_SHIFT      8 
#define GDMAC_GDT1_CCR1_SRC_PROT_CTRL_BIT        0x7
#define GDMAC_GDT1_CCR1_SRC_PROT_CTRL_BITWIDTH   3
// src_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR1_SRC_CACHE_CTRL_MASK      0x3800
#define GDMAC_GDT1_CCR1_SRC_CACHE_CTRL_SHIFT     11 
#define GDMAC_GDT1_CCR1_SRC_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT1_CCR1_SRC_CACHE_CTRL_BITWIDTH  3
// dst_inc bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR1_DST_INC_MASK             0x4000
#define GDMAC_GDT1_CCR1_DST_INC_SHIFT            14 
#define GDMAC_GDT1_CCR1_DST_INC_BIT              0x1
#define GDMAC_GDT1_CCR1_DST_INC_BITWIDTH         1
// dst_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR1_DST_BURST_SIZE_MASK      0x38000
#define GDMAC_GDT1_CCR1_DST_BURST_SIZE_SHIFT     15 
#define GDMAC_GDT1_CCR1_DST_BURST_SIZE_BIT       0x7
#define GDMAC_GDT1_CCR1_DST_BURST_SIZE_BITWIDTH  3
// dst_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR1_DST_BURST_LEN_MASK       0x3C0000
#define GDMAC_GDT1_CCR1_DST_BURST_LEN_SHIFT      18 
#define GDMAC_GDT1_CCR1_DST_BURST_LEN_BIT        0xF
#define GDMAC_GDT1_CCR1_DST_BURST_LEN_BITWIDTH   4
// dst_prot_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR1_DST_PROT_CTRL_MASK       0x1C00000
#define GDMAC_GDT1_CCR1_DST_PROT_CTRL_SHIFT      22 
#define GDMAC_GDT1_CCR1_DST_PROT_CTRL_BIT        0x7
#define GDMAC_GDT1_CCR1_DST_PROT_CTRL_BITWIDTH   3
// dst_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR1_DST_CACHE_CTRL_MASK      0xE000000
#define GDMAC_GDT1_CCR1_DST_CACHE_CTRL_SHIFT     25 
#define GDMAC_GDT1_CCR1_DST_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT1_CCR1_DST_CACHE_CTRL_BITWIDTH  3
// endian_swap_size bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR1_ENDIAN_SWAP_SIZE_MASK    0x70000000
#define GDMAC_GDT1_CCR1_ENDIAN_SWAP_SIZE_SHIFT   28 
#define GDMAC_GDT1_CCR1_ENDIAN_SWAP_SIZE_BIT     0x7
#define GDMAC_GDT1_CCR1_ENDIAN_SWAP_SIZE_BITWIDTH 3
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR1_RESERVED_MASK            0x80000000
#define GDMAC_GDT1_CCR1_RESERVED_SHIFT           31 
#define GDMAC_GDT1_CCR1_RESERVED_BIT             0x1
#define GDMAC_GDT1_CCR1_RESERVED_BITWIDTH        1
// GDT1_LC0_1 Register
#define GDMAC_GDT1_LC0_1_OFS                     0x0000142C
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC0_1_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT1_LC0_1_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT1_LC0_1_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT1_LC0_1_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC0_1_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT1_LC0_1_RESERVED_SHIFT          8 
#define GDMAC_GDT1_LC0_1_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT1_LC0_1_RESERVED_BITWIDTH       24
// GDT1_LC1_1 Register
#define GDMAC_GDT1_LC1_1_OFS                     0x00001430
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC1_1_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT1_LC1_1_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT1_LC1_1_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT1_LC1_1_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC1_1_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT1_LC1_1_RESERVED_SHIFT          8 
#define GDMAC_GDT1_LC1_1_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT1_LC1_1_RESERVED_BITWIDTH       24
// GDT1_SAR2 Register
#define GDMAC_GDT1_SAR2_OFS                      0x00001440
// src_addr bitfiled (RO) Reset=0
#define GDMAC_GDT1_SAR2_SRC_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT1_SAR2_SRC_ADDR_SHIFT           0 
#define GDMAC_GDT1_SAR2_SRC_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT1_SAR2_SRC_ADDR_BITWIDTH        32
// GDT1_DAR2 Register
#define GDMAC_GDT1_DAR2_OFS                      0x00001444
// dst_addr bitfiled (RO) Reset=0
#define GDMAC_GDT1_DAR2_DST_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT1_DAR2_DST_ADDR_SHIFT           0 
#define GDMAC_GDT1_DAR2_DST_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT1_DAR2_DST_ADDR_BITWIDTH        32
// GDT1_CCR2 Register
#define GDMAC_GDT1_CCR2_OFS                      0x00001448
// src_inc bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR2_SRC_INC_MASK             0x1
#define GDMAC_GDT1_CCR2_SRC_INC_SHIFT            0 
#define GDMAC_GDT1_CCR2_SRC_INC_BIT              0x1
#define GDMAC_GDT1_CCR2_SRC_INC_BITWIDTH         1
// src_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR2_SRC_BURST_SIZE_MASK      0xE
#define GDMAC_GDT1_CCR2_SRC_BURST_SIZE_SHIFT     1 
#define GDMAC_GDT1_CCR2_SRC_BURST_SIZE_BIT       0x7
#define GDMAC_GDT1_CCR2_SRC_BURST_SIZE_BITWIDTH  3
// src_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR2_SRC_BURST_LEN_MASK       0xF0
#define GDMAC_GDT1_CCR2_SRC_BURST_LEN_SHIFT      4 
#define GDMAC_GDT1_CCR2_SRC_BURST_LEN_BIT        0xF
#define GDMAC_GDT1_CCR2_SRC_BURST_LEN_BITWIDTH   4
// src_prot_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR2_SRC_PROT_CTRL_MASK       0x700
#define GDMAC_GDT1_CCR2_SRC_PROT_CTRL_SHIFT      8 
#define GDMAC_GDT1_CCR2_SRC_PROT_CTRL_BIT        0x7
#define GDMAC_GDT1_CCR2_SRC_PROT_CTRL_BITWIDTH   3
// src_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR2_SRC_CACHE_CTRL_MASK      0x3800
#define GDMAC_GDT1_CCR2_SRC_CACHE_CTRL_SHIFT     11 
#define GDMAC_GDT1_CCR2_SRC_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT1_CCR2_SRC_CACHE_CTRL_BITWIDTH  3
// dst_inc bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR2_DST_INC_MASK             0x4000
#define GDMAC_GDT1_CCR2_DST_INC_SHIFT            14 
#define GDMAC_GDT1_CCR2_DST_INC_BIT              0x1
#define GDMAC_GDT1_CCR2_DST_INC_BITWIDTH         1
// dst_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR2_DST_BURST_SIZE_MASK      0x38000
#define GDMAC_GDT1_CCR2_DST_BURST_SIZE_SHIFT     15 
#define GDMAC_GDT1_CCR2_DST_BURST_SIZE_BIT       0x7
#define GDMAC_GDT1_CCR2_DST_BURST_SIZE_BITWIDTH  3
// dst_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR2_DST_BURST_LEN_MASK       0x3C0000
#define GDMAC_GDT1_CCR2_DST_BURST_LEN_SHIFT      18 
#define GDMAC_GDT1_CCR2_DST_BURST_LEN_BIT        0xF
#define GDMAC_GDT1_CCR2_DST_BURST_LEN_BITWIDTH   4
// dst_prot_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR2_DST_PROT_CTRL_MASK       0x1C00000
#define GDMAC_GDT1_CCR2_DST_PROT_CTRL_SHIFT      22 
#define GDMAC_GDT1_CCR2_DST_PROT_CTRL_BIT        0x7
#define GDMAC_GDT1_CCR2_DST_PROT_CTRL_BITWIDTH   3
// dst_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR2_DST_CACHE_CTRL_MASK      0xE000000
#define GDMAC_GDT1_CCR2_DST_CACHE_CTRL_SHIFT     25 
#define GDMAC_GDT1_CCR2_DST_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT1_CCR2_DST_CACHE_CTRL_BITWIDTH  3
// endian_swap_size bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR2_ENDIAN_SWAP_SIZE_MASK    0x70000000
#define GDMAC_GDT1_CCR2_ENDIAN_SWAP_SIZE_SHIFT   28 
#define GDMAC_GDT1_CCR2_ENDIAN_SWAP_SIZE_BIT     0x7
#define GDMAC_GDT1_CCR2_ENDIAN_SWAP_SIZE_BITWIDTH 3
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR2_RESERVED_MASK            0x80000000
#define GDMAC_GDT1_CCR2_RESERVED_SHIFT           31 
#define GDMAC_GDT1_CCR2_RESERVED_BIT             0x1
#define GDMAC_GDT1_CCR2_RESERVED_BITWIDTH        1
// GDT1_LC0_2 Register
#define GDMAC_GDT1_LC0_2_OFS                     0x0000144C
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC0_2_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT1_LC0_2_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT1_LC0_2_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT1_LC0_2_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC0_2_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT1_LC0_2_RESERVED_SHIFT          8 
#define GDMAC_GDT1_LC0_2_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT1_LC0_2_RESERVED_BITWIDTH       24
// GDT1_LC1_2 Register
#define GDMAC_GDT1_LC1_2_OFS                     0x00001450
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC1_2_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT1_LC1_2_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT1_LC1_2_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT1_LC1_2_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC1_2_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT1_LC1_2_RESERVED_SHIFT          8 
#define GDMAC_GDT1_LC1_2_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT1_LC1_2_RESERVED_BITWIDTH       24
// GDT1_SAR3 Register
#define GDMAC_GDT1_SAR3_OFS                      0x00001460
// src_addr bitfiled (RO) Reset=0
#define GDMAC_GDT1_SAR3_SRC_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT1_SAR3_SRC_ADDR_SHIFT           0 
#define GDMAC_GDT1_SAR3_SRC_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT1_SAR3_SRC_ADDR_BITWIDTH        32
// GDT1_DAR3 Register
#define GDMAC_GDT1_DAR3_OFS                      0x00001464
// dst_addr bitfiled (RO) Reset=0
#define GDMAC_GDT1_DAR3_DST_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT1_DAR3_DST_ADDR_SHIFT           0 
#define GDMAC_GDT1_DAR3_DST_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT1_DAR3_DST_ADDR_BITWIDTH        32
// GDT1_CCR3 Register
#define GDMAC_GDT1_CCR3_OFS                      0x00001468
// src_inc bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR3_SRC_INC_MASK             0x1
#define GDMAC_GDT1_CCR3_SRC_INC_SHIFT            0 
#define GDMAC_GDT1_CCR3_SRC_INC_BIT              0x1
#define GDMAC_GDT1_CCR3_SRC_INC_BITWIDTH         1
// src_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR3_SRC_BURST_SIZE_MASK      0xE
#define GDMAC_GDT1_CCR3_SRC_BURST_SIZE_SHIFT     1 
#define GDMAC_GDT1_CCR3_SRC_BURST_SIZE_BIT       0x7
#define GDMAC_GDT1_CCR3_SRC_BURST_SIZE_BITWIDTH  3
// src_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR3_SRC_BURST_LEN_MASK       0xF0
#define GDMAC_GDT1_CCR3_SRC_BURST_LEN_SHIFT      4 
#define GDMAC_GDT1_CCR3_SRC_BURST_LEN_BIT        0xF
#define GDMAC_GDT1_CCR3_SRC_BURST_LEN_BITWIDTH   4
// src_prot_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR3_SRC_PROT_CTRL_MASK       0x700
#define GDMAC_GDT1_CCR3_SRC_PROT_CTRL_SHIFT      8 
#define GDMAC_GDT1_CCR3_SRC_PROT_CTRL_BIT        0x7
#define GDMAC_GDT1_CCR3_SRC_PROT_CTRL_BITWIDTH   3
// src_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR3_SRC_CACHE_CTRL_MASK      0x3800
#define GDMAC_GDT1_CCR3_SRC_CACHE_CTRL_SHIFT     11 
#define GDMAC_GDT1_CCR3_SRC_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT1_CCR3_SRC_CACHE_CTRL_BITWIDTH  3
// dst_inc bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR3_DST_INC_MASK             0x4000
#define GDMAC_GDT1_CCR3_DST_INC_SHIFT            14 
#define GDMAC_GDT1_CCR3_DST_INC_BIT              0x1
#define GDMAC_GDT1_CCR3_DST_INC_BITWIDTH         1
// dst_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR3_DST_BURST_SIZE_MASK      0x38000
#define GDMAC_GDT1_CCR3_DST_BURST_SIZE_SHIFT     15 
#define GDMAC_GDT1_CCR3_DST_BURST_SIZE_BIT       0x7
#define GDMAC_GDT1_CCR3_DST_BURST_SIZE_BITWIDTH  3
// dst_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR3_DST_BURST_LEN_MASK       0x3C0000
#define GDMAC_GDT1_CCR3_DST_BURST_LEN_SHIFT      18 
#define GDMAC_GDT1_CCR3_DST_BURST_LEN_BIT        0xF
#define GDMAC_GDT1_CCR3_DST_BURST_LEN_BITWIDTH   4
// dst_prot_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR3_DST_PROT_CTRL_MASK       0x1C00000
#define GDMAC_GDT1_CCR3_DST_PROT_CTRL_SHIFT      22 
#define GDMAC_GDT1_CCR3_DST_PROT_CTRL_BIT        0x7
#define GDMAC_GDT1_CCR3_DST_PROT_CTRL_BITWIDTH   3
// dst_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR3_DST_CACHE_CTRL_MASK      0xE000000
#define GDMAC_GDT1_CCR3_DST_CACHE_CTRL_SHIFT     25 
#define GDMAC_GDT1_CCR3_DST_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT1_CCR3_DST_CACHE_CTRL_BITWIDTH  3
// endian_swap_size bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR3_ENDIAN_SWAP_SIZE_MASK    0x70000000
#define GDMAC_GDT1_CCR3_ENDIAN_SWAP_SIZE_SHIFT   28 
#define GDMAC_GDT1_CCR3_ENDIAN_SWAP_SIZE_BIT     0x7
#define GDMAC_GDT1_CCR3_ENDIAN_SWAP_SIZE_BITWIDTH 3
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR3_RESERVED_MASK            0x80000000
#define GDMAC_GDT1_CCR3_RESERVED_SHIFT           31 
#define GDMAC_GDT1_CCR3_RESERVED_BIT             0x1
#define GDMAC_GDT1_CCR3_RESERVED_BITWIDTH        1
// GDT1_LC0_3 Register
#define GDMAC_GDT1_LC0_3_OFS                     0x0000146C
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC0_3_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT1_LC0_3_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT1_LC0_3_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT1_LC0_3_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC0_3_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT1_LC0_3_RESERVED_SHIFT          8 
#define GDMAC_GDT1_LC0_3_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT1_LC0_3_RESERVED_BITWIDTH       24
// GDT1_LC1_3 Register
#define GDMAC_GDT1_LC1_3_OFS                     0x00001470
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC1_3_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT1_LC1_3_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT1_LC1_3_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT1_LC1_3_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC1_3_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT1_LC1_3_RESERVED_SHIFT          8 
#define GDMAC_GDT1_LC1_3_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT1_LC1_3_RESERVED_BITWIDTH       24
// GDT1_SAR4 Register
#define GDMAC_GDT1_SAR4_OFS                      0x00001480
// src_addr bitfiled (RO) Reset=0
#define GDMAC_GDT1_SAR4_SRC_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT1_SAR4_SRC_ADDR_SHIFT           0 
#define GDMAC_GDT1_SAR4_SRC_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT1_SAR4_SRC_ADDR_BITWIDTH        32
// GDT1_DAR4 Register
#define GDMAC_GDT1_DAR4_OFS                      0x00001484
// dst_addr bitfiled (RO) Reset=0
#define GDMAC_GDT1_DAR4_DST_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT1_DAR4_DST_ADDR_SHIFT           0 
#define GDMAC_GDT1_DAR4_DST_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT1_DAR4_DST_ADDR_BITWIDTH        32
// GDT1_CCR4 Register
#define GDMAC_GDT1_CCR4_OFS                      0x00001488
// src_inc bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR4_SRC_INC_MASK             0x1
#define GDMAC_GDT1_CCR4_SRC_INC_SHIFT            0 
#define GDMAC_GDT1_CCR4_SRC_INC_BIT              0x1
#define GDMAC_GDT1_CCR4_SRC_INC_BITWIDTH         1
// src_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR4_SRC_BURST_SIZE_MASK      0xE
#define GDMAC_GDT1_CCR4_SRC_BURST_SIZE_SHIFT     1 
#define GDMAC_GDT1_CCR4_SRC_BURST_SIZE_BIT       0x7
#define GDMAC_GDT1_CCR4_SRC_BURST_SIZE_BITWIDTH  3
// src_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR4_SRC_BURST_LEN_MASK       0xF0
#define GDMAC_GDT1_CCR4_SRC_BURST_LEN_SHIFT      4 
#define GDMAC_GDT1_CCR4_SRC_BURST_LEN_BIT        0xF
#define GDMAC_GDT1_CCR4_SRC_BURST_LEN_BITWIDTH   4
// src_prot_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR4_SRC_PROT_CTRL_MASK       0x700
#define GDMAC_GDT1_CCR4_SRC_PROT_CTRL_SHIFT      8 
#define GDMAC_GDT1_CCR4_SRC_PROT_CTRL_BIT        0x7
#define GDMAC_GDT1_CCR4_SRC_PROT_CTRL_BITWIDTH   3
// src_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR4_SRC_CACHE_CTRL_MASK      0x3800
#define GDMAC_GDT1_CCR4_SRC_CACHE_CTRL_SHIFT     11 
#define GDMAC_GDT1_CCR4_SRC_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT1_CCR4_SRC_CACHE_CTRL_BITWIDTH  3
// dst_inc bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR4_DST_INC_MASK             0x4000
#define GDMAC_GDT1_CCR4_DST_INC_SHIFT            14 
#define GDMAC_GDT1_CCR4_DST_INC_BIT              0x1
#define GDMAC_GDT1_CCR4_DST_INC_BITWIDTH         1
// dst_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR4_DST_BURST_SIZE_MASK      0x38000
#define GDMAC_GDT1_CCR4_DST_BURST_SIZE_SHIFT     15 
#define GDMAC_GDT1_CCR4_DST_BURST_SIZE_BIT       0x7
#define GDMAC_GDT1_CCR4_DST_BURST_SIZE_BITWIDTH  3
// dst_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR4_DST_BURST_LEN_MASK       0x3C0000
#define GDMAC_GDT1_CCR4_DST_BURST_LEN_SHIFT      18 
#define GDMAC_GDT1_CCR4_DST_BURST_LEN_BIT        0xF
#define GDMAC_GDT1_CCR4_DST_BURST_LEN_BITWIDTH   4
// dst_prot_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR4_DST_PROT_CTRL_MASK       0x1C00000
#define GDMAC_GDT1_CCR4_DST_PROT_CTRL_SHIFT      22 
#define GDMAC_GDT1_CCR4_DST_PROT_CTRL_BIT        0x7
#define GDMAC_GDT1_CCR4_DST_PROT_CTRL_BITWIDTH   3
// dst_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR4_DST_CACHE_CTRL_MASK      0xE000000
#define GDMAC_GDT1_CCR4_DST_CACHE_CTRL_SHIFT     25 
#define GDMAC_GDT1_CCR4_DST_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT1_CCR4_DST_CACHE_CTRL_BITWIDTH  3
// endian_swap_size bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR4_ENDIAN_SWAP_SIZE_MASK    0x70000000
#define GDMAC_GDT1_CCR4_ENDIAN_SWAP_SIZE_SHIFT   28 
#define GDMAC_GDT1_CCR4_ENDIAN_SWAP_SIZE_BIT     0x7
#define GDMAC_GDT1_CCR4_ENDIAN_SWAP_SIZE_BITWIDTH 3
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR4_RESERVED_MASK            0x80000000
#define GDMAC_GDT1_CCR4_RESERVED_SHIFT           31 
#define GDMAC_GDT1_CCR4_RESERVED_BIT             0x1
#define GDMAC_GDT1_CCR4_RESERVED_BITWIDTH        1
// GDT1_LC0_4 Register
#define GDMAC_GDT1_LC0_4_OFS                     0x0000148C
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC0_4_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT1_LC0_4_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT1_LC0_4_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT1_LC0_4_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC0_4_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT1_LC0_4_RESERVED_SHIFT          8 
#define GDMAC_GDT1_LC0_4_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT1_LC0_4_RESERVED_BITWIDTH       24
// GDT1_LC1_4 Register
#define GDMAC_GDT1_LC1_4_OFS                     0x00001490
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC1_4_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT1_LC1_4_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT1_LC1_4_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT1_LC1_4_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC1_4_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT1_LC1_4_RESERVED_SHIFT          8 
#define GDMAC_GDT1_LC1_4_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT1_LC1_4_RESERVED_BITWIDTH       24
// GDT1_SAR5 Register
#define GDMAC_GDT1_SAR5_OFS                      0x000014A0
// src_addr bitfiled (RO) Reset=0
#define GDMAC_GDT1_SAR5_SRC_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT1_SAR5_SRC_ADDR_SHIFT           0 
#define GDMAC_GDT1_SAR5_SRC_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT1_SAR5_SRC_ADDR_BITWIDTH        32
// GDT1_DAR5 Register
#define GDMAC_GDT1_DAR5_OFS                      0x000014A4
// dst_addr bitfiled (RO) Reset=0
#define GDMAC_GDT1_DAR5_DST_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT1_DAR5_DST_ADDR_SHIFT           0 
#define GDMAC_GDT1_DAR5_DST_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT1_DAR5_DST_ADDR_BITWIDTH        32
// GDT1_CCR5 Register
#define GDMAC_GDT1_CCR5_OFS                      0x000014A8
// src_inc bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR5_SRC_INC_MASK             0x1
#define GDMAC_GDT1_CCR5_SRC_INC_SHIFT            0 
#define GDMAC_GDT1_CCR5_SRC_INC_BIT              0x1
#define GDMAC_GDT1_CCR5_SRC_INC_BITWIDTH         1
// src_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR5_SRC_BURST_SIZE_MASK      0xE
#define GDMAC_GDT1_CCR5_SRC_BURST_SIZE_SHIFT     1 
#define GDMAC_GDT1_CCR5_SRC_BURST_SIZE_BIT       0x7
#define GDMAC_GDT1_CCR5_SRC_BURST_SIZE_BITWIDTH  3
// src_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR5_SRC_BURST_LEN_MASK       0xF0
#define GDMAC_GDT1_CCR5_SRC_BURST_LEN_SHIFT      4 
#define GDMAC_GDT1_CCR5_SRC_BURST_LEN_BIT        0xF
#define GDMAC_GDT1_CCR5_SRC_BURST_LEN_BITWIDTH   4
// src_prot_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR5_SRC_PROT_CTRL_MASK       0x700
#define GDMAC_GDT1_CCR5_SRC_PROT_CTRL_SHIFT      8 
#define GDMAC_GDT1_CCR5_SRC_PROT_CTRL_BIT        0x7
#define GDMAC_GDT1_CCR5_SRC_PROT_CTRL_BITWIDTH   3
// src_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR5_SRC_CACHE_CTRL_MASK      0x3800
#define GDMAC_GDT1_CCR5_SRC_CACHE_CTRL_SHIFT     11 
#define GDMAC_GDT1_CCR5_SRC_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT1_CCR5_SRC_CACHE_CTRL_BITWIDTH  3
// dst_inc bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR5_DST_INC_MASK             0x4000
#define GDMAC_GDT1_CCR5_DST_INC_SHIFT            14 
#define GDMAC_GDT1_CCR5_DST_INC_BIT              0x1
#define GDMAC_GDT1_CCR5_DST_INC_BITWIDTH         1
// dst_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR5_DST_BURST_SIZE_MASK      0x38000
#define GDMAC_GDT1_CCR5_DST_BURST_SIZE_SHIFT     15 
#define GDMAC_GDT1_CCR5_DST_BURST_SIZE_BIT       0x7
#define GDMAC_GDT1_CCR5_DST_BURST_SIZE_BITWIDTH  3
// dst_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR5_DST_BURST_LEN_MASK       0x3C0000
#define GDMAC_GDT1_CCR5_DST_BURST_LEN_SHIFT      18 
#define GDMAC_GDT1_CCR5_DST_BURST_LEN_BIT        0xF
#define GDMAC_GDT1_CCR5_DST_BURST_LEN_BITWIDTH   4
// dst_prot_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR5_DST_PROT_CTRL_MASK       0x1C00000
#define GDMAC_GDT1_CCR5_DST_PROT_CTRL_SHIFT      22 
#define GDMAC_GDT1_CCR5_DST_PROT_CTRL_BIT        0x7
#define GDMAC_GDT1_CCR5_DST_PROT_CTRL_BITWIDTH   3
// dst_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR5_DST_CACHE_CTRL_MASK      0xE000000
#define GDMAC_GDT1_CCR5_DST_CACHE_CTRL_SHIFT     25 
#define GDMAC_GDT1_CCR5_DST_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT1_CCR5_DST_CACHE_CTRL_BITWIDTH  3
// endian_swap_size bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR5_ENDIAN_SWAP_SIZE_MASK    0x70000000
#define GDMAC_GDT1_CCR5_ENDIAN_SWAP_SIZE_SHIFT   28 
#define GDMAC_GDT1_CCR5_ENDIAN_SWAP_SIZE_BIT     0x7
#define GDMAC_GDT1_CCR5_ENDIAN_SWAP_SIZE_BITWIDTH 3
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR5_RESERVED_MASK            0x80000000
#define GDMAC_GDT1_CCR5_RESERVED_SHIFT           31 
#define GDMAC_GDT1_CCR5_RESERVED_BIT             0x1
#define GDMAC_GDT1_CCR5_RESERVED_BITWIDTH        1
// GDT1_LC0_5 Register
#define GDMAC_GDT1_LC0_5_OFS                     0x000014AC
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC0_5_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT1_LC0_5_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT1_LC0_5_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT1_LC0_5_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC0_5_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT1_LC0_5_RESERVED_SHIFT          8 
#define GDMAC_GDT1_LC0_5_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT1_LC0_5_RESERVED_BITWIDTH       24
// GDT1_LC1_5 Register
#define GDMAC_GDT1_LC1_5_OFS                     0x000014B0
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC1_5_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT1_LC1_5_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT1_LC1_5_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT1_LC1_5_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC1_5_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT1_LC1_5_RESERVED_SHIFT          8 
#define GDMAC_GDT1_LC1_5_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT1_LC1_5_RESERVED_BITWIDTH       24
// GDT1_SAR6 Register
#define GDMAC_GDT1_SAR6_OFS                      0x000014C0
// src_addr bitfiled (RO) Reset=0
#define GDMAC_GDT1_SAR6_SRC_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT1_SAR6_SRC_ADDR_SHIFT           0 
#define GDMAC_GDT1_SAR6_SRC_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT1_SAR6_SRC_ADDR_BITWIDTH        32
// GDT1_DAR6 Register
#define GDMAC_GDT1_DAR6_OFS                      0x000014C4
// dst_addr bitfiled (RO) Reset=0
#define GDMAC_GDT1_DAR6_DST_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT1_DAR6_DST_ADDR_SHIFT           0 
#define GDMAC_GDT1_DAR6_DST_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT1_DAR6_DST_ADDR_BITWIDTH        32
// GDT1_CCR6 Register
#define GDMAC_GDT1_CCR6_OFS                      0x000014C8
// src_inc bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR6_SRC_INC_MASK             0x1
#define GDMAC_GDT1_CCR6_SRC_INC_SHIFT            0 
#define GDMAC_GDT1_CCR6_SRC_INC_BIT              0x1
#define GDMAC_GDT1_CCR6_SRC_INC_BITWIDTH         1
// src_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR6_SRC_BURST_SIZE_MASK      0xE
#define GDMAC_GDT1_CCR6_SRC_BURST_SIZE_SHIFT     1 
#define GDMAC_GDT1_CCR6_SRC_BURST_SIZE_BIT       0x7
#define GDMAC_GDT1_CCR6_SRC_BURST_SIZE_BITWIDTH  3
// src_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR6_SRC_BURST_LEN_MASK       0xF0
#define GDMAC_GDT1_CCR6_SRC_BURST_LEN_SHIFT      4 
#define GDMAC_GDT1_CCR6_SRC_BURST_LEN_BIT        0xF
#define GDMAC_GDT1_CCR6_SRC_BURST_LEN_BITWIDTH   4
// src_prot_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR6_SRC_PROT_CTRL_MASK       0x700
#define GDMAC_GDT1_CCR6_SRC_PROT_CTRL_SHIFT      8 
#define GDMAC_GDT1_CCR6_SRC_PROT_CTRL_BIT        0x7
#define GDMAC_GDT1_CCR6_SRC_PROT_CTRL_BITWIDTH   3
// src_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR6_SRC_CACHE_CTRL_MASK      0x3800
#define GDMAC_GDT1_CCR6_SRC_CACHE_CTRL_SHIFT     11 
#define GDMAC_GDT1_CCR6_SRC_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT1_CCR6_SRC_CACHE_CTRL_BITWIDTH  3
// dst_inc bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR6_DST_INC_MASK             0x4000
#define GDMAC_GDT1_CCR6_DST_INC_SHIFT            14 
#define GDMAC_GDT1_CCR6_DST_INC_BIT              0x1
#define GDMAC_GDT1_CCR6_DST_INC_BITWIDTH         1
// dst_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR6_DST_BURST_SIZE_MASK      0x38000
#define GDMAC_GDT1_CCR6_DST_BURST_SIZE_SHIFT     15 
#define GDMAC_GDT1_CCR6_DST_BURST_SIZE_BIT       0x7
#define GDMAC_GDT1_CCR6_DST_BURST_SIZE_BITWIDTH  3
// dst_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR6_DST_BURST_LEN_MASK       0x3C0000
#define GDMAC_GDT1_CCR6_DST_BURST_LEN_SHIFT      18 
#define GDMAC_GDT1_CCR6_DST_BURST_LEN_BIT        0xF
#define GDMAC_GDT1_CCR6_DST_BURST_LEN_BITWIDTH   4
// dst_prot_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR6_DST_PROT_CTRL_MASK       0x1C00000
#define GDMAC_GDT1_CCR6_DST_PROT_CTRL_SHIFT      22 
#define GDMAC_GDT1_CCR6_DST_PROT_CTRL_BIT        0x7
#define GDMAC_GDT1_CCR6_DST_PROT_CTRL_BITWIDTH   3
// dst_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR6_DST_CACHE_CTRL_MASK      0xE000000
#define GDMAC_GDT1_CCR6_DST_CACHE_CTRL_SHIFT     25 
#define GDMAC_GDT1_CCR6_DST_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT1_CCR6_DST_CACHE_CTRL_BITWIDTH  3
// endian_swap_size bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR6_ENDIAN_SWAP_SIZE_MASK    0x70000000
#define GDMAC_GDT1_CCR6_ENDIAN_SWAP_SIZE_SHIFT   28 
#define GDMAC_GDT1_CCR6_ENDIAN_SWAP_SIZE_BIT     0x7
#define GDMAC_GDT1_CCR6_ENDIAN_SWAP_SIZE_BITWIDTH 3
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR6_RESERVED_MASK            0x80000000
#define GDMAC_GDT1_CCR6_RESERVED_SHIFT           31 
#define GDMAC_GDT1_CCR6_RESERVED_BIT             0x1
#define GDMAC_GDT1_CCR6_RESERVED_BITWIDTH        1
// GDT1_LC0_6 Register
#define GDMAC_GDT1_LC0_6_OFS                     0x000014CC
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC0_6_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT1_LC0_6_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT1_LC0_6_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT1_LC0_6_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC0_6_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT1_LC0_6_RESERVED_SHIFT          8 
#define GDMAC_GDT1_LC0_6_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT1_LC0_6_RESERVED_BITWIDTH       24
// GDT1_LC1_6 Register
#define GDMAC_GDT1_LC1_6_OFS                     0x000014D0
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC1_6_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT1_LC1_6_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT1_LC1_6_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT1_LC1_6_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC1_6_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT1_LC1_6_RESERVED_SHIFT          8 
#define GDMAC_GDT1_LC1_6_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT1_LC1_6_RESERVED_BITWIDTH       24
// GDT1_SAR7 Register
#define GDMAC_GDT1_SAR7_OFS                      0x000014E0
// src_addr bitfiled (RO) Reset=0
#define GDMAC_GDT1_SAR7_SRC_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT1_SAR7_SRC_ADDR_SHIFT           0 
#define GDMAC_GDT1_SAR7_SRC_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT1_SAR7_SRC_ADDR_BITWIDTH        32
// GDT1_DAR7 Register
#define GDMAC_GDT1_DAR7_OFS                      0x000014E4
// dst_addr bitfiled (RO) Reset=0
#define GDMAC_GDT1_DAR7_DST_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT1_DAR7_DST_ADDR_SHIFT           0 
#define GDMAC_GDT1_DAR7_DST_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT1_DAR7_DST_ADDR_BITWIDTH        32
// GDT1_CCR7 Register
#define GDMAC_GDT1_CCR7_OFS                      0x000014E8
// src_inc bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR7_SRC_INC_MASK             0x1
#define GDMAC_GDT1_CCR7_SRC_INC_SHIFT            0 
#define GDMAC_GDT1_CCR7_SRC_INC_BIT              0x1
#define GDMAC_GDT1_CCR7_SRC_INC_BITWIDTH         1
// src_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR7_SRC_BURST_SIZE_MASK      0xE
#define GDMAC_GDT1_CCR7_SRC_BURST_SIZE_SHIFT     1 
#define GDMAC_GDT1_CCR7_SRC_BURST_SIZE_BIT       0x7
#define GDMAC_GDT1_CCR7_SRC_BURST_SIZE_BITWIDTH  3
// src_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR7_SRC_BURST_LEN_MASK       0xF0
#define GDMAC_GDT1_CCR7_SRC_BURST_LEN_SHIFT      4 
#define GDMAC_GDT1_CCR7_SRC_BURST_LEN_BIT        0xF
#define GDMAC_GDT1_CCR7_SRC_BURST_LEN_BITWIDTH   4
// src_prot_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR7_SRC_PROT_CTRL_MASK       0x700
#define GDMAC_GDT1_CCR7_SRC_PROT_CTRL_SHIFT      8 
#define GDMAC_GDT1_CCR7_SRC_PROT_CTRL_BIT        0x7
#define GDMAC_GDT1_CCR7_SRC_PROT_CTRL_BITWIDTH   3
// src_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR7_SRC_CACHE_CTRL_MASK      0x3800
#define GDMAC_GDT1_CCR7_SRC_CACHE_CTRL_SHIFT     11 
#define GDMAC_GDT1_CCR7_SRC_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT1_CCR7_SRC_CACHE_CTRL_BITWIDTH  3
// dst_inc bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR7_DST_INC_MASK             0x4000
#define GDMAC_GDT1_CCR7_DST_INC_SHIFT            14 
#define GDMAC_GDT1_CCR7_DST_INC_BIT              0x1
#define GDMAC_GDT1_CCR7_DST_INC_BITWIDTH         1
// dst_burst_size bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR7_DST_BURST_SIZE_MASK      0x38000
#define GDMAC_GDT1_CCR7_DST_BURST_SIZE_SHIFT     15 
#define GDMAC_GDT1_CCR7_DST_BURST_SIZE_BIT       0x7
#define GDMAC_GDT1_CCR7_DST_BURST_SIZE_BITWIDTH  3
// dst_burst_len bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR7_DST_BURST_LEN_MASK       0x3C0000
#define GDMAC_GDT1_CCR7_DST_BURST_LEN_SHIFT      18 
#define GDMAC_GDT1_CCR7_DST_BURST_LEN_BIT        0xF
#define GDMAC_GDT1_CCR7_DST_BURST_LEN_BITWIDTH   4
// dst_prot_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR7_DST_PROT_CTRL_MASK       0x1C00000
#define GDMAC_GDT1_CCR7_DST_PROT_CTRL_SHIFT      22 
#define GDMAC_GDT1_CCR7_DST_PROT_CTRL_BIT        0x7
#define GDMAC_GDT1_CCR7_DST_PROT_CTRL_BITWIDTH   3
// dst_cache_ctrl bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR7_DST_CACHE_CTRL_MASK      0xE000000
#define GDMAC_GDT1_CCR7_DST_CACHE_CTRL_SHIFT     25 
#define GDMAC_GDT1_CCR7_DST_CACHE_CTRL_BIT       0x7
#define GDMAC_GDT1_CCR7_DST_CACHE_CTRL_BITWIDTH  3
// endian_swap_size bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR7_ENDIAN_SWAP_SIZE_MASK    0x70000000
#define GDMAC_GDT1_CCR7_ENDIAN_SWAP_SIZE_SHIFT   28 
#define GDMAC_GDT1_CCR7_ENDIAN_SWAP_SIZE_BIT     0x7
#define GDMAC_GDT1_CCR7_ENDIAN_SWAP_SIZE_BITWIDTH 3
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_CCR7_RESERVED_MASK            0x80000000
#define GDMAC_GDT1_CCR7_RESERVED_SHIFT           31 
#define GDMAC_GDT1_CCR7_RESERVED_BIT             0x1
#define GDMAC_GDT1_CCR7_RESERVED_BITWIDTH        1
// GDT1_LC0_7 Register
#define GDMAC_GDT1_LC0_7_OFS                     0x000014EC
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC0_7_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT1_LC0_7_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT1_LC0_7_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT1_LC0_7_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC0_7_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT1_LC0_7_RESERVED_SHIFT          8 
#define GDMAC_GDT1_LC0_7_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT1_LC0_7_RESERVED_BITWIDTH       24
// GDT1_LC1_7 Register
#define GDMAC_GDT1_LC1_7_OFS                     0x000014F0
// Loop_counter_iterations bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC1_7_LOOP_COUNTER_ITERATIONS_MASK 0xFF
#define GDMAC_GDT1_LC1_7_LOOP_COUNTER_ITERATIONS_SHIFT 0 
#define GDMAC_GDT1_LC1_7_LOOP_COUNTER_ITERATIONS_BIT 0xFF
#define GDMAC_GDT1_LC1_7_LOOP_COUNTER_ITERATIONS_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_LC1_7_RESERVED_MASK           0xFFFFFF00
#define GDMAC_GDT1_LC1_7_RESERVED_SHIFT          8 
#define GDMAC_GDT1_LC1_7_RESERVED_BIT            0xFFFFFF
#define GDMAC_GDT1_LC1_7_RESERVED_BITWIDTH       24
// GDT1_DBGSTATUS Register
#define GDMAC_GDT1_DBGSTATUS_OFS                 0x00001D00
// dbg_status bitfiled (RO) Reset=0
#define GDMAC_GDT1_DBGSTATUS_DBG_STATUS_MASK     0x1
#define GDMAC_GDT1_DBGSTATUS_DBG_STATUS_SHIFT    0 
#define GDMAC_GDT1_DBGSTATUS_DBG_STATUS_BIT      0x1
#define GDMAC_GDT1_DBGSTATUS_DBG_STATUS_BITWIDTH 1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_DBGSTATUS_RESERVED_MASK       0xFFFFFFFE
#define GDMAC_GDT1_DBGSTATUS_RESERVED_SHIFT      1 
#define GDMAC_GDT1_DBGSTATUS_RESERVED_BIT        0x7FFFFFFF
#define GDMAC_GDT1_DBGSTATUS_RESERVED_BITWIDTH   31
// GDT1_DBGCMD Register
#define GDMAC_GDT1_DBGCMD_OFS                    0x00001D04
// dbgcmd bitfiled (RW) Reset=0
#define GDMAC_GDT1_DBGCMD_DBGCMD_MASK            0x3
#define GDMAC_GDT1_DBGCMD_DBGCMD_SHIFT           0 
#define GDMAC_GDT1_DBGCMD_DBGCMD_BIT             0x3
#define GDMAC_GDT1_DBGCMD_DBGCMD_BITWIDTH        2
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_DBGCMD_RESERVED_MASK          0xFFFFFFFC
#define GDMAC_GDT1_DBGCMD_RESERVED_SHIFT         2 
#define GDMAC_GDT1_DBGCMD_RESERVED_BIT           0x3FFFFFFF
#define GDMAC_GDT1_DBGCMD_RESERVED_BITWIDTH      30
// GDT1_DBGINST0 Register
#define GDMAC_GDT1_DBGINST0_OFS                  0x00001D08
// Debug_thread bitfiled (RW) Reset=0
#define GDMAC_GDT1_DBGINST0_DEBUG_THREAD_MASK    0x1
#define GDMAC_GDT1_DBGINST0_DEBUG_THREAD_SHIFT   0 
#define GDMAC_GDT1_DBGINST0_DEBUG_THREAD_BIT     0x1
#define GDMAC_GDT1_DBGINST0_DEBUG_THREAD_BITWIDTH 1
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT1_DBGINST0_RESERVED2_MASK       0xFE
#define GDMAC_GDT1_DBGINST0_RESERVED2_SHIFT      1 
#define GDMAC_GDT1_DBGINST0_RESERVED2_BIT        0x7F
#define GDMAC_GDT1_DBGINST0_RESERVED2_BITWIDTH   7
// Channel_number bitfiled (RW) Reset=0
#define GDMAC_GDT1_DBGINST0_CHANNEL_NUMBER_MASK  0x700
#define GDMAC_GDT1_DBGINST0_CHANNEL_NUMBER_SHIFT 8 
#define GDMAC_GDT1_DBGINST0_CHANNEL_NUMBER_BIT   0x7
#define GDMAC_GDT1_DBGINST0_CHANNEL_NUMBER_BITWIDTH 3
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_DBGINST0_RESERVED_MASK        0xF800
#define GDMAC_GDT1_DBGINST0_RESERVED_SHIFT       11 
#define GDMAC_GDT1_DBGINST0_RESERVED_BIT         0x1F
#define GDMAC_GDT1_DBGINST0_RESERVED_BITWIDTH    5
// Instruction_byte_0 bitfiled (RW) Reset=0
#define GDMAC_GDT1_DBGINST0_INSTRUCTION_BYTE_0_MASK 0xFF0000
#define GDMAC_GDT1_DBGINST0_INSTRUCTION_BYTE_0_SHIFT 16 
#define GDMAC_GDT1_DBGINST0_INSTRUCTION_BYTE_0_BIT 0xFF
#define GDMAC_GDT1_DBGINST0_INSTRUCTION_BYTE_0_BITWIDTH 8
// Instruction_byte_1 bitfiled (RW) Reset=0
#define GDMAC_GDT1_DBGINST0_INSTRUCTION_BYTE_1_MASK 0xFF000000
#define GDMAC_GDT1_DBGINST0_INSTRUCTION_BYTE_1_SHIFT 24 
#define GDMAC_GDT1_DBGINST0_INSTRUCTION_BYTE_1_BIT 0xFF
#define GDMAC_GDT1_DBGINST0_INSTRUCTION_BYTE_1_BITWIDTH 8
// GDT1_DBGINST1 Register
#define GDMAC_GDT1_DBGINST1_OFS                  0x00001D0C
// Instruction_byte_2 bitfiled (RW) Reset=0
#define GDMAC_GDT1_DBGINST1_INSTRUCTION_BYTE_2_MASK 0xFF
#define GDMAC_GDT1_DBGINST1_INSTRUCTION_BYTE_2_SHIFT 0 
#define GDMAC_GDT1_DBGINST1_INSTRUCTION_BYTE_2_BIT 0xFF
#define GDMAC_GDT1_DBGINST1_INSTRUCTION_BYTE_2_BITWIDTH 8
// Instruction_byte_3 bitfiled (RW) Reset=0
#define GDMAC_GDT1_DBGINST1_INSTRUCTION_BYTE_3_MASK 0xFF00
#define GDMAC_GDT1_DBGINST1_INSTRUCTION_BYTE_3_SHIFT 8 
#define GDMAC_GDT1_DBGINST1_INSTRUCTION_BYTE_3_BIT 0xFF
#define GDMAC_GDT1_DBGINST1_INSTRUCTION_BYTE_3_BITWIDTH 8
// Instruction_byte_4 bitfiled (RW) Reset=0
#define GDMAC_GDT1_DBGINST1_INSTRUCTION_BYTE_4_MASK 0xFF0000
#define GDMAC_GDT1_DBGINST1_INSTRUCTION_BYTE_4_SHIFT 16 
#define GDMAC_GDT1_DBGINST1_INSTRUCTION_BYTE_4_BIT 0xFF
#define GDMAC_GDT1_DBGINST1_INSTRUCTION_BYTE_4_BITWIDTH 8
// Instruction_byte_5 bitfiled (RW) Reset=0
#define GDMAC_GDT1_DBGINST1_INSTRUCTION_BYTE_5_MASK 0xFF000000
#define GDMAC_GDT1_DBGINST1_INSTRUCTION_BYTE_5_SHIFT 24 
#define GDMAC_GDT1_DBGINST1_INSTRUCTION_BYTE_5_BIT 0xFF
#define GDMAC_GDT1_DBGINST1_INSTRUCTION_BYTE_5_BITWIDTH 8
// GDT1_CR0 Register
#define GDMAC_GDT1_CR0_OFS                       0x00001E00
// periph_req bitfiled (RO) Reset=1
#define GDMAC_GDT1_CR0_PERIPH_REQ_MASK           0x1
#define GDMAC_GDT1_CR0_PERIPH_REQ_SHIFT          0 
#define GDMAC_GDT1_CR0_PERIPH_REQ_BIT            0x1
#define GDMAC_GDT1_CR0_PERIPH_REQ_BITWIDTH       1
// boot_en bitfiled (RO) Reset=0
#define GDMAC_GDT1_CR0_BOOT_EN_MASK              0x2
#define GDMAC_GDT1_CR0_BOOT_EN_SHIFT             1 
#define GDMAC_GDT1_CR0_BOOT_EN_BIT               0x1
#define GDMAC_GDT1_CR0_BOOT_EN_BITWIDTH          1
// mgr_ns_at_rst bitfiled (RO) Reset=1
#define GDMAC_GDT1_CR0_MGR_NS_AT_RST_MASK        0x4
#define GDMAC_GDT1_CR0_MGR_NS_AT_RST_SHIFT       2 
#define GDMAC_GDT1_CR0_MGR_NS_AT_RST_BIT         0x1
#define GDMAC_GDT1_CR0_MGR_NS_AT_RST_BITWIDTH    1
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT1_CR0_RESERVED3_MASK            0x8
#define GDMAC_GDT1_CR0_RESERVED3_SHIFT           3 
#define GDMAC_GDT1_CR0_RESERVED3_BIT             0x1
#define GDMAC_GDT1_CR0_RESERVED3_BITWIDTH        1
// num_chnls bitfiled (RO) Reset=111
#define GDMAC_GDT1_CR0_NUM_CHNLS_MASK            0x70
#define GDMAC_GDT1_CR0_NUM_CHNLS_SHIFT           4 
#define GDMAC_GDT1_CR0_NUM_CHNLS_BIT             0x7
#define GDMAC_GDT1_CR0_NUM_CHNLS_BITWIDTH        3
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT1_CR0_RESERVED2_MASK            0xF80
#define GDMAC_GDT1_CR0_RESERVED2_SHIFT           7 
#define GDMAC_GDT1_CR0_RESERVED2_BIT             0x1F
#define GDMAC_GDT1_CR0_RESERVED2_BITWIDTH        5
// num_periph_req bitfiled (RO) Reset=11111
#define GDMAC_GDT1_CR0_NUM_PERIPH_REQ_MASK       0x1F000
#define GDMAC_GDT1_CR0_NUM_PERIPH_REQ_SHIFT      12 
#define GDMAC_GDT1_CR0_NUM_PERIPH_REQ_BIT        0x1F
#define GDMAC_GDT1_CR0_NUM_PERIPH_REQ_BITWIDTH   5
// num_events bitfiled (RO) Reset=11111
#define GDMAC_GDT1_CR0_NUM_EVENTS_MASK           0x3E0000
#define GDMAC_GDT1_CR0_NUM_EVENTS_SHIFT          17 
#define GDMAC_GDT1_CR0_NUM_EVENTS_BIT            0x1F
#define GDMAC_GDT1_CR0_NUM_EVENTS_BITWIDTH       5
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_CR0_RESERVED_MASK             0xFFC00000
#define GDMAC_GDT1_CR0_RESERVED_SHIFT            22 
#define GDMAC_GDT1_CR0_RESERVED_BIT              0x3FF
#define GDMAC_GDT1_CR0_RESERVED_BITWIDTH         10
// GDT1_CR1 Register
#define GDMAC_GDT1_CR1_OFS                       0x00001E04
// i_cache_len bitfiled (RO) Reset=101
#define GDMAC_GDT1_CR1_I_CACHE_LEN_MASK          0x7
#define GDMAC_GDT1_CR1_I_CACHE_LEN_SHIFT         0 
#define GDMAC_GDT1_CR1_I_CACHE_LEN_BIT           0x7
#define GDMAC_GDT1_CR1_I_CACHE_LEN_BITWIDTH      3
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT1_CR1_RESERVED2_MASK            0x8
#define GDMAC_GDT1_CR1_RESERVED2_SHIFT           3 
#define GDMAC_GDT1_CR1_RESERVED2_BIT             0x1
#define GDMAC_GDT1_CR1_RESERVED2_BITWIDTH        1
// num_i_cache_lines bitfiled (RO) Reset=111
#define GDMAC_GDT1_CR1_NUM_I_CACHE_LINES_MASK    0xF0
#define GDMAC_GDT1_CR1_NUM_I_CACHE_LINES_SHIFT   4 
#define GDMAC_GDT1_CR1_NUM_I_CACHE_LINES_BIT     0xF
#define GDMAC_GDT1_CR1_NUM_I_CACHE_LINES_BITWIDTH 4
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_CR1_RESERVED_MASK             0xFFFFFF00
#define GDMAC_GDT1_CR1_RESERVED_SHIFT            8 
#define GDMAC_GDT1_CR1_RESERVED_BIT              0xFFFFFF
#define GDMAC_GDT1_CR1_RESERVED_BITWIDTH         24
// GDT1_CR2 Register
#define GDMAC_GDT1_CR2_OFS                       0x00001E08
// boot_addr bitfiled (RO) Reset=0
#define GDMAC_GDT1_CR2_BOOT_ADDR_MASK            0xFFFFFFFF
#define GDMAC_GDT1_CR2_BOOT_ADDR_SHIFT           0 
#define GDMAC_GDT1_CR2_BOOT_ADDR_BIT             0xFFFFFFFF
#define GDMAC_GDT1_CR2_BOOT_ADDR_BITWIDTH        32
// GDT1_CR3 Register
#define GDMAC_GDT1_CR3_OFS                       0x00001E0C
// INS bitfiled (RO) Reset=11111111111111111111111111111111
#define GDMAC_GDT1_CR3_INS_MASK                  0xFFFFFFFF
#define GDMAC_GDT1_CR3_INS_SHIFT                 0 
#define GDMAC_GDT1_CR3_INS_BIT                   0xFFFFFFFF
#define GDMAC_GDT1_CR3_INS_BITWIDTH              32
// GDT1_CR4 Register
#define GDMAC_GDT1_CR4_OFS                       0x00001E10
// PNS bitfiled (RO) Reset=11111111111111111111111111111111
#define GDMAC_GDT1_CR4_PNS_MASK                  0xFFFFFFFF
#define GDMAC_GDT1_CR4_PNS_SHIFT                 0 
#define GDMAC_GDT1_CR4_PNS_BIT                   0xFFFFFFFF
#define GDMAC_GDT1_CR4_PNS_BITWIDTH              32
// GDT1_CRD Register
#define GDMAC_GDT1_CRD_OFS                       0x00001E14
// data_width bitfiled (RO) Reset=11
#define GDMAC_GDT1_CRD_DATA_WIDTH_MASK           0x7
#define GDMAC_GDT1_CRD_DATA_WIDTH_SHIFT          0 
#define GDMAC_GDT1_CRD_DATA_WIDTH_BIT            0x7
#define GDMAC_GDT1_CRD_DATA_WIDTH_BITWIDTH       3
// reserved4 bitfiled (RO) Reset=0
#define GDMAC_GDT1_CRD_RESERVED4_MASK            0x8
#define GDMAC_GDT1_CRD_RESERVED4_SHIFT           3 
#define GDMAC_GDT1_CRD_RESERVED4_BIT             0x1
#define GDMAC_GDT1_CRD_RESERVED4_BITWIDTH        1
// wr_cap bitfiled (RO) Reset=11
#define GDMAC_GDT1_CRD_WR_CAP_MASK               0x70
#define GDMAC_GDT1_CRD_WR_CAP_SHIFT              4 
#define GDMAC_GDT1_CRD_WR_CAP_BIT                0x7
#define GDMAC_GDT1_CRD_WR_CAP_BITWIDTH           3
// reserved3 bitfiled (RO) Reset=0
#define GDMAC_GDT1_CRD_RESERVED3_MASK            0x80
#define GDMAC_GDT1_CRD_RESERVED3_SHIFT           7 
#define GDMAC_GDT1_CRD_RESERVED3_BIT             0x1
#define GDMAC_GDT1_CRD_RESERVED3_BITWIDTH        1
// wr_q_dep bitfiled (RO) Reset=111
#define GDMAC_GDT1_CRD_WR_Q_DEP_MASK             0xF00
#define GDMAC_GDT1_CRD_WR_Q_DEP_SHIFT            8 
#define GDMAC_GDT1_CRD_WR_Q_DEP_BIT              0xF
#define GDMAC_GDT1_CRD_WR_Q_DEP_BITWIDTH         4
// rd_cap bitfiled (RO) Reset=11
#define GDMAC_GDT1_CRD_RD_CAP_MASK               0x7000
#define GDMAC_GDT1_CRD_RD_CAP_SHIFT              12 
#define GDMAC_GDT1_CRD_RD_CAP_BIT                0x7
#define GDMAC_GDT1_CRD_RD_CAP_BITWIDTH           3
// reserved2 bitfiled (RO) Reset=0
#define GDMAC_GDT1_CRD_RESERVED2_MASK            0x8000
#define GDMAC_GDT1_CRD_RESERVED2_SHIFT           15 
#define GDMAC_GDT1_CRD_RESERVED2_BIT             0x1
#define GDMAC_GDT1_CRD_RESERVED2_BITWIDTH        1
// rd_q_dep bitfiled (RO) Reset=111
#define GDMAC_GDT1_CRD_RD_Q_DEP_MASK             0xF0000
#define GDMAC_GDT1_CRD_RD_Q_DEP_SHIFT            16 
#define GDMAC_GDT1_CRD_RD_Q_DEP_BIT              0xF
#define GDMAC_GDT1_CRD_RD_Q_DEP_BITWIDTH         4
// data_buffer_dep bitfiled (RO) Reset=11111
#define GDMAC_GDT1_CRD_DATA_BUFFER_DEP_MASK      0x3FF00000
#define GDMAC_GDT1_CRD_DATA_BUFFER_DEP_SHIFT     20 
#define GDMAC_GDT1_CRD_DATA_BUFFER_DEP_BIT       0x3FF
#define GDMAC_GDT1_CRD_DATA_BUFFER_DEP_BITWIDTH  10
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_CRD_RESERVED_MASK             0xC0000000
#define GDMAC_GDT1_CRD_RESERVED_SHIFT            30 
#define GDMAC_GDT1_CRD_RESERVED_BIT              0x3
#define GDMAC_GDT1_CRD_RESERVED_BITWIDTH         2
// GDT1_WD Register
#define GDMAC_GDT1_WD_OFS                        0x00001E80
// wd_irq_only bitfiled (RW) Reset=0
#define GDMAC_GDT1_WD_WD_IRQ_ONLY_MASK           0x1
#define GDMAC_GDT1_WD_WD_IRQ_ONLY_SHIFT          0 
#define GDMAC_GDT1_WD_WD_IRQ_ONLY_BIT            0x1
#define GDMAC_GDT1_WD_WD_IRQ_ONLY_BITWIDTH       1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_WD_RESERVED_MASK              0xFFFFFFFE
#define GDMAC_GDT1_WD_RESERVED_SHIFT             1 
#define GDMAC_GDT1_WD_RESERVED_BIT               0x7FFFFFFF
#define GDMAC_GDT1_WD_RESERVED_BITWIDTH          31
// GDT1_periph_id_0 Register
#define GDMAC_GDT1_PERIPH_ID_0_OFS               0x00001FE0
// part_number_0 bitfiled (RO) Reset=110000
#define GDMAC_GDT1_PERIPH_ID_0_PART_NUMBER_0_MASK 0xFF
#define GDMAC_GDT1_PERIPH_ID_0_PART_NUMBER_0_SHIFT 0 
#define GDMAC_GDT1_PERIPH_ID_0_PART_NUMBER_0_BIT 0xFF
#define GDMAC_GDT1_PERIPH_ID_0_PART_NUMBER_0_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_PERIPH_ID_0_RESERVED_MASK     0xFFFFFF00
#define GDMAC_GDT1_PERIPH_ID_0_RESERVED_SHIFT    8 
#define GDMAC_GDT1_PERIPH_ID_0_RESERVED_BIT      0xFFFFFF
#define GDMAC_GDT1_PERIPH_ID_0_RESERVED_BITWIDTH 24
// GDT1_periph_id_1 Register
#define GDMAC_GDT1_PERIPH_ID_1_OFS               0x00001FE4
// part_number_1 bitfiled (RO) Reset=11
#define GDMAC_GDT1_PERIPH_ID_1_PART_NUMBER_1_MASK 0xF
#define GDMAC_GDT1_PERIPH_ID_1_PART_NUMBER_1_SHIFT 0 
#define GDMAC_GDT1_PERIPH_ID_1_PART_NUMBER_1_BIT 0xF
#define GDMAC_GDT1_PERIPH_ID_1_PART_NUMBER_1_BITWIDTH 4
// designer_0 bitfiled (RO) Reset=1
#define GDMAC_GDT1_PERIPH_ID_1_DESIGNER_0_MASK   0xF0
#define GDMAC_GDT1_PERIPH_ID_1_DESIGNER_0_SHIFT  4 
#define GDMAC_GDT1_PERIPH_ID_1_DESIGNER_0_BIT    0xF
#define GDMAC_GDT1_PERIPH_ID_1_DESIGNER_0_BITWIDTH 4
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_PERIPH_ID_1_RESERVED_MASK     0xFFFFFF00
#define GDMAC_GDT1_PERIPH_ID_1_RESERVED_SHIFT    8 
#define GDMAC_GDT1_PERIPH_ID_1_RESERVED_BIT      0xFFFFFF
#define GDMAC_GDT1_PERIPH_ID_1_RESERVED_BITWIDTH 24
// GDT1_periph_id_2 Register
#define GDMAC_GDT1_PERIPH_ID_2_OFS               0x00001FE8
// designer_1 bitfiled (RO) Reset=100
#define GDMAC_GDT1_PERIPH_ID_2_DESIGNER_1_MASK   0xF
#define GDMAC_GDT1_PERIPH_ID_2_DESIGNER_1_SHIFT  0 
#define GDMAC_GDT1_PERIPH_ID_2_DESIGNER_1_BIT    0xF
#define GDMAC_GDT1_PERIPH_ID_2_DESIGNER_1_BITWIDTH 4
// revision bitfiled (RO) Reset=10
#define GDMAC_GDT1_PERIPH_ID_2_REVISION_MASK     0xF0
#define GDMAC_GDT1_PERIPH_ID_2_REVISION_SHIFT    4 
#define GDMAC_GDT1_PERIPH_ID_2_REVISION_BIT      0xF
#define GDMAC_GDT1_PERIPH_ID_2_REVISION_BITWIDTH 4
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_PERIPH_ID_2_RESERVED_MASK     0xFFFFFF00
#define GDMAC_GDT1_PERIPH_ID_2_RESERVED_SHIFT    8 
#define GDMAC_GDT1_PERIPH_ID_2_RESERVED_BIT      0xFFFFFF
#define GDMAC_GDT1_PERIPH_ID_2_RESERVED_BITWIDTH 24
// GDT1_periph_id_3 Register
#define GDMAC_GDT1_PERIPH_ID_3_OFS               0x00001FEC
// revision bitfiled (RO) Reset=0
#define GDMAC_GDT1_PERIPH_ID_3_REVISION_MASK     0x1
#define GDMAC_GDT1_PERIPH_ID_3_REVISION_SHIFT    0 
#define GDMAC_GDT1_PERIPH_ID_3_REVISION_BIT      0x1
#define GDMAC_GDT1_PERIPH_ID_3_REVISION_BITWIDTH 1
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_PERIPH_ID_3_RESERVED_MASK     0xFFFFFFFE
#define GDMAC_GDT1_PERIPH_ID_3_RESERVED_SHIFT    1 
#define GDMAC_GDT1_PERIPH_ID_3_RESERVED_BIT      0x7FFFFFFF
#define GDMAC_GDT1_PERIPH_ID_3_RESERVED_BITWIDTH 31
// GDT1_pcell_id_0 Register
#define GDMAC_GDT1_PCELL_ID_0_OFS                0x00001FF0
// pcell_id_0 bitfiled (RO) Reset=1101
#define GDMAC_GDT1_PCELL_ID_0_PCELL_ID_0_MASK    0xFF
#define GDMAC_GDT1_PCELL_ID_0_PCELL_ID_0_SHIFT   0 
#define GDMAC_GDT1_PCELL_ID_0_PCELL_ID_0_BIT     0xFF
#define GDMAC_GDT1_PCELL_ID_0_PCELL_ID_0_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_PCELL_ID_0_RESERVED_MASK      0xFFFFFF00
#define GDMAC_GDT1_PCELL_ID_0_RESERVED_SHIFT     8 
#define GDMAC_GDT1_PCELL_ID_0_RESERVED_BIT       0xFFFFFF
#define GDMAC_GDT1_PCELL_ID_0_RESERVED_BITWIDTH  24
// GDT1_pcell_id_1 Register
#define GDMAC_GDT1_PCELL_ID_1_OFS                0x00001FF4
// pcell_id_1 bitfiled (RO) Reset=11110000
#define GDMAC_GDT1_PCELL_ID_1_PCELL_ID_1_MASK    0xFF
#define GDMAC_GDT1_PCELL_ID_1_PCELL_ID_1_SHIFT   0 
#define GDMAC_GDT1_PCELL_ID_1_PCELL_ID_1_BIT     0xFF
#define GDMAC_GDT1_PCELL_ID_1_PCELL_ID_1_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_PCELL_ID_1_RESERVED_MASK      0xFFFFFF00
#define GDMAC_GDT1_PCELL_ID_1_RESERVED_SHIFT     8 
#define GDMAC_GDT1_PCELL_ID_1_RESERVED_BIT       0xFFFFFF
#define GDMAC_GDT1_PCELL_ID_1_RESERVED_BITWIDTH  24
// GDT1_pcell_id_2 Register
#define GDMAC_GDT1_PCELL_ID_2_OFS                0x00001FF8
// pcell_id_2 bitfiled (RO) Reset=101
#define GDMAC_GDT1_PCELL_ID_2_PCELL_ID_2_MASK    0xFF
#define GDMAC_GDT1_PCELL_ID_2_PCELL_ID_2_SHIFT   0 
#define GDMAC_GDT1_PCELL_ID_2_PCELL_ID_2_BIT     0xFF
#define GDMAC_GDT1_PCELL_ID_2_PCELL_ID_2_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_PCELL_ID_2_RESERVED_MASK      0xFFFFFF00
#define GDMAC_GDT1_PCELL_ID_2_RESERVED_SHIFT     8 
#define GDMAC_GDT1_PCELL_ID_2_RESERVED_BIT       0xFFFFFF
#define GDMAC_GDT1_PCELL_ID_2_RESERVED_BITWIDTH  24
// GDT1_pcell_id_3 Register
#define GDMAC_GDT1_PCELL_ID_3_OFS                0x00001FFC
// pcell_id_3 bitfiled (RO) Reset=11000001
#define GDMAC_GDT1_PCELL_ID_3_PCELL_ID_3_MASK    0xFF
#define GDMAC_GDT1_PCELL_ID_3_PCELL_ID_3_SHIFT   0 
#define GDMAC_GDT1_PCELL_ID_3_PCELL_ID_3_BIT     0xFF
#define GDMAC_GDT1_PCELL_ID_3_PCELL_ID_3_BITWIDTH 8
// reserved bitfiled (RO) Reset=0
#define GDMAC_GDT1_PCELL_ID_3_RESERVED_MASK      0xFFFFFF00
#define GDMAC_GDT1_PCELL_ID_3_RESERVED_SHIFT     8 
#define GDMAC_GDT1_PCELL_ID_3_RESERVED_BIT       0xFFFFFF
#define GDMAC_GDT1_PCELL_ID_3_RESERVED_BITWIDTH  24

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _GDMAC_REG_DEF_H */
