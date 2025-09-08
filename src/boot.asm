; -----------------------------
; Minimaler Multiboot Header
; -----------------------------
section .multiboot
    align 4
    dd 0x1BADB002        ; Multiboot Magic
    dd 0x0               ; Flags
    dd -(0x1BADB002+0)   ; Checksum

; -----------------------------
; Entry Point
; -----------------------------
global _start
extern kernel_main

section .text
_start:
    call kernel_main     ; Springe zu C-Kernel
    cli                  ; Interrupts deaktivieren
    hlt                  ; CPU anhalten
