/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coder.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/05/17 20:12:46 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/15 19:53:11 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"
#include "timestamp.h"
#ifndef _DEFAULT_SOURCE
# define _DEFAULT_SOURCE
#endif
#include <unistd.h>
#include <stdio.h>

static int	log_state(
	pthread_mutex_t *mutex, time_t t, size_t id, char const *msg)
{
	int	result;

	pthread_mutex_lock(mutex);
	result = printf("%zu %lu %s\n", t, id, msg);
	pthread_mutex_unlock(mutex);
	return (result);
}

static void	drop_dongles(t_coder *coder)
{
	pthread_mutex_unlock(&coder->dongle_left->mutex);
	pthread_mutex_unlock(&coder->dongle_right->mutex);
}

static void	take_dongles(t_coder *coder)
{
	pthread_mutex_lock(&coder->dongle_left->mutex);
	log_state(&coder->ctx->print_mutex, timestamp(), coder->id, LOG_DONGLE);
	pthread_mutex_lock(&coder->dongle_right->mutex);
	log_state(&coder->ctx->print_mutex, timestamp(), coder->id, LOG_DONGLE);
}

static void	work(t_coder *coder)
{
	coder->last_compile = timestamp();
	coder->state = COMPILING;
	log_state(
		&coder->ctx->print_mutex, coder->last_compile, coder->id, LOG_COMPILE);
	usleep(coder->ctx->time_to_compile * 1000);
	coder->state = DEBUGGING;
	log_state(&coder->ctx->print_mutex, timestamp(), coder->id, LOG_DEBUG);
	usleep(coder->ctx->time_to_debug * 1000);
	coder->state = REFACTORING;
	log_state(&coder->ctx->print_mutex, timestamp(), coder->id, LOG_REFACTOR);
	usleep(coder->ctx->time_to_refactor * 1000);
	coder->state = FREE;
}

void	*coder(void *arg)
{
	t_coder	*coder;

	coder = arg;
	if (coder->id % 2)
		usleep(10000);
	while (true)
	{
		// coder_print(coder);
		take_dongles(coder);
		work(coder);
		drop_dongles(coder);
		coder->compiles += 1;
		if (coder->compiles >= coder->ctx->number_of_compiles_required)
			break ;
	}
	return (NULL);
}
