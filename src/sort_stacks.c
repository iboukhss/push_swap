/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stacks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 22:54:14 by marvin            #+#    #+#             */
/*   Updated: 2024/10/07 03:33:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "debug.h"

#include "cirbuf.h"
#include "libft.h"

void	divide_a_recursive(t_alloc handle, t_stacks stacks, int min, int max)
{
	int	pivot;

	pivot = (min + max) / 2;
	ft_printf("----------------------------\n");
	ft_printf("pivot: %d, min: %d, max: %d\n", pivot, min, max);
	ft_printf("----------------------------\n");
	if (stacks.a->len <= 1)
		return ;
	// Using a property of the pivot value here?
	// Not sure if it's a good idea, I say yes?? Isn't all my code based on
	// the convenient properties of pivot values in a perfectly aligned stack?
	while (stacks.b->len < pivot + 1)
	{
		if (*(int *)cirbuf_front(stacks.a) <= pivot)
			push_b(stacks);
		else
			rotate_a(handle, stacks);
		// This is the "push / swap" idea.
		if (stacks.b->len >= 2)
		{
			int first_b = *(int *)cirbuf_at(stacks.b, 0);
			int second_b = *(int *)cirbuf_at(stacks.b, 1);
			if (first_b < second_b)
				swap_b(handle, stacks);
		}
	}
	print_stacks(stacks);
	divide_a_recursive(handle, stacks, pivot + 1, max);
}

//
///
/// PART 1
///
//

int	find_rotation_b(t_stacks stacks, int target)
{
	int	half;
	int	i;

	// +1 to be safe but i never see this being an issue
	half = stacks.b->len / 2 + 1;
	i = 0;
	while (i < half)
	{
		if (*(int *)cirbuf_at(stacks.b, i) == target)
			return (1);
		++i;
	}
	return (-1);
}

//
///
/// PART 1
///
//

void	reinsert_a(t_alloc handle, t_stacks stacks, int pivot)
{
	int	target;
	int	rotate;

	while (stacks.b->len > pivot + 1)
	{
		target = *(int *)cirbuf_front(stacks.a) - 1;
		rotate = find_rotation_b(stacks, target);
		while (*(int *)cirbuf_front(stacks.b) != target)
		{
			if (stacks.b->len >= 2)
			{
				int first_b = *(int *)cirbuf_at(stacks.b, 0);
				int second_b = *(int *)cirbuf_at(stacks.b, 1);
				if (first_b < second_b)
				{
					swap_b(handle, stacks);
					continue ;
				}
			}
			if (rotate > 0)
				rotate_b(handle, stacks);
			else
				reverse_rotate_b(handle, stacks);
		}
		push_a(stacks);
		print_stacks(stacks);
	}
}

//
///
/// PART 2
///
//

void	sort_two(t_alloc handle, t_stacks stacks)
{
	int	a;
	int	b;

	a = *(int *)cirbuf_front(stacks.b);
	b = *(int *)cirbuf_back(stacks.b);
	if (a < b)
		swap_b(handle, stacks);
}

// IDEA: implement the optimal rotation for dividing also basically presorting the stacks
void	divide_b_recursive(t_alloc handle, t_stacks stacks, int min, int max)
{
	int	pivot;

	pivot = (min + max) / 2;
	ft_printf("----------------------------\n");
	ft_printf("pivot: %d, min: %d, max: %d\n", pivot, min, max);
	ft_printf("----------------------------\n");
	if (stacks.b->len == 2)
	{
		sort_two(handle, stacks);
		return ;
	}
	if (stacks.b->len <= 1)
		return ;
	while (stacks.b->len > pivot)
	{
		if (*(int *)cirbuf_front(stacks.b) >= pivot)
			push_a(stacks);
		else
			rotate_b(handle, stacks);
		if (stacks.a->len >= 2)
		{
			int first_a = *(int *)cirbuf_at(stacks.a, 0);
			int second_a = *(int *)cirbuf_at(stacks.a, 1);
			if (first_a > second_a)
				swap_a(handle, stacks);
		}
	}
	print_stacks(stacks);
	divide_b_recursive(handle, stacks, min, pivot - 1);
}

//
///
/// PART 2
///
//

int	find_rotation_a(t_stacks stacks, int target)
{
	int	half;
	int	i;

	half = stacks.a->len / 2 + 1;
	i = 0;
	while (i < half)
	{
		if (*(int *)cirbuf_at(stacks.a, i) == target)
			return (1);
		++i;
	}
	return (-1);
}

//
///
/// PART 2
///
//

void	reinsert_b(t_alloc handle, t_stacks stacks, int pivot)
{
	int	target;
	int	rotate;

	while (stacks.b->len < pivot + 1)
	{
		target = *(int *)cirbuf_front(stacks.b) + 1;
		rotate = find_rotation_a(stacks, target);
		while (*(int *)cirbuf_front(stacks.a) != target)
		{
			if (rotate > 0)
				rotate_a(handle, stacks);
			else
				reverse_rotate_a(handle, stacks);
		}
		push_b(stacks);
		print_stacks(stacks);
	}
}
