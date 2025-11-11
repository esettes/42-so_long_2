/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-11 13:39:33 by rstancu           #+#    #+#             */
/*   Updated: 2025-11-11 13:39:33 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"


int32_t	is_inside_map(const t_map *m, int32_t tile_x, int32_t tile_y)
{
	return (tile_x >= 0 && tile_x < m->width && tile_y >= 0 && tile_y < m->height);
}

int32_t	is_wall(const t_map *m, int32_t tile_x, int32_t tile_y)
{
	if (!is_inside_map(m, tile_x, tile_y))
		return 1;
	if (m->arr[tile_y][tile_x] == 1)
		return (true);
	return (false);
}

int32_t	is_walkable(const t_map *m, int32_t tile_x, int32_t tile_y)
{
	int32_t	n;

	if (!is_inside_map(m, tile_x, tile_y))
		return 0;
	n = m->arr[tile_y][tile_x];
	return (n != 1);
}

/**
 * gets in wich tile is player positioned and gets the center of that tile
 */
void	get_tile_and_center(t_pos pos, t_int2 *tilepos, t_pos *out)
{
	double	cx;
	double	cy;
	int32_t		tx;
	int32_t		ty;

	tx = (int32_t)(pos.x / TILESIZE);
	ty = (int32_t)(pos.y / TILESIZE);
	cx = (tx + 0.5f) * (double)TILESIZE;
	cy = (ty + 0.5f) * (double)TILESIZE;
	if (tilepos->x)
		tilepos->x = tx;
	if (tilepos->y)
		tilepos->y = ty;
	if (out->x)
		out->x = cx;
	if (out->y)
		out->y = cy;
}

void	dir_to_vec(t_dir d, int32_t *dir_x, int32_t *dir_y)
{
	int32_t	vx;
	int32_t	vy;

	vx = 0;
	vy = 0;
	if (d == DIR_LEFT)
		vx = -1;
	if (d == DIR_RIGHT)
		vx =  1;
	if (d == DIR_UP)
		vy = -1;
	if (d == DIR_DOWN)
		vy =  1;
	if (dir_x)
		*dir_x = vx;
	if (dir_y)
		*dir_y = vy;
}

int32_t	is_centered(const t_solong *so, t_pos pos)
{
	double	dir_x;
	double	dir_y;
	t_pos	center_pos;

	center_pos.x = 0;
	center_pos.y = 0;
	get_tile_and_center(pos, NULL, &center_pos);
	dir_x = pos.x - center_pos.x;
	dir_y = pos.y - center_pos.y;
	if (dir_x > -so->center_epsilon_px && dir_x < so->center_epsilon_px &&
		dir_y > -so->center_epsilon_px && dir_y < so->center_epsilon_px)
		return (true);
	return (false);
}

int32_t	can_move_dir_from_tile(const t_solong *so, t_int2 tilepos, t_dir d)
{	
	int32_t	next_x;
	int32_t	next_y;
	int32_t dir_x;
	int32_t dir_y;

	dir_x = 0;
	dir_y = 0;
    dir_to_vec(d, &dir_x, &dir_y);
    next_x = tilepos.x + dir_x;
    next_y = tilepos.y + dir_y;
    return is_walkable(&so->map, next_x, next_y);
}
