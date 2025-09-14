// Setup interrupts
// Register
// Unregister
// Dispatch


// #include<include/interrupts.h>
// #include<include/utils.h>



#include <stdint.h>
#include <stddef.h>
#include <../include/interrupts.h>   // for interrupt_context_t, interrupt_service_t
#include <../include/init/idt.h>          // for idt_init()
#include <../include/driver/pic.h>        // for pic_init(), pic_send_eoi()
#include <../include/utils.h>       // for sti()
/*******************************************************************************
 * @file    interrupts.c
 * @brief   High-level interrupt management for x86
 *
 * This file contains the interrupt dispatcher and functions for registering,
 * unregistering, and retrieving interrupt handlers. It also sets up the
 * interrupt system by initializing the PIC and the IDT, then enabling interrupts.
 *******************************************************************************/

extern int kprintf(const char *fmt, ...); // adjust if your kernel uses a different print

/* ---------------------------------------------------------------------------
 * Global handler table
 * --------------------------------------------------------------------------- */
static interrupt_service_t interrupt_handlers[256];

/* ---------------------------------------------------------------------------
 * interrupt_dispatch
 * Called from isr_common_handler (assembly).
 * --------------------------------------------------------------------------- */
// void interrupt_dispatch(interrupt_context_t *context)
// {
//     uint8_t int_no = context->int_no;

//     interrupt_service_t handler = interrupt_handlers[int_no];
//     if (handler != NULL) {
//         handler(context);   // handler sees the same context as the kernel
//     } else {
//         // kprintf("Unhandled interrupt: %d\n", int_no);
//     }

//     if (int_no >= 32 && int_no <= 47) {
//         pic_send_eoi(int_no);
//     }
// }
void interrupt_dispatch(interrupt_context_t *context)
{
    /* Defensive: null check */
    if (!context) {
        kprintf("[INT] interrupt_dispatch called with NULL context\n");
        return;
    }

    uint32_t saved_err = context->err_code;   /* for debugging */
    uint32_t int_no = context->int_no;

    /* Debug: print immediately so we know dispatcher was entered and what int_no is */
    kprintf("[INT] dispatch entered: int_no=%u err=%u\n", (unsigned)int_no, (unsigned)saved_err);

    /* Look up handler */
    interrupt_service_t handler = interrupt_handlers[int_no];
    if (handler) {
        kprintf("[INT] found handler for %u -> calling\n", (unsigned)int_no);
        handler(context);   /* Call the registered handler */
        kprintf("[INT] handler for %u returned\n", (unsigned)int_no);
    } else {
        kprintf("[INT] no handler registered for %u\n", (unsigned)int_no);
    }

    /* PIC EOI for hardware IRQs */
    if (int_no >= 32 && int_no <= 47) {
        pic_send_eoi(int_no);
        kprintf("[INT] sent EOI for %u\n", (unsigned)int_no);
    }

    /* Extra flush or NOP may help; not required */
}
/* ---------------------------------------------------------------------------
 * register_interrupt_handler
 * Register a handler function for a given interrupt vector.
 * --------------------------------------------------------------------------- */
void register_interrupt_handler(uint8_t int_no, interrupt_service_t routine)
{
    if (int_no < 256) {
        interrupt_handlers[int_no] = routine;
    }
}

/* ---------------------------------------------------------------------------
 * unregister_interrupt_handler
 * Remove a handler function for a given interrupt vector.
 * --------------------------------------------------------------------------- */
void unregister_interrupt_handler(uint8_t int_no)
{
    if (int_no < 256) {
        interrupt_handlers[int_no] = NULL;
    }
}


/* ---------------------------------------------------------------------------
 * get_interrupt_handler
 * Retrieve the handler for a given interrupt vector.
 * --------------------------------------------------------------------------- */
interrupt_service_t get_interrupt_handler(uint8_t int_no)
{
    if (int_no < 256) {
        return interrupt_handlers[int_no];
    }
    return NULL;
}

/* ---------------------------------------------------------------------------
 * setup_x86_interrupts
 * Initialize the entire x86 interrupt system.
 * --------------------------------------------------------------------------- */
void setup_x86_interrupts()
{
    /* Clear the handler table */
    for (int i = 0; i < 256; i++) {
        interrupt_handlers[i] = NULL;
    }

    /* Initialize the PIC with standard remapping: 
       master at 0x20 (32), slave at 0x28 (40) */
    pic_init(0x20, 0x28);

    /* Initialize the IDT (exceptions 0–31) */
    idt_init();

    /* Enable global interrupts */
    sti();
}