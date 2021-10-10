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
     
    Author: Yves Vollmeier <https://github.com/Tix3Dev>
    Contributer: Tim Thompson <https://github.com/V01D-NULL>
*/

ENTRY(_start)

SECTIONS
{
    /* -- Kernel sections -- */
    
    /* NOTE: Until we set the gpio/mmio_base.h defintion to VA_KERNEL_BASE + DEVICE_MEMORY_BASE
       we will get data abort exceptions.
       For this reason you should remember to update mmio_base.h once paging is working!
       If you don't, you'll get errors when trying to access MMIO devices (such as a debug call which uses the UART)
    */

    /* . = 0xffff000000080000;  */
    . = 0x80000;
    kernel_start = .;
	.text.boot	: { *(.text.boot) }
	.text.interrupts : { *(.text.interrupts) }
	.text		: { *(.text*) }
	.rodata		: { *(.rodata) }
	.data		: { *(.data) }
	.			= ALIGN(0x8);
	
	bss_begin	= .;
	.bss		: { *(.bss*) } 
	bss_end		= .;
    kernel_end = .;
    /* -- Kernel sections -- */

    . = ALIGN(0x1000);
    .page_tables : { *(.page_tables) }
}