/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/04/29 18:52:43 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/24 14:42:05 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"
#include "context.h"
#include "setup.h"
#include "traceback.h"
#include "monitor.h"
#include <stdlib.h>

static int	dongles_destroy(t_dongle *dongles)
{
	int	i;

	i = context()->number_of_coders - 1;
	while (i >= 0)
	{
		if (pthread_mutex_destroy(&(dongles + i)->mutex))
			return (traceback(ERR_MTXD, "dongles_destroy"));
		if (pthread_cond_destroy(&(dongles + i)->cond))
			return (traceback(ERR_CNDD, "dongles_destroy"));
		--i;
	}
	free(dongles);
	return (0);
}

static int	run_threads(t_coder *coders, int count)
{
	pthread_t	monitor_thread;
	int			i;

	i = 0;
	while (i < count)
	{
		if (pthread_create(&coders[i].thread, NULL, &coder, coders + i))
			return (traceback(ERR_THRC, "run_threads"));
		++i;
	}
	if (pthread_create(&monitor_thread, NULL, &monitor, coders))
		return (traceback(ERR_THRC, "run_threads"));
	i = 0;
	while (i < count)
	{
		if (pthread_join(coders[i].thread, NULL))
			return (traceback(ERR_THRJ, "run_threads"));
		++i;
	}
	if (pthread_join(monitor_thread, NULL))
		return (traceback(ERR_THRJ, "run_threads"));
	return (0);
}

int	main(int argc, char const *argv[])
{
	t_dongle	*dongles;
	t_coder		*coders;
	int			n;

	if (argc != 9)
		return (traceback(ERR_ARGC, "main"));
	if (setup_context(argv))
		return (traceback(ERR, "main"));
	n = context()->number_of_coders;
	dongles = setup_dongles(n);
	if (!dongles)
		return (traceback(ERR, "main"));
	coders = setup_coders(n, dongles);
	if (!coders)
		return (free(dongles), traceback(ERR, "main"));
	n = run_threads(coders, n);
	return (free(coders), dongles_destroy(dongles) + context_destroy() + n);
}
