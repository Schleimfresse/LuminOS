//
// Created by linus on 20.09.24.
//

#include "../include/page_frame_allocator.h"
#include "../../include/string.h"
#include "../../include/graphics.h"
#include "../include/io.h"
#include "../include/memory.h"
#include "../include/bitmap.h"


/*
void InitBitmap(struct PageFrameAllocator* self, size_t bitmapSize, void* bufferAddress);
void LockPages(struct PageFrameAllocator* self, void* address, uint64_t pageCount);
void ReservePages(struct PageFrameAllocator* self, void* address, uint64_t pageCount);
void ReservePage(struct PageFrameAllocator* self, void* address);*/

uint64_t freeMem;
uint64_t reservedMem;
uint64_t usedMem;
bool initialized = false;

void ReadEFIMemoryMap(PageFrameAllocator* self, EFI_MEMORY_DESCRIPTOR* mMap, size_t mMapSize, size_t mMapDescSize) {
    if (initialized) return;

    uint64_t mMapEntries = mMapSize / mMapDescSize;

    void* largestFreeMemSeg = NULL;
    size_t largestFreeMemSegSize = 0;

    for (int i = 0; i < mMapEntries; i++) {
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)mMap + (i * mMapDescSize));
        if (desc->type == 7) {
            if (desc->numPages * 4096 > largestFreeMemSegSize) {
                largestFreeMemSeg = desc->physAddr;
                largestFreeMemSegSize = desc->numPages * 4096;
            }
        }
    }

    uint64_t memSize = GetMemorySize(mMap, mMapEntries, mMapDescSize);
    freeMem = memSize;

    uint64_t bitmapSize = memSize / 4096 / 8 + 1;

    InitBitmap(self, bitmapSize, largestFreeMemSeg);

    LockPages(self, &self->PageBitmap, self->PageBitmap.size / 4096 + 1);

    for (int i = 0; i < mMapEntries; i++) {
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)mMap + (i * mMapDescSize));
        if (desc->type != 7) { // not EfiConventionalMemory
            ReservePages(self, desc->physAddr, desc->numPages);
        }
    }
}

void InitBitmap(PageFrameAllocator* self, size_t bitmapSize, void* bufferAddress) {
    self->PageBitmap.size = bitmapSize;
    self->PageBitmap.Buffer = (uint8_t*)bufferAddress;
    memset(self->PageBitmap.Buffer, 0, self->PageBitmap.size);
}

void FreePage(PageFrameAllocator* self, void* address) {
    uint64_t index = (uint64_t)address / 4096;
    if (!Bitmap_Get(&self->PageBitmap, index)) return;

    Bitmap_Set(&self->PageBitmap, index, false);
    freeMem += 4096;
    usedMem -= 4096;
}

void FreePages(PageFrameAllocator* self, void* addresss, uint64_t pageCount) {
    for (int i = 0; i < pageCount; i++) {
        FreePage(self, (void*)((uint64_t)addresss + (i *4096)));
    }
}

void LockPage(PageFrameAllocator* self, void* address) {
    uint64_t index = (uint64_t)address / 4096;
    if (Bitmap_Get(&self->PageBitmap, index)) return;

    Bitmap_Set(&self->PageBitmap, index, true);
    freeMem -= 4096;
    usedMem += 4096;
}

void LockPages(PageFrameAllocator* self, void* addresss, uint64_t pageCount) {
    for (int i = 0; i < pageCount; i++) {
        LockPage(self, (void*)((uint64_t)addresss + (i *4096)));
    }
}

void UnreservePage(PageFrameAllocator* self, void* address) {
    uint64_t index = (uint64_t)address / 4096;
    if (!Bitmap_Get(&self->PageBitmap, index)) return;

    Bitmap_Set(&self->PageBitmap, index, false);
    freeMem += 4096;
    reservedMem -= 4096;
}

void UnreservePages(PageFrameAllocator* self, void* addresss, uint64_t pageCount) {
    for (int i = 0; i < pageCount; i++) {
        UnreservePage(self, (void*)((uint64_t)addresss + (i *4096)));
    }
}

void ReservePages(PageFrameAllocator* self, void* addresss, uint64_t pageCount) {
    for (int i = 0; i < pageCount; i++) {
        ReservePage(self, (void*)((uint64_t)addresss + (i *4096)));
    }
}

void ReservePage(PageFrameAllocator* self, void* address) {
    uint64_t index = (uint64_t)address / 4096;
    if (Bitmap_Get(&self->PageBitmap, index)) return;

    Bitmap_Set(&self->PageBitmap, index, true);
    freeMem -= 4096;
    reservedMem += 4096;
}

uint64_t GetFreeRAM(PageFrameAllocator* self) {
    return freeMem;
}

uint64_t GetUsedRAM(PageFrameAllocator* self) {
    return usedMem;
}

uint64_t GetReservedRAM(PageFrameAllocator* self) {
    return reservedMem;
}

PageFrameAllocator* InitPageFrameAllocator(PageFrameAllocator* allocator, EFI_MEMORY_DESCRIPTOR* mMap, size_t mMapSize, size_t mMapDescSize) {
    
    allocator->ReadEFIMemoryMap = ReadEFIMemoryMap;
    allocator->FreePage = FreePage; 
    allocator->FreePages = FreePages; 
    allocator->LockPage = LockPage; 
    allocator->LockPages = LockPages; 
    //allocator->RequestPage = RequestPage;
    allocator->GetFreeRAM = GetFreeRAM;
    allocator->GetUsedRAM = GetUsedRAM;
    allocator->GetReservedRAM = GetReservedRAM;

    return allocator;
}
