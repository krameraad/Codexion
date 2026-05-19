/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/04/29 18:52:43 by ekramer       #+#    #+#                 */
/*   Updated: 2026/05/19 19:09:05 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

int	main(int argc, char const *argv[])
{
	t_context	*ctx;
	t_coder		*coders;

	if (argc != 9)
		return (error(ERR_ARGC, "main"), 1);
	ctx = context_new(argv);
	if (ctx == NULL)
		return (1);
	coders = setup_coders(*ctx);
	if (!coders)
		return (1);
	for (int i = 0; i < ctx->number_of_coders; ++i)
		if (pthread_create(&coders[i].thread, NULL, &coder, &coders[i]))
			return (fprintf(stderr, "Error making thread"), 1);
	for (int i = 0; i < ctx->number_of_coders; ++i)
		pthread_join(coders[i].thread, NULL);
	return (0);
}
