/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_anim_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:47:24 by rstancu           #+#    #+#             */
/*   Updated: 2025/11/11 13:23:48 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	init_player_anims(t_solong *so)
{
	if (!init_anim_up(&so->player, so->mlx))
		return (false);
	if (!init_anim_down(&so->player, so->mlx))
		return (false);
	if (!init_anim_right(&so->player, so->mlx))
		return (false);
	if (!init_anim_left(&so->player, so->mlx))
		return (false);
	return (true);
}
