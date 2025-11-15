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

bool	put_first_sprites_to_win(t_character *p, mlx_t *mlx)
{
	if (mlx_image_to_window(mlx, p->up.imgs[0], p->render_pos.x, p->render_pos.y) == -1)
		return (false);
	if (mlx_image_to_window(mlx, p->up.imgs[1], p->render_pos.x, p->render_pos.y) == -1)
		return (false);
	if (mlx_image_to_window(mlx, p->up.imgs[2], p->render_pos.x, p->render_pos.y) == -1)
		return (false);
	p->up.imgs[0]->instances[0].enabled = false;
	p->up.imgs[1]->instances[0].enabled = false;
	p->up.imgs[2]->instances[0].enabled = false;
	if (mlx_image_to_window(mlx, p->down.imgs[0], p->render_pos.x, p->render_pos.y) == -1)
		return (false);
	if (mlx_image_to_window(mlx, p->down.imgs[1], p->render_pos.x, p->render_pos.y) == -1)
		return (false);
	if (mlx_image_to_window(mlx, p->down.imgs[2], p->render_pos.x, p->render_pos.y) == -1)
		return (false);
	p->down.imgs[0]->instances[0].enabled = false;
	p->down.imgs[1]->instances[0].enabled = false;
	p->down.imgs[2]->instances[0].enabled = false;
	if (mlx_image_to_window(mlx, p->left.imgs[0], p->render_pos.x, p->render_pos.y) == -1)
		return (false);
	if (mlx_image_to_window(mlx, p->left.imgs[1], p->render_pos.x, p->render_pos.y) == -1)
		return (false);
	if (mlx_image_to_window(mlx, p->left.imgs[2], p->render_pos.x, p->render_pos.y) == -1)
		return (false);
	p->left.imgs[0]->instances[0].enabled = false;
	p->left.imgs[1]->instances[0].enabled = false;
	p->left.imgs[2]->instances[0].enabled = false;
	if (mlx_image_to_window(mlx, p->right.imgs[0], p->render_pos.x, p->render_pos.y) == -1)
		return (false);
	if (mlx_image_to_window(mlx, p->right.imgs[1], p->render_pos.x, p->render_pos.y) == -1)
		return (false);
	if (mlx_image_to_window(mlx, p->right.imgs[2], p->render_pos.x, p->render_pos.y) == -1)
		return (false);
	p->right.imgs[0]->instances[0].enabled = false;
	p->right.imgs[1]->instances[0].enabled = false;
	p->right.imgs[2]->instances[0].enabled = false;
	return (true);
}

bool init_player(t_solong *so, t_character *p)
{
	p->velocity.x = 0.0;
	p->velocity.y = 0.0;
	p->hitbox.x = TILESIZE / 2;
	p->hitbox.y = TILESIZE / 2;
	p->looking_left = false;
	p->wish_dir = DIR_NONE;
	p->dir = DIR_NONE;
	p->speed_px_s = PX_PER_SECONDS;
	so->center_epsilon_px = compute_center_epsilon_px(p->speed_px_s);
	if (!init_player_anims(so))
		return (false);
	if (!put_first_sprites_to_win(p, so->mlx))
		return (false);
	/* Enable the initial sprite so the player is visible on start. Set the
	   current animation to 'down' (facing down) and enable its first frame. */
	p->curr_imgs = p->down.imgs;
	p->curr_num_frames = p->down.num_frames;
	p->curr_frame = 0;
	p->accum_sec = 0.0;
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
