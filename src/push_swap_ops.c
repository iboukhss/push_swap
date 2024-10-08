/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_ops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:30:03 by marvin            #+#    #+#             */
/*   Updated: 2024/10/07 05:04:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#include "libft.h"

// NOTE: All cirbuf operations are safeguarded in a way that makes it
// impossible to dereference a NULL pointer. There is no error checking in
// stack operations except for those that need to be grouped together.

void	swap_a(t_alloc handle, t_stacks stacks)
{
	g_ops += 1;
	cirbuf_swap(handle, stacks.a, 0, 1);
	ft_puts("sa");
}

void	swap_b(t_alloc handle, t_stacks stacks)
{
	g_ops += 1;
	cirbuf_swap(handle, stacks.b, 0, 1);
	ft_puts("sb");
}

void	swap_both(t_alloc handle, t_stacks stacks)
{
	g_ops += 1;
	cirbuf_swap(handle, stacks.a, 0, 1);
	cirbuf_swap(handle, stacks.b, 0, 1);
	ft_puts("ss");
}

void	push_a(t_stacks stacks)
{
	g_ops += 1;
	if (!cirbuf_is_empty(stacks.b))
	{
		cirbuf_push_front(stacks.a, cirbuf_front(stacks.b));
		cirbuf_pop_front(stacks.b);
	}
	ft_puts("pa");
}

void	push_b(t_stacks stacks)
{
	g_ops += 1;
	if (!cirbuf_is_empty(stacks.a))
	{
		cirbuf_push_front(stacks.b, cirbuf_front(stacks.a));
		cirbuf_pop_front(stacks.a);
	}
	ft_puts("pb");
}
