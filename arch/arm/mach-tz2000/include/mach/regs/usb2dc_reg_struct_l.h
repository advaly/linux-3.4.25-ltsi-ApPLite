/*
 * arch/arm/mach-tz2000/include/mach/regs/usb2dc_reg_struct_l.h
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

#ifndef _USB2DC_REG_STRUCT_L_H
#define _USB2DC_REG_STRUCT_L_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // GOTGCTL Register
struct USB2DC_GOTGCTL {
	unsigned int SesReqScs:1;		// [0]
	unsigned int SesReq:1;		// [1]
	unsigned int Reserved5:4;		// [5:2]
	unsigned int BvalidOvEn:1;		// [6]
	unsigned int BvalidOvVal:1;		// [7]
	unsigned int HstNegScs:1;		// [8]
	unsigned int HNPReq:1;		// [9]
	unsigned int Reserved4:1;		// [10]
	unsigned int DevHNPEn:1;		// [11]
	unsigned int Reserved3:4;		// [15:12]
	unsigned int ConIDSts:1;		// [16]
	unsigned int Reserved2:2;		// [18:17]
	unsigned int BSesVld:1;		// [19]
	unsigned int OTGVer:1;		// [20]
	unsigned int Reserved:11;		// [31:21]
};
 // GOTGINT Register
struct USB2DC_GOTGINT {
	unsigned int Reserved4:2;		// [1:0]
	unsigned int SesEndDet:1;		// [2]
	unsigned int Reserved3:5;		// [7:3]
	unsigned int SesReqSucStsChng:1;		// [8]
	unsigned int HstNegSucStsChng:1;		// [9]
	unsigned int Reserved2:7;		// [16:10]
	unsigned int HstNegDet:1;		// [17]
	unsigned int ADevTOUTChg:1;		// [18]
	unsigned int Reserved:13;		// [31:19]
};
 // GAHBCFG Register
struct USB2DC_GAHBCFG {
	unsigned int GlblIntrMsk:1;		// [0]
	unsigned int HBstLen:4;		// [4:1]
	unsigned int DMAEn:1;		// [5]
	unsigned int Reserved3:1;		// [6]
	unsigned int NPTxFEmpLvl:1;		// [7]
	unsigned int Reserved2:13;		// [20:8]
	unsigned int RemMemSupp:1;		// [21]
	unsigned int NotiAllDmaWrit:1;		// [22]
	unsigned int AHBSingle:1;		// [23]
	unsigned int InvDescEndianess:1;		// [24]
	unsigned int Reserved:7;		// [31:25]
};
 // GUSBCFG Register
struct USB2DC_GUSBCFG {
	unsigned int TOutCal:3;		// [2:0]
	unsigned int PHYIf:1;		// [3]
	unsigned int ULPI_UTMI_Sel:1;		// [4]
	unsigned int FSIntf:1;		// [5]
	unsigned int PHYSel:1;		// [6]
	unsigned int Reserved6:3;		// [9:7]
	unsigned int USBTrdTim:4;		// [13:10]
	unsigned int Reserved5:1;		// [14]
	unsigned int PhyLPwrClkSel:1;		// [15]
	unsigned int Reserved4:6;		// [21:16]
	unsigned int TermSelDLPulse:1;		// [22]
	unsigned int Reserved3:3;		// [25:23]
	unsigned int IC_USBCap:1;		// [26]
	unsigned int Reserved2:1;		// [27]
	unsigned int TxEndDelay:1;		// [28]
	unsigned int Reserved:2;		// [30:29]
	unsigned int CorruptTxPkt:1;		// [31]
};
 // GRSTCTL Register
struct USB2DC_GRSTCTL {
	unsigned int CSftRst:1;		// [0]
	unsigned int Reserved2:3;		// [3:1]
	unsigned int RxFFlsh:1;		// [4]
	unsigned int TxFFlsh:1;		// [5]
	unsigned int TxFNum:5;		// [10:6]
	unsigned int Reserved:19;		// [29:11]
	unsigned int DMAReq:1;		// [30]
	unsigned int AHBIdle:1;		// [31]
};
 // GINTSTS Register
struct USB2DC_GINTSTS {
	unsigned int CurMod:1;		// [0]
	unsigned int ModeMis:1;		// [1]
	unsigned int OTGInt:1;		// [2]
	unsigned int Sof:1;		// [3]
	unsigned int RxFLvl:1;		// [4]
	unsigned int Reserved5:1;		// [5]
	unsigned int GINNakEff:1;		// [6]
	unsigned int GOUTNakEff:1;		// [7]
	unsigned int Reserved4:2;		// [9:8]
	unsigned int ErlySusp:1;		// [10]
	unsigned int USBSusp:1;		// [11]
	unsigned int USBRst:1;		// [12]
	unsigned int EnumDone:1;		// [13]
	unsigned int ISOOutDrop:1;		// [14]
	unsigned int EOPF:1;		// [15]
	unsigned int Reserved3:1;		// [16]
	unsigned int EPMis:1;		// [17]
	unsigned int IEPInt:1;		// [18]
	unsigned int OEPInt:1;		// [19]
	unsigned int incompISOIN:1;		// [20]
	unsigned int incompISOOUT:1;		// [21]
	unsigned int FetSusp:1;		// [22]
	unsigned int ResetDet:1;		// [23]
	unsigned int Reserved2:4;		// [27:24]
	unsigned int ConIDStsChng:1;		// [28]
	unsigned int Reserved:1;		// [29]
	unsigned int SessReqInt:1;		// [30]
	unsigned int WkUpInt:1;		// [31]
};
 // GINTMSK Register
struct USB2DC_GINTMSK {
	unsigned int Reserved5:1;		// [0]
	unsigned int ModeMisMsk:1;		// [1]
	unsigned int OTGIntMsk:1;		// [2]
	unsigned int SofMsk:1;		// [3]
	unsigned int RxFLvlMsk:1;		// [4]
	unsigned int Reserved4:1;		// [5]
	unsigned int GINNakEffMsk:1;		// [6]
	unsigned int GOUTNakEffMsk:1;		// [7]
	unsigned int Reserved3:2;		// [9:8]
	unsigned int ErlySuspMsk:1;		// [10]
	unsigned int USBSuspMsk:1;		// [11]
	unsigned int USBRstMsk:1;		// [12]
	unsigned int EnumDoneMsk:1;		// [13]
	unsigned int ISOOutDropMsk:1;		// [14]
	unsigned int EOPFMsk:1;		// [15]
	unsigned int Reserved2:1;		// [16]
	unsigned int EPMisMsk:1;		// [17]
	unsigned int IEPIntMsk:1;		// [18]
	unsigned int OEPIntMsk:1;		// [19]
	unsigned int incompISOINMsk:1;		// [20]
	unsigned int incompISOOUTMsk:1;		// [21]
	unsigned int FetSuspMsk:1;		// [22]
	unsigned int ResetDetMsk:1;		// [23]
	unsigned int Reserved:4;		// [27:24]
	unsigned int ConIDStsChngMsk:1;		// [28]
	unsigned int DisconnIntMsk:1;		// [29]
	unsigned int SessReqIntMsk:1;		// [30]
	unsigned int WkUpIntMsk:1;		// [31]
};
 // GRXSTSR Register
struct USB2DC_GRXSTSR {
	unsigned int EPNum:4;		// [3:0]
	unsigned int BCnt:11;		// [14:4]
	unsigned int DPID:2;		// [16:15]
	unsigned int PktSts:4;		// [20:17]
	unsigned int FN:4;		// [24:21]
	unsigned int Reserved:7;		// [31:25]
};
 // GRXSTSP Register
struct USB2DC_GRXSTSP {
	unsigned int EPNum:4;		// [3:0]
	unsigned int BCnt:11;		// [14:4]
	unsigned int DPID:2;		// [16:15]
	unsigned int PktSts:4;		// [20:17]
	unsigned int FN:4;		// [24:21]
	unsigned int Reserved:7;		// [31:25]
};
 // GRXFSIZ Register
struct USB2DC_GRXFSIZ {
	unsigned int RxFDep:11;		// [10:0]
	unsigned int Reserved:21;		// [31:11]
};
 // GNPTXFSIZ Register
struct USB2DC_GNPTXFSIZ {
	unsigned int INEPTxF0StAddr:11;		// [10:0]
	unsigned int Reserved2:5;		// [15:11]
	unsigned int INEPTxF0Dep:7;		// [22:16]
	unsigned int Reserved:9;		// [31:23]
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
	unsigned int OtgMode:3;		// [2:0]
	unsigned int OtgArch:2;		// [4:3]
	unsigned int SingPnt:1;		// [5]
	unsigned int HSPhyType:2;		// [7:6]
	unsigned int FSPhyType:2;		// [9:8]
	unsigned int NumDevEps:4;		// [13:10]
	unsigned int NumHstChnl:4;		// [17:14]
	unsigned int PerioSupport:1;		// [18]
	unsigned int DynFifoSizing:1;		// [19]
	unsigned int MultiProcIntrpt:1;		// [20]
	unsigned int Reserved2:1;		// [21]
	unsigned int NPTxQDepth:2;		// [23:22]
	unsigned int PTxQDepth:2;		// [25:24]
	unsigned int TknQDepth:5;		// [30:26]
	unsigned int Reserved:1;		// [31]
};
 // GHWCFG3 Register
struct USB2DC_GHWCFG3 {
	unsigned int XferSizeWidth:4;		// [3:0]
	unsigned int PktSizeWidth:3;		// [6:4]
	unsigned int OtgEn:1;		// [7]
	unsigned int I2CIntSel:1;		// [8]
	unsigned int VndctlSupt:1;		// [9]
	unsigned int OptFeature:1;		// [10]
	unsigned int RstType:1;		// [11]
	unsigned int ADPSupport:1;		// [12]
	unsigned int HSICMode:1;		// [13]
	unsigned int BCSupport:1;		// [14]
	unsigned int LPMMode:1;		// [15]
	unsigned int DfifoDepth:16;		// [31:16]
};
 // GHWCFG4 Register
struct USB2DC_GHWCFG4 {
	unsigned int NumDevPerioEps:4;		// [3:0]
	unsigned int PartialPwrDn:1;		// [4]
	unsigned int AhbFreq:1;		// [5]
	unsigned int Hibernation:1;		// [6]
	unsigned int ExtendedHibernation:1;		// [7]
	unsigned int Reserved:6;		// [13:8]
	unsigned int PhyDataWidth:2;		// [15:14]
	unsigned int NumCtlEps:4;		// [19:16]
	unsigned int IddgFltr:1;		// [20]
	unsigned int VBusValidFltr:1;		// [21]
	unsigned int AValidFltr:1;		// [22]
	unsigned int BValidFltr:1;		// [23]
	unsigned int SessEndFltr:1;		// [24]
	unsigned int DedFifoMode:1;		// [25]
	unsigned int INEps:4;		// [29:26]
	unsigned int DescDMAEnabled:1;		// [30]
	unsigned int DescDMA:1;		// [31]
};
 // GDFIFOCFG Register
struct USB2DC_GDFIFOCFG {
	unsigned int GDFIFOCfg:16;		// [15:0]
	unsigned int EPInfoBaseAddr:16;		// [31:16]
};
 // DIEPTXF1 Register
struct USB2DC_DIEPTXF1 {
	unsigned int INEPnTxFStAddr:11;		// [10:0]
	unsigned int Reserved2:5;		// [15:11]
	unsigned int INEPnTxFDep:9;		// [24:16]
	unsigned int Reserved:7;		// [31:25]
};
 // DIEPTXF2 Register
struct USB2DC_DIEPTXF2 {
	unsigned int INEPnTxFStAddr:11;		// [10:0]
	unsigned int Reserved2:5;		// [15:11]
	unsigned int INEPnTxFDep:9;		// [24:16]
	unsigned int Reserved:7;		// [31:25]
};
 // DIEPTXF3 Register
struct USB2DC_DIEPTXF3 {
	unsigned int INEPnTxFStAddr:11;		// [10:0]
	unsigned int Reserved2:5;		// [15:11]
	unsigned int INEPnTxFDep:9;		// [24:16]
	unsigned int Reserved:7;		// [31:25]
};
 // DCFG Register
struct USB2DC_DCFG {
	unsigned int DevSpd:2;		// [1:0]
	unsigned int NZStsOUTHShk:1;		// [2]
	unsigned int Ena32KHzSusp:1;		// [3]
	unsigned int DevAddr:7;		// [10:4]
	unsigned int PerFrInt:2;		// [12:11]
	unsigned int EnDevOutNak:1;		// [13]
	unsigned int Reserved:9;		// [22:14]
	unsigned int DescDMA:1;		// [23]
	unsigned int PerSchIntvl:2;		// [25:24]
	unsigned int ResValid:6;		// [31:26]
};
 // DCTL Register
struct USB2DC_DCTL {
	unsigned int RmtWkUpSig:1;		// [0]
	unsigned int SftDiscon:1;		// [1]
	unsigned int GNPINNakSts:1;		// [2]
	unsigned int GOUTNakSts:1;		// [3]
	unsigned int TstCtl:3;		// [6:4]
	unsigned int SGNPInNak:1;		// [7]
	unsigned int CGNPInNak:1;		// [8]
	unsigned int SGOUTNak:1;		// [9]
	unsigned int CGOUTNak:1;		// [10]
	unsigned int PWROnPrgDone:1;		// [11]
	unsigned int Reserved2:1;		// [12]
	unsigned int GMC:2;		// [14:13]
	unsigned int IgnrFrmNum:1;		// [15]
	unsigned int NakOnBble:1;		// [16]
	unsigned int EnContOnBNA:1;		// [17]
	unsigned int Reserved:14;		// [31:18]
};
 // DSTS Register
struct USB2DC_DSTS {
	unsigned int SuspSts:1;		// [0]
	unsigned int EnumSpd:2;		// [2:1]
	unsigned int ErrticErr:1;		// [3]
	unsigned int Reserved2:4;		// [7:4]
	unsigned int SOFFN:14;		// [21:8]
	unsigned int DevLnSts:2;		// [23:22]
	unsigned int Reserved:8;		// [31:24]
};
 // DIEPMSK Register
struct USB2DC_DIEPMSK {
	unsigned int XferComplMsk:1;		// [0]
	unsigned int EPDisbldMsk:1;		// [1]
	unsigned int AHBErrMsk:1;		// [2]
	unsigned int TimeOUTMsk:1;		// [3]
	unsigned int INTknTXFEmpMsk:1;		// [4]
	unsigned int INTknEPMisMsk:1;		// [5]
	unsigned int INEPNakEffMsk:1;		// [6]
	unsigned int Reserved3:1;		// [7]
	unsigned int TxfifoUndrnMsk:1;		// [8]
	unsigned int BNAInIntrMsk:1;		// [9]
	unsigned int Reserved2:3;		// [12:10]
	unsigned int NAKMsk:1;		// [13]
	unsigned int Reserved:18;		// [31:14]
};
 // DOEPMSK Register
struct USB2DC_DOEPMSK {
	unsigned int XferComplMsk:1;		// [0]
	unsigned int EPDisbldMsk:1;		// [1]
	unsigned int AHBErrMsk:1;		// [2]
	unsigned int SetUPMsk:1;		// [3]
	unsigned int OUTTknEPdisMsk:1;		// [4]
	unsigned int StsPhseRcvdMsk:1;		// [5]
	unsigned int Back2BackSETup:1;		// [6]
	unsigned int Reserved3:1;		// [7]
	unsigned int OutPktErrMsk:1;		// [8]
	unsigned int BnaOutIntrMsk:1;		// [9]
	unsigned int Reserved2:2;		// [11:10]
	unsigned int BbleErrMsk:1;		// [12]
	unsigned int NAKMsk:1;		// [13]
	unsigned int NYETMsk:1;		// [14]
	unsigned int Reserved:17;		// [31:15]
};
 // DAINT Register
struct USB2DC_DAINT {
	unsigned int InEpInt0:1;		// [0]
	unsigned int InEpInt1:1;		// [1]
	unsigned int InEpInt2:1;		// [2]
	unsigned int InEpInt3:1;		// [3]
	unsigned int Reserved2:12;		// [15:4]
	unsigned int OutEPInt0:1;		// [16]
	unsigned int OutEPInt1:1;		// [17]
	unsigned int OutEPInt2:1;		// [18]
	unsigned int OutEPInt3:1;		// [19]
	unsigned int Reserved:12;		// [31:20]
};
 // DAINTMSK Register
struct USB2DC_DAINTMSK {
	unsigned int InEpMsk0:1;		// [0]
	unsigned int InEpMsk1:1;		// [1]
	unsigned int InEpMsk2:1;		// [2]
	unsigned int InEpMsk3:1;		// [3]
	unsigned int Reserved2:12;		// [15:4]
	unsigned int OutEPMsk0:1;		// [16]
	unsigned int OutEPMsk1:1;		// [17]
	unsigned int OutEPMsk2:1;		// [18]
	unsigned int OutEPMsk3:1;		// [19]
	unsigned int Reserved:12;		// [31:20]
};
 // DVBUSDIS Register
struct USB2DC_DVBUSDIS {
	unsigned int DVBUSDis:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // DVBUSPULSE Register
struct USB2DC_DVBUSPULSE {
	unsigned int DVBUSPulse:12;		// [11:0]
	unsigned int Reserved:20;		// [31:12]
};
 // DTHRCTL Register
struct USB2DC_DTHRCTL {
	unsigned int NonISOThrEn:1;		// [0]
	unsigned int ISOThrEn:1;		// [1]
	unsigned int TxThrLen:9;		// [10:2]
	unsigned int AHBThrRatio:2;		// [12:11]
	unsigned int Reserved3:3;		// [15:13]
	unsigned int RxThrEn:1;		// [16]
	unsigned int RxThrLen:9;		// [25:17]
	unsigned int Reserved2:1;		// [26]
	unsigned int ArbPrkEn:1;		// [27]
	unsigned int Reserved:4;		// [31:28]
};
 // DIEPEMPMSK Register
struct USB2DC_DIEPEMPMSK {
	unsigned int InEpTxfEmpMsk:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // DEACHINT Register
struct USB2DC_DEACHINT {
	unsigned int EchInEpInt:16;		// [15:0]
	unsigned int EchOutEPInt:16;		// [31:16]
};
 // DEACHINTMSK Register
struct USB2DC_DEACHINTMSK {
	unsigned int EchInEpMsk:16;		// [15:0]
	unsigned int EchOutEpMsk:16;		// [31:16]
};
 // DIEPEACHMSK0 Register
struct USB2DC_DIEPEACHMSK0 {
	unsigned int XferComplMsk:1;		// [0]
	unsigned int EPDisbldMsk:1;		// [1]
	unsigned int AHBErrMsk:1;		// [2]
	unsigned int TimeOUTMsk:1;		// [3]
	unsigned int INTknTXFEmpMsk:1;		// [4]
	unsigned int INTknEPMisMsk:1;		// [5]
	unsigned int INEPNakEffMsk:1;		// [6]
	unsigned int Reserved3:1;		// [7]
	unsigned int TxfifoUndrnMsk:1;		// [8]
	unsigned int BNAInIntrMsk:1;		// [9]
	unsigned int Reserved2:3;		// [12:10]
	unsigned int NAKMsk:1;		// [13]
	unsigned int Reserved:18;		// [31:14]
};
 // DIEPEACHMSK1 Register
struct USB2DC_DIEPEACHMSK1 {
	unsigned int XferComplMsk:1;		// [0]
	unsigned int EPDisbldMsk:1;		// [1]
	unsigned int AHBErrMsk:1;		// [2]
	unsigned int TimeOUTMsk:1;		// [3]
	unsigned int INTknTXFEmpMsk:1;		// [4]
	unsigned int INTknEPMisMsk:1;		// [5]
	unsigned int INEPNakEffMsk:1;		// [6]
	unsigned int Reserved3:1;		// [7]
	unsigned int TxfifoUndrnMsk:1;		// [8]
	unsigned int BNAInIntrMsk:1;		// [9]
	unsigned int Reserved2:3;		// [12:10]
	unsigned int NAKMsk:1;		// [13]
	unsigned int Reserved:18;		// [31:14]
};
 // DIEPEACHMSK2 Register
struct USB2DC_DIEPEACHMSK2 {
	unsigned int XferComplMsk:1;		// [0]
	unsigned int EPDisbldMsk:1;		// [1]
	unsigned int AHBErrMsk:1;		// [2]
	unsigned int TimeOUTMsk:1;		// [3]
	unsigned int INTknTXFEmpMsk:1;		// [4]
	unsigned int INTknEPMisMsk:1;		// [5]
	unsigned int INEPNakEffMsk:1;		// [6]
	unsigned int Reserved3:1;		// [7]
	unsigned int TxfifoUndrnMsk:1;		// [8]
	unsigned int BNAInIntrMsk:1;		// [9]
	unsigned int Reserved2:3;		// [12:10]
	unsigned int NAKMsk:1;		// [13]
	unsigned int Reserved:18;		// [31:14]
};
 // DIEPEACHMSK3 Register
struct USB2DC_DIEPEACHMSK3 {
	unsigned int XferComplMsk:1;		// [0]
	unsigned int EPDisbldMsk:1;		// [1]
	unsigned int AHBErrMsk:1;		// [2]
	unsigned int TimeOUTMsk:1;		// [3]
	unsigned int INTknTXFEmpMsk:1;		// [4]
	unsigned int INTknEPMisMsk:1;		// [5]
	unsigned int INEPNakEffMsk:1;		// [6]
	unsigned int Reserved3:1;		// [7]
	unsigned int TxfifoUndrnMsk:1;		// [8]
	unsigned int BNAInIntrMsk:1;		// [9]
	unsigned int Reserved2:3;		// [12:10]
	unsigned int NAKMsk:1;		// [13]
	unsigned int Reserved:18;		// [31:14]
};
 // DOEPEACHMSK0 Register
struct USB2DC_DOEPEACHMSK0 {
	unsigned int XferComplMsk:1;		// [0]
	unsigned int EPDisbldMsk:1;		// [1]
	unsigned int AHBErrMsk:1;		// [2]
	unsigned int SetUPMsk:1;		// [3]
	unsigned int OUTTknEPdisMsk:1;		// [4]
	unsigned int Reserved4:1;		// [5]
	unsigned int Back2BackSETup:1;		// [6]
	unsigned int Reserved3:1;		// [7]
	unsigned int OutPktErrMsk:1;		// [8]
	unsigned int BnaOutIntrMsk:1;		// [9]
	unsigned int Reserved2:2;		// [11:10]
	unsigned int BbleErrMsk:1;		// [12]
	unsigned int NAKMsk:1;		// [13]
	unsigned int NYETMsk:1;		// [14]
	unsigned int Reserved:17;		// [31:15]
};
 // DOEPEACHMSK1 Register
struct USB2DC_DOEPEACHMSK1 {
	unsigned int XferComplMsk:1;		// [0]
	unsigned int EPDisbldMsk:1;		// [1]
	unsigned int AHBErrMsk:1;		// [2]
	unsigned int SetUPMsk:1;		// [3]
	unsigned int OUTTknEPdisMsk:1;		// [4]
	unsigned int Reserved4:1;		// [5]
	unsigned int Back2BackSETup:1;		// [6]
	unsigned int Reserved3:1;		// [7]
	unsigned int OutPktErrMsk:1;		// [8]
	unsigned int BnaOutIntrMsk:1;		// [9]
	unsigned int Reserved2:2;		// [11:10]
	unsigned int BbleErrMsk:1;		// [12]
	unsigned int NAKMsk:1;		// [13]
	unsigned int NYETMsk:1;		// [14]
	unsigned int Reserved:17;		// [31:15]
};
 // DOEPEACHMSK2 Register
struct USB2DC_DOEPEACHMSK2 {
	unsigned int XferComplMsk:1;		// [0]
	unsigned int EPDisbldMsk:1;		// [1]
	unsigned int AHBErrMsk:1;		// [2]
	unsigned int SetUPMsk:1;		// [3]
	unsigned int OUTTknEPdisMsk:1;		// [4]
	unsigned int Reserved4:1;		// [5]
	unsigned int Back2BackSETup:1;		// [6]
	unsigned int Reserved3:1;		// [7]
	unsigned int OutPktErrMsk:1;		// [8]
	unsigned int BnaOutIntrMsk:1;		// [9]
	unsigned int Reserved2:2;		// [11:10]
	unsigned int BbleErrMsk:1;		// [12]
	unsigned int NAKMsk:1;		// [13]
	unsigned int NYETMsk:1;		// [14]
	unsigned int Reserved:17;		// [31:15]
};
 // DOEPEACHMSK3 Register
struct USB2DC_DOEPEACHMSK3 {
	unsigned int XferComplMsk:1;		// [0]
	unsigned int EPDisbldMsk:1;		// [1]
	unsigned int AHBErrMsk:1;		// [2]
	unsigned int SetUPMsk:1;		// [3]
	unsigned int OUTTknEPdisMsk:1;		// [4]
	unsigned int Reserved4:1;		// [5]
	unsigned int Back2BackSETup:1;		// [6]
	unsigned int Reserved3:1;		// [7]
	unsigned int OutPktErrMsk:1;		// [8]
	unsigned int BnaOutIntrMsk:1;		// [9]
	unsigned int Reserved2:2;		// [11:10]
	unsigned int BbleErrMsk:1;		// [12]
	unsigned int NAKMsk:1;		// [13]
	unsigned int NYETMsk:1;		// [14]
	unsigned int Reserved:17;		// [31:15]
};
 // DIEPCTL0 Register
struct USB2DC_DIEPCTL0 {
	unsigned int MPS:2;		// [1:0]
	unsigned int Reserved4:13;		// [14:2]
	unsigned int USBActEP:1;		// [15]
	unsigned int Reserved3:1;		// [16]
	unsigned int NAKSts:1;		// [17]
	unsigned int EPType:2;		// [19:18]
	unsigned int Reserved2:1;		// [20]
	unsigned int Stall:1;		// [21]
	unsigned int TxFNum:4;		// [25:22]
	unsigned int CNAK:1;		// [26]
	unsigned int SNAK:1;		// [27]
	unsigned int Reserved:2;		// [29:28]
	unsigned int EPDis:1;		// [30]
	unsigned int EPEna:1;		// [31]
};
 // DIEPINT0 Register
struct USB2DC_DIEPINT0 {
	unsigned int XferCompl:1;		// [0]
	unsigned int EPDisbld:1;		// [1]
	unsigned int AHBErr:1;		// [2]
	unsigned int TimeOUT:1;		// [3]
	unsigned int INTknTXFEmp:1;		// [4]
	unsigned int INTknEPMis:1;		// [5]
	unsigned int INEPNakEff:1;		// [6]
	unsigned int TxFEmp:1;		// [7]
	unsigned int TxfifoUndrn:1;		// [8]
	unsigned int BNAIntr:1;		// [9]
	unsigned int Reserved2:1;		// [10]
	unsigned int PktDrpSts:1;		// [11]
	unsigned int BbleErr:1;		// [12]
	unsigned int NAKIntrpt:1;		// [13]
	unsigned int NYETIntrpt:1;		// [14]
	unsigned int Reserved:17;		// [31:15]
};
 // DIEPTSIZ0 Register
struct USB2DC_DIEPTSIZ0 {
	unsigned int XferSize:7;		// [6:0]
	unsigned int Reserved2:12;		// [18:7]
	unsigned int PktCnt:2;		// [20:19]
	unsigned int Reserved:11;		// [31:21]
};
 // DIEPDMA0 Register
struct USB2DC_DIEPDMA0 {
	unsigned int DMAAddr:32;		// [31:0]
};
 // DTXFSTS0 Register
struct USB2DC_DTXFSTS0 {
	unsigned int INEPTxFSpcAvail:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // DIEPDMAB0 Register
struct USB2DC_DIEPDMAB0 {
	unsigned int DMABufferAddr:32;		// [31:0]
};
 // DIEPCTL1 Register
struct USB2DC_DIEPCTL1 {
	unsigned int MPS:11;		// [10:0]
	unsigned int Reserved2:4;		// [14:11]
	unsigned int USBActEP:1;		// [15]
	unsigned int DPID:1;		// [16]
	unsigned int NAKSts:1;		// [17]
	unsigned int EPType:2;		// [19:18]
	unsigned int Reserved:1;		// [20]
	unsigned int Stall:1;		// [21]
	unsigned int TxFNum:4;		// [25:22]
	unsigned int CNAK:1;		// [26]
	unsigned int SNAK:1;		// [27]
	unsigned int SetD0PID:1;		// [28]
	unsigned int SetD1PID:1;		// [29]
	unsigned int EPDis:1;		// [30]
	unsigned int EPEna:1;		// [31]
};
 // DIEPINT1 Register
struct USB2DC_DIEPINT1 {
	unsigned int XferCompl:1;		// [0]
	unsigned int EPDisbld:1;		// [1]
	unsigned int AHBErr:1;		// [2]
	unsigned int TimeOUT:1;		// [3]
	unsigned int INTknTXFEmp:1;		// [4]
	unsigned int INTknEPMis:1;		// [5]
	unsigned int INEPNakEff:1;		// [6]
	unsigned int TxFEmp:1;		// [7]
	unsigned int TxfifoUndrn:1;		// [8]
	unsigned int BNAIntr:1;		// [9]
	unsigned int Reserved2:1;		// [10]
	unsigned int PktDrpSts:1;		// [11]
	unsigned int BbleErr:1;		// [12]
	unsigned int NAKIntrpt:1;		// [13]
	unsigned int NYETIntrpt:1;		// [14]
	unsigned int Reserved:17;		// [31:15]
};
 // DIEPTSIZ1 Register
struct USB2DC_DIEPTSIZ1 {
	unsigned int XferSize:19;		// [18:0]
	unsigned int PktCnt:10;		// [28:19]
	unsigned int MC:2;		// [30:29]
	unsigned int Reserved:1;		// [31]
};
 // DIEPDMA1 Register
struct USB2DC_DIEPDMA1 {
	unsigned int DMAAddr:32;		// [31:0]
};
 // DTXFSTS1 Register
struct USB2DC_DTXFSTS1 {
	unsigned int INEPTxFSpcAvail:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // DIEPDMAB1 Register
struct USB2DC_DIEPDMAB1 {
	unsigned int DMABufferAddr:32;		// [31:0]
};
 // DIEPCTL2 Register
struct USB2DC_DIEPCTL2 {
	unsigned int MPS:11;		// [10:0]
	unsigned int Reserved2:4;		// [14:11]
	unsigned int USBActEP:1;		// [15]
	unsigned int DPID:1;		// [16]
	unsigned int NAKSts:1;		// [17]
	unsigned int EPType:2;		// [19:18]
	unsigned int Reserved:1;		// [20]
	unsigned int Stall:1;		// [21]
	unsigned int TxFNum:4;		// [25:22]
	unsigned int CNAK:1;		// [26]
	unsigned int SNAK:1;		// [27]
	unsigned int SetD0PID:1;		// [28]
	unsigned int SetD1PID:1;		// [29]
	unsigned int EPDis:1;		// [30]
	unsigned int EPEna:1;		// [31]
};
 // DIEPINT2 Register
struct USB2DC_DIEPINT2 {
	unsigned int XferCompl:1;		// [0]
	unsigned int EPDisbld:1;		// [1]
	unsigned int AHBErr:1;		// [2]
	unsigned int TimeOUT:1;		// [3]
	unsigned int INTknTXFEmp:1;		// [4]
	unsigned int INTknEPMis:1;		// [5]
	unsigned int INEPNakEff:1;		// [6]
	unsigned int TxFEmp:1;		// [7]
	unsigned int TxfifoUndrn:1;		// [8]
	unsigned int BNAIntr:1;		// [9]
	unsigned int Reserved2:1;		// [10]
	unsigned int PktDrpSts:1;		// [11]
	unsigned int BbleErr:1;		// [12]
	unsigned int NAKIntrpt:1;		// [13]
	unsigned int NYETIntrpt:1;		// [14]
	unsigned int Reserved:17;		// [31:15]
};
 // DIEPTSIZ2 Register
struct USB2DC_DIEPTSIZ2 {
	unsigned int XferSize:19;		// [18:0]
	unsigned int PktCnt:10;		// [28:19]
	unsigned int MC:2;		// [30:29]
	unsigned int Reserved:1;		// [31]
};
 // DIEPDMA2 Register
struct USB2DC_DIEPDMA2 {
	unsigned int DMAAddr:32;		// [31:0]
};
 // DTXFSTS2 Register
struct USB2DC_DTXFSTS2 {
	unsigned int INEPTxFSpcAvail:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // DIEPDMAB2 Register
struct USB2DC_DIEPDMAB2 {
	unsigned int DMABufferAddr:32;		// [31:0]
};
 // DIEPCTL3 Register
struct USB2DC_DIEPCTL3 {
	unsigned int MPS:11;		// [10:0]
	unsigned int Reserved2:4;		// [14:11]
	unsigned int USBActEP:1;		// [15]
	unsigned int DPID:1;		// [16]
	unsigned int NAKSts:1;		// [17]
	unsigned int EPType:2;		// [19:18]
	unsigned int Reserved:1;		// [20]
	unsigned int Stall:1;		// [21]
	unsigned int TxFNum:4;		// [25:22]
	unsigned int CNAK:1;		// [26]
	unsigned int SNAK:1;		// [27]
	unsigned int SetD0PID:1;		// [28]
	unsigned int SetD1PID:1;		// [29]
	unsigned int EPDis:1;		// [30]
	unsigned int EPEna:1;		// [31]
};
 // DIEPINT3 Register
struct USB2DC_DIEPINT3 {
	unsigned int XferCompl:1;		// [0]
	unsigned int EPDisbld:1;		// [1]
	unsigned int AHBErr:1;		// [2]
	unsigned int TimeOUT:1;		// [3]
	unsigned int INTknTXFEmp:1;		// [4]
	unsigned int INTknEPMis:1;		// [5]
	unsigned int INEPNakEff:1;		// [6]
	unsigned int TxFEmp:1;		// [7]
	unsigned int TxfifoUndrn:1;		// [8]
	unsigned int BNAIntr:1;		// [9]
	unsigned int Reserved2:1;		// [10]
	unsigned int PktDrpSts:1;		// [11]
	unsigned int BbleErr:1;		// [12]
	unsigned int NAKIntrpt:1;		// [13]
	unsigned int NYETIntrpt:1;		// [14]
	unsigned int Reserved:17;		// [31:15]
};
 // DIEPTSIZ3 Register
struct USB2DC_DIEPTSIZ3 {
	unsigned int XferSize:19;		// [18:0]
	unsigned int PktCnt:10;		// [28:19]
	unsigned int MC:2;		// [30:29]
	unsigned int Reserved:1;		// [31]
};
 // DIEPDMA3 Register
struct USB2DC_DIEPDMA3 {
	unsigned int DMAAddr:32;		// [31:0]
};
 // DTXFSTS3 Register
struct USB2DC_DTXFSTS3 {
	unsigned int INEPTxFSpcAvail:16;		// [15:0]
	unsigned int Reserved:16;		// [31:16]
};
 // DIEPDMAB3 Register
struct USB2DC_DIEPDMAB3 {
	unsigned int DMABufferAddr:32;		// [31:0]
};
 // DOEPCTL0 Register
struct USB2DC_DOEPCTL0 {
	unsigned int MPS:2;		// [1:0]
	unsigned int Reserved4:13;		// [14:2]
	unsigned int USBActEP:1;		// [15]
	unsigned int Reserved3:1;		// [16]
	unsigned int NAKSts:1;		// [17]
	unsigned int EPType:2;		// [19:18]
	unsigned int Snp:1;		// [20]
	unsigned int Stall:1;		// [21]
	unsigned int Reserved2:4;		// [25:22]
	unsigned int CNAK:1;		// [26]
	unsigned int SNAK:1;		// [27]
	unsigned int Reserved:2;		// [29:28]
	unsigned int EPDis:1;		// [30]
	unsigned int EPEna:1;		// [31]
};
 // DOEPINT0 Register
struct USB2DC_DOEPINT0 {
	unsigned int XferCompl:1;		// [0]
	unsigned int EPDisbld:1;		// [1]
	unsigned int AHBErr:1;		// [2]
	unsigned int SetUp:1;		// [3]
	unsigned int OUTTknEPdis:1;		// [4]
	unsigned int StsPhseRcvd:1;		// [5]
	unsigned int Back2BackSETup:1;		// [6]
	unsigned int Reserved3:1;		// [7]
	unsigned int OutPktErr:1;		// [8]
	unsigned int BNAIntr:1;		// [9]
	unsigned int Reserved2:1;		// [10]
	unsigned int PktDrpSts:1;		// [11]
	unsigned int BbleErr:1;		// [12]
	unsigned int NAKIntrpt:1;		// [13]
	unsigned int NYETIntrpt:1;		// [14]
	unsigned int Reserved:17;		// [31:15]
};
 // DOEPTSIZ0 Register
struct USB2DC_DOEPTSIZ0 {
	unsigned int XferSize:7;		// [6:0]
	unsigned int Reserved3:12;		// [18:7]
	unsigned int PktCnt:1;		// [19]
	unsigned int Reserved2:9;		// [28:20]
	unsigned int SUPCnt:2;		// [30:29]
	unsigned int Reserved:1;		// [31]
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
	unsigned int MPS:11;		// [10:0]
	unsigned int Reserved2:4;		// [14:11]
	unsigned int USBActEP:1;		// [15]
	unsigned int DPID:1;		// [16]
	unsigned int NAKSts:1;		// [17]
	unsigned int EPType:2;		// [19:18]
	unsigned int Snp:1;		// [20]
	unsigned int Stall:1;		// [21]
	unsigned int Reserved:4;		// [25:22]
	unsigned int CNAK:1;		// [26]
	unsigned int SNAK:1;		// [27]
	unsigned int SetD0PID:1;		// [28]
	unsigned int SetD1PID:1;		// [29]
	unsigned int EPDis:1;		// [30]
	unsigned int EPEna:1;		// [31]
};
 // DOEPINT1 Register
struct USB2DC_DOEPINT1 {
	unsigned int XferCompl:1;		// [0]
	unsigned int EPDisbld:1;		// [1]
	unsigned int AHBErr:1;		// [2]
	unsigned int SetUp:1;		// [3]
	unsigned int OUTTknEPdis:1;		// [4]
	unsigned int StsPhseRcvd:1;		// [5]
	unsigned int Back2BackSETup:1;		// [6]
	unsigned int Reserved3:1;		// [7]
	unsigned int OutPktErr:1;		// [8]
	unsigned int BNAIntr:1;		// [9]
	unsigned int Reserved2:1;		// [10]
	unsigned int PktDrpSts:1;		// [11]
	unsigned int BbleErr:1;		// [12]
	unsigned int NAKIntrpt:1;		// [13]
	unsigned int NYETIntrpt:1;		// [14]
	unsigned int Reserved:17;		// [31:15]
};
 // DOEPTSIZ1 Register
struct USB2DC_DOEPTSIZ1 {
	unsigned int XferSize:19;		// [18:0]
	unsigned int PktCnt:10;		// [28:19]
	unsigned int RxDPID:2;		// [30:29]
	unsigned int Reserved:1;		// [31]
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
	unsigned int MPS:11;		// [10:0]
	unsigned int Reserved2:4;		// [14:11]
	unsigned int USBActEP:1;		// [15]
	unsigned int DPID:1;		// [16]
	unsigned int NAKSts:1;		// [17]
	unsigned int EPType:2;		// [19:18]
	unsigned int Snp:1;		// [20]
	unsigned int Stall:1;		// [21]
	unsigned int Reserved:4;		// [25:22]
	unsigned int CNAK:1;		// [26]
	unsigned int SNAK:1;		// [27]
	unsigned int SetD0PID:1;		// [28]
	unsigned int SetD1PID:1;		// [29]
	unsigned int EPDis:1;		// [30]
	unsigned int EPEna:1;		// [31]
};
 // DOEPINT2 Register
struct USB2DC_DOEPINT2 {
	unsigned int XferCompl:1;		// [0]
	unsigned int EPDisbld:1;		// [1]
	unsigned int AHBErr:1;		// [2]
	unsigned int SetUp:1;		// [3]
	unsigned int OUTTknEPdis:1;		// [4]
	unsigned int StsPhseRcvd:1;		// [5]
	unsigned int Back2BackSETup:1;		// [6]
	unsigned int Reserved3:1;		// [7]
	unsigned int OutPktErr:1;		// [8]
	unsigned int BNAIntr:1;		// [9]
	unsigned int Reserved2:1;		// [10]
	unsigned int PktDrpSts:1;		// [11]
	unsigned int BbleErr:1;		// [12]
	unsigned int NAKIntrpt:1;		// [13]
	unsigned int NYETIntrpt:1;		// [14]
	unsigned int Reserved:17;		// [31:15]
};
 // DOEPTSIZ2 Register
struct USB2DC_DOEPTSIZ2 {
	unsigned int XferSize:19;		// [18:0]
	unsigned int PktCnt:10;		// [28:19]
	unsigned int RxDPID:2;		// [30:29]
	unsigned int Reserved:1;		// [31]
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
	unsigned int MPS:11;		// [10:0]
	unsigned int Reserved2:4;		// [14:11]
	unsigned int USBActEP:1;		// [15]
	unsigned int DPID:1;		// [16]
	unsigned int NAKSts:1;		// [17]
	unsigned int EPType:2;		// [19:18]
	unsigned int Snp:1;		// [20]
	unsigned int Stall:1;		// [21]
	unsigned int Reserved:4;		// [25:22]
	unsigned int CNAK:1;		// [26]
	unsigned int SNAK:1;		// [27]
	unsigned int SetD0PID:1;		// [28]
	unsigned int SetD1PID:1;		// [29]
	unsigned int EPDis:1;		// [30]
	unsigned int EPEna:1;		// [31]
};
 // DOEPINT3 Register
struct USB2DC_DOEPINT3 {
	unsigned int XferCompl:1;		// [0]
	unsigned int EPDisbld:1;		// [1]
	unsigned int AHBErr:1;		// [2]
	unsigned int SetUp:1;		// [3]
	unsigned int OUTTknEPdis:1;		// [4]
	unsigned int StsPhseRcvd:1;		// [5]
	unsigned int Back2BackSETup:1;		// [6]
	unsigned int Reserved3:1;		// [7]
	unsigned int OutPktErr:1;		// [8]
	unsigned int BNAIntr:1;		// [9]
	unsigned int Reserved2:1;		// [10]
	unsigned int PktDrpSts:1;		// [11]
	unsigned int BbleErr:1;		// [12]
	unsigned int NAKIntrpt:1;		// [13]
	unsigned int NYETIntrpt:1;		// [14]
	unsigned int Reserved:17;		// [31:15]
};
 // DOEPTSIZ3 Register
struct USB2DC_DOEPTSIZ3 {
	unsigned int XferSize:19;		// [18:0]
	unsigned int PktCnt:10;		// [28:19]
	unsigned int RxDPID:2;		// [30:29]
	unsigned int Reserved:1;		// [31]
};
 // DOEPDMA3 Register
struct USB2DC_DOEPDMA3 {
	unsigned int DMAAddr:32;		// [31:0]
};
 // DOEPDMAB3 Register
struct USB2DC_DOEPDMAB3 {
	unsigned int DMABufferAddr:32;		// [31:0]
};
 // PCGCCTL Register
struct USB2DC_PCGCCTL {
	unsigned int StopPclk:1;		// [0]
	unsigned int GateHclk:1;		// [1]
	unsigned int PwrClmp:1;		// [2]
	unsigned int RstPdwnModule:1;		// [3]
	unsigned int Reserved2:2;		// [5:4]
	unsigned int PhySleep:1;		// [6]
	unsigned int L1Suspended:1;		// [7]
	unsigned int Reserved:24;		// [31:8]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _USB2DC_REG_STRUCT_L_H */
