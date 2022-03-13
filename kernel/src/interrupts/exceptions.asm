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

div0_handler:
    pop rdi
    mov rsi, 0x0
    call crapout
    cli
    hlt


debug_excp_handler:
    pop rdi
    mov rsi, 0x1
    call crapout
    cli
    hlt

breakpoint_handler:
    pop rdi
    mov rsi, 0x3
    call crapout
    cli
    hlt

overflow_handler:
    pop rdi
    mov rsi, 0x4
    call crapout
    cli
    hlt


bre_handler:
    pop rdi
    mov rsi, 0x5
    call crapout
    cli
    hlt

invld_opcode_handler:
    pop rdi
    mov rsi, 0x6
    call crapout
    cli
    hlt

device_not_avail_handler:
    pop rdi
    mov rsi, 0x7
    call crapout
    cli
    hlt

double_fault_handler:
    pop rdi
    mov rsi, 0x8
    call crapout
    cli
    hlt


cso_handler:
    pop rdi
    mov rsi, 0x9
    call crapout
    cli
    hlt

invalid_tss_handler:
    pop rdi
    mov rsi, 0xA
    call crapout
    cli
    hlt

snp_handler:
    pop rdi
    mov rsi, 0xB
    call crapout
    cli
    hlt

ssf_handler:
    pop rdi
    mov rsi, 0xC
    call crapout
    cli
    hlt

gpf_handler:
    pop rdi
    mov rsi, 0xD
    call crapout
    cli
    hlt

page_fault_handler:
    pop rdi
    mov rsi, 0xE
    cli
    hlt

fpe_handler:
    pop rdi
    mov rsi, 0xF
    call crapout
    cli
    hlt
