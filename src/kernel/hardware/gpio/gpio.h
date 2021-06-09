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


#ifndef GPIO_H
#define GPIO_H

#include "mmio_base.h"
#include <stdint.h>

// GPIO Function Select 0
#define GPFSEL0        ((uint32_t*) (MMIO_BASE+0x00200000))
// GPIO Function Select 1
#define GPFSEL1        ((uint32_t*) (MMIO_BASE+0x00200004))
// GPIO Function Select 2
#define GPFSEL2        ((uint32_t*) (MMIO_BASE+0x00200008))
// GPIO Function Select 3
#define GPFSEL3        ((uint32_t*) (MMIO_BASE+0x0020000C))
// GPIO Function Select 4
#define GPFSEL4        ((uint32_t*) (MMIO_BASE+0x00200010))
// GPIO Function Select 5
#define GPFSEL5        ((uint32_t*) (MMIO_BASE+0x00200014))
// GPIO Pin Output Set 0
#define GPSET0         ((uint32_t*) (MMIO_BASE+0x0020001C))
// GPIO Pin Output Set 1
#define GPSET1         ((uint32_t*) (MMIO_BASE+0x00200020))
// GPIO Pin Output Clear 0
#define GPCLR0         ((uint32_t*) (MMIO_BASE+0x00200028))
// GPIO Pin Level 0
#define GPLEV0         ((uint32_t*) (MMIO_BASE+0x00200034))
// GPIO Pin Level 1
#define GPLEV1         ((uint32_t*) (MMIO_BASE+0x00200038))
// GPIO Pin Event Detect Status 0
#define GPEDS0         ((uint32_t*) (MMIO_BASE+0x00200040))
// GPIO Pin Event Detect Status 1 
#define GPEDS1         ((uint32_t*) (MMIO_BASE+0x00200044))
// GPIO Pin High Detect Enable 0
#define GPHEN0         ((uint32_t*) (MMIO_BASE+0x00200064))
// GPIO Pin High Detect Enable 1
#define GPHEN1         ((uint32_t*) (MMIO_BASE+0x00200068))
// GPIO Pin Pull-up/down Enable
#define GPPUD          ((uint32_t*) (MMIO_BASE+0x00200094))
// GPIO Pin Pull-up/down Enable Clock 0
#define GPPUDCLK0      ((uint32_t*) (MMIO_BASE+0x00200098))
// GPIO Pin Pull-up/down Enable Clock 1
#define GPPUDCLK1      ((uint32_t*) (MMIO_BASE+0x0020009C))

#endif
