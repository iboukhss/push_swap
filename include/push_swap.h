/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:25:21 by marvin            #+#    #+#             */
/*   Updated: 2024/10/07 03:29:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "arena.h"
# include "cirbuf.h"
# include "vector.h"

extern int	g_ops;

// Indexed value type
typedef struct s_ival
{
	ptrdiff_t	index;
	int			value;
}	t_ival;

// Vector of pairs type
typedef struct s_ivalv
{
	t_ival		*data;
	ptrdiff_t	size;
	ptrdiff_t	len;
	ptrdiff_t	cap;
}	t_ivalv;

typedef struct s_stacks
{
	t_cirbuf	*a;
	t_cirbuf	*b;
}	t_stacks;

int		process_input(t_alloc handle, t_intv *ints, char **argv, int argc);

// First half
void	divide_a_recursive(t_alloc handle, t_stacks stacks, int min, int max);
int		find_rotation_b(t_stacks stacks, int target);
void	reinsert_a(t_alloc handle, t_stacks stacks, int pivot);

// Second half
void	divide_b_recursive(t_alloc handle, t_stacks stacks, int min, int max);
void	sort_two(t_alloc handle, t_stacks stacks);
int		find_rotation_a(t_stacks stacks, int target);
void	reinsert_b(t_alloc handle, t_stacks stacks, int pivot);

// Stack operations
void	swap_a(t_alloc handle, t_stacks stacks);
void	swap_b(t_alloc handle, t_stacks stacks);
void	swap_both(t_alloc handle, t_stacks stacks);
void	push_a(t_stacks stacks);
void	push_b(t_stacks stacks);
void	rotate_a(t_alloc handle, t_stacks stacks);
void	rotate_b(t_alloc handle, t_stacks stacks);
void	rotate_both(t_alloc handle, t_stacks stacks);
void	reverse_rotate_a(t_alloc handle, t_stacks stacks);
void	reverse_rotate_b(t_alloc handle, t_stacks stacks);
void	reverse_rotate_both(t_alloc handle, t_stacks stacks);

#endif
