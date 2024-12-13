# Copyright 2024 CEI UPM
# Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1

# Set macros
set design_name xilinx_clk_wizard

# Create block design
create_bd_design $design_name

# Create interface ports
set sys_diff_clock [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:diff_clock_rtl:1.0 sys_diff_clock ]
set clk_out1_0 [ create_bd_port -dir O -type clk clk_out1_0 ]

# Create instance and set properties
set clk_wiz_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:clk_wiz:6.0 clk_wiz_0 ]
	set_property -dict [list \
	CONFIG.CLKIN1_JITTER_PS {50.0} \
	CONFIG.CLKOUT1_JITTER {129.198} \
	CONFIG.CLKOUT1_PHASE_ERROR {89.971} \
	CONFIG.CLKOUT1_REQUESTED_OUT_FREQ {50.000} \
	CONFIG.CLK_IN1_BOARD_INTERFACE {sys_diff_clock} \
	CONFIG.ENABLE_CLOCK_MONITOR {false} \
	CONFIG.MMCM_CLKFBOUT_MULT_F {5.000} \
	CONFIG.MMCM_CLKIN1_PERIOD {5.000} \
	CONFIG.MMCM_CLKIN2_PERIOD {10.0} \
	CONFIG.MMCM_CLKOUT0_DIVIDE_F {20.000} \
	CONFIG.PRIMITIVE {MMCM} \
	CONFIG.PRIM_SOURCE {Differential_clock_capable_pin} \
	CONFIG.RESET_BOARD_INTERFACE {reset} \
	CONFIG.USE_LOCKED {false} \
	 CONFIG.USE_RESET {false} \
	] [get_bd_cells clk_wiz_0]

# Create interface connections
connect_bd_intf_net -intf_net sys_diff_clock_1 [get_bd_intf_ports sys_diff_clock] [get_bd_intf_pins clk_wiz_0/CLK_IN1_D]

# Create port connections
connect_bd_net -net clk_wiz_0_clk_out1 [ get_bd_ports clk_out1_0 ] [ get_bd_pins clk_wiz_0/clk_out1 ]

# Save and close block design
save_bd_design
close_bd_design $design_name

# create wrapper
set wrapper_path [ make_wrapper -fileset sources_1 -files [ get_files -norecurse xilinx_clk_wizard.bd ] -top ]
add_files -norecurse -fileset sources_1 $wrapper_path
