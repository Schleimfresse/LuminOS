//
// Created by linus on 10.08.24.
//

#ifndef VGA_DRIVER_H
#define VGA_DRIVER_H
#include <stddef.h>
#include <stdint.h>

// Hardware text mode color constants.
enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

// Function to write a null-terminated string to the terminal
void terminal_print(const char* data);

void terminal_println(const char* data);

// Function to initialize the vga-driver
void terminal_initialize(void);

// Function to convert a number to hexadecimal string
void terminal_print_hex(uint32_t hex);

void terminal_print_dec(int32_t dec);

#endif /* VGA_DRIVER_H */