#include <stdint.h>
#include <stddef.h>
#include "../stivale2.h"
#include "util/string.h"
#include "drivers/video/Framebuffer.h"
#include "drivers/IO/PIC.h"
#include "drivers/IO/IO.h"
#include "interrupts/IDT.h"
#include "interrupts/exceptions.h"

static uint8_t stack[8000];


static struct stivale2_header_tag_terminal terminal_tag = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_TERMINAL_ID,
        .next = 0
    },

    .flags = 0
};


static struct stivale2_header_tag_framebuffer lfb_tag = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
        .next = (uint64_t)&terminal_tag, 
    },

    .framebuffer_width = 0,
    .framebuffer_height = 0,
    .framebuffer_bpp = 0
};


__attribute__((section(".stivale2hdr"), used)) static struct stivale2_header stivale_header = {
    .entry_point = 0,
    .stack = (uintptr_t)&stack + sizeof(stack),
    .flags = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4),
    .tags = (uintptr_t)&lfb_tag
};


static void* get_tag(struct stivale2_struct* stivale2_struct, uint64_t id) {
    struct stivale2_tag* curTag = (void*)stivale2_struct->tags;

    while (1) {
        if (!(curTag)) {
            // End.
            return NULL;
        }

        if (curTag->identifier == id) {
            return curTag;
        }

        curTag = (void*)curTag->next;
    }
}


framebuffer_t framebuffer;

// kwrite_main wrapper.
void kwrite(const char* const STR) {    
    framebuffer.kwrite(STR, strlen(STR));
}


void fill_screen(const char* const STR) {
    for (int i = 0; i < 500; ++i) {
        kwrite(STR);
    }
}


void _start(struct stivale2_struct* stivale2_struct) {
    idt_set_vector(0x0, div0_handler, TRAP_GATE_FLAGS);
    idt_set_vector(0x0, div0_handler, TRAP_GATE_FLAGS);
    idt_set_vector(0x1, debug_excp_handler, TRAP_GATE_FLAGS);
    idt_set_vector(0x3, breakpoint_handler, TRAP_GATE_FLAGS);
    idt_set_vector(0x4, overflow_handler, TRAP_GATE_FLAGS);
    idt_set_vector(0x5, bre_handler, TRAP_GATE_FLAGS);
    idt_set_vector(0x6, invld_opcode_handler, TRAP_GATE_FLAGS);
    idt_set_vector(0x7, device_not_avail_handler, TRAP_GATE_FLAGS);
    idt_set_vector(0x8, double_fault_handler, TRAP_GATE_FLAGS);
    idt_set_vector(0x9, cso_handler, TRAP_GATE_FLAGS);
    idt_set_vector(0xA, invalid_tss_handler, TRAP_GATE_FLAGS);
    idt_set_vector(0xB, snp_handler, TRAP_GATE_FLAGS);
    idt_set_vector(0xC, ssf_handler, TRAP_GATE_FLAGS);
    idt_set_vector(0xD, gpf_handler, TRAP_GATE_FLAGS);
    idt_set_vector(0xE, page_fault_handler, TRAP_GATE_FLAGS);
    idt_set_vector(0xF, fpe_handler, TRAP_GATE_FLAGS);
    idt_install();

    struct stivale2_struct_tag_terminal* term_str_tag = get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_TERMINAL_ID);
    struct stivale2_struct_tag_framebuffer* framebuffer_tag = get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);
    framebuffer_tag->red_mask_shift = 0x0;
    framebuffer_tag->green_mask_shift = 0x0;

    if (!(term_str_tag)) {
        while (1) {
            __asm__ __volatile__("hlt");
        }
    }

    void* term_write_addr = (void*)term_str_tag->term_write;
    void(*kwrite_main)(const char* str, size_t length) = term_write_addr;

    framebuffer_t lfb;
    init_framebuffer(&lfb, (void*)framebuffer_tag->framebuffer_addr, (void*)framebuffer_tag, kwrite_main);
    framebuffer = lfb;

    kwrite("\033[34;1;4mOmegaOS - Founder: Ian Marco Moffett\n");
    kwrite("Setting up PIC chips..\n");
    pic_init();
    kwrite("Unmasking IRQ 1..\n");
    outportb(PIC1_DATA, inportb(PIC1_DATA) ^ (1 << 1));
    kwrite("Enabling interrupts..\n");
    __asm__ __volatile__("sti");
    kwrite("Done!\n");

    while (1) {
        __asm__ __volatile__("hlt");
    }
}
