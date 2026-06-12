#include <stdint.h>

// Ein GDT-Eintrag (8 Bytes)
struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t  base_middle;
    uint8_t  access;
    uint8_t  granularity;
    uint8_t  base_high;
} __attribute__((packed));

// Der GDT-Pointer (6 Bytes)
struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

// Wir brauchen 3 Einträge: Null, Code, Daten
volatile struct gdt_entry gdt[3];
volatile struct gdt_ptr gdt_p;

// Diese Funktion schreiben wir gleich in Assembly!
extern void gdt_flush(uint32_t gdt_ptr_address);

// Hilfsfunktion zum Befüllen eines Eintrags
void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt[num].base_low    = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high   = (base >> 24) & 0xFF;

    gdt[num].limit_low   = (limit & 0xFFFF);
    gdt[num].granularity = (limit >> 16) & 0x0F;
    gdt[num].granularity |= gran & 0xF0;
    gdt[num].access      = access;
}

void init_gdt() {
    gdt_p.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gdt_p.base  = (uint32_t)&gdt;

    // 1. Der obligatorische Null-Eintrag
    gdt_set_gate(0, 0, 0, 0, 0);

    // 2. Kernel Code Segment (Basis 0, Limit 4GB)
    // Access 0x9A: Vorhanden, Ring 0, ausführbar, lesbar
    // Granularity 0xCF: 4KB-Schritte (wichtig für 4GB Limit), 32-Bit Modus
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    // 3. Kernel Daten Segment (Basis 0, Limit 4GB)
    // Access 0x92: Vorhanden, Ring 0, schreibbar, lesbar
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    // Übergib die Adresse unseres GDT-Pointers an die Assembly-Funktion
    gdt_flush((uint32_t)&gdt_p);
}