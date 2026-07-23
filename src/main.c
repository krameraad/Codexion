/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/04/29 18:52:43 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/23 14:44:04 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"
#include "context.h"
#include "setup.h"
#include "traceback.h"
#include <stdlib.h>

static int	run_threads(t_coder *coders, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_create(&coders[i].thread, NULL, &coder, &coders[i]))
			return (traceback(ERR_THRC, "run_threads"));
		++i;
	}
	i = 0;
	while (i < count)
	{
		if (pthread_join(coders[i].thread, NULL))
			return (traceback(ERR_THRJ, "run_threads"));
		++i;
	}
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
	return (free(coders), free(dongles), context_destroy() + n);
}
