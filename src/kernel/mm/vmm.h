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
#include <stddef.h>

/* Flushes/invalidates the TLB for EL1 only */
#define FLUSH_TLB_EL1() asm("tlbi vmalle1\n")

#define ENTRIES_PER_TABLE       512
#define PAGESIZE                4096

typedef struct {
    uint64_t *TTBR0; //User
    uint64_t *TTBR1; //Kernel
} virtual_memory_root_t;

static inline virtual_memory_root_t TTBR_READ()
{
    virtual_memory_root_t root;
    asm("mrs %0, ttbr0_el1\n" : "=g"((uint64_t)root.TTBR0));
    asm("mrs %0, ttbr1_el1\n" : "=g"((uint64_t)root.TTBR1));
    return root;
}

void virt_mem_init();

#endif // VMM_H