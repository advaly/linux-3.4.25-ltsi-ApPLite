/*
 * arch/arm/mach-tz2000/include/mach/regs/gfx_offs_def.h
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

#ifndef GFX_OFFS_DEF_H
#define GFX_OFFS_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

#define GFX_GASCR_OFFS                 0x00000000
#define GFX_GACLAR_OFFS                0x00000004
#define GFX_GASR_OFFS                  0x00000008
#define GFX_GAICR_OFFS                 0x0000000C
#define GFX_GAIMR_OFFS                 0x00000010
#define GFX_GADR_OFFS                  0x00000014
#define GFX_GARBBEAR_OFFS              0x00000020
#define GFX_GARBBECR_OFFS              0x00000024
#define GFX_GACBBEAR_OFFS              0x00000028
#define GFX_GACBBECR_OFFS              0x0000002C
#define GFX_GAWBRBEAR_OFFS             0x00000030
#define GFX_GAWBRBECR_OFFS             0x00000034
#define GFX_GAWBWBEAR_OFFS             0x00000038
#define GFX_GAWBWBECR_OFFS             0x0000003C
#define GFX_GAMPR0LR_OFFS              0x00000040
#define GFX_GAMPR0HR_OFFS              0x00000044
#define GFX_GAMPR1LR_OFFS              0x00000048
#define GFX_GAMPR1HR_OFFS              0x0000004C
#define GFX_GAMPICR_OFFS               0x00000050
#define GFX_GAMPIMR_OFFS               0x00000054
#define GFX_GAMPACR_OFFS               0x00000058
#define GFX_GAGPR0_OFFS                0x00000080
#define GFX_GAGPR1_OFFS                0x00000084
#define GFX_GAGPR2_OFFS                0x00000088
#define GFX_GAGPR3_OFFS                0x0000008C
#define GFX_GAGPR4_OFFS                0x00000090
#define GFX_GAGPR5_OFFS                0x00000094
#define GFX_GAGPR6_OFFS                0x00000098
#define GFX_GAGPR7_OFFS                0x0000009C
#define GFX_GAGPR8_OFFS                0x000000A0
#define GFX_GAGPR9_OFFS                0x000000A4
#define GFX_GAGPR10_OFFS               0x000000A8
#define GFX_GAGPR11_OFFS               0x000000AC
#define GFX_GAGPR12_OFFS               0x000000B0
#define GFX_GAGPR13_OFFS               0x000000B4
#define GFX_GAGPR14_OFFS               0x000000B8
#define GFX_GAGPR15_OFFS               0x000000BC
#define GFX_GAGPR16_OFFS               0x000000C0
#define GFX_GAGPR17_OFFS               0x000000C4
#define GFX_GAGPR18_OFFS               0x000000C8
#define GFX_GAGPR19_OFFS               0x000000CC
#define GFX_GAGPR20_OFFS               0x000000D0
#define GFX_GAGPR21_OFFS               0x000000D4
#define GFX_GAGPR22_OFFS               0x000000D8
#define GFX_GAGPR23_OFFS               0x000000DC
#define GFX_GAGPR24_OFFS               0x000000E0
#define GFX_GAGPR25_OFFS               0x000000E4
#define GFX_GAGPR26_OFFS               0x000000E8
#define GFX_GAGPR27_OFFS               0x000000EC
#define GFX_GAGPR28_OFFS               0x000000F0
#define GFX_GAGPR29_OFFS               0x000000F4
#define GFX_GAGPR30_OFFS               0x000000F8
#define GFX_GAGPR31_OFFS               0x000000FC
#define GFX_GACMDL_OFFS                0x00000100
#define GFX_GACMDH_OFFS                0x00000104
#define GFX_DEFC0_OFFS                 0x00000200
#define GFX_DEFC1_OFFS                 0x00000204
#define GFX_DEFC2_OFFS                 0x00000208
#define GFX_DEFC3_OFFS                 0x0000020C
#define GFX_DEFC4_OFFS                 0x00000210
#define GFX_DEFC5_OFFS                 0x00000214
#define GFX_DEFC6_OFFS                 0x00000218
#define GFX_DEFC7_OFFS                 0x0000021C
#define GFX_DEFC8_OFFS                 0x00000220
#define GFX_DEFC9_OFFS                 0x00000224
#define GFX_DEFC10_OFFS                0x00000228
#define GFX_DEFC11_OFFS                0x0000022C
#define GFX_DEFC12_OFFS                0x00000230
#define GFX_DEFC13_OFFS                0x00000234
#define GFX_DEFC14_OFFS                0x00000238
#define GFX_DEFC15_OFFS                0x0000023C
#define GFX_DEFC16_OFFS                0x00000240
#define GFX_DEFC17_OFFS                0x00000244
#define GFX_DEFC18_OFFS                0x00000248
#define GFX_DEFC19_OFFS                0x0000024C
#define GFX_DEFC20_OFFS                0x00000250
#define GFX_DEFC21_OFFS                0x00000254
#define GFX_DEFC22_OFFS                0x00000258
#define GFX_DEFC23_OFFS                0x0000025C
#define GFX_DEFC24_OFFS                0x00000260
#define GFX_DEFC25_OFFS                0x00000264
#define GFX_DEFC26_OFFS                0x00000268
#define GFX_DEFC27_OFFS                0x0000026C
#define GFX_DEFC28_OFFS                0x00000270
#define GFX_DEFC29_OFFS                0x00000274
#define GFX_DEFC30_OFFS                0x00000278
#define GFX_DEFC31_OFFS                0x0000027C
#define GFX_DEFC32_OFFS                0x00000280
#define GFX_DEFC33_OFFS                0x00000284
#define GFX_DEFC34_OFFS                0x00000288
#define GFX_DEFC35_OFFS                0x0000028C
#define GFX_DEFC36_OFFS                0x00000290
#define GFX_DEFC37_OFFS                0x00000294
#define GFX_DEFC38_OFFS                0x00000298
#define GFX_DEFC39_OFFS                0x0000029C
#define GFX_DEFC40_OFFS                0x000002A0
#define GFX_DEFC41_OFFS                0x000002A4
#define GFX_DEFC42_OFFS                0x000002A8
#define GFX_DEFC43_OFFS                0x000002AC
#define GFX_DEFC44_OFFS                0x000002B0
#define GFX_DEFC45_OFFS                0x000002B4
#define GFX_DEFC46_OFFS                0x000002B8
#define GFX_DEFC47_OFFS                0x000002BC
#define GFX_DEFC48_OFFS                0x000002C0
#define GFX_DEFC49_OFFS                0x000002C4
#define GFX_DEFC50_OFFS                0x000002C8
#define GFX_DEFC51_OFFS                0x000002CC
#define GFX_DEFC52_OFFS                0x000002D0
#define GFX_DEFC53_OFFS                0x000002D4
#define GFX_DEFC54_OFFS                0x000002D8
#define GFX_DEFC55_OFFS                0x000002DC
#define GFX_DEFC56_OFFS                0x000002E0
#define GFX_DEFC57_OFFS                0x000002E4
#define GFX_DEFC58_OFFS                0x000002E8
#define GFX_DEFC59_OFFS                0x000002EC
#define GFX_DEFC60_OFFS                0x000002F0
#define GFX_DEFC61_OFFS                0x000002F4
#define GFX_DEFC62_OFFS                0x000002F8
#define GFX_DEFC63_OFFS                0x000002FC

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GFX_OFFS_DEF_H */
