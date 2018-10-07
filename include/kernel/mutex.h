#ifndef __MUTEX_H__
#define __MUTEX_H__

typedef _Atomic int atomic_s32;

typedef struct {
    atomic_s32 val;
} kernel_mutex_t;

#endif /* !__MUTEX_H__ */
