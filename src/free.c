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

void	free_exit(t_solong *so)
{
	if (so->map->exit.imgs)
	{
		if (so->map->exit.imgs[0])
		{
			mlx_delete_image(so->mlx, so->map->exit.imgs[0]);
		}
		free(so->map->exit.imgs);
	}
	if (so->map->exit.text)
	{
		if (so->map->exit.text[0])
		{
			mlx_delete_texture(so->map->exit.text[0]);
		}
		free(so->map->exit.text);
	}
}

void	free_collectibles(t_solong *so)
{
	uint16_t	i;

	if (!so->map->collects)
		return ;
	i = 0;
	while (i < so->map->num_collects)
	{
		if (so->map->collects[i].anim.imgs)
		{
			if (so->map->collects[i].anim.imgs[0])
			{
				mlx_delete_image(so->mlx, so->map->collects[i].anim.imgs[0]);
			}
			free(so->map->collects[i].anim.imgs);
		}
		if (so->map->collects[i].anim.text)
		{
			if (so->map->collects[i].anim.text[0])
			{
				mlx_delete_texture(so->map->collects[i].anim.text[0]);
			}
			free(so->map->collects[i].anim.text);
		}
		i++;
	}
	free(so->map->collects);
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
	free_player(so);
	free_enemies(so);
	if (so->cell_tile)
		mlx_delete_image(so->mlx, so->cell_tile);
	if (so->text_cell)
		mlx_delete_texture(so->text_cell);
	
	free_exit(so);
	free_collectibles(so);
	if (so->background)
		mlx_delete_image(so->mlx, so->background);
	if (so->hud_db)
		mlx_delete_image(so->mlx, so->hud_db);
	if (so->hud_text_img)
		mlx_delete_image(so->mlx, so->hud_text_img);
	if (so->hud_foreground)
		mlx_delete_image(so->mlx, so->hud_foreground);
	free_map(so->map, so->mlx);
	return (false);
}

