/*
    This file is part of an AArch64 hobbyist OS for the Raspberry Pi 3 B+ called GENADEV_OS
    Everything is openly developed on github: https://github.com/GENADEV/GENADEV_OS
    Copyright (C) 2021  GENADEV_OS and it's affiliates
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
     
    Authors: The GENADEV_OS Founder Yves Vollmeier <https://github.com/Tix3Dev> and the lead developer Tim Thompson <https://github.com/V01D-NULL>
	Contributers: All of the GENADEV_OS Contributers (tysm ^^) (Do not edit this section)
*/


#include "arm-v-8/mb/mailbox.h"
#include "arm-v-8/genadev_os.h"
#include "arm-v-8/cpu.h"
#include "hardware/framebuffer/framebuffer.h"
#include "hardware/uart/mini_uart.h"
#include "hardware/timer/timer.h"
#include "hardware/uart/uart0.h"
#include "int/irq.h"
#include "../lib/debug/debug.h"
#include "../lib/stdio/stdio.h"
#include "../lib/string/string.h"
#include "panic/panic.h"
#include "mm/vmm.h"
#include "smp/spinlock.h"
#include "../lib/assert.h"

void main()
{
	// initialize mini uart and uart0 driver
	mini_uart_init();
	uart0_init();

	debug(DBG_BOTH, "GENADEV_OS\n");

	// get current exception level
	int el = 0;
	asm volatile(
		"mrs %0, currentEL\n"
		"lsr %0, %0, 2\n"
		: "=r"(el)
	);
	debug(DBG_BOTH, "Current EL: %d\n", el);

	irq_init();
	timer_init();
	irq_enable();

	cpu_info();

	framebuffer_init();
	framebuffer_set_background_color(0xFF27DFF8);
	printk(0xFF27DFF8, 0xFFF9AC37, "Hello World! My name is: %s.", "Tix3Dev");

	kassert(1 > 2);

	for (;;) {}
}
