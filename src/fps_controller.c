/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:08:07 by rstancu           #+#    #+#             */
/*   Updated: 2025/11/12 10:33:10 by settes           ###   ########.fr       */
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
	t_int2	tilepos;
	t_pos	center_pos;
	t_int2	dir;
	t_int2	ahead_t;

	get_tile_and_center(p->pos, &tilepos, &center_pos);
	/* debug: show tile/center and pos */
	printf("[DBG] tilepos=(%d,%d) center=(%.1f,%.1f) pos=(%.1f,%.1f)\n", tilepos.x, tilepos.y, center_pos.x, center_pos.y, p->pos.x, p->pos.y);

	/* detect vertex (exact intersection of 4 tiles) */
	double local_x_in_tile = fmod(p->pos.x, (double)TILESIZE);
	double local_y_in_tile = fmod(p->pos.y, (double)TILESIZE);
	double vertex_eps = 0.0001;
	int on_vertex = ((local_x_in_tile < vertex_eps || fabs(local_x_in_tile - (double)TILESIZE) < vertex_eps) &&
			(local_y_in_tile < vertex_eps || fabs(local_y_in_tile - (double)TILESIZE) < vertex_eps));

	if (on_vertex && p->wish_dir != DIR_NONE)
	{
		/* tx/ty are the indices of the tile to the bottom-right of the
		   vertex (because integer truncation). The four tiles around the
		   vertex are: (tx-1,ty-1),(tx,ty-1),(tx-1,ty),(tx,ty). */
		t_int2 tile_idx;
		tile_idx.x = (int)(p->pos.x / TILESIZE);
		tile_idx.y = (int)(p->pos.y / TILESIZE);
		t_int2 candidate1 = {0, 0};
		t_int2 candidate2 = {0, 0};
		if (p->wish_dir == DIR_LEFT)
		{
			candidate1.x = tile_idx.x - 1; candidate1.y = tile_idx.y - 1; /* top-left */
			candidate2.x = tile_idx.x - 1; candidate2.y = tile_idx.y;     /* bottom-left */
		}
		else if (p->wish_dir == DIR_RIGHT)
		{
			candidate1.x = tile_idx.x;     candidate1.y = tile_idx.y - 1; /* top-right */
			candidate2.x = tile_idx.x;     candidate2.y = tile_idx.y;     /* bottom-right */
		}
		int walkable = 0;
		if (is_inside_map(so->map, candidate1.x, candidate1.y) && is_walkable(so->map, candidate1.x, candidate1.y))
			walkable = 1;
		if (!walkable && is_inside_map(so->map, candidate2.x, candidate2.y) && is_walkable(so->map, candidate2.x, candidate2.y))
			walkable = 1;
		printf("[DBG] vertex wish_dir=%d candidates=(%d,%d) and (%d,%d) walkable=%d\n", p->wish_dir, candidate1.x, candidate1.y, candidate2.x, candidate2.y, walkable);
		if (walkable)
			p->dir = p->wish_dir;
	}

	if (is_centered(so, p->pos))
	{
		if (p->wish_dir != DIR_NONE)
		{
			/* compute next tile for wish_dir and print walkable */
			t_int2 next;
			dir_to_vec(p->wish_dir, &next.x, &next.y);
			next.x = tilepos.x + next.x;
			next.y = tilepos.y + next.y;
			printf("[DBG] wish_dir=%d next_tile=(%d,%d)", p->wish_dir, next.x, next.y);
			if (is_inside_map(so->map, next.x, next.y))
				printf(" map_val=%d\n", so->map->arr[next.y][next.x]);
			else
				printf(" map_val=OUT_OF_BOUNDS\n");
			if (can_move_dir_from_tile(so, tilepos, p->wish_dir))
				p->dir = p->wish_dir;
		}
	}
	/* if current dir is blocked, stop and snap to center */
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
}

void	go_ahead(t_character *p, double step, t_solong *so, double dt)
{
	t_int2	dir;
	t_int2	next_tile;
	t_vec2	next_center;
	double	dist;
	double	move;
	t_int2	cur_tile;
	t_pos	cur_center;
	
	if (p->dir != DIR_NONE)
	{
		dir_to_vec(p->dir, &dir.x, &dir.y);
		/* get current tile and its center from player position */
		get_tile_and_center(p->pos, &cur_tile, &cur_center);
		update_sprites_position(p, dir.x * step, dir.y * step, so);
		step = p->speed_px_s * dt;
		next_tile.x = cur_tile.x + dir.x;
		next_tile.y = cur_tile.y + dir.y;
		next_center.x = (next_tile.x + 0.5) * (double)TILESIZE;
		next_center.y = (next_tile.y + 0.5) * (double)TILESIZE;
		
		//distance to the next center along the moving axis
		if (dir.x != 0)
		{
			p->pos.y = cur_center.y;
			dist = next_center.x - p->pos.x;
			move = ft_clampd(step, 0, fabs(dist)) * (dir.x); /////// ??
			p->pos.x += move;
		}
		else if (dir.y != 0)
		{
			p->pos.x = cur_center.x;
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
		/* request move up; will be applied when player is centered */
		so->player.wish_dir = DIR_UP;
		so->player.velocity.y = -200.0;
		printf("[DBG] UP pressed: wish_dir=%d dir=%d pos=(%.1f,%.1f)\n", so->player.wish_dir, so->player.dir, so->player.pos.x, so->player.pos.y);
		{
			t_int2 tilepos; t_pos centerpos; t_int2 next; int centered;
			get_tile_and_center(so->player.pos, &tilepos, &centerpos);
			centered = is_centered(so, so->player.pos);
			dir_to_vec(so->player.wish_dir, &next.x, &next.y);
			next.x = tilepos.x + next.x; next.y = tilepos.y + next.y;
			printf("[DBG] KEY_DEBUG tilepos=(%d,%d) center=(%.1f,%.1f) centered=%d next=(%d,%d)", tilepos.x, tilepos.y, centerpos.x, centerpos.y, centered, next.x, next.y);
			if (is_inside_map(so->map, next.x, next.y))
				printf(" map_val=%d\n", so->map->arr[next.y][next.x]);
			else
				printf(" map_val=OUT_OF_BOUNDS\n");
		}
		//update_sprites_position(&so->player, 0, -2, so);
		// any_dir = true;
		//animation_hook(so->player.curr_imgs, &so->player, curr_time, so->player.curr_num_frames);
	}
	if (mlx_is_key_down(so->mlx, MLX_KEY_DOWN))
	{
		set_current_anim(so, &so->player, so->player.down.imgs, so->player.down.num_frames);
		so->player.wish_dir = DIR_DOWN;
		so->player.velocity.y = 200.0;
		printf("[DBG] DOWN pressed: wish_dir=%d dir=%d pos=(%.1f,%.1f)\n", so->player.wish_dir, so->player.dir, so->player.pos.x, so->player.pos.y);
		//update_sprites_position(&so->player, 0, 2, so);
		// any_dir = true;
		//animation_hook(so->player.curr_imgs, &so->player, curr_time, so->player.curr_num_frames);
	}
	
	if (mlx_is_key_down(so->mlx, MLX_KEY_LEFT))
	{
		set_current_anim(so, &so->player, so->player.left.imgs, so->player.left.num_frames);
		so->player.wish_dir = DIR_LEFT;
		so->player.velocity.x = -200.0;
		printf("[DBG] LEFT pressed: wish_dir=%d dir=%d pos=(%.1f,%.1f)\n", so->player.wish_dir, so->player.dir, so->player.pos.x, so->player.pos.y);
		//update_sprites_position(&so->player, -2, 0, so);
		// so->player.looking_left = true;
		// any_dir = true;
		//animation_hook(so->player.curr_imgs, &so->player, curr_time, so->player.curr_num_frames);
	}
	else if (mlx_is_key_down(so->mlx, MLX_KEY_RIGHT))
	{
		set_current_anim(so, &so->player, so->player.right.imgs, so->player.right.num_frames);
		so->player.wish_dir = DIR_RIGHT;
		so->player.velocity.x = 200.0;
		printf("[DBG] RIGHT pressed: wish_dir=%d dir=%d pos=(%.1f,%.1f)\n", so->player.wish_dir, so->player.dir, so->player.pos.x, so->player.pos.y);
		//update_sprites_position(&so->player, 2, 0, so);
		{
			/* debug for LEFT/RIGHT: show tile and next tile value */
			t_int2 tilepos; t_pos centerpos; t_int2 next; int centered;
			get_tile_and_center(so->player.pos, &tilepos, &centerpos);
			centered = is_centered(so, so->player.pos);
			dir_to_vec(so->player.wish_dir, &next.x, &next.y);
			next.x = tilepos.x + next.x; next.y = tilepos.y + next.y;
			printf("[DBG] KEY_DEBUG tilepos=(%d,%d) center=(%.1f,%.1f) centered=%d next=(%d,%d)", tilepos.x, tilepos.y, centerpos.x, centerpos.y, centered, next.x, next.y);
			if (is_inside_map(so->map, next.x, next.y))
				printf(" map_val=%d\n", so->map->arr[next.y][next.x]);
			else
				printf(" map_val=OUT_OF_BOUNDS\n");
		}
		so->player.looking_left = false;
		// any_dir = true;
		//animation_hook(so->player.curr_imgs, &so->player, curr_time, so->player.curr_num_frames);
	}
	else
	{
		so->player.velocity.x = 0.0;
		so->player.velocity.y = 0.0;
	}

	/* After processing input, run promotion logic (center/vertex checks) so a
	   wish_dir can become dir before movement is applied. Then call go_ahead
	   once per tick (it will no-op if dir == DIR_NONE). */
	update_sprites_position(&so->player, 0.0, 0.0, so);
	{
		double dt = (double)elapsed_time / 1000.0;
		go_ahead(&so->player, 2.0, so, dt);
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
		//print_player_pos(so);
		animation_hook(so->player.curr_imgs, &so->player, curr_time, so->player.curr_num_frames);
	}
	
}
