/*
 * linux/driver/video/applite/tz2000_regs.h
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

#if !defined(__TZ2000_REGS_H__)
#define __TZ2000_REGS_H__

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/*===================================
include Files
===================================*/
#include <mach/regs/cpu_memmap_def.h>
#include <mach/regs/gfx_offs_def.h>
#include <mach/regs/gfx_reg_def.h>
#include <mach/regs/pmu_offs_def.h>
#include <mach/regs/pmu_reg_def.h>


/*===================================
Types and structures   defined
===================================*/

#define BITW_1				(0x00000001)
#define BITW_2				(0x00000003)
#define BITW_3				(0x00000007)
#define BITW_4				(0x0000000F)
#define BITW_5				(0x0000001F)
#define BITW_6				(0x0000003F)
#define BITW_7				(0x0000007F)
#define BITW_8				(0x000000FF)
#define BITW_9				(0x000001FF)
#define BITW_10				(0x000003FF)
#define BITW_11				(0x000007FF)
#define BITW_12				(0x00000FFF)
#define BITW_13				(0x00001FFF)
#define BITW_14				(0x00003FFF)
#define BITW_15				(0x00007FFF)
#define BITW_16				(0x0000FFFF)
#define BITW_17				(0x0001FFFF)
#define BITW_18				(0x0003FFFF)
#define BITW_19				(0x0007FFFF)
#define BITW_20				(0x000FFFFF)
#define BITW_21				(0x001FFFFF)
#define BITW_22				(0x003FFFFF)
#define BITW_23				(0x007FFFFF)
#define BITW_24				(0x00FFFFFF)
#define BITW_25				(0x01FFFFFF)
#define BITW_26				(0x03FFFFFF)
#define BITW_27				(0x07FFFFFF)
#define BITW_28				(0x0FFFFFFF)
#define BITW_29				(0x1FFFFFFF)
#define BITW_30				(0x3FFFFFFF)
#define BITW_31				(0x7FFFFFFF)
#define BITW_32				(0xFFFFFFFF)

#define MK_MASK(w, sft)			(BITW_##w << sft)

#define MK_VAL(v, w, sft)		(((__u32)(v) & BITW_##w) << sft)
#define GET_VAL(v, w, sft)		(((__u32)(v) >> sft) & BITW_##w)
#define MK_VAL64(v, w, sft)		(((__u64)(v) & BITW_##w) << sft)

#define MK_V(v, w, sft)			(((__u32)(v) & (w)) << sft)
#define MK_V64(v, w, sft)		(((__u64)(v) & (w)) << sft)

#define GFX_REG(reg)			(GFX_##reg##_OFFS)
#define GFX_MSK(reg, fld)		(GFX_##reg##_##fld##_MASK)
#define GFX_SFT(reg, fld)		(GFX_##reg##_##fld##_SHIFT)
#define GFX_BIT(reg, fld)		(GFX_##reg##_##fld##_BIT)
#define GFX_WDH(reg, fld)		(GFX_##reg##_##fld##_BITWIDTH)

#define GFX_V(v, r, f)			MK_V(v, GFX_BIT(r, f), GFX_SFT(r, f))


/* Graphics Accelerator Scheduler Configuration Register */
#define GASCR_DISRA_MASK			GFX_MSK(GASCR, DISRA)
	#define GASCR_DISRA_ENABLE		GFX_V(0, GASCR, DISRA)
	#define GASCR_DISRA_DISABLE		GFX_V(1, GASCR, DISRA)
#define GASCR_GAEN_MASK				GFX_MSK(GASCR, GAEN)
	#define GASCR_GAEN_DISABLED		GFX_V(0, GASCR, GAEN)
	#define GASCR_GAEN_ENABLED		GFX_V(1, GASCR, GAEN)
#define GASCR_GARESET_MASK			GFX_MSK(GASCR, GARESET)
	#define GASCR_GARESET_OFF		GFX_V(0, GASCR, GARESET)
	#define GASCR_GARESET_ON		GFX_V(1, GASCR, GARESET)

/* Graphics Accelerator Command List Address Register */
#define GACLAR_CSLA_MASK			GFX_MSK(GACLAR, CSLA)

/* Graphics Accelerator Status Register */
/* (Read-Only) */
#define GASR_CSLEF_MASK				GFX_MSK(GASR, CSLEF)
	#define GASR_CSLEF_FINISHED		GFX_V(1, GASR, CSLEF)
#define GASR_CSCEF_MASK				GFX_MSK(GASR, CSCEF)
	#define GASR_CSCEF_INVALID_CMD		GFX_V(1, GASR, CSCEF)
#define GASR_BUSY_MASK				GFX_MSK(GASR, BUSY)
	#define GASR_BUSY_RUNNING		GFX_V(1, GASR, BUSY)

/* Graphics Accelerator Interrupt Cause Register */
#define GAICR_CSLUI_MASK			GFX_MSK(GAICR, CSLUI)
	#define GAICR_CSLUI_USER0		MK_V(1, GFX_BIT(GAICR, CSLUI), 8)
	#define GAICR_CSLUI_USER1		MK_V(1, GFX_BIT(GAICR, CSLUI), 9)
	#define GAICR_CSLUI_USER2		MK_V(1, GFX_BIT(GAICR, CSLUI), 10)
	#define GAICR_CSLUI_USER3		MK_V(1, GFX_BIT(GAICR, CSLUI), 11)
	#define GAICR_CSLUI_USER4		MK_V(1, GFX_BIT(GAICR, CSLUI), 12)
	#define GAICR_CSLUI_USER5		MK_V(1, GFX_BIT(GAICR, CSLUI), 13)
	#define GAICR_CSLUI_USER6		MK_V(1, GFX_BIT(GAICR, CSLUI), 14)
	#define GAICR_CSLUI_USER7		MK_V(1, GFX_BIT(GAICR, CSLUI), 15)
	#define GAICR_CSLUI_USER8		MK_V(1, GFX_BIT(GAICR, CSLUI), 16)
	#define GAICR_CSLUI_USER9		MK_V(1, GFX_BIT(GAICR, CSLUI), 17)
	#define GAICR_CSLUI_USER10		MK_V(1, GFX_BIT(GAICR, CSLUI), 18)
	#define GAICR_CSLUI_USER11		MK_V(1, GFX_BIT(GAICR, CSLUI), 19)
	#define GAICR_CSLUI_USER12		MK_V(1, GFX_BIT(GAICR, CSLUI), 20)
	#define GAICR_CSLUI_USER13		MK_V(1, GFX_BIT(GAICR, CSLUI), 21)
	#define GAICR_CSLUI_USER14		MK_V(1, GFX_BIT(GAICR, CSLUI), 22)
	#define GAICR_CSLUI_USER15		MK_V(1, GFX_BIT(GAICR, CSLUI), 23)
	#define GAICR_CSLUI_USER16		MK_V(1, GFX_BIT(GAICR, CSLUI), 24)
	#define GAICR_CSLUI_USER17		MK_V(1, GFX_BIT(GAICR, CSLUI), 25)
	#define GAICR_CSLUI_USER18		MK_V(1, GFX_BIT(GAICR, CSLUI), 26)
	#define GAICR_CSLUI_USER19		MK_V(1, GFX_BIT(GAICR, CSLUI), 27)
	#define GAICR_CSLUI_USER20		MK_V(1, GFX_BIT(GAICR, CSLUI), 28)
	#define GAICR_CSLUI_USER21		MK_V(1, GFX_BIT(GAICR, CSLUI), 29)
	#define GAICR_CSLUI_USER22		MK_V(1, GFX_BIT(GAICR, CSLUI), 30)
	#define GAICR_CSLUI_USER23		MK_V(1, GFX_BIT(GAICR, CSLUI), 31)
#define GAICR_GARBI_MASK			GFX_MSK(GAICR, GARBI)
	#define GAICR_GARBI_ERROR		GFX_V(1, GAICR, GARBI)
#define GAICR_GACBI_MASK			GFX_MSK(GAICR, GACBI)
	#define GAICR_GACBI_ERROR		GFX_V(1, GAICR, GACBI)
#define GAICR_GAWBRI_MASK			GFX_MSK(GAICR, GAWBRI)
	#define GAICR_GAWBRI_ERROR		GFX_V(1, GAICR, GAWBRI)
#define GAICR_GAWBWI_MASK			GFX_MSK(GAICR, GAWBWI)
	#define GAICR_GAWBWI_ERROR		GFX_V(1, GAICR, GAWBWI)
#define GAICR_CSLEI_MASK			GFX_MSK(GAICR, CSLEI)
	#define GAICR_CSLEI			GFX_V(1, GAICR, CSLEI)
#define GAICR_CSCEI_MASK			GFX_MSK(GAICR, CSCEI)
	#define GAICR_CSCEI_ERROR		GFX_V(1, GAICR, CSCEI)
#define GAICR_GACENDI_MASK			GFX_MSK(GAICR, GACENDI)
	#define GAICR_GACENDI			GFX_V(1, GAICR, GACENDI)

/* Graphics Accelerator Interrupt Mask Register */
#define GAIMR_CSLUIM_MASK			GFX_MSK(GAIMR, CSLUIM)
	#define GAIMR_CSLUIM_USER0_ENABLE	MK_V(1, GFX_BIT(GAIMR, CSLUIM), 8)
	#define GAIMR_CSLUIM_USER1_ENABLE	MK_V(1, GFX_BIT(GAIMR, CSLUIM), 9)
	#define GAIMR_CSLUIM_USER2_ENABLE	MK_V(1, GFX_BIT(GAIMR, CSLUIM), 10)
	#define GAIMR_CSLUIM_USER3_ENABLE	MK_V(1, GFX_BIT(GAIMR, CSLUIM), 11)
	#define GAIMR_CSLUIM_USER4_ENABLE	MK_V(1, GFX_BIT(GAIMR, CSLUIM), 12)
	#define GAIMR_CSLUIM_USER5_ENABLE	MK_V(1, GFX_BIT(GAIMR, CSLUIM), 13)
	#define GAIMR_CSLUIM_USER6_ENABLE	MK_V(1, GFX_BIT(GAIMR, CSLUIM), 14)
	#define GAIMR_CSLUIM_USER7_ENABLE	MK_V(1, GFX_BIT(GAIMR, CSLUIM), 15)
	#define GAIMR_CSLUIM_USER8_ENABLE	MK_V(1, GFX_BIT(GAIMR, CSLUIM), 16)
	#define GAIMR_CSLUIM_USER9_ENABLE	MK_V(1, GFX_BIT(GAIMR, CSLUIM), 17)
	#define GAIMR_CSLUIM_USER10_ENABLE	MK_V(1, GFX_BIT(GAIMR, CSLUIM), 18)
	#define GAIMR_CSLUIM_USER11_ENABLE	MK_V(1, GFX_BIT(GAIMR, CSLUIM), 19)
	#define GAIMR_CSLUIM_USER12_ENABLE	MK_V(1, GFX_BIT(GAIMR, CSLUIM), 20)
	#define GAIMR_CSLUIM_USER13_ENABLE	MK_V(1, GFX_BIT(GAIMR, CSLUIM), 21)
	#define GAIMR_CSLUIM_USER14_ENABLE	MK_V(1, GFX_BIT(GAIMR, CSLUIM), 22)
	#define GAIMR_CSLUIM_USER15_ENABLE	MK_V(1, GFX_BIT(GAIMR, CSLUIM), 23)
	#define GAIMR_CSLUIM_USER16_ENABLE	MK_V(1, GFX_BIT(GAIMR, CSLUIM), 24)
	#define GAIMR_CSLUIM_USER17_ENABLE	MK_V(1, GFX_BIT(GAIMR, CSLUIM), 25)
	#define GAIMR_CSLUIM_USER18_ENABLE	MK_V(1, GFX_BIT(GAIMR, CSLUIM), 26)
	#define GAIMR_CSLUIM_USER19_ENABLE	MK_V(1, GFX_BIT(GAIMR, CSLUIM), 27)
	#define GAIMR_CSLUIM_USER20_ENABLE	MK_V(1, GFX_BIT(GAIMR, CSLUIM), 28)
	#define GAIMR_CSLUIM_USER21_ENABLE	MK_V(1, GFX_BIT(GAIMR, CSLUIM), 29)
	#define GAIMR_CSLUIM_USER22_ENABLE	MK_V(1, GFX_BIT(GAIMR, CSLUIM), 30)
	#define GAIMR_CSLUIM_USER23_ENABLE	MK_V(1, GFX_BIT(GAIMR, CSLUIM), 31)
#define GAIMR_GARBIM_MASK			GFX_MSK(GAIMR, GARBIM)
	#define GAIMR_GARBIM_ENABLE		MK_VAL(1, GAIMR, GARBIM)
#define GAIMR_GACBIM_MASK			GFX_MSK(GAIMR, GACBIM)
	#define GAIMR_GACBIM_ENABLE		MK_VAL(1, GAIMR, GACBIM)
#define GAIMR_GAWBRIM_MASK			GFX_MSK(GAIMR, GAWBRIM)
	#define GAIMR_GAWBRIM_ENABLE		MK_VAL(1, GAIMR, GAWBRIM)
#define GAIMR_GAWBWIM_MASK			GFX_MSK(GAIMR, GAWBWIM)
	#define GAIMR_GAWBWIM_ENABLE		MK_VAL(1, GAIMR, GAWBWIM)
#define GAIMR_CSLEIM_MASK			GFX_MSK(GAIMR, CSLEIM)
	#define GAIMR_CSLEIM_ENABLE		MK_VAL(1, GAIMR, CSLEIM)
#define GAIMR_CSCEIM_MASK			GFX_MSK(GAIMR, CSCEIM)
	#define GAIMR_CSCEIM_ENABLE		MK_VAL(1, GAIMR, CSCEIM)
#define GAIMR_GACENDIM_MASK			GFX_MSK(GAIMR, GACENDIM)
	#define GAIMR_GACENDIM_ENABLE		MK_VAL(1, GAIMR, GACENDIM)

/* Graphics Accelerator Delay Register */
#define GADR_GAD_MASK				GFX_MSK(GADR, GAD)

/* Graphics Accelerator Read Buffer Bus Error Address Register */
/* (Read-Only) */
#define GARBBEAR_RBA_MASK			GFX_MSK(GARBBEAR, RBA)

#define _LEN_VAL(v)				GET_VAL(v, 4, 20)
#define _ID_VAL(v)				GET_VAL(v, 4, 16)
#define _BEN_VAL(v)				GET_VAL(v, 8, 8)
#define _RTYPE_VAL(v)				GET_VAL(v, 2, 5)
#define _RTYPE_OKAY				GFX_V(0, GARBBEAR, RTYPE)
#define _RTYPE_EXOKAY				GFX_V(1, GARBBEAR, RTYPE)
#define _RTYPE_SLVERR				GFX_V(2, GARBBEAR, RTYPE)
#define _RTYPE_DECERR				GFX_V(3, GARBBEAR, RTYPE)
#define _BSIZE_VAL(v)				GET_VAL(v, 3, 2)
#define _BSIZE_1BYTE				GFX_V(0, GARBBEAR, BSIZE)
#define _BSIZE_2BYTE				GFX_V(1, GARBBEAR, BSIZE)
#define _BSIZE_4BYTE				GFX_V(2, GARBBEAR, BSIZE)
#define _BSIZE_8BYTE				GFX_V(3, GARBBEAR, BSIZE)
#define _BSIZE_16BYTE				GFX_V(4, GARBBEAR, BSIZE)
#define _BSIZE_32BYTE				GFX_V(5, GARBBEAR, BSIZE)
#define _BSIZE_64BYTE				GFX_V(6, GARBBEAR, BSIZE)
#define _BSIZE_128BYTE				GFX_V(7, GARBBEAR, BSIZE)
#define _BTYPE_VAL(v)				GET_VAL(v, 1, 1)
#define _BTYPE_FIXED				GFX_V(0, GARBBEAR, BTYPE)
#define _BTYPE_WRAP				GFX_V(0, GARBBEAR, BTYPE)
#define _BTYPE_INCR				GFX_V(1, GARBBEAR, BTYPE)
#define _WR_VAL(v)				GET_VAL(v, 1, 0)
#define _WR_READ				GFX_V(0, GARBBEAR, WR)
#define _WR_WRITE				GFX_V(1, GARBBEAR, WR)

/* Graphics Accelerator Read Buffer Bus Error Control Register */
/* (Read-Only) */
#define GARBBECR_LEN_MASK			GFX_MSK(GARBBECR, LEN)
#define GARBBECR_ID_MASK			GFX_MSK(GARBBECR, ID)
#define GARBBECR_BEN_MASK			GFX_MSK(GARBBECR, BEN)
#define GARBBECR_RTYPE_MASK			GFX_MSK(GARBBECR, RTYPE)
#define GARBBECR_BSIZE_MASK			GFX_MSK(GARBBECR, BSIZE)
#define GARBBECR_BTYPE_MASK			GFX_MSK(GARBBECR, BTYPE)
#define GARBBECR_WR_MASK			GFX_MSK(GARBBECR, WR)

/* Graphics Accelerator Cache Buffer Bus Error Address Register */
/* (Read-Only) */
#define GACBBEAR_CBA_MASK			GFX_MSK(GACBBEAR, CBA)

/* Graphics Accelerator Cache Buffer Bus Error Control Register */
#define GACBBECR_LEN_MASK			GFX_MSK(GACBBECR, LEN)
#define GACBBECR_ID_MASK			GFX_MSK(GACBBECR, ID)
#define GACBBECR_BEN_MASK			GFX_MSK(GACBBECR, BEN)
#define GACBBECR_RTYPE_MASK			GFX_MSK(GACBBECR, RTYPE)
#define GACBBECR_BSIZE_MASK			GFX_MSK(GACBBECR, BSIZE)
#define GACBBECR_BTYPE_MASK			GFX_MSK(GACBBECR, BTYPE)
#define GACBBECR_WR_MASK			GFX_MSK(GACBBECR, WR)

/* Graphics Accelerator Write Buffer Read Bus Error Address Register */
/* (Read-Only) */
#define GAWBRBEAR_WBRA_MASK			GFX_MSK(GAWBRBEAR, WBRA)

/* Graphics Accelerator Write Buffer Read Bus Error Control Register */
/*#define GAWBRBECR_OFFS				(0x0034)*/
#define GAWBRBECR_LEN_MASK			GFX_MSK(GAWBRBECR, LEN)
#define GAWBRBECR_ID_MAKS			GFX_MSK(GAWBRBECR, ID)
#define GAWBRBECR_BEN_MASK			GFX_MSK(GAWBRBECR, BEN)
#define GAWBRBECR_RTYPE_MASK			GFX_MSK(GAWBRBECR, RTYPE)
#define GAWBRBECR_BSIZE_MASK			GFX_MSK(GAWBRBECR, BSIZE)
#define GAWBRBECR_BTYPE_MASK			GFX_MSK(GAWBRBECR, BTYPE)
#define GAWBRBECR_WR_MASK			GFX_MSK(GAWBRBECR, WR)

/* Graphics Accelerator Write Buffer Write Bus Error Address Register */
/* (Read-Only) */
#define GAWBWBEAR_WBWA_MASK			GFX_MSK(GAWBWBEAR, WBWA)

/* Graphics Accelerator Write Buffer Write Bus Error Control Register */
#define GAWBWBECR_LEN_MASK			GFX_MSK(GAWBWBECR, LEN)
#define GAWBWBECR_ID_MASK			GFX_MSK(GAWBWBECR, ID)
#define GAWBWBECR_BEN_MASK			GFX_MSK(GAWBWBECR, BEN)
#define GAWBWBECR_RTYPE_MASK			GFX_MSK(GAWBWBECR, RTYPE)
#define GAWBWBECR_BSIZE_MASK			GFX_MSK(GAWBWBECR, BSIZE)
#define GAWBWBECR_BTYPE_MASK			GFX_MSK(GAWBWBECR, BTYPE)
#define GAWBWBWCR_WR_MASK			GFX_MSK(GAWBWBECR, WR)

/* Graphics Accelerator Memory Protection Region 0 Low Register */
#define GAMPR0LR_MPR0L_MASK			GFX_MSK(GAMPR0LR, MPR0L)

/* Graphics Accelerator Memory Protection Region 0 High Register */
#define GAMPR0HR_MPR0H_MASK			GFX_MSK(GAMPR0HR, MPR0H)

/* Graphics Accelerator Memory Protection Region 1 Low Register */
#define GAMPR1LR_MPR1L_MASK			GFX_MSK(GAMPR1LR, MPR1L)

/* Graphics Accelerator Memory Protection Region 1 High Register */
#define GAMPR1HR_MPR1H_MASK			GFX_MSK(GAMPR1HR, MPR1H)

/* Graphics Accelerator Memory protection Interrupt Cause Register */
#define GAMPICR_GAMPCI_MASK			GFX_MSK(GAMPICR, GAMPCI)
#define GAMPICR_GAMPI_MASK			GFX_MSK(GAMPICR, GAMPI)

/* Graphics Accelerator Memory protection Interrupt Mask Register */
#define GAMPIMR_GAMPCIM_MASK			GFX_MSK(GAMPIMR, GAMPCIM)
	#define GAMPIMR_GAMPCIM_ENABLE		GFX_V(1, GAMPIMR, GAMPCIM)
#define GAMPIMR_GAMPIM_MASK			GFX_MSK(GAMPIMR, GAMPIM)
	#define GAMPIMR_GAMPIM_ENABLE		GFX_V(1, GAMPIMR, GAMPIM)

/* Graphics Accelerator Memory protection Address Capture Register */
/* (Read-Only) */
#define GAMPACR_MPVA_MASK			GFX_MSK(GAMPACR, MPVA)

/* Graphics Accelerator General Purpose Register n */
#define GAGPR_OFFS(n)				(GFX_REG(GAGPR) + (4 * n))

/* Graphics Accelerator Command Code Low Register */

/* Graphics Accelerator Command Code High Register */

/* Drawing Engine Filter Coefficient Register n */
#define DEFC_OFFS(n)				(GFX_REG(DEFC0) + (4 * n))
#define DEFC_FC0_MASK				GFX_MSK(DEFC0, FC0)
#define DEFC_FC1_MASK				GFX_MSK(DEFC0, FC1)
#define DEFC_FC2_MASK				GFX_MSK(DEFC0, FC2)
#define DEFC_FC3_MASK				GFX_MSK(DEFC0, FC3)
#define DEFC_FC_MASK(n)		((n) & 0x3 ? DEFC_FC3_MASK : ((n) & 0x2 ? DEFC_FC2_MASK : ((n) & 0x1 ? DEFC_FC1_MASK : DEFC_FC0_MASK)))
#define DEFC_VAL(f0, f1, f2, f3)		\
		(MK_VAL(f0, 8, 24) | MK_VAL(f1, 8, 16) | MK_VAL(f2, 8, 8) | \
		 MK_VAL(f3, 8, 0))




/*===================================
Exported Variables
===================================*/



/*===================================
Exported Functions prototypes
===================================*/

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* __TZ2000_REGS_H__ */

