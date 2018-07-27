#ifndef _KERNEL_H_
#define _KERNEL_H_

/* round-down to a power of 2 */
#define align(x, a) align_mask(x, (__typeof__(x))((a)-1))
#define align_mask(x, mask) ((x) & ~(mask))

/* round-up to a power of 2 */
#define align_next(x, a) align_next_mask(x, (__typeof__(x))((a)-1))
#define align_next_mask(x, mask) (((x) + mask) & ~(mask))

int printk(const char *fmt, ...);

#endif /* !_KERNEL_H_ */
