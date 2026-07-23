/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   context.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/04/29 22:00:54 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/23 14:40:08 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"

#include "traceback.h"

t_context	*context(void)
{
	static t_context	ctx = {0};

	return (&ctx);
}

int	context_destroy(void)
{
	if (pthread_mutex_destroy(&context()->print_mutex))
		return (traceback(ERR_MTXD, "context_destroy"));
	return (0);
}
