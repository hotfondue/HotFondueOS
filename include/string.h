#ifndef STRING_H
#define STRING_H

#include "types.h"
uint16 strlength(string ch);

uint8 strEql(string ch1,string ch2);

void memcpy(uint8 *dest, const uint8 *src, uint32 len);

void memset(uint8 *dest, uint8 val, uint32 len);

#endif
