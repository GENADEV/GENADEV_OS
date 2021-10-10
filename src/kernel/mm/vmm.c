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

#include "vmm.h"
#include <stdbool.h>
#include <stddef.h>
#include <lib/debug/debug.h>
#include <lib/assert.h>
#include <kernel/arm-v-8/genadev_os.h>

static uint64_t *PGD;
virtual_memory_root_t root;

void vmap(uint64_t virt, uint64_t phys, int flags);

void virt_mem_init()
{
    PGD = (uint64_t*)GET_PGD();
    root = (virtual_memory_root_t) { .TTBR0 = NULL, .TTBR1 = PGD };

    vmap(VA_KERNEL_BASE, 0x80000, 0x3);
    asm ("msr ttbr0_el1, %0" :: "g"(root.TTBR1));
}

uint64_t *get_next_entry(uint64_t *pml, int level, int flags)
{
    //Check present bit in the table entry
    if (pml[level] & 0b1)
    {
        goto no_alloc;
    }

    no_alloc:
    return (uint64_t*)(pml[level] & ~(511));
}

void vmap(uint64_t virt, uint64_t phys, int flags)
{
    /* Ensure addresses are page aligned */
    kassert(virt % PAGESIZE == 0);
    kassert(phys % PAGESIZE == 0);
    
    //bits 64:48 are either all 1 or all 0. All 1 = ttbr1, all 0 = ttbr0
    bool is_ttbr1 = (virt >> 48) & 0xFFFF;
    size_t indexL1 = (virt >> 39) & 0x1FF; //0x1FF ~ 0b111111111
    size_t indexL2 = (virt >> 30) & 0x1FF;

    uint64_t *L1 = NULL; // PGD
    uint64_t *L2 = NULL; // PUD

    L1 = get_next_entry(PGD, indexL1, flags);
    L2 = get_next_entry(L1, indexL2, flags);
    // L2[indexL2] = (phys | flags);
}