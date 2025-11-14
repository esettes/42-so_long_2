/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-14 11:34:37 by rstancu           #+#    #+#             */
/*   Updated: 2025-11-14 11:34:37 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static inline bool	free_arr_from_index(bool **arr, size_t index)
{
	size_t	i;

	i = 0;
	while (i < index)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (false);
}

static bool	init_dfs_arr(t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	map->visited = malloc(sizeof(bool *) * map->height);
	if (!map->visited)
		return (false);
	while (i < map->height)
	{
		map->visited[i] = malloc(sizeof(bool) * map->width);
		if (!map->visited[i])
		{
			return (free_arr_from_index(map->visited, i));
		}
		j = 0;
		while (j < map->width)
		{
			map->visited[i][j] = false;
			j++;
		}
		i++;
	}
	return (true);
}

static inline bool is_walkable_tile(int32_t tile)
{
	if (tile == 1)
		return (false);
	if (tile == 0 || tile == M_COLLECTIBLE
		|| tile == M_EXIT || tile == M_PLAYER)
		return (true);
	return (false);
}

/**
 * Starts solve with players position
 */
void	dfs_fill(t_map *map, bool **visit, int32_t x, int32_t y)
{
	int32_t	cell;

	if (x < 0 || x >= (int32_t)map->width || y < 0 || y >= (int32_t)map->height)
		return ;
	if (visit[y][x])
		return ;
	cell = map->arr[y][x];
	if (!is_walkable_tile(cell))
		return ;
	visit[y][x] = true;
	dfs_fill(map, visit, x + 1, y);
	dfs_fill(map, visit, x - 1, y);
	dfs_fill(map, visit, x, y + 1);
	dfs_fill(map, visit, x, y - 1);
}

bool	is_map_playable(t_map *map, t_character *p)
{
	int32_t	y;
	int32_t	x;
	bool	check;

	if (!init_dfs_arr(map))
		return (false);
	dfs_fill(map, map->visited, (int32_t)(p->pos.x / TILESIZE),
		(int32_t)(p->pos.y / TILESIZE));
	y = 0;
	check = true;
	while (y < (int32_t)map->height)
	{
		x = 0;
		while (x < (int32_t)map->width)
		{
			if ((map->arr[y][x] == M_COLLECTIBLE || map->arr[y][x] == M_EXIT)
				&& !map->visited[y][x])
				check = false;
			x++;
		}
		y++;
	}
	free_visited(map->visited, map->height);
	return (check);
}
