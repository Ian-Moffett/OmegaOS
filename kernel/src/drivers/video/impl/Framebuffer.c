#include "../Framebuffer.h"

void init_framebuffer(framebuffer_t* lfb, void* addr, void* fb_core, void* kwrite) {
    lfb->r = 0xFF;
    lfb->g = 0xFF;
    lfb->b = 0xFF;
    lfb->x = 10;
    lfb->y = 50;
    lfb->gapsize = 300;
    lfb->addr = addr;
    lfb->fb_core = fb_core;
    lfb->kwrite = kwrite;
}
