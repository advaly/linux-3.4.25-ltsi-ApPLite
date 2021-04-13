/*
 * arch/arm/mach-tz2000/include/mach/regs/i2c_reg_struct_b.h
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

#ifndef _I2C_REG_STRUCT_B_H
#define _I2C_REG_STRUCT_B_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // IC0_IC_CON Register
struct I2C_IC0_IC_CON {
	unsigned int reserved:25;		// [31:7]
	unsigned int IC_SLAVE_DISABLE:1;		// [6]
	unsigned int IC_RESTART_EN:1;		// [5]
	unsigned int IC_10BITADDR_MASTER:1;		// [4]
	unsigned int IC_10BITADDR_SLAVE:1;		// [3]
	unsigned int SPEED:2;		// [2:1]
	unsigned int MASTER_MODE:1;		// [0]
};
 // IC0_IC_TAR Register
struct I2C_IC0_IC_TAR {
	unsigned int reserved:19;		// [31:13]
	unsigned int IC_10BITADDR_MASTER:1;		// [12]
	unsigned int SPECIAL:1;		// [11]
	unsigned int GC_OR_START:1;		// [10]
	unsigned int IC_TAR:10;		// [9:0]
};
 // IC0_IC_SAR Register
struct I2C_IC0_IC_SAR {
	unsigned int reserved:22;		// [31:10]
	unsigned int IC_SAR:10;		// [9:0]
};
 // IC0_IC_DATA_CMD Register
struct I2C_IC0_IC_DATA_CMD {
	unsigned int reserved:21;		// [31:11]
	unsigned int RESTART:1;		// [10]
	unsigned int STOP:1;		// [9]
	unsigned int CMD:1;		// [8]
	unsigned int DAT:8;		// [7:0]
};
 // IC0_IC_SS_SCL_HCNT Register
struct I2C_IC0_IC_SS_SCL_HCNT {
	unsigned int reserved:16;		// [31:16]
	unsigned int IC_SS_SCL_HCNT:16;		// [15:0]
};
 // IC0_IC_SS_SCL_LCNT Register
struct I2C_IC0_IC_SS_SCL_LCNT {
	unsigned int reserved:16;		// [31:16]
	unsigned int IC_SS_SCL_LCNT:16;		// [15:0]
};
 // IC0_IC_FS_SCL_HCNT Register
struct I2C_IC0_IC_FS_SCL_HCNT {
	unsigned int reserved:16;		// [31:16]
	unsigned int IC_FS_SCL_HCNT:16;		// [15:0]
};
 // IC0_IC_FS_SCL_LCNT Register
struct I2C_IC0_IC_FS_SCL_LCNT {
	unsigned int reserved:16;		// [31:16]
	unsigned int IC_FS_SCL_LCNT:16;		// [15:0]
};
 // IC0_IC_INTR_STAT Register
struct I2C_IC0_IC_INTR_STAT {
	unsigned int reserved:20;		// [31:12]
	unsigned int R_GEN_CALL:1;		// [11]
	unsigned int R_START_DET:1;		// [10]
	unsigned int R_STOP_DET:1;		// [9]
	unsigned int R_ACTIVITY:1;		// [8]
	unsigned int R_RX_DONE:1;		// [7]
	unsigned int R_TX_ABRT:1;		// [6]
	unsigned int R_RD_REQ:1;		// [5]
	unsigned int R_TX_EMPTY:1;		// [4]
	unsigned int R_TX_OVER:1;		// [3]
	unsigned int R_RX_FULL:1;		// [2]
	unsigned int R_RX_OVER:1;		// [1]
	unsigned int R_RX_UNDER:1;		// [0]
};
 // IC0_IC_INTR_MASK Register
struct I2C_IC0_IC_INTR_MASK {
	unsigned int reserved:20;		// [31:12]
	unsigned int M_GEN_CALL:1;		// [11]
	unsigned int M_START_DET:1;		// [10]
	unsigned int M_STOP_DET:1;		// [9]
	unsigned int M_ACTIVITY:1;		// [8]
	unsigned int M_RX_DONE:1;		// [7]
	unsigned int M_TX_ABRT:1;		// [6]
	unsigned int M_RD_REQ:1;		// [5]
	unsigned int M_TX_EMPTY:1;		// [4]
	unsigned int M_TX_OVER:1;		// [3]
	unsigned int M_RX_FULL:1;		// [2]
	unsigned int M_RX_OVER:1;		// [1]
	unsigned int M_RX_UNDER:1;		// [0]
};
 // IC0_IC_RAW_INTR_STAT Register
struct I2C_IC0_IC_RAW_INTR_STAT {
	unsigned int reserved:20;		// [31:12]
	unsigned int GEN_CALL:1;		// [11]
	unsigned int START_DET:1;		// [10]
	unsigned int STOP_DET:1;		// [9]
	unsigned int ACTIVITY:1;		// [8]
	unsigned int RX_DONE:1;		// [7]
	unsigned int TX_ABRT:1;		// [6]
	unsigned int RD_REQ:1;		// [5]
	unsigned int TX_EMPTY:1;		// [4]
	unsigned int TX_OVER:1;		// [3]
	unsigned int RX_FULL:1;		// [2]
	unsigned int RX_OVER:1;		// [1]
	unsigned int RX_UNDER:1;		// [0]
};
 // IC0_IC_RX_TL Register
struct I2C_IC0_IC_RX_TL {
	unsigned int reserved:24;		// [31:8]
	unsigned int RX_TL:8;		// [7:0]
};
 // IC0_IC_TX_TL Register
struct I2C_IC0_IC_TX_TL {
	unsigned int reserved:24;		// [31:8]
	unsigned int TX_TL:8;		// [7:0]
};
 // IC0_IC_CLR_INTR Register
struct I2C_IC0_IC_CLR_INTR {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_INTR:1;		// [0]
};
 // IC0_IC_CLR_RX_UNDER Register
struct I2C_IC0_IC_CLR_RX_UNDER {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_RX_UNDER:1;		// [0]
};
 // IC0_IC_CLR_RX_OVER Register
struct I2C_IC0_IC_CLR_RX_OVER {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_RX_OVER:1;		// [0]
};
 // IC0_IC_CLR_TX_OVER Register
struct I2C_IC0_IC_CLR_TX_OVER {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_TX_OVER:1;		// [0]
};
 // IC0_IC_CLR_RD_REQ Register
struct I2C_IC0_IC_CLR_RD_REQ {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_RD_REQ:1;		// [0]
};
 // IC0_IC_CLR_TX_ABRT Register
struct I2C_IC0_IC_CLR_TX_ABRT {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_TX_ABRT:1;		// [0]
};
 // IC0_IC_CLR_RX_DONE Register
struct I2C_IC0_IC_CLR_RX_DONE {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_RX_DONE:1;		// [0]
};
 // IC0_IC_CLR_ACTIVITY Register
struct I2C_IC0_IC_CLR_ACTIVITY {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_ACTIVITY:1;		// [0]
};
 // IC0_IC_CLR_STOP_DET Register
struct I2C_IC0_IC_CLR_STOP_DET {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_STOP_DET:1;		// [0]
};
 // IC0_IC_CLR_START_DET Register
struct I2C_IC0_IC_CLR_START_DET {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_START_DET:1;		// [0]
};
 // IC0_IC_CLR_GEN_CALL Register
struct I2C_IC0_IC_CLR_GEN_CALL {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_GEN_CALL:1;		// [0]
};
 // IC0_IC_ENABLE Register
struct I2C_IC0_IC_ENABLE {
	unsigned int reserved:30;		// [31:2]
	unsigned int ABORT:1;		// [1]
	unsigned int ENABLE:1;		// [0]
};
 // IC0_IC_STATUS Register
struct I2C_IC0_IC_STATUS {
	unsigned int reserved:25;		// [31:7]
	unsigned int SLV_ACTIVITY:1;		// [6]
	unsigned int MST_ACTIVITY:1;		// [5]
	unsigned int RFF:1;		// [4]
	unsigned int RFNE:1;		// [3]
	unsigned int TFE:1;		// [2]
	unsigned int TFNF:1;		// [1]
	unsigned int ACTIVITY:1;		// [0]
};
 // IC0_IC_TXFLR Register
struct I2C_IC0_IC_TXFLR {
	unsigned int reserved:27;		// [31:5]
	unsigned int TXFLR:5;		// [4:0]
};
 // IC0_IC_RXFLR Register
struct I2C_IC0_IC_RXFLR {
	unsigned int reserved:27;		// [31:5]
	unsigned int RXFLR:5;		// [4:0]
};
 // IC0_IC_SDA_HOLD Register
struct I2C_IC0_IC_SDA_HOLD {
	unsigned int reserved:16;		// [31:16]
	unsigned int IC_SDA_HOLD:16;		// [15:0]
};
 // IC0_IC_TX_ABRT_SOURCE Register
struct I2C_IC0_IC_TX_ABRT_SOURCE {
	unsigned int TX_FLUSH_CNT:8;		// [31:24]
	unsigned int reserved:8;		// [23:16]
	unsigned int ABRT_SLVRD_INTX:1;		// [15]
	unsigned int ABRT_SLV_ARBLOST:1;		// [14]
	unsigned int ABRT_SLVFLUSH_TXFIFO:1;		// [13]
	unsigned int ARB_LOST:1;		// [12]
	unsigned int ABRT_MASTER_DIS:1;		// [11]
	unsigned int ABRT_10B_RD_NORSTRT:1;		// [10]
	unsigned int ABRT_SBYTE_NORSTRT:1;		// [9]
	unsigned int ABRT_HS_NORSTRT:1;		// [8]
	unsigned int ABRT_SBYTE_ACKDET:1;		// [7]
	unsigned int ABRT_HS_ACKDET:1;		// [6]
	unsigned int ABRT_GCALL_READ:1;		// [5]
	unsigned int ABRT_GCALL_NOACK:1;		// [4]
	unsigned int ABRT_TXDATA_NOACK:1;		// [3]
	unsigned int ABRT_10ADDR2_NOACK:1;		// [2]
	unsigned int ABRT_10ADDR1_NOACK:1;		// [1]
	unsigned int ABRT_7B_ADDR_NOACK:1;		// [0]
};
 // IC0_IC_SLV_DATA_NACK_ONLY Register
struct I2C_IC0_IC_SLV_DATA_NACK_ONLY {
	unsigned int reserved:31;		// [31:1]
	unsigned int NACK:1;		// [0]
};
 // IC0_IC_DMA_CR Register
struct I2C_IC0_IC_DMA_CR {
	unsigned int reserved:30;		// [31:2]
	unsigned int TDMAE:1;		// [1]
	unsigned int RDMAE:1;		// [0]
};
 // IC0_IC_DMA_TDLR Register
struct I2C_IC0_IC_DMA_TDLR {
	unsigned int reserved:28;		// [31:4]
	unsigned int DMATDL:4;		// [3:0]
};
 // IC0_IC_DMA_RDLR Register
struct I2C_IC0_IC_DMA_RDLR {
	unsigned int reserved:28;		// [31:4]
	unsigned int DMARDL:4;		// [3:0]
};
 // IC0_IC_SDA_SETUP Register
struct I2C_IC0_IC_SDA_SETUP {
	unsigned int reserved:24;		// [31:8]
	unsigned int SDA_SETUP:8;		// [7:0]
};
 // IC0_IC_ACK_GENERAL_CALL Register
struct I2C_IC0_IC_ACK_GENERAL_CALL {
	unsigned int reserved:31;		// [31:1]
	unsigned int ACK_GEN_CALL:1;		// [0]
};
 // IC0_IC_ENABLE_STATUS Register
struct I2C_IC0_IC_ENABLE_STATUS {
	unsigned int reserved:29;		// [31:3]
	unsigned int SLV_RX_DATA_LOST:1;		// [2]
	unsigned int SLV_DISABLED_WHILE_BUSY:1;		// [1]
	unsigned int IC_EN:1;		// [0]
};
 // IC0_IC_FS_SPKLEN Register
struct I2C_IC0_IC_FS_SPKLEN {
	unsigned int reserved:24;		// [31:8]
	unsigned int IC_FS_SPKLEN:8;		// [7:0]
};
 // IC0_IC_COMP_PARAM_1 Register
struct I2C_IC0_IC_COMP_PARAM_1 {
	unsigned int reserved:8;		// [31:24]
	unsigned int TX_BUFFER_DEPTH:8;		// [23:16]
	unsigned int RX_BUFFER_DEPTH:8;		// [15:8]
	unsigned int ADD_ENCODED_PARAMS:1;		// [7]
	unsigned int HAS_DMA:1;		// [6]
	unsigned int INTR_IO:1;		// [5]
	unsigned int HC_COUNT_VALUES:1;		// [4]
	unsigned int MAX_SPEED_MODE:2;		// [3:2]
	unsigned int APB_DATA_WIDTH:2;		// [1:0]
};
 // IC0_IC_COMP_VERSION Register
struct I2C_IC0_IC_COMP_VERSION {
	unsigned int IC_COMP_VERSION:32;		// [31:0]
};
 // IC0_IC_COMP_TYPE Register
struct I2C_IC0_IC_COMP_TYPE {
	unsigned int IC_COMP_TYPE:32;		// [31:0]
};
 // IC1_IC_CON Register
struct I2C_IC1_IC_CON {
	unsigned int reserved:25;		// [31:7]
	unsigned int IC_SLAVE_DISABLE:1;		// [6]
	unsigned int IC_RESTART_EN:1;		// [5]
	unsigned int IC_10BITADDR_MASTER:1;		// [4]
	unsigned int IC_10BITADDR_SLAVE:1;		// [3]
	unsigned int SPEED:2;		// [2:1]
	unsigned int MASTER_MODE:1;		// [0]
};
 // IC1_IC_TAR Register
struct I2C_IC1_IC_TAR {
	unsigned int reserved:19;		// [31:13]
	unsigned int IC_10BITADDR_MASTER:1;		// [12]
	unsigned int SPECIAL:1;		// [11]
	unsigned int GC_OR_START:1;		// [10]
	unsigned int IC_TAR:10;		// [9:0]
};
 // IC1_IC_SAR Register
struct I2C_IC1_IC_SAR {
	unsigned int reserved:22;		// [31:10]
	unsigned int IC_SAR:10;		// [9:0]
};
 // IC1_IC_DATA_CMD Register
struct I2C_IC1_IC_DATA_CMD {
	unsigned int reserved:21;		// [31:11]
	unsigned int RESTART:1;		// [10]
	unsigned int STOP:1;		// [9]
	unsigned int CMD:1;		// [8]
	unsigned int DAT:8;		// [7:0]
};
 // IC1_IC_SS_SCL_HCNT Register
struct I2C_IC1_IC_SS_SCL_HCNT {
	unsigned int reserved:16;		// [31:16]
	unsigned int IC_SS_SCL_HCNT:16;		// [15:0]
};
 // IC1_IC_SS_SCL_LCNT Register
struct I2C_IC1_IC_SS_SCL_LCNT {
	unsigned int reserved:16;		// [31:16]
	unsigned int IC_SS_SCL_LCNT:16;		// [15:0]
};
 // IC1_IC_FS_SCL_HCNT Register
struct I2C_IC1_IC_FS_SCL_HCNT {
	unsigned int reserved:16;		// [31:16]
	unsigned int IC_FS_SCL_HCNT:16;		// [15:0]
};
 // IC1_IC_FS_SCL_LCNT Register
struct I2C_IC1_IC_FS_SCL_LCNT {
	unsigned int reserved:16;		// [31:16]
	unsigned int IC_FS_SCL_LCNT:16;		// [15:0]
};
 // IC1_IC_INTR_STAT Register
struct I2C_IC1_IC_INTR_STAT {
	unsigned int reserved:20;		// [31:12]
	unsigned int R_GEN_CALL:1;		// [11]
	unsigned int R_START_DET:1;		// [10]
	unsigned int R_STOP_DET:1;		// [9]
	unsigned int R_ACTIVITY:1;		// [8]
	unsigned int R_RX_DONE:1;		// [7]
	unsigned int R_TX_ABRT:1;		// [6]
	unsigned int R_RD_REQ:1;		// [5]
	unsigned int R_TX_EMPTY:1;		// [4]
	unsigned int R_TX_OVER:1;		// [3]
	unsigned int R_RX_FULL:1;		// [2]
	unsigned int R_RX_OVER:1;		// [1]
	unsigned int R_RX_UNDER:1;		// [0]
};
 // IC1_IC_INTR_MASK Register
struct I2C_IC1_IC_INTR_MASK {
	unsigned int reserved:20;		// [31:12]
	unsigned int M_GEN_CALL:1;		// [11]
	unsigned int M_START_DET:1;		// [10]
	unsigned int M_STOP_DET:1;		// [9]
	unsigned int M_ACTIVITY:1;		// [8]
	unsigned int M_RX_DONE:1;		// [7]
	unsigned int M_TX_ABRT:1;		// [6]
	unsigned int M_RD_REQ:1;		// [5]
	unsigned int M_TX_EMPTY:1;		// [4]
	unsigned int M_TX_OVER:1;		// [3]
	unsigned int M_RX_FULL:1;		// [2]
	unsigned int M_RX_OVER:1;		// [1]
	unsigned int M_RX_UNDER:1;		// [0]
};
 // IC1_IC_RAW_INTR_STAT Register
struct I2C_IC1_IC_RAW_INTR_STAT {
	unsigned int reserved:20;		// [31:12]
	unsigned int GEN_CALL:1;		// [11]
	unsigned int START_DET:1;		// [10]
	unsigned int STOP_DET:1;		// [9]
	unsigned int ACTIVITY:1;		// [8]
	unsigned int RX_DONE:1;		// [7]
	unsigned int TX_ABRT:1;		// [6]
	unsigned int RD_REQ:1;		// [5]
	unsigned int TX_EMPTY:1;		// [4]
	unsigned int TX_OVER:1;		// [3]
	unsigned int RX_FULL:1;		// [2]
	unsigned int RX_OVER:1;		// [1]
	unsigned int RX_UNDER:1;		// [0]
};
 // IC1_IC_RX_TL Register
struct I2C_IC1_IC_RX_TL {
	unsigned int reserved:24;		// [31:8]
	unsigned int RX_TL:8;		// [7:0]
};
 // IC1_IC_TX_TL Register
struct I2C_IC1_IC_TX_TL {
	unsigned int reserved:24;		// [31:8]
	unsigned int TX_TL:8;		// [7:0]
};
 // IC1_IC_CLR_INTR Register
struct I2C_IC1_IC_CLR_INTR {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_INTR:1;		// [0]
};
 // IC1_IC_CLR_RX_UNDER Register
struct I2C_IC1_IC_CLR_RX_UNDER {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_RX_UNDER:1;		// [0]
};
 // IC1_IC_CLR_RX_OVER Register
struct I2C_IC1_IC_CLR_RX_OVER {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_RX_OVER:1;		// [0]
};
 // IC1_IC_CLR_TX_OVER Register
struct I2C_IC1_IC_CLR_TX_OVER {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_TX_OVER:1;		// [0]
};
 // IC1_IC_CLR_RD_REQ Register
struct I2C_IC1_IC_CLR_RD_REQ {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_RD_REQ:1;		// [0]
};
 // IC1_IC_CLR_TX_ABRT Register
struct I2C_IC1_IC_CLR_TX_ABRT {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_TX_ABRT:1;		// [0]
};
 // IC1_IC_CLR_RX_DONE Register
struct I2C_IC1_IC_CLR_RX_DONE {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_RX_DONE:1;		// [0]
};
 // IC1_IC_CLR_ACTIVITY Register
struct I2C_IC1_IC_CLR_ACTIVITY {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_ACTIVITY:1;		// [0]
};
 // IC1_IC_CLR_STOP_DET Register
struct I2C_IC1_IC_CLR_STOP_DET {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_STOP_DET:1;		// [0]
};
 // IC1_IC_CLR_START_DET Register
struct I2C_IC1_IC_CLR_START_DET {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_START_DET:1;		// [0]
};
 // IC1_IC_CLR_GEN_CALL Register
struct I2C_IC1_IC_CLR_GEN_CALL {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_GEN_CALL:1;		// [0]
};
 // IC1_IC_ENABLE Register
struct I2C_IC1_IC_ENABLE {
	unsigned int reserved:30;		// [31:2]
	unsigned int ABORT:1;		// [1]
	unsigned int ENABLE:1;		// [0]
};
 // IC1_IC_STATUS Register
struct I2C_IC1_IC_STATUS {
	unsigned int reserved:25;		// [31:7]
	unsigned int SLV_ACTIVITY:1;		// [6]
	unsigned int MST_ACTIVITY:1;		// [5]
	unsigned int RFF:1;		// [4]
	unsigned int RFNE:1;		// [3]
	unsigned int TFE:1;		// [2]
	unsigned int TFNF:1;		// [1]
	unsigned int ACTIVITY:1;		// [0]
};
 // IC1_IC_TXFLR Register
struct I2C_IC1_IC_TXFLR {
	unsigned int reserved:27;		// [31:5]
	unsigned int TXFLR:5;		// [4:0]
};
 // IC1_IC_RXFLR Register
struct I2C_IC1_IC_RXFLR {
	unsigned int reserved:27;		// [31:5]
	unsigned int RXFLR:5;		// [4:0]
};
 // IC1_IC_SDA_HOLD Register
struct I2C_IC1_IC_SDA_HOLD {
	unsigned int reserved:16;		// [31:16]
	unsigned int IC_SDA_HOLD:16;		// [15:0]
};
 // IC1_IC_TX_ABRT_SOURCE Register
struct I2C_IC1_IC_TX_ABRT_SOURCE {
	unsigned int TX_FLUSH_CNT:8;		// [31:24]
	unsigned int reserved:8;		// [23:16]
	unsigned int ABRT_SLVRD_INTX:1;		// [15]
	unsigned int ABRT_SLV_ARBLOST:1;		// [14]
	unsigned int ABRT_SLVFLUSH_TXFIFO:1;		// [13]
	unsigned int ARB_LOST:1;		// [12]
	unsigned int ABRT_MASTER_DIS:1;		// [11]
	unsigned int ABRT_10B_RD_NORSTRT:1;		// [10]
	unsigned int ABRT_SBYTE_NORSTRT:1;		// [9]
	unsigned int ABRT_HS_NORSTRT:1;		// [8]
	unsigned int ABRT_SBYTE_ACKDET:1;		// [7]
	unsigned int ABRT_HS_ACKDET:1;		// [6]
	unsigned int ABRT_GCALL_READ:1;		// [5]
	unsigned int ABRT_GCALL_NOACK:1;		// [4]
	unsigned int ABRT_TXDATA_NOACK:1;		// [3]
	unsigned int ABRT_10ADDR2_NOACK:1;		// [2]
	unsigned int ABRT_10ADDR1_NOACK:1;		// [1]
	unsigned int ABRT_7B_ADDR_NOACK:1;		// [0]
};
 // IC1_IC_SLV_DATA_NACK_ONLY Register
struct I2C_IC1_IC_SLV_DATA_NACK_ONLY {
	unsigned int reserved:31;		// [31:1]
	unsigned int NACK:1;		// [0]
};
 // IC1_IC_DMA_CR Register
struct I2C_IC1_IC_DMA_CR {
	unsigned int reserved:30;		// [31:2]
	unsigned int TDMAE:1;		// [1]
	unsigned int RDMAE:1;		// [0]
};
 // IC1_IC_DMA_TDLR Register
struct I2C_IC1_IC_DMA_TDLR {
	unsigned int reserved:28;		// [31:4]
	unsigned int DMATDL:4;		// [3:0]
};
 // IC1_IC_DMA_RDLR Register
struct I2C_IC1_IC_DMA_RDLR {
	unsigned int reserved:28;		// [31:4]
	unsigned int DMARDL:4;		// [3:0]
};
 // IC1_IC_SDA_SETUP Register
struct I2C_IC1_IC_SDA_SETUP {
	unsigned int reserved:24;		// [31:8]
	unsigned int SDA_SETUP:8;		// [7:0]
};
 // IC1_IC_ACK_GENERAL_CALL Register
struct I2C_IC1_IC_ACK_GENERAL_CALL {
	unsigned int reserved:31;		// [31:1]
	unsigned int ACK_GEN_CALL:1;		// [0]
};
 // IC1_IC_ENABLE_STATUS Register
struct I2C_IC1_IC_ENABLE_STATUS {
	unsigned int reserved:29;		// [31:3]
	unsigned int SLV_RX_DATA_LOST:1;		// [2]
	unsigned int SLV_DISABLED_WHILE_BUSY:1;		// [1]
	unsigned int IC_EN:1;		// [0]
};
 // IC1_IC_FS_SPKLEN Register
struct I2C_IC1_IC_FS_SPKLEN {
	unsigned int reserved:24;		// [31:8]
	unsigned int IC_FS_SPKLEN:8;		// [7:0]
};
 // IC1_IC_COMP_PARAM_1 Register
struct I2C_IC1_IC_COMP_PARAM_1 {
	unsigned int reserved:8;		// [31:24]
	unsigned int TX_BUFFER_DEPTH:8;		// [23:16]
	unsigned int RX_BUFFER_DEPTH:8;		// [15:8]
	unsigned int ADD_ENCODED_PARAMS:1;		// [7]
	unsigned int HAS_DMA:1;		// [6]
	unsigned int INTR_IO:1;		// [5]
	unsigned int HC_COUNT_VALUES:1;		// [4]
	unsigned int MAX_SPEED_MODE:2;		// [3:2]
	unsigned int APB_DATA_WIDTH:2;		// [1:0]
};
 // IC1_IC_COMP_VERSION Register
struct I2C_IC1_IC_COMP_VERSION {
	unsigned int IC_COMP_VERSION:32;		// [31:0]
};
 // IC1_IC_COMP_TYPE Register
struct I2C_IC1_IC_COMP_TYPE {
	unsigned int IC_COMP_TYPE:32;		// [31:0]
};
 // IC2_IC_CON Register
struct I2C_IC2_IC_CON {
	unsigned int reserved:25;		// [31:7]
	unsigned int IC_SLAVE_DISABLE:1;		// [6]
	unsigned int IC_RESTART_EN:1;		// [5]
	unsigned int IC_10BITADDR_MASTER:1;		// [4]
	unsigned int IC_10BITADDR_SLAVE:1;		// [3]
	unsigned int SPEED:2;		// [2:1]
	unsigned int MASTER_MODE:1;		// [0]
};
 // IC2_IC_TAR Register
struct I2C_IC2_IC_TAR {
	unsigned int reserved:19;		// [31:13]
	unsigned int IC_10BITADDR_MASTER:1;		// [12]
	unsigned int SPECIAL:1;		// [11]
	unsigned int GC_OR_START:1;		// [10]
	unsigned int IC_TAR:10;		// [9:0]
};
 // IC2_IC_SAR Register
struct I2C_IC2_IC_SAR {
	unsigned int reserved:22;		// [31:10]
	unsigned int IC_SAR:10;		// [9:0]
};
 // IC2_IC_DATA_CMD Register
struct I2C_IC2_IC_DATA_CMD {
	unsigned int reserved:21;		// [31:11]
	unsigned int RESTART:1;		// [10]
	unsigned int STOP:1;		// [9]
	unsigned int CMD:1;		// [8]
	unsigned int DAT:8;		// [7:0]
};
 // IC2_IC_SS_SCL_HCNT Register
struct I2C_IC2_IC_SS_SCL_HCNT {
	unsigned int reserved:16;		// [31:16]
	unsigned int IC_SS_SCL_HCNT:16;		// [15:0]
};
 // IC2_IC_SS_SCL_LCNT Register
struct I2C_IC2_IC_SS_SCL_LCNT {
	unsigned int reserved:16;		// [31:16]
	unsigned int IC_SS_SCL_LCNT:16;		// [15:0]
};
 // IC2_IC_FS_SCL_HCNT Register
struct I2C_IC2_IC_FS_SCL_HCNT {
	unsigned int reserved:16;		// [31:16]
	unsigned int IC_FS_SCL_HCNT:16;		// [15:0]
};
 // IC2_IC_FS_SCL_LCNT Register
struct I2C_IC2_IC_FS_SCL_LCNT {
	unsigned int reserved:16;		// [31:16]
	unsigned int IC_FS_SCL_LCNT:16;		// [15:0]
};
 // IC2_IC_INTR_STAT Register
struct I2C_IC2_IC_INTR_STAT {
	unsigned int reserved:20;		// [31:12]
	unsigned int R_GEN_CALL:1;		// [11]
	unsigned int R_START_DET:1;		// [10]
	unsigned int R_STOP_DET:1;		// [9]
	unsigned int R_ACTIVITY:1;		// [8]
	unsigned int R_RX_DONE:1;		// [7]
	unsigned int R_TX_ABRT:1;		// [6]
	unsigned int R_RD_REQ:1;		// [5]
	unsigned int R_TX_EMPTY:1;		// [4]
	unsigned int R_TX_OVER:1;		// [3]
	unsigned int R_RX_FULL:1;		// [2]
	unsigned int R_RX_OVER:1;		// [1]
	unsigned int R_RX_UNDER:1;		// [0]
};
 // IC2_IC_INTR_MASK Register
struct I2C_IC2_IC_INTR_MASK {
	unsigned int reserved:20;		// [31:12]
	unsigned int M_GEN_CALL:1;		// [11]
	unsigned int M_START_DET:1;		// [10]
	unsigned int M_STOP_DET:1;		// [9]
	unsigned int M_ACTIVITY:1;		// [8]
	unsigned int M_RX_DONE:1;		// [7]
	unsigned int M_TX_ABRT:1;		// [6]
	unsigned int M_RD_REQ:1;		// [5]
	unsigned int M_TX_EMPTY:1;		// [4]
	unsigned int M_TX_OVER:1;		// [3]
	unsigned int M_RX_FULL:1;		// [2]
	unsigned int M_RX_OVER:1;		// [1]
	unsigned int M_RX_UNDER:1;		// [0]
};
 // IC2_IC_RAW_INTR_STAT Register
struct I2C_IC2_IC_RAW_INTR_STAT {
	unsigned int reserved:20;		// [31:12]
	unsigned int GEN_CALL:1;		// [11]
	unsigned int START_DET:1;		// [10]
	unsigned int STOP_DET:1;		// [9]
	unsigned int ACTIVITY:1;		// [8]
	unsigned int RX_DONE:1;		// [7]
	unsigned int TX_ABRT:1;		// [6]
	unsigned int RD_REQ:1;		// [5]
	unsigned int TX_EMPTY:1;		// [4]
	unsigned int TX_OVER:1;		// [3]
	unsigned int RX_FULL:1;		// [2]
	unsigned int RX_OVER:1;		// [1]
	unsigned int RX_UNDER:1;		// [0]
};
 // IC2_IC_RX_TL Register
struct I2C_IC2_IC_RX_TL {
	unsigned int reserved:24;		// [31:8]
	unsigned int RX_TL:8;		// [7:0]
};
 // IC2_IC_TX_TL Register
struct I2C_IC2_IC_TX_TL {
	unsigned int reserved:24;		// [31:8]
	unsigned int TX_TL:8;		// [7:0]
};
 // IC2_IC_CLR_INTR Register
struct I2C_IC2_IC_CLR_INTR {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_INTR:1;		// [0]
};
 // IC2_IC_CLR_RX_UNDER Register
struct I2C_IC2_IC_CLR_RX_UNDER {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_RX_UNDER:1;		// [0]
};
 // IC2_IC_CLR_RX_OVER Register
struct I2C_IC2_IC_CLR_RX_OVER {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_RX_OVER:1;		// [0]
};
 // IC2_IC_CLR_TX_OVER Register
struct I2C_IC2_IC_CLR_TX_OVER {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_TX_OVER:1;		// [0]
};
 // IC2_IC_CLR_RD_REQ Register
struct I2C_IC2_IC_CLR_RD_REQ {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_RD_REQ:1;		// [0]
};
 // IC2_IC_CLR_TX_ABRT Register
struct I2C_IC2_IC_CLR_TX_ABRT {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_TX_ABRT:1;		// [0]
};
 // IC2_IC_CLR_RX_DONE Register
struct I2C_IC2_IC_CLR_RX_DONE {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_RX_DONE:1;		// [0]
};
 // IC2_IC_CLR_ACTIVITY Register
struct I2C_IC2_IC_CLR_ACTIVITY {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_ACTIVITY:1;		// [0]
};
 // IC2_IC_CLR_STOP_DET Register
struct I2C_IC2_IC_CLR_STOP_DET {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_STOP_DET:1;		// [0]
};
 // IC2_IC_CLR_START_DET Register
struct I2C_IC2_IC_CLR_START_DET {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_START_DET:1;		// [0]
};
 // IC2_IC_CLR_GEN_CALL Register
struct I2C_IC2_IC_CLR_GEN_CALL {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_GEN_CALL:1;		// [0]
};
 // IC2_IC_ENABLE Register
struct I2C_IC2_IC_ENABLE {
	unsigned int reserved:30;		// [31:2]
	unsigned int ABORT:1;		// [1]
	unsigned int ENABLE:1;		// [0]
};
 // IC2_IC_STATUS Register
struct I2C_IC2_IC_STATUS {
	unsigned int reserved:25;		// [31:7]
	unsigned int SLV_ACTIVITY:1;		// [6]
	unsigned int MST_ACTIVITY:1;		// [5]
	unsigned int RFF:1;		// [4]
	unsigned int RFNE:1;		// [3]
	unsigned int TFE:1;		// [2]
	unsigned int TFNF:1;		// [1]
	unsigned int ACTIVITY:1;		// [0]
};
 // IC2_IC_TXFLR Register
struct I2C_IC2_IC_TXFLR {
	unsigned int reserved:27;		// [31:5]
	unsigned int TXFLR:5;		// [4:0]
};
 // IC2_IC_RXFLR Register
struct I2C_IC2_IC_RXFLR {
	unsigned int reserved:27;		// [31:5]
	unsigned int RXFLR:5;		// [4:0]
};
 // IC2_IC_SDA_HOLD Register
struct I2C_IC2_IC_SDA_HOLD {
	unsigned int reserved:16;		// [31:16]
	unsigned int IC_SDA_HOLD:16;		// [15:0]
};
 // IC2_IC_TX_ABRT_SOURCE Register
struct I2C_IC2_IC_TX_ABRT_SOURCE {
	unsigned int TX_FLUSH_CNT:8;		// [31:24]
	unsigned int reserved:8;		// [23:16]
	unsigned int ABRT_SLVRD_INTX:1;		// [15]
	unsigned int ABRT_SLV_ARBLOST:1;		// [14]
	unsigned int ABRT_SLVFLUSH_TXFIFO:1;		// [13]
	unsigned int ARB_LOST:1;		// [12]
	unsigned int ABRT_MASTER_DIS:1;		// [11]
	unsigned int ABRT_10B_RD_NORSTRT:1;		// [10]
	unsigned int ABRT_SBYTE_NORSTRT:1;		// [9]
	unsigned int ABRT_HS_NORSTRT:1;		// [8]
	unsigned int ABRT_SBYTE_ACKDET:1;		// [7]
	unsigned int ABRT_HS_ACKDET:1;		// [6]
	unsigned int ABRT_GCALL_READ:1;		// [5]
	unsigned int ABRT_GCALL_NOACK:1;		// [4]
	unsigned int ABRT_TXDATA_NOACK:1;		// [3]
	unsigned int ABRT_10ADDR2_NOACK:1;		// [2]
	unsigned int ABRT_10ADDR1_NOACK:1;		// [1]
	unsigned int ABRT_7B_ADDR_NOACK:1;		// [0]
};
 // IC2_IC_SLV_DATA_NACK_ONLY Register
struct I2C_IC2_IC_SLV_DATA_NACK_ONLY {
	unsigned int reserved:31;		// [31:1]
	unsigned int NACK:1;		// [0]
};
 // IC2_IC_DMA_CR Register
struct I2C_IC2_IC_DMA_CR {
	unsigned int reserved:30;		// [31:2]
	unsigned int TDMAE:1;		// [1]
	unsigned int RDMAE:1;		// [0]
};
 // IC2_IC_DMA_TDLR Register
struct I2C_IC2_IC_DMA_TDLR {
	unsigned int reserved:28;		// [31:4]
	unsigned int DMATDL:4;		// [3:0]
};
 // IC2_IC_DMA_RDLR Register
struct I2C_IC2_IC_DMA_RDLR {
	unsigned int reserved:28;		// [31:4]
	unsigned int DMARDL:4;		// [3:0]
};
 // IC2_IC_SDA_SETUP Register
struct I2C_IC2_IC_SDA_SETUP {
	unsigned int reserved:24;		// [31:8]
	unsigned int SDA_SETUP:8;		// [7:0]
};
 // IC2_IC_ACK_GENERAL_CALL Register
struct I2C_IC2_IC_ACK_GENERAL_CALL {
	unsigned int reserved:31;		// [31:1]
	unsigned int ACK_GEN_CALL:1;		// [0]
};
 // IC2_IC_ENABLE_STATUS Register
struct I2C_IC2_IC_ENABLE_STATUS {
	unsigned int reserved:29;		// [31:3]
	unsigned int SLV_RX_DATA_LOST:1;		// [2]
	unsigned int SLV_DISABLED_WHILE_BUSY:1;		// [1]
	unsigned int IC_EN:1;		// [0]
};
 // IC2_IC_FS_SPKLEN Register
struct I2C_IC2_IC_FS_SPKLEN {
	unsigned int reserved:24;		// [31:8]
	unsigned int IC_FS_SPKLEN:8;		// [7:0]
};
 // IC2_IC_COMP_PARAM_1 Register
struct I2C_IC2_IC_COMP_PARAM_1 {
	unsigned int reserved:8;		// [31:24]
	unsigned int TX_BUFFER_DEPTH:8;		// [23:16]
	unsigned int RX_BUFFER_DEPTH:8;		// [15:8]
	unsigned int ADD_ENCODED_PARAMS:1;		// [7]
	unsigned int HAS_DMA:1;		// [6]
	unsigned int INTR_IO:1;		// [5]
	unsigned int HC_COUNT_VALUES:1;		// [4]
	unsigned int MAX_SPEED_MODE:2;		// [3:2]
	unsigned int APB_DATA_WIDTH:2;		// [1:0]
};
 // IC2_IC_COMP_VERSION Register
struct I2C_IC2_IC_COMP_VERSION {
	unsigned int IC_COMP_VERSION:32;		// [31:0]
};
 // IC2_IC_COMP_TYPE Register
struct I2C_IC2_IC_COMP_TYPE {
	unsigned int IC_COMP_TYPE:32;		// [31:0]
};
 // IC3_IC_CON Register
struct I2C_IC3_IC_CON {
	unsigned int reserved:25;		// [31:7]
	unsigned int IC_SLAVE_DISABLE:1;		// [6]
	unsigned int IC_RESTART_EN:1;		// [5]
	unsigned int IC_10BITADDR_MASTER:1;		// [4]
	unsigned int IC_10BITADDR_SLAVE:1;		// [3]
	unsigned int SPEED:2;		// [2:1]
	unsigned int MASTER_MODE:1;		// [0]
};
 // IC3_IC_TAR Register
struct I2C_IC3_IC_TAR {
	unsigned int reserved:19;		// [31:13]
	unsigned int IC_10BITADDR_MASTER:1;		// [12]
	unsigned int SPECIAL:1;		// [11]
	unsigned int GC_OR_START:1;		// [10]
	unsigned int IC_TAR:10;		// [9:0]
};
 // IC3_IC_SAR Register
struct I2C_IC3_IC_SAR {
	unsigned int reserved:22;		// [31:10]
	unsigned int IC_SAR:10;		// [9:0]
};
 // IC3_IC_DATA_CMD Register
struct I2C_IC3_IC_DATA_CMD {
	unsigned int reserved:21;		// [31:11]
	unsigned int RESTART:1;		// [10]
	unsigned int STOP:1;		// [9]
	unsigned int CMD:1;		// [8]
	unsigned int DAT:8;		// [7:0]
};
 // IC3_IC_SS_SCL_HCNT Register
struct I2C_IC3_IC_SS_SCL_HCNT {
	unsigned int reserved:16;		// [31:16]
	unsigned int IC_SS_SCL_HCNT:16;		// [15:0]
};
 // IC3_IC_SS_SCL_LCNT Register
struct I2C_IC3_IC_SS_SCL_LCNT {
	unsigned int reserved:16;		// [31:16]
	unsigned int IC_SS_SCL_LCNT:16;		// [15:0]
};
 // IC3_IC_FS_SCL_HCNT Register
struct I2C_IC3_IC_FS_SCL_HCNT {
	unsigned int reserved:16;		// [31:16]
	unsigned int IC_FS_SCL_HCNT:16;		// [15:0]
};
 // IC3_IC_FS_SCL_LCNT Register
struct I2C_IC3_IC_FS_SCL_LCNT {
	unsigned int reserved:16;		// [31:16]
	unsigned int IC_FS_SCL_LCNT:16;		// [15:0]
};
 // IC3_IC_INTR_STAT Register
struct I2C_IC3_IC_INTR_STAT {
	unsigned int reserved:20;		// [31:12]
	unsigned int R_GEN_CALL:1;		// [11]
	unsigned int R_START_DET:1;		// [10]
	unsigned int R_STOP_DET:1;		// [9]
	unsigned int R_ACTIVITY:1;		// [8]
	unsigned int R_RX_DONE:1;		// [7]
	unsigned int R_TX_ABRT:1;		// [6]
	unsigned int R_RD_REQ:1;		// [5]
	unsigned int R_TX_EMPTY:1;		// [4]
	unsigned int R_TX_OVER:1;		// [3]
	unsigned int R_RX_FULL:1;		// [2]
	unsigned int R_RX_OVER:1;		// [1]
	unsigned int R_RX_UNDER:1;		// [0]
};
 // IC3_IC_INTR_MASK Register
struct I2C_IC3_IC_INTR_MASK {
	unsigned int reserved:20;		// [31:12]
	unsigned int M_GEN_CALL:1;		// [11]
	unsigned int M_START_DET:1;		// [10]
	unsigned int M_STOP_DET:1;		// [9]
	unsigned int M_ACTIVITY:1;		// [8]
	unsigned int M_RX_DONE:1;		// [7]
	unsigned int M_TX_ABRT:1;		// [6]
	unsigned int M_RD_REQ:1;		// [5]
	unsigned int M_TX_EMPTY:1;		// [4]
	unsigned int M_TX_OVER:1;		// [3]
	unsigned int M_RX_FULL:1;		// [2]
	unsigned int M_RX_OVER:1;		// [1]
	unsigned int M_RX_UNDER:1;		// [0]
};
 // IC3_IC_RAW_INTR_STAT Register
struct I2C_IC3_IC_RAW_INTR_STAT {
	unsigned int reserved:20;		// [31:12]
	unsigned int GEN_CALL:1;		// [11]
	unsigned int START_DET:1;		// [10]
	unsigned int STOP_DET:1;		// [9]
	unsigned int ACTIVITY:1;		// [8]
	unsigned int RX_DONE:1;		// [7]
	unsigned int TX_ABRT:1;		// [6]
	unsigned int RD_REQ:1;		// [5]
	unsigned int TX_EMPTY:1;		// [4]
	unsigned int TX_OVER:1;		// [3]
	unsigned int RX_FULL:1;		// [2]
	unsigned int RX_OVER:1;		// [1]
	unsigned int RX_UNDER:1;		// [0]
};
 // IC3_IC_RX_TL Register
struct I2C_IC3_IC_RX_TL {
	unsigned int reserved:24;		// [31:8]
	unsigned int RX_TL:8;		// [7:0]
};
 // IC3_IC_TX_TL Register
struct I2C_IC3_IC_TX_TL {
	unsigned int reserved:24;		// [31:8]
	unsigned int TX_TL:8;		// [7:0]
};
 // IC3_IC_CLR_INTR Register
struct I2C_IC3_IC_CLR_INTR {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_INTR:1;		// [0]
};
 // IC3_IC_CLR_RX_UNDER Register
struct I2C_IC3_IC_CLR_RX_UNDER {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_RX_UNDER:1;		// [0]
};
 // IC3_IC_CLR_RX_OVER Register
struct I2C_IC3_IC_CLR_RX_OVER {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_RX_OVER:1;		// [0]
};
 // IC3_IC_CLR_TX_OVER Register
struct I2C_IC3_IC_CLR_TX_OVER {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_TX_OVER:1;		// [0]
};
 // IC3_IC_CLR_RD_REQ Register
struct I2C_IC3_IC_CLR_RD_REQ {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_RD_REQ:1;		// [0]
};
 // IC3_IC_CLR_TX_ABRT Register
struct I2C_IC3_IC_CLR_TX_ABRT {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_TX_ABRT:1;		// [0]
};
 // IC3_IC_CLR_RX_DONE Register
struct I2C_IC3_IC_CLR_RX_DONE {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_RX_DONE:1;		// [0]
};
 // IC3_IC_CLR_ACTIVITY Register
struct I2C_IC3_IC_CLR_ACTIVITY {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_ACTIVITY:1;		// [0]
};
 // IC3_IC_CLR_STOP_DET Register
struct I2C_IC3_IC_CLR_STOP_DET {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_STOP_DET:1;		// [0]
};
 // IC3_IC_CLR_START_DET Register
struct I2C_IC3_IC_CLR_START_DET {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_START_DET:1;		// [0]
};
 // IC3_IC_CLR_GEN_CALL Register
struct I2C_IC3_IC_CLR_GEN_CALL {
	unsigned int reserved:31;		// [31:1]
	unsigned int CLR_GEN_CALL:1;		// [0]
};
 // IC3_IC_ENABLE Register
struct I2C_IC3_IC_ENABLE {
	unsigned int reserved:30;		// [31:2]
	unsigned int ABORT:1;		// [1]
	unsigned int ENABLE:1;		// [0]
};
 // IC3_IC_STATUS Register
struct I2C_IC3_IC_STATUS {
	unsigned int reserved:25;		// [31:7]
	unsigned int SLV_ACTIVITY:1;		// [6]
	unsigned int MST_ACTIVITY:1;		// [5]
	unsigned int RFF:1;		// [4]
	unsigned int RFNE:1;		// [3]
	unsigned int TFE:1;		// [2]
	unsigned int TFNF:1;		// [1]
	unsigned int ACTIVITY:1;		// [0]
};
 // IC3_IC_TXFLR Register
struct I2C_IC3_IC_TXFLR {
	unsigned int reserved:27;		// [31:5]
	unsigned int TXFLR:5;		// [4:0]
};
 // IC3_IC_RXFLR Register
struct I2C_IC3_IC_RXFLR {
	unsigned int reserved:27;		// [31:5]
	unsigned int RXFLR:5;		// [4:0]
};
 // IC3_IC_SDA_HOLD Register
struct I2C_IC3_IC_SDA_HOLD {
	unsigned int reserved:16;		// [31:16]
	unsigned int IC_SDA_HOLD:16;		// [15:0]
};
 // IC3_IC_TX_ABRT_SOURCE Register
struct I2C_IC3_IC_TX_ABRT_SOURCE {
	unsigned int TX_FLUSH_CNT:8;		// [31:24]
	unsigned int reserved:8;		// [23:16]
	unsigned int ABRT_SLVRD_INTX:1;		// [15]
	unsigned int ABRT_SLV_ARBLOST:1;		// [14]
	unsigned int ABRT_SLVFLUSH_TXFIFO:1;		// [13]
	unsigned int ARB_LOST:1;		// [12]
	unsigned int ABRT_MASTER_DIS:1;		// [11]
	unsigned int ABRT_10B_RD_NORSTRT:1;		// [10]
	unsigned int ABRT_SBYTE_NORSTRT:1;		// [9]
	unsigned int ABRT_HS_NORSTRT:1;		// [8]
	unsigned int ABRT_SBYTE_ACKDET:1;		// [7]
	unsigned int ABRT_HS_ACKDET:1;		// [6]
	unsigned int ABRT_GCALL_READ:1;		// [5]
	unsigned int ABRT_GCALL_NOACK:1;		// [4]
	unsigned int ABRT_TXDATA_NOACK:1;		// [3]
	unsigned int ABRT_10ADDR2_NOACK:1;		// [2]
	unsigned int ABRT_10ADDR1_NOACK:1;		// [1]
	unsigned int ABRT_7B_ADDR_NOACK:1;		// [0]
};
 // IC3_IC_SLV_DATA_NACK_ONLY Register
struct I2C_IC3_IC_SLV_DATA_NACK_ONLY {
	unsigned int reserved:31;		// [31:1]
	unsigned int NACK:1;		// [0]
};
 // IC3_IC_DMA_CR Register
struct I2C_IC3_IC_DMA_CR {
	unsigned int reserved:30;		// [31:2]
	unsigned int TDMAE:1;		// [1]
	unsigned int RDMAE:1;		// [0]
};
 // IC3_IC_DMA_TDLR Register
struct I2C_IC3_IC_DMA_TDLR {
	unsigned int reserved:28;		// [31:4]
	unsigned int DMATDL:4;		// [3:0]
};
 // IC3_IC_DMA_RDLR Register
struct I2C_IC3_IC_DMA_RDLR {
	unsigned int reserved:28;		// [31:4]
	unsigned int DMARDL:4;		// [3:0]
};
 // IC3_IC_SDA_SETUP Register
struct I2C_IC3_IC_SDA_SETUP {
	unsigned int reserved:24;		// [31:8]
	unsigned int SDA_SETUP:8;		// [7:0]
};
 // IC3_IC_ACK_GENERAL_CALL Register
struct I2C_IC3_IC_ACK_GENERAL_CALL {
	unsigned int reserved:31;		// [31:1]
	unsigned int ACK_GEN_CALL:1;		// [0]
};
 // IC3_IC_ENABLE_STATUS Register
struct I2C_IC3_IC_ENABLE_STATUS {
	unsigned int reserved:29;		// [31:3]
	unsigned int SLV_RX_DATA_LOST:1;		// [2]
	unsigned int SLV_DISABLED_WHILE_BUSY:1;		// [1]
	unsigned int IC_EN:1;		// [0]
};
 // IC3_IC_FS_SPKLEN Register
struct I2C_IC3_IC_FS_SPKLEN {
	unsigned int reserved:24;		// [31:8]
	unsigned int IC_FS_SPKLEN:8;		// [7:0]
};
 // IC3_IC_COMP_PARAM_1 Register
struct I2C_IC3_IC_COMP_PARAM_1 {
	unsigned int reserved:8;		// [31:24]
	unsigned int TX_BUFFER_DEPTH:8;		// [23:16]
	unsigned int RX_BUFFER_DEPTH:8;		// [15:8]
	unsigned int ADD_ENCODED_PARAMS:1;		// [7]
	unsigned int HAS_DMA:1;		// [6]
	unsigned int INTR_IO:1;		// [5]
	unsigned int HC_COUNT_VALUES:1;		// [4]
	unsigned int MAX_SPEED_MODE:2;		// [3:2]
	unsigned int APB_DATA_WIDTH:2;		// [1:0]
};
 // IC3_IC_COMP_VERSION Register
struct I2C_IC3_IC_COMP_VERSION {
	unsigned int IC_COMP_VERSION:32;		// [31:0]
};
 // IC3_IC_COMP_TYPE Register
struct I2C_IC3_IC_COMP_TYPE {
	unsigned int IC_COMP_TYPE:32;		// [31:0]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _I2C_REG_STRUCT_B_H */
