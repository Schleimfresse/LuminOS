
#ifndef BASIC_RENDERER_H
#include "../../include/graphics.h"
#define BASIC_RENDERER_H
class BasicRenderer{
    public:
    BasicRenderer(Framebuffer* targetFramebuffer, PSF1_FONT* psf1_Font);
    Framebuffer* TargetFramebuffer;
    PSF1_FONT* PSF1_Font;
    unsigned int Colour;
    void Print(const char* str);
    void PutChar(char chr, unsigned int xOff, unsigned int yOff);
    void SetCursorX(int32_t x);
    void SetCursorY(int32_t y);
    void SetCursor(Point point);
    void IncrementCursorX(int32_t x);
    void IncrementCursorY(int32_t y);
    void NewLine();
    private:
    Point CursorPosition;
};

#endif //BASIC_RENDERER_H