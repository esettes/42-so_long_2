/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:31:47 by rstancu           #+#    #+#             */
/*   Updated: 2025/11/15 11:41:42 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_collectible(t_solong *so)
{
	uint16_t	i;
	t_int2		player_tile;

	get_tile_and_center(so->player.pos, &player_tile, NULL);
	i = 0;
	while (i < so->map->original_num_collects)
	{
		if (((int32_t)so->map->collects[i].pos.x == player_tile.x
				&& (int32_t)so->map->collects[i].pos.y == player_tile.y)
			&& !so->map->collects[i].collected)
		{
			so->map->collects[i].anim.imgs[0]->instances[0].enabled = false;
			so->map->arr[player_tile.y][player_tile.x] = M_SPACE;
			so->map->num_collects--;
			so->map->collects[i].collected = true;
			return ;
		}
		i++;
	}
}
