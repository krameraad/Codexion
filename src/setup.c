/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/05/19 18:37:58 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/22 20:28:38 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"

#include "traceback.h"
#include "context.h"
#include <stdlib.h>

/* Validate that the context contains correct values. */
static bool	context_validate(t_context *ctx)
{
	if (ctx->number_of_coders < 1
		|| ctx->number_of_coders > 200
		|| ctx->time_to_burnout < 1
		|| ctx->time_to_compile < 1
		|| ctx->time_to_debug < 1
		|| ctx->time_to_refactor < 1
		|| ctx->number_of_compiles_required < 1
		|| ctx->dongle_cooldown < 1
		|| ctx->scheduler == NONE)
		return (false);
	return (true);
}

int	setup_context(char const **args)
{
	t_context	*ctx;

	ctx = malloc(sizeof(t_context));
	if (ctx == NULL)
		return (traceback(ERR_MEM, "context_new"), NULL);
	ctx->number_of_coders = atou(args[1]);
	ctx->time_to_burnout = atou(args[2]);
	ctx->time_to_compile = atou(args[3]);
	ctx->time_to_debug = atou(args[4]);
	ctx->time_to_refactor = atou(args[5]);
	ctx->number_of_compiles_required = atou(args[6]);
	ctx->dongle_cooldown = atou(args[7]);
	ctx->scheduler = get_scheduler(args[8]);
	if (!context_validate(ctx))
		return (traceback(ERR_ARGV, "context_new"), free(ctx), NULL);
	ctx->dongles = setup_dongles(ctx->number_of_coders);
	if (!ctx->dongles)
		return (traceback(ERR, "context_new"), free(ctx), NULL);
	pthread_mutex_init(&ctx->print_mutex, NULL);
	return (ctx);
	return (0);
}

t_dongle	*setup_dongles(int count)
{
	t_dongle	*dongles;
	int			i;

	dongles = malloc(count * sizeof(t_dongle));
	if (!dongles)
		return (traceback(ERR_MEM, "setup_dongles"), NULL);
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

t_coder	*setup_coders(int count, t_dongle *dongles)
{
	t_coder	*coders;
	int		i;

	coders = malloc(count * sizeof(t_coder));
	if (!coders)
		return (traceback(ERR_MEM, "setup_coders"), NULL);
	i = 0;
	while (i < count - 1)
	{
		coders[i] = (t_coder){0, i, FREE, 0, 0, NULL, NULL};
		coders[i].dongle_left = dongles + ((i - 1 + count) % count);
		coders[i].dongle_right = dongles + ((i + 1) % count);
		++i;
	}
	coders[i] = (t_coder){0, i, FREE, 0, 0, NULL, NULL};
	coders[i].dongle_right = dongles + ((i - 1 + count) % count);
	coders[i].dongle_left = dongles + ((i + 1) % count);
	return (coders);
}
