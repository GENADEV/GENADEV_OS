.section .text.interrupts

.include "src/kernel/arm-v-8/stack.S"
.include "src/kernel/arm-v-8/macros.S"

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
    ivt_set_entry undefined_irq_stub
    ivt_set_entry undefined_irq_stub
    ivt_set_entry undefined_irq_stub
    ivt_set_entry undefined_irq_stub
    
    ivt_set_entry undefined_irq_stub
    ivt_set_entry undefined_irq_stub
    ivt_set_entry undefined_irq_stub
    ivt_set_entry undefined_irq_stub
    
    ivt_set_entry undefined_irq_stub
    ivt_set_entry undefined_irq_stub
    ivt_set_entry undefined_irq_stub
    ivt_set_entry undefined_irq_stub
    
    ivt_set_entry undefined_irq_stub
    ivt_set_entry undefined_irq_stub
    ivt_set_entry undefined_irq_stub
    ivt_set_entry undefined_irq_stub

undefined_irq_stub:
    on_interrupt_enter
    b irq_unknown
    on_interrupt_exit

.global irq_init
irq_init:
    adr x0, ivt_desc //temp store
    msr vbar_el2, x0 //load the ivt descriptor into the Vector-Base-Address-Register (Exception level 2)
    uart_asm_print loaded_irq_msg
    ret

.global svc_test
svc_test:
    svc 0
    ret

.section .data
    .extern irq_unknown
    loaded_irq_msg:  .asciz "Installed IRQ's\n"
