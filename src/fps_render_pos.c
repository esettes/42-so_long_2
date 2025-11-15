/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_render_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-15 12:54:19 by rstancu           #+#    #+#             */
/*   Updated: 2025-11-15 12:54:19 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	soft_follow_axis(double *value, double target, double max_step)
{
	double	delta;

	delta = target - *value;
	if (fabs(delta) <= max_step)
	{
		*value = target;
		return ;
	}
	if (delta > 0.0)
		*value += max_step;
	else
		*value -= max_step;
}

void	update_render_pos(t_character *p, double follow_speed_px_s, double dt)
{
	double	max_step;

	max_step = follow_speed_px_s * dt;
	soft_follow_axis(&p->render_pos.x, p->pos.x, max_step);
	soft_follow_axis(&p->render_pos.y, p->pos.y, max_step);
}
