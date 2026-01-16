#include "so_long.h"

void	set_scatter_target(t_enemy *e, t_solong *so)
{
	if (e->type == GHOST_BLINKY)
	{
		e->target.x = so->map->width - 1;
		e->target.y = 0;
	}
	else if (e->type == GHOST_PINKY)
	{
		e->target.x = 0;
		e->target.y = 0;
	}
	else if (e->type == GHOST_INKY)
	{
		e->target.x = so->map->width - 1;
		e->target.y = so->map->height - 1;
	}
	else if (e->type == GHOST_CLYDE)
	{
		e->target.x = 0;
		e->target.y = so->map->height - 1;
	}
}

/**
 * Target is the current player position
 */
void	set_chase_target_blinky(t_enemy *e, t_solong *so)
{
	e->target.x = so->player.pos.x;
	e->target.y = so->player.pos.y;
}

/**
 * Target is 4 tiles ahead of the player's current direction
 */
void compute_pinky_target(t_solong *so, t_enemy *e)
{
	int32_t	dir_x;
	int32_t	dir_y;
	int32_t	player_tile_x;
	int32_t	player_tile_y;

	dir_to_vec(so->player.dir, &dir_x, &dir_y);
	player_tile_x = (int32_t)(so->player.pos.x) / TILESIZE;
	player_tile_y = (int32_t)(so->player.pos.y) / TILESIZE;
	e->target.x = player_tile_x + dir_x * 4;
	e->target.y = player_tile_y + dir_y * 4;
}

void compute_inky_intermediate_tile(t_solong *so, t_int2 *out)
{
	int32_t	dir_x;
	int32_t	dir_y;
	int32_t	player_tile_x;
	int32_t	player_tile_y;

	dir_to_vec(so->player.dir, &dir_x, &dir_y);
	player_tile_x = (int32_t)(so->player.pos.x) / TILESIZE;
	player_tile_y = (int32_t)(so->player.pos.y) / TILESIZE;
	out->x = player_tile_x + dir_x * 2;
	out->y = player_tile_y + dir_y * 2;
}

/**
 * gets the first blinky enemy position
 * red
 */
t_enemy *get_first_blinky_position(t_solong *so)
{
	size_t	i;

	i = 0;
	while (i < so->num_enemies)
	{
		if (so->enemies[i].type == GHOST_BLINKY)
		{
			return (&so->enemies[i]);
		}
		i++;
	}
	return (NULL);
}

/**
 * blue
 */
void set_chase_target_inky(t_enemy *e, t_solong *so)
{
	t_enemy *blinky;
	t_int2	intermediate_tile;
	int32_t	vector_x;
	int32_t	vector_y;

	blinky = get_first_blinky_position(so);
	if (!blinky)
	{
		e->target.x = so->player.pos.x;
		e->target.y = so->player.pos.y;
		return ;
	}
	compute_inky_intermediate_tile(so, &intermediate_tile);
	vector_x = intermediate_tile.x - (int32_t)(so->player.pos.x) / TILESIZE;
	vector_y = intermediate_tile.y - (int32_t)(so->player.pos.y) / TILESIZE;
	e->target.x = intermediate_tile.x + vector_x;
	e->target.y = intermediate_tile.y + vector_y;
}

/**
 * clyde chases the player if farther than 8 tiles, else goes to corner
 * orange
 */

void set_chase_target_clyde(t_enemy *e, t_solong *so)
{
	int32_t	dx;
	int32_t	dy;

	dx = (int32_t)(so->player.pos.x) / TILESIZE - (int32_t)(e->common.pos.x) / TILESIZE;
	dy = (int32_t)(so->player.pos.y) / TILESIZE - (int32_t)(e->common.pos.y) / TILESIZE;
	if ((dx * dx + dy * dy) > (8 * 8))
	{
		e->target.x = so->player.pos.x;
		e->target.y = so->player.pos.y;
	}
	else
	{
		e->target.x = 0;
		e->target.y = so->map->height - 1;
	}
}

void	update_ghost_target(t_solong *so, t_enemy *e)
{
	if (e->mode == GHOST_MODE_FRIGHTENED)
	{
		e->target.x = e->common.pos.x;
		e->target.y = e->common.pos.y;
	}
	if (e->mode == GHOST_MODE_SCATTER)
	{
		set_scatter_target(e, so);
		return ;
	}
	if (e->mode == GHOST_MODE_CHASE)
	{
		if (e->type == GHOST_BLINKY)
			set_chase_target_blinky(e, so);
		else if (e->type == GHOST_PINKY)
			compute_pinky_target(so, e);
		else if (e->type == GHOST_INKY)
			set_chase_target_inky(e, so);
		else if (e->type == GHOST_CLYDE)
			set_chase_target_clyde(e, so);
	}
}
