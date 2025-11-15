/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:23:45 by rstancu           #+#    #+#             */
/*   Updated: 2025/11/15 16:06:23 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define WIDTH 512
#define HEIGHT 512


static inline int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}


void ft_hook(void* param)
{
	t_solong *solong = param;

	if (mlx_is_key_down(solong->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(solong->mlx);
	if (mlx_is_key_down(solong->mlx, MLX_KEY_UP))
		solong->background->instances[0].y -= 5;
	if (mlx_is_key_down(solong->mlx, MLX_KEY_DOWN))
		solong->background->instances[0].y += 5;
	if (mlx_is_key_down(solong->mlx, MLX_KEY_LEFT))
		solong->background->instances[0].x -= 5;
	if (mlx_is_key_down(solong->mlx, MLX_KEY_RIGHT))
		solong->background->instances[0].x += 5;
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

bool	init_background(t_solong *so)
{
	mlx_texture_t *game_icon;

	game_icon = mlx_load_png(PLAYER_RIGHT_2);
	if (!game_icon)
	{
		mlx_close_window(so->mlx);
		ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2);
		return (free_all(so));
	}
	mlx_set_icon(so->mlx, game_icon);
	if (game_icon)
		mlx_delete_texture(game_icon);
	so->background = mlx_new_image(so->mlx,
		so->map->width * TILESIZE, so->map->height * TILESIZE);
	if (!so->background)
		return (false);
	for (uint32_t i = 0; i < so->background->width; ++i)
	{
		for (uint32_t y = 0; y < so->background->height; ++y)
		{
			uint32_t color = ft_pixel(0, 0, 0, 255);
			mlx_put_pixel(so->background, i, y, color);
		}
	}	
	if (mlx_image_to_window(so->mlx, so->background, 0, 0) == -1)
	{
		mlx_close_window(so->mlx);
		ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2);
		return (false);
	}
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

int32_t main(int32_t argc, char **argv)
{
	t_solong		solong;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./so_long <map_file>", 2);
		return (1);
	}
	solong.is_running = false;
	if (!init_solong(&solong, argv[1]))
		return (free_all(&solong));
	if (!init_mlx(&solong))
		return (1);
	if (!init_background(&solong))
		return (free_all(&solong));
	print_map(solong.map, &solong);
	if (!init_player(&solong, &solong.player))
	{
		free_map(solong.map, solong.mlx);
		return (false);
	}
	mlx_loop_hook(solong.mlx, fps_hook, &solong);
	mlx_loop(solong.mlx);
	mlx_close_hook(solong.mlx, fps_hook, &solong);
	mlx_close_window(solong.mlx);
	free_all(&solong);
	mlx_terminate(solong.mlx);
	return (MLX_SUCCESS);
}
