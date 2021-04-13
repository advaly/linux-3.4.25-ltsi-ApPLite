/*
 * linux/drivers/staging/applite/syscon/applite_syscon_internal.h
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

#if !defined(__SYSCON_DRIVER_INTERNAL_MODULE_H__)
#define __SYSCON_DRIVER_INTERNAL_MODULE_H__

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/*===================================
include Files
===================================*/
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/device.h>

#include <mach/platform.h>
#if IS_ENABLED(CONFIG_CRYPTO_DEV_APPLITE)
#include <crypto/scatterwalk.h>
#include <crypto/aes.h>
#include <crypto/hash.h>
#include <crypto/sha.h>
#endif	/* CONFIG_CRYPTO_DEV_APPLITE */

#include "applite_syscon_dbg.h"
#include "applite_syscon_regs.h"
#if IS_ENABLED(CONFIG_ARCH_TZ2000)
#include <mach/regs/rtc_reg_def.h>
#endif	/* CONFIG_ARCH_TZ2000 */


/*===================================
Types and structures   defined
===================================*/

/* driver values */
#define	DEVICE_NAME			"syscon"
#define	PLAT_DEVICE_NAME		"applite-syscon"
#define	SYSCON_DRIVER_VERSION		"1.0"

/* interrupt values */
#define SYSCON_IRQ_MAX			(2)
#define SYSCON_IRQ_FLAG			(IRQF_SHARED | IRQF_TRIGGER_HIGH)

/* f/w values */
#if defined(CONFIG_ARCH_TZ3000)
#define SYSCON_DEF_FW_NAME		"applite/tz3000.sbp"
#else
#define SYSCON_DEF_FW_NAME		"applite/tz2000.sbp"
#endif

#define SYSCON_AREA			((64 + 64) * 1024)
#define SYSCON_DW_TIMEOUT		(5000)	/* 5sec */

#define SYSCON_FREE_TIMEOUT		(5000)	/* 5sec */
#define SYSCON_SLOT_TIMEOUT		(10000)	/* 10sec */
#define SYSCON_TAS_TIMEOUT		(100)	/* 100msec */

#define SYSCON_SLOTC_Q_MAX		(4)
#define SYSCON_INVALID_QNO		(0xFF)

#define FLAGS_BUSY			BIT(0)

#define SYSCON_REQ_SIZE_MAX		(0x100000)	/* 1MB */
#define SYSCON_QUEUE_LEN		(50)

#define SYSCON_IV_SIZE			(16)
#define SYSCON_IV_ALIGN			(16)
#define SYSCON_IV_BUF_SIZE		(64)

#define SYSCON_HASH_DST_SIZE		(256)
#define SYSCON_HASH_DST_ALIGN		(16)
#define SYSCON_HASH_DST_BUF_SIZE	(SYSCON_HASH_DST_SIZE + \
					 SYSCON_HASH_DST_ALIGN)

#define SYSCON_HMAC_WORK_BUF_SIZE	(128)		/* 64 * 2 */
#define SYSCON_WK_BUF_SIZE		(256 + SYSCON_HMAC_WORK_BUF_SIZE)

/* for hw_random */
#define SYSCON_RNG_SIZE			(64)


/* internal values */
#define SYSCON_OK			(0)
#define SYSCON_NG			(-EFAULT)

#define SCOMM_REG_SIZE			(0x1000)



enum syscon_fw_dl {
	SYSCON_DL_NOT = 0,
	SYSCON_DL_DONE
};

enum syscon_crypto_reg {
	SYSCON_REG_CRYPTO_INIT = 0,
	SYSCON_REG_CRYPTO_DONE,
	SYSCON_REG_CRYPTO_NOT
};

/* driver structures */
struct syscon_dev {
	struct cdev		cdev;
	struct device		*device;
	__u8 __iomem		*scommbase;
	__u8 __iomem		*mboxbase;
	int			irq[SYSCON_IRQ_MAX];
	char			*virt;
	dma_addr_t		phys;
	struct completion	comp;
	struct completion	comp_l_slot;
	struct completion	comp_s_slot;
	enum syscon_fw_dl	b_download;
	struct mutex		mutex_l_slot;
	struct mutex		mutex_s_slot;
	struct mutex		mutex_dev;
	struct mutex		mutex_scomm_rsp;
	__u32			counter;
	__u32			result_l_slot;
	__u32			result_s_slot;
	enum syscon_crypto_reg	b_regist;
#if IS_ENABLED(CONFIG_CRYPTO_DEV_APPLITE)
	spinlock_t		lock;
	struct crypto_queue	queue[SYSCON_SLOTC_Q_MAX];
	unsigned long		crypto_stat[SYSCON_SLOTC_Q_MAX];
	struct semaphore	q_sem;
	struct mutex		mutex_c_slot[SYSCON_SLOTC_Q_MAX];
	struct completion	comp_c_slot[SYSCON_SLOTC_Q_MAX];
	__u32			result_c_slot[SYSCON_SLOTC_Q_MAX];
	__u32			result_c_slot_caller[SYSCON_SLOTC_Q_MAX];
	__u32			result_c_slot_sub[SYSCON_SLOTC_Q_MAX];
	__u8			use_q;
	char			*wk_virt[SYSCON_SLOTC_Q_MAX];
	dma_addr_t		wk_phys[SYSCON_SLOTC_Q_MAX];
	char			*hmac_wk_virt[SYSCON_SLOTC_Q_MAX];
	dma_addr_t		hmac_wk_phys[SYSCON_SLOTC_Q_MAX];
#endif	/* CONFIG_CRYPTO_DEV_APPLITE */
};

#if IS_ENABLED(CONFIG_CRYPTO_DEV_APPLITE)

struct syscon_ctx {
	size_t			keylen;
	__u8			key[AES_MAX_KEY_SIZE];		/* 32 byte */
	__u8			keyno;
};

struct syscon_hmac_ctx {
	size_t			keylen;
	__u8			i_key[SHA256_BLOCK_SIZE];	/* 64 byte */
	__u8			o_key[SHA256_BLOCK_SIZE];	/* 64 byte */
	struct ahash_request	*req;
	struct completion	comp;
	int			err;
};

struct syscon_cmd_c {
	__u32			dst;
	__u32			src;
	__u32			len;
	__u32			iv;
	__u32			algo;
	__u8			mode;
	__u8			queno;
	struct syscon_ctx	*ctx;
};

struct syscon_aes_reqctx {
	struct syscon_cmd_c	cmd;
};

struct syscon_hash_reqctx {
	struct syscon_cmd_c	cmd;
	__u8			free_queue;
	__u8			pre_hash;
};


#endif	/* CONFIG_CRYPTO_DEV_APPLITE */



/*===================================
Exported Variables
===================================*/

extern __u32 ul_logflags;
extern __u32 dbg_lv;
extern char *fw_path;
extern struct syscon_dev s_dev;
extern struct workqueue_struct	*syscon_wq[SYSCON_SLOTC_Q_MAX];

/*===================================
Macros
===================================*/


/* register access macros */

static inline void scomm_write8(struct syscon_dev *dev,
				__u32 offset, __u8 value)
{
	SYSCON_DBG("adr(%p+0x%08X), val(0x%02X)\n",
				dev->scommbase, offset, value);
	__raw_writeb(value, (dev->scommbase + offset));
}

static inline void scomm_write(struct syscon_dev *dev,
				__u32 offset, __u32 value)
{
	SYSCON_DBG("adr(%p+0x%08X), val(0x%08X)\n",
				dev->scommbase, offset, value);
	__raw_writel(value, (dev->scommbase + offset));
}

static inline void scomm_write_buf(struct syscon_dev *dev,
				__u32 offset, __u8 *buf, __u32 size)
{
	SYSCON_DBG("adr(%p+0x%08X), size(0x%08X)\n",
				dev->scommbase, offset, size);
	memcpy((void *)(unsigned long)(dev->scommbase + offset), buf, size);
}

static inline void scomm_memset(struct syscon_dev *dev,
				__u32 offset, __u8 val, __u32 size)
{
	SYSCON_DBG("adr(%p+0x%08X), size(0x%08X)\n",
				dev->scommbase, offset, size);
	memset((void *)(unsigned long)(dev->scommbase + offset), val, size);
}

static inline __u8 scomm_read8(struct syscon_dev *dev, __u32 offset)
{
	__u8 val = __raw_readb((dev->scommbase + offset));
	SYSCON_DBG("adr(%p+0x%08X) = %02x\n",
				dev->scommbase, offset, val);
	return val;
}

static inline __u32 scomm_read(struct syscon_dev *dev, __u32 offset)
{
	__u32 val = __raw_readl((dev->scommbase + offset));
	SYSCON_DBG("adr(%p+0x%08X) = %08x\n",
				dev->scommbase, offset, val);
	return val;
}

static inline __u64 scomm_read64(struct syscon_dev *dev, __u32 offset)
{
	__u64 val = *(volatile __u64 __force *)(dev->scommbase + offset);
	SYSCON_DBG("adr(%p+0x%08X) = %016llx\n",
				dev->scommbase, offset, val);
	return val;
}

static inline void scomm_read_buf(struct syscon_dev *dev,
				__u32 offset, __u8 *buf, __u32 size)
{
	SYSCON_DBG("adr(%p+0x%08X), size(0x%08X)\n",
				dev->scommbase, offset, size);
	memcpy(buf, (void *)(unsigned long)(dev->scommbase + offset), size);
}

static inline void scomm_dump(struct syscon_dev *dev,
				__u32 offset, __u32 size)
{
	SYSCON_DBG("adr(%p+0x%08X), size(0x%08X)\n",
				dev->scommbase, offset, size);
	syscon_dump_buf((void *)(dev->scommbase + offset), size);
}

static inline void mbox_write(struct syscon_dev *dev,
				__u32 offset, __u32 value)
{
	SYSCON_DBG("adr(%p+0x%08X), val(0x%08X)\n",
				dev->mboxbase, offset, value);
	__raw_writel(value, ((dev)->mboxbase + offset));
}

static inline __u32  mbox_read(struct syscon_dev *dev, __u32 offset)
{
	__u32 val = __raw_readl(((dev)->mboxbase + offset));
	SYSCON_DBG("adr(%p+0x%08X) = %08x\n",
				dev->mboxbase, offset, val);
	return val;
}

static inline void syscon_set_init_notify(struct syscon_dev *pdev)
{
	__u32 reg = mbox_read(pdev, MBOX_REG(REG000_SET));
	SYSCON_FUNC_START("(%08x)\n", reg);
	mbox_write(pdev, MBOX_REG(REG000_SET), (reg | MBOX_DRV_INIT_NOTIFY));
}

static inline void syscon_set_fin_notify(struct syscon_dev *pdev)
{
	__u32 reg = mbox_read(pdev, MBOX_REG(REG000_SET));
	SYSCON_FUNC_START("(%08x)\n", reg);
	mbox_write(pdev, MBOX_REG(REG000_SET), (reg | MBOX_DRV_FIN_NOTIFY));
}

static inline void syscon_set_buf_free_req(struct syscon_dev *pdev)
{
	__u32 reg = mbox_read(pdev, MBOX_REG(REG000_SET));
	SYSCON_FUNC_START("(%08x)\n", reg);
	mbox_write(pdev, MBOX_REG(REG000_SET), (reg | MBOX_BUF_FREE_REQ));
}

static inline void syscon_set_dl_req(struct syscon_dev *pdev)
{
	__u32 reg = mbox_read(pdev, MBOX_REG(REG000_SET));
	SYSCON_FUNC_START("(%08x)\n", reg);
	mbox_write(pdev, MBOX_REG(REG000_SET), (reg | MBOX_FW_DL_REQ));
}

static inline void syscon_set_pm(struct syscon_dev *pdev, __u32 val)
{
	SYSCON_FUNC_START("(%08x)\n", val);
	mbox_write(pdev, MBOX_REG(REG001_SET), val);
}

static inline void syscon_set_cmd_rsp_ack_n(struct syscon_dev *pdev)
{
	__u32 reg = mbox_read(pdev, MBOX_REG(REG002_SET));
	SYSCON_FUNC_START("(%08x)\n", reg);
	mbox_write(pdev, MBOX_REG(REG002_SET), (reg | MBOX_CMD_RSP_ACK_N));
}

static inline void syscon_set_cmd_rsp_ack_s(struct syscon_dev *pdev)
{
	__u32 reg = mbox_read(pdev, MBOX_REG(REG002_SET));
	SYSCON_FUNC_START("(%08x)\n", reg);
	mbox_write(pdev, MBOX_REG(REG002_SET), (reg | MBOX_CMD_RSP_ACK_S));
}


static inline __u32 syscon_get_tas(struct syscon_dev *pdev)
{
	__u32 tas;
	int ierr = -ETIMEDOUT;
	unsigned long to = jiffies + msecs_to_jiffies(SYSCON_TAS_TIMEOUT);

	SYSCON_FUNC_START("(%ld)\n", to);
	while (time_is_after_jiffies(to)) {
		/* wait for tas */
		tas = scomm_read(pdev, SCOMM_TAS_SECURE_OFFS);
		SYSCON_DBG("tas:%08x\n", tas);
		if (tas == 0) {
			ierr = 0;
			break;
		}
	}
	SYSCON_FUNC_END("(%d)\n", ierr);
	return ierr;
}

static inline void syscon_free_tas(struct syscon_dev *pdev)
{
	__u32 tas = scomm_read(pdev, SCOMM_TAS_SECURE_OFFS);

	SYSCON_FUNC_START("(%08x)\n", tas);
	if (tas)
		scomm_write(pdev, SCOMM_TAS_SECURE_OFFS, 0);
}


/* for sysfs interface */

static inline __u64 syscon_get_fw_info(struct syscon_dev *pdev)
{
	__u64 reg = scomm_read64(pdev, SCOMM_REG(FW_INFO));
	SYSCON_FUNC_START("(%016llx)\n", reg);
	return reg;
}

static inline __u32 syscon_get_status(struct syscon_dev *pdev)
{
	__u32 reg = scomm_read(pdev, SCOMM_REG(STATUS));
	SYSCON_FUNC_START("(%08x)\n", reg);
	return reg;
}

static inline __u64 syscon_get_counter(struct syscon_dev *pdev)
{
	__u64 reg = scomm_read64(pdev, SCOMM_REG(COUNTER));
	SYSCON_FUNC_START("(%016llx)\n", reg);
	return reg;
}

static inline __u32 syscon_get_timer(struct syscon_dev *pdev)
{
	__u32 reg = scomm_read(pdev, SCOMM_REG(TIMER));
	SYSCON_FUNC_START("(%08x)\n", reg);
	return reg;
}

static inline __u32 syscon_get_bootdevice(struct syscon_dev *pdev)
{
	__u32 reg = scomm_read(pdev, SCOMM_REG(BOOT_DEVICE));
	SYSCON_FUNC_START("(%08x)\n", reg);
	return reg;
}

static inline char *syscon_get_bootdevice_str(struct syscon_dev *pdev)
{
	char *str = NULL;
	__u32 reg = scomm_read(pdev, SCOMM_REG(BOOT_DEVICE));
	SYSCON_FUNC_START("(%08x)\n", reg);

	switch (reg) {
#if defined(CONFIG_ARCH_TZ3000)
	case SCOMM_BD_SPI:
		str = "SPI (3B)"; break;
	case SCOMM_BD_NAND_4:
		str = "NAND (4cycle)"; break;
	case SCOMM_BD_NAND_5:
		str = "NAND (5cycle)"; break;
	case SCOMM_BD_EMMC:
		str = "eMMC"; break;
	case SCOMM_BD_SD:
		str = "SD Card"; break;
#else
	case SCOMM_BD_SPI:
		str = "SPI (3B)"; break;
	case SCOMM_BD_NAND:
		str = "NAND"; break;
	case SCOMM_BD_SD_0:
		str = "SD Card 0"; break;
	case SCOMM_BD_EMMC_1:
		str = "eMMC 1"; break;
	case SCOMM_BD_SD_1:
		str = "SD Card 1"; break;
#endif
	default:
		str = "Read Error";
	}
	return str;
}

static inline __u32 syscon_get_memorysize(struct syscon_dev *pdev)
{
	__u32 reg = scomm_read(pdev, SCOMM_REG(MEMORY_SIZE));
	SYSCON_FUNC_START("(%08x)\n", reg);
	return reg;
}

static inline __u32 syscon_get_memorytype(struct syscon_dev *pdev)
{
	__u32 reg = scomm_read(pdev, SCOMM_REG(MEMORY_TYPE));
	SYSCON_FUNC_START("(%08x)\n", reg);
	return reg;
}

static inline char *syscon_get_memorytype_str(struct syscon_dev *pdev)
{
	char *str = NULL;
	__u32 reg = scomm_read(pdev, SCOMM_REG(MEMORY_TYPE));
	SYSCON_FUNC_START("(%08x)\n", reg);

#if defined(CONFIG_ARCH_TZ3000)
	str = "DRAM";
#else
	switch (reg) {
	case SCOMM_MT_DRAM:
		str = "DRAM"; break;
	case SCOMM_MT_SRAM:
		str = "SRAM"; break;
	case SCOMM_MT_NAND:
		str = "NAND Cache Mode"; break;
	case SCOMM_MT_SRAM_NAND:
		str = "SRAM & NAND Cache Mode"; break;
	default:
		str = "Read Error";
	}
#endif
	return str;
}

static inline __u32 syscon_get_sysconfig0(struct syscon_dev *pdev)
{
	__u32 reg = scomm_read(pdev, SCOMM_REG(SYS_CONFIG0));
	SYSCON_FUNC_START("(%08x)\n", reg);
	return reg;
}

static inline __u32 syscon_get_sysconfig1(struct syscon_dev *pdev)
{
	__u32 reg = scomm_read(pdev, SCOMM_REG(SYS_CONFIG1));
	SYSCON_FUNC_START("(%08x)\n", reg);
	return reg;
}

static inline __u32 syscon_get_pwmn_config0(struct syscon_dev *pdev)
{
	__u32 reg = scomm_read(pdev, SCOMM_REG(PWMN_CONFIG0));
	SYSCON_FUNC_START("(%08x)\n", reg);
	return reg;
}

static inline __u32 syscon_get_pwmn_config1(struct syscon_dev *pdev)
{
	__u32 reg = scomm_read(pdev, SCOMM_REG(PWMN_CONFIG1));
	SYSCON_FUNC_START("(%08x)\n", reg);
	return reg;
}

static inline __u32 syscon_get_pwmn_config2(struct syscon_dev *pdev)
{
	__u32 reg = scomm_read(pdev, SCOMM_REG(PWMN_CONFIG2));
	SYSCON_FUNC_START("(%08x)\n", reg);
	return reg;
}

static inline __u32 syscon_get_pwmn_config3(struct syscon_dev *pdev)
{
	__u32 reg = scomm_read(pdev, SCOMM_REG(PWMN_CONFIG3));
	SYSCON_FUNC_START("(%08x)\n", reg);
	return reg;
}

static inline char *syscon_get_wakeup_trigger_str(struct syscon_dev *pdev)
{
	char *str = NULL;
	static char tmr[20] = "timer-";
	__u32 reg1 = syscon_get_pwmn_config0(pdev);
	__u32 reg2 = syscon_get_pwmn_config1(pdev);
	SYSCON_FUNC_START("(%08x, %08x)\n", reg1, reg2);

	switch (reg1 & SCOMM_WKUP_R_MASK) {
	case SCOMM_WKUP_GPIO_FALL:
		str = "gpio-falling"; break;
	case SCOMM_WKUP_GPIO_RISE:
		str = "gpio-rising"; break;
	case SCOMM_WKUP_TIMER:
		snprintf(&tmr[6], 14, "%d", reg2);
		str = tmr;
		break;
	case SCOMM_WKUP_RTC:
#if IS_ENABLED(CONFIG_ARCH_TZ2000)
		if (reg2 == RTC_RTC_INTMASK_ALARM_INTMASK_MASK)
			str = "rtc-alarm";
		else if (reg2 == RTC_RTC_INTMASK_PERIOD_INTMASK_MASK)
			str = "rtc-periodic";
		else
			str = "unknown";
#else
		str = "rtc";
#endif	/* CONFIG_ARCH_TZ2000 */
		break;
	case SCOMM_WKUP_I2C:
		str = "i2c"; break;
	case 0:
		str = "unknown"; break;
	default:
		str = "Read Error";
	}
	return str;
}

/*===================================
Exported Functions prototypes
===================================*/

int syscon_init(void);
void syscon_exit(void);

int syscon_reset_register(struct syscon_dev *pdev);
int syscon_init_hw(struct syscon_dev *pdev);
int syscon_exit_hw(struct syscon_dev *pdev);
int syscon_check_fw(struct syscon_dev *pdev);
int syscon_load_fw(struct syscon_dev *pdev);
int syscon_exec_l_slot(struct syscon_dev *pdev, struct syscon_cmd *cmd);
int syscon_exec_s_slot(struct syscon_dev *pdev, struct syscon_cmd *cmd);
#if IS_ENABLED(CONFIG_CRYPTO_DEV_APPLITE)
int syscon_exec_c_slot(struct syscon_dev *pdev, struct syscon_cmd_c *cmd);
#endif	/* CONFIG_CRYPTO_DEV_APPLITE */
__u8 syscon_get_free_queno(struct syscon_dev *pdev);
void syscon_release_queno(struct syscon_dev *pdev, int queno);

int syscon_crypto_init(struct syscon_dev *pdev);
void syscon_crypto_exit(struct syscon_dev *pdev);

#if IS_ENABLED(CONFIG_CRYPTO_DEV_APPLITE)
int syscon_crypto_aes_init(struct syscon_dev *pdev);
void syscon_crypto_aes_exit(struct syscon_dev *pdev);
int syscon_crypto_sha_init(struct syscon_dev *pdev);
void syscon_crypto_sha_exit(struct syscon_dev *pdev);
#endif	/* CONFIG_CRYPTO_DEV_APPLITE */

#if IS_ENABLED(CONFIG_HW_RANDOM_APPLITE)
int syscon_rng_init(struct syscon_dev *pdev);
void syscon_rng_exit(struct syscon_dev *pdev);
#endif	/* CONFIG_HW_RANDOM_APPLITE */

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* __SYSCON_DRIVER_INTERNAL_MODULE_H__ */

