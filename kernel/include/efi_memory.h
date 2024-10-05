//
// Created by linus on 18.09.24.
//

#ifndef EFI_MEMORY_H
#define EFI_MEMORY_H
#include <stdint.h>

struct EFI_MEMORY_DESCRIPTOR {
    uint32_t type;
    void* phys_addr;
    void* virt_addr; 
    uint64_t num_pages;
    uint64_t attribs;
};

extern const char* EFI_MEMORY_TYPE_STRINGS[];
#endif //EFI_MEMORY_H