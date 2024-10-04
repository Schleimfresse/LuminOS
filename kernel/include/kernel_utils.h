//
// Created by linus on 04.10.24.
//

#ifndef KERNEL_UTILS_H
#define KERNEL_UTILS_H
#include <stddef.h> // rm
#include <stdint.h>
#include "basic_renderer.h"
#include "../../include/string.h"
#include "efi_memory.h"
#include "memory.h"
#include "bitmap.h"
#include "page_frame_allocator.h"
#include "page_map_indexer.h"
#include "paging.h"
#include "page_table_manager.h"

struct BootInfo {
	Framebuffer* framebuffer;
	PSF1_FONT* psf1_font;
	EFI_MEMORY_DESCRIPTOR* mMap;
	uint64_t mMapSize;
	uint64_t mMapDescSize;
} ;

extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;

struct KernelInfo {
	PageTableManager* page_table_manager;
};

KernelInfo InitializeKernel(BootInfo* BootInfo);

#endif //KERNEL_UTILS_H