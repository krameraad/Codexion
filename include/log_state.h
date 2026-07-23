/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   log_state.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/23 15:56:03 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/23 15:58:33 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_STATE_H
# define LOG_STATE_H

# include <sys/time.h>
# include <stddef.h>

# define LOG_DONGLE "has taken a dongle"
# define LOG_COMPILE "is compiling"
# define LOG_DEBUG "is debugging"
# define LOG_REFACTOR "is refactoring"
# define LOG_BURNOUT "burned out"

static int	log_state(time_t t, size_t id, char const *msg);

#endif // LOG_STATE_H
