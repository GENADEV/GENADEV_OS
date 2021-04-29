.section .text.boot

.global _start

_start:
	//Count cores
	mov x1, core_count
	ldr x2, [x1]
	add x1, x1, #1	//core_count++
	str x2, [x1]

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
		mov x0, core_count
		ldr x1, [x0]	
		cmp x1, #4 	   //rpi3 should have 4 cores
		ble 3f		   // If less cores are detected, it's weird. Just quit, might be wrong hardware or something
		
		//Setup stack
		ldr x1, =[0x80000]
		mov sp, x1
		
		//Pass the core count to main
		mov x1, core_count
		ldr w0, [x1]
		
		bl main		   // Kernel entry point
	
	3:
		b 3b

.section .data
	core_count: .hword 0x0
