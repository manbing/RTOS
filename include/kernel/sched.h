#ifndef __SCHED_H__
#define __SCHED_H__

#include <kernel/thread.h>

#define SCHED_OPT_NONE 0
#define SCHED_OPT_RESTORE_ONLY 1
#define SCHED_OPT_RESET 2
#define SCHED_OPT_TICK 3

typedef int sched_class_t;

struct sched {
    sched_class_t class_type;
    int (*init)(void);
    int (*enqueue)(struct thread_info *thread);
    int (*dequeue)(struct thread_info *thread);
    int (*elect)(int switch_type);
};

int sched_elect(int flags);
int sched_enqueue(struct thread_info *thread);

#endif /* !__SCHED_H__ */
