//
// Created by linus on 11.08.2024.
//

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <stdint.h>
#define RGB565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3))

// Declare the framebuffer initialization function
void initialize_framebuffer(void);

// sets a single pixel at the specified coordinates, third argument has to be a RGB565 color
void set_pixel(int x, int y, uint16_t color);

#endif // FRAMEBUFFER_H