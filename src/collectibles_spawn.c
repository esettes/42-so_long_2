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
	t_uint16	t;
	uint16_t	count;

	t.y = 0;
	count = 0;
	while (t.y < so->map->height)
	{
		t.x = -1;
		while (++t.x < so->map->width)
		{
			if (so->map->arr[t.y][t.x]
				&& so->map->arr[t.y][t.x] == M_COLLECTIBLE)
			{
				so->map->collects[count].pos.x = t.x;
				so->map->collects[count].pos.y = t.y;
				count++;
				if (count == so->map->num_collects)
					break ;
			}
			if (count == so->map->num_collects)
				break ;
		}
		t.y++;
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
		id = mlx_image_to_window(so->mlx, so->map->collects[i].img,
				(int32_t)(so->map->collects[i].pos.x * TILESIZE),
				(int32_t)(so->map->collects[i].pos.y * TILESIZE));
		so->map->collects[i].instance_id = id;
		i++;
	}
}
