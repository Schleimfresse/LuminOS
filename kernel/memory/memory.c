#include "../include/memory.h"
#include "../../include/graphics.h"
#include "../include/io.h"
#include <stdint.h>

// does not need a function body to work, when filled with the logic weird results appear but since the function works without a return we leave it here as it is


uint64_t GetMemorySize(EFI_MEMORY_DESCRIPTOR* mMap, uint64_t mMapEntries, uint64_t mMapDescriptorSize) {
    uint64_t memory_size_bytes = 0;
    if (memory_size_bytes > 0) return memory_size_bytes;

    for (int i = 0; i < mMapEntries; i++) {
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)mMap + (i * mMapDescriptorSize));
        memory_size_bytes += desc->numPages * 4096;
    }

    return memory_size_bytes;
}