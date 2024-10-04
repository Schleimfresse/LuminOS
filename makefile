KERNEL_DIR = ./kernel
LIB_DIR = ./lib
BUILD_DIR = ./build
KERNEL_SRC = $(shell find $(KERNEL_DIR) $(LIB_DIR) -name '*.cpp*' ! -path './gnu-efi/*')
KERNEL_OBJ = $(KERNEL_SRC:.cpp=.o)
KERNEL_ELF = $(BUILD_DIR)/kernel.elf
BOOTLOADER_EFI = gnu-efi/bootloader/boot.efi
DISK_IMG = $(BUILD_DIR)/boot.img

LDS = linker.ld
CC = gcc	
LD = ld
CFLAGS = -ffreestanding -fshort-wchar -mno-red-zone -fno-exceptions -pedantic -g -O0
LDFLAGS = -T $(LDS) -Bsymbolic -nostdlib -g

ISO = $(BUILD_DIR)/LuminOS.iso
MKFS_FAT = mkfs.fat
EFI_DIR = mnt/EFI/BOOT
IMG_SIZE = 131072

# Make all target
all: bootloader $(ISO) test clean

# Compile the bootloader using the separate makefile in gnu-efi/bootloader
bootloader:
	$(MAKE) -C gnu-efi/bootloader

# Compile the kernel C file into an object file
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Link all object files into the final ELF binary
$(KERNEL_ELF): $(KERNEL_OBJ)
	$(LD) $(LDFLAGS) -o $@ $(KERNEL_OBJ)

# Create the FAT32 EFI System Partition image
$(DISK_IMG): bootloader $(KERNEL_ELF)
	$(RM) $@
	dd if=/dev/zero of=$@ bs=512 count=$(IMG_SIZE)
	$(MKFS_FAT) -F 32 -n "UEFI BOOT" $@
	mkdir -p $(EFI_DIR)
	sudo mount -o loop $@ mnt
	sudo mkdir -p $(EFI_DIR)
	sudo cp $(BOOTLOADER_EFI) $(EFI_DIR)/BOOTX64.EFI
	sudo cp $(KERNEL_ELF) $(EFI_DIR)/kernel.elf
	sudo cp build/zap-light16.psf mnt/zap-light16.psf
	sudo cp $(BUILD_DIR)/startup.nsh mnt/
	sudo umount mnt
	$(RM) -r mnt

# Create the ISO image with the FAT32 EFI partition
$(ISO): $(DISK_IMG)
	dd if=$(DISK_IMG) of=$(ISO) bs=4M

# Test the ISO image with QEMU
test: $(ISO)
	qemu-system-x86_64 -cdrom $(ISO) -m 256M -cpu qemu64 -drive if=pflash,format=raw,unit=0,file="OVMF/OVMF_CODE-pure-efi.fd",readonly=on -drive if=pflash,format=raw,unit=1,file="OVMF/OVMF_VARS-pure-efi.fd" -net none 	# qemu-system-x86_64 -drive if=pflash,format=raw,file="OVMF/OVMF.fd" -cdrom $(ISO)
# Clean up build artifacts
clean:
	$(MAKE) -C gnu-efi/bootloader clean
	rm -f $(KERNEL_OBJ) $(KERNEL_ELF) $(DISK_IMG) $(ISO)
	rm -f -r mnt