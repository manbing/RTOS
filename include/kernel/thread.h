#ifndef _KERNEL_THREAD_H_
#define _KERNEL_THREAD_H_

#include "linux/types.h"

struct kerenl_context_regs {
        u32 r4_r12[9];
        u32 lr;
};

struct thread_context_regs {
        u32 r0_r3__r12[5];
        u32 lr;
        u32 ret_addr;
        u32 xpsr;
}

#endif /* !_KERNEL_THREAD_H_ */
