#include <../include/init/idt.h>
#include <../include/utils.h>
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

/* Helper to set an IDT entry */
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
    /* 1. Clear the entire IDT */
    memset(&idt, 0, sizeof(idt));

    /* 2. Fill first 32 entries (CPU exceptions) */
    create_idt_entry(&idt[0], (uint32_t)isr0, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[1], (uint32_t)isr1, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[2], (uint32_t)isr2, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[3], (uint32_t)isr3, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[4], (uint32_t)isr4, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[5], (uint32_t)isr5, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[6], (uint32_t)isr6, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[7], (uint32_t)isr7, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[8], (uint32_t)isr8, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[9], (uint32_t)isr9, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[10], (uint32_t)isr10, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[11], (uint32_t)isr11, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[12], (uint32_t)isr12, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[13], (uint32_t)isr13, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[14], (uint32_t)isr14, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[15], (uint32_t)isr15, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[16], (uint32_t)isr16, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[17], (uint32_t)isr17, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[18], (uint32_t)isr18, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[19], (uint32_t)isr19, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[20], (uint32_t)isr20, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[21], (uint32_t)isr21, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[22], (uint32_t)isr22, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[23], (uint32_t)isr23, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[24], (uint32_t)isr24, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[25], (uint32_t)isr25, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[26], (uint32_t)isr26, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[27], (uint32_t)isr27, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[28], (uint32_t)isr28, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[29], (uint32_t)isr29, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[30], (uint32_t)isr30, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);
    create_idt_entry(&idt[31], (uint32_t)isr31, 0x08, IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT);

    /* 3. Setup IDT pointer */
    idt_ptr.limit = sizeof(idt) - 1;
    idt_ptr.base = (uint32_t)&idt;

    /* 4. Load the IDT into the CPU */
    load_idt((uint32_t)&idt_ptr);
}

// /* --------------------------------------------------------------------------
//  * Extern ISR stubs (implemented in assembly, e.g., init/isr.s)
//  * -------------------------------------------------------------------------- */
// extern void isr0(void);
// extern void isr1(void);
// extern void isr2(void);
// extern void isr3(void);
// extern void isr4(void);
// extern void isr5(void);
// extern void isr6(void);
// extern void isr7(void);
// extern void isr8(void);
// extern void isr9(void);
// extern void isr10(void);
// extern void isr11(void);
// extern void isr12(void);
// extern void isr13(void);
// extern void isr14(void);
// extern void isr15(void);
// extern void isr16(void);
// extern void isr17(void);
// extern void isr18(void);
// extern void isr19(void);
// extern void isr20(void);
// extern void isr21(void);
// extern void isr22(void);
// extern void isr23(void);
// extern void isr24(void);
// extern void isr25(void);
// extern void isr26(void);
// extern void isr27(void);
// extern void isr28(void);
// extern void isr29(void);
// extern void isr30(void);
// extern void isr31(void);

// /* --------------------------------------------------------------------------
//  * IDT storage and pointer
//  * -------------------------------------------------------------------------- */

// /* IDT array: 256 entries */
// idt_entry_t idt[256];

// /* IDT pointer used by lidt (matches idt_ptr_t from idt.h) */
// static idt_ptr_t idt_ptr;

// /* Forward declare the loader (from header): */
// void load_idt(uint32_t);

// /* --------------------------------------------------------------------------
//  * create_idt_entry
//  *
//  * Fill a single IDT entry given an interrupt handler address (offset),
//  * selector, and the pre-composed type/attribute byte (gate_type_attr).
//  * -------------------------------------------------------------------------- */
// void create_idt_entry(idt_entry_t *entry, uint32_t offset, uint16_t selector, uint8_t gate_type_attr)
// {
//     if (!entry)
//         return;

//     entry->offset_low  = (uint16_t)(offset & 0xFFFF);
//     entry->selector    = selector;
//     entry->zero        = 0;
//     entry->type_attr   = gate_type_attr;
//     entry->offset_high = (uint16_t)((offset >> 16) & 0xFFFF);
// }

// /* --------------------------------------------------------------------------
//  * Helper: compose attribute byte for a standard kernel 32-bit interrupt gate
//  * Present | DPL0 | 32-bit interrupt gate  => IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT
//  * -------------------------------------------------------------------------- */
// #define IDT_KERNEL_INT_ATTR  (IDT_ATTR_PRESENT | IDT_ATTR_DPL0 | IDT_GATE_TYPE_32_INT)

// /* --------------------------------------------------------------------------
//  * idt_init
//  *
//  * Zero the IDT, create entries for exceptions 0..31, and load the IDT.
//  * -------------------------------------------------------------------------- */
// void idt_init(void)
// {
//     /* Clear the entire IDT to start with NULL entries */
//     memset(idt, 0, sizeof(idt));

//     /* Create entries for CPU exceptions (vectors 0..31).
//      * Map each vector i to isri (assembly stub).
//      *
//      * Exception table (vector -> name) -- reference in comments:
//      * 0: Divide Error
//      * 1: Debug
//      * 2: NMI
//      * 3: Breakpoint
//      * 4: Overflow
//      * 5: BOUND Range Exceeded
//      * 6: Invalid Opcode
//      * 7: Device Not Available
//      * 8: Double Fault
//      * 9: Coprocessor Segment Overrun
//      * 10: Invalid TSS
//      * 11: Segment Not Present
//      * 12: Stack-Segment Fault
//      * 13: General Protection Fault
//      * 14: Page Fault
//      * 15: Reserved
//      * 16: x87 Floating-Point Exception
//      * 17: Alignment Check
//      * 18: Machine Check
//      * 19: SIMD Floating-Point Exception
//      * 20: Virtualization Exception
//      * 21: Control Protection Exception
//      * 22..27: Reserved
//      * 28: Hypervisor Injection Exception
//      * 29: VMM Communication Exception
//      * 30: Security Exception
//      * 31: Reserved
//      */

//     /* Populate entries 0..31 */
//     create_idt_entry(&idt[0],  (uint32_t)isr0,  0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[1],  (uint32_t)isr1,  0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[2],  (uint32_t)isr2,  0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[3],  (uint32_t)isr3,  0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[4],  (uint32_t)isr4,  0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[5],  (uint32_t)isr5,  0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[6],  (uint32_t)isr6,  0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[7],  (uint32_t)isr7,  0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[8],  (uint32_t)isr8,  0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[9],  (uint32_t)isr9,  0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[10], (uint32_t)isr10, 0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[11], (uint32_t)isr11, 0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[12], (uint32_t)isr12, 0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[13], (uint32_t)isr13, 0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[14], (uint32_t)isr14, 0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[15], (uint32_t)isr15, 0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[16], (uint32_t)isr16, 0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[17], (uint32_t)isr17, 0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[18], (uint32_t)isr18, 0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[19], (uint32_t)isr19, 0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[20], (uint32_t)isr20, 0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[21], (uint32_t)isr21, 0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[22], (uint32_t)isr22, 0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[23], (uint32_t)isr23, 0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[24], (uint32_t)isr24, 0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[25], (uint32_t)isr25, 0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[26], (uint32_t)isr26, 0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[27], (uint32_t)isr27, 0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[28], (uint32_t)isr28, 0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[29], (uint32_t)isr29, 0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[30], (uint32_t)isr30, 0x08, IDT_KERNEL_INT_ATTR);
//     create_idt_entry(&idt[31], (uint32_t)isr31, 0x08, IDT_KERNEL_INT_ATTR);

//     /* Fill IDT pointer (limit = size - 1) */
//     idt_ptr.limit = (uint16_t)(sizeof(idt) - 1);
//     idt_ptr.base  = (uint32_t)&idt;

//     /* Load IDT into CPU (wrapper around lidt) */
//     load_idt((uint32_t)&idt_ptr);
// }
