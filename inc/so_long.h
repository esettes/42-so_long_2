/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:24:24 by rstancu           #+#    #+#             */
/*   Updated: 2025/11/08 16:05:44 by settes           ###   ########.fr       */
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
	size_t			num_frames;
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
	bool		looking_left;
}	t_character;

typedef	struct s_npc
{
	t_pos		pos;		
	mlx_image_t	*sprite;
}	t_npc;


typedef	struct s_map
{
	char			**raw;
	int32_t			**arr;
	uint16_t		**collision_map;
	uint16_t		**height_map;	// pixels
	size_t			height;
	size_t			weight;
	size_t			num_platforms;
	size_t			original_num_lines;
	mlx_image_t		**floor;
	size_t			*floor_collsion;
}	t_map;


typedef	struct s_solong
{
	t_map		*map;
	mlx_image_t	*background;
	mlx_t		*mlx;
	mlx_image_t	*screen;
	t_character	player;
	t_character	prev_player_status;
	long		last_ms;
	int			fps;
	int			last_fps_update;
	long		accum_ms;
	bool		first_imgs;
	mlx_image_t	*hud_db;
	mlx_image_t	*hud_text_img;
	mlx_image_t *hud_foreground;
}	t_solong;

bool	read_file(t_solong *so, char *file);


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


// void	init_collision_flags(t_solong *so);
// void	init_height_map(t_solong *so);
#endif
