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

void	update_sprites_position(t_character *p, double x, double y, t_solong *so)
{
	//size_t	i;
	// double	tmp_x;
	// double	tmp_y;
	t_int2	tilepos;
	t_pos	center_pos;
	t_int2	dir;
	t_int2	ahead_t;

	//i = 0;
	tilepos.x = 0;
	tilepos.y = 0;
	center_pos.x = 0.0;
	center_pos.y = 0.0;
	get_tile_and_center(p->pos, &tilepos, &center_pos);
	if (is_centered(so, p->pos))
	{
		printf("centered\n");
		if (p->wish_dir != DIR_NONE && can_move_dir_from_tile(so, tilepos, p->wish_dir))
			p->dir = p->wish_dir;
	}
	// if current dir is blocked, stop and snap to center
	if (p->dir != DIR_NONE)
	{
		dir_to_vec(p->dir, &dir.x, &dir.y);
		ahead_t.x = tilepos.x + dir.x;
		ahead_t.y = tilepos.y + dir.y;
		if (!is_walkable(so->map, ahead_t.x, ahead_t.y))
		{
			p->pos.x = center_pos.x;
			p->pos.y = center_pos.y;
			p->dir = DIR_NONE;
		}
	}
	


	(void)so;
	(void)x;
	(void)y;
	// tmp_x = (p->pos.x + x);// * p->velocity.x;
	// tmp_y = (p->pos.y + y);// * p->velocity.y;
	// if (!detect_wall(so, tmp_x, tmp_y))
	// {
	// 	p->pos.x = ft_clampd(tmp_x, 0, so->map->width * TILESIZE);
	// 	p->pos.y = ft_clampd(tmp_y, 0, (so->map->height * TILESIZE));
	// }
	
	// printf("player pos: x[%f] y[%f]\n", p->pos.x, p->pos.y);
}

void	go_ahead(t_character *p, double step, t_solong *so, double dt, t_pos tilepos, t_pos center_pos)
{
	t_int2	dir;
	t_int2	next_tile;
	t_vec2	next_center;
	double	dist;
	double	move;
	
	if (p->dir != DIR_NONE)
	{
		dir_to_vec(p->dir, &dir.x, &dir.y);
		update_sprites_position(p, dir.x * step, dir.y * step, so);
		step = p->speed_px_s * dt;
		next_tile.x = tilepos.x + dir.x;
		next_tile.y = tilepos.y + dir.y;
		next_center.x = (next_tile.x + 0.5) * (double)TILESIZE;
		next_center.y = (next_tile.y + 0.5) * (double)TILESIZE;
		
		//distance to the next center along the moving axis
		if (dir.x != 0)
		{
			p->pos.y = center_pos.y;
			dist = next_center.x - p->pos.x;
			move = ft_clampd(step, 0, fabs(dist)) * (dir.x); /////// ??
			p->pos.x += move;
		}
		else if (dir.y != 0)
		{
			p->pos.x = center_pos.x;
			dist = next_center.y - p->pos.y;
			move = ft_clampd(step, 0, fabs(dist)) * (dir.y); /////// ??
			p->pos.y += move;
		}
	}
	// wrap tunnels
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
			sprites[npc->curr_frame]->instances[0].x = npc->pos.x;
			sprites[npc->curr_frame]->instances[0].y = npc->pos.y;
			
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
	//bool		jump_press;
	long		curr_time;
	long		elapsed_time;
	long		target_frame_dur;
	//bool		any_dir;

	so = (t_solong *)param;
	curr_time = get_time_ms();	
	elapsed_time = curr_time - so->last_ms;
	target_frame_dur = 1000 / TARGET_FPS;
	//jump_press = mlx_is_key_down(so->mlx, MLX_KEY_SPACE);
	//any_dir = false;
	// if (jump_press && !so->player.prev_jump_press)
	// {
	// 	// if (so->player.looking_left)
	// 	// 	set_current_anim(so, &so->player, so->player.walk_left, NUM_PLAYER_WALK_SPRITES);
	// 	// else
	// 	// 	set_current_anim(so, &so->player, so->player.walk_right, NUM_PLAYER_WALK_SPRITES);
	//  	// so->player.jumpbuf_ms = JUMPBUF_MS;
	// 	// any_dir = true;
	// }
	if (mlx_is_key_down(so->mlx, MLX_KEY_UP))
	{
		set_current_anim(so, &so->player, so->player.up.imgs, so->player.up.num_frames);
		so->player.velocity.y = -5.0;
		so->player.dir = DIR_UP;
		//update_sprites_position(&so->player, 0, -2, so);
		go_ahead(&so->player, 2.0, so, (double)elapsed_time / 1000.0, so->player.pos, so->player.pos);
		// any_dir = true;
		//animation_hook(so->player.curr_imgs, &so->player, curr_time, so->player.curr_num_frames);
	}
	if (mlx_is_key_down(so->mlx, MLX_KEY_DOWN))
	{
		set_current_anim(so, &so->player, so->player.down.imgs, so->player.down.num_frames);
		so->player.velocity.y = 5.0;
		so->player.dir = DIR_DOWN;
		//update_sprites_position(&so->player, 0, 2, so);
		go_ahead(&so->player, 2.0, so, (double)elapsed_time / 1000.0, so->player.pos, so->player.pos);
		// any_dir = true;
		//animation_hook(so->player.curr_imgs, &so->player, curr_time, so->player.curr_num_frames);
	}
	
	if (mlx_is_key_down(so->mlx, MLX_KEY_LEFT))
	{
		set_current_anim(so, &so->player, so->player.left.imgs, so->player.left.num_frames);
		so->player.velocity.x = -5.0;
		so->player.dir = DIR_LEFT;
		//update_sprites_position(&so->player, -2, 0, so);
		go_ahead(&so->player, 2.0, so, (double)elapsed_time / 1000.0, so->player.pos, so->player.pos);
		// so->player.looking_left = true;
		// any_dir = true;
		//animation_hook(so->player.curr_imgs, &so->player, curr_time, so->player.curr_num_frames);
	}
	else if (mlx_is_key_down(so->mlx, MLX_KEY_RIGHT))
	{
		set_current_anim(so, &so->player, so->player.right.imgs, so->player.right.num_frames);
		so->player.velocity.x = 5.0;
		so->player.dir = DIR_RIGHT;
		//update_sprites_position(&so->player, 2, 0, so);
		go_ahead(&so->player, 2.0, so, (double)elapsed_time / 1000.0, so->player.pos, so->player.pos);
		so->player.looking_left = false;
		// any_dir = true;
		//animation_hook(so->player.curr_imgs, &so->player, curr_time, so->player.curr_num_frames);
	}
	else
    {
		so->player.velocity.x = 0.0;
		so->player.velocity.y = 0.0;
	}
	//physics_update(so, curr_time);
	
	// if (!any_dir && so->player.on_ground)
	// {
	// 	// if (so->player.looking_left)
	// 	// 	set_current_anim(so, &so->player, so->player.idle_left, NUM_PLAYER_WALK_SPRITES);
	// 	// else
	// 	// 	set_current_anim(so, &so->player, so->player.idle_right, NUM_PLAYER_WALK_SPRITES);
	// }

	// render_interpolated(so,  so->player.curr_imgs[0]);
	// render_interpolated(so,  so->player.curr_imgs[1]);
	// render_interpolated(so,  so->player.curr_imgs[2]);
	if (elapsed_time >= target_frame_dur)
	{
		so->last_ms += target_frame_dur;
		print_player_pos(so);
		animation_hook(so->player.curr_imgs, &so->player, curr_time, so->player.curr_num_frames);
	}
	
}
