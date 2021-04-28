#ifndef ISR_H
#define ISR_H

// isr.h -- Interface and structures for high level interrupt service routines.

#include "types.h"
#include "screen.h"
#include "system.h"

typedef struct registers
{
    uint32 ds;                  // Data segment selector
    uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
    uint32 int_no, err_code;    // Interrupt number and error code (if applicable)
    uint32 eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} registers_t;

typedef void (*isr_t)(registers_t);
void register_interrupt_handler(uint8 n, isr_t handler);

#endif
