/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lerp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-07 13:57:49 by rstancu           #+#    #+#             */
/*   Updated: 2025-11-07 13:57:49 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Linearly interpolates between a and b by t.
 * @param a The start value.
 * @param b The end value.
 * @param t The interpolation factor (0.0 to 1.0).
 * @return The interpolated value.
 */
double	ft_lerp(double a, double b, double t)
{
	return (a + (b - a) * t);
}
