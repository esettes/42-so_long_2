/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_so_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-11 10:02:14 by rstancu           #+#    #+#             */
/*   Updated: 2025-11-11 10:02:14 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	init_map(t_solong *so, char *file)
{
	so->map = malloc(sizeof(t_map));
	if (!so->map)
		return (false);
	so->map->collects = NULL;
	so->map->num_collects = 0;
	if (!read_file(so, file))
		return (false);
	return (true);
}

bool	init_solong(t_solong *so, char *file)
{
	long now;

	now = get_time_ms();
	so->last_ms = now;
	so->fps = 0;
	so->last_fps_update = now;
	so->accum_ms = 0;
	so->num_enemies = 0;
	so->fps = 0;
	so->center_epsilon_px = 1.20f;
	if (!init_map(so, file))
		return (false);
	return (true);
}