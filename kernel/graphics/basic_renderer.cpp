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

void BasicRenderer::put_pixel(uint32_t x, uint32_t y, Colour colour) {
    *(uint32_t*)((uint64_t)TargetFramebuffer->base_address + (x*4) + (y * TargetFramebuffer->pixels_per_scanline * 4)) = colour;
}

Colour BasicRenderer::get_pixel(uint32_t x, uint32_t y) {
    return *(Colour*)((uint64_t)TargetFramebuffer->base_address + (x*4) + (y * TargetFramebuffer->pixels_per_scanline * 4));
}

void BasicRenderer::clear_mouse_cursor(uint8_t* mouse_cursor, Point position) {
    if (!mouse_drawn) return;

    int32_t x_max = 16;
    int32_t y_max = 16;
    int32_t diffrence_x = TargetFramebuffer->width - position.X;
    int32_t diffrence_y = TargetFramebuffer->height - position.Y;

    if (diffrence_x < 16) x_max = diffrence_x;
    if (diffrence_y < 16) y_max = diffrence_y;

    for (int32_t y = 0; y < y_max; y++) {
        for (int32_t x = 0; x < x_max; x++) {
            int32_t bit = y * 16 + x;
            int32_t byte = bit / 8;
            if ((mouse_cursor[byte] & (0b10000000 >> (x % 8)))) {
                if (get_pixel(position.X + x, position.Y + y) == mouse_cursor_buffer_after[x + y * 16]) {
                    put_pixel(position.X + x, position.Y + y, mouse_cursor_buffer[x + y * 16]); 
                }
            }
        }
    }
}

void BasicRenderer::draw_overlay_mouse_cursor(uint8_t* mouse_cursor, Point position, Colour colour) {
    int32_t x_max = 16;
    int32_t y_max = 16;
    int32_t diffrence_x = TargetFramebuffer->width - position.X;
    int32_t diffrence_y = TargetFramebuffer->height - position.Y;

    if (diffrence_x < 16) x_max = diffrence_x;
    if (diffrence_y < 16) y_max = diffrence_y;

    for (int32_t y = 0; y < y_max; y++) {
        for (int32_t x = 0; x < x_max; x++) {
            int32_t bit = y * 16 + x;
            int32_t byte = bit / 8;
            if ((mouse_cursor[byte] & (0b10000000 >> (x % 8)))) {
                mouse_cursor_buffer[x + y * 16] = get_pixel(position.X + x, position.Y + y);
                put_pixel(position.X + x, position.Y + y, colour);
                mouse_cursor_buffer_after[x + y * 16] = get_pixel(position.X + x, position.Y + y);
            }
        }
    }

    mouse_drawn = true;
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