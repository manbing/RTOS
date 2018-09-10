#ifndef _KERNEL_H_
#define _KERNEL_H_

/* round-down to a power of 2 */
#define align(x, a) align_mask(x, (__typeof__(x))((a)-1))
#define align_mask(x, mask) ((x) & ~(mask))

/* round-up to a power of 2 */
#define align_next(x, a) align_next_mask(x, (__typeof__(x))((a)-1))
#define align_next_mask(x, mask) (((x) + mask) & ~(mask))

#define container_of(ptr, type, member)				\
    ({								\
     	const __typeof__(((type *)0)->member) *__mptr = (ptr);	\
     	(type *) ((char *) __mptr - offsetof(type, member));	\
     })

int printk(const char *fmt, ...);


#endif /* !_KERNEL_H_ */
