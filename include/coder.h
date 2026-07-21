/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coder.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/15 16:37:43 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/18 20:06:35 by ekramer       ########   odam.nl         */
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

/**
 * @brief Coder main function loop.
 * 
 * @param arg Information of the coder. Should be an object of type `t_coder`.
 * @return `NULL`.
 */
void	*coder(void *arg);

#endif // CODER_H
