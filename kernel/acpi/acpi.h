//
// Created by linus on 06.10.24.
//

#ifndef ACPI_H
#define ACPI_H
#include <stdint.h>

namespace ACPI {
    struct RSDP2 {
        unsigned char signature[8];
        uint8_t checksum;
        uint8_t oem_id[6];
        uint8_t revision;
        uint32_t rsdt_address;
        uint32_t length;
        uint64_t xsdt_address;
        uint8_t extended_checksum;
        uint8_t reserved[3];
    } __attribute__((packed));

    struct SDTHeader {
        unsigned char signature[4];
        uint32_t length;
        uint8_t revision;
        uint8_t checksum;
        uint8_t oem_id[6];
        uint8_t oem_table_id[8];
        uint32_t oem_revision;
        uint32_t creator_id;
        uint32_t creator_revision;
    }__attribute__((packed));

    struct MCFGHeader {
        SDTHeader header;
        uint64_t reserved;
    }__attribute__((packed));

    struct DeviceConfig {
        uint64_t base_address;
        uint16_t pci_seg_group;
        uint8_t start_bus;
        uint8_t end_bus;
        uint32_t reserved;
    }__attribute__((packed));


    void* find_table(SDTHeader* sdt_header, char* signature);
}

#endif //ACPI_H