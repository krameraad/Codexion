/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coder.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/05/17 20:12:46 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/02 22:32:45 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

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
		usleep(100000);
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
