#include <../include/init/idt.h>
#include <../include/utils.h>
#include <../tests/testmain.h>
#include <stdint.h>
#include <string.h>

// The IDT: 256 entries
static idt_entry_t idt[256];
static idt_ptr_t idt_ptr;

// Assembly ISR stubs (from isr.s)
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

// Table of ISR stubs for exceptions 0–31
void (*isr_table[32])() = {
    isr0,  isr1,  isr2,  isr3,
    isr4,  isr5,  isr6,  isr7,
    isr8,  isr9,  isr10, isr11,
    isr12, isr13, isr14, isr15,
    isr16, isr17, isr18, isr19,
    isr20, isr21, isr22, isr23,
    isr24, isr25, isr26, isr27,
    isr28, isr29, isr30, isr31
};

// Set the IDT entry
void create_idt_entry(idt_entry_t *entry, uint32_t offset, uint16_t selector, uint8_t gate_type_attr)
{
    if (!entry)
    {
        return;
    }
    entry->offset_low = offset & 0xFFFF;
    entry->selector = selector;
    entry->zero = 0;
    entry->type_attr = gate_type_attr;
    entry->offset_high = (offset >> 16) & 0xFFFF;
}

void idt_init()
{
    memset(&idt, 0, sizeof(idt));

    for (int i = 0; i < 32; i++) {
        create_idt_entry(&idt[i], (uint32_t)isr_table[i], 0x08,IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    }

    // Add debug for interrupt 3 specifically
    // send_msg("DEBUG: IDT entry 3 created\n");

    idt_ptr.limit = sizeof(idt) - 1;
    idt_ptr.base = (uint32_t)&idt;

    load_idt((uint32_t)&idt_ptr);
    // send_msg("DEBUG: IDT loaded\n");
}