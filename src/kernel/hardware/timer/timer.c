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
     
    Author: Michael Buch <https://github.com/Michael137>
*/

#include "timer.h"

#include "../../../lib/debug/debug.h"
#include "../../../lib/stdio/stdio.h"

void handle_timer_irq(void)
{
	uint32_t cntvct;
	uint32_t cntv_tval;
	asm volatile(
		"mrs %0, cntfrq_el0       \n\t"
		"msr cntv_tval_el0, %0    \n\t" // Set timer for in 1 second
		""
		"mrs %1, cntvct_el0       \n\t" // Read virtual counter
		: "+r"(cntv_tval), "=r"(cntvct)
		:
		:"x0");

	debug(DBG_BOTH, "Entered timer IRQ handler.\n"
		  "...[cntv_tval_el0 = 0x%x]\n"
		  "...[cntvct_el0    = 0x%x]\n"
		  , cntv_tval, cntvct);
}

void timer_init(void)
{
	uint32_t cntv_tval;
	asm volatile(
		"mrs %0, cntfrq_el0       \n\t"
		"msr cntv_tval_el0, %0    \n\t" // Initialize EL1 virtual timer value
		""
		"mov x0, #1               \n\t"
		"msr cntv_ctl_el0, x0     \n\t" // Enable virtual timer
		: "+r"(cntv_tval)
		:
		:"x0");

	debug(DBG_BOTH, "Initializing timer on core 0.\n"
		  "...Setting [cntrfrq_el0 = 0x%x]\n",
		  cntv_tval);

	// Enable core 0's virtual timer interrupt
	// See BCM2836 Rev 3.4, section on
	// "Core timers interrupts"
	*CORE0_TIMER_IRQCNTL = CNTVIRQ_CTL;
}
