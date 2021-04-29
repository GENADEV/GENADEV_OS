ARCH	= aarch64-linux-gnu
CC		= $(ARCH)-gcc
AS		= $(ARCH)-as
LD		= $(ARCH)-ld
OBJCPY	= $(ARCH)-objcopy

QEMU_AARCH64 = qemu-system-aarch64

CC_OPT			= -nostdlib -ffreestanding -std=gnu99 -mgeneral-regs-only -c
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
	$(AS) $< -o $@

%.o: %.c
	$(CC) $(CC_OPT) $< -o $@
