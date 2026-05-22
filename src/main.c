/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/04/29 18:52:43 by ekramer       #+#    #+#                 */
/*   Updated: 2026/05/22 21:08:45 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

static int run_threads(t_coder *coders, size_t count)
{
	size_t		i;

	i = 0;
	while (i < count)
	{
		if (pthread_create(&coders[i].thread, NULL, &coder, &coders[i]))
			return (error(ERR_THRD, "run_threads"));
		++i;
	}
	i = 0;
	while (i < count)
	{
		pthread_join(coders[i].thread, NULL);
		++i;
	}
	return (0);
}

int	main(int argc, char const *argv[])
{
	t_context	*ctx;
	t_coder		*coders;
	int			err;

	if (argc != 9)
		return (error(ERR_ARGC, "main"));
	ctx = context_new(argv);
	if (ctx == NULL)
		return (1);
	coders = setup_coders(ctx);
	if (!coders)
		return (1);
	err = run_threads(coders, ctx->number_of_coders);
	return (err);
}
