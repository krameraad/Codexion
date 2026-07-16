/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   context.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/04/29 22:00:54 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/16 23:13:42 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "traceback.h"
#include "get.h"
#include "setup.h"
#include <stdio.h>
#include <stdlib.h>

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
	printf("Print Mutex:       %p\n", &ctx->print_mutex);
}

void	context_free(t_context *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->number_of_coders)
	{
		pthread_mutex_destroy(&ctx->dongles[i].mutex);
		++i;
	}
	free(ctx->dongles);
	pthread_mutex_destroy(&ctx->print_mutex);
	free(ctx);
}

t_context	*context_new(char const **args)
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
}
