#include "debug.h"
#include <stdarg.h>
#include "../stdio/fmt.h"
#include "../stdio/stdio.h"

//buffer for the formatted string
const char debug_buff[512];
int debug(char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vsnprintf((char*)&debug_buff, -1, fmt, ap);

    ua_puts((char*)debug_buff);

    va_end(ap);
}