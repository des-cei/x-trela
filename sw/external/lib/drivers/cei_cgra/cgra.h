#ifndef _CGRA_H
#define _CGRA_H

#include "core_v_mini_mcu.h"

#define CGRA_BASE_ADDR      EXT_SLAVE_START_ADDRESS
#define CGRA_CONF         	0x0
#define CGRA_BS_ADDR      	0x4
#define CGRA_BS_SIZE      	0x8
#define CGRA_SEW          	0xC
#define CGRA_IN_BASE_ADDR   0x10
#define CGRA_OUT_BASE_ADDR  0x50
#define CGRA_BS_CTR_ADDR    0x90
#define CGRA_EXEC_CTR_ADDR  0x94
#define CGRA_STALL_CTR_ADDR 0x98

#define CGRA_IN0_ADDR     CGRA_IN_BASE_ADDR + 0x0
#define CGRA_IN0_SS       CGRA_IN_BASE_ADDR + 0x4
#define CGRA_IN1_ADDR     CGRA_IN_BASE_ADDR + 0x8
#define CGRA_IN1_SS       CGRA_IN_BASE_ADDR + 0xC
#define CGRA_IN2_ADDR     CGRA_IN_BASE_ADDR + 0x10
#define CGRA_IN2_SS       CGRA_IN_BASE_ADDR + 0x14
#define CGRA_IN3_ADDR     CGRA_IN_BASE_ADDR + 0x18
#define CGRA_IN3_SS       CGRA_IN_BASE_ADDR + 0x1C
#define CGRA_IN4_ADDR     CGRA_IN_BASE_ADDR + 0x20
#define CGRA_IN4_SS       CGRA_IN_BASE_ADDR + 0x24
#define CGRA_IN5_ADDR     CGRA_IN_BASE_ADDR + 0x28
#define CGRA_IN5_SS       CGRA_IN_BASE_ADDR + 0x2C
#define CGRA_IN6_ADDR     CGRA_IN_BASE_ADDR + 0x30
#define CGRA_IN6_SS       CGRA_IN_BASE_ADDR + 0x34
#define CGRA_IN7_ADDR     CGRA_IN_BASE_ADDR + 0x38
#define CGRA_IN7_SS       CGRA_IN_BASE_ADDR + 0x3C

#define CGRA_OUT0_ADDR    CGRA_OUT_BASE_ADDR + 0x0
#define CGRA_OUT0_SIZE    CGRA_OUT_BASE_ADDR + 0x4
#define CGRA_OUT1_ADDR    CGRA_OUT_BASE_ADDR + 0x8
#define CGRA_OUT1_SIZE    CGRA_OUT_BASE_ADDR + 0xC
#define CGRA_OUT2_ADDR    CGRA_OUT_BASE_ADDR + 0x10
#define CGRA_OUT2_SIZE    CGRA_OUT_BASE_ADDR + 0x14
#define CGRA_OUT3_ADDR    CGRA_OUT_BASE_ADDR + 0x18
#define CGRA_OUT3_SIZE    CGRA_OUT_BASE_ADDR + 0x1C
#define CGRA_OUT4_ADDR    CGRA_OUT_BASE_ADDR + 0x20
#define CGRA_OUT4_SIZE    CGRA_OUT_BASE_ADDR + 0x24
#define CGRA_OUT5_ADDR    CGRA_OUT_BASE_ADDR + 0x28
#define CGRA_OUT5_SIZE    CGRA_OUT_BASE_ADDR + 0x2C
#define CGRA_OUT6_ADDR    CGRA_OUT_BASE_ADDR + 0x30
#define CGRA_OUT6_SIZE    CGRA_OUT_BASE_ADDR + 0x34
#define CGRA_OUT7_ADDR    CGRA_OUT_BASE_ADDR + 0x38
#define CGRA_OUT7_SIZE    CGRA_OUT_BASE_ADDR + 0x3C

#endif
