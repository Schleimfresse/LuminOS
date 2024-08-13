//
// Created by linus on 11.08.2024.
//

#include "../../include/multiboot.h"
#include "../terminal/vga.h"
#include <stdint.h>

multiboot_uint64_t framebuffer_base;
multiboot_uint32_t framebuffer_width;
multiboot_uint32_t framebuffer_height;
multiboot_uint32_t framebuffer_pitch;
multiboot_uint8_t framebuffer_bpp;

extern multiboot_info_t *multiboot_info;

void initialize_framebuffer() {
    if (multiboot_info->flags & MULTIBOOT_INFO_FRAMEBUFFER_INFO) {
        framebuffer_base = multiboot_info->framebuffer_addr;
        framebuffer_width = multiboot_info->framebuffer_width;
        framebuffer_height = multiboot_info->framebuffer_height;
        framebuffer_pitch = multiboot_info->framebuffer_pitch;
        framebuffer_bpp = multiboot_info->framebuffer_bpp;

        // For debugging: print the framebuffer information
        terminal_println("Framebuffer Info:");
        terminal_print("Address: 0x");
        terminal_print_hex((unsigned int)framebuffer_base);
        terminal_print("\nWidth: ");
        terminal_print_dec(framebuffer_width);
        terminal_print("\nHeight: ");
        terminal_print_dec(framebuffer_height);
        terminal_print("\nPitch: ");
        terminal_print_dec(framebuffer_pitch);
        terminal_print("\nBpp: ");
        terminal_print_dec(framebuffer_bpp);
		int *ptr = (int *)MULTIBOOT_INFO_BOOTDEV;
		int value = *ptr;
		terminal_print_dec(value);
        // Optional: Clear the framebuffer or draw something
        // clear_screen();
    } else {
        terminal_print("No framebuffer information available.\n");
        while (1) {} // Halt if no framebuffer info is available
    }
}


void set_pixel(int x, int y, uint16_t color) {
	if (x >= 0 && x < framebuffer_width && y >= 0 && y < framebuffer_height) {
		uint8_t *pixel = (uint8_t *)(uintptr_t)(multiboot_info->framebuffer_addr);

		int pixel_offset = y * framebuffer_pitch + x * (framebuffer_bpp / 8);
		// Write color to pixel location
		*((uint16_t *)pixel) = color; // 16-bit color
	} else {
        terminal_println("Out of bounds");
}
}