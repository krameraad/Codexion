/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coder.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/05/17 20:12:46 by ekramer       #+#    #+#                 */
/*   Updated: 2026/05/22 20:51:08 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

static void drop_dongles(void)
{
	// drop forks
}

static void take_dongles(t_coder *coder)
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
	coder->last_compile_time = timestamp();
	coder->state = COMPILING;
	// lock print mutex
	printf("%zu %lu is compiling\n", coder->last_compile_time, coder->id);
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
		// coder_print(coder);
		take_dongles(coder);
		work(coder);
		drop_dongles();
		coder->compiles += 1;
	}
	return (NULL);
}
