/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   traceback.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/04/29 23:17:54 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/15 19:31:53 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "traceback.h"
#include <stdio.h>

int	traceback(char const *msg, char const *func)
{
	fprintf(
		stderr,
		ESC_R "Error in function \"%s\":\n\t%s\n" ESC_X,
		func, msg
	);
	return (1);
}

// void	coder_print(t_coder *coder)
// {
// 	printf(
// 		"---\nCoder: %lu, thread id: %lu\nState: %d\n"
// 		"Compiles: %d, last compile time: %lu\n"
// 		"Context pointer: %p\n---\n",
// 		coder->id, coder->thread, coder->state,
// 		coder->compiles, coder->last_compile, coder->ctx
// 		);
// }
