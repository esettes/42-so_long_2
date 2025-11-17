/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_items.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-15 13:39:27 by rstancu           #+#    #+#             */
/*   Updated: 2025-11-15 13:39:27 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_player(t_solong *so)
{
	if (so->player.curr_imgs)
		free_character(&so->player, so->mlx);
}

void	free_exit(t_solong *so)
{
	if (!so->is_running)
		return ;
	free_imgs(so->map->exit.imgs, so->mlx,
		1, so->map->exit.text);
}

void	free_collectibles(t_solong *so)
{
	uint16_t	i;

	if (!so->map->collects)
		return ;
	i = 0;
	while (i < so->map->original_num_collects)
	{
		if (so->map->collects[i].anim.imgs)
		{
			if (so->map->collects[i].anim.imgs[0])
				mlx_delete_image(so->mlx, so->map->collects[i].anim.imgs[0]);
			free(so->map->collects[i].anim.imgs);
		}
		if (so->map->collects[i].anim.text)
		{
			if (so->map->collects[i].anim.text[0])
				mlx_delete_texture(so->map->collects[i].anim.text[0]);
			free(so->map->collects[i].anim.text);
		}
		i++;
	}
	free(so->map->collects);
}

void	free_visited(bool **visited, size_t height)
{
	size_t	i;

	if (!visited)
		return ;
	i = 0;
	while (i < height)
	{
		if (visited[i])
			free(visited[i]);
		i++;
	}
	free(visited);
}

void	free_map(t_map *map, mlx_t *mlx)
{
	size_t	i;

	(void)mlx;
	if (!map)
		return ;
	if (map->arr)
	{
		i = 0;
		while (i < map->height)
		{
			if (map->arr[i] != NULL)
				free(map->arr[i]);
			i++;
		}
		free(map->arr);
	}
	free(map);
}
