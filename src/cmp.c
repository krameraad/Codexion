/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmp.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/13 16:23:35 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/23 14:25:37 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
