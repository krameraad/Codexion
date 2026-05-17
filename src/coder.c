/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coder.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/05/17 20:12:46 by ekramer       #+#    #+#                 */
/*   Updated: 2026/05/17 21:58:40 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

static void drop_forks(void)
{
	// drop forks
}

static void take_forks(size_t id)
{
	printf("%zu %lu has taken a dongle", timestamp(), id);
	printf("%zu %lu has taken a dongle", timestamp(), id);
}

static void work(t_coderinfo const info)
{
	printf("%zu %lu is compiling", timestamp(), info.id);
	usleep(1000000);
	printf("%zu %lu is debugging", timestamp(), info.id);
	usleep(1000000);
	printf("%zu %lu is refactoring", timestamp(), info.id);
	usleep(1000000);
}

void *coder(void *arg)
{
	t_coderinfo	*info = arg;

	while (true)
	{
		take_forks(info->id);
		work(*info);
		drop_forks();
	}
	return NULL;
}
