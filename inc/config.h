/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:29:38 by rstancu           #+#    #+#             */
/*   Updated: 2025/11/15 15:59:43 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# define TILESIZE			32
# define TARGET_FPS			120
# define ANIM_FRAME_INTERVAL 80.0
# define FOLLOW_SPEED_PX_S	1000.0
# define PX_PER_SECONDS		200.0

# define PHYS_DT_MS	8
# define MAX_ACC_MS	250

typedef enum e_map_typos
{
	M_SPACE = 0,
	M_WALL,
	M_PLAYER,
	M_COLLECTIBLE,
	M_ENEMY,
	M_EXIT
}	t_map_typos;

typedef enum e_dir
{
	DIR_NONE = 0,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_DOWN
}	t_dir;

typedef enum e_ghost_type
{
    GHOST_BLINKY,    // red, chaser
    GHOST_PINKY,     // pink, ambusher
    GHOST_INKY,      // cyan, unpredictable
    GHOST_CLYDE      // orange, chase then scatter
}   t_ghost_type;

typedef enum e_ghost_mode
{
    GHOST_MODE_SCATTER,	// each ghost goes to its corner
    GHOST_MODE_CHASE,	// each ghost targets the player
    GHOST_MODE_FRIGHTENED,	// blue and vulnerable
    GHOST_MODE_EATEN	// returning to the ghost house
}   t_ghost_mode;

///// PLAYER
# define NUM_PLAYER_SPRITES	3
# define PLAYER_UP_1 "./tiles/up_1.png"
# define PLAYER_UP_2 "./tiles/up_2.png"
# define PLAYER_UP_3 "./tiles/up_3.png"

# define PLAYER_DOWN_1 "./tiles/down_1.png"
# define PLAYER_DOWN_2 "./tiles/down_2.png"
# define PLAYER_DOWN_3 "./tiles/down_3.png"

# define PLAYER_RIGHT_1 "./tiles/right_1.png"
# define PLAYER_RIGHT_2 "./tiles/right_2.png"
# define PLAYER_RIGHT_3 "./tiles/right_3.png"

# define PLAYER_LEFT_1 "./tiles/left_1.png"
# define PLAYER_LEFT_2 "./tiles/left_2.png"
# define PLAYER_LEFT_3 "./tiles/left_3.png"

/////////////////////////////////// ENEMIES
# define NUM_ENEMY_SPRITES	2
# define ENEMY_RED_UP_1 "./tiles/red_up_1.png"
# define ENEMY_RED_UP_2 "./tiles/red_up_2.png"
# define ENEMY_RED_DOWN_1 "./tiles/red_down_1.png"
# define ENEMY_RED_DOWN_2 "./tiles/red_down_2.png"
# define ENEMY_RED_RIGHT_1 "./tiles/red_right_1.png"
# define ENEMY_RED_RIGHT_2 "./tiles/red_right_2.png"
# define ENEMY_RED_LEFT_1 "./tiles/red_left_1.png"
# define ENEMY_RED_LEFT_2 "./tiles/red_left_2.png"
///////////////////////////////////
# define ENEMY_BLUE_UP_1 "./tiles/blue_up_1.png"
# define ENEMY_BLUE_UP_2 "./tiles/blue_up_2.png"
# define ENEMY_BLUE_DOWN_1 "./tiles/blue_down_1.png"
# define ENEMY_BLUE_DOWN_2 "./tiles/blue_down_2.png"
# define ENEMY_BLUE_RIGHT_1 "./tiles/blue_right_1.png"
# define ENEMY_BLUE_RIGHT_2 "./tiles/blue_right_2.png"
# define ENEMY_BLUE_LEFT_1 "./tiles/blue_left_1.png"
# define ENEMY_BLUE_LEFT_2 "./tiles/blue_left_2.png"
///////////////////////////////////
# define ENEMY_ORANGE_UP_1 "./tiles/orange_up_1.png"
# define ENEMY_ORANGE_UP_2 "./tiles/orange_up_2.png"
# define ENEMY_ORANGE_DOWN_1 "./tiles/orange_down_1.png"
# define ENEMY_ORANGE_DOWN_2 "./tiles/orange_down_2.png"
# define ENEMY_ORANGE_RIGHT_1 "./tiles/orange_right_1.png"
# define ENEMY_ORANGE_RIGHT_2 "./tiles/orange_right_2.png"
# define ENEMY_ORANGE_LEFT_1 "./tiles/orange_left_1.png"
# define ENEMY_ORANGE_LEFT_2 "./tiles/orange_left_2.png"
///////////////////////////////////
# define ENEMY_PINK_UP_1 "./tiles/pink_up_1.png"
# define ENEMY_PINK_UP_2 "./tiles/pink_up_2.png"
# define ENEMY_PINK_DOWN_1 "./tiles/pink_down_1.png"
# define ENEMY_PINK_DOWN_2 "./tiles/pink_down_2.png"
# define ENEMY_PINK_RIGHT_1 "./tiles/pink_right_1.png"
# define ENEMY_PINK_RIGHT_2 "./tiles/pink_right_2.png"
# define ENEMY_PINK_LEFT_1 "./tiles/pink_left_1.png"
# define ENEMY_PINK_LEFT_2 "./tiles/pink_left_2.png"

# define CELL_TEXTURE "./tiles/cell.png"

# define COLLECT_1 "./tiles/cherry.png"
# define COLLECT_2 "./tiles/strawberry.png"
# define COLLECT_3 "./tiles/orange.png"
# define COLLECT_4 "./tiles/apple.png"

# define EXIT_TEXTURE "./tiles/exit.png"

#endif
