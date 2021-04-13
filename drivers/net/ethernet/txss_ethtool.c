/*
 * linux/drivers/net/txss_ethtool.c
 *
 * TX Sub System EtherMAC Controller ethtool driver
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

#include <linux/netdevice.h>
#include <linux/ethtool.h>
#include <linux/phy.h>
#include <linux/spinlock.h>
#include <linux/platform_data/txss_eth.h>
#include "txss_eth.h"

static int
txss_eth_get_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct txss_eth_local *lp = netdev_priv(dev);

	if (!lp->phydev)
		return -ENODEV;
	return phy_ethtool_gset(lp->phydev, cmd);
}

static int
txss_eth_set_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct txss_eth_local *lp = netdev_priv(dev);

	if (!lp->phydev)
		return -ENODEV;
	return phy_ethtool_sset(lp->phydev, cmd);
}

static void
txss_eth_get_drvinfo(struct net_device *dev, struct ethtool_drvinfo *info)
{
	strcpy(info->driver, txss_eth_driver_name);
	strcpy(info->version, txss_eth_driver_version);
}

#define TXSS_ETH_REGS_LEN   384
#define TXSS_ETH_REGS_START 0x1000
static int txss_eth_get_regs_len(struct net_device *dev)
{
	return TXSS_ETH_REGS_LEN * sizeof(u32);
}

static void
txss_eth_get_regs(struct net_device *dev, struct ethtool_regs *regs, void *p)
{
	u32 *r = p;
	unsigned long base = dev->base_addr + TXSS_ETH_REGS_START;
	int i;

	memset(r, 0, TXSS_ETH_REGS_LEN * sizeof(u32));

	for (i = 0; i < TXSS_ETH_REGS_LEN; i++) {
		*r = txss_readl((void __iomem *)(base + i * sizeof(u32)));
		r++;
	}
}

static u32 txss_eth_get_msglevel(struct net_device *dev)
{
	struct txss_eth_local *lp = netdev_priv(dev);
	return lp->msg_enable;
}

static void txss_eth_set_msglevel(struct net_device *dev, u32 datum)
{
	struct txss_eth_local *lp = netdev_priv(dev);
	lp->msg_enable = datum;
}

static int txss_eth_nway_reset(struct net_device *dev)
{
	struct txss_eth_local *lp = netdev_priv(dev);
	return phy_start_aneg(lp->phydev);
}

static int txss_eth_get_coalesce(struct net_device *dev,
				 struct ethtool_coalesce *coal)
{
	struct txss_eth_local *lp = netdev_priv(dev);

	coal->rx_coalesce_usecs = lp->rx_coalesce_usecs;
	return 0;
}

static int txss_eth_set_coalesce(struct net_device *dev,
				 struct ethtool_coalesce *coal)
{
	struct txss_eth_regs __iomem *tr =
	    (struct txss_eth_regs __iomem *)dev->base_addr;
	struct txss_eth_local *lp = netdev_priv(dev);
	struct txss_eth_platform_data *pdata = lp->pdev->dev.platform_data;
	u32 idly;

	lp->rx_coalesce_usecs = coal->rx_coalesce_usecs;
#ifdef IRQ_TYPE_UDLY
	return set_irq_type(dev->irq, IRQ_TYPE_UDLY(lp->rx_coalesce_usecs));
#else
	if (lp->rx_coalesce_usecs) {
		idly =
		    (pdata->system_clock / 1000000) * lp->rx_coalesce_usecs;
		idly <<= 4;
		if (idly & ~EMACINTDCR_IDLY_MSK) {
			pr_info("%s: %s: overflow IDLY = %x\n",
				dev->name, __func__, idly);
			return -EINVAL;
		}
		idly &= EMACINTDCR_IDLY_MSK;
		txss_writel(idly | EMACINTDCR_IDLYEN, &tr->emacintdcr);
	} else {
		txss_writel(0x0, &tr->emacintdcr);
	}
	return 0;
#endif
}

static void txss_eth_get_ringparam(struct net_device *dev,
				   struct ethtool_ringparam *ring)
{
	struct txss_eth_local *lp = netdev_priv(dev);

	ring->rx_pending = lp->rx_desc_num;
	ring->tx_pending = lp->tx_desc_num;
}

static int txss_eth_get_sset_count(struct net_device *dev, int string_set)
{
	struct txss_eth_local *lp = netdev_priv(dev);
	switch (string_set) {
	case ETH_SS_STATS:
		return sizeof(lp->lstats) / sizeof(int) + 2;
	default:
		return -EINVAL;
	}
}

static void txss_eth_get_pauseparam(struct net_device *dev,
				    struct ethtool_pauseparam *pause)
{
	struct txss_eth_local *lp = netdev_priv(dev);

	pause->autoneg = AUTONEG_ENABLE;
	pause->tx_pause = lp->tx_pause;
	pause->rx_pause = lp->rx_pause;
}

static int txss_eth_set_pauseparam(struct net_device *dev,
				   struct ethtool_pauseparam *pause)
{
	struct txss_eth_local *lp = netdev_priv(dev);
	struct txss_eth_regs __iomem *tr =
	    (struct txss_eth_regs __iomem *)dev->base_addr;
	int retval = 0;
	u32 cur_maccr, maccr;

	lp->tx_pause = pause->tx_pause;
	lp->rx_pause = pause->rx_pause;

	if (netif_running(dev)) {
		cur_maccr = txss_readl(&tr->maccr);
		maccr = cur_maccr & ~(MACCR_TXF | MACCR_TXF);
		maccr |= lp->tx_pause ? MACCR_TXF : 0;
		maccr |= lp->rx_pause ? MACCR_RXF : 0;

		if (maccr != cur_maccr)
			txss_writel(maccr, &tr->maccr);
	}
	return retval;
}

static void
txss_eth_get_ethtool_stats(struct net_device *dev, struct ethtool_stats *stats,
			   u64 *data)
{
	struct txss_eth_local *lp = netdev_priv(dev);
	int i = 0;

	txss_eth_update_pftxcntr(dev);
	txss_eth_update_pfrxcntr(dev);

	data[i++] = lp->lstats.tx_ints;
	data[i++] = lp->lstats.rx_ints;
	data[i++] = lp->tx_desc_num;
	data[i++] = lp->rx_desc_num;
	data[i++] = lp->lstats.tx_max_queue_len;
	data[i++] = lp->lstats.rx_max_queue_len;
	data[i++] = lp->lstats.tx_full;
	data[i++] = lp->lstats.tx_pause_count;
	data[i++] = lp->lstats.rx_pause_count;
	data[i++] = lp->lstats.rx_frame_overflow;
	data[i++] = lp->lstats.tx_desc_exhausted;
	data[i++] = lp->lstats.tx_fifo_underflow;
	data[i++] = lp->lstats.rx_desc_exhausted;
	data[i++] = lp->lstats.rx_fifo_overflow;
	data[i++] = lp->lstats.fci;
	data[i++] = lp->lstats.tx_timeouts;
	data[i++] = lp->lstats.rx_enable_timeouts;
	data[i++] = lp->lstats.tx_enable_timeouts;
	data[i++] = lp->lstats.frc_rx_rescheduled;
	data[i++] = lp->lstats.alloc_rxbuf_skb_failed;
}

/* *INDENT-OFF* */
static struct {
	const char str[ETH_GSTRING_LEN];
} ethtool_stats_keys[] = {
	{ "Interrupt of Tx" },
	{ "Interrupt of Rx"},
	{ "Tx descriptor ring size"},
	{ "Rx descriptor ring size"},
	{ "Tx max queue length"},
	{ "Rx max queue length"},
	{ "Tx descriptor full"},
	{ "Tx PAUSE frame count"},
	{ "Rx PAUSE frame count"},
	{ "Rx frame overflow"},
	{ "Tx descriptor exhausted"},
	{ "Tx FIFO underflow"},
	{ "Rx descriptor exhausted"},
	{ "Rx FIFO overflow"},
	{ "False Carrier Indication"},
	{ "Tx Timeout"},
	{ "Rx Enable Timeout"},
	{ "Tx Enable Timeout"},
	{ "FRC rx rescheduled"},
	{ "alloc_rxbuf_skb failed"},
};
/* *INDENT-ON* */

static void
txss_eth_get_strings(struct net_device *dev, u32 stringset, u8 *data)
{
	memcpy(data, ethtool_stats_keys, sizeof(ethtool_stats_keys));
}

static struct ethtool_ops txss_ethtool_ops = {
	.get_settings = txss_eth_get_settings,
	.set_settings = txss_eth_set_settings,
	.get_drvinfo = txss_eth_get_drvinfo,
	.get_regs_len = txss_eth_get_regs_len,
	.get_regs = txss_eth_get_regs,
	.get_link = ethtool_op_get_link,
	.get_msglevel = txss_eth_get_msglevel,
	.set_msglevel = txss_eth_set_msglevel,
	.nway_reset = txss_eth_nway_reset,
	.get_coalesce = txss_eth_get_coalesce,
	.set_coalesce = txss_eth_set_coalesce,
	.get_ringparam = txss_eth_get_ringparam,
	.get_strings = txss_eth_get_strings,
	.get_sset_count = txss_eth_get_sset_count,
	.get_ethtool_stats = txss_eth_get_ethtool_stats,
	.get_pauseparam = txss_eth_get_pauseparam,
	.set_pauseparam = txss_eth_set_pauseparam,
};

void txss_eth_set_ethtool_ops(struct net_device *dev)
{
	SET_ETHTOOL_OPS(dev, &txss_ethtool_ops);
}
