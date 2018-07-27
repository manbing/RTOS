CROSS_COMPILE ?= arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
AS = $(CROSS_COMPILE)as
AR = $(CROSS_COMPILE)ar
OBJCOPY = $(CROSS_COMPILE)objcopy
GDB = $(CROSS_COMPILE)gdb
HOSTCC  = gcc
WGET = wget
PYTHON ?= python3
QEMU_SYSTEM_ARM ?= /home/manbing/GitHub/Jserv/qemu_stm32/arm-softmmu/qemu-system-arm

# FIXME: configurable via menuconfig or command line
CFLAGS_OPT = -Os # -flto

CFLAGS += \
    -std=c99 \
    -W -Wall \
    -Iinclude -Iinclude/libc -I. \
    -I$(CMSIS)/arm -I$(CMSIS)/$(PLAT) -I$(CMSIS)/$(PLAT)/hal \
    -Iinclude/kernel \
    -Wno-main -fdiagnostics-color \
    -ffunction-sections -fdata-sections -ggdb \
    $(CFLAGS_OPT)

# FIXME: make Piko-specific build options configurable
CFLAGS += \

LDFLAGS += \
           -Wl,-Map=$(NAME).map -Wl,-Trtos.lds -Wl,--gc-sections \
           -nostartfiles

CFLAGS  += -mthumb -mcpu=$(CPU)
LDFLAGS += -mthumb -march=$(ARCH)
