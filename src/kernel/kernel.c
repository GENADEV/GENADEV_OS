/*
     This file is part of an AArch64 hobbyist OS for the Raspberry Pi 3 B+ called GENADEV_OS
     Everything is openly developed on github: https://github.com/GENADEV/GENADEV_OS
     Copyright (C) 2021  Yves Vollmeier and Tim Thompson

      This program is free software: you can redistribute it and/or modify
      it under the terms of the GNU General Public License as published by
      the Free Software Foundation, either version 3 of the License, or
      (at your option) any later version.

      This program is distributed in the hope that it will be useful,
      but WITHOUT ANY WARRANTY; without even the implied warranty of
      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

#include "arm-v-8/mb/mailbox.h"
#include "arm-v-8/genadev_os.h"
#include "arm-v-8/cpu.h"
#include "hardware/framebuffer/framebuffer.h"
#include "hardware/uart/mini_uart.h"
#include "hardware/uart/uart0.h"
#include "int/irq.h"
#include "../lib/debug/debug.h"
#include "../lib/string/string.h"
#include "panic/panic.h"

void main()
{
	// initialize mini uart and uart0 driver
	mini_uart_init();
	uart0_init();

	debug(DBG_BOTH, "GENADEV_OS\n");

	debug(DBG_UART0, "Hello World from UART0!\n");
	debug(DBG_MINI_UART, "Hello World from MINI UART!\n");

	// get current exception level
	int el = 0;
	asm volatile(
		"mrs %0, currentEL\n"
		"lsr %0, %0, 2\n"
		: "=r"(el)
	);
	debug(DBG_BOTH, "Current EL: %d\n", el);

	irq_init();
	cpu_info();

	panic("Dummy kernel panic (p.s. it's a variadic function %s)", "(No really, it is!)");


	framebuffer_init();
	framebuffer_test();

	for (;;) {}
}
