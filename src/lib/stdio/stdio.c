#include "stdio.h"

void ua_putc(char c)
{
    mini_uart_send(c);
}

void ua_puts(char *s)
{
    mini_uart_send_string(s);
}