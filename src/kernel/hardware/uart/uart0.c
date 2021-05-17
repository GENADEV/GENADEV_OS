/*
 *   This file is part of an AArch64 hobbyist OS for the Raspberry Pi 3 B+ called GENADEV_OS 
 *   Everything is openly developed on github: https://github.com/GENADEV/GENADEV_OS
 *   Copyright (C) 2021  Yves Vollmeier and Tim Thompson
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */


#include "../../arm-v-8/mb/mailbox.h"
#include "../../arm-v-8/genadev_os.h"
#include "../gpio/gpio.h"
#include "uart0.h"
#include "mini_uart.h"
#include "../../utils.h"
#include "../../../lib/debug/debug.h"

static bool init_called = false;

void uart0_init(void) {
	if (init_called)
		return;
	
	init_called = true;
	// disable uart0
	*UART0_CR = 0;

	/* set clock rate for consistent divisor values */

	// save all of the needed buffer content which we will pass later into channel 8
	// specific for the SET CLOCK RATE tag
	uint32_t __section_align *mb_buffer;
	
	mb_buffer[0] = 9 * 4;					// total buffer size
	mb_buffer[1] = MB_REQUEST;				// buffer request
	mb_buffer[2] = MB_TAG_SET_CLOCK_RATE;	// tag identifier 
 	mb_buffer[3] = 12;						// value buffer size
	mb_buffer[4] = 8;						// value buffer request/response code 
	mb_buffer[5] = 2;						// value buffer | clock id
	mb_buffer[6] = 4000000;					// value buffer | rate in Hz (4000000 = 4 Mhz)
	mb_buffer[7] = 0;						// value buffer | set turbo (0 == default (enable))
	mb_buffer[8] = 0;						// end tag 

	// write the mailbox buffer to channel 8 - property tags
	mailbox_write(8, mb_buffer);


	/* mapping UART0 to GPIO pins */

	unsigned int selector;

	// GPIO Function select '1'
	selector = *GPFSEL1;
	// clean gpio14
	selector &= ~(7<<12);
	// set alt0 for gpio14
	selector |= 4<<12;
	// clean gpio15
	selector &= ~(7<<15);
	// set alt0 for gpio15
	selector |= 4<<15;
	// load selector into GPIO Function Select 1
	*GPFSEL1 = selector;

	// enable gpio14 and gpio15 
	*GPPUD = 0;
	// delay execution
	delay(150);
	// enable clock0 on both pin 14 and 15
	*GPPUDCLK0 = (1<<14)|(1<<15);
	// delay execution
	delay(150);
	// flush GPIO setup 
	*GPPUDCLK0 = 0;

	*UART0_ICR = 0x7FF;	// clear interrupts
	*UART0_IBRD =  2;		// set baud rate to 11520
	*UART0_FBRD =  0xB;		// set the fractional part of the baud rate divisor value 
	*UART0_LCRH =  0b11<<5; // 8n1
	*UART0_CR = 0x301;		// enable Tx, Rx, FIFO
}

char uart0_recv(void) {
	while((*UART0_FR & 0x10) != 0x0);
	
	return *UART0_DR & 0xFF;
}

int uart0_send(char c) {
	while((*UART0_FR & 0x20) != 0x0);
	
	*UART0_DR = c;
	return 0;
}

void uart0_send_string(char* str) {
	for(int i = 0; str[i] != '\0'; i++) {
		uart0_send(str[i]);
	}
}
