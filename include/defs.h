/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   defs.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/16 23:20:50 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/22 20:29:05 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

# include <stdbool.h>
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

	/** @brief Indicates whether the dongle is currently available. */
	bool			available;

	/** @brief Timestamp of the most recent release.
	 * 
	 * Used to enforce the configured cooldown period.
	 */
	time_t			last_drop_time;
}	t_dongle;

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
