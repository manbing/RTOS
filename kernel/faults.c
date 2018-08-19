#include <kernel/thread.h>
#include <kernel/kernel.h>
#include "platform.h"

void dump_frame(struct kernel_context_regs *noscratch,
                struct thread_context_regs *scratch,
                u32 exc_return)
{
        printk(" r0: %08x       r1: %08x        r2: %08x        r3: %08x\n",
                scratch->r0_r3__r12[0], scratch->r0_r3__r12[1],
                scratch->r0_r3__r12[2], scratch->r0_r3__r12[3]);
        printk(" r4: %08x       r5: %08x        r6: %08x        r7: %08x\n",
                noscratch->r4_r12[0], noscratch->r4_r12[1], noscratch->r4_r12[2],
                noscratch->r4_r12[3]);
        printk(" r8: %08x       r9: %08x        r10: %08x        r11: %08x\n",
                noscratch->r4_r12[4], noscratch->r4_r12[5], noscratch->r4_r12[6],
                noscratch->r4_r12[7]);
        printk("\n EXC_RETURN: %08x\n", exc_return);
}

void fault_enter(const char *s)
{
        printk("\n-------------------------------------------------------------\n");
        printk(" #%s\n\n", s);
}

void fault_exit(void)
{
        printk("\n-------------------------------------------------------------\n");
        __platform_halt();
}

void hardfault(struct kernel_context_regs *noscratch,
               struct thread_context_regs *scratch,
               u32 exc_return)
{
        fault_enter("Hard Fault");
        dump_frame(noscratch, scratch, exc_return);
        fault_exit();
}

void memmanage(struct kernel_context_regs *noscratch,
               struct thread_context_regs *scratch,
               u32 exc_return)
{
        fault_enter("Memory Fault");
        dump_frame(noscratch, scratch, exc_return);
        fault_exit();
}

void busfault(struct kernel_context_regs *noscratch,
               struct thread_context_regs *scratch,
               u32 exc_return)
{
        fault_enter("Bus Fault");
        dump_frame(noscratch, scratch, exc_return);
        fault_exit();
}

void usagefault(struct kernel_context_regs *noscratch,
               struct thread_context_regs *scratch,
               u32 exc_return)
{
        fault_enter("Usage Fault");
        dump_frame(noscratch, scratch, exc_return);
        fault_exit();
}
