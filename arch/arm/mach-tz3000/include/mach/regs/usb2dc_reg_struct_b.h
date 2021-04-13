/*
 * arch/arm/mach-tz3000/include/mach/regs/usb2dc_reg_struct_b.h
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

#ifndef _USB2DC_REG_STRUCT_B_H
#define _USB2DC_REG_STRUCT_B_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // GOTGCTL Register
struct USB2DC_GOTGCTL {
	unsigned int Reserved:11;		// [31:21]
	unsigned int OTGVer:1;		// [20]
	unsigned int BSesVld:1;		// [19]
	unsigned int Reserved2:2;		// [18:17]
	unsigned int ConIDSts:1;		// [16]
	unsigned int Reserved3:4;		// [15:12]
	unsigned int DevHNPEn:1;		// [11]
	unsigned int Reserved4:1;		// [10]
	unsigned int HNPReq:1;		// [9]
	unsigned int HstNegScs:1;		// [8]
	unsigned int BvalidOvVal:1;		// [7]
	unsigned int BvalidOvEn:1;		// [6]
	unsigned int Reserved5:4;		// [5:2]
	unsigned int SesReq:1;		// [1]
	unsigned int SesReqScs:1;		// [0]
};
 // GOTGINT Register
struct USB2DC_GOTGINT {
	unsigned int Reserved:13;		// [31:19]
	unsigned int ADevTOUTChg:1;		// [18]
	unsigned int HstNegDet:1;		// [17]
	unsigned int Reserved2:7;		// [16:10]
	unsigned int HstNegSucStsChng:1;		// [9]
	unsigned int SesReqSucStsChng:1;		// [8]
	unsigned int Reserved3:5;		// [7:3]
	unsigned int SesEndDet:1;		// [2]
	unsigned int Reserved4:2;		// [1:0]
};
 // GAHBCFG Register
struct USB2DC_GAHBCFG {
	unsigned int Reserved:7;		// [31:25]
	unsigned int InvDescEndianess:1;		// [24]
	unsigned int AHBSingle:1;		// [23]
	unsigned int NotiAllDmaWrit:1;		// [22]
	unsigned int RemMemSupp:1;		// [21]
	unsigned int Reserved2:13;		// [20:8]
	unsigned int NPTxFEmpLvl:1;		// [7]
	unsigned int Reserved3:1;		// [6]
	unsigned int DMAEn:1;		// [5]
	unsigned int HBstLen:4;		// [4:1]
	unsigned int GlblIntrMsk:1;		// [0]
};
 // GUSBCFG Register
struct USB2DC_GUSBCFG {
	unsigned int CorruptTxPkt:1;		// [31]
	unsigned int Reserved:2;		// [30:29]
	unsigned int TxEndDelay:1;		// [28]
	unsigned int Reserved2:1;		// [27]
	unsigned int IC_USBCap:1;		// [26]
	unsigned int Reserved3:3;		// [25:23]
	unsigned int TermSelDLPulse:1;		// [22]
	unsigned int Reserved4:6;		// [21:16]
	unsigned int PhyLPwrClkSel:1;		// [15]
	unsigned int Reserved5:1;		// [14]
	unsigned int USBTrdTim:4;		// [13:10]
	unsigned int Reserved6:3;		// [9:7]
	unsigned int PHYSel:1;		// [6]
	unsigned int FSIntf:1;		// [5]
	unsigned int ULPI_UTMI_Sel:1;		// [4]
	unsigned int PHYIf:1;		// [3]
	unsigned int TOutCal:3;		// [2:0]
};
 // GRSTCTL Register
struct USB2DC_GRSTCTL {
	unsigned int AHBIdle:1;		// [31]
	unsigned int DMAReq:1;		// [30]
	unsigned int Reserved:19;		// [29:11]
	unsigned int TxFNum:5;		// [10:6]
	unsigned int TxFFlsh:1;		// [5]
	unsigned int RxFFlsh:1;		// [4]
	unsigned int Reserved2:3;		// [3:1]
	unsigned int CSftRst:1;		// [0]
};
 // GINTSTS Register
struct USB2DC_GINTSTS {
	unsigned int WkUpInt:1;		// [31]
	unsigned int SessReqInt:1;		// [30]
	unsigned int Reserved:1;		// [29]
	unsigned int ConIDStsChng:1;		// [28]
	unsigned int Reserved2:4;		// [27:24]
	unsigned int ResetDet:1;		// [23]
	unsigned int FetSusp:1;		// [22]
	unsigned int incompISOOUT:1;		// [21]
	unsigned int incompISOIN:1;		// [20]
	unsigned int OEPInt:1;		// [19]
	unsigned int IEPInt:1;		// [18]
	unsigned int EPMis:1;		// [17]
	unsigned int Reserved3:1;		// [16]
	unsigned int EOPF:1;		// [15]
	unsigned int ISOOutDrop:1;		// [14]
	unsigned int EnumDone:1;		// [13]
	unsigned int USBRst:1;		// [12]
	unsigned int USBSusp:1;		// [11]
	unsigned int ErlySusp:1;		// [10]
	unsigned int Reserved4:2;		// [9:8]
	unsigned int GOUTNakEff:1;		// [7]
	unsigned int GINNakEff:1;		// [6]
	unsigned int Reserved5:1;		// [5]
	unsigned int RxFLvl:1;		// [4]
	unsigned int Sof:1;		// [3]
	unsigned int OTGInt:1;		// [2]
	unsigned int ModeMis:1;		// [1]
	unsigned int CurMod:1;		// [0]
};
 // GINTMSK Register
struct USB2DC_GINTMSK {
	unsigned int WkUpIntMsk:1;		// [31]
	unsigned int SessReqIntMsk:1;		// [30]
	unsigned int DisconnIntMsk:1;		// [29]
	unsigned int ConIDStsChngMsk:1;		// [28]
	unsigned int Reserved:4;		// [27:24]
	unsigned int ResetDetMsk:1;		// [23]
	unsigned int FetSuspMsk:1;		// [22]
	unsigned int incompISOOUTMsk:1;		// [21]
	unsigned int incompISOINMsk:1;		// [20]
	unsigned int OEPIntMsk:1;		// [19]
	unsigned int IEPIntMsk:1;		// [18]
	unsigned int EPMisMsk:1;		// [17]
	unsigned int Reserved2:1;		// [16]
	unsigned int EOPFMsk:1;		// [15]
	unsigned int ISOOutDropMsk:1;		// [14]
	unsigned int EnumDoneMsk:1;		// [13]
	unsigned int USBRstMsk:1;		// [12]
	unsigned int USBSuspMsk:1;		// [11]
	unsigned int ErlySuspMsk:1;		// [10]
	unsigned int Reserved3:2;		// [9:8]
	unsigned int GOUTNakEffMsk:1;		// [7]
	unsigned int GINNakEffMsk:1;		// [6]
	unsigned int Reserved4:1;		// [5]
	unsigned int RxFLvlMsk:1;		// [4]
	unsigned int SofMsk:1;		// [3]
	unsigned int OTGIntMsk:1;		// [2]
	unsigned int ModeMisMsk:1;		// [1]
	unsigned int Reserved5:1;		// [0]
};
 // GRXSTSR Register
struct USB2DC_GRXSTSR {
	unsigned int Reserved:7;		// [31:25]
	unsigned int FN:4;		// [24:21]
	unsigned int PktSts:4;		// [20:17]
	unsigned int DPID:2;		// [16:15]
	unsigned int BCnt:11;		// [14:4]
	unsigned int EPNum:4;		// [3:0]
};
 // GRXSTSP Register
struct USB2DC_GRXSTSP {
	unsigned int Reserved:7;		// [31:25]
	unsigned int FN:4;		// [24:21]
	unsigned int PktSts:4;		// [20:17]
	unsigned int DPID:2;		// [16:15]
	unsigned int BCnt:11;		// [14:4]
	unsigned int EPNum:4;		// [3:0]
};
 // GRXFSIZ Register
struct USB2DC_GRXFSIZ {
	unsigned int Reserved:20;		// [31:12]
	unsigned int RxFDep:12;		// [11:0]
};
 // GNPTXFSIZ Register
struct USB2DC_GNPTXFSIZ {
	unsigned int Reserved:9;		// [31:23]
	unsigned int INEPTxF0Dep:7;		// [22:16]
	unsigned int Reserved2:4;		// [15:12]
	unsigned int INEPTxF0StAddr:12;		// [11:0]
};
 // GSNPSID Register
struct USB2DC_GSNPSID {
	unsigned int SynopsysID:32;		// [31:0]
};
 // GHWCFG1 Register
struct USB2DC_GHWCFG1 {
	unsigned int EpDir:32;		// [31:0]
};
 // GHWCFG2 Register
struct USB2DC_GHWCFG2 {
	unsigned int Reserved:1;		// [31]
	unsigned int TknQDepth:5;		// [30:26]
	unsigned int PTxQDepth:2;		// [25:24]
	unsigned int NPTxQDepth:2;		// [23:22]
	unsigned int Reserved2:1;		// [21]
	unsigned int MultiProcIntrpt:1;		// [20]
	unsigned int DynFifoSizing:1;		// [19]
	unsigned int PerioSupport:1;		// [18]
	unsigned int NumHstChnl:4;		// [17:14]
	unsigned int NumDevEps:4;		// [13:10]
	unsigned int FSPhyType:2;		// [9:8]
	unsigned int HSPhyType:2;		// [7:6]
	unsigned int SingPnt:1;		// [5]
	unsigned int OtgArch:2;		// [4:3]
	unsigned int OtgMode:3;		// [2:0]
};
 // GHWCFG3 Register
struct USB2DC_GHWCFG3 {
	unsigned int DfifoDepth:16;		// [31:16]
	unsigned int LPMMode:1;		// [15]
	unsigned int BCSupport:1;		// [14]
	unsigned int HSICMode:1;		// [13]
	unsigned int ADPSupport:1;		// [12]
	unsigned int RstType:1;		// [11]
	unsigned int OptFeature:1;		// [10]
	unsigned int VndctlSupt:1;		// [9]
	unsigned int I2CIntSel:1;		// [8]
	unsigned int OtgEn:1;		// [7]
	unsigned int PktSizeWidth:3;		// [6:4]
	unsigned int XferSizeWidth:4;		// [3:0]
};
 // GHWCFG4 Register
struct USB2DC_GHWCFG4 {
	unsigned int DescDMA:1;		// [31]
	unsigned int DescDMAEnabled:1;		// [30]
	unsigned int INEps:4;		// [29:26]
	unsigned int DedFifoMode:1;		// [25]
	unsigned int SessEndFltr:1;		// [24]
	unsigned int BValidFltr:1;		// [23]
	unsigned int AValidFltr:1;		// [22]
	unsigned int VBusValidFltr:1;		// [21]
	unsigned int IddgFltr:1;		// [20]
	unsigned int NumCtlEps:4;		// [19:16]
	unsigned int PhyDataWidth:2;		// [15:14]
	unsigned int Reserved:6;		// [13:8]
	unsigned int ExtendedHibernation:1;		// [7]
	unsigned int Hibernation:1;		// [6]
	unsigned int AhbFreq:1;		// [5]
	unsigned int PartialPwrDn:1;		// [4]
	unsigned int NumDevPerioEps:4;		// [3:0]
};
 // GDFIFOCFG Register
struct USB2DC_GDFIFOCFG {
	unsigned int EPInfoBaseAddr:16;		// [31:16]
	unsigned int GDFIFOCfg:16;		// [15:0]
};
 // DIEPTXF1 Register
struct USB2DC_DIEPTXF1 {
	unsigned int Reserved:6;		// [31:26]
	unsigned int INEPnTxFDep:10;		// [25:16]
	unsigned int Reserved2:4;		// [15:12]
	unsigned int INEPnTxFStAddr:12;		// [11:0]
};
 // DIEPTXF2 Register
struct USB2DC_DIEPTXF2 {
	unsigned int Reserved:6;		// [31:26]
	unsigned int INEPnTxFDep:10;		// [25:16]
	unsigned int Reserved2:3;		// [15:13]
	unsigned int INEPnTxFStAddr:13;		// [12:0]
};
 // DIEPTXF3 Register
struct USB2DC_DIEPTXF3 {
	unsigned int Reserved:6;		// [31:26]
	unsigned int INEPnTxFDep:10;		// [25:16]
	unsigned int Reserved2:3;		// [15:13]
	unsigned int INEPnTxFStAddr:13;		// [12:0]
};
 // DIEPTXF4 Register
struct USB2DC_DIEPTXF4 {
	unsigned int reserved:6;		// [31:26]
	unsigned int INEPnTxFDep:10;		// [25:16]
	unsigned int reserved2:3;		// [15:13]
	unsigned int INEPnTxFStAddr:13;		// [12:0]
};
 // DIEPTXF5 Register
struct USB2DC_DIEPTXF5 {
	unsigned int reserved:7;		// [31:25]
	unsigned int INEPnTxFDep:9;		// [24:16]
	unsigned int reserved2:3;		// [15:13]
	unsigned int INEPnTxFStAddr:13;		// [12:0]
};
 // DIEPTXF6 Register
struct USB2DC_DIEPTXF6 {
	unsigned int reserved:7;		// [31:25]
	unsigned int INEPnTxFDep:9;		// [24:16]
	unsigned int reserved2:3;		// [15:13]
	unsigned int INEPnTxFStAddr:13;		// [12:0]
};
 // DCFG Register
struct USB2DC_DCFG {
	unsigned int ResValid:6;		// [31:26]
	unsigned int PerSchIntvl:2;		// [25:24]
	unsigned int DescDMA:1;		// [23]
	unsigned int Reserved:9;		// [22:14]
	unsigned int EnDevOutNak:1;		// [13]
	unsigned int PerFrInt:2;		// [12:11]
	unsigned int DevAddr:7;		// [10:4]
	unsigned int Ena32KHzSusp:1;		// [3]
	unsigned int NZStsOUTHShk:1;		// [2]
	unsigned int DevSpd:2;		// [1:0]
};
 // DCTL Register
struct USB2DC_DCTL {
	unsigned int Reserved:14;		// [31:18]
	unsigned int EnContOnBNA:1;		// [17]
	unsigned int NakOnBble:1;		// [16]
	unsigned int IgnrFrmNum:1;		// [15]
	unsigned int GMC:2;		// [14:13]
	unsigned int Reserved2:1;		// [12]
	unsigned int PWROnPrgDone:1;		// [11]
	unsigned int CGOUTNak:1;		// [10]
	unsigned int SGOUTNak:1;		// [9]
	unsigned int CGNPInNak:1;		// [8]
	unsigned int SGNPInNak:1;		// [7]
	unsigned int TstCtl:3;		// [6:4]
	unsigned int GOUTNakSts:1;		// [3]
	unsigned int GNPINNakSts:1;		// [2]
	unsigned int SftDiscon:1;		// [1]
	unsigned int RmtWkUpSig:1;		// [0]
};
 // DSTS Register
struct USB2DC_DSTS {
	unsigned int Reserved:8;		// [31:24]
	unsigned int DevLnSts:2;		// [23:22]
	unsigned int SOFFN:14;		// [21:8]
	unsigned int Reserved2:4;		// [7:4]
	unsigned int ErrticErr:1;		// [3]
	unsigned int EnumSpd:2;		// [2:1]
	unsigned int SuspSts:1;		// [0]
};
 // DIEPMSK Register
struct USB2DC_DIEPMSK {
	unsigned int Reserved:18;		// [31:14]
	unsigned int NAKMsk:1;		// [13]
	unsigned int Reserved2:3;		// [12:10]
	unsigned int BNAInIntrMsk:1;		// [9]
	unsigned int TxfifoUndrnMsk:1;		// [8]
	unsigned int Reserved3:1;		// [7]
	unsigned int INEPNakEffMsk:1;		// [6]
	unsigned int INTknEPMisMsk:1;		// [5]
	unsigned int INTknTXFEmpMsk:1;		// [4]
	unsigned int TimeOUTMsk:1;		// [3]
	unsigned int AHBErrMsk:1;		// [2]
	unsigned int EPDisbldMsk:1;		// [1]
	unsigned int XferComplMsk:1;		// [0]
};
 // DOEPMSK Register
struct USB2DC_DOEPMSK {
	unsigned int Reserved:17;		// [31:15]
	unsigned int NYETMsk:1;		// [14]
	unsigned int NAKMsk:1;		// [13]
	unsigned int BbleErrMsk:1;		// [12]
	unsigned int Reserved2:2;		// [11:10]
	unsigned int BnaOutIntrMsk:1;		// [9]
	unsigned int OutPktErrMsk:1;		// [8]
	unsigned int Reserved3:1;		// [7]
	unsigned int Back2BackSETup:1;		// [6]
	unsigned int StsPhseRcvdMsk:1;		// [5]
	unsigned int OUTTknEPdisMsk:1;		// [4]
	unsigned int SetUPMsk:1;		// [3]
	unsigned int AHBErrMsk:1;		// [2]
	unsigned int EPDisbldMsk:1;		// [1]
	unsigned int XferComplMsk:1;		// [0]
};
 // DAINT Register
struct USB2DC_DAINT {
	unsigned int Reserved:9;		// [31:23]
	unsigned int OutEPInt6:1;		// [22]
	unsigned int OutEPInt5:1;		// [21]
	unsigned int OutEPInt4:1;		// [20]
	unsigned int OutEPInt3:1;		// [19]
	unsigned int OutEPInt2:1;		// [18]
	unsigned int OutEPInt1:1;		// [17]
	unsigned int OutEPInt0:1;		// [16]
	unsigned int Reserved2:9;		// [15:7]
	unsigned int InEpInt6:1;		// [6]
	unsigned int InEpInt5:1;		// [5]
	unsigned int InEpInt4:1;		// [4]
	unsigned int InEpInt3:1;		// [3]
	unsigned int InEpInt2:1;		// [2]
	unsigned int InEpInt1:1;		// [1]
	unsigned int InEpInt0:1;		// [0]
};
 // DAINTMSK Register
struct USB2DC_DAINTMSK {
	unsigned int Reserved:9;		// [31:23]
	unsigned int OutEPMsk6:1;		// [22]
	unsigned int OutEPMsk5:1;		// [21]
	unsigned int OutEPMsk4:1;		// [20]
	unsigned int OutEPMsk3:1;		// [19]
	unsigned int OutEPMsk2:1;		// [18]
	unsigned int OutEPMsk1:1;		// [17]
	unsigned int OutEPMsk0:1;		// [16]
	unsigned int Reserved2:9;		// [15:7]
	unsigned int InEpMsk6:1;		// [6]
	unsigned int InEpMsk5:1;		// [5]
	unsigned int InEpMsk4:1;		// [4]
	unsigned int InEpMsk3:1;		// [3]
	unsigned int InEpMsk2:1;		// [2]
	unsigned int InEpMsk1:1;		// [1]
	unsigned int InEpMsk0:1;		// [0]
};
 // DVBUSDIS Register
struct USB2DC_DVBUSDIS {
	unsigned int Reserved:16;		// [31:16]
	unsigned int DVBUSDis:16;		// [15:0]
};
 // DVBUSPULSE Register
struct USB2DC_DVBUSPULSE {
	unsigned int Reserved:20;		// [31:12]
	unsigned int DVBUSPulse:12;		// [11:0]
};
 // DTHRCTL Register
struct USB2DC_DTHRCTL {
	unsigned int Reserved:4;		// [31:28]
	unsigned int ArbPrkEn:1;		// [27]
	unsigned int Reserved2:1;		// [26]
	unsigned int RxThrLen:9;		// [25:17]
	unsigned int RxThrEn:1;		// [16]
	unsigned int Reserved3:3;		// [15:13]
	unsigned int AHBThrRatio:2;		// [12:11]
	unsigned int TxThrLen:9;		// [10:2]
	unsigned int ISOThrEn:1;		// [1]
	unsigned int NonISOThrEn:1;		// [0]
};
 // DIEPEMPMSK Register
struct USB2DC_DIEPEMPMSK {
	unsigned int Reserved:16;		// [31:16]
	unsigned int InEpTxfEmpMsk:16;		// [15:0]
};
 // DEACHINT Register
struct USB2DC_DEACHINT {
	unsigned int EchOutEPInt:16;		// [31:16]
	unsigned int EchInEpInt:16;		// [15:0]
};
 // DEACHINTMSK Register
struct USB2DC_DEACHINTMSK {
	unsigned int EchOutEpMsk:16;		// [31:16]
	unsigned int EchInEpMsk:16;		// [15:0]
};
 // DIEPEACHMSK0 Register
struct USB2DC_DIEPEACHMSK0 {
	unsigned int Reserved:18;		// [31:14]
	unsigned int NAKMsk:1;		// [13]
	unsigned int Reserved2:3;		// [12:10]
	unsigned int BNAInIntrMsk:1;		// [9]
	unsigned int TxfifoUndrnMsk:1;		// [8]
	unsigned int Reserved3:1;		// [7]
	unsigned int INEPNakEffMsk:1;		// [6]
	unsigned int INTknEPMisMsk:1;		// [5]
	unsigned int INTknTXFEmpMsk:1;		// [4]
	unsigned int TimeOUTMsk:1;		// [3]
	unsigned int AHBErrMsk:1;		// [2]
	unsigned int EPDisbldMsk:1;		// [1]
	unsigned int XferComplMsk:1;		// [0]
};
 // DIEPEACHMSK1 Register
struct USB2DC_DIEPEACHMSK1 {
	unsigned int Reserved:18;		// [31:14]
	unsigned int NAKMsk:1;		// [13]
	unsigned int Reserved2:3;		// [12:10]
	unsigned int BNAInIntrMsk:1;		// [9]
	unsigned int TxfifoUndrnMsk:1;		// [8]
	unsigned int Reserved3:1;		// [7]
	unsigned int INEPNakEffMsk:1;		// [6]
	unsigned int INTknEPMisMsk:1;		// [5]
	unsigned int INTknTXFEmpMsk:1;		// [4]
	unsigned int TimeOUTMsk:1;		// [3]
	unsigned int AHBErrMsk:1;		// [2]
	unsigned int EPDisbldMsk:1;		// [1]
	unsigned int XferComplMsk:1;		// [0]
};
 // DIEPEACHMSK2 Register
struct USB2DC_DIEPEACHMSK2 {
	unsigned int Reserved:18;		// [31:14]
	unsigned int NAKMsk:1;		// [13]
	unsigned int Reserved2:3;		// [12:10]
	unsigned int BNAInIntrMsk:1;		// [9]
	unsigned int TxfifoUndrnMsk:1;		// [8]
	unsigned int Reserved3:1;		// [7]
	unsigned int INEPNakEffMsk:1;		// [6]
	unsigned int INTknEPMisMsk:1;		// [5]
	unsigned int INTknTXFEmpMsk:1;		// [4]
	unsigned int TimeOUTMsk:1;		// [3]
	unsigned int AHBErrMsk:1;		// [2]
	unsigned int EPDisbldMsk:1;		// [1]
	unsigned int XferComplMsk:1;		// [0]
};
 // DIEPEACHMSK3 Register
struct USB2DC_DIEPEACHMSK3 {
	unsigned int Reserved:18;		// [31:14]
	unsigned int NAKMsk:1;		// [13]
	unsigned int Reserved2:3;		// [12:10]
	unsigned int BNAInIntrMsk:1;		// [9]
	unsigned int TxfifoUndrnMsk:1;		// [8]
	unsigned int Reserved3:1;		// [7]
	unsigned int INEPNakEffMsk:1;		// [6]
	unsigned int INTknEPMisMsk:1;		// [5]
	unsigned int INTknTXFEmpMsk:1;		// [4]
	unsigned int TimeOUTMsk:1;		// [3]
	unsigned int AHBErrMsk:1;		// [2]
	unsigned int EPDisbldMsk:1;		// [1]
	unsigned int XferComplMsk:1;		// [0]
};
 // DIEPEACHMSK4 Register
struct USB2DC_DIEPEACHMSK4 {
	unsigned int Reserved:18;		// [31:14]
	unsigned int NAKMsk:1;		// [13]
	unsigned int Reserved2:3;		// [12:10]
	unsigned int BNAInIntrMsk:1;		// [9]
	unsigned int TxfifoUndrnMsk:1;		// [8]
	unsigned int Reserved3:1;		// [7]
	unsigned int INEPNakEffMsk:1;		// [6]
	unsigned int INTknEPMisMsk:1;		// [5]
	unsigned int INTknTXFEmpMsk:1;		// [4]
	unsigned int TimeOUTMsk:1;		// [3]
	unsigned int AHBErrMsk:1;		// [2]
	unsigned int EPDisbldMsk:1;		// [1]
	unsigned int XferComplMsk:1;		// [0]
};
 // DIEPEACHMSK5 Register
struct USB2DC_DIEPEACHMSK5 {
	unsigned int Reserved:18;		// [31:14]
	unsigned int NAKMsk:1;		// [13]
	unsigned int Reserved2:3;		// [12:10]
	unsigned int BNAInIntrMsk:1;		// [9]
	unsigned int TxfifoUndrnMsk:1;		// [8]
	unsigned int Reserved3:1;		// [7]
	unsigned int INEPNakEffMsk:1;		// [6]
	unsigned int INTknEPMisMsk:1;		// [5]
	unsigned int INTknTXFEmpMsk:1;		// [4]
	unsigned int TimeOUTMsk:1;		// [3]
	unsigned int AHBErrMsk:1;		// [2]
	unsigned int EPDisbldMsk:1;		// [1]
	unsigned int XferComplMsk:1;		// [0]
};
 // DIEPEACHMSK6 Register
struct USB2DC_DIEPEACHMSK6 {
	unsigned int Reserved:18;		// [31:14]
	unsigned int NAKMsk:1;		// [13]
	unsigned int Reserved2:3;		// [12:10]
	unsigned int BNAInIntrMsk:1;		// [9]
	unsigned int TxfifoUndrnMsk:1;		// [8]
	unsigned int Reserved3:1;		// [7]
	unsigned int INEPNakEffMsk:1;		// [6]
	unsigned int INTknEPMisMsk:1;		// [5]
	unsigned int INTknTXFEmpMsk:1;		// [4]
	unsigned int TimeOUTMsk:1;		// [3]
	unsigned int AHBErrMsk:1;		// [2]
	unsigned int EPDisbldMsk:1;		// [1]
	unsigned int XferComplMsk:1;		// [0]
};
 // DOEPEACHMSK0 Register
struct USB2DC_DOEPEACHMSK0 {
	unsigned int Reserved:17;		// [31:15]
	unsigned int NYETMsk:1;		// [14]
	unsigned int NAKMsk:1;		// [13]
	unsigned int BbleErrMsk:1;		// [12]
	unsigned int Reserved2:2;		// [11:10]
	unsigned int BnaOutIntrMsk:1;		// [9]
	unsigned int OutPktErrMsk:1;		// [8]
	unsigned int Reserved3:1;		// [7]
	unsigned int Back2BackSETup:1;		// [6]
	unsigned int Reserved4:1;		// [5]
	unsigned int OUTTknEPdisMsk:1;		// [4]
	unsigned int SetUPMsk:1;		// [3]
	unsigned int AHBErrMsk:1;		// [2]
	unsigned int EPDisbldMsk:1;		// [1]
	unsigned int XferComplMsk:1;		// [0]
};
 // DOEPEACHMSK1 Register
struct USB2DC_DOEPEACHMSK1 {
	unsigned int Reserved:17;		// [31:15]
	unsigned int NYETMsk:1;		// [14]
	unsigned int NAKMsk:1;		// [13]
	unsigned int BbleErrMsk:1;		// [12]
	unsigned int Reserved2:2;		// [11:10]
	unsigned int BnaOutIntrMsk:1;		// [9]
	unsigned int OutPktErrMsk:1;		// [8]
	unsigned int Reserved3:1;		// [7]
	unsigned int Back2BackSETup:1;		// [6]
	unsigned int Reserved4:1;		// [5]
	unsigned int OUTTknEPdisMsk:1;		// [4]
	unsigned int SetUPMsk:1;		// [3]
	unsigned int AHBErrMsk:1;		// [2]
	unsigned int EPDisbldMsk:1;		// [1]
	unsigned int XferComplMsk:1;		// [0]
};
 // DOEPEACHMSK2 Register
struct USB2DC_DOEPEACHMSK2 {
	unsigned int Reserved:17;		// [31:15]
	unsigned int NYETMsk:1;		// [14]
	unsigned int NAKMsk:1;		// [13]
	unsigned int BbleErrMsk:1;		// [12]
	unsigned int Reserved2:2;		// [11:10]
	unsigned int BnaOutIntrMsk:1;		// [9]
	unsigned int OutPktErrMsk:1;		// [8]
	unsigned int Reserved3:1;		// [7]
	unsigned int Back2BackSETup:1;		// [6]
	unsigned int Reserved4:1;		// [5]
	unsigned int OUTTknEPdisMsk:1;		// [4]
	unsigned int SetUPMsk:1;		// [3]
	unsigned int AHBErrMsk:1;		// [2]
	unsigned int EPDisbldMsk:1;		// [1]
	unsigned int XferComplMsk:1;		// [0]
};
 // DOEPEACHMSK3 Register
struct USB2DC_DOEPEACHMSK3 {
	unsigned int Reserved:17;		// [31:15]
	unsigned int NYETMsk:1;		// [14]
	unsigned int NAKMsk:1;		// [13]
	unsigned int BbleErrMsk:1;		// [12]
	unsigned int Reserved2:2;		// [11:10]
	unsigned int BnaOutIntrMsk:1;		// [9]
	unsigned int OutPktErrMsk:1;		// [8]
	unsigned int Reserved3:1;		// [7]
	unsigned int Back2BackSETup:1;		// [6]
	unsigned int Reserved4:1;		// [5]
	unsigned int OUTTknEPdisMsk:1;		// [4]
	unsigned int SetUPMsk:1;		// [3]
	unsigned int AHBErrMsk:1;		// [2]
	unsigned int EPDisbldMsk:1;		// [1]
	unsigned int XferComplMsk:1;		// [0]
};
 // DOEPEACHMSK4 Register
struct USB2DC_DOEPEACHMSK4 {
	unsigned int Reserved:17;		// [31:15]
	unsigned int NYETMsk:1;		// [14]
	unsigned int NAKMsk:1;		// [13]
	unsigned int BbleErrMsk:1;		// [12]
	unsigned int Reserved2:2;		// [11:10]
	unsigned int BnaOutIntrMsk:1;		// [9]
	unsigned int OutPktErrMsk:1;		// [8]
	unsigned int Reserved3:1;		// [7]
	unsigned int Back2BackSETup:1;		// [6]
	unsigned int Reserved4:1;		// [5]
	unsigned int OUTTknEPdisMsk:1;		// [4]
	unsigned int SetUPMsk:1;		// [3]
	unsigned int AHBErrMsk:1;		// [2]
	unsigned int EPDisbldMsk:1;		// [1]
	unsigned int XferComplMsk:1;		// [0]
};
 // DOEPEACHMSK5 Register
struct USB2DC_DOEPEACHMSK5 {
	unsigned int Reserved:17;		// [31:15]
	unsigned int NYETMsk:1;		// [14]
	unsigned int NAKMsk:1;		// [13]
	unsigned int BbleErrMsk:1;		// [12]
	unsigned int Reserved2:2;		// [11:10]
	unsigned int BnaOutIntrMsk:1;		// [9]
	unsigned int OutPktErrMsk:1;		// [8]
	unsigned int Reserved3:1;		// [7]
	unsigned int Back2BackSETup:1;		// [6]
	unsigned int Reserved4:1;		// [5]
	unsigned int OUTTknEPdisMsk:1;		// [4]
	unsigned int SetUPMsk:1;		// [3]
	unsigned int AHBErrMsk:1;		// [2]
	unsigned int EPDisbldMsk:1;		// [1]
	unsigned int XferComplMsk:1;		// [0]
};
 // DOEPEACHMSK6 Register
struct USB2DC_DOEPEACHMSK6 {
	unsigned int Reserved:17;		// [31:15]
	unsigned int NYETMsk:1;		// [14]
	unsigned int NAKMsk:1;		// [13]
	unsigned int BbleErrMsk:1;		// [12]
	unsigned int Reserved2:2;		// [11:10]
	unsigned int BnaOutIntrMsk:1;		// [9]
	unsigned int OutPktErrMsk:1;		// [8]
	unsigned int Reserved3:1;		// [7]
	unsigned int Back2BackSETup:1;		// [6]
	unsigned int Reserved4:1;		// [5]
	unsigned int OUTTknEPdisMsk:1;		// [4]
	unsigned int SetUPMsk:1;		// [3]
	unsigned int AHBErrMsk:1;		// [2]
	unsigned int EPDisbldMsk:1;		// [1]
	unsigned int XferComplMsk:1;		// [0]
};
 // DIEPCTL0 Register
struct USB2DC_DIEPCTL0 {
	unsigned int EPEna:1;		// [31]
	unsigned int EPDis:1;		// [30]
	unsigned int Reserved:2;		// [29:28]
	unsigned int SNAK:1;		// [27]
	unsigned int CNAK:1;		// [26]
	unsigned int TxFNum:4;		// [25:22]
	unsigned int Stall:1;		// [21]
	unsigned int Reserved2:1;		// [20]
	unsigned int EPType:2;		// [19:18]
	unsigned int NAKSts:1;		// [17]
	unsigned int Reserved3:1;		// [16]
	unsigned int USBActEP:1;		// [15]
	unsigned int Reserved4:13;		// [14:2]
	unsigned int MPS:2;		// [1:0]
};
 // DIEPINT0 Register
struct USB2DC_DIEPINT0 {
	unsigned int Reserved:17;		// [31:15]
	unsigned int NYETIntrpt:1;		// [14]
	unsigned int NAKIntrpt:1;		// [13]
	unsigned int BbleErr:1;		// [12]
	unsigned int PktDrpSts:1;		// [11]
	unsigned int Reserved2:1;		// [10]
	unsigned int BNAIntr:1;		// [9]
	unsigned int TxfifoUndrn:1;		// [8]
	unsigned int TxFEmp:1;		// [7]
	unsigned int INEPNakEff:1;		// [6]
	unsigned int INTknEPMis:1;		// [5]
	unsigned int INTknTXFEmp:1;		// [4]
	unsigned int TimeOUT:1;		// [3]
	unsigned int AHBErr:1;		// [2]
	unsigned int EPDisbld:1;		// [1]
	unsigned int XferCompl:1;		// [0]
};
 // DIEPTSIZ0 Register
struct USB2DC_DIEPTSIZ0 {
	unsigned int Reserved:11;		// [31:21]
	unsigned int PktCnt:2;		// [20:19]
	unsigned int Reserved2:12;		// [18:7]
	unsigned int XferSize:7;		// [6:0]
};
 // DIEPDMA0 Register
struct USB2DC_DIEPDMA0 {
	unsigned int DMAAddr:32;		// [31:0]
};
 // DTXFSTS0 Register
struct USB2DC_DTXFSTS0 {
	unsigned int Reserved:16;		// [31:16]
	unsigned int INEPTxFSpcAvail:16;		// [15:0]
};
 // DIEPDMAB0 Register
struct USB2DC_DIEPDMAB0 {
	unsigned int DMABufferAddr:32;		// [31:0]
};
 // DIEPCTL1 Register
struct USB2DC_DIEPCTL1 {
	unsigned int EPEna:1;		// [31]
	unsigned int EPDis:1;		// [30]
	unsigned int SetD1PID:1;		// [29]
	unsigned int SetD0PID:1;		// [28]
	unsigned int SNAK:1;		// [27]
	unsigned int CNAK:1;		// [26]
	unsigned int TxFNum:4;		// [25:22]
	unsigned int Stall:1;		// [21]
	unsigned int Reserved:1;		// [20]
	unsigned int EPType:2;		// [19:18]
	unsigned int NAKSts:1;		// [17]
	unsigned int DPID:1;		// [16]
	unsigned int USBActEP:1;		// [15]
	unsigned int Reserved2:4;		// [14:11]
	unsigned int MPS:11;		// [10:0]
};
 // DIEPINT1 Register
struct USB2DC_DIEPINT1 {
	unsigned int Reserved:17;		// [31:15]
	unsigned int NYETIntrpt:1;		// [14]
	unsigned int NAKIntrpt:1;		// [13]
	unsigned int BbleErr:1;		// [12]
	unsigned int PktDrpSts:1;		// [11]
	unsigned int Reserved2:1;		// [10]
	unsigned int BNAIntr:1;		// [9]
	unsigned int TxfifoUndrn:1;		// [8]
	unsigned int TxFEmp:1;		// [7]
	unsigned int INEPNakEff:1;		// [6]
	unsigned int INTknEPMis:1;		// [5]
	unsigned int INTknTXFEmp:1;		// [4]
	unsigned int TimeOUT:1;		// [3]
	unsigned int AHBErr:1;		// [2]
	unsigned int EPDisbld:1;		// [1]
	unsigned int XferCompl:1;		// [0]
};
 // DIEPTSIZ1 Register
struct USB2DC_DIEPTSIZ1 {
	unsigned int Reserved:1;		// [31]
	unsigned int MC:2;		// [30:29]
	unsigned int PktCnt:10;		// [28:19]
	unsigned int XferSize:19;		// [18:0]
};
 // DIEPDMA1 Register
struct USB2DC_DIEPDMA1 {
	unsigned int DMAAddr:32;		// [31:0]
};
 // DTXFSTS1 Register
struct USB2DC_DTXFSTS1 {
	unsigned int Reserved:16;		// [31:16]
	unsigned int INEPTxFSpcAvail:16;		// [15:0]
};
 // DIEPDMAB1 Register
struct USB2DC_DIEPDMAB1 {
	unsigned int DMABufferAddr:32;		// [31:0]
};
 // DIEPCTL2 Register
struct USB2DC_DIEPCTL2 {
	unsigned int EPEna:1;		// [31]
	unsigned int EPDis:1;		// [30]
	unsigned int SetD1PID:1;		// [29]
	unsigned int SetD0PID:1;		// [28]
	unsigned int SNAK:1;		// [27]
	unsigned int CNAK:1;		// [26]
	unsigned int TxFNum:4;		// [25:22]
	unsigned int Stall:1;		// [21]
	unsigned int Reserved:1;		// [20]
	unsigned int EPType:2;		// [19:18]
	unsigned int NAKSts:1;		// [17]
	unsigned int DPID:1;		// [16]
	unsigned int USBActEP:1;		// [15]
	unsigned int Reserved2:4;		// [14:11]
	unsigned int MPS:11;		// [10:0]
};
 // DIEPINT2 Register
struct USB2DC_DIEPINT2 {
	unsigned int Reserved:17;		// [31:15]
	unsigned int NYETIntrpt:1;		// [14]
	unsigned int NAKIntrpt:1;		// [13]
	unsigned int BbleErr:1;		// [12]
	unsigned int PktDrpSts:1;		// [11]
	unsigned int Reserved2:1;		// [10]
	unsigned int BNAIntr:1;		// [9]
	unsigned int TxfifoUndrn:1;		// [8]
	unsigned int TxFEmp:1;		// [7]
	unsigned int INEPNakEff:1;		// [6]
	unsigned int INTknEPMis:1;		// [5]
	unsigned int INTknTXFEmp:1;		// [4]
	unsigned int TimeOUT:1;		// [3]
	unsigned int AHBErr:1;		// [2]
	unsigned int EPDisbld:1;		// [1]
	unsigned int XferCompl:1;		// [0]
};
 // DIEPTSIZ2 Register
struct USB2DC_DIEPTSIZ2 {
	unsigned int Reserved:1;		// [31]
	unsigned int MC:2;		// [30:29]
	unsigned int PktCnt:10;		// [28:19]
	unsigned int XferSize:19;		// [18:0]
};
 // DIEPDMA2 Register
struct USB2DC_DIEPDMA2 {
	unsigned int DMAAddr:32;		// [31:0]
};
 // DTXFSTS2 Register
struct USB2DC_DTXFSTS2 {
	unsigned int Reserved:16;		// [31:16]
	unsigned int INEPTxFSpcAvail:16;		// [15:0]
};
 // DIEPDMAB2 Register
struct USB2DC_DIEPDMAB2 {
	unsigned int DMABufferAddr:32;		// [31:0]
};
 // DIEPCTL3 Register
struct USB2DC_DIEPCTL3 {
	unsigned int EPEna:1;		// [31]
	unsigned int EPDis:1;		// [30]
	unsigned int SetD1PID:1;		// [29]
	unsigned int SetD0PID:1;		// [28]
	unsigned int SNAK:1;		// [27]
	unsigned int CNAK:1;		// [26]
	unsigned int TxFNum:4;		// [25:22]
	unsigned int Stall:1;		// [21]
	unsigned int Reserved:1;		// [20]
	unsigned int EPType:2;		// [19:18]
	unsigned int NAKSts:1;		// [17]
	unsigned int DPID:1;		// [16]
	unsigned int USBActEP:1;		// [15]
	unsigned int Reserved2:4;		// [14:11]
	unsigned int MPS:11;		// [10:0]
};
 // DIEPINT3 Register
struct USB2DC_DIEPINT3 {
	unsigned int Reserved:17;		// [31:15]
	unsigned int NYETIntrpt:1;		// [14]
	unsigned int NAKIntrpt:1;		// [13]
	unsigned int BbleErr:1;		// [12]
	unsigned int PktDrpSts:1;		// [11]
	unsigned int Reserved2:1;		// [10]
	unsigned int BNAIntr:1;		// [9]
	unsigned int TxfifoUndrn:1;		// [8]
	unsigned int TxFEmp:1;		// [7]
	unsigned int INEPNakEff:1;		// [6]
	unsigned int INTknEPMis:1;		// [5]
	unsigned int INTknTXFEmp:1;		// [4]
	unsigned int TimeOUT:1;		// [3]
	unsigned int AHBErr:1;		// [2]
	unsigned int EPDisbld:1;		// [1]
	unsigned int XferCompl:1;		// [0]
};
 // DIEPTSIZ3 Register
struct USB2DC_DIEPTSIZ3 {
	unsigned int Reserved:1;		// [31]
	unsigned int MC:2;		// [30:29]
	unsigned int PktCnt:10;		// [28:19]
	unsigned int XferSize:19;		// [18:0]
};
 // DIEPDMA3 Register
struct USB2DC_DIEPDMA3 {
	unsigned int DMAAddr:32;		// [31:0]
};
 // DTXFSTS3 Register
struct USB2DC_DTXFSTS3 {
	unsigned int Reserved:16;		// [31:16]
	unsigned int INEPTxFSpcAvail:16;		// [15:0]
};
 // DIEPDMAB3 Register
struct USB2DC_DIEPDMAB3 {
	unsigned int DMABufferAddr:32;		// [31:0]
};
 // DIEPCTL4 Register
struct USB2DC_DIEPCTL4 {
	unsigned int EPEna:1;		// [31]
	unsigned int EPDis:1;		// [30]
	unsigned int SetD1PID:1;		// [29]
	unsigned int SetD0PID:1;		// [28]
	unsigned int SNAK:1;		// [27]
	unsigned int CNAK:1;		// [26]
	unsigned int TxFNum:4;		// [25:22]
	unsigned int Stall:1;		// [21]
	unsigned int reserved:1;		// [20]
	unsigned int EPType:2;		// [19:18]
	unsigned int NAKSts:1;		// [17]
	unsigned int DPID:1;		// [16]
	unsigned int USBActEP:1;		// [15]
	unsigned int reserved2:4;		// [14:11]
	unsigned int MPS:11;		// [10:0]
};
 // DIEPINT4 Register
struct USB2DC_DIEPINT4 {
	unsigned int reserved:17;		// [31:15]
	unsigned int NYETIntrpt:1;		// [14]
	unsigned int NAKIntrpt:1;		// [13]
	unsigned int BbleErr:1;		// [12]
	unsigned int PktDrpSts:1;		// [11]
	unsigned int reserved2:1;		// [10]
	unsigned int BNAIntr:1;		// [9]
	unsigned int TxfifoUndrn:1;		// [8]
	unsigned int TxFEmp:1;		// [7]
	unsigned int INEPNakEff:1;		// [6]
	unsigned int INTknEPMis:1;		// [5]
	unsigned int INTknTXFEmp:1;		// [4]
	unsigned int TimeOUT:1;		// [3]
	unsigned int AHBErr:1;		// [2]
	unsigned int EPDisbld:1;		// [1]
	unsigned int XferCompl:1;		// [0]
};
 // DIEPTSIZ4 Register
struct USB2DC_DIEPTSIZ4 {
	unsigned int reserved:1;		// [31]
	unsigned int MC:2;		// [30:29]
	unsigned int PktCnt:10;		// [28:19]
	unsigned int XferSize:19;		// [18:0]
};
 // DIEPDMA4 Register
struct USB2DC_DIEPDMA4 {
	unsigned int DMAAddr:32;		// [31:0]
};
 // DTXFSTS4 Register
struct USB2DC_DTXFSTS4 {
	unsigned int reserved:16;		// [31:16]
	unsigned int INEPTxFSpcAvail:16;		// [15:0]
};
 // DIEPDMAB4 Register
struct USB2DC_DIEPDMAB4 {
	unsigned int DMABufferAddr:32;		// [31:0]
};
 // DIEPCTL5 Register
struct USB2DC_DIEPCTL5 {
	unsigned int EPEna:1;		// [31]
	unsigned int EPDis:1;		// [30]
	unsigned int SetD1PID:1;		// [29]
	unsigned int SetD0PID:1;		// [28]
	unsigned int SNAK:1;		// [27]
	unsigned int CNAK:1;		// [26]
	unsigned int TxFNum:4;		// [25:22]
	unsigned int Stall:1;		// [21]
	unsigned int reserved:1;		// [20]
	unsigned int EPType:2;		// [19:18]
	unsigned int NAKSts:1;		// [17]
	unsigned int DPID:1;		// [16]
	unsigned int USBActEP:1;		// [15]
	unsigned int reserved2:4;		// [14:11]
	unsigned int MPS:11;		// [10:0]
};
 // DIEPINT5 Register
struct USB2DC_DIEPINT5 {
	unsigned int reserved:17;		// [31:15]
	unsigned int NYETIntrpt:1;		// [14]
	unsigned int NAKIntrpt:1;		// [13]
	unsigned int BbleErr:1;		// [12]
	unsigned int PktDrpSts:1;		// [11]
	unsigned int reserved2:1;		// [10]
	unsigned int BNAIntr:1;		// [9]
	unsigned int TxfifoUndrn:1;		// [8]
	unsigned int TxFEmp:1;		// [7]
	unsigned int INEPNakEff:1;		// [6]
	unsigned int INTknEPMis:1;		// [5]
	unsigned int INTknTXFEmp:1;		// [4]
	unsigned int TimeOUT:1;		// [3]
	unsigned int AHBErr:1;		// [2]
	unsigned int EPDisbld:1;		// [1]
	unsigned int XferCompl:1;		// [0]
};
 // DIEPTSIZ5 Register
struct USB2DC_DIEPTSIZ5 {
	unsigned int reserved:1;		// [31]
	unsigned int MC:2;		// [30:29]
	unsigned int PktCnt:10;		// [28:19]
	unsigned int XferSize:19;		// [18:0]
};
 // DIEPDMA5 Register
struct USB2DC_DIEPDMA5 {
	unsigned int DMAAddr:32;		// [31:0]
};
 // DTXFSTS5 Register
struct USB2DC_DTXFSTS5 {
	unsigned int reserved:16;		// [31:16]
	unsigned int INEPTxFSpcAvail:16;		// [15:0]
};
 // DIEPDMAB5 Register
struct USB2DC_DIEPDMAB5 {
	unsigned int DMABufferAddr:32;		// [31:0]
};
 // DIEPCTL6 Register
struct USB2DC_DIEPCTL6 {
	unsigned int EPEna:1;		// [31]
	unsigned int EPDis:1;		// [30]
	unsigned int SetD1PID:1;		// [29]
	unsigned int SetD0PID:1;		// [28]
	unsigned int SNAK:1;		// [27]
	unsigned int CNAK:1;		// [26]
	unsigned int TxFNum:4;		// [25:22]
	unsigned int Stall:1;		// [21]
	unsigned int reserved:1;		// [20]
	unsigned int EPType:2;		// [19:18]
	unsigned int NAKSts:1;		// [17]
	unsigned int DPID:1;		// [16]
	unsigned int USBActEP:1;		// [15]
	unsigned int reserved2:4;		// [14:11]
	unsigned int MPS:11;		// [10:0]
};
 // DIEPINT6 Register
struct USB2DC_DIEPINT6 {
	unsigned int reserved:17;		// [31:15]
	unsigned int NYETIntrpt:1;		// [14]
	unsigned int NAKIntrpt:1;		// [13]
	unsigned int BbleErr:1;		// [12]
	unsigned int PktDrpSts:1;		// [11]
	unsigned int reserved2:1;		// [10]
	unsigned int BNAIntr:1;		// [9]
	unsigned int TxfifoUndrn:1;		// [8]
	unsigned int TxFEmp:1;		// [7]
	unsigned int INEPNakEff:1;		// [6]
	unsigned int INTknEPMis:1;		// [5]
	unsigned int INTknTXFEmp:1;		// [4]
	unsigned int TimeOUT:1;		// [3]
	unsigned int AHBErr:1;		// [2]
	unsigned int EPDisbld:1;		// [1]
	unsigned int XferCompl:1;		// [0]
};
 // DIEPTSIZ6 Register
struct USB2DC_DIEPTSIZ6 {
	unsigned int reserved:1;		// [31]
	unsigned int MC:2;		// [30:29]
	unsigned int PktCnt:10;		// [28:19]
	unsigned int XferSize:19;		// [18:0]
};
 // DIEPDMA6 Register
struct USB2DC_DIEPDMA6 {
	unsigned int DMAAddr:32;		// [31:0]
};
 // DTXFSTS6 Register
struct USB2DC_DTXFSTS6 {
	unsigned int reserved:16;		// [31:16]
	unsigned int INEPTxFSpcAvail:16;		// [15:0]
};
 // DIEPDMAB6 Register
struct USB2DC_DIEPDMAB6 {
	unsigned int DMABufferAddr:32;		// [31:0]
};
 // DOEPCTL0 Register
struct USB2DC_DOEPCTL0 {
	unsigned int EPEna:1;		// [31]
	unsigned int EPDis:1;		// [30]
	unsigned int Reserved:2;		// [29:28]
	unsigned int SNAK:1;		// [27]
	unsigned int CNAK:1;		// [26]
	unsigned int Reserved2:4;		// [25:22]
	unsigned int Stall:1;		// [21]
	unsigned int Snp:1;		// [20]
	unsigned int EPType:2;		// [19:18]
	unsigned int NAKSts:1;		// [17]
	unsigned int Reserved3:1;		// [16]
	unsigned int USBActEP:1;		// [15]
	unsigned int Reserved4:13;		// [14:2]
	unsigned int MPS:2;		// [1:0]
};
 // DOEPINT0 Register
struct USB2DC_DOEPINT0 {
	unsigned int Reserved:17;		// [31:15]
	unsigned int NYETIntrpt:1;		// [14]
	unsigned int NAKIntrpt:1;		// [13]
	unsigned int BbleErr:1;		// [12]
	unsigned int PktDrpSts:1;		// [11]
	unsigned int Reserved2:1;		// [10]
	unsigned int BNAIntr:1;		// [9]
	unsigned int OutPktErr:1;		// [8]
	unsigned int Reserved3:1;		// [7]
	unsigned int Back2BackSETup:1;		// [6]
	unsigned int StsPhseRcvd:1;		// [5]
	unsigned int OUTTknEPdis:1;		// [4]
	unsigned int SetUp:1;		// [3]
	unsigned int AHBErr:1;		// [2]
	unsigned int EPDisbld:1;		// [1]
	unsigned int XferCompl:1;		// [0]
};
 // DOEPTSIZ0 Register
struct USB2DC_DOEPTSIZ0 {
	unsigned int Reserved:1;		// [31]
	unsigned int SUPCnt:2;		// [30:29]
	unsigned int Reserved2:9;		// [28:20]
	unsigned int PktCnt:1;		// [19]
	unsigned int Reserved3:12;		// [18:7]
	unsigned int XferSize:7;		// [6:0]
};
 // DOEPDMA0 Register
struct USB2DC_DOEPDMA0 {
	unsigned int DMAAddr:32;		// [31:0]
};
 // DOEPDMAB0 Register
struct USB2DC_DOEPDMAB0 {
	unsigned int DMABufferAddr:32;		// [31:0]
};
 // DOEPCTL1 Register
struct USB2DC_DOEPCTL1 {
	unsigned int EPEna:1;		// [31]
	unsigned int EPDis:1;		// [30]
	unsigned int SetD1PID:1;		// [29]
	unsigned int SetD0PID:1;		// [28]
	unsigned int SNAK:1;		// [27]
	unsigned int CNAK:1;		// [26]
	unsigned int Reserved:4;		// [25:22]
	unsigned int Stall:1;		// [21]
	unsigned int Snp:1;		// [20]
	unsigned int EPType:2;		// [19:18]
	unsigned int NAKSts:1;		// [17]
	unsigned int DPID:1;		// [16]
	unsigned int USBActEP:1;		// [15]
	unsigned int Reserved2:4;		// [14:11]
	unsigned int MPS:11;		// [10:0]
};
 // DOEPINT1 Register
struct USB2DC_DOEPINT1 {
	unsigned int Reserved:17;		// [31:15]
	unsigned int NYETIntrpt:1;		// [14]
	unsigned int NAKIntrpt:1;		// [13]
	unsigned int BbleErr:1;		// [12]
	unsigned int PktDrpSts:1;		// [11]
	unsigned int Reserved2:1;		// [10]
	unsigned int BNAIntr:1;		// [9]
	unsigned int OutPktErr:1;		// [8]
	unsigned int Reserved3:1;		// [7]
	unsigned int Back2BackSETup:1;		// [6]
	unsigned int StsPhseRcvd:1;		// [5]
	unsigned int OUTTknEPdis:1;		// [4]
	unsigned int SetUp:1;		// [3]
	unsigned int AHBErr:1;		// [2]
	unsigned int EPDisbld:1;		// [1]
	unsigned int XferCompl:1;		// [0]
};
 // DOEPTSIZ1 Register
struct USB2DC_DOEPTSIZ1 {
	unsigned int Reserved:1;		// [31]
	unsigned int RxDPID:2;		// [30:29]
	unsigned int PktCnt:10;		// [28:19]
	unsigned int XferSize:19;		// [18:0]
};
 // DOEPDMA1 Register
struct USB2DC_DOEPDMA1 {
	unsigned int DMAAddr:32;		// [31:0]
};
 // DOEPDMAB1 Register
struct USB2DC_DOEPDMAB1 {
	unsigned int DMABufferAddr:32;		// [31:0]
};
 // DOEPCTL2 Register
struct USB2DC_DOEPCTL2 {
	unsigned int EPEna:1;		// [31]
	unsigned int EPDis:1;		// [30]
	unsigned int SetD1PID:1;		// [29]
	unsigned int SetD0PID:1;		// [28]
	unsigned int SNAK:1;		// [27]
	unsigned int CNAK:1;		// [26]
	unsigned int Reserved:4;		// [25:22]
	unsigned int Stall:1;		// [21]
	unsigned int Snp:1;		// [20]
	unsigned int EPType:2;		// [19:18]
	unsigned int NAKSts:1;		// [17]
	unsigned int DPID:1;		// [16]
	unsigned int USBActEP:1;		// [15]
	unsigned int Reserved2:4;		// [14:11]
	unsigned int MPS:11;		// [10:0]
};
 // DOEPINT2 Register
struct USB2DC_DOEPINT2 {
	unsigned int Reserved:17;		// [31:15]
	unsigned int NYETIntrpt:1;		// [14]
	unsigned int NAKIntrpt:1;		// [13]
	unsigned int BbleErr:1;		// [12]
	unsigned int PktDrpSts:1;		// [11]
	unsigned int Reserved2:1;		// [10]
	unsigned int BNAIntr:1;		// [9]
	unsigned int OutPktErr:1;		// [8]
	unsigned int Reserved3:1;		// [7]
	unsigned int Back2BackSETup:1;		// [6]
	unsigned int StsPhseRcvd:1;		// [5]
	unsigned int OUTTknEPdis:1;		// [4]
	unsigned int SetUp:1;		// [3]
	unsigned int AHBErr:1;		// [2]
	unsigned int EPDisbld:1;		// [1]
	unsigned int XferCompl:1;		// [0]
};
 // DOEPTSIZ2 Register
struct USB2DC_DOEPTSIZ2 {
	unsigned int Reserved:1;		// [31]
	unsigned int RxDPID:2;		// [30:29]
	unsigned int PktCnt:10;		// [28:19]
	unsigned int XferSize:19;		// [18:0]
};
 // DOEPDMA2 Register
struct USB2DC_DOEPDMA2 {
	unsigned int DMAAddr:32;		// [31:0]
};
 // DOEPDMAB2 Register
struct USB2DC_DOEPDMAB2 {
	unsigned int DMABufferAddr:32;		// [31:0]
};
 // DOEPCTL3 Register
struct USB2DC_DOEPCTL3 {
	unsigned int EPEna:1;		// [31]
	unsigned int EPDis:1;		// [30]
	unsigned int SetD1PID:1;		// [29]
	unsigned int SetD0PID:1;		// [28]
	unsigned int SNAK:1;		// [27]
	unsigned int CNAK:1;		// [26]
	unsigned int Reserved:4;		// [25:22]
	unsigned int Stall:1;		// [21]
	unsigned int Snp:1;		// [20]
	unsigned int EPType:2;		// [19:18]
	unsigned int NAKSts:1;		// [17]
	unsigned int DPID:1;		// [16]
	unsigned int USBActEP:1;		// [15]
	unsigned int Reserved2:4;		// [14:11]
	unsigned int MPS:11;		// [10:0]
};
 // DOEPINT3 Register
struct USB2DC_DOEPINT3 {
	unsigned int Reserved:17;		// [31:15]
	unsigned int NYETIntrpt:1;		// [14]
	unsigned int NAKIntrpt:1;		// [13]
	unsigned int BbleErr:1;		// [12]
	unsigned int PktDrpSts:1;		// [11]
	unsigned int Reserved2:1;		// [10]
	unsigned int BNAIntr:1;		// [9]
	unsigned int OutPktErr:1;		// [8]
	unsigned int Reserved3:1;		// [7]
	unsigned int Back2BackSETup:1;		// [6]
	unsigned int StsPhseRcvd:1;		// [5]
	unsigned int OUTTknEPdis:1;		// [4]
	unsigned int SetUp:1;		// [3]
	unsigned int AHBErr:1;		// [2]
	unsigned int EPDisbld:1;		// [1]
	unsigned int XferCompl:1;		// [0]
};
 // DOEPTSIZ3 Register
struct USB2DC_DOEPTSIZ3 {
	unsigned int Reserved:1;		// [31]
	unsigned int RxDPID:2;		// [30:29]
	unsigned int PktCnt:10;		// [28:19]
	unsigned int XferSize:19;		// [18:0]
};
 // DOEPDMA3 Register
struct USB2DC_DOEPDMA3 {
	unsigned int DMAAddr:32;		// [31:0]
};
 // DOEPDMAB3 Register
struct USB2DC_DOEPDMAB3 {
	unsigned int DMABufferAddr:32;		// [31:0]
};
 // DOEPCTL4 Register
struct USB2DC_DOEPCTL4 {
	unsigned int EPEna:1;		// [31]
	unsigned int EPDis:1;		// [30]
	unsigned int SetD1PID:1;		// [29]
	unsigned int SetD0PID:1;		// [28]
	unsigned int SNAK:1;		// [27]
	unsigned int CNAK:1;		// [26]
	unsigned int reserved:4;		// [25:22]
	unsigned int Stall:1;		// [21]
	unsigned int Snp:1;		// [20]
	unsigned int EPType:2;		// [19:18]
	unsigned int NAKSts:1;		// [17]
	unsigned int DPID:1;		// [16]
	unsigned int USBActEP:1;		// [15]
	unsigned int reserved2:4;		// [14:11]
	unsigned int MPS:11;		// [10:0]
};
 // DOEPINT4 Register
struct USB2DC_DOEPINT4 {
	unsigned int reserved:17;		// [31:15]
	unsigned int NYETIntrpt:1;		// [14]
	unsigned int NAKIntrpt:1;		// [13]
	unsigned int BbleErr:1;		// [12]
	unsigned int PktDrpSts:1;		// [11]
	unsigned int reserved2:1;		// [10]
	unsigned int BNAIntr:1;		// [9]
	unsigned int OutPktErr:1;		// [8]
	unsigned int reserved3:1;		// [7]
	unsigned int Back2BackSETup:1;		// [6]
	unsigned int StsPhseRcvd:1;		// [5]
	unsigned int OUTTknEPdis:1;		// [4]
	unsigned int SetUp:1;		// [3]
	unsigned int AHBErr:1;		// [2]
	unsigned int EPDisbld:1;		// [1]
	unsigned int XferCompl:1;		// [0]
};
 // DOEPTSIZ4 Register
struct USB2DC_DOEPTSIZ4 {
	unsigned int reserved:1;		// [31]
	unsigned int RxDPID:2;		// [30:29]
	unsigned int PktCnt:10;		// [28:19]
	unsigned int XferSize:19;		// [18:0]
};
 // DOEPDMA4 Register
struct USB2DC_DOEPDMA4 {
	unsigned int DMAAddr:32;		// [31:0]
};
 // DOEPDMAB4 Register
struct USB2DC_DOEPDMAB4 {
	unsigned int DMABufferAddr:32;		// [31:0]
};
 // DOEPCTL5 Register
struct USB2DC_DOEPCTL5 {
	unsigned int EPEna:1;		// [31]
	unsigned int EPDis:1;		// [30]
	unsigned int SetD1PID:1;		// [29]
	unsigned int SetD0PID:1;		// [28]
	unsigned int SNAK:1;		// [27]
	unsigned int CNAK:1;		// [26]
	unsigned int reserved:4;		// [25:22]
	unsigned int Stall:1;		// [21]
	unsigned int Snp:1;		// [20]
	unsigned int EPType:2;		// [19:18]
	unsigned int NAKSts:1;		// [17]
	unsigned int DPID:1;		// [16]
	unsigned int USBActEP:1;		// [15]
	unsigned int reserved2:4;		// [14:11]
	unsigned int MPS:11;		// [10:0]
};
 // DOEPINT5 Register
struct USB2DC_DOEPINT5 {
	unsigned int reserved:17;		// [31:15]
	unsigned int NYETIntrpt:1;		// [14]
	unsigned int NAKIntrpt:1;		// [13]
	unsigned int BbleErr:1;		// [12]
	unsigned int PktDrpSts:1;		// [11]
	unsigned int reserved2:1;		// [10]
	unsigned int BNAIntr:1;		// [9]
	unsigned int OutPktErr:1;		// [8]
	unsigned int reserved3:1;		// [7]
	unsigned int Back2BackSETup:1;		// [6]
	unsigned int StsPhseRcvd:1;		// [5]
	unsigned int OUTTknEPdis:1;		// [4]
	unsigned int SetUp:1;		// [3]
	unsigned int AHBErr:1;		// [2]
	unsigned int EPDisbld:1;		// [1]
	unsigned int XferCompl:1;		// [0]
};
 // DOEPTSIZ5 Register
struct USB2DC_DOEPTSIZ5 {
	unsigned int reserved:1;		// [31]
	unsigned int RxDPID:2;		// [30:29]
	unsigned int PktCnt:10;		// [28:19]
	unsigned int XferSize:19;		// [18:0]
};
 // DOEPDMA5 Register
struct USB2DC_DOEPDMA5 {
	unsigned int DMAAddr:32;		// [31:0]
};
 // DOEPDMAB5 Register
struct USB2DC_DOEPDMAB5 {
	unsigned int DMABufferAddr:32;		// [31:0]
};
 // DOEPCTL6 Register
struct USB2DC_DOEPCTL6 {
	unsigned int EPEna:1;		// [31]
	unsigned int EPDis:1;		// [30]
	unsigned int SetD1PID:1;		// [29]
	unsigned int SetD0PID:1;		// [28]
	unsigned int SNAK:1;		// [27]
	unsigned int CNAK:1;		// [26]
	unsigned int reserved:4;		// [25:22]
	unsigned int Stall:1;		// [21]
	unsigned int Snp:1;		// [20]
	unsigned int EPType:2;		// [19:18]
	unsigned int NAKSts:1;		// [17]
	unsigned int DPID:1;		// [16]
	unsigned int USBActEP:1;		// [15]
	unsigned int reserved2:4;		// [14:11]
	unsigned int MPS:11;		// [10:0]
};
 // DOEPINT6 Register
struct USB2DC_DOEPINT6 {
	unsigned int reserved:17;		// [31:15]
	unsigned int NYETIntrpt:1;		// [14]
	unsigned int NAKIntrpt:1;		// [13]
	unsigned int BbleErr:1;		// [12]
	unsigned int PktDrpSts:1;		// [11]
	unsigned int reserved2:1;		// [10]
	unsigned int BNAIntr:1;		// [9]
	unsigned int OutPktErr:1;		// [8]
	unsigned int reserved3:1;		// [7]
	unsigned int Back2BackSETup:1;		// [6]
	unsigned int StsPhseRcvd:1;		// [5]
	unsigned int OUTTknEPdis:1;		// [4]
	unsigned int SetUp:1;		// [3]
	unsigned int AHBErr:1;		// [2]
	unsigned int EPDisbld:1;		// [1]
	unsigned int XferCompl:1;		// [0]
};
 // DOEPTSIZ6 Register
struct USB2DC_DOEPTSIZ6 {
	unsigned int reserved:1;		// [31]
	unsigned int RxDPID:2;		// [30:29]
	unsigned int PktCnt:10;		// [28:19]
	unsigned int XferSize:19;		// [18:0]
};
 // DOEPDMA6 Register
struct USB2DC_DOEPDMA6 {
	unsigned int DMAAddr:32;		// [31:0]
};
 // DOEPDMAB6 Register
struct USB2DC_DOEPDMAB6 {
	unsigned int DMABufferAddr:32;		// [31:0]
};
 // PCGCCTL Register
struct USB2DC_PCGCCTL {
	unsigned int Reserved:24;		// [31:8]
	unsigned int L1Suspended:1;		// [7]
	unsigned int PhySleep:1;		// [6]
	unsigned int Reserved2:2;		// [5:4]
	unsigned int RstPdwnModule:1;		// [3]
	unsigned int PwrClmp:1;		// [2]
	unsigned int GateHclk:1;		// [1]
	unsigned int StopPclk:1;		// [0]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _USB2DC_REG_STRUCT_B_H */
