/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   context.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/15 16:33:21 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/16 23:22:32 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_H
# define CONTEXT_H

# include "defs.h"
# include <pthread.h>
# include <stdbool.h>

/* Initialize the context using arguments from the command line.
Can fail, in which case it returns `NULL` and prints a message. */
t_context	*context_new(char const **args);
/* Print the context's values. */
void		context_print(t_context *ctx);
/* Free all memory related to the context. */
void		context_free(t_context *ctx);

#endif // CONTEXT_H
