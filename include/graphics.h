//
// Created by linus on 24.08.24.
//

#ifndef GRAHICS_H
#define GRAHICS_H
#include <stddef.h>
#include <stdint.h>

#define BLACK   0x00000000
#define WHITE   0x00FFFFFF
#define RED     0x00FF0000
#define GREEN   0x0000FF00
#define BLUE    0x000000FF
#define YELLOW  0x00FFFF00
#define CYAN    0x0000FFFF
#define MAGENTA 0x00FF00FF
#define ORANGE  0x0000A5FF // CYAN
#define GRAY    0x00808080

typedef struct {
	void* BaseAddress;
	size_t BufferSize;
	uint32_t Width;
	uint32_t Height;
	uint32_t PixelsPerScanLine;
} Framebuffer;

typedef struct {
    uint32_t X;
    uint32_t Y;
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
