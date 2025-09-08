// Screen is 80 Cols and 25 rows

void clear_screen() {
    char *video_memory = (char *)0xB8000;
    unsigned char blank = 0x07; // weiß auf schwarz

    for (int i = 0; i < 80 * 25; i++) {  // 80 Spalten x 25 Zeilen
        video_memory[i*2] = ' ';         // Leerzeichen
        video_memory[i*2 + 1] = blank;   // Farbe
    }
}

void write_hello(){
  const char *str = "Hello, World!";
  char *video_memory = (char*)0xb8000; //Textmode video RAM
  for (int i=0; str[i] != '\0'; i++){
    video_memory[i*2] = str[i];
    video_memory[i*2+1] = 0x07;
  }
}


void kernel_main(){
  clear_screen();
  write_hello();
  
  while(1){}
}
