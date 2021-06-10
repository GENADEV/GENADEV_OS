/*
    This file is part of an AArch64 hobbyist OS for the Raspberry Pi 3 B+ called
    GENADEV_OS Everything is openly developed on github:
    https://github.com/GENADEV/GENADEV_OS Copyright (C) 2021  GENADEV_OS and it's
    affiliates This program is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as published by
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

#include "../../../lib/assert.h"
#include "../../../lib/debug/debug.h"
#include "../../../lib/stdio/stdio.h"

#define MILLISECONDS_IN_SECONDS 1000

static uint32_t s_counterFrequency = 0;

// In milliseconds
static uint32_t s_tickInterval = 1000;

void handle_timer_irq(void)
{
	uint32_t cntvct;

	kassert(s_tickInterval > 0);

	asm volatile(
		"msr cntv_tval_el0, %1    \n\t"	 // Set timer for in 1 second
		""
		"mrs %0, cntvct_el0       \n\t"	 // Read virtual counter
		: "=r"(cntvct)
		: "r"(s_tickInterval));

	debug(DBG_BOTH,
		  "Entered timer IRQ handler.\n"
		  "...Setting [cntv_tval_el0 = 0x%x]\n"
		  "......with [cntvct_el0    = 0x%x]\n",
		  s_tickInterval, cntvct);
}

void timer_init(uint32_t ms_interval)
{
	asm volatile("mrs %0, cntfrq_el0" : "=r"(s_counterFrequency));

	s_tickInterval = ((uint64_t)s_counterFrequency * ms_interval) / MILLISECONDS_IN_SECONDS;

	kassert(s_counterFrequency > 0 && s_tickInterval > 0);

	asm volatile(
		"msr cntv_tval_el0, %0    \n\t"	 // Initialize EL1 virtual timer value
		""
		"mov x1, #1               \n\t"
		"msr cntv_ctl_el0, x1     \n\t"	 // Enable virtual timer
		:
		: "r"(s_tickInterval)
		: "x1");

	debug(DBG_BOTH,
		  "Initializing timer on core 0.\n"
		  "...Setting [cntv_tval_el0 = 0x%x]\n"
		  "......with [cntfrq_el0 = 0x%x]\n",
		  s_tickInterval, s_counterFrequency);

	// Enable core 0's virtual timer interrupt
	// See BCM2836 Rev 3.4, section on
	// "Core timers interrupts"
	*CORE0_TIMER_IRQCNTL = CNTVIRQ_CTL;
}
