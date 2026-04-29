/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   codexion.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/04/29 19:00:05 by ekramer       #+#    #+#                 */
/*   Updated: 2026/04/29 23:49:36 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# define _DEFAULT_SOURCE
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>

/* Red terminal formatting. */
# define ESC_R "\033[91m"
/* Remove terminal formatting. */
# define ESC_X "\033[0m"

# define ERR_MEM "Failed to allocate memory."
# define ERR_ARGC "Number of arguments must be 8."
# define ERR_ARGV "Arguments are invalid (must be ints above 0 and fifo/edf)."

typedef enum e_coderstate
{
	COMPILING,
	DEBUGGING,
	REFACTORING
}	t_coderstate;

typedef enum e_scheduler
{
	NONE,
	FIFO,
	EDF
}	t_scheduler;

typedef struct s_context
{
	/* Number of coders. Also the number of dongles. */
	int			number_of_coders;

	/* Coders burn out if they didn't start compiling within
	`time_to_burnout` milliseconds since the beginning of
	their last compile or the beginning of the simulation. */
	int			time_to_burnout;

	/* Time in milliseconds that it takes for a coder to compile.
	Coder must hold two dongles to compile.
	Coder will start debugging after compiling. */
	int			time_to_compile;

	/* Time in milliseconds that it takes for a coder to debug.
	Coder will start refactoring after debugging. */
	int			time_to_debug;

	/* Time in milliseconds that it takes for a coder to refactor.
	Coder will try to acquire dongles after refactoring. */
	int			time_to_refactor;

	/* Simulation stops if all coders have compiled this many times. */
	int			number_of_compiles_required;

	/* Time in milliseconds that a dongle is unavailable after release. */
	int			dongle_cooldown;

	/* Arbitration policy used by dongles to decide who gets them
	when multiple coders request them.
	- fifo: Coder whose request arrived first. 
	- edf: Earliest deadline first, with
	deadline = `last_compile_start` + `time_to_burnout` */
	t_scheduler	scheduler;
}	t_context;

typedef struct s_coder
{
	t_coderstate	state;
	struct s_coder	*prev;
	struct s_coder	*next;
}	t_coder;

typedef struct s_dongle
{
	bool	available;
}	t_dongle;

/* Return `s` as an int if it's a valid unsigned integer, else -1. */
int			atou(char const *s);

/* Return scheduler as an enum `t_scheduler`. If invalid, return `NONE`. */
t_scheduler	get_scheduler(char const *s);

/* Initialize the context using arguments from the command line.
Can fail, in which case it returns `NULL` and prints a message. */
t_context	*context_new(char const **args);

/* Print the context's values. */
void		context_print(t_context *ctx);

/* Print an error message with the function that failed and return 1. */
int			error(char const *msg, char const *func);

#endif
