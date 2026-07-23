/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/23 15:31:18 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/23 21:28:42 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "timestamp.h"
#include "log_state.h"
#ifndef _DEFAULT_SOURCE
# define _DEFAULT_SOURCE
#endif
#include <unistd.h>

static int	check_coders(t_coder *coders, t_context *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->number_of_coders)
	{
		if (timestamp() - (coders + i)->last_compile > ctx->time_to_burnout)
			return (log_state(timestamp(), i, LOG_BURNOUT), -1);
		if ((coders + i)->compiles < ctx->number_of_compiles_required)
			return (0);
	}
	return (1);
}

void	*monitor(void *arg)
{
	t_coder		*coders;
	t_context	*ctx;

	coders = arg;
	ctx = context();
	while (1)
	{
		usleep(5000);
		if (check_coders(coders, ctx))
		{
			ctx->abort = 1;
			break ;
		}
	}
	return (NULL);
}
