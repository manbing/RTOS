#ifndef _KERNEL_THREAD_H_
#define _KERNEL_THREAD_H_

#include <sys/types.h>

#include "linux/types.h"

#define INTR_STACK_ORDER 9 /* 512 Bytes */
#define INTR_STACK_SIZE (1 << INTR_STACK_ORDER)

struct thread_info;

#define CURRENT_THREAD_INFO(var) \
    struct thread_info *var = current_thread_info();

#ifdef CONFIG_KERNEL_STACK_CHECKING
#define KERNEL_STACK_CHECKING						\
	{								\
            __auto_type cur_thread = current_thread_info();		\
            if ((cur_thread->ti_canary[0] != THREAD_CANARY0) ||		\
                (cur_thread->ti_canary[1] != THREAD_CANARY1)) {		\
               printk("\n kernel panic: overflow in kernel stack\n"); 	\
               printk(" 0 %08x  %08x\n", THREAD_CANARY0,		\
                       cur_thread->ti_canary[0]); 		    	\
               printk(" 0 %08x  %08x\n", THREAD_CANARY1,		\
                       cur_thread->ti_canary[1]); 		    	\
                							\
               for (;;) 						\
                    ;							\
            }								\
        }
#else
#define KERNEL_STACK_CHECKING
#endif

enum thread_privilege { THREAD_PRIV_SUPERVISOR = 0, THREAD_PRIV_USER = 1,};

enum thread_state {
    /* Thread structure allocated but not enqueued in the system scheduler. */
    THREAD_STATE_NEW,

    /**
     * Ready to run in the system scheduler.
     *
     * XXX: why we need two ready states?
     *
     *  Ans: One is ready for execution in active queue,
     *          the other one is the state for out of
     *          timeslice. In order to achieve O(1), we
     *          adopt specified function to determine
     *          which one is actived or expired.
     *
     * XXX: we impl map from `actived` and `expired` to
     *          `ready1` and `ready2`
     */
    THREAD_STATE_READY1,  // THREAD_STATE_ACTIVED
    THREAD_STATE_READY2,  // THREAD_STATE_EXPIRED

    /* Running by the system scheduler. */
    THREAD_STATE_RUNNING,

    /* The thread has normally exited or has called Pthread_exit to exit. Its
     * resources have not been freed and will be freed if it is detached or
     * joined.    */
    THREAD_STATE_TERMINATED,

    /* Waiting for a mutex or resource. */
    THREAD_STATE_BLOCKED
};
#define THREAD_STATE_ACTIVED THREAD_SCHED_STATE[ACTIVED]
#define THREAD_STATE_EXPIRED THREAD_SCHED_STATE[EXPIRED]

enum {
    ACTIVED,
    EXPIRED,
    NR_THREAD_SCHED_STATE,
};

static int THREAD_SCHED_STATE [NR_THREAD_SCHED_STATE] = {
    [ACTIVED] = THREAD_STATE_READY1, [EXPIRED] = THREAD_STATE_READY2,
};

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
