/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_controller_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 12:50:16 by rstancu           #+#    #+#             */
/*   Updated: 2025/11/15 15:58:42 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// If centered, tryapply wish_dir; if blocked ahead, snap and stop
// Does NOT move the character forward. Movement happens in go_ahead
static void	compute_twist_and_lock(t_character *p, t_solong *so)
{
	t_int2	tile;
	t_pos	center;
	t_int2	step;
	t_int2	ahead;

	get_tile_and_center(p->pos, &tile, &center);
	if (is_centered(so, p->pos))
	{
		if (p->wish_dir != DIR_NONE
			&& can_move_dir_from_tile(so, tile, p->wish_dir))
			p->dir = p->wish_dir;
	}
	if (p->dir != DIR_NONE)
	{
		dir_to_vec(p->dir, &step.x, &step.y);
		ahead.x = tile.x + step.x;
		ahead.y = tile.y + step.y;
		if (!is_walkable(so->map, ahead.x, ahead.y))
		{
			p->pos.x = center.x - (TILESIZE / 2);
			p->pos.y = center.y;
			p->dir = DIR_NONE;
		}
	}
}

static inline void	wrap_ahead(t_solong *so, t_character *p, t_int2 tile)
{
	if (tile.x < 0)
		p->pos.x = ((so->map->width - 0.5) * (double)TILESIZE);
	else if (tile.x >= (int32_t)so->map->width)
		p->pos.x = (0.5 * (double)TILESIZE);
}

static void	move_at_center(t_character *p, t_pos center,
						t_vec2 next_center, t_int2 step)
{
	double	dist;
	double	move;
	double	step_px;

	step_px = p->speed_px_s * p->dt;
	if (step.x != 0)
	{
		p->pos.y = center.y;
		dist = next_center.x - p->pos.x;
		move = ft_clampd(step_px, 0, fabs(dist)) * (step.x);
		p->pos.x += move;
	}
	else if (step.y != 0)
	{
		p->pos.x = center.x - (TILESIZE / 2);
		dist = next_center.y - p->pos.y;
		move = ft_clampd(step_px, 0, fabs(dist)) * (step.y);
		p->pos.y += move;
	}
}

void	go_ahead(t_character *p, t_solong *so, double dt)
{
	t_int2	step;
	t_vec2	next_center;
	t_pos	center_pos;
	t_int2	tile;
	t_int2	ahead_t;

	compute_twist_and_lock(p, so);
	dir_to_vec(p->dir, &step.x, &step.y);
	get_tile_and_center(p->pos, &tile, &center_pos);
	ahead_t.x = tile.x + step.x;
	ahead_t.y = tile.y + step.y;
	if (!is_walkable(so->map, ahead_t.x, ahead_t.y))
	{
		p->pos.x = center_pos.x;
		p->pos.y = center_pos.y;
		p->dir = DIR_NONE;
		return ;
	}
	next_center.x = (ahead_t.x + 0.5) * (double)TILESIZE;
	next_center.y = (ahead_t.y + 0.5) * (double)TILESIZE;
	p->dt = dt;
	move_at_center(p, center_pos, next_center, step);
	get_tile_and_center(p->pos, &tile, &center_pos);
	wrap_ahead(so, p, tile);
}

void	catch_esc(t_solong *so)
{
	if (mlx_is_key_down(so->mlx, MLX_KEY_ESCAPE))
	{
		//free_all(so);
		mlx_close_window(so->mlx);
		//return ;
	}
}
