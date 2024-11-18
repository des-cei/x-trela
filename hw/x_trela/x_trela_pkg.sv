// Copyright 2024 DES-CEI UPM
// Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
// SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
// Daniel Vazquez (daniel.vazquez@upm.es)

package x_trela_pkg;

  import addr_map_rule_pkg::*;
  import core_v_mini_mcu_pkg::*;

  // CGRA master ports
  localparam CGRA_XBAR_NMASTER = 8;
  // TODO: reduce X-HEEP masters to 4 for the interleaved memory
  // localparam EXT_XBAR_NMASTER = 4;
  localparam EXT_XBAR_NSLAVE = 1;

  localparam int unsigned LOG_EXT_XBAR_NMASTER = CGRA_XBAR_NMASTER > 1 ? $clog2(
      CGRA_XBAR_NMASTER
  ) : 32'd1;
  localparam int unsigned LOG_EXT_XBAR_NSLAVE = EXT_XBAR_NSLAVE > 1 ? $clog2(
      EXT_XBAR_NSLAVE
  ) : 32'd1;

  //slave mmap and idx
  localparam logic [31:0] CGRA_START_ADDRESS = core_v_mini_mcu_pkg::EXT_SLAVE_START_ADDRESS + 32'h000000;
  localparam logic [31:0] CGRA_SIZE = 32'h100000;
  localparam logic [31:0] CGRA_END_ADDRESS = CGRA_START_ADDRESS + CGRA_SIZE;
  localparam logic [31:0] CGRA_IDX = 32'd0;

  localparam addr_map_rule_t [EXT_XBAR_NSLAVE-1:0] EXT_XBAR_ADDR_RULES = '{
      '{idx: CGRA_IDX, start_addr: CGRA_START_ADDRESS, end_addr: CGRA_END_ADDRESS}
  };

  //slave encoder
  localparam EXT_SYSTEM_NPERIPHERALS = 1;

  localparam logic [31:0] CGRA_PERIPH_START_ADDRESS = core_v_mini_mcu_pkg::EXT_PERIPHERAL_START_ADDRESS + 32'h0000000;
  localparam logic [31:0] CGRA_PERIPH_SIZE = 32'h0001000;
  localparam logic [31:0] CGRA_PERIPH_END_ADDRESS = CGRA_PERIPH_START_ADDRESS + CGRA_PERIPH_SIZE;
  localparam logic [31:0] CGRA_PERIPH_IDX = 32'd0;

  localparam addr_map_rule_t [EXT_SYSTEM_NPERIPHERALS-1:0] EXT_PERIPHERALS_ADDR_RULES = '{
      '{
          idx: CGRA_PERIPH_IDX,
          start_addr: CGRA_PERIPH_START_ADDRESS,
          end_addr: CGRA_PERIPH_END_ADDRESS
      }
  };

  localparam int unsigned EXT_PERIPHERALS_PORT_SEL_WIDTH = EXT_SYSTEM_NPERIPHERALS > 1 ? $clog2(
      EXT_SYSTEM_NPERIPHERALS
  ) : 32'd1;

endpackage  // x_trela_pkg
