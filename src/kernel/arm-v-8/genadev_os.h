#ifndef GENADEV_OS_H
#define GENADEV_OS_H

/* Macros to replace the old type names, make the code look cleaner or optimize functions which use these defines */
#define __export extern 
#define __no_optimize volatile
#define __no_return __attribute__((noreturn)) void
#define __section_align  __attribute__((aligned (16)))
#define __section_align8 __attribute__((aligned (8)))

#endif // GENADEV_OS_H
