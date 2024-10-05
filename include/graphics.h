//
// Created by linus on 24.08.24.
//

#ifndef GRAHICS_H
#define GRAHICS_H
#include <stddef.h>
#include <stdint.h>

typedef enum {
    BLACK   = 0x00000000,
    WHITE   = 0x00FFFFFF,
    RED     = 0x00FF0000,
    GREEN   = 0x0000FF00,
    BLUE    = 0x000000FF,
    YELLOW  = 0x00FFFF00,
    CYAN    = 0x0000FFFF,
    MAGENTA = 0x00FF00FF,
    ORANGE  = 0x0000A5FF,
    GRAY    = 0x00808080
} Colour;

typedef struct {
	void* base_address;
	size_t buffer_size;
	uint32_t width;
	uint32_t height;
	uint32_t pixels_per_scanline;
} Framebuffer;

typedef struct {
    long X;
    long Y;
} Point;

#define PSF1_MAGIC0 0x36
#define PSF1_MAGIC1 0x04

typedef struct {
	unsigned char magic[2];
	unsigned char mode;
	unsigned char charsize;
} PSF1_HEADER;

typedef struct {
	PSF1_HEADER* psf1_header;
	void* glyphBuffer;
} PSF1_FONT;

void swap_buffers();

extern Framebuffer* fb;
extern PSF1_FONT* psf1_font;


#endif //GRAHICS_H
