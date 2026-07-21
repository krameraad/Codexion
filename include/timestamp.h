/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   timestamp.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/15 15:27:32 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/18 20:21:24 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMESTAMP_H
# define TIMESTAMP_H

# include <sys/time.h>

/**
 * @brief Get the current program time in milliseconds.
 * 
 * The first time this function is run,
 * it sets an anchor, making the time at that point always 0.
 * All future timestamps are offset from that point.
 * 
 * @return Run time in milliseconds.
 */
time_t	timestamp(void);

#endif // TIMESTAMP_H