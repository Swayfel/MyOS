#include "drivers/vga.h"

void kernel_main(){
     initialize_terminal();

     write("Hello World!\n", 10);

     while(1){}
}
