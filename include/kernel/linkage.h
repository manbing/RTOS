#ifndef _KERNEL_LINKAGE_H
#define _KERNEL_LINKAGE_H

#ifdef __ASSEMBLER__

#define ENTRY(name) \
    .globl name;	\
    .align 4;
    name:

#endif

#endif /*!_KERNEL_LINKAGE_H*/
