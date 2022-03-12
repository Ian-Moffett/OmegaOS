#include "../Keyboard.h"

keystroke_t lastKey;

static const uint8_t* const SC_ASCII = "\x00\x1B" "1234567890-=" "\x08"
"\x00" "qwertyuiop[]" "\x0D\x1D" "asdfghjkl;'`" "\x00" "\\"
"zxcvbnm,./" "\x00\x00\x00" " ";


__attribute__((interrupt)) void kb_isr(int_frame_t* frame) {
    uint16_t scancode = inportb(0x60);

    if (scancode & 0x80) {
        char c = SC_ASCII[scancode];
        lastKey.key = c;
        lastKey.serviced = false;
        lastKey.press = true;
        lastKey.scancode = scancode;
    } else {
        lastKey.key = '\0';
        lastKey.serviced = false;
        lastKey.press = false;
        lastKey.scancode = scancode;
    }

    pic_send_EOI(1);
}
