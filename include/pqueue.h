/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pqueue.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/17 14:09:07 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/17 14:37:05 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PQUEUE_H
# define PQUEUE_H

# include <stddef.h>
# include <stdbool.h>

typedef int	(*t_pq_cmp)(void *, void *);

typedef struct s_pqueue
{
	void		**items;
	size_t		cap;
	size_t		len;
	t_pq_cmp	cmp;
	bool		rev;
}	t_pqueue;

/* Returns a priority queue `t_pqueue` with a cap of `size`.
The queue sorts items using the comparator function `cmp`,
in reverse order if `rev` is `true`. */
t_pqueue	*pqueue_init(size_t size, t_pq_cmp cmp, bool rev);

void		pqueue_destroy(t_pqueue *pq);

void		pqueue_sort(t_pqueue *pq);

bool		pqueue_push(t_pqueue *pq, void *item);

void		*pqueue_pop(t_pqueue *pq);

#endif // PQUEUE_H
