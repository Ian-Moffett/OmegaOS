#include "../exceptions.h"


static void crapout(int_frame_t* frame, uint16_t vector) {
    kwrite("\n\033[41;1;37mFATAL CPU EXCEPTION: ");
    kwrite((char*)hex2str(vector));
    kwrite("\n*** KERNEL PANIC ***\n\n");
    kwrite("<==== INTERRUPT FRAME DUMP ====>\n\n");
    kwrite("RIP: ");
    kwrite((char*)hex2str(frame->rip));
    kwrite("\nCS: ");
    kwrite((char*)hex2str(frame->cs));
    kwrite("\nRFLAGS: ");
    kwrite((char*)hex2str(frame->rflags));
    kwrite("\nRSP: ");
    kwrite((char*)hex2str(frame->rsp));
    kwrite("\nSS: ");
    kwrite((char*)hex2str(frame->ss));
    kwrite("\n\n*** SYSTEM HALTED ***\n");

    __asm__ __volatile__("hlt");
}



__attribute__((interrupt)) void div0_handler(int_frame_t* frame) {
    crapout(frame, 0x0);
}


__attribute__((interrupt)) void debug_excp_handler(int_frame_t* frame) {
    crapout(frame, 0x1);
}

__attribute__((interrupt)) void breakpoint_handler(int_frame_t* frame) {
    crapout(frame, 0x3);
}

__attribute__((interrupt)) void overflow_handler(int_frame_t* frame) {
    crapout(frame, 0x4);
}


__attribute__((interrupt)) void bre_handler(int_frame_t* frame) {
    crapout(frame, 0x5);
}


__attribute__((interrupt)) void invld_opcode_handler(int_frame_t* frame) {
    crapout(frame, 0x6);
}


__attribute__((interrupt)) void device_not_avail_handler(int_frame_t* frame) {
    crapout(frame, 0x7);
}


__attribute__((interrupt)) void double_fault_handler(int_frame_t* frame) {
    crapout(frame, 0x8);
}


__attribute__((interrupt)) void cso_handler(int_frame_t* frame) {
    crapout(frame, 0x9);
}


__attribute__((interrupt)) void invalid_tss_handler(int_frame_t* frame) {
    crapout(frame, 0xA);
}

__attribute__((interrupt)) void snp_handler(int_frame_t* frame) {
    crapout(frame, 0xB);
}


__attribute__((interrupt)) void ssf_handler(int_frame_t* frame) {
    crapout(frame, 0xC);
}


__attribute__((interrupt)) void gpf_handler(int_frame_t* frame) {
    crapout(frame, 0xD);
}


__attribute__((interrupt)) void page_fault_handler(int_frame_t* frame) {
    crapout(frame, 0xE);
}

__attribute__((interrupt)) void fpe_handler(int_frame_t* frame) {
    crapout(frame, 0xF);
}
