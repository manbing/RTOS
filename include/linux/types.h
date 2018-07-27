#ifndef _LINUX_TYPES_H_
#define _LINUX_TYPES_H_

typedef unsigned int u32;
typedef int s32;

typedef unsigned int size_t;

struct list_head {
    struct list_head *next, *prev;
};

#endif /* !_LINUX_TYPES_H_ */
