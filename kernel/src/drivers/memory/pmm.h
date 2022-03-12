#ifndef PMM_H
#define PMM_H

#include <stdint.h>
#include <stddef.h>

#define _1KB (1 << 10)
#define _1MB (1 << 21)
#define _1GB (1 << 30)
#define RAM 64 * _1MB
#define PAGE_SIZE 4096
#define BMP_SIZE RAM / (PAGE_SIZE * 8 * sizeof(uint32_t))


void init_pmm();
uintptr_t alloc_frame();
void free_frame(const uintptr_t PHYSICAL_ADDRESS);
size_t frame_bytes_allocated();


uintptr_t alloc_frame();

#endif
