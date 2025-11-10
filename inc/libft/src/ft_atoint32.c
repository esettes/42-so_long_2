/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoint32.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-22 11:59:47 by rstancu           #+#    #+#             */
/*   Updated: 2025-10-22 11:59:47 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*skip_spaces(const char *p)
{
	while (*p && ft_isspace((unsigned char)*p))
		p++;
	return (p);
}

bool	ft_atoint32(const char *str, int32_t *out_value)
{
	const char	*p = str;
	long long	accumulator;
	int			sign;
	int			digit_count;
	int			digit;

	accumulator = 0;
	sign = 1;
	p = skip_spaces(p);
	digit_count = 0;
	if (*p == '+' || *p == '-')
	{
		if (*p == '-')
			sign = -1;
		p++;
	}
	while (ft_isdigit((unsigned char)*p))
	{
		digit = *p - '0';
		digit_count++;
		if (accumulator > (LLONG_MAX - digit) / 10)
			return (false);
		accumulator = (accumulator * 10) + digit;
		if ((sign == 1 && accumulator > INT_MAX)
			|| (sign == -1 && -accumulator < INT_MIN))
			return (false);
		p++;
	}
	// p = skip_spaces(p);
	// if (*p)
	// 	return (false);
	if (digit_count == 0)
		return (false);
	*out_value = (int32_t)(sign * accumulator);
	return (true);
}
