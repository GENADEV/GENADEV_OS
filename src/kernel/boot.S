/*
 *   This file is part of an AArch64 hobbyist OS for the Raspberry Pi 3 B+ called GENADEV_OS 
 *   Everything is openly developed on github: https://github.com/GENADEV/GENADEV_OS
 *   Copyright (C) 2021  Yves Vollmeier and Tim Thompson
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

.section .text.boot

.extern bss_begin
.extern bss_end

.global _start
_start:
	//For now all but the primary core will be suspended
	mrs x0, mpidr_el1	     //Multiprocessor Affinity Register
	and x0, x0, #0xFF  		 //Lower 8 bits indicate the core no.	
	cbz x0, 2f				 //Is the Core ID == 0? (Main core)
	b 1f					 //Stop the core

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
