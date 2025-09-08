#Crosscompiler

CC=i686-elf-gcc
LD=i686-elf-ld
CFLAGS=-m32 -ffreestanding -O2 -Wall -Wextra
LDFLAGS=-Ttext 0x1000 --oformat elf32-i386

all: iso/myos.iso
kernel.bin: src/kernel.c src/boot.s 
	$(CC) $(CFLAGS) -c src/kernel.c -o kernel.o
	nasm -f elf32 src/boot.asm -o boot.o
	$(LD) $(LDFLAGS) -o kernel.bin boot.o kernel.o
	mkdir -p iso/boot
	cp kernel.bin iso/boot/

iso/myos.iso: kernel.bin
	mkdir -p iso/boot/grub
	cp boot/grub/grub.cfg iso/boot/grub/
	grub-mkrescue -o iso/myos.iso iso

clean:
	rm -rf *.bin *.o iso
