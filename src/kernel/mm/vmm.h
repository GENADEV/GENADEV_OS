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
#include <stdbool.h>

/* Flushes/invalidates the TLB for EL1 only */
#define FLUSH_TLB_EL1() asm("tlbi vmalle1\n")

#define ENTRIES_PER_TABLE       512
#define PAGESIZE                4096

typedef uint64_t pte_t;

typedef struct {
    uint64_t *TTBR0; //User
    uint64_t *TTBR1; //Kernel
} virtual_memory_root_t;

enum {
    PTE_PRESENT = (1 << 0),
    PTE_PAGE    = (1 << 1),
    PTE_RW      = (0 << 7)
};

typedef enum {
    four_kib = 9, /* 9 bits for 4KiB wide pages */
} page_granularity_t;

static inline virtual_memory_root_t TTBR_READ()
{
    virtual_memory_root_t root;
    asm("mrs %0, ttbr0_el1\n" : "=g"((uint64_t)root.TTBR0));
    asm("mrs %0, ttbr1_el1\n" : "=g"((uint64_t)root.TTBR1));
    return root;
}

static inline uint64_t table_index(uint64_t virt, int bit_offset, int level, page_granularity_t gran)
{
    return (virt >> (bit_offset - gran * level)) & 0x1FF; // 0x1FF  ~ 0b111111111 (9 bits, the exact size that reveals the table index)
}

/* Return a PTE without flags (example: 0x1003 -> 0x1000) */
static inline pte_t *pte_flags_to_raw_pte(pte_t pte)
{
    return (pte_t*) (pte & ~(0xFFF));
}

static inline bool is_page_aligned(uint64_t addr)
{
    return (addr % PAGESIZE) == 0;
}

void virt_mem_init();

#endif // VMM_H