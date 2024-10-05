#include "./include/kernel_utils.h"
#include "../arch/x86_64/gdt/gdt.h"
#include "../arch/x86_64/interrupts/idt.h"
#include "../arch/x86_64/interrupts/interrupts.h"

KernelInfo kernelInfo;
PageTableManager pageTableManager = NULL;
void prepare_memory(BootInfo* bootInfo){
    uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;

    global_allocator = PageFrameAllocator();
    global_allocator.read_efi_memory_map(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescSize);

    uint64_t kernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
    uint64_t kernelPages = (uint64_t)kernelSize / 4096 + 1;

    global_allocator.lock_pages(&_KernelStart, kernelPages);

    PageTable* PML4 = (PageTable*)global_allocator.request_page();
    memset(PML4, 0, 0x1000);

    pageTableManager = PageTableManager(PML4);

    for (uint64_t t = 0; t < get_memory_size(bootInfo->mMap, mMapEntries, bootInfo->mMapDescSize); t+= 0x1000){
        pageTableManager.MapMemory((void*)t, (void*)t);
    }

    uint64_t fbBase = (uint64_t)bootInfo->framebuffer->base_address;
    uint64_t fbSize = (uint64_t)bootInfo->framebuffer->buffer_size + 0x1000;
    global_allocator.lock_pages((void*)fbBase, fbSize/ 0x1000 + 1);
    for (uint64_t t = fbBase; t < fbBase + fbSize; t += 4096){
        pageTableManager.MapMemory((void*)t, (void*)t);
    }

    asm ("mov %0, %%cr3" : : "r" (PML4));

    kernelInfo.page_table_manager = &pageTableManager;
}

IDTR idtr;
void set_idt_gate(void* handler, uint8_t entry_offset, uint8_t type_attr, uint8_t selector) {
    IDTDescEntry* interrupt = (IDTDescEntry*)(idtr.offset + entry_offset * sizeof(IDTDescEntry));
    interrupt->set_offset((uint64_t)handler);
    interrupt->type_attr = type_attr;
    interrupt->selector = selector;
}

void prepare_interrupts() {
    idtr.limit = 0x0FFF;
    idtr.offset = (uint64_t)global_allocator.request_page();

    set_idt_gate((void*)page_fault_handler, 0xE, IDT_TA_InterruptGate, 0x08);
    set_idt_gate((void*)double_fault_handler, 0x8, IDT_TA_InterruptGate, 0x08);
    set_idt_gate((void*)gp_fault_handler, 0xD, IDT_TA_InterruptGate, 0x08);
    set_idt_gate((void*)keyboard_int_handler, 0x21, IDT_TA_InterruptGate, 0x08);
    set_idt_gate((void*)mouse_int_handler, 0x2C, IDT_TA_InterruptGate, 0x08);

    asm ("lidt %0" : : "m" (idtr));

    remap_pic();
}

BasicRenderer r = BasicRenderer(NULL, NULL);
KernelInfo initialize_kernel(BootInfo* bootInfo){
    r = BasicRenderer(bootInfo->framebuffer, bootInfo->psf1_font);
    global_renderer = &r;

    GDTDescriptor gdt_descriptor;
    gdt_descriptor.size = sizeof(GDT) - 1;
    gdt_descriptor.offset = (uint64_t)&default_gdt;
    load_GDT(&gdt_descriptor);

    prepare_memory(bootInfo);

    memset(bootInfo->framebuffer->base_address, 0, bootInfo->framebuffer->buffer_size);

    prepare_interrupts();

    initialize_ps2_mouse();

    outb(PIC1_DATA, 0b11111001);
    outb(PIC2_DATA, 0b11101111);

    asm ("sti");

    return kernelInfo;
}