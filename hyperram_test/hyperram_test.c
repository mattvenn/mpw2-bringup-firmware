#include "../defs.h"
#include "../gpio_config/gpio_config_io.c"
//#include "../local_defs.h"
//#include "../stub.c"

// Caravel allows user project to use 0x30xx_xxxx address space on Wishbone bus
// HyperRAM has 8MB -> mask is 0x007fffff
// 0x3000_0000 till 307f_ffff -> RAM / MEM inisde chip
#define hyperram_mem_base_address   0x30000000
#define hyperram_mem_mask           0x007fffff
#define hyperram_mem(offset)        (*(volatile uint32_t*)(hyperram_mem_base_address + (offset & hyperram_mem_mask)))
// 0x3080_00xx -> register space inside chip
#define hyperram_reg_base_address   0x30800000
#define hyperram_reg_mask           0x003fffff
#define hyperram_reg(num)           (*(volatile uint32_t*)(hyperram_reg_base_address + ((2 * num) & hyperram_reg_mask)))
// 0x30c0_00xx -> CSR space for driver / peripheral configuration
#define hyperram_csr_base_address   0x30c00000
#define hyperram_csr_mask           0x003fffff
#define hyperram_csr_latency        (*(volatile uint32_t*)(hyperram_csr_base_address + 0x00))
#define hyperram_csr_tpre_tpost     (*(volatile uint32_t*)(hyperram_csr_base_address + 0x04))
#define hyperram_csr_tcsh           (*(volatile uint32_t*)(hyperram_csr_base_address + 0x08))
#define hyperram_csr_trmax          (*(volatile uint32_t*)(hyperram_csr_base_address + 0x0c))
#define hyperram_csr_status         (*(volatile uint32_t*)(hyperram_csr_base_address + 0x10))


// --------------------------------------------------------
// Firmware routines
// --------------------------------------------------------

void putchar(char c)
{
	if (c == '\n')
		putchar('\r');
    while (reg_uart_txfull == 1);
	reg_uart_data = c;
}

void print(const char *p)
{
	while (*p)
		putchar(*(p++));
}

void blink_short() {
    const int wait=1000000;
    reg_gpio_mode1 = 1;
    reg_gpio_mode0 = 0;
    reg_gpio_ien = 1;
    reg_gpio_oe = 1;
    reg_gpio_out = 0; delay(wait); // ON
    reg_gpio_out = 1; delay(wait); // OFF
}

void blink_long() {
    const int wait=3000000;
    reg_gpio_mode1 = 1;
    reg_gpio_mode0 = 0;
    reg_gpio_ien = 1;
    reg_gpio_oe = 1;
    reg_gpio_out = 0; delay(wait); // ON
    reg_gpio_out = 1; delay(wait); // OFF
}


/*
	IO Test:
		- Configures MPRJ lower 8-IO pins as outputs
		- Observes counter value through the MPRJ lower 8 IO pins (in the testbench)
*/

void main()
{
	/*
	IO Control Registers
	| DM     | VTRIP | SLOW  | AN_POL | AN_SEL | AN_EN | MOD_SEL | INP_DIS | HOLDH | OEB_N | MGMT_EN |
	| 3-bits | 1-bit | 1-bit | 1-bit  | 1-bit  | 1-bit | 1-bit   | 1-bit   | 1-bit | 1-bit | 1-bit   |

	Output: 0000_0110_0000_1110  (0x1808) = GPIO_MODE_USER_STD_OUTPUT
	| DM     | VTRIP | SLOW  | AN_POL | AN_SEL | AN_EN | MOD_SEL | INP_DIS | HOLDH | OEB_N | MGMT_EN |
	| 110    | 0     | 0     | 0      | 0      | 0     | 0       | 1       | 0     | 0     | 0       |


	Input: 0000_0001_0000_1111 (0x0402) = GPIO_MODE_USER_STD_INPUT_NOPULL
	| DM     | VTRIP | SLOW  | AN_POL | AN_SEL | AN_EN | MOD_SEL | INP_DIS | HOLDH | OEB_N | MGMT_EN |
	| 001    | 0     | 0     | 0      | 0      | 0     | 0       | 0       | 0     | 1     | 0       |

	*/

    gpio_config_io();

    // activate the project by setting the 1st bit of 2nd bank of LA
    reg_la1_iena = 0;
    reg_la1_oenb = 0;
    reg_la1_data = 1 << 11;  // hyperram project

    // reset design with 0bit of 1st bank of LA
    reg_la0_iena = 0;
    reg_la0_oenb = 0;
    reg_la0_data = 1;
    delay(50000);
    reg_la0_data = 0;

    // no need for anything else as this design is free running.
    while (1) {
    // write register space inside hyperram
        hyperram_reg(0x2) = 0xa573;

//        reg_mprj_datal = 1 << 8;
//        reg_la0_data = 1;
        blink_long();
 //       reg_mprj_datal = 0 << 8;
 //       reg_la0_data = 0;
        blink_long();
    }
}
