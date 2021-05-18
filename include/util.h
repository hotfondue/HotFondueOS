#ifndef UTIL_H
#define UTIL_H

#include "types.h"
#include "string.h"
#include "screen.h"
#include "kheap.h"

void memory_copy(char *source, char *dest, int nbytes);
void memory_set(uint8 *dest, uint8 val, uint32 len);
void int_to_ascii(int n, string str);  
int str_to_int(string ch);
string int_to_string(int n); 

#define PANIC(msg) panic(msg, __FILE__, __LINE__);
#define ASSERT(b) ((b) ? (void)0 : panic_assert(__FILE__, __LINE__, #b))

extern void panic(const char *message, const char *file, uint32 line);
extern void panic_assert(const char *file, uint32 line, const char *desc);    

#endif
