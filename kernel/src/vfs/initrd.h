#ifndef INITRD_H
#define INITRD_H

/*
 *  A basic virtual filesystem that
 *  just supports reading files.
 *  Designed & engineered by Ian Marco Moffett
 */


#include <stdint.h>

typedef struct {
   uint32_t nfiles; // The number of files in the ramdisk.
} initrd_header_t;

typedef struct {
    uint8_t magic;     // Magic number, for error checking.
    int8_t name[64];  // Filename.
    uint32_t offset;   // Offset in the initrd that the file starts.
    uint32_t length;   // Length of the file.
} initrd_file_header_t;


typedef struct VFSNode {
    char filename[128];
    uint32_t(*read)(struct VFSNode*, uint32_t, uint32_t, uint8_t*);
    void(*open)(struct VFSNode*);
    void(*close)(struct VFSNode*);
} vfs_node_t;


uint32_t vfs_read(vfs_node_t* node, uint32_t offset, uint32_t size, uint8_t* buffer);


#endif
