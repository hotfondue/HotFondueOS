#include "../include/screen.h"
int cursorX = 0, cursorY = 0;
const uint8 sw = 80,sh = 25,sd = 2; 
int color = 0x0F;

void clearLine(uint8 from,uint8 to)
{
        uint16 i = sw * from * sd;
        string vidmem=(string)0xb8000;
        for(i;i<(sw*to*sd);i++)
        {
                vidmem[i] = 0x0;
        }
}

void updateCursor()
{
    uint16 temp = cursorY * sw + cursorX;                              // Position = (y * width) +  x

    outportb(0x3D4, 14);                                        // Tell the VGA board we are setting the high cursor byte
    outportb(0x3D5, temp >> 8);                                 // Send the high byte across the bus
    outportb(0x3D4, 15);                                        // Tell the VGA board we are setting the low cursor byte
    outportb(0x3D5, temp);                                      // Send the low byte of the cursor location
}

void moveCursor(int x, int y)
{
	cursorX = x;
	cursorY= y;
	updateCursor();
}
void clearScreen()
{
        clearLine(0,sh-1);
        cursorX = 0;
        cursorY = 0;
        updateCursor();
}

void scrollUp(uint8 lineNumber)
{
        string vidmem = (string)0xb8000;
        uint16 i = 0;
        clearLine(0,lineNumber-1);                                            //updated
        for (i;i<sw*(sh-1)*2;i++)
        {
                vidmem[i] = vidmem[i+sw*2*lineNumber];
        }
        clearLine(sh-1-lineNumber,sh-1);
        if((cursorY - lineNumber) < 0 ) 
        {
                cursorY = 0;
                cursorX = 0;
        } 
        else 
        {
                cursorY -= lineNumber;
        }
        updateCursor();
}


void newLineCheck()
{
        if(cursorY >=sh-1)
        {
                scrollUp(1);
        }
}

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

void printdec(uint32 n)
{

    if (n == 0)
    {
        print("0");
        return;
    }

    int32 acc = n;
    char c[32];
    int i = 0;
    while (acc > 0)
    {
        c[i] = '0' + acc%10;
        acc /= 10;
        i++;
    }
    c[i] = 0;

    char c2[32];
    c2[i--] = 0;
    int j = 0;
    while(i >= 0)
    {
        c2[i--] = c[j++];
    }
    print(c2);


}

