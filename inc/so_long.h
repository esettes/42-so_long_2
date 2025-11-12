/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:24:24 by rstancu           #+#    #+#             */
/*   Updated: 2025/11/11 10:30:24 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SO_LONG_H
# define SO_LONG_H

#include <math.h>
#include <stdbool.h>
#include <MLX42.h>
#include <fcntl.h>
#include <get_next_line.h>
#include <libft.h>
#include <config.h>
#include <sys/time.h>

typedef	struct s_pos
{
	double	x;
	double	y;
}	t_pos;

typedef	struct s_cell
{
	int32_t	x;	// w
	int32_t	y;	// h
}	t_cell;

typedef struct anim
{
	mlx_texture_t	**text;
	mlx_image_t		**imgs;
	uint16_t		num_frames;
}               t_anim;

/**
 * @param coyote_ms float, remaining time of coyote jump
 * @param jumpbuf_ms float, remaining time of jump-buffer
 */
typedef	struct s_character
{
	t_pos		pos;
	t_anim		right;
	t_anim		left;
	t_anim		up;
	t_anim		idle;
	t_anim		down;
	long		last_anim_time;
	long		curr_frame;
	t_vec2		velocity;
	t_vec2		hitbox;
	mlx_image_t **curr_imgs;
	uint16_t	curr_num_frames;
	bool		looking_left;
	t_dir		dir;
	t_dir		wish_dir;
	double		speed_px_s;
}	t_character;

typedef	struct s_npc
{
	t_pos		pos;		
	t_anim		right;
	t_anim		left;
	t_anim		up;
	t_anim		idle;
	t_anim		down;
}	t_npc;


typedef struct s_collectible
{
	t_pos		pos;
	t_anim		anim;
}	t_collectible;


typedef	struct s_map
{
	char			**raw;
	int32_t			**arr;
	uint16_t		**collision_map;
	size_t			height;
	size_t			width;
	t_collectible	*collects;
	uint16_t		num_collects;
	t_pos			exit_pos;
}	t_map;


typedef	struct s_solong
{
	t_map			*map;
	mlx_image_t		*background;
	mlx_t			*mlx;
	mlx_image_t		*screen;
	t_character		player;
	t_character		prev_player_status;
	mlx_texture_t	*text_cell;
	mlx_image_t		*cell_tile;
	uint16_t		num_enemies;
	t_character		*enemies;
	long			last_ms;
	int				fps;
	int				last_fps_update;
	long			accum_ms;
	mlx_image_t		*hud_db;
	mlx_image_t		*hud_text_img;
	mlx_image_t 	*hud_foreground;
	double			center_epsilon_px; // ~0.5 * step @90 FPS

}	t_solong;

bool	read_file(t_solong *so, char *file);
bool	init_solong(t_solong *so, char *file);
bool init_player(t_solong *so, t_character *p);

void	parse_array(int32_t **map, size_t w, size_t h);
bool	resize_pixels(xpm_t *xpm, uint32_t new_w, uint32_t new_h);
///////////////////// Debug

void	print_player_pos(t_solong *so);

long	get_time_ms(void);
void	fps_hook(void *param);

void	unable_sprites(mlx_image_t **sprites, int num);

///////////////////// Physics
void	physics_update(t_solong *so, long now);

void	render_interpolated(t_solong *so, mlx_image_t *img);
void	fps_controller(void *param);
void	print_map(t_map *map, t_solong *so);

// void	init_collision_flags(t_solong *so);
// void	init_height_map(t_solong *so);
bool	init_emenies(t_solong *so);
bool	init_player_anims(t_solong *so);
///////////////////// Animations initialization
bool	init_enemy_down(t_character *e, mlx_t *mlx, char *one, char *two);
bool	init_enemy_up(t_character *e, mlx_t *mlx, char *one, char *two);
bool	init_enemy_right(t_character *e, mlx_t *mlx, char *one, char *two);
bool	init_enemy_left(t_character *e, mlx_t *mlx, char *one, char *two);

bool	free_all(t_solong *so);


int32_t	is_inside_map(const t_map *m, int32_t tile_x, int32_t tile_y);
int32_t	is_wall(const t_map *m, int32_t tile_x, int32_t tile_y);
int32_t	is_walkable(t_map *m, int32_t tile_x, int32_t tile_y);
void	get_tile_and_center(t_pos pos, t_int2 *tilepos, t_pos *out);
void	dir_to_vec(t_dir d, int32_t *dir_x, int32_t *dir_y);
int32_t	is_centered(const t_solong *so, t_pos pos);
int32_t	can_move_dir_from_tile(const t_solong *so, t_int2 tilepos, t_dir d);

#endif
