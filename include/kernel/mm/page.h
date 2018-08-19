#ifndef __KERNEL_MM_PAGE_H__
#define __KERNEL_MM_PAGE_H__

#define MAX_PAGE_ORDER 3  /* max page size is 2 KB */
#define MIN_PAGE_SIZE 256 /* min page size is 256 bytes */

long size_to_page_order(unsigned long size);
#endif /* !__KERNEL_MM_PAGE_H__ */
