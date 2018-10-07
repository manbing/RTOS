#include <kernel/mutex.h>
#include <kernel/thread.h>
#include <linux/list.h>
#include <kernel/sched.h>

static LIST_HEAD(mutex_head);

/* The thread owns the mutex on return. We also check the case when the lock
 * has been released between the test of the mutex and this syscall.
 */
int sys_pthread_mutex_lock(kernel_mutex_t *mutex)
{
    mutex->val++;
    
    if (!mutex->val)
        return 0;

    CURRENT_THREAD_INFO(curr_thread);
    curr_thread->ti_private = mutex;
    curr_thread->ti_state = THREAD_STATE_BLOCKED;
    list_add_tail(&curr_thread->ti_q, &mutex_head);
    sched_elect(SCHED_OPT_NONE);
    return 0;
}
