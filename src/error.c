/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/04/29 23:17:54 by ekramer       #+#    #+#                 */
/*   Updated: 2026/05/17 18:57:52 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

int	error(char const *msg, char const *func)
{
	fprintf(
		stderr,
		ESC_R "Error in function \"%s\":\n\t%s\n" ESC_X,
		func, msg
		);
	return (1);
}
