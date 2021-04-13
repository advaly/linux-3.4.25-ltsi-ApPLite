/*
 * arch/arm/mach-tz3000/include/mach/regs/emmcc_reg_struct_b.h
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

#ifndef _EMMCC_REG_STRUCT_B_H
#define _EMMCC_REG_STRUCT_B_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // SDMA_System_Address_Argument_2 Register
struct EMMCC_SDMA_SYSTEM_ADDRESS_ARGUMENT_2 {
	unsigned int SDMA_System_Address_Argument_2:32;		// [31:0]
};
 // Block_Count_Block_Size Register
struct EMMCC_BLOCK_COUNT_BLOCK_SIZE {
	unsigned int Blocks_Count_for_Current_Transfer:16;		// [31:16]
	unsigned int Reserved:1;		// [15]
	unsigned int Host_SDMA_Buffer_Size:3;		// [14:12]
	unsigned int Transfer_Block_Size:12;		// [11:0]
};
 // Argument_1 Register
struct EMMCC_ARGUMENT_1 {
	unsigned int Command_Argument_1:32;		// [31:0]
};
 // Command_Transfer_Mode Register
struct EMMCC_COMMAND_TRANSFER_MODE {
	unsigned int Reserved:2;		// [31:30]
	unsigned int Command_Index:6;		// [29:24]
	unsigned int Command_Type:2;		// [23:22]
	unsigned int Data_Present_Select:1;		// [21]
	unsigned int Command_Index_Check_Enable:1;		// [20]
	unsigned int Command_CRC_Check_Enable:1;		// [19]
	unsigned int Reserved2:1;		// [18]
	unsigned int Response_Type_Select:2;		// [17:16]
	unsigned int Reserved3:10;		// [15:6]
	unsigned int Multi_Single_Block_Select:1;		// [5]
	unsigned int Data_Transfer_Direction_Select:1;		// [4]
	unsigned int Auto_CMD_Enable:2;		// [3:2]
	unsigned int Block_Count_Enable:1;		// [1]
	unsigned int DMA_Enable:1;		// [0]
};
 // Response_0 Register
struct EMMCC_RESPONSE_0 {
	unsigned int Command_Response_0:32;		// [31:0]
};
 // Response_1 Register
struct EMMCC_RESPONSE_1 {
	unsigned int Command_Response_1:32;		// [31:0]
};
 // Response_2 Register
struct EMMCC_RESPONSE_2 {
	unsigned int Command_Response_2:32;		// [31:0]
};
 // Response_3 Register
struct EMMCC_RESPONSE_3 {
	unsigned int Command_Response_3:32;		// [31:0]
};
 // Buffer_Data_Port Register
struct EMMCC_BUFFER_DATA_PORT {
	unsigned int Buffer_Data:32;		// [31:0]
};
 // Present_State Register
struct EMMCC_PRESENT_STATE {
	unsigned int Reserved:3;		// [31:29]
	unsigned int DAT_Upper_Line_Signal_Level:4;		// [28:25]
	unsigned int CMD_Line_Signal_Level:1;		// [24]
	unsigned int DAT_Lower_Line_Signal_Level:4;		// [23:20]
	unsigned int Write_Protect_Switch_Pin_Level:1;		// [19]
	unsigned int Card_Detect_Pin_Level:1;		// [18]
	unsigned int Card_State_Stable:1;		// [17]
	unsigned int Card_Inserted:1;		// [16]
	unsigned int Reserved2:4;		// [15:12]
	unsigned int Buffer_Read_Enable:1;		// [11]
	unsigned int Buffer_Write_Enable:1;		// [10]
	unsigned int Read_Transfer_Active:1;		// [9]
	unsigned int Write_Transfer_Active:1;		// [8]
	unsigned int Reserved3:4;		// [7:4]
	unsigned int Re_Tuning_Request:1;		// [3]
	unsigned int DAT_Line_Active:1;		// [2]
	unsigned int Command_Inhibit_DAT:1;		// [1]
	unsigned int Command_Inhibit_CMD:1;		// [0]
};
 // Wakeup_Control_Block_Gap_Control_Power_Control_Host_Control_1 Register
struct EMMCC_WAKEUP_CONTROL_BLOCK_GAP_CONTROL_POWER_CONTROL_HOST_CONTROL_1 {
	unsigned int Reserved:5;		// [31:27]
	unsigned int Wakeup_Event_Enable_On_SD_Card_Removal:1;		// [26]
	unsigned int Wakeup_Event_Enable_On_SD_Card_Insertion:1;		// [25]
	unsigned int Wakeup_Event_Enable_On_Card_Interrupt:1;		// [24]
	unsigned int boot_ack_chk:1;		// [23]
	unsigned int alt_boot_en:1;		// [22]
	unsigned int BOOT_EN:1;		// [21]
	unsigned int SPI_MODE:1;		// [20]
	unsigned int Interrupt_At_Block_Gap:1;		// [19]
	unsigned int Read_Wait_Control:1;		// [18]
	unsigned int Continue_Request:1;		// [17]
	unsigned int Stop_At_Block_Gap_Request:1;		// [16]
	unsigned int Reserved2:4;		// [15:12]
	unsigned int SD_Bus_Voltage_Select:3;		// [11:9]
	unsigned int SD_Bus_Power:1;		// [8]
	unsigned int Card_detect_signal_detection:1;		// [7]
	unsigned int Card_Detect_Test_Level:1;		// [6]
	unsigned int Extended_Data_Transfer_Width:1;		// [5]
	unsigned int DMA_Select:2;		// [4:3]
	unsigned int High_Speed_Enable:1;		// [2]
	unsigned int Data_Transfer_Width:1;		// [1]
	unsigned int LED_Control:1;		// [0]
};
 // Software_Reset_Timeout_Control_Clock_Control Register
struct EMMCC_SOFTWARE_RESET_TIMEOUT_CONTROL_CLOCK_CONTROL {
	unsigned int Reserved:5;		// [31:27]
	unsigned int Software_Reset_for_DAT_Line:1;		// [26]
	unsigned int Software_Reset_for_CMD_Line:1;		// [25]
	unsigned int Software_Reset_for_All:1;		// [24]
	unsigned int Reserved2:4;		// [23:20]
	unsigned int Data_Timeout_Counter_Value:4;		// [19:16]
	unsigned int SDCLK_Frequency_Select:8;		// [15:8]
	unsigned int Upper_Bits_of_SDCLK_Frequency_Select:2;		// [7:6]
	unsigned int Clock_Generator_Select:1;		// [5]
	unsigned int Reserved3:2;		// [4:3]
	unsigned int SD_Clock_Enable:1;		// [2]
	unsigned int Internal_Clock_Stable:1;		// [1]
	unsigned int Internal_Clock_Enable:1;		// [0]
};
 // Error_Interrupt_Status_Normal_Interrupt_Status Register
struct EMMCC_ERROR_INTERRUPT_STATUS_NORMAL_INTERRUPT_STATUS {
	unsigned int Vendor_Specific_Error_Status:3;		// [31:29]
	unsigned int Target_Response_error:1;		// [28]
	unsigned int Reserved:1;		// [27]
	unsigned int Tuning_Error:1;		// [26]
	unsigned int ADMA_Error:1;		// [25]
	unsigned int Auto_CMD_Error:1;		// [24]
	unsigned int Current_Limit_Error:1;		// [23]
	unsigned int Data_End_Bit_Error:1;		// [22]
	unsigned int Data_CRC_Error:1;		// [21]
	unsigned int Data_Timeout_Error:1;		// [20]
	unsigned int Command_Index_Error:1;		// [19]
	unsigned int Command_End_Bit_Error:1;		// [18]
	unsigned int Command_CRC_Error:1;		// [17]
	unsigned int Command_Timeout_Error:1;		// [16]
	unsigned int Error_Interrupt:1;		// [15]
	unsigned int Boot_terminate_Interrupt:1;		// [14]
	unsigned int Boot_ack_rcv:1;		// [13]
	unsigned int Re_Tuning_Event:1;		// [12]
	unsigned int INT_C:1;		// [11]
	unsigned int INT_B:1;		// [10]
	unsigned int INT_A:1;		// [9]
	unsigned int Card_Interrupt:1;		// [8]
	unsigned int Card_Removal:1;		// [7]
	unsigned int Card_Insertion:1;		// [6]
	unsigned int Buffer_Read_Ready:1;		// [5]
	unsigned int Buffer_Write_Ready:1;		// [4]
	unsigned int DMA_Interrupt:1;		// [3]
	unsigned int Block_Gap_Event:1;		// [2]
	unsigned int Transfer_Complete:1;		// [1]
	unsigned int Command_Complete:1;		// [0]
};
 // Error_Interrupt_Status_Enable_Normal_Interrupt_Status_Enable Register
struct EMMCC_ERROR_INTERRUPT_STATUS_ENABLE_NORMAL_INTERRUPT_STATUS_ENABLE {
	unsigned int Vendor_Specific_Error_Status_Enable:3;		// [31:29]
	unsigned int Target_Response_Error_Status_Enable:1;		// [28]
	unsigned int Reserved:1;		// [27]
	unsigned int tuning_Error_Status_Enable:1;		// [26]
	unsigned int ADMA_Error_Status_Enable:1;		// [25]
	unsigned int Auto_CMD12_Error_Status_Enable:1;		// [24]
	unsigned int Current_Limit_Error_Status_Enable:1;		// [23]
	unsigned int Data_End_Bit_Error_Status_Enable:1;		// [22]
	unsigned int Data_CRC_Error_Status_Enable:1;		// [21]
	unsigned int Data_Timeout_Error_Status_Enable:1;		// [20]
	unsigned int Command_Index_Error_Status_Enable:1;		// [19]
	unsigned int Command_End_Bit_Error_Status_Enable:1;		// [18]
	unsigned int Command_CRC_Error_Status_Enable:1;		// [17]
	unsigned int Command_Timeout_Error_Status_Enable:1;		// [16]
	unsigned int Fixed_to_0:1;		// [15]
	unsigned int Boot_terminate_Interrupt_enable:1;		// [14]
	unsigned int Boot_ack_rcv_enable:1;		// [13]
	unsigned int Re_Tuning_Event_Status_Enable:1;		// [12]
	unsigned int INT_C_Status_Enable:1;		// [11]
	unsigned int INT_B_Status_Enable:1;		// [10]
	unsigned int INT_A_Status_Enable:1;		// [9]
	unsigned int Card_Interrupt_Status_Enable:1;		// [8]
	unsigned int Card_Removal_Status_Enable:1;		// [7]
	unsigned int Card_Insertion_Status_Enable:1;		// [6]
	unsigned int Buffer_Read_Ready_Status_Enable:1;		// [5]
	unsigned int Buffer_Write_Ready_Status_Enable:1;		// [4]
	unsigned int DMA_Interrupt_Status_Enable:1;		// [3]
	unsigned int Block_Gap_Event_Status_Enable:1;		// [2]
	unsigned int Transfer_Complete_Status_Enable:1;		// [1]
	unsigned int Command_Complete_Status_Enable:1;		// [0]
};
 // Error_Interrupt_Signal_Enable_Normal_Interrupt_Signal_Enable Register
struct EMMCC_ERROR_INTERRUPT_SIGNAL_ENABLE_NORMAL_INTERRUPT_SIGNAL_ENABLE {
	unsigned int Vendor_Specific_Error_Signal_Enable:3;		// [31:29]
	unsigned int Target_Response_Error_Signal_Enable:1;		// [28]
	unsigned int Reserved:1;		// [27]
	unsigned int Tuning_Error_Signal_Enable:1;		// [26]
	unsigned int ADMA_Error_Signal_Enable:1;		// [25]
	unsigned int Auto_CMD12_Error_Signal_Enable:1;		// [24]
	unsigned int Current_Limit_Error_Signal_Enable:1;		// [23]
	unsigned int Data_End_Bit_Error_Signal_Enable:1;		// [22]
	unsigned int Data_CRC_Error_Signal_Enable:1;		// [21]
	unsigned int Data_Timeout_Error_Signal_Enable:1;		// [20]
	unsigned int Command_Index_Error_Signal_Enable:1;		// [19]
	unsigned int Command_End_Bit_Error_Signal_Enable:1;		// [18]
	unsigned int Command_CRC_Error_Signal_Enable:1;		// [17]
	unsigned int Command_Timeout_Error_Signal_Enable:1;		// [16]
	unsigned int Fixed_to_0:1;		// [15]
	unsigned int Boot_terminate_Interrupt_signal_enable:1;		// [14]
	unsigned int Boot_ack_rcv_signal_enable:1;		// [13]
	unsigned int Re_Tuning_Event_signal_Enable:1;		// [12]
	unsigned int INT_C_signal_Enable:1;		// [11]
	unsigned int INT_B_signal_Enable:1;		// [10]
	unsigned int INT_A_signal_Enable:1;		// [9]
	unsigned int Card_Interrupt_Signal_Enable:1;		// [8]
	unsigned int Card_Removal_Signal_Enable:1;		// [7]
	unsigned int Card_Insertion_Signal_Enable:1;		// [6]
	unsigned int Buffer_Read_Ready_Signal_Enable:1;		// [5]
	unsigned int Buffer_Write_Ready_Signal_Enable:1;		// [4]
	unsigned int DMA_Interrupt_Signal_Enable:1;		// [3]
	unsigned int Block_Gap_Event_Signal_Enable:1;		// [2]
	unsigned int Transfer_Complete_Signal_Enable:1;		// [1]
	unsigned int Command_Complete_Signal_Enable:1;		// [0]
};
 // Host_Control_2_Auto_CMD_Error_Status Register
struct EMMCC_HOST_CONTROL_2_AUTO_CMD_ERROR_STATUS {
	unsigned int Preset_Value_Enable:1;		// [31]
	unsigned int Asynchronous_Interrupt_Enable:1;		// [30]
	unsigned int Reserved:6;		// [29:24]
	unsigned int Sampling_Clock_Select:1;		// [23]
	unsigned int Execute_Tuning:1;		// [22]
	unsigned int Driver_Strength_Select:2;		// [21:20]
	unsigned int Enable_1p8V_Signaling:1;		// [19]
	unsigned int UHS_Mode_Select:3;		// [18:16]
	unsigned int Reserved2:8;		// [15:8]
	unsigned int Command_Not_Issued_By_Auto_CMD12_Error:1;		// [7]
	unsigned int Reserved3:2;		// [6:5]
	unsigned int Auto_CMD_Index_Error:1;		// [4]
	unsigned int Auto_CMD_End_Bit_Error:1;		// [3]
	unsigned int Auto_CMD_CRC_Error:1;		// [2]
	unsigned int Auto_CMD_Timeout_Error:1;		// [1]
	unsigned int Auto_CMD12_not_Executed:1;		// [0]
};
 // Capabilities_0 Register
struct EMMCC_CAPABILITIES_0 {
	unsigned int Slot_Type:2;		// [31:30]
	unsigned int Asynchronous_Interrupt_Support:1;		// [29]
	unsigned int Support_64bit_System_Bus:1;		// [28]
	unsigned int Reserved:1;		// [27]
	unsigned int Voltage_Support_1p8V:1;		// [26]
	unsigned int Voltage_Support_3p0V:1;		// [25]
	unsigned int Voltage_Support_3p3V:1;		// [24]
	unsigned int Suspend_Resume_Support:1;		// [23]
	unsigned int SDMA_Support:1;		// [22]
	unsigned int High_Speed_Support:1;		// [21]
	unsigned int Reserved2:1;		// [20]
	unsigned int ADMA2_Support:1;		// [19]
	unsigned int Extended_Media_Bus_Support:1;		// [18]
	unsigned int Max_Block_Length:2;		// [17:16]
	unsigned int Base_Clock_Frequency_for_SD_Clock:8;		// [15:8]
	unsigned int Timeout_Clock_Unit:1;		// [7]
	unsigned int Reserved3:1;		// [6]
	unsigned int Timeout_Clock_Frequency:6;		// [5:0]
};
 // Capabilities_1 Register
struct EMMCC_CAPABILITIES_1 {
	unsigned int Reserved:6;		// [31:26]
	unsigned int SPI_block_mode:1;		// [25]
	unsigned int SPI_mode:1;		// [24]
	unsigned int Clock_Multiplier:8;		// [23:16]
	unsigned int Re_tuning_modes:2;		// [15:14]
	unsigned int Use_Tuning_for_SDR50:1;		// [13]
	unsigned int Reserved2:1;		// [12]
	unsigned int Timer_count_for_Re_Tuning:4;		// [11:8]
	unsigned int Reserved3:1;		// [7]
	unsigned int Driver_Type_D_Support:1;		// [6]
	unsigned int Driver_Type_C_Support:1;		// [5]
	unsigned int Driver_Type_A_Support:1;		// [4]
	unsigned int Reserved4:1;		// [3]
	unsigned int DDR50_Support:1;		// [2]
	unsigned int SDR104_Support:1;		// [1]
	unsigned int SDR50_Support:1;		// [0]
};
 // Maximum_Current_Capabilities Register
struct EMMCC_MAXIMUM_CURRENT_CAPABILITIES {
	unsigned int Reserved:8;		// [31:24]
	unsigned int Maximum_Current_for_1p8V:8;		// [23:16]
	unsigned int Maximum_Current_for_3p0V:8;		// [15:8]
	unsigned int Maximum_Current_for_3p3V:8;		// [7:0]
};
 // Force_Event_for_Error_Interrupt_Status_Force_Event_for_Auto_CMD_Error_Status Register
struct EMMCC_FORCE_EVENT_FOR_ERROR_INTERRUPT_STATUS_FORCE_EVENT_FOR_AUTO_CMD_ERROR_STATUS {
	unsigned int Force_Event_for_Vendor_Specific_Error_Status:3;		// [31:29]
	unsigned int Force_event_for_Target_Response_error:1;		// [28]
	unsigned int Reserved:2;		// [27:26]
	unsigned int Force_Event_for_ADMA_Error:1;		// [25]
	unsigned int Force_Event_for_Auto_CMD_Error:1;		// [24]
	unsigned int Force_Event_for_Current_Limit_Error:1;		// [23]
	unsigned int Force_Event_for_Data_End_Bit_Error:1;		// [22]
	unsigned int Force_Event_for_Data_CRC_Error:1;		// [21]
	unsigned int Force_Event_for_Data_Timeout_Error:1;		// [20]
	unsigned int Force_Event_for_Command_Index_Error:1;		// [19]
	unsigned int Force_Event_for_Command_End_Bit_Error:1;		// [18]
	unsigned int Force_Event_for_Command_CRC_Error:1;		// [17]
	unsigned int Force_Event_for_Command_Timeout_Error:1;		// [16]
	unsigned int Reserved2:8;		// [15:8]
	unsigned int Force_Event_for_command_not_issued_by_Auto_CMD12_Error:1;		// [7]
	unsigned int Reserved3:2;		// [6:5]
	unsigned int Force_Event_for_Auto_CMD_Index_Error:1;		// [4]
	unsigned int Force_Event_for_Auto_CMD_End_bit_Error:1;		// [3]
	unsigned int Force_Event_for_Auto_CMD_CRC_Error:1;		// [2]
	unsigned int Force_Event_for_Auto_CMD_timeout_Error:1;		// [1]
	unsigned int Force_Event_for_Auto_CMD12_NOT_Executed:1;		// [0]
};
 // ADMA_Error_Status Register
struct EMMCC_ADMA_ERROR_STATUS {
	unsigned int Reserved:29;		// [31:3]
	unsigned int ADMA_Length_Mismatch_Error:1;		// [2]
	unsigned int ADMA_Error_State:2;		// [1:0]
};
 // ADMA_System_Address_0 Register
struct EMMCC_ADMA_SYSTEM_ADDRESS_0 {
	unsigned int ADMA_System_Address_0:32;		// [31:0]
};
 // ADMA_System_Address_1 Register
struct EMMCC_ADMA_SYSTEM_ADDRESS_1 {
	unsigned int ADMA_System_Address_1:32;		// [31:0]
};
 // Preset_Value_for_Default_Speed_Initialization Register
struct EMMCC_PRESET_VALUE_FOR_DEFAULT_SPEED_INITIALIZATION {
	unsigned int Driver_Strength_Select_Value_for_Default_Speed:2;		// [31:30]
	unsigned int Reserved:3;		// [29:27]
	unsigned int Clock_Generator_Select_Value_for_Default_Speed:1;		// [26]
	unsigned int SDCLK_Frequency_Select_Value_for_Default_Speed:10;		// [25:16]
	unsigned int Driver_Strength_Select_Value_for_Initialization:2;		// [15:14]
	unsigned int Reserved2:3;		// [13:11]
	unsigned int Clock_Generator_Select_Value_for_Initialization:1;		// [10]
	unsigned int SDCLK_Frequency_Select_Value_for_Initialization:10;		// [9:0]
};
 // Preset_Value_for_SDR12_High_Speed Register
struct EMMCC_PRESET_VALUE_FOR_SDR12_HIGH_SPEED {
	unsigned int Driver_Strength_Select_Value_for_SDR12:2;		// [31:30]
	unsigned int Reserved:3;		// [29:27]
	unsigned int Clock_Generator_Select_Value_for_SDR12:1;		// [26]
	unsigned int SDCLK_Frequency_Select_Value_for_SDR12:10;		// [25:16]
	unsigned int Driver_Strength_Select_Value_for_High_Speed:2;		// [15:14]
	unsigned int Reserved2:3;		// [13:11]
	unsigned int Clock_Generator_Select_Value_for_High_Speed:1;		// [10]
	unsigned int SDCLK_Frequency_Select_Value_for_High_Speed:10;		// [9:0]
};
 // Preset_Value_for_SDR50_SDR25 Register
struct EMMCC_PRESET_VALUE_FOR_SDR50_SDR25 {
	unsigned int Driver_Strength_Select_Value_for_SDR50:2;		// [31:30]
	unsigned int Reserved:3;		// [29:27]
	unsigned int Clock_Generator_Select_Value_for_SDR50:1;		// [26]
	unsigned int SDCLK_Frequency_Select_Value_for_SDR50:10;		// [25:16]
	unsigned int Driver_Strength_Select_Value_for_SDR25:2;		// [15:14]
	unsigned int Reserved2:3;		// [13:11]
	unsigned int Clock_Generator_Select_Value_for_SDR25:1;		// [10]
	unsigned int SDCLK_Frequency_Select_Value_for_SDR25:10;		// [9:0]
};
 // Preset_Value_for_DDR50_SDR104 Register
struct EMMCC_PRESET_VALUE_FOR_DDR50_SDR104 {
	unsigned int Driver_Strength_Select_Value_for_DDR50:2;		// [31:30]
	unsigned int Reserved:3;		// [29:27]
	unsigned int Clock_Generator_Select_Value_for_DDR50:1;		// [26]
	unsigned int SDCLK_Frequency_Select_Value_for_DDR50:10;		// [25:16]
	unsigned int Driver_Strength_Select_Value_for_SDR104:2;		// [15:14]
	unsigned int Reserved2:3;		// [13:11]
	unsigned int Clock_Generator_Select_Value_for_SDR104:1;		// [10]
	unsigned int SDCLK_Frequency_Select_Value_for_SDR104:10;		// [9:0]
};
 // Boot_Timeout_Control Register
struct EMMCC_BOOT_TIMEOUT_CONTROL {
	unsigned int Boot_Data_Timeout_Counter_Value:32;		// [31:0]
};
 // Shared_Bus_Control Register
struct EMMCC_SHARED_BUS_CONTROL {
	unsigned int Reserved:32;		// [31:0]
};
 // Host_Controller_Version_Slot_Interrupt_Status Register
struct EMMCC_HOST_CONTROLLER_VERSION_SLOT_INTERRUPT_STATUS {
	unsigned int Vendor_Version_Number:8;		// [31:24]
	unsigned int Specification_Version_Number:8;		// [23:16]
	unsigned int Reserved:8;		// [15:8]
	unsigned int Reserved2:7;		// [7:1]
	unsigned int Interrupt_Signal_for_Slot0:1;		// [0]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _EMMCC_REG_STRUCT_B_H */
