#include "./include/kernel_utils.h"

KernelInfo kernelInfo;
PageTableManager pageTableManager = NULL;
void PrepareMemory(BootInfo* bootInfo){
    uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;

    globalAllocator = PageFrameAllocator();
    globalAllocator.ReadEFIMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescSize);

    uint64_t kernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
    uint64_t kernelPages = (uint64_t)kernelSize / 4096 + 1;

    globalAllocator.LockPages(&_KernelStart, kernelPages);

    PageTable* PML4 = (PageTable*)globalAllocator.RequestPage();
    memset(PML4, 0, 0x1000);

    pageTableManager = PageTableManager(PML4);

    for (uint64_t t = 0; t < GetMemorySize(bootInfo->mMap, mMapEntries, bootInfo->mMapDescSize); t+= 0x1000){
        pageTableManager.MapMemory((void*)t, (void*)t);
    }

    uint64_t fbBase = (uint64_t)bootInfo->framebuffer->BaseAddress;
    uint64_t fbSize = (uint64_t)bootInfo->framebuffer->BufferSize + 0x1000;
    globalAllocator.LockPages((void*)fbBase, fbSize/ 0x1000 + 1);
    for (uint64_t t = fbBase; t < fbBase + fbSize; t += 4096){
        pageTableManager.MapMemory((void*)t, (void*)t);
    }

    asm ("mov %0, %%cr3" : : "r" (PML4));

    kernelInfo.page_table_manager = &pageTableManager;
}


KernelInfo InitializeKernel(BootInfo* bootInfo){

    PrepareMemory(bootInfo);

    memset(bootInfo->framebuffer->BaseAddress, 0, bootInfo->framebuffer->BufferSize);

    return kernelInfo;
}