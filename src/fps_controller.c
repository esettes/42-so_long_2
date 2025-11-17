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

void	animation_hook(mlx_image_t **sprites, t_character *npc,
					double elapsed, int32_t num_sprites)
{
	npc->last_anim_time += elapsed;
	if (npc->last_anim_time >= ANIM_FRAME_INTERVAL)
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
	if (mlx_is_key_down(so->mlx, 265) || mlx_is_key_down(so->mlx, 87))
	{
		anim(DIR_UP, so, so->player.up.imgs, so->player.up.num_frames);
		*updated = true;
	}
	else if (mlx_is_key_down(so->mlx, 264) || mlx_is_key_down(so->mlx, 83))
	{
		anim(DIR_DOWN, so, so->player.down.imgs, so->player.down.num_frames);
		*updated = true;
	}
	else if (mlx_is_key_down(so->mlx, 263) || mlx_is_key_down(so->mlx, 65))
	{
		anim(DIR_LEFT, so, so->player.left.imgs, so->player.left.num_frames);
		*updated = true;
	}
	else if (mlx_is_key_down(so->mlx, 262) || mlx_is_key_down(so->mlx, 68))
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
	catch_esc(so);
	go_ahead(&so->player, so, dt);
	print_movements(so);
	update_render_pos(&so->player, FOLLOW_SPEED_PX_S, dt);
	animation_hook(so->player.curr_imgs, &so->player, elapsed_time,
		so->player.curr_num_frames);
	get_collectible(so);
	if (can_exit(so))
		mlx_close_window(so->mlx);
}
