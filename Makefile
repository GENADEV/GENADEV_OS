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

# There are some issues here and there when trying to install an aarch64 cross compiler on different distros so we decided to do it manually
GNU_ARM_CC = gnu-arm/gcc-arm-10.2-2020.11-x86_64-aarch64-none-elf
GNU_ARM_CC_TARBALL = gnu-arm/gcc-arm.tar.xz

ARCH	= @$(GNU_ARM_CC)/bin/aarch64-none-elf
CC		= $(ARCH)-gcc
AS		= $(ARCH)-as
LD		= $(ARCH)-ld
OBJCPY	= $(ARCH)-objcopy

QEMU_AARCH64 = qemu-system-aarch64

CC_OPT			= -fno-omit-frame-pointer -mcpu=cortex-a53 -nostdlib -ffreestanding -std=gnu99 -mgeneral-regs-only -O2 -c
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

setup: $(GNU_ARM_CC_TARBALL)
	@printf "TAR\t$^\n";
	@tar -xf $^ -C gnu-arm/
	@printf "OK\tExtracted tarball archive\n";
	@printf "Please install the libncurses5 package using your package manager (package name may vary based on your distro, this package name is derived from an apt package manager)\n";

run0: $(TARGET_FINAL)
	@printf "Keep in mind: Qemu is using the uart device\n";
	$(QEMU_AARCH64) -M raspi3 -kernel $(TARGET_FINAL) -serial stdio -d int

run1: $(TARGET_FINAL)
	@printf "Keep in mind: Qemu is using the mini-uart device\n";
	$(QEMU_AARCH64) -M raspi3 -kernel $(TARGET_FINAL) -serial null -serial stdio -d int

$(TARGET_FINAL): $(OBJ)
	$(LD) -T linker.ld $^ -o $(BUILD)/$(TARGET_ELF)
	$(OBJCPY) $(BUILD)/$(TARGET_ELF) -O binary $@

clean:
	rm -f $(OBJ) $(TARGET_ELF) $(TARGET_FINAL)

format:
	astyle --mode=c -nA1TfpxgHxbxjxp $(C_FILES)

%.o: %.S
	@printf " AS\t$<\n";
	$(AS) -c $< -o $@

%.o: %.c
	@printf " CC\t$<\n";
	$(CC)  $(CC_OPT) -c $< -o $@
