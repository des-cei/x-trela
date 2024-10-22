# Copyright 2024 CEI UPM
# Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1

# Differential clock
set_property -dict {PACKAGE_PIN G18 IOSTANDARD DIFF_SSTL15} [get_ports sys_diff_clock_clk_n]
set_property -dict {PACKAGE_PIN H19 IOSTANDARD DIFF_SSTL15} [get_ports sys_diff_clock_clk_p]
set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets jtag_tck_i]

# CPU reset
set_property -dict {PACKAGE_PIN AV40 IOSTANDARD LVCMOS18} [get_ports rst_i]
set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets rst_i]

# Status LEDs
set_property -dict {PACKAGE_PIN AM39 IOSTANDARD LVCMOS18} [get_ports rst_led_o]
set_property -dict {PACKAGE_PIN AN39 IOSTANDARD LVCMOS18} [get_ports clk_led_o]
set_property -dict {PACKAGE_PIN AR37 IOSTANDARD LVCMOS18} [get_ports exit_value_o]
set_property -dict {PACKAGE_PIN AT37 IOSTANDARD LVCMOS18} [get_ports exit_valid_o]

# Mode selection switches
set_property -dict {PACKAGE_PIN AV30 IOSTANDARD LVCMOS18} [get_ports execute_from_flash_i]
set_property -dict {PACKAGE_PIN AY33 IOSTANDARD LVCMOS18} [get_ports boot_select_i]

# Flash (FMC dummy)
set_property -dict {PACKAGE_PIN K29 IOSTANDARD LVCMOS18} [get_ports spi_flash_csb_o]
set_property -dict {PACKAGE_PIN K30 IOSTANDARD LVCMOS18} [get_ports spi_flash_sck_o]
set_property -dict {PACKAGE_PIN J30 IOSTANDARD LVCMOS18} [get_ports {spi_flash_sd_io[0]}]
set_property -dict {PACKAGE_PIN H30 IOSTANDARD LVCMOS18} [get_ports {spi_flash_sd_io[1]}]
set_property -dict {PACKAGE_PIN L29 IOSTANDARD LVCMOS18} [get_ports {spi_flash_sd_io[2]}]
set_property -dict {PACKAGE_PIN L30 IOSTANDARD LVCMOS18} [get_ports {spi_flash_sd_io[3]}]

# UART
set_property -dict {PACKAGE_PIN AU36 IOSTANDARD LVCMOS18} [get_ports uart_tx_o]
set_property -dict {PACKAGE_PIN AU33 IOSTANDARD LVCMOS18} [get_ports uart_rx_i]

#JTAG (FMC dummy)
set_property -dict {PACKAGE_PIN J31 IOSTANDARD LVCMOS18} [get_ports jtag_tdi_i]
set_property -dict {PACKAGE_PIN H31 IOSTANDARD LVCMOS18} [get_ports jtag_tdo_o]
set_property -dict {PACKAGE_PIN P30 IOSTANDARD LVCMOS18} [get_ports jtag_tms_i]
set_property -dict {PACKAGE_PIN N31 IOSTANDARD LVCMOS18} [get_ports jtag_tck_i]
set_property -dict {PACKAGE_PIN M28 IOSTANDARD LVCMOS18} [get_ports jtag_trst_ni]

# I2C
set_property -dict {PACKAGE_PIN AT35 IOSTANDARD LVCMOS18} [get_ports i2c_scl_io]
set_property -dict {PACKAGE_PIN AU32 IOSTANDARD LVCMOS18} [get_ports i2c_sda_io]

# SPI SD (FMC dummy)
set_property -dict {PACKAGE_PIN M29 IOSTANDARD LVCMOS18} [get_ports spi_csb_o]
set_property -dict {PACKAGE_PIN R28 IOSTANDARD LVCMOS18} [get_ports spi_sck_o]
set_property -dict {PACKAGE_PIN P28 IOSTANDARD LVCMOS18} [get_ports {spi_sd_io[0]}]
set_property -dict {PACKAGE_PIN N28 IOSTANDARD LVCMOS18} [get_ports {spi_sd_io[1]}]
set_property -dict {PACKAGE_PIN N29 IOSTANDARD LVCMOS18} [get_ports {spi_sd_io[2]}]
set_property -dict {PACKAGE_PIN R30 IOSTANDARD LVCMOS18} [get_ports {spi_sd_io[3]}]

# GPIO connections
# LEDs
set_property -dict {PACKAGE_PIN AR35 IOSTANDARD LVCMOS18} [get_ports {gpio_io[0]}]
set_property -dict {PACKAGE_PIN AP41 IOSTANDARD LVCMOS18} [get_ports {gpio_io[1]}]
set_property -dict {PACKAGE_PIN AP42 IOSTANDARD LVCMOS18} [get_ports {gpio_io[2]}]
set_property -dict {PACKAGE_PIN AU39 IOSTANDARD LVCMOS18} [get_ports {gpio_io[3]}]
# Buttons
set_property -dict {PACKAGE_PIN AR40 IOSTANDARD LVCMOS18} [get_ports {gpio_io[4]}]
set_property -dict {PACKAGE_PIN AU38 IOSTANDARD LVCMOS18} [get_ports {gpio_io[5]}]
set_property -dict {PACKAGE_PIN AP40 IOSTANDARD LVCMOS18} [get_ports {gpio_io[6]}]
set_property -dict {PACKAGE_PIN AW40 IOSTANDARD LVCMOS18} [get_ports {gpio_io[7]}]
set_property -dict {PACKAGE_PIN AV39 IOSTANDARD LVCMOS18} [get_ports {gpio_io[8]}]
# Switches
set_property -dict {PACKAGE_PIN BA31 IOSTANDARD LVCMOS18} [get_ports {gpio_io[9]}]
set_property -dict {PACKAGE_PIN BA32 IOSTANDARD LVCMOS18} [get_ports {gpio_io[10]}]
set_property -dict {PACKAGE_PIN AW30 IOSTANDARD LVCMOS18} [get_ports {gpio_io[11]}]
set_property -dict {PACKAGE_PIN AY30 IOSTANDARD LVCMOS18} [get_ports {gpio_io[12]}]
set_property -dict {PACKAGE_PIN BA30 IOSTANDARD LVCMOS18} [get_ports {gpio_io[13]}]
set_property -dict {PACKAGE_PIN BB31 IOSTANDARD LVCMOS18} [get_ports {gpio_io[14]}]
# (FMC dummy)
set_property -dict {PACKAGE_PIN P31 IOSTANDARD LVCMOS18} [get_ports {gpio_io[15]}]
set_property -dict {PACKAGE_PIN U31 IOSTANDARD LVCMOS18} [get_ports {gpio_io[16]}]
set_property -dict {PACKAGE_PIN T31 IOSTANDARD LVCMOS18} [get_ports {gpio_io[17]}]

# PDM2PCM (FMC dummy)
set_property -dict {PACKAGE_PIN V30 IOSTANDARD LVCMOS18} [get_ports pdm2pcm_clk_io]
set_property -dict {PACKAGE_PIN V31 IOSTANDARD LVCMOS18} [get_ports pdm2pcm_pdm_io]

# I2S (FMC dummy)
set_property -dict {PACKAGE_PIN T29 IOSTANDARD LVCMOS18} [get_ports i2s_sck_io]
set_property -dict {PACKAGE_PIN T30 IOSTANDARD LVCMOS18} [get_ports i2s_ws_io]
set_property -dict {PACKAGE_PIN W30 IOSTANDARD LVCMOS18} [get_ports i2s_sd_io]

# SPI2 (FMC dummy)
set_property -dict {PACKAGE_PIN W31 IOSTANDARD LVCMOS18} [get_ports {spi2_csb_o[0]}]
set_property -dict {PACKAGE_PIN V29 IOSTANDARD LVCMOS18} [get_ports {spi2_csb_o[1]}]
set_property -dict {PACKAGE_PIN U29 IOSTANDARD LVCMOS18} [get_ports spi2_sck_o]
set_property -dict {PACKAGE_PIN Y29 IOSTANDARD LVCMOS18} [get_ports {spi2_sd_io[0]}]
set_property -dict {PACKAGE_PIN Y30 IOSTANDARD LVCMOS18} [get_ports {spi2_sd_io[1]}]
set_property -dict {PACKAGE_PIN H40 IOSTANDARD LVCMOS18} [get_ports {spi2_sd_io[2]}]
set_property -dict {PACKAGE_PIN H41 IOSTANDARD LVCMOS18} [get_ports {spi2_sd_io[3]}]
