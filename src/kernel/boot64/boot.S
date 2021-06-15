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
	Contributer: Michael Buch
*/


.extern bss_begin
.extern bss_end
.include "src/kernel/mm/mmu.S"
.include "src/kernel/arm-v-8/asm/macros.S"
.include "src/kernel/arm-v-8/asm/sys_ctrl.S"

.section .text.boot
.include "src/kernel/boot64/EL_switch.S"

.global _start
_start:
    /* For now all but the primary core will be suspended */
    mrs x0, mpidr_el1   // Multiprocessor Affinity Register
    and x0, x0, #0xFF   // Lower 8 bits indicate the core no.
    cbz x0, drop_to_el2 // Is the Core ID == 0? (Main core)
    hang                // Stop the core

.globl el1_entry
el1_entry:
    bl bss_zero
    bl configure_mmu
    bl enable_instruction_caching
    bl main
    hang

bss_zero:
    //Get size of bss section
    mov sp, x0
    adr x0, bss_begin
    adr x1, bss_end
    sub x1, x1, x0
    1:
        str xzr, [x0], #8
        subs x1, x1, #8
        b.gt 1b
    ret


/* L1 lookup table (We will use multilevel translation tables later on) */
.section .page_tables
.globl ttbr0_el1_table_base
ttbr0_el1_table_base:
    .space 4096, 0x0
