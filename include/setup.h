/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/15 16:58:32 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/22 20:28:13 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETUP_H
# define SETUP_H

# include "defs.h"

int			setup_context(char const **args);

/**
 * @brief Set up an array of dongles.
 * 
 * @param count Amount of dongles to create.
 * @return Array of dongles, or `NULL` on failure.
 */
t_dongle	*setup_dongles(int count);

/**
 * @brief Set up an array of coders.
 * 
 * @param ctx Context with info to build the array from.
 * @return Array of coders, or `NULL` on failure.
 */
t_coder		*setup_coders(int count, t_dongle **dongles);

#endif // SETUP_H
