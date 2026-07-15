/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coder.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/15 16:37:43 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/15 19:30:10 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
# define CODER_H

# include "context.h"
# include <sys/time.h>
# include <stdbool.h>

# define LOG_DONGLE "has taken a dongle"
# define LOG_COMPILE "is compiling"
# define LOG_DEBUG "is debugging"
# define LOG_REFACTOR "is refactoring"
# define LOG_BURNOUT "burned out"

typedef enum e_coderstate
{
	FREE,
	COMPILING,
	DEBUGGING,
	REFACTORING
}	t_coderstate;

/* Represents data of a coder. */
typedef struct s_coder
{
	pthread_t		thread;
	size_t			id;
	t_coderstate	state;
	int				compiles;
	time_t			last_compile;
	t_context		*ctx;
	t_dongle		*dongle_left;
	t_dongle		*dongle_right;
}	t_coder;

/* Coder function loop. */
void		*coder(void *arg);

#endif // CODER_H
