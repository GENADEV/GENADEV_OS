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
.set MMU_BIT, 1 << 1

/*
    ttbr0 points to the first entry of the 4th page table
    ttbr1 points to the last entry of the 4th page table

MMU page structure:
     _____________
    [     PGD     ] (ttbr0/1)
    |     PMD     | (get index from VA)
    |     PUD     | (get index from VA)
    [_____PTE_____] (get offset into phys memory from VA & get index from PUD)

*/

.macro enable_mmu reg
    /* Enable the MMU */
    orr	\reg, \reg, #MMU_BIT
	msr	sctlr_el1, \reg
    isb
.endm

.macro disable_mmu reg
    /* Enable the MMU */
    and	\reg, \reg, #MMU_BIT
	msr	sctlr_el1, \reg
    isb
.endm

/* Load empty page tables (Planned: (Two stages: L1 and L2), Current: One stage: L1 table) and invalidate the TLB */
configure_mmu:
    /* There will not be a stage2 mmu setup since we don't support virtualization */
    
    //Load ttbr0 aka L1 table base address
    adr x0, ttbr0_el1_table_base
    msr ttbr0_el1, x0
    
    //Setup memory attributes
    //
    // 0: 0x44: Normal inner/outer memory (non-cacheable)
    // 1: 0xff: Normal inner/outer (WB/WA/RA)
    // 2: 0x00: Device nGnRnE
    //------------------------
    mov x0, MAIR_ATTR
    msr mair_el1, x0

    /* TCR_EL1 flags */         
                                //The comments below are for convenience
    mov x0, #64                 // T0SZ=0b1000000 (Userspace)
                                // EPD0=0b0      Perform a tablewalk on a TLB miss via the TTBR0
                                // IRGN0=0b00    Walks to TTBR0 are Inner Non-cacheable
    orr x0, x0, #(1 << 10)      // OGRN0=0b01    Walks to TTBR0 are Outer WB/WA
    orr x0, x0, #(2 << 12)      // SH0=0b10      Outer Shareable
                                // TG0=0b00      4KB Granule
    orr x0, x0, #(32 << 16)     // T1SZ=0b100000 (kernel space)
    orr x0, x0, #(1 << 22)      // A1=0b1        TTBR1_EL1 defines the ASID
                                // EPD1=0b0      Translation table walks are allowed after a TLB miss if an address was translated using TTBR1_EL1
    orr x0, x0, #(2 << 24)      // IRGN1=0b10    Walks to TTBR1 are Inner WT/RA/NWA Cacheable (NWA = No write allocate)
                                // ORGN1=0b00    Walks to TTBR1 are Outer Mon-cacheable (The Kernels translation table should make heavy use of the L1 cache for improved speeds, the userspace on the other hand makes heavy use of the L2 cache for stability)

    orr x0, x0, #(2 << 30)      // TG1=0b10      4KB Granule
    orr x0, x0, #(2 << 32)      // IPS=0b010     40 bit IPS size (1TB virtual memory)
                                // AL=0b0        8 bits, Ignored by hardware except for when reading back the register
                                // TBI0=0b0      Top byte is used in the address calculation (TTBR0)
    orr x0, x0, #(1 << 38)      // TBI1=0b1      Top byte is ignored in the address calculation

    msr tcr_el1, x0
    isb

    /* Fill table with invalid entries */
    adr x0, ttbr0_el1_table_base
    mov x1, 512  //One entry for one table, for more tables multiply this value by the amount of tables (we will most likely be using two tables so this value would be 512x2 = 1024 but we don't have multi level tables so the value is 512 for now)

    1:
        str xzr, [x0]
        sub x1, x1, #1
        cbnz x1, 1b

    mov x3, xzr
    enable_mmu x3

    dsb sy

    ret
