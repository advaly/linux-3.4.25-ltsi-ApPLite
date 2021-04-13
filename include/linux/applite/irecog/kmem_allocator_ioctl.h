/*
 * linux/include/linux/applite/kmem_allocator_ioctl.h
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
#ifndef __KMEM_ALLOCATOR_IOCTL_H__
#define __KMEM_ALLOCATOR_IOCTL_H__

#include <linux/ioctl.h>

typedef struct {
	unsigned long start_addr_phys;
	unsigned long size;
} kmem_allocator_cache_t;

#define PMU_CLOCK_LOW  0
#define PMU_CLOCK_HIGH 1

#define KMEM_ALLOCATOR_IOCTL_MAGIC  0xBC
#define KMEM_ALLOCATOR_IOCTL_GET_PHY_ADDR     _IOR(KMEM_ALLOCATOR_IOCTL_MAGIC, 0x0, unsigned long)
#define KMEM_ALLOCATOR_IOCTL_INIT_IRECOG      _IOW(KMEM_ALLOCATOR_IOCTL_MAGIC, 0x1, unsigned long)
#define KMEM_ALLOCATOR_IOCTL_CACHE_FLUSH      _IO(KMEM_ALLOCATOR_IOCTL_MAGIC, 0x2)
#define KMEM_ALLOCATOR_IOCTL_CACHE_INVALIDATE _IOW(KMEM_ALLOCATOR_IOCTL_MAGIC, 0x3, kmem_allocator_cache_t)

#endif /*  __KMEM_ALLOCATOR_IOCTL_H__ */
