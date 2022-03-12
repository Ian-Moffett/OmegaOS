#ifndef PCI_H
#define PCI_H

#include <stdint.h>

/*
 *  @slot - which slot on the motherboard to choose.
 *  @func - which device function to use.
 *  @reg_offsett - register address.
 */

uint16_t pci_config_read_word(uint8_t bus, uint8_t slot, uint8_t func, uint8_t reg_offset);


#endif
