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

#ifndef VMM_H
#define VMM_H
#include <stdint.h>

static inline uint64_t GET_PGD()
{
    uint64_t res;
    asm("mrs %0, ttbr0_el1\n" : "=r"(res));
    return res;
}

/* Flushes/invalidates the TLB for EL1 only */
#define FLUSH_TLB_EL1() asm("tlbi vmalle1\n")

struct paging_hierarchy
{
    uint64_t PGD; //Page Global Directory
    uint64_t PUD; //Page Upper Directory
    uint64_t PMD; //Page Middle Directory
    uint64_t PTE; //Page Table Entry
};


#endif // VMM_H