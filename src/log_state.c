/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   log_state.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/23 15:55:24 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/23 21:40:57 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include <stdio.h>

int	log_state(time_t t, size_t id, char const *msg)
{
	int	result;

	pthread_mutex_lock(&context()->print_mutex);
	result = printf("%zu %lu %s\n", t, id, msg);
	pthread_mutex_unlock(&context()->print_mutex);
	return (result);
}
