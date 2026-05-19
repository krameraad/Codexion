/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coder.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/05/17 20:12:46 by ekramer       #+#    #+#                 */
/*   Updated: 2026/05/19 13:25:56 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

static void drop_forks(void)
{
	// drop forks
}

static void take_forks(size_t id)
{
	printf("%zu %lu has taken a dongle\n", timestamp(), id);
	printf("%zu %lu has taken a dongle\n", timestamp(), id);
}

static void work(t_coder *coder)
{
	printf("%zu %lu is compiling\n", timestamp(), coder->id);
	usleep(1000000);
	printf("%zu %lu is debugging\n", timestamp(), coder->id);
	usleep(1000000);
	printf("%zu %lu is refactoring\n", timestamp(), coder->id);
	usleep(1000000);
}

void *coder(void *arg)
{
	t_coder	*coder = arg;

	while (true)
	{
		take_forks(coder->id);
		work(coder);
		drop_forks();
		coder->compiles += 1;
	}
	return NULL;
}
