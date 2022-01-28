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
*/

#include "cpu.h"
#include "../../lib/debug/debug.h"
#include "../panic/panic.h"

#define EXPECTED_IMPLEMENTER "Arm Limited"

void cpu_info()
{
    debug(DBG_BOTH, "=== CPU INFO ===\n");

    long midr;
    asm volatile(
        //Read Main ID Register
        "mrs %0, midr_el1\n"
        : "=g"(midr)
    );

    //Bits 'x' through 'y' (x:y)
    //31:24
    int implementer = (midr >> 24) & 0x00ffffff;
    //23:20
    int variant = (midr >> 20) & 0x00f;
    //19:16
    int architecture = (midr >> 16) & 0xf;
    //15:4
    int part_num = ((midr >> 4) & 0xff00) >> 8; //((midr >> 4) & 0xff00) = 0xfd00 (this holds true for qemu's raspi3 emulator, V. 4.2.1), then we perform a right shift to discard of the lower bits (00)
    //3:0
    int revision = (midr) & 0x000000ff;

    //Log the information and perform some sanity checks
    debug(DBG_BOTH, "Contents of the midr register: 0x%x\n", midr);
    (implementer == 0x41) ? debug(DBG_BOTH, "Implementer: %s\n", EXPECTED_IMPLEMENTER) : panic("Expected implementer %s, got 0x%x", implementer);
    (architecture == 0xf) ? debug(DBG_BOTH, "Architecture: 0x%x\n", architecture) : panic("Expected architecture version 0xf, got 0x%x", architecture);
    debug(DBG_BOTH, "Variant: 0x%x\n", variant);
    debug(DBG_BOTH, "PartNum: 0x%x\n", part_num);
    debug(DBG_BOTH, "Revision: 0x%x\n", revision);
}