/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_mandatory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-13 15:21:38 by rstancu           #+#    #+#             */
/*   Updated: 2025-11-13 15:21:38 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	check_map_limits(t_solong *so)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < so->map->height)
	{
		x = 0;
		while (x < so->map->width)
		{
			if (y == 0 || y == so->map->height - 1
				|| x == 0 || x == so->map->width - 1)
			{
				if (so->map->arr[y][x] != M_WALL)
				{
					ft_putendl_fd("Error: Map not surrounded by walls.", 2);
					return (false);
				}
			}
			x++;
		}
		y++;
	}
	return (true);
}

