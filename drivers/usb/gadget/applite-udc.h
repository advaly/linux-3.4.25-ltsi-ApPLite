/*
 * drivers/usb/gadget/applite-udc.h
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

#ifndef __APPLITE_UDC
#define __APPLITE_UDC

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/ioport.h>
#include <linux/types.h>
#include <linux/version.h>
#include <linux/errno.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/list.h>
#include <linux/interrupt.h>
#include <linux/proc_fs.h>
#include <linux/mm.h>
#include <linux/device.h>
#include <linux/dma-mapping.h>
#include <linux/io.h>

#include <asm/byteorder.h>
#include <asm/dma.h>
#include <asm/irq.h>
#include <asm/system.h>
#include <asm/unaligned.h>

#include <linux/usb/ch9.h>
#include <linux/usb/gadget.h>

/* Max packet size */
#define EP0_FIFO_SIZE		64
#define EP_FIFO_SIZE		512
#define EP_FIFO_SIZE2		1024

#ifdef CONFIG_ARCH_TZ3000
#define UDC_MAX_ENDPOINTS	7
#endif
#ifdef CONFIG_ARCH_TZ2000
#define UDC_MAX_ENDPOINTS	4
#endif

#define WAIT_FOR_SETUP          0
#define DATA_STATE_XMIT         1
#define DATA_STATE_NEED_ZLP     2
#define WAIT_FOR_OUT_STATUS     3
#define DATA_STATE_RECV         4
#define WAIT_FOR_COMPLETE       5
#define WAIT_FOR_OUT_COMPLETE   6
#define WAIT_FOR_IN_COMPLETE    7
#define WAIT_FOR_NULL_COMPLETE  8

#define TEST_J_SEL		0x1
#define TEST_K_SEL		0x2
#define TEST_SE0_NAK_SEL	0x3
#define TEST_PACKET_SEL		0x4
#define TEST_FORCE_ENABLE_SEL	0x5

#define DMA_BUFFER_SIZE		(4096*4)

/* ************************************************************************* */
/* IO
 */

typedef enum ep_type {
	ep_control = 0,
	ep_bulk_in,
	ep_bulk_out,
	ep_interrupt,
	ep_isochronous
} ep_type_t;

struct al_ep {
	struct usb_ep ep;
	struct al_udc *dev;

	const struct usb_endpoint_descriptor *desc;
	struct list_head queue;
	unsigned long pio_irqs;
	int len;
	void *dma_buf;

	u8 stopped;
	u8 bEndpointAddress;
	u8 bmAttributes;

	ep_type_t ep_type;
	u32 fifo_num;
};

struct al_request {
	struct usb_request req;
	struct list_head queue;
};

struct al_udc {
	struct usb_gadget gadget;
	struct usb_gadget_driver *driver;
	struct platform_device *dev;
	spinlock_t lock;

	int ep0state;
	void *dma_buf[UDC_MAX_ENDPOINTS+1];
	dma_addr_t dma_addr[UDC_MAX_ENDPOINTS+1];

	struct al_ep ep[UDC_MAX_ENDPOINTS];

	unsigned char usb_address;
	void __iomem *regs;
	struct resource *regs_res;
	unsigned int irq;

	unsigned req_pending:1, req_std:1, req_config:1;
};

extern struct al_udc *the_controller;

#define ep_is_in(EP)		(((EP)->bEndpointAddress&USB_DIR_IN) == USB_DIR_IN)
#define ep_index(EP)		((EP)->bEndpointAddress&0xF)
#define ep_maxpacket(EP)	((EP)->ep.maxpacket)
#define ep_type(EP)		((EP)->ep_type)

#endif /* __APPLITE_UDC */
