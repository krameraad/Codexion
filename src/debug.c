/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/05/20 14:45:30 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/16 23:25:13 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"
#include <stdio.h>

void	coder_print(t_coder *coder)
{
	printf(
		"---\nCoder: %lu, thread id: %lu\nState: %d\n"
		"Compiles: %d, last compile time: %lu\n"
		"Context pointer: %p\n---\n",
		coder->id, coder->thread, coder->state,
		coder->compiles, coder->last_compile, coder->ctx
		);
}
