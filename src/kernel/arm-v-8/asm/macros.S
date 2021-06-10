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
     
    Author: Tim Thompson <https://github.com/V01D-NULL>
	Contributor: Michael Buch <https://github.com/Michael137>
*/


//optimized and easy to read infinite loop
.macro hang
	1:
		b 1b
.endm

//print a formatted string to the mini uart
.macro uart_asm_print string
    ldr x0, =0x2
    adr x1, \string
    b debug
.endm

/* Switch to one of the specified labels based on
   the current exception level (which is read into
   the specified register 'xreg'). Note that,
   CurrentEL is not readable from EL0, so we don't
   check it. */
.macro switch_on_el xreg label1 label2 label3
    // EL is in bit-positions [3-2] of the CurrentEL register
    // so shift expected EL by '2' for comparisons

    mrs \xreg, CurrentEL

    // EL1: ...0100
    cmp    \xreg, #(1 << 2)
    b.eq   \label1

    // EL2: ...1000
    cmp    \xreg, #(2 << 2)
    b.eq   \label2

    // EL3: ...1100
    cmp    \xreg, #(3 << 2)
    b.eq   \label3
.endm

/* Read the specified system register 'sysreg' for
   current exception level into the specified register
   'xreg' */
.macro read_el_reg xreg sysreg
    switch_on_el \xreg, 101f, 102f, 103f
101:
    mrs \xreg, \sysreg\()_el1
    b 104f
102:
    mrs \xreg, \sysreg\()_el2
    b 104f
103:
    mrs \xreg, \sysreg\()_el3
    b 104f
104:
.endm
