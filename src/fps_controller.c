/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:08:07 by rstancu           #+#    #+#             */
/*   Updated: 2025/11/08 15:20:10 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_sprites_position(t_character *p, double x, double y, t_solong *so)
{
	//size_t	i;
	double	tmp_x;
	double	tmp_y;

	//i = 0;
	tmp_x = (p->pos.x + x);// * p->velocity.x;
	tmp_y = (p->pos.y + y);// * p->velocity.y;
	p->pos.x = ft_clampd(tmp_x, 0, so->map->weight * TILESIZE - TILESIZE);
	p->pos.y = ft_clampd(tmp_y, 0, (so->map->height * TILESIZE) + so->map->floor_collsion[0] + 3 - (TILESIZE * 2));
	// printf("player pos: x[%f] y[%f]\n", p->pos.x, p->pos.y);
}

void	animation_hook(t_solong *so, mlx_image_t **sprites, t_character *npc, long now)
{
	// long		elapsed_time;
	// long		target_frame_dur;

	// elapsed_time = now - so->last_ms;
	// target_frame_dur = 100 / TARGET_FPS;
	// if (elapsed_time >= target_frame_dur)
	// {
	// 	so->last_ms += target_frame_dur;
	 (void)so;
	 (void)sprites;
		//physics_update(so, now);
		if (now - npc->last_anim_time >= ANIM_FRAME_INTERVAL)
		{
			// npc->curr_frame = (npc->curr_frame + 1) % NUM_PLAYER_WALK_SPRITES;
			// npc->last_anim_time += ANIM_FRAME_INTERVAL;
			
			// sprites[npc->curr_frame]->instances[0].enabled = true;
			// sprites[(npc->curr_frame + NUM_PLAYER_WALK_SPRITES - 1) % NUM_PLAYER_WALK_SPRITES]->instances[0].enabled = false;
			// sprites[npc->curr_frame]->instances[0].x = npc->pos.x;
			// sprites[npc->curr_frame]->instances[0].y = npc->pos.y;
			
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
	// p->last_anim_time = get_time_ms();
	// p->curr_frame = 0;
	// render_interpolated(so,  p->curr_imgs[0]);
	// render_interpolated(so,  p->curr_imgs[1]);
	// render_interpolated(so,  p->curr_imgs[2]);
}

void	fps_hook(void *param)
{
	t_solong	*so;
	bool		jump_press;
	long		curr_time;
	long		elapsed_time;
	long		target_frame_dur;
	bool		any_dir;

	so = (t_solong *)param;
	curr_time = get_time_ms();	
	elapsed_time = curr_time - so->last_ms;
	target_frame_dur = 1000 / TARGET_FPS;
	jump_press = mlx_is_key_down(so->mlx, MLX_KEY_SPACE);
	any_dir = false;
	if (jump_press && !so->player.prev_jump_press)
	{
		// if (so->player.looking_left)
		// 	set_current_anim(so, &so->player, so->player.walk_left, NUM_PLAYER_WALK_SPRITES);
		// else
		// 	set_current_anim(so, &so->player, so->player.walk_right, NUM_PLAYER_WALK_SPRITES);
	 	// so->player.jumpbuf_ms = JUMPBUF_MS;
		// any_dir = true;
	}
	so->player.prev_jump_press = jump_press;
	if (mlx_is_key_down(so->mlx, MLX_KEY_UP))
	{
		// set_current_anim(so, &so->player, so->player.up, NUM_PLAYER_WALK_SPRITES);
		// so->player.velocity.y = -200.0;
		// update_sprites_position(&so->player, 0, -2, so);
		// any_dir = true;
	}
	if (mlx_is_key_down(so->mlx, MLX_KEY_DOWN))
	{
		// set_current_anim(so, &so->player, so->player.up, NUM_PLAYER_WALK_SPRITES);
		// so->player.velocity.y = 200.0;
		// update_sprites_position(&so->player, 0, 2, so);
		// any_dir = true;
	}
	
	if (mlx_is_key_down(so->mlx, MLX_KEY_LEFT))
	{
		// set_current_anim(so, &so->player, so->player.walk_left, NUM_PLAYER_WALK_SPRITES);
		// so->player.velocity.x = -200.0;
		// update_sprites_position(&so->player, -2, 0, so);
		// so->player.looking_left = true;
		// any_dir = true;
	}
	else if (mlx_is_key_down(so->mlx, MLX_KEY_RIGHT))
	{
		// set_current_anim(so, &so->player, so->player.walk_right, NUM_PLAYER_WALK_SPRITES);
		// so->player.velocity.x = 200.0;
		// update_sprites_position(&so->player, 2, 0, so);
		// so->player.looking_left = false;
		// any_dir = true;
	}
	else
        so->player.velocity.x = 0.0;
	physics_update(so, curr_time);
	
	if (!any_dir && so->player.on_ground)
	{
		// if (so->player.looking_left)
		// 	set_current_anim(so, &so->player, so->player.idle_left, NUM_PLAYER_WALK_SPRITES);
		// else
		// 	set_current_anim(so, &so->player, so->player.idle_right, NUM_PLAYER_WALK_SPRITES);
	}

	render_interpolated(so,  so->player.curr_imgs[0]);
	render_interpolated(so,  so->player.curr_imgs[1]);
	render_interpolated(so,  so->player.curr_imgs[2]);
	if (elapsed_time >= target_frame_dur)
	{
		so->last_ms += target_frame_dur;
		print_player_pos(so);
		animation_hook(so, so->player.curr_imgs, &so->player, curr_time);
	}
	
}
