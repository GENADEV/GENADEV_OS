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

#ifndef GENADEV_OS_H
#define GENADEV_OS_H

/* Macros to replace the old type names, make the code look cleaner or optimize functions which use these defines */
#define __export extern 
#define __no_optimize volatile
#define __no_return __attribute__((noreturn)) void
#define __section_align  __attribute__((aligned (16)))
#define __section_align8 __attribute__((aligned (8)))

#define R_MASK_AND_EXTRACT_BITS(val, n, mask) ((val >> n) & mask) //Perform a rightshift (R) by `n' bits and mask the bits
#define L_MASK_AND_EXTRACT_BITS(val, n, mask) ((val << n) & mask) //Perform a leftshift (L) by `n' bits and mask the bits

#define R_EXTRACT_BITS(val, n) (val >> n) //Extract `n' bits by performing a rightshift
#define L_EXTRACT_BITS(val, n) (val << n) //Extract `n' bits by performing a rightshift

#endif // GENADEV_OS_H
