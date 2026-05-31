/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/05/19 18:37:58 by ekramer       #+#    #+#                 */
/*   Updated: 2026/05/31 17:14:52 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

t_coder	*setup_coders(t_context *ctx)
{
	t_coder	*coders;
	int		count;
	int		i;

	count = ctx->number_of_coders;
	coders = malloc(count * sizeof(t_coder));
	if (!coders)
		return (error(ERR_MEM, "setup_coders"), NULL);
	i = 0;
	while (i < count - 1)
	{
		coders[i] = (t_coder){0, i, FREE, 0, 0, ctx, NULL, NULL};
		coders[i].dongle_left = &ctx->dongles[(i - 1 + count) % count];
		coders[i].dongle_right = &ctx->dongles[(i + 1) % count];
		++i;
	}
	coders[i] = (t_coder){0, i, FREE, 0, 0, ctx, NULL, NULL};
	coders[i].dongle_right = &ctx->dongles[(i - 1 + count) % count];
	coders[i].dongle_left = &ctx->dongles[(i + 1) % count];
	return (coders);
}

t_dongle	*setup_dongles(int count)
{
	t_dongle	*dongles;
	int			i;

	dongles = malloc(count * sizeof(t_dongle));
	if (!dongles)
		return (error(ERR_MEM, "setup_dongles"), NULL);
	i = 0;
	while (i < count)
	{
		pthread_mutex_init(&dongles[i].mutex, NULL);
		dongles[i].available = true;
		dongles[i].last_drop_time = 0;
		++i;
	}
	return (dongles);
}
