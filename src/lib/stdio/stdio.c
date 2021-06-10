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


#include "../../kernel/hardware/framebuffer/framebuffer.h"
#include "../../kernel/hardware/uart/mini_uart.h"
#include "../../kernel/hardware/uart/uart0.h"
#include "stdio.h"
#include <stdarg.h>
#include "../stdio/fmt.h"

void ua_putc0(char c)
{
	uart0_send(c);
}

void ua_puts0(char *s)
{
	uart0_send_string(s);
}

void ua_putc1(char c)
{
	mini_uart_send(c);
}

void ua_puts1(char *s)
{
	mini_uart_send_string(s);
}

// buffer for the formatted string
const char printk_buff[512];
int printk(uint32_t foreground_color, uint32_t background_color, char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vsnprintf((char*)&printk_buff, -1, fmt, ap);

	framebuffer_print_string((char*)printk_buff, foreground_color, background_color);

	va_end(ap);
	return 0;
}
