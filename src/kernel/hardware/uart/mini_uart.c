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

// mini uart is the same as uart1

#include "../gpio/gpio.h"
#include "mini_uart.h"
#include "uart0.h"
#include "../../utils.h"
#include "../../../lib/debug/debug.h"

static bool init_called = false;

void mini_uart_init(void)
{
    if (init_called)
        return;

    init_called = true;

    unsigned int selector;

    // GPIO Function select '1'
    selector = get32(GPFSEL1);
    // clean gpio14
    selector &= ~(7 << 12);
    // set alt5 for gpio14
    selector |= 2 << 12;
    // clean gpio15
    selector &= ~(7 << 15);
    // set alt5 for gpio15
    selector |= 2 << 15;
    // load selector into GPIO Function Select 1
    put32(GPFSEL1, selector);

    // enable gpio14 and gpio15
    put32(GPPUD, 0);
    // delay execution
    delay(150);
    // enable clock0 on both pin 14 and 15
    put32(GPPUDCLK0, (1 << 14) | (1 << 15));
    // delay execution
    delay(150);
    // flush GPIO setup
    put32(GPPUDCLK0, 0);

    // enable mini uart itself -> access to it's registers
    put32(AUX_ENABLES, 1);
    // disable auto flow control and disable receiver and transmitter
    put32(AUX_MU_CNTL_REG, 0);
    // disable receive and transmit interrupts
    put32(AUX_MU_IER_REG, 0);
    // enable 8 bit mode
    put32(AUX_MU_LCR_REG, 3);
    // set rts line to be always high
    put32(AUX_MU_MCR_REG, 0);
    // set baud rate to 115200
    put32(AUX_MU_BAUD_REG, 270);

    // enable transmitter and receiver
    put32(AUX_MU_CNTL_REG, 3);
}

char mini_uart_recv(void)
{
    while (!(get32(AUX_MU_LSR_REG) & 0x01));

    return get32(AUX_MU_IO_REG) & 0xFF;
}

int mini_uart_send(char c)
{
    while (!(get32(AUX_MU_LSR_REG) & 0x20));

    put32(AUX_MU_IO_REG, c);
    return 0;
}

void mini_uart_send_string(char* str)
{
    for (int i = 0; str[i] != '\0'; i++)
        mini_uart_send(str[i]);
}
