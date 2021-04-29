#ifndef GPIO_H
#define GPIO_H

#include "mmio_base.h"

// GPIO Function Select 0
#define GPFSEL0         (MMIO_BASE+0x00200000)
// GPIO Function Select 1
#define GPFSEL1         (MMIO_BASE+0x00200004)
// GPIO Function Select 2
#define GPFSEL2         (MMIO_BASE+0x00200008)
// GPIO Function Select 3
#define GPFSEL3         (MMIO_BASE+0x0020000C)
// GPIO Function Select 4
#define GPFSEL4         (MMIO_BASE+0x00200010)
// GPIO Function Select 5
#define GPFSEL5         (MMIO_BASE+0x00200014)
// GPIO Pin Output Set 0
#define GPSET0          (MMIO_BASE+0x0020001C)
// GPIO Pin Output Set 1
#define GPSET1          (MMIO_BASE+0x00200020)
// GPIO Pin Output Clear 0
#define GPCLR0          (MMIO_BASE+0x00200028)
// GPIO Pin Level 0
#define GPLEV0          (MMIO_BASE+0x00200034)
// GPIO Pin Level 1
#define GPLEV1          (MMIO_BASE+0x00200038)
// GPIO Pin Event Detect Status 0
#define GPEDS0          (MMIO_BASE+0x00200040)
// GPIO Pin Event Detect Status 1 
#define GPEDS1          (MMIO_BASE+0x00200044)
// GPIO Pin High Detect Enable 0
#define GPHEN0          (MMIO_BASE+0x00200064)
// GPIO Pin High Detect Enable 1
#define GPHEN1          (MMIO_BASE+0x00200068)
// GPIO Pin Pull-up/down Enable
#define GPPUD           (MMIO_BASE+0x00200094)
// GPIO Pin Pull-up/down Enable Clock 0
#define GPPUDCLK0       (MMIO_BASE+0x00200098)
// GPIO Pin Pull-up/down Enable Clock 1
#define GPPUDCLK1       (MMIO_BASE+0x0020009C)

#endif
