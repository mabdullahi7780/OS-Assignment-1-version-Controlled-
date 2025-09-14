/*******************************************************************************
 * 
 * @file    isr.s
 * @brief   Assembly stubs for CPU exceptions and interrupts
 * 
 *******************************************************************************/

KERNEL_CODE_SEGMENT = 0x08      /* Kernel code segment offset in the GDT */
KERNEL_DATA_SEGMENT = 0x10      /* Kernel data segment offset in the GDT */

.extern interrupt_dispatch   /* Declare the external C handler for ISRs */

/* ---------------------------------------------------------------------------
 * Common ISR handler
 * --------------------------------------------------------------------------- */
.globl isr_common_handler
.type isr_common_handler, @function
isr_common_handler:
    pusha                # save eax, ecx, edx, ebx, esp, ebp, esi, edi
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs

    mov $0x10, %ax       # load kernel data segment selector
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    pushl %esp           # push pointer to interrupt_context_t
    call interrupt_dispatch
    addl $4, %esp        # clean up param

    popl %gs
    popl %fs
    popl %es
    popl %ds
    popa

    addl $8, %esp        # pop error_code and int_no
    iret


/* ---------------------------------------------------------------------------
 * Macros to define ISR stubs
 * --------------------------------------------------------------------------- */

/* ISR without error code (CPU does not push an error code) */
.macro ISR_NOERR num
    .globl isr\num
isr\num:
    pushl $0          /* dummy error code */
    pushl $\num       /* int_no */
    jmp isr_common_handler
.endm

/* ISR with error code (CPU already pushed error code) */
.macro ISR_ERR num
    .globl isr\num
isr\num:
    pushl $\num       /* int_no */
    jmp isr_common_handler
.endm


/* ---------------------------------------------------------------------------
 * Define ISRs 0..31 (CPU exceptions from Table 4)
 * --------------------------------------------------------------------------- */
ISR_NOERR 0    /* Divide Error */
ISR_NOERR 1    /* Debug */
ISR_NOERR 2    /* NMI Interrupt */
ISR_NOERR 3    /* Breakpoint */
ISR_NOERR 4    /* Overflow */
ISR_NOERR 5    /* BOUND Range Exceeded */
ISR_NOERR 6    /* Invalid Opcode */
ISR_NOERR 7    /* Device Not Available */
ISR_ERR   8    /* Double Fault */
ISR_NOERR 9    /* Coprocessor Segment Overrun */
ISR_ERR   10   /* Invalid TSS */
ISR_ERR   11   /* Segment Not Present */
ISR_ERR   12   /* Stack-Segment Fault */
ISR_ERR   13   /* General Protection Fault */
ISR_ERR   14   /* Page Fault */
ISR_NOERR 15   /* Reserved */
ISR_NOERR 16   /* x87 Floating-Point Exception */
ISR_ERR   17   /* Alignment Check */
ISR_NOERR 18   /* Machine Check */
ISR_NOERR 19   /* SIMD Floating-Point Exception */
ISR_NOERR 20   /* Virtualization Exception */
ISR_ERR   21   /* Control Protection Exception */
ISR_NOERR 22   /* Reserved */
ISR_NOERR 23   /* Reserved */
ISR_NOERR 24   /* Reserved */
ISR_NOERR 25   /* Reserved */
ISR_NOERR 26   /* Reserved */
ISR_NOERR 27   /* Reserved */
ISR_NOERR 28   /* Hypervisor Injection Exception */
ISR_NOERR 29   /* VMM Communication Exception */
ISR_ERR   30   /* Security Exception */
ISR_NOERR 31   /* Reserved */
