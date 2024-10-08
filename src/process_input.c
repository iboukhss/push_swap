/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 23:24:03 by marvin            #+#    #+#             */
/*   Updated: 2024/10/07 03:03:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#include "libft.h"

// Split args with space delimiter.
int check_args(t_alloc handle, t_intv *ints, char **argv, int argc)
{
	t_strv	*args;
	int		err;

	if (argc == 2)
	{
		args = strv_split(&handle.temp, argv[1], ' ');
	}
	else
	{
		args = strv_ndup(&handle.temp, argv + 1, argc - 1);
	}
	err = intv_parse(handle.perm, ints, args);
	return (err);
}

// Make new index value pairs from integer vector.
static t_ivalv	*ivalv_new(t_arena *a, t_intv *ints)
{
	t_ivalv		*ivals;
	t_ival		elem;
	ptrdiff_t	i;

	i = 0;
	ivals = arena_alloc(a, sizeof(*ivals));
	ivals = vector_new(a, ints->len, sizeof(t_ival));
	while (i < ints->len)
	{
		elem.index = i;
		elem.value = ints->data[i];
		vector_push(a, ivals, &elem);
		++i;
	}
	return (ivals);
}

static bool	is_duplicate(t_ivalv *ivals)
{
	ptrdiff_t	i;

	i = 0;
	while (i < ivals->len - 1)
	{
		if (ivals->data[i].value == ivals->data[i + 1].value)
			return (true);
		++i;
	}
	return (false);
}

// This method prevents integer overflow.
// https://stackoverflow.com/a/53821630/23471454
static int	cmp_ivals(const void *a, const void *b)
{
	int	val_a;
	int	val_b;

	val_a = ((const t_ival *)a)->value;
	val_b = ((const t_ival *)b)->value;
	return ((val_a > val_b) - (val_a < val_b));
}

int	normalize_array(t_alloc handle, t_intv *ints)
{
	t_ivalv		*ivals;
	ptrdiff_t	i;

	ivals = ivalv_new(&handle.temp, ints);
	ft_qsort(ivals->data, ivals->len, ivals->size, cmp_ivals);
	if (is_duplicate(ivals))
	{
		return (1);
	}
	i = 0;
	while (i < ints->len)
	{
		ints->data[ivals->data[i].index] = i;
		++i;
	}
	return (0);
}

int	process_input(t_alloc handle, t_intv *ints, char **argv, int argc)
{
	int	err;

	err = check_args(handle, ints, argv, argc);
	if (err)
		return (err);
	err = normalize_array(handle, ints);
	return (err);
}
