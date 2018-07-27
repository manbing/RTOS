#include <kernel/irq.h>
#include <stddef.h>

#define IRQ_MAX 64

irq_handler_t irq_handler[IRQ_MAX];

static struct irq_desc irq_desc[NR_IRQS] = {
        [0 ... NR_IRQS - 1] = {
                .irq_data = {.state = 0x0},
                .action = NULL,
                .status = 0x0,
        }
};

static struct irq_desc *irq_to_desc(unsigned int irq)
{
        if (irq < NR_IRQS)
                return irq_desc + irq;
        return NULL;
}

int request_irq(unsigned int irq, irq_handler_t hdlr)
{
        struct irqaction *action;
        struct irq_desc *desc;

        desc = irq_to_desc(irq);

        if (desc && (desc->status & IRQ_NOREQUEST)) {
                action = (struct irqaction *) malloc(sizeof(struct irqaction));
                if (!action) {
                        goto fail;
                }

                action->irq = irq;
                action->handler = hdlr;

                desc->action = action;

                irq_handler[irq] = hdlr;

                return 0;
        }
fail:
        return -1;
}
