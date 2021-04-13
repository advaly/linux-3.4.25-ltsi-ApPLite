/*
 * linux/drivers/staging/applite/irecog/kmem_allocator/kmem_allocator_driver.c
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
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <linux/cdev.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/ioport.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/wait.h>
#include <asm/page.h>
#include <linux/sched.h>
#include <linux/semaphore.h>

#include <linux/applite/irecog/kmem_allocator_ioctl.h>

#include <mach/regs/irecog_offs_def.h>
#include <mach/regs/irecog_reg_def.h>

#include <linux/applite/irecog/drv_cmn.h>
#include "drv_defs.h"
#include "drv_cache.h"

#define KMEM_BIT(i) (1 << i)

#define DRV_KMEM_ALLOCATOR_VERSION_MAJOR        DRV_VERSION_MAJOR
#define DRV_KMEM_ALLOCATOR_VERSION_MINOR        2
#define DRV_KMEM_ALLOCATOR_VERSION_SUBMINOR     0
#define DRV_KMEM_ALLOCATOR_VERSION_STR          DRV_STR(DRV_KMEM_ALLOCATOR_VERSION_MAJOR) "." DRV_STR(DRV_KMEM_ALLOCATOR_VERSION_MINOR) "." DRV_STR(DRV_KMEM_ALLOCATOR_VERSION_SUBMINOR)

#define KMEM_ALLOCATOR_MAJOR   0	/* dynamic allocation */
#define KMEM_ALLOCATOR_MINOR   0
#define KMEM_ALLOCATOR_NR_DEVS 1
#define KMEM_ALLOCATOR_NAME    "kmem_allocator"

static int kmem_allocator_major = KMEM_ALLOCATOR_MAJOR;
static int kmem_allocator_minor = KMEM_ALLOCATOR_MINOR;
static int kmem_allocator_nr_devs = KMEM_ALLOCATOR_NR_DEVS;

module_param(kmem_allocator_major, int, S_IRUGO | S_IWUSR);
module_param(kmem_allocator_minor, int, S_IRUGO | S_IWUSR);
module_param(kmem_allocator_nr_devs, int, S_IRUGO | S_IWUSR);

static struct cdev c_dev;
static struct device *device;
static struct class *pkmem_class;

typedef struct {
	char *buf;
	unsigned long phy_addr;
	atomic_t refcount;
} memory_info;

static void kmem_allocator_allocate(memory_info *meminfo, int size);
static void kmem_allocator_free(memory_info *meminfo);

/**************************************************/
/*
 * @brief kmem_allocator_open
 *
 * @param inode
 * @param filp
 *
 * @return
 */
/**************************************************/
static int kmem_allocator_open(struct inode *inode, struct file *filp)
{
	memory_info *meminfo;

	filp->private_data = kmalloc(sizeof(memory_info), GFP_KERNEL | GFP_DMA);
	if (filp->private_data == NULL) {
		pr_err("%s: kmem_allocator open fail.\n", KMEM_ALLOCATOR_NAME);
		return 0;
	}

	meminfo = (memory_info *)filp->private_data;
	memset(meminfo, 0x00, sizeof(memory_info));

	return 0;
}

/**************************************************/
/*
 * @brief kmem_allocator_release
 *
 * @param inode
 * @param filp
 *
 * @return
 */
/**************************************************/
static int kmem_allocator_release(struct inode *inode, struct file *filp)
{
	memory_info *meminfo = filp->private_data;

	if (meminfo != NULL) {
		kmem_allocator_free(meminfo);
		kfree(filp->private_data);
		filp->private_data = NULL;
	}

	return 0;
}

/**************************************************/
/*
 * @brief kmem_allocator_allocate
 *
 * @param meminfo
 * @param size
 *
 * @return
 */
/**************************************************/
static void kmem_allocator_allocate(memory_info *meminfo, int size)
{
	char *buf;
	unsigned long offset;

	if (meminfo == NULL) {
		return;
	}

	kmem_allocator_free(meminfo);

	buf = kmalloc(size + PAGE_SIZE, GFP_KERNEL | GFP_DMA);
	if (buf == NULL) {
		goto error;
	}

	offset = (unsigned long)virt_to_phys(buf) % PAGE_SIZE;

	if (offset == 0) {
		meminfo->phy_addr = (unsigned long)virt_to_phys(buf);
	} else {
		meminfo->phy_addr =
		    (PAGE_SIZE - offset) + (unsigned long)virt_to_phys(buf);
	}

	meminfo->buf = buf;
	return;

error:
	meminfo->buf = NULL;
	meminfo->phy_addr = 0x00;
	pr_err("%s: kmalloc fail\n", KMEM_ALLOCATOR_NAME);
	return;
}

/**************************************************/
/*
 * @brief kmem_allocator_free
 *
 * @param meminfo
 *
 * @return
 */
/**************************************************/
static void kmem_allocator_free(memory_info *meminfo)
{
	if (meminfo == NULL) {
		return;
	}

	kfree(meminfo->buf);
	meminfo->buf = NULL;
}

/**************************************************/
/*
 * @brief initialize_irecog
 *
 * @param speed
 *
 * @retval 0  ok
 * @retval -1 error
 *
 */
/**************************************************/
static int initialize_irecog(unsigned long speed)
{
	return 0;
}

/**************************************************/
/*
 * @brief kmem_allocator_ioctl
 *
 * @param filp
 * @param cmd
 * @param val
 *
 * @return
 */
/**************************************************/
static long kmem_allocator_ioctl(struct file *filp, unsigned int cmd,
				 unsigned long val)
{
	long ret = 0;
	memory_info *meminfo = filp->private_data;
	unsigned long retval;

	if (meminfo == NULL) {
		return ret;
	}

	switch (cmd) {
	case KMEM_ALLOCATOR_IOCTL_GET_PHY_ADDR:
		retval = meminfo->phy_addr;
		if (copy_to_user
		    ((void __user *)val, (void *)&retval,
		     sizeof(unsigned long))) {
			return -EINVAL;
		}
		break;

	case KMEM_ALLOCATOR_IOCTL_INIT_IRECOG:

#ifndef ENABLE_SPYESIDE_SIM
		{
			unsigned long speed;

			if (copy_from_user
			    ((void *)&speed, (const void __user *)val,
			     sizeof(unsigned long))) {
				return -EINVAL;
			}
			if (initialize_irecog(speed) != 0) {
				return -EINVAL;
			}
		}
#endif
		break;

	case KMEM_ALLOCATOR_IOCTL_CACHE_FLUSH:
		drv_cache_flush_all();
		break;

	case KMEM_ALLOCATOR_IOCTL_CACHE_INVALIDATE:
		{
			kmem_allocator_cache_t cache_param;

			if (copy_from_user
			    ((void *)&cache_param, (const void __user *)val,
			     sizeof(kmem_allocator_cache_t))) {
				return -EINVAL;
			}

			drv_cache_invalidate(cache_param.start_addr_phys,
					     cache_param.size);
		}
		break;

		/* invalid command */
	default:
		pr_err("%s: invalid ioctl command %d\n",
		       KMEM_ALLOCATOR_NAME, cmd);
		return -EINVAL;
		break;
	}

	return ret;
}

/**************************************************/
/*
 * @brief kmem_allocator_vma_open
 *
 * @param vma
 *
 * @return
 */
/**************************************************/
static void kmem_allocator_vma_open(struct vm_area_struct *vma)
{
	memory_info *meminfo = vma->vm_private_data;

	atomic_inc(&meminfo->refcount);
}

/**************************************************/
/*
 * @brief kmem_allocator_vma_close
 *
 * @param vma
 *
 * @return
 */
/**************************************************/
static void kmem_allocator_vma_close(struct vm_area_struct *vma)
{
	memory_info *meminfo = vma->vm_private_data;

	if (!atomic_dec_and_test(&meminfo->refcount)) {
		return;
	}

	kmem_allocator_free(meminfo);
}

static struct vm_operations_struct kmem_allocator_vm_ops = {
	.open = kmem_allocator_vma_open,
	.close = kmem_allocator_vma_close,
};

/**************************************************/
/*
 * @brief kmem_allocator_vma_mmap
 *
 * @param file
 * @param vma
 *
 * @return
 */
/**************************************************/
static int kmem_allocator_mmap(struct file *filp, struct vm_area_struct *vma)
{
	memory_info *meminfo = filp->private_data;
	int size = vma->vm_end - vma->vm_start;

	if (meminfo->buf) {
		pr_err("%s: mmap: fail.\n", KMEM_ALLOCATOR_NAME);
		return -EBUSY;
	}

	kmem_allocator_allocate(meminfo, size);
	if (meminfo->phy_addr == 0x0) {
		pr_err("%s: mmap: fail.\n", KMEM_ALLOCATOR_NAME);
		return -EAGAIN;
	}

	if (remap_pfn_range(vma,
			    vma->vm_start,
			    meminfo->phy_addr >> PAGE_SHIFT,
			    size, vma->vm_page_prot)) {
		pr_err("%s: mmap: fail.\n", KMEM_ALLOCATOR_NAME);
		return -EAGAIN;
	}

	vma->vm_ops = &kmem_allocator_vm_ops;
	vma->vm_private_data = meminfo;

	kmem_allocator_vma_open(vma);

	return 0;
}

static const struct file_operations kmem_allocator_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = kmem_allocator_ioctl,
	.open = kmem_allocator_open,
	.mmap = kmem_allocator_mmap,
	.release = kmem_allocator_release,
};

/**************************************************/
/*
 * @brief kmem_allocator_init
 *
 * @return
 */
/**************************************************/
static int kmem_allocator_init(void)
{
	int err;
	int ret;
	dev_t dev = 0;
	dev_t devno;

	/* allocation of device number */
	if (kmem_allocator_major) {
		dev = MKDEV(kmem_allocator_major, kmem_allocator_minor);
		ret =
		    register_chrdev_region(dev, kmem_allocator_nr_devs,
					   KMEM_ALLOCATOR_NAME);
	} else {
		ret =
		    alloc_chrdev_region(&dev, kmem_allocator_minor,
					kmem_allocator_nr_devs,
					KMEM_ALLOCATOR_NAME);
		kmem_allocator_major = MAJOR(dev);
	}
	if (ret < 0) {
		pr_err("%s: can't get major %d\n",
		       KMEM_ALLOCATOR_NAME, kmem_allocator_major);
		goto fail_get_major;
	}

	devno = MKDEV(kmem_allocator_major, kmem_allocator_minor);
	cdev_init(&c_dev, &kmem_allocator_fops);
	c_dev.owner = THIS_MODULE;
	err = cdev_add(&c_dev, devno, 1);
	if (err) {
		pr_err("%s: cannot setup cdev\n", KMEM_ALLOCATOR_NAME);
	}

	/* create kmem_allocator class */
	pkmem_class = class_create(THIS_MODULE, KMEM_ALLOCATOR_NAME);
	if (IS_ERR(pkmem_class)) {
		ret = PTR_ERR(pkmem_class);
		pr_err("%s: class_create failed\n", KMEM_ALLOCATOR_NAME);
		goto fail_class_create;
	}

	/* create device structure */
	device =
	    device_create(pkmem_class, NULL, dev, NULL, KMEM_ALLOCATOR_NAME);
	if (IS_ERR(device)) {
		ret = PTR_ERR(device);
		pr_err("%s: device_create failed\n", KMEM_ALLOCATOR_NAME);
		goto fail_device_create;
	}

	pr_info("%s Driver [%s] Initialized.[%d.%d]\n",
		KMEM_ALLOCATOR_NAME,
		DRV_KMEM_ALLOCATOR_VERSION_STR, MAJOR(dev), MINOR(dev));

	return 0;

fail_device_create:
	class_destroy(pkmem_class);
fail_class_create:
	cdev_del(&c_dev);
fail_get_major:
	unregister_chrdev_region(dev, kmem_allocator_nr_devs);

	return ret;
}

/**************************************************/
/*
 * @brief kmem_allocator_exit
 *
 * @return
 */
/**************************************************/
static void kmem_allocator_exit(void)
{
	dev_t dev = MKDEV(kmem_allocator_major, kmem_allocator_minor);

	device_destroy(pkmem_class, dev);
	class_destroy(pkmem_class);

	cdev_del(&c_dev);

	unregister_chrdev_region(dev, kmem_allocator_nr_devs);

	pr_info("%s: exit\n", KMEM_ALLOCATOR_NAME);
}

module_init(kmem_allocator_init);
module_exit(kmem_allocator_exit);

MODULE_AUTHOR("TOSHIBA Corporation");
MODULE_VERSION(DRV_KMEM_ALLOCATOR_VERSION_STR);
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("kmem allocator module");
