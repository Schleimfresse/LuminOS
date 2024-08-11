# Define variables
AS = i686-elf-as
CC = i686-elf-gcc
LD = i686-elf-gcc
GRUB_FILE = grub-file
GRUB_MKRESCUE = grub-mkrescue
ISO_NAME = luminOS.iso
ISO_DIR = isodir
BOOT_DIR = bootloader/build
SRC_DIR = bootloader/src
KERNEL_SRC = kernel/kernel.c
KERNEL_O = kernel/kernel.o
LINKER_SCRIPT = linker.ld
GRUB_CFG = grub.cfg
DRIVER_DIR = kernel/drivers
all: check_multiboot create_iso

# Assemble the bootloader
$(BOOT_DIR)/boot.o: $(SRC_DIR)/boot.s
	mkdir "bootloader/build"
	$(AS) -o $@ $<

# Compile the kernel
kernel.o: $(KERNEL_SRC)
	$(CC) -c $(KERNEL_SRC) -o $(KERNEL_O) -std=gnu99 -ffreestanding -O2 -Wall -Wextra

drivers:
	$(MAKE) -C $(DRIVER_DIR)

# Link the kernel and bootloader into a binary
kernel.bin: $(BOOT_DIR)/boot.o kernel.o drivers
	$(LD) -T $(LINKER_SCRIPT) -o $@ -ffreestanding -O2 -nostdlib $(BOOT_DIR)/boot.o $(KERNEL_O) $(shell find $(DRIVER_DIR) -name '*.o')

# Check if the kernel binary is multiboot
check_multiboot: kernel.bin
	@if $(GRUB_FILE) --is-x86-multiboot $<; then \
	  echo "multiboot confirmed"; \
	else \
	  echo "the file is not multiboot"; \
	fi

# Prepare the ISO directory and create the ISO
create_iso: kernel.bin
	mkdir -p $(ISO_DIR)/boot/grub
	cp kernel.bin $(ISO_DIR)/boot/kernel.bin
	cp $(GRUB_CFG) $(ISO_DIR)/boot/grub/grub.cfg
	$(GRUB_MKRESCUE) -o $(ISO_NAME) $(ISO_DIR)

# Clean up build artifacts
clean:
	rm -f $(BOOT_DIR)/boot.o kernel.o kernel.bin $(KERNEL_O)
	rmdir $(BOOT_DIR)
	rm -rf $(ISO_DIR)
	$(MAKE) -C $(DRIVER_DIR) clean

# Clean up build artifacts
remove:
	rm -f $(ISO_NAME)
