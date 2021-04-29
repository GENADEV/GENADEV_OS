#include "debug.h"
#include <stdarg.h>
#include "../stdio/fmt.h"
#include "../stdio/stdio.h"
#include "../../kernel/hardware/uart/mini_uart.h"

extern mini_uart_status_t status;

//buffer for the formatted string
const char debug_buff[512];
int debug(char *fmt, ...)
{
    if (!status.init_true)
        return 1;
        
    va_list ap;
    va_start(ap, fmt);
    vsnprintf((char*)&debug_buff, -1, fmt, ap);

    ua_puts((char*)debug_buff);

    va_end(ap);
    return 0;
}