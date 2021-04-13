/*
 * TOSHIBA TC90431 HAMMING NAND controller driver
 *
 * Copyright (C) 2010 Toshiba Corporation
 * (C) Copyright TOSHIBA CORPORATION
 *      SEMICONDUCTOR & STORAGE PRODUCTS COMPANY 2013
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 */

#include <linux/init.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/nand.h>
#include <linux/mtd/nand_ecc.h>
#include <linux/mtd/partitions.h>
#include <linux/io.h>
#include <linux/device.h>
#include <linux/clk.h>
#include <linux/err.h>
#include <linux/pm_runtime.h>
#include <mach/platform.h>
#ifdef CONFIG_OF
#include <linux/of.h>
#endif/*CONFIG_OF*/
#include <linux/crc32.h>
#include <asm/mach/map.h>

#define DRV_DEVNAME "tc90431_nand2"
#undef  CONFIG_TC90431_HAM_NAND_BIT_DEBUG

#define ndwritel(val, addr)	__raw_writel(val, addr)
#define ndreadl(addr)		__raw_readl(addr)

/* Status (Read only)*/
#define TC90431_HAM_STATUS_RAWECCINTST		(1 << 11)
#define TC90431_HAM_STATUS_ECCINTST		(1 << 9)
#define TC90431_HAM_STATUS_ECCINTEN		(1 << 7)
#define TC90431_HAM_STATUS_RAWINTST		(1 << 5)
#define TC90431_HAM_STATUS_INTST		(1 << 3)
#define TC90431_HAM_STATUS_INTEN		(1 << 1)
#define TC90431_HAM_STATUS_LPWR			(1 << 0)

/* Set Config (Write only)*/
#define TC90431_HAM_SETCONFIG_ECCINTEN(x)	((x) << 5)
#define TC90431_HAM_SETCONFIG_LPWRREQ		(1 << 2)
#define TC90431_HAM_SETCONFIG_INTEN(x)		((x) << 0)

/* Clr Config (Write only) */
#define TC90431_HAM_CLRCONFIG_ECCINTDIS(x)	((x) << 5)
#define TC90431_HAM_CLRCONFIG_INTCLR(x)	((x) << 3)
#define TC90431_HAM_CLRCONFIG_LPWREXIT	(1 << 2)
#define TC90431_HAM_CLRCONFIG_INTDIS(x)	((x) << 0)

/* Direct Command (Write only) */
#define TC90431_HAM_DIRECTCMD_CMDTYPE(x)	((x) << 21)

/* Set Cycles (Write only) */
#define TC90431_HAM_SETCYCLES_TRR(x)		((x) << 20)
#define TC90431_HAM_SETCYCLES_TAR(x)		((x) << 17)
#define TC90431_HAM_SETCYCLES_TCLR(x)		((x) << 14)
#define TC90431_HAM_SETCYCLES_TWP(x)		((x) << 11)
#define TC90431_HAM_SETCYCLES_TREA(x)		((x) << 8)
#define TC90431_HAM_SETCYCLES_TWC(x)		((x) << 4)
#define TC90431_HAM_SETCYCLES_TRC(x)		((x) << 0)

/* Set Opmode (Write only) */
#define TC90431_HAM_SETOPMODE_MW(x)		((x) << 0)

/* Cycles0 (Read only) */
#define TC90431_HAM_CYCLES0_TRR		(0xF << 20)
#define TC90431_HAM_CYCLES0_TAR		(0x7 << 17)
#define TC90431_HAM_CYCLES0_TCLR		(0x7 << 14)
#define TC90431_HAM_CYCLES0_TWP		(0x7 << 10)
#define TC90431_HAM_CYCLES0_TREA		(0x7 << 8)
#define TC90431_HAM_CYCLES0_TWC		(0xF << 4)
#define TC90431_HAM_CYCLES0_TRC		(0xF << 0)

/* Opmode0 (Read only) */
#define TC90431_HAM_OPMODE0_MW		(0x3 << 0)

/* ECC status (Read only) */
#define TC90431_HAM_ECCSTATUS_READ		(0x1F << 25)
#define TC90431_HAM_ECCSTATUS_CAN_CRCT		(0x1F << 20)
#define TC90431_HAM_ECCSTATUS_FAIL		(0x0F << 15)
#define TC90431_HAM_ECCSTATUS_VAL_VALID	(0x1F << 10)
#define TC90431_HAM_ECCSTATUS_RD_NOT_WR	(0x1  << 9)
#define TC90431_HAM_ECCSTATUS_LAST		(0x3  << 7)
#define TC90431_HAM_ECCSTATUS_STATUS		(0x1  << 6)
#define TC90431_HAM_ECCSTATUS_RAW_INTST	(0x3F << 0)

/* ECC Configuration (Rd/Wr) */
#define TC90431_HAM_ECCMEMCFG_EXBLOCK_SIZE(x)	((x) << 11)
#define TC90431_HAM_ECCMEMCFG_EXBLOCK_EN(x)	((x) << 10)
#define TC90431_HAM_ECCMEMCFG_INT_ABORT(x)	((x) << 9)
#define TC90431_HAM_ECCMEMCFG_INT_PASS(x)	((x) << 8)
#define TC90431_HAM_ECCMEMCFG_IGNORE_ADD_EIGHT	(0x1 << 7)
#define TC90431_HAM_ECCMEMCFG_JUMP(x)		((x) << 5)
#define TC90431_HAM_ECCMEMCFG_MODE(x)		((x) << 2)
#define TC90431_HAM_ECCMEMCFG_PAGESIZE(x)	((x) << 0)
#define TC90431_HAM_ECCMEMCFG_RESERVE		(0x00000010)

/* ECC Command1 (Rd/Wr) */
#define TC90431_HAM_ECCMEMCMD1_RD_END_VAL		(0x1  << 24)
#define TC90431_HAM_ECCMEMCMD1_RD_END			(0xFF << 16)
#define TC90431_HAM_ECCMEMCMD1_RD_CMD			(0xFF << 8)
#define TC90431_HAM_ECCMEMCMD1_WR_CMD			(0xFF << 0)

/* ECC Command2 (Rd/Wr) */
#define TC90431_HAM_ECCMEMCMD2_RD_CHANGE_END_VAL	(0x1  << 24)
#define TC90431_HAM_ECCMEMCMD2_RD_CHANGE_END		(0xFF << 16)
#define TC90431_HAM_ECCMEMCMD2_RD_CHANGE		(0xFF << 8)
#define TC90431_HAM_ECCMEMCMD2_WR_CHANGE		(0xFF << 0)

/* ECC Value 0-4 */
#define TC90431_HAM_ECCVALUE_INT		(0x1 << 31)
#define TC90431_HAM_ECCVALUE_VALID		(0x1 << 30)
#define TC90431_HAM_ECCVALUE_READ		(0x1 << 29)
#define TC90431_HAM_ECCVALUE_FAIL		(0x1 << 28)
#define TC90431_HAM_ECCVALUE_CORRECT		(0x1 << 27)
#define TC90431_HAM_ECCVALUE_WRITE		(0x00FFFFFF << 0)
#define TC90431_HAM_ECCVALUE_READ_BYTE		(0x00FFFFF8)
#define TC90431_HAM_ECCVALUE_READ_BIT		(0x7 << 0)

/* Command Phase set */
#define TC90431_HAM_CMD_CHIP_ADDR		((0x00) << 24)
#define TC90431_HAM_CMD_ADDCYCLE(x)		((x) << 21)
#define TC90431_HAM_CMD_END_CMD_VAL(x)		((x) << 20)
#define TC90431_HAM_CMD_19			((0x0) << 19)
#define TC90431_HAM_CMD_END_CMD(x)		((x) << 11)
#define TC90431_HAM_CMD_START_CMD(x)		((x) << 3)

/* Data Phase set */
#define TC90431_HAM_DATA_CHIP_ADDR		((0x00) << 24)
#define TC90431_HAM_DATA_CLEAR_CS(x)		((x) << 21)
#define TC90431_HAM_DATA_END_CMD_VAL(x)	((x) << 20)
#define TC90431_HAM_DATA_19			((0x1) << 19)
#define TC90431_HAM_DATA_END_CMD(x)		((x) << 11)
#define TC90431_HAM_DATA_ECC_LAST(x)		(host->ecc_val == ECC_ON ? \
						(x) << 10 : 0)
#define GET_RAWINTST_TIMEOUT		1000
#define GET_STATUS_TIMEOUT		1000

#define ECC_OFF				0x0
#define ECC_ON				0x2

#define LARGE_PAGE			0x1
#define SMALL_PAGE			0x0

#define MACRONIX_MX30LF1G08_TIMING \
	(TC90431_HAM_SETCYCLES_TRR(0x2) | \
	 TC90431_HAM_SETCYCLES_TAR(0x2) | \
	 TC90431_HAM_SETCYCLES_TCLR(0x2) | \
	 TC90431_HAM_SETCYCLES_TWP(0x2) | \
	 TC90431_HAM_SETCYCLES_TREA(0x3) | \
	 TC90431_HAM_SETCYCLES_TWC(0x4) | \
	 TC90431_HAM_SETCYCLES_TRC(0x5))
#define TOSHIBA_TC58DVG02D5_TIMING /* TC58BVG0S3 */ \
	(TC90431_HAM_SETCYCLES_TRR(0x2) | \
	 TC90431_HAM_SETCYCLES_TAR(0x1) | \
	 TC90431_HAM_SETCYCLES_TCLR(0x1) | \
	 TC90431_HAM_SETCYCLES_TWP(0x2) | \
	 TC90431_HAM_SETCYCLES_TREA(0x2) | \
	 TC90431_HAM_SETCYCLES_TWC(0x4) | \
	 TC90431_HAM_SETCYCLES_TRC(0x4))
#ifdef CONFIG_NAND_CHIP_MACRONIX_MX30LF1G08
#define DEFAULT_AC_TIMING MACRONIX_MX30LF1G08_TIMING
#endif
#ifdef CONFIG_NAND_CHIP_TOSHIBA_TC58DVG02D5
#define DEFAULT_AC_TIMING TOSHIBA_TC58DVG02D5_TIMING
#endif

struct tc90431_ham_nand_regs {
	u32 status;
	u32 reserved00;
	u32 setconfig;
	u32 clrconfig;
	u32 directcmd;
	u32 setcycles;
	u32 setopmode;
	u32 reserved01[0x39];
	u32 cycles0;
	u32 opmode0;
	u32 reserved02[0x7E];
	u32 ecc_status;
	u32 ecc_memcfg;
	u32 ecc_memcommand1;
	u32 ecc_memcommand2;
	u32 reserved03[0x2];
	u32 ecc_value[5];
	u32 reserved04[0x335];
};

struct tc90431_ham_nand_chip_set {
	u32 full_cycle;
	u32 erase_cycle;
	u32 page_size;
	u32 column_val;
	u32 exblocksize;
	int ecc_count;
	u32 ac_timing;
	int autoset_enable;
};

struct nand_ac_timing_set {
	int man_id;
	int dev_id;
	u32 ac_timing;
};

static struct nand_ac_timing_set man_ac_chip[] = {
	{NAND_MFR_MACRONIX, 0xF1, MACRONIX_MX30LF1G08_TIMING},
	{NAND_MFR_TOSHIBA, 0xF1, TOSHIBA_TC58DVG02D5_TIMING},
	{ 0x0, 0x0, 0x00FFFFFF},
	{ 0x100,}
};

static struct tc90431_ham_nand_chip_set chip_select = {
#ifdef DEFAULT_AC_TIMING
	.ac_timing = DEFAULT_AC_TIMING,
	.autoset_enable = 0
#else
	.ac_timing = 0x00FFFFFF,
	.autoset_enable = 1
#endif
};

struct tc90431_ham_nand_host {
	struct mtd_info mtd;
	struct nand_chip nand;
	struct tc90431_ham_nand_regs __iomem *regs;	/* NAND Register set */
	struct tc90431_ham_nand_chip_set *chip_set;
	int read_byte_flag;
	int page_addr;
	int ecc_val;
	int match_oob_flag;
	u32 match_flag;
	u32 read_byte_buf;
	u32 command;
	u32 oob_read_flag;
	u32 oob_write_flag;

	unsigned long iobase;
	struct resource *ioarea;
	struct device *dev;
	struct clk *clk;
};
static void __iomem *devbase;
static struct resource *devarea;

static struct nand_ecclayout large_nand_oob_32 = {
	.eccbytes = 12,
	.eccpos = {
		   32, 33, 34,
		   35, 36, 37,
		   38, 39, 40,
		   41, 42, 43},
	.oobfree = {
		    {.offset = 2,
		     .length = 29}
		    }
};

static struct nand_ecclayout small_nand_oob_8 = {
	.eccbytes = 3,
	.eccpos = {
		   8, 9, 10},
	.oobfree = {
		    {.offset = 0,
		     .length = 4},
		    }
};

static int tc90431_ham_nand_wait_op_done(struct tc90431_ham_nand_host *host);
static int tc90431_ham_nand_set_chip(struct mtd_info *mtd);

static void tc90431_ham_nand_set_init(struct tc90431_ham_nand_host *host)
{
	struct tc90431_ham_nand_regs __iomem *regs =
	   (struct tc90431_ham_nand_regs __iomem *)host->iobase;
#ifdef CONFIG_TC90431_HAM_NAND_DEBUG
	u32 reg;
#endif
	u32 set_config = 0;

	u32 set_clrconfig = TC90431_HAM_CLRCONFIG_ECCINTDIS(0x1)
	    | TC90431_HAM_CLRCONFIG_INTDIS(0x1);
	u32 set_cycles = 0;
	u32 set_opmode = 0;
	u32 set_directcmd = TC90431_HAM_DIRECTCMD_CMDTYPE(0x2);

	set_cycles = host->chip_set->ac_timing;

	ndwritel(set_config, &regs->setconfig);
	ndwritel(set_clrconfig, &regs->clrconfig);
	ndwritel(set_cycles, &regs->setcycles);
	ndwritel(set_opmode, &regs->setopmode);
	/* update cycles0 and opmode0) */
	ndwritel(set_directcmd, &regs->directcmd);

#ifdef CONFIG_TC90431_HAM_NAND_DEBUG
	reg = ndreadl(&regs->opmode0);
	pr_warn("opmode0 = 0x%08x\n", reg);
	reg = ndreadl(&regs->cycles0);
	pr_warn("cycles0 = 0x%08x\n", reg);
#endif
}

static void tc90431_ham_nand_set_ecc(struct tc90431_ham_nand_host *host,
				      char change)
{
	struct tc90431_ham_nand_regs __iomem *regs =
	   (struct tc90431_ham_nand_regs __iomem *)host->iobase;

	u32 set_eccmemcfg = 0;

	if (host->nand.ecc.mode == NAND_ECC_BENAND) {
		/* always ECC disable when BENAND */
		host->ecc_val = ECC_OFF;
		goto exit;
	}

	set_eccmemcfg =
	    TC90431_HAM_ECCMEMCFG_RESERVE |
	    TC90431_HAM_ECCMEMCFG_EXBLOCK_EN(0x1) |
	    TC90431_HAM_ECCMEMCFG_INT_ABORT(0x0) |
	    TC90431_HAM_ECCMEMCFG_INT_PASS(0x0) |
	    TC90431_HAM_ECCMEMCFG_JUMP(0x0);

	if (host->chip_set->page_size != LARGE_PAGE) {
		set_eccmemcfg |=
		    TC90431_HAM_ECCMEMCFG_EXBLOCK_SIZE(0x1) |
		    TC90431_HAM_ECCMEMCFG_IGNORE_ADD_EIGHT |
		    TC90431_HAM_ECCMEMCFG_PAGESIZE(0x01);
	} else {
		set_eccmemcfg |=
		    TC90431_HAM_ECCMEMCFG_EXBLOCK_SIZE(0x3) |
		    TC90431_HAM_ECCMEMCFG_PAGESIZE(0x03);
	}
	set_eccmemcfg |= TC90431_HAM_ECCMEMCFG_MODE(change);

 exit:

#ifdef CONFIG_TC90431_HAM_NAND_DEBUG
	pr_warn("set_eccmemcfg = 0x%08x\n", set_eccmemcfg);
#endif
	ndwritel(set_eccmemcfg, &regs->ecc_memcfg);
}

static void tc90431_ham_nand_pre_command(unsigned int command,
					  struct tc90431_ham_nand_host *host)
{
	u32 tc90431_ham_addr;
	u32 full_cycle;

	full_cycle = host->chip_set->full_cycle;

	tc90431_ham_addr = TC90431_HAM_CMD_CHIP_ADDR |
	    TC90431_HAM_CMD_ADDCYCLE(full_cycle) |
	    TC90431_HAM_CMD_END_CMD_VAL(0x0) | TC90431_HAM_CMD_19 |
	    TC90431_HAM_CMD_END_CMD(0x0) | TC90431_HAM_CMD_START_CMD(command);
	ndwritel(0x0, tc90431_ham_addr + devbase);
	tc90431_ham_nand_wait_op_done(host);
}

static void tc90431_ham_nand_write_buf(struct mtd_info *mtd,
					const u8 *buf, int len)
{
	struct nand_chip *chip = mtd->priv;
	struct tc90431_ham_nand_host *host = chip->priv;
	u32 set_data, tc90431_ham_addr;
	int i;

	if (len != mtd->oobsize) {
		tc90431_ham_addr = TC90431_HAM_DATA_CHIP_ADDR |
		    TC90431_HAM_DATA_CLEAR_CS(0x1) |
		    TC90431_HAM_DATA_END_CMD_VAL(0x0) | TC90431_HAM_DATA_19 |
		    TC90431_HAM_DATA_END_CMD(NAND_CMD_PAGEPROG) |
		    TC90431_HAM_DATA_ECC_LAST(0x0);

		for (i = 0; i < len; i += 4) {
			set_data = buf[i] + (buf[i + 1] << 8) +
			    (buf[i + 2] << 16) + (buf[i + 3] << 24);
			ndwritel(set_data, tc90431_ham_addr + devbase);
		}

		host->oob_write_flag = 1;
	} else {
		tc90431_ham_addr = TC90431_HAM_DATA_CHIP_ADDR |
		    TC90431_HAM_DATA_CLEAR_CS(0x1) |
		    TC90431_HAM_DATA_END_CMD_VAL(0x0) | TC90431_HAM_DATA_19 |
		    TC90431_HAM_DATA_END_CMD(NAND_CMD_PAGEPROG) |
		    TC90431_HAM_DATA_ECC_LAST(0x0);


		for (i = 0; i < (len - 4); i += 4) {
			set_data = buf[i] + (buf[i + 1] << 8) +
			    (buf[i + 2] << 16) + (buf[i + 3] << 24);
			ndwritel(set_data, tc90431_ham_addr + devbase);
		}

		tc90431_ham_addr =
		    TC90431_HAM_DATA_CHIP_ADDR |
		    TC90431_HAM_DATA_CLEAR_CS(0x1) |
		    TC90431_HAM_DATA_END_CMD_VAL(0x1) |
		    TC90431_HAM_DATA_19 |
		    TC90431_HAM_DATA_END_CMD(NAND_CMD_PAGEPROG) |
		    TC90431_HAM_DATA_ECC_LAST(0x0);
		set_data =
		    buf[len - 4] + (buf[len - 3] << 8) +
		    (buf[len - 2] << 16) + (buf[len - 1] << 24);
		ndwritel(set_data, tc90431_ham_addr + devbase);

		host->oob_write_flag = 0;
		tc90431_ham_nand_wait_op_done(host);
	}
}

static int tc90431_ham_nand_write_extra_buf(struct mtd_info *mtd,
					const u8 *buf, int len)
{
	struct nand_chip *chip = mtd->priv;
	struct tc90431_ham_nand_host *host = chip->priv;
	u32 set_data, tc90431_ham_addr;
	int i;

	tc90431_ham_addr = TC90431_HAM_DATA_CHIP_ADDR |
	    TC90431_HAM_DATA_CLEAR_CS(0x1) |
	    TC90431_HAM_DATA_END_CMD_VAL(0x0) | TC90431_HAM_DATA_19 |
	    TC90431_HAM_DATA_END_CMD(NAND_CMD_PAGEPROG) |
	    TC90431_HAM_DATA_ECC_LAST(0x0);

	for (i = 0; i < (host->chip_set->exblocksize - 4); i += 4) {
		set_data = buf[i] + (buf[i + 1] << 8) +
		    (buf[i + 2] << 16) + (buf[i + 3] << 24);
		ndwritel(set_data, tc90431_ham_addr + devbase);
	}

	tc90431_ham_addr = TC90431_HAM_DATA_CHIP_ADDR |
	    TC90431_HAM_DATA_CLEAR_CS(0x1) |
	    TC90431_HAM_DATA_END_CMD_VAL(0x1) | TC90431_HAM_DATA_19 |
	    TC90431_HAM_DATA_END_CMD(NAND_CMD_PAGEPROG) |
	    TC90431_HAM_DATA_ECC_LAST(0x1);

	set_data = buf[i] + (buf[i + 1] << 8) +
		    (buf[i + 2] << 16) + (buf[i + 3] << 24);
	ndwritel(set_data, tc90431_ham_addr + devbase);

	host->oob_write_flag = 0;
	return tc90431_ham_nand_wait_op_done(host);
}

static void tc90431_ham_nand_read_buf(struct mtd_info *mtd, u8 *buf, int len)
{
	struct nand_chip *chip = mtd->priv;
	struct tc90431_ham_nand_host *host = chip->priv;
	u32 tc90431_ham_addr;
	u32 *buf32;
	int i;

	buf32 = (u32 *)buf;

	/* READ Data Phase */
	tc90431_ham_addr = TC90431_HAM_DATA_CHIP_ADDR |
	    TC90431_HAM_DATA_CLEAR_CS(0x1) |
	    TC90431_HAM_DATA_END_CMD_VAL(0x0) | TC90431_HAM_DATA_19 |
	    TC90431_HAM_DATA_END_CMD(0x00) | TC90431_HAM_DATA_ECC_LAST(0x0);

	if (len != mtd->oobsize) {
		for (i = 0; i < len / 4; i++) {
			buf32[i] = ndreadl(tc90431_ham_addr + devbase);
			if (host->match_flag == 0xFFFFFFFF)
				host->match_flag &= buf32[i];
#ifdef CONFIG_TC90431_HAM_NAND_DEBUG
			pr_warn("%s: Read buf32[%d] = 0x%08x\n",
				__func__, i, buf32[i]);
#endif
		}
		host->oob_read_flag = 1;
		return;
	}

	if (host->oob_read_flag != 1) {
		/* READOOB */
		for (i = 0; i < len / 4; i++) {
			buf32[i] = ndreadl(tc90431_ham_addr + devbase);
#ifdef CONFIG_TC90431_HAM_NAND_DEBUG
			pr_warn("%s: ReadOOB buf32[%d] = 0x%08x\n",
				__func__, i, buf32[i]);
#endif
			if ((buf32[i] != 0xFFFFFFFF) &&
			    (host->match_oob_flag != 1))
				host->match_oob_flag = 1;
		}
	} else {
		/* Read Extra Block */
		for (i = 0; i < (host->chip_set->exblocksize - 4) / 4; i++) {
			buf32[i] = ndreadl(tc90431_ham_addr + devbase);
#ifdef CONFIG_TC90431_HAM_NAND_DEBUG
			pr_warn("%s: ReadEX buf32[%d] = 0x%08x\n",
				__func__, i, buf32[i]);
#endif
		}

		tc90431_ham_addr = TC90431_HAM_DATA_CHIP_ADDR |
		    TC90431_HAM_DATA_CLEAR_CS(0x1) |
		    TC90431_HAM_DATA_END_CMD_VAL(0x0) | TC90431_HAM_DATA_19 |
		    TC90431_HAM_DATA_END_CMD(0x00) |
		    TC90431_HAM_DATA_ECC_LAST(0x1);

		buf32[i] = ndreadl(tc90431_ham_addr + devbase);
	}

	host->oob_read_flag = 0;
}

static u8 tc90431_ham_nand_read_byte(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd->priv;
	struct tc90431_ham_nand_host *host = chip->priv;
	u32 tc90431_ham_addr, tmp_buf;
	static int i;
	u8 buf;

	i = host->read_byte_flag;

	if (i == 0) {
		/* Data Phase LAST */
		tc90431_ham_addr = TC90431_HAM_DATA_CHIP_ADDR |
		    TC90431_HAM_DATA_CLEAR_CS(0x1) |
		    TC90431_HAM_DATA_END_CMD_VAL(0x0) | TC90431_HAM_DATA_19 |
		    TC90431_HAM_DATA_END_CMD(0x00) |
		    TC90431_HAM_DATA_ECC_LAST(0x0);

		tmp_buf = ndreadl(tc90431_ham_addr + devbase);
		host->read_byte_buf = tmp_buf;
	}

	buf = (u8)((host->read_byte_buf >> (8 * i)) & 0xFF);
	host->read_byte_flag++;
	if (host->read_byte_flag == 4)
		host->read_byte_flag = 0;

	return buf;
}

static int tc90431_ham_nand_biterr_check(struct mtd_info *mtd, uint8_t *buf,
						int size)
{
	struct nand_chip *chip = mtd->priv;
	struct tc90431_ham_nand_host *host = chip->priv;
	u32 *buf32, ret;
	int tmp_i[4] = {-1, -1, -1, -1};
	int i, j, t, check, oob_read, len;

	buf32 = (u32 *)buf;
	len = (size / 0x200);

	/* init */
	oob_read = 0;
	for (i = 0; i < len; i++)
		tmp_i[i] = -1;

	j = 0;
	for (t = 0; t < len; t++) {
		check = 0;
		for (i = (t * 128); i < ((t+1) * 128); i++) {
			if (buf32[i] != 0xFFFFFFFF) {
#ifdef CONFIG_TC90431_HAM_NAND_BIT_DEBUG
				pr_warn("biterr buf32[%d] = 0x%08x\n",
					i, buf32[i]);
#endif
				check += 1;
				if (check > 1)
					return 1;
				tmp_i[j] = i;
				j++;
			}
		}
	}

	t = 0;
	while ((tmp_i[t] != -1) && (t < 4)) {
		i = tmp_i[t];

		ret = hweight32((~buf32[i]));

		if (ret > 1)
			return 1;

		if (oob_read != 1) {
			host->match_oob_flag = 0;
			chip->cmdfunc(mtd, NAND_CMD_READOOB,
						0, host->page_addr);
			chip->read_buf(mtd, chip->oob_poi, mtd->oobsize);
			oob_read = 1;
		}

#ifdef CONFIG_TC90431_HAM_NAND_BIT_DEBUG
		pr_warn("\nmatch_oob_flag = %0d\n",
			host->match_oob_flag);
#endif
		if (host->match_oob_flag != 0)
			return 1;

		buf32[i] = 0xFFFFFFFF;
#ifdef CONFIG_TC90431_HAM_NAND_BIT_DEBUG
		pr_warn("\nafter biterr buf32[%d] = 0x%08x\n", i, buf32[i]);
#endif
		mtd->ecc_stats.corrected++;
		t++;
	}
	return 0;
}

static int tc90431_ham_nand_read_page_hwecc(struct mtd_info *mtd,
					     struct nand_chip *chip,
					     uint8_t *buf, int page)
{
	struct tc90431_ham_nand_host *host = chip->priv;
	struct tc90431_ham_nand_regs __iomem *regs =
	   (struct tc90431_ham_nand_regs __iomem *)host->iobase;
	u32 ecc_bit, ecc_byte, reg;
	uint8_t *buf_tmp, byte;
	int i, tmp, ret;
	unsigned long timeout;

	buf_tmp = buf;
	chip->read_buf(mtd, buf, mtd->writesize);
	chip->read_buf(mtd, chip->oob_poi, mtd->oobsize);
	wmb(); /* barrier */

	timeout = jiffies + msecs_to_jiffies(GET_STATUS_TIMEOUT);
	do {
		reg = ndreadl(&regs->ecc_status);
		if (time_after_eq(jiffies, timeout)) {
			pr_warn(DRV_DEVNAME
				":%s: ECC STATUS timeout\n", __func__);
			return -ETIMEDOUT;
		}
#ifdef CONFIG_TC90431_HAM_NAND_DEBUG
		pr_warn("read ecc_status = 0x%08x\n", reg);
#endif
	} while ((reg & TC90431_HAM_ECCSTATUS_STATUS) != 0);

	reg = ndreadl(&regs->ecc_status);
	ndwritel(TC90431_HAM_ECCSTATUS_RAW_INTST, &regs->ecc_status);
	tmp = ((reg & TC90431_HAM_ECCSTATUS_LAST) >> 0x7);
	switch (tmp) {
	case 1:
	case 2:
	case 3:
		pr_warn("%s: ECC STATUS ERR = %02x\n", __func__, tmp);
		return -EIO;

	default:
		break;
	}
	if (host->match_flag == 0xFFFFFFFF)
		return 0;
	host->match_flag = 0xFFFFFFFF;

	/* ECC bit correct check */
	if (reg & TC90431_HAM_ECCSTATUS_FAIL) {
		ret = tc90431_ham_nand_biterr_check(mtd, buf_tmp,
					mtd->writesize);

		if (ret != 1) {
#ifdef CONFIG_TC90431_HAM_NAND_DEBUG
			pr_warn("all 0xff 1bit err correct.\n");
#endif
			return 0;
		}
	}

	for (i = 0; i < host->chip_set->ecc_count; i++) {
		reg = ndreadl(&regs->ecc_value[i]);
		if (reg & TC90431_HAM_ECCVALUE_FAIL) {
			if (!(reg & TC90431_HAM_ECCVALUE_CORRECT)) {
				pr_warn("%s: ecc value[%d] correct err\n",
					__func__, i);
				mtd->ecc_stats.failed++;
				continue;
			}
			buf_tmp = buf + (0x200 * i);

			ecc_bit = reg & TC90431_HAM_ECCVALUE_READ_BIT;
			ecc_byte = ((reg &
				     (TC90431_HAM_ECCVALUE_READ_BYTE)) >> 3);
#ifdef CONFIG_TC90431_HAM_NAND_DEBUG
			pr_warn("ecc_value[%d] = 0x%08x\n", i, reg);
			pr_warn("ecc_byte = 0x%x\n", ecc_byte);
			pr_warn("ecc_bit = 0x%x\n", ecc_bit);
			pr_warn("Base buf = %p\n", buf);
			pr_warn("before:%p = 0x%02x\n",
				&buf_tmp[ecc_byte], buf_tmp[ecc_byte]);
#endif
			byte = buf_tmp[ecc_byte];
			byte =
			    ((byte & ~(1 << ecc_bit)) |
			     ((~byte) & (1 << ecc_bit)));
			buf_tmp[ecc_byte] = byte;
#ifdef CONFIG_TC90431_HAM_NAND_DEBUG
			pr_warn("after:%p = 0x%02x\n",
				&buf_tmp[ecc_byte], buf_tmp[ecc_byte]);
#endif

			mtd->ecc_stats.corrected++;
		}
	}

	return 0;
}

static int tc90431_ham_nand_write_page_hwecc(struct mtd_info *mtd,
					       struct nand_chip *chip,
					       const uint8_t *buf)
{
	struct tc90431_ham_nand_host *host = chip->priv;
	int ret = 0;

	chip->write_buf(mtd, buf, mtd->writesize);
	if (host->oob_write_flag != 0)
		ret = tc90431_ham_nand_write_extra_buf(mtd, chip->oob_poi,
							mtd->oobsize);
	else
		chip->write_buf(mtd, chip->oob_poi, mtd->oobsize);

	return ret;
}

static int tc90431_ham_nand_verify_buf(struct mtd_info *mtd,
					const u_char *buf, int len)
{
	struct nand_chip *chip = mtd->priv;
	struct tc90431_ham_nand_host *host = chip->priv;
	u32 tc90431_ham_addr;
	u32 *buf32;
	int i;

	buf32 = (u32 *)buf;

	/* READ Data Phase */
	tc90431_ham_addr = TC90431_HAM_DATA_CHIP_ADDR |
	    TC90431_HAM_DATA_CLEAR_CS(0x1) |
	    TC90431_HAM_DATA_END_CMD_VAL(0x0) | TC90431_HAM_DATA_19 |
	    TC90431_HAM_DATA_END_CMD(0x00) | TC90431_HAM_DATA_ECC_LAST(0x0);

	for (i = 0; i < len / 4; i++) {
		if (buf32[i] != ndreadl(tc90431_ham_addr + devbase))
			return -EFAULT;
	}
	return 0;
}

static int tc90431_ham_nand_wait_op_done(struct tc90431_ham_nand_host *host)
{
	struct tc90431_ham_nand_regs __iomem *regs =
	   (struct tc90431_ham_nand_regs __iomem *)host->iobase;
	unsigned long timeout;
	u32 set_clrconfig =
	    TC90431_HAM_CLRCONFIG_INTCLR(0x1) |
	    TC90431_HAM_CLRCONFIG_ECCINTDIS(0x1) |
	    TC90431_HAM_CLRCONFIG_INTDIS(0x1);
	int reg = 0;

	timeout = jiffies + msecs_to_jiffies(GET_RAWINTST_TIMEOUT);
	do {
		reg = ndreadl(&regs->status);
		if (time_after_eq(jiffies, timeout)) {
			pr_warn(DRV_DEVNAME
				":%s: RAWINTST timeout\n", __func__);
			ndwritel(set_clrconfig, &regs->clrconfig);
			return -ETIMEDOUT;
		}
	} while (!(reg & TC90431_HAM_STATUS_RAWINTST));
	ndwritel(set_clrconfig, &regs->clrconfig);
	return 0;
}

static void tc90431_ham_nand_select_chip(struct mtd_info *mtd, int chip)
{
	return;
}

static int tc90431_ham_nand_dev_ready(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd->priv;
	struct tc90431_ham_nand_host *host = chip->priv;
	u32 tc90431_ham_addr, set_addr;
	u8 status;

	tc90431_ham_addr = TC90431_HAM_CMD_CHIP_ADDR |
	    TC90431_HAM_CMD_ADDCYCLE(0x0) |
	    TC90431_HAM_CMD_END_CMD_VAL(0x0) | TC90431_HAM_CMD_19 |
	    TC90431_HAM_CMD_END_CMD(0x0) |
	    TC90431_HAM_CMD_START_CMD(NAND_CMD_STATUS);

	set_addr = 0x0;
	ndwritel(set_addr, tc90431_ham_addr + devbase);
	host->read_byte_flag = 0;

	status = tc90431_ham_nand_read_byte(mtd);

	if (status & NAND_STATUS_READY)
		return 1;	/* Ready */
	return 0;		/* Busy */
}

static int tc90431_ham_nand_waitfunc(struct mtd_info *mtd,
				      struct nand_chip *chip)
{
	struct tc90431_ham_nand_host *host = chip->priv;
	u32 tc90431_ham_addr, set_addr;
	u8 status;

	tc90431_ham_addr = TC90431_HAM_CMD_CHIP_ADDR |
	    TC90431_HAM_CMD_ADDCYCLE(0x0) |
	    TC90431_HAM_CMD_END_CMD_VAL(0x0) | TC90431_HAM_CMD_19 |
	    TC90431_HAM_CMD_END_CMD(0x0) |
	    TC90431_HAM_CMD_START_CMD(NAND_CMD_STATUS);

	set_addr = 0x0;
	ndwritel(set_addr, tc90431_ham_addr + devbase);
	host->read_byte_flag = 0;

	status = tc90431_ham_nand_read_byte(mtd);
	return status;
}

static int tc90431_ham_nand_errstat(struct mtd_info *mtd,
				    struct nand_chip *this, int state,
				    int status, int page)
{
	struct nand_chip *chip = mtd->priv;
	struct nand_errstat_cmd *esc = chip->errstat_cmd[state];

	if (esc == NULL)
		return status;

	pr_debug(DRV_DEVNAME
	      ":additional error status check enabled, state=0x%x\n", state);

	for (; esc->maf_id != -1; esc++) {
		if ((this->man_id != esc->maf_id) ||
		    (this->dev_id != esc->dev_id))
			continue;

		switch (esc->command) {
		case NAND_CMD_STATUS:
		case NAND_CMD_STATUS_MULTI:
			status = this->waitfunc(mtd, this);
			pr_debug("cmd: %02X, status: %02X\n",
				 esc->command, status);
			break;

		default:
			pr_debug("cmd: %02X, col: %d, page: 0x%08x\n",
				 esc->command, esc->column,
				 esc->page_addr ? page & chip->pagemask : -1);
			this->cmdfunc(mtd, esc->command, esc->column,
				      esc->page_addr ?
				      page & chip->pagemask : -1);
			break;
		}
	}

	return status;
}

static void tc90431_ham_nand_command(struct mtd_info *mtd,
				      unsigned int command, int column,
				      int page_addr)
{
	struct nand_chip *chip = mtd->priv;
	struct tc90431_ham_nand_host *host = chip->priv;
	unsigned int cmd, end_cmd;
	u32 tc90431_ham_addr, set_addr;
	u32 full_cycle, page_size, erase_cycle;

	pm_runtime_get_sync(host->dev);
	full_cycle = host->chip_set->full_cycle;
	erase_cycle = host->chip_set->erase_cycle;
	page_size = host->chip_set->page_size;
	host->page_addr = page_addr;

	/* Command Phase */
	switch (command) {
	case NAND_CMD_READOOB:
		host->oob_read_flag = 0;
		if (host->ecc_val != ECC_OFF) {
			host->ecc_val = ECC_OFF;
			tc90431_ham_nand_set_ecc(host, host->ecc_val);
		}
		if (host->chip_set->page_size != LARGE_PAGE) {
			tc90431_ham_addr =
			    TC90431_HAM_CMD_CHIP_ADDR |
			    TC90431_HAM_CMD_ADDCYCLE(full_cycle) |
			    TC90431_HAM_CMD_END_CMD_VAL(0x0) |
			    TC90431_HAM_CMD_19 |
			    TC90431_HAM_CMD_END_CMD(0x0) |
			    TC90431_HAM_CMD_START_CMD(command);
			set_addr =
			    (page_addr << host->chip_set->column_val) | column;
			ndwritel(set_addr, tc90431_ham_addr + devbase);
			tc90431_ham_nand_wait_op_done(host);
			break;
		} else {
			host->command = NAND_CMD_READOOB;
			column += mtd->writesize;
			command = NAND_CMD_READ0;
		}
	case NAND_CMD_READ0:

		if (host->command != NAND_CMD_READOOB &&
		    host->ecc_val != ECC_ON) {
			host->ecc_val = ECC_ON;
			tc90431_ham_nand_set_ecc(host, host->ecc_val);
			host->command = NAND_CMD_READ0;
		}

		if (host->chip_set->page_size != LARGE_PAGE)
			end_cmd = 0x0;
		else
			end_cmd = NAND_CMD_READSTART;

		tc90431_ham_addr =
		    TC90431_HAM_CMD_CHIP_ADDR |
		    TC90431_HAM_CMD_ADDCYCLE(full_cycle) |
		    TC90431_HAM_CMD_END_CMD_VAL(page_size) |
		    TC90431_HAM_CMD_19 |
		    TC90431_HAM_CMD_END_CMD(end_cmd) |
		    TC90431_HAM_CMD_START_CMD(command);

		set_addr = (page_addr << host->chip_set->column_val) | column;

		ndwritel(set_addr, tc90431_ham_addr + devbase);

		if (host->chip_set->full_cycle >= 0x5) {
			set_addr = (page_addr >> 0x10);
			ndwritel(set_addr, tc90431_ham_addr + devbase);
		}
		tc90431_ham_nand_wait_op_done(host);
		host->command = NAND_CMD_READ0;

		break;

	case NAND_CMD_READID:
		tc90431_ham_addr = TC90431_HAM_CMD_CHIP_ADDR |
		    TC90431_HAM_CMD_ADDCYCLE(0x1) |
		    TC90431_HAM_CMD_END_CMD_VAL(0x0) |
		    TC90431_HAM_CMD_19 |
		    TC90431_HAM_CMD_END_CMD(0x0) |
		    TC90431_HAM_CMD_START_CMD(command);
		set_addr = 0x0;
		ndwritel(set_addr, tc90431_ham_addr + devbase);
		host->read_byte_flag = 0;
		break;

	case NAND_CMD_SEQIN:
		if (host->chip_set->page_size != LARGE_PAGE) {
			if (column >= mtd->writesize) {
				column -= mtd->writesize;
				cmd = NAND_CMD_READOOB;
				if (host->ecc_val != ECC_OFF)
					host->ecc_val = ECC_OFF;
			} else if (column < 256) {
				cmd = NAND_CMD_READ0;
				if (host->ecc_val != ECC_ON)
					host->ecc_val = ECC_ON;
			} else {
				column -= 256;
				cmd = NAND_CMD_READ1;
				if (host->ecc_val != ECC_ON)
					host->ecc_val = ECC_ON;
			}
			tc90431_ham_nand_pre_command(cmd, host);
			tc90431_ham_nand_set_ecc(host, host->ecc_val);
		} else {
			if (column >= mtd->writesize) {
				if (host->ecc_val != ECC_OFF)
					host->ecc_val = ECC_OFF;
			} else {
				if (host->ecc_val != ECC_ON)
					host->ecc_val = ECC_ON;
			}
			tc90431_ham_nand_set_ecc(host, host->ecc_val);
		}

		tc90431_ham_addr =
		    TC90431_HAM_CMD_CHIP_ADDR |
		    TC90431_HAM_CMD_ADDCYCLE(full_cycle) |
		    TC90431_HAM_CMD_END_CMD_VAL(0x0) |
		    TC90431_HAM_CMD_19 |
		    TC90431_HAM_CMD_END_CMD(0x0) |
		    TC90431_HAM_CMD_START_CMD(command);

		set_addr = (page_addr << host->chip_set->column_val) | column;
		ndwritel(set_addr, tc90431_ham_addr + devbase);

		if (host->chip_set->full_cycle >= 5) {
			set_addr = page_addr >> 0x10;
			ndwritel(set_addr, tc90431_ham_addr + devbase);
		}
		break;

	case NAND_CMD_ERASE1:
		tc90431_ham_addr =
		    TC90431_HAM_CMD_CHIP_ADDR |
		    TC90431_HAM_CMD_ADDCYCLE(erase_cycle) |
		    TC90431_HAM_CMD_END_CMD_VAL(0x1) |
		    TC90431_HAM_CMD_19 |
		    TC90431_HAM_CMD_END_CMD(NAND_CMD_ERASE2) |
		    TC90431_HAM_CMD_START_CMD(command);
		set_addr = page_addr;
		ndwritel(set_addr, tc90431_ham_addr + devbase);
		tc90431_ham_nand_wait_op_done(host);
		break;

	case NAND_CMD_RESET:
	case NAND_CMD_STATUS:
		tc90431_ham_addr = TC90431_HAM_CMD_CHIP_ADDR |
		    TC90431_HAM_CMD_ADDCYCLE(0x0) |
		    TC90431_HAM_CMD_END_CMD_VAL(0x0) |
		    TC90431_HAM_CMD_19 |
		    TC90431_HAM_CMD_END_CMD(0x0) |
		    TC90431_HAM_CMD_START_CMD(command);

		set_addr = 0x0;
		ndwritel(set_addr, tc90431_ham_addr + devbase);
		host->read_byte_flag = 0;

		if (command == NAND_CMD_RESET)
			tc90431_ham_nand_wait_op_done(host);
		break;

	case NAND_CMD_PAGEPROG:
	case NAND_CMD_ERASE2:
		break;

	default:
		tc90431_ham_addr = TC90431_HAM_CMD_CHIP_ADDR |
		    TC90431_HAM_CMD_ADDCYCLE(0x0) |
		    TC90431_HAM_CMD_END_CMD_VAL(0x0) |
		    TC90431_HAM_CMD_19 |
		    TC90431_HAM_CMD_END_CMD(0x0) |
		    TC90431_HAM_CMD_START_CMD(command);

		ndwritel(0x0, tc90431_ham_addr + devbase);
		break;
	}
	pm_runtime_mark_last_busy(host->dev);
	pm_runtime_put_autosuspend(host->dev);
}

static int tc90431_ham_nand_set_be_chip(struct mtd_info *mtd)
{
	struct nand_chip *this = mtd->priv;
	struct tc90431_ham_nand_host *host = this->priv;
	int ret;

	host->chip_set->page_size = LARGE_PAGE;
	host->chip_set->exblocksize = mtd->oobsize;
	host->chip_set->ecc_count = 0;

	/* setting chip */
	switch (mtd->writesize) {
	case 2048:
	case 4096:
		host->chip_set->column_val = 0x10;
		break;
	default:
		pr_warn("ERR:Write Size is unmattch.\n");
		return -EIO;
	}

	ret = (int)(this->chipsize >> 20);
	switch (ret) {
	case 128:
		host->chip_set->full_cycle = 4;
		host->chip_set->erase_cycle = 2;
		break;
	case 256:
		host->chip_set->full_cycle = 5;
		host->chip_set->erase_cycle = 3;
		break;
	case 512:
		host->chip_set->full_cycle = 5;
		host->chip_set->erase_cycle = 3;
		break;
	default:
		pr_warn("ERR:Chip Size is unmattch.\n");
		return -EIO;
	}

	return 0;
}

static int tc90431_ham_nand_set_chip(struct mtd_info *mtd)
{
	struct nand_chip *this = mtd->priv;
	struct tc90431_ham_nand_host *host = this->priv;
	struct tc90431_ham_nand_regs __iomem *regs =
	   (struct tc90431_ham_nand_regs __iomem *)host->iobase;
	int i, ret;
#ifdef CONFIG_TC90431_HAM_NAND_DEBUG
	u32 reg;
#endif

	u32 set_cycles = 0;
	u32 set_directcmd = TC90431_HAM_DIRECTCMD_CMDTYPE(0x2);

	if (host->chip_set->autoset_enable != 0) {
		for (i = 0; man_ac_chip[i].man_id != 0x100; i++) {
			if (this->man_id == man_ac_chip[i].man_id &&
			    this->dev_id == man_ac_chip[i].dev_id) {
				host->chip_set->ac_timing
					= man_ac_chip[i].ac_timing;
				break;
			}

			if (man_ac_chip[i].man_id == 0x0) {
				host->chip_set->ac_timing
					= man_ac_chip[i].ac_timing;
				pr_warn("%s:\n", __func__);
				pr_warn("Warning :ChipID is unmatch ac_timing table.\n");
				pr_warn("If want to New chip, Please add \"ac_timing\" at table.");
				pr_cont(" Now, using default actiming.\n");
				break;
			}
		}
		set_cycles = host->chip_set->ac_timing;
		ndwritel(set_cycles, &regs->setcycles);
		/* update cycles0 and opmode0) */
		ndwritel(set_directcmd, &regs->directcmd);
	}

#ifdef CONFIG_TC90431_HAM_NAND_DEBUG
	pr_warn("writesize = 0x%08x\n", mtd->writesize);
	reg = ndreadl(&regs->cycles0);
	pr_warn("cycles0 = 0x%08x\n", reg);
#endif

	if (host->nand.ecc.mode == NAND_ECC_BENAND)
		return tc90431_ham_nand_set_be_chip(mtd);

	/* setting chip */
	switch (mtd->writesize) {
	case 512:
		host->chip_set->page_size = SMALL_PAGE;
		host->chip_set->column_val = 0x8;
		host->chip_set->exblocksize = 0x8;
		host->chip_set->ecc_count = 1;
		break;
	case 2048:
		host->chip_set->page_size = LARGE_PAGE;
		host->chip_set->column_val = 0x10;
		host->chip_set->exblocksize = 0x20;
		host->chip_set->ecc_count = 4;
		break;
	default:
		pr_warn("ERR:Write Size is unmattch.\n");
		return -EIO;
	}

	ret = (int)(this->chipsize >> 20);
	switch (ret) {
	case 32:
		host->chip_set->full_cycle = 3;
		host->chip_set->erase_cycle = 2;
		break;
	case 64:
		host->chip_set->full_cycle = 4;
		host->chip_set->erase_cycle = 3;
		break;
	case 128:
		host->chip_set->full_cycle = 4;
		if (host->chip_set->page_size != LARGE_PAGE)
			host->chip_set->erase_cycle = 3;
		else
			host->chip_set->erase_cycle = 2;
		break;
	case 256:
		if (host->chip_set->page_size != LARGE_PAGE)
			host->chip_set->full_cycle = 4;
		else
			host->chip_set->full_cycle = 5;
		host->chip_set->erase_cycle = 3;
		break;
	case 512:
	case 1024:
	case 2048:
		host->chip_set->full_cycle = 5;
		host->chip_set->erase_cycle = 3;
		break;
	default:
		pr_warn("ERR:Chip Size is unmattch.\n");
		return -EIO;
	}

	if (host->chip_set->page_size != LARGE_PAGE)
		this->ecc.layout = &small_nand_oob_8;
	else
		this->ecc.layout = &large_nand_oob_32;

	return 0;
}

static int __init tc90431_ham_nand_probe(struct platform_device *pdev)
{
	struct nand_chip *this;
	struct mtd_info *mtd;
	struct tc90431_ham_nand_host *host;
	struct resource *res;
	struct resource *res_dev;
	struct tc90431_ham_nand_regs __iomem *regs;
	int ret, i;
#ifdef CONFIG_OF
	struct device_node *np = NULL;
#endif/*CONFIG_OF*/
	struct mtd_part_parser_data ppdata = {};

	host = kzalloc(sizeof(struct tc90431_ham_nand_host), GFP_KERNEL);
	if (!host) {
		pr_warn("%s: No memory for nand_host\n", __func__);
		ret = -ENOMEM;
		return ret;
	}

	host->clk = clk_get(&pdev->dev, NULL);
	if (IS_ERR(host->clk))
		host->clk = NULL;
	if (host->clk) {
		ret = clk_prepare_enable(host->clk);
		if (ret) {
			clk_put(host->clk);
			host->clk = NULL;
		}
	}

	host->dev = &pdev->dev;
	this = (struct nand_chip *)&host->nand;
	mtd = &host->mtd;
	mtd->priv = this;
	this->priv = host;
	mtd->name = DRV_DEVNAME;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "%s: cannot get resource\n", __func__);
		ret = -ENOENT;
		goto err_out;
	}

	res_dev = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (!res_dev) {
		dev_err(&pdev->dev, "%s: cannot get resource\n", __func__);
		ret = -ENOENT;
		goto err_out;
	}

	host->ioarea = request_mem_region(res->start, resource_size(res),
					   pdev->name);
	if (host->ioarea == NULL) {
		dev_err(&pdev->dev, "%s: cannot request IO area\n", __func__);
		ret = -ENXIO;
		goto err_out;
	}

	devarea = request_mem_region(res_dev->start, resource_size(res_dev),
				      pdev->name);
	if (devarea == NULL) {
		dev_err(&pdev->dev, "%s: cannot request IO area\n", __func__);
		ret = -ENXIO;
		goto err_ioarea;
	}

	host->iobase = (unsigned long)ioremap(res->start, resource_size(res));
	if (!host->iobase) {
		dev_err(&pdev->dev, "%s: cannot map IO\n", __func__);
		ret = -ENXIO;
		goto err_devarea;
	}

	devbase = ioremap(res_dev->start, resource_size(res_dev));
	if (!devbase) {
		dev_err(&pdev->dev, "%s: cannot map IO\n", __func__);
		ret = -ENXIO;
		goto err_iomap;
	}

	regs = (struct tc90431_ham_nand_regs __iomem *)host->iobase;

	host->chip_set = &chip_select;

	this->chip_delay = 50;	/* 50us wait */
	this->waitfunc = tc90431_ham_nand_waitfunc;
	this->cmdfunc = tc90431_ham_nand_command;
	this->read_byte = tc90431_ham_nand_read_byte;
	this->read_buf = tc90431_ham_nand_read_buf;
	this->write_buf = tc90431_ham_nand_write_buf;
	this->verify_buf = tc90431_ham_nand_verify_buf;
	this->dev_ready = tc90431_ham_nand_dev_ready;
	this->select_chip = tc90431_ham_nand_select_chip;
	this->errstat = tc90431_ham_nand_errstat;

	this->ecc.size = 512;
	this->ecc.read_page = tc90431_ham_nand_read_page_hwecc;
	this->ecc.write_page = tc90431_ham_nand_write_page_hwecc;

	this->ecc.mode = NAND_ECC_HW;

	host->oob_read_flag = 0;
	host->oob_write_flag = 0;
	host->match_flag = 0xFFFFFFFF;
#ifdef CONFIG_OF
	np = of_find_compatible_node(NULL, NULL, "toshiba,tc90431_nand2");
	if (np != NULL) {
		u32 ac_timing = 0;
		const u32 *ip;
		ip = of_get_property(np, "ac_timing", NULL);
		if (ip)
			ac_timing = be32_to_cpup(ip);
		if (ac_timing) {
			host->chip_set->autoset_enable = 0;
			host->chip_set->ac_timing = ac_timing;
			pr_info("tc90431_nand2: given device-tree's ac_timing 0x08%x\n",
				ac_timing);
		}
	}
#endif
	if (host->chip_set->autoset_enable != 0)
		host->chip_set->ac_timing = 0x00FFFFFF;

	host->match_oob_flag = 0;

	this->options |= NAND_NO_SUBPAGE_WRITE | NAND_NO_AUTOINCR;

	/* SET INIT and ECC config */
	tc90431_ham_nand_set_init(host);
	host->command = NAND_CMD_READ0;

	pm_runtime_set_autosuspend_delay(&pdev->dev, 1000);
	pm_runtime_use_autosuspend(&pdev->dev);
	pm_runtime_set_active(&pdev->dev);
	pm_runtime_enable(&pdev->dev);

	/* first scan to find the device and get the page size */
	if (nand_scan_ident(mtd, 1, NULL)) {
		ret = -ENXIO;
		goto err_devmap;
	}

	ret = tc90431_ham_nand_set_chip(mtd);
	if (ret < 0)
		goto err_devmap;

	tc90431_ham_nand_set_ecc(host, ECC_ON);

	if (nand_scan_tail(mtd)) {
		ret = -ENXIO;
		goto err_devmap;
	}

#ifdef CONFIG_OF
	ppdata.of_node = np;
#endif
	mtd_device_parse_register(mtd, NULL, &ppdata, NULL, 0);

#ifdef CONFIG_OF
	if (np != NULL)
		of_node_put(np);
#endif/*CONFIG_OF*/
	platform_set_drvdata(pdev, host);

	for (i = 0; i < FL_STATE_MAX; i++)
		this->errstat_cmd[i] = NULL;

	return 0;

err_devmap:
	pm_runtime_disable(&pdev->dev);
	iounmap((void __iomem *)devbase);

err_iomap:
	iounmap((void __iomem *)host->iobase);

err_devarea:
	release_resource(devarea);
	kfree(devarea);

err_ioarea:
	release_resource(host->ioarea);
	kfree(host->ioarea);

err_out:
	if (host->clk) {
		clk_disable_unprepare(host->clk);
		clk_put(host->clk);
	}
	kfree(host);

#ifdef CONFIG_OF
	if (np != NULL)
		of_node_put(np);
#endif/*CONFIG_OF*/
	pr_warn(":failed.\n");
	return ret;
}

static int __exit tc90431_ham_nand_remove(struct platform_device *pdev)
{
	struct tc90431_ham_nand_host *host = platform_get_drvdata(pdev);
	struct nand_chip *this = host->mtd.priv;
	int i;

	platform_set_drvdata(pdev, NULL);

	for (i = 0; i < FL_STATE_MAX; i++) {
		if (this->errstat_cmd[i] != NULL) {
			kfree(this->errstat_cmd[i]);
			this->errstat_cmd[i] = NULL;
		}
	}
	nand_release(&host->mtd);
	if (host->clk) {
		clk_disable_unprepare(host->clk);
		clk_put(host->clk);
	}
	release_resource(host->ioarea);
	release_resource(devarea);
	kfree(host->ioarea);
	kfree(devarea);
	iounmap((void __iomem *)host->iobase);
	iounmap((void __iomem *)devbase);

	pm_runtime_disable(&pdev->dev);
	kfree(host);

	return 0;
}

#ifdef CONFIG_PM
static int tc90431_ham_nand_suspend(struct device *dev)
{
	return 0;
}

static int tc90431_ham_nand_resume(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct tc90431_ham_nand_host *host = platform_get_drvdata(pdev);

	clk_prepare_enable(host->clk);
	tc90431_ham_nand_set_init(host);
	host->command = NAND_CMD_READ0;
	tc90431_ham_nand_set_chip(&host->mtd);
	tc90431_ham_nand_set_ecc(host, ECC_ON);
	clk_disable(host->clk);
	return 0;
}
#endif

#ifdef CONFIG_PM_RUNTIME
static void tc90431_ham_nand_enter_lowpower(struct platform_device *pdev)
{
	struct tc90431_ham_nand_host *host = platform_get_drvdata(pdev);
	struct tc90431_ham_nand_regs __iomem *regs =
		(struct tc90431_ham_nand_regs __iomem *)host->iobase;
	unsigned long timeout;

	timeout = jiffies + msecs_to_jiffies(10);
	ndwritel(TC90431_HAM_SETCONFIG_LPWRREQ, &regs->setconfig);
	while (!(ndreadl(&regs->status) & TC90431_HAM_STATUS_LPWR)) {
		if (time_after_eq(jiffies, timeout)) {
			dev_warn(&pdev->dev, "enter low-power timeout\n");
			break;
		}
	}
}

static void tc90431_ham_nand_exit_lowpower(struct platform_device *pdev)
{
	struct tc90431_ham_nand_host *host = platform_get_drvdata(pdev);
	struct tc90431_ham_nand_regs __iomem *regs =
		(struct tc90431_ham_nand_regs __iomem *)host->iobase;
	ndwritel(TC90431_HAM_CLRCONFIG_LPWREXIT, &regs->clrconfig);
}

static int tc90431_ham_nand_runtime_suspend(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct tc90431_ham_nand_host *host = platform_get_drvdata(pdev);

	tc90431_ham_nand_enter_lowpower(pdev);
	clk_disable(host->clk);
	return 0;
}

static int tc90431_ham_nand_runtime_resume(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct tc90431_ham_nand_host *host = platform_get_drvdata(pdev);

	clk_enable(host->clk);
	tc90431_ham_nand_exit_lowpower(pdev);
	return 0;
}
#endif

static const struct dev_pm_ops tc90431_ham_nand_dev_pm_ops = {
	SET_SYSTEM_SLEEP_PM_OPS(tc90431_ham_nand_suspend,
				tc90431_ham_nand_resume)
	SET_RUNTIME_PM_OPS(tc90431_ham_nand_runtime_suspend,
			   tc90431_ham_nand_runtime_resume,
			   NULL)
};

static struct platform_driver tc90431_ham_nand_driver = {
	.remove = __exit_p(tc90431_ham_nand_remove),
	.driver = {
		.name = DRV_DEVNAME,
		.pm = &tc90431_ham_nand_dev_pm_ops,
		.owner = THIS_MODULE,
	},
};

static int __init tc90431_ham_nand_init(void)
{
	return platform_driver_probe(&tc90431_ham_nand_driver,
				     tc90431_ham_nand_probe);
}

static void __exit tc90431_ham_nand_exit(void)
{
	platform_driver_unregister(&tc90431_ham_nand_driver);
}

module_init(tc90431_ham_nand_init);
module_exit(tc90431_ham_nand_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("TC90431 HAMMING NAND flash controller driver");
MODULE_ALIAS("platform:tc90431_nand2");
