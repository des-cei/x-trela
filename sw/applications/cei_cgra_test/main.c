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
#include "cgra.h"
#include "kernels.h"

#define SIZE 100

mmio_region_t cgra;
volatile uint8_t cgra_intr_flag;

volatile int32_t a[SIZE] __attribute__((section(".xheep_data_interleaved")));
volatile int32_t b[SIZE] __attribute__((section(".xheep_data_interleaved")));
volatile int32_t c[SIZE] __attribute__((section(".xheep_data_interleaved")));
volatile int32_t d[SIZE] __attribute__((section(".xheep_data_interleaved")));
volatile int32_t e[SIZE] __attribute__((section(".xheep_data_interleaved")));
volatile int32_t f[SIZE] __attribute__((section(".xheep_data_interleaved")));
volatile int32_t g[SIZE] __attribute__((section(".xheep_data_interleaved")));
volatile int32_t h[SIZE] __attribute__((section(".xheep_data_interleaved")));

void fic_irq_cgra(void) {
    cgra_intr_flag = 1;
}

int main(int argc, char *argv[])
{
    enable_all_fast_interrupts(true);
    // Enable interrupt on processor side
    // Enable global interrupt for machine-level interrupts
    CSR_SET_BITS(CSR_REG_MSTATUS, 0x8);
    // Set mie.MEIE bit to one to enable machine-level fast interrupts
    const uint32_t mask = 1 << 30;
    CSR_SET_BITS(CSR_REG_MIE, mask);

    int i;
    
    for(i = 0; i < SIZE; i++) {
        a[i] = i;
        b[i] = 2*i;
        c[i] = 3*i;
        d[i] = 4*i;
    }
    
    cgra = mmio_region_from_addr(CGRA_BASE_ADDR);
    const uint32_t in_param = (sizeof(int32_t) << 16) | SIZE * sizeof(int32_t);
    const uint32_t out_param = SIZE * sizeof(int32_t);

    mmio_region_write32(cgra, (ptrdiff_t) CGRA_CONF, 2UL);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_BS_ADDR, bypass_kernel);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_BS_SIZE, BYPASS_BYTES);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_IN0_ADDR, a);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_IN0_SS, in_param);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_IN1_ADDR, b);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_IN1_SS, in_param);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_IN2_ADDR, c);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_IN2_SS, in_param);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_IN3_ADDR, d);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_IN3_SS, in_param);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_OUT0_ADDR, e);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_OUT0_SIZE, out_param);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_OUT1_ADDR, f);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_OUT1_SIZE, out_param);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_OUT2_ADDR, g);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_OUT2_SIZE, out_param);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_OUT3_ADDR, h);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_OUT3_SIZE, out_param);
    mmio_region_write32(cgra, (ptrdiff_t) CGRA_CONF, 1UL);
    // Wait CGRA is done
    cgra_intr_flag = 0;
    while(cgra_intr_flag == 0) wait_for_interrupt();

    int flag = 0;
    for(i = 0; i < SIZE; i++) {
        if(a[i] != e[i]) flag++;
        if(b[i] != f[i]) flag++;
        if(c[i] != g[i]) flag++;
        if(d[i] != h[i]) flag++;
    }

    return flag;
}