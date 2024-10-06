//
// Created by linus on 04.10.24.
//
#ifndef PAGE_TABLE_MANAGER_H
#define PAGE_TABLE_MANAGER_H
#include <stdint.h>
#include "paging.h"

class PageTableManager {
    public:
    PageTableManager(PageTable* PML4Address);
    PageTable* PML4;
    void MapMemory(void* virtualMemory, void* physicalMemory);
};

extern PageTableManager global_page_table_manager ;


#endif // PAGE_TABLE_MANAGER_H