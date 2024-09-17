// Copyright 2022 OpenHW Group
// Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
// SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1

module testharness #(
    parameter COREV_PULP                  = 0,
    parameter FPU                         = 0,
    parameter ZFINX                       = 0,
    parameter X_EXT                       = 0,         // eXtension interface in cv32e40x
    parameter JTAG_DPI                    = 0,
    parameter USE_EXTERNAL_DEVICE_EXAMPLE = 1,
    parameter CLK_FREQUENCY               = 'd100_000  //KHz
) (
    inout wire clk_i,
    inout wire rst_ni,

    inout wire boot_select_i,
    inout wire execute_from_flash_i,

    input  wire         jtag_tck_i,
    input  wire         jtag_tms_i,
    input  wire         jtag_trst_ni,
    input  wire         jtag_tdi_i,
    output wire         jtag_tdo_o,
    output logic [31:0] exit_value_o,
    inout  wire         exit_valid_o
);


  `include "tb_util.svh"

  import obi_pkg::*;
  import reg_pkg::*;

  localparam SWITCH_ACK_LATENCY = 15;

  localparam EXT_DOMAINS_RND = core_v_mini_mcu_pkg::EXTERNAL_DOMAINS == 0 ? 1 : core_v_mini_mcu_pkg::EXTERNAL_DOMAINS;

  wire uart_rx;
  wire uart_tx;
  logic sim_jtag_enable = (JTAG_DPI == 1);
  wire sim_jtag_tck;
  wire sim_jtag_tms;
  wire sim_jtag_tdi;
  wire sim_jtag_tdo;
  wire sim_jtag_trstn;
  wire mux_jtag_tck;
  wire mux_jtag_tms;
  wire mux_jtag_tdi;
  wire mux_jtag_tdo;
  wire mux_jtag_trstn;
  wire [31:0] gpio;

  wire [3:0] spi_flash_sd_io;
  wire [1:0] spi_flash_csb;
  wire spi_flash_sck;

  wire [3:0] spi_sd_io;
  wire [1:0] spi_csb;
  wire spi_sck;

  // External subsystems
  logic [EXT_DOMAINS_RND-1:0] external_subsystem_powergate_switch_n;
  logic [EXT_DOMAINS_RND-1:0] external_subsystem_powergate_switch_ack_n;
  logic [EXT_DOMAINS_RND-1:0] external_subsystem_powergate_iso_n;
  logic [EXT_DOMAINS_RND-1:0] external_subsystem_rst_n;
  logic [EXT_DOMAINS_RND-1:0] external_ram_banks_set_retentive_n;
  logic [EXT_DOMAINS_RND-1:0] external_subsystem_clkgate_en_n;

  //log parameters
  initial begin
    $display("%t: the parameter COREV_PULP is %x", $time, COREV_PULP);
    $display("%t: the parameter FPU is %x", $time, FPU);
    $display("%t: the parameter ZFINX is %x", $time, ZFINX);
    $display("%t: the parameter X_EXT is %x", $time, X_EXT);
    $display("%t: the parameter ZFINX is %x", $time, ZFINX);
    $display("%t: the parameter JTAG_DPI is %x", $time, JTAG_DPI);
    $display("%t: the parameter EXT_DOMAINS is %x", $time, core_v_mini_mcu_pkg::EXTERNAL_DOMAINS);
    $display("%t: the parameter USE_EXTERNAL_DEVICE_EXAMPLE is %x", $time,
             USE_EXTERNAL_DEVICE_EXAMPLE);
    $display("%t: the parameter CLK_FREQUENCY is %d KHz", $time, CLK_FREQUENCY);
  end

  soc_sonhamos #(
      .COREV_PULP(COREV_PULP),
      .FPU(FPU),
      .ZFINX(ZFINX),
      .X_EXT(X_EXT)
  ) soc_sonhamos_i (
      .clk_i,
      .rst_ni,
      .jtag_tdo_o(mux_jtag_tdo),
      .jtag_tck_i(mux_jtag_tck),
      .jtag_tdi_i(mux_jtag_tdi),
      .jtag_tms_i(mux_jtag_tms),
      .jtag_trst_ni(mux_jtag_trstn),
      .exit_value_o,
      .boot_select_i,
      .execute_from_flash_i,
      .exit_valid_o,
      .spi_sd_io(spi_sd_io),
      .spi_flash_sd_io(spi_flash_sd_io),
      .uart_rx_i(uart_rx),
      .uart_tx_o(uart_tx),
      .spi_flash_sck_io(spi_flash_sck),
      .spi_flash_csb_io(spi_flash_csb),
      .spi_sck_io(spi_sck),
      .spi_csb_io(spi_csb),
      .gpio_io(gpio)
  );

  //pretending to be SWITCH CELLs that delay by SWITCH_ACK_LATENCY cycles the ACK signal
  logic
      tb_cpu_subsystem_powergate_switch_ack_n[SWITCH_ACK_LATENCY+1],
      tb_peripheral_subsystem_powergate_switch_ack_n[SWITCH_ACK_LATENCY+1];
  logic [core_v_mini_mcu_pkg::NUM_BANKS-1:0] tb_memory_subsystem_banks_powergate_switch_ack_n[SWITCH_ACK_LATENCY+1];
  logic [EXT_DOMAINS_RND-1:0] tb_external_subsystem_powergate_switch_ack_n[SWITCH_ACK_LATENCY+1];

  logic delayed_tb_cpu_subsystem_powergate_switch_ack_n;
  logic delayed_tb_peripheral_subsystem_powergate_switch_ack_n;
  logic [core_v_mini_mcu_pkg::NUM_BANKS-1:0] delayed_tb_memory_subsystem_banks_powergate_switch_ack_n;
  logic [EXT_DOMAINS_RND-1:0] delayed_tb_external_subsystem_powergate_switch_ack_n;

  always_ff @(negedge clk_i) begin
    tb_cpu_subsystem_powergate_switch_ack_n[0] <= soc_sonhamos_i.x_heep_system_i.cpu_subsystem_powergate_switch_n;
    tb_peripheral_subsystem_powergate_switch_ack_n[0] <= soc_sonhamos_i.x_heep_system_i.peripheral_subsystem_powergate_switch_n;
    tb_memory_subsystem_banks_powergate_switch_ack_n[0] <= soc_sonhamos_i.x_heep_system_i.core_v_mini_mcu_i.memory_subsystem_banks_powergate_switch_n;
    tb_external_subsystem_powergate_switch_ack_n[0] <= external_subsystem_powergate_switch_n;
    for (int i = 0; i < SWITCH_ACK_LATENCY; i++) begin
      tb_memory_subsystem_banks_powergate_switch_ack_n[i+1] <= tb_memory_subsystem_banks_powergate_switch_ack_n[i];
      tb_cpu_subsystem_powergate_switch_ack_n[i+1] <= tb_cpu_subsystem_powergate_switch_ack_n[i];
      tb_peripheral_subsystem_powergate_switch_ack_n[i+1] <= tb_peripheral_subsystem_powergate_switch_ack_n[i];
      tb_external_subsystem_powergate_switch_ack_n[i+1] <= tb_external_subsystem_powergate_switch_ack_n[i];
    end
  end

  assign delayed_tb_cpu_subsystem_powergate_switch_ack_n = tb_cpu_subsystem_powergate_switch_ack_n[SWITCH_ACK_LATENCY];
  assign delayed_tb_peripheral_subsystem_powergate_switch_ack_n = tb_peripheral_subsystem_powergate_switch_ack_n[SWITCH_ACK_LATENCY];
  assign delayed_tb_memory_subsystem_banks_powergate_switch_ack_n = tb_memory_subsystem_banks_powergate_switch_ack_n[SWITCH_ACK_LATENCY];
  assign delayed_tb_external_subsystem_powergate_switch_ack_n = tb_external_subsystem_powergate_switch_ack_n[SWITCH_ACK_LATENCY];

  always_comb begin
`ifndef VERILATOR
    force soc_sonhamos_i.x_heep_system_i.core_v_mini_mcu_i.cpu_subsystem_powergate_switch_ack_ni = delayed_tb_cpu_subsystem_powergate_switch_ack_n;
    force soc_sonhamos_i.x_heep_system_i.core_v_mini_mcu_i.peripheral_subsystem_powergate_switch_ack_ni = delayed_tb_peripheral_subsystem_powergate_switch_ack_n;
    force soc_sonhamos_i.x_heep_system_i.core_v_mini_mcu_i.memory_subsystem_banks_powergate_switch_ack_n = delayed_tb_memory_subsystem_banks_powergate_switch_ack_n;
    force external_subsystem_powergate_switch_ack_n = delayed_tb_external_subsystem_powergate_switch_ack_n;
`else
    soc_sonhamos_i.x_heep_system_i.cpu_subsystem_powergate_switch_ack_n = delayed_tb_cpu_subsystem_powergate_switch_ack_n;
    soc_sonhamos_i.x_heep_system_i.peripheral_subsystem_powergate_switch_ack_n = delayed_tb_peripheral_subsystem_powergate_switch_ack_n;
    soc_sonhamos_i.x_heep_system_i.core_v_mini_mcu_i.memory_subsystem_banks_powergate_switch_ack_n = delayed_tb_memory_subsystem_banks_powergate_switch_ack_n;
    external_subsystem_powergate_switch_ack_n = delayed_tb_external_subsystem_powergate_switch_ack_n;
`endif
  end


  uartdpi #(
      .BAUD('d256000),
      .FREQ(CLK_FREQUENCY * 1000),  //Hz
      .NAME("uart0")
  ) i_uart0 (
      .clk_i,
      .rst_ni,
      .tx_o(uart_rx),
      .rx_i(uart_tx)
  );

  // jtag calls from dpi
  SimJTAG #(
      .TICK_DELAY(1),
      .PORT      (4567)
  ) i_sim_jtag (
      .clock(clk_i),
      .reset(~rst_ni),
      .enable(sim_jtag_enable),
      .init_done(rst_ni),
      .jtag_TCK(sim_jtag_tck),
      .jtag_TMS(sim_jtag_tms),
      .jtag_TDI(sim_jtag_tdi),
      .jtag_TRSTn(sim_jtag_trstn),
      .jtag_TDO_data(sim_jtag_tdo),
      .jtag_TDO_driven(1'b1),
      .exit()
  );

  assign mux_jtag_tck   = JTAG_DPI ? sim_jtag_tck : jtag_tck_i;
  assign mux_jtag_tms   = JTAG_DPI ? sim_jtag_tms : jtag_tms_i;
  assign mux_jtag_tdi   = JTAG_DPI ? sim_jtag_tdi : jtag_tdi_i;
  assign mux_jtag_trstn = JTAG_DPI ? sim_jtag_trstn : jtag_trst_ni;

  assign sim_jtag_tdo   = JTAG_DPI ? mux_jtag_tdo : '0;
  assign jtag_tdo_o     = !JTAG_DPI ? mux_jtag_tdo : '0;

endmodule  // testharness
