/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   timestamp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/05/12 14:57:49 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/17 14:33:23 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "timestamp.h"

#include <stddef.h>

time_t	timestamp(void)
{
	static time_t	offset = 0;
	time_t			delta;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	delta = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	if (!offset)
		offset = delta;
	delta -= offset;
	return (delta);
}
