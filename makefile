COMPILER = gcc
LINKER = ld
ASSEMBLER = nasm
CFLAGS = -m32 -c -ffreestanding
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T src/link.ld
EMULATOR = qemu-system-x86_64
EMULATOR_FLAGS = -kernel

OBJS = obj/kasm.o obj/gdt.o obj/interrupt.o obj/dt.o obj/isr.o obj/timer.o obj/ord_array.o obj/kheap.o obj/paging.o obj/kc.o obj/kb.o obj/screen.o obj/string.o obj/system.o obj/util.o obj/box.o obj/shell.o 
OUTPUT = hotfondue/boot/kernel.bin

run: all
	$(EMULATOR) $(EMULATOR_FLAGS) $(OUTPUT)

all:$(OBJS)
	mkdir hotfondue/ -p
	mkdir hotfondue/boot/ -p
	$(LINKER) $(LDFLAGS) -o $(OUTPUT) $(OBJS)
	
obj/gdt.o:src/gdt.asm
	$(ASSEMBLER) $(ASFLAGS) -o obj/gdt.o src/gdt.asm

obj/string.o:src/string.c
	$(COMPILER) $(CFLAGS) src/string.c -o obj/string.o

obj/system.o:src/system.c
	$(COMPILER) $(CFLAGS) src/system.c -o obj/system.o

obj/screen.o:src/screen.c
	$(COMPILER) $(CFLAGS) src/screen.c -o obj/screen.o
	
obj/kb.o:src/kb.c
	$(COMPILER) $(CFLAGS) src/kb.c -o obj/kb.o

obj/util.o:src/util.c
	$(COMPILER) $(CFLAGS) src/util.c -o obj/util.o
	
obj/interrupt.o:src/interrupt.asm
	$(ASSEMBLER) $(ASFLAGS) -o obj/interrupt.o src/interrupt.asm	
	
obj/isr.o:src/isr.c
	$(COMPILER) $(CFLAGS) src/isr.c -o obj/isr.o
	
obj/dt.o:src/dt.c
	$(COMPILER) $(CFLAGS) src/dt.c -o obj/dt.o 
	
obj/timer.o:src/timer.c
	$(COMPILER) $(CFLAGS) src/timer.c -o obj/timer.o 

obj/ord_array.o:src/ord_array.c
	$(COMPILER) $(CFLAGS) src/ord_array.c -o obj/ord_array.o

obj/kheap.o:src/kheap.c
	$(COMPILER) $(CFLAGS) src/kheap.c -o obj/kheap.o
	
obj/paging.o:src/paging.c
	$(COMPILER) $(CFLAGS) src/paging.c -o obj/paging.o

obj/box.o:src/box.c
	$(COMPILER) $(CFLAGS) src/box.c -o obj/box.o
	
obj/shell.o:src/shell.c
	$(COMPILER) $(CFLAGS) src/shell.c -o obj/shell.o

obj/kasm.o:src/kernel.asm
	$(ASSEMBLER) $(ASFLAGS) -o obj/kasm.o src/kernel.asm
	
obj/kc.o:src/kernel.c
	$(COMPILER) $(CFLAGS) src/kernel.c -o obj/kc.o 
	

build:all
	#Activate the install xorr if you do not have it already installed
	#sudo apt-get install xorriso
	rm hotfondue/boot/grub/ -r -f
	mkdir hotfondue/boot/grub/
	echo set default=0 >> hotfondue/boot/grub/grub.cfg
	echo set timeout=0 >> hotfondue/boot/grub/grub.cfg
	echo menuentry "HotFondue" { >> hotfondue/boot/grub/grub.cfg
	echo         set root='(hd96)' >> hotfondue/boot/grub/grub.cfg
	echo         multiboot /boot/kernel.bin >> hotfondue/boot/grub/grub.cfg
	echo } >> hotfondue/boot/grub/grub.cfg

	grub-mkrescue -o os.iso hotfondue/
	
clear:
	rm -f obj/*.o
	rm -r -f hotfondue/
	
