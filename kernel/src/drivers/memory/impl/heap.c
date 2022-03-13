#include "../heap.h"


typedef struct MemBlock {
    struct MemBlock* next;
    size_t size;
} memblock_t; 
