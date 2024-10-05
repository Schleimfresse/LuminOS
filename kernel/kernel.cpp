#include "./include/kernel_utils.h"

extern "C" void kernel_main(BootInfo* boot_info){
    
    KernelInfo kernel_info = initialize_kernel(boot_info);
    PageTableManager* page_table_manager = kernel_info.page_table_manager;

    global_renderer->print("Kernel initialized successfully");

    while (true) {
        process_mouse_packet();
    };
    

    while (true);
}