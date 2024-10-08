/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 22:59:20 by marvin            #+#    #+#             */
/*   Updated: 2024/10/07 03:05:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "push_swap.h"

void	print_alloc_dbg(t_alloc handle);
void	print_stacks(t_stacks stacks);

void	vector_print(void *vecptr, void (*pri_elem)(void *));

void	pri_pair(void *elem);
void	pri_int(void *elem);
void	pri_str(void *elem);

#endif
