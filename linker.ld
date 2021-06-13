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
*/

ENTRY(_start)

SECTIONS
{
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

    . = ALIGN(0x1000);
    .page_tables : { *(.page_tables) }
}
