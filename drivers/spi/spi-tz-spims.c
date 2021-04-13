/*
 * Toshiba TZ3000/TZ2000 SPIMS Controller driver
 *
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

#include <linux/clk.h>
#include <linux/completion.h>
#include <linux/err.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/pm_runtime.h>
#include <linux/spi/spi.h>

#define DRV_NAME "spi-tz-spims"

#define SPIMS_RXDATA	0x00
#define SPIMS_TXDATA	0x04
#define SPIMS_SELECT	0x08
#define SPIMS_DIV	0x0c
#define SPIMS_ENABLE	0x10
#define SPIMS_FRAME	0x14
#define SPIMS_FIFOCLR	0x18
#define SPIMS_IC	0x1c
#define SPIMS_IE	0x20
#define SPIMS_IS	0x24
#define SPIMS_RXFIFONMB	0x28
#define SPIMS_TXFIFONMB	0x2c

#define SPIMS_SELECT_MASTER	0x00000001
#define SPIMS_SELECT_CPHA	0x00010000
#define SPIMS_SELECT_CPOL	0x00020000

#define SPIMS_FRAME_MSB		0x00000100
#define SPIMS_FRAME_SCSHOLD	0x00000200
#define SPIMS_FRAME_SCK		0x00010000
#define SPIMS_FRAME_SCS		0x00020000
#define SPIMS_FRAME_MODE	0x80000000

#define SPIMS_FIFOCLR_TX	0x00000001
#define SPIMS_FIFOCLR_RX	0x00000002

#define SPIMS_IS_INT		0x00000001
#define SPIMS_IS_RXUDF		0x00000100
#define SPIMS_IS_RXOVF		0x00000200
#define SPIMS_IS_TXUDF		0x00000400
#define SPIMS_IS_TXOVF		0x00000800

#define SPIMS_FIFO_MASK		0x000000ff

#define SPIMS_FIFO_SIZE	128

#define SPIMS_DIV_MAX	7
#define SPIMS_DIV_MIN	1

struct tz_spims {
	struct completion done;
	void __iomem *membase;
	int baseclk;
	struct clk *clk;
	u32 min_speed_hz;
	struct platform_device *pdev;
};

static u32 tz_spims_rd(struct tz_spims *c, int reg)
{
	return ioread32(c->membase + reg);
}

static void tz_spims_wr(struct tz_spims *c, u32 val, int reg)
{
	iowrite32(val, c->membase + reg);
}

static int tz_spims_setup(struct spi_device *spi)
{
	struct tz_spims *c = spi_master_get_devdata(spi->master);

	if (spi->max_speed_hz < c->min_speed_hz)
		return -EINVAL;
	return 0;
}

static int tz_spims_prepare_transfer(struct spi_master *master)
{
	struct tz_spims *c = spi_master_get_devdata(master);
	pm_runtime_get_sync(&c->pdev->dev);
	return 0;
}

static int tz_spims_unprepare_transfer(struct spi_master *master)
{
	struct tz_spims *c = spi_master_get_devdata(master);
	pm_runtime_mark_last_busy(&c->pdev->dev);
	pm_runtime_put_autosuspend(&c->pdev->dev);
	return 0;
}

static irqreturn_t tz_spims_interrupt(int irq, void *dev_id)
{
	struct tz_spims *c = dev_id;
	u32 stat = tz_spims_rd(c, SPIMS_IS);

	if (stat & SPIMS_IS_INT) {
		dev_dbg(&c->pdev->dev, "int %#x\n", stat);
		/* disable intr */
		tz_spims_wr(c, 0, SPIMS_IC);
		/* clear intr */
		tz_spims_wr(c, SPIMS_IS_INT, SPIMS_IS);
		complete(&c->done);
		return IRQ_HANDLED;
	}
	return IRQ_NONE;
}

static void tz_spims_configure(struct tz_spims *c, struct spi_device *spi,
			       u32 speed_hz, u8 bits_per_word)
{
	u32 div;
	u32 select = SPIMS_SELECT_MASTER;
	u32 frame = bits_per_word - 1;

	if (!(spi->mode & SPI_LSB_FIRST))
		frame |= SPIMS_FRAME_MSB;
	if (bits_per_word > 16)
		frame |= SPIMS_FRAME_MODE;
	frame |= SPIMS_FRAME_SCS | SPIMS_FRAME_SCSHOLD;
	if (spi->mode & SPI_CPOL)
		select |= SPIMS_SELECT_CPOL;
	if (spi->mode & SPI_CPHA)
		select |= SPIMS_SELECT_CPHA;
	for (div = SPIMS_DIV_MIN; div < SPIMS_DIV_MAX; div++)
		if (c->baseclk >> div <= speed_hz)
			break;
	tz_spims_wr(c, div, SPIMS_DIV);
	tz_spims_wr(c, frame, SPIMS_FRAME);
	tz_spims_wr(c, select, SPIMS_SELECT);
	dev_dbg(&spi->dev, "DIV:%#x,FRAME:%#x,SELECT:%#x\n",
		div, frame, select);
}

static void tz_spims_enable(struct tz_spims *c, struct spi_device *spi)
{
	dev_dbg(&spi->dev, "enable\n");
	tz_spims_wr(c, 1, SPIMS_ENABLE);
}

static int tz_spims_disable(struct tz_spims *c, struct spi_device *spi)
{
	int timeout = 100;

	dev_dbg(&spi->dev, "disable\n");
	tz_spims_wr(c, 0, SPIMS_ENABLE);
	while (tz_spims_rd(c, SPIMS_ENABLE) & 1) {
		if (timeout-- < 0) {
			dev_err(&spi->dev, "timeout waiting for disable\n");
			return -ETIMEDOUT;
		}
		mdelay(1);
	}
	return 0;
}

static void tz_spims_txdata(struct tz_spims *c,
			    const void *txbuf, unsigned int wsize)
{
	u32 data;

	if (txbuf) {
		if (wsize == 1)
			data = *(const u8 *)txbuf;
		else if (wsize == 2)
			data = *(const u16 *)txbuf;
		else
			data = *(const u32 *)txbuf;
	} else {
		data = 0;
	}
	tz_spims_wr(c, data, SPIMS_TXDATA);
}

static void tz_spims_rxdata(struct tz_spims *c,
			    void *rxbuf, unsigned int wsize)
{
	u32 data = tz_spims_rd(c, SPIMS_RXDATA);

	if (rxbuf) {
		if (wsize == 1)
			*(u8 *)rxbuf = data;
		else if (wsize == 2)
			*(u16 *)rxbuf = data;
		else
			*(u32 *)rxbuf = data;
	}
}

static int tz_spims_transfer_one_message(struct spi_master *master,
					 struct spi_message *msg)
{
	struct tz_spims *c = spi_master_get_devdata(master);
	struct spi_device *spi = msg->spi;
	struct spi_transfer *t;
	unsigned int cs_delay;
	unsigned int cs_change = 1;
	int status = 0;
	u32 prev_speed_hz = 0;
	u8 prev_bits_per_word = 0;

	/* CS setup/hold/recovery time in nsec */
	cs_delay = (NSEC_PER_SEC / 2) / spi->max_speed_hz;
	tz_spims_wr(c, SPIMS_IS_INT, SPIMS_IE);

	list_for_each_entry(t, &msg->transfers, transfer_list) {
		const void *txbuf = t->tx_buf;
		void *rxbuf = t->rx_buf;
		u32 speed_hz = t->speed_hz ? : spi->max_speed_hz;
		u8 bits_per_word = t->bits_per_word ? : spi->bits_per_word;
		unsigned int words;
		unsigned int wsize;

		bits_per_word = bits_per_word ? : 8;
		if (bits_per_word <= 8) {
			wsize = 1;
		} else if (bits_per_word <= 16) {
			wsize = 2;
		} else if (bits_per_word <= 32) {
			wsize = 4;
		} else {
			dev_dbg(&spi->dev, "invalid bits_per_word\n");
			status = EINVAL;
			break;
		}

		if ((!t->tx_buf && !t->rx_buf && t->len) ||
		    (t->len & (wsize - 1)) != 0 ||
		    speed_hz < c->min_speed_hz) {
			dev_dbg(&spi->dev, "invalid parameters\n");
			status = -EINVAL;
			break;
		}

		if (prev_speed_hz != speed_hz ||
		    prev_bits_per_word != bits_per_word) {
			if (!cs_change) {
				status = tz_spims_disable(c, spi);
				if (status)
					break;
				ndelay(cs_delay);	/* CS Recovery Time */
			}
			tz_spims_configure(c, spi, speed_hz, bits_per_word);
			prev_speed_hz = speed_hz;
			prev_bits_per_word = bits_per_word;
			cs_change = 1;
		}

		if (cs_change) {
			tz_spims_wr(c, SPIMS_FIFOCLR_RX | SPIMS_FIFOCLR_TX,
				    SPIMS_FIFOCLR);
			tz_spims_enable(c, spi);
			ndelay(cs_delay);	/* CS Setup Time */
		}
		cs_change = t->cs_change;
		words = t->len / wsize;
		while (words) {
			unsigned int count = SPIMS_FIFO_SIZE;
			int i;

			if (words < count)
				count = words;
			dev_dbg(&spi->dev, "send %d words\n", count);
			/* enable intr */
			tz_spims_wr(c, count, SPIMS_IC);
			/* send */
			for (i = 0; i < count; i++) {
				tz_spims_txdata(c, txbuf, wsize);
				if (txbuf)
					txbuf += wsize;
			}
			/* wait all rx data */
			if (!wait_for_completion_timeout(&c->done, HZ)) {
				dev_err(&spi->dev,
					"timeout waiting for interrupt\n");
				status = -ETIMEDOUT;
				goto exit;
			}
			/* receive */
			for (i = 0; i < count; i++) {
				tz_spims_rxdata(c, rxbuf, wsize);
				if (rxbuf)
					rxbuf += wsize;
			}
			words -= count;
		}
		msg->actual_length += t->len;
		if (t->delay_usecs)
			udelay(t->delay_usecs);

		if (!cs_change)
			continue;
		if (t->transfer_list.next == &msg->transfers)
			break;
		/* sometimes a short mid-message deselect of the chip
		 * may be needed to terminate a mode or command
		 */
		ndelay(cs_delay);	/* CS Hold Time */
		status = tz_spims_disable(c, spi);
		if (status)
			break;
		ndelay(cs_delay);	/* CS Recovery Time */
	}

exit:
	/* normally deactivate chipselect ... unless no error and
	 * cs_change has hinted that the next message will probably
	 * be for this chip too.
	 */
	if (!(status == 0 && cs_change)) {
		ndelay(cs_delay);	/* CS Hold Time */
		status = tz_spims_disable(c, spi);
		ndelay(cs_delay);	/* CS Recovery Time */
	}
	msg->status = status;

	if (status)
		tz_spims_wr(c, 0, SPIMS_IC);
	tz_spims_wr(c, 0, SPIMS_IE);

	spi_finalize_current_message(master);
	return 0;
}

static void tz_spims_hw_init(struct tz_spims *c)
{
	tz_spims_wr(c, 0, SPIMS_ENABLE);
	tz_spims_wr(c, SPIMS_FIFOCLR_RX | SPIMS_FIFOCLR_TX, SPIMS_FIFOCLR);
	tz_spims_wr(c, 0, SPIMS_IC);
	tz_spims_wr(c, 0xffffffff, SPIMS_IS);
}

static int __devinit tz_spims_probe(struct platform_device *pdev)
{
	struct spi_master *master;
	struct tz_spims *c;
	struct resource *res;
	int ret = -ENODEV;
	int irq;

	master = spi_alloc_master(&pdev->dev, sizeof(*c));
	if (!master)
		return ret;
	c = spi_master_get_devdata(master);
	platform_set_drvdata(pdev, master);
	c->pdev = pdev;

	init_completion(&c->done);

	c->clk = clk_get(&pdev->dev, NULL);
	if (IS_ERR(c->clk)) {
		ret = PTR_ERR(c->clk);
		c->clk = NULL;
		goto exit;
	}
	ret = clk_prepare_enable(c->clk);
	if (ret) {
		clk_put(c->clk);
		c->clk = NULL;
		goto exit;
	}
	c->baseclk = clk_get_rate(c->clk);
	c->min_speed_hz = c->baseclk >> SPIMS_DIV_MAX;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		goto exit_busy;
	c->membase = devm_request_and_ioremap(&pdev->dev, res);
	if (!c->membase)
		goto exit_busy;

	tz_spims_hw_init(c);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		goto exit_busy;
	ret = devm_request_irq(&pdev->dev, irq, tz_spims_interrupt, 0,
			       DRV_NAME, c);
	if (ret)
		goto exit;

	dev_info(&pdev->dev, "at %#lx, irq %d, %dMHz\n",
		 (unsigned long)res->start, irq,
		 (c->baseclk + 500000) / 1000000);

	master->num_chipselect = 1;
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_LSB_FIRST;
	master->bus_num = pdev->id;
	master->setup = tz_spims_setup;
	master->prepare_transfer_hardware = tz_spims_prepare_transfer;
	master->transfer_one_message = tz_spims_transfer_one_message;
	master->unprepare_transfer_hardware = tz_spims_unprepare_transfer;

	ret = spi_register_master(master);
	if (ret)
		goto exit;
	pm_runtime_set_autosuspend_delay(&pdev->dev, 1000);
	pm_runtime_use_autosuspend(&pdev->dev);
	pm_runtime_set_active(&pdev->dev);
	pm_runtime_enable(&pdev->dev);
	return 0;
exit_busy:
	ret = -EBUSY;
exit:
	platform_set_drvdata(pdev, NULL);
	if (c->clk) {
		clk_disable_unprepare(c->clk);
		clk_put(c->clk);
	}
	spi_master_put(master);
	return ret;
}

static int __devexit tz_spims_remove(struct platform_device *pdev)
{
	struct spi_master *master = spi_master_get(platform_get_drvdata(pdev));
	struct tz_spims *c = spi_master_get_devdata(master);

	tz_spims_wr(c, 0, SPIMS_ENABLE);
	spi_unregister_master(master);
	platform_set_drvdata(pdev, NULL);
	pm_runtime_disable(&pdev->dev);
	clk_disable_unprepare(c->clk);
	clk_put(c->clk);
	spi_master_put(master);
	return 0;
}

#ifdef CONFIG_PM
static int tz_spims_suspend(struct device *dev)
{
	struct spi_master *master =
		platform_get_drvdata(to_platform_device(dev));
	struct tz_spims *c = spi_master_get_devdata(master);
	int ret;

	dev_dbg(dev, "suspend\n");
	ret = spi_master_suspend(master);
	if (ret)
		return ret;
	clk_enable(c->clk);
	tz_spims_wr(c, 0, SPIMS_ENABLE);
	clk_disable(c->clk);
	return 0;
}

static int tz_spims_resume(struct device *dev)
{
	struct spi_master *master =
		platform_get_drvdata(to_platform_device(dev));
	struct tz_spims *c = spi_master_get_devdata(master);

	dev_dbg(dev, "resume\n");
	clk_enable(c->clk);
	tz_spims_hw_init(c);
	clk_disable(c->clk);
	return spi_master_resume(master);
}
#endif

#ifdef CONFIG_PM_RUNTIME
static int tz_spims_runtime_suspend(struct device *dev)
{
	struct spi_master *master =
		platform_get_drvdata(to_platform_device(dev));
	struct tz_spims *c = spi_master_get_devdata(master);

	clk_disable(c->clk);

	return 0;
}

static int tz_spims_runtime_resume(struct device *dev)
{
	struct spi_master *master =
		platform_get_drvdata(to_platform_device(dev));
	struct tz_spims *c = spi_master_get_devdata(master);

	clk_enable(c->clk);

	return 0;
}
#endif

static const struct dev_pm_ops tz_spims_dev_pm_ops = {
	SET_SYSTEM_SLEEP_PM_OPS(tz_spims_suspend, tz_spims_resume)
	SET_RUNTIME_PM_OPS(tz_spims_runtime_suspend, tz_spims_runtime_resume,
			   NULL)
};

static struct platform_driver tz_spims_driver = {
	.driver = {
		.name = DRV_NAME,
		.pm	= &tz_spims_dev_pm_ops,
		.owner = THIS_MODULE,
	},
	.probe = tz_spims_probe,
	.remove = __devexit_p(tz_spims_remove),
};

module_platform_driver(tz_spims_driver);

MODULE_DESCRIPTION("Toshiba TZ3000/TZ2000 SPIMS Driver");
MODULE_LICENSE("GPL");
