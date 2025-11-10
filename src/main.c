/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:23:45 by rstancu           #+#    #+#             */
/*   Updated: 2025/11/10 11:59:07 by settes           ###   ########.fr       */
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

//bool	init_solong(t_solong *so)

int32_t main(int32_t argc, char **argv)
{
	t_solong solong;
	long now;
	mlx_texture_t *game_icon;
	mlx_image_t *icon;

	(void)argc;
	now = get_time_ms();


	
	solong.map = malloc(sizeof(t_map));

	
	
	solong.last_ms = now;
	solong.fps = 0;
	solong.last_fps_update = now;
	solong.player.last_anim_time = now;
	
	solong.player.curr_frame = now;
	solong.player.velocity.x = 0.0;
	solong.player.velocity.y = 0.0;

	solong.first_imgs = true;
	solong.player.on_ground = true;
	solong.accum_ms = 0;
	if (!read_file(&solong, argv[1]))
	{
		ft_putendl_fd("Error: Can't open file.", 2);
		return (1);
	}
	solong.mlx = mlx_init(solong.map->weight * TILESIZE, solong.map->height * TILESIZE, "Pacman!", true);
	game_icon = mlx_load_png(PLAYER_RIGHT_2);
	icon = mlx_new_image(solong.mlx, TILESIZE, TILESIZE);
	if (!solong.mlx)
	{
		ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2);
		return(1);
	}
	solong.hud_db = mlx_new_image(solong.mlx, 180, 20);
	//realloc_map(solong.map->arr, &solong);
	solong.background = mlx_new_image(solong.mlx, solong.map->weight * TILESIZE, solong.map->height * TILESIZE);
	//solong.hud_foreground = mlx_new_image(solong.mlx, solong.map->weight * TILESIZE, solong.map->height * TILESIZE);
	//mlx_set_icon(solong.mlx, game_icon);
	for (uint32_t i = 0; i < solong.background->width; ++i)
	{
		for (uint32_t y = 0; y < solong.background->height; ++y)
		{
			uint32_t color = ft_pixel(0, 0, 0, 255);
			mlx_put_pixel(solong.background, i, y, color);
		}
	}	
	if (mlx_image_to_window(solong.mlx, solong.background, 0, 0) == -1)
	{
		mlx_close_window(solong.mlx);
		ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2);
		return(1);
	}
	// debug
	// for (uint32_t i = 0; i < solong.hud_db->width; ++i)
	// {
	// 	for (uint32_t j = 0; j < solong.hud_db->height; ++j)
	// 	{
	// 		uint32_t color = ft_pixel(0, 0, 0, 255);
	// 		mlx_put_pixel(solong.hud_db, i, j, color);
	// 	}
	// }
	
	

	//init_height_map(&solong);
	// if (mlx_image_to_window(solong.mlx, solong.hud_foreground, 0, 0) == -1)
	// {
	// 	mlx_close_window(solong.mlx);
	// 	ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2);
	// 	return (1);
	// }
	// if (mlx_image_to_window(solong.mlx, solong.hud_db, solong.player.pos.x, solong.player.pos.y - 10) == -1)
	// {
	// 	mlx_close_window(solong.mlx);
	// 	ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2);
	// 	return (1);
	// }
	

	// if (!resize_pixels(xpm, TILESIZE, TILESIZE))
	// {
	// 	mlx_close_window(solong.mlx);
	// 	ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2);
	// 	return(1);
	// }

	//mlx_loop_hook(solong.mlx, fps_controller, &solong);
	mlx_loop_hook(solong.mlx, fps_hook, &solong);
	
	//mlx_key_hook(solong.mlx, &key_hook, &solong);
	mlx_loop(solong.mlx);
	//mlx_delete_image(solong.mlx, solong.hud_db);
	// if (solong.hud_text_img)
	// 	mlx_delete_image(solong.mlx, solong.hud_text_img);
	// if (solong.hud_foreground)
	// 	mlx_delete_image(solong.mlx, solong.hud_foreground);
	if (solong.background)
		mlx_delete_image(solong.mlx, solong.background);
	//free_all(&solong);
	//mlx_close_hook(solong.mlx, fps_controller, &solong);
	mlx_close_hook(solong.mlx, fps_hook, &solong);
	mlx_close_window(solong.mlx);
	mlx_terminate(solong.mlx);

	

	return (MLX_SUCCESS);
}
