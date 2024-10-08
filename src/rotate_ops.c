/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 04:40:17 by marvin            #+#    #+#             */
/*   Updated: 2024/10/07 04:41:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#include "libft.h"

void	rotate_a(t_alloc handle, t_stacks stacks)
{
	g_ops += 1;
	cirbuf_shift_left(handle, stacks.a);
	ft_puts("ra");
}

void	rotate_b(t_alloc handle, t_stacks stacks)
{
	g_ops += 1;
	cirbuf_shift_left(handle, stacks.b);
	ft_puts("rb");
}

void	rotate_both(t_alloc handle, t_stacks stacks)
{
	g_ops += 1;
	cirbuf_shift_left(handle, stacks.a);
	cirbuf_shift_left(handle, stacks.b);
	ft_puts("rr");
}
