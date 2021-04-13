/*
 * linux/drivers/net/txss_eth.c
 *
 * TX Sub System EtherMAC Controller driver
 *
 * (C) Copyright TOSHIBA CORPORATION SEMICONDUCTOR COMPANY 2008,2009
 * (C) Copyright TOSHIBA CORPORATION
 *      SEMICONDUCTOR & STORAGE PRODUCTS COMPANY 2013
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
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */
#undef DEBUG
#undef TXSS_ETH_DEBUG_IO

#include <linux/version.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_data/txss_eth.h>
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/gfp.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/interrupt.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/ethtool.h>
#include <linux/if_ether.h>
#include <linux/if_vlan.h>
#include <linux/phy.h>
#include <asm/page.h>

#ifdef CONFIG_OF
#include <linux/of_platform.h>
#endif

#define TXSS_ETH_USE_CHECKSUM_HW
#define TXSS_ETH_MAX_QUEUE_LEN
#include "txss_eth.h"

#define DRV_VERSION "1.6_p1"
#define DRV_DEVNAME "txss-eth"
const char txss_eth_driver_name[] = DRV_DEVNAME;
const char txss_eth_driver_version[] = DRV_VERSION;
static const char *print_version =
	"TX sub system EtherMAC controller driver: ver" DRV_VERSION;

#define NAPI_WEIGHT     16

MODULE_DESCRIPTION("TX Sub System EtherMAC Controller driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);

static int txss_eth_open(struct net_device *dev);
static int txss_eth_stop(struct net_device *dev);
static int txss_eth_send_packet(struct sk_buff *skb, struct net_device *dev);
static void txss_eth_tx_timeout(struct net_device *dev);
static struct net_device_stats *txss_eth_get_stats(struct net_device *dev);
static void txss_eth_set_multicast_list(struct net_device *dev);
static int txss_eth_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd);
static int txss_eth_poll(struct napi_struct *dev, int budget);
#ifdef CONFIG_NET_POLL_CONTROLLER
static void txss_eth_poll_controller(struct net_device *dev);
#endif
static irqreturn_t txss_eth_interrupt(int irq, void *dev_id);
static int txss_eth_rx(struct net_device *dev, int limit);
static int txss_eth_tx_done(struct net_device *dev);
static void txss_eth_rx_stop(struct net_device *dev);
static void txss_eth_tx_stop(struct net_device *dev);
static void txss_eth_soft_reset(struct net_device *dev);
static void txss_eth_hard_reset(struct net_device *dev);
static void txss_eth_phy_init(struct net_device *dev);
static void txss_eth_chip_reset(struct net_device *dev);
static void txss_eth_chip_init(struct net_device *dev);
static int txss_eth_mii_read(struct mii_bus *bus, int phy_id, int regnum);
static int txss_eth_mii_write(struct mii_bus *bus, int phy_id, int regnum,
			      u16 val);
static void txss_eth_mii_link_change(struct net_device *dev);

static struct txss_eth_options options = {
	.phyaddr = PHY_MAX_ADDR,
	.hec_phyaddr = PHY_MAX_ADDR
};

static int txss_eth_rx_retry;
static int fast_link;

static unsigned int current_phyaddr;

static inline int checkreg_timeout(void __iomem *reg, u32 mask,
				   u32 val, int timeout)
{
	int loop = timeout / (1000 * 1000 / HZ);
	int delay;

	mb(); /* barrier */
	while (loop--) {
		if ((txss_readl(reg) & mask) == val)
			return 0;
		mb(); /* barrier */
		schedule_timeout(1);
	}
	delay = (timeout % (1000 * 1000 / HZ));
	udelay((unsigned int) delay);
	if ((txss_readl(reg) & mask) == val)
		return 0;
	else
		return -1;
}

u32 txss_eth_update_pftxcntr(struct net_device *dev)
{
	struct txss_eth_local *lp = netdev_priv(dev);
	struct txss_eth_regs __iomem *tr =
	    (struct txss_eth_regs __iomem *)dev->base_addr;
	u32 cnt = txss_readl(&tr->pftxcntr);
	lp->lstats.tx_pause_count += cnt;
	return cnt;
}

u32 txss_eth_update_pfrxcntr(struct net_device *dev)
{
	struct txss_eth_local *lp = netdev_priv(dev);
	struct txss_eth_regs __iomem *tr =
	    (struct txss_eth_regs __iomem *)dev->base_addr;
	u32 cnt = txss_readl(&tr->pfrxcntr);
	lp->lstats.rx_pause_count += cnt;
	return cnt;
}

/* PHY register access function */

static int txss_eth_mii_read(struct mii_bus *bus, int phy_id, int regnum)
{
	struct net_device *dev = bus->priv;
	struct txss_eth_regs __iomem *tr =
	    (struct txss_eth_regs __iomem *)dev->base_addr;
	int ret;

	ret = checkreg_timeout(&tr->mdiostsr, MDIOSTSR_BSY,
			       0x0, MII_IO_TIMEOUT);
	if (ret) {
		pr_warn("%s: timeout\n", __func__);
		return -EIO;
	}

	txss_writel(MDIOADRR_PHYADR(phy_id) | MDIOADRR_PHYREG(regnum),
		    &tr->mdioadrr);
	txss_writel(MDIOCMDR_READ, &tr->mdiocmdr);

	ret = checkreg_timeout(&tr->mdiostsr, MDIOSTSR_BSY,
			       0x0, MII_IO_TIMEOUT);
	if (ret) {
		pr_warn("%s: timeout\n", __func__);
		return -EIO;
	}

	return txss_readl(&tr->mdiodatr) & 0xffff;
}

static int
txss_eth_mii_write(struct mii_bus *bus, int phy_id, int regnum, u16 val)
{
	struct net_device *dev = bus->priv;
	struct txss_eth_regs __iomem *tr =
	    (struct txss_eth_regs __iomem *)dev->base_addr;
	int ret;
	struct txss_eth_local *lp = netdev_priv(dev);

	ret = checkreg_timeout(&tr->mdiostsr, MDIOSTSR_BSY,
			       0x0, MII_IO_TIMEOUT);
	if (ret) {
		pr_warn("%s: timeout\n", __func__);
		return -EIO;
	}

	txss_writel(MDIOADRR_PHYADR(phy_id) | MDIOADRR_PHYREG(regnum),
		    &tr->mdioadrr);
	txss_writel(val, &tr->mdiodatr);
	txss_writel(MDIOCMDR_WRITE, &tr->mdiocmdr);

	ret = checkreg_timeout(&tr->mdiostsr, MDIOSTSR_BSY,
			       0x0, MII_IO_TIMEOUT);
	if (ret) {
		pr_warn("%s: timeout\n", __func__);
		return -EIO;
	}
	if (lp->phy_force_read_after_write)
		txss_eth_mii_read(bus, phy_id, MII_BMSR);

	return 0;
}

static void txss_phy_power(struct phy_device *phydev, int pon)
{
	u16 val;
	int timeout;

	if (!phydev)
		return;

	/* Wait Soft Reset */

	timeout = 1000000; /* 1 sec */
	while (--timeout) {
		if (!(phy_read(phydev, MII_BMCR) & BMCR_RESET))
			break;
		udelay(1);
	}
	if (!timeout)
		pr_err("%s: BMCR reset failed.\n", __func__);

	/* Set Power */

	val = (u16) phy_read(phydev, MII_BMCR);

	if (pon)
		val &=  ~(BMCR_PDOWN);
	else
		val |= (BMCR_PDOWN);

	if (phy_write(phydev, MII_BMCR, val))
		pr_err("%s: BMCR power set failed. phyid %d\n",
		       __func__, phydev->addr);
}

static void txss_eth_mii_link_change(struct net_device *dev)
{
	struct txss_eth_local *lp = netdev_priv(dev);
	struct phy_device *phydev = lp->phydev;
	int status_change = 0;

	if (phydev->link && ((lp->duplex != phydev->duplex) ||
			     (lp->speed != phydev->speed))) {
		struct txss_eth_regs __iomem *tr =
		    (struct txss_eth_regs __iomem *)dev->base_addr;
		u32 maccr;
		u32 macgcr;
		maccr = txss_readl(&tr->maccr);
		maccr &= ~(MACCR_RPE | MACCR_TPE);	/* Rx/Tx disable */
		txss_writel(maccr, &tr->maccr);

		/* setting duplex */
		if (phydev->duplex == DUPLEX_FULL)
			maccr |= MACCR_DPM;
		else
			maccr &= ~MACCR_DPM;
		txss_writel(maccr, &tr->maccr);
		/* setting speed */
		macgcr = txss_readl(&tr->macgcr);
		macgcr &= ~MACGCR_SPEED_MSK;
		switch (phydev->speed) {
		case SPEED_1000:
			macgcr |= MACGCR_SPEED_1000;
			break;
		case SPEED_100:
			macgcr |= MACGCR_SPEED_100;
			break;
		case SPEED_10:
		default:
			macgcr |= MACGCR_SPEED_10;
			break;
		}
		/* PHYIF workaround */
		if ((txss_readl(&tr->emacfinfr) & EMACFINFR_PHYIFWAR) &&
		    (phydev->speed <= SPEED_100))
			macgcr |= MACGCR_BSE;
		else
			macgcr &= ~MACGCR_BSE;

		txss_writel(macgcr, &tr->macgcr);

		maccr |= MACCR_RPE | MACCR_TPE;	/* Rx/Tx enable */
		txss_writel(maccr, &tr->maccr);

		lp->duplex = phydev->duplex;
		lp->speed = phydev->speed;
		status_change = 1;
	}

	if (phydev->link != lp->link) {
		if (!(phydev->link)) {
			lp->duplex = -1;
			lp->speed = 0;
		}
		lp->link = phydev->link;
		status_change = 1;
	}

	if (status_change && netif_msg_link(lp))
		phy_print_status(phydev);
}

static int txss_eth_mii_probe(struct net_device *dev)
{
	struct txss_eth_local *lp = netdev_priv(dev);
	struct phy_device *phydev = NULL;
	int phy_addr;
	struct txss_eth_platform_data *pdata = lp->pdev->dev.platform_data;

	if (current_phyaddr < PHY_MAX_ADDR &&
	    lp->mii_bus->phy_map[current_phyaddr]) {
		phydev = lp->mii_bus->phy_map[current_phyaddr];
	} else {
		/* find the first phy */
		for (phy_addr = 0; phy_addr < PHY_MAX_ADDR; phy_addr++) {
			if (lp->mii_bus->phy_map[phy_addr]) {
				if (phydev) {
					pr_err("%s: multiple PHYs found\n",
					       dev->name);
					return -EINVAL;
				}
				phydev = lp->mii_bus->phy_map[phy_addr];
				break;
			}
		}
	}

	if (!phydev) {
		pr_err("%s: no PHY found\n", dev->name);
		return -ENODEV;
	}
	/* workaround for RTL8211EG errata */
	if (phydev->phy_id == 0x001cc915) {
		pr_info("%s: Enable PHY workaround (force read after write).\n",
			dev->name);
		lp->phy_force_read_after_write = 1;
	}

	if (options.phypwrmng) {
		/*
		 * current Phy Power Up and oppsite Phy Power Down
		 */
		if (options.hec_phyaddr != PHY_MAX_ADDR) {
			int pdown_phy;

			if (options.phyaddr == phydev->addr)
				pdown_phy = options.hec_phyaddr;
			else
				pdown_phy = options.phyaddr;

			txss_phy_power(lp->mii_bus->phy_map[pdown_phy],
				       0);   /* Power Off */
		}
		txss_phy_power(phydev, 1); /* Power On */
	}

	if (options.hec_phyaddr == phydev->addr) {
		struct ifreq ifreq;
		struct mii_ioctl_data *mii_data = if_mii(&ifreq);

		/* fixup the phy for HEC to disable auto-neg, 100M/Full */

		mii_data->reg_num = MII_BMCR;
		phy_mii_ioctl(phydev, &ifreq, SIOCGMIIREG);
		mii_data->reg_num = MII_BMCR;
		mii_data->val_in = mii_data->val_out |
			BMCR_FULLDPLX | BMCR_SPEED100;
		mii_data->val_in &= ~(BMCR_ANENABLE);
		mii_data->phy_id = phydev->addr;
		phy_mii_ioctl(phydev, &ifreq, SIOCSMIIREG);
	}

	/* attach the mac to the phy */
	if (pdata && pdata->gbit_support &&
	    (options.speed == 1000 || options.speed == 0)) {
		pr_info("%s: Enable Gigabit ethernet.\n", dev->name);
		phydev = phy_connect(dev, dev_name(&phydev->dev),
				     &txss_eth_mii_link_change, 0,
				     PHY_INTERFACE_MODE_GMII);
	} else {
		phydev = phy_connect(dev, dev_name(&phydev->dev),
				     &txss_eth_mii_link_change, 0,
				     PHY_INTERFACE_MODE_MII);
	}
	if (IS_ERR(phydev)) {
		pr_err("%s: Could not attach to PHY\n", dev->name);
		return PTR_ERR(phydev);
	}
	pr_info("%s: attached PHY driver [%s] (mii_bus:phy_addr=%s, id=%x)\n",
		dev->name, phydev->drv->name, dev_name(&phydev->dev),
		phydev->phy_id);

	/* mask with MAC supported features */
	if (phydev->interface == PHY_INTERFACE_MODE_GMII)
		phydev->supported &= PHY_GBIT_FEATURES;
	else
		phydev->supported &= PHY_BASIC_FEATURES;

	if (options.hec_phyaddr == phydev->addr) {
		phydev->supported &= (SUPPORTED_100baseT_Full | SUPPORTED_TP |
				      SUPPORTED_MII);
	}

	phydev->advertising =
	    phydev->supported | SUPPORTED_Pause | SUPPORTED_Asym_Pause;

	lp->phydev = phydev;
	lp->duplex = -1;
	lp->speed = 0;
	lp->link = 0;

	return 0;
}

static int txss_eth_mii_init(struct net_device *dev)
{
	struct txss_eth_local *lp = netdev_priv(dev);
	int err, i;
#if defined(CONFIG_FIXED_PHY)
	struct phy_device *phydev;
	struct device *d;

	d = bus_find_device_by_name(&mdio_bus_type, NULL, "fixed-0:00");
	if (d) {
		phydev = to_phy_device(d);
		lp->mii_bus = phydev->bus;
		return 0;
	}
#endif

	lp->mii_bus = mdiobus_alloc();
	if (lp->mii_bus == NULL) {
		err = -ENOMEM;
		goto err_out;
	}

	lp->mii_bus->name = MII_BUS_NAME;
	lp->mii_bus->read = txss_eth_mii_read;
	lp->mii_bus->write = txss_eth_mii_write;
	snprintf(lp->mii_bus->id, MII_BUS_ID_SIZE, "%x", lp->pdev->id);
	lp->mii_bus->priv = dev;
	lp->mii_bus->parent = &lp->pdev->dev;
	lp->mii_bus->irq = kmalloc(sizeof(int) * PHY_MAX_ADDR, GFP_KERNEL);
	if (!lp->mii_bus->irq) {
		err = -ENOMEM;
		goto err_out;
	}
	lp->mii_bus->phy_mask = options.phymask;

	for (i = 0; i < PHY_MAX_ADDR; i++)
		lp->mii_bus->irq[i] = PHY_POLL;

	err = mdiobus_register(lp->mii_bus);
	if (err) {
		pr_warn("%s: could not register mdiobus. (errno=%d)\n",
			DRV_DEVNAME, err);
		goto err_out_free_mdio_irq;
	}

	return 0;

err_out_free_mdio_irq:
	kfree(lp->mii_bus->irq);
err_out:
	return err;
}

/* allocate sk_buff function */

static struct sk_buff *alloc_rxbuf_skb(struct net_device *dev,
				       dma_addr_t *dma_handle)
{
	struct txss_eth_local *lp = netdev_priv(dev);
	struct sk_buff *skb;

	skb = dev_alloc_skb(lp->max_frame_size);
	if (!skb)
		return NULL;
	skb->dev = dev;
	*dma_handle =
	    dma_map_single(&lp->pdev->dev, skb->data, lp->max_frame_size,
			   DMA_FROM_DEVICE);
	if (dma_mapping_error(&lp->pdev->dev, *dma_handle)) {
		dev_kfree_skb_any(skb);
		return NULL;
	}
	skb_reserve(skb, NET_IP_ALIGN);	/* make IP header 4byte aligned */
	return skb;
}

static void free_rxbuf_skb(struct net_device *dev, struct sk_buff *skb,
			   dma_addr_t dma_handle)
{
	struct txss_eth_local *lp = netdev_priv(dev);

	dma_unmap_single(&lp->pdev->dev, dma_handle, lp->max_frame_size,
			 DMA_FROM_DEVICE);
	dev_kfree_skb_any(skb);
}

static int txss_eth_tx_full(struct net_device *dev)
{
	struct txss_eth_local *lp = netdev_priv(dev);
	return ((lp->txdesc_start + 1) % lp->tx_desc_num == lp->txdesc_end);
}

/* ring queue function */

static int txss_eth_init_queue(struct net_device *dev)
{
	struct txss_eth_local *lp = netdev_priv(dev);
	struct txss_eth_regs __iomem *tr =
	    (struct txss_eth_regs __iomem *)dev->base_addr;
	size_t desc_size;
	int i;
	unsigned long desc_addr, desc_dma_addr;

	/* allocate descriptor ring at non-cached area */
	desc_size =
	    sizeof(struct txss_eth_td) * lp->tx_desc_num
	    + sizeof(struct txss_eth_rd) * lp->rx_desc_num;
	lp->desc = dma_alloc_coherent(&lp->pdev->dev, desc_size,
				      &lp->desc_dma, GFP_ATOMIC);
	if (lp->desc == NULL)
		return -ENOMEM;

	lp->tx_skbs =
	    kmalloc(sizeof(struct txss_eth_skbs) * lp->tx_desc_num, GFP_KERNEL);
	if (lp->tx_skbs == NULL)
		return -ENOMEM;
	lp->rx_skbs =
	    kmalloc(sizeof(struct txss_eth_skbs) * lp->rx_desc_num, GFP_KERNEL);
	if (lp->rx_skbs == NULL)
		return -ENOMEM;

	/* allocate receive buffer */
	for (i = 0; i < lp->rx_desc_num; i++) {
		lp->rx_skbs[i].skb =
		    alloc_rxbuf_skb(dev, &lp->rx_skbs[i].skb_dma);

		if (!lp->rx_skbs[i].skb) {
			while (--i >= 0) {
				free_rxbuf_skb(dev,
					       lp->rx_skbs[i].skb,
					       lp->rx_skbs[i].skb_dma);
				lp->rx_skbs[i].skb = NULL;
			}
			dma_free_coherent(&lp->pdev->dev,
					  desc_size, lp->desc, lp->desc_dma);
			lp->desc = NULL;
			return -ENOMEM;
		}
	}

	desc_addr = (unsigned long)lp->desc;
	desc_dma_addr = (unsigned long)lp->desc_dma;

	/* set receive descriptor */
	lp->rx_desc = (struct txss_eth_rd *)desc_addr;
	lp->rx_desc_dma = (struct txss_eth_rd *)desc_dma_addr;
	desc_addr += sizeof(struct txss_eth_rd) * lp->rx_desc_num;
	desc_dma_addr += sizeof(struct txss_eth_rd) * lp->rx_desc_num;
	for (i = 0; i < lp->rx_desc_num; i++) {
		lp->rx_desc[i].rd2 = RD2_RBA_SET(lp->rx_skbs[i].skb_dma);
		lp->rx_desc[i].rd1 = RD1_RBL_SET(lp->max_frame_size);
		lp->rx_desc[i].rd0 = RD0_RACT;
	}
	lp->rx_desc[lp->rx_desc_num - 1].rd0 |= RD0_RDL;
	lp->rxdesc_end = 0;

	/* clear transmit skbs */
	for (i = 0; i < lp->tx_desc_num; i++) {
		lp->tx_skbs[i].skb = NULL;
		lp->tx_skbs[i].skb_dma = 0;
	}

	/* set transmit descriptor */
	lp->tx_desc = (struct txss_eth_td *)desc_addr;
	lp->tx_desc_dma = (struct txss_eth_td *)desc_dma_addr;
	for (i = 0; i < lp->tx_desc_num; i++) {
		lp->tx_desc[i].td2 = 0x0;
		lp->tx_desc[i].td1 = 0x0;
		lp->tx_desc[i].td0 = 0x0;
	}
	lp->tx_desc[lp->tx_desc_num - 1].td0 |= TD0_TDL;
	lp->txdesc_start = 0;
	lp->txdesc_end = 0;

	/* set descriptor pointer */
	mb();
	txss_writel((u32) &lp->rx_desc_dma[0], &tr->drxspar);
	txss_writel((u32) &lp->rx_desc_dma[0], &tr->drxcpar);
	txss_writel((u32) &lp->rx_desc_dma[lp->rx_desc_num - 1], &tr->drxlpar);
	txss_writel(DRXDLR_DRXDL, &tr->drxdlr);
	txss_writel((u32) &lp->tx_desc_dma[0], &tr->dtxspar);
	txss_writel((u32) &lp->tx_desc_dma[0], &tr->dtxcpar);
	txss_writel((u32) &lp->tx_desc_dma[lp->tx_desc_num - 1], &tr->dtxlpar);
	txss_writel(DTXDLR_DTXDL, &tr->dtxdlr);

	return 0;
}

static void txss_eth_clear_tx_queue(struct net_device *dev)
{
	struct txss_eth_local *lp = netdev_priv(dev);
	struct txss_eth_regs __iomem *tr =
	    (struct txss_eth_regs __iomem *)dev->base_addr;
	struct sk_buff *skb;
	int i;

	for (i = 0; i < lp->tx_desc_num; i++) {
		skb = lp->tx_skbs[i].skb;
		if (skb) {
			lp->tx_skbs[i].skb = NULL;
			lp->tx_skbs[i].skb_dma = 0;
			dev_kfree_skb_any(skb);
		}
		lp->tx_desc[i].td2 = 0x0;
		lp->tx_desc[i].td1 = 0x0;
		lp->tx_desc[i].td0 = 0x0;
		mb(); /* barrier */
	}
	lp->tx_desc[lp->tx_desc_num - 1].td0 |= TD0_TDL;
	mb(); /* barrier */

	txss_writel((u32) &lp->tx_desc_dma[0], &tr->dtxspar);
	txss_writel((u32) &lp->tx_desc_dma[0], &tr->dtxcpar);
	txss_writel((u32) &lp->tx_desc_dma[lp->tx_desc_num - 1], &tr->dtxlpar);
	txss_writel(DTXDLR_DTXDL, &tr->dtxdlr);
	mb(); /* barrier */
	lp->txdesc_start = 0;
	lp->txdesc_end = 0;
}

static int txss_eth_free_queue(struct net_device *dev)
{
	struct txss_eth_local *lp = netdev_priv(dev);
	int i;
	size_t desc_size;

	desc_size = sizeof(struct txss_eth_td) * lp->tx_desc_num
	    + sizeof(struct txss_eth_rd) * lp->rx_desc_num;

	for (i = 0; i < lp->rx_desc_num; i++) {
		free_rxbuf_skb(dev, lp->rx_skbs[i].skb, lp->rx_skbs[i].skb_dma);
		lp->rx_skbs[i].skb = NULL;
	}
	dma_free_coherent(&lp->pdev->dev, desc_size, lp->desc, lp->desc_dma);
	kfree(lp->tx_skbs);
	kfree(lp->rx_skbs);
	return 0;
}

/* print frame data for debug */

static void print_eth(const u8 *add)
{
	unsigned char *c = (unsigned char *)add;

	pr_info("print_eth(%p)\n", add);
	pr_info(" %pM => %pM : %2.2X%2.2X\n", c + 6, c, c[12], c[13]);
}

/* net_device function */

static int txss_eth_open(struct net_device *dev)
{
	struct txss_eth_local *lp = netdev_priv(dev);
	int err;

	if (request_irq
	    (dev->irq, &txss_eth_interrupt, IRQF_SHARED, dev->name, dev))
		return -EAGAIN;

	txss_eth_chip_reset(dev);

	if (txss_eth_init_queue(dev) != 0) {
		free_irq(dev->irq, dev);
		return -EAGAIN;
	}

	err = txss_eth_mii_probe(dev);
	if (err) {
		pr_warn("%s: mii_probe failure. (errno=%d)\n",
			DRV_DEVNAME, err);
		free_irq(dev->irq, dev);
		return -EAGAIN;
	}

	napi_enable(&lp->napi);
	txss_eth_chip_init(dev);
	netif_carrier_off(dev);

	if (fast_link)
		phy_start_fast(lp->phydev);
	else
		phy_start(lp->phydev);

	netif_start_queue(dev);

	return 0;
}

static int txss_eth_stop(struct net_device *dev)
{
	struct txss_eth_local *lp = netdev_priv(dev);

	netif_stop_queue(dev);
	if (lp->phydev)
		phy_stop(lp->phydev);

	if (options.phypwrmng)
		txss_phy_power(lp->phydev, 0); /* Power Down */

	phy_disconnect(lp->phydev);

	free_irq(dev->irq, dev);	/* disable interrupt */
	txss_eth_chip_reset(dev);
	txss_eth_clear_tx_queue(dev);
	txss_eth_free_queue(dev);
	napi_disable(&lp->napi);

	return 0;
}

static int txss_eth_send_packet(struct sk_buff *skb, struct net_device *dev)
{
	struct txss_eth_local *lp = netdev_priv(dev);
	struct txss_eth_td *tx_desc;
	unsigned int i;

	i = lp->txdesc_start;
	tx_desc = &lp->tx_desc[i];

	if (netif_msg_pktdata(lp))
		print_eth(skb->data);

	lp->tx_skbs[i].skb = skb;
	lp->tx_skbs[i].skb_dma =
	    dma_map_single(&lp->pdev->dev, skb->data, skb->len, DMA_TO_DEVICE);

	tx_desc->td0 &= TD0_TDL;	/* clear TD0 */
	tx_desc->td2 = lp->tx_skbs[i].skb_dma;
	tx_desc->td1 = TD1_TBL_SET(skb->len);
	mb(); /* barrier */
	tx_desc->td0 |= TD0_TACT | TD0_TFP_ALL | TD0_TWBI;

	pr_debug("lp->tx_desc[%3d].td0 = 0x%08x, td1 = 0x%08x, td2 = 0x%08x\n",
		 i, tx_desc->td0, tx_desc->td1, tx_desc->td2);

	mb(); /* barrier */

	{
		struct txss_eth_regs __iomem *tr =
		    (struct txss_eth_regs __iomem *)dev->base_addr;
		txss_writel(DMATXR_START, &tr->dmatxr);	/* Tx DMA start */
	}

	lp->txdesc_start = (lp->txdesc_start + 1) % lp->tx_desc_num;

#ifdef TXSS_ETH_MAX_QUEUE_LEN
	lp->lstats.tx_max_queue_len = max((int)
					  ((lp->txdesc_start + lp->tx_desc_num
					    - (lp->txdesc_end))
					   % lp->tx_desc_num),
					  lp->lstats.tx_max_queue_len);
#endif

	if (txss_eth_tx_full(dev)) {
		lp->lstats.tx_full++;
		if (netif_msg_tx_queued(lp))
			pr_warn("%s: Tx desc Exhausted.\n", dev->name);
		netif_stop_queue(dev);
	}
	return 0;
}

static void txss_eth_restart(struct work_struct *work)
{
	struct txss_eth_local *lp =
	    container_of(work, struct txss_eth_local, restart_work);
	struct net_device *dev = lp->dev;

	netif_device_detach(dev);
	txss_eth_stop(dev);

	if (lp->phydev) {
		struct ifreq ifreq;
		struct mii_ioctl_data *mii_data = if_mii(&ifreq);
		int timeout;

		mii_data->reg_num = MII_BMCR;
		mii_data->val_in = BMCR_RESET;
		phy_mii_ioctl(lp->phydev, &ifreq, SIOCSMIIREG);

		timeout = 100;
		while (--timeout) {
			if (!(phy_read(lp->phydev, MII_BMCR) & BMCR_RESET))
				break;
			udelay(1);
		}
		if (!timeout)
			pr_err("%s: BMCR reset failed.\n", dev->name);
	}

	txss_eth_hard_reset(dev);

	txss_eth_open(dev);
	netif_device_attach(dev);
}

static void txss_eth_tx_timeout(struct net_device *dev)
{
	struct txss_eth_local *lp = netdev_priv(dev);
	struct txss_eth_regs __iomem *tr =
	    (struct txss_eth_regs __iomem *)dev->base_addr;

	txss_writel(0x0, &tr->emacintenr);	/* disable interrupt */
	txss_readl(&tr->emacintenr);	/* dummy read */
	mb();
	schedule_work(&lp->restart_work);
	lp->lstats.tx_timeouts++;
}

static struct net_device_stats *txss_eth_get_stats(struct net_device *dev)
{
	struct txss_eth_local *lp = netdev_priv(dev);
	struct txss_eth_regs __iomem *tr =
	    (struct txss_eth_regs __iomem *)dev->base_addr;

	lp->stats.multicast += txss_readl(&tr->rint8cntr);
	lp->stats.collisions += txss_readl(&tr->tint2cntr);
	lp->stats.rx_length_errors += txss_readl(&tr->rint4cntr);
	lp->stats.rx_length_errors += txss_readl(&tr->rint3cntr);
	lp->stats.rx_crc_errors += txss_readl(&tr->rint1cntr);
	lp->stats.rx_frame_errors += txss_readl(&tr->rint5cntr);
	lp->stats.rx_missed_errors += txss_readl(&tr->rint2cntr);
	lp->stats.rx_missed_errors += txss_readl(&tr->rxmiscntr);
	lp->stats.tx_carrier_errors += txss_readl(&tr->tint3cntr);
	lp->stats.tx_window_errors += txss_readl(&tr->tint1cntr);

	txss_writel(0x0000, &tr->rxmiscntr);	/* clear */
	return &lp->stats;
}

static void txss_eth_set_address_filter(struct net_device *dev)
{
	struct txss_eth_regs __iomem *tr =
	    (struct txss_eth_regs __iomem *)dev->base_addr;

	txss_writel(FLTCR_DISABLE, &tr->fltcr);
	if (dev->flags & IFF_ALLMULTI)
		return;		/* use normal mode */
	if (netdev_mc_count(dev) <= MACFLT_ENTRY) {
		struct netdev_hw_addr *ha;
		u32 *addr;
		int i;

		txss_writel(FLTENTR_WEALL | 0x0, &tr->fltentr);
		i = 0;
		netdev_for_each_mc_addr(ha, dev) {
			addr = (u32 *)(ha->addr);
			pr_debug("%s: set %08x%04x\n", __func__,
				 swab32(addr[0]),
				 (swab32(addr[1]) & 0xffff0000) >> 16);
			txss_writel(swab32(addr[0]), &tr->fmar[i].hr);
			txss_writel((swab32(addr[1]) & 0xffff0000) >> 16,
				    &tr->fmar[i].lr);
			i++;
		}
		txss_writel(FLTENTR_WEALL | ((0x1 << netdev_mc_count(dev)) - 1),
			    &tr->fltentr);
		txss_writel(FLTCR_ENABLE, &tr->fltcr);
	}
}

static void txss_eth_set_multicast_list(struct net_device *dev)
{
	struct txss_eth_regs __iomem *tr =
	    (struct txss_eth_regs __iomem *)dev->base_addr;
	u32 maccr;

	maccr = txss_readl(&tr->maccr);
	maccr &= ~(MACCR_RPE | MACCR_TPE);	/* Rx/Tx disable */
	txss_writel(maccr, &tr->maccr);

	if (dev->flags & IFF_PROMISC) {
		txss_writel(FLTCR_DISABLE, &tr->fltcr);
		maccr |= MACCR_PRM;
	} else {
		maccr &= ~MACCR_PRM;
		if (txss_readl(&tr->emacfinfr) & EMACFINFR_MACFLT)
			txss_eth_set_address_filter(dev);
	}

	maccr |= MACCR_RPE | MACCR_TPE;	/* Rx/Tx enable */
	txss_writel(maccr, &tr->maccr);
}

static int txss_eth_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	struct txss_eth_local *lp = netdev_priv(dev);
	struct phy_device *phydev;

	pr_debug("%s\n", __func__);

	if (if_mii(ifr)->phy_id >= PHY_MAX_ADDR)
		return -ENODEV;

	phydev = lp->mii_bus->phy_map[if_mii(ifr)->phy_id];

	if (!phydev)
		return -ENODEV;

	if (cmd == (SIOCDEVPRIVATE + 1)) {  /* Set PHY Address */
		current_phyaddr = if_mii(ifr)->phy_id;
		return 0;
	}

	if (!phydev)
		return -ENODEV;

	return phy_mii_ioctl(phydev, ifr, cmd);
}

static int txss_eth_do_interrupt(struct net_device *dev, u32 status, int limit)
{
	struct txss_eth_local *lp = netdev_priv(dev);
	struct txss_eth_regs __iomem *tr =
	    (struct txss_eth_regs __iomem *)dev->base_addr;
	u32 mac_status = txss_readl(&tr->macintr);
	int ret = -1;

	if (unlikely(mac_status)) {
		txss_writel(mac_status, &tr->macintr);
		if (netif_msg_hw(lp) && (mac_status & MACINTR_FCI)) {
			pr_warn("%s: False Carrier Indication\n",
				dev->name);
			lp->lstats.fci++;
		}
	}
	if (unlikely(status & DMAINTR_ERR)) {
		if (status & DMAINTR_RFRMER) {
			if (netif_msg_rx_err(lp))
				pr_warn("%s: Rx frame overflow. (status 0x%08x)\n",
					dev->name, status);
			lp->lstats.rx_frame_overflow++;
			lp->stats.rx_dropped++;
		}
		if (status & DMAINTR_TDE) {
			if (netif_msg_drv(lp))
				pr_warn("%s: Tx desc exhausted. (status 0x%08x)\n",
					dev->name, status);
			lp->lstats.tx_desc_exhausted++;
			lp->stats.tx_dropped++;
		}
		if (status & DMAINTR_TFE) {
			if (netif_msg_drv(lp))
				pr_warn("%s: Tx FIFO underflow. (status 0x%08x)\n",
					dev->name, status);
			lp->lstats.tx_fifo_underflow++;
			lp->stats.tx_fifo_errors++;
		}
		if (status & DMAINTR_RDE) {
			if (netif_msg_rx_err(lp))
				pr_warn("%s: Rx desc exhausted. (status 0x%08x)\n",
					dev->name, status);
			lp->lstats.rx_desc_exhausted++;
			lp->stats.rx_dropped++;
		}
		if (status & DMAINTR_RFE) {
			if (netif_msg_rx_err(lp))
				pr_warn("%s: Rx FIFO overflow. (status 0x%08x)\n",
					dev->name, status);
			lp->lstats.rx_fifo_overflow++;
			lp->stats.rx_fifo_errors++;
		}
		ret = 0;
	}
	if (status & (DMAINTR_FRC | DMAINTR_RDE) || txss_eth_rx_retry) {
		/* got a packet(s) */
		ret = txss_eth_rx(dev, limit);
		lp->lstats.rx_ints++;
	}
	if (status & (DMAINTR_FTC1 | DMAINTR_FTC0)) {
		/* transmit complete */
		txss_eth_tx_done(dev);
		lp->lstats.tx_ints++;
		ret = 0;
	}
	return ret;
}

static int txss_eth_poll(struct napi_struct *napi, int budget)
{
	struct txss_eth_local *lp =
	    container_of(napi, struct txss_eth_local, napi);
	struct net_device *dev = lp->dev;
	struct txss_eth_regs __iomem *tr =
	    (struct txss_eth_regs __iomem *)dev->base_addr;

	int received = 0;
	int handled;
	u32 status;

	status = txss_readl(&tr->dmaintr);
	do {
		/* write to clear */
		txss_writel(status, &tr->dmaintr);
		handled = txss_eth_do_interrupt(dev, status, budget - received);
		if (handled >= 0) {
			received += handled;
			if (received >= budget)
				;
			break;
		}
		status = txss_readl(&tr->dmaintr);
	} while (status);

	if (received < budget) {
		napi_complete(napi);
		/* enable interrupt */
		txss_writel(EMACINTR_DMAINT, &tr->emacintenr);
	}

	return received;
}

#ifdef CONFIG_NET_POLL_CONTROLLER
static void txss_eth_poll_controller(struct net_device *dev)
{
	disable_irq(dev->irq);
	txss_eth_interrupt(dev->irq, dev);
	enable_irq(dev->irq);
}
#endif

/* interrupt handling */

static irqreturn_t txss_eth_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	struct txss_eth_local *lp = netdev_priv(dev);
	struct txss_eth_regs __iomem *tr =
	    (struct txss_eth_regs __iomem *)dev->base_addr;
	u32 status;

	if (netif_msg_intr(lp))
		pr_info("%s: dmaintr:0x%08x macintr:0x%08x emacintr:0x%08x\n",
			__func__, txss_readl(&tr->dmaintr),
			txss_readl(&tr->macintr), txss_readl(&tr->emacintr));

	status = txss_readl(&tr->emacintr);
	if (status) {
		/* disable interrupt */
		txss_writel(0, &tr->emacintenr);
		napi_schedule(&lp->napi);
		txss_readl(&tr->emacintenr);	/* dummy read */
		mb();
		return IRQ_HANDLED;
	}
	return IRQ_NONE;
}

static int txss_eth_rx(struct net_device *dev, int limit)
{
	struct txss_eth_local *lp = netdev_priv(dev);
	struct txss_eth_regs __iomem *tr =
	    (struct txss_eth_regs __iomem *)dev->base_addr;
	struct txss_eth_rd *rx_desc;
	unsigned int i;
#ifdef TXSS_ETH_MAX_QUEUE_LEN
	u32 spar, lpar;
#endif
	int received = 0;

	struct sk_buff *skb_pre;
	dma_addr_t dma_handle_pre;

	i = lp->rxdesc_end;

#ifdef TXSS_ETH_MAX_QUEUE_LEN
	spar = txss_readl(&tr->drxspar);
	lpar = txss_readl(&tr->drxlpar);
	rx_desc = &lp->rx_desc[i];
	if (!(lp->rx_desc[i].rd0 & RD0_RACT))	/* check write back */
		lp->lstats.rx_max_queue_len =
		    max((int)((((lpar - spar) / sizeof(struct txss_eth_rd))
			       + lp->rx_desc_num - lp->rxdesc_end)
			      % lp->rx_desc_num), lp->lstats.rx_max_queue_len);
#endif
	rx_desc = &lp->rx_desc[i];
	while (!(rx_desc->rd0 & RD0_RACT)) {
		int rx_good = (rx_desc->rd0 & RD0_RFE) ? 0 : 1;
		int rx_status = rx_desc->rd0 & RD0_RFS_MASK;
		struct sk_buff *skb;
		unsigned char *data;
		int pkt_len;

		/* workaround for receiving insane descriptors. */
		if ((rx_desc->rd0 & RD0_RFP_MASK) != RD0_RFP_ALL) {
			pr_info("%s: rd0 is not RD0_RFP_ALL.\n", dev->name);
			txss_eth_tx_timeout(dev);
			return received;
		}

		if (netif_msg_rx_status(lp))
			pr_info("%s: receive frame #%02d (status 0x%08x).\n",
				dev->name, i, rx_status);

		pr_debug("lp->rx_desc[%3d].rd0 = 0x%08x, rd1 = 0x%08x, rd2 = 0x%08x\n",
			 i, rx_desc->rd0, rx_desc->rd1, rx_desc->rd2);

		if (rx_good) {
			if (--limit < 0)
				break;

			skb_pre = alloc_rxbuf_skb(dev, &dma_handle_pre);

			if (!skb_pre) {
				txss_eth_rx_retry = 1;
				lp->lstats.alloc_rxbuf_skb_failed++;
				break;
			} else {
				txss_eth_rx_retry = 0;
			}

			skb = lp->rx_skbs[i].skb;

			dma_unmap_single(&lp->pdev->dev, lp->rx_skbs[i].skb_dma,
					 lp->max_frame_size, DMA_FROM_DEVICE);
			pkt_len = RD1_RFL_GET(lp->rx_desc[i].rd1) - CSUM_LEN;
			data = skb_put(skb, pkt_len);

			if (netif_msg_pktdata(lp))
				print_eth(data);

#ifdef TXSS_ETH_USE_CHECKSUM_HW
			skb->csum = *(u16 *)((u32)skb->data + pkt_len);
			skb->ip_summed = CHECKSUM_COMPLETE;
#endif
			skb->protocol = eth_type_trans(skb, dev);
			netif_receive_skb(skb);
			received++;

			dev->last_rx = jiffies;
			lp->stats.rx_packets++;
			lp->stats.rx_bytes += pkt_len;

			lp->rx_skbs[i].skb = skb_pre;
			lp->rx_skbs[i].skb_dma = dma_handle_pre;
			rx_desc->rd2 = RD2_RBA_SET(lp->rx_skbs[i].skb_dma);
		} else {
			lp->stats.rx_errors++;
			if (netif_msg_rx_err(lp))
				pr_info("%s: Rx error (status 0x%04x)\n",
					dev->name, rx_status);
#ifdef SHOW_ERROR_PKTDATA
			{
				char output[128];
				char *p = output;
				u16 *tmp;
				int j;
				pkt_len = RD1_RFL_GET(rx_desc->rd1);
				skb = lp->rx_skbs[i].skb;
				dma_map_single(&lp->pdev->dev, skb->data,
					       lp->max_frame_size,
					       DMA_FROM_DEVICE);
				tmp = (u16 *)skb_put(skb, pkt_len);
				for (j = 0; j < pkt_len; j += sizeof(*tmp)) {
					if (j % 0x10 == 0 && output != p) {
						pr_info("%s\n", output);
						p = output;
					}
					if (j % 0x10 == 0)
						p += sprintf(p, "%08x:",
							     (u32)tmp);
					p += sprintf(p, " %0*x",
						     sizeof(*tmp) * 2, *tmp++);
				}
				pr_info("%s\n", output);
			}
#endif
			/* FIFO overflow frame */
			if (rx_status & RD0_RFS_ROC)
				;	/* nothing to do */
			/* abort receive */
			if (rx_status & RD0_RFS_RABT)
				lp->stats.rx_missed_errors++;
		}

		rx_desc->rd0 &= RD0_RDL;	/* clear RD0 */
		mb(); /* barrier */
		rx_desc->rd0 |= RD0_RACT;
		mb(); /* barrier */

		lp->rxdesc_end = (lp->rxdesc_end + 1) % lp->rx_desc_num;
		i = lp->rxdesc_end;

		rx_desc = &lp->rx_desc[i];
	}
	txss_writel(DMARXR_START, &tr->dmarxr);	/* Rx DMA restart */
	return received;
}

static int txss_eth_tx_done(struct net_device *dev)
{
	struct txss_eth_local *lp = netdev_priv(dev);
	struct txss_eth_td *tx_desc;
	unsigned int i;

	i = lp->txdesc_end;

	tx_desc = &lp->tx_desc[i];
	while ((lp->txdesc_start != lp->txdesc_end) &&
	       (!(tx_desc->td0 & TD0_TACT))) {
		int tx_good = (tx_desc->td0 & TD0_TFE) ? 0 : 1;
		int tx_status = tx_desc->td0 & TD0_TFS_MASK;
		struct sk_buff *skb = lp->tx_skbs[i].skb;

		if (netif_msg_tx_done(lp))
			pr_info("%s: complete Tx desc #%02d.\n",
				dev->name, i);

		if (tx_good) {
			lp->stats.tx_packets++;
		} else {
			lp->stats.tx_errors++;
			if (netif_msg_tx_err(lp)) {
				pr_warn("%s: Tx error (status 0x%04x)\n",
					dev->name, tx_status);
				pr_warn("lp->tx_desc[%d].td0=0x%08x, td1=0x%08x, td2=0x%08x\n",
					i, tx_desc->td0, tx_desc->td1,
					tx_desc->td2);
			}
			if (tx_status & TD0_TFS_TABT)
				lp->stats.tx_aborted_errors++;
		}

		if (skb) {
			lp->stats.tx_bytes += skb->len;
			dma_unmap_single(&lp->pdev->dev, lp->tx_skbs[i].skb_dma,
					 skb->len, DMA_TO_DEVICE);
			lp->tx_skbs[i].skb = NULL;
			lp->tx_skbs[i].skb_dma = 0;
			dev_kfree_skb_any(skb);
		}
		lp->txdesc_end = (lp->txdesc_end + 1) % lp->tx_desc_num;
		i = lp->txdesc_end;
		tx_desc = &lp->tx_desc[i];
	}

	if (netif_queue_stopped(dev) && !txss_eth_tx_full(dev))
		netif_wake_queue(dev);
	return 0;
}

/* initialize function */

static void txss_eth_rgmii_setup(struct net_device *dev)
{
	struct txss_eth_regs __iomem *tr =
	    (struct txss_eth_regs __iomem *)dev->base_addr;

	txss_writel(PHYIFR_RGMII, &tr->phyifr);
}

static void txss_eth_rx_stop(struct net_device *dev)
{
	struct txss_eth_regs __iomem *tr =
	    (struct txss_eth_regs __iomem *)dev->base_addr;
	struct txss_eth_local *lp = netdev_priv(dev);
	u32 maccr;
	int x_time, mult;
	int ret;

	mult = (lp->speed == SPEED_1000 ? 1 :
		lp->speed == SPEED_100 ? 10 : 100);

	/* MAC: Rx stop */
	maccr = txss_readl(&tr->maccr);
	maccr &= ~MACCR_RPE;
	txss_writel(maccr, &tr->maccr);

	/* Wait for 1 frame receiving */
	x_time = (((lp->max_frame_size + 12 + 8) * 8 / 1000) + 1) * mult;
	checkreg_timeout(&tr->maccr, 0x0, 0x1, x_time);

	/* DMA: Rx stop */
	ret = checkreg_timeout(&tr->rxfifostsr, RXFIFOSTSR_FAM_MASK,
			       0x0, 1000000); /* 1sec */
	if (ret)
		pr_err("%s: Timeout in DMA Rx stop (rxfifostsr = %08x).\n",
		       dev->name, txss_readl(&tr->rxfifostsr));
}

static void txss_eth_tx_stop(struct net_device *dev)
{
	struct txss_eth_regs __iomem *tr =
	    (struct txss_eth_regs __iomem *)dev->base_addr;
	struct txss_eth_local *lp = netdev_priv(dev);
	u32 maccr;
	int x_time, y_time, mult;
	int ret, timeout;

	mult = (lp->speed == SPEED_1000 ? 1 :
		lp->speed == SPEED_100 ? 10 : 100);

	/* DMA: Tx stop */
	txss_writel(DMATXR_STOP, &tr->dmatxr);
	ret = checkreg_timeout(&tr->dmatxr, 0xffffffff,
			       DMATXR_STOP, 1000000); /* 1sec */
	if (ret)
		pr_err("%s: Timeout in DMA Tx stop. %08x\n",
		       dev->name, txss_readl(&tr->dmatxr));

	/* Full duplex - 1000Mbps:0.08ms, 100Mbps:0.8ms, 10Mbps:8ms */
	/* Half duplex - 1000Mbps:14.6ms, 100Mbps:146ms, 10Mbps:1460ms */
	timeout = (lp->duplex == DUPLEX_FULL) ? 80 * mult : 15000 * mult;
	ret = checkreg_timeout(&tr->txfifostsr, TXFIFOSTSR_BUSY_MASK,
			       0x0, timeout);
	if (ret)
		pr_err("%s: Timeout in DMA Tx stop (fifostsr = %08x).\n",
		       dev->name, txss_readl(&tr->txfifostsr));

	/* Wait for 1 frame sending */
	x_time = (((lp->max_frame_size + 12 + 8) * 8 / 1000) + 1) * mult;
	y_time = ((lp->speed != 0) && (lp->duplex == DUPLEX_HALF)) ?
	    (((1 + 3 + 7 + 15 + 31 + 63 + 127 + 255 + 511 +
	       1023 * 6) * 512 / 1000) + 1) * mult : 0;
	checkreg_timeout(&tr->dmatxr, 0x0, 0x1, x_time + y_time);

	/* MAC: Tx stop */
	maccr = txss_readl(&tr->maccr);
	maccr &= ~MACCR_TPE;
	txss_writel(maccr, &tr->maccr);
}

static void txss_eth_soft_reset(struct net_device *dev)
{
	struct txss_eth_regs __iomem *tr =
	    (struct txss_eth_regs __iomem *)dev->base_addr;
	int ret;

	/* start descriptor engine */
	txss_writel(DESCCR_ENR | DESCCR_ENT, &tr->desccr);

	/* Rx/Tx stop */
	txss_eth_rx_stop(dev);
	txss_eth_tx_stop(dev);

	/* disable interrupt */
	txss_writel(0x0, &tr->dmaintenr);
	txss_writel(0x0, &tr->macintenr);

	/* soft reset */
	txss_writel(DMACR_SWRR | DMACR_SWRT, &tr->dmacr);
	ret = checkreg_timeout(&tr->dmacr, DMACR_SWRR | DMACR_SWRT,
			 0x0, 1000); /* 1ms */
	if (ret)
		pr_err("%s: Controller soft reset failed.\n",
		       dev->name);
}

static void txss_eth_hard_reset(struct net_device *dev)
{
	txss_eth_soft_reset(dev);
}

static void txss_eth_phy_init(struct net_device *dev)
{
	struct txss_eth_regs __iomem *tr =
	    (struct txss_eth_regs __iomem *)dev->base_addr;
	struct txss_eth_local *lp = netdev_priv(dev);
	struct txss_eth_platform_data *pdata = lp->pdev->dev.platform_data;

	txss_writel(PHYINTR_PHYIP_LOW, &tr->phyintr);
	/* mdiocycr: (200ns / (1000000000 / SYSTEM_CLOCK) - 1) */
	txss_writel(((pdata->system_clock + 5000000 - 1) / 5000000) - 1,
		    &tr->mdiocycr);
}

static void txss_eth_chip_reset(struct net_device *dev)
{
	txss_eth_soft_reset(dev);
	txss_eth_phy_init(dev);
}

static void txss_eth_chip_init(struct net_device *dev)
{
	struct txss_eth_local *lp = netdev_priv(dev);
	struct txss_eth_regs __iomem *tr =
	    (struct txss_eth_regs __iomem *)dev->base_addr;
	struct txss_eth_platform_data *pdata = lp->pdev->dev.platform_data;
	u32 reg;
	u32 uaddr, laddr;

	txss_writel(DMACR_DFL, &tr->dmacr);
	txss_writel(0x0, &tr->errmaskr);
	txss_writel(pdata->fifosizer ?: FIFOSIZER_DFL, &tr->fifosizer);
	txss_writel(TXFIFOTHR_SF, &tr->txfifothr);
	txss_writel(DMARXMODR_RCVMOD, &tr->dmarxmodr);
	/* for IP 4byte aligned */
	txss_writel(RXPADR_PADS(NET_IP_ALIGN) | RXPADR_PADP(0), &tr->rxpadr);
	txss_writel(RXFIFOTHR_RFF(lp->pause_rff) | RXFIFOTHR_RFD(lp->pause_rfd),
		    &tr->rxfifothr);
	txss_writel(DMAINTR_RINT8, &tr->errmaskr);
	txss_writel(DMAINTR_ALL, &tr->dmaintr);
	txss_writel(DMAINTR_FTC1 | DMAINTR_FTC0 | DMAINTR_RFRMER | DMAINTR_TDE
		    | DMAINTR_TFE | DMAINTR_FRC | DMAINTR_RDE | DMAINTR_RFE,
		    &tr->dmaintenr);

	uaddr = (dev->dev_addr[0] << 24) | (dev->dev_addr[1] << 16)
	    | (dev->dev_addr[2] << 8) | (dev->dev_addr[3] << 0);
	laddr = (dev->dev_addr[4] << 8) | (dev->dev_addr[5] << 0);
	txss_writel(uaddr, &tr->umacar);
	txss_writel(laddr, &tr->lmacar);
	txss_writel(BSTLMTR_SET, &tr->bstlmtr);
	txss_writel(LENLMTR_LENLMT(dev->mtu + ETH_HLEN
				   + ETH_FCS_LEN + VLAN_HLEN),
		    &tr->lenlmtr);
	txss_writel(lp->pause_time, &tr->apftpr);
	txss_writel(0x0, &tr->pfrtlmtr);
	reg = MACCR_TRCCM | MACCR_RZPF | MACCR_TZPF;
	if (lp->rx_pause)
		reg |= MACCR_RXF;
	if (lp->tx_pause)
		reg |= MACCR_TXF;
#ifdef TXSS_ETH_USE_CHECKSUM_HW
	reg |= MACCR_RCSC;
#endif
	txss_writel(reg, &tr->maccr);
	txss_writel(MACINTR_ALL, &tr->macintr);
	txss_writel(MACINTR_FCI, &tr->macintenr);

	txss_writel(pdata->emacdrr, &tr->emacdrr);
	txss_writel(EMACDRTRGR_DFL, &tr->emacdrtrgr);
	txss_writel(EMACDRENR_DRDEN, &tr->emacdrenr);
	/* disable EMACINTR_SERR */
	txss_writel(EMACINTR_DMAINT, &tr->emacintenr);
	txss_writel(EMACINTR_SERR, &tr->emacintr);

	txss_writel(DMARXR_START, &tr->dmarxr);	/* Rx DMA start */

	reg = txss_readl(&tr->maccr);
	/* enable mac function */
	txss_writel(reg | MACCR_RPE | MACCR_TPE, &tr->maccr);
}

static char *macaddr;
module_param(macaddr, charp, 0);
MODULE_PARM_DESC(macaddr, "Ethernet MAC address");

static int txss_eth_init_devaddr(struct net_device *dev)
{
	if (macaddr &&
	    mac_pton(macaddr, dev->dev_addr) &&
	    is_valid_ether_addr(dev->dev_addr))
		return 0;
	return -ENODEV;
}

static int txss_change_mtu(struct net_device *dev, int new_mtu)
{
	struct txss_eth_local *lp = netdev_priv(dev);
	int max_frame = new_mtu + ETH_HLEN + ETH_FCS_LEN;
	struct txss_eth_regs __iomem *tr =
	    (struct txss_eth_regs __iomem *)dev->base_addr;

	if ((max_frame < TXSS_MIN_MTU) ||
	    (max_frame + VLAN_HLEN > lp->max_frame_size)) {
		pr_warn("%s: Invalid MTU setting\n", DRV_DEVNAME);
		return -EINVAL;
	}
	if (max_frame + VLAN_HLEN < RX_BUF_SIZE)
		max_frame = RX_BUF_SIZE;

	txss_writel(LENLMTR_LENLMT(max_frame), &tr->lenlmtr);
	dev->mtu = new_mtu;

	return 0;
}

static netdev_features_t txss_fix_features(struct net_device *dev,
					   netdev_features_t features)
{
#ifdef TXSS_ETH_USE_CHECKSUM_HW
	/* changing NETIF_F_RXCSUM is not supported */
	if ((features ^ dev->features) & NETIF_F_RXCSUM)
		features ^= NETIF_F_RXCSUM;
#endif
	return features;
}

static const struct net_device_ops txss_eth_netdev_ops = {
	.ndo_open = txss_eth_open,
	.ndo_stop = txss_eth_stop,
	.ndo_start_xmit = txss_eth_send_packet,
	.ndo_get_stats = txss_eth_get_stats,
	.ndo_set_rx_mode = txss_eth_set_multicast_list,
	.ndo_tx_timeout = txss_eth_tx_timeout,
	.ndo_do_ioctl = txss_eth_ioctl,
	.ndo_validate_addr = eth_validate_addr,
	.ndo_change_mtu = txss_change_mtu,
	.ndo_set_mac_address = eth_mac_addr,
#ifdef CONFIG_NET_POLL_CONTROLLER
	.ndo_poll_controller = txss_eth_poll_controller,
#endif
	.ndo_fix_features = txss_fix_features,
};

static int txss_eth_probe(struct platform_device *pdev)
{
	struct net_device *dev;
	struct txss_eth_local *lp;
	struct resource *res;
	int ret;
	struct txss_eth_platform_data *pdata = pdev->dev.platform_data;
#ifdef CONFIG_OF
	struct device_node *np;
	const unsigned int *dt_phyaddr;
#endif

	pr_info("%s\n", print_version);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		ret = -ENODEV;
		goto err_out;
	}

	if (!request_mem_region
	    (res->start, res->end - res->start + 1, DRV_DEVNAME)) {
		ret = -EBUSY;
		goto err_out;
	}

	dev = alloc_etherdev(sizeof(struct txss_eth_local));
	if (!dev) {
		pr_warn("%s: could not allocate net_device.\n",
			DRV_DEVNAME);
		ret = -ENODEV;
		goto err_out_free_region;
	}

	SET_NETDEV_DEV(dev, &pdev->dev);
	platform_set_drvdata(pdev, dev);
	lp = netdev_priv(dev);
	lp->dev = dev;
	lp->pdev = pdev;

#ifdef CONFIG_OF
	np = of_find_compatible_node(NULL, NULL, "toshiba,txss-eth");
	if (np) {
		if (options.phyaddr == PHY_MAX_ADDR) {
			dt_phyaddr = of_get_property(np, "phyaddr", NULL);
			if (dt_phyaddr)
				options.phyaddr = be32_to_cpu(*dt_phyaddr);
		}

		if (options.hec_phyaddr == PHY_MAX_ADDR) {
			dt_phyaddr = of_get_property(np, "hec_phyaddr", NULL);
			if (dt_phyaddr)
				options.hec_phyaddr = be32_to_cpu(*dt_phyaddr);
		}
		of_node_put(np);
	}
#endif

	if (options.speed && options.speed != 100 && options.speed != 1000)
		options.speed = 100;
	if (!((options.phyaddr >= 0) && (options.phyaddr < PHY_MAX_ADDR))) {
		current_phyaddr = PHY_MAX_ADDR;
		options.phyaddr = PHY_MAX_ADDR;
	} else {
		current_phyaddr = options.phyaddr;
	}

	lp->tx_desc_num = TX_DESC_NUM;
	lp->rx_desc_num = RX_DESC_NUM;
	if (options.tx_desc_num)
		lp->tx_desc_num = (unsigned int)options.tx_desc_num;
	if (options.rx_desc_num)
		lp->rx_desc_num = (unsigned int)options.rx_desc_num;

	dev->netdev_ops = &txss_eth_netdev_ops;
	dev->watchdog_timeo = msecs_to_jiffies(400);
	netif_napi_add(dev, &lp->napi, txss_eth_poll, NAPI_WEIGHT);
	lp->max_frame_size = RX_BUF_SIZE;
	if (!options.rx_buf_size && pdata && pdata->rx_buf_size)
		options.rx_buf_size = pdata->rx_buf_size;
	if (options.rx_buf_size) {
		int max_frame;
		max_frame = options.rx_buf_size
			+ ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN;
		if (max_frame > RX_BUF_SIZE && max_frame <= RX_BUF_MAX_SIZE)
			lp->max_frame_size = max_frame;
		else if (max_frame > RX_BUF_MAX_SIZE)
			lp->max_frame_size = RX_BUF_MAX_SIZE;
	}
	lp->pause_rff = RXFIFOTHR_RFF_DFL;
	lp->pause_rfd = RXFIFOTHR_RFD_DFL;
	if (options.pause_time)
		lp->pause_time = options.pause_time;
	else
		lp->pause_time = PAUSE_TIME_DFL;
	lp->rx_pause = 1;
	lp->tx_pause = 0;

	dev->irq = platform_get_irq(pdev, 0);
	dev->base_addr = (unsigned long)
	    ioremap(res->start, res->end - res->start + 1);
	if (!dev->base_addr) {
		pr_warn("%s: could not allocate dev->base_addr.\n",
			DRV_DEVNAME);
		ret = -ENOMEM;
		goto err_out_free_region_netdev;
	}
	INIT_WORK(&lp->restart_work, txss_eth_restart);
#ifdef TXSS_ETH_USE_CHECKSUM_HW
	dev->hw_features = NETIF_F_RXCSUM;
	dev->features = NETIF_F_RXCSUM;
#endif
	txss_eth_set_ethtool_ops(dev);
	if (pdata && pdata->is_rgmii)
		txss_eth_rgmii_setup(dev);
	ret = register_netdev(dev);
	if (ret) {
		pr_warn("%s: could not register netdev.\n",
			DRV_DEVNAME);
		goto err_out_free_region_netdev;
	}

	txss_eth_hard_reset(dev);
	txss_eth_phy_init(dev);

	ret = txss_eth_mii_init(dev);
	if (ret) {
		pr_warn("%s: mii_init failure.\n", DRV_DEVNAME);
		goto err_out_unregister_netdev;
	}

	/* retrieve the ethernet address */
	memset(dev->dev_addr, 0, sizeof(dev->dev_addr));
#ifdef CONFIG_OF
	np = of_find_compatible_node(NULL, NULL, "toshiba,txss-eth");
	if (np) {
		const unsigned char *mac_address;
		mac_address = of_get_property(np, "local-mac-address", NULL);
		if (mac_address)
			memcpy(dev->dev_addr, mac_address, sizeof(char) * 6);
		of_node_put(np);
	}
#endif
	if (!is_valid_ether_addr(dev->dev_addr)) {
		if (txss_eth_init_devaddr(dev)) {
			dev_warn(&pdev->dev, "not valid ether address\n");
			random_ether_addr(dev->dev_addr);
		}
	}

	memcpy(dev->perm_addr, dev->dev_addr, dev->addr_len);
	pr_info("%s: %s at 0x%lx, %pM, IRQ %d\n",
		dev->name,
		DRV_DEVNAME,
		dev->base_addr,
		dev->dev_addr, dev->irq);

	pr_info("Default PHY address %d, HEC PHY address %d, PHY PWR Mng %d\n",
		options.phyaddr, options.hec_phyaddr, options.phypwrmng);

	lp->msg_enable = TXSS_MSG_FLAG;

	return 0;

err_out_unregister_netdev:
	unregister_netdev(dev);
err_out_free_region_netdev:
	free_netdev(dev);
err_out_free_region:
	release_mem_region(res->start, res->end - res->start + 1);
err_out:
	pr_warn("%s: not found (%d).\n", DRV_DEVNAME, ret);
	return ret;
}

static int txss_eth_remove(struct platform_device *pdev)
{
	struct net_device *dev = platform_get_drvdata(pdev);
	struct txss_eth_local *lp = netdev_priv(dev);
	struct resource *res;

	cancel_work_sync(&lp->restart_work);

	unregister_netdev(dev);

	iounmap((void __iomem *)dev->base_addr);
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(res->start, res->end - res->start + 1);
	platform_set_drvdata(pdev, NULL);

	mdiobus_unregister(lp->mii_bus);
	kfree(lp->mii_bus->irq);

	free_netdev(dev);
	return 0;
}

#ifdef CONFIG_PM
static int txss_eth_suspend(struct platform_device *pdev, pm_message_t state)
{
	struct net_device *dev = platform_get_drvdata(pdev);

	if (!netif_running(dev))
		return 0;

	netif_device_detach(dev);

	txss_eth_stop(dev);

	return 0;
}

static int txss_eth_resume(struct platform_device *pdev)
{
	struct net_device *dev = platform_get_drvdata(pdev);
	struct txss_eth_platform_data *pdata = pdev->dev.platform_data;

	if (pdata && pdata->is_rgmii)
		txss_eth_rgmii_setup(dev);

	txss_eth_chip_reset(dev);

	if (!netif_running(dev)) {
		txss_eth_chip_reset(dev);
		return 0;
	}

	if (txss_eth_open(dev) < 0) {
		pr_err("txss_eth %s: open failed\n", dev->name);
		return -EIO;
	}

	netif_device_attach(dev);

	return 0;
}

#endif /* CONFIG_PM */

static struct platform_driver txss_eth_driver = {
	.probe = txss_eth_probe,
	.remove = txss_eth_remove,
#ifdef CONFIG_PM
	.suspend = txss_eth_suspend,
	.resume = txss_eth_resume,
#endif /* CONFIG_PM */
	.driver = {
		   .name = DRV_DEVNAME,
		   }
};

module_param_named(tx_desc, options.tx_desc_num, int, 0);
MODULE_PARM_DESC(tx_desc, "transfer descriptor ring size");
module_param_named(rx_desc, options.rx_desc_num, int, 0);
MODULE_PARM_DESC(rx_desc, "receive descriptor ring size");
module_param_named(rx_buf_size, options.rx_buf_size, int, 0);
MODULE_PARM_DESC(rx_buf_size, "receive buffer size");
module_param_named(pause_time, options.pause_time, int, 0);
MODULE_PARM_DESC(pause_time, "pause time for flow control");
module_param_named(phyaddr, options.phyaddr, int, 0);
MODULE_PARM_DESC(phyaddr, "PHY address setting");
module_param_named(speed, options.speed, int, 0);
MODULE_PARM_DESC(speed, "SPEED setting");
module_param_named(phypwrmng, options.phypwrmng, int, 0);
MODULE_PARM_DESC(phypwrmng, "PHY Power Management Enable");

module_param_named(phymask, options.phymask, int, 0);
MODULE_PARM_DESC(phymask, "PHY address mask");

module_param_named(hec_phyaddr, options.hec_phyaddr, int, 0);
MODULE_PARM_DESC(hec_phyaddr, "PHY address for HEC");

module_param_named(fast_link, fast_link, int, 0);
MODULE_PARM_DESC(fast_link, "PHY fast link");

static int __init txss_eth_init(void)
{
	BUG_ON(NET_SKB_PAD < 32);	/* RD0.RBA 32byte DMA alignment */
	return platform_driver_register(&txss_eth_driver);
}

static void __exit txss_eth_exit(void)
{
	platform_driver_unregister(&txss_eth_driver);
}

module_init(txss_eth_init);
module_exit(txss_eth_exit);
