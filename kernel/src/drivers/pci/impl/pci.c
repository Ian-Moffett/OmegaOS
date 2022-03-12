#include "../pci.h"


uint16_t pci_config_read_word(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
    uint32_t lbus = (uint32_t)bus;
    uint32_t lslot = (uint32_t)slot;
    uint32_t lfunc = (uint32_t)func;

    // Get address to read from.

     uint32_t address = (uint32_t)((lbus << 16) | (lslot << 11) |
              (lfunc << 8) | (offset & 0xFC) | ((uint32_t)0x80000000));

     // Write address to read from.
     outportb(0xCF8, address);

     // Read first word of 32 bit register.
     uint16_t res = (uint16_t)((inportb(0xCFC) >> ((offset & 2) * 8)) & 0xFFFF);
     return res;
}



uint16_t pci_read_vender(uint8_t bus, uint8_t slot) {
    return pci_config_read_word(bus, slot, 0, 0);
}


void pci_verbose_scan() {
    for (int bus = 0; bus < 256; ++bus) {
        for (int device = 0; device < 32; ++device) {
            kwrite("\033[32;1;4mChecking bus ");
            kwrite(dec2str(bus));
            kwrite(", device ");
            kwrite(dec2str(device));

            uint16_t vendor = pci_read_vender(bus, device);

            if (vendor == 0xFFFF) {
                kwrite(" - \033[31;1;4mNo device found on this bus and slot");
            } else {
                kwrite(" - \033[32;1;4mDevice found with vender ID: ");
                kwrite(hex2str(vendor));
                kwrite("\n");
            }
        }
    }
}
