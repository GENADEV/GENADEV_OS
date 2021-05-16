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

__export mb_status_t mb_status;

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

	mb_status_t stat = mailbox_send(8, 8 * 4, MB_REQUEST, MB_TAG_GET_BOARD_MODEL, 4, 0, 0, 0, 0);

	// check if the the request was successful
	if(stat.status_code != MB_SUCCESSFUL_RESPONSE)
		debug("request not successful (0x%x)\n", stat.status_code);
	else
		debug("Request successful!\n");
		
	debug("END OF - mailbox test\n");	
	/* END OF TEST */


	// print everything we receive from the mini uart to the mini uart
	for(;;) {
		mini_uart_send(mini_uart_recv());
	}
}
