/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-17 13:35:57 by rstancu           #+#    #+#             */
/*   Updated: 2025-11-17 13:35:57 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static inline int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

bool	init_wall(t_solong *so)
{
	so->text_cell = mlx_load_png(CELL_TEXTURE);
	if (!so->text_cell)
	{
		mlx_close_window(so->mlx);
		ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2);
		return (free_all(so));
	}
	so->cell_tile = mlx_texture_to_image(so->mlx, so->text_cell);
	if (!so->cell_tile)
	{
		mlx_close_window(so->mlx);
		ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2);
		return (free_all(so));
	}
	mlx_resize_image(so->cell_tile, TILESIZE, TILESIZE);
	return (true);
}

bool	create_background(t_solong *so)
{
	uint16_t	x;
	uint16_t	y;

	y = -1;
	so->background = mlx_new_image(so->mlx,
			so->map->width * TILESIZE, so->map->height * TILESIZE);
	if (!so->background)
		return (false);
	while (++y < so->background->height)
	{
		x = -1;
		while (++x < so->background->width)
			mlx_put_pixel(so->background, x, y, ft_pixel(0, 0, 0, 255));
	}
	if (mlx_image_to_window(so->mlx, so->background, 0, 0) == -1)
	{
		mlx_close_window(so->mlx);
		ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2);
		return (false);
	}
	return (true);
}

bool	init_background(t_solong *so)
{
	mlx_texture_t	*game_icon;

	game_icon = mlx_load_png(PLAYER_RIGHT_2);
	if (!game_icon)
	{
		mlx_close_window(so->mlx);
		ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2);
		return (false);
	}
	mlx_set_icon(so->mlx, game_icon);
	if (game_icon)
		mlx_delete_texture(game_icon);
	if (!create_background(so))
		return (false);
	if (!init_wall(so))
		return (false);
	return (true);
}

bool	init_mlx(t_solong *so)
{
	so->mlx = mlx_init(so->map->width * TILESIZE,
			so->map->height * TILESIZE, "Pacman!", true);
	if (!so->mlx)
	{
		ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2);
		return (free_all(so));
	}
	return (true);
}
