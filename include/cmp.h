/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmp.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/17 11:26:30 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/21 17:32:59 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMP_H
# define CMP_H

/**
 * @brief Swap two objects using void pointers.
 * 
 * @param a First object.
 * @param b Second object.
 */
void	swap(void **a, void **b);

/**
 * @brief Comparator function, comparing two integers using pointers.
 * 
 * @param a First integer.
 * @param b Second integer.
 * @return 0 if `(a == b)`, >0 if `(a > b)`, <0 if `(a < b)`.
 */
int		cmp_int(const void *a, const void *b);

#endif // CMP_H
