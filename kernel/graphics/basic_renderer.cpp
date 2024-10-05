#include "../include/basic_renderer.h"

BasicRenderer* global_renderer;

BasicRenderer::BasicRenderer(Framebuffer* targetFramebuffer, PSF1_FONT* psf1_Font)
{
    TargetFramebuffer = targetFramebuffer;
    PSF1_Font = psf1_Font;
    colour = Colour::WHITE;
    cursor_position = {0, 0};
}

void BasicRenderer::print(const char* str)
{
    
    char* chr = (char*)str;
    while(*chr != 0){
        put_char(*chr, cursor_position.X, cursor_position.Y);
        cursor_position.X+=8;
        if(cursor_position.X + 8 > TargetFramebuffer->width)
        {
            new_line();
        }
        chr++;
    }
}

void BasicRenderer::clear() {
    uint64_t fb_base = (uint64_t)TargetFramebuffer->base_address;
    uint64_t bytes_per_scanline = TargetFramebuffer->pixels_per_scanline * 4;
    uint64_t fb_height = TargetFramebuffer->height;
    uint64_t fb_size = TargetFramebuffer->buffer_size;

    for (int y = 0; y < fb_height; y ++){
        uint64_t pix_ptr_base = fb_base + (bytes_per_scanline * y);
        for (uint32_t* pix_ptr = (uint32_t*)pix_ptr_base; pix_ptr < (uint32_t*)(pix_ptr_base + bytes_per_scanline); pix_ptr ++){
            *pix_ptr = clear_colour;
        }
    }
}

void BasicRenderer::clear_char() {
    if (cursor_position.X == 0) {
        cursor_position.X = TargetFramebuffer->width;
        cursor_position.Y -= 16;
        if (cursor_position.Y < 0) cursor_position.Y = 0;
    }

    uint32_t x_off = cursor_position.X;
    uint32_t y_off = cursor_position.Y;

    uint32_t* pixPtr = (uint32_t*)TargetFramebuffer->base_address;
    for (unsigned long y = y_off; y < y_off + 16; y++){
        for (unsigned long x = x_off - 8; x < x_off; x++){
            *(uint32_t*)(pixPtr + x + (y * TargetFramebuffer->pixels_per_scanline)) = clear_colour;
        }
    }

    cursor_position.X -= 8;

    if (cursor_position.X < 0) {
        cursor_position.X = TargetFramebuffer->width;
        cursor_position.Y -= 16;
        if (cursor_position.Y < 0) cursor_position.Y = 0;
    }
}

void BasicRenderer::put_char(char chr, uint32_t xOff, uint32_t yOff)
{
    uint32_t* pix_ptr = (uint32_t*)TargetFramebuffer->base_address;
    char* font_ptr = (char*)PSF1_Font->glyphBuffer + (chr * PSF1_Font->psf1_header->charsize);
    for (unsigned long y = yOff; y < yOff + 16; y++){
        for (unsigned long x = xOff; x < xOff+8; x++){
            if ((*font_ptr & (0b10000000 >> (x - xOff))) > 0){
                    *(uint32_t*)(pix_ptr + x + (y * TargetFramebuffer->pixels_per_scanline)) = colour;
                }

        }
        font_ptr++;
    }
}

void BasicRenderer::put_char(char chr)
{
    put_char(chr, cursor_position.X, cursor_position.Y);
    cursor_position.X += 8;
    if (cursor_position.X + 8 > TargetFramebuffer->width) {
        cursor_position.X = 0;
        cursor_position.Y += 16;
    }
}

void BasicRenderer::set_cursorX(int32_t x) {
    cursor_position.X = x;
}

void BasicRenderer::set_cursorY(int32_t y) {
    cursor_position.Y = y;
}

void BasicRenderer::set_cursor(Point pt) {
    cursor_position.X = pt.X;
    cursor_position.Y = pt.Y;
}

void BasicRenderer::increment_cursorX(int32_t x) {
    cursor_position.X += x;
}

void BasicRenderer::increment_cursorY(int32_t y) {
    cursor_position.Y += y;
}

void BasicRenderer::new_line() {
    cursor_position.X = 0;
    cursor_position.Y += 16;
}

void BasicRenderer::set_colour(Colour new_colour) {
    colour = new_colour;
}

void BasicRenderer::set_clear_color(Colour new_colour) {
    clear_colour = new_colour;
}