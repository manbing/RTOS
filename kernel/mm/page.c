#include <kernel/log2.h>
#include <kernel/mm/page.h>

extern char __pgmem_start__;

/* .pgmem section is 32KB:
 *      - 128 pages of 256B is a 16 bytes map
 *      -  64 pages of 512B is a  8 bytes map
 *      -  32 pages of 1KB is a  4 bytes map
 *      -  16 pages of 2KB is a  2 bytes map
 *
 * Last page is reserved by the early stack, and freed after system init.
 */

/* 0 = allocated/undefined, 1 = free */
static unsigned long *const page_bitmap[] = {
    (unsigned long[]){0, 0, 0, 0}, (unsigned long[]){0, 0,},
    (unsigned long[]){0}, (unsigned long[]){0x7fff}
};

static const unsigned long page_bitmap_sz[] = {128, 64, 32, 16};

long size_to_page_order(unsigned long size)
{
    if (size <= 256)
        return 0;
    if (size <= 512)
        return 1;
    if (size <= 1024)
        return 2;
    if (size <= 2048)
        return 3;

    return -1;
}

static inline unsigned long get_buddy_index(unsigned long idx)
{
    return idx % 2 ? idx - 1 : idx + 1;
}

static inline unsigned long addr_to_page_idx(unsigned long addr, unsigned long order)
{
    return (addr - (unsigned long) &__pgmem_start__) >> (order + ilog2(MIN_PAGE_SIZE));
}

/* try to coalesce free buddies */
void free_pages(unsigned long addr, unsigned long order)
{
    unsigned long page_idx, buddy_idx, mask;

    for (; order < MAX_PAGE_ORDER; order++) {
        page_idx = addr_to_page_idx(addr, order);
        buddy_idx = get_buddy_index(page_idx);

        if (bitmap_get_bit(page_bitmap[order], buddy_idx)) {
            bitmap_clear_bit(page_bitmap[order], buddy_idx);
            mask = ~((1 << (order + 1 + ilog2(MIN_PAGE_SIZE))) - 1);
            addr &= mask;
        } else {
            bitmap_set_bit(page_bitmap[order], page_idx);
            return;
        }
    }
    bitmap_set_bit(page_bitmap[order], addr_to_page_idx(addr, order));
}

static long find_first_free_page(unsigned long order)
{
    unsigned long page_idx = find_first_bit(page_bitmap[order], page_bitmap_sz[order]);
}

void *alloc_pages(unsigned long order)
{
    unsigned long page_idx, o;

    for (o = order; (o <= MAX_PAGE_ORDER) && (find_first_free_page(o) < 0); o++)
        ;
}
