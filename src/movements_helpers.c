/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:39:33 by rstancu           #+#    #+#             */
/*   Updated: 2025/11/13 11:15:16 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * gets in wich tile is player positioned and gets the center of that tile
 */
void	get_tile_and_center(t_pos pos, t_int2 *tilepos, t_pos *out)
{
	double	cx;
	double	cy;
	int32_t	tx;
	int32_t	ty;

	tx = (int32_t)ft_floor(((double)pos.x / (double)TILESIZE));
	ty = (int32_t)ft_floor(((double)pos.y / (double)TILESIZE));
	cx = (tx + 0.5f) * (double)TILESIZE;
	cy = (ty + 0.5f) * (double)TILESIZE;
	if (tilepos)
		tilepos->x = tx;
	if (tilepos)
		tilepos->y = ty;
	if (out)
		out->x = cx;
	if (out)
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
	else if (d == DIR_RIGHT)
		vx =  1;
	else if (d == DIR_UP)
		vy = -1;
	else if (d == DIR_DOWN)
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
    return (is_walkable(so->map, next_x, next_y));
}
