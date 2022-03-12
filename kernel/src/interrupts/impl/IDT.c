#include "../IDT.h"

static idt_vector_t idt[256];
static idtr_t idtr;


void idt_set_vector(uint8_t vector, void* isr, uint8_t flags) {
    uint64_t addr = (uint64_t)isr;
    idt[vector].isr_low = addr & 0xFFFF;
    idt[vector].isr_high = (addr >> 32) & 0xFFFFFFFF;
    idt[vector].isr_mid = (addr >> 16) & 0xFFFF;
    idt[vector].selector = 0x28;
    idt[vector].reserved = 0x0;
    idt[vector].attr = flags;
    idt[vector].ist = 0x0;
}


void load_idt(idtr_t* idtr);


void idt_install() {
    idtr.limit = (uint16_t)sizeof(idt_vector_t) * 256 - 1;
    idtr.base = (uint64_t)&idt;
    load_idt(&idtr);
}
