#include <kernel/thread.h>

struct task_info *current_task_info(void)
{
    CURRENT_THREAD_INFO(curr_thread);

    return curr_thread->ti_task;
}
