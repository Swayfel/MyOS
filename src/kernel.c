#include "drivers/vga.h"

extern void init_gdt();

void kernel_main(){
     initialize_terminal();

     write_string("GDT laden...\n");
     init_gdt();
     write_string("[OK] GDT geladen!\n");

     write_string("[OK] Kernel erfolgreich gestartet");

     while(1){}
}
