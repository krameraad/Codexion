/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/04/29 19:53:06 by ekramer       #+#    #+#                 */
/*   Updated: 2026/04/29 22:29:50 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/* Return `true` if `c` is in `s`, else `false`. */
static bool	is_in(char c, char const *s)
{
	while (*s)
	{
		if (c == *s)
			return (true);
		++s;
	}
	return (false);
}

int	atou(char const *s)
{
	char const	*str;

	str = s;
	while (*s)
	{
		if (!is_in(*s, "0123456789"))
			return (-1);
		++s;
	}
	return (atoi(str));
}

t_scheduler	get_scheduler(char const *s)
{
	if (!strcmp(s, "fifo"))
		return (FIFO);
	if (!strcmp(s, "edf"))
		return (EDF);
	return (NONE);
}
