#include "../defs.h"
#include "../gpio_config/gpio_config_io.c"

// --------------------------------------------------------
// Firmware routines
// --------------------------------------------------------

uint32_t* mem_pgm_start = (uint32_t*)64;
void (*start_xfer)(void) = 64;

void main() {
	reg_wb_enable = 0;
	reg_gpio_mode1 = 1;
	reg_gpio_mode0 = 0;
	reg_gpio_ien = 1;
	reg_gpio_oe = 1;
	reg_gpio_out = 0;
	
	reg_mprj_io_27 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_37 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_xfer = 1;
	while(reg_mprj_xfer == 1);
	reg_mprj_datal = 1 << 27;
	
	reg_mprj_datah = 0;
	reg_mprj_datal = 0;
	
	reg_mprj_io_0 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_1 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_2 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_3 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_4 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_5 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_6 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_7 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_8 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_9 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_10 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_11 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_12 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_13 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_14 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_15 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_16 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_17 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_18 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_19 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_20 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_21 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_22 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_23 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_24 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_25 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_26 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_27 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_28 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_29 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_30 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_31 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_32 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_33 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_34 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_35 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_36 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_37 = GPIO_MODE_MGMT_STD_OUTPUT;
	
	//reg_mprj_xfer = 1;
	*mem_pgm_start = 0x260007b7;
	mem_pgm_start++;
	*mem_pgm_start = 0x00100713;
	mem_pgm_start++;
	*mem_pgm_start = 0x00e7a023;
	mem_pgm_start++;
	//do {
	//reg_mprj_datal = 0xFFFFFF;
	*mem_pgm_start = 0x260007b7;
	mem_pgm_start++;
	*mem_pgm_start = 0x00c78793;
	mem_pgm_start++;
	*mem_pgm_start = 0xfff00713;
	mem_pgm_start++;
	*mem_pgm_start = 0x00e7a023;
	mem_pgm_start++;
	//reg_mprj_datal = 0;
	*mem_pgm_start = 0x260007b7;
	mem_pgm_start++;
	*mem_pgm_start = 0x00c78793;
	mem_pgm_start++;
	*mem_pgm_start = 0x0007a023;
	mem_pgm_start++;
	//} while(1);
	*mem_pgm_start = 0xfe5ff06f;
	mem_pgm_start++;
	//Padding, so the CPU doesn’t pre-fetch weird values. Idk what that would cause.
	for(int i = 0; i < 16; i++) {
		*mem_pgm_start = 0x00000013;
		mem_pgm_start++;
	}
	
	//Take branch into RAM
	reg_gpio_out = 1;
	start_xfer();
	
	while(1);
}
