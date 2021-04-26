#ifndef BOX_H
#define BOX_H

#include "types.h"
#include "screen.h"

#define NULL 0

#define VGA_ADDRESS 0xB8000
#define BUFSIZE 2200

extern uint16* vga_buffer;

#define VGA_MAX_WIDTH 80
#define VGA_MAX_HEIGHT 25

#define BOX_MAX_WIDTH 78
#define BOX_MAX_HEIGHT 23

#define BOX_SINGLELINE 1
#define BOX_DOUBLELINE 2

void init_vga(uint8 fore_color, uint8 back_color);

void fill_box(uint8 ch, uint16 x, uint16 y, uint16 width, uint16 height, uint8 color);

void create_dosbox_ui();


#endif
