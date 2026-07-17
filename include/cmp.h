/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmp.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ekramer <ekramer@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/17 11:26:30 by ekramer       #+#    #+#                 */
/*   Updated: 2026/07/17 14:37:18 by ekramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMP_H
# define CMP_H

/* Swap two objects using void pointers. */
void	swap(void **a, void **b);

/* Compare two integers. */
int		cmp_int(const void *a, const void *b);

#endif // CMP_H
