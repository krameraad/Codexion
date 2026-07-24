/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   defs.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/16 23:20:50 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/24 14:06:02 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

# include <pthread.h>

/** @brief Scheduling policies used when arbitrating dongle ownership. */
typedef enum e_scheduler
{
	/** No scheduling policy selected. */
	NONE,
	/** First-In, First-Out scheduling. */
	FIFO,
	/** Earliest Deadline First scheduling. */
	EDF
}	t_scheduler;

/** @brief Possible execution states of a coder. */
typedef enum e_coderstate
{
	/** The coder is idle and not performing any task. */
	FREE,
	/** The coder is currently compiling code. */
	COMPILING,
	/** The coder is currently debugging code. */
	DEBUGGING,
	/** The coder is currently refactoring code. */
	REFACTORING
}	t_coderstate;

/** @brief Represents a single shared dongle. */
typedef struct s_dongle
{
	/** @brief Mutex protecting access to this dongle's state. */
	pthread_mutex_t	mutex;

	pthread_cond_t	cond;

	/** @brief Timestamp of the most recent release.
	 * 
	 * Used to enforce the configured cooldown period.
	 */
	time_t			available_at;
}	t_dongle;

/** @brief Represents a single coder participating in the simulation. */
typedef struct s_coder
{
	/** @brief Thread executing this coder's routine. */
	pthread_t		thread;

	/** @brief Unique identifier of the coder. */
	size_t			id;

	/** @brief Current execution state of the coder. */
	t_coderstate	state;

	/** @brief Number of completed compilations. */
	int				compiles;

	/** @brief Timestamp marking the beginning of the most recent compilation.
	 * 
	 * Used to determine the coder's burnout deadline.
	 */
	time_t			last_compile;

	/** @brief Pointer to the left adjacent dongle. */
	t_dongle		*dongle_left;

	/** @brief Pointer to the right adjacent dongle. */
	t_dongle		*dongle_right;
}	t_coder;

#endif // DEFS_H
