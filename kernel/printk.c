#include <ucontext.h>
#include <stdarg.h>
#include <stdio.h>

#define VSNPRINTF_BUF_SIZE 256

static char vsnprintf_buf[VSNPRINTF_BUF_SIZE];
static unsigned int ctx_stack[128];
static ucontext_t printk_context;
static ucontext_t vsnprintf_context = {.uc_link = &printk_context};
static int retval;

static void co_vsnprintf(const char *format, va_list ap)
{
        retval = vsnprintf(vsnprintf_buf, VSNPRINTF_BUF_SIZE, format, ap);
}

void make_context(ucontext_t *ucp, void (*func)(), int argc, ...)
{
        va_list ap;

        if (argc) {
                va_start(ap, argc);

                /* the 4 first arguments go into registers r0-r3 */
                for (int i = 0; (i < argc) && (i < 4); i++)
                        ucp->uc_mcontext.gprs[i] = va_arg(ap, int);

                /* extra arguments go into the stack */
                va_end(ap);
        }

        /* top of the stack has a back-link pointer to the context's struct */
        ucp->uc_stack.ss_sp = (void *)((u32) ucp->uc_stack.ss_sp - sizeof(u32));
}

void init_printk(void)
{
        uart_init();
}

int printk(const char *format, ...)
{
        __disable_irq();

        va_list ap;

        va_start(ap, format);
        vsnprintf_context.uc_stack.ss_sp = &ctx_stack[128];
        make_context(&vsnprintf_context, co_vsnprintf, 2, format, ap);
}
