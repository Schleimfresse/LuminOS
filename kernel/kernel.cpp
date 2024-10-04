#include "./include/kernel_utils.h"

extern "C" void kernel_main(BootInfo* boot_info){
    
    KernelInfo kernel_info = InitializeKernel(boot_info);
    PageTableManager* page_table_manager = kernel_info.page_table_manager;

    BasicRenderer newRenderer = BasicRenderer(boot_info->framebuffer, boot_info->psf1_font);

    newRenderer.Print("Kernel initialized successfully");

    while (true);
}