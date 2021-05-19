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
        
        //1. Testing interrupts
        //a.
        //int k=9/0;
        //b.
        //asm volatile ("int $0x3");            
        
        //2. Testing timer interrupt
        //init_timer(50000);
        //asm volatile("sti");	

	//3. Testing page faults
	/*
    	initialise_paging();
    	print("Testing page faults \n\n");
    	uint32 *ptr = (uint32*)0xA0000000;        
      	uint32 do_page_fault = *ptr;            
    	*/
    	
    	//4.Testing paging+heap
    	/*
    	uint32 a = kmalloc(8);
    	initialise_paging();
    	uint32 b = kmalloc(8);
    	uint32 c = kmalloc(8);
    	print("a: ");
    	printhex(a);
    	print(", b: ");
    	printhex(b);
    	print("\nc: ");
    	printhex(c);
    
    
    	kfree(c);
    	kfree(b);
    	uint32 d = kmalloc(12);
    	print(", d: ");
    	printhex(d); 
    	*/
    
    	//5.Testing shell
    	
    	while(1){
    		uint32 m=login();
    		if(m==1){
    			init_timer(50);	//initialise timer to 50Hz
    			init_vga(WHITE, BLACK);
    			create_dosbox_ui();
    			moveCursor(0,15);
    			launch_shell(0);
    		}
    	}
    	
        
    return 0;
}
