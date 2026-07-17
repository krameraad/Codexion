/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmp.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/13 16:23:35 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/17 14:34:18 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmp.h"

void	swap(void **a, void **b)
{
	void	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	cmp_int(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}
