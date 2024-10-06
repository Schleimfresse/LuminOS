#include "pci.h"

namespace PCI {

    void enumerate_function(uint64_t device_address, uint64_t function) {
        uint64_t offset = function << 12;

        uint64_t function_address = device_address + offset;
        global_page_table_manager.MapMemory((void*)function_address, (void*)function_address);

        PCI::PCIDeviceHeader* pci_device_header = (PCIDeviceHeader*)function_address;

        if (pci_device_header->device_id == 0) return;
        if (pci_device_header->device_id == 0xFFFF) return;

        global_renderer->print(get_vendor_name(pci_device_header->vendor_id));
        global_renderer->print(" ");
        global_renderer->print(get_device_name(pci_device_header->vendor_id, pci_device_header->device_id));
        global_renderer->print(" ");
        global_renderer->print(get_subclass_name(pci_device_header->_class, pci_device_header->subclass));
        global_renderer->print(" ");
        global_renderer->print(get_prog_if_Name(pci_device_header->_class, pci_device_header->subclass, pci_device_header->prog_if));
        global_renderer->new_line();

    }

    void enumerate_device(uint64_t bus_address, uint64_t device) {
        uint64_t offset = device << 15;

        uint64_t device_address = bus_address + offset;
        global_page_table_manager.MapMemory((void*)device_address, (void*)device_address);

        PCI::PCIDeviceHeader* pci_device_header = (PCIDeviceHeader*)device_address;

        if (pci_device_header->device_id == 0) return;
        if (pci_device_header->device_id == 0xFFFF) return;

        for (uint64_t function = 0; function < 8; function++) {
            enumerate_function(device_address, function);
        }
    }

    void enumerate_bus(uint64_t base_address, uint64_t bus) {
        uint64_t offset = bus << 20;

        uint64_t bus_address = base_address + offset;
        global_page_table_manager.MapMemory((void*)bus_address, (void*)bus_address);

        PCI::PCIDeviceHeader* pci_device_header = (PCIDeviceHeader*)bus_address;

        if (pci_device_header->device_id == 0) return;
        if (pci_device_header->device_id == 0xFFFF) return;

        for (uint64_t device = 0; device < 32; device++) {
            enumerate_device(bus_address, device);
        }
    }

    void enumerate_pci(ACPI::MCFGHeader* mcfg) {
        int entries = ((mcfg->header.length) - sizeof(ACPI::MCFGHeader)) / sizeof(ACPI::DeviceConfig);

        for (int t = 0; t < entries; t++) {
            ACPI::DeviceConfig* new_device_config = (ACPI::DeviceConfig*)((uint64_t)mcfg + sizeof(ACPI::MCFGHeader) + (sizeof(ACPI::DeviceConfig) * t));
            for (uint64_t bus = new_device_config->start_bus; bus < new_device_config->end_bus; bus++) {
                enumerate_bus(new_device_config->base_address, bus);
            }
        }
    }

}