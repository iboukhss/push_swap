/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 23:00:16 by marvin            #+#    #+#             */
/*   Updated: 2024/10/07 03:34:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

#include "libft.h"
#include "vector.h"

#include <unistd.h>

void	print_alloc_dbg(t_alloc handle)
{
	t_arena	*p;
	t_arena	*t;

	p = handle.perm;
	t = &handle.temp;

	ft_dprintf(STDERR_FILENO, "--PERMANENT-----------------\n");
	ft_dprintf(STDERR_FILENO, "  In use:   %t bytes\n", p->pos - p->beg);
	ft_dprintf(STDERR_FILENO, "  Left:     %t bytes\n", p->end - p->pos);
	ft_dprintf(STDERR_FILENO, "  Capacity: %t bytes\n", p->end - p->beg);
	ft_dprintf(STDERR_FILENO, "--TEMPORARY-----------------\n");
	ft_dprintf(STDERR_FILENO, "  In use:   %t bytes\n", t->pos - t->beg);
	ft_dprintf(STDERR_FILENO, "  Left:     %t bytes\n", t->end - t->pos);
	ft_dprintf(STDERR_FILENO, "  Capacity: %t bytes\n", t->end - t->beg);	
	ft_dprintf(STDERR_FILENO, "----------------------------\n");
}

void	print_stacks(t_stacks stacks)
{
	int len_a = stacks.a->len;
	int len_b = stacks.b->len;
	int max_len = (len_a > len_b) ? len_a : len_b;

	ft_printf("\n============================\n");
	ft_printf("A\tB\n");
	for (int i = 0; i < max_len; i++)
	{
		int *ia = cirbuf_at(stacks.a, i);
		int *ib = cirbuf_at(stacks.b, i);
		if (ia == NULL)
			ft_printf(".\t");
		else
			ft_printf("%d\t", *ia);
		if (ib == NULL)
			ft_printf(".\n");
		else
			ft_printf("%d\n", *ib);
	}
	ft_printf("============================\n\n");
}

void	vector_print(void *vecptr, void (*pri_elem)(void *))
{
	t_vector	*v;
	char		*data;
	int			i;

	i = 0;
	v = vecptr;
	data = v->data;
	while (i < v->len)
	{
		ft_printf("%d: ", i);
		pri_elem(data + (i * v->size));
		ft_printf("\n");
		++i;
	}
}

void	pri_int(void *elem)
{
	ft_printf("%d", *(int *)elem);
}

void	pri_str(void *elem)
{
	ft_printf("%s", *(char **)elem);
}
