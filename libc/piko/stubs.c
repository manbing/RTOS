#include <sys/cdefs.h>


#define HANGS_ON()						\
	{							\
            printk("error: Newlib needs %s", __func__);		\
	    for (;;)						\
                ;						\
        }

void *_sbrk(__unused int incr)
{
    HANGS_ON();

    return NULL;
}
