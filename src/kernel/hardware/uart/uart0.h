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

#ifndef UART0_H 
#define UART0_H 

#include "../gpio/mmio_base.h"
#include <stdint.h>
#include <stdbool.h>


// most important UART0 registers

// UART0 base address: 0x3F201000
#define UART0_DR	((uint32_t *) (MMIO_BASE+0x00201000))
#define UART0_FR	((uint32_t *) (MMIO_BASE+0x00201018))
#define UART0_IBRD	((uint32_t *) (MMIO_BASE+0x00201024))
#define UART0_FBRD	((uint32_t *) (MMIO_BASE+0x00201028))
#define UART0_LCRH	((uint32_t *) (MMIO_BASE+0x0020102C))
#define UART0_CR	((uint32_t *) (MMIO_BASE+0x00201030))
#define UART0_IMSC	((uint32_t *) (MMIO_BASE+0x00201038))
#define UART0_ICR	((uint32_t *) (MMIO_BASE+0x00201044))

void uart0_init(void);
char uart0_recv(void);
int uart0_send(char c);
void uart0_send_string(char* str);

#endif
