#include <stdio.h>
#include <stdint.h>
#include "core_v_mini_mcu.h"
#include "csr.h"
#include "csr_registers.h"
#include "mmio.h"
#include "hart.h"
#include "handler.h"
#include "fast_intr_ctrl.h"
#include "fast_intr_ctrl_regs.h"
#include "cgra.h"
#include "kernels.h"
#include "dataset.h"

// -------------------- CGRA -------------------- //
mmio_region_t cgra;
volatile uint8_t cgra_intr_flag;

void fic_irq_cgra(void) {
    cgra_intr_flag = 1;
}
// -------------------- CGRA -------------------- //


int main(int argc, char *argv[])
{
    enable_all_fast_interrupts(true);
    // Enable interrupt on processor side
    // Enable global interrupt for machine-level interrupts
    CSR_SET_BITS(CSR_REG_MSTATUS, 0x8);
    // Set mie.MEIE bit to one to enable machine-level fast interrupts
    const uint32_t mask = 1 << 30;
    CSR_SET_BITS(CSR_REG_MIE, mask);

    // CGRA setup
    cgra = mmio_region_from_addr(CGRA_BASE_ADDR);
    const uint32_t in_param = (sizeof(int32_t) << 16) | RESULT_SIZE * sizeof(int32_t);
    const uint32_t out_param = RESULT_SIZE * sizeof(int32_t);

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

    int flag = 0;
    // for(i = 0; i < SIZE; i++) {
    // }
    // if(flag ==0) printf("SUCCESS\n");
    // else printf("FAIL\n");
    return flag;
}