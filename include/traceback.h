/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   traceback.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/15 16:05:15 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/23 13:49:51 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACEBACK_H
# define TRACEBACK_H

# define ERR "An error occurred."
# define ERR_MEM "Failed to allocate memory."
# define ERR_ARGC "Number of arguments must be 8."
# define ERR_ARGV "Arguments are invalid (must be ints above 0 and fifo/edf)."
# define ERR_THRC "Failed to create a thread."
# define ERR_THRJ "Failed to join a thread."
# define ERR_MTXI "Failed to initialize a mutex."
# define ERR_MTXD "Failed to destroy a mutex."

/** @brief Red terminal formatting. */
# define ESC_R "\033[91m"
/** @brief Remove all terminal formatting. */
# define ESC_X "\033[0m"

/**
 * @brief Print a short error message along with its origin.
 * 
 * @param msg Description of the type of error.
 * @param func Function the error originated from.
 * @return Always returns 1.
 */
int	traceback(char const *msg, char const *func);

#endif // TRACEBACK_H
