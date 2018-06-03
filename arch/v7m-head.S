#include <kernel/linkage.h>

	.syntax unified
        .thumb

	.section ".vector". "a"
        .long	__early_stack_start__		@ SP main value
        .long	reset				@ Reset
        .long	0				@ NMI
        .long	hardf				@ Hard Fault
        .long	memf				@ Mem Manage
        .long	busf				@ Bus Fault
	.long	usgf				@ UsageFault
	.long	0				@ Reserved
	.long	0				@ Reserved
	.long	0				@ Reserved
	.long	0				@ Reserved
	.long	svcall				@ SVCall
	.long	0				@ Debug Monitor
	.long	0				@ Reserved
	.long	pendsv				@ PendSV
	.long	systick				@ SysTick
	.long	irq_entry			@ IRQ 0
	.long	irq_entry			@ IRQ 1
	.long	irq_entry			@ IRQ 2
	.long	irq_entry			@ IRQ 3
	.long	irq_entry			@ IRQ 4
	.long	irq_entry			@ IRQ 5
	.long	irq_entry			@ IRQ 6
	.long	irq_entry			@ IRQ 7
	.long	irq_entry			@ IRQ 8
	.long	irq_entry			@ IRQ 9
	.long	irq_entry			@ IRQ 10
	.long	irq_entry			@ IRQ 11
	.long	irq_entry			@ IRQ 12
	.long	irq_entry			@ IRQ 13
	.long	irq_entry			@ IRQ 14
	.long	irq_entry			@ IRQ 15
	.long	irq_entry			@ IRQ 16
	.long	irq_entry			@ IRQ 17
	.long	irq_entry			@ IRQ 18
	.long	irq_entry			@ IRQ 19
	.long	irq_entry			@ IRQ 20
	.long	irq_entry			@ IRQ 21
	.long	irq_entry			@ IRQ 22
	.long	irq_entry			@ IRQ 23
	.long	irq_entry			@ IRQ 24
	.long	irq_entry			@ IRQ 25
	.long	irq_entry			@ IRQ 26
	.long	irq_entry			@ IRQ 27
	.long	irq_entry			@ IRQ 28
	.long	irq_entry			@ IRQ 29
	.long	irq_entry			@ IRQ 30
	.long	irq_entry			@ IRQ 31
	.long	irq_entry			@ IRQ 32
	.long	irq_entry			@ IRQ 33
	.long	irq_entry			@ IRQ 34
	.long	irq_entry			@ IRQ 35
	.long	irq_entry			@ IRQ 36
	.long	irq_entry			@ IRQ 37
	.long	irq_entry			@ IRQ 38
	.long	irq_entry			@ IRQ 39
	.long	irq_entry			@ IRQ 40
	.long	irq_entry			@ IRQ 41
	.long	irq_entry			@ IRQ 42
	.long	irq_entry			@ IRQ 43
	.long	irq_entry			@ IRQ 44
	.long	irq_entry			@ IRQ 45
	.long	irq_entry			@ IRQ 46
	.long	irq_entry			@ IRQ 47
	.long	irq_entry			@ IRQ 48
	.long	irq_entry			@ IRQ 49
	.long	irq_entry			@ IRQ 50
	.long	irq_entry			@ IRQ 51
	.long	irq_entry			@ IRQ 52
	.long	irq_entry			@ IRQ 53
	.long	irq_entry			@ IRQ 54
	.long	irq_entry			@ IRQ 55
	.long	irq_entry			@ IRQ 56
	.long	irq_entry			@ IRQ 57
	.long	irq_entry			@ IRQ 58
	.long	irq_entry			@ IRQ 59
	.long	irq_entry			@ IRQ 60
	.long	irq_entry			@ IRQ 61
	.long	irq_entry			@ IRQ 62
	.long	irq_entry			@ IRQ 63





