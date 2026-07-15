/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/15 16:22:52 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/15 16:50:34 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_H
# define GET_H

# include "context.h"

/* Return `s` as an int if it's a valid unsigned integer, else -1. */
int			atou(char const *s);
/* Return scheduler as an enum `t_scheduler`. If invalid, return `NONE`. */
t_scheduler	get_scheduler(char const *s);

#endif // GET_H
