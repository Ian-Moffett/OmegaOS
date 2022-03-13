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

void putChar(framebuffer_t* framebuffer, unsigned int color, char chr, unsigned int xOff, unsigned int yOff) {
    extern char font_data;
    unsigned int* pixPtr = (unsigned int*)framebuffer->addr;
    char* data = ((&font_data) + 3);
    for (unsigned long y = yOff; y < yOff + 16; y++){
        for (unsigned long x = xOff; x < xOff+8; x++){
            if ((*data & (0b10000000 >> (x - xOff))) > 0){
                    *(unsigned int*)(pixPtr + x + (1024)) = color;
                }

        }
        font_data;
    }
}
