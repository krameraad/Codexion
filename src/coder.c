/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coder.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/05/17 20:12:46 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/23 14:38:06 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"

#include "context.h"
#include "timestamp.h"
#ifndef _DEFAULT_SOURCE
# define _DEFAULT_SOURCE
#endif
#include <unistd.h>
#include <stdio.h>

static int	log_state(time_t t, size_t id, char const *msg)
{
	int	result;

	pthread_mutex_lock(&context()->print_mutex);
	result = printf("%zu %lu %s\n", t, id, msg);
	pthread_mutex_unlock(&context()->print_mutex);
	return (result);
}

static void	drop_dongles(t_coder *coder)
{
	coder->dongle_left->last_drop_time = timestamp();
	pthread_mutex_unlock(&coder->dongle_left->mutex);
	coder->dongle_right->last_drop_time = timestamp();
	pthread_mutex_unlock(&coder->dongle_right->mutex);
}

static void	take_dongles(t_coder *coder)
{
	pthread_mutex_lock(&coder->dongle_left->mutex);
	log_state(timestamp(), coder->id, LOG_DONGLE);
	pthread_mutex_lock(&coder->dongle_right->mutex);
	log_state(timestamp(), coder->id, LOG_DONGLE);
}

static void	work(t_coder *coder, t_context *ctx)
{
	coder->last_compile = timestamp();
	coder->state = COMPILING;
	log_state(coder->last_compile, coder->id, LOG_COMPILE);
	usleep(ctx->time_to_compile * 1000);
	coder->state = DEBUGGING;
	log_state(timestamp(), coder->id, LOG_DEBUG);
	usleep(ctx->time_to_debug * 1000);
	coder->state = REFACTORING;
	log_state(timestamp(), coder->id, LOG_REFACTOR);
	usleep(ctx->time_to_refactor * 1000);
	coder->state = FREE;
}

void	*coder(void *arg)
{
	t_coder		*coder;
	t_context	*ctx;

	coder = arg;
	ctx = context();
	if (coder->id % 2)
		usleep(10000);
	while (1)
	{
		take_dongles(coder);
		work(coder, ctx);
		drop_dongles(coder);
		coder->compiles += 1;
		if (coder->compiles >= ctx->number_of_compiles_required)
			break ;
	}
	return (NULL);
}
