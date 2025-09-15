#include <../include/interrupts.h>
#include <../include/init/idt.h>
#include <../include/driver/pic.h>
#include <../include/utils.h>
#include <../tests/testmain.h>
/*******************************************************************************
 * @file    interrupts.c
 * @brief   High-level interrupt management for x86
 *
 * This file contains the interrupt dispatcher and functions for registering,
 * unregistering, and retrieving interrupt handlers. It also sets up the
 * interrupt system by initializing the PIC and the IDT, then enabling interrupts.
 *******************************************************************************/

/* ---------------------------------------------------------------------------
 * Global handler table
 * --------------------------------------------------------------------------- */
static interrupt_service_t interrupt_handlers[256];

/* ---------------------------------------------------------------------------
 * interrupt_dispatch
 * Called from isr_common_handler (assembly).
 * --------------------------------------------------------------------------- */

void interrupt_dispatch(interrupt_context_t *context)
{
//    send_msg("F");  // Entered dispatch
    
    uint8_t int_no = context->int_no;

    interrupt_service_t handler = interrupt_handlers[int_no];
    if (handler != NULL)
    {
        // send_msg("G");  // About to call handler
        handler(context);
        // send_msg("H");  // Handler returned
    }
    else
    {
        // send_msg("I");  // No handler found
    }

    if (int_no >= 32 && int_no <= 47)
    {
        pic_send_eoi(int_no);
    }
    
    // send_msg("J");  // About to return from dispatch
}


/* ---------------------------------------------------------------------------
 * register_interrupt_handler
 * Register a handler function for a given interrupt vector.
 * --------------------------------------------------------------------------- */
void register_interrupt_handler(uint8_t int_no, interrupt_service_t routine)
{
    if (int_no < 256)
    {
        interrupt_handlers[int_no] = routine;
    }
}

/* ---------------------------------------------------------------------------
 * unregister_interrupt_handler
 * Remove a handler function for a given interrupt vector.
 * --------------------------------------------------------------------------- */
void unregister_interrupt_handler(uint8_t int_no)
{
    if (int_no < 256)
    {
        interrupt_handlers[int_no] = NULL;
    }
}

/* ---------------------------------------------------------------------------
 * get_interrupt_handler
 * Retrieve the handler for a given interrupt vector.
 * --------------------------------------------------------------------------- */
interrupt_service_t get_interrupt_handler(uint8_t int_no)
{
    if (int_no < 256)
    {
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
    for (int i = 0; i < 256; i++)
    {
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
