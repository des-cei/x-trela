#include <stdio.h>
#include <stdint.h>
#include "core_v_mini_mcu.h"
#include "x-heep.h"
#include "hart.h"
#include "handler.h"
#include "fast_intr_ctrl.h"
#include "fast_intr_ctrl_regs.h"
#include "mmio.h"
#include "csr.h"
#include "csr_registers.h"
#include "strela.h"
#include "strela_regs.h"
#include "kernels.h"
#include "dataset.h"

/* By default, printfs are activated for FPGA and disabled for simulation. */
#define PRINTF_IN_FPGA  1
#define PRINTF_IN_SIM   0

#if TARGET_SIM && PRINTF_IN_SIM
    #define PRINTF(fmt, ...)    printf(fmt, ## __VA_ARGS__)
#elif TARGET_IS_FPGA && PRINTF_IN_FPGA
    #define PRINTF(fmt, ...)    printf(fmt, ## __VA_ARGS__)
#else
    #define PRINTF(...)
#endif

// ---------------- STRELA definitions ---------------- //
mmio_region_t strela;
volatile uint8_t strela_intr_flag;

void fic_irq_strela(void) {
    strela_intr_flag = 1;
}
// ---------------- STRELA definitions ---------------- //


int main(int argc, char *argv[])
{
    PRINTF("\r\n");
    PRINTF("Starting STRELA conv2d application...\r\n");
    PRINTF("Vector size: %lu\r\n", DATA_SIZE);

    // Core configurations ------------
    enable_all_fast_interrupts(true);

    // Enable interrupt on processor side
    // Enable global interrupt for machine-level interrupts
    CSR_SET_BITS(CSR_REG_MSTATUS, 0x8);

    // Set mie.MEIE bit to one to enable machine-level fast interrupts
    const uint32_t mask = 1 << 30;
    CSR_SET_BITS(CSR_REG_MIE, mask);

    // STRELA parameters
    strela = mmio_region_from_addr(STRELA_BASE_ADDR);
    const uint32_t in_param = (sizeof(int32_t) << 16) | (DATA_SIZE-2*SIZE-2) * sizeof(int32_t);
    const uint32_t out_param = (DATA_SIZE-2*SIZE-2) * sizeof(int32_t);

    // STRELA execution
    mmio_region_write32(strela, (ptrdiff_t) STRELA_CTRL_REG_OFFSET, 0x1E); // RST all + PERF CTR en

    mmio_region_write32(strela, (ptrdiff_t) STRELA_CONF_ADDR_REG_OFFSET, conv2d_1_kernel);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_IMN_0_ADDR_REG_OFFSET, input);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_IMN_0_PARAM_REG_OFFSET, in_param);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_IMN_1_ADDR_REG_OFFSET, &input[1]);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_IMN_1_PARAM_REG_OFFSET, in_param);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_IMN_2_ADDR_REG_OFFSET, &input[2]);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_IMN_2_PARAM_REG_OFFSET, in_param);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_OMN_2_ADDR_REG_OFFSET, &output[SIZE+1]);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_OMN_2_SIZE_REG_OFFSET, out_param);

    mmio_region_write32(strela, (ptrdiff_t) STRELA_CTRL_REG_OFFSET, 0x09); // START + PERF CTR en

    // Wait STRELA is done
    strela_intr_flag = 0;
    while(strela_intr_flag == 0) wait_for_interrupt();

    mmio_region_write32(strela, (ptrdiff_t) STRELA_CTRL_REG_OFFSET, 0x0E); // CLR CONF + CLR PARAM + PERF CTR en

    mmio_region_write32(strela, (ptrdiff_t) STRELA_CONF_ADDR_REG_OFFSET, conv2d_2_kernel);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_IMN_0_ADDR_REG_OFFSET, &input[SIZE]);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_IMN_0_PARAM_REG_OFFSET, in_param);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_IMN_1_ADDR_REG_OFFSET, &input[SIZE+1]);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_IMN_1_PARAM_REG_OFFSET, in_param);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_IMN_2_ADDR_REG_OFFSET, &input[SIZE+2]);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_IMN_2_PARAM_REG_OFFSET, in_param);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_IMN_3_ADDR_REG_OFFSET, &output[SIZE+1]);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_IMN_3_PARAM_REG_OFFSET, in_param);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_OMN_3_ADDR_REG_OFFSET, &output[SIZE+1]);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_OMN_3_SIZE_REG_OFFSET, out_param);

    mmio_region_write32(strela, (ptrdiff_t) STRELA_CTRL_REG_OFFSET, 0x09); // START + PERF CTR en

    // Wait STRELA is done
    strela_intr_flag = 0;
    while(strela_intr_flag == 0) wait_for_interrupt();

    // Change filter values
    conv2d_2_kernel[ 3] = 0;
    conv2d_2_kernel[23] = -1;
    conv2d_2_kernel[43] = 0;

    mmio_region_write32(strela, (ptrdiff_t) STRELA_CTRL_REG_OFFSET, 0x0E); // CLR CONF + CLR PARAM + PERF CTR en

    mmio_region_write32(strela, (ptrdiff_t) STRELA_CONF_ADDR_REG_OFFSET, conv2d_2_kernel);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_IMN_0_ADDR_REG_OFFSET, &input[2*SIZE]);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_IMN_0_PARAM_REG_OFFSET, in_param);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_IMN_1_ADDR_REG_OFFSET, &input[2*SIZE+1]);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_IMN_1_PARAM_REG_OFFSET, in_param);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_IMN_2_ADDR_REG_OFFSET, &input[2*SIZE+2]);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_IMN_2_PARAM_REG_OFFSET, in_param);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_IMN_3_ADDR_REG_OFFSET, &output[SIZE+1]);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_IMN_3_PARAM_REG_OFFSET, in_param);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_OMN_3_ADDR_REG_OFFSET, &output[SIZE+1]);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_OMN_3_SIZE_REG_OFFSET, out_param);

    mmio_region_write32(strela, (ptrdiff_t) STRELA_CTRL_REG_OFFSET, 0x09); // START + PERF CTR en

    // Wait STRELA is done
    strela_intr_flag = 0;
    while(strela_intr_flag == 0) wait_for_interrupt();

    // Stop STRELA and print execution report
    mmio_region_write32(strela, (ptrdiff_t) STRELA_CTRL_REG_OFFSET, 0x00);

    volatile uint32_t total_cycles = mmio_region_read32(strela, (ptrdiff_t) STRELA_PERF_CTR_TOTAL_CYCLES_REG_OFFSET);
    volatile uint32_t conf_cycles = mmio_region_read32(strela, (ptrdiff_t) STRELA_PERF_CTR_CONF_CYCLES_REG_OFFSET);
    volatile uint32_t exec_cycles = mmio_region_read32(strela, (ptrdiff_t) STRELA_PERF_CTR_EXEC_CYCLES_REG_OFFSET);
    volatile uint32_t stall_cycles = mmio_region_read32(strela, (ptrdiff_t) STRELA_PERF_CTR_STALL_CYCLES_REG_OFFSET);

    mmio_region_write32(strela, (ptrdiff_t) STRELA_CTRL_REG_OFFSET, 0x10);

    PRINTF("Total cycles: %lu\r\n", total_cycles);
    PRINTF("Conf. cycles: %lu\r\n", conf_cycles);
    PRINTF("Exec. cycles: %lu\r\n", exec_cycles);
    PRINTF("Stall cycles: %lu\r\n", stall_cycles);

    // Check results
    int error = 0;
    for(int i = 0; i < DATA_SIZE; i++)
        if(output[i] != expected_result[i]) error++;

    if(error) PRINTF("FAIL with %d errrors!!!\r\n", error);
    else PRINTF("SUCCESS!\r\n");


    PRINTF("Finishing STRELA ReLU application...\r\n");
    return error;
/*
    newVCDfile();
    pinHigh(PIN_TO_CTRL_VCD);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_CONF, 2UL);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_BS_ADDR, conv2d_1_kernel);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_BS_SIZE, CONV2D_1_KRNL_BYTES);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_IN0_ADDR, image);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_IN0_SS, in_param);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_IN1_ADDR, &image[1]);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_IN1_SS, in_param);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_IN2_ADDR, &image[2]);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_IN2_SS, in_param);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_OUT2_ADDR, result);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_OUT2_SIZE, out_param);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_CONF, 1UL);
    // Wait CGRA is done
    cgra_intr_flag = 0;
    while(cgra_intr_flag == 0) wait_for_interrupt();
    pinLow(PIN_TO_CTRL_VCD);
    newVCDfile();
    pinHigh(PIN_TO_CTRL_VCD);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_CONF, 2UL);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_BS_ADDR, conv2d_2_kernel);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_BS_SIZE, CONV2D_2_KRNL_BYTES);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_IN0_ADDR, &image[32]);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_IN0_SS, in_param);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_IN1_ADDR, &image[33]);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_IN1_SS, in_param);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_IN2_ADDR, &image[34]);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_IN2_SS, in_param);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_IN3_ADDR, result);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_IN3_SS, in_param);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_OUT3_ADDR, result);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_OUT3_SIZE, out_param);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_CONF, 1UL);
    // Wait CGRA is done
    cgra_intr_flag = 0;
    while(cgra_intr_flag == 0) wait_for_interrupt();
    pinLow(PIN_TO_CTRL_VCD);
    newVCDfile();
    pinHigh(PIN_TO_CTRL_VCD);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_IN0_ADDR, &image[64]);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_IN0_SS, in_param);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_IN1_ADDR, &image[65]);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_IN1_SS, in_param);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_IN2_ADDR, &image[66]);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_IN2_SS, in_param);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_IN3_ADDR, result);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_IN3_SS, in_param);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_OUT3_ADDR, result);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_OUT3_SIZE, out_param);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_CONF, 1UL);
    // Wait CGRA is done
    cgra_intr_flag = 0;
    while(cgra_intr_flag == 0) wait_for_interrupt();
    pinLow(PIN_TO_CTRL_VCD);
    heepocrates_ctrl_cgra_disable(&heepocrates_ctrl, 1);

    int flag = 0;
    // for(i = 0; i < SIZE; i++) {
    // }
    // if(flag ==0) printf("SUCCESS\n");
    // else printf("FAIL\n");
    return flag;*/
}