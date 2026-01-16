/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:44:25 by rstancu           #+#    #+#             */
/*   Updated: 2026/01/16 16:18:49 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	put_first_sprites_to_win(t_character *p, mlx_t *mlx, int32_t num_sprites);

static bool	init_each_enemy(t_solong *so, uint16_t *i)
{
	if (*i % 4 == 0)
	{
		if (!init_anim_enemy_red(&so->enemies[*i].common, so->mlx))
			return (false);
	}
	else if (*i % 4 == 1)
	{
		if (!init_anim_enemy_blue(&so->enemies[*i].common, so->mlx))
			return (false);
	}
	else if (*i % 4 == 2)
	{
		if (!init_anim_enemy_orange(&so->enemies[*i].common, so->mlx))
			return (false);
	}
	else
	{
		if (!init_anim_enemy_pink(&so->enemies[*i].common, so->mlx))
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

void	init_enemies_common_attributes(t_solong *so, uint16_t i)
{
	so->enemies[i].common.hitbox.x = TILESIZE / 2;
	so->enemies[i].common.hitbox.y = TILESIZE / 2;
	so->enemies[i].common.wish_dir = DIR_NONE;
	so->enemies[i].common.dir = DIR_NONE;
	so->enemies[i].common.speed_px_s = PX_PER_SECONDS * 0.9;
	so->center_epsilon_px = compute_center_epsilon_px(so->enemies[i].common.speed_px_s);
	so->enemies[i].common.num_characters = 0;
	if (!put_first_sprites_to_win(&so->enemies[i].common, so->mlx, NUM_ENEMY_SPRITES))
		return ;
	so->enemies[i].common.curr_imgs = so->enemies[i].common.down.imgs;
	so->enemies[i].common.curr_num_frames = so->enemies[i].common.down.num_frames;
	so->enemies[i].common.curr_frame = 0;
	so->enemies[i].common.last_anim_time = 0.0;
	so->enemies[i].common.last_pos.x = (int32_t)(so->enemies[i].common.pos.x / TILESIZE);
	so->enemies[i].common.last_pos.y = (int32_t)(so->enemies[i].common.pos.y / TILESIZE);
	if (so->enemies[i].common.curr_imgs && so->enemies[i].common.curr_imgs[0])
	{
		so->enemies[i].common.curr_imgs[0]->instances[0].enabled = true;
		so->enemies[i].common.curr_imgs[0]->instances[0].x
			= (int)so->enemies[i].common.render_pos.x;
		so->enemies[i].common.curr_imgs[0]->instances[0].y
			= (int)so->enemies[i].common.render_pos.y;
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

bool	init_enemies(t_solong *so)
{
	uint16_t	i;

	i = 0;
	so->enemies = malloc(sizeof(t_character) * so->num_enemies);
	if (!so->enemies)
		return (false);
	while (i < so->num_enemies)
	{
		init_each_enemy(so, &i);
		i++;
	}
	get_enemies_positions_from_arr_map(so);
	init_enemies_attributes(so);
	i = 0;
	while (i < so->num_enemies)
	{
		init_enemies_common_attributes(so, i);
		i++;
	}
	return (true);
}
