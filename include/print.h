#ifndef PRINT_H
#define PRINT_H

//a comniation of box and screen

#include "types.h"
#include "box.h"
#include "screen.h"


void printch(char c);

void print(string ch);

void set_screen_color_from_color_code(int color_code);
void print_colored(string ch,int text_color,int bg_color);

void create_dosbox_ui();

#endif
