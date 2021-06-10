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

#ifndef KERNEL_PANIC_H
#define KERNEL_PANIC_H

#include "../arm-v-8/genadev_os.h"

#define GET_FRAMEPOINTER() __fp()

static inline int __fp()
{
    int frame_pointer;
    asm volatile("mov %0, x29\n" : "=g"(frame_pointer));
    return frame_pointer;
}

__no_return panic(const char *err, ...);
int assertion_failure(const char *err, ...);

#endif // KERNEL_PANIC_H