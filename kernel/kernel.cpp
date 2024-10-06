#include "./include/kernel_utils.h"

extern "C" void kernel_main(BootInfo* boot_info){
    
   KernelInfo kernel_info = initialize_kernel(boot_info);
   PageTableManager* page_table_manager = kernel_info.page_table_manager;

    global_renderer->print("Kernel initialized successfully");

    global_renderer->new_line();
    global_renderer->print(to_hstring((uint64_t)boot_info->rsdp));

    while (true);
}