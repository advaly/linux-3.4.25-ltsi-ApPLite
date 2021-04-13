#include <linux/kernel.h>	/* We're doing kernel work */
#include <linux/module.h>	/* Specifically, a module */
#include <linux/fs.h>
#include <asm/uaccess.h>	/* for get_user and put_user */

#include <asm/io.h> 			/* for ioremap */
#include <linux/module.h>		/* loading modules into kernel */
#include <linux/cdev.h>			/* for char device creation */
#include <linux/interrupt.h>	/* interrupt related functions */
#include <linux/sched.h>		/* wait queue */
#include <linux/proc_fs.h> 		/* for mmap related */
#include <asm/cacheflush.h>		/* for cache flush functions */
#include <linux/device.h>		/* for device create functions */
#include <linux/dma-buf.h>

#include <linux/platform_device.h>
#include <linux/pm_runtime.h>
#include <linux/clk.h>
#include <linux/delay.h>

#include <mach/regs/cpu_memmap_def.h>
#include <mach/regs/pmu_offs_def.h>
#include <mach/regs/pmu_reg_def.h>
#include <mach/regs/econf_offs_def.h>

#include "miragelite.h"

static void mirage_hw_init(void);
static void mirage_hw_exit(void);
static int mirage_runtime_suspend(struct device *dev);
static int mirage_runtime_resume(struct device *dev);

static dev_t dev_major; // Global variable for the device number 
static struct cdev c_dev; // Global variable for the character device structure
static struct class *cl; // Global variable for the device class
static struct device *mirage_mmap_device;
static struct clk *eastp_clk, *gpuss_clk;
static __u8 __iomem *pmubase, *econfbase, *gpubase;
static struct platform_device *mirage_pdev;
static unsigned int mirage_usecount;

#define __DEBUG

#define SUCCESS 0
#define DEVICE_NAME "cn_user"
#define BUF_LEN 80

#define MRG_ERR(fmt,...)				\
		pr_err("[%s] %s : --ERROR-- "fmt, DEVICE_NAME, __func__, ##__VA_ARGS__)

#define GPU_DMACSTATUS_OFFS 0x14
#define GPU_DMACINTMSK_OFFS 0x18

static inline void mirage_pmu_write(__u32 offset, __u32 val)
{
	__raw_writel(val, pmubase + offset);
}
static inline __u32 mirage_pmu_read(__u32 offset)
{
	return __raw_readl(pmubase + offset);
}
static inline void mirage_pmu_rewrite(__u32 offset, __u32 mask, __u32 val)
{
	__u32 tmp = mirage_pmu_read(offset);
	tmp &= ~mask;
	mirage_pmu_write(offset, (tmp | (val & mask)));
}

typedef struct cn_user_mmap cn_user_mmap_;
static cn_user_mmap_ global_map;

/* 
 * mirage_mmap_open
 */
static int mirage_mmap_open(struct inode *inode, struct file *file)
{
#ifdef DEBUG
	printk(KERN_INFO "mirage_mmap_open(%p)\n", file);
#endif

	mirage_usecount++;
#if IS_ENABLED(CONFIG_PM_RUNTIME)
	pm_runtime_get_sync(&(mirage_pdev->dev));
#else
	if (mirage_usecount == 1)
		mirage_runtime_resume(&(mirage_pdev->dev));
#endif
#ifdef DEBUG
	printk(KERN_INFO "%s:usecount=%d\n", __func__, mirage_usecount);
#endif
	try_module_get(THIS_MODULE);
	return SUCCESS;
}

/*  
 * mirage_mmap_release
 */
static int mirage_mmap_release(struct inode *inode, struct file *file)
{
#ifdef DEBUG
	printk(KERN_INFO "mirage_mmap_release(%p,%p)\n", inode, file);
#endif
	
	module_put(THIS_MODULE);
	mirage_usecount--;
#if IS_ENABLED(CONFIG_PM_RUNTIME)
	pm_runtime_put_sync(&(mirage_pdev->dev));
#else
	if (mirage_usecount == 0)
		mirage_runtime_suspend(&(mirage_pdev->dev));
#endif
#ifdef DEBUG
	printk(KERN_INFO "%s:usecount=%d\n", __func__, mirage_usecount);
#endif
	return SUCCESS;
}

/*  
 * mirage_mmap_read
 */
static ssize_t mirage_mmap_read(struct file *file,	/* see include/linux/fs.h   */
			   char __user * buffer,	/* buffer to be
							 * filled with data */
			   size_t length,	/* length of the buffer     */
			   loff_t * offset)
{
	
#ifdef DEBUG
	printk(KERN_INFO "mirage_mmap_read(%p,%p,%d)\n", file, buffer, length);
#endif

	return 0;
}

/* 
 * mirage_mmap_write
 * 
 */
static ssize_t
mirage_mmap_write(struct file *file,
	     const char __user * buffer, size_t length, loff_t * offset)
{
	
#ifdef DEBUG
	printk(KERN_INFO "mirage_mmap_write(%p,%s,%d)", file, buffer, length);
#endif

	return 0;
}

/*  
 * mirage_mmap_ioctl
 */
long mirage_mmap_ioctl(struct file *f, unsigned int cmd, unsigned long arg)
{		
	struct dma_buf *db;
	struct dma_buf_attachment *dba;
	struct sg_table *sg;
	dma_addr_t addr;	
	cn_fd_phys_map fd_phys_map;
	
#ifdef DEBUG
	printk(KERN_INFO "mirage_mmap_ioctl(%d,%x,%x)\n", (unsigned int)f, cmd, (unsigned int)arg);
#endif	
	/* 
	 * Switch according to the ioctl called 
	 */
	switch (cmd) {
	case IOCTL_REGPHYS:
		if (copy_from_user(&global_map, (cn_user_mmap_ *)arg, sizeof(cn_user_mmap_))){
			return -EACCES;
		}	
		break;
		
	case IOCTL_GET_PHYSADDR:	
		
		if (copy_from_user(&fd_phys_map, (cn_fd_phys_map *)arg, 
						sizeof(cn_fd_phys_map))){							
			return -EACCES;
		}	
		
		/* get the physical address */
		db = dma_buf_get(fd_phys_map.mem_fd);
		if (IS_ERR(db)) {
			MRG_ERR("dma_buf_get() failed fd[%d]\n", fd_phys_map.mem_fd);
			return -1;
		}
		
		dba = dma_buf_attach(db, mirage_mmap_device);
		
		if (IS_ERR(dba)) {
			MRG_ERR("dma_buf_attach() failed db[%p]\n", db);
			goto ERR_dma_buf_attach;
		}
		
		sg = dma_buf_map_attachment(dba, DMA_TO_DEVICE);
		
		if (IS_ERR(sg)) {
			MRG_ERR("dma_buf_map_attachment() failed dba[%p]\n",
				dba);
			goto ERR_dma_buf_map_attachment;
		}
		
		/* convert sg_table to dma_addr_t */
		addr = sg_phys(sg->sgl);		
		fd_phys_map.phys = addr;
		
		if (copy_to_user((void __user *)arg, (void *)&fd_phys_map,
				 sizeof(fd_phys_map)))
			return -EFAULT;
		
		/* release everything */			
		if (!IS_ERR_OR_NULL(dba) && !IS_ERR_OR_NULL(sg)) 
			dma_buf_unmap_attachment(dba, sg, DMA_TO_DEVICE);
		
		if (!IS_ERR_OR_NULL(db) && !IS_ERR_OR_NULL(dba)) 
			dma_buf_detach(db, dba);
		
		if (!IS_ERR_OR_NULL(db)) 
			dma_buf_put(db);
					
		break;
	}

	return SUCCESS;
	
ERR_dma_buf_map_attachment:
		dma_buf_detach(db, dba);
ERR_dma_buf_attach:
		dma_buf_put(db);
		
	return -1;	
}

static int mirage_mmap_mmap(struct file *psFile, 
							struct vm_area_struct * vma)
{
    unsigned long ulSize = vma->vm_end - vma->vm_start;
    unsigned long ulPhyAddr;
    int iRet;    
    
	ulPhyAddr = global_map.physaddr + vma->vm_pgoff;	
	
#ifdef _DEBUG
	printk("Physical address being mapped is 0x%x\n", (unsigned int)ulPhyAddr);
#endif
    ulPhyAddr = ulPhyAddr >> PAGE_SHIFT;

	/** Making it non cached */
    vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	vma->vm_flags |= VM_IO | VM_RESERVED;
	
	iRet = io_remap_pfn_range(vma, vma->vm_start, ulPhyAddr,
           ulSize, vma->vm_page_prot);
	
	
    if (iRet < 0) {
        return -EAGAIN;
    }
	return 0;
}

/* Module Declarations */

/* 
 * This structure will hold the functions to be called
 * when a process does something to the device we
 * created. Since a pointer to this structure is kept in
 * the devices table, it can't be local to
 * init_module. NULL is for unimplemented functions. 
 */
struct file_operations mirage_mmap_fops = {
	.read = mirage_mmap_read,
	.write = mirage_mmap_write,
	.unlocked_ioctl = mirage_mmap_ioctl,
	.open = mirage_mmap_open,
	.release = mirage_mmap_release,	/* a.k.a. close */
	.mmap	= mirage_mmap_mmap,
};

/* 
 * Initialize the module - Register the character device 
 */
static int __devinit mirage_probe(struct platform_device *pdev)
{
	struct resource *pmu_res, *econf_res, *gpu_res;

	printk(KERN_INFO "mirage-mmap driver init");  

	mirage_pdev = pdev;
	mirage_usecount = 0;

	if (alloc_chrdev_region(&dev_major, 0, 1, DEVICE_NAME) < 0){
		printk(KERN_INFO "err:alloc_chrdev_region");  
		return -1;  
	}    
	
	if ((cl = class_create(THIS_MODULE, DEVICE_NAME)) == NULL){
		printk(KERN_INFO "err:class_create");  
		unregister_chrdev_region(dev_major, 1);    
		return -1;  
	}    
	
	mirage_mmap_device = 
		device_create(cl, NULL, dev_major, NULL, DEVICE_NAME);
	
	if (mirage_mmap_device == NULL){    
		
		printk(KERN_INFO "err:device_create");  
		class_destroy(cl);    
		unregister_chrdev_region(dev_major, 1);    
		return -1;  
	}    
	
	cdev_init(&c_dev, &mirage_mmap_fops);    
	
	if (cdev_add(&c_dev, dev_major, 1) == -1)  
	{    
		printk(KERN_INFO "err:cdev_add");  
		device_destroy(cl, dev_major);    
		class_destroy(cl);    
		unregister_chrdev_region(dev_major, 1);    
		return -1;  
	}

	/* allocate registers memory region */
	pmu_res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "pmu");
	if (pmu_res == NULL) {
		MRG_ERR("err:platform_get_resource(pmu)");  
		cdev_del(&c_dev);
		device_destroy(cl, dev_major);
		class_destroy(cl);
		unregister_chrdev_region(dev_major, 1);
		return -EBUSY;
	}

	/* remapping registers */
	pmubase = (__u8 __iomem *)ioremap(pmu_res->start,
						 resource_size(pmu_res));
	if (pmubase == NULL) {
		MRG_ERR("err:ioremap(pmu)");  
		cdev_del(&c_dev);
		device_destroy(cl, dev_major);
		class_destroy(cl);
		unregister_chrdev_region(dev_major, 1);
		return -ENOMEM;
	}

	/* allocate registers memory region */
	econf_res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "econf");
	if (econf_res == NULL) {
		MRG_ERR("err:platform_get_resource(econf)");  
		iounmap(pmubase);
		cdev_del(&c_dev);
		device_destroy(cl, dev_major);
		class_destroy(cl);
		unregister_chrdev_region(dev_major, 1);
		return -EBUSY;
	}

	/* remapping registers */
	econfbase = (__u8 __iomem *)ioremap(econf_res->start,
						 resource_size(econf_res));
	if (econfbase == NULL) {
		MRG_ERR("err:ioremap(econf)");  
		iounmap(pmubase);
		cdev_del(&c_dev);
		device_destroy(cl, dev_major);
		class_destroy(cl);
		unregister_chrdev_region(dev_major, 1);
		return -ENOMEM;
	}

	/* allocate registers memory region */
	gpu_res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "gpu");
	if (gpu_res == NULL) {
		MRG_ERR("err:platform_get_resource(gpu)");  
		iounmap(econfbase);
		iounmap(pmubase);
		cdev_del(&c_dev);
		device_destroy(cl, dev_major);
		class_destroy(cl);
		unregister_chrdev_region(dev_major, 1);
		return -EBUSY;
	}

	/* remapping registers */
	gpubase = (__u8 __iomem *)ioremap(gpu_res->start,
						 resource_size(gpu_res));
	if (gpubase == NULL) {
		MRG_ERR("err:ioremap(gpu)");  
		iounmap(econfbase);
		iounmap(pmubase);
		cdev_del(&c_dev);
		device_destroy(cl, dev_major);
		class_destroy(cl);
		unregister_chrdev_region(dev_major, 1);
		return -ENOMEM;
	}

	gpuss_clk = clk_get(&(pdev->dev), "gpu0");
	if (IS_ERR(gpuss_clk)) {
		MRG_ERR("err:gpuSS clk_get(%s)\n", dev_name(&(pdev->dev)));  
		iounmap(gpubase);
		iounmap(econfbase);
		iounmap(pmubase);
		cdev_del(&c_dev);  
		device_destroy(cl, dev_major);    
		class_destroy(cl);    
		unregister_chrdev_region(dev_major, 1);
		return -EFAULT;
	}

	eastp_clk = clk_get(&(pdev->dev), "gpu1");
	if (IS_ERR(eastp_clk)) {
		MRG_ERR("err:gpu_eastp clk_get(%s)\n", dev_name(&(pdev->dev)));  
		clk_put(gpuss_clk);
		iounmap(gpubase);
		iounmap(econfbase);
		iounmap(pmubase);
		cdev_del(&c_dev);  
		device_destroy(cl, dev_major);    
		class_destroy(cl);    
		unregister_chrdev_region(dev_major, 1);
		return -EFAULT;
	}

	pm_runtime_enable(&(pdev->dev));
	return 0;
}

/* 
 * Cleanup - unregister the appropriate file from /proc 
 */
static int __devexit mirage_remove(struct platform_device *pdev)
{
	pm_runtime_disable(&(pdev->dev));
	clk_put(gpuss_clk);
	clk_put(eastp_clk);

	iounmap(gpubase);
	iounmap(econfbase);
	iounmap(pmubase);
	cdev_del(&c_dev);  
	device_destroy(cl, dev_major);  
	class_destroy(cl);  
	unregister_chrdev_region(dev_major, 1);  
	printk(KERN_INFO "mirage-mmap: unregistered");
	return 0;
}

static int mirage_suspend(struct device *dev)
{
#ifdef DEBUG
	printk(KERN_INFO "%s : usecount=%d\n", __func__, 
			mirage_usecount);
#endif
	/* check for idle */
	if (mirage_usecount > 0)
		return -EBUSY;

	return 0;
}

static int mirage_resume(struct device *dev)
{
#ifdef DEBUG
	printk(KERN_INFO "%s : start\n", __func__);
#endif
	return 0;
}

static int mirage_runtime_suspend(struct device *dev)
{

#ifdef DEBUG
	printk(KERN_INFO "%s : start\n", __func__);
#endif
	mirage_hw_exit();
	return 0;
}

static int mirage_runtime_resume(struct device *dev)
{
#ifdef DEBUG
	printk(KERN_INFO "%s : start\n", __func__);
#endif

	mirage_hw_init();
	return 0;
}

static void mirage_hw_init(void)
{
#ifdef DEBUG
	printk(KERN_INFO "%s : start\n", __func__);
#endif
	/* clock on */
	clk_prepare_enable(eastp_clk);
	clk_prepare_enable(gpuss_clk);

#ifdef DEBUG
	printk(KERN_INFO "\tClockGatingOff eastp:%d\n", 
		__raw_readl(pmubase + PMU_CLOCKGATINGOFF_GPUSS_0_OFS)&0x1);
	printk(KERN_INFO "\tClockGatingOff gpuss:%d\n", 
		(__raw_readl(pmubase + PMU_CLOCKGATINGOFF_EASTPIERSS_0_OFS)>>8)&0x1);
	printk(KERN_INFO "\tClockGatingOff power:%d\n", 
		__raw_readl(pmubase + PMU_CLOCKGATINGOFFFORPOWER_GPU_OFS)&0x1);
#endif

	/* soft reset off */
	__raw_writel(0x0002, (pmubase + PMU_SOFTRESETOFF_EASTPIERSS_0_OFS));
	/* seqstatus power on */
	__raw_writel(0x0001, (pmubase + PMU_SEQSTATUS_POWERON_GPU_OFS));

	__raw_writel(0x0001, (pmubase + PMU_CLOCKGATINGOFFFORPOWER_GPU_OFS));
	
	while (1) {
		if (__raw_readl(pmubase + PMU_STATUS_INTERRUPT_OFS) & 1) {
			__raw_writel(0x1, (pmubase + PMU_STATUS_INTERRUPT_OFS));
			break;
		}
	}
	while (1) {
		if (!(__raw_readl(pmubase + PMU_SEQSTATUS_POWERON_GPU_OFS) & 1))
			break;
	}
	__raw_writel(0x0001, (pmubase + PMU_STATUS_INTERRUPT_OFS));

#ifdef DEBUG
	printk(KERN_INFO "\tGPU_DMACSTATUS(%08x)\n", __raw_readl(gpubase + GPU_DMACSTATUS_OFFS));
	printk(KERN_INFO "\tGPU_DMACINTMSK(%08x)\n", __raw_readl(gpubase + GPU_DMACINTMSK_OFFS));
#endif
}

static void mirage_hw_exit(void)
{
#ifdef DEBUG
	printk(KERN_INFO "%s : start\n", __func__);
#endif
#ifdef DEBUG
	printk(KERN_INFO "\tGPU_DMACSTATUS(%08x)\n", __raw_readl(gpubase + GPU_DMACSTATUS_OFFS));
	printk(KERN_INFO "\tGPU_DMACINTMSK(%08x)\n", __raw_readl(gpubase + GPU_DMACINTMSK_OFFS));
#endif
	/* reset on */
	__raw_writel(0x0302, (pmubase + PMU_SOFTRESETON_EASTPIERSS_0_OFS));
	__raw_writel(0x0001, (pmubase + PMU_SOFTRESETON_GPUSS_0_OFS));
	__raw_writel(0x0001, (pmubase + PMU_SEQSTATUS_POWEROFF_GPU_OFS));

	while (1) {
		if (__raw_readl(pmubase + PMU_STATUS_INTERRUPT_OFS) & 1)
			break;
	}
	__raw_writel(0x0001, (pmubase + PMU_STATUS_INTERRUPT_OFS));

	clk_disable_unprepare(gpuss_clk);	/* gpu clock */
	clk_disable_unprepare(eastp_clk);	/* gpu eastpier clock */
#ifdef DEBUG
	printk(KERN_INFO "\tClockGatingOn power:%d\n", 
		__raw_readl(pmubase + PMU_CLOCKGATINGONFORPOWER_GPU_OFS)&0x1);
	printk(KERN_INFO "\tClockGatingOn gpuss:%d\n", 
		(__raw_readl(pmubase + PMU_CLOCKGATINGON_EASTPIERSS_0_OFS)>>8)&0x1);
	printk(KERN_INFO "\tClockGatingOn eastp:%d\n", 
		__raw_readl(pmubase + PMU_CLOCKGATINGON_GPUSS_0_OFS)&0x1);
#endif
}

static const struct dev_pm_ops mirage_pm_ops = {
	.suspend = mirage_suspend,
	.resume = mirage_resume,
	.runtime_suspend = mirage_runtime_suspend,
	.runtime_resume = mirage_runtime_resume,
};

static struct platform_driver mirage_driver = {
	.probe = mirage_probe,
	.remove = mirage_remove,
	.driver = {
		.name = "miragelite",
		.owner = THIS_MODULE,
		.pm = &mirage_pm_ops,
	},
};

static int __init mirage_init(void)
{
	return platform_driver_register(&mirage_driver);
}

static void __exit mirage_exit(void)
{
	platform_driver_unregister(&mirage_driver);
}

module_init(mirage_init);
module_exit(mirage_exit);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("OpenGraphics<email:opengvg@toshiba-tsip.com");
MODULE_DESCRIPTION("Our First Character Driver");
