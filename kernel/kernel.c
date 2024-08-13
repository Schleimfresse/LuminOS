#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "drivers/graphics/framebuffer.h"
#include "drivers/terminal/vga.h"
#include "include/multiboot.h"
/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
/*#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif*/

multiboot_info_t *multiboot_info;

void kernel_main(multiboot_uint32_t magic, multiboot_info_t *info) {
	terminal_initialize();

	if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
		// The bootloader did not pass the correct magic number
		terminal_println("\nError: Invalid Multiboot magic number, bootloader corrupted.");
		while (1) {}
	}

	multiboot_info = info;

	initialize_framebuffer();

	// Example: Draw a red pixel
	set_pixel(20, 20, RGB565(255,0,0));

	// Main kernel loop
	while (1) {
		// Kernel functionality
	}
}
