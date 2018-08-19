#include <kernel/compiler.h>

__weak void __platform_halt(void)
{
        for(;;)
        ;
}
