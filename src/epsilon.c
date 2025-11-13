/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epsilon.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-12 10:09:13 by rstancu           #+#    #+#             */
/*   Updated: 2025-11-12 10:09:13 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

double	compute_center_epsilon_px(double speed_px_s)
{
	double	dt_max;
	double	step_px;
	double	eps;
	double	min_eps;
	double	max_eps;

	dt_max = 1.0f / (double)TARGET_FPS;
	step_px = speed_px_s * dt_max;
	eps = 0.5f * step_px;
	min_eps = 0.5f;
	max_eps = 0.25f * (double)TILESIZE;
	if (eps < min_eps)
		eps = min_eps;
	if (eps > max_eps)
		eps = max_eps;
	return (eps);
}
