
#ifndef BASIC_RENDERER_H
#include "../../include/graphics.h"
#define BASIC_RENDERER_H
class BasicRenderer{
    public:
    BasicRenderer(Framebuffer* targetFramebuffer, PSF1_FONT* psf1_Font);
    Framebuffer* TargetFramebuffer;
    PSF1_FONT* PSF1_Font;
    void print(const char* str);
    void put_char(char chr, unsigned int xOff, unsigned int yOff);
    void put_char(char chr);
    void set_cursorX(int32_t x);
    void set_cursorY(int32_t y);
    void set_cursor(Point point);
    void set_colour(Colour colour);
    void set_clear_color(Colour colour);
    void increment_cursorX(int32_t x);
    void increment_cursorY(int32_t y);
    void new_line();
    void clear();
    void clear_char();
    private:
    Point cursor_position;
    unsigned int colour;
    unsigned int clear_colour;
};

extern BasicRenderer* global_renderer;

#endif //BASIC_RENDERER_H