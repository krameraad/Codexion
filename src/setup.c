/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/05/19 18:37:58 by ekramer       #+#    #+#                 */
/*   Updated: 2026/05/19 19:08:43 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

t_coder	*setup_coders(t_context ctx)
{
	t_coder	*coders;
	int		i;

	coders = malloc(ctx.number_of_coders * sizeof(t_coder));
	if (!coders)
		return (error(ERR_MEM, "setup_coders"), NULL);
	i = 0;
	while (i < ctx.number_of_coders)
	{
		coders[i] = (t_coder){0, i, FREE, 0};
		++i;
	}
	return (coders);
}
