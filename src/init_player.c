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
	if (mlx_image_to_window(mlx, p->up.imgs[0], p->pos.x, p->pos.y) == -1)
		return (false);
	if (mlx_image_to_window(mlx, p->up.imgs[1], p->pos.x, p->pos.y) == -1)
		return (false);
	if (mlx_image_to_window(mlx, p->up.imgs[2], p->pos.x, p->pos.y) == -1)
		return (false);
	p->up.imgs[0]->instances[0].enabled = false;
	p->up.imgs[1]->instances[0].enabled = false;
	p->up.imgs[2]->instances[0].enabled = false;
	if (mlx_image_to_window(mlx, p->down.imgs[0], p->pos.x, p->pos.y) == -1)
		return (false);
	if (mlx_image_to_window(mlx, p->down.imgs[1], p->pos.x, p->pos.y) == -1)
		return (false);
	if (mlx_image_to_window(mlx, p->down.imgs[2], p->pos.x, p->pos.y) == -1)
		return (false);
	p->down.imgs[0]->instances[0].enabled = false;
	p->down.imgs[1]->instances[0].enabled = false;
	p->down.imgs[2]->instances[0].enabled = false;
	if (mlx_image_to_window(mlx, p->left.imgs[0], p->pos.x, p->pos.y) == -1)
		return (false);
	if (mlx_image_to_window(mlx, p->left.imgs[1], p->pos.x, p->pos.y) == -1)
		return (false);
	if (mlx_image_to_window(mlx, p->left.imgs[2], p->pos.x, p->pos.y) == -1)
		return (false);
	p->left.imgs[0]->instances[0].enabled = false;
	p->left.imgs[1]->instances[0].enabled = false;
	p->left.imgs[2]->instances[0].enabled = false;
	if (mlx_image_to_window(mlx, p->right.imgs[0], p->pos.x, p->pos.y) == -1)
		return (false);
	if (mlx_image_to_window(mlx, p->right.imgs[1], p->pos.x, p->pos.y) == -1)
		return (false);
	if (mlx_image_to_window(mlx, p->right.imgs[2], p->pos.x, p->pos.y) == -1)
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
	p->speed_px_s = 200.0; // 200 pixels per second
	if (!init_player_anims(so))
		return (false);
	if (!put_first_sprites_to_win(p, so->mlx))
		return (false);
	/* Enable the initial sprite so the player is visible on start. Set the
	   current animation to 'down' (facing down) and enable its first frame. */
	p->curr_imgs = p->down.imgs;
	p->curr_num_frames = p->down.num_frames;
	p->curr_frame = 0;
	p->last_anim_time = get_time_ms();
	if (p->curr_imgs && p->curr_imgs[0])
	{
		p->curr_imgs[0]->instances[0].enabled = true;
		p->curr_imgs[0]->instances[0].x = (int)p->pos.x;
		p->curr_imgs[0]->instances[0].y = (int)p->pos.y;
	}
	return (true);
}
