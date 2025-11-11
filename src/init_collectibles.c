/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_collectibles.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-11 10:00:06 by rstancu           #+#    #+#             */
/*   Updated: 2025-11-11 10:00:06 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	init_collectible(t_collectible *c, mlx_t *mlx, char *path)
{
	c->anim.text = malloc(sizeof(mlx_texture_t *));
	if (!c->anim.text)
		return (false);
	c->anim.text[0] = mlx_load_png(path);
	if (!c->anim.text[0])
		return (false);
	c->anim.imgs = malloc(sizeof(mlx_image_t *));
	if (!c->anim.imgs)
		return (false);
	c->anim.imgs[0] = mlx_texture_to_image(mlx, c->anim.text[0]);
	if (!c->anim.imgs[0])
		return (false);
	mlx_resize_image(c->anim.imgs[0], TILESIZE, TILESIZE);
	c->anim.num_frames = 1;
	return (true);
}
bool	init_collectibles(t_solong *so)
{
	uint16_t	i;

	i = 0;
	so->map->collects = malloc(sizeof(t_collectible) * so->map->num_collects);
	if (!so->map->collects)
		return (false);
	while (i < so->map->num_collects)
	{
		if (i % 4 == 0)
		{
			if (!init_collectible(&so->map->collects[i], so->mlx, COLLECT_1))
				return (false);
		}
		else if (i % 4 == 1)
		{
			if (!init_collectible(&so->map->collects[i], so->mlx, COLLECT_2))
				return (false);
		}
		else if (i % 4 == 2)
		{
			if (!init_collectible(&so->map->collects[i], so->mlx, COLLECT_3))
				return (false);
		}
		else if (i % 4 == 3)
		{
			if (!init_collectible(&so->map->collects[i], so->mlx, COLLECT_4))
				return (false);
		}
		i++;
	}
	return (true);
}