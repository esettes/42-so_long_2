/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:08:07 by rstancu           #+#    #+#             */
/*   Updated: 2025/11/11 13:40:12 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	detect_wall(t_solong *so, double x, double y)
{
	if (so->map->arr[(int)y / TILESIZE][(int)x / TILESIZE] == 1)
	{
		// if (so->map->arr[(int)(y - TILESIZE) / TILESIZE][(int)(x - TILESIZE) / TILESIZE] == 0)
		// 	return (true);
		return (true);
	}
	
	return (false);
}

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
		printf("Centered at tile (%d,%d)\n", tile.x, tile.y);
		if (p->wish_dir != DIR_NONE && can_move_dir_from_tile(so, tile, p->wish_dir))
			p->dir = p->wish_dir;
	}
	
	// if current dir is blocked, stop and snap to center
	if (p->dir != DIR_NONE)
	{
		dir_to_vec(p->dir, &step.x, &step.y);
		ahead.x = tile.x + step.x;
		ahead.y = tile.y + step.y;
		if (!is_walkable(so->map, ahead.x, ahead.y))
		{
			p->pos.x = center.x - 32;
			p->pos.y = center.y;
			p->dir = DIR_NONE;
		}
	}
}

void	go_ahead(t_character *p, t_solong *so, double dt)
{
	t_int2	step;
	
	t_vec2	next_center;
	double	dist;
	double	move;
	t_pos	center_pos;
	t_int2	tile;
	t_int2	ahead_t;
	double	step_px;
	

	compute_twist_and_lock(p, so);
	dir_to_vec(p->dir, &step.x, &step.y);
	get_tile_and_center(p->pos, &tile, &center_pos);
	// Blocked ahead? Snap to center and stop.
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
	step_px = p->speed_px_s * dt;
	//distance to the next center along the moving axis
	if (step.x != 0)
	{
		p->pos.y = center_pos.y;
		
		dist = next_center.x - p->pos.x;
		move = ft_clampd(step_px, 0, fabs(dist)) * (step.x);
		p->pos.x += move;
	}
	else if (step.y != 0)
	{
		p->pos.x = center_pos.x - 32;
		dist = next_center.y - p->pos.y;
		move = ft_clampd(step_px, 0, fabs(dist)) * (step.y);
		p->pos.y += move;
	}
	get_tile_and_center(p->pos, &tile, &center_pos);
	if (tile.x < 0)
		p->pos.x = ((so->map->width - 0.5) * (double)TILESIZE);
	else if (tile.x >= (int32_t)so->map->width)
		p->pos.x = (0.5 * (double)TILESIZE);

}

void	animation_hook(mlx_image_t **sprites, t_character *npc, long now, int32_t num_sprites)
{
	// long		elapsed_time;
	// long		target_frame_dur;

	// elapsed_time = now - so->last_ms;
	// target_frame_dur = 100 / TARGET_FPS;
	// if (elapsed_time >= target_frame_dur)
	// {
	// 	so->last_ms += target_frame_dur;
	 (void)sprites;
	//physics_update(so, now);
	
	if (now - npc->last_anim_time >= ANIM_FRAME_INTERVAL)
	{
		npc->curr_frame = (npc->curr_frame + 1) % num_sprites;
		npc->last_anim_time += ANIM_FRAME_INTERVAL;
		
		sprites[npc->curr_frame]->instances[0].enabled = true;
		sprites[(npc->curr_frame + num_sprites - 1) % num_sprites]->instances[0].enabled = false;
		sprites[npc->curr_frame]->instances[0].x = npc->render_pos.x;
		sprites[npc->curr_frame]->instances[0].y = npc->render_pos.y - 32;
		
	}
	//}
}

void	fps_controller(void *param)
{
	t_solong	*so;
	long		curr_time;
	long		elapsed_time;
	long		target_frame_dur;
	char		*fps;

	so = (t_solong *)param;
	curr_time = get_time_ms();
	elapsed_time = curr_time - so->last_ms;
	target_frame_dur = 1000 / TARGET_FPS;
	fps = ft_itoa(so->fps);
	if (elapsed_time >= target_frame_dur)
	{
		so->last_ms += target_frame_dur;
		so->fps++;
		if (curr_time - so->last_fps_update >= 1000)
		{
			fps = ft_itoa(so->fps);
			mlx_put_string(so->mlx, fps, 100, 100);
			free(fps);
			so->fps = 0;
			so->last_fps_update += target_frame_dur;
		}
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

void	set_current_anim(t_solong *so, t_character *p, mlx_image_t **imgs, int num)
{
	// imgs[0]->instances[0].enabled = true;
	(void)so;
	if (p->curr_imgs == imgs)
		return ;
	if (p->curr_imgs)
		unable_sprites(p->curr_imgs, num);
	p->curr_imgs = imgs;
	p->curr_num_frames = NUM_PLAYER_SPRITES;
	p->last_anim_time = get_time_ms();
	p->curr_frame = 0;
	render_interpolated(so,  p->curr_imgs[0]);
	render_interpolated(so,  p->curr_imgs[1]);
	render_interpolated(so,  p->curr_imgs[2]);
}

void	fps_hook(void *param)
{
	t_solong	*so;
	long		curr_time;
	long		elapsed_time;
	long		target_frame_dur;
	double		dt;

	so = (t_solong *)param;
	curr_time = get_time_ms();	
	elapsed_time = curr_time - so->last_ms;
	target_frame_dur = 1000 / TARGET_FPS;
	dt = (curr_time - so->last_update_ms) / 1000.0;
	if (dt > 0.05)
        dt = 0.05;
	so->last_update_ms = curr_time;
	if (mlx_is_key_down(so->mlx, MLX_KEY_UP))
	{
		set_current_anim(so, &so->player, so->player.up.imgs, so->player.up.num_frames);
		so->player.velocity.y = -20.0;
		so->player.dir = DIR_UP;
	}
	else if (mlx_is_key_down(so->mlx, MLX_KEY_DOWN))
	{
		set_current_anim(so, &so->player, so->player.down.imgs, so->player.down.num_frames);
		so->player.velocity.y = 20.0;
		so->player.dir = DIR_DOWN;
	}
	
	else if (mlx_is_key_down(so->mlx, MLX_KEY_LEFT))
	{
		set_current_anim(so, &so->player, so->player.left.imgs, so->player.left.num_frames);
		so->player.velocity.x = -20.0;
		so->player.dir = DIR_LEFT;
	}
	else if (mlx_is_key_down(so->mlx, MLX_KEY_RIGHT))
	{
		set_current_anim(so, &so->player, so->player.right.imgs, so->player.right.num_frames);
		so->player.velocity.x = 20.0;
		so->player.dir = DIR_RIGHT;
	}
	else
    {
		so->player.dir = DIR_NONE;
		so->player.velocity.x = 0.0;
		so->player.velocity.y = 0.0;
	}
	go_ahead(&so->player, so, dt);
	if (elapsed_time >= target_frame_dur)
	{
		so->last_ms += target_frame_dur;
		print_player_pos(so);
		update_render_pos(&so->player, FOLLOW_SPEED_PX_S, dt);
		animation_hook(so->player.curr_imgs, &so->player, curr_time, so->player.curr_num_frames);
		get_collectible(so);
		if (can_exit(so))
			mlx_close_window(so->mlx);
	}
	
}
