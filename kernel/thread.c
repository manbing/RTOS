#include <kernel/kernel.h>
#include <kernel/thread.h>

void thread_exit(void *retval)
{
    CURRENT_THREAD_INFO(curr_thread);

    /* free thread stack memory */
    free_pages(aligan(curr_thread->ti_mach.mi_psp, curr_thread->ti_stacksize),
            size_to_page_order(curr_thread->ti_stacksize));
}

void sys_pthread_exit(void *retval)
{
    thread_exit(retval);
}
