//
// Created by linus on 20.09.24.
//
#ifndef PAGE_FRAME_ALLOCATOR_H
#define PAGE_FRAME_ALLOCATOR_H
#include "efi_memory.h"
#include <stdint.h>
#include "bitmap.h"
#include "memory.h"

class PageFrameAllocator {
    public:
    void read_efi_memory_map(EFI_MEMORY_DESCRIPTOR* mMap, size_t mMapSize, size_t mMapDescSize);
    Bitmap page_bitmap;
    void free_page(void* address);
    void free_pages(void* address, uint64_t page_count);
    void lock_page(void* address);
    void lock_pages(void* address, uint64_t page_count);
    void* request_page();
    uint64_t get_free_ram();
    uint64_t get_used_ram();
    uint64_t get_reserved_ram();


    private:
    void init_bitmap(size_t bitmap_size, void* buffer_address);
    void reserve_page(void* address);
    void reserve_pages(void* address, uint64_t page_count);
    void unreserve_page(void* address);
    void unreserve_pages(void* address, uint64_t page_count);

};

extern PageFrameAllocator global_allocator;

#endif // PAGE_FRAME_ALLOCATOR_H