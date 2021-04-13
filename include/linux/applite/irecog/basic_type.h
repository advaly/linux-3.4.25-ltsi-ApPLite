/*
 * linux/include/linux/applite/basic_types.h
 *
 * (C) Copyright TOSHIBA Corporation
 * Semiconductor & Storage Products Company 2012
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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#ifndef __BASIC_TYPE_H_
#define __BASIC_TYPE_H_

typedef void VOID;

typedef signed char SCHAR;	/* 8bit */
typedef unsigned char UCHAR;

typedef signed short SSHORT;	/* 16bit */
typedef unsigned short USHORT;

typedef signed int SINT;	/* 32bit */
typedef unsigned int UINT;

typedef signed long long SLL;	/* 64bit */
typedef unsigned long long ULL;

typedef float FLOAT;		/* 32bit single precision */
typedef double DOUBLE;		/* 64bit double precision */

typedef UCHAR REG_8;		/* packed 8bit data only for regiser */
typedef USHORT REG_16;		/* packed 16bit data only for regiser */
typedef UINT REG_32;		/* packed 32bit data only for regiser */

typedef signed long SLONG;	/* 32bit only for compatibility */
typedef unsigned long ULONG;	/* 32bit only for compatibility */

/**
 * @todo Append If Needed
 * (for example__pack short ..)
 *
 */

#endif /* __BASIC_TYPE_H_ */
