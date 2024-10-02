/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:08:14 by marvin            #+#    #+#             */
/*   Updated: 2024/10/03 01:30:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"
#include "libft.h"
#include "vector.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_pair
{
	ptrdiff_t	index;
	int			value;
}	t_pair;

typedef struct s_pairv
{
	t_pair		*data;
	ptrdiff_t	size;
	ptrdiff_t	len;
	ptrdiff_t	cap;
}	t_pairv;

static void pri_pair(void *elem)
{
	t_pair *pp;

	pp = elem;
	ft_printf("{%t, %d}", pp->index, pp->value);
}

static void	pri_int(void *elem)
{
	ft_printf("%d", *(int *)elem);
}

static void	pri_str(void *elem)
{
	ft_printf("%s", *(char **)elem);
}

static void	vector_print(void *vecptr, void (*pri_elem)(void *))
{
	t_vector	*v;
	char	*data;
	int		i;

	i = 0;
	v = (t_vector *)vecptr;
	data = (char *)v->data;
	while (i < v->len)
	{
		ft_printf("%d: ", i);
		pri_elem(data + (i * v->size));
		ft_printf("\n");
		++i;
	}
}

void	print_arena_dbg(t_arena *a)
{
	ft_dprintf(STDERR_FILENO, "----------------------------\n");
	ft_dprintf(STDERR_FILENO, "  In use:   %t bytes\n", a->pos - a->beg);
	ft_dprintf(STDERR_FILENO, "  Left:     %t bytes\n", a->end - a->pos);
	ft_dprintf(STDERR_FILENO, "  Capacity: %t bytes\n", a->end - a->beg);
	ft_dprintf(STDERR_FILENO, "----------------------------\n");
}

int	cmp_ints(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

int	cmp_pairs(const void *a, const void *b)
{
	const t_pair	*pa;
	const t_pair	*pb;
	int	val_a;
	int	val_b;

	pa = a;
	pb = b;
	val_a = pa->value;
	val_b = pb->value;
	return (val_a - val_b);
}

// Split args with space delimiter.
static int check_args(t_arena *a, t_intv *out, char **argv, int argc)
{
	t_arena	*temp;
	t_strv	*args;
	int		err;

	temp = arena_new(ARENA_SIZE);
	if (argc == 2)
		args = strv_split(temp, argv[1], ' ');
	else
		args = strv_ndup(temp, argv + 1, argc - 1);
	err = intv_parse(a, out, args);
	arena_release(temp);
	return (err);
}

t_pairv	*pairv_new(t_arena *a, t_intv *iv)
{
	t_pairv		*new;
	t_pair		elem;
	ptrdiff_t	i;

	new = arena_alloc(a, sizeof(*new));
	new = vector_new(a, iv->len, sizeof(t_pair));
	i = 0;
	while (i < iv->len)
	{
		elem.index = i;
		elem.value = iv->data[i];
		vector_push(a, new, &elem);
		++i;
	}
	return (new);
}

static bool	is_duplicate(t_pairv *pairs)
{
	ptrdiff_t	i;

	i = 0;
	while (i < pairs->len - 1)
	{
		if (pairs->data[i].value == pairs->data[i + 1].value)
			return (true);
		++i;
	}
	return (false);
}

static int	normalize(t_intv *ints)
{
	t_arena		*temp;
	t_pairv		*pairs;
	ptrdiff_t	i;

	temp = arena_new(ARENA_SIZE);
	pairs = pairv_new(temp, ints);
	ft_qsort(pairs->data, pairs->len, pairs->size, cmp_pairs);
	if (is_duplicate(pairs))
	{
		arena_release(temp);
		return (1);
	}
	i = 0;
	while (i < ints->len)
	{
		ints->data[pairs->data[i].index] = i;
		++i;
	}
	arena_release(temp);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_arena	*perm;
	t_intv	ints;
	int		err;

	if (argc < 2)
		return (EXIT_FAILURE);

	perm = arena_new(ARENA_SIZE);
	print_arena_dbg(perm);

	ft_printf("Array:\n");
	err = check_args(perm, &ints, argv, argc);
	if (err)
	{
		write(STDOUT_FILENO, "Error\n", 6);
		print_arena_dbg(perm);
		arena_release(perm);
		return (EXIT_FAILURE);
	}
	vector_print(&ints, pri_int);

	ft_printf("Normalized array:\n");
	err = normalize(&ints);
	if (err)
	{
		write(STDOUT_FILENO, "Error\n", 6);
		print_arena_dbg(perm);
		arena_release(perm);
		return (EXIT_FAILURE);	
	}
	vector_print(&ints, pri_int);

	print_arena_dbg(perm);
	arena_release(perm);
	return (0);
}
