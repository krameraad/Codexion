/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coder.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/05/17 20:12:46 by ekramer       #+#    #+#                 */
/*   Updated: 2026/05/26 21:19:48 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

static void drop_dongles(void)
{
	// drop forks
}

static void take_dongles(t_coder *coder)
{
	pthread_mutex_lock(&coder->ctx->print_mutex);
	printf("%zu %lu has taken a dongle\n", timestamp(), coder->id);
	pthread_mutex_unlock(&coder->ctx->print_mutex);
	pthread_mutex_lock(&coder->ctx->print_mutex);
	printf("%zu %lu has taken a dongle\n", timestamp(), coder->id);
	pthread_mutex_unlock(&coder->ctx->print_mutex);
}

static void work(t_coder *coder)
{
	coder->last_compile_time = timestamp();
	coder->state = COMPILING;
	pthread_mutex_lock(&coder->ctx->print_mutex);
	printf("%zu %lu is compiling\n", coder->last_compile_time, coder->id);
	pthread_mutex_unlock(&coder->ctx->print_mutex);
	usleep(coder->ctx->time_to_compile * 1000);
	coder->state = DEBUGGING;
	pthread_mutex_lock(&coder->ctx->print_mutex);
	printf("%zu %lu is debugging\n", timestamp(), coder->id);
	pthread_mutex_unlock(&coder->ctx->print_mutex);
	usleep(coder->ctx->time_to_debug * 1000);
	coder->state = REFACTORING;
	pthread_mutex_lock(&coder->ctx->print_mutex);
	printf("%zu %lu is refactoring\n", timestamp(), coder->id);
	pthread_mutex_unlock(&coder->ctx->print_mutex);
	usleep(coder->ctx->time_to_refactor * 1000);
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
		break;
	}
	return (NULL);
}
