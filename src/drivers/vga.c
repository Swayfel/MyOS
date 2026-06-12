#include "vga.h"
#include <stddef.h>

static char* video_memory = (char*)0xB8000;
static size_t terminal_row;
static size_t terminal_col;
static unsigned char terminal_color;
const int TERMINAL_MAX_WIDTH = 80;
const int TERMINAL_MAX_HEIGHT = 25;

void initialize_terminal(){
    terminal_color = create_color(VGA_COLOR_BLACK, VGA_COLOR_GREEN); 
    terminal_row = 0;
    terminal_col = 0;
  
    // Screen is 80 Cols and 25 rows
    for (int i = 0; i < TERMINAL_MAX_WIDTH * TERMINAL_MAX_HEIGHT; i++) {  // 80 Spalten x 25 Zeilen
        video_memory[i*2] = ' ';         // Leerzeichen
        video_memory[i*2 + 1] = terminal_color;  // FARBEN 
    }
}

unsigned char create_color(uint8_t background, uint8_t foreground){
    return (background << 4) | foreground;
}

void put_char(char c){
    video_memory[terminal_col*2] = c;
    video_memory[terminal_col*2+1] = terminal_color;

    terminal_col++;
}

void write(const char* data, int size){
    for (int i =  0; i < size; i++){
        put_char(data[i]);
    }
}