//
// Created by linus on 19.09.24.
//

#ifndef BITMAP_H
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#define BITMAP_H

typedef struct
{
    size_t size;
    uint8_t *Buffer;
} Bitmap;

bool Bitmap_Get(Bitmap* bitmap, uint64_t index);
void Bitmap_Set(Bitmap* bitmap, uint64_t index, bool value);

#endif //BITMAP_H
