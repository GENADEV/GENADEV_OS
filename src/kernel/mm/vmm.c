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

void validate_alignment(uint64_t virtual, uint64_t physical);
void vmap(uint64_t virt, uint64_t phys, int flags, bool kernel);

void virt_mem_init()
{
    root = TTBR_READ();

    /* vmap() tests */
    vmap(VA_KERNEL_BASE + MMIO_BASE, MMIO_BASE, 0x3, true); //Normal mapping
    vmap(0xfff2000000000000, 0x0, 0x3, true); //Malformed virtual address
}

//https://github.com/s-matyukevich/raspberry-pi-os/blob/master/docs/lesson06/rpi-os.md#page-descriptor-format
pte_t *get_next_entry(uint64_t *pml, int level, int flags)
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

    return pte_flags_to_raw_pte(pml[level]);
}

void vmap(uint64_t virt, uint64_t phys, int flags, bool kernel)
{
    /* Ensure addresses are page aligned */
    validate_alignment(virt, phys);

    //bits 64:48 are either all 1 or all 0. All 1 = ttbr1, all 0 = ttbr0
    bool is_ttbr1 = (virt >> 48) & 0xFFFF;  // 0xFFFF ~ 0b111111111111 (16 bits)

    uint64_t upper16 = (virt >> 48) & 0xFFFF;
    if (upper16 != 0xFFFF && upper16 != 0x0000)
    {
        panic("Malformed virtual address (upper 16 bits must be 0xFFFF or 0x0000, got: 0x%X)", (virt >> 48) & 0xFFFF);
    }
    
    size_t indexL0 = table_index(virt, 39, 0, four_kib);
    size_t indexL1 = table_index(virt, 30, 1, four_kib);

    pte_t *L0 = NULL; // PGD
    pte_t *L1 = NULL; // PUD

    //Rough draft of a table walk, subject to change in the future
    L0 = get_next_entry(kernel ? root.TTBR1 : root.TTBR0, indexL0, flags);
    L1 = get_next_entry(L1, indexL1, flags);
    L1[indexL1] = (phys | flags);
}

/* TODO: Do we really need to check if the physical address is aligned? 
   The pmm returns page aligned blocks of memory after all */
void validate_alignment(uint64_t virtual, uint64_t physical)
{
    if (!is_page_aligned(virtual))
        panic("Virtual address is not page aligned! [ %llX ]\n", virtual);
    
    else if (!is_page_aligned(physical))
        panic("Physical address is not page aligned! [ %llX ]\n", physical);
}