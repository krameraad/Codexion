/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   context.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/04/29 22:00:54 by ekramer       #+#    #+#                 */
/*   Updated: 2026/04/29 22:36:41 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/* Validate that the context contains correct values. */
static bool	context_validate(t_context *ctx)
{
	if (ctx->number_of_coders < 1
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

void	context_print(t_context *ctx)
{
	printf("%d\n", ctx->number_of_coders);
	printf("%d\n", ctx->time_to_burnout);
	printf("%d\n", ctx->time_to_compile);
	printf("%d\n", ctx->time_to_debug);
	printf("%d\n", ctx->time_to_refactor);
	printf("%d\n", ctx->number_of_compiles_required);
	printf("%d\n", ctx->dongle_cooldown);
	printf("%d\n", ctx->scheduler);
}

t_context	*context_new(char const **args)
{
	t_context	*ctx;

	ctx = malloc(sizeof(t_context));
	if (ctx == NULL)
		return (NULL);
	ctx->number_of_coders = atou(args[1]);
	ctx->time_to_burnout = atou(args[2]);
	ctx->time_to_compile = atou(args[3]);
	ctx->time_to_debug = atou(args[4]);
	ctx->time_to_refactor = atou(args[5]);
	ctx->number_of_compiles_required = atou(args[6]);
	ctx->dongle_cooldown = atou(args[7]);
	ctx->scheduler = get_scheduler(args[8]);
	if (!context_validate(ctx))
		return (free(ctx), NULL);
	return (ctx);
}
