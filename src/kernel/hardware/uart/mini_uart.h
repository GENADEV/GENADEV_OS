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


#ifndef MINI_UART_H
#define MINI_UART_H

#include "../gpio/mmio_base.h"
#include <stdint.h>
#include <stdbool.h>

#define AUX_ENABLES     ((uint32_t *) (MMIO_BASE+0x00215004))
#define AUX_MU_IO_REG   ((uint32_t *) (MMIO_BASE+0x00215040))
#define AUX_MU_IER_REG  ((uint32_t *) (MMIO_BASE+0x00215044))
#define AUX_MU_IIR_REG  ((uint32_t *) (MMIO_BASE+0x00215048))
#define AUX_MU_LCR_REG  ((uint32_t *) (MMIO_BASE+0x0021504C))
#define AUX_MU_MCR_REG  ((uint32_t *) (MMIO_BASE+0x00215050))
#define AUX_MU_LSR_REG  ((uint32_t *) (MMIO_BASE+0x00215054))
#define AUX_MU_MSR_REG  ((uint32_t *) (MMIO_BASE+0x00215058))
#define AUX_MU_SCRATCH  ((uint32_t *) (MMIO_BASE+0x0021505C))
#define AUX_MU_CNTL_REG ((uint32_t *) (MMIO_BASE+0x00215060))
#define AUX_MU_STAT_REG ((uint32_t *) (MMIO_BASE+0x00215064))
#define AUX_MU_BAUD_REG	((uint32_t *) (MMIO_BASE+0x00215068))

void mini_uart_init (void);
char mini_uart_recv (void);
int mini_uart_send (char c);
void mini_uart_send_string(char* str);

#endif
