/**
 * @file interrupts.h
 * @author Abdul Rafay (abdul.rafay@lums.edu.pk)
 * @brief Provides the interface to setup and manage interrupts in the x86 architecture. This includes defining the interrupt context, registering interrupt handlers, and setting up the IDT (Interrupt Descriptor Table) and PIC (Programmable Interrupt Controller).
 * @version 0.1
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef _SYS_INTERRUPTS_H
#define _SYS_INTERRUPTS_H

#include <stdint.h>
#include <utils.h>
/**
 * @brief Represents the context/state before servicing an interrupt. Note that this context is saved by the routine called `isr_common_handler` from the file `isr.s`, which is the common handler for all interrupts.
 * The order of the fields in this structure is important, as it matches the order in which the registers are pushed onto the stack by the `isr_common_handler` routine. Note that x86 calling convention dictates parameters are pushed onto the stack in reverse order, so the first parameter is pushed last.
 *
 */
struct interrupt_context
{
    // /* Pushed by pusha */
    // uint32_t edi;
    // uint32_t esi;
    // uint32_t ebp;
    // uint32_t esp_dummy; // value of esp at pusha time (ignore)
    // uint32_t ebx;
    // uint32_t edx;
    // uint32_t ecx;
    // uint32_t eax;

    // /* Pushed manually (segment registers) */
    // uint32_t gs;
    // uint32_t fs;
    // uint32_t es;
    // uint32_t ds;

    // /* Pushed by our ISR stubs */
    // uint32_t err_code;
    // uint32_t int_no;

    // /* Pushed automatically by the CPU */
    // uint32_t eip;
    // uint32_t cs;
    // uint32_t eflags;
    // /* If the interrupt came from user mode, CPU also pushes: */
    // uint32_t useresp;
    // uint32_t ss;

    uint32_t gs, fs, es, ds;                         // pushed in isr_common_handler
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // pusha
    uint32_t err_code;                               // pushed first by ISR macros / CPU
    uint32_t int_no;                                 // pushed second by ISR macros
    uint32_t eip, cs, eflags, useresp, ss;           // pushed by CPU
};

typedef struct interrupt_context interrupt_context_t;

/**
 * @brief Defines the standard interface used by the interrupt handlers setup by the kernel for each PIC device type maybe. After setting up the context, the generic irq stub should pass the control and context to the corresponding ISR. Update: should be pointer to the context structure.
 *
 */
typedef void (*interrupt_service_t)(interrupt_context_t *);

/* This is a standard assignment of IRQ pins to the hardware devices in the
    original PC AT. QEMU simulates that. */

//! defines for the IRQs and interrupt numbers
#define IRQ0_TIMER 32        // Timer interrupt
#define IRQ1_KEYBOARD 33     // Keyboard interrupt
#define IRQ3_SERIAL2 35      // Serial port 2 interrupt
#define IRQ4_SERIAL1 36      // Serial port 1 interrupt
#define IRQ5_PARALLEL2 37    // Parallel port 2 interrupt
#define IRQ6_FLOPPY 38       // Floppy disk controller interrupt
#define IRQ7_PARALLEL1 39    // Parallel port 1 interrupt
#define IRQ8_CMOSRTC 40      // CMOS real-time clock interrupt
#define IRQ9_CGA_VRETRACE 41 // CGA vertical retrace
#define IRQ13_FPU 45         // Floating Point Unit
#define IRQ14_HDC 46         // Hard Disk Controller

//! software generated interrupt for the system call
#define ISR128_SYSCALL 0x80 // syscall interrupt

void interrupt_dispatch(interrupt_context_t *context);
void register_interrupt_handler(uint8_t int_no, interrupt_service_t routine);

void unregister_interrupt_handler(uint8_t int_no);
interrupt_service_t get_interrupt_handler(uint8_t int_no);
void setup_x86_interrupts();
#endif // !_SYS_INTERRUPTS_H
