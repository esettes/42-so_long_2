/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-22 11:16:15 by rstancu           #+#    #+#             */
/*   Updated: 2025-10-22 11:16:15 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * Preserves signed zero (-0.0)
 * Comparisons with NaN are false (value != value)
 * For values >= 2pow52, double cannot represent fractional parts.
 * Double max integers representation = 2pow53
 * double -> long long -> truncate to 0 (3.9 --> 3)
 * floor (-5.1 --> -6), truncate (-5.1 --> -5) (going to 0)
 * 
 * Conversion of double to long long erase decimal part and aprox value
 * to zero. Then long long to doube makes that double value fits exactly in
 * double integer, without any lost.
 */
double	ft_floor(double value)
{
	const double	two_pow_52 = 4503599627370496.0;
	long long		trunc;
	double			int_part;

	if (value == 0.0)
		return (value);
	if (value != value)
		return (value);
	if (value >= two_pow_52 || value <= -two_pow_52)
		return (value);
	if (value < (double)LLONG_MIN || value > (double)LLONG_MAX)
		return (value);
	trunc = (long long)value;
	int_part = (double)trunc;
	if (int_part > value)
		return (int_part - 1.0);
	return (int_part);
}
