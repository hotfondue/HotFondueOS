#include "../include/print.h"

void printch(char c)
{   
    string vidmem = (string) 0xb8000;
    switch(c)
    {
        case (0x08):
                if(cursorX > 0) 
                {
	                cursorX--;									
                        vidmem[(cursorY * sw + cursorX)*sd]=0x00;	                              
	        }
	        break;
       case (0x09):
                cursorX = (cursorX + 8) & ~(8 - 1);     // Handle a tab by increasing the cursors X, but only to a point
   		break;					// where it is divisible by 8.
        case ('\r'):
                cursorX = 0;				//Handle carriage return
                break;
        case ('\n'):
                cursorX = 0;
                cursorY++;
                break;
        default:
                vidmem [((cursorY * sw + cursorX))*sd] = c;
                vidmem [((cursorY * sw + cursorX))*sd+1] = color;
                cursorX++; 
                break;
	
    }
    if(cursorX >= sw)                                                                   
    {
        cursorX = 0;                                                                
        cursorY++;                                                                    
    }
    
    newLineCheck();
    updateCursor();
}

void print (string ch)
{
        uint16 i = 0;
        uint8 length = strlength(ch);
        for(i;i<length;i++)
        {
                printch(ch[i]);
        }
         updateCursor();
        
}
void set_screen_color(int text_color,int bg_color)
{
	
	color =  (bg_color << 4) | text_color;
	
	
}

void print_colored(string ch,int text_color,int bg_color)
{
	int current_color = color;
	set_screen_color(text_color,bg_color);
	print(ch);
	color= current_color;
}


void create_dosbox_ui()
{
  fill_box(0, 0, 0, BOX_MAX_WIDTH - 8, 14, BLUE);
  draw_box(BOX_DOUBLELINE, 0, 0, BOX_MAX_WIDTH - 10, 12, WHITE, BLUE);

  moveCursor(2, 1);
  print_colored("Welcome to HotFondue-x32 v1.0.0", LIGHT_GREEN, BLUE);
 
  moveCursor(2, 4);
  print_colored("For supported shell commands: ", WHITE, BLUE);
  
  moveCursor(32, 4);
  print_colored("HELP", YELLOW, BLUE);

  moveCursor(2, 6);
  print_colored("For more information read kernel source code", WHITE, BLUE);
  
  moveCursor(2, 9);
  print_colored("HAVE FUN!", LIGHT_GREEN, BLUE);

  moveCursor(2, 11);
  print_colored("Author:",LIGHT_GREEN, BLUE);

  moveCursor(10, 11);
  print_colored("Zainab Siamwala, 185055", LIGHT_GREEN, BLUE);


}
