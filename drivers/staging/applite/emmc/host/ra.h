/**
 * @file          ra.h
 *
 * \brief         This file includes register access macros.
 *
 * \b COPYRIGHT : TOSHIBA Corporation Semiconductor and Storage Company
 * 2010-2015 All rights reserved.
 *
 * \b Project   : Glenfiddich
 *
 * \b Version   : 0.4
 *
 * \b Release   : None
 *
 * \b Date      : 28-Jun-2013
 */

/**
 * @addtogroup Common
 * @{
 */

/**
 * @addtogroup RegisterAccess
 * @{
 */

#ifndef _RA_H_
#define _RA_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/*----------------------- Header Files Inclusions ---------------------------*/
#include "types.h"

/*-------------------------- Macro Definitions ------------------------------*/

/** @addtogroup RA_DEFINES RA_DEFINES
 * @{
 */

/**
 * @brief Host controller register offsets
 */
#define _SDMA_ADR_OFF            0x00 /* 32 bit access */
#define _BLKSIZE_OFF             0x04 /* 16 bit access */
#define _BLKCNT_OFF              0x06 /* 16 bit access */
#define _ARG1_OFF                0x08 /* 32 bit access */
#define _TRANSMODE_OFF           0x0c /* 16 bit access */
#define _CMD_OFF                 0x0e /* 16 bit access */
#define _RESP01_OFF              0x10 /* 32 bit access */
#define _RESP23_OFF              0x14 /* 32 bit access */
#define _RESP45_OFF              0x18 /* 32 bit access */
#define _RESP67_OFF              0x1c /* 32 bit access */
#define _BUF_DATA_PORT_OFF       0x20 /* 32 bit access */
#define _PRESENT_STS_OFF         0x24 /* 32 bit access */
#define _HOST_CTRL1_OFF          0x28 /* 8 bit access */
#define _PWR_CTRL_OFF            0x29 /* 8 bit access */
#define _BLKGAP_CTRL_OFF         0x2a /* 8 bit access */
#define _WAKEUP_CTRL_OFF         0x2b /* 8 bit access */
#define _CLK_CTRL_OFF            0x2c /* 16 bit access */
#define _TIMEOUT_CTRL_OFF        0x2e /* 8 bit access */
#define _SOFTWARE_RST_OFF        0x2f /* 8 bit access */
#define _NORMINT_STS_OFF         0x30 /* 16 bit access */
#define _ERRINT_STS_OFF          0x32 /* 16 bit access */
#define _NORMINT_STSEN_OFF       0x34 /* 16 bit access */
#define _ERRINT_STSEN_OFF        0x36 /* 16 bit access */
#define _NORMINT_SIGEN_OFF       0x38 /* 16 bit access */
#define _ERRINT_SIGEN_OFF        0x3a /* 16 bit access */
#define _ACMD12_ERRSTS_OFF       0x3c /* 16 bit access */
#define _HOST_CTRL2_OFF          0x3E /* 16 bit access */
#define _CAPABLITY1_OFF          0x40 /* 32 bit access */
#define _CAPABLITY2_OFF          0x44 /* 32 bit access */
#define _MAXCURR_CAP_OFF         0x48 /* 32 bit access */
#define _FRC_EVT_ACMD_OFF        0x50 /* 16 bit access */
#define _FRC_EVT_ERRINT_OFF      0x52 /* 16 bit access */
#define _ADMA_ERR_OFF            0x54 /* 8bit access */
#define _ADMASTART1_OFF          0x58 /* 32 bit access */
#define _ADMASTART2_OFF          0x5C /* 32 bit access */
#define _PRESETVAL1_OFF          0x60 /* 32 bit access */
#define _PRESETVAL2_OFF          0x64 /* 32 bit access */
#define _PRESETVAL3_OFF          0x68 /* 32 bit access */
#define _PRESETVAL4_OFF          0x6c /* 32 bit access */
#define _SHRDBUS_CTRL_OFF        0xE0 /* 32 bit access */
#define _SLOT_INTSTS_OFF         0xfc /* 16 bit access */
#define _CONTROLLER_VER_OFF      0xfe /* 16 bit access */

/**
 * @brief Base Slot offset for register access
 *
 * Vendor Specific: TBD from specifications
 */
#define SLOT_OFF                 0x00000000

/**
 * @brief Slot address calculation
 */
#ifdef __32BIT
#define SLOT_ADR(s)              ((s * SLOT_OFF) + (_ub32)hc_BaseAdr)
#else /* !__32BIT */
#define SLOT_ADR(s)              ((s * SLOT_OFF) + (_ub64)hc_BaseAdr)
#endif /* __32BIT */

/**
 * @brief Register Address for each slot depending on its offset
 */
#ifdef __32BIT
#define REG_ADR(s, off)          ((_addr)(SLOT_ADR(s) + (_ub32)off))
#else /* !__32BIT */
#define REG_ADR(s, off)          ((_addr)(SLOT_ADR(s) + off))
#endif /* __32BIT */

/*----------------------- General Read register macros ----------------------*/
/*----------------- Example: Rx_REG(slot_number, offset)---------------------*/

#define R8_REG(s, offset)        os_read8(REG_ADR(s,offset))
#define R16_REG(s, offset)       os_read16(REG_ADR(s,offset))
#define R32_REG(s, offset)       os_read32(REG_ADR(s,offset))

/*-------------------------- Read register macros ----------------------------*/
/*-------------- Example: R<bit_width>_<reg_name>(slot_number) ---------------*/

/**
 * @brief Read SDMA Address Register
 */
#define R32_SDMA_ADR(s)          os_read32(REG_ADR(s, _SDMA_ADR_OFF))

/**
 * @brief Read Block Size Register
 */
#define R16_BLKSIZE(s)           os_read16(REG_ADR(s, _BLKSIZE_OFF))

/**
 * @brief Read Block Count Register
 */
#define R16_BLKCNT(s)            os_read16(REG_ADR(s, _BLKCNT_OFF))

/**
 * @brief Read Argument 1 Register
 */
#define R32_ARG1(s)              os_read32(REG_ADR(s, _ARG1_OFF))

/**
 * @brief Read Transfer Mode Register
 */
#define R16_TRANSMODE(s)         os_read16(REG_ADR(s, _TRANSMODE_OFF))

/**
 * @brief Read Command Register
 */
#define R16_CMD(s)               os_read16(REG_ADR(s, _CMD_OFF))

/**
 * @brief Read Response 01 Register
 */
#define R32_RESP01(s)            os_read32(REG_ADR(s, _RESP01_OFF))

/**
 * @brief Read Response 23 Register
 */
#define R32_RESP23(s)            os_read32(REG_ADR(s, _RESP23_OFF))

/**
 * @brief Read Response 45 Register
 */
#define R32_RESP45(s)            os_read32(REG_ADR(s, _RESP45_OFF))

/**
 * @brief Read Response 67 Register
 */
#define R32_RESP67(s)            os_read32(REG_ADR(s, _RESP67_OFF))

/**
 * @brief Read Buffer data port Register
 */
#define R32_BUF_DAT_PORT(s)      os_read32(REG_ADR(s, _BUF_DATA_PORT_OFF))

/**
 * @brief Read Present state Register
 */
#define R32_PRESENT_STS(s)       os_read32(REG_ADR(s, _PRESENT_STS_OFF))

/**
 * @brief Read Host control 1 Register
 */
#define R8_HOST_CTRL1(s)         os_read8(REG_ADR(s, _HOST_CTRL1_OFF))

/**
 * @brief Read Power control Register
 */
#define R8_PWR_CTRL(s)           os_read8(REG_ADR(s, _PWR_CTRL_OFF))

/**
 * @brief Read Block gap control Register
 */
#define R8_BLOCKGAP_CTRL(s)      os_read8(REG_ADR(s, _BLKGAP_CTRL_OFF))

/**
 * @brief Read Wake up control Register
 */
#define R8_WAKEUP_CTRL(s)        os_read8(REG_ADR(s, _WAKEUP_CTRL_OFF))

/**
 * @brief Read Clock control Register
 */
#define R16_CLK_CTRL(s)          os_read16(REG_ADR(s, _CLK_CTRL_OFF))

/**
 * @brief Read Timeout control Register
 */
#define R8_TIMEOUT_CTRL(s)       os_read8(REG_ADR(s, _TIMEOUT_CTRL_OFF))

/**
 * @brief Read Software reset Register
 */
#define R8_SOFTWARE_RST(s)       os_read8(REG_ADR(s, _SOFTWARE_RST_OFF))

/**
 * @brief Read Normal interrupt status Register
 */
#define R16_NORMINT_STS(s)       os_read16(REG_ADR(s, _NORMINT_STS_OFF))

/**
 * @brief Read Error interrupt status Register
 */
#define R16_ERRINT_STS(s)        os_read16(REG_ADR(s, _ERRINT_STS_OFF))

/**
 * @brief Read Normal interrupt status Enable Register
 */
#define R16_NORMINT_STSEN(s)     os_read16(REG_ADR(s, _NORMINT_STSEN_OFF))

/**
 * @brief Read Read Error interrupt status Enable Register
 */
#define R16_ERRINT_STSEN(s)      os_read16(REG_ADR(s, _ERRINT_STSEN_OFF))

/**
 * @brief Read Normal interrupt signal Enable Register
 */
#define R16_NORMINT_SIGEN(s)     os_read16(REG_ADR(s, _NORMINT_SIGEN_OFF))

/**
 * @brief Read Error interrupt signal Enable Register
 */
#define R16_ERRINT_SIGEN(s)      os_read16(REG_ADR(s, _ERRINT_SIGEN_OFF))

/**
 * @brief Read Auto CMD Error Status Register
 */
#define R16_ACMD_ERRSTS(s)       os_read16(REG_ADR(s, _ACMD12_ERRSTS_OFF))

/**
 * @brief Read Host control 2 Register
 */
#define R16_HOST_CTRL2(s)        os_read16(REG_ADR(s, _HOST_CTRL2_OFF))

/**
 * @brief Read lower 32 bits of capability Register
 */
#define R32_CAPABLITY1(s)        os_read32(REG_ADR(s, _CAPABLITY1_OFF))

/**
 * @brief Read upper 32 bits of capability Register
 */
#define R32_CAPABLITY2(s)        os_read32(REG_ADR(s, _CAPABLITY2_OFF))

/**
 * @brief Read Maximum current capability Register
 */
#define R32_MAXCUR_CAP(s)        os_read32(REG_ADR(s, _MAXCURR_CAP_OFF))

/**
 * @brief Read Force Event for Auto CMD Error Status Register
 */
#define R16_FRCEVT_ACMD(s)       os_read16(REG_ADR(s, _FRC_EVT_ACMD_OFF))

/**
 * @brief Read Force Event for Error interrupt status Register
 */
#define R16_FRCEVT_ERRINT(s)     os_read16(REG_ADR(s, _FRC_EVT_ERRINT_OFF))

/**
 * @brief Read ADMA Error Status Register
 */
#define R8_ADMA_ERR(s)           os_read8(REG_ADR(s, _ADMA_ERR_OFF))

/**
 * @brief Read lower 32 bits of ADMA system address Register
 */
#define R32_ADMASTART1(s)        os_read32(REG_ADR(s, _ADMASTART1_OFF))

/**
 * @brief Read upper 32 bits of ADMA system address Register
 */
#define R32_ADMASTART2(s)        os_read32(REG_ADR(s, _ADMASTART2_OFF))

/**
 * @brief Read Preset value 1 Register
 */
#define R32_PRESETVAL1(s)        os_read32(REG_ADR(s, _PRESETVAL1_OFF))

/**
 * @brief Read Preset value 2 Register
 */
#define R32_PRESETVAL2(s)        os_read32(REG_ADR(s, _PRESETVAL2_OFF))

/**
 * @brief Read Preset value 3 Register
 */
#define R32_PRESETVAL3(s)        os_read32(REG_ADR(s, _PRESETVAL3_OFF))

/**
 * @brief Read Preset value 4 Register
 */
#define R32_PRESETVAL4(s)        os_read32(REG_ADR(s, _PRESETVAL4_OFF))

/**
 * @brief Read Shared bus control Register
 */
#define R32_SHRDBUS_CTRL(s)      os_read32(REG_ADR(s, _SHRDBUS_CTRL_OFF))

/**
 * @brief Read Slot interrupt status Register
 */
#define R16_SLOT_INTSTS(s)       os_read16(REG_ADR(s, _SLOT_INTSTS_OFF))

/**
 * @brief Read Controller version Register
 */
#define R16_CTRLR_VER(s)         os_read16(REG_ADR(s, _CONTROLLER_VER_OFF))

/*----------------------- General Write register macros --------------------*/
/*-------------- Example: Wx_REG(slot_number, value, offset)----------------*/

#define W8_REG(s, v, offset)   os_write8(v, REG_ADR(s,offset))
#define W16_REG(s, v, offset)  os_write16(v, REG_ADR(s,offset))
#define W32_REG(s, v, offset)  os_write32(v, REG_ADR(s,offset))

/*---------------------- Write register macros -------------------------------*/
/*---------- Example: W<bit_width>_<reg_name>(slot_number, value) ------------*/

/**
 * @brief Write into SDMA Address Register
 */
#define W32_SDMA_ADR(s, v)       os_write32(v, REG_ADR(s, _SDMA_ADR_OFF))

/**
 * @brief Write into Block Size Register
 */
#define W16_BLKSIZE(s, v)        os_write16(v, REG_ADR(s, _BLKSIZE_OFF))

/**
 * @brief Write into Block count Register
 */
#define W16_BLKCNT(s, v)         os_write16(v, REG_ADR(s, _BLKCNT_OFF))

/**
 * @brief Write into Argument 1 Register
 */
#define W32_ARG1(s, v)           os_write32(v, REG_ADR(s, _ARG1_OFF))

/**
 * @brief Write into Transfer mode Register
 */
#define W16_TRANSMODE(s, v)      os_write16(v, REG_ADR(s, _TRANSMODE_OFF))

/**
 * @brief Write into Command Register
 */
#define W16_CMD(s, v)            os_write16(v, REG_ADR(s, _CMD_OFF))

#ifdef __GLEN
/**
 * @brief Write into Transfer mode Register and command Register
 */
#define W32_CMD_TRANS(s, v)      os_write32(v, REG_ADR(s, _TRANSMODE_OFF))
#endif /* __GLEN */

/**
 * @brief Write into Buffer data port Register
 */
#define W32_BUF_DAT_PRT(s, v)    os_write32(v, REG_ADR(s, _BUF_DATA_PORT_OFF))

/**
 * @brief Write into Host control Register
 */
#define W8_HOST_CTRL1(s, v)      os_write8(v, REG_ADR(s, _HOST_CTRL1_OFF))

/**
 * @brief Write into power control Register
 */
#define W8_PWR_CTRL(s, v)        os_write8(v, REG_ADR(s, _PWR_CTRL_OFF))

/**
 * @brief Write into Block gap control Register
 */
#define W8_BLKGAP_CTRL(s, v)     os_write8(v, REG_ADR(s, _BLKGAP_CTRL_OFF))

/**
 * @brief Write into Wake up control Register
 */
#define W8_WAKEUP_CTRL(s, v)     os_write8(v, REG_ADR(s, _WAKEUP_CTRL_OFF))

/**
 * @brief Write into Clock control Register
 */
#define W16_CLK_CTRL(s, v)       os_write16(v, REG_ADR(s, _CLK_CTRL_OFF))

/**
 * @brief Write into Timeout control Register
 */
#define W8_TIMEOUT_CTRL(s, v)    os_write8(v, REG_ADR(s, _TIMEOUT_CTRL_OFF))

/**
 * @brief Write into Software reset Register
 */
#define W8_SOFTWARE_RST(s, v)    os_write8(v, REG_ADR(s, _SOFTWARE_RST_OFF))

/**
 * @brief Write into Normal interrupt status Register
 */
#define W16_NORMINT_STS(s, v)    os_write16(v, REG_ADR(s, _NORMINT_STS_OFF))

/**
 * @brief Write into Error interrupt status Register
 */
#define W16_ERRINT_STS(s, v)     os_write16(v, REG_ADR(s, _ERRINT_STS_OFF))

/**
 * @brief Write into Normal interrupt status enable Register
 */
#define W16_NORMINT_STSEN(s, v)  os_write16(v, REG_ADR(s, _NORMINT_STSEN_OFF))

/**
 * @brief Write into Error interrupt status enable Register
 */
#define W16_ERRINT_STSEN(s, v)   os_write16(v, REG_ADR(s, _ERRINT_STSEN_OFF))

/**
 * @brief Write into Normal interrupt signal enable Register
 */
#define W16_NORMINT_SIGEN(s, v)  os_write16(v, REG_ADR(s, _NORMINT_SIGEN_OFF))

/**
 * @brief Write into Error interrupt signal enable Register
 */
#define W16_ERRINT_SIGEN(s, v)   os_write16(v, REG_ADR(s, _ERRINT_SIGEN_OFF))

/**
 * @brief Write into Host control 2 Register
 */
#define W16_HOST_CTRL2(s, v)     os_write16(v, REG_ADR(s, _HOST_CTRL2_OFF))

/**
 * @brief Write into Force Event for Auto CMD Error Status Register
 */
#define W16_FRC_EVT_ACMD(s, v)   os_write16(v, REG_ADR(s, _FRC_EVT_ACMD_OFF))

/**
 * @brief Write into Force Event Error interrupt Status Register
 */
#define W16_FRC_EVT_ERRINT(s, v) os_write16(v, REG_ADR(s, _FRC_EVT_ERRINT_OFF))

/**
 * @brief Write into lower 32 bits of ADMA system address Register
 */
#define W32_ADMASTART1(s, v)     os_write32(v, REG_ADR(s, _ADMASTART1_OFF))

/**
 * @brief Write into upper 32 bits of ADMA system address Register
 */
#define W32_ADMASTART2(s, v)     os_write32(v, REG_ADR(s, _ADMASTART2_OFF))

/**
 * @brief Write into Shared bus control register
 */
#define W32_SHRDBUS_CTRL(s, v)   os_write32(v, REG_ADR(s, _SHRDBUS_CTRL_OFF))

/**@}*/ // RA_DEFINES

/*-------------------------- Enum Definitions -------------------------------*/

/*------------------ Data Structures & Custom Typedefs ----------------------*/

/*------------------------------ Externs ------------------------------------*/

/** @addtogroup RA_Externs RA_Externs
 * @{
 */

extern _addr hc_BaseAdr; /* Host Controller Base Address */

/**@}*/ // RA_Externs

/*---------------------------- Prototypes -----------------------------------*/
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _RA_H */

/**@}*//* RegisterAccess */
/**@}*//* Common */

