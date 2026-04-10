# Crosscompiler
CC = i686-elf-gcc
LD = i686-elf-ld
CFLAGS = -m32 -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -Ttext 0x1000 --oformat elf32-i386

all: iso\myos.iso

kernel.bin: src\kernel.c src\boot.asm
	$(CC) $(CFLAGS) -c src\kernel.c -o kernel.o
	nasm -f elf32 src\boot.asm -o boot.o
	$(LD) $(LDFLAGS) -o kernel.bin boot.o kernel.o

# Die ISO-Regel kümmert sich um die gesamte Struktur
iso\myos.iso: kernel.bin
	@if not exist "iso\boot\grub" mkdir "iso\boot\grub"
	copy kernel.bin iso\boot\kernel.bin
	@if exist "boot\grub\grub.cfg" (copy boot\grub\grub.cfg iso\boot\grub\) else (echo Warnung: grub.cfg nicht gefunden!)

clean:
	@del /f /q *.bin *.o 2>NUL
	@if exist iso rd /s /q iso 2>NUL

start:
	qemu-system-i386 -kernel kernel.bin