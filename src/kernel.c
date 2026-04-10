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

unsinged char create_color(vga_color background, vga_color foreground){
  return (background << 4) | foreground
}


void clear_screen() {
  char *video_memory = (char *)0xB8000;
  unsigned char colors = create_color(VGA_COLOR_BLACK, VGA_COLOR_GREEN) 
  
    // Screen is 80 Cols and 25 rows
    for (int i = 0; i < 80 * 25; i++) {  // 80 Spalten x 25 Zeilen
        video_memory[i*2] = ' ';         // Leerzeichen
        video_memory[i*2 + 1] = colors;  // FARBEN 
    }
}

void write_hello(){
  const char *str = "Hello, World!";
  unsigned char colors = create_color(VGA_COLOR_BLACK, VGA_COLOR_GREEN) 

  char *video_memory = (char*)0xb8000; //Textmode video RAM
  for (int i=0; str[i] != '\0'; i++){
    video_memory[i*2] = str[i];
    video_memory[i*2+1] = colors;
  }
}


void kernel_main(){
  clear_screen();
  write_hello();
  
  while(1){}
}
