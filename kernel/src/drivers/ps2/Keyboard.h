#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>
#include "../../interrupts/IDT.h"
#include "../IO/IO.h"
#include "../IO/PIC.h"

typedef struct {
    uint16_t scancode;
    char key;
    bool serviced;              // If it has been serviced yet.
    bool press;                 // true if press, false if release.
} keystroke_t;


__attribute__((interrupt)) void kb_isr(int_frame_t* frame);


#endif
