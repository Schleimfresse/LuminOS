//
// Created by linus on 13.08.24.
//

#ifndef MULTIBOOT_INFO_H
#define MULTIBOOT_INFO_H
#include "../include/multiboot2.h"

void extract_multiboot2_info(unsigned long addr);

struct multiboot2_info_t {
    const char *cmdline;                        // Command line string
    const char *bootloader_name;                // Bootloader name string
    struct multiboot_tag_mmap *memory_map;      // Memory map
    struct multiboot_tag_framebuffer *framebuffer; // Framebuffer info
};

extern struct multiboot2_info_t multiboot2_info;

#endif //MULTIBOOT_INFO_H
