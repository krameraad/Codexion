/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/15 16:22:52 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/23 14:31:45 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_H
# define GET_H

# include "defs.h"

/**
 * @brief Variant of `atoi()` that should return only positive integers.
 * 
 * @param s String to convert.
 * @return Converted positive integer, or -1 on failure.
 */
int			atou(char const *s);

/**
 * @brief Get a valid scheduler type as an enum.
 * 
 * @param s String to parse into the scheduler type.
 * @return Enum equivalent of the scheduler name.
 */
t_scheduler	get_scheduler(char const *s);

#endif // GET_H
