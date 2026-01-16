/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:08:07 by rstancu           #+#    #+#             */
/*   Updated: 2026/01/16 16:26:18 by rstancu          ###   ########.fr       */
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

void	anim(t_dir dir, t_solong *so, mlx_image_t **imgs, int num, t_character *p)
{
	p->dir = dir;
	if (p->curr_imgs == imgs)
		return ;
	if (p->curr_imgs)
		unable_sprites(p->curr_imgs, num);
	p->curr_imgs = imgs;
	p->curr_num_frames = NUM_PLAYER_SPRITES;
	p->last_anim_time = 0.0;
	p->curr_frame = 0;
}

void	anim_enemy(t_dir dir, t_solong *so, mlx_image_t **imgs, int num, t_character *p)
{
	p->dir = dir;
	if (p->curr_imgs == imgs)
		return ;
	if (p->curr_imgs)
		unable_sprites(p->curr_imgs, num);
	p->curr_imgs = imgs;
	p->curr_num_frames = NUM_ENEMY_SPRITES;
	p->last_anim_time = 0.0;
	p->curr_frame = 0;
}

void	catch_keys(t_character *p, t_solong *so, bool *updated)
{
	if (mlx_is_key_down(so->mlx, 265) || mlx_is_key_down(so->mlx, 87))
	{
		anim(DIR_UP, so, p->up.imgs, p->up.num_frames, p);
		*updated = true;
	}
	else if (mlx_is_key_down(so->mlx, 264) || mlx_is_key_down(so->mlx, 83))
	{
		anim(DIR_DOWN, so, p->down.imgs, p->down.num_frames, p);
		*updated = true;
	}
	else if (mlx_is_key_down(so->mlx, 263) || mlx_is_key_down(so->mlx, 65))
	{
		anim(DIR_LEFT, so, p->left.imgs, p->left.num_frames, p);
		*updated = true;
	}
	else if (mlx_is_key_down(so->mlx, 262) || mlx_is_key_down(so->mlx, 68))
	{
		anim(DIR_RIGHT, so, p->right.imgs, p->right.num_frames, p);
		*updated = true;
	}
	else
	{
		if (*updated)
			so->movements_count++;
	}
}

// TODO introduce animations in enemies movements

void	fps_hook(void *param)
{
	t_solong	*so;
	double		elapsed_time;
	double		dt;
	bool		updated;
	uint16_t	enemies;

	so = (t_solong *)param;
	enemies = 0;
	updated = false;
	elapsed_time = so->mlx->delta_time * 1000.0;
	dt = elapsed_time / 1000.0;
	if (dt > 0.05)
		dt = 0.05;
	so->player.last_pos.x = so->player.pos.x / TILESIZE;
	so->player.last_pos.y = so->player.pos.y / TILESIZE;
	so->player.dir = DIR_NONE;
	catch_keys(so, &updated, &so->player);
	catch_esc(so);
	go_ahead(&so->player, so, dt);
	print_movements(so);
	update_render_pos(&so->player, FOLLOW_SPEED_PX_S, dt);
	while (enemies < so->num_enemies)
	{
		so->enemies[enemies].common.last_pos.x
			= so->enemies[enemies].common.pos.x / TILESIZE;
		so->enemies[enemies].common.last_pos.y
			= so->enemies[enemies].common.pos.y / TILESIZE;
		go_ahead(&so->enemies[enemies].common, so, dt);
		update_render_pos(&so->enemies[enemies].common,
			FOLLOW_SPEED_PX_S, dt);
		enemies++;
	}
	enemies = 0;
	while (enemies < so->num_enemies)
	{
		animation_hook(so->enemies[enemies].common.curr_imgs, &so->enemies[enemies].common,
			elapsed_time, so->enemies[enemies].common.curr_num_frames);
		enemies++;
	}
	animation_hook(so->player.curr_imgs, &so->player, elapsed_time,
		so->player.curr_num_frames);
	get_collectible(so);
	if (can_exit(so))
		mlx_close_window(so->mlx);
}
