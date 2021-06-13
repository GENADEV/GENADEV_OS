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

.set MAIR_ATTR, 0x000000000000FF44

/*
    ttbr0 points to the first entry of the 4th page table
    ttbr1 points to the last entry of the 4th page table

MMU page structure:
     _____________
    [     PGD     ] (ttbr0/1)
    |     PMD     | (get index from VA)
    |     PUD     | (get index from VA)
    [_____PTE_____] (get offset into phys memory from VA + get index from PUD)



*/

.set MMU_ENABLE, 1 << 0

configure_mmu:
    /* Stage1 MMU setup */

    //Load ttbr0 aka L1 table base address
    ldr x0, =ttbr0_el1_table_base
    msr ttbr0_el1, x0
    
    //Setup memory attributes
    //
    // 0: 0x44: Normal inner/outer memory (non-cacheable)
    // 1: 0xff: Normal inner/outer (WB/WA/RA)
    // 2: 0x00: Device nGnRnE
    //------------------------
    mov x0, MAIR_ATTR
    msr mair_el1, x0


    //Set TCR
    mov x0, #32
    orr x0, x0, #(0x1 << 8)              // IGRN0=0b01    Walks to TTBR0 are Inner WB/WA
    orr x0, x0, #(0x1 << 10)             // OGRN0=0b01    Walks to TTBR0 are Outer WB/WA
    orr x0, x0, #(0x3 << 12)             // SH0=0b11      Inner Shareable
                                            // TBI0=0b0      Top byte not ignored
                                            // TG0=0b00      4KB granule
                                            // IPS=0         32-bit PA space

    msr tcr_el1, x0
    isb //The above events are not always in-order exection so we use isb to wait for everything to complete



    ret


/* L1 and L2 tables (aligned to 4KiB) */
.section page_tables

ttbr0_el1_table_base:
    .fill 4096, 1, 0

ttbr1_el1_table_base:
    .fill 4096, 1, 0
