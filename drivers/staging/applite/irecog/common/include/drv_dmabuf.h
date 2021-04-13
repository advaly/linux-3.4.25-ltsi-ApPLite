/*
 * linux/drivers/staging/applite/irecog/common/include/drv_dmabuf.h
 *
 * (C) Copyright TOSHIBA Corporation
 * Semiconductor & Storage Products Company 2012
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
#ifndef DRV_DMABUF_H_
#define DRV_DMABUF_H_

#include <linux/dma-buf.h>

struct drv_dmabuf_conv_adr {
	__u8 enable;
	struct dma_buf *db;
	struct dma_buf_attachment *dba;
	struct sg_table *sg;
	dma_addr_t addr;
};

static inline int drv_dmabuf_get_phys_addr(struct device *device,
					   int fd,
					   struct drv_dmabuf_conv_adr *padr,
					   enum dma_data_direction dir)
{
	/* get phys address from fd */
	padr->db = dma_buf_get(fd);
	if (IS_ERR(padr->db)) {
		pr_err("dma_buf_get() failed fd[%d]\n", fd);
		return -1;
	}
	padr->dba = dma_buf_attach(padr->db, device);
	if (IS_ERR(padr->dba)) {
		pr_err("dma_buf_attach() failed db[%p]\n", padr->db);
		goto ERR_dma_buf_attach;
	}
	padr->sg = dma_buf_map_attachment(padr->dba, dir);
	if (IS_ERR(padr->sg)) {
		pr_err("dma_buf_map_attachment() failed dba[%p]\n", padr->dba);
		goto ERR_dma_buf_map_attachment;
	}
	/* convert sg_table to dma_addr_t */
	padr->addr = sg_phys(padr->sg->sgl);

	padr->enable = 1;

	return 0;

ERR_dma_buf_map_attachment:
	dma_buf_detach(padr->db, padr->dba);
ERR_dma_buf_attach:
	dma_buf_put(padr->db);

	return -1;
}

static inline int drv_dmabuf_put_phys_addr(struct drv_dmabuf_conv_adr *padr,
					   enum dma_data_direction dir)
{
	if (padr->enable != 1)
		return 0;

	/* release address */
	if (!IS_ERR_OR_NULL(padr->dba) && !IS_ERR_OR_NULL(padr->sg))
		dma_buf_unmap_attachment(padr->dba, padr->sg, dir);

	if (!IS_ERR_OR_NULL(padr->db) && !IS_ERR_OR_NULL(padr->dba))
		dma_buf_detach(padr->db, padr->dba);

	if (!IS_ERR_OR_NULL(padr->db))
		dma_buf_put(padr->db);

	padr->enable = 0;

	return 0;
}

#endif /* DRV_DMABUF_H_ */
