#ifndef MEMDEF_H
#define MEMDEF_H

#include <stddef.h>

//
// PA = Physical Address
// VA = Virtual address
//

/* Physical addresses */
//Kernel base address in physical memory
#define PA_KERNEL_BASE 0x80000

/* Virtual addresses */
#define VA_KERNEL_BASE  0xffff000000000000
#define VA_KERNEL_TOP   0xffffffffffffffff
#define VA_USR_BASE     0x0000000000000000
#define VA_USR_TOP      0x0000ffffffffffff

/* VA to PA */
static inline void *__to_pa(void *vaddr) { return (void*)((size_t)vaddr - VA_KERNEL_BASE); }

/* VA to PA */
static inline void *__to_va(void *paddr) { return (void*)((size_t)paddr + VA_KERNEL_BASE); }

#endif // MEMDEF_H