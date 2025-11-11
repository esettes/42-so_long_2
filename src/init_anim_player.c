/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_anim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:47:24 by rstancu           #+#    #+#             */
/*   Updated: 2025/11/11 10:28:39 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	init_anim_down(t_character *p, mlx_t *mlx)
{
	uint16_t	i;

	i = 0;
	p->down.text = malloc(sizeof(mlx_texture_t *) * NUM_PLAYER_SPRITES);
	if (!p->down.text)
		return (false);
	p->down.num_frames = NUM_PLAYER_SPRITES;
	p->down.text[0] = mlx_load_png(PLAYER_DOWN_1);
	p->down.text[1] = mlx_load_png(PLAYER_DOWN_2);
	p->down.text[2] = mlx_load_png(PLAYER_DOWN_3);
	p->down.imgs = malloc(sizeof(mlx_image_t *) * NUM_PLAYER_SPRITES);
	if (!p->down.imgs)
		return (false);
	p->down.imgs[0] = mlx_texture_to_image(mlx, p->down.text[0]);
	mlx_resize_image(p->down.imgs[0], TILESIZE, TILESIZE);
	p->down.imgs[1] = mlx_texture_to_image(mlx, p->down.text[1]);
	mlx_resize_image(p->down.imgs[1], TILESIZE, TILESIZE);
	p->down.imgs[2] = mlx_texture_to_image(mlx, p->down.text[2]);
	mlx_resize_image(p->down.imgs[2], TILESIZE, TILESIZE);
	return (true);
}

static bool init_anim_up(t_character *p, mlx_t *mlx)
{
	uint16_t	i;

	i = 0;
	p->up.text = malloc(sizeof(mlx_texture_t *) * NUM_PLAYER_SPRITES);
	if (!p->up.text)
		return (false);
	p->up.num_frames = NUM_PLAYER_SPRITES;
	p->up.text[0] = mlx_load_png(PLAYER_UP_1);
	p->up.text[1] = mlx_load_png(PLAYER_UP_2);
	p->up.text[2] = mlx_load_png(PLAYER_UP_3);
	p->up.imgs = malloc(sizeof(mlx_image_t *) * NUM_PLAYER_SPRITES);
	if (!p->up.imgs)
		return (false);
	p->up.imgs[0] = mlx_texture_to_image(mlx, p->up.text[0]);
	if (!p->up.imgs[0])
	{
		ft_putendl_fd("Error: Can't load player up animation img 0", 2);
		return (false);
	}
	mlx_resize_image(p->up.imgs[0], TILESIZE, TILESIZE);
	p->up.imgs[1] = mlx_texture_to_image(mlx, p->up.text[1]);
	mlx_resize_image(p->up.imgs[1], TILESIZE, TILESIZE);
	p->up.imgs[2] = mlx_texture_to_image(mlx, p->up.text[2]);
	mlx_resize_image(p->up.imgs[2], TILESIZE, TILESIZE);
	return (true);
}

static bool	init_anim_right(t_character *p, mlx_t *mlx)
{
	uint16_t	i;

	i = 0;
	p->right.text = malloc(sizeof(mlx_texture_t *) * NUM_PLAYER_SPRITES);
	if (!p->right.text)
		return (false);
	p->right.num_frames = NUM_PLAYER_SPRITES;
	p->right.text[0] = mlx_load_png(PLAYER_RIGHT_1);
	p->right.text[1] = mlx_load_png(PLAYER_RIGHT_2);
	p->right.text[2] = mlx_load_png(PLAYER_RIGHT_3);
	p->right.imgs = malloc(sizeof(mlx_image_t *) * NUM_PLAYER_SPRITES);
	if (!p->right.imgs)
		return (false);
	p->right.imgs[0] = mlx_texture_to_image(mlx, p->right.text[0]);
	mlx_resize_image(p->right.imgs[0], TILESIZE, TILESIZE);
	p->right.imgs[1] = mlx_texture_to_image(mlx, p->right.text[1]);
	mlx_resize_image(p->right.imgs[1], TILESIZE, TILESIZE);
	p->right.imgs[2] = mlx_texture_to_image(mlx, p->right.text[2]);
	mlx_resize_image(p->right.imgs[2], TILESIZE, TILESIZE);
	return (true);
}

static bool	init_anim_left(t_character *p, mlx_t *mlx)
{
	uint16_t	i;

	i = 0;
	p->left.text = malloc(sizeof(mlx_texture_t *) * NUM_PLAYER_SPRITES);
	if (!p->left.text)
		return (false);
	p->left.num_frames = NUM_PLAYER_SPRITES;
	p->left.text[0] = mlx_load_png(PLAYER_LEFT_1);
	p->left.text[1] = mlx_load_png(PLAYER_LEFT_2);
	p->left.text[2] = mlx_load_png(PLAYER_LEFT_3);
	p->left.imgs = malloc(sizeof(mlx_image_t *) * NUM_PLAYER_SPRITES);
	if (!p->left.imgs)
		return (false);
	p->left.imgs[0] = mlx_texture_to_image(mlx, p->left.text[0]);
	mlx_resize_image(p->left.imgs[0], TILESIZE, TILESIZE);
	p->left.imgs[1] = mlx_texture_to_image(mlx, p->left.text[1]);
	mlx_resize_image(p->left.imgs[1], TILESIZE, TILESIZE);
	p->left.imgs[2] = mlx_texture_to_image(mlx, p->left.text[2]);
	mlx_resize_image(p->left.imgs[2], TILESIZE, TILESIZE);
	return (true);
}

bool	init_player_anims(t_solong *so)
{
	if (!init_anim_up(&so->player, so->mlx))
		return (false);
	if (!init_anim_down(&so->player, so->mlx))
		return (false);
	if (!init_anim_right(&so->player, so->mlx))
		return (false);
	if (!init_anim_left(&so->player, so->mlx))
		return (false);
	return (true);
}
