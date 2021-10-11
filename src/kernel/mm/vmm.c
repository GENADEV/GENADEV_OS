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

/*
    Since the RPI 3 has only 4GiB of RAM we can get away with 2 level page tables, the PGD and PUD.
*/
#include "vmm.h"
#include "memdef.h"
#include <stdbool.h>
#include <stddef.h>
#include <lib/debug/debug.h>
#include <lib/assert.h>
#include <kernel/arm-v-8/genadev_os.h>
#include <kernel/hardware/gpio/mmio_base.h>

virtual_memory_root_t root;

void vmap(uint64_t virt, uint64_t phys, int flags, bool kernel);

void virt_mem_init()
{
    root = TTBR_READ();

    /* This is just used to test vmap() */
    vmap(MMIO_BASE, MMIO_BASE, 0x3, true);
}

//https://github.com/s-matyukevich/raspberry-pi-os/blob/master/docs/lesson06/rpi-os.md#page-descriptor-format
uint64_t *get_next_entry(uint64_t *pml, int level, int flags)
{
    // TODO:
    // if page.NOT_PRESENT:
    //  create_pte() <-- pmm_alloc() a page and whatnot
    //
    if (pml[level] & 1)
    {
        debug(DBG_BOTH, "Present bit set\n");
    } 
    else
    {
        debug(DBG_BOTH, "Present bit NOT set\n");
    }

    /* Todo: Figure out whether a set bit is a specifying a table or block descriptor */
    if (pml[level] & 2)
    {
        debug(DBG_BOTH, "Block/Table bit is set\n");
    }
    else 
    {
        debug(DBG_BOTH, "Block/Table bit is NOT set\n");
    }

    // Causes data abort- investigate
    // return (uint64_t*)(pml[level] & ~(511));

    return 0;
}

void vmap(uint64_t virt, uint64_t phys, int flags, bool kernel)
{
    /* Ensure addresses are page aligned */
    kassert(virt % PAGESIZE == 0);
    kassert(phys % PAGESIZE == 0);
    
    //bits 64:48 are either all 1 or all 0. All 1 = ttbr1, all 0 = ttbr0
    bool is_ttbr1  = (virt >> 48) & 0xFFFF; // 0xFFFF ~ 0b111111111111 (16 bits)
    size_t indexL1 = (virt >> 39) & 0x1FF;  // 0x1FF  ~ 0b111111111 (9 bits, the exact size that reveals the table index)
    size_t indexL2 = (virt >> 30) & 0x1FF;

    uint64_t *L1 = NULL; // PGD
    uint64_t *L2 = NULL; // PUD

    //Rough draft of a table walk, subject to change in the future
    L1 = get_next_entry(kernel ? root.TTBR1 : root.TTBR0, indexL1, flags);
    L2 = get_next_entry(L1, indexL2, flags);
    L2[indexL2] = (phys | flags);
}