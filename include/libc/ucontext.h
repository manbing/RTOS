#ifndef _UCONTEXT_H_
#define _UCONTEXT_H_

#include <signal.h>
#include <kernel/types.h>

/* machine context on ARM */
typedef struct mcontext {
        u32 sp;
        u32 lr;
        u32 gprs[13]; /* r0-r12 */
        u32 pc;
} __attribute__((packed)) mcontext_t;

typedef struct ucontext {
        struct ucontext *uc_link;
        /* sigset_t uc_sigmask; */
        stack_t uc_stack;
        mcontext_t uc_mcontext;
} ucontext_t;

#endif /* !_UCONTEXT_H_ */
