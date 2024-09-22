//
// Created by linus on 20.09.24.
//

#ifndef PAGE_FRAME_ALLOCATOR_H
#define PAGE_FRAME_ALLOCATOR_H
#include "efi_memory.h"
#include <stdint.h>
#include "bitmap.h"
#include "memory.h"

typedef struct PageFrameAllocator {
    Bitmap PageBitmap;

    void (*ReadEFIMemoryMap)(struct PageFrameAllocator* self, EFI_MEMORY_DESCRIPTOR* mMap, size_t mMapSize, size_t mMapDescSize);
    void (*FreePage)(struct PageFrameAllocator* self, void* address);
    void (*FreePages)(struct PageFrameAllocator* self, void* address, uint64_t pageCount);
    void (*LockPage)(struct PageFrameAllocator* self, void* address);
    void (*LockPages)(struct PageFrameAllocator* self, void* address, uint64_t pageCount);
    void* (*RequestPage)(struct PageFrameAllocator* self);
    uint64_t (*GetFreeRAM)(struct PageFrameAllocator* self);
    uint64_t (*GetUsedRAM)(struct PageFrameAllocator* self);
    uint64_t (*GetReservedRAM)(struct PageFrameAllocator* self);
} PageFrameAllocator;

extern PageFrameAllocator* InitPageFrameAllocator(PageFrameAllocator* allocator, EFI_MEMORY_DESCRIPTOR* mMap, size_t mMapSize, size_t mMapDescSize);


#endif // PAGE_FRAME_ALLOCATOR_H