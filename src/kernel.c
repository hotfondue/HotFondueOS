#include "../include/kb.h"
#include "../include/isr.h"
#include "../include/idt.h"
#include "../include/util.h"
#include "../include/shell.h"
#include "../include/types.h"
#include "../include/screen.h"
#include "../include/box.h"

int kmain()
{
	isr_install();
	clearScreen();
	//int k=9/0;
        
        init_vga(WHITE, BLACK);
        create_dosbox_ui();
        moveCursor(0,15);
        launch_shell(0);
        //asm volatile ("int $0x3");
	//asm volatile ("int $0x4");
	
	
}
