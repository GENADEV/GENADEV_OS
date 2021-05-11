/*
 *   This file is part of an AArch64 hobbyist OS for the Raspberry Pi 3 B+ called GENADEV_OS 
 *   Everything is openly developed on github: https://github.com/GENADEV/GENADEV_OS
 *   Copyright (C) 2021  Yves Vollmeier and Tim Thompson
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#ifndef IRQ_H
#define IRQ_H

#include "../hardware/gpio/mmio_base.h"
#include "../utils.h"

extern void irq_init();

/*
   https://github.com/raspberrypi/documentation/files/1888662/BCM2837-ARM-Peripherals.-.Revised.-.V2-1.pdf
   According to the latter document, the GPU interrupts are numbered 0-63, and the arm interrupts are numbered 64-71
*/

#define IRQ_ARM_1 64 /* ARM Timer interrupt */
#define IRQ_ARM_2 65 /* ARM Mailbox interrupt */
#define IRQ_ARM_3 66 /* ARM Doorbell 0 interrupt */
#define IRQ_ARM_4 67 /* ARM Doorbell 1 interrupt */
#define IRQ_ARM_5 68 /* GPU0 Halted interrupt (Or GPU1) */
#define IRQ_ARM_6 69 /* GPU1 Halted interrupt */
#define IRQ_ARM_7 70 /* Illegal access type-1 interrupt */ 
#define IRQ_ARM_8 71 /* Illegal access type-0 interrupt */

/* Referred to from the latter document */
#define IRQ_BASIC_PENDING   (MMIO_BASE + 0x200)
#define IRQ_PENDING_1       (MMIO_BASE + 0x204)
#define IRQ_PENDING_2       (MMIO_BASE + 0x208)
#define FIQ_CONTROL         (MMIO_BASE + 0x20C)
#define ENABLE_IRQS_1       (MMIO_BASE + 0x210)
#define ENABLE_IRQS_2       (MMIO_BASE + 0x214)
#define ENABLE_BASIC_IRQS   (MMIO_BASE + 0x218)
#define DISABLE_IRQS_1      (MMIO_BASE + 0x21C)
#define DISABLE_IRQS_2      (MMIO_BASE + 0x220)
#define DISABLE_BASIC_IRQS  (MMIO_BASE + 0x224)


#endif // IRQ_H
