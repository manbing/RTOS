#include <kernel/linkage.h>

	.syntax unified
	.thumb

        @ do the thread - context switch
        @
        @ r0: struct thread_info *next
        @ r1: struct thread_info *prev (i.e., the current thread)
        @ (r1), r2, r3, r12: scratch registers

ENTRY(switch_to)
    /* save previous thread context */
    push	{r4-r12, lr}
    mov		r2, sp
    mrs		r3, psp
    stm		r1!, {r2, r3}

ENTRY(thread_restore)
    /* restore next task context */
    ldm		r0!, {r1-r3}
    mov		sp, r1
    msr		control, r3
    pop		{r4-r12, pc}
ENDPROC(thread_restore)
ENDPROC(switch_to)

        .macro fault_handler f
        push    {r4-r11}
        mov     r0, sp
        mov     r2, lr
        mrs     r1, psp
        b       \f
        .endm

ENTRY(hardf)
        fault_handler hardfault
ENDPROC(hardf)

ENTRY(memf)
        fault_handler memmanage
ENDPROC(memf)

ENTRY(busf)
        fault_handler busfault
ENDPROC(busf)

ENTRY(usgf)
        fault_handler usagefault
ENDPROC(usgf)
