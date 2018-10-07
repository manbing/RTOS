#include <stdbool.h>

#include <kernel/kernel.h>
#include <kernel/thread.h>
#include <kernel/mm/page.h>
#include <kernel/sched.h>
#include <kernel/task.h>
#include <kernel/errno-base.h>
#include <linux/list.h>

static struct kernel_context_regs *alloc_interrupt_stack(void)
{
    char *memp;
    struct kernel_context_regs *kcr;

    memp = alloc_pagpes(size_to_page_order(INTR_STACK_SIZE));
    if (!memp)
        return NULL;
}

static struct thread_info *find_thread_by_id(int id)
{
    struct thread_info *tp;
    CURRENT_TASK_INFO(curr_task);

    list_for_each_entry(tp, &curr_task->thread_head, ti_list) {
        if (tp->ti_id == id)
            return tp;
    }

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

int thread_join(pthread_t thread, void **retval)
{
    struct thread_info *other;

    other = find_thread_by_id(thread);

    if (!other) /* No thread with the ID thread could be found. */
        return -ESRCH;

    if (other->ti_detached == true)
        return -EINVAL; /* thread is not a joinable thread. */

    if (other->ti_joinable == false) {
        CURRENT_THREAD_INFO(curr_thread);

        if (other->ti_joining)
            return -EINVAL; /* Another thread is already waiting tp join with this thread. */

        other->ti_joining = curr_thread;
        sched_elect(SCHED_OPT_NONE);
    }

    *retval = other->ti_retval;

    return 0;
}

int sys_pthread_join(pthread_t thread, void **retval)
{
    return thread_join(thread, retval);
}

static int thread_detach(pthread_t thread)
{
    struct thread_info *thread_info;

    thread_info = find_thread_by_id(thread);
    thread_info->ti_detached = true;

    return 0;
}

int sys_pthread_detach(pthread_t thread)
{
    return thread_detach(thread);
}
