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

#include "hardware/uart/mini_uart.h"
#include "../lib/debug/debug.h"
#include "../lib/string/string.h"
#include "int/irq.h"
#include "arm-v-8/mb/mailbox.h"
#include "arm-v-8/genadev_os.h"

void main() {
	// initialize mini uart driver
	mini_uart_init();
	
	debug("GENADEV_OS\n");

	// get current exception level
	int el = 0;
	asm volatile(
		"mrs %0, currentEL\n"
		"lsr %0, %0, 2\n"
		: "=r"(el)
	);
	debug("Current EL: %d\n", el);

	irq_init();

	/* START OF TEST */
	debug("START OF - mailbox test\n");

	// save all of the needed buffer content which we will pass later into channel 8
	// specific for the GET BOARD MODEL tag
	uint32_t __section_align *mb_buffer;
	
	mb_buffer[0] = 8 * 4;					// total buffer size
	mb_buffer[1] = MB_REQUEST;				// buffer request
	mb_buffer[2] = MB_TAG_GET_BOARD_MODEL;	// tag identifier 
 	mb_buffer[3] = 4;						// value buffer size
	mb_buffer[4] = 0;						// value buffer request/response code 
	mb_buffer[5] = 0;						// value buffer 
	mb_buffer[6] = 0;						// end tag 
	mb_buffer[7] = 0;						// padding

	debug("BEFORE WRITE AND READ\n");
	for (int i = 0; i < 8; i++) {
		debug("mailbox[%x] = %x\n", i, mb_buffer[i]);
	}
	
	// write the mailbox buffer to channel 8 - property tags
	mailbox_write(8, mb_buffer);

	// now read from channel 8 - property tags
	mailbox_read(8);

	debug("AFTER WRITE AND READ\n");
	for (int i = 0; i < 8; i++) {
		debug("mailbox[%x] = %x\n", i, mb_buffer[i]);
	}

	// check if the the request was successful
	if(mb_buffer[1] != MB_SUCCESSFUL_RESPONSE)
		debug("request not successful (0x%x)\n", mb_buffer[1]);
		
	debug("END OF - mailbox test\n");	
	/* END OF TEST */
	
	// print everything we receive from the mini uart to the mini uart
	for(;;) {
		mini_uart_send(mini_uart_recv());
	}
}
