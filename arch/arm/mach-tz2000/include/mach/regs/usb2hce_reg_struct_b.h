/*
 * arch/arm/mach-tz2000/include/mach/regs/usb2hce_reg_struct_b.h
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

#ifndef _USB2HCE_REG_STRUCT_B_H
#define _USB2HCE_REG_STRUCT_B_H

#ifdef __cplusplus
extern  {
#endif /* __cplusplus */


 // HCCAPBASE Register
struct USB2HCE_HCCAPBASE {
	unsigned int HCIVERSION:16;		// [31:16]
	unsigned int Reserved:8;		// [15:8]
	unsigned int CAPLENGTH:6;		// [7:2]
	unsigned int Reserved2:2;		// [1:0]
};
 // HCSPARAMS Register
struct USB2HCE_HCSPARAMS {
	unsigned int Reserved:8;		// [31:24]
	unsigned int debug_port_number:4;		// [23:20]
	unsigned int Reserved2:3;		// [19:17]
	unsigned int p_indicator:1;		// [16]
	unsigned int n_cc:4;		// [15:12]
	unsigned int n_pcc:4;		// [11:8]
	unsigned int port_route_rules:1;		// [7]
	unsigned int Reserved3:2;		// [6:5]
	unsigned int ppc:1;		// [4]
	unsigned int n_ports:4;		// [3:0]
};
 // HCCPARAMS Register
struct USB2HCE_HCCPARAMS {
	unsigned int Reserved:14;		// [31:18]
	unsigned int link_power_mgmt_cap:1;		// [17]
	unsigned int Reserved2:1;		// [16]
	unsigned int eecp:8;		// [15:8]
	unsigned int isoc_schedule_threshold:4;		// [7:4]
	unsigned int Reserved3:1;		// [3]
	unsigned int async_schedule_park_cap:1;		// [2]
	unsigned int frame_list_flag:1;		// [1]
	unsigned int address_64bit_cap:1;		// [0]
};
 // USBCMD Register
struct USB2HCE_USBCMD {
	unsigned int Reserved:8;		// [31:24]
	unsigned int intr_threshold_ctrl:8;		// [23:16]
	unsigned int Reserved2:4;		// [15:12]
	unsigned int async_schedule_park_mode_enable:1;		// [11]
	unsigned int Reserved3:1;		// [10]
	unsigned int async_schedule_park_mode_cnt:2;		// [9:8]
	unsigned int light_hcreset:1;		// [7]
	unsigned int intr_on_async_advance_drbell:1;		// [6]
	unsigned int async_schedule_enable:1;		// [5]
	unsigned int periodic_schedule_enable:1;		// [4]
	unsigned int frame_list_size:2;		// [3:2]
	unsigned int hcreset:1;		// [1]
	unsigned int run_stop:1;		// [0]
};
 // USBSTS Register
struct USB2HCE_USBSTS {
	unsigned int Reserved:16;		// [31:16]
	unsigned int async_schedule_status:1;		// [15]
	unsigned int periodic_schedule_status:1;		// [14]
	unsigned int reclamation:1;		// [13]
	unsigned int hchalted:1;		// [12]
	unsigned int Reserved2:6;		// [11:6]
	unsigned int intr_on_async_advance:1;		// [5]
	unsigned int host_system_error:1;		// [4]
	unsigned int frame_list_rollover:1;		// [3]
	unsigned int port_change_detect:1;		// [2]
	unsigned int usberrint:1;		// [1]
	unsigned int usbint:1;		// [0]
};
 // USBINTR Register
struct USB2HCE_USBINTR {
	unsigned int Reserved:26;		// [31:6]
	unsigned int intr_on_async_advance_enable:1;		// [5]
	unsigned int host_system_err_enable:1;		// [4]
	unsigned int frame_list_rollover_enable:1;		// [3]
	unsigned int port_change_intr_enable:1;		// [2]
	unsigned int usberrint_enable:1;		// [1]
	unsigned int usbint_enable:1;		// [0]
};
 // FRINDEX Register
struct USB2HCE_FRINDEX {
	unsigned int Reserved:18;		// [31:14]
	unsigned int frame_index:14;		// [13:0]
};
 // CTRLDSSEGMENT Register
struct USB2HCE_CTRLDSSEGMENT {
	unsigned int seg_4g_selector:32;		// [31:0]
};
 // PERIODICLISTBASE Register
struct USB2HCE_PERIODICLISTBASE {
	unsigned int base_address:20;		// [31:12]
	unsigned int Reserved:12;		// [11:0]
};
 // ASYNCLISTADDR Register
struct USB2HCE_ASYNCLISTADDR {
	unsigned int lpl:27;		// [31:5]
	unsigned int Reserved:5;		// [4:0]
};
 // CONFIGFLAG Register
struct USB2HCE_CONFIGFLAG {
	unsigned int Reserved:31;		// [31:1]
	unsigned int cf:1;		// [0]
};
 // PORTSC_0 Register
struct USB2HCE_PORTSC_0 {
	unsigned int Reserved:9;		// [31:23]
	unsigned int wkoc_e:1;		// [22]
	unsigned int wkdscnnt_e:1;		// [21]
	unsigned int wkcnnt_e:1;		// [20]
	unsigned int port_test_ctrl:4;		// [19:16]
	unsigned int port_indicator_ctrl:2;		// [15:14]
	unsigned int port_owner:1;		// [13]
	unsigned int pp:1;		// [12]
	unsigned int line_status:2;		// [11:10]
	unsigned int Reserved2:1;		// [9]
	unsigned int port_reset:1;		// [8]
	unsigned int suspend:1;		// [7]
	unsigned int force_port_resume:1;		// [6]
	unsigned int over_current_change:1;		// [5]
	unsigned int over_current_active:1;		// [4]
	unsigned int port_en_dis_change:1;		// [3]
	unsigned int port_enable_disable:1;		// [2]
	unsigned int connect_status_change:1;		// [1]
	unsigned int current_connect_status:1;		// [0]
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _USB2HCE_REG_STRUCT_B_H */
