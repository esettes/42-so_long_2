/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-11 09:44:25 by rstancu           #+#    #+#             */
/*   Updated: 2025-11-11 09:44:25 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	init_each_enemy(t_solong *so, uint16_t *i)
{
	if (*i % 4 == 0)
	{
		if (!init_anim_enemy_red(&so->enemies[*i], so->mlx))
			return (false);
	}
	else if (*i % 4 == 1)
	{
		if (!init_anim_enemy_blue(&so->enemies[*i], so->mlx))
			return (false);
	}
	else if (*i % 4 == 2)
	{
		if (!init_anim_enemy_orange(&so->enemies[*i], so->mlx))
			return (false);
	}
	else
	{
		if (!init_anim_enemy_pink(&so->enemies[*i], so->mlx))
			return (false);
	}
	return (true);
}

bool	init_emenies(t_solong *so)
{
	uint16_t	i;

	i = 0;
	so->enemies = malloc(sizeof(t_character) * so->num_enemies);
	if (!so->enemies)
		return (false);
	while (i < so->num_enemies)
	{
		init_each_enemy(so, &i);
		i++;
	}
	return (true);
}
