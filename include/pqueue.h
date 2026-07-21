/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pqueue.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/17 14:09:07 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/17 15:54:31 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PQUEUE_H
# define PQUEUE_H

# include <stddef.h>
# include <stdbool.h>

/**
 * @brief Comparator function to compare two items.
 *
 * @param a First item.
 * @param b Second item.
 * @return A negative value if @p a is lower than @p b,
 *         zero if they are equivalent,
 *         and a positive value if @p a is higher than @p b.
 */
typedef int	(*t_cmp)(void *, void *);

/**
 * @brief Generic priority queue.
 *
 * Stores pointers to arbitrary objects and orders them using a
 * user-provided comparator function.
 */
typedef struct s_pqueue
{
	void	**items;	/**< Array of stored items. */
	size_t	cap;		/**< Maximum capacity of the queue. */
	size_t	len;		/**< Current number of stored items. */
	t_cmp	cmp;		/**< Comparator used for sorting. */
	bool	rev;		/**< Whether the ordering is reversed. */
}	t_pqueue;

/**
 * @brief Create a new priority queue.
 *
 * @param size Maximum number of elements in the queue.
 * @param cmp Comparator function used to order elements.
 * @param rev If true, the queue is sorted in reverse order.
 * @return A newly allocated priority queue, or `NULL` on allocation failure.
 */
t_pqueue	*pqueue_init(size_t size, t_cmp cmp, bool rev);

/**
 * @brief Destroy a priority queue.
 *
 * Frees the memory owned by the queue itself.
 * Items stored in the queue are not freed.
 *
 * @param pq Priority queue to destroy.
 */
void		pqueue_destroy(t_pqueue *pq);

/**
 * @brief Sort a priority queue.
 *
 * Reorders the queue according to its comparator function.
 *
 * @param pq Priority queue to sort.
 */
void		pqueue_sort(t_pqueue *pq);

/**
 * @brief Insert an item into the priority queue.
 *
 * The item is added to the queue and the queue is reordered.
 *
 * @param pq Priority queue.
 * @param item Item to insert.
 * @return `true` if the item was successfully inserted, `false` otherwise.
 */
bool		pqueue_push(t_pqueue *pq, void *item);

/**
 * @brief Remove the highest-priority item from the queue.
 *
 * @param pq Priority queue.
 * @return The removed item, or `NULL` if the queue is empty.
 */
void		*pqueue_pop(t_pqueue *pq);

#endif // PQUEUE_H
