/*
 * linux/drivers/staging/applite/ma/applitema_core.c
 *
 * (C) Copyright TOSHIBA Corporation
 * Semiconductor & Storage Products Company 2012
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software FoundaTion; either version 2 of the License, or
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
#include <linux/dma-buf.h>
#include <linux/module.h>
#include <linux/scatterlist.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/dma-mapping.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/poll.h>
#include <linux/platform_device.h>
#include <asm/cacheflush.h>
#include <linux/applite/applitema.h>
#include "applitema_vmops.h"

static int applitema_open(struct inode *inode, struct file *filp);
static int applitema_release(struct inode *inode, struct file *filp);
static long applitema_ioctl(struct file *filp,
			 unsigned int cmd, unsigned long arg);

static const struct file_operations applitema_fops = {
	.owner		= THIS_MODULE,
	.unlocked_ioctl	= applitema_ioctl,
	.open		= applitema_open,
	.release	= applitema_release,
};

static struct miscdevice applitema_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "applitema",
	.fops = &applitema_fops,
};

struct applitema_buf {
	struct device *dev;
	void *vaddr;
	size_t size;
	unsigned int memtype;
	dma_addr_t dma_addr;
	atomic_t refcount;
	struct sg_table *sgt_base;
	struct applitema_vmarea_handler handler;
};

static void applitema_buf_free(void *buf_priv)
{
	struct applitema_buf *buf = buf_priv;

	if (!atomic_dec_and_test(&buf->refcount))
		return;

	if (buf->sgt_base) {
		sg_free_table(buf->sgt_base);
		kfree(buf->sgt_base);
	}

	dma_free_coherent(buf->dev, buf->size, buf->vaddr, buf->dma_addr);
	kfree(buf);
	printk(KERN_DEBUG "%s: buffer released\n", __func__); /* debug */
}

static struct applitema_buf *applitema_buf_alloc(size_t size, unsigned int memtype)
{
	struct applitema_buf *buf;
	struct device *dev = applitema_dev.parent; /* use platform_device->dev */

	buf = kzalloc(sizeof(*buf), GFP_KERNEL);
	if (!buf)
		return ERR_PTR(-ENOMEM);

	/* allocate DMA buffer */
	buf->vaddr = dma_alloc_coherent(NULL, size, &buf->dma_addr, GFP_KERNEL);
	if (!buf->vaddr) {
		kfree(buf);
		return ERR_PTR(-ENOMEM);
	}

	buf->dev = dev;
	buf->size = size;
	buf->memtype = memtype;
	buf->handler.refcount = &buf->refcount;
	buf->handler.put = applitema_buf_free;
	buf->handler.arg = buf;

	atomic_inc(&buf->refcount);

	printk(KERN_DEBUG "%s: buffer allocated (dma_addr = 0x%x)\n",
	       __func__, buf->dma_addr); /* debug */
	return buf;
}

struct applitema_attachment {
	struct sg_table sgt;
	enum dma_data_direction dir;
};

static int applitema_dmabuf_ops_attach(struct dma_buf *dbuf, struct device *dev,
	struct dma_buf_attachment *dbuf_attach)
{
	struct applitema_attachment *attach;
	unsigned int i;
	struct scatterlist *rd, *wr;
	struct sg_table *sgt;
	struct applitema_buf *buf = dbuf->priv;
	int ret;

	attach = kzalloc(sizeof(*attach), GFP_KERNEL);
	if (!attach)
		return -ENOMEM;

	sgt = &attach->sgt;
	/* Copy the buf->base_sgt scatter list to the attachment, as we can't
	 * map the same scatter list to multiple attachments at the same time.
	 */
	ret = sg_alloc_table(sgt, buf->sgt_base->orig_nents, GFP_KERNEL);
	if (ret) {
		kfree(attach);
		return -ENOMEM;
	}

	rd = buf->sgt_base->sgl;
	wr = sgt->sgl;
	for (i = 0; i < sgt->orig_nents; ++i) {
		sg_set_page(wr, sg_page(rd), rd->length, rd->offset);
		rd = sg_next(rd);
		wr = sg_next(wr);
	}

	attach->dir = DMA_NONE;
	dbuf_attach->priv = attach;

	return 0;
}

static void applitema_dmabuf_ops_detach(struct dma_buf *dbuf,
	struct dma_buf_attachment *db_attach)
{
	struct applitema_attachment *attach = db_attach->priv;
	struct sg_table *sgt;

	DEFINE_DMA_ATTRS(attrs);
	dma_set_attr(DMA_ATTR_SKIP_CPU_SYNC, &attrs);

	if (!attach)
		return;

	sgt = &attach->sgt;

	/* release the scatterlist cache */
	if (attach->dir != DMA_NONE) {
		dma_unmap_sg_attrs(db_attach->dev, sgt->sgl, sgt->orig_nents,
				   attach->dir, &attrs);
	}
	sg_free_table(sgt);
	kfree(attach);
	db_attach->priv = NULL;
}

static struct sg_table *applitema_dmabuf_ops_map(
	struct dma_buf_attachment *db_attach, enum dma_data_direction dir)
{
	struct applitema_attachment *attach = db_attach->priv;
	/* stealing dmabuf mutex to serialize map/unmap operations */
	struct mutex *lock = &db_attach->dmabuf->lock;
	struct sg_table *sgt;
	int ret;

	DEFINE_DMA_ATTRS(attrs);
	dma_set_attr(DMA_ATTR_SKIP_CPU_SYNC, &attrs);

	mutex_lock(lock);

	sgt = &attach->sgt;
	/* return previously mapped sg table */
	if (attach->dir == dir) {
		mutex_unlock(lock);
		return sgt;
	}

	/* release any previous cache */
	if (attach->dir != DMA_NONE) {
		dma_unmap_sg(db_attach->dev, sgt->sgl, sgt->orig_nents,
			attach->dir);
		attach->dir = DMA_NONE;
	}

	/* mapping to the client with new direction */
	ret = dma_map_sg_attrs(db_attach->dev, sgt->sgl, sgt->orig_nents,
			       dir, &attrs);
	if (ret <= 0) {
		pr_err("failed to map scatterlist\n");
		mutex_unlock(lock);
		return ERR_PTR(-EIO);
	}

	attach->dir = dir;

	mutex_unlock(lock);

	return sgt;
}

static void applitema_dmabuf_ops_unmap(struct dma_buf_attachment *db_attach,
	struct sg_table *sgt, enum dma_data_direction dir)
{
	/* nothing to be done here */
}

static void *applitema_dmabuf_ops_kmap(struct dma_buf *dbuf, unsigned long pgnum)
{
	struct applitema_buf *buf = dbuf->priv;

	return buf->vaddr + pgnum * PAGE_SIZE;
}

static const unsigned int pte_memtype[] = {
	L_PTE_MT_DEV_SHARED,	/* MT_DEVICE */
	L_PTE_MT_WRITEALLOC,	/* MT_WRITEALLOC */
	L_PTE_MT_BUFFERABLE,	/* MT_BUFFERABLE */
	L_PTE_MT_WRITETHROUGH,	/* MT_WRITETHROUGH */
	L_PTE_MT_WRITEBACK,	/* MT_WRITEBACK */
	L_PTE_MT_UNCACHED,	/* MT_STRONGLY_ORDERED */
};

static int applitema_dma_mmap(struct device *dev, struct vm_area_struct *vma,
			   void *cpu_addr, dma_addr_t dma_addr, size_t size,
			   unsigned int memtype)
{
	int ret = -ENXIO;
	unsigned long nr_vma_pages = (vma->vm_end - vma->vm_start) >> PAGE_SHIFT;
	unsigned long nr_pages = PAGE_ALIGN(size) >> PAGE_SHIFT;
	unsigned long pfn = dma_to_pfn(dev, dma_addr);
	unsigned long off = vma->vm_pgoff;

	vma->vm_page_prot =
		__pgprot((pgprot_val(vma->vm_page_prot) & ~L_PTE_MT_MASK) |
			 pte_memtype[memtype]);

	if (dma_mmap_from_coherent(dev, vma, cpu_addr, size, &ret))
		return ret;

	if (off < nr_pages && nr_vma_pages <= (nr_pages - off)) {
		ret = remap_pfn_range(vma, vma->vm_start,
				      pfn + off,
				      vma->vm_end - vma->vm_start,
				      vma->vm_page_prot);
	}

	return ret;
}


static int applitema_dmabuf_ops_mmap(struct dma_buf *dbuf,
	struct vm_area_struct *vma)
{
	struct applitema_buf *buf = dbuf->priv;
	unsigned long size = vma->vm_end - vma->vm_start;
	int ret;

	if (!buf) {
		printk(KERN_ERR "No buffer to map\n");
		return -EINVAL;
	}

	if (size != buf->size || vma->vm_pgoff != 0) {
		printk(KERN_ERR "partial mapping is not supported\n");
		return -EINVAL;
	}

	ret = applitema_dma_mmap(buf->dev, vma, buf->vaddr, buf->dma_addr,
			      size, buf->memtype);
	if (ret) {
		pr_err("Remapping memory failed, error: %d\n", ret);
		return ret;
	}

	vma->vm_flags		|= VM_DONTEXPAND | VM_RESERVED;
	vma->vm_private_data	= &buf->handler;
	vma->vm_ops		= &applitema_common_vm_ops;

	vma->vm_ops->open(vma);

	pr_debug("%s: mapped dma addr 0x%08lx at 0x%08lx, size %d\n",
		__func__, (unsigned long)buf->dma_addr, vma->vm_start,
		buf->size);

	return 0;
}

static void applitema_dmabuf_ops_release(struct dma_buf *dbuf)
{
	applitema_buf_free(dbuf->priv);
}

static struct dma_buf_ops applitema_dmabuf_ops = {
	.attach = applitema_dmabuf_ops_attach,
	.detach = applitema_dmabuf_ops_detach,
	.map_dma_buf = applitema_dmabuf_ops_map,
	.unmap_dma_buf = applitema_dmabuf_ops_unmap,
	.kmap = applitema_dmabuf_ops_kmap,
	.kmap_atomic = applitema_dmabuf_ops_kmap,
	.mmap = applitema_dmabuf_ops_mmap,
	.release = applitema_dmabuf_ops_release,
};

static struct sg_table *applitema_get_base_sgt(struct applitema_buf *buf)
{
	int ret;
	struct sg_table *sgt;

	DEFINE_DMA_ATTRS(attrs);
	dma_set_attr(DMA_ATTR_SKIP_CPU_SYNC, &attrs);

	sgt = kmalloc(sizeof(*sgt), GFP_KERNEL);
	if (!sgt) {
		dev_err(buf->dev, "failed to alloc sg table\n");
		return NULL;
	}

	ret = dma_get_sgtable_attrs(buf->dev, sgt, buf->vaddr, buf->dma_addr,
				    buf->size, &attrs);
	if (ret < 0) {
		dev_err(buf->dev, "failed to get scatterlist from DMA API\n");
		kfree(sgt);
		return NULL;
	}

	return sgt;
}

static int applitema_ioc_alloc(struct applitema_alloc *alloc_data)
{
	size_t size = alloc_data->size;
	unsigned int align = alloc_data->align;
	int flags = alloc_data->flags;
	unsigned int memtype = alloc_data->memtype;
	int *fd = &alloc_data->fd;
	struct applitema_buf *buf;
	struct dma_buf *dbuf;
	int ret;

	if (memtype >= APPLITEMA_MT_MAX)
		return -EINVAL;

	/* align image size to PAGE_SIZE */
	size = PAGE_ALIGN(size);
	pr_debug("%s: size %d\n", __func__, size);

	/* check align (limitation of dma_alloc_coherent) */
	/*   In dma_alloc_coherent, get_order(size) is used to allocate */
	if (align > get_order(size) + PAGE_SHIFT) {
		printk(KERN_ERR "%s: unsupported align (%d)\n", __func__, align);
		return -EINVAL;
	}

	buf = applitema_buf_alloc(size, memtype);
	if (IS_ERR(buf))
		return PTR_ERR(buf);

	if (!buf->sgt_base)
		buf->sgt_base = applitema_get_base_sgt(buf);

	dbuf = dma_buf_export(buf, &applitema_dmabuf_ops, buf->size, O_RDWR);

	if (IS_ERR(dbuf)) {
		applitema_buf_free(buf);
		return -EINVAL;
	}

	ret = dma_buf_fd(dbuf, flags);
	if (ret < 0) {
		dma_buf_put(dbuf); /* applitema_buf_free() is called internally */
		return ret;
	}

	*fd = ret;
	return 0;
}

static int applitema_ioc_cache_range(unsigned int cmd,
				  struct applitema_range *range_data)
{
	int fd = range_data->fd;
	unsigned long vaddr = range_data->vaddr;
	size_t size = range_data->size;
	int ret;
	struct vm_area_struct *vma;
	struct dma_buf *dbuf;
	struct applitema_buf *buf;
	unsigned long pfn, buf_pfn, paddr, buf_paddr;

	dbuf = dma_buf_get(fd);
	if (IS_ERR(dbuf)) {
		printk(KERN_ERR "%s: invalid dmabuf fd\n", __func__);
		return PTR_ERR(dbuf);
	}
	buf = dbuf->priv;
	buf_pfn = dma_to_pfn(buf->dev, buf->dma_addr);
	buf_paddr = buf_pfn << PAGE_SHIFT;

	down_read(&current->mm->mmap_sem);
	vma = find_vma(current->mm, vaddr);
	if (!vma) {
		printk(KERN_ERR "%s: invalid vaddr (vma not found)\n", __func__);
		ret = -EINVAL;
		goto end;
	}

	if ((vma->vm_end < vaddr + size) || (buf->size < size)) {
		printk(KERN_ERR "%s: size is too large\n", __func__);
		ret = -EINVAL;
		goto end;
	}

	ret = follow_pfn(vma, vaddr, &pfn);
	if (ret) {
		printk(KERN_ERR "%s: invalid vaddr (pfn not found)\n", __func__);
		goto end;
	}
	paddr = (pfn << PAGE_SHIFT) + (vaddr & ~PAGE_MASK);

	/* check paddr match */
	if ((paddr < buf_paddr) ||
	    ((buf_paddr + buf->size) < (paddr + size))) {
		printk(KERN_ERR "%s: paddr not match\n", __func__);
		ret = -EINVAL;
		goto end;
	}

	/* cache operation */
	switch (cmd) {
	case IOC_APPLITEMA_CACHE_CLEAN:
		dmac_map_area((void *)vaddr, size, DMA_TO_DEVICE);
		outer_clean_range(paddr, paddr + size);
		break;
	case IOC_APPLITEMA_CACHE_INV:
		outer_inv_range(paddr, paddr + size);
		dmac_unmap_area((void *)vaddr, size, DMA_FROM_DEVICE);
		break;
	case IOC_APPLITEMA_CACHE_FLUSH:
		dmac_flush_range((void *)vaddr, (void *)vaddr + size);
		outer_flush_range(paddr, paddr + size);
		break;
	default:
		printk(KERN_ERR "%s: invalid cmd (0x%x)\n", __func__, cmd);
		ret = -EINVAL;
	}

 end:
	up_read(&current->mm->mmap_sem);

	dma_buf_put(dbuf);

	return ret;
}

static long applitema_ioctl(struct file *filp,
			 unsigned int cmd, unsigned long arg)
{
	int ret;

	switch (cmd) {
	case IOC_APPLITEMA_ALLOC:
	{
		struct applitema_alloc alloc_data;
		if (copy_from_user(&alloc_data, (void __user *)arg,
				   sizeof(alloc_data)))
			return -EFAULT;

		ret = applitema_ioc_alloc(&alloc_data);
		if (ret != 0)
			return ret;

		if (copy_to_user((void __user *)arg, (void *)&alloc_data,
				 sizeof(alloc_data)))
			return -EFAULT;

		return 0;
	}
	case IOC_APPLITEMA_CACHE_CLEAN:
	case IOC_APPLITEMA_CACHE_INV:
	case IOC_APPLITEMA_CACHE_FLUSH:
	{
		struct applitema_range range_data;
		if (copy_from_user(&range_data, (void __user *)arg,
				   sizeof(range_data)))
			return -EFAULT;

		return applitema_ioc_cache_range(cmd, &range_data);
	}
	default:
		printk(KERN_ERR "%s: invalid cmd (0x%x)\n", __func__, cmd);
		return -EINVAL;
	}
}

static int applitema_open(struct inode *inode, struct file *filp)
{
	printk(KERN_DEBUG "%s\n", __func__);
	return 0;
}

static int applitema_release(struct inode *inode, struct file *filp)
{
	printk(KERN_DEBUG "%s\n", __func__);
	return 0;
}

static int __devinit applitema_probe(struct platform_device *pdev)
{
	int ret;

	applitema_dev.parent = &pdev->dev;

	ret = misc_register(&applitema_dev);
	if (ret) {
		printk(KERN_ERR "fail to misc_register (MISC_DYNAMIC_MINOR)\n");
		return ret;
	}

	return 0;
}

static int __devexit applitema_remove(struct platform_device *pdev)
{
	misc_deregister(&applitema_dev);
	return 0;
}

static struct platform_driver applitema_driver = {
	.probe = applitema_probe,
	.remove = applitema_remove,
	.driver = {
		.name = "applitema",
		.owner = THIS_MODULE,
	},
};

static int __init applitema_init(void)
{
	int ret;

	ret = platform_driver_register(&applitema_driver);
	if (ret) {
		printk(KERN_ERR "fail to platform_driver_register\n");
		return ret;
	}

	printk(KERN_DEBUG "%s: Succefully loaded.\n", __func__);
	return 0;
}

static void __exit applitema_cleanup(void)
{
	platform_driver_unregister(&applitema_driver);

	printk(KERN_DEBUG "%s: Unloaded.\n", __func__);
}

MODULE_LICENSE("GPL");
module_init(applitema_init);
module_exit(applitema_cleanup);
