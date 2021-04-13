/*
 * drivers/staging/applite/pwm/applite-pwm.c
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
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/err.h>
#include <linux/clk.h>
#include <linux/io.h>
#include <linux/pwm.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/init.h>
#include <asm/uaccess.h>
#include <mach/hardware.h>

#include <linux/pm_runtime.h>
#include <linux/clk.h>

#include <mach/platform.h>
#include <mach/regs/pwm_offs_def.h>
#include <mach/regs/pwm_reg_def.h>
#include <mach/regs/pmu_offs_def.h>
#include <mach/regs/pmu_reg_def.h>

#define APPLITE_PWM_SYSFS
/*#define APPLITE_PWM_DEBUG*/
#ifdef APPLITE_PWM_DEBUG
	#define debug		pr_info
#else
	#define debug(x, ...) { \
	}
#endif

#if IS_ENABLED(CONFIG_ARCH_TZ2000)
#define PWM_NUM	5
#endif
#if IS_ENABLED(CONFIG_ARCH_TZ3000)
#define PWM_NUM	6
#endif

#define GENB_STATUS_READY	1
#define GENB_STATUS_SETTING	2
#define GENB_STATUS_RUNNING	3
#define GENB_STATUS_RELEASE	4

#ifdef APPLITE_PWM_SYSFS
#define BUF_SIZE 30
static struct kobject *pwm_kobj;
static void __iomem	*g_mmio_base;
#endif

static const char driver_name[] = "applite-pwm";

struct pwm_device {
	struct list_head	node;
	struct platform_device *pdev;
	struct clk	*clk;

	const char	*label;

	void __iomem	*mmio_base;
	void __iomem	*pmu_base;

	unsigned int	use_count;
	unsigned int	pwm_id;

	unsigned int	iteration;

	unsigned int	div;
	unsigned int	pol;
	unsigned int	lvs;
	unsigned int	enbsel;

	unsigned int	genb_set;
};

static struct pwm_device *gpwm[PWM_NUM];

static unsigned int pwm_genb;
static unsigned int genb_set_status;
static unsigned int pwm_usecount;


static void al_pwm_hw_init(void);
static int al_pwm_runtime_suspend(struct device *dev);
static int al_pwm_runtime_resume(struct device *dev);



int pwm_config(struct pwm_device *pwm, int duty_ns, int period_ns)
{
	if (pwm == NULL || period_ns == 1) {
		pr_err("pwm_config() ERROR=EINVAL(%d)\n", -EINVAL);
		pr_err("pwm=0x%x period_ns=0x%x duty_ns=0x%x\n", (unsigned int)pwm, period_ns, duty_ns);
		return -EINVAL;
	}

	if (pwm->use_count == 0) {
		pr_err("pwm_config() ERROR=EINVAL(%d) please call pwm_request().\n", -EINVAL);
		return -EINVAL;
	}

	if (period_ns > 1 && duty_ns == 0) {
		pr_err("pwm_config() ERROR=EINVAL(%d)\n", -EINVAL);
		pr_err("[period_ns > 1 && duty_ns == 0] period_ns=0x%x duty_ns=0x%x\n", period_ns, duty_ns);
		return -EINVAL;
	}

	if (period_ns > 1 && duty_ns > 0 && duty_ns >= period_ns) {
		pr_err("pwm_config() ERROR=EINVAL(%d)\n", -EINVAL);
		pr_err("[period_ns > 1 && duty_ns > 0 && duty_ns > period_ns] period_ns=0x%x duty_ns=0x%x\n", period_ns, duty_ns);
		return -EINVAL;
	}

	if (pwm->iteration > PWM_PWM0_ITERATION_ITERATION_BIT) {
		pr_err("pwm_config() ERROR=EINVAL(%d)\n", -EINVAL);
		pr_err("[pwm->iteration > PWM_PWM0_ITERATION_ITERATION_BIT] pwm->iteration=0x%x\n", pwm->iteration);
		return -EINVAL;
	}

	/* Set FREQ(period_ns) */
	__raw_writel(period_ns, (pwm->mmio_base + (0x20 * pwm->pwm_id) + PWM_PWM0_FREQ_OFFS));

	/* Set DUTY(duty_ns) */
	__raw_writel(duty_ns, (pwm->mmio_base + (0x20 * pwm->pwm_id) + PWM_PWM0_DUTY_OFFS));

	/* Set ITERATION */
	__raw_writel(pwm->iteration, (pwm->mmio_base + (0x20 * pwm->pwm_id) + PWM_PWM0_ITERATION_OFFS));

	return 0;
}
EXPORT_SYMBOL(pwm_config);

int pwm_enable(struct pwm_device *pwm)
{
	int rc = 0;
	unsigned int pwm_cr = 0, pwm_cr_read = 0, pwm_genb_read = 0;
	unsigned int cur_div = 0, next_div = 0, tmp_enbsel = 0;

	if (pwm) {
		if (pwm->use_count == 0) {
			pr_err("pwm_enable() ERROR=EINVAL(%d) please call pwm_request().\n", -EINVAL);
			return -EINVAL;
		}
		if (pwm->enbsel > 3 || pwm->div > 15 || pwm->lvs > 1 || pwm->pol > 1) {
			pr_err("pwm_enable() ERROR=EINVAL(%d) pwm->enbsel=0x%x pwm->div=0x%x pwm->lvs=0x%x pwm->pol=0x%x\n",
				-EINVAL, pwm->enbsel, pwm->div, pwm->lvs, pwm->pol);
			return -EINVAL;
		}

		pwm_cr_read = __raw_readl((pwm->mmio_base + (0x20 * pwm->pwm_id) + PWM_PWM0_CR_OFFS));

		if (pwm->enbsel == 0) {
			if ((pwm_cr_read & PWM_PWM0_CR_ENB_MASK) == 0) {
				tmp_enbsel = ((pwm_cr_read & PWM_PWM0_CR_ENBSEL_MASK) >> PWM_PWM0_CR_ENBSEL_SHIFT);
				if (tmp_enbsel > 0) {
					pwm_genb_read = __raw_readl(pwm->mmio_base + PWM_PWM_GENB_OFFS);
					if (tmp_enbsel == 1) {
						if ((pwm_genb_read & PWM_PWM_GENB_GENB0_MASK) == 0) {
							pwm_cr = 1; /*ENB*/
						} else {
							pr_err("pwm_enable() ERROR=EBUSY(%d) (case1)please call pwm_disable().\n", -EBUSY);
							return -EBUSY;
						}
					} else if (tmp_enbsel == 2) {
						if ((pwm_genb_read & PWM_PWM_GENB_GENB1_MASK) == 0) {
							pwm_cr = 1; /*ENB*/
						} else {
							pr_err("pwm_enable() ERROR=EBUSY(%d) (case2)please call pwm_disable().\n", -EBUSY);
							return -EBUSY;
						}
					} else if (tmp_enbsel == 3) {
						if ((pwm_genb_read & PWM_PWM_GENB_GENB2_MASK) == 0) {
							pwm_cr = 1; /*ENB*/
						} else {
							pr_err("pwm_enable() ERROR=EBUSY(%d) (case3)please call pwm_disable().\n", -EBUSY);
							return -EBUSY;
						}
					}
				} else {
					pwm_cr = 1; /*ENB*/
				}
			} else {
				cur_div = pwm_cr_read & PWM_PWM0_CR_DIV_MASK;
				next_div = pwm->div << PWM_PWM0_CR_DIV_SHIFT;

				if (cur_div == next_div) {
					pwm_cr = 1; /*ENB*/
				} else {
					pr_err("pwm_enable() ERROR=EBUSY(%d) (case4)please call pwm_disable().\n", -EBUSY);
					return -EBUSY;
				}
			}
		} else {
			if ((genb_set_status == GENB_STATUS_RUNNING) || (genb_set_status == GENB_STATUS_RELEASE)) {
				pr_err("pwm_enable() ERROR=EBUSY(%d) (case5)please call pwm_disable().\n", -EBUSY);
				return -EBUSY;
			}

			pwm_cr = 0; /*ENB*/
			genb_set_status = GENB_STATUS_SETTING;

			if (pwm->enbsel == 1)
				pwm_genb = (pwm_genb | PWM_PWM_GENB_GENB0_MASK);
			else if (pwm->enbsel == 2)
				pwm_genb = (pwm_genb | PWM_PWM_GENB_GENB1_MASK);
			else if (pwm->enbsel == 3)
				pwm_genb = (pwm_genb | PWM_PWM_GENB_GENB2_MASK);
		}

		pwm_cr = (pwm_cr | (1 << PWM_PWM0_CR_UPD_SHIFT)); /*UPD*/
		pwm_cr = (pwm_cr | ((pwm->pol & 0x1) << PWM_PWM0_CR_POL_SHIFT)); /*POL*/
		pwm_cr = (pwm_cr | ((pwm->lvs & 0x1) << PWM_PWM0_CR_LVS_SHIFT)); /*LVS*/
		pwm_cr = (pwm_cr | ((pwm->div & 0xf) << PWM_PWM0_CR_DIV_SHIFT)); /*DIV*/
		pwm_cr = (pwm_cr | ((pwm->enbsel & 0x3) << PWM_PWM0_CR_ENBSEL_SHIFT)); /*ENBSEL*/

		/* Set CONTROL */
		__raw_writel(pwm_cr, (pwm->mmio_base + (0x20 * pwm->pwm_id) + PWM_PWM0_CR_OFFS));

		if (pwm->genb_set == 1) {
			__raw_writel(pwm_genb, (pwm->mmio_base + PWM_PWM_GENB_OFFS));
			genb_set_status = GENB_STATUS_RUNNING;
		}
	} else {
		pr_err("pwm_enable() NULL is specified in the argument.\n");
		return -EINVAL;
	}

	return rc;
}
EXPORT_SYMBOL(pwm_enable);

void pwm_disable(struct pwm_device *pwm)
{
	unsigned int pwm_cr_read = 0;
	unsigned int tmp_enbsel = 0;

	if (pwm) {
		if (pwm->use_count == 0) {
			pr_warning("pwm_disable() pwm is free.\n");
			return;
		}

		/* Set CONTROL(ENB=0) */
		pwm_cr_read = __raw_readl((pwm->mmio_base + (0x20 * pwm->pwm_id) + PWM_PWM0_CR_OFFS));

		if (pwm_cr_read & PWM_PWM0_CR_ENB_MASK) {
			__raw_writel(0x0, (pwm->mmio_base + (0x20 * pwm->pwm_id) + PWM_PWM0_CR_OFFS));
		} else {
			tmp_enbsel = (pwm_cr_read & PWM_PWM0_CR_ENBSEL_MASK) >> PWM_PWM0_CR_ENBSEL_SHIFT;

			if (tmp_enbsel == 1) {
				if (pwm_genb & PWM_PWM_GENB_GENB0_MASK)
					pwm_genb = (pwm_genb ^ PWM_PWM_GENB_GENB0_MASK);
			} else if (tmp_enbsel == 2) {
				if (pwm_genb & PWM_PWM_GENB_GENB1_MASK)
					pwm_genb = (pwm_genb ^ PWM_PWM_GENB_GENB1_MASK);
			} else if (tmp_enbsel == 3) {
				if (pwm_genb & PWM_PWM_GENB_GENB2_MASK)
					pwm_genb = (pwm_genb ^ PWM_PWM_GENB_GENB2_MASK);
			}

			if (tmp_enbsel > 0) {
				genb_set_status = GENB_STATUS_RELEASE;
				if (pwm_genb == 0) {
					__raw_writel(pwm_genb, (pwm->mmio_base + PWM_PWM_GENB_OFFS));
					genb_set_status = GENB_STATUS_READY;
				}
			}
		}
	} else {
		pr_warning("pwm_disable() NULL is specified in the argument.\n");
	}
}
EXPORT_SYMBOL(pwm_disable);

static DEFINE_MUTEX(pwm_lock);
static LIST_HEAD(pwm_list);

struct pwm_device *pwm_request(int pwm_id, const char *label)
{
	struct pwm_device *pwm;
	int found = 0;

	mutex_lock(&pwm_lock);

	list_for_each_entry(pwm, &pwm_list, node) {
		if (pwm->pwm_id == pwm_id) {
			found = 1;
			break;
		}
	}

	if (found) {
		if (pwm->use_count == 0) {
			pwm_usecount++;
#if IS_ENABLED(CONFIG_PM_RUNTIME)
			pm_runtime_get_sync(&(pwm->pdev->dev));
#else
			if (pwm_usecount == 1)
				al_pwm_runtime_resume(&(pwm->pdev->dev));
#endif
			debug("%s: usecount=%d\n", __func__, pwm_usecount);
			pwm->use_count++;
			pwm->label = label;
		} else {
			pr_err("pwm_request() ERROR=EBUSY(%d) please call pwm_free().\n", -EBUSY);
			pwm = ERR_PTR(-EBUSY);
		}
	} else {
		pr_err("pwm_request() ERROR=ENOENT(%d) pwm_id=%d(min=%d max=%d)\n", -ENOENT, pwm_id, 0, (PWM_NUM-1));
		pwm = ERR_PTR(-ENOENT);
	}

	mutex_unlock(&pwm_lock);
	return pwm;
}
EXPORT_SYMBOL(pwm_request);

void pwm_free(struct pwm_device *pwm)
{
	if (pwm) {
		mutex_lock(&pwm_lock);

		if (pwm->use_count) {
			pwm->use_count--;
			pwm->label = NULL;
			pwm_usecount--;
#if IS_ENABLED(CONFIG_PM_RUNTIME)
			pm_runtime_put_sync(&(pwm->pdev->dev));
#else
			if (!pwm_usecount)
				al_pwm_runtime_suspend(&(pwm->pdev->dev));
#endif
			debug("%s: usecount=%d\n", __func__, pwm_usecount);
		} else {
			pr_warning("PWM device already freed\n");
		}

		mutex_unlock(&pwm_lock);
	} else {
		pr_warning("pwm_free() NULL is specified in the argument.\n");
	}
}
EXPORT_SYMBOL(pwm_free);

/*
 * pwm_handle_interrupts - interrupt handler
 */
static irqreturn_t
pwm_handle_interrupts(int irq, void *_dev)
{
	struct pwm_device *pwm = _dev;
	unsigned int pwm_intstatus = 0;

	pwm_intstatus = __raw_readl(pwm->mmio_base + PWM_PWM_INTSTATUS_OFFS);
	pr_err("Error Interrupt! pwm_intstatus=0x%x\n", pwm_intstatus);

	__raw_writel(pwm_intstatus, (pwm->mmio_base + PWM_PWM_INTSTATUS_OFFS));

	return IRQ_RETVAL(IRQ_HANDLED);
}


#ifdef APPLITE_PWM_SYSFS
static void applitepwm_reg_dump(void)
{
	int i, offset = 0;
	unsigned int reg1 = 0, reg2 = 2, reg3 = 0, reg4 = 0;

	pwm_usecount++;
#if IS_ENABLED(CONFIG_PM_RUNTIME)
	pm_runtime_get_sync(&(gpwm[0]->pdev->dev));
#else
	if (pwm_usecount == 1)
		al_pwm_runtime_resume(&(gpwm[0]->pdev->dev));
#endif
	debug("%s: usecount=%d\n", __func__, pwm_usecount);

	pr_err("***PWM REGISTERS DUMP***\n");
	pr_err("OFFSET | DATA\n");
	for (i = 0; i < 12 ; i++) {
		reg1 = __raw_readl(g_mmio_base + offset);
		reg2 = __raw_readl(g_mmio_base + offset + 4);
		reg3 = __raw_readl(g_mmio_base + offset + 8);
		reg4 = __raw_readl(g_mmio_base + offset + 12);
		pr_err("0x%04x | %08x %08x %08x %08x\n", offset, reg1, reg2, reg3, reg4);
		offset += 0x10;
	}

	offset = 0x200;
	reg1 = __raw_readl(g_mmio_base + PWM_PWM_SYSTEM_OFFS);
	reg2 = __raw_readl(g_mmio_base + PWM_PWM_GENB_OFFS);
	pr_err("0x%04x | %08x %08x\n", offset, reg1, reg2);

	offset = 0x220;
	reg1 = __raw_readl(g_mmio_base + PWM_PWM_INTCONFIG_OFFS);
	reg2 = __raw_readl(g_mmio_base + PWM_PWM_INTMASK_OFFS);
	reg3 = __raw_readl(g_mmio_base + PWM_PWM_INTSTATUS_OFFS);
	pr_err("0x%04x | %08x %08x %08x\n", offset, reg1, reg2, reg3);

	pwm_usecount--;
#if IS_ENABLED(CONFIG_PM_RUNTIME)
	pm_runtime_put_sync(&(gpwm[0]->pdev->dev));
#else
	if (!pwm_usecount)
		al_pwm_runtime_suspend(&(gpwm[0]->pdev->dev));
#endif
	debug("%s: usecount=%d\n", __func__, pwm_usecount);
}

static ssize_t applitepwm_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	struct pwm_device *pwm;
	char		s1[BUF_SIZE];
	int		duty = 0;
	int		period = 0;
	char		label[BUF_SIZE];
	unsigned int	pwm_id = 0;
	unsigned int	use_count = 0;
	unsigned int	iteration = 0;
	unsigned int	div = 0;
	unsigned int	pol = 0;
	unsigned int	lvs = 0;
	unsigned int	enbsel = 0;
	unsigned int	genb_set = 0;

	/* method/duty/period/pwm_id/iteration/enbsel/pol/lvs/div/use_count/genb_set/label */
	sscanf(buf, "%s", s1);

	if (strcmp(s1, "pwm_help") == 0) {
		pr_err("Usage:${cmd} ${duty} ${period} ${pwm_id}\n");
		pr_err("             ${iteration} ${enbsel} ${pol}\n");
		pr_err("             ${lvs} ${div} ${use_count}\n");
		pr_err("             ${genb_set} ${label}\n");
		pr_err("\n  ${cmd} - pwm_request\n");
		pr_err("           pwm_config\n");
		pr_err("           pwm_enable\n");
		pr_err("           pwm_disable\n");
		pr_err("           pwm_free\n");
	} else {
		sscanf(buf, "%s%d%d%d%d%d%d%d%d%d%d%s",
			s1, &duty, &period, &pwm_id, &iteration,
			&enbsel, &pol, &lvs, &div, &use_count, &genb_set, label);
		if (pwm_id < PWM_NUM) {
			pwm = gpwm[pwm_id];
			pwm->label = label;
			pwm->iteration = iteration;
			pwm->enbsel = enbsel;
			pwm->pol = pol;
			pwm->lvs = lvs;
			pwm->div = div;
			pwm->use_count = use_count;
			pwm->genb_set = genb_set;
			pr_info("pwm_id=%d\n", pwm_id);

			if (strcmp(s1, "pwm_config") == 0) {
				pr_err("call pwm_config\n");
				pwm_config(pwm, duty, period);
			} else if (strcmp(s1, "pwm_request") == 0) {
				pr_err("call pwm_request\n");
				pwm_request(pwm_id, label);
			} else if (strcmp(s1, "pwm_free") == 0) {
				pr_err("call pwm_free\n");
				pwm_free(pwm);
			} else if (strcmp(s1, "pwm_enable") == 0) {
				pr_err("call pwm_enable\n");
				pwm_enable(pwm);
			} else if (strcmp(s1, "pwm_disable") == 0) {
				pr_err("call pwm_disable\n");
				pwm_disable(pwm);
			} else if (strcmp(s1, "reg_dump") == 0) {
				pr_err("call reg_dump\n");
				applitepwm_reg_dump();
			} else {
				pr_err("Please specified first arg from pwm_config or pwm_request or pwm_free or pwm_enable or pwm_disable or reg_dump\n");
				pr_err("specified parameter is method/duty/period/pwm_id/iteration/enbsel/pol/lvs/div/use_count/genb_set/label\n");
				pr_err("exsample#echo \"pwm_config 1 10 1 0 0 0 0 0 0 0 label_name\" > /sys/kernel/pwm/applitepwm\n");
			}
		} else
			pr_err("parameter(pwm_id) error.(%d)\n", pwm_id);
	}
	return strlen(buf);
}


static struct kobj_attribute pwm_attribute = __ATTR(applitepwm, 0666, NULL, applitepwm_store);

static struct attribute *attrs[] = {
	&pwm_attribute.attr,
	NULL,
};


static struct attribute_group attr_group = {
	.attrs = attrs,
};


static int pwm_sysfs_init(void)
{
	int retval;

	pwm_kobj = kobject_create_and_add("pwm", kernel_kobj);
	if (!pwm_kobj)
		return -ENOMEM;

	retval = sysfs_create_group(pwm_kobj, &attr_group);
	if (retval)
		kobject_put(pwm_kobj);

	return retval;
}

static void pwm_sysfs_exit(void)
{
	kobject_put(pwm_kobj);
}
#endif


static int __devinit al_pwm_probe(struct platform_device *pdev)
{
	struct resource *r, *r2;
	int ret = 0, i = 0, retval;
	unsigned int irq = 0;
	struct clk *clk = NULL;

	pwm_genb = 0;
	genb_set_status = 0;
	pwm_usecount = 0;

	clk = clk_get(&(pdev->dev), NULL);
	if (IS_ERR(clk)) {
		dev_err(&pdev->dev, "failed clk_get(%s, NULL)\n",
						dev_name(&pdev->dev));
		return -EFAULT;
	}

	for (i = 0; i < PWM_NUM; i++) {
		gpwm[i] = kzalloc(sizeof(struct pwm_device), GFP_KERNEL);
		if (gpwm[i] == NULL) {
			dev_err(&pdev->dev, "failed to allocate memory\n");
			clk_put(clk);
			return -ENOMEM;
		}

		gpwm[i]->use_count = 0;
		gpwm[i]->pwm_id = i;
		gpwm[i]->pdev = pdev;
		gpwm[i]->clk = clk;
	}

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (r == NULL) {
		dev_err(&pdev->dev, "no memory resource defined\n");
		ret = -EBUSY;
		goto err_free;
	}

	r = request_mem_region(r->start, resource_size(r), pdev->name);
	if (r == NULL) {
		dev_err(&pdev->dev, "failed to request memory resource\n");
		ret = -EBUSY;
		goto err_free;
	}

	gpwm[0]->mmio_base = ioremap(r->start, resource_size(r));
	if (gpwm[0]->mmio_base == NULL) {
		dev_err(&pdev->dev, "failed to ioremap() registers\n");
		ret = -ENOMEM;
		goto err_free_mem;
	}

	r2 = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (r2 == NULL) {
		dev_err(&pdev->dev, "no memory resource defined\n");
		ret = -EBUSY;
		goto err_free_mem2;
	}

	gpwm[0]->pmu_base = ioremap(r2->start, resource_size(r2));
	if (gpwm[0]->pmu_base == NULL) {
		dev_err(&pdev->dev, "failed to ioremap() registers\n");
		ret = -ENOMEM;
		goto err_free_mem3;
	}
	for (i = 1; i < PWM_NUM; i++)
		gpwm[i]->mmio_base = gpwm[0]->mmio_base;

	mutex_lock(&pwm_lock);
	for (i = 0; i < PWM_NUM; i++)
		list_add_tail(&gpwm[i]->node, &pwm_list);
	mutex_unlock(&pwm_lock);

	/* irq setup after old hardware state is cleaned up */
	irq = platform_get_irq(pdev, 0);
	retval = request_irq(irq, pwm_handle_interrupts,
				0, driver_name, gpwm[0]);
	if (retval != 0) {
		pr_err("%s: can't get irq %i, err %d\n", driver_name, irq, retval);
		retval = -EBUSY;
		goto err_free_mem4;
	}

	genb_set_status = GENB_STATUS_READY;
#ifdef APPLITE_PWM_SYSFS
	g_mmio_base = gpwm[0]->mmio_base;
	pwm_sysfs_init();
#endif

	debug("%s: enable call\n", __func__);
	pm_runtime_enable(&(pdev->dev));
	al_pwm_hw_init();

	return 0;

err_free_mem4:
	iounmap(gpwm[0]->pmu_base);
err_free_mem3:
err_free_mem2:
	iounmap(gpwm[0]->mmio_base);
err_free_mem:
	release_mem_region(r->start, resource_size(r));
err_free:
	for (i = 0; i < PWM_NUM; i++) {
		if (gpwm[i] != NULL)
			kfree(gpwm[i]);
	}
	clk_put(clk);
	return ret;
}

static int __devexit al_pwm_remove(struct platform_device *pdev)
{
	struct resource *r;
	int ret = 0, i = 0;
	unsigned int pwm_sr_read = 0;

	if (gpwm[0] == NULL)
		return -ENODEV;

#if IS_ENABLED(CONFIG_PM_RUNTIME)
	pm_runtime_get_sync(&(pdev->dev));
#else
	al_pwm_runtime_resume(&(pdev->dev));
#endif
	__raw_writel(0x1, (gpwm[0]->mmio_base + PWM_PWM_SYSTEM_OFFS));

	for (i = 0; i < 10; i++) {
		pwm_sr_read = __raw_readl((gpwm[0]->mmio_base + PWM_PWM_SYSTEM_OFFS));
#if IS_ENABLED(CONFIG_ARCH_TZ2000)
		if (!(pwm_sr_read & PWM_PWM_SYSTEM_SWRST_MASK))
#endif
#if IS_ENABLED(CONFIG_ARCH_TZ3000)
		if (!(pwm_sr_read & PWM_PWM_SYSTEM_COUNT_MASK))
#endif
			break;
		mdelay(100);
	}

#if IS_ENABLED(CONFIG_PM_RUNTIME)
	pm_runtime_put_sync(&(pdev->dev));
#else
	al_pwm_runtime_suspend(&(pdev->dev));
#endif

	debug("%s: disable call\n", __func__);
	pm_runtime_disable(&(pdev->dev));
	clk_put(gpwm[0]->clk);

	if (i == 10) {
		pr_err("al_pwm_remove() failed to soft reset\n");
		ret = -EIO;
	}

	free_irq(platform_get_irq(pdev, 0), gpwm[0]);

	mutex_lock(&pwm_lock);
	for (i = 0; i < PWM_NUM; i++)
		list_del(&gpwm[i]->node);
	mutex_unlock(&pwm_lock);

	iounmap(gpwm[0]->mmio_base);
	iounmap(gpwm[0]->pmu_base);

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(r->start, resource_size(r));
	r = platform_get_resource(pdev, IORESOURCE_MEM, 1);

	for (i = 0; i < PWM_NUM; i++)
		kfree(gpwm[i]);

#ifdef APPLITE_PWM_SYSFS
	pwm_sysfs_exit();
#endif
	return ret;
}

static void al_pwm_hw_init(void)
{
#if IS_ENABLED(CONFIG_ARCH_TZ2000)
	__u32 tmp;
#endif
#if IS_ENABLED(CONFIG_ARCH_TZ2000)
	unsigned int intmask = 0x1f;
#endif
#if IS_ENABLED(CONFIG_ARCH_TZ3000)
	unsigned int intmask = 0x3f;
#endif

	debug("%s: start\n", __func__);
	/* reset assert */
	__raw_writel(1, (gpwm[0]->pmu_base + PMU_SOFTRESETON_PERISS_1_OFS));
	/* clock on */
	clk_prepare_enable(gpwm[0]->clk);
	debug("\tClockGatingOff:%d\n",
		__raw_readl(gpwm[0]->pmu_base+PMU_CLOCKGATINGOFF_PERISS_1_OFS)&0x01);
#if IS_ENABLED(CONFIG_ARCH_TZ2000)
	/* VDD33_IOA */
	tmp = __raw_readl(gpwm[0]->pmu_base + PMU_POREN_OFS);
	tmp |= PMU_POREN_POREN_TOP_IOA_MASK;
	__raw_writel(tmp, (gpwm[0]->pmu_base + PMU_POREN_OFS));
	/* 100ns wait */
	ndelay(100);
#endif

	/* reset negate */
	__raw_writel(1, (gpwm[0]->pmu_base + PMU_SOFTRESETOFF_PERISS_1_OFS));

	/* set interrupt mask */
	__raw_writel(intmask, (gpwm[0]->mmio_base + PWM_PWM_INTMASK_OFFS));

	clk_disable_unprepare(gpwm[0]->clk);
	debug("\tClockGatingOn:%d\n",
		__raw_readl(gpwm[0]->pmu_base+PMU_CLOCKGATINGON_PERISS_1_OFS)&0x01);
}

static int al_pwm_suspend(struct device *dev)
{
	debug("%s: start usecount=%d\n", __func__, pwm_usecount);
	if (pwm_usecount > 0)
		return -EBUSY;

	return 0;
}

static int al_pwm_resume(struct device *dev)
{
	debug("%s: start\n", __func__);
	al_pwm_hw_init();
	return 0;
}

static int al_pwm_runtime_suspend(struct device *dev)
{
	debug("%s: start\n", __func__);
	clk_disable_unprepare(gpwm[0]->clk);
	debug("\tClockGatingOn:%d\n",
		__raw_readl(gpwm[0]->pmu_base+PMU_CLOCKGATINGON_PERISS_1_OFS)&0x01);
	return 0;
}

static int al_pwm_runtime_resume(struct device *dev)
{
	debug("%s: start\n", __func__);
	clk_prepare_enable(gpwm[0]->clk);
	debug("\tClockGatingOff:%d\n",
		__raw_readl(gpwm[0]->pmu_base+PMU_CLOCKGATINGOFF_PERISS_1_OFS)&0x01);
	return 0;
}

static const struct dev_pm_ops al_pwm_pm_ops = {
	.suspend = al_pwm_suspend,
	.resume = al_pwm_resume,
	.runtime_suspend = al_pwm_runtime_suspend,
	.runtime_resume = al_pwm_runtime_resume,
};

static struct platform_driver al_pwm_driver = {
	.driver		= {
		.name	= "applite-pwm",
		.owner = THIS_MODULE,
		.pm	= &al_pwm_pm_ops,
	},
	.probe		= al_pwm_probe,
	.remove		= __devexit_p(al_pwm_remove),
};


static int __init al_pwm_init(void)
{
	return platform_driver_register(&al_pwm_driver);
}
arch_initcall(al_pwm_init);

static void __exit al_pwm_exit(void)
{
	platform_driver_unregister(&al_pwm_driver);
}
module_exit(al_pwm_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("TOSHIBA Corporation");
