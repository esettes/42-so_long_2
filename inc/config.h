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
    #define ASSET_DIR "../tiles/xpm"
#endif
///// Platform
#define NUM_PLAT_SPRITES	7
#define FLOOR_1_UP ASSET_DIR "/floor_1.xpm42"
#define FLOOR_1_DOWN ASSET_DIR "/floor_1_2.xpm42"
#define FLOOR_2_UP ASSET_DIR "/floor_2.xpm42"
#define FLOOR_2_DOWN ASSET_DIR "/floor_2_2.xpm42"
#define FLOOR_3_UP ASSET_DIR "/floor_3.xpm42"
#define FLOOR_3_DOWN ASSET_DIR "/floor_3_2.xpm42"
#define FLOOR_4_UP ASSET_DIR "/floor_4.xpm42"
#define FLOOR_4_DOWN ASSET_DIR "/floor_4_2.xpm42"
#define FLOOR_5_UP ASSET_DIR "/floor_5.xpm42"
#define FLOOR_5_DOWN ASSET_DIR "/floor_5_2.xpm42"
#define FLOOR_6_UP ASSET_DIR "/floor_6.xpm42"
#define FLOOR_6_DOWN ASSET_DIR "/floor_6_2.xpm42"
#define FLOOR_7_UP ASSET_DIR "/floor_7.xpm42"
#define FLOOR_7_DOWN ASSET_DIR "/floor_7_2.xpm42"
///// Ladder
#define LADDER_MID ASSET_DIR "/ladder.xpm42"
#define LADDER_1_UP ASSET_DIR "/ladder_1.xpm42"
#define LADDER_1_DOWN ASSET_DIR "/ladder_1_2.xpm42"
#define LADDER_2_UP ASSET_DIR "/ladder_2.xpm42"
#define LADDER_2_DOWN ASSET_DIR "/ladder_2_2.xpm42"
#define LADDER_3_UP ASSET_DIR "/ladder_3.xpm42"
#define LADDER_3_DOWN ASSET_DIR "/ladder_3_2.xpm42"
#define LADDER_4_UP ASSET_DIR "/ladder_4.xpm42"
#define LADDER_4_DOWN ASSET_DIR "/ladder_4_2.xpm42"
#define LADDER_5_UP ASSET_DIR "/ladder_5.xpm42"
#define LADDER_5_DOWN ASSET_DIR "/ladder_5_2.xpm42"
#define LADDER_6_UP ASSET_DIR "/ladder_6.xpm42"
#define LADDER_6_DOWN ASSET_DIR "/ladder_6_2.xpm42"
#define LADDER_7_UP ASSET_DIR "/ladder_7.xpm42"
#define LADDER_7_DOWN ASSET_DIR "/ladder_7_2.xpm42"
///// Player
#define NUM_PLAYER_WALK_SPRITES	3
#define PLAYER_WALK_0 ASSET_DIR "/player/Walk_0.xpm42"
#define PLAYER_WALK_1 ASSET_DIR "/player/Walk_1.xpm42"
#define PLAYER_WALK_2 ASSET_DIR "/player/Walk_2.xpm42"
#define PLAYER_WALK_INVERT_0 ASSET_DIR "/player/Walk_inverted_3.xpm42"
#define PLAYER_WALK_INVERT_1 ASSET_DIR "/player/Walk_inverted_2.xpm42"
#define PLAYER_WALK_INVERT_2 ASSET_DIR "/player/Walk_inverted_1.xpm42"
#define PLAYER_UP_0 ASSET_DIR "/player/Up_1.xpm42"
#define PLAYER_UP_1 ASSET_DIR "/player/Up_2.xpm42"
#define PLAYER_UP_2 ASSET_DIR "/player/Up_1.xpm42"
#define PLAYER_IDLE_0 ASSET_DIR "/player/Walk_0.xpm42"
#define PLAYER_IDLE_RIGHT ASSET_DIR "/player/Walk_inverted_1.xpm42"
#endif
