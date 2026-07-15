/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   traceback.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/15 16:05:15 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/15 17:41:54 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACEBACK_H
# define TRACEBACK_H

# define ERR "An error occurred."
# define ERR_MEM "Failed to allocate memory."
# define ERR_THRD "Failed to create a thread."
# define ERR_ARGC "Number of arguments must be 8."
# define ERR_ARGV "Arguments are invalid (must be ints above 0 and fifo/edf)."

/* Red terminal formatting. */
# define ESC_R "\033[91m"
/* Remove terminal formatting. */
# define ESC_X "\033[0m"

/* Print an error message with the function that failed and return 1. */
int	traceback(char const *msg, char const *func);

#endif // TRACEBACK_H
