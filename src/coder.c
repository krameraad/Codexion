/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coder.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/05/17 20:12:46 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/24 14:38:32 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"

#include "context.h"
#include "timestamp.h"
#include "log_state.h"
#ifndef _DEFAULT_SOURCE
# define _DEFAULT_SOURCE
#endif
#include <unistd.h>
#include <stdio.h>

static void	drop_dongles(t_coder *coder, int cooldown)
{
	coder->dongle_left->available_at = timestamp() + cooldown;
	pthread_mutex_unlock(&coder->dongle_left->mutex);
	coder->dongle_right->available_at = timestamp() + cooldown;
	pthread_mutex_unlock(&coder->dongle_right->mutex);
}

static int	take_dongle(t_dongle *dongle, int id, int *abort)
{
	pthread_mutex_lock(&dongle->mutex);
	if (*abort)
		return (pthread_mutex_unlock(&dongle->mutex), 1);
	log_state(timestamp(), id, LOG_DONGLE);
	return (0);
}

static void	work(t_coder *coder, t_context *ctx)
{
	coder->last_compile = timestamp();
	coder->state = COMPILING;
	if (ctx->abort)
		return ;
	log_state(coder->last_compile, coder->id, LOG_COMPILE);
	usleep(ctx->time_to_compile * 1000);
	coder->state = DEBUGGING;
	if (ctx->abort)
		return ;
	log_state(timestamp(), coder->id, LOG_DEBUG);
	usleep(ctx->time_to_debug * 1000);
	coder->state = REFACTORING;
	if (ctx->abort)
		return ;
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
		if (take_dongle(coder->dongle_left, coder->id, &ctx->abort))
			break ;
		if (take_dongle(coder->dongle_right, coder->id, &ctx->abort))
		{
			pthread_mutex_unlock(&coder->dongle_left->mutex);
			break ;
		}
		work(coder, ctx);
		drop_dongles(coder, ctx->dongle_cooldown);
		if (ctx->abort)
			break ;
		coder->compiles += 1;
	}
	return (NULL);
}
