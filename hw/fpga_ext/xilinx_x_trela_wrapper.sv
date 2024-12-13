// Copyright 2022 EPFL
// Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
// SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1

module xilinx_x_trela_wrapper
  import obi_pkg::*;
  import reg_pkg::*;
#(
    parameter COREV_PULP           = 0,
    parameter FPU                  = 0,
    parameter ZFINX                = 0,
    parameter X_EXT                = 0,  // eXtension interface in cv32e40x
    parameter CLK_LED_COUNT_LENGTH = 27
) (

`ifdef FPGA_VC709
    input logic sys_diff_clock_clk_n,
    input logic sys_diff_clock_clk_p,
`elsif FPGA_GENESYS2
    input logic sys_diff_clock_clk_n,
    input logic sys_diff_clock_clk_p,
`else
    inout logic clk_i,
`endif
    inout logic rst_i,

    output logic rst_led_o,
    output logic clk_led_o,

    inout logic boot_select_i,
    inout logic execute_from_flash_i,

    inout logic jtag_tck_i,
    inout logic jtag_tms_i,
    inout logic jtag_trst_ni,
    inout logic jtag_tdi_i,
    inout logic jtag_tdo_o,

    inout logic uart_rx_i,
    inout logic uart_tx_o,

    inout logic [17:0] gpio_io,

    output logic exit_value_o,
    inout  logic exit_valid_o,

    inout logic [3:0] spi_flash_sd_io,
    inout logic spi_flash_csb_o,
    inout logic spi_flash_sck_o,

    inout logic [3:0] spi_sd_io,
    inout logic spi_csb_o,
    inout logic spi_sck_o,

    inout logic [3:0] spi2_sd_io,
    inout logic [1:0] spi2_csb_o,
    inout logic spi2_sck_o,

    inout logic i2c_scl_io,
    inout logic i2c_sda_io,

    inout logic pdm2pcm_clk_io,
    inout logic pdm2pcm_pdm_io,

    inout logic i2s_sck_io,
    inout logic i2s_ws_io,
    inout logic i2s_sd_io

);

  wire                               clk_gen;
  logic [                      31:0] exit_value;
  wire                               rst_n;
  logic [CLK_LED_COUNT_LENGTH - 1:0] clk_count;
  wire  [                      32:0] gpio;

  // reset polarity
  `ifdef FPGA_GENESYS2
    assign rst_n = rst_i;
  `else 
    assign rst_n = !rst_i;
  `endif

  // reset LED for debugging
  assign rst_led_o = rst_n;

  // counter to blink an LED
  assign clk_led_o = clk_count[CLK_LED_COUNT_LENGTH-1];

  always_ff @(posedge clk_gen or negedge rst_n) begin : clk_count_process
    if (!rst_n) begin
      clk_count <= '0;
    end else begin
      clk_count <= clk_count + 1;
    end
  end

  // eXtension Interface
  if_xif #() ext_if ();

`ifdef FPGA_VC709
  xilinx_clk_wizard_wrapper xilinx_clk_wizard_wrapper_i (
      .sys_diff_clock_clk_n,
      .sys_diff_clock_clk_p,
      .clk_out1_0(clk_gen)
  );
`elsif FPGA_GENESYS2
  xilinx_clk_wizard_wrapper xilinx_clk_wizard_wrapper_i (
      .sys_diff_clock_clk_n,
      .sys_diff_clock_clk_p,
      .clk_out1_0(clk_gen)
  );
`else  // FPGA PYNQ-Z2
  xilinx_clk_wizard_wrapper xilinx_clk_wizard_wrapper_i (
      .clk_125MHz(clk_i),
      .clk_out1_0(clk_gen)
  );
`endif

  x_trela #(
      .COREV_PULP(COREV_PULP),
      .FPU(FPU),
      .ZFINX(ZFINX),
      .X_EXT(X_EXT)
    ) x_trela_i (
      .clk_i( clk_gen ),
      .rst_ni( rst_n ),
      .jtag_tdo_o,
      .jtag_tck_i,
      .jtag_tdi_i,
      .jtag_tms_i,
      .jtag_trst_ni,
      .exit_value_o( exit_value ),
      .boot_select_i,
      .execute_from_flash_i,
      .exit_valid_o,
      .spi_sd_io,
      .spi_flash_sd_io,
      .uart_rx_i,
      .uart_tx_o,
      .spi_flash_sck_io( spi_flash_sck_o ),
      .spi_flash_csb_io( spi_flash_csb_o ),
      .spi_sck_io( spi_sck_o ),
      .spi_csb_io( spi_csb_o ),
      .gpio_io( gpio )
    );

  assign exit_value_o   = exit_value[0];
  assign gpio_io        = gpio[17:0];
  assign pdm2pcm_pdm_io = gpio[18];
  assign pdm2pcm_clk_io = gpio[19];
  assign i2s_sck_io     = gpio[20];
  assign i2s_ws_io      = gpio[21];
  assign i2s_sd_io      = gpio[22];
  assign spi2_csb_o[0]  = gpio[23];
  assign spi2_csb_o[1]  = gpio[24];
  assign spi2_sck_o     = gpio[25];
  assign spi2_sd_io[0]  = gpio[26];
  assign spi2_sd_io[1]  = gpio[27];
  assign spi2_sd_io[2]  = gpio[28];
  assign spi2_sd_io[3]  = gpio[29];
  assign i2c_sda_io     = gpio[30];
  assign i2c_scl_io     = gpio[31];

endmodule