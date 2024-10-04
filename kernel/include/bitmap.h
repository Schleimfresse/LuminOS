//
// Created by linus on 19.09.24.
//

#ifndef BITMAP_H
#include <stddef.h>
#include <stdint.h>
#define BITMAP_H

class Bitmap{
    public:
    size_t Size;
    uint8_t* Buffer;
    bool operator[](uint64_t index);
    bool Set(uint64_t index, bool value);
};

#endif //BITMAP_H