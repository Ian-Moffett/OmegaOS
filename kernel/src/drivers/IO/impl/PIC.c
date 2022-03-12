#include "../PIC.h"


void pic_send_EOI(int irq) {
    if (irq >= 8) {
        outportb(PIC2_COMMAND, PIC_EOI);
    }

    outportb(PIC1_COMMAND, PIC_EOI);
}


void pic_init() {
    static bool init = false;
    if (init) return;
    init = true;
    uint8_t master_bm, slave_bm;

    // Get bitmasks.
    master_bm = inportb(PIC1_DATA);
    io_wait();
    slave_bm = inportb(PIC2_DATA);

    // Mask everything.
    master_bm = 0xFF;
    slave_bm = 0xFF;

    // Init master PIC.
    outportb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    // Init slave PIC.
    outportb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();

    // Remap PIC.
    outportb(PIC1_DATA, 0x20);
    io_wait();
    outportb(PIC2_DATA, 0x28);
    io_wait();

    outportb(PIC1_DATA, 4);
    io_wait();
    outportb(PIC2_DATA, 2);
    io_wait();

    // V8086  mode.
    outportb(PIC1_DATA, ICW4_8086);
    io_wait();
    outportb(PIC2_DATA, ICW4_8086);
    io_wait();

    // Restore bitmasks.
    outportb(PIC1_DATA, master_bm);
    io_wait();
    outportb(PIC2_DATA, slave_bm);
}
