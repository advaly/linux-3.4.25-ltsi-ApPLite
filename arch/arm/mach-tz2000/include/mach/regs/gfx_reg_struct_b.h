/*
 * arch/arm/mach-tz2000/include/mach/regs/gfx_reg_struct_b.h
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

#ifndef _GFX_REG_STRUCT_B_H
#define _GFX_REG_STRUCT_B_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // GASCR Register
struct GFX_GASCR {
	unsigned int reserved:23;		// [31:9]
	unsigned int DISRA:1;		// [8]
	unsigned int reserved2:6;		// [7:2]
	unsigned int GAEN:1;		// [1]
	unsigned int GARESET:1;		// [0]
};
 // GACLAR Register
struct GFX_GACLAR {
	unsigned int CSLA:29;		// [31:3]
	unsigned int reserved:3;		// [2:0]
};
 // GASR Register
struct GFX_GASR {
	unsigned int reserved:28;		// [31:4]
	unsigned int CSLEF:1;		// [3]
	unsigned int CSCEF:1;		// [2]
	unsigned int reserved2:1;		// [1]
	unsigned int BUSY:1;		// [0]
};
 // GAICR Register
struct GFX_GAICR {
	unsigned int CSLUI:24;		// [31:8]
	unsigned int GARBI:1;		// [7]
	unsigned int GACBI:1;		// [6]
	unsigned int GAWBRI:1;		// [5]
	unsigned int GAWBWI:1;		// [4]
	unsigned int CSLEI:1;		// [3]
	unsigned int CSCEI:1;		// [2]
	unsigned int reserved:1;		// [1]
	unsigned int GACENDI:1;		// [0]
};
 // GAIMR Register
struct GFX_GAIMR {
	unsigned int CSLUIM:24;		// [31:8]
	unsigned int GARBIM:1;		// [7]
	unsigned int GACBIM:1;		// [6]
	unsigned int GAWBRIM:1;		// [5]
	unsigned int GAWBWIM:1;		// [4]
	unsigned int CSLEIM:1;		// [3]
	unsigned int CSCEIM:1;		// [2]
	unsigned int reserved:1;		// [1]
	unsigned int GACENDIM:1;		// [0]
};
 // GADR Register
struct GFX_GADR {
	unsigned int reserved:16;		// [31:16]
	unsigned int GAD:16;		// [15:0]
};
 // GARBBEAR Register
struct GFX_GARBBEAR {
	unsigned int RBA:29;		// [31:3]
	unsigned int reserved:3;		// [2:0]
};
 // GARBBECR Register
struct GFX_GARBBECR {
	unsigned int reserved:8;		// [31:24]
	unsigned int LEN:4;		// [23:20]
	unsigned int ID:4;		// [19:16]
	unsigned int BEN:8;		// [15:8]
	unsigned int reserved2:1;		// [7]
	unsigned int RTYPE:2;		// [6:5]
	unsigned int BSIZE:3;		// [4:2]
	unsigned int BTYPE:1;		// [1]
	unsigned int WR:1;		// [0]
};
 // GACBBEAR Register
struct GFX_GACBBEAR {
	unsigned int CBA:29;		// [31:3]
	unsigned int reserved:3;		// [2:0]
};
 // GACBBECR Register
struct GFX_GACBBECR {
	unsigned int reserved:8;		// [31:24]
	unsigned int LEN:4;		// [23:20]
	unsigned int ID:4;		// [19:16]
	unsigned int BEN:8;		// [15:8]
	unsigned int reserved2:1;		// [7]
	unsigned int RTYPE:2;		// [6:5]
	unsigned int BSIZE:3;		// [4:2]
	unsigned int BTYPE:1;		// [1]
	unsigned int WR:1;		// [0]
};
 // GAWBRBEAR Register
struct GFX_GAWBRBEAR {
	unsigned int WBRA:29;		// [31:3]
	unsigned int reserved:3;		// [2:0]
};
 // GAWBRBECR Register
struct GFX_GAWBRBECR {
	unsigned int reserved:8;		// [31:24]
	unsigned int LEN:4;		// [23:20]
	unsigned int ID:4;		// [19:16]
	unsigned int BEN:8;		// [15:8]
	unsigned int reserved2:1;		// [7]
	unsigned int RTYPE:2;		// [6:5]
	unsigned int BSIZE:3;		// [4:2]
	unsigned int BTYPE:1;		// [1]
	unsigned int WR:1;		// [0]
};
 // GAWBWBEAR Register
struct GFX_GAWBWBEAR {
	unsigned int WBWA:29;		// [31:3]
	unsigned int reserved:3;		// [2:0]
};
 // GAWBWBECR Register
struct GFX_GAWBWBECR {
	unsigned int reserved:8;		// [31:24]
	unsigned int LEN:4;		// [23:20]
	unsigned int ID:4;		// [19:16]
	unsigned int BEN:8;		// [15:8]
	unsigned int reserved2:1;		// [7]
	unsigned int RTYPE:2;		// [6:5]
	unsigned int BSIZE:3;		// [4:2]
	unsigned int BTYPE:1;		// [1]
	unsigned int WR:1;		// [0]
};
 // GAMPR0LR Register
struct GFX_GAMPR0LR {
	unsigned int MPR0L:20;		// [31:12]
	unsigned int reserved:12;		// [11:0]
};
 // GAMPR0HR Register
struct GFX_GAMPR0HR {
	unsigned int MPR0H:20;		// [31:12]
	unsigned int reserved:12;		// [11:0]
};
 // GAMPR1LR Register
struct GFX_GAMPR1LR {
	unsigned int MPR0L:20;		// [31:12]
	unsigned int reserved:12;		// [11:0]
};
 // GAMPR1HR Register
struct GFX_GAMPR1HR {
	unsigned int MPR0H:20;		// [31:12]
	unsigned int reserved:12;		// [11:0]
};
 // GAMPICR Register
struct GFX_GAMPICR {
	unsigned int reserved:30;		// [31:2]
	unsigned int GAMPCI:1;		// [1]
	unsigned int GAMPI:1;		// [0]
};
 // GAMPIMR Register
struct GFX_GAMPIMR {
	unsigned int reserved:30;		// [31:2]
	unsigned int GAMPCIM:1;		// [1]
	unsigned int GAMPIM:1;		// [0]
};
 // GAMPACR Register
struct GFX_GAMPACR {
	unsigned int MPVA:29;		// [31:3]
	unsigned int reserved:3;		// [2:0]
};
 // GAGPR0 Register
struct GFX_GAGPR0 {
	unsigned int GAGPR0:32;		// [31:0]
};
 // GAGPR1 Register
struct GFX_GAGPR1 {
	unsigned int GAGPR1:32;		// [31:0]
};
 // GAGPR2 Register
struct GFX_GAGPR2 {
	unsigned int GAGPR2:32;		// [31:0]
};
 // GAGPR3 Register
struct GFX_GAGPR3 {
	unsigned int GAGPR3:32;		// [31:0]
};
 // GAGPR4 Register
struct GFX_GAGPR4 {
	unsigned int GAGPR4:32;		// [31:0]
};
 // GAGPR5 Register
struct GFX_GAGPR5 {
	unsigned int GAGPR5:32;		// [31:0]
};
 // GAGPR6 Register
struct GFX_GAGPR6 {
	unsigned int GAGPR6:32;		// [31:0]
};
 // GAGPR7 Register
struct GFX_GAGPR7 {
	unsigned int GAGPR7:32;		// [31:0]
};
 // GAGPR8 Register
struct GFX_GAGPR8 {
	unsigned int GAGPR8:32;		// [31:0]
};
 // GAGPR9 Register
struct GFX_GAGPR9 {
	unsigned int GAGPR9:32;		// [31:0]
};
 // GAGPR10 Register
struct GFX_GAGPR10 {
	unsigned int GAGPR10:32;		// [31:0]
};
 // GAGPR11 Register
struct GFX_GAGPR11 {
	unsigned int GAGPR11:32;		// [31:0]
};
 // GAGPR12 Register
struct GFX_GAGPR12 {
	unsigned int GAGPR12:32;		// [31:0]
};
 // GAGPR13 Register
struct GFX_GAGPR13 {
	unsigned int GAGPR13:32;		// [31:0]
};
 // GAGPR14 Register
struct GFX_GAGPR14 {
	unsigned int GAGPR14:32;		// [31:0]
};
 // GAGPR15 Register
struct GFX_GAGPR15 {
	unsigned int GAGPR15:32;		// [31:0]
};
 // GAGPR16 Register
struct GFX_GAGPR16 {
	unsigned int GAGPR16:32;		// [31:0]
};
 // GAGPR17 Register
struct GFX_GAGPR17 {
	unsigned int GAGPR17:32;		// [31:0]
};
 // GAGPR18 Register
struct GFX_GAGPR18 {
	unsigned int GAGPR18:32;		// [31:0]
};
 // GAGPR19 Register
struct GFX_GAGPR19 {
	unsigned int GAGPR19:32;		// [31:0]
};
 // GAGPR20 Register
struct GFX_GAGPR20 {
	unsigned int GAGPR20:32;		// [31:0]
};
 // GAGPR21 Register
struct GFX_GAGPR21 {
	unsigned int GAGPR21:32;		// [31:0]
};
 // GAGPR22 Register
struct GFX_GAGPR22 {
	unsigned int GAGPR22:32;		// [31:0]
};
 // GAGPR23 Register
struct GFX_GAGPR23 {
	unsigned int GAGPR23:32;		// [31:0]
};
 // GAGPR24 Register
struct GFX_GAGPR24 {
	unsigned int GAGPR24:32;		// [31:0]
};
 // GAGPR25 Register
struct GFX_GAGPR25 {
	unsigned int GAGPR25:32;		// [31:0]
};
 // GAGPR26 Register
struct GFX_GAGPR26 {
	unsigned int GAGPR26:32;		// [31:0]
};
 // GAGPR27 Register
struct GFX_GAGPR27 {
	unsigned int GAGPR27:32;		// [31:0]
};
 // GAGPR28 Register
struct GFX_GAGPR28 {
	unsigned int GAGPR28:32;		// [31:0]
};
 // GAGPR29 Register
struct GFX_GAGPR29 {
	unsigned int GAGPR29:32;		// [31:0]
};
 // GAGPR30 Register
struct GFX_GAGPR30 {
	unsigned int GAGPR30:32;		// [31:0]
};
 // GAGPR31 Register
struct GFX_GAGPR31 {
	unsigned int GAGPR31:32;		// [31:0]
};
 // GACMDL Register
struct GFX_GACMDL {
	unsigned int GACMDL:32;		// [31:0]
};
 // GACMDH Register
struct GFX_GACMDH {
	unsigned int GACMDH:32;		// [31:0]
};
 // DEFC0 Register
struct GFX_DEFC0 {
	unsigned int FC0:8;		// [31:24]
	unsigned int FC1:8;		// [23:16]
	unsigned int FC2:8;		// [15:8]
	unsigned int FC3:8;		// [7:0]
};
 // DEFC1 Register
struct GFX_DEFC1 {
	unsigned int FC4:8;		// [31:24]
	unsigned int FC5:8;		// [23:16]
	unsigned int FC6:8;		// [15:8]
	unsigned int FC7:8;		// [7:0]
};
 // DEFC2 Register
struct GFX_DEFC2 {
	unsigned int FC8:8;		// [31:24]
	unsigned int FC9:8;		// [23:16]
	unsigned int FC10:8;		// [15:8]
	unsigned int FC11:8;		// [7:0]
};
 // DEFC3 Register
struct GFX_DEFC3 {
	unsigned int FC12:8;		// [31:24]
	unsigned int FC13:8;		// [23:16]
	unsigned int FC14:8;		// [15:8]
	unsigned int FC15:8;		// [7:0]
};
 // DEFC4 Register
struct GFX_DEFC4 {
	unsigned int FC16:8;		// [31:24]
	unsigned int FC17:8;		// [23:16]
	unsigned int FC18:8;		// [15:8]
	unsigned int FC19:8;		// [7:0]
};
 // DEFC5 Register
struct GFX_DEFC5 {
	unsigned int FC20:8;		// [31:24]
	unsigned int FC21:8;		// [23:16]
	unsigned int FC22:8;		// [15:8]
	unsigned int FC23:8;		// [7:0]
};
 // DEFC6 Register
struct GFX_DEFC6 {
	unsigned int FC24:8;		// [31:24]
	unsigned int FC25:8;		// [23:16]
	unsigned int FC26:8;		// [15:8]
	unsigned int FC27:8;		// [7:0]
};
 // DEFC7 Register
struct GFX_DEFC7 {
	unsigned int FC28:8;		// [31:24]
	unsigned int FC29:8;		// [23:16]
	unsigned int FC30:8;		// [15:8]
	unsigned int FC31:8;		// [7:0]
};
 // DEFC8 Register
struct GFX_DEFC8 {
	unsigned int FC32:8;		// [31:24]
	unsigned int FC33:8;		// [23:16]
	unsigned int FC34:8;		// [15:8]
	unsigned int FC35:8;		// [7:0]
};
 // DEFC9 Register
struct GFX_DEFC9 {
	unsigned int FC36:8;		// [31:24]
	unsigned int FC37:8;		// [23:16]
	unsigned int FC38:8;		// [15:8]
	unsigned int FC39:8;		// [7:0]
};
 // DEFC10 Register
struct GFX_DEFC10 {
	unsigned int FC40:8;		// [31:24]
	unsigned int FC41:8;		// [23:16]
	unsigned int FC42:8;		// [15:8]
	unsigned int FC43:8;		// [7:0]
};
 // DEFC11 Register
struct GFX_DEFC11 {
	unsigned int FC44:8;		// [31:24]
	unsigned int FC45:8;		// [23:16]
	unsigned int FC46:8;		// [15:8]
	unsigned int FC47:8;		// [7:0]
};
 // DEFC12 Register
struct GFX_DEFC12 {
	unsigned int FC48:8;		// [31:24]
	unsigned int FC49:8;		// [23:16]
	unsigned int FC50:8;		// [15:8]
	unsigned int FC51:8;		// [7:0]
};
 // DEFC13 Register
struct GFX_DEFC13 {
	unsigned int FC52:8;		// [31:24]
	unsigned int FC53:8;		// [23:16]
	unsigned int FC54:8;		// [15:8]
	unsigned int FC55:8;		// [7:0]
};
 // DEFC14 Register
struct GFX_DEFC14 {
	unsigned int FC56:8;		// [31:24]
	unsigned int FC57:8;		// [23:16]
	unsigned int FC58:8;		// [15:8]
	unsigned int FC59:8;		// [7:0]
};
 // DEFC15 Register
struct GFX_DEFC15 {
	unsigned int FC60:8;		// [31:24]
	unsigned int FC61:8;		// [23:16]
	unsigned int FC62:8;		// [15:8]
	unsigned int FC63:8;		// [7:0]
};
 // DEFC16 Register
struct GFX_DEFC16 {
	unsigned int FC64:8;		// [31:24]
	unsigned int FC65:8;		// [23:16]
	unsigned int FC66:8;		// [15:8]
	unsigned int FC67:8;		// [7:0]
};
 // DEFC17 Register
struct GFX_DEFC17 {
	unsigned int FC68:8;		// [31:24]
	unsigned int FC69:8;		// [23:16]
	unsigned int FC70:8;		// [15:8]
	unsigned int FC71:8;		// [7:0]
};
 // DEFC18 Register
struct GFX_DEFC18 {
	unsigned int FC72:8;		// [31:24]
	unsigned int FC73:8;		// [23:16]
	unsigned int FC74:8;		// [15:8]
	unsigned int FC75:8;		// [7:0]
};
 // DEFC19 Register
struct GFX_DEFC19 {
	unsigned int FC76:8;		// [31:24]
	unsigned int FC77:8;		// [23:16]
	unsigned int FC78:8;		// [15:8]
	unsigned int FC79:8;		// [7:0]
};
 // DEFC20 Register
struct GFX_DEFC20 {
	unsigned int FC80:8;		// [31:24]
	unsigned int FC81:8;		// [23:16]
	unsigned int FC82:8;		// [15:8]
	unsigned int FC83:8;		// [7:0]
};
 // DEFC21 Register
struct GFX_DEFC21 {
	unsigned int FC84:8;		// [31:24]
	unsigned int FC85:8;		// [23:16]
	unsigned int FC86:8;		// [15:8]
	unsigned int FC87:8;		// [7:0]
};
 // DEFC22 Register
struct GFX_DEFC22 {
	unsigned int FC88:8;		// [31:24]
	unsigned int FC89:8;		// [23:16]
	unsigned int FC90:8;		// [15:8]
	unsigned int FC91:8;		// [7:0]
};
 // DEFC23 Register
struct GFX_DEFC23 {
	unsigned int FC92:8;		// [31:24]
	unsigned int FC93:8;		// [23:16]
	unsigned int FC94:8;		// [15:8]
	unsigned int FC95:8;		// [7:0]
};
 // DEFC24 Register
struct GFX_DEFC24 {
	unsigned int FC96:8;		// [31:24]
	unsigned int FC97:8;		// [23:16]
	unsigned int FC98:8;		// [15:8]
	unsigned int FC99:8;		// [7:0]
};
 // DEFC25 Register
struct GFX_DEFC25 {
	unsigned int FC100:8;		// [31:24]
	unsigned int FC101:8;		// [23:16]
	unsigned int FC102:8;		// [15:8]
	unsigned int FC103:8;		// [7:0]
};
 // DEFC26 Register
struct GFX_DEFC26 {
	unsigned int FC104:8;		// [31:24]
	unsigned int FC105:8;		// [23:16]
	unsigned int FC106:8;		// [15:8]
	unsigned int FC107:8;		// [7:0]
};
 // DEFC27 Register
struct GFX_DEFC27 {
	unsigned int FC108:8;		// [31:24]
	unsigned int FC109:8;		// [23:16]
	unsigned int FC110:8;		// [15:8]
	unsigned int FC111:8;		// [7:0]
};
 // DEFC28 Register
struct GFX_DEFC28 {
	unsigned int FC112:8;		// [31:24]
	unsigned int FC113:8;		// [23:16]
	unsigned int FC114:8;		// [15:8]
	unsigned int FC115:8;		// [7:0]
};
 // DEFC29 Register
struct GFX_DEFC29 {
	unsigned int FC116:8;		// [31:24]
	unsigned int FC117:8;		// [23:16]
	unsigned int FC118:8;		// [15:8]
	unsigned int FC119:8;		// [7:0]
};
 // DEFC30 Register
struct GFX_DEFC30 {
	unsigned int FC120:8;		// [31:24]
	unsigned int FC121:8;		// [23:16]
	unsigned int FC122:8;		// [15:8]
	unsigned int FC123:8;		// [7:0]
};
 // DEFC31 Register
struct GFX_DEFC31 {
	unsigned int FC124:8;		// [31:24]
	unsigned int FC125:8;		// [23:16]
	unsigned int FC126:8;		// [15:8]
	unsigned int FC127:8;		// [7:0]
};
 // DEFC32 Register
struct GFX_DEFC32 {
	unsigned int FC128:8;		// [31:24]
	unsigned int FC129:8;		// [23:16]
	unsigned int FC130:8;		// [15:8]
	unsigned int FC131:8;		// [7:0]
};
 // DEFC33 Register
struct GFX_DEFC33 {
	unsigned int FC132:8;		// [31:24]
	unsigned int FC133:8;		// [23:16]
	unsigned int FC134:8;		// [15:8]
	unsigned int FC135:8;		// [7:0]
};
 // DEFC34 Register
struct GFX_DEFC34 {
	unsigned int FC136:8;		// [31:24]
	unsigned int FC137:8;		// [23:16]
	unsigned int FC138:8;		// [15:8]
	unsigned int FC139:8;		// [7:0]
};
 // DEFC35 Register
struct GFX_DEFC35 {
	unsigned int FC140:8;		// [31:24]
	unsigned int FC141:8;		// [23:16]
	unsigned int FC142:8;		// [15:8]
	unsigned int FC143:8;		// [7:0]
};
 // DEFC36 Register
struct GFX_DEFC36 {
	unsigned int FC144:8;		// [31:24]
	unsigned int FC145:8;		// [23:16]
	unsigned int FC146:8;		// [15:8]
	unsigned int FC147:8;		// [7:0]
};
 // DEFC37 Register
struct GFX_DEFC37 {
	unsigned int FC148:8;		// [31:24]
	unsigned int FC149:8;		// [23:16]
	unsigned int FC150:8;		// [15:8]
	unsigned int FC151:8;		// [7:0]
};
 // DEFC38 Register
struct GFX_DEFC38 {
	unsigned int FC152:8;		// [31:24]
	unsigned int FC153:8;		// [23:16]
	unsigned int FC154:8;		// [15:8]
	unsigned int FC155:8;		// [7:0]
};
 // DEFC39 Register
struct GFX_DEFC39 {
	unsigned int FC156:8;		// [31:24]
	unsigned int FC157:8;		// [23:16]
	unsigned int FC158:8;		// [15:8]
	unsigned int FC159:8;		// [7:0]
};
 // DEFC40 Register
struct GFX_DEFC40 {
	unsigned int FC160:8;		// [31:24]
	unsigned int FC161:8;		// [23:16]
	unsigned int FC162:8;		// [15:8]
	unsigned int FC163:8;		// [7:0]
};
 // DEFC41 Register
struct GFX_DEFC41 {
	unsigned int FC164:8;		// [31:24]
	unsigned int FC165:8;		// [23:16]
	unsigned int FC166:8;		// [15:8]
	unsigned int FC167:8;		// [7:0]
};
 // DEFC42 Register
struct GFX_DEFC42 {
	unsigned int FC168:8;		// [31:24]
	unsigned int FC169:8;		// [23:16]
	unsigned int FC170:8;		// [15:8]
	unsigned int FC171:8;		// [7:0]
};
 // DEFC43 Register
struct GFX_DEFC43 {
	unsigned int FC172:8;		// [31:24]
	unsigned int FC173:8;		// [23:16]
	unsigned int FC174:8;		// [15:8]
	unsigned int FC175:8;		// [7:0]
};
 // DEFC44 Register
struct GFX_DEFC44 {
	unsigned int FC176:8;		// [31:24]
	unsigned int FC177:8;		// [23:16]
	unsigned int FC178:8;		// [15:8]
	unsigned int FC179:8;		// [7:0]
};
 // DEFC45 Register
struct GFX_DEFC45 {
	unsigned int FC180:8;		// [31:24]
	unsigned int FC181:8;		// [23:16]
	unsigned int FC182:8;		// [15:8]
	unsigned int FC183:8;		// [7:0]
};
 // DEFC46 Register
struct GFX_DEFC46 {
	unsigned int FC184:8;		// [31:24]
	unsigned int FC185:8;		// [23:16]
	unsigned int FC186:8;		// [15:8]
	unsigned int FC187:8;		// [7:0]
};
 // DEFC47 Register
struct GFX_DEFC47 {
	unsigned int FC188:8;		// [31:24]
	unsigned int FC189:8;		// [23:16]
	unsigned int FC190:8;		// [15:8]
	unsigned int FC191:8;		// [7:0]
};
 // DEFC48 Register
struct GFX_DEFC48 {
	unsigned int FC192:8;		// [31:24]
	unsigned int FC193:8;		// [23:16]
	unsigned int FC194:8;		// [15:8]
	unsigned int FC195:8;		// [7:0]
};
 // DEFC49 Register
struct GFX_DEFC49 {
	unsigned int FC196:8;		// [31:24]
	unsigned int FC197:8;		// [23:16]
	unsigned int FC198:8;		// [15:8]
	unsigned int FC199:8;		// [7:0]
};
 // DEFC50 Register
struct GFX_DEFC50 {
	unsigned int FC200:8;		// [31:24]
	unsigned int FC201:8;		// [23:16]
	unsigned int FC202:8;		// [15:8]
	unsigned int FC203:8;		// [7:0]
};
 // DEFC51 Register
struct GFX_DEFC51 {
	unsigned int FC204:8;		// [31:24]
	unsigned int FC205:8;		// [23:16]
	unsigned int FC206:8;		// [15:8]
	unsigned int FC207:8;		// [7:0]
};
 // DEFC52 Register
struct GFX_DEFC52 {
	unsigned int FC208:8;		// [31:24]
	unsigned int FC209:8;		// [23:16]
	unsigned int FC210:8;		// [15:8]
	unsigned int FC211:8;		// [7:0]
};
 // DEFC53 Register
struct GFX_DEFC53 {
	unsigned int FC212:8;		// [31:24]
	unsigned int FC213:8;		// [23:16]
	unsigned int FC214:8;		// [15:8]
	unsigned int FC215:8;		// [7:0]
};
 // DEFC54 Register
struct GFX_DEFC54 {
	unsigned int FC216:8;		// [31:24]
	unsigned int FC217:8;		// [23:16]
	unsigned int FC218:8;		// [15:8]
	unsigned int FC219:8;		// [7:0]
};
 // DEFC55 Register
struct GFX_DEFC55 {
	unsigned int FC220:8;		// [31:24]
	unsigned int FC221:8;		// [23:16]
	unsigned int FC222:8;		// [15:8]
	unsigned int FC223:8;		// [7:0]
};
 // DEFC56 Register
struct GFX_DEFC56 {
	unsigned int FC224:8;		// [31:24]
	unsigned int FC225:8;		// [23:16]
	unsigned int FC226:8;		// [15:8]
	unsigned int FC227:8;		// [7:0]
};
 // DEFC57 Register
struct GFX_DEFC57 {
	unsigned int FC228:8;		// [31:24]
	unsigned int FC229:8;		// [23:16]
	unsigned int FC230:8;		// [15:8]
	unsigned int FC231:8;		// [7:0]
};
 // DEFC58 Register
struct GFX_DEFC58 {
	unsigned int FC232:8;		// [31:24]
	unsigned int FC233:8;		// [23:16]
	unsigned int FC234:8;		// [15:8]
	unsigned int FC235:8;		// [7:0]
};
 // DEFC59 Register
struct GFX_DEFC59 {
	unsigned int FC236:8;		// [31:24]
	unsigned int FC237:8;		// [23:16]
	unsigned int FC238:8;		// [15:8]
	unsigned int FC239:8;		// [7:0]
};
 // DEFC60 Register
struct GFX_DEFC60 {
	unsigned int FC240:8;		// [31:24]
	unsigned int FC241:8;		// [23:16]
	unsigned int FC242:8;		// [15:8]
	unsigned int FC243:8;		// [7:0]
};
 // DEFC61 Register
struct GFX_DEFC61 {
	unsigned int FC244:8;		// [31:24]
	unsigned int FC245:8;		// [23:16]
	unsigned int FC246:8;		// [15:8]
	unsigned int FC247:8;		// [7:0]
};
 // DEFC62 Register
struct GFX_DEFC62 {
	unsigned int FC248:8;		// [31:24]
	unsigned int FC249:8;		// [23:16]
	unsigned int FC250:8;		// [15:8]
	unsigned int FC251:8;		// [7:0]
};
 // DEFC63 Register
struct GFX_DEFC63 {
	unsigned int FC252:8;		// [31:24]
	unsigned int FC253:8;		// [23:16]
	unsigned int FC254:8;		// [15:8]
	unsigned int FC255:8;		// [7:0]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _GFX_REG_STRUCT_B_H */
