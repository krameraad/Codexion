/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coder.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/05/17 20:12:46 by ekramer       #+#    #+#                 */
/*   Updated: 2026/05/20 14:51:25 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

static void drop_forks(void)
{
	// drop forks
}

static void take_forks(t_coder *coder)
{
	// lock print mutex
	printf("%zu %lu has taken a dongle\n", timestamp(), coder->id);
	// unlock print mutex
	// lock print mutex
	printf("%zu %lu has taken a dongle\n", timestamp(), coder->id);
	// unlock print mutex
}

static void work(t_coder *coder)
{
	coder->state = COMPILING;
	// lock print mutex
	printf("%zu %lu is compiling\n", timestamp(), coder->id);
	// unlock print mutex
	usleep(500000);
	coder->state = DEBUGGING;
	// lock print mutex
	printf("%zu %lu is debugging\n", timestamp(), coder->id);
	// unlock print mutex
	usleep(500000);
	coder->state = REFACTORING;
	// lock print mutex
	printf("%zu %lu is refactoring\n", timestamp(), coder->id);
	// unlock print mutex
	usleep(500000);
	coder->state = FREE;
}

void *coder(void *arg)
{
	t_coder	*coder;
	
	coder = arg;
	while (true)
	{
		coder_print(coder);
		take_forks(coder);
		work(coder);
		drop_forks();
		coder->compiles += 1;
	}
	return (NULL);
}
