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
*/


#include "../../kernel/hardware/uart/mini_uart.h"
#include "../../kernel/hardware/uart/uart0.h"
#include "debug.h"
#include <stdarg.h>
#include "../stdio/fmt.h"
#include "../stdio/stdio.h"

// buffer for the formatted string
const char debug_buff[512];
int debug(int uart_device, char *fmt, ...)
{
	// Only use a device ranging from 0-1 or both
	if (uart_device > 2 || uart_device < 0)
		return 1;

	va_list ap;
	va_start(ap, fmt);
	vsnprintf((char*)&debug_buff, -1, fmt, ap);

	if (uart_device == 2)
		ua_puts1((char*)debug_buff), ua_puts0((char*)debug_buff);
	else
		(uart_device == 1) ? ua_puts1((char*)debug_buff) : ua_puts0((char*)debug_buff);

	va_end(ap);
	return 0;
}
