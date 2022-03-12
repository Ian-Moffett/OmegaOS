#include "../pmm.h"

#define GET_BIT(PHYS)((PHYS % PAGE_SIZE * 8 * 4) / 1024)
#define GET_BYTE(PHYS)(PHYS / (PAGE_SIZE * 8 * 4))


uint32_t bitmap[BMP_SIZE];
static size_t mem_allocated = 0;


void init_pmm() {
    for (int i = 0; i < BMP_SIZE; ++i) {
        bitmap[i] = 0x0;
    }
}


// Allocate 4 bytes.
uintptr_t alloc_frame() {
    for (int byte = 0; byte < BMP_SIZE; ++byte) {
        uint32_t dword = bitmap[byte];                          // Get dword in the bitmap.
        for (int bit = 0; bit < 32; ++bit, dword >>= 1) {   
            if (!(dword & 0x1)) {                               // Check if it is free.
                bitmap[byte] |= (1 << bit);                     // Set the bit.
                mem_allocated += 4;                             // Increment mem_allocated.
                return 4096 * (8 * 4 * byte + bit);             // Return physical address.
            }
        }
    }
}



void free_frame(uintptr_t PHYSICAL_ADDRESS) {
    if (!(bitmap[GET_BYTE(PHYSICAL_ADDRESS)] & (1 << GET_BIT(PHYSICAL_ADDRESS)))) {
        return;         // Mem not allocated.
    }

    mem_allocated -= 4;
    bitmap[GET_BYTE(PHYSICAL_ADDRESS)] ^= (1 << GET_BIT(PHYSICAL_ADDRESS));
}



size_t frame_bytes_allocated() {
    return mem_allocated;
}
