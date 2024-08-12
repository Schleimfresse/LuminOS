//
// Created by linus on 10.08.24.
//
/*
* Legacy
*/
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "vga.h"

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str)
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLUE);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c)
{
	if (c == '\n') {
	terminal_column=0;
	terminal_row++;
	return;
	}
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}

void terminal_write(const char* data, size_t size)
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

// Function to convert a number to hexadecimal string
void terminal_print_hex(uint32_t num)
{
    const char hex_chars[] = "0123456789ABCDEF";
    char buf[9]; // 8 hex digits + null terminator
    buf[8] = '\0'; // null terminator
    for (int i = 7; i >= 0; --i) {
        buf[i] = hex_chars[num & 0xF];
        num >>= 4;
    }
    terminal_print(buf); // Assuming terminal_print prints a null-terminated string
}

void terminal_print_dec(int32_t num) {
    char buf[12];
    char* p = buf + sizeof(buf) - 1; // Start at the end of the buffer
    bool negative = false;

    *p = '\0'; // Null-terminate the buffer

    if (num < 0) {
        negative = true;
        num = -num;
    }

    do {
        *(--p) = '0' + (num % 10); // Extract last digit and convert to char
        num /= 10;
    } while (num > 0);

    if (negative) {
        *(--p) = '-';
    }

    terminal_write(p, buf + sizeof(buf) - p);
}

void terminal_print(const char* data)
{
	terminal_write(data, strlen(data));
}

void terminal_println(const char* data)
{
	size_t length = strlen(data);
    char buffer[length + 1];

    for (size_t i = 0; i < length; ++i) {
        buffer[i] = data[i];
    }
    buffer[length] = '\n';
    terminal_write(buffer, length + 1);
}