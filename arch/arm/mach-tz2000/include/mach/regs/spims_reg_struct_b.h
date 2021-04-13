/*
 * arch/arm/mach-tz2000/include/mach/regs/spims_reg_struct_b.h
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

#ifndef _SPIMS_REG_STRUCT_B_H
#define _SPIMS_REG_STRUCT_B_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // SPI_RXDATA0 Register
struct SPIMS_SPI_RXDATA0 {
	unsigned int RXDATA:32;		// [31:0]
};
 // SPI_TXDATA0 Register
struct SPIMS_SPI_TXDATA0 {
	unsigned int TXDATA:32;		// [31:0]
};
 // SPI_SELECT0 Register
struct SPIMS_SPI_SELECT0 {
	unsigned int reserved:14;		// [31:18]
	unsigned int CPOL:1;		// [17]
	unsigned int CPHA:1;		// [16]
	unsigned int reserved2:15;		// [15:1]
	unsigned int MASTER:1;		// [0]
};
 // SPI_DIV0 Register
struct SPIMS_SPI_DIV0 {
	unsigned int DUMMY:1;		// [31]
	unsigned int reserved:28;		// [30:3]
	unsigned int SCALE:3;		// [2:0]
};
 // SPI_ENABLE0 Register
struct SPIMS_SPI_ENABLE0 {
	unsigned int reserved:31;		// [31:1]
	unsigned int ENABLE:1;		// [0]
};
 // SPI_FRAME0 Register
struct SPIMS_SPI_FRAME0 {
	unsigned int MODE:1;		// [31]
	unsigned int reserved:13;		// [30:18]
	unsigned int SCS:1;		// [17]
	unsigned int SCK:1;		// [16]
	unsigned int reserved2:6;		// [15:10]
	unsigned int SCSHOLD:1;		// [9]
	unsigned int MSB:1;		// [8]
	unsigned int reserved3:3;		// [7:5]
	unsigned int LENGTH:5;		// [4:0]
};
 // SPI_FIFOCLR0 Register
struct SPIMS_SPI_FIFOCLR0 {
	unsigned int reserved:30;		// [31:2]
	unsigned int RXFIFOINIT:1;		// [1]
	unsigned int TXFIFOINIT:1;		// [0]
};
 // SPI_IC0 Register
struct SPIMS_SPI_IC0 {
	unsigned int reserved:24;		// [31:8]
	unsigned int FIFOCOND:8;		// [7:0]
};
 // SPI_IE0 Register
struct SPIMS_SPI_IE0 {
	unsigned int reserved:20;		// [31:12]
	unsigned int TXOVFINTENB:1;		// [11]
	unsigned int TXUDFINTENB:1;		// [10]
	unsigned int RXOVFINTENB:1;		// [9]
	unsigned int RXUDFINTENB:1;		// [8]
	unsigned int reserved2:7;		// [7:1]
	unsigned int INTENB:1;		// [0]
};
 // SPI_IS0 Register
struct SPIMS_SPI_IS0 {
	unsigned int reserved:20;		// [31:12]
	unsigned int TXOVFINTSTATUS:1;		// [11]
	unsigned int TXUDFINTSTATUS:1;		// [10]
	unsigned int RXOVFINTSTATUS:1;		// [9]
	unsigned int RXUDFINTSTATUS:1;		// [8]
	unsigned int reserved2:7;		// [7:1]
	unsigned int INTSTATUS:1;		// [0]
};
 // SPI_RXFIFONMB0 Register
struct SPIMS_SPI_RXFIFONMB0 {
	unsigned int reserved:24;		// [31:8]
	unsigned int NUMBER:8;		// [7:0]
};
 // SPI_TXFIFONMB0 Register
struct SPIMS_SPI_TXFIFONMB0 {
	unsigned int reserved:24;		// [31:8]
	unsigned int NUMBER:8;		// [7:0]
};
 // SPI_RXDATA1 Register
struct SPIMS_SPI_RXDATA1 {
	unsigned int RXDATA:32;		// [31:0]
};
 // SPI_TXDATA1 Register
struct SPIMS_SPI_TXDATA1 {
	unsigned int TXDATA:32;		// [31:0]
};
 // SPI_SELECT1 Register
struct SPIMS_SPI_SELECT1 {
	unsigned int reserved:14;		// [31:18]
	unsigned int CPOL:1;		// [17]
	unsigned int CPHA:1;		// [16]
	unsigned int reserved2:15;		// [15:1]
	unsigned int MASTER:1;		// [0]
};
 // SPI_DIV1 Register
struct SPIMS_SPI_DIV1 {
	unsigned int DUMMY:1;		// [31]
	unsigned int reserved:28;		// [30:3]
	unsigned int SCALE:3;		// [2:0]
};
 // SPI_ENABLE1 Register
struct SPIMS_SPI_ENABLE1 {
	unsigned int reserved:31;		// [31:1]
	unsigned int ENABLE:1;		// [0]
};
 // SPI_FRAME1 Register
struct SPIMS_SPI_FRAME1 {
	unsigned int MODE:1;		// [31]
	unsigned int reserved:13;		// [30:18]
	unsigned int SCS:1;		// [17]
	unsigned int SCK:1;		// [16]
	unsigned int reserved2:6;		// [15:10]
	unsigned int SCSHOLD:1;		// [9]
	unsigned int MSB:1;		// [8]
	unsigned int reserved3:3;		// [7:5]
	unsigned int LENGTH:5;		// [4:0]
};
 // SPI_FIFOCLR1 Register
struct SPIMS_SPI_FIFOCLR1 {
	unsigned int reserved:30;		// [31:2]
	unsigned int RXFIFOINIT:1;		// [1]
	unsigned int TXFIFOINIT:1;		// [0]
};
 // SPI_IC1 Register
struct SPIMS_SPI_IC1 {
	unsigned int reserved:24;		// [31:8]
	unsigned int FIFOCOND:8;		// [7:0]
};
 // SPI_IE1 Register
struct SPIMS_SPI_IE1 {
	unsigned int reserved:20;		// [31:12]
	unsigned int TXOVFINTENB:1;		// [11]
	unsigned int TXUDFINTENB:1;		// [10]
	unsigned int RXOVFINTENB:1;		// [9]
	unsigned int RXUDFINTENB:1;		// [8]
	unsigned int reserved2:7;		// [7:1]
	unsigned int INTENB:1;		// [0]
};
 // SPI_IS1 Register
struct SPIMS_SPI_IS1 {
	unsigned int reserved:20;		// [31:12]
	unsigned int TXOVFINTSTATUS:1;		// [11]
	unsigned int TXUDFINTSTATUS:1;		// [10]
	unsigned int RXOVFINTSTATUS:1;		// [9]
	unsigned int RXUDFINTSTATUS:1;		// [8]
	unsigned int reserved2:7;		// [7:1]
	unsigned int INTSTATUS:1;		// [0]
};
 // SPI_RXFIFONMB1 Register
struct SPIMS_SPI_RXFIFONMB1 {
	unsigned int reserved:24;		// [31:8]
	unsigned int NUMBER:8;		// [7:0]
};
 // SPI_TXFIFONMB1 Register
struct SPIMS_SPI_TXFIFONMB1 {
	unsigned int reserved:24;		// [31:8]
	unsigned int NUMBER:8;		// [7:0]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SPIMS_REG_STRUCT_B_H */
