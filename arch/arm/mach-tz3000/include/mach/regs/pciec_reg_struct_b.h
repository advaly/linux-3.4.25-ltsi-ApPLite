/*
 * arch/arm/mach-tz3000/include/mach/regs/pciec_reg_struct_b.h
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

#ifndef _PCIEC_REG_STRUCT_B_H
#define _PCIEC_REG_STRUCT_B_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // PCFG_VendorID_DeviceID Register
struct PCIEC_PCFG_VENDORID_DEVICEID {
	unsigned int DEVICE_ID:16;		// [31:16]
	unsigned int VENDOR_ID:16;		// [15:0]
};
 // PCFG_Command_Status_Register Register
struct PCIEC_PCFG_COMMAND_STATUS_REGISTER {
	unsigned int Reserved:1;		// [31]
	unsigned int SIG_SYS_ERR:1;		// [30]
	unsigned int Reserved2:9;		// [29:21]
	unsigned int CAP_LST:1;		// [20]
	unsigned int INT_ST:1;		// [19]
	unsigned int Reserved3:8;		// [18:11]
	unsigned int INT_DIS:1;		// [10]
	unsigned int Reserved4:1;		// [9]
	unsigned int SERR_EN:1;		// [8]
	unsigned int Reserved5:5;		// [7:3]
	unsigned int BUSMST_EN:1;		// [2]
	unsigned int MEMSPC_EN:1;		// [1]
	unsigned int IOSPC_EN:1;		// [0]
};
 // PCFG_RevisionID_ClassCode Register
struct PCIEC_PCFG_REVISIONID_CLASSCODE {
	unsigned int CLASS_CODE:24;		// [31:8]
	unsigned int REVID:8;		// [7:0]
};
 // PCFG_CacheLineSize_LatencyTimer_Header_Type_BIST Register
struct PCIEC_PCFG_CACHELINESIZE_LATENCYTIMER_HEADER_TYPE_BIST {
	unsigned int BIST:8;		// [31:24]
	unsigned int MULTFUNC_ST:1;		// [23]
	unsigned int HD_LYOUT_CODE:7;		// [22:16]
	unsigned int LATCY_TIMER:8;		// [15:8]
	unsigned int CACHE_LINE_SIZE:8;		// [7:0]
};
 // PCFG_BAR0 Register
struct PCIEC_PCFG_BAR0 {
	unsigned int BAR0:32;		// [31:0]
};
 // PCFG_BAR1 Register
struct PCIEC_PCFG_BAR1 {
	unsigned int BAR1:32;		// [31:0]
};
 // PCFG_PrimNum_SecNum_SubordNum_Sec_Latency_Timer Register
struct PCIEC_PCFG_PRIMNUM_SECNUM_SUBORDNUM_SEC_LATENCY_TIMER {
	unsigned int Reserved:8;		// [31:24]
	unsigned int SUB_BUS_NUM:8;		// [23:16]
	unsigned int SEC_BUS_NUM:8;		// [15:8]
	unsigned int PRIM_BUS_NUM:8;		// [7:0]
};
 // PCFG_IOBASE_IOLIMIT_SEC_STATUS Register
struct PCIEC_PCFG_IOBASE_IOLIMIT_SEC_STATUS {
	unsigned int SECST_DET_PAR_ERR:1;		// [31]
	unsigned int SECST_SIG_SYS_ERR:1;		// [30]
	unsigned int SECST_RCV_MAS_ABT:1;		// [29]
	unsigned int SECST_RCV_TAT_ABT:1;		// [28]
	unsigned int SECST_SIG_TAR_ABT:1;		// [27]
	unsigned int Reserved:2;		// [26:25]
	unsigned int SECST_MAS_DT_PAR_ERR:1;		// [24]
	unsigned int Reserved2:8;		// [23:16]
	unsigned int IO_LIMT:4;		// [15:12]
	unsigned int IO_LIMT_CPB:4;		// [11:8]
	unsigned int IO_BASE:4;		// [7:4]
	unsigned int BASE_CPB:4;		// [3:0]
};
 // PCFG_Mem_Base_Mem_Limit Register
struct PCIEC_PCFG_MEM_BASE_MEM_LIMIT {
	unsigned int MEM_LIMT:12;		// [31:20]
	unsigned int Reserved:4;		// [19:16]
	unsigned int MEM_BASE:12;		// [15:4]
	unsigned int Reserved2:4;		// [3:0]
};
 // PCFG_Prefethable_Mem_base_Prefetchable_Mem_Limit Register
struct PCIEC_PCFG_PREFETHABLE_MEM_BASE_PREFETCHABLE_MEM_LIMIT {
	unsigned int PRFMEM_LIMT:12;		// [31:20]
	unsigned int PRFMEM_LIMT_CPB:4;		// [19:16]
	unsigned int PRFMEM_BASE:12;		// [15:4]
	unsigned int PRFMEM_BASE_CPB:4;		// [3:0]
};
 // PCFG_Prefethable_Base_Upper_32Bits Register
struct PCIEC_PCFG_PREFETHABLE_BASE_UPPER_32BITS {
	unsigned int PRFBASE_UP32:32;		// [31:0]
};
 // PCFG_Prefethable_Limit_Upper_32Bits Register
struct PCIEC_PCFG_PREFETHABLE_LIMIT_UPPER_32BITS {
	unsigned int PRFLIMT_UP32:32;		// [31:0]
};
 // PCFG_IOBase_Upper_IOLimit_Upper Register
struct PCIEC_PCFG_IOBASE_UPPER_IOLIMIT_UPPER {
	unsigned int IOLIMT_UP16:16;		// [31:16]
	unsigned int IOBASE_UP16:16;		// [15:0]
};
 // PCFG_CapabilityPointer Register
struct PCIEC_PCFG_CAPABILITYPOINTER {
	unsigned int CPBLTY_PNTR:32;		// [31:0]
};
 // PCFG_ExpansionROMBaseAddress Register
struct PCIEC_PCFG_EXPANSIONROMBASEADDRESS {
	unsigned int EXPANSN_ROM_BAR:32;		// [31:0]
};
 // PCFG_InterruptLineValue_InterruptPinValue_Bridge_Control Register
struct PCIEC_PCFG_INTERRUPTLINEVALUE_INTERRUPTPINVALUE_BRIDGE_CONTROL {
	unsigned int Reserved:9;		// [31:23]
	unsigned int BRDGCNTRL_SEC_BUS_RST:1;		// [22]
	unsigned int Reserved2:4;		// [21:18]
	unsigned int BRDGCNTRL_SERR_EN:1;		// [17]
	unsigned int BRDGCNTRL_PAR_ERR_RESP_EN:1;		// [16]
	unsigned int INT_PIN_VALUE:8;		// [15:8]
	unsigned int INT_LINE_VALUE:8;		// [7:0]
};
 // PCFG_CapabilityID_NextCapabilityPointer_PCIExpressCapabilities Register
struct PCIEC_PCFG_CAPABILITYID_NEXTCAPABILITYPOINTER_PCIEXPRESSCAPABILITIES {
	unsigned int Reserved:2;		// [31:30]
	unsigned int INT_MSG_NUM:5;		// [29:25]
	unsigned int SLOT_IMPLEMENTED:1;		// [24]
	unsigned int DEVPRT_TYPE:4;		// [23:20]
	unsigned int CAP_VER:4;		// [19:16]
	unsigned int NXT_CAP_PNTR:8;		// [15:8]
	unsigned int CAP_ID:8;		// [7:0]
};
 // PCFG_Device_Capabilities Register
struct PCIEC_PCFG_DEVICE_CAPABILITIES {
	unsigned int Reserved:4;		// [31:28]
	unsigned int CAP_SLTPWLMT_SCL:2;		// [27:26]
	unsigned int CAP_SLTPWLMT_VAL:8;		// [25:18]
	unsigned int Reserved2:2;		// [17:16]
	unsigned int RLBS_ERR_RPT:1;		// [15]
	unsigned int Reserved3:3;		// [14:12]
	unsigned int L1ACCEPT_LTCY:3;		// [11:9]
	unsigned int L0SACCEPT_LTCY:3;		// [8:6]
	unsigned int EXT_TAGFLD_SUPT:1;		// [5]
	unsigned int PHT_FUNC_SUPT:2;		// [4:3]
	unsigned int MAX_PLSIZE:3;		// [2:0]
};
 // PCFG_Device_Control_Device_Status Register
struct PCIEC_PCFG_DEVICE_CONTROL_DEVICE_STATUS {
	unsigned int Reserved:10;		// [31:22]
	unsigned int TR_PND:1;		// [21]
	unsigned int AUXPW_DET:1;		// [20]
	unsigned int UNSPT_REQ_DET:1;		// [19]
	unsigned int FATLERR_DET:1;		// [18]
	unsigned int NONFATLERR_DET:1;		// [17]
	unsigned int CORERR_DET:1;		// [16]
	unsigned int Reserved2:1;		// [15]
	unsigned int MAXRD_REQ_SIZE:3;		// [14:12]
	unsigned int EN_NOSNP:1;		// [11]
	unsigned int AUXPW_PM_EN:1;		// [10]
	unsigned int PHT_FUNC_EN:1;		// [9]
	unsigned int EXT_TAGFLD_EN:1;		// [8]
	unsigned int MAX_PYLDSIZ:3;		// [7:5]
	unsigned int EN_RLXD_ORDDING:1;		// [4]
	unsigned int UNSPT_REQ_RPT_EN:1;		// [3]
	unsigned int FATLERR_RPT_EN:1;		// [2]
	unsigned int NONFATLERR_RPT_EN:1;		// [1]
	unsigned int CORERR_RPT_EN:1;		// [0]
};
 // PCFG_Link_Capabilities Register
struct PCIEC_PCFG_LINK_CAPABILITIES {
	unsigned int PORT_NUM:8;		// [31:24]
	unsigned int Reserved:1;		// [23]
	unsigned int ASPM_OPT_COMP:1;		// [22]
	unsigned int LNK_BNDWD_NOTF_CAP:1;		// [21]
	unsigned int DL_LNK_ACTV_RPT_CAP:1;		// [20]
	unsigned int SUPRSDWN_ERR_RPT:1;		// [19]
	unsigned int CLK_PWMNGMNT:1;		// [18]
	unsigned int L1_EXT_LTCY:3;		// [17:15]
	unsigned int L0S_EXT_LTCY:3;		// [14:12]
	unsigned int ASPM_SPT:2;		// [11:10]
	unsigned int MAX_LNK_WIDTH1:6;		// [9:4]
	unsigned int MAX_LNK_SPD:4;		// [3:0]
};
 // PCFG_Link_Control_Link_Status Register
struct PCIEC_PCFG_LINK_CONTROL_LINK_STATUS {
	unsigned int LINKAUTOWDTHSTS:1;		// [31]
	unsigned int LINKWDTHMNGSTS:1;		// [30]
	unsigned int DL_LNK_ACTV:1;		// [29]
	unsigned int SLOT_CLK_CFG:1;		// [28]
	unsigned int LNK_TRAINING:1;		// [27]
	unsigned int Reserved:1;		// [26]
	unsigned int NEG_LNK_WIDTH:6;		// [25:20]
	unsigned int LNK_SPD:4;		// [19:16]
	unsigned int Reserved2:4;		// [15:12]
	unsigned int LNK_ATNOMS_BNDWD_INT_EN:1;		// [11]
	unsigned int LNKBNDWDMN_INT_EN:1;		// [10]
	unsigned int HD_ATNOMS_WD_DIS:1;		// [9]
	unsigned int EN_CLK_PW:1;		// [8]
	unsigned int EXTND_SYNC:1;		// [7]
	unsigned int COM_CLK_RG_CP:1;		// [6]
	unsigned int RET_LNK:1;		// [5]
	unsigned int LNK_DIS:1;		// [4]
	unsigned int RDCPL_BOUND:1;		// [3]
	unsigned int Reserved3:1;		// [2]
	unsigned int ASPM_CNTRL:2;		// [1:0]
};
 // PCFG_Root_Control_Root_Capabilities Register
struct PCIEC_PCFG_ROOT_CONTROL_ROOT_CAPABILITIES {
	unsigned int Reserved:15;		// [31:17]
	unsigned int CRS_SFT_VISIBL:1;		// [16]
	unsigned int Reserved2:11;		// [15:5]
	unsigned int CRS_SFT_VISIBL_EN:1;		// [4]
	unsigned int PME_INT_EN:1;		// [3]
	unsigned int SYSERR_FATL_EN:1;		// [2]
	unsigned int SYSERR_NONFATL_EN:1;		// [1]
	unsigned int SYSERR_COR_EN:1;		// [0]
};
 // PCFG_Root_Status Register
struct PCIEC_PCFG_ROOT_STATUS {
	unsigned int Reserved:14;		// [31:18]
	unsigned int PME_PEND_RC:1;		// [17]
	unsigned int PME_ST_RC:1;		// [16]
	unsigned int PME_REQID_RC:16;		// [15:0]
};
 // PCFG_Device_Capabilities_2 Register
struct PCIEC_PCFG_DEVICE_CAPABILITIES_2 {
	unsigned int Reserved:8;		// [31:24]
	unsigned int MAXEETLPPFX_SPT:2;		// [23:22]
	unsigned int EETLPPRFX_SPT:1;		// [21]
	unsigned int EXTFMTFLD_SPT:1;		// [20]
	unsigned int OBFF_SPT:2;		// [19:18]
	unsigned int Reserved2:4;		// [17:14]
	unsigned int TPH_CMP_SPT:2;		// [13:12]
	unsigned int LTRMAC_SPT:1;		// [11]
	unsigned int NOROEN_PRPRPAS:1;		// [10]
	unsigned int CAS_128_CMP_SPT:1;		// [9]
	unsigned int ATOMOP_64_CMP_SPT:1;		// [8]
	unsigned int ATOMOP_32_CMP_SPT:1;		// [7]
	unsigned int ATMOPRUT_SPT:1;		// [6]
	unsigned int ARIFOR_SPT:1;		// [5]
	unsigned int CPLTO_DIS_SPT:1;		// [4]
	unsigned int CPLTO_RNG_SPT:4;		// [3:0]
};
 // PCFG_Device_Control_2_Device_Status_2 Register
struct PCIEC_PCFG_DEVICE_CONTROL_2_DEVICE_STATUS_2 {
	unsigned int Reserved:16;		// [31:16]
	unsigned int EETLPPRFX_BLK:1;		// [15]
	unsigned int OBFF_EN:2;		// [14:13]
	unsigned int Reserved2:2;		// [12:11]
	unsigned int LTR_MEC_EN:1;		// [10]
	unsigned int IDO_CPL_EN:1;		// [9]
	unsigned int IDO_REQ_EN:1;		// [8]
	unsigned int ATMOP_EGRS_BLK:1;		// [7]
	unsigned int ATMOPREQ_EN:1;		// [6]
	unsigned int ARIFOR_EN:1;		// [5]
	unsigned int CPLTO_DIS:1;		// [4]
	unsigned int CPLTO_VLE:4;		// [3:0]
};
 // PCFG_Link_Capabilities_2 Register
struct PCIEC_PCFG_LINK_CAPABILITIES_2 {
	unsigned int Reserved:23;		// [31:9]
	unsigned int CRSLNK_SPT:1;		// [8]
	unsigned int SPTLNKSPD_VECT:7;		// [7:1]
	unsigned int Reserved2:1;		// [0]
};
 // PCFG_Link_Control_2_Link_Status_2 Register
struct PCIEC_PCFG_LINK_CONTROL_2_LINK_STATUS_2 {
	unsigned int Reserved:10;		// [31:22]
	unsigned int LNK_EQ_REQ:1;		// [21]
	unsigned int EQ_PH3_SUCS:1;		// [20]
	unsigned int EQ_PH2_SUCS:1;		// [19]
	unsigned int EQ_PH1_SUCS:1;		// [18]
	unsigned int EQ_COMP:1;		// [17]
	unsigned int CUR_DEEMPSIS_LVL:1;		// [16]
	unsigned int CMP_PRDEEMPSIS:4;		// [15:12]
	unsigned int CMP_SOS:1;		// [11]
	unsigned int ENT_MOD_CMP:1;		// [10]
	unsigned int TR_MRGN:3;		// [9:7]
	unsigned int SEL_DEEMPSIS:1;		// [6]
	unsigned int HD_ATNOMS_SPD:1;		// [5]
	unsigned int ENTR_CMP:1;		// [4]
	unsigned int TGTLNKSPD:4;		// [3:0]
};
 // PCFG_Power_Management_Capabilities Register
struct PCIEC_PCFG_POWER_MANAGEMENT_CAPABILITIES {
	unsigned int PME_SPT:5;		// [31:27]
	unsigned int D2_SPT:1;		// [26]
	unsigned int D1_SPT:1;		// [25]
	unsigned int AUX_CUR2:1;		// [24]
	unsigned int AUX_CUR1:2;		// [23:22]
	unsigned int DEV_SPEC_INI:1;		// [21]
	unsigned int Reserved:1;		// [20]
	unsigned int PME_CLK:1;		// [19]
	unsigned int PME_VER:3;		// [18:16]
	unsigned int NXT_CAP_PNTR_PMCS:8;		// [15:8]
	unsigned int CAP_ID_PMCS:8;		// [7:0]
};
 // PCFG_Power_Management_Status_Control Register
struct PCIEC_PCFG_POWER_MANAGEMENT_STATUS_CONTROL {
	unsigned int PME_DATA:8;		// [31:24]
	unsigned int PME_BPCC_EN:1;		// [23]
	unsigned int PME_B2B3:1;		// [22]
	unsigned int Reserved:6;		// [21:16]
	unsigned int PME_ST:1;		// [15]
	unsigned int PME_DATSCL:2;		// [14:13]
	unsigned int PME_DATSEL:4;		// [12:9]
	unsigned int PME_EN:1;		// [8]
	unsigned int Reserved2:4;		// [7:4]
	unsigned int NO_SFTRST:1;		// [3]
	unsigned int Reserved3:1;		// [2]
	unsigned int POWER_ST:2;		// [1:0]
};
 // PCFG_PCIExpress_Extended_Capability_ID Register
struct PCIEC_PCFG_PCIEXPRESS_EXTENDED_CAPABILITY_ID {
	unsigned int PCIE_CAPOFSET_AER:12;		// [31:20]
	unsigned int PCIE_CAPVER_AER:4;		// [19:16]
	unsigned int PCIE_EXTCAPID_AER:16;		// [15:0]
};
 // PCFG_Uncorrectable_Error_Status Register
struct PCIEC_PCFG_UNCORRECTABLE_ERROR_STATUS {
	unsigned int Reserved:6;		// [31:26]
	unsigned int TLP_PRFX_BLK_ERR_ST:1;		// [25]
	unsigned int ATMOP_EGRS_BLK_ST:1;		// [24]
	unsigned int MCBLCK_TLP_ST:1;		// [23]
	unsigned int UNCRCT_INTNL_ERR_ST:1;		// [22]
	unsigned int ACS_VIOLT_ST:1;		// [21]
	unsigned int UNSPT_REQ_ST:1;		// [20]
	unsigned int ECRC_ERR_ST:1;		// [19]
	unsigned int MALFM_TLP_ST:1;		// [18]
	unsigned int RCV_OVFLW_ST:1;		// [17]
	unsigned int UNEXPCT_CPL_ST:1;		// [16]
	unsigned int CMPLT_ABRT_ST:1;		// [15]
	unsigned int CPL_TIMOUT_ST:1;		// [14]
	unsigned int FLWCNTRLPRTCL_ERR_ST:1;		// [13]
	unsigned int PISN_TLP_ST:1;		// [12]
	unsigned int Reserved2:6;		// [11:6]
	unsigned int SUPRSDWN_ERR_ST:1;		// [5]
	unsigned int DL_PRTCL_ERR_ST:1;		// [4]
	unsigned int Reserved3:4;		// [3:0]
};
 // PCFG_Uncorrectable_Error_Mask Register
struct PCIEC_PCFG_UNCORRECTABLE_ERROR_MASK {
	unsigned int Reserved:6;		// [31:26]
	unsigned int TLP_PRFX_BLK_ERR_MSK:1;		// [25]
	unsigned int ATMOP_EGRS_BLK_MSK:1;		// [24]
	unsigned int MCBLCK_TLP_MSK:1;		// [23]
	unsigned int UNCRCT_INTNL_ERR_MSK:1;		// [22]
	unsigned int ACS_VIOLT_MSK:1;		// [21]
	unsigned int UNSPT_REQ_MSK:1;		// [20]
	unsigned int ECRC_ERR_MSK:1;		// [19]
	unsigned int MALFM_TLP_MSK:1;		// [18]
	unsigned int RCV_OVFLW_MSK:1;		// [17]
	unsigned int UNEXPCT_CPL_MSK:1;		// [16]
	unsigned int CMPLT_ABRT_MSK:1;		// [15]
	unsigned int CPL_TIMOUT_MSK:1;		// [14]
	unsigned int FLWCNTRLPRTCL_ERR_MSK:1;		// [13]
	unsigned int PISN_TLP_MSK:1;		// [12]
	unsigned int Reserved2:6;		// [11:6]
	unsigned int SUPRSDWN_ERR_MSK:1;		// [5]
	unsigned int DL_PRTCL_ERR_MSK:1;		// [4]
	unsigned int Reserved3:4;		// [3:0]
};
 // PCFG_Uncorrectable_Error_Severity Register
struct PCIEC_PCFG_UNCORRECTABLE_ERROR_SEVERITY {
	unsigned int Reserved:6;		// [31:26]
	unsigned int TLP_PRFX_BLK_ERR_SVRTY:1;		// [25]
	unsigned int ATMOP_EGRS_BLK_SVRTY:1;		// [24]
	unsigned int MCBLCK_TLP_SVRTY:1;		// [23]
	unsigned int UNCRCT_INTNL_ERR_SVRTY:1;		// [22]
	unsigned int ACS_VIOLT_SVRTY:1;		// [21]
	unsigned int UNSPT_REQ_SVRTY:1;		// [20]
	unsigned int ECRC_ERR_SVRTY:1;		// [19]
	unsigned int MALFM_TLP_SVRTY:1;		// [18]
	unsigned int RCV_OVFLW_SVRTY:1;		// [17]
	unsigned int UNEXPCT_CPL_SVRTY:1;		// [16]
	unsigned int CMPLT_ABRT_SVRTY:1;		// [15]
	unsigned int CPL_TIMOUT_SVRTY:1;		// [14]
	unsigned int FLWCNTRLPRTCL_ERR_SVRTY:1;		// [13]
	unsigned int PISN_TLP_SVRTY:1;		// [12]
	unsigned int Reserved2:6;		// [11:6]
	unsigned int SUPRSDWN_ERR_SVRTY:1;		// [5]
	unsigned int DL_PRTCL_ERR_SVRTY:1;		// [4]
	unsigned int Reserved3:4;		// [3:0]
};
 // PCFG_Correctable_Error_Status Register
struct PCIEC_PCFG_CORRECTABLE_ERROR_STATUS {
	unsigned int Reserved:16;		// [31:16]
	unsigned int HDLOG_OVFLW_ST:1;		// [15]
	unsigned int CRCT_INTNL_ERR_ST:1;		// [14]
	unsigned int ADV_NONFATL_ERR_ST:1;		// [13]
	unsigned int RPLYTIM_TIMOUT_ST:1;		// [12]
	unsigned int Reserved2:3;		// [11:9]
	unsigned int RPLYNUM_RLOVR_ST:1;		// [8]
	unsigned int BADDLLP_ST:1;		// [7]
	unsigned int BADTLP_ST:1;		// [6]
	unsigned int Reserved3:5;		// [5:1]
	unsigned int RCV_ERR_ST:1;		// [0]
};
 // PCFG_Correctable_Error_Mask Register
struct PCIEC_PCFG_CORRECTABLE_ERROR_MASK {
	unsigned int Reserved:16;		// [31:16]
	unsigned int HDLOG_OVFLW_MSK:1;		// [15]
	unsigned int CRCT_INTNL_ERR_MSK:1;		// [14]
	unsigned int ADV_NONFATL_ERR_MSK:1;		// [13]
	unsigned int RPLYTIM_TIMOUT_MSK:1;		// [12]
	unsigned int Reserved2:3;		// [11:9]
	unsigned int RPLYNUM_RLOVR_MSK:1;		// [8]
	unsigned int BADDLLP_MSK:1;		// [7]
	unsigned int BADTLP_MSK:1;		// [6]
	unsigned int Reserved3:5;		// [5:1]
	unsigned int RCV_ERR_MSK:1;		// [0]
};
 // PCFG_Advanced_Error_Capabilities_and_Control Register
struct PCIEC_PCFG_ADVANCED_ERROR_CAPABILITIES_AND_CONTROL {
	unsigned int Reserved:20;		// [31:12]
	unsigned int TLP_PRFX_LOG_PRSNT:1;		// [11]
	unsigned int MLTHD_REC_EN:1;		// [10]
	unsigned int MLTHD_REC_CAP:1;		// [9]
	unsigned int ECRC_CHK_EN:1;		// [8]
	unsigned int ECRC_CHK_CAP:1;		// [7]
	unsigned int ECRC_GEN_EN:1;		// [6]
	unsigned int ECRC_GEN_CAP:1;		// [5]
	unsigned int FRST_ERR_POINTR:5;		// [4:0]
};
 // PCFG_HeaderLog_Register_1stDW Register
struct PCIEC_PCFG_HEADERLOG_REGISTER_1STDW {
	unsigned int HDLOG_REG1:32;		// [31:0]
};
 // PCFG_HeaderLog_Register_2ndDW Register
struct PCIEC_PCFG_HEADERLOG_REGISTER_2NDDW {
	unsigned int HDLOG_REG2:32;		// [31:0]
};
 // PCFG_HeaderLog_Register_3rdDW Register
struct PCIEC_PCFG_HEADERLOG_REGISTER_3RDDW {
	unsigned int HDLOG_REG3:32;		// [31:0]
};
 // PCFG_HeaderLog_Register_4thDW Register
struct PCIEC_PCFG_HEADERLOG_REGISTER_4THDW {
	unsigned int HDLOG_REG4:32;		// [31:0]
};
 // PCFG_Root_Error_Command Register
struct PCIEC_PCFG_ROOT_ERROR_COMMAND {
	unsigned int Reserved:29;		// [31:3]
	unsigned int FATLERR_RC_RPT_EN:1;		// [2]
	unsigned int NONFATLERR_RC_RPT_EN:1;		// [1]
	unsigned int CORERR_RC_RPT_EN:1;		// [0]
};
 // PCFG_Root_Error_Status Register
struct PCIEC_PCFG_ROOT_ERROR_STATUS {
	unsigned int ADVERR_INTMSG_NUM:5;		// [31:27]
	unsigned int Reserved:20;		// [26:7]
	unsigned int FATLERR_MSG_RCV:1;		// [6]
	unsigned int NONFATLERR_MSG_RCV:1;		// [5]
	unsigned int FST_UNCOR_FATL:1;		// [4]
	unsigned int MULT_FATLNONFATLERR_RCV:1;		// [3]
	unsigned int FATLNONFATLERR_RCV:1;		// [2]
	unsigned int MULT_CORERR_RCV:1;		// [1]
	unsigned int CORERR_RCV:1;		// [0]
};
 // PCFG_Error_Source_Identification_Correctable_Error_Source_Identification Register
struct PCIEC_PCFG_ERROR_SOURCE_IDENTIFICATION_CORRECTABLE_ERROR_SOURCE_IDENTIFICATION {
	unsigned int FATLNONFATLERR_SOURCE_ID:16;		// [31:16]
	unsigned int CORERR_SOURCE_ID:16;		// [15:0]
};
 // PCFG_First_TLP_Prefix_Log_Register Register
struct PCIEC_PCFG_FIRST_TLP_PREFIX_LOG_REGISTER {
	unsigned int TLPPRFX_LOG_REG1:32;		// [31:0]
};
 // PCFG_Second_TLP_Prefix_Log_Register Register
struct PCIEC_PCFG_SECOND_TLP_PREFIX_LOG_REGISTER {
	unsigned int TLPPRFX_LOG_REG2:32;		// [31:0]
};
 // PCFG_Third_TLP_Prefix_Log_Register Register
struct PCIEC_PCFG_THIRD_TLP_PREFIX_LOG_REGISTER {
	unsigned int TLPPRFX_LOG_REG3:32;		// [31:0]
};
 // PCFG_Fourth_TLP_Prefix_Log_Register Register
struct PCIEC_PCFG_FOURTH_TLP_PREFIX_LOG_REGISTER {
	unsigned int TLPPRFX_LOG_REG4:32;		// [31:0]
};
 // PCFG_VirtualChannel_Enhanced_Capability_Header Register
struct PCIEC_PCFG_VIRTUALCHANNEL_ENHANCED_CAPABILITY_HEADER {
	unsigned int PCIE_CAPOFSET_VC:12;		// [31:20]
	unsigned int PCIE_CAPVER_VC:4;		// [19:16]
	unsigned int PCIE_EXTCAPID_VC:16;		// [15:0]
};
 // PCFG_Port_VC_Capability_Register1 Register
struct PCIEC_PCFG_PORT_VC_CAPABILITY_REGISTER1 {
	unsigned int Reserved:20;		// [31:12]
	unsigned int PRT_ARB_TBL_ENT:2;		// [11:10]
	unsigned int REF_CLK:2;		// [9:8]
	unsigned int Reserved2:1;		// [7]
	unsigned int LOWPRORTY_EXT_VC:3;		// [6:4]
	unsigned int Reserved3:1;		// [3]
	unsigned int EXT_VC_CNT:3;		// [2:0]
};
 // PCFG_Port_VC_Capability_Register2 Register
struct PCIEC_PCFG_PORT_VC_CAPABILITY_REGISTER2 {
	unsigned int VC_ARB_TBL_OFSET:8;		// [31:24]
	unsigned int Reserved:16;		// [23:8]
	unsigned int VC_ARB_TBL_CAP:8;		// [7:0]
};
 // PCFG_Port_VC_Control_Port_VC_Status Register
struct PCIEC_PCFG_PORT_VC_CONTROL_PORT_VC_STATUS {
	unsigned int Reserved:15;		// [31:17]
	unsigned int VC_ARB_TBL_ST:1;		// [16]
	unsigned int Reserved2:12;		// [15:4]
	unsigned int VC_ARB_SEL:3;		// [3:1]
	unsigned int VC_ARB_TBL:1;		// [0]
};
 // PCFG_VC_Resource_Capability_0 Register
struct PCIEC_PCFG_VC_RESOURCE_CAPABILITY_0 {
	unsigned int PORT_ARB_TBL_OFSET_0:8;		// [31:24]
	unsigned int Reserved:1;		// [23]
	unsigned int MAX_TIM_SLT_0:7;		// [22:16]
	unsigned int RJCT_0:1;		// [15]
	unsigned int Reserved2:7;		// [14:8]
	unsigned int PORT_ARB_CAP_0:8;		// [7:0]
};
 // PCFG_VC_Resource_Control_0 Register
struct PCIEC_PCFG_VC_RESOURCE_CONTROL_0 {
	unsigned int VC_EN_0:1;		// [31]
	unsigned int Reserved:4;		// [30:27]
	unsigned int VCID_0:3;		// [26:24]
	unsigned int Reserved2:4;		// [23:20]
	unsigned int PORT_ARB_SEL_0:3;		// [19:17]
	unsigned int LDPRT_ARB_TBL_0:1;		// [16]
	unsigned int Reserved3:8;		// [15:8]
	unsigned int TCVCMAP17_0:7;		// [7:1]
	unsigned int TCVCMAP0_0:1;		// [0]
};
 // PCFG_VC_Resource_Status_0 Register
struct PCIEC_PCFG_VC_RESOURCE_STATUS_0 {
	unsigned int Reserved:14;		// [31:18]
	unsigned int VCNEG_PEND_0:1;		// [17]
	unsigned int PORT_ARB_TBL_ST_0:1;		// [16]
	unsigned int Reserved2:16;		// [15:0]
};
 // PBSC_VENDOR_ID_DEVICE_ID Register
struct PCIEC_PBSC_VENDOR_ID_DEVICE_ID {
	unsigned int BS_CFG_DEVICE_ID:16;		// [31:16]
	unsigned int BS_CFG_VENDOR_ID:16;		// [15:0]
};
 // PBSC_REVISION_ID Register
struct PCIEC_PBSC_REVISION_ID {
	unsigned int BS_CFG_CLASS_CODE:24;		// [31:8]
	unsigned int BS_CFG_REVID:8;		// [7:0]
};
 // PBSC_BAR_RANGE_SET Register
struct PCIEC_PBSC_BAR_RANGE_SET {
	unsigned int Reserved:9;		// [31:23]
	unsigned int BS_BAR_P1_RPLC_EN:1;		// [22]
	unsigned int BS_BAR_P1_OW:6;		// [21:16]
	unsigned int Reserved2:1;		// [15]
	unsigned int BS_BAR_P0_RPLC_EN:1;		// [14]
	unsigned int BS_BAR_P0_OW:6;		// [13:8]
	unsigned int BAR_PARTITION_EN:6;		// [7:2]
	unsigned int BAR_PARTITION_TYPE:2;		// [1:0]
};
 // PBSC_BAR_0_CFG Register
struct PCIEC_PBSC_BAR_0_CFG {
	unsigned int BS_BAR0:32;		// [31:0]
};
 // PBSC_BAR_1_CFG Register
struct PCIEC_PBSC_BAR_1_CFG {
	unsigned int BS_BAR1:32;		// [31:0]
};
 // PBSC_BAR_RANGE_SET2 Register
struct PCIEC_PBSC_BAR_RANGE_SET2 {
	unsigned int Reserved:24;		// [31:8]
	unsigned int BAR_PARTYPE_EXT:8;		// [7:0]
};
 // PBSC_EXROM_BAR_SET Register
struct PCIEC_PBSC_EXROM_BAR_SET {
	unsigned int BS_EXBAR_REPL:22;		// [31:10]
	unsigned int Reserved:2;		// [9:8]
	unsigned int BS_EXROM_OW:4;		// [7:4]
	unsigned int Reserved2:2;		// [3:2]
	unsigned int BS_EXROM_BAR_RPLC_EN:1;		// [1]
	unsigned int BS_EXROM_BAR_EN:1;		// [0]
};
 // PBSC_COMPATI_CAPA_POINT Register
struct PCIEC_PBSC_COMPATI_CAPA_POINT {
	unsigned int BS_CFG_CPBLTY_PNTR:32;		// [31:0]
};
 // PBSC_MAX_LATENCY Register
struct PCIEC_PBSC_MAX_LATENCY {
	unsigned int Reserved:16;		// [31:16]
	unsigned int BS_CFG_INT_PIN_VALUE:8;		// [15:8]
	unsigned int Reserved2:8;		// [7:0]
};
 // PBSC_PCIE_CAPA_NXT_POINT Register
struct PCIEC_PBSC_PCIE_CAPA_NXT_POINT {
	unsigned int Reserved:2;		// [31:30]
	unsigned int BS_CFG_INT_MSG_NUM:5;		// [29:25]
	unsigned int Reserved2:1;		// [24]
	unsigned int BS_CFG_DEVPRT_TYPE:4;		// [23:20]
	unsigned int Reserved3:4;		// [19:16]
	unsigned int BS_CFG_NXT_CAP_PNTR:8;		// [15:8]
	unsigned int Reserved4:8;		// [7:0]
};
 // PBSC_DEV_CAPA Register
struct PCIEC_PBSC_DEV_CAPA {
	unsigned int Reserved:20;		// [31:12]
	unsigned int BS_CFG_L1ACCEPT_LTCY:3;		// [11:9]
	unsigned int BS_CFG_L0SACCEPT_LTCY:3;		// [8:6]
	unsigned int Reserved2:3;		// [5:3]
	unsigned int BS_CFG_MAX_PLSIZE:3;		// [2:0]
};
 // PBSC_DEV_CONT Register
struct PCIEC_PBSC_DEV_CONT {
	unsigned int Reserved:17;		// [31:15]
	unsigned int BS_CFG_MAXRD_REQ_SIZE:3;		// [14:12]
	unsigned int Reserved2:12;		// [11:0]
};
 // PBSC_LINK_CAPA Register
struct PCIEC_PBSC_LINK_CAPA {
	unsigned int BS_CFG_PORT_NUM:8;		// [31:24]
	unsigned int Reserved:1;		// [23]
	unsigned int BS_CFG_ASPM_OPT_COMP:1;		// [22]
	unsigned int Reserved2:10;		// [21:12]
	unsigned int BS_CFG_ASPM_SPT:2;		// [11:10]
	unsigned int BS_CFG_MAX_LNK_WIDTH1:6;		// [9:4]
	unsigned int BS_CFG_MAX_LNK_SPD:4;		// [3:0]
};
 // PBSC_LINK_CONT Register
struct PCIEC_PBSC_LINK_CONT {
	unsigned int Reserved:3;		// [31:29]
	unsigned int BS_CFG_SLOT_CLK_CFG:1;		// [28]
	unsigned int Reserved2:24;		// [27:4]
	unsigned int BS_CFG_RDCPL_BOUND:1;		// [3]
	unsigned int Reserved3:3;		// [2:0]
};
 // PBSC_LINK_CAPA2 Register
struct PCIEC_PBSC_LINK_CAPA2 {
	unsigned int Reserved:8;		// [31:24]
	unsigned int BS_CFG_MAXEETLPPFX_SPT:2;		// [23:22]
	unsigned int BS_CFG_EETLPPRFX_SPT:1;		// [21]
	unsigned int Reserved2:1;		// [20]
	unsigned int BS_CFG_OBFF_SPT:2;		// [19:18]
	unsigned int Reserved3:7;		// [17:11]
	unsigned int BS_CFG_NOROEN_PRPRPAS:1;		// [10]
	unsigned int Reserved4:6;		// [9:4]
	unsigned int BS_CFG_CPLTO_RNG_SPT:4;		// [3:0]
};
 // PBSC_LINK_CONT2 Register
struct PCIEC_PBSC_LINK_CONT2 {
	unsigned int Reserved:25;		// [31:7]
	unsigned int BS_CFG_SEL_DEEMPSIS:1;		// [6]
	unsigned int Reserved2:6;		// [5:0]
};
 // PBSC_LNK_CAP2 Register
struct PCIEC_PBSC_LNK_CAP2 {
	unsigned int Reserved:24;		// [31:8]
	unsigned int BS_CFG_SPTLNKSPD_VECT:7;		// [7:1]
	unsigned int Reserved2:1;		// [0]
};
 // PBSC_PM_CAPA_NXT_POINT Register
struct PCIEC_PBSC_PM_CAPA_NXT_POINT {
	unsigned int BS_CFG_PME_SPT:5;		// [31:27]
	unsigned int BS_CFG_D2_SPT:1;		// [26]
	unsigned int BS_CFG_D1_SPT:1;		// [25]
	unsigned int BS_CFG_AUX_CUR2:1;		// [24]
	unsigned int BS_CFG_AUX_CUR1:2;		// [23:22]
	unsigned int Reserved:6;		// [21:16]
	unsigned int BS_CFG_NXT_CAP_PNTR_PMCS:8;		// [15:8]
	unsigned int Reserved2:8;		// [7:0]
};
 // PBSC_PM_ST_CNTRL Register
struct PCIEC_PBSC_PM_ST_CNTRL {
	unsigned int Reserved:28;		// [31:4]
	unsigned int BS_CFG_NO_SFTRST:1;		// [3]
	unsigned int Reserved2:3;		// [2:0]
};
 // PBSC_PCIE_EXTND_CAPID Register
struct PCIEC_PBSC_PCIE_EXTND_CAPID {
	unsigned int BS_CFG_PCIE_CAPOFSET_AER:12;		// [31:20]
	unsigned int Reserved:20;		// [19:0]
};
 // PBSC_AER_CAP_CNTRL Register
struct PCIEC_PBSC_AER_CAP_CNTRL {
	unsigned int Reserved:22;		// [31:10]
	unsigned int BS_CFG_MLTHD_REC_CAP:1;		// [9]
	unsigned int Reserved2:9;		// [8:0]
};
 // PBSC_Root_Error_Status Register
struct PCIEC_PBSC_ROOT_ERROR_STATUS {
	unsigned int BS_CFG_ADVERR_INTMSG_NUM:5;		// [31:27]
	unsigned int Reserved:27;		// [26:0]
};
 // PBSC_VC_Enhanced_Cap_Hdr Register
struct PCIEC_PBSC_VC_ENHANCED_CAP_HDR {
	unsigned int BS_CFG_PCIE_CAPOFSET_VC:12;		// [31:20]
	unsigned int Reserved:20;		// [19:0]
};
 // PBSC_PRT_VC_CAP_REG1 Register
struct PCIEC_PBSC_PRT_VC_CAP_REG1 {
	unsigned int Reserved:25;		// [31:7]
	unsigned int BS_CFG_LOWPRORTY_EXT_VC:3;		// [6:4]
	unsigned int Reserved2:4;		// [3:0]
};
 // PBSC_TPH_REQ_EXTND_CAPHD Register
struct PCIEC_PBSC_TPH_REQ_EXTND_CAPHD {
	unsigned int BS_CFG_PCIE_CAPOFSET_TPH:12;		// [31:20]
	unsigned int Reserved:20;		// [19:0]
};
 // PBSC_SEC_PCIE_EXTND_CAPHD Register
struct PCIEC_PBSC_SEC_PCIE_EXTND_CAPHD {
	unsigned int BS_CFG_PCIE_CAPOFSET_SECPCIE:12;		// [31:20]
	unsigned int Reserved:20;		// [19:0]
};
 // PBSC_Lane_Equalization_Control_0_1 Register
struct PCIEC_PBSC_LANE_EQUALIZATION_CONTROL_0_1 {
	unsigned int Reserved:1;		// [31]
	unsigned int BS_CFG_UPST_PORT_RX_PRESET_HINT_1:3;		// [30:28]
	unsigned int BS_CFG_UPST_PORT_TX_PRESET_1:4;		// [27:24]
	unsigned int Reserved2:1;		// [23]
	unsigned int BS_CFG_DWST_PORT_RX_PRESET_HINT_1:3;		// [22:20]
	unsigned int BS_CFG_DWST_PORT_TX_PRESET_1:4;		// [19:16]
	unsigned int Reserved3:1;		// [15]
	unsigned int BS_CFG_UPST_PORT_RX_PRESET_HINT_0:3;		// [14:12]
	unsigned int BS_CFG_UPST_PORT_TX_PRESET_0:4;		// [11:8]
	unsigned int Reserved4:1;		// [7]
	unsigned int BS_CFG_DWST_PORT_RX_PRESET_HINT_0:3;		// [6:4]
	unsigned int BS_CFG_DWST_PORT_TX_PRESET_0:4;		// [3:0]
};
 // PBSC_Lane_Equalization_Control_2_3 Register
struct PCIEC_PBSC_LANE_EQUALIZATION_CONTROL_2_3 {
	unsigned int Reserved:1;		// [31]
	unsigned int BS_CFG_UPST_PORT_RX_PRESET_HINT_3:3;		// [30:28]
	unsigned int BS_CFG_UPST_PORT_TX_PRESET_3:4;		// [27:24]
	unsigned int Reserved2:1;		// [23]
	unsigned int BS_CFG_DWST_PORT_RX_PRESET_HINT_3:3;		// [22:20]
	unsigned int BS_CFG_DWST_PORT_TX_PRESET_3:4;		// [19:16]
	unsigned int Reserved3:1;		// [15]
	unsigned int BS_CFG_UPST_PORT_RX_PRESET_HINT_2:3;		// [14:12]
	unsigned int BS_CFG_UPST_PORT_TX_PRESET_2:4;		// [11:8]
	unsigned int Reserved4:1;		// [7]
	unsigned int BS_CFG_DWST_PORT_RX_PRESET_HINT_2:3;		// [6:4]
	unsigned int BS_CFG_DWST_PORT_TX_PRESET_2:4;		// [3:0]
};
 // PBSC_FUNC_READY Register
struct PCIEC_PBSC_FUNC_READY {
	unsigned int Reserved:31;		// [31:1]
	unsigned int BS_FUNC_READY:1;		// [0]
};
 // PTLC_RC_VBAR_RANGE_SET Register
struct PCIEC_PTLC_RC_VBAR_RANGE_SET {
	unsigned int Reserved:1;		// [31]
	unsigned int VBAR_P2_RPLC_EN:1;		// [30]
	unsigned int VBAR_P2_OW:6;		// [29:24]
	unsigned int Reserved2:1;		// [23]
	unsigned int VBAR_P1_RPLC_EN:1;		// [22]
	unsigned int VBAR_P1_OW:6;		// [21:16]
	unsigned int Reserved3:1;		// [15]
	unsigned int VBAR_P0_RPLC_EN:1;		// [14]
	unsigned int VBAR_P0_OW:6;		// [13:8]
	unsigned int Reserved4:3;		// [7:5]
	unsigned int VBAR_PARTITION_EN:3;		// [4:2]
	unsigned int RC_NOVBARMATCH_THR:1;		// [1]
	unsigned int RC_BASE_LIM_EN:1;		// [0]
};
 // PTLC_RC_VBAR_0 Register
struct PCIEC_PTLC_RC_VBAR_0 {
	unsigned int RC_VBAR_0:32;		// [31:0]
};
 // PTLC_RC_VBAR_1 Register
struct PCIEC_PTLC_RC_VBAR_1 {
	unsigned int RC_VBAR_1:32;		// [31:0]
};
 // PTLC_RC_VBAR_2 Register
struct PCIEC_PTLC_RC_VBAR_2 {
	unsigned int RC_VBAR_2:32;		// [31:0]
};
 // PTLC_RC_VBAR_3 Register
struct PCIEC_PTLC_RC_VBAR_3 {
	unsigned int RC_VBAR_3:32;		// [31:0]
};
 // PTLC_RC_VBAR_4 Register
struct PCIEC_PTLC_RC_VBAR_4 {
	unsigned int RC_VBAR_4:32;		// [31:0]
};
 // PTLC_RC_VBAR_5 Register
struct PCIEC_PTLC_RC_VBAR_5 {
	unsigned int RC_VBAR_5:32;		// [31:0]
};
 // PTLC_RC_BS_VBAR_0 Register
struct PCIEC_PTLC_RC_BS_VBAR_0 {
	unsigned int RC_BS_VBAR_0:32;		// [31:0]
};
 // PTLC_RC_BS_VBAR_1 Register
struct PCIEC_PTLC_RC_BS_VBAR_1 {
	unsigned int RC_BS_VBAR_1:32;		// [31:0]
};
 // PTLC_RC_BS_VBAR_2 Register
struct PCIEC_PTLC_RC_BS_VBAR_2 {
	unsigned int RC_BS_VBAR_2:32;		// [31:0]
};
 // PTLC_RC_BS_VBAR_3 Register
struct PCIEC_PTLC_RC_BS_VBAR_3 {
	unsigned int RC_BS_VBAR_3:32;		// [31:0]
};
 // PTLC_RC_BS_VBAR_4 Register
struct PCIEC_PTLC_RC_BS_VBAR_4 {
	unsigned int RC_BS_VBAR_4:32;		// [31:0]
};
 // PTLC_RC_BS_VBAR_5 Register
struct PCIEC_PTLC_RC_BS_VBAR_5 {
	unsigned int RC_BS_VBAR_5:32;		// [31:0]
};
 // PTLC_RC_BS_SLOTMSG_EN Register
struct PCIEC_PTLC_RC_BS_SLOTMSG_EN {
	unsigned int Reserved:16;		// [31:16]
	unsigned int RC_BS_SLOTMSG_FUNC:8;		// [15:8]
	unsigned int Reserved2:7;		// [7:1]
	unsigned int RC_BS_SLOTMSG_EN:1;		// [0]
};
 // PTLC_RC_BS_SLOTMSG_DW Register
struct PCIEC_PTLC_RC_BS_SLOTMSG_DW {
	unsigned int RC_BS_SLOTMSG_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Issue Register
struct PCIEC_PTLC_FREEMSG_ISSUE {
	unsigned int Reserved:30;		// [31:2]
	unsigned int FR_MSG_PEND:1;		// [1]
	unsigned int FR_MSG_KICK:1;		// [0]
};
 // PTLC_FreeMsg_Header_0DW Register
struct PCIEC_PTLC_FREEMSG_HEADER_0DW {
	unsigned int FR_LENGTH_DW:8;		// [31:24]
	unsigned int Reserved:6;		// [23:18]
	unsigned int FR_LENGTH_UP:2;		// [17:16]
	unsigned int Reserved2:1;		// [15]
	unsigned int FR_MSG_TC:3;		// [14:12]
	unsigned int Reserved3:9;		// [11:3]
	unsigned int FR_MSG_TYPE:3;		// [2:0]
};
 // PTLC_FreeMsg_Header_1DW Register
struct PCIEC_PTLC_FREEMSG_HEADER_1DW {
	unsigned int FR_MSG_CODE:8;		// [31:24]
	unsigned int Reserved:8;		// [23:16]
	unsigned int FR_MSG_REQID_DW:8;		// [15:8]
	unsigned int Reserved2:8;		// [7:0]
};
 // PTLC_FreeMsg_Header_2DW Register
struct PCIEC_PTLC_FREEMSG_HEADER_2DW {
	unsigned int FR_MSG_H2DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Header_3DW Register
struct PCIEC_PTLC_FREEMSG_HEADER_3DW {
	unsigned int FR_MSG_H3DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_0DW Register
struct PCIEC_PTLC_FREEMSG_DATA_0DW {
	unsigned int FR_MSG_D00_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_1DW Register
struct PCIEC_PTLC_FREEMSG_DATA_1DW {
	unsigned int FR_MSG_D01_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_2DW Register
struct PCIEC_PTLC_FREEMSG_DATA_2DW {
	unsigned int FR_MSG_D02_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_3DW Register
struct PCIEC_PTLC_FREEMSG_DATA_3DW {
	unsigned int FR_MSG_D03_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_4DW Register
struct PCIEC_PTLC_FREEMSG_DATA_4DW {
	unsigned int FR_MSG_D04_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_5DW Register
struct PCIEC_PTLC_FREEMSG_DATA_5DW {
	unsigned int FR_MSG_D05_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_6DW Register
struct PCIEC_PTLC_FREEMSG_DATA_6DW {
	unsigned int FR_MSG_D06_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_7DW Register
struct PCIEC_PTLC_FREEMSG_DATA_7DW {
	unsigned int FR_MSG_D07_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_8DW Register
struct PCIEC_PTLC_FREEMSG_DATA_8DW {
	unsigned int FR_MSG_D08_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_9DW Register
struct PCIEC_PTLC_FREEMSG_DATA_9DW {
	unsigned int FR_MSG_D09_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_10DW Register
struct PCIEC_PTLC_FREEMSG_DATA_10DW {
	unsigned int FR_MSG_D0A_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_11DW Register
struct PCIEC_PTLC_FREEMSG_DATA_11DW {
	unsigned int FR_MSG_D0B_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_12DW Register
struct PCIEC_PTLC_FREEMSG_DATA_12DW {
	unsigned int FR_MSG_D0C_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_13DW Register
struct PCIEC_PTLC_FREEMSG_DATA_13DW {
	unsigned int FR_MSG_D0D_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_14DW Register
struct PCIEC_PTLC_FREEMSG_DATA_14DW {
	unsigned int FR_MSG_D0E_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_15DW Register
struct PCIEC_PTLC_FREEMSG_DATA_15DW {
	unsigned int FR_MSG_D0F_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_16DW Register
struct PCIEC_PTLC_FREEMSG_DATA_16DW {
	unsigned int FR_MSG_D10_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_17DW Register
struct PCIEC_PTLC_FREEMSG_DATA_17DW {
	unsigned int FR_MSG_D11_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_18DW Register
struct PCIEC_PTLC_FREEMSG_DATA_18DW {
	unsigned int FR_MSG_D12_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_19DW Register
struct PCIEC_PTLC_FREEMSG_DATA_19DW {
	unsigned int FR_MSG_D13_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_20DW Register
struct PCIEC_PTLC_FREEMSG_DATA_20DW {
	unsigned int FR_MSG_D14_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_21DW Register
struct PCIEC_PTLC_FREEMSG_DATA_21DW {
	unsigned int FR_MSG_D15_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_22DW Register
struct PCIEC_PTLC_FREEMSG_DATA_22DW {
	unsigned int FR_MSG_D16_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_23DW Register
struct PCIEC_PTLC_FREEMSG_DATA_23DW {
	unsigned int FR_MSG_D17_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_24DW Register
struct PCIEC_PTLC_FREEMSG_DATA_24DW {
	unsigned int FR_MSG_D18_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_25DW Register
struct PCIEC_PTLC_FREEMSG_DATA_25DW {
	unsigned int FR_MSG_D19_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_26DW Register
struct PCIEC_PTLC_FREEMSG_DATA_26DW {
	unsigned int FR_MSG_D1A_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_27DW Register
struct PCIEC_PTLC_FREEMSG_DATA_27DW {
	unsigned int FR_MSG_D1B_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_28DW Register
struct PCIEC_PTLC_FREEMSG_DATA_28DW {
	unsigned int FR_MSG_D1C_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_29DW Register
struct PCIEC_PTLC_FREEMSG_DATA_29DW {
	unsigned int FR_MSG_D1D_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_30DW Register
struct PCIEC_PTLC_FREEMSG_DATA_30DW {
	unsigned int FR_MSG_D1E_DW:32;		// [31:0]
};
 // PTLC_FreeMsg_Data_31DW Register
struct PCIEC_PTLC_FREEMSG_DATA_31DW {
	unsigned int FR_MSG_D1F_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Header_0DW Register
struct PCIEC_PTLC_RECEIVEDMSG_HEADER_0DW {
	unsigned int RCV_VMSG_H0_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Header_1DW Register
struct PCIEC_PTLC_RECEIVEDMSG_HEADER_1DW {
	unsigned int RCV_VMSG_H1_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Header_2DW Register
struct PCIEC_PTLC_RECEIVEDMSG_HEADER_2DW {
	unsigned int RCV_VMSG_H2_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Header_3DW Register
struct PCIEC_PTLC_RECEIVEDMSG_HEADER_3DW {
	unsigned int RCV_VMSG_H3_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_0DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_0DW {
	unsigned int RCV_VMSG_D00_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_1DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_1DW {
	unsigned int RCV_VMSG_D01_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_2DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_2DW {
	unsigned int RCV_VMSG_D02_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_3DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_3DW {
	unsigned int RCV_VMSG_D03_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_4DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_4DW {
	unsigned int RCV_VMSG_D04_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_5DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_5DW {
	unsigned int RCV_VMSG_D05_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_6DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_6DW {
	unsigned int RCV_VMSG_D06_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_7DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_7DW {
	unsigned int RCV_VMSG_D07_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_8DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_8DW {
	unsigned int RCV_VMSG_D08_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_9DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_9DW {
	unsigned int RCV_VMSG_D09_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_10DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_10DW {
	unsigned int RCV_VMSG_D0A_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_11DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_11DW {
	unsigned int RCV_VMSG_D0B_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_12DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_12DW {
	unsigned int RCV_VMSG_D0C_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_13DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_13DW {
	unsigned int RCV_VMSG_D0D_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_14DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_14DW {
	unsigned int RCV_VMSG_D0E_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_15DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_15DW {
	unsigned int RCV_VMSG_D0F_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_16DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_16DW {
	unsigned int RCV_VMSG_D10_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_17DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_17DW {
	unsigned int RCV_VMSG_D11_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_18DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_18DW {
	unsigned int RCV_VMSG_D12_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_19DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_19DW {
	unsigned int RCV_VMSG_D13_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_20DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_20DW {
	unsigned int RCV_VMSG_D14_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_21DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_21DW {
	unsigned int RCV_VMSG_D15_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_22DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_22DW {
	unsigned int RCV_VMSG_D16_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_23DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_23DW {
	unsigned int RCV_VMSG_D17_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_24DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_24DW {
	unsigned int RCV_VMSG_D18_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_25DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_25DW {
	unsigned int RCV_VMSG_D19_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_26DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_26DW {
	unsigned int RCV_VMSG_D1A_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_27DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_27DW {
	unsigned int RCV_VMSG_D1B_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_28DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_28DW {
	unsigned int RCV_VMSG_D1C_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_29DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_29DW {
	unsigned int RCV_VMSG_D1D_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_30DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_30DW {
	unsigned int RCV_VMSG_D1E_DW:32;		// [31:0]
};
 // PTLC_ReceivedMsg_Data_31DW Register
struct PCIEC_PTLC_RECEIVEDMSG_DATA_31DW {
	unsigned int RCV_VMSG_D1F_DW:32;		// [31:0]
};
 // PTLC_Received_LTR_OBFF_Msg_Header_0DW Register
struct PCIEC_PTLC_RECEIVED_LTR_OBFF_MSG_HEADER_0DW {
	unsigned int RCV_LMSG_H0_DW:32;		// [31:0]
};
 // PTLC_Received_LTR_OBFF_Msg_Header_1DW Register
struct PCIEC_PTLC_RECEIVED_LTR_OBFF_MSG_HEADER_1DW {
	unsigned int RCV_LMSG_H1_DW:32;		// [31:0]
};
 // PTLC_Received_LTR_OBFF_Msg_Header_2DW Register
struct PCIEC_PTLC_RECEIVED_LTR_OBFF_MSG_HEADER_2DW {
	unsigned int RCV_LMSG_H2_DW:32;		// [31:0]
};
 // PTLC_Received_LTR_OBFF_Msg_Header_3DW Register
struct PCIEC_PTLC_RECEIVED_LTR_OBFF_MSG_HEADER_3DW {
	unsigned int RCV_LMSG_H3_DW:32;		// [31:0]
};
 // PMACC_PCLK_SYNC_RST Register
struct PCIEC_PMACC_PCLK_SYNC_RST {
	unsigned int Reserved:31;		// [31:1]
	unsigned int PCLK_SYNC_RST:1;		// [0]
};
 // PMACC_RATE_CHG_CTRL Register
struct PCIEC_PMACC_RATE_CHG_CTRL {
	unsigned int Reserved:6;		// [31:26]
	unsigned int RG_PP_RATECHGSWCTRL:1;		// [25]
	unsigned int RG_PP_RATECHGSWCTRLENA:1;		// [24]
	unsigned int Reserved2:7;		// [23:17]
	unsigned int RG_PP_AUTORATECHGEN:1;		// [16]
	unsigned int Reserved3:7;		// [15:9]
	unsigned int RG_PP_UNRELIABLERATECHGEN:1;		// [8]
	unsigned int Reserved4:3;		// [7:5]
	unsigned int RG_PP_RATECHGENA:1;		// [4]
	unsigned int RG_PP_TRGLINKSPD:4;		// [3:0]
};
 // PMACC_RATE_CHG_STATUS Register
struct PCIEC_PMACC_RATE_CHG_STATUS {
	unsigned int Reserved:28;		// [31:4]
	unsigned int ML_PP_RATEINFO:4;		// [3:0]
};
 // PMACC_MAC_ERR_STATUS Register
struct PCIEC_PMACC_MAC_ERR_STATUS {
	unsigned int Reserved:26;		// [31:6]
	unsigned int ML_PP_ERR_FRAME:1;		// [5]
	unsigned int ML_PP_ERR_LLDERR:1;		// [4]
	unsigned int ML_PP_ERR_DISPARITY:1;		// [3]
	unsigned int ML_PP_ERR_EBUNDER:1;		// [2]
	unsigned int ML_PP_ERR_EBOVER:1;		// [1]
	unsigned int ML_PP_ERR_8B10B:1;		// [0]
};
 // PMACC_LTSSM_MON Register
struct PCIEC_PMACC_LTSSM_MON {
	unsigned int Reserved:4;		// [31:28]
	unsigned int ML_PP_LTSSMMST:4;		// [27:24]
	unsigned int ML_PP_LTSSMSST:8;		// [23:16]
	unsigned int Reserved2:6;		// [15:10]
	unsigned int ML_PP_TXL0SST:2;		// [9:8]
	unsigned int Reserved3:6;		// [7:2]
	unsigned int ML_PP_RXL0SST:2;		// [1:0]
};
 // IPC_PIPE_RESET_SH Register
struct PCIEC_IPC_PIPE_RESET_SH {
	unsigned int Reserved:31;		// [31:1]
	unsigned int PIPE_RESET_SH:1;		// [0]
};
 // IPC_IP_MODE Register
struct PCIEC_IPC_IP_MODE {
	unsigned int VIRTUAL_RC_BUS_NUM:8;		// [31:24]
	unsigned int Reserved:3;		// [23:21]
	unsigned int EXIST_FUNC_NUM:5;		// [20:16]
	unsigned int Reserved2:5;		// [15:11]
	unsigned int EXIST_VC_NUM:3;		// [10:8]
	unsigned int Reserved3:7;		// [7:1]
	unsigned int IP_MODE_RC:1;		// [0]
};
 // IPC_RC_INTXMSI_CONT Register
struct PCIEC_IPC_RC_INTXMSI_CONT {
	unsigned int Reserved:12;		// [31:20]
	unsigned int RC_LANE_ERR_ST_INT_MSK:1;		// [19]
	unsigned int RC_UR_DET_INT_MSK:1;		// [18]
	unsigned int RC_SEC_ST_INT_MSK:1;		// [17]
	unsigned int RC_ST_INT_MSK:1;		// [16]
	unsigned int Reserved2:4;		// [15:12]
	unsigned int RC_INTD_O_MSK:1;		// [11]
	unsigned int RC_INTC_O_MSK:1;		// [10]
	unsigned int RC_INTB_O_MSK:1;		// [9]
	unsigned int RC_INTA_O_MSK:1;		// [8]
	unsigned int Reserved3:7;		// [7:1]
	unsigned int RC_INTNL_INTXMSI_SNATCH_EN:1;		// [0]
};
 // IPC_PHY_CFGOUT Register
struct PCIEC_IPC_PHY_CFGOUT {
	unsigned int Reserved:30;		// [31:2]
	unsigned int STOPPCLKL1:1;		// [1]
	unsigned int PLLENABLE_N:1;		// [0]
};
 // IPC_RANGE00_UP_OFFSET Register
struct PCIEC_IPC_RANGE00_UP_OFFSET {
	unsigned int PCIE_00_OFFSET_ADR_UP:32;		// [31:0]
};
 // IPC_RANGE00_EN Register
struct PCIEC_IPC_RANGE00_EN {
	unsigned int PCIE_00_OFFSET_ADR_DW:20;		// [31:12]
	unsigned int PCIE_00_OFFSET_FUNCNUM:8;		// [11:4]
	unsigned int PCIE_00_OFFSET_PTYPE:1;		// [3]
	unsigned int PCIE_00_OFFSET_EN:3;		// [2:0]
};
 // IPC_RANGE00_UP_RPLC Register
struct PCIEC_IPC_RANGE00_UP_RPLC {
	unsigned int PCIE_00_OFFSET_REPLACE_UP:32;		// [31:0]
};
 // IPC_RANGE00_WIDTH Register
struct PCIEC_IPC_RANGE00_WIDTH {
	unsigned int PCIE_00_OFFSET_REPLACE_DW:20;		// [31:12]
	unsigned int Reserved:3;		// [11:9]
	unsigned int PCIE_00_OFFSET_TC:3;		// [8:6]
	unsigned int PCIE_00_OFFSET_OW:6;		// [5:0]
};
 // IPC_RANGE01_UP_OFFSET Register
struct PCIEC_IPC_RANGE01_UP_OFFSET {
	unsigned int PCIE_01_OFFSET_ADR_UP:32;		// [31:0]
};
 // IPC_RANGE01_EN Register
struct PCIEC_IPC_RANGE01_EN {
	unsigned int PCIE_01_OFFSET_ADR_DW:20;		// [31:12]
	unsigned int PCIE_01_OFFSET_FUNCNUM:8;		// [11:4]
	unsigned int PCIE_01_OFFSET_PTYPE:1;		// [3]
	unsigned int PCIE_01_OFFSET_EN:3;		// [2:0]
};
 // IPC_RANGE01_UP_RPLC Register
struct PCIEC_IPC_RANGE01_UP_RPLC {
	unsigned int PCIE_01_OFFSET_REPLACE_UP:32;		// [31:0]
};
 // IPC_RANGE01_WIDTH Register
struct PCIEC_IPC_RANGE01_WIDTH {
	unsigned int PCIE_01_OFFSET_REPLACE_DW:20;		// [31:12]
	unsigned int Reserved:3;		// [11:9]
	unsigned int PCIE_01_OFFSET_TC:3;		// [8:6]
	unsigned int PCIE_01_OFFSET_OW:6;		// [5:0]
};
 // IPC_RANGE02_UP_OFFSET Register
struct PCIEC_IPC_RANGE02_UP_OFFSET {
	unsigned int PCIE_02_OFFSET_ADR_UP:32;		// [31:0]
};
 // IPC_RANGE02_EN Register
struct PCIEC_IPC_RANGE02_EN {
	unsigned int PCIE_02_OFFSET_ADR_DW:20;		// [31:12]
	unsigned int PCIE_02_OFFSET_FUNCNUM:8;		// [11:4]
	unsigned int PCIE_02_OFFSET_PTYPE:1;		// [3]
	unsigned int PCIE_02_OFFSET_EN:3;		// [2:0]
};
 // IPC_RANGE02_UP_RPLC Register
struct PCIEC_IPC_RANGE02_UP_RPLC {
	unsigned int PCIE_02_OFFSET_REPLACE_UP:32;		// [31:0]
};
 // IPC_RANGE02_WIDTH Register
struct PCIEC_IPC_RANGE02_WIDTH {
	unsigned int PCIE_02_OFFSET_REPLACE_DW:20;		// [31:12]
	unsigned int Reserved:3;		// [11:9]
	unsigned int PCIE_02_OFFSET_TC:3;		// [8:6]
	unsigned int PCIE_02_OFFSET_OW:6;		// [5:0]
};
 // IPC_RANGE03_UP_OFFSET Register
struct PCIEC_IPC_RANGE03_UP_OFFSET {
	unsigned int PCIE_03_OFFSET_ADR_UP:32;		// [31:0]
};
 // IPC_RANGE03_EN Register
struct PCIEC_IPC_RANGE03_EN {
	unsigned int PCIE_03_OFFSET_ADR_DW:20;		// [31:12]
	unsigned int PCIE_03_OFFSET_FUNCNUM:8;		// [11:4]
	unsigned int PCIE_03_OFFSET_PTYPE:1;		// [3]
	unsigned int PCIE_03_OFFSET_EN:3;		// [2:0]
};
 // IPC_RANGE03_UP_RPLC Register
struct PCIEC_IPC_RANGE03_UP_RPLC {
	unsigned int PCIE_03_OFFSET_REPLACE_UP:32;		// [31:0]
};
 // IPC_RANGE03_WIDTH Register
struct PCIEC_IPC_RANGE03_WIDTH {
	unsigned int PCIE_03_OFFSET_REPLACE_DW:20;		// [31:12]
	unsigned int Reserved:3;		// [11:9]
	unsigned int PCIE_03_OFFSET_TC:3;		// [8:6]
	unsigned int PCIE_03_OFFSET_OW:6;		// [5:0]
};
 // TLC_PM_CTRL1 Register
struct PCIEC_TLC_PM_CTRL1 {
	unsigned int Reserved:15;		// [31:17]
	unsigned int STOP_PCLK_EN:1;		// [16]
	unsigned int Reserved2:4;		// [15:12]
	unsigned int L2_DONE_RPT_EN:1;		// [11]
	unsigned int L2_DIR_SWCTRL_EN:1;		// [10]
	unsigned int CLKREQ_DEA_SWCTRL_EN:1;		// [9]
	unsigned int STOP_PCLK_SWCTRL_EN:1;		// [8]
	unsigned int Reserved3:5;		// [7:3]
	unsigned int ASPML1_SWCTRL_EN:1;		// [2]
	unsigned int PCIPML2_SWCTRL_EN:1;		// [1]
	unsigned int PCIPML1_SWCTRL_EN:1;		// [0]
};
 // TLC_PM_CTRL2 Register
struct PCIEC_TLC_PM_CTRL2 {
	unsigned int Reserved:13;		// [31:19]
	unsigned int PM_PME_TRG:1;		// [18]
	unsigned int PME_TO_ACK_TRG:1;		// [17]
	unsigned int PME_TURN_OFF_TRG:1;		// [16]
	unsigned int PM_AS_NAK_TRG:1;		// [15]
	unsigned int PM_AS_REQUEST_L1_TRG:1;		// [14]
	unsigned int PM_REQUEST_ACK_TRG:1;		// [13]
	unsigned int PM_ENTER_L23_TRG:1;		// [12]
	unsigned int PM_ENTER_L1_TRG:1;		// [11]
	unsigned int Reserved2:9;		// [10:2]
	unsigned int DIRECT_RECOVERY_TRG:1;		// [1]
	unsigned int DIRECT_DETECT_TRG:1;		// [0]
};
 // MACC_NFTS_SREF_CTRL Register
struct PCIEC_MACC_NFTS_SREF_CTRL {
	unsigned int Reserved:8;		// [31:24]
	unsigned int Reserved2:8;		// [23:16]
	unsigned int RG_PA_SNFTSSELF_GEN2:8;		// [15:8]
	unsigned int RG_PA_SNFTSSELF_GEN1:8;		// [7:0]
};
 // MACC_NFTS_CREF_CTRL Register
struct PCIEC_MACC_NFTS_CREF_CTRL {
	unsigned int Reserved:8;		// [31:24]
	unsigned int Reserved2:8;		// [23:16]
	unsigned int RG_PA_CNFTSSELF_GEN2:8;		// [15:8]
	unsigned int RG_PA_CNFTSSELF_GEN1:8;		// [7:0]
};
 // MACC_L1EXITLTCY_CTRL Register
struct PCIEC_MACC_L1EXITLTCY_CTRL {
	unsigned int Reserved:5;		// [31:27]
	unsigned int Reserved2:3;		// [26:24]
	unsigned int Reserved3:1;		// [23]
	unsigned int RG_PA_CL1EXITLTCY_GEN2:3;		// [22:20]
	unsigned int Reserved4:1;		// [19]
	unsigned int RG_PA_CL1EXITLTCY_GEN1:3;		// [18:16]
	unsigned int Reserved5:5;		// [15:11]
	unsigned int Reserved6:3;		// [10:8]
	unsigned int Reserved7:1;		// [7]
	unsigned int RG_PA_SL1EXITLTCY_GEN2:3;		// [6:4]
	unsigned int Reserved8:1;		// [3]
	unsigned int RG_PA_SL1EXITLTCY_GEN1:3;		// [2:0]
};
 // MACC_TXCOMMON_TO_CTRL Register
struct PCIEC_MACC_TXCOMMON_TO_CTRL {
	unsigned int Reserved:14;		// [31:18]
	unsigned int RG_PA_TXCOMTIM:18;		// [17:0]
};
 // MACC_PHYPIPE_INFO Register
struct PCIEC_MACC_PHYPIPE_INFO {
	unsigned int Reserved:2;		// [31:30]
	unsigned int RG_PA_RXEIDLY:6;		// [29:24]
	unsigned int Reserved2:7;		// [23:17]
	unsigned int RG_PA_TXSWING:1;		// [16]
	unsigned int Reserved3:7;		// [15:9]
	unsigned int RG_PA_CLKREQ_SUPPORT:1;		// [8]
	unsigned int Reserved4:5;		// [7:3]
	unsigned int RG_PA_PDRATEMODE:1;		// [2]
	unsigned int RG_PA_PIPE30:1;		// [1]
	unsigned int RG_PA_GENERALPHY:1;		// [0]
};
 // STMA_PINT0_INT Register
struct PCIEC_STMA_PINT0_INT {
	unsigned int Reserved:21;		// [31:11]
	unsigned int LINK_STATE:2;		// [10:9]
	unsigned int LINK_STATE_CHG:1;		// [8]
	unsigned int Reserved2:6;		// [7:2]
	unsigned int PCLK_VALID_CHG:1;		// [1]
	unsigned int PCLK_VALID:1;		// [0]
};
 // STMA_PINT0_INT_MSK Register
struct PCIEC_STMA_PINT0_INT_MSK {
	unsigned int Reserved:23;		// [31:9]
	unsigned int LINK_STATE_CHG_MSK:1;		// [8]
	unsigned int Reserved2:6;		// [7:2]
	unsigned int PCLK_VALID_CHG_MSK:1;		// [1]
	unsigned int Reserved3:1;		// [0]
};
 // STMA_PORT_INT1 Register
struct PCIEC_STMA_PORT_INT1 {
	unsigned int Reserved:7;		// [31:25]
	unsigned int VC0_SAXI_ERR_DET_RES:1;		// [24]
	unsigned int Reserved2:7;		// [23:17]
	unsigned int VC0_MAXI_ERR_DET_RES:1;		// [16]
	unsigned int Reserved3:7;		// [15:9]
	unsigned int VC0_INTERNAL_ERR_DET_RES:1;		// [8]
	unsigned int Reserved4:3;		// [7:5]
	unsigned int POWER_INFORM_INT_RES:1;		// [4]
	unsigned int RC_INTERNAL_INT_RES:1;		// [3]
	unsigned int RECEIVE_MSG_INT_RES:1;		// [2]
	unsigned int MAC_INFORM_INT_RES:1;		// [1]
	unsigned int VC_VALID_INT_RES:1;		// [0]
};
 // STMA_PORT_INT1_MSK Register
struct PCIEC_STMA_PORT_INT1_MSK {
	unsigned int Reserved:7;		// [31:25]
	unsigned int VC0_SAXI_ERR_DET_MSK_RES:1;		// [24]
	unsigned int Reserved2:7;		// [23:17]
	unsigned int VC0_MAXI_ERR_DET_MSK_RES:1;		// [16]
	unsigned int Reserved3:7;		// [15:9]
	unsigned int VC0_INTERNAL_ERR_DET_MSK_RES:1;		// [8]
	unsigned int Reserved4:3;		// [7:5]
	unsigned int POWER_INFORM_INT_MSK_RES:1;		// [4]
	unsigned int RC_INTERNAL_INT_MSK_RES:1;		// [3]
	unsigned int RECEIVE_MSG_MSK_RES:1;		// [2]
	unsigned int MAC_INFORM_INT_MSK_RES:1;		// [1]
	unsigned int VC_VALID_MSK_RES:1;		// [0]
};
 // STMA_PORT_INT2 Register
struct PCIEC_STMA_PORT_INT2 {
	unsigned int Reserved:27;		// [31:5]
	unsigned int TR_PND_CHG_INT_RES:1;		// [4]
	unsigned int PMCSR_CHANGE_INT_RES:1;		// [3]
	unsigned int Reserved2:2;		// [2:1]
	unsigned int FLR_INT_RES:1;		// [0]
};
 // STMA_PORT_INT2_MSK Register
struct PCIEC_STMA_PORT_INT2_MSK {
	unsigned int Reserved:27;		// [31:5]
	unsigned int TR_PND_CHG_INT_MSK_RES:1;		// [4]
	unsigned int PMCSR_CHANGE_INT_MSK_RES:1;		// [3]
	unsigned int Reserved2:2;		// [2:1]
	unsigned int FLR_INT_MSK_RES:1;		// [0]
};
 // STMA_VC_VALID_INT Register
struct PCIEC_STMA_VC_VALID_INT {
	unsigned int Reserved:23;		// [31:9]
	unsigned int VC0_VALID:1;		// [8]
	unsigned int Reserved2:7;		// [7:1]
	unsigned int VC0_VALID_CHG:1;		// [0]
};
 // STMA_VC_VALID_INT_MSK Register
struct PCIEC_STMA_VC_VALID_INT_MSK {
	unsigned int Reserved:24;		// [31:8]
	unsigned int Reserved2:7;		// [7:1]
	unsigned int VC0_VALID_CHG_MSK:1;		// [0]
};
 // STMA_MAC_INFORM_INT Register
struct PCIEC_STMA_MAC_INFORM_INT {
	unsigned int Reserved:21;		// [31:11]
	unsigned int ML_PA_RATECHGRQ:1;		// [10]
	unsigned int ML_PA_EPAUTOWDTH:1;		// [9]
	unsigned int ML_PA_EPWDTHMNG:1;		// [8]
	unsigned int Reserved2:5;		// [7:3]
	unsigned int ML_PA_HOTRESET:1;		// [2]
	unsigned int ML_PA_DISABLED:1;		// [1]
	unsigned int ML_PA_LINKDOWN:1;		// [0]
};
 // STMA_MAC_INFORM_INT_MSK Register
struct PCIEC_STMA_MAC_INFORM_INT_MSK {
	unsigned int Reserved:21;		// [31:11]
	unsigned int ML_PA_RATECHGRQ_MSK:1;		// [10]
	unsigned int ML_PA_EPAUTOWDTH_MSK:1;		// [9]
	unsigned int ML_PA_EPWDTHMNG_MSK:1;		// [8]
	unsigned int Reserved2:5;		// [7:3]
	unsigned int HOTRESET_MSK:1;		// [2]
	unsigned int DISABLED_MSK:1;		// [1]
	unsigned int LINKDOWN_MSK:1;		// [0]
};
 // STMA_RECEIVE_MSG Register
struct PCIEC_STMA_RECEIVE_MSG {
	unsigned int Reserved:26;		// [31:6]
	unsigned int VDM_DET:1;		// [5]
	unsigned int OBFF_DET:1;		// [4]
	unsigned int LTR_DET:1;		// [3]
	unsigned int SLOT_POWER_DET:1;		// [2]
	unsigned int PM_MSG_DET:1;		// [1]
	unsigned int ERR_MSG_DET:1;		// [0]
};
 // STMA_RECEIVE_MSG_MSK Register
struct PCIEC_STMA_RECEIVE_MSG_MSK {
	unsigned int Reserved:26;		// [31:6]
	unsigned int VDM_DET_MSK:1;		// [5]
	unsigned int OBFF_DET_MSK:1;		// [4]
	unsigned int LTR_DET_MSK:1;		// [3]
	unsigned int SLOT_POWER_DET_MSK:1;		// [2]
	unsigned int PM_MSG_DET_MSK:1;		// [1]
	unsigned int ERR_MSG_DET_MSK:1;		// [0]
};
 // STMA_RC_INTERNAL_INT Register
struct PCIEC_STMA_RC_INTERNAL_INT {
	unsigned int Reserved:30;		// [31:2]
	unsigned int RC_INTNL_INTXMSI_DET:1;		// [1]
	unsigned int RC_SYS_ERR_DET:1;		// [0]
};
 // STMA_RC_INTERNAL_INT_MSK Register
struct PCIEC_STMA_RC_INTERNAL_INT_MSK {
	unsigned int Reserved:30;		// [31:2]
	unsigned int RC_INTNL_INTXMSI_DET_MSK:1;		// [1]
	unsigned int RC_SYS_ERR_DET_MSK:1;		// [0]
};
 // STMA_POWER_INFORM_INT Register
struct PCIEC_STMA_POWER_INFORM_INT {
	unsigned int Reserved:20;		// [31:12]
	unsigned int PM_L2_DONE_ST:1;		// [11]
	unsigned int PM_L2_DIR_REQ_ST:1;		// [10]
	unsigned int PM_CLKREQ_DEA_REQ_ST:1;		// [9]
	unsigned int PM_STOP_PCLK_REQ_ST:1;		// [8]
	unsigned int Reserved2:1;		// [7]
	unsigned int PM_AS_NAK_RCV_ST:1;		// [6]
	unsigned int PME_TO_ACK_TIMEOUT_ST:1;		// [5]
	unsigned int PME_TO_ACK_RCV_ST:1;		// [4]
	unsigned int PME_TURN_OFF_RCV_ST:1;		// [3]
	unsigned int PM_AS_REQ_L1_RCV_ST:1;		// [2]
	unsigned int PM_ENTER_L23_RCV_ST:1;		// [1]
	unsigned int PM_ENTER_L1_RCV_ST:1;		// [0]
};
 // STMA_POWER_INFORM_INT_MSK Register
struct PCIEC_STMA_POWER_INFORM_INT_MSK {
	unsigned int Reserved:20;		// [31:12]
	unsigned int PM_L2_DONE_MSK:1;		// [11]
	unsigned int PM_L2_DIR_REQ_MSK:1;		// [10]
	unsigned int PM_CLKREQ_DEA_REQ_MSK:1;		// [9]
	unsigned int PM_STOP_PCLK_REQ_MSK:1;		// [8]
	unsigned int Reserved2:1;		// [7]
	unsigned int PM_AS_NAK_RCV_MSK:1;		// [6]
	unsigned int PME_TO_ACK_TIMEOUT_MSK:1;		// [5]
	unsigned int PME_TO_ACK_RCV_MSK:1;		// [4]
	unsigned int PME_TURN_OFF_RCV_MSK:1;		// [3]
	unsigned int PM_AS_REQ_L1_RCV_ST_MSK:1;		// [2]
	unsigned int PM_ENTER_L23_RCV_MSK:1;		// [1]
	unsigned int PM_ENTER_L1_RCV_MSK:1;		// [0]
};
 // STMA_VC0_MAXI_ERR Register
struct PCIEC_STMA_VC0_MAXI_ERR {
	unsigned int Reserved:29;		// [31:3]
	unsigned int VC0_MAXI_UNKNOWN_WR:1;		// [2]
	unsigned int VC0_MAXI_UNKNOWN_RD:1;		// [1]
	unsigned int VC0_MAXI_ERR_DET:1;		// [0]
};
 // STMA_VC0_MAXI_ERR_MSK Register
struct PCIEC_STMA_VC0_MAXI_ERR_MSK {
	unsigned int Reserved:31;		// [31:1]
	unsigned int VC0_MAXI_ERR_DET_MSK:1;		// [0]
};
 // STMA_VC0_AXIW_ERR Register
struct PCIEC_STMA_VC0_AXIW_ERR {
	unsigned int Reserved:2;		// [31:30]
	unsigned int VC0_AXIW_ERR_DAT_PYLD_OVR:1;		// [29]
	unsigned int Reserved2:2;		// [28:27]
	unsigned int VC0_AXIW_ERR_DAT_LSTRB:1;		// [26]
	unsigned int VC0_AXIW_ERR_DAT_1STRB:1;		// [25]
	unsigned int VC0_AXIW_ERR_DAT_MSTRB:1;		// [24]
	unsigned int VC0_AXIW_ERR_DAT_EARLYLAST:1;		// [23]
	unsigned int VC0_AXIW_ERR_DAT_NOLAST:1;		// [22]
	unsigned int VC0_AXIW_ERR_ACC_MEMIO_SPCEN:1;		// [21]
	unsigned int VC0_AXIW_ERR_ACC_BASE_LIMIT:1;		// [20]
	unsigned int VC0_AXIW_ERR_ACC_EP_CFG:1;		// [19]
	unsigned int VC0_AXIW_ERR_ACC_CFG_NG3:1;		// [18]
	unsigned int VC0_AXIW_ERR_ACC_CFG_NG2:1;		// [17]
	unsigned int VC0_AXIW_ERR_ACC_CFG_NG1:1;		// [16]
	unsigned int Reserved3:1;		// [15]
	unsigned int VC0_AXIW_ERR_ACC_BUSMSTR:1;		// [14]
	unsigned int VC0_AXIW_ERR_ACC_FUNCRESET:1;		// [13]
	unsigned int VC0_AXIW_ERR_ACC_FUNCREADY:1;		// [12]
	unsigned int VC0_AXIW_ERR_ACC_SRAMSIZE:1;		// [11]
	unsigned int VC0_AXIW_ERR_ACC_OFFSET:1;		// [10]
	unsigned int VC0_AXIW_ERR_ACC_TCVC:1;		// [9]
	unsigned int VC0_AXIW_ERR_ACC_PCLK_READY:1;		// [8]
	unsigned int VC0_AXIW_ERR_ACC_VC_READY:1;		// [7]
	unsigned int VC0_AXIW_ERR_ACC_4KB:1;		// [6]
	unsigned int VC0_AXIW_ERR_ACC_PCIE:1;		// [5]
	unsigned int VC0_AXIW_ERR_ACC_LEN:1;		// [4]
	unsigned int VC0_AXIW_ERR_ACC_BURST:1;		// [3]
	unsigned int VC0_AXIW_ERR_ACC_SIZE:1;		// [2]
	unsigned int VC0_AXIW_ERR_ACC_TYPE:1;		// [1]
	unsigned int VC0_AXIW_ERR_DET:1;		// [0]
};
 // STMA_VC0_AXIW_ERR_MSK Register
struct PCIEC_STMA_VC0_AXIW_ERR_MSK {
	unsigned int Reserved:31;		// [31:1]
	unsigned int VC0_AXIW_ERR_DET_MSK:1;		// [0]
};
 // STMA_VC0_AXIR_ERR Register
struct PCIEC_STMA_VC0_AXIR_ERR {
	unsigned int Reserved:10;		// [31:22]
	unsigned int VC0_AXIR_ERR_ACC_MEMIO_SPCEN:1;		// [21]
	unsigned int VC0_AXIR_ERR_ACC_BASE_LIMIT:1;		// [20]
	unsigned int VC0_AXIR_ERR_ACC_EP_CFG:1;		// [19]
	unsigned int VC0_AXIR_ERR_ACC_CFG_NG3:1;		// [18]
	unsigned int VC0_AXIR_ERR_ACC_CFG_NG2:1;		// [17]
	unsigned int VC0_AXIR_ERR_ACC_CFG_NG1:1;		// [16]
	unsigned int Reserved2:1;		// [15]
	unsigned int VC0_AXIR_ERR_ACC_BUSMSTR:1;		// [14]
	unsigned int VC0_AXIR_ERR_ACC_FUNCRESET:1;		// [13]
	unsigned int VC0_AXIR_ERR_ACC_FUNCREADY:1;		// [12]
	unsigned int VC0_AXIR_ERR_ACC_SRAMSIZE:1;		// [11]
	unsigned int VC0_AXIR_ERR_ACC_OFFSET:1;		// [10]
	unsigned int VC0_AXIR_ERR_ACC_TCVC:1;		// [9]
	unsigned int VC0_AXIR_ERR_ACC_PCLK_READY:1;		// [8]
	unsigned int VC0_AXIR_ERR_ACC_VC_READY:1;		// [7]
	unsigned int VC0_AXIR_ERR_ACC_4KB:1;		// [6]
	unsigned int VC0_AXIR_ERR_ACC_PCIE:1;		// [5]
	unsigned int VC0_AXIR_ERR_ACC_LEN:1;		// [4]
	unsigned int VC0_AXIR_ERR_ACC_BURST:1;		// [3]
	unsigned int VC0_AXIR_ERR_ACC_SIZE:1;		// [2]
	unsigned int VC0_AXIR_ERR_ACC_TYPE:1;		// [1]
	unsigned int VC0_AXIR_ERR_DET:1;		// [0]
};
 // STMA_VC0_AXIR_ERR_MSK Register
struct PCIEC_STMA_VC0_AXIR_ERR_MSK {
	unsigned int Reserved:31;		// [31:1]
	unsigned int VC0_AXIR_ERR_DET_MSK:1;		// [0]
};
 // STMA_FLR Register
struct PCIEC_STMA_FLR {
	unsigned int Reserved:31;		// [31:1]
	unsigned int FLR_FUNC0_DET:1;		// [0]
};
 // STMA_FLR_MSK Register
struct PCIEC_STMA_FLR_MSK {
	unsigned int Reserved:31;		// [31:1]
	unsigned int FLR_FUNC0_DET_MSK:1;		// [0]
};
 // STMA_FUNCTION_READY Register
struct PCIEC_STMA_FUNCTION_READY {
	unsigned int Reserved:31;		// [31:1]
	unsigned int MONI_FUNC_READY:1;		// [0]
};
 // STMA_PMCSR_CHANGE Register
struct PCIEC_STMA_PMCSR_CHANGE {
	unsigned int Reserved:31;		// [31:1]
	unsigned int PMCSR_FUNC0_CHG_DET:1;		// [0]
};
 // STMA_PMCSR_CHANGE_MSK Register
struct PCIEC_STMA_PMCSR_CHANGE_MSK {
	unsigned int Reserved:31;		// [31:1]
	unsigned int PMCSR_FUNC0_CHG_DET_MSK:1;		// [0]
};
 // STMA_PMCSR_COPY_VAL Register
struct PCIEC_STMA_PMCSR_COPY_VAL {
	unsigned int Reserved:30;		// [31:2]
	unsigned int F00_PM_STATE:2;		// [1:0]
};
 // STMA_TRANSFER_PEND_BIT_COPY Register
struct PCIEC_STMA_TRANSFER_PEND_BIT_COPY {
	unsigned int Reserved:31;		// [31:1]
	unsigned int MRG_CFG_TR_PND:1;		// [0]
};
 // STMA_TR_PEND_CHG_DET Register
struct PCIEC_STMA_TR_PEND_CHG_DET {
	unsigned int Reserved:31;		// [31:1]
	unsigned int MRG_CFG_TR_PND_CHG_DET:1;		// [0]
};
 // STMA_TR_PEND_CHG_DET_MSK Register
struct PCIEC_STMA_TR_PEND_CHG_DET_MSK {
	unsigned int Reserved:31;		// [31:1]
	unsigned int MRG_CFG_TR_PND_CHG_DET_MSK:1;		// [0]
};
 // APCFG_ACC_KICK Register
struct PCIEC_APCFG_ACC_KICK {
	unsigned int Reserved:31;		// [31:1]
	unsigned int APCFG_TLP_KICK:1;		// [0]
};
 // APCFG_ACC_BUSY Register
struct PCIEC_APCFG_ACC_BUSY {
	unsigned int Reserved:30;		// [31:2]
	unsigned int APCFG_ACC_ERR:1;		// [1]
	unsigned int APCFG_ACC_BUSY:1;		// [0]
};
 // APCFG_ACC_RDATA Register
struct PCIEC_APCFG_ACC_RDATA {
	unsigned int APCFG_ACC_RDATA:32;		// [31:0]
};
 // APCFG_TLP_HED0 Register
struct PCIEC_APCFG_TLP_HED0 {
	unsigned int APCFG_TLP_FMT:3;		// [31:29]
	unsigned int APCFG_TLP_TYPE:5;		// [28:24]
	unsigned int Reserved:8;		// [23:16]
	unsigned int APCFG_TLP_TD:1;		// [15]
	unsigned int Reserved2:15;		// [14:0]
};
 // APCFG_TLP_HED1 Register
struct PCIEC_APCFG_TLP_HED1 {
	unsigned int APCFG_TLP_REQID:16;		// [31:16]
	unsigned int Reserved:12;		// [15:4]
	unsigned int APCFG_TLP_FDWBE:4;		// [3:0]
};
 // APCFG_TLP_HED2 Register
struct PCIEC_APCFG_TLP_HED2 {
	unsigned int APCFG_TLP_HED2_0:8;		// [31:24]
	unsigned int APCFG_TLP_HED2_1:8;		// [23:16]
	unsigned int APCFG_TLP_HED2_2:8;		// [15:8]
	unsigned int APCFG_TLP_HED2_3:8;		// [7:0]
};
 // APCFG_TLP_DAT Register
struct PCIEC_APCFG_TLP_DAT {
	unsigned int APCFG_TLP_DAT_0:8;		// [31:24]
	unsigned int APCFG_TLP_DAT_1:8;		// [23:16]
	unsigned int APCFG_TLP_DAT_2:8;		// [15:8]
	unsigned int APCFG_TLP_DAT_3:8;		// [7:0]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _PCIEC_REG_STRUCT_B_H */
