#include "../include/isr.h"

// isr.c -- High level interrupt service routines and interrupt request handlers.

string exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t regs)
{
    print("unhandled interrupt:");
    print("\n0x");
    printdec(regs.int_no);
    printch(' ');
    print(exception_messages[regs.int_no]);
     printdec(tick++);
    printch('\n');
    if (regs.int_no >= IRQ_MASTER_0) {
        if (regs.int_no >= IRQ_SLAVE_0)
            outportb(PIC_SLAVE_CMD, PIC_CMD_RESET);
        outportb(PIC_MASTER_CMD, PIC_CMD_RESET);
    }
}
