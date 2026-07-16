/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   defs.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/16 23:20:50 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/16 23:24:52 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

# include <stdbool.h>
# include <pthread.h>

typedef enum e_scheduler
{
	NONE,
	FIFO,
	EDF
}	t_scheduler;

typedef enum e_coderstate
{
	FREE,
	COMPILING,
	DEBUGGING,
	REFACTORING
}	t_coderstate;

/* Represents data of a dongle. */
typedef struct s_dongle
{
	pthread_mutex_t	mutex;
	bool			available;
	time_t			last_drop_time;
}	t_dongle;

/* Contains general info for the simulation. */
typedef struct s_context
{
	/* Number of coders. Also the number of dongles. */
	int				number_of_coders;
	/* Coders burn out if they didn't start compiling within
	`time_to_burnout` milliseconds since the beginning of
	their last compile or the beginning of the simulation. */
	int				time_to_burnout;
	/* Time in milliseconds that it takes for a coder to compile.
	Coder must hold two dongles to compile.
	Coder will start debugging after compiling. */
	int				time_to_compile;
	/* Time in milliseconds that it takes for a coder to debug.
	Coder will start refactoring after debugging. */
	int				time_to_debug;
	/* Time in milliseconds that it takes for a coder to refactor.
	Coder will try to acquire dongles after refactoring. */
	int				time_to_refactor;
	/* Simulation stops if all coders have compiled this many times. */
	int				number_of_compiles_required;
	/* Time in milliseconds that a dongle is unavailable after release. */
	int				dongle_cooldown;
	/* Arbitration policy used by dongles to decide who gets them
	when multiple coders request a dongle.
	- fifo: Coder whose request arrived first.
	- edf: Earliest deadline first, with
	deadline = `last_compile_start` + `time_to_burnout` */
	t_scheduler		scheduler;
	/* Array of all dongles. */
	t_dongle		*dongles;
	/* Mutex to guard print statements. */
	pthread_mutex_t	print_mutex;
}	t_context;

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

#endif // DEFS_H
