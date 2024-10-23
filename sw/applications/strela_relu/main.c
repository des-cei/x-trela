#include <stdio.h>
#include <stdint.h>
#include "core_v_mini_mcu.h"
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
    PRINTF("Starting STRELA ReLU application...\r\n");
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
    int chunk = DATA_SIZE / 3;
    int rest = DATA_SIZE % 3;
    uint32_t in12_param = (sizeof(int32_t) << 16) | chunk * sizeof(int32_t);
    uint32_t out12_param = chunk * sizeof(int32_t);
    uint32_t in3_param = (sizeof(int32_t) << 16) | (chunk+rest) * sizeof(int32_t);
    uint32_t out3_param = (chunk+rest) * sizeof(int32_t);

    // STRELA execution
    mmio_region_write32(strela, (ptrdiff_t) STRELA_CTRL_REG_OFFSET, 0x1E); // RST all + PERF CTR en

    mmio_region_write32(strela, (ptrdiff_t) STRELA_CONF_ADDR_REG_OFFSET, relu_kernel);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_IMN_0_ADDR_REG_OFFSET, input);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_IMN_0_PARAM_REG_OFFSET, in12_param);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_IMN_1_ADDR_REG_OFFSET, &input[chunk]);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_IMN_1_PARAM_REG_OFFSET, in12_param);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_IMN_3_ADDR_REG_OFFSET, &input[2*chunk]);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_IMN_3_PARAM_REG_OFFSET, in3_param);

    mmio_region_write32(strela, (ptrdiff_t) STRELA_OMN_0_ADDR_REG_OFFSET, output);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_OMN_0_SIZE_REG_OFFSET, out12_param);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_OMN_2_ADDR_REG_OFFSET, &output[chunk]);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_OMN_2_SIZE_REG_OFFSET, out12_param);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_OMN_3_ADDR_REG_OFFSET, &output[2*chunk]);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_OMN_3_SIZE_REG_OFFSET, out3_param);
    
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

    if(error) PRINTF("Execution failed with %d errrors!!!\r\n", error);
    else PRINTF("Execution finished successfully!\r\n");


    PRINTF("Finishing STRELA ReLU application...\r\n");
    return error;
}