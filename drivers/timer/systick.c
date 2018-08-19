#include <kernel/sched.h>

void __attribute__((naked)) pendsv(void)
{
    __asm__ __volatile__(
            "push	{lr}	\n\t"
            "mov	r0,    #3	\n\t"
            "bl 	sched_elect	\n\t"
            "pop 	{pc}"
            ::
            );
}
