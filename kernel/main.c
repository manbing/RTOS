#include <kernel/thread.h>

struct thread_info *start_kernel(void)
{
        init_printk();
}
