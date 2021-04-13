/*
 * drivers/staging/iio/adc/applite_sadc.c
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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/err.h>
#include <linux/delay.h>
#include <linux/sched.h>

#include <linux/pm_runtime.h>
#include <linux/clk.h>

#include <mach/regs/pmu_offs_def.h>
#include <mach/regs/pmu_reg_def.h>

#include "../iio.h"
#include "../sysfs.h"
#include "applite_sadc.h"


#ifdef APPLITE_SADC_DEBUG
	#define DEBUG		pr_info

#ifdef APPLITE_SADC_DEBUG_INFO
	#define DEBUG_INFO	pr_info
#else
	#define DEBUG_INFO(x, ...) { \
	}
#endif

#else
	#define DEBUG(x, ...) { \
	}
	#define DEBUG_INFO(x, ...) { \
	}
#endif


#define MOD_NAME "applite-sadc"
#define SADC_TIMEOUT 10	/* 10ms timeout */

static int al_sadc_runtime_suspend(struct device *dev);
static int al_sadc_runtime_resume(struct device *dev);

/* write to register */
static inline void reg_write(const volatile u32 *reg, u32 val)
{
	__raw_writel(val, (void __iomem *)reg);
}


/* read from register */
static inline u32 reg_read(const volatile u32 *reg)
{
	return __raw_readl((void __iomem *)reg);
}

static void al_sadc_hw_init(struct al_sadc_info *info)
{
#if IS_ENABLED(CONFIG_ARCH_TZ2000)
	__u32 tmp;
#endif

	DEBUG("%s : start\n", __func__);
	/* reset assert */
	__raw_writel(0x100, (info->pmu_base + PMU_SOFTRESETON_PERISS_1_OFS));
	/* clock on */
	clk_prepare_enable(info->clk);
	DEBUG("\tClockGatingOff:%d\n",
		(__raw_readl(info->pmu_base + PMU_ClockGatingOff_periSS_1_OFFS)>>8)&0x1);
#if IS_ENABLED(CONFIG_ARCH_TZ2000)
	/* VDD33_IOA */
	tmp = __raw_readl(info->pmu_base + PMU_POREN_OFS);
	tmp |= PMU_POREN_POREN_TOP_ADC_MASK;
	__raw_writel(tmp, (info->pmu_base + PMU_POREN_OFS));
	/* 100ns wait */
	ndelay(100);
#endif
	/* reset negate */
	__raw_writel(0x100, (info->pmu_base + PMU_SOFTRESETOFF_PERISS_1_OFS));

	clk_disable_unprepare(info->clk);
	DEBUG("\tClockGatingOn:%d\n",
		(__raw_readl(info->pmu_base + PMU_ClockGatingOn_periSS_1_OFFS)>>8)&0x1);
}


static int al_sadc_read_raw(struct iio_dev *indio_dev,
				struct iio_chan_spec const *chan,
				int *val,
				int *val2,
				long mask)
{
	int     retval;
	u32	read_val;
	u32	i;
	unsigned long timeout;
	struct al_sadc_info *info = iio_priv(indio_dev);

	DEBUG("%s : start(CH:%d)\n", __func__, (int)chan->address);

	if (mask == 0) {

		mutex_lock(&indio_dev->mlock);
#if IS_ENABLED(CONFIG_PM_RUNTIME)
		pm_runtime_get_sync(indio_dev->dev.parent);
		DEBUG("usage_count:%d(%d)\n", indio_dev->dev.parent->power.usage_count,
			(int)chan->address);
#else
		if (!info->sadc_usecount)
			al_sadc_runtime_resume(indio_dev->dev.parent);
#endif
		info->sadc_usecount++;
		DEBUG("%s : sadc_usecount=%d\n", __func__, info->sadc_usecount);

		/* Measurement setup */
		if (info->sadc_wait_flg != 0) {
			DEBUG("%s : waiting start(CH=%d)\n", __func__, (int)chan->address);

			/* Wait for complete */
			info->done = false;
			mutex_unlock(&indio_dev->mlock);
			wait_event(info->wq_data_avail, info->done);

			/* Get convert data from buffer */
			*val = info->data[chan->address];
			if (!info->sadc_err)
				retval = IIO_VAL_INT;
			else
				retval = info->sadc_err;
		} else {
			DEBUG("%s : read sequence start(CH=%d)\n", __func__, (int)chan->address);
			/*debug_count++;*/
			/* Set wait flag */
			info->sadc_wait_flg = 1;
			mutex_unlock(&indio_dev->mlock);

			/* To RESET Status */
			reg_write(&info->sadc_reg->sadctrl, SADCTRL_RST | SADCTRL_STB);

			/* To STB Status */
			read_val = reg_read(&info->sadc_reg->sadctrl);
			read_val = (read_val & ~SADCTRL_RST) | SADCTRL_STB;
			reg_write(&info->sadc_reg->sadctrl, read_val);

			/* To START Status */
			read_val = reg_read(&info->sadc_reg->sadctrl);
			read_val = (read_val & ~(SADCTRL_RST | SADCTRL_STB));
			reg_write(&info->sadc_reg->sadctrl, read_val);

			/* Check Valid Bit for READ Status */
			timeout = jiffies + msecs_to_jiffies(SADC_TIMEOUT);
			do {
				read_val = reg_read(&info->sadc_reg->sadctrl);
				if (read_val & SADCTRL_VALID)
					break;
			} while (time_after_eq(timeout, jiffies));

			/* To STB Status */
			reg_write(&info->sadc_reg->sadctrl, SADCTRL_STB);

			/* Check Valid bit */
			if (read_val & SADCTRL_VALID) {
				/* Get convert data from all CH. and write to buffer */
				for (i = 0; i < SADCH_NUM; i++) {
					info->data[i] = (reg_read(&info->sadc_reg->sadch[i]) &
							SADCH_VALUE_MASK);
					DEBUG_INFO("\tdata[CH:%d]:%d\n", i, info->data[i]);
				}

				DEBUG_INFO("\tSADDEBUG:0x%x\n", reg_read(&info->sadc_reg->saddebug));
				info->sadc_err = SADC_ERR_NONE;
				retval = IIO_VAL_INT;
			}
			/* Timeout */
			else {
				memset(&info->data[0], 0, sizeof(info->data)); /* Clear buffer */
				pr_err("%s : Read timeout(CH:%d) SADDEBUG:0x%x\n", __func__
					, (int)chan->address, reg_read(&info->sadc_reg->saddebug));
				info->sadc_err = -ETIMEDOUT;
				retval = -ETIMEDOUT;
			}

			/* To RESET Status */
			reg_write(&info->sadc_reg->sadctrl, SADCTRL_RST | SADCTRL_STB);

			/* Get convert data from buffer */
			*val = info->data[chan->address];

			mutex_lock(&indio_dev->mlock);
			/* Clear wait flag */
			info->sadc_wait_flg = 0;

			/* Call complete for waiting channel */
			info->done = true;
			wake_up_all(&info->wq_data_avail);
			mutex_unlock(&indio_dev->mlock);
		}

		mutex_lock(&indio_dev->mlock);
#if IS_ENABLED(CONFIG_PM_RUNTIME)
		pm_runtime_put_sync(indio_dev->dev.parent);
		DEBUG("usage_count:%d(%d)\n", indio_dev->dev.parent->power.usage_count,
			(int)chan->address);
#else
		if (info->sadc_usecount == 1)
			al_sadc_runtime_suspend(indio_dev->dev.parent);
#endif
		info->sadc_usecount--;
		mutex_unlock(&indio_dev->mlock);
		DEBUG("%s : sadc_usecount=%d\n", __func__, info->sadc_usecount);

		DEBUG("%s : end(CH:%d) value=%d\n", __func__, (int)chan->address, *val);
		return retval;
	}

	DEBUG("%s : invalid mask=%d\n", __func__, (int)mask);
	retval = -EINVAL;
	return retval;
}


static const struct iio_info al_sadc_iio_info = {
	.read_raw = &al_sadc_read_raw,
	.driver_module = THIS_MODULE,
};

#ifdef CONFIG_ARCH_TZ3000
#define AL_SADC_CHANNEL(num) {				\
	.type = IIO_VOLTAGE,				\
	.indexed = 1,					\
	.channel = num,					\
	.address = num,					\
	.info_mask = 0,					\
	.scan_index = num,				\
	.scan_type = IIO_ST('u', 10, 32, 0),		\
}
#endif
#ifdef CONFIG_ARCH_TZ2000
#define AL_SADC_CHANNEL(num) {				\
	.type = IIO_VOLTAGE,				\
	.indexed = 1,					\
	.channel = num,					\
	.address = num,					\
	.info_mask = 0,					\
	.scan_index = num,				\
	.scan_type = IIO_ST('u', 12, 32, 0),		\
}
#endif


static struct iio_chan_spec al_sadc_iio_channels[] = {
#ifdef CONFIG_ARCH_TZ3000
	AL_SADC_CHANNEL(0),
	AL_SADC_CHANNEL(1),
	AL_SADC_CHANNEL(2),
	AL_SADC_CHANNEL(3),
	AL_SADC_CHANNEL(4),
	AL_SADC_CHANNEL(5),
#endif
#ifdef CONFIG_ARCH_TZ2000
	AL_SADC_CHANNEL(0),
	AL_SADC_CHANNEL(1),
	AL_SADC_CHANNEL(2),
	AL_SADC_CHANNEL(3),
#endif
};


static int __devinit al_sadc_probe(struct platform_device *pdev)
{
	struct al_sadc_info *info = NULL;
	struct resource *res, *res2;
	void __iomem *addr, *addr2;
	int retval = -ENODEV;
	struct iio_dev *iodev = NULL;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "failed to get platform I/O memory\n");
		retval = -EBUSY;
		goto errout1;
	}

	/* Request the regions */
	if (!request_mem_region(res->start, resource_size(res), "iio-applite-sadc")) {
		dev_err(&pdev->dev, "failed to reserve registers\n");
		retval = -EBUSY;
		goto errout1;
	}

	addr = ioremap(res->start, resource_size(res));
	if (!addr) {
		dev_err(&pdev->dev, "failed mapping memory\n");
		retval = -ENOMEM;
		goto errout2;
	}

	res2 = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (!res2) {
		dev_err(&pdev->dev, "failed to get platform I/O memory(PMU)\n");
		retval = -EBUSY;
		goto errout3;
	}


	addr2 = ioremap(res2->start, resource_size(res2));
	if (!addr2) {
		dev_err(&pdev->dev, "failed mapping memory(PMU)\n");
		retval = -ENOMEM;
		goto errout4;
	}

	iodev = iio_allocate_device(sizeof(struct al_sadc_info));
	if (!iodev) {
		dev_err(&pdev->dev, "failed allocating iio device\n");
		retval = -ENOMEM;
		goto errout5;
	}

	info = iio_priv(iodev);
	info->sadc_reg = (struct al_sadc_reg *)addr;
	info->pmu_base = addr2;
	info->sadc_wait_flg = 0;
	info->sadc_err = 0;
	info->sadc_usecount = 0;

	platform_set_drvdata(pdev, iodev);

	init_waitqueue_head(&info->wq_data_avail);

	iodev->name = MOD_NAME;
	iodev->dev.parent = &pdev->dev;
	iodev->info = &al_sadc_iio_info;
	iodev->modes = INDIO_DIRECT_MODE;
	iodev->channels = al_sadc_iio_channels;
	iodev->num_channels = ARRAY_SIZE(al_sadc_iio_channels);

	retval = iio_device_register(iodev);
	if (retval) {
		dev_err(&pdev->dev, "failed register iio device (%d)\n", retval);
		goto errout6;
	}

	info->clk = clk_get(&(pdev->dev), NULL);
	if (IS_ERR(info->clk)) {
		dev_err(&pdev->dev, "failed clk_get(%s, NULL)\n",
						dev_name(&pdev->dev));
		retval = -EFAULT;
		goto errout7;
	}
	pm_runtime_enable(&(pdev->dev));
	al_sadc_hw_init(info);

	dev_info(&pdev->dev, "ApPLite Slow AD driver loaded\n");

	return 0;

errout7:
	iio_device_unregister(iodev);
errout6:
	iio_free_device(iodev);
errout5:
	iounmap(addr2);
errout4:
errout3:
	iounmap(addr);
errout2:
	release_mem_region(res->start, resource_size(res));
errout1:
	return retval;
}

static int __devexit al_sadc_remove(struct platform_device *pdev)
{
	struct iio_dev *iodev = platform_get_drvdata(pdev);
	struct al_sadc_info *info = iio_priv(iodev);
	struct resource *res;

	dev_info(&pdev->dev, "ApPLite Slow AD driver remove\n");

	pm_runtime_disable(&(pdev->dev));

	clk_put(info->clk);
	iio_device_unregister(iodev);

	platform_set_drvdata(pdev, NULL);
	iounmap((void __iomem *)info->sadc_reg);
	iounmap(info->pmu_base);
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(res->start, resource_size(res));

	info->sadc_wait_flg = 0;
	info->sadc_err = 0;
	iio_free_device(iodev);

	DEBUG("%s : remove end\n", __func__);

	return 0;
}

static int al_sadc_suspend(struct device *dev)
{
	struct platform_device *pdev;
	struct iio_dev *iodev;
	struct al_sadc_info *info;

	pdev = to_platform_device(dev);
	iodev = platform_get_drvdata(pdev);
	info = iio_priv(iodev);
	/* check for idle */
	DEBUG("%s : start usecount=%d\n", __func__, info->sadc_usecount);
	if (info->sadc_usecount > 0)
		return -EBUSY;

	return 0;
}

static int al_sadc_resume(struct device *dev)
{
	struct platform_device *pdev;
	struct iio_dev *iodev;
	struct al_sadc_info *info;

	DEBUG("%s : start\n", __func__);
	pdev = to_platform_device(dev);
	iodev = platform_get_drvdata(pdev);
	info = iio_priv(iodev);

	al_sadc_hw_init(info);
	return 0;
}

static int al_sadc_runtime_suspend(struct device *dev)
{
	struct platform_device *pdev;
	struct iio_dev *iodev;
	struct al_sadc_info *info;
	__u32 val;

	DEBUG("%s : start\n", __func__);
	pdev = to_platform_device(dev);
	iodev = platform_get_drvdata(pdev);
	info = iio_priv(iodev);

	/* check for idle */
	val = reg_read(&info->sadc_reg->sadctrl);
	if (!(val & SADCTRL_RST)) {
		DEBUG("\tBUSY! (0x%x)\n", val);
		return -EBUSY;
	}
	clk_disable_unprepare(info->clk);
	DEBUG("\tClockGatingOn:%d\n",
		(__raw_readl(info->pmu_base + PMU_ClockGatingOn_periSS_1_OFFS)>>8)&0x1);
	return 0;
}

static int al_sadc_runtime_resume(struct device *dev)
{
	struct platform_device *pdev;
	struct iio_dev *iodev;
	struct al_sadc_info *info;

	DEBUG("%s : start\n", __func__);
	pdev = to_platform_device(dev);
	iodev = platform_get_drvdata(pdev);
	info = iio_priv(iodev);

	clk_prepare_enable(info->clk);
	DEBUG("\tClockGatingOff:%d\n",
		(__raw_readl(info->pmu_base + PMU_ClockGatingOff_periSS_1_OFFS)>>8)&0x1);
	return 0;
}


static const struct dev_pm_ops al_sadc_pm_ops = {
	.suspend = al_sadc_suspend,
	.resume = al_sadc_resume,
	.runtime_suspend = al_sadc_runtime_suspend,
	.runtime_resume = al_sadc_runtime_resume,
};

static struct platform_driver al_sadc_driver = {
	.probe		= al_sadc_probe,
	.remove		= __devexit_p(al_sadc_remove),
	.driver		= {
		.name	= MOD_NAME,
		.owner	= THIS_MODULE,
		.pm = &al_sadc_pm_ops,
	},
};

module_platform_driver(al_sadc_driver);

MODULE_AUTHOR("TOSHIBA Corporation");
MODULE_DESCRIPTION("ApP Lite  Slow AD driver");
MODULE_LICENSE("GPL v2");

