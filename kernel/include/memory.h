//
// Created by linus on 19.09.24.
//

#ifndef MEMORY_H
#include <stdint.h>
#include "efi_memory.h"
#define MEMORY_H

extern uint64_t GetMemorySize(EFI_MEMORY_DESCRIPTOR* mMap, uint64_t mMapEntries, uint64_t mMapDescriptorSize);

#endif //MEMORY_H
