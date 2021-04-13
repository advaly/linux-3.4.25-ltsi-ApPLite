/*
 * arch/arm/mach-tz3000/include/mach/regs/emmcc_offs_def.h
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

#ifndef EMMCC_OFFS_DEF_H
#define EMMCC_OFFS_DEF_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */

#define EMMCC_SDMA_System_Address_Argument_2_OFFS 0x00000000
#define EMMCC_Block_Count_Block_Size_OFFS 0x00000004
#define EMMCC_Argument_1_OFFS          0x00000008
#define EMMCC_Command_Transfer_Mode_OFFS 0x0000000C
#define EMMCC_Response_0_OFFS          0x00000010
#define EMMCC_Response_1_OFFS          0x00000014
#define EMMCC_Response_2_OFFS          0x00000018
#define EMMCC_Response_3_OFFS          0x0000001C
#define EMMCC_Buffer_Data_Port_OFFS    0x00000020
#define EMMCC_Present_State_OFFS       0x00000024
#define EMMCC_Wakeup_Control_Block_Gap_Control_Power_Control_Host_Control_1_OFFS 0x00000028
#define EMMCC_Software_Reset_Timeout_Control_Clock_Control_OFFS 0x0000002C
#define EMMCC_Error_Interrupt_Status_Normal_Interrupt_Status_OFFS 0x00000030
#define EMMCC_Error_Interrupt_Status_Enable_Normal_Interrupt_Status_Enable_OFFS 0x00000034
#define EMMCC_Error_Interrupt_Signal_Enable_Normal_Interrupt_Signal_Enable_OFFS 0x00000038
#define EMMCC_Host_Control_2_Auto_CMD_Error_Status_OFFS 0x0000003C
#define EMMCC_Capabilities_0_OFFS      0x00000040
#define EMMCC_Capabilities_1_OFFS      0x00000044
#define EMMCC_Maximum_Current_Capabilities_OFFS 0x00000048
#define EMMCC_Force_Event_for_Error_Interrupt_Status_Force_Event_for_Auto_CMD_Error_Status_OFFS 0x00000050
#define EMMCC_ADMA_Error_Status_OFFS   0x00000054
#define EMMCC_ADMA_System_Address_0_OFFS 0x00000058
#define EMMCC_ADMA_System_Address_1_OFFS 0x0000005C
#define EMMCC_Preset_Value_for_Default_Speed_Initialization_OFFS 0x00000060
#define EMMCC_Preset_Value_for_SDR12_High_Speed_OFFS 0x00000064
#define EMMCC_Preset_Value_for_SDR50_SDR25_OFFS 0x00000068
#define EMMCC_Preset_Value_for_DDR50_SDR104_OFFS 0x0000006C
#define EMMCC_Boot_Timeout_Control_OFFS 0x00000070
#define EMMCC_Shared_Bus_Control_OFFS  0x000000E0
#define EMMCC_Host_Controller_Version_Slot_Interrupt_Status_OFFS 0x000000FC

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* EMMCC_OFFS_DEF_H */
