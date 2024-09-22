//
// Created by linus on 18.09.24.
//

#ifndef EFI_MEMORY_H
#define EFI_MEMORY_H
#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint32_t type;
    void* physAddr;
    void* virtAddr;
    uint64_t numPages;
    uint64_t attributes;
} EFI_MEMORY_DESCRIPTOR;

extern const char* EFI_MEMORY_TYPE_STRINGS[];
#endif //EFI_MEMORY_H