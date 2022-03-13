#include "../initrd.h"


uint32_t vfs_read(vfs_node_t* node, uint32_t offset, uint32_t size, uint8_t* buffer) {
    if (node->read) {
        return node->read(node, offset, size, buffer);
    } else {
        return 0;
    }
}
