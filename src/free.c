/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:27:50 by rstancu           #+#    #+#             */
/*   Updated: 2025/11/11 13:32:15 by settes           ###   ########.fr       */
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
			if (mlx)
			{
				mlx_delete_image(mlx, character->right.imgs[i]);
				if (character->right.text && character->right.text[i])
					mlx_delete_texture(character->right.text[i]);
			}
		}
		if (character->left.imgs && character->left.imgs[i])
		{
			if (mlx)
			{
				mlx_delete_image(mlx, character->left.imgs[i]);
				if (character->left.text && character->left.text[i])
					mlx_delete_texture(character->left.text[i]);
			}
		}	
		if (character->up.imgs && character->up.imgs[i])
		{
			if (mlx)
			{
				mlx_delete_image(mlx, character->up.imgs[i]);
				if (character->up.text && character->up.text[i])
					mlx_delete_texture(character->up.text[i]);
			}
		}
		if (character->down.imgs && character->down.imgs[i])
		{
			if (mlx)
			{
				mlx_delete_image(mlx, character->down.imgs[i]);
				if (character->down.text && character->down.text[i])
					mlx_delete_texture(character->down.text[i]);
			}
		}
		i++;
	}
	free(character->right.imgs);
	free(character->left.imgs);
	free(character->up.imgs);
	free(character->down.imgs);
	if (character->right.text)
		free(character->right.text);
	if (character->left.text)
		free(character->left.text);
	if (character->up.text)
		free(character->up.text);
	if (character->down.text)
		free(character->down.text);
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

void	free_map(t_map *map, mlx_t *mlx)
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
			/* Use the provided mlx context to delete images. Also delete
			   the associated texture and free the malloc'd arrays. */
			if (mlx && map->collects[i].anim.imgs[0])
				mlx_delete_image(mlx, map->collects[i].anim.imgs[0]);
			if (map->collects[i].anim.text && map->collects[i].anim.text[0])
				mlx_delete_texture(map->collects[i].anim.text[0]);
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
	/* Free player and enemies (they need the mlx context). */
	free_player(so);
	free_enemies(so);
	/* Free cell/tiles if present */
	if (so->cell_tile)
		mlx_delete_image(so->mlx, so->cell_tile);
	if (so->text_cell)
		mlx_delete_texture(so->text_cell);
	/* Free collectibles and the map using the mlx context */
	free_map(so->map, so->mlx);
	return (false);
}
