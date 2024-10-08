/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate_ops.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 04:41:04 by marvin            #+#    #+#             */
/*   Updated: 2024/10/07 04:41:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#include "libft.h"

void	reverse_rotate_a(t_alloc handle, t_stacks stacks)
{
	g_ops += 1;
	cirbuf_shift_right(handle, stacks.a);
	ft_puts("rra");
}

void	reverse_rotate_b(t_alloc handle, t_stacks stacks)
{
	g_ops += 1;
	cirbuf_shift_right(handle, stacks.b);
	ft_puts("rrb");
}

void	reverse_rotate_both(t_alloc handle, t_stacks stacks)
{
	g_ops += 1;
	cirbuf_shift_right(handle, stacks.a);
	cirbuf_shift_right(handle, stacks.b);
	ft_puts("rrr");
}
