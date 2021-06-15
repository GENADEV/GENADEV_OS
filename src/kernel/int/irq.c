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

    Author: Tim Thompson <https://github.com/V01D-NULL>
    Contributor: Michael Buch <https://github.com/Michael137>
*/

#include "irq.h"

#include <stdint.h>

#include "../../lib/debug/debug.h"
#include "../hardware/timer/timer.h"

void handle_undefined_exception(uint32_t currentEL, uint32_t esr,
								uint32_t elr)
{
	debug(DBG_BOTH,
		  "***********************************************\n"
		  "Received exception for which no handler exists:\n"
		  "\tCurrentEL: 0x%lx\n"
		  "\tESR      : 0x%lx\n"
		  "\tELR      : 0x%lx\n"
		  "***********************************************\n",
		  currentEL >> 2, esr, elr);
}

void handle_irq(void)
{
	switch (*CORE0_IRQ_SOURCE)
	{
		case CORE_INT_SOURCE_CNTVIRQ:
			handle_timer_irq();
			break;

		default:
			debug(DBG_BOTH,
				  "[WARNING] Unknown IRQ received:\n"
				  "\tIRQ_PENDING_1: %x\n"
				  "\tIRQ_PENDING_2: %x\n"
				  "\tIRQ_BASIC_PENDING: %x\n"
				  "\tIRQ_CORE0_INTERRUPT_SOURCE: %x\n"
				  "\tIRQ_CORE1_INTERRUPT_SOURCE: %x\n"
				  "\tIRQ_CORE2_INTERRUPT_SOURCE: %x\n"
				  "\tIRQ_CORE3_INTERRUPT_SOURCE: %x\n",
				  *IRQ_PENDING_1, *IRQ_PENDING_2, *IRQ_BASIC_PENDING,
				  *CORE0_IRQ_SOURCE, *CORE1_IRQ_SOURCE, *CORE2_IRQ_SOURCE,
				  *CORE3_IRQ_SOURCE);
			break;
	}
}
