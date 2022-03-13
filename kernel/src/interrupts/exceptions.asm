global div0_handler
global debug_excp_handler
global breakpoint_handler
global overflow_handler
global bre_handler          ; Bound range exceeded
global invld_opcode_handler 
global device_not_avail_handler
global double_fault_handler
global cso_handler                  ; Copressesor overrun.
global invalid_tss_handler
global snp_handler                  ; Segment not present.
global ssf_handler
global gpf_handler
global gpf_handler
global page_fault_handler
global fpe_handler              ; Floating point exception handler

extern crapout

%macro panic 1
    pop rdi
    mov rsi, %1
    times 6 pop rdx
    call crapout
    cli
    hlt
%endmacro

div0_handler:
    panic 0x0

debug_excp_handler:
    panic 0x1

breakpoint_handler:
    panic 0x3

overflow_handler:
    panic 0x4

bre_handler:
    panic 0x5

invld_opcode_handler:
    panic 0x6

device_not_avail_handler:
    panic 0x7

double_fault_handler:
    panic 0x7

cso_handler:
    panic 0x9

invalid_tss_handler:
    panic 0xA

snp_handler:
    panic 0xB

ssf_handler:
    panic 0xC

gpf_handler:
    panic 0xD

page_fault_handler:
    panic 0xE

fpe_handler:
    panic 0xF
