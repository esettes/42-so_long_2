/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics_controller.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:54:17 by rstancu           #+#    #+#             */
/*   Updated: 2025/11/10 11:32:03 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Try jump
 * Applies gravity and smooth to vertical velocity
 * Updates position
 */
void	physics_step(t_character *p, double dt, t_map *map)
{
	double	down;
	//double	tmp_x;
	//double	tmp_y;

	(void)map;
	// printf("dt: %.2f ms\n", dt * 1000.0);
	coyote_update(p, dt * 1000.0);
	try_jump(p);
	if (DRAG > 0.0)
	{
		down = expf(-DRAG * dt);
		p->velocity.y = p->velocity.y * down + (GRAVITY / DRAG) * (1.0 - down);
	}
	else
		p->velocity.y += GRAVITY * dt;
	// tmp_x = p->pos.x + (p->velocity.x * dt);
	// tmp_y = p->pos.y + (p->velocity.y * dt);
	// p->pos.x = ft_clampd(tmp_x, 0, (map->height * TILESIZE) + map->floor_collsion[0] + 3 - (TILESIZE * 2));
	// p->pos.y = ft_clampd(tmp_y, 0, (map->height * TILESIZE) + map->floor_collsion[0] + 3 - (TILESIZE * 2));
	if (!p->on_ground)
	{
		p->pos.x += (p->velocity.x * dt);
		p->pos.y += (p->velocity.y * dt);
	}
	solve_vertical_space(p, map);
}

void	physics_update(t_solong *so, long now)
{
	long	delta;
	
	delta = now - so->last_ms;
	if (delta < 0)
		delta = 0;
	if (delta > MAX_ACC_MS)
		delta = MAX_ACC_MS;
	//so->accum_ms = ft_clampi(so->accum_ms + delta, 0, MAX_ACC_MS);
	so->accum_ms += delta;
	so->last_ms = now;
	if (so->accum_ms >= PHYS_DT_MS)
	{
		so->prev_player_status = so->player;
		physics_step(&so->player, (double)PHYS_DT_MS / 1000.0, so->map);
		so->accum_ms -= PHYS_DT_MS;
	}
	
}

void	render_interpolated(t_solong *so, mlx_image_t *img)
{
	double	alpha;
	double	render_x;
	double	render_y;

	alpha = (double)so->accum_ms / (double)PHYS_DT_MS;
	alpha = ft_clampd(alpha, 0.0, 1.0);
	render_x = so->prev_player_status.pos.x + (so->player.pos.x - so->prev_player_status.pos.x) * alpha;
	render_y = so->prev_player_status.pos.y + (so->player.pos.y - so->prev_player_status.pos.y) * alpha;
	// render_x = ft_lerp(so->prev_player_status.pos.x, so->player.pos.x, alpha);
	// render_y = ft_lerp(so->prev_player_status.pos.y, so->player.pos.y, alpha);
	img->instances[0].x = (int)render_x;
	img->instances[0].y = (int)render_y;
}
