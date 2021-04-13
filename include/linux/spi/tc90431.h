/*
 *  include/linux/spi/tc90431.h
 *
 *  various definitions for Toshiba TC90431 SPI controller driver
 *
 *  (C) Copyright TOSHIBA CORPORATION SEMICONDUCTOR COMPANY 2010
 * (C) Copyright TOSHIBA CORPORATION
 *      SEMICONDUCTOR & STORAGE PRODUCTS COMPANY 2013
 */

#ifndef __TC90431_SPI_H__
#define __TC90431_SPI_H__

#define OPCODE_FAST_READ_SINGLE      0x0b	/* == OPCODE_FAST_READ */
#define OPCODE_FAST_READ_DUAL_OUTPUT 0x3b
#define OPCODE_FAST_READ_DUAL_IO     0xbb
#define OPCODE_FAST_READ_QUAD_OUTPUT 0x6b
#define OPCODE_FAST_READ_QUAD_IO     0xeb

struct tc90431_spi_controller_data {
	u32 deassert_time;
#if IS_ENABLED(CONFIG_MTD_M25P80)
	unsigned long dir_read_phys;
	unsigned long dir_read_size;
	/* parameters initialized by m25p80 driver */
	u32 dir_max_speed_hz;
	u32 dir_deassert_time;
	unsigned char dir_read_opcode;
	unsigned char dir_read_dummy_count;
#endif
};

#endif /* __TC90431_SPI_H__ */
