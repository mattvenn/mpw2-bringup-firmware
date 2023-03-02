#include "../defs.h"
#include "../gpio_config/gpio_config_io.c"
//#include "../local_defs.h"
//#include "../stub.c"

// --------------------------------------------------------
// Firmware routines
// --------------------------------------------------------

#define MPRJ_BASE 0x30000000
#define REG0 ((volatile uint32_t*) (MPRJ_BASE + 0x00))
#define REG1 ((volatile uint32_t*) (MPRJ_BASE + 0x04))
#define REG2 ((volatile uint32_t*) (MPRJ_BASE + 0x08))
#define REG3 ((volatile uint32_t*) (MPRJ_BASE + 0x0c))

#define MPRJ_FB 0x30000100
#define FB0 ((volatile uint32_t*) (MPRJ_FB + 0x00))
#define FB1 ((volatile uint32_t*) (MPRJ_FB + 0x04))
#define FB2 ((volatile uint32_t*) (MPRJ_FB + 0x08))
#define FB3 ((volatile uint32_t*) (MPRJ_FB + 0x0c))

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

    /*
	reg_mprj_io_8    =  GPIO_MODE_USER_STD_OUTPUT;
	reg_mprj_io_9 =  GPIO_MODE_USER_STD_OUTPUT;
	reg_mprj_io_10 =  GPIO_MODE_USER_STD_OUTPUT;
	reg_mprj_io_11 =  GPIO_MODE_USER_STD_OUTPUT;
	reg_mprj_io_12 =  GPIO_MODE_USER_STD_OUTPUT;
	reg_mprj_io_13 =  GPIO_MODE_USER_STD_OUTPUT;
	reg_mprj_io_14 =  GPIO_MODE_USER_STD_OUTPUT;
	reg_mprj_io_15 =  GPIO_MODE_USER_STD_OUTPUT;
	reg_mprj_io_16 =  GPIO_MODE_USER_STD_OUTPUT;
    */

    gpio_config_io();

    // activate the project by setting the 1st bit of 2nd bank of LA
    reg_la1_iena = 0;
    reg_la1_oenb = 0;
    reg_la1_data = 1 << 12;  // 1st project

    // reset design with 0bit of 1st bank of LA
    reg_la0_iena = 0;
    reg_la0_oenb = 0;
    reg_la0_data = 1;
    delay(50000);
    reg_la0_data = 0;


    // set the screen to be white
    *REG2 = 0x00FF00FF;
    *REG3 = 0x00000000;     

    *FB0  = 0xFFFFFFFF;
    *FB1  = 0xFFFFFFFF;
    *FB2  = 0xFFFFFFFF;
    *FB3  = 0xFFFFFFFF;     

    *REG0 = 0x7FFF;     

    // no need for anything else as this design is free running.
    while (1) {
        blink_short();
        for( int i = 0; i < 0xFFFF; i += 0xFF)
            *REG0 = i;
    }
}
