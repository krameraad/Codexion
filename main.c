/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/04/29 18:52:43 by ekramer       #+#    #+#                 */
/*   Updated: 2026/04/29 22:36:41 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
# External functions:
## Threads
- pthread_create, pthread_join

## Mutexes
- pthread_mutex_init, pthread_mutex_lock,
pthread_mutex_unlock, pthread_mutex_destroy

## Condition variables
- pthread_cond_init, pthread_cond_wait, pthread_cond_timedwait,
pthread_cond_broadcast, pthread_cond_destroy

## General use
- gettimeofday, usleep, write, malloc, free,
printf, fprintf, strcmp, strlen, atoi, memset
*/

#include "codexion.h"

int	main(int argc, char const *argv[])
{
	t_context	*ctx;

	if (argc != 9)
		return (fprintf(stderr, ESC_R "Number of arguments must be 8.\n"), 1);
	ctx = context_new(argv);
	if (ctx == NULL)
		return (fprintf(stderr, ESC_R "Arguments are invalid.\n"), 1);
	return (0);
}
