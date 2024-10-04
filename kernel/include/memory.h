//
// Created by linus on 19.09.24.
//

#ifndef MEMORY_H
#define MEMORY_H
#include <stdint.h>
#include "efi_memory.h"

uint64_t GetMemorySize(EFI_MEMORY_DESCRIPTOR* mMap, uint64_t mMapEntries, uint64_t mMapDescSize);
void memset(void* dest, uint8_t val, uint64_t num);
#endif //MEMORY_H