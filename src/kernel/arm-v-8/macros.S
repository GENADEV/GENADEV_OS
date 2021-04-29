//optimized and easy to read infinite loop
.macro hang
	1:
		b 1b
.endm

//print a formatted string to the mini uart
.macro uart_asm_print string
    adr x0, \string
    b debug
.endm
