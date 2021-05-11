#*   This file is part of an AArch64 hobbyist OS for the Raspberry Pi 3 B+ called GENADEV_OS \
 *   Everything is openly developed on github: https://github.com/GENADEV/GENADEV_OS \
 *   Copyright (C) 2021  Yves Vollmeier and Tim Thompson \
 *   \
 *   This program is free software: you can redistribute it and/or modify \
 *   it under the terms of the GNU General Public License as published by \
 *   the Free Software Foundation, either version 3 of the License, or \
 *   (at your option) any later version. \
 *   \
 *   This program is distributed in the hope that it will be useful, \
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of \
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the \
 *   GNU General Public License for more details. \
 *   \
 *   You should have received a copy of the GNU General Public License \
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>. \
 *   \
 */  \


ARCH	= @aarch64-linux-gnu
CC		= $(ARCH)-gcc
AS		= $(ARCH)-as
LD		= $(ARCH)-ld
OBJCPY	= $(ARCH)-objcopy

QEMU_AARCH64 = qemu-system-aarch64

CC_OPT			= -mcpu=cortex-a53 -nostdlib -ffreestanding -std=gnu99 -mgeneral-regs-only -c
TARGET_ELF		= kernel8.elf
TARGET_FINAL	= kernel8.img

C_FILES		= $(shell find src/ -type f -name '*.c')
AS_FILES	= $(shell find src/ -type f -name '*.S')

C_OBJ	= $(C_FILES:.c=.o)
AS_OBJ	= $(AS_FILES:.S=.o)
OBJ		= $(AS_OBJ) $(C_OBJ)

BUILD = build

all: $(TARGET_FINAL)
	@printf "DONE\n";

run: $(TARGET_FINAL)
	$(QEMU_AARCH64) -M raspi3 -kernel $(TARGET_FINAL) -serial null -serial stdio -d int

$(TARGET_FINAL): $(OBJ)
	$(LD) -T linker.ld $^ -o $(BUILD)/$(TARGET_ELF)
	$(OBJCPY) $(BUILD)/$(TARGET_ELF) -O binary $@

clean:
	rm -f $(OBJ) $(TARGET_ELF) $(TARGET_FINAL)

%.o: %.S
	@printf " AS\t$<\n";
	$(AS) -c $< -o $@

%.o: %.c
	@printf " CC\t$<\n";
	$(CC)  $(CC_OPT) -c $< -o $@
