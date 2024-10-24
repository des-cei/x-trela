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
#include "x-heep.h"

/* By default, printfs are activated for FPGA and disabled for simulation. */
#define PRINTF_IN_FPGA  1
#define PRINTF_IN_SIM   0

#if TARGET_SIM && PRINTF_IN_SIM
    #define PRINTF(fmt, ...)    printf(fmt, ## __VA_ARGS__)
    #define SIZE 100
#elif TARGET_IS_FPGA && PRINTF_IN_FPGA
    #define PRINTF(fmt, ...)    printf(fmt, ## __VA_ARGS__)
    #define SIZE 2000
#else
    #define PRINTF(...)
    #define SIZE 100
#endif

volatile int32_t a[SIZE] __attribute__((section(".xheep_data_interleaved")));
volatile int32_t b[SIZE] __attribute__((section(".xheep_data_interleaved")));
volatile int32_t c[SIZE] __attribute__((section(".xheep_data_interleaved")));
volatile int32_t d[SIZE] __attribute__((section(".xheep_data_interleaved")));
volatile int32_t e[SIZE] __attribute__((section(".xheep_data_interleaved")));
volatile int32_t f[SIZE] __attribute__((section(".xheep_data_interleaved")));
volatile int32_t g[SIZE] __attribute__((section(".xheep_data_interleaved")));
volatile int32_t h[SIZE] __attribute__((section(".xheep_data_interleaved")));

// ---------------- CGRA definitions ---------------- //
mmio_region_t cgra;
volatile uint8_t cgra_intr_flag;

void fic_irq_strela(void) {
    cgra_intr_flag = 1;
}
// ---------------- CGRA definitions ---------------- //

int main(int argc, char *argv[])
{
    PRINTF("\r\n");
    PRINTF("Starting STRELA test application...\r\n");

	// Core configurations
    enable_all_fast_interrupts(true);
    // Enable interrupt on processor side
    // Enable global interrupt for machine-level interrupts
    CSR_SET_BITS(CSR_REG_MSTATUS, 0x8);
    // Set mie.MEIE bit to one to enable machine-level fast interrupts
    const uint32_t mask = 1 << 30;
    CSR_SET_BITS(CSR_REG_MIE, mask);

    // Data initialization
    int i;
    for(i = 0; i < SIZE; i++) {
        a[i] = i;
        b[i] = 2*i;
        c[i] = 3*i;
        d[i] = 4*i;
    }

    // Constant CGRA parameters
    cgra = mmio_region_from_addr(STRELA_BASE_ADDR);
    const uint32_t in_param = (sizeof(int32_t) << 16) | SIZE * sizeof(int32_t);
    const uint32_t out_param = SIZE * sizeof(int32_t);

    // CGRA execution
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_CTRL_REG_OFFSET, 0x1E); // RST all + PERF CTR en

    mmio_region_write32(cgra, (ptrdiff_t) STRELA_CONF_ADDR_REG_OFFSET, bypass_kernel);
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_IMN_0_ADDR_REG_OFFSET, a);
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_IMN_0_PARAM_REG_OFFSET, in_param);
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_IMN_1_ADDR_REG_OFFSET, b);
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_IMN_1_PARAM_REG_OFFSET, in_param);
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_IMN_2_ADDR_REG_OFFSET, c);
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_IMN_2_PARAM_REG_OFFSET, in_param);
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_IMN_3_ADDR_REG_OFFSET, d);
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_IMN_3_PARAM_REG_OFFSET, in_param);

    mmio_region_write32(cgra, (ptrdiff_t) STRELA_OMN_0_ADDR_REG_OFFSET, e);
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_OMN_0_SIZE_REG_OFFSET, out_param);
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_OMN_1_ADDR_REG_OFFSET, f);
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_OMN_1_SIZE_REG_OFFSET, out_param);
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_OMN_2_ADDR_REG_OFFSET, g);
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_OMN_2_SIZE_REG_OFFSET, out_param);
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_OMN_3_ADDR_REG_OFFSET, h);
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_OMN_3_SIZE_REG_OFFSET, out_param);
    
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_CTRL_REG_OFFSET, 0x09); // START + PERF CTR en

    // Wait CGRA is done
    cgra_intr_flag = 0;
    while(cgra_intr_flag == 0) wait_for_interrupt();

    mmio_region_write32(cgra, (ptrdiff_t) STRELA_CTRL_REG_OFFSET, 0x09); // START + PERF CTR en
    // Wait CGRA is done
    cgra_intr_flag = 0;
    while(cgra_intr_flag == 0) wait_for_interrupt();

    mmio_region_write32(cgra, (ptrdiff_t) STRELA_CTRL_REG_OFFSET, 0x0A); // CLR CONF + PERF CTR en

    mmio_region_write32(cgra, (ptrdiff_t) STRELA_CONF_ADDR_REG_OFFSET, bypass_kernel);
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_IMN_0_ADDR_REG_OFFSET, a);
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_IMN_0_PARAM_REG_OFFSET, in_param);
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_IMN_1_ADDR_REG_OFFSET, b);
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_IMN_1_PARAM_REG_OFFSET, in_param);
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_IMN_2_ADDR_REG_OFFSET, c);
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_IMN_2_PARAM_REG_OFFSET, in_param);
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_IMN_3_ADDR_REG_OFFSET, d);
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_IMN_3_PARAM_REG_OFFSET, in_param);

    mmio_region_write32(cgra, (ptrdiff_t) STRELA_OMN_0_ADDR_REG_OFFSET, e);
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_OMN_0_SIZE_REG_OFFSET, out_param);
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_OMN_1_ADDR_REG_OFFSET, f);
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_OMN_1_SIZE_REG_OFFSET, out_param);
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_OMN_2_ADDR_REG_OFFSET, g);
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_OMN_2_SIZE_REG_OFFSET, out_param);
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_OMN_3_ADDR_REG_OFFSET, h);
    mmio_region_write32(cgra, (ptrdiff_t) STRELA_OMN_3_SIZE_REG_OFFSET, out_param);
    

    mmio_region_write32(cgra, (ptrdiff_t) STRELA_CTRL_REG_OFFSET, 0x09); // START + PERF CTR en

    // Wait CGRA is done
    cgra_intr_flag = 0;
    while(cgra_intr_flag == 0) wait_for_interrupt();

    mmio_region_write32(cgra, (ptrdiff_t) STRELA_CTRL_REG_OFFSET, 0x0C); // CHN CONF + PERF CTR en

    mmio_region_write32(cgra, (ptrdiff_t) STRELA_CONF_ADDR_REG_OFFSET, bypass_kernel);
    

    mmio_region_write32(cgra, (ptrdiff_t) STRELA_CTRL_REG_OFFSET, 0x09); // START + PERF CTR en

    // Wait CGRA is done
    cgra_intr_flag = 0;
    while(cgra_intr_flag == 0) wait_for_interrupt();

    mmio_region_write32(cgra, (ptrdiff_t) STRELA_CTRL_REG_OFFSET, 0);

    volatile uint32_t total_cycles = mmio_region_read32(cgra, (ptrdiff_t) STRELA_PERF_CTR_TOTAL_CYCLES_REG_OFFSET);
    volatile uint32_t conf_cycles = mmio_region_read32(cgra, (ptrdiff_t) STRELA_PERF_CTR_CONF_CYCLES_REG_OFFSET);
    volatile uint32_t exec_cycles = mmio_region_read32(cgra, (ptrdiff_t) STRELA_PERF_CTR_EXEC_CYCLES_REG_OFFSET);
    volatile uint32_t stall_cycles = mmio_region_read32(cgra, (ptrdiff_t) STRELA_PERF_CTR_STALL_CYCLES_REG_OFFSET);

    mmio_region_write32(cgra, (ptrdiff_t) STRELA_CTRL_REG_OFFSET, 0x10);

    PRINTF("Total cycles: %lu\r\n", total_cycles);
    PRINTF("Conf. cycles: %lu\r\n", conf_cycles);
    PRINTF("Exec. cycles: %lu\r\n", exec_cycles);
    PRINTF("Stall cycles: %lu\r\n", stall_cycles);

    PRINTF("Finishing STRELA test application...\r\n");
    return 0;
}
