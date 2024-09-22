//
// Created by linus on 21.09.24.
//

#ifndef STRING_H
#define STRING_H
#include <stddef.h>

void *memset (void *dest, int val, size_t len);
void *memcpy (void *dest, const void *src, size_t len);
char* to_string(size_t value);

#endif //STRING_H
