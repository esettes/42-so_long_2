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
				printf("Collectible %d at tile (%d,%d) pos (%.1f,%.1f)\n", count, j, i, so->map->collects[count].pos.x, so->map->collects[count].pos.y);
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
	char	pos_str[50];
	
	i = 0;
	init_collectibles(so);
	get_collectibles_pos(so);
	while (i < so->map->num_collects)
	{
		so->map->collects[i].img = so->map->collects[i].anim.imgs[0];
		// print position os each collectible on top of each one with mlx_put_string
		sprintf(pos_str, "Pos: (%.0f, %.0f)", so->map->collects[i].pos.x, so->map->collects[i].pos.y);
		mlx_put_string(so->mlx, pos_str, (int)(so->map->collects[i].pos.x) * TILESIZE, (int)(	so->map->collects[i].pos.y) * TILESIZE);
		id = mlx_image_to_window(so->mlx, so->map->collects[i].img, (int32_t)(so->map->collects[i].pos.x  * TILESIZE), (int32_t)(so->map->collects[i].pos.y * TILESIZE));
		so->map->collects[i].instance_id = id;
		i++;
	}
}
