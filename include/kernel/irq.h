#ifndef KERNEL_IRQ_H
#define KERNEL_IRQ_H

#define NR_IRQS 64

struct irqaction;
typedef void (*irq_handler_t)(void);

enum {
        IRQ_NOREQUEST = 1,
        IRQ_MAX
};

/**
 * struct irq_data - per chip data
 * XXX: Thanks for CMSIS. We don't have to impl per chip function and data.
 *      but this concept should be remained due to more precious description
 *      of irqs and chips(HW).
 */
struct irq_data {
        unsigned int state;
};

/**
 * struct irq_desc - interrupt descriptor
 *
 * @action:		the irq function
 * @status:             status information
 * @irq_state:          per irq state information
 */
struct irq_desc {
        struct irq_data irq_data;
        struct irqaction *action;
        unsigned int status;
};

struct irqaction {
        irq_handler_t handler;
        unsigned int irq;
};

int request_irq(unsigned int irq, irq_handler_t hdlr);
int free_irq(unsigned int irq);

#endif /* !KERNEL_IRQ_H */
