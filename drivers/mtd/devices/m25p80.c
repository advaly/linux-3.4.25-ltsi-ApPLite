/*
 * MTD SPI driver for ST M25Pxx (and similar) serial flash chips
 *
 * Author: Mike Lavender, mike@steroidmicros.com
 *
 * Copyright (c) 2005, Intec Automation Inc.
 *
 * Some parts are based on lart.c by Abraham Van Der Merwe
 *
 * Cleaned up and generalized based on mtd_dataflash.c
 *
 * This code is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include <linux/init.h>
#include <linux/err.h>
#include <linux/errno.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/interrupt.h>
#include <linux/mutex.h>
#include <linux/math64.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/mod_devicetable.h>

#include <linux/mtd/cfi.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/partitions.h>
#include <linux/of_platform.h>

#include <linux/spi/spi.h>
#include <linux/spi/flash.h>
#if IS_ENABLED(CONFIG_SPI_TC90431)
#include <asm/cacheflush.h>
#include <linux/io.h>
#endif

/* Flash opcodes. */
#define	OPCODE_WREN		0x06	/* Write enable */
#define	OPCODE_RDSR		0x05	/* Read status register */
#define	OPCODE_WRSR		0x01	/* Write status register 1 byte */
#define	OPCODE_NORM_READ	0x03	/* Read data bytes (low frequency) */
#define	OPCODE_FAST_READ	0x0b	/* Read data bytes (high frequency) */
#define	OPCODE_PP		0x02	/* Page program (up to 256 bytes) */
#define	OPCODE_BE_4K		0x20	/* Erase 4KiB block */
#define	OPCODE_BE_32K		0x52	/* Erase 32KiB block */
#define	OPCODE_CHIP_ERASE	0xc7	/* Erase whole flash chip */
#define	OPCODE_SE		0xd8	/* Sector erase (usually 64KiB) */
#define	OPCODE_RDID		0x9f	/* Read JEDEC ID */

/* Used for SST flashes only. */
#define	OPCODE_BP		0x02	/* Byte program */
#define	OPCODE_WRDI		0x04	/* Write disable */
#define	OPCODE_AAI_WP		0xad	/* Auto address increment word program */

/* Used for Macronix flashes only. */
#define	OPCODE_EN4B		0xb7	/* Enter 4-byte mode */
#define	OPCODE_EX4B		0xe9	/* Exit 4-byte mode */

/* Used for Spansion flashes only. */
#define	OPCODE_BRWR		0x17	/* Bank register write */

/* Status Register bits. */
#define	SR_WIP			1	/* Write in progress */
#define	SR_WEL			2	/* Write enable latch */
/* meaning of other SR_* bits may differ between vendors */
#define	SR_BP0			4	/* Block protect 0 */
#define	SR_BP1			8	/* Block protect 1 */
#define	SR_BP2			0x10	/* Block protect 2 */
#define	SR_SRWD			0x80	/* SR write protect */

/* Define max times to check status register before we give up. */
#define	MAX_READY_WAIT_JIFFIES	(40 * HZ)	/* M25P16 specs 40s max chip erase */
#define	MAX_CMD_SIZE		5

#ifdef CONFIG_M25PXX_USE_FAST_READ
#define OPCODE_READ 	OPCODE_FAST_READ
#define FAST_READ_DUMMY_BYTE 1
#else
#define OPCODE_READ 	OPCODE_NORM_READ
#define FAST_READ_DUMMY_BYTE 0
#endif

#define JEDEC_MFR(_jedec_id)	((_jedec_id) >> 16)

static bool no_chiperase;
module_param(no_chiperase, bool, 0644);
MODULE_PARM_DESC(no_chiperase, "do not use chip erase (default 0)");

static bool no_4kerase = 1;
module_param(no_4kerase, bool, 0444);
MODULE_PARM_DESC(no_4kerase, "do not use 4k sector erase (default 1)");

#if IS_ENABLED(CONFIG_SPI_TC90431)
static bool diracc = 1;
module_param(diracc, bool, 0444);
MODULE_PARM_DESC(diracc, "enable direct access (default 1)");
#endif

/****************************************************************************/

struct m25p {
	struct spi_device	*spi;
	struct mutex		lock;
	struct mtd_info		mtd;
	u16			page_size;
	u16			addr_width;
	u8			erase_opcode;
	u8			*command;
	ulong			srval;
	bool			wp;
	/* micron n25q512a needs polling for flag status twice */
	unsigned int		need_poll_flag:1;
#if IS_ENABLED(CONFIG_SPI_TC90431)
	unsigned long		virt;
#endif
};

static inline struct m25p *mtd_to_m25p(struct mtd_info *mtd)
{
	return container_of(mtd, struct m25p, mtd);
}

/****************************************************************************/

/*
 * Internal helper functions
 */

#if IS_ENABLED(CONFIG_SPI_TC90431)
/*
 * Invalidate a region of data cache used for reading from spi flash
 */
static void invalidate_cache_for_spi(unsigned long start, size_t size)
{
	outer_inv_range(__pa(start), __pa(start) + size);
	outer_sync();
	dmac_flush_range((void *)start, (void *)start + size);
}
#endif

#define OPCODE_RDCR 0x35
#define OPCODE_HPM  0xa3
#define SR_QE       0x40
#define SR2_QE      0x02
#define CR_QUAD     0x02

/*
 * Read the configuration/status2 register.
 */
static int read_cr(struct m25p *flash)
{
	ssize_t retval;
	u8 code = OPCODE_RDCR;
	u8 val;

	retval = spi_write_then_read(flash->spi, &code, 1, &val, 1);

	if (retval < 0) {
		dev_err(&flash->spi->dev, "error %d reading CR\n", (int)retval);
		return retval;
	}

	return val;
}

/*
 * Write status and configuration/status2 registers.
 */
static int write_sr_2data(struct m25p *flash, u8 val1, u8 val2)
{
	flash->command[0] = OPCODE_WRSR;
	flash->command[1] = val1;
	flash->command[2] = val2;

	return spi_write(flash->spi, flash->command, 3);
}

/*
 * Enable high performance mode.
 */
static int high_performance_mode(struct m25p *flash)
{
	flash->command[0] = OPCODE_HPM;
	flash->command[1] = 0xff;
	flash->command[2] = 0xff;
	flash->command[3] = 0xff;

	return spi_write(flash->spi, flash->command, 4);
}

/*
 * Read the status register, returning its value in the location
 * Return the status register value.
 * Returns negative if error occurred.
 */
static int read_sr(struct m25p *flash)
{
	ssize_t retval;
	u8 code = OPCODE_RDSR;
	u8 val;

	retval = spi_write_then_read(flash->spi, &code, 1, &val, 1);

	if (retval < 0) {
		dev_err(&flash->spi->dev, "error %d reading SR\n",
				(int) retval);
		return retval;
	}

	return val;
}

/*
 * Write status register 1 byte
 * Returns negative if error occurred.
 */
static int write_sr(struct m25p *flash, u8 val)
{
	flash->command[0] = OPCODE_WRSR;
	flash->command[1] = val;

	return spi_write(flash->spi, flash->command, 2);
}

#define OPCODE_RD_FSR 0x70	/* FLAG STATUS */
#define FSR_READY	0x80

static int read_fsr(struct m25p *flash)
{
	ssize_t retval;
	u8 code = OPCODE_RD_FSR;
	u8 val;

	retval = spi_write_then_read(flash->spi, &code, 1, &val, 1);

	if (retval < 0) {
		dev_err(&flash->spi->dev, "error %d reading FSR\n",
			(int) retval);
		return retval;
	}

	return val;
}

#if IS_ENABLED(CONFIG_SPI_TC90431)
#define OPCODE_RD_VCR 0x85	/* VOLATILE CONFIGURATION */
#define OPCODE_WR_VCR 0x81

static int read_vcr(struct m25p *flash)
{
	ssize_t retval;
	u8 code = OPCODE_RD_VCR;
	u8 val;

	retval = spi_write_then_read(flash->spi, &code, 1, &val, 1);

	if (retval < 0) {
		dev_err(&flash->spi->dev, "error %d reading VCR\n",
			(int) retval);
		return retval;
	}

	return val;
}

static int write_vcr(struct m25p *flash, u8 val)
{
	flash->command[0] = OPCODE_WR_VCR;
	flash->command[1] = val;

	return spi_write(flash->spi, flash->command, 2);
}
#endif

/*
 * Set write enable latch with Write Enable command.
 * Returns negative if error occurred.
 */
static inline int write_enable(struct m25p *flash)
{
	u8	code = OPCODE_WREN;

	return spi_write_then_read(flash->spi, &code, 1, NULL, 0);
}

/*
 * Send write disble instruction to the chip.
 */
static inline int write_disable(struct m25p *flash)
{
	u8	code = OPCODE_WRDI;

	return spi_write_then_read(flash->spi, &code, 1, NULL, 0);
}

/*
 * Enable/disable 4-byte addressing mode.
 */
static inline int set_4byte(struct m25p *flash, u32 jedec_id, int enable)
{
	int ret;

	switch (JEDEC_MFR(jedec_id)) {
	case CFI_MFR_MACRONIX:
		flash->command[0] = enable ? OPCODE_EN4B : OPCODE_EX4B;
		return spi_write(flash->spi, flash->command, 1);
	case CFI_MFR_ST:
		write_enable(flash);
		flash->command[0] = enable ? OPCODE_EN4B : OPCODE_EX4B;
		ret = spi_write(flash->spi, flash->command, 1);
		write_disable(flash);
		return ret;
	default:
		/* Spansion style */
		flash->command[0] = OPCODE_BRWR;
		flash->command[1] = enable << 7;
		return spi_write(flash->spi, flash->command, 2);
	}
}

/*
 * Service routine to read status register until ready, or timeout occurs.
 * Returns non-zero if error.
 */
static int wait_till_ready(struct m25p *flash)
{
	unsigned long deadline;
	int sr;

	deadline = jiffies + MAX_READY_WAIT_JIFFIES;

	do {
		if (flash->need_poll_flag) {
			int fsr, fsr2;
			/*
			 * from n25q512a datasheet:
			 * The end of operations such as power-up,
			 * WRITE STATUS REGISTER, and WRITE NON-
			 * VOLATILE CONFIGURATION REGISTER can be
			 * detected by means of a READ FLAG STATUS
			 * REGISTER command being issued twice to poll
			 * the flag status register for both die, S#
			 * toggled between command execution, and bit
			 * 7 of the flag status register outputs 1
			 * both times.
			 */
			fsr = read_fsr(flash);
			if (fsr < 0)
				break;
			fsr2 = read_fsr(flash);
			if (fsr2 < 0)
				break;
			if (!((fsr & fsr2) & FSR_READY)) {
				cond_resched();
				continue;
			}
		}
		if ((sr = read_sr(flash)) < 0)
			break;
		else if (!(sr & SR_WIP))
			return 0;

		cond_resched();

	} while (!time_after_eq(jiffies, deadline));

	return 1;
}

/*
 * Erase the whole flash memory
 *
 * Returns 0 if successful, non-zero otherwise.
 */
static int erase_chip(struct m25p *flash)
{
	pr_debug("%s: %s %lldKiB\n", dev_name(&flash->spi->dev), __func__,
			(long long)(flash->mtd.size >> 10));

	/* Wait until finished previous write command. */
	if (wait_till_ready(flash))
		return 1;

	/* Send write enable, then erase commands. */
	write_enable(flash);

	/* Set up command buffer. */
	flash->command[0] = OPCODE_CHIP_ERASE;

	spi_write(flash->spi, flash->command, 1);

	return 0;
}

static void m25p_addr2cmd(struct m25p *flash, unsigned int addr, u8 *cmd)
{
	/* opcode is in cmd[0] */
	cmd[1] = addr >> (flash->addr_width * 8 -  8);
	cmd[2] = addr >> (flash->addr_width * 8 - 16);
	cmd[3] = addr >> (flash->addr_width * 8 - 24);
	cmd[4] = addr >> (flash->addr_width * 8 - 32);
}

static int m25p_cmdsz(struct m25p *flash)
{
	return 1 + flash->addr_width;
}

/*
 * Erase one sector of flash memory at offset ``offset'' which is any
 * address within the sector which should be erased.
 *
 * Returns 0 if successful, non-zero otherwise.
 */
static int erase_sector(struct m25p *flash, u32 offset)
{
	pr_debug("%s: %s %dKiB at 0x%08x\n", dev_name(&flash->spi->dev),
			__func__, flash->mtd.erasesize / 1024, offset);

	/* Wait until finished previous write command. */
	if (wait_till_ready(flash))
		return 1;

	/* Send write enable, then erase commands. */
	write_enable(flash);

	/* Set up command buffer. */
	flash->command[0] = flash->erase_opcode;
	m25p_addr2cmd(flash, offset, flash->command);

	spi_write(flash->spi, flash->command, m25p_cmdsz(flash));

	return 0;
}

/****************************************************************************/

/*
 * MTD implementation
 */

/*
 * Erase an address range on the flash chip.  The address range may extend
 * one or more erase sectors.  Return an error is there is a problem erasing.
 */
static int m25p80_erase(struct mtd_info *mtd, struct erase_info *instr)
{
	struct m25p *flash = mtd_to_m25p(mtd);
	u32 addr,len;
	uint32_t rem;

	pr_debug("%s: %s at 0x%llx, len %lld\n", dev_name(&flash->spi->dev),
			__func__, (long long)instr->addr,
			(long long)instr->len);

	div_u64_rem(instr->len, mtd->erasesize, &rem);
	if (rem)
		return -EINVAL;

	addr = instr->addr;
	len = instr->len;

	mutex_lock(&flash->lock);

	/* whole-chip erase? */
	if (!no_chiperase && len == flash->mtd.size) {
		if (erase_chip(flash)) {
			instr->state = MTD_ERASE_FAILED;
			mutex_unlock(&flash->lock);
			return -EIO;
		}

	/* REVISIT in some cases we could speed up erasing large regions
	 * by using OPCODE_SE instead of OPCODE_BE_4K.  We may have set up
	 * to use "small sector erase", but that's not always optimal.
	 */

	/* "sector"-at-a-time erase */
	} else {
		while (len) {
			if (erase_sector(flash, addr)) {
				instr->state = MTD_ERASE_FAILED;
				mutex_unlock(&flash->lock);
				return -EIO;
			}

			addr += mtd->erasesize;
			len -= mtd->erasesize;
		}
	}

#if IS_ENABLED(CONFIG_SPI_TC90431)
	if (flash->virt)
		invalidate_cache_for_spi(flash->virt + instr->addr, instr->len);
#endif
	mutex_unlock(&flash->lock);

	instr->state = MTD_ERASE_DONE;
	mtd_erase_callback(instr);

	return 0;
}

/*
 * Read an address range from the flash chip.  The address range
 * may be any size provided it is within the physical boundaries.
 */
static int m25p80_read(struct mtd_info *mtd, loff_t from, size_t len,
	size_t *retlen, u_char *buf)
{
	struct m25p *flash = mtd_to_m25p(mtd);
	struct spi_transfer t[2];
	struct spi_message m;

	pr_debug("%s: %s from 0x%08x, len %zd\n", dev_name(&flash->spi->dev),
			__func__, (u32)from, len);

#if IS_ENABLED(CONFIG_SPI_TC90431)
	if (flash->virt) {
		mutex_lock(&flash->lock);
		if (wait_till_ready(flash)) {
			mutex_unlock(&flash->lock);
			return 1;
		}
		memcpy(buf, (void *)flash->virt + from, len);
		mutex_unlock(&flash->lock);
		*retlen = len;
		return 0;
	}
#endif
	spi_message_init(&m);
	memset(t, 0, (sizeof t));

	/* NOTE:
	 * OPCODE_FAST_READ (if available) is faster.
	 * Should add 1 byte DUMMY_BYTE.
	 */
	t[0].tx_buf = flash->command;
	t[0].len = m25p_cmdsz(flash) + FAST_READ_DUMMY_BYTE;
	spi_message_add_tail(&t[0], &m);

	t[1].rx_buf = buf;
	t[1].len = len;
	spi_message_add_tail(&t[1], &m);

	mutex_lock(&flash->lock);

	/* Wait till previous write/erase is done. */
	if (wait_till_ready(flash)) {
		/* REVISIT status return?? */
		mutex_unlock(&flash->lock);
		return 1;
	}

	/* FIXME switch to OPCODE_FAST_READ.  It's required for higher
	 * clocks; and at this writing, every chip this driver handles
	 * supports that opcode.
	 */

	/* Set up the write data buffer. */
	flash->command[0] = OPCODE_READ;
	m25p_addr2cmd(flash, from, flash->command);

	if (!flash->spi->master->max_xfer_len ||
	    len <= flash->spi->master->max_xfer_len) {
		spi_sync(flash->spi, &m);

		*retlen = m.actual_length - m25p_cmdsz(flash) -
			FAST_READ_DUMMY_BYTE;
	} else {
		u32 max_len = flash->spi->master->max_xfer_len;
		u32 i;

		*retlen = 0;
		for (i = 0; i < len; i += max_len) {
			if (max_len > len - i)
				max_len = len - i;
			if (i != 0) {
				m25p_addr2cmd(flash, from + i, flash->command);
				wait_till_ready(flash);
				t[1].rx_buf = buf + i;
			}
			t[1].len = max_len;

			spi_sync(flash->spi, &m);

			*retlen += m.actual_length - m25p_cmdsz(flash) -
				FAST_READ_DUMMY_BYTE;
		}
	}

	mutex_unlock(&flash->lock);

	return 0;
}

/*
 * Write an address range to the flash chip.  Data must be written in
 * FLASH_PAGESIZE chunks.  The address range may be any size provided
 * it is within the physical boundaries.
 */
static int m25p80_write(struct mtd_info *mtd, loff_t to, size_t len,
	size_t *retlen, const u_char *buf)
{
	struct m25p *flash = mtd_to_m25p(mtd);
	u32 page_offset, page_size;
	struct spi_transfer t[2];
	struct spi_message m;

	pr_debug("%s: %s to 0x%08x, len %zd\n", dev_name(&flash->spi->dev),
			__func__, (u32)to, len);
	if (flash->spi->master->max_xfer_len &&
	    min_t(size_t, len, flash->page_size) >
	    flash->spi->master->max_xfer_len) {
		dev_err(&flash->spi->dev, "write len exceeds max_xfer_len\n");
		return -EINVAL;
	}

	spi_message_init(&m);
	memset(t, 0, (sizeof t));

	t[0].tx_buf = flash->command;
	t[0].len = m25p_cmdsz(flash);
	spi_message_add_tail(&t[0], &m);

	t[1].tx_buf = buf;
	spi_message_add_tail(&t[1], &m);

	mutex_lock(&flash->lock);

	/* Wait until finished previous write command. */
	if (wait_till_ready(flash)) {
		mutex_unlock(&flash->lock);
		return 1;
	}

	write_enable(flash);

	/* Set up the opcode in the write buffer. */
	flash->command[0] = OPCODE_PP;
	m25p_addr2cmd(flash, to, flash->command);

	page_offset = to & (flash->page_size - 1);

	/* do all the bytes fit onto one page? */
	if (page_offset + len <= flash->page_size) {
		t[1].len = len;

		spi_sync(flash->spi, &m);

		*retlen = m.actual_length - m25p_cmdsz(flash);
	} else {
		u32 i;

		/* the size of data remaining on the first page */
		page_size = flash->page_size - page_offset;

		t[1].len = page_size;
		spi_sync(flash->spi, &m);

		*retlen = m.actual_length - m25p_cmdsz(flash);

		/* write everything in flash->page_size chunks */
		for (i = page_size; i < len; i += page_size) {
			page_size = len - i;
			if (page_size > flash->page_size)
				page_size = flash->page_size;

			/* write the next page to flash */
			m25p_addr2cmd(flash, to + i, flash->command);

			t[1].tx_buf = buf + i;
			t[1].len = page_size;

			wait_till_ready(flash);

			write_enable(flash);

			spi_sync(flash->spi, &m);

			*retlen += m.actual_length - m25p_cmdsz(flash);
		}
	}

#if IS_ENABLED(CONFIG_SPI_TC90431)
	if (flash->virt)
		invalidate_cache_for_spi(flash->virt + to, len);
#endif
	mutex_unlock(&flash->lock);

	return 0;
}

static int sst_write(struct mtd_info *mtd, loff_t to, size_t len,
		size_t *retlen, const u_char *buf)
{
	struct m25p *flash = mtd_to_m25p(mtd);
	struct spi_transfer t[2];
	struct spi_message m;
	size_t actual;
	int cmd_sz, ret;

	pr_debug("%s: %s to 0x%08x, len %zd\n", dev_name(&flash->spi->dev),
			__func__, (u32)to, len);
	if (flash->spi->master->max_xfer_len &&
	    min_t(size_t, len, flash->page_size) >
	    flash->spi->master->max_xfer_len) {
		dev_err(&flash->spi->dev, "write len exceeds max_xfer_len\n");
		return -EINVAL;
	}

	spi_message_init(&m);
	memset(t, 0, (sizeof t));

	t[0].tx_buf = flash->command;
	t[0].len = m25p_cmdsz(flash);
	spi_message_add_tail(&t[0], &m);

	t[1].tx_buf = buf;
	spi_message_add_tail(&t[1], &m);

	mutex_lock(&flash->lock);

	/* Wait until finished previous write command. */
	ret = wait_till_ready(flash);
	if (ret)
		goto time_out;

	write_enable(flash);

	actual = to % 2;
	/* Start write from odd address. */
	if (actual) {
		flash->command[0] = OPCODE_BP;
		m25p_addr2cmd(flash, to, flash->command);

		/* write one byte. */
		t[1].len = 1;
		spi_sync(flash->spi, &m);
		ret = wait_till_ready(flash);
		if (ret)
			goto time_out;
		*retlen += m.actual_length - m25p_cmdsz(flash);
	}
	to += actual;

	flash->command[0] = OPCODE_AAI_WP;
	m25p_addr2cmd(flash, to, flash->command);

	/* Write out most of the data here. */
	cmd_sz = m25p_cmdsz(flash);
	for (; actual < len - 1; actual += 2) {
		t[0].len = cmd_sz;
		/* write two bytes. */
		t[1].len = 2;
		t[1].tx_buf = buf + actual;

		spi_sync(flash->spi, &m);
		ret = wait_till_ready(flash);
		if (ret)
			goto time_out;
		*retlen += m.actual_length - cmd_sz;
		cmd_sz = 1;
		to += 2;
	}
	write_disable(flash);
	ret = wait_till_ready(flash);
	if (ret)
		goto time_out;

	/* Write out trailing byte if it exists. */
	if (actual != len) {
		write_enable(flash);
		flash->command[0] = OPCODE_BP;
		m25p_addr2cmd(flash, to, flash->command);
		t[0].len = m25p_cmdsz(flash);
		t[1].len = 1;
		t[1].tx_buf = buf + actual;

		spi_sync(flash->spi, &m);
		ret = wait_till_ready(flash);
		if (ret)
			goto time_out;
		*retlen += m.actual_length - m25p_cmdsz(flash);
		write_disable(flash);
	}

time_out:
#if IS_ENABLED(CONFIG_SPI_TC90431)
	if (flash->virt)
		invalidate_cache_for_spi(flash->virt + to, len);
#endif
	mutex_unlock(&flash->lock);
	return ret;
}

/****************************************************************************/

/*
 * SPI device driver setup and teardown
 */

struct flash_info {
	/* JEDEC id zero means "no ID" (most older chips); otherwise it has
	 * a high byte of zero plus three data bytes: the manufacturer id,
	 * then a two byte device id.
	 */
	u32		jedec_id;
	u16             ext_id;

	/* The size listed here is what works with OPCODE_SE, which isn't
	 * necessarily called a "sector" by the vendor.
	 */
	unsigned	sector_size;
	u16		n_sectors;

	u16		page_size;
	u16		addr_width;

	u16		flags;
#define	SECT_4K		0x01		/* OPCODE_BE_4K works uniformly */
#define	M25P_NO_ERASE	0x02		/* No erase command needed */
};

/*
 * Chip specific functions for lock/unlock
 */

static int lock_func_type1(struct mtd_info *mtd, loff_t ofs, uint64_t len)
{
	struct m25p *flash = mtd_to_m25p(mtd);
	int sr, sr2;
	mutex_lock(&flash->lock);
	sr = read_sr(flash);
	sr2 = read_cr(flash);
	sr |= (SR_BP0 | SR_BP1 | SR_BP2);
	write_enable(flash);
	write_sr_2data(flash, sr, sr2);
	if (wait_till_ready(flash)) {
		mutex_unlock(&flash->lock);
		return -EBUSY;
	}
	sr = read_sr(flash);
	sr2 = read_cr(flash);
	if ((sr & (SR_BP0 | SR_BP1 | SR_BP2)) != (SR_BP0 | SR_BP1 | SR_BP2)) {
		mutex_unlock(&flash->lock);
		return -EIO;
	}
	flash->wp = 1;
	flash->srval = sr | (sr2 << 8);
	mutex_unlock(&flash->lock);
	return 0;
}

static int unlock_func_type1(struct mtd_info *mtd, loff_t ofs, uint64_t len)
{
	struct m25p *flash = mtd_to_m25p(mtd);
	int sr, sr2;
	mutex_lock(&flash->lock);
	sr = read_sr(flash);
	sr2 = read_cr(flash);
	sr &= ~(SR_BP0 | SR_BP1 | SR_BP2);
	write_enable(flash);
	write_sr_2data(flash, sr, sr2);
	if (wait_till_ready(flash)) {
		mutex_unlock(&flash->lock);
		return -EBUSY;
	}
	sr = read_sr(flash);
	sr2 = read_cr(flash);
	if ((sr & (SR_BP0 | SR_BP1 | SR_BP2)) != 0) {
		mutex_unlock(&flash->lock);
		return -EIO;
	}
	flash->wp = 0;
	flash->srval = sr | (sr2 << 8);
	mutex_unlock(&flash->lock);
	return 0;
}

static int lock_func_type2(struct mtd_info *mtd, loff_t ofs, uint64_t len)
{
	struct m25p *flash = mtd_to_m25p(mtd);
	int sr;
	mutex_lock(&flash->lock);
	sr = read_sr(flash);
	sr |= (SR_BP0 | SR_BP1 | SR_BP2);
	write_enable(flash);
	write_sr(flash, sr);
	if (wait_till_ready(flash)) {
		mutex_unlock(&flash->lock);
		return -EBUSY;
	}
	sr = read_sr(flash);
	if ((sr & (SR_BP0 | SR_BP1 | SR_BP2)) != (SR_BP0 | SR_BP1 | SR_BP2)) {
		mutex_unlock(&flash->lock);
		return -EIO;
	}
	flash->wp = 1;
	flash->srval = sr;
	mutex_unlock(&flash->lock);
	return 0;
}

static int unlock_func_type2(struct mtd_info *mtd, loff_t ofs, uint64_t len)
{
	struct m25p *flash = mtd_to_m25p(mtd);
	int sr;
	mutex_lock(&flash->lock);
	sr = read_sr(flash);
	sr &= ~(SR_BP0 | SR_BP1 | SR_BP2);
	write_enable(flash);
	write_sr(flash, sr);
	if (wait_till_ready(flash)) {
		mutex_unlock(&flash->lock);
		return -EBUSY;
	}
	sr = read_sr(flash);
	if ((sr & (SR_BP0 | SR_BP1 | SR_BP2)) != 0) {
		mutex_unlock(&flash->lock);
		return -EIO;
	}
	flash->wp = 0;
	flash->srval = sr;
	mutex_unlock(&flash->lock);
	return 0;
}

/*
 * Chip specific functions for enabling dual/quad mode.
 */
struct flash_fixup_info {
	const char *name;
	int (*option_func)(struct m25p *flash,
			   const struct flash_fixup_info *finfo);
#if IS_ENABLED(CONFIG_SPI_TC90431)
	u32 max_speed_hz;
	u32 deassert_time;
	u8 dir_read_opcode;
	u32 dir_max_speed_hz;
	u32 dir_deassert_time;
#endif
};

static int opt_func_s25flxxp(struct m25p *flash,
			     const struct flash_fixup_info *finfo)
{
	int sr, cr;
	sr = read_sr(flash);
	cr = read_cr(flash);
	write_enable(flash);
	write_sr_2data(flash, sr, cr | CR_QUAD);
	if (wait_till_ready(flash))
		return -EBUSY;

	return 0;
}

static int opt_func_w25q32v(struct m25p *flash,
			    const struct flash_fixup_info *finfo)
{
	int sr, sr2;

	write_enable(flash);
	high_performance_mode(flash);
	sr = read_sr(flash);
	sr2 = read_cr(flash);
	write_enable(flash);
	write_sr_2data(flash, sr, sr2 | SR2_QE);
	if (wait_till_ready(flash))
		return -EBUSY;

	return 0;
}

static int opt_func_w25q80bv(struct m25p *flash,
			     const struct flash_fixup_info *finfo)
{
	int sr, sr2;

	sr = read_sr(flash);
	sr2 = read_cr(flash);
	write_enable(flash);
	write_sr_2data(flash, sr, sr2 | SR2_QE);
	if (wait_till_ready(flash))
		return -EBUSY;

	if (flash->srval != ULONG_MAX) {
		sr = (flash->srval & 0xff);
		sr2 = (flash->srval & 0xff00) >> 8;
		write_enable(flash);
		write_sr_2data(flash, sr, sr2);
		if (wait_till_ready(flash))
			return -EBUSY;
	}

	flash->mtd._lock = lock_func_type1;
	flash->mtd._unlock = unlock_func_type1;

	sr = read_sr(flash);
	sr2 = read_cr(flash);
	flash->srval = sr | (sr2 << 8);
	if ((sr & (SR_BP0 | SR_BP1 | SR_BP2)) == (SR_BP0 | SR_BP1 | SR_BP2))
		flash->wp = 1;
	else
		flash->wp = 0;

	return 0;
}

static int opt_func_w25q128bv(struct m25p *flash,
			      const struct flash_fixup_info *finfo)
{
	int sr, sr2;

	sr = read_sr(flash);
	sr2 = read_cr(flash);
	write_enable(flash);
	write_sr_2data(flash, sr, sr2 | SR2_QE);
	if (wait_till_ready(flash))
		return -EBUSY;

	return 0;
}

static int opt_func_mx25lxx35d(struct m25p *flash,
			       const struct flash_fixup_info *finfo)
{
	int sr;

	sr = read_sr(flash);
	write_enable(flash);
	write_sr(flash, sr | SR_QE);
	if (wait_till_ready(flash))
		return -EBUSY;

	return 0;
}

static int opt_func_en25q080a(struct m25p *flash,
			      const struct flash_fixup_info *finfo)
{
	int sr;

	if (flash->srval != ULONG_MAX) {
		sr = (flash->srval & 0xff);
		write_enable(flash);
		write_sr(flash, sr);
		if (wait_till_ready(flash))
			return -EBUSY;
	}

	flash->mtd._lock = lock_func_type2;
	flash->mtd._unlock = unlock_func_type2;

	sr = read_sr(flash);
	flash->srval = sr;
	if ((sr & (SR_BP0 | SR_BP1 | SR_BP2)) == (SR_BP0 | SR_BP1 | SR_BP2))
		flash->wp = 1;
	else
		flash->wp = 0;

	return 0;
}

static int opt_func_n25q512a(struct m25p *flash,
			     const struct flash_fixup_info *finfo)
{
#if IS_ENABLED(CONFIG_SPI_TC90431)
	struct flash_platform_data *pdata = flash->spi->dev.platform_data;
	if (pdata && pdata->tc90431_spi_data) {
		int vcr;
		int cycles = 8;
		switch (finfo->dir_read_opcode) {
		case OPCODE_FAST_READ_DUAL_IO:
			pdata->tc90431_spi_data->dir_read_dummy_count = 2;
			break;
		case OPCODE_FAST_READ_QUAD_IO:
			pdata->tc90431_spi_data->dir_read_dummy_count = 4;
			break;
		default:
			pdata->tc90431_spi_data->dir_read_dummy_count = 1;
		}
		vcr = read_vcr(flash);
		if (vcr < 0)
			return vcr;
		write_enable(flash);
		write_vcr(flash, (vcr & 0x0f) | (cycles << 4));
	}
#endif
	flash->need_poll_flag = true;
	return 0;
}

#define INFO(_jedec_id, _ext_id, _sector_size, _n_sectors, _flags)	\
	((kernel_ulong_t)&(struct flash_info) {				\
		.jedec_id = (_jedec_id),				\
		.ext_id = (_ext_id),					\
		.sector_size = (_sector_size),				\
		.n_sectors = (_n_sectors),				\
		.page_size = 256,					\
		.flags = (_flags),					\
	})

#define CAT25_INFO(_sector_size, _n_sectors, _page_size, _addr_width)	\
	((kernel_ulong_t)&(struct flash_info) {				\
		.sector_size = (_sector_size),				\
		.n_sectors = (_n_sectors),				\
		.page_size = (_page_size),				\
		.addr_width = (_addr_width),				\
		.flags = M25P_NO_ERASE,					\
	})

/* NOTE: double check command sets and memory organization when you add
 * more flash chips.  This current list focusses on newer chips, which
 * have been converging on command sets which including JEDEC ID.
 */
static const struct spi_device_id m25p_ids[] = {
	/* Atmel -- some are (confusingly) marketed as "DataFlash" */
	{ "at25fs010",  INFO(0x1f6601, 0, 32 * 1024,   4, SECT_4K) },
	{ "at25fs040",  INFO(0x1f6604, 0, 64 * 1024,   8, SECT_4K) },

	{ "at25df041a", INFO(0x1f4401, 0, 64 * 1024,   8, SECT_4K) },
	{ "at25df321a", INFO(0x1f4701, 0, 64 * 1024,  64, SECT_4K) },
	{ "at25df641",  INFO(0x1f4800, 0, 64 * 1024, 128, SECT_4K) },

	{ "at26f004",   INFO(0x1f0400, 0, 64 * 1024,  8, SECT_4K) },
	{ "at26df081a", INFO(0x1f4501, 0, 64 * 1024, 16, SECT_4K) },
	{ "at26df161a", INFO(0x1f4601, 0, 64 * 1024, 32, SECT_4K) },
	{ "at25df161",  INFO(0x1f4602, 0, 64 * 1024, 32, 0) },
	{ "at26df321",  INFO(0x1f4700, 0, 64 * 1024, 64, SECT_4K) },

	/* EON -- en25xxx */
	{ "en25f32", INFO(0x1c3116, 0, 64 * 1024,  64, SECT_4K) },
	{ "en25p32", INFO(0x1c2016, 0, 64 * 1024,  64, 0) },
	{ "en25q32b", INFO(0x1c3016, 0, 64 * 1024,  64, 0) },
	{ "en25p64", INFO(0x1c2017, 0, 64 * 1024, 128, 0) },
	{ "en25q080a",	INFO(0x1c3014, 0, 64 * 1024, 16, 0) },
	{ "en25q128",	INFO(0x1c3018, 0, 64 * 1024, 256, 0) },

	/* Intel/Numonyx -- xxxs33b */
	{ "160s33b",  INFO(0x898911, 0, 64 * 1024,  32, 0) },
	{ "320s33b",  INFO(0x898912, 0, 64 * 1024,  64, 0) },
	{ "640s33b",  INFO(0x898913, 0, 64 * 1024, 128, 0) },

	/* Macronix */
	{ "mx25l4005a",  INFO(0xc22013, 0, 64 * 1024,   8, SECT_4K) },
	{ "mx25l8005",   INFO(0xc22014, 0, 64 * 1024,  16, 0) },
	{ "mx25l1606e",  INFO(0xc22015, 0, 64 * 1024,  32, SECT_4K) },
	{ "mx25l3205d",  INFO(0xc22016, 0, 64 * 1024,  64, 0) },
	{ "mx25l6405d",  INFO(0xc22017, 0, 64 * 1024, 128, 0) },
	{ "mx25u6435f",  INFO(0xc22537, 0, 64 * 1024, 128, SECT_4K) },
	{ "mx25l12805d", INFO(0xc22018, 0, 64 * 1024, 256, 0) },
	{ "mx25l12855e", INFO(0xc22618, 0, 64 * 1024, 256, 0) },
	{ "mx25u12835f", INFO(0xc22538, 0, 64 * 1024, 256, 0) },
	{ "mx25l25635e", INFO(0xc22019, 0, 64 * 1024, 512, 0) },
	{ "mx25l25655e", INFO(0xc22619, 0, 64 * 1024, 512, 0) },
	{ "mx25l1635d",  INFO(0xc22415, 0, 64 * 1024,  32, 0) },
	{ "mx25l3235d",  INFO(0xc25e16, 0, 64 * 1024,  64, 0) },
	{ "mx66l51235f", INFO(0xc2201a, 0, 64 * 1024, 1024, SECT_4K) },

	/* Spansion -- single (large) sector size only, at least
	 * for the chips listed here (without boot sectors).
	 */
	{ "s25sl004a",  INFO(0x010212,      0,  64 * 1024,   8, 0) },
	{ "s25sl008a",  INFO(0x010213,      0,  64 * 1024,  16, 0) },
	{ "s25sl016a",  INFO(0x010214,      0,  64 * 1024,  32, 0) },
	{ "s25sl032a",  INFO(0x010215,      0,  64 * 1024,  64, 0) },
	{ "s25sl032p",  INFO(0x010215, 0x4d00,  64 * 1024,  64, SECT_4K) },
	{ "s25sl064a",  INFO(0x010216,      0,  64 * 1024, 128, 0) },
	{ "s25fl256s0", INFO(0x010219, 0x4d00, 256 * 1024, 128, 0) },
	{ "s25fl256s1", INFO(0x010219, 0x4d01,  64 * 1024, 512, 0) },
	{ "s25fl512s",  INFO(0x010220, 0x4d00, 256 * 1024, 256, 0) },
	{ "s70fl01gs",  INFO(0x010221, 0x4d00, 256 * 1024, 256, 0) },
	{ "s25sl12800", INFO(0x012018, 0x0300, 256 * 1024,  64, 0) },
	{ "s25sl12801", INFO(0x012018, 0x0301,  64 * 1024, 256, 0) },
	{ "s25fl129p0", INFO(0x012018, 0x4d00, 256 * 1024,  64, 0) },
	{ "s25fl129p1", INFO(0x012018, 0x4d01,  64 * 1024, 256, 0) },
	{ "s25fl016k",  INFO(0xef4015,      0,  64 * 1024,  32, SECT_4K) },
	{ "s25fl064k",  INFO(0xef4017,      0,  64 * 1024, 128, SECT_4K) },

	/* SST -- large erase sizes are "overlays", "sectors" are 4K */
	{ "sst25vf040b", INFO(0xbf258d, 0, 64 * 1024,  8, SECT_4K) },
	{ "sst25vf080b", INFO(0xbf258e, 0, 64 * 1024, 16, SECT_4K) },
	{ "sst25vf016b", INFO(0xbf2541, 0, 64 * 1024, 32, SECT_4K) },
	{ "sst25vf032b", INFO(0xbf254a, 0, 64 * 1024, 64, SECT_4K) },
	{ "sst25wf512",  INFO(0xbf2501, 0, 64 * 1024,  1, SECT_4K) },
	{ "sst25wf010",  INFO(0xbf2502, 0, 64 * 1024,  2, SECT_4K) },
	{ "sst25wf020",  INFO(0xbf2503, 0, 64 * 1024,  4, SECT_4K) },
	{ "sst25wf040",  INFO(0xbf2504, 0, 64 * 1024,  8, SECT_4K) },

	/* ST Microelectronics -- newer production may have feature updates */
	{ "m25p05",  INFO(0x202010,  0,  32 * 1024,   2, 0) },
	{ "m25p10",  INFO(0x202011,  0,  32 * 1024,   4, 0) },
	{ "m25p20",  INFO(0x202012,  0,  64 * 1024,   4, 0) },
	{ "m25p40",  INFO(0x202013,  0,  64 * 1024,   8, 0) },
	{ "m25p80",  INFO(0x202014,  0,  64 * 1024,  16, 0) },
	{ "m25p16",  INFO(0x202015,  0,  64 * 1024,  32, 0) },
	{ "m25p32",  INFO(0x202016,  0,  64 * 1024,  64, 0) },
	{ "m25p64",  INFO(0x202017,  0,  64 * 1024, 128, 0) },
	{ "m25p128", INFO(0x202018,  0, 256 * 1024,  64, 0) },

	{ "m25p05-nonjedec",  INFO(0, 0,  32 * 1024,   2, 0) },
	{ "m25p10-nonjedec",  INFO(0, 0,  32 * 1024,   4, 0) },
	{ "m25p20-nonjedec",  INFO(0, 0,  64 * 1024,   4, 0) },
	{ "m25p40-nonjedec",  INFO(0, 0,  64 * 1024,   8, 0) },
	{ "m25p80-nonjedec",  INFO(0, 0,  64 * 1024,  16, 0) },
	{ "m25p16-nonjedec",  INFO(0, 0,  64 * 1024,  32, 0) },
	{ "m25p32-nonjedec",  INFO(0, 0,  64 * 1024,  64, 0) },
	{ "m25p64-nonjedec",  INFO(0, 0,  64 * 1024, 128, 0) },
	{ "m25p128-nonjedec", INFO(0, 0, 256 * 1024,  64, 0) },

	{ "m45pe10", INFO(0x204011,  0, 64 * 1024,    2, 0) },
	{ "m45pe80", INFO(0x204014,  0, 64 * 1024,   16, 0) },
	{ "m45pe16", INFO(0x204015,  0, 64 * 1024,   32, 0) },

	{ "m25pe80", INFO(0x208014,  0, 64 * 1024, 16,       0) },
	{ "m25pe16", INFO(0x208015,  0, 64 * 1024, 32, SECT_4K) },

	{ "m25px32",    INFO(0x207116,  0, 64 * 1024, 64, SECT_4K) },
	{ "m25px32-s0", INFO(0x207316,  0, 64 * 1024, 64, SECT_4K) },
	{ "m25px32-s1", INFO(0x206316,  0, 64 * 1024, 64, SECT_4K) },
	{ "m25px64",    INFO(0x207117,  0, 64 * 1024, 128, 0) },

	{ "n25q128",    INFO(0x20ba18,  0, 64 * 1024, 256, 0) },
	{ "n25q512a",   INFO(0x20ba20,  0, 64 * 1024, 1024, SECT_4K) },

	/* Winbond -- w25x "blocks" are 64K, "sectors" are 4KiB */
	{ "w25x10", INFO(0xef3011, 0, 64 * 1024,  2,  SECT_4K) },
	{ "w25x20", INFO(0xef3012, 0, 64 * 1024,  4,  SECT_4K) },
	{ "w25x40", INFO(0xef3013, 0, 64 * 1024,  8,  SECT_4K) },
	{ "w25x80", INFO(0xef3014, 0, 64 * 1024,  16, SECT_4K) },
	{ "w25x16", INFO(0xef3015, 0, 64 * 1024,  32, SECT_4K) },
	{ "w25x32", INFO(0xef3016, 0, 64 * 1024,  64, SECT_4K) },
	{ "w25q32", INFO(0xef4016, 0, 64 * 1024,  64, SECT_4K) },
	{ "w25x64", INFO(0xef3017, 0, 64 * 1024, 128, SECT_4K) },
	{ "w25q64", INFO(0xef4017, 0, 64 * 1024, 128, SECT_4K) },
	{ "w25q80bv",	INFO(0xef4014, 0, 64 * 1024, 16, 0) },
	{ "w25q128bv",	INFO(0xef4018, 0, 64 * 1024, 256, 0) },

	/* Catalyst / On Semiconductor -- non-JEDEC */
	{ "cat25c11", CAT25_INFO(  16, 8, 16, 1) },
	{ "cat25c03", CAT25_INFO(  32, 8, 16, 2) },
	{ "cat25c09", CAT25_INFO( 128, 8, 32, 2) },
	{ "cat25c17", CAT25_INFO( 256, 8, 32, 2) },
	{ "cat25128", CAT25_INFO(2048, 8, 64, 2) },
	{ },
};

#if IS_ENABLED(CONFIG_SPI_TC90431)
#define FINFO(_name, _option_func, _max_speed_hz, _deassert_time, \
	_dir_read_opcode, _dir_max_speed_hz, _dir_deassert_time) \
	.name = _name, \
	.option_func = _option_func, \
	.max_speed_hz = _max_speed_hz, \
	.deassert_time = _deassert_time, \
	.dir_read_opcode = _dir_read_opcode, \
	.dir_max_speed_hz = _dir_max_speed_hz, \
	.dir_deassert_time = _dir_deassert_time,
#else
#define FINFO(_name, _option_func, _max_speed_hz, _deassert_time, \
	_dir_read_opcode, _dir_max_speed_hz, _dir_deassert_time) \
	.name = _name, \
	.option_func = _option_func,
#endif

static const struct flash_fixup_info m25p_fixup_ids[] = {
	{ FINFO("s25sl032p", opt_func_s25flxxp,
		104000000, 50, OPCODE_FAST_READ_QUAD_IO, 80000000, 50) },
	{ FINFO("s25fl129p1", opt_func_s25flxxp,
		104000000, 50, OPCODE_FAST_READ_QUAD_IO, 80000000, 10) },
	{ FINFO("s25fl512s", opt_func_s25flxxp,
		104000000, 50, OPCODE_FAST_READ_QUAD_IO, 80000000, 10) },
	{ FINFO("w25q32", opt_func_w25q32v,
		80000000, 50, OPCODE_FAST_READ_QUAD_IO, 80000000, 50) },
	{ FINFO("w25q128bv", opt_func_w25q128bv,
		104000000, 50, OPCODE_FAST_READ_QUAD_IO, 80000000, 50) },
	{ FINFO("w25q80bv", opt_func_w25q80bv,
		104000000, 50, OPCODE_FAST_READ_QUAD_IO, 80000000, 50) },
	{ FINFO("mx25l1635d", opt_func_mx25lxx35d,
		86000000, 50, OPCODE_FAST_READ_QUAD_IO, 75000000, 50) },
	{ FINFO("mx25l3235d", opt_func_mx25lxx35d,
		104000000, 50, OPCODE_FAST_READ_QUAD_IO, 75000000, 50) },
	{ FINFO("mx25l6405d", opt_func_mx25lxx35d,
		104000000, 50, OPCODE_FAST_READ_QUAD_IO, 70000000, 50) },
	{ FINFO("mx25l12805d", opt_func_mx25lxx35d, /* mx25l12835f */
		133000000, 30, OPCODE_FAST_READ_QUAD_IO, 84000000, 7) },
	{ FINFO("en25q080a", opt_func_en25q080a,
		100000000, 50, OPCODE_FAST_READ_QUAD_IO, 80000000, 15) },
	{ FINFO("en25q128", opt_func_en25q080a,
		104000000, 50, OPCODE_FAST_READ_QUAD_IO, 80000000, 15) },
	{ FINFO("mx25u12835f", opt_func_mx25lxx35d,
		104000000, 30, OPCODE_FAST_READ_QUAD_IO, 84000000, 5) },
	{ FINFO("mx25u6435f", opt_func_mx25lxx35d,
		104000000, 30, OPCODE_FAST_READ_QUAD_IO, 84000000, 5) },
	{ FINFO("mx66l51235f", opt_func_mx25lxx35d,
		133000000, 30, OPCODE_FAST_READ_QUAD_IO, 84000000, 7) },
#if 1 /* REVISIT: limit to 33MHz and increase dir_deassert_time */
	{ FINFO("n25q512a", opt_func_n25q512a,
		108000000, 50, OPCODE_FAST_READ_QUAD_IO, 33333334, 580) },
#else
	{ FINFO("n25q512a", opt_func_n25q512a,
		108000000, 50, OPCODE_FAST_READ_QUAD_IO, 95000000, 20) },
#endif
};

MODULE_DEVICE_TABLE(spi, m25p_ids);

static const struct spi_device_id *__devinit jedec_probe(struct spi_device *spi)
{
	int			tmp;
	u8			code = OPCODE_RDID;
	u8			id[5];
	u32			jedec;
	u16                     ext_jedec;
	struct flash_info	*info;

	/* JEDEC also defines an optional "extended device information"
	 * string for after vendor-specific data, after the three bytes
	 * we use here.  Supporting some chips might require using it.
	 */
	tmp = spi_write_then_read(spi, &code, 1, id, 5);
	if (tmp < 0) {
		pr_debug("%s: error %d reading JEDEC ID\n",
				dev_name(&spi->dev), tmp);
		return ERR_PTR(tmp);
	}
	jedec = id[0];
	jedec = jedec << 8;
	jedec |= id[1];
	jedec = jedec << 8;
	jedec |= id[2];

	ext_jedec = id[3] << 8 | id[4];

	for (tmp = 0; tmp < ARRAY_SIZE(m25p_ids) - 1; tmp++) {
		info = (void *)m25p_ids[tmp].driver_data;
		if (info->jedec_id == jedec) {
			if (info->ext_id != 0 && info->ext_id != ext_jedec)
				continue;
			return &m25p_ids[tmp];
		}
	}
	dev_err(&spi->dev, "unrecognized JEDEC id %06x\n", jedec);
	return ERR_PTR(-ENODEV);
}


/*
 * board specific setup should have ensured the SPI clock used here
 * matches what the READ command supports, at least until this driver
 * understands FAST_READ (for clocks over 25 MHz).
 */
static int __devinit m25p_probe(struct spi_device *spi)
{
	const struct spi_device_id	*id = spi_get_device_id(spi);
	struct flash_platform_data	*data;
	struct m25p			*flash;
	struct flash_info		*info;
	unsigned			i;
	struct mtd_part_parser_data	ppdata;
#if IS_ENABLED(CONFIG_SPI_TC90431)
	struct tc90431_spi_controller_data *tc90431_spi_data = NULL;
#endif

#ifdef CONFIG_MTD_OF_PARTS
	if (!of_device_is_available(spi->dev.of_node))
		return -ENODEV;
#endif

	/* Platform data helps sort out which chip type we have, as
	 * well as how this board partitions it.  If we don't have
	 * a chip ID, try the JEDEC id commands; they'll work for most
	 * newer chips, even if we don't recognize the particular chip.
	 */
	data = spi->dev.platform_data;
	if (data && data->type) {
		const struct spi_device_id *plat_id;

		for (i = 0; i < ARRAY_SIZE(m25p_ids) - 1; i++) {
			plat_id = &m25p_ids[i];
			if (strcmp(data->type, plat_id->name))
				continue;
			break;
		}

		if (i < ARRAY_SIZE(m25p_ids) - 1)
			id = plat_id;
		else
			dev_warn(&spi->dev, "unrecognized id %s\n", data->type);
	}

	info = (void *)id->driver_data;

	if (info->jedec_id) {
		const struct spi_device_id *jid;

		jid = jedec_probe(spi);
		if (IS_ERR(jid)) {
			return PTR_ERR(jid);
		} else if (jid != id) {
			/*
			 * JEDEC knows better, so overwrite platform ID. We
			 * can't trust partitions any longer, but we'll let
			 * mtd apply them anyway, since some partitions may be
			 * marked read-only, and we don't want to lose that
			 * information, even if it's not 100% accurate.
			 */
			dev_warn(&spi->dev, "found %s, expected %s\n",
				 jid->name, id->name);
			id = jid;
			info = (void *)jid->driver_data;
		}
	}

	flash = kzalloc(sizeof *flash, GFP_KERNEL);
	if (!flash)
		return -ENOMEM;
	flash->srval = ULONG_MAX;
	flash->wp = false;
	flash->command = kmalloc(MAX_CMD_SIZE + FAST_READ_DUMMY_BYTE, GFP_KERNEL);
	if (!flash->command) {
		kfree(flash);
		return -ENOMEM;
	}

	flash->spi = spi;
	mutex_init(&flash->lock);
	dev_set_drvdata(&spi->dev, flash);

	/*
	 * Atmel, SST and Intel/Numonyx serial flash tend to power
	 * up with the software protection bits set
	 */

	if (JEDEC_MFR(info->jedec_id) == CFI_MFR_ATMEL ||
	    JEDEC_MFR(info->jedec_id) == CFI_MFR_INTEL ||
	    JEDEC_MFR(info->jedec_id) == CFI_MFR_SST) {
		write_enable(flash);
		write_sr(flash, 0);
	}

	if (data && data->name)
		flash->mtd.name = data->name;
	else
		flash->mtd.name = dev_name(&spi->dev);

	flash->mtd.type = MTD_NORFLASH;
	flash->mtd.writesize = 1;
	flash->mtd.flags = MTD_CAP_NORFLASH;
	flash->mtd.size = info->sector_size * info->n_sectors;
	flash->mtd._erase = m25p80_erase;
	flash->mtd._read = m25p80_read;

	/* sst flash chips use AAI word program */
	if (JEDEC_MFR(info->jedec_id) == CFI_MFR_SST)
		flash->mtd._write = sst_write;
	else
		flash->mtd._write = m25p80_write;

#if IS_ENABLED(CONFIG_SPI_TC90431)
	if (data)
		tc90431_spi_data = data->tc90431_spi_data;
	if (diracc && tc90431_spi_data && tc90431_spi_data->dir_read_phys) {
		unsigned long phys = tc90431_spi_data->dir_read_phys;
		if (tc90431_spi_data->dir_read_size < flash->mtd.size) {
			dev_err(&spi->dev,
				"mtd size exceeds direct map size\n");
			return -ENXIO;
		}
		tc90431_spi_data->dir_read_size = flash->mtd.size;
		flash->virt =
			(unsigned long)ioremap_cached(phys, flash->mtd.size);
		if (!flash->virt) {
			dev_err(&spi->dev, "cannot create direct map\n");
			return -ENXIO;
		}
		invalidate_cache_for_spi(flash->virt, flash->mtd.size);
		tc90431_spi_data->dir_max_speed_hz = 0;
		tc90431_spi_data->dir_deassert_time = 0;
		tc90431_spi_data->dir_read_opcode = 0;
		tc90431_spi_data->dir_read_dummy_count = 0;
	}
#endif
	for (i = 0; i < ARRAY_SIZE(m25p_fixup_ids); i++) {
		int ret;
		const struct flash_fixup_info *fixup_info;
		fixup_info = &m25p_fixup_ids[i];
		if (strcmp(id->name, fixup_info->name) == 0) {
			ret = fixup_info->option_func(flash, fixup_info);
			if (ret < 0) {
				dev_err(&spi->dev,
					"%s: failed option operation\n",
					__func__);
				return ret;
			}
#if IS_ENABLED(CONFIG_SPI_TC90431)
			if (!tc90431_spi_data)
				break;
			if (fixup_info->max_speed_hz)
				spi->max_speed_hz = fixup_info->max_speed_hz;
			if (fixup_info->deassert_time)
				tc90431_spi_data->deassert_time =
					fixup_info->deassert_time;
			if (!flash->virt)
				break;
			if (fixup_info->dir_max_speed_hz)
				tc90431_spi_data->dir_max_speed_hz =
					fixup_info->dir_max_speed_hz;
			if (fixup_info->dir_deassert_time)
				tc90431_spi_data->dir_deassert_time =
					fixup_info->dir_deassert_time;
			if (fixup_info->dir_read_opcode)
				tc90431_spi_data->dir_read_opcode =
					fixup_info->dir_read_opcode;
			break;
#endif
		}
	}
	flash->erase_opcode = OPCODE_SE;
	flash->mtd.erasesize = info->sector_size;

	/* prefer "small sector" erase if possible */
	if (!no_4kerase && (info->flags & SECT_4K)) {
		flash->erase_opcode = OPCODE_BE_4K;
		flash->mtd.erasesize = 4096;
	} else {
		flash->erase_opcode = OPCODE_SE;
		flash->mtd.erasesize = info->sector_size;
	}

	if (info->flags & M25P_NO_ERASE)
		flash->mtd.flags |= MTD_NO_ERASE;

	ppdata.of_node = spi->dev.of_node;
	flash->mtd.dev.parent = &spi->dev;
	flash->page_size = info->page_size;
	flash->mtd.writebufsize = flash->page_size;

	if (info->addr_width)
		flash->addr_width = info->addr_width;
	else {
		/* enable 4-byte addressing if the device exceeds 16MiB */
		if (flash->mtd.size > 0x1000000) {
			flash->addr_width = 4;
			set_4byte(flash, info->jedec_id, 1);
		} else
			flash->addr_width = 3;
	}

	dev_info(&spi->dev, "%s (%lld Kbytes)\n", id->name,
			(long long)flash->mtd.size >> 10);

#if IS_ENABLED(CONFIG_SPI_TC90431)
#ifdef CONFIG_M25PXX_USE_FAST_READ
	if (flash->virt) {
		if (!tc90431_spi_data->dir_read_opcode) {
			tc90431_spi_data->dir_read_opcode =
				OPCODE_FAST_READ_SINGLE;
			tc90431_spi_data->dir_read_dummy_count = 1;
		}
	}
#endif
	if (tc90431_spi_data) {
		int ret;
		if (!tc90431_spi_data->dir_read_dummy_count) {
			if (tc90431_spi_data->dir_read_opcode ==
			    OPCODE_FAST_READ_QUAD_IO)
				tc90431_spi_data->dir_read_dummy_count = 3;
			else
				tc90431_spi_data->dir_read_dummy_count = 1;
		}
		/* if not specified, use program-access timings */
		if (!tc90431_spi_data->dir_deassert_time)
			tc90431_spi_data->dir_deassert_time =
				tc90431_spi_data->deassert_time;
		if (!tc90431_spi_data->dir_max_speed_hz)
			tc90431_spi_data->dir_max_speed_hz = spi->max_speed_hz;
		/* update settings */
		ret = spi_setup(spi);
		if (ret) {
			dev_err(&spi->dev, "setup failed.\n");
			return ret;
		}
	}
#endif
	pr_debug("mtd .name = %s, .size = 0x%llx (%lldMiB) "
			".erasesize = 0x%.8x (%uKiB) .numeraseregions = %d\n",
		flash->mtd.name,
		(long long)flash->mtd.size, (long long)(flash->mtd.size >> 20),
		flash->mtd.erasesize, flash->mtd.erasesize / 1024,
		flash->mtd.numeraseregions);

	if (flash->mtd.numeraseregions)
		for (i = 0; i < flash->mtd.numeraseregions; i++)
			pr_debug("mtd.eraseregions[%d] = { .offset = 0x%llx, "
				".erasesize = 0x%.8x (%uKiB), "
				".numblocks = %d }\n",
				i, (long long)flash->mtd.eraseregions[i].offset,
				flash->mtd.eraseregions[i].erasesize,
				flash->mtd.eraseregions[i].erasesize / 1024,
				flash->mtd.eraseregions[i].numblocks);


	/* partitions should match sector boundaries; and it may be good to
	 * use readonly partitions for writeprotected sectors (BP2..BP0).
	 */
	return mtd_device_parse_register(&flash->mtd, NULL, &ppdata,
			data ? data->parts : NULL,
			data ? data->nr_parts : 0);
}


static int __devexit m25p_remove(struct spi_device *spi)
{
	struct m25p	*flash = dev_get_drvdata(&spi->dev);
	int		status;

#if IS_ENABLED(CONFIG_SPI_TC90431)
	if (flash->virt)
		iounmap((void __iomem *)flash->virt);
#endif
	/* Clean up MTD stuff. */
	status = mtd_device_unregister(&flash->mtd);
	if (status == 0) {
		kfree(flash->command);
		kfree(flash);
	}
	return 0;
}


static struct spi_driver m25p80_driver = {
	.driver = {
		.name	= "m25p80",
		.owner	= THIS_MODULE,
	},
	.id_table	= m25p_ids,
	.probe	= m25p_probe,
	.remove	= __devexit_p(m25p_remove),

	/* REVISIT: many of these chips have deep power-down modes, which
	 * should clearly be entered on suspend() to minimize power use.
	 * And also when they're otherwise idle...
	 */
};

module_spi_driver(m25p80_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mike Lavender");
MODULE_DESCRIPTION("MTD SPI driver for ST M25Pxx flash chips");
