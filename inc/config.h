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

#define TILESIZE			24
#define TARGET_FPS			120
#define ANIM_FRAME_INTERVAL 80.0	// ms
#define FOLLOW_SPEED_PX_S	1000.0
#define PX_PER_SECONDS		200.0

#define PHYS_DT_MS	8          // 125 Hz
#define MAX_ACC_MS	250

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


#ifndef ASSET_DIR
    #define ASSET_DIR "../tiles"
#endif
///// PLAYER
#define NUM_PLAYER_SPRITES	3
#define PLAYER_UP_1 ASSET_DIR	"/up_1.png"
#define PLAYER_UP_2 ASSET_DIR	"/up_2.png"
#define PLAYER_UP_3 ASSET_DIR	"/up_3.png"

#define PLAYER_DOWN_1 ASSET_DIR	"/down_1.png"
#define PLAYER_DOWN_2 ASSET_DIR	"/down_2.png"
#define PLAYER_DOWN_3 ASSET_DIR	"/down_3.png"

#define PLAYER_RIGHT_1 ASSET_DIR	"/right_1.png"
#define PLAYER_RIGHT_2 ASSET_DIR	"/right_2.png"
#define PLAYER_RIGHT_3 ASSET_DIR	"/right_3.png"

#define PLAYER_LEFT_1 ASSET_DIR	"/left_1.png"
#define PLAYER_LEFT_2 ASSET_DIR	"/left_2.png"
#define PLAYER_LEFT_3 ASSET_DIR	"/left_3.png"

/////////////////////////////////// ENEMIES
#define NUM_ENEMY_SPRITES	2
#define ENEMY_RED_UP_1 ASSET_DIR	"/red_up_1.png"
#define ENEMY_RED_UP_2 ASSET_DIR	"/red_up_2.png"
#define ENEMY_RED_DOWN_1 ASSET_DIR	"/red_down_1.png"
#define ENEMY_RED_DOWN_2 ASSET_DIR	"/red_down_2.png"
#define ENEMY_RED_RIGHT_1 ASSET_DIR	"/red_right_1.png"
#define ENEMY_RED_RIGHT_2 ASSET_DIR	"/red_right_2.png"
#define ENEMY_RED_LEFT_1 ASSET_DIR	"/red_left_1.png"
#define ENEMY_RED_LEFT_2 ASSET_DIR	"/red_left_2.png"
///////////////////////////////////
#define ENEMY_BLUE_UP_1 ASSET_DIR	"/blue_up_1.png"
#define ENEMY_BLUE_UP_2 ASSET_DIR	"/blue_up_2.png"
#define ENEMY_BLUE_DOWN_1 ASSET_DIR	"/blue_down_1.png"
#define ENEMY_BLUE_DOWN_2 ASSET_DIR	"/blue_down_2.png"
#define ENEMY_BLUE_RIGHT_1 ASSET_DIR	"/blue_right_1.png"
#define ENEMY_BLUE_RIGHT_2 ASSET_DIR	"/blue_right_2.png"
#define ENEMY_BLUE_LEFT_1 ASSET_DIR	"/blue_left_1.png"
#define ENEMY_BLUE_LEFT_2 ASSET_DIR	"/blue_left_2.png"
///////////////////////////////////
#define ENEMY_ORANGE_UP_1 ASSET_DIR	"/orange_up_1.png"
#define ENEMY_ORANGE_UP_2 ASSET_DIR	"/orange_up_2.png"
#define ENEMY_ORANGE_DOWN_1 ASSET_DIR	"/orange_down_1.png"
#define ENEMY_ORANGE_DOWN_2 ASSET_DIR	"/orange_down_2.png"
#define ENEMY_ORANGE_RIGHT_1 ASSET_DIR	"/orange_right_1.png"
#define ENEMY_ORANGE_RIGHT_2 ASSET_DIR	"/orange_right_2.png"
#define ENEMY_ORANGE_LEFT_1 ASSET_DIR	"/orange_left_1.png"
#define ENEMY_ORANGE_LEFT_2 ASSET_DIR	"/orange_left_2.png"
///////////////////////////////////
#define ENEMY_PINK_UP_1 ASSET_DIR	"/pink_up_1.png"
#define ENEMY_PINK_UP_2 ASSET_DIR	"/pink_up_2.png"
#define ENEMY_PINK_DOWN_1 ASSET_DIR	"/pink_down_1.png"
#define ENEMY_PINK_DOWN_2 ASSET_DIR	"/pink_down_2.png"
#define ENEMY_PINK_RIGHT_1 ASSET_DIR	"/pink_right_1.png"
#define ENEMY_PINK_RIGHT_2 ASSET_DIR	"/pink_right_2.png"
#define ENEMY_PINK_LEFT_1 ASSET_DIR	"/pink_left_1.png"
#define ENEMY_PINK_LEFT_2 ASSET_DIR	"/pink_left_2.png"

#define CELL_TEXTURE ASSET_DIR	"/cell.png"

#define COLLECT_1 ASSET_DIR	"/cherry.png"
#define COLLECT_2 ASSET_DIR	"/strawberry.png"
#define COLLECT_3 ASSET_DIR	"/orange.png"
#define COLLECT_4 ASSET_DIR	"/apple.png"

#define EXIT_TEXTURE ASSET_DIR	"/exit.png"

#endif
