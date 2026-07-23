/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   context.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/15 16:33:21 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/23 14:19:42 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_H
# define CONTEXT_H

# include "defs.h"

/** @brief Global configuration and shared state for the simulation. */
typedef struct s_context
{
	/** @brief Number of coders. Also the number of dongles. */
	int				number_of_coders;

	/**
	 * @brief Time it takes for a coder to burn out, in milliseconds.
	 * 
	 * If a coder doesn't start compiling before this amount of time passes,
	 * counted from the beginning of the simulation or from their last compile,
	 * they burn out and the simulation stops.
	 */
	int				time_to_burnout;

	/**
	 * @brief Duration of a compilation, in milliseconds.
	 *
	 * A coder must hold both adjacent dongles while compiling.
	 * After compiling, the coder transitions to debugging.
	 */
	int				time_to_compile;

	/**
	 * @brief Duration of debugging, in milliseconds.
	 *
	 * After debugging, the coder transitions to refactoring.
	 */
	int				time_to_debug;

	/**
	 * @brief Duration of refactoring, in milliseconds.
	 *
	 * After refactoring, the coder attempts to acquire dongles
	 * for the next compilation.
	 */
	int				time_to_refactor;

	/**
	 * @brief Number of successful compilations required per coder.
	 *
	 * The simulation terminates once every coder reaches this count.
	 */
	int				number_of_compiles_required;

	/**
	 * @brief Cooldown period after a dongle is released, in milliseconds.
	 *
	 * During this interval the dongle cannot be acquired.
	 */
	int				dongle_cooldown;

	/**
	 * @brief Scheduling policy used to arbitrate dongle requests.
	 *
	 * - ::FIFO grants the dongle to the earliest requester.
	 * - ::EDF grants the dongle to the requester with the earliest
	 *   burnout deadline, calculated as:
	 *   `last_compile + time_to_burnout`.
	 */
	t_scheduler		scheduler;

	/** @brief Mutex used to serialize console output. */
	pthread_mutex_t	print_mutex;
}	t_context;

t_context	*context(void);

int			context_destroy(void);

#endif // CONTEXT_H
