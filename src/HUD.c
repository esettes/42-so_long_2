#include "so_long.h"

// static inline int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
// {
//     return (r << 24 | g << 16 | b << 8 | a);
// }

void	print_player_pos(t_solong *so)
{
	char	pos_str[50];
	int		x;
	int		y;
	t_int2		player_tile;

	get_tile_and_center(so->player.render_pos, &player_tile, NULL);
	x = (int)(so->player.render_pos.x);
	y = (int)(so->player.render_pos.y);
	if (so->hud_text_img)
	{
		mlx_delete_image(so->mlx, so->hud_text_img);
	}
	
	so->hud_db->instances[0].x = x;
	so->hud_db->instances[0].y = y - 10;
	
	sprintf(pos_str, "Pos: (%d, %d)", player_tile.x, player_tile.y);
	so->hud_text_img = mlx_put_string(so->mlx, pos_str, (int)(so->player.render_pos.x), (int)(so->player.render_pos.y) - 10);
}
