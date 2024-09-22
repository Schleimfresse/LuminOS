#include <stdint.h>
#include "../../include/graphics.h"

Point CursorPosition;

void putChar(const uint32_t color, const char chr, const uint32_t xOff, const uint32_t yOff) {
    uint32_t* pixPtr = (uint32_t*)fb->BaseAddress;
    char* fontPtr = psf1_font->glyphBuffer + (chr * psf1_font->psf1_header->charsize);
    for (unsigned long y = yOff; y < yOff + 16; y++){
        for (unsigned long x = xOff; x < xOff+8; x++){
            if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0){
                    *(uint32_t*)(pixPtr + x + (y * fb->PixelsPerScanLine)) = color;
                }

        }
        fontPtr++;
    }
}

void Print(char* str, uint32_t color) {
    char* chr = str;

    while (*chr != 0)
    {
        putChar(color, *chr, CursorPosition.X, CursorPosition.Y);
        CursorPosition.X+=8;
        if(CursorPosition.X + 8 > fb->Width)
        {
            CursorPosition.X = 0;
            CursorPosition.Y += 16;
        }
        chr++;
    }
    //swap_buffers();
}

void SetCursorX(int32_t x) {
    CursorPosition.X = x;
}

void SetCursorY(int32_t y) {
    CursorPosition.Y = y;
}

void SetCursor(int32_t x, int32_t y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
}

void IncrementCursorX(int32_t x) {
    CursorPosition.X += x;
}

void IncrementCursorY(int32_t y) {
    CursorPosition.Y += y;
}
