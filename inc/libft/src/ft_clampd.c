/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clampd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-06 14:28:32 by rstancu           #+#    #+#             */
/*   Updated: 2025-11-06 14:28:32 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_clampd(double x, double lo, double hi)
{
	if (x < lo)
		return (lo);
	else if (x > hi)
		return (hi);
	return (x);
}
