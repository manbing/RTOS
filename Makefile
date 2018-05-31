NAME = rtos

PLAT ?= stm32p103

include platform/$(PLAT)/Makefile

CSRC +=
SSRC += 
