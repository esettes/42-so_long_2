/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:27:50 by rstancu           #+#    #+#             */
/*   Updated: 2025/11/10 11:47:16 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_character(t_character *character, mlx_t *mlx)
{
	uint16_t	i;

	i = 0;
	while (i < character->right.num_frames)
	{
		if (character->right.imgs && character->right.imgs[i])
		{
			mlx_delete_image(mlx, character->right.imgs[i]);
			mlx_delete_texture(character->right.text[i]);
		}
		if (character->left.imgs && character->left.imgs[i])
		{
			mlx_delete_image(mlx, character->left.imgs[i]);
			mlx_delete_texture(character->left.text[i]);
		}	
		if (character->up.imgs && character->up.imgs[i])
		{
			mlx_delete_image(mlx, character->up.imgs[i]);
			mlx_delete_texture(character->up.text[i]);
		}
		if (character->down.imgs && character->down.imgs[i])
		{
			mlx_delete_image(mlx, character->down.imgs[i]);
			mlx_delete_texture(character->down.text[i]);
		}
		i++;
	}
	free(character->right.imgs);
	free(character->left.imgs);
	free(character->up.imgs);
	free(character->down.imgs);
}

void	free_enemies(t_solong *so)
{
	uint16_t	i;

	if (!so->enemies)
		return ;
	i = 0;
	while (i < so->num_enemies)
	{
		free_character(&so->enemies[i], so->mlx);
		i++;
	}
	free(so->enemies);
}

void	free_player(t_solong *so)
{
	free_character(&so->player, so->mlx);
}

void	free_map(t_map *map)
{
	size_t	i;

	if (!map)
		return ;
	if (map->arr)
	{
		i = 0;
		while (i < map->height)
		{
			free(map->arr[i]);
			i++;
		}
		free(map->arr);
	}
	i = 0;
	while (i < map->num_collects)
	{
		if (map->collects && map->collects[i].anim.imgs)
		{
			mlx_delete_image(NULL, map->collects[i].anim.imgs[0]);
			mlx_delete_texture(*map->collects[i].anim.text);
			free(map->collects[i].anim.imgs);
			free(map->collects[i].anim.text);
		}
		i++;
	}
	free(map->collects);
	free(map);
}

bool	free_all(t_solong *so)
{
	free_player(so);
	free_enemies(so);
	free_map(so->map);
	return (false);
}
