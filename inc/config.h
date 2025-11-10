/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:29:38 by rstancu           #+#    #+#             */
/*   Updated: 2025/11/04 19:08:25 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

#define TILESIZE			64
#define TARGET_FPS			120
#define ANIM_FRAME_INTERVAL 60	// ms

#define	JUMPBUF_MS	120.0f
#define COYOTE_MS   120.0f

#define PHYS_DT_MS	6          // 125 Hz
#define MAX_ACC_MS	250
#define	GRAVITY		4800.0f
#define	JUMP		-1150.0f
#define	DRAG		2.0f
#define	GROUND		(TILESIZE * 12) - (TILESIZE)

typedef enum e_map_typos
{
	M_SPACE = 0,
	M_PLATFORM,
	M_LADDER_UP,
	M_LADDER_DOWN,
	M_LADDER,
	M_WALL,
	M_FLOOR,
	M_CEIL,
	M_PLAYER,
	M_COLLECTIBLE,
	M_ENEMY,
	M_EXIT
}	t_map_typos;

typedef uint16_t t_tile_flags;

enum e_tile_flags{
    TF_EMPTY          = 0u,
    TF_PLATFORM_TOP   = 1u << 0,  // one-way: blocks only when falling from above
    TF_LADDER         = 1u << 1,  // ladder cell
    TF_LADDER_DOWN	  = 1u << 2,  // ladder starts here (no ladder above)
    TF_LADDER_UP	  = 1u << 3,  // ladder ends here (no ladder below)
    TF_SOLID_FULL     = 1u << 4   // optional: full solid block (walls)
};

#ifndef ASSET_DIR
    #define ASSET_DIR "../tiles"
#endif
///// PLAYER
#define NUM_PLAYER_SPRITES	3
#define PLAYER_UP_1	"/up_1.png"
#define PLAYER_UP_2	"/up_2.png"
#define PLAYER_UP_3	"/up_3.png"

#define PLAYER_DOWN_1	"/down_1.png"
#define PLAYER_DOWN_2	"/down_2.png"
#define PLAYER_DOWN_3	"/down_3.png"

#define PLAYER_RIGHT_1	"/right_1.png"
#define PLAYER_RIGHT_2	"/right_2.png"
#define PLAYER_RIGHT_3	"/right_3.png"

#define PLAYER_LEFT_1	"/left_1.png"
#define PLAYER_LEFT_2	"/left_2.png"
#define PLAYER_LEFT_3	"/left_3.png"

/////////////////////////////////// ENEMIES
#define NUM_ENEMY_SPRITES	2
#define ENEMY_RED_UP_1	"/red_up_1.png"
#define ENEMY_RED_UP_2	"/red_up_2.png"
#define ENEMY_RED_DOWN_1	"/red_down_1.png"
#define ENEMY_RED_DOWN_2	"/red_down_2.png"
#define ENEMY_RED_RIGHT_1	"/red_right_1.png"
#define ENEMY_RED_RIGHT_2	"/red_right_2.png"
#define ENEMY_RED_LEFT_1	"/red_left_1.png"
#define ENEMY_RED_LEFT_2	"/red_left_2.png"
///////////////////////////////////
#define ENEMY_BLUE_UP_1	"/blue_up_1.png"
#define ENEMY_BLUE_UP_2	"/blue_up_2.png"
#define ENEMY_BLUE_DOWN_1	"/blue_down_1.png"
#define ENEMY_BLUE_DOWN_2	"/blue_down_2.png"
#define ENEMY_BLUE_RIGHT_1	"/blue_right_1.png"
#define ENEMY_BLUE_RIGHT_2	"/blue_right_2.png"
#define ENEMY_BLUE_LEFT_1	"/blue_left_1.png"
#define ENEMY_BLUE_LEFT_2	"/blue_left_2.png"
///////////////////////////////////
#define ENEMY_ORANGE_UP_1	"/orange_up_1.png"
#define ENEMY_ORANGE_UP_2	"/orange_up_2.png"
#define ENEMY_ORANGE_DOWN_1	"/orange_down_1.png"
#define ENEMY_ORANGE_DOWN_2	"/orange_down_2.png"
#define ENEMY_ORANGE_RIGHT_1	"/orange_right_1.png"
#define ENEMY_ORANGE_RIGHT_2	"/orange_right_2.png"
#define ENEMY_ORANGE_LEFT_1	"/orange_left_1.png"
#define ENEMY_ORANGE_LEFT_2	"/orange_left_2.png"
///////////////////////////////////
#define ENEMY_PINK_UP_1	"/pink_up_1.png"
#define ENEMY_PINK_UP_2	"/pink_up_2.png"
#define ENEMY_PINK_DOWN_1	"/pink_down_1.png"
#define ENEMY_PINK_DOWN_2	"/pink_down_2.png"
#define ENEMY_PINK_RIGHT_1	"/pink_right_1.png"
#define ENEMY_PINK_RIGHT_2	"/pink_right_2.png"
#define ENEMY_PINK_LEFT_1	"/pink_left_1.png"
#define ENEMY_PINK_LEFT_2	"/pink_left_2.png"

#endif
