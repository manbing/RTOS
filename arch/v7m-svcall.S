#include <kernel/linkage.h>

        .syntax unified
        .thumb

        .set    R0, 0
        .set    RET_ADDRESS, 24
        .set    xPSR, 0x1c

ENTRY(svcall)
        push    {lr}
        mrs     lr, psp
        ldr     r12, [lr, #RET_ADDRESS]
        ldrb    r12, [r12, #-2]
        tbb     [pc, r12]

0:      .irpc   argc, 0123456
        .byte   ($\argc - 0b) / 2
        .endr
        .balign 2

        .balign 2
$0:     ldr     r12, =syscall_vect
        ldr.w   r12, [r12, r0, lsl #2]
        blx     r12
        b       0f

        .balign 2
$1:     ldr     r12, =syscall_vect
        ldr.w   r12, [r12, r1, lsl #2]
        blx     r12
        b       0f

        .balign 2
$2:     ldr     r12, =syscall_vect
        ldr.w   r12, [r12, r2, lsl #2]
        blx     r12
        b       0f

        .balign 2
$3:     ldr     r12, =syscall_vect
        ldr.w   r12, [r12, r3, lsl #2]
        blx     r12
        b       0f

        .balign 2
$4:     ldr     r12, [lr, #xPSR]
        tst     r12, #1 << 9
        ite     eq
        ldreq   lr, [lr, #0x20]
        ldrne   lr, [lr, #0x24]
        ldr     r12, =syscall_vect
        ldr.w   r12, [r12, lr, lsl #2]
        blx     r12
        b       0f

        .balign 2
$5:     ldr     r12, [lr, #xPSR]
        tst     r12, #1 << 9
        ite     eq
        addeq   lr, #0x20
        addne   lr, #0x24
        ldm     lr, {r12, lr}
        push    {r12}
        ldr     r12, =syscall_vect
        ldr.w   r12, [r12, lr, lsl #2]
        blx     r12
        add     sp, #4
        b       0f

        .balign 2
$6:     ldr     r12, [lr, #xPSR]
        tst     r12, #1 << 9
        ite     eq
        addeq   lr, #0x20
        addne   lr, #0x24
        ldm     lr, {r11, r12, lr}
        push    {r11, r12}
        ldr     r12, =syscall_vect
        ldr.w   r12, [r12, lr, lsl #2]
        blx     r12
        pop     {r11, r12}


        .global syscall_return
syscall_return:
0:      mrs     r1, psp
        str     r0, [r1, #R0]
        pop     {pc}
ENDPROC(svcall)
