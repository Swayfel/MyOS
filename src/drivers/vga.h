#ifndef VGA_H
#define VGA_H

#include <stdint.h>

enum vga_color{
  VGA_COLOR_BLACK = 0,
  VGA_COLOR_BLUE = 1,
  VGA_COLOR_GREEN = 2,
  VGA_COLOR_CYAN = 3,
  VGA_COLOR_RED = 4,
  VGA_COLOR_MAGENTA = 5,
  VGA_COLOR_BROWN = 6,
  VGA_COLOR_LIGHT_GREY = 7,
  VGA_COLOR_DARK_GREY = 8,
  VGA_COLOR_LIGHT_BLUE = 9,
  VGA_COLOR_LIGHT_GREEN = 0xA,
  VGA_COLOR_LIGHT_CYAN = 0xB,
  VGA_COLOR_LIGHT_RED = 0xC,
  VGA_COLOR_LIGHT_MAGENTA = 0xD,
  VGA_COLOR_YELLOW = 0xE,
  VGA_COLOR_WHITE = 0xF
};

void initialize_terminal();
unsigned char create_color(uint8_t background, uint8_t foreground);
void put_char(char c);
void write(const char* data, int size);

#endif