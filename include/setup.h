/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/15 16:58:32 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/17 14:33:06 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETUP_H
# define SETUP_H

# include "defs.h"

/* Return an array of coders made from the arguments in `ctx`.
Can fail, in which case it returns `NULL` and prints a message. */
t_coder		*setup_coders(t_context *ctx);

/* Return an array of dongles made from the arguments in `ctx`.
Can fail, in which case it returns `NULL` and prints a message. */
t_dongle	*setup_dongles(int count);

#endif // SETUP_H
