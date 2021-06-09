/*
 *   This file is part of an AArch64 hobbyist OS for the Raspberry Pi 3 B+ called GENADEV_OS
 *   Everything is openly developed on github: https://github.com/GENADEV/GENADEV_OS
 *   Copyright (C) 2021  Yves Vollmeier, Tim Thompson and Michael Buch
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

.extern bss_begin
.extern bss_end

.section .text.boot

.global _start
_start:
    /* For now all but the primary core will be suspended */
    mrs x0, mpidr_el1   // Multiprocessor Affinity Register
    and x0, x0, #0xFF   // Lower 8 bits indicate the core no.
    cbz x0, drop_to_el2 // Is the Core ID == 0? (Main core)
    b hang              // Stop the core

drop_to_el2:
    // If we are already at EL2 (e.g., when running in QEMU),
    // skip this step
    mrs x0, CurrentEL
    cmp x0, #(2 << 2)
    b.eq drop_to_el1

    mov x0, #0x5b1        // RW=1, HCE=1, SMD=1, RES=1, NS=1
    msr scr_el3, x0

    mov x0, #0x3c9        // D=1, A=1, I=1, F=1 M=EL2h
    msr spsr_el3, x0

    adr x0, drop_to_el1
    msr elr_el3, x0
    eret

drop_to_el1:
    ldr x0, =[0x80000]
    msr sp_el1, x0

    mov x1, #(1 << 31)    // Set execution state to AArch64
    orr x1, x1, #(1 << 1) // SWIO
    msr hcr_el2, x1

    mov x1, #0x3c4        // D=1, A=1, I=1, F=1 M=EL1t
    msr spsr_el2, x1

    mov x1, #(3 << 20)    // Disable floating-point, SVE
    msr cpacr_el1, x1

    adr x1, el1_entry
    msr elr_el2, x1
    eret

el1_entry:
    bl bss_zero
    bl main
    b hang

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

hang:
    b hang
