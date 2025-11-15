/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:08:07 by rstancu           #+#    #+#             */
/*   Updated: 2025/11/13 11:14:13 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void soft_follow_axis(double *value, double target, double max_step)
{
    double delta;
	
	delta = target - *value;
    if (fabs(delta) <= max_step)
	{
        *value = target;
        return;
    }
	if (delta > 0.0)
		*value += max_step;
	else
		*value -= max_step;
}

void update_render_pos(t_character *p, double follow_speed_px_s, double dt)
{
    double max_step;
	
	max_step = follow_speed_px_s * dt;
    soft_follow_axis(&p->render_pos.x, p->pos.x, max_step);
    soft_follow_axis(&p->render_pos.y, p->pos.y, max_step);
}

// If centered, tryapply wish_dir; if blocked ahead, snap and stop
// Does NOT move the character forward. Movement happens in go_ahead
void	compute_twist_and_lock(t_character *p, t_solong *so)
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

static inline void wrap_ahead(t_solong * so, t_character *p, t_int2 tile)
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

void	animation_hook(mlx_image_t **sprites, t_character *npc,
					double elapsed, int32_t num_sprites)
{

	npc->last_anim_time += elapsed;
	if (npc->last_anim_time  >= ANIM_FRAME_INTERVAL)
	{
		npc->curr_frame = (npc->curr_frame + 1) % num_sprites;
		npc->last_anim_time -= ANIM_FRAME_INTERVAL;
		
		sprites[npc->curr_frame]->instances[0].enabled = true;
		sprites[(npc->curr_frame + num_sprites - 1)
			% num_sprites]->instances[0].enabled = false;
		sprites[npc->curr_frame]->instances[0].x = npc->render_pos.x;
		sprites[npc->curr_frame]->instances[0].y
			= npc->render_pos.y - (TILESIZE / 2);
	}
}

void	unable_sprites(mlx_image_t **sprites, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		sprites[i]->instances[0].enabled = false;
		i++;
	}
}

void	anim(t_dir dir, t_solong *so, mlx_image_t **imgs, int num)
{
	so->player.dir = dir;
	if (so->player.curr_imgs == imgs)
		return ;
	if (so->player.curr_imgs)
		unable_sprites(so->player.curr_imgs, num);
	so->player.curr_imgs = imgs;
	so->player.curr_num_frames = NUM_PLAYER_SPRITES;
	so->player.last_anim_time = 0.0;
	so->player.curr_frame = 0;
}

void	catch_keys(t_solong *so, bool *updated)
{
	if (mlx_is_key_down(so->mlx, MLX_KEY_UP))
	{
		anim(DIR_UP, so, so->player.up.imgs, so->player.up.num_frames);
		*updated = true;
	}
	else if (mlx_is_key_down(so->mlx, MLX_KEY_DOWN))
	{
		anim(DIR_DOWN, so, so->player.down.imgs, so->player.down.num_frames);
		*updated = true;
	}
	else if (mlx_is_key_down(so->mlx, MLX_KEY_LEFT))
	{
		anim(DIR_LEFT, so, so->player.left.imgs, so->player.left.num_frames);
		*updated = true;
	}
	else if (mlx_is_key_down(so->mlx, MLX_KEY_RIGHT))
	{
		anim(DIR_RIGHT, so, so->player.right.imgs, so->player.right.num_frames);
		*updated = true;
	}
	else
    {
		if (*updated)
			so->movements_count++;
	}
}

void	fps_hook(void *param)
{
	t_solong	*so;
	double		elapsed_time;
	double		dt;
	bool		updated;
	
	so = (t_solong *)param;
	updated = false;
	elapsed_time = so->mlx->delta_time * 1000.0;
	dt = elapsed_time / 1000.0;
	if (dt > 0.05)
        dt = 0.05;
	so->player.last_pos.x = so->player.pos.x / TILESIZE;
	so->player.last_pos.y = so->player.pos.y / TILESIZE;
	so->player.dir = DIR_NONE;
	catch_keys(so, &updated);
	go_ahead(&so->player, so, dt);
	print_movements(so);
	update_render_pos(&so->player, FOLLOW_SPEED_PX_S, dt);
	animation_hook(so->player.curr_imgs, &so->player, elapsed_time,
				so->player.curr_num_frames);
	get_collectible(so);
	if (can_exit(so))
		mlx_close_window(so->mlx);
}
