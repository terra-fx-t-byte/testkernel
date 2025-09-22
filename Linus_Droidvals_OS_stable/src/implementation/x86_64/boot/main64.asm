global long_mode_start
extern kernel_main

section .text
bits 64
long_mode_start:
    ;loading 0 into a bunch of registers
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call kernel_main
    hlt
