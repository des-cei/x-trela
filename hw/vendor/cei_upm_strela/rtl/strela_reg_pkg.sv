// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
// Register Package auto-generated by `reggen` containing data structure

package strela_reg_pkg;

  // Address widths within the block
  parameter int BlockAw = 7;

  ////////////////////////////
  // Typedefs for registers //
  ////////////////////////////

  typedef struct packed {
    struct packed {
      logic        q;
    } start;
    struct packed {
      logic        q;
    } clr_param;
    struct packed {
      logic        q;
    } clr_conf;
    struct packed {
      logic        q;
    } perf_ctr_en;
    struct packed {
      logic        q;
    } perf_ctr_rst;
  } strela_reg2hw_ctrl_reg_t;

  typedef struct packed {
    logic [31:0] q;
  } strela_reg2hw_perf_ctr_total_cycles_reg_t;

  typedef struct packed {
    logic [31:0] q;
  } strela_reg2hw_perf_ctr_exec_cycles_reg_t;

  typedef struct packed {
    logic [31:0] q;
  } strela_reg2hw_perf_ctr_conf_cycles_reg_t;

  typedef struct packed {
    logic [31:0] q;
  } strela_reg2hw_perf_ctr_stall_cycles_reg_t;

  typedef struct packed {
    logic [31:0] q;
  } strela_reg2hw_conf_addr_reg_t;

  typedef struct packed {
    logic [31:0] q;
  } strela_reg2hw_imn_0_addr_reg_t;

  typedef struct packed {
    struct packed {
      logic [15:0] q;
    } imn_0_size;
    struct packed {
      logic [15:0] q;
    } imn_0_stride;
  } strela_reg2hw_imn_0_param_reg_t;

  typedef struct packed {
    logic [31:0] q;
  } strela_reg2hw_imn_1_addr_reg_t;

  typedef struct packed {
    struct packed {
      logic [15:0] q;
    } imn_1_size;
    struct packed {
      logic [15:0] q;
    } imn_1_stride;
  } strela_reg2hw_imn_1_param_reg_t;

  typedef struct packed {
    logic [31:0] q;
  } strela_reg2hw_imn_2_addr_reg_t;

  typedef struct packed {
    struct packed {
      logic [15:0] q;
    } imn_2_size;
    struct packed {
      logic [15:0] q;
    } imn_2_stride;
  } strela_reg2hw_imn_2_param_reg_t;

  typedef struct packed {
    logic [31:0] q;
  } strela_reg2hw_imn_3_addr_reg_t;

  typedef struct packed {
    struct packed {
      logic [15:0] q;
    } imn_3_size;
    struct packed {
      logic [15:0] q;
    } imn_3_stride;
  } strela_reg2hw_imn_3_param_reg_t;

  typedef struct packed {
    logic [31:0] q;
  } strela_reg2hw_omn_0_addr_reg_t;

  typedef struct packed {
    logic [15:0] q;
  } strela_reg2hw_omn_0_size_reg_t;

  typedef struct packed {
    logic [31:0] q;
  } strela_reg2hw_omn_1_addr_reg_t;

  typedef struct packed {
    logic [15:0] q;
  } strela_reg2hw_omn_1_size_reg_t;

  typedef struct packed {
    logic [31:0] q;
  } strela_reg2hw_omn_2_addr_reg_t;

  typedef struct packed {
    logic [15:0] q;
  } strela_reg2hw_omn_2_size_reg_t;

  typedef struct packed {
    logic [31:0] q;
  } strela_reg2hw_omn_3_addr_reg_t;

  typedef struct packed {
    logic [15:0] q;
  } strela_reg2hw_omn_3_size_reg_t;

  typedef struct packed {
    struct packed {
      logic        d;
      logic        de;
    } start;
    struct packed {
      logic        d;
      logic        de;
    } clr_param;
    struct packed {
      logic        d;
      logic        de;
    } clr_conf;
    struct packed {
      logic        d;
      logic        de;
    } perf_ctr_en;
    struct packed {
      logic        d;
      logic        de;
    } perf_ctr_rst;
  } strela_hw2reg_ctrl_reg_t;

  typedef struct packed {
    struct packed {
      logic        d;
      logic        de;
    } exec_done;
    struct packed {
      logic        d;
      logic        de;
    } conf_done;
  } strela_hw2reg_status_reg_t;

  typedef struct packed {
    logic [31:0] d;
    logic        de;
  } strela_hw2reg_perf_ctr_total_cycles_reg_t;

  typedef struct packed {
    logic [31:0] d;
    logic        de;
  } strela_hw2reg_perf_ctr_exec_cycles_reg_t;

  typedef struct packed {
    logic [31:0] d;
    logic        de;
  } strela_hw2reg_perf_ctr_conf_cycles_reg_t;

  typedef struct packed {
    logic [31:0] d;
    logic        de;
  } strela_hw2reg_perf_ctr_stall_cycles_reg_t;

  typedef struct packed {
    logic [31:0] d;
    logic        de;
  } strela_hw2reg_conf_addr_reg_t;

  typedef struct packed {
    logic [31:0] d;
    logic        de;
  } strela_hw2reg_imn_0_addr_reg_t;

  typedef struct packed {
    struct packed {
      logic [15:0] d;
      logic        de;
    } imn_0_size;
    struct packed {
      logic [15:0] d;
      logic        de;
    } imn_0_stride;
  } strela_hw2reg_imn_0_param_reg_t;

  typedef struct packed {
    logic [31:0] d;
    logic        de;
  } strela_hw2reg_imn_1_addr_reg_t;

  typedef struct packed {
    struct packed {
      logic [15:0] d;
      logic        de;
    } imn_1_size;
    struct packed {
      logic [15:0] d;
      logic        de;
    } imn_1_stride;
  } strela_hw2reg_imn_1_param_reg_t;

  typedef struct packed {
    logic [31:0] d;
    logic        de;
  } strela_hw2reg_imn_2_addr_reg_t;

  typedef struct packed {
    struct packed {
      logic [15:0] d;
      logic        de;
    } imn_2_size;
    struct packed {
      logic [15:0] d;
      logic        de;
    } imn_2_stride;
  } strela_hw2reg_imn_2_param_reg_t;

  typedef struct packed {
    logic [31:0] d;
    logic        de;
  } strela_hw2reg_imn_3_addr_reg_t;

  typedef struct packed {
    struct packed {
      logic [15:0] d;
      logic        de;
    } imn_3_size;
    struct packed {
      logic [15:0] d;
      logic        de;
    } imn_3_stride;
  } strela_hw2reg_imn_3_param_reg_t;

  typedef struct packed {
    logic [31:0] d;
    logic        de;
  } strela_hw2reg_omn_0_addr_reg_t;

  typedef struct packed {
    logic [15:0] d;
    logic        de;
  } strela_hw2reg_omn_0_size_reg_t;

  typedef struct packed {
    logic [31:0] d;
    logic        de;
  } strela_hw2reg_omn_1_addr_reg_t;

  typedef struct packed {
    logic [15:0] d;
    logic        de;
  } strela_hw2reg_omn_1_size_reg_t;

  typedef struct packed {
    logic [31:0] d;
    logic        de;
  } strela_hw2reg_omn_2_addr_reg_t;

  typedef struct packed {
    logic [15:0] d;
    logic        de;
  } strela_hw2reg_omn_2_size_reg_t;

  typedef struct packed {
    logic [31:0] d;
    logic        de;
  } strela_hw2reg_omn_3_addr_reg_t;

  typedef struct packed {
    logic [15:0] d;
    logic        de;
  } strela_hw2reg_omn_3_size_reg_t;

  // Register -> HW type
  typedef struct packed {
    strela_reg2hw_ctrl_reg_t ctrl; // [612:608]
    strela_reg2hw_perf_ctr_total_cycles_reg_t perf_ctr_total_cycles; // [607:576]
    strela_reg2hw_perf_ctr_exec_cycles_reg_t perf_ctr_exec_cycles; // [575:544]
    strela_reg2hw_perf_ctr_conf_cycles_reg_t perf_ctr_conf_cycles; // [543:512]
    strela_reg2hw_perf_ctr_stall_cycles_reg_t perf_ctr_stall_cycles; // [511:480]
    strela_reg2hw_conf_addr_reg_t conf_addr; // [479:448]
    strela_reg2hw_imn_0_addr_reg_t imn_0_addr; // [447:416]
    strela_reg2hw_imn_0_param_reg_t imn_0_param; // [415:384]
    strela_reg2hw_imn_1_addr_reg_t imn_1_addr; // [383:352]
    strela_reg2hw_imn_1_param_reg_t imn_1_param; // [351:320]
    strela_reg2hw_imn_2_addr_reg_t imn_2_addr; // [319:288]
    strela_reg2hw_imn_2_param_reg_t imn_2_param; // [287:256]
    strela_reg2hw_imn_3_addr_reg_t imn_3_addr; // [255:224]
    strela_reg2hw_imn_3_param_reg_t imn_3_param; // [223:192]
    strela_reg2hw_omn_0_addr_reg_t omn_0_addr; // [191:160]
    strela_reg2hw_omn_0_size_reg_t omn_0_size; // [159:144]
    strela_reg2hw_omn_1_addr_reg_t omn_1_addr; // [143:112]
    strela_reg2hw_omn_1_size_reg_t omn_1_size; // [111:96]
    strela_reg2hw_omn_2_addr_reg_t omn_2_addr; // [95:64]
    strela_reg2hw_omn_2_size_reg_t omn_2_size; // [63:48]
    strela_reg2hw_omn_3_addr_reg_t omn_3_addr; // [47:16]
    strela_reg2hw_omn_3_size_reg_t omn_3_size; // [15:0]
  } strela_reg2hw_t;

  // HW -> register type
  typedef struct packed {
    strela_hw2reg_ctrl_reg_t ctrl; // [646:637]
    strela_hw2reg_status_reg_t status; // [636:633]
    strela_hw2reg_perf_ctr_total_cycles_reg_t perf_ctr_total_cycles; // [632:600]
    strela_hw2reg_perf_ctr_exec_cycles_reg_t perf_ctr_exec_cycles; // [599:567]
    strela_hw2reg_perf_ctr_conf_cycles_reg_t perf_ctr_conf_cycles; // [566:534]
    strela_hw2reg_perf_ctr_stall_cycles_reg_t perf_ctr_stall_cycles; // [533:501]
    strela_hw2reg_conf_addr_reg_t conf_addr; // [500:468]
    strela_hw2reg_imn_0_addr_reg_t imn_0_addr; // [467:435]
    strela_hw2reg_imn_0_param_reg_t imn_0_param; // [434:401]
    strela_hw2reg_imn_1_addr_reg_t imn_1_addr; // [400:368]
    strela_hw2reg_imn_1_param_reg_t imn_1_param; // [367:334]
    strela_hw2reg_imn_2_addr_reg_t imn_2_addr; // [333:301]
    strela_hw2reg_imn_2_param_reg_t imn_2_param; // [300:267]
    strela_hw2reg_imn_3_addr_reg_t imn_3_addr; // [266:234]
    strela_hw2reg_imn_3_param_reg_t imn_3_param; // [233:200]
    strela_hw2reg_omn_0_addr_reg_t omn_0_addr; // [199:167]
    strela_hw2reg_omn_0_size_reg_t omn_0_size; // [166:150]
    strela_hw2reg_omn_1_addr_reg_t omn_1_addr; // [149:117]
    strela_hw2reg_omn_1_size_reg_t omn_1_size; // [116:100]
    strela_hw2reg_omn_2_addr_reg_t omn_2_addr; // [99:67]
    strela_hw2reg_omn_2_size_reg_t omn_2_size; // [66:50]
    strela_hw2reg_omn_3_addr_reg_t omn_3_addr; // [49:17]
    strela_hw2reg_omn_3_size_reg_t omn_3_size; // [16:0]
  } strela_hw2reg_t;

  // Register offsets
  parameter logic [BlockAw-1:0] STRELA_CTRL_OFFSET = 7'h 0;
  parameter logic [BlockAw-1:0] STRELA_STATUS_OFFSET = 7'h 4;
  parameter logic [BlockAw-1:0] STRELA_PERF_CTR_TOTAL_CYCLES_OFFSET = 7'h 8;
  parameter logic [BlockAw-1:0] STRELA_PERF_CTR_EXEC_CYCLES_OFFSET = 7'h c;
  parameter logic [BlockAw-1:0] STRELA_PERF_CTR_CONF_CYCLES_OFFSET = 7'h 10;
  parameter logic [BlockAw-1:0] STRELA_PERF_CTR_STALL_CYCLES_OFFSET = 7'h 14;
  parameter logic [BlockAw-1:0] STRELA_CONF_ADDR_OFFSET = 7'h 18;
  parameter logic [BlockAw-1:0] STRELA_IMN_0_ADDR_OFFSET = 7'h 1c;
  parameter logic [BlockAw-1:0] STRELA_IMN_0_PARAM_OFFSET = 7'h 20;
  parameter logic [BlockAw-1:0] STRELA_IMN_1_ADDR_OFFSET = 7'h 24;
  parameter logic [BlockAw-1:0] STRELA_IMN_1_PARAM_OFFSET = 7'h 28;
  parameter logic [BlockAw-1:0] STRELA_IMN_2_ADDR_OFFSET = 7'h 2c;
  parameter logic [BlockAw-1:0] STRELA_IMN_2_PARAM_OFFSET = 7'h 30;
  parameter logic [BlockAw-1:0] STRELA_IMN_3_ADDR_OFFSET = 7'h 34;
  parameter logic [BlockAw-1:0] STRELA_IMN_3_PARAM_OFFSET = 7'h 38;
  parameter logic [BlockAw-1:0] STRELA_OMN_0_ADDR_OFFSET = 7'h 3c;
  parameter logic [BlockAw-1:0] STRELA_OMN_0_SIZE_OFFSET = 7'h 40;
  parameter logic [BlockAw-1:0] STRELA_OMN_1_ADDR_OFFSET = 7'h 44;
  parameter logic [BlockAw-1:0] STRELA_OMN_1_SIZE_OFFSET = 7'h 48;
  parameter logic [BlockAw-1:0] STRELA_OMN_2_ADDR_OFFSET = 7'h 4c;
  parameter logic [BlockAw-1:0] STRELA_OMN_2_SIZE_OFFSET = 7'h 50;
  parameter logic [BlockAw-1:0] STRELA_OMN_3_ADDR_OFFSET = 7'h 54;
  parameter logic [BlockAw-1:0] STRELA_OMN_3_SIZE_OFFSET = 7'h 58;

  // Register index
  typedef enum int {
    STRELA_CTRL,
    STRELA_STATUS,
    STRELA_PERF_CTR_TOTAL_CYCLES,
    STRELA_PERF_CTR_EXEC_CYCLES,
    STRELA_PERF_CTR_CONF_CYCLES,
    STRELA_PERF_CTR_STALL_CYCLES,
    STRELA_CONF_ADDR,
    STRELA_IMN_0_ADDR,
    STRELA_IMN_0_PARAM,
    STRELA_IMN_1_ADDR,
    STRELA_IMN_1_PARAM,
    STRELA_IMN_2_ADDR,
    STRELA_IMN_2_PARAM,
    STRELA_IMN_3_ADDR,
    STRELA_IMN_3_PARAM,
    STRELA_OMN_0_ADDR,
    STRELA_OMN_0_SIZE,
    STRELA_OMN_1_ADDR,
    STRELA_OMN_1_SIZE,
    STRELA_OMN_2_ADDR,
    STRELA_OMN_2_SIZE,
    STRELA_OMN_3_ADDR,
    STRELA_OMN_3_SIZE
  } strela_id_e;

  // Register width information to check illegal writes
  parameter logic [3:0] STRELA_PERMIT [23] = '{
    4'b 0001, // index[ 0] STRELA_CTRL
    4'b 0001, // index[ 1] STRELA_STATUS
    4'b 1111, // index[ 2] STRELA_PERF_CTR_TOTAL_CYCLES
    4'b 1111, // index[ 3] STRELA_PERF_CTR_EXEC_CYCLES
    4'b 1111, // index[ 4] STRELA_PERF_CTR_CONF_CYCLES
    4'b 1111, // index[ 5] STRELA_PERF_CTR_STALL_CYCLES
    4'b 1111, // index[ 6] STRELA_CONF_ADDR
    4'b 1111, // index[ 7] STRELA_IMN_0_ADDR
    4'b 1111, // index[ 8] STRELA_IMN_0_PARAM
    4'b 1111, // index[ 9] STRELA_IMN_1_ADDR
    4'b 1111, // index[10] STRELA_IMN_1_PARAM
    4'b 1111, // index[11] STRELA_IMN_2_ADDR
    4'b 1111, // index[12] STRELA_IMN_2_PARAM
    4'b 1111, // index[13] STRELA_IMN_3_ADDR
    4'b 1111, // index[14] STRELA_IMN_3_PARAM
    4'b 1111, // index[15] STRELA_OMN_0_ADDR
    4'b 0011, // index[16] STRELA_OMN_0_SIZE
    4'b 1111, // index[17] STRELA_OMN_1_ADDR
    4'b 0011, // index[18] STRELA_OMN_1_SIZE
    4'b 1111, // index[19] STRELA_OMN_2_ADDR
    4'b 0011, // index[20] STRELA_OMN_2_SIZE
    4'b 1111, // index[21] STRELA_OMN_3_ADDR
    4'b 0011  // index[22] STRELA_OMN_3_SIZE
  };

endpackage
