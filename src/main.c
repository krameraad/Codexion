/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/04/29 18:52:43 by ekramer       #+#    #+#                 */
/*   Updated: 2026/05/09 19:55:18 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	main(int argc, char const *argv[])
{
	t_context	*ctx;

	if (argc != 9)
		return (error(ERR_ARGC, "main"), 1);
	ctx = context_new(argv);
	if (ctx == NULL)
		return (1);
	return (0);
}
