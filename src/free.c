/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:27:50 by rstancu           #+#    #+#             */
/*   Updated: 2025/11/11 13:32:15 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_imgs(mlx_image_t **imgs, mlx_t *mlx, int num,
	mlx_texture_t **text)
{
	uint16_t	i;

	i = 0;
	while (i < num)
	{
		if (imgs && imgs[i])
		{
			if (mlx)
				mlx_delete_image(mlx, imgs[i]);
			if (text && text[i])
				mlx_delete_texture(text[i]);
		}
		i++;
	}
	if (imgs)
		free(imgs);
	if (text)
		free(text);
}

void	free_character(t_character *character, mlx_t *mlx)
{
	int32_t		num;

	num = NUM_PLAYER_SPRITES;
	free_imgs(character->right.imgs, mlx, num, character->right.text);
	free_imgs(character->left.imgs, mlx, num, character->left.text);
	free_imgs(character->up.imgs, mlx, num, character->up.text);
	free_imgs(character->down.imgs, mlx, num, character->down.text);
}

bool	free_all(t_solong *so)
{
	if (so->is_running)
	{
		free_player(so);
		if (so->cell_tile)
			mlx_delete_image(so->mlx, so->cell_tile);
		if (so->text_cell)
			mlx_delete_texture(so->text_cell);
		free_exit(so);
		free_collectibles(so);
		if (so->background)
			mlx_delete_image(so->mlx, so->background);
		if (so->movements_img)
			mlx_delete_image(so->mlx, so->movements_img);
		free_map(so->map, so->mlx);
	}
	return (false);
}
