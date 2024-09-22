//
// Created by linus on 18.09.24.
//

#ifndef HEAP_H
#include <stddef.h>
#define HEAP_H

void* malloc(size_t size);
void free(void* ptr);
void init_heap();
#endif //HEAP_H
