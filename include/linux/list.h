#ifndef __LIST_H__
#define __LIST_H__

#include <linux/compiler.h>

#define LIST_HEAD_INIT(name)	\
	{			\
            &(name), &(name)	\
        }

#define LIST_HEAD(name) struct list_head name = LIST_HEAD_INIT(name)

/**
 * list entry - get the struct for this entry
 * @ptr:	the &struct list_head pointer.
 * @type:	the type of the struct this embedded in.
 * @member:     the name of the list_head within the struct.
 */
#define list_entry(ptr, type, member) container_of(ptr, type, member)

/**
 * list_first_entry - get the first element from a list
 * @ptr:	the list head to take the element from.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_head within the struct.
 *
 * Note, that list is expected to be not empty.
 */
#define list_first_entry(ptr, type, member) \
    list_entry((ptr)->next, type, member)

/**
 * list_next_entry - get the next element in list
 * @pos:	the type * to curosr.
 * @member:	the name of the list_head within the struct.
 */
#define list_next_entry(pos, member) \
    list_entry((pos)->member.next, __typeof__(*(pos)), member)

/**
 * list_for_each_entry	-	iterate over list of given type
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head for you list.
 * @member:	the name of the list_head within the struct.
 */
#define list_for_each_entry(pos, head, member)				\
    for (pos = list_first_entry(head, __typeof__(*pos), member);	\
         &pos->member != (head); pos = list_next_entry(pos, member))

/*
 * Insert a new entry between two known consecutive entries.
 * 
 * This is only for internal list manipulation where we know
 * thre prev/next entries already!
 */
static inline void __list_add(struct list_head *new,
        		      struct list_head *prev,
                              struct list_head *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    WRITE_ONCE(prev->next, new);
}

/*
 * list_add_tail - add a new entry
 * @new: new entry to be added
 * @head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
    __list_add(new, head->prev, head);
}

#endif /* !__LIST_H__ */
