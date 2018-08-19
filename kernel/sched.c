#include <kernel/thread.h>
#include <kernel/sched.h>

static struct sched *sched;

int sched_elect(int flags)
{
    int r;
    CURRENT_THREAD_INFO(cur_thread);

    KERNEL_STACK_CHECKING;

    r = sched->elect(flags);
    cur_thread->ti_state = THREAD_STATE_RUNNING;

    return r;
}

int sched_enqueue(struct thread_info *thread)
{
    thread->ti_state = THREAD_STATE_ACTIVED;

    return sched->enqueue(thread);
}
