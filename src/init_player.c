/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:49:21 by rstancu           #+#    #+#             */
/*   Updated: 2025/11/11 13:39:40 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	put_imgs_to_win(mlx_t *mlx, mlx_image_t **imgs, t_pos pos)
{
	uint16_t	i;

	i = 0;
	while (i < NUM_PLAYER_SPRITES)
	{
		if (mlx_image_to_window(mlx, imgs[i], pos.x, pos.y) == -1)
			return (false);
		imgs[i]->instances[0].enabled = false;
		i++;
	}
	return (true);
}

static bool	put_first_sprites_to_win(t_character *p, mlx_t *mlx)
{
	if (!put_imgs_to_win(mlx, p->up.imgs, p->render_pos))
		return (false);
	if (!put_imgs_to_win(mlx, p->down.imgs, p->render_pos))
		return (false);
	if (!put_imgs_to_win(mlx, p->left.imgs, p->render_pos))
		return (false);
	if (!put_imgs_to_win(mlx, p->right.imgs, p->render_pos))
		return (false);
	return (true);
}

bool	init_player(t_solong *so, t_character *p)
{
	p->hitbox.x = TILESIZE / 2;
	p->hitbox.y = TILESIZE / 2;
	p->wish_dir = DIR_NONE;
	p->dir = DIR_NONE;
	p->speed_px_s = PX_PER_SECONDS;
	so->center_epsilon_px = compute_center_epsilon_px(p->speed_px_s);
	if (!init_player_anims(so))
		return (false);
	if (!put_first_sprites_to_win(p, so->mlx))
		return (false);
	p->curr_imgs = p->down.imgs;
	p->curr_num_frames = p->down.num_frames;
	p->curr_frame = 0;
	p->last_anim_time = 0.0;
	p->last_pos.x = (int32_t)(p->pos.x / TILESIZE);
	p->last_pos.y = (int32_t)(p->pos.y / TILESIZE);
	if (p->curr_imgs && p->curr_imgs[0])
	{
		p->curr_imgs[0]->instances[0].enabled = true;
		p->curr_imgs[0]->instances[0].x = (int)p->render_pos.x;
		p->curr_imgs[0]->instances[0].y = (int)p->render_pos.y;
	}
	return (true);
}
