OUTPUT_FORMAT("elf32_littlearm")
OUTPUT_ARCH(arm)

#define RAMORG 0x20000000

MEMORY
{
    rom (rx) : ORIGIN = 0, LENGTH = ROMSZ
    ram (rwx) : ORIGIN = RAMORG, LENGTH = RAMSZ
}

SECTIONS
{
    .vector 0: {
        PROVIDE(__vector_start__ = .);
        KEEP(*(.vector))
    } > rom

    .text BLOCK(8): {
        PROVIDE(__text_start__ = .);
        *(.text*)
        PROVIDE(__text_edn__ = .);
        . = ALIGN(8);
        PROVIDE(__shell_cmd_start__ = .);
        KEEP(*(.shell_cmd*))
        PROVIDE(__shell_cmd_end__ = .);
        PROVIDE(__sched_classes_start__ = .);
        KEEP(*(sched.class*))
        PROVIDE(__sched_classes_end__ = .);
        PROVIDE(__serial_hook_start__ = .);
        KEEP(*(serial.hook))
        PROVIDE(__serial_hook_end__ = .);
        PROVIDE(__rodata_start__ = .);
        *(.rodata*)
        PROVIDE(__rodata_end__ = .);
    } > rom
}
