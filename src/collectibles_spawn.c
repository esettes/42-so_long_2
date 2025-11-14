/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectibles_spawn.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-12 13:19:27 by rstancu           #+#    #+#             */
/*   Updated: 2025-11-12 13:19:27 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_collectibles_pos(t_solong *so)
{
	uint16_t	i;
	uint16_t	j;
	uint16_t	count;

	i = 0;
	count = 0;
	while (i < so->map->height)
	{
		j = 0;
		while (j < so->map->width)
		{
			if (so->map->arr[i][j] && so->map->arr[i][j] == M_COLLECTIBLE)
			{
				so->map->collects[count].pos.x = j;
				so->map->collects[count].pos.y = i;
				count++;
				if (count == so->map->num_collects)
					break ;
			}
			j++;
			if (count == so->map->num_collects)
				break ;
		}
		i++;
	}
}

void	spawn_collectibles(t_solong *so)
{
	uint16_t	i;
	int32_t		id;
	
	i = 0;
	init_collectibles(so);
	get_collectibles_pos(so);
	while (i < so->map->num_collects)
	{
		so->map->collects[i].img = so->map->collects[i].anim.imgs[0];
		id = mlx_image_to_window(so->mlx, so->map->collects[i].img, (int32_t)(so->map->collects[i].pos.x  * TILESIZE), (int32_t)(so->map->collects[i].pos.y * TILESIZE));
		so->map->collects[i].instance_id = id;
		i++;
	}
}
