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


#ifndef LIB_STDIO_H
#define LIB_STDIO_H

/* mini uart putc */
void ua_putc1(char c);

/* mini uart puts */
void ua_puts1(char *s);

/* uart putc */
void ua_putc0(char c);;

/* uart puts */
void ua_puts0(char *s);

/* print formatted string to the framebuffer with ability to set the color of the text */
int printk(uint32_t foreground_color, uint32_t background_color, char *fmt, ...);

#endif // LIB_STDIO_H
