/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/04/29 23:17:54 by ekramer       #+#    #+#                 */
/*   Updated: 2026/05/27 20:53:29 by ekramer       ########   odam.nl         */
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

int	log_state(pthread_mutex_t *mutex, time_t t, size_t id, char const *msg)
{
	int	result;

	pthread_mutex_lock(mutex);
	printf("HELP!\n");
	result = printf("%zu %lu %s\n", t, id, msg);
	pthread_mutex_unlock(mutex);
	return (result);
}
