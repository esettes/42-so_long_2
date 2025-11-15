/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:49:07 by rstancu           #+#    #+#             */
/*   Updated: 2025/11/13 11:32:58 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_exit(t_solong *so)
{
	if (!init_exit(so))
	{
		ft_putendl_fd("Error: Can't init exit image.", 2);
		return ;
	}
	if (!mlx_image_to_window(so->mlx, so->map->exit.imgs[0],
			so->map->exit_pos.x * TILESIZE, so->map->exit_pos.y * TILESIZE))
	{
		return ;
	}
}

bool	can_exit(t_solong *so)
{
	t_int2		player_tile;

	get_tile_and_center(so->player.pos, &player_tile, NULL);
	if ((int32_t)so->map->exit_pos.x == player_tile.x
		&& (int32_t)so->map->exit_pos.y == player_tile.y)
	{
		if (so->map->num_collects > 0)
			return (false);
		return (true);
	}
	return (false);
}
