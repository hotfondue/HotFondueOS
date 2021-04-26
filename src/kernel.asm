bits	32
section		.text
	align	4
	dd	0x1BADB002
	dd	0x00
	dd	- (0x1BADB002+0x00)
	
global start
extern kmain		;this fx is gonna be located in kernel.c
start:
	cli		;clears interrupts
	call kmain	
	hlt		;halts the cpu ie pause it from executing from this address
