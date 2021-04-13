/*
 * linux/drivers/staging/applite/irecog/filter/sl_error.h
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
#ifndef _SL_ERROR_H_
#define _SL_ERROR_H_

#define SL_NO_ERROR	0
#define SL_ERROR_BASE -4096

#define SL_ERROR_FAILED					(SL_ERROR_BASE -	0x0001)
#define SL_ERROR_ILLEGAL_PARAMETER		(SL_ERROR_BASE -	0x0002)
#define SL_ERROR_OUT_OF_RANGE			(SL_ERROR_BASE -	0x0003)
#define SL_ERROR_OVERFLOW				(SL_ERROR_BASE -	0x0004)
#define SL_ERROR_ILLEGAL_CODE			(SL_ERROR_BASE -	0x0005)
#define SL_ERROR_OUT_OF_PARAM			(SL_ERROR_BASE -	0x0006)
#define SL_ERROR_INIT_FAILED			(SL_ERROR_BASE -	0x0007)
#define SL_ERROR_ILLEGAL_HIF_PARAMETER	(SL_ERROR_BASE -	0x0008)
#define SL_ERROR_OUTOF_INTERNAL_RESOURCE		(SL_ERROR_BASE -	0x0009)

#endif
