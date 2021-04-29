.section .text.boot

.extern bss_begin
.extern bss_end

.global _start
_start:
	//For now all but the primary core will be suspended
	mrs x0, mpidr_el1	     //Multiprocessor Affinity Register
	and x0, x0, #0xFF  		 //Lower 8 bits indicate the core no.	
	cbz x0, 2f				 //Is the Core ID == 0? (Main core)
	bne 1f					 //Stop the core

	//Every core that comes here != Core no. 0x0
	1:
		b 1b

	//Main core is the only thing executing useful code from here on
	2:	
		//Setup stack
		ldr x1, =[0x80000]
		mov sp, x1

		bl bss_zero //Zero out bss
		bl main		//Kernel entry point
	
	3:
		b 3b

bss_zero:    
    //Get size of bss section
    ldr x0, =bss_begin
    ldr x1, =bss_end
    sub x3, x0, x1

    1:
        sub x3, x1, x0      //Decrement the counter which specifies when the bss section is all zero
        str xzr, [x0], #8   //clear out a section of bss data in byte sized chunks
        cbnz x3, 1b         //goto 1 if x3 != 0x0
	ret
