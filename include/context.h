/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   context.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/15 16:33:21 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/17 16:03:04 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_H
# define CONTEXT_H

# include "defs.h"
# include <pthread.h>
# include <stdbool.h>

/**
 * @brief Initialize the context using arguments from the command line.
 * 
 * @param args Program arguments.
 * @return Context object containing the parsed data.
 */
t_context	*context_new(char const **args);

/**
 * @brief Print the contents of a context.
 *
 * @param ctx Context to print.
 */
void		context_print(t_context *ctx);

/**
 * @brief Destroy a context and its associated resources.
 *
 * @param ctx Context to destroy.
 */
void		context_free(t_context *ctx);

#endif // CONTEXT_H
