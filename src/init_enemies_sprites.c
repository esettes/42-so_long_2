/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemies_sprites.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-15 13:54:21 by rstancu           #+#    #+#             */
/*   Updated: 2025-11-15 13:54:21 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	init_anim_enemy_red(t_character *e, mlx_t *mlx)
{
	if (!init_enemy_up(e, mlx, ENEMY_RED_UP_1, ENEMY_RED_UP_2))
		return (false);
	if (!init_enemy_down(e, mlx, ENEMY_RED_DOWN_1, ENEMY_RED_DOWN_2))
		return (false);
	if (!init_enemy_right(e, mlx, ENEMY_RED_RIGHT_1, ENEMY_RED_RIGHT_2))
		return (false);
	if (!init_enemy_left(e, mlx, ENEMY_RED_LEFT_1, ENEMY_RED_LEFT_2))
		return (false);
	return (true);
}

bool	init_anim_enemy_blue(t_character *e, mlx_t *mlx)
{
	if (!init_enemy_up(e, mlx, ENEMY_BLUE_UP_1, ENEMY_BLUE_UP_2))
		return (false);
	if (!init_enemy_down(e, mlx, ENEMY_BLUE_DOWN_1, ENEMY_BLUE_DOWN_2))
		return (false);
	if (!init_enemy_right(e, mlx, ENEMY_BLUE_RIGHT_1, ENEMY_BLUE_RIGHT_2))
		return (false);
	if (!init_enemy_left(e, mlx, ENEMY_BLUE_LEFT_1, ENEMY_BLUE_LEFT_2))
		return (false);
	return (true);
}

bool	init_anim_enemy_orange(t_character *e, mlx_t *mlx)
{
	if (!init_enemy_up(e, mlx, ENEMY_ORANGE_UP_1, ENEMY_ORANGE_UP_2))
		return (false);
	if (!init_enemy_down(e, mlx, ENEMY_ORANGE_DOWN_1, ENEMY_ORANGE_DOWN_2))
		return (false);
	if (!init_enemy_right(e, mlx, ENEMY_ORANGE_RIGHT_1, ENEMY_ORANGE_RIGHT_2))
		return (false);
	if (!init_enemy_left(e, mlx, ENEMY_ORANGE_LEFT_1, ENEMY_ORANGE_LEFT_2))
		return (false);
	return (true);
}

bool	init_anim_enemy_pink(t_character *e, mlx_t *mlx)
{
	if (!init_enemy_up(e, mlx, ENEMY_PINK_UP_1, ENEMY_PINK_UP_2))
		return (false);
	if (!init_enemy_down(e, mlx, ENEMY_PINK_DOWN_1, ENEMY_PINK_DOWN_2))
		return (false);
	if (!init_enemy_right(e, mlx, ENEMY_PINK_RIGHT_1, ENEMY_PINK_RIGHT_2))
		return (false);
	if (!init_enemy_left(e, mlx, ENEMY_PINK_LEFT_1, ENEMY_PINK_LEFT_2))
		return (false);
	return (true);
}
