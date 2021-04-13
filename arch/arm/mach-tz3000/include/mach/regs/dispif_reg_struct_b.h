/*
 * arch/arm/mach-tz3000/include/mach/regs/dispif_reg_struct_b.h
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

#ifndef _DISPIF_REG_STRUCT_B_H
#define _DISPIF_REG_STRUCT_B_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // IRQ_HBLK_R_MODE Register
struct DISPIF_IRQ_HBLK_R_MODE {
	unsigned int irq_hblk_r_mode:2;		// [31:30]
	unsigned int reserved:1;		// [29]
	unsigned int irq_hblk_r_vcnt:13;		// [28:16]
	unsigned int irq_hblk_r_hcnt:16;		// [15:0]
};
 // IRQ_HBLK_R_MODE2 Register
struct DISPIF_IRQ_HBLK_R_MODE2 {
	unsigned int irq_hblk_r_mode2:2;		// [31:30]
	unsigned int reserved:1;		// [29]
	unsigned int irq_hblk_r_vcnt2:13;		// [28:16]
	unsigned int irq_hblk_r_hcnt2:16;		// [15:0]
};
 // IRQ_HBLK_R_MODE3 Register
struct DISPIF_IRQ_HBLK_R_MODE3 {
	unsigned int irq_hblk_r_mode3:2;		// [31:30]
	unsigned int reserved:1;		// [29]
	unsigned int irq_hblk_r_vcnt3:13;		// [28:16]
	unsigned int irq_hblk_r_hcnt3:16;		// [15:0]
};
 // IRQ_VBLK_R_MODE Register
struct DISPIF_IRQ_VBLK_R_MODE {
	unsigned int reserved:3;		// [31:29]
	unsigned int irq_vblk_r_vcnt:13;		// [28:16]
	unsigned int irq_hblk_r_hcnt:16;		// [15:0]
};
 // IRQ_VBLK_F_MODE Register
struct DISPIF_IRQ_VBLK_F_MODE {
	unsigned int reserved:3;		// [31:29]
	unsigned int irq_vblk_f_vcnt:13;		// [28:16]
	unsigned int irq_hblk_f_hcnt:16;		// [15:0]
};
 // MDI_GO Register
struct DISPIF_MDI_GO {
	unsigned int reserved:3;		// [31:29]
	unsigned int mdi_go_vcnt:13;		// [28:16]
	unsigned int mdi_go_hcnt:16;		// [15:0]
};
 // HV_MAX Register
struct DISPIF_HV_MAX {
	unsigned int reserved:3;		// [31:29]
	unsigned int vcnt_max:13;		// [28:16]
	unsigned int hcnt_max:16;		// [15:0]
};
 // HV_DLY Register
struct DISPIF_HV_DLY {
	unsigned int reserved:3;		// [31:29]
	unsigned int v_dly:13;		// [28:16]
	unsigned int h_dly:16;		// [15:0]
};
 // HBLK Register
struct DISPIF_HBLK {
	unsigned int hblk_f:16;		// [31:16]
	unsigned int hblk_r:16;		// [15:0]
};
 // HBLK2 Register
struct DISPIF_HBLK2 {
	unsigned int hblk2_f:16;		// [31:16]
	unsigned int hblk2_r:16;		// [15:0]
};
 // HD Register
struct DISPIF_HD {
	unsigned int hd_f:16;		// [31:16]
	unsigned int hd_r:16;		// [15:0]
};
 // HD2 Register
struct DISPIF_HD2 {
	unsigned int hd2_f:16;		// [31:16]
	unsigned int hd2_r:16;		// [15:0]
};
 // VBLK Register
struct DISPIF_VBLK {
	unsigned int reserved:3;		// [31:29]
	unsigned int vblk_f:13;		// [28:16]
	unsigned int reserved2:3;		// [15:13]
	unsigned int vblk_r:13;		// [12:0]
};
 // VD_R Register
struct DISPIF_VD_R {
	unsigned int reserved:3;		// [31:29]
	unsigned int vd_r_vcnt:13;		// [28:16]
	unsigned int vd_r_hcnt:16;		// [15:0]
};
 // VD_F Register
struct DISPIF_VD_F {
	unsigned int reserved:3;		// [31:29]
	unsigned int vd_f_vcnt:13;		// [28:16]
	unsigned int vd_f_hcnt:16;		// [15:0]
};
 // DTG_START Register
struct DISPIF_DTG_START {
	unsigned int reserved:31;		// [31:1]
	unsigned int dtg_start:1;		// [0]
};
 // DTG_STOP Register
struct DISPIF_DTG_STOP {
	unsigned int reserved:31;		// [31:1]
	unsigned int dtg_stop:1;		// [0]
};
 // DTG_FORCE_STOP Register
struct DISPIF_DTG_FORCE_STOP {
	unsigned int reserved:31;		// [31:1]
	unsigned int dtg_force_stop:1;		// [0]
};
 // HS_0 Register
struct DISPIF_HS_0 {
	unsigned int reserved:31;		// [31:1]
	unsigned int hs_0_en:1;		// [0]
};
 // HS_0_SET1 Register
struct DISPIF_HS_0_SET1 {
	unsigned int reserved:21;		// [31:11]
	unsigned int hs0_hd_set:3;		// [10:8]
	unsigned int reserved2:1;		// [7]
	unsigned int hs0_hbkp_set:3;		// [6:4]
	unsigned int reserved3:1;		// [3]
	unsigned int hs0_hfrp_set:3;		// [2:0]
};
 // HS_0_SET2 Register
struct DISPIF_HS_0_SET2 {
	unsigned int reserved:21;		// [31:11]
	unsigned int hs0_hd_set2:3;		// [10:8]
	unsigned int reserved2:1;		// [7]
	unsigned int hs0_hbkp_set2:3;		// [6:4]
	unsigned int reserved3:1;		// [3]
	unsigned int hs0_hfrp_set2:3;		// [2:0]
};
 // IRQ_EN Register
struct DISPIF_IRQ_EN {
	unsigned int reserved:7;		// [31:25]
	unsigned int vsync_en:1;		// [24]
	unsigned int reserved2:3;		// [23:21]
	unsigned int vblk_re_en:1;		// [20]
	unsigned int reserved3:3;		// [19:17]
	unsigned int hblk_r_en3:1;		// [16]
	unsigned int reserved4:3;		// [15:13]
	unsigned int hblk_r_en2:1;		// [12]
	unsigned int reserved5:3;		// [11:9]
	unsigned int hblk_r_en:1;		// [8]
	unsigned int reserved6:3;		// [7:5]
	unsigned int vblk_r_en:1;		// [4]
	unsigned int reserved7:3;		// [3:1]
	unsigned int vblk_f_en:1;		// [0]
};
 // IRQ_STAT Register
struct DISPIF_IRQ_STAT {
	unsigned int reserved:7;		// [31:25]
	unsigned int stat_vsync_en:1;		// [24]
	unsigned int reserved2:3;		// [23:21]
	unsigned int stat_vblk_re_en:1;		// [20]
	unsigned int reserved3:3;		// [19:17]
	unsigned int stat_hblk_r_en3:1;		// [16]
	unsigned int reserved4:3;		// [15:13]
	unsigned int stat_hblk_r_en2:1;		// [12]
	unsigned int reserved5:3;		// [11:9]
	unsigned int stat_hblk_r_en:1;		// [8]
	unsigned int reserved6:3;		// [7:5]
	unsigned int stat_vblk_r_en:1;		// [4]
	unsigned int reserved7:3;		// [3:1]
	unsigned int stat_vblk_f_en:1;		// [0]
};
 // DTG_STAT Register
struct DISPIF_DTG_STAT {
	unsigned int reserved:28;		// [31:4]
	unsigned int stat_dtg:4;		// [3:0]
};
 // DATA_STAT Register
struct DISPIF_DATA_STAT {
	unsigned int stat_act:1;		// [31]
	unsigned int reserved:2;		// [30:29]
	unsigned int stat_vcnt:13;		// [28:16]
	unsigned int stat_hcnt:16;		// [15:0]
};
 // DSI_PPI_STARTCNTRL Register
struct DISPIF_DSI_PPI_STARTCNTRL {
	unsigned int reserved:31;		// [31:1]
	unsigned int START:1;		// [0]
};
 // DSI_PPI_STATUS Register
struct DISPIF_DSI_PPI_STATUS {
	unsigned int reserved:31;		// [31:1]
	unsigned int BUSY:1;		// [0]
};
 // DSI_PPI_LINEINTCNT Register
struct DISPIF_DSI_PPI_LINEINTCNT {
	unsigned int reserved:16;		// [31:16]
	unsigned int LINEINITCNT:16;		// [15:0]
};
 // DSI_PPI_LPTXTIMECNT Register
struct DISPIF_DSI_PPI_LPTXTIMECNT {
	unsigned int reserved:21;		// [31:11]
	unsigned int LPTXTIMECNT:11;		// [10:0]
};
 // DSI_PPI_TCLK_HEADERCNT Register
struct DISPIF_DSI_PPI_TCLK_HEADERCNT {
	unsigned int reserved:16;		// [31:16]
	unsigned int TCLK_ZEROCNT:8;		// [15:8]
	unsigned int reserved2:1;		// [7]
	unsigned int TCLK_PREPARECNT:7;		// [6:0]
};
 // DSI_PPI_TCLK_TRAILCNT Register
struct DISPIF_DSI_PPI_TCLK_TRAILCNT {
	unsigned int reserved:24;		// [31:8]
	unsigned int TCLK_TRAILCNT:8;		// [7:0]
};
 // DSI_PPI_THS_HEADERCNT Register
struct DISPIF_DSI_PPI_THS_HEADERCNT {
	unsigned int reserved:17;		// [31:15]
	unsigned int THS_ZEROCNT:7;		// [14:8]
	unsigned int reserved2:1;		// [7]
	unsigned int THS_PREPARECNT:7;		// [6:0]
};
 // DSI_PPI_TWAKEUP Register
struct DISPIF_DSI_PPI_TWAKEUP {
	unsigned int reserved:16;		// [31:16]
	unsigned int TWAKEUPCNT:16;		// [15:0]
};
 // DSI_PPI_TCLK_POSTCNT Register
struct DISPIF_DSI_PPI_TCLK_POSTCNT {
	unsigned int reserved:21;		// [31:11]
	unsigned int TCLK_POSTCNT:11;		// [10:0]
};
 // DSI_PPI_THS_TRAILCNT Register
struct DISPIF_DSI_PPI_THS_TRAILCNT {
	unsigned int reserved:28;		// [31:4]
	unsigned int THS_TRAILCNT:4;		// [3:0]
};
 // DSI_PPI_HSTXVREGCNT Register
struct DISPIF_DSI_PPI_HSTXVREGCNT {
	unsigned int reserved:16;		// [31:16]
	unsigned int HSTXVREGCNT:16;		// [15:0]
};
 // DSI_PPI_HSTXVREGTN Register
struct DISPIF_DSI_PPI_HSTXVREGTN {
	unsigned int reserved:27;		// [31:5]
	unsigned int D3M_HSTXVREGEN:1;		// [4]
	unsigned int D2M_HSTXVREGEN:1;		// [3]
	unsigned int D1M_HSTXVREGEN:1;		// [2]
	unsigned int D0M_HSTXVREGEN:1;		// [1]
	unsigned int CLM_HSTXVREGEN:1;		// [0]
};
 // DSI_PPI_TXOPTIONCNTRL Register
struct DISPIF_DSI_PPI_TXOPTIONCNTRL {
	unsigned int reserved:31;		// [31:1]
	unsigned int CONTCLKMOD:1;		// [0]
};
 // DSI_PPI_BTACNTRL1 Register
struct DISPIF_DSI_PPI_BTACNTRL1 {
	unsigned int reserved:5;		// [31:27]
	unsigned int TXTAGOCNT:11;		// [26:16]
	unsigned int reserved2:5;		// [15:11]
	unsigned int RXTASURECNT:11;		// [10:0]
};
 // DSI_DCS Register
struct DISPIF_DSI_DCS {
	unsigned int reserved:16;		// [31:16]
	unsigned int DCS1:8;		// [15:8]
	unsigned int DCS0:8;		// [7:0]
};
 // DSI_CONTROL Register
struct DISPIF_DSI_CONTROL {
	unsigned int reserved:18;		// [31:14]
	unsigned int PrToEn:1;		// [13]
	unsigned int TaToEn:1;		// [12]
	unsigned int LrxToEn:1;		// [11]
	unsigned int HtxToEn:1;		// [10]
	unsigned int CntDis:1;		// [9]
	unsigned int EccDis:1;		// [8]
	unsigned int TxMd:1;		// [7]
	unsigned int CrcDis:1;		// [6]
	unsigned int HsCkMd:1;		// [5]
	unsigned int reserved2:2;		// [4:3]
	unsigned int NOL:2;		// [2:1]
	unsigned int EoTDis:1;		// [0]
};
 // DSI_STATUS Register
struct DISPIF_DSI_STATUS {
	unsigned int reserved:11;		// [31:21]
	unsigned int CQ1SKIP:1;		// [20]
	unsigned int LPFl:1;		// [19]
	unsigned int LPAF:1;		// [18]
	unsigned int LPAE:1;		// [17]
	unsigned int LPEm:1;		// [16]
	unsigned int QSw:1;		// [15]
	unsigned int Q1Fl:1;		// [14]
	unsigned int Q1AF:1;		// [13]
	unsigned int Q1AE:1;		// [12]
	unsigned int Q1Em:1;		// [11]
	unsigned int WSyn:1;		// [10]
	unsigned int TxAct:1;		// [9]
	unsigned int RxAct:1;		// [8]
	unsigned int RxAF:1;		// [7]
	unsigned int RxAE:1;		// [6]
	unsigned int RxEm:1;		// [5]
	unsigned int Q0Fl:1;		// [4]
	unsigned int Q0AF:1;		// [3]
	unsigned int Q0AE:1;		// [2]
	unsigned int Q0Em:1;		// [1]
	unsigned int Hlt:1;		// [0]
};
 // DSI_INT Register
struct DISPIF_DSI_INT {
	unsigned int IntSw7:1;		// [31]
	unsigned int IntSw6:1;		// [30]
	unsigned int IntSw5:1;		// [29]
	unsigned int IntSw4:1;		// [28]
	unsigned int IntSw3:1;		// [27]
	unsigned int IntSw2:1;		// [26]
	unsigned int IntSw1:1;		// [25]
	unsigned int IntSw0:1;		// [24]
	unsigned int IntLPFl:1;		// [23]
	unsigned int IntLPAF:1;		// [22]
	unsigned int IntLPAE:1;		// [21]
	unsigned int IntLPEm:1;		// [20]
	unsigned int reserved:1;		// [19]
	unsigned int IntACK:1;		// [18]
	unsigned int IntQ1Fl:1;		// [17]
	unsigned int IntQ1AF:1;		// [16]
	unsigned int IntQ1AE:1;		// [15]
	unsigned int IntQ1Em:1;		// [14]
	unsigned int reserved2:1;		// [13]
	unsigned int IntRxEd:1;		// [12]
	unsigned int IntTe:1;		// [11]
	unsigned int IntRxAF:1;		// [10]
	unsigned int IntRxAE:1;		// [9]
	unsigned int IntRxEm:1;		// [8]
	unsigned int IntQ0Fl:1;		// [7]
	unsigned int IntQ0AF:1;		// [6]
	unsigned int IntQ0AE:1;		// [5]
	unsigned int IntQ0Em:1;		// [4]
	unsigned int IntHlt:1;		// [3]
	unsigned int IntEr:1;		// [2]
	unsigned int IntRxEr:1;		// [1]
	unsigned int IntAckEr:1;		// [0]
};
 // DSI_INT_ENA Register
struct DISPIF_DSI_INT_ENA {
	unsigned int reserved:8;		// [31:24]
	unsigned int IEnLPFl:1;		// [23]
	unsigned int IEnLPAF:1;		// [22]
	unsigned int IEnLPAE:1;		// [21]
	unsigned int IEnLPEm:1;		// [20]
	unsigned int reserved2:1;		// [19]
	unsigned int IEnAk:1;		// [18]
	unsigned int IEnQ1Fl:1;		// [17]
	unsigned int IEnAF:1;		// [16]
	unsigned int IEnAE:1;		// [15]
	unsigned int IEnQ1Em:1;		// [14]
	unsigned int IEnSw:1;		// [13]
	unsigned int IEnRxEd:1;		// [12]
	unsigned int IEnTe:1;		// [11]
	unsigned int IEnRxAF:1;		// [10]
	unsigned int IEnRxAE:1;		// [9]
	unsigned int IEnRxEm:1;		// [8]
	unsigned int IEnQ0Fl:1;		// [7]
	unsigned int IEnQ0AF:1;		// [6]
	unsigned int IEnQ0AE:1;		// [5]
	unsigned int IEnQ0Em:1;		// [4]
	unsigned int IEnHlt:1;		// [3]
	unsigned int IEnEr:1;		// [2]
	unsigned int IEnRxEr:1;		// [1]
	unsigned int IEnAkEr:1;		// [0]
};
 // DSI_HTX_TO Register
struct DISPIF_DSI_HTX_TO {
	unsigned int reserved:8;		// [31:24]
	unsigned int HTX_TO:24;		// [23:0]
};
 // DSI_LRXH_TO Register
struct DISPIF_DSI_LRXH_TO {
	unsigned int reserved:8;		// [31:24]
	unsigned int LRXH_TO:24;		// [23:0]
};
 // DSI_TA_TO Register
struct DISPIF_DSI_TA_TO {
	unsigned int reserved:8;		// [31:24]
	unsigned int TA_TO:24;		// [23:0]
};
 // DSI_PR_TO Register
struct DISPIF_DSI_PR_TO {
	unsigned int reserved:8;		// [31:24]
	unsigned int PR_TO:24;		// [23:0]
};
 // DSI_SYNC_TO Register
struct DISPIF_DSI_SYNC_TO {
	unsigned int reserved:8;		// [31:24]
	unsigned int DSI_SYNC_TO:24;		// [23:0]
};
 // DSI_RXFIFO Register
struct DISPIF_DSI_RXFIFO {
	unsigned int RXDATA:32;		// [31:0]
};
 // DSI_ACKERR_INTEN Register
struct DISPIF_DSI_ACKERR_INTEN {
	unsigned int reserved:16;		// [31:16]
	unsigned int ACKERR_REPORT:16;		// [15:0]
};
 // DSI_ACKERR_INTENA Register
struct DISPIF_DSI_ACKERR_INTENA {
	unsigned int reserved:16;		// [31:16]
	unsigned int ACKERR_INTENA:16;		// [15:0]
};
 // DSI_ACKERR_HALT Register
struct DISPIF_DSI_ACKERR_HALT {
	unsigned int reserved:16;		// [31:16]
	unsigned int ACKERR_HALT:16;		// [15:0]
};
 // DSI_RXERR Register
struct DISPIF_DSI_RXERR {
	unsigned int reserved:11;		// [31:21]
	unsigned int TATO:1;		// [20]
	unsigned int RxHTo:1;		// [19]
	unsigned int reserved2:1;		// [18]
	unsigned int FOvrFlw:1;		// [17]
	unsigned int reserved3:1;		// [16]
	unsigned int ERROR_REPORT_MASTER:16;		// [15:0]
};
 // DSI_RXERR_INTENA Register
struct DISPIF_DSI_RXERR_INTENA {
	unsigned int reserved:11;		// [31:21]
	unsigned int IEnTATO:1;		// [20]
	unsigned int IEnRxHTo:1;		// [19]
	unsigned int reserved2:1;		// [18]
	unsigned int IEnFOvrFlw:1;		// [17]
	unsigned int reserved3:1;		// [16]
	unsigned int ERROR_REPORT_MASTER_INTENA:16;		// [15:0]
};
 // DSI_RXERR_HALT Register
struct DISPIF_DSI_RXERR_HALT {
	unsigned int reserved:11;		// [31:21]
	unsigned int HltTATO:1;		// [20]
	unsigned int HltRxHTo:1;		// [19]
	unsigned int reserved2:1;		// [18]
	unsigned int HltFOvrFlw:1;		// [17]
	unsigned int reserved3:1;		// [16]
	unsigned int ERROR_REPORT_MASTER_HALT:16;		// [15:0]
};
 // DSI_ERR Register
struct DISPIF_DSI_ERR {
	unsigned int reserved:21;		// [31:11]
	unsigned int LPWrEr:1;		// [10]
	unsigned int LTxBrk:1;		// [9]
	unsigned int WCEr:1;		// [8]
	unsigned int SynTo:1;		// [7]
	unsigned int RxFRdEr:1;		// [6]
	unsigned int TeEr:1;		// [5]
	unsigned int QUnk:1;		// [4]
	unsigned int QWrEr:1;		// [3]
	unsigned int HTxTo:1;		// [2]
	unsigned int HTxBrk:1;		// [1]
	unsigned int Cntn:1;		// [0]
};
 // DSI_ERR_INTENA Register
struct DISPIF_DSI_ERR_INTENA {
	unsigned int reserved:21;		// [31:11]
	unsigned int IEnLPWrEr:1;		// [10]
	unsigned int IEnLTxBrk:1;		// [9]
	unsigned int IEnWCEr:1;		// [8]
	unsigned int IEnSynTo:1;		// [7]
	unsigned int IEnRxFRdEr:1;		// [6]
	unsigned int IEnTeEr:1;		// [5]
	unsigned int IEnQUnk:1;		// [4]
	unsigned int IEnQWEr:1;		// [3]
	unsigned int IEnHTxTo:1;		// [2]
	unsigned int IEnHTxBrk:1;		// [1]
	unsigned int IEnCntn:1;		// [0]
};
 // DSI_ERR_HALT Register
struct DISPIF_DSI_ERR_HALT {
	unsigned int reserved:21;		// [31:11]
	unsigned int HltLPWEr:1;		// [10]
	unsigned int HltLTxBrk:1;		// [9]
	unsigned int HltWCEr:1;		// [8]
	unsigned int HltSynTo:1;		// [7]
	unsigned int HltRxFRdEr:1;		// [6]
	unsigned int HltTeEr:1;		// [5]
	unsigned int HltQUnk:1;		// [4]
	unsigned int HltQWEr:1;		// [3]
	unsigned int HltHTxTo:1;		// [2]
	unsigned int HltHTxBrk:1;		// [1]
	unsigned int HltCntn:1;		// [0]
};
 // DSI_CQ0 Register
struct DISPIF_DSI_CQ0 {
	unsigned int COMMAND0:32;		// [31:0]
};
 // DSI_RESET Register
struct DISPIF_DSI_RESET {
	unsigned int reserved:26;		// [31:6]
	unsigned int RstLPF:1;		// [5]
	unsigned int RstRxF:1;		// [4]
	unsigned int RstQ1:1;		// [3]
	unsigned int RstQ0:1;		// [2]
	unsigned int RstCnf:1;		// [1]
	unsigned int reserved2:1;		// [0]
};
 // DSI_CONTINUE Register
struct DISPIF_DSI_CONTINUE {
	unsigned int CONTINUE:32;		// [31:0]
};
 // DSI_INT_CLR Register
struct DISPIF_DSI_INT_CLR {
	unsigned int ICrSw7:1;		// [31]
	unsigned int ICrSw6:1;		// [30]
	unsigned int ICrSw5:1;		// [29]
	unsigned int ICrSw4:1;		// [28]
	unsigned int ICrSw3:1;		// [27]
	unsigned int ICrSw2:1;		// [26]
	unsigned int ICrSw1:1;		// [25]
	unsigned int ICrSw0:1;		// [24]
	unsigned int ICrLPFl:1;		// [23]
	unsigned int ICrLPAF:1;		// [22]
	unsigned int ICrLPAE:1;		// [21]
	unsigned int ICrLPEm:1;		// [20]
	unsigned int reserved:1;		// [19]
	unsigned int ICrAk:1;		// [18]
	unsigned int ICrQ1Fl:1;		// [17]
	unsigned int ICrQ1AF:1;		// [16]
	unsigned int ICrQ1AE:1;		// [15]
	unsigned int ICrQ1Em:1;		// [14]
	unsigned int reserved2:1;		// [13]
	unsigned int ICrRxEd:1;		// [12]
	unsigned int ICrTE:1;		// [11]
	unsigned int ICrRxAF:1;		// [10]
	unsigned int ICrRxAE:1;		// [9]
	unsigned int ICrRxEm:1;		// [8]
	unsigned int ICrQ0Fl:1;		// [7]
	unsigned int ICrQ0AF:1;		// [6]
	unsigned int ICrQ0AE:1;		// [5]
	unsigned int ICrQ0Em:1;		// [4]
	unsigned int ICrHlt:1;		// [3]
	unsigned int ICrEr:1;		// [2]
	unsigned int ICrRxEr:1;		// [1]
	unsigned int ICrAkEr:1;		// [0]
};
 // DSI_CQ1 Register
struct DISPIF_DSI_CQ1 {
	unsigned int COMMAND1:32;		// [31:0]
};
 // DSI_PAUSE Register
struct DISPIF_DSI_PAUSE {
	unsigned int PAUSE:32;		// [31:0]
};
 // DSI_START Register
struct DISPIF_DSI_START {
	unsigned int reserved:31;		// [31:1]
	unsigned int Strt:1;		// [0]
};
 // CQ1SKIP Register
struct DISPIF_CQ1SKIP {
	unsigned int reserved:31;		// [31:1]
	unsigned int SKIP:1;		// [0]
};
 // LPFIFO Register
struct DISPIF_LPFIFO {
	unsigned int LPFIFO:32;		// [31:0]
};
 // DSI_DPHY_CLW_DPHYCONTTX Register
struct DISPIF_DSI_DPHY_CLW_DPHYCONTTX {
	unsigned int reserved:22;		// [31:10]
	unsigned int CLW_CAP:2;		// [9:8]
	unsigned int CL_DLYCNTRL:4;		// [7:4]
	unsigned int reserved2:2;		// [3:2]
	unsigned int CLW_LPTXCURREN:2;		// [1:0]
};
 // DSI_DPHY_D0W_DPHYCONTTX Register
struct DISPIF_DSI_DPHY_D0W_DPHYCONTTX {
	unsigned int reserved:22;		// [31:10]
	unsigned int D0W_CAP:2;		// [9:8]
	unsigned int D0_DLYCNTRL:4;		// [7:4]
	unsigned int reserved2:2;		// [3:2]
	unsigned int D0W_LPTXCURREN:2;		// [1:0]
};
 // DSI_DPHY_D1W_DPHYCONTTX Register
struct DISPIF_DSI_DPHY_D1W_DPHYCONTTX {
	unsigned int reserved:22;		// [31:10]
	unsigned int D1W_CAP:2;		// [9:8]
	unsigned int D1_DLYCNTRL:4;		// [7:4]
	unsigned int reserved2:2;		// [3:2]
	unsigned int D1W_LPTXCURREN:2;		// [1:0]
};
 // DSI_DPHY_D2W_DPHYCONTTX Register
struct DISPIF_DSI_DPHY_D2W_DPHYCONTTX {
	unsigned int reserved:22;		// [31:10]
	unsigned int D2W_CAP:2;		// [9:8]
	unsigned int D2_DLYCNTRL:4;		// [7:4]
	unsigned int reserved2:2;		// [3:2]
	unsigned int D2W_LPTXCURREN:2;		// [1:0]
};
 // DSI_DPHY_D3W_DPHYCONTTX Register
struct DISPIF_DSI_DPHY_D3W_DPHYCONTTX {
	unsigned int reserved:22;		// [31:10]
	unsigned int D3W_CAP:2;		// [9:8]
	unsigned int D3_DLYCNTRL:4;		// [7:4]
	unsigned int reserved2:2;		// [3:2]
	unsigned int D3W_LPTXCURREN:2;		// [1:0]
};
 // DSI_DPHY_CLWCNTRL Register
struct DISPIF_DSI_DPHY_CLWCNTRL {
	unsigned int reserved:22;		// [31:10]
	unsigned int CLM_CNTRL:2;		// [9:8]
	unsigned int reserved2:7;		// [7:1]
	unsigned int CLM_EN:1;		// [0]
};
 // DSI_DPHY_D0WCNTRL Register
struct DISPIF_DSI_DPHY_D0WCNTRL {
	unsigned int reserved:22;		// [31:10]
	unsigned int D0M_CNTRL:2;		// [9:8]
	unsigned int reserved2:7;		// [7:1]
	unsigned int D0M_EN:1;		// [0]
};
 // DSI_DPHY_D1WCNTRL Register
struct DISPIF_DSI_DPHY_D1WCNTRL {
	unsigned int reserved:22;		// [31:10]
	unsigned int D1M_CNTRL:2;		// [9:8]
	unsigned int reserved2:7;		// [7:1]
	unsigned int D1M_EN:1;		// [0]
};
 // DSI_DPHY_D2WCNTRL Register
struct DISPIF_DSI_DPHY_D2WCNTRL {
	unsigned int reserved:22;		// [31:10]
	unsigned int D2M_CNTRL:2;		// [9:8]
	unsigned int reserved2:7;		// [7:1]
	unsigned int D2M_EN:1;		// [0]
};
 // DSI_DPHY_D3WCNTRL Register
struct DISPIF_DSI_DPHY_D3WCNTRL {
	unsigned int reserved:22;		// [31:10]
	unsigned int D3M_CNTRL:2;		// [9:8]
	unsigned int reserved2:7;		// [7:1]
	unsigned int D3M_EN:1;		// [0]
};
 // BYPCKEN Register
struct DISPIF_BYPCKEN {
	unsigned int reserved:31;		// [31:1]
	unsigned int bypcken:1;		// [0]
};
 // CKEN Register
struct DISPIF_CKEN {
	unsigned int reserved:31;		// [31:1]
	unsigned int cken:1;		// [0]
};
 // CKTRISTATE Register
struct DISPIF_CKTRISTATE {
	unsigned int reserved:31;		// [31:1]
	unsigned int cktristate:1;		// [0]
};
 // ENABLE Register
struct DISPIF_ENABLE {
	unsigned int reserved:31;		// [31:1]
	unsigned int pllenable:1;		// [0]
};
 // EXTFBEN Register
struct DISPIF_EXTFBEN {
	unsigned int reserved:31;		// [31:1]
	unsigned int extfben:1;		// [0]
};
 // FBD Register
struct DISPIF_FBD {
	unsigned int reserved:23;		// [31:9]
	unsigned int fbd:9;		// [8:0]
};
 // FRS Register
struct DISPIF_FRS {
	unsigned int reserved:30;		// [31:2]
	unsigned int frs:2;		// [1:0]
};
 // LBWS Register
struct DISPIF_LBWS {
	unsigned int reserved:30;		// [31:2]
	unsigned int lbws:2;		// [1:0]
};
 // LFBREN Register
struct DISPIF_LFBREN {
	unsigned int reserved:31;		// [31:1]
	unsigned int lfbren:1;		// [0]
};
 // PRD Register
struct DISPIF_PRD {
	unsigned int reserved:28;		// [31:4]
	unsigned int prd:4;		// [3:0]
};
 // TEST Register
struct DISPIF_TEST {
	unsigned int reserved:23;		// [31:9]
	unsigned int tcken:1;		// [8]
	unsigned int reserved2:3;		// [7:5]
	unsigned int tcks:1;		// [4]
	unsigned int reserved3:3;		// [3:1]
	unsigned int plltesten:1;		// [0]
};
 // DISPIF_CGATE Register
struct DISPIF_DISPIF_CGATE {
	unsigned int reserved:23;		// [31:9]
	unsigned int MDI_videoclken:1;		// [8]
	unsigned int reserved2:3;		// [7:5]
	unsigned int DTG_videoclken:1;		// [4]
	unsigned int reserved3:2;		// [3:2]
	unsigned int DSITX_videoclken:1;		// [1]
	unsigned int DSITX_HSbytelken:1;		// [0]
};
 // DISPIF_IRQMOD Register
struct DISPIF_DISPIF_IRQMOD {
	unsigned int reserved:31;		// [31:1]
	unsigned int IRQ_MOD:1;		// [0]
};
 // DISPIF_IRQSEL Register
struct DISPIF_DISPIF_IRQSEL {
	unsigned int DISPIF_IntFrame_sel:4;		// [31:28]
	unsigned int DISPIF_IntErr_sel:4;		// [27:24]
	unsigned int DISPIF_DSIInt_sel:4;		// [23:20]
	unsigned int DISPIF_HBlankInInt_sel:4;		// [19:16]
	unsigned int DISPIF_VBlankInInt_sel:4;		// [15:12]
	unsigned int DISPIF_VBlankOutInt_sel:4;		// [11:8]
	unsigned int DISPIF_HBlankInInt2_sel:4;		// [7:4]
	unsigned int DISPIF_HBlankInInt3_sel:4;		// [3:0]
};
 // FCONVA_START Register
struct DISPIF_FCONVA_START {
	unsigned int Reserved:30;		// [31:2]
	unsigned int CHANNEL:1;		// [1]
	unsigned int START:1;		// [0]
};
 // FCONVA_ABORT Register
struct DISPIF_FCONVA_ABORT {
	unsigned int Reserved:31;		// [31:1]
	unsigned int ABORT:1;		// [0]
};
 // FCONVA_SET_DUMMY_READ Register
struct DISPIF_FCONVA_SET_DUMMY_READ {
	unsigned int Reserved:28;		// [31:4]
	unsigned int DUMMY_READ:4;		// [3:0]
};
 // FCONVA_SET_BUSIF Register
struct DISPIF_FCONVA_SET_BUSIF {
	unsigned int Reserved:28;		// [31:4]
	unsigned int OUTSTAND_CMD:4;		// [3:0]
};
 // FCONVA_SET_SEL_ALPHA Register
struct DISPIF_FCONVA_SET_SEL_ALPHA {
	unsigned int Reserved:31;		// [31:1]
	unsigned int SEL_ALPHA:1;		// [0]
};
 // FCONVA_IRQ Register
struct DISPIF_FCONVA_IRQ {
	unsigned int Reserved2:24;		// [31:8]
	unsigned int MERGE_ERROR_IRQ:1;		// [7]
	unsigned int DISP_ERROR_IRQ:1;		// [6]
	unsigned int REG_ERROR_IRQ:1;		// [5]
	unsigned int START_ERROR_IRQ:1;		// [4]
	unsigned int Reserved:3;		// [3:1]
	unsigned int FRAME_END_IRQ:1;		// [0]
};
 // FCONVA_SET_IRQ_MASK Register
struct DISPIF_FCONVA_SET_IRQ_MASK {
	unsigned int Reserved2:24;		// [31:8]
	unsigned int MERGE_ERROR_MASK:1;		// [7]
	unsigned int DISP_ERROR_MASK:1;		// [6]
	unsigned int REG_ERROR_MASK:1;		// [5]
	unsigned int START_ERROR_MASK:1;		// [4]
	unsigned int Reserved:3;		// [3:1]
	unsigned int FRAME_END_MASK:1;		// [0]
};
 // FCONVA_SET_Y2RMTX_OFFSET Register
struct DISPIF_FCONVA_SET_Y2RMTX_OFFSET {
	unsigned int Reserved2:8;		// [31:24]
	unsigned int Y2R_COFFSET:8;		// [23:16]
	unsigned int Reserved:8;		// [15:8]
	unsigned int Y2R_YOFFSET:8;		// [7:0]
};
 // FCONVA_SET_Y2RMTX_COEF00 Register
struct DISPIF_FCONVA_SET_Y2RMTX_COEF00 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int Y2R_COEF00:10;		// [9:0]
};
 // FCONVA_SET_Y2RMTX_COEF01 Register
struct DISPIF_FCONVA_SET_Y2RMTX_COEF01 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int Y2R_COEF01:10;		// [9:0]
};
 // FCONVA_SET_Y2RMTX_COEF02 Register
struct DISPIF_FCONVA_SET_Y2RMTX_COEF02 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int Y2R_COEF02:10;		// [9:0]
};
 // FCONVA_SET_Y2RMTX_COEF10 Register
struct DISPIF_FCONVA_SET_Y2RMTX_COEF10 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int Y2R_COEF10:10;		// [9:0]
};
 // FCONVA_SET_Y2RMTX_COEF11 Register
struct DISPIF_FCONVA_SET_Y2RMTX_COEF11 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int Y2R_COEF11:10;		// [9:0]
};
 // FCONVA_SET_Y2RMTX_COEF12 Register
struct DISPIF_FCONVA_SET_Y2RMTX_COEF12 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int Y2R_COEF12:10;		// [9:0]
};
 // FCONVA_SET_Y2RMTX_COEF20 Register
struct DISPIF_FCONVA_SET_Y2RMTX_COEF20 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int Y2R_COEF20:10;		// [9:0]
};
 // FCONVA_SET_Y2RMTX_COEF21 Register
struct DISPIF_FCONVA_SET_Y2RMTX_COEF21 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int Y2R_COEF21:10;		// [9:0]
};
 // FCONVA_SET_Y2RMTX_COEF22 Register
struct DISPIF_FCONVA_SET_Y2RMTX_COEF22 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int Y2R_COEF22:10;		// [9:0]
};
 // FCONVA_SET_RGBLIMIT Register
struct DISPIF_FCONVA_SET_RGBLIMIT {
	unsigned int Reserved2:8;		// [31:24]
	unsigned int Y2R_RGBMIN_LIMIT:8;		// [23:16]
	unsigned int Reserved:8;		// [15:8]
	unsigned int Y2R_RGBMAX_LIMIT:8;		// [7:0]
};
 // FCONVA_SET_R2YMTX_OFFSET Register
struct DISPIF_FCONVA_SET_R2YMTX_OFFSET {
	unsigned int Reserved2:8;		// [31:24]
	unsigned int R2Y_COFFSET:8;		// [23:16]
	unsigned int Reserved:8;		// [15:8]
	unsigned int R2Y_YOFFSET:8;		// [7:0]
};
 // FCONVA_SET_R2YMTX_COEF00 Register
struct DISPIF_FCONVA_SET_R2YMTX_COEF00 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int R2Y_COEF00:10;		// [9:0]
};
 // FCONVA_SET_R2YMTX_COEF01 Register
struct DISPIF_FCONVA_SET_R2YMTX_COEF01 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int R2Y_COEF01:10;		// [9:0]
};
 // FCONVA_SET_R2YMTX_COEF02 Register
struct DISPIF_FCONVA_SET_R2YMTX_COEF02 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int R2Y_COEF02:10;		// [9:0]
};
 // FCONVA_SET_R2YMTX_COEF10 Register
struct DISPIF_FCONVA_SET_R2YMTX_COEF10 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int R2Y_COEF10:10;		// [9:0]
};
 // FCONVA_SET_R2YMTX_COEF11 Register
struct DISPIF_FCONVA_SET_R2YMTX_COEF11 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int R2Y_COEF11:10;		// [9:0]
};
 // FCONVA_SET_R2YMTX_COEF12 Register
struct DISPIF_FCONVA_SET_R2YMTX_COEF12 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int R2Y_COEF12:10;		// [9:0]
};
 // FCONVA_SET_R2YMTX_COEF20 Register
struct DISPIF_FCONVA_SET_R2YMTX_COEF20 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int R2Y_COEF20:10;		// [9:0]
};
 // FCONVA_SET_R2YMTX_COEF21 Register
struct DISPIF_FCONVA_SET_R2YMTX_COEF21 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int R2Y_COEF21:10;		// [9:0]
};
 // FCONVA_SET_R2YMTX_COEF22 Register
struct DISPIF_FCONVA_SET_R2YMTX_COEF22 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int R2Y_COEF22:10;		// [9:0]
};
 // FCONVA_SET_YLIMIT Register
struct DISPIF_FCONVA_SET_YLIMIT {
	unsigned int Reserved2:8;		// [31:24]
	unsigned int R2Y_YMIN_LIMIT:8;		// [23:16]
	unsigned int Reserved:8;		// [15:8]
	unsigned int R2Y_YMAX_LIMIT:8;		// [7:0]
};
 // FCONVA_SET_CLIMIT Register
struct DISPIF_FCONVA_SET_CLIMIT {
	unsigned int Reserved2:8;		// [31:24]
	unsigned int R2Y_CMIN_LIMIT:8;		// [23:16]
	unsigned int Reserved:8;		// [15:8]
	unsigned int R2Y_CMAX_LIMIT:8;		// [7:0]
};
 // FCONVA_TRANS_IN_FORMAT Register
struct DISPIF_FCONVA_TRANS_IN_FORMAT {
	unsigned int Reserved4:8;		// [31:24]
	unsigned int IN_FORMATID:8;		// [23:16]
	unsigned int Reserved3:7;		// [15:9]
	unsigned int IN_SCAN:1;		// [8]
	unsigned int Reserved2:2;		// [7:6]
	unsigned int IN_PLANE:2;		// [5:4]
	unsigned int Reserved:2;		// [3:2]
	unsigned int IN_COLORFORMAT:2;		// [1:0]
};
 // FCONVA_TRANS_IN_HSIZE Register
struct DISPIF_FCONVA_TRANS_IN_HSIZE {
	unsigned int Reserved:21;		// [31:11]
	unsigned int IN_HSIZE:11;		// [10:0]
};
 // FCONVA_TRANS_IN_VSIZE Register
struct DISPIF_FCONVA_TRANS_IN_VSIZE {
	unsigned int Reserved:22;		// [31:10]
	unsigned int IN_VSIZE:10;		// [9:0]
};
 // FCONVA_TRANS_IN_BASEADDR_GY Register
struct DISPIF_FCONVA_TRANS_IN_BASEADDR_GY {
	unsigned int IN_BADDR_GY:32;		// [31:0]
};
 // FCONVA_TRANS_IN_BASEADDR_BCB Register
struct DISPIF_FCONVA_TRANS_IN_BASEADDR_BCB {
	unsigned int IN_BADDR_BCB:32;		// [31:0]
};
 // FCONVA_TRANS_IN_BASEADDR_RCR Register
struct DISPIF_FCONVA_TRANS_IN_BASEADDR_RCR {
	unsigned int IN_BADDR_RCR:32;		// [31:0]
};
 // FCONVA_TRANS_IN_PITCH_GY Register
struct DISPIF_FCONVA_TRANS_IN_PITCH_GY {
	unsigned int Reserved:20;		// [31:12]
	unsigned int IN_PITCH_GY:12;		// [11:0]
};
 // FCONVA_TRANS_IN_PITCH_BCB Register
struct DISPIF_FCONVA_TRANS_IN_PITCH_BCB {
	unsigned int Reserved:20;		// [31:12]
	unsigned int IN_PITCH_BCB:12;		// [11:0]
};
 // FCONVA_TRANS_IN_PITCH_RCR Register
struct DISPIF_FCONVA_TRANS_IN_PITCH_RCR {
	unsigned int Reserved:20;		// [31:12]
	unsigned int IN_PITCH_RCR:12;		// [11:0]
};
 // FCONVA_TRANS_OUT_FORMAT Register
struct DISPIF_FCONVA_TRANS_OUT_FORMAT {
	unsigned int Reserved4:8;		// [31:24]
	unsigned int OUT_FORMATID:8;		// [23:16]
	unsigned int Reserved3:7;		// [15:9]
	unsigned int OUT_SCAN:1;		// [8]
	unsigned int Reserved2:2;		// [7:6]
	unsigned int OUT_PLANE:2;		// [5:4]
	unsigned int Reserved:2;		// [3:2]
	unsigned int OUT_COLORFORMAT:2;		// [1:0]
};
 // FCONVA_TRANS_OUT_HSIZE Register
struct DISPIF_FCONVA_TRANS_OUT_HSIZE {
	unsigned int Reserved:21;		// [31:11]
	unsigned int OUT_HSIZE:11;		// [10:0]
};
 // FCONVA_TRANS_OUT_VSIZE Register
struct DISPIF_FCONVA_TRANS_OUT_VSIZE {
	unsigned int Reserved:22;		// [31:10]
	unsigned int OUT_VSIZE:10;		// [9:0]
};
 // FCONVA_TRANS_OUT_BASEADDR_GY Register
struct DISPIF_FCONVA_TRANS_OUT_BASEADDR_GY {
	unsigned int OUT_BADDR_GY:32;		// [31:0]
};
 // FCONVA_TRANS_OUT_BASEADDR_BCB Register
struct DISPIF_FCONVA_TRANS_OUT_BASEADDR_BCB {
	unsigned int OUT_BADDR_BCB:32;		// [31:0]
};
 // FCONVA_TRANS_OUT_BASEADDR_RCR Register
struct DISPIF_FCONVA_TRANS_OUT_BASEADDR_RCR {
	unsigned int OUT_BADDR_RCR:32;		// [31:0]
};
 // FCONVA_TRANS_OUT_PITCH_GY Register
struct DISPIF_FCONVA_TRANS_OUT_PITCH_GY {
	unsigned int Reserved:20;		// [31:12]
	unsigned int OUT_PITCH_GY:12;		// [11:0]
};
 // FCONVA_TRANS_OUT_PITCH_BCB Register
struct DISPIF_FCONVA_TRANS_OUT_PITCH_BCB {
	unsigned int Reserved:20;		// [31:12]
	unsigned int OUT_PITCH_BCB:12;		// [11:0]
};
 // FCONVA_TRANS_OUT_PITCH_RCR Register
struct DISPIF_FCONVA_TRANS_OUT_PITCH_RCR {
	unsigned int Reserved:20;		// [31:12]
	unsigned int OUT_PITCH_RCR:12;		// [11:0]
};
 // FCONVA_TRANS_FORCE_MODE Register
struct DISPIF_FCONVA_TRANS_FORCE_MODE {
	unsigned int Reserved:31;		// [31:1]
	unsigned int FORCE_MODE:1;		// [0]
};
 // FCONVA_CH_FORCE_GY Register
struct DISPIF_FCONVA_CH_FORCE_GY {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_GY:8;		// [7:0]
};
 // FCONVA_CH_FORCE_BCB Register
struct DISPIF_FCONVA_CH_FORCE_BCB {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_BCB:8;		// [7:0]
};
 // FCONVA_CH_FORCE_R Register
struct DISPIF_FCONVA_CH_FORCE_R {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_RCR:8;		// [7:0]
};
 // FCONVA_CH_FORCE_A Register
struct DISPIF_FCONVA_CH_FORCE_A {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_ALPHA:8;		// [7:0]
};
 // FCONVA_TRANS_CROP Register
struct DISPIF_FCONVA_TRANS_CROP {
	unsigned int Reserved4:4;		// [31:28]
	unsigned int CROP_RIGHT:4;		// [27:24]
	unsigned int Reserved3:4;		// [23:20]
	unsigned int CROP_LEFT:4;		// [19:16]
	unsigned int Reserved2:4;		// [15:12]
	unsigned int CROP_LOWER:4;		// [11:8]
	unsigned int Reserved:4;		// [7:4]
	unsigned int CROP_UPPER:4;		// [3:0]
};
 // FCONVA_TRANS_STATUS Register
struct DISPIF_FCONVA_TRANS_STATUS {
	unsigned int Reserved2:23;		// [31:9]
	unsigned int MERGE_STATUS:1;		// [8]
	unsigned int Reserved:6;		// [7:2]
	unsigned int TRANS_CHANNEL:1;		// [1]
	unsigned int TRUNS_STATUS:1;		// [0]
};
 // FCONVA_TRANS_LINE Register
struct DISPIF_FCONVA_TRANS_LINE {
	unsigned int Reserved2:5;		// [31:27]
	unsigned int OUTPUT_LINE:11;		// [26:16]
	unsigned int Reserved:5;		// [15:11]
	unsigned int INPUT_LINE:11;		// [10:0]
};
 // FCONVA_SET_IN_FORMAT0 Register
struct DISPIF_FCONVA_SET_IN_FORMAT0 {
	unsigned int Reserved4:8;		// [31:24]
	unsigned int IN_FORMATID0:8;		// [23:16]
	unsigned int Reserved3:7;		// [15:9]
	unsigned int IN_SCAN0:1;		// [8]
	unsigned int Reserved2:2;		// [7:6]
	unsigned int IN_PLANE0:2;		// [5:4]
	unsigned int Reserved:2;		// [3:2]
	unsigned int IN_COLORFORMAT0:2;		// [1:0]
};
 // FCONVA_SET_IN_HSIZE0 Register
struct DISPIF_FCONVA_SET_IN_HSIZE0 {
	unsigned int Reserved:21;		// [31:11]
	unsigned int IN_HSIZE0:11;		// [10:0]
};
 // FCONVA_SET_IN_VSIZE0 Register
struct DISPIF_FCONVA_SET_IN_VSIZE0 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int IN_VSIZE0:10;		// [9:0]
};
 // FCONVA_SET_IN_BASEADDR_GY0 Register
struct DISPIF_FCONVA_SET_IN_BASEADDR_GY0 {
	unsigned int IN_BADDR_GY0:32;		// [31:0]
};
 // FCONVA_SET_IN_BASEADDR_BCB0 Register
struct DISPIF_FCONVA_SET_IN_BASEADDR_BCB0 {
	unsigned int IN_BADDR_BCB0:32;		// [31:0]
};
 // FCONVA_SET_IN_BASEADDR_RCR0 Register
struct DISPIF_FCONVA_SET_IN_BASEADDR_RCR0 {
	unsigned int IN_BADDR_RCR0:32;		// [31:0]
};
 // FCONVA_SET_IN_PITCH_GY0 Register
struct DISPIF_FCONVA_SET_IN_PITCH_GY0 {
	unsigned int Reserved:20;		// [31:12]
	unsigned int IN_PITCH_GY0:12;		// [11:0]
};
 // FCONVA_SET_IN_PITCH_BCB0 Register
struct DISPIF_FCONVA_SET_IN_PITCH_BCB0 {
	unsigned int Reserved:20;		// [31:12]
	unsigned int IN_PITCH_BCB0:12;		// [11:0]
};
 // FCONVA_SET_IN_PITCH_RCR0 Register
struct DISPIF_FCONVA_SET_IN_PITCH_RCR0 {
	unsigned int Reserved:20;		// [31:12]
	unsigned int IN_PITCH_RCR0:12;		// [11:0]
};
 // FCONVA_SET_OUT_FORMAT0 Register
struct DISPIF_FCONVA_SET_OUT_FORMAT0 {
	unsigned int Reserved4:15;		// [31:17]
	unsigned int OUT_FORMATID0:1;		// [16]
	unsigned int Reserved3:7;		// [15:9]
	unsigned int OUT_SCAN0:1;		// [8]
	unsigned int Reserved2:2;		// [7:6]
	unsigned int OUT_PLANE0:2;		// [5:4]
	unsigned int Reserved:2;		// [3:2]
	unsigned int OUT_COLORFORMAT0:2;		// [1:0]
};
 // FCONVA_SET_OUT_HSIZE0 Register
struct DISPIF_FCONVA_SET_OUT_HSIZE0 {
	unsigned int Reserved:21;		// [31:11]
	unsigned int OUT_HSIZE0:11;		// [10:0]
};
 // FCONVA_SET_OUT_VSIZE0 Register
struct DISPIF_FCONVA_SET_OUT_VSIZE0 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int OUT_VSIZE0:10;		// [9:0]
};
 // FCONVA_SET_OUT_BASEADDR_GY0 Register
struct DISPIF_FCONVA_SET_OUT_BASEADDR_GY0 {
	unsigned int OUT_BADDR_GY0:32;		// [31:0]
};
 // FCONVA_SET_OUT_BASEADDR_BCB0 Register
struct DISPIF_FCONVA_SET_OUT_BASEADDR_BCB0 {
	unsigned int OUT_BADDR_BCB0:32;		// [31:0]
};
 // FCONVA_SET_OUT_BASEADDR_RCR0 Register
struct DISPIF_FCONVA_SET_OUT_BASEADDR_RCR0 {
	unsigned int OUT_BADDR_RCR0:32;		// [31:0]
};
 // FCONVA_SET_OUT_PITCH_GY0 Register
struct DISPIF_FCONVA_SET_OUT_PITCH_GY0 {
	unsigned int Reserved:20;		// [31:12]
	unsigned int OUT_PITCH_GY0:12;		// [11:0]
};
 // FCONVA_SET_OUT_PITCH_BCB0 Register
struct DISPIF_FCONVA_SET_OUT_PITCH_BCB0 {
	unsigned int Reserved:20;		// [31:12]
	unsigned int OUT_PITCH_BCB0:12;		// [11:0]
};
 // FCONVA_SET_OUT_PITCH_RCR0 Register
struct DISPIF_FCONVA_SET_OUT_PITCH_RCR0 {
	unsigned int Reserved:20;		// [31:12]
	unsigned int OUT_PITCH_RCR0:12;		// [11:0]
};
 // FCONVA_SET_FORCE_MODE0 Register
struct DISPIF_FCONVA_SET_FORCE_MODE0 {
	unsigned int Reserved:31;		// [31:1]
	unsigned int FORCE_MODE0:1;		// [0]
};
 // FCONVA_SET_FORCE_GY0 Register
struct DISPIF_FCONVA_SET_FORCE_GY0 {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_GY0:8;		// [7:0]
};
 // FCONVA_SET_FORCE_BCB0 Register
struct DISPIF_FCONVA_SET_FORCE_BCB0 {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_BCB0:8;		// [7:0]
};
 // FCONVA_SET_FORCE_RCR0 Register
struct DISPIF_FCONVA_SET_FORCE_RCR0 {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_RCR0:8;		// [7:0]
};
 // FCONVA_SET_FORCE_A0 Register
struct DISPIF_FCONVA_SET_FORCE_A0 {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_ALPHA0:8;		// [7:0]
};
 // FCONVA_SET_CROP0 Register
struct DISPIF_FCONVA_SET_CROP0 {
	unsigned int Reserved4:4;		// [31:28]
	unsigned int CROP_RIGHT0:4;		// [27:24]
	unsigned int Reserved3:4;		// [23:20]
	unsigned int CROP_LEFT0:4;		// [19:16]
	unsigned int Reserved2:4;		// [15:12]
	unsigned int CROP_LOWER0:4;		// [11:8]
	unsigned int Reserved:4;		// [7:4]
	unsigned int CROP_UPPER0:4;		// [3:0]
};
 // FCONVA_SET_IN_FORMAT1 Register
struct DISPIF_FCONVA_SET_IN_FORMAT1 {
	unsigned int Reserved4:8;		// [31:24]
	unsigned int IN_FORMATID1:8;		// [23:16]
	unsigned int Reserved3:7;		// [15:9]
	unsigned int IN_SCAN1:1;		// [8]
	unsigned int Reserved2:2;		// [7:6]
	unsigned int IN_PLANE1:2;		// [5:4]
	unsigned int Reserved:2;		// [3:2]
	unsigned int IN_COLORFORMAT1:2;		// [1:0]
};
 // FCONVA_SET_IN_HSIZE1 Register
struct DISPIF_FCONVA_SET_IN_HSIZE1 {
	unsigned int Reserved:21;		// [31:11]
	unsigned int IN_HSIZE1:11;		// [10:0]
};
 // FCONVA_SET_IN_VSIZE1 Register
struct DISPIF_FCONVA_SET_IN_VSIZE1 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int IN_VSIZE1:10;		// [9:0]
};
 // FCONVA_SET_IN_BASEADDR_GY1 Register
struct DISPIF_FCONVA_SET_IN_BASEADDR_GY1 {
	unsigned int IN_BADDR_GY1:32;		// [31:0]
};
 // FCONVA_SET_IN_BASEADDR_BCB1 Register
struct DISPIF_FCONVA_SET_IN_BASEADDR_BCB1 {
	unsigned int IN_BADDR_BCB1:32;		// [31:0]
};
 // FCONVA_SET_IN_BASEADDR_RCR1 Register
struct DISPIF_FCONVA_SET_IN_BASEADDR_RCR1 {
	unsigned int IN_BADDR_RCR1:32;		// [31:0]
};
 // FCONVA_SET_IN_PITCH_GY1 Register
struct DISPIF_FCONVA_SET_IN_PITCH_GY1 {
	unsigned int Reserved:20;		// [31:12]
	unsigned int IN_PITCH_GY1:12;		// [11:0]
};
 // FCONVA_SET_IN_PITCH_BCB1 Register
struct DISPIF_FCONVA_SET_IN_PITCH_BCB1 {
	unsigned int Reserved:20;		// [31:12]
	unsigned int IN_PITCH_BCB1:12;		// [11:0]
};
 // FCONVA_SET_IN_PITCH_RCR1 Register
struct DISPIF_FCONVA_SET_IN_PITCH_RCR1 {
	unsigned int Reserved:20;		// [31:12]
	unsigned int IN_PITCH_RCR1:12;		// [11:0]
};
 // FCONVA_SET_OUT_FORMAT1 Register
struct DISPIF_FCONVA_SET_OUT_FORMAT1 {
	unsigned int Reserved4:8;		// [31:24]
	unsigned int OUT_FORMATID1:8;		// [23:16]
	unsigned int Reserved3:7;		// [15:9]
	unsigned int OUT_SCAN1:1;		// [8]
	unsigned int Reserved2:2;		// [7:6]
	unsigned int OUT_PLANE1:2;		// [5:4]
	unsigned int Reserved:2;		// [3:2]
	unsigned int OUT_COLORFORMAT1:2;		// [1:0]
};
 // FCONVA_SET_OUT_HSIZE1 Register
struct DISPIF_FCONVA_SET_OUT_HSIZE1 {
	unsigned int Reserved:21;		// [31:11]
	unsigned int OUT_HSIZE1:11;		// [10:0]
};
 // FCONVA_SET_OUT_VSIZE1 Register
struct DISPIF_FCONVA_SET_OUT_VSIZE1 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int OUT_VSIZE1:10;		// [9:0]
};
 // FCONVA_SET_OUT_BASEADDR_GY1 Register
struct DISPIF_FCONVA_SET_OUT_BASEADDR_GY1 {
	unsigned int OUT_BADDR_GY1:32;		// [31:0]
};
 // FCONVA_SET_OUT_BASEADDR_BCB1 Register
struct DISPIF_FCONVA_SET_OUT_BASEADDR_BCB1 {
	unsigned int OUT_BADDR_BCB1:32;		// [31:0]
};
 // FCONVA_SET_OUT_BASEADDR_RCR1 Register
struct DISPIF_FCONVA_SET_OUT_BASEADDR_RCR1 {
	unsigned int OUT_BADDR_RCR1:32;		// [31:0]
};
 // FCONVA_SET_OUT_PITCH_GY1 Register
struct DISPIF_FCONVA_SET_OUT_PITCH_GY1 {
	unsigned int Reserved:20;		// [31:12]
	unsigned int OUT_PITCH_GY1:12;		// [11:0]
};
 // FCONVA_SET_OUT_PITCH_BCB1 Register
struct DISPIF_FCONVA_SET_OUT_PITCH_BCB1 {
	unsigned int Reserved:20;		// [31:12]
	unsigned int OUT_PITCH_BCB1:12;		// [11:0]
};
 // FCONVA_SET_OUT_PITCH_RCR1 Register
struct DISPIF_FCONVA_SET_OUT_PITCH_RCR1 {
	unsigned int Reserved:20;		// [31:12]
	unsigned int OUT_PITCH_RCR1:12;		// [11:0]
};
 // FCONVA_SET_FORCE_MODE1 Register
struct DISPIF_FCONVA_SET_FORCE_MODE1 {
	unsigned int Reserved:31;		// [31:1]
	unsigned int FORCE_MODE1:1;		// [0]
};
 // FCONVA_SET_FORCE_GY1 Register
struct DISPIF_FCONVA_SET_FORCE_GY1 {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_GY1:8;		// [7:0]
};
 // FCONVA_SET_FORCE_BCB1 Register
struct DISPIF_FCONVA_SET_FORCE_BCB1 {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_BCB1:8;		// [7:0]
};
 // FCONVA_SET_FORCE_RCR1 Register
struct DISPIF_FCONVA_SET_FORCE_RCR1 {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_RCR1:8;		// [7:0]
};
 // FCONVA_SET_FORCE_A1 Register
struct DISPIF_FCONVA_SET_FORCE_A1 {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_ALPHA1:8;		// [7:0]
};
 // FCONVA_SET_CROP1 Register
struct DISPIF_FCONVA_SET_CROP1 {
	unsigned int Reserved4:4;		// [31:28]
	unsigned int CROP_RIGHT1:4;		// [27:24]
	unsigned int Reserved3:4;		// [23:20]
	unsigned int CROP_LEFT1:4;		// [19:16]
	unsigned int Reserved2:4;		// [15:12]
	unsigned int CROP_LOWER1:4;		// [11:8]
	unsigned int Reserved:4;		// [7:4]
	unsigned int CROP_UPPER1:4;		// [3:0]
};
 // FCONVB_START Register
struct DISPIF_FCONVB_START {
	unsigned int Reserved:30;		// [31:2]
	unsigned int CHANNEL:1;		// [1]
	unsigned int START:1;		// [0]
};
 // FCONVB_ABORT Register
struct DISPIF_FCONVB_ABORT {
	unsigned int Reserved:31;		// [31:1]
	unsigned int ABORT:1;		// [0]
};
 // FCONVB_SET_DUMMY_READ Register
struct DISPIF_FCONVB_SET_DUMMY_READ {
	unsigned int Reserved:28;		// [31:4]
	unsigned int DUMMY_READ:4;		// [3:0]
};
 // FCONVB_SET_BUSIF Register
struct DISPIF_FCONVB_SET_BUSIF {
	unsigned int Reserved:28;		// [31:4]
	unsigned int OUTSTAND_CMD:4;		// [3:0]
};
 // FCONVB_SET_SEL_ALPHA Register
struct DISPIF_FCONVB_SET_SEL_ALPHA {
	unsigned int Reserved:31;		// [31:1]
	unsigned int SEL_ALPHA:1;		// [0]
};
 // FCONVB_IRQ Register
struct DISPIF_FCONVB_IRQ {
	unsigned int Reserved2:24;		// [31:8]
	unsigned int MERGE_ERROR_IRQ:1;		// [7]
	unsigned int DISP_ERROR_IRQ:1;		// [6]
	unsigned int REG_ERROR_IRQ:1;		// [5]
	unsigned int START_ERROR_IRQ:1;		// [4]
	unsigned int Reserved:3;		// [3:1]
	unsigned int FRAME_END_IRQ:1;		// [0]
};
 // FCONVB_SET_IRQ_MASK Register
struct DISPIF_FCONVB_SET_IRQ_MASK {
	unsigned int Reserved2:24;		// [31:8]
	unsigned int MERGE_ERROR_MASK:1;		// [7]
	unsigned int DISP_ERROR_MASK:1;		// [6]
	unsigned int REG_ERROR_MASK:1;		// [5]
	unsigned int START_ERROR_MASK:1;		// [4]
	unsigned int Reserved:3;		// [3:1]
	unsigned int FRAME_END_MASK:1;		// [0]
};
 // FCONVB_SET_Y2RMTX_OFFSET Register
struct DISPIF_FCONVB_SET_Y2RMTX_OFFSET {
	unsigned int Reserved2:8;		// [31:24]
	unsigned int Y2R_COFFSET:8;		// [23:16]
	unsigned int Reserved:8;		// [15:8]
	unsigned int Y2R_YOFFSET:8;		// [7:0]
};
 // FCONVB_SET_Y2RMTX_COEF00 Register
struct DISPIF_FCONVB_SET_Y2RMTX_COEF00 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int Y2R_COEF00:10;		// [9:0]
};
 // FCONVB_SET_Y2RMTX_COEF01 Register
struct DISPIF_FCONVB_SET_Y2RMTX_COEF01 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int Y2R_COEF01:10;		// [9:0]
};
 // FCONVB_SET_Y2RMTX_COEF02 Register
struct DISPIF_FCONVB_SET_Y2RMTX_COEF02 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int Y2R_COEF02:10;		// [9:0]
};
 // FCONVB_SET_Y2RMTX_COEF10 Register
struct DISPIF_FCONVB_SET_Y2RMTX_COEF10 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int Y2R_COEF10:10;		// [9:0]
};
 // FCONVB_SET_Y2RMTX_COEF11 Register
struct DISPIF_FCONVB_SET_Y2RMTX_COEF11 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int Y2R_COEF11:10;		// [9:0]
};
 // FCONVB_SET_Y2RMTX_COEF12 Register
struct DISPIF_FCONVB_SET_Y2RMTX_COEF12 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int Y2R_COEF12:10;		// [9:0]
};
 // FCONVB_SET_Y2RMTX_COEF20 Register
struct DISPIF_FCONVB_SET_Y2RMTX_COEF20 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int Y2R_COEF20:10;		// [9:0]
};
 // FCONVB_SET_Y2RMTX_COEF21 Register
struct DISPIF_FCONVB_SET_Y2RMTX_COEF21 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int Y2R_COEF21:10;		// [9:0]
};
 // FCONVB_SET_Y2RMTX_COEF22 Register
struct DISPIF_FCONVB_SET_Y2RMTX_COEF22 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int Y2R_COEF22:10;		// [9:0]
};
 // FCONVB_SET_RGBLIMIT Register
struct DISPIF_FCONVB_SET_RGBLIMIT {
	unsigned int Reserved2:8;		// [31:24]
	unsigned int Y2R_RGBMIN_LIMIT:8;		// [23:16]
	unsigned int Reserved:8;		// [15:8]
	unsigned int Y2R_RGBMAX_LIMIT:8;		// [7:0]
};
 // FCONVB_SET_R2YMTX_OFFSET Register
struct DISPIF_FCONVB_SET_R2YMTX_OFFSET {
	unsigned int Reserved2:8;		// [31:24]
	unsigned int R2Y_COFFSET:8;		// [23:16]
	unsigned int Reserved:8;		// [15:8]
	unsigned int R2Y_YOFFSET:8;		// [7:0]
};
 // FCONVB_SET_R2YMTX_COEF00 Register
struct DISPIF_FCONVB_SET_R2YMTX_COEF00 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int R2Y_COEF00:10;		// [9:0]
};
 // FCONVB_SET_R2YMTX_COEF01 Register
struct DISPIF_FCONVB_SET_R2YMTX_COEF01 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int R2Y_COEF01:10;		// [9:0]
};
 // FCONVB_SET_R2YMTX_COEF02 Register
struct DISPIF_FCONVB_SET_R2YMTX_COEF02 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int R2Y_COEF02:10;		// [9:0]
};
 // FCONVB_SET_R2YMTX_COEF10 Register
struct DISPIF_FCONVB_SET_R2YMTX_COEF10 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int R2Y_COEF10:10;		// [9:0]
};
 // FCONVB_SET_R2YMTX_COEF11 Register
struct DISPIF_FCONVB_SET_R2YMTX_COEF11 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int R2Y_COEF11:10;		// [9:0]
};
 // FCONVB_SET_R2YMTX_COEF12 Register
struct DISPIF_FCONVB_SET_R2YMTX_COEF12 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int R2Y_COEF12:10;		// [9:0]
};
 // FCONVB_SET_R2YMTX_COEF20 Register
struct DISPIF_FCONVB_SET_R2YMTX_COEF20 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int R2Y_COEF20:10;		// [9:0]
};
 // FCONVB_SET_R2YMTX_COEF21 Register
struct DISPIF_FCONVB_SET_R2YMTX_COEF21 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int R2Y_COEF21:10;		// [9:0]
};
 // FCONVB_SET_R2YMTX_COEF22 Register
struct DISPIF_FCONVB_SET_R2YMTX_COEF22 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int R2Y_COEF22:10;		// [9:0]
};
 // FCONVB_SET_YLIMIT Register
struct DISPIF_FCONVB_SET_YLIMIT {
	unsigned int Reserved2:8;		// [31:24]
	unsigned int R2Y_YMIN_LIMIT:8;		// [23:16]
	unsigned int Reserved:8;		// [15:8]
	unsigned int R2Y_YMAX_LIMIT:8;		// [7:0]
};
 // FCONVB_SET_CLIMIT Register
struct DISPIF_FCONVB_SET_CLIMIT {
	unsigned int Reserved2:8;		// [31:24]
	unsigned int R2Y_CMIN_LIMIT:8;		// [23:16]
	unsigned int Reserved:8;		// [15:8]
	unsigned int R2Y_CMAX_LIMIT:8;		// [7:0]
};
 // FCONVB_TRANS_IN_FORMAT Register
struct DISPIF_FCONVB_TRANS_IN_FORMAT {
	unsigned int Reserved4:8;		// [31:24]
	unsigned int IN_FORMATID:8;		// [23:16]
	unsigned int Reserved3:7;		// [15:9]
	unsigned int IN_SCAN:1;		// [8]
	unsigned int Reserved2:2;		// [7:6]
	unsigned int IN_PLANE:2;		// [5:4]
	unsigned int Reserved:2;		// [3:2]
	unsigned int IN_COLORFORMAT:2;		// [1:0]
};
 // FCONVB_TRANS_IN_HSIZE Register
struct DISPIF_FCONVB_TRANS_IN_HSIZE {
	unsigned int Reserved:21;		// [31:11]
	unsigned int IN_HSIZE:11;		// [10:0]
};
 // FCONVB_TRANS_IN_VSIZE Register
struct DISPIF_FCONVB_TRANS_IN_VSIZE {
	unsigned int Reserved:22;		// [31:10]
	unsigned int IN_VSIZE:10;		// [9:0]
};
 // FCONVB_TRANS_IN_BASEADDR_GY Register
struct DISPIF_FCONVB_TRANS_IN_BASEADDR_GY {
	unsigned int IN_BADDR_GY:32;		// [31:0]
};
 // FCONVB_TRANS_IN_BASEADDR_BCB Register
struct DISPIF_FCONVB_TRANS_IN_BASEADDR_BCB {
	unsigned int IN_BADDR_BCB:32;		// [31:0]
};
 // FCONVB_TRANS_IN_BASEADDR_RCR Register
struct DISPIF_FCONVB_TRANS_IN_BASEADDR_RCR {
	unsigned int IN_BADDR_RCR:32;		// [31:0]
};
 // FCONVB_TRANS_IN_PITCH_GY Register
struct DISPIF_FCONVB_TRANS_IN_PITCH_GY {
	unsigned int Reserved:20;		// [31:12]
	unsigned int IN_PITCH_GY:12;		// [11:0]
};
 // FCONVB_TRANS_IN_PITCH_BCB Register
struct DISPIF_FCONVB_TRANS_IN_PITCH_BCB {
	unsigned int Reserved:20;		// [31:12]
	unsigned int IN_PITCH_BCB:12;		// [11:0]
};
 // FCONVB_TRANS_IN_PITCH_RCR Register
struct DISPIF_FCONVB_TRANS_IN_PITCH_RCR {
	unsigned int Reserved:20;		// [31:12]
	unsigned int IN_PITCH_RCR:12;		// [11:0]
};
 // FCONVB_TRANS_OUT_FORMAT Register
struct DISPIF_FCONVB_TRANS_OUT_FORMAT {
	unsigned int Reserved4:8;		// [31:24]
	unsigned int OUT_FORMATID:8;		// [23:16]
	unsigned int Reserved3:7;		// [15:9]
	unsigned int OUT_SCAN:1;		// [8]
	unsigned int Reserved2:2;		// [7:6]
	unsigned int OUT_PLANE:2;		// [5:4]
	unsigned int Reserved:2;		// [3:2]
	unsigned int OUT_COLORFORMAT:2;		// [1:0]
};
 // FCONVB_TRANS_OUT_HSIZE Register
struct DISPIF_FCONVB_TRANS_OUT_HSIZE {
	unsigned int Reserved:21;		// [31:11]
	unsigned int OUT_HSIZE:11;		// [10:0]
};
 // FCONVB_TRANS_OUT_VSIZE Register
struct DISPIF_FCONVB_TRANS_OUT_VSIZE {
	unsigned int Reserved:22;		// [31:10]
	unsigned int OUT_VSIZE:10;		// [9:0]
};
 // FCONVB_TRANS_OUT_BASEADDR_GY Register
struct DISPIF_FCONVB_TRANS_OUT_BASEADDR_GY {
	unsigned int OUT_BADDR_GY:32;		// [31:0]
};
 // FCONVB_TRANS_OUT_BASEADDR_BCB Register
struct DISPIF_FCONVB_TRANS_OUT_BASEADDR_BCB {
	unsigned int OUT_BADDR_BCB:32;		// [31:0]
};
 // FCONVB_TRANS_OUT_BASEADDR_RCR Register
struct DISPIF_FCONVB_TRANS_OUT_BASEADDR_RCR {
	unsigned int OUT_BADDR_RCR:32;		// [31:0]
};
 // FCONVB_TRANS_OUT_PITCH_GY Register
struct DISPIF_FCONVB_TRANS_OUT_PITCH_GY {
	unsigned int Reserved:20;		// [31:12]
	unsigned int OUT_PITCH_GY:12;		// [11:0]
};
 // FCONVB_TRANS_OUT_PITCH_BCB Register
struct DISPIF_FCONVB_TRANS_OUT_PITCH_BCB {
	unsigned int Reserved:20;		// [31:12]
	unsigned int OUT_PITCH_BCB:12;		// [11:0]
};
 // FCONVB_TRANS_OUT_PITCH_RCR Register
struct DISPIF_FCONVB_TRANS_OUT_PITCH_RCR {
	unsigned int Reserved:20;		// [31:12]
	unsigned int OUT_PITCH_RCR:12;		// [11:0]
};
 // FCONVB_TRANS_FORCE_MODE Register
struct DISPIF_FCONVB_TRANS_FORCE_MODE {
	unsigned int Reserved:31;		// [31:1]
	unsigned int FORCE_MODE:1;		// [0]
};
 // FCONVB_CH_FORCE_GY Register
struct DISPIF_FCONVB_CH_FORCE_GY {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_GY:8;		// [7:0]
};
 // FCONVB_CH_FORCE_BCB Register
struct DISPIF_FCONVB_CH_FORCE_BCB {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_BCB:8;		// [7:0]
};
 // FCONVB_CH_FORCE_R Register
struct DISPIF_FCONVB_CH_FORCE_R {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_RCR:8;		// [7:0]
};
 // FCONVB_CH_FORCE_A Register
struct DISPIF_FCONVB_CH_FORCE_A {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_ALPHA:8;		// [7:0]
};
 // FCONVB_TRANS_CROP Register
struct DISPIF_FCONVB_TRANS_CROP {
	unsigned int Reserved4:4;		// [31:28]
	unsigned int CROP_RIGHT:4;		// [27:24]
	unsigned int Reserved3:4;		// [23:20]
	unsigned int CROP_LEFT:4;		// [19:16]
	unsigned int Reserved2:4;		// [15:12]
	unsigned int CROP_LOWER:4;		// [11:8]
	unsigned int Reserved:4;		// [7:4]
	unsigned int CROP_UPPER:4;		// [3:0]
};
 // FCONVB_TRANS_STATUS Register
struct DISPIF_FCONVB_TRANS_STATUS {
	unsigned int Reserved2:23;		// [31:9]
	unsigned int MERGE_STATUS:1;		// [8]
	unsigned int Reserved:6;		// [7:2]
	unsigned int TRANS_CHANNEL:1;		// [1]
	unsigned int TRUNS_STATUS:1;		// [0]
};
 // FCONVB_TRANS_LINE Register
struct DISPIF_FCONVB_TRANS_LINE {
	unsigned int Reserved2:5;		// [31:27]
	unsigned int OUTPUT_LINE:11;		// [26:16]
	unsigned int Reserved:5;		// [15:11]
	unsigned int INPUT_LINE:11;		// [10:0]
};
 // FCONVB_SET_IN_FORMAT0 Register
struct DISPIF_FCONVB_SET_IN_FORMAT0 {
	unsigned int Reserved4:8;		// [31:24]
	unsigned int IN_FORMATID0:8;		// [23:16]
	unsigned int Reserved3:7;		// [15:9]
	unsigned int IN_SCAN0:1;		// [8]
	unsigned int Reserved2:2;		// [7:6]
	unsigned int IN_PLANE0:2;		// [5:4]
	unsigned int Reserved:2;		// [3:2]
	unsigned int IN_COLORFORMAT0:2;		// [1:0]
};
 // FCONVB_SET_IN_HSIZE0 Register
struct DISPIF_FCONVB_SET_IN_HSIZE0 {
	unsigned int Reserved:21;		// [31:11]
	unsigned int IN_HSIZE0:11;		// [10:0]
};
 // FCONVB_SET_IN_VSIZE0 Register
struct DISPIF_FCONVB_SET_IN_VSIZE0 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int IN_VSIZE0:10;		// [9:0]
};
 // FCONVB_SET_IN_BASEADDR_GY0 Register
struct DISPIF_FCONVB_SET_IN_BASEADDR_GY0 {
	unsigned int IN_BADDR_GY0:32;		// [31:0]
};
 // FCONVB_SET_IN_BASEADDR_BCB0 Register
struct DISPIF_FCONVB_SET_IN_BASEADDR_BCB0 {
	unsigned int IN_BADDR_BCB0:32;		// [31:0]
};
 // FCONVB_SET_IN_BASEADDR_RCR0 Register
struct DISPIF_FCONVB_SET_IN_BASEADDR_RCR0 {
	unsigned int IN_BADDR_RCR0:32;		// [31:0]
};
 // FCONVB_SET_IN_PITCH_GY0 Register
struct DISPIF_FCONVB_SET_IN_PITCH_GY0 {
	unsigned int Reserved:20;		// [31:12]
	unsigned int IN_PITCH_GY0:12;		// [11:0]
};
 // FCONVB_SET_IN_PITCH_BCB0 Register
struct DISPIF_FCONVB_SET_IN_PITCH_BCB0 {
	unsigned int Reserved:20;		// [31:12]
	unsigned int IN_PITCH_BCB0:12;		// [11:0]
};
 // FCONVB_SET_IN_PITCH_RCR0 Register
struct DISPIF_FCONVB_SET_IN_PITCH_RCR0 {
	unsigned int Reserved:20;		// [31:12]
	unsigned int IN_PITCH_RCR0:12;		// [11:0]
};
 // FCONVB_SET_OUT_FORMAT0 Register
struct DISPIF_FCONVB_SET_OUT_FORMAT0 {
	unsigned int Reserved4:15;		// [31:17]
	unsigned int OUT_FORMATID0:1;		// [16]
	unsigned int Reserved3:7;		// [15:9]
	unsigned int OUT_SCAN0:1;		// [8]
	unsigned int Reserved2:2;		// [7:6]
	unsigned int OUT_PLANE0:2;		// [5:4]
	unsigned int Reserved:2;		// [3:2]
	unsigned int OUT_COLORFORMAT0:2;		// [1:0]
};
 // FCONVB_SET_OUT_HSIZE0 Register
struct DISPIF_FCONVB_SET_OUT_HSIZE0 {
	unsigned int Reserved:21;		// [31:11]
	unsigned int OUT_HSIZE0:11;		// [10:0]
};
 // FCONVB_SET_OUT_VSIZE0 Register
struct DISPIF_FCONVB_SET_OUT_VSIZE0 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int OUT_VSIZE0:10;		// [9:0]
};
 // FCONVB_SET_OUT_BASEADDR_GY0 Register
struct DISPIF_FCONVB_SET_OUT_BASEADDR_GY0 {
	unsigned int OUT_BADDR_GY0:32;		// [31:0]
};
 // FCONVB_SET_OUT_BASEADDR_BCB0 Register
struct DISPIF_FCONVB_SET_OUT_BASEADDR_BCB0 {
	unsigned int OUT_BADDR_BCB0:32;		// [31:0]
};
 // FCONVB_SET_OUT_BASEADDR_RCR0 Register
struct DISPIF_FCONVB_SET_OUT_BASEADDR_RCR0 {
	unsigned int OUT_BADDR_RCR0:32;		// [31:0]
};
 // FCONVB_SET_OUT_PITCH_GY0 Register
struct DISPIF_FCONVB_SET_OUT_PITCH_GY0 {
	unsigned int Reserved:20;		// [31:12]
	unsigned int OUT_PITCH_GY0:12;		// [11:0]
};
 // FCONVB_SET_OUT_PITCH_BCB0 Register
struct DISPIF_FCONVB_SET_OUT_PITCH_BCB0 {
	unsigned int Reserved:20;		// [31:12]
	unsigned int OUT_PITCH_BCB0:12;		// [11:0]
};
 // FCONVB_SET_OUT_PITCH_RCR0 Register
struct DISPIF_FCONVB_SET_OUT_PITCH_RCR0 {
	unsigned int Reserved:20;		// [31:12]
	unsigned int OUT_PITCH_RCR0:12;		// [11:0]
};
 // FCONVB_SET_FORCE_MODE0 Register
struct DISPIF_FCONVB_SET_FORCE_MODE0 {
	unsigned int Reserved:31;		// [31:1]
	unsigned int FORCE_MODE0:1;		// [0]
};
 // FCONVB_SET_FORCE_GY0 Register
struct DISPIF_FCONVB_SET_FORCE_GY0 {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_GY0:8;		// [7:0]
};
 // FCONVB_SET_FORCE_BCB0 Register
struct DISPIF_FCONVB_SET_FORCE_BCB0 {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_BCB0:8;		// [7:0]
};
 // FCONVB_SET_FORCE_RCR0 Register
struct DISPIF_FCONVB_SET_FORCE_RCR0 {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_RCR0:8;		// [7:0]
};
 // FCONVB_SET_FORCE_A0 Register
struct DISPIF_FCONVB_SET_FORCE_A0 {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_ALPHA0:8;		// [7:0]
};
 // FCONVB_SET_CROP0 Register
struct DISPIF_FCONVB_SET_CROP0 {
	unsigned int Reserved4:4;		// [31:28]
	unsigned int CROP_RIGHT0:4;		// [27:24]
	unsigned int Reserved3:4;		// [23:20]
	unsigned int CROP_LEFT0:4;		// [19:16]
	unsigned int Reserved2:4;		// [15:12]
	unsigned int CROP_LOWER0:4;		// [11:8]
	unsigned int Reserved:4;		// [7:4]
	unsigned int CROP_UPPER0:4;		// [3:0]
};
 // FCONVB_SET_IN_FORMAT1 Register
struct DISPIF_FCONVB_SET_IN_FORMAT1 {
	unsigned int Reserved4:8;		// [31:24]
	unsigned int IN_FORMATID1:8;		// [23:16]
	unsigned int Reserved3:7;		// [15:9]
	unsigned int IN_SCAN1:1;		// [8]
	unsigned int Reserved2:2;		// [7:6]
	unsigned int IN_PLANE1:2;		// [5:4]
	unsigned int Reserved:2;		// [3:2]
	unsigned int IN_COLORFORMAT1:2;		// [1:0]
};
 // FCONVB_SET_IN_HSIZE1 Register
struct DISPIF_FCONVB_SET_IN_HSIZE1 {
	unsigned int Reserved:21;		// [31:11]
	unsigned int IN_HSIZE1:11;		// [10:0]
};
 // FCONVB_SET_IN_VSIZE1 Register
struct DISPIF_FCONVB_SET_IN_VSIZE1 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int IN_VSIZE1:10;		// [9:0]
};
 // FCONVB_SET_IN_BASEADDR_GY1 Register
struct DISPIF_FCONVB_SET_IN_BASEADDR_GY1 {
	unsigned int IN_BADDR_GY1:32;		// [31:0]
};
 // FCONVB_SET_IN_BASEADDR_BCB1 Register
struct DISPIF_FCONVB_SET_IN_BASEADDR_BCB1 {
	unsigned int IN_BADDR_BCB1:32;		// [31:0]
};
 // FCONVB_SET_IN_BASEADDR_RCR1 Register
struct DISPIF_FCONVB_SET_IN_BASEADDR_RCR1 {
	unsigned int IN_BADDR_RCR1:32;		// [31:0]
};
 // FCONVB_SET_IN_PITCH_GY1 Register
struct DISPIF_FCONVB_SET_IN_PITCH_GY1 {
	unsigned int Reserved:20;		// [31:12]
	unsigned int IN_PITCH_GY1:12;		// [11:0]
};
 // FCONVB_SET_IN_PITCH_BCB1 Register
struct DISPIF_FCONVB_SET_IN_PITCH_BCB1 {
	unsigned int Reserved:20;		// [31:12]
	unsigned int IN_PITCH_BCB1:12;		// [11:0]
};
 // FCONVB_SET_IN_PITCH_RCR1 Register
struct DISPIF_FCONVB_SET_IN_PITCH_RCR1 {
	unsigned int Reserved:20;		// [31:12]
	unsigned int IN_PITCH_RCR1:12;		// [11:0]
};
 // FCONVB_SET_OUT_FORMAT1 Register
struct DISPIF_FCONVB_SET_OUT_FORMAT1 {
	unsigned int Reserved4:8;		// [31:24]
	unsigned int OUT_FORMATID1:8;		// [23:16]
	unsigned int Reserved3:7;		// [15:9]
	unsigned int OUT_SCAN1:1;		// [8]
	unsigned int Reserved2:2;		// [7:6]
	unsigned int OUT_PLANE1:2;		// [5:4]
	unsigned int Reserved:2;		// [3:2]
	unsigned int OUT_COLORFORMAT1:2;		// [1:0]
};
 // FCONVB_SET_OUT_HSIZE1 Register
struct DISPIF_FCONVB_SET_OUT_HSIZE1 {
	unsigned int Reserved:21;		// [31:11]
	unsigned int OUT_HSIZE1:11;		// [10:0]
};
 // FCONVB_SET_OUT_VSIZE1 Register
struct DISPIF_FCONVB_SET_OUT_VSIZE1 {
	unsigned int Reserved:22;		// [31:10]
	unsigned int OUT_VSIZE1:10;		// [9:0]
};
 // FCONVB_SET_OUT_BASEADDR_GY1 Register
struct DISPIF_FCONVB_SET_OUT_BASEADDR_GY1 {
	unsigned int OUT_BADDR_GY1:32;		// [31:0]
};
 // FCONVB_SET_OUT_BASEADDR_BCB1 Register
struct DISPIF_FCONVB_SET_OUT_BASEADDR_BCB1 {
	unsigned int OUT_BADDR_BCB1:32;		// [31:0]
};
 // FCONVB_SET_OUT_BASEADDR_RCR1 Register
struct DISPIF_FCONVB_SET_OUT_BASEADDR_RCR1 {
	unsigned int OUT_BADDR_RCR1:32;		// [31:0]
};
 // FCONVB_SET_OUT_PITCH_GY1 Register
struct DISPIF_FCONVB_SET_OUT_PITCH_GY1 {
	unsigned int Reserved:20;		// [31:12]
	unsigned int OUT_PITCH_GY1:12;		// [11:0]
};
 // FCONVB_SET_OUT_PITCH_BCB1 Register
struct DISPIF_FCONVB_SET_OUT_PITCH_BCB1 {
	unsigned int Reserved:20;		// [31:12]
	unsigned int OUT_PITCH_BCB1:12;		// [11:0]
};
 // FCONVB_SET_OUT_PITCH_RCR1 Register
struct DISPIF_FCONVB_SET_OUT_PITCH_RCR1 {
	unsigned int Reserved:20;		// [31:12]
	unsigned int OUT_PITCH_RCR1:12;		// [11:0]
};
 // FCONVB_SET_FORCE_MODE1 Register
struct DISPIF_FCONVB_SET_FORCE_MODE1 {
	unsigned int Reserved:31;		// [31:1]
	unsigned int FORCE_MODE1:1;		// [0]
};
 // FCONVB_SET_FORCE_GY1 Register
struct DISPIF_FCONVB_SET_FORCE_GY1 {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_GY1:8;		// [7:0]
};
 // FCONVB_SET_FORCE_BCB1 Register
struct DISPIF_FCONVB_SET_FORCE_BCB1 {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_BCB1:8;		// [7:0]
};
 // FCONVB_SET_FORCE_RCR1 Register
struct DISPIF_FCONVB_SET_FORCE_RCR1 {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_RCR1:8;		// [7:0]
};
 // FCONVB_SET_FORCE_A1 Register
struct DISPIF_FCONVB_SET_FORCE_A1 {
	unsigned int Reserved:24;		// [31:8]
	unsigned int FORCE_ALPHA1:8;		// [7:0]
};
 // FCONVB_SET_CROP1 Register
struct DISPIF_FCONVB_SET_CROP1 {
	unsigned int Reserved4:4;		// [31:28]
	unsigned int CROP_RIGHT1:4;		// [27:24]
	unsigned int Reserved3:4;		// [23:20]
	unsigned int CROP_LEFT1:4;		// [19:16]
	unsigned int Reserved2:4;		// [15:12]
	unsigned int CROP_LOWER1:4;		// [11:8]
	unsigned int Reserved:4;		// [7:4]
	unsigned int CROP_UPPER1:4;		// [3:0]
};
 // FCONVC_ACT Register
struct DISPIF_FCONVC_ACT {
	unsigned int Reserved:31;		// [31:1]
	unsigned int SeqAct:1;		// [0]
};
 // FCONVC_SETTING Register
struct DISPIF_FCONVC_SETTING {
	unsigned int Reserved3:19;		// [31:13]
	unsigned int Reserved2:4;		// [12:9]
	unsigned int PixelRep:1;		// [8]
	unsigned int Reserved:3;		// [7:5]
	unsigned int Interlace_B:1;		// [4]
	unsigned int Toggle_B:1;		// [3]
	unsigned int Interlace_A:1;		// [2]
	unsigned int Toggle_A:1;		// [1]
	unsigned int MergeK:1;		// [0]
};
 // FCONVC_KICKA_CHANNEL Register
struct DISPIF_FCONVC_KICKA_CHANNEL {
	unsigned int Reserved:31;		// [31:1]
	unsigned int Channel:1;		// [0]
};
 // FCONVC_KICKA_TB Register
struct DISPIF_FCONVC_KICKA_TB {
	unsigned int Reserved:31;		// [31:1]
	unsigned int Field:1;		// [0]
};
 // FCONVC_KICKB_CHANNEL Register
struct DISPIF_FCONVC_KICKB_CHANNEL {
	unsigned int Reserved:31;		// [31:1]
	unsigned int Channel:1;		// [0]
};
 // FCONVC_KICKB_TB Register
struct DISPIF_FCONVC_KICKB_TB {
	unsigned int Reserved:31;		// [31:1]
	unsigned int Field:1;		// [0]
};
 // FCONVC_MGSETTING Register
struct DISPIF_FCONVC_MGSETTING {
	unsigned int Reserved:28;		// [31:4]
	unsigned int AlphaModeA:2;		// [3:2]
	unsigned int AlphaModeB:2;		// [1:0]
};
 // FCONVC_DSIERRFIXVAL Register
struct DISPIF_FCONVC_DSIERRFIXVAL {
	unsigned int Reserved:2;		// [31:30]
	unsigned int FixDataR:10;		// [29:20]
	unsigned int FixDataG:10;		// [19:10]
	unsigned int FixDataB:10;		// [9:0]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DISPIF_REG_STRUCT_B_H */
