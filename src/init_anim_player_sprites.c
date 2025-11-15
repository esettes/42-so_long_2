/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_anim_player_sprites.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-15 13:46:26 by rstancu           #+#    #+#             */
/*   Updated: 2025-11-15 13:46:26 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	resize_imgs(mlx_image_t **imgs, uint16_t num)
{
	uint16_t	i;

	i = 0;
	while (i < num)
	{
		if (!mlx_resize_image(imgs[i], TILESIZE, TILESIZE))
			return (false);
		i++;
	}
	return (true);
}

bool	init_anim_down(t_character *p, mlx_t *mlx)
{
	p->down.text = malloc(sizeof(mlx_texture_t *) * NUM_PLAYER_SPRITES);
	if (!p->down.text)
		return (false);
	p->down.num_frames = NUM_PLAYER_SPRITES;
	p->down.text[0] = mlx_load_png(PLAYER_DOWN_1);
	p->down.text[1] = mlx_load_png(PLAYER_DOWN_2);
	p->down.text[2] = mlx_load_png(PLAYER_DOWN_3);
	if (!p->down.text[0] || !p->down.text[1] || !p->down.text[2])
	{
		ft_putendl_fd("Error: Can't load player down animation textures", 2);
		return (false);
	}
	p->down.imgs = malloc(sizeof(mlx_image_t *) * NUM_PLAYER_SPRITES);
	if (!p->down.imgs)
		return (false);
	p->down.imgs[0] = mlx_texture_to_image(mlx, p->down.text[0]);
	p->down.imgs[1] = mlx_texture_to_image(mlx, p->down.text[1]);
	p->down.imgs[2] = mlx_texture_to_image(mlx, p->down.text[2]);
	if (!p->down.imgs[0] || !p->down.imgs[1] || !p->down.imgs[2])
	{
		ft_putendl_fd("Error: Can't load player down animation img 0", 2);
		return (false);
	}
	resize_imgs(p->down.imgs, NUM_PLAYER_SPRITES);
	return (true);
}

bool	init_anim_up(t_character *p, mlx_t *mlx)
{
	p->up.text = malloc(sizeof(mlx_texture_t *) * NUM_PLAYER_SPRITES);
	if (!p->up.text)
		return (false);
	p->up.num_frames = NUM_PLAYER_SPRITES;
	p->up.text[0] = mlx_load_png(PLAYER_UP_1);
	p->up.text[1] = mlx_load_png(PLAYER_UP_2);
	p->up.text[2] = mlx_load_png(PLAYER_UP_3);
	if (!p->up.text[0] || !p->up.text[1] || !p->up.text[2])
	{
		ft_putendl_fd("Error: Can't load player up animation textures", 2);
		return (false);
	}
	p->up.imgs = malloc(sizeof(mlx_image_t *) * NUM_PLAYER_SPRITES);
	if (!p->up.imgs)
		return (false);
	p->up.imgs[0] = mlx_texture_to_image(mlx, p->up.text[0]);
	p->up.imgs[1] = mlx_texture_to_image(mlx, p->up.text[1]);
	p->up.imgs[2] = mlx_texture_to_image(mlx, p->up.text[2]);
	if (!p->up.imgs[0] || !p->up.imgs[1] || !p->up.imgs[2])
	{
		ft_putendl_fd("Error: Can't load player up animation img 0", 2);
		return (false);
	}
	resize_imgs(p->up.imgs, NUM_PLAYER_SPRITES);
	return (true);
}

bool	init_anim_right(t_character *p, mlx_t *mlx)
{
	p->right.text = malloc(sizeof(mlx_texture_t *) * NUM_PLAYER_SPRITES);
	if (!p->right.text)
		return (false);
	p->right.num_frames = NUM_PLAYER_SPRITES;
	p->right.text[0] = mlx_load_png(PLAYER_RIGHT_1);
	p->right.text[1] = mlx_load_png(PLAYER_RIGHT_2);
	p->right.text[2] = mlx_load_png(PLAYER_RIGHT_3);
	if (!p->right.text[0] || !p->right.text[1] || !p->right.text[2])
	{
		ft_putendl_fd("Error: Can't load player right animation textures", 2);
		return (false);
	}
	p->right.imgs = malloc(sizeof(mlx_image_t *) * NUM_PLAYER_SPRITES);
	if (!p->right.imgs)
		return (false);
	p->right.imgs[0] = mlx_texture_to_image(mlx, p->right.text[0]);
	p->right.imgs[1] = mlx_texture_to_image(mlx, p->right.text[1]);
	p->right.imgs[2] = mlx_texture_to_image(mlx, p->right.text[2]);
	if (!p->right.imgs[0] || !p->right.imgs[1] || !p->right.imgs[2])
	{
		ft_putendl_fd("Error: Can't load player right animation img 0", 2);
		return (false);
	}
	resize_imgs(p->right.imgs, NUM_PLAYER_SPRITES);
	return (true);
}

bool	init_anim_left(t_character *p, mlx_t *mlx)
{
	p->left.text = malloc(sizeof(mlx_texture_t *) * NUM_PLAYER_SPRITES);
	if (!p->left.text)
		return (false);
	p->left.num_frames = NUM_PLAYER_SPRITES;
	p->left.text[0] = mlx_load_png(PLAYER_LEFT_1);
	p->left.text[1] = mlx_load_png(PLAYER_LEFT_2);
	p->left.text[2] = mlx_load_png(PLAYER_LEFT_3);
	if (!p->left.text[0] || !p->left.text[1] || !p->left.text[2])
	{
		ft_putendl_fd("Error: Can't load player left animation textures", 2);
		return (false);
	}
	p->left.imgs = malloc(sizeof(mlx_image_t *) * NUM_PLAYER_SPRITES);
	if (!p->left.imgs)
		return (false);
	p->left.imgs[0] = mlx_texture_to_image(mlx, p->left.text[0]);
	p->left.imgs[1] = mlx_texture_to_image(mlx, p->left.text[1]);
	p->left.imgs[2] = mlx_texture_to_image(mlx, p->left.text[2]);
	if (!p->left.imgs[0] || !p->left.imgs[1] || !p->left.imgs[2])
	{
		ft_putendl_fd("Error: Can't load player left animation img 0", 2);
		return (false);
	}
	resize_imgs(p->left.imgs, NUM_PLAYER_SPRITES);
	return (true);
}
