#include "../include/kb.h"
#include "../include/dt.h"
#include "../include/util.h"
#include "../include/shell.h"
#include "../include/types.h"
#include "../include/screen.h"
#include "../include/system.h"
#include "../include/box.h"
#include "../include/timer.h"
#include "../include/paging.h"

int kmain()
{
	init_descriptor_tables();
	clearScreen();
        //init_timer(50000);
        init_timer(50);
        initialise_paging();
        //uint32 *ptr = (uint32*)0xA0000000;		//-> call page fault
        //uint32 do_page_fault = *ptr;
        
        init_vga(WHITE, BLACK);
        create_dosbox_ui();
        moveCursor(0,15);
        launch_shell(0);
        
        //int k=9/0;
        
        //asm volatile ("int $0x3");			//-> call normal interrupt
	//asm volatile("sti");				//-> call timer interrupt
	
	
	return 0;
}
