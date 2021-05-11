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

#include "debug.h"
#include <stdarg.h>
#include "../stdio/fmt.h"
#include "../stdio/stdio.h"
#include "../../kernel/hardware/uart/mini_uart.h"

extern mini_uart_status_t status;

//buffer for the formatted string
const char debug_buff[512];
int debug(char *fmt, ...)
{
    if (!status.init_true)
        return 1;
        
    va_list ap;
    va_start(ap, fmt);
    vsnprintf((char*)&debug_buff, -1, fmt, ap);

    ua_puts((char*)debug_buff);

    va_end(ap);
    return 0;
}
