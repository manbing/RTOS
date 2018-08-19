#include <kernel/kernel.h>
#include <kernel/thread.h>
#include <kernel/mm/page.h>
#include <kernel/sched.h>

static struct kernel_context_regs *alloc_interrupt_stack(void)
{
    char *memp;
    struct kernel_context_regs *kcr;

    memp = alloc_pagpes(size_to_page_order(INTR_STACK_SIZE));
    if (!memp)
        return NULL;
}

void thread_exit(void *retval)
{
    CURRENT_THREAD_INFO(curr_thread);

    /* free thread stack memory */
    free_pages(align(curr_thread->ti_mach.mi_psp, curr_thread->ti_stacksize),
            size_to_page_order(curr_thread->ti_stacksize));
}

void sys_pthread_exit(void *retval)
{
    thread_exit(retval);
}

int thread_self(void)
{
    CURRENT_THREAD_INFO(curr_thread);

    return curr_thread->ti_id;
}

pthread_t sys_pthread_self(void)
{
    return (pthread_t) thread_self();
}

int thread_yield(void)
{
    CURRENT_THREAD_INFO(curr_thread);
    sched_enqueue(curr_thread);

    return sched_elect(SCHED_OPT_NONE);
}

int sys_pthread_yield(void)
{
    return thread_yield();
}

struct thread_info *thread_create(void **(*start_routine)(void *),
                                  void *arg,
                                  enum thread_privilege priv,
                                  size_t stacksize,
                                  struct task_info *task)
{
    struct thread_info *thread;
    struct kernel_context_regs *kcr;
    struct thread_context_regs *tcr;
    static int thread_count = 0;

    kcr = alloc_interrupt_stack();
    if(!kcr)
        return NULL;
}

int sys_pthread_create(pthread_t *thread,
                        const pthread_attr_t *attr,
                        void *(*start_routine)(void *),
                        void *arg)
{
    return 0;
}
