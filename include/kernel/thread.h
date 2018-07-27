#ifndef _KERNEL_THREAD_H_
#define _KERNEL_THREAD_H_

#include "linux/types.h"

#define INTR_STACK_ORDER 9 /* 512 Bytes */
#define INTR_STACK_SIZE (1 << INTR_STACK_ORDER)

struct thread_info;

#define CURRENT_THREAD_INFO(var) \
    struct thread_info *var = current_thread_info();

struct kernel_context_regs {
        u32 r4_r12[9];
        u32 lr;
};

struct thread_context_regs {
        u32 r0_r3__r12[5];
        u32 lr;
        u32 ret_addr;
        u32 xpsr;
};

/* machine-specific thread info on ARM */
struct mthread_info {
    u32 mi_msp;  /* +0 */
    u32 mi_psp;  /* +4 */
    u32 mi_priv; /* +8 */
} __attribute__((packed));

struct thread_info {
    /* machine-specific thread info */
    struct mthread_info ti_mach;

    /* thread description data */
    int ti_priority;
    int ti_id;
    int ti_state;
    size_t ti_stacksize; /* user thread stacksize */
    struct task_info *ti_task;

    struct list_head ti_list; /* global list of threads */
    struct list_head ti_q; /* shared by sched runq, mutex waitq, thread joinq */

    /* http://www.domaigne.com/blog/computing/joinable-and-detached-threads/ */
    void *ti_retval;
    int ti_detached;
    int ti_joinable;
    struct thread_info *ti_joining;

    /* Pointer to mutually exclusive data: the mutex the thread is blocking
     * on, the exit value when thread is not yet joined, etc. */
    void *ti_private;

/* /\* local-storage *\/ */
/* struct list_head *ti_lsq; // local-storage queue */

#ifdef CONFIG_KERNEL_STACK_CHECKING
    u32 ti_canary[2];
#endif

    char ti_storage[0];
};

static inline struct thread_info *current_thread_info(void)
{
    struct thread_info *this;

    __asm__ __volatile__(
            "mov %0, sp \n\t"
            "bfc %0, #0, %1"
            : "=r" (this)
            : "M" (INTR_STACK_ORDER));

    return this;
}

#endif /* !_KERNEL_THREAD_H_ */
