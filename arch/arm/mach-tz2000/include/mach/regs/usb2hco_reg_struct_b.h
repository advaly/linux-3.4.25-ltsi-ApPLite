/*
 * arch/arm/mach-tz2000/include/mach/regs/usb2hco_reg_struct_b.h
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

#ifndef _USB2HCO_REG_STRUCT_B_H
#define _USB2HCO_REG_STRUCT_B_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // HcRevision Register
struct USB2HCO_HCREVISION {
	unsigned int Reserved:23;		// [31:9]
	unsigned int Legacy:1;		// [8]
	unsigned int REV:8;		// [7:0]
};
 // HcControl Register
struct USB2HCO_HCCONTROL {
	unsigned int Reserved:21;		// [31:11]
	unsigned int RWE:1;		// [10]
	unsigned int RWC:1;		// [9]
	unsigned int IR:1;		// [8]
	unsigned int HCFS:2;		// [7:6]
	unsigned int BLE:1;		// [5]
	unsigned int CLE:1;		// [4]
	unsigned int IE:1;		// [3]
	unsigned int PLE:1;		// [2]
	unsigned int CBSR:2;		// [1:0]
};
 // HcCommandStatus Register
struct USB2HCO_HCCOMMANDSTATUS {
	unsigned int Reserved:14;		// [31:18]
	unsigned int SOC:2;		// [17:16]
	unsigned int Reserved2:13;		// [15:3]
	unsigned int BLF:1;		// [2]
	unsigned int CLF:1;		// [1]
	unsigned int HCR:1;		// [0]
};
 // HcInterruptStatus Register
struct USB2HCO_HCINTERRUPTSTATUS {
	unsigned int Reserved:1;		// [31]
	unsigned int OC:1;		// [30]
	unsigned int Reserved2:23;		// [29:7]
	unsigned int RHSC:1;		// [6]
	unsigned int FNO:1;		// [5]
	unsigned int UE:1;		// [4]
	unsigned int RD:1;		// [3]
	unsigned int SF:1;		// [2]
	unsigned int WDH:1;		// [1]
	unsigned int SO:1;		// [0]
};
 // HcInterruptEnable Register
struct USB2HCO_HCINTERRUPTENABLE {
	unsigned int MIE:1;		// [31]
	unsigned int OC:1;		// [30]
	unsigned int Reserved:23;		// [29:7]
	unsigned int RHSC:1;		// [6]
	unsigned int FNO:1;		// [5]
	unsigned int UE:1;		// [4]
	unsigned int RD:1;		// [3]
	unsigned int SF:1;		// [2]
	unsigned int WDH:1;		// [1]
	unsigned int SO:1;		// [0]
};
 // HcInterruptDisable Register
struct USB2HCO_HCINTERRUPTDISABLE {
	unsigned int MIE:1;		// [31]
	unsigned int OC:1;		// [30]
	unsigned int Reserved:23;		// [29:7]
	unsigned int RHSC:1;		// [6]
	unsigned int FNO:1;		// [5]
	unsigned int UE:1;		// [4]
	unsigned int RD:1;		// [3]
	unsigned int SF:1;		// [2]
	unsigned int WDH:1;		// [1]
	unsigned int SO:1;		// [0]
};
 // HcHCCA Register
struct USB2HCO_HCHCCA {
	unsigned int HCCA:24;		// [31:8]
	unsigned int Reserved:8;		// [7:0]
};
 // HcPeriodCurrentED Register
struct USB2HCO_HCPERIODCURRENTED {
	unsigned int PCED:28;		// [31:4]
	unsigned int Reserved:4;		// [3:0]
};
 // HcControlHeadED Register
struct USB2HCO_HCCONTROLHEADED {
	unsigned int CHED:28;		// [31:4]
	unsigned int Reserved:4;		// [3:0]
};
 // HcControlCurrentED Register
struct USB2HCO_HCCONTROLCURRENTED {
	unsigned int CCED:28;		// [31:4]
	unsigned int Reserved:4;		// [3:0]
};
 // HcBulkHeadED Register
struct USB2HCO_HCBULKHEADED {
	unsigned int BHED:28;		// [31:4]
	unsigned int Reserved:4;		// [3:0]
};
 // HcBulkCurrentED Register
struct USB2HCO_HCBULKCURRENTED {
	unsigned int BCED:28;		// [31:4]
	unsigned int Reserved:4;		// [3:0]
};
 // HcDoneHead Register
struct USB2HCO_HCDONEHEAD {
	unsigned int DH:28;		// [31:4]
	unsigned int Reserved:4;		// [3:0]
};
 // HcFmInterval Register
struct USB2HCO_HCFMINTERVAL {
	unsigned int FIT:1;		// [31]
	unsigned int FSMPS:15;		// [30:16]
	unsigned int Reserved:2;		// [15:14]
	unsigned int FI:14;		// [13:0]
};
 // HcFmRemaining Register
struct USB2HCO_HCFMREMAINING {
	unsigned int FRT:1;		// [31]
	unsigned int Reserved:17;		// [30:14]
	unsigned int FR:14;		// [13:0]
};
 // HcFmNumber Register
struct USB2HCO_HCFMNUMBER {
	unsigned int Reserved:16;		// [31:16]
	unsigned int FN:16;		// [15:0]
};
 // HcPeriodicStart Register
struct USB2HCO_HCPERIODICSTART {
	unsigned int Reserved:18;		// [31:14]
	unsigned int PS:14;		// [13:0]
};
 // HcLSThreshold Register
struct USB2HCO_HCLSTHRESHOLD {
	unsigned int Reserved:20;		// [31:12]
	unsigned int LST:12;		// [11:0]
};
 // HcRhDescriptorA Register
struct USB2HCO_HCRHDESCRIPTORA {
	unsigned int POTPGT:8;		// [31:24]
	unsigned int Reserved:11;		// [23:13]
	unsigned int NOCP:1;		// [12]
	unsigned int OCPM:1;		// [11]
	unsigned int Reserved2:1;		// [10]
	unsigned int NPS:1;		// [9]
	unsigned int PSM:1;		// [8]
	unsigned int NDP:8;		// [7:0]
};
 // HcRhDescriptorB Register
struct USB2HCO_HCRHDESCRIPTORB {
	unsigned int Reserved:14;		// [31:18]
	unsigned int PPCM:1;		// [17]
	unsigned int Reserved2:15;		// [16:2]
	unsigned int DR:1;		// [1]
	unsigned int Reserved3:1;		// [0]
};
 // HcRhStatus Register
struct USB2HCO_HCRHSTATUS {
	unsigned int Reserved:14;		// [31:18]
	unsigned int OCIC:1;		// [17]
	unsigned int Reserved2:1;		// [16]
	unsigned int DRWE:1;		// [15]
	unsigned int Reserved3:13;		// [14:2]
	unsigned int OCI:1;		// [1]
	unsigned int Reserved4:1;		// [0]
};
 // HcRhPortStatus_0 Register
struct USB2HCO_HCRHPORTSTATUS_0 {
	unsigned int Reserved:11;		// [31:21]
	unsigned int PRSC:1;		// [20]
	unsigned int OCIC:1;		// [19]
	unsigned int PSSC:1;		// [18]
	unsigned int PESC:1;		// [17]
	unsigned int CSC:1;		// [16]
	unsigned int Reserved2:6;		// [15:10]
	unsigned int LSDA:1;		// [9]
	unsigned int PPS:1;		// [8]
	unsigned int Reserved3:3;		// [7:5]
	unsigned int PRS:1;		// [4]
	unsigned int POCI:1;		// [3]
	unsigned int PSS:1;		// [2]
	unsigned int PES:1;		// [1]
	unsigned int CCS:1;		// [0]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _USB2HCO_REG_STRUCT_B_H */
