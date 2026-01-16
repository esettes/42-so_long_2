/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:44:25 by rstancu           #+#    #+#             */
/*   Updated: 2026/01/16 15:55:37 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	init_each_enemy(t_solong *so, uint16_t *i)
{
	if (*i % 4 == 0)
	{
		if (!init_anim_enemy_red(&so->enemies[*i], so->mlx))
			return (false);
	}
	else if (*i % 4 == 1)
	{
		if (!init_anim_enemy_blue(&so->enemies[*i], so->mlx))
			return (false);
	}
	else if (*i % 4 == 2)
	{
		if (!init_anim_enemy_orange(&so->enemies[*i], so->mlx))
			return (false);
	}
	else
	{
		if (!init_anim_enemy_pink(&so->enemies[*i], so->mlx))
			return (false);
	}
	return (true);
}

void	get_enemies_positions_from_arr_map(t_solong *so)
{
	size_t	k;
	size_t	j;
	uint16_t	idx;

	k = 0;
	idx = 0;
	while (k < so->map->height)
	{
		j = 0;
		while (j < so->map->width)
		{
			if (so->map->arr[k][j] == M_ENEMY)
			{
				so->enemies[idx].common.pos.x = (double)j * TILESIZE;
				so->enemies[idx].common.pos.y = (double)k * TILESIZE;
				idx++;
			}
			j++;
		}
		k++;
	}
}

void	init_enemies_attributes(t_solong *so)
{
	size_t	i;

	i = 0;
	while (i < so->num_enemies)
	{
		so->enemies[i].mode = GHOST_MODE_SCATTER;
		so->enemies[i].is_elroy = false;
		if (i % 4 == 0)
		{
			so->enemies[i].type = GHOST_BLINKY;
			so->enemies[i].corner.x = so->map->width - 1;
			so->enemies[i].corner.y = 0;
		}
		else if (i % 4 == 1)
		{
			so->enemies[i].type = GHOST_INKY;
			so->enemies[i].corner.x = so->map->width - 1;
			so->enemies[i].corner.y = so->map->height - 1;
		}
		else if (i % 4 == 2)
		{
			so->enemies[i].type = GHOST_CLYDE;
			so->enemies[i].corner.x = 0;
			so->enemies[i].corner.y = so->map->height - 1;
		}
		else
		{
			so->enemies[i].type = GHOST_PINKY;
			so->enemies[i].corner.x = 0;
			so->enemies[i].corner.y = 0;
		}
		i++;
	}
}

bool	init_emenies(t_solong *so)
{
	uint16_t	i;

	i = 0;
	so->enemies = malloc(sizeof(t_character) * so->num_enemies);
	if (!so->enemies)
		return (false);
	while (i < so->num_enemies)
	{
		init_each_enemy(so, &i);
		// init enemy position, mode, type ...
		i++;
	}
	return (true);
}
