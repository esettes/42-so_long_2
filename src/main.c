/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:23:45 by rstancu           #+#    #+#             */
/*   Updated: 2026/01/16 16:03:39 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static inline void	close_mlx(t_solong *so)
{
	mlx_close_hook(so->mlx, fps_hook, so);
	mlx_close_window(so->mlx);
	free_all(so);
	mlx_terminate(so->mlx);
}

int32_t	main(int32_t argc, char **argv)
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
	if (!init_enemies(&solong))
	{
		free_all(&solong);
		return (false);
	}
	mlx_loop_hook(solong.mlx, fps_hook, &solong);
	mlx_loop(solong.mlx);
	close_mlx(&solong);
	return (MLX_SUCCESS);
}
