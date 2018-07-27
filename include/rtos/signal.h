#ifndef _SIGNAL_H_
#define _SIGNAL_H_

typedef struct {
        void *ss_sp;	/* Base address of stack */
        int ss_flags;	/* Flags */
        size_t ss_size;	/* Number of bytes in stack */
} stack_t;

#endif /* !_SIGNAL_H_ */
