
#ifndef MIRAGELITE_H
#define MIRAGELITE_H

#include <linux/types.h>
#include <linux/ioctl.h>

#define CN_USER_MISC_MINOR		244
#define MAJOR_NUM CN_USER_MISC_MINOR

#define IOC_TYPE_CN			0xcf

#define IOCTL_INTDRV_INTSET		_IO(IOC_TYPE_CN, 0x01)
#define IOCTL_INTDRV_INTUNSET		_IO(IOC_TYPE_CN, 0x02)
#define IOCTL_INTDRV_INTWAIT		_IO(IOC_TYPE_CN, 0x03)
#define IOCTL_INTDRV_INTENABLE		_IO(IOC_TYPE_CN, 0x04)
#define IOCTL_INTDRV_INTDISABLE		_IO(IOC_TYPE_CN, 0x05)
#define IOCTL_INTDRV_CANCEL		_IO(IOC_TYPE_CN, 0x06)
#define IOCTL_INTDRV_GET_COUNT		_IO(IOC_TYPE_CN, 0x08)
#define IOCTL_INTDRV_GET_INTRBITMAP	_IO(IOC_TYPE_CN, 0x11)
#define IOCTL_INTDRV_GET_CREGS		_IO(IOC_TYPE_CN, 0x13)
#define IOCTL_INTDRV_CLR_CREGS		_IO(IOC_TYPE_CN, 0x14)

#define IOCTL_GET_PHYSADDR		_IO(IOC_TYPE_CN, 0x20)
#define IOCTL_CACHE_CLEAN		_IO(IOC_TYPE_CN, 0x21)
#define IOCTL_CACHE_INV			_IO(IOC_TYPE_CN, 0x22)
#define IOCTL_CACHE_FLUSH		_IO(IOC_TYPE_CN, 0x23)
#define IOCTL_CACHE_FLUSH_ALL		_IO(IOC_TYPE_CN, 0x27)

#define IOCTL_REGPHYS			_IO(IOC_TYPE_CN, 0x30)

#define MAX_CN_USER_MMAP		32
#define MAX_CN_USER_IRQ			32

struct cn_irqdata {
	char name[8];
	int irq;
	int nl_group;
	unsigned long baseaddr;
	unsigned long cause_offset;
	unsigned long clear_offset;
	unsigned long skipaddr;
	int regnum;
	unsigned long flags;
#define CN_USER_KEEP_DISABLE		0x00010000
#define CN_USER_BYTE_SWAP		0x10000000
};

struct cn_cause {
	__u32 cause[32];
	int count;		/* number of register */
	int irq;		/* irq */
	long pid;
};

struct cn_user_mmap {
	char name[8];		/* name */
	unsigned long physaddr;	/* physical address */
	unsigned long size;	/* size */
	unsigned long cache;	/* cache */
	unsigned long offset;	/* offset */
};

typedef struct _cn_fd_phys_map{
	int mem_fd;
	unsigned int phys;
}cn_fd_phys_map;
/*===================================
Exported Variables
===================================*/
/*===================================
Exported Functions prototypes
===================================*/
#endif /*MIRAGELITE_H */
