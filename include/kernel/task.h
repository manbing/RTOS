#ifndef __TASK_H__
#define __TASK_H__

#include <kernel/fs.h>

#define PID_BASE 7000
#define PID_MAX 32768

struct task_info;

#define CURRENT_TASK_INFO(var) struct task_info *var = current_task_info();

struct task_info {
    pid_t pid;
    unsigned long filemap;
    struct file filetable[FILE_MAX];
    struct list_head list;
    struct list_head thread_head;
    struct list_head signal_head;
};

#endif /* __TASK_H__ */
