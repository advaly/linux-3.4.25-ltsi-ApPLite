/*
 * Toshiba TC90431 SPI Controller driver
 *
 *  (C) Copyright TOSHIBA CORPORATION SEMICONDUCTOR COMPANY 2010
 * (C) Copyright TOSHIBA CORPORATION
 *      SEMICONDUCTOR & STORAGE PRODUCTS COMPANY 2013
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include <linux/errno.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/platform_data/spi-tc90431.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/jiffies.h>
#include <linux/spi/spi.h>
#include <linux/spi/tc90431.h>
#include <linux/io.h>
#include <mach/platform.h>

#define DRV_VERSION "1.4"
#define DRV_DEVNAME "tc90431_spi"
static const char tc90431_spi_driver_name[] = DRV_DEVNAME;
static const char tc90431_spi_driver_version[] = DRV_VERSION;
static const char *print_version =
	"TC90431 SPI controller driver: ver" DRV_VERSION;

#ifdef CONFIG_SPI_TC90431_DEBUG
#define DBG(x...) printk(x)
#else
#define DBG(x...)
#endif

#define DIR_BASE		0x000
#define DIR_MMAP(ch)		(DIR_BASE + 0x000 + (ch) * 0x4)
#define DIR_CNTL(ch)		(DIR_BASE + 0x008 + (ch) * 0x4)
#define DIR_RDCNTL(ch)		(DIR_BASE + 0x010 + (ch) * 0x4)

#define PRG_BASE		0x400
#define PRG_CNTL0		(PRG_BASE + 0x000)
#define PRG_CNTL1		(PRG_BASE + 0x004)
#define PRG_INTEN		(PRG_BASE + 0x008)
#define PRG_STAT		(PRG_BASE + 0x00c)
#define PRG_PRIBUF		(PRG_BASE + 0x100)
#define PRG_SECBUF		(PRG_BASE + 0x200)

#define PRIBUF_SIZE		8
#define SECBUF_SIZE		256
#define PRIBUF_XFERSIZE(len)	(((len) - 1) << 16)
#define SECBUF_XFERSIZE(len)	(((len) - 1) << 24)
#define PRIBUF_ENABLE		0x00000010
#define SECBUF_ENABLE		0x00000020

#define XFER_START		0x00000001
#define XFER_INPROGRESS		0x00000002
#define XFER_DONE		0x00000001

#define CHIPSELECT(ch)	((ch) << 1)

#define SDCE(sdce)		((sdce) << 4)
#define POSEDGE			0x0
#define NEGEDGE			0x1
#define SCSD(scsd)		((scsd) << 8)
#define MAX_SCSD		0xff
#define SPR(spr)		((spr) << 16)
#define SPR_MAX			0x1f
#define SCSD_SPR_MASK		0x001fff00
#define NSEC_TO_SCSD(nsec, clk) \
	((((nsec) * 1000) / (1000000000 / ((clk) / 10)) + 99) / 100)

#define FDEN(fden)		((fden) << 2)
#define FBA_FDEN_MASK		0x07ff003c
#define DIRACCESS_ENABLE	0x1

#define RDCNTL_MASK		0xff00f8fc
#define ADDRBYTECNT		0x00000800
#define RDCMD(cmd)		((cmd) << 24)
#define DMYCNT(cnt)		((cnt) << 12)
#define DATA_SINGLE		0x00
#define DMMY_SINGLE		0x00
#define ADDR_SINGLE		0x00
#define DATA_DUAL		0x40
#define DMMY_DUAL		0x10
#define ADDR_DUAL		0x04
#define DATA_QUAD		0x80
#define DMMY_QUAD		0x20
#define ADDR_QUAD		0x08

#define INT_ENABLE		0x1
#define STAT_ALLCLEAR		0x0

#define TC90431_SPIC_MAX_CHIPSELECT	2
#define TC90431_SPIC_MAX_WAIT		100	/* msec */

struct tc90431_spi {
	void __iomem *iobase;
	struct resource *ioarea;
	u8 cs;
	u8 spr;
	u16 scsd;
#if IS_ENABLED(CONFIG_MTD_M25P80)
	u8 init_direct[TC90431_SPIC_MAX_CHIPSELECT];
#ifdef CONFIG_PM
	struct {
		u32 dir_mmap;
		u32 dir_cntl;
		u32 dir_rdcntl;
	} saved[TC90431_SPIC_MAX_CHIPSELECT];
#endif
#endif
	struct platform_device *pdev;
	struct mutex bus_lock; /* mutex */

	struct workqueue_struct *workqueue;
	struct work_struct work;

	struct list_head queue;
	spinlock_t lock; /* spinlock */

};

static ssize_t tc90431_spi_dump_regs(struct device *pdev,
				     struct device_attribute *attr, char *buf)
{
	unsigned int i, len = 0;
	struct spi_master *master = container_of(pdev, struct spi_master, dev);
	struct tc90431_spi *c = spi_master_get_devdata(master);

	len +=
	    sprintf(buf + len, "mmap0       : 0x%08x\n",
		    readl(c->iobase + DIR_MMAP(0)));
	len +=
	    sprintf(buf + len, "mmap1       : 0x%08x\n",
		    readl(c->iobase + DIR_MMAP(1)));
	len +=
	    sprintf(buf + len, "dir_cntl0   : 0x%08x\n",
		    readl(c->iobase + DIR_CNTL(0)));
	len +=
	    sprintf(buf + len, "dir_cntl1   : 0x%08x\n",
		    readl(c->iobase + DIR_CNTL(1)));
	len +=
	    sprintf(buf + len, "dir_rdcntl0 : 0x%08x\n",
		    readl(c->iobase + DIR_RDCNTL(0)));
	len +=
	    sprintf(buf + len, "dir_rdcntl1 : 0x%08x\n",
		    readl(c->iobase + DIR_RDCNTL(1)));
	len +=
	    sprintf(buf + len, "prg_cntl0   : 0x%08x\n",
		    readl(c->iobase + PRG_CNTL0));
	len +=
	    sprintf(buf + len, "prg_cntl1   : 0x%08x\n",
		    readl(c->iobase + PRG_CNTL1));
	len +=
	    sprintf(buf + len, "inten       : 0x%08x\n",
		    readl(c->iobase + PRG_INTEN));
	len +=
	    sprintf(buf + len, "stat        : 0x%08x\n",
		    readl(c->iobase + PRG_STAT));

	len += sprintf(buf + len, "pribuf      :\n");
	for (i = 0; i < PRIBUF_SIZE; i++) {
		len += sprintf(buf + len, "%02x ",
			       readb(c->iobase + PRG_PRIBUF + i));
	}
	len += sprintf(buf + len, "\n");

	len += sprintf(buf + len, "secbuf      :\n");
	for (i = 0; i < SECBUF_SIZE; i++) {
		len += sprintf(buf + len, "%02x ",
			       readb(c->iobase + PRG_SECBUF + i));
		if ((i % 16) == 15)
			len += sprintf(buf + len, "\n");
	}

	return len;
}

static DEVICE_ATTR(hw_regs, S_IRUGO, tc90431_spi_dump_regs, NULL);

#if IS_ENABLED(CONFIG_MTD_M25P80)
static int tc90431_spi_setup_direct_access(struct spi_device *spi)
{
	int i;
	u32 max_hz;
	struct tc90431_spi *c = spi_master_get_devdata(spi->master);
	struct tc90431_spi_controller_data *data = spi->controller_data;
	struct spi_tc90431_platform_data *pdata = c->pdev->dev.platform_data;
	u8 fden;
	u8 dir_spr;
	u16 dir_scsd;
	u32 r;

	/* setup flash density */
	for (fden = 0; fden <= 0x0f; fden++) {
		if (data->dir_read_size <= SZ_64K << fden)
			break;
	}

	DBG("%s: [dir] ch=%d fden=0x%x\n", __func__, c->cs, fden);

	r = ((data->dir_read_phys | FDEN(fden)) & FBA_FDEN_MASK) |
		DIRACCESS_ENABLE;
	writel(r, c->iobase + DIR_MMAP(c->cs));

	/* setup baudrate */
	max_hz = data->dir_max_speed_hz > pdata->max_hz ?
		pdata->max_hz : data->dir_max_speed_hz;

	for (i = 0; i <= SPR_MAX; i++) {
		if (max_hz >= pdata->baud_clock / (i + 1)) {
			dir_spr = i;
			break;
		}
	}
	if (i > SPR_MAX)
		dir_spr = SPR_MAX;

	/* setup chip select deassert time */
	dir_scsd = NSEC_TO_SCSD(data->dir_deassert_time, pdata->hbus_clock);
	if (dir_scsd > MAX_SCSD)
		dir_scsd = MAX_SCSD;

	DBG("%s: [dir] ch=%d spr=0x%x scsd=%d opcode=0x%x dummy=%d\n",
	    __func__, c->cs, dir_spr, dir_scsd,
	    data->dir_read_opcode, data->dir_read_dummy_count);

	r = readl(c->iobase + DIR_CNTL(c->cs)) & ~SCSD_SPR_MASK;
	r |= SCSD(dir_scsd) | SPR(dir_spr);
	writel(r, c->iobase + DIR_CNTL(c->cs));

	r = readl(c->iobase + DIR_RDCNTL(c->cs)) & ~RDCNTL_MASK;
	if (data->dir_read_size > SZ_16M)
		r |= ADDRBYTECNT;
	r |= RDCMD(data->dir_read_opcode) | DMYCNT(data->dir_read_dummy_count);
	switch (data->dir_read_opcode) {
	case OPCODE_FAST_READ_SINGLE:
		r |= DATA_SINGLE | DMMY_SINGLE | ADDR_SINGLE;
		break;
	case OPCODE_FAST_READ_DUAL_OUTPUT:
		r |= DATA_DUAL | DMMY_SINGLE | ADDR_SINGLE;
		break;
	case OPCODE_FAST_READ_DUAL_IO:
		r |= DATA_DUAL | DMMY_DUAL | ADDR_DUAL;
		break;
	case OPCODE_FAST_READ_QUAD_OUTPUT:
		r |= DATA_QUAD | DMMY_SINGLE | ADDR_SINGLE;
		break;
	case OPCODE_FAST_READ_QUAD_IO:
		r |= DATA_QUAD | DMMY_QUAD | ADDR_QUAD;
		break;
	default:
		dev_err(&spi->dev, "%s: Not supported operation: op=0x%02x\n",
			__func__, data->dir_read_opcode);
		return -EINVAL;
	}
	writel(r, c->iobase + DIR_RDCNTL(c->cs));
	return 0;
}
#endif

static int tc90431_spi_setup(struct spi_device *spi)
{
	int i;
	u32 max_hz;
	struct tc90431_spi *c = spi_master_get_devdata(spi->master);
	struct tc90431_spi_controller_data *data = spi->controller_data;
	struct spi_tc90431_platform_data *pdata = c->pdev->dev.platform_data;

	/* setup baudrate */
	max_hz = (spi->max_speed_hz > pdata->max_hz) ?
		pdata->max_hz : spi->max_speed_hz;

	for (i = 0; i <= SPR_MAX; i++) {
		if (max_hz >= pdata->baud_clock / (i + 1)) {
			c->spr = i;
			break;
		}
	}
	if (i > SPR_MAX)
		c->spr = SPR_MAX;

	/* setup chip select deassert time */
	c->scsd = NSEC_TO_SCSD(data->deassert_time, pdata->hbus_clock);
	if (c->scsd > MAX_SCSD)
		c->scsd = MAX_SCSD;

	/* update current chip select */
	c->cs = spi->chip_select;

#if IS_ENABLED(CONFIG_MTD_M25P80)
	if (!c->init_direct[c->cs] && data->dir_read_opcode) {
		int ret = tc90431_spi_setup_direct_access(spi);
		if (ret < 0)
			return ret;
		c->init_direct[c->cs] = 1;
	}
#endif
	return 0;
}

static void tc90431_spi_cleanup(struct spi_device *spi)
{
#if IS_ENABLED(CONFIG_MTD_M25P80)
	struct tc90431_spi *c = spi_master_get_devdata(spi->master);
	int i;
	for (i = 0; i < TC90431_SPIC_MAX_CHIPSELECT; i++)
		c->init_direct[i] = 0;

#endif
}

static int tc90431_spi_wait_done(struct tc90431_spi *c)
{
	unsigned long timeout;
	unsigned long tmp;

	timeout = jiffies + msecs_to_jiffies(TC90431_SPIC_MAX_WAIT);

	while (1) {
		tmp = jiffies;
		if (!(readl(c->iobase + PRG_STAT) & XFER_INPROGRESS))
			return 0;
		if (time_after(tmp, timeout))
			break;
		DBG("BUSY\n");
		cond_resched();
	}

	return 1;
}

static void tc90431_spi_set_data(struct tc90431_spi *c, u32 reg, u8 *buf,
				 u32 len, u32 offset)
{
	int i;
	void __iomem *p = c->iobase + reg + offset;

	for (i = 0; i < len; i++)
		writeb(*buf++, p + i);
}

static void tc90431_spi_get_data(struct tc90431_spi *c, u32 reg, u8 *buf,
				 u32 len, u32 offset)
{
	int i;
	void __iomem *p = c->iobase + reg + offset;

	for (i = 0; i < len; i++)
		*buf++ = readb(p + i);
}

static int tc90431_spi_do_one_msg(struct spi_message *m)
{
	struct spi_device *spi = m->spi;
	int status = 0;
	u32 r = 0;
	u32 first_check = 0, first_len = 0, index = 0;
	struct spi_master *master = spi->master;
	struct tc90431_spi *c = spi_master_get_devdata(master);
	struct spi_transfer *t;

	mutex_lock(&c->bus_lock);

	m->actual_length = 0;

	/* call setup again when the chipselect was changed */
	if (spi->chip_select != c->cs) {
		status = master->setup(spi);
		if (status < 0)
			goto exit;
	}

	/* set data register */
	list_for_each_entry(t, &m->transfers, transfer_list) {
		/* use the primary buffer only when the first transfer is
		   transmission and 8 bytes or less */
		if (first_check == 0) {
			first_check = 1;
			if (t->tx_buf && (t->len < PRIBUF_SIZE)) {
				tc90431_spi_set_data(c, PRG_PRIBUF,
						     (u8 *)t->tx_buf, t->len,
						     0);
				first_len = t->len;
				continue;
			}
		}

		if (t->len) {
			if ((index + t->len) > SECBUF_SIZE) {
				dev_err(&spi->dev, "%s: Message size too big\n",
					__func__);
				status = -EINVAL;
				goto exit;
			}

			if (t->tx_buf) {
				tc90431_spi_set_data(c, PRG_SECBUF,
						     (u8 *)t->tx_buf, t->len,
						     index);
				index += t->len;
			} else if (t->rx_buf) {
				index += t->len;
			} else {
				dev_err(&spi->dev, "%s: No message prepared\n",
					__func__);
				status = -EINVAL;
				goto exit;
			}
		}
	}

	if (first_len == 0 && index == 0)
		goto exit;

	/* set control register 0 */
	r = readl(c->iobase + PRG_CNTL0) & ~SCSD_SPR_MASK;
	r |= SCSD(c->scsd) | SPR(c->spr);
	writel(r, c->iobase + PRG_CNTL0);

	/* set control register 1 */
	r = 0;
	if (first_len > 0)
		r |= PRIBUF_ENABLE | PRIBUF_XFERSIZE(first_len);

	if (index > 0)
		r |= SECBUF_ENABLE | SECBUF_XFERSIZE(index);

	r |= CHIPSELECT(c->cs) | XFER_START;

	DBG("%s: [transfer params] ", __func__);
	DBG("ch=%d, scsd=%d, spr=0x%02x, ", c->cs, c->scsd, c->spr);
	DBG("first_len=%d, second_len=%d\n", first_len, index);

	writel(r, c->iobase + PRG_CNTL1);

	if (tc90431_spi_wait_done(c)) {
		dev_err(&spi->dev, "%s: Wait idle timeout\n", __func__);
		status = -EIO;
		goto exit;
	}

	/* get data from data register */
	index = 0;
	list_for_each_entry(t, &m->transfers, transfer_list) {
		if (first_check == 1) {
			first_check = 0;
			if (first_len > 0)
				continue;
		}

		if (t->len) {
			if (t->rx_buf) {
				tc90431_spi_get_data(c, PRG_SECBUF,
						     (u8 *)t->rx_buf, t->len,
						     index);
				index += t->len;
			} else if (t->tx_buf) {
				index += t->len;
			} else {
				dev_err(&spi->dev, "%s: No message prepared\n",
					__func__);
				status = -EINVAL;
				goto exit;
			}
		}
	}

	m->actual_length = first_len + index;

exit:
	DBG("%s:[transfer result] status=%d, actual_length=%d\n", __func__,
	    status, m->actual_length);
	m->status = status;
	m->complete(m->context);


	mutex_unlock(&c->bus_lock);

	return status;
}

static void tc90431_spi_work(struct work_struct *work)
{
	struct tc90431_spi *c = container_of(work, struct tc90431_spi, work);

	spin_lock_irq(&c->lock);
	while (!list_empty(&c->queue)) {
		struct spi_message *m =
		    container_of(c->queue.next, struct spi_message, queue);

		list_del_init(&m->queue);
		spin_unlock_irq(&c->lock);

		tc90431_spi_do_one_msg(m);

		spin_lock_irq(&c->lock);
	}
	spin_unlock_irq(&c->lock);
}

static int tc90431_spi_transfer(struct spi_device *spi, struct spi_message *m)
{
	struct tc90431_spi *c = spi_master_get_devdata(spi->master);
	unsigned long flags;

	m->actual_length = 0;
	m->status = -EINPROGRESS;

	spin_lock_irqsave(&c->lock, flags);
	list_add_tail(&m->queue, &c->queue);
	queue_work(c->workqueue, &c->work);
	spin_unlock_irqrestore(&c->lock, flags);

	return 0;
}

static void tc90431_spi_hw_init(struct tc90431_spi *c)
{
	int i;
	u32 r;

	for (i = 0; i < TC90431_SPIC_MAX_CHIPSELECT; i++) {
		r = readl(c->iobase + DIR_MMAP(i)) & ~DIRACCESS_ENABLE;
		writel(r, c->iobase + DIR_MMAP(i));
	}
	writel(readl(c->iobase + PRG_CNTL0) | SDCE(NEGEDGE),
	       c->iobase + PRG_CNTL0);
	writel(readl(c->iobase + PRG_INTEN) & ~INT_ENABLE,
	       c->iobase + PRG_INTEN);
	writel(STAT_ALLCLEAR, c->iobase + PRG_STAT);
}

static int tc90431_spi_probe(struct platform_device *pdev)
{
	struct tc90431_spi *c;
	struct spi_master *master;
	struct resource *res;
	int ret;

	pr_info("%s.%d: %s\n", DRV_DEVNAME, pdev->id, print_version);

	master = spi_alloc_master(&pdev->dev, sizeof(struct tc90431_spi));
	if (master == NULL) {
		dev_err(&pdev->dev, "%s: No memory for spi_master\n", __func__);
		ret = -ENOMEM;
		goto err_out;
	}

	c = spi_master_get_devdata(master);
	c->pdev = pdev;

	master->bus_num = pdev->id;
	master->num_chipselect = TC90431_SPIC_MAX_CHIPSELECT;
	master->setup = tc90431_spi_setup;
	master->cleanup = tc90431_spi_cleanup;
	master->transfer = tc90431_spi_transfer;
	master->max_xfer_len = SECBUF_SIZE;

	mutex_init(&c->bus_lock);
	platform_set_drvdata(pdev, master);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "%s: cannot get resource\n", __func__);
		ret = -ENOENT;
		goto err_alloc_master;
	}

	c->ioarea =
	    request_mem_region(res->start, resource_size(res), pdev->name);
	if (c->ioarea == NULL) {
		dev_err(&pdev->dev, "%s: cannot request IO area\n", __func__);
		ret = -ENXIO;
		goto err_out;
	}

	c->iobase = ioremap(res->start, resource_size(res));
	if (c->iobase == NULL) {
		dev_err(&pdev->dev, "%s: cannot map IO\n", __func__);
		ret = -ENXIO;
		goto err_ioarea;
	}

	tc90431_spi_hw_init(c);

	spin_lock_init(&c->lock);
	INIT_WORK(&c->work, tc90431_spi_work);
	INIT_LIST_HEAD(&c->queue);
	c->workqueue =
	    create_singlethread_workqueue(dev_name(master->dev.parent));
	if (c->workqueue == NULL) {
		ret = -EBUSY;
		goto err_iomap;
	}

	ret = spi_register_master(master);
	if (ret < 0) {
		dev_err(&pdev->dev,
			"%s: cannot register spi_master, ret = %d\n", __func__,
			ret);
		goto err_wq;
	}

	ret = device_create_file(&master->dev, &dev_attr_hw_regs);
	if (ret < 0) {
		dev_err(&pdev->dev,
			"%s: class_device_create_file return fail, ret = %d\n",
			__func__, ret);
		goto err_register_master;
	}

	return 0;

err_register_master:
	spi_unregister_master(master);

err_wq:
	destroy_workqueue(c->workqueue);

err_iomap:
	iounmap(c->iobase);

err_ioarea:
	release_resource(c->ioarea);
	kfree(c->ioarea);

err_alloc_master:
	spi_master_put(master);

err_out:

	return ret;
}

static int tc90431_spi_remove(struct platform_device *pdev)
{
	struct spi_master *master = spi_master_get(platform_get_drvdata(pdev));
	struct tc90431_spi *c = spi_master_get_devdata(master);

	platform_set_drvdata(pdev, NULL);

	flush_workqueue(c->workqueue);
	destroy_workqueue(c->workqueue);

	spi_unregister_master(master);

	iounmap(c->iobase);

	release_resource(c->ioarea);
	kfree(c->ioarea);

	spi_master_put(master);

	return 0;
}

#ifdef CONFIG_PM
static int tc90431_spi_suspend(struct device *dev)
{
#if IS_ENABLED(CONFIG_MTD_M25P80)
	struct spi_master *master =
		platform_get_drvdata(to_platform_device(dev));
	struct tc90431_spi *c = spi_master_get_devdata(master);
	int i;

	dev_dbg(dev, "suspend\n");
	for (i = 0; i < TC90431_SPIC_MAX_CHIPSELECT; i++) {
		c->saved[i].dir_mmap = readl(c->iobase + DIR_MMAP(i));
		c->saved[i].dir_cntl = readl(c->iobase + DIR_CNTL(i));
		c->saved[i].dir_rdcntl = readl(c->iobase + DIR_RDCNTL(i));
		writel(c->saved[i].dir_mmap & ~DIRACCESS_ENABLE,
		       c->iobase + DIR_MMAP(i));
	}
#endif
	return 0;
}

static int tc90431_spi_resume(struct device *dev)
{
	struct spi_master *master =
		platform_get_drvdata(to_platform_device(dev));
	struct tc90431_spi *c = spi_master_get_devdata(master);
#if IS_ENABLED(CONFIG_MTD_M25P80)
	int i;
#endif

	dev_dbg(dev, "resume\n");
	tc90431_spi_hw_init(c);
#if IS_ENABLED(CONFIG_MTD_M25P80)
	for (i = 0; i < TC90431_SPIC_MAX_CHIPSELECT; i++) {
		writel(c->saved[i].dir_mmap, c->iobase + DIR_MMAP(i));
		writel(c->saved[i].dir_cntl, c->iobase + DIR_CNTL(i));
		writel(c->saved[i].dir_rdcntl, c->iobase + DIR_RDCNTL(i));
	}
#endif
	return 0;
}
#endif

static SIMPLE_DEV_PM_OPS(tc90431_spi_dev_pm_ops,
			 tc90431_spi_suspend, tc90431_spi_resume);

static struct platform_driver tc90431_spi_driver = {
	.probe = tc90431_spi_probe,
	.remove = tc90431_spi_remove,
	.driver = {
		.name = DRV_DEVNAME,
		.pm = &tc90431_spi_dev_pm_ops,
		.owner = THIS_MODULE,
	},
};

static int __init tc90431_spi_init(void)
{
	return platform_driver_register(&tc90431_spi_driver);
}

static void __exit tc90431_spi_exit(void)
{
	platform_driver_unregister(&tc90431_spi_driver);
}

MODULE_DESCRIPTION("Toshiba TC90431 SPI Driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);

module_init(tc90431_spi_init);
module_exit(tc90431_spi_exit);
