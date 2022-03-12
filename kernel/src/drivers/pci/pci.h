#ifndef PCI_H
#define PCI_H


#include <stdint.h>
#include <stdbool.h>
#include "../IO/IO.h"
#include "../video/Framebuffer.h"

/*
 *  @slot - which slot on the motherboard to choose.
 *  @func - which device function to use.
 *  @reg_offsett - register address.
 */

uint16_t pci_config_read_word(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
uint16_t pci_read_vender(uint8_t bus, uint8_t slot);
void pci_verbose_scan();


#endif
