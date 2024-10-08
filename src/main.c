/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:08:14 by marvin            #+#    #+#             */
/*   Updated: 2024/10/08 19:20:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "debug.h"

#include "libft.h"
#include "vector.h"

#include <stdlib.h>		// EXIT_FAILURE
#include <unistd.h>		// write()

int	g_ops = 0;


static void	stacks_init(t_alloc handle, t_stacks *stacks, t_intv *ints)
{
	stacks->a = cirbuf_vdup(handle.perm, ints);
	stacks->b = cirbuf_new(handle.perm, ints->len, ints->size);
}

int	main(int argc, char **argv)
{
	t_alloc		handle;
	t_stacks	stacks;
	t_intv		ints;
	int			err;

	if (argc < 2)
		return (EXIT_FAILURE);

	allocator_init(&handle, ARENA_SIZE);
	err = process_input(handle, &ints, argv, argc);
	if (err)
	{
		write(STDERR_FILENO, "Error\n", 6);
		allocator_destroy(handle);
		return (1);
	}

	stacks_init(handle, &stacks, &ints);

	print_stacks(stacks);

	// GOAL: keep building a LIS on stack A

	int min, max, curr_a, curr_b;

	int last_a;

	min = max = *(int *)cirbuf_front(stacks.a);
	rotate_a(handle, stacks);

	curr_a = *(int *)cirbuf_front(stacks.a);

	// not the best condition right now
	while (curr_a != min)
	{
		if (curr_a > max)
		{
			max = curr_a;
			rotate_a(handle, stacks);
		}
		else
		{
			if (cirbuf_is_empty(stacks.b))
				push_b(stacks);
			else
			{
				curr_b = *(int *)cirbuf_front(stacks.b);

				if (curr_a > curr_b)
				{
					push_b(stacks);
				}
				else
				{
					// reinsert now
					// this is where the complication begins..
					print_stacks(stacks);
					while (!cirbuf_is_empty(stacks.b))
					{
						curr_b = *(int *)cirbuf_front(stacks.b);
						last_a = *(int *)cirbuf_back(stacks.a);
						if (last_a > curr_b)
							reverse_rotate_a(handle, stacks);
						else
							push_a(stacks);
					}
					break ;
				}
			}
		}
		// curr a can never be empty because we start with min = max
		curr_a = *(int *)cirbuf_front(stacks.a);
	}
	
	print_stacks(stacks);

	/*
	int pivot = (0 + stacks.a->len - 1) / 2;
	divide_a_recursive(handle, stacks, 0, stacks.a->len - 1);
	reinsert_a(handle, stacks, pivot);
	divide_b_recursive(handle, stacks, 0, pivot);
	reinsert_b(handle, stacks, pivot);
	*/

	//print_stacks(stacks);
	
	print_alloc_dbg(handle);
	allocator_destroy(handle);
	ft_printf("Total operations: %d\n", g_ops);
	return (0);
}
