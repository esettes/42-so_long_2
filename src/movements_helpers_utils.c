/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_helpers_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-15 12:43:48 by rstancu           #+#    #+#             */
/*   Updated: 2025-11-15 12:43:48 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int32_t	is_inside_map(const t_map *m, int32_t tile_x, int32_t tile_y)
{
	return (tile_x >= 0 && (size_t)tile_x < m->width && tile_y >= 0
		&& (size_t)tile_y < m->height);
}

int32_t	is_wall(const t_map *m, int32_t tile_x, int32_t tile_y)
{
	if (!is_inside_map(m, tile_x, tile_y))
		return (1);
	if (m->arr[tile_y][tile_x] == 1)
		return (true);
	return (false);
}

int32_t	is_walkable(t_map *m, int32_t tile_x, int32_t tile_y)
{
	int32_t	n;

	if (!is_inside_map(m, tile_x, tile_y))
		return (0);
	n = m->arr[tile_y][tile_x];
	return (n != 1);
}
