//
// Created by linus on 13.08.24.
//

#include "../include/multiboot2.h"
#include "multiboot_info.h"

struct multiboot2_info_t multiboot2_info;

void extract_multiboot2_info(unsigned long addr) {
    struct multiboot_tag *tag;
    for (tag = (struct multiboot_tag *) (addr + 8);
           tag->type != MULTIBOOT_TAG_TYPE_END;
           tag = (struct multiboot_tag *) ((multiboot_uint8_t *) tag
                                           + ((tag->size + 7) & ~7)))
    {

        switch (tag->type) {
            case MULTIBOOT_TAG_TYPE_CMDLINE:
                {
                    struct multiboot_tag_string *cmdline_tag = (struct multiboot_tag_string *) tag;
                    multiboot2_info.cmdline = cmdline_tag->string;
                }
                break;

            case MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME:
                {
                    struct multiboot_tag_string *bootloader_name_tag = (struct multiboot_tag_string *) tag;
                    multiboot2_info.bootloader_name = bootloader_name_tag->string;
                }
                break;

            case MULTIBOOT_TAG_TYPE_MMAP:
                {
                    struct multiboot_tag_mmap *mmap_tag = (struct multiboot_tag_mmap *) tag;
                    struct multiboot_mmap_entry *entry;
                    multiboot2_info.memory_map = mmap_tag;
                    for (entry = mmap_tag->entries;
                         (multiboot_uint8_t *) entry < (multiboot_uint8_t *) tag + tag->size;
                         entry = (struct multiboot_mmap_entry *) ((multiboot_uint8_t *) entry + mmap_tag->entry_size)) {
                               (unsigned) (entry->addr >> 32), (unsigned) (entry->addr & 0xFFFFFFFF),
                               (unsigned) (entry->len >> 32), (unsigned) (entry->len & 0xFFFFFFFF),
                               (unsigned) entry->type;
                    }
                }
                break;

            case MULTIBOOT_TAG_TYPE_FRAMEBUFFER:
                {
                    struct multiboot_tag_framebuffer *fb_tag = (struct multiboot_tag_framebuffer *) tag;
                           fb_tag->common.framebuffer_addr, fb_tag->common.framebuffer_pitch,
                           fb_tag->common.framebuffer_width, fb_tag->common.framebuffer_height,
                           fb_tag->common.framebuffer_bpp;
                    multiboot2_info.framebuffer = fb_tag;
                }
                break;

            default:
                break;
        }
    }

}