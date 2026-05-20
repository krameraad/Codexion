/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/05/20 14:45:30 by ekramer       #+#    #+#                 */
/*   Updated: 2026/05/20 14:55:07 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	coder_print(t_coder *coder)
{
	printf(
		"Coder: %lu, thread id: %lu\nState: %d\n"
		"Compiles: %lu, last compile time: %lu\n"
		"Context pointer: %p\n---\n",
		coder->id, coder->thread, coder->state,
		coder->compiles, coder->last_compile_time, coder->ctx
	);
}