/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:03:05 by rstancu           #+#    #+#             */
/*   Updated: 2025/11/13 11:33:13 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

void	print_map(t_map *map, t_solong *so)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->arr[i][j] == 1)
				mlx_image_to_window(so->mlx, so->cell_tile,
								j * TILESIZE, i * TILESIZE);
			j++;
		}
		i++;
	}
	print_exit(so);
}
