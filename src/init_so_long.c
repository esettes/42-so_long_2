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
	so->map->num_exits = 0;
	if (!read_file(so, file))
	{
		free(so->map);
		return (false);
	}
	return (true);
}

bool	init_solong(t_solong *so, char *file)
{
	long now;

	if (!is_valid_extension(file))
	{
		ft_putendl_fd("Error: Invalid file extension.", 2);
		return (false);
	}
	now = get_time_ms();
	so->last_ms = now;
	so->last_update_ms = now;
	so->num_enemies = 0;
	so->movements_count = 0;
	if (!init_map(so, file))
		return (false);
	if (!check_map_limits(so))
	{
		free_map(so->map, so->mlx);
		return (false);
	}
	if (!is_map_playable(so->map, &so->player))
	{
		ft_putendl_fd("Error: Map is not playable.", 2);
		free_map(so->map, so->mlx);
		return (false);
	}
	so->is_running = true;
	return (true);
}