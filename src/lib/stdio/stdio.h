#ifndef LIB_STDIO_H
#define LIB_STDIO_H

#include "../../kernel/hardware/uart/mini_uart.h"

/* uart putc */
void ua_putc(char c);

/* uart puts */
void ua_puts(char *s);


#endif // LIB_STDIO_H