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

#include "panic.h"
#include <stdarg.h>
#include "../../lib/stdio/fmt.h"
#include "../../lib/debug/debug.h"

char panic_buff[512];
__no_return panic(int frame_ptr, const char *err, ...)
{
	va_list ap;
	va_start(ap, err);
	vsnprintf((char*)&panic_buff, -1, err, ap);

	debug(DBG_BOTH,
		  "\n---= KERNEL PANIC =---\n"
		  "Fault: %s\n",
		  (char*)panic_buff
		 );

	debug(DBG_BOTH, "Frame pointer: 0x%x\n", frame_ptr);

	for (;;);
}