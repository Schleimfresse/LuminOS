#include "keyboard.h"
#include "../../kernel/include/basic_renderer.h"

bool is_left_shift_pressed;
bool is_right_shift_pressed;

void handle_keyboard(uint8_t scancode) {
    char ascii = QWERTYKeyboard::translate(scancode, is_left_shift_pressed | is_right_shift_pressed);

    switch (scancode) {
        case left_shift:
            is_left_shift_pressed = true;
            return;
        
        case left_shift + 0x80:
            is_left_shift_pressed = false;
            return;
        case right_shift:
            is_right_shift_pressed = true;
            return;
        case enter:
            global_renderer->new_line();
            return;
        case spacebar:
            global_renderer->put_char(' ');
            return;
        case back_space:
            global_renderer->clear_char();
            return;
    };
    if (ascii != 0) {
        global_renderer->put_char(ascii);
    }
}