/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:31:47 by rstancu           #+#    #+#             */
/*   Updated: 2025/11/13 11:29:03 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_collectible(t_solong *so)
{
	uint16_t	i;
	uint16_t	k;
	t_int2		player_tile;

	get_tile_and_center(so->player.pos, &player_tile, NULL);
	i = 0;
	k = 0;
	while (i < so->map->num_collects)
	{
		if ((int32_t)so->map->collects[i].pos.x == player_tile.x
			&& (int32_t)so->map->collects[i].pos.y == player_tile.y)
		{
			// while (k < so->map->collects[i].anim.imgs[0]->count)
			// {
			// 	// if (so->map->collects[i].anim.imgs[0]->instances[k].x == (int32_t)(so->map->collects[i].pos.x * TILESIZE)
			// 	// 	&& so->map->collects[i].anim.imgs[0]->instances[k].y == (int32_t)(so->map->collects[i].pos.y * TILESIZE))
			// 	// {
			// 		so->map->collects[i].anim.imgs[0]->instances[k].enabled = false;
			// 		//break ;
			// 	//}
			// 	k++;
			// }
			so->map->collects[i].anim.imgs[0]->instances[0].enabled = false;
			so->map->arr[player_tile.y][player_tile.x] = M_SPACE;
			so->map->num_collects--;
			return ;
		}
		i++;
	}
}

// int32_t	find_instance_at(mlx_image_t *img, int px, int py)
// {
// 	size_t	k;

// 	k = 0;
// 	while (k < img->count)
// 	{
// 		if (img->instances[k].x == px && img->instances[k].y == py)
// 			return (k);
// 	}
// 	return (-1);
// }

// void	get_collectible(t_solong *so)
// {
// 	uint16_t	i;
// 	t_int2		player_tile;
// 	t_collectible	*c;
// 	t_int2		pos;
// 	int32_t		id;

// 	get_tile_and_center(so->player.render_pos, &player_tile, NULL);
// 	i = 0;
// 	while (i < so->map->num_collects)
// 	{
// 		c = &so->map->collects[i];
// 		if (!c->collected && (int32_t)so->map->collects[i].pos.x == player_tile.x
// 			&& (int32_t)so->map->collects[i].pos.y == player_tile.y)
// 		{
// 			printf("Collected collectible at (%d,%d) !!!! =^o^=\n", player_tile.x, player_tile.y);
// 			pos.x = (int32_t)(c->pos.x * TILESIZE);
// 			pos.y = (int32_t)(c->pos.y * TILESIZE);
// 			id = find_instance_at(c->anim.imgs[0], pos.x, pos.y);
// 			if (id >= 0)
// 				so->map->collects[i].img->instances[id].enabled = false;
// 			so->map->arr[player_tile.y][player_tile.x] = M_SPACE;
// 			c->collected = true;
// 			so->map->num_collects--;
// 			return ;
// 		}
// 		i++;
// 	}
// }
