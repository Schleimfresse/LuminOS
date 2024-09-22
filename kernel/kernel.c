#include "../include/graphics.h"
#include "./include/heap.h"
#include "./include/memory.h"
#include "./include/bitmap.h"
//#include "./include/page_frame_allocator.h"
#include "./include/io.h"
#include "../include/string.h"
#include <stdint.h>

typedef struct {
	Framebuffer* framebuffer;
	PSF1_FONT* psf1_font;
	EFI_MEMORY_DESCRIPTOR* mMap;
	uint64_t mMapSize;
	uint64_t mMapDescriptorSize;
} BootInfo;

Framebuffer* fb;
PSF1_FONT* psf1_font;
//Framebuffer* backBuffer;

/*void swap_buffers() {
    memcpy(fb->BaseAddress, backBuffer->BaseAddress, fb->BufferSize);
}

void init_back_buffer() {
    backBuffer = (Framebuffer*)malloc(sizeof(Framebuffer));

    if (backBuffer) {
        Print("Successfully allocated 8294400 bytes", GRAY);
    } else {
        Print("Allocation failed", GRAY);
        return;
    }
    backBuffer->BaseAddress = (uint32_t*)malloc(fb->BufferSize); 
    if (backBuffer->BaseAddress == NULL) {
    
        free(backBuffer);
        return;
    }

    backBuffer->BufferSize = fb->BufferSize;
    backBuffer->Width = fb->Width;
    backBuffer->Height = fb->Height;
    backBuffer->PixelsPerScanLine = fb->PixelsPerScanLine;
    memset(backBuffer->BaseAddress, 0, backBuffer->BufferSize);

}*/









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











































void kernel_main(BootInfo* bootInfo) {
    fb = bootInfo->framebuffer;
    psf1_font = bootInfo->psf1_font;
    uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescriptorSize;

    Print(to_string(GetMemorySize(bootInfo->mMap, mMapEntries, bootInfo->mMapDescriptorSize) / 1024 / 1024), GREEN);
    Print("Mb ", WHITE);
    Print(to_string(mMapEntries), WHITE);
    Print(" ", WHITE);
    Print(to_string(bootInfo->mMapDescriptorSize), WHITE);

    SetCursor(50, 120);

    init_heap();
    //init_back_buffer();

    /*int BBP = 4;
    for (uint32_t y = 200; y < 250; y++) {
		for (uint32_t x = 0; x < fb->Width; x++) {
            if (x < fb->Width && y < fb->Height) {
                *(uint32_t*)(fb->BaseAddress + (x + y * fb->PixelsPerScanLine) * BBP) = BLUE;
            }
        }
	}*/
    // swap_buffers();
    PageFrameAllocator page_frame_allocator;
    PageFrameAllocator* pfa_ptr = &page_frame_allocator;
    //PageFrameAllocator* new_allocator = InitPageFrameAllocator(&page_frame_allocator, bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescriptorSize);
    
    ReadEFIMemoryMap(pfa_ptr, bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescriptorSize);

    Print(to_string(bootInfo->mMapSize), GREEN);
        Print("  ", GREEN);
    Print(to_string(bootInfo->mMapDescriptorSize), GREEN);
    
    IncrementCursorY(16);
    SetCursorX(0);
    Print("Free RAM:", WHITE);
    Print(to_string(GetFreeRAM(pfa_ptr) / 1024 / 1024), GRAY);
    Print(" KB ", WHITE);

    IncrementCursorY(16);
    SetCursorX(0);
    Print("Used RAM:", WHITE);
    Print(to_string(GetUsedRAM(pfa_ptr) / 1024 / 1024), GRAY);
    Print(" KB ", WHITE);

    IncrementCursorY(16);
    SetCursorX(0);
    Print("Reserved RAM:", WHITE);
    Print(to_string(GetReservedRAM(pfa_ptr) / 1024 / 1024), GRAY);
    Print(" KB ", WHITE);

    IncrementCursorY(16);
    SetCursorX(0);
    Print("Total RAM:", WHITE);
    Print(to_string((GetReservedRAM(pfa_ptr) + GetFreeRAM(pfa_ptr) + GetUsedRAM(pfa_ptr)) / 1024 / 1024), CYAN);
    Print(" KB ", WHITE);

    __asm__ volatile("int3"); 

    while (1);
}