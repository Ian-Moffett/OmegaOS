#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    unsigned char magic[2];
    unsigned char mode;
    unsigned char chsize;
} psf1_header_t;


typedef struct {
    psf1_header_t* header;
    void* glpyhBuffer;
} psf1_font_t;


typedef struct {
    void(*kwrite)(const char* const STR, size_t size);
    void* addr;
    void* fb_core;
    uint64_t x;
    uint64_t y;
    uint16_t gapsize;
    uint8_t r;
    uint8_t g;
    uint8_t b;
} framebuffer_t;


void kwrite(framebuffer_t framebuffer, const char* STR);
void init_framebuffer(framebuffer_t* lfb, void* addr, void* fb_core, void* kwrite);


#endif
