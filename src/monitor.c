/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/23 15:31:18 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/23 15:58:42 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "timestamp.h"
#include "log_state.h"
#ifndef _DEFAULT_SOURCE
# define _DEFAULT_SOURCE
#endif
#include <unistd.h>

void	*monitor(void *arg)
{
	t_coder		*coder;
	t_context	*ctx;
	int			i;

	coder = arg;
	ctx = context();
	while (1)
	{
		usleep(5000);
		i = 0;
		while (i < ctx->number_of_coders)
			if ((coder + i)->compiles >= ctx->number_of_compiles_required)
				++i;
			else if (timestamp() - (coder + i)->last_compile > ctx->time_to_burnout)
			{
				log_state(timestamp(), i, LOG_BURNOUT);
				i = -1;
				break ;
			}
		if (i == -1 || i == ctx->number_of_coders)
		{
			ctx->abort = 1;
			break ;
		}
	}
	return (NULL);
}
