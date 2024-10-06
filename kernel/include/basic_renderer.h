
#ifndef BASIC_RENDERER_H
#include "../../include/graphics.h"
#define BASIC_RENDERER_H
class BasicRenderer{
    public:
    BasicRenderer(Framebuffer* targetFramebuffer, PSF1_FONT* psf1_Font);
    Framebuffer* TargetFramebuffer;
    PSF1_FONT* PSF1_Font;
    void print(const char* str);
    void put_char(char chr, uint32_t xOff, uint32_t yOff);
    void put_char(char chr);
    void put_pixel(uint32_t x, uint32_t y, Colour colour);
    Colour get_pixel(uint32_t x, uint32_t y);
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
    void draw_overlay_mouse_cursor(uint8_t* mouse_cursor, Point position, Colour colour);
    void clear_mouse_cursor(uint8_t* mouse_cursor, Point position);
    Colour mouse_cursor_buffer[16 * 16];
    Colour mouse_cursor_buffer_after[16 * 16];
    private:
    Point cursor_position;
    uint32_t colour;
    uint32_t clear_colour;
    bool mouse_drawn;
};

extern BasicRenderer* global_renderer;

#endif //BASIC_RENDERER_H