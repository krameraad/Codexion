/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/04/29 18:52:43 by ekramer       #+#    #+#                 */
/*   Updated: 2026/05/19 13:15:44 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

int	main(int argc, char const *argv[])
{
	t_context	*ctx;
	t_coder		coders[10] = {
		{0}, {0}, {0}, {0}, {0},
		{0}, {0}, {0}, {0}, {0}};

	
	if (argc != 9)
		return (error(ERR_ARGC, "main"), 1);
	ctx = context_new(argv);
	if (ctx == NULL)
		return (1);
	for (size_t i = 0; i < 10; ++i)
		if (pthread_create(&coders[i].thread, NULL, &coder, &coders[i].thread))
			return (fprintf(stderr, "Error thread"), 1);
	for (size_t i = 0; i < 10; ++i)
		pthread_join(coders[i].thread, NULL);
	return (0);
}
