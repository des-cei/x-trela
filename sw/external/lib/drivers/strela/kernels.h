#include <stdint.h>

#define NPE 16
#define CONFIG_SIZE NPE * 5
#define CONFIG_BYTES CONFIG_SIZE * 4

uint32_t bypass_kernel[CONFIG_SIZE] __attribute__((section(".xheep_data_interleaved"))) = {
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 0
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 4
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 8
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 12

    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 1
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 5
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 9
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 13

    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 2
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 6
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 10
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 14

    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 3
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 7
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 11
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000  // 15
};

uint32_t minsearch_kernel[CONFIG_SIZE] __attribute__((section(".xheep_data_interleaved"))) = {
    0xC0000814, 0x00264010, 0x00000000, 0x00000000, 0xCD000000, // 0
    0x40000084, 0x00000000, 0x00000000, 0x00000000, 0x0D000000, // 4
    0x08002002, 0x00000000, 0x00000000, 0x00000000, 0x15000000, // 8
    0x1B000002, 0x18C01040, 0x00000000, 0x00000001, 0xC5000000, // 12

    0x18408000, 0x147809D7, 0x00000032, 0x00000000, 0xF1000064, // 1
    0x921C0001, 0x00000000, 0x00000000, 0x00000000, 0x25000000, // 5
    0x1881000A, 0x04480130, 0x00000000, 0x00000000, 0xF5000000, // 9
    0x03400008, 0x14A801D1, 0x00000050, 0x00000000, 0xE5000064, // 13

    0xD8008420, 0x04680980, 0x00000000, 0x00000000, 0xF5000000, // 2
    0xDA100810, 0x00664010, 0x00000000, 0x00000000, 0xED000000, // 6
    0x00400008, 0x142801D1, 0x00000320, 0x00000000, 0xE5000064, // 10
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 14

    0x80040000, 0x00000000, 0x00000000, 0x00000000, 0x21000000, // 3
    0x00200010, 0x14380C57, 0x00000032, 0x00000000, 0xE5000064, // 7
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 11
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000  // 15
};

uint32_t fft_kernel[CONFIG_SIZE] __attribute__((section(".xheep_data_interleaved"))) = {
    0x580000A1, 0x00402200, 0x00000000, 0x00000007, 0xCD000000, // 0
    0x18800002, 0x00402230, 0x00000000, 0x00000000, 0xE5000000, // 4
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 8
    0xC0000424, 0x00204080, 0x00000000, 0x00000000, 0xCD000000, // 12

    0xC0800401, 0x002040B0, 0x00000000, 0x00000000, 0xED000000, // 1
    0x10080002, 0x00000000, 0x00000000, 0x00000000, 0x25000000, // 5
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 9
    0xC0800011, 0x00200030, 0x00000000, 0x00000000, 0xE5000000, // 13

    0x00000044, 0x00000002, 0x00000000, 0x00000000, 0x0D000000, // 2
    0xC0800400, 0x002000B0, 0x00000000, 0x00000000, 0xE9000000, // 6
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 10
    0xC0000814, 0x00204010, 0x00000000, 0x00000000, 0xCD000000, // 14

    0x80040014, 0x00102046, 0x00000000, 0x00000007, 0xE5000000, // 3
    0x00000402, 0x001020C6, 0x00000000, 0x00000007, 0xCD000000, // 7
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 11
    0xC0800011, 0x00200030, 0x00000000, 0x00000000, 0xE5000000  // 15
};

uint32_t conv2d_1_kernel[CONFIG_SIZE] __attribute__((section(".xheep_data_interleaved"))) = {
    0xC0000020, 0x00202200, 0x00000000, 0x00000000, 0xC5000000, // 0
    0x00000004, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 4
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 8
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 12

    0xC0000020, 0x00202200, 0x00000000, 0xFFFFFFFF, 0xC5000000, // 1
    0x18800010, 0x00400030, 0x00000000, 0x00000000, 0xE5000000, // 5
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 9
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 13

    0xC0000020, 0x00202200, 0x00000000, 0x00000000, 0xC5000000, // 2
    0xC0800010, 0x00200030, 0x00000000, 0x00000000, 0xE5000000, // 6
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 10
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 14

    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 3
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 7
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 11
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000  // 15
};

uint32_t conv2d_2_kernel[CONFIG_SIZE] __attribute__((section(".xheep_data_interleaved"))) = {
    0xC0000020, 0x00202200, 0x00000000, 0xFFFFFFFF, 0xC5000000, // 0
    0x00000004, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 4
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 8
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 12

    0xC0000020, 0x00202200, 0x00000000, 0x00000005, 0xC5000000, // 1
    0x18800010, 0x00400030, 0x00000000, 0x00000000, 0xE5000000, // 5
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 9
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 13

    0xC0000020, 0x00202200, 0x00000000, 0xFFFFFFFF, 0xC5000000, // 2
    0x18800010, 0x00400030, 0x00000000, 0x00000000, 0xE5000000, // 6
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 10
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 14

    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 3
    0xC0800010, 0x00200030, 0x00000000, 0x00000000, 0xE5000000, // 7
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 11
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000  // 15
};

uint32_t relu_kernel[CONFIG_SIZE] __attribute__((section(".xheep_data_interleaved"))) = {
    0xC0000021, 0x00260200, 0x00000000, 0x00000000, 0xC5000000, // 0
    0xC0800010, 0x00202030, 0x00000000, 0x00000000, 0xE5000000, // 4
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 8
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 12

    0xC0000024, 0x00260200, 0x00000000, 0x00000000, 0xC5000000, // 1
    0x00000004, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 5
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 9
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 13

    0xC0810000, 0x00202130, 0x00000000, 0x00000000, 0xF1000000, // 2
    0x02100002, 0x00000000, 0x00000000, 0x00000000, 0x25000000, // 6
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 10
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 14

    0xC0000024, 0x00260200, 0x00000000, 0x00000000, 0xC5000000, // 3
    0xC0000420, 0x00202080, 0x00000000, 0x00000000, 0xCD000000, // 7
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 11
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000  // 15
};

uint32_t dither_filter_kernel[CONFIG_SIZE] __attribute__((section(".xheep_data_interleaved"))) = {
    0xC0000420, 0x00600086, 0x00000000, 0x00000000, 0xCD000000, // 0
    0xD8000020, 0x00664200, 0x00000000, 0x0000007F, 0xC5000000, // 4
    0xC0000020, 0x00202200, 0x00000000, 0x000000FF, 0xC5000000, // 8
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 12

    0x80041000, 0x00000004, 0x00000000, 0x00000000, 0x31000000, // 1
    0x03210022, 0x14880D00, 0x00000000, 0x00000000, 0xF5000000, // 5
    0x03000020, 0x00804200, 0x00000000, 0x000000FF, 0xC5000000, // 9
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 13

    0xC0000420, 0x00600086, 0x00000000, 0x00000000, 0xCD000000, // 2
    0xD8000020, 0x00664200, 0x00000000, 0x0000007F, 0xC5000000, // 6
    0xC0000020, 0x00202200, 0x00000000, 0x000000FF, 0xC5000000, // 10
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 14

    0x80041000, 0x00000004, 0x00000000, 0x00000000, 0x31000000, // 3
    0x03210022, 0x14880D00, 0x00000000, 0x00000000, 0xF5000000, // 7
    0x03000020, 0x00804200, 0x00000000, 0x000000FF, 0xC5000000, // 11
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000  // 15
};

uint32_t mult_cte_m_v_kernel[CONFIG_SIZE] __attribute__((section(".xheep_data_interleaved"))) = {
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 0
    0x00000004, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 4
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 8
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 12

    0xC0000020, 0x00202200, 0x00000000, 0x00000007, 0xC5000000, // 1
    0xD0880010, 0x00202030, 0x00000000, 0x00000000, 0xE5000000, // 5
    0x00000020, 0x08201001, 0x00000000, 0x00000000, 0x4500000F, // 9
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 13

    0xC0000020, 0x00202200, 0x00000000, 0x00000007, 0xC5000000, // 2
    0xD0880010, 0x00202030, 0x00000000, 0x00000000, 0xE5000000, // 6
    0x00000020, 0x08201001, 0x00000000, 0x00000000, 0x4500000F, // 10
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 14

    0xC0000020, 0x00202200, 0x00000000, 0x00000007, 0xC5000000, // 3
    0xC0800010, 0x00202030, 0x00000000, 0x00000000, 0xE5000000, // 7
    0x00000020, 0x08201001, 0x00000000, 0x00000000, 0x4500000F, // 11
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000  // 15
};

uint32_t sum_cte_v_v_kernel[CONFIG_SIZE] __attribute__((section(".xheep_data_interleaved"))) = {
    0xC0000420, 0x00200080, 0x00000000, 0x00000000, 0xCD000000, // 0
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 4
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 8
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 12

    0x00000020, 0x00102206, 0x00000000, 0x00000007, 0xC5000000, // 1
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 5
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 9
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 13

    0xC0000420, 0x00200080, 0x00000000, 0x00000000, 0xCD000000, // 2
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 6
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 10
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 14

    0x00000020, 0x00102206, 0x00000000, 0x00000007, 0xC5000000, // 3
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 7
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 11
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000  // 15
};

uint32_t dot_product_kernel[CONFIG_SIZE] __attribute__((section(".xheep_data_interleaved"))) = {
    0x00000004, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 0
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 4
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 8
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 12

    0xD0880010, 0x00202030, 0x00000000, 0x00000000, 0xE5000000, // 1
    0x00000020, 0x08201001, 0x00000000, 0x00000000, 0x4500000F, // 5
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 9
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 13

    0xD0880010, 0x00202030, 0x00000000, 0x00000000, 0xE5000000, // 2
    0x00000020, 0x08201001, 0x00000000, 0x00000000, 0x4500000F, // 6
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 10
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 14

    0xC0800010, 0x00202030, 0x00000000, 0x00000000, 0xE5000000, // 3
    0x00000020, 0x08201001, 0x00000000, 0x00000000, 0x4500000F, // 7
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 11
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000  // 15
};

uint32_t gemver_0_kernel[CONFIG_SIZE] __attribute__((section(".xheep_data_interleaved"))) = {
    0xC0000420, 0x00200080, 0x00000000, 0x00000000, 0xCD000000, // 0
    0xC0000420, 0x00200080, 0x00000000, 0x00000000, 0xCD000000, // 4
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 8
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 12

    0x00000012, 0x00102046, 0x00000000, 0x00000007, 0xC5000000, // 1
    0x18000050, 0x00402042, 0x00000000, 0x00000007, 0xCD000000, // 5
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 9
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 13

    0x18000012, 0x00402040, 0x00000000, 0x00000007, 0xC5000000, // 2
    0x10080010, 0x00102046, 0x00000000, 0x00000007, 0xE5000000, // 6
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 10
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 14

    0xC0400020, 0x00200180, 0x00000000, 0x00000000, 0xE5000000, // 3
    0xC0400020, 0x00200180, 0x00000000, 0x00000000, 0xE5000000, // 7
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 11
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000  // 15
};

uint32_t gemver_0_1_kernel[CONFIG_SIZE] __attribute__((section(".xheep_data_interleaved"))) = {
    0xC0000420, 0x00200080, 0x00000000, 0x00000000, 0xCD000000, // 0
    0xC0000420, 0x00200080, 0x00000000, 0x00000000, 0xCD000000, // 4
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 8
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 12

    0x00000010, 0x00102046, 0x00000000, 0x00000007, 0xC5000000, // 1
    0x00000040, 0x00000002, 0x00000000, 0x00000000, 0x09000000, // 5
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 9
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 13

    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 2
    0x00000010, 0x00102046, 0x00000000, 0x00000007, 0xC5000000, // 6
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 10
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 14

    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 3
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 7
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 11
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000  // 15
};

uint32_t gemver_2_kernel[CONFIG_SIZE] __attribute__((section(".xheep_data_interleaved"))) = {
    0xC0000420, 0x00200080, 0x00000000, 0x00000000, 0xCD000000, // 0
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 4
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 8
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 12

    0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 1
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 5
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 9
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 13

    0xC0000420, 0x00200080, 0x00000000, 0x00000000, 0xCD000000, // 2
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 6
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 10
    0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 14

    0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x05000000, // 3
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 7
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, // 11
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000  // 15
};
