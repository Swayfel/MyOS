global gdt_flush          ; Macht die Funktion für C sichtbar
extern gdt_p

gdt_flush:
    lgdt [gdt_p]            ; Lade die GDT in die CPU

    ; Jetzt müssen wir die Daten-Register aktualisieren.
    ; Wir laden den Selektor 0x10 (Eintrag 2 * 8 Bytes) in alle Datensegmente.
    mov ax, 0x10          
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Das Code-Segment (CS) kann man nicht mit "mov" beschreiben.
    ; Man MUSS einen "Far Jump" (weiten Sprung) machen, um CS zu ändern.
    ; 0x08 ist der Selektor für unseren Kernel Code (Eintrag 1 * 8 Bytes).
    jmp 0x08:.complete_flush

.complete_flush:
    ret                   ; Zurück zum C-Code