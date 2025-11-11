#include "so_long.h"

bool	init_enemy_down(t_character *e, mlx_t *mlx, char *one, char *two)
{
	e->down.text = malloc(sizeof(mlx_texture_t *) * NUM_ENEMY_SPRITES);
	if (!e->down.text)
		return (false);
	e->down.num_frames = NUM_ENEMY_SPRITES;
	e->down.text[0] = mlx_load_png(one);
	e->down.text[1] = mlx_load_png(two);
	e->down.imgs = malloc(sizeof(mlx_image_t *) * NUM_ENEMY_SPRITES);
	if (!e->down.imgs)
		return (false);
	e->down.imgs[0] = mlx_texture_to_image(mlx, e->down.text[0]);
	e->down.imgs[1] = mlx_texture_to_image(mlx, e->down.text[1]);
	return (true);
}

bool	init_enemy_up(t_character *e, mlx_t *mlx, char *one, char *two)
{
	e->up.text = malloc(sizeof(mlx_texture_t *) * NUM_ENEMY_SPRITES);
	if (!e->up.text)
		return (false);
	e->up.num_frames = NUM_ENEMY_SPRITES;
	e->up.text[0] = mlx_load_png(one);
	e->up.text[1] = mlx_load_png(two);
	e->up.imgs = malloc(sizeof(mlx_image_t *) * NUM_ENEMY_SPRITES);
	if (!e->up.imgs)
		return (false);
	e->up.imgs[0] = mlx_texture_to_image(mlx, e->up.text[0]);
	e->up.imgs[1] = mlx_texture_to_image(mlx, e->up.text[1]);
	return (true);
}

bool	init_enemy_right(t_character *e, mlx_t *mlx, char *one, char *two)
{
	e->right.text = malloc(sizeof(mlx_texture_t *) * NUM_ENEMY_SPRITES);
	if (!e->right.text)
		return (false);
	e->right.num_frames = NUM_ENEMY_SPRITES;
	e->right.text[0] = mlx_load_png(one);
	e->right.text[1] = mlx_load_png(two);
	e->right.imgs = malloc(sizeof(mlx_image_t *) * NUM_ENEMY_SPRITES);
	if (!e->right.imgs)
		return (false);
	e->right.imgs[0] = mlx_texture_to_image(mlx, e->right.text[0]);
	e->right.imgs[1] = mlx_texture_to_image(mlx, e->right.text[1]);
	return (true);
}

bool	init_enemy_left(t_character *e, mlx_t *mlx, char *one, char *two)
{
	e->left.text = malloc(sizeof(mlx_texture_t *) * NUM_ENEMY_SPRITES);
	if (!e->left.text)
		return (false);
	e->left.num_frames = NUM_ENEMY_SPRITES;
	e->left.text[0] = mlx_load_png(one);
	e->left.text[1] = mlx_load_png(two);
	e->left.imgs = malloc(sizeof(mlx_image_t *) * NUM_ENEMY_SPRITES);
	if (!e->left.imgs)
		return (false);
	e->left.imgs[0] = mlx_texture_to_image(mlx, e->left.text[0]);
	e->left.imgs[1] = mlx_texture_to_image(mlx, e->left.text[1]);
	return (true);
}

bool	init_anim_enemy_red(t_character *e, mlx_t *mlx)
{
	if (!init_enemy_up(e, mlx, ENEMY_RED_UP_1, ENEMY_RED_UP_2))
		return (false);
	if (!init_enemy_down(e, mlx, ENEMY_RED_DOWN_1, ENEMY_RED_DOWN_2))
		return (false);
	if (!init_enemy_right(e, mlx, ENEMY_RED_RIGHT_1, ENEMY_RED_RIGHT_2))
		return (false);
	if (!init_enemy_left(e, mlx, ENEMY_RED_LEFT_1, ENEMY_RED_LEFT_2))
		return (false);
	return (true);
}

bool	init_anim_enemy_blue(t_character *e, mlx_t *mlx)
{
	if (!init_enemy_up(e, mlx, ENEMY_BLUE_UP_1, ENEMY_BLUE_UP_2))
		return (false);
	if (!init_enemy_down(e, mlx, ENEMY_BLUE_DOWN_1, ENEMY_BLUE_DOWN_2))
		return (false);
	if (!init_enemy_right(e, mlx, ENEMY_BLUE_RIGHT_1, ENEMY_BLUE_RIGHT_2))
		return (false);
	if (!init_enemy_left(e, mlx, ENEMY_BLUE_LEFT_1, ENEMY_BLUE_LEFT_2))
		return (false);
	return (true);
}

bool	init_anim_enemy_orange(t_character *e, mlx_t *mlx)
{
	if (!init_enemy_up(e, mlx, ENEMY_ORANGE_UP_1, ENEMY_ORANGE_UP_2))
		return (false);
	if (!init_enemy_down(e, mlx, ENEMY_ORANGE_DOWN_1, ENEMY_ORANGE_DOWN_2))
		return (false);
	if (!init_enemy_right(e, mlx, ENEMY_ORANGE_RIGHT_1, ENEMY_ORANGE_RIGHT_2))
		return (false);
	if (!init_enemy_left(e, mlx, ENEMY_ORANGE_LEFT_1, ENEMY_ORANGE_LEFT_2))
		return (false);
	return (true);
}

bool	init_anim_enemy_pink(t_character *e, mlx_t *mlx)
{
	if (!init_enemy_up(e, mlx, ENEMY_PINK_UP_1, ENEMY_PINK_UP_2))
		return (false);
	if (!init_enemy_down(e, mlx, ENEMY_PINK_DOWN_1, ENEMY_PINK_DOWN_2))
		return (false);
	if (!init_enemy_right(e, mlx, ENEMY_PINK_RIGHT_1, ENEMY_PINK_RIGHT_2))
		return (false);
	if (!init_enemy_left(e, mlx, ENEMY_PINK_LEFT_1, ENEMY_PINK_LEFT_2))
		return (false);
	return (true);
}

bool	init_emenies(t_solong *so)
{
	uint16_t	i;

	i = 0;
	while (i < so->num_enemies)
	{
		if (i % 4 == 0)
		{
			if (!init_anim_enemy_red(&so->enemies[i], so->mlx))
				return (false);
		}
		else if (i % 4 == 1)
		{
			if (!init_anim_enemy_blue(&so->enemies[i], so->mlx))
				return (false);
		}
		else if (i % 4 == 2)
		{
			if (!init_anim_enemy_orange(&so->enemies[i], so->mlx))
				return (false);
		}
		else
		{
			if (!init_anim_enemy_pink(&so->enemies[i], so->mlx))
				return (false);
		}
		i++;
	}

}