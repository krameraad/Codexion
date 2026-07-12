/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pqueue.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/12 19:45:22 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/12 20:19:56 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

t_pqueue	*pqueue_init(size_t size, size_t data_size)
{
	t_pqueue	*pq;

	pq = malloc(sizeof(t_pqueue));
	if (pq == NULL)
		return (NULL);
	pq->items = malloc(size * data_size);
	if (pq->items == NULL)
		return (free(pq), NULL);
	pq->len = 0;
	pq->cap = size;
	return (pq);
}

void	pqueue_destroy(t_pqueue *pqueue)
{
	free(pqueue->items);
	free(pqueue);
}

int	pqueue_push(t_pqueue *pqueue, void *item)
{
	if (pqueue->len >= pqueue->cap)
		return (1);
	pqueue->items[pqueue->len] = item;
	pqueue->len += 1;
	return (0);
}

t_pqueue	*pqueue_pop(t_pqueue *pqueue)
{
	if (pqueue->len <= 0)
		return (NULL);
	pqueue->len -= 1;
	return (pqueue->items[pqueue->len]);
}
