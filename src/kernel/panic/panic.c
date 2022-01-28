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


#include "panic.h"
#include <stdarg.h>
#include "../../lib/stdio/fmt.h"
#include "../../lib/debug/debug.h"
#include <stdint.h>
#include "../arm-v-8/cpu.h"

struct stackframe
{
    struct stackframe* fp;
    uint32_t lr;
};

void walk_frames(unsigned int MaxFrames);

char panic_buff[512];
__no_return panic(const char *err, ...)
{
    va_list ap;
    va_start(ap, err);
    vsnprintf((char*)&panic_buff, -1, err, ap);

    debug(DBG_BOTH,
          "\n---= KERNEL PANIC =---\n"
          "Fault: %s\n\n",
          (char*)panic_buff
         );

    walk_frames(10);

    debug(DBG_BOTH, "Stack trace complete | Halting computer now\n");

    for (;;)
        relax_cpu();
}

int assertion_failure(const char *err, ...)
{
    va_list ap;
    va_start(ap, err);
    vsnprintf((char*)&panic_buff, -1, err, ap);

    debug(DBG_BOTH,
          "\n---= Assertion failure =---\n"
          "Fault: %s\n\n",
          (char*)panic_buff
         );

    walk_frames(10);

    debug(DBG_BOTH, "Stack trace complete | Halting computer now\n");

    for (;;)
        relax_cpu();
}

/* Walk a linked list of (lr, fp) which comprise the linked list of frame pointers. For more see this awesome stackoverflow answer which I came across: https://stackoverflow.com/questions/15752188/arm-link-register-and-frame-pointer#15752671 */
void walk_frames(unsigned int MaxFrames)
{
    struct stackframe *stk;
    asm ("mov %0, x29\n" : "=g"(stk));

    debug(DBG_BOTH, "Stack trace: \n");

    for (uint32_t frame = 0; stk && frame < MaxFrames; ++frame)
    {
        // Unwind to previous stack frame
        debug(DBG_BOTH, " (%d) _unknown_: 0x%x     \n", frame, stk->lr);
        stk = stk->fp;
    }
}
