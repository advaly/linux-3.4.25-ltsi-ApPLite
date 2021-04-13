/*
 * linux/drivers/staging/applite/ma/applitema.h
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
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#ifndef __APPLITEMA_H__
#define __APPLITEMA_H__

#define APPLITEMA_DEV_FILE	"/dev/applitema"

/* memory type (n=TEX[0],C,B)			   n   */
#define APPLITEMA_MT_DEVICE		0       /* 100 */
#define APPLITEMA_MT_WRITEALLOC		1       /* 111 */
#define APPLITEMA_MT_BUFFERABLE		2       /* 001 */
#define APPLITEMA_MT_WRITETHROUGH	3       /* 010 */
#define APPLITEMA_MT_WRITEBACK		4       /* 011 */
#define APPLITEMA_MT_STRONGLY_ORDERED	5       /* 000 */
#define APPLITEMA_MT_MAX		6

struct applitema_alloc {
	size_t size;
	unsigned int align; /* specify by exponent of power of 2 */
	int flags;
	unsigned int memtype;
	int fd;
};

struct applitema_range {
	int fd;
	unsigned long vaddr;
	size_t size;
};

#define APPLITEMA_MAGIC		's'
#define IOC_APPLITEMA_ALLOC		_IOWR(APPLITEMA_MAGIC, 0x01, struct applitema_alloc)
#define IOC_APPLITEMA_CACHE_CLEAN	_IOR(APPLITEMA_MAGIC, 0x02, struct applitema_range)
#define IOC_APPLITEMA_CACHE_INV		_IOR(APPLITEMA_MAGIC, 0x03, struct applitema_range)
#define IOC_APPLITEMA_CACHE_FLUSH	_IOR(APPLITEMA_MAGIC, 0x04, struct applitema_range)

#endif /* __APPLITEMA_H__ */
