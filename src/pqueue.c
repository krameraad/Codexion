/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pqueue.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/12 19:45:22 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/17 11:26:13 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"
#include <stdlib.h>

t_pqueue	*pqueue_init(size_t size, pq_cmp cmp, bool rev)
{
	t_pqueue	*pq;

	pq = malloc(sizeof(t_pqueue));
	if (!pq)
		return (error(ERR_MEM, "pqueue_init"), NULL);
	pq->items = malloc(size * sizeof(void *));
	if (!pq->items)
		return (free(pq), error(ERR_MEM, "pqueue_init"), NULL);
	pq->len = 0;
	pq->cap = size;
	pq->cmp = cmp;
	pq->rev = rev;
	return (pq);
}

void	pqueue_destroy(t_pqueue *pq)
{
	free(pq->items);
	free(pq);
}

void	pqueue_sort(t_pqueue *pq)
{
	size_t	i;

	i = pq->len - 1;
	while (i > 0)
	{
		if (pq->cmp(pq->items[i], pq->items[i - 1]) * (1 - !pq->rev * 2) > 0)
			swap(&pq->items[i], &pq->items[i - 1]);
		--i;
	}
}

bool	pqueue_push(t_pqueue *pq, void *item)
{
	if (pq->len >= pq->cap)
		return (false);
	pq->items[pq->len++] = item;
	pqueue_sort(pq);
	return (true);
}

void	*pqueue_pop(t_pqueue *pq)
{
	if (pq->len <= 0)
		return (NULL);
	return (pq->items[--pq->len]);
}

// Priority queue test.

// void	pqueue_print(t_pqueue *pq)
// {
// 	int		**items = (int **)pq->items;

// 	printf("[");
// 	for (size_t i = 0; i < pq->len; ++i)
// 	{
// 		printf("%d", *items[i]);
// 		if (i + 1 != pq->len)
// 			printf(", ");
// 	}
// 	printf("]\n");
// }

// int main(int argc, char const *argv[])
// {
// 	int array[] = {9,8,6,4,3,1,0};
// 	int a = 7, b = 2, c = 20;
// 	t_pqueue *pq = pqueue_init(10, &cmp_int, false);

// 	for (size_t i = 0; i < 7; ++i)
// 		pqueue_push(pq, array + i);
// 	// printf("Popped: %d\n", *(int *)pqueue_pop(pq));
// 	// printf("Popped: %d\n", *(int *)pqueue_pop(pq));
// 	// printf("Popped: %d\n", *(int *)pqueue_pop(pq));
// 	pqueue_print(pq);
// 	pqueue_push(pq, &a);
// 	pqueue_push(pq, &b);
// 	pqueue_push(pq, &c);
// 	pqueue_print(pq);
	
// 	return 0;
// }
