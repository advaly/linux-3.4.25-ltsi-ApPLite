/*
 * drivers/usb/gadget/applite-udc.c
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

/* #define VERBOSE_DEBUG */

#include <linux/device.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/ioport.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/list.h>
#include <linux/interrupt.h>
#include <linux/mm.h>
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/irq.h>
#include <linux/clk.h>
#include <linux/err.h>
#include <linux/seq_file.h>
#include <linux/debugfs.h>
#include <linux/io.h>
#include <linux/prefetch.h>
#include <linux/gpio.h>

#include <asm/byteorder.h>
#include <asm/dma.h>
#include <asm/mach-types.h>
#include <asm/unaligned.h>

#include <linux/usb/ch9.h>
#include <linux/usb/gadget.h>
#include <linux/usb/otg.h>

#include <mach/platform.h>

#include "applite-udc.h"
#include "applite-regs.h"

#define EP0_CON		0
#define EP_MASK		0xF

#define DRIVER_VERSION  "1 March 2013"
#define DRIVER_DESC     "ApP Lite  USB Device Controller Gadget,"\
				"(c) 2012-2013 TOSHIBA Corporation"
static const char driver_name[] = "applite-udc";
static const char ep0name[] = "ep0-control";
struct al_udc  *the_controller;

/* Max packet size*/
static unsigned int ep0_fifo_size = 64;
static unsigned int ep_fifo_size =  512;
static unsigned int ep_fifo_size2 = 1024;
static int reset_available = 1;

/*#define APPLITE_USB_DEBUG*/
#ifdef APPLITE_USB_DEBUG
static char *state_names[] = {
	"WAIT_FOR_SETUP",
	"DATA_STATE_XMIT",
	"DATA_STATE_NEED_ZLP",
	"WAIT_FOR_OUT_STATUS",
	"DATA_STATE_RECV",
	"WAIT_FOR_COMPLETE",
	"WAIT_FOR_OUT_COMPLETE",
	"WAIT_FOR_IN_COMPLETE",
	"WAIT_FOR_NULL_COMPLETE",
};
	#define debug		pr_info

#define APPLITE_USB_DEBUG_REG
#ifdef APPLITE_USB_DEBUG_REG
	#define debug_reg	pr_info
#else
	#define debug(x, ...) { \
	}
#endif

#else
	#define debug(x, ...) { \
	}
#endif

#if 0
	#define al_readl(v, a) { \
		*v = readl(a); \
	}
	#define al_writel(v, a) { \
		writel(v, a); \
	}
#else
	#define al_readl(v, a) { \
		*v = __raw_readl(a); \
	}
	#define al_writel(v, a) { \
		__raw_writel((volatile uint32_t)v, a); \
	}
#endif

static struct al_usbotg_reg *reg;
static struct usb_ctrlrequest *usb_ctrl;
static dma_addr_t usb_ctrl_dma_addr;

/*
  Local declarations.
*/
static int al_ep_enable(struct usb_ep *ep,
		const struct usb_endpoint_descriptor *);
static int al_ep_disable(struct usb_ep *ep);
static struct usb_request *al_alloc_request(struct usb_ep *ep,
		gfp_t gfp_flags);
static void al_free_request(struct usb_ep *ep, struct usb_request *);

static int al_queue(struct usb_ep *ep, struct usb_request *, gfp_t gfp_flags);
static int al_dequeue(struct usb_ep *ep, struct usb_request *);
static int al_fifo_status(struct usb_ep *ep);
static void al_fifo_flush(struct usb_ep *ep);
static void al_ep0_read(struct al_udc *dev);
static void al_ep0_kick(struct al_udc *dev, struct al_ep *ep);
static void al_handle_ep0(struct al_udc *dev);
static int al_ep0_write(struct al_udc *dev);
static int write_fifo_ep0(struct al_ep *ep, struct al_request *req);
static void done(struct al_ep *ep, struct al_request *req, int status);
static void stop_activity(struct al_udc *dev,
		struct usb_gadget_driver *driver);
static int udc_enable(struct al_udc *dev);
static void udc_set_address(struct al_udc *dev, unsigned char address);
static void reconfig_usbd(void);
static void set_max_pktsize(struct al_udc *dev, enum usb_device_speed speed);
static void nuke(struct al_ep *ep, int status);
static int al_udc_set_halt(struct usb_ep *_ep, int value);
static void al_udc_set_nak(struct al_ep *ep);


/* ---------------------------------------------------------------------------
 *	device-scoped parts of the xfer dma
 * ---------------------------------------------------------------------------*/
static u8 clear_feature_num;
static int clear_feature_flag;

/* Bulk-Only Mass Storage Reset (class-specific request) */
#define GET_MAX_LUN_REQUEST	0xFE
#define BOT_RESET_REQUEST	0xFF

static inline void al_udc_ep0_zlp(struct al_udc *dev)
{
	u32 ep_ctrl;

	al_writel(usb_ctrl_dma_addr, (void __iomem *)&reg->in_endp[EP0_CON].diepdma);

	al_writel(DIEPT_SIZ_PKT_CNT(1), (void __iomem *)&reg->in_endp[EP0_CON].dieptsiz);

	al_readl(&ep_ctrl, (void __iomem *)&reg->in_endp[EP0_CON].diepctl);

	al_writel(ep_ctrl|DEPCTL_EPENA|DEPCTL_CNAK,
		(void __iomem *)&reg->in_endp[EP0_CON].diepctl);

	al_readl(&ep_ctrl, (void __iomem *)&reg->in_endp[EP0_CON].diepctl);
	debug("%s:EP0 ZLP DIEPCTL0 = 0x%x\n",
		__func__, ep_ctrl);
	dev->ep0state = WAIT_FOR_IN_COMPLETE;
}

static void al_udc_pre_setup(void)
{
	u32 ep_ctrl;

	debug("%s:Prepare Setup packets.\n", __func__);

	al_writel(DOEPT_SIZ_PKT_CNT(1) | sizeof(struct usb_ctrlrequest),
		(void __iomem *)&reg->out_endp[EP0_CON].doeptsiz);
	al_writel(usb_ctrl_dma_addr, (void __iomem *)&reg->out_endp[EP0_CON].doepdma);

	al_readl(&ep_ctrl, (void __iomem *)&reg->out_endp[EP0_CON].doepctl);
	al_writel(ep_ctrl|DEPCTL_EPENA, (void __iomem *)&reg->out_endp[EP0_CON].doepctl);

	al_readl(&ep_ctrl, (void __iomem *)&reg->in_endp[EP0_CON].diepctl);
	debug("%s:EP0 ZLP DIEPCTL0 = 0x%x\n", __func__, ep_ctrl);
	al_readl(&ep_ctrl, (void __iomem *)&reg->out_endp[EP0_CON].doepctl);
	debug("%s:EP0 ZLP DOEPCTL0 = 0x%x\n", __func__, ep_ctrl);
}

static inline void al_ep0_complete_out(void)
{
	u32 ep_ctrl;

	al_readl(&ep_ctrl, (void __iomem *)&reg->in_endp[EP0_CON].diepctl);
	debug("%s:EP0 ZLP DIEPCTL0 = 0x%x\n", __func__, ep_ctrl);
	al_readl(&ep_ctrl, (void __iomem *)&reg->out_endp[EP0_CON].doepctl);
	debug("%s:EP0 ZLP DOEPCTL0 = 0x%x\n",
		__func__, ep_ctrl);

	debug("%s : Prepare Complete Out packet.\n", __func__);

	al_writel(DOEPT_SIZ_PKT_CNT(1) | sizeof(struct usb_ctrlrequest),
		(void __iomem *)&reg->out_endp[EP0_CON].doeptsiz);
	al_writel(usb_ctrl_dma_addr, (void __iomem *)&reg->out_endp[EP0_CON].doepdma);

	al_readl(&ep_ctrl, (void __iomem *)&reg->out_endp[EP0_CON].doepctl);
	al_writel(ep_ctrl|DEPCTL_EPENA|DEPCTL_CNAK,
		(void __iomem *)&reg->out_endp[EP0_CON].doepctl);

	al_readl(&ep_ctrl, (void __iomem *)&reg->in_endp[EP0_CON].diepctl);
	debug("%s:EP0 ZLP DIEPCTL0 = 0x%x\n", __func__, ep_ctrl);
	al_readl(&ep_ctrl, (void __iomem *)&reg->out_endp[EP0_CON].doepctl);
	debug("%s:EP0 ZLP DOEPCTL0 = 0x%x\n", __func__, ep_ctrl);
}

static int setdma_rx(struct al_ep *ep, struct al_request *req)
{
	int retval;
	u32 *buf, ctrl;
	u32 length, pktcnt;
	u32 ep_num = ep_index(ep);
	u32 doepdma, doeptsiz, doepctl;

	buf = req->req.buf + req->req.actual;
	buf = req->req.buf;

	prefetchw(buf);

	length = min(req->req.length - req->req.actual, (u32)ep->ep.maxpacket);

	retval = usb_gadget_map_request(&the_controller->gadget, &req->req, 0); /* DMA FROM DEVICE */
	if (retval)
		return retval;

	ep->len = length;
	ep->dma_buf = buf;

	if (length == 0)
		pktcnt = 1;
	else
		pktcnt = (length - 1)/(ep->ep.maxpacket) + 1;

	pktcnt = 1;
	al_readl(&ctrl, (void __iomem *)&reg->out_endp[ep_num].doepctl);

	al_writel(req->req.dma + req->req.actual,
		(void __iomem *)&reg->out_endp[ep_num].doepdma);
	if (ep_type(ep) == ep_control) {
		al_writel((3<<29) |
			DOEPT_SIZ_PKT_CNT(pktcnt) | DOEPT_SIZ_XFER_SIZE(length),
			(void __iomem *)&reg->out_endp[ep_num].doeptsiz);
	} else {
		al_writel(
			DOEPT_SIZ_PKT_CNT(pktcnt) | DOEPT_SIZ_XFER_SIZE(length),
			(void __iomem *)&reg->out_endp[ep_num].doeptsiz);
	}
	al_writel(DEPCTL_EPENA|DEPCTL_CNAK|ctrl,
		(void __iomem *)&reg->out_endp[ep_num].doepctl);

	al_readl(&doepdma, (void __iomem *)&reg->out_endp[ep_num].doepdma);
	al_readl(&doeptsiz, (void __iomem *)&reg->out_endp[ep_num].doeptsiz);
	al_readl(&doepctl, (void __iomem *)&reg->out_endp[ep_num].doepctl);
	debug("%s: EP%d RX DMA start : DOEPDMA = 0x%x,"
		"DOEPTSIZ = 0x%x, DOEPCTL = 0x%x\n"
		"\tbuf = 0x%p, pktcnt = %d, xfersize = %d\n",
		__func__, ep_num,
		doepdma, doeptsiz, doepctl,
		buf, pktcnt, length);
	return 0;
}

static int setdma_tx(struct al_ep *ep, struct al_request *req)
{
	int retval;
	u32 *buf, ctrl = 0;
	u32 length, pktcnt;
	u32 ep_num = ep_index(ep);
	u32 diepdma, dieptsiz, diepctl;

	buf = req->req.buf + req->req.actual;
	length = req->req.length - req->req.actual;

	retval = usb_gadget_map_request(&ep->dev->gadget, &req->req, 1);  /* DMA TO DEVICE */
	if (retval)
		return retval;

	if (ep_num == EP0_CON)
		length = min(length, (u32)ep_maxpacket(ep));

	ep->len = length;
	ep->dma_buf = buf;

	if (length == 0)
		pktcnt = 1;
	else
		pktcnt = (length - 1)/(ep->ep.maxpacket) + 1;

	/* Flush the endpoint's Tx FIFO */
	al_writel(TX_FIFO_NUMBER(ep->fifo_num), (void __iomem *)&reg->grstctl);
	al_writel(TX_FIFO_NUMBER(ep->fifo_num) | TX_FIFO_FLUSH, (void __iomem *)&reg->grstctl);
	while (1) {
		al_readl(&ctrl, (void __iomem *)&reg->grstctl)
		if (!(ctrl & TX_FIFO_FLUSH))
			break;
	}

	al_writel(req->req.dma + req->req.actual,
		(void __iomem *)&reg->in_endp[ep_num].diepdma);
	if (ep_type(ep) == ep_isochronous) {
		al_writel((pktcnt<<29) | DIEPT_SIZ_PKT_CNT(pktcnt) | DIEPT_SIZ_XFER_SIZE(length),
			(void __iomem *)&reg->in_endp[ep_num].dieptsiz);
	} else {
		al_writel(DIEPT_SIZ_PKT_CNT(pktcnt) | DIEPT_SIZ_XFER_SIZE(length),
			(void __iomem *)&reg->in_endp[ep_num].dieptsiz);
	}

	al_readl(&ctrl, (void __iomem *)&reg->in_endp[ep_num].diepctl);

	/* Write the FIFO number to be used for this endpoint */
	ctrl &= DIEPCTL_TX_FIFO_NUM_MASK;
	ctrl |= DIEPCTL_TX_FIFO_NUM(ep->fifo_num);

	/* Clear reserved (Next EP) bits */
	ctrl = (ctrl&~(EP_MASK<<DEPCTL_NEXT_EP_BIT));

	al_writel(DEPCTL_EPENA|DEPCTL_CNAK|ctrl, (void __iomem *)&reg->in_endp[ep_num].diepctl);

	al_readl(&diepdma, (void __iomem *)&reg->in_endp[ep_num].diepdma);
	al_readl(&dieptsiz, (void __iomem *)&reg->in_endp[ep_num].dieptsiz);
	al_readl(&diepctl, (void __iomem *)&reg->in_endp[ep_num].diepctl);
	debug("%s:EP%d TX DMA start : DIEPDMA = 0x%x,"
		"DIEPTSIZ = 0x%x, DIEPCTL = 0x%x\n"
		"\tbuf = 0x%p, pktcnt = %d, xfersize = %d\n",
		__func__, ep_num,
		diepdma, dieptsiz, diepctl,
		buf, pktcnt, length);

	return length;
}

static void complete_rx(struct al_udc *dev, u8 ep_num)
{
	struct al_ep *ep = &dev->ep[ep_num];
	struct al_request *req = NULL;
	u32 ep_tsr = 0, xfer_size = 0, is_short = 0;

	if (list_empty(&ep->queue)) {
		debug("%s: RX DMA done : NULL REQ on OUT EP-%d\n",
			__func__, ep_num);
		return;
	}

	req = list_entry(ep->queue.next, struct al_request, queue);
	usb_gadget_unmap_request(&dev->gadget, &req->req, 0); /* DMA FROM DEVICE */
	al_readl(&ep_tsr, (void __iomem *)&reg->out_endp[ep_num].doeptsiz);

	if (ep_num == EP0_CON)
		xfer_size = (ep_tsr & DOEPT_SIZ_XFER_SIZE_MAX_EP0);
	else
		xfer_size = (ep_tsr & DOEPT_SIZ_XFER_SIZE_MAX_EP);

	xfer_size = ep->len - xfer_size;

	req->req.actual += min(xfer_size, req->req.length - req->req.actual);
	is_short = (xfer_size < ep->ep.maxpacket);

	debug("%s: RX DMA done : ep = %d, rx bytes = %d/%d, "
		"is_short = %d, DOEPTSIZ = 0x%x, remained bytes = %d\n",
		__func__, ep_num, req->req.actual, req->req.length,
		is_short, ep_tsr, xfer_size);

	if (is_short || req->req.actual == req->req.length) {
		if (ep_num == EP0_CON && dev->ep0state == DATA_STATE_RECV) {
			debug(" => Send ZLP\n");
			al_udc_ep0_zlp(dev);
			/* packet will be completed in complete_tx() */
			dev->ep0state = WAIT_FOR_IN_COMPLETE;
		} else {
			done(ep, req, 0);

			if (!list_empty(&ep->queue)) {
				req = list_entry(ep->queue.next,
					struct al_request, queue);
				debug("%s: Next Rx request start...\n", __func__);
				setdma_rx(ep, req);
			}
		}
	} else {
		setdma_rx(ep, req);
	}
}

static void complete_tx(struct al_udc *dev, u8 ep_num)
{
	struct al_ep *ep = &dev->ep[ep_num];
	struct al_request *req;
	u32 ep_tsr = 0, xfer_size = 0, is_short = 0;
	u32 last;

	if (dev->ep0state == WAIT_FOR_NULL_COMPLETE) {
		dev->ep0state = WAIT_FOR_OUT_COMPLETE;
		req = list_entry(ep->queue.next, struct al_request, queue);
		usb_gadget_unmap_request(&dev->gadget, &req->req, 1);  /* DMA TO DEVICE */
		al_ep0_complete_out();
		return;
	}

	if (list_empty(&ep->queue)) {
		debug("%s: TX DMA done : NULL REQ on IN EP-%d\n",
			__func__, ep_num);
		return;
	}

	req = list_entry(ep->queue.next, struct al_request, queue);
	usb_gadget_unmap_request(&dev->gadget, &req->req, 1);  /* DMA TO DEVICE */

	al_readl(&ep_tsr, (void __iomem *)&reg->in_endp[ep_num].dieptsiz);

	debug("%s: actual=%d length=%d eplen=%d\n",
		__func__, req->req.actual, req->req.length, ep->len);

	xfer_size = ep->len;
	is_short = (xfer_size < ep->ep.maxpacket);
	req->req.actual += min(xfer_size, req->req.length - req->req.actual);

	debug("%s: TX DMA done : ep = %d, tx bytes = %d/%d, "
		"is_short = %d, DIEPTSIZ = 0x%x, remained bytes = %d\n",
		__func__, ep_num, req->req.actual, req->req.length,
		is_short, ep_tsr, xfer_size);

	if (ep_num == 0) {
		if (dev->ep0state == DATA_STATE_XMIT) {
			debug("%s: ep_num = %d, ep0stat =="
				"DATA_STATE_XMIT\n",
				__func__, ep_num);
			last = write_fifo_ep0(ep, req);
			if (last)
				dev->ep0state = WAIT_FOR_COMPLETE;
		} else if (dev->ep0state == WAIT_FOR_IN_COMPLETE) {
			debug("%s: ep_num = %d, completing request\n",
				__func__, ep_num);
				done(ep, req, 0);
				dev->ep0state = WAIT_FOR_SETUP;
		} else if (dev->ep0state == WAIT_FOR_COMPLETE) {
			debug("%s: ep_num = %d, completing request\n",
				__func__, ep_num);
			done(ep, req, 0);
			dev->ep0state = WAIT_FOR_OUT_COMPLETE;
			al_ep0_complete_out();
		} else {
			debug("%s: ep_num = %d, invalid ep state\n",
				__func__, ep_num);
		}
		return;
	}

	if (req->req.actual == req->req.length)
		done(ep, req, 0);

	if (!list_empty(&ep->queue)) {
		req = list_entry(ep->queue.next, struct al_request, queue);
		debug("%s: Next Tx request start... req=0x%x\n", __func__, (u32)req);
		setdma_tx(ep, req);
	}
}

static inline void al_udc_check_tx_queue(struct al_udc *dev, u8 ep_num)
{
	struct al_ep *ep = &dev->ep[ep_num];
	struct al_request *req;

	debug("%s: Check queue, ep_num = %d\n", __func__, ep_num);

	if (!list_empty(&ep->queue)) {
		req = list_entry(ep->queue.next, struct al_request, queue);
		debug("%s: Next Tx request(0x%p) start...\n",
			__func__, req);

		if (ep_is_in(ep))
			setdma_tx(ep, req);
		else
			setdma_rx(ep, req);
	} else {
		debug("%s: NULL REQ on IN EP-%d\n", __func__, ep_num);
		return;
	}
}

static void process_ep_in_intr(struct al_udc *dev)
{
	u32 ep_intr, ep_intr_status;
	u8 ep_num = 0;

	al_readl(&ep_intr, (void __iomem *)&reg->daint);
	debug("*** %s: EP In interrupt : DAINT = 0x%x\n", __func__, ep_intr);

	ep_intr &= DAINT_MASK;

	while (ep_intr) {
		if (ep_intr & DAINT_IN_EP_INT(1)) {
			al_readl(&ep_intr_status,
				(void __iomem *)&reg->in_endp[ep_num].diepint);
			debug("\tEP%d-IN : DIEPINT = 0x%x\n",
				ep_num, ep_intr_status);

			/* Interrupt Clear */
			al_writel(ep_intr_status,
				(void __iomem *)&reg->in_endp[ep_num].diepint);
			if (ep_intr_status & TRANSFER_DONE) {
				complete_tx(dev, ep_num);

				if (ep_num == 0) {
					if (dev->ep0state == WAIT_FOR_IN_COMPLETE) {
						dev->ep0state = WAIT_FOR_SETUP;
						debug("\tstate WAIT_FOR_IN_COMPLETE --> %s\n",
							state_names[dev->ep0state]);
					}

					if (dev->ep0state == WAIT_FOR_SETUP)
						al_udc_pre_setup();

					/* continue transfer after
					   set_clear_halt for DMA mode */
					if (clear_feature_flag == 1) {
						al_udc_check_tx_queue(dev,
							clear_feature_num);
						clear_feature_flag = 0;
					}
				}
			}
		}
		ep_num++;
		ep_intr >>= 1;
	}
}

static void process_ep_out_intr(struct al_udc *dev)
{
	u32 ep_intr, ep_intr_status;
	u8 ep_num = 0;

	al_readl(&ep_intr, (void __iomem *)&reg->daint);
	debug("*** %s: EP OUT interrupt : DAINT = 0x%x\n",
		__func__, ep_intr);

	ep_intr = (ep_intr >> DAINT_OUT_BIT) & DAINT_MASK;

	while (ep_intr) {
		if (ep_intr & 0x1) {
			al_readl(&ep_intr_status,
				(void __iomem *)&reg->out_endp[ep_num].doepint);
			debug("\tEP%d-OUT : DOEPINT = 0x%x\n",
				ep_num, ep_intr_status);

			/* Interrupt Clear */
			al_writel(ep_intr_status,
				(void __iomem *)&reg->out_endp[ep_num].doepint);
			if (ep_num == 0) {
				if (ep_intr_status & TRANSFER_DONE) {
					if (dev->ep0state !=
					    WAIT_FOR_OUT_COMPLETE) {
						complete_rx(dev, ep_num);
					} else {
						dev->ep0state = WAIT_FOR_SETUP;
						debug("\tstate WAIT_FOR_OUT_COMPLETE --> %s\n",
							state_names[dev->ep0state]);
						al_udc_pre_setup();
					}
				}

				if (ep_intr_status &
				    CTRL_OUT_EP_SETUP_PHASE_DONE) {
					debug("SETUP packet arrived\n");
					al_handle_ep0(dev);
				}
			} else {
				if (ep_intr_status & TRANSFER_DONE)
					complete_rx(dev, ep_num);
			}
		}
		ep_num++;
		ep_intr >>= 1;
	}
}

/*
 *      usb client interrupt handler.
 */
static irqreturn_t al_udc_irq(struct al_udc *dev, u32 intr_status, u32 gintmsk)
{
	u32 usb_status;
	u32 daint, daintmsk;
	unsigned long flags;

	spin_lock_irqsave(&dev->lock, flags);

	al_readl(&daint, (void __iomem *)&reg->daint);
	al_readl(&daintmsk, (void __iomem *)&reg->daintmsk)
	debug("\n*** %s : GINTSTS=0x%x(on state %s), GINTMSK : 0x%x, "
		"DAINT : 0x%x, DAINTMSK : 0x%x\n",
		__func__, intr_status, state_names[dev->ep0state], gintmsk,
		daint, daintmsk);

	if (!intr_status) {
		spin_unlock_irqrestore(&dev->lock, flags);
		return IRQ_RETVAL(IRQ_HANDLED);
	}

	if (intr_status & INT_ENUMDONE) {
		debug("\tSpeed Detection interrupt\n");

		al_writel(INT_ENUMDONE, (void __iomem *)&reg->gintsts);
		al_readl(&usb_status, (void __iomem *)&reg->dsts);
		usb_status = (usb_status & 0x6);

		if (usb_status & (USB_FULL_30_60MHZ | USB_FULL_48MHZ)) {
			debug("\t\tFull Speed Detection\n");
			set_max_pktsize(dev, USB_SPEED_FULL);
		} else {
			debug("\t\tHigh Speed Detection : 0x%x\n", usb_status);
			set_max_pktsize(dev, USB_SPEED_HIGH);
		}
	}

	if (intr_status & INT_EARLY_SUSPEND) {
		debug("\tEarly suspend interrupt\n");
		al_writel(INT_EARLY_SUSPEND, (void __iomem *)&reg->gintsts);
	}

	if (intr_status & INT_SUSPEND) {
		al_readl(&usb_status, (void __iomem *)&reg->dsts);
		debug("\tSuspend interrupt :(DSTS):0x%x\n", usb_status);
		al_writel(INT_SUSPEND, (void __iomem *)&reg->gintsts);

		if (dev->gadget.speed != USB_SPEED_UNKNOWN
		    && dev->driver) {
			if (dev->driver->suspend)
				dev->driver->suspend(&dev->gadget);

			/* HACK to let gadget detect disconnected state */
			if (dev->driver->disconnect) {
				spin_unlock_irqrestore(&dev->lock, flags);
				dev->driver->disconnect(&dev->gadget);
				spin_lock_irqsave(&dev->lock, flags);
			}
		}
	}
	if (intr_status & INT_RESUME) {
		debug("\tResume interrupt\n");
		al_writel(INT_RESUME, (void __iomem *)&reg->gintsts);

		if (dev->gadget.speed != USB_SPEED_UNKNOWN
		    && dev->driver
		    && dev->driver->resume) {
			dev->driver->resume(&dev->gadget);
		}
	}
	if (intr_status & INT_RESET) {
		al_readl(&usb_status, (void __iomem *)&reg->gotgctl);
		debug("\tReset interrupt - (GOTGCTL):0x%x\n", usb_status);
		al_writel(INT_RESET, (void __iomem *)&reg->gintsts);

		if ((usb_status & 0xc0000) == (0x3 << 18)) {
			if (reset_available) {
				debug("\t\tOTG core got reset (%d)!!\n",
					reset_available);
				reconfig_usbd();
				dev->ep0state = WAIT_FOR_SETUP;
				reset_available = 0;
				al_udc_pre_setup();
			} else {
				reset_available = 1;
			}
		} else {
			reset_available = 1;
			debug("\t\tRESET handling skipped\n");
		}
		if (intr_status & (INT_IN_EP | INT_OUT_EP))
			debug("\t\tRESET & EP interrupt\n");
	}
	if (intr_status & INT_IN_EP)
		process_ep_in_intr(dev);

	if (intr_status & INT_OUT_EP)
		process_ep_out_intr(dev);

	spin_unlock_irqrestore(&dev->lock, flags);

	return IRQ_RETVAL(IRQ_HANDLED);
}

/** Queue one request
 *  Kickstart transfer if needed
 */
static int al_queue(struct usb_ep *_ep, struct usb_request *_req,
		gfp_t gfp_flags)
{
	struct al_request *req;
	struct al_ep *ep;
	struct al_udc *dev;
	unsigned long flags;
	u32 ep_num, gintsts;

	req = container_of(_req, struct al_request, req);
	if (unlikely(!_req || !_req->complete || !_req->buf
		     || !list_empty(&req->queue))) {
		debug("%s: bad params\n", __func__);
		return -EINVAL;
	}

	ep = container_of(_ep, struct al_ep, ep);

	if (unlikely(!_ep || (!ep->desc && ep->ep.name != ep0name))) {
		debug("%s: bad ep: %s, %d, %p\n", __func__,
			ep->ep.name, !ep->desc, _ep);
		return -EINVAL;
	}

	ep_num = ep_index(ep);
	dev = ep->dev;
	if (unlikely(!dev->driver || dev->gadget.speed == USB_SPEED_UNKNOWN)) {
		debug("%s: bogus device state %p\n", __func__, dev->driver);
		return -ESHUTDOWN;
	}

	spin_lock_irqsave(&dev->lock, flags);

	_req->status = -EINPROGRESS;
	_req->actual = 0;

	/* kickstart this i/o queue? */
	debug("\n*** %s: %s-%s req = %p, len = %d, buf = %p"
		"Q empty = %d, stopped = %d\n",
		__func__, _ep->name, ep_is_in(ep) ? "in" : "out",
		_req, _req->length, _req->buf,
		list_empty(&ep->queue), ep->stopped);

	if (list_empty(&ep->queue) && !ep->stopped) {
		if (ep_num == 0) {
			/* EP0 */
			list_add_tail(&req->queue, &ep->queue);
			al_ep0_kick(dev, ep);
			req = NULL;
		} else if (ep_is_in(ep)) {
			gintsts = readl((void __iomem *)&reg->gintsts);
			debug("%s: ep_is_in, UDC_OTG_GINTSTS=0x%x\n",
				__func__, gintsts);
			setdma_tx(ep, req);
		} else {
			al_readl(&gintsts, (void __iomem *)&reg->gintsts);
			debug("%s:ep_is_out, UDC_OTG_GINTSTS=0x%x\n",
				__func__, gintsts);
			setdma_rx(ep, req);
		}
	}

	/* pio or dma irq handler advances the queue. */
	if (likely(req != NULL))
		list_add_tail(&req->queue, &ep->queue);

	spin_unlock_irqrestore(&dev->lock, flags);

	return 0;
}

/****************************************************************/
/* End Point 0 related functions                                */
/****************************************************************/

/* return:  0 = still running, 1 = completed, negative = errno */
static int write_fifo_ep0(struct al_ep *ep, struct al_request *req)
{
	u32 max;
	unsigned count;
	int is_last;

	max = ep_maxpacket(ep);

	debug("%s: max = %d\n", __func__, max);

	count = setdma_tx(ep, req);

	/* last packet is usually short (or a zlp) */
	if (likely(count != max)) {
		is_last = 1;
	} else {
		if (likely(req->req.length != req->req.actual + count)
			   || req->req.zero)
			is_last = 0;
		else
			is_last = 1;
	}

	debug("%s: wrote %s %d bytes%s %d left %p\n", __func__,
		ep->ep.name, count,
		is_last ? "/L" : "",
		req->req.length - req->req.actual - count, req);

	/* requests complete when all IN data is in the FIFO */
	if (is_last) {
		ep->dev->ep0state = WAIT_FOR_SETUP;
		return 1;
	}

	return 0;
}

#if 0
static int al_fifo_read(struct al_ep *ep, u32 *cp, int max)
{
	u32 bytes;

	bytes = sizeof(struct usb_ctrlrequest);

	debug("%s: bytes=%d, ep_index=%d %p\n", __func__,
		bytes, ep_index(ep), ep->dev->dma_buf[ep_index(ep)]);

	return bytes;
}
#endif

/**
 * udc_set_address - set the USB address for this device
 * @address:
 *
 * Called from control endpoint function
 * after it decodes a set address setup packet.
 */
static void udc_set_address(struct al_udc *dev, unsigned char address)
{
	u32 ctrl;
	u32 dcfg;

	al_readl(&ctrl, (void __iomem *)&reg->dcfg);
	al_writel(DEVICE_ADDRESS(address) | ctrl, (void __iomem *)&reg->dcfg);

	al_udc_ep0_zlp(dev);

	al_readl(&dcfg, (void __iomem *)&reg->dcfg);
	debug("%s: USB OTG 2.0 Device address=%d, DCFG=0x%x\n",
		__func__, address, dcfg);

	dev->usb_address = address;
}

static inline void al_udc_ep0_set_stall(struct al_ep *ep)
{
	struct al_udc *dev;
	u32 ep_ctrl = 0;

	dev = ep->dev;
	al_readl(&ep_ctrl, (void __iomem *)&reg->in_endp[EP0_CON].diepctl);

	/* set the disable and stall bits */
	if (ep_ctrl & DEPCTL_EPENA)
		ep_ctrl |= DEPCTL_EPDIS;

	ep_ctrl |= DEPCTL_STALL;

	al_writel(ep_ctrl, (void __iomem *)&reg->in_endp[EP0_CON].diepctl);

	debug("%s: set ep%d stall, DIEPCTL0 = 0x%p\n",
		__func__, ep_index(ep), &reg->in_endp[EP0_CON].diepctl);
	/*
	 * The application can only set this bit, and the core clears it,
	 * when a SETUP token is received for this endpoint
	 */
	dev->ep0state = WAIT_FOR_SETUP;

	al_udc_pre_setup();
}

static void al_ep0_read(struct al_udc *dev)
{
	struct al_request *req;
	struct al_ep *ep = &dev->ep[0];

	if (!list_empty(&ep->queue)) {
		req = list_entry(ep->queue.next, struct al_request, queue);
	} else {
		debug("%s: NULL REQ\n", __func__);
		return;
	}

	debug("%s: req = %p, req.length = 0x%x, req.actual = 0x%x\n",
		__func__, req, req->req.length, req->req.actual);

	if (req->req.length == 0) {
		/* zlp for Set_configuration, Set_interface,
		 * or Bulk-Only mass storage reset */

		ep->len = 0;
		al_udc_ep0_zlp(dev);

		debug("%s: req.length = 0, bRequest = %d\n",
			__func__, usb_ctrl->bRequest);
		return;
	}

	setdma_rx(ep, req);
}

/*
 * DATA_STATE_XMIT
 */
static int al_ep0_write(struct al_udc *dev)
{
	struct al_request *req;
	struct al_ep *ep = &dev->ep[0];
	int ret, need_zlp = 0;

	if (list_empty(&ep->queue))
		req = NULL;
	else
		req = list_entry(ep->queue.next, struct al_request, queue);

	if (!req) {
		debug("%s: NULL REQ\n", __func__);
		return 0;
	}

	debug("%s: req = %p, req.length = 0x%x, req.actual = 0x%x\n",
		__func__, req, req->req.length, req->req.actual);

	if (req->req.length - req->req.actual == ep0_fifo_size) {
		/* Next write will end with the packet size, */
		/* so we need Zero-length-packet */
		need_zlp = 1;
	}

	ret = write_fifo_ep0(ep, req);

	if ((ret == 1) && !need_zlp) {
		/* Last packet */
		dev->ep0state = WAIT_FOR_COMPLETE;
		debug("%s: finished, waiting for status\n", __func__);
	} else {
		dev->ep0state = DATA_STATE_XMIT;
		debug("%s: not finished\n", __func__);
	}

	return 1;
}

static int al_udc_get_status(struct al_udc *dev, struct usb_ctrlrequest *crq)
{
	u8 ep_num = crq->wIndex & 0x7F;
	u32 ep_ctrl;
	u32 *p = the_controller->dma_buf[1];
	u16 g_status;

	debug("%s: *** USB_REQ_GET_STATUS\n", __func__);
	debug("crq->brequest:0x%x\n", crq->bRequestType & USB_RECIP_MASK);
	switch (crq->bRequestType & USB_RECIP_MASK) {
	case USB_RECIP_INTERFACE:
		g_status = 0;
		debug("\tGET_STATUS:USB_RECIP_INTERFACE, g_status = %d\n",
			g_status);
		break;

	case USB_RECIP_DEVICE:
		g_status = 0x1; /* Self powered */
		debug("\tGET_STATUS: USB_RECIP_DEVICE, g_status = %d\n",
			g_status);
		break;

	case USB_RECIP_ENDPOINT:
		if (crq->wLength > 2) {
			debug("\tGET_STATUS:Not support EP or wLength\n");
			return 1;
		}

		g_status = dev->ep[ep_num].stopped;
		debug("\tGET_STATUS: USB_RECIP_ENDPOINT, g_status = %d\n",
			g_status);

		break;

	default:
		return 1;
	}

	memcpy(p, &g_status, sizeof(g_status));

	al_writel(the_controller->dma_addr[1], (void __iomem *)&reg->in_endp[EP0_CON].diepdma);
	al_writel(DIEPT_SIZ_PKT_CNT(1) | DIEPT_SIZ_XFER_SIZE(2),
		(void __iomem *)&reg->in_endp[EP0_CON].dieptsiz);

	al_readl(&ep_ctrl, (void __iomem *)&reg->in_endp[EP0_CON].diepctl);
	al_writel(ep_ctrl|DEPCTL_EPENA|DEPCTL_CNAK,
		(void __iomem *)&reg->in_endp[EP0_CON].diepctl);
	dev->ep0state = WAIT_FOR_NULL_COMPLETE;

	return 0;
}

static void al_udc_set_nak(struct al_ep *ep)
{
	u8 ep_num;
	u32 ep_ctrl = 0;

	ep_num = ep_index(ep);
	debug("%s: ep_num = %d, ep_type = %d\n", __func__, ep_num, ep->ep_type);

	if (ep_is_in(ep)) {
		al_readl(&ep_ctrl, (void __iomem *)&reg->in_endp[ep_num].diepctl);
		ep_ctrl |= DEPCTL_SNAK;
		al_writel(ep_ctrl, (void __iomem *)&reg->in_endp[ep_num].diepctl);
		al_readl(&ep_ctrl, (void __iomem *)&reg->in_endp[ep_num].diepctl)
		debug("%s: set NAK, DIEPCTL%d = 0x%x\n",
			__func__, ep_num, ep_ctrl);
	} else {
		al_readl(&ep_ctrl, (void __iomem *)&reg->out_endp[ep_num].doepctl);
		ep_ctrl |= DEPCTL_SNAK;
		al_writel(ep_ctrl, (void __iomem *)&reg->out_endp[ep_num].doepctl);
		al_readl(&ep_ctrl, (void __iomem *)&reg->out_endp[ep_num].doepctl)
		debug("%s: set NAK, DOEPCTL%d = 0x%x\n",
			__func__, ep_num, ep_ctrl);
	}

	return;
}

static void al_udc_ep_set_stall(struct al_ep *ep)
{
	u8 ep_num;
	u32 ep_ctrl = 0;

	ep_num = ep_index(ep);
	debug("%s: ep_num = %d, ep_type = %d\n", __func__, ep_num, ep->ep_type);

	if (ep_is_in(ep)) {
		al_readl(&ep_ctrl, (void __iomem *)&reg->in_endp[ep_num].diepctl);

		/* set the disable and stall bits */
		if (ep_ctrl & DEPCTL_EPENA)
			ep_ctrl |= DEPCTL_EPDIS;

		ep_ctrl |= DEPCTL_STALL;

		al_writel(ep_ctrl, (void __iomem *)&reg->in_endp[ep_num].diepctl);
		al_readl(&ep_ctrl, (void __iomem *)&reg->in_endp[ep_num].diepctl);
		debug("%s: set stall, DIEPCTL%d = 0x%x\n",
			__func__, ep_num, ep_ctrl);

	} else {
		al_readl(&ep_ctrl, (void __iomem *)&reg->out_endp[ep_num].doepctl);

		/* set the stall bit */
		ep_ctrl |= DEPCTL_STALL;

		al_writel(ep_ctrl, (void __iomem *)&reg->out_endp[ep_num].doepctl);
		al_readl(&ep_ctrl, (void __iomem *)&reg->out_endp[ep_num].doepctl);
		debug("%s: set stall, DOEPCTL%d = 0x%x\n",
			__func__, ep_num, ep_ctrl);
	}

	return;
}

static void al_udc_ep_clear_stall(struct al_ep *ep)
{
	u8 ep_num;
	u32 ep_ctrl = 0;

	ep_num = ep_index(ep);
	debug("%s: ep_num = %d, ep_type = %d\n", __func__, ep_num, ep->ep_type);

	if (ep_is_in(ep)) {
		al_readl(&ep_ctrl, (void __iomem *)&reg->in_endp[ep_num].diepctl);

		/* clear stall bit */
		ep_ctrl &= ~DEPCTL_STALL;

		/*
		 * USB Spec 9.4.5: For endpoints using data toggle, regardless
		 * of whether an endpoint has the Halt feature set, a
		 * ClearFeature(ENDPOINT_HALT) request always results in the
		 * data toggle being reinitialized to DATA0.
		 */
		if (ep->bmAttributes == USB_ENDPOINT_XFER_INT
		    || ep->bmAttributes == USB_ENDPOINT_XFER_BULK) {
			ep_ctrl |= DEPCTL_SETD0PID; /* DATA0 */
		}

		al_writel(ep_ctrl, (void __iomem *)&reg->in_endp[ep_num].diepctl);
		al_readl(&ep_ctrl, (void __iomem *)&reg->in_endp[ep_num].diepctl);
		debug("%s: cleared stall, DIEPCTL%d = 0x%x\n",
			__func__, ep_num, ep_ctrl);

	} else {
		al_readl(&ep_ctrl, (void __iomem *)&reg->out_endp[ep_num].doepctl);

		/* clear stall bit */
		ep_ctrl &= ~DEPCTL_STALL;

		if (ep->bmAttributes == USB_ENDPOINT_XFER_INT
		    || ep->bmAttributes == USB_ENDPOINT_XFER_BULK) {
			ep_ctrl |= DEPCTL_SETD0PID; /* DATA0 */
		}

		al_writel(ep_ctrl, (void __iomem *)&reg->out_endp[ep_num].doepctl);
		al_readl(&ep_ctrl, (void __iomem *)&reg->out_endp[ep_num].doepctl);
		debug("%s: cleared stall, DOEPCTL%d = 0x%x\n",
			__func__, ep_num, ep_ctrl);
	}
	return;
}

static int al_udc_set_halt(struct usb_ep *_ep, int value)
{
	struct al_ep *ep;
	struct al_udc *dev;
	unsigned long flags;
	u8 ep_num;

	ep = container_of(_ep, struct al_ep, ep);
	ep_num = ep_index(ep);

	if (unlikely(!_ep || !ep->desc || ep_num == EP0_CON ||
		     ep->desc->bmAttributes == USB_ENDPOINT_XFER_ISOC)) {
		debug("%s: %s bad ep or descriptor\n", __func__, ep->ep.name);
		return -EINVAL;
	}

	/* Attempt to halt IN ep will fail if any transfer requests
	 * are still queue */
	if (value && ep_is_in(ep) && !list_empty(&ep->queue)) {
		debug("%s: %s queue not empty, req = %p\n",
			__func__, ep->ep.name,
			list_entry(ep->queue.next, struct al_request, queue));

		return -EAGAIN;
	}

	dev = ep->dev;
	debug("%s: ep_num = %d, value = %d\n", __func__, ep_num, value);

	spin_lock_irqsave(&dev->lock, flags);

	if (value == 0) {
		ep->stopped = 0;
		al_udc_ep_clear_stall(ep);
	} else {
		if (ep_num == 0)
			dev->ep0state = WAIT_FOR_SETUP;

		ep->stopped = 1;
		al_udc_ep_set_stall(ep);
	}

	spin_unlock_irqrestore(&dev->lock, flags);

	return 0;
}

static void al_udc_ep_activate(struct al_ep *ep)
{
	u8 ep_num;
	u32 ep_ctrl = 0, daintmsk = 0;
	u32 msk;

	ep_num = ep_index(ep);

	/* Read DEPCTLn register */
	if (ep_is_in(ep)) {
		al_readl(&ep_ctrl, (void __iomem *)&reg->in_endp[ep_num].diepctl);
		daintmsk = 1 << ep_num;
	} else {
		al_readl(&ep_ctrl, (void __iomem *)&reg->out_endp[ep_num].doepctl);
		daintmsk = (1 << ep_num) << DAINT_OUT_BIT;
	}

	debug("%s: EPCTRL%d = 0x%x, ep_is_in = %d\n",
		__func__, ep_num, ep_ctrl, ep_is_in(ep));

	/* If the EP is already active don't change the EP Control
	 * register. */
	if (!(ep_ctrl & DEPCTL_USBACTEP)) {
		ep_ctrl = (ep_ctrl & ~DEPCTL_TYPE_MASK) |
			(ep->bmAttributes << DEPCTL_TYPE_BIT);
		ep_ctrl = (ep_ctrl & ~DEPCTL_MPS_MASK) |
			(ep->ep.maxpacket << DEPCTL_MPS_BIT);
		ep_ctrl |= (DEPCTL_SETD0PID | DEPCTL_USBACTEP | DEPCTL_SNAK);

		if (ep_is_in(ep)) {
			al_writel(ep_ctrl, (void __iomem *)&reg->in_endp[ep_num].diepctl);
			al_readl(&ep_ctrl, (void __iomem *)&reg->in_endp[ep_num].diepctl);
			debug("%s: USB Active EP%d, DIEPCTRL%d = 0x%x\n",
				__func__, ep_num, ep_num, ep_ctrl);
		} else {
			al_writel(ep_ctrl, (void __iomem *)&reg->out_endp[ep_num].doepctl);
			al_readl(&ep_ctrl, (void __iomem *)&reg->out_endp[ep_num].doepctl);
			debug("%s: USB Active EP%d, DOEPCTRL%d = 0x%x\n",
				__func__, ep_num, ep_num, ep_ctrl);
		}
	}

	/* Unmask EP Interrupt */
	al_readl(&msk, (void __iomem *)&reg->daintmsk);
	al_writel(msk|daintmsk, (void __iomem *)&reg->daintmsk);
	al_readl(&daintmsk, (void __iomem *)&reg->daintmsk);
	debug("%s: DAINTMSK = 0x%x\n", __func__, daintmsk);
}

static int al_udc_clear_feature(struct usb_ep *_ep)
{
	struct al_udc *dev;
	struct al_ep *ep;
	u8 ep_num;

	ep = container_of(_ep, struct al_ep, ep);
	ep_num = ep_index(ep);

	dev = ep->dev;
	debug("%s: ep_num = %d, is_in = %d, clear_feature_flag = %d\n",
		__func__, ep_num, ep_is_in(ep), clear_feature_flag);

	if (usb_ctrl->wLength != 0) {
		debug("\tCLEAR_FEATURE: wLength is not zero.....\n");
		return 1;
	}

	switch (usb_ctrl->bRequestType & USB_RECIP_MASK) {
	case USB_RECIP_DEVICE:
		switch (usb_ctrl->wValue) {
		case USB_DEVICE_REMOTE_WAKEUP:
			debug("\tOFF:USB_DEVICE_REMOTE_WAKEUP\n");
			break;

		case USB_DEVICE_TEST_MODE:
			debug("\tCLEAR_FEATURE: USB_DEVICE_TEST_MODE\n");
			/** @todo Add CLEAR_FEATURE for TEST modes. */
			break;
		}

		al_udc_ep0_zlp(dev);
		break;

	case USB_RECIP_ENDPOINT:
		debug("\tCLEAR_FEATURE:USB_RECIP_ENDPOINT, wValue = %d\n",
			usb_ctrl->wValue);

		if (usb_ctrl->wValue == USB_ENDPOINT_HALT) {
			if (ep_num == 0) {
				al_udc_ep0_set_stall(ep);
				return 0;
			}

			al_udc_ep0_zlp(dev);

			al_udc_ep_clear_stall(ep);
			al_udc_ep_activate(ep);
			ep->stopped = 0;

			clear_feature_num = ep_num;
			clear_feature_flag = 1;
		}
		break;
	}

	return 0;
}

static int al_udc_set_feature(struct usb_ep *_ep)
{
	struct al_udc *dev;
	struct al_ep *ep;
	u8 ep_num;

	ep = container_of(_ep, struct al_ep, ep);
	ep_num = ep_index(ep);
	dev = ep->dev;

	debug("%s: *** USB_REQ_SET_FEATURE , ep_num = %d\n",
		__func__, ep_num);

	if (usb_ctrl->wLength != 0) {
		debug("\tSET_FEATURE: wLength is not zero.....\n");
		return 1;
	}

	switch (usb_ctrl->bRequestType & USB_RECIP_MASK) {
	case USB_RECIP_DEVICE:
		switch (usb_ctrl->wValue) {
		case USB_DEVICE_REMOTE_WAKEUP:
			debug("\tSET_FEATURE:USB_DEVICE_REMOTE_WAKEUP\n");
			break;
		case USB_DEVICE_B_HNP_ENABLE:
			debug("\tSET_FEATURE: USB_DEVICE_B_HNP_ENABLE\n");
			break;

		case USB_DEVICE_A_HNP_SUPPORT:
			/* RH port supports HNP */
			debug("\tSET_FEATURE:USB_DEVICE_A_HNP_SUPPORT\n");
			break;

		case USB_DEVICE_A_ALT_HNP_SUPPORT:
			/* other RH port does */
			debug("\tSET: USB_DEVICE_A_ALT_HNP_SUPPORT\n");
			break;
		}

		al_udc_ep0_zlp(dev);
		return 0;

	case USB_RECIP_INTERFACE:
		debug("\tSET_FEATURE: USB_RECIP_INTERFACE\n");
		break;

	case USB_RECIP_ENDPOINT:
		debug("\tSET_FEATURE: USB_RECIP_ENDPOINT\n");
		if (usb_ctrl->wValue == USB_ENDPOINT_HALT) {
			if (ep_num == 0) {
				al_udc_ep0_set_stall(ep);
				return 0;
			}
			ep->stopped = 1;
			al_udc_ep_set_stall(ep);
		}

		al_udc_ep0_zlp(dev);
		return 0;
	}

	return 1;
}

/*
 * WAIT_FOR_SETUP (OUT_PKT_RDY)
 */
static void al_ep0_setup(struct al_udc *dev)
{
	struct al_ep *ep = &dev->ep[0];
	int i;
	u8 ep_num;

	/* Nuke all previous transfers */
	nuke(ep, -EPROTO);

	/* read control req from fifo (8 bytes) */
/*	al_fifo_read(ep, (u32 *)usb_ctrl, 8);*/

	debug("%s: bRequestType = 0x%x(%s), bRequest = 0x%x"
		"\twLength = 0x%x, wValue = 0x%x, wIndex= 0x%x\n",
		__func__, usb_ctrl->bRequestType,
		(usb_ctrl->bRequestType & USB_DIR_IN) ? "IN" : "OUT",
		usb_ctrl->bRequest,
		usb_ctrl->wLength, usb_ctrl->wValue, usb_ctrl->wIndex);

	if (usb_ctrl->bRequest == GET_MAX_LUN_REQUEST &&
	    usb_ctrl->wLength != 1) {
		debug("\t%s:GET_MAX_LUN_REQUEST:invalid", __func__);
		debug("wLength = %d, setup returned\n", usb_ctrl->wLength);

		al_udc_ep0_set_stall(ep);
		dev->ep0state = WAIT_FOR_SETUP;

		return;
	} else if (usb_ctrl->bRequest == BOT_RESET_REQUEST &&
		   usb_ctrl->wLength != 0) {
		/* Bulk-Only mass storage reset of class-specific request */
		debug("%s:BOT Rest:invalid wLength =%d, setup returned\n",
			__func__, usb_ctrl->wLength);

		al_udc_ep0_set_stall(ep);
		dev->ep0state = WAIT_FOR_SETUP;

		return;
	}

	/* Set direction of EP0 */
	if (likely(usb_ctrl->bRequestType & USB_DIR_IN))
		ep->bEndpointAddress |= USB_DIR_IN;
	else
		ep->bEndpointAddress &= ~USB_DIR_IN;
	/* cope with automatic for some standard requests. */
	dev->req_std = (usb_ctrl->bRequestType & USB_TYPE_MASK)
		== USB_TYPE_STANDARD;

	dev->req_pending = 1;

	/* Handle some SETUP packets ourselves */
	if (dev->req_std) {
		switch (usb_ctrl->bRequest) {
		case USB_REQ_SET_ADDRESS:
			debug("%s: *** USB_REQ_SET_ADDRESS (%d)\n",
				__func__, usb_ctrl->wValue);
			if (usb_ctrl->bRequestType
			    != (USB_TYPE_STANDARD | USB_RECIP_DEVICE))
				break;

			udc_set_address(dev, usb_ctrl->wValue);
			return;

		case USB_REQ_SET_CONFIGURATION:
			debug("=====================================\n");
			debug("%s: USB_REQ_SET_CONFIGURATION (%d)\n",
				__func__, usb_ctrl->wValue);

			if (usb_ctrl->bRequestType == USB_RECIP_DEVICE)
				reset_available = 1;

			break;

		case USB_REQ_GET_DESCRIPTOR:
			debug("%s: *** USB_REQ_GET_DESCRIPTOR\n", __func__);
			break;

		case USB_REQ_SET_INTERFACE:
			debug("%s: *** USB_REQ_SET_INTERFACE (%d)\n",
				__func__, usb_ctrl->wValue);

			if (usb_ctrl->bRequestType == USB_RECIP_INTERFACE)
				reset_available = 1;

			break;

		case USB_REQ_GET_CONFIGURATION:
			debug("%s: *** USB_REQ_GET_CONFIGURATION\n", __func__);
			break;

		case USB_REQ_GET_STATUS:
			if (!al_udc_get_status(dev, usb_ctrl))
				return;

			break;

		case USB_REQ_CLEAR_FEATURE:
			ep_num = usb_ctrl->wIndex & 0x7f;

			if (!al_udc_clear_feature(&dev->ep[ep_num].ep))
				return;

			break;

		case USB_REQ_SET_FEATURE:
			ep_num = usb_ctrl->wIndex & 0x7f;

			if (!al_udc_set_feature(&dev->ep[ep_num].ep))
				return;

			break;

		default:
			debug("%s: *** Default of usb_ctrl->bRequest=0x%x "
				"happened.\n", __func__, usb_ctrl->bRequest);
			break;
		}
	}

	if (likely(dev->driver)) {
		/* device-2-host (IN) or no data setup command,
		 * process immediately */
		debug("%s:usb_ctrlreq will be passed to fsg_setup()\n",
			__func__);

		spin_unlock(&dev->lock);
		i = dev->driver->setup(&dev->gadget, usb_ctrl);
		spin_lock(&dev->lock);

		if (i < 0) {
			/* setup processing failed, force stall */
			al_udc_ep0_set_stall(ep);
			dev->ep0state = WAIT_FOR_SETUP;

			debug("\tdev->driver->setup failed (%d),"
				" bRequest = %d\n", i, usb_ctrl->bRequest);


		} else if (dev->req_pending) {
			dev->req_pending = 0;
			debug("\tdev->req_pending...\n");
		}
		debug("\tep0state = %s\n", state_names[dev->ep0state]);

	}
}

/*
 * handle ep0 interrupt
 */
static void al_handle_ep0(struct al_udc *dev)
{
	if (dev->ep0state == WAIT_FOR_SETUP) {
		debug("%s: WAIT_FOR_SETUP\n", __func__);
		al_ep0_setup(dev);

	} else {
		debug("%s: strange state!!(state = %s)\n",
			__func__, state_names[dev->ep0state]);
	}
}

static void al_ep0_kick(struct al_udc *dev, struct al_ep *ep)
{
	debug("%s: ep_is_in = %d\n", __func__, ep_is_in(ep));
	if (ep_is_in(ep)) {
		dev->ep0state = DATA_STATE_XMIT;
		al_ep0_write(dev);

	} else {
		dev->ep0state = DATA_STATE_RECV;
		al_ep0_read(dev);
	}
}


/* ---------------------------------------------------------------------------
 *	device-scoped parts of the OTG
 * ---------------------------------------------------------------------------*/

static struct usb_ep_ops al_ep_ops = {
	.enable = al_ep_enable,
	.disable = al_ep_disable,

	.alloc_request = al_alloc_request,
	.free_request = al_free_request,

	.queue = al_queue,
	.dequeue = al_dequeue,

	.set_halt = al_udc_set_halt,
	.fifo_status = al_fifo_status,
	.fifo_flush = al_fifo_flush,
};

/*
 * udc_disable - disable USB device controller
 */
static void udc_disable(struct al_udc *dev)
{
	udc_set_address(dev, 0);

	dev->ep0state = WAIT_FOR_SETUP;
	dev->gadget.speed = USB_SPEED_UNKNOWN;
	dev->usb_address = 0;

	debug("%s: speed=%d address=%d ep0state=%s\n",
		__func__, dev->gadget.speed, dev->usb_address, state_names[dev->ep0state]);
}

/*
 * udc_reinit - initialize software state
 */
static void udc_reinit(struct al_udc *dev)
{
	int i;

	/* device/ep0 records init */
	INIT_LIST_HEAD(&dev->gadget.ep_list);
	INIT_LIST_HEAD(&dev->gadget.ep0->ep_list);
	dev->ep0state = WAIT_FOR_SETUP;

	/* basic endpoint records init */
	for (i = 0; i < UDC_MAX_ENDPOINTS; i++) {
		struct al_ep *ep = &dev->ep[i];

		if (i != 0)
			list_add_tail(&ep->ep.ep_list, &dev->gadget.ep_list);

		ep->desc = NULL;
		ep->stopped = 0;
		INIT_LIST_HEAD(&ep->queue);
	}
	debug("%s: Init list ep0state=%s\n", __func__, state_names[dev->ep0state]);

	/* the rest was statically initialized, and is read-only */
}

/*
 * until it's enabled, this UDC should be completely invisible
 * to any USB host.
 */
static int udc_enable(struct al_udc *dev)
{
	debug("%s: call reconfig_usbd()\n", __func__);
	reconfig_usbd();
	dev->gadget.speed = USB_SPEED_UNKNOWN;

	return 0;
}

/*
 * done - retire a request; caller blocked irqs
 */
static void done(struct al_ep *ep, struct al_request *req, int status)
{
	unsigned int stopped = ep->stopped;

	list_del_init(&req->queue);

	debug("%s: status=%d req.status=%d\n", __func__, status, req->req.status);

	if (req->req.status == -EINPROGRESS)
		req->req.status = status;
	else
		status = req->req.status;

	/* don't modify queue heads during completion callback */
	ep->stopped = 1;

	spin_unlock(&ep->dev->lock);
	req->req.complete(&ep->ep, &req->req);
	spin_lock(&ep->dev->lock);

	ep->stopped = stopped;
}

/*
 * nuke - dequeue ALL requests
 */
static void nuke(struct al_ep *ep, int status)
{
	struct al_request *req;

	debug("%s: status=%d\n", __func__, status);

	/* called with irqs blocked */
	while (!list_empty(&ep->queue)) {
		req = list_entry(ep->queue.next, struct al_request, queue);
		done(ep, req, status);
	}
}

static void stop_activity(struct al_udc *dev,
		struct usb_gadget_driver *driver)
{
	int i;

	/* don't disconnect drivers more than once */
	if (dev->gadget.speed == USB_SPEED_UNKNOWN)
		driver = NULL;
	dev->gadget.speed = USB_SPEED_UNKNOWN;

	/* prevent new request submissions, kill any outstanding requests  */
	for (i = 0; i < UDC_MAX_ENDPOINTS; i++) {
		struct al_ep *ep = &dev->ep[i];
		ep->stopped = 1;
		nuke(ep, -ESHUTDOWN);
	}

	/* report disconnect; the driver is already quiesced */
	if (driver) {
		spin_unlock(&dev->lock);
		driver->disconnect(&dev->gadget);
		spin_lock(&dev->lock);
	}

	debug("%s: speed=%d driver disconnected.\n", __func__, dev->gadget.speed);

	/* re-init driver-visible data structures */
	udc_reinit(dev);
}

static void reconfig_usbd(void)
{
	int i;
	unsigned int utemp;
	unsigned int ad;

	/* 2. Soft-reset OTG Core and then unreset again. */
	al_writel(CORE_SOFT_RESET, (void __iomem *)&reg->grstctl);
	utemp = (0<<15          /* PHY Low Power Clock sel */
		|1<<14          /* Non-Periodic TxFIFO Rewind Enable */
		|0<<9|0<<8      /* [0:HNP disable, 1:HNP enable][ 0:SRP disable, 1:SRP enable] H1= 1,1 */
		|0<<7           /* ulpi DDR sel */
		|0<<6           /* 0: high speed utmi+, 1: full speed serial */
		|0<<4           /* 0: utmi+, 1:ulpi */
		|0x7<<0);       /* HS/FS Timeout */
	/* [13:10] Turnaround time 0x5:16-bit 0x9:8-bit utmi+ */
	/* [3] phy i/f 0:8bit, 1:16bit */
	utemp |= (0x9<<10 | 0<<3);
	al_writel(utemp, (void __iomem *)&reg->gusbcfg);

	/* 3. Put the OTG device core in the disconnected state and ignore */
	/*    frame number. */
	al_readl(&utemp, (void __iomem *)&reg->dctl);
	utemp |= SOFT_DISCONNECT | IGNR_FRM_NUM;
	al_writel(utemp, (void __iomem *)&reg->dctl);

	udelay(20);

	/* 4. Make the OTG device core exit from the disconnected state.*/
	al_readl(&utemp, (void __iomem *)&reg->dctl);
	utemp = utemp & ~SOFT_DISCONNECT;
	al_writel(utemp, (void __iomem *)&reg->dctl);

	for (i = 0; i < UDC_MAX_ENDPOINTS; i++) {
		al_readl(&utemp, (void __iomem *)&reg->in_endp[i].diepctl);
		if (utemp & DEPCTL_EPENA) {
			utemp |= DEPCTL_EPDIS | DEPCTL_SNAK;
			al_writel(utemp, (void __iomem *)&reg->in_endp[i].diepctl);
		}

		/* OUT EP0 cannot be disabled */
		if (i != 0) {
			al_readl(&utemp, (void __iomem *)&reg->out_endp[i].doepctl);
			if (utemp & DEPCTL_EPENA)
				al_writel(utemp|DEPCTL_EPDIS|DEPCTL_SNAK,
					(void __iomem *)&reg->out_endp[i].doepctl);
		}
	}

	/* 5. Configure OTG Core to initial settings of device mode.*/
	/* 1: full speed(30Mhz) 0:high speed]*/
	al_writel(EP_MISS_CNT(1) | DEV_SPEED_HIGH_SPEED_20, (void __iomem *)&reg->dcfg);

	mdelay(1);

	/* 6. Unmask the core interrupts*/
	al_writel(GINTMSK_INIT, (void __iomem *)&reg->gintmsk);

	/* 7. Set NAK bit of EP0 - EP6 */
	al_writel(DEPCTL_EPDIS|DEPCTL_SNAK, (void __iomem *)&reg->out_endp[EP0_CON].doepctl);
	al_writel(DEPCTL_EPDIS|DEPCTL_SNAK, (void __iomem *)&reg->in_endp[EP0_CON].diepctl);
	for (i = 1; i < UDC_MAX_ENDPOINTS; i++) {
		al_writel(DEPCTL_EPDIS|DEPCTL_SNAK, (void __iomem *)&reg->out_endp[i].doepctl);
		al_writel(DEPCTL_EPDIS|DEPCTL_SNAK, (void __iomem *)&reg->in_endp[i].diepctl);
	}

	/* 8. Unmask EPO interrupts*/
	al_writel(((1 << EP0_CON) << DAINT_OUT_BIT)
			| (1 << EP0_CON), (void __iomem *)&reg->daintmsk);

	/* 9. Unmask device OUT EP common interrupts*/
	al_writel(DOEPMSK_INIT, (void __iomem *)&reg->doepmsk);

	/* 10. Unmask device IN EP common interrupts*/
	al_writel(DIEPMSK_INIT, (void __iomem *)&reg->diepmsk);

	/* 11. Set Rx FIFO Size (in 32-bit words) */
	al_writel(RX_FIFO_SIZE >> 2, (void __iomem *)&reg->grxfsiz);

	/* 12. Set Non Periodic Tx FIFO Size */
	al_writel((NPTX_FIFO_SIZE >> 2) << 16 | ((RX_FIFO_SIZE >> 2)) << 0,
		(void __iomem *)&reg->gnptxfsiz);
	ad = (NPTX_FIFO_SIZE >> 2);

	/*     EP3 */
#define PTX_SIZE1	0x0300
	al_writel((PTX_SIZE1) << 16 | ad, (void __iomem *)&reg->dieptxf[0]);
	ad += PTX_SIZE1;
	/*     EP5 */
#define PTX_SIZE2	0x180
	al_writel((PTX_SIZE2) << 16 | ad, (void __iomem *)&reg->dieptxf[1]);
	ad += PTX_SIZE2;
	/*     EP1 */
#define PTX_SIZE3	0x180
	al_writel((PTX_SIZE3) << 16 | ad, (void __iomem *)&reg->dieptxf[2]);
	ad += PTX_SIZE3;
	/*     EP2 */
#define PTX_SIZE4	0x180
	al_writel((PTX_SIZE4) << 16 | ad, (void __iomem *)&reg->dieptxf[3]);
	ad += PTX_SIZE4;
	/*     EP4 */
#define PTX_SIZE5	0x100
	al_writel((PTX_SIZE5) << 16 | ad, (void __iomem *)&reg->dieptxf[4]);
	ad += PTX_SIZE5;

	/* Flush the RX FIFO */
	al_writel(RX_FIFO_FLUSH, (void __iomem *)&reg->grstctl);
	do {
		al_readl(&utemp, (void __iomem *)&reg->grstctl);
	} while (utemp & RX_FIFO_FLUSH);

	/* Flush all the Tx FIFO's */
	al_writel(TX_FIFO_FLUSH_ALL, (void __iomem *)&reg->grstctl);
	al_writel(TX_FIFO_FLUSH_ALL | TX_FIFO_FLUSH, (void __iomem *)&reg->grstctl);
	do {
		al_readl(&utemp, (void __iomem *)&reg->grstctl);
	} while (utemp & TX_FIFO_FLUSH);

	/* 13. Clear NAK bit of EP0 */
	/* For Slave mode*/
	/* EP0: Control OUT */
	al_writel(DEPCTL_EPDIS | DEPCTL_CNAK,
		(void __iomem *)&reg->out_endp[EP0_CON].doepctl);

	/* 14. Initialize OTG Link Core.*/
	al_writel(GAHBCFG_INIT, (void __iomem *)&reg->gahbcfg);

#ifdef APPLITE_USB_DEBUG_REG
	al_readl(&utemp, &reg->gusbcfg);
	debug_reg("%s: gusbcfg=0x%x\n", __func__, utemp);
	al_readl(&utemp, &reg->gintmsk);
	debug_reg("%s: gintmsk=0x%x\n", __func__, utemp);
	al_readl(&utemp, &reg->gahbcfg);
	debug_reg("%s: gahbcfg=0x%x\n", __func__, utemp);
	al_readl(&utemp, &reg->grstctl);
	debug_reg("%s: grstctl=0x%x\n", __func__, utemp);
	al_readl(&utemp, &reg->grxfsiz);
	debug_reg("%s: grxfsiz=0x%x\n", __func__, utemp);
	al_readl(&utemp, &reg->gnptxfsiz);
	debug_reg("%s: gnptxfsiz=0x%x\n", __func__, utemp);
	al_readl(&utemp, &reg->dctl);
	debug_reg("%s: dctl=0x%x\n", __func__, utemp);
	al_readl(&utemp, &reg->dcfg);
	debug_reg("%s: dcfg=0x%x\n", __func__, utemp);
	al_readl(&utemp, &reg->daintmsk);
	debug_reg("%s: daintmsk=0x%x\n", __func__, utemp);
	al_readl(&utemp, &reg->doepmsk);
	debug_reg("%s: doepmsk=0x%x\n", __func__, utemp);
	al_readl(&utemp, &reg->diepmsk);
	debug_reg("%s: diepmsk=0x%x\n", __func__, utemp);
	for (i = 0; i < UDC_MAX_ENDPOINTS; i++) {
		al_readl(&utemp, &reg->in_endp[i].diepctl);
		debug_reg("%s: diepctl[%d]=0x%x\n", __func__, i, utemp);
		al_readl(&utemp, &reg->out_endp[i].doepctl);
		debug_reg("%s: doepctl[%d]=0x%x\n", __func__, i, utemp);
		al_readl(&utemp, &reg->dieptxf[i]);
		debug_reg("%s: dieptxf[%d]=0x%x\n", __func__, i, utemp);
	}
#endif

}

static void set_max_pktsize(struct al_udc *dev, enum usb_device_speed speed)
{
	unsigned int ep_ctrl;
	int i;

	if (speed == USB_SPEED_HIGH) {
		ep0_fifo_size = 64;
		ep_fifo_size = 512;
		ep_fifo_size2 = 1024;
		dev->gadget.speed = USB_SPEED_HIGH;
	} else {
		ep0_fifo_size = 64;
		ep_fifo_size = 64;
		ep_fifo_size2 = 64;
		dev->gadget.speed = USB_SPEED_FULL;
	}

	dev->ep[0].ep.maxpacket = ep0_fifo_size;
	for (i = 1; i < UDC_MAX_ENDPOINTS; i++) {
		dev->ep[i].ep.maxpacket = ep_fifo_size;
		if (ep_type(&dev->ep[i]) == ep_bulk_out) {
			al_readl(&ep_ctrl, (void __iomem *)&reg->out_endp[i].doepctl);
			ep_ctrl = ep_ctrl & ~0x7ff;
			ep_ctrl |= ep_fifo_size;
			al_writel(ep_ctrl, (void __iomem *)&reg->out_endp[i].doepctl);
		} else {
			al_readl(&ep_ctrl, (void __iomem *)&reg->in_endp[i].diepctl);
			ep_ctrl = ep_ctrl & ~0x7ff;
			ep_ctrl |= ep_fifo_size;
			al_writel(ep_ctrl, (void __iomem *)&reg->in_endp[i].diepctl);
		}
	}

	/* EP0 - Control IN (64 bytes) */
	al_readl(&ep_ctrl, (void __iomem *)&reg->in_endp[EP0_CON].diepctl);
	al_writel(ep_ctrl|(0<<0), (void __iomem *)&reg->in_endp[EP0_CON].diepctl);

	/* EP0 - Control OUT (64 bytes) */
	al_readl(&ep_ctrl, (void __iomem *)&reg->out_endp[EP0_CON].doepctl);
	al_writel(ep_ctrl|(0<<0), (void __iomem *)&reg->out_endp[EP0_CON].doepctl);

	debug("%s: fifo size ep0=%d ep1-6=%d\n", __func__, ep0_fifo_size, ep_fifo_size);
}

/*
 * Enable EP
 */
static int al_ep_enable(struct usb_ep *_ep,
	const struct usb_endpoint_descriptor *desc)
{
	struct al_ep *ep;
	struct al_udc *dev;
	unsigned long flags;

	debug("%s: %p\n", __func__, _ep);

	ep = container_of(_ep, struct al_ep, ep);
	if (!_ep || !desc || ep->desc || _ep->name == ep0name
		|| desc->bDescriptorType != USB_DT_ENDPOINT
		|| ep->bEndpointAddress != desc->bEndpointAddress
		|| ep_maxpacket(ep) <
			le16_to_cpu(get_unaligned(&desc->wMaxPacketSize))) {

		debug("%s: bad ep or descriptor\n", __func__);
		return -EINVAL;
	}

	/* xfer types must match, except that interrupt ~= bulk */
	if (ep->bmAttributes != desc->bmAttributes
		&& ep->bmAttributes != USB_ENDPOINT_XFER_BULK
		&& desc->bmAttributes != USB_ENDPOINT_XFER_INT) {

		debug("%s: %s type mismatch\n", __func__, _ep->name);
		return -EINVAL;
	}

	/* hardware _could_ do smaller, but driver doesn't */
	if ((desc->bmAttributes == USB_ENDPOINT_XFER_BULK
		&& le16_to_cpu(get_unaligned(&desc->wMaxPacketSize)) !=
		ep_maxpacket(ep)) || !get_unaligned(&desc->wMaxPacketSize)) {

		debug("%s: bad %s maxpacket\n", __func__, _ep->name);
		return -ERANGE;
	}

	dev = ep->dev;
	if (!dev->driver || dev->gadget.speed == USB_SPEED_UNKNOWN) {

		debug("%s: bogus device state\n", __func__);
		return -ESHUTDOWN;
	}

	ep->stopped = 0;
	ep->desc = desc;
	ep->pio_irqs = 0;
	ep->ep.maxpacket = le16_to_cpu(get_unaligned(&desc->wMaxPacketSize));

	/* Reset halt state */
	al_udc_set_nak(ep);
	al_udc_set_halt(_ep, 0);

	spin_lock_irqsave(&ep->dev->lock, flags);
	al_udc_ep_activate(ep);
	spin_unlock_irqrestore(&ep->dev->lock, flags);

	debug("%s: enabled %s, stopped = %d, maxpacket = %d\n",
		__func__, _ep->name, ep->stopped, ep->ep.maxpacket);
	return 0;
}

/*
 * Disable EP
 */
static int al_ep_disable(struct usb_ep *_ep)
{
	struct al_ep *ep;
	unsigned long flags;

	debug("%s: %p\n", __func__, _ep);

	ep = container_of(_ep, struct al_ep, ep);
	if (!_ep || !ep->desc) {
		debug("%s: %s not enabled\n", __func__,
			ep ? ep->ep.name : NULL);
		return -EINVAL;
	}

	spin_lock_irqsave(&ep->dev->lock, flags);

	/* Nuke all pending requests */
	nuke(ep, -ESHUTDOWN);

	ep->desc = NULL;
	ep->stopped = 1;

	spin_unlock_irqrestore(&ep->dev->lock, flags);

	debug("%s: disabled %s\n", __func__, _ep->name);
	return 0;
}

static struct usb_request *al_alloc_request(struct usb_ep *ep,
					gfp_t gfp_flags)
{
	struct al_request *req;

	req = kzalloc(sizeof(struct al_request), gfp_flags);
	if (!req)
		return NULL;

	debug("%s: %s %p\n", __func__, ep->name, ep);
	INIT_LIST_HEAD(&req->queue);

	return &req->req;
}

static void al_free_request(struct usb_ep *ep, struct usb_request *_req)
{
	struct al_request *req;

	debug("%s: %p\n", __func__, ep);

	req = container_of(_req, struct al_request, req);
	WARN_ON(!list_empty(&req->queue));
	kfree(req);
}

/* dequeue JUST ONE request */
static int al_dequeue(struct usb_ep *_ep, struct usb_request *_req)
{
	struct al_ep *ep;
	struct al_request *req;
	unsigned long flags;

	debug("%s: %p\n", __func__, _ep);

	ep = container_of(_ep, struct al_ep, ep);
	if (!_ep || ep->ep.name == ep0name)
		return -EINVAL;

	spin_lock_irqsave(&ep->dev->lock, flags);

	/* make sure it's actually queued on this endpoint */
	list_for_each_entry(req, &ep->queue, queue) {
		if (&req->req == _req)
			break;
	}
	if (&req->req != _req) {
		spin_unlock_irqrestore(&ep->dev->lock, flags);
		return -EINVAL;
	}

	done(ep, req, -ECONNRESET);

	spin_unlock_irqrestore(&ep->dev->lock, flags);
	return 0;
}

/*
 * Return bytes in EP FIFO
 */
static int al_fifo_status(struct usb_ep *_ep)
{
	int count = 0;
	struct al_ep *ep;

	ep = container_of(_ep, struct al_ep, ep);
	if (!_ep) {
		debug("%s: bad ep\n", __func__);
		return -ENODEV;
	}

	debug("%s: %d\n", __func__, ep_index(ep));

	/* LPD can't report unclaimed bytes from IN fifos */
	if (ep_is_in(ep))
		return -EOPNOTSUPP;

	return count;
}

/*
 * Flush EP FIFO
 */
static void al_fifo_flush(struct usb_ep *_ep)
{
	struct al_ep *ep;
	u32 ep_num;

	ep = container_of(_ep, struct al_ep, ep);
	if (unlikely(!_ep || (!ep->desc && ep->ep.name != ep0name))) {
		debug("%s: bad ep\n", __func__);
		return;
	}

	ep_num = ep_index(ep);
	debug("%s: %d\n", __func__, ep_index(ep));
}





/* ---------------------------------------------------------------------------
 *	device-scoped parts of the api to the usb controller hardware
 * ---------------------------------------------------------------------------*/

/*
 * al_udc_pullup -
 */
static int al_udc_pullup(struct usb_gadget *_gadget, int is_active)
{
	return 0;
}

/*
 * al_udc_start -
 */
static int al_udc_start(struct usb_gadget_driver *driver,
		int (*bind)(struct usb_gadget *))
{
	struct al_udc *dev = the_controller;
	int retval;
	unsigned long flags;

	debug("%s: called '%s'\n", __func__, driver->driver.name);

	if (!driver
		|| (driver->max_speed != USB_SPEED_FULL &&
		    driver->max_speed != USB_SPEED_HIGH)
		|| !bind
		|| !driver->disconnect
		|| !driver->setup)
		return -EINVAL;
	if (!dev)
		return -ENODEV;
	if (dev->driver)
		return -EBUSY;

	spin_lock_irqsave(&dev->lock, flags);
	/* first hook up the driver ... */
	dev->driver = driver;
	dev->gadget.dev.driver = &driver->driver;
	spin_unlock_irqrestore(&dev->lock, flags);

	retval = device_add(&dev->gadget.dev);
	if (retval) {
		pr_err("%s: failed to register gadget device %d\n",
			dev->gadget.name, retval);
		goto err;
	}

	retval = bind(&dev->gadget);
	if (retval) {
		device_del(&dev->gadget.dev);
		pr_err("%s: bind to driver --> error %d\n",
			dev->gadget.name, retval);
		goto err;
	}

	debug("%s: binding gadget driver '%s'\n", __func__, driver->driver.name);

	enable_irq(dev->irq);
	udc_enable(dev);

	return 0;

err:
	dev->driver = NULL;
	dev->gadget.dev.driver = NULL;
	return retval;
}

/*
 * al_udc_stop -
 */
static int al_udc_stop(struct usb_gadget_driver *driver)
{
	struct al_udc *dev = the_controller;
	unsigned long flags;

	if (!dev)
		return -ENODEV;
	if (!driver || driver != dev->driver || !driver->unbind)
		return -EINVAL;

	debug("%s: unbind gadget driver '%s'\n", __func__, driver->driver.name);

	spin_lock_irqsave(&dev->lock, flags);
	stop_activity(dev, driver);
	spin_unlock_irqrestore(&dev->lock, flags);

	driver->unbind(&dev->gadget);

	disable_irq(dev->irq);
	device_del(&dev->gadget.dev);

	udc_disable(dev);

	dev->driver = NULL;
	dev->gadget.dev.driver = NULL;

	return 0;
}

static const struct usb_gadget_ops al_udc_ops = {
	.pullup		= al_udc_pullup,
	.start		= al_udc_start,
	.stop		= al_udc_stop,
};

/*-------------------------------------------------------------------------*/

/*
 * usb_gadget_handle_interrupts - interrupt handler
 */
static irqreturn_t
usb_gadget_handle_interrupts(int irq, void *_dev)
{
	struct al_udc *dev = _dev;
	u32 intr_status;
	u32 gintmsk;
	struct al_usbotg_reg *otg_reg;

	otg_reg = (struct al_usbotg_reg *)dev->regs;
	al_readl(&intr_status, (void __iomem *)&otg_reg->gintsts);
	al_readl(&gintmsk, (void __iomem *)&otg_reg->gintmsk);

	if (intr_status & gintmsk)
		return al_udc_irq(dev, intr_status, gintmsk);

	return IRQ_RETVAL(0);
}

/*-------------------------------------------------------------------------*/

/* this uses load-time allocation and initialization (instead of
 * doing it at run-time) to save code, eliminate fault paths, and
 * be more obviously correct.
 */
#ifdef CONFIG_ARCH_TZ3000
static struct al_udc memory = {
	.usb_address = 0,

	.gadget = {
		.ops		= &al_udc_ops,
		.ep0		= &memory.ep[0].ep,
		.name		= driver_name,
		.dev = {
			.init_name	= "gadget",
		},
	},

	/* control endpoint */
	.ep[0] = {
		.ep = {
			.name		= ep0name,
			.ops		= &al_ep_ops,
			.maxpacket	= EP0_FIFO_SIZE,
		},
		.dev		= &memory,

		.bEndpointAddress = 0,
		.bmAttributes = 0,

		.ep_type = ep_control,
		.fifo_num = 0,
	},

	/* first group of endpoints */
	.ep[1] = {
		.ep = {
			.name		= "ep1-int",
			.ops		= &al_ep_ops,
			.maxpacket	= EP_FIFO_SIZE,
		},
		.dev		= &memory,

		.bEndpointAddress = USB_DIR_IN | 1,
		.bmAttributes = USB_ENDPOINT_XFER_INT,

		.ep_type = ep_interrupt,
		.fifo_num = 1,
	},
	.ep[2] = {
		.ep = {
			.name		= "ep2-int",
			.ops		= &al_ep_ops,
			.maxpacket	= EP_FIFO_SIZE,
		},
		.dev		= &memory,

		.bEndpointAddress = USB_DIR_IN | 2,
		.bmAttributes = USB_ENDPOINT_XFER_INT,

		.ep_type = ep_interrupt,
		.fifo_num = 2,
	},

	.ep[3] = {
		.ep = {
			.name		= "ep3-iso",
			.ops		= &al_ep_ops,
			.maxpacket	= 1024,
		},
		.dev		= &memory,

		.bEndpointAddress = USB_DIR_IN | 3,
		.bmAttributes = USB_ENDPOINT_XFER_ISOC,

		.ep_type = ep_isochronous,
		.fifo_num = 3,
	},
	.ep[4] = {
		.ep = {
			.name		= "ep4-int",
			.ops		= &al_ep_ops,
			.maxpacket	= EP_FIFO_SIZE,
		},
		.dev		= &memory,

		.bEndpointAddress = USB_DIR_IN | 4,
		.bmAttributes = USB_ENDPOINT_XFER_ISOC,

		.ep_type = ep_interrupt,
		.fifo_num = 4,
	},

	.ep[5] = {
		.ep = {
			.name		= "ep5in-bulk",
			.ops		= &al_ep_ops,
			.maxpacket	= EP_FIFO_SIZE,
		},
		.dev		= &memory,

		.bEndpointAddress = USB_DIR_IN | 5,
		.bmAttributes = USB_ENDPOINT_XFER_BULK,

		.ep_type = ep_bulk_in,
		.fifo_num = 5,
	},
	.ep[6] = {
		.ep = {
			.name		= "ep6out-bulk",
			.ops		= &al_ep_ops,
			.maxpacket	= EP_FIFO_SIZE,
		},
		.dev		= &memory,

		.bEndpointAddress = USB_DIR_OUT | 6,
		.bmAttributes = USB_ENDPOINT_XFER_BULK,

		.ep_type = ep_bulk_out,
		.fifo_num = 6,
	},
};
#endif
#ifdef CONFIG_ARCH_TZ2000
static struct al_udc memory = {
	.usb_address = 0,

	.gadget = {
		.ops		= &al_udc_ops,
		.ep0		= &memory.ep[0].ep,
		.name		= driver_name,
		.dev = {
			.init_name	= "gadget",
		},
	},

	/* control endpoint */
	.ep[0] = {
		.ep = {
			.name		= ep0name,
			.ops		= &al_ep_ops,
			.maxpacket	= EP0_FIFO_SIZE,
		},
		.dev		= &memory,

		.bEndpointAddress = 0,
		.bmAttributes = 0,

		.ep_type = ep_control,
		.fifo_num = 0,
	},

	/* first group of endpoints */
	.ep[1] = {
		.ep = {
			.name		= "ep1in-bulk",
			.ops		= &al_ep_ops,
			.maxpacket	= EP_FIFO_SIZE,
		},
		.dev		= &memory,

		.bEndpointAddress = USB_DIR_IN | 1,
		.bmAttributes = USB_ENDPOINT_XFER_BULK,

		.ep_type = ep_bulk_in,
		.fifo_num = 1,
	},
	.ep[2] = {
		.ep = {
			.name		= "ep2out-bulk",
			.ops		= &al_ep_ops,
			.maxpacket	= EP_FIFO_SIZE,
		},
		.dev		= &memory,

		.bEndpointAddress = USB_DIR_OUT | 2,
		.bmAttributes = USB_ENDPOINT_XFER_BULK,

		.ep_type = ep_bulk_out,
		.fifo_num = 2,
	},

	.ep[3] = {
		.ep = {
			.name		= "ep3-iso",
			.ops		= &al_ep_ops,
			.maxpacket	= 1024,
		},
		.dev		= &memory,

		.bEndpointAddress = USB_DIR_IN | 3,
		.bmAttributes = USB_ENDPOINT_XFER_ISOC,

		.ep_type = ep_isochronous,
		.fifo_num = 3,
	},

};
#endif

/*
 * al_udc_probe - binds to the platform device
 */
static int al_udc_probe(struct platform_device *pdev)
{
	struct al_udc *dev = &memory;
	struct resource *res;
	unsigned int irq;
	int retval;
	int i;

	spin_lock_init(&dev->lock);
	dev->dev = pdev;

	device_initialize(&dev->gadget.dev);
	dev->gadget.dev.parent = &pdev->dev;

	dev->gadget.is_otg = 0;
	dev->gadget.is_a_peripheral = 0;
	dev->gadget.b_hnp_enable = 0;
	dev->gadget.a_hnp_support = 0;
	dev->gadget.a_alt_hnp_support = 0;

	the_controller = dev;
	platform_set_drvdata(pdev, dev);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		pr_err("%s: cannot find register resource 0\n",
			driver_name);
		return -EINVAL;
	}

	dev->regs_res = request_mem_region(res->start, resource_size(res),
				dev_name(&pdev->dev));
	if (!dev->regs_res) {
		pr_err("%s: cannot reserve registers\n", driver_name);
		return -ENOENT;
	}

	dev->regs = ioremap(res->start, resource_size(res));
	if (!dev->regs) {
		pr_err("%s: cannot map registers\n", driver_name);
		retval = -ENXIO;
		goto err_regs_res;
	}
	reg = (struct al_usbotg_reg *)dev->regs;

	udc_reinit(dev);

	/* irq setup after old hardware state is cleaned up */
	irq = platform_get_irq(pdev, 0);
	retval = request_irq(irq, usb_gadget_handle_interrupts,
						0, driver_name, dev);
	if (retval != 0) {
		pr_err("%s: cannot get irq %i, err %d\n", driver_name,
			dev->irq, retval);
		retval = -EBUSY;
		goto err_regs;
	}
	dev->irq = irq;
	disable_irq(dev->irq);

	for (i = 0; i < UDC_MAX_ENDPOINTS+1; i++) {
		dev->dma_buf[i] = dma_alloc_coherent(&pdev->dev,
				DMA_BUFFER_SIZE,
				&dev->dma_addr[i], GFP_KERNEL);
		if (!dev->dma_buf[i]) {
			pr_err("%s: cannot get usb_ctrl dma memory\n",
			driver_name);
			retval = -ENOMEM;
			goto err_dma;
		}
	}
	usb_ctrl = dev->dma_buf[0];
	usb_ctrl_dma_addr = dev->dma_addr[0];

	retval = usb_add_gadget_udc(&pdev->dev, &dev->gadget);
	if (retval)
		goto err_dma;

	debug("%s: probe OK! irq=%d reg=0x%x\n", __func__, irq, (u32)reg);

	return retval;

err_dma:
	for (i = 0; i < UDC_MAX_ENDPOINTS+1; i++) {
		if (dev->dma_buf[i]) {
			dma_free_coherent(&pdev->dev,
				DMA_BUFFER_SIZE,
				dev->dma_buf[i], dev->dma_addr[i]);
			dev->dma_buf[i] = NULL;
		}
	}
	free_irq(dev->irq, dev);
	dev->irq = 0;
err_regs:
	iounmap(dev->regs);
	dev->regs = NULL;
err_regs_res:
	release_resource(dev->regs_res);
	kfree(dev->regs_res);
	dev->regs_res = NULL;
	return retval;
}

static int al_udc_remove(struct platform_device *pdev)
{
	int i;
	struct al_udc *dev = platform_get_drvdata(pdev);

	usb_del_gadget_udc(&dev->gadget);
	usb_gadget_unregister_driver(dev->driver);

	udc_disable(dev);

	if (dev->irq) {
		free_irq(platform_get_irq(pdev, 0), dev);
		dev->irq = 0;
	}
	if (dev->regs) {
		iounmap(dev->regs);
		dev->regs = NULL;
	}

	for (i = 0; i < UDC_MAX_ENDPOINTS+1; i++) {
		if (dev->dma_buf[i]) {
			dma_free_coherent(&pdev->dev,
				DMA_BUFFER_SIZE,
				dev->dma_buf[i], dev->dma_addr[i]);
			dev->dma_buf[i] = NULL;
		}
	}

	if (dev->regs_res) {
		release_resource(dev->regs_res);
		kfree(dev->regs_res);
		dev->regs_res = NULL;
	}

	platform_set_drvdata(pdev, NULL);
	the_controller = NULL;

	debug("%s : remove ok! irq=%d regs=%d regs_res=%d dma_buf=%d\n",
		__func__, dev->irq, dev->regs, dev->regs_res, dev->dma_buf[0]);

	return 0;
}

/*-------------------------------------------------------------------------*/

#ifdef	CONFIG_PM
static int al_udc_suspend(struct platform_device *pdev, pm_message_t state)
{
	int i;
	struct al_udc *dev = platform_get_drvdata(pdev);

	if (dev->driver) {
		if (dev->driver->suspend)
			dev->driver->suspend(&dev->gadget);

		/* Terminate any outstanding requests  */
		spin_lock(&dev->lock);
		for (i = 0; i < UDC_MAX_ENDPOINTS; i++) {
			struct al_ep *ep = &dev->ep[i];
			ep->stopped = 1;
		}
		spin_unlock(&dev->lock);

		if (dev->driver->disconnect)
			dev->driver->disconnect(&dev->gadget);

		udc_disable(dev);
	}

	return 0;
}

static int al_udc_resume(struct platform_device *pdev)
{
	struct al_udc *dev = platform_get_drvdata(pdev);

	if (dev->driver) {
		udc_reinit(dev);
		udc_enable(dev);

		if (dev->driver->resume)
			dev->driver->resume(&dev->gadget);
	}

	return 0;
}

#else
#define	al_udc_suspend	NULL
#define	al_udc_resume	NULL
#endif /* CONFIG_PM */

/*-------------------------------------------------------------------------*/

static struct platform_driver al_udc_driver = {
	.probe		= al_udc_probe,
	.remove		= al_udc_remove,
	.suspend	= al_udc_suspend,
	.resume		= al_udc_resume,
	.driver		= {
		.owner	= THIS_MODULE,
		.name	= "applite-udc",
	},
};

static int __init al_udc_init(void)
{
	int err = 0;

	pr_info("%s: version %s\n", driver_name, DRIVER_VERSION);

	err = platform_driver_register(&al_udc_driver);
	if (err < 0) {
		pr_err("%s : platform_driver_register() failed\n",
			driver_name);
		return err;
	}

	return 0;
}
module_init(al_udc_init);

static void __exit al_udc_exit(void)
{
	platform_driver_unregister(&al_udc_driver);
}
module_exit(al_udc_exit);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("TOSHIBA Corporation");
MODULE_LICENSE("GPL v2");

