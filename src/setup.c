/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/05/19 18:37:58 by ekramer       #+#    #+#                 */
/*   Updated: 2026/05/26 23:11:45 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

t_coder	*setup_coders(t_context *ctx)
{
	t_coder	*coders;
	int		i;

	coders = malloc(ctx->number_of_coders * sizeof(t_coder));
	if (!coders)
		return (error(ERR_MEM, "setup_coders"), NULL);
	i = 0;
	while (i < ctx->number_of_coders)
	{
		coders[i] = (t_coder){0, i, FREE, 0, 0, ctx};
		++i;
	}
	return (coders);
}

t_dongle	*setup_dongles(int count)
{
	t_dongle	*dongles;
	int		i;

	dongles = malloc(count * sizeof(t_dongle));
	if (!dongles)
		return (error(ERR_MEM, "setup_dongles"), NULL);
	i = 0;
	while (i < count)
	{
		dongles[i] = (t_dongle){true, 0};
		++i;
	}
	return (dongles);
}
