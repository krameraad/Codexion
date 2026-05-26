/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   context.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/04/29 22:00:54 by ekramer       #+#    #+#                 */
/*   Updated: 2026/05/26 23:12:25 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

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
	printf("Coders:            %d\n", ctx->number_of_coders);
	printf("Burnout time:      %d\n", ctx->time_to_burnout);
	printf("Compile time:      %d\n", ctx->time_to_compile);
	printf("Debug time:        %d\n", ctx->time_to_debug);
	printf("Refactor time:     %d\n", ctx->time_to_refactor);
	printf("Compiles required: %d\n", ctx->number_of_compiles_required);
	printf("Dongle cooldown:   %d\n", ctx->dongle_cooldown);
	if (ctx->scheduler == FIFO)
		printf("Scheduler:         fifo\n");
	else
		printf("Scheduler:         edf\n");
}

t_context	*context_new(char const **args)
{
	t_context	*ctx;

	ctx = malloc(sizeof(t_context));
	if (ctx == NULL)
		return (error(ERR_MEM, "context_new"), NULL);
	ctx->number_of_coders = atou(args[1]);
	ctx->time_to_burnout = atou(args[2]);
	ctx->time_to_compile = atou(args[3]);
	ctx->time_to_debug = atou(args[4]);
	ctx->time_to_refactor = atou(args[5]);
	ctx->number_of_compiles_required = atou(args[6]);
	ctx->dongle_cooldown = atou(args[7]);
	ctx->scheduler = get_scheduler(args[8]);
	ctx->dongles = setup_dongles(ctx->number_of_coders);
	pthread_mutex_init(&ctx->print_mutex, NULL);
	if (!context_validate(ctx))
		return (error(ERR_ARGV, "context_new"), free(ctx), NULL);
	return (ctx);
}
