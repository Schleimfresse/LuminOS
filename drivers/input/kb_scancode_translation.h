//
// Created by linus on 05.10.24.
//

#ifndef KB_SCANCODE_TRANSLATION_H
#define KB_SCANCODE_TRANSLATION_H
#include <stdint.h>

namespace QWERTYKeyboard {
    #define left_shift 0x2A
    #define right_shift 0x36
    #define enter 0x1C
    #define back_space 0x0E
    #define spacebar 0x39

    extern const char ascii_table[];
    char translate(uint8_t scancode, bool uppercase);
}

#endif //KB_SCANCODE_TRANSLATION_H