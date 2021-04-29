/* Two nice macros to allocate and free n bytes from the stack. It is up to the caller to ensure that the allocation is safe to perform */

.macro stack_alloc n
	sub sp, sp, \n
.endm


.macro stack_free n
	add sp, sp, \n
.endm
