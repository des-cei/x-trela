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
    PRINTF("Starting STRELA dither filter application...\r\n");
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
    const int chunk = DATA_SIZE;
    const int rest = 0;
    const uint32_t in1_param = (sizeof(int32_t) << 16) | chunk * sizeof(int32_t);
    const uint32_t out1_param = chunk * sizeof(int32_t);
    const uint32_t in2_param = (sizeof(int32_t) << 16) | (chunk+rest) * sizeof(int32_t);
    const uint32_t out2_param = (chunk+rest) * sizeof(int32_t);

    // STRELA execution
    mmio_region_write32(strela, (ptrdiff_t) STRELA_CTRL_REG_OFFSET, 1 << STRELA_CTRL_CLR_BIT);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_MODE_REG_OFFSET, 1 << STRELA_MODE_PERF_CTR_EN_BIT | 1 << STRELA_MODE_INTR_EN_BIT);

    mmio_region_write32(strela, (ptrdiff_t) STRELA_CONF_ADDR_REG_OFFSET, dither_filter_kernel);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_IMN_0_ADDR_REG_OFFSET, input);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_IMN_0_PARAM_REG_OFFSET, in1_param);

    mmio_region_write32(strela, (ptrdiff_t) STRELA_OMN_0_ADDR_REG_OFFSET, output);
    mmio_region_write32(strela, (ptrdiff_t) STRELA_OMN_0_SIZE_REG_OFFSET, out1_param);
    
    mmio_region_write32(strela, (ptrdiff_t) STRELA_CTRL_REG_OFFSET, 1 << STRELA_CTRL_START_BIT);

    // Wait STRELA is done
    strela_intr_flag = 0;
    while(strela_intr_flag == 0) wait_for_interrupt();

    // Stop STRELA and print execution report
    mmio_region_write32(strela, (ptrdiff_t) STRELA_MODE_REG_OFFSET, 0);

    volatile uint32_t total_cycles = mmio_region_read32(strela, (ptrdiff_t) STRELA_PERF_CTR_TOTAL_CYCLES_REG_OFFSET);
    volatile uint32_t conf_cycles = mmio_region_read32(strela, (ptrdiff_t) STRELA_PERF_CTR_CONF_CYCLES_REG_OFFSET);
    volatile uint32_t exec_cycles = mmio_region_read32(strela, (ptrdiff_t) STRELA_PERF_CTR_EXEC_CYCLES_REG_OFFSET);
    volatile uint32_t stall_cycles = mmio_region_read32(strela, (ptrdiff_t) STRELA_PERF_CTR_STALL_CYCLES_REG_OFFSET);

    mmio_region_write32(strela, (ptrdiff_t) STRELA_CTRL_REG_OFFSET, 1 << STRELA_CTRL_CLR_BIT);

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


    PRINTF("Finishing STRELA dither filter application...\r\n");
    return error;
}