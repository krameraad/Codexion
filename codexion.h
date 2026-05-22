/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   codexion.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/04/29 19:00:05 by ekramer       #+#    #+#                 */
/*   Updated: 2026/05/22 21:35:59 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

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
# define ERR_THRD "Failed to create a thread."
# define ERR_ARGC "Number of arguments must be 8."
# define ERR_ARGV "Arguments are invalid (must be ints above 0 and fifo/edf)."

// ENUMS ----------------------------------------------------------------------
typedef enum e_coderstate
{
	FREE,
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

// STRUCTS --------------------------------------------------------------------
/* Represents data of a dongle. */
typedef struct s_dongle
{
	bool	available;
	time_t	last_drop_time;
}	t_dongle;

/* Contains general info for the simulation. */
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
	when multiple coders request a dongle.
	- fifo: Coder whose request arrived first. 
	- edf: Earliest deadline first, with
	deadline = `last_compile_start` + `time_to_burnout` */
	t_scheduler	scheduler;
}	t_context;	

/* Represents data of a coder. */
typedef struct s_coder
{
	pthread_t		thread;
	size_t			id;
	t_coderstate	state;
	size_t			compiles;
	time_t			last_compile_time;
	t_context		*ctx;
}	t_coder;

// CODER.C --------------------------------------------------------------------
/* Coder function loop. */
void		*coder(void *arg);

// CONTEXT.C ------------------------------------------------------------------
/* Initialize the context using arguments from the command line.
Can fail, in which case it returns `NULL` and prints a message. */
t_context	*context_new(char const **args);
/* Print the context's values. */
void		context_print(t_context *ctx);

// DEBUG.C --------------------------------------------------------------------
/* Print a coder's values. */
void		coder_print(t_coder *coder);

// ERROR.C --------------------------------------------------------------------
/* Print an error message with the function that failed and return 1. */
int			error(char const *msg, char const *func);

// GET.C ----------------------------------------------------------------------
/* Return `s` as an int if it's a valid unsigned integer, else -1. */
int			atou(char const *s);
/* Return scheduler as an enum `t_scheduler`. If invalid, return `NONE`. */
t_scheduler	get_scheduler(char const *s);

// SETUP.C --------------------------------------------------------------------
/* Return an array of coders made from the arguments in `ctx`.
Can fail, in which case it returns `NULL` and prints a message. */
t_coder		*setup_coders(t_context *ctx);

// TIME.C ---------------------------------------------------------------------
/* Returns a `time_t` value that represents a timestamp in milliseconds. */
time_t		timestamp(void);

#endif
