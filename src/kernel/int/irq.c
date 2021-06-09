/*
 *   This file is part of an AArch64 hobbyist OS for the Raspberry Pi 3 B+ called GENADEV_OS 
 *   Everything is openly developed on github: https://github.com/GENADEV/GENADEV_OS
 *   Copyright (C) 2021  Yves Vollmeier, Tim Thompson and Michael Buch
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

#include "irq.h"

#include <stdint.h>

#include "../../lib/debug/debug.h"

void handle_undefined_exception(uint32_t exceptionLevel, uint32_t esr,
								uint32_t elr)
{
	debug(DBG_BOTH,
		  "***********************************************\n"
		  "Received exception for which no handler exists:\n"
		  "\tCurrentEL: 0x%lx\n"
		  "\tESR      : 0x%lx\n"
		  "\tELR      : 0x%lx\n"
		  "***********************************************\n",
		  exceptionLevel, esr, elr);
}
