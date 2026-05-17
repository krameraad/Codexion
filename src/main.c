/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/04/29 18:52:43 by ekramer       #+#    #+#                 */
/*   Updated: 2026/05/17 20:15:41 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

int	main(int argc, char const *argv[])
{
	t_context	*ctx;
	int			i;

	if (argc != 9)
		return (error(ERR_ARGC, "main"), 1);
	ctx = context_new(argv);
	if (ctx == NULL)
		return (1);
	i = 0;
	while ()
	return (0);
}
