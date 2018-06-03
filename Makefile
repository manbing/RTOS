NAME = rtos

PLAT ?= stm32p103

include platform/$(PLAT)/Makefile

CSRC +=
SSRC += 

# arch-specific
SSRC += arch/v7m-head.S arch/v7m-entry.S arch/v7m-svcall.S
CSRC += arch/v7m-faults.c
