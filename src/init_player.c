/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-11 09:49:21 by rstancu           #+#    #+#             */
/*   Updated: 2025-11-11 09:49:21 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool init_player(t_solong *so, t_character *p)
{
	p->velocity.x = 0.0;
	p->velocity.y = 0.0;
	p->hitbox.x = TILESIZE / 2;
	p->hitbox.y = TILESIZE / 2;
	p->looking_left = false;
	init_player_anims(so);
	return (true);
}