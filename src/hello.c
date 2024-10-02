/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hello.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:44:07 by marvin            #+#    #+#             */
/*   Updated: 2024/09/28 20:39:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

static bool	is_overflow(int64_t num, int next_digit)
{
	if (num < 0)
	{
		return (num < (INT64_MIN + next_digit) / 10);
	}
	else
	{
		return (num > (INT64_MAX - next_digit) / 10);
	}
}

int	str_to_i64(int64_t *out, const char *str)
{
	int64_t	num;
	int		sign;
	int		digit;

	num = 0;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		++str;
	if (!isdigit(*str))
		return (EINVAL);
	while (isdigit(*str))
	{
		digit = *str - '0';
		if (is_overflow(num, digit))
			return (EOVERFLOW);
		num *= 10;
		num += sign * digit;
		++str;
	}
	*out = num;
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	int64_t out;
	int err = str_to_i64(&out, argv[1]);
	if (err)
	{
		printf("Error: %s\n", strerror(err));
		return (1);
	}
	printf("Int: %" PRIi64 "\n", out);
	return (0);
}
