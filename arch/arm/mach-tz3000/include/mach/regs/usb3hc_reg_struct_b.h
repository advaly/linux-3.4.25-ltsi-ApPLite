/*
 * arch/arm/mach-tz3000/include/mach/regs/usb3hc_reg_struct_b.h
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

#ifndef _USB3HC_REG_STRUCT_B_H
#define _USB3HC_REG_STRUCT_B_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // CAPLENGTH Register
struct USB3HC_CAPLENGTH {
	unsigned int HCIVERSION:16;		// [31:16]
	unsigned int RSVD0:8;		// [15:8]
	unsigned int CAPLENGTH:8;		// [7:0]
};
 // HCSPARAMS1 Register
struct USB3HC_HCSPARAMS1 {
	unsigned int MAXPORTS:8;		// [31:24]
	unsigned int RSVD1:5;		// [23:19]
	unsigned int MAXINTRS:11;		// [18:8]
	unsigned int MAXSLOTS:8;		// [7:0]
};
 // HCSPARAMS2 Register
struct USB3HC_HCSPARAMS2 {
	unsigned int MAXSCRATCHPADBUFS:5;		// [31:27]
	unsigned int SPR:1;		// [26]
	unsigned int MAXSCRATCHPADBUFS_HI:5;		// [25:21]
	unsigned int RSVD2:13;		// [20:8]
	unsigned int ERSTMAX:4;		// [7:4]
	unsigned int IST:4;		// [3:0]
};
 // HCSPARAMS3 Register
struct USB3HC_HCSPARAMS3 {
	unsigned int U2_DEVICE_EXIT_LAT:16;		// [31:16]
	unsigned int RSVD3:8;		// [15:8]
	unsigned int U1_DEVICE_EXIT_LAT:8;		// [7:0]
};
 // HCCPARAMS Register
struct USB3HC_HCCPARAMS {
	unsigned int XECP:16;		// [31:16]
	unsigned int MAXPSASIZE:4;		// [15:12]
	unsigned int RSVD3:3;		// [11:9]
	unsigned int PAE:1;		// [8]
	unsigned int NSS:1;		// [7]
	unsigned int LTC:1;		// [6]
	unsigned int LHRC:1;		// [5]
	unsigned int PIND:1;		// [4]
	unsigned int PPC:1;		// [3]
	unsigned int CSZ:1;		// [2]
	unsigned int BNC:1;		// [1]
	unsigned int AC64:1;		// [0]
};
 // DBOFF Register
struct USB3HC_DBOFF {
	unsigned int DOORBELL_ARRAY_OFFSET:30;		// [31:2]
	unsigned int RSVD4:2;		// [1:0]
};
 // RTSOFF Register
struct USB3HC_RTSOFF {
	unsigned int RUNTIME_REG_SPACE_OFFSET:27;		// [31:5]
	unsigned int RSVD5:5;		// [4:0]
};
 // USBCMD Register
struct USB3HC_USBCMD {
	unsigned int RSVD8:20;		// [31:12]
	unsigned int EU3S:1;		// [11]
	unsigned int EWE:1;		// [10]
	unsigned int CRS:1;		// [9]
	unsigned int CSS:1;		// [8]
	unsigned int LHCRST:1;		// [7]
	unsigned int RSVD7:3;		// [6:4]
	unsigned int HSEE:1;		// [3]
	unsigned int INTE:1;		// [2]
	unsigned int HCRST:1;		// [1]
	unsigned int R_S:1;		// [0]
};
 // USBSTS Register
struct USB3HC_USBSTS {
	unsigned int RSVD11:19;		// [31:13]
	unsigned int HCE:1;		// [12]
	unsigned int CNR:1;		// [11]
	unsigned int SRE:1;		// [10]
	unsigned int RSS:1;		// [9]
	unsigned int SSS:1;		// [8]
	unsigned int RSVD10:3;		// [7:5]
	unsigned int PCD:1;		// [4]
	unsigned int EINT:1;		// [3]
	unsigned int HSE:1;		// [2]
	unsigned int RSVD9:1;		// [1]
	unsigned int HCH:1;		// [0]
};
 // PAGESIZE Register
struct USB3HC_PAGESIZE {
	unsigned int RSVD12:16;		// [31:16]
	unsigned int PAGE_SIZE:16;		// [15:0]
};
 // DNCTRL Register
struct USB3HC_DNCTRL {
	unsigned int RSVD13:16;		// [31:16]
	unsigned int N0_N15:16;		// [15:0]
};
 // CRCR_LO Register
struct USB3HC_CRCR_LO {
	unsigned int CMD_RING_PNTR:26;		// [31:6]
	unsigned int RSVD14:2;		// [5:4]
	unsigned int CRR:1;		// [3]
	unsigned int CA:1;		// [2]
	unsigned int CS:1;		// [1]
	unsigned int RCS:1;		// [0]
};
 // CRCR_HI Register
struct USB3HC_CRCR_HI {
	unsigned int CMD_RING_PNTR:32;		// [31:0]
};
 // DCBAAP_LO Register
struct USB3HC_DCBAAP_LO {
	unsigned int DEVICE_CONTEXT_BAAP:26;		// [31:6]
	unsigned int RSVD16:6;		// [5:0]
};
 // DCBAAP_HI Register
struct USB3HC_DCBAAP_HI {
	unsigned int DEVICE_CONTEXT_BAAP:32;		// [31:0]
};
 // CONFIG Register
struct USB3HC_CONFIG {
	unsigned int RSVD17:24;		// [31:8]
	unsigned int MAXSLOTSEN:8;		// [7:0]
};
 // PORTSC_0 Register
struct USB3HC_PORTSC_0 {
	unsigned int WPR:1;		// [31]
	unsigned int DR:1;		// [30]
	unsigned int RSVD20:2;		// [29:28]
	unsigned int WOE:1;		// [27]
	unsigned int WDE:1;		// [26]
	unsigned int WCE:1;		// [25]
	unsigned int CAS:1;		// [24]
	unsigned int CEC:1;		// [23]
	unsigned int PLC:1;		// [22]
	unsigned int PRC:1;		// [21]
	unsigned int OCC:1;		// [20]
	unsigned int WRC:1;		// [19]
	unsigned int PEC:1;		// [18]
	unsigned int CSC:1;		// [17]
	unsigned int LWS:1;		// [16]
	unsigned int PIC:2;		// [15:14]
	unsigned int PORTSPEED:4;		// [13:10]
	unsigned int PP:1;		// [9]
	unsigned int PLS:4;		// [8:5]
	unsigned int PR:1;		// [4]
	unsigned int OCA:1;		// [3]
	unsigned int RSVD18:1;		// [2]
	unsigned int PED:1;		// [1]
	unsigned int CCS:1;		// [0]
};
 // PORTPMSC_20_0 Register
struct USB3HC_PORTPMSC_20_0 {
	unsigned int PRTTSTCTRL:4;		// [31:28]
	unsigned int Rsvd10:11;		// [27:17]
	unsigned int HLE:1;		// [16]
	unsigned int L1DSLOT:8;		// [15:8]
	unsigned int HIRD:4;		// [7:4]
	unsigned int PWE:1;		// [3]
	unsigned int L1S:3;		// [2:0]
};
 // PORTLI_0 Register
struct USB3HC_PORTLI_0 {
	unsigned int RSVD22:16;		// [31:16]
	unsigned int LINK_ERROR_COUNT:16;		// [15:0]
};
 // PORTSC_1 Register
struct USB3HC_PORTSC_1 {
	unsigned int WPR:1;		// [31]
	unsigned int DR:1;		// [30]
	unsigned int RSVD20:2;		// [29:28]
	unsigned int WOE:1;		// [27]
	unsigned int WDE:1;		// [26]
	unsigned int WCE:1;		// [25]
	unsigned int CAS:1;		// [24]
	unsigned int CEC:1;		// [23]
	unsigned int PLC:1;		// [22]
	unsigned int PRC:1;		// [21]
	unsigned int OCC:1;		// [20]
	unsigned int WRC:1;		// [19]
	unsigned int PEC:1;		// [18]
	unsigned int CSC:1;		// [17]
	unsigned int LWS:1;		// [16]
	unsigned int PIC:2;		// [15:14]
	unsigned int PORTSPEED:4;		// [13:10]
	unsigned int PP:1;		// [9]
	unsigned int PLS:4;		// [8:5]
	unsigned int PR:1;		// [4]
	unsigned int OCA:1;		// [3]
	unsigned int RSVD18:1;		// [2]
	unsigned int PED:1;		// [1]
	unsigned int CCS:1;		// [0]
};
 // PORTPMSC_SS_0 Register
struct USB3HC_PORTPMSC_SS_0 {
	unsigned int RSVD21:15;		// [31:17]
	unsigned int FLA:1;		// [16]
	unsigned int U2_TIMEOUT:8;		// [15:8]
	unsigned int U1_TIMEOUT:8;		// [7:0]
};
 // PORTLI_1 Register
struct USB3HC_PORTLI_1 {
	unsigned int RSVD22:16;		// [31:16]
	unsigned int LINK_ERROR_COUNT:16;		// [15:0]
};
 // MFINDEX Register
struct USB3HC_MFINDEX {
	unsigned int RSVD23:18;		// [31:14]
	unsigned int MICROFRAME_INDEX:14;		// [13:0]
};
 // IMAN_0 Register
struct USB3HC_IMAN_0 {
	unsigned int RSVD25:30;		// [31:2]
	unsigned int IE:1;		// [1]
	unsigned int IP:1;		// [0]
};
 // IMOD_0 Register
struct USB3HC_IMOD_0 {
	unsigned int IMODC:16;		// [31:16]
	unsigned int IMODI:16;		// [15:0]
};
 // ERSTSZ_0 Register
struct USB3HC_ERSTSZ_0 {
	unsigned int RSVD26:16;		// [31:16]
	unsigned int ERS_TABLE_SIZE:16;		// [15:0]
};
 // ERSTBA_LO_0 Register
struct USB3HC_ERSTBA_LO_0 {
	unsigned int ERS_TABLE_BAR:26;		// [31:6]
	unsigned int RSVD28:6;		// [5:0]
};
 // ERSTBA_HI_0 Register
struct USB3HC_ERSTBA_HI_0 {
	unsigned int ERS_TABLE_BAR:32;		// [31:0]
};
 // ERDP_LO_0 Register
struct USB3HC_ERDP_LO_0 {
	unsigned int ERD_PNTR:28;		// [31:4]
	unsigned int EHB:1;		// [3]
	unsigned int DESI:3;		// [2:0]
};
 // ERDP_HI_0 Register
struct USB3HC_ERDP_HI_0 {
	unsigned int ERD_PNTR:32;		// [31:0]
};
 // DB_0 Register
struct USB3HC_DB_0 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_1 Register
struct USB3HC_DB_1 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_2 Register
struct USB3HC_DB_2 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_3 Register
struct USB3HC_DB_3 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_4 Register
struct USB3HC_DB_4 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_5 Register
struct USB3HC_DB_5 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_6 Register
struct USB3HC_DB_6 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_7 Register
struct USB3HC_DB_7 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_8 Register
struct USB3HC_DB_8 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_9 Register
struct USB3HC_DB_9 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_10 Register
struct USB3HC_DB_10 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_11 Register
struct USB3HC_DB_11 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_12 Register
struct USB3HC_DB_12 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_13 Register
struct USB3HC_DB_13 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_14 Register
struct USB3HC_DB_14 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_15 Register
struct USB3HC_DB_15 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_16 Register
struct USB3HC_DB_16 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_17 Register
struct USB3HC_DB_17 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_18 Register
struct USB3HC_DB_18 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_19 Register
struct USB3HC_DB_19 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_20 Register
struct USB3HC_DB_20 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_21 Register
struct USB3HC_DB_21 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_22 Register
struct USB3HC_DB_22 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_23 Register
struct USB3HC_DB_23 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_24 Register
struct USB3HC_DB_24 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_25 Register
struct USB3HC_DB_25 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_26 Register
struct USB3HC_DB_26 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_27 Register
struct USB3HC_DB_27 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_28 Register
struct USB3HC_DB_28 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_29 Register
struct USB3HC_DB_29 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_30 Register
struct USB3HC_DB_30 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_31 Register
struct USB3HC_DB_31 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_32 Register
struct USB3HC_DB_32 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_33 Register
struct USB3HC_DB_33 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_34 Register
struct USB3HC_DB_34 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_35 Register
struct USB3HC_DB_35 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_36 Register
struct USB3HC_DB_36 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_37 Register
struct USB3HC_DB_37 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_38 Register
struct USB3HC_DB_38 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_39 Register
struct USB3HC_DB_39 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_40 Register
struct USB3HC_DB_40 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_41 Register
struct USB3HC_DB_41 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_42 Register
struct USB3HC_DB_42 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_43 Register
struct USB3HC_DB_43 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_44 Register
struct USB3HC_DB_44 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_45 Register
struct USB3HC_DB_45 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_46 Register
struct USB3HC_DB_46 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_47 Register
struct USB3HC_DB_47 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_48 Register
struct USB3HC_DB_48 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_49 Register
struct USB3HC_DB_49 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_50 Register
struct USB3HC_DB_50 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_51 Register
struct USB3HC_DB_51 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_52 Register
struct USB3HC_DB_52 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_53 Register
struct USB3HC_DB_53 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_54 Register
struct USB3HC_DB_54 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_55 Register
struct USB3HC_DB_55 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_56 Register
struct USB3HC_DB_56 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_57 Register
struct USB3HC_DB_57 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_58 Register
struct USB3HC_DB_58 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_59 Register
struct USB3HC_DB_59 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_60 Register
struct USB3HC_DB_60 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_61 Register
struct USB3HC_DB_61 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_62 Register
struct USB3HC_DB_62 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_63 Register
struct USB3HC_DB_63 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_64 Register
struct USB3HC_DB_64 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_65 Register
struct USB3HC_DB_65 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_66 Register
struct USB3HC_DB_66 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_67 Register
struct USB3HC_DB_67 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_68 Register
struct USB3HC_DB_68 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_69 Register
struct USB3HC_DB_69 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_70 Register
struct USB3HC_DB_70 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_71 Register
struct USB3HC_DB_71 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_72 Register
struct USB3HC_DB_72 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_73 Register
struct USB3HC_DB_73 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_74 Register
struct USB3HC_DB_74 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_75 Register
struct USB3HC_DB_75 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_76 Register
struct USB3HC_DB_76 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_77 Register
struct USB3HC_DB_77 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_78 Register
struct USB3HC_DB_78 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_79 Register
struct USB3HC_DB_79 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_80 Register
struct USB3HC_DB_80 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_81 Register
struct USB3HC_DB_81 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_82 Register
struct USB3HC_DB_82 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_83 Register
struct USB3HC_DB_83 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_84 Register
struct USB3HC_DB_84 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_85 Register
struct USB3HC_DB_85 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_86 Register
struct USB3HC_DB_86 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_87 Register
struct USB3HC_DB_87 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_88 Register
struct USB3HC_DB_88 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_89 Register
struct USB3HC_DB_89 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_90 Register
struct USB3HC_DB_90 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_91 Register
struct USB3HC_DB_91 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_92 Register
struct USB3HC_DB_92 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_93 Register
struct USB3HC_DB_93 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_94 Register
struct USB3HC_DB_94 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_95 Register
struct USB3HC_DB_95 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_96 Register
struct USB3HC_DB_96 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_97 Register
struct USB3HC_DB_97 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_98 Register
struct USB3HC_DB_98 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_99 Register
struct USB3HC_DB_99 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_100 Register
struct USB3HC_DB_100 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_101 Register
struct USB3HC_DB_101 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_102 Register
struct USB3HC_DB_102 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_103 Register
struct USB3HC_DB_103 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_104 Register
struct USB3HC_DB_104 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_105 Register
struct USB3HC_DB_105 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_106 Register
struct USB3HC_DB_106 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_107 Register
struct USB3HC_DB_107 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_108 Register
struct USB3HC_DB_108 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_109 Register
struct USB3HC_DB_109 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_110 Register
struct USB3HC_DB_110 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_111 Register
struct USB3HC_DB_111 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_112 Register
struct USB3HC_DB_112 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_113 Register
struct USB3HC_DB_113 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_114 Register
struct USB3HC_DB_114 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_115 Register
struct USB3HC_DB_115 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_116 Register
struct USB3HC_DB_116 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_117 Register
struct USB3HC_DB_117 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_118 Register
struct USB3HC_DB_118 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_119 Register
struct USB3HC_DB_119 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_120 Register
struct USB3HC_DB_120 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_121 Register
struct USB3HC_DB_121 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_122 Register
struct USB3HC_DB_122 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_123 Register
struct USB3HC_DB_123 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_124 Register
struct USB3HC_DB_124 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_125 Register
struct USB3HC_DB_125 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // DB_126 Register
struct USB3HC_DB_126 {
	unsigned int DB_STREAM_ID:16;		// [31:16]
	unsigned int RSVD29:8;		// [15:8]
	unsigned int DB_TARGET:8;		// [7:0]
};
 // USBLEGSUP Register
struct USB3HC_USBLEGSUP {
	unsigned int RSVD31:7;		// [31:25]
	unsigned int HC_OS_OWNED:1;		// [24]
	unsigned int RSVD30:7;		// [23:17]
	unsigned int HC_BIOS_OWNED:1;		// [16]
	unsigned int NEXT_CAPABILITY_POINTER:8;		// [15:8]
	unsigned int CAPABILITY_ID:8;		// [7:0]
};
 // USBLEGCTLSTS Register
struct USB3HC_USBLEGCTLSTS {
	unsigned int SMI_ON_BAR:1;		// [31]
	unsigned int SMI_ON_PCI:1;		// [30]
	unsigned int SMI_ON_OS:1;		// [29]
	unsigned int RSVD35:8;		// [28:21]
	unsigned int SMI_ON_HOST:1;		// [20]
	unsigned int RSVD34:3;		// [19:17]
	unsigned int SMI_ON_EVENT:1;		// [16]
	unsigned int SMI_ON_BAR_E:1;		// [15]
	unsigned int SMI_ON_PCI_E:1;		// [14]
	unsigned int SMI_ON_OS_E:1;		// [13]
	unsigned int RSVD33:8;		// [12:5]
	unsigned int SMI_ON_HOST_E:1;		// [4]
	unsigned int RSVD32:3;		// [3:1]
	unsigned int USB_SMI_ENABLE:1;		// [0]
};
 // SUPTPRT2_DW0 Register
struct USB3HC_SUPTPRT2_DW0 {
	unsigned int MAJOR_REVISION:8;		// [31:24]
	unsigned int MINOR_REVISION:8;		// [23:16]
	unsigned int NEXT_CAPABILITY_POINTER:8;		// [15:8]
	unsigned int CAPABILITY_ID:8;		// [7:0]
};
 // SUPTPRT2_DW1 Register
struct USB3HC_SUPTPRT2_DW1 {
	unsigned int NAME_STRING:32;		// [31:0]
};
 // SUPTPRT2_DW2 Register
struct USB3HC_SUPTPRT2_DW2 {
	unsigned int PSIC:4;		// [31:28]
	unsigned int Rsvd14:8;		// [27:20]
	unsigned int HLC:1;		// [19]
	unsigned int IHI:1;		// [18]
	unsigned int HSO:1;		// [17]
	unsigned int Rsvd8:1;		// [16]
	unsigned int COMPATIBLE_PORT_COUNT:8;		// [15:8]
	unsigned int COMPATIBLE_PORT_OFFSET:8;		// [7:0]
};
 // SUPTPRT2_DW3 Register
struct USB3HC_SUPTPRT2_DW3 {
	unsigned int reserved:27;		// [31:5]
	unsigned int PROTCL_SLT_TY:5;		// [4:0]
};
 // SUPTPRT3_DW0 Register
struct USB3HC_SUPTPRT3_DW0 {
	unsigned int MAJOR_REVISION:8;		// [31:24]
	unsigned int MINOR_REVISION:8;		// [23:16]
	unsigned int NEXT_CAPABILITY_POINTER:8;		// [15:8]
	unsigned int CAPABILITY_ID:8;		// [7:0]
};
 // SUPTPRT3_DW1 Register
struct USB3HC_SUPTPRT3_DW1 {
	unsigned int NAME_STRING:32;		// [31:0]
};
 // SUPTPRT3_DW2 Register
struct USB3HC_SUPTPRT3_DW2 {
	unsigned int PSIC:4;		// [31:28]
	unsigned int RSVD34:12;		// [27:16]
	unsigned int COMPATIBLE_PORT_COUNT:8;		// [15:8]
	unsigned int COMPATIBLE_PORT_OFFSET:8;		// [7:0]
};
 // SUPTPRT3_DW3 Register
struct USB3HC_SUPTPRT3_DW3 {
	unsigned int Rsvd7:27;		// [31:5]
	unsigned int PROTCL_SLT_TY:5;		// [4:0]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _USB3HC_REG_STRUCT_B_H */
