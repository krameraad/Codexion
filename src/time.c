/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/05/12 14:57:49 by ekramer       #+#    #+#                 */
/*   Updated: 2026/05/19 13:30:57 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

time_t	timestamp(void)
{
	static time_t	t = 0;
	time_t			delta;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	
	printf("%zu\n", t);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
