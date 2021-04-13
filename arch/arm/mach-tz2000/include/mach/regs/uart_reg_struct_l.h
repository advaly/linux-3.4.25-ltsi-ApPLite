/*
 * arch/arm/mach-tz2000/include/mach/regs/uart_reg_struct_l.h
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

#ifndef _UART_REG_STRUCT_L_H
#define _UART_REG_STRUCT_L_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // UA0_RBR_THR_DLL Register
struct UART_UA0_RBR_THR_DLL {
	unsigned int RBR_THR_DLL:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // UA0_IER_DLH Register
struct UART_UA0_IER_DLH {
	unsigned int ERBFI_DLH0:1;		// [0]
	unsigned int ETBEI_DLH1:1;		// [1]
	unsigned int ELSI_DLH2:1;		// [2]
	unsigned int EDSSI_DLH3:1;		// [3]
	unsigned int DLH64:3;		// [6:4]
	unsigned int PTIME_DLH7:1;		// [7]
	unsigned int reserved:24;		// [31:8]
};
 // UA0_FCR_IIR Register
struct UART_UA0_FCR_IIR {
	unsigned int IID0_FIFOE:1;		// [0]
	unsigned int IID1_RFIFOR:1;		// [1]
	unsigned int IID2_XFIFOR:1;		// [2]
	unsigned int IID3_DMAM:1;		// [3]
	unsigned int TET:2;		// [5:4]
	unsigned int FIFOSE_RCVR:2;		// [7:6]
	unsigned int reserved:24;		// [31:8]
};
 // UA0_LCR Register
struct UART_UA0_LCR {
	unsigned int DLS:2;		// [1:0]
	unsigned int STOP:1;		// [2]
	unsigned int PEN:1;		// [3]
	unsigned int EPS:1;		// [4]
	unsigned int SP:1;		// [5]
	unsigned int Break:1;		// [6]
	unsigned int DLAB:1;		// [7]
	unsigned int reserved:24;		// [31:8]
};
 // UA0_MCR Register
struct UART_UA0_MCR {
	unsigned int DTR:1;		// [0]
	unsigned int RTS:1;		// [1]
	unsigned int OUT1:1;		// [2]
	unsigned int OUT2:1;		// [3]
	unsigned int LoopBack:1;		// [4]
	unsigned int AFCE:1;		// [5]
	unsigned int SIRE:1;		// [6]
	unsigned int reserved:25;		// [31:7]
};
 // UA0_LSR Register
struct UART_UA0_LSR {
	unsigned int DR:1;		// [0]
	unsigned int OE:1;		// [1]
	unsigned int PE:1;		// [2]
	unsigned int FE:1;		// [3]
	unsigned int BI:1;		// [4]
	unsigned int THRE:1;		// [5]
	unsigned int TEMT:1;		// [6]
	unsigned int RFE:1;		// [7]
	unsigned int reserved:24;		// [31:8]
};
 // UA0_MSR Register
struct UART_UA0_MSR {
	unsigned int DCTS:1;		// [0]
	unsigned int DDSR:1;		// [1]
	unsigned int TERI:1;		// [2]
	unsigned int DDCD:1;		// [3]
	unsigned int CTS:1;		// [4]
	unsigned int DSR:1;		// [5]
	unsigned int RI:1;		// [6]
	unsigned int DCD:1;		// [7]
	unsigned int reserved:24;		// [31:8]
};
 // UA0_SCR Register
struct UART_UA0_SCR {
	unsigned int SCR:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // UA0_FAR Register
struct UART_UA0_FAR {
	unsigned int FAR:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // UA0_TFR Register
struct UART_UA0_TFR {
	unsigned int TFR:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // UA0_RFW Register
struct UART_UA0_RFW {
	unsigned int RFWD:8;		// [7:0]
	unsigned int RFPE:1;		// [8]
	unsigned int RFFE:1;		// [9]
	unsigned int reserved:22;		// [31:10]
};
 // UA0_USR Register
struct UART_UA0_USR {
	unsigned int BUSY:1;		// [0]
	unsigned int TFNF:1;		// [1]
	unsigned int TFE:1;		// [2]
	unsigned int RFNE:1;		// [3]
	unsigned int RFF:1;		// [4]
	unsigned int reserved:27;		// [31:5]
};
 // UA0_TFL Register
struct UART_UA0_TFL {
	unsigned int TFL:5;		// [4:0]
	unsigned int reserved:27;		// [31:5]
};
 // UA0_RFL Register
struct UART_UA0_RFL {
	unsigned int RFL:5;		// [4:0]
	unsigned int reserved:27;		// [31:5]
};
 // UA0_HTX Register
struct UART_UA0_HTX {
	unsigned int HTX:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // UA0_DMASA Register
struct UART_UA0_DMASA {
	unsigned int DMASA:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // UA0_CPR Register
struct UART_UA0_CPR {
	unsigned int APB_DATA_WIDTH:2;		// [1:0]
	unsigned int reserved3:2;		// [3:2]
	unsigned int AFCE_MODE:1;		// [4]
	unsigned int THRE_MODE:1;		// [5]
	unsigned int SIR_MODE:1;		// [6]
	unsigned int SIR_LP_MODE:1;		// [7]
	unsigned int ADDITIONAL_FEAT:1;		// [8]
	unsigned int FIFO_ACCESS:1;		// [9]
	unsigned int FIFO_STAT:1;		// [10]
	unsigned int SHADOW:1;		// [11]
	unsigned int UART_ADD_ENCODED_PARAMS:1;		// [12]
	unsigned int DMA_EXTRA:1;		// [13]
	unsigned int reserved2:2;		// [15:14]
	unsigned int FIFO_MODE:8;		// [23:16]
	unsigned int reserved:8;		// [31:24]
};
 // UA0_UCV Register
struct UART_UA0_UCV {
	unsigned int UART_Component_Version:32;		// [31:0]
};
 // UA0_CTR Register
struct UART_UA0_CTR {
	unsigned int Peripheral_ID:32;		// [31:0]
};
 // UA1_RBR_THR_DLL Register
struct UART_UA1_RBR_THR_DLL {
	unsigned int RBR_THR_DLL:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // UA1_IER_DLH Register
struct UART_UA1_IER_DLH {
	unsigned int ERBFI_DLH0:1;		// [0]
	unsigned int ETBEI_DLH1:1;		// [1]
	unsigned int ELSI_DLH2:1;		// [2]
	unsigned int EDSSI_DLH3:1;		// [3]
	unsigned int DLH64:3;		// [6:4]
	unsigned int PTIME_DLH7:1;		// [7]
	unsigned int reserved:24;		// [31:8]
};
 // UA1_FCR_IIR Register
struct UART_UA1_FCR_IIR {
	unsigned int IID0_FIFOE:1;		// [0]
	unsigned int IID1_RFIFOR:1;		// [1]
	unsigned int IID2_XFIFOR:1;		// [2]
	unsigned int IID3_DMAM:1;		// [3]
	unsigned int TET:2;		// [5:4]
	unsigned int FIFOSE_RCVR:2;		// [7:6]
	unsigned int reserved:24;		// [31:8]
};
 // UA1_LCR Register
struct UART_UA1_LCR {
	unsigned int DLS:2;		// [1:0]
	unsigned int STOP:1;		// [2]
	unsigned int PEN:1;		// [3]
	unsigned int EPS:1;		// [4]
	unsigned int SP:1;		// [5]
	unsigned int Break:1;		// [6]
	unsigned int DLAB:1;		// [7]
	unsigned int reserved:24;		// [31:8]
};
 // UA1_MCR Register
struct UART_UA1_MCR {
	unsigned int DTR:1;		// [0]
	unsigned int RTS:1;		// [1]
	unsigned int OUT1:1;		// [2]
	unsigned int OUT2:1;		// [3]
	unsigned int LoopBack:1;		// [4]
	unsigned int AFCE:1;		// [5]
	unsigned int SIRE:1;		// [6]
	unsigned int reserved:25;		// [31:7]
};
 // UA1_LSR Register
struct UART_UA1_LSR {
	unsigned int DR:1;		// [0]
	unsigned int OE:1;		// [1]
	unsigned int PE:1;		// [2]
	unsigned int FE:1;		// [3]
	unsigned int BI:1;		// [4]
	unsigned int THRE:1;		// [5]
	unsigned int TEMT:1;		// [6]
	unsigned int RFE:1;		// [7]
	unsigned int reserved:24;		// [31:8]
};
 // UA1_MSR Register
struct UART_UA1_MSR {
	unsigned int DCTS:1;		// [0]
	unsigned int DDSR:1;		// [1]
	unsigned int TERI:1;		// [2]
	unsigned int DDCD:1;		// [3]
	unsigned int CTS:1;		// [4]
	unsigned int DSR:1;		// [5]
	unsigned int RI:1;		// [6]
	unsigned int DCD:1;		// [7]
	unsigned int reserved:24;		// [31:8]
};
 // UA1_SCR Register
struct UART_UA1_SCR {
	unsigned int SCR:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // UA1_FAR Register
struct UART_UA1_FAR {
	unsigned int FAR:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // UA1_TFR Register
struct UART_UA1_TFR {
	unsigned int TFR:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // UA1_RFW Register
struct UART_UA1_RFW {
	unsigned int RFWD:8;		// [7:0]
	unsigned int RFPE:1;		// [8]
	unsigned int RFFE:1;		// [9]
	unsigned int reserved:22;		// [31:10]
};
 // UA1_USR Register
struct UART_UA1_USR {
	unsigned int BUSY:1;		// [0]
	unsigned int TFNF:1;		// [1]
	unsigned int TFE:1;		// [2]
	unsigned int RFNE:1;		// [3]
	unsigned int RFF:1;		// [4]
	unsigned int reserved:27;		// [31:5]
};
 // UA1_TFL Register
struct UART_UA1_TFL {
	unsigned int TFL:5;		// [4:0]
	unsigned int reserved:27;		// [31:5]
};
 // UA1_RFL Register
struct UART_UA1_RFL {
	unsigned int RFL:5;		// [4:0]
	unsigned int reserved:27;		// [31:5]
};
 // UA1_HTX Register
struct UART_UA1_HTX {
	unsigned int HTX:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // UA1_DMASA Register
struct UART_UA1_DMASA {
	unsigned int DMASA:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // UA1_CPR Register
struct UART_UA1_CPR {
	unsigned int APB_DATA_WIDTH:2;		// [1:0]
	unsigned int reserved3:2;		// [3:2]
	unsigned int AFCE_MODE:1;		// [4]
	unsigned int THRE_MODE:1;		// [5]
	unsigned int SIR_MODE:1;		// [6]
	unsigned int SIR_LP_MODE:1;		// [7]
	unsigned int ADDITIONAL_FEAT:1;		// [8]
	unsigned int FIFO_ACCESS:1;		// [9]
	unsigned int FIFO_STAT:1;		// [10]
	unsigned int SHADOW:1;		// [11]
	unsigned int UART_ADD_ENCODED_PARAMS:1;		// [12]
	unsigned int DMA_EXTRA:1;		// [13]
	unsigned int reserved2:2;		// [15:14]
	unsigned int FIFO_MODE:8;		// [23:16]
	unsigned int reserved:8;		// [31:24]
};
 // UA1_UCV Register
struct UART_UA1_UCV {
	unsigned int UART_Component_Version:32;		// [31:0]
};
 // UA1_CTR Register
struct UART_UA1_CTR {
	unsigned int Peripheral_ID:32;		// [31:0]
};
 // UA2_RBR_THR_DLL Register
struct UART_UA2_RBR_THR_DLL {
	unsigned int RBR_THR_DLL:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // UA2_IER_DLH Register
struct UART_UA2_IER_DLH {
	unsigned int ERBFI_DLH0:1;		// [0]
	unsigned int ETBEI_DLH1:1;		// [1]
	unsigned int ELSI_DLH2:1;		// [2]
	unsigned int EDSSI_DLH3:1;		// [3]
	unsigned int DLH64:3;		// [6:4]
	unsigned int PTIME_DLH7:1;		// [7]
	unsigned int reserved:24;		// [31:8]
};
 // UA2_FCR_IIR Register
struct UART_UA2_FCR_IIR {
	unsigned int IID0_FIFOE:1;		// [0]
	unsigned int IID1_RFIFOR:1;		// [1]
	unsigned int IID2_XFIFOR:1;		// [2]
	unsigned int IID3_DMAM:1;		// [3]
	unsigned int TET:2;		// [5:4]
	unsigned int FIFOSE_RCVR:2;		// [7:6]
	unsigned int reserved:24;		// [31:8]
};
 // UA2_LCR Register
struct UART_UA2_LCR {
	unsigned int DLS:2;		// [1:0]
	unsigned int STOP:1;		// [2]
	unsigned int PEN:1;		// [3]
	unsigned int EPS:1;		// [4]
	unsigned int SP:1;		// [5]
	unsigned int Break:1;		// [6]
	unsigned int DLAB:1;		// [7]
	unsigned int reserved:24;		// [31:8]
};
 // UA2_MCR Register
struct UART_UA2_MCR {
	unsigned int DTR:1;		// [0]
	unsigned int RTS:1;		// [1]
	unsigned int OUT1:1;		// [2]
	unsigned int OUT2:1;		// [3]
	unsigned int LoopBack:1;		// [4]
	unsigned int AFCE:1;		// [5]
	unsigned int SIRE:1;		// [6]
	unsigned int reserved:25;		// [31:7]
};
 // UA2_LSR Register
struct UART_UA2_LSR {
	unsigned int DR:1;		// [0]
	unsigned int OE:1;		// [1]
	unsigned int PE:1;		// [2]
	unsigned int FE:1;		// [3]
	unsigned int BI:1;		// [4]
	unsigned int THRE:1;		// [5]
	unsigned int TEMT:1;		// [6]
	unsigned int RFE:1;		// [7]
	unsigned int reserved:24;		// [31:8]
};
 // UA2_MSR Register
struct UART_UA2_MSR {
	unsigned int DCTS:1;		// [0]
	unsigned int DDSR:1;		// [1]
	unsigned int TERI:1;		// [2]
	unsigned int DDCD:1;		// [3]
	unsigned int CTS:1;		// [4]
	unsigned int DSR:1;		// [5]
	unsigned int RI:1;		// [6]
	unsigned int DCD:1;		// [7]
	unsigned int reserved:24;		// [31:8]
};
 // UA2_SCR Register
struct UART_UA2_SCR {
	unsigned int SCR:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // UA2_FAR Register
struct UART_UA2_FAR {
	unsigned int FAR:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // UA2_TFR Register
struct UART_UA2_TFR {
	unsigned int TFR:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // UA2_RFW Register
struct UART_UA2_RFW {
	unsigned int RFWD:8;		// [7:0]
	unsigned int RFPE:1;		// [8]
	unsigned int RFFE:1;		// [9]
	unsigned int reserved:22;		// [31:10]
};
 // UA2_USR Register
struct UART_UA2_USR {
	unsigned int BUSY:1;		// [0]
	unsigned int TFNF:1;		// [1]
	unsigned int TFE:1;		// [2]
	unsigned int RFNE:1;		// [3]
	unsigned int RFF:1;		// [4]
	unsigned int reserved:27;		// [31:5]
};
 // UA2_TFL Register
struct UART_UA2_TFL {
	unsigned int TFL:5;		// [4:0]
	unsigned int reserved:27;		// [31:5]
};
 // UA2_RFL Register
struct UART_UA2_RFL {
	unsigned int RFL:5;		// [4:0]
	unsigned int reserved:27;		// [31:5]
};
 // UA2_HTX Register
struct UART_UA2_HTX {
	unsigned int HTX:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // UA2_DMASA Register
struct UART_UA2_DMASA {
	unsigned int DMASA:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // UA2_CPR Register
struct UART_UA2_CPR {
	unsigned int APB_DATA_WIDTH:2;		// [1:0]
	unsigned int reserved3:2;		// [3:2]
	unsigned int AFCE_MODE:1;		// [4]
	unsigned int THRE_MODE:1;		// [5]
	unsigned int SIR_MODE:1;		// [6]
	unsigned int SIR_LP_MODE:1;		// [7]
	unsigned int ADDITIONAL_FEAT:1;		// [8]
	unsigned int FIFO_ACCESS:1;		// [9]
	unsigned int FIFO_STAT:1;		// [10]
	unsigned int SHADOW:1;		// [11]
	unsigned int UART_ADD_ENCODED_PARAMS:1;		// [12]
	unsigned int DMA_EXTRA:1;		// [13]
	unsigned int reserved2:2;		// [15:14]
	unsigned int FIFO_MODE:8;		// [23:16]
	unsigned int reserved:8;		// [31:24]
};
 // UA2_UCV Register
struct UART_UA2_UCV {
	unsigned int UART_Component_Version:32;		// [31:0]
};
 // UA2_CTR Register
struct UART_UA2_CTR {
	unsigned int Peripheral_ID:32;		// [31:0]
};
 // UA3_RBR_THR_DLL Register
struct UART_UA3_RBR_THR_DLL {
	unsigned int RBR_THR_DLL:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // UA3_IER_DLH Register
struct UART_UA3_IER_DLH {
	unsigned int ERBFI_DLH0:1;		// [0]
	unsigned int ETBEI_DLH1:1;		// [1]
	unsigned int ELSI_DLH2:1;		// [2]
	unsigned int EDSSI_DLH3:1;		// [3]
	unsigned int DLH64:3;		// [6:4]
	unsigned int PTIME_DLH7:1;		// [7]
	unsigned int reserved:24;		// [31:8]
};
 // UA3_FCR_IIR Register
struct UART_UA3_FCR_IIR {
	unsigned int IID0_FIFOE:1;		// [0]
	unsigned int IID1_RFIFOR:1;		// [1]
	unsigned int IID2_XFIFOR:1;		// [2]
	unsigned int IID3_DMAM:1;		// [3]
	unsigned int TET:2;		// [5:4]
	unsigned int FIFOSE_RCVR:2;		// [7:6]
	unsigned int reserved:24;		// [31:8]
};
 // UA3_LCR Register
struct UART_UA3_LCR {
	unsigned int DLS:2;		// [1:0]
	unsigned int STOP:1;		// [2]
	unsigned int PEN:1;		// [3]
	unsigned int EPS:1;		// [4]
	unsigned int SP:1;		// [5]
	unsigned int Break:1;		// [6]
	unsigned int DLAB:1;		// [7]
	unsigned int reserved:24;		// [31:8]
};
 // UA3_MCR Register
struct UART_UA3_MCR {
	unsigned int DTR:1;		// [0]
	unsigned int RTS:1;		// [1]
	unsigned int OUT1:1;		// [2]
	unsigned int OUT2:1;		// [3]
	unsigned int LoopBack:1;		// [4]
	unsigned int AFCE:1;		// [5]
	unsigned int SIRE:1;		// [6]
	unsigned int reserved:25;		// [31:7]
};
 // UA3_LSR Register
struct UART_UA3_LSR {
	unsigned int DR:1;		// [0]
	unsigned int OE:1;		// [1]
	unsigned int PE:1;		// [2]
	unsigned int FE:1;		// [3]
	unsigned int BI:1;		// [4]
	unsigned int THRE:1;		// [5]
	unsigned int TEMT:1;		// [6]
	unsigned int RFE:1;		// [7]
	unsigned int reserved:24;		// [31:8]
};
 // UA3_MSR Register
struct UART_UA3_MSR {
	unsigned int DCTS:1;		// [0]
	unsigned int DDSR:1;		// [1]
	unsigned int TERI:1;		// [2]
	unsigned int DDCD:1;		// [3]
	unsigned int CTS:1;		// [4]
	unsigned int DSR:1;		// [5]
	unsigned int RI:1;		// [6]
	unsigned int DCD:1;		// [7]
	unsigned int reserved:24;		// [31:8]
};
 // UA3_SCR Register
struct UART_UA3_SCR {
	unsigned int SCR:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // UA3_FAR Register
struct UART_UA3_FAR {
	unsigned int FAR:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // UA3_TFR Register
struct UART_UA3_TFR {
	unsigned int TFR:8;		// [7:0]
	unsigned int reserved:24;		// [31:8]
};
 // UA3_RFW Register
struct UART_UA3_RFW {
	unsigned int RFWD:8;		// [7:0]
	unsigned int RFPE:1;		// [8]
	unsigned int RFFE:1;		// [9]
	unsigned int reserved:22;		// [31:10]
};
 // UA3_USR Register
struct UART_UA3_USR {
	unsigned int BUSY:1;		// [0]
	unsigned int TFNF:1;		// [1]
	unsigned int TFE:1;		// [2]
	unsigned int RFNE:1;		// [3]
	unsigned int RFF:1;		// [4]
	unsigned int reserved:27;		// [31:5]
};
 // UA3_TFL Register
struct UART_UA3_TFL {
	unsigned int TFL:5;		// [4:0]
	unsigned int reserved:27;		// [31:5]
};
 // UA3_RFL Register
struct UART_UA3_RFL {
	unsigned int RFL:5;		// [4:0]
	unsigned int reserved:27;		// [31:5]
};
 // UA3_HTX Register
struct UART_UA3_HTX {
	unsigned int HTX:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // UA3_DMASA Register
struct UART_UA3_DMASA {
	unsigned int DMASA:1;		// [0]
	unsigned int reserved:31;		// [31:1]
};
 // UA3_CPR Register
struct UART_UA3_CPR {
	unsigned int APB_DATA_WIDTH:2;		// [1:0]
	unsigned int reserved3:2;		// [3:2]
	unsigned int AFCE_MODE:1;		// [4]
	unsigned int THRE_MODE:1;		// [5]
	unsigned int SIR_MODE:1;		// [6]
	unsigned int SIR_LP_MODE:1;		// [7]
	unsigned int ADDITIONAL_FEAT:1;		// [8]
	unsigned int FIFO_ACCESS:1;		// [9]
	unsigned int FIFO_STAT:1;		// [10]
	unsigned int SHADOW:1;		// [11]
	unsigned int UART_ADD_ENCODED_PARAMS:1;		// [12]
	unsigned int DMA_EXTRA:1;		// [13]
	unsigned int reserved2:2;		// [15:14]
	unsigned int FIFO_MODE:8;		// [23:16]
	unsigned int reserved:8;		// [31:24]
};
 // UA3_UCV Register
struct UART_UA3_UCV {
	unsigned int UART_Component_Version:32;		// [31:0]
};
 // UA3_CTR Register
struct UART_UA3_CTR {
	unsigned int Peripheral_ID:32;		// [31:0]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _UART_REG_STRUCT_L_H */
