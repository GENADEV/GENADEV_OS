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

.section .text.interrupts

.include "src/kernel/arm-v-8/asm/macros.S"
.include "src/kernel/arm-v-8/asm/stack.S"

//undefined irq handler (C)
.extern undefined_irq

//16 exception handlers total, as shown in the save_reg macro we do 16 * offset, the highest offset we can have is 16 so the max size of space we must reserve for the stack is 16*16=256
.set INT_STACK, 256

//Set an interrupt handler in the IVT 
.macro ivt_set_entry handler
    .align 7
    b \handler
.endm

//push does not exists on aarch64 so this is a neat macro to push a register to the stack
.macro save_reg reg1 reg2 offset
    stp \reg1, \reg2, [sp, #16 * \offset] //There is space for 16 exception handlers (4 exception level * 4 exception states)
.endm

//This macro is the counterpart of save_reg, it can be seen as an exclusive `pop` for interrupts (don't call this anywhere but this file)
.macro restore_reg reg1 reg2 offset
    ldp \reg1, \reg2, [sp, #16 * \offset]
.endm

//Save registers + pc to return to (that is, if we return from the interrupt)
.macro on_interrupt_enter
    /* Allocate some space on the stack for the interrupt frame */
    stack_alloc INT_STACK
    
    /* x0-29 are GP registers who's state must be restored if we return from an interrupt */
    save_reg x0, x1,   0
    save_reg x2, x3,   1
    save_reg x4, x5,   2
    save_reg x6, x7,   3
    save_reg x8, x9,   4
    save_reg x10, x11, 5
    save_reg x12, x13, 6
    save_reg x14, x15, 7
    save_reg x16, x17, 8
    save_reg x18, x19, 9
    save_reg x20, x21, 10
    save_reg x22, x23, 11
    save_reg x24, x25, 12
    save_reg x26, x27, 13
    save_reg x28, x29, 14

    /* Preserve the PC */
    str x30, [sp, #16 * 15]
.endm

.macro on_interrupt_exit
    /* Restore GP registers to their values before the interrupt occured */
    restore_reg x0, x1,   0
    restore_reg x2, x3,   1
    restore_reg x4, x5,   2
    restore_reg x6, x7,   3
    restore_reg x8, x9,   4
    restore_reg x10, x11, 5
    restore_reg x12, x13, 6
    restore_reg x14, x15, 7
    restore_reg x16, x17, 8
    restore_reg x18, x19, 9
    restore_reg x20, x21, 10
    restore_reg x22, x23, 11
    restore_reg x24, x25, 12
    restore_reg x26, x27, 13
    restore_reg x28, x29, 14

    /* Restore PC */
    ldr x30, [sp, #16 * 15]

    /* Free the allocated stack space */
    stack_free INT_STACK
    eret
.endm

ivt_desc:
    /* Exception taken from current EL with SP_EL0 */
    ivt_set_entry undefined_exception_stub // Synchronous
    ivt_set_entry undefined_exception_stub // IRQ/vIRQ
    ivt_set_entry undefined_exception_stub // FIQ/vFIQ
    ivt_set_entry undefined_exception_stub // SError/vSError

    /* Exception taken from current EL with SP_ELx, x > 1 */
    ivt_set_entry undefined_exception_stub // Synchronous
    ivt_set_entry undefined_exception_stub // IRQ/vIRQ
    ivt_set_entry undefined_exception_stub // FIQ/vFIQ
    ivt_set_entry undefined_exception_stub // SError/vSError

    /* Exception taken from lower EL and EL immediately lower
       than target is using AArch64 */
    ivt_set_entry undefined_exception_stub // Synchronous
    ivt_set_entry undefined_exception_stub // IRQ/vIRQ
    ivt_set_entry undefined_exception_stub // FIQ/vFIQ
    ivt_set_entry undefined_exception_stub // SError/vSError

     /* Exception taken from lower EL and EL immediately lower
        than target is using AArch32 */
    ivt_set_entry undefined_exception_stub // Synchronous
    ivt_set_entry undefined_exception_stub // IRQ/vIRQ
    ivt_set_entry undefined_exception_stub // FIQ/vFIQ
    ivt_set_entry undefined_exception_stub // SError/vSError

undefined_exception_stub:
    on_interrupt_enter
    mrs x0, CurrentEL
    read_el_reg x1 esr
    read_el_reg x2 elr
    b handle_undefined_exception
    on_interrupt_exit

.global irq_init
irq_init:
    adr x0, ivt_desc //temp store
    msr vbar_el1, x0
    uart_asm_print loaded_irq_msg
    ret

.global irq_enable
irq_enable:
    msr DAIFClr, #2
    ret

.global irq_disable
irq_disable:
    msr DAIFSet, #2
    ret

.section .data
    .extern irq_unknown
    loaded_irq_msg:  .asciz "Installed IRQ's\n"
