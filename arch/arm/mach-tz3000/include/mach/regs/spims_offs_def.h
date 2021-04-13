/*
 * arch/arm/mach-tz3000/include/mach/regs/spims_offs_def.h
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

#ifndef SPIMS_OFFS_DEF_H
#define SPIMS_OFFS_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

#define SPIMS_SPI_RXDATA0_OFFS         0x00000000
#define SPIMS_SPI_TXDATA0_OFFS         0x00000004
#define SPIMS_SPI_SELECT0_OFFS         0x00000008
#define SPIMS_SPI_DIV0_OFFS            0x0000000C
#define SPIMS_SPI_ENABLE0_OFFS         0x00000010
#define SPIMS_SPI_FRAME0_OFFS          0x00000014
#define SPIMS_SPI_FIFOCLR0_OFFS        0x00000018
#define SPIMS_SPI_IC0_OFFS             0x0000001C
#define SPIMS_SPI_IE0_OFFS             0x00000020
#define SPIMS_SPI_IS0_OFFS             0x00000024
#define SPIMS_SPI_RXFIFONMB0_OFFS      0x00000028
#define SPIMS_SPI_TXFIFONMB0_OFFS      0x0000002C
#define SPIMS_SPI_RXDATA1_OFFS         0x00010000
#define SPIMS_SPI_TXDATA1_OFFS         0x00010004
#define SPIMS_SPI_SELECT1_OFFS         0x00010008
#define SPIMS_SPI_DIV1_OFFS            0x0001000C
#define SPIMS_SPI_ENABLE1_OFFS         0x00010010
#define SPIMS_SPI_FRAME1_OFFS          0x00010014
#define SPIMS_SPI_FIFOCLR1_OFFS        0x00010018
#define SPIMS_SPI_IC1_OFFS             0x0001001C
#define SPIMS_SPI_IE1_OFFS             0x00010020
#define SPIMS_SPI_IS1_OFFS             0x00010024
#define SPIMS_SPI_RXFIFONMB1_OFFS      0x00010028
#define SPIMS_SPI_TXFIFONMB1_OFFS      0x0001002C

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SPIMS_OFFS_DEF_H */
