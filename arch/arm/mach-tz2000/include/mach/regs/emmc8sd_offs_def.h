/*
 * arch/arm/mach-tz2000/include/mach/regs/emmc8sd_offs_def.h
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
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef EMMC8SD_OFFS_DEF_H
#define EMMC8SD_OFFS_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

#define EMMC8SD_SDMA_System_Address_Argument_2_OFFS 0x00000000
#define EMMC8SD_Block_Count_Block_Size_OFFS 0x00000004
#define EMMC8SD_Argument_1_OFFS        0x00000008
#define EMMC8SD_Command_Transfer_Mode_OFFS 0x0000000C
#define EMMC8SD_Response_0_OFFS        0x00000010
#define EMMC8SD_Response_1_OFFS        0x00000014
#define EMMC8SD_Response_2_OFFS        0x00000018
#define EMMC8SD_Response_3_OFFS        0x0000001C
#define EMMC8SD_Buffer_Data_Port_OFFS  0x00000020
#define EMMC8SD_Present_State_OFFS     0x00000024
#define EMMC8SD_Wakeup_Control_Block_Gap_Control_Power_Control_Host_Control_1_OFFS 0x00000028
#define EMMC8SD_Software_Reset_Timeout_Control_Clock_Control_OFFS 0x0000002C
#define EMMC8SD_Error_Interrupt_Status_Normal_Interrupt_Status_OFFS 0x00000030
#define EMMC8SD_Error_Interrupt_Status_Enable_Normal_Interrupt_Status_Enable_OFFS 0x00000034
#define EMMC8SD_Error_Interrupt_Signal_Enable_Normal_Interrupt_Signal_Enable_OFFS 0x00000038
#define EMMC8SD_Host_Control_2_Auto_CMD_Error_Status_OFFS 0x0000003C
#define EMMC8SD_Capabilities_0_OFFS    0x00000040
#define EMMC8SD_Capabilities_1_OFFS    0x00000044
#define EMMC8SD_Maximum_Current_Capabilities_OFFS 0x00000048
#define EMMC8SD_Force_Event_for_Error_Interrupt_Status_Force_Event_for_Auto_CMD_Error_Status_OFFS 0x00000050
#define EMMC8SD_ADMA_Error_Status_OFFS 0x00000054
#define EMMC8SD_ADMA_System_Address_0_OFFS 0x00000058
#define EMMC8SD_ADMA_System_Address_1_OFFS 0x0000005C
#define EMMC8SD_Preset_Value_for_Default_Speed_Initialization_OFFS 0x00000060
#define EMMC8SD_Preset_Value_for_SDR12_High_Speed_OFFS 0x00000064
#define EMMC8SD_Preset_Value_for_SDR50_SDR25_OFFS 0x00000068
#define EMMC8SD_Preset_Value_for_DDR50_SDR104_OFFS 0x0000006C
#define EMMC8SD_Boot_Timeout_Control_OFFS 0x00000070
#define EMMC8SD_Shared_Bus_Control_OFFS 0x000000E0
#define EMMC8SD_Host_Controller_Version_Slot_Interrupt_Status_OFFS 0x000000FC

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* EMMC8SD_OFFS_DEF_H */
