#ifndef SCREEN_H
#define SCREEN_H
#include "system.h"
#include "string.h"
#include "types.h"

extern int cursorX , cursorY;
extern const uint8 sw ,sh ,sd ;                  //We define the screen width, height, and depth.

enum colors {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    GREY,
    DARK_GREY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_MAGENTA,
    YELLOW,
    WHITE,
};

void clearLine(uint8 from,uint8 to);

void updateCursor();

void moveCursor(int x, int y);

void clearScreen();

void scrollUp(uint8 lineNumber);

void newLineCheck();

void printch(char c);

void print(string ch);

void set_screen_color(int text_color,int bg_color);
void set_screen_color_from_color_code(int color_code);
void print_colored(string ch,int text_color,int bg_color);

void printdec(uint32 n);

#endif
