/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coder.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/15 16:37:43 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/17 14:26:23 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
# define CODER_H

# include "defs.h"

# define LOG_DONGLE "has taken a dongle"
# define LOG_COMPILE "is compiling"
# define LOG_DEBUG "is debugging"
# define LOG_REFACTOR "is refactoring"
# define LOG_BURNOUT "burned out"

/* Coder function loop. */
void		*coder(void *arg);

#endif // CODER_H
