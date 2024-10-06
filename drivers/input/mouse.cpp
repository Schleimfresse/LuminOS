#include "mouse.h"

uint8_t mouse_pointer[] = {
    0b11111111, 0b11100000,
    0b11111111, 0b10000000,
    0b11111110, 0b00000000,
    0b11111100, 0b00000000,
    0b11111000, 0b00000000,
    0b11110000, 0b00000000,
    0b11100000, 0b00000000,
    0b11000000, 0b00000000,
    0b11000000, 0b00000000,
    0b10000000, 0b00000000,
    0b10000000, 0b00000000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
}; // upgrade this

void mouse_wait() {
    uint64_t timeout = 100000;
    while (timeout--) {    
        if ((inb(0x64) & 0b10) == 0) {
            return;
        }
    }
}

void mouse_wait_input() {
    uint64_t timeout = 100000;
    while (timeout--) {    
        if (inb(0x64) & 0b1) {
            return;
        }
    }
}

void mouse_write(uint8_t value) {
    mouse_wait();
    outb(0x64, 0xD4);
    mouse_wait();
    outb(0x60, value);
}

uint8_t mouse_read() {
    mouse_wait_input();
    return inb(0x60);
}

uint8_t mouse_cycle = 0;
uint8_t mouse_packet[4];
bool mouse_packet_ready = false;
Point mouse_position;
Point mouse_position_old;
void handle_ps2_mouse(uint8_t data) {

    process_mouse_packet();
    static bool skip = true;
    if (skip) {skip = false; return;}

    switch (mouse_cycle) {
        case 0:
            if (data & 0b00001000 == 0) break;
            mouse_packet[0] = data;
            mouse_cycle++;
            break;
        case 1:
            mouse_packet[1] = data;
            mouse_cycle++;
            break;
        case 2:
            mouse_packet[2] = data;
            mouse_packet_ready = true;
            mouse_cycle = 0;
            break;
    }
}

void process_mouse_packet() {
    if (!mouse_packet_ready) return;
        mouse_packet_ready = false;

        bool x_negative, y_negative, x_overflow, y_overflow;

        if (mouse_packet[0] & PS2XSign) {
            x_negative = true;
        } else x_negative = false;

        if (mouse_packet[0] & PS2YSign) {
            y_negative = true;
        } else y_negative = false;

        if (mouse_packet[0] & PS2XOverflow) {
            x_overflow = true;
        } else x_overflow = false;

        if (mouse_packet[0] & PS2YOverflow) {
            y_overflow = true;
        } else y_overflow = false;

        if (!x_negative) {
            mouse_position.X += mouse_packet[1];
            if (x_overflow) {
                mouse_position.X += 255;
            }
        } else {
            mouse_packet[1] = 256 - mouse_packet[1];
            mouse_position.X -= mouse_packet[1];
            if (x_overflow) {
                mouse_position.X -= 255;
            }
        }

         if (!y_negative) {
            mouse_position.Y -= mouse_packet[2];
            if (y_overflow) {
                mouse_position.Y -= 255;
            }
        } else {
            mouse_packet[2] = 256 - mouse_packet[2];
            mouse_position.Y += mouse_packet[2];
            if (y_overflow) {
                mouse_position.Y += 255;
            }
        }

        if (mouse_position.X < 0) mouse_position.X = 0;
        if (mouse_position.X > global_renderer->TargetFramebuffer->width-1) mouse_position.X = global_renderer->TargetFramebuffer->width-1;

        if (mouse_position.Y < 0) mouse_position.Y = 0;
        if (mouse_position.Y > global_renderer->TargetFramebuffer->height-1) mouse_position.Y = global_renderer->TargetFramebuffer->height-1;

        global_renderer->clear_mouse_cursor(mouse_pointer, mouse_position_old);
        global_renderer->draw_overlay_mouse_cursor(mouse_pointer, mouse_position, Colour::WHITE);

        if (mouse_packet[0] & PS2LeftButton) {

        }
        if (mouse_packet[0] & PS2MiddleButton) {

        }
        if (mouse_packet[0] & PS2RightButton) {

        }
        
        mouse_packet_ready = false;
        mouse_position_old = mouse_position;
}

void initialize_ps2_mouse() {
    outb(0x64, 0xA8); // enabling he auxiliary device - mouse

    mouse_wait();
    outb(0x64, 0x20);
    mouse_wait_input();
    uint8_t status = inb(0x60);
    status |= 0b10;
    mouse_wait();
    outb(0x64, 0x60);
    mouse_wait();
    outb(0x60, status); // setting correct bit is the "compaq" status byte https://wiki.osdev.org/PS/2_Mouse

    mouse_write(0xF6);
    mouse_read();

    mouse_write(0xF4);
    mouse_read();
}