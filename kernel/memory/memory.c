#include "../include/memory.h"
#include "../../include/graphics.h"
#include "../../include/string.h"
#include "../include/io.h"
#include <stdint.h>

uint64_t GetMemorySize(EFI_MEMORY_DESCRIPTOR* mMap, uint64_t mMapEntries, uint64_t mMapDescriptorSize) {
    uint64_t memory_size_bytes = 0;
    if (memory_size_bytes > 0) return memory_size_bytes;

    for (int i = 0; i < mMapEntries; i++) {
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)mMap + (i * mMapDescriptorSize));
        memory_size_bytes += desc->numPages * 4096;
    }
    IncrementCursorY(16);
    Print(to_string(memory_size_bytes), WHITE);

    return memory_size_bytes;
}