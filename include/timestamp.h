/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   timestamp.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/15 15:27:32 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/15 16:01:17 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMESTAMP_H
# define TIMESTAMP_H

# include <sys/time.h>

/* Returns a `time_t` value that represents a timestamp in milliseconds. */
time_t	timestamp(void);

#endif // TIMESTAMP_H