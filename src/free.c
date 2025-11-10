/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:27:50 by rstancu           #+#    #+#             */
/*   Updated: 2025/11/10 11:47:16 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// void	free_platf_info(t_platform_data *plat, mlx_t *mlx, t_xpm_platform *xpm)
// {
// 	size_t i;
	
// 	i= 0;
// 	mlx_delete_image(mlx, plat->under_start);
// 	mlx_delete_image(mlx, plat->top_end);
// 	mlx_delete_image(mlx, plat->under_end);
// 	while (i < plat->num_mid_sprites)
// 	{
// 		mlx_delete_image(mlx, plat->top[i]);
// 		mlx_delete_image(mlx, plat->under[i]);
// 		i++;
// 	}
// 	free(plat->top);
// 	free(plat->under);
// 	mlx_delete_xpm42(xpm->top_start);
// 	mlx_delete_xpm42(xpm->under_start);
// 	mlx_delete_xpm42(xpm->top_end);
// 	mlx_delete_xpm42(xpm->under_end);
// 	i = 0;
// 	while (i < xpm->num_mid_sprites)
// 	{
// 		mlx_delete_xpm42(xpm->top[i]);
// 		mlx_delete_xpm42(xpm->under[i]);
// 		i++;
// 	}

// 	free(xpm->top);
// 	free(xpm->under);
// }

// bool	free_old_map(int32_t **map, size_t height)
// {
// 	size_t	i;

// 	i = -1;
// 	if (map)
// 	{
// 		while (++i < height)
// 			if (map[i])
// 				free(map[i]);
// 		free(map);
// 	}
// 	return (false);
// }

// bool	free_arr_xpm42(void **arr, size_t size)
// {
// 	if (arr)
// 	{
// 		while (--size)
// 		{
// 			if (arr[size])
// 				mlx_delete_xpm42((xpm_t *)arr[size]);
// 		}
// 		free(arr);
// 	}
// 	return (false);
// }


// bool	free_buffer_imgs(t_solong *so)
// {
// 	size_t	j;

// 	j = 0;
// 	while (j < so->map->num_platforms)
// 	{
// 		if (so->map->plat[j])
// 		{
// 			size_t k = 0;
// 			while (k < so->map->plat[j]->size)
// 			{
// 				if (so->map->plat[j]->buffer_top && so->map->plat[j]->buffer_top[k])
// 					mlx_delete_image(so->mlx, so->map->plat[j]->buffer_top[k]);
// 				if (so->map->plat[j]->buffer_under && so->map->plat[j]->buffer_under[k])
// 					mlx_delete_image(so->mlx, so->map->plat[j]->buffer_under[k]);
// 				k++;
// 			}
// 			free(so->map->plat[j]->buffer_top);
// 			free(so->map->plat[j]->buffer_under);
// 		}
// 		j++;
// 	}
// 	return (false);
// }

// bool	free_buff_ladder(t_solong *so)
// {
// 	size_t	k;

// 	k = 0;
// 	while (k < NUM_PLAT_SPRITES)
// 	{
// 		if (so->map->info_plat.down_ladder[k])
// 			mlx_delete_image(so->mlx, so->map->info_plat.down_ladder[k]);
// 		if (so->map->info_plat.down_ladder[k])
// 			mlx_delete_image(so->mlx, so->map->info_plat.down_ladder[k]);
// 		k++;
// 	}
// 	k = 0;
// 	while (k < NUM_PLAT_SPRITES)
// 	{
// 		if (so->map->xpm_plat.down_ladder[k])
// 			mlx_delete_xpm42(so->map->xpm_plat.down_ladder[k]);
// 		if (so->map->xpm_plat.up_ladder[k])
// 			mlx_delete_xpm42(so->map->xpm_plat.up_ladder[k]);
// 		k++;
// 	}
// 	mlx_delete_image(so->mlx, so->map->info_plat.ladder);
// 	mlx_delete_xpm42(so->map->xpm_plat.ladder);
// 	return (false);
// }

// void	free_player_sprites(t_character *player, mlx_t *mlx)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < NUM_PLAYER_WALK_SPRITES)
// 	{
// 		if (player->walk_left[i])
// 			mlx_delete_image(mlx, player->walk_left[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < NUM_PLAYER_WALK_SPRITES)
// 	{
// 		if (player->xpm[i])
// 			mlx_delete_xpm42(player->xpm[i]);
// 		i++;
// 	}
// }

// bool	free_all(t_solong *so)
// {
// 	size_t	i;

// 	i = -1;
// 	if (so->map->floor)
// 	{
// 		while (++i < so->map->weight)
// 		{
// 			if (so->map->floor[i])
// 				mlx_delete_image(so->mlx, so->map->floor[i]);
// 		}
// 		free(so->map->floor);
// 	}
// 	if (so->map->floor_collsion)
// 		free(so->map->floor_collsion);
// 	if (so->background)
// 	{
// 		mlx_delete_image(so->mlx, so->background);
// 	}
// 	i = -1;
// 	if (so->map->plat)
// 	{
// 		while (++i < so->map->num_platforms)
// 		{
// 			if (so->map->plat[i])
// 			{
// 				if (so->map->plat[i]->height_px)
// 					free(so->map->plat[i]->height_px);
// 				if (so->map->plat[i]->buffer_top)
// 					free(so->map->plat[i]->buffer_top);
// 				if (so->map->plat[i]->buffer_under)
// 					free(so->map->plat[i]->buffer_under);
// 				free(so->map->plat[i]);
// 			}
// 		}
// 		free(so->map->plat);
// 	}
// 	//free_buffer_imgs(so);
// 	free_platf_info(&so->map->info_plat, so->mlx, &so->map->xpm_plat);
// 	mlx_delete_xpm42(so->map->xpm_plat.top_start);
// 	mlx_delete_xpm42(so->map->xpm_plat.top_end);
// 	mlx_delete_xpm42(so->map->xpm_plat.under_end);
// 	mlx_delete_xpm42(so->map->xpm_plat.under_start);
// 	free_buff_ladder(so);
// 	free_arr_xpm42((void **)so->map->xpm_plat.top, so->map->xpm_plat.num_mid_sprites);
// 	free_arr_xpm42((void **)so->map->xpm_plat.under, so->map->xpm_plat.num_mid_sprites);
// 	free_player_sprites(&so->player, so->mlx);
// 	if (so->map->info_plat.up_ladder)
// 		free(so->map->info_plat.up_ladder);
// 	if (so->map->info_plat.down_ladder)
// 		free(so->map->info_plat.down_ladder);
// 	i = 0;
// 	while (i < so->map->weight)
// 	{
// 		free(so->map->collision_map[i]);
// 		i++;
// 	}
// 	free(so->map->collision_map);
// 	i = 0;
// 	if (so->map->arr)
// 	{
// 		while (so->map->arr[i])
// 			free(so->map->arr[i++]);
// 		free(so->map->arr);
// 	}
// 	// i = 0;
// 	// while (i < so->map->num_platforms)
// 	// {
// 	// 	free(so->map->plat)
// 	// }
// 	if (so->map)
// 		free(so->map);
// 	return (false);
// }

