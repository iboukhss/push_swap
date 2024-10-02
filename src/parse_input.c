/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 00:52:43 by marvin            #+#    #+#             */
/*   Updated: 2024/09/28 17:42:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static int	get_num_negative(intmax_t *out, const char *s, intmax_t min)
{
	intmax_t	num;
	int			digit;

	if (!isdigit(*s))
		return (EINVAL);
	num = 0;
	while (isdigit(*s))
	{
		digit = *s - '0';
		if (num < (min + digit) / 10)
			return (EOVERFLOW);
		num = num * 10 - digit;
		++s;
	}
	*out = num;
	return (0);
}

static int	get_num_positive(intmax_t *out, const char *s, intmax_t max)
{
	intmax_t	num;
	int			digit;

	if (!isdigit(*s))
		return (EINVAL);
	num = 0;
	while (isdigit(*s))
	{
		digit = *s - '0';
		if (num > (max - digit) / 10)
			return (EOVERFLOW);
		num = num * 10 + digit;
		++s;
	}
	*out = num;
	return (0);
}
bool	is_range(const char *s, intmax_t min, intmax_t max)
{
	intmax_t	num;
	char		sign;
	int			err;

	sign = *s;
	if (*s == '-' || *s == '+')
		++s;
	if (sign == '-')
	{
		err = get_num_negative(&num, s, min);
	}
	else
	{
		err = get_num_positive(&num, s, max);
	}
	errno = err;
	return (!err && (num >= min && num <= max));
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	is_range(argv[1], INTMAX_MIN, INTMAX_MAX) ? puts("yes") : printf("no\nError: %s\n", strerror(errno));
	return (0);
}
