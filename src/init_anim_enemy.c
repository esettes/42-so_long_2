/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_anim_enemy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-11 09:43:58 by rstancu           #+#    #+#             */
/*   Updated: 2025-11-11 09:43:58 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	init_enemy_down(t_character *e, mlx_t *mlx, char *one, char *two)
{
	e->down.text = malloc(sizeof(mlx_texture_t *) * NUM_ENEMY_SPRITES);
	if (!e->down.text)
		return (false);
	e->down.num_frames = NUM_ENEMY_SPRITES;
	e->down.text[0] = mlx_load_png(one);
	e->down.text[1] = mlx_load_png(two);
	e->down.imgs = malloc(sizeof(mlx_image_t *) * NUM_ENEMY_SPRITES);
	if (!e->down.imgs)
		return (false);
	e->down.imgs[0] = mlx_texture_to_image(mlx, e->down.text[0]);
	mlx_resize_image(e->down.imgs[0], TILESIZE, TILESIZE);
	e->down.imgs[1] = mlx_texture_to_image(mlx, e->down.text[1]);
	mlx_resize_image(e->down.imgs[1], TILESIZE, TILESIZE);
	return (true);
}

bool	init_enemy_up(t_character *e, mlx_t *mlx, char *one, char *two)
{
	e->up.text = malloc(sizeof(mlx_texture_t *) * NUM_ENEMY_SPRITES);
	if (!e->up.text)
		return (false);
	e->up.num_frames = NUM_ENEMY_SPRITES;
	e->up.text[0] = mlx_load_png(one);
	e->up.text[1] = mlx_load_png(two);
	e->up.imgs = malloc(sizeof(mlx_image_t *) * NUM_ENEMY_SPRITES);
	if (!e->up.imgs)
		return (false);
	e->up.imgs[0] = mlx_texture_to_image(mlx, e->up.text[0]);
	mlx_resize_image(e->up.imgs[0], TILESIZE, TILESIZE);
	e->up.imgs[1] = mlx_texture_to_image(mlx, e->up.text[1]);
	mlx_resize_image(e->up.imgs[1], TILESIZE, TILESIZE);
	return (true);
}

bool	init_enemy_right(t_character *e, mlx_t *mlx, char *one, char *two)
{
	e->right.text = malloc(sizeof(mlx_texture_t *) * NUM_ENEMY_SPRITES);
	if (!e->right.text)
		return (false);
	e->right.num_frames = NUM_ENEMY_SPRITES;
	e->right.text[0] = mlx_load_png(one);
	e->right.text[1] = mlx_load_png(two);
	e->right.imgs = malloc(sizeof(mlx_image_t *) * NUM_ENEMY_SPRITES);
	if (!e->right.imgs)
		return (false);
	e->right.imgs[0] = mlx_texture_to_image(mlx, e->right.text[0]);
	mlx_resize_image(e->right.imgs[0], TILESIZE, TILESIZE);
	e->right.imgs[1] = mlx_texture_to_image(mlx, e->right.text[1]);
	mlx_resize_image(e->right.imgs[1], TILESIZE, TILESIZE);
	return (true);
}

bool	init_enemy_left(t_character *e, mlx_t *mlx, char *one, char *two)
{
	e->left.text = malloc(sizeof(mlx_texture_t *) * NUM_ENEMY_SPRITES);
	if (!e->left.text)
		return (false);
	e->left.num_frames = NUM_ENEMY_SPRITES;
	e->left.text[0] = mlx_load_png(one);
	e->left.text[1] = mlx_load_png(two);
	e->left.imgs = malloc(sizeof(mlx_image_t *) * NUM_ENEMY_SPRITES);
	if (!e->left.imgs)
		return (false);
	e->left.imgs[0] = mlx_texture_to_image(mlx, e->left.text[0]);
	mlx_resize_image(e->left.imgs[0], TILESIZE, TILESIZE);
	e->left.imgs[1] = mlx_texture_to_image(mlx, e->left.text[1]);
	mlx_resize_image(e->left.imgs[1], TILESIZE, TILESIZE);
	return (true);
}
