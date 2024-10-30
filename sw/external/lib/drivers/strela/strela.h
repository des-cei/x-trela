#ifndef _STRELA_H
#define _STRELA_H

#include <stdint.h>
#include "core_v_mini_mcu.h"

/*************** Definitions ***************/

#define STRELA_BASE_ADDR EXT_PERIPHERAL_START_ADDRESS

#define PE_POSITION (uint8_t[]){0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15}

/*************** Functions   ***************/

inline uint32_t get_pe_initial_value(uint32_t *conf_addr, uint8_t pe_number) {
	return conf_addr[PE_POSITION[pe_number]*5+2];
}

inline void set_pe_initial_value(uint32_t *conf_addr, uint8_t pe_number, uint32_t value) {
	conf_addr[PE_POSITION[pe_number]*5+2] = value;
}

inline uint32_t get_pe_const(uint32_t *conf_addr, uint8_t pe_number) {
	return conf_addr[PE_POSITION[pe_number]*5+3];
}

inline void set_pe_const(uint32_t *conf_addr, uint8_t pe_number, uint32_t value) {
	conf_addr[PE_POSITION[pe_number]*5+3] = value;
}

inline uint32_t get_pe_delay_value(uint32_t *conf_addr, uint8_t pe_number) {
	return conf_addr[PE_POSITION[pe_number]*5+4] & 0xFFFF0000;
}

inline void set_pe_delay_value(uint32_t * conf_addr, uint8_t pe_number, uint32_t value) {
	conf_addr[PE_POSITION[pe_number]*5+4] = (conf_addr[PE_POSITION[pe_number]*5+4] & 0xFFFF0000) | value;
}

#endif
